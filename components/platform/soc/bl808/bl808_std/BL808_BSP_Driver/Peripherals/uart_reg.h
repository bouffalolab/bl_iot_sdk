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
#ifndef  __UART_REG_H__
#define  __UART_REG_H__

#include "bl808.h"

/* 0x0 : utx_config */
#define UART_UTX_CONFIG_OFFSET                                  (0x0)
#define UART_CR_UTX_EN                                          UART_CR_UTX_EN
#define UART_CR_UTX_EN_POS                                      (0U)
#define UART_CR_UTX_EN_LEN                                      (1U)
#define UART_CR_UTX_EN_MSK                                      (((1U<<UART_CR_UTX_EN_LEN)-1)<<UART_CR_UTX_EN_POS)
#define UART_CR_UTX_EN_UMSK                                     (~(((1U<<UART_CR_UTX_EN_LEN)-1)<<UART_CR_UTX_EN_POS))
#define UART_CR_UTX_CTS_EN                                      UART_CR_UTX_CTS_EN
#define UART_CR_UTX_CTS_EN_POS                                  (1U)
#define UART_CR_UTX_CTS_EN_LEN                                  (1U)
#define UART_CR_UTX_CTS_EN_MSK                                  (((1U<<UART_CR_UTX_CTS_EN_LEN)-1)<<UART_CR_UTX_CTS_EN_POS)
#define UART_CR_UTX_CTS_EN_UMSK                                 (~(((1U<<UART_CR_UTX_CTS_EN_LEN)-1)<<UART_CR_UTX_CTS_EN_POS))
#define UART_CR_UTX_FRM_EN                                      UART_CR_UTX_FRM_EN
#define UART_CR_UTX_FRM_EN_POS                                  (2U)
#define UART_CR_UTX_FRM_EN_LEN                                  (1U)
#define UART_CR_UTX_FRM_EN_MSK                                  (((1U<<UART_CR_UTX_FRM_EN_LEN)-1)<<UART_CR_UTX_FRM_EN_POS)
#define UART_CR_UTX_FRM_EN_UMSK                                 (~(((1U<<UART_CR_UTX_FRM_EN_LEN)-1)<<UART_CR_UTX_FRM_EN_POS))
#define UART_CR_UTX_LIN_EN                                      UART_CR_UTX_LIN_EN
#define UART_CR_UTX_LIN_EN_POS                                  (3U)
#define UART_CR_UTX_LIN_EN_LEN                                  (1U)
#define UART_CR_UTX_LIN_EN_MSK                                  (((1U<<UART_CR_UTX_LIN_EN_LEN)-1)<<UART_CR_UTX_LIN_EN_POS)
#define UART_CR_UTX_LIN_EN_UMSK                                 (~(((1U<<UART_CR_UTX_LIN_EN_LEN)-1)<<UART_CR_UTX_LIN_EN_POS))
#define UART_CR_UTX_PRT_EN                                      UART_CR_UTX_PRT_EN
#define UART_CR_UTX_PRT_EN_POS                                  (4U)
#define UART_CR_UTX_PRT_EN_LEN                                  (1U)
#define UART_CR_UTX_PRT_EN_MSK                                  (((1U<<UART_CR_UTX_PRT_EN_LEN)-1)<<UART_CR_UTX_PRT_EN_POS)
#define UART_CR_UTX_PRT_EN_UMSK                                 (~(((1U<<UART_CR_UTX_PRT_EN_LEN)-1)<<UART_CR_UTX_PRT_EN_POS))
#define UART_CR_UTX_PRT_SEL                                     UART_CR_UTX_PRT_SEL
#define UART_CR_UTX_PRT_SEL_POS                                 (5U)
#define UART_CR_UTX_PRT_SEL_LEN                                 (1U)
#define UART_CR_UTX_PRT_SEL_MSK                                 (((1U<<UART_CR_UTX_PRT_SEL_LEN)-1)<<UART_CR_UTX_PRT_SEL_POS)
#define UART_CR_UTX_PRT_SEL_UMSK                                (~(((1U<<UART_CR_UTX_PRT_SEL_LEN)-1)<<UART_CR_UTX_PRT_SEL_POS))
#define UART_CR_UTX_IR_EN                                       UART_CR_UTX_IR_EN
#define UART_CR_UTX_IR_EN_POS                                   (6U)
#define UART_CR_UTX_IR_EN_LEN                                   (1U)
#define UART_CR_UTX_IR_EN_MSK                                   (((1U<<UART_CR_UTX_IR_EN_LEN)-1)<<UART_CR_UTX_IR_EN_POS)
#define UART_CR_UTX_IR_EN_UMSK                                  (~(((1U<<UART_CR_UTX_IR_EN_LEN)-1)<<UART_CR_UTX_IR_EN_POS))
#define UART_CR_UTX_IR_INV                                      UART_CR_UTX_IR_INV
#define UART_CR_UTX_IR_INV_POS                                  (7U)
#define UART_CR_UTX_IR_INV_LEN                                  (1U)
#define UART_CR_UTX_IR_INV_MSK                                  (((1U<<UART_CR_UTX_IR_INV_LEN)-1)<<UART_CR_UTX_IR_INV_POS)
#define UART_CR_UTX_IR_INV_UMSK                                 (~(((1U<<UART_CR_UTX_IR_INV_LEN)-1)<<UART_CR_UTX_IR_INV_POS))
#define UART_CR_UTX_BIT_CNT_D                                   UART_CR_UTX_BIT_CNT_D
#define UART_CR_UTX_BIT_CNT_D_POS                               (8U)
#define UART_CR_UTX_BIT_CNT_D_LEN                               (3U)
#define UART_CR_UTX_BIT_CNT_D_MSK                               (((1U<<UART_CR_UTX_BIT_CNT_D_LEN)-1)<<UART_CR_UTX_BIT_CNT_D_POS)
#define UART_CR_UTX_BIT_CNT_D_UMSK                              (~(((1U<<UART_CR_UTX_BIT_CNT_D_LEN)-1)<<UART_CR_UTX_BIT_CNT_D_POS))
#define UART_CR_UTX_BIT_CNT_P                                   UART_CR_UTX_BIT_CNT_P
#define UART_CR_UTX_BIT_CNT_P_POS                               (11U)
#define UART_CR_UTX_BIT_CNT_P_LEN                               (2U)
#define UART_CR_UTX_BIT_CNT_P_MSK                               (((1U<<UART_CR_UTX_BIT_CNT_P_LEN)-1)<<UART_CR_UTX_BIT_CNT_P_POS)
#define UART_CR_UTX_BIT_CNT_P_UMSK                              (~(((1U<<UART_CR_UTX_BIT_CNT_P_LEN)-1)<<UART_CR_UTX_BIT_CNT_P_POS))
#define UART_CR_UTX_BIT_CNT_B                                   UART_CR_UTX_BIT_CNT_B
#define UART_CR_UTX_BIT_CNT_B_POS                               (13U)
#define UART_CR_UTX_BIT_CNT_B_LEN                               (3U)
#define UART_CR_UTX_BIT_CNT_B_MSK                               (((1U<<UART_CR_UTX_BIT_CNT_B_LEN)-1)<<UART_CR_UTX_BIT_CNT_B_POS)
#define UART_CR_UTX_BIT_CNT_B_UMSK                              (~(((1U<<UART_CR_UTX_BIT_CNT_B_LEN)-1)<<UART_CR_UTX_BIT_CNT_B_POS))
#define UART_CR_UTX_LEN                                         UART_CR_UTX_LEN
#define UART_CR_UTX_LEN_POS                                     (16U)
#define UART_CR_UTX_LEN_LEN                                     (16U)
#define UART_CR_UTX_LEN_MSK                                     (((1U<<UART_CR_UTX_LEN_LEN)-1)<<UART_CR_UTX_LEN_POS)
#define UART_CR_UTX_LEN_UMSK                                    (~(((1U<<UART_CR_UTX_LEN_LEN)-1)<<UART_CR_UTX_LEN_POS))

