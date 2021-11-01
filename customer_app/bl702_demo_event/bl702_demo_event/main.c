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
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <vfs.h>
#include <device/vfs_uart.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>

#include <bl_sys.h>
#include <bl_chip.h>
#include <bl_wireless.h>
#include <bl_irq.h>
#include <bl_sec.h>
#include <bl_rtc.h>
#include <bl_uart.h>
#include <bl_gpio.h>
#include <bl_flash.h>
#include <bl_timer.h>
#include <bl_wdt.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <hosal_uart.h>
#include <hal_gpio.h>
#include <hal_hwtimer.h>
#include <hal_pds.h>
#include <hal_tcal.h>

#ifdef CFG_ETHERNET_ENABLE
#include <lwip/netif.h>
#include <lwip/etharp.h>
#include <lwip/udp.h>
#include <lwip/ip.h>
#include <lwip/init.h>
#include <lwip/ip_addr.h>
#include <lwip/tcpip.h>
#include <lwip/dhcp.h>
#include <lwip/netifapi.h>

#include <bl_sys_ota.h>
#include <bl_emac.h>
#include <bl702_glb.h>
#include <bl702_common.h>
#include <bflb_platform.h>
#include <eth_bd.h>
#include <netutils/netutils.h>

#include <netif/ethernet.h>
#endif /* CFG_ETHERNET_ENABLE */
#include <easyflash.h>
#include <libfdt.h>
#include <utils_log.h>
#include <blog.h>
#include <utils_string.h>
#if defined(CONFIG_AUTO_PTS)
#include "bttester.h"
#include "autopts_uart.h"
#endif

#if defined(CFG_BLE_ENABLE)
#include "bluetooth.h"
#include "ble_cli_cmds.h"
#include <hci_driver.h>
#include "ble_lib_api.h"

#if defined(CONFIG_BLE_TP_SERVER)
#include "ble_tp_svc.h"
#endif

#if defined(CONFIG_BT_MESH)
#include "mesh_cli_cmds.h"
#endif
#endif

#if defined(CFG_ZIGBEE_ENABLE)
#include "zb_common.h"
#include "zb_stack_cli.h"
#include "zigbee_app.h"
#include "zb_bdb.h"
#endif
#if defined(CONFIG_ZIGBEE_PROV)
#include "blsync_ble_app.h"
#endif
#if defined(CFG_USE_PSRAM)
#include "bl_psram.h"
#endif /* CFG_USE_PSRAM */

#include "bl_flash.h"

#ifdef CFG_ETHERNET_ENABLE
//extern err_t ethernetif_init(struct netif *netif);
extern err_t eth_init(struct netif *netif);

#define ETH_USE_DHCP 1

#if ETH_USE_DHCP
void lwip_init_netif(void)
{
    ip_addr_t ipaddr, netmask, gw;
    IP4_ADDR(&ipaddr, 0,0,0,0);
    IP4_ADDR(&netmask, 0,0,0,0);
    IP4_ADDR(&gw, 0,0,0,0);
    netif_add(&eth_mac, &ipaddr, &netmask, &gw, NULL, eth_init, ethernet_input);
    //netif_set_default(&eth_mac);
    //netif_set_up(&eth_mac);
    //printf("start dhcp....\r\n");
    //dhcp_start(&eth_mac);
}
#else
void lwip_init_netif(void)
{
    ip_addr_t ipaddr, netmask, gw;

    IP4_ADDR(&gw, 192,168,99,1);
    IP4_ADDR(&ipaddr, 192,168,99,150);
    IP4_ADDR(&netmask, 255,255,255,0);

    netif_add(&eth_mac, &ipaddr, &netmask, &gw, NULL, eth_init, ethernet_input);
    netif_set_default(&eth_mac);
    netif_set_up(&eth_mac);
}
#endif /* ETH_USE_DHCP */
#endif /* CFG_ETHERNET_ENABLE */

HOSAL_UART_DEV_DECL(uart_stdio, 0, 14, 15, 2000000);

extern uint8_t _heap_start;
extern uint8_t _heap_size; // @suppress("Type cannot be resolved")
extern uint8_t _heap2_start;
extern uint8_t _heap2_size; // @suppress("Type cannot be resolved")
static HeapRegion_t xHeapRegions[] =
{
    { &_heap_start,  (unsigned int) &_heap_size}, //set on runtime
    { &_heap2_start, (unsigned int) &_heap2_size },            
    { NULL, 0 }, /* Terminates the array. */
    { NULL, 0 } /* Terminates the array. */
};
#if defined(CFG_USE_PSRAM)
extern uint8_t _heap3_start;
extern uint8_t _heap3_size; // @suppress("Type cannot be resolved")
static HeapRegion_t xHeapRegionsPsram[] =  
{
    { &_heap3_start, (unsigned int) &_heap3_size },
    { NULL, 0 }, /* Terminates the array. */
    { NULL, 0 } /* Terminates the array. */
};
#endif /* CFG_USE_PSRAM */



