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
#ifndef  __SF_CTRL_REG_H__
#define  __SF_CTRL_REG_H__

#include "bl808.h"

/* 0x0 : sf_ctrl_0 */
#define SF_CTRL_0_OFFSET                                        (0x0)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL                            SF_CTRL_SF_CLK_SF_RX_INV_SEL
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS                        (2U)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN                        (1U)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_MSK                        (((1U<<SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_UMSK                       (~(((1U<<SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS))
#define SF_CTRL_SF_CLK_OUT_GATE_EN                              SF_CTRL_SF_CLK_OUT_GATE_EN
#define SF_CTRL_SF_CLK_OUT_GATE_EN_POS                          (3U)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_LEN                          (1U)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_MSK                          (((1U<<SF_CTRL_SF_CLK_OUT_GATE_EN_LEN)-1)<<SF_CTRL_SF_CLK_OUT_GATE_EN_POS)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_UMSK                         (~(((1U<<SF_CTRL_SF_CLK_OUT_GATE_EN_LEN)-1)<<SF_CTRL_SF_CLK_OUT_GATE_EN_POS))
#define SF_CTRL_SF_CLK_OUT_INV_SEL                              SF_CTRL_SF_CLK_OUT_INV_SEL
#define SF_CTRL_SF_CLK_OUT_INV_SEL_POS                          (4U)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_LEN                          (1U)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_MSK                          (((1U<<SF_CTRL_SF_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_OUT_INV_SEL_POS)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_OUT_INV_SEL_POS))
#define SF_CTRL_SF_IF_READ_DLY_N                                SF_CTRL_SF_IF_READ_DLY_N
#define SF_CTRL_SF_IF_READ_DLY_N_POS                            (8U)
#define SF_CTRL_SF_IF_READ_DLY_N_LEN                            (3U)
#define SF_CTRL_SF_IF_READ_DLY_N_MSK                            (((1U<<SF_CTRL_SF_IF_READ_DLY_N_LEN)-1)<<SF_CTRL_SF_IF_READ_DLY_N_POS)
#define SF_CTRL_SF_IF_READ_DLY_N_UMSK                           (~(((1U<<SF_CTRL_SF_IF_READ_DLY_N_LEN)-1)<<SF_CTRL_SF_IF_READ_DLY_N_POS))
#define SF_CTRL_SF_IF_READ_DLY_EN                               SF_CTRL_SF_IF_READ_DLY_EN
#define SF_CTRL_SF_IF_READ_DLY_EN_POS                           (11U)
#define SF_CTRL_SF_IF_READ_DLY_EN_LEN                           (1U)
#define SF_CTRL_SF_IF_READ_DLY_EN_MSK                           (((1U<<SF_CTRL_SF_IF_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF_IF_READ_DLY_EN_POS)
#define SF_CTRL_SF_IF_READ_DLY_EN_UMSK                          (~(((1U<<SF_CTRL_SF_IF_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF_IF_READ_DLY_EN_POS))
#define SF_CTRL_SF_IF_INT                                       SF_CTRL_SF_IF_INT
#define SF_CTRL_SF_IF_INT_POS                                   (16U)
#define SF_CTRL_SF_IF_INT_LEN                                   (1U)
#define SF_CTRL_SF_IF_INT_MSK                                   (((1U<<SF_CTRL_SF_IF_INT_LEN)-1)<<SF_CTRL_SF_IF_INT_POS)
#define SF_CTRL_SF_IF_INT_UMSK                                  (~(((1U<<SF_CTRL_SF_IF_INT_LEN)-1)<<SF_CTRL_SF_IF_INT_POS))
#define SF_CTRL_SF_IF_INT_CLR                                   SF_CTRL_SF_IF_INT_CLR
#define SF_CTRL_SF_IF_INT_CLR_POS                               (17U)
#define SF_CTRL_SF_IF_INT_CLR_LEN                               (1U)
#define SF_CTRL_SF_IF_INT_CLR_MSK                               (((1U<<SF_CTRL_SF_IF_INT_CLR_LEN)-1)<<SF_CTRL_SF_IF_INT_CLR_POS)
#define SF_CTRL_SF_IF_INT_CLR_UMSK                              (~(((1U<<SF_CTRL_SF_IF_INT_CLR_LEN)-1)<<SF_CTRL_SF_IF_INT_CLR_POS))
#define SF_CTRL_SF_IF_INT_SET                                   SF_CTRL_SF_IF_INT_SET
#define SF_CTRL_SF_IF_INT_SET_POS                               (18U)
#define SF_CTRL_SF_IF_INT_SET_LEN                               (1U)
#define SF_CTRL_SF_IF_INT_SET_MSK                               (((1U<<SF_CTRL_SF_IF_INT_SET_LEN)-1)<<SF_CTRL_SF_IF_INT_SET_POS)
#define SF_CTRL_SF_IF_INT_SET_UMSK                              (~(((1U<<SF_CTRL_SF_IF_INT_SET_LEN)-1)<<SF_CTRL_SF_IF_INT_SET_POS))
#define SF_CTRL_SF_IF_32B_ADR_EN                                SF_CTRL_SF_IF_32B_ADR_EN
#define SF_CTRL_SF_IF_32B_ADR_EN_POS                            (19U)
#define SF_CTRL_SF_IF_32B_ADR_EN_LEN                            (1U)
#define SF_CTRL_SF_IF_32B_ADR_EN_MSK                            (((1U<<SF_CTRL_SF_IF_32B_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_32B_ADR_EN_POS)
#define SF_CTRL_SF_IF_32B_ADR_EN_UMSK                           (~(((1U<<SF_CTRL_SF_IF_32B_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_32B_ADR_EN_POS))
#define SF_CTRL_SF_AES_DOUT_ENDIAN                              SF_CTRL_SF_AES_DOUT_ENDIAN
#define SF_CTRL_SF_AES_DOUT_ENDIAN_POS                          (20U)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_LEN                          (1U)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_MSK                          (((1U<<SF_CTRL_SF_AES_DOUT_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_DOUT_ENDIAN_POS)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_UMSK                         (~(((1U<<SF_CTRL_SF_AES_DOUT_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_DOUT_ENDIAN_POS))
#define SF_CTRL_SF_AES_DIN_ENDIAN                               SF_CTRL_SF_AES_DIN_ENDIAN
#define SF_CTRL_SF_AES_DIN_ENDIAN_POS                           (21U)
#define SF_CTRL_SF_AES_DIN_ENDIAN_LEN                           (1U)
#define SF_CTRL_SF_AES_DIN_ENDIAN_MSK                           (((1U<<SF_CTRL_SF_AES_DIN_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_DIN_ENDIAN_POS)
#define SF_CTRL_SF_AES_DIN_ENDIAN_UMSK                          (~(((1U<<SF_CTRL_SF_AES_DIN_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_DIN_ENDIAN_POS))
#define SF_CTRL_SF_AES_KEY_ENDIAN                               SF_CTRL_SF_AES_KEY_ENDIAN
#define SF_CTRL_SF_AES_KEY_ENDIAN_POS                           (22U)
#define SF_CTRL_SF_AES_KEY_ENDIAN_LEN                           (1U)
#define SF_CTRL_SF_AES_KEY_ENDIAN_MSK                           (((1U<<SF_CTRL_SF_AES_KEY_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_KEY_ENDIAN_POS)
#define SF_CTRL_SF_AES_KEY_ENDIAN_UMSK                          (~(((1U<<SF_CTRL_SF_AES_KEY_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_KEY_ENDIAN_POS))
#define SF_CTRL_SF_AES_IV_ENDIAN                                SF_CTRL_SF_AES_IV_ENDIAN
#define SF_CTRL_SF_AES_IV_ENDIAN_POS                            (23U)
#define SF_CTRL_SF_AES_IV_ENDIAN_LEN                            (1U)
#define SF_CTRL_SF_AES_IV_ENDIAN_MSK                            (((1U<<SF_CTRL_SF_AES_IV_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_IV_ENDIAN_POS)
#define SF_CTRL_SF_AES_IV_ENDIAN_UMSK                           (~(((1U<<SF_CTRL_SF_AES_IV_ENDIAN_LEN)-1)<<SF_CTRL_SF_AES_IV_ENDIAN_POS))
#define SF_CTRL_SF_ID                                           SF_CTRL_SF_ID
#define SF_CTRL_SF_ID_POS                                       (24U)
#define SF_CTRL_SF_ID_LEN                                       (8U)
#define SF_CTRL_SF_ID_MSK                                       (((1U<<SF_CTRL_SF_ID_LEN)-1)<<SF_CTRL_SF_ID_POS)
#define SF_CTRL_SF_ID_UMSK                                      (~(((1U<<SF_CTRL_SF_ID_LEN)-1)<<SF_CTRL_SF_ID_POS))

/* 0x4 : sf_ctrl_1 */
#define SF_CTRL_1_OFFSET                                        (0x4)
#define SF_CTRL_SF_IF_SR_PAT_MASK                               SF_CTRL_SF_IF_SR_PAT_MASK
#define SF_CTRL_SF_IF_SR_PAT_MASK_POS                           (0U)
#define SF_CTRL_SF_IF_SR_PAT_MASK_LEN                           (8U)
#define SF_CTRL_SF_IF_SR_PAT_MASK_MSK                           (((1U<<SF_CTRL_SF_IF_SR_PAT_MASK_LEN)-1)<<SF_CTRL_SF_IF_SR_PAT_MASK_POS)
#define SF_CTRL_SF_IF_SR_PAT_MASK_UMSK                          (~(((1U<<SF_CTRL_SF_IF_SR_PAT_MASK_LEN)-1)<<SF_CTRL_SF_IF_SR_PAT_MASK_POS))
#define SF_CTRL_SF_IF_SR_PAT                                    SF_CTRL_SF_IF_SR_PAT
#define SF_CTRL_SF_IF_SR_PAT_POS                                (8U)
#define SF_CTRL_SF_IF_SR_PAT_LEN                                (8U)
#define SF_CTRL_SF_IF_SR_PAT_MSK                                (((1U<<SF_CTRL_SF_IF_SR_PAT_LEN)-1)<<SF_CTRL_SF_IF_SR_PAT_POS)
#define SF_CTRL_SF_IF_SR_PAT_UMSK                               (~(((1U<<SF_CTRL_SF_IF_SR_PAT_LEN)-1)<<SF_CTRL_SF_IF_SR_PAT_POS))
#define SF_CTRL_SF_IF_SR_INT                                    SF_CTRL_SF_IF_SR_INT
#define SF_CTRL_SF_IF_SR_INT_POS                                (16U)
#define SF_CTRL_SF_IF_SR_INT_LEN                                (1U)
#define SF_CTRL_SF_IF_SR_INT_MSK                                (((1U<<SF_CTRL_SF_IF_SR_INT_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_POS)
#define SF_CTRL_SF_IF_SR_INT_UMSK                               (~(((1U<<SF_CTRL_SF_IF_SR_INT_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_POS))
#define SF_CTRL_SF_IF_SR_INT_EN                                 SF_CTRL_SF_IF_SR_INT_EN
#define SF_CTRL_SF_IF_SR_INT_EN_POS                             (17U)
#define SF_CTRL_SF_IF_SR_INT_EN_LEN                             (1U)
#define SF_CTRL_SF_IF_SR_INT_EN_MSK                             (((1U<<SF_CTRL_SF_IF_SR_INT_EN_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_EN_POS)
#define SF_CTRL_SF_IF_SR_INT_EN_UMSK                            (~(((1U<<SF_CTRL_SF_IF_SR_INT_EN_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_EN_POS))
#define SF_CTRL_SF_IF_SR_INT_SET                                SF_CTRL_SF_IF_SR_INT_SET
#define SF_CTRL_SF_IF_SR_INT_SET_POS                            (18U)
#define SF_CTRL_SF_IF_SR_INT_SET_LEN                            (1U)
#define SF_CTRL_SF_IF_SR_INT_SET_MSK                            (((1U<<SF_CTRL_SF_IF_SR_INT_SET_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_SET_POS)
#define SF_CTRL_SF_IF_SR_INT_SET_UMSK                           (~(((1U<<SF_CTRL_SF_IF_SR_INT_SET_LEN)-1)<<SF_CTRL_SF_IF_SR_INT_SET_POS))
#define SF_CTRL_SF_IF_0_ACK_LAT                                 SF_CTRL_SF_IF_0_ACK_LAT
#define SF_CTRL_SF_IF_0_ACK_LAT_POS                             (20U)
#define SF_CTRL_SF_IF_0_ACK_LAT_LEN                             (3U)
#define SF_CTRL_SF_IF_0_ACK_LAT_MSK                             (((1U<<SF_CTRL_SF_IF_0_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF_0_ACK_LAT_POS)
#define SF_CTRL_SF_IF_0_ACK_LAT_UMSK                            (~(((1U<<SF_CTRL_SF_IF_0_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF_0_ACK_LAT_POS))
#define SF_CTRL_SF_AHB2SIF_DISWRAP                              SF_CTRL_SF_AHB2SIF_DISWRAP
#define SF_CTRL_SF_AHB2SIF_DISWRAP_POS                          (23U)
#define SF_CTRL_SF_AHB2SIF_DISWRAP_LEN                          (1U)
#define SF_CTRL_SF_AHB2SIF_DISWRAP_MSK                          (((1U<<SF_CTRL_SF_AHB2SIF_DISWRAP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_DISWRAP_POS)
#define SF_CTRL_SF_AHB2SIF_DISWRAP_UMSK                         (~(((1U<<SF_CTRL_SF_AHB2SIF_DISWRAP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_DISWRAP_POS))
#define SF_CTRL_SF_IF_REG_HOLD                                  SF_CTRL_SF_IF_REG_HOLD
#define SF_CTRL_SF_IF_REG_HOLD_POS                              (24U)
#define SF_CTRL_SF_IF_REG_HOLD_LEN                              (1U)
#define SF_CTRL_SF_IF_REG_HOLD_MSK                              (((1U<<SF_CTRL_SF_IF_REG_HOLD_LEN)-1)<<SF_CTRL_SF_IF_REG_HOLD_POS)
#define SF_CTRL_SF_IF_REG_HOLD_UMSK                             (~(((1U<<SF_CTRL_SF_IF_REG_HOLD_LEN)-1)<<SF_CTRL_SF_IF_REG_HOLD_POS))
#define SF_CTRL_SF_IF_REG_WP                                    SF_CTRL_SF_IF_REG_WP
#define SF_CTRL_SF_IF_REG_WP_POS                                (25U)
#define SF_CTRL_SF_IF_REG_WP_LEN                                (1U)
#define SF_CTRL_SF_IF_REG_WP_MSK                                (((1U<<SF_CTRL_SF_IF_REG_WP_LEN)-1)<<SF_CTRL_SF_IF_REG_WP_POS)
#define SF_CTRL_SF_IF_REG_WP_UMSK                               (~(((1U<<SF_CTRL_SF_IF_REG_WP_LEN)-1)<<SF_CTRL_SF_IF_REG_WP_POS))
#define SF_CTRL_SF_AHB2SIF_STOPPED                              SF_CTRL_SF_AHB2SIF_STOPPED
#define SF_CTRL_SF_AHB2SIF_STOPPED_POS                          (26U)
#define SF_CTRL_SF_AHB2SIF_STOPPED_LEN                          (1U)
#define SF_CTRL_SF_AHB2SIF_STOPPED_MSK                          (((1U<<SF_CTRL_SF_AHB2SIF_STOPPED_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STOPPED_POS)
#define SF_CTRL_SF_AHB2SIF_STOPPED_UMSK                         (~(((1U<<SF_CTRL_SF_AHB2SIF_STOPPED_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STOPPED_POS))
#define SF_CTRL_SF_AHB2SIF_STOP                                 SF_CTRL_SF_AHB2SIF_STOP
#define SF_CTRL_SF_AHB2SIF_STOP_POS                             (27U)
#define SF_CTRL_SF_AHB2SIF_STOP_LEN                             (1U)
#define SF_CTRL_SF_AHB2SIF_STOP_MSK                             (((1U<<SF_CTRL_SF_AHB2SIF_STOP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STOP_POS)
#define SF_CTRL_SF_AHB2SIF_STOP_UMSK                            (~(((1U<<SF_CTRL_SF_AHB2SIF_STOP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STOP_POS))
#define SF_CTRL_SF_IF_FN_SEL                                    SF_CTRL_SF_IF_FN_SEL
#define SF_CTRL_SF_IF_FN_SEL_POS                                (28U)
#define SF_CTRL_SF_IF_FN_SEL_LEN                                (1U)
#define SF_CTRL_SF_IF_FN_SEL_MSK                                (((1U<<SF_CTRL_SF_IF_FN_SEL_LEN)-1)<<SF_CTRL_SF_IF_FN_SEL_POS)
#define SF_CTRL_SF_IF_FN_SEL_UMSK                               (~(((1U<<SF_CTRL_SF_IF_FN_SEL_LEN)-1)<<SF_CTRL_SF_IF_FN_SEL_POS))
#define SF_CTRL_SF_IF_EN                                        SF_CTRL_SF_IF_EN
#define SF_CTRL_SF_IF_EN_POS                                    (29U)
#define SF_CTRL_SF_IF_EN_LEN                                    (1U)
#define SF_CTRL_SF_IF_EN_MSK                                    (((1U<<SF_CTRL_SF_IF_EN_LEN)-1)<<SF_CTRL_SF_IF_EN_POS)
#define SF_CTRL_SF_IF_EN_UMSK                                   (~(((1U<<SF_CTRL_SF_IF_EN_LEN)-1)<<SF_CTRL_SF_IF_EN_POS))
#define SF_CTRL_SF_AHB2SIF_EN                                   SF_CTRL_SF_AHB2SIF_EN
#define SF_CTRL_SF_AHB2SIF_EN_POS                               (30U)
#define SF_CTRL_SF_AHB2SIF_EN_LEN                               (1U)
#define SF_CTRL_SF_AHB2SIF_EN_MSK                               (((1U<<SF_CTRL_SF_AHB2SIF_EN_LEN)-1)<<SF_CTRL_SF_AHB2SIF_EN_POS)
#define SF_CTRL_SF_AHB2SIF_EN_UMSK                              (~(((1U<<SF_CTRL_SF_AHB2SIF_EN_LEN)-1)<<SF_CTRL_SF_AHB2SIF_EN_POS))
#define SF_CTRL_SF_AHB2SRAM_EN                                  SF_CTRL_SF_AHB2SRAM_EN
#define SF_CTRL_SF_AHB2SRAM_EN_POS                              (31U)
#define SF_CTRL_SF_AHB2SRAM_EN_LEN                              (1U)
#define SF_CTRL_SF_AHB2SRAM_EN_MSK                              (((1U<<SF_CTRL_SF_AHB2SRAM_EN_LEN)-1)<<SF_CTRL_SF_AHB2SRAM_EN_POS)
#define SF_CTRL_SF_AHB2SRAM_EN_UMSK                             (~(((1U<<SF_CTRL_SF_AHB2SRAM_EN_LEN)-1)<<SF_CTRL_SF_AHB2SRAM_EN_POS))

/* 0x8 : sf_if_sahb_0 */
#define SF_CTRL_SF_IF_SAHB_0_OFFSET                             (0x8)
#define SF_CTRL_SF_IF_BUSY                                      SF_CTRL_SF_IF_BUSY
#define SF_CTRL_SF_IF_BUSY_POS                                  (0U)
#define SF_CTRL_SF_IF_BUSY_LEN                                  (1U)
#define SF_CTRL_SF_IF_BUSY_MSK                                  (((1U<<SF_CTRL_SF_IF_BUSY_LEN)-1)<<SF_CTRL_SF_IF_BUSY_POS)
#define SF_CTRL_SF_IF_BUSY_UMSK                                 (~(((1U<<SF_CTRL_SF_IF_BUSY_LEN)-1)<<SF_CTRL_SF_IF_BUSY_POS))
#define SF_CTRL_SF_IF_0_TRIG                                    SF_CTRL_SF_IF_0_TRIG
#define SF_CTRL_SF_IF_0_TRIG_POS                                (1U)
#define SF_CTRL_SF_IF_0_TRIG_LEN                                (1U)
#define SF_CTRL_SF_IF_0_TRIG_MSK                                (((1U<<SF_CTRL_SF_IF_0_TRIG_LEN)-1)<<SF_CTRL_SF_IF_0_TRIG_POS)
#define SF_CTRL_SF_IF_0_TRIG_UMSK                               (~(((1U<<SF_CTRL_SF_IF_0_TRIG_LEN)-1)<<SF_CTRL_SF_IF_0_TRIG_POS))
#define SF_CTRL_SF_IF_0_DAT_BYTE                                SF_CTRL_SF_IF_0_DAT_BYTE
#define SF_CTRL_SF_IF_0_DAT_BYTE_POS                            (2U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_LEN                            (10U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_0_DAT_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_BYTE_POS)
#define SF_CTRL_SF_IF_0_DAT_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_0_DAT_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_BYTE_POS))
#define SF_CTRL_SF_IF_0_DMY_BYTE                                SF_CTRL_SF_IF_0_DMY_BYTE
#define SF_CTRL_SF_IF_0_DMY_BYTE_POS                            (12U)
#define SF_CTRL_SF_IF_0_DMY_BYTE_LEN                            (5U)
#define SF_CTRL_SF_IF_0_DMY_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_0_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_0_DMY_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_0_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_0_ADR_BYTE                                SF_CTRL_SF_IF_0_ADR_BYTE
#define SF_CTRL_SF_IF_0_ADR_BYTE_POS                            (17U)
#define SF_CTRL_SF_IF_0_ADR_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_0_ADR_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_0_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_0_ADR_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_0_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_0_CMD_BYTE                                SF_CTRL_SF_IF_0_CMD_BYTE
#define SF_CTRL_SF_IF_0_CMD_BYTE_POS                            (20U)
#define SF_CTRL_SF_IF_0_CMD_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_0_CMD_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_0_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_0_CMD_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_0_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_0_DAT_RW                                  SF_CTRL_SF_IF_0_DAT_RW
#define SF_CTRL_SF_IF_0_DAT_RW_POS                              (23U)
#define SF_CTRL_SF_IF_0_DAT_RW_LEN                              (1U)
#define SF_CTRL_SF_IF_0_DAT_RW_MSK                              (((1U<<SF_CTRL_SF_IF_0_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_RW_POS)
#define SF_CTRL_SF_IF_0_DAT_RW_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_RW_POS))
#define SF_CTRL_SF_IF_0_DAT_EN                                  SF_CTRL_SF_IF_0_DAT_EN
#define SF_CTRL_SF_IF_0_DAT_EN_POS                              (24U)
#define SF_CTRL_SF_IF_0_DAT_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_0_DAT_EN_MSK                              (((1U<<SF_CTRL_SF_IF_0_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_EN_POS)
#define SF_CTRL_SF_IF_0_DAT_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_0_DAT_EN_POS))
#define SF_CTRL_SF_IF_0_DMY_EN                                  SF_CTRL_SF_IF_0_DMY_EN
#define SF_CTRL_SF_IF_0_DMY_EN_POS                              (25U)
#define SF_CTRL_SF_IF_0_DMY_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_0_DMY_EN_MSK                              (((1U<<SF_CTRL_SF_IF_0_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_0_DMY_EN_POS)
#define SF_CTRL_SF_IF_0_DMY_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_0_DMY_EN_POS))
#define SF_CTRL_SF_IF_0_ADR_EN                                  SF_CTRL_SF_IF_0_ADR_EN
#define SF_CTRL_SF_IF_0_ADR_EN_POS                              (26U)
#define SF_CTRL_SF_IF_0_ADR_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_0_ADR_EN_MSK                              (((1U<<SF_CTRL_SF_IF_0_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_0_ADR_EN_POS)
#define SF_CTRL_SF_IF_0_ADR_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_0_ADR_EN_POS))
#define SF_CTRL_SF_IF_0_CMD_EN                                  SF_CTRL_SF_IF_0_CMD_EN
#define SF_CTRL_SF_IF_0_CMD_EN_POS                              (27U)
#define SF_CTRL_SF_IF_0_CMD_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_0_CMD_EN_MSK                              (((1U<<SF_CTRL_SF_IF_0_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_EN_POS)
#define SF_CTRL_SF_IF_0_CMD_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_EN_POS))
#define SF_CTRL_SF_IF_0_SPI_MODE                                SF_CTRL_SF_IF_0_SPI_MODE
#define SF_CTRL_SF_IF_0_SPI_MODE_POS                            (28U)
#define SF_CTRL_SF_IF_0_SPI_MODE_LEN                            (3U)
#define SF_CTRL_SF_IF_0_SPI_MODE_MSK                            (((1U<<SF_CTRL_SF_IF_0_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_0_SPI_MODE_POS)
#define SF_CTRL_SF_IF_0_SPI_MODE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_0_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_0_SPI_MODE_POS))
#define SF_CTRL_SF_IF_0_QPI_MODE_EN                             SF_CTRL_SF_IF_0_QPI_MODE_EN
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_POS                         (31U)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN                         (1U)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_MSK                         (((1U<<SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_0_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_UMSK                        (~(((1U<<SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_0_QPI_MODE_EN_POS))

/* 0xC : sf_if_sahb_1 */
#define SF_CTRL_SF_IF_SAHB_1_OFFSET                             (0xC)
#define SF_CTRL_SF_IF_0_CMD_BUF_0                               SF_CTRL_SF_IF_0_CMD_BUF_0
#define SF_CTRL_SF_IF_0_CMD_BUF_0_POS                           (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_LEN                           (32U)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_MSK                           (((1U<<SF_CTRL_SF_IF_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_UMSK                          (~(((1U<<SF_CTRL_SF_IF_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BUF_0_POS))

/* 0x10 : sf_if_sahb_2 */
#define SF_CTRL_SF_IF_SAHB_2_OFFSET                             (0x10)
#define SF_CTRL_SF_IF_0_CMD_BUF_1                               SF_CTRL_SF_IF_0_CMD_BUF_1
#define SF_CTRL_SF_IF_0_CMD_BUF_1_POS                           (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_LEN                           (32U)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_MSK                           (((1U<<SF_CTRL_SF_IF_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_UMSK                          (~(((1U<<SF_CTRL_SF_IF_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_0_CMD_BUF_1_POS))

/* 0x14 : sf_if_iahb_0 */
#define SF_CTRL_SF_IF_IAHB_0_OFFSET                             (0x14)
#define SF_CTRL_SF_IF_1_DMY_BYTE                                SF_CTRL_SF_IF_1_DMY_BYTE
#define SF_CTRL_SF_IF_1_DMY_BYTE_POS                            (12U)
#define SF_CTRL_SF_IF_1_DMY_BYTE_LEN                            (5U)
#define SF_CTRL_SF_IF_1_DMY_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_1_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_1_DMY_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_1_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_1_ADR_BYTE                                SF_CTRL_SF_IF_1_ADR_BYTE
#define SF_CTRL_SF_IF_1_ADR_BYTE_POS                            (17U)
#define SF_CTRL_SF_IF_1_ADR_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_1_ADR_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_1_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_1_ADR_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_1_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_1_CMD_BYTE                                SF_CTRL_SF_IF_1_CMD_BYTE
#define SF_CTRL_SF_IF_1_CMD_BYTE_POS                            (20U)
#define SF_CTRL_SF_IF_1_CMD_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_1_CMD_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_1_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_1_CMD_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_1_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_1_DAT_RW                                  SF_CTRL_SF_IF_1_DAT_RW
#define SF_CTRL_SF_IF_1_DAT_RW_POS                              (23U)
#define SF_CTRL_SF_IF_1_DAT_RW_LEN                              (1U)
#define SF_CTRL_SF_IF_1_DAT_RW_MSK                              (((1U<<SF_CTRL_SF_IF_1_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_1_DAT_RW_POS)
#define SF_CTRL_SF_IF_1_DAT_RW_UMSK                             (~(((1U<<SF_CTRL_SF_IF_1_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_1_DAT_RW_POS))
#define SF_CTRL_SF_IF_1_DAT_EN                                  SF_CTRL_SF_IF_1_DAT_EN
#define SF_CTRL_SF_IF_1_DAT_EN_POS                              (24U)
#define SF_CTRL_SF_IF_1_DAT_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_1_DAT_EN_MSK                              (((1U<<SF_CTRL_SF_IF_1_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_1_DAT_EN_POS)
#define SF_CTRL_SF_IF_1_DAT_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_1_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_1_DAT_EN_POS))
#define SF_CTRL_SF_IF_1_DMY_EN                                  SF_CTRL_SF_IF_1_DMY_EN
#define SF_CTRL_SF_IF_1_DMY_EN_POS                              (25U)
#define SF_CTRL_SF_IF_1_DMY_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_1_DMY_EN_MSK                              (((1U<<SF_CTRL_SF_IF_1_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_1_DMY_EN_POS)
#define SF_CTRL_SF_IF_1_DMY_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_1_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_1_DMY_EN_POS))
#define SF_CTRL_SF_IF_1_ADR_EN                                  SF_CTRL_SF_IF_1_ADR_EN
#define SF_CTRL_SF_IF_1_ADR_EN_POS                              (26U)
#define SF_CTRL_SF_IF_1_ADR_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_1_ADR_EN_MSK                              (((1U<<SF_CTRL_SF_IF_1_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_1_ADR_EN_POS)
#define SF_CTRL_SF_IF_1_ADR_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_1_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_1_ADR_EN_POS))
#define SF_CTRL_SF_IF_1_CMD_EN                                  SF_CTRL_SF_IF_1_CMD_EN
#define SF_CTRL_SF_IF_1_CMD_EN_POS                              (27U)
#define SF_CTRL_SF_IF_1_CMD_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_1_CMD_EN_MSK                              (((1U<<SF_CTRL_SF_IF_1_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_EN_POS)
#define SF_CTRL_SF_IF_1_CMD_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_1_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_EN_POS))
#define SF_CTRL_SF_IF_1_SPI_MODE                                SF_CTRL_SF_IF_1_SPI_MODE
#define SF_CTRL_SF_IF_1_SPI_MODE_POS                            (28U)
#define SF_CTRL_SF_IF_1_SPI_MODE_LEN                            (3U)
#define SF_CTRL_SF_IF_1_SPI_MODE_MSK                            (((1U<<SF_CTRL_SF_IF_1_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_1_SPI_MODE_POS)
#define SF_CTRL_SF_IF_1_SPI_MODE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_1_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_1_SPI_MODE_POS))
#define SF_CTRL_SF_IF_1_QPI_MODE_EN                             SF_CTRL_SF_IF_1_QPI_MODE_EN
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_POS                         (31U)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN                         (1U)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_MSK                         (((1U<<SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_1_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_UMSK                        (~(((1U<<SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_1_QPI_MODE_EN_POS))

/* 0x18 : sf_if_iahb_1 */
#define SF_CTRL_SF_IF_IAHB_1_OFFSET                             (0x18)
#define SF_CTRL_SF_IF_1_CMD_BUF_0                               SF_CTRL_SF_IF_1_CMD_BUF_0
#define SF_CTRL_SF_IF_1_CMD_BUF_0_POS                           (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_LEN                           (32U)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_MSK                           (((1U<<SF_CTRL_SF_IF_1_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_UMSK                          (~(((1U<<SF_CTRL_SF_IF_1_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BUF_0_POS))

/* 0x1C : sf_if_iahb_2 */
#define SF_CTRL_SF_IF_IAHB_2_OFFSET                             (0x1C)
#define SF_CTRL_SF_IF_1_CMD_BUF_1                               SF_CTRL_SF_IF_1_CMD_BUF_1
#define SF_CTRL_SF_IF_1_CMD_BUF_1_POS                           (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_LEN                           (32U)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_MSK                           (((1U<<SF_CTRL_SF_IF_1_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_UMSK                          (~(((1U<<SF_CTRL_SF_IF_1_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_1_CMD_BUF_1_POS))

/* 0x20 : sf_if_status_0 */
#define SF_CTRL_SF_IF_STATUS_0_OFFSET                           (0x20)
#define SF_CTRL_SF_IF_STATUS_0                                  SF_CTRL_SF_IF_STATUS_0
#define SF_CTRL_SF_IF_STATUS_0_POS                              (0U)
#define SF_CTRL_SF_IF_STATUS_0_LEN                              (32U)
#define SF_CTRL_SF_IF_STATUS_0_MSK                              (((1U<<SF_CTRL_SF_IF_STATUS_0_LEN)-1)<<SF_CTRL_SF_IF_STATUS_0_POS)
#define SF_CTRL_SF_IF_STATUS_0_UMSK                             (~(((1U<<SF_CTRL_SF_IF_STATUS_0_LEN)-1)<<SF_CTRL_SF_IF_STATUS_0_POS))

/* 0x24 : sf_if_status_1 */
#define SF_CTRL_SF_IF_STATUS_1_OFFSET                           (0x24)
#define SF_CTRL_SF_IF_STATUS_1                                  SF_CTRL_SF_IF_STATUS_1
#define SF_CTRL_SF_IF_STATUS_1_POS                              (0U)
#define SF_CTRL_SF_IF_STATUS_1_LEN                              (32U)
#define SF_CTRL_SF_IF_STATUS_1_MSK                              (((1U<<SF_CTRL_SF_IF_STATUS_1_LEN)-1)<<SF_CTRL_SF_IF_STATUS_1_POS)
#define SF_CTRL_SF_IF_STATUS_1_UMSK                             (~(((1U<<SF_CTRL_SF_IF_STATUS_1_LEN)-1)<<SF_CTRL_SF_IF_STATUS_1_POS))

/* 0x28 : sf_aes */
#define SF_CTRL_SF_AES_OFFSET                                   (0x28)
#define SF_CTRL_SF_AES_EN                                       SF_CTRL_SF_AES_EN
#define SF_CTRL_SF_AES_EN_POS                                   (0U)
#define SF_CTRL_SF_AES_EN_LEN                                   (1U)
#define SF_CTRL_SF_AES_EN_MSK                                   (((1U<<SF_CTRL_SF_AES_EN_LEN)-1)<<SF_CTRL_SF_AES_EN_POS)
#define SF_CTRL_SF_AES_EN_UMSK                                  (~(((1U<<SF_CTRL_SF_AES_EN_LEN)-1)<<SF_CTRL_SF_AES_EN_POS))
#define SF_CTRL_SF_AES_MODE                                     SF_CTRL_SF_AES_MODE
#define SF_CTRL_SF_AES_MODE_POS                                 (1U)
#define SF_CTRL_SF_AES_MODE_LEN                                 (2U)
#define SF_CTRL_SF_AES_MODE_MSK                                 (((1U<<SF_CTRL_SF_AES_MODE_LEN)-1)<<SF_CTRL_SF_AES_MODE_POS)
#define SF_CTRL_SF_AES_MODE_UMSK                                (~(((1U<<SF_CTRL_SF_AES_MODE_LEN)-1)<<SF_CTRL_SF_AES_MODE_POS))
#define SF_CTRL_SF_AES_BLK_MODE                                 SF_CTRL_SF_AES_BLK_MODE
#define SF_CTRL_SF_AES_BLK_MODE_POS                             (3U)
#define SF_CTRL_SF_AES_BLK_MODE_LEN                             (1U)
#define SF_CTRL_SF_AES_BLK_MODE_MSK                             (((1U<<SF_CTRL_SF_AES_BLK_MODE_LEN)-1)<<SF_CTRL_SF_AES_BLK_MODE_POS)
#define SF_CTRL_SF_AES_BLK_MODE_UMSK                            (~(((1U<<SF_CTRL_SF_AES_BLK_MODE_LEN)-1)<<SF_CTRL_SF_AES_BLK_MODE_POS))
#define SF_CTRL_SF_AES_XTS_KEY_OPT                              SF_CTRL_SF_AES_XTS_KEY_OPT
#define SF_CTRL_SF_AES_XTS_KEY_OPT_POS                          (4U)
#define SF_CTRL_SF_AES_XTS_KEY_OPT_LEN                          (1U)
#define SF_CTRL_SF_AES_XTS_KEY_OPT_MSK                          (((1U<<SF_CTRL_SF_AES_XTS_KEY_OPT_LEN)-1)<<SF_CTRL_SF_AES_XTS_KEY_OPT_POS)
#define SF_CTRL_SF_AES_XTS_KEY_OPT_UMSK                         (~(((1U<<SF_CTRL_SF_AES_XTS_KEY_OPT_LEN)-1)<<SF_CTRL_SF_AES_XTS_KEY_OPT_POS))
#define SF_CTRL_SF_AES_STATUS                                   SF_CTRL_SF_AES_STATUS
#define SF_CTRL_SF_AES_STATUS_POS                               (5U)
#define SF_CTRL_SF_AES_STATUS_LEN                               (27U)
#define SF_CTRL_SF_AES_STATUS_MSK                               (((1U<<SF_CTRL_SF_AES_STATUS_LEN)-1)<<SF_CTRL_SF_AES_STATUS_POS)
#define SF_CTRL_SF_AES_STATUS_UMSK                              (~(((1U<<SF_CTRL_SF_AES_STATUS_LEN)-1)<<SF_CTRL_SF_AES_STATUS_POS))

/* 0x2C : sf_ahb2sif_status */
#define SF_CTRL_SF_AHB2SIF_STATUS_OFFSET                        (0x2C)
#define SF_CTRL_SF_AHB2SIF_STATUS                               SF_CTRL_SF_AHB2SIF_STATUS
#define SF_CTRL_SF_AHB2SIF_STATUS_POS                           (0U)
#define SF_CTRL_SF_AHB2SIF_STATUS_LEN                           (32U)
#define SF_CTRL_SF_AHB2SIF_STATUS_MSK                           (((1U<<SF_CTRL_SF_AHB2SIF_STATUS_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STATUS_POS)
#define SF_CTRL_SF_AHB2SIF_STATUS_UMSK                          (~(((1U<<SF_CTRL_SF_AHB2SIF_STATUS_LEN)-1)<<SF_CTRL_SF_AHB2SIF_STATUS_POS))

/* 0x30 : sf_if_io_dly_0 */
#define SF_CTRL_SF_IF_IO_DLY_0_OFFSET                           (0x30)
#define SF_CTRL_SF_CS_DLY_SEL                                   SF_CTRL_SF_CS_DLY_SEL
#define SF_CTRL_SF_CS_DLY_SEL_POS                               (0U)
#define SF_CTRL_SF_CS_DLY_SEL_LEN                               (2U)
#define SF_CTRL_SF_CS_DLY_SEL_MSK                               (((1U<<SF_CTRL_SF_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CS_DLY_SEL_POS)
#define SF_CTRL_SF_CS_DLY_SEL_UMSK                              (~(((1U<<SF_CTRL_SF_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CS_DLY_SEL_POS))
#define SF_CTRL_SF_CS2_DLY_SEL                                  SF_CTRL_SF_CS2_DLY_SEL
#define SF_CTRL_SF_CS2_DLY_SEL_POS                              (2U)
#define SF_CTRL_SF_CS2_DLY_SEL_LEN                              (2U)
#define SF_CTRL_SF_CS2_DLY_SEL_MSK                              (((1U<<SF_CTRL_SF_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CS2_DLY_SEL_POS)
#define SF_CTRL_SF_CS2_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_SF_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CS2_DLY_SEL_POS))
#define SF_CTRL_SF_CLK_OUT_DLY_SEL                              SF_CTRL_SF_CLK_OUT_DLY_SEL
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_POS                          (8U)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_OE_DLY_SEL                               SF_CTRL_SF_DQS_OE_DLY_SEL
#define SF_CTRL_SF_DQS_OE_DLY_SEL_POS                           (26U)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_LEN                           (2U)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_MSK                           (((1U<<SF_CTRL_SF_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_UMSK                          (~(((1U<<SF_CTRL_SF_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_DI_DLY_SEL                               SF_CTRL_SF_DQS_DI_DLY_SEL
#define SF_CTRL_SF_DQS_DI_DLY_SEL_POS                           (28U)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_LEN                           (2U)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_MSK                           (((1U<<SF_CTRL_SF_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_UMSK                          (~(((1U<<SF_CTRL_SF_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_DO_DLY_SEL                               SF_CTRL_SF_DQS_DO_DLY_SEL
#define SF_CTRL_SF_DQS_DO_DLY_SEL_POS                           (30U)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_LEN                           (2U)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_MSK                           (((1U<<SF_CTRL_SF_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_UMSK                          (~(((1U<<SF_CTRL_SF_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_DQS_DO_DLY_SEL_POS))

/* 0x34 : sf_if_io_dly_1 */
#define SF_CTRL_SF_IF_IO_DLY_1_OFFSET                           (0x34)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL                              SF_CTRL_SF_IO_0_OE_DLY_SEL
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_POS                          (0U)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_0_DI_DLY_SEL                              SF_CTRL_SF_IO_0_DI_DLY_SEL
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_POS                          (8U)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_0_DO_DLY_SEL                              SF_CTRL_SF_IO_0_DO_DLY_SEL
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_POS                          (16U)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_0_DO_DLY_SEL_POS))

/* 0x38 : sf_if_io_dly_2 */
#define SF_CTRL_SF_IF_IO_DLY_2_OFFSET                           (0x38)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL                              SF_CTRL_SF_IO_1_OE_DLY_SEL
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_POS                          (0U)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_1_DI_DLY_SEL                              SF_CTRL_SF_IO_1_DI_DLY_SEL
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_POS                          (8U)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_1_DO_DLY_SEL                              SF_CTRL_SF_IO_1_DO_DLY_SEL
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_POS                          (16U)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_1_DO_DLY_SEL_POS))

/* 0x3C : sf_if_io_dly_3 */
#define SF_CTRL_SF_IF_IO_DLY_3_OFFSET                           (0x3C)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL                              SF_CTRL_SF_IO_2_OE_DLY_SEL
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_POS                          (0U)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_2_DI_DLY_SEL                              SF_CTRL_SF_IO_2_DI_DLY_SEL
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_POS                          (8U)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_2_DO_DLY_SEL                              SF_CTRL_SF_IO_2_DO_DLY_SEL
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_POS                          (16U)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_2_DO_DLY_SEL_POS))

/* 0x40 : sf_if_io_dly_4 */
#define SF_CTRL_SF_IF_IO_DLY_4_OFFSET                           (0x40)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL                              SF_CTRL_SF_IO_3_OE_DLY_SEL
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_POS                          (0U)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_3_DI_DLY_SEL                              SF_CTRL_SF_IO_3_DI_DLY_SEL
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_POS                          (8U)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_3_DO_DLY_SEL                              SF_CTRL_SF_IO_3_DO_DLY_SEL
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_POS                          (16U)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF_IO_3_DO_DLY_SEL_POS))

/* 0x44 : sf_reserved */
#define SF_CTRL_SF_RESERVED_OFFSET                              (0x44)
#define SF_CTRL_SF_RESERVED                                     SF_CTRL_SF_RESERVED
#define SF_CTRL_SF_RESERVED_POS                                 (0U)
#define SF_CTRL_SF_RESERVED_LEN                                 (32U)
#define SF_CTRL_SF_RESERVED_MSK                                 (((1U<<SF_CTRL_SF_RESERVED_LEN)-1)<<SF_CTRL_SF_RESERVED_POS)
#define SF_CTRL_SF_RESERVED_UMSK                                (~(((1U<<SF_CTRL_SF_RESERVED_LEN)-1)<<SF_CTRL_SF_RESERVED_POS))

/* 0x48 : sf2_if_io_dly_0 */
#define SF_CTRL_SF2_IF_IO_DLY_0_OFFSET                          (0x48)
#define SF_CTRL_SF2_CS_DLY_SEL                                  SF_CTRL_SF2_CS_DLY_SEL
#define SF_CTRL_SF2_CS_DLY_SEL_POS                              (0U)
#define SF_CTRL_SF2_CS_DLY_SEL_LEN                              (2U)
#define SF_CTRL_SF2_CS_DLY_SEL_MSK                              (((1U<<SF_CTRL_SF2_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CS_DLY_SEL_POS)
#define SF_CTRL_SF2_CS_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_SF2_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CS_DLY_SEL_POS))
#define SF_CTRL_SF2_CS2_DLY_SEL                                 SF_CTRL_SF2_CS2_DLY_SEL
#define SF_CTRL_SF2_CS2_DLY_SEL_POS                             (2U)
#define SF_CTRL_SF2_CS2_DLY_SEL_LEN                             (2U)
#define SF_CTRL_SF2_CS2_DLY_SEL_MSK                             (((1U<<SF_CTRL_SF2_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CS2_DLY_SEL_POS)
#define SF_CTRL_SF2_CS2_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_SF2_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CS2_DLY_SEL_POS))
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL                             SF_CTRL_SF2_CLK_OUT_DLY_SEL
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_OE_DLY_SEL                              SF_CTRL_SF2_DQS_OE_DLY_SEL
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_POS                          (26U)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_DI_DLY_SEL                              SF_CTRL_SF2_DQS_DI_DLY_SEL
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_POS                          (28U)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_DO_DLY_SEL                              SF_CTRL_SF2_DQS_DO_DLY_SEL
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_POS                          (30U)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_DQS_DO_DLY_SEL_POS))

/* 0x4C : sf2_if_io_dly_1 */
#define SF_CTRL_SF2_IF_IO_DLY_1_OFFSET                          (0x4C)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL                             SF_CTRL_SF2_IO_0_OE_DLY_SEL
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL                             SF_CTRL_SF2_IO_0_DI_DLY_SEL
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL                             SF_CTRL_SF2_IO_0_DO_DLY_SEL
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS))

/* 0x50 : sf2_if_io_dly_2 */
#define SF_CTRL_SF2_IF_IO_DLY_2_OFFSET                          (0x50)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL                             SF_CTRL_SF2_IO_1_OE_DLY_SEL
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL                             SF_CTRL_SF2_IO_1_DI_DLY_SEL
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL                             SF_CTRL_SF2_IO_1_DO_DLY_SEL
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS))

/* 0x54 : sf2_if_io_dly_3 */
#define SF_CTRL_SF2_IF_IO_DLY_3_OFFSET                          (0x54)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL                             SF_CTRL_SF2_IO_2_OE_DLY_SEL
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL                             SF_CTRL_SF2_IO_2_DI_DLY_SEL
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL                             SF_CTRL_SF2_IO_2_DO_DLY_SEL
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS))

