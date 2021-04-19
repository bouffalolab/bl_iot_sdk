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

#if WIFI_PROV_SMART_CONFIG_ENABLE

static bool             sg_smart_config_start = false;
static eWiFiConfigState ap_connect_state      = WIFI_CONFIG_ING;

void set_smart_config_state(eWiFiConfigState state)
{
    ap_connect_state = state;
}

static eWiFiConfigState get_smart_config_state(void)
{
    return ap_connect_state;
}

static void smart_config_task(void *params)
{
    WifiConfigEventCallBack wifi_config_event_cb = params;
    uint32_t                time_count           = (WIFI_CONFIG_WAIT_TIME_MS / WIFI_CONFIG_BLINK_TIME_MS);

    while ((true == sg_smart_config_start) && (--time_count)) {
        // check smart config result, call set_smart_config_state set result

        if (WIFI_CONFIG_SUCCESS == get_smart_config_state() && true == HAL_Wifi_IsConnected()) {
            wifi_config_event_cb(EVENT_WIFI_CONFIG_SUCCESS, NULL);
            break;
        } else if (WIFI_CONFIG_FAIL == get_smart_config_state()) {
            wifi_config_event_cb(EVENT_WIFI_CONFIG_FAILED, NULL);
            break;
        }

        HAL_SleepMs(WIFI_CONFIG_BLINK_TIME_MS);

        if (time_count % 10 == 0) {
            Log_d("smart_config_task running!");
        }
    }

    Log_d("task end connect_success :%d, task_run :%d, time_count:%d", get_smart_config_state(), sg_smart_config_start,
          time_count);

    if (0 == time_count) {
        wifi_config_event_cb(EVENT_WIFI_CONFIG_TIMEOUT, NULL);
    }

    HAL_SmartConfig_Stop();

    return;
}

static int _smart_config_task_start(void *params)
{
    static ThreadParams thread_params;
    thread_params.thread_func = smart_config_task;
    thread_params.thread_name = "smart_config_task";
    thread_params.stack_size  = 8192;
    thread_params.priority    = 3;
    thread_params.user_arg    = params;
    int ret                   = HAL_ThreadCreate(&thread_params);
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("HAL_ThreadCreate(smart_config_task) failed!");
        return -1;
    }

    return 0;
}

int start_device_smartconfig(void)
{
    return QCLOUD_RET_SUCCESS;
}

int stop_device_smartconfig(void)
{
    return QCLOUD_RET_SUCCESS;
}

#endif

/**
 * @brief Start smart config
 *
 * @param params is NULL
 *
 * @return 0 when success, or err code for failure
 */
int HAL_SmartConfig_Start(void *params, WifiConfigEventCallBack event_cb)
{
    int ret = QCLOUD_RET_SUCCESS;
#if WIFI_PROV_SMART_CONFIG_ENABLE
    // TO-DO device platform start smart config
    ret = start_device_smartconfig();
    if (QCLOUD_RET_SUCCESS != ret) {
        Log_e("start smart config failed! ret:%d", ret);
        return ret;
    }

    set_smart_config_state(WIFI_CONFIG_ING);
    sg_smart_config_start = true;

    ret = _smart_config_task_start(event_cb);
    if (QCLOUD_RET_SUCCESS != ret) {
        HAL_SmartConfig_Stop();
    }
#endif
    return ret;
}

/**
 * @brief Stop WiFi config and device binding process
 */
int HAL_SmartConfig_Stop(void)
{
    int ret = QCLOUD_RET_SUCCESS;

#if WIFI_PROV_SMART_CONFIG_ENABLE

    set_smart_config_state(WIFI_CONFIG_ING);

    if (true == sg_smart_config_start) {
        Log_i("HAL_SmartConfig_Stop");

        sg_smart_config_start = false;

        // TO-DO device platform stop smart config
        ret = stop_device_smartconfig();
    }
#endif
    return ret;
}
