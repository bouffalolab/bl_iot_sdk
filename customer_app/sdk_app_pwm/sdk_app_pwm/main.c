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
#include <hal/soc/pwm.h>
#include <device/vfs_pwm.h>

#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>

#include <lwip/tcpip.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/tcp.h>
#include <lwip/err.h>
#include <http_client.h>
#include <netutils/netutils.h>

#include <bl602_glb.h>
#include <bl602_hbn.h>

#include <bl_sys.h>
#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_wifi.h>
#include <bl_sec.h>
#include <bl_cks.h>
#include <bl_irq.h>
#include <bl_dma.h>
#include <bl_gpio_cli.h>
#include <bl_wdt_cli.h>
#include <hal_uart.h>
#include <hal_sys.h>
#include <hal_gpio.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <looprt.h>
#include <loopset.h>

#include <bl_sys_time.h>
#include <bl_sys_ota.h>
#include <bl_romfs.h>
#include <fdt.h>

#include <easyflash.h>
#include <bl60x_fw_api.h>
#include <wifi_mgmr_ext.h>
#include <utils_log.h>
#include <libfdt.h>
#include <blog.h>
#include "hal_pwm.h"

#define TASK_PRIORITY_FW            ( 30 )

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

#include <bl_pwm.h>
void cmd_pwm_init(char *buf, int len, int argc, char **argv)
{
    uint8_t id;
    uint8_t pin;

    if (argc != 3) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);
    pin = atoi(argv[2]);

    bl_pwm_init(id, pin, 6000000);
}

void cmd_pwm_start(char *buf, int len, int argc, char **argv)
{
    uint8_t id;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);

    bl_pwm_start(id);
}

void cmd_pwm_stop(char *buf, int len, int argc, char **argv)
{
    uint8_t id;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);

    bl_pwm_stop(id);
}

void pwm_entry(void *arg)
{
    int fd = 0;
    const char *name = arg;
    int i;
    float duty = 0;

    aos_msleep(2000);
    fd = aos_open(name, 0);

    log_info("name = %s, fd = %d\r\n", name, fd);
    for (i = 0; i <= 100; i += 1) {
        duty = (float)i;
        log_info("set duty = %d\r\n", duty);
        aos_ioctl(fd, IOCTL_PWM_OUTPUT_DUTY, (unsigned long)(&duty));
        aos_ioctl(fd, IOCTL_PWM_OUTPUT_START, 0);
        aos_msleep(500);
    }

    aos_ioctl(fd, IOCTL_PWM_OUTPUT_STOP, 0);
}

void cmd_pwm_task(char *buf, int len, int argc, char **argv)
{
    aos_task_new("pwm_tsk", pwm_entry, "/dev/pwm0", 1024);
}

void cmd_pwm_test(char *buf, int len, int argc, char **argv)
{
    uint8_t pin = 0;
    uint8_t id = 0;
    int i;

    bl_pwm_init(id, pin, 60000);
    bl_pwm_set_duty(id, 50);

    for (i = 0; i < 10; i++) {
        log_info("start pin = %d, id = %d\r\n", id, pin);
        bl_pwm_start(id);
        aos_msleep(2000);

        log_info("stop pin = %d, id = %d\r\n", id, pin);
        bl_pwm_stop(id);
        aos_msleep(2000);
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "pwm_init", "pwm_init 0 0", cmd_pwm_init},
    { "pwm_start", "pwm_start 0", cmd_pwm_start},
    { "pwm_stop", "pwm_stop 0", cmd_pwm_stop},
    { "pwm_task", "pwm_task", cmd_pwm_task},
    { "pwm_test", "pwm_test", cmd_pwm_test},
};

void __pwm_init(char *buf, int len, int argc, char **argv)
{
    int id;
    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }
    id = atoi(argv[1]);
    hal_pwm_init(id, id);
    hal_pwm_duty_set(id, 5000, 0);
    hal_pwm_start(id);
}

void __pwm_duty_set(char *buf, int len, int argc, char **argv)
{
    uint32_t id, duty, ms;

    if (argc != 4) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);
    duty = atoi(argv[2]);
    ms = atoi(argv[3]);
    hal_pwm_duty_set(id, duty, ms);
}

void __pwm_duty_get(char *buf, int len, int argc, char **argv)
{
    uint32_t duty;
    int id;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);

    hal_pwm_duty_get(id, &duty);

    printf("pwm duty %ld", duty);
}

void __pwm_freq_set(char *buf, int len, int argc, char **argv)
{
    uint32_t freq;
    int id;

    if (argc != 3) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);
    freq = atoi(argv[2]);
    hal_pwm_freq_update(id, freq);
}

void __pwm_freq_get(char *buf, int len, int argc, char **argv)
{
    uint32_t freq;
    int id;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);
    hal_pwm_freq_get(id, &freq);
    printf("pwm freq %ld", freq);
}

void __pwm_stop(char *buf, int len, int argc, char **argv)
{
    int id;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    id = atoi(argv[1]);
    hal_pwm_stop(id);
}

// hal_pwm_init 0
// hal_pwm_duty_set 0 9000 20000
// hal_pwm_duty_set 1 3000 18000
// hal_pwm_duty_set 2 7000 15000
// hal_pwm_duty_set 3 7000 15000
const static struct cli_command hal_pwm_cmds[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "hal_pwm_init", "pwm_init 0", __pwm_init},
    { "hal_pwm_duty_set", "pwm_duty_set 0 20000 1000", __pwm_duty_set},
    { "hal_pwm_duty_get", "pwm_duty_get 0", __pwm_duty_get},
    { "hal_pwm_freq_set", "pwm_freq_set 0 3000", __pwm_freq_set},
    { "hal_pwm_freq_get", "pwm_freq_get 0", __pwm_freq_get},
    { "hal_pwm_stop", "pwm_stop 0", __pwm_stop},
};

static void _cli_init()
{
    /*Put CLI which needs to be init here*/
    easyflash_cli_init();
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

static void aos_loop_proc(void *pvParameters)
{
    int fd_console;
    uint32_t fdt = 0, offset = 0;
    static StackType_t proc_stack_looprt[512];
    static StaticTask_t proc_task_looprt;

    /*Init bloop stuff*/
    looprt_start(proc_stack_looprt, 512, &proc_task_looprt);
    loopset_led_hook_on_looprt();

    easyflash_init();
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
    if (0 == get_dts_addr("gpio", &fdt, &offset)) {
        hal_gpio_init_from_dts(fdt, offset);
    }

    /* pwm */
    if (0 == get_dts_addr("pwm", &fdt, &offset)) {
        vfs_pwm_init(fdt, offset);
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
    bl_dma_init();
    hal_boot2_init();

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

    bl_sys_early_init();

    /*Init UART In the first place*/
    bl_uart_init(0, 16, 7, 255, 255, 2 * 1000 * 1000);
    printf("Starting bl602 now....\r\n");

    bl_sys_init();

    _dump_boot_info();

    vPortDefineHeapRegions(xHeapRegions);
    printf("Heap %u@%p, %u@%p\r\n",
            (unsigned int)&_heap_size, &_heap_start,
            (unsigned int)&_heap_wifi_size, &_heap_wifi_start
    );

    system_init();
    system_thread_init();

    puts("[OS] Starting aos_loop_proc task...\r\n");
    xTaskCreateStatic(aos_loop_proc, (char*)"event_loop", 1024, NULL, 15, aos_loop_proc_stack, &aos_loop_proc_task);
    puts("[OS] Starting TCP/IP Stack...\r\n");
    tcpip_init(NULL, NULL);

    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
