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
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "xram.h"
#include "xram_platform.h"
#include "ring.h"

#if XRAM_RING_MAX > 15
#error "Too many queues!"
#endif

#define XRAM_POOLING_TIMES 32

static struct xram_head *g_xram_head = NULL;

ring_pos_t xram_ring_c906_pos = NULL;
ring_pos_t xram_ring_e907_pos = NULL;

struct ring_desc {
    struct {
        enum xram_cpu_type ring_cpu;
        uint32_t ring_size;
    } item[2];
};

/* clang-format off */
/* Ring memory map defintion */
static struct ring_desc ring_map_define[XRAM_RING_ID_MAX] = {
  [XRAM_RING_ID_LOG_C906]       = {{{CPU_E907, 0}, {CPU_C906, 512 - 8}}},
  [XRAM_RING_ID_LOG_E902]       = {{{CPU_E907, 0}, {CPU_E902, 0}}},
  [XRAM_RING_ID_NET]            = {{{CPU_E907, 4096 - 8}, {CPU_C906, 4096 - 8}}},
  [XRAM_RING_ID_PERIPHERAL]     = {{{CPU_E907, 512 - 8}, {CPU_C906, 512 - 8}}},
  [XRAM_RING_ID_RPC]            = {{{CPU_E907, 128 - 8}, {CPU_C906, 128 - 8}}},
  [XRAM_RING_ID_AIn1_C906_E902] = {{{CPU_C906, 0}, {CPU_E902, 0}}},
  [XRAM_RING_ID_AIn1_E907_E902] = {{{CPU_E907, 0}, {CPU_E902, 0}}}
};
/* clang-format on */

/* Ethernet Ring, Peripherals Ring, RPC Ring... */
xram_ring_ctx_t g_xram_ring_context[XRAM_RING_ID_MAX];

void XRAMHeadCntClear(void)
{
    assert(g_xram_head != NULL);
    g_xram_head->cnt = 0;
}

void XRAMHeadCntIncrease(void)
{
    assert(g_xram_head != NULL);
    g_xram_head->cnt++;
}

void XRAMHeadCntSet(uint32_t val)
{
    assert(g_xram_head != NULL);
    g_xram_head->cnt = val;
}

int XRAMHeadCntGet(void)
{
    assert(g_xram_head != NULL);
    return (g_xram_head->cnt);
}