#define TIME_5MS_IN_32768CYCLE  (164) // (5000/(1000000/32768))
bool pds_start = false;
static void bl702_low_power_config(void);
static void cmd_start_pds(char *buf, int len, int argc, char **argv)
{
    pds_start = true;
	bl702_low_power_config();
}

static void cmd_lowpower_config(char *buf, int len, int argc, char **argv)
{
    bl702_low_power_config();
}

typedef enum {
    TEST_OP_GET32 = 0,
    TEST_OP_GET16,
    TEST_OP_SET32 = 256,
    TEST_OP_SET16,
    TEST_OP_MAX = 0x7FFFFFFF
} test_op_t;
static __attribute__ ((noinline)) uint32_t misaligned_acc_test(void *ptr, test_op_t op, uint32_t v)
{
    uint32_t res = 0;

    switch (op) {
        case TEST_OP_GET32:
            res = *(volatile uint32_t *)ptr;
            break;
        case TEST_OP_GET16:
            res = *(volatile uint16_t *)ptr;
            break;
        case TEST_OP_SET32:
            *(volatile uint32_t *)ptr = v;
            break;
        case TEST_OP_SET16:
            *(volatile uint16_t *)ptr = v;
            break;
        default:
            break;
    }

    return res;
}

//uint32_t bl_timer_now_us(void){return 0;}
void test_align(uint32_t buf)
{
    volatile uint32_t testv[4] = {0};
    uint32_t t1 = 0;
    uint32_t t2 = 0;
    uint32_t t3 = 0;
    uint32_t i = 0;
    volatile uint32_t reg = buf;

    portDISABLE_INTERRUPTS();

    /* test get 32 */
    __asm volatile ("nop":::"memory");
    t1 = *(volatile uint32_t*)0x4000A52C;
    // 3*n + 5
    testv[0] = *(volatile uint32_t *)(reg + 0 * 8 + 1);
    t2 = *(volatile uint32_t*)0x4000A52C;
    // 3*n + 1
    testv[1] = *(volatile uint32_t *)(reg + 1 * 8 + 0);
    t3 = *(volatile uint32_t*)0x4000A52C;
    log_info("testv[0] = %08lx, testv[1] = %08lx\r\n", testv[0], testv[1]);
    log_info("time_us = %ld & %ld ---> %d\r\n", (t2 - t1), (t3 - t2), (t2 - t1)/(t3 - t2));

    /* test get 16 */
    __asm volatile ("nop":::"memory");
    t1 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        testv[0] = misaligned_acc_test((void *)(reg + 2 * 8 + 1), TEST_OP_GET16, 0);
    }
    t2 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        testv[1] = misaligned_acc_test((void *)(reg + 3 * 8 + 0), TEST_OP_GET16, 0);
    }
    t3 = bl_timer_now_us();
    log_info("testv[0] = %08lx, testv[1] = %08lx\r\n", testv[0], testv[1]);
    log_info("time_us = %ld & %ld ---> %d\r\n", (t2 - t1), (t3 - t2), (t2 - t1)/(t3 - t2));

    /* test set 32 */
    __asm volatile ("nop":::"memory");
    t1 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        misaligned_acc_test((void *)(reg + 4 * 8 + 1), TEST_OP_SET32, 0x44332211);
    }
    t2 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        misaligned_acc_test((void *)(reg + 5 * 8 + 0), TEST_OP_SET32, 0x44332211);
    }
    t3 = bl_timer_now_us();
    log_info("time_us = %ld & %ld ---> %d\r\n", (t2 - t1), (t3 - t2), (t2 - t1)/(t3 - t2));

    /* test set 16 */
    __asm volatile ("nop":::"memory");
    t1 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        misaligned_acc_test((void *)(reg + 6 * 8 + 1), TEST_OP_SET16, 0x6655);
    }
    t2 = bl_timer_now_us();
    for (i = 0; i < 1 * 1000 * 1000; i++) {
        misaligned_acc_test((void *)(reg + 7 * 8 + 0), TEST_OP_SET16, 0x6655);
    }
    t3 = bl_timer_now_us();
    log_info("time_us = %ld & %ld ---> %d\r\n", (t2 - t1), (t3 - t2), (t2 - t1)/(t3 - t2));

    portENABLE_INTERRUPTS();
}

