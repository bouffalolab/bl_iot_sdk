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

#ifndef _LCD_H_
#define _LCD_H_

#include "font.h"

/* Select screen Type */
/* 选择使用的接口与屏幕 */
// #define LCD_DBI_ILI9488
// #define LCD_DISP_QSPI_GC9C01
// #define LCD_DPI_ILI9488
#define LCD_DPI_STANDARD
// #define LCD_DSI_VIDIO_ILI9881C
// #define LCD_SPI_ILI9488
// #define LCD_SPI_ILI9341
// #define LCD_SPI_ST7796

#define LCD_INTERFACE_SPI       1
#define LCD_INTERFACE_DBI       2
#define LCD_INTERFACE_DPI       3
#define LCD_INTERFACE_DSI_VIDIO 4

#if defined LCD_DBI_ILI9488

#include "mipi_dbi/ili9488_dbi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_DBI
#define LCD_W                        ILI9488_DBI_W
#define LCD_H                        ILI9488_DBI_H
#define LCD_COLOR_DEPTH              ILI9488_DBI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) ili9488_dbi_##_func(__VA_ARGS__)

#elif defined LCD_DISP_QSPI_GC9C01

#include "disp_qspi/gc9c01_disp_qspi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_DBI
#define LCD_W                        GC9C01_DISP_QSPI_W
#define LCD_H                        GC9C01_DISP_QSPI_H
#define LCD_COLOR_DEPTH              GC9C01_DISP_QSPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) gc9c01_disp_qspi_##_func(__VA_ARGS__)

#elif defined LCD_DPI_ILI9488

#include "mipi_dpi/ili9488_dpi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_DPI
#define LCD_W                        ILI9488_DPI_W
#define LCD_H                        ILI9488_DPI_H
#define LCD_COLOR_DEPTH              ILI9488_DPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) ili9488_dpi_##_func(__VA_ARGS__)

#elif defined LCD_DPI_STANDARD

#include "mipi_dpi/standard_dpi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_DPI
#define LCD_W                        STANDARD_DPI_W
#define LCD_H                        STANDARD_DPI_H
#define LCD_COLOR_DEPTH              STANDARD_DPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) standard_dpi_##_func(__VA_ARGS__)

#elif defined LCD_DSI_VIDIO_ILI9881C

#include "mipi_dsi/ili9881c_dsi_vidio.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_DSI_VIDIO
#define LCD_W                        ILI9881C_DSI_VIDIO_W
#define LCD_H                        ILI9881C_DSI_VIDIO_H
#define LCD_COLOR_DEPTH              ILI9881C_DSI_VIDIO_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) ili9881c_dsi_vidio_##_func(__VA_ARGS__)

#elif defined LCD_SPI_ILI9488

#include "spi/ili9488_spi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_SPI
#define LCD_W                        ILI9488_SPI_W
#define LCD_H                        ILI9488_SPI_H
#define LCD_COLOR_DEPTH              ILI9488_SPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) ili9488_spi_##_func(__VA_ARGS__)

#elif defined LCD_SPI_ILI9341

#include "spi/ili9341_spi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_SPI
#define LCD_W                        ILI9341_SPI_W
#define LCD_H                        ILI9341_SPI_H
#define LCD_COLOR_DEPTH              ILI9341_SPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) ili9341_spi_##_func(__VA_ARGS__)

#elif defined LCD_SPI_ST7796

#include "spi/st7796_spi.h"
#define LCD_INTERFACE_TYPE           LCD_INTERFACE_SPI
#define LCD_W                        ST7796_SPI_W
#define LCD_H                        ST7796_SPI_H
#define LCD_COLOR_DEPTH              ST7796_SPI_COLOR_DEPTH
#define _LCD_FUNC_DEFINE(_func, ...) st7796_spi_##_func(__VA_ARGS__)

#elif
#error "Please select a screen type"
#endif

#define LCD_COLOR_RGB888(r, g, b) (((r << 16) | (g << 8) | (b)) & 0xffffff)
#define LCD_COLOR_RGB565(r, g, b) (((r >> 3) << 11 | (g >> 2) << 5 | (b >> 3)) & 0xffff)

#if (LCD_COLOR_DEPTH == 16)
typedef uint16_t lcd_color_t;
#define LCD_COLOR_RGB(r, g, b) LCD_COLOR_RGB565(r, g, b)
#elif (LCD_COLOR_DEPTH == 32)
typedef uint32_t lcd_color_t;
#define LCD_COLOR_RGB(r, g, b) LCD_COLOR_RGB888(r, g, b)
#endif

#define ABS(x) ((x) > 0 ? (x) : -(x))

/* MCU LCD Common interface */
#if (LCD_INTERFACE_TYPE == LCD_INTERFACE_DBI) || (LCD_INTERFACE_TYPE == LCD_INTERFACE_SPI)

extern struct device *lcd_dev_ifs;
extern struct device *lcd_dev_ifs_dma;
extern uint16_t lcd_max_x, lcd_max_y;

int lcd_init(void);
int lcd_async_callback_register(void (*callback)(void));
int lcd_set_dir(uint8_t dir, uint8_t mir_flag);
int lcd_draw_point(uint16_t x, uint16_t y, lcd_color_t color);
int lcd_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_clear(lcd_color_t color);
int lcd_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t *picture);
int lcd_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t *picture);
int lcd_draw_is_busy(void);
int lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_draw_circle(uint16_t x, uint16_t y, uint16_t r, lcd_color_t color);
#if FONT_ASCII_16X8
int lcd_draw_str_ascii16(uint16_t x, uint16_t y, lcd_color_t color, lcd_color_t bk_color, uint8_t *str, uint8_t num);
#endif

/* RGB LCD Common interface */
#elif (LCD_INTERFACE_TYPE == LCD_INTERFACE_DPI) || (LCD_INTERFACE_TYPE == LCD_INTERFACE_DSI_VIDIO)

/* frame int callback and frame swap int callback */
#define FRAME_INT_TYPE_CYCLE 0
#define FRAME_INT_TYPE_SWAP  1

int lcd_init(lcd_color_t *screen_buffer);
int lcd_screen_switch(lcd_color_t *screen_buffer);
lcd_color_t *lcd_get_screen_using(void);
int lcd_frame_callback_register(uint32_t callback_type, void (*callback)(void));

int lcd_clear(lcd_color_t *screen_buffer, lcd_color_t color);
int lcd_draw_point(lcd_color_t *screen_buffer, uint16_t x, uint16_t y, lcd_color_t color);
int lcd_draw_area(lcd_color_t *screen_buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_draw_picture(lcd_color_t *screen_buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t *picture);
int lcd_draw_line(lcd_color_t *screen_buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_draw_rectangle(lcd_color_t *screen_buffer, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd_color_t color);
int lcd_draw_circle(lcd_color_t *screen_buffer, uint16_t x, uint16_t y, uint16_t r, lcd_color_t color);
#if FONT_ASCII_16X8
int lcd_draw_str_ascii16(lcd_color_t *screen_buffer, uint16_t x, uint16_t y, lcd_color_t color, lcd_color_t bk_color, uint8_t *str, uint8_t num);
#endif

#endif

#endif