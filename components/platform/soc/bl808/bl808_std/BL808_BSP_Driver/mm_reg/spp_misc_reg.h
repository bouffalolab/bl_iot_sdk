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
#ifndef  __SPP_MISC_REG_H__
#define  __SPP_MISC_REG_H__

#include "bl808.h"

/* 0x0 : config */
#define SPP_MISC_CONFIG_OFFSET                                  (0x0)
#define SPP_MISC_RG_DVPAS_ENABLE                                SPP_MISC_RG_DVPAS_ENABLE
#define SPP_MISC_RG_DVPAS_ENABLE_POS                            (0U)
#define SPP_MISC_RG_DVPAS_ENABLE_LEN                            (1U)
#define SPP_MISC_RG_DVPAS_ENABLE_MSK                            (((1U<<SPP_MISC_RG_DVPAS_ENABLE_LEN)-1)<<SPP_MISC_RG_DVPAS_ENABLE_POS)
#define SPP_MISC_RG_DVPAS_ENABLE_UMSK                           (~(((1U<<SPP_MISC_RG_DVPAS_ENABLE_LEN)-1)<<SPP_MISC_RG_DVPAS_ENABLE_POS))
#define SPP_MISC_RG_DVPAS_HS_INV                                SPP_MISC_RG_DVPAS_HS_INV
#define SPP_MISC_RG_DVPAS_HS_INV_POS                            (1U)
#define SPP_MISC_RG_DVPAS_HS_INV_LEN                            (1U)
#define SPP_MISC_RG_DVPAS_HS_INV_MSK                            (((1U<<SPP_MISC_RG_DVPAS_HS_INV_LEN)-1)<<SPP_MISC_RG_DVPAS_HS_INV_POS)
#define SPP_MISC_RG_DVPAS_HS_INV_UMSK                           (~(((1U<<SPP_MISC_RG_DVPAS_HS_INV_LEN)-1)<<SPP_MISC_RG_DVPAS_HS_INV_POS))
#define SPP_MISC_RG_DVPAS_VS_INV                                SPP_MISC_RG_DVPAS_VS_INV
#define SPP_MISC_RG_DVPAS_VS_INV_POS                            (2U)
#define SPP_MISC_RG_DVPAS_VS_INV_LEN                            (1U)
#define SPP_MISC_RG_DVPAS_VS_INV_MSK                            (((1U<<SPP_MISC_RG_DVPAS_VS_INV_LEN)-1)<<SPP_MISC_RG_DVPAS_VS_INV_POS)
#define SPP_MISC_RG_DVPAS_VS_INV_UMSK                           (~(((1U<<SPP_MISC_RG_DVPAS_VS_INV_LEN)-1)<<SPP_MISC_RG_DVPAS_VS_INV_POS))
#define SPP_MISC_RG_DVPAS_DA_ORDER                              SPP_MISC_RG_DVPAS_DA_ORDER
#define SPP_MISC_RG_DVPAS_DA_ORDER_POS                          (3U)
#define SPP_MISC_RG_DVPAS_DA_ORDER_LEN                          (1U)
#define SPP_MISC_RG_DVPAS_DA_ORDER_MSK                          (((1U<<SPP_MISC_RG_DVPAS_DA_ORDER_LEN)-1)<<SPP_MISC_RG_DVPAS_DA_ORDER_POS)
#define SPP_MISC_RG_DVPAS_DA_ORDER_UMSK                         (~(((1U<<SPP_MISC_RG_DVPAS_DA_ORDER_LEN)-1)<<SPP_MISC_RG_DVPAS_DA_ORDER_POS))
#define SPP_MISC_RG_DVPAS_FIFO_TH                               SPP_MISC_RG_DVPAS_FIFO_TH
#define SPP_MISC_RG_DVPAS_FIFO_TH_POS                           (16U)
#define SPP_MISC_RG_DVPAS_FIFO_TH_LEN                           (11U)
#define SPP_MISC_RG_DVPAS_FIFO_TH_MSK                           (((1U<<SPP_MISC_RG_DVPAS_FIFO_TH_LEN)-1)<<SPP_MISC_RG_DVPAS_FIFO_TH_POS)
#define SPP_MISC_RG_DVPAS_FIFO_TH_UMSK                          (~(((1U<<SPP_MISC_RG_DVPAS_FIFO_TH_LEN)-1)<<SPP_MISC_RG_DVPAS_FIFO_TH_POS))
#define SPP_MISC_CR_SPP_DE_AS_HSYNC                             SPP_MISC_CR_SPP_DE_AS_HSYNC
#define SPP_MISC_CR_SPP_DE_AS_HSYNC_POS                         (30U)
#define SPP_MISC_CR_SPP_DE_AS_HSYNC_LEN                         (1U)
#define SPP_MISC_CR_SPP_DE_AS_HSYNC_MSK                         (((1U<<SPP_MISC_CR_SPP_DE_AS_HSYNC_LEN)-1)<<SPP_MISC_CR_SPP_DE_AS_HSYNC_POS)
#define SPP_MISC_CR_SPP_DE_AS_HSYNC_UMSK                        (~(((1U<<SPP_MISC_CR_SPP_DE_AS_HSYNC_LEN)-1)<<SPP_MISC_CR_SPP_DE_AS_HSYNC_POS))
#define SPP_MISC_REG_SPP_PCLK_FORCE_ON                          SPP_MISC_REG_SPP_PCLK_FORCE_ON
#define SPP_MISC_REG_SPP_PCLK_FORCE_ON_POS                      (31U)
#define SPP_MISC_REG_SPP_PCLK_FORCE_ON_LEN                      (1U)
#define SPP_MISC_REG_SPP_PCLK_FORCE_ON_MSK                      (((1U<<SPP_MISC_REG_SPP_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_REG_SPP_PCLK_FORCE_ON_POS)
#define SPP_MISC_REG_SPP_PCLK_FORCE_ON_UMSK                     (~(((1U<<SPP_MISC_REG_SPP_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_REG_SPP_PCLK_FORCE_ON_POS))

/* 0x4 : pix_data_ctrl */
#define SPP_MISC_PIX_DATA_CTRL_OFFSET                           (0x4)
#define SPP_MISC_REG_PIX_DATA_CTRL                              SPP_MISC_REG_PIX_DATA_CTRL
#define SPP_MISC_REG_PIX_DATA_CTRL_POS                          (0U)
#define SPP_MISC_REG_PIX_DATA_CTRL_LEN                          (12U)
#define SPP_MISC_REG_PIX_DATA_CTRL_MSK                          (((1U<<SPP_MISC_REG_PIX_DATA_CTRL_LEN)-1)<<SPP_MISC_REG_PIX_DATA_CTRL_POS)
#define SPP_MISC_REG_PIX_DATA_CTRL_UMSK                         (~(((1U<<SPP_MISC_REG_PIX_DATA_CTRL_LEN)-1)<<SPP_MISC_REG_PIX_DATA_CTRL_POS))
#define SPP_MISC_REG_PIX_DATA_SHT_BIT                           SPP_MISC_REG_PIX_DATA_SHT_BIT
#define SPP_MISC_REG_PIX_DATA_SHT_BIT_POS                       (16U)
#define SPP_MISC_REG_PIX_DATA_SHT_BIT_LEN                       (4U)
#define SPP_MISC_REG_PIX_DATA_SHT_BIT_MSK                       (((1U<<SPP_MISC_REG_PIX_DATA_SHT_BIT_LEN)-1)<<SPP_MISC_REG_PIX_DATA_SHT_BIT_POS)
#define SPP_MISC_REG_PIX_DATA_SHT_BIT_UMSK                      (~(((1U<<SPP_MISC_REG_PIX_DATA_SHT_BIT_LEN)-1)<<SPP_MISC_REG_PIX_DATA_SHT_BIT_POS))
#define SPP_MISC_REG_PIX_DATA_SHT_DIR                           SPP_MISC_REG_PIX_DATA_SHT_DIR
#define SPP_MISC_REG_PIX_DATA_SHT_DIR_POS                       (20U)
#define SPP_MISC_REG_PIX_DATA_SHT_DIR_LEN                       (1U)
#define SPP_MISC_REG_PIX_DATA_SHT_DIR_MSK                       (((1U<<SPP_MISC_REG_PIX_DATA_SHT_DIR_LEN)-1)<<SPP_MISC_REG_PIX_DATA_SHT_DIR_POS)
#define SPP_MISC_REG_PIX_DATA_SHT_DIR_UMSK                      (~(((1U<<SPP_MISC_REG_PIX_DATA_SHT_DIR_LEN)-1)<<SPP_MISC_REG_PIX_DATA_SHT_DIR_POS))
#define SPP_MISC_REG_SPP_DTSRC_SRC                              SPP_MISC_REG_SPP_DTSRC_SRC
#define SPP_MISC_REG_SPP_DTSRC_SRC_POS                          (31U)
#define SPP_MISC_REG_SPP_DTSRC_SRC_LEN                          (1U)
#define SPP_MISC_REG_SPP_DTSRC_SRC_MSK                          (((1U<<SPP_MISC_REG_SPP_DTSRC_SRC_LEN)-1)<<SPP_MISC_REG_SPP_DTSRC_SRC_POS)
#define SPP_MISC_REG_SPP_DTSRC_SRC_UMSK                         (~(((1U<<SPP_MISC_REG_SPP_DTSRC_SRC_LEN)-1)<<SPP_MISC_REG_SPP_DTSRC_SRC_POS))

/* 0x8 : dvp2bus_src_sel_1 */
#define SPP_MISC_DVP2BUS_SRC_SEL_1_OFFSET                       (0x8)
#define SPP_MISC_RG_D2B_DVP_SEL_A                               SPP_MISC_RG_D2B_DVP_SEL_A
#define SPP_MISC_RG_D2B_DVP_SEL_A_POS                           (0U)
#define SPP_MISC_RG_D2B_DVP_SEL_A_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_A_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_A_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_A_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_A_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_A_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_A_POS))
#define SPP_MISC_RG_D2X_ID_SEL_A                                SPP_MISC_RG_D2X_ID_SEL_A
#define SPP_MISC_RG_D2X_ID_SEL_A_POS                            (7U)
#define SPP_MISC_RG_D2X_ID_SEL_A_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_A_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_A_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_A_POS)
#define SPP_MISC_RG_D2X_ID_SEL_A_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_A_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_A_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_B                               SPP_MISC_RG_D2B_DVP_SEL_B
#define SPP_MISC_RG_D2B_DVP_SEL_B_POS                           (8U)
#define SPP_MISC_RG_D2B_DVP_SEL_B_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_B_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_B_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_B_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_B_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_B_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_B_POS))
#define SPP_MISC_RG_D2X_ID_SEL_B                                SPP_MISC_RG_D2X_ID_SEL_B
#define SPP_MISC_RG_D2X_ID_SEL_B_POS                            (15U)
#define SPP_MISC_RG_D2X_ID_SEL_B_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_B_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_B_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_B_POS)
#define SPP_MISC_RG_D2X_ID_SEL_B_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_B_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_B_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_C                               SPP_MISC_RG_D2B_DVP_SEL_C
#define SPP_MISC_RG_D2B_DVP_SEL_C_POS                           (16U)
#define SPP_MISC_RG_D2B_DVP_SEL_C_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_C_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_C_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_C_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_C_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_C_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_C_POS))
#define SPP_MISC_RG_D2X_ID_SEL_C                                SPP_MISC_RG_D2X_ID_SEL_C
#define SPP_MISC_RG_D2X_ID_SEL_C_POS                            (23U)
#define SPP_MISC_RG_D2X_ID_SEL_C_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_C_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_C_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_C_POS)
#define SPP_MISC_RG_D2X_ID_SEL_C_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_C_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_C_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_D                               SPP_MISC_RG_D2B_DVP_SEL_D
#define SPP_MISC_RG_D2B_DVP_SEL_D_POS                           (24U)
#define SPP_MISC_RG_D2B_DVP_SEL_D_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_D_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_D_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_D_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_D_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_D_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_D_POS))
#define SPP_MISC_RG_D2X_ID_SEL_D                                SPP_MISC_RG_D2X_ID_SEL_D
#define SPP_MISC_RG_D2X_ID_SEL_D_POS                            (31U)
#define SPP_MISC_RG_D2X_ID_SEL_D_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_D_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_D_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_D_POS)
#define SPP_MISC_RG_D2X_ID_SEL_D_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_D_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_D_POS))

/* 0xC : dvp_frame_m_to_n */
#define SPP_MISC_DVP_FRAME_M_TO_N_OFFSET                        (0xC)
#define SPP_MISC_CR_FRAME_M_TO_N_EN                             SPP_MISC_CR_FRAME_M_TO_N_EN
#define SPP_MISC_CR_FRAME_M_TO_N_EN_POS                         (0U)
#define SPP_MISC_CR_FRAME_M_TO_N_EN_LEN                         (1U)
#define SPP_MISC_CR_FRAME_M_TO_N_EN_MSK                         (((1U<<SPP_MISC_CR_FRAME_M_TO_N_EN_LEN)-1)<<SPP_MISC_CR_FRAME_M_TO_N_EN_POS)
#define SPP_MISC_CR_FRAME_M_TO_N_EN_UMSK                        (~(((1U<<SPP_MISC_CR_FRAME_M_TO_N_EN_LEN)-1)<<SPP_MISC_CR_FRAME_M_TO_N_EN_POS))
#define SPP_MISC_CR_FRAME_INTERVAL                              SPP_MISC_CR_FRAME_INTERVAL
#define SPP_MISC_CR_FRAME_INTERVAL_POS                          (4U)
#define SPP_MISC_CR_FRAME_INTERVAL_LEN                          (4U)
#define SPP_MISC_CR_FRAME_INTERVAL_MSK                          (((1U<<SPP_MISC_CR_FRAME_INTERVAL_LEN)-1)<<SPP_MISC_CR_FRAME_INTERVAL_POS)
#define SPP_MISC_CR_FRAME_INTERVAL_UMSK                         (~(((1U<<SPP_MISC_CR_FRAME_INTERVAL_LEN)-1)<<SPP_MISC_CR_FRAME_INTERVAL_POS))
#define SPP_MISC_CR_FRAME_CNT_N                                 SPP_MISC_CR_FRAME_CNT_N
#define SPP_MISC_CR_FRAME_CNT_N_POS                             (8U)
#define SPP_MISC_CR_FRAME_CNT_N_LEN                             (4U)
#define SPP_MISC_CR_FRAME_CNT_N_MSK                             (((1U<<SPP_MISC_CR_FRAME_CNT_N_LEN)-1)<<SPP_MISC_CR_FRAME_CNT_N_POS)
#define SPP_MISC_CR_FRAME_CNT_N_UMSK                            (~(((1U<<SPP_MISC_CR_FRAME_CNT_N_LEN)-1)<<SPP_MISC_CR_FRAME_CNT_N_POS))
#define SPP_MISC_CR_FRAME_CNT_M                                 SPP_MISC_CR_FRAME_CNT_M
#define SPP_MISC_CR_FRAME_CNT_M_POS                             (12U)
#define SPP_MISC_CR_FRAME_CNT_M_LEN                             (4U)
#define SPP_MISC_CR_FRAME_CNT_M_MSK                             (((1U<<SPP_MISC_CR_FRAME_CNT_M_LEN)-1)<<SPP_MISC_CR_FRAME_CNT_M_POS)
#define SPP_MISC_CR_FRAME_CNT_M_UMSK                            (~(((1U<<SPP_MISC_CR_FRAME_CNT_M_LEN)-1)<<SPP_MISC_CR_FRAME_CNT_M_POS))

/* 0x10 : spp_id_bayer */
#define SPP_MISC_SPP_ID_BAYER_OFFSET                            (0x10)
#define SPP_MISC_REG_BAYER_IDGEN_RST                            SPP_MISC_REG_BAYER_IDGEN_RST
#define SPP_MISC_REG_BAYER_IDGEN_RST_POS                        (0U)
#define SPP_MISC_REG_BAYER_IDGEN_RST_LEN                        (1U)
#define SPP_MISC_REG_BAYER_IDGEN_RST_MSK                        (((1U<<SPP_MISC_REG_BAYER_IDGEN_RST_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_RST_POS)
#define SPP_MISC_REG_BAYER_IDGEN_RST_UMSK                       (~(((1U<<SPP_MISC_REG_BAYER_IDGEN_RST_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_RST_POS))
#define SPP_MISC_REG_BAYER_IDGEN_EDGE                           SPP_MISC_REG_BAYER_IDGEN_EDGE
#define SPP_MISC_REG_BAYER_IDGEN_EDGE_POS                       (1U)
#define SPP_MISC_REG_BAYER_IDGEN_EDGE_LEN                       (1U)
#define SPP_MISC_REG_BAYER_IDGEN_EDGE_MSK                       (((1U<<SPP_MISC_REG_BAYER_IDGEN_EDGE_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_EDGE_POS)
#define SPP_MISC_REG_BAYER_IDGEN_EDGE_UMSK                      (~(((1U<<SPP_MISC_REG_BAYER_IDGEN_EDGE_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_EDGE_POS))
#define SPP_MISC_REG_BAYER_IDGEN_CNT_INCR                       SPP_MISC_REG_BAYER_IDGEN_CNT_INCR
#define SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_POS                   (16U)
#define SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_LEN                   (16U)
#define SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_MSK                   (((1U<<SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_POS)
#define SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_UMSK                  (~(((1U<<SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_LEN)-1)<<SPP_MISC_REG_BAYER_IDGEN_CNT_INCR_POS))

/* 0x14 : dvp2bus_src_sel_2 */
#define SPP_MISC_DVP2BUS_SRC_SEL_2_OFFSET                       (0x14)
#define SPP_MISC_RG_D2B_DVP_SEL_E                               SPP_MISC_RG_D2B_DVP_SEL_E
#define SPP_MISC_RG_D2B_DVP_SEL_E_POS                           (0U)
#define SPP_MISC_RG_D2B_DVP_SEL_E_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_E_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_E_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_E_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_E_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_E_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_E_POS))
#define SPP_MISC_RG_D2X_ID_SEL_E                                SPP_MISC_RG_D2X_ID_SEL_E
#define SPP_MISC_RG_D2X_ID_SEL_E_POS                            (7U)
#define SPP_MISC_RG_D2X_ID_SEL_E_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_E_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_E_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_E_POS)
#define SPP_MISC_RG_D2X_ID_SEL_E_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_E_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_E_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_F                               SPP_MISC_RG_D2B_DVP_SEL_F
#define SPP_MISC_RG_D2B_DVP_SEL_F_POS                           (8U)
#define SPP_MISC_RG_D2B_DVP_SEL_F_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_F_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_F_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_F_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_F_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_F_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_F_POS))
#define SPP_MISC_RG_D2X_ID_SEL_F                                SPP_MISC_RG_D2X_ID_SEL_F
#define SPP_MISC_RG_D2X_ID_SEL_F_POS                            (15U)
#define SPP_MISC_RG_D2X_ID_SEL_F_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_F_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_F_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_F_POS)
#define SPP_MISC_RG_D2X_ID_SEL_F_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_F_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_F_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_G                               SPP_MISC_RG_D2B_DVP_SEL_G
#define SPP_MISC_RG_D2B_DVP_SEL_G_POS                           (16U)
#define SPP_MISC_RG_D2B_DVP_SEL_G_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_G_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_G_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_G_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_G_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_G_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_G_POS))
#define SPP_MISC_RG_D2X_ID_SEL_G                                SPP_MISC_RG_D2X_ID_SEL_G
#define SPP_MISC_RG_D2X_ID_SEL_G_POS                            (23U)
#define SPP_MISC_RG_D2X_ID_SEL_G_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_G_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_G_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_G_POS)
#define SPP_MISC_RG_D2X_ID_SEL_G_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_G_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_G_POS))
#define SPP_MISC_RG_D2B_DVP_SEL_H                               SPP_MISC_RG_D2B_DVP_SEL_H
#define SPP_MISC_RG_D2B_DVP_SEL_H_POS                           (24U)
#define SPP_MISC_RG_D2B_DVP_SEL_H_LEN                           (6U)
#define SPP_MISC_RG_D2B_DVP_SEL_H_MSK                           (((1U<<SPP_MISC_RG_D2B_DVP_SEL_H_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_H_POS)
#define SPP_MISC_RG_D2B_DVP_SEL_H_UMSK                          (~(((1U<<SPP_MISC_RG_D2B_DVP_SEL_H_LEN)-1)<<SPP_MISC_RG_D2B_DVP_SEL_H_POS))
#define SPP_MISC_RG_D2X_ID_SEL_H                                SPP_MISC_RG_D2X_ID_SEL_H
#define SPP_MISC_RG_D2X_ID_SEL_H_POS                            (31U)
#define SPP_MISC_RG_D2X_ID_SEL_H_LEN                            (1U)
#define SPP_MISC_RG_D2X_ID_SEL_H_MSK                            (((1U<<SPP_MISC_RG_D2X_ID_SEL_H_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_H_POS)
#define SPP_MISC_RG_D2X_ID_SEL_H_UMSK                           (~(((1U<<SPP_MISC_RG_D2X_ID_SEL_H_LEN)-1)<<SPP_MISC_RG_D2X_ID_SEL_H_POS))

/* 0x20 : int_clr */
#define SPP_MISC_INT_CLR_OFFSET                                 (0x20)
#define SPP_MISC_RG_RESERVEB_INT_CLR                                 SPP_MISC_RG_RESERVEB_INT_CLR
#define SPP_MISC_RG_RESERVEB_INT_CLR_POS                             (0U)
#define SPP_MISC_RG_RESERVEB_INT_CLR_LEN                             (1U)
#define SPP_MISC_RG_RESERVEB_INT_CLR_MSK                             (((1U<<SPP_MISC_RG_RESERVEB_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB_INT_CLR_POS)
#define SPP_MISC_RG_RESERVEB_INT_CLR_UMSK                            (~(((1U<<SPP_MISC_RG_RESERVEB_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB_INT_CLR_POS))
#define SPP_MISC_RG_RESERVEA_INT_CLR                                  SPP_MISC_RG_RESERVEA_INT_CLR
#define SPP_MISC_RG_RESERVEA_INT_CLR_POS                              (1U)
#define SPP_MISC_RG_RESERVEA_INT_CLR_LEN                              (1U)
#define SPP_MISC_RG_RESERVEA_INT_CLR_MSK                              (((1U<<SPP_MISC_RG_RESERVEA_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEA_INT_CLR_POS)
#define SPP_MISC_RG_RESERVEA_INT_CLR_UMSK                             (~(((1U<<SPP_MISC_RG_RESERVEA_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEA_INT_CLR_POS))
#define SPP_MISC_RG_WR_INT_CLR                                 SPP_MISC_RG_WR_INT_CLR
#define SPP_MISC_RG_WR_INT_CLR_POS                             (2U)
#define SPP_MISC_RG_WR_INT_CLR_LEN                             (1U)
#define SPP_MISC_RG_WR_INT_CLR_MSK                             (((1U<<SPP_MISC_RG_WR_INT_CLR_LEN)-1)<<SPP_MISC_RG_WR_INT_CLR_POS)
#define SPP_MISC_RG_WR_INT_CLR_UMSK                            (~(((1U<<SPP_MISC_RG_WR_INT_CLR_LEN)-1)<<SPP_MISC_RG_WR_INT_CLR_POS))
#define SPP_MISC_RG_RESERVEB2_INT_CLR                                SPP_MISC_RG_RESERVEB2_INT_CLR
#define SPP_MISC_RG_RESERVEB2_INT_CLR_POS                            (3U)
#define SPP_MISC_RG_RESERVEB2_INT_CLR_LEN                            (1U)
#define SPP_MISC_RG_RESERVEB2_INT_CLR_MSK                            (((1U<<SPP_MISC_RG_RESERVEB2_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB2_INT_CLR_POS)
#define SPP_MISC_RG_RESERVEB2_INT_CLR_UMSK                           (~(((1U<<SPP_MISC_RG_RESERVEB2_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB2_INT_CLR_POS))
#define SPP_MISC_RG_OSD_PB_INT_CLR                              SPP_MISC_RG_OSD_PB_INT_CLR
#define SPP_MISC_RG_OSD_PB_INT_CLR_POS                          (4U)
#define SPP_MISC_RG_OSD_PB_INT_CLR_LEN                          (1U)
#define SPP_MISC_RG_OSD_PB_INT_CLR_MSK                          (((1U<<SPP_MISC_RG_OSD_PB_INT_CLR_LEN)-1)<<SPP_MISC_RG_OSD_PB_INT_CLR_POS)
#define SPP_MISC_RG_OSD_PB_INT_CLR_UMSK                         (~(((1U<<SPP_MISC_RG_OSD_PB_INT_CLR_LEN)-1)<<SPP_MISC_RG_OSD_PB_INT_CLR_POS))
#define SPP_MISC_RG_SEOF1_INT_CLR                               SPP_MISC_RG_SEOF1_INT_CLR
#define SPP_MISC_RG_SEOF1_INT_CLR_POS                           (8U)
#define SPP_MISC_RG_SEOF1_INT_CLR_LEN                           (1U)
#define SPP_MISC_RG_SEOF1_INT_CLR_MSK                           (((1U<<SPP_MISC_RG_SEOF1_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_CLR_POS)
#define SPP_MISC_RG_SEOF1_INT_CLR_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF1_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_CLR_POS))
#define SPP_MISC_RG_SEOF2_INT_CLR                               SPP_MISC_RG_SEOF2_INT_CLR
#define SPP_MISC_RG_SEOF2_INT_CLR_POS                           (9U)
#define SPP_MISC_RG_SEOF2_INT_CLR_LEN                           (1U)
#define SPP_MISC_RG_SEOF2_INT_CLR_MSK                           (((1U<<SPP_MISC_RG_SEOF2_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_CLR_POS)
#define SPP_MISC_RG_SEOF2_INT_CLR_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF2_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_CLR_POS))
#define SPP_MISC_RG_SEOF3_INT_CLR                               SPP_MISC_RG_SEOF3_INT_CLR
#define SPP_MISC_RG_SEOF3_INT_CLR_POS                           (10U)
#define SPP_MISC_RG_SEOF3_INT_CLR_LEN                           (1U)
#define SPP_MISC_RG_SEOF3_INT_CLR_MSK                           (((1U<<SPP_MISC_RG_SEOF3_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_CLR_POS)
#define SPP_MISC_RG_SEOF3_INT_CLR_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF3_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_CLR_POS))
#define SPP_MISC_RG_RESERVEA_HIST_INT_CLR                             SPP_MISC_RG_RESERVEA_HIST_INT_CLR
#define SPP_MISC_RG_RESERVEA_HIST_INT_CLR_POS                         (11U)
#define SPP_MISC_RG_RESERVEA_HIST_INT_CLR_LEN                         (1U)
#define SPP_MISC_RG_RESERVEA_HIST_INT_CLR_MSK                         (((1U<<SPP_MISC_RG_RESERVEA_HIST_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEA_HIST_INT_CLR_POS)
#define SPP_MISC_RG_RESERVEA_HIST_INT_CLR_UMSK                        (~(((1U<<SPP_MISC_RG_RESERVEA_HIST_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEA_HIST_INT_CLR_POS))
#define SPP_MISC_RG_RESERVEB3_INT_CLR                                SPP_MISC_RG_RESERVEB3_INT_CLR
#define SPP_MISC_RG_RESERVEB3_INT_CLR_POS                            (12U)
#define SPP_MISC_RG_RESERVEB3_INT_CLR_LEN                            (1U)
#define SPP_MISC_RG_RESERVEB3_INT_CLR_MSK                            (((1U<<SPP_MISC_RG_RESERVEB3_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB3_INT_CLR_POS)
#define SPP_MISC_RG_RESERVEB3_INT_CLR_UMSK                           (~(((1U<<SPP_MISC_RG_RESERVEB3_INT_CLR_LEN)-1)<<SPP_MISC_RG_RESERVEB3_INT_CLR_POS))
#define SPP_MISC_RG_DP_SEOF0_INT_CLR                            SPP_MISC_RG_DP_SEOF0_INT_CLR
#define SPP_MISC_RG_DP_SEOF0_INT_CLR_POS                        (13U)
#define SPP_MISC_RG_DP_SEOF0_INT_CLR_LEN                        (1U)
#define SPP_MISC_RG_DP_SEOF0_INT_CLR_MSK                        (((1U<<SPP_MISC_RG_DP_SEOF0_INT_CLR_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_CLR_POS)
#define SPP_MISC_RG_DP_SEOF0_INT_CLR_UMSK                       (~(((1U<<SPP_MISC_RG_DP_SEOF0_INT_CLR_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_CLR_POS))
#define SPP_MISC_RG_SEOF4_INT_CLR                               SPP_MISC_RG_SEOF4_INT_CLR
#define SPP_MISC_RG_SEOF4_INT_CLR_POS                           (14U)
#define SPP_MISC_RG_SEOF4_INT_CLR_LEN                           (1U)
#define SPP_MISC_RG_SEOF4_INT_CLR_MSK                           (((1U<<SPP_MISC_RG_SEOF4_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_CLR_POS)
#define SPP_MISC_RG_SEOF4_INT_CLR_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF4_INT_CLR_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_CLR_POS))

