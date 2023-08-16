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
#ifndef  __MM_GLB_REG_H__
#define  __MM_GLB_REG_H__

#include "bl808.h"

/* 0x0 : mm_clk_ctrl_cpu */
#define MM_GLB_MM_CLK_CTRL_CPU_OFFSET                           (0x0)
#define MM_GLB_REG_PLL_EN                                       MM_GLB_REG_PLL_EN
#define MM_GLB_REG_PLL_EN_POS                                   (0U)
#define MM_GLB_REG_PLL_EN_LEN                                   (1U)
#define MM_GLB_REG_PLL_EN_MSK                                   (((1U<<MM_GLB_REG_PLL_EN_LEN)-1)<<MM_GLB_REG_PLL_EN_POS)
#define MM_GLB_REG_PLL_EN_UMSK                                  (~(((1U<<MM_GLB_REG_PLL_EN_LEN)-1)<<MM_GLB_REG_PLL_EN_POS))
#define MM_GLB_REG_CPU_CLK_EN                                   MM_GLB_REG_CPU_CLK_EN
#define MM_GLB_REG_CPU_CLK_EN_POS                               (1U)
#define MM_GLB_REG_CPU_CLK_EN_LEN                               (1U)
#define MM_GLB_REG_CPU_CLK_EN_MSK                               (((1U<<MM_GLB_REG_CPU_CLK_EN_LEN)-1)<<MM_GLB_REG_CPU_CLK_EN_POS)
#define MM_GLB_REG_CPU_CLK_EN_UMSK                              (~(((1U<<MM_GLB_REG_CPU_CLK_EN_LEN)-1)<<MM_GLB_REG_CPU_CLK_EN_POS))
#define MM_GLB_REG_BCLK_EN                                      MM_GLB_REG_BCLK_EN
#define MM_GLB_REG_BCLK_EN_POS                                  (2U)
#define MM_GLB_REG_BCLK_EN_LEN                                  (1U)
#define MM_GLB_REG_BCLK_EN_MSK                                  (((1U<<MM_GLB_REG_BCLK_EN_LEN)-1)<<MM_GLB_REG_BCLK_EN_POS)
#define MM_GLB_REG_BCLK_EN_UMSK                                 (~(((1U<<MM_GLB_REG_BCLK_EN_LEN)-1)<<MM_GLB_REG_BCLK_EN_POS))
#define MM_GLB_HBN_UART_CLK_SEL                                 MM_GLB_HBN_UART_CLK_SEL
#define MM_GLB_HBN_UART_CLK_SEL_POS                             (5U)
#define MM_GLB_HBN_UART_CLK_SEL_LEN                             (1U)
#define MM_GLB_HBN_UART_CLK_SEL_MSK                             (((1U<<MM_GLB_HBN_UART_CLK_SEL_LEN)-1)<<MM_GLB_HBN_UART_CLK_SEL_POS)
#define MM_GLB_HBN_UART_CLK_SEL_UMSK                            (~(((1U<<MM_GLB_HBN_UART_CLK_SEL_LEN)-1)<<MM_GLB_HBN_UART_CLK_SEL_POS))
#define MM_GLB_REG_SPI_CLK_SEL                                  MM_GLB_REG_SPI_CLK_SEL
#define MM_GLB_REG_SPI_CLK_SEL_POS                              (7U)
#define MM_GLB_REG_SPI_CLK_SEL_LEN                              (1U)
#define MM_GLB_REG_SPI_CLK_SEL_MSK                              (((1U << MM_GLB_REG_SPI_CLK_SEL_LEN) - 1) << MM_GLB_REG_SPI_CLK_SEL_POS)
#define MM_GLB_REG_SPI_CLK_SEL_UMSK                             (~(((1U << MM_GLB_REG_SPI_CLK_SEL_LEN) - 1) << MM_GLB_REG_SPI_CLK_SEL_POS))
#define MM_GLB_REG_CPU_CLK_SEL                                  MM_GLB_REG_CPU_CLK_SEL
#define MM_GLB_REG_CPU_CLK_SEL_POS                              (8U)
#define MM_GLB_REG_CPU_CLK_SEL_LEN                              (2U)
#define MM_GLB_REG_CPU_CLK_SEL_MSK                              (((1U<<MM_GLB_REG_CPU_CLK_SEL_LEN)-1)<<MM_GLB_REG_CPU_CLK_SEL_POS)
#define MM_GLB_REG_CPU_CLK_SEL_UMSK                             (~(((1U<<MM_GLB_REG_CPU_CLK_SEL_LEN)-1)<<MM_GLB_REG_CPU_CLK_SEL_POS))
#define MM_GLB_HBN_ROOT_CLK_SEL                                 MM_GLB_HBN_ROOT_CLK_SEL
#define MM_GLB_HBN_ROOT_CLK_SEL_POS                             (10U)
#define MM_GLB_HBN_ROOT_CLK_SEL_LEN                             (2U)
#define MM_GLB_HBN_ROOT_CLK_SEL_MSK                             (((1U<<MM_GLB_HBN_ROOT_CLK_SEL_LEN)-1)<<MM_GLB_HBN_ROOT_CLK_SEL_POS)
#define MM_GLB_HBN_ROOT_CLK_SEL_UMSK                            (~(((1U<<MM_GLB_HBN_ROOT_CLK_SEL_LEN)-1)<<MM_GLB_HBN_ROOT_CLK_SEL_POS))
#define MM_GLB_REG_MMCPU0_CLK_EN                                MM_GLB_REG_MMCPU0_CLK_EN
#define MM_GLB_REG_MMCPU0_CLK_EN_POS                            (12U)
#define MM_GLB_REG_MMCPU0_CLK_EN_LEN                            (1U)
#define MM_GLB_REG_MMCPU0_CLK_EN_MSK                            (((1U<<MM_GLB_REG_MMCPU0_CLK_EN_LEN)-1)<<MM_GLB_REG_MMCPU0_CLK_EN_POS)
#define MM_GLB_REG_MMCPU0_CLK_EN_UMSK                           (~(((1U<<MM_GLB_REG_MMCPU0_CLK_EN_LEN)-1)<<MM_GLB_REG_MMCPU0_CLK_EN_POS))
#define MM_GLB_REG_MMCPU1_CLK_EN                                MM_GLB_REG_MMCPU1_CLK_EN
#define MM_GLB_REG_MMCPU1_CLK_EN_POS                            (13U)
#define MM_GLB_REG_MMCPU1_CLK_EN_LEN                            (1U)
#define MM_GLB_REG_MMCPU1_CLK_EN_MSK                            (((1U<<MM_GLB_REG_MMCPU1_CLK_EN_LEN)-1)<<MM_GLB_REG_MMCPU1_CLK_EN_POS)
#define MM_GLB_REG_MMCPU1_CLK_EN_UMSK                           (~(((1U<<MM_GLB_REG_MMCPU1_CLK_EN_LEN)-1)<<MM_GLB_REG_MMCPU1_CLK_EN_POS))
#define MM_GLB_CPU_CLK_SW_STATE                                 MM_GLB_CPU_CLK_SW_STATE
#define MM_GLB_CPU_CLK_SW_STATE_POS                             (24U)
#define MM_GLB_CPU_CLK_SW_STATE_LEN                             (3U)
#define MM_GLB_CPU_CLK_SW_STATE_MSK                             (((1U<<MM_GLB_CPU_CLK_SW_STATE_LEN)-1)<<MM_GLB_CPU_CLK_SW_STATE_POS)
#define MM_GLB_CPU_CLK_SW_STATE_UMSK                            (~(((1U<<MM_GLB_CPU_CLK_SW_STATE_LEN)-1)<<MM_GLB_CPU_CLK_SW_STATE_POS))

