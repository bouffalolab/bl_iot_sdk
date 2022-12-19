/*
 * Amazon FreeRTOS POSIX V1.1.0
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file FreeRTOS_POSIX_clock.c
 * @brief Implementation of clock functions in time.h
 */

/* C standard library includes. */
#include <stddef.h>
#include <string.h>

/* FreeRTOS+POSIX includes. */
#include "FreeRTOS_POSIX.h"
//#include "FreeRTOS_POSIX/errno.h"
#include <errno.h>
#include <FreeRTOS_POSIX/bl_sys/time.h>

#include "FreeRTOS_POSIX/utils.h"

/* Declaration of snprintf. The header stdio.h is not included because it
 * includes conflicting symbols on some platforms. */
extern int snprintf( char * s,
                     size_t n,
                     const char * format,
                     ... );


/* simple epoch time implement for projects without bltime component */
static int gTimezone = 8*3600; //default timezone value is 8*3600(bejing)
static uint64_t gEpochTime = 0; //in ms
static uint64_t gSyncTick = 0; //in ms

__attribute__ ((weak)) int bl_sys_time_get(uint64_t *epoch)
{
    int ms_diff;

    if (0 == gEpochTime) {
        *epoch = xTaskGetTickCount();
        return -1;
    }

    ms_diff = ((int32_t)xTaskGetTickCount()) - ((int32_t)gSyncTick);
    *epoch = gEpochTime + ms_diff;

    return 0;
}

__attribute__ ((weak)) void bl_sys_time_update(uint64_t epoch)
{
    gSyncTick = xTaskGetTickCount();
    gEpochTime = epoch;
}

/*-----------------------------------------------------------*/

clock_t clock( void )
{
    /* This function is currently unsupported. It will always return -1. */

    return ( clock_t ) -1;
}

/*-----------------------------------------------------------*/

int clock_getcpuclockid( pid_t pid,
                         clockid_t * clock_id )
{
    /* Silence warnings about unused parameters. */
    ( void ) pid;
    ( void ) clock_id;

    /* This function is currently unsupported. It will always return EPERM. */
    return EPERM;
}

/*-----------------------------------------------------------*/

int clock_getres( clockid_t clock_id,
                  struct timespec * res )
{
    /* Silence warnings about unused parameters. */
    ( void ) clock_id;

    /* Convert FreeRTOS tick resolution as timespec. */
    if( res != NULL )
    {
        res->tv_sec = 0;
        res->tv_nsec = NANOSECONDS_PER_TICK;
    }

    return 0;
}

/*-----------------------------------------------------------*/
int __clock_gettime(struct timespec * tp)
{
    unsigned int update_tick = 0;
    uint64_t epoch_time = 0;
    uint32_t current_sec = 0, current_msec = 0;

    bl_sys_time_get(&epoch_time);
    current_sec = epoch_time / 1000;
    current_msec = epoch_time % 1000;

    tp->tv_sec = current_sec;
    tp->tv_nsec = current_msec*1000000;
    //printf("%s:%d, time = %d, %d\r\n", __func__, __LINE__, (int)tp->tv_sec, (int)tp->tv_nsec);
    return 0;
}

int clock_gettime( clockid_t clock_id,
                   struct timespec * tp )
{
    TimeOut_t xCurrentTime = { 0 };
    int iStatus = 0;

    /* Intermediate variable used to convert TimeOut_t to struct timespec.
     * Also used to detect overflow issues. It must be unsigned because the
     * behavior of signed integer overflow is undefined. */
    uint64_t ullTickCount = 0ULL;

    /* Silence warnings about unused parameters. */
    ( void ) clock_id;

    /* Check tp. */
    if( tp == NULL )
    {
        /* POSIX does not specify this function setting errno for invalid
         * parameters, so just set the return value. */
        iStatus = -1;
    }

    if( iStatus == 0 )
    {
        switch (clock_id) {
        case CLOCK_REALTIME:
            __clock_gettime(tp);  
            break;
        case CLOCK_MONOTONIC:
            /* Get the current tick count and overflow count. vTaskSetTimeOutState()
            * is used to get these values because they are both static in tasks.c. */
            vTaskSetTimeOutState( &xCurrentTime );

            /* Adjust the tick count for the number of times a TickType_t has overflowed.
            * portMAX_DELAY should be the maximum value of a TickType_t. */
            ullTickCount = ( uint64_t ) ( xCurrentTime.xOverflowCount ) << ( sizeof( TickType_t ) * 8 );

            /* Add the current tick count. */
            ullTickCount += ( uint64_t) xCurrentTime.xTimeOnEntering;

            /* Convert ullTickCount to timespec. */
            UTILS_NanosecondsToTimespec( ( int64_t ) (ullTickCount * NANOSECONDS_PER_TICK), tp );
            break;
        default:
            iStatus = -1;
        }
    }

