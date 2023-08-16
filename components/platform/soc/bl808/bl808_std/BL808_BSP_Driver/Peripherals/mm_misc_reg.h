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
#ifndef  __MM_MISC_REG_H__
#define  __MM_MISC_REG_H__

#include "bl808.h"

/* 0x0 : CPU0_Boot */
#define MM_MISC_CPU0_BOOT_OFFSET                                (0x0)
#define MM_MISC_REG_CPU0_RVBA                                   MM_MISC_REG_CPU0_RVBA
#define MM_MISC_REG_CPU0_RVBA_POS                               (0U)
#define MM_MISC_REG_CPU0_RVBA_LEN                               (32U)
#define MM_MISC_REG_CPU0_RVBA_MSK                               (((1U<<MM_MISC_REG_CPU0_RVBA_LEN)-1)<<MM_MISC_REG_CPU0_RVBA_POS)
#define MM_MISC_REG_CPU0_RVBA_UMSK                              (~(((1U<<MM_MISC_REG_CPU0_RVBA_LEN)-1)<<MM_MISC_REG_CPU0_RVBA_POS))

/* 0x4 : CPU1_Boot */
#define MM_MISC_CPU1_BOOT_OFFSET                                (0x4)
#define MM_MISC_REG_CPU1_RVBA                                   MM_MISC_REG_CPU1_RVBA
#define MM_MISC_REG_CPU1_RVBA_POS                               (0U)
#define MM_MISC_REG_CPU1_RVBA_LEN                               (32U)
#define MM_MISC_REG_CPU1_RVBA_MSK                               (((1U<<MM_MISC_REG_CPU1_RVBA_LEN)-1)<<MM_MISC_REG_CPU1_RVBA_POS)
#define MM_MISC_REG_CPU1_RVBA_UMSK                              (~(((1U<<MM_MISC_REG_CPU1_RVBA_LEN)-1)<<MM_MISC_REG_CPU1_RVBA_POS))

/* 0x8 : CPU_cfg */
#define MM_MISC_CPU_CFG_OFFSET                                  (0x8)
#define MM_MISC_REG_CPU0_APB_BASE                               MM_MISC_REG_CPU0_APB_BASE
#define MM_MISC_REG_CPU0_APB_BASE_POS                           (0U)
#define MM_MISC_REG_CPU0_APB_BASE_LEN                           (13U)
#define MM_MISC_REG_CPU0_APB_BASE_MSK                           (((1U<<MM_MISC_REG_CPU0_APB_BASE_LEN)-1)<<MM_MISC_REG_CPU0_APB_BASE_POS)
#define MM_MISC_REG_CPU0_APB_BASE_UMSK                          (~(((1U<<MM_MISC_REG_CPU0_APB_BASE_LEN)-1)<<MM_MISC_REG_CPU0_APB_BASE_POS))
#define MM_MISC_REG_CPU1_APB_BASE                               MM_MISC_REG_CPU1_APB_BASE
#define MM_MISC_REG_CPU1_APB_BASE_POS                           (16U)
#define MM_MISC_REG_CPU1_APB_BASE_LEN                           (13U)
#define MM_MISC_REG_CPU1_APB_BASE_MSK                           (((1U<<MM_MISC_REG_CPU1_APB_BASE_LEN)-1)<<MM_MISC_REG_CPU1_APB_BASE_POS)
#define MM_MISC_REG_CPU1_APB_BASE_UMSK                          (~(((1U<<MM_MISC_REG_CPU1_APB_BASE_LEN)-1)<<MM_MISC_REG_CPU1_APB_BASE_POS))

/* 0xC : CPU_sts1 */
#define MM_MISC_CPU_STS1_OFFSET                                 (0xC)
#define MM_MISC_CPU0_JDB_PM                                     MM_MISC_CPU0_JDB_PM
#define MM_MISC_CPU0_JDB_PM_POS                                 (0U)
#define MM_MISC_CPU0_JDB_PM_LEN                                 (2U)
#define MM_MISC_CPU0_JDB_PM_MSK                                 (((1U<<MM_MISC_CPU0_JDB_PM_LEN)-1)<<MM_MISC_CPU0_JDB_PM_POS)
#define MM_MISC_CPU0_JDB_PM_UMSK                                (~(((1U<<MM_MISC_CPU0_JDB_PM_LEN)-1)<<MM_MISC_CPU0_JDB_PM_POS))
#define MM_MISC_CPU1_JDB_PM                                     MM_MISC_CPU1_JDB_PM
#define MM_MISC_CPU1_JDB_PM_POS                                 (2U)
#define MM_MISC_CPU1_JDB_PM_LEN                                 (2U)
#define MM_MISC_CPU1_JDB_PM_MSK                                 (((1U<<MM_MISC_CPU1_JDB_PM_LEN)-1)<<MM_MISC_CPU1_JDB_PM_POS)
#define MM_MISC_CPU1_JDB_PM_UMSK                                (~(((1U<<MM_MISC_CPU1_JDB_PM_LEN)-1)<<MM_MISC_CPU1_JDB_PM_POS))
#define MM_MISC_CPU0_LPMD_B                                     MM_MISC_CPU0_LPMD_B
#define MM_MISC_CPU0_LPMD_B_POS                                 (4U)
#define MM_MISC_CPU0_LPMD_B_LEN                                 (2U)
#define MM_MISC_CPU0_LPMD_B_MSK                                 (((1U<<MM_MISC_CPU0_LPMD_B_LEN)-1)<<MM_MISC_CPU0_LPMD_B_POS)
#define MM_MISC_CPU0_LPMD_B_UMSK                                (~(((1U<<MM_MISC_CPU0_LPMD_B_LEN)-1)<<MM_MISC_CPU0_LPMD_B_POS))
#define MM_MISC_CPU1_LPMD_B                                     MM_MISC_CPU1_LPMD_B
#define MM_MISC_CPU1_LPMD_B_POS                                 (6U)
#define MM_MISC_CPU1_LPMD_B_LEN                                 (2U)
#define MM_MISC_CPU1_LPMD_B_MSK                                 (((1U<<MM_MISC_CPU1_LPMD_B_LEN)-1)<<MM_MISC_CPU1_LPMD_B_POS)
#define MM_MISC_CPU1_LPMD_B_UMSK                                (~(((1U<<MM_MISC_CPU1_LPMD_B_LEN)-1)<<MM_MISC_CPU1_LPMD_B_POS))
#define MM_MISC_CPU0_RETIRE_PC_39_32                            MM_MISC_CPU0_RETIRE_PC_39_32
#define MM_MISC_CPU0_RETIRE_PC_39_32_POS                        (16U)
#define MM_MISC_CPU0_RETIRE_PC_39_32_LEN                        (8U)
#define MM_MISC_CPU0_RETIRE_PC_39_32_MSK                        (((1U<<MM_MISC_CPU0_RETIRE_PC_39_32_LEN)-1)<<MM_MISC_CPU0_RETIRE_PC_39_32_POS)
#define MM_MISC_CPU0_RETIRE_PC_39_32_UMSK                       (~(((1U<<MM_MISC_CPU0_RETIRE_PC_39_32_LEN)-1)<<MM_MISC_CPU0_RETIRE_PC_39_32_POS))
#define MM_MISC_CPU1_RETIRE_PC_39_32                            MM_MISC_CPU1_RETIRE_PC_39_32
#define MM_MISC_CPU1_RETIRE_PC_39_32_POS                        (24U)
#define MM_MISC_CPU1_RETIRE_PC_39_32_LEN                        (8U)
#define MM_MISC_CPU1_RETIRE_PC_39_32_MSK                        (((1U<<MM_MISC_CPU1_RETIRE_PC_39_32_LEN)-1)<<MM_MISC_CPU1_RETIRE_PC_39_32_POS)
#define MM_MISC_CPU1_RETIRE_PC_39_32_UMSK                       (~(((1U<<MM_MISC_CPU1_RETIRE_PC_39_32_LEN)-1)<<MM_MISC_CPU1_RETIRE_PC_39_32_POS))

