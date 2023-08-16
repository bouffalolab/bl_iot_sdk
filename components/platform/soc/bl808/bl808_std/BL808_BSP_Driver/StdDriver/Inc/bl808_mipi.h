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
#ifndef __BL808_MIPI_H__
#define __BL808_MIPI_H__

#include <bl808_comm_mm.h>
#include <mipi_reg.h>

typedef enum {
    MIPI_RX_1_LANE = 0,
    MIPI_RX_2_LANE = 1,
} MIPI_RX_LANE_NUM_E;

typedef enum {
    MIPI_GENERIC_ERR    = 1 << 0,
    MIPI_LANE_MERGE_ERR = 1 << 1,
    MIPI_ECC_ERR        = 1 << 2,
    MIPI_CRC_ERR        = 1 << 3,
} MIPI_INTR_E;

typedef struct {
    uint32_t           dvp_vc_num;
    MIPI_RX_LANE_NUM_E lane_num;
    BL_Fun_Type        unpack_en;
    BL_Fun_Type        sync_sp_en;
    BL_Fun_Type        data_bit_inv_en;
} MIPI_CFG_S;

void MIPI_Init();
void MIPI_Config(MIPI_CFG_S* Cfg);
void MIPI_Set_State(BL_Fun_Type state);
#endif /* __BL808_MIPI_H__ */