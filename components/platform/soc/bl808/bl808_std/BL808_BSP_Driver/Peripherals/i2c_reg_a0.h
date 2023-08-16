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
#ifndef  __I2C_REG_H__
#define  __I2C_REG_H__

#include "bl808.h"

/* 0x0 : i2c_config */
#define I2C_CONFIG_OFFSET                                       (0x0)
#define I2C_CR_I2C_M_EN_POS                                     (0U)
#define I2C_CR_I2C_M_EN_LEN                                     (1U)
#define I2C_CR_I2C_M_EN_MSK                                     (((1U<<I2C_CR_I2C_M_EN_LEN)-1)<<I2C_CR_I2C_M_EN_POS)
#define I2C_CR_I2C_M_EN_UMSK                                    (~(((1U<<I2C_CR_I2C_M_EN_LEN)-1)<<I2C_CR_I2C_M_EN_POS))
#define I2C_CR_I2C_M_EN_SET                                     (1U<<I2C_CR_I2C_M_EN_POS)
#define I2C_CR_I2C_M_EN_CLEAR                                   (~(((1U<<I2C_CR_I2C_M_EN_LEN)-1)<<I2C_CR_I2C_M_EN_POS))
#define I2C_CR_I2C_DEG_EN_POS                                   (2U)
#define I2C_CR_I2C_DEG_EN_LEN                                   (1U)
#define I2C_CR_I2C_DEG_EN_MSK                                   (((1U<<I2C_CR_I2C_DEG_EN_LEN)-1)<<I2C_CR_I2C_DEG_EN_POS)
#define I2C_CR_I2C_DEG_EN_UMSK                                  (~(((1U<<I2C_CR_I2C_DEG_EN_LEN)-1)<<I2C_CR_I2C_DEG_EN_POS))
#define I2C_CR_I2C_DEG_EN_SET                                   (1U<<I2C_CR_I2C_DEG_EN_POS)
#define I2C_CR_I2C_DEG_EN_CLEAR                                 (~(((1U<<I2C_CR_I2C_DEG_EN_LEN)-1)<<I2C_CR_I2C_DEG_EN_POS))
#define I2C_CR_I2C_SCL_SYNC_EN_POS                              (3U)
#define I2C_CR_I2C_SCL_SYNC_EN_LEN                              (1U)
#define I2C_CR_I2C_SCL_SYNC_EN_MSK                              (((1U<<I2C_CR_I2C_SCL_SYNC_EN_LEN)-1)<<I2C_CR_I2C_SCL_SYNC_EN_POS)
#define I2C_CR_I2C_SCL_SYNC_EN_UMSK                             (~(((1U<<I2C_CR_I2C_SCL_SYNC_EN_LEN)-1)<<I2C_CR_I2C_SCL_SYNC_EN_POS))
#define I2C_CR_I2C_SCL_SYNC_EN_SET                              (1U<<I2C_CR_I2C_SCL_SYNC_EN_POS)
#define I2C_CR_I2C_SCL_SYNC_EN_CLEAR                            (~(((1U<<I2C_CR_I2C_SCL_SYNC_EN_LEN)-1)<<I2C_CR_I2C_SCL_SYNC_EN_POS))
#define I2C_CR_I2C_SLV_ADDR_POS                                 (8U)
#define I2C_CR_I2C_SLV_ADDR_LEN                                 (7U)
#define I2C_CR_I2C_SLV_ADDR_MSK                                 (((1U<<I2C_CR_I2C_SLV_ADDR_LEN)-1)<<I2C_CR_I2C_SLV_ADDR_POS)
#define I2C_CR_I2C_SLV_ADDR_UMSK                                (~(((1U<<I2C_CR_I2C_SLV_ADDR_LEN)-1)<<I2C_CR_I2C_SLV_ADDR_POS))
#define I2C_CR_I2C_PKT_NUM_POS                                  (16U)
#define I2C_CR_I2C_PKT_NUM_LEN                                  (2U)
#define I2C_CR_I2C_PKT_NUM_MSK                                  (((1U<<I2C_CR_I2C_PKT_NUM_LEN)-1)<<I2C_CR_I2C_PKT_NUM_POS)
#define I2C_CR_I2C_PKT_NUM_UMSK                                 (~(((1U<<I2C_CR_I2C_PKT_NUM_LEN)-1)<<I2C_CR_I2C_PKT_NUM_POS))
#define I2C_CR_I2C_PKT_DIR_POS                                  (20U)
#define I2C_CR_I2C_PKT_DIR_LEN                                  (4U)
#define I2C_CR_I2C_PKT_DIR_MSK                                  (((1U<<I2C_CR_I2C_PKT_DIR_LEN)-1)<<I2C_CR_I2C_PKT_DIR_POS)
#define I2C_CR_I2C_PKT_DIR_UMSK                                 (~(((1U<<I2C_CR_I2C_PKT_DIR_LEN)-1)<<I2C_CR_I2C_PKT_DIR_POS))
#define I2C_CR_I2C_DEG_CNT_POS                                  (28U)
#define I2C_CR_I2C_DEG_CNT_LEN                                  (4U)
#define I2C_CR_I2C_DEG_CNT_MSK                                  (((1U<<I2C_CR_I2C_DEG_CNT_LEN)-1)<<I2C_CR_I2C_DEG_CNT_POS)
#define I2C_CR_I2C_DEG_CNT_UMSK                                 (~(((1U<<I2C_CR_I2C_DEG_CNT_LEN)-1)<<I2C_CR_I2C_DEG_CNT_POS))

