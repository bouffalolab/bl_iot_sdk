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

#include "../lcd.h"

#if defined(LCD_DBI_ILI9488) && (defined(BL808) || defined(BL616))

#if defined(BL808) && !defined(CPU_D0)
#warning "bl808-m0 does not support dma2 interrupts, unable to use flush completion interrupt call"
#endif

#if defined(BL808)
#include "bl808_glb.h"
#include "bl808_dbi.h"
#elif defined(BL616)
#include "bl616_glb.h"
#include "bl616_dbi.h"
#include "bl616_dbi_qspi.h"
#endif

#include "ili9488_dbi.h"
#include "hal_dma.h"

#if defined(BL808)
#define DBI_DMAx_CHx DMA2_CH0_INDEX
#elif defined(BL616)
#define DBI_DMAx_CHx DMA0_CH0_INDEX
#endif

/* asynchronous flush interrupt callback */
typedef void (*ili9488_dbi_callback)(void);
static volatile ili9488_dbi_callback ili9488_dbi_async_callback = NULL;
static volatile bool ili9488_dbi_sync_flush_flag = 0;

/* DMA handle */
static struct device *dma_dbi_tx;

/* DBI cfg */
static DBI_CFG_Type dbi_cfg;

/* high speed  CLK cfg */
static DBI_Period_CFG_Type period_hs;
/* low speed  CLK cfg */
static DBI_Period_CFG_Type period_ls;

const ili9488_dbi_init_cmd_t ili9488_dbi_init_cmds[] = {
    { 0x01, NULL, 0 },  /* software reset */
    { 0xFF, NULL, 10 }, /* delay 10ms */

    { 0x11, NULL, 0 },   /* Sleep Out */
    { 0xFF, NULL, 120 }, /* delay 120ms */

    { 0xE0, "\x00\x07\x0F\x0D\x1B\x0A\x3C\x78\x4A\x07\x0E\x09\x1B\x1E\x0F", 15 }, /* PGAMCTRL (Positive Gamma Control) */
    { 0xE1, "\x00\x22\x24\x26\x12\x07\x36\x47\x47\x06\x0A\x07\x30\x37\x0F", 15 }, /* NGAMCTRL (Negative Gamma Control) */

    { 0xC0, "\x10\x10", 2 }, /* Power Control 1 */
    { 0xC1, "\x41", 1 },     /* Power Control 2 */

    { 0xC5, "\x00\x2C\x80", 3 }, /* VCOM Control */
    { 0x36, "\x08", 1 },         /* Memory Access Control */

#if (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB565)
    { 0x3A, "\x55", 1 }, /* Interface Pixel Format RGB565 */
#elif (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB666)
    { 0x3A, "\x66", 1 }, /* Interface Pixel Format RGB666 */
#endif

    { 0xB0, "\x00", 1 },     /* Interface Mode Control */
    { 0xB1, "\xB0", 1 },     /* Frame rate 70Hz */
    { 0xB4, "\x02", 1 },     /* Display Inversion Control */
    { 0xB6, "\x02\x22", 2 }, /* Display Function Control */
    { 0xE9, "\x00", 1 },     /* Set Image Function */

    { 0xF7, "\xA9\x51\x2C\x82", 4 }, /* Adjust Control 3 */

    { 0x29, NULL, 0 }, /* Display On */
    { 0xFF, NULL, 10 },
};

/**
 * @brief ili9488_dbi_dma_flush_callback
 *
 * @return
 */
void ili9488_dbi_dma_flush_callback(struct device *dev, void *args, uint32_t size, uint32_t event)
{
    if (ili9488_dbi_sync_flush_flag == true) {
        ili9488_dbi_sync_flush_flag = false;
        return;
    }

    while (lcd_draw_is_busy()) {
    };

    if (ili9488_dbi_async_callback != NULL) {
        ili9488_dbi_async_callback();
    }
}

/**
 * @brief ili9488_dbi_async_callback_register
 *
 * @return
 */
void ili9488_dbi_async_callback_register(void (*callback)(void))
{
    ili9488_dbi_async_callback = callback;
}

/**
 * @brief ili9488_dbi_spi_init
 *
 * @return int  0:succes  1:error
 */