/* 0x10 : CPU_sts2 */
#define MM_MISC_CPU_STS2_OFFSET                                 (0x10)
#define MM_MISC_CPU0_RETIRE_PC_31_0                             MM_MISC_CPU0_RETIRE_PC_31_0
#define MM_MISC_CPU0_RETIRE_PC_31_0_POS                         (0U)
#define MM_MISC_CPU0_RETIRE_PC_31_0_LEN                         (32U)
#define MM_MISC_CPU0_RETIRE_PC_31_0_MSK                         (((1U<<MM_MISC_CPU0_RETIRE_PC_31_0_LEN)-1)<<MM_MISC_CPU0_RETIRE_PC_31_0_POS)
#define MM_MISC_CPU0_RETIRE_PC_31_0_UMSK                        (~(((1U<<MM_MISC_CPU0_RETIRE_PC_31_0_LEN)-1)<<MM_MISC_CPU0_RETIRE_PC_31_0_POS))

/* 0x14 : CPU_sts3 */
#define MM_MISC_CPU_STS3_OFFSET                                 (0x14)
#define MM_MISC_CPU1_RETIRE_PC_31_0                             MM_MISC_CPU1_RETIRE_PC_31_0
#define MM_MISC_CPU1_RETIRE_PC_31_0_POS                         (0U)
#define MM_MISC_CPU1_RETIRE_PC_31_0_LEN                         (32U)
#define MM_MISC_CPU1_RETIRE_PC_31_0_MSK                         (((1U<<MM_MISC_CPU1_RETIRE_PC_31_0_LEN)-1)<<MM_MISC_CPU1_RETIRE_PC_31_0_POS)
#define MM_MISC_CPU1_RETIRE_PC_31_0_UMSK                        (~(((1U<<MM_MISC_CPU1_RETIRE_PC_31_0_LEN)-1)<<MM_MISC_CPU1_RETIRE_PC_31_0_POS))

/* 0x18 : CPU_RTC */
#define MM_MISC_CPU_RTC_OFFSET                                  (0x18)
#define MM_MISC_C906_RTC_DIV                                    MM_MISC_C906_RTC_DIV
#define MM_MISC_C906_RTC_DIV_POS                                (0U)
#define MM_MISC_C906_RTC_DIV_LEN                                (10U)
#define MM_MISC_C906_RTC_DIV_MSK                                (((1U<<MM_MISC_C906_RTC_DIV_LEN)-1)<<MM_MISC_C906_RTC_DIV_POS)
#define MM_MISC_C906_RTC_DIV_UMSK                               (~(((1U<<MM_MISC_C906_RTC_DIV_LEN)-1)<<MM_MISC_C906_RTC_DIV_POS))
#define MM_MISC_C906_RTC_RST                                    MM_MISC_C906_RTC_RST
#define MM_MISC_C906_RTC_RST_POS                                (30U)
#define MM_MISC_C906_RTC_RST_LEN                                (1U)
#define MM_MISC_C906_RTC_RST_MSK                                (((1U<<MM_MISC_C906_RTC_RST_LEN)-1)<<MM_MISC_C906_RTC_RST_POS)
#define MM_MISC_C906_RTC_RST_UMSK                               (~(((1U<<MM_MISC_C906_RTC_RST_LEN)-1)<<MM_MISC_C906_RTC_RST_POS))
#define MM_MISC_C906_RTC_EN                                     MM_MISC_C906_RTC_EN
#define MM_MISC_C906_RTC_EN_POS                                 (31U)
#define MM_MISC_C906_RTC_EN_LEN                                 (1U)
#define MM_MISC_C906_RTC_EN_MSK                                 (((1U<<MM_MISC_C906_RTC_EN_LEN)-1)<<MM_MISC_C906_RTC_EN_POS)
#define MM_MISC_C906_RTC_EN_UMSK                                (~(((1U<<MM_MISC_C906_RTC_EN_LEN)-1)<<MM_MISC_C906_RTC_EN_POS))

