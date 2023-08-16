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
#ifndef  __MMSYS_MISC_REG_H__
#define  __MMSYS_MISC_REG_H__

#include "bl808.h"

/* 0x0 : a5_boot */
#define MMSYS_MISC_A5_BOOT_OFFSET                               (0x0)
#define MMSYS_MISC_REG_A5_BOOT_EN                               MMSYS_MISC_REG_A5_BOOT_EN
#define MMSYS_MISC_REG_A5_BOOT_EN_POS                           (0U)
#define MMSYS_MISC_REG_A5_BOOT_EN_LEN                           (1U)
#define MMSYS_MISC_REG_A5_BOOT_EN_MSK                           (((1U<<MMSYS_MISC_REG_A5_BOOT_EN_LEN)-1)<<MMSYS_MISC_REG_A5_BOOT_EN_POS)
#define MMSYS_MISC_REG_A5_BOOT_EN_UMSK                          (~(((1U<<MMSYS_MISC_REG_A5_BOOT_EN_LEN)-1)<<MMSYS_MISC_REG_A5_BOOT_EN_POS))
#define MMSYS_MISC_REG_A5_BOOT_ADDR                             MMSYS_MISC_REG_A5_BOOT_ADDR
#define MMSYS_MISC_REG_A5_BOOT_ADDR_POS                         (1U)
#define MMSYS_MISC_REG_A5_BOOT_ADDR_LEN                         (31U)
#define MMSYS_MISC_REG_A5_BOOT_ADDR_MSK                         (((1U<<MMSYS_MISC_REG_A5_BOOT_ADDR_LEN)-1)<<MMSYS_MISC_REG_A5_BOOT_ADDR_POS)
#define MMSYS_MISC_REG_A5_BOOT_ADDR_UMSK                        (~(((1U<<MMSYS_MISC_REG_A5_BOOT_ADDR_LEN)-1)<<MMSYS_MISC_REG_A5_BOOT_ADDR_POS))

/* 0x20 : peri_apb_ctrl */
#define MMSYS_MISC_PERI_APB_CTRL_OFFSET                         (0x20)
#define MMSYS_MISC_RG_PCLK_FORCE_ON                             MMSYS_MISC_RG_PCLK_FORCE_ON
#define MMSYS_MISC_RG_PCLK_FORCE_ON_POS                         (0U)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_LEN                         (16U)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_MSK                         (((1U<<MMSYS_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MMSYS_MISC_RG_PCLK_FORCE_ON_POS)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_UMSK                        (~(((1U<<MMSYS_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MMSYS_MISC_RG_PCLK_FORCE_ON_POS))

