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
#include <assert.h>
#include "ring.h"
#include "xram_platform.h"

#if defined(XRAM_CPU_C906)
#include <core_rv64.h>
#include <csi_rv64_gcc.h>
#elif defined(XRAM_CPU_E907)
#include <core_rv32.h>
#include <csi_rv32_gcc.h>
#endif

extern ring_pos_t xram_ring_c906_pos;
extern ring_pos_t xram_ring_e907_pos;
void debug_pos(uint32_t i)
{
    xram_log("[debug] [%d] e907:[%p/%d][%p/%d] c906:[%p/%d][%p/%d]\r\n",
             (int)i,
             &xram_ring_e907_pos->head[i],
             (int)xram_ring_e907_pos->head[i],
             &xram_ring_e907_pos->tail[i],
             (int)xram_ring_e907_pos->tail[i],
             &xram_ring_c906_pos->head[i],
             (int)xram_ring_c906_pos->head[i],
             &xram_ring_c906_pos->tail[i],
             (int)xram_ring_c906_pos->tail[i]);
}

#if 0
#define xram_ring_head_clean()                                         \
    {                                                                  \
        csi_dcache_clean_range(RING_HEAD_POS(ring), sizeof(uint32_t)); \
        csi_dcache_clean_range(RING_TAIL_POS(ring), sizeof(uint32_t)); \
    }

#define xram_ring_head_invalid()                                         \
    {                                                                    \
        csi_dcache_invalid_range(RING_HEAD_POS(ring), sizeof(uint32_t)); \
        csi_dcache_invalid_range(RING_TAIL_POS(ring), sizeof(uint32_t)); \
    }

#define xram_ring_head_flush()                                                 \
    {                                                                          \
        csi_dcache_clean_invalid_range(RING_HEAD_POS(ring), sizeof(uint32_t)); \
        csi_dcache_clean_invalid_range(RING_TAIL_POS(ring), sizeof(uint32_t)); \
    }

#define xram_ring_date_clean(addr, len)    \
    {                                      \
        csi_dcache_clean_range(addr, len); \
    }

#define xram_ring_data_invalid(addr, len)    \
    {                                        \
        csi_dcache_invalid_range(addr, len); \
    }

#define xram_ring_data_flush(addr, len)            \
    {                                              \
        csi_dcache_clean_invalid_range(addr, len); \
    }
#else
#define xram_ring_head_clean() \
    {                          \
        ;                      \
    }

#define xram_ring_head_invalid() \
    {                            \
        ;                        \
    }

#define xram_ring_head_flush() \
    {                          \
        ;                      \
    }
#define xram_ring_date_clean(addr, len) \
    {                                   \
        ;                               \
    }

#define xram_ring_data_invalid(addr, len) \
    {                                     \
        ;                                 \
    }

#define xram_ring_data_flush(addr, len) \
    {                                   \
        ;                               \
    }

#endif