void test_misaligned_access(void) __attribute__((optimize("O0")));
void test_misaligned_access(void)// __attribute__((optimize("O0")))
{
#define TEST_V_LEN         (32)
    __attribute__ ((aligned(16))) volatile unsigned char test_vector[TEST_V_LEN] = {0};
    int i = 0;
    volatile uint32_t v = 0;
    uint32_t addr = (uint32_t)test_vector;
    volatile char *pb = (volatile char *)test_vector;
    register float a asm("fa0") = 0.0f;
    register float b asm("fa1") = 0.5f;

    for (i = 0; i < TEST_V_LEN; i ++)
        test_vector[i] = i;

    addr += 1; // offset 1
    __asm volatile ("nop");
    v = *(volatile uint16_t *)(addr); // 0x0201
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0x0201\r\n", __func__, v);
    __asm volatile ("nop");
    *(volatile uint16_t *)(addr) = 0x5aa5;
    __asm volatile ("nop");
    __asm volatile ("nop");
    v = *(volatile uint16_t *)(addr); // 0x5aa5
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0x5aa5\r\n", __func__, v);

    addr += 4; // offset 5
    __asm volatile ("nop");
    v = *(volatile uint32_t *)(addr); //0x08070605
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0x08070605\r\n", __func__, v);
    __asm volatile ("nop");
    *(volatile uint32_t *)(addr) = 0xa5aa55a5;
    __asm volatile ("nop");
    __asm volatile ("nop");
    v = *(volatile uint32_t *)(addr); // 0xa5aa55a5
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0xa5aa55a5\r\n", __func__, v);

    pb[0x11] = 0x00;
    pb[0x12] = 0x00;
    pb[0x13] = 0xc0;
    pb[0x14] = 0x3f;

    addr += 12; // offset 0x11
    __asm volatile ("nop");
    a = *(float *)(addr);
    __asm volatile ("nop");
    v = a * 4.0f; /* should be 6 */
    __asm volatile ("nop");
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0x6\r\n", __func__, v);
    b = v / 12.0f;
    __asm volatile ("nop");
    addr += 4; // offset 0x15
    *(float *)(addr) = b;
    __asm volatile ("nop");
    v = *(volatile uint32_t *)(addr); // 0x3f000000
    __asm volatile ("nop");
    printf("%s: v=%8lx, should be 0x3f000000\r\n", __func__, v);
}

static void cmd_align(char *buf, int len, int argc, char **argv)
{
    char *testbuf = NULL;
    int i = 0;

    log_info("align test start.\r\n");
    test_misaligned_access();

    testbuf = aos_malloc(1024);
    if (!testbuf) {
        log_error("mem error.\r\n");
    }
 
    memset(testbuf, 0xEE, 1024);
    for (i = 0; i < 32; i++) {
        testbuf[i] = i;
    }
    test_align((uint32_t)(testbuf));

    log_buf(testbuf, 64);
    aos_free(testbuf);

    log_info("align test end.\r\n");
}
#if defined(CONFIG_ZIGBEE_PROV)
static void cmd_blsync_blezb_start(void)
{
    blsync_ble_start();
}
#endif

static void cmd_wdt_set(char *buf, int len, int argc, char **argv)
{
    if(argc != 2){
        log_info("Number of parameters error.\r\n");
        return;
    }
    if(strcmp(argv[1], "enable") == 0){
        bl_wdt_init(4000);
    }
    else if(strcmp(argv[1], "disable") == 0){
        bl_wdt_disable();
    }
    else{
        log_info("Second parameter error.\r\n");
    }
}

#if defined(CFG_ZIGBEE_ENABLE)
void zbcli_bdb_local_default_report_cfg(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    uint8_t para_cnt = PRE_CLI_PARAM_NUM;
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM + 1;
    uint8_t ep;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        
        printf("zb_bdb_local_default_report_cfg  <local ep>\r\n"
                       "ep - <uint8_t>\r\n");
        return;
    }
    else
    {   
        get_uint8_from_string(&argv[para_cnt++], &ep);
        zb_bdb_localDefaultReportCfg(ep);   
    }
}