/* 0x2C : mm_infra_qos_ctrl */
#define MMSYS_MISC_MM_INFRA_QOS_CTRL_OFFSET                     (0x2C)
#define MMSYS_MISC_REG_DMA_AWQOS                                MMSYS_MISC_REG_DMA_AWQOS
#define MMSYS_MISC_REG_DMA_AWQOS_POS                            (0U)
#define MMSYS_MISC_REG_DMA_AWQOS_LEN                            (1U)
#define MMSYS_MISC_REG_DMA_AWQOS_MSK                            (((1U<<MMSYS_MISC_REG_DMA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_DMA_AWQOS_POS)
#define MMSYS_MISC_REG_DMA_AWQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_DMA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_DMA_AWQOS_POS))
#define MMSYS_MISC_REG_DMA_ARQOS                                MMSYS_MISC_REG_DMA_ARQOS
#define MMSYS_MISC_REG_DMA_ARQOS_POS                            (1U)
#define MMSYS_MISC_REG_DMA_ARQOS_LEN                            (1U)
#define MMSYS_MISC_REG_DMA_ARQOS_MSK                            (((1U<<MMSYS_MISC_REG_DMA_ARQOS_LEN)-1)<<MMSYS_MISC_REG_DMA_ARQOS_POS)
#define MMSYS_MISC_REG_DMA_ARQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_DMA_ARQOS_LEN)-1)<<MMSYS_MISC_REG_DMA_ARQOS_POS))
#define MMSYS_MISC_REG_A5M0_AWQOS                               MMSYS_MISC_REG_A5M0_AWQOS
#define MMSYS_MISC_REG_A5M0_AWQOS_POS                           (2U)
#define MMSYS_MISC_REG_A5M0_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_A5M0_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_A5M0_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A5M0_AWQOS_POS)
#define MMSYS_MISC_REG_A5M0_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_A5M0_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A5M0_AWQOS_POS))
#define MMSYS_MISC_REG_A5M0_ARQOS                               MMSYS_MISC_REG_A5M0_ARQOS
#define MMSYS_MISC_REG_A5M0_ARQOS_POS                           (3U)
#define MMSYS_MISC_REG_A5M0_ARQOS_LEN                           (1U)
#define MMSYS_MISC_REG_A5M0_ARQOS_MSK                           (((1U<<MMSYS_MISC_REG_A5M0_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A5M0_ARQOS_POS)
#define MMSYS_MISC_REG_A5M0_ARQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_A5M0_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A5M0_ARQOS_POS))
#define MMSYS_MISC_REG_A5M1_AWQOS                               MMSYS_MISC_REG_A5M1_AWQOS
#define MMSYS_MISC_REG_A5M1_AWQOS_POS                           (4U)
#define MMSYS_MISC_REG_A5M1_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_A5M1_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_A5M1_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A5M1_AWQOS_POS)
#define MMSYS_MISC_REG_A5M1_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_A5M1_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A5M1_AWQOS_POS))
#define MMSYS_MISC_REG_A5M1_ARQOS                               MMSYS_MISC_REG_A5M1_ARQOS
#define MMSYS_MISC_REG_A5M1_ARQOS_POS                           (5U)
#define MMSYS_MISC_REG_A5M1_ARQOS_LEN                           (1U)
#define MMSYS_MISC_REG_A5M1_ARQOS_MSK                           (((1U<<MMSYS_MISC_REG_A5M1_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A5M1_ARQOS_POS)
#define MMSYS_MISC_REG_A5M1_ARQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_A5M1_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A5M1_ARQOS_POS))
#define MMSYS_MISC_REG_2DDMA_AWQOS                              MMSYS_MISC_REG_2DDMA_AWQOS
#define MMSYS_MISC_REG_2DDMA_AWQOS_POS                          (6U)
#define MMSYS_MISC_REG_2DDMA_AWQOS_LEN                          (1U)
#define MMSYS_MISC_REG_2DDMA_AWQOS_MSK                          (((1U<<MMSYS_MISC_REG_2DDMA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_2DDMA_AWQOS_POS)
#define MMSYS_MISC_REG_2DDMA_AWQOS_UMSK                         (~(((1U<<MMSYS_MISC_REG_2DDMA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_2DDMA_AWQOS_POS))
#define MMSYS_MISC_REG_2DDMA_ARQOS                              MMSYS_MISC_REG_2DDMA_ARQOS
#define MMSYS_MISC_REG_2DDMA_ARQOS_POS                          (7U)
#define MMSYS_MISC_REG_2DDMA_ARQOS_LEN                          (1U)
#define MMSYS_MISC_REG_2DDMA_ARQOS_MSK                          (((1U<<MMSYS_MISC_REG_2DDMA_ARQOS_LEN)-1)<<MMSYS_MISC_REG_2DDMA_ARQOS_POS)
#define MMSYS_MISC_REG_2DDMA_ARQOS_UMSK                         (~(((1U<<MMSYS_MISC_REG_2DDMA_ARQOS_LEN)-1)<<MMSYS_MISC_REG_2DDMA_ARQOS_POS))
#define MMSYS_MISC_REG_SDH_AWQOS                                MMSYS_MISC_REG_SDH_AWQOS
#define MMSYS_MISC_REG_SDH_AWQOS_POS                            (8U)
#define MMSYS_MISC_REG_SDH_AWQOS_LEN                            (1U)
#define MMSYS_MISC_REG_SDH_AWQOS_MSK                            (((1U<<MMSYS_MISC_REG_SDH_AWQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_AWQOS_POS)
#define MMSYS_MISC_REG_SDH_AWQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_SDH_AWQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_AWQOS_POS))
#define MMSYS_MISC_REG_SDH_ARQOS                                MMSYS_MISC_REG_SDH_ARQOS
#define MMSYS_MISC_REG_SDH_ARQOS_POS                            (9U)
#define MMSYS_MISC_REG_SDH_ARQOS_LEN                            (1U)
#define MMSYS_MISC_REG_SDH_ARQOS_MSK                            (((1U<<MMSYS_MISC_REG_SDH_ARQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_ARQOS_POS)
#define MMSYS_MISC_REG_SDH_ARQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_SDH_ARQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_ARQOS_POS))
#define MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN                     MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN
#define MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_POS                 (16U)
#define MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_LEN                 (3U)
#define MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_MSK                 (((1U<<MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_LEN)-1)<<MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_POS)
#define MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_UMSK                (~(((1U<<MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_LEN)-1)<<MMSYS_MISC_REG_W_ISSUE_THRE_MM2CONN_POS))
#define MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM                     MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM
#define MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_POS                 (20U)
#define MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_LEN                 (3U)
#define MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_MSK                 (((1U<<MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_LEN)-1)<<MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_POS)
#define MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_UMSK                (~(((1U<<MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_LEN)-1)<<MMSYS_MISC_REG_W_ISSUE_THRE_CONN2MM_POS))

