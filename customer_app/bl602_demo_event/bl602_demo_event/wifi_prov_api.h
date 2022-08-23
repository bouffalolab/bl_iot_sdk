#ifndef __WIFI_PROV_API_H__
#define __WIFI_PROV_API_H__

#if defined(CONFIG_BT_MESH_SYNC)
#include "blsync_ble.h"

int wifi_prov_api_event_trigger_connect_mesh(struct wifi_conn *info);
int wifi_prov_api_event_trigger_disconnect_mesh(void);
int wifi_prov_api_event_trigger_scan_mesh(void(*complete)(void *));
int wifi_prov_api_event_state_get_mesh(void(*state_get)(void *));
#endif /* CONFIG_BT_MESH_SYNC */

int wifi_prov_api_event_trigger_connect(void);
int wifi_prov_api_event_trigger_disconnect(void);

/*set len to the ssid len, if ssid is NOT '\0' tailed*/
int wifi_prov_api_event_trigger_ssid(const char *ssid, int len);

/*set len to the ssid len, if ssid is NOT '\0' tailed*/
int wifi_prov_api_event_trigger_password(const char *password, int len);
#endif
