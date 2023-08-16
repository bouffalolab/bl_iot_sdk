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
#include "hal_common.h"
#include "bl808_l1c.h"
#include "bl808_glb.h"
#include "bl808_hbn.h"

volatile uint32_t nesting = 0;

void ATTR_TCM_SECTION cpu_global_irq_enable(void)
{
    nesting--;
    if (nesting == 0) {
        __enable_irq();
    }
}

void ATTR_TCM_SECTION cpu_global_irq_disable(void)
{
    __disable_irq();
    nesting++;
}

void hal_por_reset(void)
{
    GLB_SW_POR_Reset();
}

void hal_system_reset(void)
{
    GLB_SW_System_Reset();
}

void hal_cpu_reset(void)
{
    GLB_SW_CPU_Reset();
}

void hal_reboot_config(hal_reboot_cfg_t rbot)
{
    switch(rbot){
        case HAL_REBOOT_AS_BOOTPIN:
            HBN_Set_Hand_Off_Config(0);
            break;
        case HAL_REBOOT_FROM_INTERFACE:
            HBN_Set_Hand_Off_Config(1);
            break;
        case HAL_REBOOT_FROM_MEDIA:
            HBN_Set_Hand_Off_Config(2);
            break;
        default :
            HBN_Set_Hand_Off_Config(0);
            break;
    }
}

void ATTR_TCM_SECTION hal_dcache_clean_all(void)
{
    L1C_DCache_Clean_All();
}

void ATTR_TCM_SECTION hal_dcache_invalid_all(void)
{
    L1C_DCache_Invalid_All();
}

void ATTR_TCM_SECTION hal_dcache_clean_invalid_all(void)
{
    L1C_DCache_Clean_Invalid_All();
}

void ATTR_TCM_SECTION hal_dcache_clean_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr & CACHE_INV_ADDR_Msk;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}

void ATTR_TCM_SECTION hal_dcache_invalidate_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_IPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}

void ATTR_TCM_SECTION hal_dcache_clean_invalidate_byaddr(uintptr_t addr, uint32_t len)
{
    int64_t op_size = len + (uint64_t)addr % 32;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 32;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CIPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
}