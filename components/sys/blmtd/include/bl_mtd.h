#ifndef __BL_MTD_H__
#define __BL_MTD_H__
#include <stdint.h>

typedef void *bl_mtd_handle_t;
typedef struct {
    char name[16];
    unsigned int offset;
    unsigned int size;
    void *xip_addr;
} bl_mtd_info_t;

#define BL_MTD_OPEN_FLAG_NONE           (0)
/* open backup partition */
#define BL_MTD_OPEN_FLAG_BACKUP        (1 << 0)
#define BL_MTD_OPEN_FLAG_BUSADDR       (1 << 1)
int bl_mtd_open(const char *name, bl_mtd_handle_t *handle, unsigned int flags);
int bl_mtd_close(bl_mtd_handle_t handle);
int bl_mtd_info(bl_mtd_handle_t handle, bl_mtd_info_t *info);
int bl_mtd_erase(bl_mtd_handle_t handle, unsigned int addr, unsigned int size);
int bl_mtd_erase_all(bl_mtd_handle_t handle);
int bl_mtd_write(bl_mtd_handle_t handle, unsigned int addr, unsigned int size, const uint8_t *data);
int bl_mtd_read(bl_mtd_handle_t handle,  unsigned int addr, unsigned int size, uint8_t *data);
int bl_mtd_size(bl_mtd_handle_t handle, unsigned int *size);

#define BL_MTD_PARTITION_NAME_PSM               "PSM"
#define BL_MTD_PARTITION_NAME_FW_DEFAULT        "FW"
#define BL_MTD_PARTITION_NAME_ROMFS             "media"

#endif
