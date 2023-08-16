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
#include <stdint.h>
#include "bl808_glb.h"
#include <core_rv64.h>

#define __STARTUP_CLEAR_BSS 1

/*----------------------------------------------------------------------------
  Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __itcm_load_addr;
extern uint32_t __dtcm_load_addr;
extern uint32_t __system_ram_load_addr;
extern uint32_t __ram_load_addr;

extern uint32_t __text_code_start__;
extern uint32_t __text_code_end__;
extern uint32_t __tcm_code_start__;
extern uint32_t __tcm_code_end__;
extern uint32_t __tcm_data_start__;
extern uint32_t __tcm_data_end__;
extern uint32_t __system_ram_data_start__;
extern uint32_t __system_ram_data_end__;
extern uint32_t __ram_data_start__;
extern uint32_t __ram_data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __noinit_data_start__;
extern uint32_t __noinit_data_end__;

extern uint32_t __StackTop;
extern uint32_t __StackLimit;
extern uint32_t __HeapBase;
extern uint32_t __HeapLimit;

//extern uint32_t __copy_table_start__;
//extern uint32_t __copy_table_end__;
//extern uint32_t __zero_table_start__;
//extern uint32_t __zero_table_end__;

#if defined(DUAL_CORE)
volatile uintptr_t ATTR_MP_SHARE_DATA_SECTION master_copy_done = 0;
#endif

void start_load(void)
{
    uint32_t *pSrc, *pDest;
    uint32_t *pTable __attribute__((unused));

    /* Copy ITCM code */
    pSrc = &__itcm_load_addr;
    pDest = &__tcm_code_start__;

    for (; pDest < &__tcm_code_end__;) {
        *pDest++ = *pSrc++;
    }

    /* Copy DTCM code */
    pSrc = &__dtcm_load_addr;
    pDest = &__tcm_data_start__;

    for (; pDest < &__tcm_data_end__;) {
        *pDest++ = *pSrc++;
    }

    /* BF Add system RAM data copy */
    pSrc = &__system_ram_load_addr;
    pDest = &__system_ram_data_start__;

    for (; pDest < &__system_ram_data_end__;) {
        *pDest++ = *pSrc++;
    }

    /* BF Add OCARAM data copy */
    pSrc = &__ram_load_addr;
    pDest = &__ram_data_start__;

    for (; pDest < &__ram_data_end__;) {
        *pDest++ = *pSrc++;
    }

#ifdef __STARTUP_CLEAR_BSS
    /*  Single BSS section scheme.
	 *
	 *  The BSS section is specified by following symbols
	 *    __bss_start__: start of the BSS section.
	 *    __bss_end__: end of the BSS section.
	 *
	 *  Both addresses must be aligned to 4 bytes boundary.
	 */
    pDest = &__bss_start__;

    for (; pDest < &__bss_end__;) {
        *pDest++ = 0ul;
    }

#endif

    csi_dcache_clean();

#if defined(DUAL_CORE)
    __DSB();

    if (GLB_CORE_ID_D0 == GLB_Get_Core_Type()) {
        master_copy_done = 0xDEAD5501;
    }

    __DSB();
#endif
}