/* 0x24 : int_ctrl */
#define SPP_MISC_INT_CTRL_OFFSET                                (0x24)
#define SPP_MISC_RG_RESERVEA_INT_MASK                                 SPP_MISC_RG_RESERVEA_INT_MASK
#define SPP_MISC_RG_RESERVEA_INT_MASK_POS                             (0U)
#define SPP_MISC_RG_RESERVEA_INT_MASK_LEN                             (1U)
#define SPP_MISC_RG_RESERVEA_INT_MASK_MSK                             (((1U<<SPP_MISC_RG_RESERVEA_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEA_INT_MASK_POS)
#define SPP_MISC_RG_RESERVEA_INT_MASK_UMSK                            (~(((1U<<SPP_MISC_RG_RESERVEA_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEA_INT_MASK_POS))
#define SPP_MISC_RG_RESERVEB_INT_MASK                                SPP_MISC_RG_RESERVEB_INT_MASK
#define SPP_MISC_RG_RESERVEB_INT_MASK_POS                            (1U)
#define SPP_MISC_RG_RESERVEB_INT_MASK_LEN                            (1U)
#define SPP_MISC_RG_RESERVEB_INT_MASK_MSK                            (((1U<<SPP_MISC_RG_RESERVEB_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB_INT_MASK_POS)
#define SPP_MISC_RG_RESERVEB_INT_MASK_UMSK                           (~(((1U<<SPP_MISC_RG_RESERVEB_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB_INT_MASK_POS))
#define SPP_MISC_RG_WR_INT_MASK                                SPP_MISC_RG_WR_INT_MASK
#define SPP_MISC_RG_WR_INT_MASK_POS                            (2U)
#define SPP_MISC_RG_WR_INT_MASK_LEN                            (1U)
#define SPP_MISC_RG_WR_INT_MASK_MSK                            (((1U<<SPP_MISC_RG_WR_INT_MASK_LEN)-1)<<SPP_MISC_RG_WR_INT_MASK_POS)
#define SPP_MISC_RG_WR_INT_MASK_UMSK                           (~(((1U<<SPP_MISC_RG_WR_INT_MASK_LEN)-1)<<SPP_MISC_RG_WR_INT_MASK_POS))
#define SPP_MISC_RG_RESERVEB2_INT_MASK                               SPP_MISC_RG_RESERVEB2_INT_MASK
#define SPP_MISC_RG_RESERVEB2_INT_MASK_POS                           (3U)
#define SPP_MISC_RG_RESERVEB2_INT_MASK_LEN                           (1U)
#define SPP_MISC_RG_RESERVEB2_INT_MASK_MSK                           (((1U<<SPP_MISC_RG_RESERVEB2_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB2_INT_MASK_POS)
#define SPP_MISC_RG_RESERVEB2_INT_MASK_UMSK                          (~(((1U<<SPP_MISC_RG_RESERVEB2_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB2_INT_MASK_POS))
#define SPP_MISC_RG_OSD_PB_INT_MASK                             SPP_MISC_RG_OSD_PB_INT_MASK
#define SPP_MISC_RG_OSD_PB_INT_MASK_POS                         (4U)
#define SPP_MISC_RG_OSD_PB_INT_MASK_LEN                         (1U)
#define SPP_MISC_RG_OSD_PB_INT_MASK_MSK                         (((1U<<SPP_MISC_RG_OSD_PB_INT_MASK_LEN)-1)<<SPP_MISC_RG_OSD_PB_INT_MASK_POS)
#define SPP_MISC_RG_OSD_PB_INT_MASK_UMSK                        (~(((1U<<SPP_MISC_RG_OSD_PB_INT_MASK_LEN)-1)<<SPP_MISC_RG_OSD_PB_INT_MASK_POS))
#define SPP_MISC_RG_SEOF1_INT_MASK                              SPP_MISC_RG_SEOF1_INT_MASK
#define SPP_MISC_RG_SEOF1_INT_MASK_POS                          (8U)
#define SPP_MISC_RG_SEOF1_INT_MASK_LEN                          (1U)
#define SPP_MISC_RG_SEOF1_INT_MASK_MSK                          (((1U<<SPP_MISC_RG_SEOF1_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_MASK_POS)
#define SPP_MISC_RG_SEOF1_INT_MASK_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF1_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_MASK_POS))
#define SPP_MISC_RG_SEOF1_INT_EDGE                              SPP_MISC_RG_SEOF1_INT_EDGE
#define SPP_MISC_RG_SEOF1_INT_EDGE_POS                          (9U)
#define SPP_MISC_RG_SEOF1_INT_EDGE_LEN                          (1U)
#define SPP_MISC_RG_SEOF1_INT_EDGE_MSK                          (((1U<<SPP_MISC_RG_SEOF1_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_EDGE_POS)
#define SPP_MISC_RG_SEOF1_INT_EDGE_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF1_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_EDGE_POS))
#define SPP_MISC_RG_SEOF1_INT_SRC                               SPP_MISC_RG_SEOF1_INT_SRC
#define SPP_MISC_RG_SEOF1_INT_SRC_POS                           (10U)
#define SPP_MISC_RG_SEOF1_INT_SRC_LEN                           (2U)
#define SPP_MISC_RG_SEOF1_INT_SRC_MSK                           (((1U<<SPP_MISC_RG_SEOF1_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_SRC_POS)
#define SPP_MISC_RG_SEOF1_INT_SRC_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF1_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF1_INT_SRC_POS))
#define SPP_MISC_RG_SEOF2_INT_MASK                              SPP_MISC_RG_SEOF2_INT_MASK
#define SPP_MISC_RG_SEOF2_INT_MASK_POS                          (12U)
#define SPP_MISC_RG_SEOF2_INT_MASK_LEN                          (1U)
#define SPP_MISC_RG_SEOF2_INT_MASK_MSK                          (((1U<<SPP_MISC_RG_SEOF2_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_MASK_POS)
#define SPP_MISC_RG_SEOF2_INT_MASK_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF2_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_MASK_POS))
#define SPP_MISC_RG_SEOF2_INT_EDGE                              SPP_MISC_RG_SEOF2_INT_EDGE
#define SPP_MISC_RG_SEOF2_INT_EDGE_POS                          (13U)
#define SPP_MISC_RG_SEOF2_INT_EDGE_LEN                          (1U)
#define SPP_MISC_RG_SEOF2_INT_EDGE_MSK                          (((1U<<SPP_MISC_RG_SEOF2_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_EDGE_POS)
#define SPP_MISC_RG_SEOF2_INT_EDGE_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF2_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_EDGE_POS))
#define SPP_MISC_RG_SEOF2_INT_SRC                               SPP_MISC_RG_SEOF2_INT_SRC
#define SPP_MISC_RG_SEOF2_INT_SRC_POS                           (14U)
#define SPP_MISC_RG_SEOF2_INT_SRC_LEN                           (2U)
#define SPP_MISC_RG_SEOF2_INT_SRC_MSK                           (((1U<<SPP_MISC_RG_SEOF2_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_SRC_POS)
#define SPP_MISC_RG_SEOF2_INT_SRC_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF2_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF2_INT_SRC_POS))
#define SPP_MISC_RG_SEOF3_INT_MASK                              SPP_MISC_RG_SEOF3_INT_MASK
#define SPP_MISC_RG_SEOF3_INT_MASK_POS                          (16U)
#define SPP_MISC_RG_SEOF3_INT_MASK_LEN                          (1U)
#define SPP_MISC_RG_SEOF3_INT_MASK_MSK                          (((1U<<SPP_MISC_RG_SEOF3_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_MASK_POS)
#define SPP_MISC_RG_SEOF3_INT_MASK_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF3_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_MASK_POS))
#define SPP_MISC_RG_SEOF3_INT_EDGE                              SPP_MISC_RG_SEOF3_INT_EDGE
#define SPP_MISC_RG_SEOF3_INT_EDGE_POS                          (17U)
#define SPP_MISC_RG_SEOF3_INT_EDGE_LEN                          (1U)
#define SPP_MISC_RG_SEOF3_INT_EDGE_MSK                          (((1U<<SPP_MISC_RG_SEOF3_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_EDGE_POS)
#define SPP_MISC_RG_SEOF3_INT_EDGE_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF3_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_EDGE_POS))
#define SPP_MISC_RG_SEOF3_INT_SRC                               SPP_MISC_RG_SEOF3_INT_SRC
#define SPP_MISC_RG_SEOF3_INT_SRC_POS                           (18U)
#define SPP_MISC_RG_SEOF3_INT_SRC_LEN                           (2U)
#define SPP_MISC_RG_SEOF3_INT_SRC_MSK                           (((1U<<SPP_MISC_RG_SEOF3_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_SRC_POS)
#define SPP_MISC_RG_SEOF3_INT_SRC_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF3_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF3_INT_SRC_POS))
#define SPP_MISC_RG_RESERVEA_HIST_INT_MASK                            SPP_MISC_RG_RESERVEA_HIST_INT_MASK
#define SPP_MISC_RG_RESERVEA_HIST_INT_MASK_POS                        (20U)
#define SPP_MISC_RG_RESERVEA_HIST_INT_MASK_LEN                        (1U)
#define SPP_MISC_RG_RESERVEA_HIST_INT_MASK_MSK                        (((1U<<SPP_MISC_RG_RESERVEA_HIST_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEA_HIST_INT_MASK_POS)
#define SPP_MISC_RG_RESERVEA_HIST_INT_MASK_UMSK                       (~(((1U<<SPP_MISC_RG_RESERVEA_HIST_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEA_HIST_INT_MASK_POS))
#define SPP_MISC_RG_RESERVEB3_INT_MASK                               SPP_MISC_RG_RESERVEB3_INT_MASK
#define SPP_MISC_RG_RESERVEB3_INT_MASK_POS                           (21U)
#define SPP_MISC_RG_RESERVEB3_INT_MASK_LEN                           (1U)
#define SPP_MISC_RG_RESERVEB3_INT_MASK_MSK                           (((1U<<SPP_MISC_RG_RESERVEB3_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB3_INT_MASK_POS)
#define SPP_MISC_RG_RESERVEB3_INT_MASK_UMSK                          (~(((1U<<SPP_MISC_RG_RESERVEB3_INT_MASK_LEN)-1)<<SPP_MISC_RG_RESERVEB3_INT_MASK_POS))
#define SPP_MISC_RG_DP_SEOF0_INT_SRC                            SPP_MISC_RG_DP_SEOF0_INT_SRC
#define SPP_MISC_RG_DP_SEOF0_INT_SRC_POS                        (22U)
#define SPP_MISC_RG_DP_SEOF0_INT_SRC_LEN                        (1U)
#define SPP_MISC_RG_DP_SEOF0_INT_SRC_MSK                        (((1U<<SPP_MISC_RG_DP_SEOF0_INT_SRC_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_SRC_POS)
#define SPP_MISC_RG_DP_SEOF0_INT_SRC_UMSK                       (~(((1U<<SPP_MISC_RG_DP_SEOF0_INT_SRC_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_SRC_POS))
#define SPP_MISC_RG_DP_SEOF0_INT_EDGE                           SPP_MISC_RG_DP_SEOF0_INT_EDGE
#define SPP_MISC_RG_DP_SEOF0_INT_EDGE_POS                       (23U)
#define SPP_MISC_RG_DP_SEOF0_INT_EDGE_LEN                       (1U)
#define SPP_MISC_RG_DP_SEOF0_INT_EDGE_MSK                       (((1U<<SPP_MISC_RG_DP_SEOF0_INT_EDGE_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_EDGE_POS)
#define SPP_MISC_RG_DP_SEOF0_INT_EDGE_UMSK                      (~(((1U<<SPP_MISC_RG_DP_SEOF0_INT_EDGE_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_EDGE_POS))
#define SPP_MISC_RG_DP_SEOF0_INT_MASK                           SPP_MISC_RG_DP_SEOF0_INT_MASK
#define SPP_MISC_RG_DP_SEOF0_INT_MASK_POS                       (24U)
#define SPP_MISC_RG_DP_SEOF0_INT_MASK_LEN                       (1U)
#define SPP_MISC_RG_DP_SEOF0_INT_MASK_MSK                       (((1U<<SPP_MISC_RG_DP_SEOF0_INT_MASK_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_MASK_POS)
#define SPP_MISC_RG_DP_SEOF0_INT_MASK_UMSK                      (~(((1U<<SPP_MISC_RG_DP_SEOF0_INT_MASK_LEN)-1)<<SPP_MISC_RG_DP_SEOF0_INT_MASK_POS))
#define SPP_MISC_RG_SEOF4_INT_MASK                              SPP_MISC_RG_SEOF4_INT_MASK
#define SPP_MISC_RG_SEOF4_INT_MASK_POS                          (28U)
#define SPP_MISC_RG_SEOF4_INT_MASK_LEN                          (1U)
#define SPP_MISC_RG_SEOF4_INT_MASK_MSK                          (((1U<<SPP_MISC_RG_SEOF4_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_MASK_POS)
#define SPP_MISC_RG_SEOF4_INT_MASK_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF4_INT_MASK_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_MASK_POS))
#define SPP_MISC_RG_SEOF4_INT_EDGE                              SPP_MISC_RG_SEOF4_INT_EDGE
#define SPP_MISC_RG_SEOF4_INT_EDGE_POS                          (29U)
#define SPP_MISC_RG_SEOF4_INT_EDGE_LEN                          (1U)
#define SPP_MISC_RG_SEOF4_INT_EDGE_MSK                          (((1U<<SPP_MISC_RG_SEOF4_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_EDGE_POS)
#define SPP_MISC_RG_SEOF4_INT_EDGE_UMSK                         (~(((1U<<SPP_MISC_RG_SEOF4_INT_EDGE_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_EDGE_POS))
#define SPP_MISC_RG_SEOF4_INT_SRC                               SPP_MISC_RG_SEOF4_INT_SRC
#define SPP_MISC_RG_SEOF4_INT_SRC_POS                           (30U)
#define SPP_MISC_RG_SEOF4_INT_SRC_LEN                           (2U)
#define SPP_MISC_RG_SEOF4_INT_SRC_MSK                           (((1U<<SPP_MISC_RG_SEOF4_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_SRC_POS)
#define SPP_MISC_RG_SEOF4_INT_SRC_UMSK                          (~(((1U<<SPP_MISC_RG_SEOF4_INT_SRC_LEN)-1)<<SPP_MISC_RG_SEOF4_INT_SRC_POS))

/* 0x28 : spp_id_yuv */
#define SPP_MISC_SPP_ID_YUV_OFFSET                              (0x28)
#define SPP_MISC_REG_YUV_IDGEN_RST                              SPP_MISC_REG_YUV_IDGEN_RST
#define SPP_MISC_REG_YUV_IDGEN_RST_POS                          (0U)
#define SPP_MISC_REG_YUV_IDGEN_RST_LEN                          (1U)
#define SPP_MISC_REG_YUV_IDGEN_RST_MSK                          (((1U<<SPP_MISC_REG_YUV_IDGEN_RST_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_RST_POS)
#define SPP_MISC_REG_YUV_IDGEN_RST_UMSK                         (~(((1U<<SPP_MISC_REG_YUV_IDGEN_RST_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_RST_POS))
#define SPP_MISC_REG_YUV_IDGEN_EDGE                             SPP_MISC_REG_YUV_IDGEN_EDGE
#define SPP_MISC_REG_YUV_IDGEN_EDGE_POS                         (1U)
#define SPP_MISC_REG_YUV_IDGEN_EDGE_LEN                         (1U)
#define SPP_MISC_REG_YUV_IDGEN_EDGE_MSK                         (((1U<<SPP_MISC_REG_YUV_IDGEN_EDGE_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_EDGE_POS)
#define SPP_MISC_REG_YUV_IDGEN_EDGE_UMSK                        (~(((1U<<SPP_MISC_REG_YUV_IDGEN_EDGE_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_EDGE_POS))
#define SPP_MISC_REG_YUV_IDGEN_CNT_INCR                         SPP_MISC_REG_YUV_IDGEN_CNT_INCR
#define SPP_MISC_REG_YUV_IDGEN_CNT_INCR_POS                     (16U)
#define SPP_MISC_REG_YUV_IDGEN_CNT_INCR_LEN                     (16U)
#define SPP_MISC_REG_YUV_IDGEN_CNT_INCR_MSK                     (((1U<<SPP_MISC_REG_YUV_IDGEN_CNT_INCR_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_CNT_INCR_POS)
#define SPP_MISC_REG_YUV_IDGEN_CNT_INCR_UMSK                    (~(((1U<<SPP_MISC_REG_YUV_IDGEN_CNT_INCR_LEN)-1)<<SPP_MISC_REG_YUV_IDGEN_CNT_INCR_POS))

/* 0x2C : dvp_reshape */
#define SPP_MISC_DVP_RESHAPE_OFFSET                             (0x2C)
#define SPP_MISC_REG_RSHP_TGL_COUNT                             SPP_MISC_REG_RSHP_TGL_COUNT
#define SPP_MISC_REG_RSHP_TGL_COUNT_POS                         (0U)
#define SPP_MISC_REG_RSHP_TGL_COUNT_LEN                         (5U)
#define SPP_MISC_REG_RSHP_TGL_COUNT_MSK                         (((1U<<SPP_MISC_REG_RSHP_TGL_COUNT_LEN)-1)<<SPP_MISC_REG_RSHP_TGL_COUNT_POS)
#define SPP_MISC_REG_RSHP_TGL_COUNT_UMSK                        (~(((1U<<SPP_MISC_REG_RSHP_TGL_COUNT_LEN)-1)<<SPP_MISC_REG_RSHP_TGL_COUNT_POS))
#define SPP_MISC_REG_RSHP_HSYNC_INV                             SPP_MISC_REG_RSHP_HSYNC_INV
#define SPP_MISC_REG_RSHP_HSYNC_INV_POS                         (5U)
#define SPP_MISC_REG_RSHP_HSYNC_INV_LEN                         (1U)
#define SPP_MISC_REG_RSHP_HSYNC_INV_MSK                         (((1U<<SPP_MISC_REG_RSHP_HSYNC_INV_LEN)-1)<<SPP_MISC_REG_RSHP_HSYNC_INV_POS)
#define SPP_MISC_REG_RSHP_HSYNC_INV_UMSK                        (~(((1U<<SPP_MISC_REG_RSHP_HSYNC_INV_LEN)-1)<<SPP_MISC_REG_RSHP_HSYNC_INV_POS))
#define SPP_MISC_REG_RSHP_VSYNC_INV                             SPP_MISC_REG_RSHP_VSYNC_INV
#define SPP_MISC_REG_RSHP_VSYNC_INV_POS                         (6U)
#define SPP_MISC_REG_RSHP_VSYNC_INV_LEN                         (1U)
#define SPP_MISC_REG_RSHP_VSYNC_INV_MSK                         (((1U<<SPP_MISC_REG_RSHP_VSYNC_INV_LEN)-1)<<SPP_MISC_REG_RSHP_VSYNC_INV_POS)
#define SPP_MISC_REG_RSHP_VSYNC_INV_UMSK                        (~(((1U<<SPP_MISC_REG_RSHP_VSYNC_INV_LEN)-1)<<SPP_MISC_REG_RSHP_VSYNC_INV_POS))
#define SPP_MISC_REG_RSHP_CLR                                   SPP_MISC_REG_RSHP_CLR
#define SPP_MISC_REG_RSHP_CLR_POS                               (7U)
#define SPP_MISC_REG_RSHP_CLR_LEN                               (1U)
#define SPP_MISC_REG_RSHP_CLR_MSK                               (((1U<<SPP_MISC_REG_RSHP_CLR_LEN)-1)<<SPP_MISC_REG_RSHP_CLR_POS)
#define SPP_MISC_REG_RSHP_CLR_UMSK                              (~(((1U<<SPP_MISC_REG_RSHP_CLR_LEN)-1)<<SPP_MISC_REG_RSHP_CLR_POS))
#define SPP_MISC_REG_RSHP_EN                                    SPP_MISC_REG_RSHP_EN
#define SPP_MISC_REG_RSHP_EN_POS                                (8U)
#define SPP_MISC_REG_RSHP_EN_LEN                                (1U)
#define SPP_MISC_REG_RSHP_EN_MSK                                (((1U<<SPP_MISC_REG_RSHP_EN_LEN)-1)<<SPP_MISC_REG_RSHP_EN_POS)
#define SPP_MISC_REG_RSHP_EN_UMSK                               (~(((1U<<SPP_MISC_REG_RSHP_EN_LEN)-1)<<SPP_MISC_REG_RSHP_EN_POS))

/* 0x40 : scalerA_i_size */
#define SPP_MISC_SCALERA_I_SIZE_OFFSET                          (0x40)
#define SPP_MISC_RG_SCALERA_I_W                                 SPP_MISC_RG_SCALERA_I_W
#define SPP_MISC_RG_SCALERA_I_W_POS                             (0U)
#define SPP_MISC_RG_SCALERA_I_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERA_I_W_MSK                             (((1U<<SPP_MISC_RG_SCALERA_I_W_LEN)-1)<<SPP_MISC_RG_SCALERA_I_W_POS)
#define SPP_MISC_RG_SCALERA_I_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERA_I_W_LEN)-1)<<SPP_MISC_RG_SCALERA_I_W_POS))
#define SPP_MISC_RG_SCALERA_I_H                                 SPP_MISC_RG_SCALERA_I_H
#define SPP_MISC_RG_SCALERA_I_H_POS                             (16U)
#define SPP_MISC_RG_SCALERA_I_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERA_I_H_MSK                             (((1U<<SPP_MISC_RG_SCALERA_I_H_LEN)-1)<<SPP_MISC_RG_SCALERA_I_H_POS)
#define SPP_MISC_RG_SCALERA_I_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERA_I_H_LEN)-1)<<SPP_MISC_RG_SCALERA_I_H_POS))
#define SPP_MISC_RG_SCLRA_SW_SH                                 SPP_MISC_RG_SCLRA_SW_SH
#define SPP_MISC_RG_SCLRA_SW_SH_POS                             (27U)
#define SPP_MISC_RG_SCLRA_SW_SH_LEN                             (1U)
#define SPP_MISC_RG_SCLRA_SW_SH_MSK                             (((1U<<SPP_MISC_RG_SCLRA_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRA_SW_SH_POS)
#define SPP_MISC_RG_SCLRA_SW_SH_UMSK                            (~(((1U<<SPP_MISC_RG_SCLRA_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRA_SW_SH_POS))
#define SPP_MISC_RG_SCALERA_BYPASS                              SPP_MISC_RG_SCALERA_BYPASS
#define SPP_MISC_RG_SCALERA_BYPASS_POS                          (28U)
#define SPP_MISC_RG_SCALERA_BYPASS_LEN                          (1U)
#define SPP_MISC_RG_SCALERA_BYPASS_MSK                          (((1U<<SPP_MISC_RG_SCALERA_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERA_BYPASS_POS)
#define SPP_MISC_RG_SCALERA_BYPASS_UMSK                         (~(((1U<<SPP_MISC_RG_SCALERA_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERA_BYPASS_POS))
#define SPP_MISC_RG_SCALERA_SEL                                 SPP_MISC_RG_SCALERA_SEL
#define SPP_MISC_RG_SCALERA_SEL_POS                             (29U)
#define SPP_MISC_RG_SCALERA_SEL_LEN                             (3U)
#define SPP_MISC_RG_SCALERA_SEL_MSK                             (((1U<<SPP_MISC_RG_SCALERA_SEL_LEN)-1)<<SPP_MISC_RG_SCALERA_SEL_POS)
#define SPP_MISC_RG_SCALERA_SEL_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERA_SEL_LEN)-1)<<SPP_MISC_RG_SCALERA_SEL_POS))

/* 0x44 : scalerA_o_size */
#define SPP_MISC_SCALERA_O_SIZE_OFFSET                          (0x44)
#define SPP_MISC_RG_SCALERA_O_W                                 SPP_MISC_RG_SCALERA_O_W
#define SPP_MISC_RG_SCALERA_O_W_POS                             (0U)
#define SPP_MISC_RG_SCALERA_O_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERA_O_W_MSK                             (((1U<<SPP_MISC_RG_SCALERA_O_W_LEN)-1)<<SPP_MISC_RG_SCALERA_O_W_POS)
#define SPP_MISC_RG_SCALERA_O_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERA_O_W_LEN)-1)<<SPP_MISC_RG_SCALERA_O_W_POS))
#define SPP_MISC_RG_SCALERA_O_H                                 SPP_MISC_RG_SCALERA_O_H
#define SPP_MISC_RG_SCALERA_O_H_POS                             (16U)
#define SPP_MISC_RG_SCALERA_O_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERA_O_H_MSK                             (((1U<<SPP_MISC_RG_SCALERA_O_H_LEN)-1)<<SPP_MISC_RG_SCALERA_O_H_POS)
#define SPP_MISC_RG_SCALERA_O_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERA_O_H_LEN)-1)<<SPP_MISC_RG_SCALERA_O_H_POS))

/* 0x48 : scalerB_i_size */
#define SPP_MISC_SCALERB_I_SIZE_OFFSET                          (0x48)
#define SPP_MISC_RG_SCALERB_I_W                                 SPP_MISC_RG_SCALERB_I_W
#define SPP_MISC_RG_SCALERB_I_W_POS                             (0U)
#define SPP_MISC_RG_SCALERB_I_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERB_I_W_MSK                             (((1U<<SPP_MISC_RG_SCALERB_I_W_LEN)-1)<<SPP_MISC_RG_SCALERB_I_W_POS)
#define SPP_MISC_RG_SCALERB_I_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERB_I_W_LEN)-1)<<SPP_MISC_RG_SCALERB_I_W_POS))
#define SPP_MISC_RG_SCALERB_I_H                                 SPP_MISC_RG_SCALERB_I_H
#define SPP_MISC_RG_SCALERB_I_H_POS                             (16U)
#define SPP_MISC_RG_SCALERB_I_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERB_I_H_MSK                             (((1U<<SPP_MISC_RG_SCALERB_I_H_LEN)-1)<<SPP_MISC_RG_SCALERB_I_H_POS)
#define SPP_MISC_RG_SCALERB_I_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERB_I_H_LEN)-1)<<SPP_MISC_RG_SCALERB_I_H_POS))
#define SPP_MISC_RG_SCLRB_SW_SH                                 SPP_MISC_RG_SCLRB_SW_SH
#define SPP_MISC_RG_SCLRB_SW_SH_POS                             (27U)
#define SPP_MISC_RG_SCLRB_SW_SH_LEN                             (1U)
#define SPP_MISC_RG_SCLRB_SW_SH_MSK                             (((1U<<SPP_MISC_RG_SCLRB_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRB_SW_SH_POS)
#define SPP_MISC_RG_SCLRB_SW_SH_UMSK                            (~(((1U<<SPP_MISC_RG_SCLRB_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRB_SW_SH_POS))
#define SPP_MISC_RG_SCALERB_BYPASS                              SPP_MISC_RG_SCALERB_BYPASS
#define SPP_MISC_RG_SCALERB_BYPASS_POS                          (28U)
#define SPP_MISC_RG_SCALERB_BYPASS_LEN                          (1U)
#define SPP_MISC_RG_SCALERB_BYPASS_MSK                          (((1U<<SPP_MISC_RG_SCALERB_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERB_BYPASS_POS)
#define SPP_MISC_RG_SCALERB_BYPASS_UMSK                         (~(((1U<<SPP_MISC_RG_SCALERB_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERB_BYPASS_POS))
#define SPP_MISC_RG_SCALERB_SEL                                 SPP_MISC_RG_SCALERB_SEL
#define SPP_MISC_RG_SCALERB_SEL_POS                             (29U)
#define SPP_MISC_RG_SCALERB_SEL_LEN                             (3U)
#define SPP_MISC_RG_SCALERB_SEL_MSK                             (((1U<<SPP_MISC_RG_SCALERB_SEL_LEN)-1)<<SPP_MISC_RG_SCALERB_SEL_POS)
#define SPP_MISC_RG_SCALERB_SEL_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERB_SEL_LEN)-1)<<SPP_MISC_RG_SCALERB_SEL_POS))

/* 0x4C : scalerB_o_size */
#define SPP_MISC_SCALERB_O_SIZE_OFFSET                          (0x4C)
#define SPP_MISC_RG_SCALERB_O_W                                 SPP_MISC_RG_SCALERB_O_W
#define SPP_MISC_RG_SCALERB_O_W_POS                             (0U)
#define SPP_MISC_RG_SCALERB_O_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERB_O_W_MSK                             (((1U<<SPP_MISC_RG_SCALERB_O_W_LEN)-1)<<SPP_MISC_RG_SCALERB_O_W_POS)
#define SPP_MISC_RG_SCALERB_O_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERB_O_W_LEN)-1)<<SPP_MISC_RG_SCALERB_O_W_POS))
#define SPP_MISC_RG_SCALERB_O_H                                 SPP_MISC_RG_SCALERB_O_H
#define SPP_MISC_RG_SCALERB_O_H_POS                             (16U)
#define SPP_MISC_RG_SCALERB_O_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERB_O_H_MSK                             (((1U<<SPP_MISC_RG_SCALERB_O_H_LEN)-1)<<SPP_MISC_RG_SCALERB_O_H_POS)
#define SPP_MISC_RG_SCALERB_O_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERB_O_H_LEN)-1)<<SPP_MISC_RG_SCALERB_O_H_POS))

/* 0x50 : scalerC_i_size */
#define SPP_MISC_SCALERC_I_SIZE_OFFSET                          (0x50)
#define SPP_MISC_RG_SCALERC_I_W                                 SPP_MISC_RG_SCALERC_I_W
#define SPP_MISC_RG_SCALERC_I_W_POS                             (0U)
#define SPP_MISC_RG_SCALERC_I_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERC_I_W_MSK                             (((1U<<SPP_MISC_RG_SCALERC_I_W_LEN)-1)<<SPP_MISC_RG_SCALERC_I_W_POS)
#define SPP_MISC_RG_SCALERC_I_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERC_I_W_LEN)-1)<<SPP_MISC_RG_SCALERC_I_W_POS))
#define SPP_MISC_RG_SCALERC_I_H                                 SPP_MISC_RG_SCALERC_I_H
#define SPP_MISC_RG_SCALERC_I_H_POS                             (16U)
#define SPP_MISC_RG_SCALERC_I_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERC_I_H_MSK                             (((1U<<SPP_MISC_RG_SCALERC_I_H_LEN)-1)<<SPP_MISC_RG_SCALERC_I_H_POS)
#define SPP_MISC_RG_SCALERC_I_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERC_I_H_LEN)-1)<<SPP_MISC_RG_SCALERC_I_H_POS))
#define SPP_MISC_RG_SCLRC_SW_SH                                 SPP_MISC_RG_SCLRC_SW_SH
#define SPP_MISC_RG_SCLRC_SW_SH_POS                             (27U)
#define SPP_MISC_RG_SCLRC_SW_SH_LEN                             (1U)
#define SPP_MISC_RG_SCLRC_SW_SH_MSK                             (((1U<<SPP_MISC_RG_SCLRC_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRC_SW_SH_POS)
#define SPP_MISC_RG_SCLRC_SW_SH_UMSK                            (~(((1U<<SPP_MISC_RG_SCLRC_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRC_SW_SH_POS))
#define SPP_MISC_RG_SCALERC_BYPASS                              SPP_MISC_RG_SCALERC_BYPASS
#define SPP_MISC_RG_SCALERC_BYPASS_POS                          (28U)
#define SPP_MISC_RG_SCALERC_BYPASS_LEN                          (1U)
#define SPP_MISC_RG_SCALERC_BYPASS_MSK                          (((1U<<SPP_MISC_RG_SCALERC_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERC_BYPASS_POS)
#define SPP_MISC_RG_SCALERC_BYPASS_UMSK                         (~(((1U<<SPP_MISC_RG_SCALERC_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERC_BYPASS_POS))
#define SPP_MISC_RG_SCALERC_SEL                                 SPP_MISC_RG_SCALERC_SEL
#define SPP_MISC_RG_SCALERC_SEL_POS                             (29U)
#define SPP_MISC_RG_SCALERC_SEL_LEN                             (3U)
#define SPP_MISC_RG_SCALERC_SEL_MSK                             (((1U<<SPP_MISC_RG_SCALERC_SEL_LEN)-1)<<SPP_MISC_RG_SCALERC_SEL_POS)
#define SPP_MISC_RG_SCALERC_SEL_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERC_SEL_LEN)-1)<<SPP_MISC_RG_SCALERC_SEL_POS))

/* 0x54 : scalerC_o_size */
#define SPP_MISC_SCALERC_O_SIZE_OFFSET                          (0x54)
#define SPP_MISC_RG_SCALERC_O_W                                 SPP_MISC_RG_SCALERC_O_W
#define SPP_MISC_RG_SCALERC_O_W_POS                             (0U)
#define SPP_MISC_RG_SCALERC_O_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERC_O_W_MSK                             (((1U<<SPP_MISC_RG_SCALERC_O_W_LEN)-1)<<SPP_MISC_RG_SCALERC_O_W_POS)
#define SPP_MISC_RG_SCALERC_O_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERC_O_W_LEN)-1)<<SPP_MISC_RG_SCALERC_O_W_POS))
#define SPP_MISC_RG_SCALERC_O_H                                 SPP_MISC_RG_SCALERC_O_H
#define SPP_MISC_RG_SCALERC_O_H_POS                             (16U)
#define SPP_MISC_RG_SCALERC_O_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERC_O_H_MSK                             (((1U<<SPP_MISC_RG_SCALERC_O_H_LEN)-1)<<SPP_MISC_RG_SCALERC_O_H_POS)
#define SPP_MISC_RG_SCALERC_O_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERC_O_H_LEN)-1)<<SPP_MISC_RG_SCALERC_O_H_POS))

/* 0x58 : scalerD_i_size */
#define SPP_MISC_SCALERD_I_SIZE_OFFSET                          (0x58)
#define SPP_MISC_RG_SCALERD_I_W                                 SPP_MISC_RG_SCALERD_I_W
#define SPP_MISC_RG_SCALERD_I_W_POS                             (0U)
#define SPP_MISC_RG_SCALERD_I_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERD_I_W_MSK                             (((1U<<SPP_MISC_RG_SCALERD_I_W_LEN)-1)<<SPP_MISC_RG_SCALERD_I_W_POS)
#define SPP_MISC_RG_SCALERD_I_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERD_I_W_LEN)-1)<<SPP_MISC_RG_SCALERD_I_W_POS))
#define SPP_MISC_RG_SCALERD_I_H                                 SPP_MISC_RG_SCALERD_I_H
#define SPP_MISC_RG_SCALERD_I_H_POS                             (16U)
#define SPP_MISC_RG_SCALERD_I_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERD_I_H_MSK                             (((1U<<SPP_MISC_RG_SCALERD_I_H_LEN)-1)<<SPP_MISC_RG_SCALERD_I_H_POS)
#define SPP_MISC_RG_SCALERD_I_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERD_I_H_LEN)-1)<<SPP_MISC_RG_SCALERD_I_H_POS))
#define SPP_MISC_RG_SCLRD_SW_SH                                 SPP_MISC_RG_SCLRD_SW_SH
#define SPP_MISC_RG_SCLRD_SW_SH_POS                             (27U)
#define SPP_MISC_RG_SCLRD_SW_SH_LEN                             (1U)
#define SPP_MISC_RG_SCLRD_SW_SH_MSK                             (((1U<<SPP_MISC_RG_SCLRD_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRD_SW_SH_POS)
#define SPP_MISC_RG_SCLRD_SW_SH_UMSK                            (~(((1U<<SPP_MISC_RG_SCLRD_SW_SH_LEN)-1)<<SPP_MISC_RG_SCLRD_SW_SH_POS))
#define SPP_MISC_RG_SCALERD_BYPASS                              SPP_MISC_RG_SCALERD_BYPASS
#define SPP_MISC_RG_SCALERD_BYPASS_POS                          (28U)
#define SPP_MISC_RG_SCALERD_BYPASS_LEN                          (1U)
#define SPP_MISC_RG_SCALERD_BYPASS_MSK                          (((1U<<SPP_MISC_RG_SCALERD_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERD_BYPASS_POS)
#define SPP_MISC_RG_SCALERD_BYPASS_UMSK                         (~(((1U<<SPP_MISC_RG_SCALERD_BYPASS_LEN)-1)<<SPP_MISC_RG_SCALERD_BYPASS_POS))
#define SPP_MISC_RG_SCALERD_SEL                                 SPP_MISC_RG_SCALERD_SEL
#define SPP_MISC_RG_SCALERD_SEL_POS                             (29U)
#define SPP_MISC_RG_SCALERD_SEL_LEN                             (3U)
#define SPP_MISC_RG_SCALERD_SEL_MSK                             (((1U<<SPP_MISC_RG_SCALERD_SEL_LEN)-1)<<SPP_MISC_RG_SCALERD_SEL_POS)
#define SPP_MISC_RG_SCALERD_SEL_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERD_SEL_LEN)-1)<<SPP_MISC_RG_SCALERD_SEL_POS))

