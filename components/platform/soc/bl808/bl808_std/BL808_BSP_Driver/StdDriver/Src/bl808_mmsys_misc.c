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
#include <bl808_mmsys_misc.h>


#define MMSYS_DUMMY_WAIT       {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}

void ATTR_TCM_SECTION MMSYS_Enable_CM4_Cache(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_L1C_CONFIG);
    tmpVal=BL_SET_REG_BIT(tmpVal, MMSYS_MISC_L1C_BYPASS);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_L1C_CONFIG, tmpVal);

    tmpVal = BL_CLR_REG_BIT(tmpVal, MMSYS_MISC_L1C_BYPASS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_L1C_WAY_DIS, 0);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_L1C_CNT_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_L1C_EARLY_RESP_DIS);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_L1C_AUX_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_L1C_RANGE, 0xFFFFFFFF);     /* all L1 address cacheable */
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_L1C_CONFIG, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_L1C_CACHEABLE);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_L1C_CONFIG, tmpVal);
    MMSYS_DUMMY_WAIT;
}

void MMSYS_Set_SW_GPIO(uint8_t pos, uint8_t value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_DUMMY);

    if(value > 0) {
        tmpVal |= (1<<pos);
    } else {
        tmpVal &= (~(1<<pos));
    }

    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_DUMMY, tmpVal);
}

void MMSYS_VRAM_Ctrl(MMSYS_VRAM_Ctrl_Cfg *cfg)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_VRAM_CTRL);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_L2_SRAM_REL,  cfg->l2sram);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_PF_SRAM_REL,  cfg->pfh);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_APU_SRAM_REL, cfg->apu);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_ISP_SRAM_REL, cfg->isp);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_VRAM_CTRL, tmpVal);

    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_VRAM_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, MMSYS_MISC_REG_SYSRAM_SET);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_VRAM_CTRL, tmpVal);
}