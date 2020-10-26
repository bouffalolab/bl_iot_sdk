/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __WIFI_MGMR_H__
#define __WIFI_MGMR_H__
#include <stdint.h>

#include "include/wifi_mgmr_ext.h"
#include "stateMachine.h"
#include "os_hal.h"

#define WIFI_MGMR_SCAN_ITEMS_MAX (50)
#define WIFI_MGMR_PROFILES_MAX (2)
#define WIFI_MGMR_MQ_MSG_SIZE (128 + 64 + 32)
#define WIFI_MGMR_MQ_MSG_COUNT (10)

/**
 ****************************************************************************************
 *
 * @file wifi_mgmr.h
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */

enum EVENT_TYPE {
   EVENT_TYPE_FW,
   EVENT_TYPE_APP,
   EVENT_TYPE_GLB,
};

typedef enum WIFI_MGMR_EVENT {
    /*section for wifi manager event*/
    WIFI_MGMR_EVENT_APP_IDLE = 0,
    WIFI_MGMR_EVENT_APP_CONNECT,
    WIFI_MGMR_EVENT_APP_SNIFFER,
    WIFI_MGMR_EVENT_APP_CONNECTED,
    WIFI_MGMR_EVENT_APP_IP_GOT,
    WIFI_MGMR_EVENT_APP_DISCONNECT,
    WIFI_MGMR_EVENT_APP_RECONNECT,
    WIFI_MGMR_EVENT_APP_PHY_UP,
    WIFI_MGMR_EVENT_APP_AP_START,
    WIFI_MGMR_EVENT_APP_AP_STOP,
    WIFI_MGMR_EVENT_APP_CONF_MAX_STA,
    WIFI_MGMR_EVENT_APP_RC_CONFIG,
    WIFI_MGMR_EVENT_APP_DENOISE,
    WIFI_MGMR_EVENT_APP_RELOAD_TSEN,

    /*boundary between APP and FW*/
    WIFI_MGMR_EVENT_MAXAPP_MINIFW,

    /*section for sending FW command event*/
    WIFI_MGMR_EVENT_FW_DISCONNECT,
    WIFI_MGMR_EVENT_FW_POWERSAVING,
    WIFI_MGMR_EVENT_FW_CHANNEL_SET,
    WIFI_MGMR_EVENT_FW_SCAN,
    WIFI_MGMR_EVENT_FW_IND_DISCONNECT,
    WIFI_MGMR_EVENT_FW_IND_CONNECTED,
    WIFI_MGMR_EVENT_FW_DATA_RAW_SEND,
    WIFI_MGMR_EVENT_FW_CFG_REQ,

    /*boundary between APP and Global handled EVENT*/
    WIFI_MGMR_EVENT_MAXFW_MINI_GLOBAL,

    /*section for sending global handled event*/
    WIFI_MGMR_EVENT_GLB_SCAN_IND_BEACON,
    WIFI_MGMR_EVENT_GLB_SCAN_IND_PROBE_RESP,
    WIFI_MGMR_EVENT_GLB_AP_IND_STA_NEW,
    WIFI_MGMR_EVENT_GLB_AP_IND_STA_DEL,
    WIFI_MGMR_EVENT_GLB_DISABLE_AUTORECONNECT,
    WIFI_MGMR_EVENT_GLB_ENABLE_AUTORECONNECT,
    WIFI_MGMR_EVENT_GLB_IP_UPDATE,

} WIFI_MGMR_EVENT_T;

typedef enum WIFI_MGMR_CONNECTION_STATUS {
    WIFI_MGMR_CONNECTION_STATUS_IDLE,
    WIFI_MGMR_CONNECTION_STATUS_CONNECTING,
    WIFI_MGMR_CONNECTION_STATUS_CONNECTED_IP_YES,
    WIFI_MGMR_CONNECTION_STATUS_CONNECTED_IP_NO,
    WIFI_MGMR_CONNECTION_STATUS_DISCONNECTED,
} WIFI_MGMR_CONNECTION_STATUS_T;

#pragma pack(push, 1)
typedef struct wifi_mgmr_msg {
    WIFI_MGMR_EVENT_T ev;
    void *data1;
    void *data2;
    uint32_t len;
    uint8_t data[0];
} wifi_mgmr_msg_t;

typedef struct wifi_mgmr_cfg_element_msg {
    uint32_t ops;
    uint32_t task;
    uint32_t element;
    uint32_t type;
    uint32_t length;
    uint32_t buf[];
} wifi_mgmr_cfg_element_msg_t;

typedef struct wifi_mgmr_profile_msg {
    char ssid[32];
    char ssid_tail[1];
    uint32_t ssid_len;
    char psk[64];
    char psk_tail[1];
    char pmk[64];
    char pmk_tail[1];
    uint32_t psk_len;
    uint32_t pmk_len;
    uint8_t mac[6];
    uint8_t band;
    uint16_t freq;
    uint8_t dhcp_use;
} wifi_mgmr_profile_msg_t;

typedef struct wifi_mgmr_ipgot_msg {
    uint32_t ip;
    uint32_t mask;
    uint32_t gw;
    uint32_t dns1;
    uint32_t dns2;
} wifi_mgmr_ipgot_msg_t;

typedef struct wifi_mgmr_ap_msg {
    int32_t channel;
    char ssid[32];
    char ssid_tail[1];
    uint8_t hidden_ssid;
    uint32_t ssid_len;
    char psk[64];
    char psk_tail[1];
    uint32_t psk_len;
} wifi_mgmr_ap_msg_t;