void zbcli_bdb_set_channel_set(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    uint32_t ret;
    uint8_t para_cnt = PRE_CLI_PARAM_NUM;
    uint32_t primaryChannelSet;
    uint32_t secondaryChannelSet;
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM + 2;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        printf("zb_bdb_set_channel_set <srcEp>\r\n"
                "primaryChannelSet - <uint32_t>\r\n"
                "secondaryChannelSet - <uint32_t>\r\n");
        return;
    }
    else
    {   
        get_uint32_from_string(&argv[para_cnt++], &primaryChannelSet);
        get_uint32_from_string(&argv[para_cnt++], &secondaryChannelSet);
        ret = zb_bdb_setChannelSet(primaryChannelSet, secondaryChannelSet);
        if(ret)
        {
            printf("%s fails to set bdbChannelSet with error code(0x%lx)\r\n", __func__, ret);
        }
    }
}

void  zb_bdb_appCb(struct _zbBdbCbMsg *cbMsg)
{
    printf("%s: msgType 0x%x, status 0x%x, bindCnt %d\r\n", __func__, cbMsg->msgType, cbMsg->status, cbMsg->bindCnt);    
}

void zbcli_bdb_start_Fb_Initiator(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    uint8_t para_cnt = PRE_CLI_PARAM_NUM;
    uint8_t srcEp;
    uint8_t commissionMode;
    uint16_t groupId;
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM + 2;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        printf("zb_bdb_start_Fb_Initiator <srcEp,groupId>\r\n"
                "srcEp - <uint8_t>\r\n"
                "groupId - <uint16_t>group id \r\n");
        return;
    }
    else
    {   
        get_uint8_from_string(&argv[para_cnt++], &srcEp);
        get_uint16_from_string(&argv[para_cnt++], &groupId);
        zb_bdb_startFindBindInitiator(srcEp, groupId, zb_bdb_appCb);
    }
}

void zbcli_bdb_fb_start_target(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    uint8_t para_cnt = PRE_CLI_PARAM_NUM;
    uint8_t ep;
    uint16_t identifyTimeInSec;
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM + 2;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        printf("zb_bdb_fb_target <srcEp, identifyTimeInSec>\r\n"
                "srcEp - <uint8_t>\r\n"
                "identifyTimeInSec - <uint16_t>\r\n");
        return;
    }
    else
    {   
        get_uint8_from_string(&argv[para_cnt++], &ep);
        get_uint16_from_string(&argv[para_cnt++], &identifyTimeInSec);
        zb_bdb_startFindBindTarget(ep, identifyTimeInSec, zb_bdb_appCb);
    }
}

void zbcli_bdb_nwk_form(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        printf("zb_bdb_nwk_form <void>\r\n");
        return;
    }
    else
    {   
        zb_bdb_nwkForm(zb_bdb_appCb);
    }
}

void zbcli_bdb_nwk_steer(char* pcWriteBuffer, int xWriteBufferLen, int argc, char** argv)
{
    const uint8_t EXPECTED_PARA_CNT = PRE_CLI_PARAM_NUM;

    if(argc != EXPECTED_PARA_CNT)
    {
        printf("Wrong number of args\r\n");
        printf("zb_bdb_nwk_steer <void>\r\n");
        return;
    }
    else
    {   
        zb_bdb_nwkSteer(zb_bdb_appCb);
    }
}

