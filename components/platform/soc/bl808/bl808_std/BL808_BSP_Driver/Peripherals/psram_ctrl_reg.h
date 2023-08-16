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
#ifndef  __PSRAM_CTRL_REG_H__
#define  __PSRAM_CTRL_REG_H__

#include "bl808.h"

/* 0x0 : psram_configure */
#define PSRAM_CTRL_PSRAM_CONFIGURE_OFFSET                       (0x0)
#define PSRAM_CTRL_REG_VENDOR_SEL                               PSRAM_CTRL_REG_VENDOR_SEL
#define PSRAM_CTRL_REG_VENDOR_SEL_POS                           (0U)
#define PSRAM_CTRL_REG_VENDOR_SEL_LEN                           (2U)
#define PSRAM_CTRL_REG_VENDOR_SEL_MSK                           (((1U<<PSRAM_CTRL_REG_VENDOR_SEL_LEN)-1)<<PSRAM_CTRL_REG_VENDOR_SEL_POS)
#define PSRAM_CTRL_REG_VENDOR_SEL_UMSK                          (~(((1U<<PSRAM_CTRL_REG_VENDOR_SEL_LEN)-1)<<PSRAM_CTRL_REG_VENDOR_SEL_POS))
#define PSRAM_CTRL_REG_AP_MR                                    PSRAM_CTRL_REG_AP_MR
#define PSRAM_CTRL_REG_AP_MR_POS                                (4U)
#define PSRAM_CTRL_REG_AP_MR_LEN                                (3U)
#define PSRAM_CTRL_REG_AP_MR_MSK                                (((1U<<PSRAM_CTRL_REG_AP_MR_LEN)-1)<<PSRAM_CTRL_REG_AP_MR_POS)
#define PSRAM_CTRL_REG_AP_MR_UMSK                               (~(((1U<<PSRAM_CTRL_REG_AP_MR_LEN)-1)<<PSRAM_CTRL_REG_AP_MR_POS))
#define PSRAM_CTRL_REG_WB_REG_SEL                               PSRAM_CTRL_REG_WB_REG_SEL
#define PSRAM_CTRL_REG_WB_REG_SEL_POS                           (8U)
#define PSRAM_CTRL_REG_WB_REG_SEL_LEN                           (2U)
#define PSRAM_CTRL_REG_WB_REG_SEL_MSK                           (((1U<<PSRAM_CTRL_REG_WB_REG_SEL_LEN)-1)<<PSRAM_CTRL_REG_WB_REG_SEL_POS)
#define PSRAM_CTRL_REG_WB_REG_SEL_UMSK                          (~(((1U<<PSRAM_CTRL_REG_WB_REG_SEL_LEN)-1)<<PSRAM_CTRL_REG_WB_REG_SEL_POS))
#define PSRAM_CTRL_REG_CONFIG_W_PUSLE                           PSRAM_CTRL_REG_CONFIG_W_PUSLE
#define PSRAM_CTRL_REG_CONFIG_W_PUSLE_POS                       (12U)
#define PSRAM_CTRL_REG_CONFIG_W_PUSLE_LEN                       (1U)
#define PSRAM_CTRL_REG_CONFIG_W_PUSLE_MSK                       (((1U<<PSRAM_CTRL_REG_CONFIG_W_PUSLE_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_W_PUSLE_POS)
#define PSRAM_CTRL_REG_CONFIG_W_PUSLE_UMSK                      (~(((1U<<PSRAM_CTRL_REG_CONFIG_W_PUSLE_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_W_PUSLE_POS))
#define PSRAM_CTRL_REG_CONFIG_R_PUSLE                           PSRAM_CTRL_REG_CONFIG_R_PUSLE
#define PSRAM_CTRL_REG_CONFIG_R_PUSLE_POS                       (13U)
#define PSRAM_CTRL_REG_CONFIG_R_PUSLE_LEN                       (1U)
#define PSRAM_CTRL_REG_CONFIG_R_PUSLE_MSK                       (((1U<<PSRAM_CTRL_REG_CONFIG_R_PUSLE_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_R_PUSLE_POS)
#define PSRAM_CTRL_REG_CONFIG_R_PUSLE_UMSK                      (~(((1U<<PSRAM_CTRL_REG_CONFIG_R_PUSLE_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_R_PUSLE_POS))
#define PSRAM_CTRL_STS_CONFIG_W_DONE                            PSRAM_CTRL_STS_CONFIG_W_DONE
#define PSRAM_CTRL_STS_CONFIG_W_DONE_POS                        (14U)
#define PSRAM_CTRL_STS_CONFIG_W_DONE_LEN                        (1U)
#define PSRAM_CTRL_STS_CONFIG_W_DONE_MSK                        (((1U<<PSRAM_CTRL_STS_CONFIG_W_DONE_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_W_DONE_POS)
#define PSRAM_CTRL_STS_CONFIG_W_DONE_UMSK                       (~(((1U<<PSRAM_CTRL_STS_CONFIG_W_DONE_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_W_DONE_POS))
#define PSRAM_CTRL_STS_CONFIG_R_DONE                            PSRAM_CTRL_STS_CONFIG_R_DONE
#define PSRAM_CTRL_STS_CONFIG_R_DONE_POS                        (15U)
#define PSRAM_CTRL_STS_CONFIG_R_DONE_LEN                        (1U)
#define PSRAM_CTRL_STS_CONFIG_R_DONE_MSK                        (((1U<<PSRAM_CTRL_STS_CONFIG_R_DONE_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_R_DONE_POS)
#define PSRAM_CTRL_STS_CONFIG_R_DONE_UMSK                       (~(((1U<<PSRAM_CTRL_STS_CONFIG_R_DONE_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_R_DONE_POS))
#define PSRAM_CTRL_REG_CONFIG_REQ                               PSRAM_CTRL_REG_CONFIG_REQ
#define PSRAM_CTRL_REG_CONFIG_REQ_POS                           (16U)
#define PSRAM_CTRL_REG_CONFIG_REQ_LEN                           (1U)
#define PSRAM_CTRL_REG_CONFIG_REQ_MSK                           (((1U<<PSRAM_CTRL_REG_CONFIG_REQ_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_REQ_POS)
#define PSRAM_CTRL_REG_CONFIG_REQ_UMSK                          (~(((1U<<PSRAM_CTRL_REG_CONFIG_REQ_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_REQ_POS))
#define PSRAM_CTRL_REG_CONFIG_GNT                               PSRAM_CTRL_REG_CONFIG_GNT
#define PSRAM_CTRL_REG_CONFIG_GNT_POS                           (17U)
#define PSRAM_CTRL_REG_CONFIG_GNT_LEN                           (1U)
#define PSRAM_CTRL_REG_CONFIG_GNT_MSK                           (((1U<<PSRAM_CTRL_REG_CONFIG_GNT_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_GNT_POS)
#define PSRAM_CTRL_REG_CONFIG_GNT_UMSK                          (~(((1U<<PSRAM_CTRL_REG_CONFIG_GNT_LEN)-1)<<PSRAM_CTRL_REG_CONFIG_GNT_POS))