/* 0x4 : i2c_int_sts */
#define I2C_INT_STS_OFFSET                                      (0x4)
#define I2C_CR_I2C_INT_EN_POS                                   (0U)
#define I2C_CR_I2C_INT_EN_LEN                                   (1U)
#define I2C_CR_I2C_INT_EN_MSK                                   (((1U<<I2C_CR_I2C_INT_EN_LEN)-1)<<I2C_CR_I2C_INT_EN_POS)
#define I2C_CR_I2C_INT_EN_UMSK                                  (~(((1U<<I2C_CR_I2C_INT_EN_LEN)-1)<<I2C_CR_I2C_INT_EN_POS))
#define I2C_CR_I2C_INT_EN_SET                                   (1U<<I2C_CR_I2C_INT_EN_POS)
#define I2C_CR_I2C_INT_EN_CLEAR                                 (~(((1U<<I2C_CR_I2C_INT_EN_LEN)-1)<<I2C_CR_I2C_INT_EN_POS))
#define I2C_CR_I2C_INT_MASK_POS                                 (1U)
#define I2C_CR_I2C_INT_MASK_LEN                                 (1U)
#define I2C_CR_I2C_INT_MASK_MSK                                 (((1U<<I2C_CR_I2C_INT_MASK_LEN)-1)<<I2C_CR_I2C_INT_MASK_POS)
#define I2C_CR_I2C_INT_MASK_UMSK                                (~(((1U<<I2C_CR_I2C_INT_MASK_LEN)-1)<<I2C_CR_I2C_INT_MASK_POS))
#define I2C_CR_I2C_INT_MASK_SET                                 (1U<<I2C_CR_I2C_INT_MASK_POS)
#define I2C_CR_I2C_INT_MASK_CLEAR                               (~(((1U<<I2C_CR_I2C_INT_MASK_LEN)-1)<<I2C_CR_I2C_INT_MASK_POS))
#define I2C_STS_I2C_INT_POS                                     (2U)
#define I2C_STS_I2C_INT_LEN                                     (1U)
#define I2C_STS_I2C_INT_MSK                                     (((1U<<I2C_STS_I2C_INT_LEN)-1)<<I2C_STS_I2C_INT_POS)
#define I2C_STS_I2C_INT_UMSK                                    (~(((1U<<I2C_STS_I2C_INT_LEN)-1)<<I2C_STS_I2C_INT_POS))
#define I2C_STS_I2C_INT_SET                                     (1U<<I2C_STS_I2C_INT_POS)
#define I2C_STS_I2C_INT_CLEAR                                   (~(((1U<<I2C_STS_I2C_INT_LEN)-1)<<I2C_STS_I2C_INT_POS))
#define I2C_STS_I2C_GOT_NACK_POS                                (4U)
#define I2C_STS_I2C_GOT_NACK_LEN                                (1U)
#define I2C_STS_I2C_GOT_NACK_MSK                                (((1U<<I2C_STS_I2C_GOT_NACK_LEN)-1)<<I2C_STS_I2C_GOT_NACK_POS)
#define I2C_STS_I2C_GOT_NACK_UMSK                               (~(((1U<<I2C_STS_I2C_GOT_NACK_LEN)-1)<<I2C_STS_I2C_GOT_NACK_POS))
#define I2C_STS_I2C_GOT_NACK_SET                                (1U<<I2C_STS_I2C_GOT_NACK_POS)
#define I2C_STS_I2C_GOT_NACK_CLEAR                              (~(((1U<<I2C_STS_I2C_GOT_NACK_LEN)-1)<<I2C_STS_I2C_GOT_NACK_POS))
#define I2C_STS_I2C_ARB_LOST_POS                                (5U)
#define I2C_STS_I2C_ARB_LOST_LEN                                (1U)
#define I2C_STS_I2C_ARB_LOST_MSK                                (((1U<<I2C_STS_I2C_ARB_LOST_LEN)-1)<<I2C_STS_I2C_ARB_LOST_POS)
#define I2C_STS_I2C_ARB_LOST_UMSK                               (~(((1U<<I2C_STS_I2C_ARB_LOST_LEN)-1)<<I2C_STS_I2C_ARB_LOST_POS))
#define I2C_STS_I2C_ARB_LOST_SET                                (1U<<I2C_STS_I2C_ARB_LOST_POS)
#define I2C_STS_I2C_ARB_LOST_CLEAR                              (~(((1U<<I2C_STS_I2C_ARB_LOST_LEN)-1)<<I2C_STS_I2C_ARB_LOST_POS))
#define I2C_CR_I2C_BUS_BUSY_CLR_POS                             (8U)
#define I2C_CR_I2C_BUS_BUSY_CLR_LEN                             (1U)
#define I2C_CR_I2C_BUS_BUSY_CLR_MSK                             (((1U<<I2C_CR_I2C_BUS_BUSY_CLR_LEN)-1)<<I2C_CR_I2C_BUS_BUSY_CLR_POS)
#define I2C_CR_I2C_BUS_BUSY_CLR_UMSK                            (~(((1U<<I2C_CR_I2C_BUS_BUSY_CLR_LEN)-1)<<I2C_CR_I2C_BUS_BUSY_CLR_POS))
#define I2C_CR_I2C_BUS_BUSY_CLR_SET                             (1U<<I2C_CR_I2C_BUS_BUSY_CLR_POS)
#define I2C_CR_I2C_BUS_BUSY_CLR_CLEAR                           (~(((1U<<I2C_CR_I2C_BUS_BUSY_CLR_LEN)-1)<<I2C_CR_I2C_BUS_BUSY_CLR_POS))
#define I2C_STS_I2C_BUS_BUSY_POS                                (9U)
#define I2C_STS_I2C_BUS_BUSY_LEN                                (1U)
#define I2C_STS_I2C_BUS_BUSY_MSK                                (((1U<<I2C_STS_I2C_BUS_BUSY_LEN)-1)<<I2C_STS_I2C_BUS_BUSY_POS)
#define I2C_STS_I2C_BUS_BUSY_UMSK                               (~(((1U<<I2C_STS_I2C_BUS_BUSY_LEN)-1)<<I2C_STS_I2C_BUS_BUSY_POS))
#define I2C_STS_I2C_BUS_BUSY_SET                                (1U<<I2C_STS_I2C_BUS_BUSY_POS)
#define I2C_STS_I2C_BUS_BUSY_CLEAR                              (~(((1U<<I2C_STS_I2C_BUS_BUSY_LEN)-1)<<I2C_STS_I2C_BUS_BUSY_POS))