/* 0x5C : scalerD_o_size */
#define SPP_MISC_SCALERD_O_SIZE_OFFSET                          (0x5C)
#define SPP_MISC_RG_SCALERD_O_W                                 SPP_MISC_RG_SCALERD_O_W
#define SPP_MISC_RG_SCALERD_O_W_POS                             (0U)
#define SPP_MISC_RG_SCALERD_O_W_LEN                             (11U)
#define SPP_MISC_RG_SCALERD_O_W_MSK                             (((1U<<SPP_MISC_RG_SCALERD_O_W_LEN)-1)<<SPP_MISC_RG_SCALERD_O_W_POS)
#define SPP_MISC_RG_SCALERD_O_W_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERD_O_W_LEN)-1)<<SPP_MISC_RG_SCALERD_O_W_POS))
#define SPP_MISC_RG_SCALERD_O_H                                 SPP_MISC_RG_SCALERD_O_H
#define SPP_MISC_RG_SCALERD_O_H_POS                             (16U)
#define SPP_MISC_RG_SCALERD_O_H_LEN                             (11U)
#define SPP_MISC_RG_SCALERD_O_H_MSK                             (((1U<<SPP_MISC_RG_SCALERD_O_H_LEN)-1)<<SPP_MISC_RG_SCALERD_O_H_POS)
#define SPP_MISC_RG_SCALERD_O_H_UMSK                            (~(((1U<<SPP_MISC_RG_SCALERD_O_H_LEN)-1)<<SPP_MISC_RG_SCALERD_O_H_POS))

/* 0x60 : disp_config */
#define SPP_MISC_DISP_CONFIG_OFFSET                             (0x60)
#define SPP_MISC_RG_DISP_BT656_EN                               SPP_MISC_RG_DISP_BT656_EN
#define SPP_MISC_RG_DISP_BT656_EN_POS                           (4U)
#define SPP_MISC_RG_DISP_BT656_EN_LEN                           (1U)
#define SPP_MISC_RG_DISP_BT656_EN_MSK                           (((1U<<SPP_MISC_RG_DISP_BT656_EN_LEN)-1)<<SPP_MISC_RG_DISP_BT656_EN_POS)
#define SPP_MISC_RG_DISP_BT656_EN_UMSK                          (~(((1U<<SPP_MISC_RG_DISP_BT656_EN_LEN)-1)<<SPP_MISC_RG_DISP_BT656_EN_POS))
#define SPP_MISC_RG_DISP_BT1120_EN                              SPP_MISC_RG_DISP_BT1120_EN
#define SPP_MISC_RG_DISP_BT1120_EN_POS                          (5U)
#define SPP_MISC_RG_DISP_BT1120_EN_LEN                          (1U)
#define SPP_MISC_RG_DISP_BT1120_EN_MSK                          (((1U<<SPP_MISC_RG_DISP_BT1120_EN_LEN)-1)<<SPP_MISC_RG_DISP_BT1120_EN_POS)
#define SPP_MISC_RG_DISP_BT1120_EN_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_BT1120_EN_LEN)-1)<<SPP_MISC_RG_DISP_BT1120_EN_POS))
#define SPP_MISC_RG_DISP_DPI_EN                                 SPP_MISC_RG_DISP_DPI_EN
#define SPP_MISC_RG_DISP_DPI_EN_POS                             (6U)
#define SPP_MISC_RG_DISP_DPI_EN_LEN                             (1U)
#define SPP_MISC_RG_DISP_DPI_EN_MSK                             (((1U<<SPP_MISC_RG_DISP_DPI_EN_LEN)-1)<<SPP_MISC_RG_DISP_DPI_EN_POS)
#define SPP_MISC_RG_DISP_DPI_EN_UMSK                            (~(((1U<<SPP_MISC_RG_DISP_DPI_EN_LEN)-1)<<SPP_MISC_RG_DISP_DPI_EN_POS))
#define SPP_MISC_RG_DISP_HDMI_EN                                SPP_MISC_RG_DISP_HDMI_EN
#define SPP_MISC_RG_DISP_HDMI_EN_POS                            (7U)
#define SPP_MISC_RG_DISP_HDMI_EN_LEN                            (1U)
#define SPP_MISC_RG_DISP_HDMI_EN_MSK                            (((1U<<SPP_MISC_RG_DISP_HDMI_EN_LEN)-1)<<SPP_MISC_RG_DISP_HDMI_EN_POS)
#define SPP_MISC_RG_DISP_HDMI_EN_UMSK                           (~(((1U<<SPP_MISC_RG_DISP_HDMI_EN_LEN)-1)<<SPP_MISC_RG_DISP_HDMI_EN_POS))
#define SPP_MISC_RG_DISP_MUX_SEL                                SPP_MISC_RG_DISP_MUX_SEL
#define SPP_MISC_RG_DISP_MUX_SEL_POS                            (8U)
#define SPP_MISC_RG_DISP_MUX_SEL_LEN                            (2U)
#define SPP_MISC_RG_DISP_MUX_SEL_MSK                            (((1U<<SPP_MISC_RG_DISP_MUX_SEL_LEN)-1)<<SPP_MISC_RG_DISP_MUX_SEL_POS)
#define SPP_MISC_RG_DISP_MUX_SEL_UMSK                           (~(((1U<<SPP_MISC_RG_DISP_MUX_SEL_LEN)-1)<<SPP_MISC_RG_DISP_MUX_SEL_POS))
#define SPP_MISC_RG_OSDDP_SEL                                   SPP_MISC_RG_OSDDP_SEL
#define SPP_MISC_RG_OSDDP_SEL_POS                               (12U)
#define SPP_MISC_RG_OSDDP_SEL_LEN                               (2U)
#define SPP_MISC_RG_OSDDP_SEL_MSK                               (((1U<<SPP_MISC_RG_OSDDP_SEL_LEN)-1)<<SPP_MISC_RG_OSDDP_SEL_POS)
#define SPP_MISC_RG_OSDDP_SEL_UMSK                              (~(((1U<<SPP_MISC_RG_OSDDP_SEL_LEN)-1)<<SPP_MISC_RG_OSDDP_SEL_POS))
#define SPP_MISC_RG_DISP_CLKO_INV                               SPP_MISC_RG_DISP_CLKO_INV
#define SPP_MISC_RG_DISP_CLKO_INV_POS                           (31U)
#define SPP_MISC_RG_DISP_CLKO_INV_LEN                           (1U)
#define SPP_MISC_RG_DISP_CLKO_INV_MSK                           (((1U<<SPP_MISC_RG_DISP_CLKO_INV_LEN)-1)<<SPP_MISC_RG_DISP_CLKO_INV_POS)
#define SPP_MISC_RG_DISP_CLKO_INV_UMSK                          (~(((1U<<SPP_MISC_RG_DISP_CLKO_INV_LEN)-1)<<SPP_MISC_RG_DISP_CLKO_INV_POS))

/* 0x64 : disp_dpi_config */
#define SPP_MISC_DISP_DPI_CONFIG_OFFSET                         (0x64)
#define SPP_MISC_RG_DISP_DPI_HS_W                               SPP_MISC_RG_DISP_DPI_HS_W
#define SPP_MISC_RG_DISP_DPI_HS_W_POS                           (0U)
#define SPP_MISC_RG_DISP_DPI_HS_W_LEN                           (8U)
#define SPP_MISC_RG_DISP_DPI_HS_W_MSK                           (((1U<<SPP_MISC_RG_DISP_DPI_HS_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_HS_W_POS)
#define SPP_MISC_RG_DISP_DPI_HS_W_UMSK                          (~(((1U<<SPP_MISC_RG_DISP_DPI_HS_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_HS_W_POS))
#define SPP_MISC_RG_DISP_DPI_HFP_W                              SPP_MISC_RG_DISP_DPI_HFP_W
#define SPP_MISC_RG_DISP_DPI_HFP_W_POS                          (8U)
#define SPP_MISC_RG_DISP_DPI_HFP_W_LEN                          (8U)
#define SPP_MISC_RG_DISP_DPI_HFP_W_MSK                          (((1U<<SPP_MISC_RG_DISP_DPI_HFP_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_HFP_W_POS)
#define SPP_MISC_RG_DISP_DPI_HFP_W_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_DPI_HFP_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_HFP_W_POS))
#define SPP_MISC_RG_DISP_DPI_VS_W                               SPP_MISC_RG_DISP_DPI_VS_W
#define SPP_MISC_RG_DISP_DPI_VS_W_POS                           (16U)
#define SPP_MISC_RG_DISP_DPI_VS_W_LEN                           (8U)
#define SPP_MISC_RG_DISP_DPI_VS_W_MSK                           (((1U<<SPP_MISC_RG_DISP_DPI_VS_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_VS_W_POS)
#define SPP_MISC_RG_DISP_DPI_VS_W_UMSK                          (~(((1U<<SPP_MISC_RG_DISP_DPI_VS_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_VS_W_POS))
#define SPP_MISC_RG_DISP_DPI_VFP_W                              SPP_MISC_RG_DISP_DPI_VFP_W
#define SPP_MISC_RG_DISP_DPI_VFP_W_POS                          (24U)
#define SPP_MISC_RG_DISP_DPI_VFP_W_LEN                          (8U)
#define SPP_MISC_RG_DISP_DPI_VFP_W_MSK                          (((1U<<SPP_MISC_RG_DISP_DPI_VFP_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_VFP_W_POS)
#define SPP_MISC_RG_DISP_DPI_VFP_W_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_DPI_VFP_W_LEN)-1)<<SPP_MISC_RG_DISP_DPI_VFP_W_POS))

/* 0x68 : disp_yuv_rgb_config_0 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_0_OFFSET                   (0x68)
#define SPP_MISC_RG_DISP_Y2R_PRE_0                              SPP_MISC_RG_DISP_Y2R_PRE_0
#define SPP_MISC_RG_DISP_Y2R_PRE_0_POS                          (0U)
#define SPP_MISC_RG_DISP_Y2R_PRE_0_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_PRE_0_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_PRE_0_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_0_POS)
#define SPP_MISC_RG_DISP_Y2R_PRE_0_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_PRE_0_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_0_POS))
#define SPP_MISC_RG_DISP_Y2R_PRE_1                              SPP_MISC_RG_DISP_Y2R_PRE_1
#define SPP_MISC_RG_DISP_Y2R_PRE_1_POS                          (10U)
#define SPP_MISC_RG_DISP_Y2R_PRE_1_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_PRE_1_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_PRE_1_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_1_POS)
#define SPP_MISC_RG_DISP_Y2R_PRE_1_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_PRE_1_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_1_POS))
#define SPP_MISC_RG_DISP_Y2R_PRE_2                              SPP_MISC_RG_DISP_Y2R_PRE_2
#define SPP_MISC_RG_DISP_Y2R_PRE_2_POS                          (20U)
#define SPP_MISC_RG_DISP_Y2R_PRE_2_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_PRE_2_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_PRE_2_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_2_POS)
#define SPP_MISC_RG_DISP_Y2R_PRE_2_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_PRE_2_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_PRE_2_POS))
#define SPP_MISC_RG_DISP_Y2R_EN                                 SPP_MISC_RG_DISP_Y2R_EN
#define SPP_MISC_RG_DISP_Y2R_EN_POS                             (31U)
#define SPP_MISC_RG_DISP_Y2R_EN_LEN                             (1U)
#define SPP_MISC_RG_DISP_Y2R_EN_MSK                             (((1U<<SPP_MISC_RG_DISP_Y2R_EN_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_EN_POS)
#define SPP_MISC_RG_DISP_Y2R_EN_UMSK                            (~(((1U<<SPP_MISC_RG_DISP_Y2R_EN_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_EN_POS))

/* 0x6C : disp_yuv_rgb_config_1 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_1_OFFSET                   (0x6C)
#define SPP_MISC_RG_DISP_Y2R_POS_0                              SPP_MISC_RG_DISP_Y2R_POS_0
#define SPP_MISC_RG_DISP_Y2R_POS_0_POS                          (0U)
#define SPP_MISC_RG_DISP_Y2R_POS_0_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_POS_0_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_POS_0_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_0_POS)
#define SPP_MISC_RG_DISP_Y2R_POS_0_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_POS_0_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_0_POS))
#define SPP_MISC_RG_DISP_Y2R_POS_1                              SPP_MISC_RG_DISP_Y2R_POS_1
#define SPP_MISC_RG_DISP_Y2R_POS_1_POS                          (10U)
#define SPP_MISC_RG_DISP_Y2R_POS_1_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_POS_1_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_POS_1_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_1_POS)
#define SPP_MISC_RG_DISP_Y2R_POS_1_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_POS_1_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_1_POS))
#define SPP_MISC_RG_DISP_Y2R_POS_2                              SPP_MISC_RG_DISP_Y2R_POS_2
#define SPP_MISC_RG_DISP_Y2R_POS_2_POS                          (20U)
#define SPP_MISC_RG_DISP_Y2R_POS_2_LEN                          (9U)
#define SPP_MISC_RG_DISP_Y2R_POS_2_MSK                          (((1U<<SPP_MISC_RG_DISP_Y2R_POS_2_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_2_POS)
#define SPP_MISC_RG_DISP_Y2R_POS_2_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_Y2R_POS_2_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_POS_2_POS))

/* 0x70 : disp_yuv_rgb_config_2 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_2_OFFSET                   (0x70)
#define SPP_MISC_RG_DISP_Y2R_MTX_00                             SPP_MISC_RG_DISP_Y2R_MTX_00
#define SPP_MISC_RG_DISP_Y2R_MTX_00_POS                         (0U)
#define SPP_MISC_RG_DISP_Y2R_MTX_00_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_00_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_00_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_00_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_00_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_00_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_00_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_01                             SPP_MISC_RG_DISP_Y2R_MTX_01
#define SPP_MISC_RG_DISP_Y2R_MTX_01_POS                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_01_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_01_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_01_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_01_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_01_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_01_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_01_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_02_L                           SPP_MISC_RG_DISP_Y2R_MTX_02_L
#define SPP_MISC_RG_DISP_Y2R_MTX_02_L_POS                       (24U)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_L_LEN                       (8U)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_L_MSK                       (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_02_L_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_02_L_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_L_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_02_L_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_02_L_POS))

/* 0x74 : disp_yuv_rgb_config_3 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_3_OFFSET                   (0x74)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_U                           SPP_MISC_RG_DISP_Y2R_MTX_02_U
#define SPP_MISC_RG_DISP_Y2R_MTX_02_U_POS                       (0U)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_U_LEN                       (4U)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_U_MSK                       (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_02_U_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_02_U_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_02_U_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_02_U_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_02_U_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_10                             SPP_MISC_RG_DISP_Y2R_MTX_10
#define SPP_MISC_RG_DISP_Y2R_MTX_10_POS                         (4U)
#define SPP_MISC_RG_DISP_Y2R_MTX_10_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_10_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_10_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_10_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_10_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_10_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_10_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_11                             SPP_MISC_RG_DISP_Y2R_MTX_11
#define SPP_MISC_RG_DISP_Y2R_MTX_11_POS                         (16U)
#define SPP_MISC_RG_DISP_Y2R_MTX_11_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_11_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_11_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_11_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_11_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_11_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_11_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_12_L                           SPP_MISC_RG_DISP_Y2R_MTX_12_L
#define SPP_MISC_RG_DISP_Y2R_MTX_12_L_POS                       (28U)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_L_LEN                       (4U)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_L_MSK                       (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_12_L_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_12_L_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_L_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_12_L_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_12_L_POS))

/* 0x78 : disp_yuv_rgb_config_4 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_4_OFFSET                   (0x78)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_U                           SPP_MISC_RG_DISP_Y2R_MTX_12_U
#define SPP_MISC_RG_DISP_Y2R_MTX_12_U_POS                       (0U)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_U_LEN                       (8U)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_U_MSK                       (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_12_U_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_12_U_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_12_U_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_12_U_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_12_U_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_20                             SPP_MISC_RG_DISP_Y2R_MTX_20
#define SPP_MISC_RG_DISP_Y2R_MTX_20_POS                         (8U)
#define SPP_MISC_RG_DISP_Y2R_MTX_20_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_20_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_20_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_20_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_20_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_20_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_20_POS))
#define SPP_MISC_RG_DISP_Y2R_MTX_21                             SPP_MISC_RG_DISP_Y2R_MTX_21
#define SPP_MISC_RG_DISP_Y2R_MTX_21_POS                         (20U)
#define SPP_MISC_RG_DISP_Y2R_MTX_21_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_21_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_21_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_21_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_21_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_21_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_21_POS))

/* 0x7C : disp_yuv_rgb_config_5 */
#define SPP_MISC_DISP_YUV_RGB_CONFIG_5_OFFSET                   (0x7C)
#define SPP_MISC_RG_DISP_Y2R_MTX_22                             SPP_MISC_RG_DISP_Y2R_MTX_22
#define SPP_MISC_RG_DISP_Y2R_MTX_22_POS                         (0U)
#define SPP_MISC_RG_DISP_Y2R_MTX_22_LEN                         (12U)
#define SPP_MISC_RG_DISP_Y2R_MTX_22_MSK                         (((1U<<SPP_MISC_RG_DISP_Y2R_MTX_22_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_22_POS)
#define SPP_MISC_RG_DISP_Y2R_MTX_22_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_Y2R_MTX_22_LEN)-1)<<SPP_MISC_RG_DISP_Y2R_MTX_22_POS))

/* 0x80 : spp_subsys_bus_ctrl */
#define SPP_MISC_SPP_SUBSYS_BUS_CTRL_OFFSET                     (0x80)
#define SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON                       SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON
#define SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_POS                   (0U)
#define SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_LEN                   (16U)
#define SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_MSK                   (((1U<<SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_POS)
#define SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_UMSK                  (~(((1U<<SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_RG_SPP_SUB_PCLK_FORCE_ON_POS))
#define SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON                      SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON
#define SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_POS                  (16U)
#define SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_LEN                  (16U)
#define SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_MSK                  (((1U<<SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_POS)
#define SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_UMSK                 (~(((1U<<SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_LEN)-1)<<SPP_MISC_RG_SPP_PERI_PCLK_FORCE_ON_POS))

/* 0xA0 : osdA_i_ctrl */
#define SPP_MISC_OSDA_I_CTRL_OFFSET                             (0xA0)
#define SPP_MISC_RG_OSD_PB_SEL                                  SPP_MISC_RG_OSD_PB_SEL
#define SPP_MISC_RG_OSD_PB_SEL_POS                              (0U)
#define SPP_MISC_RG_OSD_PB_SEL_LEN                              (1U)
#define SPP_MISC_RG_OSD_PB_SEL_MSK                              (((1U<<SPP_MISC_RG_OSD_PB_SEL_LEN)-1)<<SPP_MISC_RG_OSD_PB_SEL_POS)
#define SPP_MISC_RG_OSD_PB_SEL_UMSK                             (~(((1U<<SPP_MISC_RG_OSD_PB_SEL_LEN)-1)<<SPP_MISC_RG_OSD_PB_SEL_POS))
#define SPP_MISC_RG_OSDA_SEL                                    SPP_MISC_RG_OSDA_SEL
#define SPP_MISC_RG_OSDA_SEL_POS                                (29U)
#define SPP_MISC_RG_OSDA_SEL_LEN                                (3U)
#define SPP_MISC_RG_OSDA_SEL_MSK                                (((1U<<SPP_MISC_RG_OSDA_SEL_LEN)-1)<<SPP_MISC_RG_OSDA_SEL_POS)
#define SPP_MISC_RG_OSDA_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_OSDA_SEL_LEN)-1)<<SPP_MISC_RG_OSDA_SEL_POS))

/* 0xA4 : osdB_i_ctrl */
#define SPP_MISC_OSDB_I_CTRL_OFFSET                             (0xA4)
#define SPP_MISC_RG_OSDB_SEL                                    SPP_MISC_RG_OSDB_SEL
#define SPP_MISC_RG_OSDB_SEL_POS                                (29U)
#define SPP_MISC_RG_OSDB_SEL_LEN                                (3U)
#define SPP_MISC_RG_OSDB_SEL_MSK                                (((1U<<SPP_MISC_RG_OSDB_SEL_LEN)-1)<<SPP_MISC_RG_OSDB_SEL_POS)
#define SPP_MISC_RG_OSDB_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_OSDB_SEL_LEN)-1)<<SPP_MISC_RG_OSDB_SEL_POS))

/* 0xA8 : osdC_i_ctrl */
#define SPP_MISC_OSDC_I_CTRL_OFFSET                             (0xA8)
#define SPP_MISC_RG_OSDC_SEL                                    SPP_MISC_RG_OSDC_SEL
#define SPP_MISC_RG_OSDC_SEL_POS                                (29U)
#define SPP_MISC_RG_OSDC_SEL_LEN                                (3U)
#define SPP_MISC_RG_OSDC_SEL_MSK                                (((1U<<SPP_MISC_RG_OSDC_SEL_LEN)-1)<<SPP_MISC_RG_OSDC_SEL_POS)
#define SPP_MISC_RG_OSDC_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_OSDC_SEL_LEN)-1)<<SPP_MISC_RG_OSDC_SEL_POS))

/* 0xAC : osdD_i_ctrl */
#define SPP_MISC_OSDD_I_CTRL_OFFSET                             (0xAC)
#define SPP_MISC_RG_OSDD_SEL                                    SPP_MISC_RG_OSDD_SEL
#define SPP_MISC_RG_OSDD_SEL_POS                                (29U)
#define SPP_MISC_RG_OSDD_SEL_LEN                                (3U)
#define SPP_MISC_RG_OSDD_SEL_MSK                                (((1U<<SPP_MISC_RG_OSDD_SEL_LEN)-1)<<SPP_MISC_RG_OSDD_SEL_POS)
#define SPP_MISC_RG_OSDD_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_OSDD_SEL_LEN)-1)<<SPP_MISC_RG_OSDD_SEL_POS))

/* 0xC0 : spp_subsys_dbg_sel */
#define SPP_MISC_SPP_SUBSYS_DBG_SEL_OFFSET                      (0xC0)
#define SPP_MISC_REG_SPP_SUB_DBG_EN                             SPP_MISC_REG_SPP_SUB_DBG_EN
#define SPP_MISC_REG_SPP_SUB_DBG_EN_POS                         (0U)
#define SPP_MISC_REG_SPP_SUB_DBG_EN_LEN                         (1U)
#define SPP_MISC_REG_SPP_SUB_DBG_EN_MSK                         (((1U<<SPP_MISC_REG_SPP_SUB_DBG_EN_LEN)-1)<<SPP_MISC_REG_SPP_SUB_DBG_EN_POS)
#define SPP_MISC_REG_SPP_SUB_DBG_EN_UMSK                        (~(((1U<<SPP_MISC_REG_SPP_SUB_DBG_EN_LEN)-1)<<SPP_MISC_REG_SPP_SUB_DBG_EN_POS))
#define SPP_MISC_REG_SPP_SUB_DBG_SEL                            SPP_MISC_REG_SPP_SUB_DBG_SEL
#define SPP_MISC_REG_SPP_SUB_DBG_SEL_POS                        (4U)
#define SPP_MISC_REG_SPP_SUB_DBG_SEL_LEN                        (4U)
#define SPP_MISC_REG_SPP_SUB_DBG_SEL_MSK                        (((1U<<SPP_MISC_REG_SPP_SUB_DBG_SEL_LEN)-1)<<SPP_MISC_REG_SPP_SUB_DBG_SEL_POS)
#define SPP_MISC_REG_SPP_SUB_DBG_SEL_UMSK                       (~(((1U<<SPP_MISC_REG_SPP_SUB_DBG_SEL_LEN)-1)<<SPP_MISC_REG_SPP_SUB_DBG_SEL_POS))

/* 0xFC : SPP_MISC_Dummy */
#define SPP_MISC_DUMMY_OFFSET                                   (0xFC)
#define SPP_MISC_DUMMY_REG                                      SPP_MISC_DUMMY_REG
#define SPP_MISC_DUMMY_REG_POS                                  (0U)
#define SPP_MISC_DUMMY_REG_LEN                                  (32U)
#define SPP_MISC_DUMMY_REG_MSK                                  (((1U<<SPP_MISC_DUMMY_REG_LEN)-1)<<SPP_MISC_DUMMY_REG_POS)
#define SPP_MISC_DUMMY_REG_UMSK                                 (~(((1U<<SPP_MISC_DUMMY_REG_LEN)-1)<<SPP_MISC_DUMMY_REG_POS))

/* 0x100 : adjA_ctrl_0 */
#define SPP_MISC_ADJA_CTRL_0_OFFSET                             (0x100)
#define SPP_MISC_REG_ADJA_ADJ_EB                                SPP_MISC_REG_ADJA_ADJ_EB
#define SPP_MISC_REG_ADJA_ADJ_EB_POS                            (0U)
#define SPP_MISC_REG_ADJA_ADJ_EB_LEN                            (1U)
#define SPP_MISC_REG_ADJA_ADJ_EB_MSK                            (((1U<<SPP_MISC_REG_ADJA_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJA_ADJ_EB_POS)
#define SPP_MISC_REG_ADJA_ADJ_EB_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJA_ADJ_EB_POS))
#define SPP_MISC_REG_ADJA_Y_LUMA                                SPP_MISC_REG_ADJA_Y_LUMA
#define SPP_MISC_REG_ADJA_Y_LUMA_POS                            (1U)
#define SPP_MISC_REG_ADJA_Y_LUMA_LEN                            (9U)
#define SPP_MISC_REG_ADJA_Y_LUMA_MSK                            (((1U<<SPP_MISC_REG_ADJA_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJA_Y_LUMA_POS)
#define SPP_MISC_REG_ADJA_Y_LUMA_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJA_Y_LUMA_POS))
#define SPP_MISC_REG_ADJA_Y_MUL0                                SPP_MISC_REG_ADJA_Y_MUL0
#define SPP_MISC_REG_ADJA_Y_MUL0_POS                            (10U)
#define SPP_MISC_REG_ADJA_Y_MUL0_LEN                            (11U)
#define SPP_MISC_REG_ADJA_Y_MUL0_MSK                            (((1U<<SPP_MISC_REG_ADJA_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MUL0_POS)
#define SPP_MISC_REG_ADJA_Y_MUL0_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MUL0_POS))
#define SPP_MISC_REG_ADJA_Y_MUL1                                SPP_MISC_REG_ADJA_Y_MUL1
#define SPP_MISC_REG_ADJA_Y_MUL1_POS                            (21U)
#define SPP_MISC_REG_ADJA_Y_MUL1_LEN                            (11U)
#define SPP_MISC_REG_ADJA_Y_MUL1_MSK                            (((1U<<SPP_MISC_REG_ADJA_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MUL1_POS)
#define SPP_MISC_REG_ADJA_Y_MUL1_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MUL1_POS))

/* 0x104 : adjA_ctrl_1 */
#define SPP_MISC_ADJA_CTRL_1_OFFSET                             (0x104)
#define SPP_MISC_REG_ADJA_Y_MIN                                 SPP_MISC_REG_ADJA_Y_MIN
#define SPP_MISC_REG_ADJA_Y_MIN_POS                             (0U)
#define SPP_MISC_REG_ADJA_Y_MIN_LEN                             (8U)
#define SPP_MISC_REG_ADJA_Y_MIN_MSK                             (((1U<<SPP_MISC_REG_ADJA_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MIN_POS)
#define SPP_MISC_REG_ADJA_Y_MIN_UMSK                            (~(((1U<<SPP_MISC_REG_ADJA_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MIN_POS))
#define SPP_MISC_REG_ADJA_Y_MAX                                 SPP_MISC_REG_ADJA_Y_MAX
#define SPP_MISC_REG_ADJA_Y_MAX_POS                             (8U)
#define SPP_MISC_REG_ADJA_Y_MAX_LEN                             (8U)
#define SPP_MISC_REG_ADJA_Y_MAX_MSK                             (((1U<<SPP_MISC_REG_ADJA_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MAX_POS)
#define SPP_MISC_REG_ADJA_Y_MAX_UMSK                            (~(((1U<<SPP_MISC_REG_ADJA_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJA_Y_MAX_POS))
#define SPP_MISC_REG_ADJA_UV_MIN                                SPP_MISC_REG_ADJA_UV_MIN
#define SPP_MISC_REG_ADJA_UV_MIN_POS                            (16U)
#define SPP_MISC_REG_ADJA_UV_MIN_LEN                            (8U)
#define SPP_MISC_REG_ADJA_UV_MIN_MSK                            (((1U<<SPP_MISC_REG_ADJA_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MIN_POS)
#define SPP_MISC_REG_ADJA_UV_MIN_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MIN_POS))
#define SPP_MISC_REG_ADJA_UV_MAX                                SPP_MISC_REG_ADJA_UV_MAX
#define SPP_MISC_REG_ADJA_UV_MAX_POS                            (24U)
#define SPP_MISC_REG_ADJA_UV_MAX_LEN                            (8U)
#define SPP_MISC_REG_ADJA_UV_MAX_MSK                            (((1U<<SPP_MISC_REG_ADJA_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MAX_POS)
#define SPP_MISC_REG_ADJA_UV_MAX_UMSK                           (~(((1U<<SPP_MISC_REG_ADJA_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MAX_POS))

/* 0x108 : adjA_ctrl_2 */
#define SPP_MISC_ADJA_CTRL_2_OFFSET                             (0x108)
#define SPP_MISC_RG_ADJA_SEL                                    SPP_MISC_RG_ADJA_SEL
#define SPP_MISC_RG_ADJA_SEL_POS                                (0U)
#define SPP_MISC_RG_ADJA_SEL_LEN                                (4U)
#define SPP_MISC_RG_ADJA_SEL_MSK                                (((1U<<SPP_MISC_RG_ADJA_SEL_LEN)-1)<<SPP_MISC_RG_ADJA_SEL_POS)
#define SPP_MISC_RG_ADJA_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_ADJA_SEL_LEN)-1)<<SPP_MISC_RG_ADJA_SEL_POS))
#define SPP_MISC_REG_ADJA_UV_MUL0                               SPP_MISC_REG_ADJA_UV_MUL0
#define SPP_MISC_REG_ADJA_UV_MUL0_POS                           (10U)
#define SPP_MISC_REG_ADJA_UV_MUL0_LEN                           (11U)
#define SPP_MISC_REG_ADJA_UV_MUL0_MSK                           (((1U<<SPP_MISC_REG_ADJA_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MUL0_POS)
#define SPP_MISC_REG_ADJA_UV_MUL0_UMSK                          (~(((1U<<SPP_MISC_REG_ADJA_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MUL0_POS))
#define SPP_MISC_REG_ADJA_UV_MUL1                               SPP_MISC_REG_ADJA_UV_MUL1
#define SPP_MISC_REG_ADJA_UV_MUL1_POS                           (21U)
#define SPP_MISC_REG_ADJA_UV_MUL1_LEN                           (11U)
#define SPP_MISC_REG_ADJA_UV_MUL1_MSK                           (((1U<<SPP_MISC_REG_ADJA_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MUL1_POS)
#define SPP_MISC_REG_ADJA_UV_MUL1_UMSK                          (~(((1U<<SPP_MISC_REG_ADJA_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJA_UV_MUL1_POS))

/* 0x110 : adjB_ctrl_0 */
#define SPP_MISC_ADJB_CTRL_0_OFFSET                             (0x110)
#define SPP_MISC_REG_ADJB_ADJ_EB                                SPP_MISC_REG_ADJB_ADJ_EB
#define SPP_MISC_REG_ADJB_ADJ_EB_POS                            (0U)
#define SPP_MISC_REG_ADJB_ADJ_EB_LEN                            (1U)
#define SPP_MISC_REG_ADJB_ADJ_EB_MSK                            (((1U<<SPP_MISC_REG_ADJB_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJB_ADJ_EB_POS)
#define SPP_MISC_REG_ADJB_ADJ_EB_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJB_ADJ_EB_POS))
#define SPP_MISC_REG_ADJB_Y_LUMA                                SPP_MISC_REG_ADJB_Y_LUMA
#define SPP_MISC_REG_ADJB_Y_LUMA_POS                            (1U)
#define SPP_MISC_REG_ADJB_Y_LUMA_LEN                            (9U)
#define SPP_MISC_REG_ADJB_Y_LUMA_MSK                            (((1U<<SPP_MISC_REG_ADJB_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJB_Y_LUMA_POS)
#define SPP_MISC_REG_ADJB_Y_LUMA_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJB_Y_LUMA_POS))
#define SPP_MISC_REG_ADJB_Y_MUL0                                SPP_MISC_REG_ADJB_Y_MUL0
#define SPP_MISC_REG_ADJB_Y_MUL0_POS                            (10U)
#define SPP_MISC_REG_ADJB_Y_MUL0_LEN                            (11U)
#define SPP_MISC_REG_ADJB_Y_MUL0_MSK                            (((1U<<SPP_MISC_REG_ADJB_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MUL0_POS)
#define SPP_MISC_REG_ADJB_Y_MUL0_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MUL0_POS))
#define SPP_MISC_REG_ADJB_Y_MUL1                                SPP_MISC_REG_ADJB_Y_MUL1
#define SPP_MISC_REG_ADJB_Y_MUL1_POS                            (21U)
#define SPP_MISC_REG_ADJB_Y_MUL1_LEN                            (11U)
#define SPP_MISC_REG_ADJB_Y_MUL1_MSK                            (((1U<<SPP_MISC_REG_ADJB_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MUL1_POS)
#define SPP_MISC_REG_ADJB_Y_MUL1_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MUL1_POS))

