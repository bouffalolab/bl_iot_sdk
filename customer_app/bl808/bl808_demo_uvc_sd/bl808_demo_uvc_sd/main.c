#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include <string.h>
#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>
#include <freertos_e907_helper_ps_with_irq.h>
#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_sec.h>
#include <bl_timer.h>
#include <bl_sys.h>
#ifdef FEATURE_ENABLE_EASYFLASH
#include <easyflash.h>
#endif
#include <hal_uart.h>
#include <hal_sys.h>

#include <hosal_uart.h>
#include <bl808_pds.h>
#include <bl808_glb.h>
#include <bl808_glb_gpio.h>


#include <bl808_user_xram.h>
#include <xram_platform.h>
#include <xram_peripheral.h>
#include <xram_peri_common.h>


#include <boot_cpu0.h>
#ifdef SYS_USER_VFS_ROMFS_ENABLE
#include <bl_romfs.h>
#include <fs/vfs_romfs.h>
#endif
#include "hal_sdh.h"
#include "fatfs.h"
#include <helper_sdh.h>
#include <helper_usb_cam.h>
#include <helper_audio.h>
#define TASK_AOS_TASKNAME       ((char*)"aos_loop")
#define TASK_AOS_STACKSIZE      (1024)
#define TASK_AOS_PRIORITY       (15)
#define UART_PIN_TX_FOR_DEBUG       (14)
#define UART_PIN_RX_FOR_DEBUG       (15)

HOSAL_UART_DEV_DECL(uart_stdio, 0, UART_PIN_TX_FOR_DEBUG, UART_PIN_RX_FOR_DEBUG, 115200)

extern uint8_t _heap_start;
extern uint8_t _heap_size; // @suppress("Type cannot be resolved")


HeapRegion_t xHeapRegions[] =
{
    { &_heap_start, (uint32_t)&_heap_size}, //FIXME hardcode heap region set on runtime
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
    // printf("Memory Allocate Failed. Current left size is %d bytes\r\n",
    //     xPortGetFreeHeapSize()
    // );
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
    puts("------------------------------------------------------------\r\n");
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

static void system_thread_init()
{
    //bl_sec_init();
    //bl_sec_test();
    //tcpip_init(NULL, NULL);
}

static void _cli_init()
{
    int ret = 0;
    /*Put CLI which needs to be init here*/
    /* The following code is to make sure the cli command could be found by the linker */
#ifdef FEATURE_ENABLE_EASYFLASH
    easyflash_cli_init();
#endif
    boot_cpu0_cli_init();
    freertos_e907_helper_ps_init();
    freertos_e907_helper_ps_init_all_irqctx();

    helper_usb_cam_cli_init();
    helper_audio_cli_init();

    hal_sd_bus_4bits_enable();
    ret = fatfs_register();
    printf("fatfs ret:%d\r\n", ret);
    helper_sdh_cli_init();
}

static void event_cb_cli_raw_event(input_event_t *event, void *private_data)
{
    switch (event->code) {
        case CODE_CLI_DATA_RAW:
        {
            printf("CLI RAW Data, %s\r\n", (char*)event->value);
            aos_cli_input_direct((char*)event->value, strlen((char*)event->value));
            vPortFree((char*)event->value);
        }
        break;
        default:
        {
            /*nothing*/
        }
    }
}

static void app_delayed_action(void *arg)
{
    char *cmd1;
    struct {
        const char *cmd;
        int delay;
    } cmd_list[] = {
        {"c906\r\n",           200},
        {"usb_cam\r\n",        10},
    };
    static unsigned int counter = 0;

    if (counter < sizeof(cmd_list)/sizeof(cmd_list[0])) {
        cmd1 = pvPortMalloc(strlen(cmd_list[counter].cmd));
        memcpy(cmd1, cmd_list[counter].cmd, strlen(cmd_list[counter].cmd));
        aos_post_event(EV_CLI, CODE_CLI_DATA_RAW, (unsigned long)cmd1);
        aos_post_delayed_action(cmd_list[counter].delay, app_delayed_action, NULL);
        counter++;
    }

}

static void aos_loop_proc(void *pvParameters)
{
    int fd_console;

    vfs_init();
    vfs_device_init();

    /* uart */
    vfs_uart_init_simple_mode(0, UART_PIN_TX_FOR_DEBUG, UART_PIN_RX_FOR_DEBUG, 2000000, "/dev/ttyS0");

    aos_loop_init();

    romfs_register();
#ifdef FEATURE_ENABLE_EASYFLASH
    easyflash_init();
#endif


    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        puts("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void*)0x12345678);
        _cli_init();
        aos_register_event_filter(EV_CLI, event_cb_cli_raw_event, NULL);
        aos_post_delayed_action(10, app_delayed_action, NULL);
    }

    puts("start aos loop... \r\n");

    aos_loop_run();

    puts("------------------------------------------\r\n");
    puts("+++++++++Critical Exit From Loop++++++++++\r\n");
    puts("******************************************\r\n");
    vTaskDelete(NULL);
}

#if 0
static void xram_task(void *pvParameters)
{
    size_t ret = 0;
    uint8_t buf[128] = {0};
    bl_xram_user_ring_reset();
    while (1) {
        ret = 0;
        memset(buf, 0, sizeof(buf));
        ret = bl_xram_user_ring_read(buf, 10);
        if (ret != 0) {
            printf("rcv msg %s size %d\r\n", buf, ret);
            bl_xram_user_ring_write("hello c906", 10);
        }
        vTaskDelay(500);
    }
}
#endif

void xram_peri_op()
{
    XRAMRingReset(XRAM_PERI_OP_QUEUE);
    xram_operation_handle();
}

void bfl_main()
{
    static StackType_t aos_loop_proc_stack[1024];
    static StaticTask_t aos_loop_proc_task;
    static StackType_t xram_task_stack[256];
    static StaticTask_t xram_task_handle;

    bl_uart_init(0, UART_PIN_TX_FOR_DEBUG, UART_PIN_RX_FOR_DEBUG, 255, 255, 2000000);

    printf("mtimer clock freq:%ld\r\n", CPU_Get_MTimer_Clock());

    bl_sys_lowlevel_init();
    _dump_boot_info();

    vPortDefineHeapRegions(xHeapRegions);

    puts("[OS] Starting aos_loop_proc task...\r\n");
    bl_xram_user_ring_init();
    system_thread_init();

    xTaskCreateStatic(aos_loop_proc, TASK_AOS_TASKNAME, TASK_AOS_STACKSIZE, NULL,
        TASK_AOS_PRIORITY, aos_loop_proc_stack, &aos_loop_proc_task);
    xTaskCreateStatic(xram_peri_op, "xram_peri", 256, NULL, 20, xram_task_stack, &xram_task_handle);

    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}

