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
#ifndef __BL80X_NPU_H__
#define __BL80X_NPU_H__

#include "bl808_common.h"

enum {
    NPU_IMG_IN_MODE_SOUND = 0,
    NPU_IMG_IN_MODE_YUV400 = 1,
    NPU_IMG_IN_MODE_YUV422 = 2
};

void NPU_Weight_Cfg(uint32_t addr);
void NPU_Image_Cfg(uint32_t addr);
void NPU_Bias_Cfg(uint32_t addr);
void NPU_Instruct_Cfg(uint32_t addr);
void NPU_Output_Cfg(uint32_t addr);
void NPU_Seg_Cfg(uint32_t seg_num);
void NPU_Set_Unsgn_Val(uint32_t unsgn);
void NPU_Set_Relu_Val(uint32_t relu);
void NPU_Set_TF_En(uint32_t en);
void NPU_Set_Img_In_Mode(uint32_t mode);
int NPU_Get_Int(void);
void NPU_Clr_Int(void);
void NPU_Resume(void);
void NPU_Reset(void);
void NPU_Start(void);
void NPU_Stop(void);

#endif /* __BL80X_NPU_H__ */

