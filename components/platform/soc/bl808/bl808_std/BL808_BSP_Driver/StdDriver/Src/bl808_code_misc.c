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
#include <bl808_codec_misc.h>
#include <codec_misc_reg.h>

void CODEC_MISC_BLAI_Limit_RD(uint32_t value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CODEC_MISC_BASE, CODEC_MISC_BLAI_LMTR_RD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CODEC_MISC_REG_BLAI_RCMD_CNT, value);
    tmpVal = BL_SET_REG_BIT(tmpVal, CODEC_MISC_REG_BLAI_RCMD_MODE);

    BL_WR_REG(CODEC_MISC_BASE, CODEC_MISC_BLAI_LMTR_RD, tmpVal);
}

void CODEC_MISC_BLAI_Limit_WR(uint32_t value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CODEC_MISC_BASE, CODEC_MISC_BLAI_LMTR_WR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CODEC_MISC_REG_BLAI_WCMD_CNT, value);
    tmpVal = BL_SET_REG_BIT(tmpVal, CODEC_MISC_REG_BLAI_WCMD_MODE);

    BL_WR_REG(CODEC_MISC_BASE, CODEC_MISC_BLAI_LMTR_WR, tmpVal);
}

