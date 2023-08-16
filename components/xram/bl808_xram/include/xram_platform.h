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
#ifndef _XRAM_PLATFORM_H_
#define _XRAM_PLATFORM_H_
#include <stdint.h>
#include <xram.h>
#include <ring.h>
#include <bl808.h>

#if !defined(XRAM_CPU_C906) && !defined(XRAM_CPU_E907) && !defined(XRAM_CPU_E902)
#define error "Unknow CPU Type!"
#endif

struct bl_ipc_regs {
    volatile uint32_t trigger_int;
    volatile uint32_t a[7];
    volatile uint32_t trigger_int_res;
    volatile uint32_t int_rawstatus;
    volatile uint32_t int_clear;
    volatile uint32_t int_umaskset;
    volatile uint32_t int_umaskclear;
};
typedef struct bl_ipc_regs *bl_ipc_regs_t;

#define BL_IPC_BASE_E907 ((bl_ipc_regs_t)IPC0_BASE)  //((uint32_t)0x2000a800)
#define BL_IPC_E907_IRQn IPC_M0_IRQn                 //IRQ_NUM_BASE + 3

#define BL_IPC_BASE_E902 ((bl_ipc_regs_t)IPC1_BASE)  //((uint32_t)0x2000a840)
#define BL_IPC_E902_IRQn IPC_LP_IRQn

#define BL_IPC_BASE_C906 ((bl_ipc_regs_t)IPC2_BASE)  //((uint32_t)0x30005000)
#define BL_IPC_C906_IRQn IPC_D0_IRQn                 //IRQ_NUM_BASE + 38

#define BL_INTRRUPT_UMASK_FLAG (0xFFFFFFFF)

/* xram ring context */
struct xram_ring_ctx {
    xram_ring_t tx_ring;
    xram_ring_t rx_ring;
    int ring_id;
};
typedef struct xram_ring_ctx *xram_ring_ctx_t;

typedef void (*meta_rx_worker_func_t)(xram_ring_ctx_t meta_ring);

enum xram_cpu_type {
    CPU_C906,
    CPU_E907,
    CPU_E902,
    CPU_MAX,
};

enum xram_ring_event {
    EVENT_RESET,
    EVENT_WRITE,
    EVENT_READ,
    EVENT_MAX,
};

xram_ring_ctx_t xram_plat_ring_ctx_create(int notify_idx);
void xram_plat_ring_ctx_destroy(xram_ring_ctx_t *ctx);

static inline enum xram_cpu_type xram_plat_get_cpu_type(void) {
#if defined(XRAM_CPU_C906)
    return CPU_C906;
#elif defined(XRAM_CPU_E907)
    return CPU_E907;
#elif defined(XRAM_CPU_E902)
    return CPU_E902;
#endif
    return CPU_MAX;
}

void xram_plat_reset_meta_ring(void);
uint32_t xram_palt_get_xram_version(void);
uint32_t xram_palt_check_xram_version(void);
uint8_t *xram_plat_get_xram_head(void);
uint8_t *xram_plat_get_log_queue_addr(void);
uint8_t *xram_plat_get_xram_addr(void);
uint8_t *xram_plat_get_c906_ring_addr(void);
uint8_t *xram_plat_get_e907_ring_addr(void);

int xram_plat_notify_init(void);
void xram_plat_notify_deinit(void);
int xram_plat_notify_regist(xram_ring_ctx_t ctx);
void xram_plat_notify_unregist(xram_ring_ctx_t ctx);

unsigned int xram_plat_notify_calculate_timeout(unsigned int timeout_ms);

void xram_plat_notify_send(xram_ring_ctx_t ctx, enum xram_ring_event ev);
int xram_plat_notify_wait(xram_ring_ctx_t ctx, enum xram_ring_event ev);
int xram_plat_notify_wait_timeout(xram_ring_ctx_t ctx, enum xram_ring_event ev, unsigned int *timeout);
#endif

