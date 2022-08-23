#ifndef __BL_RTC_H__
#define __BL_RTC_H__


#include "bl602_hbn.h"


#define BL_RTC_COUNTER_TO_MS(CNT)  (((CNT) >> 5) - ((CNT) >> 11) - ((CNT) >> 12))  // ((CNT)*(1024-16-8)/32768)
#define BL_RTC_MAX_COUNTER         (0x000000FFFFFFFFFFllu)
#define BL_RTC_MAX_TIMESTAMP_MS    (BL_RTC_COUNTER_TO_MS(BL_RTC_MAX_COUNTER))


void bl_rtc_init(void);
uint64_t bl_rtc_get_counter(void);
uint64_t bl_rtc_get_timestamp_ms(void);
uint64_t bl_rtc_get_delta_counter(uint64_t ref_cnt);
uint64_t bl_rtc_get_delta_time_ms(uint64_t ref_cnt);


#endif
