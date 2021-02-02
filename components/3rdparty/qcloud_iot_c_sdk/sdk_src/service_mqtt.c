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

#include <string.h>
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"
#include "mqtt_client.h"
#include "service_mqtt.h"
#include "json_parser.h"


typedef struct {
    eServiceEvent eventid;
    OnServiceMessageCallback callback;
    void *context;
} Service_Event_Struct_t;

static Service_Event_Struct_t sg_service_event_map[] = {
    {eSERVICE_RESOURCE,  NULL, NULL},
    {eSERVICE_FACE_AI,   NULL, NULL}
};

static char sg_service_pub_topic[MAX_SIZE_OF_CLOUD_TOPIC];

/* gen service topic: "$thing/down/service/$(product_id)/$(device_name)" */
static int _gen_service_mqtt_topic_info(const char *productId, const char *deviceName, char *sub_topic)
{
	int ret;
	
    memset(sg_service_pub_topic, '\0', MAX_SIZE_OF_CLOUD_TOPIC);
    ret = HAL_Snprintf(sg_service_pub_topic, MAX_SIZE_OF_CLOUD_TOPIC, "$thing/up/service/%s/%s",
                       STRING_PTR_PRINT_SANITY_CHECK(productId), STRING_PTR_PRINT_SANITY_CHECK(deviceName));
    if (ret < 0) {
        goto exit;
    }
    ret = HAL_Snprintf(sub_topic, MAX_SIZE_OF_CLOUD_TOPIC, "$thing/down/service/%s/%s",
                       STRING_PTR_PRINT_SANITY_CHECK(productId), STRING_PTR_PRINT_SANITY_CHECK(deviceName));

exit:

	return ret;
}

static char *_get_service_mqtt_topic_info(void)
{
    return sg_service_pub_topic;
}

static Service_Event_Struct_t *_get_service_event_handle(eServiceEvent evt)
{
    if ( evt >= sizeof(sg_service_event_map) / sizeof(sg_service_event_map[0])) {
        return NULL;
    }

    return &sg_service_event_map[evt];
}

static int _set_service_event_handle(eServiceEvent evt, OnServiceMessageCallback callback, void *context)
{
    if (evt >= sizeof(sg_service_event_map) / sizeof(sg_service_event_map[0])) {
        return QCLOUD_ERR_INVAL;
    }

    sg_service_event_map[evt].callback = callback;
    sg_service_event_map[evt].context = context;

    return QCLOUD_RET_SUCCESS;
}

static eServiceEvent _service_mqtt_parse_event(char *method)
{
	eServiceEvent evt;

    if (!strcmp(method, METHOD_RES_REPORT_VERSION_RSP) || !strcmp(method, METHOD_RES_UPDATE_RESOURCE) ||
        !strcmp(method, METHOD_RES_DELETE_RESOURCE) || !strcmp(method, METHOD_RES_REQ_URL_RESP)) {
        evt = eSERVICE_RESOURCE;
    } else if (!strcmp(method, METHOD_FACE_AI_REPLY)) {
        evt = eSERVICE_FACE_AI;
    } else {
        Log_i("not support service method %s", STRING_PTR_PRINT_SANITY_CHECK(method));
        evt = eSERVICE_DEFAULT;
    }

	return evt;
}

/* callback after resource topic is subscribed */
static void _service_mqtt_cb(void *pClient, MQTTMessage *message, void *pContext)
{
	int len = message->payload_len;

    Log_d("topic=%.*s", message->topic_len, message->ptopic);
    Log_d("len=%u, topic_msg=%.*s", message->payload_len, message->payload_len, (char *)message->payload);
	
    //parse msg and dispatch to event callback according to sg_service_event_map 
    char *recv_payload = HAL_Malloc(message->payload_len + 1);
	if(!recv_payload){
		Log_e("malloc %dbytes mem fail", message->payload_len);
		return;
	}	
	memset(recv_payload, '\0', len + 1);
	strncpy(recv_payload, message->payload, len);
    char * json_method = LITE_json_value_of(FIELD_METHOD, recv_payload);
	if(json_method){
		eServiceEvent event = _service_mqtt_parse_event(json_method);
	    Service_Event_Struct_t *handle = _get_service_event_handle(event);
	    if(handle->callback) {
	        handle->callback(handle->context, recv_payload, len);
	    }
		HAL_Free(json_method);
	}else{
		Log_e("no method found");
	}

	HAL_Free(recv_payload);
}

