/*
 * Copyright (c) 2016-2023 Bouffalolab.
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
#include <stdio.h>

#define SECTION_TIME_MAX 16
struct registed_stat {
    char *name;
    uint64_t begin;
    uint64_t cost;
    uint64_t task_time;
    uint64_t background_time;
    uint64_t trap_counter;
    uint64_t msec;
};
static struct registed_stat section_time[SECTION_TIME_MAX];

int freertos_e907_helper_section_time_register(char *name, int msec)
{
    int i;
    for(i = 0; i < SECTION_TIME_MAX; i++)
	if(section_time[i].name == NULL)
	    break;
    if(i == SECTION_TIME_MAX)
	return -1;
    section_time[i].name = name;
    section_time[i].begin = 0;
    section_time[i].cost = 0;
    section_time[i].task_time = 0;
    section_time[i].background_time = 0;
    section_time[i].msec = msec;
    return i;
}

inline static uint64_t msec2cycle(uint64_t msec)
{
    return msec * (configCPU_CORE_CLOCK_HZ / 1000);
}

void freertos_e907_helper_section_time_begin(int index, float *result)
{
    uint64_t begin, background;

    if(index < 0)
	return;
    vGetTaskRunningTimeSnapshot(&begin, &background);
    if(section_time[index].begin != 0)
	section_time[index].task_time += begin - section_time[index].begin;
    section_time[index].begin = begin;

    if(section_time[index].background_time == 0) {
	section_time[index].background_time = background;
    } else if (background - section_time[index].background_time > msec2cycle(section_time[index].msec)) {
	/* msec arrived */
	*result = section_time[index].cost / (float) section_time[index].task_time * 100;
    }
}

void freertos_e907_helper_section_time_end(int index)
{
    uint64_t end, background;

    if(index < 0)
	return;
    vGetTaskRunningTimeSnapshot(&end, &background);
    section_time[index].cost += end - section_time[index].begin;
}
