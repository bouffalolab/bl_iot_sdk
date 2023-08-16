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
#include <rnm_server.h>
#include <stdio.h>
#include <string.h>

void rnms_handle_user_ext(rnms_t *rnm, rnm_msg_t *cmd)
{
    uint8_t msg_buf[256];
    rnm_user_ext_msg_t *rsp = (rnm_user_ext_msg_t *)msg_buf;
    rnm_user_ext_msg_t *msg = cmd->data;
    const char rsp_str[] = "response from device";

    // TODO Add your handler here
    rnm_warning("Recv user ext\r\n");
    if (!msg) {
        return;
    }
    printf("%s\r\n", msg->payload);

    memset(rsp, 0, sizeof(*rsp));
    // field cmd, session_id should be set
    // flag should be RNM_MSG_FLAG_ACK
    rnms_msg_fill_common(rnm, rsp, cmd);
    memcpy(rsp->payload, rsp_str, sizeof(rsp_str));

    rnms_msg_output(rnm, rsp, sizeof(*rsp) + sizeof(rsp_str));
}