/* 0x1C : tzc_CPU */
#define MM_MISC_TZC_CPU_OFFSET                                  (0x1C)
#define MM_MISC_REG_CPU0_CFG_RD_LOCK                            MM_MISC_REG_CPU0_CFG_RD_LOCK
#define MM_MISC_REG_CPU0_CFG_RD_LOCK_POS                        (0U)
#define MM_MISC_REG_CPU0_CFG_RD_LOCK_LEN                        (1U)
#define MM_MISC_REG_CPU0_CFG_RD_LOCK_MSK                        (((1U<<MM_MISC_REG_CPU0_CFG_RD_LOCK_LEN)-1)<<MM_MISC_REG_CPU0_CFG_RD_LOCK_POS)
#define MM_MISC_REG_CPU0_CFG_RD_LOCK_UMSK                       (~(((1U<<MM_MISC_REG_CPU0_CFG_RD_LOCK_LEN)-1)<<MM_MISC_REG_CPU0_CFG_RD_LOCK_POS))
#define MM_MISC_REG_CPU0_CFG_WR_LOCK                            MM_MISC_REG_CPU0_CFG_WR_LOCK
#define MM_MISC_REG_CPU0_CFG_WR_LOCK_POS                        (1U)
#define MM_MISC_REG_CPU0_CFG_WR_LOCK_LEN                        (1U)
#define MM_MISC_REG_CPU0_CFG_WR_LOCK_MSK                        (((1U<<MM_MISC_REG_CPU0_CFG_WR_LOCK_LEN)-1)<<MM_MISC_REG_CPU0_CFG_WR_LOCK_POS)
#define MM_MISC_REG_CPU0_CFG_WR_LOCK_UMSK                       (~(((1U<<MM_MISC_REG_CPU0_CFG_WR_LOCK_LEN)-1)<<MM_MISC_REG_CPU0_CFG_WR_LOCK_POS))
#define MM_MISC_REG_CPU1_CFG_RD_LOCK                            MM_MISC_REG_CPU1_CFG_RD_LOCK
#define MM_MISC_REG_CPU1_CFG_RD_LOCK_POS                        (2U)
#define MM_MISC_REG_CPU1_CFG_RD_LOCK_LEN                        (1U)
#define MM_MISC_REG_CPU1_CFG_RD_LOCK_MSK                        (((1U<<MM_MISC_REG_CPU1_CFG_RD_LOCK_LEN)-1)<<MM_MISC_REG_CPU1_CFG_RD_LOCK_POS)
#define MM_MISC_REG_CPU1_CFG_RD_LOCK_UMSK                       (~(((1U<<MM_MISC_REG_CPU1_CFG_RD_LOCK_LEN)-1)<<MM_MISC_REG_CPU1_CFG_RD_LOCK_POS))
#define MM_MISC_REG_CPU1_CFG_WR_LOCK                            MM_MISC_REG_CPU1_CFG_WR_LOCK
#define MM_MISC_REG_CPU1_CFG_WR_LOCK_POS                        (3U)
#define MM_MISC_REG_CPU1_CFG_WR_LOCK_LEN                        (1U)
#define MM_MISC_REG_CPU1_CFG_WR_LOCK_MSK                        (((1U<<MM_MISC_REG_CPU1_CFG_WR_LOCK_LEN)-1)<<MM_MISC_REG_CPU1_CFG_WR_LOCK_POS)
#define MM_MISC_REG_CPU1_CFG_WR_LOCK_UMSK                       (~(((1U<<MM_MISC_REG_CPU1_CFG_WR_LOCK_LEN)-1)<<MM_MISC_REG_CPU1_CFG_WR_LOCK_POS))

/* 0x20 : peri_apb_ctrl */
#define MM_MISC_PERI_APB_CTRL_OFFSET                            (0x20)
#define MM_MISC_RG_PCLK_FORCE_ON                                MM_MISC_RG_PCLK_FORCE_ON
#define MM_MISC_RG_PCLK_FORCE_ON_POS                            (0U)
#define MM_MISC_RG_PCLK_FORCE_ON_LEN                            (16U)
#define MM_MISC_RG_PCLK_FORCE_ON_MSK                            (((1U<<MM_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MM_MISC_RG_PCLK_FORCE_ON_POS)
#define MM_MISC_RG_PCLK_FORCE_ON_UMSK                           (~(((1U<<MM_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MM_MISC_RG_PCLK_FORCE_ON_POS))