/* 0x4 : mm_clk_cpu */
#define MM_GLB_MM_CLK_CPU_OFFSET                                (0x4)
#define MM_GLB_REG_CPU_CLK_DIV                                  MM_GLB_REG_CPU_CLK_DIV
#define MM_GLB_REG_CPU_CLK_DIV_POS                              (0U)
#define MM_GLB_REG_CPU_CLK_DIV_LEN                              (8U)
#define MM_GLB_REG_CPU_CLK_DIV_MSK                              (((1U<<MM_GLB_REG_CPU_CLK_DIV_LEN)-1)<<MM_GLB_REG_CPU_CLK_DIV_POS)
#define MM_GLB_REG_CPU_CLK_DIV_UMSK                             (~(((1U<<MM_GLB_REG_CPU_CLK_DIV_LEN)-1)<<MM_GLB_REG_CPU_CLK_DIV_POS))
#define MM_GLB_REG_CNN_CLK_DIV_EN                               MM_GLB_REG_CNN_CLK_DIV_EN
#define MM_GLB_REG_CNN_CLK_DIV_EN_POS                           (8U)
#define MM_GLB_REG_CNN_CLK_DIV_EN_LEN                           (1U)
#define MM_GLB_REG_CNN_CLK_DIV_EN_MSK                           (((1U<<MM_GLB_REG_CNN_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_CNN_CLK_DIV_EN_POS)
#define MM_GLB_REG_CNN_CLK_DIV_EN_UMSK                          (~(((1U<<MM_GLB_REG_CNN_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_CNN_CLK_DIV_EN_POS))
#define MM_GLB_REG_CNN_CLK_SEL                                  MM_GLB_REG_CNN_CLK_SEL
#define MM_GLB_REG_CNN_CLK_SEL_POS                              (9U)
#define MM_GLB_REG_CNN_CLK_SEL_LEN                              (2U)
#define MM_GLB_REG_CNN_CLK_SEL_MSK                              (((1U<<MM_GLB_REG_CNN_CLK_SEL_LEN)-1)<<MM_GLB_REG_CNN_CLK_SEL_POS)
#define MM_GLB_REG_CNN_CLK_SEL_UMSK                             (~(((1U<<MM_GLB_REG_CNN_CLK_SEL_LEN)-1)<<MM_GLB_REG_CNN_CLK_SEL_POS))
#define MM_GLB_REG_CNN_CLK_DIV                                  MM_GLB_REG_CNN_CLK_DIV
#define MM_GLB_REG_CNN_CLK_DIV_POS                              (12U)
#define MM_GLB_REG_CNN_CLK_DIV_LEN                              (3U)
#define MM_GLB_REG_CNN_CLK_DIV_MSK                              (((1U<<MM_GLB_REG_CNN_CLK_DIV_LEN)-1)<<MM_GLB_REG_CNN_CLK_DIV_POS)
#define MM_GLB_REG_CNN_CLK_DIV_UMSK                             (~(((1U<<MM_GLB_REG_CNN_CLK_DIV_LEN)-1)<<MM_GLB_REG_CNN_CLK_DIV_POS))
#define MM_GLB_REG_BCLK2X_DIV                                   MM_GLB_REG_BCLK2X_DIV
#define MM_GLB_REG_BCLK2X_DIV_POS                               (16U)
#define MM_GLB_REG_BCLK2X_DIV_LEN                               (8U)
#define MM_GLB_REG_BCLK2X_DIV_MSK                               (((1U<<MM_GLB_REG_BCLK2X_DIV_LEN)-1)<<MM_GLB_REG_BCLK2X_DIV_POS)
#define MM_GLB_REG_BCLK2X_DIV_UMSK                              (~(((1U<<MM_GLB_REG_BCLK2X_DIV_LEN)-1)<<MM_GLB_REG_BCLK2X_DIV_POS))
#define MM_GLB_REG_BCLK1X_DIV                                   MM_GLB_REG_BCLK1X_DIV
#define MM_GLB_REG_BCLK1X_DIV_POS                               (24U)
#define MM_GLB_REG_BCLK1X_DIV_LEN                               (8U)
#define MM_GLB_REG_BCLK1X_DIV_MSK                               (((1U<<MM_GLB_REG_BCLK1X_DIV_LEN)-1)<<MM_GLB_REG_BCLK1X_DIV_POS)
#define MM_GLB_REG_BCLK1X_DIV_UMSK                              (~(((1U<<MM_GLB_REG_BCLK1X_DIV_LEN)-1)<<MM_GLB_REG_BCLK1X_DIV_POS))

