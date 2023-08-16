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
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <bl_os_hal.h>
#include <ring.h>
#include <xram.h>
#include <xram_platform.h>
#include <bl_irq.h>

static volatile uint32_t g_ipi_regs_bak;

#define STATIC_XRAM_REGION_ATTRIBUTE __attribute__((section(".static_xram_region")))
#define XRAM_RANGE_SIZE (16384) /* xram size:16K */
static uint8_t s_xram_region[XRAM_RANGE_SIZE] STATIC_XRAM_REGION_ATTRIBUTE;

/* IPI */
#define IPI_TRIGGER_STATUS(base) (*((volatile uint32_t *)(base) + 9))

#define IPI_TRIGGER_SET(base, bits)                    \
    {                                                  \
        (*((volatile uint32_t *)(base) + 0) = (bits)); \
    }

#define IPI_TRIGGER_CLEAR(base, bits)                   \
    {                                                   \
        (*((volatile uint32_t *)(base) + 10) = (bits)); \
    }

/* enable bits corresponding interrupt */
#define IPI_UNMASK(base, bits)                          \
    {                                                   \
        (*((volatile uint32_t *)(base) + 11) = (bits)); \
        g_ipi_regs_bak |= (bits);                       \
    }

/* disable bits corresponding interrupt */
#define IPI_MASK(base, bits)                            \
    {                                                   \
        (*((volatile uint32_t *)(base) + 12) = (bits)); \
        g_ipi_regs_bak &= ~(bits);                      \
    }

extern xram_ring_ctx_t g_xram_ring_context[XRAM_RING_ID_MAX];

struct ipi_reg_desc;
struct ipi_reg_field_desc {
    enum xram_ring_id ring_id;
    struct ipi_reg_desc *peer;
};

struct ipi_reg_desc {
    bl_ipc_regs_t ipi_reg_base;   /* ipi register base address */
    enum xram_cpu_type belong_to; /* belong to which cpu */
    struct ipi_reg_field_desc *reg_field;
};

static const struct ipi_reg_field_desc ipi_c906_from_e907[];
//static const struct ipi_reg_field_desc ipi_c906_from_e902[];
static const struct ipi_reg_field_desc ipi_e907_from_c906[];
//static const struct ipi_reg_field_desc ipi_e907_from_e902[];
//static const struct ipi_reg_field_desc ipi_e902_from_c907[];
//static const struct ipi_reg_field_desc ipi_e902_from_e907[];

/* CPU IPI trigger info */
static const struct ipi_reg_desc peer_trigger_info[] = {
    [CPU_C906] = {BL_IPC_BASE_E907, CPU_E907, ipi_c906_from_e907},
    [CPU_E907] = {BL_IPC_BASE_C906, CPU_C906, ipi_e907_from_c906},
};

static const struct ipi_reg_desc *ring_route_table[XRAM_RING_ID_MAX] = {
#if defined(XRAM_CPU_C906)
    [XRAM_RING_ID_LOG_C906] = &peer_trigger_info[CPU_C906],
    [XRAM_RING_ID_NET] = &peer_trigger_info[CPU_C906],
    [XRAM_RING_ID_PERIPHERAL] = &peer_trigger_info[CPU_C906],
    [XRAM_RING_ID_RPC] = &peer_trigger_info[CPU_C906],
#elif defined(XRAM_CPU_E907)
    [XRAM_RING_ID_LOG_C906] = &peer_trigger_info[CPU_E907],
    [XRAM_RING_ID_NET] = &peer_trigger_info[CPU_E907],
    [XRAM_RING_ID_PERIPHERAL] = &peer_trigger_info[CPU_E907],
    [XRAM_RING_ID_RPC] = &peer_trigger_info[CPU_E907],
#elif defined(XRAM_CPU_E902)
// TODO
#endif
};

