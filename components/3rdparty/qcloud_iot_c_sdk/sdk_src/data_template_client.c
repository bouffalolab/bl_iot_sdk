/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "data_template_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_template_action.h"
#include "data_template_client_common.h"
#include "data_template_client_json.h"
#include "qutils_param_check.h"
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

static void _init_request_params(RequestParams *pParams, Method method, OnReplyCallback callback, void *userContext,
                                 uint8_t timeout_sec)
{
    pParams->method           = method;
    pParams->user_context     = userContext;
    pParams->timeout_sec      = timeout_sec;
    pParams->request_callback = callback;
}

int IOT_Template_Publish(void *pClient, char *topicName, PublishParams *pParams)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    return qcloud_iot_mqtt_publish(pTemplate->mqtt, topicName, pParams);
}

int IOT_Template_Subscribe(void *pClient, char *topicFilter, SubscribeParams *pParams)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    return qcloud_iot_mqtt_subscribe(pTemplate->mqtt, topicFilter, pParams);
}

int IOT_Template_Unsubscribe(void *pClient, char *topicFilter)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    return qcloud_iot_mqtt_unsubscribe(pTemplate->mqtt, topicFilter);
}

bool IOT_Template_IsConnected(void *pClient)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    IOT_FUNC_EXIT_RC(IOT_MQTT_IsConnected(pTemplate->mqtt))
}

int IOT_Template_Set_DataTemplate(void *pClient, void *data_template, DataTemplateDestroyCb cb)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(data_template, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate   = (Qcloud_IoT_Template *)pClient;
    pTemplate->pDataTemplate         = data_template;
    pTemplate->DataTemplateDestroyCb = cb;

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS);
}

void *IOT_Template_Get_DataTemplate(void *pClient)
{
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    return (NULL != pTemplate) ? pTemplate->pDataTemplate : NULL;
}

int IOT_Template_Register_Property(void *pClient, DeviceProperty *pProperty, OnPropRegCallback callback)
{
    IOT_FUNC_ENTRY;
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    int                  rc;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    if (template_common_check_property_existence(pTemplate, pProperty))
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_PROPERTY_EXIST);

    rc = template_common_register_property_on_delta(pTemplate, pProperty, callback);

    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_UnRegister_Property(void *pClient, DeviceProperty *pProperty)
{
    IOT_FUNC_ENTRY;
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    if (!template_common_check_property_existence(pTemplate, pProperty)) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_NOT_PROPERTY_EXIST);
    }
    int rc = template_common_remove_property(pTemplate, pProperty);
    IOT_FUNC_EXIT_RC(rc);
}

