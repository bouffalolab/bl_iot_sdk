#ifndef __HAL_PDS_H__
#define __HAL_PDS_H__

#include "bl_pds.h"
#include <utils_list.h>

void hal_pds_init(void);
void hal_pds_fastboot_cfg(uint32_t addr);
void hal_pds_enter_without_time_compensation(uint32_t pdsLevel, uint32_t pdsSleepCycles);
uint32_t hal_pds_enter_with_time_compensation(uint32_t pdsLevel, uint32_t pdsSleepCycles);
#endif
