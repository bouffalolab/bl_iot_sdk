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
#ifndef  __CLKRST_REG_H__
#define  __CLKRST_REG_H__

#include "bl808.h"

/* 0x0 : mm_clk_ctrl_cpu */
#define CLKRST_MM_CLK_CTRL_CPU_OFFSET                           (0x0)
#define CLKRST_REG_PLL_EN                                       CLKRST_REG_PLL_EN
#define CLKRST_REG_PLL_EN_POS                                   (0U)
#define CLKRST_REG_PLL_EN_LEN                                   (1U)
#define CLKRST_REG_PLL_EN_MSK                                   (((1U<<CLKRST_REG_PLL_EN_LEN)-1)<<CLKRST_REG_PLL_EN_POS)
#define CLKRST_REG_PLL_EN_UMSK                                  (~(((1U<<CLKRST_REG_PLL_EN_LEN)-1)<<CLKRST_REG_PLL_EN_POS))
#define CLKRST_REG_CPU_CLK_EN                                   CLKRST_REG_CPU_CLK_EN
#define CLKRST_REG_CPU_CLK_EN_POS                               (1U)
#define CLKRST_REG_CPU_CLK_EN_LEN                               (1U)
#define CLKRST_REG_CPU_CLK_EN_MSK                               (((1U<<CLKRST_REG_CPU_CLK_EN_LEN)-1)<<CLKRST_REG_CPU_CLK_EN_POS)
#define CLKRST_REG_CPU_CLK_EN_UMSK                              (~(((1U<<CLKRST_REG_CPU_CLK_EN_LEN)-1)<<CLKRST_REG_CPU_CLK_EN_POS))
#define CLKRST_REG_BCLK_EN                                      CLKRST_REG_BCLK_EN
#define CLKRST_REG_BCLK_EN_POS                                  (2U)
#define CLKRST_REG_BCLK_EN_LEN                                  (1U)
#define CLKRST_REG_BCLK_EN_MSK                                  (((1U<<CLKRST_REG_BCLK_EN_LEN)-1)<<CLKRST_REG_BCLK_EN_POS)
#define CLKRST_REG_BCLK_EN_UMSK                                 (~(((1U<<CLKRST_REG_BCLK_EN_LEN)-1)<<CLKRST_REG_BCLK_EN_POS))
#define CLKRST_REG_A5_CPU_CLK_EN                                CLKRST_REG_A5_CPU_CLK_EN
#define CLKRST_REG_A5_CPU_CLK_EN_POS                            (3U)
#define CLKRST_REG_A5_CPU_CLK_EN_LEN                            (1U)
#define CLKRST_REG_A5_CPU_CLK_EN_MSK                            (((1U<<CLKRST_REG_A5_CPU_CLK_EN_LEN)-1)<<CLKRST_REG_A5_CPU_CLK_EN_POS)
#define CLKRST_REG_A5_CPU_CLK_EN_UMSK                           (~(((1U<<CLKRST_REG_A5_CPU_CLK_EN_LEN)-1)<<CLKRST_REG_A5_CPU_CLK_EN_POS))
#define CLKRST_REG_E74C_CLK_EN                                  CLKRST_REG_E74C_CLK_EN
#define CLKRST_REG_E74C_CLK_EN_POS                              (4U)
#define CLKRST_REG_E74C_CLK_EN_LEN                              (1U)
#define CLKRST_REG_E74C_CLK_EN_MSK                              (((1U<<CLKRST_REG_E74C_CLK_EN_LEN)-1)<<CLKRST_REG_E74C_CLK_EN_POS)
#define CLKRST_REG_E74C_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_E74C_CLK_EN_LEN)-1)<<CLKRST_REG_E74C_CLK_EN_POS))
#define CLKRST_HBN_UART_CLK_SEL                                 CLKRST_HBN_UART_CLK_SEL
#define CLKRST_HBN_UART_CLK_SEL_POS                             (5U)
#define CLKRST_HBN_UART_CLK_SEL_LEN                             (1U)
#define CLKRST_HBN_UART_CLK_SEL_MSK                             (((1U<<CLKRST_HBN_UART_CLK_SEL_LEN)-1)<<CLKRST_HBN_UART_CLK_SEL_POS)
#define CLKRST_HBN_UART_CLK_SEL_UMSK                            (~(((1U<<CLKRST_HBN_UART_CLK_SEL_LEN)-1)<<CLKRST_HBN_UART_CLK_SEL_POS))
#define CLKRST_REG_E74C_CLK_EN_2                                CLKRST_REG_E74C_CLK_EN_2
#define CLKRST_REG_E74C_CLK_EN_2_POS                            (6U)
#define CLKRST_REG_E74C_CLK_EN_2_LEN                            (1U)
#define CLKRST_REG_E74C_CLK_EN_2_MSK                            (((1U<<CLKRST_REG_E74C_CLK_EN_2_LEN)-1)<<CLKRST_REG_E74C_CLK_EN_2_POS)
#define CLKRST_REG_E74C_CLK_EN_2_UMSK                           (~(((1U<<CLKRST_REG_E74C_CLK_EN_2_LEN)-1)<<CLKRST_REG_E74C_CLK_EN_2_POS))
#define CLKRST_REG_PLL_SEL                                      CLKRST_REG_PLL_SEL
#define CLKRST_REG_PLL_SEL_POS                                  (8U)
#define CLKRST_REG_PLL_SEL_LEN                                  (2U)
#define CLKRST_REG_PLL_SEL_MSK                                  (((1U<<CLKRST_REG_PLL_SEL_LEN)-1)<<CLKRST_REG_PLL_SEL_POS)
#define CLKRST_REG_PLL_SEL_UMSK                                 (~(((1U<<CLKRST_REG_PLL_SEL_LEN)-1)<<CLKRST_REG_PLL_SEL_POS))
#define CLKRST_HBN_ROOT_CLK_SEL                                 CLKRST_HBN_ROOT_CLK_SEL
#define CLKRST_HBN_ROOT_CLK_SEL_POS                             (10U)
#define CLKRST_HBN_ROOT_CLK_SEL_LEN                             (2U)
#define CLKRST_HBN_ROOT_CLK_SEL_MSK                             (((1U<<CLKRST_HBN_ROOT_CLK_SEL_LEN)-1)<<CLKRST_HBN_ROOT_CLK_SEL_POS)
#define CLKRST_HBN_ROOT_CLK_SEL_UMSK                            (~(((1U<<CLKRST_HBN_ROOT_CLK_SEL_LEN)-1)<<CLKRST_HBN_ROOT_CLK_SEL_POS))
#define CLKRST_REG_M4_FCLK_EN                                   CLKRST_REG_M4_FCLK_EN
#define CLKRST_REG_M4_FCLK_EN_POS                               (12U)
#define CLKRST_REG_M4_FCLK_EN_LEN                               (1U)
#define CLKRST_REG_M4_FCLK_EN_MSK                               (((1U<<CLKRST_REG_M4_FCLK_EN_LEN)-1)<<CLKRST_REG_M4_FCLK_EN_POS)
#define CLKRST_REG_M4_FCLK_EN_UMSK                              (~(((1U<<CLKRST_REG_M4_FCLK_EN_LEN)-1)<<CLKRST_REG_M4_FCLK_EN_POS))
#define CLKRST_REG_M4_FCLK_SEL                                  CLKRST_REG_M4_FCLK_SEL
#define CLKRST_REG_M4_FCLK_SEL_POS                              (13U)
#define CLKRST_REG_M4_FCLK_SEL_LEN                              (1U)
#define CLKRST_REG_M4_FCLK_SEL_MSK                              (((1U<<CLKRST_REG_M4_FCLK_SEL_LEN)-1)<<CLKRST_REG_M4_FCLK_SEL_POS)
#define CLKRST_REG_M4_FCLK_SEL_UMSK                             (~(((1U<<CLKRST_REG_M4_FCLK_SEL_LEN)-1)<<CLKRST_REG_M4_FCLK_SEL_POS))
#define CLKRST_REG_M4_HCLK_EN                                   CLKRST_REG_M4_HCLK_EN
#define CLKRST_REG_M4_HCLK_EN_POS                               (14U)
#define CLKRST_REG_M4_HCLK_EN_LEN                               (1U)
#define CLKRST_REG_M4_HCLK_EN_MSK                               (((1U<<CLKRST_REG_M4_HCLK_EN_LEN)-1)<<CLKRST_REG_M4_HCLK_EN_POS)
#define CLKRST_REG_M4_HCLK_EN_UMSK                              (~(((1U<<CLKRST_REG_M4_HCLK_EN_LEN)-1)<<CLKRST_REG_M4_HCLK_EN_POS))
#define CLKRST_REG_M4_TRACE_EN                                  CLKRST_REG_M4_TRACE_EN
#define CLKRST_REG_M4_TRACE_EN_POS                              (15U)
#define CLKRST_REG_M4_TRACE_EN_LEN                              (1U)
#define CLKRST_REG_M4_TRACE_EN_MSK                              (((1U<<CLKRST_REG_M4_TRACE_EN_LEN)-1)<<CLKRST_REG_M4_TRACE_EN_POS)
#define CLKRST_REG_M4_TRACE_EN_UMSK                             (~(((1U<<CLKRST_REG_M4_TRACE_EN_LEN)-1)<<CLKRST_REG_M4_TRACE_EN_POS))
#define CLKRST_CPU_CLK_SW_STATE                                 CLKRST_CPU_CLK_SW_STATE
#define CLKRST_CPU_CLK_SW_STATE_POS                             (24U)
#define CLKRST_CPU_CLK_SW_STATE_LEN                             (3U)
#define CLKRST_CPU_CLK_SW_STATE_MSK                             (((1U<<CLKRST_CPU_CLK_SW_STATE_LEN)-1)<<CLKRST_CPU_CLK_SW_STATE_POS)
#define CLKRST_CPU_CLK_SW_STATE_UMSK                            (~(((1U<<CLKRST_CPU_CLK_SW_STATE_LEN)-1)<<CLKRST_CPU_CLK_SW_STATE_POS))
#define CLKRST_M4_FCLK_SW_STATE                                 CLKRST_M4_FCLK_SW_STATE
#define CLKRST_M4_FCLK_SW_STATE_POS                             (28U)
#define CLKRST_M4_FCLK_SW_STATE_LEN                             (3U)
#define CLKRST_M4_FCLK_SW_STATE_MSK                             (((1U<<CLKRST_M4_FCLK_SW_STATE_LEN)-1)<<CLKRST_M4_FCLK_SW_STATE_POS)
#define CLKRST_M4_FCLK_SW_STATE_UMSK                            (~(((1U<<CLKRST_M4_FCLK_SW_STATE_LEN)-1)<<CLKRST_M4_FCLK_SW_STATE_POS))

/* 0x4 : mm_clk_cpu */
#define CLKRST_MM_CLK_CPU_OFFSET                                (0x4)
#define CLKRST_REG_CPU_CLK_DIV                                  CLKRST_REG_CPU_CLK_DIV
#define CLKRST_REG_CPU_CLK_DIV_POS                              (0U)
#define CLKRST_REG_CPU_CLK_DIV_LEN                              (8U)
#define CLKRST_REG_CPU_CLK_DIV_MSK                              (((1U<<CLKRST_REG_CPU_CLK_DIV_LEN)-1)<<CLKRST_REG_CPU_CLK_DIV_POS)
#define CLKRST_REG_CPU_CLK_DIV_UMSK                             (~(((1U<<CLKRST_REG_CPU_CLK_DIV_LEN)-1)<<CLKRST_REG_CPU_CLK_DIV_POS))
#define CLKRST_REG_CNN_CLK_DIV_EN                               CLKRST_REG_CNN_CLK_DIV_EN
#define CLKRST_REG_CNN_CLK_DIV_EN_POS                           (8U)
#define CLKRST_REG_CNN_CLK_DIV_EN_LEN                           (1U)
#define CLKRST_REG_CNN_CLK_DIV_EN_MSK                           (((1U<<CLKRST_REG_CNN_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_CNN_CLK_DIV_EN_POS)
#define CLKRST_REG_CNN_CLK_DIV_EN_UMSK                          (~(((1U<<CLKRST_REG_CNN_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_CNN_CLK_DIV_EN_POS))
#define CLKRST_REG_CNN_CLK_SEL                                  CLKRST_REG_CNN_CLK_SEL
#define CLKRST_REG_CNN_CLK_SEL_POS                              (9U)
#define CLKRST_REG_CNN_CLK_SEL_LEN                              (2U)
#define CLKRST_REG_CNN_CLK_SEL_MSK                              (((1U<<CLKRST_REG_CNN_CLK_SEL_LEN)-1)<<CLKRST_REG_CNN_CLK_SEL_POS)
#define CLKRST_REG_CNN_CLK_SEL_UMSK                             (~(((1U<<CLKRST_REG_CNN_CLK_SEL_LEN)-1)<<CLKRST_REG_CNN_CLK_SEL_POS))
#define CLKRST_REG_BCLK_DIV                                     CLKRST_REG_BCLK_DIV
#define CLKRST_REG_BCLK_DIV_POS                                 (16U)
#define CLKRST_REG_BCLK_DIV_LEN                                 (8U)
#define CLKRST_REG_BCLK_DIV_MSK                                 (((1U<<CLKRST_REG_BCLK_DIV_LEN)-1)<<CLKRST_REG_BCLK_DIV_POS)
#define CLKRST_REG_BCLK_DIV_UMSK                                (~(((1U<<CLKRST_REG_BCLK_DIV_LEN)-1)<<CLKRST_REG_BCLK_DIV_POS))

/* 0x8 : isp_dp_clk */
#define CLKRST_ISP_DP_CLK_OFFSET                                (0x8)
#define CLKRST_REG_ISP_CLK_DIV_EN                               CLKRST_REG_ISP_CLK_DIV_EN
#define CLKRST_REG_ISP_CLK_DIV_EN_POS                           (0U)
#define CLKRST_REG_ISP_CLK_DIV_EN_LEN                           (1U)
#define CLKRST_REG_ISP_CLK_DIV_EN_MSK                           (((1U<<CLKRST_REG_ISP_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_ISP_CLK_DIV_EN_POS)
#define CLKRST_REG_ISP_CLK_DIV_EN_UMSK                          (~(((1U<<CLKRST_REG_ISP_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_ISP_CLK_DIV_EN_POS))
#define CLKRST_REG_ISP_CLK_SEL                                  CLKRST_REG_ISP_CLK_SEL
#define CLKRST_REG_ISP_CLK_SEL_POS                              (1U)
#define CLKRST_REG_ISP_CLK_SEL_LEN                              (2U)
#define CLKRST_REG_ISP_CLK_SEL_MSK                              (((1U<<CLKRST_REG_ISP_CLK_SEL_LEN)-1)<<CLKRST_REG_ISP_CLK_SEL_POS)
#define CLKRST_REG_ISP_CLK_SEL_UMSK                             (~(((1U<<CLKRST_REG_ISP_CLK_SEL_LEN)-1)<<CLKRST_REG_ISP_CLK_SEL_POS))
#define CLKRST_REG_ISP_CLK_DIV                                  CLKRST_REG_ISP_CLK_DIV
#define CLKRST_REG_ISP_CLK_DIV_POS                              (8U)
#define CLKRST_REG_ISP_CLK_DIV_LEN                              (8U)
#define CLKRST_REG_ISP_CLK_DIV_MSK                              (((1U<<CLKRST_REG_ISP_CLK_DIV_LEN)-1)<<CLKRST_REG_ISP_CLK_DIV_POS)
#define CLKRST_REG_ISP_CLK_DIV_UMSK                             (~(((1U<<CLKRST_REG_ISP_CLK_DIV_LEN)-1)<<CLKRST_REG_ISP_CLK_DIV_POS))
#define CLKRST_REG_HDMI_CLK_DIV_EN                              CLKRST_REG_HDMI_CLK_DIV_EN
#define CLKRST_REG_HDMI_CLK_DIV_EN_POS                          (16U)
#define CLKRST_REG_HDMI_CLK_DIV_EN_LEN                          (1U)
#define CLKRST_REG_HDMI_CLK_DIV_EN_MSK                          (((1U<<CLKRST_REG_HDMI_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_HDMI_CLK_DIV_EN_POS)
#define CLKRST_REG_HDMI_CLK_DIV_EN_UMSK                         (~(((1U<<CLKRST_REG_HDMI_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_HDMI_CLK_DIV_EN_POS))
#define CLKRST_REG_DISP_CLK_SEL                                 CLKRST_REG_DISP_CLK_SEL
#define CLKRST_REG_DISP_CLK_SEL_POS                             (17U)
#define CLKRST_REG_DISP_CLK_SEL_LEN                             (1U)
#define CLKRST_REG_DISP_CLK_SEL_MSK                             (((1U<<CLKRST_REG_DISP_CLK_SEL_LEN)-1)<<CLKRST_REG_DISP_CLK_SEL_POS)
#define CLKRST_REG_DISP_CLK_SEL_UMSK                            (~(((1U<<CLKRST_REG_DISP_CLK_SEL_LEN)-1)<<CLKRST_REG_DISP_CLK_SEL_POS))
#define CLKRST_REG_DISP_CLK_DIV                                 CLKRST_REG_DISP_CLK_DIV
#define CLKRST_REG_DISP_CLK_DIV_POS                             (20U)
#define CLKRST_REG_DISP_CLK_DIV_LEN                             (4U)
#define CLKRST_REG_DISP_CLK_DIV_MSK                             (((1U<<CLKRST_REG_DISP_CLK_DIV_LEN)-1)<<CLKRST_REG_DISP_CLK_DIV_POS)
#define CLKRST_REG_DISP_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_DISP_CLK_DIV_LEN)-1)<<CLKRST_REG_DISP_CLK_DIV_POS))


/* 0xC : codec_clk */
#define CLKRST_CODEC_CLK_OFFSET                                 (0xC)
#define CLKRST_REG_H264_CLK_DIV_EN                              CLKRST_REG_H264_CLK_DIV_EN
#define CLKRST_REG_H264_CLK_DIV_EN_POS                          (8U)
#define CLKRST_REG_H264_CLK_DIV_EN_LEN                          (1U)
#define CLKRST_REG_H264_CLK_DIV_EN_MSK                          (((1U<<CLKRST_REG_H264_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_H264_CLK_DIV_EN_POS)
#define CLKRST_REG_H264_CLK_DIV_EN_UMSK                         (~(((1U<<CLKRST_REG_H264_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_H264_CLK_DIV_EN_POS))
#define CLKRST_REG_H264_CLK_SEL                                 CLKRST_REG_H264_CLK_SEL
#define CLKRST_REG_H264_CLK_SEL_POS                             (9U)
#define CLKRST_REG_H264_CLK_SEL_LEN                             (2U)
#define CLKRST_REG_H264_CLK_SEL_MSK                             (((1U<<CLKRST_REG_H264_CLK_SEL_LEN)-1)<<CLKRST_REG_H264_CLK_SEL_POS)
#define CLKRST_REG_H264_CLK_SEL_UMSK                            (~(((1U<<CLKRST_REG_H264_CLK_SEL_LEN)-1)<<CLKRST_REG_H264_CLK_SEL_POS))
#define CLKRST_REG_H264_CLK_DIV                                 CLKRST_REG_H264_CLK_DIV
#define CLKRST_REG_H264_CLK_DIV_POS                             (12U)
#define CLKRST_REG_H264_CLK_DIV_LEN                             (3U)
#define CLKRST_REG_H264_CLK_DIV_MSK                             (((1U<<CLKRST_REG_H264_CLK_DIV_LEN)-1)<<CLKRST_REG_H264_CLK_DIV_POS)
#define CLKRST_REG_H264_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_H264_CLK_DIV_LEN)-1)<<CLKRST_REG_H264_CLK_DIV_POS))

