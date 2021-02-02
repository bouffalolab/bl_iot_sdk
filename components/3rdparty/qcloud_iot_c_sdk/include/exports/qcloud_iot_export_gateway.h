
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

#ifndef QCLOUD_IOT_EXPORT_GATEWAY_H_
#define QCLOUD_IOT_EXPORT_GATEWAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "qcloud_iot_export_mqtt.h"

/* Gateway and sub-device parameter */
typedef struct {
    /*gateway device info */
    char *product_id;
    char *device_name;
    /*sub-device device info */
    char *subdev_product_id;
    char *subdev_device_name;

} GatewayParam;

#define DEFAULT_GATEWAY_PARAMS \
    {                          \
        NULL, NULL, NULL, NULL \
    }

/**
 * @brief Define a callback to be invoked when gatway event happen
 *
 * @param context, the program context
 * @param client, the gateway client
 * @param msg, the event message.
 *
 * @return none
 */
typedef void (*GatewayEventHandleFun)(void *client, void *context, void *msg);

/* The structure of gateway init param */
typedef struct {
    MQTTInitParams        init_param;    /* MQTT params */
    void *                event_context; /* the user context */
    GatewayEventHandleFun event_handler; /* event handler for gateway user*/
} GatewayInitParam;

#define DEFAULT_GATEWAY_INIT_PARAMS         \
    {                                       \
        DEFAULT_MQTTINIT_PARAMS, NULL, NULL \
    }

/**
 * @brief Create gateway client and connect to MQTT server
 *
 * @param init_param Gateway MQTT init parameters
 *
 * @return a valid gateway client handle when success, or NULL otherwise
 */
void *IOT_Gateway_Construct(GatewayInitParam *init_param);

/**
 * @brief Close connection and destroy gateway client
 *
 * @param client    handle to gateway client
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int IOT_Gateway_Destroy(void *client);

/**
 * @brief Make sub-device online
 *
 * @param client    handle to gateway client
 * @param param     sub-device parameters
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int IOT_Gateway_Subdev_Online(void *client, GatewayParam *param);

/**
 * @brief Make sub-device offline
 *
 * @param client    handle to gateway client
 * @param param     sub-device parameters
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int IOT_Gateway_Subdev_Offline(void *client, GatewayParam *param);

/**
 * @brief Make sub-device bind
 *
 * @param client    handle to gateway client
 * @param param     gateway parameters
 * @param pBindSubDevInfo   sub dev info wait bind
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int IOT_Gateway_Subdev_Bind(void *client, GatewayParam *param, DeviceInfo *pBindSubDevInfo);

/**
 * @brief Make sub-device unbind
 *
 * @param client    handle to gateway client
 * @param param     gateway parameters
 * @param pBindSubDevInfo   sub dev info wait unbind
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int IOT_Gateway_Subdev_Unbind(void *client, GatewayParam *param, DeviceInfo *pSubDevInfo);

/**
 * @brief Publish gateway MQTT message
 *
 * @param client        handle to gateway client
 * @param topic_name    MQTT topic name
 * @param params        publish parameters
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Gateway_Publish(void *client, char *topic_name, PublishParams *params);

/**
 * @brief Subscribe gateway MQTT topic
 *
 * @param client        handle to gateway client
 * @param topic_filter  MQTT topic filter
 * @param params subscribe parameters
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Gateway_Subscribe(void *client, char *topic_filter, SubscribeParams *params);

/**
 * @brief unsubscribe gateway MQTT topic
 *
 * @param client        handle to gateway client
 * @param topic_filter  MQTT topic filter
 *
 * @return packet id (>=0) when success, or err code (<0) for failure
 */
int IOT_Gateway_Unsubscribe(void *client, char *topic_filter);

/**
 * @brief check if MQTT topic has been subscribed or not
 *
 * @param pClient       handle to MQTT client
 * @param topicFilter   MQTT topic filter
 *
 * @return true when successfully subscribed, or false if not yet
 */
int IOT_Gateway_IsSubReady(void *client, char *topic_filter);

/**
 * @brief Check connection and keep alive state, read/handle MQTT message in
 * synchronized way
 *
 * @param client        handle to gateway client
 * @param timeout_ms timeout value (unit: ms) for this operation
 *
 * @return QCLOUD_RET_SUCCESS when success, or err code for failure
 */
int IOT_Gateway_Yield(void *client, uint32_t timeout_ms);

/**
 * @brief Get mqtt_client of GateWay
 *
 * @param client  handle to gateway client
 *
 * @return mqtt_client of GateWay
 */
void *IOT_Gateway_Get_Mqtt_Client(void *client);

#ifdef MULTITHREAD_ENABLED
/**
 * @brief Start the default yield thread to read and handle gateway msg
 *
 * @param pClient       handle to gateway client
 * @return QCLOUD_RET_SUCCESS when success, err code for failure
 */
int IOT_Gateway_Start_Yield_Thread(void *pClient);

/**
 * @brief Stop the default yield thread to read and handle data_template control
 * and reply msg
 *
 * @param pClient       handle to gateway client
 */
void IOT_Gateway_Stop_Yield_Thread(void *pClient);

/**
 * @brief Get the status of yield thread
 *
 * @param pClient       handle to gateway client
 * @param exit_code     exit code of the thread
 * @return true= thread running, false = thread quit
 */
bool IOT_Gateway_Get_Yield_Status(void *pClient, int *exit_code);
#endif

#ifdef __cplusplus
}
#endif

#endif /* QCLOUD_IOT_EXPORT_GATEWAY_H_ */
