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

#include "qcloud_iot_import.h"
#include "qcloud_iot_export.h"
#include "qutils_timer.h"

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

#if WIFI_PROV_AIRKISS_CONFIG_ENABLE

static bool             sg_airkiss_start = false;  // airkiss config start flag
static eWiFiConfigState ap_connect_state = WIFI_CONFIG_ING;

void set_airkiss_config_state(eWiFiConfigState state)
{
    ap_connect_state = state;
}

static eWiFiConfigState get_airkiss_config_state(void)
{
    return ap_connect_state;
}

// loop check connect ap result
static void airkiss_task(void *params)
{
    uint32_t                time_count           = WIFI_CONFIG_WAIT_TIME_MS / WIFI_CONFIG_BLINK_TIME_MS;
    WifiConfigEventCallBack wifi_config_event_cb = (WifiConfigEventCallBack)params;

    while ((true == sg_airkiss_start) && (--time_count)) {
        // check airkiss config result, call set_airkiss_config_state set result

        if (WIFI_CONFIG_SUCCESS == get_airkiss_config_state() && true == HAL_Wifi_IsConnected()) {
            wifi_config_event_cb(EVENT_WIFI_CONFIG_SUCCESS, NULL);
            break;
        } else if (WIFI_CONFIG_FAIL == get_airkiss_config_state()) {
            wifi_config_event_cb(EVENT_WIFI_CONFIG_FAILED, NULL);
            break;
        }

        HAL_SleepMs(WIFI_CONFIG_BLINK_TIME_MS);

        if (time_count % 10 == 0) {
            Log_d("airkiss_task running!");
        }
    }

    Log_d("task end connect_success :%d, task_run :%d, time_count:%d", get_airkiss_config_state(), sg_airkiss_start,
          time_count);

    if (0 == time_count) {
        wifi_config_event_cb(EVENT_WIFI_CONFIG_TIMEOUT, NULL);
    }

    HAL_AirkissConfig_Stop();
}

static int _airkiss_task_start(void *params)
{
    static ThreadParams thread_params;
    thread_params.thread_func = airkiss_task;
    thread_params.thread_name = "airkiss_task";
    thread_params.stack_size  = 8192;
    thread_params.priority    = 3;
    thread_params.user_arg    = params;
    int ret                   = HAL_ThreadCreate(&thread_params);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("HAL_ThreadCreate(airkiss_task) failed!");
        return -1;
    }

    return 0;
}

int start_device_airkiss(void)
{
    return QCLOUD_RET_SUCCESS;
}

int stop_device_airkiss(void)
{
    return QCLOUD_RET_SUCCESS;
}

#endif
/**
 * @brief Start airkiss
 *
 * @param params is NULL
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_AirkissConfig_Start(void *params, WifiConfigEventCallBack event_cb)
{
    int ret = QCLOUD_RET_SUCCESS;
#if WIFI_PROV_AIRKISS_CONFIG_ENABLE

    // TO-DO device platform start airkiss
    ret = start_device_airkiss();
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("start airkiss config failed! ret:%d", ret);
        return ret;
    }

    sg_airkiss_start = true;
    set_airkiss_config_state(WIFI_CONFIG_ING);

    ret = _airkiss_task_start(event_cb);

    if (QCLOUD_RET_SUCCESS != ret) {
        HAL_AirkissConfig_Stop();
    }
#endif
    return ret;
}

/**
 * @brief Stop WiFi config and device binding process
 */
int HAL_AirkissConfig_Stop(void)
{
    int ret = QCLOUD_RET_SUCCESS;
#if WIFI_PROV_AIRKISS_CONFIG_ENABLE

    set_airkiss_config_state(WIFI_CONFIG_ING);

    if (true == sg_airkiss_start) {
        Log_i("HAL_AirkissConfig_Stop");

        sg_airkiss_start = false;

        // TO-DO device platform stop airkiss
        ret = stop_device_airkiss();
    }
#endif
    return ret;
}