/* 0x8 : i2c_pkt_len_0 */
#define I2C_PKT_LEN_0_OFFSET                                    (0x8)
#define I2C_CR_I2C_PKT_0_LEN_POS                                (0U)
#define I2C_CR_I2C_PKT_0_LEN_LEN                                (16U)
#define I2C_CR_I2C_PKT_0_LEN_MSK                                (((1U<<I2C_CR_I2C_PKT_0_LEN_LEN)-1)<<I2C_CR_I2C_PKT_0_LEN_POS)
#define I2C_CR_I2C_PKT_0_LEN_UMSK                               (~(((1U<<I2C_CR_I2C_PKT_0_LEN_LEN)-1)<<I2C_CR_I2C_PKT_0_LEN_POS))
#define I2C_CR_I2C_PKT_1_LEN_POS                                (16U)
#define I2C_CR_I2C_PKT_1_LEN_LEN                                (16U)
#define I2C_CR_I2C_PKT_1_LEN_MSK                                (((1U<<I2C_CR_I2C_PKT_1_LEN_LEN)-1)<<I2C_CR_I2C_PKT_1_LEN_POS)
#define I2C_CR_I2C_PKT_1_LEN_UMSK                               (~(((1U<<I2C_CR_I2C_PKT_1_LEN_LEN)-1)<<I2C_CR_I2C_PKT_1_LEN_POS))