/* 0x10 : mm_clk_ctrl_peri */
#define CLKRST_MM_CLK_CTRL_PERI_OFFSET                          (0x10)
#define CLKRST_REG_I2C_CLK_DIV                                  CLKRST_REG_I2C_CLK_DIV
#define CLKRST_REG_I2C_CLK_DIV_POS                              (0U)
#define CLKRST_REG_I2C_CLK_DIV_LEN                              (8U)
#define CLKRST_REG_I2C_CLK_DIV_MSK                              (((1U<<CLKRST_REG_I2C_CLK_DIV_LEN)-1)<<CLKRST_REG_I2C_CLK_DIV_POS)
#define CLKRST_REG_I2C_CLK_DIV_UMSK                             (~(((1U<<CLKRST_REG_I2C_CLK_DIV_LEN)-1)<<CLKRST_REG_I2C_CLK_DIV_POS))
#define CLKRST_REG_I2C_CLK_DIV_EN                               CLKRST_REG_I2C_CLK_DIV_EN
#define CLKRST_REG_I2C_CLK_DIV_EN_POS                           (8U)
#define CLKRST_REG_I2C_CLK_DIV_EN_LEN                           (1U)
#define CLKRST_REG_I2C_CLK_DIV_EN_MSK                           (((1U<<CLKRST_REG_I2C_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_I2C_CLK_DIV_EN_POS)
#define CLKRST_REG_I2C_CLK_DIV_EN_UMSK                          (~(((1U<<CLKRST_REG_I2C_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_I2C_CLK_DIV_EN_POS))
#define CLKRST_REG_I2CA_CLK_EN                                  CLKRST_REG_I2CA_CLK_EN
#define CLKRST_REG_I2CA_CLK_EN_POS                              (9U)
#define CLKRST_REG_I2CA_CLK_EN_LEN                              (1U)
#define CLKRST_REG_I2CA_CLK_EN_MSK                              (((1U<<CLKRST_REG_I2CA_CLK_EN_LEN)-1)<<CLKRST_REG_I2CA_CLK_EN_POS)
#define CLKRST_REG_I2CA_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_I2CA_CLK_EN_LEN)-1)<<CLKRST_REG_I2CA_CLK_EN_POS))
#define CLKRST_REG_I2CB_CLK_EN                                  CLKRST_REG_I2CB_CLK_EN
#define CLKRST_REG_I2CB_CLK_EN_POS                              (10U)
#define CLKRST_REG_I2CB_CLK_EN_LEN                              (1U)
#define CLKRST_REG_I2CB_CLK_EN_MSK                              (((1U<<CLKRST_REG_I2CB_CLK_EN_LEN)-1)<<CLKRST_REG_I2CB_CLK_EN_POS)
#define CLKRST_REG_I2CB_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_I2CB_CLK_EN_LEN)-1)<<CLKRST_REG_I2CB_CLK_EN_POS))
#define CLKRST_REG_SDH_CLK_EN                                   CLKRST_REG_SDH_CLK_EN
#define CLKRST_REG_SDH_CLK_EN_POS                               (12U)
#define CLKRST_REG_SDH_CLK_EN_LEN                               (1U)
#define CLKRST_REG_SDH_CLK_EN_MSK                               (((1U<<CLKRST_REG_SDH_CLK_EN_LEN)-1)<<CLKRST_REG_SDH_CLK_EN_POS)
#define CLKRST_REG_SDH_CLK_EN_UMSK                              (~(((1U<<CLKRST_REG_SDH_CLK_EN_LEN)-1)<<CLKRST_REG_SDH_CLK_EN_POS))
#define CLKRST_REG_SDH_CLK_SEL                                  CLKRST_REG_SDH_CLK_SEL
#define CLKRST_REG_SDH_CLK_SEL_POS                              (13U)
#define CLKRST_REG_SDH_CLK_SEL_LEN                              (3U)
#define CLKRST_REG_SDH_CLK_SEL_MSK                              (((1U<<CLKRST_REG_SDH_CLK_SEL_LEN)-1)<<CLKRST_REG_SDH_CLK_SEL_POS)
#define CLKRST_REG_SDH_CLK_SEL_UMSK                             (~(((1U<<CLKRST_REG_SDH_CLK_SEL_LEN)-1)<<CLKRST_REG_SDH_CLK_SEL_POS))
#define CLKRST_REG_UART_CLK_DIV_EN                              CLKRST_REG_UART_CLK_DIV_EN
#define CLKRST_REG_UART_CLK_DIV_EN_POS                          (16U)
#define CLKRST_REG_UART_CLK_DIV_EN_LEN                          (1U)
#define CLKRST_REG_UART_CLK_DIV_EN_MSK                          (((1U<<CLKRST_REG_UART_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_UART_CLK_DIV_EN_POS)
#define CLKRST_REG_UART_CLK_DIV_EN_UMSK                         (~(((1U<<CLKRST_REG_UART_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_UART_CLK_DIV_EN_POS))
#define CLKRST_REG_UART_CLK_DIV                                 CLKRST_REG_UART_CLK_DIV
#define CLKRST_REG_UART_CLK_DIV_POS                             (17U)
#define CLKRST_REG_UART_CLK_DIV_LEN                             (3U)
#define CLKRST_REG_UART_CLK_DIV_MSK                             (((1U<<CLKRST_REG_UART_CLK_DIV_LEN)-1)<<CLKRST_REG_UART_CLK_DIV_POS)
#define CLKRST_REG_UART_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_UART_CLK_DIV_LEN)-1)<<CLKRST_REG_UART_CLK_DIV_POS))
#define CLKRST_REG_ETH_CLK_EN                                   CLKRST_REG_ETH_CLK_EN
#define CLKRST_REG_ETH_CLK_EN_POS                               (20U)
#define CLKRST_REG_ETH_CLK_EN_LEN                               (1U)
#define CLKRST_REG_ETH_CLK_EN_MSK                               (((1U<<CLKRST_REG_ETH_CLK_EN_LEN)-1)<<CLKRST_REG_ETH_CLK_EN_POS)
#define CLKRST_REG_ETH_CLK_EN_UMSK                              (~(((1U<<CLKRST_REG_ETH_CLK_EN_LEN)-1)<<CLKRST_REG_ETH_CLK_EN_POS))
#define CLKRST_REG_ETH_CLK_SEL                                  CLKRST_REG_ETH_CLK_SEL
#define CLKRST_REG_ETH_CLK_SEL_POS                              (21U)
#define CLKRST_REG_ETH_CLK_SEL_LEN                              (2U)
#define CLKRST_REG_ETH_CLK_SEL_MSK                              (((1U<<CLKRST_REG_ETH_CLK_SEL_LEN)-1)<<CLKRST_REG_ETH_CLK_SEL_POS)
#define CLKRST_REG_ETH_CLK_SEL_UMSK                             (~(((1U<<CLKRST_REG_ETH_CLK_SEL_LEN)-1)<<CLKRST_REG_ETH_CLK_SEL_POS))
#define CLKRST_REG_SPI_CLK_DIV_EN                               CLKRST_REG_SPI_CLK_DIV_EN
#define CLKRST_REG_SPI_CLK_DIV_EN_POS                           (23U)
#define CLKRST_REG_SPI_CLK_DIV_EN_LEN                           (1U)
#define CLKRST_REG_SPI_CLK_DIV_EN_MSK                           (((1U<<CLKRST_REG_SPI_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_SPI_CLK_DIV_EN_POS)
#define CLKRST_REG_SPI_CLK_DIV_EN_UMSK                          (~(((1U<<CLKRST_REG_SPI_CLK_DIV_EN_LEN)-1)<<CLKRST_REG_SPI_CLK_DIV_EN_POS))
#define CLKRST_REG_SPI_CLK_DIV                                  CLKRST_REG_SPI_CLK_DIV
#define CLKRST_REG_SPI_CLK_DIV_POS                              (24U)
#define CLKRST_REG_SPI_CLK_DIV_LEN                              (8U)
#define CLKRST_REG_SPI_CLK_DIV_MSK                              (((1U<<CLKRST_REG_SPI_CLK_DIV_LEN)-1)<<CLKRST_REG_SPI_CLK_DIV_POS)
#define CLKRST_REG_SPI_CLK_DIV_UMSK                             (~(((1U<<CLKRST_REG_SPI_CLK_DIV_LEN)-1)<<CLKRST_REG_SPI_CLK_DIV_POS))

/* 0x14 : mm_clk_ctrl_peri2 */
#define CLKRST_MM_CLK_CTRL_PERI2_OFFSET                         (0x14)
#define CLKRST_REG_I2S0_CLK_DIV                                 CLKRST_REG_I2S0_CLK_DIV
#define CLKRST_REG_I2S0_CLK_DIV_POS                             (0U)
#define CLKRST_REG_I2S0_CLK_DIV_LEN                             (6U)
#define CLKRST_REG_I2S0_CLK_DIV_MSK                             (((1U<<CLKRST_REG_I2S0_CLK_DIV_LEN)-1)<<CLKRST_REG_I2S0_CLK_DIV_POS)
#define CLKRST_REG_I2S0_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_I2S0_CLK_DIV_LEN)-1)<<CLKRST_REG_I2S0_CLK_DIV_POS))
#define CLKRST_REG_I2S0_REF_CLK_OE                              CLKRST_REG_I2S0_REF_CLK_OE
#define CLKRST_REG_I2S0_REF_CLK_OE_POS                          (6U)
#define CLKRST_REG_I2S0_REF_CLK_OE_LEN                          (1U)
#define CLKRST_REG_I2S0_REF_CLK_OE_MSK                          (((1U<<CLKRST_REG_I2S0_REF_CLK_OE_LEN)-1)<<CLKRST_REG_I2S0_REF_CLK_OE_POS)
#define CLKRST_REG_I2S0_REF_CLK_OE_UMSK                         (~(((1U<<CLKRST_REG_I2S0_REF_CLK_OE_LEN)-1)<<CLKRST_REG_I2S0_REF_CLK_OE_POS))
#define CLKRST_REG_I2S0_CLK_EN                                  CLKRST_REG_I2S0_CLK_EN
#define CLKRST_REG_I2S0_CLK_EN_POS                              (7U)
#define CLKRST_REG_I2S0_CLK_EN_LEN                              (1U)
#define CLKRST_REG_I2S0_CLK_EN_MSK                              (((1U<<CLKRST_REG_I2S0_CLK_EN_LEN)-1)<<CLKRST_REG_I2S0_CLK_EN_POS)
#define CLKRST_REG_I2S0_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_I2S0_CLK_EN_LEN)-1)<<CLKRST_REG_I2S0_CLK_EN_POS))
#define CLKRST_REG_I2S1_CLK_DIV                                 CLKRST_REG_I2S1_CLK_DIV
#define CLKRST_REG_I2S1_CLK_DIV_POS                             (8U)
#define CLKRST_REG_I2S1_CLK_DIV_LEN                             (6U)
#define CLKRST_REG_I2S1_CLK_DIV_MSK                             (((1U<<CLKRST_REG_I2S1_CLK_DIV_LEN)-1)<<CLKRST_REG_I2S1_CLK_DIV_POS)
#define CLKRST_REG_I2S1_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_I2S1_CLK_DIV_LEN)-1)<<CLKRST_REG_I2S1_CLK_DIV_POS))
#define CLKRST_REG_I2S1_REF_CLK_OE                              CLKRST_REG_I2S1_REF_CLK_OE
#define CLKRST_REG_I2S1_REF_CLK_OE_POS                          (14U)
#define CLKRST_REG_I2S1_REF_CLK_OE_LEN                          (1U)
#define CLKRST_REG_I2S1_REF_CLK_OE_MSK                          (((1U<<CLKRST_REG_I2S1_REF_CLK_OE_LEN)-1)<<CLKRST_REG_I2S1_REF_CLK_OE_POS)
#define CLKRST_REG_I2S1_REF_CLK_OE_UMSK                         (~(((1U<<CLKRST_REG_I2S1_REF_CLK_OE_LEN)-1)<<CLKRST_REG_I2S1_REF_CLK_OE_POS))
#define CLKRST_REG_I2S1_CLK_EN                                  CLKRST_REG_I2S1_CLK_EN
#define CLKRST_REG_I2S1_CLK_EN_POS                              (15U)
#define CLKRST_REG_I2S1_CLK_EN_LEN                              (1U)
#define CLKRST_REG_I2S1_CLK_EN_MSK                              (((1U<<CLKRST_REG_I2S1_CLK_EN_LEN)-1)<<CLKRST_REG_I2S1_CLK_EN_POS)
#define CLKRST_REG_I2S1_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_I2S1_CLK_EN_LEN)-1)<<CLKRST_REG_I2S1_CLK_EN_POS))
#define CLKRST_REG_PDM0_CLK_DIV                                 CLKRST_REG_PDM0_CLK_DIV
#define CLKRST_REG_PDM0_CLK_DIV_POS                             (16U)
#define CLKRST_REG_PDM0_CLK_DIV_LEN                             (6U)
#define CLKRST_REG_PDM0_CLK_DIV_MSK                             (((1U<<CLKRST_REG_PDM0_CLK_DIV_LEN)-1)<<CLKRST_REG_PDM0_CLK_DIV_POS)
#define CLKRST_REG_PDM0_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_PDM0_CLK_DIV_LEN)-1)<<CLKRST_REG_PDM0_CLK_DIV_POS))
#define CLKRST_REG_PDM0_CLK_EN                                  CLKRST_REG_PDM0_CLK_EN
#define CLKRST_REG_PDM0_CLK_EN_POS                              (22U)
#define CLKRST_REG_PDM0_CLK_EN_LEN                              (1U)
#define CLKRST_REG_PDM0_CLK_EN_MSK                              (((1U<<CLKRST_REG_PDM0_CLK_EN_LEN)-1)<<CLKRST_REG_PDM0_CLK_EN_POS)
#define CLKRST_REG_PDM0_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_PDM0_CLK_EN_LEN)-1)<<CLKRST_REG_PDM0_CLK_EN_POS))
#define CLKRST_REG_PDM1_CLK_DIV                                 CLKRST_REG_PDM1_CLK_DIV
#define CLKRST_REG_PDM1_CLK_DIV_POS                             (24U)
#define CLKRST_REG_PDM1_CLK_DIV_LEN                             (6U)
#define CLKRST_REG_PDM1_CLK_DIV_MSK                             (((1U<<CLKRST_REG_PDM1_CLK_DIV_LEN)-1)<<CLKRST_REG_PDM1_CLK_DIV_POS)
#define CLKRST_REG_PDM1_CLK_DIV_UMSK                            (~(((1U<<CLKRST_REG_PDM1_CLK_DIV_LEN)-1)<<CLKRST_REG_PDM1_CLK_DIV_POS))
#define CLKRST_REG_PDM1_CLK_EN                                  CLKRST_REG_PDM1_CLK_EN
#define CLKRST_REG_PDM1_CLK_EN_POS                              (30U)
#define CLKRST_REG_PDM1_CLK_EN_LEN                              (1U)
#define CLKRST_REG_PDM1_CLK_EN_MSK                              (((1U<<CLKRST_REG_PDM1_CLK_EN_LEN)-1)<<CLKRST_REG_PDM1_CLK_EN_POS)
#define CLKRST_REG_PDM1_CLK_EN_UMSK                             (~(((1U<<CLKRST_REG_PDM1_CLK_EN_LEN)-1)<<CLKRST_REG_PDM1_CLK_EN_POS))

/* 0x20 : mm_clk_32k */
#define CLKRST_MM_CLK_32K_OFFSET                                (0x20)
#define CLKRST_REG_EN_DIG_32K_GEN                               CLKRST_REG_EN_DIG_32K_GEN
#define CLKRST_REG_EN_DIG_32K_GEN_POS                           (0U)
#define CLKRST_REG_EN_DIG_32K_GEN_LEN                           (1U)
#define CLKRST_REG_EN_DIG_32K_GEN_MSK                           (((1U<<CLKRST_REG_EN_DIG_32K_GEN_LEN)-1)<<CLKRST_REG_EN_DIG_32K_GEN_POS)
#define CLKRST_REG_EN_DIG_32K_GEN_UMSK                          (~(((1U<<CLKRST_REG_EN_DIG_32K_GEN_LEN)-1)<<CLKRST_REG_EN_DIG_32K_GEN_POS))
#define CLKRST_REG_EN_COMP_SAT                                  CLKRST_REG_EN_COMP_SAT
#define CLKRST_REG_EN_COMP_SAT_POS                              (1U)
#define CLKRST_REG_EN_COMP_SAT_LEN                              (1U)
#define CLKRST_REG_EN_COMP_SAT_MSK                              (((1U<<CLKRST_REG_EN_COMP_SAT_LEN)-1)<<CLKRST_REG_EN_COMP_SAT_POS)
#define CLKRST_REG_EN_COMP_SAT_UMSK                             (~(((1U<<CLKRST_REG_EN_COMP_SAT_LEN)-1)<<CLKRST_REG_EN_COMP_SAT_POS))
#define CLKRST_REG_512K_SEL                                     CLKRST_REG_512K_SEL
#define CLKRST_REG_512K_SEL_POS                                 (2U)
#define CLKRST_REG_512K_SEL_LEN                                 (2U)
#define CLKRST_REG_512K_SEL_MSK                                 (((1U<<CLKRST_REG_512K_SEL_LEN)-1)<<CLKRST_REG_512K_SEL_POS)
#define CLKRST_REG_512K_SEL_UMSK                                (~(((1U<<CLKRST_REG_512K_SEL_LEN)-1)<<CLKRST_REG_512K_SEL_POS))
#define CLKRST_REG_DIG_32K_CNT                                  CLKRST_REG_DIG_32K_CNT
#define CLKRST_REG_DIG_32K_CNT_POS                              (4U)
#define CLKRST_REG_DIG_32K_CNT_LEN                              (11U)
#define CLKRST_REG_DIG_32K_CNT_MSK                              (((1U<<CLKRST_REG_DIG_32K_CNT_LEN)-1)<<CLKRST_REG_DIG_32K_CNT_POS)
#define CLKRST_REG_DIG_32K_CNT_UMSK                             (~(((1U<<CLKRST_REG_DIG_32K_CNT_LEN)-1)<<CLKRST_REG_DIG_32K_CNT_POS))

