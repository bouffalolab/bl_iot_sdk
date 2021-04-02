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
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>

#include <bl602_glb.h>
#include <bl602_hbn.h>

#include <bl_sys.h>
#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_wifi.h>
#include <bl_sec.h>
#include <bl_cks.h>
#include <bl_irq.h>
#include <bl_timer.h>
#include <bl_dma.h>
#include <bl_gpio_cli.h>
#include <bl_wdt_cli.h>
#include <hal_uart.h>
#include <hal_sys.h>
#include <hal_gpio.h>
#include <hal_hbn.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <hal_button.h>
#include <looprt.h>
#include <loopset.h>
#include <bl_sys_time.h>
#include <bl_romfs.h>
#include <fdt.h>

#include <utils_log.h>
#include <libfdt.h>
#include <blog.h>
#include <hal_spi.h>
#include "demo.h"


#define TASK_PRIORITY_FW            ( 30 )
#define mainHELLO_TASK_PRIORITY     ( 20 )
#define UART_ID_2 (2)
#define WIFI_AP_PSM_INFO_SSID           "conf_ap_ssid"
#define WIFI_AP_PSM_INFO_PASSWORD       "conf_ap_psk"
#define WIFI_AP_PSM_INFO_PMK            "conf_ap_pmk"
#define WIFI_AP_PSM_INFO_BSSID          "conf_ap_bssid"
#define WIFI_AP_PSM_INFO_CHANNEL        "conf_ap_channel"
#define WIFI_AP_PSM_INFO_IP             "conf_ap_ip"
#define WIFI_AP_PSM_INFO_MASK           "conf_ap_mask"
#define WIFI_AP_PSM_INFO_GW             "conf_ap_gw"
#define WIFI_AP_PSM_INFO_DNS1           "conf_ap_dns1"
#define WIFI_AP_PSM_INFO_DNS2           "conf_ap_dns2"
#define WIFI_AP_PSM_INFO_IP_LEASE_TIME  "conf_ap_ip_lease_time"
#define WIFI_AP_PSM_INFO_GW_MAC         "conf_ap_gw_mac"
#define CLI_CMD_AUTOSTART1              "cmd_auto1"
#define CLI_CMD_AUTOSTART2              "cmd_auto2"

extern uint8_t _heap_start;
extern uint8_t _heap_size; // @suppress("Type cannot be resolved")
extern uint8_t _heap_wifi_start;
extern uint8_t _heap_wifi_size; // @suppress("Type cannot be resolved")
static HeapRegion_t xHeapRegions[] =
{
        { &_heap_start,  (unsigned int) &_heap_size}, //set on runtime
        { &_heap_wifi_start, (unsigned int) &_heap_wifi_size },
        { NULL, 0 }, /* Terminates the array. */
        { NULL, 0 } /* Terminates the array. */
};

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName )
{
    puts("Stack Overflow checked\r\n");
    while (1) {
        /*empty here*/
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("Memory Allocate Failed. Current left size is %d bytes\r\n",
        xPortGetFreeHeapSize()
    );
    while (1) {
        /*empty here*/
    }
}

void vApplicationIdleHook(void)
{
    __asm volatile(
            "   wfi     "
    );
    /*empty*/
}

static void proc_hellow_entry(void *pvParameters)
{
    vTaskDelay(500);

    while (1) {
        printf("%s: RISC-V rv32imafc\r\n", __func__);
        vTaskDelay(10000);
    }
    vTaskDelete(NULL);
}

static void cmd_exception_load(char *buf, int len, int argc, char **argv)
{
    bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_LOAD_MISALIGN, (void*)0x22008001);
}

static void cmd_exception_l_illegal(char *buf, int len, int argc, char **argv)
{
    bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_ACCESS_ILLEGAL, (void*)0x00200000);
}

static void cmd_exception_store(char *buf, int len, int argc, char **argv)
{
    bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_STORE_MISALIGN, (void*)0x22008001);
}

static void cmd_exception_illegal_ins(char *buf, int len, int argc, char **argv)
{
    bl_irq_exception_trigger(BL_IRQ_EXCEPTION_TYPE_ILLEGAL_INSTRUCTION, (void*)0x22008001);
}

static void cmd_logen(char *buf, int len, int argc, char **argv)
{
    bl_sys_logall_enable();
}

static void cmd_logdis(char *buf, int len, int argc, char **argv)
{
    bl_sys_logall_disable();
}

