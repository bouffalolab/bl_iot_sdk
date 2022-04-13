#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <bl_timer.h>

#include <openthread/config.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/alarm-micro.h>
#include <openthread/platform/time.h>
#include <openthread/platform/diag.h>
#include <openthread_port.h>
#include <openthread_assert.h>


#define OT_ALARM_TIMER_MARGIN               10   /** 10 us */
#define OT_ALARM_TIMER_ID                   0

typedef struct {
    otInstance  *aInstance;
    uint32_t    periodnum;
    uint32_t    target;
    uint32_t    state;      /** 0, not start, 1, ms timer, 2, us timer */
} otAlarm_t;

otAlarm_t otAlarm_var = {.aInstance = NULL, .periodnum = 0, .state = 0};

static void ot_alarmCb (void);
static void ot_alarmStart (otInstance *aInstance, bool isms, uint32_t aT0, uint32_t aDt);

void ot_alarmCb (void) 
{
    uint32_t sevent;

    uint32_t critial = OT_ENTER_CRITICAL_ISR();
    if (otAlarm_var.state == 1) {
        sevent = OT_SYSTEM_EVENT_ALARM_MS_EXPIRED;
    }
    else if (otAlarm_var.state == 2) {
        sevent = OT_SYSTEM_EVENT_ALARM_US_EXPIRED;
    }
    else {
        otAlarm_var.state = 0;
        OT_EXIT_CRITICAL_ISR(critial);
        return;
    }
    
    if (otAlarm_var.periodnum == 0) {
        otAlarm_var.state = 0;
        OT_EXIT_CRITICAL_ISR(critial);
        OT_NOTIFY_ISR(sevent);
        return;
    }
    else if (otAlarm_var.periodnum == 1) {
        if ((int64_t)bl_timer_get_current_time() + ((int64_t)1 << 32) - (int64_t)otAlarm_var.target <= OT_ALARM_TIMER_MARGIN) {
            otAlarm_var.state = 0;
            OT_EXIT_CRITICAL_ISR(critial);
            OT_NOTIFY_ISR(sevent);
            return;
        }
    }

    otAlarm_var.periodnum --;
    bl_timer_start(OT_ALARM_TIMER_ID, otAlarm_var.target, ot_alarmCb);
    OT_EXIT_CRITICAL_ISR(critial);
}

void ot_alarmStart (otInstance *aInstance, bool isms, uint32_t aT0, uint32_t aDt) 
{
    int64_t ustimeout;
    int64_t target;

    OT_ENTER_CRITICAL();
    if (0 == otAlarm_var.aInstance) {
        otAlarm_var.aInstance = aInstance;
    }

    otAlarm_var.state = 0;
    bl_timer_stop(OT_ALARM_TIMER_ID);

    ustimeout = bl_timer_get_current_time();
    if (isms) {
        target = (int64_t)aDt * 1000 + (int64_t)aT0 * 1000;
    }
    else {
        target = (int64_t)aDt + (int64_t)aT0;
    }

    ustimeout = target - ustimeout - (int64_t) OT_ALARM_TIMER_MARGIN;
    if (ustimeout <= 0) {
        OT_EXIT_CRITICAL();
        if (isms) {
            OT_NOTIFY(OT_SYSTEM_EVENT_ALARM_MS_EXPIRED);
        }
        else {
            OT_NOTIFY(OT_SYSTEM_EVENT_ALARM_US_EXPIRED);
        }
    }
    else {
        otAlarm_var.periodnum = (target >> 32);
        otAlarm_var.target = target & 0xffffffff;
        otAlarm_var.state = isms? 1: 2;

        bl_timer_start(OT_ALARM_TIMER_ID, otAlarm_var.target, ot_alarmCb);
        OT_EXIT_CRITICAL();
    }
}

uint64_t otPlatTimeGet(void)
{
    return (uint64_t)bl_timer_get_current_time() + ((uint64_t)bl_timer_get_overflow_cnt() << 32);
}

uint16_t otPlatTimeGetXtalAccuracy(void)
{
    return 0;
}

void otPlatAlarmMilliStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt)
{
    ot_alarmStart(aInstance, 1, aT0, aDt);
}

void otPlatAlarmMilliStop(otInstance *aInstance) 
{
    otAlarm_var.state = 0;
    bl_timer_stop(OT_ALARM_TIMER_ID);
}

uint32_t otPlatAlarmMilliGetNow(void) 
{
    return (uint32_t)(otPlatTimeGet() / 1000);
}

void ot_alarmTask(ot_system_event_t sevent) 
{
    if (!(OT_SYSTEM_EVENT_ALARM_ALL_MASK & sevent)) {
        return;
    }

    if (OT_SYSTEM_EVENT_ALARM_MS_EXPIRED & sevent) 
    {
        otPlatAlarmMilliFired(otAlarm_var.aInstance);
    }

#if OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
    if (OT_SYSTEM_EVENT_ALARM_US_EXPIRED & sevent) 
    {
        otPlatAlarmMicroFired(otAlarm_var.aInstance);
    }
#endif
}

void otPlatAlarmMicroStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt)
{
    ot_alarmStart(aInstance, 0, aT0, aDt);
}

void otPlatAlarmMicroStop(otInstance *aInstance)
{
    otAlarm_var.state = 0;
    bl_timer_stop(OT_ALARM_TIMER_ID);
}

uint32_t otPlatAlarmMicroGetNow(void)
{
   return bl_timer_get_current_time();
}


#if 0
typedef struct {
    uint32_t timerId;
    TimerHandle_t handle;
    otInstance *aInstance;
} otAlarm_t;

otAlarm_t otAlarm = {.timerId = 0, .handle = NULL};

static void otPlatALarm_timerCallback( TimerHandle_t xTimer ) 
{
    if (*(uint32_t *)pvTimerGetTimerID(xTimer) == otAlarm.timerId) {
        otPlatAlarmMilliFired(otAlarm.aInstance);
    }
}

void otPlatALarm_init(otInstance *aInstance) 
{
    otAlarm.handle = xTimerCreate("ot_timer", 1, pdFALSE, (void *)&otAlarm, otPlatALarm_timerCallback);
}

void otPlatAlarmMilliStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt)
{
    if (0 == otAlarm.aInstance) {
        otAlarm.aInstance = aInstance;
    }

    BaseType_t ret;
    uint32_t now = otPlatAlarmMilliGetNow();
    uint32_t timeout = aDt - (now - aT0);

    timeout = timeout == 0? 1: timeout;
    ret = xTimerChangePeriod( otAlarm.handle, pdMS_TO_TICKS(timeout), 0 );
    OT_ASSERT(ret == pdPASS);

    otAlarm.timerId += 1;
    vTimerSetTimerID(otAlarm.handle, &otAlarm.timerId);

    //printf("timer, now = %lu, to = %lu, id = %ld\r\n", now, timeout, otAlarm.timerId);
}

void otPlatAlarmMilliStop(otInstance *aInstance) 
{
    if (xTimerIsTimerActive(otAlarm.handle) == pdTRUE) {
        otAlarm.timerId += 1;
        vTimerSetTimerID(otAlarm.handle, &otAlarm.timerId);
        xTimerStop(otAlarm.handle , 0 );
    }
    //printf("stop\r\n");
}

uint32_t otPlatAlarmMilliGetNow(void) 
{
    uint32_t now = (uint32_t)((long long)xTaskGetTickCount() * 1000/configTICK_RATE_HZ);
    return now;
}
#endif