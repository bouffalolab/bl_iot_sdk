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
#include "blsync_ble_app.h"
#include "wifi_prov_api.h"
#include <FreeRTOS.h>
#include <task.h>
#include "blsync_ble.h"
#include "bluetooth.h"
#include "ble_cli_cmds.h"
#include "hci_driver.h"
#include "ble_lib_api.h"
#include <aos/yloop.h>
#include <cli.h>
#include "at_server.h"

static bl_ble_sync_t *gp_index = NULL;

static void wifiprov_connect_ap_ind(struct wifi_conn *info)
{
    extern int wifi_mgmr_status_code_clean_internal();
    wifi_mgmr_status_code_clean_internal();
    printf("Recevied indication to connect to AP\r\n");
    wifi_prov_api_event_trigger_connect(info);
}

static void wifiprov_disc_from_ap_ind(void)
{
    printf("Recevied indication to disconnect to AP\r\n");
    wifi_prov_api_event_trigger_disconnect();
}

static void wifiprov_wifi_scan(void(*complete)(void *))
{
    printf("Recevied indication to wifi scan\r\n");
    wifi_prov_api_event_trigger_scan(complete);
}

static void wifiprov_api_state_get(void(*state_get)(void *))
{
    printf("Recevied indication to wifi state get\r\n");
    wifi_prov_api_event_state_get(state_get);
}

static void blesync_complete_cb (void *p_arg)
{

}

static struct blesync_wifi_func WifiProv_conn_callback = {
    .local_connect_remote_ap = wifiprov_connect_ap_ind,
    .local_disconnect_remote_ap = wifiprov_disc_from_ap_ind,
    .local_wifi_scan = wifiprov_wifi_scan,
    .local_wifi_state_get = wifiprov_api_state_get,
};

static void app_delayed_action_bleadv(void *arg)
{
    char *cmd1 = "ble_init\r\n";
    char *cmd2 = "ble_start_adv 0 0 0x100 0x100\r\n";

    aos_cli_input_direct(cmd1, strlen(cmd1));
    aos_cli_input_direct(cmd2, strlen(cmd2));
}

static void blsync_disconnected(struct bt_conn *conn, u8_t reason)
{
    printf("disconnected (reason %u)\r\n",reason);
    at_server_notify_with_ctx(AT_BLE_DISCONNECTED, NULL, 0);
}

static void blsync_connected(struct bt_conn *conn, u8_t err)
{
    const bt_addr_le_t *addr = bt_conn_get_dst(conn);
    at_server_notify_with_ctx(AT_BLE_CONNECTED, (void *)&addr->a, sizeof(addr->a));
    printf("%s\n",__func__);
}


static struct bt_conn_cb blsync_cb = {
    .connected  =   blsync_connected,
    .disconnected   =   blsync_disconnected,
};

void blsync_ble_start(void)
{
    static uint8_t inited = 0;

    if (inited == 0) {
        inited = 1;
        bt_conn_cb_register(&blsync_cb);
    }
    if (gp_index != NULL) {
        printf("blsync already started\r\n");
        return;
    }
    gp_index = pvPortMalloc(sizeof(bl_ble_sync_t));
    if (gp_index == NULL) {
        return;
    }
    bl_ble_sync_start(gp_index,
                      &WifiProv_conn_callback,
                      blesync_complete_cb,
                      (void *)gp_index);
    aos_post_delayed_action(500, app_delayed_action_bleadv, NULL);
}

static void app_delayed_action_bleadvstop(void *arg)
{
    char *cmd3 = "ble_stop_adv\r\n";
    aos_cli_input_direct(cmd3, strlen(cmd3));
    bl_ble_sync_stop(gp_index);
    vPortFree(gp_index);
    gp_index = NULL;
}

void blsync_ble_stop(void)
{
    aos_post_delayed_action(100, app_delayed_action_bleadvstop, NULL);
}

