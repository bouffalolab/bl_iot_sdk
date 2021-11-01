#include <FreeRTOS.h>
#include <task.h>
#include <bl_sys_time.h>
#include <cli.h>
#include "demo.h"

static void _cli_init()
{
    /*Put CLI which needs to be init here*/
    bl_sys_time_cli_init();
    fdt_cli_init();
}

static void system_thread_init()
{
    /*nothing here*/
}

static void proc_main_entry(void *pvParameters)
{
    _cli_init();

    vTaskDelete(NULL);
}

void main()
{
    static StaticTask_t proc_main_task;
    static StackType_t proc_main_stack[1024];

    system_thread_init();

    puts("[OS] proc_main_entry task...\r\n");
    xTaskCreateStatic(proc_main_entry, (char*)"main_entry", 1024, NULL, 15, proc_main_stack, &proc_main_task);
}
