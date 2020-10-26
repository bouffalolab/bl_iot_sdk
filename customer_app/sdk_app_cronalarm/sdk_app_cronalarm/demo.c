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
#include <stdint.h>
#include <string.h>

#include <looprt.h>
#include <loopset.h>
#include <sntp.h>
#include <bl_sys_time.h>
#include <fdt.h>

#include <cronalarms.h>
#include <loopset_cronalarm.h>
#include <time.h>
#include <cli.h>
#include <utils_time.h>
#include <stdlib.h>


static void Repeats(void)
{
    printf("every minutes 1-10s  every seconds trigger once \r\n");
    return;
}

static void Repeats2(void)
{
    printf("every 2 seconds trigger \r\n");
    return;
}

static void OnceOnly(void)
{
    printf("after 30s only trigger once \r\n");
    return;
}

static void test_min01(void)
{
    printf("now time 9:44:30 \r\n");
    return;
}


static void test_min02(void)
{
    printf("run every 1m   \r\n");
    return;
}

static void test_min03(void)
{
    printf("3 minutes 15s run once \r\n");
    return;
}

static void test_hour01(void)
{
    printf("run every 1 hour \r\n");
    return;
}

static void test_hour02(void)
{
    printf("run every 4 hour 15:15 \r\n");
    return;
}


static void test_day01(void)
{
    printf("run every day 00:00:00 \r\n");
    return;
}

static void test_day02(void)
{
    printf("run every 3 day  00:23:11 \r\n");
    return;
}


static void test_week01(void)
{
    printf("run every MON, WED, FRI  00:00:00 \r\n");
    return;
}

static void test_week02(void)
{
    printf("run every Firday 00:23:11 \r\n");
    return;
}


static void test_month01(void)
{
    printf("run every month  1  day:0  00:00:00 \r\n");
    return;
}

static void test_month02(void)
{
    printf("run every JAN, FEB   day 1  01:23:11 \r\n");
    return;
}


static void cmd_test_seconds(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("1-10/1 * * * * *", Repeats, 0);         // every minute 1-10s every second triggle once.
    cron_alarm_create("*/2 * * * * *", Repeats2, 0);         // timer for every 2 seconds
    cron_alarm_create("*/30 * * * * *", OnceOnly, 1);         // called once after 30 seconds
    return;
}

static void cmd_test_minutes(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("27 44 9 * * *", test_min01, 0);         // every 9:44:27
    cron_alarm_create("0 */1 * * * *", test_min02, 0);         // timer for every 1 minutes 
    cron_alarm_create("15 3 * * * *", test_min03, 1);         // 3 minutes run once
    return;
}

static void cmd_test_hour(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("0 0 */1 * * *", test_hour01, 0);         //every hour 0 min, 0 s
    cron_alarm_create("15 15 */4 * * *", test_hour02, 0);       //every 4 hour 15 min, 15 s
    return;
}


static void cmd_test_day(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("0 0 0 */1 * ?", test_day01, 0);         //every 1 day, 0:0:0
    cron_alarm_create("11 23 0 */3 * *", test_day02, 0);       //every 3 day, 00:23:11
    return;
}


static void cmd_test_week(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("0 0 0 * * MON,WED,FRI", test_week01, 0);         //every MON, WED, FRI 00:00:00
    cron_alarm_create("11 23 0 ? * 5", test_week02, 0);       //every Friday 00:23:11
    return;
}

static void cmd_test_month(char *buf, int len, int argc, char **argv)
{
    cron_alarm_create("0 0 0 1 * *", test_month01, 0);         //every month  1day, 00:00:00
    cron_alarm_create("11 23 1 1 JAN-FEB *", test_month02, 0);      //every JAN, FEB day1 01:23:11
    return;
}

static void cmd_add_minutes(char *buf, int len, int argc, char **argv)
{
    int num = 0;
    if (argc == 1) {
        cronal_time(60);
    } else if (argc == 2) {
        num = atoi(argv[1]);
        cronal_time(60 * num);
    } else {
    }

    return;
}

static void cmd_add_hour(char *buf, int len, int argc, char **argv)
{
    int num = 0;
    if (argc == 1) {
        cronal_time(3600);
    } else if (argc == 2) {
        num = atoi(argv[1]);
        cronal_time(3600 * num);
    } else {
    }

    return;
}

static void cmd_add_day(char *buf, int len, int argc, char **argv)
{
    int num = 0;
    if (argc == 1) {
        cronal_time(86400);
    } else if (argc == 2) {
        num = atoi(argv[1]);
        cronal_time(86400 * num);
    } else {
    }

    return;
}

static void cmd_add_week(char *buf, int len, int argc, char **argv)
{
    int num = 0;
    if (argc == 1) {
        cronal_time(604800);
    } else if (argc == 2) {
        num = atoi(argv[1]);
        cronal_time(604800 * num);
    } else {
    }
    
    return;
}

static void cmd_add_month(char *buf, int len, int argc, char **argv)
{
    int num = 0;
    if (argc == 1) {
        cronal_time(2592000);
    } else if (argc == 2) {
        num = atoi(argv[1]);
        cronal_time(2592000 * num);
    } else {
    }

    return;
}

static void cmd_show_date(char *buf, int len, int argc, char **argv)
{
    uint32_t seconds = 0;
    utils_time_date_t date;


    puts("test time is\r\n");
    seconds = cronal_time(0);
    utils_time_date_from_epoch(seconds, &date);
    printf("Date & time is: %u-%02u-%02u %02u:%02u:%02u (Day %u of week, Day %u of Year)\r\n",
        date.ntp_year,
        date.ntp_month,
        date.ntp_date,
        date.ntp_hour,
        date.ntp_minute,
        date.ntp_second,
        date.ntp_week_day,
        date.day_of_year
    );

    return;
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "test_seconds", "test seconds", cmd_test_seconds},
        { "test_minutes", "test minutes", cmd_test_minutes},
        { "test_hour", "test hour", cmd_test_hour},
        { "test_day", "test day", cmd_test_day},
        { "test_week", "test week", cmd_test_week},
        { "test_month", "test month", cmd_test_month},
        { "add_minutes", "add 1 minutes", cmd_add_minutes},
        { "add_hour", "add 1 hour", cmd_add_hour},
        { "add_day", "add 1 day", cmd_add_day},
        { "add_week", "add 1 week", cmd_add_week},
        { "add_month", "add 1 month", cmd_add_month},
        { "sdate", "show date", cmd_show_date},
};

int cron_alarm_cli_init(void)
{
    return 0;
}