static int ili9488_dbi_peripheral_init(void)
{
#if (ILI9488_DBI_INTERFACE == ILI9488_DBI_TYPE_C_3_WIRE)
    period_ls.startLen = 2;
    period_ls.dataPhase0Len = 2;
    period_ls.dataPhase1Len = 2;
    period_ls.intervalLen = 2;

    period_hs.startLen = 1;
    period_hs.dataPhase0Len = 1;
    period_hs.dataPhase1Len = 1;
    period_hs.intervalLen = 1;

    dbi_cfg.mode = DBI_TYPE_C_3_WIRE;
    dbi_cfg.continueEn = ENABLE; /* Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    dbi_cfg.dummyEn = DISABLE;   /* Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    dbi_cfg.dummyCnt = 0;        /* Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    dbi_cfg.clkPhase = 0;        /* DBI clock phase */
    dbi_cfg.clkPolarity = 0;     /* DBI clock polarity */
    dbi_cfg.period = period_ls;  /* */
#elif (ILI9488_DBI_INTERFACE == ILI9488_DBI_TYPE_C_4_WIRE)
    period_ls.startLen = 2;
    period_ls.dataPhase0Len = 2;
    period_ls.dataPhase1Len = 2;
    period_ls.intervalLen = 2;

    period_hs.startLen = 1;
    period_hs.dataPhase0Len = 1;
    period_hs.dataPhase1Len = 1;
    period_hs.intervalLen = 1;

    dbi_cfg.mode = DBI_TYPE_C_4_WIRE;
    dbi_cfg.continueEn = ENABLE;            /* Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    dbi_cfg.dummyEn = DISABLE;              /* Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    dbi_cfg.dummyCnt = 0;                   /* Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    dbi_cfg.clkPhase = 0;                   /* DBI clock phase */
    dbi_cfg.clkPolarity = 0;                /* DBI clock polarity */
    dbi_cfg.period = period_ls;             /* */
#elif (ILI9488_DBI_INTERFACE == ILI9488_DBI_TYPE_B)
    period_ls.startLen = 4;
    period_ls.dataPhase0Len = 4;
    period_ls.dataPhase1Len = 4;
    period_ls.intervalLen = 4;

    period_hs.startLen = 2;
    period_hs.dataPhase0Len = 2;
    period_hs.dataPhase1Len = 2;
    period_hs.intervalLen = 2;

    dbi_cfg.mode = DBI_TYPE_B;
    dbi_cfg.continueEn = ENABLE; /* Enable:CS will stay asserted between each consecutive pixel, disable:CS will de-assert between each pixel */
    dbi_cfg.dummyEn = DISABLE;   /* Enable:dummy cycle will be inserted between command phase adn data phase, disable:no dummy cycle */
    dbi_cfg.dummyCnt = 0;        /* Dummy cycle count,effective only in type C(fixed to 1 in type B) */
    dbi_cfg.clkPhase = 0;        /* DBI clock phase */
    dbi_cfg.clkPolarity = 0;     /* DBI clock polarity */
    dbi_cfg.period = period_ls;  /* */
#endif

#if defined(BL616)
    dbi_cfg.CSStretchMode = DBI_CS_STRETCHMODE_DISABLE;
#endif

#if (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB565)
    dbi_cfg.pixelFormat = DBI_PIXEL_RGB565;   /* DBI pixel format */
    dbi_cfg.fifoFormat = DBI_FIFO_565_RGBRGB; /* DBI fifo format */
#elif (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB666)
    dbi_cfg.pixelFormat = DBI_PIXEL_RGB666; /* DBI pixel format */
    dbi_cfg.fifoFormat = DBI_FIFO_888_NRGB; /* DBI fifo format */
#endif

    // #if defined(BL808)
    //     HBN_AON_PAD_CFG_Type aonPadCfg = {
    //         DISABLE,
    //         DISABLE,
    //         DISABLE,
    //         HBN_GPIO_PAD_PULL_NONE
    //     };
    //     HBN_Aon_Pad_Cfg(DISABLE, HBN_AON_PAD_GPIO40, &aonPadCfg);
    // #endif

    DBI_Init(&dbi_cfg);
    DBI_SetTxFifoThreshold(3);

    /* DMA config */
    dma_register(DBI_DMAx_CHx, "lcd_dev_ifs_dma");
    dma_dbi_tx = device_find("lcd_dev_ifs_dma");

    if (dma_dbi_tx != NULL) {
        DMA_DEV(dma_dbi_tx)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_dbi_tx)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_dbi_tx)->src_req = DMA_REQUEST_NONE;
        DMA_DEV(dma_dbi_tx)->dst_req = DMA_REQUEST_DBI_TX;
        DMA_DEV(dma_dbi_tx)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_dbi_tx)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
        DMA_DEV(dma_dbi_tx)->src_width = DMA_TRANSFER_WIDTH_32BIT;
        DMA_DEV(dma_dbi_tx)->dst_width = DMA_TRANSFER_WIDTH_32BIT;
        DMA_DEV(dma_dbi_tx)->src_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_dbi_tx)->dst_burst_size = DMA_BURST_INCR1;

        device_open(dma_dbi_tx, DEVICE_OFLAG_DEFAULT);
        device_set_callback(dma_dbi_tx, ili9488_dbi_dma_flush_callback);
        device_control(dma_dbi_tx, DEVICE_CTRL_SET_INT, NULL);
    }

    return 0;
}

