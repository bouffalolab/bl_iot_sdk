#ifndef __JOYLINK_TIMER_H__
#define __JOYLINK_TIMER_H__

#include <stddef.h>
#include <sys/times.h>
#include "joylink_stdint.h"


typedef struct{
    uint32_t    year;         /* 年份，其值等于实际年份减去1900 */
    uint8_t     month;      /* 月份(从一月开始，0代一月)，取值区间为[0,11]*/
    uint8_t     week;         /*星期，取值区间为[0,6]，其中0代表星期天，1代表星期一 ，以此内推*/
    uint8_t     day;           /* 一个月中的日期，取值区间为[1,31]      */
    uint8_t     hour;        /* 时，取值区间为[0 ,23]        */
    uint8_t     minute;   /* 分，取值区间为 [0 ,59]        */
    uint8_t     second;   /* 秒，取值区间为[0,59]        */
    uint32_t    timestamp; /*秒，时间戳 */
}jl_time_t;

typedef struct {
    uint32_t second;
    uint32_t ms;
} jl_time_stamp_t;

/**
 * set utc timestamp
 * @param[in] time_stamp_ms : timestamp(ms)
 * @return: success or fail
 *
 */
int32_t jl_set_UTCtime(jl_time_stamp_t ts);

/**
* @brief get timestamp(ms)
* @param none
* @return time ms
*/
int jl_get_time_msec(jl_time_stamp_t *ts);

/**
 * get timestamp(ms)
 *
 * @return: UTC Second
 *
 */
uint32_t jl_get_time_second(uint32_t *jl_time);

/**
 * get time string
 *
 * @out param: 
 * @return: success or fail
 *
 */
int jl_get_time(jl_time_t *jl_time);

/**
 * get time string
 *
 * @out param: "year-month-day hour:minute:second"
 * @return: success or fail
 *
 */
char *jl_get_time_str(void);

/**
 * get os time
 *
 * @out param: none
 * @return: sys time ticks ms since sys start
*/

uint32_t jl_get_os_time(void);

#endif



