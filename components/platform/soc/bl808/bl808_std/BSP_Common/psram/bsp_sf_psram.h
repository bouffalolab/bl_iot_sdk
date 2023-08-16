/*
 * Copyright (c) 2016-2023 Bouffalolab.
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

#ifndef __BSP_SF_PSRAM_H__
#define __BSP_SF_PSRAM_H__

#include "bl702.h"

#define BSP_PSRAM_BASE BL702_PSRAM_XIP_BASE

#define PSRAM_SIZE (2 * 1024 * 1024)

#define BFLB_EXTFLASH_CS_GPIO    GLB_GPIO_PIN_25
#define BFLB_EXTPSRAM_CLK_GPIO   GLB_GPIO_PIN_27
#define BFLB_EXTPSRAM_CS_GPIO    GLB_GPIO_PIN_17
#define BFLB_EXTPSRAM_DATA0_GPIO GLB_GPIO_PIN_28
#define BFLB_EXTPSRAM_DATA1_GPIO GLB_GPIO_PIN_24
#define BFLB_EXTPSRAM_DATA2_GPIO GLB_GPIO_PIN_23
#define BFLB_EXTPSRAM_DATA3_GPIO GLB_GPIO_PIN_26

void bsp_sf_psram_gpio_init(void);
void bsp_sf_psram_init(uint8_t sw_reset);
void bsp_sf_psram_read_id(uint8_t *data);

#endif /* __BSP_SF_PSRAM_H__ */
