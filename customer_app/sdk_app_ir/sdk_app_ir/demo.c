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

/*NOTE: 
 * The order of IR sending data is LSB, 
 * but the order required by the chip WS2812B and UCS1903 is MSB, 
 * so here needs to be converted.
 * */

static void convert_data(uint32_t *data, int length)
{
    int i = 0;

    for (i = 0; i < length; i++) {
        /* Change MSB_first to LSB_first */
        data[i] = ((data[i] >> 1) & 0x55555555) | ((data[i] << 1) & 0xaaaaaaaa);
        data[i] = ((data[i] >> 2) & 0x33333333) | ((data[i] << 2) & 0xcccccccc);
        data[i] = ((data[i] >> 4) & 0x0f0f0f0f) | ((data[i] << 4) & 0xf0f0f0f0);
        data[i] = ((data[i] >> 16) & 0xff) | (data[i] & 0xff00) | ((data[i] << 16) & 0xff0000);
    }

    return;
}

static void test_irled(char *buf, int len, int argc, char **argv)
{
    uint32_t data[13];
    int i;

    for (i = 0; i < 13; i++) {
        data[i] = 0x3f;
    }
    
    convert_data(data, 13);
    hal_irled_init(1);//WS2812B 0, UCS1903 1

    hal_irled_send_data(13, data);
    hal_irled_send_data(13, data);
    hal_irled_send_data(13, data);

    return;
}


const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_ir", "test ir led", test_irled},
};

int irled_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
