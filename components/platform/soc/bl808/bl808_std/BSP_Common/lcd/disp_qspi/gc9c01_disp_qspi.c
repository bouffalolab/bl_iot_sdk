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

#if defined(LCD_DISP_QSPI_GC9C01) && defined(BL616)

#if defined(BL616)
#include "bl616_dbi.h"
#include "bl616_dbi_qspi.h"
#include "bl616_glb.h"
#endif

#include "gc9c01_disp_qspi.h"
#include "hal_dma.h"

#if defined(BL616)
#define DBI_DMAx_CHx DMA0_CH0_INDEX
#endif

/* gc9c01 cmd */
#if (GC9C01_DISP_QSPI_WIRE_WIDTH_CMD == 1 && GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR == 1 && GC9C01_DISP_QSPI_WIRE_WIDTH_DATA == 1)
#define GC9C01_DISP_QSPI_CMD (0x02)
#elif (GC9C01_DISP_QSPI_WIRE_WIDTH_CMD == 1 && GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR == 1 && GC9C01_DISP_QSPI_WIRE_WIDTH_DATA == 4)
#define GC9C01_DISP_QSPI_CMD (0x32)
#elif (GC9C01_DISP_QSPI_WIRE_WIDTH_CMD == 1 && GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR == 4 && GC9C01_DISP_QSPI_WIRE_WIDTH_DATA == 4)
#define GC9C01_DISP_QSPI_CMD (0x12)
#elif
#error " GC9C01 QSPI interface do not support this mode"
#endif

/* asynchronous flush interrupt callback */
typedef void (*gc9c01_disp_qspi_callback)(void);
static volatile gc9c01_disp_qspi_callback gc9c01_disp_qspi_async_callback = NULL;
static volatile bool gc9c01_disp_qspi_sync_flush_flag = 0;

/* DMA handle */
static struct device *dma_dbi_tx;

/* DBI_QSPI cfg */
static DBI_QSPI_CFG_Type dbi_qspi_cfg;
/* DBI_QSPI Wire cfg */
static DBI_QSPI_WIRE_CFG_Type qspiWire;

/* high speed  CLK cfg */
static DBI_Period_CFG_Type period_hs = {
    .startLen = 2,
    .dataPhase0Len = 2,
    .dataPhase1Len = 1,
    .intervalLen = 2,
};
/* low speed  CLK cfg */
static DBI_Period_CFG_Type period_ls = {
    .startLen = 4,
    .dataPhase0Len = 4,
    .dataPhase1Len = 4,
    .intervalLen = 4,
};

const gc9c01_disp_qspi_init_cmd_t gc9c01_disp_qspi_init_cmds[] = {

    { 0xFE, NULL, 0 },
    { 0xEF, NULL, 0 },
    { 0x01, NULL, 0 },
    { 0xFF, NULL, 120 },
    { 0x80, "\x11", 1 },
    { 0x81, "\x70", 1 },
    { 0x82, "\x09", 1 },
    { 0x83, "\x03", 1 },
    { 0x84, "\x20", 1 },
    { 0x89, "\x10", 1 },
    { 0x8A, "\x4F", 1 },
    { 0x8B, "\x08", 1 },
    { 0x8C, "\x59", 1 },
    { 0x8D, "\x51", 1 },
    { 0x36, "\x00", 1 },
#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
    { 0x3A, "\x05", 1 },
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
    { 0x3A, "\x06", 1 },
// { 0xB1, "\x08", 1 },
#endif
    { 0xEC, "\x07", 1 },
    { 0x74, "\x01\x80\x00\x00\x00\x00", 6 },
    { 0x98, "\x3E", 1 },
    { 0x99, "\x3E", 1 },
    { 0xC3, "\x3A", 1 },
    { 0xC4, "\x16", 1 },
    { 0xA1, "\x01\x04", 2 },
    { 0xA2, "\x01\x04", 2 },
    { 0xCB, "\x02", 1 },
    { 0x7C, "\xB6\x26", 2 },
    { 0xAC, "\x24", 1 },
    { 0xF6, "\x80", 1 },
    { 0xB5, "\x09\x09", 2 },
    { 0x60, "\x38\x0B\x5B\x56", 4 },
    { 0x63, "\x3A\xE0\x5B\x56", 4 },
    { 0x64, "\x38\x0D\x72\xDD\x5B\x56", 6 },
    { 0x66, "\x38\x11\x72\xE1\x5B\x56", 6 },
    { 0x68, "\x3B\x08\x08\x00\x08\x29\x5B", 7 },
    { 0x6E, "\x00\x00\x00\x07\x01\x13\x11\x0B\x09\x16\x15\x1D\x1E\x00\x00\x00\x00\x00\x00\x1E\x1D\x15\x16\x0A\x0C\x12\x14\x02\x08\x00\x00\x00", 32 },
    { 0xBE, "\x11", 1 },
    { 0x6C, "\xCC\x0C\xCC\x84\xCC\x04\x50", 7 },
    { 0x7D, "\x72", 1 },
    { 0x7E, "\x38", 1 },
    { 0x70, "\x02\x03\x09\x05\x0C\x06\x09\x05\x0C\x06", 10 },
    { 0x90, "\x06\x06\x05\x06", 4 },
    { 0x93, "\x45\xFF\x00", 3 },
    { 0xF0, "\x46\x0B\x0F\x0A\x10\x3F", 6 },
    { 0xF1, "\x52\x9A\x4F\x36\x37\xFF", 6 },
    { 0xF2, "\x46\x0B\x0F\x0A\x10\x3F", 6 },
    { 0xF3, "\x52\x9A\x4F\x36\x37\xFF", 6 },
    { 0xFB, "\x00\x00", 2 },
    { 0xB4, "\x01", 1 },
    { 0x35, "\x00", 1 },

    { 0x11, NULL, 0 },
    { 0xFF, NULL, 120 },
    { 0x29, NULL, 0 },
};

