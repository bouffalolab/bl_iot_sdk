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
#include "bl808.h"
#include "bl808_clock.h"
#include "bl808_glb.h"
#include "bl808_ef_cfg.h"
#ifdef BOOTROM
#include "bflb_bootrom.h"
#endif

#define BL808_B0 (0x0)
#define BL808_B1 (0x1)
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSTEM_CLOCK (32000000UL)
uintptr_t g_system_clock = SYSTEM_CLOCK;

/*----------------------------------------------------------------------------
  System initialization function
 *----------------------------------------------------------------------------*/

void System_BOR_Init(void)
{
    //HBN_BOR_CFG_Type borCfg = {1/* pu_bor */, 0/* irq_bor_en */, 1/* bor_vth */, 1/* bor_sel */};
    //HBN_Set_BOR_Cfg(&borCfg);
}

void System_Core_Clock_Set(BL_System_Clock_Type type, uint32_t clock)
{
    Clock_Cfg_Type *pClk = (Clock_Cfg_Type *)SYS_CLOCK_CFG_ADDR;

    CHECK_PARAM(IS_BL_SYSTEM_CLOCK_TYPE(type));

    if (type < BL_SYSTEM_CLOCK_MAX) {
        pClk->systemClock[type] = clock;
        pClk->magic = SYS_CLOCK_CFG_MAGIC;
    }
}

void System_Init(void)
{
    uintptr_t tmpVal = 0;
#ifdef DUALCORE
    while ((BL_RD_WORD(IPC_SYNC_ADDR1) != IPC_SYNC_FLAG) ||
           (BL_RD_WORD(IPC_SYNC_ADDR2) != IPC_SYNC_FLAG)) {
        // clang-format off
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        __NOP(); __NOP(); __NOP(); __NOP();
        // clang-format on
        /* if cache is off, comment this and this api need to start load itcm*/
        // L1C_DCache_Invalid_By_Addr(IPC_SYNC_ADDR1, 8);
    };
    /* clear this flags for system reboot */
    BL_WR_WORD(IPC_SYNC_ADDR1, 0x0);
    BL_WR_WORD(IPC_SYNC_ADDR2, 0x0);
#endif
    /* turn on cache to speed up boot sequence */
    csi_icache_enable();
    csi_dcache_enable();
    /* enable I/D Cache preload. */
    tmpVal = __get_MHINT();
    tmpVal |= (1 << 8) | (1 << 2);
    /* clear AMR */
    tmpVal &= (~0x18);
    __set_MHINT(tmpVal);
    __DSB();

    /* init bor for all platform */
    System_BOR_Init();
}

void System_Post_Init(void)
{
    /* fix amr setting */
    uintptr_t tmpVal = 0;
    Efuse_Chip_Info_Type chip_info;
    EF_Ctrl_Get_Chip_Info(&chip_info);
    /* if not B0 enable AMR */
    if (chip_info.chipInfo != BL808_B0) {
        tmpVal = __get_MHINT();
        tmpVal |= (1 << 3);
        __set_MHINT(tmpVal);
    }

    System_Interrupt_Init();

    /* global IRQ enable */
    __enable_irq();
}

int32_t drv_get_cpu_id(void)
{
    return __get_MHARTID();
}

int32_t drv_get_cpu_freq(int32_t idx)
{
    return g_system_clock;
}

#if defined(DUAL_CORE)
extern void Reset_Handler(void);
#endif