#ifdef ACTION_ENABLED
int IOT_Template_Register_Action(void *pClient, DeviceAction *pAction, OnActionHandleCallback callback)
{
    IOT_FUNC_ENTRY;
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    int                  rc;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    rc = IOT_Action_Register(pTemplate, pAction, callback);
    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_UnRegister_Action(void *pClient, DeviceAction *pAction)
{
    IOT_FUNC_ENTRY;
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    int rc = IOT_Action_Remove(pTemplate, pAction);
    IOT_FUNC_EXIT_RC(rc);
}
#endif

static void _copy_template_init_params_to_mqtt(MQTTInitParams *pMqttInitParams, TemplateInitParams *templateInitParams)
{
    pMqttInitParams->region      = templateInitParams->region;
    pMqttInitParams->device_name = templateInitParams->device_name;
    pMqttInitParams->product_id  = templateInitParams->product_id;

#ifdef AUTH_MODE_CERT
    pMqttInitParams->cert_file = templateInitParams->cert_file;
    pMqttInitParams->key_file  = templateInitParams->key_file;
#else
    pMqttInitParams->device_secret = templateInitParams->device_secret;
#endif

    pMqttInitParams->command_timeout        = templateInitParams->command_timeout;
    pMqttInitParams->keep_alive_interval_ms = templateInitParams->keep_alive_interval_ms;
    pMqttInitParams->clean_session          = templateInitParams->clean_session;
    pMqttInitParams->auto_connect_enable    = templateInitParams->auto_connect_enable;
}

static void _reply_ack_cb(void *pClient, Method method, ReplyAck replyAck, const char *pReceivedJsonDocument,
                          void *pUserdata)
{
    Request *request = (Request *)pUserdata;
    Log_d("replyAck=%d", replyAck);

    if (NULL != pReceivedJsonDocument) {
        Log_d("Received Json Document=%s", pReceivedJsonDocument);
    } else {
        Log_d("Received Json Document is NULL");
    }

    *((ReplyAck *)(request->user_context)) = replyAck;
}

/*control data may be for get status replay*/
static void _get_status_reply_ack_cb(void *pClient, Method method, ReplyAck replyAck, const char *pReceivedJsonDocument,
                                     void *pUserdata)
{
    Request *request = (Request *)pUserdata;

    Log_d("replyAck=%d", replyAck);
    if (NULL == pReceivedJsonDocument) {
        Log_d("Received Json Document is NULL");
    } else {
        Log_d("Received Json Document=%s", pReceivedJsonDocument);
    }

    if (*((ReplyAck *)request->user_context) == ACK_ACCEPTED) {
        IOT_Template_ClearControl(pClient, request->client_token, NULL, QCLOUD_IOT_MQTT_COMMAND_TIMEOUT);
    } else {
        *((ReplyAck *)request->user_context) = replyAck;
    }
}

static int _template_ConstructControlReply(char *jsonBuffer, size_t sizeOfBuffer, sReplyPara *replyPara)
{
    POINTER_SANITY_CHECK(jsonBuffer, QCLOUD_ERR_INVAL);

    int     rc;
    size_t  remain_size = 0;
    int32_t rc_of_snprintf;

    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    rc_of_snprintf = HAL_Snprintf(jsonBuffer, remain_size, "{\"code\":%d, \"clientToken\":\"%s\",", replyPara->code,
                                  get_control_clientToken());
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    if (strlen(replyPara->status_msg) > 0) {
        rc_of_snprintf =
            HAL_Snprintf(jsonBuffer + strlen(jsonBuffer), remain_size, "\"status\":\"%s\"}", replyPara->status_msg);
    } else {
        rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, "}");
    }

    rc = check_snprintf_return(rc_of_snprintf, remain_size);

    return rc;
}

static void _template_mqtt_event_handler(void *pclient, void *context, MQTTEventMsg *msg)
{
    POINTER_SANITY_CHECK_RTN(context);
    uintptr_t            packet_id  = (uintptr_t)msg->msg;
    Qcloud_IoT_Template *pTemplate  = (Qcloud_IoT_Template *)context;
    MQTTMessage *        topic_info = (MQTTMessage *)msg->msg;

    if (pTemplate) {
        if (pclient != pTemplate->mqtt) {
            //Log_d("not template topic event");
            return;
        }
    }

    switch (msg->event_type) {
        case MQTT_EVENT_SUBCRIBE_SUCCESS:
            Log_d("template subscribe success, packet-id=%u", packet_id);
            if (pTemplate->inner_data.sync_status > 0)
                pTemplate->inner_data.sync_status = 0;
            break;
        case MQTT_EVENT_SUBCRIBE_TIMEOUT:
            Log_d("template subscribe wait ack timeout, packet-id=%u", packet_id);
            if (pTemplate->inner_data.sync_status > 0)
                pTemplate->inner_data.sync_status = -1;
            break;
        case MQTT_EVENT_SUBCRIBE_NACK:
            Log_d("template subscribe nack, packet-id=%u", packet_id);
            if (pTemplate->inner_data.sync_status > 0)
                pTemplate->inner_data.sync_status = -1;
            break;
        case MQTT_EVENT_PUBLISH_RECVEIVED:
            Log_d(
                "template topic message arrived but without any related pClient: "
                "topic=%.*s, topic_msg=%.*s",
                topic_info->topic_len, topic_info->ptopic, topic_info->payload_len, topic_info->payload);
            break;
        default:
            /* Log_i("Should NOT arrive here."); */
            break;
    }
    if (pTemplate->event_handle.h_fp != NULL) {
        pTemplate->event_handle.h_fp(pTemplate, pTemplate->event_handle.context, msg);
    }
}

