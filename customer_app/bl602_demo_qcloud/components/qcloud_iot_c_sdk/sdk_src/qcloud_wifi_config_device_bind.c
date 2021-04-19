/*
 * Copyright (c) 2020 Tencent Cloud. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "cJSON.h"

#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

static bool sg_token_received                  = false;
static char sg_token_str[MAX_TOKEN_LENGTH + 4] = {0};
static int  sg_bind_reply_code                 = -1;

typedef struct {
    bool sub_ready;
    bool send_ready;
    int  reply_code;
} TokenHandleData;

static void _mqtt_event_handler(void *pclient, void *handle_context, MQTTEventMsg *msg)
{
    MQTTMessage *    mqtt_messge = (MQTTMessage *)msg->msg;
    uintptr_t        packet_id   = (uintptr_t)msg->msg;
    TokenHandleData *app_data    = (TokenHandleData *)handle_context;

    switch (msg->event_type) {
        case MQTT_EVENT_DISCONNECT:
            Log_i("MQTT disconnect.");
            break;

        case MQTT_EVENT_RECONNECT:
            Log_i("MQTT reconnect.");
            break;

        case MQTT_EVENT_PUBLISH_RECVEIVED:
            Log_i("unhandled msg arrived: topic=%s", mqtt_messge->ptopic);
            break;

        case MQTT_EVENT_SUBCRIBE_SUCCESS:
            Log_d("mqtt topic subscribe success");
            app_data->sub_ready = true;
            break;

        case MQTT_EVENT_SUBCRIBE_TIMEOUT:
            Log_i("mqtt topic subscribe timeout");
            app_data->sub_ready = false;
            break;

        case MQTT_EVENT_SUBCRIBE_NACK:
            Log_i("mqtt topic subscribe NACK");
            app_data->sub_ready = false;
            break;

        case MQTT_EVENT_PUBLISH_SUCCESS:
            Log_i("publish success, packet-id=%u", (unsigned int)packet_id);
            app_data->send_ready = true;
            break;

        case MQTT_EVENT_PUBLISH_TIMEOUT:
            Log_i("publish timeout, packet-id=%u", (unsigned int)packet_id);
            app_data->send_ready = false;
            break;

        case MQTT_EVENT_PUBLISH_NACK:
            Log_i("publish nack, packet-id=%u", (unsigned int)packet_id);
            app_data->send_ready = false;
            break;

        default:
            Log_i("unknown event type: %d", msg->event_type);
            break;
    }
}

// callback when MQTT msg arrives
static void _on_message_callback(void *pClient, MQTTMessage *message, void *userData)
{
    if (message == NULL) {
        Log_e("msg null");
        return;
    }

    if (message->topic_len == 0 && message->payload_len == 0) {
        Log_e("length zero");
        return;
    }

    Log_i("recv msg topic: %s", message->ptopic);

    uint32_t msg_topic_len = message->payload_len + 4;
    char *   buf           = (char *)HAL_Malloc(msg_topic_len);
    if (buf == NULL) {
        Log_e("malloc %u bytes failed", msg_topic_len);
        return;
    }

    memset(buf, 0, msg_topic_len);
    memcpy(buf, message->payload, message->payload_len);
    Log_i("msg payload: %s", buf);

    cJSON *root = cJSON_Parse(buf);
    if (!root) {
        Log_e("Parsing JSON Error");
        push_error_log(ERR_TOKEN_REPLY, ERR_APP_CMD_JSON_FORMAT);
    } else {
        cJSON *code_json = cJSON_GetObjectItem(root, "code");
        if (code_json) {
            TokenHandleData *app_data = (TokenHandleData *)userData;
            app_data->reply_code      = code_json->valueint;
            Log_d("token reply code = %d", code_json->valueint);

            sg_bind_reply_code = app_data->reply_code;

            if (app_data->reply_code)
                push_error_log(ERR_TOKEN_REPLY, app_data->reply_code);
        } else {
            Log_e("Parsing reply code Error");
            push_error_log(ERR_TOKEN_REPLY, ERR_APP_CMD_JSON_FORMAT);
        }

        cJSON_Delete(root);
    }

    HAL_Free(buf);
}

// subscrib MQTT topic
static int _subscribe_topic_wait_result(void *client, DeviceInfo *dev_info, TokenHandleData *app_data)
{
    char topic_name[128] = {0};

    int size = HAL_Snprintf(topic_name, sizeof(topic_name), "$thing/down/service/%s/%s", dev_info->product_id,
                            dev_info->device_name);
    if (size < 0 || size > sizeof(topic_name) - 1) {
        Log_e("topic content length not enough! content size:%d  buf size:%d", size, (int)sizeof(topic_name));
        return QCLOUD_ERR_FAILURE;
    }

    SubscribeParams sub_params    = DEFAULT_SUB_PARAMS;
    sub_params.qos                = QOS0;
    sub_params.on_message_handler = _on_message_callback;
    sub_params.user_data          = (void *)app_data;

    int rc = IOT_MQTT_Subscribe(client, topic_name, &sub_params);
    if (rc < 0) {
        Log_e("MQTT subscribe failed: %d", rc);
        return rc;
    }

    int wait_cnt = 2;
    while (!app_data->sub_ready && (wait_cnt-- > 0)) {
        // wait for subscription result
        rc = IOT_MQTT_Yield(client, 1000);
        if (rc) {
            Log_e("MQTT error: %d", rc);
            return rc;
        }
    }

    if (wait_cnt > 0) {
        return QCLOUD_RET_SUCCESS;
    } else {
        Log_w("wait for subscribe result timeout!");
        return QCLOUD_ERR_FAILURE;
    }
}

// publish MQTT msg
static int _publish_token_msg(void *client, DeviceInfo *dev_info, char *token_str)
{
    char topic_name[128] = {0};

    int size = HAL_Snprintf(topic_name, sizeof(topic_name), "$thing/up/service/%s/%s", dev_info->product_id,
                            dev_info->device_name);
    if (size < 0 || size > sizeof(topic_name) - 1) {
        Log_e("topic content length not enough! content size:%d  buf size:%d", size, (int)sizeof(topic_name));
        return QCLOUD_ERR_FAILURE;
    }

    PublishParams pub_params = DEFAULT_PUB_PARAMS;
    pub_params.qos           = QOS1;

    char topic_content[256] = {0};

    size = HAL_Snprintf(topic_content, sizeof(topic_content),
                        "{\"method\":\"app_bind_token\",\"clientToken\":\"%s-%u\",\"params\": {\"token\":\"%s\"}}",
                        dev_info->device_name, HAL_GetTimeMs(), token_str);
    if (size < 0 || size > sizeof(topic_content) - 1) {
        Log_e("payload content length not enough! content size:%d  buf size:%d", size, (int)sizeof(topic_content));
        return QCLOUD_ERR_MALLOC;
    }

    pub_params.payload     = topic_content;
    pub_params.payload_len = strlen(topic_content);

    return IOT_MQTT_Publish(client, topic_name, &pub_params);
}

// send token data via mqtt publishing
static int _send_token_wait_reply(void *client, DeviceInfo *dev_info, TokenHandleData *app_data)
{
    int ret      = 0;
    int wait_cnt = 20;

    // for smartconfig, we need to wait for the token data from app
    while (!sg_token_received && (wait_cnt-- > 0)) {
        IOT_MQTT_Yield(client, 1000);
        Log_i("wait for token data...");
    }

    if (!sg_token_received) {
        Log_e("Wait for token data timeout");
        return QCLOUD_ERR_INVAL;
    }

    wait_cnt = 3;
publish_token:
    ret = _publish_token_msg(client, dev_info, sg_token_str);
    if (ret < 0 && (wait_cnt-- > 0)) {
        Log_e("Client publish token failed: %d", ret);
        if (IOT_MQTT_IsConnected(client)) {
            IOT_MQTT_Yield(client, 500);
        } else {
            Log_e("Wifi or MQTT lost connection! Wait and retry!");
            IOT_MQTT_Yield(client, 2000);
        }
        goto publish_token;
    }

    if (ret < 0)
        return ret;

    wait_cnt = 5;
    while (!app_data->send_ready && (wait_cnt-- > 0)) {
        IOT_MQTT_Yield(client, 1000);
        Log_i("wait for token sending result...");
    }

    ret = 0;
    if (!app_data->send_ready) {
        Log_e("Client publish token timeout");
        ret = QCLOUD_ERR_FAILURE;
    }

    return ret;
}

// get the device info or do device dynamic register
static int _get_reg_dev_info(DeviceInfo *dev_info)
{
    int ret = HAL_GetDevInfo(dev_info);
    if (ret) {
        Log_e("HAL_GetDevInfo error: %d", ret);
        return ret;
    }

    // just a sample to show if we need to do dynamic register
    // if dev_info->device_secret == "YOUR_IOT_PSK", there is no device secret for now
    //    dev_info->product_secret != "YOUR_PRODUCT_SECRET", we have product secret and can do dynamic register
#ifdef DEV_DYN_REG_ENABLED
#ifdef AUTH_MODE_CERT
    /* just demo the cert/key files are empty */
    if ((0 != strcmp(dev_info->dev_cert_file_name, "YOUR_DEVICE_CERT_FILE_NAME")) &&
        (0 != strcmp(dev_info->dev_key_file_name, "YOUR_DEVICE_PRIVATE_KEY_FILE_NAME"))) {
        Log_d("dev Cert exist %s-%s", dev_info->dev_cert_file_name, dev_info->dev_key_file_name);
        return QCLOUD_RET_SUCCESS;
    }
    Log_d("dev Cert not exist, do dyn reg!");
