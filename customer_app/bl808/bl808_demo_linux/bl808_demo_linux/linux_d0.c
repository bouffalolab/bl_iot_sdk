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
#ifdef CPU_D0

#include <stdint.h>

#include "linux_cfg.h"
#include "bl808_demo_linux.h"

void d0_init_clk(void)
{
    /* Todo: move to platform init segment */
    uint32_t mm_clk_ctrl_cpu = *(volatile uint32_t *)0x30007000;
    mm_clk_ctrl_cpu = mm_clk_ctrl_cpu | (3 << 13); // set bclk to 160M
    mm_clk_ctrl_cpu = (mm_clk_ctrl_cpu & ~(0x3 << 4)) | (2 << 4); // set uart clk to 32M
    *(volatile uint32_t *)0x30007000 = mm_clk_ctrl_cpu;
}

void d0_init_linux(void)
{
    uint64_t tmp, tmp2;
    tmp = 0x30013;
    asm volatile("csrw mcor, %0"::"r"(tmp));
    tmp = 0x17f;
    asm volatile("csrw mhcr, %0"::"r"(tmp));
    tmp = 0x638000;
    asm volatile("csrw mxstatus, %0"::"r"(tmp));
    tmp = 0x4104;
    asm volatile("csrw mhint, %0"::"r"(tmp));

    tmp = 0xe0000000 >> 2;
    asm volatile("csrw pmpaddr0, %0"::"r"(tmp));
    tmp = 0xe0000000 >> 2 | ((0x8000000 - 1) >> 3);
    asm volatile("csrw pmpaddr1, %0"::"r"(tmp));
    tmp = 0x20000000 >> 2 | ((0x10000000 - 1) >> 3);
    asm volatile("csrw pmpaddr2, %0"::"r"(tmp));
    tmp = 0xfffc0000 >> 2 | ((0x2000 - 1) >> 3);
    asm volatile("csrw pmpaddr3, %0"::"r"(tmp));
    tmp = 0x00000000 >> 2 | ((0x10000000 - 1) >> 3);
    asm volatile("csrw pmpaddr4, %0"::"r"(tmp));
    tmp = 0xffffffffff >> 2;
    asm volatile("csrw pmpaddr5, %0"::"r"(tmp));
    tmp = 0x88989b9b9b8f;
    asm volatile("csrw pmpcfg0, %0"::"r"(tmp));

    tmp = DTB_ADDR;
    tmp2 = OPENSBI_ADDR;
    asm volatile("mv a1, %0\n\t"
            "jalr %1"
            ::"r"(tmp), "r"(tmp2));
}

#endif // CPU_D0