/* 0x2C : mm_infra_qos_ctrl */
#define MM_MISC_MM_INFRA_QOS_CTRL_OFFSET                        (0x2C)
#define MM_MISC_REG_DMA_AWQOS                                   MM_MISC_REG_DMA_AWQOS
#define MM_MISC_REG_DMA_AWQOS_POS                               (0U)
#define MM_MISC_REG_DMA_AWQOS_LEN                               (1U)
#define MM_MISC_REG_DMA_AWQOS_MSK                               (((1U<<MM_MISC_REG_DMA_AWQOS_LEN)-1)<<MM_MISC_REG_DMA_AWQOS_POS)
#define MM_MISC_REG_DMA_AWQOS_UMSK                              (~(((1U<<MM_MISC_REG_DMA_AWQOS_LEN)-1)<<MM_MISC_REG_DMA_AWQOS_POS))
#define MM_MISC_REG_DMA_ARQOS                                   MM_MISC_REG_DMA_ARQOS
#define MM_MISC_REG_DMA_ARQOS_POS                               (1U)
#define MM_MISC_REG_DMA_ARQOS_LEN                               (1U)
#define MM_MISC_REG_DMA_ARQOS_MSK                               (((1U<<MM_MISC_REG_DMA_ARQOS_LEN)-1)<<MM_MISC_REG_DMA_ARQOS_POS)
#define MM_MISC_REG_DMA_ARQOS_UMSK                              (~(((1U<<MM_MISC_REG_DMA_ARQOS_LEN)-1)<<MM_MISC_REG_DMA_ARQOS_POS))
#define MM_MISC_REG_MMCPU0_AWQOS                                MM_MISC_REG_MMCPU0_AWQOS
#define MM_MISC_REG_MMCPU0_AWQOS_POS                            (2U)
#define MM_MISC_REG_MMCPU0_AWQOS_LEN                            (1U)
#define MM_MISC_REG_MMCPU0_AWQOS_MSK                            (((1U<<MM_MISC_REG_MMCPU0_AWQOS_LEN)-1)<<MM_MISC_REG_MMCPU0_AWQOS_POS)
#define MM_MISC_REG_MMCPU0_AWQOS_UMSK                           (~(((1U<<MM_MISC_REG_MMCPU0_AWQOS_LEN)-1)<<MM_MISC_REG_MMCPU0_AWQOS_POS))
#define MM_MISC_REG_MMCPU0_ARQOS                                MM_MISC_REG_MMCPU0_ARQOS
#define MM_MISC_REG_MMCPU0_ARQOS_POS                            (3U)
#define MM_MISC_REG_MMCPU0_ARQOS_LEN                            (1U)
#define MM_MISC_REG_MMCPU0_ARQOS_MSK                            (((1U<<MM_MISC_REG_MMCPU0_ARQOS_LEN)-1)<<MM_MISC_REG_MMCPU0_ARQOS_POS)
#define MM_MISC_REG_MMCPU0_ARQOS_UMSK                           (~(((1U<<MM_MISC_REG_MMCPU0_ARQOS_LEN)-1)<<MM_MISC_REG_MMCPU0_ARQOS_POS))
#define MM_MISC_REG_MMCPU1_AWQOS                                MM_MISC_REG_MMCPU1_AWQOS
#define MM_MISC_REG_MMCPU1_AWQOS_POS                            (4U)
#define MM_MISC_REG_MMCPU1_AWQOS_LEN                            (1U)
#define MM_MISC_REG_MMCPU1_AWQOS_MSK                            (((1U<<MM_MISC_REG_MMCPU1_AWQOS_LEN)-1)<<MM_MISC_REG_MMCPU1_AWQOS_POS)
#define MM_MISC_REG_MMCPU1_AWQOS_UMSK                           (~(((1U<<MM_MISC_REG_MMCPU1_AWQOS_LEN)-1)<<MM_MISC_REG_MMCPU1_AWQOS_POS))
#define MM_MISC_REG_MMCPU1_ARQOS                                MM_MISC_REG_MMCPU1_ARQOS
#define MM_MISC_REG_MMCPU1_ARQOS_POS                            (5U)
#define MM_MISC_REG_MMCPU1_ARQOS_LEN                            (1U)
#define MM_MISC_REG_MMCPU1_ARQOS_MSK                            (((1U<<MM_MISC_REG_MMCPU1_ARQOS_LEN)-1)<<MM_MISC_REG_MMCPU1_ARQOS_POS)
#define MM_MISC_REG_MMCPU1_ARQOS_UMSK                           (~(((1U<<MM_MISC_REG_MMCPU1_ARQOS_LEN)-1)<<MM_MISC_REG_MMCPU1_ARQOS_POS))
#define MM_MISC_REG_H_WTHRE_MM2CONN                             MM_MISC_REG_H_WTHRE_MM2CONN
#define MM_MISC_REG_H_WTHRE_MM2CONN_POS                         (16U)
#define MM_MISC_REG_H_WTHRE_MM2CONN_LEN                         (2U)
#define MM_MISC_REG_H_WTHRE_MM2CONN_MSK                         (((1U<<MM_MISC_REG_H_WTHRE_MM2CONN_LEN)-1)<<MM_MISC_REG_H_WTHRE_MM2CONN_POS)
#define MM_MISC_REG_H_WTHRE_MM2CONN_UMSK                        (~(((1U<<MM_MISC_REG_H_WTHRE_MM2CONN_LEN)-1)<<MM_MISC_REG_H_WTHRE_MM2CONN_POS))
#define MM_MISC_REG_H_WTHRE_CONN2MM                             MM_MISC_REG_H_WTHRE_CONN2MM
#define MM_MISC_REG_H_WTHRE_CONN2MM_POS                         (18U)
#define MM_MISC_REG_H_WTHRE_CONN2MM_LEN                         (2U)
#define MM_MISC_REG_H_WTHRE_CONN2MM_MSK                         (((1U<<MM_MISC_REG_H_WTHRE_CONN2MM_LEN)-1)<<MM_MISC_REG_H_WTHRE_CONN2MM_POS)
#define MM_MISC_REG_H_WTHRE_CONN2MM_UMSK                        (~(((1U<<MM_MISC_REG_H_WTHRE_CONN2MM_LEN)-1)<<MM_MISC_REG_H_WTHRE_CONN2MM_POS))

/* 0x30 : mm_bus_dec_err */
#define MM_MISC_MM_BUS_DEC_ERR_OFFSET                           (0x30)
#define MM_MISC_REG_DEC_ERR_CLR                                 MM_MISC_REG_DEC_ERR_CLR
#define MM_MISC_REG_DEC_ERR_CLR_POS                             (0U)
#define MM_MISC_REG_DEC_ERR_CLR_LEN                             (1U)
#define MM_MISC_REG_DEC_ERR_CLR_MSK                             (((1U<<MM_MISC_REG_DEC_ERR_CLR_LEN)-1)<<MM_MISC_REG_DEC_ERR_CLR_POS)
#define MM_MISC_REG_DEC_ERR_CLR_UMSK                            (~(((1U<<MM_MISC_REG_DEC_ERR_CLR_LEN)-1)<<MM_MISC_REG_DEC_ERR_CLR_POS))
#define MM_MISC_REG_DEC_ERR_LATCH_LAST                          MM_MISC_REG_DEC_ERR_LATCH_LAST
#define MM_MISC_REG_DEC_ERR_LATCH_LAST_POS                      (1U)
#define MM_MISC_REG_DEC_ERR_LATCH_LAST_LEN                      (1U)
#define MM_MISC_REG_DEC_ERR_LATCH_LAST_MSK                      (((1U<<MM_MISC_REG_DEC_ERR_LATCH_LAST_LEN)-1)<<MM_MISC_REG_DEC_ERR_LATCH_LAST_POS)
#define MM_MISC_REG_DEC_ERR_LATCH_LAST_UMSK                     (~(((1U<<MM_MISC_REG_DEC_ERR_LATCH_LAST_LEN)-1)<<MM_MISC_REG_DEC_ERR_LATCH_LAST_POS))
#define MM_MISC_MMINFRA_DEC_ERR_LAT                             MM_MISC_MMINFRA_DEC_ERR_LAT
#define MM_MISC_MMINFRA_DEC_ERR_LAT_POS                         (8U)
#define MM_MISC_MMINFRA_DEC_ERR_LAT_LEN                         (1U)
#define MM_MISC_MMINFRA_DEC_ERR_LAT_MSK                         (((1U<<MM_MISC_MMINFRA_DEC_ERR_LAT_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_LAT_POS)
#define MM_MISC_MMINFRA_DEC_ERR_LAT_UMSK                        (~(((1U<<MM_MISC_MMINFRA_DEC_ERR_LAT_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_LAT_POS))
#define MM_MISC_MMINFRA_DEC_ERR_WRITE                           MM_MISC_MMINFRA_DEC_ERR_WRITE
#define MM_MISC_MMINFRA_DEC_ERR_WRITE_POS                       (9U)
#define MM_MISC_MMINFRA_DEC_ERR_WRITE_LEN                       (1U)
#define MM_MISC_MMINFRA_DEC_ERR_WRITE_MSK                       (((1U<<MM_MISC_MMINFRA_DEC_ERR_WRITE_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_WRITE_POS)
#define MM_MISC_MMINFRA_DEC_ERR_WRITE_UMSK                      (~(((1U<<MM_MISC_MMINFRA_DEC_ERR_WRITE_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_WRITE_POS))
#define MM_MISC_MMINFRA_DEC_ERR_SRC                             MM_MISC_MMINFRA_DEC_ERR_SRC
#define MM_MISC_MMINFRA_DEC_ERR_SRC_POS                         (12U)
#define MM_MISC_MMINFRA_DEC_ERR_SRC_LEN                         (3U)
#define MM_MISC_MMINFRA_DEC_ERR_SRC_MSK                         (((1U<<MM_MISC_MMINFRA_DEC_ERR_SRC_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_SRC_POS)
#define MM_MISC_MMINFRA_DEC_ERR_SRC_UMSK                        (~(((1U<<MM_MISC_MMINFRA_DEC_ERR_SRC_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_SRC_POS))
#define MM_MISC_MMINFRA_DEC_ERR_ID                              MM_MISC_MMINFRA_DEC_ERR_ID
#define MM_MISC_MMINFRA_DEC_ERR_ID_POS                          (16U)
#define MM_MISC_MMINFRA_DEC_ERR_ID_LEN                          (5U)
#define MM_MISC_MMINFRA_DEC_ERR_ID_MSK                          (((1U<<MM_MISC_MMINFRA_DEC_ERR_ID_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_ID_POS)
#define MM_MISC_MMINFRA_DEC_ERR_ID_UMSK                         (~(((1U<<MM_MISC_MMINFRA_DEC_ERR_ID_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_ID_POS))

