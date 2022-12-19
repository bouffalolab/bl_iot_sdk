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
#ifndef __BL808_CLKRST_H__
#define __BL808_CLKRST_H__

#include <bl808_common.h>
#include <bl808_comm_mm.h>

typedef enum {
    SDH_CLK_24_MHZ = 0,
    SDH_CLK_48_MHZ = 1,
    SDH_CLK_96_MHZ = 2,
    SDH_CLK_192_MHZ = 3,
    SDH_CLK_25_MHZ = 4,
    SDH_CLK_50_MHZ = 5,
    SDH_CLK_100_MHZ = 6,
    SDH_CLK_208_MHZ = 7,
} SDH_CLK_SEL_E;

typedef enum {
    SPP_CLK_160MHz = 0,
    SPP_CLK_240MHz = 1,
    SPP_CLK_400MHz = 2,
    SPP_CLK_BCLK = 3,
} SPP_CLK_SEL_E;
void SPP_Clk_Sel(SPP_CLK_SEL_E clk_sel, BL_Fun_Type clk_div_en, int clk_div);
void SPP_SDH_Clk_Sel(SDH_CLK_SEL_E sdh_clk);
void SPP_Get_Clk(uint32_t *spp_clk);
void SPP_Sensor_Reset(void);
void SPP_Disable(void);
void SPP_Enable(void);
void CLKRST_ResetSPPTSrc(void);
void CLKRST_ResetHdmiTSrc(void);
void CLKRST_DVP2AXI_SW_Reset(DVP2AXI_Port_Type dvp2axi);
void CLKRST_H264_ENC_SW_Reset(void);
void CLKRST_MJPEG_ENC_SW_Reset(void);
void CLKRST_DMA_SW_Reset(void);
void CLKRST_Set_PDM_CLK(uint8_t id, uint8_t enable ,uint8_t clkDiv);
void CLKRST_H264_ENC_CLK_Sel(uint8_t clk, uint8_t div);
void CLKRST_H264_ENC_CLK_En(uint8_t en);
void CLKRST_NPU_SW_Reset(void);
void CLKRST_NPU_CLK_Sel(uint8_t clk);
void CLKRST_NPU_CLK_En(uint8_t en);

#endif /* __BL808_CLKRST_H__ */