int IOT_Template_JSON_ConstructReportArray(void *pClient, char *jsonBuffer, size_t sizeOfBuffer, uint8_t count,
        DeviceProperty *pDeviceProperties[])
{
    POINTER_SANITY_CHECK(jsonBuffer, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pDeviceProperties, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    POINTER_SANITY_CHECK(pTemplate, QCLOUD_ERR_INVAL);

    size_t  remain_size    = 0;
    int32_t rc_of_snprintf = 0;
    int     rc;
    int8_t  i;

    build_empty_json(&(pTemplate->inner_data.token_num), jsonBuffer, pTemplate->device_info.product_id);
    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, ", \"params\":{");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    for (i = 0; i < count; i++) {
        DeviceProperty *pJsonNode = pDeviceProperties[i];
        if (pJsonNode != NULL && pJsonNode->key != NULL) {
            rc = put_json_node(jsonBuffer, remain_size, pJsonNode);

            if (rc != QCLOUD_RET_SUCCESS) {
                return rc;
            }
        } else {
            return QCLOUD_ERR_INVAL;
        }
    }

    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }
    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, "}}");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("construct datatemplate report array failed: %d", rc);
        return rc;
    }

    return rc;
}

int IOT_Template_ClearControl(void *pClient, char *pClientToken, OnReplyCallback callback, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int  rc;
    char JsonDoc[MAX_CLEAE_DOC_LEN];

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pClientToken, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    // if topic $thing/down/property subscribe not success before, subsrcibe again
    if (pTemplate->inner_data.sync_status < 0) {
        rc = subscribe_template_downstream_topic(pTemplate);
        if (rc < 0) {
            Log_e("Subcribe $thing/down/property fail!");
        }
    }

    memset(JsonDoc, 0, MAX_CLEAE_DOC_LEN);
    int rc_of_snprintf = HAL_Snprintf(JsonDoc, MAX_CLEAE_DOC_LEN, "{\"clientToken\":\"%s\"}", pClientToken);
    rc                 = check_snprintf_return(rc_of_snprintf, MAX_CLEAE_DOC_LEN);
    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    RequestParams request_params = DEFAULT_REQUEST_PARAMS;
    _init_request_params(&request_params, CLEAR, callback, NULL, timeout_ms / 1000);

    rc = send_template_request(pTemplate, &request_params, JsonDoc, MAX_CLEAE_DOC_LEN);
    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_Report(void *pClient, char *pJsonDoc, size_t sizeOfBuffer, OnReplyCallback callback, void *userContext,
                        uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pJsonDoc, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    // if topic $thing/down/property subscribe not success before, subsrcibe again
    if (pTemplate->inner_data.sync_status < 0) {
        rc = subscribe_template_downstream_topic(pTemplate);
        if (rc < 0) {
            Log_e("Subcribe $thing/down/property fail!");
        }
    }

    // Log_d("Report Document: %s", pJsonDoc);

    RequestParams request_params = DEFAULT_REQUEST_PARAMS;
    _init_request_params(&request_params, REPORT, callback, userContext, timeout_ms / 1000);

    rc = send_template_request(pTemplate, &request_params, pJsonDoc, sizeOfBuffer);
    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_Report_Sync(void *pClient, char *pJsonDoc, size_t sizeOfBuffer, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc = QCLOUD_RET_SUCCESS;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pJsonDoc, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *template = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(template->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    ReplyAck ack_report = ACK_NONE;
    rc                  = IOT_Template_Report(pClient, pJsonDoc, sizeOfBuffer, _reply_ack_cb, &ack_report, timeout_ms);
    if (rc != QCLOUD_RET_SUCCESS)
        IOT_FUNC_EXIT_RC(rc);
    while (ACK_NONE == ack_report) {
        IOT_Template_Yield(pClient, 200);
    }

    if (ACK_ACCEPTED == ack_report) {
        rc = QCLOUD_RET_SUCCESS;
    } else if (ACK_TIMEOUT == ack_report) {
        rc = QCLOUD_ERR_REPORT_TIMEOUT;
    } else if (ACK_REJECTED == ack_report) {
        rc = QCLOUD_ERR_REPORT_REJECTED;
    }

    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_JSON_ConstructSysInfo(void *pClient, char *jsonBuffer, size_t sizeOfBuffer, DeviceProperty *pPlatInfo,
                                       DeviceProperty *pSelfInfo)
{
    POINTER_SANITY_CHECK(jsonBuffer, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pPlatInfo, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    POINTER_SANITY_CHECK(pTemplate, QCLOUD_ERR_INVAL);

    size_t  remain_size    = 0;
    int32_t rc_of_snprintf = 0;
    int     rc;

    build_empty_json(&(pTemplate->inner_data.token_num), jsonBuffer, pTemplate->device_info.product_id);
    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, ", \"params\":{");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    DeviceProperty *pJsonNode = pPlatInfo;
    while ((NULL != pJsonNode) && (NULL != pJsonNode->key)) {
        rc = put_json_node(jsonBuffer, remain_size, pJsonNode);
        if (rc != QCLOUD_RET_SUCCESS) {
            return rc;
        }
        pJsonNode++;
    }

    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }
    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, "},");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }

    pJsonNode = pSelfInfo;
    if ((NULL == pJsonNode) || (NULL == pJsonNode->key)) {
        Log_d("No self define info");
        goto end;
    }
    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 2, remain_size, ", \"device_label\":{");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

    while ((NULL != pJsonNode) && (NULL != pJsonNode->key)) {
        rc = put_json_node(jsonBuffer, remain_size, pJsonNode);
        if (rc != QCLOUD_RET_SUCCESS) {
            return rc;
        }
        pJsonNode++;
    }

    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, "}},");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);
    if (rc != QCLOUD_RET_SUCCESS) {
        return rc;
    }