/* 0x34 : mm_bus_dec_err_addr */
#define MM_MISC_MM_BUS_DEC_ERR_ADDR_OFFSET                      (0x34)
#define MM_MISC_MMINFRA_DEC_ERR_ADDR                            MM_MISC_MMINFRA_DEC_ERR_ADDR
#define MM_MISC_MMINFRA_DEC_ERR_ADDR_POS                        (0U)
#define MM_MISC_MMINFRA_DEC_ERR_ADDR_LEN                        (32U)
#define MM_MISC_MMINFRA_DEC_ERR_ADDR_MSK                        (((1U<<MM_MISC_MMINFRA_DEC_ERR_ADDR_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_ADDR_POS)
#define MM_MISC_MMINFRA_DEC_ERR_ADDR_UMSK                       (~(((1U<<MM_MISC_MMINFRA_DEC_ERR_ADDR_LEN)-1)<<MM_MISC_MMINFRA_DEC_ERR_ADDR_POS))

/* 0x38 : mcu_bus_dec_err */
#define MM_MISC_MCU_BUS_DEC_ERR_OFFSET                          (0x38)
#define MM_MISC_REG_DEC_ERR_CLR_MCU                             MM_MISC_REG_DEC_ERR_CLR_MCU
#define MM_MISC_REG_DEC_ERR_CLR_MCU_POS                         (0U)
#define MM_MISC_REG_DEC_ERR_CLR_MCU_LEN                         (1U)
#define MM_MISC_REG_DEC_ERR_CLR_MCU_MSK                         (((1U<<MM_MISC_REG_DEC_ERR_CLR_MCU_LEN)-1)<<MM_MISC_REG_DEC_ERR_CLR_MCU_POS)
#define MM_MISC_REG_DEC_ERR_CLR_MCU_UMSK                        (~(((1U<<MM_MISC_REG_DEC_ERR_CLR_MCU_LEN)-1)<<MM_MISC_REG_DEC_ERR_CLR_MCU_POS))
#define MM_MISC_REG_DEC_ERR_LAST_MCU                            MM_MISC_REG_DEC_ERR_LAST_MCU
#define MM_MISC_REG_DEC_ERR_LAST_MCU_POS                        (1U)
#define MM_MISC_REG_DEC_ERR_LAST_MCU_LEN                        (1U)
#define MM_MISC_REG_DEC_ERR_LAST_MCU_MSK                        (((1U<<MM_MISC_REG_DEC_ERR_LAST_MCU_LEN)-1)<<MM_MISC_REG_DEC_ERR_LAST_MCU_POS)
#define MM_MISC_REG_DEC_ERR_LAST_MCU_UMSK                       (~(((1U<<MM_MISC_REG_DEC_ERR_LAST_MCU_LEN)-1)<<MM_MISC_REG_DEC_ERR_LAST_MCU_POS))
#define MM_MISC_MCU_DEC_ERR_LAT                                 MM_MISC_MCU_DEC_ERR_LAT
#define MM_MISC_MCU_DEC_ERR_LAT_POS                             (8U)
#define MM_MISC_MCU_DEC_ERR_LAT_LEN                             (1U)
#define MM_MISC_MCU_DEC_ERR_LAT_MSK                             (((1U<<MM_MISC_MCU_DEC_ERR_LAT_LEN)-1)<<MM_MISC_MCU_DEC_ERR_LAT_POS)
#define MM_MISC_MCU_DEC_ERR_LAT_UMSK                            (~(((1U<<MM_MISC_MCU_DEC_ERR_LAT_LEN)-1)<<MM_MISC_MCU_DEC_ERR_LAT_POS))
#define MM_MISC_MCU_DEC_ERR_WRITE                               MM_MISC_MCU_DEC_ERR_WRITE
#define MM_MISC_MCU_DEC_ERR_WRITE_POS                           (9U)
#define MM_MISC_MCU_DEC_ERR_WRITE_LEN                           (1U)
#define MM_MISC_MCU_DEC_ERR_WRITE_MSK                           (((1U<<MM_MISC_MCU_DEC_ERR_WRITE_LEN)-1)<<MM_MISC_MCU_DEC_ERR_WRITE_POS)
#define MM_MISC_MCU_DEC_ERR_WRITE_UMSK                          (~(((1U<<MM_MISC_MCU_DEC_ERR_WRITE_LEN)-1)<<MM_MISC_MCU_DEC_ERR_WRITE_POS))
#define MM_MISC_MCU_DEC_ERR_SRC                                 MM_MISC_MCU_DEC_ERR_SRC
#define MM_MISC_MCU_DEC_ERR_SRC_POS                             (12U)
#define MM_MISC_MCU_DEC_ERR_SRC_LEN                             (2U)
#define MM_MISC_MCU_DEC_ERR_SRC_MSK                             (((1U<<MM_MISC_MCU_DEC_ERR_SRC_LEN)-1)<<MM_MISC_MCU_DEC_ERR_SRC_POS)
#define MM_MISC_MCU_DEC_ERR_SRC_UMSK                            (~(((1U<<MM_MISC_MCU_DEC_ERR_SRC_LEN)-1)<<MM_MISC_MCU_DEC_ERR_SRC_POS))
#define MM_MISC_MCU_DEC_ERR_ID                                  MM_MISC_MCU_DEC_ERR_ID
#define MM_MISC_MCU_DEC_ERR_ID_POS                              (16U)
#define MM_MISC_MCU_DEC_ERR_ID_LEN                              (6U)
#define MM_MISC_MCU_DEC_ERR_ID_MSK                              (((1U<<MM_MISC_MCU_DEC_ERR_ID_LEN)-1)<<MM_MISC_MCU_DEC_ERR_ID_POS)
#define MM_MISC_MCU_DEC_ERR_ID_UMSK                             (~(((1U<<MM_MISC_MCU_DEC_ERR_ID_LEN)-1)<<MM_MISC_MCU_DEC_ERR_ID_POS))

