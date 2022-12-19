/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <bl808_glb.h>
#include <bl808_psram_ctrl.h>
#include "bl_psram.h"

/**
 ****************************************************************************************
 *
 * @file bl_psram.c
 * Copyright (C) Bouffalo Lab 2016-2018
 *
 ****************************************************************************************
 */
int ATTR_VRAM_SECTION bl_psram_init(GLB_PSRAM_CLK_Type psramClk)
{
    PSRAM_RLatency_Type r_latency;
    PSRAM_WLatency_Type w_latency;

    switch (psramClk)
    {
        case GLB_PSRAM_CLK_BCLK:
            r_latency = PSRAM_3_CLOCKS_RLATENCY;    /* 66M */
            w_latency = PSRAM_3_CLOCKS_WLATENCY;    /* 66M */
            break;
        case GLB_PSRAM_CLK_240M:
            r_latency = PSRAM_5_CLOCKS_RLATENCY;    /* 133M */
            w_latency = PSRAM_5_CLOCKS_WLATENCY;    /* 133M */
            break;
        case GLB_PSRAM_CLK_320M:
            r_latency = PSRAM_6_CLOCKS_RLATENCY;    /* 166M */
            w_latency = PSRAM_6_CLOCKS_WLATENCY;    /* 166M */
            break;
        case GLB_PSRAM_CLK_400M:
            r_latency = PSRAM_7_CLOCKS_RLATENCY;    /* 200M */
            w_latency = PSRAM_7_CLOCKS_WLATENCY;    /* 200M */
            break;
        default:
            r_latency = PSRAM_5_CLOCKS_RLATENCY;    /* 133M */
            w_latency = PSRAM_5_CLOCKS_WLATENCY;    /* 133M */
            break;
    }

    /* set PSram latency to match psram clk */
    PSram_Ctrl_APMemory_Cfg_Latency(PSRAM0_ID, r_latency, w_latency);
    PSram_Ctrl_APMemory_Cfg_Latency(PSRAM1_ID, r_latency, w_latency);

    PSram_Ctrl_Set_Output_Delay(PSRAM0_ID);
    PSram_Ctrl_Set_Output_Delay(PSRAM1_ID);

    GLB_Set_PSRAM_CLK(psramClk);
#if 0
#if 0
    PSram_Ctrl_Init(PSRAM_CTRL_X8_MODE,&delayCfg);
#endif
    PSram_Ctrl_WinbX8_Cfg_Set(&psramCfg);

#if 1
#if 0
    PSram_Cache_Enable(0x00);
#else
    *(uint32_t*)0x40000060 = 0x0400000;
    *(uint32_t*)0x40000060 = 0x0408003 | (1 << 13);
#endif
#endif
#endif
    return 0;
}