/* 0xC : i2c_pkt_len_1 */
#define I2C_PKT_LEN_1_OFFSET                                    (0xC)
#define I2C_CR_I2C_PKT_2_LEN_POS                                (0U)
#define I2C_CR_I2C_PKT_2_LEN_LEN                                (16U)
#define I2C_CR_I2C_PKT_2_LEN_MSK                                (((1U<<I2C_CR_I2C_PKT_2_LEN_LEN)-1)<<I2C_CR_I2C_PKT_2_LEN_POS)
#define I2C_CR_I2C_PKT_2_LEN_UMSK                               (~(((1U<<I2C_CR_I2C_PKT_2_LEN_LEN)-1)<<I2C_CR_I2C_PKT_2_LEN_POS))
#define I2C_CR_I2C_PKT_3_LEN_POS                                (16U)
#define I2C_CR_I2C_PKT_3_LEN_LEN                                (16U)
#define I2C_CR_I2C_PKT_3_LEN_MSK                                (((1U<<I2C_CR_I2C_PKT_3_LEN_LEN)-1)<<I2C_CR_I2C_PKT_3_LEN_POS)
#define I2C_CR_I2C_PKT_3_LEN_UMSK                               (~(((1U<<I2C_CR_I2C_PKT_3_LEN_LEN)-1)<<I2C_CR_I2C_PKT_3_LEN_POS))

/* 0x10 : i2c_prd_start */
#define I2C_PRD_START_OFFSET                                    (0x10)
#define I2C_CR_I2C_PRD_S_PH_0_POS                               (0U)
#define I2C_CR_I2C_PRD_S_PH_0_LEN                               (8U)
#define I2C_CR_I2C_PRD_S_PH_0_MSK                               (((1U<<I2C_CR_I2C_PRD_S_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_0_POS)
#define I2C_CR_I2C_PRD_S_PH_0_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_S_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_0_POS))
#define I2C_CR_I2C_PRD_S_PH_1_POS                               (8U)
#define I2C_CR_I2C_PRD_S_PH_1_LEN                               (8U)
#define I2C_CR_I2C_PRD_S_PH_1_MSK                               (((1U<<I2C_CR_I2C_PRD_S_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_1_POS)
#define I2C_CR_I2C_PRD_S_PH_1_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_S_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_1_POS))
#define I2C_CR_I2C_PRD_S_PH_2_POS                               (16U)
#define I2C_CR_I2C_PRD_S_PH_2_LEN                               (8U)
#define I2C_CR_I2C_PRD_S_PH_2_MSK                               (((1U<<I2C_CR_I2C_PRD_S_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_2_POS)
#define I2C_CR_I2C_PRD_S_PH_2_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_S_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_2_POS))
#define I2C_CR_I2C_PRD_S_PH_3_POS                               (24U)
#define I2C_CR_I2C_PRD_S_PH_3_LEN                               (8U)
#define I2C_CR_I2C_PRD_S_PH_3_MSK                               (((1U<<I2C_CR_I2C_PRD_S_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_3_POS)
#define I2C_CR_I2C_PRD_S_PH_3_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_S_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_S_PH_3_POS))

/* 0x14 : i2c_prd_stop */
#define I2C_PRD_STOP_OFFSET                                     (0x14)
#define I2C_CR_I2C_PRD_P_PH_0_POS                               (0U)
#define I2C_CR_I2C_PRD_P_PH_0_LEN                               (8U)
#define I2C_CR_I2C_PRD_P_PH_0_MSK                               (((1U<<I2C_CR_I2C_PRD_P_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_0_POS)
#define I2C_CR_I2C_PRD_P_PH_0_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_P_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_0_POS))
#define I2C_CR_I2C_PRD_P_PH_1_POS                               (8U)
#define I2C_CR_I2C_PRD_P_PH_1_LEN                               (8U)
#define I2C_CR_I2C_PRD_P_PH_1_MSK                               (((1U<<I2C_CR_I2C_PRD_P_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_1_POS)
#define I2C_CR_I2C_PRD_P_PH_1_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_P_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_1_POS))
#define I2C_CR_I2C_PRD_P_PH_2_POS                               (16U)
#define I2C_CR_I2C_PRD_P_PH_2_LEN                               (8U)
#define I2C_CR_I2C_PRD_P_PH_2_MSK                               (((1U<<I2C_CR_I2C_PRD_P_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_2_POS)
#define I2C_CR_I2C_PRD_P_PH_2_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_P_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_2_POS))
#define I2C_CR_I2C_PRD_P_PH_3_POS                               (24U)
#define I2C_CR_I2C_PRD_P_PH_3_LEN                               (8U)
#define I2C_CR_I2C_PRD_P_PH_3_MSK                               (((1U<<I2C_CR_I2C_PRD_P_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_3_POS)
#define I2C_CR_I2C_PRD_P_PH_3_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_P_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_P_PH_3_POS))

