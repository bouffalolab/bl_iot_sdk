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
#include <semphr.h>
#include <queue.h>
#include <stream_buffer.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <cli.h>
#include <vfs.h>
#include <sys/fcntl.h>

#include <lwip/tcpip.h>
#include <lwip/ip_addr.h>
#include <lwip/netifapi.h>
#include <lwip/sockets.h>

#include <utils_log.h>
#include <utils_crc.h>
#include <mjpeg_booster.h>
#include <mjpeg_sw_buffer.h>
#include <helper_mjpeg.h>
#ifdef CPU_D0
#include <sample_common.h>
//#include <bl-osd-app.h>
#include <core_rv64.h>
#endif
// MJPEG configs
#define CONF_MJPEG_Q_MAX                      50
#define CONF_MJPEG_Q_MIN                      10
#define CONF_MJPEG_Q_UPGRADE_SIZE_THRESHOLD   (15*1024)
#define CONF_MJPEG_Q_DOWNGRADE_SIZE_THRESHOLD (55*1024)

#define UDP_ANNOUNCE_PORT       (8801)
#define UDP_ANNOUNCE_INTERVAL   (3000)

#define mainSTART_AP_TASK_PRIORITY  ( 15 )
#define FRAMES_FPS      20
#define VIDER_STREAM_ID 2
#define JPEG_STREAM_ID 2
#define H264_STREAM_ID 0
#define OSD_ENABLE      0

static void get_h264(void *param);
volatile int no_need_announce = 0;
static uint8_t udp_buf[1500];
static void configStartSenderTask(void *_)
{
    int ret;
    long unsigned int noblock = 1;
    //struct sockaddr_in sender_local_sockaddr, sock_broadcast;
    struct sockaddr_in sock_broadcast;
    int sender_socketfd;
    struct  {
        uint8_t version[4];
        uint8_t ip[4];
        uint8_t header[4];
        uint8_t mac[6];
    } announce_s;
    
    ret = mjpeg_sender_config(8800, 1234);
    if (ret < 0)
        printf("mjpeg_sender_config error\r\n");
    ret = mjpeg_sender_start();
    if (ret < 0)
        printf("mjpeg_sender_start error\r\n");
    //mjpeg_sw_fifo_config(CONF_MJPEG_Q_MAX, CONF_MJPEG_Q_MIN,
    //        CONF_MJPEG_Q_UPGRADE_SIZE_THRESHOLD, CONF_MJPEG_Q_DOWNGRADE_SIZE_THRESHOLD);

    puts("[MAIN] [ANNONCE] Sending location...\r\n");
    sender_socketfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#if 0
    memset(&sender_local_sockaddr, 0, sizeof(struct sockaddr_in));
    sender_local_sockaddr.sin_family = AF_INET;
    sender_local_sockaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    sender_local_sockaddr.sin_port = htons(UDP_ANNOUNCE_PORT);

    if (bind(sender_socketfd, (struct sockaddr*)&sender_local_sockaddr, sizeof(sender_local_sockaddr))) {
        while (1) {
            vTaskDelay(3000);
            puts("[MAIN] [ANNONCE] Failed when bind\r\n");
        }
    }
#endif
    memset(&sock_broadcast, 0, sizeof(struct sockaddr_in));
    sock_broadcast.sin_family = PF_INET;
    sock_broadcast.sin_port = htons(UDP_ANNOUNCE_PORT);
    sock_broadcast.sin_addr.s_addr = inet_addr("255.255.255.255");

    memset(&announce_s, 0, sizeof(announce_s));
    announce_s.version[0] = 0x01;
    announce_s.version[1] = 0x02;
    announce_s.version[2] = 0x03;
    announce_s.version[3] = 0x04;
    announce_s.ip[0] = 192;
    announce_s.ip[1] = 168;
    announce_s.ip[2] = 1;
    announce_s.ip[3] = 11;
    strcpy((char*)(&announce_s.header), "MAC");
    announce_s.mac[0] = 0x1b;
    announce_s.mac[1] = 0xb9;
    announce_s.mac[2] = 0x05;
    announce_s.mac[3] = 0x03;
    announce_s.mac[4] = 0x02;
    announce_s.mac[5] = 0x01;

    /*set recv function nonblock*/
    ioctl(sender_socketfd, FIONBIO, &noblock);
    while (1) {
        /* rcv may packet*/
        ret = recv(sender_socketfd, udp_buf, sizeof(udp_buf), 0);
        if (ret > 0) {
            printf("rcv data len %d\r\n", ret);
        }
 
        if (0 == no_need_announce) {
            printf("[ANNOUNCE]\r\n");
            lwip_sendto(sender_socketfd, &announce_s, sizeof(announce_s), 0, (struct sockaddr*)&sock_broadcast, sizeof(struct sockaddr_in));
        //} else {
        //    break;
        }
        vTaskDelay(UDP_ANNOUNCE_INTERVAL);
    }
    lwip_close(sender_socketfd);
    vTaskDelete(NULL);
}
#if 0
static int set_image_appendix_cb(uint64_t image_seq, uint8_t *appendix_data, int *appendix_data_len)
{
    if (image_seq & 1) {
       return -1; // 跳过奇数序号
    }
    memcpy(appendix_data, "12345678", 8);
    *appendix_data_len = 8;
    //*appendix_data_len = snprintf((char *)appendix_data, 32, "FAKE GSENSOR DATA %llu", image_seq);
    return 0;
}
#endif
SemaphoreHandle_t Stream_semaphore;
#ifdef CPU_D0
static int h264_judge_i_frame(uint8_t *frame_buf)
{
    int ret = 0;
    if (frame_buf[4] != 0x67) { /*FIXME: sure I-FRAME flag */
        ret = 1;
    }
    return ret;
}

