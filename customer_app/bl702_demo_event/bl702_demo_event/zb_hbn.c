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
#if defined(CFG_ZIGBEE_HBN)
#include <FreeRTOS.h>
#include <task.h>
#include <bl_sys.h>
#include <bl_irq.h>
#include <bl_rtc.h>
#include <bl_timer.h>
#include <hosal_uart.h>

#include "zb_aps.h"
#include "zigbee_app.h"
#include "zcl_pollCtrl.h"
#include "bl_hbn.h"
#include "lmac154.h"

extern bool hbn_start;
ATTR_HBN_DATA_SECTION struct _zsedNwkInfo zsedNwkInfo;
ATTR_HBN_DATA_SECTION uint8_t dataReq[10];
ATTR_HBN_NOINIT_SECTION struct _zbRxPacket rxPktStoredInHbnRam;
#define RX_DATA_WAIT_DUR_US 7000
#define ZB_HBN_PRINT 0
bool doSysReset = false;
uint32_t rxMaxTargetTime = 0;
#if ZB_HBN_PRINT == 0
#define printf(...)   (void)0
#endif
static void bl_zb_send_data_req(void)
{
    //little endian
    //data Reqeust:frame control, sequence number, destination pan id, destination address, source address, command frame id.
    dataReq[2] = zsedNwkInfo.macSeqNum;
    zsedNwkInfo.macSeqNum++;
    lmac154_triggerTx(dataReq, 10, false); 
}

void lmac154_txDoneEvent(lmac154_tx_status_t tx_status)
{
    printf("%s, (STATUS: %d)\r\n", __func__, tx_status);
    if(tx_status != LMAC154_TX_STATUS_TX_FINISHED)
    {
        printf("enter hbn\r\n");
        zb_store_tx_power();
        //(zsedNwkInfo.longPollItvlInQuarterSeconds*1000)/4
        bl_hbn_enter_with_fastboot(zsedNwkInfo.sleepCycles);
    }
    else
        lmac154_enableRx();
}

void lmac154_ackEvent(uint8_t ack_received, uint8_t frame_pending, uint8_t seq_num)
{ 
    printf("%s, ack_received(%d), frame_pending(%d), seq_num(%d)\r\n", __func__ ,ack_received, frame_pending, seq_num);
    if(!ack_received || !frame_pending)
    {
        //#1:mac ack is received, frame pending is 0
        //#2:mac ack is not received(lmac has done re-transmittion)
        //In above two case, enter hbn.
        lmac154_disableRx();
        zb_store_tx_power();
        printf("enter into hbn\r\n");
        bl_hbn_enter_with_fastboot(zsedNwkInfo.sleepCycles);
    }
    else
    {
        rxMaxTargetTime = bl_timer_get_current_time() + RX_DATA_WAIT_DUR_US;
    }
}

void lmac154_hwAutoTxAckDoneEvent(void)
{
    printf("%s\r\n", __func__);
    if(doSysReset)
    {
        doSysReset = false;
        lmac154_disableRx();
        printf("do reset\r\n");
        bl_sys_rstinfo_clr();
        GLB_SW_POR_Reset();
    }  
}

void lmac154_rxDoneEvent(uint8_t *rx_buf, uint8_t rx_len, uint8_t crc_fail)
{
    uint8_t dstAddrMode;
    uint16_t dstAddr;
    printf("%s, rx_len(%d), crc_fail(%d)\r\n", __func__, rx_len, crc_fail);

    rxMaxTargetTime = 0;
    if(crc_fail || !rx_buf || !rx_len)
    {
        zb_store_tx_power();
        bl_hbn_enter_with_fastboot(zsedNwkInfo.sleepCycles);
    }

    dstAddrMode = (rx_buf[1] & 0xc0)>>6;
    dstAddr = (rx_buf[6] << 8) | rx_buf[5];

    if(dstAddrMode == ZB_APS_ADDR_MODE_SHORT && dstAddr == zsedNwkInfo.srcShortAddr)
    {
        rxPktStoredInHbnRam.len = rx_len;
        memcpy(rxPktStoredInHbnRam.data, rx_buf, rx_len);
        lmac154_readRxCrc(rxPktStoredInHbnRam.fcs);
        rxPktStoredInHbnRam.freqOffset = lmac154_getFrequencyOffset();
        rxPktStoredInHbnRam.rssi = lmac154_getRSSI();
        rxPktStoredInHbnRam.sfdCorr = lmac154_getSFDCorrelation();
        doSysReset = true;
    }
    else
    {
        printf("No data from parent received\r\n");
        if(!doSysReset)
         {
            zb_store_tx_power();
            bl_hbn_enter_with_fastboot(zsedNwkInfo.sleepCycles);
         }
    }
}

