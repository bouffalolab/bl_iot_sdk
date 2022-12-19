/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <bl_irq.h>
#include "cli.h"
int cli_putstr(char *msg);

#define PS_BUFFER_SIZE 4096
struct tasks_stat {
    uint64_t task_num;
    TaskStatus_t *ts_array;
    uint64_t total_run_time;
    uint64_t idle_run_time;
    uint64_t trap_run_time;
};
struct irqs_stat {
    uint64_t irq_num;
    struct irq_ctx *irq_array;
};
static struct tasks_stat ps_tasks_stat;
static struct irqs_stat ps_irqs_stat;
static uint64_t interval;

// similar to vTaskList
static int u_task_list(char *write_buffer, int32_t buffer_len, float *usage, float *trap_usage)
{
    TaskStatus_t *ts_array;
    UBaseType_t array_size;
    uint32_t i, j;
    int n = 0;
    char cStatus;
    uint64_t total_run_time, trap_run_time, idle_count = 0;

    /* Take a snapshot of the number of tasks in case it changes while this
       function is executing. */
    array_size = uxTaskGetNumberOfTasks();

    if(!ps_tasks_stat.ts_array) {
	ps_tasks_stat.ts_array = pvPortMalloc(array_size * sizeof(TaskStatus_t));
	ps_tasks_stat.task_num = 0;
	ps_tasks_stat.total_run_time = 0;
	ps_tasks_stat.idle_run_time = 0;
	ps_tasks_stat.trap_run_time = 0;
    }
    ts_array = pvPortMalloc(array_size * sizeof(TaskStatus_t));

    if(!ts_array || !ps_tasks_stat.ts_array) {
	vPortFree(ts_array);
	vPortFree(ps_tasks_stat.ts_array);
	return -pdFREERTOS_ERRNO_ENOMEM;
    }

    array_size = uxTaskGetSystemState(ts_array, array_size, &total_run_time);

    if(ps_tasks_stat.total_run_time)
	interval = total_run_time - ps_tasks_stat.total_run_time;
    else
	interval = total_run_time;

    /* Create a human readable table from the binary data. */
    for(i = 0; i < array_size; i++) {
	switch(ts_array[i].eCurrentState) {
/*
 * Macros used by vListTask to indicate which state a task is in.
 */
#define tskRUNNING_CHAR         ( 'X' )
#define tskBLOCKED_CHAR         ( 'B' )
#define tskREADY_CHAR           ( 'R' )
#define tskDELETED_CHAR         ( 'D' )
#define tskSUSPENDED_CHAR       ( 'S' )
	case eRunning:	    cStatus = tskRUNNING_CHAR;
	    break;
	case eReady:	    cStatus = tskREADY_CHAR;
	    break;
	case eBlocked:	    cStatus = tskBLOCKED_CHAR;
	    break;
	case eSuspended:    cStatus = tskSUSPENDED_CHAR;
	    break;
	case eDeleted:	    cStatus = tskDELETED_CHAR;
	    break;
	default:
	    cStatus = 0x00;
	    break;
	}

	/* find in ps_tasks_stat */
	for(j = 0; j < ps_tasks_stat.task_num; j++) {
	    if(ps_tasks_stat.ts_array[j].xHandle == ts_array[i].xHandle \
	       && ps_tasks_stat.ts_array[j].xTaskNumber == ts_array[i].xTaskNumber) {
		n = snprintf(write_buffer, buffer_len, "%-15.15s\t%c\t%u\t%u\t%u\t%p\t%.4f%%\r\n", ts_array[i].pcTaskName, \
			cStatus, (unsigned int)ts_array[i].uxCurrentPriority, (unsigned int)ts_array[i].usStackHighWaterMark, \
			(unsigned int)ts_array[i].xTaskNumber, ts_array[i].pxStackBase, \
			(ts_array[i].ulRunTimeCounter - ps_tasks_stat.ts_array[j].ulRunTimeCounter) \
			/ (float)interval * 100);
		break;
	    }
	}

	/* cannot find in ps_tasks_stat */
	if(j == ps_tasks_stat.task_num) {
	    n = snprintf(write_buffer, buffer_len,  "%-15.15s\t%c\t%u\t%u\t%u\t%p\t%.4f%%\r\n", ts_array[i].pcTaskName, \
		    cStatus, (unsigned int)ts_array[i].uxCurrentPriority, (unsigned int)ts_array[i].usStackHighWaterMark, \
		    (unsigned int)ts_array[i].xTaskNumber, ts_array[i].pxStackBase, \
		    ts_array[i].ulRunTimeCounter / (float)interval * 100);
	}

	if(ts_array[i].xHandle == xTaskGetIdleTaskHandle()) {
	    idle_count = ts_array[i].ulRunTimeCounter - ps_tasks_stat.idle_run_time;
	    ps_tasks_stat.idle_run_time = ts_array[i].ulRunTimeCounter;
	}
	if(n < 0) {
	    vPortFree(ts_array);
	    return n;
	}
	buffer_len -= n;
	write_buffer += n;
	if(buffer_len <= 0) {
	    vPortFree(ts_array);
	    return -pdFREERTOS_ERRNO_ENOBUFS;
	}
    }

    // todo: defer free new ts_array
    vPortFree(ps_tasks_stat.ts_array);
    ps_tasks_stat.ts_array = ts_array;
    ps_tasks_stat.task_num = array_size;
    ps_tasks_stat.total_run_time = total_run_time;
    *usage = (interval - idle_count) / (float)interval * 100;
    trap_run_time = ullPortGetTrapAllCurrentTime();
    *trap_usage = (trap_run_time - ps_tasks_stat.trap_run_time) / (float)interval * 100;
    ps_tasks_stat.trap_run_time = trap_run_time;
    return interval / configCPU_CORE_CLOCK_HZ;
}