/* 0x4 : urx_config */
#define UART_URX_CONFIG_OFFSET                                  (0x4)
#define UART_CR_URX_EN                                          UART_CR_URX_EN
#define UART_CR_URX_EN_POS                                      (0U)
#define UART_CR_URX_EN_LEN                                      (1U)
#define UART_CR_URX_EN_MSK                                      (((1U<<UART_CR_URX_EN_LEN)-1)<<UART_CR_URX_EN_POS)
#define UART_CR_URX_EN_UMSK                                     (~(((1U<<UART_CR_URX_EN_LEN)-1)<<UART_CR_URX_EN_POS))
#define UART_CR_URX_ABR_EN                                      UART_CR_URX_ABR_EN
#define UART_CR_URX_ABR_EN_POS                                  (1U)
#define UART_CR_URX_ABR_EN_LEN                                  (1U)
#define UART_CR_URX_ABR_EN_MSK                                  (((1U<<UART_CR_URX_ABR_EN_LEN)-1)<<UART_CR_URX_ABR_EN_POS)
#define UART_CR_URX_ABR_EN_UMSK                                 (~(((1U<<UART_CR_URX_ABR_EN_LEN)-1)<<UART_CR_URX_ABR_EN_POS))
#define UART_CR_URX_LIN_EN                                      UART_CR_URX_LIN_EN
#define UART_CR_URX_LIN_EN_POS                                  (3U)
#define UART_CR_URX_LIN_EN_LEN                                  (1U)
#define UART_CR_URX_LIN_EN_MSK                                  (((1U<<UART_CR_URX_LIN_EN_LEN)-1)<<UART_CR_URX_LIN_EN_POS)
#define UART_CR_URX_LIN_EN_UMSK                                 (~(((1U<<UART_CR_URX_LIN_EN_LEN)-1)<<UART_CR_URX_LIN_EN_POS))
#define UART_CR_URX_PRT_EN                                      UART_CR_URX_PRT_EN
#define UART_CR_URX_PRT_EN_POS                                  (4U)
#define UART_CR_URX_PRT_EN_LEN                                  (1U)
#define UART_CR_URX_PRT_EN_MSK                                  (((1U<<UART_CR_URX_PRT_EN_LEN)-1)<<UART_CR_URX_PRT_EN_POS)
#define UART_CR_URX_PRT_EN_UMSK                                 (~(((1U<<UART_CR_URX_PRT_EN_LEN)-1)<<UART_CR_URX_PRT_EN_POS))
#define UART_CR_URX_PRT_SEL                                     UART_CR_URX_PRT_SEL
#define UART_CR_URX_PRT_SEL_POS                                 (5U)
#define UART_CR_URX_PRT_SEL_LEN                                 (1U)
#define UART_CR_URX_PRT_SEL_MSK                                 (((1U<<UART_CR_URX_PRT_SEL_LEN)-1)<<UART_CR_URX_PRT_SEL_POS)
#define UART_CR_URX_PRT_SEL_UMSK                                (~(((1U<<UART_CR_URX_PRT_SEL_LEN)-1)<<UART_CR_URX_PRT_SEL_POS))
#define UART_CR_URX_IR_EN                                       UART_CR_URX_IR_EN
#define UART_CR_URX_IR_EN_POS                                   (6U)
#define UART_CR_URX_IR_EN_LEN                                   (1U)
#define UART_CR_URX_IR_EN_MSK                                   (((1U<<UART_CR_URX_IR_EN_LEN)-1)<<UART_CR_URX_IR_EN_POS)
#define UART_CR_URX_IR_EN_UMSK                                  (~(((1U<<UART_CR_URX_IR_EN_LEN)-1)<<UART_CR_URX_IR_EN_POS))
#define UART_CR_URX_IR_INV                                      UART_CR_URX_IR_INV
#define UART_CR_URX_IR_INV_POS                                  (7U)
#define UART_CR_URX_IR_INV_LEN                                  (1U)
#define UART_CR_URX_IR_INV_MSK                                  (((1U<<UART_CR_URX_IR_INV_LEN)-1)<<UART_CR_URX_IR_INV_POS)
#define UART_CR_URX_IR_INV_UMSK                                 (~(((1U<<UART_CR_URX_IR_INV_LEN)-1)<<UART_CR_URX_IR_INV_POS))
#define UART_CR_URX_BIT_CNT_D                                   UART_CR_URX_BIT_CNT_D
#define UART_CR_URX_BIT_CNT_D_POS                               (8U)
#define UART_CR_URX_BIT_CNT_D_LEN                               (3U)
#define UART_CR_URX_BIT_CNT_D_MSK                               (((1U<<UART_CR_URX_BIT_CNT_D_LEN)-1)<<UART_CR_URX_BIT_CNT_D_POS)
#define UART_CR_URX_BIT_CNT_D_UMSK                              (~(((1U<<UART_CR_URX_BIT_CNT_D_LEN)-1)<<UART_CR_URX_BIT_CNT_D_POS))
#define UART_CR_URX_DEG_EN                                      UART_CR_URX_DEG_EN
#define UART_CR_URX_DEG_EN_POS                                  (11U)
#define UART_CR_URX_DEG_EN_LEN                                  (1U)
#define UART_CR_URX_DEG_EN_MSK                                  (((1U<<UART_CR_URX_DEG_EN_LEN)-1)<<UART_CR_URX_DEG_EN_POS)
#define UART_CR_URX_DEG_EN_UMSK                                 (~(((1U<<UART_CR_URX_DEG_EN_LEN)-1)<<UART_CR_URX_DEG_EN_POS))
#define UART_CR_URX_DEG_CNT                                     UART_CR_URX_DEG_CNT
#define UART_CR_URX_DEG_CNT_POS                                 (12U)
#define UART_CR_URX_DEG_CNT_LEN                                 (4U)
#define UART_CR_URX_DEG_CNT_MSK                                 (((1U<<UART_CR_URX_DEG_CNT_LEN)-1)<<UART_CR_URX_DEG_CNT_POS)
#define UART_CR_URX_DEG_CNT_UMSK                                (~(((1U<<UART_CR_URX_DEG_CNT_LEN)-1)<<UART_CR_URX_DEG_CNT_POS))
#define UART_CR_URX_LEN                                         UART_CR_URX_LEN
#define UART_CR_URX_LEN_POS                                     (16U)
#define UART_CR_URX_LEN_LEN                                     (16U)
#define UART_CR_URX_LEN_MSK                                     (((1U<<UART_CR_URX_LEN_LEN)-1)<<UART_CR_URX_LEN_POS)
#define UART_CR_URX_LEN_UMSK                                    (~(((1U<<UART_CR_URX_LEN_LEN)-1)<<UART_CR_URX_LEN_POS))

/* 0x8 : uart_bit_prd */
#define UART_BIT_PRD_OFFSET                                     (0x8)
#define UART_CR_UTX_BIT_PRD                                     UART_CR_UTX_BIT_PRD
#define UART_CR_UTX_BIT_PRD_POS                                 (0U)
#define UART_CR_UTX_BIT_PRD_LEN                                 (16U)
#define UART_CR_UTX_BIT_PRD_MSK                                 (((1U<<UART_CR_UTX_BIT_PRD_LEN)-1)<<UART_CR_UTX_BIT_PRD_POS)
#define UART_CR_UTX_BIT_PRD_UMSK                                (~(((1U<<UART_CR_UTX_BIT_PRD_LEN)-1)<<UART_CR_UTX_BIT_PRD_POS))
#define UART_CR_URX_BIT_PRD                                     UART_CR_URX_BIT_PRD
#define UART_CR_URX_BIT_PRD_POS                                 (16U)
#define UART_CR_URX_BIT_PRD_LEN                                 (16U)
#define UART_CR_URX_BIT_PRD_MSK                                 (((1U<<UART_CR_URX_BIT_PRD_LEN)-1)<<UART_CR_URX_BIT_PRD_POS)
#define UART_CR_URX_BIT_PRD_UMSK                                (~(((1U<<UART_CR_URX_BIT_PRD_LEN)-1)<<UART_CR_URX_BIT_PRD_POS))

/* 0xC : data_config */
#define UART_DATA_CONFIG_OFFSET                                 (0xC)
#define UART_CR_UART_BIT_INV                                    UART_CR_UART_BIT_INV
#define UART_CR_UART_BIT_INV_POS                                (0U)
#define UART_CR_UART_BIT_INV_LEN                                (1U)
#define UART_CR_UART_BIT_INV_MSK                                (((1U<<UART_CR_UART_BIT_INV_LEN)-1)<<UART_CR_UART_BIT_INV_POS)
#define UART_CR_UART_BIT_INV_UMSK                               (~(((1U<<UART_CR_UART_BIT_INV_LEN)-1)<<UART_CR_UART_BIT_INV_POS))

/* 0x10 : utx_ir_position */
#define UART_UTX_IR_POSITION_OFFSET                             (0x10)
#define UART_CR_UTX_IR_POS_S                                    UART_CR_UTX_IR_POS_S
#define UART_CR_UTX_IR_POS_S_POS                                (0U)
#define UART_CR_UTX_IR_POS_S_LEN                                (16U)
#define UART_CR_UTX_IR_POS_S_MSK                                (((1U<<UART_CR_UTX_IR_POS_S_LEN)-1)<<UART_CR_UTX_IR_POS_S_POS)
#define UART_CR_UTX_IR_POS_S_UMSK                               (~(((1U<<UART_CR_UTX_IR_POS_S_LEN)-1)<<UART_CR_UTX_IR_POS_S_POS))
#define UART_CR_UTX_IR_POS_P                                    UART_CR_UTX_IR_POS_P
#define UART_CR_UTX_IR_POS_P_POS                                (16U)
#define UART_CR_UTX_IR_POS_P_LEN                                (16U)
#define UART_CR_UTX_IR_POS_P_MSK                                (((1U<<UART_CR_UTX_IR_POS_P_LEN)-1)<<UART_CR_UTX_IR_POS_P_POS)
#define UART_CR_UTX_IR_POS_P_UMSK                               (~(((1U<<UART_CR_UTX_IR_POS_P_LEN)-1)<<UART_CR_UTX_IR_POS_P_POS))

/* 0x14 : urx_ir_position */
#define UART_URX_IR_POSITION_OFFSET                             (0x14)
#define UART_CR_URX_IR_POS_S                                    UART_CR_URX_IR_POS_S
#define UART_CR_URX_IR_POS_S_POS                                (0U)
#define UART_CR_URX_IR_POS_S_LEN                                (16U)
#define UART_CR_URX_IR_POS_S_MSK                                (((1U<<UART_CR_URX_IR_POS_S_LEN)-1)<<UART_CR_URX_IR_POS_S_POS)
#define UART_CR_URX_IR_POS_S_UMSK                               (~(((1U<<UART_CR_URX_IR_POS_S_LEN)-1)<<UART_CR_URX_IR_POS_S_POS))

/* 0x18 : urx_rto_timer */
#define UART_URX_RTO_TIMER_OFFSET                               (0x18)
#define UART_CR_URX_RTO_VALUE                                   UART_CR_URX_RTO_VALUE
#define UART_CR_URX_RTO_VALUE_POS                               (0U)
#define UART_CR_URX_RTO_VALUE_LEN                               (8U)
#define UART_CR_URX_RTO_VALUE_MSK                               (((1U<<UART_CR_URX_RTO_VALUE_LEN)-1)<<UART_CR_URX_RTO_VALUE_POS)
#define UART_CR_URX_RTO_VALUE_UMSK                              (~(((1U<<UART_CR_URX_RTO_VALUE_LEN)-1)<<UART_CR_URX_RTO_VALUE_POS))

