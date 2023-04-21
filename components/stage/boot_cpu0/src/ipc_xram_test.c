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
#include <FreeRTOS.h>
#include <task.h>
#include <cli.h>
#include <getopt.h>
#include <bl_ipc.h>
#include <bl808_glb.h>
#include <bl808_ipc.h>
#include "memdata.h"

#define READ_XRAM           0
#define WRITE_XRAM          1
#define IPC_LATENCY_M0      2
#define IPC_LATENCY_D0      3
#define DEFECT_VALUE        10

#define XRAM_BASE_ADDR      0x40000000
#define REG_ADDR_OFFSET     0x4
#define BYTES_SIZE          (16 * 1024)
#define MTIME_CLOCK_HZ      (22.733 * 1000 * 1000)

static void print_cpu_mtime(GLB_CORE_ID_Type id)
{
    uint32_t high;
    uint32_t low;

    high = *((volatile uint32_t *)0xE000BFFC);
    low = *((volatile uint32_t *)0xE000BFF8);

    switch (id) {
        case GLB_CORE_ID_M0:
            printf("[M0-E907] mtime: h: %lu, l: %lu\r\n", high, low);
            break;
        case GLB_CORE_ID_D0:
            printf("[D0-C906] mtime: h: %lu, l: %lu\r\n", high, low);
            break;
        case GLB_CORE_ID_LP:
            printf("[LP-E902] mtime: h: %lu, l: %lu\r\n", high, low);
            break;
        default:
            break;
    }
}

static void ipc_latency_m0(void)
{
    print_cpu_mtime(GLB_CORE_ID_D0);
}

static void ipc_latency_d0(void)
{
    IPC_Trigger_Target_CPU(GLB_CORE_ID_D0, IPC_LATENCY_D0);
    print_cpu_mtime(GLB_CORE_ID_D0);
}

static bool is_update = false;
static void loop_read_xram(void *pvParameters)
{
    uint32_t start_high;
    uint32_t start_low;
    uint32_t end_high;
    uint32_t end_low;

    while (1) {
        if (!is_update) {
            goto skip;
        }

        is_update = false;

        start_high = *((volatile uint32_t *)0xE000BFFC);
        start_low = *((volatile uint32_t *)0xE000BFF8);

        memcpy(test_data, (uint32_t *)XRAM_BASE_ADDR, BYTES_SIZE);

        end_high = *((volatile uint32_t *)0xE000BFFC);
        end_low = *((volatile uint32_t *)0xE000BFF8);

        uint32_t diff = (end_high - start_high) * 0xFFFFFFFF + (end_low - start_low);
        float speed = (float)BYTES_SIZE / diff * (float)MTIME_CLOCK_HZ / (1024 * 1024);

        printf("[E907][Read from XRAM] Start h: %lu, l: %lu\tEnd h: %lu, l: %lu\tDiff: %lu\tSpeed: %.3fMbytes/s\r\n",
                start_high, start_low, end_high, end_low, diff, speed);

skip:
        vTaskDelay(1);
    }
}

static void loop_write_xram(void *pvParameters)
{
    uint32_t start_high;
    uint32_t start_low;
    uint32_t end_high;
    uint32_t end_low;

    while (1) {
        start_high = *((volatile uint32_t *)0xE000BFFC);
        start_low = *((volatile uint32_t *)0xE000BFF8);

        memcpy((uint32_t *)XRAM_BASE_ADDR, test_data, BYTES_SIZE);
        csi_dcache_clean_range((uint32_t *)XRAM_BASE_ADDR, BYTES_SIZE);

        end_high = *((volatile uint32_t *)0xE000BFFC);
        end_low = *((volatile uint32_t *)0xE000BFF8);

        IPC_Trigger_Target_CPU(GLB_CORE_ID_D0, WRITE_XRAM);

        uint32_t diff = (end_high - start_high) * 0xFFFFFFFF + (end_low - start_low);
        float speed = (float)BYTES_SIZE / diff * (float)MTIME_CLOCK_HZ / (1024 * 1024);
        printf("[E907][Write to XRAM] Start h: %lu, l: %lu\tEnd h: %lu, l: %lu\tDiff: %lu\tSpeed: %.3fMbytes/s\r\n",
                start_high, start_low, end_high, end_low, diff, speed);

        vTaskDelay(2000);
    }
}