/**
 * @brief gc9c01_disp_qspi_dma_flush_callback
 *
 * @return
 */
void gc9c01_disp_qspi_dma_flush_callback(struct device *dev, void *args, uint32_t size, uint32_t event)
{
    if (gc9c01_disp_qspi_sync_flush_flag == true) {
        gc9c01_disp_qspi_sync_flush_flag = false;
        return;
    }

    while (lcd_draw_is_busy()) {
    };

    if (gc9c01_disp_qspi_async_callback != NULL) {
        gc9c01_disp_qspi_async_callback();
    }
}

/**
 * @brief gc9c01_disp_qspi_async_callback_register
 *
 * @return
 */
void gc9c01_disp_qspi_async_callback_register(void (*callback)(void))
{
    gc9c01_disp_qspi_async_callback = callback;
}

/**
 * @brief gc9c01_spi_init
 *
 * @return int  0:succes  1:error
 */
static int gc9c01_disp_qspi_peripheral_init(void)
{
#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
    dbi_qspi_cfg.pixelFormat = DBI_PIXEL_RGB565;
    dbi_qspi_cfg.fifoFormat = DBI_FIFO_565_RGBRGB;
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
    dbi_qspi_cfg.pixelFormat = DBI_PIXEL_RGB888;
    dbi_qspi_cfg.fifoFormat = DBI_FIFO_888_NRGB;
#endif
    dbi_qspi_cfg.clkPhase = DBI_SCL_CLK_PHASE_0;
    dbi_qspi_cfg.clkPolarity = DBI_SCL_CLK_PHASE_0;
    dbi_qspi_cfg.CSStretchMode = DBI_CS_STRETCHMODE_ENABLE;
    dbi_qspi_cfg.period = period_ls;
    dbi_qspi_cfg.startCommand = GC9C01_DISP_QSPI_CMD;
    dbi_qspi_cfg.qspiAddressSize = 3;
    DBI_QSPI_Init(&dbi_qspi_cfg);
    DBI_SetFIFOMode(DBI_FIFO_MODE_RGB);
    DBI_SetTxFifoThreshold(3);

#if (GC9C01_DISP_QSPI_WIRE_WIDTH_DATA == 1)
    qspiWire.dataWire = DBI_QSPI_WIRE_1;
#elif (GC9C01_DISP_QSPI_WIRE_WIDTH_DATA == 4)
    qspiWire.dataWire = DBI_QSPI_WIRE_4;
#endif

#if (GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR == 1)
    qspiWire.addressWire = DBI_QSPI_WIRE_1;
#elif (GC9C01_DISP_QSPI_WIRE_WIDTH_ADDR == 4)
    qspiWire.addressWire = DBI_QSPI_WIRE_4;
#endif

#if (GC9C01_DISP_QSPI_WIRE_WIDTH_CMD == 1)
    qspiWire.commandWire = DBI_QSPI_WIRE_1;
#elif (GC9C01_DISP_QSPI_WIRE_WIDTH_CMD == 4)
    qspiWire.commandWire = DBI_QSPI_WIRE_4;
#endif

    DBI_QSPI_SetWire(&qspiWire);

    /* DMA config */
    dma_register(DMA0_CH0_INDEX, "lcd_dev_ifs_dma");
    dma_dbi_tx = device_find("lcd_dev_ifs_dma");

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
    device_set_callback(dma_dbi_tx, gc9c01_disp_qspi_dma_flush_callback);
    device_control(dma_dbi_tx, DEVICE_CTRL_SET_INT, NULL);

    return 0;
}

