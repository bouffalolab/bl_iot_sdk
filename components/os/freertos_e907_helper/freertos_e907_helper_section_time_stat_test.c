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
#include <bl808.h>
#include <bl_irq.h>
#include "freertos_e907_helper_section_time_stat.h"
#include "cli.h"

#define MSIP_BASE (0xE0000000UL)

static char memcpy_src[4096];
static char memcpy_dst[4096];
static void memcpy_payload(int num){
    memcpy(memcpy_dst, memcpy_src, num);
}

static void trigger_soft(unsigned int i)
{
    while(i--) {
	// trigger irq
	*(volatile char *)MSIP_BASE = 1;
    }
}

static void fake_trigger_soft(unsigned int i)
{
    while(i--) {
	// fake trigger irq
	*(volatile char *)MSIP_BASE = 0;
    }
}

static void section_time_test1(){
    float result = -1, result1 = -1;
    int id, id1, i = 0;
    id = freertos_e907_helper_section_time_register("hello", 1000);
    id1 = freertos_e907_helper_section_time_register("hello1", 1000);
    while(1){
	freertos_e907_helper_section_time_begin(id1, &result1);
	freertos_e907_helper_section_time_begin(id, &result);
	if(result > 0)
	    id = -1;
	if(result1 > 0)
	    id1 = -1;
	if(result > 0 && result1 > 0 ) {
	    printf("1000 msec have arrived, %.2f%%\r\n", result);
	    printf("1000 msec have arrived, %.2f%%\r\n", result1);
	    break;
	}
	memcpy_payload(4096);
	//trigger_soft(10);
	freertos_e907_helper_section_time_end(id);
	//fake_trigger_soft(1000);
	memcpy_payload(4096);
	freertos_e907_helper_section_time_end(id1);
    }
    /* with 1000 soft trigger, 87.62%, 99.31%,
       this case acturally measure id1: 87ms, id: 76ms, irq: 913ms,
       accroding ps-thead-test4 measure test_task: 67ms, irq: 932ms,
       So section_time_stat dont decrease precision */
    /* with 100 soft trigger, 60.39%, 97.78% */
    /* with 10 soft trigger,  49.34%, 97.15% */
    /* comment trigger, 47.06%, 97.04% */

}

int soft_irq_count;
static void irq_handler(void)
{
    int i = 100;
    if(*(char *)MSIP_BASE == 1)
	*(char *)MSIP_BASE = 0;
    while(i--) soft_irq_count++;
}

static void section_time_test1_cmd(char *buf, int len, int argc, char **argv)
{
    if(argc != 1) {
	puts("section_time_test1 \r\n");
	return;
    }
    StackType_t *proc_stack_ptr = pvPortMalloc(1000 * sizeof(StackType_t));
    StaticTask_t *task_ptr = pvPortMalloc(1 * sizeof(StaticTask_t));
    if(!proc_stack_ptr || !task_ptr) {
	vPortFree(proc_stack_ptr);
	vPortFree(task_ptr);
	puts("malloc error\r\n");
	return;
    }
    bl_irq_register(MSOFT_IRQn, irq_handler);
    bl_irq_enable(MSOFT_IRQn);
    xTaskCreateStatic(section_time_test1, (char*)"section_time_test1", 1000, NULL, 16, proc_stack_ptr, task_ptr);
}

const struct cli_command section_time_test_cmds[] STATIC_CLI_CMD_ATTRIBUTE = {
	{ "section-time-stat-test1", "run", section_time_test1_cmd },
};

int freertos_e907_helper_section_time_stat_test_init(void)
{
    return 0;
}