/* 0x114 : adjB_ctrl_1 */
#define SPP_MISC_ADJB_CTRL_1_OFFSET                             (0x114)
#define SPP_MISC_REG_ADJB_Y_MIN                                 SPP_MISC_REG_ADJB_Y_MIN
#define SPP_MISC_REG_ADJB_Y_MIN_POS                             (0U)
#define SPP_MISC_REG_ADJB_Y_MIN_LEN                             (8U)
#define SPP_MISC_REG_ADJB_Y_MIN_MSK                             (((1U<<SPP_MISC_REG_ADJB_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MIN_POS)
#define SPP_MISC_REG_ADJB_Y_MIN_UMSK                            (~(((1U<<SPP_MISC_REG_ADJB_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MIN_POS))
#define SPP_MISC_REG_ADJB_Y_MAX                                 SPP_MISC_REG_ADJB_Y_MAX
#define SPP_MISC_REG_ADJB_Y_MAX_POS                             (8U)
#define SPP_MISC_REG_ADJB_Y_MAX_LEN                             (8U)
#define SPP_MISC_REG_ADJB_Y_MAX_MSK                             (((1U<<SPP_MISC_REG_ADJB_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MAX_POS)
#define SPP_MISC_REG_ADJB_Y_MAX_UMSK                            (~(((1U<<SPP_MISC_REG_ADJB_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJB_Y_MAX_POS))
#define SPP_MISC_REG_ADJB_UV_MIN                                SPP_MISC_REG_ADJB_UV_MIN
#define SPP_MISC_REG_ADJB_UV_MIN_POS                            (16U)
#define SPP_MISC_REG_ADJB_UV_MIN_LEN                            (8U)
#define SPP_MISC_REG_ADJB_UV_MIN_MSK                            (((1U<<SPP_MISC_REG_ADJB_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MIN_POS)
#define SPP_MISC_REG_ADJB_UV_MIN_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MIN_POS))
#define SPP_MISC_REG_ADJB_UV_MAX                                SPP_MISC_REG_ADJB_UV_MAX
#define SPP_MISC_REG_ADJB_UV_MAX_POS                            (24U)
#define SPP_MISC_REG_ADJB_UV_MAX_LEN                            (8U)
#define SPP_MISC_REG_ADJB_UV_MAX_MSK                            (((1U<<SPP_MISC_REG_ADJB_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MAX_POS)
#define SPP_MISC_REG_ADJB_UV_MAX_UMSK                           (~(((1U<<SPP_MISC_REG_ADJB_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MAX_POS))

/* 0x118 : adjB_ctrl_2 */
#define SPP_MISC_ADJB_CTRL_2_OFFSET                             (0x118)
#define SPP_MISC_RG_ADJB_SEL                                    SPP_MISC_RG_ADJB_SEL
#define SPP_MISC_RG_ADJB_SEL_POS                                (0U)
#define SPP_MISC_RG_ADJB_SEL_LEN                                (4U)
#define SPP_MISC_RG_ADJB_SEL_MSK                                (((1U<<SPP_MISC_RG_ADJB_SEL_LEN)-1)<<SPP_MISC_RG_ADJB_SEL_POS)
#define SPP_MISC_RG_ADJB_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_ADJB_SEL_LEN)-1)<<SPP_MISC_RG_ADJB_SEL_POS))
#define SPP_MISC_REG_ADJB_UV_MUL0                               SPP_MISC_REG_ADJB_UV_MUL0
#define SPP_MISC_REG_ADJB_UV_MUL0_POS                           (10U)
#define SPP_MISC_REG_ADJB_UV_MUL0_LEN                           (11U)
#define SPP_MISC_REG_ADJB_UV_MUL0_MSK                           (((1U<<SPP_MISC_REG_ADJB_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MUL0_POS)
#define SPP_MISC_REG_ADJB_UV_MUL0_UMSK                          (~(((1U<<SPP_MISC_REG_ADJB_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MUL0_POS))
#define SPP_MISC_REG_ADJB_UV_MUL1                               SPP_MISC_REG_ADJB_UV_MUL1
#define SPP_MISC_REG_ADJB_UV_MUL1_POS                           (21U)
#define SPP_MISC_REG_ADJB_UV_MUL1_LEN                           (11U)
#define SPP_MISC_REG_ADJB_UV_MUL1_MSK                           (((1U<<SPP_MISC_REG_ADJB_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MUL1_POS)
#define SPP_MISC_REG_ADJB_UV_MUL1_UMSK                          (~(((1U<<SPP_MISC_REG_ADJB_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJB_UV_MUL1_POS))

/* 0x120 : adjC_ctrl_0 */
#define SPP_MISC_ADJC_CTRL_0_OFFSET                             (0x120)
#define SPP_MISC_REG_ADJC_ADJ_EB                                SPP_MISC_REG_ADJC_ADJ_EB
#define SPP_MISC_REG_ADJC_ADJ_EB_POS                            (0U)
#define SPP_MISC_REG_ADJC_ADJ_EB_LEN                            (1U)
#define SPP_MISC_REG_ADJC_ADJ_EB_MSK                            (((1U<<SPP_MISC_REG_ADJC_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJC_ADJ_EB_POS)
#define SPP_MISC_REG_ADJC_ADJ_EB_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJC_ADJ_EB_POS))
#define SPP_MISC_REG_ADJC_Y_LUMA                                SPP_MISC_REG_ADJC_Y_LUMA
#define SPP_MISC_REG_ADJC_Y_LUMA_POS                            (1U)
#define SPP_MISC_REG_ADJC_Y_LUMA_LEN                            (9U)
#define SPP_MISC_REG_ADJC_Y_LUMA_MSK                            (((1U<<SPP_MISC_REG_ADJC_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJC_Y_LUMA_POS)
#define SPP_MISC_REG_ADJC_Y_LUMA_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJC_Y_LUMA_POS))
#define SPP_MISC_REG_ADJC_Y_MUL0                                SPP_MISC_REG_ADJC_Y_MUL0
#define SPP_MISC_REG_ADJC_Y_MUL0_POS                            (10U)
#define SPP_MISC_REG_ADJC_Y_MUL0_LEN                            (11U)
#define SPP_MISC_REG_ADJC_Y_MUL0_MSK                            (((1U<<SPP_MISC_REG_ADJC_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MUL0_POS)
#define SPP_MISC_REG_ADJC_Y_MUL0_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MUL0_POS))
#define SPP_MISC_REG_ADJC_Y_MUL1                                SPP_MISC_REG_ADJC_Y_MUL1
#define SPP_MISC_REG_ADJC_Y_MUL1_POS                            (21U)
#define SPP_MISC_REG_ADJC_Y_MUL1_LEN                            (11U)
#define SPP_MISC_REG_ADJC_Y_MUL1_MSK                            (((1U<<SPP_MISC_REG_ADJC_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MUL1_POS)
#define SPP_MISC_REG_ADJC_Y_MUL1_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MUL1_POS))

/* 0x124 : adjC_ctrl_1 */
#define SPP_MISC_ADJC_CTRL_1_OFFSET                             (0x124)
#define SPP_MISC_REG_ADJC_Y_MIN                                 SPP_MISC_REG_ADJC_Y_MIN
#define SPP_MISC_REG_ADJC_Y_MIN_POS                             (0U)
#define SPP_MISC_REG_ADJC_Y_MIN_LEN                             (8U)
#define SPP_MISC_REG_ADJC_Y_MIN_MSK                             (((1U<<SPP_MISC_REG_ADJC_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MIN_POS)
#define SPP_MISC_REG_ADJC_Y_MIN_UMSK                            (~(((1U<<SPP_MISC_REG_ADJC_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MIN_POS))
#define SPP_MISC_REG_ADJC_Y_MAX                                 SPP_MISC_REG_ADJC_Y_MAX
#define SPP_MISC_REG_ADJC_Y_MAX_POS                             (8U)
#define SPP_MISC_REG_ADJC_Y_MAX_LEN                             (8U)
#define SPP_MISC_REG_ADJC_Y_MAX_MSK                             (((1U<<SPP_MISC_REG_ADJC_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MAX_POS)
#define SPP_MISC_REG_ADJC_Y_MAX_UMSK                            (~(((1U<<SPP_MISC_REG_ADJC_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJC_Y_MAX_POS))
#define SPP_MISC_REG_ADJC_UV_MIN                                SPP_MISC_REG_ADJC_UV_MIN
#define SPP_MISC_REG_ADJC_UV_MIN_POS                            (16U)
#define SPP_MISC_REG_ADJC_UV_MIN_LEN                            (8U)
#define SPP_MISC_REG_ADJC_UV_MIN_MSK                            (((1U<<SPP_MISC_REG_ADJC_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MIN_POS)
#define SPP_MISC_REG_ADJC_UV_MIN_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MIN_POS))
#define SPP_MISC_REG_ADJC_UV_MAX                                SPP_MISC_REG_ADJC_UV_MAX
#define SPP_MISC_REG_ADJC_UV_MAX_POS                            (24U)
#define SPP_MISC_REG_ADJC_UV_MAX_LEN                            (8U)
#define SPP_MISC_REG_ADJC_UV_MAX_MSK                            (((1U<<SPP_MISC_REG_ADJC_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MAX_POS)
#define SPP_MISC_REG_ADJC_UV_MAX_UMSK                           (~(((1U<<SPP_MISC_REG_ADJC_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MAX_POS))

/* 0x128 : adjC_ctrl_2 */
#define SPP_MISC_ADJC_CTRL_2_OFFSET                             (0x128)
#define SPP_MISC_RG_ADJC_SEL                                    SPP_MISC_RG_ADJC_SEL
#define SPP_MISC_RG_ADJC_SEL_POS                                (0U)
#define SPP_MISC_RG_ADJC_SEL_LEN                                (4U)
#define SPP_MISC_RG_ADJC_SEL_MSK                                (((1U<<SPP_MISC_RG_ADJC_SEL_LEN)-1)<<SPP_MISC_RG_ADJC_SEL_POS)
#define SPP_MISC_RG_ADJC_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_ADJC_SEL_LEN)-1)<<SPP_MISC_RG_ADJC_SEL_POS))
#define SPP_MISC_REG_ADJC_UV_MUL0                               SPP_MISC_REG_ADJC_UV_MUL0
#define SPP_MISC_REG_ADJC_UV_MUL0_POS                           (10U)
#define SPP_MISC_REG_ADJC_UV_MUL0_LEN                           (11U)
#define SPP_MISC_REG_ADJC_UV_MUL0_MSK                           (((1U<<SPP_MISC_REG_ADJC_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MUL0_POS)
#define SPP_MISC_REG_ADJC_UV_MUL0_UMSK                          (~(((1U<<SPP_MISC_REG_ADJC_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MUL0_POS))
#define SPP_MISC_REG_ADJC_UV_MUL1                               SPP_MISC_REG_ADJC_UV_MUL1
#define SPP_MISC_REG_ADJC_UV_MUL1_POS                           (21U)
#define SPP_MISC_REG_ADJC_UV_MUL1_LEN                           (11U)
#define SPP_MISC_REG_ADJC_UV_MUL1_MSK                           (((1U<<SPP_MISC_REG_ADJC_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MUL1_POS)
#define SPP_MISC_REG_ADJC_UV_MUL1_UMSK                          (~(((1U<<SPP_MISC_REG_ADJC_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJC_UV_MUL1_POS))

/* 0x130 : adjD_ctrl_0 */
#define SPP_MISC_ADJD_CTRL_0_OFFSET                             (0x130)
#define SPP_MISC_REG_ADJD_ADJ_EB                                SPP_MISC_REG_ADJD_ADJ_EB
#define SPP_MISC_REG_ADJD_ADJ_EB_POS                            (0U)
#define SPP_MISC_REG_ADJD_ADJ_EB_LEN                            (1U)
#define SPP_MISC_REG_ADJD_ADJ_EB_MSK                            (((1U<<SPP_MISC_REG_ADJD_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJD_ADJ_EB_POS)
#define SPP_MISC_REG_ADJD_ADJ_EB_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_ADJ_EB_LEN)-1)<<SPP_MISC_REG_ADJD_ADJ_EB_POS))
#define SPP_MISC_REG_ADJD_Y_LUMA                                SPP_MISC_REG_ADJD_Y_LUMA
#define SPP_MISC_REG_ADJD_Y_LUMA_POS                            (1U)
#define SPP_MISC_REG_ADJD_Y_LUMA_LEN                            (9U)
#define SPP_MISC_REG_ADJD_Y_LUMA_MSK                            (((1U<<SPP_MISC_REG_ADJD_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJD_Y_LUMA_POS)
#define SPP_MISC_REG_ADJD_Y_LUMA_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_Y_LUMA_LEN)-1)<<SPP_MISC_REG_ADJD_Y_LUMA_POS))
#define SPP_MISC_REG_ADJD_Y_MUL0                                SPP_MISC_REG_ADJD_Y_MUL0
#define SPP_MISC_REG_ADJD_Y_MUL0_POS                            (10U)
#define SPP_MISC_REG_ADJD_Y_MUL0_LEN                            (11U)
#define SPP_MISC_REG_ADJD_Y_MUL0_MSK                            (((1U<<SPP_MISC_REG_ADJD_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MUL0_POS)
#define SPP_MISC_REG_ADJD_Y_MUL0_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_Y_MUL0_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MUL0_POS))
#define SPP_MISC_REG_ADJD_Y_MUL1                                SPP_MISC_REG_ADJD_Y_MUL1
#define SPP_MISC_REG_ADJD_Y_MUL1_POS                            (21U)
#define SPP_MISC_REG_ADJD_Y_MUL1_LEN                            (11U)
#define SPP_MISC_REG_ADJD_Y_MUL1_MSK                            (((1U<<SPP_MISC_REG_ADJD_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MUL1_POS)
#define SPP_MISC_REG_ADJD_Y_MUL1_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_Y_MUL1_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MUL1_POS))

/* 0x134 : adjD_ctrl_1 */
#define SPP_MISC_ADJD_CTRL_1_OFFSET                             (0x134)
#define SPP_MISC_REG_ADJD_Y_MIN                                 SPP_MISC_REG_ADJD_Y_MIN
#define SPP_MISC_REG_ADJD_Y_MIN_POS                             (0U)
#define SPP_MISC_REG_ADJD_Y_MIN_LEN                             (8U)
#define SPP_MISC_REG_ADJD_Y_MIN_MSK                             (((1U<<SPP_MISC_REG_ADJD_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MIN_POS)
#define SPP_MISC_REG_ADJD_Y_MIN_UMSK                            (~(((1U<<SPP_MISC_REG_ADJD_Y_MIN_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MIN_POS))
#define SPP_MISC_REG_ADJD_Y_MAX                                 SPP_MISC_REG_ADJD_Y_MAX
#define SPP_MISC_REG_ADJD_Y_MAX_POS                             (8U)
#define SPP_MISC_REG_ADJD_Y_MAX_LEN                             (8U)
#define SPP_MISC_REG_ADJD_Y_MAX_MSK                             (((1U<<SPP_MISC_REG_ADJD_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MAX_POS)
#define SPP_MISC_REG_ADJD_Y_MAX_UMSK                            (~(((1U<<SPP_MISC_REG_ADJD_Y_MAX_LEN)-1)<<SPP_MISC_REG_ADJD_Y_MAX_POS))
#define SPP_MISC_REG_ADJD_UV_MIN                                SPP_MISC_REG_ADJD_UV_MIN
#define SPP_MISC_REG_ADJD_UV_MIN_POS                            (16U)
#define SPP_MISC_REG_ADJD_UV_MIN_LEN                            (8U)
#define SPP_MISC_REG_ADJD_UV_MIN_MSK                            (((1U<<SPP_MISC_REG_ADJD_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MIN_POS)
#define SPP_MISC_REG_ADJD_UV_MIN_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_UV_MIN_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MIN_POS))
#define SPP_MISC_REG_ADJD_UV_MAX                                SPP_MISC_REG_ADJD_UV_MAX
#define SPP_MISC_REG_ADJD_UV_MAX_POS                            (24U)
#define SPP_MISC_REG_ADJD_UV_MAX_LEN                            (8U)
#define SPP_MISC_REG_ADJD_UV_MAX_MSK                            (((1U<<SPP_MISC_REG_ADJD_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MAX_POS)
#define SPP_MISC_REG_ADJD_UV_MAX_UMSK                           (~(((1U<<SPP_MISC_REG_ADJD_UV_MAX_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MAX_POS))

/* 0x138 : adjD_ctrl_2 */
#define SPP_MISC_ADJD_CTRL_2_OFFSET                             (0x138)
#define SPP_MISC_RG_ADJD_SEL                                    SPP_MISC_RG_ADJD_SEL
#define SPP_MISC_RG_ADJD_SEL_POS                                (0U)
#define SPP_MISC_RG_ADJD_SEL_LEN                                (4U)
#define SPP_MISC_RG_ADJD_SEL_MSK                                (((1U<<SPP_MISC_RG_ADJD_SEL_LEN)-1)<<SPP_MISC_RG_ADJD_SEL_POS)
#define SPP_MISC_RG_ADJD_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_ADJD_SEL_LEN)-1)<<SPP_MISC_RG_ADJD_SEL_POS))
#define SPP_MISC_REG_ADJD_UV_MUL0                               SPP_MISC_REG_ADJD_UV_MUL0
#define SPP_MISC_REG_ADJD_UV_MUL0_POS                           (10U)
#define SPP_MISC_REG_ADJD_UV_MUL0_LEN                           (11U)
#define SPP_MISC_REG_ADJD_UV_MUL0_MSK                           (((1U<<SPP_MISC_REG_ADJD_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MUL0_POS)
#define SPP_MISC_REG_ADJD_UV_MUL0_UMSK                          (~(((1U<<SPP_MISC_REG_ADJD_UV_MUL0_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MUL0_POS))
#define SPP_MISC_REG_ADJD_UV_MUL1                               SPP_MISC_REG_ADJD_UV_MUL1
#define SPP_MISC_REG_ADJD_UV_MUL1_POS                           (21U)
#define SPP_MISC_REG_ADJD_UV_MUL1_LEN                           (11U)
#define SPP_MISC_REG_ADJD_UV_MUL1_MSK                           (((1U<<SPP_MISC_REG_ADJD_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MUL1_POS)
#define SPP_MISC_REG_ADJD_UV_MUL1_UMSK                          (~(((1U<<SPP_MISC_REG_ADJD_UV_MUL1_LEN)-1)<<SPP_MISC_REG_ADJD_UV_MUL1_POS))

/* 0x160 : y2rA_config_0 */
#define SPP_MISC_Y2RA_CONFIG_0_OFFSET                           (0x160)
#define SPP_MISC_RG_Y2RA_PRE_0                                  SPP_MISC_RG_Y2RA_PRE_0
#define SPP_MISC_RG_Y2RA_PRE_0_POS                              (0U)
#define SPP_MISC_RG_Y2RA_PRE_0_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_PRE_0_MSK                              (((1U<<SPP_MISC_RG_Y2RA_PRE_0_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_0_POS)
#define SPP_MISC_RG_Y2RA_PRE_0_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_PRE_0_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_0_POS))
#define SPP_MISC_RG_Y2RA_POS_0                                  SPP_MISC_RG_Y2RA_POS_0
#define SPP_MISC_RG_Y2RA_POS_0_POS                              (16U)
#define SPP_MISC_RG_Y2RA_POS_0_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_POS_0_MSK                              (((1U<<SPP_MISC_RG_Y2RA_POS_0_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_0_POS)
#define SPP_MISC_RG_Y2RA_POS_0_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_POS_0_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_0_POS))
#define SPP_MISC_RG_Y2RA_EN                                     SPP_MISC_RG_Y2RA_EN
#define SPP_MISC_RG_Y2RA_EN_POS                                 (27U)
#define SPP_MISC_RG_Y2RA_EN_LEN                                 (1U)
#define SPP_MISC_RG_Y2RA_EN_MSK                                 (((1U<<SPP_MISC_RG_Y2RA_EN_LEN)-1)<<SPP_MISC_RG_Y2RA_EN_POS)
#define SPP_MISC_RG_Y2RA_EN_UMSK                                (~(((1U<<SPP_MISC_RG_Y2RA_EN_LEN)-1)<<SPP_MISC_RG_Y2RA_EN_POS))
#define SPP_MISC_RG_Y2RA_SEL                                    SPP_MISC_RG_Y2RA_SEL
#define SPP_MISC_RG_Y2RA_SEL_POS                                (28U)
#define SPP_MISC_RG_Y2RA_SEL_LEN                                (4U)
#define SPP_MISC_RG_Y2RA_SEL_MSK                                (((1U<<SPP_MISC_RG_Y2RA_SEL_LEN)-1)<<SPP_MISC_RG_Y2RA_SEL_POS)
#define SPP_MISC_RG_Y2RA_SEL_UMSK                               (~(((1U<<SPP_MISC_RG_Y2RA_SEL_LEN)-1)<<SPP_MISC_RG_Y2RA_SEL_POS))

/* 0x164 : y2rA_config_1 */
#define SPP_MISC_Y2RA_CONFIG_1_OFFSET                           (0x164)
#define SPP_MISC_RG_Y2RA_PRE_1                                  SPP_MISC_RG_Y2RA_PRE_1
#define SPP_MISC_RG_Y2RA_PRE_1_POS                              (0U)
#define SPP_MISC_RG_Y2RA_PRE_1_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_PRE_1_MSK                              (((1U<<SPP_MISC_RG_Y2RA_PRE_1_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_1_POS)
#define SPP_MISC_RG_Y2RA_PRE_1_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_PRE_1_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_1_POS))
#define SPP_MISC_RG_Y2RA_POS_1                                  SPP_MISC_RG_Y2RA_POS_1
#define SPP_MISC_RG_Y2RA_POS_1_POS                              (16U)
#define SPP_MISC_RG_Y2RA_POS_1_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_POS_1_MSK                              (((1U<<SPP_MISC_RG_Y2RA_POS_1_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_1_POS)
#define SPP_MISC_RG_Y2RA_POS_1_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_POS_1_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_1_POS))

/* 0x168 : y2rA_config_2 */
#define SPP_MISC_Y2RA_CONFIG_2_OFFSET                           (0x168)
#define SPP_MISC_RG_Y2RA_PRE_2                                  SPP_MISC_RG_Y2RA_PRE_2
#define SPP_MISC_RG_Y2RA_PRE_2_POS                              (0U)
#define SPP_MISC_RG_Y2RA_PRE_2_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_PRE_2_MSK                              (((1U<<SPP_MISC_RG_Y2RA_PRE_2_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_2_POS)
#define SPP_MISC_RG_Y2RA_PRE_2_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_PRE_2_LEN)-1)<<SPP_MISC_RG_Y2RA_PRE_2_POS))
#define SPP_MISC_RG_Y2RA_POS_2                                  SPP_MISC_RG_Y2RA_POS_2
#define SPP_MISC_RG_Y2RA_POS_2_POS                              (16U)
#define SPP_MISC_RG_Y2RA_POS_2_LEN                              (9U)
#define SPP_MISC_RG_Y2RA_POS_2_MSK                              (((1U<<SPP_MISC_RG_Y2RA_POS_2_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_2_POS)
#define SPP_MISC_RG_Y2RA_POS_2_UMSK                             (~(((1U<<SPP_MISC_RG_Y2RA_POS_2_LEN)-1)<<SPP_MISC_RG_Y2RA_POS_2_POS))

/* 0x16C : y2rA_config_3 */
#define SPP_MISC_Y2RA_CONFIG_3_OFFSET                           (0x16C)
#define SPP_MISC_RG_Y2RA_MTX_00                                 SPP_MISC_RG_Y2RA_MTX_00
#define SPP_MISC_RG_Y2RA_MTX_00_POS                             (0U)
#define SPP_MISC_RG_Y2RA_MTX_00_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_00_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_00_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_00_POS)
#define SPP_MISC_RG_Y2RA_MTX_00_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_00_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_00_POS))
#define SPP_MISC_RG_Y2RA_MTX_01                                 SPP_MISC_RG_Y2RA_MTX_01
#define SPP_MISC_RG_Y2RA_MTX_01_POS                             (16U)
#define SPP_MISC_RG_Y2RA_MTX_01_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_01_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_01_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_01_POS)
#define SPP_MISC_RG_Y2RA_MTX_01_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_01_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_01_POS))

/* 0x170 : y2rA_config_4 */
#define SPP_MISC_Y2RA_CONFIG_4_OFFSET                           (0x170)
#define SPP_MISC_RG_Y2RA_MTX_02                                 SPP_MISC_RG_Y2RA_MTX_02
#define SPP_MISC_RG_Y2RA_MTX_02_POS                             (0U)
#define SPP_MISC_RG_Y2RA_MTX_02_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_02_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_02_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_02_POS)
#define SPP_MISC_RG_Y2RA_MTX_02_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_02_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_02_POS))
#define SPP_MISC_RG_Y2RA_MTX_10                                 SPP_MISC_RG_Y2RA_MTX_10
#define SPP_MISC_RG_Y2RA_MTX_10_POS                             (16U)
#define SPP_MISC_RG_Y2RA_MTX_10_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_10_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_10_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_10_POS)
#define SPP_MISC_RG_Y2RA_MTX_10_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_10_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_10_POS))

/* 0x174 : y2rA_config_5 */
#define SPP_MISC_Y2RA_CONFIG_5_OFFSET                           (0x174)
#define SPP_MISC_RG_Y2RA_MTX_11                                 SPP_MISC_RG_Y2RA_MTX_11
#define SPP_MISC_RG_Y2RA_MTX_11_POS                             (0U)
#define SPP_MISC_RG_Y2RA_MTX_11_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_11_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_11_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_11_POS)
#define SPP_MISC_RG_Y2RA_MTX_11_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_11_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_11_POS))
#define SPP_MISC_RG_Y2RA_MTX_12                                 SPP_MISC_RG_Y2RA_MTX_12
#define SPP_MISC_RG_Y2RA_MTX_12_POS                             (16U)
#define SPP_MISC_RG_Y2RA_MTX_12_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_12_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_12_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_12_POS)
#define SPP_MISC_RG_Y2RA_MTX_12_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_12_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_12_POS))

/* 0x178 : y2rA_config_6 */
#define SPP_MISC_Y2RA_CONFIG_6_OFFSET                           (0x178)
#define SPP_MISC_RG_Y2RA_MTX_20                                 SPP_MISC_RG_Y2RA_MTX_20
#define SPP_MISC_RG_Y2RA_MTX_20_POS                             (0U)
#define SPP_MISC_RG_Y2RA_MTX_20_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_20_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_20_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_20_POS)
#define SPP_MISC_RG_Y2RA_MTX_20_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_20_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_20_POS))
#define SPP_MISC_RG_Y2RA_MTX_21                                 SPP_MISC_RG_Y2RA_MTX_21
#define SPP_MISC_RG_Y2RA_MTX_21_POS                             (16U)
#define SPP_MISC_RG_Y2RA_MTX_21_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_21_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_21_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_21_POS)
#define SPP_MISC_RG_Y2RA_MTX_21_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_21_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_21_POS))

/* 0x17C : y2rA_config_7 */
#define SPP_MISC_Y2RA_CONFIG_7_OFFSET                           (0x17C)
#define SPP_MISC_RG_Y2RA_MTX_22                                 SPP_MISC_RG_Y2RA_MTX_22
#define SPP_MISC_RG_Y2RA_MTX_22_POS                             (0U)
#define SPP_MISC_RG_Y2RA_MTX_22_LEN                             (12U)
#define SPP_MISC_RG_Y2RA_MTX_22_MSK                             (((1U<<SPP_MISC_RG_Y2RA_MTX_22_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_22_POS)
#define SPP_MISC_RG_Y2RA_MTX_22_UMSK                            (~(((1U<<SPP_MISC_RG_Y2RA_MTX_22_LEN)-1)<<SPP_MISC_RG_Y2RA_MTX_22_POS))

/* 0x180 : disp_rgb2yuv_config_0 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_0_OFFSET                   (0x180)
#define SPP_MISC_RG_DISP_R2Y_PRE_0                              SPP_MISC_RG_DISP_R2Y_PRE_0
#define SPP_MISC_RG_DISP_R2Y_PRE_0_POS                          (0U)
#define SPP_MISC_RG_DISP_R2Y_PRE_0_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_PRE_0_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_PRE_0_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_0_POS)
#define SPP_MISC_RG_DISP_R2Y_PRE_0_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_PRE_0_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_0_POS))
#define SPP_MISC_RG_DISP_R2Y_PRE_1                              SPP_MISC_RG_DISP_R2Y_PRE_1
#define SPP_MISC_RG_DISP_R2Y_PRE_1_POS                          (10U)
#define SPP_MISC_RG_DISP_R2Y_PRE_1_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_PRE_1_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_PRE_1_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_1_POS)
#define SPP_MISC_RG_DISP_R2Y_PRE_1_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_PRE_1_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_1_POS))
#define SPP_MISC_RG_DISP_R2Y_PRE_2                              SPP_MISC_RG_DISP_R2Y_PRE_2
#define SPP_MISC_RG_DISP_R2Y_PRE_2_POS                          (20U)
#define SPP_MISC_RG_DISP_R2Y_PRE_2_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_PRE_2_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_PRE_2_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_2_POS)
#define SPP_MISC_RG_DISP_R2Y_PRE_2_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_PRE_2_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_PRE_2_POS))
#define SPP_MISC_RG_DISP_R2Y_EN                                 SPP_MISC_RG_DISP_R2Y_EN
#define SPP_MISC_RG_DISP_R2Y_EN_POS                             (31U)
#define SPP_MISC_RG_DISP_R2Y_EN_LEN                             (1U)
#define SPP_MISC_RG_DISP_R2Y_EN_MSK                             (((1U<<SPP_MISC_RG_DISP_R2Y_EN_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_EN_POS)
#define SPP_MISC_RG_DISP_R2Y_EN_UMSK                            (~(((1U<<SPP_MISC_RG_DISP_R2Y_EN_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_EN_POS))

/* 0x184 : disp_rgb2yuv_config_1 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_1_OFFSET                   (0x184)
#define SPP_MISC_RG_DISP_R2Y_POS_0                              SPP_MISC_RG_DISP_R2Y_POS_0
#define SPP_MISC_RG_DISP_R2Y_POS_0_POS                          (0U)
#define SPP_MISC_RG_DISP_R2Y_POS_0_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_POS_0_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_POS_0_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_0_POS)
#define SPP_MISC_RG_DISP_R2Y_POS_0_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_POS_0_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_0_POS))
#define SPP_MISC_RG_DISP_R2Y_POS_1                              SPP_MISC_RG_DISP_R2Y_POS_1
#define SPP_MISC_RG_DISP_R2Y_POS_1_POS                          (10U)
#define SPP_MISC_RG_DISP_R2Y_POS_1_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_POS_1_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_POS_1_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_1_POS)
#define SPP_MISC_RG_DISP_R2Y_POS_1_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_POS_1_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_1_POS))
#define SPP_MISC_RG_DISP_R2Y_POS_2                              SPP_MISC_RG_DISP_R2Y_POS_2
#define SPP_MISC_RG_DISP_R2Y_POS_2_POS                          (20U)
#define SPP_MISC_RG_DISP_R2Y_POS_2_LEN                          (9U)
#define SPP_MISC_RG_DISP_R2Y_POS_2_MSK                          (((1U<<SPP_MISC_RG_DISP_R2Y_POS_2_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_2_POS)
#define SPP_MISC_RG_DISP_R2Y_POS_2_UMSK                         (~(((1U<<SPP_MISC_RG_DISP_R2Y_POS_2_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_POS_2_POS))

/* 0x188 : disp_rgb2yuv_config_2 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_2_OFFSET                   (0x188)
#define SPP_MISC_RG_DISP_R2Y_MTX_00                             SPP_MISC_RG_DISP_R2Y_MTX_00
#define SPP_MISC_RG_DISP_R2Y_MTX_00_POS                         (0U)
#define SPP_MISC_RG_DISP_R2Y_MTX_00_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_00_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_00_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_00_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_00_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_00_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_00_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_01                             SPP_MISC_RG_DISP_R2Y_MTX_01
#define SPP_MISC_RG_DISP_R2Y_MTX_01_POS                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_01_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_01_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_01_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_01_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_01_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_01_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_01_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_02_L                           SPP_MISC_RG_DISP_R2Y_MTX_02_L
#define SPP_MISC_RG_DISP_R2Y_MTX_02_L_POS                       (24U)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_L_LEN                       (8U)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_L_MSK                       (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_02_L_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_02_L_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_L_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_02_L_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_02_L_POS))

/* 0x18C : disp_rgb2yuv_config_3 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_3_OFFSET                   (0x18C)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_U                           SPP_MISC_RG_DISP_R2Y_MTX_02_U
#define SPP_MISC_RG_DISP_R2Y_MTX_02_U_POS                       (0U)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_U_LEN                       (4U)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_U_MSK                       (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_02_U_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_02_U_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_02_U_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_02_U_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_02_U_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_10                             SPP_MISC_RG_DISP_R2Y_MTX_10
#define SPP_MISC_RG_DISP_R2Y_MTX_10_POS                         (4U)
#define SPP_MISC_RG_DISP_R2Y_MTX_10_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_10_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_10_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_10_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_10_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_10_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_10_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_11                             SPP_MISC_RG_DISP_R2Y_MTX_11
#define SPP_MISC_RG_DISP_R2Y_MTX_11_POS                         (16U)
#define SPP_MISC_RG_DISP_R2Y_MTX_11_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_11_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_11_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_11_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_11_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_11_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_11_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_12_L                           SPP_MISC_RG_DISP_R2Y_MTX_12_L
#define SPP_MISC_RG_DISP_R2Y_MTX_12_L_POS                       (28U)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_L_LEN                       (4U)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_L_MSK                       (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_12_L_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_12_L_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_L_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_12_L_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_12_L_POS))

/* 0x190 : disp_rgb2yuv_config_4 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_4_OFFSET                   (0x190)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_U                           SPP_MISC_RG_DISP_R2Y_MTX_12_U
#define SPP_MISC_RG_DISP_R2Y_MTX_12_U_POS                       (0U)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_U_LEN                       (8U)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_U_MSK                       (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_12_U_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_12_U_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_12_U_UMSK                      (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_12_U_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_12_U_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_20                             SPP_MISC_RG_DISP_R2Y_MTX_20
#define SPP_MISC_RG_DISP_R2Y_MTX_20_POS                         (8U)
#define SPP_MISC_RG_DISP_R2Y_MTX_20_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_20_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_20_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_20_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_20_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_20_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_20_POS))
#define SPP_MISC_RG_DISP_R2Y_MTX_21                             SPP_MISC_RG_DISP_R2Y_MTX_21
#define SPP_MISC_RG_DISP_R2Y_MTX_21_POS                         (20U)
#define SPP_MISC_RG_DISP_R2Y_MTX_21_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_21_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_21_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_21_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_21_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_21_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_21_POS))

/* 0x194 : disp_rgb2yuv_config_5 */
#define SPP_MISC_DISP_RGB2YUV_CONFIG_5_OFFSET                   (0x194)
#define SPP_MISC_RG_DISP_R2Y_MTX_22                             SPP_MISC_RG_DISP_R2Y_MTX_22
#define SPP_MISC_RG_DISP_R2Y_MTX_22_POS                         (0U)
#define SPP_MISC_RG_DISP_R2Y_MTX_22_LEN                         (12U)
#define SPP_MISC_RG_DISP_R2Y_MTX_22_MSK                         (((1U<<SPP_MISC_RG_DISP_R2Y_MTX_22_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_22_POS)
#define SPP_MISC_RG_DISP_R2Y_MTX_22_UMSK                        (~(((1U<<SPP_MISC_RG_DISP_R2Y_MTX_22_LEN)-1)<<SPP_MISC_RG_DISP_R2Y_MTX_22_POS))