/* 0x4 : psram_manual_control */
#define PSRAM_CTRL_PSRAM_MANUAL_CONTROL_OFFSET                  (0x4)
#define PSRAM_CTRL_REG_WC_SW                                    PSRAM_CTRL_REG_WC_SW
#define PSRAM_CTRL_REG_WC_SW_POS                                (0U)
#define PSRAM_CTRL_REG_WC_SW_LEN                                (6U)
#define PSRAM_CTRL_REG_WC_SW_MSK                                (((1U<<PSRAM_CTRL_REG_WC_SW_LEN)-1)<<PSRAM_CTRL_REG_WC_SW_POS)
#define PSRAM_CTRL_REG_WC_SW_UMSK                               (~(((1U<<PSRAM_CTRL_REG_WC_SW_LEN)-1)<<PSRAM_CTRL_REG_WC_SW_POS))
#define PSRAM_CTRL_REG_WC_SW_EN                                 PSRAM_CTRL_REG_WC_SW_EN
#define PSRAM_CTRL_REG_WC_SW_EN_POS                             (8U)
#define PSRAM_CTRL_REG_WC_SW_EN_LEN                             (1U)
#define PSRAM_CTRL_REG_WC_SW_EN_MSK                             (((1U<<PSRAM_CTRL_REG_WC_SW_EN_LEN)-1)<<PSRAM_CTRL_REG_WC_SW_EN_POS)
#define PSRAM_CTRL_REG_WC_SW_EN_UMSK                            (~(((1U<<PSRAM_CTRL_REG_WC_SW_EN_LEN)-1)<<PSRAM_CTRL_REG_WC_SW_EN_POS))
#define PSRAM_CTRL_REG_STATE_HOLD_TICK                          PSRAM_CTRL_REG_STATE_HOLD_TICK
#define PSRAM_CTRL_REG_STATE_HOLD_TICK_POS                      (9U)
#define PSRAM_CTRL_REG_STATE_HOLD_TICK_LEN                      (1U)
#define PSRAM_CTRL_REG_STATE_HOLD_TICK_MSK                      (((1U<<PSRAM_CTRL_REG_STATE_HOLD_TICK_LEN)-1)<<PSRAM_CTRL_REG_STATE_HOLD_TICK_POS)
#define PSRAM_CTRL_REG_STATE_HOLD_TICK_UMSK                     (~(((1U<<PSRAM_CTRL_REG_STATE_HOLD_TICK_LEN)-1)<<PSRAM_CTRL_REG_STATE_HOLD_TICK_POS))
#define PSRAM_CTRL_REG_FORCE_CEB_LOW                            PSRAM_CTRL_REG_FORCE_CEB_LOW
#define PSRAM_CTRL_REG_FORCE_CEB_LOW_POS                        (12U)
#define PSRAM_CTRL_REG_FORCE_CEB_LOW_LEN                        (1U)
#define PSRAM_CTRL_REG_FORCE_CEB_LOW_MSK                        (((1U<<PSRAM_CTRL_REG_FORCE_CEB_LOW_LEN)-1)<<PSRAM_CTRL_REG_FORCE_CEB_LOW_POS)
#define PSRAM_CTRL_REG_FORCE_CEB_LOW_UMSK                       (~(((1U<<PSRAM_CTRL_REG_FORCE_CEB_LOW_LEN)-1)<<PSRAM_CTRL_REG_FORCE_CEB_LOW_POS))
#define PSRAM_CTRL_REG_FORCE_CEB_HIGH                           PSRAM_CTRL_REG_FORCE_CEB_HIGH
#define PSRAM_CTRL_REG_FORCE_CEB_HIGH_POS                       (13U)
#define PSRAM_CTRL_REG_FORCE_CEB_HIGH_LEN                       (1U)
#define PSRAM_CTRL_REG_FORCE_CEB_HIGH_MSK                       (((1U<<PSRAM_CTRL_REG_FORCE_CEB_HIGH_LEN)-1)<<PSRAM_CTRL_REG_FORCE_CEB_HIGH_POS)
#define PSRAM_CTRL_REG_FORCE_CEB_HIGH_UMSK                      (~(((1U<<PSRAM_CTRL_REG_FORCE_CEB_HIGH_LEN)-1)<<PSRAM_CTRL_REG_FORCE_CEB_HIGH_POS))
#define PSRAM_CTRL_REG_PSRAM_RESETB                             PSRAM_CTRL_REG_PSRAM_RESETB
#define PSRAM_CTRL_REG_PSRAM_RESETB_POS                         (14U)
#define PSRAM_CTRL_REG_PSRAM_RESETB_LEN                         (1U)
#define PSRAM_CTRL_REG_PSRAM_RESETB_MSK                         (((1U<<PSRAM_CTRL_REG_PSRAM_RESETB_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_RESETB_POS)
#define PSRAM_CTRL_REG_PSRAM_RESETB_UMSK                        (~(((1U<<PSRAM_CTRL_REG_PSRAM_RESETB_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_RESETB_POS))
#define PSRAM_CTRL_REG_2X1X_EDGE_ALI                            PSRAM_CTRL_REG_2X1X_EDGE_ALI
#define PSRAM_CTRL_REG_2X1X_EDGE_ALI_POS                        (15U)
#define PSRAM_CTRL_REG_2X1X_EDGE_ALI_LEN                        (1U)
#define PSRAM_CTRL_REG_2X1X_EDGE_ALI_MSK                        (((1U<<PSRAM_CTRL_REG_2X1X_EDGE_ALI_LEN)-1)<<PSRAM_CTRL_REG_2X1X_EDGE_ALI_POS)
#define PSRAM_CTRL_REG_2X1X_EDGE_ALI_UMSK                       (~(((1U<<PSRAM_CTRL_REG_2X1X_EDGE_ALI_LEN)-1)<<PSRAM_CTRL_REG_2X1X_EDGE_ALI_POS))
#define PSRAM_CTRL_STS_CONFIG_READ                              PSRAM_CTRL_STS_CONFIG_READ
#define PSRAM_CTRL_STS_CONFIG_READ_POS                          (16U)
#define PSRAM_CTRL_STS_CONFIG_READ_LEN                          (16U)
#define PSRAM_CTRL_STS_CONFIG_READ_MSK                          (((1U<<PSRAM_CTRL_STS_CONFIG_READ_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_READ_POS)
#define PSRAM_CTRL_STS_CONFIG_READ_UMSK                         (~(((1U<<PSRAM_CTRL_STS_CONFIG_READ_LEN)-1)<<PSRAM_CTRL_STS_CONFIG_READ_POS))

