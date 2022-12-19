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
#ifndef __AUDIO_PLAYER_H__
#define __AUDIO_PLAYER_H__
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stream_buffer.h>
#include <bl_audio.h>
typedef enum {
    AUDIO_PLAYER_CMD_NONE,
    AUDIO_PLAYER_CMD_EVT,
    AUDIO_PLAYER_CMD_PLAY,
    AUDIO_PLAYER_CMD_PAUSE,
    AUDIO_PLAYER_CMD_RESUME,
    AUDIO_PLAYER_CMD_STOP,
    AUDIO_PLAYER_CMD_FIFO_CREATE,
    AUDIO_PLAYER_CMD_FIFO_DESTORY,
    AUDIO_PLAYER_CMD_FIFO_START,
    AUDIO_PLAYER_CMD_FIFO_STOP,
    AUDIO_PLAYER_CMD_FIFO_ID3TAG_DROP,
 
    /*sample rate related*/
    AUDIO_PLAYER_CMD_SAMPLE_RATE_CONFIG,
    AUDIO_PLAYER_CMD_RECORD_CONFIG,

    AUDIO_PLAYER_SIGNAL_OUTPUT_FETCHED,
    AUDIO_PLAYER_SIGNAL_INPUT_FETCHED,
} AUDIO_PLAYER_CMD_T;

typedef enum {
	AUDIO_PLAYER_EVENT_NONE,
	AUDIO_PLAYER_EVENT_START,
	AUDIO_PLAYER_EVENT_PAUSE,
	AUDIO_PLAYER_EVENT_STOP,
	AUDIO_PLAYER_EVENT_COMPLETE,
	AUDIO_PLAYER_EVENT_ERR,
} AUDIO_PLAYER_EVENT_T;

typedef int (*audio_player_event_cb)(int event, void *arg);

typedef enum {
    AUDIO_PLAYER_STATE_NULL = 0,
    AUDIO_PLAYER_STATE_PALYING,
    AUDIO_PLAYER_STATE_PAUSE,
    AUDIO_PLAYER_STATE_STOP,
    AUDIO_PLAYER_STATE_STOPING,
    AUDIO_PLAYER_STATE_MAX,
} audio_player_state_t;

typedef struct audio_player audio_player_t;
typedef struct audio_player {
    /*api function call*/
    int (*init)(audio_player_t *);
    void (*play)(audio_player_t *, char *url, audio_player_event_cb callback, void *cb_arg);
    void (*pause)(audio_player_t *);
    void (*resume)(audio_player_t *);
    void (*stop)(audio_player_t *);
    void (*fifo_create)(audio_player_t *);
    void (*fifo_destory)(audio_player_t *);
    void (*fifo_start)(audio_player_t *);
    void (*fifo_stop)(audio_player_t *, int stop_now);
    int (*fifo_write)(audio_player_t *, const void *data, int data_len, int isblock);

    /*Advanced api*/
    void (*set_samplerate)(audio_player_t *, int samplerate);
    void (*record_config)(audio_player_t *, int enable);
    size_t (*record_read)(audio_player_t *, void *buf, int len);

    /*status call*/
    int (*isrunning)(audio_player_t *);

    /*private sections*/
    QueueHandle_t qe_cmd;
    StreamBufferHandle_t rb_input;
    StreamBufferHandle_t rb_record;
    StreamBufferHandle_t rb_output;
    void *mp3decoder;//decoder holder

    char *url;
    audio_player_event_cb callback;
    void *cb_arg;
    int url_play_done;
    
    unsigned int flash_addr;
    unsigned int flash_len;
    unsigned int flash_read;

    /*player state*/
    audio_player_state_t state;

    /*audio_framework device*/
    //audio_framework_device_t *device;
    bl_audio_dev_t *device;
    TaskHandle_t task;
} audio_player_t;

int audio_player_init(void);
int audio_player_deinit(void);
int audio_player_get(audio_player_t **player);

#endif
