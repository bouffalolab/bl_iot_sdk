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
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>

#include <vfs_err.h>
#include <vfs_register.h>
#include <vfs.h>
#include <cli.h>
#include <bl_uart.h>
#include <hal_uart.h>
#include <device/vfs_uart.h>
#include <utils_log.h>
#include <bl602_uart.h>
#include "demo.h"

void log_step(const char *step[2])
{
    printf("%s   %s\r\n", step[0], step[1]);
}

void cmd_uart_flush(char *buf, int len, int argc, char **argv)
{
    int fd;
    const char *pbuf1 = "1>0123456789abcdefghijklmnopqrstuvwxyz>0123456789abcdefghijklmnopqrstuvwxyz>0123456789abcdefghijklmnopqrstuvwxyz>2";
    const char *pbuf2 = "3<0123456789abcdefghijklmnopqrstuvwxyz<0123456789abcdefghijklmnopqrstuvwxyz<0123456789abcdefghijklmnopqrstuvwxyz<4";


    fd = aos_open("/dev/ttyS1", 0);
    if (fd < 0) {
        printf("open ttyS1 error\r\n");
        return;
    }
    while (1)
    {
        aos_write(fd, pbuf1, strlen(pbuf1));
        while ( 1 == UART_GetTxBusBusyStatus(1)) {
        }
        //bl_uart_flush(1);
        aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
        aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 4800);
        vTaskDelay(2000);
        aos_write(fd, pbuf2, strlen(pbuf2));
        aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
        aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 4800);
        vTaskDelay(2000);
   }
}

void bluart_block_entry(void *arg)
{
    int length;
    uint8_t buf_recv[50];
    const char *name = arg;
    uint32_t count = 0;

    int fd = aos_open(name, 0);
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
    aos_ioctl(fd, IOCTL_UART_IOC_READ_BLOCK, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        length = aos_read(fd, buf_recv, sizeof(buf_recv));
        if (length > 0) {
            log_info("%s name.length = %d:\r\n", name, length);
            aos_write(fd, buf_recv, length);
        }
        vTaskDelay(500);
        log_info("test.\r\n");
        count++;

        if (count == 5) {
            log_info("set noblock.\r\n");
            aos_ioctl(fd, IOCTL_UART_IOC_READ_NOBLOCK, 0);
        }

        if (count == 10) {
            log_info("set block.\r\n");
            aos_ioctl(fd, IOCTL_UART_IOC_READ_BLOCK, 0);
        }
    }
}

void bluart_ioctl1_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        //log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = 5000;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITENDBYTE_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void bluart_ioctl2_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        //log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = 0;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void bluart_ioctl3_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = AOS_WAIT_FOREVER;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void cmd_uart_ioctl(char *buf, int len, int argc, char **argv)
{
    if (argc != 2) {
        log_error("arg error.\r\n");
        return;
    }
    if (0 == memcmp(argv[1], "1", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl1_entry, "/dev/ttyS1", 2048);
    } else if (0 == memcmp(argv[1], "2", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl2_entry, "/dev/ttyS1", 2048);
    } else if (0 == memcmp(argv[1], "3", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl3_entry, "/dev/ttyS1", 2048);
    }
}

void cmd_uart_block(char *buf, int len, int argc, char **argv)
{
    //aos_task_new("uart0_block", bluart_block_entry, "/dev/ttyS0", 2048);
    aos_task_new("uart1_block", bluart_block_entry, "/dev/ttyS1", 2048);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "uartflush", "uart flush", cmd_uart_flush},
    { "uartblock", "uart block", cmd_uart_block},
    { "uartioctl", "uart io control", cmd_uart_ioctl},
};

int uart_ctl_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