#else
    /* just demo the PSK is empty */
    if (0 != strcmp(dev_info->device_secret, "YOUR_IOT_PSK")) {
        Log_d("dev psk exist");
        return QCLOUD_RET_SUCCESS;
    }
    Log_d("dev psk not exist, do dyn reg!");

    if (0 == strcmp(dev_info->device_secret, "YOUR_PRODUCT_SECRET")) {
        Log_d("product secret not exist, please set it , dyn reg need");
        return QCLOUD_RET_SUCCESS;
    }
#endif
    ret = IOT_DynReg_Device(dev_info);
    if (ret) {
        Log_e("dynamic register device failed: %d", ret);
        return ret;
    }

    // save the dev info
    ret = HAL_SetDevInfo(dev_info);
    if (ret) {
        Log_e("HAL_SetDevInfo failed: %d", ret);
        return ret;
    }

    // delay a while
    HAL_SleepMs(500);
#endif

    return QCLOUD_RET_SUCCESS;
}

// setup mqtt connection and return client handle
static void *_setup_mqtt_connect(DeviceInfo *dev_info, TokenHandleData *app_data)
{
    MQTTInitParams init_params = DEFAULT_MQTTINIT_PARAMS;
    init_params.device_name    = dev_info->device_name;
    init_params.product_id     = dev_info->product_id;
#ifdef AUTH_MODE_CERT
    init_params.cert_file = dev_info->dev_cert_file_name;
    init_params.key_file  = dev_info->dev_key_file_name;
#else
    init_params.device_secret = dev_info->device_secret;
#endif
    init_params.event_handle.h_fp    = _mqtt_event_handler;
    init_params.event_handle.context = (void *)app_data;

    void *client = IOT_MQTT_Construct(&init_params);
    if (client) {
        Log_i("Cloud Device Construct Success");
    }

    return client;
}

