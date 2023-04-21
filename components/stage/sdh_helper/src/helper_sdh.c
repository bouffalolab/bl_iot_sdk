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
#include <sys/fcntl.h>

#include <FreeRTOS.h>
#include <task.h>

#include <vfs.h>
#include <cli.h>
#include <aos/kernel.h>
#include <helper_sdh.h>

#include "utils_log.h"
#include <bl_usb_cam.h>

static void fatfs_test_cmd(char *buf, int len, int argc, char **argv)
{
    aos_dir_t * dp;
    int fd_txt, counter = 0, ret;
    char path_txt[32];
    char *txt_buffer;

    dp = (aos_dir_t *)aos_opendir("/sdcard");
    if (dp) {
        aos_dirent_t *out_dirent;
        counter = 0;
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                break;
            }
            printf("file name is %s\r\n", out_dirent->d_name);
            counter++;
        }
        aos_closedir(dp);
    } else {
        printf("dp is NULL, when dump sdcard\r\n");
    }

    snprintf(path_txt, sizeof(path_txt), "/sdcard/bl60x_%d.txt\r\n", counter);
    printf("Tring to create txt file: %s\r\n", path_txt);
    fd_txt = aos_open(path_txt, O_RDWR | O_CREAT | O_TRUNC);
    if (fd_txt >= 0) {
        aos_write(fd_txt, path_txt, strlen(path_txt));
        aos_close(fd_txt);
    }

    printf("dumping again....\r\n");

    dp = (aos_dir_t *)aos_opendir("/sdcard");
    if (dp) {
        aos_dirent_t *out_dirent;
        counter = 0;
        while(1) {
            out_dirent = (aos_dirent_t *)aos_readdir(dp);
            if (out_dirent == NULL) {
                break;
            }
            printf("file name is %s\r\n", out_dirent->d_name);
            counter++;
        }
        aos_closedir(dp);
    } else {
        printf("dp is NULL, when dump sdcard\r\n");
    }

    fd_txt = aos_open(path_txt, 0);
    if (fd_txt >= 0) {
        txt_buffer = pvPortMalloc(129);
        if (txt_buffer) {
            ret = aos_read(fd_txt, txt_buffer, 128);//one byte left for string tail
            if (ret > 0 && ret < 128) {
                printf("Read %d bytes from file\r\n", ret);
                txt_buffer[ret] = '\0';
                printf("Content is:\r\n %s\r\n", txt_buffer);
            } else {
                printf("Error when read file content, ret is %d\r\n", ret);
                goto error_out;
            }
        } else {
            printf("No mem when alloc for txt buffer");
            goto error_out;
        }
    }

error_out:
    return;
}

void cmd_sdh_wtest(char *buf, int len, int argc, char **argv)
{
    int fd = -1;
    int i;
    char *test_buf = 0;

    test_buf = pvPortMalloc(4096);

    if (test_buf == 0) {
        log_error("SDH buf error.\r\n");
        return;
    }

    log_info("sdh_wtest start.\r\n");
    memset(test_buf, 0x55, 4096);
    fd = aos_open("/sdcard/wtest.txt", O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        log_error("open err.\r\n");
        return;
    }

    for(i = 0; i < 100; i++) {
        aos_write(fd, test_buf, 4096);
        aos_msleep(10);
    }

    aos_close(fd);
    vPortFree(test_buf);

    log_info("sdh_wtest stop.\r\n");
}

