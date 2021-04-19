/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2018-2020 THL A29 Limited, a Tencent company. All rights
 reserved.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"

#include "qcloud_wifi_config.h"
#include <bl60x_fw_api.h>
#include <wifi_mgmr_ext.h>

static void wifi_connect(char *ssidname, char *password)
{
    wifi_interface_t wifi_interface;

    wifi_interface = wifi_mgmr_sta_enable();
    wifi_mgmr_sta_connect(wifi_interface, ssidname, password, NULL, NULL, 0, 0);
}

int HAL_Wifi_StaConnect(const char *ssid, const char *psw, uint8_t channel)
{
    Log_i("STA to connect SSID:%s PASSWORD:%s CHANNEL:%d", ssid, psw, channel);
    wifi_connect(ssid,psw);

    return QCLOUD_RET_SUCCESS;
}

bool q_cloud_IsConnected=0;
bool HAL_Wifi_IsConnected(void)
{
    if(q_cloud_IsConnected==1)
        return true;
        
    return false;
}

int HAL_Wifi_read_err_log(uint32_t offset, void *log, size_t log_size)
{
    Log_i("HAL_Wifi_check_err_log");

    return QCLOUD_RET_SUCCESS;
}

int HAL_Wifi_write_err_log(uint32_t offset, void *log, size_t log_size)
{
    Log_i("HAL_Wifi_check_err_log");

    return QCLOUD_RET_SUCCESS;
}

int HAL_Wifi_clear_err_log(void)
{
    Log_i("HAL_Wifi_clear_err_log");

    return QCLOUD_RET_SUCCESS;
}