/* 0x8 : mm_clk_ctrl_isp_sub_sys */
#define MM_GLB_MM_CLK_CTRL_ISP_SUB_SYS_OFFSET                   (0x8)
#define MM_GLB_REG_ISP_CLK_DIV_EN                               MM_GLB_REG_ISP_CLK_DIV_EN
#define MM_GLB_REG_ISP_CLK_DIV_EN_POS                           (0U)
#define MM_GLB_REG_ISP_CLK_DIV_EN_LEN                           (1U)
#define MM_GLB_REG_ISP_CLK_DIV_EN_MSK                           (((1U<<MM_GLB_REG_ISP_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_ISP_CLK_DIV_EN_POS)
#define MM_GLB_REG_ISP_CLK_DIV_EN_UMSK                          (~(((1U<<MM_GLB_REG_ISP_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_ISP_CLK_DIV_EN_POS))
#define MM_GLB_REG_ISP_CLK_SEL                                  MM_GLB_REG_ISP_CLK_SEL
#define MM_GLB_REG_ISP_CLK_SEL_POS                              (1U)
#define MM_GLB_REG_ISP_CLK_SEL_LEN                              (2U)
#define MM_GLB_REG_ISP_CLK_SEL_MSK                              (((1U<<MM_GLB_REG_ISP_CLK_SEL_LEN)-1)<<MM_GLB_REG_ISP_CLK_SEL_POS)
#define MM_GLB_REG_ISP_CLK_SEL_UMSK                             (~(((1U<<MM_GLB_REG_ISP_CLK_SEL_LEN)-1)<<MM_GLB_REG_ISP_CLK_SEL_POS))
#define MM_GLB_REG_ISP_CLK_DIV                                  MM_GLB_REG_ISP_CLK_DIV
#define MM_GLB_REG_ISP_CLK_DIV_POS                              (8U)
#define MM_GLB_REG_ISP_CLK_DIV_LEN                              (8U)
#define MM_GLB_REG_ISP_CLK_DIV_MSK                              (((1U<<MM_GLB_REG_ISP_CLK_DIV_LEN)-1)<<MM_GLB_REG_ISP_CLK_DIV_POS)
#define MM_GLB_REG_ISP_CLK_DIV_UMSK                             (~(((1U<<MM_GLB_REG_ISP_CLK_DIV_LEN)-1)<<MM_GLB_REG_ISP_CLK_DIV_POS))
#define MM_GLB_REG_DP_CLK_DIV_EN                                MM_GLB_REG_DP_CLK_DIV_EN
#define MM_GLB_REG_DP_CLK_DIV_EN_POS                            (16U)
#define MM_GLB_REG_DP_CLK_DIV_EN_LEN                            (1U)
#define MM_GLB_REG_DP_CLK_DIV_EN_MSK                            (((1U<<MM_GLB_REG_DP_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_DP_CLK_DIV_EN_POS)
#define MM_GLB_REG_DP_CLK_DIV_EN_UMSK                           (~(((1U<<MM_GLB_REG_DP_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_DP_CLK_DIV_EN_POS))
#define MM_GLB_REG_DP_CLK_SEL                                   MM_GLB_REG_DP_CLK_SEL
#define MM_GLB_REG_DP_CLK_SEL_POS                               (17U)
#define MM_GLB_REG_DP_CLK_SEL_LEN                               (2U)
#define MM_GLB_REG_DP_CLK_SEL_MSK                               (((1U<<MM_GLB_REG_DP_CLK_SEL_LEN)-1)<<MM_GLB_REG_DP_CLK_SEL_POS)
#define MM_GLB_REG_DP_CLK_SEL_UMSK                              (~(((1U<<MM_GLB_REG_DP_CLK_SEL_LEN)-1)<<MM_GLB_REG_DP_CLK_SEL_POS))
#define MM_GLB_REG_DP_CLK_DIV                                   MM_GLB_REG_DP_CLK_DIV
#define MM_GLB_REG_DP_CLK_DIV_POS                               (20U)
#define MM_GLB_REG_DP_CLK_DIV_LEN                               (4U)
#define MM_GLB_REG_DP_CLK_DIV_MSK                               (((1U<<MM_GLB_REG_DP_CLK_DIV_LEN)-1)<<MM_GLB_REG_DP_CLK_DIV_POS)
#define MM_GLB_REG_DP_CLK_DIV_UMSK                              (~(((1U<<MM_GLB_REG_DP_CLK_DIV_LEN)-1)<<MM_GLB_REG_DP_CLK_DIV_POS))
#define MM_GLB_REG_SNSR_CLK_DIV_EN                              MM_GLB_REG_SNSR_CLK_DIV_EN
#define MM_GLB_REG_SNSR_CLK_DIV_EN_POS                          (24U)
#define MM_GLB_REG_SNSR_CLK_DIV_EN_LEN                          (1U)
#define MM_GLB_REG_SNSR_CLK_DIV_EN_MSK                          (((1U<<MM_GLB_REG_SNSR_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_SNSR_CLK_DIV_EN_POS)
#define MM_GLB_REG_SNSR_CLK_DIV_EN_UMSK                         (~(((1U<<MM_GLB_REG_SNSR_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_SNSR_CLK_DIV_EN_POS))
#define MM_GLB_REG_SNSR_CLK_DIV                                 MM_GLB_REG_SNSR_CLK_DIV
#define MM_GLB_REG_SNSR_CLK_DIV_POS                             (28U)
#define MM_GLB_REG_SNSR_CLK_DIV_LEN                             (4U)
#define MM_GLB_REG_SNSR_CLK_DIV_MSK                             (((1U<<MM_GLB_REG_SNSR_CLK_DIV_LEN)-1)<<MM_GLB_REG_SNSR_CLK_DIV_POS)
#define MM_GLB_REG_SNSR_CLK_DIV_UMSK                            (~(((1U<<MM_GLB_REG_SNSR_CLK_DIV_LEN)-1)<<MM_GLB_REG_SNSR_CLK_DIV_POS))