/* 0x30 : mm_bus_dec_err */
#define MMSYS_MISC_MM_BUS_DEC_ERR_OFFSET                        (0x30)
#define MMSYS_MISC_REG_DEC_ERR_CLR                              MMSYS_MISC_REG_DEC_ERR_CLR
#define MMSYS_MISC_REG_DEC_ERR_CLR_POS                          (0U)
#define MMSYS_MISC_REG_DEC_ERR_CLR_LEN                          (1U)
#define MMSYS_MISC_REG_DEC_ERR_CLR_MSK                          (((1U<<MMSYS_MISC_REG_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_CLR_POS)
#define MMSYS_MISC_REG_DEC_ERR_CLR_UMSK                         (~(((1U<<MMSYS_MISC_REG_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_CLR_POS))
#define MMSYS_MISC_REG_DEC_ERR_LATCH_LAST                       MMSYS_MISC_REG_DEC_ERR_LATCH_LAST
#define MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_POS                   (1U)
#define MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_LEN                   (1U)
#define MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_MSK                   (((1U<<MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_POS)
#define MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_UMSK                  (~(((1U<<MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_LATCH_LAST_POS))
#define MMSYS_MISC_MMINFRA_DEC_ERR_LAT                          MMSYS_MISC_MMINFRA_DEC_ERR_LAT
#define MMSYS_MISC_MMINFRA_DEC_ERR_LAT_POS                      (8U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_LAT_LEN                      (1U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_LAT_MSK                      (((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_LAT_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_LAT_POS)
#define MMSYS_MISC_MMINFRA_DEC_ERR_LAT_UMSK                     (~(((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_LAT_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_LAT_POS))
#define MMSYS_MISC_MMINFRA_DEC_ERR_WRITE                        MMSYS_MISC_MMINFRA_DEC_ERR_WRITE
#define MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_POS                    (9U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_LEN                    (1U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_MSK                    (((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_POS)
#define MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_UMSK                   (~(((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_WRITE_POS))
#define MMSYS_MISC_MMINFRA_DEC_ERR_SRC                          MMSYS_MISC_MMINFRA_DEC_ERR_SRC
#define MMSYS_MISC_MMINFRA_DEC_ERR_SRC_POS                      (12U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_SRC_LEN                      (2U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_SRC_MSK                      (((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_SRC_POS)
#define MMSYS_MISC_MMINFRA_DEC_ERR_SRC_UMSK                     (~(((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_SRC_POS))
#define MMSYS_MISC_MMINFRA_DEC_ERR_ID                           MMSYS_MISC_MMINFRA_DEC_ERR_ID
#define MMSYS_MISC_MMINFRA_DEC_ERR_ID_POS                       (16U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ID_LEN                       (8U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ID_MSK                       (((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_ID_POS)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ID_UMSK                      (~(((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_ID_POS))

/* 0x34 : mm_bus_dec_err_addr */
#define MMSYS_MISC_MM_BUS_DEC_ERR_ADDR_OFFSET                   (0x34)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ADDR                         MMSYS_MISC_MMINFRA_DEC_ERR_ADDR
#define MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_POS                     (0U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_LEN                     (32U)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_MSK                     (((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_POS)
#define MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_UMSK                    (~(((1U<<MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MMINFRA_DEC_ERR_ADDR_POS))

