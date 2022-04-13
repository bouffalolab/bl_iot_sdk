
#include <assert.h>
#include <stdio.h>
#include <errno.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <openthread-core-config.h>
#include <openthread/cli.h>
#include <openthread/diag.h>
#include <openthread/tasklet.h>

#include "openthread_port.h"
#include <openthread_assert.h>

ot_system_event_t           ot_system_event_var = OT_SYSTEM_EVENT_NONE;
static SemaphoreHandle_t    ot_extLock          = NULL;
static otInstance *         ot_instance         = NULL;
static TaskHandle_t         ot_taskHandle       = NULL;

__attribute__((weak)) void otrAppProcess(ot_system_event_t sevent) 
{
}

void otTaskletsSignalPending(otInstance *aInstance)
{
    if (aInstance) {
        OT_NOTIFY(OT_SYSTEM_EVENT_OT_TASKLET);
    }
}

otInstance *otrGetInstance()
{
    return ot_instance;
}

void otSysProcessDrivers(otInstance *aInstance) 
{
    ot_system_event_t sevent = OT_SYSTEM_EVENT_NONE;

    OT_GET_NOTIFY(sevent);
    ot_alarmTask(sevent);
    ot_uartTask(sevent);
    ot_radioTask(sevent);
    otrAppProcess(sevent);
}

void otSysEventSignalPending(void)
{
    if (xPortIsInsideInterrupt())
    {
        BaseType_t pxHigherPriorityTaskWoken = pdTRUE;
        vTaskNotifyGiveFromISR( ot_taskHandle, &pxHigherPriorityTaskWoken);
    }
    else
    {
        xTaskNotifyGive(ot_taskHandle);
    }
}

void otrLock(void)
{
    if (xTaskGetCurrentTaskHandle() != ot_taskHandle) {
        xSemaphoreTake(ot_extLock, portMAX_DELAY);
    }
}

void otrUnlock(void)
{
    if (xTaskGetCurrentTaskHandle() != ot_taskHandle) {
        xSemaphoreGive(ot_extLock);
    }
}

void otrStackInit(void) 
{
    static StaticQueue_t stackLock;

    ot_extLock = xSemaphoreCreateMutexStatic(&stackLock);
    assert(ot_extLock != NULL);

    ot_instance = otInstanceInitSingle();
    assert(ot_instance);
}

static void otrStackTask(void *aContext)
{
    /** This task is an example to handle both main event loop of openthread task lets and 
     * hardware drivers for openthread, such as radio, alarm timer and also uart shell.
     * Customer can implement own task for both of two these missions with other privoded APIs.  */

    errno;

    OT_THREAD_SAFE (
        ot_radioInit(ot_instance);

        otrStackInit();

#if OPENTHREAD_ENABLE_DIAG
        otDiagInit(ot_instance);
#endif

        otrInitUser(ot_instance);
    );

    while (true)
    {

        OT_THREAD_SAFE (
            otTaskletsProcess(ot_instance);
            otSysProcessDrivers(ot_instance);
        );

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }

    otInstanceFinalize(ot_instance);
    ot_instance = NULL;

    vTaskDelete(NULL);
}

void otrStart(void)
{
    static StackType_t  ot_stackTask_stack[OT_TASK_SIZE];
    static StaticTask_t ot_task;

    ot_taskHandle = xTaskCreateStatic(otrStackTask, "threadTask", OT_TASK_SIZE, ot_instance, OT_TASK_PRORITY, ot_stackTask_stack, &ot_task);
}