/* 0x10 : mm_clk_ctrl_peri */
#define MM_GLB_MM_CLK_CTRL_PERI_OFFSET                          (0x10)
#define MM_GLB_REG_I2C0_CLK_DIV                                 MM_GLB_REG_I2C0_CLK_DIV
#define MM_GLB_REG_I2C0_CLK_DIV_POS                             (0U)
#define MM_GLB_REG_I2C0_CLK_DIV_LEN                             (8U)
#define MM_GLB_REG_I2C0_CLK_DIV_MSK                             (((1U<<MM_GLB_REG_I2C0_CLK_DIV_LEN)-1)<<MM_GLB_REG_I2C0_CLK_DIV_POS)
#define MM_GLB_REG_I2C0_CLK_DIV_UMSK                            (~(((1U<<MM_GLB_REG_I2C0_CLK_DIV_LEN)-1)<<MM_GLB_REG_I2C0_CLK_DIV_POS))
#define MM_GLB_REG_I2C0_CLK_DIV_EN                              MM_GLB_REG_I2C0_CLK_DIV_EN
#define MM_GLB_REG_I2C0_CLK_DIV_EN_POS                          (8U)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_LEN                          (1U)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_MSK                          (((1U<<MM_GLB_REG_I2C0_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_I2C0_CLK_DIV_EN_POS)
#define MM_GLB_REG_I2C0_CLK_DIV_EN_UMSK                         (~(((1U<<MM_GLB_REG_I2C0_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_I2C0_CLK_DIV_EN_POS))
#define MM_GLB_REG_I2C0_CLK_EN                                  MM_GLB_REG_I2C0_CLK_EN
#define MM_GLB_REG_I2C0_CLK_EN_POS                              (9U)
#define MM_GLB_REG_I2C0_CLK_EN_LEN                              (1U)
#define MM_GLB_REG_I2C0_CLK_EN_MSK                              (((1U<<MM_GLB_REG_I2C0_CLK_EN_LEN)-1)<<MM_GLB_REG_I2C0_CLK_EN_POS)
#define MM_GLB_REG_I2C0_CLK_EN_UMSK                             (~(((1U<<MM_GLB_REG_I2C0_CLK_EN_LEN)-1)<<MM_GLB_REG_I2C0_CLK_EN_POS))
#define MM_GLB_REG_UART0_CLK_DIV_EN                             MM_GLB_REG_UART0_CLK_DIV_EN
#define MM_GLB_REG_UART0_CLK_DIV_EN_POS                         (16U)
#define MM_GLB_REG_UART0_CLK_DIV_EN_LEN                         (1U)
#define MM_GLB_REG_UART0_CLK_DIV_EN_MSK                         (((1U<<MM_GLB_REG_UART0_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_UART0_CLK_DIV_EN_POS)
#define MM_GLB_REG_UART0_CLK_DIV_EN_UMSK                        (~(((1U<<MM_GLB_REG_UART0_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_UART0_CLK_DIV_EN_POS))
#define MM_GLB_REG_UART0_CLK_DIV                                MM_GLB_REG_UART0_CLK_DIV
#define MM_GLB_REG_UART0_CLK_DIV_POS                            (17U)
#define MM_GLB_REG_UART0_CLK_DIV_LEN                            (3U)
#define MM_GLB_REG_UART0_CLK_DIV_MSK                            (((1U<<MM_GLB_REG_UART0_CLK_DIV_LEN)-1)<<MM_GLB_REG_UART0_CLK_DIV_POS)
#define MM_GLB_REG_UART0_CLK_DIV_UMSK                           (~(((1U<<MM_GLB_REG_UART0_CLK_DIV_LEN)-1)<<MM_GLB_REG_UART0_CLK_DIV_POS))
#define MM_GLB_REG_SPI_CLK_DIV_EN                               MM_GLB_REG_SPI_CLK_DIV_EN
#define MM_GLB_REG_SPI_CLK_DIV_EN_POS                           (23U)
#define MM_GLB_REG_SPI_CLK_DIV_EN_LEN                           (1U)
#define MM_GLB_REG_SPI_CLK_DIV_EN_MSK                           (((1U<<MM_GLB_REG_SPI_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_SPI_CLK_DIV_EN_POS)
#define MM_GLB_REG_SPI_CLK_DIV_EN_UMSK                          (~(((1U<<MM_GLB_REG_SPI_CLK_DIV_EN_LEN)-1)<<MM_GLB_REG_SPI_CLK_DIV_EN_POS))
#define MM_GLB_REG_SPI_CLK_DIV                                  MM_GLB_REG_SPI_CLK_DIV
#define MM_GLB_REG_SPI_CLK_DIV_POS                              (24U)
#define MM_GLB_REG_SPI_CLK_DIV_LEN                              (8U)
#define MM_GLB_REG_SPI_CLK_DIV_MSK                              (((1U<<MM_GLB_REG_SPI_CLK_DIV_LEN)-1)<<MM_GLB_REG_SPI_CLK_DIV_POS)
#define MM_GLB_REG_SPI_CLK_DIV_UMSK                             (~(((1U<<MM_GLB_REG_SPI_CLK_DIV_LEN)-1)<<MM_GLB_REG_SPI_CLK_DIV_POS))

/* 0x14 : mm_clk_ctrl_peri2 */
#define MM_GLB_MM_CLK_CTRL_PERI2_OFFSET                         (0x14)
#define MM_GLB_REG_I2S0_CLK_DIV                                 MM_GLB_REG_I2S0_CLK_DIV
#define MM_GLB_REG_I2S0_CLK_DIV_POS                             (0U)
#define MM_GLB_REG_I2S0_CLK_DIV_LEN                             (6U)
#define MM_GLB_REG_I2S0_CLK_DIV_MSK                             (((1U<<MM_GLB_REG_I2S0_CLK_DIV_LEN)-1)<<MM_GLB_REG_I2S0_CLK_DIV_POS)
#define MM_GLB_REG_I2S0_CLK_DIV_UMSK                            (~(((1U<<MM_GLB_REG_I2S0_CLK_DIV_LEN)-1)<<MM_GLB_REG_I2S0_CLK_DIV_POS))
#define MM_GLB_REG_I2S0_REF_CLK_OE                              MM_GLB_REG_I2S0_REF_CLK_OE
#define MM_GLB_REG_I2S0_REF_CLK_OE_POS                          (6U)
#define MM_GLB_REG_I2S0_REF_CLK_OE_LEN                          (1U)
#define MM_GLB_REG_I2S0_REF_CLK_OE_MSK                          (((1U<<MM_GLB_REG_I2S0_REF_CLK_OE_LEN)-1)<<MM_GLB_REG_I2S0_REF_CLK_OE_POS)
#define MM_GLB_REG_I2S0_REF_CLK_OE_UMSK                         (~(((1U<<MM_GLB_REG_I2S0_REF_CLK_OE_LEN)-1)<<MM_GLB_REG_I2S0_REF_CLK_OE_POS))
#define MM_GLB_REG_I2S0_CLK_EN                                  MM_GLB_REG_I2S0_CLK_EN
#define MM_GLB_REG_I2S0_CLK_EN_POS                              (7U)
#define MM_GLB_REG_I2S0_CLK_EN_LEN                              (1U)
#define MM_GLB_REG_I2S0_CLK_EN_MSK                              (((1U<<MM_GLB_REG_I2S0_CLK_EN_LEN)-1)<<MM_GLB_REG_I2S0_CLK_EN_POS)
#define MM_GLB_REG_I2S0_CLK_EN_UMSK                             (~(((1U<<MM_GLB_REG_I2S0_CLK_EN_LEN)-1)<<MM_GLB_REG_I2S0_CLK_EN_POS))