/* 0x38 : mcu_bus_dec_err */
#define MMSYS_MISC_MCU_BUS_DEC_ERR_OFFSET                       (0x38)
#define MMSYS_MISC_REG_DEC_ERR_CLR_MCU                          MMSYS_MISC_REG_DEC_ERR_CLR_MCU
#define MMSYS_MISC_REG_DEC_ERR_CLR_MCU_POS                      (0U)
#define MMSYS_MISC_REG_DEC_ERR_CLR_MCU_LEN                      (1U)
#define MMSYS_MISC_REG_DEC_ERR_CLR_MCU_MSK                      (((1U<<MMSYS_MISC_REG_DEC_ERR_CLR_MCU_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_CLR_MCU_POS)
#define MMSYS_MISC_REG_DEC_ERR_CLR_MCU_UMSK                     (~(((1U<<MMSYS_MISC_REG_DEC_ERR_CLR_MCU_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_CLR_MCU_POS))
#define MMSYS_MISC_REG_DEC_ERR_LAST_MCU                         MMSYS_MISC_REG_DEC_ERR_LAST_MCU
#define MMSYS_MISC_REG_DEC_ERR_LAST_MCU_POS                     (1U)
#define MMSYS_MISC_REG_DEC_ERR_LAST_MCU_LEN                     (1U)
#define MMSYS_MISC_REG_DEC_ERR_LAST_MCU_MSK                     (((1U<<MMSYS_MISC_REG_DEC_ERR_LAST_MCU_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_LAST_MCU_POS)
#define MMSYS_MISC_REG_DEC_ERR_LAST_MCU_UMSK                    (~(((1U<<MMSYS_MISC_REG_DEC_ERR_LAST_MCU_LEN)-1)<<MMSYS_MISC_REG_DEC_ERR_LAST_MCU_POS))
#define MMSYS_MISC_MCU_DEC_ERR_LAT                              MMSYS_MISC_MCU_DEC_ERR_LAT
#define MMSYS_MISC_MCU_DEC_ERR_LAT_POS                          (8U)
#define MMSYS_MISC_MCU_DEC_ERR_LAT_LEN                          (1U)
#define MMSYS_MISC_MCU_DEC_ERR_LAT_MSK                          (((1U<<MMSYS_MISC_MCU_DEC_ERR_LAT_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_LAT_POS)
#define MMSYS_MISC_MCU_DEC_ERR_LAT_UMSK                         (~(((1U<<MMSYS_MISC_MCU_DEC_ERR_LAT_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_LAT_POS))
#define MMSYS_MISC_MCU_DEC_ERR_WRITE                            MMSYS_MISC_MCU_DEC_ERR_WRITE
#define MMSYS_MISC_MCU_DEC_ERR_WRITE_POS                        (9U)
#define MMSYS_MISC_MCU_DEC_ERR_WRITE_LEN                        (1U)
#define MMSYS_MISC_MCU_DEC_ERR_WRITE_MSK                        (((1U<<MMSYS_MISC_MCU_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_WRITE_POS)
#define MMSYS_MISC_MCU_DEC_ERR_WRITE_UMSK                       (~(((1U<<MMSYS_MISC_MCU_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_WRITE_POS))
#define MMSYS_MISC_MCU_DEC_ERR_SRC                              MMSYS_MISC_MCU_DEC_ERR_SRC
#define MMSYS_MISC_MCU_DEC_ERR_SRC_POS                          (12U)
#define MMSYS_MISC_MCU_DEC_ERR_SRC_LEN                          (1U)
#define MMSYS_MISC_MCU_DEC_ERR_SRC_MSK                          (((1U<<MMSYS_MISC_MCU_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_SRC_POS)
#define MMSYS_MISC_MCU_DEC_ERR_SRC_UMSK                         (~(((1U<<MMSYS_MISC_MCU_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_SRC_POS))
#define MMSYS_MISC_MCU_DEC_ERR_ID                               MMSYS_MISC_MCU_DEC_ERR_ID
#define MMSYS_MISC_MCU_DEC_ERR_ID_POS                           (16U)
#define MMSYS_MISC_MCU_DEC_ERR_ID_LEN                           (5U)
#define MMSYS_MISC_MCU_DEC_ERR_ID_MSK                           (((1U<<MMSYS_MISC_MCU_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_ID_POS)
#define MMSYS_MISC_MCU_DEC_ERR_ID_UMSK                          (~(((1U<<MMSYS_MISC_MCU_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_ID_POS))

/* 0x3C : mcu_bus_dec_err_addr */
#define MMSYS_MISC_MCU_BUS_DEC_ERR_ADDR_OFFSET                  (0x3C)
#define MMSYS_MISC_MCU_DEC_ERR_ADDR                             MMSYS_MISC_MCU_DEC_ERR_ADDR
#define MMSYS_MISC_MCU_DEC_ERR_ADDR_POS                         (0U)
#define MMSYS_MISC_MCU_DEC_ERR_ADDR_LEN                         (32U)
#define MMSYS_MISC_MCU_DEC_ERR_ADDR_MSK                         (((1U<<MMSYS_MISC_MCU_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_ADDR_POS)
#define MMSYS_MISC_MCU_DEC_ERR_ADDR_UMSK                        (~(((1U<<MMSYS_MISC_MCU_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MCU_DEC_ERR_ADDR_POS))

/* 0x40 : dma_clk_ctrl */
#define MMSYS_MISC_DMA_CLK_CTRL_OFFSET                          (0x40)
#define MMSYS_MISC_DMA_CLK_EN                                   MMSYS_MISC_DMA_CLK_EN
#define MMSYS_MISC_DMA_CLK_EN_POS                               (0U)
#define MMSYS_MISC_DMA_CLK_EN_LEN                               (8U)
#define MMSYS_MISC_DMA_CLK_EN_MSK                               (((1U<<MMSYS_MISC_DMA_CLK_EN_LEN)-1)<<MMSYS_MISC_DMA_CLK_EN_POS)
#define MMSYS_MISC_DMA_CLK_EN_UMSK                              (~(((1U<<MMSYS_MISC_DMA_CLK_EN_LEN)-1)<<MMSYS_MISC_DMA_CLK_EN_POS))