static const struct ipi_reg_field_desc ipi_c906_from_e907[] = {
    {XRAM_RING_ID_LOG_C906, &peer_trigger_info[CPU_E907]},
    {XRAM_RING_ID_NET, &peer_trigger_info[CPU_E907]},
    {XRAM_RING_ID_PERIPHERAL, &peer_trigger_info[CPU_E907]},
    {XRAM_RING_ID_RPC, &peer_trigger_info[CPU_E907]},
    {XRAM_RING_ID_MAX, NULL}};

static const struct ipi_reg_field_desc ipi_e907_from_c906[] = {
    {XRAM_RING_ID_LOG_C906, &peer_trigger_info[CPU_C906]},
    {XRAM_RING_ID_NET, &peer_trigger_info[CPU_C906]},
    {XRAM_RING_ID_PERIPHERAL, &peer_trigger_info[CPU_C906]},
    {XRAM_RING_ID_RPC, &peer_trigger_info[CPU_C906]},
    {XRAM_RING_ID_MAX, NULL}};

struct xram_plat_ring_ctx {
    struct xram_ring_ctx p_ctx;
};

static struct xram_plat_ring_ctx xram_plat_ring_context[XRAM_RING_ID_MAX];

/* record which task wait which ring's which event */
static BL_TaskHandle_t ring_wait_slot[XRAM_RING_ID_MAX][EVENT_MAX];

static int find_reg_field_idx(struct ipi_reg_field_desc *reg_field, enum xram_ring_id ring_id)
{
    int i;

    for (i = 0; reg_field[i].ring_id != ring_id && reg_field[i].ring_id != XRAM_RING_ID_MAX; i++)
        ;

    if (reg_field[i].ring_id == XRAM_RING_ID_MAX) {
        return -1;
    } else {
        return i;
    }
    return -1;
}

//static void xram_plat_ring_irq_handler(struct ipi_reg_desc *local_ipi_desc) {
static void xram_plat_ring_irq_handler(void)
{
#if defined(XRAM_CPU_E907)
    struct ipi_reg_desc *local_ipi_desc = &peer_trigger_info[CPU_C906];
#elif defined(XRAM_CPU_C906)
    struct ipi_reg_desc *local_ipi_desc = &peer_trigger_info[CPU_E907];
#endif
    uint32_t pending = IPI_TRIGGER_STATUS(local_ipi_desc->ipi_reg_base);
    uint32_t ring_status;
    int ipi_idx, ring_id, peer_ipi_idx;
    int xYieldRequired = BL_OS_FALSE, xYieldFinal = BL_OS_FALSE;

    for (ipi_idx = 0; (ring_id = local_ipi_desc->reg_field[ipi_idx].ring_id), ring_id != XRAM_RING_ID_MAX; ipi_idx++) {
        /* check current ring have event pending or not */
        ring_status = (pending >> (3 * ipi_idx)) & 0x7;

        if (ring_status == 0) {
            continue;
        }

        if (ring_status & (0x1 << EVENT_READ)) {
            xram_log("irq handle: %d read ev\r\n", ring_id);
            /* weak up waiting read event thread */
            if (ring_wait_slot[ring_id][EVENT_READ] != NULL) {
                xYieldRequired = bl_os_task_notify_isr(ring_wait_slot[ring_id][EVENT_READ]);
                xYieldFinal |= xYieldRequired;
                ring_wait_slot[ring_id][EVENT_READ] = NULL;
                IPI_MASK(local_ipi_desc->ipi_reg_base, (0x1 << EVENT_READ) << (3 * ipi_idx));
            }
        }

        if (ring_status & (0x1 << EVENT_WRITE)) {
            xram_log("irq handle: %d write ev\r\n", ring_id);
            /* weak up waiting write event thread */
            if (ring_wait_slot[ring_id][EVENT_WRITE] != NULL) {
                xYieldRequired = bl_os_task_notify_isr(ring_wait_slot[ring_id][EVENT_WRITE]);
                xYieldFinal |= xYieldRequired;
                ring_wait_slot[ring_id][EVENT_WRITE] = NULL;
                IPI_MASK(local_ipi_desc->ipi_reg_base, (0x1 << EVENT_WRITE) << (3 * ipi_idx));
            }
        }

        if (ring_status & (0x1 << EVENT_RESET)) {
            printf("irq handle: %d reset ev\r\n", ring_id);

            /* do meta rx ring reset */
            if (g_xram_ring_context[ring_id]->tx_ring != NULL) {
                xram_ring_reset(g_xram_ring_context[ring_id]->tx_ring);
            }

            /* weak up waiting reset event thread */
            if (ring_wait_slot[ring_id][EVENT_RESET] != NULL) {
                xYieldRequired = bl_os_task_notify_isr(ring_wait_slot[ring_id][EVENT_RESET]);
                xYieldFinal |= xYieldRequired;
                ring_wait_slot[ring_id][EVENT_RESET] = NULL;

                /* Mask reset handler, prevent re-entering the interrupt and let the lower half handle it */
                IPI_MASK(local_ipi_desc->ipi_reg_base, (0x1 << EVENT_RESET) << (3 * ipi_idx));
            } else {
                /* Notify peer */
                struct ipi_reg_desc *peer_ipi_desc = ring_route_table[ring_id];
                assert(peer_ipi_desc != NULL);

                /* Get ring id corresponding peer ipi register descriptor */
                peer_ipi_idx = find_reg_field_idx(peer_ipi_desc->reg_field, ring_id);

                assert(peer_ipi_idx != -1);

                IPI_TRIGGER_CLEAR(local_ipi_desc->ipi_reg_base, (0x1 << EVENT_RESET) << (3 * ipi_idx));

                /* trigger peer back */
                IPI_TRIGGER_SET(peer_ipi_desc->ipi_reg_base, (0x1 << EVENT_RESET) << (3 * peer_ipi_idx));
            }
        }
    }

    bl_os_yield_from_isr(xYieldFinal);
}

