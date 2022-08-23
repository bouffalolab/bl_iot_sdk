#ifndef __BL_EFUSE_H__
#define __BL_EFUSE_H__
#include <stdint.h>
#include <math.h>
int bl_efuse_read_mac(uint8_t mac[8]);
int bl_efuse_read_mac_factory(uint8_t mac[8]);
int bl_efuse_read_capcode(uint8_t *capcode);
int bl_efuse_read_pwroft(int8_t poweroffset[2]);
int bl_efuse_read_pwroft_ex(int8_t poweroffset_zigbee[16], int8_t poweroffset_ble[40]);
int bl_efuse_read_tsen_refcode(int16_t *refcode);
#endif
