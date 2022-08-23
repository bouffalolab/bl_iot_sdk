#ifndef __BL_PDS_H__
#define __BL_PDS_H__

#include <stdint.h>

void bl_pds_init(void);
void bl_pds_fastboot_cfg(uint32_t addr);
void bl_pds_enter(uint32_t pdsLevel, uint32_t pdsSleepCycles);

int bl_pds_rf_turnon(void *arg);
int bl_pds_rf_turnoff(void *arg);

#endif