xram_ring_ctx_t xram_plat_ring_ctx_create(int ring_id)
{
    struct xram_plat_ring_ctx *ctx;

    if (ring_id > XRAM_RING_ID_MAX) {
        xram_log("invalid ring_id\n");
        return NULL;
    }

    ctx = &xram_plat_ring_context[ring_id];

#if 0
  ctx = calloc(1, sizeof(struct xram_plat_ring_ctx));
  if (ctx == NULL) {
    return NULL;
  }
#endif

    ctx->p_ctx.ring_id = ring_id;

    return &ctx->p_ctx;
}

void xram_plat_ring_ctx_destroy(xram_ring_ctx_t *ctx)
{
    assert(ctx != NULL && *ctx != NULL);
#if 0
  free(*ctx);
  *ctx = NULL;
#endif
}

uint32_t xram_palt_get_xram_version(void)
{
    /* TODO */
    return 1;
}

int xram_plat_get_log_discard_cnt(void)
{
    /* TODO */
    return 0;
}

uint32_t xram_palt_check_xram_version(void)
{
    /* TODO */
    return 1;
}

uint8_t *xram_plat_get_xram_head(void)
{
    /* xram head address */
    return (uint8_t *)s_xram_region;
}

#define ADDR_ALIGN_UP(x) (((uintptr_t)(x) + 0x3F) & ~0x3F)

uint8_t *xram_plat_get_c906_ring_addr(void)
{
    /* c906 ring pos array address */
    return (uint8_t *)ADDR_ALIGN_UP(xram_plat_get_xram_head() + sizeof(struct xram_head));
}

uint8_t *xram_plat_get_e907_ring_addr(void)
{
    /* e907 ring pos array address */
    return ADDR_ALIGN_UP(xram_plat_get_c906_ring_addr() + sizeof(struct ring_pos));
}

uint8_t *xram_plat_get_xram_addr(void)
{
    /* xram address */
    return ADDR_ALIGN_UP(xram_plat_get_e907_ring_addr() + sizeof(struct ring_pos));
}

