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
#ifndef __BL808_MMSYS_MISC_H__
#define __BL808_MMSYS_MISC_H__

#include <bl808_common.h>
#include <mmsys_misc_reg.h>


typedef enum {
    MMSYS_REL_VRAM_64_L2_0  = 0,
    MMSYS_REL_VRAM_0_L2_64 = 1,
}MMSYS_VRAM_L2_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_PFH_192  = 0,
    MMSYS_REL_VRAM_64_PFH_128 = 1,
    MMSYS_REL_VRAM_128_PFH_64 = 2,
    MMSYS_REL_VRAM_192_PFH_0  = 3
}MMSYS_VRAM_PFH_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_APU_128 = 0,
    MMSYS_REL_VRAM_128_APU_0 = 1,
}MMSYS_VRAM_APU_SRAM_Type;

typedef enum {
    MMSYS_REL_VRAM_0_ISP_64 = 0,
    MMSYS_REL_VRAM_64_ISP_0 = 1,
}MMSYS_VRAM_ISP_SRAM_Type;

typedef struct {
    MMSYS_VRAM_L2_SRAM_Type  l2sram;
    MMSYS_VRAM_PFH_SRAM_Type pfh;
    MMSYS_VRAM_APU_SRAM_Type apu;
    MMSYS_VRAM_ISP_SRAM_Type isp;
}MMSYS_VRAM_Ctrl_Cfg;

void MMSYS_Enable_CM4_Cache(void);
void MMSYS_Set_SW_GPIO(uint8_t pos, uint8_t value);
void MMSYS_VRAM_Ctrl(MMSYS_VRAM_Ctrl_Cfg *cfg);

#endif /* __BL808_MMSYS_MISC_H__ */