/* 0x1C0 : cropA_hsync */
#define SPP_MISC_CROPA_HSYNC_OFFSET                             (0x1C0)
#define SPP_MISC_REG_CROPA_HSYNC_START                          SPP_MISC_REG_CROPA_HSYNC_START
#define SPP_MISC_REG_CROPA_HSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPA_HSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPA_HSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPA_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPA_HSYNC_START_POS)
#define SPP_MISC_REG_CROPA_HSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPA_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPA_HSYNC_START_POS))
#define SPP_MISC_REG_CROPA_HSYNC_END                            SPP_MISC_REG_CROPA_HSYNC_END
#define SPP_MISC_REG_CROPA_HSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPA_HSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPA_HSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPA_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPA_HSYNC_END_POS)
#define SPP_MISC_REG_CROPA_HSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPA_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPA_HSYNC_END_POS))

/* 0x1C4 : cropA_vsync */
#define SPP_MISC_CROPA_VSYNC_OFFSET                             (0x1C4)
#define SPP_MISC_REG_CROPA_VSYNC_START                          SPP_MISC_REG_CROPA_VSYNC_START
#define SPP_MISC_REG_CROPA_VSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPA_VSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPA_VSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPA_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPA_VSYNC_START_POS)
#define SPP_MISC_REG_CROPA_VSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPA_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPA_VSYNC_START_POS))
#define SPP_MISC_REG_CROPA_VSYNC_END                            SPP_MISC_REG_CROPA_VSYNC_END
#define SPP_MISC_REG_CROPA_VSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPA_VSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPA_VSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPA_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPA_VSYNC_END_POS)
#define SPP_MISC_REG_CROPA_VSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPA_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPA_VSYNC_END_POS))

/* 0x1C8 : cropB_hsync */
#define SPP_MISC_CROPB_HSYNC_OFFSET                             (0x1C8)
#define SPP_MISC_REG_CROPB_HSYNC_START                          SPP_MISC_REG_CROPB_HSYNC_START
#define SPP_MISC_REG_CROPB_HSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPB_HSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPB_HSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPB_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPB_HSYNC_START_POS)
#define SPP_MISC_REG_CROPB_HSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPB_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPB_HSYNC_START_POS))
#define SPP_MISC_REG_CROPB_HSYNC_END                            SPP_MISC_REG_CROPB_HSYNC_END
#define SPP_MISC_REG_CROPB_HSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPB_HSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPB_HSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPB_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPB_HSYNC_END_POS)
#define SPP_MISC_REG_CROPB_HSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPB_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPB_HSYNC_END_POS))

/* 0x1CC : cropB_vsync */
#define SPP_MISC_CROPB_VSYNC_OFFSET                             (0x1CC)
#define SPP_MISC_REG_CROPB_VSYNC_START                          SPP_MISC_REG_CROPB_VSYNC_START
#define SPP_MISC_REG_CROPB_VSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPB_VSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPB_VSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPB_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPB_VSYNC_START_POS)
#define SPP_MISC_REG_CROPB_VSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPB_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPB_VSYNC_START_POS))
#define SPP_MISC_REG_CROPB_VSYNC_END                            SPP_MISC_REG_CROPB_VSYNC_END
#define SPP_MISC_REG_CROPB_VSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPB_VSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPB_VSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPB_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPB_VSYNC_END_POS)
#define SPP_MISC_REG_CROPB_VSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPB_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPB_VSYNC_END_POS))

/* 0x1D0 : cropC_hsync */
#define SPP_MISC_CROPC_HSYNC_OFFSET                             (0x1D0)
#define SPP_MISC_REG_CROPC_HSYNC_START                          SPP_MISC_REG_CROPC_HSYNC_START
#define SPP_MISC_REG_CROPC_HSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPC_HSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPC_HSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPC_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPC_HSYNC_START_POS)
#define SPP_MISC_REG_CROPC_HSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPC_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPC_HSYNC_START_POS))
#define SPP_MISC_REG_CROPC_HSYNC_END                            SPP_MISC_REG_CROPC_HSYNC_END
#define SPP_MISC_REG_CROPC_HSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPC_HSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPC_HSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPC_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPC_HSYNC_END_POS)
#define SPP_MISC_REG_CROPC_HSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPC_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPC_HSYNC_END_POS))

/* 0x1D4 : cropC_vsync */
#define SPP_MISC_CROPC_VSYNC_OFFSET                             (0x1D4)
#define SPP_MISC_REG_CROPC_VSYNC_START                          SPP_MISC_REG_CROPC_VSYNC_START
#define SPP_MISC_REG_CROPC_VSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPC_VSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPC_VSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPC_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPC_VSYNC_START_POS)
#define SPP_MISC_REG_CROPC_VSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPC_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPC_VSYNC_START_POS))
#define SPP_MISC_REG_CROPC_VSYNC_END                            SPP_MISC_REG_CROPC_VSYNC_END
#define SPP_MISC_REG_CROPC_VSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPC_VSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPC_VSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPC_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPC_VSYNC_END_POS)
#define SPP_MISC_REG_CROPC_VSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPC_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPC_VSYNC_END_POS))

/* 0x1D8 : cropD_hsync */
#define SPP_MISC_CROPD_HSYNC_OFFSET                             (0x1D8)
#define SPP_MISC_REG_CROPD_HSYNC_START                          SPP_MISC_REG_CROPD_HSYNC_START
#define SPP_MISC_REG_CROPD_HSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPD_HSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPD_HSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPD_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPD_HSYNC_START_POS)
#define SPP_MISC_REG_CROPD_HSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPD_HSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPD_HSYNC_START_POS))
#define SPP_MISC_REG_CROPD_HSYNC_END                            SPP_MISC_REG_CROPD_HSYNC_END
#define SPP_MISC_REG_CROPD_HSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPD_HSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPD_HSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPD_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPD_HSYNC_END_POS)
#define SPP_MISC_REG_CROPD_HSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPD_HSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPD_HSYNC_END_POS))

/* 0x1DC : cropD_vsync */
#define SPP_MISC_CROPD_VSYNC_OFFSET                             (0x1DC)
#define SPP_MISC_REG_CROPD_VSYNC_START                          SPP_MISC_REG_CROPD_VSYNC_START
#define SPP_MISC_REG_CROPD_VSYNC_START_POS                      (0U)
#define SPP_MISC_REG_CROPD_VSYNC_START_LEN                      (16U)
#define SPP_MISC_REG_CROPD_VSYNC_START_MSK                      (((1U<<SPP_MISC_REG_CROPD_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPD_VSYNC_START_POS)
#define SPP_MISC_REG_CROPD_VSYNC_START_UMSK                     (~(((1U<<SPP_MISC_REG_CROPD_VSYNC_START_LEN)-1)<<SPP_MISC_REG_CROPD_VSYNC_START_POS))
#define SPP_MISC_REG_CROPD_VSYNC_END                            SPP_MISC_REG_CROPD_VSYNC_END
#define SPP_MISC_REG_CROPD_VSYNC_END_POS                        (16U)
#define SPP_MISC_REG_CROPD_VSYNC_END_LEN                        (16U)
#define SPP_MISC_REG_CROPD_VSYNC_END_MSK                        (((1U<<SPP_MISC_REG_CROPD_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPD_VSYNC_END_POS)
#define SPP_MISC_REG_CROPD_VSYNC_END_UMSK                       (~(((1U<<SPP_MISC_REG_CROPD_VSYNC_END_LEN)-1)<<SPP_MISC_REG_CROPD_VSYNC_END_POS))

/* 0x1E0 : crop_enable */
#define SPP_MISC_CROP_ENABLE_OFFSET                             (0x1E0)
#define SPP_MISC_REG_CROPA_ENABLE                               SPP_MISC_REG_CROPA_ENABLE
#define SPP_MISC_REG_CROPA_ENABLE_POS                           (0U)
#define SPP_MISC_REG_CROPA_ENABLE_LEN                           (1U)
#define SPP_MISC_REG_CROPA_ENABLE_MSK                           (((1U<<SPP_MISC_REG_CROPA_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPA_ENABLE_POS)
#define SPP_MISC_REG_CROPA_ENABLE_UMSK                          (~(((1U<<SPP_MISC_REG_CROPA_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPA_ENABLE_POS))
#define SPP_MISC_REG_CROPB_ENABLE                               SPP_MISC_REG_CROPB_ENABLE
#define SPP_MISC_REG_CROPB_ENABLE_POS                           (1U)
#define SPP_MISC_REG_CROPB_ENABLE_LEN                           (1U)
#define SPP_MISC_REG_CROPB_ENABLE_MSK                           (((1U<<SPP_MISC_REG_CROPB_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPB_ENABLE_POS)
#define SPP_MISC_REG_CROPB_ENABLE_UMSK                          (~(((1U<<SPP_MISC_REG_CROPB_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPB_ENABLE_POS))
#define SPP_MISC_REG_CROPC_ENABLE                               SPP_MISC_REG_CROPC_ENABLE
#define SPP_MISC_REG_CROPC_ENABLE_POS                           (2U)
#define SPP_MISC_REG_CROPC_ENABLE_LEN                           (1U)
#define SPP_MISC_REG_CROPC_ENABLE_MSK                           (((1U<<SPP_MISC_REG_CROPC_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPC_ENABLE_POS)
#define SPP_MISC_REG_CROPC_ENABLE_UMSK                          (~(((1U<<SPP_MISC_REG_CROPC_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPC_ENABLE_POS))
#define SPP_MISC_REG_CROPD_ENABLE                               SPP_MISC_REG_CROPD_ENABLE
#define SPP_MISC_REG_CROPD_ENABLE_POS                           (3U)
#define SPP_MISC_REG_CROPD_ENABLE_LEN                           (1U)
#define SPP_MISC_REG_CROPD_ENABLE_MSK                           (((1U<<SPP_MISC_REG_CROPD_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPD_ENABLE_POS)
#define SPP_MISC_REG_CROPD_ENABLE_UMSK                          (~(((1U<<SPP_MISC_REG_CROPD_ENABLE_LEN)-1)<<SPP_MISC_REG_CROPD_ENABLE_POS))

/* 0x1FC : disp_gma_cfg */
#define SPP_MISC_DISP_GMA_CFG_OFFSET                            (0x1FC)
#define SPP_MISC_REG_DP_GMA_CH0_EN                              SPP_MISC_REG_DP_GMA_CH0_EN
#define SPP_MISC_REG_DP_GMA_CH0_EN_POS                          (0U)
#define SPP_MISC_REG_DP_GMA_CH0_EN_LEN                          (1U)
#define SPP_MISC_REG_DP_GMA_CH0_EN_MSK                          (((1U<<SPP_MISC_REG_DP_GMA_CH0_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH0_EN_POS)
#define SPP_MISC_REG_DP_GMA_CH0_EN_UMSK                         (~(((1U<<SPP_MISC_REG_DP_GMA_CH0_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH0_EN_POS))
#define SPP_MISC_REG_DP_GMA_CH1_EN                              SPP_MISC_REG_DP_GMA_CH1_EN
#define SPP_MISC_REG_DP_GMA_CH1_EN_POS                          (1U)
#define SPP_MISC_REG_DP_GMA_CH1_EN_LEN                          (1U)
#define SPP_MISC_REG_DP_GMA_CH1_EN_MSK                          (((1U<<SPP_MISC_REG_DP_GMA_CH1_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH1_EN_POS)
#define SPP_MISC_REG_DP_GMA_CH1_EN_UMSK                         (~(((1U<<SPP_MISC_REG_DP_GMA_CH1_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH1_EN_POS))
#define SPP_MISC_REG_DP_GMA_CH2_EN                              SPP_MISC_REG_DP_GMA_CH2_EN
#define SPP_MISC_REG_DP_GMA_CH2_EN_POS                          (2U)
#define SPP_MISC_REG_DP_GMA_CH2_EN_LEN                          (1U)
#define SPP_MISC_REG_DP_GMA_CH2_EN_MSK                          (((1U<<SPP_MISC_REG_DP_GMA_CH2_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH2_EN_POS)
#define SPP_MISC_REG_DP_GMA_CH2_EN_UMSK                         (~(((1U<<SPP_MISC_REG_DP_GMA_CH2_EN_LEN)-1)<<SPP_MISC_REG_DP_GMA_CH2_EN_POS))

/* 0x200 : disp_gma_curve_00 */
#define SPP_MISC_DISP_GMA_CURVE_00_OFFSET                       (0x200)
#define SPP_MISC_REG_DP_GMA_CURVE_00                            SPP_MISC_REG_DP_GMA_CURVE_00
#define SPP_MISC_REG_DP_GMA_CURVE_00_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_00_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_00_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_00_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_00_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_00_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_00_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_00_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_01                            SPP_MISC_REG_DP_GMA_CURVE_01
#define SPP_MISC_REG_DP_GMA_CURVE_01_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_01_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_01_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_01_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_01_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_01_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_01_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_01_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_02                            SPP_MISC_REG_DP_GMA_CURVE_02
#define SPP_MISC_REG_DP_GMA_CURVE_02_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_02_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_02_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_02_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_02_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_02_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_02_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_02_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_03                            SPP_MISC_REG_DP_GMA_CURVE_03
#define SPP_MISC_REG_DP_GMA_CURVE_03_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_03_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_03_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_03_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_03_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_03_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_03_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_03_POS))

/* 0x204 : disp_gma_curve_04 */
#define SPP_MISC_DISP_GMA_CURVE_04_OFFSET                       (0x204)
#define SPP_MISC_REG_DP_GMA_CURVE_04                            SPP_MISC_REG_DP_GMA_CURVE_04
#define SPP_MISC_REG_DP_GMA_CURVE_04_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_04_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_04_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_04_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_04_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_04_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_04_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_04_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_05                            SPP_MISC_REG_DP_GMA_CURVE_05
#define SPP_MISC_REG_DP_GMA_CURVE_05_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_05_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_05_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_05_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_05_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_05_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_05_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_05_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_06                            SPP_MISC_REG_DP_GMA_CURVE_06
#define SPP_MISC_REG_DP_GMA_CURVE_06_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_06_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_06_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_06_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_06_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_06_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_06_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_06_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_07                            SPP_MISC_REG_DP_GMA_CURVE_07
#define SPP_MISC_REG_DP_GMA_CURVE_07_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_07_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_07_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_07_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_07_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_07_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_07_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_07_POS))

/* 0x208 : disp_gma_curve_08 */
#define SPP_MISC_DISP_GMA_CURVE_08_OFFSET                       (0x208)
#define SPP_MISC_REG_DP_GMA_CURVE_08                            SPP_MISC_REG_DP_GMA_CURVE_08
#define SPP_MISC_REG_DP_GMA_CURVE_08_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_08_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_08_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_08_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_08_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_08_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_08_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_08_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_09                            SPP_MISC_REG_DP_GMA_CURVE_09
#define SPP_MISC_REG_DP_GMA_CURVE_09_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_09_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_09_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_09_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_09_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_09_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_09_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_09_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_0A                            SPP_MISC_REG_DP_GMA_CURVE_0A
#define SPP_MISC_REG_DP_GMA_CURVE_0A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_0A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_0B                            SPP_MISC_REG_DP_GMA_CURVE_0B
#define SPP_MISC_REG_DP_GMA_CURVE_0B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_0B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0B_POS))

/* 0x20C : disp_gma_curve_0c */
#define SPP_MISC_DISP_GMA_CURVE_0C_OFFSET                       (0x20C)
#define SPP_MISC_REG_DP_GMA_CURVE_0C                            SPP_MISC_REG_DP_GMA_CURVE_0C
#define SPP_MISC_REG_DP_GMA_CURVE_0C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_0C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_0D                            SPP_MISC_REG_DP_GMA_CURVE_0D
#define SPP_MISC_REG_DP_GMA_CURVE_0D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_0E                            SPP_MISC_REG_DP_GMA_CURVE_0E
#define SPP_MISC_REG_DP_GMA_CURVE_0E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_0E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_0F                            SPP_MISC_REG_DP_GMA_CURVE_0F
#define SPP_MISC_REG_DP_GMA_CURVE_0F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_0F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_0F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_0F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_0F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_0F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_0F_POS))

/* 0x210 : disp_gma_curve_10 */
#define SPP_MISC_DISP_GMA_CURVE_10_OFFSET                       (0x210)
#define SPP_MISC_REG_DP_GMA_CURVE_10                            SPP_MISC_REG_DP_GMA_CURVE_10
#define SPP_MISC_REG_DP_GMA_CURVE_10_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_10_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_10_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_10_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_10_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_10_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_10_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_10_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_11                            SPP_MISC_REG_DP_GMA_CURVE_11
#define SPP_MISC_REG_DP_GMA_CURVE_11_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_11_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_11_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_11_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_11_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_11_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_11_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_11_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_12                            SPP_MISC_REG_DP_GMA_CURVE_12
#define SPP_MISC_REG_DP_GMA_CURVE_12_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_12_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_12_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_12_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_12_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_12_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_12_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_12_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_13                            SPP_MISC_REG_DP_GMA_CURVE_13
#define SPP_MISC_REG_DP_GMA_CURVE_13_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_13_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_13_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_13_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_13_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_13_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_13_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_13_POS))

/* 0x214 : disp_gma_curve_14 */
#define SPP_MISC_DISP_GMA_CURVE_14_OFFSET                       (0x214)
#define SPP_MISC_REG_DP_GMA_CURVE_14                            SPP_MISC_REG_DP_GMA_CURVE_14
#define SPP_MISC_REG_DP_GMA_CURVE_14_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_14_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_14_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_14_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_14_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_14_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_14_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_14_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_15                            SPP_MISC_REG_DP_GMA_CURVE_15
#define SPP_MISC_REG_DP_GMA_CURVE_15_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_15_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_15_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_15_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_15_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_15_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_15_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_15_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_16                            SPP_MISC_REG_DP_GMA_CURVE_16
#define SPP_MISC_REG_DP_GMA_CURVE_16_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_16_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_16_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_16_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_16_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_16_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_16_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_16_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_17                            SPP_MISC_REG_DP_GMA_CURVE_17
#define SPP_MISC_REG_DP_GMA_CURVE_17_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_17_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_17_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_17_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_17_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_17_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_17_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_17_POS))

/* 0x218 : disp_gma_curve_18 */
#define SPP_MISC_DISP_GMA_CURVE_18_OFFSET                       (0x218)
#define SPP_MISC_REG_DP_GMA_CURVE_18                            SPP_MISC_REG_DP_GMA_CURVE_18
#define SPP_MISC_REG_DP_GMA_CURVE_18_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_18_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_18_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_18_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_18_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_18_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_18_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_18_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_19                            SPP_MISC_REG_DP_GMA_CURVE_19
#define SPP_MISC_REG_DP_GMA_CURVE_19_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_19_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_19_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_19_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_19_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_19_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_19_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_19_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_1A                            SPP_MISC_REG_DP_GMA_CURVE_1A
#define SPP_MISC_REG_DP_GMA_CURVE_1A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_1A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_1B                            SPP_MISC_REG_DP_GMA_CURVE_1B
#define SPP_MISC_REG_DP_GMA_CURVE_1B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_1B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1B_POS))

/* 0x21C : disp_gma_curve_1c */
#define SPP_MISC_DISP_GMA_CURVE_1C_OFFSET                       (0x21C)
#define SPP_MISC_REG_DP_GMA_CURVE_1C                            SPP_MISC_REG_DP_GMA_CURVE_1C
#define SPP_MISC_REG_DP_GMA_CURVE_1C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_1C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_1D                            SPP_MISC_REG_DP_GMA_CURVE_1D
#define SPP_MISC_REG_DP_GMA_CURVE_1D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_1E                            SPP_MISC_REG_DP_GMA_CURVE_1E
#define SPP_MISC_REG_DP_GMA_CURVE_1E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_1E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_1F                            SPP_MISC_REG_DP_GMA_CURVE_1F
#define SPP_MISC_REG_DP_GMA_CURVE_1F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_1F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_1F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_1F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_1F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_1F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_1F_POS))

/* 0x220 : disp_gma_curve_20 */
#define SPP_MISC_DISP_GMA_CURVE_20_OFFSET                       (0x220)
#define SPP_MISC_REG_DP_GMA_CURVE_20                            SPP_MISC_REG_DP_GMA_CURVE_20
#define SPP_MISC_REG_DP_GMA_CURVE_20_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_20_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_20_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_20_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_20_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_20_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_20_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_20_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_21                            SPP_MISC_REG_DP_GMA_CURVE_21
#define SPP_MISC_REG_DP_GMA_CURVE_21_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_21_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_21_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_21_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_21_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_21_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_21_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_21_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_22                            SPP_MISC_REG_DP_GMA_CURVE_22
#define SPP_MISC_REG_DP_GMA_CURVE_22_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_22_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_22_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_22_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_22_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_22_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_22_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_22_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_23                            SPP_MISC_REG_DP_GMA_CURVE_23
#define SPP_MISC_REG_DP_GMA_CURVE_23_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_23_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_23_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_23_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_23_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_23_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_23_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_23_POS))

/* 0x224 : disp_gma_curve_24 */
#define SPP_MISC_DISP_GMA_CURVE_24_OFFSET                       (0x224)
#define SPP_MISC_REG_DP_GMA_CURVE_24                            SPP_MISC_REG_DP_GMA_CURVE_24
#define SPP_MISC_REG_DP_GMA_CURVE_24_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_24_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_24_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_24_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_24_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_24_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_24_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_24_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_25                            SPP_MISC_REG_DP_GMA_CURVE_25
#define SPP_MISC_REG_DP_GMA_CURVE_25_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_25_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_25_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_25_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_25_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_25_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_25_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_25_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_26                            SPP_MISC_REG_DP_GMA_CURVE_26
#define SPP_MISC_REG_DP_GMA_CURVE_26_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_26_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_26_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_26_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_26_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_26_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_26_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_26_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_27                            SPP_MISC_REG_DP_GMA_CURVE_27
#define SPP_MISC_REG_DP_GMA_CURVE_27_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_27_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_27_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_27_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_27_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_27_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_27_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_27_POS))

/* 0x228 : disp_gma_curve_28 */
#define SPP_MISC_DISP_GMA_CURVE_28_OFFSET                       (0x228)
#define SPP_MISC_REG_DP_GMA_CURVE_28                            SPP_MISC_REG_DP_GMA_CURVE_28
#define SPP_MISC_REG_DP_GMA_CURVE_28_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_28_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_28_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_28_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_28_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_28_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_28_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_28_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_29                            SPP_MISC_REG_DP_GMA_CURVE_29
#define SPP_MISC_REG_DP_GMA_CURVE_29_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_29_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_29_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_29_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_29_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_29_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_29_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_29_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_2A                            SPP_MISC_REG_DP_GMA_CURVE_2A
#define SPP_MISC_REG_DP_GMA_CURVE_2A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_2A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_2B                            SPP_MISC_REG_DP_GMA_CURVE_2B
#define SPP_MISC_REG_DP_GMA_CURVE_2B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_2B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2B_POS))

/* 0x22C : disp_gma_curve_2c */
#define SPP_MISC_DISP_GMA_CURVE_2C_OFFSET                       (0x22C)
#define SPP_MISC_REG_DP_GMA_CURVE_2C                            SPP_MISC_REG_DP_GMA_CURVE_2C
#define SPP_MISC_REG_DP_GMA_CURVE_2C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_2C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_2D                            SPP_MISC_REG_DP_GMA_CURVE_2D
#define SPP_MISC_REG_DP_GMA_CURVE_2D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_2E                            SPP_MISC_REG_DP_GMA_CURVE_2E
#define SPP_MISC_REG_DP_GMA_CURVE_2E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_2E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_2F                            SPP_MISC_REG_DP_GMA_CURVE_2F
#define SPP_MISC_REG_DP_GMA_CURVE_2F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_2F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_2F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_2F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_2F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_2F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_2F_POS))

/* 0x230 : disp_gma_curve_30 */
#define SPP_MISC_DISP_GMA_CURVE_30_OFFSET                       (0x230)
#define SPP_MISC_REG_DP_GMA_CURVE_30                            SPP_MISC_REG_DP_GMA_CURVE_30
#define SPP_MISC_REG_DP_GMA_CURVE_30_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_30_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_30_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_30_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_30_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_30_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_30_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_30_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_31                            SPP_MISC_REG_DP_GMA_CURVE_31
#define SPP_MISC_REG_DP_GMA_CURVE_31_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_31_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_31_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_31_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_31_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_31_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_31_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_31_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_32                            SPP_MISC_REG_DP_GMA_CURVE_32
#define SPP_MISC_REG_DP_GMA_CURVE_32_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_32_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_32_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_32_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_32_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_32_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_32_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_32_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_33                            SPP_MISC_REG_DP_GMA_CURVE_33
#define SPP_MISC_REG_DP_GMA_CURVE_33_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_33_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_33_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_33_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_33_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_33_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_33_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_33_POS))

/* 0x234 : disp_gma_curve_34 */
#define SPP_MISC_DISP_GMA_CURVE_34_OFFSET                       (0x234)
#define SPP_MISC_REG_DP_GMA_CURVE_34                            SPP_MISC_REG_DP_GMA_CURVE_34
#define SPP_MISC_REG_DP_GMA_CURVE_34_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_34_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_34_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_34_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_34_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_34_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_34_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_34_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_35                            SPP_MISC_REG_DP_GMA_CURVE_35
#define SPP_MISC_REG_DP_GMA_CURVE_35_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_35_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_35_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_35_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_35_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_35_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_35_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_35_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_36                            SPP_MISC_REG_DP_GMA_CURVE_36
#define SPP_MISC_REG_DP_GMA_CURVE_36_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_36_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_36_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_36_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_36_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_36_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_36_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_36_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_37                            SPP_MISC_REG_DP_GMA_CURVE_37
#define SPP_MISC_REG_DP_GMA_CURVE_37_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_37_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_37_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_37_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_37_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_37_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_37_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_37_POS))

/* 0x238 : disp_gma_curve_38 */
#define SPP_MISC_DISP_GMA_CURVE_38_OFFSET                       (0x238)
#define SPP_MISC_REG_DP_GMA_CURVE_38                            SPP_MISC_REG_DP_GMA_CURVE_38
#define SPP_MISC_REG_DP_GMA_CURVE_38_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_38_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_38_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_38_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_38_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_38_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_38_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_38_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_39                            SPP_MISC_REG_DP_GMA_CURVE_39
#define SPP_MISC_REG_DP_GMA_CURVE_39_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_39_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_39_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_39_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_39_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_39_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_39_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_39_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_3A                            SPP_MISC_REG_DP_GMA_CURVE_3A
#define SPP_MISC_REG_DP_GMA_CURVE_3A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_3A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_3B                            SPP_MISC_REG_DP_GMA_CURVE_3B
#define SPP_MISC_REG_DP_GMA_CURVE_3B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_3B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3B_POS))

/* 0x23C : disp_gma_curve_3c */
#define SPP_MISC_DISP_GMA_CURVE_3C_OFFSET                       (0x23C)
#define SPP_MISC_REG_DP_GMA_CURVE_3C                            SPP_MISC_REG_DP_GMA_CURVE_3C
#define SPP_MISC_REG_DP_GMA_CURVE_3C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_3C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_3D                            SPP_MISC_REG_DP_GMA_CURVE_3D
#define SPP_MISC_REG_DP_GMA_CURVE_3D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_3E                            SPP_MISC_REG_DP_GMA_CURVE_3E
#define SPP_MISC_REG_DP_GMA_CURVE_3E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_3E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_3F                            SPP_MISC_REG_DP_GMA_CURVE_3F
#define SPP_MISC_REG_DP_GMA_CURVE_3F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_3F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_3F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_3F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_3F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_3F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_3F_POS))

/* 0x240 : disp_gma_curve_40 */
#define SPP_MISC_DISP_GMA_CURVE_40_OFFSET                       (0x240)
#define SPP_MISC_REG_DP_GMA_CURVE_40                            SPP_MISC_REG_DP_GMA_CURVE_40
#define SPP_MISC_REG_DP_GMA_CURVE_40_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_40_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_40_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_40_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_40_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_40_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_40_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_40_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_41                            SPP_MISC_REG_DP_GMA_CURVE_41
#define SPP_MISC_REG_DP_GMA_CURVE_41_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_41_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_41_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_41_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_41_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_41_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_41_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_41_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_42                            SPP_MISC_REG_DP_GMA_CURVE_42
#define SPP_MISC_REG_DP_GMA_CURVE_42_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_42_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_42_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_42_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_42_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_42_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_42_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_42_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_43                            SPP_MISC_REG_DP_GMA_CURVE_43
#define SPP_MISC_REG_DP_GMA_CURVE_43_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_43_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_43_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_43_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_43_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_43_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_43_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_43_POS))

/* 0x244 : disp_gma_curve_44 */
#define SPP_MISC_DISP_GMA_CURVE_44_OFFSET                       (0x244)
#define SPP_MISC_REG_DP_GMA_CURVE_44                            SPP_MISC_REG_DP_GMA_CURVE_44
#define SPP_MISC_REG_DP_GMA_CURVE_44_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_44_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_44_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_44_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_44_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_44_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_44_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_44_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_45                            SPP_MISC_REG_DP_GMA_CURVE_45
#define SPP_MISC_REG_DP_GMA_CURVE_45_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_45_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_45_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_45_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_45_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_45_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_45_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_45_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_46                            SPP_MISC_REG_DP_GMA_CURVE_46
#define SPP_MISC_REG_DP_GMA_CURVE_46_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_46_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_46_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_46_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_46_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_46_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_46_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_46_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_47                            SPP_MISC_REG_DP_GMA_CURVE_47
#define SPP_MISC_REG_DP_GMA_CURVE_47_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_47_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_47_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_47_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_47_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_47_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_47_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_47_POS))

/* 0x248 : disp_gma_curve_48 */
#define SPP_MISC_DISP_GMA_CURVE_48_OFFSET                       (0x248)
#define SPP_MISC_REG_DP_GMA_CURVE_48                            SPP_MISC_REG_DP_GMA_CURVE_48
#define SPP_MISC_REG_DP_GMA_CURVE_48_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_48_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_48_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_48_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_48_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_48_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_48_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_48_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_49                            SPP_MISC_REG_DP_GMA_CURVE_49
#define SPP_MISC_REG_DP_GMA_CURVE_49_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_49_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_49_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_49_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_49_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_49_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_49_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_49_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_4A                            SPP_MISC_REG_DP_GMA_CURVE_4A
#define SPP_MISC_REG_DP_GMA_CURVE_4A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_4A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_4B                            SPP_MISC_REG_DP_GMA_CURVE_4B
#define SPP_MISC_REG_DP_GMA_CURVE_4B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_4B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4B_POS))