/* 0x40 : mm_sw_sys_reset */
#define CLKRST_MM_SW_SYS_RESET_OFFSET                           (0x40)
#define CLKRST_REG_CTRL_SYS_RESET                               CLKRST_REG_CTRL_SYS_RESET
#define CLKRST_REG_CTRL_SYS_RESET_POS                           (0U)
#define CLKRST_REG_CTRL_SYS_RESET_LEN                           (1U)
#define CLKRST_REG_CTRL_SYS_RESET_MSK                           (((1U<<CLKRST_REG_CTRL_SYS_RESET_LEN)-1)<<CLKRST_REG_CTRL_SYS_RESET_POS)
#define CLKRST_REG_CTRL_SYS_RESET_UMSK                          (~(((1U<<CLKRST_REG_CTRL_SYS_RESET_LEN)-1)<<CLKRST_REG_CTRL_SYS_RESET_POS))
#define CLKRST_REG_CTRL_CPU_RESET                               CLKRST_REG_CTRL_CPU_RESET
#define CLKRST_REG_CTRL_CPU_RESET_POS                           (1U)
#define CLKRST_REG_CTRL_CPU_RESET_LEN                           (1U)
#define CLKRST_REG_CTRL_CPU_RESET_MSK                           (((1U<<CLKRST_REG_CTRL_CPU_RESET_LEN)-1)<<CLKRST_REG_CTRL_CPU_RESET_POS)
#define CLKRST_REG_CTRL_CPU_RESET_UMSK                          (~(((1U<<CLKRST_REG_CTRL_CPU_RESET_LEN)-1)<<CLKRST_REG_CTRL_CPU_RESET_POS))
#define CLKRST_REG_CTRL_PWRON_RST                               CLKRST_REG_CTRL_PWRON_RST
#define CLKRST_REG_CTRL_PWRON_RST_POS                           (2U)
#define CLKRST_REG_CTRL_PWRON_RST_LEN                           (1U)
#define CLKRST_REG_CTRL_PWRON_RST_MSK                           (((1U<<CLKRST_REG_CTRL_PWRON_RST_LEN)-1)<<CLKRST_REG_CTRL_PWRON_RST_POS)
#define CLKRST_REG_CTRL_PWRON_RST_UMSK                          (~(((1U<<CLKRST_REG_CTRL_PWRON_RST_LEN)-1)<<CLKRST_REG_CTRL_PWRON_RST_POS))
#define CLKRST_REG_CTRL_A5_CPU_RESET                            CLKRST_REG_CTRL_A5_CPU_RESET
#define CLKRST_REG_CTRL_A5_CPU_RESET_POS                        (8U)
#define CLKRST_REG_CTRL_A5_CPU_RESET_LEN                        (1U)
#define CLKRST_REG_CTRL_A5_CPU_RESET_MSK                        (((1U<<CLKRST_REG_CTRL_A5_CPU_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_CPU_RESET_POS)
#define CLKRST_REG_CTRL_A5_CPU_RESET_UMSK                       (~(((1U<<CLKRST_REG_CTRL_A5_CPU_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_CPU_RESET_POS))
#define CLKRST_REG_CTRL_A5_DBG_RESET                            CLKRST_REG_CTRL_A5_DBG_RESET
#define CLKRST_REG_CTRL_A5_DBG_RESET_POS                        (9U)
#define CLKRST_REG_CTRL_A5_DBG_RESET_LEN                        (1U)
#define CLKRST_REG_CTRL_A5_DBG_RESET_MSK                        (((1U<<CLKRST_REG_CTRL_A5_DBG_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_DBG_RESET_POS)
#define CLKRST_REG_CTRL_A5_DBG_RESET_UMSK                       (~(((1U<<CLKRST_REG_CTRL_A5_DBG_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_DBG_RESET_POS))
#define CLKRST_REG_CTRL_A5_PERI_RESET                           CLKRST_REG_CTRL_A5_PERI_RESET
#define CLKRST_REG_CTRL_A5_PERI_RESET_POS                       (10U)
#define CLKRST_REG_CTRL_A5_PERI_RESET_LEN                       (1U)
#define CLKRST_REG_CTRL_A5_PERI_RESET_MSK                       (((1U<<CLKRST_REG_CTRL_A5_PERI_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_PERI_RESET_POS)
#define CLKRST_REG_CTRL_A5_PERI_RESET_UMSK                      (~(((1U<<CLKRST_REG_CTRL_A5_PERI_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_PERI_RESET_POS))
#define CLKRST_REG_CTRL_A5_SCU_RESET                            CLKRST_REG_CTRL_A5_SCU_RESET
#define CLKRST_REG_CTRL_A5_SCU_RESET_POS                        (11U)
#define CLKRST_REG_CTRL_A5_SCU_RESET_LEN                        (1U)
#define CLKRST_REG_CTRL_A5_SCU_RESET_MSK                        (((1U<<CLKRST_REG_CTRL_A5_SCU_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_SCU_RESET_POS)
#define CLKRST_REG_CTRL_A5_SCU_RESET_UMSK                       (~(((1U<<CLKRST_REG_CTRL_A5_SCU_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_SCU_RESET_POS))
#define CLKRST_REG_CTRL_A5_WDT_RESET                            CLKRST_REG_CTRL_A5_WDT_RESET
#define CLKRST_REG_CTRL_A5_WDT_RESET_POS                        (12U)
#define CLKRST_REG_CTRL_A5_WDT_RESET_LEN                        (1U)
#define CLKRST_REG_CTRL_A5_WDT_RESET_MSK                        (((1U<<CLKRST_REG_CTRL_A5_WDT_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_WDT_RESET_POS)
#define CLKRST_REG_CTRL_A5_WDT_RESET_UMSK                       (~(((1U<<CLKRST_REG_CTRL_A5_WDT_RESET_LEN)-1)<<CLKRST_REG_CTRL_A5_WDT_RESET_POS))
#define CLKRST_REG_CTRL_E74_RESET                               CLKRST_REG_CTRL_E74_RESET
#define CLKRST_REG_CTRL_E74_RESET_POS                           (16U)
#define CLKRST_REG_CTRL_E74_RESET_LEN                           (1U)
#define CLKRST_REG_CTRL_E74_RESET_MSK                           (((1U<<CLKRST_REG_CTRL_E74_RESET_LEN)-1)<<CLKRST_REG_CTRL_E74_RESET_POS)
#define CLKRST_REG_CTRL_E74_RESET_UMSK                          (~(((1U<<CLKRST_REG_CTRL_E74_RESET_LEN)-1)<<CLKRST_REG_CTRL_E74_RESET_POS))

/* 0x44 : sw_reset_mm_peri */
#define CLKRST_SW_RESET_MM_PERI_OFFSET                          (0x44)
#define CLKRST_SWRST_MM_MISC                                    CLKRST_SWRST_MM_MISC
#define CLKRST_SWRST_MM_MISC_POS                                (0U)
#define CLKRST_SWRST_MM_MISC_LEN                                (1U)
#define CLKRST_SWRST_MM_MISC_MSK                                (((1U<<CLKRST_SWRST_MM_MISC_LEN)-1)<<CLKRST_SWRST_MM_MISC_POS)
#define CLKRST_SWRST_MM_MISC_UMSK                               (~(((1U<<CLKRST_SWRST_MM_MISC_LEN)-1)<<CLKRST_SWRST_MM_MISC_POS))
#define CLKRST_SWRST_DMA                                        CLKRST_SWRST_DMA
#define CLKRST_SWRST_DMA_POS                                    (1U)
#define CLKRST_SWRST_DMA_LEN                                    (1U)
#define CLKRST_SWRST_DMA_MSK                                    (((1U<<CLKRST_SWRST_DMA_LEN)-1)<<CLKRST_SWRST_DMA_POS)
#define CLKRST_SWRST_DMA_UMSK                                   (~(((1U<<CLKRST_SWRST_DMA_LEN)-1)<<CLKRST_SWRST_DMA_POS))
#define CLKRST_SWRST_UART                                       CLKRST_SWRST_UART
#define CLKRST_SWRST_UART_POS                                   (2U)
#define CLKRST_SWRST_UART_LEN                                   (1U)
#define CLKRST_SWRST_UART_MSK                                   (((1U<<CLKRST_SWRST_UART_LEN)-1)<<CLKRST_SWRST_UART_POS)
#define CLKRST_SWRST_UART_UMSK                                  (~(((1U<<CLKRST_SWRST_UART_LEN)-1)<<CLKRST_SWRST_UART_POS))
#define CLKRST_SWRST_I2CA                                       CLKRST_SWRST_I2CA
#define CLKRST_SWRST_I2CA_POS                                   (3U)
#define CLKRST_SWRST_I2CA_LEN                                   (1U)
#define CLKRST_SWRST_I2CA_MSK                                   (((1U<<CLKRST_SWRST_I2CA_LEN)-1)<<CLKRST_SWRST_I2CA_POS)
#define CLKRST_SWRST_I2CA_UMSK                                  (~(((1U<<CLKRST_SWRST_I2CA_LEN)-1)<<CLKRST_SWRST_I2CA_POS))
#define CLKRST_SWRST_I2CB                                       CLKRST_SWRST_I2CB
#define CLKRST_SWRST_I2CB_POS                                   (4U)
#define CLKRST_SWRST_I2CB_LEN                                   (1U)
#define CLKRST_SWRST_I2CB_MSK                                   (((1U<<CLKRST_SWRST_I2CB_LEN)-1)<<CLKRST_SWRST_I2CB_POS)
#define CLKRST_SWRST_I2CB_UMSK                                  (~(((1U<<CLKRST_SWRST_I2CB_LEN)-1)<<CLKRST_SWRST_I2CB_POS))
#define CLKRST_SWRST_PSRAMA                                     CLKRST_SWRST_PSRAMA
#define CLKRST_SWRST_PSRAMA_POS                                 (5U)
#define CLKRST_SWRST_PSRAMA_LEN                                 (1U)
#define CLKRST_SWRST_PSRAMA_MSK                                 (((1U<<CLKRST_SWRST_PSRAMA_LEN)-1)<<CLKRST_SWRST_PSRAMA_POS)
#define CLKRST_SWRST_PSRAMA_UMSK                                (~(((1U<<CLKRST_SWRST_PSRAMA_LEN)-1)<<CLKRST_SWRST_PSRAMA_POS))
#define CLKRST_SWRST_PSRAMB                                     CLKRST_SWRST_PSRAMB
#define CLKRST_SWRST_PSRAMB_POS                                 (6U)
#define CLKRST_SWRST_PSRAMB_LEN                                 (1U)
#define CLKRST_SWRST_PSRAMB_MSK                                 (((1U<<CLKRST_SWRST_PSRAMB_LEN)-1)<<CLKRST_SWRST_PSRAMB_POS)
#define CLKRST_SWRST_PSRAMB_UMSK                                (~(((1U<<CLKRST_SWRST_PSRAMB_LEN)-1)<<CLKRST_SWRST_PSRAMB_POS))
#define CLKRST_SWRST_SPI                                        CLKRST_SWRST_SPI
#define CLKRST_SWRST_SPI_POS                                    (8U)
#define CLKRST_SWRST_SPI_LEN                                    (1U)
#define CLKRST_SWRST_SPI_MSK                                    (((1U<<CLKRST_SWRST_SPI_LEN)-1)<<CLKRST_SWRST_SPI_POS)
#define CLKRST_SWRST_SPI_UMSK                                   (~(((1U<<CLKRST_SWRST_SPI_LEN)-1)<<CLKRST_SWRST_SPI_POS))
#define CLKRST_SWRST_CCI                                        CLKRST_SWRST_CCI
#define CLKRST_SWRST_CCI_POS                                    (9U)
#define CLKRST_SWRST_CCI_LEN                                    (1U)
#define CLKRST_SWRST_CCI_MSK                                    (((1U<<CLKRST_SWRST_CCI_LEN)-1)<<CLKRST_SWRST_CCI_POS)
#define CLKRST_SWRST_CCI_UMSK                                   (~(((1U<<CLKRST_SWRST_CCI_LEN)-1)<<CLKRST_SWRST_CCI_POS))
#define CLKRST_SWRST_I2S0                                       CLKRST_SWRST_I2S0
#define CLKRST_SWRST_I2S0_POS                                   (10U)
#define CLKRST_SWRST_I2S0_LEN                                   (1U)
#define CLKRST_SWRST_I2S0_MSK                                   (((1U<<CLKRST_SWRST_I2S0_LEN)-1)<<CLKRST_SWRST_I2S0_POS)
#define CLKRST_SWRST_I2S0_UMSK                                  (~(((1U<<CLKRST_SWRST_I2S0_LEN)-1)<<CLKRST_SWRST_I2S0_POS))
#define CLKRST_SWRST_I2S1                                       CLKRST_SWRST_I2S1
#define CLKRST_SWRST_I2S1_POS                                   (11U)
#define CLKRST_SWRST_I2S1_LEN                                   (1U)
#define CLKRST_SWRST_I2S1_MSK                                   (((1U<<CLKRST_SWRST_I2S1_LEN)-1)<<CLKRST_SWRST_I2S1_POS)
#define CLKRST_SWRST_I2S1_UMSK                                  (~(((1U<<CLKRST_SWRST_I2S1_LEN)-1)<<CLKRST_SWRST_I2S1_POS))
#define CLKRST_SWRST_PDM0                                       CLKRST_SWRST_PDM0
#define CLKRST_SWRST_PDM0_POS                                   (12U)
#define CLKRST_SWRST_PDM0_LEN                                   (1U)
#define CLKRST_SWRST_PDM0_MSK                                   (((1U<<CLKRST_SWRST_PDM0_LEN)-1)<<CLKRST_SWRST_PDM0_POS)
#define CLKRST_SWRST_PDM0_UMSK                                  (~(((1U<<CLKRST_SWRST_PDM0_LEN)-1)<<CLKRST_SWRST_PDM0_POS))
#define CLKRST_SWRST_PDM1                                       CLKRST_SWRST_PDM1
#define CLKRST_SWRST_PDM1_POS                                   (13U)
#define CLKRST_SWRST_PDM1_LEN                                   (1U)
#define CLKRST_SWRST_PDM1_MSK                                   (((1U<<CLKRST_SWRST_PDM1_LEN)-1)<<CLKRST_SWRST_PDM1_POS)
#define CLKRST_SWRST_PDM1_UMSK                                  (~(((1U<<CLKRST_SWRST_PDM1_LEN)-1)<<CLKRST_SWRST_PDM1_POS))
#define CLKRST_SWRST_SDH                                        CLKRST_SWRST_SDH
#define CLKRST_SWRST_SDH_POS                                    (16U)
#define CLKRST_SWRST_SDH_LEN                                    (1U)
#define CLKRST_SWRST_SDH_MSK                                    (((1U<<CLKRST_SWRST_SDH_LEN)-1)<<CLKRST_SWRST_SDH_POS)
#define CLKRST_SWRST_SDH_UMSK                                   (~(((1U<<CLKRST_SWRST_SDH_LEN)-1)<<CLKRST_SWRST_SDH_POS))
#define CLKRST_SWRST_ETH                                        CLKRST_SWRST_ETH
#define CLKRST_SWRST_ETH_POS                                    (24U)
#define CLKRST_SWRST_ETH_LEN                                    (1U)
#define CLKRST_SWRST_ETH_MSK                                    (((1U<<CLKRST_SWRST_ETH_LEN)-1)<<CLKRST_SWRST_ETH_POS)
#define CLKRST_SWRST_ETH_UMSK                                   (~(((1U<<CLKRST_SWRST_ETH_LEN)-1)<<CLKRST_SWRST_ETH_POS))

/* 0x48 : sw_reset_isp_sub */
#define CLKRST_SW_RESET_ISP_SUB_OFFSET                          (0x48)
#define CLKRST_SWRST_ISP_MISC                                   CLKRST_SWRST_ISP_MISC
#define CLKRST_SWRST_ISP_MISC_POS                               (0U)
#define CLKRST_SWRST_ISP_MISC_LEN                               (1U)
#define CLKRST_SWRST_ISP_MISC_MSK                               (((1U<<CLKRST_SWRST_ISP_MISC_LEN)-1)<<CLKRST_SWRST_ISP_MISC_POS)
#define CLKRST_SWRST_ISP_MISC_UMSK                              (~(((1U<<CLKRST_SWRST_ISP_MISC_LEN)-1)<<CLKRST_SWRST_ISP_MISC_POS))
#define CLKRST_SWRST_ISP_MAIN                                   CLKRST_SWRST_ISP_MAIN
#define CLKRST_SWRST_ISP_MAIN_POS                               (1U)
#define CLKRST_SWRST_ISP_MAIN_LEN                               (1U)
#define CLKRST_SWRST_ISP_MAIN_MSK                               (((1U<<CLKRST_SWRST_ISP_MAIN_LEN)-1)<<CLKRST_SWRST_ISP_MAIN_POS)
#define CLKRST_SWRST_ISP_MAIN_UMSK                              (~(((1U<<CLKRST_SWRST_ISP_MAIN_LEN)-1)<<CLKRST_SWRST_ISP_MAIN_POS))
#define CLKRST_SWRST_ISP_TSRC                                   CLKRST_SWRST_ISP_TSRC
#define CLKRST_SWRST_ISP_TSRC_POS                               (2U)
#define CLKRST_SWRST_ISP_TSRC_LEN                               (1U)
#define CLKRST_SWRST_ISP_TSRC_MSK                               (((1U<<CLKRST_SWRST_ISP_TSRC_LEN)-1)<<CLKRST_SWRST_ISP_TSRC_POS)
#define CLKRST_SWRST_ISP_TSRC_UMSK                              (~(((1U<<CLKRST_SWRST_ISP_TSRC_LEN)-1)<<CLKRST_SWRST_ISP_TSRC_POS))
#define CLKRST_SWRST_HDMI_TSRC                                  CLKRST_SWRST_HDMI_TSRC
#define CLKRST_SWRST_HDMI_TSRC_POS                              (3U)
#define CLKRST_SWRST_HDMI_TSRC_LEN                              (1U)
#define CLKRST_SWRST_HDMI_TSRC_MSK                              (((1U<<CLKRST_SWRST_HDMI_TSRC_LEN)-1)<<CLKRST_SWRST_HDMI_TSRC_POS)
#define CLKRST_SWRST_HDMI_TSRC_UMSK                             (~(((1U<<CLKRST_SWRST_HDMI_TSRC_LEN)-1)<<CLKRST_SWRST_HDMI_TSRC_POS))
#define CLKRST_SWRST_NR3D_CTRL                                  CLKRST_SWRST_NR3D_CTRL
#define CLKRST_SWRST_NR3D_CTRL_POS                              (4U)
#define CLKRST_SWRST_NR3D_CTRL_LEN                              (1U)
#define CLKRST_SWRST_NR3D_CTRL_MSK                              (((1U<<CLKRST_SWRST_NR3D_CTRL_LEN)-1)<<CLKRST_SWRST_NR3D_CTRL_POS)
#define CLKRST_SWRST_NR3D_CTRL_UMSK                             (~(((1U<<CLKRST_SWRST_NR3D_CTRL_LEN)-1)<<CLKRST_SWRST_NR3D_CTRL_POS))
#define CLKRST_SWRST_DVP2BUSA                                   CLKRST_SWRST_DVP2BUSA
#define CLKRST_SWRST_DVP2BUSA_POS                               (5U)
#define CLKRST_SWRST_DVP2BUSA_LEN                               (1U)
#define CLKRST_SWRST_DVP2BUSA_MSK                               (((1U<<CLKRST_SWRST_DVP2BUSA_LEN)-1)<<CLKRST_SWRST_DVP2BUSA_POS)
#define CLKRST_SWRST_DVP2BUSA_UMSK                              (~(((1U<<CLKRST_SWRST_DVP2BUSA_LEN)-1)<<CLKRST_SWRST_DVP2BUSA_POS))
#define CLKRST_SWRST_DVP2BUSB                                   CLKRST_SWRST_DVP2BUSB
#define CLKRST_SWRST_DVP2BUSB_POS                               (6U)
#define CLKRST_SWRST_DVP2BUSB_LEN                               (1U)
#define CLKRST_SWRST_DVP2BUSB_MSK                               (((1U<<CLKRST_SWRST_DVP2BUSB_LEN)-1)<<CLKRST_SWRST_DVP2BUSB_POS)
#define CLKRST_SWRST_DVP2BUSB_UMSK                              (~(((1U<<CLKRST_SWRST_DVP2BUSB_LEN)-1)<<CLKRST_SWRST_DVP2BUSB_POS))
#define CLKRST_SWRST_DVP2BUSC                                   CLKRST_SWRST_DVP2BUSC
#define CLKRST_SWRST_DVP2BUSC_POS                               (7U)
#define CLKRST_SWRST_DVP2BUSC_LEN                               (1U)
#define CLKRST_SWRST_DVP2BUSC_MSK                               (((1U<<CLKRST_SWRST_DVP2BUSC_LEN)-1)<<CLKRST_SWRST_DVP2BUSC_POS)
#define CLKRST_SWRST_DVP2BUSC_UMSK                              (~(((1U<<CLKRST_SWRST_DVP2BUSC_LEN)-1)<<CLKRST_SWRST_DVP2BUSC_POS))
#define CLKRST_SWRST_DVP2BUSD                                   CLKRST_SWRST_DVP2BUSD
#define CLKRST_SWRST_DVP2BUSD_POS                               (8U)
#define CLKRST_SWRST_DVP2BUSD_LEN                               (1U)
#define CLKRST_SWRST_DVP2BUSD_MSK                               (((1U<<CLKRST_SWRST_DVP2BUSD_LEN)-1)<<CLKRST_SWRST_DVP2BUSD_POS)
#define CLKRST_SWRST_DVP2BUSD_UMSK                              (~(((1U<<CLKRST_SWRST_DVP2BUSD_LEN)-1)<<CLKRST_SWRST_DVP2BUSD_POS))
#define CLKRST_SWRST_ISP_REG                                    CLKRST_SWRST_ISP_REG
#define CLKRST_SWRST_ISP_REG_POS                                (16U)
#define CLKRST_SWRST_ISP_REG_LEN                                (1U)
#define CLKRST_SWRST_ISP_REG_MSK                                (((1U<<CLKRST_SWRST_ISP_REG_LEN)-1)<<CLKRST_SWRST_ISP_REG_POS)
#define CLKRST_SWRST_ISP_REG_UMSK                               (~(((1U<<CLKRST_SWRST_ISP_REG_LEN)-1)<<CLKRST_SWRST_ISP_REG_POS))

