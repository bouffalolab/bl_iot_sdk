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
#include "malloc_hw.h"

#include <FreeRTOS.h>
#include "string.h"
#include "stdio.h"

#define MEM_UNIT_SIZE            1024

#define DTCM_ADDR_START     0X2014000
#define DTCM_ADDR_END       (DTCM_ADDR_START + (48 * 1024))
#define OCRAM_ADDR_START    0X2020000
#define OCRAM_ADDR_END      (OCRAM_ADDR_START + (64 * 1024))
#define WRAM_ADDR_START     0X2030000
#define WRAM_ADDR_END       (WRAM_ADDR_START + (112 * 1024))

static const char *g_ram_type[] = {
    "DTCM",
    "OCRAM",
    "WRAM",
};

void *malloc_hw (size_t size, ram_type_t type)
{
    void *ptr;
    uint32_t counts, piece, ptr_piece_num;
    uint32_t *p_heap_addr;
    uint32_t addr_start, addr_end;

    if (type == DTCM) {
        addr_start = DTCM_ADDR_START;
        addr_end = OCRAM_ADDR_END;
    } else if (type == OCRAM) {
        addr_start = OCRAM_ADDR_START;
        addr_end = OCRAM_ADDR_END;
    } else if (type == WRAM) {
        addr_start = WRAM_ADDR_START;
        addr_end = WRAM_ADDR_END;
    } else {
        return NULL;
    }

    ptr_piece_num = xPortGetFreeHeapSize() / MEM_UNIT_SIZE + 1;
    p_heap_addr = pvPortMalloc(ptr_piece_num * 4);
    memset(p_heap_addr, 0, ptr_piece_num * 4);
    if (p_heap_addr == NULL) {
        return NULL;
    }
    
    ptr = NULL;
    counts = 0;
    while (1) {
        ptr = pvPortMalloc(MEM_UNIT_SIZE);

        if (ptr == NULL) {
            goto __exit;
        }

        p_heap_addr[counts++] = (uint32_t)ptr;

        if ((uint32_t)((uint32_t)ptr & 0x0fffffff) >= addr_start) {
            if ((uint32_t)((uint32_t)ptr & 0x0fffffff) <= addr_end) {
                printf("ram type is %s\r\n", g_ram_type[type]);
                ptr = pvPortMalloc(size);
                break;
            }
        }
    }
    for (piece = 0; piece < counts; piece++) {
        vPortFree((uint32_t *)p_heap_addr[piece]);
    }

__exit:
    vPortFree(p_heap_addr);
    return ptr;
}

void free_hw(void *ptr)
{
    vPortFree(ptr);
}