/* 0x58 : sf2_if_io_dly_4 */
#define SF_CTRL_SF2_IF_IO_DLY_4_OFFSET                          (0x58)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL                             SF_CTRL_SF2_IO_3_OE_DLY_SEL
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL                             SF_CTRL_SF2_IO_3_DI_DLY_SEL
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL                             SF_CTRL_SF2_IO_3_DO_DLY_SEL
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS))

/* 0x5C : sf3_if_io_dly_0 */
#define SF_CTRL_SF3_IF_IO_DLY_0_OFFSET                          (0x5C)
#define SF_CTRL_SF3_CS_DLY_SEL                                  SF_CTRL_SF3_CS_DLY_SEL
#define SF_CTRL_SF3_CS_DLY_SEL_POS                              (0U)
#define SF_CTRL_SF3_CS_DLY_SEL_LEN                              (2U)
#define SF_CTRL_SF3_CS_DLY_SEL_MSK                              (((1U<<SF_CTRL_SF3_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CS_DLY_SEL_POS)
#define SF_CTRL_SF3_CS_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_SF3_CS_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CS_DLY_SEL_POS))
#define SF_CTRL_SF3_CS2_DLY_SEL                                 SF_CTRL_SF3_CS2_DLY_SEL
#define SF_CTRL_SF3_CS2_DLY_SEL_POS                             (2U)
#define SF_CTRL_SF3_CS2_DLY_SEL_LEN                             (2U)
#define SF_CTRL_SF3_CS2_DLY_SEL_MSK                             (((1U<<SF_CTRL_SF3_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CS2_DLY_SEL_POS)
#define SF_CTRL_SF3_CS2_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_SF3_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CS2_DLY_SEL_POS))
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL                             SF_CTRL_SF3_CLK_OUT_DLY_SEL
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_OE_DLY_SEL                              SF_CTRL_SF3_DQS_OE_DLY_SEL
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_POS                          (26U)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_DI_DLY_SEL                              SF_CTRL_SF3_DQS_DI_DLY_SEL
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_POS                          (28U)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_DO_DLY_SEL                              SF_CTRL_SF3_DQS_DO_DLY_SEL
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_POS                          (30U)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN                          (2U)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_MSK                          (((1U<<SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_UMSK                         (~(((1U<<SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_DQS_DO_DLY_SEL_POS))

/* 0x60 : sf3_if_io_dly_1 */
#define SF_CTRL_SF3_IF_IO_DLY_1_OFFSET                          (0x60)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL                             SF_CTRL_SF3_IO_0_OE_DLY_SEL
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL                             SF_CTRL_SF3_IO_0_DI_DLY_SEL
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL                             SF_CTRL_SF3_IO_0_DO_DLY_SEL
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS))

/* 0x64 : sf3_if_io_dly_2 */
#define SF_CTRL_SF3_IF_IO_DLY_2_OFFSET                          (0x64)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL                             SF_CTRL_SF3_IO_1_OE_DLY_SEL
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL                             SF_CTRL_SF3_IO_1_DI_DLY_SEL
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL                             SF_CTRL_SF3_IO_1_DO_DLY_SEL
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS))

/* 0x68 : sf3_if_io_dly_3 */
#define SF_CTRL_SF3_IF_IO_DLY_3_OFFSET                          (0x68)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL                             SF_CTRL_SF3_IO_2_OE_DLY_SEL
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL                             SF_CTRL_SF3_IO_2_DI_DLY_SEL
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL                             SF_CTRL_SF3_IO_2_DO_DLY_SEL
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS))

