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
#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <hal_ir.h>
#include <stdlib.h>
#include <stdio.h>
#include <cli.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <stdio.h>
#include "demo.h"
#include <queue.h>

uint32_t data[5001];
static void test_irled(char *buf, int len, int argc, char **argv)
{
    static int init_flag = 0;
    int i;
    int cnt = 1;
    
    for (i = 0; i < 5001; i++) {
        if (i % 100 == 0 && i % 200 != 0) {
            cnt = 0;
        } else if (i % 200 == 0 && i != 0) {
            cnt = 1;
        } 

        if (!cnt) {
            data[i] = 0xffffff;
        } else {
            data[i] = 0;
        }
    }
    
    if (init_flag == 0) {
        hal_irled_init(1);//WS2812B 0, UCS1903 1
        init_flag = 1;
    }

    for (i = 0; i < 1; i++) {
        hal_irled_send_data(5001, data);
    }

    return;
}

static void cmd_free(char *buf, int len, int argc, char **argv)
{
    printf("free memory is %d\r\n", xPortGetFreeHeapSize());
    printf("min free memory is %d\r\n", xPortGetMinimumEverFreeHeapSize());
}


const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_ir", "test ir led", test_irled},
    {"free", "free", cmd_free},
};

int irled_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
