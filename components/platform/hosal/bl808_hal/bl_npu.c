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
#include "bl808_common.h"
#include "bl808_clkrst.h"
#include "bl_npu.h"
#include "bl80x_npu.h"

static bool g_bNPUStarted = false;

void bl_npu_ack_irq(void)
{
    NPU_Clr_Int();
}

void bl_npu_layer_setup(uint8_t *inst, uint8_t *weight, uint8_t *bias)
{
    if (inst)
        NPU_Instruct_Cfg((uint32_t) inst);
    if (weight)
        NPU_Weight_Cfg((uint32_t) weight);
    if (bias)
        NPU_Bias_Cfg((uint32_t) bias);
}

void bl_npu_set_input_buffer(uint8_t *buffer, uint32_t seg_size)
{
    NPU_Image_Cfg((uint32_t) buffer);
    NPU_Seg_Cfg(seg_size);
}

void bl_npu_set_net_param(uint8_t unsigned_input, uint8_t relu_n, uint8_t is_tflite)
{
    NPU_Set_Unsgn_Val(unsigned_input);
    NPU_Set_Relu_Val(relu_n);
    NPU_Set_TF_En(is_tflite);
}

void bl_npu_reset_unsign(void)
{
    NPU_Set_Unsgn_Val(0);
}

void bl_npu_start(void)
{
    if (g_bNPUStarted) {
        NPU_Resume();
    } else {
        NPU_Start();
        g_bNPUStarted = true;
    }
}

void bl_npu_stop(void)
{
    NPU_Stop();
    g_bNPUStarted = false;
}

void bl_npu_init(void)
{
    CLKRST_NPU_CLK_Sel(2);
}

void bl_npu_clk_en(int en)
{
    CLKRST_NPU_CLK_En(en);
}