/* 0x50 : vram_ctrl */
#define MMSYS_MISC_VRAM_CTRL_OFFSET                             (0x50)
#define MMSYS_MISC_REG_SYSRAM_SET                               MMSYS_MISC_REG_SYSRAM_SET
#define MMSYS_MISC_REG_SYSRAM_SET_POS                           (0U)
#define MMSYS_MISC_REG_SYSRAM_SET_LEN                           (1U)
#define MMSYS_MISC_REG_SYSRAM_SET_MSK                           (((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS)
#define MMSYS_MISC_REG_SYSRAM_SET_UMSK                          (~(((1U<<MMSYS_MISC_REG_SYSRAM_SET_LEN)-1)<<MMSYS_MISC_REG_SYSRAM_SET_POS))
#define MMSYS_MISC_REG_PF_SRAM_REL                              MMSYS_MISC_REG_PF_SRAM_REL
#define MMSYS_MISC_REG_PF_SRAM_REL_POS                          (1U)
#define MMSYS_MISC_REG_PF_SRAM_REL_LEN                          (2U)
#define MMSYS_MISC_REG_PF_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS)
#define MMSYS_MISC_REG_PF_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_PF_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_PF_SRAM_REL_POS))
#define MMSYS_MISC_REG_L2_SRAM_REL                              MMSYS_MISC_REG_L2_SRAM_REL
#define MMSYS_MISC_REG_L2_SRAM_REL_POS                          (4U)
#define MMSYS_MISC_REG_L2_SRAM_REL_LEN                          (1U)
#define MMSYS_MISC_REG_L2_SRAM_REL_MSK                          (((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS)
#define MMSYS_MISC_REG_L2_SRAM_REL_UMSK                         (~(((1U<<MMSYS_MISC_REG_L2_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_L2_SRAM_REL_POS))
#define MMSYS_MISC_REG_ISP_SRAM_REL                             MMSYS_MISC_REG_ISP_SRAM_REL
#define MMSYS_MISC_REG_ISP_SRAM_REL_POS                         (6U)
#define MMSYS_MISC_REG_ISP_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_ISP_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_ISP_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_ISP_SRAM_REL_POS)
#define MMSYS_MISC_REG_ISP_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_ISP_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_ISP_SRAM_REL_POS))
#define MMSYS_MISC_REG_APU_SRAM_REL                             MMSYS_MISC_REG_APU_SRAM_REL
#define MMSYS_MISC_REG_APU_SRAM_REL_POS                         (7U)
#define MMSYS_MISC_REG_APU_SRAM_REL_LEN                         (1U)
#define MMSYS_MISC_REG_APU_SRAM_REL_MSK                         (((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS)
#define MMSYS_MISC_REG_APU_SRAM_REL_UMSK                        (~(((1U<<MMSYS_MISC_REG_APU_SRAM_REL_LEN)-1)<<MMSYS_MISC_REG_APU_SRAM_REL_POS))