/**
 * @brief gc9c01_draw_is_busy, After the call gc9c01_draw_picture_dma must check this,
 *         if gc9c01_draw_is_busy() == 1, Don't allow other draw !!
 *         can run in the DMA interrupt callback function.
 *
 * @return int 0:draw end; 1:Being draw
 */
int gc9c01_disp_qspi_draw_is_busy(void)
{
    if (device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CHANNEL_GET_STATUS, NULL)) {
        return 1;
    } else {
        /* Wait transfer end */
        while (DBI_GetBusBusyStatus()) {
        }
        /* disable DBI-DMA request */
        DBI_SetDMA(DISABLE);
        /* clear interrupt */
        DBI_IntClear();
        /* low speed mode */
        DBI_SetPeriod(&period_ls);
        return 0;
    }
}

/**
 * @brief gc9c01_init
 *
 * @return int
 */
int gc9c01_disp_qspi_init()
{
#if defined(BL616)
    GLB_Set_DBI_CLK(ENABLE, GLB_DBI_CLK_MCU_MUXPLL_160M, 0);
#endif

    gc9c01_disp_qspi_peripheral_init();

    for (uint16_t i = 0; i < (sizeof(gc9c01_disp_qspi_init_cmds) / sizeof(gc9c01_disp_qspi_init_cmd_t)); i++) {
        uint32_t qspi_address;
        if (gc9c01_disp_qspi_init_cmds[i].cmd == 0xFF) {
            bflb_platform_delay_ms(gc9c01_disp_qspi_init_cmds[i].databytes);
        } else {
            qspi_address = (gc9c01_disp_qspi_init_cmds[i].cmd << 8) & 0x0000FF00;
            DBI_QSPI_SendCAWithNormalData(GC9C01_DISP_QSPI_CMD, qspi_address, gc9c01_disp_qspi_init_cmds[i].databytes, (uint8_t *)gc9c01_disp_qspi_init_cmds[i].data);
        }
    }
    return 0;
}

/**
 * @brief
 *
 * @param dir
 * @param mir_flag
 */
int gc9c01_disp_qspi_set_dir(uint8_t dir, uint8_t mir_flag)
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
    DBI_QSPI_SendCAWithNormalData(GC9C01_DISP_QSPI_CMD, 0x003600, 1, &param);
    return dir;
}

/**
 * @brief gc9c01_set_draw_window
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
void gc9c01_disp_qspi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
#if GC9C01_DISP_QSPI_OFFSET_X
    x1 += GC9C01_DISP_QSPI_OFFSET_X;
    x2 += GC9C01_DISP_QSPI_OFFSET_X;
#endif
#if GC9C01_DISP_QSPI_OFFSET_Y
    y1 += GC9C01_DISP_QSPI_OFFSET_Y;
    y2 += GC9C01_DISP_QSPI_OFFSET_Y;
#endif

    uint8_t param[4];

    param[0] = (x1 >> 8) & 0xFF;
    param[1] = x1 & 0xFF;
    param[2] = (x2 >> 8) & 0xFF;
    param[3] = x2 & 0xFF;
    DBI_QSPI_SendCAWithNormalData(GC9C01_DISP_QSPI_CMD, 0x002A00, 4, param);

    param[0] = (y1 >> 8) & 0xFF;
    param[1] = y1 & 0xFF;
    param[2] = (y2 >> 8) & 0xFF;
    param[3] = y2 & 0xFF;
    DBI_QSPI_SendCAWithNormalData(GC9C01_DISP_QSPI_CMD, 0x002B00, 4, param);
}

/**
 * @brief gc9c01_draw_point
 *
 * @param x
 * @param y
 * @param color
 */