void bl_hbn_fastboot_done_callback(void)
{
    lmac154_isr_t trigger_event;
    #if ZB_HBN_PRINT == 1
    HOSAL_UART_DEV_DECL(uart_stdio, 0, 14, 15, 2000000);
    hosal_uart_init(&uart_stdio);
    #endif
    
    printf("HBN wakeup\r\n");
    
    bl_timer_init();
    lmac154_init();
    bl_irq_enable(M154_IRQn);
    lmac154_setChannel(zsedNwkInfo.currChnl-11);
    lmac154_setPanId(zsedNwkInfo.panId);
    lmac154_setShortAddr(zsedNwkInfo.srcShortAddr);
    trigger_event = lmac154_getInterruptHandler();
    bl_zb_send_data_req();

    while(1){
        trigger_event();
        if(rxMaxTargetTime)
        {
            if(bl_timer_get_current_time() > rxMaxTargetTime)
            {
                printf("rx data timeout,enter into hbn\r\n");
                zb_store_tx_power();
                bl_hbn_enter_with_fastboot(zsedNwkInfo.sleepCycles);
            }
        }
        else
        {
            __WFI();
            bl_irq_pending_clear(M154_IRQn);
        }
    }
}

#if ( configUSE_TICKLESS_IDLE != 0 )
void vApplicationSleep( TickType_t xExpectedIdleTime )
{
    uint32_t xActualIdleTime = 0;
    eSleepModeStatus eSleepStatus;
    uint32_t sleepCycles;
    uint16_t shortIntvlInQuarterSeconds;
    uint32_t longPollItvlInQuarterSeconds;
    
    if(hbn_start == 0){
        return;
    }

    eSleepStatus = eTaskConfirmSleepModeStatus();
    if(eSleepStatus == eAbortSleep){
        printf("eSleepStatus == eAbortSleep\r\n");
        return;
    }
    
    if(!zb_stackIdle())
    {
        return;
    }
    zcl_pollCtrlGetShortPollIntvl(&shortIntvlInQuarterSeconds);
    xActualIdleTime = zb_zsedGetIdleDuration() / 1000;//ms
    
    if(xActualIdleTime < (shortIntvlInQuarterSeconds * 250))
        return;

    if(zb_isJoined())
    {
        zsedNwkInfo.currChnl = zb_getChannel();
        zsedNwkInfo.macSeqNum = zb_getMacSeqNum();
        zsedNwkInfo.panId = zb_getPanId();
        zsedNwkInfo.srcShortAddr = zb_getShortAddr();
        zsedNwkInfo.parentShortAddr = zb_getParentShortAddr();
        zcl_pollCtrlGetLongPollIntvl(&longPollItvlInQuarterSeconds);
        zsedNwkInfo.sleepCycles = (uint64_t)(longPollItvlInQuarterSeconds)*32768/4;
        dataReq[0] = 0x63;
        dataReq[1] = 0x88;
        dataReq[2] = zsedNwkInfo.macSeqNum;
        dataReq[3] = (uint8_t)zsedNwkInfo.panId;
        dataReq[4] = (uint8_t)(zsedNwkInfo.panId >> 8);
        dataReq[5] = (uint8_t)zsedNwkInfo.parentShortAddr;
        dataReq[6] = (uint8_t)(zsedNwkInfo.parentShortAddr >> 8);
        dataReq[7] = (uint8_t)zsedNwkInfo.srcShortAddr;
        dataReq[8] = (uint8_t)(zsedNwkInfo.srcShortAddr >> 8);
        dataReq[9] = 4;
    }
    
   if(eSleepStatus == eStandardSleep){
        if(xExpectedIdleTime < xActualIdleTime){
            sleepCycles = (uint64_t)xExpectedIdleTime * 32768 / 1000;
        }else{
            sleepCycles = (uint64_t)xActualIdleTime *32768 / 1000;
        }
    }else{
        sleepCycles = (uint64_t)xActualIdleTime *32768 / 1000;
    }
    
    bl_irq_disable(M154_IRQn);

    printf("[%lu] will sleep: %lu cycles\r\n", (uint32_t)bl_rtc_get_timestamp_ms(), sleepCycles);
    zb_store_tx_power();
    bl_hbn_enter_with_fastboot(sleepCycles);
}
#endif
#endif//#if defined(CFG_ZIGBEE_HBN)