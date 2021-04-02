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
#include <string.h>
#include <stdio.h>

#include "wifi_mgmr_api.h"
#include "bl_defs.h"

#define MAX_SSID_LEN_CHECK 32
#define MAX_PSK_LEN_CHECK 64

int wifi_mgmr_api_common(wifi_mgmr_msg_t *msg, WIFI_MGMR_EVENT_T ev, void *data1, void *data2, uint32_t len)
{
    msg->ev = ev;
    msg->data1 = data1;
    msg->data2 = data2;
    msg->len = len;

    wifi_mgmr_event_notify(msg);

    return 0;
}

int wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_T ev, void *data1, void *data2)
{
    wifi_mgmr_msg_t msg;

    msg.ev = ev;
    msg.data1 = data1;
    msg.data2 = data2;
    msg.len = sizeof (wifi_mgmr_msg_t);

    wifi_mgmr_event_notify(&msg);

    return 0;
}

int wifi_mgmr_api_connect(char *ssid, char *psk, char *pmk, uint8_t *mac, uint8_t band, uint16_t freq)
{
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_profile_msg_t *profile;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_profile_msg_t)];//XXX caution for stack overflow

    memset(buffer, 0, sizeof(buffer));
    msg = (wifi_mgmr_msg_t*)buffer;

    profile = (wifi_mgmr_profile_msg_t*)msg->data;
    profile->ssid_len = strlen(ssid);//ssid should never be NULL
    memcpy(profile->ssid, ssid, profile->ssid_len);
    profile->ssid_tail[0] = '\0';
    profile->psk_len = psk ? strlen(psk) : 0;//psk can be NULL
    if (profile->psk_len > sizeof(profile->psk)) {
        return -1;
    } else if (profile->psk_len > 0) {
        memcpy(profile->psk, psk, profile->psk_len);
    }
    profile->psk_tail[0] = '\0';
    profile->pmk_len = pmk ? strlen(pmk) : 0;//pmk can be NULL
    if (0 != profile->pmk_len && sizeof(profile->pmk) != profile->pmk_len) {
        return -1;
    } else if (sizeof(profile->pmk) == profile->pmk_len) {
        memcpy(profile->pmk, pmk, profile->pmk_len);
    }
    profile->pmk_tail[0] = '\0';
    if (mac) {
        memcpy(profile->mac, mac, sizeof(profile->mac));
    }
    if (freq > 0) {
        //define the channel
        profile->band = band;
        profile->freq = freq;
        printf("wifi mgmr band:%d freq: %d\r\n", profile->band, profile->freq);
    }
    profile->dhcp_use = 1;//force use DHCP currently

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_APP_CONNECT,
        (void*)0x1,
        (void*)0x2,
        sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_profile_msg_t)
    );
}

int wifi_mgmr_api_cfg_req(uint32_t ops, uint32_t task, uint32_t element, uint32_t type, uint32_t length, uint32_t *buf)
{
#define MAX_LENGTH_LIMIT        (32)
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_cfg_element_msg_t *cfg_req;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_cfg_element_msg_t) + MAX_LENGTH_LIMIT];//XXX caution for stack overflow

    if (length > MAX_LENGTH_LIMIT) {
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    msg = (wifi_mgmr_msg_t*)buffer;

    cfg_req = (wifi_mgmr_cfg_element_msg_t*)msg->data;
    cfg_req->ops = ops;
    cfg_req->task = task;
    cfg_req->element = element;
    cfg_req->type = type;
    cfg_req->length = length;
    if (length) {
        memcpy(cfg_req->buf, buf, length);
    }

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_FW_CFG_REQ,
        (void*)0x1,
        (void*)0x2,
        sizeof (wifi_mgmr_msg_t) + sizeof(wifi_mgmr_profile_msg_t) + length
    );
}

int wifi_mgmr_api_ip_got(uint32_t ip, uint32_t mask, uint32_t gw, uint32_t dns1, uint32_t dns2)
{
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_ipgot_msg_t *ipgot;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_ipgot_msg_t)];//XXX caution for stack overflow

    memset(buffer, 0, sizeof(buffer));
    msg = (wifi_mgmr_msg_t*)buffer;

    ipgot = (wifi_mgmr_ipgot_msg_t*)msg->data;
    ipgot->ip = ip;
    ipgot->mask = mask;
    ipgot->gw = gw;
    ipgot->dns1 = dns1;
    ipgot->dns2 = dns2;

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_APP_IP_GOT,
        (void*)0x1,
        (void*)0x2,
        sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_ipgot_msg_t)
    );
}

