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

#if defined(LCD_DPI_ST7701S)

#include "bflb_platform.h"
#include "st7701s_dpi.h"
#include "bl_mipi_dpi.h"

#if ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_DBI_TYPE_C

#error "Not currently supported DBI typeC"

#if defined(BL808)
#include "bl808_dbi.h"
#elif defined(BL616)
#include "bl616_dbi.h"
#endif

#elif ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_SPI

#include "hal_spi.h"
#include "hal_gpio.h"

#define ST7701S_SPI_INDEX SPI0_INDEX

#endif

/* mipi dpi (RGB) paramant */
static lcd_mipi_dpi_init_t dpi_para = {
    .width = ST7701S_DPI_W,  /* LCD Active Width */
    .height = ST7701S_DPI_H, /* LCD Active Height */
                             /* Total Width = HSW + HBP + Active_Width + HFP */
    .hsw = 4,                /* LCD HSW (Hsync Pulse Width) */
    .hbp = 6,                /* LCD HBP (Hsync Back Porch) */
    .hfp = 10,               /* LCD HFP (Hsync Front Porch) */
                             /* Total Height = VSW + VBP + Active_Height + VFP */
    .vsw = 4,                /* LCD VSW (Vsync Pulse Width) */
    .vbp = 10,               /* LCD VBP (Vsync Back Porch) */
    .vfp = 6,                /* LCD VFP (Vsync Front Porch) */

    .frame_rate = 50, /* Maximum refresh frame rate per second, Used to automatically calculate the clock frequency */

    .pixel_format = ST7701S_DPI_PIXEL_FORMAT,

    .frame_buff = NULL,
};

#if ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_DBI_TYPE_C

/* dbi config */
static DBI_CFG_Type dbiCfg = {
    .mode = DBI_TYPE_C_4_WIRE,               /* DBI type B or C select */
    .pixelFormat = DBI_PIXEL_RGB888,         /* DBI pixel format */
    .fifoFormat = DBI_FIFO_888_NBGR,         /* DBI fifo format */
    .continueEn = ENABLE,                    /* Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    .dummyEn = DISABLE,                      /* Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    .dummyCnt = 0,                           /* Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    .clkPhase = DBI_SCL_CLK_PHASE_0,         /* DBI clock phase */
    .clkPolarity = DBI_SCL_CLK_POLARITY_LOW, /* DBI clock polarity */
    .period.startLen = 9,
    .period.dataPhase0Len = 9,
    .period.dataPhase1Len = 9,
    .period.intervalLen = 9
};

#elif ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_SPI

static struct device *st7701s_spi;

static int st7701s_spi_write_cmd_data(const st7701s_dpi_init_cmd_t *cmd_date)
{
    int res = 0;
    uint8_t data[6] = { 0x20, cmd_date->cmd, 0x00, 0x00, 0x40, 0x00 };

    if (cmd_date->databytes) {
        for (uint16_t i = 0; i < cmd_date->databytes; i++) {
            data[3] = i;
            data[5] = cmd_date->data[i];

            /* send cmd and parameter */
            ST7701S_SPI_CS_LOW;
            res = device_write(st7701s_spi, 0, data, 6);
            ST7701S_SPI_CS_HIGH;
        }
    } else {
        /* No data, just send commands */
        ST7701S_SPI_CS_LOW;
        res = device_write(st7701s_spi, 0, data, 4);
        ST7701S_SPI_CS_HIGH;
    }

    return res;
}

#endif

static const st7701s_dpi_init_cmd_t st7701s_dpi_mode_init_cmds[] = {

    { 0xFF, "\x77\x01\x00\x00\x10", 5 },
    { 0xC0, "\x63\x00", 2 },
    { 0xC1, "\x0A\x02", 2 },
    { 0xC2, "\x07\x08", 2 },
    { 0xCC, "\x10", 1 },

    { 0xB0, "\x00\x11\x19\x0C\x10\x06\x07\x0A\x09\x22\x04\x10\x0E\x28\x30\x1C", 16 },
    { 0xB0, "\x00\x12\x19\x0D\x10\x04\x06\x07\x08\x23\x04\x12\x11\x28\x30\x1C", 16 },

    { 0xFF, "\x77\x01\x00\x00\x11", 5 },

#if 0
    { 0xC3, "\x00\x06\x0A", 3 }, /* 0x00: DE mode */
#else
    { 0xC3, "\x80\x06\x0A", 3 }, /* 0x80: HV mode, HBP, VBP */
#endif

    { 0xB0, "\x4D", 1 },
    { 0xB1, "\x3C", 1 },
    { 0xB2, "\x07", 1 },
    { 0xB3, "\x80", 1 },
    { 0xB5, "\x47", 1 },
    { 0xB7, "\x85", 1 },
    { 0xB8, "\x21", 1 },
    { 0xB9, "\x10", 1 },
    { 0xC1, "\x78", 1 },
    { 0xC2, "\x78", 1 },
    { 0xD0, "\x88", 1 },

    { 0xE0, "\x00\x00\x02", 3 },
    { 0xE1, "\x04\x00\x00\x00\x05\x00\x00\x00\x00\x20\x20", 11 },
    { 0xE2, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 13 },
    { 0xE3, "\x00\x00\x33\x00", 4 },
    { 0xE4, "\x22\x00", 2 },
    { 0xE5, "\x04\x34\xAA\xAA\x06\x34\xAA\xAA\x00\x00\x00\x00\x00\x00\x00\x00", 16 },
    { 0xE6, "\x00\x00\x33\x00", 4 },
    { 0xE7, "\x22\x00", 2 },
    { 0xE8, "\x05\x34\xAA\xAA\x07\x34\xAA\xAA\x00\x00\x00\x00\x00\x00\x00\x00", 16 },
    { 0xEB, "\x02\x00\x40\x40\x00\x00\x00", 7 },
    { 0xEC, "\x00\x00", 2 },
    { 0xED, "\xFA\x45\x0B\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xB0\x54\xAF", 16 },

    { 0xFF, "\x77\x01\x00\x00\x00", 5 },
    { 0x36, "\x00", 0 },

    { 0x11, NULL, 0 },
    { 0x29, NULL, 0 },
};

