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

#include "bl808_psram_ctrl.h"


static const uint32_t psramAddr[2] = {PSRAM0_CTRL_BASE, PSRAM1_CTRL_BASE};


void ATTR_VRAM_SECTION PSram_Ctrl_APMemory_Cfg_Latency(PSRAM_ID_Type id,
    PSRAM_RLatency_Type r_latency, PSRAM_WLatency_Type w_latency)
{
    uint32_t PSRAMx = psramAddr[id];
    uint32_t tmpVal;

    CHECK_PARAM(IS_PSRAM_R_LATENCY_TYPE(r_latency));
    CHECK_PARAM(IS_PSRAM_W_LATENCY_TYPE(w_latency));

    tmpVal = BL_RD_REG(PSRAMx, PSRAM_CTRL_APMEMORY_PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_AP_R_LATENCY_CODE, r_latency);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_AP_W_LATENCY_CODE, w_latency);
    BL_WR_REG(PSRAMx, PSRAM_CTRL_APMEMORY_PSRAM_CONFIGURE, tmpVal);

    /* write mode register 0 (Read Latency Code) */
    tmpVal = BL_RD_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_AP_MR, 0x0);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_CTRL_REG_CONFIG_W_PUSLE);
    BL_WR_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE, tmpVal);

    /* polling until write mode register done */
    while (BL_IS_REG_BIT_SET(BL_RD_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE),
        PSRAM_CTRL_STS_CONFIG_W_DONE) != 1);

    /* write mode register 4 (Write Latency Code) */
    tmpVal = BL_RD_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_AP_MR, 0x4);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_CTRL_REG_CONFIG_W_PUSLE);
    BL_WR_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE, tmpVal);

    /* polling until write mode register done */
    while (BL_IS_REG_BIT_SET(BL_RD_REG(PSRAMx, PSRAM_CTRL_PSRAM_CONFIGURE),
        PSRAM_CTRL_STS_CONFIG_W_DONE) != 1);
}

void ATTR_VRAM_SECTION PSram_Ctrl_Set_Output_Delay(PSRAM_ID_Type id)
{
    uint32_t PSRAMx = psramAddr[id];
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(PSRAMx, PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_DELAY_SEL_O_CLK, 0xFF);     /* 8 delay cell */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N, 0xFF);   /* 8 delay cell */
    BL_WR_REG(PSRAMx, PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL0, tmpVal);
}



/*@} end of group PSRAM_CTRL_Public_Functions */

/*@} end of group PSRAM_CTRL */

/*@} end of group BL60x_Peripheral_Driver */