QueueHandle_t h264_frame_queue = NULL;
StreamBufferHandle_t h264_data_stream;
static void save_h264(void)
{
    int ret = 0;
    uint8_t *ptr1, *ptr2;
    uint32_t len1, len2, h264_size = 0;
    static int drop_flag = 0;
    h264_frame_queue = xQueueCreate(1024, sizeof(uint32_t));
    if (NULL == h264_frame_queue) {
        printf("create h264 frame queue fail!\r\n");
        while(1);
    }

    h264_data_stream = xStreamBufferCreate(5 * 1024 * 1024, 0);
    if (NULL == h264_frame_queue) {
        printf("create h264 data buffer fail!\r\n");
        while(1);
    }
    while (1) {
        len2 = 0;
        ptr2 = NULL;
        ret = sample_get_h264_frame(&ptr1, &len1, &ptr2, &len2, 0);
        if (!ret) {
            if (drop_flag) {
                csi_dcache_invalid_range(ptr1, len1);
                if (h264_judge_i_frame(ptr1)) {
                    continue;
                } else {
                    drop_flag = 0; /* GET next I-frame maybe save*/
                }
            }
            h264_size = len1 + len2;
            if (uxQueueSpacesAvailable(h264_frame_queue)) {
                if (h264_size <= xStreamBufferSpacesAvailable(h264_data_stream)) {
                    csi_dcache_invalid_range(ptr1, len1);
                    xStreamBufferSend(h264_data_stream, ptr1, len1, 0);
                    if (len2) {
                        csi_dcache_invalid_range(ptr2, len2);
                        xStreamBufferSend(h264_data_stream, ptr2, len2, 0);
                    }
                    xQueueSend(h264_frame_queue, &h264_size, 0);
                } else {
                    drop_flag = 1; /*can not save h264 frame so drop next data util next I frame*/
                }
            } else {
                drop_flag = 1; /*can not save h264 frame so drop next data util next I frame*/
            }
        }
    }

}
#endif

