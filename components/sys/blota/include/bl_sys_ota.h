#ifndef __BL_SYS_OTA_H__
#define __BL_SYS_OTA_H__
#include <stdint.h>

#define LWIP_CONFIG_ENABLE_IPV4 1

#define OTA_PROGRAM_SIZE (512)
#define OTA_TCP_PORT     3333

int bl_sys_ota_cli_init(void);

#endif
