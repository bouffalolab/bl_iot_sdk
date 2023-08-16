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

#if defined(LCD_SPI_ST7796)

#include "st7796_spi.h"
#include "hal_spi.h"
#include "hal_dma.h"
#include "hal_gpio.h"

#if (defined(BL808) || defined(BL606P)) && defined(CPU_D0)
#define ST7796_SPI_ID        1
#define ST7796_SPI_INDEX     SPI1_INDEX
#define ST7796_SPI_DMA_INDEX DMA2_CH0_INDEX
#else
#define ST7796_SPI_ID        0
#define ST7796_SPI_INDEX     SPI0_INDEX
#define ST7796_SPI_DMA_INDEX DMA0_CH3_INDEX
#endif

/* asynchronous flush interrupt callback */
typedef void (*st7796_spi_callback)(void);
static volatile st7796_spi_callback st7796_spi_async_callback = NULL;
static volatile bool st7796_spi_sync_flush_flag = 0;

static struct device *st7796_spi;
static struct device *dma_spi_tx;

const st7796_spi_init_cmd_t st7796_spi_init_cmds[] = {
    { 0x01, NULL, 0 },
    { 0xFF, NULL, 10 },
    { 0x11, NULL, 0 }, /* Exit sleep */
    { 0xFF, NULL, 120 },

    { 0xF0, "\xC3", 1 },
    { 0xF0, "\x96", 1 },

    { 0x36, "\x48", 1 },

    { 0x3A, "\x05", 1 }, /* RGB565 */
    { 0xE6, "\x0F\xF2\x3F\x4F\x4F\x28\x0E\x00", 8 },
    { 0xC5, "\x2A", 1 },

/* Display Inversion */
#if 0
    { 0xB4, "\x01", 1 },
    { 0x21, NULL, 0 },
#endif

    { 0xE0, "\xF0\x03\x0A\x11\x14\x1C\x3B\x55\x4A\x0A\x13\x14\x1C\x1F", 14 }, /* Set Gamma */
    { 0XE1, "\xF0\x03\x0A\x0C\x0C\x09\x36\x54\x49\x0F\x1B\x18\x1B\x1F", 14 }, /* Set Gamma */

    { 0xF0, "\x3C", 1 },
    { 0xF0, "\x69", 1 },

    { 0x29, NULL, 0 }, /* Display on */
    { 0xFF, NULL, 10 },
};

/**
 * @brief st7796_spi_dma_flush_callback
 *
 * @return
 */
void st7796_spi_dma_flush_callback(struct device *dev, void *args, uint32_t size, uint32_t event)
{
    if (st7796_spi_sync_flush_flag == true) {
        st7796_spi_sync_flush_flag = false;
        return;
    }

    while (lcd_draw_is_busy()) {
    };

    if (st7796_spi_async_callback != NULL) {
        st7796_spi_async_callback();
    }
}

/**
 * @brief st7796_spi_async_callback_register
 *
 * @return
 */
void st7796_spi_async_callback_register(void (*callback)(void))
{
    st7796_spi_async_callback = callback;
}

/**
 * @brief st7796_spi_init
 *
 * @return int  0:succes  1:error
 */
static int st7796_spi_peripheral_init(void)
{
    gpio_set_mode(ST7796_SPI_CS_PIN, GPIO_OUTPUT_MODE);
    gpio_set_mode(ST7796_SPI_DC_PIN, GPIO_OUTPUT_MODE);
    ST7796_SPI_CS_HIGH;
    ST7796_SPI_DC_HIGH;

    st7796_spi = device_find("lcd_dev_ifs");
    if (st7796_spi) {
        device_close(st7796_spi);
    } else {
        spi_register(ST7796_SPI_INDEX, "lcd_dev_ifs");
        st7796_spi = device_find("lcd_dev_ifs");
    }
    if (st7796_spi) {
        SPI_DEV(st7796_spi)->mode = SPI_MASTER_MODE;
#if defined(BL808) || defined(BL606P) || defined(BL616)
        SPI_DEV(st7796_spi)->clk = (40 * 1000 * 1000);
        SPI_DEV(st7796_spi)->direction = SPI_MSB_BYTE3_DIRECTION_FIRST;
#else
        SPI_DEV(st7796_spi)->clk = (36 * 1000 * 1000);
        SPI_DEV(st7796_spi)->direction = SPI_MSB_BYTE0_DIRECTION_FIRST;
#endif
        SPI_DEV(st7796_spi)->datasize = SPI_DATASIZE_8BIT;
        SPI_DEV(st7796_spi)->clk_polaraity = SPI_POLARITY_LOW;
        SPI_DEV(st7796_spi)->clk_phase = SPI_PHASE_1EDGE;
#if (SPI_FIFO_LEN >= 16)
        SPI_DEV(st7796_spi)->fifo_threshold = 7;
#else
        SPI_DEV(st7796_spi)->fifo_threshold = 0;
#endif

        device_open(st7796_spi, DEVICE_OFLAG_STREAM_TX);
    } else {
        return 1;
    }

    dma_spi_tx = device_find("lcd_dev_ifs_dma");
    if (dma_spi_tx) {
        device_close(dma_spi_tx);
    } else {
        dma_register(ST7796_SPI_DMA_INDEX, "lcd_dev_ifs_dma");
        dma_spi_tx = device_find("lcd_dev_ifs_dma");
    }
    if (dma_spi_tx) {
        DMA_DEV(dma_spi_tx)->direction = DMA_MEMORY_TO_PERIPH;
        DMA_DEV(dma_spi_tx)->transfer_mode = DMA_LLI_ONCE_MODE;
        DMA_DEV(dma_spi_tx)->src_req = DMA_REQUEST_NONE;
#if (ST7796_SPI_ID == 0)
        DMA_DEV(dma_spi_tx)->dst_req = DMA_REQUEST_SPI0_TX;
#elif (ST7796_SPI_ID == 1)
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
        device_control(st7796_spi, DEVICE_CTRL_ATTACH_TX_DMA, dma_spi_tx);

        device_set_callback(dma_spi_tx, st7796_spi_dma_flush_callback);
        device_control(dma_spi_tx, DEVICE_CTRL_SET_INT, NULL);
    } else {
        return 1;
    }

    device_control(st7796_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);

    return 0;
}