/* 0x1C : uart_sw_mode */
#define UART_SW_MODE_OFFSET                                     (0x1C)
#define UART_CR_UTX_TXD_SW_MODE                                 UART_CR_UTX_TXD_SW_MODE
#define UART_CR_UTX_TXD_SW_MODE_POS                             (0U)
#define UART_CR_UTX_TXD_SW_MODE_LEN                             (1U)
#define UART_CR_UTX_TXD_SW_MODE_MSK                             (((1U<<UART_CR_UTX_TXD_SW_MODE_LEN)-1)<<UART_CR_UTX_TXD_SW_MODE_POS)
#define UART_CR_UTX_TXD_SW_MODE_UMSK                            (~(((1U<<UART_CR_UTX_TXD_SW_MODE_LEN)-1)<<UART_CR_UTX_TXD_SW_MODE_POS))
#define UART_CR_UTX_TXD_SW_VAL                                  UART_CR_UTX_TXD_SW_VAL
#define UART_CR_UTX_TXD_SW_VAL_POS                              (1U)
#define UART_CR_UTX_TXD_SW_VAL_LEN                              (1U)
#define UART_CR_UTX_TXD_SW_VAL_MSK                              (((1U<<UART_CR_UTX_TXD_SW_VAL_LEN)-1)<<UART_CR_UTX_TXD_SW_VAL_POS)
#define UART_CR_UTX_TXD_SW_VAL_UMSK                             (~(((1U<<UART_CR_UTX_TXD_SW_VAL_LEN)-1)<<UART_CR_UTX_TXD_SW_VAL_POS))
#define UART_CR_URX_RTS_SW_MODE                                 UART_CR_URX_RTS_SW_MODE
#define UART_CR_URX_RTS_SW_MODE_POS                             (2U)
#define UART_CR_URX_RTS_SW_MODE_LEN                             (1U)
#define UART_CR_URX_RTS_SW_MODE_MSK                             (((1U<<UART_CR_URX_RTS_SW_MODE_LEN)-1)<<UART_CR_URX_RTS_SW_MODE_POS)
#define UART_CR_URX_RTS_SW_MODE_UMSK                            (~(((1U<<UART_CR_URX_RTS_SW_MODE_LEN)-1)<<UART_CR_URX_RTS_SW_MODE_POS))
#define UART_CR_URX_RTS_SW_VAL                                  UART_CR_URX_RTS_SW_VAL
#define UART_CR_URX_RTS_SW_VAL_POS                              (3U)
#define UART_CR_URX_RTS_SW_VAL_LEN                              (1U)
#define UART_CR_URX_RTS_SW_VAL_MSK                              (((1U<<UART_CR_URX_RTS_SW_VAL_LEN)-1)<<UART_CR_URX_RTS_SW_VAL_POS)
#define UART_CR_URX_RTS_SW_VAL_UMSK                             (~(((1U<<UART_CR_URX_RTS_SW_VAL_LEN)-1)<<UART_CR_URX_RTS_SW_VAL_POS))

/* 0x20 : UART interrupt status */
#define UART_INT_STS_OFFSET                                     (0x20)
#define UART_UTX_END_INT                                        UART_UTX_END_INT
#define UART_UTX_END_INT_POS                                    (0U)
#define UART_UTX_END_INT_LEN                                    (1U)
#define UART_UTX_END_INT_MSK                                    (((1U<<UART_UTX_END_INT_LEN)-1)<<UART_UTX_END_INT_POS)
#define UART_UTX_END_INT_UMSK                                   (~(((1U<<UART_UTX_END_INT_LEN)-1)<<UART_UTX_END_INT_POS))
#define UART_URX_END_INT                                        UART_URX_END_INT
#define UART_URX_END_INT_POS                                    (1U)
#define UART_URX_END_INT_LEN                                    (1U)
#define UART_URX_END_INT_MSK                                    (((1U<<UART_URX_END_INT_LEN)-1)<<UART_URX_END_INT_POS)
#define UART_URX_END_INT_UMSK                                   (~(((1U<<UART_URX_END_INT_LEN)-1)<<UART_URX_END_INT_POS))
#define UART_UTX_FRDY_INT                                       UART_UTX_FRDY_INT
#define UART_UTX_FRDY_INT_POS                                   (2U)
#define UART_UTX_FRDY_INT_LEN                                   (1U)
#define UART_UTX_FRDY_INT_MSK                                   (((1U<<UART_UTX_FRDY_INT_LEN)-1)<<UART_UTX_FRDY_INT_POS)
#define UART_UTX_FRDY_INT_UMSK                                  (~(((1U<<UART_UTX_FRDY_INT_LEN)-1)<<UART_UTX_FRDY_INT_POS))
#define UART_URX_FRDY_INT                                       UART_URX_FRDY_INT
#define UART_URX_FRDY_INT_POS                                   (3U)
#define UART_URX_FRDY_INT_LEN                                   (1U)
#define UART_URX_FRDY_INT_MSK                                   (((1U<<UART_URX_FRDY_INT_LEN)-1)<<UART_URX_FRDY_INT_POS)
#define UART_URX_FRDY_INT_UMSK                                  (~(((1U<<UART_URX_FRDY_INT_LEN)-1)<<UART_URX_FRDY_INT_POS))
#define UART_URX_RTO_INT                                        UART_URX_RTO_INT
#define UART_URX_RTO_INT_POS                                    (4U)
#define UART_URX_RTO_INT_LEN                                    (1U)
#define UART_URX_RTO_INT_MSK                                    (((1U<<UART_URX_RTO_INT_LEN)-1)<<UART_URX_RTO_INT_POS)
#define UART_URX_RTO_INT_UMSK                                   (~(((1U<<UART_URX_RTO_INT_LEN)-1)<<UART_URX_RTO_INT_POS))
#define UART_URX_PCE_INT                                        UART_URX_PCE_INT
#define UART_URX_PCE_INT_POS                                    (5U)
#define UART_URX_PCE_INT_LEN                                    (1U)
#define UART_URX_PCE_INT_MSK                                    (((1U<<UART_URX_PCE_INT_LEN)-1)<<UART_URX_PCE_INT_POS)
#define UART_URX_PCE_INT_UMSK                                   (~(((1U<<UART_URX_PCE_INT_LEN)-1)<<UART_URX_PCE_INT_POS))
#define UART_UTX_FER_INT                                        UART_UTX_FER_INT
#define UART_UTX_FER_INT_POS                                    (6U)
#define UART_UTX_FER_INT_LEN                                    (1U)
#define UART_UTX_FER_INT_MSK                                    (((1U<<UART_UTX_FER_INT_LEN)-1)<<UART_UTX_FER_INT_POS)
#define UART_UTX_FER_INT_UMSK                                   (~(((1U<<UART_UTX_FER_INT_LEN)-1)<<UART_UTX_FER_INT_POS))
#define UART_URX_FER_INT                                        UART_URX_FER_INT
#define UART_URX_FER_INT_POS                                    (7U)
#define UART_URX_FER_INT_LEN                                    (1U)
#define UART_URX_FER_INT_MSK                                    (((1U<<UART_URX_FER_INT_LEN)-1)<<UART_URX_FER_INT_POS)
#define UART_URX_FER_INT_UMSK                                   (~(((1U<<UART_URX_FER_INT_LEN)-1)<<UART_URX_FER_INT_POS))
#define UART_URX_LSE_INT                                        UART_URX_LSE_INT
#define UART_URX_LSE_INT_POS                                    (8U)
#define UART_URX_LSE_INT_LEN                                    (1U)
#define UART_URX_LSE_INT_MSK                                    (((1U<<UART_URX_LSE_INT_LEN)-1)<<UART_URX_LSE_INT_POS)
#define UART_URX_LSE_INT_UMSK                                   (~(((1U<<UART_URX_LSE_INT_LEN)-1)<<UART_URX_LSE_INT_POS))
#define UART_URX_BCR_INT                                        UART_URX_BCR_INT
#define UART_URX_BCR_INT_POS                                    (9U)
#define UART_URX_BCR_INT_LEN                                    (1U)
#define UART_URX_BCR_INT_MSK                                    (((1U<<UART_URX_BCR_INT_LEN)-1)<<UART_URX_BCR_INT_POS)
#define UART_URX_BCR_INT_UMSK                                   (~(((1U<<UART_URX_BCR_INT_LEN)-1)<<UART_URX_BCR_INT_POS))
#define UART_URX_ADS_INT                                        UART_URX_ADS_INT
#define UART_URX_ADS_INT_POS                                    (10U)
#define UART_URX_ADS_INT_LEN                                    (1U)
#define UART_URX_ADS_INT_MSK                                    (((1U<<UART_URX_ADS_INT_LEN)-1)<<UART_URX_ADS_INT_POS)
#define UART_URX_ADS_INT_UMSK                                   (~(((1U<<UART_URX_ADS_INT_LEN)-1)<<UART_URX_ADS_INT_POS))
#define UART_URX_AD5_INT                                        UART_URX_AD5_INT
#define UART_URX_AD5_INT_POS                                    (11U)
#define UART_URX_AD5_INT_LEN                                    (1U)
#define UART_URX_AD5_INT_MSK                                    (((1U<<UART_URX_AD5_INT_LEN)-1)<<UART_URX_AD5_INT_POS)
#define UART_URX_AD5_INT_UMSK                                   (~(((1U<<UART_URX_AD5_INT_LEN)-1)<<UART_URX_AD5_INT_POS))