/* 0x24C : disp_gma_curve_4c */
#define SPP_MISC_DISP_GMA_CURVE_4C_OFFSET                       (0x24C)
#define SPP_MISC_REG_DP_GMA_CURVE_4C                            SPP_MISC_REG_DP_GMA_CURVE_4C
#define SPP_MISC_REG_DP_GMA_CURVE_4C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_4C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_4D                            SPP_MISC_REG_DP_GMA_CURVE_4D
#define SPP_MISC_REG_DP_GMA_CURVE_4D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_4E                            SPP_MISC_REG_DP_GMA_CURVE_4E
#define SPP_MISC_REG_DP_GMA_CURVE_4E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_4E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_4F                            SPP_MISC_REG_DP_GMA_CURVE_4F
#define SPP_MISC_REG_DP_GMA_CURVE_4F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_4F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_4F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_4F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_4F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_4F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_4F_POS))

/* 0x250 : disp_gma_curve_50 */
#define SPP_MISC_DISP_GMA_CURVE_50_OFFSET                       (0x250)
#define SPP_MISC_REG_DP_GMA_CURVE_50                            SPP_MISC_REG_DP_GMA_CURVE_50
#define SPP_MISC_REG_DP_GMA_CURVE_50_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_50_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_50_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_50_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_50_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_50_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_50_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_50_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_51                            SPP_MISC_REG_DP_GMA_CURVE_51
#define SPP_MISC_REG_DP_GMA_CURVE_51_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_51_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_51_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_51_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_51_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_51_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_51_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_51_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_52                            SPP_MISC_REG_DP_GMA_CURVE_52
#define SPP_MISC_REG_DP_GMA_CURVE_52_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_52_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_52_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_52_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_52_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_52_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_52_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_52_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_53                            SPP_MISC_REG_DP_GMA_CURVE_53
#define SPP_MISC_REG_DP_GMA_CURVE_53_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_53_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_53_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_53_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_53_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_53_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_53_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_53_POS))

/* 0x254 : disp_gma_curve_54 */
#define SPP_MISC_DISP_GMA_CURVE_54_OFFSET                       (0x254)
#define SPP_MISC_REG_DP_GMA_CURVE_54                            SPP_MISC_REG_DP_GMA_CURVE_54
#define SPP_MISC_REG_DP_GMA_CURVE_54_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_54_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_54_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_54_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_54_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_54_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_54_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_54_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_55                            SPP_MISC_REG_DP_GMA_CURVE_55
#define SPP_MISC_REG_DP_GMA_CURVE_55_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_55_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_55_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_55_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_55_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_55_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_55_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_55_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_56                            SPP_MISC_REG_DP_GMA_CURVE_56
#define SPP_MISC_REG_DP_GMA_CURVE_56_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_56_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_56_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_56_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_56_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_56_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_56_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_56_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_57                            SPP_MISC_REG_DP_GMA_CURVE_57
#define SPP_MISC_REG_DP_GMA_CURVE_57_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_57_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_57_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_57_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_57_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_57_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_57_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_57_POS))

/* 0x258 : disp_gma_curve_58 */
#define SPP_MISC_DISP_GMA_CURVE_58_OFFSET                       (0x258)
#define SPP_MISC_REG_DP_GMA_CURVE_58                            SPP_MISC_REG_DP_GMA_CURVE_58
#define SPP_MISC_REG_DP_GMA_CURVE_58_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_58_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_58_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_58_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_58_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_58_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_58_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_58_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_59                            SPP_MISC_REG_DP_GMA_CURVE_59
#define SPP_MISC_REG_DP_GMA_CURVE_59_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_59_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_59_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_59_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_59_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_59_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_59_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_59_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_5A                            SPP_MISC_REG_DP_GMA_CURVE_5A
#define SPP_MISC_REG_DP_GMA_CURVE_5A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_5A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_5B                            SPP_MISC_REG_DP_GMA_CURVE_5B
#define SPP_MISC_REG_DP_GMA_CURVE_5B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_5B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5B_POS))

/* 0x25C : disp_gma_curve_5c */
#define SPP_MISC_DISP_GMA_CURVE_5C_OFFSET                       (0x25C)
#define SPP_MISC_REG_DP_GMA_CURVE_5C                            SPP_MISC_REG_DP_GMA_CURVE_5C
#define SPP_MISC_REG_DP_GMA_CURVE_5C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_5C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_5D                            SPP_MISC_REG_DP_GMA_CURVE_5D
#define SPP_MISC_REG_DP_GMA_CURVE_5D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_5E                            SPP_MISC_REG_DP_GMA_CURVE_5E
#define SPP_MISC_REG_DP_GMA_CURVE_5E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_5E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_5F                            SPP_MISC_REG_DP_GMA_CURVE_5F
#define SPP_MISC_REG_DP_GMA_CURVE_5F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_5F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_5F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_5F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_5F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_5F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_5F_POS))

/* 0x260 : disp_gma_curve_60 */
#define SPP_MISC_DISP_GMA_CURVE_60_OFFSET                       (0x260)
#define SPP_MISC_REG_DP_GMA_CURVE_60                            SPP_MISC_REG_DP_GMA_CURVE_60
#define SPP_MISC_REG_DP_GMA_CURVE_60_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_60_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_60_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_60_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_60_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_60_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_60_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_60_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_61                            SPP_MISC_REG_DP_GMA_CURVE_61
#define SPP_MISC_REG_DP_GMA_CURVE_61_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_61_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_61_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_61_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_61_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_61_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_61_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_61_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_62                            SPP_MISC_REG_DP_GMA_CURVE_62
#define SPP_MISC_REG_DP_GMA_CURVE_62_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_62_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_62_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_62_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_62_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_62_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_62_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_62_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_63                            SPP_MISC_REG_DP_GMA_CURVE_63
#define SPP_MISC_REG_DP_GMA_CURVE_63_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_63_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_63_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_63_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_63_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_63_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_63_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_63_POS))

/* 0x264 : disp_gma_curve_64 */
#define SPP_MISC_DISP_GMA_CURVE_64_OFFSET                       (0x264)
#define SPP_MISC_REG_DP_GMA_CURVE_64                            SPP_MISC_REG_DP_GMA_CURVE_64
#define SPP_MISC_REG_DP_GMA_CURVE_64_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_64_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_64_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_64_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_64_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_64_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_64_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_64_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_65                            SPP_MISC_REG_DP_GMA_CURVE_65
#define SPP_MISC_REG_DP_GMA_CURVE_65_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_65_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_65_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_65_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_65_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_65_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_65_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_65_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_66                            SPP_MISC_REG_DP_GMA_CURVE_66
#define SPP_MISC_REG_DP_GMA_CURVE_66_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_66_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_66_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_66_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_66_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_66_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_66_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_66_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_67                            SPP_MISC_REG_DP_GMA_CURVE_67
#define SPP_MISC_REG_DP_GMA_CURVE_67_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_67_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_67_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_67_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_67_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_67_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_67_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_67_POS))

/* 0x268 : disp_gma_curve_68 */
#define SPP_MISC_DISP_GMA_CURVE_68_OFFSET                       (0x268)
#define SPP_MISC_REG_DP_GMA_CURVE_68                            SPP_MISC_REG_DP_GMA_CURVE_68
#define SPP_MISC_REG_DP_GMA_CURVE_68_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_68_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_68_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_68_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_68_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_68_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_68_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_68_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_69                            SPP_MISC_REG_DP_GMA_CURVE_69
#define SPP_MISC_REG_DP_GMA_CURVE_69_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_69_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_69_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_69_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_69_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_69_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_69_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_69_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_6A                            SPP_MISC_REG_DP_GMA_CURVE_6A
#define SPP_MISC_REG_DP_GMA_CURVE_6A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_6A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_6B                            SPP_MISC_REG_DP_GMA_CURVE_6B
#define SPP_MISC_REG_DP_GMA_CURVE_6B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_6B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6B_POS))

/* 0x26C : disp_gma_curve_6c */
#define SPP_MISC_DISP_GMA_CURVE_6C_OFFSET                       (0x26C)
#define SPP_MISC_REG_DP_GMA_CURVE_6C                            SPP_MISC_REG_DP_GMA_CURVE_6C
#define SPP_MISC_REG_DP_GMA_CURVE_6C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_6C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_6D                            SPP_MISC_REG_DP_GMA_CURVE_6D
#define SPP_MISC_REG_DP_GMA_CURVE_6D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_6E                            SPP_MISC_REG_DP_GMA_CURVE_6E
#define SPP_MISC_REG_DP_GMA_CURVE_6E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_6E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_6F                            SPP_MISC_REG_DP_GMA_CURVE_6F
#define SPP_MISC_REG_DP_GMA_CURVE_6F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_6F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_6F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_6F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_6F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_6F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_6F_POS))

/* 0x270 : disp_gma_curve_70 */
#define SPP_MISC_DISP_GMA_CURVE_70_OFFSET                       (0x270)
#define SPP_MISC_REG_DP_GMA_CURVE_70                            SPP_MISC_REG_DP_GMA_CURVE_70
#define SPP_MISC_REG_DP_GMA_CURVE_70_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_70_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_70_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_70_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_70_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_70_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_70_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_70_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_71                            SPP_MISC_REG_DP_GMA_CURVE_71
#define SPP_MISC_REG_DP_GMA_CURVE_71_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_71_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_71_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_71_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_71_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_71_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_71_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_71_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_72                            SPP_MISC_REG_DP_GMA_CURVE_72
#define SPP_MISC_REG_DP_GMA_CURVE_72_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_72_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_72_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_72_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_72_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_72_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_72_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_72_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_73                            SPP_MISC_REG_DP_GMA_CURVE_73
#define SPP_MISC_REG_DP_GMA_CURVE_73_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_73_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_73_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_73_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_73_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_73_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_73_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_73_POS))

/* 0x274 : disp_gma_curve_74 */
#define SPP_MISC_DISP_GMA_CURVE_74_OFFSET                       (0x274)
#define SPP_MISC_REG_DP_GMA_CURVE_74                            SPP_MISC_REG_DP_GMA_CURVE_74
#define SPP_MISC_REG_DP_GMA_CURVE_74_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_74_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_74_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_74_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_74_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_74_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_74_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_74_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_75                            SPP_MISC_REG_DP_GMA_CURVE_75
#define SPP_MISC_REG_DP_GMA_CURVE_75_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_75_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_75_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_75_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_75_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_75_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_75_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_75_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_76                            SPP_MISC_REG_DP_GMA_CURVE_76
#define SPP_MISC_REG_DP_GMA_CURVE_76_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_76_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_76_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_76_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_76_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_76_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_76_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_76_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_77                            SPP_MISC_REG_DP_GMA_CURVE_77
#define SPP_MISC_REG_DP_GMA_CURVE_77_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_77_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_77_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_77_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_77_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_77_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_77_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_77_POS))

/* 0x278 : disp_gma_curve_78 */
#define SPP_MISC_DISP_GMA_CURVE_78_OFFSET                       (0x278)
#define SPP_MISC_REG_DP_GMA_CURVE_78                            SPP_MISC_REG_DP_GMA_CURVE_78
#define SPP_MISC_REG_DP_GMA_CURVE_78_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_78_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_78_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_78_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_78_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_78_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_78_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_78_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_79                            SPP_MISC_REG_DP_GMA_CURVE_79
#define SPP_MISC_REG_DP_GMA_CURVE_79_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_79_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_79_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_79_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_79_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_79_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_79_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_79_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_7A                            SPP_MISC_REG_DP_GMA_CURVE_7A
#define SPP_MISC_REG_DP_GMA_CURVE_7A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_7A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_7B                            SPP_MISC_REG_DP_GMA_CURVE_7B
#define SPP_MISC_REG_DP_GMA_CURVE_7B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_7B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7B_POS))

/* 0x27C : disp_gma_curve_7c */
#define SPP_MISC_DISP_GMA_CURVE_7C_OFFSET                       (0x27C)
#define SPP_MISC_REG_DP_GMA_CURVE_7C                            SPP_MISC_REG_DP_GMA_CURVE_7C
#define SPP_MISC_REG_DP_GMA_CURVE_7C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_7C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_7D                            SPP_MISC_REG_DP_GMA_CURVE_7D
#define SPP_MISC_REG_DP_GMA_CURVE_7D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_7E                            SPP_MISC_REG_DP_GMA_CURVE_7E
#define SPP_MISC_REG_DP_GMA_CURVE_7E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_7E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_7F                            SPP_MISC_REG_DP_GMA_CURVE_7F
#define SPP_MISC_REG_DP_GMA_CURVE_7F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_7F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_7F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_7F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_7F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_7F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_7F_POS))

/* 0x280 : disp_gma_curve_80 */
#define SPP_MISC_DISP_GMA_CURVE_80_OFFSET                       (0x280)
#define SPP_MISC_REG_DP_GMA_CURVE_80                            SPP_MISC_REG_DP_GMA_CURVE_80
#define SPP_MISC_REG_DP_GMA_CURVE_80_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_80_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_80_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_80_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_80_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_80_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_80_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_80_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_81                            SPP_MISC_REG_DP_GMA_CURVE_81
#define SPP_MISC_REG_DP_GMA_CURVE_81_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_81_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_81_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_81_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_81_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_81_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_81_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_81_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_82                            SPP_MISC_REG_DP_GMA_CURVE_82
#define SPP_MISC_REG_DP_GMA_CURVE_82_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_82_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_82_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_82_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_82_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_82_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_82_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_82_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_83                            SPP_MISC_REG_DP_GMA_CURVE_83
#define SPP_MISC_REG_DP_GMA_CURVE_83_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_83_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_83_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_83_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_83_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_83_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_83_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_83_POS))

/* 0x284 : disp_gma_curve_84 */
#define SPP_MISC_DISP_GMA_CURVE_84_OFFSET                       (0x284)
#define SPP_MISC_REG_DP_GMA_CURVE_84                            SPP_MISC_REG_DP_GMA_CURVE_84
#define SPP_MISC_REG_DP_GMA_CURVE_84_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_84_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_84_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_84_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_84_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_84_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_84_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_84_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_85                            SPP_MISC_REG_DP_GMA_CURVE_85
#define SPP_MISC_REG_DP_GMA_CURVE_85_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_85_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_85_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_85_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_85_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_85_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_85_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_85_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_86                            SPP_MISC_REG_DP_GMA_CURVE_86
#define SPP_MISC_REG_DP_GMA_CURVE_86_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_86_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_86_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_86_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_86_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_86_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_86_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_86_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_87                            SPP_MISC_REG_DP_GMA_CURVE_87
#define SPP_MISC_REG_DP_GMA_CURVE_87_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_87_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_87_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_87_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_87_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_87_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_87_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_87_POS))

/* 0x288 : disp_gma_curve_88 */
#define SPP_MISC_DISP_GMA_CURVE_88_OFFSET                       (0x288)
#define SPP_MISC_REG_DP_GMA_CURVE_88                            SPP_MISC_REG_DP_GMA_CURVE_88
#define SPP_MISC_REG_DP_GMA_CURVE_88_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_88_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_88_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_88_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_88_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_88_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_88_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_88_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_89                            SPP_MISC_REG_DP_GMA_CURVE_89
#define SPP_MISC_REG_DP_GMA_CURVE_89_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_89_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_89_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_89_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_89_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_89_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_89_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_89_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_8A                            SPP_MISC_REG_DP_GMA_CURVE_8A
#define SPP_MISC_REG_DP_GMA_CURVE_8A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_8A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_8B                            SPP_MISC_REG_DP_GMA_CURVE_8B
#define SPP_MISC_REG_DP_GMA_CURVE_8B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_8B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8B_POS))

/* 0x28C : disp_gma_curve_8c */
#define SPP_MISC_DISP_GMA_CURVE_8C_OFFSET                       (0x28C)
#define SPP_MISC_REG_DP_GMA_CURVE_8C                            SPP_MISC_REG_DP_GMA_CURVE_8C
#define SPP_MISC_REG_DP_GMA_CURVE_8C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_8C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_8D                            SPP_MISC_REG_DP_GMA_CURVE_8D
#define SPP_MISC_REG_DP_GMA_CURVE_8D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_8E                            SPP_MISC_REG_DP_GMA_CURVE_8E
#define SPP_MISC_REG_DP_GMA_CURVE_8E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_8E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_8F                            SPP_MISC_REG_DP_GMA_CURVE_8F
#define SPP_MISC_REG_DP_GMA_CURVE_8F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_8F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_8F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_8F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_8F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_8F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_8F_POS))

/* 0x290 : disp_gma_curve_90 */
#define SPP_MISC_DISP_GMA_CURVE_90_OFFSET                       (0x290)
#define SPP_MISC_REG_DP_GMA_CURVE_90                            SPP_MISC_REG_DP_GMA_CURVE_90
#define SPP_MISC_REG_DP_GMA_CURVE_90_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_90_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_90_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_90_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_90_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_90_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_90_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_90_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_91                            SPP_MISC_REG_DP_GMA_CURVE_91
#define SPP_MISC_REG_DP_GMA_CURVE_91_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_91_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_91_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_91_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_91_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_91_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_91_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_91_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_92                            SPP_MISC_REG_DP_GMA_CURVE_92
#define SPP_MISC_REG_DP_GMA_CURVE_92_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_92_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_92_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_92_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_92_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_92_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_92_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_92_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_93                            SPP_MISC_REG_DP_GMA_CURVE_93
#define SPP_MISC_REG_DP_GMA_CURVE_93_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_93_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_93_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_93_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_93_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_93_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_93_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_93_POS))

/* 0x294 : disp_gma_curve_94 */
#define SPP_MISC_DISP_GMA_CURVE_94_OFFSET                       (0x294)
#define SPP_MISC_REG_DP_GMA_CURVE_94                            SPP_MISC_REG_DP_GMA_CURVE_94
#define SPP_MISC_REG_DP_GMA_CURVE_94_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_94_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_94_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_94_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_94_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_94_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_94_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_94_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_95                            SPP_MISC_REG_DP_GMA_CURVE_95
#define SPP_MISC_REG_DP_GMA_CURVE_95_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_95_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_95_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_95_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_95_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_95_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_95_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_95_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_96                            SPP_MISC_REG_DP_GMA_CURVE_96
#define SPP_MISC_REG_DP_GMA_CURVE_96_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_96_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_96_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_96_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_96_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_96_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_96_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_96_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_97                            SPP_MISC_REG_DP_GMA_CURVE_97
#define SPP_MISC_REG_DP_GMA_CURVE_97_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_97_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_97_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_97_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_97_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_97_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_97_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_97_POS))

/* 0x298 : disp_gma_curve_98 */
#define SPP_MISC_DISP_GMA_CURVE_98_OFFSET                       (0x298)
#define SPP_MISC_REG_DP_GMA_CURVE_98                            SPP_MISC_REG_DP_GMA_CURVE_98
#define SPP_MISC_REG_DP_GMA_CURVE_98_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_98_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_98_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_98_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_98_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_98_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_98_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_98_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_99                            SPP_MISC_REG_DP_GMA_CURVE_99
#define SPP_MISC_REG_DP_GMA_CURVE_99_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_99_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_99_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_99_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_99_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_99_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_99_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_99_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_9A                            SPP_MISC_REG_DP_GMA_CURVE_9A
#define SPP_MISC_REG_DP_GMA_CURVE_9A_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_9A_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9A_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9A_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9A_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9A_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9A_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_9B                            SPP_MISC_REG_DP_GMA_CURVE_9B
#define SPP_MISC_REG_DP_GMA_CURVE_9B_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_9B_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9B_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9B_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9B_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9B_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9B_POS))

/* 0x29C : disp_gma_curve_9c */
#define SPP_MISC_DISP_GMA_CURVE_9C_OFFSET                       (0x29C)
#define SPP_MISC_REG_DP_GMA_CURVE_9C                            SPP_MISC_REG_DP_GMA_CURVE_9C
#define SPP_MISC_REG_DP_GMA_CURVE_9C_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_9C_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9C_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9C_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9C_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9C_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9C_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_9D                            SPP_MISC_REG_DP_GMA_CURVE_9D
#define SPP_MISC_REG_DP_GMA_CURVE_9D_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9D_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9D_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9D_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9D_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9D_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9D_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_9E                            SPP_MISC_REG_DP_GMA_CURVE_9E
#define SPP_MISC_REG_DP_GMA_CURVE_9E_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_9E_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9E_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9E_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9E_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9E_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9E_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_9F                            SPP_MISC_REG_DP_GMA_CURVE_9F
#define SPP_MISC_REG_DP_GMA_CURVE_9F_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_9F_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_9F_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_9F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9F_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_9F_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_9F_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_9F_POS))

/* 0x2A0 : disp_gma_curve_a0 */
#define SPP_MISC_DISP_GMA_CURVE_A0_OFFSET                       (0x2A0)
#define SPP_MISC_REG_DP_GMA_CURVE_A0                            SPP_MISC_REG_DP_GMA_CURVE_A0
#define SPP_MISC_REG_DP_GMA_CURVE_A0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_A0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A1                            SPP_MISC_REG_DP_GMA_CURVE_A1
#define SPP_MISC_REG_DP_GMA_CURVE_A1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A2                            SPP_MISC_REG_DP_GMA_CURVE_A2
#define SPP_MISC_REG_DP_GMA_CURVE_A2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_A2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A3                            SPP_MISC_REG_DP_GMA_CURVE_A3
#define SPP_MISC_REG_DP_GMA_CURVE_A3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_A3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A3_POS))

/* 0x2A4 : disp_gma_curve_a4 */
#define SPP_MISC_DISP_GMA_CURVE_A4_OFFSET                       (0x2A4)
#define SPP_MISC_REG_DP_GMA_CURVE_A4                            SPP_MISC_REG_DP_GMA_CURVE_A4
#define SPP_MISC_REG_DP_GMA_CURVE_A4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_A4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A5                            SPP_MISC_REG_DP_GMA_CURVE_A5
#define SPP_MISC_REG_DP_GMA_CURVE_A5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A6                            SPP_MISC_REG_DP_GMA_CURVE_A6
#define SPP_MISC_REG_DP_GMA_CURVE_A6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_A6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A7                            SPP_MISC_REG_DP_GMA_CURVE_A7
#define SPP_MISC_REG_DP_GMA_CURVE_A7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_A7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A7_POS))

/* 0x2A8 : disp_gma_curve_a8 */
#define SPP_MISC_DISP_GMA_CURVE_A8_OFFSET                       (0x2A8)
#define SPP_MISC_REG_DP_GMA_CURVE_A8                            SPP_MISC_REG_DP_GMA_CURVE_A8
#define SPP_MISC_REG_DP_GMA_CURVE_A8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_A8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_A9                            SPP_MISC_REG_DP_GMA_CURVE_A9
#define SPP_MISC_REG_DP_GMA_CURVE_A9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_A9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_A9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_A9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_A9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_A9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_AA                            SPP_MISC_REG_DP_GMA_CURVE_AA
#define SPP_MISC_REG_DP_GMA_CURVE_AA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_AA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_AA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_AA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_AA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_AB                            SPP_MISC_REG_DP_GMA_CURVE_AB
#define SPP_MISC_REG_DP_GMA_CURVE_AB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_AB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_AB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_AB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_AB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AB_POS))

/* 0x2AC : disp_gma_curve_ac */
#define SPP_MISC_DISP_GMA_CURVE_AC_OFFSET                       (0x2AC)
#define SPP_MISC_REG_DP_GMA_CURVE_AC                            SPP_MISC_REG_DP_GMA_CURVE_AC
#define SPP_MISC_REG_DP_GMA_CURVE_AC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_AC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_AC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_AC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_AC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_AD                            SPP_MISC_REG_DP_GMA_CURVE_AD
#define SPP_MISC_REG_DP_GMA_CURVE_AD_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AD_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AD_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_AD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AD_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_AD_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_AD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AD_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_RESERVEA                            SPP_MISC_REG_DP_GMA_CURVE_RESERVEA
#define SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_RESERVEA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_AF                            SPP_MISC_REG_DP_GMA_CURVE_AF
#define SPP_MISC_REG_DP_GMA_CURVE_AF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_AF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_AF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_AF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_AF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_AF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_AF_POS))

/* 0x2B0 : disp_gma_curve_b0 */
#define SPP_MISC_DISP_GMA_CURVE_B0_OFFSET                       (0x2B0)
#define SPP_MISC_REG_DP_GMA_CURVE_B0                            SPP_MISC_REG_DP_GMA_CURVE_B0
#define SPP_MISC_REG_DP_GMA_CURVE_B0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_B0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B1                            SPP_MISC_REG_DP_GMA_CURVE_B1
#define SPP_MISC_REG_DP_GMA_CURVE_B1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B2                            SPP_MISC_REG_DP_GMA_CURVE_B2
#define SPP_MISC_REG_DP_GMA_CURVE_B2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_B2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B3                            SPP_MISC_REG_DP_GMA_CURVE_B3
#define SPP_MISC_REG_DP_GMA_CURVE_B3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_B3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B3_POS))

/* 0x2B4 : disp_gma_curve_b4 */
#define SPP_MISC_DISP_GMA_CURVE_B4_OFFSET                       (0x2B4)
#define SPP_MISC_REG_DP_GMA_CURVE_B4                            SPP_MISC_REG_DP_GMA_CURVE_B4
#define SPP_MISC_REG_DP_GMA_CURVE_B4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_B4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B5                            SPP_MISC_REG_DP_GMA_CURVE_B5
#define SPP_MISC_REG_DP_GMA_CURVE_B5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B6                            SPP_MISC_REG_DP_GMA_CURVE_B6
#define SPP_MISC_REG_DP_GMA_CURVE_B6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_B6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B7                            SPP_MISC_REG_DP_GMA_CURVE_B7
#define SPP_MISC_REG_DP_GMA_CURVE_B7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_B7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B7_POS))

/* 0x2B8 : disp_gma_curve_b8 */
#define SPP_MISC_DISP_GMA_CURVE_B8_OFFSET                       (0x2B8)
#define SPP_MISC_REG_DP_GMA_CURVE_B8                            SPP_MISC_REG_DP_GMA_CURVE_B8
#define SPP_MISC_REG_DP_GMA_CURVE_B8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_B8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_B9                            SPP_MISC_REG_DP_GMA_CURVE_B9
#define SPP_MISC_REG_DP_GMA_CURVE_B9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_B9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_B9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_B9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_B9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_B9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_BA                            SPP_MISC_REG_DP_GMA_CURVE_BA
#define SPP_MISC_REG_DP_GMA_CURVE_BA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_BA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_BB                            SPP_MISC_REG_DP_GMA_CURVE_BB
#define SPP_MISC_REG_DP_GMA_CURVE_BB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_BB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BB_POS))

/* 0x2BC : disp_gma_curve_bc */
#define SPP_MISC_DISP_GMA_CURVE_BC_OFFSET                       (0x2BC)
#define SPP_MISC_REG_DP_GMA_CURVE_BC                            SPP_MISC_REG_DP_GMA_CURVE_BC
#define SPP_MISC_REG_DP_GMA_CURVE_BC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_BC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_BD                            SPP_MISC_REG_DP_GMA_CURVE_BD
#define SPP_MISC_REG_DP_GMA_CURVE_BD_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BD_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BD_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BD_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BD_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BD_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_BE                            SPP_MISC_REG_DP_GMA_CURVE_BE
#define SPP_MISC_REG_DP_GMA_CURVE_BE_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_BE_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BE_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BE_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BE_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BE_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_BF                            SPP_MISC_REG_DP_GMA_CURVE_BF
#define SPP_MISC_REG_DP_GMA_CURVE_BF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_BF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_BF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_BF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_BF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_BF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_BF_POS))

/* 0x2C0 : disp_gma_curve_c0 */
#define SPP_MISC_DISP_GMA_CURVE_C0_OFFSET                       (0x2C0)
#define SPP_MISC_REG_DP_GMA_CURVE_C0                            SPP_MISC_REG_DP_GMA_CURVE_C0
#define SPP_MISC_REG_DP_GMA_CURVE_C0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_C0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C1                            SPP_MISC_REG_DP_GMA_CURVE_C1
#define SPP_MISC_REG_DP_GMA_CURVE_C1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C2                            SPP_MISC_REG_DP_GMA_CURVE_C2
#define SPP_MISC_REG_DP_GMA_CURVE_C2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_C2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C3                            SPP_MISC_REG_DP_GMA_CURVE_C3
#define SPP_MISC_REG_DP_GMA_CURVE_C3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_C3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C3_POS))

/* 0x2C4 : disp_gma_curve_c4 */
#define SPP_MISC_DISP_GMA_CURVE_C4_OFFSET                       (0x2C4)
#define SPP_MISC_REG_DP_GMA_CURVE_C4                            SPP_MISC_REG_DP_GMA_CURVE_C4
#define SPP_MISC_REG_DP_GMA_CURVE_C4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_C4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C5                            SPP_MISC_REG_DP_GMA_CURVE_C5
#define SPP_MISC_REG_DP_GMA_CURVE_C5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C6                            SPP_MISC_REG_DP_GMA_CURVE_C6
#define SPP_MISC_REG_DP_GMA_CURVE_C6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_C6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C7                            SPP_MISC_REG_DP_GMA_CURVE_C7
#define SPP_MISC_REG_DP_GMA_CURVE_C7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_C7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C7_POS))

/* 0x2C8 : disp_gma_curve_c8 */
#define SPP_MISC_DISP_GMA_CURVE_C8_OFFSET                       (0x2C8)
#define SPP_MISC_REG_DP_GMA_CURVE_C8                            SPP_MISC_REG_DP_GMA_CURVE_C8
#define SPP_MISC_REG_DP_GMA_CURVE_C8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_C8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_C9                            SPP_MISC_REG_DP_GMA_CURVE_C9
#define SPP_MISC_REG_DP_GMA_CURVE_C9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_C9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_C9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_C9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_C9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_C9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_CA                            SPP_MISC_REG_DP_GMA_CURVE_CA
#define SPP_MISC_REG_DP_GMA_CURVE_CA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_CA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_CB                            SPP_MISC_REG_DP_GMA_CURVE_CB
#define SPP_MISC_REG_DP_GMA_CURVE_CB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_CB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CB_POS))

/* 0x2CC : disp_gma_curve_cc */
#define SPP_MISC_DISP_GMA_CURVE_CC_OFFSET                       (0x2CC)
#define SPP_MISC_REG_DP_GMA_CURVE_CC                            SPP_MISC_REG_DP_GMA_CURVE_CC
#define SPP_MISC_REG_DP_GMA_CURVE_CC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_CC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_CD                            SPP_MISC_REG_DP_GMA_CURVE_CD
#define SPP_MISC_REG_DP_GMA_CURVE_CD_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CD_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CD_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CD_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CD_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CD_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_CE                            SPP_MISC_REG_DP_GMA_CURVE_CE
#define SPP_MISC_REG_DP_GMA_CURVE_CE_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_CE_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CE_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CE_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CE_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CE_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_CF                            SPP_MISC_REG_DP_GMA_CURVE_CF
#define SPP_MISC_REG_DP_GMA_CURVE_CF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_CF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_CF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_CF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_CF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_CF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_CF_POS))

/* 0x2D0 : disp_gma_curve_d0 */
#define SPP_MISC_DISP_GMA_CURVE_D0_OFFSET                       (0x2D0)
#define SPP_MISC_REG_DP_GMA_CURVE_D0                            SPP_MISC_REG_DP_GMA_CURVE_D0
#define SPP_MISC_REG_DP_GMA_CURVE_D0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_D0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D1                            SPP_MISC_REG_DP_GMA_CURVE_D1
#define SPP_MISC_REG_DP_GMA_CURVE_D1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D2                            SPP_MISC_REG_DP_GMA_CURVE_D2
#define SPP_MISC_REG_DP_GMA_CURVE_D2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_D2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D3                            SPP_MISC_REG_DP_GMA_CURVE_D3
#define SPP_MISC_REG_DP_GMA_CURVE_D3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_D3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D3_POS))

/* 0x2D4 : disp_gma_curve_d4 */
#define SPP_MISC_DISP_GMA_CURVE_D4_OFFSET                       (0x2D4)
#define SPP_MISC_REG_DP_GMA_CURVE_D4                            SPP_MISC_REG_DP_GMA_CURVE_D4
#define SPP_MISC_REG_DP_GMA_CURVE_D4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_D4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D5                            SPP_MISC_REG_DP_GMA_CURVE_D5
#define SPP_MISC_REG_DP_GMA_CURVE_D5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D6                            SPP_MISC_REG_DP_GMA_CURVE_D6
#define SPP_MISC_REG_DP_GMA_CURVE_D6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_D6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D7                            SPP_MISC_REG_DP_GMA_CURVE_D7
#define SPP_MISC_REG_DP_GMA_CURVE_D7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_D7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D7_POS))

