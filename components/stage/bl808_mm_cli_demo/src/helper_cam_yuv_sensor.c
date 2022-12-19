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

#include <bl_cam.h>
#include <core_rv64.h>
#include <helper_cam_yuv_sensor.h>

#define mainSTART_AP_TASK_PRIORITY  ( 15 )

void yuv_cam_cb(void)
{
    /*FIXME this api call in interrupt*/
    printf("frame done\r\n");
}

static void yuv_sensor_test(void *param)
{
    uint8_t *picture = NULL;
    uint32_t length = 0;

    if (0 != bl_cam_yuv_init()) {
        printf("bl cam init fail!\r\n");
        goto exit;
    }

    bl_cam_yuv_cb_register(yuv_cam_cb);

    while (1) {
        if (0 == bl_cam_rgb_frame_get(&picture,&length)) {
            printf("get rgb frame %p size %ubytes\r\n", picture, length);
            /*FIXME D-CACHE ENABLE need invalid*/
            bl_cam_yuv_frame_pop();
        }
        vTaskDelay(5);
    }
    bl_cam_yuv_deinit();
exit:
    vTaskDelete(NULL);
}

static void test_cam_mjpeg(void *param)
{
    uint8_t *picture = NULL;
    uint32_t length = 0;

    if (0 != bl_cam_mjpeg_init()) {
        printf("bl cam mjpeg fail!\r\n");
        goto exit;
    }
 
    while (1) {
        if (0 == bl_cam_mjpeg_get(&picture,&length)) {
            printf("get mjpeg frame %p size %ubytes\r\n", picture, length);
            /*FIXME D-CACHE ENABLE need invalid*/
            csi_dcache_invalid_range((void *)picture, length);
            bl_cam_mjpeg_pop();
        }
        vTaskDelay(5);
    }
    bl_cam_mjpeg_deinit();
exit:
    vTaskDelete(NULL);
}

void cmd_test_yuv_sensor(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(yuv_sensor_test, (char*)"yuv sensor", 512, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}

void cmd_cam_mjpeg_start(char *buf, int len, int argc, char **argv)
{
    if (argc == 1) {
        bl_cam_mjpeg_init();
    } else {
        bl_cam_mipi_mjpeg_init();
    }
}

void cmd_cam_mjpeg_test(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(test_cam_mjpeg, (char*)"mjpeg test", 512, NULL, mainSTART_AP_TASK_PRIORITY + 2, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "yuv_sensor_test", "yuv sensor test", cmd_test_yuv_sensor},
    { "cam_mjpeg_start", "yuv sensor mjpeg start", cmd_cam_mjpeg_start},
    { "cam_mjpeg_test", "yuv sensor mjpeg test", cmd_cam_mjpeg_test}
};

int helper_cam_yuv_sensor_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