/* 0x24 : UART interrupt mask */
#define UART_INT_MASK_OFFSET                                    (0x24)
#define UART_CR_UTX_END_MASK                                    UART_CR_UTX_END_MASK
#define UART_CR_UTX_END_MASK_POS                                (0U)
#define UART_CR_UTX_END_MASK_LEN                                (1U)
#define UART_CR_UTX_END_MASK_MSK                                (((1U<<UART_CR_UTX_END_MASK_LEN)-1)<<UART_CR_UTX_END_MASK_POS)
#define UART_CR_UTX_END_MASK_UMSK                               (~(((1U<<UART_CR_UTX_END_MASK_LEN)-1)<<UART_CR_UTX_END_MASK_POS))
#define UART_CR_URX_END_MASK                                    UART_CR_URX_END_MASK
#define UART_CR_URX_END_MASK_POS                                (1U)
#define UART_CR_URX_END_MASK_LEN                                (1U)
#define UART_CR_URX_END_MASK_MSK                                (((1U<<UART_CR_URX_END_MASK_LEN)-1)<<UART_CR_URX_END_MASK_POS)
#define UART_CR_URX_END_MASK_UMSK                               (~(((1U<<UART_CR_URX_END_MASK_LEN)-1)<<UART_CR_URX_END_MASK_POS))
#define UART_CR_UTX_FRDY_MASK                                   UART_CR_UTX_FRDY_MASK
#define UART_CR_UTX_FRDY_MASK_POS                               (2U)
#define UART_CR_UTX_FRDY_MASK_LEN                               (1U)
#define UART_CR_UTX_FRDY_MASK_MSK                               (((1U<<UART_CR_UTX_FRDY_MASK_LEN)-1)<<UART_CR_UTX_FRDY_MASK_POS)
#define UART_CR_UTX_FRDY_MASK_UMSK                              (~(((1U<<UART_CR_UTX_FRDY_MASK_LEN)-1)<<UART_CR_UTX_FRDY_MASK_POS))
#define UART_CR_URX_FRDY_MASK                                   UART_CR_URX_FRDY_MASK
#define UART_CR_URX_FRDY_MASK_POS                               (3U)
#define UART_CR_URX_FRDY_MASK_LEN                               (1U)
#define UART_CR_URX_FRDY_MASK_MSK                               (((1U<<UART_CR_URX_FRDY_MASK_LEN)-1)<<UART_CR_URX_FRDY_MASK_POS)
#define UART_CR_URX_FRDY_MASK_UMSK                              (~(((1U<<UART_CR_URX_FRDY_MASK_LEN)-1)<<UART_CR_URX_FRDY_MASK_POS))
#define UART_CR_URX_RTO_MASK                                    UART_CR_URX_RTO_MASK
#define UART_CR_URX_RTO_MASK_POS                                (4U)
#define UART_CR_URX_RTO_MASK_LEN                                (1U)
#define UART_CR_URX_RTO_MASK_MSK                                (((1U<<UART_CR_URX_RTO_MASK_LEN)-1)<<UART_CR_URX_RTO_MASK_POS)
#define UART_CR_URX_RTO_MASK_UMSK                               (~(((1U<<UART_CR_URX_RTO_MASK_LEN)-1)<<UART_CR_URX_RTO_MASK_POS))
#define UART_CR_URX_PCE_MASK                                    UART_CR_URX_PCE_MASK
#define UART_CR_URX_PCE_MASK_POS                                (5U)
#define UART_CR_URX_PCE_MASK_LEN                                (1U)
#define UART_CR_URX_PCE_MASK_MSK                                (((1U<<UART_CR_URX_PCE_MASK_LEN)-1)<<UART_CR_URX_PCE_MASK_POS)
#define UART_CR_URX_PCE_MASK_UMSK                               (~(((1U<<UART_CR_URX_PCE_MASK_LEN)-1)<<UART_CR_URX_PCE_MASK_POS))
#define UART_CR_UTX_FER_MASK                                    UART_CR_UTX_FER_MASK
#define UART_CR_UTX_FER_MASK_POS                                (6U)
#define UART_CR_UTX_FER_MASK_LEN                                (1U)
#define UART_CR_UTX_FER_MASK_MSK                                (((1U<<UART_CR_UTX_FER_MASK_LEN)-1)<<UART_CR_UTX_FER_MASK_POS)
#define UART_CR_UTX_FER_MASK_UMSK                               (~(((1U<<UART_CR_UTX_FER_MASK_LEN)-1)<<UART_CR_UTX_FER_MASK_POS))
#define UART_CR_URX_FER_MASK                                    UART_CR_URX_FER_MASK
#define UART_CR_URX_FER_MASK_POS                                (7U)
#define UART_CR_URX_FER_MASK_LEN                                (1U)
#define UART_CR_URX_FER_MASK_MSK                                (((1U<<UART_CR_URX_FER_MASK_LEN)-1)<<UART_CR_URX_FER_MASK_POS)
#define UART_CR_URX_FER_MASK_UMSK                               (~(((1U<<UART_CR_URX_FER_MASK_LEN)-1)<<UART_CR_URX_FER_MASK_POS))
#define UART_CR_URX_LSE_MASK                                    UART_CR_URX_LSE_MASK
#define UART_CR_URX_LSE_MASK_POS                                (8U)
#define UART_CR_URX_LSE_MASK_LEN                                (1U)
#define UART_CR_URX_LSE_MASK_MSK                                (((1U<<UART_CR_URX_LSE_MASK_LEN)-1)<<UART_CR_URX_LSE_MASK_POS)
#define UART_CR_URX_LSE_MASK_UMSK                               (~(((1U<<UART_CR_URX_LSE_MASK_LEN)-1)<<UART_CR_URX_LSE_MASK_POS))
#define UART_CR_URX_BCR_MASK                                    UART_CR_URX_BCR_MASK
#define UART_CR_URX_BCR_MASK_POS                                (9U)
#define UART_CR_URX_BCR_MASK_LEN                                (1U)
#define UART_CR_URX_BCR_MASK_MSK                                (((1U<<UART_CR_URX_BCR_MASK_LEN)-1)<<UART_CR_URX_BCR_MASK_POS)
#define UART_CR_URX_BCR_MASK_UMSK                               (~(((1U<<UART_CR_URX_BCR_MASK_LEN)-1)<<UART_CR_URX_BCR_MASK_POS))
#define UART_CR_URX_ADS_MASK                                    UART_CR_URX_ADS_MASK
#define UART_CR_URX_ADS_MASK_POS                                (10U)
#define UART_CR_URX_ADS_MASK_LEN                                (1U)
#define UART_CR_URX_ADS_MASK_MSK                                (((1U<<UART_CR_URX_ADS_MASK_LEN)-1)<<UART_CR_URX_ADS_MASK_POS)
#define UART_CR_URX_ADS_MASK_UMSK                               (~(((1U<<UART_CR_URX_ADS_MASK_LEN)-1)<<UART_CR_URX_ADS_MASK_POS))
#define UART_CR_URX_AD5_MASK                                    UART_CR_URX_AD5_MASK
#define UART_CR_URX_AD5_MASK_POS                                (11U)
#define UART_CR_URX_AD5_MASK_LEN                                (1U)
#define UART_CR_URX_AD5_MASK_MSK                                (((1U<<UART_CR_URX_AD5_MASK_LEN)-1)<<UART_CR_URX_AD5_MASK_POS)
#define UART_CR_URX_AD5_MASK_UMSK                               (~(((1U<<UART_CR_URX_AD5_MASK_LEN)-1)<<UART_CR_URX_AD5_MASK_POS))

/* 0x28 : UART interrupt clear */
#define UART_INT_CLEAR_OFFSET                                   (0x28)
#define UART_CR_UTX_END_CLR                                     UART_CR_UTX_END_CLR
#define UART_CR_UTX_END_CLR_POS                                 (0U)
#define UART_CR_UTX_END_CLR_LEN                                 (1U)
#define UART_CR_UTX_END_CLR_MSK                                 (((1U<<UART_CR_UTX_END_CLR_LEN)-1)<<UART_CR_UTX_END_CLR_POS)
#define UART_CR_UTX_END_CLR_UMSK                                (~(((1U<<UART_CR_UTX_END_CLR_LEN)-1)<<UART_CR_UTX_END_CLR_POS))
#define UART_CR_URX_END_CLR                                     UART_CR_URX_END_CLR
#define UART_CR_URX_END_CLR_POS                                 (1U)
#define UART_CR_URX_END_CLR_LEN                                 (1U)
#define UART_CR_URX_END_CLR_MSK                                 (((1U<<UART_CR_URX_END_CLR_LEN)-1)<<UART_CR_URX_END_CLR_POS)
#define UART_CR_URX_END_CLR_UMSK                                (~(((1U<<UART_CR_URX_END_CLR_LEN)-1)<<UART_CR_URX_END_CLR_POS))
#define UART_CR_URX_RTO_CLR                                     UART_CR_URX_RTO_CLR
#define UART_CR_URX_RTO_CLR_POS                                 (4U)
#define UART_CR_URX_RTO_CLR_LEN                                 (1U)
#define UART_CR_URX_RTO_CLR_MSK                                 (((1U<<UART_CR_URX_RTO_CLR_LEN)-1)<<UART_CR_URX_RTO_CLR_POS)
#define UART_CR_URX_RTO_CLR_UMSK                                (~(((1U<<UART_CR_URX_RTO_CLR_LEN)-1)<<UART_CR_URX_RTO_CLR_POS))
#define UART_CR_URX_PCE_CLR                                     UART_CR_URX_PCE_CLR
#define UART_CR_URX_PCE_CLR_POS                                 (5U)
#define UART_CR_URX_PCE_CLR_LEN                                 (1U)
#define UART_CR_URX_PCE_CLR_MSK                                 (((1U<<UART_CR_URX_PCE_CLR_LEN)-1)<<UART_CR_URX_PCE_CLR_POS)
#define UART_CR_URX_PCE_CLR_UMSK                                (~(((1U<<UART_CR_URX_PCE_CLR_LEN)-1)<<UART_CR_URX_PCE_CLR_POS))
#define UART_CR_URX_LSE_CLR                                     UART_CR_URX_LSE_CLR
#define UART_CR_URX_LSE_CLR_POS                                 (8U)
#define UART_CR_URX_LSE_CLR_LEN                                 (1U)
#define UART_CR_URX_LSE_CLR_MSK                                 (((1U<<UART_CR_URX_LSE_CLR_LEN)-1)<<UART_CR_URX_LSE_CLR_POS)
#define UART_CR_URX_LSE_CLR_UMSK                                (~(((1U<<UART_CR_URX_LSE_CLR_LEN)-1)<<UART_CR_URX_LSE_CLR_POS))
#define UART_CR_URX_BCR_CLR                                     UART_CR_URX_BCR_CLR
#define UART_CR_URX_BCR_CLR_POS                                 (9U)
#define UART_CR_URX_BCR_CLR_LEN                                 (1U)
#define UART_CR_URX_BCR_CLR_MSK                                 (((1U<<UART_CR_URX_BCR_CLR_LEN)-1)<<UART_CR_URX_BCR_CLR_POS)
#define UART_CR_URX_BCR_CLR_UMSK                                (~(((1U<<UART_CR_URX_BCR_CLR_LEN)-1)<<UART_CR_URX_BCR_CLR_POS))
#define UART_CR_URX_ADS_CLR                                     UART_CR_URX_ADS_CLR
#define UART_CR_URX_ADS_CLR_POS                                 (10U)
#define UART_CR_URX_ADS_CLR_LEN                                 (1U)
#define UART_CR_URX_ADS_CLR_MSK                                 (((1U<<UART_CR_URX_ADS_CLR_LEN)-1)<<UART_CR_URX_ADS_CLR_POS)
#define UART_CR_URX_ADS_CLR_UMSK                                (~(((1U<<UART_CR_URX_ADS_CLR_LEN)-1)<<UART_CR_URX_ADS_CLR_POS))
#define UART_CR_URX_AD5_CLR                                     UART_CR_URX_AD5_CLR
#define UART_CR_URX_AD5_CLR_POS                                 (11U)
#define UART_CR_URX_AD5_CLR_LEN                                 (1U)
#define UART_CR_URX_AD5_CLR_MSK                                 (((1U<<UART_CR_URX_AD5_CLR_LEN)-1)<<UART_CR_URX_AD5_CLR_POS)
#define UART_CR_URX_AD5_CLR_UMSK                                (~(((1U<<UART_CR_URX_AD5_CLR_LEN)-1)<<UART_CR_URX_AD5_CLR_POS))

