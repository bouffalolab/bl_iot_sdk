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

#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_irq.h>
#include <bl_timer.h>
#include <hal_sys.h>
#include <hosal_uart.h>

#include <utils_log.h>
#include <blog.h>



#define UART_ID_C906 (0)
#define mainHELLO_TASK_PRIORITY     ( 20 )
#define UART_ID_2 (2)
#define UART_ID_1 (1)
#define UART_ID_0 (0)


HOSAL_UART_DEV_DECL(uart_stdio, UART_ID_C906, 16, 17, 2000000)
/* TODO: const */
volatile uint32_t uxTopUsedPriority __attribute__((used)) =  configMAX_PRIORITIES - 1;

static HeapRegion_t xHeapRegions[] =
{
    { NULL, 0 },    /* set on runtime */
    { NULL, 0 },    /* set on runtime */
    { NULL, 0 }     /* Terminates the array */
};

static void bl808_FreeRTOS_init(void)
{
    extern uint8_t _heap_start_tcm;
    extern uint8_t _heap_size_tcm;
    //extern uint8_t _heap_start;
    //extern uint8_t _heap_size;

    xHeapRegions[0].pucStartAddress = (uint8_t*)&_heap_start_tcm;
    xHeapRegions[0].xSizeInBytes = (size_t)&_heap_size_tcm;

    printf("Heap Info: %ld KB @ [0x%p ~ 0x%p]\r\n",
            xHeapRegions[0].xSizeInBytes >> 10,
            xHeapRegions[0].pucStartAddress,
            xHeapRegions[0].pucStartAddress + xHeapRegions[0].xSizeInBytes
    );
    /*when psram enable need use*/
#if 0
    xHeapRegions[1].pucStartAddress = (uint8_t*)&_heap_start;
    xHeapRegions[1].xSizeInBytes = (uint32_t)&_heap_size;
    printf("psram Info: %ld KB @ [0x%p ~ 0x%p]\r\n",
            xHeapRegions[1].xSizeInBytes >> 10,
            xHeapRegions[1].pucStartAddress,
            xHeapRegions[1].pucStartAddress + xHeapRegions[1].xSizeInBytes
    );
#endif
    vPortDefineHeapRegions(xHeapRegions);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName )
{
    puts("Stack Overflow checked\r\n");
    printf("Task Name %s\r\n", pcTaskName);
    while (1) {
        /*empty here*/
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("Memory Allocate Failed. Current left size is %lu bytes\r\n",
        xPortGetFreeHeapSize()
    );
    while (1) {
        /*empty here*/
    }
}

void vApplicationIdleHook(void)
{
#if 0
    __asm volatile(
            "   wfi     "
    );
    /*empty*/
#else
    (void)uxTopUsedPriority;
#endif
}

static void _cli_init()
{
    extern int helper_cam_yuv_sensor_cli_init(void);
    helper_cam_yuv_sensor_cli_init();
}

static void cmd_c906_hello_word(char *buf, int len, int argc, char **argv)
{
    printf("C906 hello world!\r\n");
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "hello", "c906 hello world", cmd_c906_hello_word}
};

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
        {"cam_mjpeg_start mipi\r\n",      50},
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
    vfs_uart_init_simple_mode(0, 16, 17, 2000000, "/dev/ttyS0"); //UART for cli

    aos_loop_init();

    fd_console = aos_open("/dev/ttyS0", 0);
    if (fd_console >= 0) {
        printf("Init CLI with event Driven\r\n");
        aos_cli_init(0);
        aos_poll_read_fd(fd_console, aos_cli_event_cb_read_get(), (void*)0x12345678);
        _cli_init();
        aos_register_event_filter(EV_CLI, event_cb_cli_raw_event, NULL);
        aos_post_delayed_action(10, app_delayed_action, NULL);
    }

    aos_loop_run();

    puts("------------------------------------------\r\n");
    puts("+++++++++Critical Exit From Loop++++++++++\r\n");
    puts("******************************************\r\n");
    vTaskDelete(NULL);
}

static void proc_hellow_entry(void *pvParameters)
{
    char isa_str[32] = { 0 };
    // int count = 1;
    bl_chip_info(isa_str);
    while (1) {
        printf("hello %s, tick %lu\r\n", isa_str, xTaskGetTickCount());
        vTaskDelay(1000);
    }
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

#if 0
static void system_init(void)
{
    bl_irq_init();
}

static void system_thread_init()
{
    /*nothing here*/
}
#endif




void bfl_main()
{
    static StackType_t aos_loop_proc_stack[1024];
    static StaticTask_t aos_loop_proc_task;
    static StackType_t proc_hellow_stack[512];
    static StaticTask_t proc_hellow_task;
extern void bflb_platform_init_time();
    //bflb_platform_init_time();
    //bl_uart_gpio_init(UART_ID_1, 1, 1, 0, 0, 2000000);        //UART for debug msg
  
    bl_uart_c906_init(UART_ID_C906, 16, 17, 0, 0, 2000000);

    puts("Starting bl808 now....\r\n");
    bl808_FreeRTOS_init();

    puts("[OS] Starting aos_loop_proc task...\r\n");
    xTaskCreateStatic(aos_loop_proc, (char*)"event_loop", 1024, NULL, 15, aos_loop_proc_stack, &aos_loop_proc_task);

    puts("[OS] Starting proc_hellow_entry task...\r\n");
    xTaskCreateStatic(proc_hellow_entry, (char*)"hellow", 512, NULL, 15, proc_hellow_stack, &proc_hellow_task);

    puts("[OS] Starting OS Scheduler...\r\n");
    vTaskStartScheduler();
}