/* 0x4C : sw_reset_codec_sub */
#define CLKRST_SW_RESET_CODEC_SUB_OFFSET                        (0x4C)
#define CLKRST_SWRST_CODEC_MISC                                 CLKRST_SWRST_CODEC_MISC
#define CLKRST_SWRST_CODEC_MISC_POS                             (0U)
#define CLKRST_SWRST_CODEC_MISC_LEN                             (1U)
#define CLKRST_SWRST_CODEC_MISC_MSK                             (((1U<<CLKRST_SWRST_CODEC_MISC_LEN)-1)<<CLKRST_SWRST_CODEC_MISC_POS)
#define CLKRST_SWRST_CODEC_MISC_UMSK                            (~(((1U<<CLKRST_SWRST_CODEC_MISC_LEN)-1)<<CLKRST_SWRST_CODEC_MISC_POS))
#define CLKRST_SWRST_MJPEG                                      CLKRST_SWRST_MJPEG
#define CLKRST_SWRST_MJPEG_POS                                  (1U)
#define CLKRST_SWRST_MJPEG_LEN                                  (1U)
#define CLKRST_SWRST_MJPEG_MSK                                  (((1U<<CLKRST_SWRST_MJPEG_LEN)-1)<<CLKRST_SWRST_MJPEG_POS)
#define CLKRST_SWRST_MJPEG_UMSK                                 (~(((1U<<CLKRST_SWRST_MJPEG_LEN)-1)<<CLKRST_SWRST_MJPEG_POS))
#define CLKRST_SWRST_H264                                       CLKRST_SWRST_H264
#define CLKRST_SWRST_H264_POS                                   (2U)
#define CLKRST_SWRST_H264_LEN                                   (1U)
#define CLKRST_SWRST_H264_MSK                                   (((1U<<CLKRST_SWRST_H264_LEN)-1)<<CLKRST_SWRST_H264_POS)
#define CLKRST_SWRST_H264_UMSK                                  (~(((1U<<CLKRST_SWRST_H264_LEN)-1)<<CLKRST_SWRST_H264_POS))
#define CLKRST_SWRST_MJPEGDEC                                   CLKRST_SWRST_MJPEGDEC
#define CLKRST_SWRST_MJPEGDEC_POS                               (3U)
#define CLKRST_SWRST_MJPEGDEC_LEN                               (1U)
#define CLKRST_SWRST_MJPEGDEC_MSK                               (((1U<<CLKRST_SWRST_MJPEG_LEN)-1)<<CLKRST_SWRST_MJPEG_POS)
#define CLKRST_SWRST_MJPEGDEC_UMSK                              (~(((1U<<CLKRST_SWRST_MJPEG_LEN)-1)<<CLKRST_SWRST_MJPEG_POS))
#define CLKRST_SWRST_NPU                                        CLKRST_SWRST_NPU
#define CLKRST_SWRST_NPU_POS                                    (4U)
#define CLKRST_SWRST_NPU_LEN                                    (1U)
#define CLKRST_SWRST_NPU_MSK                                    (((1U<<CLKRST_SWRST_NPU_LEN)-1)<<CLKRST_SWRST_NPU_POS)
#define CLKRST_SWRST_NPU_UMSK                                   (~(((1U<<CLKRST_SWRST_NPU_LEN)-1)<<CLKRST_SWRST_NPU_POS))

#define CLKRST_SWRST_VRAM                                       CLKRST_SWRST_VRAM
#define CLKRST_SWRST_VRAM_POS                                   (16U)
#define CLKRST_SWRST_VRAM_LEN                                   (1U)
#define CLKRST_SWRST_VRAM_MSK                                   (((1U<<CLKRST_SWRST_VRAM_LEN)-1)<<CLKRST_SWRST_VRAM_POS)
#define CLKRST_SWRST_VRAM_UMSK                                  (~(((1U<<CLKRST_SWRST_VRAM_LEN)-1)<<CLKRST_SWRST_VRAM_POS))

/* 0x50 : image_sensor_ctrl */
#define CLKRST_IMAGE_SENSOR_CTRL_OFFSET                         (0x50)
#define CLKRST_RG_IS_RST_N                                      CLKRST_RG_IS_RST_N
#define CLKRST_RG_IS_RST_N_POS                                  (0U)
#define CLKRST_RG_IS_RST_N_LEN                                  (1U)
#define CLKRST_RG_IS_RST_N_MSK                                  (((1U<<CLKRST_RG_IS_RST_N_LEN)-1)<<CLKRST_RG_IS_RST_N_POS)
#define CLKRST_RG_IS_RST_N_UMSK                                 (~(((1U<<CLKRST_RG_IS_RST_N_LEN)-1)<<CLKRST_RG_IS_RST_N_POS))

