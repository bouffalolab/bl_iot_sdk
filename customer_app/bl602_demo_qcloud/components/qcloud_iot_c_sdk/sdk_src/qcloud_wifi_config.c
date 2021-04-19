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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "qcloud_iot_export_log.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

static char sg_ssid[MAX_SSID_LEN + 1];
static char sg_psk[MAX_PSK_LEN + 1];

typedef struct {
    int (*config_start)(void *, WifiConfigEventCallBack);
    int (*config_stop)(void);
} WiFiConfigMethod;

static WiFiConfigMethod sg_wifi_config_methods[] = {
    {HAL_SoftApProvision_Start, HAL_SoftApProvision_Stop},  // WIFI_CONFIG_TYPE_SOFT_AP
    {HAL_SmartConfig_Start, HAL_SmartConfig_Stop},          // WIFI_CONFIG_TYPE_SMART_CONFIG
    {HAL_AirkissConfig_Start, HAL_AirkissConfig_Stop},      // WIFI_CONFIG_TYPE_AIRKISS
    {HAL_SimpleConfig_Start, HAL_SimpleConfig_Stop},        // WIFI_CONFIG_TYPE_SIMPLE_CONFIG
    {HAL_BTComboConfig_Start, HAL_BTComboConfig_Stop}       // WIFI_CONFIG_TYPE_BTCombo_CONFIG
};

static WiFiConfigMethod *       sg_wifi_config_method_now = NULL;
static WifiConfigResultCallBack sg_wifi_config_result_cb  = NULL;

static void _qiot_wifi_config_event_cb(eWiFiConfigEvent event, void *usr_data)
{
    switch (event) {
        case EVENT_WIFI_CONFIG_SUCCESS:
            if (qiot_device_bind()) {
                Log_e("Device bind failed!");
                sg_wifi_config_result_cb(RESULT_WIFI_CONFIG_FAILED, NULL);
            } else {
                Log_d("Device bind success!");
                sg_wifi_config_result_cb(RESULT_WIFI_CONFIG_SUCCESS, NULL);
            }
            break;

        case EVENT_WIFI_CONFIG_FAILED:
            Log_e("Wifi config failed!");
            sg_wifi_config_result_cb(RESULT_WIFI_CONFIG_FAILED, NULL);
            break;

        case EVENT_WIFI_CONFIG_TIMEOUT:
            Log_e("Wifi config timeout!");
            sg_wifi_config_result_cb(RESULT_WIFI_CONFIG_TIMEOUT, NULL);
            break;

        default:
            Log_e("Unknown wifi config error!");
            sg_wifi_config_result_cb(RESULT_WIFI_CONFIG_FAILED, NULL);
            break;
    }
}

/**
 * @brief Start WiFi config and device binding process
 *
 * @param type WiFi config type, only WIFI_CONFIG_TYPE_SIMPLE_CONFIG is supported now
 * @param params See rtk_simple_config.h
 * @param result_cb callback to get wifi config result
 *
 * @return 0 when success, or err code for failure
 */
int qiot_wifi_config_start(eWiFiConfigType type, void *params, WifiConfigResultCallBack result_cb)
{
    if (type < WIFI_CONFIG_TYPE_SOFT_AP || type > WIFI_CONFIG_TYPE_BT_COMBO) {
        Log_e("Unknown wifi config type!");
        return ERR_UNKNOWN_WIFI_CONFIG_TYPE;
    }

    if (init_dev_log_queue()) {
        Log_e("Init dev log queue failed!");
        return ERR_WIFI_CONFIG_START_FAILED;
    }

    if (init_error_log_queue()) {
        Log_e("Init error log queue failed!");
        return ERR_WIFI_CONFIG_START_FAILED;
    }

    sg_wifi_config_method_now = &sg_wifi_config_methods[type];

    if (!sg_wifi_config_method_now->config_start) {
        sg_wifi_config_method_now = NULL;
        Log_e("Unsupported wifi config type!");
        return ERR_UNSUPPORTED_WIFI_CONFIG_TYPE;
    }

    sg_wifi_config_result_cb = result_cb;
    if (sg_wifi_config_method_now->config_start(params, _qiot_wifi_config_event_cb)) {
        sg_wifi_config_method_now = NULL;
        Log_e("Wifi Config start failed!");
        return ERR_WIFI_CONFIG_START_FAILED;
    }

    if (qiot_comm_service_start()) {
        sg_wifi_config_method_now->config_stop();
        sg_wifi_config_method_now = NULL;
        Log_e("Comm service start failed!");
        return ERR_COMM_SERVICE_START_FAILED;
    }

    return RET_WIFI_CONFIG_START_SUCCESS;
}

/**
 * @brief Stop WiFi config and device binding process
 */
void qiot_wifi_config_stop(void)
{
    qiot_comm_service_stop();
}

/**
 * @brief Send wifi config log to app
 */
int qiot_wifi_config_send_log(void)
{
#if WIFI_LOG_UPLOAD
#define LOG_SOFTAP_CH 6
    int ret;

    Log_e("start softAP for log");
    ret = start_device_softAP("ESP-LOG-QUERY", "86013388", LOG_SOFTAP_CH);
    if (ret) {
        Log_e("start_softAP failed: %d", ret);
        goto err_eixt;
    }

    ret = qiot_log_service_start();
    if (ret) {
        Log_e("qiot_log_service_start failed: %d", ret);
    }

    return 0;

err_eixt:
    stop_device_softAP();
    delete_dev_log_queue();

    return ret;
#undef LOG_SOFTAP_CH
#else
    return 0;
#endif
}

void qiot_wifi_ap_info_set(const uint8_t *ssid, const uint8_t *psw)
{
    memset(sg_ssid, '\0', MAX_SSID_LEN);
    memset(sg_psk, '\0', MAX_PSK_LEN);

    memcpy(sg_ssid, ssid, MAX_SSID_LEN);
    memcpy(sg_psk, psw, MAX_PSK_LEN);
}

void qiot_wifi_ap_info_get(uint8_t *ssid, int ssid_buff_len, uint8_t *psk, int psk_buff_len)
{
    memset(ssid, '\0', ssid_buff_len);
    memset(psk, '\0', psk_buff_len);

    memcpy(ssid, sg_ssid, MAX_SSID_LEN);
    memcpy(psk, sg_psk, MAX_PSK_LEN);
}
