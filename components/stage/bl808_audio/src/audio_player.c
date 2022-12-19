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
#include <utils_debug.h>
#include <utils_log.h>
#include <audio_player.h>


#define TASK_PRIORITY_PLAYER    (10)
#define DECODER_INPUT_BUFFER_SIZE     (8 * 1024)

#define DECODER_OUTPUT_BUFFER_ONCE     (1152 * 4)
#define OUTPUT_BUFFER_THREHOLD         (1152 * 4)
#define DECODER_OUTPUT_BUFFER_SIZE     (2 * 1152 * 4)

typedef struct {
    void *msg;
    void *arg1;
    void *arg2;
    void *arg3;
} player_cmd_t;

static audio_player_t *_player;
static uint8_t *tx_buffer = NULL;
static uint8_t *rx_buffer = NULL;
static uint8_t *media_data = NULL;
static uint32_t buffer_len;
static uint8_t *record_data = NULL;
static uint32_t record_len;
static int rx_disable = 0;

static int _player_create(void);
static void _callback_notify(audio_player_t *player, AUDIO_PLAYER_EVENT_T event);

int audio_player_get(audio_player_t **player)
{
    if (NULL == _player) {
        return -1;
    }
    *player = _player;
    return 0;
}

int audio_player_init(void)
{
    if (NULL == _player) {
        if (_player_create()) {
            return -1;
        }
    }

    return 0;
}

int audio_player_deinit(void)
{
    return 0;
}

static void _callback_notify(audio_player_t *player, AUDIO_PLAYER_EVENT_T event)
{
    if (player->callback) {
        player->callback(event, player->cb_arg);
    }
}

static void _fifo_reset(audio_player_t *player)
{
    xStreamBufferReset(player->rb_input);
    /*clean rb_input*/
}