int st7701s_dpi_init(st7701s_dpi_color_t *screen_buffer)
{
/* Ili9481 needs to be initialized using the DBI(typeC) or SPI interface */
#if ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_DBI_TYPE_C
    DBI_Init(&dbiCfg);

    for (uint16_t i = 0; i < (sizeof(st7701s_dpi_mode_init_cmds) / sizeof(st7701s_dpi_init_cmd_t)); i++) {
        if (st7701s_dpi_mode_init_cmds[i].cmd == 0xFF) {
            bflb_platform_delay_ms(st7701s_dpi_mode_init_cmds[i].databytes);
        } else {
            DBI_SetPhaseState(ENABLE, DISABLE);
            DBI_SendCmdWithNormalData(st7701s_dpi_mode_init_cmds[i].cmd, 0, NULL);
            DBI_SetPhaseState(DISABLE, ENABLE);
            for (uint8_t j = 0; j < st7701s_dpi_mode_init_cmds[i].databytes; j++) {
                DBI_SendCmdWithNormalData(0xFF, 1, (uint8_t *)&st7701s_dpi_mode_init_cmds[i].data[j]);
            }
        }
    }
    DBI_SetPhaseState(DISABLE, DISABLE);

#elif ST7701S_DPI_INIT_INTERFACE == ST7701S_DPI_INIT_INTERFACE_SPI

    gpio_set_mode(ST7701S_SPI_CS_PIN, GPIO_OUTPUT_MODE);
    ST7701S_SPI_CS_HIGH;

    st7701s_spi = device_find("lcd_dev_ifs");
    if (st7701s_spi) {
        device_close(st7701s_spi);
    } else {
        spi_register(ST7701S_SPI_INDEX, "lcd_dev_ifs");
        st7701s_spi = device_find("lcd_dev_ifs");
    }

    if (st7701s_spi) {
        SPI_DEV(st7701s_spi)->mode = SPI_MASTER_MODE;
        SPI_DEV(st7701s_spi)->clk = (8 * 1000 * 1000);
        SPI_DEV(st7701s_spi)->direction = SPI_MSB_BYTE0_DIRECTION_FIRST;
        SPI_DEV(st7701s_spi)->datasize = SPI_DATASIZE_8BIT;
        SPI_DEV(st7701s_spi)->clk_polaraity = SPI_POLARITY_LOW;
        SPI_DEV(st7701s_spi)->clk_phase = SPI_PHASE_1EDGE;
        SPI_DEV(st7701s_spi)->fifo_threshold = 0;

        device_open(st7701s_spi, DEVICE_OFLAG_STREAM_TX);
    }

    for (uint16_t i = 0; i < (sizeof(st7701s_dpi_mode_init_cmds) / sizeof(st7701s_dpi_init_cmd_t)); i++) {
        if (st7701s_dpi_mode_init_cmds[i].cmd == 0xFF && st7701s_dpi_mode_init_cmds[i].data == NULL) {
            /* delay */
            bflb_platform_delay_ms(st7701s_dpi_mode_init_cmds[i].databytes);
        } else {
            /* send cmd with parameter */
            st7701s_spi_write_cmd_data(&st7701s_dpi_mode_init_cmds[i]);
        }
    }

#endif

    /* mipi dpi init */
    dpi_para.frame_buff = (void *)screen_buffer;
    return lcd_mipi_dpi_init(&dpi_para);
}

int st7701s_dpi_screen_switch(st7701s_dpi_color_t *screen_buffer)
{
    return lcd_mipi_dpi_screen_switch((void *)screen_buffer);
}

st7701s_dpi_color_t *st7701s_dpi_get_screen_using(void)
{
    return (st7701s_dpi_color_t *)lcd_mipi_dpi_get_screen_using();
}

int st7701s_dpi_frame_callback_register(uint32_t callback_type, void (*callback)(void))
{
    if (callback_type == FRAME_INT_TYPE_CYCLE) {
        lcd_mipi_dpi_frame_callback_register(LCD_MIPI_DPI_FRAME_INT_TYPE_CYCLE, callback);
    } else if (callback_type == FRAME_INT_TYPE_SWAP) {
        lcd_mipi_dpi_frame_callback_register(LCD_MIPI_DPI_FRAME_INT_TYPE_SWAP, callback);
    }

    return 0;
}

#endif