/**
 * @brief st7796_spi_write_cmd
 *
 * @param cmd
 * @return int 0:succes  1:error
 */
static int st7796_spi_write_cmd(uint8_t cmd)
{
    ST7796_SPI_DC_LOW;
    ST7796_SPI_CS_LOW;
    int res = device_write(st7796_spi, 0, &cmd, 1);
    ST7796_SPI_CS_HIGH;
    ST7796_SPI_DC_HIGH;
    return res;
}

/**
 * @brief st7796_spi_write_data_byte
 *
 * @param data
 * @return int 0:succes  1:error
 */
static int st7796_spi_write_data_byte(uint8_t data)
{
    ST7796_SPI_CS_LOW;
    int res = device_write(st7796_spi, 0, &data, 1);
    ST7796_SPI_CS_HIGH;
    return res;
}

/**
 * @brief st7796_spi_draw_is_busy, After the call st7796_spi_draw_picture_dma must check this,
 *         if st7796_spi_draw_is_busy() == 1, Don't allow other draw !!
 *         can run in the DMA interrupt callback function.
 *
 * @return int 0:draw end; 1:Being draw
 */
int st7796_spi_draw_is_busy(void)
{
    if (dma_channel_check_busy(SPI_DEV(st7796_spi)->tx_dma)) {
        return 1;
    } else {
        /* Wait for tx FIFO to be empty */
        while (device_control(st7796_spi, DEVICE_CTRL_SPI_GET_TX_FIFO, NULL) < SPI_FIFO_LEN)
            ;
        /* Wait for the SPI bus to be idle */
        while (device_control(st7796_spi, DEVICE_CTRL_SPI_GET_BUS_BUSY_STATUS, NULL) != 0)
            ;
        /* Switch the SPI to non-DMA mode */
        device_control(st7796_spi, DEVICE_CTRL_TX_DMA_SUSPEND, NULL);
        ST7796_SPI_CS_HIGH;

        device_control(st7796_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_8BIT);
        return 0;
    }
}

/**
 * @brief st7796_spi_init
 *
 * @return int
 */