void _player_thread_entry(void *param)
{
    audio_player_t *player = _player;
    AUDIO_PLAYER_CMD_T cmd;
    BaseType_t ret;
    player_cmd_t cmd_msg;

    (void) ret;

    while (1) {
        /* Step one, Get the proper command */
        ret = xQueueReceive(player->qe_cmd, &cmd_msg, portMAX_DELAY);
        cmd = (AUDIO_PLAYER_CMD_T)cmd_msg.msg;

        /* Step two, Handle command */
        switch (cmd) {
            case AUDIO_PLAYER_CMD_PLAY:
            {
                //TODO only STOPPED state can accept PLAY CMD
                if (player->state == AUDIO_PLAYER_STATE_STOP) {
                    printf("[PLAYER] [CMD] PLAY. url is %s, cb is %p, arg is %p\r\n",
                            (char*)cmd_msg.arg1,
                            cmd_msg.arg2,
                            cmd_msg.arg3
                    );
                    player->url = (char*)cmd_msg.arg1;
                    player->callback = cmd_msg.arg2;
                    player->cb_arg = cmd_msg.arg3;
                    player->url_play_done = 0;
                    printf("[PLAYER] Will play from flash 0x%x, size is %u Bytes\r\n",
                            player->flash_addr,
                            player->flash_len
                    );
                    player->state = AUDIO_PLAYER_STATE_PALYING;
                    _callback_notify(player, AUDIO_PLAYER_EVENT_START);
                } else {
                    puts("[PLAYER] [STATE] Stop PLayer FIRST before another play\r\n");
                    if (cmd_msg.arg1) {
                        vPortFree(cmd_msg.arg1);
                    }
                }
            }
            break;
            case AUDIO_PLAYER_CMD_PAUSE:
            {
                player->state = AUDIO_PLAYER_STATE_PAUSE;
                puts("[PLAYER] [CMD] PAUSE\r\n");
                _callback_notify(player, AUDIO_PLAYER_EVENT_PAUSE);
            }
            break;
            case AUDIO_PLAYER_CMD_RESUME:
            {
                player->state = AUDIO_PLAYER_STATE_PALYING;
                puts("[PLAYER] [CMD] RESUME\r\n");
            }
            break;
            case AUDIO_PLAYER_CMD_STOP:
            {
                player->state = AUDIO_PLAYER_STATE_STOP;
                puts("[PLAYER] [CMD] STOP\r\n");
                _callback_notify(player, AUDIO_PLAYER_EVENT_STOP);
                _fifo_reset(player);
            }
            break;
            case AUDIO_PLAYER_CMD_FIFO_CREATE:
            {
                puts("[PLAYER] [CMD] FIFO Create\r\n");
                if (player->url) {
                    puts("Won't start when play URL\r\n");
                }
            }
            break;
            case AUDIO_PLAYER_CMD_FIFO_DESTORY:
            {
                puts("[PLAYER] [CMD] FIFO DESTORY\r\n");
                /*XXX FIXME reader here of xStreamBufferReset is audio_player, 
                 * we may pay attention to the write of player->rb_input
                 */
                _fifo_reset(player);//clear any data left in Ring Buffer
            }
            break;
            case AUDIO_PLAYER_CMD_FIFO_START:
            {
                puts("[PLAYER] [CMD] fifo start\r\n");
                if (player->url) {
                    puts("Won't start when play URL\r\n");
                } else {
                    _fifo_reset(player);
                    player->state = AUDIO_PLAYER_STATE_PALYING;
                    //_callback_notify(player, AUDIO_PLAYER_EVENT_START);
                }
            }
            break;
            case AUDIO_PLAYER_CMD_FIFO_STOP:
            {
                puts("[PLAYER] [CMD] fifo stop");
                if (cmd_msg.arg1) {
                    /*STOP now command*/
                    puts("now reset fifo...\r\n");
                    player->state = AUDIO_PLAYER_STATE_STOP;//block fifo_write API by setting state
                    //_callback_notify(player, AUDIO_PLAYER_EVENT_STOP);
                    _fifo_reset(player);
                } else {
                    /*STOP later command*/
                    player->state = AUDIO_PLAYER_STATE_STOPING;//block fifo_write API by setting state
                    puts("later. go to STOPING before fifo clear\r\n");
                    //_callback_notify(player, AUDIO_PLAYER_EVENT_STOP);
                }
            }
            break;
            case AUDIO_PLAYER_CMD_SAMPLE_RATE_CONFIG:
            {
                printf("[PLAYER] [CMD] sample rate CMD %d\r\n", (int)cmd_msg.arg1);
            }
            break;
            case AUDIO_PLAYER_CMD_RECORD_CONFIG:
            {
                printf("[PLAYER] [CMD] record config CMD:%s\r\n", cmd_msg.arg1 ? "enable" : "disable");
                _fifo_reset(player);
                if (cmd_msg.arg1) {
                    /*enable routine*/
                    rx_disable = 0;
                } else {
                    /*disable routine*/
                    rx_disable = 1;
                }
            }
            break;
            case AUDIO_PLAYER_SIGNAL_OUTPUT_FETCHED:
            {
                //printf("[PLAYER] [CMD] OUTPUT FETCHED, %p\r\n", player->mp3decoder);
                //printf("output audio media addr %p\r\n", media_data);
                if (AUDIO_PLAYER_STATE_PALYING == player->state) {
                    ret = xStreamBufferReceive(player->rb_input, media_data, buffer_len, 0);
                    if (ret < buffer_len) {
                        memset(media_data + ret, 0, buffer_len - ret);
                    }
                } else if (AUDIO_PLAYER_STATE_PAUSE == player->state) {
                    memset(media_data, 0, buffer_len);
                } else {
                    memset(media_data, 0, buffer_len);
                }
                csi_dcache_clean_range((uint32_t *)media_data, buffer_len);
            }
            break;
            case AUDIO_PLAYER_SIGNAL_INPUT_FETCHED:
            {
                //printf("input audio addr %p\r\n", record_data);
                csi_dcache_invalid_range((uint32_t *)record_data, record_len);
                ret = xStreamBufferSend(
                    player->rb_record,
                    record_data,
                    record_len,
                    0
                );
            }
            break;
            default:
            {
                /*nothing here*/
            }
        }
    }
}

