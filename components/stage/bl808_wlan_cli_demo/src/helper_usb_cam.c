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
#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>
#include <vfs.h>
#include <utils_log.h>
#include <bl_usb_cam.h>
#include <sys/fcntl.h>

static void usb_cam_test(void *param)
{
    if (bl_usb_cam_init()) {
        printf("init usb cam fail\r\n");
        goto exit;
    }

    while (1) {
        bl_usb_cam_transfer();
        vTaskDelay(5);
    }
exit:
    vTaskDelete(NULL);
}

void cmd_test_usb_cam(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(usb_cam_test, (char*)"yuv sensor", 512, NULL, 10, NULL);
}

static int counter = 0; 
static void sdh_dump_cam_task(void *par)
{
    int fd = -1;
    char path_txt[32];
    uint8_t *pic_buf = NULL;
    size_t img_len = 0;

    pic_buf = pvPortMalloc(100 * 1024);

    if (pic_buf == NULL) {
        goto exit;
    }

    if (imgbuf_queue == NULL) {
        imgbuf_queue = xQueueCreate(1, sizeof(uint8_t *));
    }

    if (imglen_queue == NULL) {
        imglen_queue = xQueueCreate(1, sizeof(size_t));
    }

    xQueueSend(imgbuf_queue, &pic_buf, 0);
    while (1) {
        xQueueReceive(imglen_queue, &img_len, portMAX_DELAY);
        counter++;
        snprintf(path_txt, sizeof(path_txt), "/sdcard/bl808_%d.jpeg\r\n", counter);
        log_info("dump cnt:%d cam path:%s\r\n",counter, path_txt);
        log_info("dump cam start...\r\n");

        fd = aos_open(path_txt, O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            goto exit;
        }

        if (fd >= 0) {
            log_info("dump cam write %d...\r\n", img_len);
            aos_write(fd, pic_buf, (img_len));
            aos_close(fd);
            aos_msleep(10);
            log_info("dump done.\r\n");
            break;
        }

    }

exit:

    if (imgbuf_queue) {
        vQueueDelete(imgbuf_queue);
        imgbuf_queue = NULL;
    }

    if (imglen_queue) {
        vQueueDelete(imglen_queue);
        imglen_queue = NULL;
    }
    vPortFree(pic_buf);
    vTaskDelete(NULL);
}

static void sdh_dump_cam_test(char *buf, int len, int argc, char **argv)
{
    xTaskCreate(sdh_dump_cam_task, (char*)"dump_jpeg_sdcard", 512, NULL, 10, NULL);
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"usb_cam", "usb cam test", cmd_test_usb_cam},
    {"sdh_dump_cam", "sdh_dump_cam_test", sdh_dump_cam_test}
};

int helper_usb_cam_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
