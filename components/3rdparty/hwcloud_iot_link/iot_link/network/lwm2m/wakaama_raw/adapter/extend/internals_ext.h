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

#ifndef __INTERNALS_EXT_H__
#define __INTERNALS_EXT_H__

#include "liblwm2m.h"

#include <ctype.h>  // isprint

#include "connection.h"

#include <osal.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#ifdef LWM2M_WITH_LOGS
// undef LOG (defined in internals.h)
#ifdef LOG
#undef LOG
#undef LOG_ARG
#undef LOG_URI
#endif

#define LOG(STR) (void)lwm2m_printf("[%d][%s:%d] " STR "\r\n", (uint32_t)lwm2m_gettime(), __func__ , __LINE__)
#define LOG_ARG(FMT, ...) (void)lwm2m_printf("[%d][%s:%d] " FMT "\r\n", (uint32_t)lwm2m_gettime(), __func__ , __LINE__ , __VA_ARGS__)
#define LOG_URI(URI)                                                                \
{                                                                                   \
    if (NULL == (URI)) (void)lwm2m_printf("[%s:%d] NULL\r\n", __func__ , __LINE__);     \
    else                                                                            \
    {                                                                               \
        (void)lwm2m_printf("[%s:%d] /%d", __func__ , __LINE__ , (URI)->objectId);       \
        if (LWM2M_URI_IS_SET_INSTANCE(URI)) (void)lwm2m_printf("/%d", (URI)->instanceId); \
        if (LWM2M_URI_IS_SET_RESOURCE(URI)) (void)lwm2m_printf("/%d", (URI)->resourceId); \
        (void)lwm2m_printf("\r\n");                                                       \
    }                                                                               \
}
#define UNUSEX(x)
#else
#define UNUSEX(x) (x)=(x)
#endif


// defined in registration_ext.c
void registration_reset(lwm2m_context_t *contextP, lwm2m_server_t *serverP);
lwm2m_server_t *registration_get_registered_server(lwm2m_context_t *contextP);


// defined in bootstrap_ext.c
bool bootstrap_isBsServerIpValid(const lwm2m_context_t *contextP);
void bootstrap_createBsConnection(lwm2m_context_t *contextP, lwm2m_server_t *targetP);


#ifdef LWM2M_CLIENT_MODE
// defined in observe_ext.c
int observe_send_transaction(lwm2m_context_t *contextP, lwm2m_data_cfg_t  *cfg, lwm2m_watcher_t *watcherP,
                             uint8_t *buffer, size_t length);

void observe_app_step(lwm2m_context_t *contextP,
                      lwm2m_observed_t *targetP,
                      time_t currentTime,
                      time_t *timeoutP);
#endif // LWM2M_CLIENT_MODE

static inline int dm_isUriOpaqueHandle(const lwm2m_uri_t *uriP)
{
    return (19 == uriP->objectId);
}

// defined in liblwm2m_ext.c
void lwm2m_reset_register(lwm2m_context_t *context);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __INTERNALS_EXT_H__ */

