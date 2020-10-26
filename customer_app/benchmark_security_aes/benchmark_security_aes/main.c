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

#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_wifi.h>
#include <bl_sec.h>
#include <bl_cks.h>
#include <bl_irq.h>
#include <bl_dma.h>
#include <hal_uart.h>
#include <hal_sys.h>
#include <hal_gpio.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <looprt.h>
#include <loopset.h>
#include <bl_sys_time.h>
#include <fdt.h>
#include <libfdt.h>
#include <mbedtls/aes.h>
#include <mbedtls/gcm.h>
#include <mbedtls/sha1.h>
#include <mbedtls/sha256.h>

#include <utils_log.h>
#include <libfdt.h>
#include <blog.h>
#include <bl_timer.h>

#include "aes_test.h"
#include "gmac_test.h"
#include "sha_test.h"

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

static void _cli_init()
{
    /*Put CLI which needs to be init here*/
    bl_sys_time_cli_init();
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

static void aos_loop_proc(void *pvParameters)
{
    int fd_console;
    uint32_t fdt = 0, offset = 0;

    vfs_init();
    vfs_device_init();

    /* uart */
    if (0 == get_dts_addr("uart", &fdt, &offset)) {
        vfs_uart_init(fdt, offset);
    }

    aos_loop_init();

    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        printf("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void*)0x12345678);
        _cli_init();
    }

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
    bl_sec_init();
    bl_sec_test();
    bl_dma_init();
    bl_irq_init();
    hal_boot2_init();

    /* board config is set after system is init*/
    hal_board_cfg(0);
}

static void system_thread_init()
{
    /*nothing here*/
}

static void test_cmd_aes_ecb(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count  = 256;
    aes_key_t keytype = AES_TEST_KEY_128;
    uint8_t aes_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        keytype = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        aes_soft = strtol(argv[4], NULL, 0);
    }
    if (argc >= 6) {
        ram_type = strtol(argv[5], NULL, 0);
    }

    aes_ecb_test(length, count, keytype, aes_soft, ram_type);
}

static void test_cmd_aes_cbc(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count  = 256;
    aes_key_t keytype = AES_TEST_KEY_128;
    uint8_t aes_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        keytype = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        aes_soft = strtol(argv[4], NULL, 0);
    }
    if (argc >= 6) {
        ram_type = strtol(argv[5], NULL, 0);
    }

    aes_cbc_test(length, count, keytype, aes_soft, ram_type);
}

static void test_cmd_aes_ctr(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count  = 256;
    aes_key_t keytype = AES_TEST_KEY_128;
    uint8_t aes_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        keytype = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        aes_soft = strtol(argv[4], NULL, 0);
    }
    if (argc >= 6) {
        ram_type = strtol(argv[5], NULL, 0);
    }
    aes_ctr_test(length, count, keytype, aes_soft, ram_type);
}

static void test_cmd_aes_gcm(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count  = 256;
    aes_key_t keytype = AES_TEST_KEY_128;
    uint8_t aes_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        keytype = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        aes_soft = strtol(argv[4], NULL, 0);
    }
    if (argc >= 6) {
        ram_type = strtol(argv[5], NULL, 0);
    }
    aes_gcm_test(length, count, keytype, aes_soft, ram_type);
}

static void test_cmd_gmac(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count  = 256;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        ram_type = strtol(argv[3], NULL, 0);
    }
    gmac_test(length, count, ram_type);
}

static void test_cmd_sha256(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count =  256;
    uint8_t sha_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        sha_soft = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        ram_type = strtol(argv[4], NULL, 0);
    }
    sha_test(length, count, SHA_256_MODE, sha_soft, ram_type);
}

static void test_cmd_sha224(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count =  256;
    uint8_t sha_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        sha_soft = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        ram_type = strtol(argv[4], NULL, 0);
    }
    sha_test(length, count, SHA_224_MODE, sha_soft, ram_type);
}

static void test_cmd_sha1(char *buf, int len, int argc, char **argv)
{
    uint32_t length = 32768;
    uint32_t count =  256;
    uint8_t sha_soft = 0;
    ram_type_t ram_type = DTCM;

    if (argc >= 2) {
        length = strtol(argv[1], NULL, 0);
    }
    if (argc >= 3) {
        count = strtol(argv[2], NULL, 0);
    }
    if (argc >= 4) {
        sha_soft = strtol(argv[3], NULL, 0);
    }
    if (argc >= 5) {
        ram_type = strtol(argv[4], NULL, 0);
    }
    sha_test(length, count, SHA_1_MODE, sha_soft, ram_type);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "test_aes_ecb", "AES ECB -length -count -keytype -soft -ramtype", test_cmd_aes_ecb},
    { "test_aes_cbc", "AES CBC -length -count -keytype -soft -ramtype", test_cmd_aes_cbc},
    { "test_aes_ctr", "AES CTR -length -count -keytype -soft -ramtype", test_cmd_aes_ctr},
    { "test_aes_gcm", "AES GCM -length -count -keytype -soft -ramtype", test_cmd_aes_gcm},
    { "test_aes_gmac", "AES GMAC -length -count -ramtype", test_cmd_gmac},
    { "test_sha256", "SHA256 -length -count -soft -ramtype", test_cmd_sha256},
    { "test_sha224", "SHA224 -length -count -soft -ramtype", test_cmd_sha224},
    { "test_sha1", "SHA1 -length -count -soft -ramtype", test_cmd_sha1},
};

void bfl_main(void)
{
    static StaticTask_t aos_loop_proc_task;
    static StackType_t aos_loop_proc_stack[1024];

    /*Init UART In the first place*/
    bl_uart_init(0, 16, 7, 255, 255, 2 * 1000 * 1000);
    puts("Starting bl602 now....\r\n");

    _dump_boot_info();

    vPortDefineHeapRegions(xHeapRegions);

    system_init();
    system_thread_init();

    puts("[OS] Starting aos_loop_proc task...\r\n");
    xTaskCreateStatic(aos_loop_proc, (char*)"event_loop", 1024, NULL, 15, aos_loop_proc_stack, &aos_loop_proc_task);

    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
