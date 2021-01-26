/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
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

/*******************************************************************************
 *
 * Copyright (c) 2013, 2014 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    David Navarro, Intel Corporation - initial API and implementation
 *    Bosch Software Innovations GmbH - Please refer to git log
 *    Pascal Rieux - Please refer to git log
 *    Ville Skytt? - Please refer to git log
 *
 *******************************************************************************/

/*
 *  Resources:
 *
 *          Name            | ID | Operations | Instances | Mandatory |  Type   |  Range  | Units |
 *  Server URI              |  0 |            |  Single   |    Yes    | String  |         |       |
 *  Bootstrap Server        |  1 |            |  Single   |    Yes    | Boolean |         |       |
 *  Security Mode           |  2 |            |  Single   |    Yes    | Integer |   0-3   |       |
 *  Public Key or ID        |  3 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Server Public Key or ID |  4 |            |  Single   |    Yes    | Opaque  |         |       |
 *  Secret Key              |  5 |            |  Single   |    Yes    | Opaque  |         |       |
 *  SMS Security Mode       |  6 |            |  Single   |    No     | Integer |  0-255  |       |
 *  SMS Binding Key Param.  |  7 |            |  Single   |    No     | Opaque  |   6 B   |       |
 *  SMS Binding Secret Keys |  8 |            |  Single   |    No     | Opaque  | 32-48 B |       |
 *  Server SMS Number       |  9 |            |  Single   |    No     | String  |         |       |
 *  Short Server ID         | 10 |            |  Single   |    No     | Integer | 1-65535 |       |
 *  Client Hold Off Time    | 11 |            |  Single   |    No     | Integer |         |   s   |
 *  BS Account Timeout      | 12 |            |  Single   |    No     | Integer |         |   s   |
 *
 */

/*
 * Here we implement a very basic LWM2M Security Object which only knows NoSec security mode.
 */

#include "internals.h"
#include "object_comm.h"

#define URI_MAX_LEN (64)

