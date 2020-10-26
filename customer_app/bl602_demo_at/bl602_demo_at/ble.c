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
#include <FreeRTOS.h>
#include <task.h>

#include "bluetooth.h"
#include "ble_cli_cmds.h"
#if defined(CONFIG_BT_MESH)
#include "mesh_cli_cmds.h"
#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
#include "gen_srv.h"
#include "bl_gpio.h"
#endif
#endif
#include "hci_driver.h"
#include "ble_lib_api.h"
#if defined(CONFIG_BT_WIFIPROV_SERVER)
#include "wifi_prov.h"
#endif
#include "log.h"
#include "wifi_prov_api.h"
#if defined(CONFIG_BLE_TP_SERVER)
#include "ble_tp_svc.h"
#endif

#if defined(CONFIG_BT_WIFIPROV_SERVER)
static void wifiprov_connect_ap_ind(void)
{
    printf("Recevied indication to connect to AP\r\n");    
    wifi_prov_api_event_trigger_connect();
}

static void wifiprov_disc_from_ap_ind(void)
{
    printf("Recevied indication to disconnect to AP\r\n");
    wifi_prov_api_event_trigger_disconnect();
}

static void wifiprov_ssid_ind(void *buf,size_t size)
{
    printf("Recevied ssid : %s \r\n", bt_hex(buf, size));
    wifi_prov_api_event_trigger_ssid(buf, size);
}

static void wifiprov_bssid_ind(void *buf,size_t size)
{
    
    printf("Recevied bssid: %s \r\n", bt_hex(buf, size));
}

static void wifiprov_password_ind(void *buf,size_t size)
{
    printf("Recevied password: %s \r\n", bt_hex(buf, size));
    wifi_prov_api_event_trigger_password(buf, size);
}

struct conn_callback WifiProv_conn_callback = {
	.local_connect_remote_ap = wifiprov_connect_ap_ind,
	.local_disconnect_remote_ap = wifiprov_disc_from_ap_ind,
	.get_remote_ap_ssid = wifiprov_ssid_ind,
	.get_remote_ap_bssid = wifiprov_bssid_ind,
	.get_remote_password = wifiprov_password_ind,
};
#endif


#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
//#define LED_PIN         (21)
#define LED_PIN         (5)
#define LED_PIN_PULLUP  (0)
#define LED_PIN_PULDONW (0)

void model_gen_cb(uint8_t value)
{
    bl_gpio_output_set(LED_PIN, value); 
}
#endif

void bt_enable_cb(int err)
{
    if (!err) {     
        ble_cli_register();
#if defined(CONFIG_BT_STACK_PTS)
        pts_cli_register();
#endif

#if defined(CONFIG_BT_MESH)
        blemesh_cli_register();
#if defined(CONFIG_BT_MESH_MODEL_GEN_SRV)
        bl_gpio_enable_output(LED_PIN, LED_PIN_PULLUP, LED_PIN_PULDONW);
        mesh_gen_srv_callback_register(model_gen_cb); 
#endif
#endif

#if defined(CONFIG_BT_WIFIPROV_SERVER)
        WifiProv_init(&WifiProv_conn_callback);
#endif

#if defined(CONFIG_BLE_TP_SERVER)
        ble_tp_init();
#endif
    }
}

void ble_stack_start(void)
{
     // Initialize BLE controller
    ble_controller_init(configMAX_PRIORITIES - 1);
    // Initialize BLE Host stack
    hci_driver_init();
    bt_enable(bt_enable_cb);
}
