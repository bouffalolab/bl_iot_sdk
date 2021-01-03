/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <blog.h>
#include <bl_adc.h>
#include <bl_irq.h>
#include <bl_dma.h>
#include <hal_adc.h>

static int check_adc_gpio_valid(int gpio_num)
{
    int i;
    int gpio_arr[12] = {4, 5, 6, 9, 10, 11, 12, 13, 14, 15};

    for (i = 0; i < 10; i++) {
        if (gpio_num == gpio_arr[i]) {
            return 0;
        }
    }

    return -1;
}

//mode = 0, for normal adc. freq 40HZ~1300HZ. one time sampling one data.
//mode = 1, for mic, freq 500HZ~16000HZ, one time sampling data_num data.
int hal_adc_init(int mode, int freq, int data_num, int gpio_num)
{
    int ret;
    int buf_size;

    if (mode == 0) {
        if (freq < 40 || freq > 1300) {
            blog_error("illegal freq. for mode0, freq 40HZ ~ 1300HZ \r\n");

            return -1;
        }
    } else if (mode == 1) {
        if (freq < 500 || freq > 16000) {
            blog_error("illegal freq. for mode1, freq 500HZ ~ 16000HZ \r\n");

            return -1;
        }
    } else {
        blog_error("illegal mode. \r\n");

        return -1;
    }

    ret = check_adc_gpio_valid(gpio_num);
    if (ret != 0) {
        blog_error("illegal gpio num \r\n");

        return -1;
    }

    bl_adc_freq_init(mode, freq);
    bl_adc_init(mode, gpio_num);

    if (mode == 0) {
        buf_size = ADC_CHANNEL_MAX;
    } else {
        buf_size = data_num;
    }
    ret = bl_adc_dma_init(mode, buf_size);
    if (ret < 0) {
        blog_error("adc init failed \r\n");

        return -1;
    }

    hal_adc_add_channel(gpio_num);

    bl_adc_start();

    return 0;
}

int hal_adc_callback_register(bl_adc_cb_t cb)
{
    adc_ctx_t *ctx;

    if (cb == NULL) {
        blog_error("cb is NULL, register failed. \r\n");

        return -1;
    }

    ctx = bl_dma_find_ctx_by_channel(ADC_DMA_CHANNEL);
    ctx->cb = cb;

    return 0;
}

/* the following function for mode 0*/
int hal_adc_add_channel(int gpio_num)
{
    int ret;
    adc_ctx_t *pstctx;
    int channel;

    ret = check_adc_gpio_valid(gpio_num);
    if (ret < 0) {
        blog_error("not legal gpio num, adc only support gpio 4,5,6,9,10,11,12,13,14,15 \r\n");

        return -1;
    }

    bl_adc_gpio_init(gpio_num);
    channel = bl_adc_get_channel_by_gpio(gpio_num);
    pstctx = bl_dma_find_ctx_by_channel(ADC_DMA_CHANNEL);
    pstctx->chan_init_table = pstctx->chan_init_table | (1 << channel);

    return 0;
}

int32_t hal_adc_get_data(int gpio_num, int raw_flag)
{
    int ret;
    adc_ctx_t *pstctx;
    uint32_t adc_data[ADC_CHANNEL_MAX];
    int32_t data;
    int channel;

    ret = check_adc_gpio_valid(gpio_num);
    if (ret < 0) {
        blog_error("not legal gpio num, adc only support gpio 4,5,6,9,10,11,12,13,14,15 \r\n");

        return -1;
    }

    pstctx = bl_dma_find_ctx_by_channel(ADC_DMA_CHANNEL);
    if (pstctx == NULL) {
        blog_error("get ctx error \r\n");

        return -1;
    }

    channel = bl_adc_get_channel_by_gpio(gpio_num);
    if (((1 << channel) & pstctx->chan_init_table) == 0) {
        blog_error("gpio = %d  not init as adc \r\n", gpio_num);
        return -1;
    }

    if (pstctx->channel_data == NULL) {
        blog_error("adc sampling not finish. \r\n");

        return -1;
    }
    memcpy((uint8_t*)adc_data, (uint8_t*)(pstctx->channel_data), ADC_CHANNEL_MAX * 4);
    data = bl_adc_parse_data(adc_data, ADC_CHANNEL_MAX, channel, raw_flag);

    return data;
}

int32_t hal_prase_adc_data(uint32_t *ptr, int gpio_num, int raw_flag)
{
    int32_t data;
    int channel;

    channel = bl_adc_get_channel_by_gpio(gpio_num);
    if (channel == -1) {
        blog_error("illegal gpio num. \r\n");

        return -1;
    }

    data = bl_adc_parse_data(ptr, ADC_CHANNEL_MAX, channel, raw_flag);

    return data;
}

/* the following function for mode 1*/
int hal_parse_data_arr(uint32_t *ptr, uint32_t *output, uint32_t data_size)
{
    int i;

    for (i = 0; i < data_size; i++) {
        output[i] = ptr[i] & 0xffff;
    }

    return 0;
}
