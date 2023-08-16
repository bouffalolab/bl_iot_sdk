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
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <bl_os_hal.h>

#include "cli.h"
#include "xram.h"

static BL_TaskHandle_t g_bench_rx_task;
static BL_TaskHandle_t g_bench_tx_task;

struct xram_bench_pkt {
    uint32_t crc32;
    uint32_t sequence;
    uint16_t pkt_length;
    uint8_t pattern;
    uint8_t data[];
} __attribute__((packed));
typedef struct xram_bench_pkt *xram_bench_pkt_t;

static unsigned int length_mismatch_cnt = 0;
static unsigned int data_payload_error_cnt = 0;
static unsigned int sequence_error_cnt = 0;

static void xram_rx_bench_thread(void *arg)
{
    uint32_t block_size = (uint32_t)(uintptr_t)arg;
    void *buffer = bl_os_malloc(block_size);
    uint32_t s_time, s_now;
    xram_bench_pkt_t pkt = (xram_bench_pkt_t)buffer;

    uint64_t total_recv = 0;
    uint32_t sequence = 0;

    if (buffer == NULL) {
        printf("allock block failed!\n");
        goto _out;
    }

    XRAMRingReset(XRAM_RING_ID_NET);

    s_time = bl_os_get_tick();
    while (1) {
        s_now = bl_os_get_tick();

        total_recv += XRAMRingRead(XRAM_RING_ID_NET, buffer, block_size);

        if (pkt->pkt_length != block_size) {
            printf("block size mismatch: %" PRId16 " != %" PRId32 "\r\n", pkt->pkt_length, block_size);
            length_mismatch_cnt++;
        }

        /* trick */
        if (pkt->pattern != pkt->data[0] || 0 != memcmp(pkt->data, pkt->data + 1, pkt->pkt_length - sizeof(struct xram_bench_pkt) - 1)) {
            printf("data payload mismatch! %" PRIx16 "\r\n", pkt->pattern);
            data_payload_error_cnt++;
        }

        if (pkt->sequence != sequence) {
            sequence_error_cnt++;
            sequence = pkt->sequence;
        }

        sequence++;

#if defined(XRAM_BENCH_USE_CRC)
        /* TODO */
#endif

        if ((s_now - s_time) > 1000) {
            float f_now;

            f_now = ((float)(total_recv)*8 / ((float)(s_now - s_time) / 1000)) / 1000000;

            printf("xram rx bench: %.4f Mbps. total %" PRId64 " time %" PRId32
                   "s"
                   ",[L]:%d, [P]:%d, [S]:%d\r\n",
                   f_now,
                   total_recv,
                   (s_now - s_time) / 1000,
                   length_mismatch_cnt,
                   data_payload_error_cnt,
                   sequence_error_cnt);
            total_recv = 0;
            s_time = s_now;
        }
    }

_out:
    bl_os_task_delete(NULL);
}

static void xram_tx_bench_thread(void *arg)
{
    uint32_t block_size = (uint32_t)(uintptr_t)arg;
    void *buffer = bl_os_malloc(block_size);
    xram_bench_pkt_t pkt = (xram_bench_pkt_t)buffer;
    unsigned char data = 0;
    uint32_t s_time, s_now;

    uint64_t total_send = 0;
    uint32_t sequence = 0;

    if (buffer == NULL) {
        printf("allock block failed!\n");
        goto _out;
    }

    s_time = bl_os_get_tick();
    while (1) {
        pkt->pkt_length = block_size;
        pkt->pattern = data++;
        pkt->sequence = sequence++;

        s_now = bl_os_get_tick();
        memset(pkt->data, pkt->pattern, pkt->pkt_length - sizeof(struct xram_bench_pkt));

        total_send += XRAMRingWrite(XRAM_RING_ID_NET, buffer, block_size);

        if ((s_now - s_time) > 1000) {
            float f_now;

            f_now = ((float)(total_send)*8 / ((float)(s_now - s_time) / 1000)) / 1000000;

            printf("xram tx bench: %.4f Mbps. total %" PRId64 " time %" PRId32
                   "s"
                   "\r\n",
                   f_now,
                   total_send,
                   (s_now - s_time) / 1000);
            total_send = 0;
            s_time = s_now;
        }
    }

_out:
    bl_os_task_delete(NULL);
}

static void cmd_xram_bench_init(char *buf, int len, int argc, char **argv)
{
    int result;
    uint32_t block_size = 128;

    if (argc > 1) {
        block_size = atoi(argv[1]);
    }

    if (block_size == 0) {
        printf("bench time error!\r\n");
        return;
    }

    if (XRAMHeadInit() == -1) {
        puts("Init XRAM head failed.\r\n");
        return;
    }

    XRAMRingInit();

    result = bl_os_task_create("rx_bench", xram_rx_bench_thread, 256, (void *)block_size, 14, &g_bench_rx_task);
    if (result != BL_OS_TRUE) {
        printf("create xram bench rx task failed!!\r\n");
    }
}

static void cmd_xram_bench_start(char *buf, int len, int argc, char **argv)
{
    int result;
    uint32_t block_size = 128;

    if (argc > 1) {
        block_size = atoi(argv[1]);
    }

    if (block_size == 0) {
        printf("bench time error!\r\n");
        return;
    }

    result = bl_os_task_create("tx_bench", xram_tx_bench_thread, 256, (void *)block_size, 14, &g_bench_tx_task);
    if (result != BL_OS_TRUE) {
        printf("create xram bench tx task failed!!\r\n");
    }
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"xram_bench_init", "xram bench init [rx block size]", cmd_xram_bench_init},
    {"xram_bench_start", "xram bench start", cmd_xram_bench_start}};

void cli_init_xram_bench(void)
{
    return;
}

