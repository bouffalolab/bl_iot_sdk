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

#if defined(LCD_SPI_ILI9488)

#include "ili9488_spi.h"
#include "hal_spi.h"
#include "hal_dma.h"
#include "hal_gpio.h"

#if (defined(BL808) || defined(BL606P)) && defined(CPU_D0)
#define ILI9488_SPI_ID        1
#define ILI9488_SPI_INDEX     SPI1_INDEX
#define ILI9488_SPI_DMA_INDEX DMA2_CH0_INDEX
#else
#define ILI9488_SPI_ID        0
#define ILI9488_SPI_INDEX     SPI0_INDEX
#define ILI9488_SPI_DMA_INDEX DMA0_CH3_INDEX
#endif

/* asynchronous flush interrupt callback */
typedef void (*ili9488_spi_callback)(void);
static volatile ili9488_spi_callback ili9488_spi_async_callback = NULL;
static volatile bool ili9488_spi_sync_flush_flag = 0;

static struct device *ili9488_spi;
static struct device *dma_spi_tx;

const ili9488_spi_init_cmd_t ili9488_spi_init_cmds[] = {
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

    { 0x3A, "\x55", 1 }, /* Interface Pixel Format RGB565 */

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
 * @brief ili9488_spi_dma_flush_callback
 *
 * @return
 */
void ili9488_spi_dma_flush_callback(struct device *dev, void *args, uint32_t size, uint32_t event)
{
    if (ili9488_spi_sync_flush_flag == true) {
        ili9488_spi_sync_flush_flag = false;
        return;
    }

    while (lcd_draw_is_busy()) {
    };

    if (ili9488_spi_async_callback != NULL) {
        ili9488_spi_async_callback();
    }
}

/**
 * @brief ili9488_spi_async_callback_register
 *
 * @return
 */
void ili9488_spi_async_callback_register(void (*callback)(void))
{
    ili9488_spi_async_callback = callback;
}

/**
 * @brief ili9488_spi_init
 *
 * @return int  0:succes  1:error
 */
static int ili9488_spi_peripheral_init(void)
{
    gpio_set_mode(ILI9488_SPI_CS_PIN, GPIO_OUTPUT_MODE);
    gpio_set_mode(ILI9488_SPI_DC_PIN, GPIO_OUTPUT_MODE);
    ILI9488_SPI_CS_HIGH;
    ILI9488_SPI_DC_HIGH;

    ili9488_spi = device_find("lcd_dev_ifs");
    if (ili9488_spi) {
        device_close(ili9488_spi);
    } else {
        spi_register(ILI9488_SPI_INDEX, "lcd_dev_ifs");
        ili9488_spi = device_find("lcd_dev_ifs");
    }
    if (ili9488_spi) {
        SPI_DEV(ili9488_spi)->mode = SPI_MASTER_MODE;
#if defined(BL808) || defined(BL606P) || defined(BL616)
        SPI_DEV(ili9488_spi)->clk = (40 * 1000 * 1000);
        SPI_DEV(ili9488_spi)->direction = SPI_MSB_BYTE3_DIRECTION_FIRST;
#else
        SPI_DEV(ili9488_spi)->clk = (36 * 1000 * 1000);
        SPI_DEV(ili9488_spi)->direction = SPI_MSB_BYTE0_DIRECTION_FIRST;
#endif
        SPI_DEV(ili9488_spi)->datasize = SPI_DATASIZE_8BIT;
        SPI_DEV(ili9488_spi)->clk_polaraity = SPI_POLARITY_LOW;
        SPI_DEV(ili9488_spi)->clk_phase = SPI_PHASE_1EDGE;
#if (SPI_FIFO_LEN >= 16)
        SPI_DEV(ili9488_spi)->fifo_threshold = 7;
#else
        SPI_DEV(ili9488_spi)->fifo_threshold = 0;
#endif

        device_open(ili9488_spi, DEVICE_OFLAG_STREAM_TX);
    } else {
        return 1;
    }

    dma_spi_tx = device_find("lcd_dev_ifs_dma");
    if (dma_spi_tx) {
        device_close(dma_spi_tx);
    } else {
        dma_register(ILI9488_SPI_DMA_INDEX, "lcd_dev_ifs_dma");
        dma_spi_tx = device_find("lcd_dev_ifs_dma");
    }
    if (dma_spi_tx) {
        DMA_DEV(dma_spi_tx)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_spi_tx)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_spi_tx)->src_req = DMA_REQUEST_NONE;
#if (ILI9488_SPI_ID == 0)
        DMA_DEV(dma_spi_tx)->dst_req = DMA_REQUEST_SPI0_TX;
#elif (ILI9488_SPI_ID == 1)
        DMA_DEV(dma_spi_tx)->dst_req = DMA_REQUEST_SPI1_TX;
#endif
        DMA_DEV(dma_spi_tx)->src_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
        DMA_DEV(dma_spi_tx)->dst_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
#if (SPI_FIFO_LEN >= 16)
        DMA_DEV(dma_spi_tx)->src_burst_size = DMA_BURST_INCR4;
        DMA_DEV(dma_spi_tx)->dst_burst_size = DMA_BURST_INCR4;
#else
        DMA_DEV(dma_spi_tx)->src_burst_size = DMA_BURST_INCR1;
        DMA_DEV(dma_spi_tx)->dst_burst_size = DMA_BURST_INCR1;
#endif
        DMA_DEV(dma_spi_tx)->src_width = DMA_TRANSFER_WIDTH_16BIT;
        DMA_DEV(dma_spi_tx)->dst_width = DMA_TRANSFER_WIDTH_16BIT;

        device_open(dma_spi_tx, 0);
        device_control(ili9488_spi, DEVICE_CTRL_ATTACH_TX_DMA, dma_spi_tx);

        device_set_callback(dma_spi_tx, ili9488_spi_dma_flush_callback);
        device_control(dma_spi_tx, DEVICE_CTRL_SET_INT, NULL);
    } else {
        return 1;
    }

    device_control(ili9488_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);

    return 0;
}

