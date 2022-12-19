/*
 * Copyright (c) 2016-2022 Bouffalolab.
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

#ifndef _TOUCH_H_
#define _TOUCH_H_

#include "bflb_platform.h"

/* spi interface
    TOUCH_SPI_XPT2046  // Not currently supported
*/

/* i2c interface
    TOUCH_I2C_FT6X36
    TOUCH_I2C_GT911
*/

/* Select Touch Type */
#define TOUCH_I2C_GT911

#define TOUCH_INTERFACE_SPI 1
#define TOUCH_INTERFACE_I2C 2

typedef struct
{
    uint16_t coord_x;
    uint16_t coord_y;
} touch_coord_t;

#if defined TOUCH_SPI_XPT2046

#include "xpt2046_spi.h"
#define TOUCH_INTERFACE_TYPE           TOUCH_INTERFACE_SPI
#define TOUCH_MAX_POINT                XPT2046_MAX_POINT
#define _TOUCH_FUNC_DEFINE(_func, ...) xpt2046_spi_##_func(__VA_ARGS__)

#elif defined TOUCH_I2C_FT6X36

#include "ft6x36_i2c.h"
#define TOUCH_INTERFACE_TYPE           TOUCH_INTERFACE_I2C
#define TOUCH_MAX_POINT                FT6X36_I2C_MAX_POINT
#define _TOUCH_FUNC_DEFINE(_func, ...) ft6x36_i2c_##_func(__VA_ARGS__)

#elif defined TOUCH_I2C_GT911

#include "gt911_i2c.h"
#define TOUCH_INTERFACE_TYPE           TOUCH_INTERFACE_I2C
#define TOUCH_MAX_POINT                GT911_I2C_MAX_POINT
#define _TOUCH_FUNC_DEFINE(_func, ...) gt911_i2c_##_func(__VA_ARGS__)

#elif
#error "Please select a touch type"
#endif

int touch_init(touch_coord_t *max_value);
int touch_read(uint8_t *point_num, touch_coord_t *touch_coord, uint8_t max_num);

#endif