end:
    if ((remain_size = sizeOfBuffer - strlen(jsonBuffer)) <= 1) {
        return QCLOUD_ERR_JSON_BUFFER_TOO_SMALL;
    }
    rc_of_snprintf = HAL_Snprintf(jsonBuffer + strlen(jsonBuffer) - 1, remain_size, "}");
    rc             = check_snprintf_return(rc_of_snprintf, remain_size);

    return rc;
}

int IOT_Template_Report_SysInfo(void *pClient, char *pJsonDoc, size_t sizeOfBuffer, OnReplyCallback callback,
                                void *userContext, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pJsonDoc, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    // if topic $thing/down/property subscribe not success before, subsrcibe again
    if (pTemplate->inner_data.sync_status < 0) {
        rc = subscribe_template_downstream_topic(pTemplate);
        if (rc < 0) {
            Log_e("Subcribe $thing/down/property fail!");
        }
    }

    // Log_d("eLOG_INFO Document: %s", pJsonDoc);

    RequestParams request_params = DEFAULT_REQUEST_PARAMS;
    _init_request_params(&request_params, RINFO, callback, userContext, timeout_ms / 1000);

    rc = send_template_request(pTemplate, &request_params, pJsonDoc, sizeOfBuffer);
    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_Report_SysInfo_Sync(void *pClient, char *pJsonDoc, size_t sizeOfBuffer, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc = QCLOUD_RET_SUCCESS;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pJsonDoc, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *template = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(template->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    ReplyAck ack_report = ACK_NONE;
    rc = IOT_Template_Report_SysInfo(pClient, pJsonDoc, sizeOfBuffer, _reply_ack_cb, &ack_report, timeout_ms);

    if (rc != QCLOUD_RET_SUCCESS)
        IOT_FUNC_EXIT_RC(rc);
    while (ACK_NONE == ack_report) {
        IOT_Template_Yield(pClient, 200);
    }

    if (ACK_ACCEPTED == ack_report) {
        rc = QCLOUD_RET_SUCCESS;
    } else if (ACK_TIMEOUT == ack_report) {
        rc = QCLOUD_ERR_REPORT_TIMEOUT;
    } else if (ACK_REJECTED == ack_report) {
        rc = QCLOUD_ERR_REPORT_REJECTED;
    }

    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_GetStatus(void *pClient, OnReplyCallback callback, void *userContext, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(callback, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    // if topic $thing/down/property subscribe not success before, subsrcibe again
    if (pTemplate->inner_data.sync_status < 0) {
        rc = subscribe_template_downstream_topic(pTemplate);
        if (rc < 0) {
            Log_e("Subcribe $thing/down/property fail!");
        }
    }

    char getRequestJsonDoc[MAX_SIZE_OF_JSON_WITH_CLIENT_TOKEN];
    build_empty_json(&(pTemplate->inner_data.token_num), getRequestJsonDoc, pTemplate->device_info.product_id);

    // Log_d("GET Status Document: %s", getRequestJsonDoc);

    RequestParams request_params = DEFAULT_REQUEST_PARAMS;
    _init_request_params(&request_params, GET, callback, userContext, timeout_ms / 1000);

    rc = send_template_request(pTemplate, &request_params, getRequestJsonDoc, MAX_SIZE_OF_JSON_WITH_CLIENT_TOKEN);
    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_GetStatus_sync(void *pClient, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc = QCLOUD_RET_SUCCESS;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    ReplyAck ack_request = ACK_NONE;
    rc                   = IOT_Template_GetStatus(pClient, _get_status_reply_ack_cb, &ack_request, timeout_ms);
    if (rc != QCLOUD_RET_SUCCESS)
        IOT_FUNC_EXIT_RC(rc);
    while (ACK_NONE == ack_request) {
        IOT_Template_Yield(pClient, 200);
    }

    if (ACK_ACCEPTED == ack_request) {
        rc = QCLOUD_RET_SUCCESS;
    } else if (ACK_TIMEOUT == ack_request) {
        rc = QCLOUD_ERR_GET_TIMEOUT;
    } else if (ACK_REJECTED == ack_request) {
        rc = QCLOUD_ERR_GET_REJECTED;
    }

    IOT_FUNC_EXIT_RC(rc);
}

int IOT_Template_ControlReply(void *pClient, char *pJsonDoc, size_t sizeOfBuffer, sReplyPara *replyPara)
{
    IOT_FUNC_ENTRY;
    int rc;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pJsonDoc, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    if (IOT_MQTT_IsConnected(pTemplate->mqtt) == false) {
        Log_e("template is disconnected");
        IOT_FUNC_EXIT_RC(QCLOUD_ERR_MQTT_NO_CONN);
    }

    // if topic $thing/down/property subscribe not success before, subsrcibe again
    if (pTemplate->inner_data.sync_status < 0) {
        rc = subscribe_template_downstream_topic(pTemplate);
        if (rc < 0) {
            Log_e("Subcribe $thing/down/property fail!");
        }
    }

    rc = _template_ConstructControlReply(pJsonDoc, sizeOfBuffer, replyPara);
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("Construct ControlReply fail,rc=%d", rc);
        return rc;
    }
    Log_d("Report Document: %s", pJsonDoc);

    RequestParams request_params = DEFAULT_REQUEST_PARAMS;
    _init_request_params(&request_params, REPLY, NULL, NULL, replyPara->timeout_ms / 1000);

    rc = send_template_request(pTemplate, &request_params, pJsonDoc, sizeOfBuffer);
    IOT_FUNC_EXIT_RC(rc);
}

#ifdef MULTITHREAD_ENABLED

int IOT_Template_Start_Yield_Thread(void *pClient)
{
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    int rc = IOT_MQTT_StartLoop(pTemplate->mqtt);
    if(QCLOUD_RET_SUCCESS == rc) {
        pTemplate->yield_thread_running = true;
    } else {
        pTemplate->yield_thread_running = false;
    }

    return rc;
}

void IOT_Template_Stop_Yield_Thread(void *pClient)
{
    POINTER_SANITY_CHECK_RTN(pClient);
    Qcloud_IoT_Template *pTemplate  = (Qcloud_IoT_Template *)pClient;

    IOT_MQTT_StopLoop(pTemplate->mqtt);
    pTemplate->yield_thread_running = false;
    HAL_SleepMs(1000);

    return;
}

bool IOT_Template_Get_Yield_Status(void *pClient, int *exit_code)
{
    POINTER_SANITY_CHECK(pClient, false);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    pTemplate->yield_thread_running = IOT_MQTT_GetLoopStatus(pTemplate->mqtt, exit_code);

    return pTemplate->yield_thread_running;
}

int IOT_Template_Destroy_Except_MQTT(void *pClient)
{
    IOT_FUNC_ENTRY;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    qcloud_iot_template_reset(pClient);

    if (NULL != pTemplate->DataTemplateDestroyCb) {
        pTemplate->DataTemplateDestroyCb(pClient);
    }

    if (NULL != pTemplate->mutex) {
        HAL_MutexDestroy(pTemplate->mutex);
    }

    if (NULL != pTemplate->inner_data.downstream_topic) {
        HAL_Free(pTemplate->inner_data.downstream_topic);
        pTemplate->inner_data.downstream_topic = NULL;
    }

    HAL_Free(pClient);

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS)
}
#endif


int IOT_Template_Yield(void *pClient, uint32_t timeout_ms)
{
    IOT_FUNC_ENTRY;
    int rc;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    NUMBERIC_SANITY_CHECK(timeout_ms, QCLOUD_ERR_INVAL);
    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    handle_template_expired_reply(pTemplate);

#ifdef EVENT_POST_ENABLED
    handle_template_expired_event(pTemplate);
#endif

    rc = IOT_MQTT_Yield(pTemplate->mqtt, timeout_ms);

    IOT_FUNC_EXIT_RC(rc);
}

void *IOT_Template_Get_MQTT_Client(void *pClient)
{
    POINTER_SANITY_CHECK(pClient, NULL);
    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;

    return pTemplate->mqtt;
}

void *IOT_Template_Construct(TemplateInitParams *pParams, void *pMqttClient)
{
    POINTER_SANITY_CHECK(pParams, NULL);
    int rc;

    Qcloud_IoT_Template *pTemplate = NULL;
    if ((pTemplate = (Qcloud_IoT_Template *)HAL_Malloc(sizeof(Qcloud_IoT_Template))) == NULL) {
        Log_e("memory not enough to malloc TemplateClient");
        return NULL;
    }

    MQTTInitParams mqtt_init_params;
    _copy_template_init_params_to_mqtt(&mqtt_init_params, pParams);

    mqtt_init_params.event_handle.h_fp    = _template_mqtt_event_handler;
    mqtt_init_params.event_handle.context = pTemplate;

    rc = iot_device_info_set(&pTemplate->device_info, pParams->product_id, pParams->device_name);
    if (rc != QCLOUD_RET_SUCCESS) {
        Log_e("failed to set device info: %d", rc);
        goto End;
    }

    void *mqtt_client = NULL;
    if (NULL == pMqttClient) {
        if ((mqtt_client = IOT_MQTT_Construct(&mqtt_init_params)) == NULL) {
            HAL_Free(pTemplate);
            goto End;
        }
    } else {  // multi dev share the same mqtt client
        mqtt_client = pMqttClient;
    }

#ifdef MULTITHREAD_ENABLED
    pTemplate->yield_thread_running = false;
#endif

    pTemplate->mqtt                        = mqtt_client;
    pTemplate->event_handle                = pParams->event_handle;	
	pTemplate->usr_control_handle          = pParams->usr_control_handle;
    pTemplate->inner_data.upstream_topic   = NULL;
    pTemplate->inner_data.downstream_topic = NULL;
    pTemplate->inner_data.token_num        = 0;
    pTemplate->inner_data.eventflags       = 0;

    rc = qcloud_iot_template_init(pTemplate);
    if (rc != QCLOUD_RET_SUCCESS) {
        IOT_MQTT_Destroy(&(pTemplate->mqtt));
        IOT_Template_Destroy(pTemplate);
        HAL_Free(pTemplate);
        goto End;
    }

    rc = subscribe_template_downstream_topic(pTemplate);
    if (rc < 0) {
        Log_e("Subcribe $thing/down/property fail!");
    } else {
        if (!pMqttClient) {
            pTemplate->inner_data.sync_status = rc;
            while (rc == pTemplate->inner_data.sync_status) {
                IOT_Template_Yield(pTemplate, 100);
            }

            if (0 == pTemplate->inner_data.sync_status) {
                Log_i("Sync device data successfully");
            } else {
                Log_e("Sync device data failed");
            }
        } else {
            pTemplate->inner_data.sync_status = 0;
        }
    }

#ifdef EVENT_POST_ENABLED
    rc = IOT_Event_Init(pTemplate);
    if (rc < 0) {
        Log_e("event init failed: %d", rc);
        IOT_Template_Destroy(pTemplate);
        goto End;
    }
#endif

#ifdef ACTION_ENABLED
    rc = IOT_Action_Init(pTemplate);
    if (rc < 0) {
        Log_e("action init failed: %d", rc);
        IOT_Template_Destroy(pTemplate);
        goto End;
    }
#endif

    return pTemplate;

End:

    return NULL;
}

int IOT_Template_Destroy(void *pClient)
{
    IOT_FUNC_ENTRY;

    POINTER_SANITY_CHECK(pClient, QCLOUD_ERR_INVAL);

    Qcloud_IoT_Template *pTemplate = (Qcloud_IoT_Template *)pClient;
    qcloud_iot_template_reset(pTemplate);
    IOT_MQTT_Destroy(&pTemplate->mqtt);

    if (NULL != pTemplate->mutex) {
        HAL_MutexDestroy(pTemplate->mutex);
    }

    if (NULL != pTemplate->inner_data.downstream_topic) {
        HAL_Free(pTemplate->inner_data.downstream_topic);
        pTemplate->inner_data.downstream_topic = NULL;
    }

    HAL_Free(pClient);

    IOT_FUNC_EXIT_RC(QCLOUD_RET_SUCCESS)
}
#ifdef __cplusplus
}
#endif