/* 0x40 : mm_sw_sys_reset */
#define MM_GLB_MM_SW_SYS_RESET_OFFSET                           (0x40)
#define MM_GLB_REG_CTRL_SYS_RESET                               MM_GLB_REG_CTRL_SYS_RESET
#define MM_GLB_REG_CTRL_SYS_RESET_POS                           (0U)
#define MM_GLB_REG_CTRL_SYS_RESET_LEN                           (1U)
#define MM_GLB_REG_CTRL_SYS_RESET_MSK                           (((1U<<MM_GLB_REG_CTRL_SYS_RESET_LEN)-1)<<MM_GLB_REG_CTRL_SYS_RESET_POS)
#define MM_GLB_REG_CTRL_SYS_RESET_UMSK                          (~(((1U<<MM_GLB_REG_CTRL_SYS_RESET_LEN)-1)<<MM_GLB_REG_CTRL_SYS_RESET_POS))
#define MM_GLB_REG_CTRL_PWRON_RST                               MM_GLB_REG_CTRL_PWRON_RST
#define MM_GLB_REG_CTRL_PWRON_RST_POS                           (2U)
#define MM_GLB_REG_CTRL_PWRON_RST_LEN                           (1U)
#define MM_GLB_REG_CTRL_PWRON_RST_MSK                           (((1U<<MM_GLB_REG_CTRL_PWRON_RST_LEN)-1)<<MM_GLB_REG_CTRL_PWRON_RST_POS)
#define MM_GLB_REG_CTRL_PWRON_RST_UMSK                          (~(((1U<<MM_GLB_REG_CTRL_PWRON_RST_LEN)-1)<<MM_GLB_REG_CTRL_PWRON_RST_POS))
#define MM_GLB_REG_CTRL_MMCPU0_RESET                            MM_GLB_REG_CTRL_MMCPU0_RESET
#define MM_GLB_REG_CTRL_MMCPU0_RESET_POS                        (8U)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_LEN                        (1U)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_MSK                        (((1U<<MM_GLB_REG_CTRL_MMCPU0_RESET_LEN)-1)<<MM_GLB_REG_CTRL_MMCPU0_RESET_POS)
#define MM_GLB_REG_CTRL_MMCPU0_RESET_UMSK                       (~(((1U<<MM_GLB_REG_CTRL_MMCPU0_RESET_LEN)-1)<<MM_GLB_REG_CTRL_MMCPU0_RESET_POS))
#define MM_GLB_REG_CTRL_MMCPU1_RESET                            MM_GLB_REG_CTRL_MMCPU1_RESET
#define MM_GLB_REG_CTRL_MMCPU1_RESET_POS                        (9U)
#define MM_GLB_REG_CTRL_MMCPU1_RESET_LEN                        (1U)
#define MM_GLB_REG_CTRL_MMCPU1_RESET_MSK                        (((1U<<MM_GLB_REG_CTRL_MMCPU1_RESET_LEN)-1)<<MM_GLB_REG_CTRL_MMCPU1_RESET_POS)
#define MM_GLB_REG_CTRL_MMCPU1_RESET_UMSK                       (~(((1U<<MM_GLB_REG_CTRL_MMCPU1_RESET_LEN)-1)<<MM_GLB_REG_CTRL_MMCPU1_RESET_POS))
#define MM_GLB_REG_WL2MM_RST_MSK                                MM_GLB_REG_WL2MM_RST_MSK
#define MM_GLB_REG_WL2MM_RST_MSK_POS                            (15U)
#define MM_GLB_REG_WL2MM_RST_MSK_LEN                            (1U)
#define MM_GLB_REG_WL2MM_RST_MSK_MSK                            (((1U<<MM_GLB_REG_WL2MM_RST_MSK_LEN)-1)<<MM_GLB_REG_WL2MM_RST_MSK_POS)
#define MM_GLB_REG_WL2MM_RST_MSK_UMSK                           (~(((1U<<MM_GLB_REG_WL2MM_RST_MSK_LEN)-1)<<MM_GLB_REG_WL2MM_RST_MSK_POS))