/* 0x18 : i2c_prd_data */
#define I2C_PRD_DATA_OFFSET                                     (0x18)
#define I2C_CR_I2C_PRD_D_PH_0_POS                               (0U)
#define I2C_CR_I2C_PRD_D_PH_0_LEN                               (8U)
#define I2C_CR_I2C_PRD_D_PH_0_MSK                               (((1U<<I2C_CR_I2C_PRD_D_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_0_POS)
#define I2C_CR_I2C_PRD_D_PH_0_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_D_PH_0_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_0_POS))
#define I2C_CR_I2C_PRD_D_PH_1_POS                               (8U)
#define I2C_CR_I2C_PRD_D_PH_1_LEN                               (8U)
#define I2C_CR_I2C_PRD_D_PH_1_MSK                               (((1U<<I2C_CR_I2C_PRD_D_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_1_POS)
#define I2C_CR_I2C_PRD_D_PH_1_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_D_PH_1_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_1_POS))
#define I2C_CR_I2C_PRD_D_PH_2_POS                               (16U)
#define I2C_CR_I2C_PRD_D_PH_2_LEN                               (8U)
#define I2C_CR_I2C_PRD_D_PH_2_MSK                               (((1U<<I2C_CR_I2C_PRD_D_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_2_POS)
#define I2C_CR_I2C_PRD_D_PH_2_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_D_PH_2_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_2_POS))
#define I2C_CR_I2C_PRD_D_PH_3_POS                               (24U)
#define I2C_CR_I2C_PRD_D_PH_3_LEN                               (8U)
#define I2C_CR_I2C_PRD_D_PH_3_MSK                               (((1U<<I2C_CR_I2C_PRD_D_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_3_POS)
#define I2C_CR_I2C_PRD_D_PH_3_UMSK                              (~(((1U<<I2C_CR_I2C_PRD_D_PH_3_LEN)-1)<<I2C_CR_I2C_PRD_D_PH_3_POS))

