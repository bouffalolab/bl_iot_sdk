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

#ifndef _STANDARD_DBI_H_
#define _STANDARD_DBI_H_

#include "bflb_platform.h"
#include "bl_mipi_dpi.h"

/* Select pixel format */
#define STANDARD_DPI_PIXEL_FORMAT LCD_MIPI_DPI_PIXEL_FORMAT_RGB565

/* RGB Default timing parameter Settings */
/* Total Width = HSW + HBP + Active_Width + HFP */
/* Total Height = VSW + VBP + Active_Height + VFP */

/* STANDARD LCD Active Width */
#define STANDARD_DPI_W 800
/* STANDARD LCD Active Height */
#define STANDARD_DPI_H 480

/* STANDARD LCD HSW (Hsync Pulse Width) */
#define STANDARD_DPI_HSW 4
/* STANDARD LCD HBP (Hsync Back Porch) */
#define STANDARD_DPI_HBP 82
/* STANDARD LCD HFP (Hsync Front Porch) */
#define STANDARD_DPI_HFP 14

/* STANDARD LCD VSW (Vsync Pulse Width) */
#define STANDARD_DPI_VSW 5
/* STANDARD LCD VBP (Vsync Back Porch) */
#define STANDARD_DPI_VBP 6
/* STANDARD LCD VFP (Vsync Front Porch) */
#define STANDARD_DPI_VFP 39

/* Maximum refresh frame rate per second, Used to automatically calculate the clock frequency */
#define STANDARD_DPI_FRAME_RATE 70

/* Do not modify the following information */

#if (STANDARD_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_RGB565)
#define STANDARD_DPI_COLOR_DEPTH 16
typedef uint16_t standard_dpi_color_t;
#elif (STANDARD_DPI_PIXEL_FORMAT == LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888)
#define STANDARD_DPI_COLOR_DEPTH 32
typedef uint32_t standard_dpi_color_t;
#endif

int standard_dpi_init(standard_dpi_color_t *screen_buffer);
int standard_dpi_screen_switch(standard_dpi_color_t *screen_buffer);
standard_dpi_color_t *standard_dpi_get_screen_using(void);
int standard_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
