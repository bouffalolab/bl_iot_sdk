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
 * @file     csi_core.h
 * @brief    CSI Core Layer Header File
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CORE_H_
#define _CORE_H_

#include <stdint.h>

#if defined(__CK801__) || defined(__E801__)
#include <core_801.h>
#elif defined(__CK802__) || defined(__E802__) || defined(__E802T__) || defined(__S802__) || defined(__S802T__)
#include <core_802.h>
#elif defined(__CK804__) || defined(__E804D__) || defined(__E804DT__) || defined(__E804F__) || defined(__E804FT__) || defined(__E804DF__) || defined(__E804DFT__)
#include <core_804.h>
#elif defined(__CK803__) || defined(__E803__) || defined(__E803T__) || defined(__S803__) || defined(__S803T__)
#include <core_803.h>
#elif defined(__CK805__) || defined(__I805__) || defined(__I805F__)
#include <core_805.h>
#elif defined(__CK610__)
#include <core_ck610.h>
#elif defined(__CK810__) || defined(__C810__) || defined(__C810T__) || defined(__C810V__) || defined(__C810VT__)
#include <core_810.h>
#elif defined(__CK807__) || defined(__C807__) || defined(__C807F__) || defined(__C807FV__) || defined(__R807__)
#include <core_807.h>
#elif defined(__riscv) && defined(CONFIG_CSKY_CORETIM)
#include <core_rv32_old.h>
#elif defined(__riscv)
#if (__riscv_xlen == 32)
#include <core_rv32.h>
#elif (__riscv_xlen == 64)
#include <core_rv64.h>
#else
#error "XLEN of riscv not supported"
#endif
#endif

#ifdef __riscv
#if (__riscv_xlen == 32)
#include <csi_rv32_gcc.h>
#elif (__riscv_xlen == 64)
#include <csi_rv64_gcc.h>
#else
#error "XLEN of riscv not supported"
#endif
#else
#include <csi_gcc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CORE_H_ */
