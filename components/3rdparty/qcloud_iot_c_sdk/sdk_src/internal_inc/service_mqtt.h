/*
 * Tencent is pleased to support the open source community by making IoT Hub available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IOT_SERVICE_COM_H_
#define IOT_SERVICE_COM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define FIELD_METHOD         	  	  "method"
#define METHOD_RES_REPORT_VERSION_RSP "report_version_rsp"
#define METHOD_RES_UPDATE_RESOURCE    "update_resource"
#define METHOD_RES_DELETE_RESOURCE    "del_resource"
#define METHOD_RES_REQ_URL_RESP       "request_url_resp"
#define METHOD_FACE_AI_REPLY       	  "call_service_reply"


typedef enum {
    eSERVICE_RESOURCE = 0,
    eSERVICE_FACE_AI  = 1,
    eSERVICE_DEFAULT  = 0xff
} eServiceEvent;

typedef void (*OnServiceMessageCallback)(void *pContext, const char *msg, uint32_t msgLen);

int qcloud_service_mqtt_init(const char *productId, const char *deviceName, void *mqtt_client);
void qcloud_service_mqtt_deinit(void *mqtt_client);
int qcloud_service_mqtt_post_msg(void *mqtt_client, const char *msg, int qos);
int qcloud_service_mqtt_event_register(eServiceEvent evt, OnServiceMessageCallback callback, void *context);

#ifdef __cplusplus
}
#endif

#endif /* IOT_SERVICE_COM_H_ */