/* 0x60 : sw_reset_mask */
#define CLKRST_SW_RESET_MASK_OFFSET                             (0x60)
#define CLKRST_REG_RST_MASK_A5SYS_TO_SYS                        CLKRST_REG_RST_MASK_A5SYS_TO_SYS
#define CLKRST_REG_RST_MASK_A5SYS_TO_SYS_POS                    (0U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_SYS_LEN                    (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_SYS_MSK                    (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_SYS_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_SYS_UMSK                   (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_SYS_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_SYS                        CLKRST_REG_RST_MASK_A5WDT_TO_SYS
#define CLKRST_REG_RST_MASK_A5WDT_TO_SYS_POS                    (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_SYS_LEN                    (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_SYS_MSK                    (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_SYS_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_SYS_UMSK                   (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_SYS_POS))
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU                      CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_POS                  (2U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5CPU_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU                      CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_POS                  (3U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5CPU_POS))
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG                      CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_POS                  (4U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5DBG_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG                      CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_POS                  (5U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5DBG_POS))
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI                     CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_POS                 (6U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_LEN                 (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_MSK                 (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_UMSK                (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5PERI_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI                     CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_POS                 (7U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_LEN                 (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_MSK                 (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_UMSK                (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5PERI_POS))
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU                      CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_POS                  (8U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5SCU_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU                      CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_POS                  (9U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5SCU_POS))
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT                      CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_POS                  (10U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_POS)
#define CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_LEN)-1)<<CLKRST_REG_RST_MASK_A5SYS_TO_A5WDT_POS))
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT                      CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_POS                  (11U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_LEN                  (1U)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_MSK                  (((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_POS)
#define CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_UMSK                 (~(((1U<<CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_LEN)-1)<<CLKRST_REG_RST_MASK_A5WDT_TO_A5WDT_POS))
#define CLKRST_REG_RST_MASK_E74_TO_SYS                          CLKRST_REG_RST_MASK_E74_TO_SYS
#define CLKRST_REG_RST_MASK_E74_TO_SYS_POS                      (12U)
#define CLKRST_REG_RST_MASK_E74_TO_SYS_LEN                      (1U)
#define CLKRST_REG_RST_MASK_E74_TO_SYS_MSK                      (((1U<<CLKRST_REG_RST_MASK_E74_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_E74_TO_SYS_POS)
#define CLKRST_REG_RST_MASK_E74_TO_SYS_UMSK                     (~(((1U<<CLKRST_REG_RST_MASK_E74_TO_SYS_LEN)-1)<<CLKRST_REG_RST_MASK_E74_TO_SYS_POS))
#define CLKRST_REG_RST_MASK_E74_TO_E74                          CLKRST_REG_RST_MASK_E74_TO_E74
#define CLKRST_REG_RST_MASK_E74_TO_E74_POS                      (13U)
#define CLKRST_REG_RST_MASK_E74_TO_E74_LEN                      (1U)
#define CLKRST_REG_RST_MASK_E74_TO_E74_MSK                      (((1U<<CLKRST_REG_RST_MASK_E74_TO_E74_LEN)-1)<<CLKRST_REG_RST_MASK_E74_TO_E74_POS)
#define CLKRST_REG_RST_MASK_E74_TO_E74_UMSK                     (~(((1U<<CLKRST_REG_RST_MASK_E74_TO_E74_LEN)-1)<<CLKRST_REG_RST_MASK_E74_TO_E74_POS))

/* 0x80 : SYS_TICK_CFG */
#define CLKRST_SYS_TICK_CFG_OFFSET                              (0x80)
#define CLKRST_STCALIB                                          CLKRST_STCALIB
#define CLKRST_STCALIB_POS                                      (0U)
#define CLKRST_STCALIB_LEN                                      (26U)
#define CLKRST_STCALIB_MSK                                      (((1U<<CLKRST_STCALIB_LEN)-1)<<CLKRST_STCALIB_POS)
#define CLKRST_STCALIB_UMSK                                     (~(((1U<<CLKRST_STCALIB_LEN)-1)<<CLKRST_STCALIB_POS))

/* 0x100 : clkpll register 1 */
#define CLKRST_CLKIP1_OFFSET                                    (0x100)
#define CLKRST_CLKPLL_PPU                                       CLKRST_CLKPLL_PPU
#define CLKRST_CLKPLL_PPU_POS                                   (0U)
#define CLKRST_CLKPLL_PPU_LEN                                   (1U)
#define CLKRST_CLKPLL_PPU_MSK                                   (((1U<<CLKRST_CLKPLL_PPU_LEN)-1)<<CLKRST_CLKPLL_PPU_POS)
#define CLKRST_CLKPLL_PPU_UMSK                                  (~(((1U<<CLKRST_CLKPLL_PPU_LEN)-1)<<CLKRST_CLKPLL_PPU_POS))
#define CLKRST_CLKPLL_PU                                        CLKRST_CLKPLL_PU
#define CLKRST_CLKPLL_PU_POS                                    (1U)
#define CLKRST_CLKPLL_PU_LEN                                    (1U)
#define CLKRST_CLKPLL_PU_MSK                                    (((1U<<CLKRST_CLKPLL_PU_LEN)-1)<<CLKRST_CLKPLL_PU_POS)
#define CLKRST_CLKPLL_PU_UMSK                                   (~(((1U<<CLKRST_CLKPLL_PU_LEN)-1)<<CLKRST_CLKPLL_PU_POS))
#define CLKRST_CLKPLL2_PPU                                      CLKRST_CLKPLL2_PPU
#define CLKRST_CLKPLL2_PPU_POS                                  (2U)
#define CLKRST_CLKPLL2_PPU_LEN                                  (1U)
#define CLKRST_CLKPLL2_PPU_MSK                                  (((1U<<CLKRST_CLKPLL2_PPU_LEN)-1)<<CLKRST_CLKPLL2_PPU_POS)
#define CLKRST_CLKPLL2_PPU_UMSK                                 (~(((1U<<CLKRST_CLKPLL2_PPU_LEN)-1)<<CLKRST_CLKPLL2_PPU_POS))
#define CLKRST_CLKPLL2_PU                                       CLKRST_CLKPLL2_PU
#define CLKRST_CLKPLL2_PU_POS                                   (3U)
#define CLKRST_CLKPLL2_PU_LEN                                   (1U)
#define CLKRST_CLKPLL2_PU_MSK                                   (((1U<<CLKRST_CLKPLL2_PU_LEN)-1)<<CLKRST_CLKPLL2_PU_POS)
#define CLKRST_CLKPLL2_PU_UMSK                                  (~(((1U<<CLKRST_CLKPLL2_PU_LEN)-1)<<CLKRST_CLKPLL2_PU_POS))
#define CLKRST_TEN_CLKPLL                                       CLKRST_TEN_CLKPLL
#define CLKRST_TEN_CLKPLL_POS                                   (4U)
#define CLKRST_TEN_CLKPLL_LEN                                   (3U)
#define CLKRST_TEN_CLKPLL_MSK                                   (((1U<<CLKRST_TEN_CLKPLL_LEN)-1)<<CLKRST_TEN_CLKPLL_POS)
#define CLKRST_TEN_CLKPLL_UMSK                                  (~(((1U<<CLKRST_TEN_CLKPLL_LEN)-1)<<CLKRST_TEN_CLKPLL_POS))
#define CLKRST_TEN_CLKPLL2                                      CLKRST_TEN_CLKPLL2
#define CLKRST_TEN_CLKPLL2_POS                                  (8U)
#define CLKRST_TEN_CLKPLL2_LEN                                  (3U)
#define CLKRST_TEN_CLKPLL2_MSK                                  (((1U<<CLKRST_TEN_CLKPLL2_LEN)-1)<<CLKRST_TEN_CLKPLL2_POS)
#define CLKRST_TEN_CLKPLL2_UMSK                                 (~(((1U<<CLKRST_TEN_CLKPLL2_LEN)-1)<<CLKRST_TEN_CLKPLL2_POS))
#define CLKRST_DTEST_CLKIP_EN                                   CLKRST_DTEST_CLKIP_EN
#define CLKRST_DTEST_CLKIP_EN_POS                               (12U)
#define CLKRST_DTEST_CLKIP_EN_LEN                               (2U)
#define CLKRST_DTEST_CLKIP_EN_MSK                               (((1U<<CLKRST_DTEST_CLKIP_EN_LEN)-1)<<CLKRST_DTEST_CLKIP_EN_POS)
#define CLKRST_DTEST_CLKIP_EN_UMSK                              (~(((1U<<CLKRST_DTEST_CLKIP_EN_LEN)-1)<<CLKRST_DTEST_CLKIP_EN_POS))
#define CLKRST_DTEST_CLK25M_EN                                  CLKRST_DTEST_CLK25M_EN
#define CLKRST_DTEST_CLK25M_EN_POS                              (14U)
#define CLKRST_DTEST_CLK25M_EN_LEN                              (1U)
#define CLKRST_DTEST_CLK25M_EN_MSK                              (((1U<<CLKRST_DTEST_CLK25M_EN_LEN)-1)<<CLKRST_DTEST_CLK25M_EN_POS)
#define CLKRST_DTEST_CLK25M_EN_UMSK                             (~(((1U<<CLKRST_DTEST_CLK25M_EN_LEN)-1)<<CLKRST_DTEST_CLK25M_EN_POS))
#define CLKRST_DTEST_PULLDOWN                                   CLKRST_DTEST_PULLDOWN
#define CLKRST_DTEST_PULLDOWN_POS                               (15U)
#define CLKRST_DTEST_PULLDOWN_LEN                               (1U)
#define CLKRST_DTEST_PULLDOWN_MSK                               (((1U<<CLKRST_DTEST_PULLDOWN_LEN)-1)<<CLKRST_DTEST_PULLDOWN_POS)
#define CLKRST_DTEST_PULLDOWN_UMSK                              (~(((1U<<CLKRST_DTEST_PULLDOWN_LEN)-1)<<CLKRST_DTEST_PULLDOWN_POS))

/* 0x104 : clkpll register 2 */
#define CLKRST_CLKIP2_OFFSET                                    (0x104)
#define CLKRST_CLKPLL_PU_VCON_CMP                               CLKRST_CLKPLL_PU_VCON_CMP
#define CLKRST_CLKPLL_PU_VCON_CMP_POS                           (0U)
#define CLKRST_CLKPLL_PU_VCON_CMP_LEN                           (1U)
#define CLKRST_CLKPLL_PU_VCON_CMP_MSK                           (((1U<<CLKRST_CLKPLL_PU_VCON_CMP_LEN)-1)<<CLKRST_CLKPLL_PU_VCON_CMP_POS)
#define CLKRST_CLKPLL_PU_VCON_CMP_UMSK                          (~(((1U<<CLKRST_CLKPLL_PU_VCON_CMP_LEN)-1)<<CLKRST_CLKPLL_PU_VCON_CMP_POS))
#define CLKRST_CLKPLL_PU_PFD                                    CLKRST_CLKPLL_PU_PFD
#define CLKRST_CLKPLL_PU_PFD_POS                                (1U)
#define CLKRST_CLKPLL_PU_PFD_LEN                                (1U)
#define CLKRST_CLKPLL_PU_PFD_MSK                                (((1U<<CLKRST_CLKPLL_PU_PFD_LEN)-1)<<CLKRST_CLKPLL_PU_PFD_POS)
#define CLKRST_CLKPLL_PU_PFD_UMSK                               (~(((1U<<CLKRST_CLKPLL_PU_PFD_LEN)-1)<<CLKRST_CLKPLL_PU_PFD_POS))
#define CLKRST_CLKPLL_PU_CP                                     CLKRST_CLKPLL_PU_CP
#define CLKRST_CLKPLL_PU_CP_POS                                 (2U)
#define CLKRST_CLKPLL_PU_CP_LEN                                 (1U)
#define CLKRST_CLKPLL_PU_CP_MSK                                 (((1U<<CLKRST_CLKPLL_PU_CP_LEN)-1)<<CLKRST_CLKPLL_PU_CP_POS)
#define CLKRST_CLKPLL_PU_CP_UMSK                                (~(((1U<<CLKRST_CLKPLL_PU_CP_LEN)-1)<<CLKRST_CLKPLL_PU_CP_POS))
#define CLKRST_CLKPLL_VCON_FORCE_EN                             CLKRST_CLKPLL_VCON_FORCE_EN
#define CLKRST_CLKPLL_VCON_FORCE_EN_POS                         (3U)
#define CLKRST_CLKPLL_VCON_FORCE_EN_LEN                         (1U)
#define CLKRST_CLKPLL_VCON_FORCE_EN_MSK                         (((1U<<CLKRST_CLKPLL_VCON_FORCE_EN_LEN)-1)<<CLKRST_CLKPLL_VCON_FORCE_EN_POS)
#define CLKRST_CLKPLL_VCON_FORCE_EN_UMSK                        (~(((1U<<CLKRST_CLKPLL_VCON_FORCE_EN_LEN)-1)<<CLKRST_CLKPLL_VCON_FORCE_EN_POS))
#define CLKRST_CLKPLL_CP3_SCALE                                 CLKRST_CLKPLL_CP3_SCALE
#define CLKRST_CLKPLL_CP3_SCALE_POS                             (4U)
#define CLKRST_CLKPLL_CP3_SCALE_LEN                             (2U)
#define CLKRST_CLKPLL_CP3_SCALE_MSK                             (((1U<<CLKRST_CLKPLL_CP3_SCALE_LEN)-1)<<CLKRST_CLKPLL_CP3_SCALE_POS)
#define CLKRST_CLKPLL_CP3_SCALE_UMSK                            (~(((1U<<CLKRST_CLKPLL_CP3_SCALE_LEN)-1)<<CLKRST_CLKPLL_CP3_SCALE_POS))
#define CLKRST_CLKPLL_RES_SCALE                                 CLKRST_CLKPLL_RES_SCALE
#define CLKRST_CLKPLL_RES_SCALE_POS                             (6U)
#define CLKRST_CLKPLL_RES_SCALE_LEN                             (3U)
#define CLKRST_CLKPLL_RES_SCALE_MSK                             (((1U<<CLKRST_CLKPLL_RES_SCALE_LEN)-1)<<CLKRST_CLKPLL_RES_SCALE_POS)
#define CLKRST_CLKPLL_RES_SCALE_UMSK                            (~(((1U<<CLKRST_CLKPLL_RES_SCALE_LEN)-1)<<CLKRST_CLKPLL_RES_SCALE_POS))
#define CLKRST_CLKPLL_REFDIV_RATIO                              CLKRST_CLKPLL_REFDIV_RATIO
#define CLKRST_CLKPLL_REFDIV_RATIO_POS                          (9U)
#define CLKRST_CLKPLL_REFDIV_RATIO_LEN                          (4U)
#define CLKRST_CLKPLL_REFDIV_RATIO_MSK                          (((1U<<CLKRST_CLKPLL_REFDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL_REFDIV_RATIO_POS)
#define CLKRST_CLKPLL_REFDIV_RATIO_UMSK                         (~(((1U<<CLKRST_CLKPLL_REFDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL_REFDIV_RATIO_POS))
#define CLKRST_CLKPLL_FBDIV_RATIO                               CLKRST_CLKPLL_FBDIV_RATIO
#define CLKRST_CLKPLL_FBDIV_RATIO_POS                           (13U)
#define CLKRST_CLKPLL_FBDIV_RATIO_LEN                           (10U)
#define CLKRST_CLKPLL_FBDIV_RATIO_MSK                           (((1U<<CLKRST_CLKPLL_FBDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL_FBDIV_RATIO_POS)
#define CLKRST_CLKPLL_FBDIV_RATIO_UMSK                          (~(((1U<<CLKRST_CLKPLL_FBDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL_FBDIV_RATIO_POS))
#define CLKRST_CLKPLL_ICP                                       CLKRST_CLKPLL_ICP
#define CLKRST_CLKPLL_ICP_POS                                   (23U)
#define CLKRST_CLKPLL_ICP_LEN                                   (3U)
#define CLKRST_CLKPLL_ICP_MSK                                   (((1U<<CLKRST_CLKPLL_ICP_LEN)-1)<<CLKRST_CLKPLL_ICP_POS)
#define CLKRST_CLKPLL_ICP_UMSK                                  (~(((1U<<CLKRST_CLKPLL_ICP_LEN)-1)<<CLKRST_CLKPLL_ICP_POS))
#define CLKRST_CLKPLL_SHRTR                                     CLKRST_CLKPLL_SHRTR
#define CLKRST_CLKPLL_SHRTR_POS                                 (26U)
#define CLKRST_CLKPLL_SHRTR_LEN                                 (1U)
#define CLKRST_CLKPLL_SHRTR_MSK                                 (((1U<<CLKRST_CLKPLL_SHRTR_LEN)-1)<<CLKRST_CLKPLL_SHRTR_POS)
#define CLKRST_CLKPLL_SHRTR_UMSK                                (~(((1U<<CLKRST_CLKPLL_SHRTR_LEN)-1)<<CLKRST_CLKPLL_SHRTR_POS))
#define CLKRST_CLKPLL_RINGCAP_EN                                CLKRST_CLKPLL_RINGCAP_EN
#define CLKRST_CLKPLL_RINGCAP_EN_POS                            (27U)
#define CLKRST_CLKPLL_RINGCAP_EN_LEN                            (1U)
#define CLKRST_CLKPLL_RINGCAP_EN_MSK                            (((1U<<CLKRST_CLKPLL_RINGCAP_EN_LEN)-1)<<CLKRST_CLKPLL_RINGCAP_EN_POS)
#define CLKRST_CLKPLL_RINGCAP_EN_UMSK                           (~(((1U<<CLKRST_CLKPLL_RINGCAP_EN_LEN)-1)<<CLKRST_CLKPLL_RINGCAP_EN_POS))
#define CLKRST_CLKPLL_RESET                                     CLKRST_CLKPLL_RESET
#define CLKRST_CLKPLL_RESET_POS                                 (28U)
#define CLKRST_CLKPLL_RESET_LEN                                 (1U)
#define CLKRST_CLKPLL_RESET_MSK                                 (((1U<<CLKRST_CLKPLL_RESET_LEN)-1)<<CLKRST_CLKPLL_RESET_POS)
#define CLKRST_CLKPLL_RESET_UMSK                                (~(((1U<<CLKRST_CLKPLL_RESET_LEN)-1)<<CLKRST_CLKPLL_RESET_POS))

/* 0x108 : clkpll register 3 */
#define CLKRST_CLKIP3_OFFSET                                    (0x108)
#define CLKRST_CLKPLL_VCTRL_CMP                                 CLKRST_CLKPLL_VCTRL_CMP
#define CLKRST_CLKPLL_VCTRL_CMP_POS                             (0U)
#define CLKRST_CLKPLL_VCTRL_CMP_LEN                             (2U)
#define CLKRST_CLKPLL_VCTRL_CMP_MSK                             (((1U<<CLKRST_CLKPLL_VCTRL_CMP_LEN)-1)<<CLKRST_CLKPLL_VCTRL_CMP_POS)
#define CLKRST_CLKPLL_VCTRL_CMP_UMSK                            (~(((1U<<CLKRST_CLKPLL_VCTRL_CMP_LEN)-1)<<CLKRST_CLKPLL_VCTRL_CMP_POS))
#define CLKRST_CLKPLL_VCTRL_RANGE                               CLKRST_CLKPLL_VCTRL_RANGE
#define CLKRST_CLKPLL_VCTRL_RANGE_POS                           (2U)
#define CLKRST_CLKPLL_VCTRL_RANGE_LEN                           (2U)
#define CLKRST_CLKPLL_VCTRL_RANGE_MSK                           (((1U<<CLKRST_CLKPLL_VCTRL_RANGE_LEN)-1)<<CLKRST_CLKPLL_VCTRL_RANGE_POS)
#define CLKRST_CLKPLL_VCTRL_RANGE_UMSK                          (~(((1U<<CLKRST_CLKPLL_VCTRL_RANGE_LEN)-1)<<CLKRST_CLKPLL_VCTRL_RANGE_POS))
#define CLKRST_CLKPLL_V2I_R_CAL                                 CLKRST_CLKPLL_V2I_R_CAL
#define CLKRST_CLKPLL_V2I_R_CAL_POS                             (4U)
#define CLKRST_CLKPLL_V2I_R_CAL_LEN                             (4U)
#define CLKRST_CLKPLL_V2I_R_CAL_MSK                             (((1U<<CLKRST_CLKPLL_V2I_R_CAL_LEN)-1)<<CLKRST_CLKPLL_V2I_R_CAL_POS)
#define CLKRST_CLKPLL_V2I_R_CAL_UMSK                            (~(((1U<<CLKRST_CLKPLL_V2I_R_CAL_LEN)-1)<<CLKRST_CLKPLL_V2I_R_CAL_POS))
#define CLKRST_CLKPLL_V2I_IDAC                                  CLKRST_CLKPLL_V2I_IDAC
#define CLKRST_CLKPLL_V2I_IDAC_POS                              (8U)
#define CLKRST_CLKPLL_V2I_IDAC_LEN                              (4U)
#define CLKRST_CLKPLL_V2I_IDAC_MSK                              (((1U<<CLKRST_CLKPLL_V2I_IDAC_LEN)-1)<<CLKRST_CLKPLL_V2I_IDAC_POS)
#define CLKRST_CLKPLL_V2I_IDAC_UMSK                             (~(((1U<<CLKRST_CLKPLL_V2I_IDAC_LEN)-1)<<CLKRST_CLKPLL_V2I_IDAC_POS))
#define CLKRST_CLKPLL_CP_OPAMP_EN                               CLKRST_CLKPLL_CP_OPAMP_EN
#define CLKRST_CLKPLL_CP_OPAMP_EN_POS                           (12U)
#define CLKRST_CLKPLL_CP_OPAMP_EN_LEN                           (1U)
#define CLKRST_CLKPLL_CP_OPAMP_EN_MSK                           (((1U<<CLKRST_CLKPLL_CP_OPAMP_EN_LEN)-1)<<CLKRST_CLKPLL_CP_OPAMP_EN_POS)
#define CLKRST_CLKPLL_CP_OPAMP_EN_UMSK                          (~(((1U<<CLKRST_CLKPLL_CP_OPAMP_EN_LEN)-1)<<CLKRST_CLKPLL_CP_OPAMP_EN_POS))

/* 0x10C : clkpll register 4 */
#define CLKRST_CLKIP4_OFFSET                                    (0x10C)
#define CLKRST_CLKPLL2_PU_VCON_CMP                              CLKRST_CLKPLL2_PU_VCON_CMP
#define CLKRST_CLKPLL2_PU_VCON_CMP_POS                          (0U)
#define CLKRST_CLKPLL2_PU_VCON_CMP_LEN                          (1U)
#define CLKRST_CLKPLL2_PU_VCON_CMP_MSK                          (((1U<<CLKRST_CLKPLL2_PU_VCON_CMP_LEN)-1)<<CLKRST_CLKPLL2_PU_VCON_CMP_POS)
#define CLKRST_CLKPLL2_PU_VCON_CMP_UMSK                         (~(((1U<<CLKRST_CLKPLL2_PU_VCON_CMP_LEN)-1)<<CLKRST_CLKPLL2_PU_VCON_CMP_POS))
#define CLKRST_CLKPLL2_PU_PFD                                   CLKRST_CLKPLL2_PU_PFD
#define CLKRST_CLKPLL2_PU_PFD_POS                               (1U)
#define CLKRST_CLKPLL2_PU_PFD_LEN                               (1U)
#define CLKRST_CLKPLL2_PU_PFD_MSK                               (((1U<<CLKRST_CLKPLL2_PU_PFD_LEN)-1)<<CLKRST_CLKPLL2_PU_PFD_POS)
#define CLKRST_CLKPLL2_PU_PFD_UMSK                              (~(((1U<<CLKRST_CLKPLL2_PU_PFD_LEN)-1)<<CLKRST_CLKPLL2_PU_PFD_POS))
#define CLKRST_CLKPLL2_PU_CP                                    CLKRST_CLKPLL2_PU_CP
#define CLKRST_CLKPLL2_PU_CP_POS                                (2U)
#define CLKRST_CLKPLL2_PU_CP_LEN                                (1U)
#define CLKRST_CLKPLL2_PU_CP_MSK                                (((1U<<CLKRST_CLKPLL2_PU_CP_LEN)-1)<<CLKRST_CLKPLL2_PU_CP_POS)
#define CLKRST_CLKPLL2_PU_CP_UMSK                               (~(((1U<<CLKRST_CLKPLL2_PU_CP_LEN)-1)<<CLKRST_CLKPLL2_PU_CP_POS))
#define CLKRST_CLKPLL2_VCON_FORCE_EN                            CLKRST_CLKPLL2_VCON_FORCE_EN
#define CLKRST_CLKPLL2_VCON_FORCE_EN_POS                        (3U)
#define CLKRST_CLKPLL2_VCON_FORCE_EN_LEN                        (1U)
#define CLKRST_CLKPLL2_VCON_FORCE_EN_MSK                        (((1U<<CLKRST_CLKPLL2_VCON_FORCE_EN_LEN)-1)<<CLKRST_CLKPLL2_VCON_FORCE_EN_POS)
#define CLKRST_CLKPLL2_VCON_FORCE_EN_UMSK                       (~(((1U<<CLKRST_CLKPLL2_VCON_FORCE_EN_LEN)-1)<<CLKRST_CLKPLL2_VCON_FORCE_EN_POS))
#define CLKRST_CLKPLL2_CP3_SCALE                                CLKRST_CLKPLL2_CP3_SCALE
#define CLKRST_CLKPLL2_CP3_SCALE_POS                            (4U)
#define CLKRST_CLKPLL2_CP3_SCALE_LEN                            (2U)
#define CLKRST_CLKPLL2_CP3_SCALE_MSK                            (((1U<<CLKRST_CLKPLL2_CP3_SCALE_LEN)-1)<<CLKRST_CLKPLL2_CP3_SCALE_POS)
#define CLKRST_CLKPLL2_CP3_SCALE_UMSK                           (~(((1U<<CLKRST_CLKPLL2_CP3_SCALE_LEN)-1)<<CLKRST_CLKPLL2_CP3_SCALE_POS))
#define CLKRST_CLKPLL2_RES_SCALE                                CLKRST_CLKPLL2_RES_SCALE
#define CLKRST_CLKPLL2_RES_SCALE_POS                            (6U)
#define CLKRST_CLKPLL2_RES_SCALE_LEN                            (3U)
#define CLKRST_CLKPLL2_RES_SCALE_MSK                            (((1U<<CLKRST_CLKPLL2_RES_SCALE_LEN)-1)<<CLKRST_CLKPLL2_RES_SCALE_POS)
#define CLKRST_CLKPLL2_RES_SCALE_UMSK                           (~(((1U<<CLKRST_CLKPLL2_RES_SCALE_LEN)-1)<<CLKRST_CLKPLL2_RES_SCALE_POS))
#define CLKRST_CLKPLL2_REFDIV_RATIO                             CLKRST_CLKPLL2_REFDIV_RATIO
#define CLKRST_CLKPLL2_REFDIV_RATIO_POS                         (9U)
#define CLKRST_CLKPLL2_REFDIV_RATIO_LEN                         (4U)
#define CLKRST_CLKPLL2_REFDIV_RATIO_MSK                         (((1U<<CLKRST_CLKPLL2_REFDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL2_REFDIV_RATIO_POS)
#define CLKRST_CLKPLL2_REFDIV_RATIO_UMSK                        (~(((1U<<CLKRST_CLKPLL2_REFDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL2_REFDIV_RATIO_POS))
#define CLKRST_CLKPLL2_FBDIV_RATIO                              CLKRST_CLKPLL2_FBDIV_RATIO
#define CLKRST_CLKPLL2_FBDIV_RATIO_POS                          (13U)
#define CLKRST_CLKPLL2_FBDIV_RATIO_LEN                          (10U)
#define CLKRST_CLKPLL2_FBDIV_RATIO_MSK                          (((1U<<CLKRST_CLKPLL2_FBDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL2_FBDIV_RATIO_POS)
#define CLKRST_CLKPLL2_FBDIV_RATIO_UMSK                         (~(((1U<<CLKRST_CLKPLL2_FBDIV_RATIO_LEN)-1)<<CLKRST_CLKPLL2_FBDIV_RATIO_POS))
#define CLKRST_CLKPLL2_ICP                                      CLKRST_CLKPLL2_ICP
#define CLKRST_CLKPLL2_ICP_POS                                  (23U)
#define CLKRST_CLKPLL2_ICP_LEN                                  (3U)
#define CLKRST_CLKPLL2_ICP_MSK                                  (((1U<<CLKRST_CLKPLL2_ICP_LEN)-1)<<CLKRST_CLKPLL2_ICP_POS)
#define CLKRST_CLKPLL2_ICP_UMSK                                 (~(((1U<<CLKRST_CLKPLL2_ICP_LEN)-1)<<CLKRST_CLKPLL2_ICP_POS))
#define CLKRST_CLKPLL2_SHRTR                                    CLKRST_CLKPLL2_SHRTR
#define CLKRST_CLKPLL2_SHRTR_POS                                (26U)
#define CLKRST_CLKPLL2_SHRTR_LEN                                (1U)
#define CLKRST_CLKPLL2_SHRTR_MSK                                (((1U<<CLKRST_CLKPLL2_SHRTR_LEN)-1)<<CLKRST_CLKPLL2_SHRTR_POS)
#define CLKRST_CLKPLL2_SHRTR_UMSK                               (~(((1U<<CLKRST_CLKPLL2_SHRTR_LEN)-1)<<CLKRST_CLKPLL2_SHRTR_POS))
#define CLKRST_CLKPLL2_RINGCAP_EN                               CLKRST_CLKPLL2_RINGCAP_EN
#define CLKRST_CLKPLL2_RINGCAP_EN_POS                           (27U)
#define CLKRST_CLKPLL2_RINGCAP_EN_LEN                           (1U)
#define CLKRST_CLKPLL2_RINGCAP_EN_MSK                           (((1U<<CLKRST_CLKPLL2_RINGCAP_EN_LEN)-1)<<CLKRST_CLKPLL2_RINGCAP_EN_POS)
#define CLKRST_CLKPLL2_RINGCAP_EN_UMSK                          (~(((1U<<CLKRST_CLKPLL2_RINGCAP_EN_LEN)-1)<<CLKRST_CLKPLL2_RINGCAP_EN_POS))
#define CLKRST_CLKPLL2_RESET                                    CLKRST_CLKPLL2_RESET
#define CLKRST_CLKPLL2_RESET_POS                                (28U)
#define CLKRST_CLKPLL2_RESET_LEN                                (1U)
#define CLKRST_CLKPLL2_RESET_MSK                                (((1U<<CLKRST_CLKPLL2_RESET_LEN)-1)<<CLKRST_CLKPLL2_RESET_POS)
#define CLKRST_CLKPLL2_RESET_UMSK                               (~(((1U<<CLKRST_CLKPLL2_RESET_LEN)-1)<<CLKRST_CLKPLL2_RESET_POS))

/* 0x110 : clkpll register 5 */
#define CLKRST_CLKIP5_OFFSET                                    (0x110)
#define CLKRST_CLKPLL2_VCTRL_CMP                                CLKRST_CLKPLL2_VCTRL_CMP
#define CLKRST_CLKPLL2_VCTRL_CMP_POS                            (0U)
#define CLKRST_CLKPLL2_VCTRL_CMP_LEN                            (2U)
#define CLKRST_CLKPLL2_VCTRL_CMP_MSK                            (((1U<<CLKRST_CLKPLL2_VCTRL_CMP_LEN)-1)<<CLKRST_CLKPLL2_VCTRL_CMP_POS)
#define CLKRST_CLKPLL2_VCTRL_CMP_UMSK                           (~(((1U<<CLKRST_CLKPLL2_VCTRL_CMP_LEN)-1)<<CLKRST_CLKPLL2_VCTRL_CMP_POS))
#define CLKRST_CLKPLL2_VCTRL_RANGE                              CLKRST_CLKPLL2_VCTRL_RANGE
#define CLKRST_CLKPLL2_VCTRL_RANGE_POS                          (4U)
#define CLKRST_CLKPLL2_VCTRL_RANGE_LEN                          (2U)
#define CLKRST_CLKPLL2_VCTRL_RANGE_MSK                          (((1U<<CLKRST_CLKPLL2_VCTRL_RANGE_LEN)-1)<<CLKRST_CLKPLL2_VCTRL_RANGE_POS)
#define CLKRST_CLKPLL2_VCTRL_RANGE_UMSK                         (~(((1U<<CLKRST_CLKPLL2_VCTRL_RANGE_LEN)-1)<<CLKRST_CLKPLL2_VCTRL_RANGE_POS))
#define CLKRST_CLKPLL2_V2I_R_CAL                                CLKRST_CLKPLL2_V2I_R_CAL
#define CLKRST_CLKPLL2_V2I_R_CAL_POS                            (8U)
#define CLKRST_CLKPLL2_V2I_R_CAL_LEN                            (4U)
#define CLKRST_CLKPLL2_V2I_R_CAL_MSK                            (((1U<<CLKRST_CLKPLL2_V2I_R_CAL_LEN)-1)<<CLKRST_CLKPLL2_V2I_R_CAL_POS)
#define CLKRST_CLKPLL2_V2I_R_CAL_UMSK                           (~(((1U<<CLKRST_CLKPLL2_V2I_R_CAL_LEN)-1)<<CLKRST_CLKPLL2_V2I_R_CAL_POS))
#define CLKRST_CLKPLL2_V2I_IDAC                                 CLKRST_CLKPLL2_V2I_IDAC
#define CLKRST_CLKPLL2_V2I_IDAC_POS                             (12U)
#define CLKRST_CLKPLL2_V2I_IDAC_LEN                             (4U)
#define CLKRST_CLKPLL2_V2I_IDAC_MSK                             (((1U<<CLKRST_CLKPLL2_V2I_IDAC_LEN)-1)<<CLKRST_CLKPLL2_V2I_IDAC_POS)
#define CLKRST_CLKPLL2_V2I_IDAC_UMSK                            (~(((1U<<CLKRST_CLKPLL2_V2I_IDAC_LEN)-1)<<CLKRST_CLKPLL2_V2I_IDAC_POS))
#define CLKRST_CLKPLL2_CP_OPAMP_EN                              CLKRST_CLKPLL2_CP_OPAMP_EN
#define CLKRST_CLKPLL2_CP_OPAMP_EN_POS                          (16U)
#define CLKRST_CLKPLL2_CP_OPAMP_EN_LEN                          (1U)
#define CLKRST_CLKPLL2_CP_OPAMP_EN_MSK                          (((1U<<CLKRST_CLKPLL2_CP_OPAMP_EN_LEN)-1)<<CLKRST_CLKPLL2_CP_OPAMP_EN_POS)
#define CLKRST_CLKPLL2_CP_OPAMP_EN_UMSK                         (~(((1U<<CLKRST_CLKPLL2_CP_OPAMP_EN_LEN)-1)<<CLKRST_CLKPLL2_CP_OPAMP_EN_POS))

/* 0x114 : clkip prediv */
#define CLKRST_CLKIP_PREDIV_OFFSET                              (0x114)
#define CLKRST_PREDIV_REF_SEL                                   CLKRST_PREDIV_REF_SEL
#define CLKRST_PREDIV_REF_SEL_POS                               (0U)
#define CLKRST_PREDIV_REF_SEL_LEN                               (3U)
#define CLKRST_PREDIV_REF_SEL_MSK                               (((1U<<CLKRST_PREDIV_REF_SEL_LEN)-1)<<CLKRST_PREDIV_REF_SEL_POS)
#define CLKRST_PREDIV_REF_SEL_UMSK                              (~(((1U<<CLKRST_PREDIV_REF_SEL_LEN)-1)<<CLKRST_PREDIV_REF_SEL_POS))
#define CLKRST_PU_PREDIV                                        CLKRST_PU_PREDIV
#define CLKRST_PU_PREDIV_POS                                    (3U)
#define CLKRST_PU_PREDIV_LEN                                    (1U)
#define CLKRST_PU_PREDIV_MSK                                    (((1U<<CLKRST_PU_PREDIV_LEN)-1)<<CLKRST_PU_PREDIV_POS)
#define CLKRST_PU_PREDIV_UMSK                                   (~(((1U<<CLKRST_PU_PREDIV_LEN)-1)<<CLKRST_PU_PREDIV_POS))
#define CLKRST_PREDIV                                           CLKRST_PREDIV
#define CLKRST_PREDIV_POS                                       (4U)
#define CLKRST_PREDIV_LEN                                       (7U)
#define CLKRST_PREDIV_MSK                                       (((1U<<CLKRST_PREDIV_LEN)-1)<<CLKRST_PREDIV_POS)
#define CLKRST_PREDIV_UMSK                                      (~(((1U<<CLKRST_PREDIV_LEN)-1)<<CLKRST_PREDIV_POS))
#define CLKRST_RESET_PREDIV                                     CLKRST_RESET_PREDIV
#define CLKRST_RESET_PREDIV_POS                                 (11U)
#define CLKRST_RESET_PREDIV_LEN                                 (1U)
#define CLKRST_RESET_PREDIV_MSK                                 (((1U<<CLKRST_RESET_PREDIV_LEN)-1)<<CLKRST_RESET_PREDIV_POS)
#define CLKRST_RESET_PREDIV_UMSK                                (~(((1U<<CLKRST_RESET_PREDIV_LEN)-1)<<CLKRST_RESET_PREDIV_POS))

/* 0x118 : clkip postdiv */
#define CLKRST_CLKIP_POSTDIV_OFFSET                             (0x118)
#define CLKRST_CLKPLL_EN_400M_CLK                               CLKRST_CLKPLL_EN_400M_CLK
#define CLKRST_CLKPLL_EN_400M_CLK_POS                           (1U)
#define CLKRST_CLKPLL_EN_400M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_400M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_400M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_400M_CLK_POS)
#define CLKRST_CLKPLL_EN_400M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_400M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_400M_CLK_POS))
#define CLKRST_CLKPLL_EN_320M_CLK                               CLKRST_CLKPLL_EN_320M_CLK
#define CLKRST_CLKPLL_EN_320M_CLK_POS                           (2U)
#define CLKRST_CLKPLL_EN_320M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_320M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_320M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_320M_CLK_POS)
#define CLKRST_CLKPLL_EN_320M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_320M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_320M_CLK_POS))
#define CLKRST_CLKPLL_EN_267M_CLK                               CLKRST_CLKPLL_EN_267M_CLK
#define CLKRST_CLKPLL_EN_267M_CLK_POS                           (3U)
#define CLKRST_CLKPLL_EN_267M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_267M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_267M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_267M_CLK_POS)
#define CLKRST_CLKPLL_EN_267M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_267M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_267M_CLK_POS))
#define CLKRST_CLKPLL_EN_240M_CLK                               CLKRST_CLKPLL_EN_240M_CLK
#define CLKRST_CLKPLL_EN_240M_CLK_POS                           (4U)
#define CLKRST_CLKPLL_EN_240M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_240M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_240M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_240M_CLK_POS)
#define CLKRST_CLKPLL_EN_240M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_240M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_240M_CLK_POS))
#define CLKRST_CLKPLL_EN_192M_CLK                               CLKRST_CLKPLL_EN_192M_CLK
#define CLKRST_CLKPLL_EN_192M_CLK_POS                           (5U)
#define CLKRST_CLKPLL_EN_192M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_192M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_192M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_192M_CLK_POS)
#define CLKRST_CLKPLL_EN_192M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_192M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_192M_CLK_POS))
#define CLKRST_CLKPLL_EN_160M_CLK                               CLKRST_CLKPLL_EN_160M_CLK
#define CLKRST_CLKPLL_EN_160M_CLK_POS                           (6U)
#define CLKRST_CLKPLL_EN_160M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_160M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_160M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_160M_CLK_POS)
#define CLKRST_CLKPLL_EN_160M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_160M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_160M_CLK_POS))
#define CLKRST_CLKPLL_EN_120M_CLK                               CLKRST_CLKPLL_EN_120M_CLK
#define CLKRST_CLKPLL_EN_120M_CLK_POS                           (7U)
#define CLKRST_CLKPLL_EN_120M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_120M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_120M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_120M_CLK_POS)
#define CLKRST_CLKPLL_EN_120M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_120M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_120M_CLK_POS))
#define CLKRST_CLKPLL_EN_100M_CLK                               CLKRST_CLKPLL_EN_100M_CLK
#define CLKRST_CLKPLL_EN_100M_CLK_POS                           (8U)
#define CLKRST_CLKPLL_EN_100M_CLK_LEN                           (1U)
#define CLKRST_CLKPLL_EN_100M_CLK_MSK                           (((1U<<CLKRST_CLKPLL_EN_100M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_100M_CLK_POS)
#define CLKRST_CLKPLL_EN_100M_CLK_UMSK                          (~(((1U<<CLKRST_CLKPLL_EN_100M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_100M_CLK_POS))
#define CLKRST_CLKPLL_EN_50M_CLK                                CLKRST_CLKPLL_EN_50M_CLK
#define CLKRST_CLKPLL_EN_50M_CLK_POS                            (9U)
#define CLKRST_CLKPLL_EN_50M_CLK_LEN                            (1U)
#define CLKRST_CLKPLL_EN_50M_CLK_MSK                            (((1U<<CLKRST_CLKPLL_EN_50M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_50M_CLK_POS)
#define CLKRST_CLKPLL_EN_50M_CLK_UMSK                           (~(((1U<<CLKRST_CLKPLL_EN_50M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_50M_CLK_POS))
#define CLKRST_CLKPLL_EN_25M_CLK                                CLKRST_CLKPLL_EN_25M_CLK
#define CLKRST_CLKPLL_EN_25M_CLK_POS                            (10U)
#define CLKRST_CLKPLL_EN_25M_CLK_LEN                            (1U)
#define CLKRST_CLKPLL_EN_25M_CLK_MSK                            (((1U<<CLKRST_CLKPLL_EN_25M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_25M_CLK_POS)
#define CLKRST_CLKPLL_EN_25M_CLK_UMSK                           (~(((1U<<CLKRST_CLKPLL_EN_25M_CLK_LEN)-1)<<CLKRST_CLKPLL_EN_25M_CLK_POS))
#define CLKRST_PLL_CLK_SEL                                      CLKRST_PLL_CLK_SEL
#define CLKRST_PLL_CLK_SEL_POS                                  (12U)
#define CLKRST_PLL_CLK_SEL_LEN                                  (2U)
#define CLKRST_PLL_CLK_SEL_MSK                                  (((1U<<CLKRST_PLL_CLK_SEL_LEN)-1)<<CLKRST_PLL_CLK_SEL_POS)
#define CLKRST_PLL_CLK_SEL_UMSK                                 (~(((1U<<CLKRST_PLL_CLK_SEL_LEN)-1)<<CLKRST_PLL_CLK_SEL_POS))
#define CLKRST_PU_POSTDIV                                       CLKRST_PU_POSTDIV
#define CLKRST_PU_POSTDIV_POS                                   (14U)
#define CLKRST_PU_POSTDIV_LEN                                   (1U)
#define CLKRST_PU_POSTDIV_MSK                                   (((1U<<CLKRST_PU_POSTDIV_LEN)-1)<<CLKRST_PU_POSTDIV_POS)
#define CLKRST_PU_POSTDIV_UMSK                                  (~(((1U<<CLKRST_PU_POSTDIV_LEN)-1)<<CLKRST_PU_POSTDIV_POS))

/* 0x11C : clkip aupll register 1 */
#define CLKRST_CLKIP_AUPLL1_OFFSET                              (0x11C)
#define CLKRST_AUPLL_VCO_SPEED                                  CLKRST_AUPLL_VCO_SPEED
#define CLKRST_AUPLL_VCO_SPEED_POS                              (0U)
#define CLKRST_AUPLL_VCO_SPEED_LEN                              (3U)
#define CLKRST_AUPLL_VCO_SPEED_MSK                              (((1U<<CLKRST_AUPLL_VCO_SPEED_LEN)-1)<<CLKRST_AUPLL_VCO_SPEED_POS)
#define CLKRST_AUPLL_VCO_SPEED_UMSK                             (~(((1U<<CLKRST_AUPLL_VCO_SPEED_LEN)-1)<<CLKRST_AUPLL_VCO_SPEED_POS))
#define CLKRST_AUPLL_ICP                                        CLKRST_AUPLL_ICP
#define CLKRST_AUPLL_ICP_POS                                    (3U)
#define CLKRST_AUPLL_ICP_LEN                                    (3U)
#define CLKRST_AUPLL_ICP_MSK                                    (((1U<<CLKRST_AUPLL_ICP_LEN)-1)<<CLKRST_AUPLL_ICP_POS)
#define CLKRST_AUPLL_ICP_UMSK                                   (~(((1U<<CLKRST_AUPLL_ICP_LEN)-1)<<CLKRST_AUPLL_ICP_POS))
#define CLKRST_AUPLL_R4_SHORT                                   CLKRST_AUPLL_R4_SHORT
#define CLKRST_AUPLL_R4_SHORT_POS                               (6U)
#define CLKRST_AUPLL_R4_SHORT_LEN                               (1U)
#define CLKRST_AUPLL_R4_SHORT_MSK                               (((1U<<CLKRST_AUPLL_R4_SHORT_LEN)-1)<<CLKRST_AUPLL_R4_SHORT_POS)
#define CLKRST_AUPLL_R4_SHORT_UMSK                              (~(((1U<<CLKRST_AUPLL_R4_SHORT_LEN)-1)<<CLKRST_AUPLL_R4_SHORT_POS))
#define CLKRST_AUPLL_R4                                         CLKRST_AUPLL_R4
#define CLKRST_AUPLL_R4_POS                                     (7U)
#define CLKRST_AUPLL_R4_LEN                                     (2U)
#define CLKRST_AUPLL_R4_MSK                                     (((1U<<CLKRST_AUPLL_R4_LEN)-1)<<CLKRST_AUPLL_R4_POS)
#define CLKRST_AUPLL_R4_UMSK                                    (~(((1U<<CLKRST_AUPLL_R4_LEN)-1)<<CLKRST_AUPLL_R4_POS))
#define CLKRST_AUPLL_C3                                         CLKRST_AUPLL_C3
#define CLKRST_AUPLL_C3_POS                                     (9U)
#define CLKRST_AUPLL_C3_LEN                                     (2U)
#define CLKRST_AUPLL_C3_MSK                                     (((1U<<CLKRST_AUPLL_C3_LEN)-1)<<CLKRST_AUPLL_C3_POS)
#define CLKRST_AUPLL_C3_UMSK                                    (~(((1U<<CLKRST_AUPLL_C3_LEN)-1)<<CLKRST_AUPLL_C3_POS))
#define CLKRST_AUPLL_CZ                                         CLKRST_AUPLL_CZ
#define CLKRST_AUPLL_CZ_POS                                     (11U)
#define CLKRST_AUPLL_CZ_LEN                                     (2U)
#define CLKRST_AUPLL_CZ_MSK                                     (((1U<<CLKRST_AUPLL_CZ_LEN)-1)<<CLKRST_AUPLL_CZ_POS)
#define CLKRST_AUPLL_CZ_UMSK                                    (~(((1U<<CLKRST_AUPLL_CZ_LEN)-1)<<CLKRST_AUPLL_CZ_POS))
#define CLKRST_AUPLL_RZ                                         CLKRST_AUPLL_RZ
#define CLKRST_AUPLL_RZ_POS                                     (13U)
#define CLKRST_AUPLL_RZ_LEN                                     (2U)
#define CLKRST_AUPLL_RZ_MSK                                     (((1U<<CLKRST_AUPLL_RZ_LEN)-1)<<CLKRST_AUPLL_RZ_POS)
#define CLKRST_AUPLL_RZ_UMSK                                    (~(((1U<<CLKRST_AUPLL_RZ_LEN)-1)<<CLKRST_AUPLL_RZ_POS))
#define CLKRST_AUPLL_REFDIV_RATIO                               CLKRST_AUPLL_REFDIV_RATIO
#define CLKRST_AUPLL_REFDIV_RATIO_POS                           (21U)
#define CLKRST_AUPLL_REFDIV_RATIO_LEN                           (4U)
#define CLKRST_AUPLL_REFDIV_RATIO_MSK                           (((1U<<CLKRST_AUPLL_REFDIV_RATIO_LEN)-1)<<CLKRST_AUPLL_REFDIV_RATIO_POS)
#define CLKRST_AUPLL_REFDIV_RATIO_UMSK                          (~(((1U<<CLKRST_AUPLL_REFDIV_RATIO_LEN)-1)<<CLKRST_AUPLL_REFDIV_RATIO_POS))
#define CLKRST_AUPLL_RESET_REFDIV                               CLKRST_AUPLL_RESET_REFDIV
#define CLKRST_AUPLL_RESET_REFDIV_POS                           (25U)
#define CLKRST_AUPLL_RESET_REFDIV_LEN                           (1U)
#define CLKRST_AUPLL_RESET_REFDIV_MSK                           (((1U<<CLKRST_AUPLL_RESET_REFDIV_LEN)-1)<<CLKRST_AUPLL_RESET_REFDIV_POS)
#define CLKRST_AUPLL_RESET_REFDIV_UMSK                          (~(((1U<<CLKRST_AUPLL_RESET_REFDIV_LEN)-1)<<CLKRST_AUPLL_RESET_REFDIV_POS))
#define CLKRST_AUPLL_SHRTR                                      CLKRST_AUPLL_SHRTR
#define CLKRST_AUPLL_SHRTR_POS                                  (26U)
#define CLKRST_AUPLL_SHRTR_LEN                                  (1U)
#define CLKRST_AUPLL_SHRTR_MSK                                  (((1U<<CLKRST_AUPLL_SHRTR_LEN)-1)<<CLKRST_AUPLL_SHRTR_POS)
#define CLKRST_AUPLL_SHRTR_UMSK                                 (~(((1U<<CLKRST_AUPLL_SHRTR_LEN)-1)<<CLKRST_AUPLL_SHRTR_POS))
#define CLKRST_AUPLL_PU_PFD                                     CLKRST_AUPLL_PU_PFD
#define CLKRST_AUPLL_PU_PFD_POS                                 (27U)
#define CLKRST_AUPLL_PU_PFD_LEN                                 (1U)
#define CLKRST_AUPLL_PU_PFD_MSK                                 (((1U<<CLKRST_AUPLL_PU_PFD_LEN)-1)<<CLKRST_AUPLL_PU_PFD_POS)
#define CLKRST_AUPLL_PU_PFD_UMSK                                (~(((1U<<CLKRST_AUPLL_PU_PFD_LEN)-1)<<CLKRST_AUPLL_PU_PFD_POS))
#define CLKRST_AUPLL_RESET_FBDV                                 CLKRST_AUPLL_RESET_FBDV
#define CLKRST_AUPLL_RESET_FBDV_POS                             (28U)
#define CLKRST_AUPLL_RESET_FBDV_LEN                             (1U)
#define CLKRST_AUPLL_RESET_FBDV_MSK                             (((1U<<CLKRST_AUPLL_RESET_FBDV_LEN)-1)<<CLKRST_AUPLL_RESET_FBDV_POS)
#define CLKRST_AUPLL_RESET_FBDV_UMSK                            (~(((1U<<CLKRST_AUPLL_RESET_FBDV_LEN)-1)<<CLKRST_AUPLL_RESET_FBDV_POS))
#define CLKRST_AUPLL_PU_FBDV                                    CLKRST_AUPLL_PU_FBDV
#define CLKRST_AUPLL_PU_FBDV_POS                                (29U)
#define CLKRST_AUPLL_PU_FBDV_LEN                                (1U)
#define CLKRST_AUPLL_PU_FBDV_MSK                                (((1U<<CLKRST_AUPLL_PU_FBDV_LEN)-1)<<CLKRST_AUPLL_PU_FBDV_POS)
#define CLKRST_AUPLL_PU_FBDV_UMSK                               (~(((1U<<CLKRST_AUPLL_PU_FBDV_LEN)-1)<<CLKRST_AUPLL_PU_FBDV_POS))
#define CLKRST_AUPLL_CP_OPAMP_EN                                CLKRST_AUPLL_CP_OPAMP_EN
#define CLKRST_AUPLL_CP_OPAMP_EN_POS                            (30U)
#define CLKRST_AUPLL_CP_OPAMP_EN_LEN                            (1U)
#define CLKRST_AUPLL_CP_OPAMP_EN_MSK                            (((1U<<CLKRST_AUPLL_CP_OPAMP_EN_LEN)-1)<<CLKRST_AUPLL_CP_OPAMP_EN_POS)
#define CLKRST_AUPLL_CP_OPAMP_EN_UMSK                           (~(((1U<<CLKRST_AUPLL_CP_OPAMP_EN_LEN)-1)<<CLKRST_AUPLL_CP_OPAMP_EN_POS))
#define CLKRST_AUPLL_PU_CP                                      CLKRST_AUPLL_PU_CP
#define CLKRST_AUPLL_PU_CP_POS                                  (31U)
#define CLKRST_AUPLL_PU_CP_LEN                                  (1U)
#define CLKRST_AUPLL_PU_CP_MSK                                  (((1U<<CLKRST_AUPLL_PU_CP_LEN)-1)<<CLKRST_AUPLL_PU_CP_POS)
#define CLKRST_AUPLL_PU_CP_UMSK                                 (~(((1U<<CLKRST_AUPLL_PU_CP_LEN)-1)<<CLKRST_AUPLL_PU_CP_POS))

/* 0x120 : clkip aupll register 2 */
#define CLKRST_CLKIP_AUPLL2_OFFSET                              (0x120)
#define CLKRST_AUPLL_SDMIN                                      CLKRST_AUPLL_SDMIN
#define CLKRST_AUPLL_SDMIN_POS                                  (0U)
#define CLKRST_AUPLL_SDMIN_LEN                                  (24U)
#define CLKRST_AUPLL_SDMIN_MSK                                  (((1U<<CLKRST_AUPLL_SDMIN_LEN)-1)<<CLKRST_AUPLL_SDMIN_POS)
#define CLKRST_AUPLL_SDMIN_UMSK                                 (~(((1U<<CLKRST_AUPLL_SDMIN_LEN)-1)<<CLKRST_AUPLL_SDMIN_POS))

/* 0x124 : clkip aupll register 3 */
#define CLKRST_CLKIP_AUPLL3_OFFSET                              (0x124)
#define CLKRST_AUPLL_PU                                         CLKRST_AUPLL_PU
#define CLKRST_AUPLL_PU_POS                                     (0U)
#define CLKRST_AUPLL_PU_LEN                                     (1U)
#define CLKRST_AUPLL_PU_MSK                                     (((1U<<CLKRST_AUPLL_PU_LEN)-1)<<CLKRST_AUPLL_PU_POS)
#define CLKRST_AUPLL_PU_UMSK                                    (~(((1U<<CLKRST_AUPLL_PU_LEN)-1)<<CLKRST_AUPLL_PU_POS))
#define CLKRST_TEN_AUPLL                                        CLKRST_TEN_AUPLL
#define CLKRST_TEN_AUPLL_POS                                    (2U)
#define CLKRST_TEN_AUPLL_LEN                                    (2U)
#define CLKRST_TEN_AUPLL_MSK                                    (((1U<<CLKRST_TEN_AUPLL_LEN)-1)<<CLKRST_TEN_AUPLL_POS)
#define CLKRST_TEN_AUPLL_UMSK                                   (~(((1U<<CLKRST_TEN_AUPLL_LEN)-1)<<CLKRST_TEN_AUPLL_POS))
#define CLKRST_DTEST_AUPLL_FSDM_EN                              CLKRST_DTEST_AUPLL_FSDM_EN
#define CLKRST_DTEST_AUPLL_FSDM_EN_POS                          (4U)
#define CLKRST_DTEST_AUPLL_FSDM_EN_LEN                          (1U)
#define CLKRST_DTEST_AUPLL_FSDM_EN_MSK                          (((1U<<CLKRST_DTEST_AUPLL_FSDM_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FSDM_EN_POS)
#define CLKRST_DTEST_AUPLL_FSDM_EN_UMSK                         (~(((1U<<CLKRST_DTEST_AUPLL_FSDM_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FSDM_EN_POS))
#define CLKRST_DTEST_AUPLL_FREF_EN                              CLKRST_DTEST_AUPLL_FREF_EN
#define CLKRST_DTEST_AUPLL_FREF_EN_POS                          (5U)
#define CLKRST_DTEST_AUPLL_FREF_EN_LEN                          (1U)
#define CLKRST_DTEST_AUPLL_FREF_EN_MSK                          (((1U<<CLKRST_DTEST_AUPLL_FREF_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FREF_EN_POS)
#define CLKRST_DTEST_AUPLL_FREF_EN_UMSK                         (~(((1U<<CLKRST_DTEST_AUPLL_FREF_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FREF_EN_POS))
#define CLKRST_DTEST_AUPLL_FIN_EN                               CLKRST_DTEST_AUPLL_FIN_EN
#define CLKRST_DTEST_AUPLL_FIN_EN_POS                           (6U)
#define CLKRST_DTEST_AUPLL_FIN_EN_LEN                           (1U)
#define CLKRST_DTEST_AUPLL_FIN_EN_MSK                           (((1U<<CLKRST_DTEST_AUPLL_FIN_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FIN_EN_POS)
#define CLKRST_DTEST_AUPLL_FIN_EN_UMSK                          (~(((1U<<CLKRST_DTEST_AUPLL_FIN_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_FIN_EN_POS))
#define CLKRST_AUPLL_POSTDIV                                    CLKRST_AUPLL_POSTDIV
#define CLKRST_AUPLL_POSTDIV_POS                                (7U)
#define CLKRST_AUPLL_POSTDIV_LEN                                (7U)
#define CLKRST_AUPLL_POSTDIV_MSK                                (((1U<<CLKRST_AUPLL_POSTDIV_LEN)-1)<<CLKRST_AUPLL_POSTDIV_POS)
#define CLKRST_AUPLL_POSTDIV_UMSK                               (~(((1U<<CLKRST_AUPLL_POSTDIV_LEN)-1)<<CLKRST_AUPLL_POSTDIV_POS))
#define CLKRST_AUPLL_SEL_SAMPLE_CLK                             CLKRST_AUPLL_SEL_SAMPLE_CLK
#define CLKRST_AUPLL_SEL_SAMPLE_CLK_POS                         (14U)
#define CLKRST_AUPLL_SEL_SAMPLE_CLK_LEN                         (2U)
#define CLKRST_AUPLL_SEL_SAMPLE_CLK_MSK                         (((1U<<CLKRST_AUPLL_SEL_SAMPLE_CLK_LEN)-1)<<CLKRST_AUPLL_SEL_SAMPLE_CLK_POS)
#define CLKRST_AUPLL_SEL_SAMPLE_CLK_UMSK                        (~(((1U<<CLKRST_AUPLL_SEL_SAMPLE_CLK_LEN)-1)<<CLKRST_AUPLL_SEL_SAMPLE_CLK_POS))
#define CLKRST_AUPLL_RESET_POSTDIV                              CLKRST_AUPLL_RESET_POSTDIV
#define CLKRST_AUPLL_RESET_POSTDIV_POS                          (16U)
#define CLKRST_AUPLL_RESET_POSTDIV_LEN                          (1U)
#define CLKRST_AUPLL_RESET_POSTDIV_MSK                          (((1U<<CLKRST_AUPLL_RESET_POSTDIV_LEN)-1)<<CLKRST_AUPLL_RESET_POSTDIV_POS)
#define CLKRST_AUPLL_RESET_POSTDIV_UMSK                         (~(((1U<<CLKRST_AUPLL_RESET_POSTDIV_LEN)-1)<<CLKRST_AUPLL_RESET_POSTDIV_POS))
#define CLKRST_AUPLL_SEL_FB_CLK                                 CLKRST_AUPLL_SEL_FB_CLK
#define CLKRST_AUPLL_SEL_FB_CLK_POS                             (17U)
#define CLKRST_AUPLL_SEL_FB_CLK_LEN                             (2U)
#define CLKRST_AUPLL_SEL_FB_CLK_MSK                             (((1U<<CLKRST_AUPLL_SEL_FB_CLK_LEN)-1)<<CLKRST_AUPLL_SEL_FB_CLK_POS)
#define CLKRST_AUPLL_SEL_FB_CLK_UMSK                            (~(((1U<<CLKRST_AUPLL_SEL_FB_CLK_LEN)-1)<<CLKRST_AUPLL_SEL_FB_CLK_POS))
#define CLKRST_AUPLL_SDM_RESET                                  CLKRST_AUPLL_SDM_RESET
#define CLKRST_AUPLL_SDM_RESET_POS                              (19U)
#define CLKRST_AUPLL_SDM_RESET_LEN                              (1U)
#define CLKRST_AUPLL_SDM_RESET_MSK                              (((1U<<CLKRST_AUPLL_SDM_RESET_LEN)-1)<<CLKRST_AUPLL_SDM_RESET_POS)
#define CLKRST_AUPLL_SDM_RESET_UMSK                             (~(((1U<<CLKRST_AUPLL_SDM_RESET_LEN)-1)<<CLKRST_AUPLL_SDM_RESET_POS))
#define CLKRST_AUPLL_SDM_FLAG                                   CLKRST_AUPLL_SDM_FLAG
#define CLKRST_AUPLL_SDM_FLAG_POS                               (20U)
#define CLKRST_AUPLL_SDM_FLAG_LEN                               (1U)
#define CLKRST_AUPLL_SDM_FLAG_MSK                               (((1U<<CLKRST_AUPLL_SDM_FLAG_LEN)-1)<<CLKRST_AUPLL_SDM_FLAG_POS)
#define CLKRST_AUPLL_SDM_FLAG_UMSK                              (~(((1U<<CLKRST_AUPLL_SDM_FLAG_LEN)-1)<<CLKRST_AUPLL_SDM_FLAG_POS))
#define CLKRST_AUPLL_SDM_BYPASS                                 CLKRST_AUPLL_SDM_BYPASS
#define CLKRST_AUPLL_SDM_BYPASS_POS                             (21U)
#define CLKRST_AUPLL_SDM_BYPASS_LEN                             (1U)
#define CLKRST_AUPLL_SDM_BYPASS_MSK                             (((1U<<CLKRST_AUPLL_SDM_BYPASS_LEN)-1)<<CLKRST_AUPLL_SDM_BYPASS_POS)
#define CLKRST_AUPLL_SDM_BYPASS_UMSK                            (~(((1U<<CLKRST_AUPLL_SDM_BYPASS_LEN)-1)<<CLKRST_AUPLL_SDM_BYPASS_POS))
#define CLKRST_AUPLL_DITHER_SEL                                 CLKRST_AUPLL_DITHER_SEL
#define CLKRST_AUPLL_DITHER_SEL_POS                             (22U)
#define CLKRST_AUPLL_DITHER_SEL_LEN                             (2U)
#define CLKRST_AUPLL_DITHER_SEL_MSK                             (((1U<<CLKRST_AUPLL_DITHER_SEL_LEN)-1)<<CLKRST_AUPLL_DITHER_SEL_POS)
#define CLKRST_AUPLL_DITHER_SEL_UMSK                            (~(((1U<<CLKRST_AUPLL_DITHER_SEL_LEN)-1)<<CLKRST_AUPLL_DITHER_SEL_POS))
#define CLKRST_DTEST_AUPLL_CLK_EN                               CLKRST_DTEST_AUPLL_CLK_EN
#define CLKRST_DTEST_AUPLL_CLK_EN_POS                           (24U)
#define CLKRST_DTEST_AUPLL_CLK_EN_LEN                           (1U)
#define CLKRST_DTEST_AUPLL_CLK_EN_MSK                           (((1U<<CLKRST_DTEST_AUPLL_CLK_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_CLK_EN_POS)
#define CLKRST_DTEST_AUPLL_CLK_EN_UMSK                          (~(((1U<<CLKRST_DTEST_AUPLL_CLK_EN_LEN)-1)<<CLKRST_DTEST_AUPLL_CLK_EN_POS))

/* 0x128 : cip register */
#define CLKRST_CIP_OFFSET                                       (0x128)
#define CLKRST_PU_MBG                                           CLKRST_PU_MBG
#define CLKRST_PU_MBG_POS                                       (0U)
#define CLKRST_PU_MBG_LEN                                       (1U)
#define CLKRST_PU_MBG_MSK                                       (((1U<<CLKRST_PU_MBG_LEN)-1)<<CLKRST_PU_MBG_POS)
#define CLKRST_PU_MBG_UMSK                                      (~(((1U<<CLKRST_PU_MBG_LEN)-1)<<CLKRST_PU_MBG_POS))
#define CLKRST_PU_SFREG                                         CLKRST_PU_SFREG
#define CLKRST_PU_SFREG_POS                                     (1U)
#define CLKRST_PU_SFREG_LEN                                     (1U)
#define CLKRST_PU_SFREG_MSK                                     (((1U<<CLKRST_PU_SFREG_LEN)-1)<<CLKRST_PU_SFREG_POS)
#define CLKRST_PU_SFREG_UMSK                                    (~(((1U<<CLKRST_PU_SFREG_LEN)-1)<<CLKRST_PU_SFREG_POS))
#define CLKRST_VG11_SEL                                         CLKRST_VG11_SEL
#define CLKRST_VG11_SEL_POS                                     (4U)
#define CLKRST_VG11_SEL_LEN                                     (2U)
#define CLKRST_VG11_SEL_MSK                                     (((1U<<CLKRST_VG11_SEL_LEN)-1)<<CLKRST_VG11_SEL_POS)
#define CLKRST_VG11_SEL_UMSK                                    (~(((1U<<CLKRST_VG11_SEL_LEN)-1)<<CLKRST_VG11_SEL_POS))
#define CLKRST_VG15_SEL                                         CLKRST_VG15_SEL
#define CLKRST_VG15_SEL_POS                                     (6U)
#define CLKRST_VG15_SEL_LEN                                     (2U)
#define CLKRST_VG15_SEL_MSK                                     (((1U<<CLKRST_VG15_SEL_LEN)-1)<<CLKRST_VG15_SEL_POS)
#define CLKRST_VG15_SEL_UMSK                                    (~(((1U<<CLKRST_VG15_SEL_LEN)-1)<<CLKRST_VG15_SEL_POS))
#define CLKRST_TEN_MBG                                          CLKRST_TEN_MBG
#define CLKRST_TEN_MBG_POS                                      (8U)
#define CLKRST_TEN_MBG_LEN                                      (1U)
#define CLKRST_TEN_MBG_MSK                                      (((1U<<CLKRST_TEN_MBG_LEN)-1)<<CLKRST_TEN_MBG_POS)
#define CLKRST_TEN_MBG_UMSK                                     (~(((1U<<CLKRST_TEN_MBG_LEN)-1)<<CLKRST_TEN_MBG_POS))
#define CLKRST_TEN_SFREG                                        CLKRST_TEN_SFREG
#define CLKRST_TEN_SFREG_POS                                    (9U)
#define CLKRST_TEN_SFREG_LEN                                    (1U)
#define CLKRST_TEN_SFREG_MSK                                    (((1U<<CLKRST_TEN_SFREG_LEN)-1)<<CLKRST_TEN_SFREG_POS)
#define CLKRST_TEN_SFREG_UMSK                                   (~(((1U<<CLKRST_TEN_SFREG_LEN)-1)<<CLKRST_TEN_SFREG_POS))
#define CLKRST_TMUX                                             CLKRST_TMUX
#define CLKRST_TMUX_POS                                         (12U)
#define CLKRST_TMUX_LEN                                         (3U)
#define CLKRST_TMUX_MSK                                         (((1U<<CLKRST_TMUX_LEN)-1)<<CLKRST_TMUX_POS)
#define CLKRST_TMUX_UMSK                                        (~(((1U<<CLKRST_TMUX_LEN)-1)<<CLKRST_TMUX_POS))
#define CLKRST_DC_TP_OUT_EN                                     CLKRST_DC_TP_OUT_EN
#define CLKRST_DC_TP_OUT_EN_POS                                 (16U)
#define CLKRST_DC_TP_OUT_EN_LEN                                 (1U)
#define CLKRST_DC_TP_OUT_EN_MSK                                 (((1U<<CLKRST_DC_TP_OUT_EN_LEN)-1)<<CLKRST_DC_TP_OUT_EN_POS)
#define CLKRST_DC_TP_OUT_EN_UMSK                                (~(((1U<<CLKRST_DC_TP_OUT_EN_LEN)-1)<<CLKRST_DC_TP_OUT_EN_POS))

/* 0x12C : ldo11 register 1 */
#define CLKRST_LDO11_1_OFFSET                                   (0x12C)
#define CLKRST_LDO11_CFG0                                       CLKRST_LDO11_CFG0
#define CLKRST_LDO11_CFG0_POS                                   (0U)
#define CLKRST_LDO11_CFG0_LEN                                   (32U)
#define CLKRST_LDO11_CFG0_MSK                                   (((1U<<CLKRST_LDO11_CFG0_LEN)-1)<<CLKRST_LDO11_CFG0_POS)
#define CLKRST_LDO11_CFG0_UMSK                                  (~(((1U<<CLKRST_LDO11_CFG0_LEN)-1)<<CLKRST_LDO11_CFG0_POS))

/* 0x130 : ldo11 register 2 */
#define CLKRST_LDO11_2_OFFSET                                   (0x130)
#define CLKRST_LDO11_CFG1                                       CLKRST_LDO11_CFG1
#define CLKRST_LDO11_CFG1_POS                                   (0U)
#define CLKRST_LDO11_CFG1_LEN                                   (32U)
#define CLKRST_LDO11_CFG1_MSK                                   (((1U<<CLKRST_LDO11_CFG1_LEN)-1)<<CLKRST_LDO11_CFG1_POS)
#define CLKRST_LDO11_CFG1_UMSK                                  (~(((1U<<CLKRST_LDO11_CFG1_LEN)-1)<<CLKRST_LDO11_CFG1_POS))

/* 0x134 : rf reserved register */
#define CLKRST_RF_RESV_OFFSET                                   (0x134)
#define CLKRST_RF_RESV0                                         CLKRST_RF_RESV0
#define CLKRST_RF_RESV0_POS                                     (0U)
#define CLKRST_RF_RESV0_LEN                                     (16U)
#define CLKRST_RF_RESV0_MSK                                     (((1U<<CLKRST_RF_RESV0_LEN)-1)<<CLKRST_RF_RESV0_POS)
#define CLKRST_RF_RESV0_UMSK                                    (~(((1U<<CLKRST_RF_RESV0_LEN)-1)<<CLKRST_RF_RESV0_POS))
#define CLKRST_RF_RESV1                                         CLKRST_RF_RESV1
#define CLKRST_RF_RESV1_POS                                     (16U)
#define CLKRST_RF_RESV1_LEN                                     (16U)
#define CLKRST_RF_RESV1_MSK                                     (((1U<<CLKRST_RF_RESV1_LEN)-1)<<CLKRST_RF_RESV1_POS)
#define CLKRST_RF_RESV1_UMSK                                    (~(((1U<<CLKRST_RF_RESV1_LEN)-1)<<CLKRST_RF_RESV1_POS))

/* 0x138 : rf reserved register */
#define CLKRST_RF_OUT_RESV_OFFSET                               (0x138)
#define CLKRST_RF_OUT_RESV                                      CLKRST_RF_OUT_RESV
#define CLKRST_RF_OUT_RESV_POS                                  (0U)
#define CLKRST_RF_OUT_RESV_LEN                                  (32U)
#define CLKRST_RF_OUT_RESV_MSK                                  (((1U<<CLKRST_RF_OUT_RESV_LEN)-1)<<CLKRST_RF_OUT_RESV_POS)
#define CLKRST_RF_OUT_RESV_UMSK                                 (~(((1U<<CLKRST_RF_OUT_RESV_LEN)-1)<<CLKRST_RF_OUT_RESV_POS))


struct  clkrst_reg {
    /* 0x0 : mm_clk_ctrl_cpu */
    union {
        struct {
            uint32_t reg_pll_en                     :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_cpu_clk_en                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_bclk_en                    :  1; /* [    2],        r/w,        0x1 */
            uint32_t reg_a5_cpu_clk_en              :  1; /* [    3],        r/w,        0x1 */
            uint32_t reg_e74c_clk_en                :  1; /* [    4],        r/w,        0x1 */
            uint32_t hbn_uart_clk_sel               :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_e74c_clk_en_2              :  1; /* [    6],        r/w,        0x1 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_pll_sel                    :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t hbn_root_clk_sel               :  2; /* [11:10],        r/w,        0x0 */
            uint32_t reg_m4_fclk_en                 :  1; /* [   12],        r/w,        0x1 */
            uint32_t reg_m4_fclk_sel                :  1; /* [   13],        r/w,        0x1 */
            uint32_t reg_m4_hclk_en                 :  1; /* [   14],        r/w,        0x1 */
            uint32_t reg_m4_trace_en                :  1; /* [   15],        r/w,        0x1 */
            uint32_t reserved_16_23                 :  8; /* [23:16],       rsvd,        0x0 */
            uint32_t cpu_clk_sw_state               :  3; /* [26:24],          r,        0x0 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t m4_fclk_sw_state               :  3; /* [30:28],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_cpu;

    /* 0x4 : mm_clk_cpu */
    union {
        struct {
            uint32_t reg_cpu_clk_div                :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_cnn_clk_div_en             :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_cnn_clk_sel                :  2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11_15                 :  5; /* [15:11],       rsvd,        0x0 */
            uint32_t reg_bclk_div                   :  8; /* [23:16],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_cpu;

    /* 0x8 : isp_dp_clk */
    union {
        struct {
            uint32_t reg_isp_clk_div_en             :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_isp_clk_sel                :  2; /* [ 2: 1],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_isp_clk_div                :  8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_hdmi_clk_div_en            :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_disp_clk_sel               :  1; /* [   17],        r/w,        0x0 */
            uint32_t reserved_18_19                 :  2; /* [19:18],       rsvd,        0x0 */
            uint32_t reg_disp_clk_div               :  4; /* [23:20],        r/w,        0x0 */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } isp_dp_clk;

    /* 0xC : codec_clk */
    union {
        struct {
            uint32_t reserved_0_7                   :  8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t reg_h264_clk_div_en            :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_h264_clk_sel               :  2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t reg_h264_clk_div               :  3; /* [14:12],       rsvd,        0x0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } codec_clk;

    /* 0x10 : mm_clk_ctrl_peri */
    union {
        struct {
            uint32_t reg_i2c_clk_div                :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_i2c_clk_div_en             :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_i2cA_clk_en                :  1; /* [    9],        r/w,        0x1 */
            uint32_t reg_i2cB_clk_en                :  1; /* [   10],        r/w,        0x1 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t reg_sdh_clk_en                 :  1; /* [   12],        r/w,        0x1 */
            uint32_t reg_sdh_clk_sel                :  3; /* [15:13],        r/w,        0x0 */
            uint32_t reg_uart_clk_div_en            :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_uart_clk_div               :  3; /* [19:17],        r/w,        0x0 */
            uint32_t reg_eth_clk_en                 :  1; /* [   20],        r/w,        0x1 */
            uint32_t reg_eth_clk_sel                :  2; /* [22:21],        r/w,        0x0 */
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
            uint32_t reg_i2s1_clk_div               :  6; /* [13: 8],        r/w,        0x0 */
            uint32_t reg_i2s1_ref_clk_oe            :  1; /* [   14],        r/w,        0x1 */
            uint32_t reg_i2s1_clk_en                :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_pdm0_clk_div               :  6; /* [21:16],        r/w,        0x1 */
            uint32_t reg_pdm0_clk_en                :  1; /* [   22],        r/w,        0x1 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t reg_pdm1_clk_div               :  6; /* [29:24],        r/w,        0x1 */
            uint32_t reg_pdm1_clk_en                :  1; /* [   30],        r/w,        0x1 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_ctrl_peri2;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : mm_clk_32k */
    union {
        struct {
            uint32_t reg_en_dig_32k_gen             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_en_comp_sat                :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_512k_sel                   :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_dig_32k_cnt                : 11; /* [14: 4],        r/w,      0x4b0 */
            uint32_t reserved_15_31                 : 17; /* [31:15],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_clk_32k;

    /* 0x24  reserved */
    uint8_t RESERVED0x24[28];

    /* 0x40 : mm_sw_sys_reset */
    union {
        struct {
            uint32_t reg_ctrl_sys_reset             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_ctrl_cpu_reset             :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_ctrl_pwron_rst             :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_ctrl_a5_cpu_reset          :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_ctrl_a5_dbg_reset          :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_ctrl_a5_peri_reset         :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_ctrl_a5_scu_reset          :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_ctrl_a5_wdt_reset          :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t reg_ctrl_e74_reset             :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_sw_sys_reset;

    /* 0x44 : sw_reset_mm_peri */
    union {
        struct {
            uint32_t swrst_mm_misc                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t swrst_dma                      :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_uart                     :  1; /* [    2],        r/w,        0x0 */
            uint32_t swrst_i2cA                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t swrst_i2cB                     :  1; /* [    4],        r/w,        0x0 */
            uint32_t swrst_psramA                   :  1; /* [    5],        r/w,        0x0 */
            uint32_t swrst_psramB                   :  1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t swrst_spi                      :  1; /* [    8],        r/w,        0x0 */
            uint32_t swrst_cci                      :  1; /* [    9],        r/w,        0x0 */
            uint32_t swrst_i2s0                     :  1; /* [   10],        r/w,        0x0 */
            uint32_t swrst_i2s1                     :  1; /* [   11],        r/w,        0x0 */
            uint32_t swrst_pdm0                     :  1; /* [   12],        r/w,        0x0 */
            uint32_t swrst_pdm1                     :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t swrst_sdh                      :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_23                 :  7; /* [23:17],       rsvd,        0x0 */
            uint32_t swrst_eth                      :  1; /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_mm_peri;

    /* 0x48 : sw_reset_isp_sub */
    union {
        struct {
            uint32_t swrst_isp_misc                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t swrst_isp_main                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_isp_tsrc                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t swrst_hdmi_tsrc                :  1; /* [    3],        r/w,        0x0 */
            uint32_t swrst_nr3d_ctrl                :  1; /* [    4],        r/w,        0x0 */
            uint32_t swrst_dvp2busA                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t swrst_dvp2busB                 :  1; /* [    6],        r/w,        0x0 */
            uint32_t swrst_dvp2busC                 :  1; /* [    7],        r/w,        0x0 */
            uint32_t swrst_dvp2busD                 :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9_15                  :  7; /* [15: 9],       rsvd,        0x0 */
            uint32_t swrst_isp_reg                  :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_isp_sub;

    /* 0x4C : sw_reset_codec_sub */
    union {
        struct {
            uint32_t swrst_codec_misc               :  1; /* [    0],        r/w,        0x0 */
            uint32_t swrst_mjpeg                    :  1; /* [    1],        r/w,        0x0 */
            uint32_t swrst_h264                     :  1; /* [    2],        r/w,        0x0 */
            uint32_t swrst_mjpegdec                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t swrst_npu                      :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_15                  : 11; /* [15: 5],       rsvd,        0x0 */
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

    /* 0x54  reserved */
    uint8_t RESERVED0x54[12];

    /* 0x60 : sw_reset_mask */
    union {
        struct {
            uint32_t reg_rst_mask_a5sys_to_sys      :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_sys      :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5sys_to_a5cpu    :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_a5cpu    :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5sys_to_a5dbg    :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_a5dbg    :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5sys_to_a5peri   :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_a5peri   :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5sys_to_a5scu    :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_a5scu    :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5sys_to_a5wdt    :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_rst_mask_a5wdt_to_a5wdt    :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_rst_mask_e74_to_sys        :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_rst_mask_e74_to_e74        :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_31                 : 18; /* [31:14],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } sw_reset_mask;

    /* 0x64  reserved */
    uint8_t RESERVED0x64[28];

    /* 0x80 : SYS_TICK_CFG */
    union {
        struct {
            uint32_t STCALIB                        : 26; /* [25: 0],        r/w,     0x270f */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } SYS_TICK_CFG;

    /* 0x84  reserved */
    uint8_t RESERVED0x84[124];

    /* 0x100 : clkpll register 1 */
    union {
        struct {
            uint32_t clkpll_ppu                     :  1; /* [    0],        r/w,        0x0 */
            uint32_t clkpll_pu                      :  1; /* [    1],        r/w,        0x0 */
            uint32_t clkpll2_ppu                    :  1; /* [    2],        r/w,        0x0 */
            uint32_t clkpll2_pu                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t ten_clkpll                     :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t ten_clkpll2                    :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t dtest_clkip_en                 :  2; /* [13:12],        r/w,        0x0 */
            uint32_t dtest_clk25M_en                :  1; /* [   14],        r/w,        0x0 */
            uint32_t dtest_pulldown                 :  1; /* [   15],        r/w,        0x1 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip1;

    /* 0x104 : clkpll register 2 */
    union {
        struct {
            uint32_t clkpll_pu_vcon_cmp             :  1; /* [    0],        r/w,        0x1 */
            uint32_t clkpll_pu_pfd                  :  1; /* [    1],        r/w,        0x1 */
            uint32_t clkpll_pu_cp                   :  1; /* [    2],        r/w,        0x1 */
            uint32_t clkpll_vcon_force_en           :  1; /* [    3],        r/w,        0x1 */
            uint32_t clkpll_cp3_scale               :  2; /* [ 5: 4],        r/w,        0x3 */
            uint32_t clkpll_res_scale               :  3; /* [ 8: 6],        r/w,        0x4 */
            uint32_t clkpll_refdiv_ratio            :  4; /* [12: 9],        r/w,        0x1 */
            uint32_t clkpll_fbdiv_ratio             : 10; /* [22:13],        r/w,       0x19 */
            uint32_t clkpll_icp                     :  3; /* [25:23],        r/w,        0x3 */
            uint32_t clkpll_shrtr                   :  1; /* [   26],        r/w,        0x0 */
            uint32_t clkpll_ringcap_en              :  1; /* [   27],        r/w,        0x1 */
            uint32_t clkpll_reset                   :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip2;

    /* 0x108 : clkpll register 3 */
    union {
        struct {
            uint32_t clkpll_vctrl_cmp               :  2; /* [ 1: 0],          r,        0x0 */
            uint32_t clkpll_vctrl_range             :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t clkpll_v2i_r_cal               :  4; /* [ 7: 4],        r/w,        0x7 */
            uint32_t clkpll_v2i_idac                :  4; /* [11: 8],        r/w,        0x6 */
            uint32_t clkpll_cp_opamp_en             :  1; /* [   12],        r/w,        0x1 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip3;

    /* 0x10C : clkpll register 4 */
    union {
        struct {
            uint32_t clkpll2_pu_vcon_cmp            :  1; /* [    0],        r/w,        0x1 */
            uint32_t clkpll2_pu_pfd                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t clkpll2_pu_cp                  :  1; /* [    2],        r/w,        0x1 */
            uint32_t clkpll2_vcon_force_en          :  1; /* [    3],        r/w,        0x1 */
            uint32_t clkpll2_cp3_scale              :  2; /* [ 5: 4],        r/w,        0x3 */
            uint32_t clkpll2_res_scale              :  3; /* [ 8: 6],        r/w,        0x4 */
            uint32_t clkpll2_refdiv_ratio           :  4; /* [12: 9],        r/w,        0x2 */
            uint32_t clkpll2_fbdiv_ratio            : 10; /* [22:13],        r/w,       0x14 */
            uint32_t clkpll2_icp                    :  3; /* [25:23],        r/w,        0x3 */
            uint32_t clkpll2_shrtr                  :  1; /* [   26],        r/w,        0x0 */
            uint32_t clkpll2_ringcap_en             :  1; /* [   27],        r/w,        0x0 */
            uint32_t clkpll2_reset                  :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip4;

    /* 0x110 : clkpll register 5 */
    union {
        struct {
            uint32_t clkpll2_vctrl_cmp              :  2; /* [ 1: 0],          r,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t clkpll2_vctrl_range            :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t clkpll2_v2i_r_cal              :  4; /* [11: 8],        r/w,        0x7 */
            uint32_t clkpll2_v2i_idac               :  4; /* [15:12],        r/w,        0x6 */
            uint32_t clkpll2_cp_opamp_en            :  1; /* [   16],        r/w,        0x1 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip5;

    /* 0x114 : clkip prediv */
    union {
        struct {
            uint32_t prediv_ref_sel                 :  3; /* [ 2: 0],        r/w,        0x7 */
            uint32_t pu_prediv                      :  1; /* [    3],        r/w,        0x1 */
            uint32_t prediv                         :  7; /* [10: 4],        r/w,        0xc */
            uint32_t reset_prediv                   :  1; /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip_prediv;

    /* 0x118 : clkip postdiv */
    union {
        struct {
            uint32_t reserved_0                     :  1; /* [    0],       rsvd,        0x0 */
            uint32_t clkpll_en_400M_clk             :  1; /* [    1],        r/w,        0x0 */
            uint32_t clkpll_en_320M_clk             :  1; /* [    2],        r/w,        0x0 */
            uint32_t clkpll_en_267M_clk             :  1; /* [    3],        r/w,        0x0 */
            uint32_t clkpll_en_240M_clk             :  1; /* [    4],        r/w,        0x0 */
            uint32_t clkpll_en_192M_clk             :  1; /* [    5],        r/w,        0x0 */
            uint32_t clkpll_en_160M_clk             :  1; /* [    6],        r/w,        0x1 */
            uint32_t clkpll_en_120M_clk             :  1; /* [    7],        r/w,        0x0 */
            uint32_t clkpll_en_100M_clk             :  1; /* [    8],        r/w,        0x0 */
            uint32_t clkpll_en_50M_clk              :  1; /* [    9],        r/w,        0x0 */
            uint32_t clkpll_en_25M_clk              :  1; /* [   10],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t pll_clk_sel                    :  2; /* [13:12],        r/w,        0x0 */
            uint32_t pu_postdiv                     :  1; /* [   14],        r/w,        0x1 */
            uint32_t reserved_15_31                 : 17; /* [31:15],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip_postdiv;

    /* 0x11C : clkip aupll register 1 */
    union {
        struct {
            uint32_t aupll_vco_speed                :  3; /* [ 2: 0],        r/w,        0x4 */
            uint32_t aupll_icp                      :  3; /* [ 5: 3],        r/w,        0x3 */
            uint32_t aupll_r4_short                 :  1; /* [    6],        r/w,        0x0 */
            uint32_t aupll_r4                       :  2; /* [ 8: 7],        r/w,        0x2 */
            uint32_t aupll_c3                       :  2; /* [10: 9],        r/w,        0x3 */
            uint32_t aupll_cz                       :  2; /* [12:11],        r/w,        0x2 */
            uint32_t aupll_rz                       :  2; /* [14:13],        r/w,        0x2 */
            uint32_t reserved_15_20                 :  6; /* [20:15],       rsvd,        0x0 */
            uint32_t aupll_refdiv_ratio             :  4; /* [24:21],        r/w,        0x3 */
            uint32_t aupll_reset_refdiv             :  1; /* [   25],        r/w,        0x0 */
            uint32_t aupll_shrtr                    :  1; /* [   26],        r/w,        0x0 */
            uint32_t aupll_pu_pfd                   :  1; /* [   27],        r/w,        0x1 */
            uint32_t aupll_reset_fbdv               :  1; /* [   28],        r/w,        0x0 */
            uint32_t aupll_pu_fbdv                  :  1; /* [   29],        r/w,        0x1 */
            uint32_t aupll_cp_opamp_en              :  1; /* [   30],        r/w,        0x1 */
            uint32_t aupll_pu_cp                    :  1; /* [   31],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } clkip_aupll1;

    /* 0x120 : clkip aupll register 2 */
    union {
        struct {
            uint32_t aupll_sdmin                    : 24; /* [23: 0],        r/w,   0x4ccccd */
            uint32_t reserved_24_31                 :  8; /* [31:24],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip_aupll2;

    /* 0x124 : clkip aupll register 3 */
    union {
        struct {
            uint32_t aupll_pu                       :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1                     :  1; /* [    1],       rsvd,        0x0 */
            uint32_t ten_aupll                      :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t dtest_aupll_fsdm_en            :  1; /* [    4],        r/w,        0x0 */
            uint32_t dtest_aupll_fref_en            :  1; /* [    5],        r/w,        0x0 */
            uint32_t dtest_aupll_fin_en             :  1; /* [    6],        r/w,        0x0 */
            uint32_t aupll_postdiv                  :  7; /* [13: 7],        r/w,       0x14 */
            uint32_t aupll_sel_sample_clk           :  2; /* [15:14],        r/w,        0x1 */
            uint32_t aupll_reset_postdiv            :  1; /* [   16],        r/w,        0x0 */
            uint32_t aupll_sel_fb_clk               :  2; /* [18:17],        r/w,        0x0 */
            uint32_t aupll_sdm_reset                :  1; /* [   19],        r/w,        0x0 */
            uint32_t aupll_sdm_flag                 :  1; /* [   20],        r/w,        0x1 */
            uint32_t aupll_sdm_bypass               :  1; /* [   21],        r/w,        0x0 */
            uint32_t aupll_dither_sel               :  2; /* [23:22],        r/w,        0x0 */
            uint32_t dtest_aupll_clk_en             :  1; /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_31                 :  7; /* [31:25],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } clkip_aupll3;

    /* 0x128 : cip register */
    union {
        struct {
            uint32_t pu_mbg                         :  1; /* [    0],        r/w,        0x0 */
            uint32_t pu_sfreg                       :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t vg11_sel                       :  2; /* [ 5: 4],        r/w,        0x2 */
            uint32_t vg15_sel                       :  2; /* [ 7: 6],        r/w,        0x2 */
            uint32_t ten_mbg                        :  1; /* [    8],        r/w,        0x0 */
            uint32_t ten_sfreg                      :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_11                 :  2; /* [11:10],       rsvd,        0x0 */
            uint32_t tmux                           :  3; /* [14:12],        r/w,        0x0 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t dc_tp_out_en                   :  1; /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cip;

    /* 0x12C : ldo11 register 1 */
    union {
        struct {
            uint32_t ldo11_cfg0                     : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ldo11_1;

    /* 0x130 : ldo11 register 2 */
    union {
        struct {
            uint32_t ldo11_cfg1                     : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } ldo11_2;

    /* 0x134 : rf reserved register */
    union {
        struct {
            uint32_t rf_resv0                       : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t rf_resv1                       : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } rf_resv;

    /* 0x138 : rf reserved register */
    union {
        struct {
            uint32_t rf_out_resv                    : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } rf_out_resv;

};

typedef volatile struct clkrst_reg clkrst_reg_t;


#endif  /* __CLKRST_REG_H__ */