/* 0x8 : fifo_thres_control */
#define PSRAM_CTRL_FIFO_THRES_CONTROL_OFFSET                    (0x8)
#define PSRAM_CTRL_REG_MASK_W_FIFO_CNT                          PSRAM_CTRL_REG_MASK_W_FIFO_CNT
#define PSRAM_CTRL_REG_MASK_W_FIFO_CNT_POS                      (0U)
#define PSRAM_CTRL_REG_MASK_W_FIFO_CNT_LEN                      (16U)
#define PSRAM_CTRL_REG_MASK_W_FIFO_CNT_MSK                      (((1U<<PSRAM_CTRL_REG_MASK_W_FIFO_CNT_LEN)-1)<<PSRAM_CTRL_REG_MASK_W_FIFO_CNT_POS)
#define PSRAM_CTRL_REG_MASK_W_FIFO_CNT_UMSK                     (~(((1U<<PSRAM_CTRL_REG_MASK_W_FIFO_CNT_LEN)-1)<<PSRAM_CTRL_REG_MASK_W_FIFO_CNT_POS))
#define PSRAM_CTRL_REG_MASK_R_FIFO_REM                          PSRAM_CTRL_REG_MASK_R_FIFO_REM
#define PSRAM_CTRL_REG_MASK_R_FIFO_REM_POS                      (16U)
#define PSRAM_CTRL_REG_MASK_R_FIFO_REM_LEN                      (16U)
#define PSRAM_CTRL_REG_MASK_R_FIFO_REM_MSK                      (((1U<<PSRAM_CTRL_REG_MASK_R_FIFO_REM_LEN)-1)<<PSRAM_CTRL_REG_MASK_R_FIFO_REM_POS)
#define PSRAM_CTRL_REG_MASK_R_FIFO_REM_UMSK                     (~(((1U<<PSRAM_CTRL_REG_MASK_R_FIFO_REM_LEN)-1)<<PSRAM_CTRL_REG_MASK_R_FIFO_REM_POS))

/* 0xC : psram_manual_control2 */
#define PSRAM_CTRL_PSRAM_MANUAL_CONTROL2_OFFSET                 (0xC)
#define PSRAM_CTRL_REG_HOLD_CYCLE_SW                            PSRAM_CTRL_REG_HOLD_CYCLE_SW
#define PSRAM_CTRL_REG_HOLD_CYCLE_SW_POS                        (0U)
#define PSRAM_CTRL_REG_HOLD_CYCLE_SW_LEN                        (4U)
#define PSRAM_CTRL_REG_HOLD_CYCLE_SW_MSK                        (((1U<<PSRAM_CTRL_REG_HOLD_CYCLE_SW_LEN)-1)<<PSRAM_CTRL_REG_HOLD_CYCLE_SW_POS)
#define PSRAM_CTRL_REG_HOLD_CYCLE_SW_UMSK                       (~(((1U<<PSRAM_CTRL_REG_HOLD_CYCLE_SW_LEN)-1)<<PSRAM_CTRL_REG_HOLD_CYCLE_SW_POS))
#define PSRAM_CTRL_REG_HC_SW_EN                                 PSRAM_CTRL_REG_HC_SW_EN
#define PSRAM_CTRL_REG_HC_SW_EN_POS                             (4U)
#define PSRAM_CTRL_REG_HC_SW_EN_LEN                             (1U)
#define PSRAM_CTRL_REG_HC_SW_EN_MSK                             (((1U<<PSRAM_CTRL_REG_HC_SW_EN_LEN)-1)<<PSRAM_CTRL_REG_HC_SW_EN_POS)
#define PSRAM_CTRL_REG_HC_SW_EN_UMSK                            (~(((1U<<PSRAM_CTRL_REG_HC_SW_EN_LEN)-1)<<PSRAM_CTRL_REG_HC_SW_EN_POS))

/* 0x10 : winbond_psram_configure */
#define PSRAM_CTRL_WINBOND_PSRAM_CONFIGURE_OFFSET               (0x10)
#define PSRAM_CTRL_REG_WB_LATENCY                               PSRAM_CTRL_REG_WB_LATENCY
#define PSRAM_CTRL_REG_WB_LATENCY_POS                           (0U)
#define PSRAM_CTRL_REG_WB_LATENCY_LEN                           (4U)
#define PSRAM_CTRL_REG_WB_LATENCY_MSK                           (((1U<<PSRAM_CTRL_REG_WB_LATENCY_LEN)-1)<<PSRAM_CTRL_REG_WB_LATENCY_POS)
#define PSRAM_CTRL_REG_WB_LATENCY_UMSK                          (~(((1U<<PSRAM_CTRL_REG_WB_LATENCY_LEN)-1)<<PSRAM_CTRL_REG_WB_LATENCY_POS))
#define PSRAM_CTRL_REG_WB_DRIVE_ST                              PSRAM_CTRL_REG_WB_DRIVE_ST
#define PSRAM_CTRL_REG_WB_DRIVE_ST_POS                          (4U)
#define PSRAM_CTRL_REG_WB_DRIVE_ST_LEN                          (2U)
#define PSRAM_CTRL_REG_WB_DRIVE_ST_MSK                          (((1U<<PSRAM_CTRL_REG_WB_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_REG_WB_DRIVE_ST_POS)
#define PSRAM_CTRL_REG_WB_DRIVE_ST_UMSK                         (~(((1U<<PSRAM_CTRL_REG_WB_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_REG_WB_DRIVE_ST_POS))
#define PSRAM_CTRL_REG_WB_BURST_LENGTH                          PSRAM_CTRL_REG_WB_BURST_LENGTH
#define PSRAM_CTRL_REG_WB_BURST_LENGTH_POS                      (8U)
#define PSRAM_CTRL_REG_WB_BURST_LENGTH_LEN                      (2U)
#define PSRAM_CTRL_REG_WB_BURST_LENGTH_MSK                      (((1U<<PSRAM_CTRL_REG_WB_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_REG_WB_BURST_LENGTH_POS)
#define PSRAM_CTRL_REG_WB_BURST_LENGTH_UMSK                     (~(((1U<<PSRAM_CTRL_REG_WB_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_REG_WB_BURST_LENGTH_POS))
#define PSRAM_CTRL_REG_WB_FIX_LATENCY                           PSRAM_CTRL_REG_WB_FIX_LATENCY
#define PSRAM_CTRL_REG_WB_FIX_LATENCY_POS                       (12U)
#define PSRAM_CTRL_REG_WB_FIX_LATENCY_LEN                       (1U)
#define PSRAM_CTRL_REG_WB_FIX_LATENCY_MSK                       (((1U<<PSRAM_CTRL_REG_WB_FIX_LATENCY_LEN)-1)<<PSRAM_CTRL_REG_WB_FIX_LATENCY_POS)
#define PSRAM_CTRL_REG_WB_FIX_LATENCY_UMSK                      (~(((1U<<PSRAM_CTRL_REG_WB_FIX_LATENCY_LEN)-1)<<PSRAM_CTRL_REG_WB_FIX_LATENCY_POS))
#define PSRAM_CTRL_REG_WB_DPD_DIS                               PSRAM_CTRL_REG_WB_DPD_DIS
#define PSRAM_CTRL_REG_WB_DPD_DIS_POS                           (13U)
#define PSRAM_CTRL_REG_WB_DPD_DIS_LEN                           (1U)
#define PSRAM_CTRL_REG_WB_DPD_DIS_MSK                           (((1U<<PSRAM_CTRL_REG_WB_DPD_DIS_LEN)-1)<<PSRAM_CTRL_REG_WB_DPD_DIS_POS)
#define PSRAM_CTRL_REG_WB_DPD_DIS_UMSK                          (~(((1U<<PSRAM_CTRL_REG_WB_DPD_DIS_LEN)-1)<<PSRAM_CTRL_REG_WB_DPD_DIS_POS))
#define PSRAM_CTRL_REG_WB_PASR                                  PSRAM_CTRL_REG_WB_PASR
#define PSRAM_CTRL_REG_WB_PASR_POS                              (16U)
#define PSRAM_CTRL_REG_WB_PASR_LEN                              (3U)
#define PSRAM_CTRL_REG_WB_PASR_MSK                              (((1U<<PSRAM_CTRL_REG_WB_PASR_LEN)-1)<<PSRAM_CTRL_REG_WB_PASR_POS)
#define PSRAM_CTRL_REG_WB_PASR_UMSK                             (~(((1U<<PSRAM_CTRL_REG_WB_PASR_LEN)-1)<<PSRAM_CTRL_REG_WB_PASR_POS))
#define PSRAM_CTRL_REG_WB_HYBRID_SLP                            PSRAM_CTRL_REG_WB_HYBRID_SLP
#define PSRAM_CTRL_REG_WB_HYBRID_SLP_POS                        (20U)
#define PSRAM_CTRL_REG_WB_HYBRID_SLP_LEN                        (1U)
#define PSRAM_CTRL_REG_WB_HYBRID_SLP_MSK                        (((1U<<PSRAM_CTRL_REG_WB_HYBRID_SLP_LEN)-1)<<PSRAM_CTRL_REG_WB_HYBRID_SLP_POS)
#define PSRAM_CTRL_REG_WB_HYBRID_SLP_UMSK                       (~(((1U<<PSRAM_CTRL_REG_WB_HYBRID_SLP_LEN)-1)<<PSRAM_CTRL_REG_WB_HYBRID_SLP_POS))