/* 0x2D8 : disp_gma_curve_d8 */
#define SPP_MISC_DISP_GMA_CURVE_D8_OFFSET                       (0x2D8)
#define SPP_MISC_REG_DP_GMA_CURVE_D8                            SPP_MISC_REG_DP_GMA_CURVE_D8
#define SPP_MISC_REG_DP_GMA_CURVE_D8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_D8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_D9                            SPP_MISC_REG_DP_GMA_CURVE_D9
#define SPP_MISC_REG_DP_GMA_CURVE_D9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_D9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_D9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_D9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_D9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_D9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_DA                            SPP_MISC_REG_DP_GMA_CURVE_DA
#define SPP_MISC_REG_DP_GMA_CURVE_DA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_DA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_DB                            SPP_MISC_REG_DP_GMA_CURVE_DB
#define SPP_MISC_REG_DP_GMA_CURVE_DB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_DB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DB_POS))

/* 0x2DC : disp_gma_curve_dc */
#define SPP_MISC_DISP_GMA_CURVE_DC_OFFSET                       (0x2DC)
#define SPP_MISC_REG_DP_GMA_CURVE_DC                            SPP_MISC_REG_DP_GMA_CURVE_DC
#define SPP_MISC_REG_DP_GMA_CURVE_DC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_DC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_DD                            SPP_MISC_REG_DP_GMA_CURVE_DD
#define SPP_MISC_REG_DP_GMA_CURVE_DD_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DD_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DD_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DD_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DD_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DD_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_DE                            SPP_MISC_REG_DP_GMA_CURVE_DE
#define SPP_MISC_REG_DP_GMA_CURVE_DE_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_DE_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DE_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DE_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DE_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DE_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_DF                            SPP_MISC_REG_DP_GMA_CURVE_DF
#define SPP_MISC_REG_DP_GMA_CURVE_DF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_DF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_DF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_DF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_DF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_DF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_DF_POS))

/* 0x2E0 : disp_gma_curve_e0 */
#define SPP_MISC_DISP_GMA_CURVE_E0_OFFSET                       (0x2E0)
#define SPP_MISC_REG_DP_GMA_CURVE_E0                            SPP_MISC_REG_DP_GMA_CURVE_E0
#define SPP_MISC_REG_DP_GMA_CURVE_E0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_E0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E1                            SPP_MISC_REG_DP_GMA_CURVE_E1
#define SPP_MISC_REG_DP_GMA_CURVE_E1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E2                            SPP_MISC_REG_DP_GMA_CURVE_E2
#define SPP_MISC_REG_DP_GMA_CURVE_E2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_E2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E3                            SPP_MISC_REG_DP_GMA_CURVE_E3
#define SPP_MISC_REG_DP_GMA_CURVE_E3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_E3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E3_POS))

/* 0x2E4 : disp_gma_curve_e4 */
#define SPP_MISC_DISP_GMA_CURVE_E4_OFFSET                       (0x2E4)
#define SPP_MISC_REG_DP_GMA_CURVE_E4                            SPP_MISC_REG_DP_GMA_CURVE_E4
#define SPP_MISC_REG_DP_GMA_CURVE_E4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_E4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E5                            SPP_MISC_REG_DP_GMA_CURVE_E5
#define SPP_MISC_REG_DP_GMA_CURVE_E5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E6                            SPP_MISC_REG_DP_GMA_CURVE_E6
#define SPP_MISC_REG_DP_GMA_CURVE_E6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_E6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E7                            SPP_MISC_REG_DP_GMA_CURVE_E7
#define SPP_MISC_REG_DP_GMA_CURVE_E7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_E7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E7_POS))

/* 0x2E8 : disp_gma_curve_e8 */
#define SPP_MISC_DISP_GMA_CURVE_E8_OFFSET                       (0x2E8)
#define SPP_MISC_REG_DP_GMA_CURVE_E8                            SPP_MISC_REG_DP_GMA_CURVE_E8
#define SPP_MISC_REG_DP_GMA_CURVE_E8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_E8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_E9                            SPP_MISC_REG_DP_GMA_CURVE_E9
#define SPP_MISC_REG_DP_GMA_CURVE_E9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_E9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_E9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_E9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_E9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_E9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_EA                            SPP_MISC_REG_DP_GMA_CURVE_EA
#define SPP_MISC_REG_DP_GMA_CURVE_EA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_EA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_EA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_EA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_EA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_EA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_EB                            SPP_MISC_REG_DP_GMA_CURVE_EB
#define SPP_MISC_REG_DP_GMA_CURVE_EB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_EB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_EB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_EB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_EB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_EB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EB_POS))

/* 0x2EC : disp_gma_curve_ec */
#define SPP_MISC_DISP_GMA_CURVE_EC_OFFSET                       (0x2EC)
#define SPP_MISC_REG_DP_GMA_CURVE_EC                            SPP_MISC_REG_DP_GMA_CURVE_EC
#define SPP_MISC_REG_DP_GMA_CURVE_EC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_EC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_EC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_EC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_EC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_EC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_ED                            SPP_MISC_REG_DP_GMA_CURVE_ED
#define SPP_MISC_REG_DP_GMA_CURVE_ED_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_ED_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_ED_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_ED_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_ED_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_ED_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_ED_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_ED_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_EE                            SPP_MISC_REG_DP_GMA_CURVE_EE
#define SPP_MISC_REG_DP_GMA_CURVE_EE_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_EE_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_EE_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_EE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EE_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_EE_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_EE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EE_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_EF                            SPP_MISC_REG_DP_GMA_CURVE_EF
#define SPP_MISC_REG_DP_GMA_CURVE_EF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_EF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_EF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_EF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_EF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_EF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_EF_POS))

/* 0x2F0 : disp_gma_curve_f0 */
#define SPP_MISC_DISP_GMA_CURVE_F0_OFFSET                       (0x2F0)
#define SPP_MISC_REG_DP_GMA_CURVE_F0                            SPP_MISC_REG_DP_GMA_CURVE_F0
#define SPP_MISC_REG_DP_GMA_CURVE_F0_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_F0_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F0_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F0_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F0_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F0_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F0_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F1                            SPP_MISC_REG_DP_GMA_CURVE_F1
#define SPP_MISC_REG_DP_GMA_CURVE_F1_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F1_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F1_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F1_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F1_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F1_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F1_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F2                            SPP_MISC_REG_DP_GMA_CURVE_F2
#define SPP_MISC_REG_DP_GMA_CURVE_F2_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_F2_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F2_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F2_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F2_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F2_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F2_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F3                            SPP_MISC_REG_DP_GMA_CURVE_F3
#define SPP_MISC_REG_DP_GMA_CURVE_F3_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_F3_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F3_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F3_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F3_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F3_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F3_POS))

/* 0x2F4 : disp_gma_curve_f4 */
#define SPP_MISC_DISP_GMA_CURVE_F4_OFFSET                       (0x2F4)
#define SPP_MISC_REG_DP_GMA_CURVE_F4                            SPP_MISC_REG_DP_GMA_CURVE_F4
#define SPP_MISC_REG_DP_GMA_CURVE_F4_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_F4_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F4_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F4_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F4_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F4_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F4_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F5                            SPP_MISC_REG_DP_GMA_CURVE_F5
#define SPP_MISC_REG_DP_GMA_CURVE_F5_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F5_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F5_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F5_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F5_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F5_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F5_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F6                            SPP_MISC_REG_DP_GMA_CURVE_F6
#define SPP_MISC_REG_DP_GMA_CURVE_F6_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_F6_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F6_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F6_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F6_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F6_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F6_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F7                            SPP_MISC_REG_DP_GMA_CURVE_F7
#define SPP_MISC_REG_DP_GMA_CURVE_F7_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_F7_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F7_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F7_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F7_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F7_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F7_POS))

/* 0x2F8 : disp_gma_curve_f8 */
#define SPP_MISC_DISP_GMA_CURVE_F8_OFFSET                       (0x2F8)
#define SPP_MISC_REG_DP_GMA_CURVE_F8                            SPP_MISC_REG_DP_GMA_CURVE_F8
#define SPP_MISC_REG_DP_GMA_CURVE_F8_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_F8_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F8_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F8_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F8_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F8_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F8_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_F9                            SPP_MISC_REG_DP_GMA_CURVE_F9
#define SPP_MISC_REG_DP_GMA_CURVE_F9_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F9_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_F9_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_F9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F9_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_F9_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_F9_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_F9_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_FA                            SPP_MISC_REG_DP_GMA_CURVE_FA
#define SPP_MISC_REG_DP_GMA_CURVE_FA_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_FA_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FA_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FA_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FA_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FA_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FA_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_FB                            SPP_MISC_REG_DP_GMA_CURVE_FB
#define SPP_MISC_REG_DP_GMA_CURVE_FB_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_FB_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FB_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FB_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FB_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FB_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FB_POS))

/* 0x2FC : disp_gma_curve_fc */
#define SPP_MISC_DISP_GMA_CURVE_FC_OFFSET                       (0x2FC)
#define SPP_MISC_REG_DP_GMA_CURVE_FC                            SPP_MISC_REG_DP_GMA_CURVE_FC
#define SPP_MISC_REG_DP_GMA_CURVE_FC_POS                        (0U)
#define SPP_MISC_REG_DP_GMA_CURVE_FC_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FC_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FC_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FC_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FC_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FC_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_FD                            SPP_MISC_REG_DP_GMA_CURVE_FD
#define SPP_MISC_REG_DP_GMA_CURVE_FD_POS                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FD_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FD_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FD_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FD_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FD_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FD_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_FE                            SPP_MISC_REG_DP_GMA_CURVE_FE
#define SPP_MISC_REG_DP_GMA_CURVE_FE_POS                        (16U)
#define SPP_MISC_REG_DP_GMA_CURVE_FE_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FE_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FE_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FE_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FE_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FE_POS))
#define SPP_MISC_REG_DP_GMA_CURVE_FF                            SPP_MISC_REG_DP_GMA_CURVE_FF
#define SPP_MISC_REG_DP_GMA_CURVE_FF_POS                        (24U)
#define SPP_MISC_REG_DP_GMA_CURVE_FF_LEN                        (8U)
#define SPP_MISC_REG_DP_GMA_CURVE_FF_MSK                        (((1U<<SPP_MISC_REG_DP_GMA_CURVE_FF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FF_POS)
#define SPP_MISC_REG_DP_GMA_CURVE_FF_UMSK                       (~(((1U<<SPP_MISC_REG_DP_GMA_CURVE_FF_LEN)-1)<<SPP_MISC_REG_DP_GMA_CURVE_FF_POS))


struct  isp_misc_reg {
    /* 0x0 : config */
    union {
        struct {
            uint32_t rg_dvpas_enable                :  1; /* [    0],        r/w,        0x0 */
            uint32_t rg_dvpas_hs_inv                :  1; /* [    1],        r/w,        0x0 */
            uint32_t rg_dvpas_vs_inv                :  1; /* [    2],        r/w,        0x0 */
            uint32_t rg_dvpas_da_order              :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_15                  : 12; /* [15: 4],       rsvd,        0x0 */
            uint32_t rg_dvpas_fifo_th               : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_29                 :  3; /* [29:27],       rsvd,        0x0 */
            uint32_t cr_isp_de_as_hsync             :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_isp_pclk_force_on          :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } config;

    /* 0x4 : pix_data_ctrl */
    union {
        struct {
            uint32_t reg_pix_data_ctrl              : 12; /* [11: 0],        r/w,      0xfff */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_pix_data_sht_bit           :  4; /* [19:16],        r/w,        0x0 */
            uint32_t reg_pix_data_sht_dir           :  1; /* [   20],        r/w,        0x0 */
            uint32_t reserved_21_30                 : 10; /* [30:21],       rsvd,        0x0 */
            uint32_t reg_isp_dtsrc_src              :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } pix_data_ctrl;

    /* 0x8 : dvp2bus_src_sel_1 */
    union {
        struct {
            uint32_t rg_d2b_dvp_sel_a               :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6                     :  1; /* [    6],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_a                :  1; /* [    7],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_b               :  6; /* [13: 8],        r/w,        0x0 */
            uint32_t reserved_14                    :  1; /* [   14],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_b                :  1; /* [   15],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_c               :  6; /* [21:16],        r/w,        0x0 */
            uint32_t reserved_22                    :  1; /* [   22],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_c                :  1; /* [   23],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_d               :  6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30                    :  1; /* [   30],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_d                :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2bus_src_sel_1;

    /* 0xC : dvp_frame_m_to_n */
    union {
        struct {
            uint32_t cr_frame_m_to_n_en             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t cr_frame_interval              :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t cr_frame_cnt_n                 :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t cr_frame_cnt_m                 :  4; /* [15:12],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_frame_m_to_n;

    /* 0x10 : isp_id_bayer */
    union {
        struct {
            uint32_t reg_bayer_idgen_rst            :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_bayer_idgen_edge           :  1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_15                  : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t reg_bayer_idgen_cnt_incr       : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } isp_id_bayer;

    /* 0x14 : dvp2bus_src_sel_2 */
    union {
        struct {
            uint32_t rg_d2b_dvp_sel_e               :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6                     :  1; /* [    6],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_e                :  1; /* [    7],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_f               :  6; /* [13: 8],        r/w,        0x0 */
            uint32_t reserved_14                    :  1; /* [   14],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_f                :  1; /* [   15],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_g               :  6; /* [21:16],        r/w,        0x0 */
            uint32_t reserved_22                    :  1; /* [   22],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_g                :  1; /* [   23],        r/w,        0x0 */
            uint32_t rg_d2b_dvp_sel_h               :  6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30                    :  1; /* [   30],       rsvd,        0x0 */
            uint32_t rg_d2x_id_sel_h                :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp2bus_src_sel_2;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : int_clr */
    union {
        struct {
            uint32_t rg_reserveb_int_clr            :  1; /* [    0],        w1p,        0x0 */
            uint32_t rg_reservea_int_clr            :  1; /* [    1],        w1p,        0x0 */
            uint32_t rg_reservew_int_clr            :  1; /* [    2],        w1p,        0x0 */
            uint32_t rg_reserveb2_int_clr           :  1; /* [    3],        w1p,        0x0 */
            uint32_t rg_osd_pb_int_clr              :  1; /* [    4],        w1p,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t rg_seof1_int_clr               :  1; /* [    8],        w1p,        0x0 */
            uint32_t rg_seof2_int_clr               :  1; /* [    9],        w1p,        0x0 */
            uint32_t rg_seof3_int_clr               :  1; /* [   10],        w1p,        0x0 */
            uint32_t rg_reservea_hist_int_clr       :  1; /* [   11],        w1p,        0x0 */
            uint32_t rg_reserveb3_int_clr           :  1; /* [   12],        w1p,        0x0 */
            uint32_t rg_dp_seof0_int_clr            :  1; /* [   13],        w1p,        0x0 */
            uint32_t rg_seof4_int_clr               :  1; /* [   14],        w1p,        0x0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } int_clr;

    /* 0x24 : int_ctrl */
    union {
        struct {
            uint32_t rg_reservea_int_mask           :  1; /* [    0],        r/w,        0x0 */
            uint32_t rg_reserveb_int_mask           :  1; /* [    1],        r/w,        0x0 */
            uint32_t rg_reservew_int_mask           :  1; /* [    2],        r/w,        0x0 */
            uint32_t rg_reserveb2_int_mask          :  1; /* [    3],        r/w,        0x0 */
            uint32_t rg_osd_pb_int_mask             :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t rg_seof1_int_mask              :  1; /* [    8],        r/w,        0x0 */
            uint32_t rg_seof1_int_edge              :  1; /* [    9],        r/w,        0x0 */
            uint32_t rg_seof1_int_src               :  2; /* [11:10],        r/w,        0x2 */
            uint32_t rg_seof2_int_mask              :  1; /* [   12],        r/w,        0x0 */
            uint32_t rg_seof2_int_edge              :  1; /* [   13],        r/w,        0x0 */
            uint32_t rg_seof2_int_src               :  2; /* [15:14],        r/w,        0x2 */
            uint32_t rg_seof3_int_mask              :  1; /* [   16],        r/w,        0x0 */
            uint32_t rg_seof3_int_edge              :  1; /* [   17],        r/w,        0x0 */
            uint32_t rg_seof3_int_src               :  2; /* [19:18],        r/w,        0x2 */
            uint32_t rg_reservea_hist_int_mask      :  1; /* [   20],        r/w,        0x0 */
            uint32_t rg_reserveb3_int_mask          :  1; /* [   21],        r/w,        0x0 */
            uint32_t rg_dp_seof0_int_src            :  1; /* [   22],        r/w,        0x0 */
            uint32_t rg_dp_seof0_int_edge           :  1; /* [   23],        r/w,        0x0 */
            uint32_t rg_dp_seof0_int_mask           :  1; /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_27                 :  3; /* [27:25],       rsvd,        0x0 */
            uint32_t rg_seof4_int_mask              :  1; /* [   28],        r/w,        0x0 */
            uint32_t rg_seof4_int_edge              :  1; /* [   29],        r/w,        0x0 */
            uint32_t rg_seof4_int_src               :  2; /* [31:30],        r/w,        0x2 */
        }BF;
        uint32_t WORD;
    } int_ctrl;

    /* 0x28 : isp_id_yuv */
    union {
        struct {
            uint32_t reg_yuv_idgen_rst              :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_yuv_idgen_edge             :  1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_15                  : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t reg_yuv_idgen_cnt_incr         : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } isp_id_yuv;

    /* 0x2C : dvp_reshape */
    union {
        struct {
            uint32_t reg_rshp_tgl_count             :  5; /* [ 4: 0],        r/w,        0x0 */
            uint32_t reg_rshp_hsync_inv             :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_rshp_vsync_inv             :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_rshp_clr                   :  1; /* [    7],        w1p,        0x0 */
            uint32_t reg_rshp_en                    :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dvp_reshape;

    /* 0x30  reserved */
    uint8_t RESERVED0x30[16];

    /* 0x40 : scalerA_i_size */
    union {
        struct {
            uint32_t rg_scalerA_i_w                 : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerA_i_h                 : 11; /* [26:16],        r/w,      0x438 */
            uint32_t rg_sclrA_sw_sh                 :  1; /* [   27],        w1p,        0x0 */
            uint32_t rg_scalerA_bypass              :  1; /* [   28],        r/w,        0x1 */
            uint32_t rg_scalerA_sel                 :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerA_i_size;

    /* 0x44 : scalerA_o_size */
    union {
        struct {
            uint32_t rg_scalerA_o_w                 : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerA_o_h                 : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerA_o_size;

    /* 0x48 : scalerB_i_size */
    union {
        struct {
            uint32_t rg_scalerB_i_w                 : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerB_i_h                 : 11; /* [26:16],        r/w,      0x438 */
            uint32_t rg_sclrB_sw_sh                 :  1; /* [   27],        w1p,        0x0 */
            uint32_t rg_scalerB_bypass              :  1; /* [   28],        r/w,        0x1 */
            uint32_t rg_scalerB_sel                 :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerB_i_size;

    /* 0x4C : scalerB_o_size */
    union {
        struct {
            uint32_t rg_scalerB_o_w                 : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerB_o_h                 : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerB_o_size;

    /* 0x50 : scalerC_i_size */
    union {
        struct {
            uint32_t rg_scalerC_i_w                 : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerC_i_h                 : 11; /* [26:16],        r/w,      0x438 */
            uint32_t rg_sclrC_sw_sh                 :  1; /* [   27],        w1p,        0x0 */
            uint32_t rg_scalerC_bypass              :  1; /* [   28],        r/w,        0x1 */
            uint32_t rg_scalerC_sel                 :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerC_i_size;

    /* 0x54 : scalerC_o_size */
    union {
        struct {
            uint32_t rg_scalerC_o_w                 : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerC_o_h                 : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerC_o_size;

    /* 0x58 : scalerD_i_size */
    union {
        struct {
            uint32_t rg_scalerD_i_w                 : 11; /* [10: 0],        r/w,      0x780 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerD_i_h                 : 11; /* [26:16],        r/w,      0x438 */
            uint32_t rg_sclrD_sw_sh                 :  1; /* [   27],        w1p,        0x0 */
            uint32_t rg_scalerD_bypass              :  1; /* [   28],        r/w,        0x1 */
            uint32_t rg_scalerD_sel                 :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerD_i_size;

    /* 0x5C : scalerD_o_size */
    union {
        struct {
            uint32_t rg_scalerD_o_w                 : 11; /* [10: 0],        r/w,      0x500 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t rg_scalerD_o_h                 : 11; /* [26:16],        r/w,      0x2d0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } scalerD_o_size;

    /* 0x60 : disp_config */
    union {
        struct {
            uint32_t reserved_0_3                   :  4; /* [ 3: 0],       rsvd,        0x0 */
            uint32_t rg_disp_bt656_en               :  1; /* [    4],        r/w,        0x0 */
            uint32_t rg_disp_bt1120_en              :  1; /* [    5],        r/w,        0x0 */
            uint32_t rg_disp_dpi_en                 :  1; /* [    6],        r/w,        0x0 */
            uint32_t rg_disp_hdmi_en                :  1; /* [    7],        r/w,        0x0 */
            uint32_t rg_disp_mux_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t rg_osdDP_sel                   :  2; /* [13:12],        r/w,        0x0 */
            uint32_t reserved_14_30                 : 17; /* [30:14],       rsvd,        0x0 */
            uint32_t rg_disp_clko_inv               :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_config;

    /* 0x64 : disp_dpi_config */
    union {
        struct {
            uint32_t rg_disp_dpi_hs_w               :  8; /* [ 7: 0],        r/w,        0x8 */
            uint32_t rg_disp_dpi_hfp_w              :  8; /* [15: 8],        r/w,       0x10 */
            uint32_t rg_disp_dpi_vs_w               :  8; /* [23:16],        r/w,        0x2 */
            uint32_t rg_disp_dpi_vfp_w              :  8; /* [31:24],        r/w,        0x4 */
        }BF;
        uint32_t WORD;
    } disp_dpi_config;

    /* 0x68 : disp_yuv_rgb_config_0 */
    union {
        struct {
            uint32_t rg_disp_y2r_pre_0              :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9                     :  1; /* [    9],       rsvd,        0x0 */
            uint32_t rg_disp_y2r_pre_1              :  9; /* [18:10],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t rg_disp_y2r_pre_2              :  9; /* [28:20],        r/w,        0x0 */
            uint32_t reserved_29_30                 :  2; /* [30:29],       rsvd,        0x0 */
            uint32_t rg_disp_y2r_en                 :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_0;

    /* 0x6C : disp_yuv_rgb_config_1 */
    union {
        struct {
            uint32_t rg_disp_y2r_pos_0              :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9                     :  1; /* [    9],       rsvd,        0x0 */
            uint32_t rg_disp_y2r_pos_1              :  9; /* [18:10],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t rg_disp_y2r_pos_2              :  9; /* [28:20],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_1;

    /* 0x70 : disp_yuv_rgb_config_2 */
    union {
        struct {
            uint32_t rg_disp_y2r_mtx_00             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_01             : 12; /* [23:12],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_02_l           :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_2;

    /* 0x74 : disp_yuv_rgb_config_3 */
    union {
        struct {
            uint32_t rg_disp_y2r_mtx_02_u           :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_10             : 12; /* [15: 4],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_11             : 12; /* [27:16],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_12_l           :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_3;

    /* 0x78 : disp_yuv_rgb_config_4 */
    union {
        struct {
            uint32_t rg_disp_y2r_mtx_12_u           :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_20             : 12; /* [19: 8],        r/w,        0x0 */
            uint32_t rg_disp_y2r_mtx_21             : 12; /* [31:20],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_4;

    /* 0x7C : disp_yuv_rgb_config_5 */
    union {
        struct {
            uint32_t rg_disp_y2r_mtx_22             : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_yuv_rgb_config_5;

    /* 0x80 : isp_subsys_bus_ctrl */
    union {
        struct {
            uint32_t rg_isp_sub_pclk_force_on       : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t rg_isp_peri_pclk_force_on      : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } isp_subsys_bus_ctrl;

    /* 0x84  reserved */
    uint8_t RESERVED0x84[28];

    /* 0xA0 : osdA_i_ctrl */
    union {
        struct {
            uint32_t rg_osd_pb_sel                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_28                  : 28; /* [28: 1],       rsvd,        0x0 */
            uint32_t rg_osdA_sel                    :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } osdA_i_ctrl;

    /* 0xA4 : osdB_i_ctrl */
    union {
        struct {
            uint32_t reserved_0_28                  : 29; /* [28: 0],       rsvd,        0x0 */
            uint32_t rg_osdB_sel                    :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } osdB_i_ctrl;

    /* 0xA8 : osdC_i_ctrl */
    union {
        struct {
            uint32_t reserved_0_28                  : 29; /* [28: 0],       rsvd,        0x0 */
            uint32_t rg_osdC_sel                    :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } osdC_i_ctrl;

    /* 0xAC : osdD_i_ctrl */
    union {
        struct {
            uint32_t reserved_0_28                  : 29; /* [28: 0],       rsvd,        0x0 */
            uint32_t rg_osdD_sel                    :  3; /* [31:29],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } osdD_i_ctrl;

    /* 0xb0  reserved */
    uint8_t RESERVED0xb0[16];

    /* 0xC0 : isp_subsys_dbg_sel */
    union {
        struct {
            uint32_t reg_isp_sub_dbg_en             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_isp_sub_dbg_sel            :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } isp_subsys_dbg_sel;

    /* 0xc4  reserved */
    uint8_t RESERVED0xc4[56];

    /* 0xFC : SPP_MISC_Dummy */
    union {
        struct {
            uint32_t dummy_reg                      : 32; /* [31: 0],        r/w, 0xffff0000 */
        }BF;
        uint32_t WORD;
    } SPP_MISC_Dummy;

    /* 0x100 : adjA_ctrl_0 */
    union {
        struct {
            uint32_t reg_adjA_adj_eb                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_adjA_y_luma                :  9; /* [ 9: 1],        r/w,        0x0 */
            uint32_t reg_adjA_y_mul0                : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjA_y_mul1                : 11; /* [31:21],        r/w,      0x35e */
        }BF;
        uint32_t WORD;
    } adjA_ctrl_0;

    /* 0x104 : adjA_ctrl_1 */
    union {
        struct {
            uint32_t reg_adjA_y_min                 :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t reg_adjA_y_max                 :  8; /* [15: 8],        r/w,       0xeb */
            uint32_t reg_adjA_uv_min                :  8; /* [23:16],        r/w,       0x10 */
            uint32_t reg_adjA_uv_max                :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } adjA_ctrl_1;

    /* 0x108 : adjA_ctrl_2 */
    union {
        struct {
            uint32_t rg_adjA_sel                    :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_9                   :  6; /* [ 9: 4],       rsvd,        0x0 */
            uint32_t reg_adjA_uv_mul0               : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjA_uv_mul1               : 11; /* [31:21],        r/w,      0x387 */
        }BF;
        uint32_t WORD;
    } adjA_ctrl_2;

    /* 0x10c  reserved */
    uint8_t RESERVED0x10c[4];

    /* 0x110 : adjB_ctrl_0 */
    union {
        struct {
            uint32_t reg_adjB_adj_eb                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_adjB_y_luma                :  9; /* [ 9: 1],        r/w,        0x0 */
            uint32_t reg_adjB_y_mul0                : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjB_y_mul1                : 11; /* [31:21],        r/w,      0x35e */
        }BF;
        uint32_t WORD;
    } adjB_ctrl_0;

    /* 0x114 : adjB_ctrl_1 */
    union {
        struct {
            uint32_t reg_adjB_y_min                 :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t reg_adjB_y_max                 :  8; /* [15: 8],        r/w,       0xeb */
            uint32_t reg_adjB_uv_min                :  8; /* [23:16],        r/w,       0x10 */
            uint32_t reg_adjB_uv_max                :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } adjB_ctrl_1;

    /* 0x118 : adjB_ctrl_2 */
    union {
        struct {
            uint32_t rg_adjB_sel                    :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_9                   :  6; /* [ 9: 4],       rsvd,        0x0 */
            uint32_t reg_adjB_uv_mul0               : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjB_uv_mul1               : 11; /* [31:21],        r/w,      0x387 */
        }BF;
        uint32_t WORD;
    } adjB_ctrl_2;

    /* 0x11c  reserved */
    uint8_t RESERVED0x11c[4];

    /* 0x120 : adjC_ctrl_0 */
    union {
        struct {
            uint32_t reg_adjC_adj_eb                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_adjC_y_luma                :  9; /* [ 9: 1],        r/w,        0x0 */
            uint32_t reg_adjC_y_mul0                : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjC_y_mul1                : 11; /* [31:21],        r/w,      0x35e */
        }BF;
        uint32_t WORD;
    } adjC_ctrl_0;

    /* 0x124 : adjC_ctrl_1 */
    union {
        struct {
            uint32_t reg_adjC_y_min                 :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t reg_adjC_y_max                 :  8; /* [15: 8],        r/w,       0xeb */
            uint32_t reg_adjC_uv_min                :  8; /* [23:16],        r/w,       0x10 */
            uint32_t reg_adjC_uv_max                :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } adjC_ctrl_1;

    /* 0x128 : adjC_ctrl_2 */
    union {
        struct {
            uint32_t rg_adjC_sel                    :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_9                   :  6; /* [ 9: 4],       rsvd,        0x0 */
            uint32_t reg_adjC_uv_mul0               : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjC_uv_mul1               : 11; /* [31:21],        r/w,      0x387 */
        }BF;
        uint32_t WORD;
    } adjC_ctrl_2;

    /* 0x12c  reserved */
    uint8_t RESERVED0x12c[4];

    /* 0x130 : adjD_ctrl_0 */
    union {
        struct {
            uint32_t reg_adjD_adj_eb                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_adjD_y_luma                :  9; /* [ 9: 1],        r/w,        0x0 */
            uint32_t reg_adjD_y_mul0                : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjD_y_mul1                : 11; /* [31:21],        r/w,      0x35e */
        }BF;
        uint32_t WORD;
    } adjD_ctrl_0;

    /* 0x134 : adjD_ctrl_1 */
    union {
        struct {
            uint32_t reg_adjD_y_min                 :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t reg_adjD_y_max                 :  8; /* [15: 8],        r/w,       0xeb */
            uint32_t reg_adjD_uv_min                :  8; /* [23:16],        r/w,       0x10 */
            uint32_t reg_adjD_uv_max                :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } adjD_ctrl_1;

    /* 0x138 : adjD_ctrl_2 */
    union {
        struct {
            uint32_t rg_adjD_sel                    :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t reserved_4_9                   :  6; /* [ 9: 4],       rsvd,        0x0 */
            uint32_t reg_adjD_uv_mul0               : 11; /* [20:10],        r/w,      0x380 */
            uint32_t reg_adjD_uv_mul1               : 11; /* [31:21],        r/w,      0x387 */
        }BF;
        uint32_t WORD;
    } adjD_ctrl_2;

    /* 0x13c  reserved */
    uint8_t RESERVED0x13c[36];

    /* 0x160 : y2rA_config_0 */
    union {
        struct {
            uint32_t rg_y2rA_pre_0                  :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t rg_y2rA_pos_0                  :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_26                 :  2; /* [26:25],       rsvd,        0x0 */
            uint32_t rg_y2rA_en                     :  1; /* [   27],        r/w,        0x0 */
            uint32_t rg_y2rA_sel                    :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_0;

    /* 0x164 : y2rA_config_1 */
    union {
        struct {
            uint32_t rg_y2rA_pre_1                  :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t rg_y2rA_pos_1                  :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_1;

    /* 0x168 : y2rA_config_2 */
    union {
        struct {
            uint32_t rg_y2rA_pre_2                  :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t rg_y2rA_pos_2                  :  9; /* [24:16],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_2;

    /* 0x16C : y2rA_config_3 */
    union {
        struct {
            uint32_t rg_y2rA_mtx_00                 : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t rg_y2rA_mtx_01                 : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_3;

    /* 0x170 : y2rA_config_4 */
    union {
        struct {
            uint32_t rg_y2rA_mtx_02                 : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t rg_y2rA_mtx_10                 : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_4;

    /* 0x174 : y2rA_config_5 */
    union {
        struct {
            uint32_t rg_y2rA_mtx_11                 : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t rg_y2rA_mtx_12                 : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_5;

    /* 0x178 : y2rA_config_6 */
    union {
        struct {
            uint32_t rg_y2rA_mtx_20                 : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t rg_y2rA_mtx_21                 : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_6;

    /* 0x17C : y2rA_config_7 */
    union {
        struct {
            uint32_t rg_y2rA_mtx_22                 : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } y2rA_config_7;

    /* 0x180 : disp_rgb2yuv_config_0 */
    union {
        struct {
            uint32_t rg_disp_r2y_pre_0              :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9                     :  1; /* [    9],       rsvd,        0x0 */
            uint32_t rg_disp_r2y_pre_1              :  9; /* [18:10],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t rg_disp_r2y_pre_2              :  9; /* [28:20],        r/w,        0x0 */
            uint32_t reserved_29_30                 :  2; /* [30:29],       rsvd,        0x0 */
            uint32_t rg_disp_r2y_en                 :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_0;