/* 0x60 : l1c_config */
#define MMSYS_MISC_L1C_CONFIG_OFFSET                            (0x60)
#define MMSYS_MISC_L1C_CACHEABLE                                MMSYS_MISC_L1C_CACHEABLE
#define MMSYS_MISC_L1C_CACHEABLE_POS                            (0U)
#define MMSYS_MISC_L1C_CACHEABLE_LEN                            (1U)
#define MMSYS_MISC_L1C_CACHEABLE_MSK                            (((1U<<MMSYS_MISC_L1C_CACHEABLE_LEN)-1)<<MMSYS_MISC_L1C_CACHEABLE_POS)
#define MMSYS_MISC_L1C_CACHEABLE_UMSK                           (~(((1U<<MMSYS_MISC_L1C_CACHEABLE_LEN)-1)<<MMSYS_MISC_L1C_CACHEABLE_POS))
#define MMSYS_MISC_L1C_CNT_EN                                   MMSYS_MISC_L1C_CNT_EN
#define MMSYS_MISC_L1C_CNT_EN_POS                               (1U)
#define MMSYS_MISC_L1C_CNT_EN_LEN                               (1U)
#define MMSYS_MISC_L1C_CNT_EN_MSK                               (((1U<<MMSYS_MISC_L1C_CNT_EN_LEN)-1)<<MMSYS_MISC_L1C_CNT_EN_POS)
#define MMSYS_MISC_L1C_CNT_EN_UMSK                              (~(((1U<<MMSYS_MISC_L1C_CNT_EN_LEN)-1)<<MMSYS_MISC_L1C_CNT_EN_POS))
#define MMSYS_MISC_L1C_INVALID                                  MMSYS_MISC_L1C_INVALID
#define MMSYS_MISC_L1C_INVALID_POS                              (2U)
#define MMSYS_MISC_L1C_INVALID_LEN                              (1U)
#define MMSYS_MISC_L1C_INVALID_MSK                              (((1U<<MMSYS_MISC_L1C_INVALID_LEN)-1)<<MMSYS_MISC_L1C_INVALID_POS)
#define MMSYS_MISC_L1C_INVALID_UMSK                             (~(((1U<<MMSYS_MISC_L1C_INVALID_LEN)-1)<<MMSYS_MISC_L1C_INVALID_POS))
#define MMSYS_MISC_L1C_INVALID_DONE                             MMSYS_MISC_L1C_INVALID_DONE
#define MMSYS_MISC_L1C_INVALID_DONE_POS                         (3U)
#define MMSYS_MISC_L1C_INVALID_DONE_LEN                         (1U)
#define MMSYS_MISC_L1C_INVALID_DONE_MSK                         (((1U<<MMSYS_MISC_L1C_INVALID_DONE_LEN)-1)<<MMSYS_MISC_L1C_INVALID_DONE_POS)
#define MMSYS_MISC_L1C_INVALID_DONE_UMSK                        (~(((1U<<MMSYS_MISC_L1C_INVALID_DONE_LEN)-1)<<MMSYS_MISC_L1C_INVALID_DONE_POS))
#define MMSYS_MISC_L1C_WAY_DIS                                  MMSYS_MISC_L1C_WAY_DIS
#define MMSYS_MISC_L1C_WAY_DIS_POS                              (8U)
#define MMSYS_MISC_L1C_WAY_DIS_LEN                              (4U)
#define MMSYS_MISC_L1C_WAY_DIS_MSK                              (((1U<<MMSYS_MISC_L1C_WAY_DIS_LEN)-1)<<MMSYS_MISC_L1C_WAY_DIS_POS)
#define MMSYS_MISC_L1C_WAY_DIS_UMSK                             (~(((1U<<MMSYS_MISC_L1C_WAY_DIS_LEN)-1)<<MMSYS_MISC_L1C_WAY_DIS_POS))
#define MMSYS_MISC_L1C_AUX_EN                                   MMSYS_MISC_L1C_AUX_EN
#define MMSYS_MISC_L1C_AUX_EN_POS                               (13U)
#define MMSYS_MISC_L1C_AUX_EN_LEN                               (1U)
#define MMSYS_MISC_L1C_AUX_EN_MSK                               (((1U<<MMSYS_MISC_L1C_AUX_EN_LEN)-1)<<MMSYS_MISC_L1C_AUX_EN_POS)
#define MMSYS_MISC_L1C_AUX_EN_UMSK                              (~(((1U<<MMSYS_MISC_L1C_AUX_EN_LEN)-1)<<MMSYS_MISC_L1C_AUX_EN_POS))
#define MMSYS_MISC_L1C_BYPASS                                   MMSYS_MISC_L1C_BYPASS
#define MMSYS_MISC_L1C_BYPASS_POS                               (14U)
#define MMSYS_MISC_L1C_BYPASS_LEN                               (1U)
#define MMSYS_MISC_L1C_BYPASS_MSK                               (((1U<<MMSYS_MISC_L1C_BYPASS_LEN)-1)<<MMSYS_MISC_L1C_BYPASS_POS)
#define MMSYS_MISC_L1C_BYPASS_UMSK                              (~(((1U<<MMSYS_MISC_L1C_BYPASS_LEN)-1)<<MMSYS_MISC_L1C_BYPASS_POS))
#define MMSYS_MISC_L1C_EARLY_RESP_DIS                           MMSYS_MISC_L1C_EARLY_RESP_DIS
#define MMSYS_MISC_L1C_EARLY_RESP_DIS_POS                       (15U)
#define MMSYS_MISC_L1C_EARLY_RESP_DIS_LEN                       (1U)
#define MMSYS_MISC_L1C_EARLY_RESP_DIS_MSK                       (((1U<<MMSYS_MISC_L1C_EARLY_RESP_DIS_LEN)-1)<<MMSYS_MISC_L1C_EARLY_RESP_DIS_POS)
#define MMSYS_MISC_L1C_EARLY_RESP_DIS_UMSK                      (~(((1U<<MMSYS_MISC_L1C_EARLY_RESP_DIS_LEN)-1)<<MMSYS_MISC_L1C_EARLY_RESP_DIS_POS))
#define MMSYS_MISC_L1C_RANGE                                    MMSYS_MISC_L1C_RANGE
#define MMSYS_MISC_L1C_RANGE_POS                                (16U)
#define MMSYS_MISC_L1C_RANGE_LEN                                (8U)
#define MMSYS_MISC_L1C_RANGE_MSK                                (((1U<<MMSYS_MISC_L1C_RANGE_LEN)-1)<<MMSYS_MISC_L1C_RANGE_POS)
#define MMSYS_MISC_L1C_RANGE_UMSK                               (~(((1U<<MMSYS_MISC_L1C_RANGE_LEN)-1)<<MMSYS_MISC_L1C_RANGE_POS))