int st7796_spi_init()
{
    int res = st7796_spi_peripheral_init();
    if (res) {
        return res;
    }

    for (uint16_t i = 0; i < (sizeof(st7796_spi_init_cmds) / sizeof(st7796_spi_init_cmd_t)); i++) {
        if (st7796_spi_init_cmds[i].cmd == 0xFF) {
            bflb_platform_delay_ms(st7796_spi_init_cmds[i].databytes);
        } else {
            /* send register address */
            res |= st7796_spi_write_cmd(st7796_spi_init_cmds[i].cmd);

            /* send register data */
            for (uint8_t j = 0; j < (st7796_spi_init_cmds[i].databytes & 0x7F); j++) {
                res |= st7796_spi_write_data_byte(st7796_spi_init_cmds[i].data[j]);
            }

            if (res) {
                return res;
            }
        }
    }
    st7796_spi_set_draw_window(0, 0, ST7796_SPI_H, ST7796_SPI_W);
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
int st7796_spi_set_dir(uint8_t dir, uint8_t mir_flag)
{
    uint8_t param;
    switch (dir) {
        case 0:
            if (!mir_flag)
                param = 0x08;
            else
                param = 0x48;
            break;
        case 1:
            if (!mir_flag)
                param = 0xA8;
            else
                param = 0x28;
            break;
        case 2:
            if (!mir_flag)
                param = 0xC8;
            else
                param = 0x88;
            break;
        case 3:
            if (!mir_flag)
                param = 0x68;
            else
                param = 0xE8;

            break;
        default:
            return -1;
            break;
    }
    st7796_spi_write_cmd(0x36);
    st7796_spi_write_data_byte(param);
    return dir;
}

/**
 * @brief st7796_spi_set_draw_window
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
void st7796_spi_set_draw_window(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
#if ST7796_SPI_OFFSET_X
    x1 += ST7796_SPI_OFFSET_X;
    x2 += ST7796_SPI_OFFSET_X;
#endif
#if ST7796_SPI_OFFSET_Y
    y1 += ST7796_SPI_OFFSET_Y;
    y2 += ST7796_SPI_OFFSET_Y;
#endif

    st7796_spi_write_cmd(0x2a);
    st7796_spi_write_data_byte(x1 >> 8);
    st7796_spi_write_data_byte(x1);
    st7796_spi_write_data_byte(x2 >> 8);
    st7796_spi_write_data_byte(x2);

    st7796_spi_write_cmd(0x2b);
    st7796_spi_write_data_byte(y1 >> 8);
    st7796_spi_write_data_byte(y1);
    st7796_spi_write_data_byte(y2 >> 8);
    st7796_spi_write_data_byte(y2);

    st7796_spi_write_cmd(0x2c);
}

/**
 * @brief st7796_spi_draw_point
 *
 * @param x
 * @param y
 * @param color
 */
void st7796_spi_draw_point(uint16_t x, uint16_t y, st7796_spi_color_t color)
{
#if defined(BL808) || defined(BL606P) || defined(BL616)
#else
    color = ((color >> 8) & 0xFF) | color << 8;
#endif

    st7796_spi_set_draw_window(x, y, x, y);
    ST7796_SPI_DC_HIGH;
    ST7796_SPI_CS_LOW;
    device_write(st7796_spi, 0, &color, 2);
    ST7796_SPI_CS_HIGH;
}

/**
 * @brief st7796_draw_area
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param color
 */
void st7796_spi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, st7796_spi_color_t color)
{
    uint32_t pixelDataSize, PixelCount = (x2 - x1 + 1) * (y2 - y1 + 1);
    uint32_t color_src;

#if defined(BL808) || defined(BL606P) || defined(BL616)
    color_src = color;
    csi_dcache_clean_range((void *)(&color_src), sizeof(color_src));
#else
    color_src = ((color >> 8) & 0xFF) | color << 8;
#endif

    st7796_spi_set_draw_window(x1, y1, x2, y2);

    /* get pixel Data Size */
    pixelDataSize = PixelCount << 1;

    device_control(st7796_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_16BIT);

    /* disable src_addr_inc */
    device_control(dma_spi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)DISABLE);

    ST7796_SPI_CS_LOW;

    /* sync mode, temporary shutdown interrupt */
    st7796_spi_sync_flush_flag = true;

    /* dma write */
    device_control(st7796_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
    device_write(st7796_spi, 0, &color_src, pixelDataSize);

    /* Wait to finish, and cs high */
    while (st7796_spi_draw_is_busy()) {
    };

    /* enable src_addr_inc */
    device_control(dma_spi_tx, DEVICE_CTRL_DMA_CONFIG_SI, (void *)ENABLE);
}

/**
 * @brief st7796_draw_picture_dma, Non-blocking! Using DMA acceleration, Not waiting for the draw end
 *  After the call, No other operations are allowed until (st7796_draw_is_busy()==0)
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void st7796_spi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, st7796_spi_color_t *picture)
{
    size_t picture_size = (x2 - x1 + 1) * (y2 - y1 + 1);

    st7796_spi_set_draw_window(x1, y1, x2, y2);

#if defined(BL808) || defined(BL606P) || defined(BL616)
    csi_dcache_clean_range((void *)(picture), (picture_size << 1));
#else
    lcd_swap_color_data16(picture, picture, picture_size);
#endif

    device_control(st7796_spi, DEVICE_CTRL_SPI_SET_FRAME_SIZE, (void *)SPI_DATASIZE_16BIT);

    ST7796_SPI_CS_LOW;

    device_control(st7796_spi, DEVICE_CTRL_TX_DMA_RESUME, NULL);
    device_write(st7796_spi, 0, picture, (picture_size << 1));
}

/**
 * @brief st7796_draw_picture,Blocking,Using DMA acceleration,Waiting for the draw end
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param picture
 */
void st7796_spi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, st7796_spi_color_t *picture)
{
    /* sync mode, temporary shutdown interrupt */
    st7796_spi_sync_flush_flag = true;

    st7796_spi_draw_picture_nonblocking(x1, y1, x2, y2, picture);
    while (st7796_spi_draw_is_busy()) {
    };
}

#endif
