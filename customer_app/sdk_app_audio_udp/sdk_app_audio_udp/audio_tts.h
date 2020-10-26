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
#ifndef __AUDIO_TTS_H__
#define __AUDIO_TTS_H__

#include <FreeRTOS.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <bl_romfs.h>
#include <vfs.h>
#include <utils_list.h>
#include <fs/vfs_romfs.h>
#include <audio_framework.h>

#define DAC_AUDIO_BITS             10

#define DAC_AUDIO_NUM_TEN          10
#define DAC_AUDIO_NUM_HUNDRED      11
#define DAC_AUDIO_NUM_THOUSAND     12
#define DAC_AUDIO_NUM_TEN_THOUSAND 13
#define DAC_AUDIO_NUM_BILLION      14
#define DAC_AUDIO_NUM_POINT        15
#define DAC_AUDIO_NUM_END          16

#define NUM_FILEBUF_MAX_NUMS     DAC_AUDIO_NUM_END

typedef void (*audio_dac_pfn_t)(void *p_arg);

typedef struct audio_tts_item {
    struct utils_list_hdr item;
    romfs_filebuf_t num_file;
    uint8_t num;
    void (*cb)(void *arg);
    void *arg;
} audio_tts_item_t;

typedef struct audio_tts_event {
    struct utils_list_hdr hdr;
    struct utils_list item;
    void (*cb)(void *arg);
    void *arg;
    audio_dac_pfn_t usr_cb;
    void *p_usr_arg;
    uint32_t r_size;
} audio_tts_event_t;

typedef struct audio_tts_dev {
    audio_framework_device_t *p_audio_dev;
    romfs_filebuf_t num_filebuf[NUM_FILEBUF_MAX_NUMS];
    void *dma_irq_ev;
    void *dma_irq_item;
    struct utils_list dma_list_head;
    uint32_t r_size;
    uint8_t end_flag;
} audio_tts_dev_t;

int audio_tts_init (audio_tts_dev_t *p_dev, const char *name);

int audio_tts_deinit (audio_tts_dev_t *p_dev);

int audio_tts_num_play (audio_tts_dev_t *p_dev,
                        uint64_t num_int,
                        uint8_t num_decimal,
                        audio_dac_pfn_t cb,
                        void *p_arg);

int audio_tts_characters_play (audio_tts_dev_t *p_dev,
                               romfs_filebuf_t *p_file,
                               audio_dac_pfn_t cb,
                               void *p_arg);

int audio_tts_start (audio_tts_dev_t *p_dev);

int audio_tts_stop (audio_tts_dev_t *p_dev);

#endif
