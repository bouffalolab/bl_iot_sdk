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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>
#include <vfs.h>

#include <audio_player.h>
#include <helper_audio.h>
#include <test_audio_16k_pcm.h>
#define mainSTART_AP_TASK_PRIORITY      10 
#define record_len                      4 * 1024
static void audio_record_task(void *par)
{
    audio_player_t *player = NULL;
    uint8_t *record_buf = NULL;

    audio_player_get(&player);

    if (player == NULL) {
        printf("player no init \r\n");
        goto exit;
    }

    record_buf = pvPortMalloc(record_len);
    if (NULL == record_buf) {
        printf("malloc record buf fail!\r\n");
        goto exit;
    }

    while (1) {
        player->record_read(player, record_buf, record_len); //read_block
    }
    vPortFree(record_buf);

exit:
    vTaskDelete(NULL);
}

static void audio_play_task(void *par)
{
    audio_player_t *player = NULL;
    size_t ret, remain_len, total_size, w_len;
    audio_player_get(&player);

    if (player == NULL) {
        printf("player no init \r\n");
        goto exit;
    }

    player->fifo_start(player);
    remain_len = sizeof(wa_mono_16k_pcm);
    total_size = remain_len;
    while (1) {
        w_len = remain_len > 4096 ? 4096 : remain_len; /* once write len any value is ok */
        ret = player->fifo_write(player, wa_mono_16k_pcm + total_size - remain_len, w_len, 1); //write block
        remain_len -= ret;
        if (remain_len == 0) {
            remain_len = total_size;
        }
    }
exit:
    vTaskDelete(NULL);
}

static void cmd_test_audio_init(char *buf, int len, int argc, char **argv)
{
    audio_player_t *player = NULL;
    audio_player_init();

    audio_player_get(&player);

    if (player != NULL) {
        player->init(player);
    } else {
        printf("player init fail!\r\n");
    }
}

static void cmd_test_audio_record(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(audio_record_task, (char*)"audio record", 512, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}

static void cmd_test_audio_play(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(audio_play_task, (char*)"audio play", 512, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "audio_init", "audio init", cmd_test_audio_init},
    { "audio_record", "audio record", cmd_test_audio_record},
    { "audio_play", "audio play", cmd_test_audio_play}
};

int helper_audio_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