#endif

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = { 
        {"pds_start", "enable or disable pds", cmd_start_pds},
        {"lw_cfg", "lowpower configuration for active current test", cmd_lowpower_config},
        {"aligntc", "align case test", cmd_align},
        #if defined(CONFIG_ZIGBEE_PROV)
        { "blsync_blezb_start", "start zigbee provisioning via ble", cmd_blsync_blezb_start},
        #endif
        { "wdt_set", "enable or disable pds", cmd_wdt_set},
        #if defined(CFG_ZIGBEE_ENABLE)
        //bdb
        { "zb_bdb_local_default_report_cfg",  "bdb local default report ", zbcli_bdb_local_default_report_cfg},
        { "zb_bdb_set_channel_set",  "bdb set channel set", zbcli_bdb_set_channel_set},
        { "zb_bdb_start_fb_initiator",  "bdb start fb initiator", zbcli_bdb_start_Fb_Initiator},
        { "zb_bdb_start_fb_target",  "bdb start fb target", zbcli_bdb_fb_start_target},
        { "zb_bdb_nwk_form",  "bdb nwk formation", zbcli_bdb_nwk_form},
        { "zb_bdb_nwk_steer",  "bdb nwk steering", zbcli_bdb_nwk_steer},
        #endif
};

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName )
{
    puts("Stack Overflow checked\r\n");
	if(pcTaskName){
		printf("Stack name %s\r\n", pcTaskName);
	}
    while (1) {
        /*empty here*/
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("Memory Allocate Failed. Current left size is %d bytes\r\n"
#if defined(CFG_USE_PSRAM)
        "Current psram left size is %d bytes\r\n"
#endif /*CFG_USE_PSRAM*/
        ,xPortGetFreeHeapSize()
#if defined(CFG_USE_PSRAM)
        ,xPortGetFreeHeapSizePsram()
#endif /*CFG_USE_PSRAM*/
    );
    while (1) {
        /*empty here*/
    }
}

void vApplicationIdleHook(void)
{
    bl_wdt_feed();

    if(!pds_start){
        __asm volatile(
                "   wfi     "
        );
        /*empty*/
    }
}

#if 0
void vApplicationSleep( TickType_t xExpectedIdleTime)
{
    static uint32_t ticks = 0;
    uint32_t cnt = xTaskGetTickCount();
    
    if( (cnt - ticks > 1000) && (xExpectedIdleTime > 20) ){
      ticks = cnt;
      printf("Idle Time: %u\r\n", (unsigned int)xExpectedIdleTime);
      BL702_Delay_MS(1);
      /* Enter pds level 1 for 10ms */
    #if 0
      hal_pds_enter_without_time_compensation(31, 32768/100);
      uint32_t sync = 0;//bl_sys_time_sync();
    #else
    /*Disable mtimer interrrupt*/
    *(volatile uint8_t*)configCLIC_TIMER_ENABLE_ADDRESS = 0;
    uint32_t sync = hal_pds_enter_with_time_compensation(31, 32768*10);
    *(volatile uint8_t*)configCLIC_TIMER_ENABLE_ADDRESS = 1;
    bl_uart_init(0, 14, 15, 255, 255, 2 * 1000 * 1000);
    #endif
    printf("%u ticks compensated\r\n", (unsigned int)sync);
    }
}
#endif

static void bl702_low_power_config(void)
{
    uint8_t i;
    
    // Power off DLL
    GLB_Power_Off_DLL();
    
    // Disable secure engine
    Sec_Eng_Trng_Disable();
    SEC_Eng_Turn_Off_Sec_Ring();

    #if !defined(CFG_ZIGBEE_ENABLE)
    // if zigbee is not enabled, Disable Zigbee clock
    GLB_Set_MAC154_ZIGBEE_CLK(0);
    #endif
    
    // Set all gpio pads to High-Z state
    for(i=0; i<=22; i++){
        // jtag pins
        if((i == 0) || (i == 1) || (i == 2) || (i == 9)){
           //continue;
        }
        
        // uart pins
        if((i == 14) || (i == 15)){
            continue;
        }
        
        GLB_GPIO_Set_HZ(i);
    }
    
    // Set all psram pads to High-Z state
    GLB_Set_Psram_Pad_HZ();
    
    // Gate peripheral clock
    for(i=0; i<=31; i++){
        if(i == BL_AHB_SLAVE1_GLB){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_MIX){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_EFUSE){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_L1C){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_SFC){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_PDS_HBN_AON_HBNRAM){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_UART0){
            continue;
        }
        
        if(i == BL_AHB_SLAVE1_TMR){
            continue;
        }
        
        GLB_AHB_Slave1_Clock_Gate(1, i);
    }
}

void bl_pds_restore(void)
{
    bl_uart_init(0, 14, 15, 255, 255, 2 * 1000 * 1000);
    bl_uart_int_enable(0);
#ifndef CFG_USB_CDC_ENABLE
	//power off Dll
    GLB_Power_Off_DLL();
#endif
#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_restore(void);
    usb_cdc_restore();
#endif
    
#if defined(CFG_BLE_PDS)
    ble_controller_sleep_restore();
   // bl_sec_init();
#endif
}

//For test
extern int32_t rwip_get_sleep_stat_cnt(void);
//end
#if ( configUSE_TICKLESS_IDLE != 0 )
#if defined(CFG_BLE_PDS)
extern bool le_check_valid_scan(void);
extern bool le_check_valid_conn(void);
//Allocate retention memory
void *bl_alloc_retmem(size_t xWantedSize )
{
    return pvPortMalloc(xWantedSize);    
}

void vApplicationSleep( TickType_t xExpectedIdleTime_ms)
{
    int32_t bleSleepDuration_32768cycles = 0;
    int32_t expectedIdleTime_32768cycles = 0;
    eSleepModeStatus eSleepStatus;
    bool freertos_max_idle = false;
    #if (LE_PDS_FLASH)
    uint8_t ioMode;
    uint8_t contRead; 
    #endif

    if (pds_start == 0 || le_check_valid_scan())
        return;

    if(xExpectedIdleTime_ms + xTaskGetTickCount() == portMAX_DELAY){
        freertos_max_idle = true;
    }else{   
        xExpectedIdleTime_ms -= 1;
        expectedIdleTime_32768cycles = 32768 * xExpectedIdleTime_ms / 1000;
    }

    if((!freertos_max_idle)&&(expectedIdleTime_32768cycles < TIME_5MS_IN_32768CYCLE)){
        return;
    }
        
    eSleepStatus = eTaskConfirmSleepModeStatus();
    if(eSleepStatus == eAbortSleep || ble_controller_sleep_is_ongoing())
    {
        return;
    }

    bleSleepDuration_32768cycles = ble_controller_sleep();

    if(bleSleepDuration_32768cycles < TIME_5MS_IN_32768CYCLE)
    {
        return;
    }
    else
    { 
        printf("Sleep_cycles=%ld,state_cnt=%d\r\n", bleSleepDuration_32768cycles, rwip_get_sleep_stat_cnt());
        uint8_t reduceSleepTime;
        SPI_Flash_Cfg_Type *flashCfg = bl_flash_get_flashCfg();
        uint8_t ioMode =  flashCfg->ioMode & 0xF;
        uint8_t contRead = flashCfg->cReadSupport;
        uint8_t cpuClk = GLB_Get_Root_CLK_Sel();
        if(ioMode == 4 && contRead == 1 && cpuClk == GLB_ROOT_CLK_XTAL)
        {
           reduceSleepTime = 100;
        }
        else if(ioMode == 1 && contRead == 0 && cpuClk == GLB_ROOT_CLK_XTAL)
        {
           reduceSleepTime = 130;
        }
        else
        {
           reduceSleepTime = 130;
        }
        printf("reduceSleepTime=%d\r\n",reduceSleepTime);
        if(eSleepStatus == eStandardSleep && ((!freertos_max_idle) && (expectedIdleTime_32768cycles < bleSleepDuration_32768cycles)))
        {
           hal_pds_enter_with_time_compensation(31, expectedIdleTime_32768cycles - reduceSleepTime);
        }
        else
        {
           hal_pds_enter_with_time_compensation(31, bleSleepDuration_32768cycles - reduceSleepTime);
        }
        
        bl_timer_init();
        bl_pds_restore();
    }
}
#elif defined(CFG_ZIGBEE_PDS)
void vApplicationSleep( TickType_t xExpectedIdleTime )
{
    uint32_t xActualIdleTime = 0;
    eSleepModeStatus eSleepStatus;
    uint32_t sleepTime;
    uint32_t sleepCycles;
    
#define PDS_TOLERANCE_TIME_MS    5
    
    if(pds_start == 0){
        return;
    }
    
#if defined(CFG_ZIGBEE_PDS)
    if(!zb_stackIdle())
    {
        return;
    }
    xActualIdleTime = zb_zedGetIdleDuration() / 1000;
#endif
    
    if(xActualIdleTime <= PDS_TOLERANCE_TIME_MS){
        return;
    }
    
    eSleepStatus = eTaskConfirmSleepModeStatus();
    if(eSleepStatus == eAbortSleep){
        return;
    }else if(eSleepStatus == eStandardSleep){
        if(xExpectedIdleTime <= PDS_TOLERANCE_TIME_MS){
            return;
        }else if(xExpectedIdleTime < xActualIdleTime){
            sleepTime = xExpectedIdleTime - PDS_TOLERANCE_TIME_MS;
        }else{
            sleepTime = xActualIdleTime - PDS_TOLERANCE_TIME_MS;
        }
    }else{
        sleepTime = xActualIdleTime - PDS_TOLERANCE_TIME_MS;
    }
    
    printf("[%lu] will sleep: %lu ms\r\n", (uint32_t)bl_rtc_get_timestamp_ms(), sleepTime);
    
#if defined(CFG_ZIGBEE_PDS)
    zb_zedStoreRegs();
    zb_zedStoreTime();
#endif
    
    sleepCycles = (uint64_t)32768 * sleepTime / 1000;
    sleepTime = hal_pds_enter_with_time_compensation(31, sleepCycles);
    bl_pds_restore();
    
#if defined(CFG_ZIGBEE_PDS)
    zb_zedRestoreTime(sleepTime * 1000);
    zb_zedRestoreRegs();
#endif
    
    printf("[%lu] actually sleep: %lu ms\r\n", (uint32_t)bl_rtc_get_timestamp_ms(), sleepTime);
}
#else
void vApplicationSleep( TickType_t xExpectedIdleTime )
{
    
}
#endif
#endif

#if ( configUSE_TICK_HOOK != 0 )
void vApplicationTickHook( void )
{
#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_monitor(void);
    usb_cdc_monitor();
#endif
#if defined(CFG_ZIGBEE_ENABLE)
	extern void ZB_MONITOR(void);
	ZB_MONITOR();
#endif
}
#endif

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    //static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
    static StackType_t uxIdleTaskStack[256];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    //*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE; 
    *pulIdleTaskStackSize = 256;//size 256 words is For ble pds mode, otherwise stack overflow of idle task will happen.
}

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void user_vAssertCalled(void) __attribute__ ((weak, alias ("vAssertCalled")));
void vAssertCalled(void)
{
    taskDISABLE_INTERRUPTS();

    abort();
}