/* 0x2C : UART interrupt enable */
#define UART_INT_EN_OFFSET                                      (0x2C)
#define UART_CR_UTX_END_EN                                      UART_CR_UTX_END_EN
#define UART_CR_UTX_END_EN_POS                                  (0U)
#define UART_CR_UTX_END_EN_LEN                                  (1U)
#define UART_CR_UTX_END_EN_MSK                                  (((1U<<UART_CR_UTX_END_EN_LEN)-1)<<UART_CR_UTX_END_EN_POS)
#define UART_CR_UTX_END_EN_UMSK                                 (~(((1U<<UART_CR_UTX_END_EN_LEN)-1)<<UART_CR_UTX_END_EN_POS))
#define UART_CR_URX_END_EN                                      UART_CR_URX_END_EN
#define UART_CR_URX_END_EN_POS                                  (1U)
#define UART_CR_URX_END_EN_LEN                                  (1U)
#define UART_CR_URX_END_EN_MSK                                  (((1U<<UART_CR_URX_END_EN_LEN)-1)<<UART_CR_URX_END_EN_POS)
#define UART_CR_URX_END_EN_UMSK                                 (~(((1U<<UART_CR_URX_END_EN_LEN)-1)<<UART_CR_URX_END_EN_POS))
#define UART_CR_UTX_FRDY_EN                                     UART_CR_UTX_FRDY_EN
#define UART_CR_UTX_FRDY_EN_POS                                 (2U)
#define UART_CR_UTX_FRDY_EN_LEN                                 (1U)
#define UART_CR_UTX_FRDY_EN_MSK                                 (((1U<<UART_CR_UTX_FRDY_EN_LEN)-1)<<UART_CR_UTX_FRDY_EN_POS)
#define UART_CR_UTX_FRDY_EN_UMSK                                (~(((1U<<UART_CR_UTX_FRDY_EN_LEN)-1)<<UART_CR_UTX_FRDY_EN_POS))
#define UART_CR_URX_FRDY_EN                                     UART_CR_URX_FRDY_EN
#define UART_CR_URX_FRDY_EN_POS                                 (3U)
#define UART_CR_URX_FRDY_EN_LEN                                 (1U)
#define UART_CR_URX_FRDY_EN_MSK                                 (((1U<<UART_CR_URX_FRDY_EN_LEN)-1)<<UART_CR_URX_FRDY_EN_POS)
#define UART_CR_URX_FRDY_EN_UMSK                                (~(((1U<<UART_CR_URX_FRDY_EN_LEN)-1)<<UART_CR_URX_FRDY_EN_POS))
#define UART_CR_URX_RTO_EN                                      UART_CR_URX_RTO_EN
#define UART_CR_URX_RTO_EN_POS                                  (4U)
#define UART_CR_URX_RTO_EN_LEN                                  (1U)
#define UART_CR_URX_RTO_EN_MSK                                  (((1U<<UART_CR_URX_RTO_EN_LEN)-1)<<UART_CR_URX_RTO_EN_POS)
#define UART_CR_URX_RTO_EN_UMSK                                 (~(((1U<<UART_CR_URX_RTO_EN_LEN)-1)<<UART_CR_URX_RTO_EN_POS))
#define UART_CR_URX_PCE_EN                                      UART_CR_URX_PCE_EN
#define UART_CR_URX_PCE_EN_POS                                  (5U)
#define UART_CR_URX_PCE_EN_LEN                                  (1U)
#define UART_CR_URX_PCE_EN_MSK                                  (((1U<<UART_CR_URX_PCE_EN_LEN)-1)<<UART_CR_URX_PCE_EN_POS)
#define UART_CR_URX_PCE_EN_UMSK                                 (~(((1U<<UART_CR_URX_PCE_EN_LEN)-1)<<UART_CR_URX_PCE_EN_POS))
#define UART_CR_UTX_FER_EN                                      UART_CR_UTX_FER_EN
#define UART_CR_UTX_FER_EN_POS                                  (6U)
#define UART_CR_UTX_FER_EN_LEN                                  (1U)
#define UART_CR_UTX_FER_EN_MSK                                  (((1U<<UART_CR_UTX_FER_EN_LEN)-1)<<UART_CR_UTX_FER_EN_POS)
#define UART_CR_UTX_FER_EN_UMSK                                 (~(((1U<<UART_CR_UTX_FER_EN_LEN)-1)<<UART_CR_UTX_FER_EN_POS))
#define UART_CR_URX_FER_EN                                      UART_CR_URX_FER_EN
#define UART_CR_URX_FER_EN_POS                                  (7U)
#define UART_CR_URX_FER_EN_LEN                                  (1U)
#define UART_CR_URX_FER_EN_MSK                                  (((1U<<UART_CR_URX_FER_EN_LEN)-1)<<UART_CR_URX_FER_EN_POS)
#define UART_CR_URX_FER_EN_UMSK                                 (~(((1U<<UART_CR_URX_FER_EN_LEN)-1)<<UART_CR_URX_FER_EN_POS))
#define UART_CR_URX_LSE_EN                                      UART_CR_URX_LSE_EN
#define UART_CR_URX_LSE_EN_POS                                  (8U)
#define UART_CR_URX_LSE_EN_LEN                                  (1U)
#define UART_CR_URX_LSE_EN_MSK                                  (((1U<<UART_CR_URX_LSE_EN_LEN)-1)<<UART_CR_URX_LSE_EN_POS)
#define UART_CR_URX_LSE_EN_UMSK                                 (~(((1U<<UART_CR_URX_LSE_EN_LEN)-1)<<UART_CR_URX_LSE_EN_POS))
#define UART_CR_URX_BCR_EN                                      UART_CR_URX_BCR_EN
#define UART_CR_URX_BCR_EN_POS                                  (9U)
#define UART_CR_URX_BCR_EN_LEN                                  (1U)
#define UART_CR_URX_BCR_EN_MSK                                  (((1U<<UART_CR_URX_BCR_EN_LEN)-1)<<UART_CR_URX_BCR_EN_POS)
#define UART_CR_URX_BCR_EN_UMSK                                 (~(((1U<<UART_CR_URX_BCR_EN_LEN)-1)<<UART_CR_URX_BCR_EN_POS))
#define UART_CR_URX_ADS_EN                                      UART_CR_URX_ADS_EN
#define UART_CR_URX_ADS_EN_POS                                  (10U)
#define UART_CR_URX_ADS_EN_LEN                                  (1U)
#define UART_CR_URX_ADS_EN_MSK                                  (((1U<<UART_CR_URX_ADS_EN_LEN)-1)<<UART_CR_URX_ADS_EN_POS)
#define UART_CR_URX_ADS_EN_UMSK                                 (~(((1U<<UART_CR_URX_ADS_EN_LEN)-1)<<UART_CR_URX_ADS_EN_POS))
#define UART_CR_URX_AD5_EN                                      UART_CR_URX_AD5_EN
#define UART_CR_URX_AD5_EN_POS                                  (11U)
#define UART_CR_URX_AD5_EN_LEN                                  (1U)
#define UART_CR_URX_AD5_EN_MSK                                  (((1U<<UART_CR_URX_AD5_EN_LEN)-1)<<UART_CR_URX_AD5_EN_POS)
#define UART_CR_URX_AD5_EN_UMSK                                 (~(((1U<<UART_CR_URX_AD5_EN_LEN)-1)<<UART_CR_URX_AD5_EN_POS))

/* 0x30 : uart_status */
#define UART_STATUS_OFFSET                                      (0x30)
#define UART_STS_UTX_BUS_BUSY                                   UART_STS_UTX_BUS_BUSY
#define UART_STS_UTX_BUS_BUSY_POS                               (0U)
#define UART_STS_UTX_BUS_BUSY_LEN                               (1U)
#define UART_STS_UTX_BUS_BUSY_MSK                               (((1U<<UART_STS_UTX_BUS_BUSY_LEN)-1)<<UART_STS_UTX_BUS_BUSY_POS)
#define UART_STS_UTX_BUS_BUSY_UMSK                              (~(((1U<<UART_STS_UTX_BUS_BUSY_LEN)-1)<<UART_STS_UTX_BUS_BUSY_POS))
#define UART_STS_URX_BUS_BUSY                                   UART_STS_URX_BUS_BUSY
#define UART_STS_URX_BUS_BUSY_POS                               (1U)
#define UART_STS_URX_BUS_BUSY_LEN                               (1U)
#define UART_STS_URX_BUS_BUSY_MSK                               (((1U<<UART_STS_URX_BUS_BUSY_LEN)-1)<<UART_STS_URX_BUS_BUSY_POS)
#define UART_STS_URX_BUS_BUSY_UMSK                              (~(((1U<<UART_STS_URX_BUS_BUSY_LEN)-1)<<UART_STS_URX_BUS_BUSY_POS))