/* 0x14 : winbond_psram_status */
#define PSRAM_CTRL_WINBOND_PSRAM_STATUS_OFFSET                  (0x14)
#define PSRAM_CTRL_STS_WB_LATENCY                               PSRAM_CTRL_STS_WB_LATENCY
#define PSRAM_CTRL_STS_WB_LATENCY_POS                           (0U)
#define PSRAM_CTRL_STS_WB_LATENCY_LEN                           (4U)
#define PSRAM_CTRL_STS_WB_LATENCY_MSK                           (((1U<<PSRAM_CTRL_STS_WB_LATENCY_LEN)-1)<<PSRAM_CTRL_STS_WB_LATENCY_POS)
#define PSRAM_CTRL_STS_WB_LATENCY_UMSK                          (~(((1U<<PSRAM_CTRL_STS_WB_LATENCY_LEN)-1)<<PSRAM_CTRL_STS_WB_LATENCY_POS))
#define PSRAM_CTRL_STS_WB_DRIVE_ST                              PSRAM_CTRL_STS_WB_DRIVE_ST
#define PSRAM_CTRL_STS_WB_DRIVE_ST_POS                          (4U)
#define PSRAM_CTRL_STS_WB_DRIVE_ST_LEN                          (2U)
#define PSRAM_CTRL_STS_WB_DRIVE_ST_MSK                          (((1U<<PSRAM_CTRL_STS_WB_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_STS_WB_DRIVE_ST_POS)
#define PSRAM_CTRL_STS_WB_DRIVE_ST_UMSK                         (~(((1U<<PSRAM_CTRL_STS_WB_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_STS_WB_DRIVE_ST_POS))
#define PSRAM_CTRL_STS_WB_BURST_LENGTH                          PSRAM_CTRL_STS_WB_BURST_LENGTH
#define PSRAM_CTRL_STS_WB_BURST_LENGTH_POS                      (8U)
#define PSRAM_CTRL_STS_WB_BURST_LENGTH_LEN                      (2U)
#define PSRAM_CTRL_STS_WB_BURST_LENGTH_MSK                      (((1U<<PSRAM_CTRL_STS_WB_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_STS_WB_BURST_LENGTH_POS)
#define PSRAM_CTRL_STS_WB_BURST_LENGTH_UMSK                     (~(((1U<<PSRAM_CTRL_STS_WB_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_STS_WB_BURST_LENGTH_POS))
#define PSRAM_CTRL_STS_WB_FIX_LATENCY                           PSRAM_CTRL_STS_WB_FIX_LATENCY
#define PSRAM_CTRL_STS_WB_FIX_LATENCY_POS                       (12U)
#define PSRAM_CTRL_STS_WB_FIX_LATENCY_LEN                       (1U)
#define PSRAM_CTRL_STS_WB_FIX_LATENCY_MSK                       (((1U<<PSRAM_CTRL_STS_WB_FIX_LATENCY_LEN)-1)<<PSRAM_CTRL_STS_WB_FIX_LATENCY_POS)
#define PSRAM_CTRL_STS_WB_FIX_LATENCY_UMSK                      (~(((1U<<PSRAM_CTRL_STS_WB_FIX_LATENCY_LEN)-1)<<PSRAM_CTRL_STS_WB_FIX_LATENCY_POS))
#define PSRAM_CTRL_STS_WB_DPD_DIS                               PSRAM_CTRL_STS_WB_DPD_DIS
#define PSRAM_CTRL_STS_WB_DPD_DIS_POS                           (13U)
#define PSRAM_CTRL_STS_WB_DPD_DIS_LEN                           (1U)
#define PSRAM_CTRL_STS_WB_DPD_DIS_MSK                           (((1U<<PSRAM_CTRL_STS_WB_DPD_DIS_LEN)-1)<<PSRAM_CTRL_STS_WB_DPD_DIS_POS)
#define PSRAM_CTRL_STS_WB_DPD_DIS_UMSK                          (~(((1U<<PSRAM_CTRL_STS_WB_DPD_DIS_LEN)-1)<<PSRAM_CTRL_STS_WB_DPD_DIS_POS))
#define PSRAM_CTRL_STS_WB_PASR                                  PSRAM_CTRL_STS_WB_PASR
#define PSRAM_CTRL_STS_WB_PASR_POS                              (16U)
#define PSRAM_CTRL_STS_WB_PASR_LEN                              (3U)
#define PSRAM_CTRL_STS_WB_PASR_MSK                              (((1U<<PSRAM_CTRL_STS_WB_PASR_LEN)-1)<<PSRAM_CTRL_STS_WB_PASR_POS)
#define PSRAM_CTRL_STS_WB_PASR_UMSK                             (~(((1U<<PSRAM_CTRL_STS_WB_PASR_LEN)-1)<<PSRAM_CTRL_STS_WB_PASR_POS))
#define PSRAM_CTRL_STS_WB_HYBRID_SLP                            PSRAM_CTRL_STS_WB_HYBRID_SLP
#define PSRAM_CTRL_STS_WB_HYBRID_SLP_POS                        (20U)
#define PSRAM_CTRL_STS_WB_HYBRID_SLP_LEN                        (1U)
#define PSRAM_CTRL_STS_WB_HYBRID_SLP_MSK                        (((1U<<PSRAM_CTRL_STS_WB_HYBRID_SLP_LEN)-1)<<PSRAM_CTRL_STS_WB_HYBRID_SLP_POS)
#define PSRAM_CTRL_STS_WB_HYBRID_SLP_UMSK                       (~(((1U<<PSRAM_CTRL_STS_WB_HYBRID_SLP_LEN)-1)<<PSRAM_CTRL_STS_WB_HYBRID_SLP_POS))