xram_ring_t xram_ring_init(void *const buffer, uint32_t buffer_size, uint32_t ring_id, uint32_t cpu, uint32_t flag)
{
    struct xram_ring *ring;

    if (buffer == NULL || buffer_size == 0) {
        return NULL;
    }

    if (ring_id > XRAM_RING_ID_MAX) {
        return NULL;
    }

    ring = (struct xram_ring *)buffer;
    assert(xram_ring_c906_pos != NULL && xram_ring_e907_pos != NULL);
    if (cpu == CPU_C906) {
        if (flag == RING_TYPE_TX) {
            ring->head = (uintptr_t)&xram_ring_e907_pos->head[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
            ring->tail = (uintptr_t)&xram_ring_c906_pos->tail[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
        } else if (flag == RING_TYPE_RX) {
            ring->head = (uintptr_t)&xram_ring_c906_pos->head[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
            ring->tail = (uintptr_t)&xram_ring_e907_pos->tail[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
        }
    } else if (cpu == CPU_E907) {
        if (flag == RING_TYPE_TX) {
            ring->head = (uintptr_t)&xram_ring_c906_pos->head[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
            ring->tail = (uintptr_t)&xram_ring_e907_pos->tail[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
        } else if (flag == RING_TYPE_RX) {
            ring->head = (uintptr_t)&xram_ring_e907_pos->head[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
            ring->tail = (uintptr_t)&xram_ring_c906_pos->tail[ring_id] - (uintptr_t)XRAM_RING_ADDRESS;
        }
    }
    ring->buffer_size = buffer_size;
    xram_log("ringid %d cpu %d %s: head %x tail %x\r\n", (int)ring_id, (int)cpu, flag ? "RX" : "TX", (int)ring->head, (int)ring->tail);

    xram_ring_head_clean();

    return ring;
}

/* Caution! */
void xram_ring_reset(xram_ring_t ring)
{
    assert(ring != NULL);

    RING_HEAD(ring) = 0;
    RING_TAIL(ring) = 0;
    xram_ring_head_clean();
}

/* Reader */
int xram_ring_is_empty(xram_ring_t ring)
{
    assert(ring != NULL);

    xram_ring_head_invalid();
    return (RING_HEAD(ring) == RING_TAIL(ring));
}

int xram_ring_is_full(xram_ring_t ring)
{
    assert(ring != NULL);

    xram_ring_head_invalid();
    return (((RING_TAIL(ring) + 1) % ring->buffer_size) == RING_HEAD(ring));
}

/* Avaliable Data length */
uint32_t xram_ring_used_length(xram_ring_t ring)
{
    assert(ring != NULL);

    xram_ring_head_invalid();
    return ((RING_TAIL(ring) - RING_HEAD(ring) + ring->buffer_size) % ring->buffer_size);
}

/* Free space */
uint32_t xram_ring_free_length(xram_ring_t ring)
{
    assert(ring != NULL);

    xram_ring_head_invalid();
    return (ring->buffer_size - (xram_ring_used_length(ring)) - 1);
}

/* Reader */
uint32_t xram_ring_read(xram_ring_t ring, uint8_t *des, uint32_t size)
{
    uint32_t length;
    uint32_t bytes;
    uint32_t min;

    assert(ring != NULL && des != NULL);

    if (size == 0) {
        return 0;
    }

    length = xram_ring_used_length(ring);
    if (length == 0) {
        return 0;
    }

    bytes = (length > size) ? size : length;

    min = bytes <= (ring->buffer_size - RING_HEAD(ring)) ? bytes : ring->buffer_size - RING_HEAD(ring);
    xram_ring_data_invalid((void *)ring->buffer, ring->buffer_size);
    memcpy(des, ring->buffer + RING_HEAD(ring), min);
    memcpy(des + min, ring->buffer, bytes - min);

    /*
	 * make sure that the data is copied before
	 * incrementing the ring->head index counter
	 */
    rmb();

    RING_HEAD(ring) = (RING_HEAD(ring) + bytes) % ring->buffer_size;

    xram_ring_date_clean(RING_HEAD_POS(ring), sizeof(uint32_t));
    return bytes;
}

uint32_t xram_ring_write(xram_ring_t ring, uint8_t *src, uint32_t size)
{
    uint32_t freeLength;
    uint32_t bytes;
    uint32_t min;

    assert(ring != NULL);

    if (src == NULL || size == 0) {
        return 0;
    }

    if (xram_ring_is_full(ring)) {
        return 0;
    }

    freeLength = xram_ring_free_length(ring);
    bytes = (freeLength > size) ? size : freeLength;

    min = bytes <= (ring->buffer_size - RING_TAIL(ring)) ? bytes : ring->buffer_size - RING_TAIL(ring);
    memcpy(ring->buffer + RING_TAIL(ring), src, min);
    memcpy(ring->buffer, src + min, bytes - min);

    /*
	 * make sure that the data in the fifo is up to date before
	 * incrementing the ring->tail index counter
	 */
    wmb();
    RING_TAIL(ring) = (RING_TAIL(ring) + bytes) % ring->buffer_size;

    xram_ring_date_clean(RING_TAIL_POS(ring), sizeof(uint32_t));
    xram_ring_date_clean((void *)ring->buffer, ring->buffer_size);
    return bytes;
}

uint32_t xram_ring_get_dma_node(xram_ring_t ring, struct ring_dma *node, uint32_t size)
{
    uint32_t length;
    uint32_t bytes;
    uint32_t min;

    assert(ring != NULL);
    assert(node != NULL);

    if (node == NULL || size == 0) {
        return 0;
    }

    if (xram_ring_is_empty(ring)) {
        return 0;
    }

    length = xram_ring_used_length(ring);
    bytes = (length > size) ? size : length;
    min = bytes <= (ring->buffer_size - RING_HEAD(ring)) ? bytes : ring->buffer_size - RING_HEAD(ring);

    node->src = ring->buffer + RING_HEAD(ring);
    node->len = min;
    (node + 1)->src = ring->buffer;
    (node + 1)->len = bytes - min;

    return bytes;
}