int wifi_mgmr_api_ip_update(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_GLB_IP_UPDATE, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_reconnect(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_RECONNECT, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_disable_autoreconnect(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_GLB_DISABLE_AUTORECONNECT, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_enable_autoreconnect(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_GLB_ENABLE_AUTORECONNECT, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_disconnect(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_DISCONNECT, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_rate_config(uint16_t config)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_RC_CONFIG, (void*)(intptr_t)config, (void*)0x2);
}

int wifi_mgmr_api_conf_max_sta(uint8_t max_sta_supported)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_CONF_MAX_STA, (void*)(intptr_t)max_sta_supported, (void*)0x2);
}

int wifi_mgmr_api_ifaceup(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_PHY_UP, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_sniffer_enable(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_SNIFFER, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_scan_item_beacon(uint8_t channel, int8_t rssi, uint8_t auth, uint8_t mac[], uint8_t ssid[], int len, int8_t ppm_abs, int8_t ppm_rel, uint8_t cipher)
{
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_scan_item_t *scan;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_scan_item_t)];//XXX caution for stack overflow

    memset(buffer, 0, sizeof(buffer));
    msg = (wifi_mgmr_msg_t*)buffer;

    scan = (wifi_mgmr_scan_item_t*)msg->data;
    memcpy(scan->ssid, ssid, len);
    scan->ssid_tail[0] = '\0';
    scan->ssid_len = len;
    memcpy(scan->bssid, mac, sizeof(scan->bssid));
    scan->channel = channel;
    scan->rssi = rssi;
    scan->auth = auth;
    scan->cipher = cipher;
    scan->ppm_abs = ppm_abs;
    scan->ppm_rel = ppm_rel;

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_GLB_SCAN_IND_BEACON,
        (void*)0x1,
        (void*)0x2,
        sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_scan_item_t)
    );
}

int wifi_mgmr_api_fw_disconnect(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_FW_DISCONNECT, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_fw_tsen_reload(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_RELOAD_TSEN, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_fw_scan(uint16_t *channels, uint16_t channel_num)
{
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_scan_fixed_channels_t *ch_req;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_scan_fixed_channels_t) + sizeof(ch_req->channels[0]) * MAX_FIXED_CHANNELS_LIMIT];//XXX caution for stack overflow

    memset(buffer, 0, sizeof(buffer));
    msg = (wifi_mgmr_msg_t*)buffer;

    ch_req = (wifi_mgmr_scan_fixed_channels_t*)msg->data;
    ch_req->channel_num = channel_num;
    if (channel_num) {
        memcpy(ch_req->channels, channels, sizeof(ch_req->channels[0]) * channel_num);
    }

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_FW_SCAN,
        (void*)0x1,
        (void*)0x2,
        sizeof (wifi_mgmr_msg_t) + sizeof(wifi_mgmr_scan_fixed_channels_t) + sizeof(ch_req->channels[0]) * channel_num
    );

}

int wifi_mgmr_api_fw_powersaving(int mode)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_FW_POWERSAVING, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_ap_start(char *ssid, char *passwd, int channel, uint8_t hidden_ssid)
{
    wifi_mgmr_msg_t *msg;
    wifi_mgmr_ap_msg_t *ap;
    uint8_t buffer[sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_ap_msg_t)];//XXX caution for stack overflow

    if (NULL == ssid) {
        //TODO unified ERR code?
        return -1;
    }
    memset(buffer, 0, sizeof(buffer));//we do this, since we need to store len
    msg = (wifi_mgmr_msg_t*)buffer;
    ap = (wifi_mgmr_ap_msg_t*)msg->data;
    if ((ap->ssid_len = strlen(ssid)) > MAX_SSID_LEN_CHECK) {
        return -1;
    }
    if (passwd && (ap->psk_len = strlen(passwd)) > MAX_PSK_LEN_CHECK) {
        return -1;
    }

    memcpy(ap->ssid, ssid, ap->ssid_len);
    if (passwd) {
        memcpy(ap->psk, passwd, ap->psk_len);
    } else {
        ap->psk_len = 0;
    }
    ap->channel = channel;
    ap->hidden_ssid = hidden_ssid ? 1 : 0;

    return wifi_mgmr_api_common(
        msg,
        WIFI_MGMR_EVENT_APP_AP_START,
        (void*)0x1,
        (void*)0x2,
        sizeof(wifi_mgmr_msg_t) + sizeof(wifi_mgmr_ap_msg_t)
    );
}

int wifi_mgmr_api_ap_stop(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_AP_STOP, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_idle(void)
{
    return wifi_mgmr_api_common_msg(WIFI_MGMR_EVENT_APP_IDLE, (void*)0x1, (void*)0x2);
}

int wifi_mgmr_api_denoise_enable(void)
{
    return wifi_mgmr_api_common_msg(
        WIFI_MGMR_EVENT_APP_DENOISE,
        (void*)0x1,//use non-zero for enable denoise
        (void*)0x2
    );
}

int wifi_mgmr_api_denoise_disable(void)
{
    return wifi_mgmr_api_common_msg(
        WIFI_MGMR_EVENT_APP_DENOISE,
        (void*)0x0,//use non-zero for enable denoise
        (void*)0x2
    );
}

int wifi_mgmr_api_channel_set(int channel, int use_40Mhz)
{
    return wifi_mgmr_api_common_msg(
        WIFI_MGMR_EVENT_FW_CHANNEL_SET,
        (void*)channel,
        (void*)use_40Mhz
    );
}

/*TODO callback for RAW data send*/
int wifi_mgmr_api_raw_send(uint8_t *pkt, int len)
{
    return wifi_mgmr_api_common_msg(
        WIFI_MGMR_EVENT_FW_DATA_RAW_SEND,
        (void*)pkt,
        (void*)len
    );
}

int wifi_mgmr_api_set_country_code(char *country_code)
{
    wifi_mgmr_set_country_code_internal(country_code);

    return 0;
}

