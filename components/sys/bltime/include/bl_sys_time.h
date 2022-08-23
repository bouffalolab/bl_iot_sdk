#ifndef __BL_SYS_TIME_H__
#define __BL_SYS_TIME_H__

#include <stdint.h>
#include "bl_rtc.h"

void bl_sys_time_update(uint64_t epoch);
int bl_sys_time_get(uint64_t *epoch);
int bl_sys_time_cli_init(void);

void bl_sys_time_sync_init(void);
int bl_sys_time_sync_state(uint32_t *xTicksToJump);
uint32_t bl_sys_time_sync(void);

#endif