static int audio_callback_tx(void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    player_cmd_t cmd;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    cmd.msg = (void*)AUDIO_PLAYER_SIGNAL_OUTPUT_FETCHED;

    media_data = audiodata;
    buffer_len = len;

    xQueueSendFromISR(_player->qe_cmd, &cmd, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken );
    }

    return 0;
}

static int audio_callback_rx(void *uerdata, uint8_t *audiodata, int len, int is_underrun)
{
    player_cmd_t cmd;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  
    cmd.msg = (void*)AUDIO_PLAYER_SIGNAL_INPUT_FETCHED;
    if (rx_disable) {
        /*nothing here*/
    } else {
        record_data = audiodata;
        record_len = len;
        xQueueSendFromISR(_player->qe_cmd, &cmd, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken) {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }

    return 0;
}

static int _player_init(audio_player_t *player)
{
    bl_audio_init(player->device);
    player->device->rx_enable = 1;
    player->device->rx_channel = LEFT_CHANNEL;
    player->device->tx_channel = LEFT_CHANNEL;
    bl_audio_tx_buffer_config(player->device, (void **)&tx_buffer, 8192);
    bl_audio_rx_buffer_config(player->device, (void **)&rx_buffer, 8192);

    bl_audio_samplerate_set(player->device, AUDIO_16_KHZ);
    bl_audio_tx_ready_config(player->device, audio_callback_tx, NULL);
    bl_audio_rx_ready_config(player->device, audio_callback_rx, NULL);
    bl_audio_start(player->device);
    /*need config audio or dma*/
    return 0;
}

static void inline _play_cmd_send(audio_player_t *player, player_cmd_t *cmd)
{
    xQueueSend(player->qe_cmd, cmd, portMAX_DELAY);
}

static void _player_play(audio_player_t *player, char *url, audio_player_event_cb callback, void *cb_arg)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_PLAY;
    cmd.arg1 = url;
    cmd.arg2 = callback;
    cmd.arg3 = cb_arg;

    _play_cmd_send(player, &cmd);
}

static void _player_pause(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_PAUSE;

    _play_cmd_send(player, &cmd);
}

static void _player_resume(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_RESUME;

    _play_cmd_send(player, &cmd);
}

static void _player_stop(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_STOP;
    _play_cmd_send(player, &cmd);
}

static void _player_fifo_create(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_FIFO_CREATE;

    _play_cmd_send(player, &cmd);
}

static void _player_fifo_start(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_FIFO_START;
    puts("will send fifo start\r\n");

    _play_cmd_send(player, &cmd);
    vTaskDelay(1);
}

static void _player_fifo_stop(audio_player_t *player, int stop_now)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_FIFO_STOP;
    cmd.arg1 = (void*)stop_now;
    puts("will send fifo stop\r\n");

    _play_cmd_send(player, &cmd);
}

static void _player_fifo_destory(audio_player_t *player)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_FIFO_DESTORY;

    _play_cmd_send(player, &cmd);
}