    return iStatus;
}

/*-----------------------------------------------------------*/

int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const struct timespec * rqtp,
                     struct timespec * rmtp )
{
    int iStatus = 0;
    TickType_t xSleepTime = 0;
    struct timespec xCurrentTime = { 0 };

    /* Silence warnings about unused parameters. */
    ( void ) clock_id;
    ( void ) rmtp;
    ( void ) flags; /* This is only ignored if INCLUDE_vTaskDelayUntil is 0. */

    /* Check rqtp. */
    if( UTILS_ValidateTimespec( rqtp ) == false )
    {
        iStatus = EINVAL;
    }

    /* Get current time */
    if( ( iStatus == 0 ) && ( clock_gettime( CLOCK_REALTIME, &xCurrentTime ) != 0 ) )
    {
        iStatus = EINVAL;
    }

    if( iStatus == 0 )
    {
        /* Check for absolute time sleep. */
        if( ( flags & TIMER_ABSTIME ) == TIMER_ABSTIME )
        {
            /* Get current time */
            if( clock_gettime( CLOCK_REALTIME, &xCurrentTime ) != 0 )
            {
                iStatus = EINVAL;
            }

            /* Get number of ticks until absolute time. */
            if( ( iStatus == 0 ) && ( UTILS_AbsoluteTimespecToDeltaTicks( rqtp, &xCurrentTime, &xSleepTime ) == 0 ) )
            {
                /* Delay until absolute time if vTaskDelayUntil is available. */
                #if ( INCLUDE_vTaskDelayUntil == 1 )

                    /* Get the current tick count. This variable isn't declared
                     * at the top of the function because it's only used and needed
                     * if vTaskDelayUntil is available. */
                    TickType_t xCurrentTicks = xTaskGetTickCount();

                    /* Delay until absolute time. */
                    vTaskDelayUntil( &xCurrentTicks, xSleepTime );
                #else

                    /* If vTaskDelayUntil isn't available, ignore the TIMER_ABSTIME flag
                     * and sleep for a relative time. */
                    vTaskDelay( xSleepTime );
                #endif
            }
        }
        else
        {
            /* If TIMER_ABSTIME isn't specified, convert rqtp to ticks and
             * sleep for a relative time. */
            if( UTILS_TimespecToTicks( rqtp, &xSleepTime ) == 0 )
            {
                vTaskDelay( xSleepTime );
            }
        }
    }

    return iStatus;
}

/*-----------------------------------------------------------*/

int clock_settime( clockid_t clock_id,
                   const struct timespec * tp )
{
#if 0
    /* Silence warnings about unused parameters. */
    ( void ) clock_id;
    ( void ) tp;

    /* This function is currently unsupported. It will always return -1 and
     * set errno to EPERM. */
    errno = EPERM;

    return -1;
#else
    bl_sys_time_update((tp->tv_sec * NANOSECONDS_PER_SECOND + tp->tv_nsec) / MICROSECONDS_PER_SECOND);

    return 0;
#endif
}

/*-----------------------------------------------------------*/
void setTimezone(int tz)
{
    gTimezone = tz;
}
int getTimezone(void)
{
    return gTimezone;
}


/*-----------------------------------------------------------*/

int nanosleep( const struct timespec * rqtp,
               struct timespec * rmtp )
{
    int iStatus = 0;
    TickType_t xSleepTime = 0;

    /* Silence warnings about unused parameters. */
    ( void ) rmtp;

    /* Check rqtp. */
    if( UTILS_ValidateTimespec( rqtp ) == false )
    {
        errno = EINVAL;
        iStatus = -1;
    }

    if( iStatus == 0 )
    {
        /* Convert rqtp to ticks and delay. */
        if( UTILS_TimespecToTicks( rqtp, &xSleepTime ) == 0 )
        {
            vTaskDelay( xSleepTime );
        }
    }

    return iStatus;
}

/*-----------------------------------------------------------*/
time_t time( time_t * tloc )
{
    time_t current_time;
    struct timespec tp;

    __clock_gettime(&tp);
    current_time = tp.tv_sec;

    if( tloc != NULL )
        *tloc = current_time;

    return current_time;
}

/*-----------------------------------------------------------*/

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    unsigned int ms = 0;
    if(tv)
    {
        long sec = 0;
        long usec = 0;
        struct timespec tp;
        __clock_gettime(&tp);
        tv->tv_sec = tp.tv_sec;
        tv->tv_usec = tp.tv_nsec / 1000;
    }
    if(tz)
    {
        tz->tz_minuteswest = 0;
        tz->tz_dsttime = 0;
    }
    return 0;
}

int settimeofday(struct timeval *tv, struct timezone *tz)
{
    bl_sys_time_update((tv->tv_sec * MICROSECONDS_PER_SECOND + tv->tv_usec) / 1000);

    return 0;
}