int xram_plat_notify_init(void)
{
    /* mask all register */
#if defined(XRAM_CPU_C906)
    IPI_MASK(BL_IPC_BASE_C906, (uint32_t)-1);
    bl_irq_register(BL_IPC_C906_IRQn, xram_plat_ring_irq_handler);
    bl_irq_enable(BL_IPC_C906_IRQn);
#elif defined(XRAM_CPU_E907)
    IPI_MASK(BL_IPC_BASE_E907, (uint32_t)-1);
    bl_irq_register(BL_IPC_E907_IRQn, xram_plat_ring_irq_handler);
    bl_irq_enable(BL_IPC_E907_IRQn);
#elif defined(XRAM_CPU_E902)
#endif

    return 0;
}

void xram_plat_notify_deinit(void)
{
    /* TODO */
}

static struct ipi_reg_desc *xram_plat_local_ipi_desc(int *ipi_idx, enum xram_ring_id ring_id)
{
    int index;
    struct ipi_reg_desc *local_ipi_desc;
    index = find_reg_field_idx(ring_route_table[ring_id]->reg_field, ring_id);
    assert(index != -1);

    local_ipi_desc = ring_route_table[ring_id]->reg_field[index].peer;
    assert(local_ipi_desc != NULL);

    index = find_reg_field_idx(local_ipi_desc->reg_field, ring_id);
    assert(index != -1);

    *ipi_idx = index;

    return local_ipi_desc;
}

int xram_plat_notify_regist(xram_ring_ctx_t ctx)
{
    uint32_t bits;
    int ipi_idx;
    struct ipi_reg_desc *local_ipi_desc = NULL;

    assert(ctx != NULL);

    local_ipi_desc = xram_plat_local_ipi_desc(&ipi_idx, ctx->ring_id);
    assert(ipi_idx != -1 && local_ipi_desc != NULL);

    bits = (0x1 << EVENT_RESET) << (ipi_idx * 3);

    bl_os_enter_critical();
    /* enable reset event */
    IPI_UNMASK(local_ipi_desc->ipi_reg_base, bits);
    bl_os_exit_critical(0);
    return 0;
}

void xram_plat_notify_unregist(xram_ring_ctx_t ctx)
{
    return;
}

unsigned int xram_plat_notify_calculate_timeout(unsigned int timeout_ms)
{
    return bl_os_ms_to_tick(timeout_ms);
}

void xram_plat_notify_send(xram_ring_ctx_t ctx, enum xram_ring_event ev)
{
    uint32_t bits;
    int ipi_idx;
    struct ipi_reg_desc *ipi_desc;

    assert(ev < EVENT_MAX);

    /* if we trigger reset event, we mask us reset interrupt first */
    if (ev == EVENT_RESET) {
        struct ipi_reg_desc *local_ipi_desc = NULL;

        /* get local ipi register descriptor */
        local_ipi_desc = xram_plat_local_ipi_desc(&ipi_idx, ctx->ring_id);
        assert(ipi_idx != -1 && local_ipi_desc != NULL);

        bits = (0x1 << EVENT_RESET) << (3 * ipi_idx);

        bl_os_enter_critical();
        IPI_MASK(local_ipi_desc->ipi_reg_base, bits);
        bl_os_exit_critical(0);
    }

    /* Get ring id corresponding peer ipi register descriptor */
    ipi_desc = ring_route_table[ctx->ring_id];
    assert(ipi_desc != NULL);

    ipi_idx = find_reg_field_idx(ipi_desc->reg_field, ctx->ring_id);
    bits = (0x1 << ev) << (3 * ipi_idx);

    /* XXX trigger the event interrupt */
    bl_os_enter_critical();
    IPI_TRIGGER_SET(ipi_desc->ipi_reg_base, bits);
    bl_os_exit_critical(0);

    return;
}

