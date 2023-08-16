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

#ifndef _ILI9488_DBI_H_
#define _ILI9488_DBI_H_

#include "bflb_platform.h"

/* Optional MIPI interface type */
#define ILI9488_DBI_TYPE_C_4_WIRE 1
#define ILI9488_DBI_TYPE_C_3_WIRE 2
#define ILI9488_DBI_TYPE_B        3

/* Optional pixel data format type */
#define ILI9488_DBI_PIXEL_FORMAT_RGB666 666 /* Equivalent to RGB888 */
#define ILI9488_DBI_PIXEL_FORMAT_RGB565 565

/* Selecting an interface type*/
#define ILI9488_DBI_INTERFACE ILI9488_DBI_TYPE_B

#if (ILI9488_DBI_INTERFACE == ILI9488_DBI_TYPE_B)
/* Select pixel format */
#define ILI9488_DBI_PIXEL_FORMAT ILI9488_DBI_PIXEL_FORMAT_RGB565
#else
/* Do not modify, ili9488-TypeC mode Only support RGB666 */
#define ILI9488_DBI_PIXEL_FORMAT ILI9488_DBI_PIXEL_FORMAT_RGB666
#endif

/* ILI9488 LCD width */
#define ILI9488_DBI_W 320
/* ILI9488 LCD height */
#define ILI9488_DBI_H 480

/* The offset of the area can be displayed */
#define ILI9488_DBI_OFFSET_X 0
#define ILI9488_DBI_OFFSET_Y 0

#if (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB565)
#define ILI9488_DBI_COLOR_DEPTH 16
typedef uint16_t ili9488_dbi_color_t;
#elif (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB666)
#define ILI9488_DBI_COLOR_DEPTH 32
typedef uint32_t ili9488_dbi_color_t;
#endif

typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} ili9488_dbi_init_cmd_t;

int ili9488_dbi_init();
void ili9488_dbi_async_callback_register(void (*callback)(void));
int ili9488_dbi_set_dir(uint8_t dir, uint8_t mir_flag);
void ili9488_dbi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ili9488_dbi_draw_point(uint16_t x, uint16_t y, ili9488_dbi_color_t color);
void ili9488_dbi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t color);
void ili9488_dbi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t *picture);
void ili9488_dbi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t *picture);
int ili9488_dbi_draw_is_busy(void);

#endif
