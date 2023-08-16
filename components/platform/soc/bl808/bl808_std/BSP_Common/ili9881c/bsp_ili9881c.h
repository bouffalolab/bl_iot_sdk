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
#ifndef __ILI9881C_H__
#define __ILI9881C_H__

#include "hal_gpio.h"
/** @addtogroup  BL702_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ILI9881C
 *  @{
 */

/** @defgroup  ILI9881C_Public_Types
 *  @{
 */

/*@} end of group ILI9881C_Public_Types */

/** @defgroup  ILI9881C_Public_Constants
 *  @{
 */

/*@} end of group ILI9881C_Public_Constants */

/** @defgroup  ILI9881C_Public_Macros
 *  @{
 */
#define DSI_LANE_NUMBER_USE    2
#define DSI_ILI9881C_BSIT_MODE 0
#define LCD_CS_PIN             GPIO_PIN_10
#define LCD_DC_PIN             GPIO_PIN_22

#define CS1_HIGH gpio_write(LCD_CS_PIN, 1)
#define CS1_LOW  gpio_write(LCD_CS_PIN, 0)
#define DC_HIGH  gpio_write(LCD_DC_PIN, 1)
#define DC_LOW   gpio_write(LCD_DC_PIN, 0)
#define LCD_W    240 /* LCD width */
#define LCD_H    320 /* LCD height */
/* Turn 24-bit RGB color to 16-bit */
#define RGB(r, g, b) (((r >> 3) << 3 | (g >> 5) | (g >> 2) << 13 | (b >> 3) << 8) & 0xffff)
/* Calculate 32-bit or 16-bit absolute value */
#define ABS32(value) ((value ^ (value >> 31)) - (value >> 31))
#define ABS16(value) ((value ^ (value >> 15)) - (value >> 15))

/*@} end of group ILI9881C_Public_Macros */

/** @defgroup  ILI9881C_Public_Functions
 *  @{
 */

/**
 *  @brief ILI9881C Functions
 */

int display_prepare(void);
int display_enable(void);
int display_disable(void);
int display_unprepare(void);

/*@} end of group ILI9881C_Public_Functions */

/*@} end of group ILI9881C */

/*@} end of group BL702_Peripheral_Driver */

#endif /* __ILI9881C_H__ */
