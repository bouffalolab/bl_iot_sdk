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
#include <bl808_pds.h>
#include <bl808_glb.h>
#include <bl808_glb_gpio.h>
#include <mm_misc_reg.h>
#include <core_rv32.h>

/* FIXME: Use std driver */
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
    MMSYS_REL_VRAM_0_SPP_64 = 0,
    MMSYS_REL_VRAM_64_SPP_0 = 1,
}MMSYS_VRAM_SPP_SRAM_Type;

typedef struct {
    MMSYS_VRAM_L2_SRAM_Type  l2sram;
    MMSYS_VRAM_PFH_SRAM_Type pfh;
    MMSYS_VRAM_APU_SRAM_Type apu;
    MMSYS_VRAM_SPP_SRAM_Type spp;
}MMSYS_VRAM_Ctrl_Cfg;

/* 0x50 : vram_ctrl */
#define MMSYS_MISC_VRAM_CTRL_OFFSET                             (0x50)
#define MMSYS_MISC_REG_SYSRAM_SET                               MMSYS_MISC_REG_SYSRAM_SET
#define MMSYS_MISC_REG_SYSRAM_SET_POS                           (0U)
#define MMSYS_MISC_REG_SYSRAM_SET_LEN                           (1U)
#define MMSYS_MISC_REG_SYSRAM_SET_MSK                           (((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS)
#define MMSYS_MISC_REG_SYSRAM_SET_UMSK                          (~(((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS))
#define MMSYS_MISC_REG_PF_SRAM_REL                              MMSYS_MISC_REG_PF_SRAM_REL
#define MMSYS_MISC_REG_PF_SRAM_REL_POS                          (1U)
#define MMSYS_MISC_REG_PF_SRAM_REL_LEN                          (2U)
#define MMSYS_MISC_REG_PF_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS)
#define MMSYS_MISC_REG_PF_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS))
#define MMSYS_MISC_REG_L2_SRAM_REL                              MMSYS_MISC_REG_L2_SRAM_REL
#define MMSYS_MISC_REG_L2_SRAM_REL_POS                          (4U)
#define MMSYS_MISC_REG_L2_SRAM_REL_LEN                          (1U)
#define MMSYS_MISC_REG_L2_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS)
#define MMSYS_MISC_REG_L2_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS))
#define MMSYS_MISC_REG_SPP_SRAM_REL                             MMSYS_MISC_REG_SPP_SRAM_REL
#define MMSYS_MISC_REG_SPP_SRAM_REL_POS                         (6U)
#define MMSYS_MISC_REG_SPP_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_SPP_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_SPP_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_SPP_SRAM_REL_POS)
#define MMSYS_MISC_REG_SPP_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_SPP_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_SPP_SRAM_REL_POS))
#define MMSYS_MISC_REG_APU_SRAM_REL                             MMSYS_MISC_REG_APU_SRAM_REL
#define MMSYS_MISC_REG_APU_SRAM_REL_POS                         (7U)
#define MMSYS_MISC_REG_APU_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_APU_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS)
#define MMSYS_MISC_REG_APU_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS))

#define MMSYS_MISC_BASE             ((uint32_t)0x30000000)            /*!< MMSys misc base address */

static void MMSYS_VRAM_Ctrl(MMSYS_VRAM_Ctrl_Cfg *cfg)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_WORD(MMSYS_MISC_BASE + 0x50);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_L2_SRAM_REL,  cfg->l2sram);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_PF_SRAM_REL,  cfg->pfh);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_APU_SRAM_REL, cfg->apu);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_SPP_SRAM_REL, cfg->spp);

    BL_WR_WORD(MMSYS_MISC_BASE + 0x50, tmpVal);

    tmpVal=BL_RD_WORD(MMSYS_MISC_BASE + 0x50);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_REG_SYSRAM_SET);
    BL_WR_WORD(MMSYS_MISC_BASE + 0x50, tmpVal);
}

void l2_sram_vram_config(void)
{
    MMSYS_VRAM_Ctrl_Cfg cfg;
    cfg.l2sram = MMSYS_REL_VRAM_64_L2_0;
    cfg.pfh    = MMSYS_REL_VRAM_0_PFH_192;
    cfg.apu    = MMSYS_REL_VRAM_0_APU_128;
    cfg.spp    = MMSYS_REL_VRAM_0_SPP_64;

    MMSYS_VRAM_Ctrl(&cfg);
}