/* 0x80 : i2c_fifo_config_0 */
#define I2C_FIFO_CONFIG_0_OFFSET                                 (0x80)
#define I2C_FIFO_TX_EN_POS                                       (0U)
#define I2C_FIFO_TX_EN_LEN                                       (1U)
#define I2C_FIFO_TX_EN_MSK                                       (((1U<<I2C_FIFO_TX_EN_LEN)-1)<<I2C_FIFO_TX_EN_POS)
#define I2C_FIFO_TX_EN_UMSK                                      (~(((1U<<I2C_FIFO_TX_EN_LEN)-1)<<I2C_FIFO_TX_EN_POS))
#define I2C_FIFO_TX_EN_SET                                       (1U<<I2C_FIFO_TX_EN_POS)
#define I2C_FIFO_TX_EN_CLEAR                                     (~(((1U<<I2C_FIFO_TX_EN_LEN)-1)<<I2C_FIFO_TX_EN_POS))
#define I2C_FIFO_RX_EN_POS                                       (1U)
#define I2C_FIFO_RX_EN_LEN                                       (1U)
#define I2C_FIFO_RX_EN_MSK                                       (((1U<<I2C_FIFO_RX_EN_LEN)-1)<<I2C_FIFO_RX_EN_POS)
#define I2C_FIFO_RX_EN_UMSK                                      (~(((1U<<I2C_FIFO_RX_EN_LEN)-1)<<I2C_FIFO_RX_EN_POS))
#define I2C_FIFO_RX_EN_SET                                       (1U<<I2C_FIFO_RX_EN_POS)
#define I2C_FIFO_RX_EN_CLEAR                                     (~(((1U<<I2C_FIFO_RX_EN_LEN)-1)<<I2C_FIFO_RX_EN_POS))
#define I2C_TX_FIFO_CLR_POS                                     (2U)
#define I2C_TX_FIFO_CLR_LEN                                     (1U)
#define I2C_TX_FIFO_CLR_MSK                                     (((1U<<I2C_TX_FIFO_CLR_LEN)-1)<<I2C_TX_FIFO_CLR_POS)
#define I2C_TX_FIFO_CLR_UMSK                                    (~(((1U<<I2C_TX_FIFO_CLR_LEN)-1)<<I2C_TX_FIFO_CLR_POS))
#define I2C_TX_FIFO_CLR_SET                                     (1U<<I2C_TX_FIFO_CLR_POS)
#define I2C_TX_FIFO_CLR_CLEAR                                   (~(((1U<<I2C_TX_FIFO_CLR_LEN)-1)<<I2C_TX_FIFO_CLR_POS))
#define I2C_RX_FIFO_CLR_POS                                     (3U)
#define I2C_RX_FIFO_CLR_LEN                                     (1U)
#define I2C_RX_FIFO_CLR_MSK                                     (((1U<<I2C_RX_FIFO_CLR_LEN)-1)<<I2C_RX_FIFO_CLR_POS)
#define I2C_RX_FIFO_CLR_UMSK                                    (~(((1U<<I2C_RX_FIFO_CLR_LEN)-1)<<I2C_RX_FIFO_CLR_POS))
#define I2C_RX_FIFO_CLR_SET                                     (1U<<I2C_RX_FIFO_CLR_POS)
#define I2C_RX_FIFO_CLR_CLEAR                                   (~(((1U<<I2C_RX_FIFO_CLR_LEN)-1)<<I2C_RX_FIFO_CLR_POS))
#define I2C_TX_FIFO_OVERFLOW_POS                                (4U)
#define I2C_TX_FIFO_OVERFLOW_LEN                                (1U)
#define I2C_TX_FIFO_OVERFLOW_MSK                                (((1U<<I2C_TX_FIFO_OVERFLOW_LEN)-1)<<I2C_TX_FIFO_OVERFLOW_POS)
#define I2C_TX_FIFO_OVERFLOW_UMSK                               (~(((1U<<I2C_TX_FIFO_OVERFLOW_LEN)-1)<<I2C_TX_FIFO_OVERFLOW_POS))
#define I2C_TX_FIFO_OVERFLOW_SET                                (1U<<I2C_TX_FIFO_OVERFLOW_POS)
#define I2C_TX_FIFO_OVERFLOW_CLEAR                              (~(((1U<<I2C_TX_FIFO_OVERFLOW_LEN)-1)<<I2C_TX_FIFO_OVERFLOW_POS))
#define I2C_TX_FIFO_UNDERFLOW_POS                               (5U)
#define I2C_TX_FIFO_UNDERFLOW_LEN                               (1U)
#define I2C_TX_FIFO_UNDERFLOW_MSK                               (((1U<<I2C_TX_FIFO_UNDERFLOW_LEN)-1)<<I2C_TX_FIFO_UNDERFLOW_POS)
#define I2C_TX_FIFO_UNDERFLOW_UMSK                              (~(((1U<<I2C_TX_FIFO_UNDERFLOW_LEN)-1)<<I2C_TX_FIFO_UNDERFLOW_POS))
#define I2C_TX_FIFO_UNDERFLOW_SET                               (1U<<I2C_TX_FIFO_UNDERFLOW_POS)
#define I2C_TX_FIFO_UNDERFLOW_CLEAR                             (~(((1U<<I2C_TX_FIFO_UNDERFLOW_LEN)-1)<<I2C_TX_FIFO_UNDERFLOW_POS))
#define I2C_RX_FIFO_OVERFLOW_POS                                (6U)
#define I2C_RX_FIFO_OVERFLOW_LEN                                (1U)
#define I2C_RX_FIFO_OVERFLOW_MSK                                (((1U<<I2C_RX_FIFO_OVERFLOW_LEN)-1)<<I2C_RX_FIFO_OVERFLOW_POS)
#define I2C_RX_FIFO_OVERFLOW_UMSK                               (~(((1U<<I2C_RX_FIFO_OVERFLOW_LEN)-1)<<I2C_RX_FIFO_OVERFLOW_POS))
#define I2C_RX_FIFO_OVERFLOW_SET                                (1U<<I2C_RX_FIFO_OVERFLOW_POS)
#define I2C_RX_FIFO_OVERFLOW_CLEAR                              (~(((1U<<I2C_RX_FIFO_OVERFLOW_LEN)-1)<<I2C_RX_FIFO_OVERFLOW_POS))
#define I2C_RX_FIFO_UNDERFLOW_POS                               (7U)
#define I2C_RX_FIFO_UNDERFLOW_LEN                               (1U)
#define I2C_RX_FIFO_UNDERFLOW_MSK                               (((1U<<I2C_RX_FIFO_UNDERFLOW_LEN)-1)<<I2C_RX_FIFO_UNDERFLOW_POS)
#define I2C_RX_FIFO_UNDERFLOW_UMSK                              (~(((1U<<I2C_RX_FIFO_UNDERFLOW_LEN)-1)<<I2C_RX_FIFO_UNDERFLOW_POS))
#define I2C_RX_FIFO_UNDERFLOW_SET                               (1U<<I2C_RX_FIFO_UNDERFLOW_POS)
#define I2C_RX_FIFO_UNDERFLOW_CLEAR                             (~(((1U<<I2C_RX_FIFO_UNDERFLOW_LEN)-1)<<I2C_RX_FIFO_UNDERFLOW_POS))

