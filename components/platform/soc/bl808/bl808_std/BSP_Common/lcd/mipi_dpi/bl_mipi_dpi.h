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

#include "../lcd.h"

#ifndef _BL_MIPI_DPI_H_
#define _BL_MIPI_DPI_H_

#define LCD_MIPI_DPI_PIXEL_FORMAT_RGB565  0
#define LCD_MIPI_DPI_PIXEL_FORMAT_NRGB888 1

#define LCD_MIPI_DPI_FRAME_INT_TYPE_CYCLE 0
#define LCD_MIPI_DPI_FRAME_INT_TYPE_SWAP  1

typedef struct {
    uint16_t width;  /* LCD Active Width */
    uint16_t height; /* LCD Active Height */
                     /* Total Width = HSW + HBP + Active_Width + HFP */
    uint16_t hsw;    /* LCD HSW (Hsync Pulse Width) */
    uint16_t hbp;    /* LCD HBP (Hsync Back Porch) */
    uint16_t hfp;    /* LCD HFP (Hsync Front Porch) */
                     /* Total Height = VSW + VBP + Active_Height + VFP */
    uint16_t vsw;    /* LCD VSW (Vsync Pulse Width) */
    uint16_t vbp;    /* LCD VBP (Vsync Back Porch) */
    uint16_t vfp;    /* LCD VFP (Vsync Front Porch) */

    uint16_t frame_rate; /* Maximum refresh frame rate per second, Used to automatically calculate the clock frequency */

    uint16_t pixel_format;

    void *frame_buff; /* The frame buffer */
} lcd_mipi_dpi_init_t;

#if defined(BL616)

typedef struct {
    void *disp_buff;
    void *dma_lli;
    uint16_t lru_value;
} pec_dpi_dma_lli_cache_t;

/* PEC select */
#define PEC_ID_USE PEC0_ID
#define SM_ID_USE  PEC_SM0

/* DMA select */
#define DMA_ID_USE    DMA0_ID
#define DMA_CHAN_USE  DMA_CH3
#define DMA_HAL_INDEX DMA0_CH3_INDEX
#define DMA_MAX_COUNT 4032

/* Maximum number of DPI invalid rows, >= (VHW + VBP + VFP) */
#define DPI_PEC_INVALID_LIN_MAX 300

/* Maximum number of DPI valid pixels, >= (Width * Height) */
#define DPI_PEC_VALID_PIXEL_MAX (800 * 480)

/* cache num of dma_lli, >= 2,
    Performance is best when the value is no less than the number of disp_buffs used */
#define DPI_PEC_DMA_LLI_CACHE_NUM 3

/* PEC pin config */
/* You need to set up the reuse function of these pins yourself */
/* Rules: PIN_DE = PIN_CLK + 1;  PIN_LATCH = PIN_CLK + 2;  PIN_VSYNC = PIN_HSYNC + 1*/
#define PIN_CLK        GLB_GPIO_PIN_32
#define PIN_HSYNC      GLB_GPIO_PIN_18
#define PIN_DATA_START GLB_GPIO_PIN_23

/* DE mode select */
#define DE_MODE 1

/* The mode of data latch.
    0: 16-bit *1-cycle date out;
    1: 8-bit *2-cycle date out, Low 8-bit latch, high 8-bit pass-through, Additional latch devices are required */
#define DATA_LATCH_MODE 1

/* Signal effective level selection */
#define V_SYNC_SINGLE_POL 0
#define H_SYNC_SINGLE_POL 0
#define DE_SINGLE_POL     1

#endif

int lcd_mipi_dpi_init(lcd_mipi_dpi_init_t *dpi_para);
int lcd_mipi_dpi_screen_switch(void *screen_buffer);
void *lcd_mipi_dpi_get_screen_using(void);
int lcd_mipi_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void));

#endif