/* 0x20 : apmemory_psram_configure */
#define PSRAM_CTRL_APMEMORY_PSRAM_CONFIGURE_OFFSET              (0x20)
#define PSRAM_CTRL_REG_AP_BURST_LENGTH                          PSRAM_CTRL_REG_AP_BURST_LENGTH
#define PSRAM_CTRL_REG_AP_BURST_LENGTH_POS                      (0U)
#define PSRAM_CTRL_REG_AP_BURST_LENGTH_LEN                      (2U)
#define PSRAM_CTRL_REG_AP_BURST_LENGTH_MSK                      (((1U<<PSRAM_CTRL_REG_AP_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_REG_AP_BURST_LENGTH_POS)
#define PSRAM_CTRL_REG_AP_BURST_LENGTH_UMSK                     (~(((1U<<PSRAM_CTRL_REG_AP_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_REG_AP_BURST_LENGTH_POS))
#define PSRAM_CTRL_REG_AP_BURST_TYPE                            PSRAM_CTRL_REG_AP_BURST_TYPE
#define PSRAM_CTRL_REG_AP_BURST_TYPE_POS                        (4U)
#define PSRAM_CTRL_REG_AP_BURST_TYPE_LEN                        (1U)
#define PSRAM_CTRL_REG_AP_BURST_TYPE_MSK                        (((1U<<PSRAM_CTRL_REG_AP_BURST_TYPE_LEN)-1)<<PSRAM_CTRL_REG_AP_BURST_TYPE_POS)
#define PSRAM_CTRL_REG_AP_BURST_TYPE_UMSK                       (~(((1U<<PSRAM_CTRL_REG_AP_BURST_TYPE_LEN)-1)<<PSRAM_CTRL_REG_AP_BURST_TYPE_POS))
#define PSRAM_CTRL_REG_AP_RBX                                   PSRAM_CTRL_REG_AP_RBX
#define PSRAM_CTRL_REG_AP_RBX_POS                               (5U)
#define PSRAM_CTRL_REG_AP_RBX_LEN                               (1U)
#define PSRAM_CTRL_REG_AP_RBX_MSK                               (((1U<<PSRAM_CTRL_REG_AP_RBX_LEN)-1)<<PSRAM_CTRL_REG_AP_RBX_POS)
#define PSRAM_CTRL_REG_AP_RBX_UMSK                              (~(((1U<<PSRAM_CTRL_REG_AP_RBX_LEN)-1)<<PSRAM_CTRL_REG_AP_RBX_POS))
#define PSRAM_CTRL_REG_AP_RF                                    PSRAM_CTRL_REG_AP_RF
#define PSRAM_CTRL_REG_AP_RF_POS                                (6U)
#define PSRAM_CTRL_REG_AP_RF_LEN                                (1U)
#define PSRAM_CTRL_REG_AP_RF_MSK                                (((1U<<PSRAM_CTRL_REG_AP_RF_LEN)-1)<<PSRAM_CTRL_REG_AP_RF_POS)
#define PSRAM_CTRL_REG_AP_RF_UMSK                               (~(((1U<<PSRAM_CTRL_REG_AP_RF_LEN)-1)<<PSRAM_CTRL_REG_AP_RF_POS))
#define PSRAM_CTRL_REG_AP_PASR                                  PSRAM_CTRL_REG_AP_PASR
#define PSRAM_CTRL_REG_AP_PASR_POS                              (8U)
#define PSRAM_CTRL_REG_AP_PASR_LEN                              (3U)
#define PSRAM_CTRL_REG_AP_PASR_MSK                              (((1U<<PSRAM_CTRL_REG_AP_PASR_LEN)-1)<<PSRAM_CTRL_REG_AP_PASR_POS)
#define PSRAM_CTRL_REG_AP_PASR_UMSK                             (~(((1U<<PSRAM_CTRL_REG_AP_PASR_LEN)-1)<<PSRAM_CTRL_REG_AP_PASR_POS))
#define PSRAM_CTRL_REG_AP_W_LATENCY_CODE                        PSRAM_CTRL_REG_AP_W_LATENCY_CODE
#define PSRAM_CTRL_REG_AP_W_LATENCY_CODE_POS                    (12U)
#define PSRAM_CTRL_REG_AP_W_LATENCY_CODE_LEN                    (3U)
#define PSRAM_CTRL_REG_AP_W_LATENCY_CODE_MSK                    (((1U<<PSRAM_CTRL_REG_AP_W_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_REG_AP_W_LATENCY_CODE_POS)
#define PSRAM_CTRL_REG_AP_W_LATENCY_CODE_UMSK                   (~(((1U<<PSRAM_CTRL_REG_AP_W_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_REG_AP_W_LATENCY_CODE_POS))
#define PSRAM_CTRL_REG_AP_DRIVE_ST                              PSRAM_CTRL_REG_AP_DRIVE_ST
#define PSRAM_CTRL_REG_AP_DRIVE_ST_POS                          (16U)
#define PSRAM_CTRL_REG_AP_DRIVE_ST_LEN                          (2U)
#define PSRAM_CTRL_REG_AP_DRIVE_ST_MSK                          (((1U<<PSRAM_CTRL_REG_AP_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_REG_AP_DRIVE_ST_POS)
#define PSRAM_CTRL_REG_AP_DRIVE_ST_UMSK                         (~(((1U<<PSRAM_CTRL_REG_AP_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_REG_AP_DRIVE_ST_POS))
#define PSRAM_CTRL_REG_AP_R_LATENCY_CODE                        PSRAM_CTRL_REG_AP_R_LATENCY_CODE
#define PSRAM_CTRL_REG_AP_R_LATENCY_CODE_POS                    (20U)
#define PSRAM_CTRL_REG_AP_R_LATENCY_CODE_LEN                    (3U)
#define PSRAM_CTRL_REG_AP_R_LATENCY_CODE_MSK                    (((1U<<PSRAM_CTRL_REG_AP_R_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_REG_AP_R_LATENCY_CODE_POS)
#define PSRAM_CTRL_REG_AP_R_LATENCY_CODE_UMSK                   (~(((1U<<PSRAM_CTRL_REG_AP_R_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_REG_AP_R_LATENCY_CODE_POS))
#define PSRAM_CTRL_REG_AP_R_LATENCY_TYPE                        PSRAM_CTRL_REG_AP_R_LATENCY_TYPE
#define PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_POS                    (24U)
#define PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_LEN                    (1U)
#define PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_MSK                    (((1U<<PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_LEN)-1)<<PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_POS)
#define PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_UMSK                   (~(((1U<<PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_LEN)-1)<<PSRAM_CTRL_REG_AP_R_LATENCY_TYPE_POS))
#define PSRAM_CTRL_REG_AP_LINEAR_DIS                            PSRAM_CTRL_REG_AP_LINEAR_DIS
#define PSRAM_CTRL_REG_AP_LINEAR_DIS_POS                        (25U)
#define PSRAM_CTRL_REG_AP_LINEAR_DIS_LEN                        (1U)
#define PSRAM_CTRL_REG_AP_LINEAR_DIS_MSK                        (((1U<<PSRAM_CTRL_REG_AP_LINEAR_DIS_LEN)-1)<<PSRAM_CTRL_REG_AP_LINEAR_DIS_POS)
#define PSRAM_CTRL_REG_AP_LINEAR_DIS_UMSK                       (~(((1U<<PSRAM_CTRL_REG_AP_LINEAR_DIS_LEN)-1)<<PSRAM_CTRL_REG_AP_LINEAR_DIS_POS))
#define PSRAM_CTRL_REG_AP_GLB_RESET_PULSE                       PSRAM_CTRL_REG_AP_GLB_RESET_PULSE
#define PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_POS                   (28U)
#define PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_LEN                   (1U)
#define PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_MSK                   (((1U<<PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_LEN)-1)<<PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_POS)
#define PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_UMSK                  (~(((1U<<PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_LEN)-1)<<PSRAM_CTRL_REG_AP_GLB_RESET_PULSE_POS))