static void cmd_load0w(char *buf, int len, int argc, char **argv)
{
    volatile uint32_t v = 0;

    /* backtrace */
    v = *(volatile uint32_t *)0;
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

    testbuf = aos_malloc(64);
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

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "exception_load", "exception load test", cmd_exception_load},
        { "exception_l_illegal", "exception load test", cmd_exception_l_illegal},
        { "exception_store", "exception store test", cmd_exception_store},
        { "exception_inst_illegal", "exception illegal instruction", cmd_exception_illegal_ins},
        /*TCP/IP network test*/
        {"logen", "logen", cmd_logen},
        {"logdis", "logdis", cmd_logdis},
        {"load0w", "load word from 0", cmd_load0w},
        {"aligntc", "align case test", cmd_align},
};

static void _cli_init()
{
    bl_sys_time_cli_init();
    blfdt_cli_init();
    bl_wdt_cli_init();
    bl_gpio_cli_init();
    looprt_test_cli_init();
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

static void __opt_feature_init(void)
{
#ifdef CONF_USER_ENABLE_VFS_ROMFS
    romfs_register();
#endif
}

extern int test_lcd_base(void);
static void aos_loop_proc(void *pvParameters)
{
    int fd_console;
    uint32_t fdt = 0, offset = 0;
    static StackType_t proc_stack_looprt[512];
    static StaticTask_t proc_task_looprt;

    /*Init bloop stuff*/
    looprt_start(proc_stack_looprt, 512, &proc_task_looprt);
    loopset_led_hook_on_looprt();

//    easyflash_init();
    vfs_init();
    vfs_device_init();

    /* uart */
#if 1
    if (0 == get_dts_addr("uart", &fdt, &offset)) {
        vfs_uart_init(fdt, offset);
    }
#else
    vfs_uart_init_simple_mode(0, 7, 16, 2 * 1000 * 1000, "/dev/ttyS0");
#endif

    if (0 == get_dts_addr("spi", &fdt, &offset)) {
        vfs_spi_fdt_init(fdt, offset);

    }

    __opt_feature_init();
    aos_loop_init();

    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        printf("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void*)0x12345678);
        _cli_init();
    }

    spi_wave_cli_init();
    aos_loop_run();

    puts("------------------------------------------\r\n");
    puts("+++++++++Critical Exit From Loop++++++++++\r\n");
    puts("******************************************\r\n");
    vTaskDelete(NULL);
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
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
    volatile uint32_t ulSetTo1ToExitFunction = 0;

    taskDISABLE_INTERRUPTS();
    while( ulSetTo1ToExitFunction != 1 ) {
        __asm volatile( "NOP" );
    }
}

static void _dump_boot_info(void)
{
    char chip_feature[40];
    const char *banner;

    puts("Booting BL602 Chip...\r\n");

    /*Display Banner*/
    if (0 == bl_chip_banner(&banner)) {
        puts(banner);
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

    puts("Build Version: ");
    puts(BL_SDK_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

    puts("PHY   Version: ");
    puts(BL_SDK_PHY_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

    puts("RF    Version: ");
    puts(BL_SDK_RF_VER); // @suppress("Symbol is not resolved")
    puts("\r\n");

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
    bl_sec_init();
    bl_sec_test();
    hal_boot2_init();
    bl_dma_init();

    /* board config is set after system is init*/
    hal_board_cfg(0);
}

static void system_thread_init()
{
    /*nothing here*/
}


void bfl_main()
{
    static StackType_t aos_loop_proc_stack[1024];
    static StaticTask_t aos_loop_proc_task;
    static StackType_t proc_hellow_stack[512];
    static StaticTask_t proc_hellow_task;


    bl_sys_early_init();

    /*Init UART In the first place*/
    bl_uart_init(0, 16, 7, 255, 255, 2 * 1000 * 1000);
    puts("Starting bl602 now....\r\n");

    bl_sys_init();

    _dump_boot_info();

    vPortDefineHeapRegions(xHeapRegions);
    printf("Heap %u@%p, %u@%p\r\n",
            (unsigned int)&_heap_size, &_heap_start,
            (unsigned int)&_heap_wifi_size, &_heap_wifi_start
    );

    system_init();
    system_thread_init();

    puts("[OS] Starting proc_hellow_entry task...\r\n");
    xTaskCreateStatic(proc_hellow_entry, (char*)"hellow", 512, NULL, 15, proc_hellow_stack, &proc_hellow_task);
    puts("[OS] Starting aos_loop_proc task...\r\n");
    xTaskCreateStatic(aos_loop_proc, (char*)"event_loop", 1024, NULL, 15, aos_loop_proc_stack, &aos_loop_proc_task);
    puts("[OS] Starting TCP/IP Stack...\r\n");

    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
