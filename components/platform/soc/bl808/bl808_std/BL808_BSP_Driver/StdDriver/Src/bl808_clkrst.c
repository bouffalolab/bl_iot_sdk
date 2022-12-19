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
#include <bl808.h>
#include <clkrst_reg.h>

#include <bl808_clkrst.h>


//FIXME TODO spp clk value should be define accrording to SPP_Clk_Sel
const uint32_t SPP_CLK_SET[] =
    {80000000, 120000000, 200000000};


void Global_Reset(void)
{
    uint32_t tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET);

    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_CTRL_A5_SCU_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);

    BL808_Delay_MS(1);

    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_CTRL_A5_SCU_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);
}

void SPP_Clk_Sel(SPP_CLK_SEL_E clk_sel, BL_Fun_Type clk_div_en, int clk_div)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->spp_dp_clk.BF.reg_spp_clk_sel = clk_sel;
    clkrst_reg->spp_dp_clk.BF.reg_spp_clk_div_en = clk_div_en;
    clkrst_reg->spp_dp_clk.BF.reg_spp_clk_div = clk_div & 0xff;
}

void SPP_Get_Clk(uint32_t *spp_clk)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    /* TODO: check SPP status */

    *spp_clk = SPP_CLK_SET[clkrst_reg->spp_dp_clk.BF.reg_spp_clk_sel];

    if (clkrst_reg->spp_dp_clk.BF.reg_spp_clk_div_en) {
        *spp_clk = (uint32_t)DIV_ROUND(*spp_clk, (clkrst_reg->spp_dp_clk.BF.reg_spp_clk_div + 1));
    }
}

void SPP_SDH_Clk_Sel(SDH_CLK_SEL_E sdh_clk)
{
    uint32_t tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI);

    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_SDH_CLK_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_SDH_CLK_SEL, sdh_clk);

    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI, tmpVal);
}

void SPP_Sensor_Reset(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->image_sensor_ctrl.BF.rg_is_rst_n = 0;   /* pull down the reset pin */
    BL808_Delay_MS(2);                                     /* pull down for 10 ms */
    clkrst_reg->image_sensor_ctrl.BF.rg_is_rst_n = 1;   /* pull up the reset pin */
    BL808_Delay_MS(1);
}

void SPP_Disable(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;
    clkrst_reg->sw_reset_spp_sub.BF.swrst_spp_main = 1;
}

void SPP_Enable(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;
    clkrst_reg->sw_reset_spp_sub.BF.swrst_spp_main = 0;
}

void CLKRST_ResetSPPTSrc(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_SWRST_SPP_TSRC);
    BL_WR_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB, tmpVal);

    BL808_Delay_MS(1);

    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_SWRST_SPP_TSRC);
    BL_WR_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB, tmpVal);
}

void CLKRST_ResetHdmiTSrc(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_SWRST_HDMI_TSRC);
    BL_WR_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB, tmpVal);

    BL808_Delay_MS(1);

    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_SWRST_HDMI_TSRC);
    BL_WR_REG(CLKRST_BASE, CLKRST_SW_RESET_SPP_SUB, tmpVal);
}

void CLKRST_DVP2AXI_SW_Reset(DVP2AXI_Port_Type dvp2axi)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    if (dvp2axi == DVP2AXI_A) {
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busA = 1;
        BL808_Delay_MS(1);
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busA = 0;
    } else if (dvp2axi == DVP2AXI_B) {
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busB = 1;
        BL808_Delay_MS(1);
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busB = 0;
    } else if (dvp2axi == DVP2AXI_C) {
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busC = 1;
        BL808_Delay_MS(1);
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busC = 0;
    } else if (dvp2axi == DVP2AXI_D) {
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busD = 1;
        BL808_Delay_MS(1);
        clkrst_reg->sw_reset_spp_sub.BF.swrst_dvp2busD = 0;
    }
}

void CLKRST_H264_ENC_SW_Reset(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->sw_reset_codec_sub.BF.swrst_h264 = 1;   /* pull up the reset pin */
    BL808_Delay_MS(1);                                       /* pull down for 1 ms */
    clkrst_reg->sw_reset_codec_sub.BF.swrst_h264 = 0;   /* pull down the reset pin */
}

void CLKRST_H264_ENC_CLK_Sel(uint8_t clk, uint8_t div)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->codec_clk.BF.reg_h264_clk_sel = clk;
    clkrst_reg->codec_clk.BF.reg_h264_clk_div = div;
}

void CLKRST_H264_ENC_CLK_En(uint8_t en)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->codec_clk.BF.reg_h264_clk_div_en = en;
}

void CLKRST_NPU_SW_Reset(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->sw_reset_codec_sub.BF.swrst_npu = 1;   /* pull up the reset pin */
    BL808_Delay_MS(1);                                       /* pull down for 1 ms */
    clkrst_reg->sw_reset_codec_sub.BF.swrst_npu = 0;   /* pull down the reset pin */
}

void CLKRST_NPU_CLK_Sel(uint8_t clk)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->mm_clk_cpu.BF.reg_cnn_clk_sel = clk;   /* pull up the reset pin */
}

void CLKRST_NPU_CLK_En(uint8_t en)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->mm_clk_cpu.BF.reg_cnn_clk_div_en = en;   /* npu cg */
}

void CLKRST_MJPEG_ENC_SW_Reset(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->sw_reset_codec_sub.BF.swrst_mjpeg = 1;   /* pull up the reset pin */
    BL808_Delay_MS(1);                                        /* pull down for 1 ms */
    clkrst_reg->sw_reset_codec_sub.BF.swrst_mjpeg = 0;   /* pull down the reset pin */
}

void CLKRST_DMA_SW_Reset(void)
{
    clkrst_reg_t *clkrst_reg = (clkrst_reg_t*)CLKRST_BASE;

    clkrst_reg->sw_reset_mm_peri.BF.swrst_dma = 1;   /* pull up the reset pin */
    BL808_Delay_MS(1);                                    /* pull down for 1 ms */
    clkrst_reg->sw_reset_mm_peri.BF.swrst_dma = 0;   /* pull down the reset pin */
}

void CLKRST_Set_PDM_CLK(uint8_t id, uint8_t enable ,uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2);

    if(id == 0) {
        if(enable == 1){
            tmpVal=BL_SET_REG_BIT(tmpVal, CLKRST_REG_PDM0_CLK_EN);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PDM0_CLK_DIV, clkDiv);
        }else{
            tmpVal=BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PDM0_CLK_EN);
        }
    } else if (id == 1) {
        if(enable == 1){
            tmpVal=BL_SET_REG_BIT(tmpVal, CLKRST_REG_PDM1_CLK_EN);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PDM1_CLK_DIV, clkDiv);
        }else{
            tmpVal=BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PDM1_CLK_EN);
        }
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2, tmpVal);
}

