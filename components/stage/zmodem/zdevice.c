/*
 * File      : zdevice.c
 * the implemention of zmodem protocol.
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 */

#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>
#include "zdef.h"
#include "zmodem_cli.h"


uint32_t Line_left  = 0;          /* left number of data in the read line buffer*/
uint32_t Left_sizes = 0;          /* left file sizes */
uint32_t Baudrate   = BITRATE;    /* console baudrate */

static int zdevice_fd = 0;

uint32_t get_device_baud(void)
{
    return(Baudrate);
}

uint32_t get_sys_time(void)
{
    return(0L);
}

void zsend_byte(uint16_t ch)
{
    aos_write(zdevice_fd, &ch, 1);

    return;
}

void zsend_line(uint16_t c)
{
    uint16_t ch;

    ch = (c & 0377);
    aos_write(zdevice_fd, &ch, 1);

    return;
}

int16_t zread_line(uint16_t timeout)
{
    char *str;
    static char buf[10];

    Line_left = 0;
    timeout/=5;
    while (1)
    {
        Line_left = aos_read(zdevice_fd, buf, 1);
        if (Line_left)
        {
             Line_left = Line_left;
             str = buf;
             break;
        }
    }
    if (Line_left < 1) return TIMEOUT;
    Line_left -=1;

    return (*str++ & 0377);
}

/*
 * send a string to the modem, processing for \336 (sleep 1 sec)
 *   and \335 (break signal)
 */
void zsend_break(char *cmd)
{

    while (*cmd++)
    {
        switch (*cmd)
        {
        case '\336':
             continue;
        case '\335':
             vTaskDelay(RT_TICK_PER_SECOND);
             continue;
        default:
             zsend_line(*cmd);
             break;
        }
    }
}
/* send cancel string to get the other end to shut up */
void zsend_can(void)
{
    static char cmd[] = {24,24,24,24,24,24,24,24,24,24,0};

    zsend_break(cmd);
    printf("\x0d");
    Line_left=0;           /* clear Line_left */

    return;
}

int zdevice_init()
{
    if (zdevice_fd <= 0) {
        zdevice_fd = aos_cli_device_fd_get();
    }
    if (zdevice_fd > 0) {
        aos_cancel_poll_read_fd(zdevice_fd, aos_cli_event_cb_read_get(), (void *)0x12345678);
        return 0;
    } else {
        return -1;
    }
}

void zdevice_uninit()
{
    if (zdevice_fd <= 0) {
        zdevice_fd = aos_cli_device_fd_get();
    }
    if (zdevice_fd > 0) {
        aos_poll_read_fd(zdevice_fd, aos_cli_event_cb_read_get(), (void*)0x12345678);
    }
}
/* end of zdevice.c */
