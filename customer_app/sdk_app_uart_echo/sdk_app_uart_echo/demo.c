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
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <vfs.h>
#include <utils_log.h>
#include "demo.h"

static const char *ci_table_step_init[] = CI_CASE_TABLE_STEP1;
static const char *ci_table_step_send[] = CI_CASE_TABLE_STEP2;
static const char *ci_table_step_recv[] = CI_CASE_TABLE_STEP3;
static const char *ci_table_step_end[] = CI_CASE_TABLE_STEP4;

void log_step(const char *step[2])
{
    printf("%s   %s\r\n", step[0], step[1]);
}

static void uart_echo_task(void *arg)
{
    int length = 0, total = 0;
    uint8_t buf_recv[128];
    uint8_t *pbuf = buf_recv;
    const char *name = arg;
    const char *send_recv_log = "1234567890abcdefg";

    int fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);
    if (fd < 0) {
        return;
    }
    memset(buf_recv, 0, sizeof(buf_recv));
    log_step(ci_table_step_init);

    aos_write(fd, send_recv_log, strlen(send_recv_log));
    log_step(ci_table_step_send);

    vTaskDelay(1000);
    length = 0;

    while (1) {
        length = aos_read(fd, pbuf + total, strlen(send_recv_log));
        total += length;    
        
        if (total != strlen(send_recv_log)) {
            continue;
        }
        if (memcmp(buf_recv, send_recv_log, strlen(send_recv_log)) == 0) {
            printf("recvbuff:%s\r\n", send_recv_log);
            log_step(ci_table_step_recv);
            break;
        }
        vTaskDelay(10);
    }
    aos_close(fd);
    log_step(ci_table_step_end);
}

void ci_loop_proc()
{
    aos_task_new("uart_echo", uart_echo_task, "/dev/ttyS1", 2048);
}