/* 0x24 : apmemory_psram_status */
#define PSRAM_CTRL_APMEMORY_PSRAM_STATUS_OFFSET                 (0x24)
#define PSRAM_CTRL_STS_AP_BURST_LENGTH                          PSRAM_CTRL_STS_AP_BURST_LENGTH
#define PSRAM_CTRL_STS_AP_BURST_LENGTH_POS                      (0U)
#define PSRAM_CTRL_STS_AP_BURST_LENGTH_LEN                      (2U)
#define PSRAM_CTRL_STS_AP_BURST_LENGTH_MSK                      (((1U<<PSRAM_CTRL_STS_AP_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_STS_AP_BURST_LENGTH_POS)
#define PSRAM_CTRL_STS_AP_BURST_LENGTH_UMSK                     (~(((1U<<PSRAM_CTRL_STS_AP_BURST_LENGTH_LEN)-1)<<PSRAM_CTRL_STS_AP_BURST_LENGTH_POS))
#define PSRAM_CTRL_STS_AP_BURST_TYPE                            PSRAM_CTRL_STS_AP_BURST_TYPE
#define PSRAM_CTRL_STS_AP_BURST_TYPE_POS                        (4U)
#define PSRAM_CTRL_STS_AP_BURST_TYPE_LEN                        (1U)
#define PSRAM_CTRL_STS_AP_BURST_TYPE_MSK                        (((1U<<PSRAM_CTRL_STS_AP_BURST_TYPE_LEN)-1)<<PSRAM_CTRL_STS_AP_BURST_TYPE_POS)
#define PSRAM_CTRL_STS_AP_BURST_TYPE_UMSK                       (~(((1U<<PSRAM_CTRL_STS_AP_BURST_TYPE_LEN)-1)<<PSRAM_CTRL_STS_AP_BURST_TYPE_POS))
#define PSRAM_CTRL_STS_AP_RBX                                   PSRAM_CTRL_STS_AP_RBX
#define PSRAM_CTRL_STS_AP_RBX_POS                               (5U)
#define PSRAM_CTRL_STS_AP_RBX_LEN                               (1U)
#define PSRAM_CTRL_STS_AP_RBX_MSK                               (((1U<<PSRAM_CTRL_STS_AP_RBX_LEN)-1)<<PSRAM_CTRL_STS_AP_RBX_POS)
#define PSRAM_CTRL_STS_AP_RBX_UMSK                              (~(((1U<<PSRAM_CTRL_STS_AP_RBX_LEN)-1)<<PSRAM_CTRL_STS_AP_RBX_POS))
#define PSRAM_CTRL_STS_AP_RF                                    PSRAM_CTRL_STS_AP_RF
#define PSRAM_CTRL_STS_AP_RF_POS                                (6U)
#define PSRAM_CTRL_STS_AP_RF_LEN                                (1U)
#define PSRAM_CTRL_STS_AP_RF_MSK                                (((1U<<PSRAM_CTRL_STS_AP_RF_LEN)-1)<<PSRAM_CTRL_STS_AP_RF_POS)
#define PSRAM_CTRL_STS_AP_RF_UMSK                               (~(((1U<<PSRAM_CTRL_STS_AP_RF_LEN)-1)<<PSRAM_CTRL_STS_AP_RF_POS))
#define PSRAM_CTRL_STS_AP_PASR                                  PSRAM_CTRL_STS_AP_PASR
#define PSRAM_CTRL_STS_AP_PASR_POS                              (8U)
#define PSRAM_CTRL_STS_AP_PASR_LEN                              (3U)
#define PSRAM_CTRL_STS_AP_PASR_MSK                              (((1U<<PSRAM_CTRL_STS_AP_PASR_LEN)-1)<<PSRAM_CTRL_STS_AP_PASR_POS)
#define PSRAM_CTRL_STS_AP_PASR_UMSK                             (~(((1U<<PSRAM_CTRL_STS_AP_PASR_LEN)-1)<<PSRAM_CTRL_STS_AP_PASR_POS))
#define PSRAM_CTRL_STS_AP_W_LATENCY_CODE                        PSRAM_CTRL_STS_AP_W_LATENCY_CODE
#define PSRAM_CTRL_STS_AP_W_LATENCY_CODE_POS                    (12U)
#define PSRAM_CTRL_STS_AP_W_LATENCY_CODE_LEN                    (3U)
#define PSRAM_CTRL_STS_AP_W_LATENCY_CODE_MSK                    (((1U<<PSRAM_CTRL_STS_AP_W_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_STS_AP_W_LATENCY_CODE_POS)
#define PSRAM_CTRL_STS_AP_W_LATENCY_CODE_UMSK                   (~(((1U<<PSRAM_CTRL_STS_AP_W_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_STS_AP_W_LATENCY_CODE_POS))
#define PSRAM_CTRL_STS_AP_DRIVE_ST                              PSRAM_CTRL_STS_AP_DRIVE_ST
#define PSRAM_CTRL_STS_AP_DRIVE_ST_POS                          (16U)
#define PSRAM_CTRL_STS_AP_DRIVE_ST_LEN                          (2U)
#define PSRAM_CTRL_STS_AP_DRIVE_ST_MSK                          (((1U<<PSRAM_CTRL_STS_AP_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_STS_AP_DRIVE_ST_POS)
#define PSRAM_CTRL_STS_AP_DRIVE_ST_UMSK                         (~(((1U<<PSRAM_CTRL_STS_AP_DRIVE_ST_LEN)-1)<<PSRAM_CTRL_STS_AP_DRIVE_ST_POS))
#define PSRAM_CTRL_STS_AP_R_LATENCY_CODE                        PSRAM_CTRL_STS_AP_R_LATENCY_CODE
#define PSRAM_CTRL_STS_AP_R_LATENCY_CODE_POS                    (20U)
#define PSRAM_CTRL_STS_AP_R_LATENCY_CODE_LEN                    (3U)
#define PSRAM_CTRL_STS_AP_R_LATENCY_CODE_MSK                    (((1U<<PSRAM_CTRL_STS_AP_R_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_STS_AP_R_LATENCY_CODE_POS)
#define PSRAM_CTRL_STS_AP_R_LATENCY_CODE_UMSK                   (~(((1U<<PSRAM_CTRL_STS_AP_R_LATENCY_CODE_LEN)-1)<<PSRAM_CTRL_STS_AP_R_LATENCY_CODE_POS))
#define PSRAM_CTRL_STS_AP_R_LATENCY_TYPE                        PSRAM_CTRL_STS_AP_R_LATENCY_TYPE
#define PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_POS                    (24U)
#define PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_LEN                    (1U)
#define PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_MSK                    (((1U<<PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_LEN)-1)<<PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_POS)
#define PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_UMSK                   (~(((1U<<PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_LEN)-1)<<PSRAM_CTRL_STS_AP_R_LATENCY_TYPE_POS))