/**
 * @brief ili9488_spi_write_cmd
 *
 * @param cmd
 * @return int 0:succes  1:error
 */
static int ili9488_spi_write_cmd(uint8_t cmd)
{
    ILI9488_SPI_DC_LOW;
    ILI9488_SPI_CS_LOW;
    int res = device_write(ili9488_spi, 0, &cmd, 1);
    ILI9488_SPI_CS_HIGH;
    ILI9488_SPI_DC_HIGH;
    return res;
}

/**
 * @brief ili9488_spi_write_data_byte
 *
 * @param data
 * @return int 0:succes  1:error
 */
static int ili9488_spi_write_data_byte(uint8_t data)
{
    ILI9488_SPI_CS_LOW;
    int res = device_write(ili9488_spi, 0, &data, 1);
    ILI9488_SPI_CS_HIGH;
    return res;
}

/**
 * @brief ili9488_spi_draw_is_busy, After the call ili9488_spi_draw_picture_dma must check this,
 *         if ili9488_spi_draw_is_busy() == 1, Don't allow other draw !!
 *         can run in the DMA interrupt callback function.
 *
 * @return int 0:draw end; 1:Being draw
 */
int ili9488_spi_draw_is_busy(void)
{
    if (dma_channel_check_busy(SPI_DEV(ili9488_spi)->tx_dma)) {
        return 1;
    } else {
        /* Wait for tx FIFO to be empty */
        while (device_control(ili9488_spi, DEVICE_CTRL_SPI_GET_TX_FIFO, NULL) < SPI_FIFO_LEN)
            ;
        /* Wait for the SPI bus to be idle */
        while (device_control(ili9488_spi, DEVICE_CTRL_SPI_GET_BUS_BUSY_STATUS, NULL) != 0)
            ;
        /* Switch the SPI to non-DMA mode */
        device_control(ili9488_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);
        ILI9488_SPI_CS_HIGH;

        device_control(ili9488_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_8BIT);
        return 0;
    }
}

/**
 * @brief ili9488_spi_init
 *
 * @return int
 */
int ili9488_spi_init()
{
    int res = ili9488_spi_peripheral_init();
    if (res) {
        return res;
    }

    for (uint16_t i = 0; i < (sizeof(ili9488_spi_init_cmds) / sizeof(ili9488_spi_init_cmd_t)); i++) {
        if (ili9488_spi_init_cmds[i].cmd == 0xFF) {
            bflb_platform_delay_ms(ili9488_spi_init_cmds[i].databytes);
        } else {
            /* send register address */
            res |= ili9488_spi_write_cmd(ili9488_spi_init_cmds[i].cmd);

            /* send register data */
            for (uint8_t j = 0; j < (ili9488_spi_init_cmds[i].databytes & 0x7F); j++) {
                res |= ili9488_spi_write_data_byte(ili9488_spi_init_cmds[i].data[j]);
            }

            if (res) {
                return res;
            }
        }
    }
    ili9488_spi_set_draw_window(0, 0, ILI9488_SPI_H, ILI9488_SPI_W);
    return res;
}

#if defined(BL702) || defined(BL602)

/**
 * @brief lcd_swap_color_data16
 *
 * @param dst destination
 * @param src source
 * @param color_num color num
 * @return int
 */