/* 0x34 : sts_urx_abr_prd */
#define UART_STS_URX_ABR_PRD_OFFSET                             (0x34)
#define UART_STS_URX_ABR_PRD_START                              UART_STS_URX_ABR_PRD_START
#define UART_STS_URX_ABR_PRD_START_POS                          (0U)
#define UART_STS_URX_ABR_PRD_START_LEN                          (16U)
#define UART_STS_URX_ABR_PRD_START_MSK                          (((1U<<UART_STS_URX_ABR_PRD_START_LEN)-1)<<UART_STS_URX_ABR_PRD_START_POS)
#define UART_STS_URX_ABR_PRD_START_UMSK                         (~(((1U<<UART_STS_URX_ABR_PRD_START_LEN)-1)<<UART_STS_URX_ABR_PRD_START_POS))
#define UART_STS_URX_ABR_PRD_0X55                               UART_STS_URX_ABR_PRD_0X55
#define UART_STS_URX_ABR_PRD_0X55_POS                           (16U)
#define UART_STS_URX_ABR_PRD_0X55_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_0X55_MSK                           (((1U<<UART_STS_URX_ABR_PRD_0X55_LEN)-1)<<UART_STS_URX_ABR_PRD_0X55_POS)
#define UART_STS_URX_ABR_PRD_0X55_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_0X55_LEN)-1)<<UART_STS_URX_ABR_PRD_0X55_POS))

/* 0x38 : urx_abr_prd_b01 */
#define UART_URX_ABR_PRD_B01_OFFSET                             (0x38)
#define UART_STS_URX_ABR_PRD_BIT0                               UART_STS_URX_ABR_PRD_BIT0
#define UART_STS_URX_ABR_PRD_BIT0_POS                           (0U)
#define UART_STS_URX_ABR_PRD_BIT0_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT0_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT0_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT0_POS)
#define UART_STS_URX_ABR_PRD_BIT0_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT0_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT0_POS))
#define UART_STS_URX_ABR_PRD_BIT1                               UART_STS_URX_ABR_PRD_BIT1
#define UART_STS_URX_ABR_PRD_BIT1_POS                           (16U)
#define UART_STS_URX_ABR_PRD_BIT1_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT1_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT1_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT1_POS)
#define UART_STS_URX_ABR_PRD_BIT1_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT1_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT1_POS))

/* 0x3C : urx_abr_prd_b23 */
#define UART_URX_ABR_PRD_B23_OFFSET                             (0x3C)
#define UART_STS_URX_ABR_PRD_BIT2                               UART_STS_URX_ABR_PRD_BIT2
#define UART_STS_URX_ABR_PRD_BIT2_POS                           (0U)
#define UART_STS_URX_ABR_PRD_BIT2_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT2_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT2_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT2_POS)
#define UART_STS_URX_ABR_PRD_BIT2_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT2_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT2_POS))
#define UART_STS_URX_ABR_PRD_BIT3                               UART_STS_URX_ABR_PRD_BIT3
#define UART_STS_URX_ABR_PRD_BIT3_POS                           (16U)
#define UART_STS_URX_ABR_PRD_BIT3_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT3_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT3_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT3_POS)
#define UART_STS_URX_ABR_PRD_BIT3_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT3_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT3_POS))

/* 0x40 : urx_abr_prd_b45 */
#define UART_URX_ABR_PRD_B45_OFFSET                             (0x40)
#define UART_STS_URX_ABR_PRD_BIT4                               UART_STS_URX_ABR_PRD_BIT4
#define UART_STS_URX_ABR_PRD_BIT4_POS                           (0U)
#define UART_STS_URX_ABR_PRD_BIT4_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT4_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT4_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT4_POS)
#define UART_STS_URX_ABR_PRD_BIT4_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT4_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT4_POS))
#define UART_STS_URX_ABR_PRD_BIT5                               UART_STS_URX_ABR_PRD_BIT5
#define UART_STS_URX_ABR_PRD_BIT5_POS                           (16U)
#define UART_STS_URX_ABR_PRD_BIT5_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT5_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT5_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT5_POS)
#define UART_STS_URX_ABR_PRD_BIT5_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT5_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT5_POS))

/* 0x44 : urx_abr_prd_b67 */
#define UART_URX_ABR_PRD_B67_OFFSET                             (0x44)
#define UART_STS_URX_ABR_PRD_BIT6                               UART_STS_URX_ABR_PRD_BIT6
#define UART_STS_URX_ABR_PRD_BIT6_POS                           (0U)
#define UART_STS_URX_ABR_PRD_BIT6_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT6_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT6_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT6_POS)
#define UART_STS_URX_ABR_PRD_BIT6_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT6_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT6_POS))
#define UART_STS_URX_ABR_PRD_BIT7                               UART_STS_URX_ABR_PRD_BIT7
#define UART_STS_URX_ABR_PRD_BIT7_POS                           (16U)
#define UART_STS_URX_ABR_PRD_BIT7_LEN                           (16U)
#define UART_STS_URX_ABR_PRD_BIT7_MSK                           (((1U<<UART_STS_URX_ABR_PRD_BIT7_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT7_POS)
#define UART_STS_URX_ABR_PRD_BIT7_UMSK                          (~(((1U<<UART_STS_URX_ABR_PRD_BIT7_LEN)-1)<<UART_STS_URX_ABR_PRD_BIT7_POS))

/* 0x48 : urx_abr_pw_tol */
#define UART_URX_ABR_PW_TOL_OFFSET                              (0x48)
#define UART_CR_URX_ABR_PW_TOL                                  UART_CR_URX_ABR_PW_TOL
#define UART_CR_URX_ABR_PW_TOL_POS                              (0U)
#define UART_CR_URX_ABR_PW_TOL_LEN                              (8U)
#define UART_CR_URX_ABR_PW_TOL_MSK                              (((1U<<UART_CR_URX_ABR_PW_TOL_LEN)-1)<<UART_CR_URX_ABR_PW_TOL_POS)
#define UART_CR_URX_ABR_PW_TOL_UMSK                             (~(((1U<<UART_CR_URX_ABR_PW_TOL_LEN)-1)<<UART_CR_URX_ABR_PW_TOL_POS))

/* 0x50 : urx_bcr_int_cfg */
#define UART_URX_BCR_INT_CFG_OFFSET                             (0x50)
#define UART_CR_URX_BCR_VALUE                                   UART_CR_URX_BCR_VALUE
#define UART_CR_URX_BCR_VALUE_POS                               (0U)
#define UART_CR_URX_BCR_VALUE_LEN                               (16U)
#define UART_CR_URX_BCR_VALUE_MSK                               (((1U<<UART_CR_URX_BCR_VALUE_LEN)-1)<<UART_CR_URX_BCR_VALUE_POS)
#define UART_CR_URX_BCR_VALUE_UMSK                              (~(((1U<<UART_CR_URX_BCR_VALUE_LEN)-1)<<UART_CR_URX_BCR_VALUE_POS))
#define UART_STS_URX_BCR_COUNT                                  UART_STS_URX_BCR_COUNT
#define UART_STS_URX_BCR_COUNT_POS                              (16U)
#define UART_STS_URX_BCR_COUNT_LEN                              (16U)
#define UART_STS_URX_BCR_COUNT_MSK                              (((1U<<UART_STS_URX_BCR_COUNT_LEN)-1)<<UART_STS_URX_BCR_COUNT_POS)
#define UART_STS_URX_BCR_COUNT_UMSK                             (~(((1U<<UART_STS_URX_BCR_COUNT_LEN)-1)<<UART_STS_URX_BCR_COUNT_POS))

/* 0x54 : utx_rs485_cfg */
#define UART_UTX_RS485_CFG_OFFSET                               (0x54)
#define UART_CR_UTX_RS485_EN                                    UART_CR_UTX_RS485_EN
#define UART_CR_UTX_RS485_EN_POS                                (0U)
#define UART_CR_UTX_RS485_EN_LEN                                (1U)
#define UART_CR_UTX_RS485_EN_MSK                                (((1U<<UART_CR_UTX_RS485_EN_LEN)-1)<<UART_CR_UTX_RS485_EN_POS)
#define UART_CR_UTX_RS485_EN_UMSK                               (~(((1U<<UART_CR_UTX_RS485_EN_LEN)-1)<<UART_CR_UTX_RS485_EN_POS))
#define UART_CR_UTX_RS485_POL                                   UART_CR_UTX_RS485_POL
#define UART_CR_UTX_RS485_POL_POS                               (1U)
#define UART_CR_UTX_RS485_POL_LEN                               (1U)
#define UART_CR_UTX_RS485_POL_MSK                               (((1U<<UART_CR_UTX_RS485_POL_LEN)-1)<<UART_CR_UTX_RS485_POL_POS)
#define UART_CR_UTX_RS485_POL_UMSK                              (~(((1U<<UART_CR_UTX_RS485_POL_LEN)-1)<<UART_CR_UTX_RS485_POL_POS))

