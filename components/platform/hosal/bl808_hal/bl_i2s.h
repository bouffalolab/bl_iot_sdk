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
#ifndef __BL_I2S_H__
#define __BL_I2S_H__
#include <stddef.h>

typedef enum {
    BL_I2S_ID_0,
    BL_I2S_ID_1,
} BL_I2S_ID_T;

typedef enum {
    BL_I2S_FORMAT_DATA_BIT8,
    BL_I2S_FORMAT_DATA_BIT16,
    BL_I2S_FORMAT_DATA_BIT24,
    BL_I2S_FORMAT_DATA_BIT32,
} BL_I2S_FORMAT_DATA_T;

typedef enum {
    BL_I2S_FORMAT_WIDTH_BIT8,
    BL_I2S_FORMAT_WIDTH_BIT16,
    BL_I2S_FORMAT_WIDTH_BIT24,
    BL_I2S_FORMAT_WIDTH_BIT32,
} BL_I2S_FORMAT_WIDTH_T;

typedef enum {
    BL_I2S_FORMAT_FRAME_OUTPUT_BIT8,
    BL_I2S_FORMAT_FRAME_OUTPUT_BIT16,
    BL_I2S_FORMAT_FRAME_OUTPUT_BIT24,
    BL_I2S_FORMAT_FRAME_OUTPUT_BIT32,
} BL_I2S_FORMAT_FRAME_OUTPUT_T;

typedef enum {
    BL_I2S_SAMPLE_RATE_8K,
    BL_I2S_SAMPLE_RATE_11P025K,
    BL_I2S_SAMPLE_RATE_12K,
    BL_I2S_SAMPLE_RATE_16K,
    BL_I2S_SAMPLE_RATE_22P05K,
    BL_I2S_SAMPLE_RATE_24K,
    BL_I2S_SAMPLE_RATE_32K,
    BL_I2S_SAMPLE_RATE_44P1K,
    BL_I2S_SAMPLE_RATE_48K,
    BL_I2S_SAMPLE_RATE_96K,
    BL_I2S_SAMPLE_RATE_192K,
} BL_I2S_SAMPLE_RATE_T;

typedef enum {
    BL_I2S_MODE_NORMAL,
    BL_I2S_MODE_LEFT,
    BL_I2S_MODE_RIGHT,
} BL_I2S_MODE_T;

typedef enum {
    /*16bit*/
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH16BIT_MONO,
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH24BIT_MONO,
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH32BIT_MONO,
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH16BIT_STERO,
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH24BIT_STERO,
    BL_AUDIO_FORMAT_DATA16BIT_WIDTH32BIT_STERO,

    /*24bit*/
    BL_AUDIO_FORMAT_DATA24BIT_WIDTH24BIT_MONO,
    BL_AUDIO_FORMAT_DATA24BIT_WIDTH32BIT_MONO,
    BL_AUDIO_FORMAT_DATA24BIT_WIDTH24BIT_STERO,
    BL_AUDIO_FORMAT_DATA24BIT_WIDTH32BIT_STERO,

    /*32bit*/
    BL_AUDIO_FORMAT_DATA32BIT_WIDTH32BIT_MONO,
    BL_AUDIO_FORMAT_DATA32BIT_WIDTH32BIT_STERO,
} BL_AUDIO_FORMAT_T;

typedef int (*bl_audio_callback_tx_ready_t)(void *usrdata, uint8_t *audiodata, int len, int is_overflow);
typedef int (*bl_audio_callback_rx_ready_t)(void *usrdata, uint8_t *audiodata, int len, int is_overflow);

int bl_i2s_tx_buffer_config(int size, void **ptr_mem, void *(*malloc_dma_ptr)(size_t size));
int bl_i2s_rx_buffer_config(int size, void **ptr_mem, void *(*malloc_dma_ptr)(size_t size));
int bl_i2s_init(int tx_enable, int rx_enable, void *(*malloc_dma_ptr)(size_t size), void (*free_dma_ptr)(void*ptr));
int bl_i2s_unint(void (*free_dma_ptr)(void* ptr));
int bl_i2s_start(void);
int bl_i2s_stop(void);
int bl_i2s_sample_rate_config(BL_I2S_SAMPLE_RATE_T config);
int bl_i2s_configure(BL_AUDIO_FORMAT_T format);
int bl_i2s_set_mclk(uint32_t mclk);
int bl_i2s_tx_ready_config(bl_audio_callback_tx_ready_t cb, void *usrdata);
int bl_i2s_rx_ready_config(bl_audio_callback_rx_ready_t cb, void *usrdata);

#endif
