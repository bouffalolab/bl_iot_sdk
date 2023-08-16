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

#ifndef _GC9C01_DISP_QSPI_H_
#define _GC9C01_DISP_QSPI_H_

#include "bflb_platform.h"

/* Optional pixel data format type */
#define GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888 888
#define GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565 565

/* Select qspi Wire width for cmd */
/* Wire width for cmd, gc9c01 must 1 */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_CMD 1
/* Wire width for address, 1 or 4 */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR 4
/* Wire width for data, 1 or 4, and it's not less than address */
#define GC9C01_DISP_QSPI_WIRE_WIDTH_DATA 4

/* Select pixel format */
#define GC9C01_DISP_QSPI_PIXEL_FORMAT GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565

/* GC9C01 LCD width */
#define GC9C01_DISP_QSPI_W 360
/* GC9C01 LCD height */
#define GC9C01_DISP_QSPI_H 360

/* The offset of the area can be displayed */
#define GC9C01_DISP_QSPI_OFFSET_X 0
#define GC9C01_DISP_QSPI_OFFSET_Y 0

#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
#define GC9C01_DISP_QSPI_COLOR_DEPTH 16
typedef uint16_t gc9c01_disp_qspi_color_t;
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
#define GC9C01_DISP_QSPI_COLOR_DEPTH 32
typedef uint32_t gc9c01_disp_qspi_color_t;
#endif

typedef struct {
    uint8_t cmd; /* 0xFF : delay(databytes)ms */
    const char *data;
    uint8_t databytes; /* Num of data in data; or delay time */
} gc9c01_disp_qspi_init_cmd_t;

int gc9c01_disp_qspi_init();
void gc9c01_disp_qspi_async_callback_register(void (*callback)(void));
int gc9c01_disp_qspi_set_dir(uint8_t dir, uint8_t mir_flag);
void gc9c01_disp_qspi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void gc9c01_disp_qspi_draw_point(uint16_t x, uint16_t y, gc9c01_disp_qspi_color_t color);
void gc9c01_disp_qspi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t color);
void gc9c01_disp_qspi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture);
void gc9c01_disp_qspi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture);
int gc9c01_disp_qspi_draw_is_busy(void);

#endif