/* 0x80 : uart_fifo_config_0 */
#define UART_FIFO_CONFIG_0_OFFSET                               (0x80)
#define UART_DMA_TX_EN                                          UART_DMA_TX_EN
#define UART_DMA_TX_EN_POS                                      (0U)
#define UART_DMA_TX_EN_LEN                                      (1U)
#define UART_DMA_TX_EN_MSK                                      (((1U<<UART_DMA_TX_EN_LEN)-1)<<UART_DMA_TX_EN_POS)
#define UART_DMA_TX_EN_UMSK                                     (~(((1U<<UART_DMA_TX_EN_LEN)-1)<<UART_DMA_TX_EN_POS))
#define UART_DMA_RX_EN                                          UART_DMA_RX_EN
#define UART_DMA_RX_EN_POS                                      (1U)
#define UART_DMA_RX_EN_LEN                                      (1U)
#define UART_DMA_RX_EN_MSK                                      (((1U<<UART_DMA_RX_EN_LEN)-1)<<UART_DMA_RX_EN_POS)
#define UART_DMA_RX_EN_UMSK                                     (~(((1U<<UART_DMA_RX_EN_LEN)-1)<<UART_DMA_RX_EN_POS))
#define UART_TX_FIFO_CLR                                        UART_TX_FIFO_CLR
#define UART_TX_FIFO_CLR_POS                                    (2U)
#define UART_TX_FIFO_CLR_LEN                                    (1U)
#define UART_TX_FIFO_CLR_MSK                                    (((1U<<UART_TX_FIFO_CLR_LEN)-1)<<UART_TX_FIFO_CLR_POS)
#define UART_TX_FIFO_CLR_UMSK                                   (~(((1U<<UART_TX_FIFO_CLR_LEN)-1)<<UART_TX_FIFO_CLR_POS))
#define UART_RX_FIFO_CLR                                        UART_RX_FIFO_CLR
#define UART_RX_FIFO_CLR_POS                                    (3U)
#define UART_RX_FIFO_CLR_LEN                                    (1U)
#define UART_RX_FIFO_CLR_MSK                                    (((1U<<UART_RX_FIFO_CLR_LEN)-1)<<UART_RX_FIFO_CLR_POS)
#define UART_RX_FIFO_CLR_UMSK                                   (~(((1U<<UART_RX_FIFO_CLR_LEN)-1)<<UART_RX_FIFO_CLR_POS))
#define UART_TX_FIFO_OVERFLOW                                   UART_TX_FIFO_OVERFLOW
#define UART_TX_FIFO_OVERFLOW_POS                               (4U)
#define UART_TX_FIFO_OVERFLOW_LEN                               (1U)
#define UART_TX_FIFO_OVERFLOW_MSK                               (((1U<<UART_TX_FIFO_OVERFLOW_LEN)-1)<<UART_TX_FIFO_OVERFLOW_POS)
#define UART_TX_FIFO_OVERFLOW_UMSK                              (~(((1U<<UART_TX_FIFO_OVERFLOW_LEN)-1)<<UART_TX_FIFO_OVERFLOW_POS))
#define UART_TX_FIFO_UNDERFLOW                                  UART_TX_FIFO_UNDERFLOW
#define UART_TX_FIFO_UNDERFLOW_POS                              (5U)
#define UART_TX_FIFO_UNDERFLOW_LEN                              (1U)
#define UART_TX_FIFO_UNDERFLOW_MSK                              (((1U<<UART_TX_FIFO_UNDERFLOW_LEN)-1)<<UART_TX_FIFO_UNDERFLOW_POS)
#define UART_TX_FIFO_UNDERFLOW_UMSK                             (~(((1U<<UART_TX_FIFO_UNDERFLOW_LEN)-1)<<UART_TX_FIFO_UNDERFLOW_POS))
#define UART_RX_FIFO_OVERFLOW                                   UART_RX_FIFO_OVERFLOW
#define UART_RX_FIFO_OVERFLOW_POS                               (6U)
#define UART_RX_FIFO_OVERFLOW_LEN                               (1U)
#define UART_RX_FIFO_OVERFLOW_MSK                               (((1U<<UART_RX_FIFO_OVERFLOW_LEN)-1)<<UART_RX_FIFO_OVERFLOW_POS)
#define UART_RX_FIFO_OVERFLOW_UMSK                              (~(((1U<<UART_RX_FIFO_OVERFLOW_LEN)-1)<<UART_RX_FIFO_OVERFLOW_POS))
#define UART_RX_FIFO_UNDERFLOW                                  UART_RX_FIFO_UNDERFLOW
#define UART_RX_FIFO_UNDERFLOW_POS                              (7U)
#define UART_RX_FIFO_UNDERFLOW_LEN                              (1U)
#define UART_RX_FIFO_UNDERFLOW_MSK                              (((1U<<UART_RX_FIFO_UNDERFLOW_LEN)-1)<<UART_RX_FIFO_UNDERFLOW_POS)
#define UART_RX_FIFO_UNDERFLOW_UMSK                             (~(((1U<<UART_RX_FIFO_UNDERFLOW_LEN)-1)<<UART_RX_FIFO_UNDERFLOW_POS))

/* 0x84 : uart_fifo_config_1 */
#define UART_FIFO_CONFIG_1_OFFSET                               (0x84)
#define UART_TX_FIFO_CNT                                        UART_TX_FIFO_CNT
#define UART_TX_FIFO_CNT_POS                                    (0U)
#define UART_TX_FIFO_CNT_LEN                                    (6U)
#define UART_TX_FIFO_CNT_MSK                                    (((1U<<UART_TX_FIFO_CNT_LEN)-1)<<UART_TX_FIFO_CNT_POS)
#define UART_TX_FIFO_CNT_UMSK                                   (~(((1U<<UART_TX_FIFO_CNT_LEN)-1)<<UART_TX_FIFO_CNT_POS))
#define UART_RX_FIFO_CNT                                        UART_RX_FIFO_CNT
#define UART_RX_FIFO_CNT_POS                                    (8U)
#define UART_RX_FIFO_CNT_LEN                                    (6U)
#define UART_RX_FIFO_CNT_MSK                                    (((1U<<UART_RX_FIFO_CNT_LEN)-1)<<UART_RX_FIFO_CNT_POS)
#define UART_RX_FIFO_CNT_UMSK                                   (~(((1U<<UART_RX_FIFO_CNT_LEN)-1)<<UART_RX_FIFO_CNT_POS))
#define UART_TX_FIFO_TH                                         UART_TX_FIFO_TH
#define UART_TX_FIFO_TH_POS                                     (16U)
#define UART_TX_FIFO_TH_LEN                                     (5U)
#define UART_TX_FIFO_TH_MSK                                     (((1U<<UART_TX_FIFO_TH_LEN)-1)<<UART_TX_FIFO_TH_POS)
#define UART_TX_FIFO_TH_UMSK                                    (~(((1U<<UART_TX_FIFO_TH_LEN)-1)<<UART_TX_FIFO_TH_POS))
#define UART_RX_FIFO_TH                                         UART_RX_FIFO_TH
#define UART_RX_FIFO_TH_POS                                     (24U)
#define UART_RX_FIFO_TH_LEN                                     (5U)
#define UART_RX_FIFO_TH_MSK                                     (((1U<<UART_RX_FIFO_TH_LEN)-1)<<UART_RX_FIFO_TH_POS)
#define UART_RX_FIFO_TH_UMSK                                    (~(((1U<<UART_RX_FIFO_TH_LEN)-1)<<UART_RX_FIFO_TH_POS))

/* 0x88 : uart_fifo_wdata */
#define UART_FIFO_WDATA_OFFSET                                  (0x88)
#define UART_FIFO_WDATA                                         UART_FIFO_WDATA
#define UART_FIFO_WDATA_POS                                     (0U)
#define UART_FIFO_WDATA_LEN                                     (8U)
#define UART_FIFO_WDATA_MSK                                     (((1U<<UART_FIFO_WDATA_LEN)-1)<<UART_FIFO_WDATA_POS)
#define UART_FIFO_WDATA_UMSK                                    (~(((1U<<UART_FIFO_WDATA_LEN)-1)<<UART_FIFO_WDATA_POS))

/* 0x8C : uart_fifo_rdata */
#define UART_FIFO_RDATA_OFFSET                                  (0x8C)
#define UART_FIFO_RDATA                                         UART_FIFO_RDATA
#define UART_FIFO_RDATA_POS                                     (0U)
#define UART_FIFO_RDATA_LEN                                     (8U)
#define UART_FIFO_RDATA_MSK                                     (((1U<<UART_FIFO_RDATA_LEN)-1)<<UART_FIFO_RDATA_POS)
#define UART_FIFO_RDATA_UMSK                                    (~(((1U<<UART_FIFO_RDATA_LEN)-1)<<UART_FIFO_RDATA_POS))


struct  uart_reg {
    /* 0x0 : utx_config */
    union {
        struct {
            uint32_t cr_utx_en                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_utx_cts_en                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t cr_utx_frm_en                  :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_utx_lin_en                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t cr_utx_prt_en                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_utx_prt_sel                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_utx_ir_en                   :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_utx_ir_inv                  :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_utx_bit_cnt_d               :  3; /* [10: 8],        r/w,        0x7 */
            uint32_t cr_utx_bit_cnt_p               :  2; /* [12:11],        r/w,        0x1 */
            uint32_t cr_utx_bit_cnt_b               :  3; /* [15:13],        r/w,        0x4 */
            uint32_t cr_utx_len                     : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } utx_config;

    /* 0x4 : urx_config */
    union {
        struct {
            uint32_t cr_urx_en                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_urx_abr_en                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2                     :  1; /* [    2],       rsvd,        0x0 */
            uint32_t cr_urx_lin_en                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t cr_urx_prt_en                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_urx_prt_sel                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_urx_ir_en                   :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_urx_ir_inv                  :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_urx_bit_cnt_d               :  3; /* [10: 8],        r/w,        0x7 */
            uint32_t cr_urx_deg_en                  :  1; /* [   11],        r/w,        0x0 */
            uint32_t cr_urx_deg_cnt                 :  4; /* [15:12],        r/w,        0x0 */
            uint32_t cr_urx_len                     : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_config;