/* 0x80 : psram_intf_delay_ctrl0 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL0_OFFSET                (0x80)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN                      PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_POS                  (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_LEN                  (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_MSK                  (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_UMSK                 (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_OEN_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_CEB                          PSRAM_CTRL_REG_DELAY_SEL_O_CEB
#define PSRAM_CTRL_REG_DELAY_SEL_O_CEB_POS                      (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CEB_LEN                      (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CEB_MSK                      (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CEB_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CEB_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CEB_UMSK                     (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CEB_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CEB_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N                        PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_POS                    (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_LEN                    (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_MSK                    (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_UMSK                   (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_N_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK                          PSRAM_CTRL_REG_DELAY_SEL_O_CLK
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_POS                      (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_LEN                      (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_MSK                      (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_CLK_UMSK                     (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_CLK_POS))

/* 0x84 : psram_intf_delay_ctrl1 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL1_OFFSET                (0x84)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_POS                     (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ1_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_POS                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ0_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN                      PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_POS                  (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_LEN                  (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_MSK                  (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_UMSK                 (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ_OEN_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS                          PSRAM_CTRL_REG_DELAY_SEL_O_DQS
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_POS                      (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_LEN                      (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_MSK                      (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_DQS_UMSK                     (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_DQS_POS))

/* 0x88 : psram_intf_delay_ctrl2 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL2_OFFSET                (0x88)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_POS                     (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ5_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_POS                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ4_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_POS                     (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ3_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_POS                     (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ2_POS))

/* 0x8C : psram_intf_delay_ctrl3 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL3_OFFSET                (0x8C)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_POS                     (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ1_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_POS                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ0_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_POS                     (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ7_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6                         PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_POS                     (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_O_ADQ6_POS))

/* 0x90 : psram_intf_delay_ctrl4 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL4_OFFSET                (0x90)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_POS                     (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ5_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_POS                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ4_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_POS                     (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ3_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_POS                     (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ2_POS))

/* 0x94 : psram_intf_delay_ctrl5 */
#define PSRAM_CTRL_PSRAM_INTF_DELAY_CTRL5_OFFSET                (0x94)
#define PSRAM_CTRL_REG_DELAY_SEL_I_DQS                          PSRAM_CTRL_REG_DELAY_SEL_I_DQS
#define PSRAM_CTRL_REG_DELAY_SEL_I_DQS_POS                      (0U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_DQS_LEN                      (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_DQS_MSK                      (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_DQS_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_DQS_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_DQS_UMSK                     (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_DQS_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_DQS_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_POS                     (16U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ7_POS))
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6                         PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_POS                     (24U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_LEN                     (8U)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_MSK                     (((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_POS)
#define PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_UMSK                    (~(((1U<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_LEN)-1)<<PSRAM_CTRL_REG_DELAY_SEL_I_ADQ6_POS))

/* 0xC0 : psram_dbg_sel */
#define PSRAM_CTRL_PSRAM_DBG_SEL_OFFSET                         (0xC0)
#define PSRAM_CTRL_REG_PSRAM_DBG_EN                             PSRAM_CTRL_REG_PSRAM_DBG_EN
#define PSRAM_CTRL_REG_PSRAM_DBG_EN_POS                         (0U)
#define PSRAM_CTRL_REG_PSRAM_DBG_EN_LEN                         (1U)
#define PSRAM_CTRL_REG_PSRAM_DBG_EN_MSK                         (((1U<<PSRAM_CTRL_REG_PSRAM_DBG_EN_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DBG_EN_POS)
#define PSRAM_CTRL_REG_PSRAM_DBG_EN_UMSK                        (~(((1U<<PSRAM_CTRL_REG_PSRAM_DBG_EN_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DBG_EN_POS))
#define PSRAM_CTRL_REG_PSRAM_DBG_SEL                            PSRAM_CTRL_REG_PSRAM_DBG_SEL
#define PSRAM_CTRL_REG_PSRAM_DBG_SEL_POS                        (4U)
#define PSRAM_CTRL_REG_PSRAM_DBG_SEL_LEN                        (4U)
#define PSRAM_CTRL_REG_PSRAM_DBG_SEL_MSK                        (((1U<<PSRAM_CTRL_REG_PSRAM_DBG_SEL_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DBG_SEL_POS)
#define PSRAM_CTRL_REG_PSRAM_DBG_SEL_UMSK                       (~(((1U<<PSRAM_CTRL_REG_PSRAM_DBG_SEL_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DBG_SEL_POS))

/* 0xF0 : psram_dummy_reg */
#define PSRAM_CTRL_PSRAM_DUMMY_REG_OFFSET                       (0xF0)
#define PSRAM_CTRL_REG_PSRAM_DUMMY_REG                          PSRAM_CTRL_REG_PSRAM_DUMMY_REG
#define PSRAM_CTRL_REG_PSRAM_DUMMY_REG_POS                      (0U)
#define PSRAM_CTRL_REG_PSRAM_DUMMY_REG_LEN                      (32U)
#define PSRAM_CTRL_REG_PSRAM_DUMMY_REG_MSK                      (((1U<<PSRAM_CTRL_REG_PSRAM_DUMMY_REG_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DUMMY_REG_POS)
#define PSRAM_CTRL_REG_PSRAM_DUMMY_REG_UMSK                     (~(((1U<<PSRAM_CTRL_REG_PSRAM_DUMMY_REG_LEN)-1)<<PSRAM_CTRL_REG_PSRAM_DUMMY_REG_POS))


struct  psram_ctrl_reg {
    /* 0x0 : psram_configure */
    union {
        struct {
            uint32_t reg_vendor_sel                 :  2; /* [ 1: 0],        r/w,        0x2 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t reg_ap_mr                      :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_wb_reg_sel                 :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t reg_config_w_pusle             :  1; /* [   12],          w,        0x0 */
            uint32_t reg_config_r_pusle             :  1; /* [   13],          w,        0x0 */
            uint32_t sts_config_w_done              :  1; /* [   14],          r,        0x1 */
            uint32_t sts_config_r_done              :  1; /* [   15],          r,        0x1 */
            uint32_t reg_config_req                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_config_gnt                 :  1; /* [   17],          r,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_configure;

    /* 0x4 : psram_manual_control */
    union {
        struct {
            uint32_t reg_wc_sw                      :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_wc_sw_en                   :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_state_hold_tick            :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t reg_force_ceb_low              :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_force_ceb_high             :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_psram_resetb               :  1; /* [   14],        r/w,        0x1 */
            uint32_t reg_2x1x_edge_ali              :  1; /* [   15],        r/w,        0x0 */
            uint32_t sts_config_read                : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_manual_control;

    /* 0x8 : fifo_thres_control */
    union {
        struct {
            uint32_t reg_mask_w_fifo_cnt            : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_mask_r_fifo_rem            : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } fifo_thres_control;

    /* 0xC : psram_manual_control2 */
    union {
        struct {
            uint32_t reg_hold_cycle_sw              :  4; /* [ 3: 0],        r/w,        0x8 */
            uint32_t reg_hc_sw_en                   :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_manual_control2;

    /* 0x10 : winbond_psram_configure */
    union {
        struct {
            uint32_t reg_wb_latency                 :  4; /* [ 3: 0],        r/w,        0x1 */
            uint32_t reg_wb_drive_st                :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_wb_burst_length            :  2; /* [ 9: 8],        r/w,        0x3 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t reg_wb_fix_latency             :  1; /* [   12],        r/w,        0x1 */
            uint32_t reg_wb_dpd_dis                 :  1; /* [   13],        r/w,        0x1 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t reg_wb_pasr                    :  3; /* [18:16],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t reg_wb_hybrid_slp              :  1; /* [   20],        r/w,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } winbond_psram_configure;

    /* 0x14 : winbond_psram_status */
    union {
        struct {
            uint32_t sts_wb_latency                 :  4; /* [ 3: 0],          r,        0x1 */
            uint32_t sts_wb_drive_st                :  2; /* [ 5: 4],          r,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t sts_wb_burst_length            :  2; /* [ 9: 8],          r,        0x3 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t sts_wb_fix_latency             :  1; /* [   12],          r,        0x1 */
            uint32_t sts_wb_dpd_dis                 :  1; /* [   13],          r,        0x1 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t sts_wb_pasr                    :  3; /* [18:16],          r,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t sts_wb_hybrid_slp              :  1; /* [   20],          r,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } winbond_psram_status;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : apmemory_psram_configure */
    union {
        struct {
            uint32_t reg_ap_burst_length            :  2; /* [ 1: 0],        r/w,        0x1 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t reg_ap_burst_type              :  1; /* [    4],        r/w,        0x1 */
            uint32_t reg_ap_rbx                     :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_ap_rf                      :  1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_ap_pasr                    :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t reg_ap_w_latency_code          :  3; /* [14:12],        r/w,        0x2 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t reg_ap_drive_st                :  2; /* [17:16],        r/w,        0x1 */
            uint32_t reserved_18_19                 :  2; /* [19:18],       rsvd,        0x0 */
            uint32_t reg_ap_r_latency_code          :  3; /* [22:20],        r/w,        0x2 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t reg_ap_r_latency_type          :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_ap_linear_dis              :  1; /* [   25],        r/w,        0x0 */
            uint32_t reserved_26_27                 :  2; /* [27:26],       rsvd,        0x0 */
            uint32_t reg_ap_glb_reset_pulse         :  1; /* [   28],          w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } apmemory_psram_configure;

    /* 0x24 : apmemory_psram_status */
    union {
        struct {
            uint32_t sts_ap_burst_length            :  2; /* [ 1: 0],          r,        0x1 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t sts_ap_burst_type              :  1; /* [    4],          r,        0x1 */
            uint32_t sts_ap_rbx                     :  1; /* [    5],          r,        0x0 */
            uint32_t sts_ap_rf                      :  1; /* [    6],          r,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t sts_ap_pasr                    :  3; /* [10: 8],          r,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t sts_ap_w_latency_code          :  3; /* [14:12],          r,        0x2 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t sts_ap_drive_st                :  2; /* [17:16],          r,        0x1 */
            uint32_t reserved_18_19                 :  2; /* [19:18],       rsvd,        0x0 */
            uint32_t sts_ap_r_latency_code          :  3; /* [22:20],          r,        0x2 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t sts_ap_r_latency_type          :  1; /* [   24],          r,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } apmemory_psram_status;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[88];

    /* 0x80 : psram_intf_delay_ctrl0 */
    union {
        struct {
            uint32_t reg_delay_sel_o_dqs_oen        :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_ceb            :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_clk_n          :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_clk            :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl0;

    /* 0x84 : psram_intf_delay_ctrl1 */
    union {
        struct {
            uint32_t reg_delay_sel_o_adq1           :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq0           :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq_oen        :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_dqs            :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl1;

    /* 0x88 : psram_intf_delay_ctrl2 */
    union {
        struct {
            uint32_t reg_delay_sel_o_adq5           :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq4           :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq3           :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq2           :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl2;

    /* 0x8C : psram_intf_delay_ctrl3 */
    union {
        struct {
            uint32_t reg_delay_sel_i_adq1           :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq0           :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq7           :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_o_adq6           :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl3;

    /* 0x90 : psram_intf_delay_ctrl4 */
    union {
        struct {
            uint32_t reg_delay_sel_i_adq5           :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq4           :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq3           :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq2           :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl4;

    /* 0x94 : psram_intf_delay_ctrl5 */
    union {
        struct {
            uint32_t reg_delay_sel_i_dqs            : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq7           :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_delay_sel_i_adq6           :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_intf_delay_ctrl5;

    /* 0x98  reserved */
    uint8_t RESERVED0x98[40];

    /* 0xC0 : psram_dbg_sel */
    union {
        struct {
            uint32_t reg_psram_dbg_en               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_psram_dbg_sel              :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } psram_dbg_sel;

    /* 0xc4  reserved */
    uint8_t RESERVED0xc4[44];

    /* 0xF0 : psram_dummy_reg */
    union {
        struct {
            uint32_t reg_psram_dummy_reg            : 32; /* [31: 0],        r/w, 0xffff0000 */
        }BF;
        uint32_t WORD;
    } psram_dummy_reg;

};

typedef volatile struct psram_ctrl_reg psram_ctrl_reg_t;


#endif  /* __PSRAM_CTRL_REG_H__ */
