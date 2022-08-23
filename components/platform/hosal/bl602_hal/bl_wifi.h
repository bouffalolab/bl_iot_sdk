#ifndef __BL_WIFI_H__
#define __BL_WIFI_H__
typedef struct bl_wifi_ap_info {
    uint8_t ssid[33];
    uint8_t psk[65];
    uint8_t chan;
} bl_wifi_ap_info_t;


int bl_wifi_enable_irq(void);
int bl_wifi_clock_enable(void);
int bl_wifi_sta_mac_addr_set(uint8_t mac[6]);
int bl_wifi_ap_mac_addr_set(uint8_t mac[6]);
int bl_wifi_mac_addr_set(uint8_t mac[6]);
int bl_wifi_country_code_set(uint8_t country_code);
int bl_wifi_ap_info_set(uint8_t* ssid, uint8_t ssid_len, 
                      uint8_t* psk, uint8_t psk_len,
                      uint8_t chan);
int bl_wifi_mac_addr_get(uint8_t mac[6]);
int bl_wifi_ap_info_get(bl_wifi_ap_info_t* ap_info);
int bl_wifi_sta_info_set(uint8_t* ssid, uint8_t ssid_len, uint8_t* psk, uint8_t psk_len, int autoconnect);
int bl_wifi_sta_info_get(bl_wifi_ap_info_t* sta_info);
#endif