    /* 0x8 : uart_bit_prd */
    union {
        struct {
            uint32_t cr_utx_bit_prd                 : 16; /* [15: 0],        r/w,       0xff */
            uint32_t cr_urx_bit_prd                 : 16; /* [31:16],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } uart_bit_prd;

    /* 0xC : data_config */
    union {
        struct {
            uint32_t cr_uart_bit_inv                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } data_config;

    /* 0x10 : utx_ir_position */
    union {
        struct {
            uint32_t cr_utx_ir_pos_s                : 16; /* [15: 0],        r/w,       0x70 */
            uint32_t cr_utx_ir_pos_p                : 16; /* [31:16],        r/w,       0x9f */
        }BF;
        uint32_t WORD;
    } utx_ir_position;

    /* 0x14 : urx_ir_position */
    union {
        struct {
            uint32_t cr_urx_ir_pos_s                : 16; /* [15: 0],        r/w,       0x6f */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_ir_position;

    /* 0x18 : urx_rto_timer */
    union {
        struct {
            uint32_t cr_urx_rto_value               :  8; /* [ 7: 0],        r/w,        0xf */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_rto_timer;

    /* 0x1C : uart_sw_mode */
    union {
        struct {
            uint32_t cr_utx_txd_sw_mode             :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_utx_txd_sw_val              :  1; /* [    1],        r/w,        0x0 */
            uint32_t cr_urx_rts_sw_mode             :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_urx_rts_sw_val              :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_sw_mode;

    /* 0x20 : UART interrupt status */
    union {
        struct {
            uint32_t utx_end_int                    :  1; /* [    0],          r,        0x0 */
            uint32_t urx_end_int                    :  1; /* [    1],          r,        0x0 */
            uint32_t utx_frdy_int                   :  1; /* [    2],          r,        0x1 */
            uint32_t urx_frdy_int                   :  1; /* [    3],          r,        0x0 */
            uint32_t urx_rto_int                    :  1; /* [    4],          r,        0x0 */
            uint32_t urx_pce_int                    :  1; /* [    5],          r,        0x0 */
            uint32_t utx_fer_int                    :  1; /* [    6],          r,        0x0 */
            uint32_t urx_fer_int                    :  1; /* [    7],          r,        0x0 */
            uint32_t urx_lse_int                    :  1; /* [    8],          r,        0x0 */
            uint32_t urx_bcr_int                    :  1; /* [    9],          r,        0x0 */
            uint32_t urx_ads_int                    :  1; /* [   10],          r,        0x0 */
            uint32_t urx_ad5_int                    :  1; /* [   11],          r,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_int_sts;

    /* 0x24 : UART interrupt mask */
    union {
        struct {
            uint32_t cr_utx_end_mask                :  1; /* [    0],        r/w,        0x1 */
            uint32_t cr_urx_end_mask                :  1; /* [    1],        r/w,        0x1 */
            uint32_t cr_utx_frdy_mask               :  1; /* [    2],        r/w,        0x1 */
            uint32_t cr_urx_frdy_mask               :  1; /* [    3],        r/w,        0x1 */
            uint32_t cr_urx_rto_mask                :  1; /* [    4],        r/w,        0x1 */
            uint32_t cr_urx_pce_mask                :  1; /* [    5],        r/w,        0x1 */
            uint32_t cr_utx_fer_mask                :  1; /* [    6],        r/w,        0x1 */
            uint32_t cr_urx_fer_mask                :  1; /* [    7],        r/w,        0x1 */
            uint32_t cr_urx_lse_mask                :  1; /* [    8],        r/w,        0x1 */
            uint32_t cr_urx_bcr_mask                :  1; /* [    9],        r/w,        0x1 */
            uint32_t cr_urx_ads_mask                :  1; /* [   10],        r/w,        0x1 */
            uint32_t cr_urx_ad5_mask                :  1; /* [   11],        r/w,        0x1 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_int_mask;

    /* 0x28 : UART interrupt clear */
    union {
        struct {
            uint32_t cr_utx_end_clr                 :  1; /* [    0],        w1c,        0x0 */
            uint32_t cr_urx_end_clr                 :  1; /* [    1],        w1c,        0x0 */
            uint32_t rsvd_2                         :  1; /* [    2],       rsvd,        0x0 */
            uint32_t rsvd_3                         :  1; /* [    3],       rsvd,        0x0 */
            uint32_t cr_urx_rto_clr                 :  1; /* [    4],        w1c,        0x0 */
            uint32_t cr_urx_pce_clr                 :  1; /* [    5],        w1c,        0x0 */
            uint32_t rsvd_6                         :  1; /* [    6],       rsvd,        0x0 */
            uint32_t rsvd_7                         :  1; /* [    7],       rsvd,        0x0 */
            uint32_t cr_urx_lse_clr                 :  1; /* [    8],        w1c,        0x0 */
            uint32_t cr_urx_bcr_clr                 :  1; /* [    9],        w1c,        0x0 */
            uint32_t cr_urx_ads_clr                 :  1; /* [   10],        w1c,        0x0 */
            uint32_t cr_urx_ad5_clr                 :  1; /* [   11],        w1c,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_int_clear;

    /* 0x2C : UART interrupt enable */
    union {
        struct {
            uint32_t cr_utx_end_en                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t cr_urx_end_en                  :  1; /* [    1],        r/w,        0x1 */
            uint32_t cr_utx_frdy_en                 :  1; /* [    2],        r/w,        0x1 */
            uint32_t cr_urx_frdy_en                 :  1; /* [    3],        r/w,        0x1 */
            uint32_t cr_urx_rto_en                  :  1; /* [    4],        r/w,        0x1 */
            uint32_t cr_urx_pce_en                  :  1; /* [    5],        r/w,        0x1 */
            uint32_t cr_utx_fer_en                  :  1; /* [    6],        r/w,        0x1 */
            uint32_t cr_urx_fer_en                  :  1; /* [    7],        r/w,        0x1 */
            uint32_t cr_urx_lse_en                  :  1; /* [    8],        r/w,        0x1 */
            uint32_t cr_urx_bcr_en                  :  1; /* [    9],        r/w,        0x1 */
            uint32_t cr_urx_ads_en                  :  1; /* [   10],        r/w,        0x1 */
            uint32_t cr_urx_ad5_en                  :  1; /* [   11],        r/w,        0x1 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_int_en;

    /* 0x30 : uart_status */
    union {
        struct {
            uint32_t sts_utx_bus_busy               :  1; /* [    0],          r,        0x0 */
            uint32_t sts_urx_bus_busy               :  1; /* [    1],          r,        0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_status;

    /* 0x34 : sts_urx_abr_prd */
    union {
        struct {
            uint32_t sts_urx_abr_prd_start          : 16; /* [15: 0],          r,        0x0 */
            uint32_t sts_urx_abr_prd_0x55           : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } sts_urx_abr_prd;

    /* 0x38 : urx_abr_prd_b01 */
    union {
        struct {
            uint32_t sts_urx_abr_prd_bit0           : 16; /* [15: 0],          r,        0x0 */
            uint32_t sts_urx_abr_prd_bit1           : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_abr_prd_b01;

    /* 0x3C : urx_abr_prd_b23 */
    union {
        struct {
            uint32_t sts_urx_abr_prd_bit2           : 16; /* [15: 0],          r,        0x0 */
            uint32_t sts_urx_abr_prd_bit3           : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_abr_prd_b23;

    /* 0x40 : urx_abr_prd_b45 */
    union {
        struct {
            uint32_t sts_urx_abr_prd_bit4           : 16; /* [15: 0],          r,        0x0 */
            uint32_t sts_urx_abr_prd_bit5           : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_abr_prd_b45;

    /* 0x44 : urx_abr_prd_b67 */
    union {
        struct {
            uint32_t sts_urx_abr_prd_bit6           : 16; /* [15: 0],          r,        0x0 */
            uint32_t sts_urx_abr_prd_bit7           : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_abr_prd_b67;

    /* 0x48 : urx_abr_pw_tol */
    union {
        struct {
            uint32_t cr_urx_abr_pw_tol              :  8; /* [ 7: 0],        r/w,        0x3 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_abr_pw_tol;

    /* 0x4c  reserved */
    uint8_t RESERVED0x4c[4];

    /* 0x50 : urx_bcr_int_cfg */
    union {
        struct {
            uint32_t cr_urx_bcr_value               : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t sts_urx_bcr_count              : 16; /* [31:16],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } urx_bcr_int_cfg;

    /* 0x54 : utx_rs485_cfg */
    union {
        struct {
            uint32_t cr_utx_rs485_en                :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_utx_rs485_pol               :  1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } utx_rs485_cfg;

    /* 0x58  reserved */
    uint8_t RESERVED0x58[40];

    /* 0x80 : uart_fifo_config_0 */
    union {
        struct {
            uint32_t uart_dma_tx_en                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t uart_dma_rx_en                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t tx_fifo_clr                    :  1; /* [    2],        w1c,        0x0 */
            uint32_t rx_fifo_clr                    :  1; /* [    3],        w1c,        0x0 */
            uint32_t tx_fifo_overflow               :  1; /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow              :  1; /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow               :  1; /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow              :  1; /* [    7],          r,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_fifo_config_0;

    /* 0x84 : uart_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt                    :  6; /* [ 5: 0],          r,       0x20 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt                    :  6; /* [13: 8],          r,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t tx_fifo_th                     :  5; /* [20:16],        r/w,        0x0 */
            uint32_t reserved_21_23                 :  3; /* [23:21],       rsvd,        0x0 */
            uint32_t rx_fifo_th                     :  5; /* [28:24],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_fifo_config_1;

    /* 0x88 : uart_fifo_wdata */
    union {
        struct {
            uint32_t uart_fifo_wdata                :  8; /* [ 7: 0],          w,          x */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_fifo_wdata;

    /* 0x8C : uart_fifo_rdata */
    union {
        struct {
            uint32_t uart_fifo_rdata                :  8; /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } uart_fifo_rdata;

};

typedef volatile struct uart_reg uart_reg_t;


#endif  /* __UART_REG_H__ */
