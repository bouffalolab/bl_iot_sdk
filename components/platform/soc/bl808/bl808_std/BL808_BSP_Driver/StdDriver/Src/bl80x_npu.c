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
#include "bl80x_npu.h"
#include "npu_reg.h"

void NPU_Init(void)
{

}

void NPU_Weight_Cfg(uint32_t addr)
{
    BL_WR_REG(NPU_BASE, NPU_BLAI_WEIGHT_ADDR, addr);
}

void NPU_Bias_Cfg(uint32_t addr)
{
    BL_WR_REG(NPU_BASE, NPU_BLAI_BIAS_ADDR, addr);
}

void NPU_Instruct_Cfg(uint32_t addr)
{
    BL_WR_REG(NPU_BASE, NPU_BLAI_INST_ADDR, addr);
}

void NPU_Image_Cfg(uint32_t addr)
{
    BL_WR_REG(NPU_BASE, NPU_APU_DM0_ADDR, addr);
}

void NPU_Seg_Cfg(uint32_t seg_num)
{
    BL_WR_REG(NPU_BASE, NPU_APU_DM1_ADDR, seg_num);
}

void NPU_Set_Unsgn_Val(uint32_t unsgn)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BALI_GENERAL_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, NPU_REG_IMGI_UNSGN, unsgn);
    BL_WR_REG(NPU_BASE, NPU_BALI_GENERAL_CFG, tmpVal);
}

void NPU_Set_Img_In_Mode(uint32_t mode)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BALI_GENERAL_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, NPU_REG_IMG_IN_MODE, mode);
    BL_WR_REG(NPU_BASE, NPU_BALI_GENERAL_CFG, tmpVal);
}

void NPU_Set_Relu_Val(uint32_t relu)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, NPU_REG_RELU_N, relu);
    BL_WR_REG(NPU_BASE, NPU_BLAI_INT_CFG, tmpVal);
}

void NPU_Set_TF_En(uint32_t en)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_TF_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, NPU_REG_TENFLOW_EN, en);
    BL_WR_REG(NPU_BASE, NPU_BLAI_TF_CFG0, tmpVal);
}

int NPU_Get_Int(void)
{
    return BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG) & (1 << 9);
}

void NPU_Clr_Int(void)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, NPU_REG_INT_CLR);
    BL_WR_REG(NPU_BASE, NPU_BLAI_INT_CFG, tmpVal);
}

void NPU_Resume(void)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, NPU_REG_BLAI_RESUME);
    BL_WR_REG(NPU_BASE, NPU_BLAI_INT_CFG, tmpVal);
}

void NPU_Start(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, NPU_REG_BLAI_START);
    BL_WR_REG(NPU_BASE, NPU_BLAI_INT_CFG, tmpVal);
}

void NPU_Stop(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(NPU_BASE, NPU_BLAI_INT_CFG);
    tmpVal = BL_SET_REG_BIT(tmpVal, NPU_REG_BLAI_STOP);
    BL_WR_REG(NPU_BASE, NPU_BLAI_INT_CFG, tmpVal);
}
