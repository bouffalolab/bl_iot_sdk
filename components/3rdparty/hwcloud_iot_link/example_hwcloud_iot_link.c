/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
// #include "queue.h"

extern int link_main(void *args); 
void vStartCLOUDTasks_hwcloud(uint16_t usTaskStackSize, UBaseType_t uxTaskPriority)
{
	BaseType_t x = 0L;

	xTaskCreate(link_main,	/* The function that implements the task. */
			"link_main",			/* Just a text name for the task to aid debugging. */
			usTaskStackSize,	/* The stack size is defined in FreeRTOSIPConfig.h. */
			(void *)x,		/* The task parameter, not used in this case. */
			uxTaskPriority,		/* The priority assigned to the task is defined in FreeRTOSConfig.h. */
			NULL);				/* The task handle is not used. */

}

void example_hwcloud_iot_link(void)
{	

	vStartCLOUDTasks_hwcloud(1000, tskIDLE_PRIORITY + 16);

}
/*-----------------------------------------------------------*/