#pragma pack(pop)

typedef struct wifi_mgmr_profile {
    char ssid[33];
    uint8_t no_autoconnect;
    uint32_t ssid_len;
    char psk[65];
    uint32_t psk_len;
    char pmk[65];
    uint32_t pmk_len;
    uint8_t mac[6];
    uint8_t dhcp_use;

    /*reserved field for wifi manager*/
    uint8_t priority;
    uint8_t isActive;
    uint8_t isUsed;
} wifi_mgmr_profile_t;


typedef struct
{
    uint8_t wep40 : 1;
    uint8_t wep104 : 1;
    uint8_t tkip : 1;
    uint8_t ccmp : 1;
    uint8_t rsvd : 4;
} wifi_mgmr_cipher_t;

typedef struct wifi_mgmr_scan_item {
    char ssid[32];
    char ssid_tail[1];//always put ssid_tail after ssid
    uint32_t ssid_len;
    uint8_t bssid[6];
    uint8_t channel;
    int8_t rssi;
    int8_t ppm_abs;
    int8_t ppm_rel;
    uint8_t auth;
    uint8_t cipher;
    uint8_t is_used;
    uint32_t timestamp_lastseen;
} wifi_mgmr_scan_item_t;

struct wlan_netif {
    int mode;//0: sta; 1: ap
    uint8_t vif_index;
    uint8_t mac[6];
    struct {
        uint32_t ip;
        uint32_t mask;
        uint32_t gw;
        uint32_t dns1;
        uint32_t dns2;
    } ipv4;
    struct netif netif;
    union {
        struct {
            int8_t rssi;
        } sta;
    };
};

typedef struct wifi_mgmr_connect_ind_stat_info {
    uint16_t status_code;
    /*mgmr recv ind event from fw when connect or disconnect  */
#define WIFI_MGMR_CONNECT_IND_STAT_INFO_TYPE_IND_CONNECTION (1)
#define WIFI_MGMR_CONNECT_IND_STAT_INFO_TYPE_IND_DISCONNECTION (2)
    uint8_t type_ind;
    char ssid[32];
    char psk[65];
    uint8_t bssid[6];
    uint16_t chan_freq;
    uint8_t chan_band;
} wifi_mgmr_connect_ind_stat_info_t;

typedef struct wifi_mgmr_sta_basic_info {
    uint8_t  sta_idx;
    uint8_t  is_used;;
    uint8_t  sta_mac[6];
    uint32_t tsfhi;
    uint32_t tsflo;
    int      rssi;
    uint8_t  data_rate;
} wifi_mgmr_sta_basic_info_t;

typedef struct wifi_mgmr {
    uint8_t ready;//TODO mgmr init process
    /*filed for PHY*/
    int channel;
    int inf_ap_enabled;

    struct wlan_netif wlan_sta;
    struct wlan_netif wlan_ap;
    WIFI_MGMR_CONNECTION_STATUS_T status;
    /*profiles*/
    wifi_mgmr_profile_t profiles[WIFI_MGMR_PROFILES_MAX];
    int profile_active_index;

    wifi_mgmr_scan_item_t scan_items[WIFI_MGMR_SCAN_ITEMS_MAX];
    os_messagequeue_t mq;
    uint8_t mq_pool[WIFI_MGMR_MQ_MSG_SIZE*WIFI_MGMR_MQ_MSG_COUNT];
    struct stateMachine m;
    os_timer_t timer;
    wifi_mgmr_connect_ind_stat_info_t wifi_mgmr_stat_info;
    char country_code[3];
    uint8_t disable_autoreconnect;
    int channel_nums;

    /*pending task*/
    uint32_t pending_task;
#define WIFI_MGMR_PENDING_TASK_SCAN_BIT     (1 << 0)
    /*Feature Bits*/
    uint32_t features;
#define WIFI_MGMR_FEATURES_SCAN_SAVE_HIDDEN_SSID    (1 << 0)

    /*Manager config*/
    int scan_item_timeout;
#define WIFI_MGMR_CONFIG_SCAN_ITEM_TIMEOUT      (15000)
} wifi_mgmr_t;

int wifi_mgmr_event_notify(wifi_mgmr_msg_t *msg);
int wifi_mgmr_state_get_internal(int *state);
int wifi_mgmr_status_code_clean_internal(void);
int wifi_mgmr_status_code_get_internal(int *s_code);
int wifi_mgmr_set_country_code_internal(char *country_code);
int wifi_mgmr_ap_sta_cnt_get_internal(uint8_t *sta_cnt);
int wifi_mgmr_ap_sta_info_get_internal(wifi_mgmr_sta_basic_info_t *sta_info_internal, uint8_t idx);
int wifi_mgmr_ap_sta_delete_internal(uint8_t sta_idx);
int wifi_mgmr_scan_complete_notify();
extern wifi_mgmr_t wifiMgmr;
char *wifi_mgmr_auth_to_str(uint8_t auth);
char *wifi_mgmr_cipher_to_str(uint8_t cipher);
int wifi_mgmr_api_fw_tsen_reload(void);

static inline int wifi_mgmr_scan_item_is_timeout(wifi_mgmr_t *mgmr, wifi_mgmr_scan_item_t *item)
{
    return ((unsigned int)os_tick_get() - (unsigned int)item->timestamp_lastseen) >= mgmr->scan_item_timeout ? 1 : 0;
}
#endif