static int _player_fifo_write(audio_player_t *player, const void *data, int data_len, int isblock)
{
    int pos = 0;
    size_t ret;
    int consumed_bytes = 0;

    if (AUDIO_PLAYER_STATE_STOP == player->state ||
            AUDIO_PLAYER_STATE_STOPING == player->state) {
        puts("[AUDIO] [PLAYER] won't write on STOP state\r\n");
        return -1;
    }
#if 0
    printf("[AUDIO] fifo write want to write %d bytes\r\n", data_len);
#endif
    //FIXME proper value. 4096 or 1024? 
    if (isblock) {
        //consider break rb_input
        while (data_len > 0) {
            ret = xStreamBufferSend(
                player->rb_input,
                ((uint8_t*)data) + pos,
                data_len > 4096 ? 4096 : data_len,
                portMAX_DELAY
            );
            pos += ret;
            data_len -= ret;
            consumed_bytes += ret;
            if (AUDIO_PLAYER_STATE_STOP == player->state ||
                    AUDIO_PLAYER_STATE_STOPING == player->state) {
                /*break when fifo is stopped*/
                break;
            }
        }
    } else {
        //non-block mode
        while (data_len > 0) {
            ret = xStreamBufferSend(
                player->rb_input,
                ((uint8_t*)data) + pos,
                data_len > 1024 ? 1024 : data_len,
                0
            );
            //printf("%d Bytes written\r\n", ret);
            if (ret <= 0) {
                break;
            }
            pos += ret;
            data_len -= ret;
            consumed_bytes += ret;
            if (AUDIO_PLAYER_STATE_STOP == player->state ||
                    AUDIO_PLAYER_STATE_STOPING == player->state) {
                /*break when fifo is stopped*/
                break;
            }
        }
    }
#if 0
    printf("[AUDIO] [FIFO] %s want write %d bytes from %p, actual %d bytes written\r\n",
            isblock ? "block" : "non-block",
            data_len,
            data,
            consumed_bytes
    );
#endif
    return consumed_bytes;
}

void _player_set_samplerate(audio_player_t *player, int samplerate)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_SAMPLE_RATE_CONFIG;
    cmd.arg1 = (void*)samplerate;

    xQueueSend(player->qe_cmd, &cmd, portMAX_DELAY);
}

void _player_record_config(audio_player_t *player, int enable)
{
    player_cmd_t cmd;

    memset(&cmd, 0, sizeof(cmd));
    cmd.msg = (void*)AUDIO_PLAYER_CMD_RECORD_CONFIG;
    cmd.arg1 = (void*)enable;

    xQueueSend(player->qe_cmd, &cmd, portMAX_DELAY);
}

size_t _player_record_read(audio_player_t *player, void *buf, int len)
{
    size_t n, data_len = 0;
    while (data_len < len) {
        n = xStreamBufferReceive(player->rb_record, buf + data_len, len - data_len, portMAX_DELAY);
        data_len += n;
    }
    return data_len;
}

static int _player_create(void)
{
    audio_player_t *t_player;
 
    t_player = pvPortMalloc(sizeof(audio_player_t));
    BL_ASSERT_ERROR(t_player);
    memset(t_player, 0, sizeof(audio_player_t));
    _player = t_player;

    t_player->device = pvPortMalloc(sizeof(bl_audio_dev_t));
    BL_ASSERT_ERROR(t_player->device);
    memset(t_player->device, 0, sizeof(bl_audio_dev_t));
 


    //TODO check the memory usage
    t_player->qe_cmd = xQueueCreate(10, sizeof(player_cmd_t));
    t_player->rb_input = xStreamBufferCreate(8 * 1024, 16);//TODO opt with input stream type
    t_player->rb_record = xStreamBufferCreate(8 * 1024, 16);//TODO opt with input stream type
    xTaskCreate(_player_thread_entry, "player", 2048, NULL, TASK_PRIORITY_PLAYER, &(t_player->task));

    t_player->init = _player_init;
    t_player->play = _player_play;
    t_player->pause = _player_pause;
    t_player->resume = _player_resume;
    t_player->stop = _player_stop;
    t_player->fifo_create = _player_fifo_create;
    t_player->fifo_destory = _player_fifo_destory;
    t_player->fifo_start = _player_fifo_start;
    t_player->fifo_stop = _player_fifo_stop;
    t_player->fifo_write = _player_fifo_write;
    t_player->state = AUDIO_PLAYER_STATE_STOP;
    t_player->set_samplerate = _player_set_samplerate;
    t_player->record_config = _player_record_config;
    t_player->record_read = _player_record_read;

    BL_ASSERT_ERROR(t_player->qe_cmd);
    BL_ASSERT_ERROR(t_player->task);
    BL_ASSERT_ERROR(t_player->rb_input);
    BL_ASSERT_ERROR(t_player->rb_record);
    //BL_ASSERT_ERROR(t_player->rb_output);


    return 0;
}
