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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "qcloud_iot_export.h"
#include "qutils_timer.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

#if WIFI_PROV_BT_COMBO_CONFIG_ENABLE

static bool             sg_bt_combo_config_start = false;
static eWiFiConfigState ap_connect_state         = WIFI_CONFIG_ING;

void set_bt_combo_config_state(eWiFiConfigState state)
{
    ap_connect_state = state;
}

static eWiFiConfigState get_bt_combo_config_state(void)
{
    return ap_connect_state;
}

static int bt_combo_send_message(char *buff, int buff_len)
{
    // TO-DO
    return QCLOUD_RET_SUCCESS;
}

static void bt_combo_report_wificonn_success()
{
    // TO-DO subtype 0x04
}

static int bt_combo_report_bind_result(int token_status)
{
    int        ret           = QCLOUD_ERR_FAILURE;
    char       json_str[256] = {0};
    DeviceInfo devinfo;

    ret = HAL_GetDevInfo(&devinfo);
    if (ret != QCLOUD_RET_SUCCESS) {
        Log_e("load dev info failed: %d", ret);
        return -1;
    }

    HAL_Snprintf(json_str, sizeof(json_str), "{\"status\":%d,\"productID\":\"%s\",\"deviceName\":\"%s\"}\r\n",
                 token_status, devinfo.product_id, devinfo.device_name);

    // TO-DO BLE Send json_str to wechat applet subtype 0x05
    bt_combo_send_message(json_str, strlen(json_str));

    return ret;
}

static void bt_combo_config_task(void *params)
{
    WifiConfigEventCallBack wifi_config_event_cb = params;
    int                     bind_reply_code      = 0;
    uint32_t                time_count           = WIFI_CONFIG_WAIT_TIME_MS / WIFI_CONFIG_BLINK_TIME_MS;

    while ((true == sg_bt_combo_config_start) && (--time_count)) {
        // check bt combo config result, call set_bt_combo_apconn_state set result
        // call set_bt_combo_token_state set token is getted

        if ((WIFI_CONFIG_SUCCESS == get_bt_combo_config_state()) && (true == HAL_Wifi_IsConnected())) {
            bt_combo_report_wificonn_success();
            wifi_config_event_cb(EVENT_WIFI_CONFIG_SUCCESS, NULL);
            if (true == qiot_device_bind_get_cloud_reply_code(&bind_reply_code)) {
                bt_combo_report_bind_result(bind_reply_code);
            }
            break;
        } else if (WIFI_CONFIG_FAIL == get_bt_combo_config_state()) {
            wifi_config_event_cb(EVENT_WIFI_CONFIG_FAILED, NULL);
            break;
        }

        HAL_SleepMs(WIFI_CONFIG_BLINK_TIME_MS);

        if (time_count % 10 == 0) {
            Log_d("bt combo task running!");
        }
    }

    Log_d("task end connect_success :%d, task_run :%d", get_bt_combo_config_state(), sg_bt_combo_config_start);

    if (0 == time_count) {
        wifi_config_event_cb(EVENT_WIFI_CONFIG_TIMEOUT, NULL);
    }

    HAL_BTComboConfig_Stop();
}

int _bt_combo_config_task_start(void *params)
{
    static ThreadParams thread_params;
    thread_params.thread_func = bt_combo_config_task;
    thread_params.thread_name = "bt_combo_config_task";
    thread_params.stack_size  = 8192;
    thread_params.priority    = 3;
    thread_params.user_arg    = params;
    int ret                   = HAL_ThreadCreate(&thread_params);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("HAL_ThreadCreate(_bt_combo_config_task_start) failed!");
        return -1;
    }

    return 0;
}

int start_device_btcomboconfig(void)
{
    // TO-DO
    return QCLOUD_RET_SUCCESS;
}

int stop_device_btcomboconfig(void)
{
    // TO-DO
    return QCLOUD_RET_SUCCESS;
}

#endif

/**
 * @brief Start bt combo config
 *
 * @param params is null
 *
 * @return 0 when success, or err code for failure
 */
int HAL_BTComboConfig_Start(void *params, WifiConfigEventCallBack event_cb)
{
    int ret = QCLOUD_RET_SUCCESS;
#if WIFI_PROV_BT_COMBO_CONFIG_ENABLE
    set_bt_combo_config_state(WIFI_CONFIG_ING);

    // TO-DO device platform start bt combo config
    ret = start_device_btcomboconfig();
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("start bt combo config failed! ret:%d", ret);
        return ret;
    }

    sg_bt_combo_config_start = true;

    ret = _bt_combo_config_task_start(event_cb);
    if (QCLOUD_RET_SUCCESS != ret) {
        HAL_BTComboConfig_Stop();
    }
#endif
    return ret;
}

/**
 * @brief Stop WiFi config and device binding process
 */
int HAL_BTComboConfig_Stop(void)
{
    int ret = QCLOUD_RET_SUCCESS;
#if WIFI_PROV_BT_COMBO_CONFIG_ENABLE
    set_bt_combo_config_state(WIFI_CONFIG_ING);

    if (sg_bt_combo_config_start) {
        Log_i("HAL_BTComboConfig_Stop");

        sg_bt_combo_config_start = false;

        // TO-DO device platform stop bt combo config
        ret = stop_device_btcomboconfig();
    }
#endif
    return ret;
}
