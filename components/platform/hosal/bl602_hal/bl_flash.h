#ifndef __BL_FLASH_H__
#define __BL_FLASH_H__
#include <stdint.h>

int bl_flash_erase(uint32_t addr, int len);
int bl_flash_write(uint32_t addr, uint8_t *src, int len);
int bl_flash_read(uint32_t addr, uint8_t *dst, int len);
int bl_flash_config_update(void);
void* bl_flash_get_flashCfg(void);

int bl_flash_read_byxip(uint32_t addr, uint8_t *dst, int len);
int bl_flash_init(void);
#endif