static void _cli_init()
{
    /*Put CLI which needs to be init here*/
#if defined(CFG_EFLASH_LOADER_ENABLE)
    extern int helper_eflash_loader_cli_init(void);
    helper_eflash_loader_cli_init();
#endif

#if defined(CFG_RFPHY_CLI_ENABLE)
    extern int helper_rfphy_cli_init(void);
    helper_rfphy_cli_init();
#endif
#ifdef CFG_ETHERNET_ENABLE
    /*Put CLI which needs to be init here*/
    network_netutils_iperf_cli_register();
    network_netutils_ping_cli_register();
    bl_sys_ota_cli_init();
#endif /* CFG_ETHERNET_ENABLE */
}

static int get_dts_addr(const char *name, uint32_t *start, uint32_t *off)
{
    uint32_t addr = hal_board_get_factory_addr();
    const void *fdt = (const void *)addr;
    uint32_t offset;

    if (!name || !start || !off) {
        return -1;
    }

    offset = fdt_subnode_offset(fdt, 0, name);
    if (offset <= 0) {
       log_error("%s NULL.\r\n", name);
       return -1;
    }

    *start = (uint32_t)fdt;
    *off = offset;

    return 0;
}

#if defined(CFG_BLE_ENABLE)
void ble_init(void)
{
	extern void ble_stack_start(void);
	ble_stack_start();
}
#endif