/* 0x3C : mcu_bus_dec_err_addr */
#define MM_MISC_MCU_BUS_DEC_ERR_ADDR_OFFSET                     (0x3C)
#define MM_MISC_MCU_DEC_ERR_ADDR                                MM_MISC_MCU_DEC_ERR_ADDR
#define MM_MISC_MCU_DEC_ERR_ADDR_POS                            (0U)
#define MM_MISC_MCU_DEC_ERR_ADDR_LEN                            (32U)
#define MM_MISC_MCU_DEC_ERR_ADDR_MSK                            (((1U<<MM_MISC_MCU_DEC_ERR_ADDR_LEN)-1)<<MM_MISC_MCU_DEC_ERR_ADDR_POS)
#define MM_MISC_MCU_DEC_ERR_ADDR_UMSK                           (~(((1U<<MM_MISC_MCU_DEC_ERR_ADDR_LEN)-1)<<MM_MISC_MCU_DEC_ERR_ADDR_POS))

/* 0x40 : dma_clk_ctrl */
#define MM_MISC_DMA_CLK_CTRL_OFFSET                             (0x40)
#define MM_MISC_DMA_CLK_EN                                      MM_MISC_DMA_CLK_EN
#define MM_MISC_DMA_CLK_EN_POS                                  (0U)
#define MM_MISC_DMA_CLK_EN_LEN                                  (8U)
#define MM_MISC_DMA_CLK_EN_MSK                                  (((1U<<MM_MISC_DMA_CLK_EN_LEN)-1)<<MM_MISC_DMA_CLK_EN_POS)
#define MM_MISC_DMA_CLK_EN_UMSK                                 (~(((1U<<MM_MISC_DMA_CLK_EN_LEN)-1)<<MM_MISC_DMA_CLK_EN_POS))

/* 0x50 : sram_ctrl */
#define MM_MISC_SRAM_CTRL_OFFSET                                (0x50)
#define MM_MISC_REG_BLAI_SRAM_SEL                               MM_MISC_REG_BLAI_SRAM_SEL
#define MM_MISC_REG_BLAI_SRAM_SEL_POS                           (0U)
#define MM_MISC_REG_BLAI_SRAM_SEL_LEN                           (1U)
#define MM_MISC_REG_BLAI_SRAM_SEL_MSK                           (((1U<<MM_MISC_REG_BLAI_SRAM_SEL_LEN)-1)<<MM_MISC_REG_BLAI_SRAM_SEL_POS)
#define MM_MISC_REG_BLAI_SRAM_SEL_UMSK                          (~(((1U<<MM_MISC_REG_BLAI_SRAM_SEL_LEN)-1)<<MM_MISC_REG_BLAI_SRAM_SEL_POS))

/* 0x60 : sram_parm */
#define MM_MISC_SRAM_PARM_OFFSET                                (0x60)
#define MM_MISC_REG_SRAM_CPU_RAM_DVS                            MM_MISC_REG_SRAM_CPU_RAM_DVS
#define MM_MISC_REG_SRAM_CPU_RAM_DVS_POS                        (0U)
#define MM_MISC_REG_SRAM_CPU_RAM_DVS_LEN                        (4U)
#define MM_MISC_REG_SRAM_CPU_RAM_DVS_MSK                        (((1U<<MM_MISC_REG_SRAM_CPU_RAM_DVS_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_DVS_POS)
#define MM_MISC_REG_SRAM_CPU_RAM_DVS_UMSK                       (~(((1U<<MM_MISC_REG_SRAM_CPU_RAM_DVS_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_DVS_POS))
#define MM_MISC_REG_SRAM_CPU_RAM_DVSE                           MM_MISC_REG_SRAM_CPU_RAM_DVSE
#define MM_MISC_REG_SRAM_CPU_RAM_DVSE_POS                       (4U)
#define MM_MISC_REG_SRAM_CPU_RAM_DVSE_LEN                       (1U)
#define MM_MISC_REG_SRAM_CPU_RAM_DVSE_MSK                       (((1U<<MM_MISC_REG_SRAM_CPU_RAM_DVSE_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_DVSE_POS)
#define MM_MISC_REG_SRAM_CPU_RAM_DVSE_UMSK                      (~(((1U<<MM_MISC_REG_SRAM_CPU_RAM_DVSE_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_DVSE_POS))
#define MM_MISC_REG_SRAM_CPU_RAM_NAP                            MM_MISC_REG_SRAM_CPU_RAM_NAP
#define MM_MISC_REG_SRAM_CPU_RAM_NAP_POS                        (5U)
#define MM_MISC_REG_SRAM_CPU_RAM_NAP_LEN                        (1U)
#define MM_MISC_REG_SRAM_CPU_RAM_NAP_MSK                        (((1U<<MM_MISC_REG_SRAM_CPU_RAM_NAP_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_NAP_POS)
#define MM_MISC_REG_SRAM_CPU_RAM_NAP_UMSK                       (~(((1U<<MM_MISC_REG_SRAM_CPU_RAM_NAP_LEN)-1)<<MM_MISC_REG_SRAM_CPU_RAM_NAP_POS))
#define MM_MISC_REG_SRAM_L2RAM_DVS                              MM_MISC_REG_SRAM_L2RAM_DVS
#define MM_MISC_REG_SRAM_L2RAM_DVS_POS                          (8U)
#define MM_MISC_REG_SRAM_L2RAM_DVS_LEN                          (4U)
#define MM_MISC_REG_SRAM_L2RAM_DVS_MSK                          (((1U<<MM_MISC_REG_SRAM_L2RAM_DVS_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_DVS_POS)
#define MM_MISC_REG_SRAM_L2RAM_DVS_UMSK                         (~(((1U<<MM_MISC_REG_SRAM_L2RAM_DVS_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_DVS_POS))
#define MM_MISC_REG_SRAM_L2RAM_DVSE                             MM_MISC_REG_SRAM_L2RAM_DVSE
#define MM_MISC_REG_SRAM_L2RAM_DVSE_POS                         (12U)
#define MM_MISC_REG_SRAM_L2RAM_DVSE_LEN                         (1U)
#define MM_MISC_REG_SRAM_L2RAM_DVSE_MSK                         (((1U<<MM_MISC_REG_SRAM_L2RAM_DVSE_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_DVSE_POS)
#define MM_MISC_REG_SRAM_L2RAM_DVSE_UMSK                        (~(((1U<<MM_MISC_REG_SRAM_L2RAM_DVSE_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_DVSE_POS))
#define MM_MISC_REG_SRAM_L2RAM_NAP                              MM_MISC_REG_SRAM_L2RAM_NAP
#define MM_MISC_REG_SRAM_L2RAM_NAP_POS                          (13U)
#define MM_MISC_REG_SRAM_L2RAM_NAP_LEN                          (1U)
#define MM_MISC_REG_SRAM_L2RAM_NAP_MSK                          (((1U<<MM_MISC_REG_SRAM_L2RAM_NAP_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_NAP_POS)
#define MM_MISC_REG_SRAM_L2RAM_NAP_UMSK                         (~(((1U<<MM_MISC_REG_SRAM_L2RAM_NAP_LEN)-1)<<MM_MISC_REG_SRAM_L2RAM_NAP_POS))