/* 0x84 : i2c_fifo_config_1 */
#define I2C_FIFO_CONFIG_1_OFFSET                                 (0x84)
#define I2C_TX_FIFO_CNT_POS                                     (0U)
#define I2C_TX_FIFO_CNT_LEN                                     (5U)
#define I2C_TX_FIFO_CNT_MSK                                     (((1U<<I2C_TX_FIFO_CNT_LEN)-1)<<I2C_TX_FIFO_CNT_POS)
#define I2C_TX_FIFO_CNT_UMSK                                    (~(((1U<<I2C_TX_FIFO_CNT_LEN)-1)<<I2C_TX_FIFO_CNT_POS))
#define I2C_RX_FIFO_CNT_POS                                     (8U)
#define I2C_RX_FIFO_CNT_LEN                                     (5U)
#define I2C_RX_FIFO_CNT_MSK                                     (((1U<<I2C_RX_FIFO_CNT_LEN)-1)<<I2C_RX_FIFO_CNT_POS)
#define I2C_RX_FIFO_CNT_UMSK                                    (~(((1U<<I2C_RX_FIFO_CNT_LEN)-1)<<I2C_RX_FIFO_CNT_POS))
#define I2C_TX_FIFO_TH_POS                                      (16U)
#define I2C_TX_FIFO_TH_LEN                                      (4U)
#define I2C_TX_FIFO_TH_MSK                                      (((1U<<I2C_TX_FIFO_TH_LEN)-1)<<I2C_TX_FIFO_TH_POS)
#define I2C_TX_FIFO_TH_UMSK                                     (~(((1U<<I2C_TX_FIFO_TH_LEN)-1)<<I2C_TX_FIFO_TH_POS))
#define I2C_RX_FIFO_TH_POS                                      (24U)
#define I2C_RX_FIFO_TH_LEN                                      (4U)
#define I2C_RX_FIFO_TH_MSK                                      (((1U<<I2C_RX_FIFO_TH_LEN)-1)<<I2C_RX_FIFO_TH_POS)
#define I2C_RX_FIFO_TH_UMSK                                     (~(((1U<<I2C_RX_FIFO_TH_LEN)-1)<<I2C_RX_FIFO_TH_POS))

/* 0x88 : i2c_fifo_wdata */
#define I2C_FIFO_WDATA_OFFSET                                    (0x88)
#define I2C_FIFO_WDATA_POS                                       (0U)
#define I2C_FIFO_WDATA_LEN                                       (32U)
#define I2C_FIFO_WDATA_MSK                                       (((1U<<I2C_FIFO_WDATA_LEN)-1)<<I2C_FIFO_WDATA_POS)
#define I2C_FIFO_WDATA_UMSK                                      (~(((1U<<I2C_FIFO_WDATA_LEN)-1)<<I2C_FIFO_WDATA_POS))

/* 0x8C : i2c_fifo_rdata */
#define I2C_FIFO_RDATA_OFFSET                                    (0x8C)
#define I2C_FIFO_RDATA_POS                                       (0U)
#define I2C_FIFO_RDATA_LEN                                       (32U)
#define I2C_FIFO_RDATA_MSK                                       (((1U<<I2C_FIFO_RDATA_LEN)-1)<<I2C_FIFO_RDATA_POS)
#define I2C_FIFO_RDATA_UMSK                                      (~(((1U<<I2C_FIFO_RDATA_LEN)-1)<<I2C_FIFO_RDATA_POS))