// send mqtt token to iot explorer
static int _mqtt_send_token(void)
{
    // get the device info or do device dynamic register
    DeviceInfo dev_info;
    int        ret = _get_reg_dev_info(&dev_info);
    if (ret) {
        Log_e("Get device info failed: %d", ret);
        return ret;
    }

    // token handle data
    TokenHandleData app_data;
    app_data.sub_ready  = false;
    app_data.send_ready = false;
    app_data.reply_code = 404;

    sg_bind_reply_code = app_data.reply_code;

    // mqtt connection
    void *client = _setup_mqtt_connect(&dev_info, &app_data);
    if (client == NULL) {
        ret = IOT_MQTT_GetErrCode();
        Log_e("Cloud Device Construct Failed: %d", ret);
        push_error_log(ERR_MQTT_CONNECT, ret);
        return ret;
    }

    // subscribe token reply topic
    ret = _subscribe_topic_wait_result(client, &dev_info, &app_data);
    if (ret < 0) {
        Log_w("Client Subscribe Topic Failed: %d", ret);
    }

    // publish token msg and wait for reply
    int retry_cnt = 2;
    do {
        ret = _send_token_wait_reply(client, &dev_info, &app_data);
        IOT_MQTT_Yield(client, 1000);
    } while (ret && retry_cnt--);

    if (ret)
        push_error_log(ERR_TOKEN_SEND, ret);

    IOT_MQTT_Destroy(&client);

    // sleep 5 seconds to avoid frequent MQTT connection
    if (ret == 0)
        HAL_SleepMs(5000);
    return ret;
}

int qiot_device_bind(void)
{
    Log_d("device bind start");
    int ret = _mqtt_send_token();
    if (ret) {
        Log_e("WIFI_MQTT_CONNECT_FAILED: %d", ret);
        PUSH_LOG("WIFI_MQTT_CONNECT_FAILED: %d", ret);
    } else {
        Log_i("WIFI_MQTT_CONNECT_SUCCESS");
        PUSH_LOG("WIFI_MQTT_CONNECT_SUCCESS");
    }
    return ret;
}

void qiot_device_bind_set_token(const char *token)
{
    sg_token_received = true;
    strncpy(sg_token_str, token, MAX_TOKEN_LENGTH);
}

bool qiot_device_bind_get_cloud_reply_code(int *bind_reply_code)
{
    *bind_reply_code = sg_bind_reply_code;

    Log_w("Device bind cloud reply code: %d", sg_bind_reply_code);

    return sg_bind_reply_code == -1 ? false : true;
}
