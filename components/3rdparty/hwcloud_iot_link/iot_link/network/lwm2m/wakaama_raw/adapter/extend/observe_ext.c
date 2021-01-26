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

#define RES_M_STATE  3

static lwm2m_transaction_callback_t  observe_call_back;

void lwm2m_register_observe_ack_call_back(lwm2m_transaction_callback_t callback)
{
    observe_call_back = callback;
}

int observe_send_transaction(lwm2m_context_t *contextP, lwm2m_data_cfg_t  *cfg, lwm2m_watcher_t *watcherP,
                             uint8_t *buffer, size_t length)
{
    lwm2m_transaction_t *transaction;
    int ret;
    transaction = transaction_new(watcherP->server->sessionH, COAP_205_CONTENT, NULL, NULL, watcherP->lastMid, watcherP->tokenLen, watcherP->token);

    if (NULL == transaction)
    {
        LOG("transaction_new null");
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    transaction->cfg.callback = cfg->callback;
    transaction->cfg.cookie = cfg->cookie;
    transaction->cfg.type = cfg->type;
    transaction->callback = observe_call_back;
    coap_set_header_content_type(transaction->message, watcherP->format);
    coap_set_header_observe(transaction->message, watcherP->counter++);
    coap_set_payload(transaction->message, buffer, length);
    contextP->transactionList = (lwm2m_transaction_t *)LWM2M_LIST_ADD(contextP->transactionList, transaction);
    ret = transaction_send(contextP, transaction);
    LOG_ARG("notify con msg, cookie:%d type:%d,ret:%d", transaction->cfg.cookie, transaction->cfg.type, ret);
    return ret;
}

void observe_app_step(lwm2m_context_t *contextP,
                      lwm2m_observed_t *targetP,
                      time_t currentTime,
                      time_t *timeoutP)
{
    LOG("Entering");
    lwm2m_watcher_t *watcherP;
    uint8_t *buffer = NULL;
    size_t length = 0;
    lwm2m_data_t *dataP = NULL;
    lwm2m_data_cfg_t  cfg = {0, 0, NULL};
    int size = 0;

    while (COAP_205_CONTENT == object_readData(contextP, &targetP->uri, &size, &dataP, &cfg, 0))
    {
        for (watcherP = targetP->watcherList ; watcherP != NULL ; watcherP = watcherP->next)
        {
            int res;

            if (NULL == buffer)
            {
                res = lwm2m_data_serialize(&targetP->uri, size, dataP, &(watcherP->format), &buffer);

                if (res < 0)
                {
                    if (NULL != dataP)
                    {
                        lwm2m_data_free(size, dataP);
                        dataP = NULL;
                    }

                    if (NULL != buffer)
                    {
                        lwm2m_free(buffer);
                    }

                    break;
                }
                else
                {
                    length = (size_t)res;
                }
            }

            if (true == watcherP->active)
            {
                watcherP->lastTime = currentTime;
                watcherP->lastMid = contextP->nextMID++;

                if (NULL == cfg.callback)
                {
                    coap_packet_t message[1];
                    coap_init_message(message, COAP_TYPE_NON, COAP_205_CONTENT, 0);
                    coap_set_header_content_type(message, watcherP->format);
                    coap_set_payload(message, buffer, length);
                    message->mid = watcherP->lastMid;
                    coap_set_header_token(message, watcherP->token, watcherP->tokenLen);
                    coap_set_header_observe(message, watcherP->counter++);
                    (void)message_send(contextP, message, watcherP->server->sessionH);
                    LOG_ARG("notify no con msg, msgid:", message->mid);
                }
                else
                {
                    (void)observe_send_transaction(contextP, &cfg, watcherP, buffer, length);
                }
            }
        }

        if (NULL != dataP)
        {
            lwm2m_data_free(size, dataP);
            dataP = NULL;
        }

        if (NULL != buffer)
        {
            lwm2m_free(buffer);
            buffer = NULL;
        }
    }

    if (NULL != dataP)
    {
        lwm2m_data_free(size, dataP);
    }
}
uint8_t lwm2m_get_observe_info(lwm2m_context_t *contextP, lwm2m_observe_info_t *observe_info)
{
    lwm2m_observed_t *targetP;
    lwm2m_watcher_t *watcherP;

    if ((NULL == observe_info) || (NULL == contextP))
    {
        LOG("null pointer\n");
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    for (targetP = contextP->observedList ; NULL != targetP; targetP = targetP->next)
    {
        if ((!LWM2M_URI_IS_SET_RESOURCE(&targetP->uri))
            || (LWM2M_FIRMWARE_UPDATE_OBJECT_ID != targetP->uri.objectId)
            || (0 != targetP->uri.instanceId)
            || (RES_M_STATE != targetP->uri.resourceId))
        {
            continue;
        }

        watcherP = targetP->watcherList;
        observe_info->counter = watcherP->counter;
        (void) memcpy(observe_info->token, watcherP->token, sizeof(observe_info->token));
        observe_info->tokenLen = watcherP->tokenLen;
        observe_info->format = watcherP->format;
        return COAP_NO_ERROR;
    }

    return COAP_500_INTERNAL_SERVER_ERROR;
}

uint8_t lwm2m_send_notify(lwm2m_context_t *contextP, lwm2m_observe_info_t *observe_info, int firmware_update_state,  lwm2m_data_cfg_t  *cfg)
{
    lwm2m_uri_t uri;
    int res;
    lwm2m_data_t data;
    lwm2m_media_type_t format;
    uint8_t *buffer = NULL;
    lwm2m_server_t *server;
    lwm2m_watcher_t watcherP;

    if ((NULL == observe_info) || (NULL == contextP) || (NULL == cfg))
    {
        LOG("null pointer\n");
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    server = registration_get_registered_server(contextP);

    if (NULL == server)
    {
        LOG("registration_get_registered_server fail\n");
        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    uri.objectId = LWM2M_FIRMWARE_UPDATE_OBJECT_ID;
    uri.instanceId = 0;
    uri.resourceId = RES_M_STATE;
#ifndef LWM2M_VERSION_1_0
    uri.resourceInstanceId = LWM2M_MAX_ID;
#endif
    // uri.flag = (LWM2M_URI_FLAG_OBJECT_ID | LWM2M_URI_FLAG_INSTANCE_ID | LWM2M_URI_FLAG_RESOURCE_ID);
    format = (lwm2m_media_type_t)observe_info->format;
    (void) memset(&data, 0, sizeof(data));
    data.id = uri.resourceId;
    lwm2m_data_encode_int(firmware_update_state, &data);
    res = lwm2m_data_serialize(&uri, 1, &data, &format, &buffer);

    if (res < 0)
    {
        LOG("lwm2m_data_serialize fail\n");

        if (NULL != buffer)
        {
            lwm2m_free(buffer);
        }

        return COAP_500_INTERNAL_SERVER_ERROR;
    }

    (void) memset(&watcherP, 0, sizeof(watcherP));
    watcherP.lastMid = contextP->nextMID++;
    watcherP.tokenLen = observe_info->tokenLen;
    (void) memcpy(watcherP.token, observe_info->token, sizeof(watcherP.token));
    watcherP.format = format;
    watcherP.counter = observe_info->counter;
    watcherP.server = server;
    return (uint8_t)observe_send_transaction(contextP, cfg, &watcherP, buffer, res);
}

#endif // LWM2M_CLIENT_MODE