    /* 0x184 : disp_rgb2yuv_config_1 */
    union {
        struct {
            uint32_t rg_disp_r2y_pos_0              :  9; /* [ 8: 0],        r/w,        0x0 */
            uint32_t reserved_9                     :  1; /* [    9],       rsvd,        0x0 */
            uint32_t rg_disp_r2y_pos_1              :  9; /* [18:10],        r/w,       0x80 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t rg_disp_r2y_pos_2              :  9; /* [28:20],        r/w,       0x80 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_1;

    /* 0x188 : disp_rgb2yuv_config_2 */
    union {
        struct {
            uint32_t rg_disp_r2y_mtx_00             : 12; /* [11: 0],        r/w,       0x99 */
            uint32_t rg_disp_r2y_mtx_01             : 12; /* [23:12],        r/w,      0x12d */
            uint32_t rg_disp_r2y_mtx_02_l           :  8; /* [31:24],        r/w,       0x3a */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_2;

    /* 0x18C : disp_rgb2yuv_config_3 */
    union {
        struct {
            uint32_t rg_disp_r2y_mtx_02_u           :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t rg_disp_r2y_mtx_10             : 12; /* [15: 4],        r/w,      0xfa9 */
            uint32_t rg_disp_r2y_mtx_11             : 12; /* [27:16],        r/w,      0xf57 */
            uint32_t rg_disp_r2y_mtx_12_l           :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_3;

    /* 0x190 : disp_rgb2yuv_config_4 */
    union {
        struct {
            uint32_t rg_disp_r2y_mtx_12_u           :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t rg_disp_r2y_mtx_20             : 12; /* [19: 8],        r/w,      0x100 */
            uint32_t rg_disp_r2y_mtx_21             : 12; /* [31:20],        r/w,      0xf29 */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_4;

    /* 0x194 : disp_rgb2yuv_config_5 */
    union {
        struct {
            uint32_t rg_disp_r2y_mtx_22             : 12; /* [11: 0],        r/w,      0xfd7 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_rgb2yuv_config_5;

    /* 0x198  reserved */
    uint8_t RESERVED0x198[40];

    /* 0x1C0 : cropA_hsync */
    union {
        struct {
            uint32_t reg_cropA_hsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropA_hsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropA_hsync;

    /* 0x1C4 : cropA_vsync */
    union {
        struct {
            uint32_t reg_cropA_vsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropA_vsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropA_vsync;

    /* 0x1C8 : cropB_hsync */
    union {
        struct {
            uint32_t reg_cropB_hsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropB_hsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropB_hsync;

    /* 0x1CC : cropB_vsync */
    union {
        struct {
            uint32_t reg_cropB_vsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropB_vsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropB_vsync;

    /* 0x1D0 : cropC_hsync */
    union {
        struct {
            uint32_t reg_cropC_hsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropC_hsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropC_hsync;

    /* 0x1D4 : cropC_vsync */
    union {
        struct {
            uint32_t reg_cropC_vsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropC_vsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropC_vsync;

    /* 0x1D8 : cropD_hsync */
    union {
        struct {
            uint32_t reg_cropD_hsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropD_hsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropD_hsync;

    /* 0x1DC : cropD_vsync */
    union {
        struct {
            uint32_t reg_cropD_vsync_start          : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_cropD_vsync_end            : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } cropD_vsync;

    /* 0x1E0 : crop_enable */
    union {
        struct {
            uint32_t reg_cropA_enable               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_cropB_enable               :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_cropC_enable               :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_cropD_enable               :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } crop_enable;

    /* 0x1e4  reserved */
    uint8_t RESERVED0x1e4[24];

    /* 0x1FC : disp_gma_cfg */
    union {
        struct {
            uint32_t reg_dp_gma_ch0_en              :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_dp_gma_ch1_en              :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_dp_gma_ch2_en              :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } disp_gma_cfg;

    /* 0x200 : disp_gma_curve_00 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_00            :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_dp_gma_curve_01            :  8; /* [15: 8],        r/w,        0x1 */
            uint32_t reg_dp_gma_curve_02            :  8; /* [23:16],        r/w,        0x2 */
            uint32_t reg_dp_gma_curve_03            :  8; /* [31:24],        r/w,        0x3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_00;

    /* 0x204 : disp_gma_curve_04 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_04            :  8; /* [ 7: 0],        r/w,        0x4 */
            uint32_t reg_dp_gma_curve_05            :  8; /* [15: 8],        r/w,        0x5 */
            uint32_t reg_dp_gma_curve_06            :  8; /* [23:16],        r/w,        0x6 */
            uint32_t reg_dp_gma_curve_07            :  8; /* [31:24],        r/w,        0x7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_04;

    /* 0x208 : disp_gma_curve_08 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_08            :  8; /* [ 7: 0],        r/w,        0x8 */
            uint32_t reg_dp_gma_curve_09            :  8; /* [15: 8],        r/w,        0x9 */
            uint32_t reg_dp_gma_curve_0a            :  8; /* [23:16],        r/w,        0xa */
            uint32_t reg_dp_gma_curve_0b            :  8; /* [31:24],        r/w,        0xb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_08;

    /* 0x20C : disp_gma_curve_0c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_0c            :  8; /* [ 7: 0],        r/w,        0xc */
            uint32_t reg_dp_gma_curve_0d            :  8; /* [15: 8],        r/w,        0xd */
            uint32_t reg_dp_gma_curve_0e            :  8; /* [23:16],        r/w,        0xe */
            uint32_t reg_dp_gma_curve_0f            :  8; /* [31:24],        r/w,        0xf */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_0c;

    /* 0x210 : disp_gma_curve_10 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_10            :  8; /* [ 7: 0],        r/w,       0x10 */
            uint32_t reg_dp_gma_curve_11            :  8; /* [15: 8],        r/w,       0x11 */
            uint32_t reg_dp_gma_curve_12            :  8; /* [23:16],        r/w,       0x12 */
            uint32_t reg_dp_gma_curve_13            :  8; /* [31:24],        r/w,       0x13 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_10;

    /* 0x214 : disp_gma_curve_14 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_14            :  8; /* [ 7: 0],        r/w,       0x14 */
            uint32_t reg_dp_gma_curve_15            :  8; /* [15: 8],        r/w,       0x15 */
            uint32_t reg_dp_gma_curve_16            :  8; /* [23:16],        r/w,       0x16 */
            uint32_t reg_dp_gma_curve_17            :  8; /* [31:24],        r/w,       0x17 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_14;

    /* 0x218 : disp_gma_curve_18 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_18            :  8; /* [ 7: 0],        r/w,       0x18 */
            uint32_t reg_dp_gma_curve_19            :  8; /* [15: 8],        r/w,       0x19 */
            uint32_t reg_dp_gma_curve_1a            :  8; /* [23:16],        r/w,       0x1a */
            uint32_t reg_dp_gma_curve_1b            :  8; /* [31:24],        r/w,       0x1b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_18;

    /* 0x21C : disp_gma_curve_1c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_1c            :  8; /* [ 7: 0],        r/w,       0x1c */
            uint32_t reg_dp_gma_curve_1d            :  8; /* [15: 8],        r/w,       0x1d */
            uint32_t reg_dp_gma_curve_1e            :  8; /* [23:16],        r/w,       0x1e */
            uint32_t reg_dp_gma_curve_1f            :  8; /* [31:24],        r/w,       0x1f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_1c;

    /* 0x220 : disp_gma_curve_20 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_20            :  8; /* [ 7: 0],        r/w,       0x20 */
            uint32_t reg_dp_gma_curve_21            :  8; /* [15: 8],        r/w,       0x21 */
            uint32_t reg_dp_gma_curve_22            :  8; /* [23:16],        r/w,       0x22 */
            uint32_t reg_dp_gma_curve_23            :  8; /* [31:24],        r/w,       0x23 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_20;

    /* 0x224 : disp_gma_curve_24 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_24            :  8; /* [ 7: 0],        r/w,       0x24 */
            uint32_t reg_dp_gma_curve_25            :  8; /* [15: 8],        r/w,       0x25 */
            uint32_t reg_dp_gma_curve_26            :  8; /* [23:16],        r/w,       0x26 */
            uint32_t reg_dp_gma_curve_27            :  8; /* [31:24],        r/w,       0x27 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_24;

    /* 0x228 : disp_gma_curve_28 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_28            :  8; /* [ 7: 0],        r/w,       0x28 */
            uint32_t reg_dp_gma_curve_29            :  8; /* [15: 8],        r/w,       0x29 */
            uint32_t reg_dp_gma_curve_2a            :  8; /* [23:16],        r/w,       0x2a */
            uint32_t reg_dp_gma_curve_2b            :  8; /* [31:24],        r/w,       0x2b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_28;

    /* 0x22C : disp_gma_curve_2c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_2c            :  8; /* [ 7: 0],        r/w,       0x2c */
            uint32_t reg_dp_gma_curve_2d            :  8; /* [15: 8],        r/w,       0x2d */
            uint32_t reg_dp_gma_curve_2e            :  8; /* [23:16],        r/w,       0x2e */
            uint32_t reg_dp_gma_curve_2f            :  8; /* [31:24],        r/w,       0x2f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_2c;

    /* 0x230 : disp_gma_curve_30 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_30            :  8; /* [ 7: 0],        r/w,       0x30 */
            uint32_t reg_dp_gma_curve_31            :  8; /* [15: 8],        r/w,       0x31 */
            uint32_t reg_dp_gma_curve_32            :  8; /* [23:16],        r/w,       0x32 */
            uint32_t reg_dp_gma_curve_33            :  8; /* [31:24],        r/w,       0x33 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_30;

    /* 0x234 : disp_gma_curve_34 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_34            :  8; /* [ 7: 0],        r/w,       0x34 */
            uint32_t reg_dp_gma_curve_35            :  8; /* [15: 8],        r/w,       0x35 */
            uint32_t reg_dp_gma_curve_36            :  8; /* [23:16],        r/w,       0x36 */
            uint32_t reg_dp_gma_curve_37            :  8; /* [31:24],        r/w,       0x37 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_34;

    /* 0x238 : disp_gma_curve_38 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_38            :  8; /* [ 7: 0],        r/w,       0x38 */
            uint32_t reg_dp_gma_curve_39            :  8; /* [15: 8],        r/w,       0x39 */
            uint32_t reg_dp_gma_curve_3a            :  8; /* [23:16],        r/w,       0x3a */
            uint32_t reg_dp_gma_curve_3b            :  8; /* [31:24],        r/w,       0x3b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_38;

    /* 0x23C : disp_gma_curve_3c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_3c            :  8; /* [ 7: 0],        r/w,       0x3c */
            uint32_t reg_dp_gma_curve_3d            :  8; /* [15: 8],        r/w,       0x3d */
            uint32_t reg_dp_gma_curve_3e            :  8; /* [23:16],        r/w,       0x3e */
            uint32_t reg_dp_gma_curve_3f            :  8; /* [31:24],        r/w,       0x3f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_3c;

    /* 0x240 : disp_gma_curve_40 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_40            :  8; /* [ 7: 0],        r/w,       0x40 */
            uint32_t reg_dp_gma_curve_41            :  8; /* [15: 8],        r/w,       0x41 */
            uint32_t reg_dp_gma_curve_42            :  8; /* [23:16],        r/w,       0x42 */
            uint32_t reg_dp_gma_curve_43            :  8; /* [31:24],        r/w,       0x43 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_40;

    /* 0x244 : disp_gma_curve_44 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_44            :  8; /* [ 7: 0],        r/w,       0x44 */
            uint32_t reg_dp_gma_curve_45            :  8; /* [15: 8],        r/w,       0x45 */
            uint32_t reg_dp_gma_curve_46            :  8; /* [23:16],        r/w,       0x46 */
            uint32_t reg_dp_gma_curve_47            :  8; /* [31:24],        r/w,       0x47 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_44;

    /* 0x248 : disp_gma_curve_48 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_48            :  8; /* [ 7: 0],        r/w,       0x48 */
            uint32_t reg_dp_gma_curve_49            :  8; /* [15: 8],        r/w,       0x49 */
            uint32_t reg_dp_gma_curve_4a            :  8; /* [23:16],        r/w,       0x4a */
            uint32_t reg_dp_gma_curve_4b            :  8; /* [31:24],        r/w,       0x4b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_48;

    /* 0x24C : disp_gma_curve_4c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_4c            :  8; /* [ 7: 0],        r/w,       0x4c */
            uint32_t reg_dp_gma_curve_4d            :  8; /* [15: 8],        r/w,       0x4d */
            uint32_t reg_dp_gma_curve_4e            :  8; /* [23:16],        r/w,       0x4e */
            uint32_t reg_dp_gma_curve_4f            :  8; /* [31:24],        r/w,       0x4f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_4c;

    /* 0x250 : disp_gma_curve_50 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_50            :  8; /* [ 7: 0],        r/w,       0x50 */
            uint32_t reg_dp_gma_curve_51            :  8; /* [15: 8],        r/w,       0x51 */
            uint32_t reg_dp_gma_curve_52            :  8; /* [23:16],        r/w,       0x52 */
            uint32_t reg_dp_gma_curve_53            :  8; /* [31:24],        r/w,       0x53 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_50;

    /* 0x254 : disp_gma_curve_54 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_54            :  8; /* [ 7: 0],        r/w,       0x54 */
            uint32_t reg_dp_gma_curve_55            :  8; /* [15: 8],        r/w,       0x55 */
            uint32_t reg_dp_gma_curve_56            :  8; /* [23:16],        r/w,       0x56 */
            uint32_t reg_dp_gma_curve_57            :  8; /* [31:24],        r/w,       0x57 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_54;

    /* 0x258 : disp_gma_curve_58 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_58            :  8; /* [ 7: 0],        r/w,       0x58 */
            uint32_t reg_dp_gma_curve_59            :  8; /* [15: 8],        r/w,       0x59 */
            uint32_t reg_dp_gma_curve_5a            :  8; /* [23:16],        r/w,       0x5a */
            uint32_t reg_dp_gma_curve_5b            :  8; /* [31:24],        r/w,       0x5b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_58;

    /* 0x25C : disp_gma_curve_5c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_5c            :  8; /* [ 7: 0],        r/w,       0x5c */
            uint32_t reg_dp_gma_curve_5d            :  8; /* [15: 8],        r/w,       0x5d */
            uint32_t reg_dp_gma_curve_5e            :  8; /* [23:16],        r/w,       0x5e */
            uint32_t reg_dp_gma_curve_5f            :  8; /* [31:24],        r/w,       0x5f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_5c;

    /* 0x260 : disp_gma_curve_60 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_60            :  8; /* [ 7: 0],        r/w,       0x60 */
            uint32_t reg_dp_gma_curve_61            :  8; /* [15: 8],        r/w,       0x61 */
            uint32_t reg_dp_gma_curve_62            :  8; /* [23:16],        r/w,       0x62 */
            uint32_t reg_dp_gma_curve_63            :  8; /* [31:24],        r/w,       0x63 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_60;

    /* 0x264 : disp_gma_curve_64 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_64            :  8; /* [ 7: 0],        r/w,       0x64 */
            uint32_t reg_dp_gma_curve_65            :  8; /* [15: 8],        r/w,       0x65 */
            uint32_t reg_dp_gma_curve_66            :  8; /* [23:16],        r/w,       0x66 */
            uint32_t reg_dp_gma_curve_67            :  8; /* [31:24],        r/w,       0x67 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_64;

    /* 0x268 : disp_gma_curve_68 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_68            :  8; /* [ 7: 0],        r/w,       0x68 */
            uint32_t reg_dp_gma_curve_69            :  8; /* [15: 8],        r/w,       0x69 */
            uint32_t reg_dp_gma_curve_6a            :  8; /* [23:16],        r/w,       0x6a */
            uint32_t reg_dp_gma_curve_6b            :  8; /* [31:24],        r/w,       0x6b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_68;

    /* 0x26C : disp_gma_curve_6c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_6c            :  8; /* [ 7: 0],        r/w,       0x6c */
            uint32_t reg_dp_gma_curve_6d            :  8; /* [15: 8],        r/w,       0x6d */
            uint32_t reg_dp_gma_curve_6e            :  8; /* [23:16],        r/w,       0x6e */
            uint32_t reg_dp_gma_curve_6f            :  8; /* [31:24],        r/w,       0x6f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_6c;

    /* 0x270 : disp_gma_curve_70 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_70            :  8; /* [ 7: 0],        r/w,       0x70 */
            uint32_t reg_dp_gma_curve_71            :  8; /* [15: 8],        r/w,       0x71 */
            uint32_t reg_dp_gma_curve_72            :  8; /* [23:16],        r/w,       0x72 */
            uint32_t reg_dp_gma_curve_73            :  8; /* [31:24],        r/w,       0x73 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_70;

    /* 0x274 : disp_gma_curve_74 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_74            :  8; /* [ 7: 0],        r/w,       0x74 */
            uint32_t reg_dp_gma_curve_75            :  8; /* [15: 8],        r/w,       0x75 */
            uint32_t reg_dp_gma_curve_76            :  8; /* [23:16],        r/w,       0x76 */
            uint32_t reg_dp_gma_curve_77            :  8; /* [31:24],        r/w,       0x77 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_74;

    /* 0x278 : disp_gma_curve_78 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_78            :  8; /* [ 7: 0],        r/w,       0x78 */
            uint32_t reg_dp_gma_curve_79            :  8; /* [15: 8],        r/w,       0x79 */
            uint32_t reg_dp_gma_curve_7a            :  8; /* [23:16],        r/w,       0x7a */
            uint32_t reg_dp_gma_curve_7b            :  8; /* [31:24],        r/w,       0x7b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_78;

    /* 0x27C : disp_gma_curve_7c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_7c            :  8; /* [ 7: 0],        r/w,       0x7c */
            uint32_t reg_dp_gma_curve_7d            :  8; /* [15: 8],        r/w,       0x7d */
            uint32_t reg_dp_gma_curve_7e            :  8; /* [23:16],        r/w,       0x7e */
            uint32_t reg_dp_gma_curve_7f            :  8; /* [31:24],        r/w,       0x7f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_7c;

    /* 0x280 : disp_gma_curve_80 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_80            :  8; /* [ 7: 0],        r/w,       0x80 */
            uint32_t reg_dp_gma_curve_81            :  8; /* [15: 8],        r/w,       0x81 */
            uint32_t reg_dp_gma_curve_82            :  8; /* [23:16],        r/w,       0x82 */
            uint32_t reg_dp_gma_curve_83            :  8; /* [31:24],        r/w,       0x83 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_80;

    /* 0x284 : disp_gma_curve_84 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_84            :  8; /* [ 7: 0],        r/w,       0x84 */
            uint32_t reg_dp_gma_curve_85            :  8; /* [15: 8],        r/w,       0x85 */
            uint32_t reg_dp_gma_curve_86            :  8; /* [23:16],        r/w,       0x86 */
            uint32_t reg_dp_gma_curve_87            :  8; /* [31:24],        r/w,       0x87 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_84;

    /* 0x288 : disp_gma_curve_88 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_88            :  8; /* [ 7: 0],        r/w,       0x88 */
            uint32_t reg_dp_gma_curve_89            :  8; /* [15: 8],        r/w,       0x89 */
            uint32_t reg_dp_gma_curve_8a            :  8; /* [23:16],        r/w,       0x8a */
            uint32_t reg_dp_gma_curve_8b            :  8; /* [31:24],        r/w,       0x8b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_88;

    /* 0x28C : disp_gma_curve_8c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_8c            :  8; /* [ 7: 0],        r/w,       0x8c */
            uint32_t reg_dp_gma_curve_8d            :  8; /* [15: 8],        r/w,       0x8d */
            uint32_t reg_dp_gma_curve_8e            :  8; /* [23:16],        r/w,       0x8e */
            uint32_t reg_dp_gma_curve_8f            :  8; /* [31:24],        r/w,       0x8f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_8c;

    /* 0x290 : disp_gma_curve_90 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_90            :  8; /* [ 7: 0],        r/w,       0x90 */
            uint32_t reg_dp_gma_curve_91            :  8; /* [15: 8],        r/w,       0x91 */
            uint32_t reg_dp_gma_curve_92            :  8; /* [23:16],        r/w,       0x92 */
            uint32_t reg_dp_gma_curve_93            :  8; /* [31:24],        r/w,       0x93 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_90;

    /* 0x294 : disp_gma_curve_94 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_94            :  8; /* [ 7: 0],        r/w,       0x94 */
            uint32_t reg_dp_gma_curve_95            :  8; /* [15: 8],        r/w,       0x95 */
            uint32_t reg_dp_gma_curve_96            :  8; /* [23:16],        r/w,       0x96 */
            uint32_t reg_dp_gma_curve_97            :  8; /* [31:24],        r/w,       0x97 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_94;

    /* 0x298 : disp_gma_curve_98 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_98            :  8; /* [ 7: 0],        r/w,       0x98 */
            uint32_t reg_dp_gma_curve_99            :  8; /* [15: 8],        r/w,       0x99 */
            uint32_t reg_dp_gma_curve_9a            :  8; /* [23:16],        r/w,       0x9a */
            uint32_t reg_dp_gma_curve_9b            :  8; /* [31:24],        r/w,       0x9b */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_98;

    /* 0x29C : disp_gma_curve_9c */
    union {
        struct {
            uint32_t reg_dp_gma_curve_9c            :  8; /* [ 7: 0],        r/w,       0x9c */
            uint32_t reg_dp_gma_curve_9d            :  8; /* [15: 8],        r/w,       0x9d */
            uint32_t reg_dp_gma_curve_9e            :  8; /* [23:16],        r/w,       0x9e */
            uint32_t reg_dp_gma_curve_9f            :  8; /* [31:24],        r/w,       0x9f */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_9c;

    /* 0x2A0 : disp_gma_curve_a0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_a0            :  8; /* [ 7: 0],        r/w,       0xa0 */
            uint32_t reg_dp_gma_curve_a1            :  8; /* [15: 8],        r/w,       0xa1 */
            uint32_t reg_dp_gma_curve_a2            :  8; /* [23:16],        r/w,       0xa2 */
            uint32_t reg_dp_gma_curve_a3            :  8; /* [31:24],        r/w,       0xa3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_a0;

    /* 0x2A4 : disp_gma_curve_a4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_a4            :  8; /* [ 7: 0],        r/w,       0xa4 */
            uint32_t reg_dp_gma_curve_a5            :  8; /* [15: 8],        r/w,       0xa5 */
            uint32_t reg_dp_gma_curve_a6            :  8; /* [23:16],        r/w,       0xa6 */
            uint32_t reg_dp_gma_curve_a7            :  8; /* [31:24],        r/w,       0xa7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_a4;

    /* 0x2A8 : disp_gma_curve_a8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_a8            :  8; /* [ 7: 0],        r/w,       0xa8 */
            uint32_t reg_dp_gma_curve_a9            :  8; /* [15: 8],        r/w,       0xa9 */
            uint32_t reg_dp_gma_curve_aa            :  8; /* [23:16],        r/w,       0xaa */
            uint32_t reg_dp_gma_curve_ab            :  8; /* [31:24],        r/w,       0xab */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_a8;

    /* 0x2AC : disp_gma_curve_ac */
    union {
        struct {
            uint32_t reg_dp_gma_curve_ac            :  8; /* [ 7: 0],        r/w,       0xac */
            uint32_t reg_dp_gma_curve_ad            :  8; /* [15: 8],        r/w,       0xad */
            uint32_t reg_dp_gma_curve_ae            :  8; /* [23:16],        r/w,       0xae */
            uint32_t reg_dp_gma_curve_af            :  8; /* [31:24],        r/w,       0xaf */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_ac;

    /* 0x2B0 : disp_gma_curve_b0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_b0            :  8; /* [ 7: 0],        r/w,       0xb0 */
            uint32_t reg_dp_gma_curve_b1            :  8; /* [15: 8],        r/w,       0xb1 */
            uint32_t reg_dp_gma_curve_b2            :  8; /* [23:16],        r/w,       0xb2 */
            uint32_t reg_dp_gma_curve_b3            :  8; /* [31:24],        r/w,       0xb3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_b0;

    /* 0x2B4 : disp_gma_curve_b4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_b4            :  8; /* [ 7: 0],        r/w,       0xb4 */
            uint32_t reg_dp_gma_curve_b5            :  8; /* [15: 8],        r/w,       0xb5 */
            uint32_t reg_dp_gma_curve_b6            :  8; /* [23:16],        r/w,       0xb6 */
            uint32_t reg_dp_gma_curve_b7            :  8; /* [31:24],        r/w,       0xb7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_b4;

    /* 0x2B8 : disp_gma_curve_b8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_b8            :  8; /* [ 7: 0],        r/w,       0xb8 */
            uint32_t reg_dp_gma_curve_b9            :  8; /* [15: 8],        r/w,       0xb9 */
            uint32_t reg_dp_gma_curve_ba            :  8; /* [23:16],        r/w,       0xba */
            uint32_t reg_dp_gma_curve_bb            :  8; /* [31:24],        r/w,       0xbb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_b8;

    /* 0x2BC : disp_gma_curve_bc */
    union {
        struct {
            uint32_t reg_dp_gma_curve_bc            :  8; /* [ 7: 0],        r/w,       0xbc */
            uint32_t reg_dp_gma_curve_bd            :  8; /* [15: 8],        r/w,       0xbd */
            uint32_t reg_dp_gma_curve_be            :  8; /* [23:16],        r/w,       0xbe */
            uint32_t reg_dp_gma_curve_bf            :  8; /* [31:24],        r/w,       0xbf */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_bc;

    /* 0x2C0 : disp_gma_curve_c0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_c0            :  8; /* [ 7: 0],        r/w,       0xc0 */
            uint32_t reg_dp_gma_curve_c1            :  8; /* [15: 8],        r/w,       0xc1 */
            uint32_t reg_dp_gma_curve_c2            :  8; /* [23:16],        r/w,       0xc2 */
            uint32_t reg_dp_gma_curve_c3            :  8; /* [31:24],        r/w,       0xc3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_c0;

    /* 0x2C4 : disp_gma_curve_c4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_c4            :  8; /* [ 7: 0],        r/w,       0xc4 */
            uint32_t reg_dp_gma_curve_c5            :  8; /* [15: 8],        r/w,       0xc5 */
            uint32_t reg_dp_gma_curve_c6            :  8; /* [23:16],        r/w,       0xc6 */
            uint32_t reg_dp_gma_curve_c7            :  8; /* [31:24],        r/w,       0xc7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_c4;

    /* 0x2C8 : disp_gma_curve_c8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_c8            :  8; /* [ 7: 0],        r/w,       0xc8 */
            uint32_t reg_dp_gma_curve_c9            :  8; /* [15: 8],        r/w,       0xc9 */
            uint32_t reg_dp_gma_curve_ca            :  8; /* [23:16],        r/w,       0xca */
            uint32_t reg_dp_gma_curve_cb            :  8; /* [31:24],        r/w,       0xcb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_c8;

    /* 0x2CC : disp_gma_curve_cc */
    union {
        struct {
            uint32_t reg_dp_gma_curve_cc            :  8; /* [ 7: 0],        r/w,       0xcc */
            uint32_t reg_dp_gma_curve_cd            :  8; /* [15: 8],        r/w,       0xcd */
            uint32_t reg_dp_gma_curve_ce            :  8; /* [23:16],        r/w,       0xce */
            uint32_t reg_dp_gma_curve_cf            :  8; /* [31:24],        r/w,       0xcf */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_cc;

    /* 0x2D0 : disp_gma_curve_d0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_d0            :  8; /* [ 7: 0],        r/w,       0xd0 */
            uint32_t reg_dp_gma_curve_d1            :  8; /* [15: 8],        r/w,       0xd1 */
            uint32_t reg_dp_gma_curve_d2            :  8; /* [23:16],        r/w,       0xd2 */
            uint32_t reg_dp_gma_curve_d3            :  8; /* [31:24],        r/w,       0xd3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_d0;

    /* 0x2D4 : disp_gma_curve_d4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_d4            :  8; /* [ 7: 0],        r/w,       0xd4 */
            uint32_t reg_dp_gma_curve_d5            :  8; /* [15: 8],        r/w,       0xd5 */
            uint32_t reg_dp_gma_curve_d6            :  8; /* [23:16],        r/w,       0xd6 */
            uint32_t reg_dp_gma_curve_d7            :  8; /* [31:24],        r/w,       0xd7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_d4;

    /* 0x2D8 : disp_gma_curve_d8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_d8            :  8; /* [ 7: 0],        r/w,       0xd8 */
            uint32_t reg_dp_gma_curve_d9            :  8; /* [15: 8],        r/w,       0xd9 */
            uint32_t reg_dp_gma_curve_da            :  8; /* [23:16],        r/w,       0xda */
            uint32_t reg_dp_gma_curve_db            :  8; /* [31:24],        r/w,       0xdb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_d8;

    /* 0x2DC : disp_gma_curve_dc */
    union {
        struct {
            uint32_t reg_dp_gma_curve_dc            :  8; /* [ 7: 0],        r/w,       0xdc */
            uint32_t reg_dp_gma_curve_dd            :  8; /* [15: 8],        r/w,       0xdd */
            uint32_t reg_dp_gma_curve_de            :  8; /* [23:16],        r/w,       0xde */
            uint32_t reg_dp_gma_curve_df            :  8; /* [31:24],        r/w,       0xdf */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_dc;

    /* 0x2E0 : disp_gma_curve_e0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_e0            :  8; /* [ 7: 0],        r/w,       0xe0 */
            uint32_t reg_dp_gma_curve_e1            :  8; /* [15: 8],        r/w,       0xe1 */
            uint32_t reg_dp_gma_curve_e2            :  8; /* [23:16],        r/w,       0xe2 */
            uint32_t reg_dp_gma_curve_e3            :  8; /* [31:24],        r/w,       0xe3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_e0;

    /* 0x2E4 : disp_gma_curve_e4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_e4            :  8; /* [ 7: 0],        r/w,       0xe4 */
            uint32_t reg_dp_gma_curve_e5            :  8; /* [15: 8],        r/w,       0xe5 */
            uint32_t reg_dp_gma_curve_e6            :  8; /* [23:16],        r/w,       0xe6 */
            uint32_t reg_dp_gma_curve_e7            :  8; /* [31:24],        r/w,       0xe7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_e4;

    /* 0x2E8 : disp_gma_curve_e8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_e8            :  8; /* [ 7: 0],        r/w,       0xe8 */
            uint32_t reg_dp_gma_curve_e9            :  8; /* [15: 8],        r/w,       0xe9 */
            uint32_t reg_dp_gma_curve_ea            :  8; /* [23:16],        r/w,       0xea */
            uint32_t reg_dp_gma_curve_eb            :  8; /* [31:24],        r/w,       0xeb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_e8;

    /* 0x2EC : disp_gma_curve_ec */
    union {
        struct {
            uint32_t reg_dp_gma_curve_ec            :  8; /* [ 7: 0],        r/w,       0xec */
            uint32_t reg_dp_gma_curve_ed            :  8; /* [15: 8],        r/w,       0xed */
            uint32_t reg_dp_gma_curve_ee            :  8; /* [23:16],        r/w,       0xee */
            uint32_t reg_dp_gma_curve_ef            :  8; /* [31:24],        r/w,       0xef */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_ec;

    /* 0x2F0 : disp_gma_curve_f0 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_f0            :  8; /* [ 7: 0],        r/w,       0xf0 */
            uint32_t reg_dp_gma_curve_f1            :  8; /* [15: 8],        r/w,       0xf1 */
            uint32_t reg_dp_gma_curve_f2            :  8; /* [23:16],        r/w,       0xf2 */
            uint32_t reg_dp_gma_curve_f3            :  8; /* [31:24],        r/w,       0xf3 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_f0;

    /* 0x2F4 : disp_gma_curve_f4 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_f4            :  8; /* [ 7: 0],        r/w,       0xf4 */
            uint32_t reg_dp_gma_curve_f5            :  8; /* [15: 8],        r/w,       0xf5 */
            uint32_t reg_dp_gma_curve_f6            :  8; /* [23:16],        r/w,       0xf6 */
            uint32_t reg_dp_gma_curve_f7            :  8; /* [31:24],        r/w,       0xf7 */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_f4;

    /* 0x2F8 : disp_gma_curve_f8 */
    union {
        struct {
            uint32_t reg_dp_gma_curve_f8            :  8; /* [ 7: 0],        r/w,       0xf8 */
            uint32_t reg_dp_gma_curve_f9            :  8; /* [15: 8],        r/w,       0xf9 */
            uint32_t reg_dp_gma_curve_fa            :  8; /* [23:16],        r/w,       0xfa */
            uint32_t reg_dp_gma_curve_fb            :  8; /* [31:24],        r/w,       0xfb */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_f8;

    /* 0x2FC : disp_gma_curve_fc */
    union {
        struct {
            uint32_t reg_dp_gma_curve_fc            :  8; /* [ 7: 0],        r/w,       0xfc */
            uint32_t reg_dp_gma_curve_fd            :  8; /* [15: 8],        r/w,       0xfd */
            uint32_t reg_dp_gma_curve_fe            :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_dp_gma_curve_ff            :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } disp_gma_curve_fc;

};

typedef volatile struct isp_misc_reg isp_misc_reg_t;


#endif  /* __SPP_MISC_REG_H__ */
