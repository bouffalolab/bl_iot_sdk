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
#include "csi_core.h"
#include "rv_pmp.h"

static void rvpmp_reg_write(uintptr_t i, uintptr_t attr, uintptr_t pa)
{
    register uintptr_t cfg = 0;
    uintptr_t offset = 0;
    uintptr_t mask = ENTRY_FLAG_MASK;

    switch (i) {
        case 0:
            __asm volatile("csrw pmpaddr0, %0"
                           :
                           : "r"(pa));
            break;

        case 1:
            __asm volatile("csrw pmpaddr1, %0"
                           :
                           : "r"(pa));
            break;

        case 2:
            __asm volatile("csrw pmpaddr2, %0"
                           :
                           : "r"(pa));
            break;

        case 3:
            __asm volatile("csrw pmpaddr3, %0"
                           :
                           : "r"(pa));
            break;

        case 4:
            __asm volatile("csrw pmpaddr4, %0"
                           :
                           : "r"(pa));
            break;

        case 5:
            __asm volatile("csrw pmpaddr5, %0"
                           :
                           : "r"(pa));
            break;

        case 6:
            __asm volatile("csrw pmpaddr6, %0"
                           :
                           : "r"(pa));
            break;

        case 7:
            __asm volatile("csrw pmpaddr7, %0"
                           :
                           : "r"(pa));
            break;

        case 8:
            __asm volatile("csrw pmpaddr8, %0"
                           :
                           : "r"(pa));
            break;

        case 9:
            __asm volatile("csrw pmpaddr9, %0"
                           :
                           : "r"(pa));
            break;

        case 10:
            __asm volatile("csrw pmpaddr10, %0"
                           :
                           : "r"(pa));
            break;

        case 11:
            __asm volatile("csrw pmpaddr11, %0"
                           :
                           : "r"(pa));
            break;

        case 12:
            __asm volatile("csrw pmpaddr12, %0"
                           :
                           : "r"(pa));
            break;

        case 13:
            __asm volatile("csrw pmpaddr13, %0"
                           :
                           : "r"(pa));
            break;

        case 14:
            __asm volatile("csrw pmpaddr14, %0"
                           :
                           : "r"(pa));
            break;

        case 15:
            __asm volatile("csrw pmpaddr15, %0"
                           :
                           : "r"(pa));
            break;

        default:
            break;
    }

#if (__riscv_xlen == 32)

    switch (i) {
        case 0 ... 3:
            __asm volatile("csrr %0, pmpcfg0"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= ~(mask << (offset * ENTRY_FLAG_SIZE));
            cfg |= attr << (offset * ENTRY_FLAG_SIZE);
            __asm volatile("csrw pmpcfg0, %0"
                           :
                           : "r"(cfg));
            break;

        case 4 ... 7:
            __asm volatile("csrr %0, pmpcfg1"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= ~(mask << (offset * ENTRY_FLAG_SIZE));
            cfg |= attr << (offset * ENTRY_FLAG_SIZE);
            __asm volatile("csrw pmpcfg1, %0"
                           :
                           : "r"(cfg));
            break;

        case 8 ... 11:
            __asm volatile("csrr %0, pmpcfg2"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= ~(mask << (offset * ENTRY_FLAG_SIZE));
            cfg |= attr << (offset * ENTRY_FLAG_SIZE);
            __asm volatile("csrw pmpcfg2, %0"
                           :
                           : "r"(cfg));
            break;

        case 12 ... 15:
            __asm volatile("csrr %0, pmpcfg3"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= ~(mask << (offset * ENTRY_FLAG_SIZE));
            cfg |= attr << (offset * ENTRY_FLAG_SIZE);
            __asm volatile("csrw pmpcfg3, %0"
                           :
                           : "r"(cfg));
            break;

        default:
            break;
    }

#elif (__riscv_xlen == 64)

    switch (i) {
        case 0 ... 7:
            __asm volatile("csrr %0, pmpcfg0"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= (~(mask << (offset * ENTRY_FLAG_SIZE)));
            cfg |= (attr << (offset * ENTRY_FLAG_SIZE));
            __asm volatile("csrw pmpcfg0, %0"
                           :
                           : "r"(cfg));
            break;

        case 8 ... 15:
            __asm volatile("csrr %0, pmpcfg2"
                           : "=r"(cfg));
            offset = i % ENTRY_IN_CFG_REG;
            cfg &= ~(mask << (offset * ENTRY_FLAG_SIZE));
            cfg |= attr << (offset * ENTRY_FLAG_SIZE);
            __asm volatile("csrw pmpcfg2, %0"
                           :
                           : "r"(cfg));
            break;

        default:
            break;
    }

#else
#error "XLEN of riscv not supported"
#endif
}

static uint32_t pmp_get_config(uintptr_t e)
{
    uintptr_t cfg = 0;
    uint32_t offset = 0;

#if (__riscv_xlen == 32)

    switch (e) {
        case 0 ... 3:
            __asm volatile("csrr %0, pmpcfg0"
                           : "=r"(cfg));
            break;

        case 4 ... 7:
            __asm volatile("csrr %0, pmpcfg1"
                           : "=r"(cfg));
            break;

        case 8 ... 11:
            __asm volatile("csrr %0, pmpcfg2"
                           : "=r"(cfg));
            break;

        case 12 ... 15:
            __asm volatile("csrr %0, pmpcfg3"
                           : "=r"(cfg));
            break;

        default:
            break;
    }

#elif (__riscv_xlen == 64)

    switch (e) {
        case 0 ... 7:
            __asm volatile("csrr %0, pmpcfg0"
                           : "=r"(cfg));
            break;

        case 8 ... 15:
            __asm volatile("csrr %0, pmpcfg2"
                           : "=r"(cfg));
            break;

        default:
            break;
    }

#else
#error "XLEN of riscv not supported"
#endif

    offset = e % ENTRY_IN_CFG_REG;
    cfg >>= (offset * ENTRY_FLAG_SIZE);

    return cfg & ENTRY_FLAG_MASK;
}

pmp_status_type_e rvpmp_fill_entry(const pmp_config_entry_t *entry, uintptr_t i, uintptr_t force)
{
    uintptr_t am = 0;
    uintptr_t attr = 0;
    uintptr_t pa = 0;
    pmp_status_type_e ret = PMP_STATUS_OK;
    uint32_t cfg;

    /* check entry */
    cfg = pmp_get_config(i);
    if (cfg & ENTRY_FLAG_M_MODE_L) {
        return PMP_STATUS_DENIED;
    } else if ((cfg & ENTRY_FLAG_ADDR_MASK) && (!force)) {
        return PMP_STATUS_BUSY;
    }

    attr = entry->entry_flag;
    pa = entry->entry_pa_base;

    am = entry->entry_flag & ENTRY_FLAG_ADDR_MASK;

    switch (am) {
        case ENTRY_FLAG_ADDR_TOR:
            pa >>= 2;
            break;

        case ENTRY_FLAG_ADDR_NAPOT:
            /* rule of NAPOT */
            if (pa & (entry->entry_pa_length - 1))
                ret = PMP_STATUS_INVALID;
            pa |= (entry->entry_pa_length - 1) >> 1;
            pa >>= 2;
            break;

        default:
            attr = 0;
            ret = PMP_STATUS_UNSUPPORTED;
            break;
    }

    if (PMP_STATUS_OK == ret)
        rvpmp_reg_write(i, attr, pa);

    return ret;
}

pmp_status_type_e rvpmp_init(const pmp_config_entry_t *entry, uintptr_t n)
{
    uintptr_t i = 0;
    pmp_status_type_e ret = PMP_STATUS_OK;

    __asm volatile ("fence":::"memory");

    for (; i < n; i++) {
        ret = rvpmp_fill_entry(&entry[i], i, 0);
        if (PMP_STATUS_OK != ret)
            break;
    }

    __asm volatile ("fence":::"memory");

    return ret;
}