void cmd_sdh_w100m(char *buf, int len, int argc, char **argv)
{
    int fd = -1;
    char *test_buf = NULL;
    uint32_t i, time_start, time_end;

    test_buf = pvPortMalloc(1024 * 64);

    if (test_buf == 0) {
        log_error("SDH buf error.\r\n");
        return;
    }
    memset(test_buf, 0x55, 1024 * 64);
    log_info("MALLOC test_buf = %p\r\n", test_buf);

    {
        /* 64k */
        fd = aos_open("/sdcard/w64k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 16*100; i++) {
            aos_write(fd, test_buf, 64*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 64k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 32k */
        fd = aos_open("/sdcard/w32k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 32*100; i++) {
            aos_write(fd, test_buf, 32*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 32k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 16k */
        fd = aos_open("/sdcard/w16k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 64*100; i++) {
            aos_write(fd, test_buf, 16*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 16k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    {
        /* 8k */
        fd = aos_open("/sdcard/w8k.txt", O_RDWR | O_CREAT | O_TRUNC);
        if (fd < 0) {
            log_error("open err.\r\n");
            return;
        }
        log_info("start write.\r\n");
        time_start = xTaskGetTickCount();
        for(i = 0; i < 128*100; i++) {
            aos_write(fd, test_buf, 8*1024);
        }
        time_end = xTaskGetTickCount();
        log_info("end write.\r\n");
        log_info("unit 8k, 100M Byte use %ld ms\r\n", (time_end - time_start));
        aos_close(fd);
    }

    vPortFree(test_buf);
}

#define FATFS_TEST_FILE_NAME     "/sdcard/test_file.txt"
#define SDU_DATA_CHECK 1
#define TEST_BUFF_SIZE (128 * 1024)

static const char test_data[] =
    "I've been reading books of old \r\n\
    The legends and the myths \r\n\
    Achilles and his gold \r\n\
    Hercules and his gifts \r\n\
    Spiderman's control \r\n\
    And Batman with his fists\r\n\
    And clearly I don't see myself upon that list\r\n\
    But she said, where'd you wanna go?\r\n\
    How much you wanna risk?\r\n\
    I'm not looking for somebody\r\n\
    With some superhuman gifts\r\n\
    Some superhero\r\n\
    Some fairytale bliss\r\n\
    Just something I can turn to\r\n\
    Somebody I can kiss\r\n\
    I want something just like this\r\n\r\n";

static void fatfs_speed_test(char *buf, int len, int argc, char **argv)
{
    unsigned int time_node, i, j;
    int fd_file;
    int ret;
    uint8_t *rw_buffer = NULL;
    void *rw_mem = NULL;

#if SDU_DATA_CHECK
    uint8_t *check_buffer= NULL;
    void *check_mem = NULL;
#endif

    rw_mem = pvPortMalloc(TEST_BUFF_SIZE + 8);
    if(rw_mem == NULL){
        printf("fatfs test no memory\r\n");
        goto out;
    }
    /* Must be 8 bytes aligned */
    rw_buffer = rw_mem + (8 - (uintptr_t)rw_mem % 8);

#if SDU_DATA_CHECK
    check_mem = pvPortMalloc(TEST_BUFF_SIZE + 8);
    if(check_mem == NULL){
        printf("fatfs test no memory\r\n");
        goto out;
    }
    /* Must be 8 bytes aligned */
    check_buffer = check_mem + (8 - (uintptr_t)check_mem % 8);
#endif

    /* full test data to buff */
    for (uint32_t size = 0; size < (TEST_BUFF_SIZE - sizeof(test_data)); size += sizeof(test_data)) {
        memcpy(&rw_buffer[size], test_data, sizeof(test_data));
    }
#if SDU_DATA_CHECK
        memcpy(check_buffer, rw_buffer, TEST_BUFF_SIZE);
#endif

    /* write test */
    printf("\r\n******************** be about to write test... **********************\r\n");
    fd_file = aos_open(FATFS_TEST_FILE_NAME, O_TRUNC | O_RDWR);
    if (fd_file >= 0) {
        time_node = (uint32_t)xTaskGetTickCount();

        /*write into file*/
        for (i = 0; i < 1024; i++) {
            ret = aos_write(fd_file, rw_buffer, TEST_BUFF_SIZE);
            if (ret != TEST_BUFF_SIZE) {
                goto out;
            }
        }

        /* close file */
        ret= aos_close(fd_file);
        /* get time */
        time_node = (uint32_t)xTaskGetTickCount() - time_node;

        if (ret >= 0) {
            printf("Write Test Succeed! \r\n");
            printf("Single data size:%d Byte, Write the number:%d, Total size:%d KB\r\n", TEST_BUFF_SIZE, i, TEST_BUFF_SIZE * i >> 10);
            printf("Time:%dms, Write Speed:%d KB/s \r\n", time_node, ((TEST_BUFF_SIZE * i) >> 10) * 1000 / time_node);
        } else {
            printf("Fail to write files(%d) num:%d\n", ret, i);
            goto out;
        }
    } else {
        printf("Fail to open or create files.\r\n");
        goto out;
    }

    memset(rw_buffer, 0xFF, TEST_BUFF_SIZE);

    /* read test */
    printf("\r\n******************** be about to read test... **********************\r\n");
    fd_file = aos_open(FATFS_TEST_FILE_NAME, O_RDONLY);
    if (fd_file > 0) {
        time_node = (uint32_t)xTaskGetTickCount();

        for (i = 0; i < 1024; i++) {
            ret = aos_read(fd_file, rw_buffer, TEST_BUFF_SIZE);
            if (ret != TEST_BUFF_SIZE) {
                break;
            }
        }
        /* close file */
        ret= aos_close(fd_file);
        /* get time */
        time_node = (uint32_t)xTaskGetTickCount() - time_node;

        if (ret >= 0) {
            printf("Read Test Succeed! \r\n");
            printf("Single data size:%dByte, Read the number:%d, Total size:%d KB\r\n", TEST_BUFF_SIZE, i, TEST_BUFF_SIZE * i >> 10);
            printf("Time:%dms, Read Speed:%d KB/s \r\n", time_node, ((TEST_BUFF_SIZE * i) >> 10) * 1000 / time_node);
        } else {
            printf("Fail to read file: (%d), num:%d\n", ret, i);
            goto out;
        }
    } else {
        printf("Fail to open files.\r\n");
        goto out;
    }

    memset(rw_buffer, 0xFF, TEST_BUFF_SIZE);

    /* check data */
#if SDU_DATA_CHECK
    printf("\r\n******************** be about to check test... **********************\r\n");
    fd_file = aos_open(FATFS_TEST_FILE_NAME, O_RDONLY);
    if (fd_file > 0) {

        for (i = 0; i < 1024; i++) {
            ret = aos_read(fd_file, rw_buffer, TEST_BUFF_SIZE);
            if (ret != TEST_BUFF_SIZE) {
                break;
            }
            for (j = 0; j < TEST_BUFF_SIZE; j++) {
                if (rw_buffer[j] != check_buffer[j]) {
                    printf("data err :0x%s/0x%s\r\n", &rw_buffer[j-10], &check_buffer[j-10]);
                    break;
                }
            }
            if (j < TEST_BUFF_SIZE) {
                break;
            }
        }
        /* close file */
        ret= aos_close(fd_file);

        if (ret >= 0) {
            if (i < 1024 || j < TEST_BUFF_SIZE) {
                printf("Check Test Error! \r\n");
                printf("Data Error!  Num:%d/1024, Byte:%d/%d", i, j, TEST_BUFF_SIZE);
            } else {
                printf("Check Test Succeed! \r\n");
                printf("All Data Is Good! \r\n");
            }

        } else {
            printf("Fail to read file: (%d), num:%d\n", ret, i);
            goto out;
        }
    } else {
        printf("Fail to open files.\r\n");
        goto out;
    }
#endif

out:
    if(rw_mem != NULL){
        vPortFree(rw_mem);
    }
#if SDU_DATA_CHECK
    if(check_mem != NULL){
        vPortFree(check_mem);
    }
#endif

    printf("fatfs test end\r\n");
}


// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"test_sdh", "test SDH based on fatfs", fatfs_test_cmd},
    {"sdh_wtest", "sdh_wtest", cmd_sdh_wtest},
    {"sdh_w100m", "cmd_sdh_w100m", cmd_sdh_w100m},
    {"fatfs_speed_test", "fatfs_speed_test", fatfs_speed_test},
};

int helper_sdh_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));

    return 0;
}