#if defined(CFG_ZIGBEE_ENABLE)
void zigbee_init(void)
{
    zbRet_t status;
    status = zb_stackInit();
    if (status != ZB_SUCC)
    {
        printf("BL Zbstack Init fail : 0x%08x\r\n", status);
        //ASSERT(false);
    }
    else
    {
        printf("BL Zbstack Init Success\r\n");
    }

    zb_cli_register();

    register_zb_cb();
    
    zb_app_startup();

    zb_bdb_init();
}
#endif

static void aos_loop_proc(void *pvParameters)
{
    int fd_console;
    uint32_t fdt = 0, offset = 0;

    vfs_init();
    vfs_device_init();

    /* uart */
    const char *uart_node[] = {
        "uart@4000A000",
        "uart@4000A100",
    };

    if (0 == get_dts_addr("uart", &fdt, &offset)) {
        vfs_uart_init(fdt, offset, uart_node, 2);
    }

#ifndef CFG_ETHERNET_ENABLE
    /* gpio */
    if (0 == get_dts_addr("gpio", &fdt, &offset)) {
        hal_gpio_init_from_dts(fdt, offset);
    }
#endif /* CFG_ETHERNET_ENABLE */

    aos_loop_init();

    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        printf("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void*)0x12345678);
        _cli_init();
    }

#if defined(CFG_USB_CDC_ENABLE)
    extern void usb_cdc_start(int fd_console);
    usb_cdc_start(fd_console);
#endif

    hal_hwtimer_init();

#if defined(CFG_BLE_ENABLE)
    #if defined(CONFIG_AUTO_PTS)
    pts_uart_init(1,115200,8,1,0,0);
    // Initialize BLE controller
    ble_controller_init(configMAX_PRIORITIES - 1);
    extern int hci_driver_init(void);
    // Initialize BLE Host stack
    hci_driver_init();

    tester_send(BTP_SERVICE_ID_CORE, CORE_EV_IUT_READY, BTP_INDEX_NONE,
            NULL, 0);
    #else
    ble_init();
    #endif
#endif

#if defined(CFG_ZIGBEE_ENABLE)
    zigbee_init();
#endif

    aos_loop_run();

    puts("------------------------------------------\r\n");
    puts("+++++++++Critical Exit From Loop++++++++++\r\n");
    puts("******************************************\r\n");
    vTaskDelete(NULL);
}

