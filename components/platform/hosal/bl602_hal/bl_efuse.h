#ifndef __BL_EFUSE_H__
#define __BL_EFUSE_H__
#include <stdint.h>
int bl_efuse_read_mac(uint8_t mac[6]);
int bl_efuse_read_mac_factory(uint8_t mac[6]);
int bl_efuse_read_capcode(uint8_t *capcode);
int bl_efuse_read_pwroft(int8_t poweroffset[14]);
int bl_efuse_ctrl_program_R0(uint32_t index, uint32_t *data, uint32_t len);
int bl_efuse_ctrl_read_R0(uint32_t index, uint32_t *data, uint32_t len);
int bl_efuse_read_mac_opt(uint8_t slot, uint8_t mac[6], uint8_t reload);
#endif
