#ifndef __BL_WIRELESS_H__
#define __BL_WIRELESS_H__

#include <stdint.h>

int bl_wireless_mac_addr_set(uint8_t mac[8]);
int bl_wireless_mac_addr_get(uint8_t mac[8]);
int bl_wireless_power_offset_set(int8_t poweroffset_zigbee[16], int8_t poweroffset_ble[40]);
int bl_wireless_power_offset_get(int8_t poweroffset_zigbee[16], int8_t poweroffset_ble[40]);
int8_t bl_wireless_power_offset_zigbee_get(uint8_t ch);
int8_t bl_wireless_power_offset_ble_get(uint8_t ch);
void bl_wireless_tcal_en_set(uint8_t en);
uint8_t bl_wireless_tcal_en_get(void);

#endif
