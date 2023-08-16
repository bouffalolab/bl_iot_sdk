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
#ifndef __RING_H_
#define __RING_H_

#include <stdint.h>
#include "xram.h"
// #include "xram_platform.h"

/* NOTE: must be a value power of two */
#define RING_BUFFER_MIN_SIZE 512

/** Memory barriers */
#define mb() __DSB()
#define rmb() __DSB()
#define wmb() __DSB()

struct xram_ring {
    uint16_t head;
    uint16_t tail;
    uint32_t buffer_size;
    uint8_t buffer[];
};
typedef struct xram_ring *xram_ring_t;

struct ring_pos {
    // uint32_t head[XRAM_RING_ID_MAX];
    // uint32_t tail[XRAM_RING_ID_MAX];
    uint32_t head[16];
    uint32_t tail[16];
};

typedef struct ring_pos *ring_pos_t;
#define RING_POSITION_LEN (sizeof(struct ring_pos))
#define RING_TYPE_TX 0
#define RING_TYPE_RX 1

/* EM Region */
#define XRAM_RING_ADDRESS (0x22020000)

#define RING_HEAD_POS(x) ((void *)(x->head + XRAM_RING_ADDRESS))
#define RING_TAIL_POS(x) ((void *)(x->tail + XRAM_RING_ADDRESS))

#define RING_HEAD(x) (*(uint32_t *)(x->head + XRAM_RING_ADDRESS))
#define RING_TAIL(x) (*(uint32_t *)(x->tail + XRAM_RING_ADDRESS))

struct ring_dma {
    uint8_t *src;
    uint32_t len;
};

#define XRAM_RING_HEADER_SIZE (sizeof(struct xram_ring))

void debug_pos(uint32_t i);
xram_ring_t xram_ring_init(void *const buffer, uint32_t buffer_size, uint32_t ring_id, uint32_t cpu, uint32_t flag);
void xram_ring_reset(xram_ring_t ring);
int xram_ring_is_empty(xram_ring_t ring);
int xram_ring_is_full(xram_ring_t ring);

uint32_t xram_ring_used_length(xram_ring_t ring);
uint32_t xram_ring_free_length(xram_ring_t ring);
uint32_t xram_ring_read(xram_ring_t ring, uint8_t *des, uint32_t size);
uint32_t xram_ring_write(xram_ring_t ring, uint8_t *src, uint32_t size);
uint32_t xram_ring_get_dma_node(xram_ring_t ring, struct ring_dma *node, uint32_t size);
#endif

