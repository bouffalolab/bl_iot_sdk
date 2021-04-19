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

#ifndef __QCLOUD_IOT_WIFI_CONFIG_H__
#define __QCLOUD_IOT_WIFI_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_ERR_LOG_POST 1
#define WIFI_LOG_UPLOAD   1

#define WIFI_PROV_SOFT_AP_ENABLE         1  ///< wifi provisioning method: device AP, need Wechat Applets
#define WIFI_PROV_SMART_CONFIG_ENABLE    0  ///< wifi provisioning method: smart config, need Wechat Applets
#define WIFI_PROV_AIRKISS_CONFIG_ENABLE  0  ///< wifi provisioning method: airkiss, need Wechat Applets
#define WIFI_PROV_SIMPLE_CONFIG_ENABLE   0  ///< wifi provisioning method: simple config, need Wechat Applets
#define WIFI_PROV_BT_COMBO_CONFIG_ENABLE 0  ///< wifi provisioning method: bt combo config, need Wechat Applets

#define MAX_SSID_LEN 32  // max ssid len
#define MAX_PSK_LEN  65  // max psk len

typedef enum {
    WIFI_CONFIG_TYPE_SOFT_AP       = 0, /* Soft ap */
    WIFI_CONFIG_TYPE_SMART_CONFIG  = 1, /* Smart config*/
    WIFI_CONFIG_TYPE_AIRKISS       = 2, /* Airkiss */
    WIFI_CONFIG_TYPE_SIMPLE_CONFIG = 3, /* Simple config  */
    WIFI_CONFIG_TYPE_BT_COMBO      = 4, /* BT Combo config */
} eWiFiConfigType;

typedef enum {
    RET_WIFI_CONFIG_START_SUCCESS    = 0,
    ERR_UNKNOWN_WIFI_CONFIG_TYPE     = -1,
    ERR_UNSUPPORTED_WIFI_CONFIG_TYPE = -2,
    ERR_WIFI_CONFIG_START_FAILED     = -3,
    ERR_COMM_SERVICE_START_FAILED    = -4
} eWiFiConfigErrCode;

typedef enum {
    RESULT_WIFI_CONFIG_SUCCESS, /* WiFi config success */
    RESULT_WIFI_CONFIG_FAILED,  /* WiFi config failed */
    RESULT_WIFI_CONFIG_TIMEOUT  /* WiFi config timeout */
} eWiFiConfigResult;

typedef void (*WifiConfigResultCallBack)(eWiFiConfigResult result, void *usr_data);

typedef enum {
    EVENT_WIFI_CONFIG_SUCCESS = 0, /* WiFi config success */
    EVENT_WIFI_CONFIG_FAILED  = 1, /* WiFi config failed */
    EVENT_WIFI_CONFIG_TIMEOUT = 2, /* WiFi config timeout */
} eWiFiConfigEvent;

typedef enum {
    WIFI_CONFIG_ING     = 0, /* WiFi config ING*/
    WIFI_CONFIG_FAIL    = 1, /* WiFi config FAIL */
    WIFI_CONFIG_SUCCESS = 2, /* WiFi config SUCCESS */
} eWiFiConfigState;

typedef void (*WifiConfigEventCallBack)(eWiFiConfigEvent event, void *usr_data);

/**
 * @brief Start WiFi config and device binding process
 *
 * @param type @see eWiFiConfigType, only WIFI_CONFIG_TYPE_SIMPLE_CONFIG is supported now
 * @param params @see rtk_simple_config.h
 * @param result_cb callback to get wifi config result
 *
 * @return @see eWiFiConfigErrCode
 */
int qiot_wifi_config_start(eWiFiConfigType type, void *params, WifiConfigResultCallBack result_cb);

/**
 * @brief Stop WiFi config and device binding process immediately
 */
void qiot_wifi_config_stop(void);

/**
 * @brief Send wifi config log to mini program
 */
int qiot_wifi_config_send_log(void);

/**
 * @brief set the ap ssid and psk fetched by wifi config
 */
void qiot_wifi_ap_info_set(const uint8_t *ssid, const uint8_t *psw);

/**
 * @brief get the ap ssid and psk fetched by wifi config
 */
void qiot_wifi_ap_info_get(uint8_t *ssid, int ssid_buff_len, uint8_t *psk, int psk_buff_len);

/**
 * @brief set device token and notify to bind device
 *
 * @param token from wechat applet
 *
 */
void qiot_device_bind_set_token(const char *token);