/**
 * @brief ili9488_dbi_draw_is_busy, After the call ili9488_dbi_draw_picture_dma must check this,
 *         if ili9488_dbi_draw_is_busy() == 1, Don't allow other draw !!
 *         can run in the DMA interrupt callback function.
 *
 * @return int 0:draw end; 1:Being draw
 */
int ili9488_dbi_draw_is_busy(void)
{
    if (device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CHANNEL_GET_STATUS, NULL)) {
        return 1;
    } else {
        /* Wait transfer end */
        while (DBI_GetBusBusyStatus()) {
        }
        /* disable DBI-DMA request */
        DBI_SetDMA(DISABLE);
        /* clear interrupt and fifo*/
        DBI_IntClear();
        /* low speed mode */
        DBI_SetPeriod(&period_ls);
        return 0;
    }
}

/**
 * @brief ili9488_dbi_init
 *
 * @return int
 */
int ili9488_dbi_init()
{
#if defined(BL616)
    GLB_Set_DBI_CLK(ENABLE, GLB_DBI_CLK_MCU_MUXPLL_160M, 0);
#endif

    ili9488_dbi_peripheral_init();

    for (uint16_t i = 0; i < (sizeof(ili9488_dbi_init_cmds) / sizeof(ili9488_dbi_init_cmd_t)); i++) {
        if (ili9488_dbi_init_cmds[i].cmd == 0xFF) {
            bflb_platform_delay_ms(ili9488_dbi_init_cmds[i].databytes);
        } else {
            // DBI_SendCmdWithNormalData(ili9488_dbi_init_cmds[i].cmd, ili9488_dbi_init_cmds[i].databytes, (uint8_t *)ili9488_dbi_init_cmds[i].data);
            DBI_SetPhaseState(ENABLE, DISABLE);
            DBI_SendCmdWithNormalData(ili9488_dbi_init_cmds[i].cmd, 0, NULL);
            DBI_SetPhaseState(DISABLE, ENABLE);
            for (uint8_t j = 0; j < ili9488_dbi_init_cmds[i].databytes; j++) {
                DBI_SendCmdWithNormalData(0xFF, 1, (uint8_t *)&ili9488_dbi_init_cmds[i].data[j]);
            }
        }
    }
    DBI_SetPhaseState(ENABLE, ENABLE);
    return 0;
}

/**
 * @brief
 *
 * @param dir
 * @param mir_flag
 */
int ili9488_dbi_set_dir(uint8_t dir, uint8_t mir_flag)
{
    uint8_t param;
    switch (dir) {
        case 0:
            if (!mir_flag)
                param = 0x00;
            else
                param = 0x01;
            break;
        case 1:
            if (!mir_flag)
                param = 0x60;
            else
                param = 0x20;
            break;
        case 2:
            if (!mir_flag)
                param = 0xC0;
            else
                param = 0x80;
            break;
        case 3:
            if (!mir_flag)
                param = 0xA0;
            else
                param = 0xE0;

            break;
        default:
            return -1;
            break;
    }
    DBI_SendCmdWithNormalData(0x36, 1, &param);
    return dir;
}

/**
 * @brief ili9488_dbi_set_draw_window
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
void ili9488_dbi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
#if ILI9488_DBI_OFFSET_X
    x1 += ILI9488_DBI_OFFSET_X;
    x2 += ILI9488_DBI_OFFSET_X;
#endif
#if ILI9488_DBI_OFFSET_Y
    y1 += ILI9488_DBI_OFFSET_Y;
    y2 += ILI9488_DBI_OFFSET_Y;
#endif

    uint8_t param[4];

    param[0] = (y1 >> 8) & 0xFF;
    param[1] = y1 & 0xFF;
    param[2] = (y2 >> 8) & 0xFF;
    param[3] = y2 & 0xFF;
    DBI_SetPhaseState(ENABLE, ENABLE);
    DBI_SendCmdWithNormalData(0x2B, 4, param);

    param[0] = (x1 >> 8) & 0xFF;
    param[1] = x1 & 0xFF;
    param[2] = (x2 >> 8) & 0xFF;
    param[3] = x2 & 0xFF;
    DBI_SendCmdWithNormalData(0x2A, 4, param);
}

/**
 * @brief ili9488_dbi_draw_point
 *
 * @param x
 * @param y
 * @param color
 */
void ili9488_dbi_draw_point(uint16_t x, uint16_t y, ili9488_dbi_color_t color)
{
    /* set window */
    ili9488_dbi_set_draw_window(x, y, x, y);
    /* set command */
    DBI_SetCommand(0x2C);
    /* send data of pixel */
    DBI_SetPhaseState(ENABLE, ENABLE);
    DBI_SendCmdWithPixelData(0x2C, 1, (uint32_t *)(&color));
}

