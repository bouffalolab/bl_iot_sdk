#include "hal_pds.h"
#include "bl_rtc.h"


void hal_pds_init(void)
{
    bl_pds_init();
    
#if 0  /* RTC is started by bl_rtc_init() in bl_rtc.c */
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
    uint64_t rtcRefCnt;
    uint32_t actualSleepDuration_ms;
    uint32_t mtimerClkCfg;
    uint32_t mtimerClkCycles;
    uint32_t ulCurrentTimeHigh, ulCurrentTimeLow;
    volatile uint32_t * const pulTimeHigh = ( volatile uint32_t * const ) ( configCLINT_BASE_ADDRESS + 0xBFFC );
    volatile uint32_t * const pulTimeLow = ( volatile uint32_t * const ) ( configCLINT_BASE_ADDRESS + 0xBFF8 );
    
    extern volatile uint64_t * const pullMachineTimerCompareRegister;
    extern void vPortSetupTimerInterrupt(void);
    
    mtimerClkCfg = BL_RD_REG(GLB_BASE, GLB_CPU_CLK_CFG);  // store mtimer clock setting
    
    *pullMachineTimerCompareRegister = -1;  // avoid mtimer interrupt pending
    *(volatile uint8_t *)configCLIC_TIMER_ENABLE_ADDRESS = 0;  // disable mtimer interrrupt
    
    do
    {
        ulCurrentTimeHigh = *pulTimeHigh;
        ulCurrentTimeLow = *pulTimeLow;
    } while( ulCurrentTimeHigh != *pulTimeHigh );
    
    rtcRefCnt = bl_rtc_get_counter();
    
    bl_pds_enter(pdsLevel, pdsSleepCycles);
    
    actualSleepDuration_ms = (uint32_t)bl_rtc_get_delta_time_ms(rtcRefCnt);
    
    mtimerClkCycles = actualSleepDuration_ms * 1000 * 4;
    ulCurrentTimeLow += mtimerClkCycles;
    if(ulCurrentTimeLow < mtimerClkCycles){
        ulCurrentTimeHigh++;
    }
    
    BL_WR_REG(GLB_BASE, GLB_CPU_CLK_CFG, mtimerClkCfg);  // restore mtimer clock setting
    
    *pullMachineTimerCompareRegister = -1;
    *(volatile uint8_t *)configCLIC_TIMER_ENABLE_ADDRESS = 0;
    
    *pulTimeLow = 0;
    *pulTimeHigh = ulCurrentTimeHigh;
    *pulTimeLow = ulCurrentTimeLow;
    
    vPortSetupTimerInterrupt();
    *(volatile uint8_t *)configCLIC_TIMER_ENABLE_ADDRESS = 1;
    
    vTaskStepTick(actualSleepDuration_ms);
    
    return actualSleepDuration_ms;
}