#if 0
static void proc_hellow_entry(void *pvParameters)
{
    vTaskDelay(500);

    while (1) {
        printf("%s: RISC-V rv32imafc\r\n", __func__);
        vTaskDelay(10000);
    }
    vTaskDelete(NULL);
}
#endif

static void _dump_boot_info(void)
{
    char chip_feature[40];
    const char *banner;

    puts("Booting BL702 Chip...\r\n");

    /*Display Banner*/
    if (0 == bl_chip_banner(&banner)) {
//        puts(banner);
    }
    puts("\r\n");
    /*Chip Feature list*/
    puts("\r\n");
    puts("------------------------------------------------------------\r\n");
    puts("RISC-V Core Feature:");
    bl_chip_info(chip_feature);
    puts(chip_feature);
    puts("\r\n");

    puts("Build Version: ");
    puts(BL_SDK_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

    puts("Std BSP Driver Version: ");
    puts(BL_SDK_STDDRV_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

    puts("Std BSP Common Version: ");
    puts(BL_SDK_STDCOM_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

    puts("RF Version: ");
    puts(BL_SDK_RF_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

#if defined(CFG_BLE_ENABLE)
    puts("BLE Controller LIB Version: ");
    puts(ble_controller_get_lib_ver());
    puts("\r\n");
#endif

#if defined(CFG_ZIGBEE_ENABLE)
    puts("Zigbee LIB Version: ");
    puts(zb_getLibVer());
    puts("\r\n");
#endif

    puts("Build Date: ");
    puts(__DATE__);
    puts("\r\n");
    puts("Build Time: ");
    puts(__TIME__);
    puts("\r\n");
    puts("------------------------------------------------------------\r\n");

}

static void system_init(void)
{
    blog_init();
    bl_irq_init();
#if defined(CFG_ETHERNET_ENABLE) || defined(CFG_BLE_ENABLE) || defined(CFG_ZIGBEE_ENABLE)
	bl_sec_init();
#endif /*CFG_ETHERNET_ENABLE*/
    bl_rtc_init();
    hal_boot2_init();

    /* board config is set after system is init*/
    hal_board_cfg(0);
    hal_pds_init();
    hal_tcal_init();

    //bl_wdt_init(4000);

#if defined(CFG_USE_PSRAM)
    bl_psram_init();
    vPortDefineHeapRegionsPsram(xHeapRegionsPsram);
#endif /*CFG_USE_PSRAM*/
}

static void system_thread_init()
{
    /*nothing here*/
}

void rf_reset_done_callback(void)
{
    hal_tcal_restart();
}

void setup_heap()
{
    bl_sys_em_config();

    // Invoked during system boot via start.S
    vPortDefineHeapRegions(xHeapRegions);
}

void bl702_main()
{
    static StackType_t aos_loop_proc_stack[1024];
    static StaticTask_t aos_loop_proc_task;
    //static StackType_t proc_hellow_stack[512];
    //static StaticTask_t proc_hellow_task;

    bl_sys_early_init();
    
    /*Init UART In the first place*/
    hosal_uart_init(&uart_stdio);
    puts("Starting bl702 now....\r\n");

    bl_sys_init();

    _dump_boot_info();

    printf("Heap %u@%p, %u@%p"
#if defined(CFG_USE_PSRAM)
            ", %u@%p"
#endif /*CFG_USE_PSRAM*/
            "\r\n",
            (unsigned int)&_heap_size, &_heap_start,
            (unsigned int)&_heap2_size, &_heap2_start
#if defined(CFG_USE_PSRAM)
            ,(unsigned int)&_heap3_size, &_heap3_start
#endif /*CFG_USE_PSRAM*/
    );

    system_init();
    system_thread_init();

    //puts("[OS] Starting proc_hellow_entry task...\r\n");
    //xTaskCreateStatic(proc_hellow_entry, (char*)"hellow", sizeof(proc_hellow_stack)/4, NULL, 15, proc_hellow_stack, &proc_hellow_task);
    puts("[OS] Starting aos_loop_proc task...\r\n");

#if defined(CONFIG_AUTO_PTS)
    tester_init();
#endif
    xTaskCreateStatic(aos_loop_proc, (char*)"event_loop", sizeof(aos_loop_proc_stack)/4, NULL, 15, aos_loop_proc_stack, &aos_loop_proc_task);

#ifdef CFG_ETHERNET_ENABLE
    tcpip_init(NULL, NULL);
    lwip_init_netif();
#endif /*CFG_ETHERNET_ENABLE*/
    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
