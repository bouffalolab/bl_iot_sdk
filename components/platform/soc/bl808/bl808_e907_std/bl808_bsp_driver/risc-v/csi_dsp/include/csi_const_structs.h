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

/******************************************************************************
 * @file     csi_const_structs.h
 * @brief    Constant structs that are initialized for user convenience.
 * @version  V1.0
 * @date     Feb. 2020
 ******************************************************************************/


#ifndef _RISCV_CONST_STRUCTS_H
#define _RISCV_CONST_STRUCTS_H

#include "csi_math.h"
#include "csi_common_tables.h"

extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix4_fast_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix2_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len16;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len32;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len64;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len128;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len256;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len512;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len1024;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len2048;
extern const csi_cfft_instance_f32 csi_cfft_radix4_sR_f32_len4096;

extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len16 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len32 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len64 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len128 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len256 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len512 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len1024 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len2048 ;
extern const csi_cfft_instance_f32 csi_cfft_sR_f32_len4096 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len16 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len32 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len64 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len128 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len256 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len512 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len1024 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len2048 ;
extern const csi_cfft_instance_q31 csi_cfft_sR_q31_len4096 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len16 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len32 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len64 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len128 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len256 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len512 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len1024 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len2048 ;
extern const csi_cfft_instance_q15 csi_cfft_sR_q15_len4096 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len32 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len64 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len128 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len256 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len512 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len1024 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len2048 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len4096 ;
extern const csi_rfft_fast_instance_f32 csi_rfft_sR_f32_len8192 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len32 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len64 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len128 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len256 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len512 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len1024 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len2048 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len4096 ;
extern const csi_rfft_instance_q31 csi_rfft_sR_q31_len8192 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len32 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len64 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len128 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len256 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len512 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len1024 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len2048 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len4096 ;
extern const csi_rfft_instance_q15 csi_rfft_sR_q15_len8192 ;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len32;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len64;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len128;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len256;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len512;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len1024;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len2048;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len4096;
extern const csi_rfft_instance_f32 csi_inv_rfft_sR_f32_len8192;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len32;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len64;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len128;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len256;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len512;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len1024;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len2048;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len4096;
extern const csi_rfft_instance_q31 csi_inv_rfft_sR_q31_len8192;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len32;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len64;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len128;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len256;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len512;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len1024;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len2048;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len4096;
extern const csi_rfft_instance_q15 csi_inv_rfft_sR_q15_len8192;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len128;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len512;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len2048;
extern const csi_dct4_instance_q31 csi_dct4_sR_q31_len8192;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len128;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len512;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len2048;
extern const csi_dct4_instance_q15 csi_dct4_sR_q15_len8192;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len128;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len512;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len2048;
extern const csi_dct4_instance_f32 csi_dct4_sR_f32_len8192;

#endif