/* 0x64 : l1c_hit_cnt_lsb */
#define MMSYS_MISC_L1C_HIT_CNT_LSB_OFFSET                       (0x64)
#define MMSYS_MISC_L1C_HIT_CNT_LSB                              MMSYS_MISC_L1C_HIT_CNT_LSB
#define MMSYS_MISC_L1C_HIT_CNT_LSB_POS                          (0U)
#define MMSYS_MISC_L1C_HIT_CNT_LSB_LEN                          (32U)
#define MMSYS_MISC_L1C_HIT_CNT_LSB_MSK                          (((1U<<MMSYS_MISC_L1C_HIT_CNT_LSB_LEN)-1)<<MMSYS_MISC_L1C_HIT_CNT_LSB_POS)
#define MMSYS_MISC_L1C_HIT_CNT_LSB_UMSK                         (~(((1U<<MMSYS_MISC_L1C_HIT_CNT_LSB_LEN)-1)<<MMSYS_MISC_L1C_HIT_CNT_LSB_POS))

/* 0x68 : l1c_hit_cnt_msb */
#define MMSYS_MISC_L1C_HIT_CNT_MSB_OFFSET                       (0x68)
#define MMSYS_MISC_L1C_HIT_CNT_MSB                              MMSYS_MISC_L1C_HIT_CNT_MSB
#define MMSYS_MISC_L1C_HIT_CNT_MSB_POS                          (0U)
#define MMSYS_MISC_L1C_HIT_CNT_MSB_LEN                          (32U)
#define MMSYS_MISC_L1C_HIT_CNT_MSB_MSK                          (((1U<<MMSYS_MISC_L1C_HIT_CNT_MSB_LEN)-1)<<MMSYS_MISC_L1C_HIT_CNT_MSB_POS)
#define MMSYS_MISC_L1C_HIT_CNT_MSB_UMSK                         (~(((1U<<MMSYS_MISC_L1C_HIT_CNT_MSB_LEN)-1)<<MMSYS_MISC_L1C_HIT_CNT_MSB_POS))

/* 0x6C : l1c_miss_cnt */
#define MMSYS_MISC_L1C_MISS_CNT_OFFSET                          (0x6C)
#define MMSYS_MISC_L1C_MISS_CNT                                 MMSYS_MISC_L1C_MISS_CNT
#define MMSYS_MISC_L1C_MISS_CNT_POS                             (0U)
#define MMSYS_MISC_L1C_MISS_CNT_LEN                             (32U)
#define MMSYS_MISC_L1C_MISS_CNT_MSK                             (((1U<<MMSYS_MISC_L1C_MISS_CNT_LEN)-1)<<MMSYS_MISC_L1C_MISS_CNT_POS)
#define MMSYS_MISC_L1C_MISS_CNT_UMSK                            (~(((1U<<MMSYS_MISC_L1C_MISS_CNT_LEN)-1)<<MMSYS_MISC_L1C_MISS_CNT_POS))

/* 0xFC : mmsys_misc_dummy */
#define MMSYS_MISC_DUMMY_OFFSET                                 (0xFC)
#define MMSYS_MISC_DUMMY_REG                                    MMSYS_MISC_DUMMY_REG
#define MMSYS_MISC_DUMMY_REG_POS                                (0U)
#define MMSYS_MISC_DUMMY_REG_LEN                                (32U)
#define MMSYS_MISC_DUMMY_REG_MSK                                (((1U<<MMSYS_MISC_DUMMY_REG_LEN)-1)<<MMSYS_MISC_DUMMY_REG_POS)
#define MMSYS_MISC_DUMMY_REG_UMSK                               (~(((1U<<MMSYS_MISC_DUMMY_REG_LEN)-1)<<MMSYS_MISC_DUMMY_REG_POS))

/* 0x100 : DDR_debug */
#define MMSYS_MISC_DDR_DEBUG_OFFSET                             (0x100)
#define MMSYS_MISC_DDR_CALIB_DONE                               MMSYS_MISC_DDR_CALIB_DONE
#define MMSYS_MISC_DDR_CALIB_DONE_POS                           (0U)
#define MMSYS_MISC_DDR_CALIB_DONE_LEN                           (1U)
#define MMSYS_MISC_DDR_CALIB_DONE_MSK                           (((1U<<MMSYS_MISC_DDR_CALIB_DONE_LEN)-1)<<MMSYS_MISC_DDR_CALIB_DONE_POS)
#define MMSYS_MISC_DDR_CALIB_DONE_UMSK                          (~(((1U<<MMSYS_MISC_DDR_CALIB_DONE_LEN)-1)<<MMSYS_MISC_DDR_CALIB_DONE_POS))


struct  mmsys_misc_reg {
    /* 0x0 : a5_boot */
    union {
        struct {
            uint32_t reg_a5_boot_en                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_a5_boot_addr               : 31; /* [31: 1],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } a5_boot;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[28];

    /* 0x20 : peri_apb_ctrl */
    union {
        struct {
            uint32_t rg_pclk_force_on               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } peri_apb_ctrl;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[8];

