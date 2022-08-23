#include <FreeRTOS.h>
#include <task.h>
#include "hal_wifi.h"
#include <bl_pm.h>


#define WIFI_STACK_SIZE     (1536)
#define TASK_PRIORITY_FW    (30)

#ifndef FEATURE_WIFI_DISABLE
#include <bl60x_fw_api.h>
int hal_wifi_start_firmware_task(void)
{
    static StackType_t wifi_fw_stack[WIFI_STACK_SIZE];
    static StaticTask_t wifi_fw_task;

    bl_pm_init();
    xTaskCreateStatic(wifi_main, (char*)"fw", WIFI_STACK_SIZE, NULL, TASK_PRIORITY_FW, wifi_fw_stack, &wifi_fw_task);

    return 0;
}
#endif