/* 0x80 : codec_misc_1 */
#define MM_MISC_CODEC_MISC_1_OFFSET                             (0x80)
#define MM_MISC_REG_BLAI_CMD_CNT                                MM_MISC_REG_BLAI_CMD_CNT
#define MM_MISC_REG_BLAI_CMD_CNT_POS                            (0U)
#define MM_MISC_REG_BLAI_CMD_CNT_LEN                            (16U)
#define MM_MISC_REG_BLAI_CMD_CNT_MSK                            (((1U<<MM_MISC_REG_BLAI_CMD_CNT_LEN)-1)<<MM_MISC_REG_BLAI_CMD_CNT_POS)
#define MM_MISC_REG_BLAI_CMD_CNT_UMSK                           (~(((1U<<MM_MISC_REG_BLAI_CMD_CNT_LEN)-1)<<MM_MISC_REG_BLAI_CMD_CNT_POS))
#define MM_MISC_REG_BLAI_CMD_MODE                               MM_MISC_REG_BLAI_CMD_MODE
#define MM_MISC_REG_BLAI_CMD_MODE_POS                           (31U)
#define MM_MISC_REG_BLAI_CMD_MODE_LEN                           (1U)
#define MM_MISC_REG_BLAI_CMD_MODE_MSK                           (((1U<<MM_MISC_REG_BLAI_CMD_MODE_LEN)-1)<<MM_MISC_REG_BLAI_CMD_MODE_POS)
#define MM_MISC_REG_BLAI_CMD_MODE_UMSK                          (~(((1U<<MM_MISC_REG_BLAI_CMD_MODE_LEN)-1)<<MM_MISC_REG_BLAI_CMD_MODE_POS))

/* 0xA0 : MM_INT_STA0 */
#define MM_MISC_MM_INT_STA0_OFFSET                              (0xA0)
#define MM_MISC_MM_INT_STA0                                     MM_MISC_MM_INT_STA0
#define MM_MISC_MM_INT_STA0_POS                                 (0U)
#define MM_MISC_MM_INT_STA0_LEN                                 (32U)
#define MM_MISC_MM_INT_STA0_MSK                                 (((1U<<MM_MISC_MM_INT_STA0_LEN)-1)<<MM_MISC_MM_INT_STA0_POS)
#define MM_MISC_MM_INT_STA0_UMSK                                (~(((1U<<MM_MISC_MM_INT_STA0_LEN)-1)<<MM_MISC_MM_INT_STA0_POS))

/* 0xA4 : MM_INT_MASK0 */
#define MM_MISC_MM_INT_MASK0_OFFSET                             (0xA4)
#define MM_MISC_MM_INT_MASK0                                    MM_MISC_MM_INT_MASK0
#define MM_MISC_MM_INT_MASK0_POS                                (0U)
#define MM_MISC_MM_INT_MASK0_LEN                                (32U)
#define MM_MISC_MM_INT_MASK0_MSK                                (((1U<<MM_MISC_MM_INT_MASK0_LEN)-1)<<MM_MISC_MM_INT_MASK0_POS)
#define MM_MISC_MM_INT_MASK0_UMSK                               (~(((1U<<MM_MISC_MM_INT_MASK0_LEN)-1)<<MM_MISC_MM_INT_MASK0_POS))

/* 0xA8 : MM_INT_CLR0 */
#define MM_MISC_MM_INT_CLR0_OFFSET                              (0xA8)
#define MM_MISC_MM_INT_CLR0                                     MM_MISC_MM_INT_CLR0
#define MM_MISC_MM_INT_CLR0_POS                                 (0U)
#define MM_MISC_MM_INT_CLR0_LEN                                 (32U)
#define MM_MISC_MM_INT_CLR0_MSK                                 (((1U<<MM_MISC_MM_INT_CLR0_LEN)-1)<<MM_MISC_MM_INT_CLR0_POS)
#define MM_MISC_MM_INT_CLR0_UMSK                                (~(((1U<<MM_MISC_MM_INT_CLR0_LEN)-1)<<MM_MISC_MM_INT_CLR0_POS))

/* 0xFC : mmsys_misc_dummy */
#define MM_MISC_MMSYS_MISC_DUMMY_OFFSET                         (0xFC)
#define MM_MISC_DUMMY_REG                                       MM_MISC_DUMMY_REG
#define MM_MISC_DUMMY_REG_POS                                   (0U)
#define MM_MISC_DUMMY_REG_LEN                                   (32U)
#define MM_MISC_DUMMY_REG_MSK                                   (((1U<<MM_MISC_DUMMY_REG_LEN)-1)<<MM_MISC_DUMMY_REG_POS)
#define MM_MISC_DUMMY_REG_UMSK                                  (~(((1U<<MM_MISC_DUMMY_REG_LEN)-1)<<MM_MISC_DUMMY_REG_POS))

