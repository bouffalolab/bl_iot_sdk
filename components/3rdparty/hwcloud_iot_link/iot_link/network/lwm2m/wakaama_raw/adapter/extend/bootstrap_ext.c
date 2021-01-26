/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#include "internals.h"

#ifdef LWM2M_CLIENT_MODE
#ifdef LWM2M_BOOTSTRAP

void prv_resetBootstrapServer(lwm2m_server_t *serverP, void *userData)
{
    if (NULL != serverP->sessionH)
    {
        lwm2m_close_connection(serverP->sessionH, userData);
        serverP->sessionH = NULL;
    }

    free_block1_buffer(serverP->block1Data);
    serverP->block1Data = NULL;
}


void bootstrap_createBsConnection(lwm2m_context_t *contextP, lwm2m_server_t *targetP)
{
    prv_resetBootstrapServer(targetP, contextP->userData);
    targetP->sessionH = lwm2m_connect_server(targetP->secObjInstID, contextP->userData);
}


bool bootstrap_isBsServerIpValid(const lwm2m_context_t *contextP)
{
    lwm2m_server_t *targetP;
    targetP = contextP->bootstrapServerList;

    while (NULL != targetP)
    {
        if (lwm2m_is_sec_obj_uri_valid(targetP->secObjInstID, contextP->userData))
        {
            return true;
        }

        targetP = targetP->next;
    }

    return false;
}

#endif // LWM2M_BOOTSTRAP
#endif // LWM2M_CLIENT_MODE