/* 0x44 : sw_reset_mm_peri */
#define MM_GLB_SW_RESET_MM_PERI_OFFSET                          (0x44)
#define MM_GLB_SWRST_MM_MISC                                    MM_GLB_SWRST_MM_MISC
#define MM_GLB_SWRST_MM_MISC_POS                                (0U)
#define MM_GLB_SWRST_MM_MISC_LEN                                (1U)
#define MM_GLB_SWRST_MM_MISC_MSK                                (((1U<<MM_GLB_SWRST_MM_MISC_LEN)-1)<<MM_GLB_SWRST_MM_MISC_POS)
#define MM_GLB_SWRST_MM_MISC_UMSK                               (~(((1U<<MM_GLB_SWRST_MM_MISC_LEN)-1)<<MM_GLB_SWRST_MM_MISC_POS))
#define MM_GLB_SWRST_DMA                                        MM_GLB_SWRST_DMA
#define MM_GLB_SWRST_DMA_POS                                    (1U)
#define MM_GLB_SWRST_DMA_LEN                                    (1U)
#define MM_GLB_SWRST_DMA_MSK                                    (((1U<<MM_GLB_SWRST_DMA_LEN)-1)<<MM_GLB_SWRST_DMA_POS)
#define MM_GLB_SWRST_DMA_UMSK                                   (~(((1U<<MM_GLB_SWRST_DMA_LEN)-1)<<MM_GLB_SWRST_DMA_POS))
#define MM_GLB_SWRST_UART0                                      MM_GLB_SWRST_UART0
#define MM_GLB_SWRST_UART0_POS                                  (2U)
#define MM_GLB_SWRST_UART0_LEN                                  (1U)
#define MM_GLB_SWRST_UART0_MSK                                  (((1U<<MM_GLB_SWRST_UART0_LEN)-1)<<MM_GLB_SWRST_UART0_POS)
#define MM_GLB_SWRST_UART0_UMSK                                 (~(((1U<<MM_GLB_SWRST_UART0_LEN)-1)<<MM_GLB_SWRST_UART0_POS))
#define MM_GLB_SWRST_I2C0                                       MM_GLB_SWRST_I2C0
#define MM_GLB_SWRST_I2C0_POS                                   (3U)
#define MM_GLB_SWRST_I2C0_LEN                                   (1U)
#define MM_GLB_SWRST_I2C0_MSK                                   (((1U<<MM_GLB_SWRST_I2C0_LEN)-1)<<MM_GLB_SWRST_I2C0_POS)
#define MM_GLB_SWRST_I2C0_UMSK                                  (~(((1U<<MM_GLB_SWRST_I2C0_LEN)-1)<<MM_GLB_SWRST_I2C0_POS))
#define MM_GLB_SWRST_IPC                                        MM_GLB_SWRST_IPC
#define MM_GLB_SWRST_IPC_POS                                    (5U)
#define MM_GLB_SWRST_IPC_LEN                                    (1U)
#define MM_GLB_SWRST_IPC_MSK                                    (((1U<<MM_GLB_SWRST_IPC_LEN)-1)<<MM_GLB_SWRST_IPC_POS)
#define MM_GLB_SWRST_IPC_UMSK                                   (~(((1U<<MM_GLB_SWRST_IPC_LEN)-1)<<MM_GLB_SWRST_IPC_POS))
#define MM_GLB_SWRST_SPI                                        MM_GLB_SWRST_SPI
#define MM_GLB_SWRST_SPI_POS                                    (8U)
#define MM_GLB_SWRST_SPI_LEN                                    (1U)
#define MM_GLB_SWRST_SPI_MSK                                    (((1U<<MM_GLB_SWRST_SPI_LEN)-1)<<MM_GLB_SWRST_SPI_POS)
#define MM_GLB_SWRST_SPI_UMSK                                   (~(((1U<<MM_GLB_SWRST_SPI_LEN)-1)<<MM_GLB_SWRST_SPI_POS))
#define MM_GLB_SWRST_TIMER                                      MM_GLB_SWRST_TIMER
#define MM_GLB_SWRST_TIMER_POS                                  (9U)
#define MM_GLB_SWRST_TIMER_LEN                                  (1U)
#define MM_GLB_SWRST_TIMER_MSK                                  (((1U<<MM_GLB_SWRST_TIMER_LEN)-1)<<MM_GLB_SWRST_TIMER_POS)
#define MM_GLB_SWRST_TIMER_UMSK                                 (~(((1U<<MM_GLB_SWRST_TIMER_LEN)-1)<<MM_GLB_SWRST_TIMER_POS))
#define MM_GLB_SWRST_I2S0                                       MM_GLB_SWRST_I2S0
#define MM_GLB_SWRST_I2S0_POS                                   (10U)
#define MM_GLB_SWRST_I2S0_LEN                                   (1U)
#define MM_GLB_SWRST_I2S0_MSK                                   (((1U<<MM_GLB_SWRST_I2S0_LEN)-1)<<MM_GLB_SWRST_I2S0_POS)
#define MM_GLB_SWRST_I2S0_UMSK                                  (~(((1U<<MM_GLB_SWRST_I2S0_LEN)-1)<<MM_GLB_SWRST_I2S0_POS))