    /* 0x2C : mm_infra_qos_ctrl */
    union {
        struct {
            uint32_t reg_dma_awqos                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_dma_arqos                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_a5m0_awqos                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_a5m0_arqos                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_a5m1_awqos                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_a5m1_arqos                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_2ddma_awqos                :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_2ddma_arqos                :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_sdh_awqos                  :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_sdh_arqos                  :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t reg_w_issue_thre_mm2conn       :  3; /* [18:16],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t reg_w_issue_thre_conn2mm       :  3; /* [22:20],        r/w,        0x0 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_qos_ctrl;

    /* 0x30 : mm_bus_dec_err */
    union {
        struct {
            uint32_t reg_dec_err_clr                :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_dec_err_latch_last         :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_lat            :  1; /* [    8],          r,        0x0 */
            uint32_t mminfra_dec_err_write          :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_src            :  2; /* [13:12],          r,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_id             :  8; /* [23:16],          r,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_bus_dec_err;

    /* 0x34 : mm_bus_dec_err_addr */
    union {
        struct {
            uint32_t mminfra_dec_err_addr           : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_bus_dec_err_addr;

    /* 0x38 : mcu_bus_dec_err */
    union {
        struct {
            uint32_t reg_dec_err_clr_mcu            :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_dec_err_last_mcu           :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t mcu_dec_err_lat                :  1; /* [    8],          r,        0x0 */
            uint32_t mcu_dec_err_write              :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t mcu_dec_err_src                :  1; /* [   12],          r,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t mcu_dec_err_id                 :  5; /* [20:16],          r,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu_bus_dec_err;

    /* 0x3C : mcu_bus_dec_err_addr */
    union {
        struct {
            uint32_t mcu_dec_err_addr               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu_bus_dec_err_addr;

    /* 0x40 : dma_clk_ctrl */
    union {
        struct {
            uint32_t dma_clk_en                     :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dma_clk_ctrl;

    /* 0x44  reserved */
    uint8_t RESERVED0x44[12];

    /* 0x50 : vram_ctrl */
    union {
        struct {
            uint32_t reg_sysram_set                 :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_l2_sram_rel                :  3; /* [ 3: 1],        r/w,        0x3 */
            uint32_t reg_pf_sram_rel                :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t reg_apu_sram_rel               :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_isp_sram_rel               :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_31                  : 23; /* [31: 9],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } vram_ctrl;

    /* 0x54  reserved */
    uint8_t RESERVED0x54[12];

    /* 0x60 : l1c_config */
    union {
        struct {
            uint32_t l1c_cacheable                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t l1c_cnt_en                     :  1; /* [    1],        r/w,        0x0 */
            uint32_t l1c_invalid                    :  1; /* [    2],        r/w,        0x0 */
            uint32_t l1c_invalid_done               :  1; /* [    3],          r,        0x0 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t l1c_way_dis                    :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12                    :  1; /* [   12],       rsvd,        0x0 */
            uint32_t l1c_aux_en                     :  1; /* [   13],        r/w,        0x1 */
            uint32_t l1c_bypass                     :  1; /* [   14],        r/w,        0x1 */
            uint32_t l1c_early_resp_dis             :  1; /* [   15],        r/w,        0x0 */
            uint32_t l1c_range                      :  8; /* [23:16],        r/w,       0x20 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_config;

    /* 0x64 : l1c_hit_cnt_lsb */
    union {
        struct {
            uint32_t l1c_hit_cnt_lsb                : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_hit_cnt_lsb;

    /* 0x68 : l1c_hit_cnt_msb */
    union {
        struct {
            uint32_t l1c_hit_cnt_msb                : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_hit_cnt_msb;

    /* 0x6C : l1c_miss_cnt */
    union {
        struct {
            uint32_t l1c_miss_cnt                   : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_miss_cnt;

    /* 0x70  reserved */
    uint8_t RESERVED0x70[140];

    /* 0xFC : mmsys_misc_dummy */
    union {
        struct {
            uint32_t dummy_reg                      : 32; /* [31: 0],        r/w, 0xffff0000 */
        }BF;
        uint32_t WORD;
    } mmsys_misc_dummy;

    /* 0x100 : DDR_debug */
    union {
        struct {
            uint32_t ddr_calib_done                 :  1; /* [    0],          r,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } DDR_debug;

};

typedef volatile struct mmsys_misc_reg mmsys_misc_reg_t;

#define MMSYS_MISC_GPIO_OFFSET              0x200
#define MMSYS_MISC_GPIO_INPUT_OFFSET        0x2A0
#define MMSYS_MISC_GPIO_OUTPUT_OFFSET       0x2B0
#define MMSYS_MISC_GPIO_OUTPUT_EN_OFFSET    0x2C0

#endif  /* __MMSYS_MISC_REG_H__ */
