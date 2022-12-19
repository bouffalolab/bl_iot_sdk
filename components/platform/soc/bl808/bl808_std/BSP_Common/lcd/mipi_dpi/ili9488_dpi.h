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

#ifndef _ILI9488_DBI_H_
#define _ILI9488_DBI_H_

#include "bflb_platform.h"
#include "bl_mipi_dpi.h"

/* Optional initialization interface */
#define ILI9488_DPI_INIT_INTERFACE_SPI        0
#define ILI9488_DPI_INIT_INTERFACE_DBI_TYPE_C 1

/* Select pixel format */
#define ILI9488_DPI_PIXEL_FORMAT LCD_MIPI_DPI_PIXEL_FORMAT_RGB565

/* Select Initialize interface */
#define ILI9488_DPI_INIT_INTERFACE ILI9488_DPI_INIT_INTERFACE_SPI

/* Select SPI Initialize interface pin */
#if ILI9488_DPI_INIT_INTERFACE == ILI9488_DPI_INIT_INTERFACE_SPI

#define ILI9488_SPI_CS_PIN GPIO_PIN_20
#define ILI9488_SPI_DC_PIN GPIO_PIN_3

#define ILI9488_SPI_CS_HIGH gpio_write(ILI9488_SPI_CS_PIN, 1)
#define ILI9488_SPI_CS_LOW  gpio_write(ILI9488_SPI_CS_PIN, 0)
#define ILI9488_SPI_DC_HIGH gpio_write(ILI9488_SPI_DC_PIN, 1)
#define ILI9488_SPI_DC_LOW  gpio_write(ILI9488_SPI_DC_PIN, 0)

#endif

/* Do not modify the following information */

/* ILI9481 LCD Active Width */
#define ILI9488_DPI_W 320
/* ILI9481 LCD Active Height */
#define ILI9488_DPI_H 480

#if (ILI9488_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565)
#define ILI9488_DPI_COLOR_DEPTH 16
typedef uint16_t ili9488_dpi_color_t;
#elif (ILI9488_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888)
#define ILI9488_DPI_COLOR_DEPTH 32
typedef uint32_t ili9488_dpi_color_t;
#else
#error "ILI9488 pixel format select error"
#endif

/* Ili9488 needs to be initialized using the DBI(typeC) or SPI interface */
typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} ili9488_dpi_init_cmd_t;

int ili9488_dpi_init(ili9488_dpi_color_t *screen_buffer);
int ili9488_dpi_screen_switch(ili9488_dpi_color_t *screen_buffer);
ili9488_dpi_color_t *ili9488_dpi_get_screen_using(void);
int ili9488_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