/* 0x48 : sw_reset_isp_sub */
#define MM_GLB_SW_RESET_ISP_SUB_OFFSET                          (0x48)
#define MM_GLB_SWRST_ISP_MISC                                   MM_GLB_SWRST_ISP_MISC
#define MM_GLB_SWRST_ISP_MISC_POS                               (0U)
#define MM_GLB_SWRST_ISP_MISC_LEN                               (1U)
#define MM_GLB_SWRST_ISP_MISC_MSK                               (((1U<<MM_GLB_SWRST_ISP_MISC_LEN)-1)<<MM_GLB_SWRST_ISP_MISC_POS)
#define MM_GLB_SWRST_ISP_MISC_UMSK                              (~(((1U<<MM_GLB_SWRST_ISP_MISC_LEN)-1)<<MM_GLB_SWRST_ISP_MISC_POS))
#define MM_GLB_SWRST_DVP2BUSA                                   MM_GLB_SWRST_DVP2BUSA
#define MM_GLB_SWRST_DVP2BUSA_POS                               (1U)
#define MM_GLB_SWRST_DVP2BUSA_LEN                               (1U)
#define MM_GLB_SWRST_DVP2BUSA_MSK                               (((1U<<MM_GLB_SWRST_DVP2BUSA_LEN)-1)<<MM_GLB_SWRST_DVP2BUSA_POS)
#define MM_GLB_SWRST_DVP2BUSA_UMSK                              (~(((1U<<MM_GLB_SWRST_DVP2BUSA_LEN)-1)<<MM_GLB_SWRST_DVP2BUSA_POS))
#define MM_GLB_SWRST_DVP2BUSB                                   MM_GLB_SWRST_DVP2BUSB
#define MM_GLB_SWRST_DVP2BUSB_POS                               (2U)
#define MM_GLB_SWRST_DVP2BUSB_LEN                               (1U)
#define MM_GLB_SWRST_DVP2BUSB_MSK                               (((1U<<MM_GLB_SWRST_DVP2BUSB_LEN)-1)<<MM_GLB_SWRST_DVP2BUSB_POS)
#define MM_GLB_SWRST_DVP2BUSB_UMSK                              (~(((1U<<MM_GLB_SWRST_DVP2BUSB_LEN)-1)<<MM_GLB_SWRST_DVP2BUSB_POS))
#define MM_GLB_SWRST_DVP2BUSC                                   MM_GLB_SWRST_DVP2BUSC
#define MM_GLB_SWRST_DVP2BUSC_POS                               (3U)
#define MM_GLB_SWRST_DVP2BUSC_LEN                               (1U)
#define MM_GLB_SWRST_DVP2BUSC_MSK                               (((1U<<MM_GLB_SWRST_DVP2BUSC_LEN)-1)<<MM_GLB_SWRST_DVP2BUSC_POS)
#define MM_GLB_SWRST_DVP2BUSC_UMSK                              (~(((1U<<MM_GLB_SWRST_DVP2BUSC_LEN)-1)<<MM_GLB_SWRST_DVP2BUSC_POS))
#define MM_GLB_SWRST_OSD_DRAW                                   MM_GLB_SWRST_OSD_DRAW
#define MM_GLB_SWRST_OSD_DRAW_POS                               (4U)
#define MM_GLB_SWRST_OSD_DRAW_LEN                               (1U)
#define MM_GLB_SWRST_OSD_DRAW_MSK                               (((1U<<MM_GLB_SWRST_OSD_DRAW_LEN)-1)<<MM_GLB_SWRST_OSD_DRAW_POS)
#define MM_GLB_SWRST_OSD_DRAW_UMSK                              (~(((1U<<MM_GLB_SWRST_OSD_DRAW_LEN)-1)<<MM_GLB_SWRST_OSD_DRAW_POS))
#define MM_GLB_SWRST_DP                                         MM_GLB_SWRST_DP
#define MM_GLB_SWRST_DP_POS                                     (5U)
#define MM_GLB_SWRST_DP_LEN                                     (1U)
#define MM_GLB_SWRST_DP_MSK                                     (((1U<<MM_GLB_SWRST_DP_LEN)-1)<<MM_GLB_SWRST_DP_POS)
#define MM_GLB_SWRST_DP_UMSK                                    (~(((1U<<MM_GLB_SWRST_DP_LEN)-1)<<MM_GLB_SWRST_DP_POS))
#define MM_GLB_SWRST_IMG_PR                                     MM_GLB_SWRST_IMG_PR
#define MM_GLB_SWRST_IMG_PR_POS                                 (16U)
#define MM_GLB_SWRST_IMG_PR_LEN                                 (1U)
#define MM_GLB_SWRST_IMG_PR_MSK                                 (((1U<<MM_GLB_SWRST_IMG_PR_LEN)-1)<<MM_GLB_SWRST_IMG_PR_POS)
#define MM_GLB_SWRST_IMG_PR_UMSK                                (~(((1U<<MM_GLB_SWRST_IMG_PR_LEN)-1)<<MM_GLB_SWRST_IMG_PR_POS))
#define MM_GLB_SWRST_SCLRA                                      MM_GLB_SWRST_SCLRA
#define MM_GLB_SWRST_SCLRA_POS                                  (17U)
#define MM_GLB_SWRST_SCLRA_LEN                                  (1U)
#define MM_GLB_SWRST_SCLRA_MSK                                  (((1U<<MM_GLB_SWRST_SCLRA_LEN)-1)<<MM_GLB_SWRST_SCLRA_POS)
#define MM_GLB_SWRST_SCLRA_UMSK                                 (~(((1U<<MM_GLB_SWRST_SCLRA_LEN)-1)<<MM_GLB_SWRST_SCLRA_POS))
#define MM_GLB_SWRST_SCLRB                                      MM_GLB_SWRST_SCLRB
#define MM_GLB_SWRST_SCLRB_POS                                  (18U)
#define MM_GLB_SWRST_SCLRB_LEN                                  (1U)
#define MM_GLB_SWRST_SCLRB_MSK                                  (((1U<<MM_GLB_SWRST_SCLRB_LEN)-1)<<MM_GLB_SWRST_SCLRB_POS)
#define MM_GLB_SWRST_SCLRB_UMSK                                 (~(((1U<<MM_GLB_SWRST_SCLRB_LEN)-1)<<MM_GLB_SWRST_SCLRB_POS))

/* 0x4C : sw_reset_codec_sub */
#define MM_GLB_SW_RESET_CODEC_SUB_OFFSET                        (0x4C)
#define MM_GLB_SWRST_MJPEG                                      MM_GLB_SWRST_MJPEG
#define MM_GLB_SWRST_MJPEG_POS                                  (1U)
#define MM_GLB_SWRST_MJPEG_LEN                                  (1U)
#define MM_GLB_SWRST_MJPEG_MSK                                  (((1U<<MM_GLB_SWRST_MJPEG_LEN)-1)<<MM_GLB_SWRST_MJPEG_POS)
#define MM_GLB_SWRST_MJPEG_UMSK                                 (~(((1U<<MM_GLB_SWRST_MJPEG_LEN)-1)<<MM_GLB_SWRST_MJPEG_POS))
#define MM_GLB_SWRST_CNN                                        MM_GLB_SWRST_CNN
#define MM_GLB_SWRST_CNN_POS                                    (2U)
#define MM_GLB_SWRST_CNN_LEN                                    (1U)
#define MM_GLB_SWRST_CNN_MSK                                    (((1U<<MM_GLB_SWRST_CNN_LEN)-1)<<MM_GLB_SWRST_CNN_POS)
#define MM_GLB_SWRST_CNN_UMSK                                   (~(((1U<<MM_GLB_SWRST_CNN_LEN)-1)<<MM_GLB_SWRST_CNN_POS))
#define MM_GLB_SWRST_VRAM                                       MM_GLB_SWRST_VRAM
#define MM_GLB_SWRST_VRAM_POS                                   (16U)
#define MM_GLB_SWRST_VRAM_LEN                                   (1U)
#define MM_GLB_SWRST_VRAM_MSK                                   (((1U<<MM_GLB_SWRST_VRAM_LEN)-1)<<MM_GLB_SWRST_VRAM_POS)
#define MM_GLB_SWRST_VRAM_UMSK                                  (~(((1U<<MM_GLB_SWRST_VRAM_LEN)-1)<<MM_GLB_SWRST_VRAM_POS))