/* 0x6C : sf3_if_io_dly_4 */
#define SF_CTRL_SF3_IF_IO_DLY_4_OFFSET                          (0x6C)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL                             SF_CTRL_SF3_IO_3_OE_DLY_SEL
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS                         (0U)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL                             SF_CTRL_SF3_IO_3_DI_DLY_SEL
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS                         (8U)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL                             SF_CTRL_SF3_IO_3_DO_DLY_SEL
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS                         (16U)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN                         (2U)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_MSK                         (((1U<<SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS))

/* 0x70 : sf_ctrl_2 */
#define SF_CTRL_2_OFFSET                                        (0x70)
#define SF_CTRL_SF_IF_PAD_SEL                                   SF_CTRL_SF_IF_PAD_SEL
#define SF_CTRL_SF_IF_PAD_SEL_POS                               (0U)
#define SF_CTRL_SF_IF_PAD_SEL_LEN                               (2U)
#define SF_CTRL_SF_IF_PAD_SEL_MSK                               (((1U<<SF_CTRL_SF_IF_PAD_SEL_LEN)-1)<<SF_CTRL_SF_IF_PAD_SEL_POS)
#define SF_CTRL_SF_IF_PAD_SEL_UMSK                              (~(((1U<<SF_CTRL_SF_IF_PAD_SEL_LEN)-1)<<SF_CTRL_SF_IF_PAD_SEL_POS))
#define SF_CTRL_SF_IF_PAD_SEL_LOCK                              SF_CTRL_SF_IF_PAD_SEL_LOCK
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_POS                          (3U)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN                          (1U)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_MSK                          (((1U<<SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN)-1)<<SF_CTRL_SF_IF_PAD_SEL_LOCK_POS)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_UMSK                         (~(((1U<<SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN)-1)<<SF_CTRL_SF_IF_PAD_SEL_LOCK_POS))
#define SF_CTRL_SF_IF_DTR_EN                                    SF_CTRL_SF_IF_DTR_EN
#define SF_CTRL_SF_IF_DTR_EN_POS                                (4U)
#define SF_CTRL_SF_IF_DTR_EN_LEN                                (1U)
#define SF_CTRL_SF_IF_DTR_EN_MSK                                (((1U<<SF_CTRL_SF_IF_DTR_EN_LEN)-1)<<SF_CTRL_SF_IF_DTR_EN_POS)
#define SF_CTRL_SF_IF_DTR_EN_UMSK                               (~(((1U<<SF_CTRL_SF_IF_DTR_EN_LEN)-1)<<SF_CTRL_SF_IF_DTR_EN_POS))
#define SF_CTRL_SF_IF_DQS_EN                                    SF_CTRL_SF_IF_DQS_EN
#define SF_CTRL_SF_IF_DQS_EN_POS                                (5U)
#define SF_CTRL_SF_IF_DQS_EN_LEN                                (1U)
#define SF_CTRL_SF_IF_DQS_EN_MSK                                (((1U<<SF_CTRL_SF_IF_DQS_EN_LEN)-1)<<SF_CTRL_SF_IF_DQS_EN_POS)
#define SF_CTRL_SF_IF_DQS_EN_UMSK                               (~(((1U<<SF_CTRL_SF_IF_DQS_EN_LEN)-1)<<SF_CTRL_SF_IF_DQS_EN_POS))
#define SF_CTRL_SF_IF_TRIG_WR_PROT                              SF_CTRL_SF_IF_TRIG_WR_PROT
#define SF_CTRL_SF_IF_TRIG_WR_PROT_POS                          (6U)
#define SF_CTRL_SF_IF_TRIG_WR_PROT_LEN                          (1U)
#define SF_CTRL_SF_IF_TRIG_WR_PROT_MSK                          (((1U<<SF_CTRL_SF_IF_TRIG_WR_PROT_LEN)-1)<<SF_CTRL_SF_IF_TRIG_WR_PROT_POS)
#define SF_CTRL_SF_IF_TRIG_WR_PROT_UMSK                         (~(((1U<<SF_CTRL_SF_IF_TRIG_WR_PROT_LEN)-1)<<SF_CTRL_SF_IF_TRIG_WR_PROT_POS))
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK                           SF_CTRL_SF_AHB2SIF_REMAP_LOCK
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK_POS                       (25U)
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK_LEN                       (1U)
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK_MSK                       (((1U<<SF_CTRL_SF_AHB2SIF_REMAP_LOCK_LEN)-1)<<SF_CTRL_SF_AHB2SIF_REMAP_LOCK_POS)
#define SF_CTRL_SF_AHB2SIF_REMAP_LOCK_UMSK                      (~(((1U<<SF_CTRL_SF_AHB2SIF_REMAP_LOCK_LEN)-1)<<SF_CTRL_SF_AHB2SIF_REMAP_LOCK_POS))
#define SF_CTRL_SF_AHB2SIF_REMAP                                SF_CTRL_SF_AHB2SIF_REMAP
#define SF_CTRL_SF_AHB2SIF_REMAP_POS                            (26U)
#define SF_CTRL_SF_AHB2SIF_REMAP_LEN                            (2U)
#define SF_CTRL_SF_AHB2SIF_REMAP_MSK                            (((1U<<SF_CTRL_SF_AHB2SIF_REMAP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_REMAP_POS)
#define SF_CTRL_SF_AHB2SIF_REMAP_UMSK                           (~(((1U<<SF_CTRL_SF_AHB2SIF_REMAP_LEN)-1)<<SF_CTRL_SF_AHB2SIF_REMAP_POS))
#define SF_CTRL_SF_IF_BK_SWAP                                   SF_CTRL_SF_IF_BK_SWAP
#define SF_CTRL_SF_IF_BK_SWAP_POS                               (28U)
#define SF_CTRL_SF_IF_BK_SWAP_LEN                               (1U)
#define SF_CTRL_SF_IF_BK_SWAP_MSK                               (((1U<<SF_CTRL_SF_IF_BK_SWAP_LEN)-1)<<SF_CTRL_SF_IF_BK_SWAP_POS)
#define SF_CTRL_SF_IF_BK_SWAP_UMSK                              (~(((1U<<SF_CTRL_SF_IF_BK_SWAP_LEN)-1)<<SF_CTRL_SF_IF_BK_SWAP_POS))
#define SF_CTRL_SF_IF_BK2_MODE                                  SF_CTRL_SF_IF_BK2_MODE
#define SF_CTRL_SF_IF_BK2_MODE_POS                              (29U)
#define SF_CTRL_SF_IF_BK2_MODE_LEN                              (1U)
#define SF_CTRL_SF_IF_BK2_MODE_MSK                              (((1U<<SF_CTRL_SF_IF_BK2_MODE_LEN)-1)<<SF_CTRL_SF_IF_BK2_MODE_POS)
#define SF_CTRL_SF_IF_BK2_MODE_UMSK                             (~(((1U<<SF_CTRL_SF_IF_BK2_MODE_LEN)-1)<<SF_CTRL_SF_IF_BK2_MODE_POS))
#define SF_CTRL_SF_IF_BK2_EN                                    SF_CTRL_SF_IF_BK2_EN
#define SF_CTRL_SF_IF_BK2_EN_POS                                (30U)
#define SF_CTRL_SF_IF_BK2_EN_LEN                                (1U)
#define SF_CTRL_SF_IF_BK2_EN_MSK                                (((1U<<SF_CTRL_SF_IF_BK2_EN_LEN)-1)<<SF_CTRL_SF_IF_BK2_EN_POS)
#define SF_CTRL_SF_IF_BK2_EN_UMSK                               (~(((1U<<SF_CTRL_SF_IF_BK2_EN_LEN)-1)<<SF_CTRL_SF_IF_BK2_EN_POS))
#define SF_CTRL_SF_IF_0_BK_SEL                                  SF_CTRL_SF_IF_0_BK_SEL
#define SF_CTRL_SF_IF_0_BK_SEL_POS                              (31U)
#define SF_CTRL_SF_IF_0_BK_SEL_LEN                              (1U)
#define SF_CTRL_SF_IF_0_BK_SEL_MSK                              (((1U<<SF_CTRL_SF_IF_0_BK_SEL_LEN)-1)<<SF_CTRL_SF_IF_0_BK_SEL_POS)
#define SF_CTRL_SF_IF_0_BK_SEL_UMSK                             (~(((1U<<SF_CTRL_SF_IF_0_BK_SEL_LEN)-1)<<SF_CTRL_SF_IF_0_BK_SEL_POS))

/* 0x74 : sf_ctrl_3 */
#define SF_CTRL_3_OFFSET                                        (0x74)
#define SF_CTRL_SF_CMDS_2_WRAP_LEN                              SF_CTRL_SF_CMDS_2_WRAP_LEN
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_POS                          (0U)
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_LEN                          (4U)
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_MSK                          (((1U<<SF_CTRL_SF_CMDS_2_WRAP_LEN_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_LEN_POS)
#define SF_CTRL_SF_CMDS_2_WRAP_LEN_UMSK                         (~(((1U<<SF_CTRL_SF_CMDS_2_WRAP_LEN_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_LEN_POS))
#define SF_CTRL_SF_CMDS_2_EN                                    SF_CTRL_SF_CMDS_2_EN
#define SF_CTRL_SF_CMDS_2_EN_POS                                (4U)
#define SF_CTRL_SF_CMDS_2_EN_LEN                                (1U)
#define SF_CTRL_SF_CMDS_2_EN_MSK                                (((1U<<SF_CTRL_SF_CMDS_2_EN_LEN)-1)<<SF_CTRL_SF_CMDS_2_EN_POS)
#define SF_CTRL_SF_CMDS_2_EN_UMSK                               (~(((1U<<SF_CTRL_SF_CMDS_2_EN_LEN)-1)<<SF_CTRL_SF_CMDS_2_EN_POS))
#define SF_CTRL_SF_CMDS_2_BT_DLY                                SF_CTRL_SF_CMDS_2_BT_DLY
#define SF_CTRL_SF_CMDS_2_BT_DLY_POS                            (5U)
#define SF_CTRL_SF_CMDS_2_BT_DLY_LEN                            (3U)
#define SF_CTRL_SF_CMDS_2_BT_DLY_MSK                            (((1U<<SF_CTRL_SF_CMDS_2_BT_DLY_LEN)-1)<<SF_CTRL_SF_CMDS_2_BT_DLY_POS)
#define SF_CTRL_SF_CMDS_2_BT_DLY_UMSK                           (~(((1U<<SF_CTRL_SF_CMDS_2_BT_DLY_LEN)-1)<<SF_CTRL_SF_CMDS_2_BT_DLY_POS))
#define SF_CTRL_SF_CMDS_2_BT_EN                                 SF_CTRL_SF_CMDS_2_BT_EN
#define SF_CTRL_SF_CMDS_2_BT_EN_POS                             (8U)
#define SF_CTRL_SF_CMDS_2_BT_EN_LEN                             (1U)
#define SF_CTRL_SF_CMDS_2_BT_EN_MSK                             (((1U<<SF_CTRL_SF_CMDS_2_BT_EN_LEN)-1)<<SF_CTRL_SF_CMDS_2_BT_EN_POS)
#define SF_CTRL_SF_CMDS_2_BT_EN_UMSK                            (~(((1U<<SF_CTRL_SF_CMDS_2_BT_EN_LEN)-1)<<SF_CTRL_SF_CMDS_2_BT_EN_POS))
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI                            SF_CTRL_SF_CMDS_2_WRAP_Q_INI
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI_POS                        (9U)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI_LEN                        (1U)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI_MSK                        (((1U<<SF_CTRL_SF_CMDS_2_WRAP_Q_INI_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_Q_INI_POS)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_INI_UMSK                       (~(((1U<<SF_CTRL_SF_CMDS_2_WRAP_Q_INI_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_Q_INI_POS))
#define SF_CTRL_SF_CMDS_2_WRAP_MODE                             SF_CTRL_SF_CMDS_2_WRAP_MODE
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_POS                         (10U)
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_LEN                         (2U)
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_MSK                         (((1U<<SF_CTRL_SF_CMDS_2_WRAP_MODE_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_MODE_POS)
#define SF_CTRL_SF_CMDS_2_WRAP_MODE_UMSK                        (~(((1U<<SF_CTRL_SF_CMDS_2_WRAP_MODE_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_MODE_POS))
#define SF_CTRL_SF_CMDS_2_WRAP_Q                                SF_CTRL_SF_CMDS_2_WRAP_Q
#define SF_CTRL_SF_CMDS_2_WRAP_Q_POS                            (12U)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_LEN                            (1U)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_MSK                            (((1U<<SF_CTRL_SF_CMDS_2_WRAP_Q_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_Q_POS)
#define SF_CTRL_SF_CMDS_2_WRAP_Q_UMSK                           (~(((1U<<SF_CTRL_SF_CMDS_2_WRAP_Q_LEN)-1)<<SF_CTRL_SF_CMDS_2_WRAP_Q_POS))
#define SF_CTRL_SF_CMDS_1_WRAP_LEN                              SF_CTRL_SF_CMDS_1_WRAP_LEN
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_POS                          (13U)
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_LEN                          (4U)
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_MSK                          (((1U<<SF_CTRL_SF_CMDS_1_WRAP_LEN_LEN)-1)<<SF_CTRL_SF_CMDS_1_WRAP_LEN_POS)
#define SF_CTRL_SF_CMDS_1_WRAP_LEN_UMSK                         (~(((1U<<SF_CTRL_SF_CMDS_1_WRAP_LEN_LEN)-1)<<SF_CTRL_SF_CMDS_1_WRAP_LEN_POS))
#define SF_CTRL_SF_CMDS_1_EN                                    SF_CTRL_SF_CMDS_1_EN
#define SF_CTRL_SF_CMDS_1_EN_POS                                (17U)
#define SF_CTRL_SF_CMDS_1_EN_LEN                                (1U)
#define SF_CTRL_SF_CMDS_1_EN_MSK                                (((1U<<SF_CTRL_SF_CMDS_1_EN_LEN)-1)<<SF_CTRL_SF_CMDS_1_EN_POS)
#define SF_CTRL_SF_CMDS_1_EN_UMSK                               (~(((1U<<SF_CTRL_SF_CMDS_1_EN_LEN)-1)<<SF_CTRL_SF_CMDS_1_EN_POS))
#define SF_CTRL_SF_CMDS_1_WRAP_MODE                             SF_CTRL_SF_CMDS_1_WRAP_MODE
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_POS                         (18U)
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_LEN                         (2U)
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_MSK                         (((1U<<SF_CTRL_SF_CMDS_1_WRAP_MODE_LEN)-1)<<SF_CTRL_SF_CMDS_1_WRAP_MODE_POS)
#define SF_CTRL_SF_CMDS_1_WRAP_MODE_UMSK                        (~(((1U<<SF_CTRL_SF_CMDS_1_WRAP_MODE_LEN)-1)<<SF_CTRL_SF_CMDS_1_WRAP_MODE_POS))
#define SF_CTRL_SF_CMDS_CORE_EN                                 SF_CTRL_SF_CMDS_CORE_EN
#define SF_CTRL_SF_CMDS_CORE_EN_POS                             (20U)
#define SF_CTRL_SF_CMDS_CORE_EN_LEN                             (1U)
#define SF_CTRL_SF_CMDS_CORE_EN_MSK                             (((1U<<SF_CTRL_SF_CMDS_CORE_EN_LEN)-1)<<SF_CTRL_SF_CMDS_CORE_EN_POS)
#define SF_CTRL_SF_CMDS_CORE_EN_UMSK                            (~(((1U<<SF_CTRL_SF_CMDS_CORE_EN_LEN)-1)<<SF_CTRL_SF_CMDS_CORE_EN_POS))
#define SF_CTRL_SF_IF_1_ACK_LAT                                 SF_CTRL_SF_IF_1_ACK_LAT
#define SF_CTRL_SF_IF_1_ACK_LAT_POS                             (29U)
#define SF_CTRL_SF_IF_1_ACK_LAT_LEN                             (3U)
#define SF_CTRL_SF_IF_1_ACK_LAT_MSK                             (((1U<<SF_CTRL_SF_IF_1_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF_1_ACK_LAT_POS)
#define SF_CTRL_SF_IF_1_ACK_LAT_UMSK                            (~(((1U<<SF_CTRL_SF_IF_1_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF_1_ACK_LAT_POS))

/* 0x78 : sf_if_iahb_3 */
#define SF_CTRL_SF_IF_IAHB_3_OFFSET                             (0x78)
#define SF_CTRL_SF_IF_2_DMY_BYTE                                SF_CTRL_SF_IF_2_DMY_BYTE
#define SF_CTRL_SF_IF_2_DMY_BYTE_POS                            (12U)
#define SF_CTRL_SF_IF_2_DMY_BYTE_LEN                            (5U)
#define SF_CTRL_SF_IF_2_DMY_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_2_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_2_DMY_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_2_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_2_ADR_BYTE                                SF_CTRL_SF_IF_2_ADR_BYTE
#define SF_CTRL_SF_IF_2_ADR_BYTE_POS                            (17U)
#define SF_CTRL_SF_IF_2_ADR_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_2_ADR_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_2_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_2_ADR_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_2_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_2_CMD_BYTE                                SF_CTRL_SF_IF_2_CMD_BYTE
#define SF_CTRL_SF_IF_2_CMD_BYTE_POS                            (20U)
#define SF_CTRL_SF_IF_2_CMD_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_2_CMD_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_2_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_2_CMD_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_2_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_2_DAT_RW                                  SF_CTRL_SF_IF_2_DAT_RW
#define SF_CTRL_SF_IF_2_DAT_RW_POS                              (23U)
#define SF_CTRL_SF_IF_2_DAT_RW_LEN                              (1U)
#define SF_CTRL_SF_IF_2_DAT_RW_MSK                              (((1U<<SF_CTRL_SF_IF_2_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_2_DAT_RW_POS)
#define SF_CTRL_SF_IF_2_DAT_RW_UMSK                             (~(((1U<<SF_CTRL_SF_IF_2_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_2_DAT_RW_POS))
#define SF_CTRL_SF_IF_2_DAT_EN                                  SF_CTRL_SF_IF_2_DAT_EN
#define SF_CTRL_SF_IF_2_DAT_EN_POS                              (24U)
#define SF_CTRL_SF_IF_2_DAT_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_2_DAT_EN_MSK                              (((1U<<SF_CTRL_SF_IF_2_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_2_DAT_EN_POS)
#define SF_CTRL_SF_IF_2_DAT_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_2_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_2_DAT_EN_POS))
#define SF_CTRL_SF_IF_2_DMY_EN                                  SF_CTRL_SF_IF_2_DMY_EN
#define SF_CTRL_SF_IF_2_DMY_EN_POS                              (25U)
#define SF_CTRL_SF_IF_2_DMY_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_2_DMY_EN_MSK                              (((1U<<SF_CTRL_SF_IF_2_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_2_DMY_EN_POS)
#define SF_CTRL_SF_IF_2_DMY_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_2_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_2_DMY_EN_POS))
#define SF_CTRL_SF_IF_2_ADR_EN                                  SF_CTRL_SF_IF_2_ADR_EN
#define SF_CTRL_SF_IF_2_ADR_EN_POS                              (26U)
#define SF_CTRL_SF_IF_2_ADR_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_2_ADR_EN_MSK                              (((1U<<SF_CTRL_SF_IF_2_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_2_ADR_EN_POS)
#define SF_CTRL_SF_IF_2_ADR_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_2_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_2_ADR_EN_POS))
#define SF_CTRL_SF_IF_2_CMD_EN                                  SF_CTRL_SF_IF_2_CMD_EN
#define SF_CTRL_SF_IF_2_CMD_EN_POS                              (27U)
#define SF_CTRL_SF_IF_2_CMD_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_2_CMD_EN_MSK                              (((1U<<SF_CTRL_SF_IF_2_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_EN_POS)
#define SF_CTRL_SF_IF_2_CMD_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_2_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_EN_POS))
#define SF_CTRL_SF_IF_2_SPI_MODE                                SF_CTRL_SF_IF_2_SPI_MODE
#define SF_CTRL_SF_IF_2_SPI_MODE_POS                            (28U)
#define SF_CTRL_SF_IF_2_SPI_MODE_LEN                            (3U)
#define SF_CTRL_SF_IF_2_SPI_MODE_MSK                            (((1U<<SF_CTRL_SF_IF_2_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_2_SPI_MODE_POS)
#define SF_CTRL_SF_IF_2_SPI_MODE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_2_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_2_SPI_MODE_POS))
#define SF_CTRL_SF_IF_2_QPI_MODE_EN                             SF_CTRL_SF_IF_2_QPI_MODE_EN
#define SF_CTRL_SF_IF_2_QPI_MODE_EN_POS                         (31U)
#define SF_CTRL_SF_IF_2_QPI_MODE_EN_LEN                         (1U)
#define SF_CTRL_SF_IF_2_QPI_MODE_EN_MSK                         (((1U<<SF_CTRL_SF_IF_2_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_2_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_2_QPI_MODE_EN_UMSK                        (~(((1U<<SF_CTRL_SF_IF_2_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_2_QPI_MODE_EN_POS))

/* 0x7C : sf_if_iahb_4 */
#define SF_CTRL_SF_IF_IAHB_4_OFFSET                             (0x7C)
#define SF_CTRL_SF_IF_2_CMD_BUF_0                               SF_CTRL_SF_IF_2_CMD_BUF_0
#define SF_CTRL_SF_IF_2_CMD_BUF_0_POS                           (0U)
#define SF_CTRL_SF_IF_2_CMD_BUF_0_LEN                           (32U)
#define SF_CTRL_SF_IF_2_CMD_BUF_0_MSK                           (((1U<<SF_CTRL_SF_IF_2_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_2_CMD_BUF_0_UMSK                          (~(((1U<<SF_CTRL_SF_IF_2_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BUF_0_POS))

/* 0x80 : sf_if_iahb_5 */
#define SF_CTRL_SF_IF_IAHB_5_OFFSET                             (0x80)
#define SF_CTRL_SF_IF_2_CMD_BUF_1                               SF_CTRL_SF_IF_2_CMD_BUF_1
#define SF_CTRL_SF_IF_2_CMD_BUF_1_POS                           (0U)
#define SF_CTRL_SF_IF_2_CMD_BUF_1_LEN                           (32U)
#define SF_CTRL_SF_IF_2_CMD_BUF_1_MSK                           (((1U<<SF_CTRL_SF_IF_2_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_2_CMD_BUF_1_UMSK                          (~(((1U<<SF_CTRL_SF_IF_2_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_2_CMD_BUF_1_POS))

/* 0x84 : sf_if_iahb_6 */
#define SF_CTRL_SF_IF_IAHB_6_OFFSET                             (0x84)
#define SF_CTRL_SF_IF_3_ADR_BYTE                                SF_CTRL_SF_IF_3_ADR_BYTE
#define SF_CTRL_SF_IF_3_ADR_BYTE_POS                            (17U)
#define SF_CTRL_SF_IF_3_ADR_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_3_ADR_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_3_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_3_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_3_ADR_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_3_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_3_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_3_CMD_BYTE                                SF_CTRL_SF_IF_3_CMD_BYTE
#define SF_CTRL_SF_IF_3_CMD_BYTE_POS                            (20U)
#define SF_CTRL_SF_IF_3_CMD_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_3_CMD_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_3_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_3_CMD_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_3_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_3_ADR_EN                                  SF_CTRL_SF_IF_3_ADR_EN
#define SF_CTRL_SF_IF_3_ADR_EN_POS                              (26U)
#define SF_CTRL_SF_IF_3_ADR_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_3_ADR_EN_MSK                              (((1U<<SF_CTRL_SF_IF_3_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_3_ADR_EN_POS)
#define SF_CTRL_SF_IF_3_ADR_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_3_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_3_ADR_EN_POS))
#define SF_CTRL_SF_IF_3_CMD_EN                                  SF_CTRL_SF_IF_3_CMD_EN
#define SF_CTRL_SF_IF_3_CMD_EN_POS                              (27U)
#define SF_CTRL_SF_IF_3_CMD_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_3_CMD_EN_MSK                              (((1U<<SF_CTRL_SF_IF_3_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_EN_POS)
#define SF_CTRL_SF_IF_3_CMD_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_3_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_EN_POS))
#define SF_CTRL_SF_IF_3_SPI_MODE                                SF_CTRL_SF_IF_3_SPI_MODE
#define SF_CTRL_SF_IF_3_SPI_MODE_POS                            (28U)
#define SF_CTRL_SF_IF_3_SPI_MODE_LEN                            (3U)
#define SF_CTRL_SF_IF_3_SPI_MODE_MSK                            (((1U<<SF_CTRL_SF_IF_3_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_3_SPI_MODE_POS)
#define SF_CTRL_SF_IF_3_SPI_MODE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_3_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_3_SPI_MODE_POS))
#define SF_CTRL_SF_IF_3_QPI_MODE_EN                             SF_CTRL_SF_IF_3_QPI_MODE_EN
#define SF_CTRL_SF_IF_3_QPI_MODE_EN_POS                         (31U)
#define SF_CTRL_SF_IF_3_QPI_MODE_EN_LEN                         (1U)
#define SF_CTRL_SF_IF_3_QPI_MODE_EN_MSK                         (((1U<<SF_CTRL_SF_IF_3_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_3_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_3_QPI_MODE_EN_UMSK                        (~(((1U<<SF_CTRL_SF_IF_3_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_3_QPI_MODE_EN_POS))

/* 0x88 : sf_if_iahb_7 */
#define SF_CTRL_SF_IF_IAHB_7_OFFSET                             (0x88)
#define SF_CTRL_SF_IF_3_CMD_BUF_0                               SF_CTRL_SF_IF_3_CMD_BUF_0
#define SF_CTRL_SF_IF_3_CMD_BUF_0_POS                           (0U)
#define SF_CTRL_SF_IF_3_CMD_BUF_0_LEN                           (32U)
#define SF_CTRL_SF_IF_3_CMD_BUF_0_MSK                           (((1U<<SF_CTRL_SF_IF_3_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_3_CMD_BUF_0_UMSK                          (~(((1U<<SF_CTRL_SF_IF_3_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BUF_0_POS))

/* 0x8C : sf_if_iahb_8 */
#define SF_CTRL_SF_IF_IAHB_8_OFFSET                             (0x8C)
#define SF_CTRL_SF_IF_3_CMD_BUF_1                               SF_CTRL_SF_IF_3_CMD_BUF_1
#define SF_CTRL_SF_IF_3_CMD_BUF_1_POS                           (0U)
#define SF_CTRL_SF_IF_3_CMD_BUF_1_LEN                           (32U)
#define SF_CTRL_SF_IF_3_CMD_BUF_1_MSK                           (((1U<<SF_CTRL_SF_IF_3_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_3_CMD_BUF_1_UMSK                          (~(((1U<<SF_CTRL_SF_IF_3_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_3_CMD_BUF_1_POS))

/* 0x90 : sf_if_iahb_9 */
#define SF_CTRL_SF_IF_IAHB_9_OFFSET                             (0x90)
#define SF_CTRL_SF_IF_4_DMY_BYTE                                SF_CTRL_SF_IF_4_DMY_BYTE
#define SF_CTRL_SF_IF_4_DMY_BYTE_POS                            (12U)
#define SF_CTRL_SF_IF_4_DMY_BYTE_LEN                            (5U)
#define SF_CTRL_SF_IF_4_DMY_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_4_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_4_DMY_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_4_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_4_ADR_BYTE                                SF_CTRL_SF_IF_4_ADR_BYTE
#define SF_CTRL_SF_IF_4_ADR_BYTE_POS                            (17U)
#define SF_CTRL_SF_IF_4_ADR_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_4_ADR_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_4_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_4_ADR_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_4_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_4_CMD_BYTE                                SF_CTRL_SF_IF_4_CMD_BYTE
#define SF_CTRL_SF_IF_4_CMD_BYTE_POS                            (20U)
#define SF_CTRL_SF_IF_4_CMD_BYTE_LEN                            (3U)
#define SF_CTRL_SF_IF_4_CMD_BYTE_MSK                            (((1U<<SF_CTRL_SF_IF_4_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_4_CMD_BYTE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_4_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_4_DAT_RW                                  SF_CTRL_SF_IF_4_DAT_RW
#define SF_CTRL_SF_IF_4_DAT_RW_POS                              (23U)
#define SF_CTRL_SF_IF_4_DAT_RW_LEN                              (1U)
#define SF_CTRL_SF_IF_4_DAT_RW_MSK                              (((1U<<SF_CTRL_SF_IF_4_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_4_DAT_RW_POS)
#define SF_CTRL_SF_IF_4_DAT_RW_UMSK                             (~(((1U<<SF_CTRL_SF_IF_4_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF_4_DAT_RW_POS))
#define SF_CTRL_SF_IF_4_DAT_EN                                  SF_CTRL_SF_IF_4_DAT_EN
#define SF_CTRL_SF_IF_4_DAT_EN_POS                              (24U)
#define SF_CTRL_SF_IF_4_DAT_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_4_DAT_EN_MSK                              (((1U<<SF_CTRL_SF_IF_4_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_4_DAT_EN_POS)
#define SF_CTRL_SF_IF_4_DAT_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_4_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF_4_DAT_EN_POS))
#define SF_CTRL_SF_IF_4_DMY_EN                                  SF_CTRL_SF_IF_4_DMY_EN
#define SF_CTRL_SF_IF_4_DMY_EN_POS                              (25U)
#define SF_CTRL_SF_IF_4_DMY_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_4_DMY_EN_MSK                              (((1U<<SF_CTRL_SF_IF_4_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_4_DMY_EN_POS)
#define SF_CTRL_SF_IF_4_DMY_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_4_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF_4_DMY_EN_POS))
#define SF_CTRL_SF_IF_4_ADR_EN                                  SF_CTRL_SF_IF_4_ADR_EN
#define SF_CTRL_SF_IF_4_ADR_EN_POS                              (26U)
#define SF_CTRL_SF_IF_4_ADR_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_4_ADR_EN_MSK                              (((1U<<SF_CTRL_SF_IF_4_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_4_ADR_EN_POS)
#define SF_CTRL_SF_IF_4_ADR_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_4_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF_4_ADR_EN_POS))
#define SF_CTRL_SF_IF_4_CMD_EN                                  SF_CTRL_SF_IF_4_CMD_EN
#define SF_CTRL_SF_IF_4_CMD_EN_POS                              (27U)
#define SF_CTRL_SF_IF_4_CMD_EN_LEN                              (1U)
#define SF_CTRL_SF_IF_4_CMD_EN_MSK                              (((1U<<SF_CTRL_SF_IF_4_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_EN_POS)
#define SF_CTRL_SF_IF_4_CMD_EN_UMSK                             (~(((1U<<SF_CTRL_SF_IF_4_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_EN_POS))
#define SF_CTRL_SF_IF_4_SPI_MODE                                SF_CTRL_SF_IF_4_SPI_MODE
#define SF_CTRL_SF_IF_4_SPI_MODE_POS                            (28U)
#define SF_CTRL_SF_IF_4_SPI_MODE_LEN                            (3U)
#define SF_CTRL_SF_IF_4_SPI_MODE_MSK                            (((1U<<SF_CTRL_SF_IF_4_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_4_SPI_MODE_POS)
#define SF_CTRL_SF_IF_4_SPI_MODE_UMSK                           (~(((1U<<SF_CTRL_SF_IF_4_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF_4_SPI_MODE_POS))
#define SF_CTRL_SF_IF_4_QPI_MODE_EN                             SF_CTRL_SF_IF_4_QPI_MODE_EN
#define SF_CTRL_SF_IF_4_QPI_MODE_EN_POS                         (31U)
#define SF_CTRL_SF_IF_4_QPI_MODE_EN_LEN                         (1U)
#define SF_CTRL_SF_IF_4_QPI_MODE_EN_MSK                         (((1U<<SF_CTRL_SF_IF_4_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_4_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_4_QPI_MODE_EN_UMSK                        (~(((1U<<SF_CTRL_SF_IF_4_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF_4_QPI_MODE_EN_POS))

/* 0x94 : sf_if_iahb_10 */
#define SF_CTRL_SF_IF_IAHB_10_OFFSET                            (0x94)
#define SF_CTRL_SF_IF_4_CMD_BUF_0                               SF_CTRL_SF_IF_4_CMD_BUF_0
#define SF_CTRL_SF_IF_4_CMD_BUF_0_POS                           (0U)
#define SF_CTRL_SF_IF_4_CMD_BUF_0_LEN                           (32U)
#define SF_CTRL_SF_IF_4_CMD_BUF_0_MSK                           (((1U<<SF_CTRL_SF_IF_4_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_4_CMD_BUF_0_UMSK                          (~(((1U<<SF_CTRL_SF_IF_4_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BUF_0_POS))

/* 0x98 : sf_if_iahb_11 */
#define SF_CTRL_SF_IF_IAHB_11_OFFSET                            (0x98)
#define SF_CTRL_SF_IF_4_CMD_BUF_1                               SF_CTRL_SF_IF_4_CMD_BUF_1
#define SF_CTRL_SF_IF_4_CMD_BUF_1_POS                           (0U)
#define SF_CTRL_SF_IF_4_CMD_BUF_1_LEN                           (32U)
#define SF_CTRL_SF_IF_4_CMD_BUF_1_MSK                           (((1U<<SF_CTRL_SF_IF_4_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_4_CMD_BUF_1_UMSK                          (~(((1U<<SF_CTRL_SF_IF_4_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF_4_CMD_BUF_1_POS))

/* 0x9C : sf_if_iahb_12 */
#define SF_CTRL_SF_IF_IAHB_12_OFFSET                            (0x9C)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL                           SF_CTRL_SF2_CLK_SF_RX_INV_SEL
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL_POS                       (2U)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL_LEN                       (1U)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL_MSK                       (((1U<<SF_CTRL_SF2_CLK_SF_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_SF_RX_INV_SEL_POS)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SEL_UMSK                      (~(((1U<<SF_CTRL_SF2_CLK_SF_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_SF_RX_INV_SEL_POS))
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC                           SF_CTRL_SF2_CLK_SF_RX_INV_SRC
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC_POS                       (3U)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC_LEN                       (1U)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC_MSK                       (((1U<<SF_CTRL_SF2_CLK_SF_RX_INV_SRC_LEN)-1)<<SF_CTRL_SF2_CLK_SF_RX_INV_SRC_POS)
#define SF_CTRL_SF2_CLK_SF_RX_INV_SRC_UMSK                      (~(((1U<<SF_CTRL_SF2_CLK_SF_RX_INV_SRC_LEN)-1)<<SF_CTRL_SF2_CLK_SF_RX_INV_SRC_POS))
#define SF_CTRL_SF2_CLK_OUT_INV_SEL                             SF_CTRL_SF2_CLK_OUT_INV_SEL
#define SF_CTRL_SF2_CLK_OUT_INV_SEL_POS                         (4U)
#define SF_CTRL_SF2_CLK_OUT_INV_SEL_LEN                         (1U)
#define SF_CTRL_SF2_CLK_OUT_INV_SEL_MSK                         (((1U<<SF_CTRL_SF2_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_OUT_INV_SEL_POS)
#define SF_CTRL_SF2_CLK_OUT_INV_SEL_UMSK                        (~(((1U<<SF_CTRL_SF2_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF2_CLK_OUT_INV_SEL_POS))
#define SF_CTRL_SF3_CLK_OUT_INV_SEL                             SF_CTRL_SF3_CLK_OUT_INV_SEL
#define SF_CTRL_SF3_CLK_OUT_INV_SEL_POS                         (5U)
#define SF_CTRL_SF3_CLK_OUT_INV_SEL_LEN                         (1U)
#define SF_CTRL_SF3_CLK_OUT_INV_SEL_MSK                         (((1U<<SF_CTRL_SF3_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF3_CLK_OUT_INV_SEL_POS)
#define SF_CTRL_SF3_CLK_OUT_INV_SEL_UMSK                        (~(((1U<<SF_CTRL_SF3_CLK_OUT_INV_SEL_LEN)-1)<<SF_CTRL_SF3_CLK_OUT_INV_SEL_POS))
#define SF_CTRL_SF2_IF_READ_DLY_N                               SF_CTRL_SF2_IF_READ_DLY_N
#define SF_CTRL_SF2_IF_READ_DLY_N_POS                           (8U)
#define SF_CTRL_SF2_IF_READ_DLY_N_LEN                           (3U)
#define SF_CTRL_SF2_IF_READ_DLY_N_MSK                           (((1U<<SF_CTRL_SF2_IF_READ_DLY_N_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_N_POS)
#define SF_CTRL_SF2_IF_READ_DLY_N_UMSK                          (~(((1U<<SF_CTRL_SF2_IF_READ_DLY_N_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_N_POS))
#define SF_CTRL_SF2_IF_READ_DLY_EN                              SF_CTRL_SF2_IF_READ_DLY_EN
#define SF_CTRL_SF2_IF_READ_DLY_EN_POS                          (11U)
#define SF_CTRL_SF2_IF_READ_DLY_EN_LEN                          (1U)
#define SF_CTRL_SF2_IF_READ_DLY_EN_MSK                          (((1U<<SF_CTRL_SF2_IF_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_EN_POS)
#define SF_CTRL_SF2_IF_READ_DLY_EN_UMSK                         (~(((1U<<SF_CTRL_SF2_IF_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_EN_POS))
#define SF_CTRL_SF2_IF_READ_DLY_SRC                             SF_CTRL_SF2_IF_READ_DLY_SRC
#define SF_CTRL_SF2_IF_READ_DLY_SRC_POS                         (12U)
#define SF_CTRL_SF2_IF_READ_DLY_SRC_LEN                         (1U)
#define SF_CTRL_SF2_IF_READ_DLY_SRC_MSK                         (((1U<<SF_CTRL_SF2_IF_READ_DLY_SRC_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_SRC_POS)
#define SF_CTRL_SF2_IF_READ_DLY_SRC_UMSK                        (~(((1U<<SF_CTRL_SF2_IF_READ_DLY_SRC_LEN)-1)<<SF_CTRL_SF2_IF_READ_DLY_SRC_POS))

/* 0xA0 : sf_id0_offset */
#define SF_CTRL_SF_ID0_OFFSET_OFFSET                            (0xA0)
#define SF_CTRL_SF_ID0_OFFSET                                   SF_CTRL_SF_ID0_OFFSET
#define SF_CTRL_SF_ID0_OFFSET_POS                               (0U)
#define SF_CTRL_SF_ID0_OFFSET_LEN                               (28U)
#define SF_CTRL_SF_ID0_OFFSET_MSK                               (((1U<<SF_CTRL_SF_ID0_OFFSET_LEN)-1)<<SF_CTRL_SF_ID0_OFFSET_POS)
#define SF_CTRL_SF_ID0_OFFSET_UMSK                              (~(((1U<<SF_CTRL_SF_ID0_OFFSET_LEN)-1)<<SF_CTRL_SF_ID0_OFFSET_POS))

/* 0xA4 : sf_id1_offset */
#define SF_CTRL_SF_ID1_OFFSET_OFFSET                            (0xA4)
#define SF_CTRL_SF_ID1_OFFSET                                   SF_CTRL_SF_ID1_OFFSET
#define SF_CTRL_SF_ID1_OFFSET_POS                               (0U)
#define SF_CTRL_SF_ID1_OFFSET_LEN                               (28U)
#define SF_CTRL_SF_ID1_OFFSET_MSK                               (((1U<<SF_CTRL_SF_ID1_OFFSET_LEN)-1)<<SF_CTRL_SF_ID1_OFFSET_POS)
#define SF_CTRL_SF_ID1_OFFSET_UMSK                              (~(((1U<<SF_CTRL_SF_ID1_OFFSET_LEN)-1)<<SF_CTRL_SF_ID1_OFFSET_POS))

/* 0xA8 : sf_bk2_id0_offset */
#define SF_CTRL_SF_BK2_ID0_OFFSET_OFFSET                        (0xA8)
#define SF_CTRL_SF_BK2_ID0_OFFSET                               SF_CTRL_SF_BK2_ID0_OFFSET
#define SF_CTRL_SF_BK2_ID0_OFFSET_POS                           (0U)
#define SF_CTRL_SF_BK2_ID0_OFFSET_LEN                           (28U)
#define SF_CTRL_SF_BK2_ID0_OFFSET_MSK                           (((1U<<SF_CTRL_SF_BK2_ID0_OFFSET_LEN)-1)<<SF_CTRL_SF_BK2_ID0_OFFSET_POS)
#define SF_CTRL_SF_BK2_ID0_OFFSET_UMSK                          (~(((1U<<SF_CTRL_SF_BK2_ID0_OFFSET_LEN)-1)<<SF_CTRL_SF_BK2_ID0_OFFSET_POS))

/* 0xAC : sf_bk2_id1_offset */
#define SF_CTRL_SF_BK2_ID1_OFFSET_OFFSET                        (0xAC)
#define SF_CTRL_SF_BK2_ID1_OFFSET                               SF_CTRL_SF_BK2_ID1_OFFSET
#define SF_CTRL_SF_BK2_ID1_OFFSET_POS                           (0U)
#define SF_CTRL_SF_BK2_ID1_OFFSET_LEN                           (28U)
#define SF_CTRL_SF_BK2_ID1_OFFSET_MSK                           (((1U<<SF_CTRL_SF_BK2_ID1_OFFSET_LEN)-1)<<SF_CTRL_SF_BK2_ID1_OFFSET_POS)
#define SF_CTRL_SF_BK2_ID1_OFFSET_UMSK                          (~(((1U<<SF_CTRL_SF_BK2_ID1_OFFSET_LEN)-1)<<SF_CTRL_SF_BK2_ID1_OFFSET_POS))

/* 0xB0 : sf_dbg */
#define SF_CTRL_SF_DBG_OFFSET                                   (0xB0)
#define SF_CTRL_SF_AUTOLOAD_ST                                  SF_CTRL_SF_AUTOLOAD_ST
#define SF_CTRL_SF_AUTOLOAD_ST_POS                              (0U)
#define SF_CTRL_SF_AUTOLOAD_ST_LEN                              (5U)
#define SF_CTRL_SF_AUTOLOAD_ST_MSK                              (((1U<<SF_CTRL_SF_AUTOLOAD_ST_LEN)-1)<<SF_CTRL_SF_AUTOLOAD_ST_POS)
#define SF_CTRL_SF_AUTOLOAD_ST_UMSK                             (~(((1U<<SF_CTRL_SF_AUTOLOAD_ST_LEN)-1)<<SF_CTRL_SF_AUTOLOAD_ST_POS))
#define SF_CTRL_SF_AUTOLOAD_ST_DONE                             SF_CTRL_SF_AUTOLOAD_ST_DONE
#define SF_CTRL_SF_AUTOLOAD_ST_DONE_POS                         (5U)
#define SF_CTRL_SF_AUTOLOAD_ST_DONE_LEN                         (1U)
#define SF_CTRL_SF_AUTOLOAD_ST_DONE_MSK                         (((1U<<SF_CTRL_SF_AUTOLOAD_ST_DONE_LEN)-1)<<SF_CTRL_SF_AUTOLOAD_ST_DONE_POS)
#define SF_CTRL_SF_AUTOLOAD_ST_DONE_UMSK                        (~(((1U<<SF_CTRL_SF_AUTOLOAD_ST_DONE_LEN)-1)<<SF_CTRL_SF_AUTOLOAD_ST_DONE_POS))

/* 0xC0 : sf_if2_ctrl_0 */
#define SF_CTRL_SF_IF2_CTRL_0_OFFSET                            (0xC0)
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL                        SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_POS                    (2U)
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_LEN                    (1U)
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_MSK                    (((1U<<SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_POS)
#define SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_UMSK                   (~(((1U<<SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_LEN)-1)<<SF_CTRL_SF_CLK_SF_IF2_RX_INV_SEL_POS))
#define SF_CTRL_SF_IF2_READ_DLY_N                               SF_CTRL_SF_IF2_READ_DLY_N
#define SF_CTRL_SF_IF2_READ_DLY_N_POS                           (8U)
#define SF_CTRL_SF_IF2_READ_DLY_N_LEN                           (3U)
#define SF_CTRL_SF_IF2_READ_DLY_N_MSK                           (((1U<<SF_CTRL_SF_IF2_READ_DLY_N_LEN)-1)<<SF_CTRL_SF_IF2_READ_DLY_N_POS)
#define SF_CTRL_SF_IF2_READ_DLY_N_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_READ_DLY_N_LEN)-1)<<SF_CTRL_SF_IF2_READ_DLY_N_POS))
#define SF_CTRL_SF_IF2_READ_DLY_EN                              SF_CTRL_SF_IF2_READ_DLY_EN
#define SF_CTRL_SF_IF2_READ_DLY_EN_POS                          (11U)
#define SF_CTRL_SF_IF2_READ_DLY_EN_LEN                          (1U)
#define SF_CTRL_SF_IF2_READ_DLY_EN_MSK                          (((1U<<SF_CTRL_SF_IF2_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF_IF2_READ_DLY_EN_POS)
#define SF_CTRL_SF_IF2_READ_DLY_EN_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_READ_DLY_EN_LEN)-1)<<SF_CTRL_SF_IF2_READ_DLY_EN_POS))
#define SF_CTRL_SF_IF2_INT                                      SF_CTRL_SF_IF2_INT
#define SF_CTRL_SF_IF2_INT_POS                                  (16U)
#define SF_CTRL_SF_IF2_INT_LEN                                  (1U)
#define SF_CTRL_SF_IF2_INT_MSK                                  (((1U<<SF_CTRL_SF_IF2_INT_LEN)-1)<<SF_CTRL_SF_IF2_INT_POS)
#define SF_CTRL_SF_IF2_INT_UMSK                                 (~(((1U<<SF_CTRL_SF_IF2_INT_LEN)-1)<<SF_CTRL_SF_IF2_INT_POS))
#define SF_CTRL_SF_IF2_INT_CLR                                  SF_CTRL_SF_IF2_INT_CLR
#define SF_CTRL_SF_IF2_INT_CLR_POS                              (17U)
#define SF_CTRL_SF_IF2_INT_CLR_LEN                              (1U)
#define SF_CTRL_SF_IF2_INT_CLR_MSK                              (((1U<<SF_CTRL_SF_IF2_INT_CLR_LEN)-1)<<SF_CTRL_SF_IF2_INT_CLR_POS)
#define SF_CTRL_SF_IF2_INT_CLR_UMSK                             (~(((1U<<SF_CTRL_SF_IF2_INT_CLR_LEN)-1)<<SF_CTRL_SF_IF2_INT_CLR_POS))
#define SF_CTRL_SF_IF2_INT_SET                                  SF_CTRL_SF_IF2_INT_SET
#define SF_CTRL_SF_IF2_INT_SET_POS                              (18U)
#define SF_CTRL_SF_IF2_INT_SET_LEN                              (1U)
#define SF_CTRL_SF_IF2_INT_SET_MSK                              (((1U<<SF_CTRL_SF_IF2_INT_SET_LEN)-1)<<SF_CTRL_SF_IF2_INT_SET_POS)
#define SF_CTRL_SF_IF2_INT_SET_UMSK                             (~(((1U<<SF_CTRL_SF_IF2_INT_SET_LEN)-1)<<SF_CTRL_SF_IF2_INT_SET_POS))
#define SF_CTRL_SF_IF2_REPLACE_SF1                              SF_CTRL_SF_IF2_REPLACE_SF1
#define SF_CTRL_SF_IF2_REPLACE_SF1_POS                          (23U)
#define SF_CTRL_SF_IF2_REPLACE_SF1_LEN                          (1U)
#define SF_CTRL_SF_IF2_REPLACE_SF1_MSK                          (((1U<<SF_CTRL_SF_IF2_REPLACE_SF1_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF1_POS)
#define SF_CTRL_SF_IF2_REPLACE_SF1_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_REPLACE_SF1_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF1_POS))
#define SF_CTRL_SF_IF2_REPLACE_SF2                              SF_CTRL_SF_IF2_REPLACE_SF2
#define SF_CTRL_SF_IF2_REPLACE_SF2_POS                          (24U)
#define SF_CTRL_SF_IF2_REPLACE_SF2_LEN                          (1U)
#define SF_CTRL_SF_IF2_REPLACE_SF2_MSK                          (((1U<<SF_CTRL_SF_IF2_REPLACE_SF2_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF2_POS)
#define SF_CTRL_SF_IF2_REPLACE_SF2_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_REPLACE_SF2_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF2_POS))
#define SF_CTRL_SF_IF2_REPLACE_SF3                              SF_CTRL_SF_IF2_REPLACE_SF3
#define SF_CTRL_SF_IF2_REPLACE_SF3_POS                          (25U)
#define SF_CTRL_SF_IF2_REPLACE_SF3_LEN                          (1U)
#define SF_CTRL_SF_IF2_REPLACE_SF3_MSK                          (((1U<<SF_CTRL_SF_IF2_REPLACE_SF3_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF3_POS)
#define SF_CTRL_SF_IF2_REPLACE_SF3_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_REPLACE_SF3_LEN)-1)<<SF_CTRL_SF_IF2_REPLACE_SF3_POS))
#define SF_CTRL_SF_IF2_PAD_SEL                                  SF_CTRL_SF_IF2_PAD_SEL
#define SF_CTRL_SF_IF2_PAD_SEL_POS                              (26U)
#define SF_CTRL_SF_IF2_PAD_SEL_LEN                              (2U)
#define SF_CTRL_SF_IF2_PAD_SEL_MSK                              (((1U<<SF_CTRL_SF_IF2_PAD_SEL_LEN)-1)<<SF_CTRL_SF_IF2_PAD_SEL_POS)
#define SF_CTRL_SF_IF2_PAD_SEL_UMSK                             (~(((1U<<SF_CTRL_SF_IF2_PAD_SEL_LEN)-1)<<SF_CTRL_SF_IF2_PAD_SEL_POS))
#define SF_CTRL_SF_IF2_BK_SWAP                                  SF_CTRL_SF_IF2_BK_SWAP
#define SF_CTRL_SF_IF2_BK_SWAP_POS                              (28U)
#define SF_CTRL_SF_IF2_BK_SWAP_LEN                              (1U)
#define SF_CTRL_SF_IF2_BK_SWAP_MSK                              (((1U<<SF_CTRL_SF_IF2_BK_SWAP_LEN)-1)<<SF_CTRL_SF_IF2_BK_SWAP_POS)
#define SF_CTRL_SF_IF2_BK_SWAP_UMSK                             (~(((1U<<SF_CTRL_SF_IF2_BK_SWAP_LEN)-1)<<SF_CTRL_SF_IF2_BK_SWAP_POS))
#define SF_CTRL_SF_IF2_BK2_MODE                                 SF_CTRL_SF_IF2_BK2_MODE
#define SF_CTRL_SF_IF2_BK2_MODE_POS                             (29U)
#define SF_CTRL_SF_IF2_BK2_MODE_LEN                             (1U)
#define SF_CTRL_SF_IF2_BK2_MODE_MSK                             (((1U<<SF_CTRL_SF_IF2_BK2_MODE_LEN)-1)<<SF_CTRL_SF_IF2_BK2_MODE_POS)
#define SF_CTRL_SF_IF2_BK2_MODE_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_BK2_MODE_LEN)-1)<<SF_CTRL_SF_IF2_BK2_MODE_POS))
#define SF_CTRL_SF_IF2_BK2_EN                                   SF_CTRL_SF_IF2_BK2_EN
#define SF_CTRL_SF_IF2_BK2_EN_POS                               (30U)
#define SF_CTRL_SF_IF2_BK2_EN_LEN                               (1U)
#define SF_CTRL_SF_IF2_BK2_EN_MSK                               (((1U<<SF_CTRL_SF_IF2_BK2_EN_LEN)-1)<<SF_CTRL_SF_IF2_BK2_EN_POS)
#define SF_CTRL_SF_IF2_BK2_EN_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_BK2_EN_LEN)-1)<<SF_CTRL_SF_IF2_BK2_EN_POS))
#define SF_CTRL_SF_IF2_BK_SEL                                   SF_CTRL_SF_IF2_BK_SEL
#define SF_CTRL_SF_IF2_BK_SEL_POS                               (31U)
#define SF_CTRL_SF_IF2_BK_SEL_LEN                               (1U)
#define SF_CTRL_SF_IF2_BK_SEL_MSK                               (((1U<<SF_CTRL_SF_IF2_BK_SEL_LEN)-1)<<SF_CTRL_SF_IF2_BK_SEL_POS)
#define SF_CTRL_SF_IF2_BK_SEL_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_BK_SEL_LEN)-1)<<SF_CTRL_SF_IF2_BK_SEL_POS))

/* 0xC4 : sf_if2_ctrl_1 */
#define SF_CTRL_SF_IF2_CTRL_1_OFFSET                            (0xC4)
#define SF_CTRL_SF_IF2_SR_PAT_MASK                              SF_CTRL_SF_IF2_SR_PAT_MASK
#define SF_CTRL_SF_IF2_SR_PAT_MASK_POS                          (0U)
#define SF_CTRL_SF_IF2_SR_PAT_MASK_LEN                          (8U)
#define SF_CTRL_SF_IF2_SR_PAT_MASK_MSK                          (((1U<<SF_CTRL_SF_IF2_SR_PAT_MASK_LEN)-1)<<SF_CTRL_SF_IF2_SR_PAT_MASK_POS)
#define SF_CTRL_SF_IF2_SR_PAT_MASK_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_SR_PAT_MASK_LEN)-1)<<SF_CTRL_SF_IF2_SR_PAT_MASK_POS))
#define SF_CTRL_SF_IF2_SR_PAT                                   SF_CTRL_SF_IF2_SR_PAT
#define SF_CTRL_SF_IF2_SR_PAT_POS                               (8U)
#define SF_CTRL_SF_IF2_SR_PAT_LEN                               (8U)
#define SF_CTRL_SF_IF2_SR_PAT_MSK                               (((1U<<SF_CTRL_SF_IF2_SR_PAT_LEN)-1)<<SF_CTRL_SF_IF2_SR_PAT_POS)
#define SF_CTRL_SF_IF2_SR_PAT_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_SR_PAT_LEN)-1)<<SF_CTRL_SF_IF2_SR_PAT_POS))
#define SF_CTRL_SF_IF2_SR_INT                                   SF_CTRL_SF_IF2_SR_INT
#define SF_CTRL_SF_IF2_SR_INT_POS                               (16U)
#define SF_CTRL_SF_IF2_SR_INT_LEN                               (1U)
#define SF_CTRL_SF_IF2_SR_INT_MSK                               (((1U<<SF_CTRL_SF_IF2_SR_INT_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_POS)
#define SF_CTRL_SF_IF2_SR_INT_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_SR_INT_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_POS))
#define SF_CTRL_SF_IF2_SR_INT_EN                                SF_CTRL_SF_IF2_SR_INT_EN
#define SF_CTRL_SF_IF2_SR_INT_EN_POS                            (17U)
#define SF_CTRL_SF_IF2_SR_INT_EN_LEN                            (1U)
#define SF_CTRL_SF_IF2_SR_INT_EN_MSK                            (((1U<<SF_CTRL_SF_IF2_SR_INT_EN_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_EN_POS)
#define SF_CTRL_SF_IF2_SR_INT_EN_UMSK                           (~(((1U<<SF_CTRL_SF_IF2_SR_INT_EN_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_EN_POS))
#define SF_CTRL_SF_IF2_SR_INT_SET                               SF_CTRL_SF_IF2_SR_INT_SET
#define SF_CTRL_SF_IF2_SR_INT_SET_POS                           (18U)
#define SF_CTRL_SF_IF2_SR_INT_SET_LEN                           (1U)
#define SF_CTRL_SF_IF2_SR_INT_SET_MSK                           (((1U<<SF_CTRL_SF_IF2_SR_INT_SET_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_SET_POS)
#define SF_CTRL_SF_IF2_SR_INT_SET_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_SR_INT_SET_LEN)-1)<<SF_CTRL_SF_IF2_SR_INT_SET_POS))
#define SF_CTRL_SF_IF2_ACK_LAT                                  SF_CTRL_SF_IF2_ACK_LAT
#define SF_CTRL_SF_IF2_ACK_LAT_POS                              (20U)
#define SF_CTRL_SF_IF2_ACK_LAT_LEN                              (3U)
#define SF_CTRL_SF_IF2_ACK_LAT_MSK                              (((1U<<SF_CTRL_SF_IF2_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF2_ACK_LAT_POS)
#define SF_CTRL_SF_IF2_ACK_LAT_UMSK                             (~(((1U<<SF_CTRL_SF_IF2_ACK_LAT_LEN)-1)<<SF_CTRL_SF_IF2_ACK_LAT_POS))
#define SF_CTRL_SF_IF2_REG_HOLD                                 SF_CTRL_SF_IF2_REG_HOLD
#define SF_CTRL_SF_IF2_REG_HOLD_POS                             (24U)
#define SF_CTRL_SF_IF2_REG_HOLD_LEN                             (1U)
#define SF_CTRL_SF_IF2_REG_HOLD_MSK                             (((1U<<SF_CTRL_SF_IF2_REG_HOLD_LEN)-1)<<SF_CTRL_SF_IF2_REG_HOLD_POS)
#define SF_CTRL_SF_IF2_REG_HOLD_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_REG_HOLD_LEN)-1)<<SF_CTRL_SF_IF2_REG_HOLD_POS))
#define SF_CTRL_SF_IF2_REG_WP                                   SF_CTRL_SF_IF2_REG_WP
#define SF_CTRL_SF_IF2_REG_WP_POS                               (25U)
#define SF_CTRL_SF_IF2_REG_WP_LEN                               (1U)
#define SF_CTRL_SF_IF2_REG_WP_MSK                               (((1U<<SF_CTRL_SF_IF2_REG_WP_LEN)-1)<<SF_CTRL_SF_IF2_REG_WP_POS)
#define SF_CTRL_SF_IF2_REG_WP_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_REG_WP_LEN)-1)<<SF_CTRL_SF_IF2_REG_WP_POS))
#define SF_CTRL_SF_IF2_FN_SEL                                   SF_CTRL_SF_IF2_FN_SEL
#define SF_CTRL_SF_IF2_FN_SEL_POS                               (28U)
#define SF_CTRL_SF_IF2_FN_SEL_LEN                               (1U)
#define SF_CTRL_SF_IF2_FN_SEL_MSK                               (((1U<<SF_CTRL_SF_IF2_FN_SEL_LEN)-1)<<SF_CTRL_SF_IF2_FN_SEL_POS)
#define SF_CTRL_SF_IF2_FN_SEL_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_FN_SEL_LEN)-1)<<SF_CTRL_SF_IF2_FN_SEL_POS))
#define SF_CTRL_SF_IF2_EN                                       SF_CTRL_SF_IF2_EN
#define SF_CTRL_SF_IF2_EN_POS                                   (29U)
#define SF_CTRL_SF_IF2_EN_LEN                                   (1U)
#define SF_CTRL_SF_IF2_EN_MSK                                   (((1U<<SF_CTRL_SF_IF2_EN_LEN)-1)<<SF_CTRL_SF_IF2_EN_POS)
#define SF_CTRL_SF_IF2_EN_UMSK                                  (~(((1U<<SF_CTRL_SF_IF2_EN_LEN)-1)<<SF_CTRL_SF_IF2_EN_POS))

/* 0xC8 : sf_if2_sahb_0 */
#define SF_CTRL_SF_IF2_SAHB_0_OFFSET                            (0xC8)
#define SF_CTRL_SF_IF2_BUSY                                     SF_CTRL_SF_IF2_BUSY
#define SF_CTRL_SF_IF2_BUSY_POS                                 (0U)
#define SF_CTRL_SF_IF2_BUSY_LEN                                 (1U)
#define SF_CTRL_SF_IF2_BUSY_MSK                                 (((1U<<SF_CTRL_SF_IF2_BUSY_LEN)-1)<<SF_CTRL_SF_IF2_BUSY_POS)
#define SF_CTRL_SF_IF2_BUSY_UMSK                                (~(((1U<<SF_CTRL_SF_IF2_BUSY_LEN)-1)<<SF_CTRL_SF_IF2_BUSY_POS))
#define SF_CTRL_SF_IF2_0_TRIG                                   SF_CTRL_SF_IF2_0_TRIG
#define SF_CTRL_SF_IF2_0_TRIG_POS                               (1U)
#define SF_CTRL_SF_IF2_0_TRIG_LEN                               (1U)
#define SF_CTRL_SF_IF2_0_TRIG_MSK                               (((1U<<SF_CTRL_SF_IF2_0_TRIG_LEN)-1)<<SF_CTRL_SF_IF2_0_TRIG_POS)
#define SF_CTRL_SF_IF2_0_TRIG_UMSK                              (~(((1U<<SF_CTRL_SF_IF2_0_TRIG_LEN)-1)<<SF_CTRL_SF_IF2_0_TRIG_POS))
#define SF_CTRL_SF_IF2_0_DAT_BYTE                               SF_CTRL_SF_IF2_0_DAT_BYTE
#define SF_CTRL_SF_IF2_0_DAT_BYTE_POS                           (2U)
#define SF_CTRL_SF_IF2_0_DAT_BYTE_LEN                           (10U)
#define SF_CTRL_SF_IF2_0_DAT_BYTE_MSK                           (((1U<<SF_CTRL_SF_IF2_0_DAT_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_BYTE_POS)
#define SF_CTRL_SF_IF2_0_DAT_BYTE_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_0_DAT_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_BYTE_POS))
#define SF_CTRL_SF_IF2_0_DMY_BYTE                               SF_CTRL_SF_IF2_0_DMY_BYTE
#define SF_CTRL_SF_IF2_0_DMY_BYTE_POS                           (12U)
#define SF_CTRL_SF_IF2_0_DMY_BYTE_LEN                           (5U)
#define SF_CTRL_SF_IF2_0_DMY_BYTE_MSK                           (((1U<<SF_CTRL_SF_IF2_0_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_DMY_BYTE_POS)
#define SF_CTRL_SF_IF2_0_DMY_BYTE_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_0_DMY_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_DMY_BYTE_POS))
#define SF_CTRL_SF_IF2_0_ADR_BYTE                               SF_CTRL_SF_IF2_0_ADR_BYTE
#define SF_CTRL_SF_IF2_0_ADR_BYTE_POS                           (17U)
#define SF_CTRL_SF_IF2_0_ADR_BYTE_LEN                           (3U)
#define SF_CTRL_SF_IF2_0_ADR_BYTE_MSK                           (((1U<<SF_CTRL_SF_IF2_0_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_ADR_BYTE_POS)
#define SF_CTRL_SF_IF2_0_ADR_BYTE_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_0_ADR_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_ADR_BYTE_POS))
#define SF_CTRL_SF_IF2_0_CMD_BYTE                               SF_CTRL_SF_IF2_0_CMD_BYTE
#define SF_CTRL_SF_IF2_0_CMD_BYTE_POS                           (20U)
#define SF_CTRL_SF_IF2_0_CMD_BYTE_LEN                           (3U)
#define SF_CTRL_SF_IF2_0_CMD_BYTE_MSK                           (((1U<<SF_CTRL_SF_IF2_0_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BYTE_POS)
#define SF_CTRL_SF_IF2_0_CMD_BYTE_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_0_CMD_BYTE_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BYTE_POS))
#define SF_CTRL_SF_IF2_0_DAT_RW                                 SF_CTRL_SF_IF2_0_DAT_RW
#define SF_CTRL_SF_IF2_0_DAT_RW_POS                             (23U)
#define SF_CTRL_SF_IF2_0_DAT_RW_LEN                             (1U)
#define SF_CTRL_SF_IF2_0_DAT_RW_MSK                             (((1U<<SF_CTRL_SF_IF2_0_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_RW_POS)
#define SF_CTRL_SF_IF2_0_DAT_RW_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_0_DAT_RW_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_RW_POS))
#define SF_CTRL_SF_IF2_0_DAT_EN                                 SF_CTRL_SF_IF2_0_DAT_EN
#define SF_CTRL_SF_IF2_0_DAT_EN_POS                             (24U)
#define SF_CTRL_SF_IF2_0_DAT_EN_LEN                             (1U)
#define SF_CTRL_SF_IF2_0_DAT_EN_MSK                             (((1U<<SF_CTRL_SF_IF2_0_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_EN_POS)
#define SF_CTRL_SF_IF2_0_DAT_EN_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_0_DAT_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_DAT_EN_POS))
#define SF_CTRL_SF_IF2_0_DMY_EN                                 SF_CTRL_SF_IF2_0_DMY_EN
#define SF_CTRL_SF_IF2_0_DMY_EN_POS                             (25U)
#define SF_CTRL_SF_IF2_0_DMY_EN_LEN                             (1U)
#define SF_CTRL_SF_IF2_0_DMY_EN_MSK                             (((1U<<SF_CTRL_SF_IF2_0_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_DMY_EN_POS)
#define SF_CTRL_SF_IF2_0_DMY_EN_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_0_DMY_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_DMY_EN_POS))
#define SF_CTRL_SF_IF2_0_ADR_EN                                 SF_CTRL_SF_IF2_0_ADR_EN
#define SF_CTRL_SF_IF2_0_ADR_EN_POS                             (26U)
#define SF_CTRL_SF_IF2_0_ADR_EN_LEN                             (1U)
#define SF_CTRL_SF_IF2_0_ADR_EN_MSK                             (((1U<<SF_CTRL_SF_IF2_0_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_ADR_EN_POS)
#define SF_CTRL_SF_IF2_0_ADR_EN_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_0_ADR_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_ADR_EN_POS))
#define SF_CTRL_SF_IF2_0_CMD_EN                                 SF_CTRL_SF_IF2_0_CMD_EN
#define SF_CTRL_SF_IF2_0_CMD_EN_POS                             (27U)
#define SF_CTRL_SF_IF2_0_CMD_EN_LEN                             (1U)
#define SF_CTRL_SF_IF2_0_CMD_EN_MSK                             (((1U<<SF_CTRL_SF_IF2_0_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_EN_POS)
#define SF_CTRL_SF_IF2_0_CMD_EN_UMSK                            (~(((1U<<SF_CTRL_SF_IF2_0_CMD_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_EN_POS))
#define SF_CTRL_SF_IF2_0_SPI_MODE                               SF_CTRL_SF_IF2_0_SPI_MODE
#define SF_CTRL_SF_IF2_0_SPI_MODE_POS                           (28U)
#define SF_CTRL_SF_IF2_0_SPI_MODE_LEN                           (3U)
#define SF_CTRL_SF_IF2_0_SPI_MODE_MSK                           (((1U<<SF_CTRL_SF_IF2_0_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF2_0_SPI_MODE_POS)
#define SF_CTRL_SF_IF2_0_SPI_MODE_UMSK                          (~(((1U<<SF_CTRL_SF_IF2_0_SPI_MODE_LEN)-1)<<SF_CTRL_SF_IF2_0_SPI_MODE_POS))
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN                            SF_CTRL_SF_IF2_0_QPI_MODE_EN
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN_POS                        (31U)
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN_LEN                        (1U)
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN_MSK                        (((1U<<SF_CTRL_SF_IF2_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF2_0_QPI_MODE_EN_UMSK                       (~(((1U<<SF_CTRL_SF_IF2_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_SF_IF2_0_QPI_MODE_EN_POS))

/* 0xCC : sf_if2_sahb_1 */
#define SF_CTRL_SF_IF2_SAHB_1_OFFSET                            (0xCC)
#define SF_CTRL_SF_IF2_0_CMD_BUF_0                              SF_CTRL_SF_IF2_0_CMD_BUF_0
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_POS                          (0U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_LEN                          (32U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_MSK                          (((1U<<SF_CTRL_SF_IF2_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF2_0_CMD_BUF_0_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BUF_0_POS))

/* 0xD0 : sf_if2_sahb_2 */
#define SF_CTRL_SF_IF2_SAHB_2_OFFSET                            (0xD0)
#define SF_CTRL_SF_IF2_0_CMD_BUF_1                              SF_CTRL_SF_IF2_0_CMD_BUF_1
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_POS                          (0U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_LEN                          (32U)
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_MSK                          (((1U<<SF_CTRL_SF_IF2_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF2_0_CMD_BUF_1_UMSK                         (~(((1U<<SF_CTRL_SF_IF2_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_SF_IF2_0_CMD_BUF_1_POS))

/* 0x100 : sf_ctrl_prot_en_rd */
#define SF_CTRL_PROT_EN_RD_OFFSET                               (0x100)
#define SF_CTRL_PROT_EN_RD                                      SF_CTRL_PROT_EN_RD
#define SF_CTRL_PROT_EN_RD_POS                                  (0U)
#define SF_CTRL_PROT_EN_RD_LEN                                  (1U)
#define SF_CTRL_PROT_EN_RD_MSK                                  (((1U<<SF_CTRL_PROT_EN_RD_LEN)-1)<<SF_CTRL_PROT_EN_RD_POS)
#define SF_CTRL_PROT_EN_RD_UMSK                                 (~(((1U<<SF_CTRL_PROT_EN_RD_LEN)-1)<<SF_CTRL_PROT_EN_RD_POS))
#define SF_CTRL_ID0_EN_RD                                       SF_CTRL_ID0_EN_RD
#define SF_CTRL_ID0_EN_RD_POS                                   (1U)
#define SF_CTRL_ID0_EN_RD_LEN                                   (1U)
#define SF_CTRL_ID0_EN_RD_MSK                                   (((1U<<SF_CTRL_ID0_EN_RD_LEN)-1)<<SF_CTRL_ID0_EN_RD_POS)
#define SF_CTRL_ID0_EN_RD_UMSK                                  (~(((1U<<SF_CTRL_ID0_EN_RD_LEN)-1)<<SF_CTRL_ID0_EN_RD_POS))
#define SF_CTRL_ID1_EN_RD                                       SF_CTRL_ID1_EN_RD
#define SF_CTRL_ID1_EN_RD_POS                                   (2U)
#define SF_CTRL_ID1_EN_RD_LEN                                   (1U)
#define SF_CTRL_ID1_EN_RD_MSK                                   (((1U<<SF_CTRL_ID1_EN_RD_LEN)-1)<<SF_CTRL_ID1_EN_RD_POS)
#define SF_CTRL_ID1_EN_RD_UMSK                                  (~(((1U<<SF_CTRL_ID1_EN_RD_LEN)-1)<<SF_CTRL_ID1_EN_RD_POS))
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK                           SF_CTRL_SF_IF2_0_TRIG_WR_LOCK
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_POS                       (29U)
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_LEN                       (1U)
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_MSK                       (((1U<<SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_LEN)-1)<<SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_POS)
#define SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_UMSK                      (~(((1U<<SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_LEN)-1)<<SF_CTRL_SF_IF2_0_TRIG_WR_LOCK_POS))
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK                            SF_CTRL_SF_IF_0_TRIG_WR_LOCK
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK_POS                        (30U)
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK_LEN                        (1U)
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK_MSK                        (((1U<<SF_CTRL_SF_IF_0_TRIG_WR_LOCK_LEN)-1)<<SF_CTRL_SF_IF_0_TRIG_WR_LOCK_POS)
#define SF_CTRL_SF_IF_0_TRIG_WR_LOCK_UMSK                       (~(((1U<<SF_CTRL_SF_IF_0_TRIG_WR_LOCK_LEN)-1)<<SF_CTRL_SF_IF_0_TRIG_WR_LOCK_POS))
#define SF_CTRL_SF_DBG_DIS                                      SF_CTRL_SF_DBG_DIS
#define SF_CTRL_SF_DBG_DIS_POS                                  (31U)
#define SF_CTRL_SF_DBG_DIS_LEN                                  (1U)
#define SF_CTRL_SF_DBG_DIS_MSK                                  (((1U<<SF_CTRL_SF_DBG_DIS_LEN)-1)<<SF_CTRL_SF_DBG_DIS_POS)
#define SF_CTRL_SF_DBG_DIS_UMSK                                 (~(((1U<<SF_CTRL_SF_DBG_DIS_LEN)-1)<<SF_CTRL_SF_DBG_DIS_POS))

/* 0x104 : sf_ctrl_prot_en */
#define SF_CTRL_PROT_EN_OFFSET                                  (0x104)
#define SF_CTRL_PROT_EN                                         SF_CTRL_PROT_EN
#define SF_CTRL_PROT_EN_POS                                     (0U)
#define SF_CTRL_PROT_EN_LEN                                     (1U)
#define SF_CTRL_PROT_EN_MSK                                     (((1U<<SF_CTRL_PROT_EN_LEN)-1)<<SF_CTRL_PROT_EN_POS)
#define SF_CTRL_PROT_EN_UMSK                                    (~(((1U<<SF_CTRL_PROT_EN_LEN)-1)<<SF_CTRL_PROT_EN_POS))
#define SF_CTRL_ID0_EN                                          SF_CTRL_ID0_EN
#define SF_CTRL_ID0_EN_POS                                      (1U)
#define SF_CTRL_ID0_EN_LEN                                      (1U)
#define SF_CTRL_ID0_EN_MSK                                      (((1U<<SF_CTRL_ID0_EN_LEN)-1)<<SF_CTRL_ID0_EN_POS)
#define SF_CTRL_ID0_EN_UMSK                                     (~(((1U<<SF_CTRL_ID0_EN_LEN)-1)<<SF_CTRL_ID0_EN_POS))
#define SF_CTRL_ID1_EN                                          SF_CTRL_ID1_EN
#define SF_CTRL_ID1_EN_POS                                      (2U)
#define SF_CTRL_ID1_EN_LEN                                      (1U)
#define SF_CTRL_ID1_EN_MSK                                      (((1U<<SF_CTRL_ID1_EN_LEN)-1)<<SF_CTRL_ID1_EN_POS)
#define SF_CTRL_ID1_EN_UMSK                                     (~(((1U<<SF_CTRL_ID1_EN_LEN)-1)<<SF_CTRL_ID1_EN_POS))

/* 0x200 : sf_aes_key_r0_0 */
#define SF_CTRL_SF_AES_KEY_R0_0_OFFSET                          (0x200)
#define SF_CTRL_SF_AES_KEY_R0_0                                 SF_CTRL_SF_AES_KEY_R0_0
#define SF_CTRL_SF_AES_KEY_R0_0_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_0_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_0_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_0_POS)
#define SF_CTRL_SF_AES_KEY_R0_0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_0_POS))

/* 0x204 : sf_aes_key_r0_1 */
#define SF_CTRL_SF_AES_KEY_R0_1_OFFSET                          (0x204)
#define SF_CTRL_SF_AES_KEY_R0_1                                 SF_CTRL_SF_AES_KEY_R0_1
#define SF_CTRL_SF_AES_KEY_R0_1_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_1_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_1_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_1_POS)
#define SF_CTRL_SF_AES_KEY_R0_1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_1_POS))

/* 0x208 : sf_aes_key_r0_2 */
#define SF_CTRL_SF_AES_KEY_R0_2_OFFSET                          (0x208)
#define SF_CTRL_SF_AES_KEY_R0_2                                 SF_CTRL_SF_AES_KEY_R0_2
#define SF_CTRL_SF_AES_KEY_R0_2_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_2_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_2_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_2_POS)
#define SF_CTRL_SF_AES_KEY_R0_2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_2_POS))

/* 0x20C : sf_aes_key_r0_3 */
#define SF_CTRL_SF_AES_KEY_R0_3_OFFSET                          (0x20C)
#define SF_CTRL_SF_AES_KEY_R0_3                                 SF_CTRL_SF_AES_KEY_R0_3
#define SF_CTRL_SF_AES_KEY_R0_3_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_3_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_3_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_3_POS)
#define SF_CTRL_SF_AES_KEY_R0_3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_3_POS))

/* 0x210 : sf_aes_key_r0_4 */
#define SF_CTRL_SF_AES_KEY_R0_4_OFFSET                          (0x210)
#define SF_CTRL_SF_AES_KEY_R0_4                                 SF_CTRL_SF_AES_KEY_R0_4
#define SF_CTRL_SF_AES_KEY_R0_4_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_4_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_4_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_4_POS)
#define SF_CTRL_SF_AES_KEY_R0_4_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_4_POS))

/* 0x214 : sf_aes_key_r0_5 */
#define SF_CTRL_SF_AES_KEY_R0_5_OFFSET                          (0x214)
#define SF_CTRL_SF_AES_KEY_R0_5                                 SF_CTRL_SF_AES_KEY_R0_5
#define SF_CTRL_SF_AES_KEY_R0_5_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_5_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_5_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_5_POS)
#define SF_CTRL_SF_AES_KEY_R0_5_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_5_POS))

/* 0x218 : sf_aes_key_r0_6 */
#define SF_CTRL_SF_AES_KEY_R0_6_OFFSET                          (0x218)
#define SF_CTRL_SF_AES_KEY_R0_6                                 SF_CTRL_SF_AES_KEY_R0_6
#define SF_CTRL_SF_AES_KEY_R0_6_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_6_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_6_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_6_POS)
#define SF_CTRL_SF_AES_KEY_R0_6_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_6_POS))

/* 0x21C : sf_aes_key_r0_7 */
#define SF_CTRL_SF_AES_KEY_R0_7_OFFSET                          (0x21C)
#define SF_CTRL_SF_AES_KEY_R0_7                                 SF_CTRL_SF_AES_KEY_R0_7
#define SF_CTRL_SF_AES_KEY_R0_7_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R0_7_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R0_7_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R0_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_7_POS)
#define SF_CTRL_SF_AES_KEY_R0_7_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R0_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R0_7_POS))

/* 0x220 : sf_aes_iv_r0_w0 */
#define SF_CTRL_SF_AES_IV_R0_W0_OFFSET                          (0x220)
#define SF_CTRL_SF_AES_IV_R0_W0                                 SF_CTRL_SF_AES_IV_R0_W0
#define SF_CTRL_SF_AES_IV_R0_W0_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R0_W0_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R0_W0_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R0_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W0_POS)
#define SF_CTRL_SF_AES_IV_R0_W0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R0_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W0_POS))

/* 0x224 : sf_aes_iv_r0_w1 */
#define SF_CTRL_SF_AES_IV_R0_W1_OFFSET                          (0x224)
#define SF_CTRL_SF_AES_IV_R0_W1                                 SF_CTRL_SF_AES_IV_R0_W1
#define SF_CTRL_SF_AES_IV_R0_W1_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R0_W1_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R0_W1_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R0_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W1_POS)
#define SF_CTRL_SF_AES_IV_R0_W1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R0_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W1_POS))

/* 0x228 : sf_aes_iv_r0_w2 */
#define SF_CTRL_SF_AES_IV_R0_W2_OFFSET                          (0x228)
#define SF_CTRL_SF_AES_IV_R0_W2                                 SF_CTRL_SF_AES_IV_R0_W2
#define SF_CTRL_SF_AES_IV_R0_W2_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R0_W2_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R0_W2_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R0_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W2_POS)
#define SF_CTRL_SF_AES_IV_R0_W2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R0_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W2_POS))

/* 0x22C : sf_aes_iv_r0_w3 */
#define SF_CTRL_SF_AES_IV_R0_W3_OFFSET                          (0x22C)
#define SF_CTRL_SF_AES_IV_R0_W3                                 SF_CTRL_SF_AES_IV_R0_W3
#define SF_CTRL_SF_AES_IV_R0_W3_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R0_W3_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R0_W3_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R0_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W3_POS)
#define SF_CTRL_SF_AES_IV_R0_W3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R0_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R0_W3_POS))

/* 0x230 : sf_aes_r0_start */
#define SF_CTRL_SF_AES_R0_START_OFFSET                          (0x230)
#define SF_CTRL_SF_AES_REGION_R0_START                          SF_CTRL_SF_AES_REGION_R0_START
#define SF_CTRL_SF_AES_REGION_R0_START_POS                      (0U)
#define SF_CTRL_SF_AES_REGION_R0_START_LEN                      (19U)
#define SF_CTRL_SF_AES_REGION_R0_START_MSK                      (((1U<<SF_CTRL_SF_AES_REGION_R0_START_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_START_POS)
#define SF_CTRL_SF_AES_REGION_R0_START_UMSK                     (~(((1U<<SF_CTRL_SF_AES_REGION_R0_START_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_START_POS))
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN                      SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_POS                  (29U)
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_LEN                  (1U)
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_MSK                  (((1U<<SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_POS)
#define SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_UMSK                 (~(((1U<<SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_HW_KEY_EN_POS))
#define SF_CTRL_SF_AES_REGION_R0_EN                             SF_CTRL_SF_AES_REGION_R0_EN
#define SF_CTRL_SF_AES_REGION_R0_EN_POS                         (30U)
#define SF_CTRL_SF_AES_REGION_R0_EN_LEN                         (1U)
#define SF_CTRL_SF_AES_REGION_R0_EN_MSK                         (((1U<<SF_CTRL_SF_AES_REGION_R0_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_EN_POS)
#define SF_CTRL_SF_AES_REGION_R0_EN_UMSK                        (~(((1U<<SF_CTRL_SF_AES_REGION_R0_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_EN_POS))
#define SF_CTRL_SF_AES_REGION_R0_LOCK                           SF_CTRL_SF_AES_REGION_R0_LOCK
#define SF_CTRL_SF_AES_REGION_R0_LOCK_POS                       (31U)
#define SF_CTRL_SF_AES_REGION_R0_LOCK_LEN                       (1U)
#define SF_CTRL_SF_AES_REGION_R0_LOCK_MSK                       (((1U<<SF_CTRL_SF_AES_REGION_R0_LOCK_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_LOCK_POS)
#define SF_CTRL_SF_AES_REGION_R0_LOCK_UMSK                      (~(((1U<<SF_CTRL_SF_AES_REGION_R0_LOCK_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_LOCK_POS))

/* 0x234 : sf_aes_r0_end */
#define SF_CTRL_SF_AES_R0_END_OFFSET                            (0x234)
#define SF_CTRL_SF_AES_REGION_R0_END                            SF_CTRL_SF_AES_REGION_R0_END
#define SF_CTRL_SF_AES_REGION_R0_END_POS                        (0U)
#define SF_CTRL_SF_AES_REGION_R0_END_LEN                        (19U)
#define SF_CTRL_SF_AES_REGION_R0_END_MSK                        (((1U<<SF_CTRL_SF_AES_REGION_R0_END_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_END_POS)
#define SF_CTRL_SF_AES_REGION_R0_END_UMSK                       (~(((1U<<SF_CTRL_SF_AES_REGION_R0_END_LEN)-1)<<SF_CTRL_SF_AES_REGION_R0_END_POS))

/* 0x280 : sf_aes_key_r1_0 */
#define SF_CTRL_SF_AES_KEY_R1_0_OFFSET                          (0x280)
#define SF_CTRL_SF_AES_KEY_R1_0                                 SF_CTRL_SF_AES_KEY_R1_0
#define SF_CTRL_SF_AES_KEY_R1_0_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_0_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_0_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_0_POS)
#define SF_CTRL_SF_AES_KEY_R1_0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_0_POS))

/* 0x284 : sf_aes_key_r1_1 */
#define SF_CTRL_SF_AES_KEY_R1_1_OFFSET                          (0x284)
#define SF_CTRL_SF_AES_KEY_R1_1                                 SF_CTRL_SF_AES_KEY_R1_1
#define SF_CTRL_SF_AES_KEY_R1_1_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_1_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_1_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_1_POS)
#define SF_CTRL_SF_AES_KEY_R1_1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_1_POS))

/* 0x288 : sf_aes_key_r1_2 */
#define SF_CTRL_SF_AES_KEY_R1_2_OFFSET                          (0x288)
#define SF_CTRL_SF_AES_KEY_R1_2                                 SF_CTRL_SF_AES_KEY_R1_2
#define SF_CTRL_SF_AES_KEY_R1_2_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_2_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_2_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_2_POS)
#define SF_CTRL_SF_AES_KEY_R1_2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_2_POS))

/* 0x28C : sf_aes_key_r1_3 */
#define SF_CTRL_SF_AES_KEY_R1_3_OFFSET                          (0x28C)
#define SF_CTRL_SF_AES_KEY_R1_3                                 SF_CTRL_SF_AES_KEY_R1_3
#define SF_CTRL_SF_AES_KEY_R1_3_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_3_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_3_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_3_POS)
#define SF_CTRL_SF_AES_KEY_R1_3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_3_POS))

/* 0x290 : sf_aes_key_r1_4 */
#define SF_CTRL_SF_AES_KEY_R1_4_OFFSET                          (0x290)
#define SF_CTRL_SF_AES_KEY_R1_4                                 SF_CTRL_SF_AES_KEY_R1_4
#define SF_CTRL_SF_AES_KEY_R1_4_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_4_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_4_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_4_POS)
#define SF_CTRL_SF_AES_KEY_R1_4_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_4_POS))

/* 0x294 : sf_aes_key_r1_5 */
#define SF_CTRL_SF_AES_KEY_R1_5_OFFSET                          (0x294)
#define SF_CTRL_SF_AES_KEY_R1_5                                 SF_CTRL_SF_AES_KEY_R1_5
#define SF_CTRL_SF_AES_KEY_R1_5_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_5_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_5_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_5_POS)
#define SF_CTRL_SF_AES_KEY_R1_5_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_5_POS))

/* 0x298 : sf_aes_key_r1_6 */
#define SF_CTRL_SF_AES_KEY_R1_6_OFFSET                          (0x298)
#define SF_CTRL_SF_AES_KEY_R1_6                                 SF_CTRL_SF_AES_KEY_R1_6
#define SF_CTRL_SF_AES_KEY_R1_6_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_6_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_6_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_6_POS)
#define SF_CTRL_SF_AES_KEY_R1_6_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_6_POS))

/* 0x29C : sf_aes_key_r1_7 */
#define SF_CTRL_SF_AES_KEY_R1_7_OFFSET                          (0x29C)
#define SF_CTRL_SF_AES_KEY_R1_7                                 SF_CTRL_SF_AES_KEY_R1_7
#define SF_CTRL_SF_AES_KEY_R1_7_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R1_7_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R1_7_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R1_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_7_POS)
#define SF_CTRL_SF_AES_KEY_R1_7_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R1_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R1_7_POS))

/* 0x2A0 : sf_aes_iv_r1_w0 */
#define SF_CTRL_SF_AES_IV_R1_W0_OFFSET                          (0x2A0)
#define SF_CTRL_SF_AES_IV_R1_W0                                 SF_CTRL_SF_AES_IV_R1_W0
#define SF_CTRL_SF_AES_IV_R1_W0_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R1_W0_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R1_W0_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R1_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W0_POS)
#define SF_CTRL_SF_AES_IV_R1_W0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R1_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W0_POS))

/* 0x2A4 : sf_aes_iv_r1_w1 */
#define SF_CTRL_SF_AES_IV_R1_W1_OFFSET                          (0x2A4)
#define SF_CTRL_SF_AES_IV_R1_W1                                 SF_CTRL_SF_AES_IV_R1_W1
#define SF_CTRL_SF_AES_IV_R1_W1_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R1_W1_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R1_W1_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R1_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W1_POS)
#define SF_CTRL_SF_AES_IV_R1_W1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R1_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W1_POS))

/* 0x2A8 : sf_aes_iv_r1_w2 */
#define SF_CTRL_SF_AES_IV_R1_W2_OFFSET                          (0x2A8)
#define SF_CTRL_SF_AES_IV_R1_W2                                 SF_CTRL_SF_AES_IV_R1_W2
#define SF_CTRL_SF_AES_IV_R1_W2_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R1_W2_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R1_W2_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R1_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W2_POS)
#define SF_CTRL_SF_AES_IV_R1_W2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R1_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W2_POS))

/* 0x2AC : sf_aes_iv_r1_w3 */
#define SF_CTRL_SF_AES_IV_R1_W3_OFFSET                          (0x2AC)
#define SF_CTRL_SF_AES_IV_R1_W3                                 SF_CTRL_SF_AES_IV_R1_W3
#define SF_CTRL_SF_AES_IV_R1_W3_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R1_W3_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R1_W3_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R1_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W3_POS)
#define SF_CTRL_SF_AES_IV_R1_W3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R1_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R1_W3_POS))

/* 0x2B0 : sf_aes_r1_start */
#define SF_CTRL_SF_AES_R1_START_OFFSET                          (0x2B0)
#define SF_CTRL_SF_AES_R1_START                                 SF_CTRL_SF_AES_R1_START
#define SF_CTRL_SF_AES_R1_START_POS                             (0U)
#define SF_CTRL_SF_AES_R1_START_LEN                             (19U)
#define SF_CTRL_SF_AES_R1_START_MSK                             (((1U<<SF_CTRL_SF_AES_R1_START_LEN)-1)<<SF_CTRL_SF_AES_R1_START_POS)
#define SF_CTRL_SF_AES_R1_START_UMSK                            (~(((1U<<SF_CTRL_SF_AES_R1_START_LEN)-1)<<SF_CTRL_SF_AES_R1_START_POS))
#define SF_CTRL_SF_AES_R1_HW_KEY_EN                             SF_CTRL_SF_AES_R1_HW_KEY_EN
#define SF_CTRL_SF_AES_R1_HW_KEY_EN_POS                         (29U)
#define SF_CTRL_SF_AES_R1_HW_KEY_EN_LEN                         (1U)
#define SF_CTRL_SF_AES_R1_HW_KEY_EN_MSK                         (((1U<<SF_CTRL_SF_AES_R1_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_R1_HW_KEY_EN_POS)
#define SF_CTRL_SF_AES_R1_HW_KEY_EN_UMSK                        (~(((1U<<SF_CTRL_SF_AES_R1_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_R1_HW_KEY_EN_POS))
#define SF_CTRL_SF_AES_R1_EN                                    SF_CTRL_SF_AES_R1_EN
#define SF_CTRL_SF_AES_R1_EN_POS                                (30U)
#define SF_CTRL_SF_AES_R1_EN_LEN                                (1U)
#define SF_CTRL_SF_AES_R1_EN_MSK                                (((1U<<SF_CTRL_SF_AES_R1_EN_LEN)-1)<<SF_CTRL_SF_AES_R1_EN_POS)
#define SF_CTRL_SF_AES_R1_EN_UMSK                               (~(((1U<<SF_CTRL_SF_AES_R1_EN_LEN)-1)<<SF_CTRL_SF_AES_R1_EN_POS))
#define SF_CTRL_SF_AES_R1_LOCK                                  SF_CTRL_SF_AES_R1_LOCK
#define SF_CTRL_SF_AES_R1_LOCK_POS                              (31U)
#define SF_CTRL_SF_AES_R1_LOCK_LEN                              (1U)
#define SF_CTRL_SF_AES_R1_LOCK_MSK                              (((1U<<SF_CTRL_SF_AES_R1_LOCK_LEN)-1)<<SF_CTRL_SF_AES_R1_LOCK_POS)
#define SF_CTRL_SF_AES_R1_LOCK_UMSK                             (~(((1U<<SF_CTRL_SF_AES_R1_LOCK_LEN)-1)<<SF_CTRL_SF_AES_R1_LOCK_POS))

/* 0x2B4 : sf_aes_r1_end */
#define SF_CTRL_SF_AES_R1_END_OFFSET                            (0x2B4)
#define SF_CTRL_SF_AES_R1_END                                   SF_CTRL_SF_AES_R1_END
#define SF_CTRL_SF_AES_R1_END_POS                               (0U)
#define SF_CTRL_SF_AES_R1_END_LEN                               (19U)
#define SF_CTRL_SF_AES_R1_END_MSK                               (((1U<<SF_CTRL_SF_AES_R1_END_LEN)-1)<<SF_CTRL_SF_AES_R1_END_POS)
#define SF_CTRL_SF_AES_R1_END_UMSK                              (~(((1U<<SF_CTRL_SF_AES_R1_END_LEN)-1)<<SF_CTRL_SF_AES_R1_END_POS))

/* 0x300 : sf_aes_key_r2_0 */
#define SF_CTRL_SF_AES_KEY_R2_0_OFFSET                          (0x300)
#define SF_CTRL_SF_AES_KEY_R2_0                                 SF_CTRL_SF_AES_KEY_R2_0
#define SF_CTRL_SF_AES_KEY_R2_0_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_0_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_0_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_0_POS)
#define SF_CTRL_SF_AES_KEY_R2_0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_0_POS))

/* 0x304 : sf_aes_key_r2_1 */
#define SF_CTRL_SF_AES_KEY_R2_1_OFFSET                          (0x304)
#define SF_CTRL_SF_AES_KEY_R2_1                                 SF_CTRL_SF_AES_KEY_R2_1
#define SF_CTRL_SF_AES_KEY_R2_1_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_1_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_1_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_1_POS)
#define SF_CTRL_SF_AES_KEY_R2_1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_1_POS))

/* 0x308 : sf_aes_key_r2_2 */
#define SF_CTRL_SF_AES_KEY_R2_2_OFFSET                          (0x308)
#define SF_CTRL_SF_AES_KEY_R2_2                                 SF_CTRL_SF_AES_KEY_R2_2
#define SF_CTRL_SF_AES_KEY_R2_2_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_2_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_2_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_2_POS)
#define SF_CTRL_SF_AES_KEY_R2_2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_2_POS))

/* 0x30C : sf_aes_key_r2_3 */
#define SF_CTRL_SF_AES_KEY_R2_3_OFFSET                          (0x30C)
#define SF_CTRL_SF_AES_KEY_R2_3                                 SF_CTRL_SF_AES_KEY_R2_3
#define SF_CTRL_SF_AES_KEY_R2_3_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_3_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_3_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_3_POS)
#define SF_CTRL_SF_AES_KEY_R2_3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_3_POS))

/* 0x310 : sf_aes_key_r2_4 */
#define SF_CTRL_SF_AES_KEY_R2_4_OFFSET                          (0x310)
#define SF_CTRL_SF_AES_KEY_R2_4                                 SF_CTRL_SF_AES_KEY_R2_4
#define SF_CTRL_SF_AES_KEY_R2_4_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_4_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_4_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_4_POS)
#define SF_CTRL_SF_AES_KEY_R2_4_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_4_POS))

/* 0x314 : sf_aes_key_r2_5 */
#define SF_CTRL_SF_AES_KEY_R2_5_OFFSET                          (0x314)
#define SF_CTRL_SF_AES_KEY_R2_5                                 SF_CTRL_SF_AES_KEY_R2_5
#define SF_CTRL_SF_AES_KEY_R2_5_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_5_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_5_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_5_POS)
#define SF_CTRL_SF_AES_KEY_R2_5_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_5_POS))

/* 0x318 : sf_aes_key_r2_6 */
#define SF_CTRL_SF_AES_KEY_R2_6_OFFSET                          (0x318)
#define SF_CTRL_SF_AES_KEY_R2_6                                 SF_CTRL_SF_AES_KEY_R2_6
#define SF_CTRL_SF_AES_KEY_R2_6_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_6_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_6_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_6_POS)
#define SF_CTRL_SF_AES_KEY_R2_6_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_6_POS))

/* 0x31C : sf_aes_key_r2_7 */
#define SF_CTRL_SF_AES_KEY_R2_7_OFFSET                          (0x31C)
#define SF_CTRL_SF_AES_KEY_R2_7                                 SF_CTRL_SF_AES_KEY_R2_7
#define SF_CTRL_SF_AES_KEY_R2_7_POS                             (0U)
#define SF_CTRL_SF_AES_KEY_R2_7_LEN                             (32U)
#define SF_CTRL_SF_AES_KEY_R2_7_MSK                             (((1U<<SF_CTRL_SF_AES_KEY_R2_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_7_POS)
#define SF_CTRL_SF_AES_KEY_R2_7_UMSK                            (~(((1U<<SF_CTRL_SF_AES_KEY_R2_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_R2_7_POS))

/* 0x320 : sf_aes_iv_r2_w0 */
#define SF_CTRL_SF_AES_IV_R2_W0_OFFSET                          (0x320)
#define SF_CTRL_SF_AES_IV_R2_W0                                 SF_CTRL_SF_AES_IV_R2_W0
#define SF_CTRL_SF_AES_IV_R2_W0_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R2_W0_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R2_W0_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R2_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W0_POS)
#define SF_CTRL_SF_AES_IV_R2_W0_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R2_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W0_POS))

/* 0x324 : sf_aes_iv_r2_w1 */
#define SF_CTRL_SF_AES_IV_R2_W1_OFFSET                          (0x324)
#define SF_CTRL_SF_AES_IV_R2_W1                                 SF_CTRL_SF_AES_IV_R2_W1
#define SF_CTRL_SF_AES_IV_R2_W1_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R2_W1_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R2_W1_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R2_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W1_POS)
#define SF_CTRL_SF_AES_IV_R2_W1_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R2_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W1_POS))

/* 0x328 : sf_aes_iv_r2_w2 */
#define SF_CTRL_SF_AES_IV_R2_W2_OFFSET                          (0x328)
#define SF_CTRL_SF_AES_IV_R2_W2                                 SF_CTRL_SF_AES_IV_R2_W2
#define SF_CTRL_SF_AES_IV_R2_W2_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R2_W2_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R2_W2_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R2_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W2_POS)
#define SF_CTRL_SF_AES_IV_R2_W2_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R2_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W2_POS))

/* 0x32C : sf_aes_iv_r2_w3 */
#define SF_CTRL_SF_AES_IV_R2_W3_OFFSET                          (0x32C)
#define SF_CTRL_SF_AES_IV_R2_W3                                 SF_CTRL_SF_AES_IV_R2_W3
#define SF_CTRL_SF_AES_IV_R2_W3_POS                             (0U)
#define SF_CTRL_SF_AES_IV_R2_W3_LEN                             (32U)
#define SF_CTRL_SF_AES_IV_R2_W3_MSK                             (((1U<<SF_CTRL_SF_AES_IV_R2_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W3_POS)
#define SF_CTRL_SF_AES_IV_R2_W3_UMSK                            (~(((1U<<SF_CTRL_SF_AES_IV_R2_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_R2_W3_POS))

/* 0x330 : sf_aes_r2_start */
#define SF_CTRL_SF_AES_R2_START_OFFSET                          (0x330)
#define SF_CTRL_SF_AES_R2_START                                 SF_CTRL_SF_AES_R2_START
#define SF_CTRL_SF_AES_R2_START_POS                             (0U)
#define SF_CTRL_SF_AES_R2_START_LEN                             (19U)
#define SF_CTRL_SF_AES_R2_START_MSK                             (((1U<<SF_CTRL_SF_AES_R2_START_LEN)-1)<<SF_CTRL_SF_AES_R2_START_POS)
#define SF_CTRL_SF_AES_R2_START_UMSK                            (~(((1U<<SF_CTRL_SF_AES_R2_START_LEN)-1)<<SF_CTRL_SF_AES_R2_START_POS))
#define SF_CTRL_SF_AES_R2_HW_KEY_EN                             SF_CTRL_SF_AES_R2_HW_KEY_EN
#define SF_CTRL_SF_AES_R2_HW_KEY_EN_POS                         (29U)
#define SF_CTRL_SF_AES_R2_HW_KEY_EN_LEN                         (1U)
#define SF_CTRL_SF_AES_R2_HW_KEY_EN_MSK                         (((1U<<SF_CTRL_SF_AES_R2_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_R2_HW_KEY_EN_POS)
#define SF_CTRL_SF_AES_R2_HW_KEY_EN_UMSK                        (~(((1U<<SF_CTRL_SF_AES_R2_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_R2_HW_KEY_EN_POS))
#define SF_CTRL_SF_AES_R2_EN                                    SF_CTRL_SF_AES_R2_EN
#define SF_CTRL_SF_AES_R2_EN_POS                                (30U)
#define SF_CTRL_SF_AES_R2_EN_LEN                                (1U)
#define SF_CTRL_SF_AES_R2_EN_MSK                                (((1U<<SF_CTRL_SF_AES_R2_EN_LEN)-1)<<SF_CTRL_SF_AES_R2_EN_POS)
#define SF_CTRL_SF_AES_R2_EN_UMSK                               (~(((1U<<SF_CTRL_SF_AES_R2_EN_LEN)-1)<<SF_CTRL_SF_AES_R2_EN_POS))
#define SF_CTRL_SF_AES_R2_LOCK                                  SF_CTRL_SF_AES_R2_LOCK
#define SF_CTRL_SF_AES_R2_LOCK_POS                              (31U)
#define SF_CTRL_SF_AES_R2_LOCK_LEN                              (1U)
#define SF_CTRL_SF_AES_R2_LOCK_MSK                              (((1U<<SF_CTRL_SF_AES_R2_LOCK_LEN)-1)<<SF_CTRL_SF_AES_R2_LOCK_POS)
#define SF_CTRL_SF_AES_R2_LOCK_UMSK                             (~(((1U<<SF_CTRL_SF_AES_R2_LOCK_LEN)-1)<<SF_CTRL_SF_AES_R2_LOCK_POS))

/* 0x334 : sf_aes_r2_end */
#define SF_CTRL_SF_AES_R2_END_OFFSET                            (0x334)
#define SF_CTRL_SF_AES_R2_END                                   SF_CTRL_SF_AES_R2_END
#define SF_CTRL_SF_AES_R2_END_POS                               (0U)
#define SF_CTRL_SF_AES_R2_END_LEN                               (19U)
#define SF_CTRL_SF_AES_R2_END_MSK                               (((1U<<SF_CTRL_SF_AES_R2_END_LEN)-1)<<SF_CTRL_SF_AES_R2_END_POS)
#define SF_CTRL_SF_AES_R2_END_UMSK                              (~(((1U<<SF_CTRL_SF_AES_R2_END_LEN)-1)<<SF_CTRL_SF_AES_R2_END_POS))


struct  sf_ctrl_reg {
    /* 0x0 : sf_ctrl_0 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t sf_clk_sf_rx_inv_sel           :  1; /* [    2],        r/w,        0x1 */
            uint32_t sf_clk_out_gate_en             :  1; /* [    3],        r/w,        0x1 */
            uint32_t sf_clk_out_inv_sel             :  1; /* [    4],        r/w,        0x1 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t sf_if_read_dly_n               :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t sf_if_read_dly_en              :  1; /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t sf_if_int                      :  1; /* [   16],          r,        0x0 */
            uint32_t sf_if_int_clr                  :  1; /* [   17],        r/w,        0x1 */
            uint32_t sf_if_int_set                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t sf_if_32b_adr_en               :  1; /* [   19],        r/w,        0x0 */
            uint32_t sf_aes_dout_endian             :  1; /* [   20],        r/w,        0x1 */
            uint32_t sf_aes_din_endian              :  1; /* [   21],        r/w,        0x1 */
            uint32_t sf_aes_key_endian              :  1; /* [   22],        r/w,        0x1 */
            uint32_t sf_aes_iv_endian               :  1; /* [   23],        r/w,        0x1 */
            uint32_t sf_id                          :  8; /* [31:24],        r/w,       0x1a */
        }BF;
        uint32_t WORD;
    } sf_ctrl_0;

    /* 0x4 : sf_ctrl_1 */
    union {
        struct {
            uint32_t sf_if_sr_pat_mask              :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t sf_if_sr_pat                   :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t sf_if_sr_int                   :  1; /* [   16],          r,        0x0 */
            uint32_t sf_if_sr_int_en                :  1; /* [   17],        r/w,        0x0 */
            uint32_t sf_if_sr_int_set               :  1; /* [   18],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t sf_if_0_ack_lat                :  3; /* [22:20],        r/w,        0x6 */
            uint32_t sf_ahb2sif_diswrap             :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if_reg_hold                 :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if_reg_wp                   :  1; /* [   25],        r/w,        0x1 */
            uint32_t sf_ahb2sif_stopped             :  1; /* [   26],          r,        0x0 */
            uint32_t sf_ahb2sif_stop                :  1; /* [   27],        r/w,        0x0 */
            uint32_t sf_if_fn_sel                   :  1; /* [   28],        r/w,        0x1 */
            uint32_t sf_if_en                       :  1; /* [   29],        r/w,        0x1 */
            uint32_t sf_ahb2sif_en                  :  1; /* [   30],        r/w,        0x1 */
            uint32_t sf_ahb2sram_en                 :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } sf_ctrl_1;

    /* 0x8 : sf_if_sahb_0 */
    union {
        struct {
            uint32_t sf_if_busy                     :  1; /* [    0],          r,        0x0 */
            uint32_t sf_if_0_trig                   :  1; /* [    1],        r/w,        0x0 */
            uint32_t sf_if_0_dat_byte               : 10; /* [11: 2],        r/w,       0xff */
            uint32_t sf_if_0_dmy_byte               :  5; /* [16:12],        r/w,        0x0 */
            uint32_t sf_if_0_adr_byte               :  3; /* [19:17],        r/w,        0x2 */
            uint32_t sf_if_0_cmd_byte               :  3; /* [22:20],        r/w,        0x0 */
            uint32_t sf_if_0_dat_rw                 :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if_0_dat_en                 :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if_0_dmy_en                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_if_0_adr_en                 :  1; /* [   26],        r/w,        0x1 */
            uint32_t sf_if_0_cmd_en                 :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if_0_spi_mode               :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if_0_qpi_mode_en            :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_sahb_0;

    /* 0xC : sf_if_sahb_1 */
    union {
        struct {
            uint32_t sf_if_0_cmd_buf_0              : 32; /* [31: 0],        r/w,  0x3000000 */
        }BF;
        uint32_t WORD;
    } sf_if_sahb_1;

    /* 0x10 : sf_if_sahb_2 */
    union {
        struct {
            uint32_t sf_if_0_cmd_buf_1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_sahb_2;

    /* 0x14 : sf_if_iahb_0 */
    union {
        struct {
            uint32_t reserved_0_11                  : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t sf_if_1_dmy_byte               :  5; /* [16:12],        r/w,        0x0 */
            uint32_t sf_if_1_adr_byte               :  3; /* [19:17],        r/w,        0x2 */
            uint32_t sf_if_1_cmd_byte               :  3; /* [22:20],        r/w,        0x0 */
            uint32_t sf_if_1_dat_rw                 :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if_1_dat_en                 :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if_1_dmy_en                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_if_1_adr_en                 :  1; /* [   26],        r/w,        0x1 */
            uint32_t sf_if_1_cmd_en                 :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if_1_spi_mode               :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if_1_qpi_mode_en            :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_0;

    /* 0x18 : sf_if_iahb_1 */
    union {
        struct {
            uint32_t sf_if_1_cmd_buf_0              : 32; /* [31: 0],        r/w,  0x3000000 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_1;

    /* 0x1C : sf_if_iahb_2 */
    union {
        struct {
            uint32_t sf_if_1_cmd_buf_1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_2;

    /* 0x20 : sf_if_status_0 */
    union {
        struct {
            uint32_t sf_if_status_0                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_status_0;

    /* 0x24 : sf_if_status_1 */
    union {
        struct {
            uint32_t sf_if_status_1                 : 32; /* [31: 0],          r, 0x20000000 */
        }BF;
        uint32_t WORD;
    } sf_if_status_1;

    /* 0x28 : sf_aes */
    union {
        struct {
            uint32_t sf_aes_en                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t sf_aes_mode                    :  2; /* [ 2: 1],        r/w,        0x0 */
            uint32_t sf_aes_blk_mode                :  1; /* [    3],        r/w,        0x0 */
            uint32_t sf_aes_xts_key_opt             :  1; /* [    4],        r/w,        0x0 */
            uint32_t sf_aes_status                  : 27; /* [31: 5],          r,        0x2 */
        }BF;
        uint32_t WORD;
    } sf_aes;

    /* 0x2C : sf_ahb2sif_status */
    union {
        struct {
            uint32_t sf_ahb2sif_status              : 32; /* [31: 0],          r,  0x1010003 */
        }BF;
        uint32_t WORD;
    } sf_ahb2sif_status;

    /* 0x30 : sf_if_io_dly_0 */
    union {
        struct {
            uint32_t sf_cs_dly_sel                  :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t sf_cs2_dly_sel                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t sf_clk_out_dly_sel             :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_25                 : 16; /* [25:10],       rsvd,        0x0 */
            uint32_t sf_dqs_oe_dly_sel              :  2; /* [27:26],        r/w,        0x0 */
            uint32_t sf_dqs_di_dly_sel              :  2; /* [29:28],        r/w,        0x0 */
            uint32_t sf_dqs_do_dly_sel              :  2; /* [31:30],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_io_dly_0;

    /* 0x34 : sf_if_io_dly_1 */
    union {
        struct {
            uint32_t sf_io_0_oe_dly_sel             :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf_io_0_di_dly_sel             :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf_io_0_do_dly_sel             :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_io_dly_1;

    /* 0x38 : sf_if_io_dly_2 */
    union {
        struct {
            uint32_t sf_io_1_oe_dly_sel             :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf_io_1_di_dly_sel             :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf_io_1_do_dly_sel             :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_io_dly_2;

    /* 0x3C : sf_if_io_dly_3 */
    union {
        struct {
            uint32_t sf_io_2_oe_dly_sel             :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf_io_2_di_dly_sel             :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf_io_2_do_dly_sel             :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_io_dly_3;

    /* 0x40 : sf_if_io_dly_4 */
    union {
        struct {
            uint32_t sf_io_3_oe_dly_sel             :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf_io_3_di_dly_sel             :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf_io_3_do_dly_sel             :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_io_dly_4;

    /* 0x44 : sf_reserved */
    union {
        struct {
            uint32_t sf_reserved                    : 32; /* [31: 0],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } sf_reserved;

    /* 0x48 : sf2_if_io_dly_0 */
    union {
        struct {
            uint32_t sf2_cs_dly_sel                 :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t sf2_cs2_dly_sel                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t sf2_clk_out_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_25                 : 16; /* [25:10],       rsvd,        0x0 */
            uint32_t sf2_dqs_oe_dly_sel             :  2; /* [27:26],        r/w,        0x0 */
            uint32_t sf2_dqs_di_dly_sel             :  2; /* [29:28],        r/w,        0x0 */
            uint32_t sf2_dqs_do_dly_sel             :  2; /* [31:30],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf2_if_io_dly_0;

    /* 0x4C : sf2_if_io_dly_1 */
    union {
        struct {
            uint32_t sf2_io_0_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf2_io_0_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf2_io_0_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf2_if_io_dly_1;

    /* 0x50 : sf2_if_io_dly_2 */
    union {
        struct {
            uint32_t sf2_io_1_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf2_io_1_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf2_io_1_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf2_if_io_dly_2;

    /* 0x54 : sf2_if_io_dly_3 */
    union {
        struct {
            uint32_t sf2_io_2_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf2_io_2_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf2_io_2_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf2_if_io_dly_3;

    /* 0x58 : sf2_if_io_dly_4 */
    union {
        struct {
            uint32_t sf2_io_3_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf2_io_3_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf2_io_3_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf2_if_io_dly_4;

    /* 0x5C : sf3_if_io_dly_0 */
    union {
        struct {
            uint32_t sf3_cs_dly_sel                 :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t sf3_cs2_dly_sel                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t sf3_clk_out_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_25                 : 16; /* [25:10],       rsvd,        0x0 */
            uint32_t sf3_dqs_oe_dly_sel             :  2; /* [27:26],        r/w,        0x0 */
            uint32_t sf3_dqs_di_dly_sel             :  2; /* [29:28],        r/w,        0x0 */
            uint32_t sf3_dqs_do_dly_sel             :  2; /* [31:30],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf3_if_io_dly_0;

    /* 0x60 : sf3_if_io_dly_1 */
    union {
        struct {
            uint32_t sf3_io_0_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf3_io_0_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf3_io_0_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf3_if_io_dly_1;

    /* 0x64 : sf3_if_io_dly_2 */
    union {
        struct {
            uint32_t sf3_io_1_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf3_io_1_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf3_io_1_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf3_if_io_dly_2;

    /* 0x68 : sf3_if_io_dly_3 */
    union {
        struct {
            uint32_t sf3_io_2_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf3_io_2_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf3_io_2_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf3_if_io_dly_3;

    /* 0x6C : sf3_if_io_dly_4 */
    union {
        struct {
            uint32_t sf3_io_3_oe_dly_sel            :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t sf3_io_3_di_dly_sel            :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t sf3_io_3_do_dly_sel            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf3_if_io_dly_4;

    /* 0x70 : sf_ctrl_2 */
    union {
        struct {
            uint32_t sf_if_pad_sel                  :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2                     :  1; /* [    2],       rsvd,        0x0 */
            uint32_t sf_if_pad_sel_lock             :  1; /* [    3],        r/w,        0x0 */
            uint32_t sf_if_dtr_en                   :  1; /* [    4],        r/w,        0x0 */
            uint32_t sf_if_dqs_en                   :  1; /* [    5],        r/w,        0x0 */
            uint32_t sf_if_trig_wr_prot             :  1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7_24                  : 18; /* [24: 7],       rsvd,        0x0 */
            uint32_t sf_ahb2sif_remap_lock          :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_ahb2sif_remap               :  2; /* [27:26],        r/w,        0x0 */
            uint32_t sf_if_bk_swap                  :  1; /* [   28],        r/w,        0x0 */
            uint32_t sf_if_bk2_mode                 :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_if_bk2_en                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_if_0_bk_sel                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_ctrl_2;

    /* 0x74 : sf_ctrl_3 */
    union {
        struct {
            uint32_t sf_cmds_2_wrap_len             :  4; /* [ 3: 0],        r/w,        0x6 */
            uint32_t sf_cmds_2_en                   :  1; /* [    4],        r/w,        0x1 */
            uint32_t sf_cmds_2_bt_dly               :  3; /* [ 7: 5],        r/w,        0x2 */
            uint32_t sf_cmds_2_bt_en                :  1; /* [    8],        r/w,        0x1 */
            uint32_t sf_cmds_2_wrap_q_ini           :  1; /* [    9],        r/w,        0x0 */
            uint32_t sf_cmds_2_wrap_mode            :  2; /* [11:10],        r/w,        0x0 */
            uint32_t sf_cmds_2_wrap_q               :  1; /* [   12],          r,        0x0 */
            uint32_t sf_cmds_1_wrap_len             :  4; /* [16:13],        r/w,        0x6 */
            uint32_t sf_cmds_1_en                   :  1; /* [   17],        r/w,        0x0 */
            uint32_t sf_cmds_1_wrap_mode            :  2; /* [19:18],        r/w,        0x0 */
            uint32_t sf_cmds_core_en                :  1; /* [   20],        r/w,        0x1 */
            uint32_t reserved_21_28                 :  8; /* [28:21],       rsvd,        0x0 */
            uint32_t sf_if_1_ack_lat                :  3; /* [31:29],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } sf_ctrl_3;

    /* 0x78 : sf_if_iahb_3 */
    union {
        struct {
            uint32_t reserved_0_11                  : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t sf_if_2_dmy_byte               :  5; /* [16:12],        r/w,        0x0 */
            uint32_t sf_if_2_adr_byte               :  3; /* [19:17],        r/w,        0x2 */
            uint32_t sf_if_2_cmd_byte               :  3; /* [22:20],        r/w,        0x0 */
            uint32_t sf_if_2_dat_rw                 :  1; /* [   23],        r/w,        0x1 */
            uint32_t sf_if_2_dat_en                 :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if_2_dmy_en                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_if_2_adr_en                 :  1; /* [   26],        r/w,        0x1 */
            uint32_t sf_if_2_cmd_en                 :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if_2_spi_mode               :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if_2_qpi_mode_en            :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_3;

    /* 0x7C : sf_if_iahb_4 */
    union {
        struct {
            uint32_t sf_if_2_cmd_buf_0              : 32; /* [31: 0],        r/w, 0x38000000 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_4;

    /* 0x80 : sf_if_iahb_5 */
    union {
        struct {
            uint32_t sf_if_2_cmd_buf_1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_5;

    /* 0x84 : sf_if_iahb_6 */
    union {
        struct {
            uint32_t reserved_0_16                  : 17; /* [16: 0],       rsvd,        0x0 */
            uint32_t sf_if_3_adr_byte               :  3; /* [19:17],        r/w,        0x0 */
            uint32_t sf_if_3_cmd_byte               :  3; /* [22:20],        r/w,        0x0 */
            uint32_t reserved_23_25                 :  3; /* [25:23],       rsvd,        0x0 */
            uint32_t sf_if_3_adr_en                 :  1; /* [   26],        r/w,        0x0 */
            uint32_t sf_if_3_cmd_en                 :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if_3_spi_mode               :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if_3_qpi_mode_en            :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_6;

    /* 0x88 : sf_if_iahb_7 */
    union {
        struct {
            uint32_t sf_if_3_cmd_buf_0              : 32; /* [31: 0],        r/w, 0xc0000000 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_7;

    /* 0x8C : sf_if_iahb_8 */
    union {
        struct {
            uint32_t sf_if_3_cmd_buf_1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_8;

    /* 0x90 : sf_if_iahb_9 */
    union {
        struct {
            uint32_t reserved_0_11                  : 12; /* [11: 0],       rsvd,        0x0 */
            uint32_t sf_if_4_dmy_byte               :  5; /* [16:12],        r/w,        0x2 */
            uint32_t sf_if_4_adr_byte               :  3; /* [19:17],        r/w,        0x2 */
            uint32_t sf_if_4_cmd_byte               :  3; /* [22:20],        r/w,        0x0 */
            uint32_t sf_if_4_dat_rw                 :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if_4_dat_en                 :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if_4_dmy_en                 :  1; /* [   25],        r/w,        0x1 */
            uint32_t sf_if_4_adr_en                 :  1; /* [   26],        r/w,        0x1 */
            uint32_t sf_if_4_cmd_en                 :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if_4_spi_mode               :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if_4_qpi_mode_en            :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_9;

    /* 0x94 : sf_if_iahb_10 */
    union {
        struct {
            uint32_t sf_if_4_cmd_buf_0              : 32; /* [31: 0],        r/w, 0xeb000000 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_10;

    /* 0x98 : sf_if_iahb_11 */
    union {
        struct {
            uint32_t sf_if_4_cmd_buf_1              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_11;

    /* 0x9C : sf_if_iahb_12 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t sf2_clk_sf_rx_inv_sel          :  1; /* [    2],        r/w,        0x0 */
            uint32_t sf2_clk_sf_rx_inv_src          :  1; /* [    3],        r/w,        0x0 */
            uint32_t sf2_clk_out_inv_sel            :  1; /* [    4],        r/w,        0x1 */
            uint32_t sf3_clk_out_inv_sel            :  1; /* [    5],        r/w,        0x1 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t sf2_if_read_dly_n              :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t sf2_if_read_dly_en             :  1; /* [   11],        r/w,        0x0 */
            uint32_t sf2_if_read_dly_src            :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if_iahb_12;

    /* 0xA0 : sf_id0_offset */
    union {
        struct {
            uint32_t sf_id0_offset                  : 28; /* [27: 0],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_id0_offset;

    /* 0xA4 : sf_id1_offset */
    union {
        struct {
            uint32_t sf_id1_offset                  : 28; /* [27: 0],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_id1_offset;

    /* 0xA8 : sf_bk2_id0_offset */
    union {
        struct {
            uint32_t sf_bk2_id0_offset              : 28; /* [27: 0],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_bk2_id0_offset;

    /* 0xAC : sf_bk2_id1_offset */
    union {
        struct {
            uint32_t sf_bk2_id1_offset              : 28; /* [27: 0],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_bk2_id1_offset;

    /* 0xB0 : sf_dbg */
    union {
        struct {
            uint32_t sf_autoload_st                 :  5; /* [ 4: 0],          r,        0x1 */
            uint32_t sf_autoload_st_done            :  1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_31                  : 26; /* [31: 6],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_dbg;

    /* 0xb4  reserved */
    uint8_t RESERVED0xb4[12];

    /* 0xC0 : sf_if2_ctrl_0 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t sf_clk_sf_if2_rx_inv_sel       :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t sf_if2_read_dly_n              :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t sf_if2_read_dly_en             :  1; /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t sf_if2_int                     :  1; /* [   16],          r,        0x0 */
            uint32_t sf_if2_int_clr                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t sf_if2_int_set                 :  1; /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_22                 :  4; /* [22:19],       rsvd,        0x0 */
            uint32_t sf_if2_replace_sf1             :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if2_replace_sf2             :  1; /* [   24],        r/w,        0x0 */
            uint32_t sf_if2_replace_sf3             :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_if2_pad_sel                 :  2; /* [27:26],        r/w,        0x0 */
            uint32_t sf_if2_bk_swap                 :  1; /* [   28],        r/w,        0x0 */
            uint32_t sf_if2_bk2_mode                :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_if2_bk2_en                  :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_if2_bk_sel                  :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if2_ctrl_0;

    /* 0xC4 : sf_if2_ctrl_1 */
    union {
        struct {
            uint32_t sf_if2_sr_pat_mask             :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t sf_if2_sr_pat                  :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t sf_if2_sr_int                  :  1; /* [   16],          r,        0x0 */
            uint32_t sf_if2_sr_int_en               :  1; /* [   17],        r/w,        0x0 */
            uint32_t sf_if2_sr_int_set              :  1; /* [   18],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t sf_if2_ack_lat                 :  3; /* [22:20],        r/w,        0x6 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t sf_if2_reg_hold                :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if2_reg_wp                  :  1; /* [   25],        r/w,        0x1 */
            uint32_t reserved_26_27                 :  2; /* [27:26],       rsvd,        0x0 */
            uint32_t sf_if2_fn_sel                  :  1; /* [   28],        r/w,        0x0 */
            uint32_t sf_if2_en                      :  1; /* [   29],        r/w,        0x1 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if2_ctrl_1;

    /* 0xC8 : sf_if2_sahb_0 */
    union {
        struct {
            uint32_t sf_if2_busy                    :  1; /* [    0],          r,        0x0 */
            uint32_t sf_if2_0_trig                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t sf_if2_0_dat_byte              : 10; /* [11: 2],        r/w,       0xff */
            uint32_t sf_if2_0_dmy_byte              :  5; /* [16:12],        r/w,        0x0 */
            uint32_t sf_if2_0_adr_byte              :  3; /* [19:17],        r/w,        0x2 */
            uint32_t sf_if2_0_cmd_byte              :  3; /* [22:20],        r/w,        0x0 */
            uint32_t sf_if2_0_dat_rw                :  1; /* [   23],        r/w,        0x0 */
            uint32_t sf_if2_0_dat_en                :  1; /* [   24],        r/w,        0x1 */
            uint32_t sf_if2_0_dmy_en                :  1; /* [   25],        r/w,        0x0 */
            uint32_t sf_if2_0_adr_en                :  1; /* [   26],        r/w,        0x1 */
            uint32_t sf_if2_0_cmd_en                :  1; /* [   27],        r/w,        0x1 */
            uint32_t sf_if2_0_spi_mode              :  3; /* [30:28],        r/w,        0x0 */
            uint32_t sf_if2_0_qpi_mode_en           :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if2_sahb_0;

    /* 0xCC : sf_if2_sahb_1 */
    union {
        struct {
            uint32_t sf_if2_0_cmd_buf_0             : 32; /* [31: 0],        r/w,  0x3000000 */
        }BF;
        uint32_t WORD;
    } sf_if2_sahb_1;

    /* 0xD0 : sf_if2_sahb_2 */
    union {
        struct {
            uint32_t sf_if2_0_cmd_buf_1             : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_if2_sahb_2;

    /* 0xd4  reserved */
    uint8_t RESERVED0xd4[44];

    /* 0x100 : sf_ctrl_prot_en_rd */
    union {
        struct {
            uint32_t sf_ctrl_prot_en_rd             :  1; /* [    0],          r,        0x1 */
            uint32_t sf_ctrl_id0_en_rd              :  1; /* [    1],          r,        0x1 */
            uint32_t sf_ctrl_id1_en_rd              :  1; /* [    2],          r,        0x1 */
            uint32_t reserved_3_28                  : 26; /* [28: 3],       rsvd,        0x0 */
            uint32_t sf_if2_0_trig_wr_lock          :  1; /* [   29],          r,        0x0 */
            uint32_t sf_if_0_trig_wr_lock           :  1; /* [   30],          r,        0x0 */
            uint32_t sf_dbg_dis                     :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_ctrl_prot_en_rd;

    /* 0x104 : sf_ctrl_prot_en */
    union {
        struct {
            uint32_t sf_ctrl_prot_en                :  1; /* [    0],        r/w,        0x1 */
            uint32_t sf_ctrl_id0_en                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t sf_ctrl_id1_en                 :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_ctrl_prot_en;

    /* 0x108  reserved */
    uint8_t RESERVED0x108[248];

    /* 0x200 : sf_aes_key_r0_0 */
    union {
        struct {
            uint32_t sf_aes_key_r0_0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_0;

    /* 0x204 : sf_aes_key_r0_1 */
    union {
        struct {
            uint32_t sf_aes_key_r0_1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_1;

    /* 0x208 : sf_aes_key_r0_2 */
    union {
        struct {
            uint32_t sf_aes_key_r0_2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_2;

    /* 0x20C : sf_aes_key_r0_3 */
    union {
        struct {
            uint32_t sf_aes_key_r0_3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_3;

    /* 0x210 : sf_aes_key_r0_4 */
    union {
        struct {
            uint32_t sf_aes_key_r0_4                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_4;

    /* 0x214 : sf_aes_key_r0_5 */
    union {
        struct {
            uint32_t sf_aes_key_r0_5                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_5;

    /* 0x218 : sf_aes_key_r0_6 */
    union {
        struct {
            uint32_t sf_aes_key_r0_6                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_6;

    /* 0x21C : sf_aes_key_r0_7 */
    union {
        struct {
            uint32_t sf_aes_key_r0_7                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r0_7;

    /* 0x220 : sf_aes_iv_r0_w0 */
    union {
        struct {
            uint32_t sf_aes_iv_r0_w0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r0_w0;

    /* 0x224 : sf_aes_iv_r0_w1 */
    union {
        struct {
            uint32_t sf_aes_iv_r0_w1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r0_w1;

    /* 0x228 : sf_aes_iv_r0_w2 */
    union {
        struct {
            uint32_t sf_aes_iv_r0_w2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r0_w2;

    /* 0x22C : sf_aes_iv_r0_w3 */
    union {
        struct {
            uint32_t sf_aes_iv_r0_w3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r0_w3;

    /* 0x230 : sf_aes_r0_start */
    union {
        struct {
            uint32_t sf_aes_region_r0_start         : 19; /* [18: 0],        r/w,        0x0 */
            uint32_t reserved_19_28                 : 10; /* [28:19],       rsvd,        0x0 */
            uint32_t sf_aes_region_r0_hw_key_en     :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_aes_region_r0_en            :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_aes_region_r0_lock          :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r0_start;

    /* 0x234 : sf_aes_r0_end */
    union {
        struct {
            uint32_t sf_aes_region_r0_end           : 19; /* [18: 0],        r/w,     0x3fff */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r0_end;

    /* 0x238  reserved */
    uint8_t RESERVED0x238[72];

    /* 0x280 : sf_aes_key_r1_0 */
    union {
        struct {
            uint32_t sf_aes_key_r1_0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_0;

    /* 0x284 : sf_aes_key_r1_1 */
    union {
        struct {
            uint32_t sf_aes_key_r1_1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_1;

    /* 0x288 : sf_aes_key_r1_2 */
    union {
        struct {
            uint32_t sf_aes_key_r1_2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_2;

    /* 0x28C : sf_aes_key_r1_3 */
    union {
        struct {
            uint32_t sf_aes_key_r1_3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_3;

    /* 0x290 : sf_aes_key_r1_4 */
    union {
        struct {
            uint32_t sf_aes_key_r1_4                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_4;

    /* 0x294 : sf_aes_key_r1_5 */
    union {
        struct {
            uint32_t sf_aes_key_r1_5                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_5;

    /* 0x298 : sf_aes_key_r1_6 */
    union {
        struct {
            uint32_t sf_aes_key_r1_6                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_6;

    /* 0x29C : sf_aes_key_r1_7 */
    union {
        struct {
            uint32_t sf_aes_key_r1_7                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r1_7;

    /* 0x2A0 : sf_aes_iv_r1_w0 */
    union {
        struct {
            uint32_t sf_aes_iv_r1_w0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r1_w0;

    /* 0x2A4 : sf_aes_iv_r1_w1 */
    union {
        struct {
            uint32_t sf_aes_iv_r1_w1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r1_w1;

    /* 0x2A8 : sf_aes_iv_r1_w2 */
    union {
        struct {
            uint32_t sf_aes_iv_r1_w2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r1_w2;

    /* 0x2AC : sf_aes_iv_r1_w3 */
    union {
        struct {
            uint32_t sf_aes_iv_r1_w3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r1_w3;

    /* 0x2B0 : sf_aes_r1_start */
    union {
        struct {
            uint32_t sf_aes_r1_start                : 19; /* [18: 0],        r/w,        0x0 */
            uint32_t reserved_19_28                 : 10; /* [28:19],       rsvd,        0x0 */
            uint32_t sf_aes_r1_hw_key_en            :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_aes_r1_en                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_aes_r1_lock                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r1_start;

    /* 0x2B4 : sf_aes_r1_end */
    union {
        struct {
            uint32_t sf_aes_r1_end                  : 19; /* [18: 0],        r/w,     0x3fff */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r1_end;

    /* 0x2b8  reserved */
    uint8_t RESERVED0x2b8[72];

    /* 0x300 : sf_aes_key_r2_0 */
    union {
        struct {
            uint32_t sf_aes_key_r2_0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_0;

    /* 0x304 : sf_aes_key_r2_1 */
    union {
        struct {
            uint32_t sf_aes_key_r2_1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_1;

    /* 0x308 : sf_aes_key_r2_2 */
    union {
        struct {
            uint32_t sf_aes_key_r2_2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_2;

    /* 0x30C : sf_aes_key_r2_3 */
    union {
        struct {
            uint32_t sf_aes_key_r2_3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_3;

    /* 0x310 : sf_aes_key_r2_4 */
    union {
        struct {
            uint32_t sf_aes_key_r2_4                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_4;

    /* 0x314 : sf_aes_key_r2_5 */
    union {
        struct {
            uint32_t sf_aes_key_r2_5                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_5;

    /* 0x318 : sf_aes_key_r2_6 */
    union {
        struct {
            uint32_t sf_aes_key_r2_6                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_6;

    /* 0x31C : sf_aes_key_r2_7 */
    union {
        struct {
            uint32_t sf_aes_key_r2_7                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_r2_7;

    /* 0x320 : sf_aes_iv_r2_w0 */
    union {
        struct {
            uint32_t sf_aes_iv_r2_w0                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r2_w0;

    /* 0x324 : sf_aes_iv_r2_w1 */
    union {
        struct {
            uint32_t sf_aes_iv_r2_w1                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r2_w1;

    /* 0x328 : sf_aes_iv_r2_w2 */
    union {
        struct {
            uint32_t sf_aes_iv_r2_w2                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r2_w2;

    /* 0x32C : sf_aes_iv_r2_w3 */
    union {
        struct {
            uint32_t sf_aes_iv_r2_w3                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_r2_w3;

    /* 0x330 : sf_aes_r2_start */
    union {
        struct {
            uint32_t sf_aes_r2_start                : 19; /* [18: 0],        r/w,        0x0 */
            uint32_t reserved_19_28                 : 10; /* [28:19],       rsvd,        0x0 */
            uint32_t sf_aes_r2_hw_key_en            :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_aes_r2_en                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_aes_r2_lock                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r2_start;

    /* 0x334 : sf_aes_r2_end */
    union {
        struct {
            uint32_t sf_aes_r2_end                  : 19; /* [18: 0],        r/w,     0x3fff */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_r2_end;

};

typedef volatile struct sf_ctrl_reg sf_ctrl_reg_t;


/*Following is reg patch*/

/* 0x0 : sf_if_sahb_0 */
#define SF_CTRL_IF_SAHB_0_OFFSET                                (0x0)
#define SF_CTRL_IF_BUSY                                         SF_CTRL_IF_BUSY
#define SF_CTRL_IF_BUSY_POS                                     (0U)
#define SF_CTRL_IF_BUSY_LEN                                     (1U)
#define SF_CTRL_IF_BUSY_MSK                                     (((1U<<SF_CTRL_IF_BUSY_LEN)-1)<<SF_CTRL_IF_BUSY_POS)
#define SF_CTRL_IF_BUSY_UMSK                                    (~(((1U<<SF_CTRL_IF_BUSY_LEN)-1)<<SF_CTRL_IF_BUSY_POS))
#define SF_CTRL_IF_0_TRIG                                       SF_CTRL_IF_0_TRIG
#define SF_CTRL_IF_0_TRIG_POS                                   (1U)
#define SF_CTRL_IF_0_TRIG_LEN                                   (1U)
#define SF_CTRL_IF_0_TRIG_MSK                                   (((1U<<SF_CTRL_IF_0_TRIG_LEN)-1)<<SF_CTRL_IF_0_TRIG_POS)
#define SF_CTRL_IF_0_TRIG_UMSK                                  (~(((1U<<SF_CTRL_IF_0_TRIG_LEN)-1)<<SF_CTRL_IF_0_TRIG_POS))
#define SF_CTRL_IF_0_DAT_BYTE                                   SF_CTRL_IF_0_DAT_BYTE
#define SF_CTRL_IF_0_DAT_BYTE_POS                               (2U)
#define SF_CTRL_IF_0_DAT_BYTE_LEN                               (10U)
#define SF_CTRL_IF_0_DAT_BYTE_MSK                               (((1U<<SF_CTRL_IF_0_DAT_BYTE_LEN)-1)<<SF_CTRL_IF_0_DAT_BYTE_POS)
#define SF_CTRL_IF_0_DAT_BYTE_UMSK                              (~(((1U<<SF_CTRL_IF_0_DAT_BYTE_LEN)-1)<<SF_CTRL_IF_0_DAT_BYTE_POS))
#define SF_CTRL_IF_0_DMY_BYTE                                   SF_CTRL_IF_0_DMY_BYTE
#define SF_CTRL_IF_0_DMY_BYTE_POS                               (12U)
#define SF_CTRL_IF_0_DMY_BYTE_LEN                               (5U)
#define SF_CTRL_IF_0_DMY_BYTE_MSK                               (((1U<<SF_CTRL_IF_0_DMY_BYTE_LEN)-1)<<SF_CTRL_IF_0_DMY_BYTE_POS)
#define SF_CTRL_IF_0_DMY_BYTE_UMSK                              (~(((1U<<SF_CTRL_IF_0_DMY_BYTE_LEN)-1)<<SF_CTRL_IF_0_DMY_BYTE_POS))
#define SF_CTRL_IF_0_ADR_BYTE                                   SF_CTRL_IF_0_ADR_BYTE
#define SF_CTRL_IF_0_ADR_BYTE_POS                               (17U)
#define SF_CTRL_IF_0_ADR_BYTE_LEN                               (3U)
#define SF_CTRL_IF_0_ADR_BYTE_MSK                               (((1U<<SF_CTRL_IF_0_ADR_BYTE_LEN)-1)<<SF_CTRL_IF_0_ADR_BYTE_POS)
#define SF_CTRL_IF_0_ADR_BYTE_UMSK                              (~(((1U<<SF_CTRL_IF_0_ADR_BYTE_LEN)-1)<<SF_CTRL_IF_0_ADR_BYTE_POS))
#define SF_CTRL_IF_0_CMD_BYTE                                   SF_CTRL_IF_0_CMD_BYTE
#define SF_CTRL_IF_0_CMD_BYTE_POS                               (20U)
#define SF_CTRL_IF_0_CMD_BYTE_LEN                               (3U)
#define SF_CTRL_IF_0_CMD_BYTE_MSK                               (((1U<<SF_CTRL_IF_0_CMD_BYTE_LEN)-1)<<SF_CTRL_IF_0_CMD_BYTE_POS)
#define SF_CTRL_IF_0_CMD_BYTE_UMSK                              (~(((1U<<SF_CTRL_IF_0_CMD_BYTE_LEN)-1)<<SF_CTRL_IF_0_CMD_BYTE_POS))
#define SF_CTRL_IF_0_DAT_RW                                     SF_CTRL_IF_0_DAT_RW
#define SF_CTRL_IF_0_DAT_RW_POS                                 (23U)
#define SF_CTRL_IF_0_DAT_RW_LEN                                 (1U)
#define SF_CTRL_IF_0_DAT_RW_MSK                                 (((1U<<SF_CTRL_IF_0_DAT_RW_LEN)-1)<<SF_CTRL_IF_0_DAT_RW_POS)
#define SF_CTRL_IF_0_DAT_RW_UMSK                                (~(((1U<<SF_CTRL_IF_0_DAT_RW_LEN)-1)<<SF_CTRL_IF_0_DAT_RW_POS))
#define SF_CTRL_IF_0_DAT_EN                                     SF_CTRL_IF_0_DAT_EN
#define SF_CTRL_IF_0_DAT_EN_POS                                 (24U)
#define SF_CTRL_IF_0_DAT_EN_LEN                                 (1U)
#define SF_CTRL_IF_0_DAT_EN_MSK                                 (((1U<<SF_CTRL_IF_0_DAT_EN_LEN)-1)<<SF_CTRL_IF_0_DAT_EN_POS)
#define SF_CTRL_IF_0_DAT_EN_UMSK                                (~(((1U<<SF_CTRL_IF_0_DAT_EN_LEN)-1)<<SF_CTRL_IF_0_DAT_EN_POS))
#define SF_CTRL_IF_0_DMY_EN                                     SF_CTRL_IF_0_DMY_EN
#define SF_CTRL_IF_0_DMY_EN_POS                                 (25U)
#define SF_CTRL_IF_0_DMY_EN_LEN                                 (1U)
#define SF_CTRL_IF_0_DMY_EN_MSK                                 (((1U<<SF_CTRL_IF_0_DMY_EN_LEN)-1)<<SF_CTRL_IF_0_DMY_EN_POS)
#define SF_CTRL_IF_0_DMY_EN_UMSK                                (~(((1U<<SF_CTRL_IF_0_DMY_EN_LEN)-1)<<SF_CTRL_IF_0_DMY_EN_POS))
#define SF_CTRL_IF_0_ADR_EN                                     SF_CTRL_IF_0_ADR_EN
#define SF_CTRL_IF_0_ADR_EN_POS                                 (26U)
#define SF_CTRL_IF_0_ADR_EN_LEN                                 (1U)
#define SF_CTRL_IF_0_ADR_EN_MSK                                 (((1U<<SF_CTRL_IF_0_ADR_EN_LEN)-1)<<SF_CTRL_IF_0_ADR_EN_POS)
#define SF_CTRL_IF_0_ADR_EN_UMSK                                (~(((1U<<SF_CTRL_IF_0_ADR_EN_LEN)-1)<<SF_CTRL_IF_0_ADR_EN_POS))
#define SF_CTRL_IF_0_CMD_EN                                     SF_CTRL_IF_0_CMD_EN
#define SF_CTRL_IF_0_CMD_EN_POS                                 (27U)
#define SF_CTRL_IF_0_CMD_EN_LEN                                 (1U)
#define SF_CTRL_IF_0_CMD_EN_MSK                                 (((1U<<SF_CTRL_IF_0_CMD_EN_LEN)-1)<<SF_CTRL_IF_0_CMD_EN_POS)
#define SF_CTRL_IF_0_CMD_EN_UMSK                                (~(((1U<<SF_CTRL_IF_0_CMD_EN_LEN)-1)<<SF_CTRL_IF_0_CMD_EN_POS))
#define SF_CTRL_IF_0_SPI_MODE                                   SF_CTRL_IF_0_SPI_MODE
#define SF_CTRL_IF_0_SPI_MODE_POS                               (28U)
#define SF_CTRL_IF_0_SPI_MODE_LEN                               (3U)
#define SF_CTRL_IF_0_SPI_MODE_MSK                               (((1U<<SF_CTRL_IF_0_SPI_MODE_LEN)-1)<<SF_CTRL_IF_0_SPI_MODE_POS)
#define SF_CTRL_IF_0_SPI_MODE_UMSK                              (~(((1U<<SF_CTRL_IF_0_SPI_MODE_LEN)-1)<<SF_CTRL_IF_0_SPI_MODE_POS))
#define SF_CTRL_IF_0_QPI_MODE_EN                                SF_CTRL_IF_0_QPI_MODE_EN
#define SF_CTRL_IF_0_QPI_MODE_EN_POS                            (31U)
#define SF_CTRL_IF_0_QPI_MODE_EN_LEN                            (1U)
#define SF_CTRL_IF_0_QPI_MODE_EN_MSK                            (((1U<<SF_CTRL_IF_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_IF_0_QPI_MODE_EN_POS)
#define SF_CTRL_IF_0_QPI_MODE_EN_UMSK                           (~(((1U<<SF_CTRL_IF_0_QPI_MODE_EN_LEN)-1)<<SF_CTRL_IF_0_QPI_MODE_EN_POS))

/* 0x4 : sf_if_sahb_1 */
#define SF_CTRL_IF_SAHB_1_OFFSET                                (0x4)
#define SF_CTRL_IF_0_CMD_BUF_0                                  SF_CTRL_IF_0_CMD_BUF_0
#define SF_CTRL_IF_0_CMD_BUF_0_POS                              (0U)
#define SF_CTRL_IF_0_CMD_BUF_0_LEN                              (32U)
#define SF_CTRL_IF_0_CMD_BUF_0_MSK                              (((1U<<SF_CTRL_IF_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_IF_0_CMD_BUF_0_POS)
#define SF_CTRL_IF_0_CMD_BUF_0_UMSK                             (~(((1U<<SF_CTRL_IF_0_CMD_BUF_0_LEN)-1)<<SF_CTRL_IF_0_CMD_BUF_0_POS))

/* 0x8 : sf_if_sahb_2 */
#define SF_CTRL_IF_SAHB_2_OFFSET                                (0x8)
#define SF_CTRL_IF_0_CMD_BUF_1                                  SF_CTRL_IF_0_CMD_BUF_1
#define SF_CTRL_IF_0_CMD_BUF_1_POS                              (0U)
#define SF_CTRL_IF_0_CMD_BUF_1_LEN                              (32U)
#define SF_CTRL_IF_0_CMD_BUF_1_MSK                              (((1U<<SF_CTRL_IF_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_IF_0_CMD_BUF_1_POS)
#define SF_CTRL_IF_0_CMD_BUF_1_UMSK                             (~(((1U<<SF_CTRL_IF_0_CMD_BUF_1_LEN)-1)<<SF_CTRL_IF_0_CMD_BUF_1_POS))


struct  sf_if_sahb_0_reg {
    /* 0x0 : sf_if_sahb_0 */
    union {
        struct {
            uint32_t if_busy                        :  1; /* [    0],          r,        0x0 */
            uint32_t if_0_trig                      :  1; /* [    1],        r/w,        0x0 */
            uint32_t if_0_dat_byte                  : 10; /* [11: 2],        r/w,       0xff */
            uint32_t if_0_dmy_byte                  :  5; /* [16:12],        r/w,        0x0 */
            uint32_t if_0_adr_byte                  :  3; /* [19:17],        r/w,        0x2 */
            uint32_t if_0_cmd_byte                  :  3; /* [22:20],        r/w,        0x0 */
            uint32_t if_0_dat_rw                    :  1; /* [   23],        r/w,        0x0 */
            uint32_t if_0_dat_en                    :  1; /* [   24],        r/w,        0x1 */
            uint32_t if_0_dmy_en                    :  1; /* [   25],        r/w,        0x0 */
            uint32_t if_0_adr_en                    :  1; /* [   26],        r/w,        0x1 */
            uint32_t if_0_cmd_en                    :  1; /* [   27],        r/w,        0x1 */
            uint32_t if_0_spi_mode                  :  3; /* [30:28],        r/w,        0x0 */
            uint32_t if_0_qpi_mode_en               :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } if_sahb_0;

    /* 0x4 : sf_if_sahb_1 */
    union {
        struct {
            uint32_t if_0_cmd_buf_0                 : 32; /* [31: 0],        r/w,  0x3000000 */
        }BF;
        uint32_t WORD;
    } if_sahb_1;

    /* 0x8 : sf_if_sahb_2 */
    union {
        struct {
            uint32_t if_0_cmd_buf_1                 : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } if_sahb_2;

};

typedef volatile struct sf_if_sahb_0_reg sf_if_sahb_0_reg_t;

#define SF_CTRL_IF1_SAHB_OFFSET     0x8
#define SF_CTRL_IF2_SAHB_OFFSET     0xC8


/*Following is reg patch*/

/* 0x0 : if_io_dly_0 */
#define SF_CTRL_IO_DLY_0_OFFSET                                 (0x0)
#define SF_CTRL_CS_DLY_SEL                                      SF_CTRL_CS_DLY_SEL
#define SF_CTRL_CS_DLY_SEL_POS                                  (0U)
#define SF_CTRL_CS_DLY_SEL_LEN                                  (2U)
#define SF_CTRL_CS_DLY_SEL_MSK                                  (((1U<<SF_CTRL_CS_DLY_SEL_LEN)-1)<<SF_CTRL_CS_DLY_SEL_POS)
#define SF_CTRL_CS_DLY_SEL_UMSK                                 (~(((1U<<SF_CTRL_CS_DLY_SEL_LEN)-1)<<SF_CTRL_CS_DLY_SEL_POS))
#define SF_CTRL_CS2_DLY_SEL                                     SF_CTRL_CS2_DLY_SEL
#define SF_CTRL_CS2_DLY_SEL_POS                                 (2U)
#define SF_CTRL_CS2_DLY_SEL_LEN                                 (2U)
#define SF_CTRL_CS2_DLY_SEL_MSK                                 (((1U<<SF_CTRL_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_CS2_DLY_SEL_POS)
#define SF_CTRL_CS2_DLY_SEL_UMSK                                (~(((1U<<SF_CTRL_CS2_DLY_SEL_LEN)-1)<<SF_CTRL_CS2_DLY_SEL_POS))
#define SF_CTRL_CLK_OUT_DLY_SEL                                 SF_CTRL_CLK_OUT_DLY_SEL
#define SF_CTRL_CLK_OUT_DLY_SEL_POS                             (8U)
#define SF_CTRL_CLK_OUT_DLY_SEL_LEN                             (2U)
#define SF_CTRL_CLK_OUT_DLY_SEL_MSK                             (((1U<<SF_CTRL_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_CLK_OUT_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_CLK_OUT_DLY_SEL_LEN)-1)<<SF_CTRL_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_DQS_OE_DLY_SEL                                  SF_CTRL_DQS_OE_DLY_SEL
#define SF_CTRL_DQS_OE_DLY_SEL_POS                              (26U)
#define SF_CTRL_DQS_OE_DLY_SEL_LEN                              (2U)
#define SF_CTRL_DQS_OE_DLY_SEL_MSK                              (((1U<<SF_CTRL_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_DQS_OE_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_DQS_OE_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_DQS_DI_DLY_SEL                                  SF_CTRL_DQS_DI_DLY_SEL
#define SF_CTRL_DQS_DI_DLY_SEL_POS                              (28U)
#define SF_CTRL_DQS_DI_DLY_SEL_LEN                              (2U)
#define SF_CTRL_DQS_DI_DLY_SEL_MSK                              (((1U<<SF_CTRL_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_DQS_DI_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_DQS_DI_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_DQS_DO_DLY_SEL                                  SF_CTRL_DQS_DO_DLY_SEL
#define SF_CTRL_DQS_DO_DLY_SEL_POS                              (30U)
#define SF_CTRL_DQS_DO_DLY_SEL_LEN                              (2U)
#define SF_CTRL_DQS_DO_DLY_SEL_MSK                              (((1U<<SF_CTRL_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_DQS_DO_DLY_SEL_UMSK                             (~(((1U<<SF_CTRL_DQS_DO_DLY_SEL_LEN)-1)<<SF_CTRL_DQS_DO_DLY_SEL_POS))

/* 0x4 : if_io_dly_1 */
#define SF_CTRL_IO_DLY_1_OFFSET                                 (0x4)
#define SF_CTRL_IO_0_OE_DLY_SEL                                 SF_CTRL_IO_0_OE_DLY_SEL
#define SF_CTRL_IO_0_OE_DLY_SEL_POS                             (0U)
#define SF_CTRL_IO_0_OE_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_0_OE_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_IO_0_OE_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_0_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_IO_0_DI_DLY_SEL                                 SF_CTRL_IO_0_DI_DLY_SEL
#define SF_CTRL_IO_0_DI_DLY_SEL_POS                             (8U)
#define SF_CTRL_IO_0_DI_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_0_DI_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_IO_0_DI_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_0_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_IO_0_DO_DLY_SEL                                 SF_CTRL_IO_0_DO_DLY_SEL
#define SF_CTRL_IO_0_DO_DLY_SEL_POS                             (16U)
#define SF_CTRL_IO_0_DO_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_0_DO_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_IO_0_DO_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_0_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_0_DO_DLY_SEL_POS))

/* 0x8 : if_io_dly_2 */
#define SF_CTRL_IO_DLY_2_OFFSET                                 (0x8)
#define SF_CTRL_IO_1_OE_DLY_SEL                                 SF_CTRL_IO_1_OE_DLY_SEL
#define SF_CTRL_IO_1_OE_DLY_SEL_POS                             (0U)
#define SF_CTRL_IO_1_OE_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_1_OE_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_IO_1_OE_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_1_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_IO_1_DI_DLY_SEL                                 SF_CTRL_IO_1_DI_DLY_SEL
#define SF_CTRL_IO_1_DI_DLY_SEL_POS                             (8U)
#define SF_CTRL_IO_1_DI_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_1_DI_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_IO_1_DI_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_1_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_IO_1_DO_DLY_SEL                                 SF_CTRL_IO_1_DO_DLY_SEL
#define SF_CTRL_IO_1_DO_DLY_SEL_POS                             (16U)
#define SF_CTRL_IO_1_DO_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_1_DO_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_IO_1_DO_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_1_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_1_DO_DLY_SEL_POS))

/* 0xc : if_io_dly_3 */
#define SF_CTRL_IO_DLY_3_OFFSET                                 (0xc)
#define SF_CTRL_IO_2_OE_DLY_SEL                                 SF_CTRL_IO_2_OE_DLY_SEL
#define SF_CTRL_IO_2_OE_DLY_SEL_POS                             (0U)
#define SF_CTRL_IO_2_OE_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_2_OE_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_IO_2_OE_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_2_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_IO_2_DI_DLY_SEL                                 SF_CTRL_IO_2_DI_DLY_SEL
#define SF_CTRL_IO_2_DI_DLY_SEL_POS                             (8U)
#define SF_CTRL_IO_2_DI_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_2_DI_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_IO_2_DI_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_2_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_IO_2_DO_DLY_SEL                                 SF_CTRL_IO_2_DO_DLY_SEL
#define SF_CTRL_IO_2_DO_DLY_SEL_POS                             (16U)
#define SF_CTRL_IO_2_DO_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_2_DO_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_IO_2_DO_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_2_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_2_DO_DLY_SEL_POS))

/* 0x10 : if_io_dly_4 */
#define SF_CTRL_IO_DLY_4_OFFSET                                 (0x10)
#define SF_CTRL_IO_3_OE_DLY_SEL                                 SF_CTRL_IO_3_OE_DLY_SEL
#define SF_CTRL_IO_3_OE_DLY_SEL_POS                             (0U)
#define SF_CTRL_IO_3_OE_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_3_OE_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_IO_3_OE_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_3_OE_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_IO_3_DI_DLY_SEL                                 SF_CTRL_IO_3_DI_DLY_SEL
#define SF_CTRL_IO_3_DI_DLY_SEL_POS                             (8U)
#define SF_CTRL_IO_3_DI_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_3_DI_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_IO_3_DI_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_3_DI_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_IO_3_DO_DLY_SEL                                 SF_CTRL_IO_3_DO_DLY_SEL
#define SF_CTRL_IO_3_DO_DLY_SEL_POS                             (16U)
#define SF_CTRL_IO_3_DO_DLY_SEL_LEN                             (2U)
#define SF_CTRL_IO_3_DO_DLY_SEL_MSK                             (((1U<<SF_CTRL_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_IO_3_DO_DLY_SEL_UMSK                            (~(((1U<<SF_CTRL_IO_3_DO_DLY_SEL_LEN)-1)<<SF_CTRL_IO_3_DO_DLY_SEL_POS))


struct  sf_if_io_dly_0_reg {
    /* 0x0 : if_io_dly_0 */
    union {
        struct {
            uint32_t cs_dly_sel                     :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t cs2_dly_sel                    :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t clk_out_dly_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_25                 : 16; /* [25:10],       rsvd,        0x0 */
            uint32_t dqs_oe_dly_sel                 :  2; /* [27:26],        r/w,        0x0 */
            uint32_t dqs_di_dly_sel                 :  2; /* [29:28],        r/w,        0x0 */
            uint32_t dqs_do_dly_sel                 :  2; /* [31:30],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } io_dly_0;

    /* 0x4 : if_io_dly_1 */
    union {
        struct {
            uint32_t io_0_oe_dly_sel                :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t io_0_di_dly_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t io_0_do_dly_sel                :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } io_dly_1;

    /* 0x8 : if_io_dly_2 */
    union {
        struct {
            uint32_t io_1_oe_dly_sel                :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t io_1_di_dly_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t io_1_do_dly_sel                :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } io_dly_2;

    /* 0xc : if_io_dly_3 */
    union {
        struct {
            uint32_t io_2_oe_dly_sel                :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t io_2_di_dly_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t io_2_do_dly_sel                :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } io_dly_3;

    /* 0x10 : if_io_dly_4 */
    union {
        struct {
            uint32_t io_3_oe_dly_sel                :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t io_3_di_dly_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t io_3_do_dly_sel                :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } io_dly_4;

};

typedef volatile struct sf_if_io_dly_0_reg sf_if_io_dly_0_reg_t;

#define SF_CTRL_IF_IO_DLY_1_OFFSET     0x30
#define SF_CTRL_IF_IO_DLY_2_OFFSET     0x48
#define SF_CTRL_IF_IO_DLY_3_OFFSET     0x5C


/*Following is reg patch*/

/* 0x0 : sf_aes_key_0 */
#define SF_CTRL_SF_AES_KEY_0_OFFSET                             (0x0)
#define SF_CTRL_SF_AES_KEY_0                                    SF_CTRL_SF_AES_KEY_0
#define SF_CTRL_SF_AES_KEY_0_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_0_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_0_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_0_POS)
#define SF_CTRL_SF_AES_KEY_0_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_0_LEN)-1)<<SF_CTRL_SF_AES_KEY_0_POS))

/* 0x4 : sf_aes_key_1 */
#define SF_CTRL_SF_AES_KEY_1_OFFSET                             (0x4)
#define SF_CTRL_SF_AES_KEY_1                                    SF_CTRL_SF_AES_KEY_1
#define SF_CTRL_SF_AES_KEY_1_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_1_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_1_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_1_POS)
#define SF_CTRL_SF_AES_KEY_1_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_1_LEN)-1)<<SF_CTRL_SF_AES_KEY_1_POS))

/* 0x8 : sf_aes_key_2 */
#define SF_CTRL_SF_AES_KEY_2_OFFSET                             (0x8)
#define SF_CTRL_SF_AES_KEY_2                                    SF_CTRL_SF_AES_KEY_2
#define SF_CTRL_SF_AES_KEY_2_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_2_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_2_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_2_POS)
#define SF_CTRL_SF_AES_KEY_2_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_2_LEN)-1)<<SF_CTRL_SF_AES_KEY_2_POS))

/* 0xc : sf_aes_key_3 */
#define SF_CTRL_SF_AES_KEY_3_OFFSET                             (0xc)
#define SF_CTRL_SF_AES_KEY_3                                    SF_CTRL_SF_AES_KEY_3
#define SF_CTRL_SF_AES_KEY_3_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_3_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_3_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_3_POS)
#define SF_CTRL_SF_AES_KEY_3_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_3_LEN)-1)<<SF_CTRL_SF_AES_KEY_3_POS))

/* 0x10 : sf_aes_key_4 */
#define SF_CTRL_SF_AES_KEY_4_OFFSET                             (0x10)
#define SF_CTRL_SF_AES_KEY_4                                    SF_CTRL_SF_AES_KEY_4
#define SF_CTRL_SF_AES_KEY_4_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_4_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_4_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_4_POS)
#define SF_CTRL_SF_AES_KEY_4_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_4_LEN)-1)<<SF_CTRL_SF_AES_KEY_4_POS))

/* 0x14 : sf_aes_key_5 */
#define SF_CTRL_SF_AES_KEY_5_OFFSET                             (0x14)
#define SF_CTRL_SF_AES_KEY_5                                    SF_CTRL_SF_AES_KEY_5
#define SF_CTRL_SF_AES_KEY_5_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_5_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_5_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_5_POS)
#define SF_CTRL_SF_AES_KEY_5_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_5_LEN)-1)<<SF_CTRL_SF_AES_KEY_5_POS))

/* 0x18 : sf_aes_key_6 */
#define SF_CTRL_SF_AES_KEY_6_OFFSET                             (0x18)
#define SF_CTRL_SF_AES_KEY_6                                    SF_CTRL_SF_AES_KEY_6
#define SF_CTRL_SF_AES_KEY_6_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_6_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_6_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_6_POS)
#define SF_CTRL_SF_AES_KEY_6_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_6_LEN)-1)<<SF_CTRL_SF_AES_KEY_6_POS))

/* 0x1c : sf_aes_key_7 */
#define SF_CTRL_SF_AES_KEY_7_OFFSET                             (0x1c)
#define SF_CTRL_SF_AES_KEY_7                                    SF_CTRL_SF_AES_KEY_7
#define SF_CTRL_SF_AES_KEY_7_POS                                (0U)
#define SF_CTRL_SF_AES_KEY_7_LEN                                (32U)
#define SF_CTRL_SF_AES_KEY_7_MSK                                (((1U<<SF_CTRL_SF_AES_KEY_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_7_POS)
#define SF_CTRL_SF_AES_KEY_7_UMSK                               (~(((1U<<SF_CTRL_SF_AES_KEY_7_LEN)-1)<<SF_CTRL_SF_AES_KEY_7_POS))

/* 0x20 : sf_aes_iv_w0 */
#define SF_CTRL_SF_AES_IV_W0_OFFSET                             (0x20)
#define SF_CTRL_SF_AES_IV_W0                                    SF_CTRL_SF_AES_IV_W0
#define SF_CTRL_SF_AES_IV_W0_POS                                (0U)
#define SF_CTRL_SF_AES_IV_W0_LEN                                (32U)
#define SF_CTRL_SF_AES_IV_W0_MSK                                (((1U<<SF_CTRL_SF_AES_IV_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_W0_POS)
#define SF_CTRL_SF_AES_IV_W0_UMSK                               (~(((1U<<SF_CTRL_SF_AES_IV_W0_LEN)-1)<<SF_CTRL_SF_AES_IV_W0_POS))

/* 0x24 : sf_aes_iv_w1 */
#define SF_CTRL_SF_AES_IV_W1_OFFSET                             (0x24)
#define SF_CTRL_SF_AES_IV_W1                                    SF_CTRL_SF_AES_IV_W1
#define SF_CTRL_SF_AES_IV_W1_POS                                (0U)
#define SF_CTRL_SF_AES_IV_W1_LEN                                (32U)
#define SF_CTRL_SF_AES_IV_W1_MSK                                (((1U<<SF_CTRL_SF_AES_IV_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_W1_POS)
#define SF_CTRL_SF_AES_IV_W1_UMSK                               (~(((1U<<SF_CTRL_SF_AES_IV_W1_LEN)-1)<<SF_CTRL_SF_AES_IV_W1_POS))

/* 0x28 : sf_aes_iv_w2 */
#define SF_CTRL_SF_AES_IV_W2_OFFSET                             (0x28)
#define SF_CTRL_SF_AES_IV_W2                                    SF_CTRL_SF_AES_IV_W2
#define SF_CTRL_SF_AES_IV_W2_POS                                (0U)
#define SF_CTRL_SF_AES_IV_W2_LEN                                (32U)
#define SF_CTRL_SF_AES_IV_W2_MSK                                (((1U<<SF_CTRL_SF_AES_IV_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_W2_POS)
#define SF_CTRL_SF_AES_IV_W2_UMSK                               (~(((1U<<SF_CTRL_SF_AES_IV_W2_LEN)-1)<<SF_CTRL_SF_AES_IV_W2_POS))

/* 0x2c : sf_aes_iv_w3 */
#define SF_CTRL_SF_AES_IV_W3_OFFSET                             (0x2c)
#define SF_CTRL_SF_AES_IV_W3                                    SF_CTRL_SF_AES_IV_W3
#define SF_CTRL_SF_AES_IV_W3_POS                                (0U)
#define SF_CTRL_SF_AES_IV_W3_LEN                                (32U)
#define SF_CTRL_SF_AES_IV_W3_MSK                                (((1U<<SF_CTRL_SF_AES_IV_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_W3_POS)
#define SF_CTRL_SF_AES_IV_W3_UMSK                               (~(((1U<<SF_CTRL_SF_AES_IV_W3_LEN)-1)<<SF_CTRL_SF_AES_IV_W3_POS))

/* 0x30 : sf_aes_start */
#define SF_CTRL_SF_AES_START_OFFSET                             (0x30)
#define SF_CTRL_SF_AES_REGION_START                             SF_CTRL_SF_AES_REGION_START
#define SF_CTRL_SF_AES_REGION_START_POS                         (0U)
#define SF_CTRL_SF_AES_REGION_START_LEN                         (19U)
#define SF_CTRL_SF_AES_REGION_START_MSK                         (((1U<<SF_CTRL_SF_AES_REGION_START_LEN)-1)<<SF_CTRL_SF_AES_REGION_START_POS)
#define SF_CTRL_SF_AES_REGION_START_UMSK                        (~(((1U<<SF_CTRL_SF_AES_REGION_START_LEN)-1)<<SF_CTRL_SF_AES_REGION_START_POS))
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN                         SF_CTRL_SF_AES_REGION_HW_KEY_EN
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN_POS                     (29U)
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN_LEN                     (1U)
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN_MSK                     (((1U<<SF_CTRL_SF_AES_REGION_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_HW_KEY_EN_POS)
#define SF_CTRL_SF_AES_REGION_HW_KEY_EN_UMSK                    (~(((1U<<SF_CTRL_SF_AES_REGION_HW_KEY_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_HW_KEY_EN_POS))
#define SF_CTRL_SF_AES_REGION_EN                                SF_CTRL_SF_AES_REGION_EN
#define SF_CTRL_SF_AES_REGION_EN_POS                            (30U)
#define SF_CTRL_SF_AES_REGION_EN_LEN                            (1U)
#define SF_CTRL_SF_AES_REGION_EN_MSK                            (((1U<<SF_CTRL_SF_AES_REGION_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_EN_POS)
#define SF_CTRL_SF_AES_REGION_EN_UMSK                           (~(((1U<<SF_CTRL_SF_AES_REGION_EN_LEN)-1)<<SF_CTRL_SF_AES_REGION_EN_POS))
#define SF_CTRL_SF_AES_REGION_LOCK                              SF_CTRL_SF_AES_REGION_LOCK
#define SF_CTRL_SF_AES_REGION_LOCK_POS                          (31U)
#define SF_CTRL_SF_AES_REGION_LOCK_LEN                          (1U)
#define SF_CTRL_SF_AES_REGION_LOCK_MSK                          (((1U<<SF_CTRL_SF_AES_REGION_LOCK_LEN)-1)<<SF_CTRL_SF_AES_REGION_LOCK_POS)
#define SF_CTRL_SF_AES_REGION_LOCK_UMSK                         (~(((1U<<SF_CTRL_SF_AES_REGION_LOCK_LEN)-1)<<SF_CTRL_SF_AES_REGION_LOCK_POS))

/* 0x34 : sf_aes_end */
#define SF_CTRL_SF_AES_END_OFFSET                               (0x34)
#define SF_CTRL_SF_AES_REGION_END                               SF_CTRL_SF_AES_REGION_END
#define SF_CTRL_SF_AES_REGION_END_POS                           (0U)
#define SF_CTRL_SF_AES_REGION_END_LEN                           (19U)
#define SF_CTRL_SF_AES_REGION_END_MSK                           (((1U<<SF_CTRL_SF_AES_REGION_END_LEN)-1)<<SF_CTRL_SF_AES_REGION_END_POS)
#define SF_CTRL_SF_AES_REGION_END_UMSK                          (~(((1U<<SF_CTRL_SF_AES_REGION_END_LEN)-1)<<SF_CTRL_SF_AES_REGION_END_POS))


struct  sf_ctrl_aes_region_reg {
    /* 0x0 : sf_aes_key_0 */
    union {
        struct {
            uint32_t sf_aes_key_0                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_0;

    /* 0x4 : sf_aes_key_1 */
    union {
        struct {
            uint32_t sf_aes_key_1                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_1;

    /* 0x8 : sf_aes_key_2 */
    union {
        struct {
            uint32_t sf_aes_key_2                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_2;

    /* 0xc : sf_aes_key_3 */
    union {
        struct {
            uint32_t sf_aes_key_3                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_3;

    /* 0x10 : sf_aes_key_4 */
    union {
        struct {
            uint32_t sf_aes_key_4                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_4;

    /* 0x14 : sf_aes_key_5 */
    union {
        struct {
            uint32_t sf_aes_key_5                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_5;

    /* 0x18 : sf_aes_key_6 */
    union {
        struct {
            uint32_t sf_aes_key_6                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_6;

    /* 0x1c : sf_aes_key_7 */
    union {
        struct {
            uint32_t sf_aes_key_7                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_key_7;

    /* 0x20 : sf_aes_iv_w0 */
    union {
        struct {
            uint32_t sf_aes_iv_w0                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_w0;

    /* 0x24 : sf_aes_iv_w1 */
    union {
        struct {
            uint32_t sf_aes_iv_w1                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_w1;

    /* 0x28 : sf_aes_iv_w2 */
    union {
        struct {
            uint32_t sf_aes_iv_w2                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_w2;

    /* 0x2c : sf_aes_iv_w3 */
    union {
        struct {
            uint32_t sf_aes_iv_w3                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_iv_w3;

    /* 0x30 : sf_aes_start */
    union {
        struct {
            uint32_t sf_aes_region_start            : 19; /* [18: 0],        r/w,        0x0 */
            uint32_t reserved_19_28                 : 10; /* [28:19],       rsvd,        0x0 */
            uint32_t sf_aes_region_hw_key_en        :  1; /* [   29],        r/w,        0x0 */
            uint32_t sf_aes_region_en               :  1; /* [   30],        r/w,        0x0 */
            uint32_t sf_aes_region_lock             :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_start;

    /* 0x34 : sf_aes_end */
    union {
        struct {
            uint32_t sf_aes_region_end              : 19; /* [18: 0],        r/w,     0x3fff */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sf_aes_end;

};

typedef volatile struct sf_ctrl_aes_region_reg sf_ctrl_aes_region_reg_t;

#define SF_CTRL_AES_REGION_OFFSET     0x200


#endif  /* __SF_CTRL_REG_H__ */
