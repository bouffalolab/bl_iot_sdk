#ifndef __BL_RTC_H__
#define __BL_RTC_H__


#include "bl702_hbn.h"


#define BL_RTC_COUNTER_TO_MS(CNT)  ((uint64_t)(CNT)*1000/32768) // ((CNT)*(1024-16-8)/32768)
#define BL_RTC_MAX_COUNTER         (0x000000FFFFFFFFFFllu)
#define BL_RTC_MAX_TIMESTAMP_MS    (BL_RTC_COUNTER_TO_MS(BL_RTC_MAX_COUNTER))


void bl_rtc_init(void);
uint64_t bl_rtc_get_counter(void);
uint64_t bl_rtc_get_timestamp_ms(void);
uint64_t bl_rtc_get_delta_counter(uint64_t ref_cnt);
uint64_t bl_rtc_get_delta_time_ms(uint64_t ref_cnt);


#endif