static int lcd_swap_color_data16(uint16_t *dst, uint16_t *src, uint32_t color_num)
{
    for (size_t i = 0; i < color_num; i++) {
        dst[i] = (src[i] << 8) | (src[i] >> 8);
    }
    return 0;
}

#endif

/**
 * @brief
 *
 * @param dir
 * @param mir_flag
 */
int ili9488_spi_set_dir(uint8_t dir, uint8_t mir_flag)
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
    ili9488_spi_write_cmd(0x36);
    ili9488_spi_write_data_byte(param);
    return dir;
}

/**
 * @brief ili9488_spi_set_draw_window
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
void ili9488_spi_set_draw_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
#if ILI9488_SPI_OFFSET_X
    x1 += ILI9488_SPI_OFFSET_X;
    x2 += ILI9488_SPI_OFFSET_X;
#endif
#if ILI9488_SPI_OFFSET_Y
    y1 += ILI9488_SPI_OFFSET_Y;
    y2 += ILI9488_SPI_OFFSET_Y;
#endif

    ili9488_spi_write_cmd(0x2a);
    ili9488_spi_write_data_byte(x1 >> 8);
    ili9488_spi_write_data_byte(x1);
    ili9488_spi_write_data_byte(x2 >> 8);
    ili9488_spi_write_data_byte(x2);

    ili9488_spi_write_cmd(0x2b);
    ili9488_spi_write_data_byte(y1 >> 8);
    ili9488_spi_write_data_byte(y1);
    ili9488_spi_write_data_byte(y2 >> 8);
    ili9488_spi_write_data_byte(y2);

    ili9488_spi_write_cmd(0x2c);
}

/**
 * @brief ili9488_spi_draw_point
 *
 * @param x
 * @param y
 * @param color
 */
void ili9488_spi_draw_point(uint16_t x, uint16_t y, ili9488_spi_color_t color)
{
#if defined(BL808) || defined(BL606P) || defined(BL616)
#else
    color = ((color >> 8) & 0xFF) | color << 8;
#endif

    ili9488_spi_set_draw_window(x, y, x, y);
    ILI9488_SPI_DC_HIGH;
    ILI9488_SPI_CS_LOW;
    device_write(ili9488_spi, 0, &color, 2);
    ILI9488_SPI_CS_HIGH;
}

/**
 * @brief ili9488_spi_draw_area
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void ili9488_spi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_spi_color_t color)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);
    uint32_t color_src;

#if defined(BL808) || defined(BL606P) || defined(BL616)
    color_src = color;
    csi_dcache_clean_range((void *)(&color_src), sizeof(color_src));
#else
    color_src = ((color >> 8) & 0xFF) | color << 8;
#endif

    ili9488_spi_set_draw_window(x1, y1, x2, y2);

    /* get pixel Data Size */
    pixelDataSize = PixelCount << 1;

    device_control(ili9488_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_16BIT);

    /* disable src_addr_inc */
    device_control(dma_spi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)DISABLE);

    ILI9488_SPI_CS_LOW;

    /* sync mode, temporary shutdown interrupt */
    ili9488_spi_sync_flush_flag = true;

    /* dma write */
    device_control(ili9488_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
    device_write(ili9488_spi, 0, &color_src, pixelDataSize);

    /* Wait to finish, and cs high */
    while (ili9488_spi_draw_is_busy()) {
    };

    /* enable src_addr_inc */
    device_control(dma_spi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)ENABLE);
}

/**
 * @brief ili9488_spi_draw_picture_dma, Non-blocking! Using DMA acceleration, Not waiting for the draw end
 *  After the call, No other operations are allowed until (ili9488_spi_draw_is_busy()==0)
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */

void ili9488_spi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_spi_color_t *picture)
{
    size_t picture_size = (x2 - x1 + 1) * (y2 - y1 + 1);

    ili9488_spi_set_draw_window(x1, y1, x2, y2);

#if defined(BL808) || defined(BL606P) || defined(BL616)
    csi_dcache_clean_range((void *)(picture), (picture_size << 1));
#else
    lcd_swap_color_data16(picture, picture, picture_size);
#endif

    device_control(ili9488_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_16BIT);

    ILI9488_SPI_CS_LOW;

    device_control(ili9488_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
    device_write(ili9488_spi, 0, picture, (picture_size << 1));
}

/**
 * @brief ili9488_spi_draw_picture,Blocking，Using DMA acceleration,Waiting for the draw end
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void ili9488_spi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, ili9488_spi_color_t *picture)
{
    /* sync mode, temporary shutdown interrupt */
    ili9488_spi_sync_flush_flag = true;

    ili9488_spi_draw_picture_nonblocking(x1, y1, x2, y2, picture);
    while (ili9488_spi_draw_is_busy()) {
    };
}

#endif
