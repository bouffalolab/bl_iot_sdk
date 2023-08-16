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
#ifndef  __MCU_MISC_REG_H__
#define  __MCU_MISC_REG_H__

#include "bl808.h"

/* 0x0 : l1c_config */
#define MCU_MISC_L1C_CONFIG_OFFSET                              (0x0)
#define MCU_MISC_PATCH_D_EN                                     MCU_MISC_PATCH_D_EN
#define MCU_MISC_PATCH_D_EN_POS                                 (4U)
#define MCU_MISC_PATCH_D_EN_LEN                                 (2U)
#define MCU_MISC_PATCH_D_EN_MSK                                 (((1U<<MCU_MISC_PATCH_D_EN_LEN)-1)<<MCU_MISC_PATCH_D_EN_POS)
#define MCU_MISC_PATCH_D_EN_UMSK                                (~(((1U<<MCU_MISC_PATCH_D_EN_LEN)-1)<<MCU_MISC_PATCH_D_EN_POS))
#define MCU_MISC_PATCH_OPTION                                   MCU_MISC_PATCH_OPTION
#define MCU_MISC_PATCH_OPTION_POS                               (6U)
#define MCU_MISC_PATCH_OPTION_LEN                               (1U)
#define MCU_MISC_PATCH_OPTION_MSK                               (((1U<<MCU_MISC_PATCH_OPTION_LEN)-1)<<MCU_MISC_PATCH_OPTION_POS)
#define MCU_MISC_PATCH_OPTION_UMSK                              (~(((1U<<MCU_MISC_PATCH_OPTION_LEN)-1)<<MCU_MISC_PATCH_OPTION_POS))
#define MCU_MISC_PRAM_CLK_SEL                                   MCU_MISC_PRAM_CLK_SEL
#define MCU_MISC_PRAM_CLK_SEL_POS                               (7U)
#define MCU_MISC_PRAM_CLK_SEL_LEN                               (1U)
#define MCU_MISC_PRAM_CLK_SEL_MSK                               (((1U<<MCU_MISC_PRAM_CLK_SEL_LEN)-1)<<MCU_MISC_PRAM_CLK_SEL_POS)
#define MCU_MISC_PRAM_CLK_SEL_UMSK                              (~(((1U<<MCU_MISC_PRAM_CLK_SEL_LEN)-1)<<MCU_MISC_PRAM_CLK_SEL_POS))
#define MCU_MISC_IROM_2T_ACCESS                                 MCU_MISC_IROM_2T_ACCESS
#define MCU_MISC_IROM_2T_ACCESS_POS                             (12U)
#define MCU_MISC_IROM_2T_ACCESS_LEN                             (1U)
#define MCU_MISC_IROM_2T_ACCESS_MSK                             (((1U<<MCU_MISC_IROM_2T_ACCESS_LEN)-1)<<MCU_MISC_IROM_2T_ACCESS_POS)
#define MCU_MISC_IROM_2T_ACCESS_UMSK                            (~(((1U<<MCU_MISC_IROM_2T_ACCESS_LEN)-1)<<MCU_MISC_IROM_2T_ACCESS_POS))
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT                          MCU_MISC_STS_MCU_INFRA_TIMEOUT
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS                      (16U)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN                      (6U)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_MSK                      (((1U<<MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS)
#define MCU_MISC_STS_MCU_INFRA_TIMEOUT_UMSK                     (~(((1U<<MCU_MISC_STS_MCU_INFRA_TIMEOUT_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_TIMEOUT_POS))
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN                       MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS                   (24U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN                   (6U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_MSK                   (((1U<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_UMSK                  (~(((1U<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_EN_POS))

/* 0x4 : bus_error_clr_sts */
#define MCU_MISC_BUS_ERROR_CLR_STS_OFFSET                       (0x4)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR                      MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS                  (0U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN                  (1U)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_MSK                  (((1U<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS)
#define MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_UMSK                 (~(((1U<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_TIMEOUT_CLR_POS))
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR                      MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_POS                  (1U)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_LEN                  (1U)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_MSK                  (((1U<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_POS)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_UMSK                 (~(((1U<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_CLR_POS))
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT                      MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_POS                  (2U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_LEN                  (1U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_MSK                  (((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_POS)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_UMSK                 (~(((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_INT_POS))
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE                    MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_POS                (3U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_LEN                (1U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_MSK                (((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_POS)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_UMSK               (~(((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_WRITE_POS))
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC                      MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_POS                  (4U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_LEN                  (3U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_MSK                  (((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_POS)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_UMSK                 (~(((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_SRC_POS))

/* 0x8 : bus_error_addr */
#define MCU_MISC_BUS_ERROR_ADDR_OFFSET                          (0x8)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR                     MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_POS                 (0U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_LEN                 (32U)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_MSK                 (((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_POS)
#define MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_UMSK                (~(((1U<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_LEN)-1)<<MCU_MISC_STS_MCU_INFRA_DEC_ERR_ADDR_POS))

/* 0xC : bus_cfg */
#define MCU_MISC_BUS_CFG_OFFSET                                 (0xC)
#define MCU_MISC_REG_MCU_D1_HQOS                                MCU_MISC_REG_MCU_D1_HQOS
#define MCU_MISC_REG_MCU_D1_HQOS_POS                            (0U)
#define MCU_MISC_REG_MCU_D1_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_D1_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_D1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_D1_HQOS_POS)
#define MCU_MISC_REG_MCU_D1_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_D1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_D1_HQOS_POS))
#define MCU_MISC_REG_MCU_D2_HQOS                                MCU_MISC_REG_MCU_D2_HQOS
#define MCU_MISC_REG_MCU_D2_HQOS_POS                            (1U)
#define MCU_MISC_REG_MCU_D2_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_D2_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_D2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_D2_HQOS_POS)
#define MCU_MISC_REG_MCU_D2_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_D2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_D2_HQOS_POS))
#define MCU_MISC_REG_MCU_I1_HQOS                                MCU_MISC_REG_MCU_I1_HQOS
#define MCU_MISC_REG_MCU_I1_HQOS_POS                            (2U)
#define MCU_MISC_REG_MCU_I1_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_I1_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_I1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_I1_HQOS_POS)
#define MCU_MISC_REG_MCU_I1_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_I1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_I1_HQOS_POS))
#define MCU_MISC_REG_MCU_I2_HQOS                                MCU_MISC_REG_MCU_I2_HQOS
#define MCU_MISC_REG_MCU_I2_HQOS_POS                            (3U)
#define MCU_MISC_REG_MCU_I2_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_I2_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_I2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_I2_HQOS_POS)
#define MCU_MISC_REG_MCU_I2_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_I2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_I2_HQOS_POS))
#define MCU_MISC_REG_MCU_S1_HQOS                                MCU_MISC_REG_MCU_S1_HQOS
#define MCU_MISC_REG_MCU_S1_HQOS_POS                            (4U)
#define MCU_MISC_REG_MCU_S1_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_S1_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_S1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_S1_HQOS_POS)
#define MCU_MISC_REG_MCU_S1_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_S1_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_S1_HQOS_POS))
#define MCU_MISC_REG_MCU_S2_HQOS                                MCU_MISC_REG_MCU_S2_HQOS
#define MCU_MISC_REG_MCU_S2_HQOS_POS                            (5U)
#define MCU_MISC_REG_MCU_S2_HQOS_LEN                            (1U)
#define MCU_MISC_REG_MCU_S2_HQOS_MSK                            (((1U<<MCU_MISC_REG_MCU_S2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_S2_HQOS_POS)
#define MCU_MISC_REG_MCU_S2_HQOS_UMSK                           (~(((1U<<MCU_MISC_REG_MCU_S2_HQOS_LEN)-1)<<MCU_MISC_REG_MCU_S2_HQOS_POS))
#define MCU_MISC_REG_MCU_IFNRA_ARB_MODE                         MCU_MISC_REG_MCU_IFNRA_ARB_MODE
#define MCU_MISC_REG_MCU_IFNRA_ARB_MODE_POS                     (16U)
#define MCU_MISC_REG_MCU_IFNRA_ARB_MODE_LEN                     (4U)
#define MCU_MISC_REG_MCU_IFNRA_ARB_MODE_MSK                     (((1U<<MCU_MISC_REG_MCU_IFNRA_ARB_MODE_LEN)-1)<<MCU_MISC_REG_MCU_IFNRA_ARB_MODE_POS)
#define MCU_MISC_REG_MCU_IFNRA_ARB_MODE_UMSK                    (~(((1U<<MCU_MISC_REG_MCU_IFNRA_ARB_MODE_LEN)-1)<<MCU_MISC_REG_MCU_IFNRA_ARB_MODE_POS))
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST                     MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_POS                 (31U)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_LEN                 (1U)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_MSK                 (((1U<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_POS)
#define MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_UMSK                (~(((1U<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_LEN)-1)<<MCU_MISC_REG_MCU_INFRA_DEC_ERR_LAST_POS))

/* 0x10 : mcu2_boot */
#define MCU_MISC_MCU2_BOOT_OFFSET                               (0x10)
#define MCU_MISC_REG_MCU2_RST_ADDR                              MCU_MISC_REG_MCU2_RST_ADDR
#define MCU_MISC_REG_MCU2_RST_ADDR_POS                          (0U)
#define MCU_MISC_REG_MCU2_RST_ADDR_LEN                          (32U)
#define MCU_MISC_REG_MCU2_RST_ADDR_MSK                          (((1U<<MCU_MISC_REG_MCU2_RST_ADDR_LEN)-1)<<MCU_MISC_REG_MCU2_RST_ADDR_POS)
#define MCU_MISC_REG_MCU2_RST_ADDR_UMSK                         (~(((1U<<MCU_MISC_REG_MCU2_RST_ADDR_LEN)-1)<<MCU_MISC_REG_MCU2_RST_ADDR_POS))

/* 0x14 : e906_rtc */
#define MCU_MISC_E906_RTC_OFFSET                                (0x14)
#define MCU_MISC_E906_RTC_DIV                                   MCU_MISC_E906_RTC_DIV
#define MCU_MISC_E906_RTC_DIV_POS                               (0U)
#define MCU_MISC_E906_RTC_DIV_LEN                               (10U)
#define MCU_MISC_E906_RTC_DIV_MSK                               (((1U<<MCU_MISC_E906_RTC_DIV_LEN)-1)<<MCU_MISC_E906_RTC_DIV_POS)
#define MCU_MISC_E906_RTC_DIV_UMSK                              (~(((1U<<MCU_MISC_E906_RTC_DIV_LEN)-1)<<MCU_MISC_E906_RTC_DIV_POS))
#define MCU_MISC_E906_RTC_RST                                   MCU_MISC_E906_RTC_RST
#define MCU_MISC_E906_RTC_RST_POS                               (30U)
#define MCU_MISC_E906_RTC_RST_LEN                               (1U)
#define MCU_MISC_E906_RTC_RST_MSK                               (((1U<<MCU_MISC_E906_RTC_RST_LEN)-1)<<MCU_MISC_E906_RTC_RST_POS)
#define MCU_MISC_E906_RTC_RST_UMSK                              (~(((1U<<MCU_MISC_E906_RTC_RST_LEN)-1)<<MCU_MISC_E906_RTC_RST_POS))
#define MCU_MISC_E906_RTC_EN                                    MCU_MISC_E906_RTC_EN
#define MCU_MISC_E906_RTC_EN_POS                                (31U)
#define MCU_MISC_E906_RTC_EN_LEN                                (1U)
#define MCU_MISC_E906_RTC_EN_MSK                                (((1U<<MCU_MISC_E906_RTC_EN_LEN)-1)<<MCU_MISC_E906_RTC_EN_POS)
#define MCU_MISC_E906_RTC_EN_UMSK                               (~(((1U<<MCU_MISC_E906_RTC_EN_LEN)-1)<<MCU_MISC_E906_RTC_EN_POS))

/* 0x100 : mcu_cfg1 */
#define MCU_MISC_MCU_CFG1_OFFSET                                (0x100)
#define MCU_MISC_REG_MCU1_DFS_REQ                               MCU_MISC_REG_MCU1_DFS_REQ
#define MCU_MISC_REG_MCU1_DFS_REQ_POS                           (0U)
#define MCU_MISC_REG_MCU1_DFS_REQ_LEN                           (1U)
#define MCU_MISC_REG_MCU1_DFS_REQ_MSK                           (((1U<<MCU_MISC_REG_MCU1_DFS_REQ_LEN)-1)<<MCU_MISC_REG_MCU1_DFS_REQ_POS)
#define MCU_MISC_REG_MCU1_DFS_REQ_UMSK                          (~(((1U<<MCU_MISC_REG_MCU1_DFS_REQ_LEN)-1)<<MCU_MISC_REG_MCU1_DFS_REQ_POS))
#define MCU_MISC_REG_MCU2_DFS_REQ                               MCU_MISC_REG_MCU2_DFS_REQ
#define MCU_MISC_REG_MCU2_DFS_REQ_POS                           (1U)
#define MCU_MISC_REG_MCU2_DFS_REQ_LEN                           (1U)
#define MCU_MISC_REG_MCU2_DFS_REQ_MSK                           (((1U<<MCU_MISC_REG_MCU2_DFS_REQ_LEN)-1)<<MCU_MISC_REG_MCU2_DFS_REQ_POS)
#define MCU_MISC_REG_MCU2_DFS_REQ_UMSK                          (~(((1U<<MCU_MISC_REG_MCU2_DFS_REQ_LEN)-1)<<MCU_MISC_REG_MCU2_DFS_REQ_POS))
#define MCU_MISC_STS_MCU1_DFS_ACK                               MCU_MISC_STS_MCU1_DFS_ACK
#define MCU_MISC_STS_MCU1_DFS_ACK_POS                           (2U)
#define MCU_MISC_STS_MCU1_DFS_ACK_LEN                           (1U)
#define MCU_MISC_STS_MCU1_DFS_ACK_MSK                           (((1U<<MCU_MISC_STS_MCU1_DFS_ACK_LEN)-1)<<MCU_MISC_STS_MCU1_DFS_ACK_POS)
#define MCU_MISC_STS_MCU1_DFS_ACK_UMSK                          (~(((1U<<MCU_MISC_STS_MCU1_DFS_ACK_LEN)-1)<<MCU_MISC_STS_MCU1_DFS_ACK_POS))
#define MCU_MISC_STS_MCU2_DFS_ACK                               MCU_MISC_STS_MCU2_DFS_ACK
#define MCU_MISC_STS_MCU2_DFS_ACK_POS                           (3U)
#define MCU_MISC_STS_MCU2_DFS_ACK_LEN                           (1U)
#define MCU_MISC_STS_MCU2_DFS_ACK_MSK                           (((1U<<MCU_MISC_STS_MCU2_DFS_ACK_LEN)-1)<<MCU_MISC_STS_MCU2_DFS_ACK_POS)
#define MCU_MISC_STS_MCU2_DFS_ACK_UMSK                          (~(((1U<<MCU_MISC_STS_MCU2_DFS_ACK_LEN)-1)<<MCU_MISC_STS_MCU2_DFS_ACK_POS))
#define MCU_MISC_REG_MCU1_SRST_EN                               MCU_MISC_REG_MCU1_SRST_EN
#define MCU_MISC_REG_MCU1_SRST_EN_POS                           (4U)
#define MCU_MISC_REG_MCU1_SRST_EN_LEN                           (2U)
#define MCU_MISC_REG_MCU1_SRST_EN_MSK                           (((1U<<MCU_MISC_REG_MCU1_SRST_EN_LEN)-1)<<MCU_MISC_REG_MCU1_SRST_EN_POS)
#define MCU_MISC_REG_MCU1_SRST_EN_UMSK                          (~(((1U<<MCU_MISC_REG_MCU1_SRST_EN_LEN)-1)<<MCU_MISC_REG_MCU1_SRST_EN_POS))
#define MCU_MISC_REG_MCU2_SRST_EN                               MCU_MISC_REG_MCU2_SRST_EN
#define MCU_MISC_REG_MCU2_SRST_EN_POS                           (6U)
#define MCU_MISC_REG_MCU2_SRST_EN_LEN                           (2U)
#define MCU_MISC_REG_MCU2_SRST_EN_MSK                           (((1U<<MCU_MISC_REG_MCU2_SRST_EN_LEN)-1)<<MCU_MISC_REG_MCU2_SRST_EN_POS)
#define MCU_MISC_REG_MCU2_SRST_EN_UMSK                          (~(((1U<<MCU_MISC_REG_MCU2_SRST_EN_LEN)-1)<<MCU_MISC_REG_MCU2_SRST_EN_POS))
#define MCU_MISC_STS_MCU2_LPMD_B                                MCU_MISC_STS_MCU2_LPMD_B
#define MCU_MISC_STS_MCU2_LPMD_B_POS                            (8U)
#define MCU_MISC_STS_MCU2_LPMD_B_LEN                            (2U)
#define MCU_MISC_STS_MCU2_LPMD_B_MSK                            (((1U<<MCU_MISC_STS_MCU2_LPMD_B_LEN)-1)<<MCU_MISC_STS_MCU2_LPMD_B_POS)
#define MCU_MISC_STS_MCU2_LPMD_B_UMSK                           (~(((1U<<MCU_MISC_STS_MCU2_LPMD_B_LEN)-1)<<MCU_MISC_STS_MCU2_LPMD_B_POS))
#define MCU_MISC_STS_MCU1_LPMD_B                                MCU_MISC_STS_MCU1_LPMD_B
#define MCU_MISC_STS_MCU1_LPMD_B_POS                            (10U)
#define MCU_MISC_STS_MCU1_LPMD_B_LEN                            (2U)
#define MCU_MISC_STS_MCU1_LPMD_B_MSK                            (((1U<<MCU_MISC_STS_MCU1_LPMD_B_LEN)-1)<<MCU_MISC_STS_MCU1_LPMD_B_POS)
#define MCU_MISC_STS_MCU1_LPMD_B_UMSK                           (~(((1U<<MCU_MISC_STS_MCU1_LPMD_B_LEN)-1)<<MCU_MISC_STS_MCU1_LPMD_B_POS))
#define MCU_MISC_STS_MCU1_PM                                    MCU_MISC_STS_MCU1_PM
#define MCU_MISC_STS_MCU1_PM_POS                                (12U)
#define MCU_MISC_STS_MCU1_PM_LEN                                (2U)
#define MCU_MISC_STS_MCU1_PM_MSK                                (((1U<<MCU_MISC_STS_MCU1_PM_LEN)-1)<<MCU_MISC_STS_MCU1_PM_POS)
#define MCU_MISC_STS_MCU1_PM_UMSK                               (~(((1U<<MCU_MISC_STS_MCU1_PM_LEN)-1)<<MCU_MISC_STS_MCU1_PM_POS))
#define MCU_MISC_STS_MCU2_PM                                    MCU_MISC_STS_MCU2_PM
#define MCU_MISC_STS_MCU2_PM_POS                                (14U)
#define MCU_MISC_STS_MCU2_PM_LEN                                (2U)
#define MCU_MISC_STS_MCU2_PM_MSK                                (((1U<<MCU_MISC_STS_MCU2_PM_LEN)-1)<<MCU_MISC_STS_MCU2_PM_POS)
#define MCU_MISC_STS_MCU2_PM_UMSK                               (~(((1U<<MCU_MISC_STS_MCU2_PM_LEN)-1)<<MCU_MISC_STS_MCU2_PM_POS))
#define MCU_MISC_MCU1_WFI_FORCE                                 MCU_MISC_MCU1_WFI_FORCE
#define MCU_MISC_MCU1_WFI_FORCE_POS                             (16U)
#define MCU_MISC_MCU1_WFI_FORCE_LEN                             (1U)
#define MCU_MISC_MCU1_WFI_FORCE_MSK                             (((1U<<MCU_MISC_MCU1_WFI_FORCE_LEN)-1)<<MCU_MISC_MCU1_WFI_FORCE_POS)
#define MCU_MISC_MCU1_WFI_FORCE_UMSK                            (~(((1U<<MCU_MISC_MCU1_WFI_FORCE_LEN)-1)<<MCU_MISC_MCU1_WFI_FORCE_POS))
#define MCU_MISC_MCU2_WFI_FORCE                                 MCU_MISC_MCU2_WFI_FORCE
#define MCU_MISC_MCU2_WFI_FORCE_POS                             (17U)
#define MCU_MISC_MCU2_WFI_FORCE_LEN                             (1U)
#define MCU_MISC_MCU2_WFI_FORCE_MSK                             (((1U<<MCU_MISC_MCU2_WFI_FORCE_LEN)-1)<<MCU_MISC_MCU2_WFI_FORCE_POS)
#define MCU_MISC_MCU2_WFI_FORCE_UMSK                            (~(((1U<<MCU_MISC_MCU2_WFI_FORCE_LEN)-1)<<MCU_MISC_MCU2_WFI_FORCE_POS))

/* 0x110 : mcu1_log1 */
#define MCU_MISC_MCU1_LOG1_OFFSET                               (0x110)
#define MCU_MISC_STS_MCU1_MCAUSE                                MCU_MISC_STS_MCU1_MCAUSE
#define MCU_MISC_STS_MCU1_MCAUSE_POS                            (0U)
#define MCU_MISC_STS_MCU1_MCAUSE_LEN                            (32U)
#define MCU_MISC_STS_MCU1_MCAUSE_MSK                            (((1U<<MCU_MISC_STS_MCU1_MCAUSE_LEN)-1)<<MCU_MISC_STS_MCU1_MCAUSE_POS)
#define MCU_MISC_STS_MCU1_MCAUSE_UMSK                           (~(((1U<<MCU_MISC_STS_MCU1_MCAUSE_LEN)-1)<<MCU_MISC_STS_MCU1_MCAUSE_POS))

/* 0x114 : mcu1_log2 */
#define MCU_MISC_MCU1_LOG2_OFFSET                               (0x114)
#define MCU_MISC_STS_MCU1_MINTSTATUS                            MCU_MISC_STS_MCU1_MINTSTATUS
#define MCU_MISC_STS_MCU1_MINTSTATUS_POS                        (0U)
#define MCU_MISC_STS_MCU1_MINTSTATUS_LEN                        (32U)
#define MCU_MISC_STS_MCU1_MINTSTATUS_MSK                        (((1U<<MCU_MISC_STS_MCU1_MINTSTATUS_LEN)-1)<<MCU_MISC_STS_MCU1_MINTSTATUS_POS)
#define MCU_MISC_STS_MCU1_MINTSTATUS_UMSK                       (~(((1U<<MCU_MISC_STS_MCU1_MINTSTATUS_LEN)-1)<<MCU_MISC_STS_MCU1_MINTSTATUS_POS))

/* 0x118 : mcu1_log3 */
#define MCU_MISC_MCU1_LOG3_OFFSET                               (0x118)
#define MCU_MISC_STS_MCU1_MSTATUS                               MCU_MISC_STS_MCU1_MSTATUS
#define MCU_MISC_STS_MCU1_MSTATUS_POS                           (0U)
#define MCU_MISC_STS_MCU1_MSTATUS_LEN                           (32U)
#define MCU_MISC_STS_MCU1_MSTATUS_MSK                           (((1U<<MCU_MISC_STS_MCU1_MSTATUS_LEN)-1)<<MCU_MISC_STS_MCU1_MSTATUS_POS)
#define MCU_MISC_STS_MCU1_MSTATUS_UMSK                          (~(((1U<<MCU_MISC_STS_MCU1_MSTATUS_LEN)-1)<<MCU_MISC_STS_MCU1_MSTATUS_POS))

/* 0x11C : mcu1_log4 */
#define MCU_MISC_MCU1_LOG4_OFFSET                               (0x11C)
#define MCU_MISC_STS_MCU1_SP                                    MCU_MISC_STS_MCU1_SP
#define MCU_MISC_STS_MCU1_SP_POS                                (0U)
#define MCU_MISC_STS_MCU1_SP_LEN                                (1U)
#define MCU_MISC_STS_MCU1_SP_MSK                                (((1U<<MCU_MISC_STS_MCU1_SP_LEN)-1)<<MCU_MISC_STS_MCU1_SP_POS)
#define MCU_MISC_STS_MCU1_SP_UMSK                               (~(((1U<<MCU_MISC_STS_MCU1_SP_LEN)-1)<<MCU_MISC_STS_MCU1_SP_POS))
#define MCU_MISC_STS_MCU1_PC                                    MCU_MISC_STS_MCU1_PC
#define MCU_MISC_STS_MCU1_PC_POS                                (1U)
#define MCU_MISC_STS_MCU1_PC_LEN                                (31U)
#define MCU_MISC_STS_MCU1_PC_MSK                                (((1U<<MCU_MISC_STS_MCU1_PC_LEN)-1)<<MCU_MISC_STS_MCU1_PC_POS)
#define MCU_MISC_STS_MCU1_PC_UMSK                               (~(((1U<<MCU_MISC_STS_MCU1_PC_LEN)-1)<<MCU_MISC_STS_MCU1_PC_POS))

/* 0x150 : mcu2_log1 */
#define MCU_MISC_MCU2_LOG1_OFFSET                               (0x150)
#define MCU_MISC_STS_MCU2_MCAUSE                                MCU_MISC_STS_MCU2_MCAUSE
#define MCU_MISC_STS_MCU2_MCAUSE_POS                            (0U)
#define MCU_MISC_STS_MCU2_MCAUSE_LEN                            (32U)
#define MCU_MISC_STS_MCU2_MCAUSE_MSK                            (((1U<<MCU_MISC_STS_MCU2_MCAUSE_LEN)-1)<<MCU_MISC_STS_MCU2_MCAUSE_POS)
#define MCU_MISC_STS_MCU2_MCAUSE_UMSK                           (~(((1U<<MCU_MISC_STS_MCU2_MCAUSE_LEN)-1)<<MCU_MISC_STS_MCU2_MCAUSE_POS))

/* 0x154 : mcu2_log2 */
#define MCU_MISC_MCU2_LOG2_OFFSET                               (0x154)
#define MCU_MISC_STS_MCU2_MINTSTATUS                            MCU_MISC_STS_MCU2_MINTSTATUS
#define MCU_MISC_STS_MCU2_MINTSTATUS_POS                        (0U)
#define MCU_MISC_STS_MCU2_MINTSTATUS_LEN                        (32U)
#define MCU_MISC_STS_MCU2_MINTSTATUS_MSK                        (((1U<<MCU_MISC_STS_MCU2_MINTSTATUS_LEN)-1)<<MCU_MISC_STS_MCU2_MINTSTATUS_POS)
#define MCU_MISC_STS_MCU2_MINTSTATUS_UMSK                       (~(((1U<<MCU_MISC_STS_MCU2_MINTSTATUS_LEN)-1)<<MCU_MISC_STS_MCU2_MINTSTATUS_POS))

/* 0x158 : mcu2_log3 */
#define MCU_MISC_MCU2_LOG3_OFFSET                               (0x158)
#define MCU_MISC_STS_MCU2_MSTATUS                               MCU_MISC_STS_MCU2_MSTATUS
#define MCU_MISC_STS_MCU2_MSTATUS_POS                           (0U)
#define MCU_MISC_STS_MCU2_MSTATUS_LEN                           (32U)
#define MCU_MISC_STS_MCU2_MSTATUS_MSK                           (((1U<<MCU_MISC_STS_MCU2_MSTATUS_LEN)-1)<<MCU_MISC_STS_MCU2_MSTATUS_POS)
#define MCU_MISC_STS_MCU2_MSTATUS_UMSK                          (~(((1U<<MCU_MISC_STS_MCU2_MSTATUS_LEN)-1)<<MCU_MISC_STS_MCU2_MSTATUS_POS))

/* 0x15C : mcu2_log4 */
#define MCU_MISC_MCU2_LOG4_OFFSET                               (0x15C)
#define MCU_MISC_STS_MCU2_SP                                    MCU_MISC_STS_MCU2_SP
#define MCU_MISC_STS_MCU2_SP_POS                                (0U)
#define MCU_MISC_STS_MCU2_SP_LEN                                (1U)
#define MCU_MISC_STS_MCU2_SP_MSK                                (((1U<<MCU_MISC_STS_MCU2_SP_LEN)-1)<<MCU_MISC_STS_MCU2_SP_POS)
#define MCU_MISC_STS_MCU2_SP_UMSK                               (~(((1U<<MCU_MISC_STS_MCU2_SP_LEN)-1)<<MCU_MISC_STS_MCU2_SP_POS))
#define MCU_MISC_STS_MCU2_PC                                    MCU_MISC_STS_MCU2_PC
#define MCU_MISC_STS_MCU2_PC_POS                                (1U)
#define MCU_MISC_STS_MCU2_PC_LEN                                (31U)
#define MCU_MISC_STS_MCU2_PC_MSK                                (((1U<<MCU_MISC_STS_MCU2_PC_LEN)-1)<<MCU_MISC_STS_MCU2_PC_POS)
#define MCU_MISC_STS_MCU2_PC_UMSK                               (~(((1U<<MCU_MISC_STS_MCU2_PC_LEN)-1)<<MCU_MISC_STS_MCU2_PC_POS))

/* 0x208 : irom1_misr_dataout_0 */
#define MCU_MISC_IROM1_MISR_DATAOUT_0_OFFSET                    (0x208)
#define MCU_MISC_IROM1_MISR_DATAOUT_0                           MCU_MISC_IROM1_MISR_DATAOUT_0
#define MCU_MISC_IROM1_MISR_DATAOUT_0_POS                       (0U)
#define MCU_MISC_IROM1_MISR_DATAOUT_0_LEN                       (32U)
#define MCU_MISC_IROM1_MISR_DATAOUT_0_MSK                       (((1U<<MCU_MISC_IROM1_MISR_DATAOUT_0_LEN)-1)<<MCU_MISC_IROM1_MISR_DATAOUT_0_POS)
#define MCU_MISC_IROM1_MISR_DATAOUT_0_UMSK                      (~(((1U<<MCU_MISC_IROM1_MISR_DATAOUT_0_LEN)-1)<<MCU_MISC_IROM1_MISR_DATAOUT_0_POS))

/* 0x20C : irom1_misr_dataout_1 */
#define MCU_MISC_IROM1_MISR_DATAOUT_1_OFFSET                    (0x20C)
#define MCU_MISC_IROM1_MISR_DATAOUT_1                           MCU_MISC_IROM1_MISR_DATAOUT_1
#define MCU_MISC_IROM1_MISR_DATAOUT_1_POS                       (0U)
#define MCU_MISC_IROM1_MISR_DATAOUT_1_LEN                       (32U)
#define MCU_MISC_IROM1_MISR_DATAOUT_1_MSK                       (((1U<<MCU_MISC_IROM1_MISR_DATAOUT_1_LEN)-1)<<MCU_MISC_IROM1_MISR_DATAOUT_1_POS)
#define MCU_MISC_IROM1_MISR_DATAOUT_1_UMSK                      (~(((1U<<MCU_MISC_IROM1_MISR_DATAOUT_1_LEN)-1)<<MCU_MISC_IROM1_MISR_DATAOUT_1_POS))


struct  mcu_misc_reg {
    /* 0x0 : l1c_config */
    union {
        struct {
            uint32_t reserved_0_3                   :  4; /* [ 3: 0],       rsvd,        0x0 */
            uint32_t patch_d_en                     :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t patch_option                   :  1; /* [    6],        r/w,        0x0 */
            uint32_t pram_clk_sel                   :  1; /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_11                  :  4; /* [11: 8],       rsvd,        0x0 */
            uint32_t irom_2t_access                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t sts_mcu_infra_timeout          :  6; /* [21:16],          r,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_mcu_infra_timeout_en       :  6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_config;

    /* 0x4 : bus_error_clr_sts */
    union {
        struct {
            uint32_t reg_mcu_infra_timeout_clr      :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_mcu_infra_dec_err_clr      :  1; /* [    1],        r/w,        0x0 */
            uint32_t sts_mcu_infra_dec_err_int      :  1; /* [    2],          r,        0x0 */
            uint32_t sts_mcu_infra_dec_err_write    :  1; /* [    3],          r,        0x0 */
            uint32_t sts_mcu_infra_dec_err_src      :  3; /* [ 6: 4],          r,        0x0 */
            uint32_t reserved_7_31                  : 25; /* [31: 7],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } bus_error_clr_sts;

    /* 0x8 : bus_error_addr */
    union {
        struct {
            uint32_t sts_mcu_infra_dec_err_addr     : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } bus_error_addr;

    /* 0xC : bus_cfg */
    union {
        struct {
            uint32_t reg_mcu_d1_hqos                :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_mcu_d2_hqos                :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_mcu_i1_hqos                :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_mcu_i2_hqos                :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_mcu_s1_hqos                :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_mcu_s2_hqos                :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_mcu_ifnra_arb_mode         :  4; /* [19:16],        r/w,        0x0 */
            uint32_t reserved_20_30                 : 11; /* [30:20],       rsvd,        0x0 */
            uint32_t reg_mcu_infra_dec_err_last     :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } bus_cfg;

    /* 0x10 : mcu2_boot */
    union {
        struct {
            uint32_t reg_mcu2_rst_addr              : 32; /* [31: 0],        r/w, 0x21000000 */
        }BF;
        uint32_t WORD;
    } mcu2_boot;

    /* 0x14 : e906_rtc */
    union {
        struct {
            uint32_t e906_rtc_div                   : 10; /* [ 9: 0],        r/w,        0xa */
            uint32_t reserved_10_29                 : 20; /* [29:10],       rsvd,        0x0 */
            uint32_t e906_rtc_rst                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t e906_rtc_en                    :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } e906_rtc;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[232];

    /* 0x100 : mcu_cfg1 */
    union {
        struct {
            uint32_t reg_mcu1_dfs_req               :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_mcu2_dfs_req               :  1; /* [    1],        r/w,        0x0 */
            uint32_t sts_mcu1_dfs_ack               :  1; /* [    2],          r,        0x0 */
            uint32_t sts_mcu2_dfs_ack               :  1; /* [    3],          r,        0x0 */
            uint32_t reg_mcu1_srst_en               :  2; /* [ 5: 4],        r/w,        0x3 */
            uint32_t reg_mcu2_srst_en               :  2; /* [ 7: 6],        r/w,        0x3 */
            uint32_t sts_mcu2_lpmd_b                :  2; /* [ 9: 8],          r,        0x0 */
            uint32_t sts_mcu1_lpmd_b                :  2; /* [11:10],          r,        0x0 */
            uint32_t sts_mcu1_pm                    :  2; /* [13:12],          r,        0x0 */
            uint32_t sts_mcu2_pm                    :  2; /* [15:14],          r,        0x0 */
            uint32_t MCU1_WFI_FORCE                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t MCU2_WFI_FORCE                 :  1; /* [   17],        r/w,        0x0 */
            uint32_t reserved_18_31                 : 14; /* [31:18],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu_cfg1;

    /* 0x104  reserved */
    uint8_t RESERVED0x104[12];

    /* 0x110 : mcu1_log1 */
    union {
        struct {
            uint32_t sts_mcu1_mcause                : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu1_log1;

    /* 0x114 : mcu1_log2 */
    union {
        struct {
            uint32_t sts_mcu1_mintstatus            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu1_log2;

    /* 0x118 : mcu1_log3 */
    union {
        struct {
            uint32_t sts_mcu1_mstatus               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu1_log3;

    /* 0x11C : mcu1_log4 */
    union {
        struct {
            uint32_t sts_mcu1_sp                    :  1; /* [    0],          r,        0x0 */
            uint32_t sts_mcu1_pc                    : 31; /* [31: 1],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu1_log4;

    /* 0x120  reserved */
    uint8_t RESERVED0x120[48];

    /* 0x150 : mcu2_log1 */
    union {
        struct {
            uint32_t sts_mcu2_mcause                : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu2_log1;

    /* 0x154 : mcu2_log2 */
    union {
        struct {
            uint32_t sts_mcu2_mintstatus            : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu2_log2;

    /* 0x158 : mcu2_log3 */
    union {
        struct {
            uint32_t sts_mcu2_mstatus               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu2_log3;

    /* 0x15C : mcu2_log4 */
    union {
        struct {
            uint32_t sts_mcu2_sp                    :  1; /* [    0],          r,        0x0 */
            uint32_t sts_mcu2_pc                    : 31; /* [31: 1],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mcu2_log4;

    /* 0x160  reserved */
    uint8_t RESERVED0x160[168];

    /* 0x208 : irom1_misr_dataout_0 */
    union {
        struct {
            uint32_t irom1_misr_dataout_0           : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } irom1_misr_dataout_0;

    /* 0x20C : irom1_misr_dataout_1 */
    union {
        struct {
            uint32_t irom1_misr_dataout_1           : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } irom1_misr_dataout_1;

};

typedef volatile struct mcu_misc_reg mcu_misc_reg_t;


#endif  /* __MCU_MISC_REG_H__ */
