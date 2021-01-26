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

void registration_reset(lwm2m_context_t *contextP,
                        lwm2m_server_t *serverP)
{
    //registration_deregister(contextP, serverP);
    if (NULL != serverP->sessionH)
    {
        lwm2m_close_connection(serverP->sessionH, contextP->userData);
        serverP->sessionH = NULL;
    }

    serverP->status = STATE_DEREGISTERED;
}

lwm2m_server_t *registration_get_registered_server(lwm2m_context_t *contextP)
{
    lwm2m_server_t *targetP;

    if (NULL == contextP)
    {
        LOG("null pointer");
        return NULL;
    }

    targetP = contextP->serverList;

    while (NULL != targetP)
    {
        if ((STATE_REGISTERED == targetP->status)
            || (STATE_REG_UPDATE_PENDING == targetP->status)
            || (STATE_REG_UPDATE_NEEDED == targetP->status)
            || (STATE_REG_FULL_UPDATE_NEEDED == targetP->status))
        {
            return targetP;
        }

        targetP = targetP->next;
    }

    return NULL;
}

#endif // LWM2M_CLIENT_MODE