/* 0x50 : image_sensor_ctrl */
#define MM_GLB_IMAGE_SENSOR_CTRL_OFFSET                         (0x50)
#define MM_GLB_RG_IS_RST_N                                      MM_GLB_RG_IS_RST_N
#define MM_GLB_RG_IS_RST_N_POS                                  (0U)
#define MM_GLB_RG_IS_RST_N_LEN                                  (1U)
#define MM_GLB_RG_IS_RST_N_MSK                                  (((1U<<MM_GLB_RG_IS_RST_N_LEN)-1)<<MM_GLB_RG_IS_RST_N_POS)
#define MM_GLB_RG_IS_RST_N_UMSK                                 (~(((1U<<MM_GLB_RG_IS_RST_N_LEN)-1)<<MM_GLB_RG_IS_RST_N_POS))


struct  mm_glb_reg {
    /* 0x0 : mm_clk_ctrl_cpu */
    union {
        struct {
            uint32_t reg_pll_en                     :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_cpu_clk_en                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_bclk_en                    :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_4                   :  2; /* [ 4: 3],       rsvd,        0x0 */
            uint32_t hbn_uart_clk_sel               :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_cpu_clk_sel                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t hbn_root_clk_sel               :  2; /* [11:10],        r/w,        0x0 */
            uint32_t reg_mmcpu0_clk_en              :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_mmcpu1_clk_en              :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_23                 : 10; /* [23:14],       rsvd,        0x0 */
            uint32_t cpu_clk_sw_state               :  3; /* [26:24],          r,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_cpu;

    /* 0x4 : mm_clk_cpu */
    union {
        struct {
            uint32_t reg_cpu_clk_div                :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_cnn_clk_div_en             :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_cnn_clk_sel                :  2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t reg_cnn_clk_div                :  3; /* [14:12],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t reg_bclk2x_div                 :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_bclk1x_div                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_cpu;

    /* 0x8 : mm_clk_ctrl_isp_sub_sys */
    union {
        struct {
            uint32_t reg_isp_clk_div_en             :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_isp_clk_sel                :  2; /* [ 2: 1],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_isp_clk_div                :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_dp_clk_div_en              :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_dp_clk_sel                 :  2; /* [18:17],        r/w,        0x0 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t reg_dp_clk_div                 :  4; /* [23:20],        r/w,        0x0 */
            uint32_t reg_snsr_clk_div_en            :  1; /* [   24],        r/w,        0x1 */
            uint32_t reserved_25_27                 :  3; /* [27:25],       rsvd,        0x0 */
            uint32_t reg_snsr_clk_div               :  4; /* [31:28],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_isp_sub_sys;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[4];

    /* 0x10 : mm_clk_ctrl_peri */
    union {
        struct {
            uint32_t reg_i2c0_clk_div               :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_i2c0_clk_div_en            :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_i2c0_clk_en                :  1; /* [    9],        r/w,        0x1 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t reg_uart0_clk_div_en           :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_uart0_clk_div              :  3; /* [19:17],        r/w,        0x0 */
            uint32_t reserved_20_22                 :  3; /* [22:20],       rsvd,        0x0 */
            uint32_t reg_spi_clk_div_en             :  1; /* [   23],        r/w,        0x1 */
            uint32_t reg_spi_clk_div                :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_peri;

    /* 0x14 : mm_clk_ctrl_peri2 */
    union {
        struct {
            uint32_t reg_i2s0_clk_div               :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reg_i2s0_ref_clk_oe            :  1; /* [    6],        r/w,        0x1 */
            uint32_t reg_i2s0_clk_en                :  1; /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_peri2;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[40];

    /* 0x40 : mm_sw_sys_reset */
    union {
        struct {
            uint32_t reg_ctrl_sys_reset             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1                     :  1; /* [    1],       rsvd,        0x0 */
            uint32_t reg_ctrl_pwron_rst             :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_ctrl_mmcpu0_reset          :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_ctrl_mmcpu1_reset          :  1; /* [    9],        r/w,        0x1 */
            uint32_t reserved_10_14                 :  5; /* [14:10],       rsvd,        0x0 */
            uint32_t reg_wl2mm_rst_msk              :  1; /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_sw_sys_reset;

    /* 0x44 : sw_reset_mm_peri */
    union {
        struct {
            uint32_t swrst_mm_misc                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t swrst_dma                      :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_uart0                    :  1; /* [    2],        r/w,        0x0 */
            uint32_t swrst_i2c0                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t reserved_4                     :  1; /* [    4],       rsvd,        0x0 */
            uint32_t swrst_ipc                      :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t swrst_spi                      :  1; /* [    8],        r/w,        0x0 */
            uint32_t swrst_timer                    :  1; /* [    9],        r/w,        0x0 */
            uint32_t swrst_i2s0                     :  1; /* [   10],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_mm_peri;

    /* 0x48 : sw_reset_isp_sub */
    union {
        struct {
            uint32_t swrst_isp_misc                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t swrst_dvp2busA                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_dvp2busB                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t swrst_dvp2busC                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t swrst_osd_draw                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t swrst_dp                       :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t swrst_img_pr                   :  1; /* [   16],        r/w,        0x0 */
            uint32_t swrst_sclrA                    :  1; /* [   17],        r/w,        0x0 */
            uint32_t swrst_sclrB                    :  1; /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_isp_sub;

    /* 0x4C : sw_reset_codec_sub */
    union {
        struct {
            uint32_t reserved_0                     :  1; /* [    0],       rsvd,        0x0 */
            uint32_t swrst_mjpeg                    :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_cnn                      :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_15                  : 13; /* [15: 3],       rsvd,        0x0 */
            uint32_t swrst_vram                     :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_codec_sub;

    /* 0x50 : image_sensor_ctrl */
    union {
        struct {
            uint32_t rg_is_rst_n                    :  1; /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } image_sensor_ctrl;

};

typedef volatile struct mm_glb_reg mm_glb_reg_t;


#endif  /* __MM_GLB_REG_H__ */
