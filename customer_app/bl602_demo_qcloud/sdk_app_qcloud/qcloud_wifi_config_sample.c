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

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include "qcloud_iot_export.h"
#include "qcloud_iot_import.h"
#include "qutils_getopt.h"
#include "lite-utils.h"
#include "qutils_timer.h"
#include <hal_hwtimer.h>

#include "qcloud_wifi_config.h"
#include "qcloud_wifi_config_internal.h"

#if !(WIFI_PROV_SOFT_AP_ENABLE || WIFI_PROV_SMART_CONFIG_ENABLE || WIFI_PROV_AIRKISS_CONFIG_ENABLE || \
      WIFI_PROV_SIMPLE_CONFIG_ENABLE || WIFI_PROV_BT_COMBO_CONFIG_ENABLE)

#error "Please choose one set to 1 of them in qcloud_wifi_config.h"
#endif
static bool wifi_config_result_success = false;

#ifdef AUTH_MODE_CERT
static char sg_cert_file[PATH_MAX + 1 + 1024];  // full path of device cert file
static char sg_key_file[PATH_MAX + 1 + 1024];   // full path of device key file
#endif

static TaskHandle_t q_cloud_netconfig_task = NULL;
TaskHandle_t q_cloud_demo_task = NULL;
static hw_timer_t  *qcloud_demo_handle= NULL;
// user's log print callback
static bool log_handler(const char *message)
{
    // return true if print success
    return false;
}
static void _wifi_config_result_cb(eWiFiConfigResult event, void *usr_data)
{
    Log_d("entry...");
    qiot_wifi_config_stop();
    switch (event) {
        case RESULT_WIFI_CONFIG_SUCCESS:
            Log_i("WiFi is ready, to do Qcloud IoT demo");
            Log_d("timestamp now:%d", HAL_Timer_current_sec());
            wifi_config_result_success = true;
            Log_i("send q_cloud_netconfig_task exit\r\n");
            xTaskNotify(q_cloud_netconfig_task, 1, eSetValueWithOverwrite);
            break;

        case RESULT_WIFI_CONFIG_TIMEOUT:
            Log_e("wifi config timeout!");
            wifi_config_result_success = false;
        case RESULT_WIFI_CONFIG_FAILED:
            Log_e("wifi config failed!");
            qiot_wifi_config_send_log();
            wifi_config_result_success = false;
            break;

        default:
            break;
    }
}

static bool qcloud_wifi_config_proc()
{
    int   rc;
    Timer timer;
#if WIFI_PROV_SOFT_AP_ENABLE
    eSoftApConfigParams apConf = {"tcloud-softap", "12345678", 6};
    rc                         = qiot_wifi_config_start(WIFI_CONFIG_TYPE_SOFT_AP, &apConf, _wifi_config_result_cb);
    countdown(&timer, 500);
    while ((rc == QCLOUD_RET_SUCCESS) && (false == wifi_config_result_success) && !expired(&timer)) {
        Log_d("wait wifi config result...");
        HAL_SleepMs(1000);
    }
    qiot_wifi_config_stop();
    if (true == wifi_config_result_success) {
        return true;
    }
#endif  // WIFI_PROV_SOFT_AP_ENABLE

#if WIFI_PROV_SMART_CONFIG_ENABLE
    rc = qiot_wifi_config_start(WIFI_CONFIG_TYPE_SMART_CONFIG, NULL, _wifi_config_result_cb);
    countdown(&timer, 500);
    while ((rc == QCLOUD_RET_SUCCESS) && (false == wifi_config_result_success) && !expired(&timer)) {
        Log_d("wait wifi config result...");
        HAL_SleepMs(1000);
    }
    qiot_wifi_config_stop();
    if (true == wifi_config_result_success) {
        return true;
    }
#endif  // WIFI_PROV_SMART_CONFIG_ENABLE

#if WIFI_PROV_AIRKISS_CONFIG_ENABLE
    rc = qiot_wifi_config_start(WIFI_CONFIG_TYPE_AIRKISS, NULL, _wifi_config_result_cb);
    countdown(&timer, 500);
    while ((rc == QCLOUD_RET_SUCCESS) && (false == wifi_config_result_success) && !expired(&timer)) {
        Log_d("wait wifi config result...");
        HAL_SleepMs(1000);
    }
    qiot_wifi_config_stop();
    if (true == wifi_config_result_success) {
        return true;
    }
#endif  // WIFI_PROV_AIRKISS_CONFIG_ENABLE

#if WIFI_PROV_SIMPLE_CONFIG_ENABLE
    rc = qiot_wifi_config_start(WIFI_CONFIG_TYPE_SIMPLE_CONFIG, NULL, _wifi_config_result_cb);
    countdown(&timer, 500);
    while ((rc == QCLOUD_RET_SUCCESS) && (false == wifi_config_result_success) && !expired(&timer)) {
        Log_d("wait wifi config result...");
        HAL_SleepMs(1000);
    }
    qiot_wifi_config_stop();
    if (true == wifi_config_result_success) {
        return true;
    }
#endif  // WIFI_PROV_SIMPLE_CONFIG_ENABLE

#if WIFI_PROV_BT_COMBO_CONFIG_ENABLE
    rc = qiot_wifi_config_start(WIFI_CONFIG_TYPE_BT_COMBO, NULL, _wifi_config_result_cb);
    countdown(&timer, 500);
    while ((rc == QCLOUD_RET_SUCCESS) && (false == wifi_config_result_success) && !expired(&timer)) {
        Log_d("wait wifi config result...");
        HAL_SleepMs(1000);
    }
    qiot_wifi_config_stop();
    if (true == wifi_config_result_success) {
        return true;
    }
#endif  // WIFI_PROV_BT_COMBO_CONFIG_ENABLE
    return false;
}
void Start_Qcloud_Demo(void)
{
extern void bl_qcloud_main(void);

    if(qcloud_demo_handle!=NULL)
    {
        hal_hwtimer_delete(qcloud_demo_handle);
    }
    qcloud_demo_handle=NULL;
   q_cloud_demo_task=NULL; 
   xTaskCreate(bl_qcloud_main, (char*)"tencent cloud", 5120, NULL, 16, &q_cloud_demo_task);
}

void q_cloud_netconfig(int argc, char **argv)
{
    int rc=0;
    uint32_t ulNotifiedValue = 0;
	uint8_t flagexit = 0;
    // init log level
    IOT_Log_Set_Level(eLOG_DEBUG);
    IOT_Log_Set_MessageHandler(log_handler);


    if (false == qcloud_wifi_config_proc()) {
        Log_d("wifi config failed");
    }
    while(1)
    {
        xTaskNotifyWait(0x00, 0xffffffff, &ulNotifiedValue, 50);
        if (ulNotifiedValue == 1)
			flagexit = 1;
		ulNotifiedValue = 0;
        if (flagexit){
            Log_i("wifi config ok");
            goto _exit;
        }

    }

_exit:
	printf("exit q_cloud_netconfig\r\n");
    qcloud_demo_handle = hal_hwtimer_create(100, Start_Qcloud_Demo, 1);
	q_cloud_netconfig_task = NULL;
    vTaskDelete(NULL);
}

void Q_Cloud_Config_Net_Start(void)  
{
	if (q_cloud_netconfig_task != NULL)
		return;
	printf("create q_cloud_netconfig task\r\n");
	xTaskCreate(q_cloud_netconfig, "loctrltask", 10240, NULL, 18, &q_cloud_netconfig_task);   
}