/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if defined(CFG_ZIGBEE_PDS)
#include <FreeRTOS.h>
#include <task.h>
#include <bl_irq.h>
#include <bl_rtc.h>
#include <hosal_uart.h>

#include "hal_pds.h"
#include "zb_common.h"

extern bool pds_start;
static void bl_pds_restore(void)
{
    HOSAL_UART_DEV_DECL(uart_stdio, 0, 14, 15, 2000000);
    hosal_uart_init(&uart_stdio);

#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_restore(void);
    usb_cdc_restore();
#endif
}

#if ( configUSE_TICKLESS_IDLE != 0 )
void vApplicationSleep( TickType_t xExpectedIdleTime )
{
    uint32_t xActualIdleTime = 0;
    eSleepModeStatus eSleepStatus;
    uint32_t sleepTime;
    uint32_t sleepCycles;
    
#define PDS_TOLERANCE_TIME_MS    5
//in driver, it takes (sleep_cycles-PDS_WARMUP_LATENCY_CNT) as sleep cycles. Make sure pds sleep for at least 1 ms(about 31cycles).
#define PDS_MIN_TIME_MS    (PDS_WARMUP_LATENCY_CNT + 30 + 31)/31 
    
    if(pds_start == 0){
        return;
    }

    eSleepStatus = eTaskConfirmSleepModeStatus();
    if(eSleepStatus == eAbortSleep){
        printf("eSleepStatus == eAbortSleep\r\n");
        return;
    }else if(eSleepStatus == eStandardSleep){
        if(xExpectedIdleTime <= PDS_TOLERANCE_TIME_MS + PDS_MIN_TIME_MS){
            return;
        }
    }
    
    if(!zb_stackIdle())
    {
        return;
    }

    xActualIdleTime = zb_zsedGetIdleDuration() / 1000;

    if(xActualIdleTime <= PDS_TOLERANCE_TIME_MS + PDS_MIN_TIME_MS){
        return;
    }
    
   if(eSleepStatus == eStandardSleep){
        if(xExpectedIdleTime < xActualIdleTime){
            sleepTime = xExpectedIdleTime - PDS_TOLERANCE_TIME_MS;
        }else{
            sleepTime = xActualIdleTime - PDS_TOLERANCE_TIME_MS;
        }
    }else{
        sleepTime = xActualIdleTime - PDS_TOLERANCE_TIME_MS;
    }

    bl_irq_disable(M154_IRQn);
    printf("[%lu] will sleep: %lu ms\r\n", (uint32_t)bl_rtc_get_timestamp_ms(), sleepTime);
    
    zb_zsedStoreRegs();
    zb_zsedStoreTime();

    sleepCycles = (uint64_t)32768 * sleepTime / 1000;
    sleepTime = hal_pds_enter_with_time_compensation(31, sleepCycles);
    bl_pds_restore();
      
    zb_zsedRestoreRegs();
    zb_zsedRestoreTime(sleepTime * 1000);
    
    printf("[%lu] actually sleep: %lu ms\r\n", (uint32_t)bl_rtc_get_timestamp_ms(), sleepTime);
}
#endif
#endif//#if defined(CFG_ZIGBEE_PDS)