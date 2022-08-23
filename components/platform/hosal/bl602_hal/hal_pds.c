#include "hal_pds.h"
#include "bl602_glb.h"
#include "bl602_common.h"

#include <utils_list.h>
#include <blog.h>


void hal_pds_init(void)
{
    bl_pds_init();
    
#if 0  /* RTC is started by bl_rtc_init() in bl_rtc.c */
    HBN_Clear_RTC_Counter();
    HBN_Enable_RTC_Counter();
#endif
}

void hal_pds_fastboot_cfg(uint32_t addr)
{
    bl_pds_fastboot_cfg(addr);
}

void hal_pds_enter_without_time_compensation(uint32_t pdsLevel, uint32_t pdsSleepCycles)
{
    bl_pds_enter(pdsLevel, pdsSleepCycles);
}

uint32_t hal_pds_enter_with_time_compensation(uint32_t pdsLevel, uint32_t pdsSleepCycles)
{
    uint32_t rtcLowBeforeSleep, rtcHighBeforeSleep;
    uint32_t rtcLowAfterSleep, rtcHighAfterSleep;
    uint32_t actualSleepDuration_32768cycles;
    uint32_t actualSleepDuration_ms;
    
    HBN_Get_RTC_Timer_Val(&rtcLowBeforeSleep, &rtcHighBeforeSleep);
    
    bl_pds_enter(pdsLevel, pdsSleepCycles);
    
    HBN_Get_RTC_Timer_Val(&rtcLowAfterSleep, &rtcHighAfterSleep);
    
    CHECK_PARAM((rtcHighAfterSleep - rtcHighBeforeSleep) <= 1); // make sure sleep less than 1 hour (2^32 us > 1 hour)
    
    actualSleepDuration_32768cycles = (rtcLowAfterSleep - rtcLowBeforeSleep);
    
    actualSleepDuration_ms = (actualSleepDuration_32768cycles>>5)-(actualSleepDuration_32768cycles>>11)-(actualSleepDuration_32768cycles>>12);
    
    vTaskStepTick(actualSleepDuration_ms);
    
    return actualSleepDuration_ms;
}
