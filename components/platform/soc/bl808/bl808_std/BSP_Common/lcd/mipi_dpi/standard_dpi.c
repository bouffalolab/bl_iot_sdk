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

#if defined(LCD_DPI_STANDARD)

#include "bflb_platform.h"
#include "standard_dpi.h"
#include "bl_mipi_dpi.h"

/* mipi dpi (RGB) paramant */
static lcd_mipi_dpi_init_t dpi_para = {
    .width = STANDARD_DPI_W,  /* LCD Active Width */
    .height = STANDARD_DPI_H, /* LCD Active Height */
                              /* Total Width = HSW + HBP + Active_Width + HFP */
    .hsw = STANDARD_DPI_HSW,  /* LCD HSW (Hsync Pulse Width) */
    .hbp = STANDARD_DPI_HBP,  /* LCD HBP (Hsync Back Porch) */
    .hfp = STANDARD_DPI_HFP,  /* LCD HFP (Hsync Front Porch) */
                              /* Total Height = VSW + VBP + Active_Height + VFP */
    .vsw = STANDARD_DPI_VSW,  /* LCD VSW (Vsync Pulse Width) */
    .vbp = STANDARD_DPI_VBP,  /* LCD VBP (Vsync Back Porch) */
    .vfp = STANDARD_DPI_VFP,  /* LCD VFP (Vsync Front Porch) */

    .frame_rate = 60, /* Maximum refresh frame rate per second, Used to automatically calculate the clock frequency */

    .pixel_format = STANDARD_DPI_PIXEL_FORMAT,

    .frame_buff = NULL,
};

int standard_dpi_init(standard_dpi_color_t *screen_buffer)
{
    if (screen_buffer == NULL) {
        return -1;
    }

    /* mipi dpi init */
    dpi_para.frame_buff = (void *)screen_buffer;
    return lcd_mipi_dpi_init(&dpi_para);
}

int standard_dpi_screen_switch(standard_dpi_color_t *screen_buffer)
{
    return lcd_mipi_dpi_screen_switch((void *)screen_buffer);
}

standard_dpi_color_t *standard_dpi_get_screen_using(void)
{
    return (standard_dpi_color_t *)lcd_mipi_dpi_get_screen_using();
}

int standard_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void))
{
    if (callback_type == FRAME_INT_TYPE_CYCLE) {
        lcd_mipi_dpi_frame_callback_register(LCD_MIPI_DPI_FRAME_INT_TYPE_CYCLE, callback);
    } else if (callback_type == FRAME_INT_TYPE_SWAP) {
        lcd_mipi_dpi_frame_callback_register(LCD_MIPI_DPI_FRAME_INT_TYPE_SWAP, callback);
    }

    return 0;
}

#endif