int XRAMHeadInit()
{
    enum xram_cpu_type cpu;

    g_xram_head = (struct xram_head *)xram_plat_get_xram_head();
    assert(g_xram_head != NULL);

    if(g_xram_head != XRAM_RING_ADDRESS){
        printf("xram head addr:%p not equal to %x.\r\n", g_xram_head, XRAM_RING_ADDRESS);
        return -1;
    }

    cpu = xram_plat_get_cpu_type();
    assert(cpu != CPU_MAX);
    if (cpu == CPU_E907) {
        g_xram_head->ver = xram_palt_get_xram_version();
        g_xram_head->cnt = 0;
    } else if ((cpu == CPU_C906) || (cpu == CPU_E902)) {
        if (!xram_palt_check_xram_version()) {
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

void xram_ring_pos_init(void)
{
    xram_ring_c906_pos = xram_plat_get_c906_ring_addr();
    xram_ring_e907_pos = xram_plat_get_e907_ring_addr();
    // printf("c906 pos:0x%x e907 pos:0x%x\r\n",xram_ring_c906_pos, xram_ring_e907_pos);
}

/* init XRAM meta ring, tx meta ring, rx meta ring */
int XRAMRingInit(void)
{
    enum xram_cpu_type cpu;
    xram_ring_ctx_t tmp;
    struct ring_desc *ring_desc;
    uint8_t *curr_addr;
    int i, j;

    curr_addr = xram_plat_get_xram_addr();
    if (curr_addr == NULL) {
        xram_log("get xram_addr_start address failed!\n");
        return -1;
    }

    xram_ring_pos_init();

    if (xram_plat_notify_init()) {
        xram_log("init notify failed\n");
        goto _exit_1;
    }

    cpu = xram_plat_get_cpu_type();
    /* init ring context */
    for (i = 0; i < XRAM_RING_ID_MAX; i++) {
        ring_desc = &ring_map_define[i];
        g_xram_ring_context[i] = NULL;

        for (j = 0; j < 2; j++) {
            /* If I am on the list, it means this queue belongs to me */
            if (ring_desc->item[j].ring_cpu == cpu) {
                tmp = xram_plat_ring_ctx_create(i);
                assert(tmp != NULL);  // TODO Release resouse instead
                g_xram_ring_context[i] = tmp;

                if (j == 0) {
                    /* I am the first one, I need to be responsible for the initialization */
                    tmp->tx_ring = xram_ring_init((void *)curr_addr, ring_desc->item[0].ring_size, i, cpu, RING_TYPE_TX);
                    if (tmp->tx_ring != NULL) {
                        curr_addr += (sizeof(struct xram_ring) + ring_desc->item[0].ring_size);
                    }

                    tmp->rx_ring = xram_ring_init((void *)curr_addr, ring_desc->item[1].ring_size, i, cpu, RING_TYPE_RX);
                    if (tmp->rx_ring != NULL) {
                        curr_addr += (sizeof(struct xram_ring) + ring_desc->item[1].ring_size);
                    }

                } else {
                    if (0 == ring_desc->item[0].ring_size) {
                        tmp->rx_ring = NULL;
                    } else {
                        tmp->rx_ring = (xram_ring_t)curr_addr;
                        curr_addr += (sizeof(struct xram_ring) + ring_desc->item[0].ring_size);
                    }

                    if (0 == ring_desc->item[1].ring_size) {
                        tmp->tx_ring = NULL;
                    } else {
                        tmp->tx_ring = (xram_ring_t)curr_addr;
                        curr_addr += (sizeof(struct xram_ring) + ring_desc->item[1].ring_size);
                    }
                }

                printf("init ring:%d,tx:%p,rx:%p\r\n", i, tmp->tx_ring, tmp->rx_ring);
            }
        }
    }

    return 0;

//_exit_4:
//_exit_3:
//xram_plat_ctx_destroy(&g_meta_ring);
//xram_plat_ctx_destroy(g_meta_ring);
//_exit_2:
//xram_plat_notify_deinit();
_exit_1:
    return -1;
}

int XRAMRingReset(uint32_t ringid)
{
    xram_ring_ctx_t curr_ring = g_xram_ring_context[ringid];
    assert(ringid < XRAM_RING_ID_MAX);

    if (curr_ring == NULL) {
        return -1;
    }

    /* reset us tx ring */
    if (curr_ring->tx_ring != NULL) {
        xram_ring_reset(curr_ring->tx_ring);
    }

    /* send reset request to peer to reset it's tx ring */
    xram_plat_notify_send(curr_ring, EVENT_RESET);

    /* waiting peer response */
    xram_plat_notify_wait(curr_ring, EVENT_RESET);
    return 0;
}

static int xram_write_internal(xram_ring_ctx_t ring_ctx, void *buffer, uint32_t size)
{
    uint32_t write_len = 0, curr_len;
    uint32_t loop = XRAM_POOLING_TIMES;
    assert(ring_ctx != NULL);

    xram_log("write to tx queue[%p]:head %d tail %d total %d :size [%d]\r\n", ring_ctx->tx_ring,
             (int)RING_HEAD(ring_ctx->tx_ring), (int)RING_TAIL(ring_ctx->tx_ring), (int)ring_ctx->tx_ring->buffer_size, (int)size);
    while (write_len < size) {
        if (xram_ring_is_full(ring_ctx->tx_ring)) {
            if (loop) {
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                loop--;
            } else {
                xram_plat_notify_wait(ring_ctx, EVENT_READ);
            }

            continue;
        }

        curr_len = xram_ring_write(ring_ctx->tx_ring, buffer + write_len, size - write_len);
        write_len += curr_len;

        xram_plat_notify_send(ring_ctx, EVENT_WRITE);
    }

    return write_len;
}

static int xram_write_timeout_internal(xram_ring_ctx_t ring_ctx, void *buffer, uint32_t size, uint32_t timeout_ms)
{
    uint32_t write_len = 0, curr_len;
    uint32_t loop = XRAM_POOLING_TIMES;
    assert(ring_ctx != NULL);

    unsigned int timeout = xram_plat_notify_calculate_timeout(timeout_ms);

    while (write_len < size) {
        if (xram_ring_is_full(ring_ctx->tx_ring)) {
            if (loop) {
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                loop--;
            } else {
                if (xram_plat_notify_wait_timeout(ring_ctx, EVENT_READ, &timeout)) {
                    return write_len;
                }
            }
            continue;
        }

        curr_len = xram_ring_write(ring_ctx->tx_ring, buffer + write_len, size - write_len);
        write_len += curr_len;

        xram_plat_notify_send(ring_ctx, EVENT_WRITE);
    }

    return write_len;
}

int XRAMRingWrite(uint32_t ringid, void *const buffer, uint32_t size)
{
    xram_ring_ctx_t curr_ring = g_xram_ring_context[ringid];
    assert(ringid < XRAM_RING_ID_MAX);

    if (curr_ring == NULL) {
        return -1;
    }

    return xram_write_internal(curr_ring, buffer, size);
}

int XRAMRingWriteTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout)
{
    xram_ring_ctx_t curr_ring = g_xram_ring_context[ringid];
    assert(ringid < XRAM_RING_ID_MAX);

    if (curr_ring == NULL) {
        return -1;
    }

    return xram_write_timeout_internal(curr_ring, buffer, size, timeout);
}

static int xram_read_internal(xram_ring_ctx_t ring_ctx, void *const buffer, uint32_t size)
{
    uint32_t read_len = 0, curr_len;
    uint32_t loop = XRAM_POOLING_TIMES;
    assert(ring_ctx != NULL);

    xram_log("read to tx queue[%p]:head %d tail %d total %d :size %d\r\n", ring_ctx->rx_ring,
             (int)RING_HEAD(ring_ctx->rx_ring), (int)RING_TAIL(ring_ctx->rx_ring), (int)ring_ctx->rx_ring->buffer_size, (int)size);
    while (read_len < size) {
        if (xram_ring_is_empty(ring_ctx->rx_ring)) {
            if (loop) {
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                loop--;
            } else {
                xram_plat_notify_wait(ring_ctx, EVENT_WRITE);
            }

            continue;
        }

        curr_len = xram_ring_read(ring_ctx->rx_ring, buffer + read_len, size - read_len);
        read_len += curr_len;
        xram_log("xram read curr len %d\r\n", (unsigned int)curr_len);

        xram_plat_notify_send(ring_ctx, EVENT_READ);
    }

    return read_len;
}

static int xram_read_timeout_internal(xram_ring_ctx_t ring_ctx, void *const buffer, uint32_t size, uint32_t timeout_ms)
{
    uint32_t read_len = 0, curr_len;
    uint32_t loop = XRAM_POOLING_TIMES;
    assert(ring_ctx != NULL);

    unsigned int timeout = xram_plat_notify_calculate_timeout(timeout_ms);
    xram_log("read to tx queue[%p]:head %d tail %d total %d :size %d\r\n", ring_ctx->rx_ring,
             (int)ring_ctx->rx_ring->head, (int)ring_ctx->rx_ring->tail, (int)ring_ctx->rx_ring->buffer_size, (int)size);

    while (read_len < size) {
        if (xram_ring_is_empty(ring_ctx->rx_ring)) {
            if (loop) {
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                asm volatile("nop");
                loop--;
            } else {
                if (xram_plat_notify_wait_timeout(ring_ctx, EVENT_WRITE, &timeout)) {
                    return read_len;
                }
            }
            continue;
        }

        curr_len = xram_ring_read(ring_ctx->rx_ring, buffer + read_len, size - read_len);
        read_len += curr_len;

        xram_plat_notify_send(ring_ctx, EVENT_READ);
    }

    return read_len;
}

int XRAMRingRead(uint32_t ringid, void *const buffer, uint32_t size)
{
    xram_ring_ctx_t curr_ring = g_xram_ring_context[ringid];

    assert(ringid < XRAM_RING_ID_MAX);

    if (curr_ring == NULL) {
        return -1;
    }

    return xram_read_internal(curr_ring, buffer, size);
}

int XRAMRingReadTimeout(uint32_t ringid, void *const buffer, uint32_t size, uint32_t timeout)
{
    xram_ring_ctx_t curr_ring = g_xram_ring_context[ringid];

    assert(ringid < XRAM_RING_ID_MAX);

    if (curr_ring == NULL) {
        return -1;
    }

    return xram_read_timeout_internal(curr_ring, buffer, size, timeout);
}