static uint8_t prv_get_value(lwm2m_data_t *dataP,
                             security_instance_t *targetP)
{
    switch (dataP->id)
    {
        case LWM2M_SECURITY_URI_ID:
            lwm2m_data_encode_string(targetP->uri, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_BOOTSTRAP_ID:
            lwm2m_data_encode_bool(targetP->isBootstrap, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SECURITY_ID:
            lwm2m_data_encode_int(targetP->securityMode, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_PUBLIC_KEY_ID:
            lwm2m_data_encode_opaque((uint8_t *)targetP->publicIdentity, targetP->publicIdLen, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID:
            lwm2m_data_encode_opaque((uint8_t *)targetP->serverPublicKey, targetP->serverPublicKeyLen, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SECRET_KEY_ID:
            lwm2m_data_encode_opaque((uint8_t *)targetP->secretKey, targetP->secretKeyLen, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SMS_SECURITY_ID:
            lwm2m_data_encode_int(targetP->smsSecurityMode, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SMS_KEY_PARAM_ID:
            lwm2m_data_encode_opaque((uint8_t *)targetP->smsParams, targetP->smsParamsLen, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SMS_SECRET_KEY_ID:
            lwm2m_data_encode_opaque((uint8_t *)targetP->smsSecret, targetP->smsSecretLen, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SMS_SERVER_NUMBER_ID:
            lwm2m_data_encode_int(0, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_SHORT_SERVER_ID:
            lwm2m_data_encode_int(targetP->shortID, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_HOLD_OFF_ID:
            lwm2m_data_encode_int(targetP->clientHoldOffTime, dataP);
            return COAP_205_CONTENT;

        case LWM2M_SECURITY_BOOTSTRAP_TIMEOUT_ID:
            lwm2m_data_encode_int(targetP->bootstrapServerAccountTimeout, dataP);
            return COAP_205_CONTENT;

        default:
            return COAP_404_NOT_FOUND;
    }
}

static uint8_t prv_security_read(uint16_t instanceId,
                                 int *numDataP,
                                 lwm2m_data_t **dataArrayP,
                                 lwm2m_data_cfg_t *dataCfg,
                                 lwm2m_object_t *objectP)
{
    security_instance_t *targetP;
    uint8_t result;
    int i;
    targetP = (security_instance_t *)lwm2m_list_find(objectP->instanceList, instanceId);

    if (NULL == targetP) return COAP_404_NOT_FOUND;

    // is the server asking for the full instance ?
    if (0 == *numDataP)
    {
        uint16_t resList[] = {LWM2M_SECURITY_URI_ID,
                              LWM2M_SECURITY_BOOTSTRAP_ID,
                              LWM2M_SECURITY_SECURITY_ID,
                              LWM2M_SECURITY_PUBLIC_KEY_ID,
                              LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID,
                              LWM2M_SECURITY_SECRET_KEY_ID,
                              LWM2M_SECURITY_SMS_SECURITY_ID,
                              LWM2M_SECURITY_SMS_KEY_PARAM_ID,
                              LWM2M_SECURITY_SMS_SECRET_KEY_ID,
                              LWM2M_SECURITY_SMS_SERVER_NUMBER_ID,
                              LWM2M_SECURITY_SHORT_SERVER_ID,
                              LWM2M_SECURITY_HOLD_OFF_ID,
                              LWM2M_SECURITY_BOOTSTRAP_TIMEOUT_ID
                             };
        int nbRes = sizeof(resList) / sizeof(uint16_t);
        *dataArrayP = lwm2m_data_new(nbRes);

        if (NULL == *dataArrayP) return COAP_500_INTERNAL_SERVER_ERROR;

        *numDataP = nbRes;

        for (i = 0 ; i < nbRes ; i++)
        {
            (*dataArrayP)[i].id = resList[i];
        }
    }

    i = 0;

    do
    {
        result = prv_get_value((*dataArrayP) + i, targetP);
        i++;
    }
    while ((i < *numDataP) && (COAP_205_CONTENT == result));

    return result;
}

#ifdef LWM2M_BOOTSTRAP

//static const *s_bs_test_uri = "coap://49.4.85.232:5683";


static uint8_t prv_security_write(uint16_t instanceId,
                                  int numData,
                                  lwm2m_data_t *dataArray,
                                  lwm2m_object_t *objectP)
{
    security_instance_t *targetP;
    int i;
    uint8_t result = COAP_204_CHANGED;
    targetP = (security_instance_t *)lwm2m_list_find(objectP->instanceList, instanceId);

    if (NULL == targetP)
    {
        return COAP_404_NOT_FOUND;
    }

    i = 0;

    do
    {
        switch (dataArray[i].id)
        {
            case LWM2M_SECURITY_URI_ID:
                if (NULL != targetP->uri) lwm2m_free(targetP->uri);

                targetP->uri = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length + 1);

                if (NULL != targetP->uri)
                {
                    (void) memset(targetP->uri, 0, dataArray[i].value.asBuffer.length + 1);
                    (void) strncpy(targetP->uri, (char *)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
                    result = COAP_204_CHANGED;
                }
                //            targetP->uri = (char *)lwm2m_malloc(strlen(s_bs_test_uri) + 1); ///--TODO, do the test
                //            if (targetP->uri != NULL)
                //            {
                //                (void) strncpy(targetP->uri, (char *)s_bs_test_uri, strlen(s_bs_test_uri) + 1);
                //                result = COAP_204_CHANGED;
                //            }
                else
                {
                    result = COAP_500_INTERNAL_SERVER_ERROR;
                }

                break;

            case LWM2M_SECURITY_BOOTSTRAP_ID:
                if (1 == lwm2m_data_decode_bool(dataArray + i, &(targetP->isBootstrap)))
                {
                    result = COAP_204_CHANGED;
                }
                else
                {
                    result = COAP_400_BAD_REQUEST;
                }

                break;

            case LWM2M_SECURITY_SECURITY_ID:
            {
                int64_t value;

                if (1 == lwm2m_data_decode_int(dataArray + i, &value))
                {
                    if (value >= 0 && value <= 3)
                    {
                        targetP->securityMode = value;
                        result = COAP_204_CHANGED;
                    }
                    else
                    {
                        result = COAP_406_NOT_ACCEPTABLE;
                    }
                }
                else
                {
                    result = COAP_400_BAD_REQUEST;
                }
            }
            break;

            case LWM2M_SECURITY_PUBLIC_KEY_ID:
                if (NULL != targetP->publicIdentity) lwm2m_free(targetP->publicIdentity);

                targetP->publicIdentity = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length + 1);

                if (NULL != targetP->publicIdentity)
                {
                    (void) memset(targetP->publicIdentity, 0, dataArray[i].value.asBuffer.length + 1);
                    (void) memcpy(targetP->publicIdentity, (char *)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
                    targetP->publicIdLen = dataArray[i].value.asBuffer.length;
                    result = COAP_204_CHANGED;
                }
                else
                {
                    result = COAP_500_INTERNAL_SERVER_ERROR;
                }

                break;

            case LWM2M_SECURITY_SERVER_PUBLIC_KEY_ID:
                if (NULL != targetP->serverPublicKey) lwm2m_free(targetP->serverPublicKey);

                targetP->serverPublicKey = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length + 1);

                if (NULL != targetP->serverPublicKey)
                {
                    (void) memset(targetP->serverPublicKey, 0, dataArray[i].value.asBuffer.length + 1);
                    (void) memcpy(targetP->serverPublicKey, (char *)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
                    targetP->serverPublicKeyLen = dataArray[i].value.asBuffer.length;
                    result = COAP_204_CHANGED;
                }
                else
                {
                    result = COAP_500_INTERNAL_SERVER_ERROR;
                }

                break;

            case LWM2M_SECURITY_SECRET_KEY_ID:
                if (NULL != targetP->secretKey) lwm2m_free(targetP->secretKey);

                targetP->secretKey = (char *)lwm2m_malloc(dataArray[i].value.asBuffer.length + 1);

                if (NULL != targetP->secretKey)
                {
                    (void) memset(targetP->secretKey, 0, dataArray[i].value.asBuffer.length + 1);
                    (void) memcpy(targetP->secretKey, (char *)dataArray[i].value.asBuffer.buffer, dataArray[i].value.asBuffer.length);
                    targetP->secretKeyLen = dataArray[i].value.asBuffer.length;
                    result = COAP_204_CHANGED;
                }
                else
                {
                    result = COAP_500_INTERNAL_SERVER_ERROR;
                }

                break;

            case LWM2M_SECURITY_SMS_SECURITY_ID:
                // Let just ignore this
                result = COAP_204_CHANGED;
                break;

            case LWM2M_SECURITY_SMS_KEY_PARAM_ID:
                // Let just ignore this
                result = COAP_204_CHANGED;
                break;

            case LWM2M_SECURITY_SMS_SECRET_KEY_ID:
                // Let just ignore this
                result = COAP_204_CHANGED;
                break;

            case LWM2M_SECURITY_SMS_SERVER_NUMBER_ID:
                // Let just ignore this
                result = COAP_204_CHANGED;
                break;

            case LWM2M_SECURITY_SHORT_SERVER_ID:
            {
                int64_t value;

                if (1 == lwm2m_data_decode_int(dataArray + i, &value))
                {
                    if (value >= 0 && value <= 0xFFFF)
                    {
                        targetP->shortID = value;
                        result = COAP_204_CHANGED;
                    }
                    else
                    {
                        result = COAP_406_NOT_ACCEPTABLE;
                    }
                }
                else
                {
                    result = COAP_400_BAD_REQUEST;
                }
            }
            break;

            case LWM2M_SECURITY_HOLD_OFF_ID:
            {
                int64_t value;

                if (1 == lwm2m_data_decode_int(dataArray + i, &value))
                {
                    if (value >= 0 && value <= UINT32_MAX)
                    {
                        targetP->clientHoldOffTime = value;
                        result = COAP_204_CHANGED;
                    }
                    else
                    {
                        result = COAP_406_NOT_ACCEPTABLE;
                    }
                }
                else
                {
                    result = COAP_400_BAD_REQUEST;
                }

                break;
            }

            case LWM2M_SECURITY_BOOTSTRAP_TIMEOUT_ID:
            {
                int64_t value;

                if (1 == lwm2m_data_decode_int(dataArray + i, &value))
                {
                    if (value >= 0 && value <= UINT32_MAX)
                    {
                        targetP->bootstrapServerAccountTimeout = value;
                        result = COAP_204_CHANGED;
                    }
                    else
                    {
                        result = COAP_406_NOT_ACCEPTABLE;
                    }
                }
                else
                {
                    result = COAP_400_BAD_REQUEST;
                }

                break;
            }

            default:
                return COAP_400_BAD_REQUEST;
        }

        i++;
    }
    while ((i < numData) && (COAP_204_CHANGED == result));

    return result;
}

static uint8_t prv_security_delete(uint16_t id,
                                   lwm2m_object_t *objectP)
{
    security_instance_t *targetP;
    objectP->instanceList = lwm2m_list_remove(objectP->instanceList, id, (lwm2m_list_t **)&targetP);

    if (NULL == targetP) return COAP_404_NOT_FOUND;

    if (NULL != targetP->uri)
    {
        lwm2m_free(targetP->uri);
    }

    lwm2m_free(targetP);
    return COAP_202_DELETED;
}

static uint8_t prv_security_create(uint16_t instanceId,
                                   int numData,
                                   lwm2m_data_t *dataArray,
                                   lwm2m_object_t *objectP)
{
    security_instance_t *targetP;
    uint8_t result;
    targetP = (security_instance_t *)lwm2m_malloc(sizeof(security_instance_t));

    if (NULL == targetP) return COAP_500_INTERNAL_SERVER_ERROR;

    (void) memset(targetP, 0, sizeof(security_instance_t));
    targetP->instanceId = instanceId;
    objectP->instanceList = LWM2M_LIST_ADD(objectP->instanceList, targetP);
    result = prv_security_write(instanceId, numData, dataArray, objectP);

    if (COAP_204_CHANGED != result)
    {
        (void)prv_security_delete(instanceId, objectP);
    }
    else
    {
        targetP->shortID =  123;
        result = COAP_201_CREATED;
    }

    return result;
}
#endif

void copy_security_object(lwm2m_object_t *objectDest, lwm2m_object_t *objectSrc)
{
    security_instance_t *instanceSrc;
    security_instance_t *previousInstanceDest = NULL;
    (void) memcpy(objectDest, objectSrc, sizeof(lwm2m_object_t));
    objectDest->instanceList = NULL;
    objectDest->userData = NULL;
    instanceSrc = (security_instance_t *)objectSrc->instanceList;

    while (NULL != instanceSrc)
    {
        security_instance_t *instanceDest = (security_instance_t *)lwm2m_malloc(sizeof(security_instance_t));

        if (NULL == instanceDest)
        {
            return;
        }

        (void) memcpy(instanceDest, instanceSrc, sizeof(security_instance_t));
        instanceDest->uri = (char *)lwm2m_malloc(strlen(instanceSrc->uri) + 1);

        if (NULL == instanceDest->uri)
        {
            lwm2m_free(instanceDest);
            return;
        }

        (void) strncpy(instanceDest->uri, instanceSrc->uri, strlen(instanceSrc->uri) + 1);

        if (LWM2M_SECURITY_MODE_PRE_SHARED_KEY == instanceSrc->securityMode)
        {
            instanceDest->publicIdentity = lwm2m_strdup(instanceSrc->publicIdentity);
            instanceDest->secretKey = lwm2m_strdup(instanceSrc->secretKey);
        }

        instanceSrc = (security_instance_t *)instanceSrc->next;

        if (NULL == previousInstanceDest)
        {
            objectDest->instanceList = (lwm2m_list_t *)instanceDest;
        }
        else
        {
            previousInstanceDest->next = instanceDest;
        }

        previousInstanceDest = instanceDest;
    }
}

void display_security_object(lwm2m_object_t *object)
{
#ifdef WITH_LOGS
    fprintf(stdout, "  /%u: Security object, instances:\r\n", object->objID);
    security_instance_t *instance = (security_instance_t *)object->instanceList;

    while (NULL != instance)
    {
        fprintf(stdout, "    /%u/%u: instanceId: %u, uri: %s, isBootstrap: %s, shortId: %u, clientHoldOffTime: %u\r\n",
                object->objID, instance->instanceId,
                instance->instanceId, instance->uri, instance->isBootstrap ? "true" : "false",
                instance->shortID, instance->clientHoldOffTime);
        instance = (security_instance_t *)instance->next;
    }

#endif
}

void clean_security_object(lwm2m_object_t *objectP)
{
    if (NULL == objectP)
    {
        return;
    }

    while (objectP->instanceList != NULL)
    {
        security_instance_t *securityInstance = (security_instance_t *)objectP->instanceList;
        objectP->instanceList = objectP->instanceList->next;

        if (NULL != securityInstance->uri)
        {
            lwm2m_free(securityInstance->uri);
        }

        if (LWM2M_SECURITY_MODE_PRE_SHARED_KEY == securityInstance->securityMode)
        {
            lwm2m_free(securityInstance->publicIdentity);
            lwm2m_free(securityInstance->secretKey);
        }

        lwm2m_free(securityInstance);
    }

    lwm2m_free(objectP);
}

int add_security_object_instance(lwm2m_object_t *obj, int object_instance_id, void *param)
{
    security_instance_t *instance = NULL;
    lwm2m_al_sec_obj_param_t *sec_param = (lwm2m_al_sec_obj_param_t *)param;
    char serverUri[URI_MAX_LEN];

    if ((NULL == obj) || (NULL == param))
    {
        return (int)LWM2M_ARG_INVALID;
    }

    instance = (security_instance_t *)lwm2m_malloc(sizeof(security_instance_t));

    if (NULL == instance)
    {
        return (int)LWM2M_MALLOC_FAILED;
    }

    (void) memset(instance, 0, sizeof(security_instance_t));
    instance->instanceId = object_instance_id;   //i=0 for iot_server, i=1 for bs_server
    instance->isBootstrap = sec_param->is_bootstrap;

    if (sec_param->server_ip && sec_param->server_port)
    {
        if (NULL != sec_param->psk)
        {
            (void)snprintf(serverUri, URI_MAX_LEN, "coaps://%s:%s", sec_param->server_ip, sec_param->server_port);
        }
        else
        {
            (void)snprintf(serverUri, URI_MAX_LEN, "coap://%s:%s", sec_param->server_ip, sec_param->server_port);
        }
    }
    else
    {
        serverUri[0] = '\0';
    }

    instance->uri = (char *)lwm2m_strdup(serverUri);

    if (NULL == instance->uri)
    {
        lwm2m_free(instance);
        return (int)LWM2M_MALLOC_FAILED;
    }

    instance->securityMode = LWM2M_SECURITY_MODE_NONE;

    if ((NULL != sec_param->psk_id) && (NULL != sec_param->psk))
    {
        instance->securityMode = LWM2M_SECURITY_MODE_PRE_SHARED_KEY;
        instance->publicIdentity = (char *)lwm2m_strdup(sec_param->psk_id);

        if (NULL == instance->publicIdentity)
        {
            lwm2m_free(instance->uri);
            lwm2m_free(instance);
            return (int)LWM2M_MALLOC_FAILED;
        }

        instance->publicIdLen = strlen(sec_param->psk_id);

        if (sec_param->psk_len > 0)
        {
            instance->secretKey = (char *)lwm2m_malloc(sec_param->psk_len);

            if (NULL == instance->secretKey)
            {
                lwm2m_free(instance->uri);
                lwm2m_free(instance->publicIdentity);
                lwm2m_free(instance);
                return LWM2M_MALLOC_FAILED;
            }

            (void) memcpy(instance->secretKey, sec_param->psk, sec_param->psk_len);
            instance->secretKeyLen = sec_param->psk_len;
        }
    }

    instance->shortID = sec_param->server_id;
    //10? is suitable? it could be changed by the bs server. for lwm2m_server_t member lifetime.
    instance->clientHoldOffTime = sec_param->hold_off_time;
    // After instance id is initialized
    obj->instanceList = LWM2M_LIST_ADD(obj->instanceList, instance);
    return (int)LWM2M_OK;
}

int config_security_object(lwm2m_object_t *obj, void *param)
{
    if (NULL == obj)
    {
        return LWM2M_ARG_INVALID;
    }

    obj->readFunc = prv_security_read;
#ifdef LWM2M_BOOTSTRAP
    obj->writeFunc = prv_security_write;
    obj->createFunc = prv_security_create;
    obj->deleteFunc = prv_security_delete;
#endif
    return (int)LWM2M_OK;
}

/********************* Security Obj Helpers **********************/

char *security_get_uri(lwm2m_object_t *objectP, uint16_t secObjInstID)
{
    security_instance_t *targetP = (security_instance_t *)LWM2M_LIST_FIND(objectP->instanceList, secObjInstID);

    if (NULL != targetP)
    {
        return lwm2m_strdup(targetP->uri);
    }

    return NULL;
}