static int u_irq_list(char *write_buffer, int32_t buffer_len)
{
    int i, n, irq_array_size;
    uint64_t irq_count;
    struct irq_ctx **ctx = bl_irq_ctx_list(&irq_array_size);
    if(!ps_irqs_stat.irq_array) {
	ps_irqs_stat.irq_num = 0;
	// todo: defer free
	ps_irqs_stat.irq_array = pvPortMalloc(irq_array_size * sizeof(struct irq_ctx));
	memset(ps_irqs_stat.irq_array, 0, irq_array_size * sizeof(struct irq_ctx));
    }
    if(!ps_irqs_stat.irq_array)
	return -pdFREERTOS_ERRNO_ENOMEM;
    for(i = 0; i < irq_array_size; i++){
	if(!ctx[i])
	    continue;
	irq_count = ctx[i]->irq_run_time;
	if(irq_count == ps_irqs_stat.irq_array[i].irq_run_time)
	    continue;
	n = snprintf(write_buffer, buffer_len, "[%-13.13s]\t%d\t\t\t\t\t\t%.2f%%\r\n", ctx[i]->name, ctx[i]->irqnum, \
		     (irq_count - ps_irqs_stat.irq_array[i].irq_run_time) / (float)interval * 100);
	ps_irqs_stat.irq_array[i].irq_run_time = irq_count;
	buffer_len -= n;
	write_buffer += n;
	if(buffer_len <= 0) {
	    return -pdFREERTOS_ERRNO_ENOBUFS;
	}
    }
    return 0;
}

void freertos_e907_helper_ps_init_all_irqctx(void)
{
    int i, irq_array_size;
    bl_irq_ctx_list(&irq_array_size);
    //todo defer free
    struct irq_ctx *ctx = pvPortMalloc(irq_array_size * sizeof(struct irq_ctx));
    for(i = 1; i< irq_array_size; i++){
	ctx->name = "irq";
	ctx->irqnum = i;
	ctx->irq_run_time = 0;
	//fake address 1
	bl_irq_register_with_ctx(i, 1, ctx);
	ctx++;
    }
}

static void ps_cmd(char *buf, int len, int argc, char **argv)
{
    char *buffer;
    uint32_t buffer_len = PS_BUFFER_SIZE;
    float total_usage = 0, trap_usage = 0;
    int ago;
    const char *const header = "%uMHZ\t\t\t\t\t\t\t\tTrap: %.6f%%\r\nTask\t\tS\tP\tStack\t#\tBase" \
	"\t\tUsage(%.2f%% %us)\r\n" \
	"**********************************************************************************\r\n";

    buffer = pvPortMalloc(buffer_len);
    if (NULL == buffer) {
	printf("cli: malloc error\r\n");
	return;
    }
    *buffer = 0;
    ago = u_task_list(buffer, buffer_len, &total_usage, &trap_usage);
    if (ago >= 0) {
	printf(header, (unsigned int)configCPU_CORE_CLOCK_HZ / (1000 * 1000), trap_usage, total_usage, (unsigned int)ago);
	cli_putstr(buffer);
    } else if (ago == -pdFREERTOS_ERRNO_ENOBUFS) {
	printf("cli: buffer is not enough\r\n");
    } else if (ago == -pdFREERTOS_ERRNO_ENOMEM) {
	printf("cli: malloc error\r\n");
    } else {
	printf("cli: other error\r\n");
    }
    *buffer = 0;
    ago = u_irq_list(buffer, buffer_len);
    if (ago >= 0) {
	cli_putstr(buffer);
    } else if (ago == -pdFREERTOS_ERRNO_ENOBUFS) {
	printf("cli: buffer is not enough\r\n");
    } else if (ago == -pdFREERTOS_ERRNO_ENOMEM) {
	printf("cli: malloc error\r\n");
    } else {
	printf("cli: other error\r\n");
    }
    vPortFree(buffer);
}

const struct cli_command cli_helper_cmds[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "ps-thead", "thread dump", ps_cmd },
};

int freertos_e907_helper_ps_init(void)
{
    return 0;
}