/* 0x100 : DDR_debug */
#define MM_MISC_DDR_DEBUG_OFFSET                                (0x100)
#define MM_MISC_DDR_CALIB_DONE                                  MM_MISC_DDR_CALIB_DONE
#define MM_MISC_DDR_CALIB_DONE_POS                              (0U)
#define MM_MISC_DDR_CALIB_DONE_LEN                              (1U)
#define MM_MISC_DDR_CALIB_DONE_MSK                              (((1U<<MM_MISC_DDR_CALIB_DONE_LEN)-1)<<MM_MISC_DDR_CALIB_DONE_POS)
#define MM_MISC_DDR_CALIB_DONE_UMSK                             (~(((1U<<MM_MISC_DDR_CALIB_DONE_LEN)-1)<<MM_MISC_DDR_CALIB_DONE_POS))


struct  mm_misc_reg {
    /* 0x0 : CPU0_Boot */
    union {
        struct {
            uint32_t reg_cpu0_rvba                  : 32; /* [31: 0],        r/w, 0x3eff0000 */
        }BF;
        uint32_t WORD;
    } CPU0_Boot;

    /* 0x4 : CPU1_Boot */
    union {
        struct {
            uint32_t reg_cpu1_rvba                  : 32; /* [31: 0],        r/w, 0x3eff0000 */
        }BF;
        uint32_t WORD;
    } CPU1_Boot;

    /* 0x8 : CPU_cfg */
    union {
        struct {
            uint32_t reg_cpu0_apb_base              : 13; /* [12: 0],        r/w,       0x1c */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t reg_cpu1_apb_base              : 13; /* [28:16],        r/w,       0x1c */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } CPU_cfg;

    /* 0xC : CPU_sts1 */
    union {
        struct {
            uint32_t cpu0_jdb_pm                    :  2; /* [ 1: 0],          r,        0x0 */
            uint32_t cpu1_jdb_pm                    :  2; /* [ 3: 2],          r,        0x0 */
            uint32_t cpu0_lpmd_b                    :  2; /* [ 5: 4],          r,        0x0 */
            uint32_t cpu1_lpmd_b                    :  2; /* [ 7: 6],          r,        0x0 */
            uint32_t reserved_8_15                  :  8; /* [15: 8],       rsvd,        0x0 */
            uint32_t cpu0_retire_pc_39_32           :  8; /* [23:16],          r,        0x0 */
            uint32_t cpu1_retire_pc_39_32           :  8; /* [31:24],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } CPU_sts1;

    /* 0x10 : CPU_sts2 */
    union {
        struct {
            uint32_t cpu0_retire_pc_31_0            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } CPU_sts2;

    /* 0x14 : CPU_sts3 */
    union {
        struct {
            uint32_t cpu1_retire_pc_31_0            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } CPU_sts3;

    /* 0x18 : CPU_RTC */
    union {
        struct {
            uint32_t c906_rtc_div                   : 10; /* [ 9: 0],        r/w,        0xa */
            uint32_t reserved_10_29                 : 20; /* [29:10],       rsvd,        0x0 */
            uint32_t c906_rtc_rst                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t c906_rtc_en                    :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } CPU_RTC;

    /* 0x1C : tzc_CPU */
    union {
        struct {
            uint32_t reg_cpu0_cfg_rd_lock           :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_cpu0_cfg_wr_lock           :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_cpu1_cfg_rd_lock           :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_cpu1_cfg_wr_lock           :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4_31                  : 28; /* [31: 4],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_CPU;

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
            uint32_t reg_mmcpu0_awqos               :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_mmcpu0_arqos               :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_mmcpu1_awqos               :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_mmcpu1_arqos               :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_h_wthre_mm2conn            :  2; /* [17:16],        r/w,        0x0 */
            uint32_t reg_h_wthre_conn2mm            :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_qos_ctrl;

    /* 0x30 : mm_bus_dec_err */
    union {
        struct {
            uint32_t reg_dec_err_clr                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_dec_err_latch_last         :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_lat            :  1; /* [    8],          r,        0x0 */
            uint32_t mminfra_dec_err_write          :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_src            :  3; /* [14:12],          r,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t mminfra_dec_err_id             :  5; /* [20:16],          r,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
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
            uint32_t reg_dec_err_clr_mcu            :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_dec_err_last_mcu           :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t mcu_dec_err_lat                :  1; /* [    8],          r,        0x0 */
            uint32_t mcu_dec_err_write              :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t mcu_dec_err_src                :  2; /* [13:12],          r,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t mcu_dec_err_id                 :  6; /* [21:16],          r,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
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

    /* 0x50 : sram_ctrl */
    union {
        struct {
            uint32_t reg_blai_sram_sel              :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sram_ctrl;

    /* 0x54  reserved */
    uint8_t RESERVED0x54[12];

    /* 0x60 : sram_parm */
    union {
        struct {
            uint32_t reg_sram_cpu_ram_dvs           :  4; /* [ 3: 0],        r/w,        0xc */
            uint32_t reg_sram_cpu_ram_dvse          :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_sram_cpu_ram_nap           :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_sram_l2ram_dvs             :  4; /* [11: 8],        r/w,        0xc */
            uint32_t reg_sram_l2ram_dvse            :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_sram_l2ram_nap             :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sram_parm;

    /* 0x64  reserved */
    uint8_t RESERVED0x64[28];

    /* 0x80 : codec_misc_1 */
    union {
        struct {
            uint32_t reg_blai_cmd_cnt               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_30                 : 15; /* [30:16],       rsvd,        0x0 */
            uint32_t reg_blai_cmd_mode              :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } codec_misc_1;

    /* 0x84  reserved */
    uint8_t RESERVED0x84[28];

    /* 0xA0 : MM_INT_STA0 */
    union {
        struct {
            uint32_t mm_int_sta0                    : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } MM_INT_STA0;

    /* 0xA4 : MM_INT_MASK0 */
    union {
        struct {
            uint32_t mm_int_mask0                   : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } MM_INT_MASK0;

    /* 0xA8 : MM_INT_CLR0 */
    union {
        struct {
            uint32_t mm_int_clr0                    : 32; /* [31: 0],        w1c,        0x0 */
        }BF;
        uint32_t WORD;
    } MM_INT_CLR0;

    /* 0xac  reserved */
    uint8_t RESERVED0xac[80];

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

typedef volatile struct mm_misc_reg mm_misc_reg_t;


#endif  /* __MM_MISC_REG_H__ */