struct  i2c_reg {
    /* 0x0 : i2c_config */
    union {
        struct {
            uint32_t cr_i2c_m_en                    :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1                     :  1; /* [    1],       rsvd,        0x0 */
            uint32_t cr_i2c_deg_en                  :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_i2c_scl_sync_en             :  1; /* [    3],        r/w,        0x1 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t cr_i2c_slv_addr                :  7; /* [14: 8],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t cr_i2c_pkt_num                 :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_19                 :  2; /* [19:18],       rsvd,        0x0 */
            uint32_t cr_i2c_pkt_dir                 :  4; /* [23:20],        r/w,        0xf */
            uint32_t reserved_24_27                 :  4; /* [27:24],       rsvd,        0x0 */
            uint32_t cr_i2c_deg_cnt                 :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_config;

    /* 0x4 : i2c_int_sts */
    union {
        struct {
            uint32_t cr_i2c_int_en                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t cr_i2c_int_mask                :  1; /* [    1],        r/w,        0x0 */
            uint32_t sts_i2c_int                    :  1; /* [    2],          r,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t sts_i2c_got_nack               :  1; /* [    4],          r,        0x0 */
            uint32_t sts_i2c_arb_lost               :  1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t cr_i2c_bus_busy_clr            :  1; /* [    8],        r/w,        0x0 */
            uint32_t sts_i2c_bus_busy               :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_int_sts;

    /* 0x8 : i2c_pkt_len_0 */
    union {
        struct {
            uint32_t cr_i2c_pkt_0_len               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t cr_i2c_pkt_1_len               : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_pkt_len_0;

    /* 0xC : i2c_pkt_len_1 */
    union {
        struct {
            uint32_t cr_i2c_pkt_2_len               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t cr_i2c_pkt_3_len               : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_pkt_len_1;

    /* 0x10 : i2c_prd_start */
    union {
        struct {
            uint32_t cr_i2c_prd_s_ph_0              :  8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_1              :  8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_2              :  8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_s_ph_3              :  8; /* [31:24],        r/w,        0xf */
        }BF;
        uint32_t WORD;
    } i2c_prd_start;

    /* 0x14 : i2c_prd_stop */
    union {
        struct {
            uint32_t cr_i2c_prd_p_ph_0              :  8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_1              :  8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_2              :  8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_p_ph_3              :  8; /* [31:24],        r/w,        0xf */
        }BF;
        uint32_t WORD;
    } i2c_prd_stop;

    /* 0x18 : i2c_prd_data */
    union {
        struct {
            uint32_t cr_i2c_prd_d_ph_0              :  8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_1              :  8; /* [15: 8],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_2              :  8; /* [23:16],        r/w,        0xf */
            uint32_t cr_i2c_prd_d_ph_3              :  8; /* [31:24],        r/w,        0xf */
        }BF;
        uint32_t WORD;
    } i2c_prd_data;

    /* 0x1c  reserved */
    uint8_t RESERVED0x1c[100];

    /* 0x80 : i2c_fifo_config_0 */
    union {
        struct {
            uint32_t i2c_fifo_tx_en                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t i2c_fifo_rx_en                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t tx_fifo_clr                    :  1; /* [    2],        r/w,        0x0 */
            uint32_t rx_fifo_clr                    :  1; /* [    3],        r/w,        0x0 */
            uint32_t tx_fifo_overflow               :  1; /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow              :  1; /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow               :  1; /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow              :  1; /* [    7],          r,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_fifo_config_0;

    /* 0x84 : i2c_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt                    :  5; /* [ 4: 0],          r,       0x10 */
            uint32_t rsvd_7_5                       :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt                    :  5; /* [12: 8],          r,        0x0 */
            uint32_t rsvd_15_13                     :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t tx_fifo_th                     :  4; /* [19:16],        r/w,        0x0 */
            uint32_t rsvd_23_20                     :  4; /* [23:20],       rsvd,        0x0 */
            uint32_t rx_fifo_th                     :  4; /* [27:24],        r/w,        0x0 */
            uint32_t rsvd_31_28                     :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_fifo_config_1;

    /* 0x88 : i2c_fifo_wdata */
    union {
        struct {
            uint32_t i2c_fifo_wdata                  : 32; /* [31: 0],          w,          x */
        }BF;
        uint32_t WORD;
    } i2c_fifo_wdata;

    /* 0x8C : i2c_fifo_rdata */
    union {
        struct {
            uint32_t i2c_fifo_rdata                  : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } i2c_fifo_rdata;

};

typedef volatile struct i2c_reg i2c_reg_t;


#endif  /* __I2C_REG_H__ */