/**
 * @brief get bind device cloud reply code
 *
 * @param bind_reply_code 0 is success other is fail, send it to wechat applet
 *
 * @return recv cloud platform reply device bind msg is true, other return false happen error
 */
bool qiot_device_bind_get_cloud_reply_code(int *bind_reply_code);

/**
 * @brief device start to connect ap, include switch mode to sta, disconnect ap, connect ap
 *
 * @param ssid connect ap ssid
 * @param psw  connect ap ssid->password
 * @param channel connect ap in channel
 *
 * @return 0 is fun proc success, other fun proc failed
 */
int HAL_Wifi_StaConnect(const char *ssid, const char *psw, uint8_t channel);

/**
 * @brief get station connect ap result
 *
 * @param void
 *
 * @return true is get ip; other is false
 */
bool HAL_Wifi_IsConnected(void);

typedef struct {
    const char *ssid;
    const char *psw;
    uint8_t     ch;
} eSoftApConfigParams;

/**
 * @brief Start softAP provision
 *
 * @param params See eSoftApConfigParams
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_SoftApProvision_Start(void *params, WifiConfigEventCallBack event_cb);

/**
 * @brief Stop softAp WiFi provision and device binding process
 */
int HAL_SoftApProvision_Stop(void);

/**
 * @brief start device softap
 * @param ssid  softap ssid
 * @param psw   softap pws
 * @param ch    softap channel
 *
 * @return 0 when success, or err code for failuer
 */
int start_device_softAP(const char *ssid, const char *psw, uint8_t ch);

/**
 * @brief start device softap
 *
 * @return 0 when success, or err code for failuer
 */
int stop_device_softAP(void);

/**
 * @brief Start airkiss
 *
 * @param params is NULL
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_AirkissConfig_Start(void *params, WifiConfigEventCallBack event_cb);
/**
 * @brief Stop airkiss and device binding process
 */
int HAL_AirkissConfig_Stop(void);

/**
 * @brief set airkiss config state
 *
 * @param eWiFiConfigStatee, ing,succ,fail
 *
 * @return null
 */
void set_airkiss_config_state(eWiFiConfigState state);

/**
 * @brief Start smart config
 *
 * @param params is NULL
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_SmartConfig_Start(void *params, WifiConfigEventCallBack event_cb);
/**
 * @brief Stop SmartConfig and device binding process
 */
int HAL_SmartConfig_Stop(void);

/**
 * @brief set smart config state
 *
 * @param eWiFiConfigState ing,succ,fail
 *
 * @return null
 */
void set_smart_config_state(eWiFiConfigState state);

/**
 * @brief Start simple config
 *
 * @param params is NULL
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_SimpleConfig_Start(void *params, WifiConfigEventCallBack event_cb);
/**
 * @brief Stop simple config and device binding process
 */
int HAL_SimpleConfig_Stop(void);

/**
 * @brief set simple config state
 *
 * @param eWiFiConfigState ing,succ,fail
 *
 * @return null
 */
void set_simple_config_state(eWiFiConfigState state);

/**
 * @brief Start bt combo config
 *
 * @param params is NULL
 * @event_cb wifi config event callback, success to bind device
 *
 * @return 0 when success, or err code for failure
 */
int HAL_BTComboConfig_Start(void *params, WifiConfigEventCallBack event_cb);
/**
 * @brief Stop bt combo config and device binding process
 */
int HAL_BTComboConfig_Stop(void);

/**
 * @brief set bt combo config state
 *
 * @param eWiFiConfigState ing,succ,fail
 *
 * @return null
 */
void set_bt_combo_config_state(eWiFiConfigState state);

/**
 * @brief get wifi config err log from saved
 *
 * @param offset   log read start position
 * @param log  err log get buff
 * @param log_size err log buff size
 *
 * @return 0 when success, or err code for failure
 */
int HAL_Wifi_read_err_log(uint32_t offset, void *log, size_t log_size);

/**
 * @brief save wifi config err log
 *
 * @param offset   log write start position
 * @param log  err log buff
 * @param log_size err log buff size
 *
 * @return 0 when success, or err code for failure
 */
int HAL_Wifi_write_err_log(uint32_t offset, void *log, size_t log_size);

/**
 * @brief clear saved all log
 *
 * @param is NULL
 *
 * @return 0 when success, or err code for failure
 */
int HAL_Wifi_clear_err_log(void);

#ifdef __cplusplus
}
#endif

#endif  //__QCLOUD_WIFI_CONFIG_H__
