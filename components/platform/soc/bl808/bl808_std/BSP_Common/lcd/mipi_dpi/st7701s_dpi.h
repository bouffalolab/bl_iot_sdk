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

#ifndef _ST7701S_DBI_H_
#define _ST7701S_DBI_H_

#include "bflb_platform.h"
#include "bl_mipi_dpi.h"

/* Optional initialization interface */
#define ST7701S_DPI_INIT_INTERFACE_SPI        0
#define ST7701S_DPI_INIT_INTERFACE_DBI_TYPE_C 1

/* Select pixel format */
#define ST7701S_DPI_PIXEL_FORMAT LCD_MIPI_DPI_PIXEL_FORMAT_RGB565

/* Select Initialize interface */
#define ST7701S_DPI_INIT_INTERFACE ST7701S_DPI_INIT_INTERFACE_SPI

#if ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_SPI

/* Select SPI Initialize interface pin */
#define ST7701S_SPI_CS_PIN GPIO_PIN_0

#define ST7701S_SPI_CS_HIGH gpio_write(ST7701S_SPI_CS_PIN, 1)
#define ST7701S_SPI_CS_LOW  gpio_write(ST7701S_SPI_CS_PIN, 0)

#endif

/* Do not modify the following information */

/* ST7701S LCD Active Width */
#define ST7701S_DPI_W 480
/* ST7701S LCD Active Height */
#define ST7701S_DPI_H 800

#if (ST7701S_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565)
#define ST7701S_DPI_COLOR_DEPTH 16
typedef uint16_t st7701s_dpi_color_t;
#elif (ST7701S_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888)
#define ST7701S_DPI_COLOR_DEPTH 32
typedef uint32_t st7701s_dpi_color_t;
#else
#error "ST7701S pixel format select error"
#endif

/* Ili9481 needs to be initialized using the DBI(typeC) or SPI interface */
typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} st7701s_dpi_init_cmd_t;

int st7701s_dpi_init(st7701s_dpi_color_t *screen_buffer);
int st7701s_dpi_screen_switch(st7701s_dpi_color_t *screen_buffer);
st7701s_dpi_color_t *st7701s_dpi_get_screen_using(void);
int st7701s_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
