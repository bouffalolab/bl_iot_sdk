/*
 * Copyright (c) 2016-2023 Bouffalolab.
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
#include <rnm_client_cmds.h>

#include <string.h>
#include <rnm_utils.h>

#define INPUT_COMMON_CHECK(truth)  \
    if (!(truth)) {                \
        return RNMC_INVALID_INPUT; \
    }

static rnmc_ret_t send_cmd_with_pld_rsp(rnmc_t *rnm, rnm_base_msg_t *msg, int extra_timeout_ms, void **result)
{
    rnmc_ret_t ret;
    rnm_msg_t resp;
    void *copy;

    ret = rnmc_cmd_send(rnm, msg, sizeof(*msg), &resp, extra_timeout_ms + RNMC_DEFAULT_CMD_TIMEOUT_MS);
    if (RNMC_OK != ret) {
        return ret;
    }
    ret = resp.cmd.status;
    if (RNMC_OK == ret) {
        if ((copy = rnm_malloc(resp.data_len))) {
            memcpy(copy, resp.data, resp.data_len);
            *result = copy;
        } else {
            ret = RNMC_NOMEM;
        }
        resp.free_fn(resp.data);
    }
    return ret;
}

rnmc_ret_t rnmc_reset(rnmc_t *rnm)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm);

    rnm->mode = RNMC_WIFI_MODE_NONE;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_RESET;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), 12 * 1000 + RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_sta_connect(rnmc_t *rnm, const uint8_t *ssid, uint16_t ssid_len, const uint8_t *password)
{
    rnm_sta_connect_msg_t msg;

    INPUT_COMMON_CHECK(rnm && ssid && ssid_len);

    if (!(rnm->mode == RNMC_WIFI_MODE_NONE || rnm->mode == RNMC_WIFI_MODE_STA)) {
        return RNMC_INVALID_MODE;
    }
    memset(&msg, 0, sizeof(msg));
    msg.hdr.cmd = BF1B_CMD_STA_CONNECT;
    msg.ssid_len = ssid_len;
    memcpy(msg.ssid, ssid, ssid_len);
    if (password) {
        strcpy((char *)msg.password, (char *)password);
    }
    rnm->mode = RNMC_WIFI_MODE_STA;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_sta_disconnect(rnmc_t *rnm)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm);

    if (!(rnm->mode == RNMC_WIFI_MODE_STA)) {
        return RNMC_INVALID_MODE;
    }
    rnm->mode = RNMC_WIFI_MODE_NONE;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_STA_DISCONNECT;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), 12 * 1000 + RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_get_mac_addr(rnmc_t *rnm, uint8_t *mac)
{
    rnm_base_msg_t msg;
    rnm_mac_addr_ind_msg_t *result = NULL;
    rnmc_ret_t ret;

    INPUT_COMMON_CHECK(rnm && mac);

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_GET_MAC_ADDR;

    if (RNMC_OK != (ret = send_cmd_with_pld_rsp(rnm, &msg, 0, (void **)&result))) {
        return ret;
    }
    rnm_debug("got STA MAC ADDR " MAC_ADDR_FMT " AP MAC ADDR " MAC_ADDR_FMT "\r\n", ARR_ELE_LIST_6(result->sta_mac), ARR_ELE_LIST_6(result->ap_mac));
    memcpy(mac, result->sta_mac, 6);
    rnm_free(result);
    return ret;
}

rnmc_ret_t rnmc_scan(rnmc_t *rnm, rnm_scan_ind_msg_t **result)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm && result);

    if (!(rnm->mode == RNMC_WIFI_MODE_NONE)) {
        return RNMC_INVALID_MODE;
    }

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_SCAN;

    return send_cmd_with_pld_rsp(rnm, &msg, 15 * 1000, (void **)result);
}

rnmc_ret_t rnmc_sta_get_link_status(rnmc_t *rnm, struct bf1b_wifi_ap_record *status)
{
    rnm_base_msg_t msg;
    rnm_sta_link_status_ind_msg_t *result = NULL;
    rnmc_ret_t ret;

    INPUT_COMMON_CHECK(rnm && status);

    if (!(rnm->mode == RNMC_WIFI_MODE_STA)) {
        return RNMC_INVALID_MODE;
    }

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_STA_GET_LINK_STATUS;

    if (RNMC_OK != (ret = send_cmd_with_pld_rsp(rnm, &msg, 0, (void **)&result))) {
        return ret;
    }
    memcpy(status, &result->record, sizeof(*status));
    rnm_free(result);
    return ret;
}

rnmc_ret_t rnmc_ap_start(rnmc_t *rnm, uint16_t channel, uint16_t ssid_len, const uint8_t *ssid, const char *password)
{
    rnm_ap_start_msg_t msg;

    INPUT_COMMON_CHECK(rnm && channel && (ssid_len <= 32) && ssid);

    if (!(rnm->mode == RNMC_WIFI_MODE_NONE)) {
        return RNMC_INVALID_MODE;
    }

    if (password) {
        size_t len = strlen(password);
        if (!(len >= 8 && len <= 63)) {
            return RNMC_INVALID_INPUT;
        }
    }
    memset(&msg, 0, sizeof(msg));
    msg.hdr.cmd = BF1B_CMD_AP_START;
    msg.is_open = password ? 0 : 1;
    msg.channel = channel;
    msg.ssid_len = ssid_len;
    memcpy(msg.ssid, ssid, ssid_len);
    if (password) {
        strcpy((char *)msg.password, password);
    }
    rnm->mode = RNMC_WIFI_MODE_AP;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_ap_stop(rnmc_t *rnm)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm);

    if (!(rnm->mode == RNMC_WIFI_MODE_AP)) {
        return RNMC_INVALID_MODE;
    }
    rnm->mode = RNMC_WIFI_MODE_NONE;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_AP_STOP;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_ap_get_sta_list(rnmc_t *rnm, rnm_ap_sta_list_ind_msg_t **result)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm && result);

    if (!(rnm->mode == RNMC_WIFI_MODE_AP)) {
        return RNMC_INVALID_MODE;
    }

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_AP_GET_STA_LIST;

    return send_cmd_with_pld_rsp(rnm, &msg, 0, (void **)result);
}

rnmc_ret_t rnmc_sniffer_start(rnmc_t *rnm)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm);

    if (!(rnm->mode == RNMC_WIFI_MODE_NONE)) {
        return RNMC_INVALID_MODE;
    }
    rnm->mode = RNMC_WIFI_MODE_SNIFFER;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_MONITOR_START;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_sniffer_stop(rnmc_t *rnm)
{
    rnm_base_msg_t msg;

    INPUT_COMMON_CHECK(rnm);

    if (!(rnm->mode == RNMC_WIFI_MODE_SNIFFER)) {
        return RNMC_INVALID_MODE;
    }
    rnm->mode = RNMC_WIFI_MODE_NONE;

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_MONITOR_STOP;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_sniffer_set_channel(rnmc_t *rnm, uint16_t channel)
{
    rnm_monitor_set_channel_msg_t msg;

    INPUT_COMMON_CHECK(rnm && channel);

    if (!(rnm->mode == RNMC_WIFI_MODE_SNIFFER)) {
        return RNMC_INVALID_MODE;
    }
    memset(&msg, 0, sizeof(msg));
    msg.hdr.cmd = BF1B_CMD_MONITOR_SET_CHANNEL;
    msg.channel = channel;
    return rnmc_cmd_send_simple(rnm, &msg, sizeof(msg), RNMC_DEFAULT_CMD_TIMEOUT_MS);
}

rnmc_ret_t rnmc_sniffer_get_channel(rnmc_t *rnm, uint16_t *channel)
{
    rnm_base_msg_t msg;
    rnm_monitor_channel_ind_msg_t *result = NULL;
    rnmc_ret_t ret;

    INPUT_COMMON_CHECK(rnm && channel);

    if (!(rnm->mode == RNMC_WIFI_MODE_SNIFFER)) {
        return RNMC_INVALID_MODE;
    }

    memset(&msg, 0, sizeof(msg));
    msg.cmd = BF1B_CMD_MONITOR_GET_CHANNEL;

    if (RNMC_OK != (ret = send_cmd_with_pld_rsp(rnm, &msg, 0, (void **)&result))) {
        return ret;
    }
    *channel = result->channel;
    rnm_free(result);
    return ret;
}