static void cameraTask(void *pvParameters)
{
#ifdef CPU_D0
    int ret = 0;
#endif
    int stream_id = *(int *)pvParameters;
    //uint16_t frame_count = 0;
    //uint32_t tick_now, tick_last = 0;
    Stream_semaphore = xSemaphoreCreateBinary();
    if (NULL == Stream_semaphore) {
        printf("create semaphore fail\r\n");
        vTaskDelete(NULL);
    }

    if (mjpeg_sw_fifo_init(1920, 1080)) {
        printf("[SENDER] mjpeg_sw_fifo_init failed\r\n");
        while (1) {
            /* empty */;
        }
    }

    /*cam is ready, now start task*/
    xTaskCreate(mjpeg_sender_task, "sender", 1024, &stream_id, mainSTART_AP_TASK_PRIORITY + 1, NULL);
    xTaskCreate(mjpeg_sender_ctl_task, "senderctl", 512, NULL, mainSTART_AP_TASK_PRIORITY + 2, NULL);
    xTaskCreate(configStartSenderTask, "foo", 256, NULL, mainSTART_AP_TASK_PRIORITY, NULL);
    vTaskDelay(50);
    //mjpeg_set_per_image_appendix_callback_register(set_image_appendix_cb);

    //tick_last = xTaskGetTickCount();
    while (1) {
        if (Stream_semaphore != NULL) {
            if (xSemaphoreTake(Stream_semaphore, portMAX_DELAY) == pdTRUE) {
                if (1 == no_need_announce) {
#ifdef CPU_D0
                    if (stream_id == JPEG_STREAM_ID) {
                        ret = sample_system_mjpeg_init();
#if OSD_ENABLE
                    bl_osd_init();
                    vTaskDelay(100);
#endif
                    } else if (stream_id == H264_STREAM_ID) {
                        ret = sample_system_init();
                    } else {
                        printf("wrong stream id %d\r\n", stream_id);
                        vTaskDelete(NULL);
                    }

                    if (ret) {
                        printf("Sample system init fail!!\r\n");
                        vTaskDelete(NULL);
                    }

                    /* Wait spp stable, then start mjpeg encoder */

                    vTaskDelay(1000);

                    ret = sample_encoder_init();
                    if (ret) {
                        printf("Video codec init fail!!\r\n");
                    }
                    if (stream_id == JPEG_STREAM_ID) {
                        sample_set_jpeg_quality(JPEG_STREAM_ID, 50);
                    }
                    vTaskDelay(5); 
                    printf("stream start\r\n");
                    sample_start_stream(stream_id);
                    vSemaphoreDelete(Stream_semaphore);
                    Stream_semaphore = NULL;
                    if(stream_id == H264_STREAM_ID) {
                        xTaskCreate(get_h264, (char*)"h264", 1024, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
                        //save_h264();
                    }
#else
                    vSemaphoreDelete(Stream_semaphore);
                    Stream_semaphore = NULL;
#endif
                }
            }
        } else {
            //printf("cam delay\r\n");
            vTaskDelay(1000);
        }
#if 0
        tick_now = xTaskGetTickCount();
        if (((int32_t)tick_now) - ((int32_t)tick_last) > 10*1000) {
            tick_last = xTaskGetTickCount();
            /*debug every 30*/
            //printf("[MAIN] FPS is %u\r\n", 0);
            //printf("[MAIN] FPS is %u\r\n", (*(volatile uint16_t*)0x40016028 - frame_count)/10);
           // frame_count = *(volatile uint16_t*)0x40016028;
        }
        vTaskDelay(pdMS_TO_TICKS(50 / 2));
#endif 
    }
}

static void cmd_mjpeg_start(char *buf, int len, int argc, char **argv)
{
    static int stream_id = JPEG_STREAM_ID;
    puts("-------------------------->>> Starting MJPEG tasks\r\n");
    if (argc == 2) {
        if (0 == strcmp(argv[1], "h264")) {
            stream_id = H264_STREAM_ID;
        } else if (strcmp(argv[1], "mjpeg")) {
            printf("input param error\r\n");
        }
    }
    xTaskCreate(cameraTask, (char*)"camera", 512, &stream_id, mainSTART_AP_TASK_PRIORITY, NULL);
}
#ifdef CPU_D0
static void get_jpeg(void *param)
{
    int ret = 0;
    MMEncoderStream stream_info;
    uint8_t *img_buf = (uint8_t *)0x52000000;
    uint32_t tot_size = 0;
    ret = MM_Encoder_GetStream(2, &stream_info);
    csi_dcache_invalid_range((uint64_t *)stream_info.frame_start_addr, stream_info.frame_size);
    memcpy(img_buf + tot_size, stream_info.frame_start_addr, stream_info.frame_size);
    tot_size += stream_info.frame_size;
    printf ("first addr %p size %d\r\n", stream_info.frame_start_addr, stream_info.frame_size);
    csi_dcache_clean_range((uint64_t *)img_buf, tot_size);
    sample_close_stream(2);
    printf("get jpeg done  start addr %p  end arrd %p size %08x\r\n", img_buf, img_buf + tot_size, tot_size);
    vTaskDelete(NULL);
}

static void cmd_test_jpeg(char *buf, int len, int argc, char **argv)
{
    int ret = 0;
    ret = sample_system_mjpeg_init();
    if (ret) {
        printf("Sample system init fail!!\r\n");
    }

    /* Wait spp stable, then start mjpeg encoder */
    vTaskDelay(1000);

    ret = sample_encoder_init();
    if (ret) {
        printf("Video codec init fail!!\r\n");
    }
    sample_set_jpeg_quality(JPEG_STREAM_ID, 50);
    vTaskDelay(500);
    printf("stream start\r\n");
    sample_start_stream(2);

    //xTaskCreate(get_jpeg, (char*)"jpeg", 1024, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}

static void get_h264(void *param)
{
    int ret = 0, drop_flag = 0;
    MMEncoderStream stream_info;
    uint8_t *img_buf = (uint8_t *)FRAME_BUF_ADDR;
    uint32_t tot_size = 0;
    uint64_t count = 0;
    frame_head_t *h264_frame = NULL;
    memset(img_buf, 0, FRAME_BUF_SIZE);
    csi_dcache_clean_range((uint64_t *)img_buf, FRAME_BUF_SIZE);
    while (1) {
        ret = MM_Encoder_GetStream(0, &stream_info);
        if (!ret) {
            csi_dcache_invalid_range((uint64_t *)stream_info.frame_start_addr, stream_info.frame_size);
            if (drop_flag) {
                if (h264_judge_i_frame(stream_info.frame_start_addr)) {
                    continue;
                } else {
                    drop_flag = 0;
                }
            }
                
            h264_frame = (frame_head_t *)(img_buf + ((count & (FRAME_NUM - 1)) * PER_FRAME_SIZE));
            csi_dcache_invalid_range((uint64_t *)h264_frame, sizeof(frame_head_t));
            if (0 == h264_frame->used_flag) {
                h264_frame->seq = count;
                h264_frame->length = stream_info.frame_size + stream_info.frame_sec_size;
                memcpy(h264_frame->data, stream_info.frame_start_addr, stream_info.frame_size);
                if (stream_info.frame_sec_size) {
                    csi_dcache_invalid_range((uint64_t *)stream_info.frame_sec_addr, stream_info.frame_sec_size);
                    memcpy(h264_frame->data + stream_info.frame_size, stream_info.frame_sec_addr, stream_info.frame_sec_size);
                }
                h264_frame->crc_val = utils_crc32(h264_frame->data, h264_frame->length);
                h264_frame->used_flag = USED_MAGIC_FLAG;
                csi_dcache_clean_range((uint64_t *)h264_frame, sizeof(frame_head_t) + h264_frame->length);
                //printf("h264_send buf %p len%u\r\n", h264_frame, h264_frame->length);
                count++;
            } else if (USED_MAGIC_FLAG == h264_frame->used_flag) {
                drop_flag = 1;
                printf("buffer full h264 frame drop fail\r\n");
            } else {
                printf("h264 frame buffer error!\r\n");
                while (1);
            }
        }
    }
}

static void cmd_test_h264(char *buf, int len, int argc, char **argv)
{
    int ret = 0;
    ret = sample_system_init();
    if (ret) {
        printf("Sample system init fail!!\r\n");
    }

    /* Wait spp stable, then start mjpeg encoder */
    vTaskDelay(1000);

    ret = sample_encoder_init();
    if (ret) {
        printf("Video codec init fail!!\r\n");
    }
    vTaskDelay(5);
    printf("stream start\r\n");
    sample_start_stream(0);

    xTaskCreate(get_h264, (char*)"h264", 1024, NULL, mainSTART_AP_TASK_PRIORITY + 3, NULL);
}
#endif

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "mjpeg_start", "start mjpeg tasks", cmd_mjpeg_start },
#ifdef CPU_D0
    { "h264_start", "start h264 tasks", cmd_test_h264 },
    { "jpeg_start", "start h264 tasks", cmd_test_jpeg }
#endif
};

int helper_mjpeg_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}
