#ifndef __HOSAL_OTA_H__
#define __HOSAL_OTA_H__
#include <stdint.h>

#define HOSAL_OTA_FILE_SIZE_MAX    0x100000  // 1M

int hosal_ota_start(uint32_t file_size);
int hosal_ota_update(uint32_t filesize, uint32_t offset, uint8_t *buf, uint32_t buf_len);
int hosal_ota_finish(uint8_t check_hash, uint8_t auto_reset);
int hosal_ota_read(uint32_t offset, uint8_t *buf, uint32_t buf_len);

#endif
