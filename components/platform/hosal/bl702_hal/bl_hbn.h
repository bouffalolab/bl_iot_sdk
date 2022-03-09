/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_HBN_H__
#define __BL_HBN_H__


#include "bl702_glb.h"
#include "bl702_sec_eng.h"
#include "bl702_sf_cfg.h"
#include "bl702_sflash.h"
#include "bl702_romdriver.h"


#define ATTR_NOINLINE              __attribute__((noinline))
#define ATTR_HBN_CODE_SECTION      __attribute__((section(".hbn_code." ATTR_UNI_SYMBOL)))
#define ATTR_HBN_DATA_SECTION      __attribute__((section(".hbn_data")))
#define ATTR_HBN_NOINIT_SECTION    __attribute__((section(".hbn_noinit")))

#define HBN_WAKEUP_BY_RTC          1
#define HBN_WAKEUP_BY_GPIO         2


void bl_hbn_fastboot_init(void);
void bl_hbn_gpio_wakeup_cfg(uint8_t pin_list[], uint8_t pin_num);  // available gpio: 9 - 12
void bl_hbn_enter_with_fastboot(uint32_t hbnSleepCycles);
void bl_hbn_fastboot_done_callback(void);
int bl_hbn_get_wakeup_source(void);
uint32_t bl_hbn_get_wakeup_gpio(void);


typedef struct _hbn_type {
    uint8_t buflen;
    uint8_t active;
    uint8_t buf[1];
} hbn_type_t;

int bl_hbn_enter(hbn_type_t *hbn, uint32_t *time);

#endif