/**
 * @brief ili9488_dbi_draw_area
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void ili9488_dbi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t color)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);
    uint32_t color_src;

    ili9488_dbi_set_draw_window(x1, y1, x2, y2);

    /* disable transfer */
    DBI_Disable();

    /* high speed mode */
    DBI_SetPeriod(&period_hs);

    /* clear fifo and interrupt */
    DBI_TxFifoClear();
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(0x2C);

    /* Data type select, and set data count */
    DBI_SetPhaseState(ENABLE, ENABLE);
    DBI_SetDataTypeAndCount(DBI_DATA_PIXEL, PixelCount);

    /* get pixel Data Size */
#if (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB565)
    pixelDataSize = ((PixelCount + 1) >> 1) << 2;
    color_src = color << 16 | color;
#elif (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB666)
    pixelDataSize = PixelCount << 2;
    color_src = color;
#endif

    /* sync mode, temporary shutdown interrupt */
    ili9488_dbi_sync_flush_flag = true;

    /* disable src_addr_inc */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)DISABLE);
    /* DMA config */
    dma_reload(dma_dbi_tx, (uint32_t)(uintptr_t)(&color_src), (uint32_t)DMA_ADDR_DBI_TDR, pixelDataSize);

#if defined(BL808) || defined(BL606P) || defined(BL616)
    csi_dcache_clean_range((void *)(&color_src), sizeof(color_src));
#endif
    /* enable DBI-DMA request */
    DBI_SetDMA(ENABLE);

    /* Enable DMA */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CHANNEL_START, NULL);

    /* Enable DBI transfer */
    DBI_Enable();

    while (ili9488_dbi_draw_is_busy()) {
    }

    /* enable src_addr_inc */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)ENABLE);
}

/**
 * @brief ili9488_dbi_draw_picture_dma, Non-blocking! Using DMA acceleration, Not waiting for the draw end
 *  After the call, No other operations are allowed until (ili9488_dbi_draw_is_busy()==0)
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */

void ili9488_dbi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t *picture)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);

    ili9488_dbi_set_draw_window(x1, y1, x2, y2);

    /* disable transfer */
    DBI_Disable();

    /* high speed mode */
    DBI_SetPeriod(&period_hs);

    /* clear fifo and interrupt */
    DBI_TxFifoClear();
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(0x2C);

    /* Data type select, and set data count */
    DBI_SetPhaseState(ENABLE, ENABLE);
    DBI_SetDataTypeAndCount(DBI_DATA_PIXEL, PixelCount);

    /* DMA config */
#if (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB565)
    pixelDataSize = ((PixelCount + 1) >> 1) << 2;
#elif (ILI9488_DBI_PIXEL_FORMAT == ILI9488_DBI_PIXEL_FORMAT_RGB666)
    pixelDataSize = PixelCount << 2;
#endif
    dma_reload(dma_dbi_tx, (uint32_t)(uintptr_t)picture, (uint32_t)DMA_ADDR_DBI_TDR, pixelDataSize);

#if defined(BL808) || defined(BL606P) || defined(BL616)
    csi_dcache_clean_range((void *)picture, pixelDataSize);
#endif
    /* enable DBI-DMA request */
    DBI_SetDMA(ENABLE);

    /* Enable DMA */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CHANNEL_START, NULL);

    /* Enable DBI transfer */
    DBI_Enable();
}

/**
 * @brief ili9488_dbi_draw_picture,Blocking，Using DMA acceleration,Waiting for the draw end
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void ili9488_dbi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_dbi_color_t *picture)
{
#if 0
    /* set window */
    ili9488_dbi_set_draw_window( x1,  y1,  x2,  y2);
    /* set command */
    DBI_SetCommand(0x2C);
    /* high speed mode */
    DBI_SetPeriod(&period_hs);
    /* send data of pixel */
    DBI_SetPhaseState(ENABLE, ENABLE);
    DBI_SendCmdWithPixelData(0x2C, (x2- x1 + 1) * (y2 - y1 + 1), (uint32_t *)picture);
    /* low speed mode */
    DBI_SetPeriod(&period_ls);
#else
    /* sync mode, temporary shutdown interrupt */
    ili9488_dbi_sync_flush_flag = true;

    ili9488_dbi_draw_picture_nonblocking(x1, y1, x2, y2, picture);
    while (ili9488_dbi_draw_is_busy()) {
    }
#endif
}

#elif defined(LCD_DBI_ILI9488)
#error "Devices that do not support DBI! Replace the driver port (lcd.h)"
#endif