static void loop_send_ipc(void *pvParameters)
{
    while (1) {
        IPC_Trigger_Target_CPU(GLB_CORE_ID_D0, IPC_LATENCY_M0);
        print_cpu_mtime(GLB_CORE_ID_M0);
        vTaskDelay(2000);
    }
}

static void on_d0_trigger_callback(uint32_t src)
{
    switch (src) {
        case (1 << READ_XRAM):
            is_update = true;
            break;
        case (1 << IPC_LATENCY_M0):
            ipc_latency_m0();
            break;
        case (1 << IPC_LATENCY_D0):
            ipc_latency_d0();
            break;
        default:
            printf("cannot find ipc src %lu\r\n", src);
            break;
    }
}

static void show_usage(void)
{
    aos_cli_printf("ipc_xram_test [options]\r\n");
    aos_cli_printf("need select one of below options\r\n");
    aos_cli_printf("0: C906 write xram, and then E907 read\r\n");
    aos_cli_printf("\tE907 should run first\r\n");
    aos_cli_printf("1: E907 write xram, and then C906 read\r\n");
    aos_cli_printf("\tC906 should run first\r\n");
    aos_cli_printf("2: E907 trigger C906 IPC, C906 send callback to E907 when receive\r\n");
    aos_cli_printf("\tC906 should run first\r\n");
    aos_cli_printf("3: C906 trigger E907 IPC, E907 send callback to C906 when receive\r\n");
    aos_cli_printf("\tE907 should run first\r\n");
    aos_cli_printf("10: C906 continuously add 1 to specific xram, E907 defects the xram and print if the value is changed\n");
    aos_cli_printf("\tE907 should run first\r\n");
    aos_cli_printf("example:\r\n");
    aos_cli_printf("    ipc_xram_test 0\r\n");
}

static void loop_defect_value(void *pvParameters)
{
    uint32_t value = 0;
    while (1) {
        csi_dcache_invalid_range((uint32_t *)XRAM_BASE_ADDR, 4);
        if (*(volatile uint32_t *)XRAM_BASE_ADDR != value) {
            value = *(volatile uint32_t *)XRAM_BASE_ADDR;
            printf("[E907] value has been changed to %lu\r\n", value);
        }
        vTaskDelay(1);
    }
}

void ipc_xram_test(char *buf, int len, int argc, char **argv)
{
    if (2 != argc) {
        show_usage();
        return;
    }

    int cmd = atoi(argv[1]);
    switch (cmd) {
        case READ_XRAM:
            ipc_m0_init(NULL, on_d0_trigger_callback);
            xTaskCreate(loop_read_xram, "read xram", 1024, NULL, 5, NULL);
            puts("[E907] start to read xram test\r\n");
            break;
        case WRITE_XRAM:
            xTaskCreate(loop_write_xram, "write xram", 1024, NULL, 5, NULL);
            puts("[E907] start to write xram test\r\n");
            break;
        case IPC_LATENCY_M0:
            ipc_m0_init(NULL, on_d0_trigger_callback);
            xTaskCreate(loop_send_ipc, "send ipc", 1024, NULL, 5, NULL);
            puts("[E907] start to trigger D0 IPC\r\n");
            break;
        case IPC_LATENCY_D0:
            ipc_m0_init(NULL, on_d0_trigger_callback);
            puts("[E907] start to receive IPC from D0\r\n");
            break;
        case DEFECT_VALUE:
            xTaskCreate(loop_defect_value, "defect value", 512, NULL, 5, NULL);
            puts("start to defect the value on 0x40000000\r\n");
            break;
        default:
            show_usage();
            return ;
    }
}