int xram_plat_notify_wait(xram_ring_ctx_t ctx, enum xram_ring_event ev)
{
    BL_TaskHandle_t me = NULL;
    struct ipi_reg_desc *local_ipi_desc = NULL;
    int ipi_idx;
    uint32_t bits;

    assert(ev < EVENT_MAX);
    assert(ctx != NULL);

    /* get local ipi register descriptor */
    local_ipi_desc = xram_plat_local_ipi_desc(&ipi_idx, ctx->ring_id);
    assert(ipi_idx != -1 && local_ipi_desc != NULL);

    bits = (0x1 << ev) << (3 * ipi_idx);

    me = bl_os_task_get_current_task();

    for (;;) {
        bl_os_enter_critical();
        /* if corresponding pending bit already set */
        if (IPI_TRIGGER_STATUS(local_ipi_desc->ipi_reg_base) & bits) {
            /* clear pending bit */
            IPI_TRIGGER_CLEAR(local_ipi_desc->ipi_reg_base, bits);

            /* re-enable RESET interrupt */
            if (ev == EVENT_RESET) {
                bits = (0x1 << EVENT_RESET) << (3 * ipi_idx);
                IPI_UNMASK(local_ipi_desc->ipi_reg_base, bits);
            }

            bl_os_exit_critical(0);
            return 0;
        }

        assert(ring_wait_slot[ctx->ring_id][ev] == NULL || ring_wait_slot[ctx->ring_id][ev] == me);
        ring_wait_slot[ctx->ring_id][ev] = me;

        /* enable corresponding bit's interrupt */
        IPI_UNMASK(local_ipi_desc->ipi_reg_base, bits);

        bl_os_exit_critical(0);

        // if ((ring_wait_slot[ctx->ring_id][ev]) == NULL && (*(uint32_t *)((uintptr_t)me + 0xa0) == 0))
        // {
        //   assert(0);
        // }

        bl_os_task_wait(me, 5);
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}

int xram_plat_notify_wait_timeout(xram_ring_ctx_t ctx, enum xram_ring_event ev, unsigned int *timeout)
{
    BL_TaskHandle_t me = NULL;
    BL_TimeOut_t xTimeOut;
    BL_TickType_t xTicksToWait = 0;
    struct ipi_reg_desc *local_ipi_desc;
    int ipi_idx;
    uint32_t bits;

    assert(ev < EVENT_MAX);
    assert(ctx != NULL);
    assert(timeout != NULL);

    xTicksToWait = (BL_TickType_t)*timeout;
    /* get local ipi register descriptor */
    local_ipi_desc = xram_plat_local_ipi_desc(&ipi_idx, ctx->ring_id);
    assert(ipi_idx != -1 && local_ipi_desc != NULL);

    bits = (0x1 << ev) << (3 * ipi_idx);

    me = bl_os_task_get_current_task();
    xTimeOut = bl_os_set_timeout();

    for (;;) {
        if (bl_os_check_timeout(xTimeOut, &xTicksToWait) != BL_OS_FALSE) {
            *timeout = 0;
            return -1;
        }

        bl_os_enter_critical();
        /* if corresponding pending bit already set */
        if (IPI_TRIGGER_STATUS(local_ipi_desc->ipi_reg_base) & bits) {
            /* clear pending bit */
            IPI_TRIGGER_CLEAR(local_ipi_desc->ipi_reg_base, bits);
            bl_os_exit_critical(0);

            *timeout = xTicksToWait;
            return 0;
        }

        assert(ring_wait_slot[ctx->ring_id][ev] == NULL || ring_wait_slot[ctx->ring_id][ev] == me);
        ring_wait_slot[ctx->ring_id][ev] = me;

        /* enable corresponding bit's interrupt */
        IPI_UNMASK(local_ipi_desc->ipi_reg_base, bits);

        bl_os_exit_critical(0);

        bl_os_task_wait(me, xTicksToWait);
    }

    bl_os_free(xTimeOut);
}