void gc9c01_disp_qspi_draw_point(uint16_t x, uint16_t y, gc9c01_disp_qspi_color_t color)
{
    /* set window */
    gc9c01_disp_qspi_set_draw_window(x, y, x, y);
    /* send data of pixel */
    DBI_QSPI_SendCAWithPixelData(GC9C01_DISP_QSPI_CMD, 0x002C00, 1, (uint32_t *)(&color));
}

/**
 * @brief gc9c01_draw_area
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void gc9c01_disp_qspi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t color)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);
    uint32_t color_src;

    gc9c01_disp_qspi_set_draw_window(x1, y1, x2, y2);

    /* disable transfer */
    DBI_Disable();

    /* high speed mode */
    DBI_SetPeriod(&period_hs);

    /* clear fifo and interrupt */
    DBI_TxFifoClear();
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(GC9C01_DISP_QSPI_CMD);
    /* set address */
    DBI_QSPI_SetAddress(0x002C00);

    /* Data type select, and set data count */
    DBI_SetDataTypeAndCount(DBI_DATA_PIXEL, PixelCount);

    /* get pixel Data Size */
#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
    pixelDataSize = ((PixelCount + 1) >> 1) << 2;
    color_src = color << 16 | color;
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
    pixelDataSize = PixelCount << 2;
    color_src = color;
#endif

    /* sync mode, temporary shutdown interrupt */
    gc9c01_disp_qspi_sync_flush_flag = true;

    /* disable src_addr_inc */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)DISABLE);
    /* DMA config */
    dma_reload(dma_dbi_tx, (uint32_t)(uintptr_t)(&color_src), (uint32_t)DMA_ADDR_DBI_TDR, pixelDataSize);

#if defined(BL616)
    csi_dcache_clean_range((void *)(&color_src), sizeof(color_src));
#endif

    /* enable DBI-DMA request */
    DBI_SetDMA(ENABLE);

    /* Enable DMA */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CHANNEL_START, NULL);

    /* Enable DBI transfer */
    DBI_Enable();

    while (gc9c01_disp_qspi_draw_is_busy()) {
    }

    /* enable src_addr_inc */
    device_control(dma_dbi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)ENABLE);
}

/**
 * @brief gc9c01_draw_picture_dma, Non-blocking! Using DMA acceleration, Not waiting for the draw end
 *  After the call, No other operations are allowed until (gc9c01_draw_is_busy()==0)
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void gc9c01_disp_qspi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);

    gc9c01_disp_qspi_set_draw_window(x1, y1, x2, y2);

    /* disable transfer */
    DBI_Disable();

    /* high speed mode */
    DBI_SetPeriod(&period_hs);

    /* clear fifo and interrupt */
    DBI_TxFifoClear();
    DBI_IntClear();

    /* set command */
    DBI_SetCommand(GC9C01_DISP_QSPI_CMD);
    /* set address */
    DBI_QSPI_SetAddress(0x002C00);

    /* Data type select, and set data count */
    DBI_SetDataTypeAndCount(DBI_DATA_PIXEL, PixelCount);

    /* DMA config */
#if (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB565)
    pixelDataSize = ((PixelCount + 1) >> 1) << 2;
#elif (GC9C01_DISP_QSPI_PIXEL_FORMAT == GC9C01_DISP_QSPI_PIXEL_FORMAT_RGB888)
    pixelDataSize = PixelCount << 2;
#endif

    dma_reload(dma_dbi_tx, (uint32_t)picture, (uint32_t)DMA_ADDR_DBI_TDR, pixelDataSize);

#if defined(BL616)
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
 * @brief gc9c01_draw_picture,Blocking，Using DMA acceleration,Waiting for the draw end
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void gc9c01_disp_qspi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gc9c01_disp_qspi_color_t *picture)
{
    gc9c01_disp_qspi_set_draw_window(x1, y1, x2, y2);

    /* high speed mode */
    DBI_SetPeriod(&period_hs);

    DBI_QSPI_SendCAWithPixelData(GC9C01_DISP_QSPI_CMD, 0x002C00, (x2 - x1 + 1) * (y2 - y1 + 1), (uint32_t *)picture);

    /* low speed mode */
    DBI_SetPeriod(&period_ls);
}

#elif defined(LCD_DISP_QSPI_GC9C01)
#error "Devices that do not support DISP-QSPI! Replace the driver port (lcd.h)"
#endif
