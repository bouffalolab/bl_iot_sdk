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

#ifndef _ILI9341_SPI_H_
#define _ILI9341_SPI_H_

#include "bflb_platform.h"

#define ILI9341_SPI_CS_PIN GPIO_PIN_10
#define ILI9341_SPI_DC_PIN GPIO_PIN_22

#define ILI9341_SPI_CS_HIGH gpio_write(ILI9341_SPI_CS_PIN, 1)
#define ILI9341_SPI_CS_LOW  gpio_write(ILI9341_SPI_CS_PIN, 0)
#define ILI9341_SPI_DC_HIGH gpio_write(ILI9341_SPI_DC_PIN, 1)
#define ILI9341_SPI_DC_LOW  gpio_write(ILI9341_SPI_DC_PIN, 0)

#define ILI9341_SPI_W 240 /* ILI9341 LCD width */
#define ILI9341_SPI_H 320 /* ILI9341 LCD height */

#define ILI9341_SPI_OFFSET_X 0
#define ILI9341_SPI_OFFSET_Y 0

#define ILI9341_SPI_COLOR_DEPTH 16

typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} ili9341_spi_init_cmd_t;

typedef uint16_t ili9341_spi_color_t;

int ili9341_spi_init();
void ili9341_spi_async_callback_register(void (*callback)(void));
int ili9341_spi_set_dir(uint8_t dir, uint8_t mir_flag);
void ili9341_spi_set_draw_window(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void ili9341_spi_draw_point(uint16_t x, uint16_t y, ili9341_spi_color_t color);
void ili9341_spi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9341_spi_color_t color);
void ili9341_spi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9341_spi_color_t *picture);
void ili9341_spi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9341_spi_color_t *picture);
int ili9341_spi_draw_is_busy(void);

#endif