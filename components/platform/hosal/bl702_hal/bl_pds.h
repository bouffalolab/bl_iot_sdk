#ifndef __BL_PDS_H__
#define __BL_PDS_H__


#include "bl702_glb.h"
#include "bl702_sec_eng.h"
#include "bl702_sf_cfg.h"
#include "bl702_sflash.h"
#include "bl702_romdriver.h"


#define ATTR_NOINLINE                   __attribute__((noinline))
#define ATTR_PDS_SECTION                __attribute__((section(".pds_code." ATTR_UNI_SYMBOL)))

#define PDS_WAKEUP_BY_SLEEP_CNT         1
#define PDS_WAKEUP_BY_GPIO              2


void bl_pds_init(void);
void bl_pds_gpio_wakeup_cfg(uint8_t pin_list[], uint8_t pin_num);  // available gpio: 0 - 7, 9 - 12
void bl_pds_gpio_wakeup_cfg_ex(uint32_t bitmap);  // one bit per gpio, only for pds0 - pds3
void bl_pds_fastboot_cfg(uint32_t addr);
void bl_pds_enter(uint32_t pdsLevel, uint32_t pdsSleepCycles);
void bl_pds_fastboot_done_callback(void);
int bl_pds_get_wakeup_source(void);
uint32_t bl_pds_get_wakeup_gpio(void);


#endif
