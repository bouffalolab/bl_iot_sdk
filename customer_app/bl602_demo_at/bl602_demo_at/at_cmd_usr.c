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
#include "atcmd/at_command.h"
#include "at_debug.h"
#include "at_private.h"
#include <cJSON.h>
#include <FreeRTOS.h>

typedef struct {
  int       arg1;
  at_text_t arg2[64];
} at_test_para_t;

static AT_ERROR_CODE __usr_at_cmd_demo(at_para_t *at_para) {
    s32 paracnt;
    int res;
    at_test_para_t para = {0};
    at_para_descriptor_t cmd_para_list[] = {
        {APT_DI, &para.arg1, AET_PARA | AET_LINE | SIZE_LIMIT(sizeof(para.arg1))},
        {APT_TEXT, &para.arg2, AET_PARA | AET_LINE | SIZE_LIMIT(sizeof(para.arg2))},
    };

    if (*at_para->ptr == AT_QUE) {
      at_dump("TEST AT ? SUCCESSFUL");
      return AEC_OK;
    } else if (*at_para->ptr == AT_EQU) {
      at_para->ptr++; /* skip '=' */

      res = at_get_parameters(&at_para->ptr, cmd_para_list,
                              TABLE_SIZE(cmd_para_list), &paracnt);

      if (res != AEC_OK) {
        return AEC_PARA_ERROR;
      }
      at_dump("TEST AT %d %s SUCCESSFUL", para.arg1, para.arg2);
      return AEC_OK;
    }

    return AEC_OK;
}

static const at_command_handler_t g_at_cmd_usr[] = {
    {"AT+TEST", __usr_at_cmd_demo, "=[arg1],[arg2] -- Usr at cmd demo"},
};

void usr_at_cmd_register(void)
{
    at_command_register(g_at_cmd_usr, TABLE_SIZE(g_at_cmd_usr));
}