static int _service_mqtt_publish(void *mqtt_client, int qos, const char *msg)
{
    int  ret;
    PublishParams pub_params = DEFAULT_PUB_PARAMS;

    if (0 == qos) {
        pub_params.qos = QOS0;
    } else {
        pub_params.qos = QOS1;
    }
    pub_params.payload     = (void *)msg;
    pub_params.payload_len = strlen(msg);
    ret = IOT_MQTT_Publish(mqtt_client, _get_service_mqtt_topic_info(), &pub_params);
    if (ret < 0) {
        Log_e("publish to topic: %s failed", _get_service_mqtt_topic_info());
    }

    return ret;
}

static void _service_mqtt_sub_event_handler(void *pClient, MQTTEventType event_type, void *pUserData)
{
    switch (event_type) {
        case MQTT_EVENT_SUBCRIBE_SUCCESS:
            Log_d("resource topic subscribe success");
            break;

        case MQTT_EVENT_SUBCRIBE_TIMEOUT:
            Log_i("resource topic subscribe timeout");
            break;

        case MQTT_EVENT_SUBCRIBE_NACK:
            Log_i("resource topic subscribe NACK");
            break;
        case MQTT_EVENT_UNSUBSCRIBE:
            Log_i("resource topic has been unsubscribed");
            break;
        case MQTT_EVENT_CLIENT_DESTROY:
            Log_i("mqtt client has been destroyed");
            break;

        default:
            return;
    }
}

int qcloud_service_mqtt_init(const char *productId, const char *deviceName, void *mqtt_client)
{
    int ret;

	char topic_name[MAX_SIZE_OF_CLOUD_TOPIC];
	memset(topic_name, '\0', MAX_SIZE_OF_CLOUD_TOPIC);
	ret = _gen_service_mqtt_topic_info(productId, deviceName, topic_name);
	if(ret < 0){
		Log_e("gen service topic fail");
	}

    if (IOT_MQTT_IsSubReady(mqtt_client, topic_name)) {
        Log_d("%s has been already subscribed", topic_name);
        return QCLOUD_RET_SUCCESS;
    }

    SubscribeParams sub_params      = DEFAULT_SUB_PARAMS;
    sub_params.on_message_handler   = _service_mqtt_cb;
    sub_params.on_sub_event_handler = _service_mqtt_sub_event_handler;
    sub_params.qos                  = QOS1;
	
    ret = IOT_MQTT_Subscribe(mqtt_client, topic_name, &sub_params);
    if (ret < 0) {
        Log_e("service topic subscribe failed!");
		return QCLOUD_ERR_FAILURE;
    }	
    
	int wait_cnt = 10;
    while (!IOT_MQTT_IsSubReady(mqtt_client, topic_name) && (wait_cnt > 0)) {
        // wait for subscription result
        ret = IOT_MQTT_Yield(mqtt_client, 1000);
        if (ret) {
            Log_e("mqtt yield error: %d", ret);
            return ret;
        }
        wait_cnt--;
    }

    if (wait_cnt == 0) {
        Log_e("service topic subscribe timeout!");
         return QCLOUD_ERR_FAILURE;
    }

    return QCLOUD_RET_SUCCESS;	
}

void qcloud_service_mqtt_deinit(void *mqtt_client)
{
    if (mqtt_client) {
        IOT_MQTT_Unsubscribe(mqtt_client, _get_service_mqtt_topic_info());
    }
}

int qcloud_service_mqtt_post_msg(void *mqtt_client, const char *msg, int qos)
{
    return _service_mqtt_publish(mqtt_client, qos, msg);
}

int qcloud_service_mqtt_event_register(eServiceEvent evt, OnServiceMessageCallback callback, void *context)
{	
	return _set_service_event_handle(evt, callback, context);
}

#ifdef __cplusplus
}
#endif
