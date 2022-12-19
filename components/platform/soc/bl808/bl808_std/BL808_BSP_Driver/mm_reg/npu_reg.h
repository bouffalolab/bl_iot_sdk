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
#ifndef  __NPU_REG_H__
#define  __NPU_REG_H__

#include "bl808.h"

/* 0x00 : BALI_GENERAL_CFG */
#define NPU_BALI_GENERAL_CFG_OFFSET                             (0x00)
#define NPU_REG_IMGI_UNSGN                                      NPU_REG_IMGI_UNSGN
#define NPU_REG_IMGI_UNSGN_POS                                  (0U)
#define NPU_REG_IMGI_UNSGN_LEN                                  (1U)
#define NPU_REG_IMGI_UNSGN_MSK                                  (((1U<<NPU_REG_IMGI_UNSGN_LEN)-1)<<NPU_REG_IMGI_UNSGN_POS)
#define NPU_REG_IMGI_UNSGN_UMSK                                 (~(((1U<<NPU_REG_IMGI_UNSGN_LEN)-1)<<NPU_REG_IMGI_UNSGN_POS))
#define NPU_REG_IMG_IN_MODE                                     NPU_REG_IMG_IN_MODE
#define NPU_REG_IMG_IN_MODE_POS                                 (8U)
#define NPU_REG_IMG_IN_MODE_LEN                                 (2U)
#define NPU_REG_IMG_IN_MODE_MSK                                 (((1U<<NPU_REG_IMG_IN_MODE_LEN)-1)<<NPU_REG_IMG_IN_MODE_POS)
#define NPU_REG_IMG_IN_MODE_UMSK                                (~(((1U<<NPU_REG_IMG_IN_MODE_LEN)-1)<<NPU_REG_IMG_IN_MODE_POS))
#define NPU_REG_FTABLE_IDX_BASE                                 NPU_REG_FTABLE_IDX_BASE
#define NPU_REG_FTABLE_IDX_BASE_POS                             (16U)
#define NPU_REG_FTABLE_IDX_BASE_LEN                             (6U)
#define NPU_REG_FTABLE_IDX_BASE_MSK                             (((1U<<NPU_REG_FTABLE_IDX_BASE_LEN)-1)<<NPU_REG_FTABLE_IDX_BASE_POS)
#define NPU_REG_FTABLE_IDX_BASE_UMSK                            (~(((1U<<NPU_REG_FTABLE_IDX_BASE_LEN)-1)<<NPU_REG_FTABLE_IDX_BASE_POS))
#define NPU_REG_FTABLE_DAT_BASE                                 NPU_REG_FTABLE_DAT_BASE
#define NPU_REG_FTABLE_DAT_BASE_POS                             (24U)
#define NPU_REG_FTABLE_DAT_BASE_LEN                             (6U)
#define NPU_REG_FTABLE_DAT_BASE_MSK                             (((1U<<NPU_REG_FTABLE_DAT_BASE_LEN)-1)<<NPU_REG_FTABLE_DAT_BASE_POS)
#define NPU_REG_FTABLE_DAT_BASE_UMSK                            (~(((1U<<NPU_REG_FTABLE_DAT_BASE_LEN)-1)<<NPU_REG_FTABLE_DAT_BASE_POS))
#define NPU_AXI_W_IDLE                                          NPU_AXI_W_IDLE
#define NPU_AXI_W_IDLE_POS                                      (30U)
#define NPU_AXI_W_IDLE_LEN                                      (1U)
#define NPU_AXI_W_IDLE_MSK                                      (((1U<<NPU_AXI_W_IDLE_LEN)-1)<<NPU_AXI_W_IDLE_POS)
#define NPU_AXI_W_IDLE_UMSK                                     (~(((1U<<NPU_AXI_W_IDLE_LEN)-1)<<NPU_AXI_W_IDLE_POS))
#define NPU_AXI_R_IDLE                                          NPU_AXI_R_IDLE
#define NPU_AXI_R_IDLE_POS                                      (31U)
#define NPU_AXI_R_IDLE_LEN                                      (1U)
#define NPU_AXI_R_IDLE_MSK                                      (((1U<<NPU_AXI_R_IDLE_LEN)-1)<<NPU_AXI_R_IDLE_POS)
#define NPU_AXI_R_IDLE_UMSK                                     (~(((1U<<NPU_AXI_R_IDLE_LEN)-1)<<NPU_AXI_R_IDLE_POS))

/* 0x04 : BLAI_INT_CFG */
#define NPU_BLAI_INT_CFG_OFFSET                                 (0x04)
#define NPU_REG_BLAI_START                                      NPU_REG_BLAI_START
#define NPU_REG_BLAI_START_POS                                  (0U)
#define NPU_REG_BLAI_START_LEN                                  (1U)
#define NPU_REG_BLAI_START_MSK                                  (((1U<<NPU_REG_BLAI_START_LEN)-1)<<NPU_REG_BLAI_START_POS)
#define NPU_REG_BLAI_START_UMSK                                 (~(((1U<<NPU_REG_BLAI_START_LEN)-1)<<NPU_REG_BLAI_START_POS))
#define NPU_REG_BLAI_STOP                                       NPU_REG_BLAI_STOP
#define NPU_REG_BLAI_STOP_POS                                   (1U)
#define NPU_REG_BLAI_STOP_LEN                                   (1U)
#define NPU_REG_BLAI_STOP_MSK                                   (((1U<<NPU_REG_BLAI_STOP_LEN)-1)<<NPU_REG_BLAI_STOP_POS)
#define NPU_REG_BLAI_STOP_UMSK                                  (~(((1U<<NPU_REG_BLAI_STOP_LEN)-1)<<NPU_REG_BLAI_STOP_POS))
#define NPU_REG_BLAI_RESUME                                     NPU_REG_BLAI_RESUME
#define NPU_REG_BLAI_RESUME_POS                                 (2U)
#define NPU_REG_BLAI_RESUME_LEN                                 (1U)
#define NPU_REG_BLAI_RESUME_MSK                                 (((1U<<NPU_REG_BLAI_RESUME_LEN)-1)<<NPU_REG_BLAI_RESUME_POS)
#define NPU_REG_BLAI_RESUME_UMSK                                (~(((1U<<NPU_REG_BLAI_RESUME_LEN)-1)<<NPU_REG_BLAI_RESUME_POS))
#define NPU_REG_INT_CLR                                         NPU_REG_INT_CLR
#define NPU_REG_INT_CLR_POS                                     (8U)
#define NPU_REG_INT_CLR_LEN                                     (1U)
#define NPU_REG_INT_CLR_MSK                                     (((1U<<NPU_REG_INT_CLR_LEN)-1)<<NPU_REG_INT_CLR_POS)
#define NPU_REG_INT_CLR_UMSK                                    (~(((1U<<NPU_REG_INT_CLR_LEN)-1)<<NPU_REG_INT_CLR_POS))
#define NPU_STS_BLAI_INT                                        NPU_STS_BLAI_INT
#define NPU_STS_BLAI_INT_POS                                    (9U)
#define NPU_STS_BLAI_INT_LEN                                    (1U)
#define NPU_STS_BLAI_INT_MSK                                    (((1U<<NPU_STS_BLAI_INT_LEN)-1)<<NPU_STS_BLAI_INT_POS)
#define NPU_STS_BLAI_INT_UMSK                                   (~(((1U<<NPU_STS_BLAI_INT_LEN)-1)<<NPU_STS_BLAI_INT_POS))
#define NPU_REG_RELU_N                                          NPU_REG_RELU_N 
#define NPU_REG_RELU_N_POS                                      (16U)
#define NPU_REG_RELU_N_LEN                                      (5U)
#define NPU_REG_RELU_N_MSK                                      (((1U<<NPU_REG_RELU_N_LEN)-1)<<NPU_REG_RELU_N_POS)
#define NPU_REG_RELU_N_UMSK                                     (~(((1U<<NPU_REG_RELU_N_LEN)-1)<<NPU_REG_RELU_N_POS))

/* 0x10 : BLAI_WEIGHT_ADDR */
#define NPU_BLAI_WEIGHT_ADDR_OFFSET                             (0x10)
#define NPU_REG_WEIG_ADDR_BASE                                  NPU_REG_WEIG_ADDR_BASE
#define NPU_REG_WEIG_ADDR_BASE_POS                              (0U)
#define NPU_REG_WEIG_ADDR_BASE_LEN                              (32U)
#define NPU_REG_WEIG_ADDR_BASE_MSK                              (((1U<<NPU_REG_WEIG_ADDR_BASE_LEN)-1)<<NPU_REG_WEIG_ADDR_BASE_POS)
#define NPU_REG_WEIG_ADDR_BASE_UMSK                             (~(((1U<<NPU_REG_WEIG_ADDR_BASE_LEN)-1)<<NPU_REG_WEIG_ADDR_BASE_POS))

/* 0x14 : BLAI_BIAS_ADDR */
#define NPU_BLAI_BIAS_ADDR_OFFSET                               (0x14)
#define NPU_REG_BIAS_ADDR_BASE                                  NPU_REG_BIAS_ADDR_BASE
#define NPU_REG_BIAS_ADDR_BASE_POS                              (0U)
#define NPU_REG_BIAS_ADDR_BASE_LEN                              (32U)
#define NPU_REG_BIAS_ADDR_BASE_MSK                              (((1U<<NPU_REG_BIAS_ADDR_BASE_LEN)-1)<<NPU_REG_BIAS_ADDR_BASE_POS)
#define NPU_REG_BIAS_ADDR_BASE_UMSK                             (~(((1U<<NPU_REG_BIAS_ADDR_BASE_LEN)-1)<<NPU_REG_BIAS_ADDR_BASE_POS))

/* 0x18 : BLAI_INST_ADDR */
#define NPU_BLAI_INST_ADDR_OFFSET                               (0x18)
#define NPU_REG_INST_ADDR_BASE                                  NPU_REG_INST_ADDR_BASE
#define NPU_REG_INST_ADDR_BASE_POS                              (0U)
#define NPU_REG_INST_ADDR_BASE_LEN                              (32U)
#define NPU_REG_INST_ADDR_BASE_MSK                              (((1U<<NPU_REG_INST_ADDR_BASE_LEN)-1)<<NPU_REG_INST_ADDR_BASE_POS)
#define NPU_REG_INST_ADDR_BASE_UMSK                             (~(((1U<<NPU_REG_INST_ADDR_BASE_LEN)-1)<<NPU_REG_INST_ADDR_BASE_POS))

/* 0x1C : APU_DM0_ADDR */
#define NPU_APU_DM0_ADDR_OFFSET                                 (0x1C)
#define NPU_REG_IMG_ADDR_BASE                                   NPU_REG_IMG_ADDR_BASE
#define NPU_REG_IMG_ADDR_BASE_POS                               (0U)
#define NPU_REG_IMG_ADDR_BASE_LEN                               (32U)
#define NPU_REG_IMG_ADDR_BASE_MSK                               (((1U<<NPU_REG_IMG_ADDR_BASE_LEN)-1)<<NPU_REG_IMG_ADDR_BASE_POS)
#define NPU_REG_IMG_ADDR_BASE_UMSK                              (~(((1U<<NPU_REG_IMG_ADDR_BASE_LEN)-1)<<NPU_REG_IMG_ADDR_BASE_POS))

/* 0x20 : APU_DM1_ADDR */
#define NPU_APU_DM1_ADDR_OFFSET                                 (0x20)
#define NPU_REG_IMG_MEM_SEG                                     NPU_REG_IMG_MEM_SEG
#define NPU_REG_IMG_MEM_SEG_POS                                 (0U)
#define NPU_REG_IMG_MEM_SEG_LEN                                 (32U)
#define NPU_REG_IMG_MEM_SEG_MSK                                 (((1U<<NPU_REG_IMG_MEM_SEG_LEN)-1)<<NPU_REG_IMG_MEM_SEG_POS)
#define NPU_REG_IMG_MEM_SEG_UMSK                                (~(((1U<<NPU_REG_IMG_MEM_SEG_LEN)-1)<<NPU_REG_IMG_MEM_SEG_POS))

/* 0x24 : BLAI_TF_CFG0 */
#define NPU_BLAI_TF_CFG0_OFFSET                                 (0x24)
#define NPU_REG_TENFLOW_EN                                      NPU_REG_TENFLOW_EN
#define NPU_REG_TENFLOW_EN_POS                                  (31U)
#define NPU_REG_TENFLOW_EN_LEN                                  (1U)
#define NPU_REG_TENFLOW_EN_MSK                                  (((1U<<NPU_REG_TENFLOW_EN_LEN)-1)<<NPU_REG_TENFLOW_EN_POS)
#define NPU_REG_TENFLOW_EN_UMSK                                 (~(((1U<<NPU_REG_TENFLOW_EN_LEN)-1)<<NPU_REG_TENFLOW_EN_POS))

/* 0x100 : BLAI_ACT_TABLE00 */
#define NPU_BLAI_ACT_TABLE00_OFFSET                             (0x100)
#define NPU_REG_ACT_TABLE_00                                    NPU_REG_ACT_TABLE_00
#define NPU_REG_ACT_TABLE_00_POS                                (0U)
#define NPU_REG_ACT_TABLE_00_LEN                                (8U)
#define NPU_REG_ACT_TABLE_00_MSK                                (((1U<<NPU_REG_ACT_TABLE_00_LEN)-1)<<NPU_REG_ACT_TABLE_00_POS)
#define NPU_REG_ACT_TABLE_00_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_00_LEN)-1)<<NPU_REG_ACT_TABLE_00_POS))
#define NPU_REG_ACT_TABLE_01                                    NPU_REG_ACT_TABLE_01
#define NPU_REG_ACT_TABLE_01_POS                                (8U)
#define NPU_REG_ACT_TABLE_01_LEN                                (8U)
#define NPU_REG_ACT_TABLE_01_MSK                                (((1U<<NPU_REG_ACT_TABLE_01_LEN)-1)<<NPU_REG_ACT_TABLE_01_POS)
#define NPU_REG_ACT_TABLE_01_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_01_LEN)-1)<<NPU_REG_ACT_TABLE_01_POS))
#define NPU_REG_ACT_TABLE_02                                    NPU_REG_ACT_TABLE_02
#define NPU_REG_ACT_TABLE_02_POS                                (16U)
#define NPU_REG_ACT_TABLE_02_LEN                                (8U)
#define NPU_REG_ACT_TABLE_02_MSK                                (((1U<<NPU_REG_ACT_TABLE_02_LEN)-1)<<NPU_REG_ACT_TABLE_02_POS)
#define NPU_REG_ACT_TABLE_02_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_02_LEN)-1)<<NPU_REG_ACT_TABLE_02_POS))
#define NPU_REG_ACT_TABLE_03                                    NPU_REG_ACT_TABLE_03
#define NPU_REG_ACT_TABLE_03_POS                                (24U)
#define NPU_REG_ACT_TABLE_03_LEN                                (8U)
#define NPU_REG_ACT_TABLE_03_MSK                                (((1U<<NPU_REG_ACT_TABLE_03_LEN)-1)<<NPU_REG_ACT_TABLE_03_POS)
#define NPU_REG_ACT_TABLE_03_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_03_LEN)-1)<<NPU_REG_ACT_TABLE_03_POS))

/* 0x104 : BLAI_ACT_TABLE07_04 */
#define NPU_BLAI_ACT_TABLE07_04_OFFSET                          (0x104)
#define NPU_REG_ACT_TABLE_04                                    NPU_REG_ACT_TABLE_04
#define NPU_REG_ACT_TABLE_04_POS                                (0U)
#define NPU_REG_ACT_TABLE_04_LEN                                (8U)
#define NPU_REG_ACT_TABLE_04_MSK                                (((1U<<NPU_REG_ACT_TABLE_04_LEN)-1)<<NPU_REG_ACT_TABLE_04_POS)
#define NPU_REG_ACT_TABLE_04_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_04_LEN)-1)<<NPU_REG_ACT_TABLE_04_POS))
#define NPU_REG_ACT_TABLE_05                                    NPU_REG_ACT_TABLE_05
#define NPU_REG_ACT_TABLE_05_POS                                (8U)
#define NPU_REG_ACT_TABLE_05_LEN                                (8U)
#define NPU_REG_ACT_TABLE_05_MSK                                (((1U<<NPU_REG_ACT_TABLE_05_LEN)-1)<<NPU_REG_ACT_TABLE_05_POS)
#define NPU_REG_ACT_TABLE_05_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_05_LEN)-1)<<NPU_REG_ACT_TABLE_05_POS))
#define NPU_REG_ACT_TABLE_06                                    NPU_REG_ACT_TABLE_06
#define NPU_REG_ACT_TABLE_06_POS                                (16U)
#define NPU_REG_ACT_TABLE_06_LEN                                (8U)
#define NPU_REG_ACT_TABLE_06_MSK                                (((1U<<NPU_REG_ACT_TABLE_06_LEN)-1)<<NPU_REG_ACT_TABLE_06_POS)
#define NPU_REG_ACT_TABLE_06_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_06_LEN)-1)<<NPU_REG_ACT_TABLE_06_POS))
#define NPU_REG_ACT_TABLE_07                                    NPU_REG_ACT_TABLE_07
#define NPU_REG_ACT_TABLE_07_POS                                (24U)
#define NPU_REG_ACT_TABLE_07_LEN                                (8U)
#define NPU_REG_ACT_TABLE_07_MSK                                (((1U<<NPU_REG_ACT_TABLE_07_LEN)-1)<<NPU_REG_ACT_TABLE_07_POS)
#define NPU_REG_ACT_TABLE_07_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_07_LEN)-1)<<NPU_REG_ACT_TABLE_07_POS))

/* 0x108 : BLAI_ACT_TABLE0B_08 */
#define NPU_BLAI_ACT_TABLE0B_08_OFFSET                          (0x108)
#define NPU_REG_ACT_TABLE_08                                    NPU_REG_ACT_TABLE_08
#define NPU_REG_ACT_TABLE_08_POS                                (0U)
#define NPU_REG_ACT_TABLE_08_LEN                                (8U)
#define NPU_REG_ACT_TABLE_08_MSK                                (((1U<<NPU_REG_ACT_TABLE_08_LEN)-1)<<NPU_REG_ACT_TABLE_08_POS)
#define NPU_REG_ACT_TABLE_08_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_08_LEN)-1)<<NPU_REG_ACT_TABLE_08_POS))
#define NPU_REG_ACT_TABLE_09                                    NPU_REG_ACT_TABLE_09
#define NPU_REG_ACT_TABLE_09_POS                                (8U)
#define NPU_REG_ACT_TABLE_09_LEN                                (8U)
#define NPU_REG_ACT_TABLE_09_MSK                                (((1U<<NPU_REG_ACT_TABLE_09_LEN)-1)<<NPU_REG_ACT_TABLE_09_POS)
#define NPU_REG_ACT_TABLE_09_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_09_LEN)-1)<<NPU_REG_ACT_TABLE_09_POS))
#define NPU_REG_ACT_TABLE_0A                                    NPU_REG_ACT_TABLE_0A
#define NPU_REG_ACT_TABLE_0A_POS                                (16U)
#define NPU_REG_ACT_TABLE_0A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0A_MSK                                (((1U<<NPU_REG_ACT_TABLE_0A_LEN)-1)<<NPU_REG_ACT_TABLE_0A_POS)
#define NPU_REG_ACT_TABLE_0A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0A_LEN)-1)<<NPU_REG_ACT_TABLE_0A_POS))
#define NPU_REG_ACT_TABLE_0B                                    NPU_REG_ACT_TABLE_0B
#define NPU_REG_ACT_TABLE_0B_POS                                (24U)
#define NPU_REG_ACT_TABLE_0B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0B_MSK                                (((1U<<NPU_REG_ACT_TABLE_0B_LEN)-1)<<NPU_REG_ACT_TABLE_0B_POS)
#define NPU_REG_ACT_TABLE_0B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0B_LEN)-1)<<NPU_REG_ACT_TABLE_0B_POS))

/* 0x10C : BLAI_ACT_TABLE0F_0C */
#define NPU_BLAI_ACT_TABLE0F_0C_OFFSET                          (0x10C)
#define NPU_REG_ACT_TABLE_0C                                    NPU_REG_ACT_TABLE_0C
#define NPU_REG_ACT_TABLE_0C_POS                                (0U)
#define NPU_REG_ACT_TABLE_0C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0C_MSK                                (((1U<<NPU_REG_ACT_TABLE_0C_LEN)-1)<<NPU_REG_ACT_TABLE_0C_POS)
#define NPU_REG_ACT_TABLE_0C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0C_LEN)-1)<<NPU_REG_ACT_TABLE_0C_POS))
#define NPU_REG_ACT_TABLE_0D                                    NPU_REG_ACT_TABLE_0D
#define NPU_REG_ACT_TABLE_0D_POS                                (8U)
#define NPU_REG_ACT_TABLE_0D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0D_MSK                                (((1U<<NPU_REG_ACT_TABLE_0D_LEN)-1)<<NPU_REG_ACT_TABLE_0D_POS)
#define NPU_REG_ACT_TABLE_0D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0D_LEN)-1)<<NPU_REG_ACT_TABLE_0D_POS))
#define NPU_REG_ACT_TABLE_0E                                    NPU_REG_ACT_TABLE_0E
#define NPU_REG_ACT_TABLE_0E_POS                                (16U)
#define NPU_REG_ACT_TABLE_0E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0E_MSK                                (((1U<<NPU_REG_ACT_TABLE_0E_LEN)-1)<<NPU_REG_ACT_TABLE_0E_POS)
#define NPU_REG_ACT_TABLE_0E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0E_LEN)-1)<<NPU_REG_ACT_TABLE_0E_POS))
#define NPU_REG_ACT_TABLE_0F                                    NPU_REG_ACT_TABLE_0F
#define NPU_REG_ACT_TABLE_0F_POS                                (24U)
#define NPU_REG_ACT_TABLE_0F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_0F_MSK                                (((1U<<NPU_REG_ACT_TABLE_0F_LEN)-1)<<NPU_REG_ACT_TABLE_0F_POS)
#define NPU_REG_ACT_TABLE_0F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_0F_LEN)-1)<<NPU_REG_ACT_TABLE_0F_POS))

/* 0x110 : BLAI_ACT_TABLE13_10 */
#define NPU_BLAI_ACT_TABLE13_10_OFFSET                          (0x110)
#define NPU_REG_ACT_TABLE_10                                    NPU_REG_ACT_TABLE_10
#define NPU_REG_ACT_TABLE_10_POS                                (0U)
#define NPU_REG_ACT_TABLE_10_LEN                                (8U)
#define NPU_REG_ACT_TABLE_10_MSK                                (((1U<<NPU_REG_ACT_TABLE_10_LEN)-1)<<NPU_REG_ACT_TABLE_10_POS)
#define NPU_REG_ACT_TABLE_10_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_10_LEN)-1)<<NPU_REG_ACT_TABLE_10_POS))
#define NPU_REG_ACT_TABLE_11                                    NPU_REG_ACT_TABLE_11
#define NPU_REG_ACT_TABLE_11_POS                                (8U)
#define NPU_REG_ACT_TABLE_11_LEN                                (8U)
#define NPU_REG_ACT_TABLE_11_MSK                                (((1U<<NPU_REG_ACT_TABLE_11_LEN)-1)<<NPU_REG_ACT_TABLE_11_POS)
#define NPU_REG_ACT_TABLE_11_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_11_LEN)-1)<<NPU_REG_ACT_TABLE_11_POS))
#define NPU_REG_ACT_TABLE_12                                    NPU_REG_ACT_TABLE_12
#define NPU_REG_ACT_TABLE_12_POS                                (16U)
#define NPU_REG_ACT_TABLE_12_LEN                                (8U)
#define NPU_REG_ACT_TABLE_12_MSK                                (((1U<<NPU_REG_ACT_TABLE_12_LEN)-1)<<NPU_REG_ACT_TABLE_12_POS)
#define NPU_REG_ACT_TABLE_12_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_12_LEN)-1)<<NPU_REG_ACT_TABLE_12_POS))
#define NPU_REG_ACT_TABLE_13                                    NPU_REG_ACT_TABLE_13
#define NPU_REG_ACT_TABLE_13_POS                                (24U)
#define NPU_REG_ACT_TABLE_13_LEN                                (8U)
#define NPU_REG_ACT_TABLE_13_MSK                                (((1U<<NPU_REG_ACT_TABLE_13_LEN)-1)<<NPU_REG_ACT_TABLE_13_POS)
#define NPU_REG_ACT_TABLE_13_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_13_LEN)-1)<<NPU_REG_ACT_TABLE_13_POS))

/* 0x114 : BLAI_ACT_TABLE17_14 */
#define NPU_BLAI_ACT_TABLE17_14_OFFSET                          (0x114)
#define NPU_REG_ACT_TABLE_14                                    NPU_REG_ACT_TABLE_14
#define NPU_REG_ACT_TABLE_14_POS                                (0U)
#define NPU_REG_ACT_TABLE_14_LEN                                (8U)
#define NPU_REG_ACT_TABLE_14_MSK                                (((1U<<NPU_REG_ACT_TABLE_14_LEN)-1)<<NPU_REG_ACT_TABLE_14_POS)
#define NPU_REG_ACT_TABLE_14_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_14_LEN)-1)<<NPU_REG_ACT_TABLE_14_POS))
#define NPU_REG_ACT_TABLE_15                                    NPU_REG_ACT_TABLE_15
#define NPU_REG_ACT_TABLE_15_POS                                (8U)
#define NPU_REG_ACT_TABLE_15_LEN                                (8U)
#define NPU_REG_ACT_TABLE_15_MSK                                (((1U<<NPU_REG_ACT_TABLE_15_LEN)-1)<<NPU_REG_ACT_TABLE_15_POS)
#define NPU_REG_ACT_TABLE_15_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_15_LEN)-1)<<NPU_REG_ACT_TABLE_15_POS))
#define NPU_REG_ACT_TABLE_16                                    NPU_REG_ACT_TABLE_16
#define NPU_REG_ACT_TABLE_16_POS                                (16U)
#define NPU_REG_ACT_TABLE_16_LEN                                (8U)
#define NPU_REG_ACT_TABLE_16_MSK                                (((1U<<NPU_REG_ACT_TABLE_16_LEN)-1)<<NPU_REG_ACT_TABLE_16_POS)
#define NPU_REG_ACT_TABLE_16_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_16_LEN)-1)<<NPU_REG_ACT_TABLE_16_POS))
#define NPU_REG_ACT_TABLE_17                                    NPU_REG_ACT_TABLE_17
#define NPU_REG_ACT_TABLE_17_POS                                (24U)
#define NPU_REG_ACT_TABLE_17_LEN                                (8U)
#define NPU_REG_ACT_TABLE_17_MSK                                (((1U<<NPU_REG_ACT_TABLE_17_LEN)-1)<<NPU_REG_ACT_TABLE_17_POS)
#define NPU_REG_ACT_TABLE_17_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_17_LEN)-1)<<NPU_REG_ACT_TABLE_17_POS))

/* 0x118 : BLAI_ACT_TABLE1B_18 */
#define NPU_BLAI_ACT_TABLE1B_18_OFFSET                          (0x118)
#define NPU_REG_ACT_TABLE_18                                    NPU_REG_ACT_TABLE_18
#define NPU_REG_ACT_TABLE_18_POS                                (0U)
#define NPU_REG_ACT_TABLE_18_LEN                                (8U)
#define NPU_REG_ACT_TABLE_18_MSK                                (((1U<<NPU_REG_ACT_TABLE_18_LEN)-1)<<NPU_REG_ACT_TABLE_18_POS)
#define NPU_REG_ACT_TABLE_18_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_18_LEN)-1)<<NPU_REG_ACT_TABLE_18_POS))
#define NPU_REG_ACT_TABLE_19                                    NPU_REG_ACT_TABLE_19
#define NPU_REG_ACT_TABLE_19_POS                                (8U)
#define NPU_REG_ACT_TABLE_19_LEN                                (8U)
#define NPU_REG_ACT_TABLE_19_MSK                                (((1U<<NPU_REG_ACT_TABLE_19_LEN)-1)<<NPU_REG_ACT_TABLE_19_POS)
#define NPU_REG_ACT_TABLE_19_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_19_LEN)-1)<<NPU_REG_ACT_TABLE_19_POS))
#define NPU_REG_ACT_TABLE_1A                                    NPU_REG_ACT_TABLE_1A
#define NPU_REG_ACT_TABLE_1A_POS                                (16U)
#define NPU_REG_ACT_TABLE_1A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1A_MSK                                (((1U<<NPU_REG_ACT_TABLE_1A_LEN)-1)<<NPU_REG_ACT_TABLE_1A_POS)
#define NPU_REG_ACT_TABLE_1A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1A_LEN)-1)<<NPU_REG_ACT_TABLE_1A_POS))
#define NPU_REG_ACT_TABLE_1B                                    NPU_REG_ACT_TABLE_1B
#define NPU_REG_ACT_TABLE_1B_POS                                (24U)
#define NPU_REG_ACT_TABLE_1B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1B_MSK                                (((1U<<NPU_REG_ACT_TABLE_1B_LEN)-1)<<NPU_REG_ACT_TABLE_1B_POS)
#define NPU_REG_ACT_TABLE_1B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1B_LEN)-1)<<NPU_REG_ACT_TABLE_1B_POS))

/* 0x11C : BLAI_ACT_TABLE1F_1C */
#define NPU_BLAI_ACT_TABLE1F_1C_OFFSET                          (0x11C)
#define NPU_REG_ACT_TABLE_1C                                    NPU_REG_ACT_TABLE_1C
#define NPU_REG_ACT_TABLE_1C_POS                                (0U)
#define NPU_REG_ACT_TABLE_1C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1C_MSK                                (((1U<<NPU_REG_ACT_TABLE_1C_LEN)-1)<<NPU_REG_ACT_TABLE_1C_POS)
#define NPU_REG_ACT_TABLE_1C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1C_LEN)-1)<<NPU_REG_ACT_TABLE_1C_POS))
#define NPU_REG_ACT_TABLE_1D                                    NPU_REG_ACT_TABLE_1D
#define NPU_REG_ACT_TABLE_1D_POS                                (8U)
#define NPU_REG_ACT_TABLE_1D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1D_MSK                                (((1U<<NPU_REG_ACT_TABLE_1D_LEN)-1)<<NPU_REG_ACT_TABLE_1D_POS)
#define NPU_REG_ACT_TABLE_1D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1D_LEN)-1)<<NPU_REG_ACT_TABLE_1D_POS))
#define NPU_REG_ACT_TABLE_1E                                    NPU_REG_ACT_TABLE_1E
#define NPU_REG_ACT_TABLE_1E_POS                                (16U)
#define NPU_REG_ACT_TABLE_1E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1E_MSK                                (((1U<<NPU_REG_ACT_TABLE_1E_LEN)-1)<<NPU_REG_ACT_TABLE_1E_POS)
#define NPU_REG_ACT_TABLE_1E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1E_LEN)-1)<<NPU_REG_ACT_TABLE_1E_POS))
#define NPU_REG_ACT_TABLE_1F                                    NPU_REG_ACT_TABLE_1F
#define NPU_REG_ACT_TABLE_1F_POS                                (24U)
#define NPU_REG_ACT_TABLE_1F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_1F_MSK                                (((1U<<NPU_REG_ACT_TABLE_1F_LEN)-1)<<NPU_REG_ACT_TABLE_1F_POS)
#define NPU_REG_ACT_TABLE_1F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_1F_LEN)-1)<<NPU_REG_ACT_TABLE_1F_POS))

/* 0x120 : BLAI_ACT_TABLE_23_20 */
#define NPU_BLAI_ACT_TABLE_23_20_OFFSET                         (0x120)
#define NPU_REG_ACT_TABLE_20                                    NPU_REG_ACT_TABLE_20
#define NPU_REG_ACT_TABLE_20_POS                                (0U)
#define NPU_REG_ACT_TABLE_20_LEN                                (8U)
#define NPU_REG_ACT_TABLE_20_MSK                                (((1U<<NPU_REG_ACT_TABLE_20_LEN)-1)<<NPU_REG_ACT_TABLE_20_POS)
#define NPU_REG_ACT_TABLE_20_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_20_LEN)-1)<<NPU_REG_ACT_TABLE_20_POS))
#define NPU_REG_ACT_TABLE_21                                    NPU_REG_ACT_TABLE_21
#define NPU_REG_ACT_TABLE_21_POS                                (8U)
#define NPU_REG_ACT_TABLE_21_LEN                                (8U)
#define NPU_REG_ACT_TABLE_21_MSK                                (((1U<<NPU_REG_ACT_TABLE_21_LEN)-1)<<NPU_REG_ACT_TABLE_21_POS)
#define NPU_REG_ACT_TABLE_21_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_21_LEN)-1)<<NPU_REG_ACT_TABLE_21_POS))
#define NPU_REG_ACT_TABLE_22                                    NPU_REG_ACT_TABLE_22
#define NPU_REG_ACT_TABLE_22_POS                                (16U)
#define NPU_REG_ACT_TABLE_22_LEN                                (8U)
#define NPU_REG_ACT_TABLE_22_MSK                                (((1U<<NPU_REG_ACT_TABLE_22_LEN)-1)<<NPU_REG_ACT_TABLE_22_POS)
#define NPU_REG_ACT_TABLE_22_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_22_LEN)-1)<<NPU_REG_ACT_TABLE_22_POS))
#define NPU_REG_ACT_TABLE_23                                    NPU_REG_ACT_TABLE_23
#define NPU_REG_ACT_TABLE_23_POS                                (24U)
#define NPU_REG_ACT_TABLE_23_LEN                                (8U)
#define NPU_REG_ACT_TABLE_23_MSK                                (((1U<<NPU_REG_ACT_TABLE_23_LEN)-1)<<NPU_REG_ACT_TABLE_23_POS)
#define NPU_REG_ACT_TABLE_23_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_23_LEN)-1)<<NPU_REG_ACT_TABLE_23_POS))

/* 0x124 : BLAI_ACT_TABLE_27_24 */
#define NPU_BLAI_ACT_TABLE_27_24_OFFSET                         (0x124)
#define NPU_REG_ACT_TABLE_24                                    NPU_REG_ACT_TABLE_24
#define NPU_REG_ACT_TABLE_24_POS                                (0U)
#define NPU_REG_ACT_TABLE_24_LEN                                (8U)
#define NPU_REG_ACT_TABLE_24_MSK                                (((1U<<NPU_REG_ACT_TABLE_24_LEN)-1)<<NPU_REG_ACT_TABLE_24_POS)
#define NPU_REG_ACT_TABLE_24_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_24_LEN)-1)<<NPU_REG_ACT_TABLE_24_POS))
#define NPU_REG_ACT_TABLE_25                                    NPU_REG_ACT_TABLE_25
#define NPU_REG_ACT_TABLE_25_POS                                (8U)
#define NPU_REG_ACT_TABLE_25_LEN                                (8U)
#define NPU_REG_ACT_TABLE_25_MSK                                (((1U<<NPU_REG_ACT_TABLE_25_LEN)-1)<<NPU_REG_ACT_TABLE_25_POS)
#define NPU_REG_ACT_TABLE_25_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_25_LEN)-1)<<NPU_REG_ACT_TABLE_25_POS))
#define NPU_REG_ACT_TABLE_26                                    NPU_REG_ACT_TABLE_26
#define NPU_REG_ACT_TABLE_26_POS                                (16U)
#define NPU_REG_ACT_TABLE_26_LEN                                (8U)
#define NPU_REG_ACT_TABLE_26_MSK                                (((1U<<NPU_REG_ACT_TABLE_26_LEN)-1)<<NPU_REG_ACT_TABLE_26_POS)
#define NPU_REG_ACT_TABLE_26_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_26_LEN)-1)<<NPU_REG_ACT_TABLE_26_POS))
#define NPU_REG_ACT_TABLE_27                                    NPU_REG_ACT_TABLE_27
#define NPU_REG_ACT_TABLE_27_POS                                (24U)
#define NPU_REG_ACT_TABLE_27_LEN                                (8U)
#define NPU_REG_ACT_TABLE_27_MSK                                (((1U<<NPU_REG_ACT_TABLE_27_LEN)-1)<<NPU_REG_ACT_TABLE_27_POS)
#define NPU_REG_ACT_TABLE_27_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_27_LEN)-1)<<NPU_REG_ACT_TABLE_27_POS))

/* 0x128 : BLAI_ACT_TABLE_2B_28 */
#define NPU_BLAI_ACT_TABLE_2B_28_OFFSET                         (0x128)
#define NPU_REG_ACT_TABLE_28                                    NPU_REG_ACT_TABLE_28
#define NPU_REG_ACT_TABLE_28_POS                                (0U)
#define NPU_REG_ACT_TABLE_28_LEN                                (8U)
#define NPU_REG_ACT_TABLE_28_MSK                                (((1U<<NPU_REG_ACT_TABLE_28_LEN)-1)<<NPU_REG_ACT_TABLE_28_POS)
#define NPU_REG_ACT_TABLE_28_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_28_LEN)-1)<<NPU_REG_ACT_TABLE_28_POS))
#define NPU_REG_ACT_TABLE_29                                    NPU_REG_ACT_TABLE_29
#define NPU_REG_ACT_TABLE_29_POS                                (8U)
#define NPU_REG_ACT_TABLE_29_LEN                                (8U)
#define NPU_REG_ACT_TABLE_29_MSK                                (((1U<<NPU_REG_ACT_TABLE_29_LEN)-1)<<NPU_REG_ACT_TABLE_29_POS)
#define NPU_REG_ACT_TABLE_29_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_29_LEN)-1)<<NPU_REG_ACT_TABLE_29_POS))
#define NPU_REG_ACT_TABLE_2A                                    NPU_REG_ACT_TABLE_2A
#define NPU_REG_ACT_TABLE_2A_POS                                (16U)
#define NPU_REG_ACT_TABLE_2A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2A_MSK                                (((1U<<NPU_REG_ACT_TABLE_2A_LEN)-1)<<NPU_REG_ACT_TABLE_2A_POS)
#define NPU_REG_ACT_TABLE_2A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2A_LEN)-1)<<NPU_REG_ACT_TABLE_2A_POS))
#define NPU_REG_ACT_TABLE_2B                                    NPU_REG_ACT_TABLE_2B
#define NPU_REG_ACT_TABLE_2B_POS                                (24U)
#define NPU_REG_ACT_TABLE_2B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2B_MSK                                (((1U<<NPU_REG_ACT_TABLE_2B_LEN)-1)<<NPU_REG_ACT_TABLE_2B_POS)
#define NPU_REG_ACT_TABLE_2B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2B_LEN)-1)<<NPU_REG_ACT_TABLE_2B_POS))

/* 0x12C : BLAI_ACT_TABLE_2F_2C */
#define NPU_BLAI_ACT_TABLE_2F_2C_OFFSET                         (0x12C)
#define NPU_REG_ACT_TABLE_2C                                    NPU_REG_ACT_TABLE_2C
#define NPU_REG_ACT_TABLE_2C_POS                                (0U)
#define NPU_REG_ACT_TABLE_2C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2C_MSK                                (((1U<<NPU_REG_ACT_TABLE_2C_LEN)-1)<<NPU_REG_ACT_TABLE_2C_POS)
#define NPU_REG_ACT_TABLE_2C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2C_LEN)-1)<<NPU_REG_ACT_TABLE_2C_POS))
#define NPU_REG_ACT_TABLE_2D                                    NPU_REG_ACT_TABLE_2D
#define NPU_REG_ACT_TABLE_2D_POS                                (8U)
#define NPU_REG_ACT_TABLE_2D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2D_MSK                                (((1U<<NPU_REG_ACT_TABLE_2D_LEN)-1)<<NPU_REG_ACT_TABLE_2D_POS)
#define NPU_REG_ACT_TABLE_2D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2D_LEN)-1)<<NPU_REG_ACT_TABLE_2D_POS))
#define NPU_REG_ACT_TABLE_2E                                    NPU_REG_ACT_TABLE_2E
#define NPU_REG_ACT_TABLE_2E_POS                                (16U)
#define NPU_REG_ACT_TABLE_2E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2E_MSK                                (((1U<<NPU_REG_ACT_TABLE_2E_LEN)-1)<<NPU_REG_ACT_TABLE_2E_POS)
#define NPU_REG_ACT_TABLE_2E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2E_LEN)-1)<<NPU_REG_ACT_TABLE_2E_POS))
#define NPU_REG_ACT_TABLE_2F                                    NPU_REG_ACT_TABLE_2F
#define NPU_REG_ACT_TABLE_2F_POS                                (24U)
#define NPU_REG_ACT_TABLE_2F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_2F_MSK                                (((1U<<NPU_REG_ACT_TABLE_2F_LEN)-1)<<NPU_REG_ACT_TABLE_2F_POS)
#define NPU_REG_ACT_TABLE_2F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_2F_LEN)-1)<<NPU_REG_ACT_TABLE_2F_POS))

/* 0x130 : BLAI_ACT_TABLE_33_30 */
#define NPU_BLAI_ACT_TABLE_33_30_OFFSET                         (0x130)
#define NPU_REG_ACT_TABLE_30                                    NPU_REG_ACT_TABLE_30
#define NPU_REG_ACT_TABLE_30_POS                                (0U)
#define NPU_REG_ACT_TABLE_30_LEN                                (8U)
#define NPU_REG_ACT_TABLE_30_MSK                                (((1U<<NPU_REG_ACT_TABLE_30_LEN)-1)<<NPU_REG_ACT_TABLE_30_POS)
#define NPU_REG_ACT_TABLE_30_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_30_LEN)-1)<<NPU_REG_ACT_TABLE_30_POS))
#define NPU_REG_ACT_TABLE_31                                    NPU_REG_ACT_TABLE_31
#define NPU_REG_ACT_TABLE_31_POS                                (8U)
#define NPU_REG_ACT_TABLE_31_LEN                                (8U)
#define NPU_REG_ACT_TABLE_31_MSK                                (((1U<<NPU_REG_ACT_TABLE_31_LEN)-1)<<NPU_REG_ACT_TABLE_31_POS)
#define NPU_REG_ACT_TABLE_31_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_31_LEN)-1)<<NPU_REG_ACT_TABLE_31_POS))
#define NPU_REG_ACT_TABLE_32                                    NPU_REG_ACT_TABLE_32
#define NPU_REG_ACT_TABLE_32_POS                                (16U)
#define NPU_REG_ACT_TABLE_32_LEN                                (8U)
#define NPU_REG_ACT_TABLE_32_MSK                                (((1U<<NPU_REG_ACT_TABLE_32_LEN)-1)<<NPU_REG_ACT_TABLE_32_POS)
#define NPU_REG_ACT_TABLE_32_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_32_LEN)-1)<<NPU_REG_ACT_TABLE_32_POS))
#define NPU_REG_ACT_TABLE_33                                    NPU_REG_ACT_TABLE_33
#define NPU_REG_ACT_TABLE_33_POS                                (24U)
#define NPU_REG_ACT_TABLE_33_LEN                                (8U)
#define NPU_REG_ACT_TABLE_33_MSK                                (((1U<<NPU_REG_ACT_TABLE_33_LEN)-1)<<NPU_REG_ACT_TABLE_33_POS)
#define NPU_REG_ACT_TABLE_33_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_33_LEN)-1)<<NPU_REG_ACT_TABLE_33_POS))

/* 0x134 : BLAI_ACT_TABLE_37_34 */
#define NPU_BLAI_ACT_TABLE_37_34_OFFSET                         (0x134)
#define NPU_REG_ACT_TABLE_34                                    NPU_REG_ACT_TABLE_34
#define NPU_REG_ACT_TABLE_34_POS                                (0U)
#define NPU_REG_ACT_TABLE_34_LEN                                (8U)
#define NPU_REG_ACT_TABLE_34_MSK                                (((1U<<NPU_REG_ACT_TABLE_34_LEN)-1)<<NPU_REG_ACT_TABLE_34_POS)
#define NPU_REG_ACT_TABLE_34_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_34_LEN)-1)<<NPU_REG_ACT_TABLE_34_POS))
#define NPU_REG_ACT_TABLE_35                                    NPU_REG_ACT_TABLE_35
#define NPU_REG_ACT_TABLE_35_POS                                (8U)
#define NPU_REG_ACT_TABLE_35_LEN                                (8U)
#define NPU_REG_ACT_TABLE_35_MSK                                (((1U<<NPU_REG_ACT_TABLE_35_LEN)-1)<<NPU_REG_ACT_TABLE_35_POS)
#define NPU_REG_ACT_TABLE_35_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_35_LEN)-1)<<NPU_REG_ACT_TABLE_35_POS))
#define NPU_REG_ACT_TABLE_36                                    NPU_REG_ACT_TABLE_36
#define NPU_REG_ACT_TABLE_36_POS                                (16U)
#define NPU_REG_ACT_TABLE_36_LEN                                (8U)
#define NPU_REG_ACT_TABLE_36_MSK                                (((1U<<NPU_REG_ACT_TABLE_36_LEN)-1)<<NPU_REG_ACT_TABLE_36_POS)
#define NPU_REG_ACT_TABLE_36_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_36_LEN)-1)<<NPU_REG_ACT_TABLE_36_POS))
#define NPU_REG_ACT_TABLE_37                                    NPU_REG_ACT_TABLE_37
#define NPU_REG_ACT_TABLE_37_POS                                (24U)
#define NPU_REG_ACT_TABLE_37_LEN                                (8U)
#define NPU_REG_ACT_TABLE_37_MSK                                (((1U<<NPU_REG_ACT_TABLE_37_LEN)-1)<<NPU_REG_ACT_TABLE_37_POS)
#define NPU_REG_ACT_TABLE_37_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_37_LEN)-1)<<NPU_REG_ACT_TABLE_37_POS))

/* 0x138 : BLAI_ACT_TABLE_3B_38 */
#define NPU_BLAI_ACT_TABLE_3B_38_OFFSET                         (0x138)
#define NPU_REG_ACT_TABLE_38                                    NPU_REG_ACT_TABLE_38
#define NPU_REG_ACT_TABLE_38_POS                                (0U)
#define NPU_REG_ACT_TABLE_38_LEN                                (8U)
#define NPU_REG_ACT_TABLE_38_MSK                                (((1U<<NPU_REG_ACT_TABLE_38_LEN)-1)<<NPU_REG_ACT_TABLE_38_POS)
#define NPU_REG_ACT_TABLE_38_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_38_LEN)-1)<<NPU_REG_ACT_TABLE_38_POS))
#define NPU_REG_ACT_TABLE_39                                    NPU_REG_ACT_TABLE_39
#define NPU_REG_ACT_TABLE_39_POS                                (8U)
#define NPU_REG_ACT_TABLE_39_LEN                                (8U)
#define NPU_REG_ACT_TABLE_39_MSK                                (((1U<<NPU_REG_ACT_TABLE_39_LEN)-1)<<NPU_REG_ACT_TABLE_39_POS)
#define NPU_REG_ACT_TABLE_39_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_39_LEN)-1)<<NPU_REG_ACT_TABLE_39_POS))
#define NPU_REG_ACT_TABLE_3A                                    NPU_REG_ACT_TABLE_3A
#define NPU_REG_ACT_TABLE_3A_POS                                (16U)
#define NPU_REG_ACT_TABLE_3A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3A_MSK                                (((1U<<NPU_REG_ACT_TABLE_3A_LEN)-1)<<NPU_REG_ACT_TABLE_3A_POS)
#define NPU_REG_ACT_TABLE_3A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3A_LEN)-1)<<NPU_REG_ACT_TABLE_3A_POS))
#define NPU_REG_ACT_TABLE_3B                                    NPU_REG_ACT_TABLE_3B
#define NPU_REG_ACT_TABLE_3B_POS                                (24U)
#define NPU_REG_ACT_TABLE_3B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3B_MSK                                (((1U<<NPU_REG_ACT_TABLE_3B_LEN)-1)<<NPU_REG_ACT_TABLE_3B_POS)
#define NPU_REG_ACT_TABLE_3B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3B_LEN)-1)<<NPU_REG_ACT_TABLE_3B_POS))

/* 0x13C : BLAI_ACT_TABLE_3F_3C */
#define NPU_BLAI_ACT_TABLE_3F_3C_OFFSET                         (0x13C)
#define NPU_REG_ACT_TABLE_3C                                    NPU_REG_ACT_TABLE_3C
#define NPU_REG_ACT_TABLE_3C_POS                                (0U)
#define NPU_REG_ACT_TABLE_3C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3C_MSK                                (((1U<<NPU_REG_ACT_TABLE_3C_LEN)-1)<<NPU_REG_ACT_TABLE_3C_POS)
#define NPU_REG_ACT_TABLE_3C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3C_LEN)-1)<<NPU_REG_ACT_TABLE_3C_POS))
#define NPU_REG_ACT_TABLE_3D                                    NPU_REG_ACT_TABLE_3D
#define NPU_REG_ACT_TABLE_3D_POS                                (8U)
#define NPU_REG_ACT_TABLE_3D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3D_MSK                                (((1U<<NPU_REG_ACT_TABLE_3D_LEN)-1)<<NPU_REG_ACT_TABLE_3D_POS)
#define NPU_REG_ACT_TABLE_3D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3D_LEN)-1)<<NPU_REG_ACT_TABLE_3D_POS))
#define NPU_REG_ACT_TABLE_3E                                    NPU_REG_ACT_TABLE_3E
#define NPU_REG_ACT_TABLE_3E_POS                                (16U)
#define NPU_REG_ACT_TABLE_3E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3E_MSK                                (((1U<<NPU_REG_ACT_TABLE_3E_LEN)-1)<<NPU_REG_ACT_TABLE_3E_POS)
#define NPU_REG_ACT_TABLE_3E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3E_LEN)-1)<<NPU_REG_ACT_TABLE_3E_POS))
#define NPU_REG_ACT_TABLE_3F                                    NPU_REG_ACT_TABLE_3F
#define NPU_REG_ACT_TABLE_3F_POS                                (24U)
#define NPU_REG_ACT_TABLE_3F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_3F_MSK                                (((1U<<NPU_REG_ACT_TABLE_3F_LEN)-1)<<NPU_REG_ACT_TABLE_3F_POS)
#define NPU_REG_ACT_TABLE_3F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_3F_LEN)-1)<<NPU_REG_ACT_TABLE_3F_POS))

/* 0x140 : BLAI_ACT_TABLE_43_40 */
#define NPU_BLAI_ACT_TABLE_43_40_OFFSET                         (0x140)
#define NPU_REG_ACT_TABLE_40                                    NPU_REG_ACT_TABLE_40
#define NPU_REG_ACT_TABLE_40_POS                                (0U)
#define NPU_REG_ACT_TABLE_40_LEN                                (8U)
#define NPU_REG_ACT_TABLE_40_MSK                                (((1U<<NPU_REG_ACT_TABLE_40_LEN)-1)<<NPU_REG_ACT_TABLE_40_POS)
#define NPU_REG_ACT_TABLE_40_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_40_LEN)-1)<<NPU_REG_ACT_TABLE_40_POS))
#define NPU_REG_ACT_TABLE_41                                    NPU_REG_ACT_TABLE_41
#define NPU_REG_ACT_TABLE_41_POS                                (8U)
#define NPU_REG_ACT_TABLE_41_LEN                                (8U)
#define NPU_REG_ACT_TABLE_41_MSK                                (((1U<<NPU_REG_ACT_TABLE_41_LEN)-1)<<NPU_REG_ACT_TABLE_41_POS)
#define NPU_REG_ACT_TABLE_41_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_41_LEN)-1)<<NPU_REG_ACT_TABLE_41_POS))
#define NPU_REG_ACT_TABLE_42                                    NPU_REG_ACT_TABLE_42
#define NPU_REG_ACT_TABLE_42_POS                                (16U)
#define NPU_REG_ACT_TABLE_42_LEN                                (8U)
#define NPU_REG_ACT_TABLE_42_MSK                                (((1U<<NPU_REG_ACT_TABLE_42_LEN)-1)<<NPU_REG_ACT_TABLE_42_POS)
#define NPU_REG_ACT_TABLE_42_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_42_LEN)-1)<<NPU_REG_ACT_TABLE_42_POS))
#define NPU_REG_ACT_TABLE_43                                    NPU_REG_ACT_TABLE_43
#define NPU_REG_ACT_TABLE_43_POS                                (24U)
#define NPU_REG_ACT_TABLE_43_LEN                                (8U)
#define NPU_REG_ACT_TABLE_43_MSK                                (((1U<<NPU_REG_ACT_TABLE_43_LEN)-1)<<NPU_REG_ACT_TABLE_43_POS)
#define NPU_REG_ACT_TABLE_43_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_43_LEN)-1)<<NPU_REG_ACT_TABLE_43_POS))

/* 0x144 : BLAI_ACT_TABLE_47_44 */
#define NPU_BLAI_ACT_TABLE_47_44_OFFSET                         (0x144)
#define NPU_REG_ACT_TABLE_44                                    NPU_REG_ACT_TABLE_44
#define NPU_REG_ACT_TABLE_44_POS                                (0U)
#define NPU_REG_ACT_TABLE_44_LEN                                (8U)
#define NPU_REG_ACT_TABLE_44_MSK                                (((1U<<NPU_REG_ACT_TABLE_44_LEN)-1)<<NPU_REG_ACT_TABLE_44_POS)
#define NPU_REG_ACT_TABLE_44_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_44_LEN)-1)<<NPU_REG_ACT_TABLE_44_POS))
#define NPU_REG_ACT_TABLE_45                                    NPU_REG_ACT_TABLE_45
#define NPU_REG_ACT_TABLE_45_POS                                (8U)
#define NPU_REG_ACT_TABLE_45_LEN                                (8U)
#define NPU_REG_ACT_TABLE_45_MSK                                (((1U<<NPU_REG_ACT_TABLE_45_LEN)-1)<<NPU_REG_ACT_TABLE_45_POS)
#define NPU_REG_ACT_TABLE_45_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_45_LEN)-1)<<NPU_REG_ACT_TABLE_45_POS))
#define NPU_REG_ACT_TABLE_46                                    NPU_REG_ACT_TABLE_46
#define NPU_REG_ACT_TABLE_46_POS                                (16U)
#define NPU_REG_ACT_TABLE_46_LEN                                (8U)
#define NPU_REG_ACT_TABLE_46_MSK                                (((1U<<NPU_REG_ACT_TABLE_46_LEN)-1)<<NPU_REG_ACT_TABLE_46_POS)
#define NPU_REG_ACT_TABLE_46_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_46_LEN)-1)<<NPU_REG_ACT_TABLE_46_POS))
#define NPU_REG_ACT_TABLE_47                                    NPU_REG_ACT_TABLE_47
#define NPU_REG_ACT_TABLE_47_POS                                (24U)
#define NPU_REG_ACT_TABLE_47_LEN                                (8U)
#define NPU_REG_ACT_TABLE_47_MSK                                (((1U<<NPU_REG_ACT_TABLE_47_LEN)-1)<<NPU_REG_ACT_TABLE_47_POS)
#define NPU_REG_ACT_TABLE_47_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_47_LEN)-1)<<NPU_REG_ACT_TABLE_47_POS))

/* 0x148 : BLAI_ACT_TABLE_4B_48 */
#define NPU_BLAI_ACT_TABLE_4B_48_OFFSET                         (0x148)
#define NPU_REG_ACT_TABLE_48                                    NPU_REG_ACT_TABLE_48
#define NPU_REG_ACT_TABLE_48_POS                                (0U)
#define NPU_REG_ACT_TABLE_48_LEN                                (8U)
#define NPU_REG_ACT_TABLE_48_MSK                                (((1U<<NPU_REG_ACT_TABLE_48_LEN)-1)<<NPU_REG_ACT_TABLE_48_POS)
#define NPU_REG_ACT_TABLE_48_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_48_LEN)-1)<<NPU_REG_ACT_TABLE_48_POS))
#define NPU_REG_ACT_TABLE_49                                    NPU_REG_ACT_TABLE_49
#define NPU_REG_ACT_TABLE_49_POS                                (8U)
#define NPU_REG_ACT_TABLE_49_LEN                                (8U)
#define NPU_REG_ACT_TABLE_49_MSK                                (((1U<<NPU_REG_ACT_TABLE_49_LEN)-1)<<NPU_REG_ACT_TABLE_49_POS)
#define NPU_REG_ACT_TABLE_49_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_49_LEN)-1)<<NPU_REG_ACT_TABLE_49_POS))
#define NPU_REG_ACT_TABLE_4A                                    NPU_REG_ACT_TABLE_4A
#define NPU_REG_ACT_TABLE_4A_POS                                (16U)
#define NPU_REG_ACT_TABLE_4A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4A_MSK                                (((1U<<NPU_REG_ACT_TABLE_4A_LEN)-1)<<NPU_REG_ACT_TABLE_4A_POS)
#define NPU_REG_ACT_TABLE_4A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4A_LEN)-1)<<NPU_REG_ACT_TABLE_4A_POS))
#define NPU_REG_ACT_TABLE_4B                                    NPU_REG_ACT_TABLE_4B
#define NPU_REG_ACT_TABLE_4B_POS                                (24U)
#define NPU_REG_ACT_TABLE_4B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4B_MSK                                (((1U<<NPU_REG_ACT_TABLE_4B_LEN)-1)<<NPU_REG_ACT_TABLE_4B_POS)
#define NPU_REG_ACT_TABLE_4B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4B_LEN)-1)<<NPU_REG_ACT_TABLE_4B_POS))

/* 0x14C : BLAI_ACT_TABLE_4F_4C */
#define NPU_BLAI_ACT_TABLE_4F_4C_OFFSET                         (0x14C)
#define NPU_REG_ACT_TABLE_4C                                    NPU_REG_ACT_TABLE_4C
#define NPU_REG_ACT_TABLE_4C_POS                                (0U)
#define NPU_REG_ACT_TABLE_4C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4C_MSK                                (((1U<<NPU_REG_ACT_TABLE_4C_LEN)-1)<<NPU_REG_ACT_TABLE_4C_POS)
#define NPU_REG_ACT_TABLE_4C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4C_LEN)-1)<<NPU_REG_ACT_TABLE_4C_POS))
#define NPU_REG_ACT_TABLE_4D                                    NPU_REG_ACT_TABLE_4D
#define NPU_REG_ACT_TABLE_4D_POS                                (8U)
#define NPU_REG_ACT_TABLE_4D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4D_MSK                                (((1U<<NPU_REG_ACT_TABLE_4D_LEN)-1)<<NPU_REG_ACT_TABLE_4D_POS)
#define NPU_REG_ACT_TABLE_4D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4D_LEN)-1)<<NPU_REG_ACT_TABLE_4D_POS))
#define NPU_REG_ACT_TABLE_4E                                    NPU_REG_ACT_TABLE_4E
#define NPU_REG_ACT_TABLE_4E_POS                                (16U)
#define NPU_REG_ACT_TABLE_4E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4E_MSK                                (((1U<<NPU_REG_ACT_TABLE_4E_LEN)-1)<<NPU_REG_ACT_TABLE_4E_POS)
#define NPU_REG_ACT_TABLE_4E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4E_LEN)-1)<<NPU_REG_ACT_TABLE_4E_POS))
#define NPU_REG_ACT_TABLE_4F                                    NPU_REG_ACT_TABLE_4F
#define NPU_REG_ACT_TABLE_4F_POS                                (24U)
#define NPU_REG_ACT_TABLE_4F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_4F_MSK                                (((1U<<NPU_REG_ACT_TABLE_4F_LEN)-1)<<NPU_REG_ACT_TABLE_4F_POS)
#define NPU_REG_ACT_TABLE_4F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_4F_LEN)-1)<<NPU_REG_ACT_TABLE_4F_POS))

/* 0x150 : BLAI_ACT_TABLE_53_50 */
#define NPU_BLAI_ACT_TABLE_53_50_OFFSET                         (0x150)
#define NPU_REG_ACT_TABLE_50                                    NPU_REG_ACT_TABLE_50
#define NPU_REG_ACT_TABLE_50_POS                                (0U)
#define NPU_REG_ACT_TABLE_50_LEN                                (8U)
#define NPU_REG_ACT_TABLE_50_MSK                                (((1U<<NPU_REG_ACT_TABLE_50_LEN)-1)<<NPU_REG_ACT_TABLE_50_POS)
#define NPU_REG_ACT_TABLE_50_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_50_LEN)-1)<<NPU_REG_ACT_TABLE_50_POS))
#define NPU_REG_ACT_TABLE_51                                    NPU_REG_ACT_TABLE_51
#define NPU_REG_ACT_TABLE_51_POS                                (8U)
#define NPU_REG_ACT_TABLE_51_LEN                                (8U)
#define NPU_REG_ACT_TABLE_51_MSK                                (((1U<<NPU_REG_ACT_TABLE_51_LEN)-1)<<NPU_REG_ACT_TABLE_51_POS)
#define NPU_REG_ACT_TABLE_51_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_51_LEN)-1)<<NPU_REG_ACT_TABLE_51_POS))
#define NPU_REG_ACT_TABLE_52                                    NPU_REG_ACT_TABLE_52
#define NPU_REG_ACT_TABLE_52_POS                                (16U)
#define NPU_REG_ACT_TABLE_52_LEN                                (8U)
#define NPU_REG_ACT_TABLE_52_MSK                                (((1U<<NPU_REG_ACT_TABLE_52_LEN)-1)<<NPU_REG_ACT_TABLE_52_POS)
#define NPU_REG_ACT_TABLE_52_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_52_LEN)-1)<<NPU_REG_ACT_TABLE_52_POS))
#define NPU_REG_ACT_TABLE_53                                    NPU_REG_ACT_TABLE_53
#define NPU_REG_ACT_TABLE_53_POS                                (24U)
#define NPU_REG_ACT_TABLE_53_LEN                                (8U)
#define NPU_REG_ACT_TABLE_53_MSK                                (((1U<<NPU_REG_ACT_TABLE_53_LEN)-1)<<NPU_REG_ACT_TABLE_53_POS)
#define NPU_REG_ACT_TABLE_53_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_53_LEN)-1)<<NPU_REG_ACT_TABLE_53_POS))

/* 0x154 : BLAI_ACT_TABLE_57_54 */
#define NPU_BLAI_ACT_TABLE_57_54_OFFSET                         (0x154)
#define NPU_REG_ACT_TABLE_54                                    NPU_REG_ACT_TABLE_54
#define NPU_REG_ACT_TABLE_54_POS                                (0U)
#define NPU_REG_ACT_TABLE_54_LEN                                (8U)
#define NPU_REG_ACT_TABLE_54_MSK                                (((1U<<NPU_REG_ACT_TABLE_54_LEN)-1)<<NPU_REG_ACT_TABLE_54_POS)
#define NPU_REG_ACT_TABLE_54_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_54_LEN)-1)<<NPU_REG_ACT_TABLE_54_POS))
#define NPU_REG_ACT_TABLE_55                                    NPU_REG_ACT_TABLE_55
#define NPU_REG_ACT_TABLE_55_POS                                (8U)
#define NPU_REG_ACT_TABLE_55_LEN                                (8U)
#define NPU_REG_ACT_TABLE_55_MSK                                (((1U<<NPU_REG_ACT_TABLE_55_LEN)-1)<<NPU_REG_ACT_TABLE_55_POS)
#define NPU_REG_ACT_TABLE_55_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_55_LEN)-1)<<NPU_REG_ACT_TABLE_55_POS))
#define NPU_REG_ACT_TABLE_56                                    NPU_REG_ACT_TABLE_56
#define NPU_REG_ACT_TABLE_56_POS                                (16U)
#define NPU_REG_ACT_TABLE_56_LEN                                (8U)
#define NPU_REG_ACT_TABLE_56_MSK                                (((1U<<NPU_REG_ACT_TABLE_56_LEN)-1)<<NPU_REG_ACT_TABLE_56_POS)
#define NPU_REG_ACT_TABLE_56_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_56_LEN)-1)<<NPU_REG_ACT_TABLE_56_POS))
#define NPU_REG_ACT_TABLE_57                                    NPU_REG_ACT_TABLE_57
#define NPU_REG_ACT_TABLE_57_POS                                (24U)
#define NPU_REG_ACT_TABLE_57_LEN                                (8U)
#define NPU_REG_ACT_TABLE_57_MSK                                (((1U<<NPU_REG_ACT_TABLE_57_LEN)-1)<<NPU_REG_ACT_TABLE_57_POS)
#define NPU_REG_ACT_TABLE_57_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_57_LEN)-1)<<NPU_REG_ACT_TABLE_57_POS))

/* 0x158 : BLAI_ACT_TABLE_5B_58 */
#define NPU_BLAI_ACT_TABLE_5B_58_OFFSET                         (0x158)
#define NPU_REG_ACT_TABLE_58                                    NPU_REG_ACT_TABLE_58
#define NPU_REG_ACT_TABLE_58_POS                                (0U)
#define NPU_REG_ACT_TABLE_58_LEN                                (8U)
#define NPU_REG_ACT_TABLE_58_MSK                                (((1U<<NPU_REG_ACT_TABLE_58_LEN)-1)<<NPU_REG_ACT_TABLE_58_POS)
#define NPU_REG_ACT_TABLE_58_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_58_LEN)-1)<<NPU_REG_ACT_TABLE_58_POS))
#define NPU_REG_ACT_TABLE_59                                    NPU_REG_ACT_TABLE_59
#define NPU_REG_ACT_TABLE_59_POS                                (8U)
#define NPU_REG_ACT_TABLE_59_LEN                                (8U)
#define NPU_REG_ACT_TABLE_59_MSK                                (((1U<<NPU_REG_ACT_TABLE_59_LEN)-1)<<NPU_REG_ACT_TABLE_59_POS)
#define NPU_REG_ACT_TABLE_59_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_59_LEN)-1)<<NPU_REG_ACT_TABLE_59_POS))
#define NPU_REG_ACT_TABLE_5A                                    NPU_REG_ACT_TABLE_5A
#define NPU_REG_ACT_TABLE_5A_POS                                (16U)
#define NPU_REG_ACT_TABLE_5A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5A_MSK                                (((1U<<NPU_REG_ACT_TABLE_5A_LEN)-1)<<NPU_REG_ACT_TABLE_5A_POS)
#define NPU_REG_ACT_TABLE_5A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5A_LEN)-1)<<NPU_REG_ACT_TABLE_5A_POS))
#define NPU_REG_ACT_TABLE_5B                                    NPU_REG_ACT_TABLE_5B
#define NPU_REG_ACT_TABLE_5B_POS                                (24U)
#define NPU_REG_ACT_TABLE_5B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5B_MSK                                (((1U<<NPU_REG_ACT_TABLE_5B_LEN)-1)<<NPU_REG_ACT_TABLE_5B_POS)
#define NPU_REG_ACT_TABLE_5B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5B_LEN)-1)<<NPU_REG_ACT_TABLE_5B_POS))

/* 0x15C : BLAI_ACT_TABLE_5F_5C */
#define NPU_BLAI_ACT_TABLE_5F_5C_OFFSET                         (0x15C)
#define NPU_REG_ACT_TABLE_5C                                    NPU_REG_ACT_TABLE_5C
#define NPU_REG_ACT_TABLE_5C_POS                                (0U)
#define NPU_REG_ACT_TABLE_5C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5C_MSK                                (((1U<<NPU_REG_ACT_TABLE_5C_LEN)-1)<<NPU_REG_ACT_TABLE_5C_POS)
#define NPU_REG_ACT_TABLE_5C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5C_LEN)-1)<<NPU_REG_ACT_TABLE_5C_POS))
#define NPU_REG_ACT_TABLE_5D                                    NPU_REG_ACT_TABLE_5D
#define NPU_REG_ACT_TABLE_5D_POS                                (8U)
#define NPU_REG_ACT_TABLE_5D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5D_MSK                                (((1U<<NPU_REG_ACT_TABLE_5D_LEN)-1)<<NPU_REG_ACT_TABLE_5D_POS)
#define NPU_REG_ACT_TABLE_5D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5D_LEN)-1)<<NPU_REG_ACT_TABLE_5D_POS))
#define NPU_REG_ACT_TABLE_5E                                    NPU_REG_ACT_TABLE_5E
#define NPU_REG_ACT_TABLE_5E_POS                                (16U)
#define NPU_REG_ACT_TABLE_5E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5E_MSK                                (((1U<<NPU_REG_ACT_TABLE_5E_LEN)-1)<<NPU_REG_ACT_TABLE_5E_POS)
#define NPU_REG_ACT_TABLE_5E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5E_LEN)-1)<<NPU_REG_ACT_TABLE_5E_POS))
#define NPU_REG_ACT_TABLE_5F                                    NPU_REG_ACT_TABLE_5F
#define NPU_REG_ACT_TABLE_5F_POS                                (24U)
#define NPU_REG_ACT_TABLE_5F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_5F_MSK                                (((1U<<NPU_REG_ACT_TABLE_5F_LEN)-1)<<NPU_REG_ACT_TABLE_5F_POS)
#define NPU_REG_ACT_TABLE_5F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_5F_LEN)-1)<<NPU_REG_ACT_TABLE_5F_POS))

/* 0x160 : BLAI_ACT_TABLE_63_60 */
#define NPU_BLAI_ACT_TABLE_63_60_OFFSET                         (0x160)
#define NPU_REG_ACT_TABLE_60                                    NPU_REG_ACT_TABLE_60
#define NPU_REG_ACT_TABLE_60_POS                                (0U)
#define NPU_REG_ACT_TABLE_60_LEN                                (8U)
#define NPU_REG_ACT_TABLE_60_MSK                                (((1U<<NPU_REG_ACT_TABLE_60_LEN)-1)<<NPU_REG_ACT_TABLE_60_POS)
#define NPU_REG_ACT_TABLE_60_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_60_LEN)-1)<<NPU_REG_ACT_TABLE_60_POS))
#define NPU_REG_ACT_TABLE_61                                    NPU_REG_ACT_TABLE_61
#define NPU_REG_ACT_TABLE_61_POS                                (8U)
#define NPU_REG_ACT_TABLE_61_LEN                                (8U)
#define NPU_REG_ACT_TABLE_61_MSK                                (((1U<<NPU_REG_ACT_TABLE_61_LEN)-1)<<NPU_REG_ACT_TABLE_61_POS)
#define NPU_REG_ACT_TABLE_61_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_61_LEN)-1)<<NPU_REG_ACT_TABLE_61_POS))
#define NPU_REG_ACT_TABLE_62                                    NPU_REG_ACT_TABLE_62
#define NPU_REG_ACT_TABLE_62_POS                                (16U)
#define NPU_REG_ACT_TABLE_62_LEN                                (8U)
#define NPU_REG_ACT_TABLE_62_MSK                                (((1U<<NPU_REG_ACT_TABLE_62_LEN)-1)<<NPU_REG_ACT_TABLE_62_POS)
#define NPU_REG_ACT_TABLE_62_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_62_LEN)-1)<<NPU_REG_ACT_TABLE_62_POS))
#define NPU_REG_ACT_TABLE_63                                    NPU_REG_ACT_TABLE_63
#define NPU_REG_ACT_TABLE_63_POS                                (24U)
#define NPU_REG_ACT_TABLE_63_LEN                                (8U)
#define NPU_REG_ACT_TABLE_63_MSK                                (((1U<<NPU_REG_ACT_TABLE_63_LEN)-1)<<NPU_REG_ACT_TABLE_63_POS)
#define NPU_REG_ACT_TABLE_63_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_63_LEN)-1)<<NPU_REG_ACT_TABLE_63_POS))

/* 0x164 : BLAI_ACT_TABLE_67_64 */
#define NPU_BLAI_ACT_TABLE_67_64_OFFSET                         (0x164)
#define NPU_REG_ACT_TABLE_64                                    NPU_REG_ACT_TABLE_64
#define NPU_REG_ACT_TABLE_64_POS                                (0U)
#define NPU_REG_ACT_TABLE_64_LEN                                (8U)
#define NPU_REG_ACT_TABLE_64_MSK                                (((1U<<NPU_REG_ACT_TABLE_64_LEN)-1)<<NPU_REG_ACT_TABLE_64_POS)
#define NPU_REG_ACT_TABLE_64_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_64_LEN)-1)<<NPU_REG_ACT_TABLE_64_POS))
#define NPU_REG_ACT_TABLE_65                                    NPU_REG_ACT_TABLE_65
#define NPU_REG_ACT_TABLE_65_POS                                (8U)
#define NPU_REG_ACT_TABLE_65_LEN                                (8U)
#define NPU_REG_ACT_TABLE_65_MSK                                (((1U<<NPU_REG_ACT_TABLE_65_LEN)-1)<<NPU_REG_ACT_TABLE_65_POS)
#define NPU_REG_ACT_TABLE_65_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_65_LEN)-1)<<NPU_REG_ACT_TABLE_65_POS))
#define NPU_REG_ACT_TABLE_66                                    NPU_REG_ACT_TABLE_66
#define NPU_REG_ACT_TABLE_66_POS                                (16U)
#define NPU_REG_ACT_TABLE_66_LEN                                (8U)
#define NPU_REG_ACT_TABLE_66_MSK                                (((1U<<NPU_REG_ACT_TABLE_66_LEN)-1)<<NPU_REG_ACT_TABLE_66_POS)
#define NPU_REG_ACT_TABLE_66_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_66_LEN)-1)<<NPU_REG_ACT_TABLE_66_POS))
#define NPU_REG_ACT_TABLE_67                                    NPU_REG_ACT_TABLE_67
#define NPU_REG_ACT_TABLE_67_POS                                (24U)
#define NPU_REG_ACT_TABLE_67_LEN                                (8U)
#define NPU_REG_ACT_TABLE_67_MSK                                (((1U<<NPU_REG_ACT_TABLE_67_LEN)-1)<<NPU_REG_ACT_TABLE_67_POS)
#define NPU_REG_ACT_TABLE_67_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_67_LEN)-1)<<NPU_REG_ACT_TABLE_67_POS))

/* 0x168 : BLAI_ACT_TABLE_6B_68 */
#define NPU_BLAI_ACT_TABLE_6B_68_OFFSET                         (0x168)
#define NPU_REG_ACT_TABLE_68                                    NPU_REG_ACT_TABLE_68
#define NPU_REG_ACT_TABLE_68_POS                                (0U)
#define NPU_REG_ACT_TABLE_68_LEN                                (8U)
#define NPU_REG_ACT_TABLE_68_MSK                                (((1U<<NPU_REG_ACT_TABLE_68_LEN)-1)<<NPU_REG_ACT_TABLE_68_POS)
#define NPU_REG_ACT_TABLE_68_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_68_LEN)-1)<<NPU_REG_ACT_TABLE_68_POS))
#define NPU_REG_ACT_TABLE_69                                    NPU_REG_ACT_TABLE_69
#define NPU_REG_ACT_TABLE_69_POS                                (8U)
#define NPU_REG_ACT_TABLE_69_LEN                                (8U)
#define NPU_REG_ACT_TABLE_69_MSK                                (((1U<<NPU_REG_ACT_TABLE_69_LEN)-1)<<NPU_REG_ACT_TABLE_69_POS)
#define NPU_REG_ACT_TABLE_69_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_69_LEN)-1)<<NPU_REG_ACT_TABLE_69_POS))
#define NPU_REG_ACT_TABLE_6A                                    NPU_REG_ACT_TABLE_6A
#define NPU_REG_ACT_TABLE_6A_POS                                (16U)
#define NPU_REG_ACT_TABLE_6A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6A_MSK                                (((1U<<NPU_REG_ACT_TABLE_6A_LEN)-1)<<NPU_REG_ACT_TABLE_6A_POS)
#define NPU_REG_ACT_TABLE_6A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6A_LEN)-1)<<NPU_REG_ACT_TABLE_6A_POS))
#define NPU_REG_ACT_TABLE_6B                                    NPU_REG_ACT_TABLE_6B
#define NPU_REG_ACT_TABLE_6B_POS                                (24U)
#define NPU_REG_ACT_TABLE_6B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6B_MSK                                (((1U<<NPU_REG_ACT_TABLE_6B_LEN)-1)<<NPU_REG_ACT_TABLE_6B_POS)
#define NPU_REG_ACT_TABLE_6B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6B_LEN)-1)<<NPU_REG_ACT_TABLE_6B_POS))

/* 0x16C : BLAI_ACT_TABLE_6F_6C */
#define NPU_BLAI_ACT_TABLE_6F_6C_OFFSET                         (0x16C)
#define NPU_REG_ACT_TABLE_6C                                    NPU_REG_ACT_TABLE_6C
#define NPU_REG_ACT_TABLE_6C_POS                                (0U)
#define NPU_REG_ACT_TABLE_6C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6C_MSK                                (((1U<<NPU_REG_ACT_TABLE_6C_LEN)-1)<<NPU_REG_ACT_TABLE_6C_POS)
#define NPU_REG_ACT_TABLE_6C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6C_LEN)-1)<<NPU_REG_ACT_TABLE_6C_POS))
#define NPU_REG_ACT_TABLE_6D                                    NPU_REG_ACT_TABLE_6D
#define NPU_REG_ACT_TABLE_6D_POS                                (8U)
#define NPU_REG_ACT_TABLE_6D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6D_MSK                                (((1U<<NPU_REG_ACT_TABLE_6D_LEN)-1)<<NPU_REG_ACT_TABLE_6D_POS)
#define NPU_REG_ACT_TABLE_6D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6D_LEN)-1)<<NPU_REG_ACT_TABLE_6D_POS))
#define NPU_REG_ACT_TABLE_6E                                    NPU_REG_ACT_TABLE_6E
#define NPU_REG_ACT_TABLE_6E_POS                                (16U)
#define NPU_REG_ACT_TABLE_6E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6E_MSK                                (((1U<<NPU_REG_ACT_TABLE_6E_LEN)-1)<<NPU_REG_ACT_TABLE_6E_POS)
#define NPU_REG_ACT_TABLE_6E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6E_LEN)-1)<<NPU_REG_ACT_TABLE_6E_POS))
#define NPU_REG_ACT_TABLE_6F                                    NPU_REG_ACT_TABLE_6F
#define NPU_REG_ACT_TABLE_6F_POS                                (24U)
#define NPU_REG_ACT_TABLE_6F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_6F_MSK                                (((1U<<NPU_REG_ACT_TABLE_6F_LEN)-1)<<NPU_REG_ACT_TABLE_6F_POS)
#define NPU_REG_ACT_TABLE_6F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_6F_LEN)-1)<<NPU_REG_ACT_TABLE_6F_POS))

/* 0x170 : BLAI_ACT_TABLE_73_70 */
#define NPU_BLAI_ACT_TABLE_73_70_OFFSET                         (0x170)
#define NPU_REG_ACT_TABLE_70                                    NPU_REG_ACT_TABLE_70
#define NPU_REG_ACT_TABLE_70_POS                                (0U)
#define NPU_REG_ACT_TABLE_70_LEN                                (8U)
#define NPU_REG_ACT_TABLE_70_MSK                                (((1U<<NPU_REG_ACT_TABLE_70_LEN)-1)<<NPU_REG_ACT_TABLE_70_POS)
#define NPU_REG_ACT_TABLE_70_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_70_LEN)-1)<<NPU_REG_ACT_TABLE_70_POS))
#define NPU_REG_ACT_TABLE_71                                    NPU_REG_ACT_TABLE_71
#define NPU_REG_ACT_TABLE_71_POS                                (8U)
#define NPU_REG_ACT_TABLE_71_LEN                                (8U)
#define NPU_REG_ACT_TABLE_71_MSK                                (((1U<<NPU_REG_ACT_TABLE_71_LEN)-1)<<NPU_REG_ACT_TABLE_71_POS)
#define NPU_REG_ACT_TABLE_71_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_71_LEN)-1)<<NPU_REG_ACT_TABLE_71_POS))
#define NPU_REG_ACT_TABLE_72                                    NPU_REG_ACT_TABLE_72
#define NPU_REG_ACT_TABLE_72_POS                                (16U)
#define NPU_REG_ACT_TABLE_72_LEN                                (8U)
#define NPU_REG_ACT_TABLE_72_MSK                                (((1U<<NPU_REG_ACT_TABLE_72_LEN)-1)<<NPU_REG_ACT_TABLE_72_POS)
#define NPU_REG_ACT_TABLE_72_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_72_LEN)-1)<<NPU_REG_ACT_TABLE_72_POS))
#define NPU_REG_ACT_TABLE_73                                    NPU_REG_ACT_TABLE_73
#define NPU_REG_ACT_TABLE_73_POS                                (24U)
#define NPU_REG_ACT_TABLE_73_LEN                                (8U)
#define NPU_REG_ACT_TABLE_73_MSK                                (((1U<<NPU_REG_ACT_TABLE_73_LEN)-1)<<NPU_REG_ACT_TABLE_73_POS)
#define NPU_REG_ACT_TABLE_73_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_73_LEN)-1)<<NPU_REG_ACT_TABLE_73_POS))

/* 0x174 : BLAI_ACT_TABLE_77_74 */
#define NPU_BLAI_ACT_TABLE_77_74_OFFSET                         (0x174)
#define NPU_REG_ACT_TABLE_74                                    NPU_REG_ACT_TABLE_74
#define NPU_REG_ACT_TABLE_74_POS                                (0U)
#define NPU_REG_ACT_TABLE_74_LEN                                (8U)
#define NPU_REG_ACT_TABLE_74_MSK                                (((1U<<NPU_REG_ACT_TABLE_74_LEN)-1)<<NPU_REG_ACT_TABLE_74_POS)
#define NPU_REG_ACT_TABLE_74_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_74_LEN)-1)<<NPU_REG_ACT_TABLE_74_POS))
#define NPU_REG_ACT_TABLE_75                                    NPU_REG_ACT_TABLE_75
#define NPU_REG_ACT_TABLE_75_POS                                (8U)
#define NPU_REG_ACT_TABLE_75_LEN                                (8U)
#define NPU_REG_ACT_TABLE_75_MSK                                (((1U<<NPU_REG_ACT_TABLE_75_LEN)-1)<<NPU_REG_ACT_TABLE_75_POS)
#define NPU_REG_ACT_TABLE_75_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_75_LEN)-1)<<NPU_REG_ACT_TABLE_75_POS))
#define NPU_REG_ACT_TABLE_76                                    NPU_REG_ACT_TABLE_76
#define NPU_REG_ACT_TABLE_76_POS                                (16U)
#define NPU_REG_ACT_TABLE_76_LEN                                (8U)
#define NPU_REG_ACT_TABLE_76_MSK                                (((1U<<NPU_REG_ACT_TABLE_76_LEN)-1)<<NPU_REG_ACT_TABLE_76_POS)
#define NPU_REG_ACT_TABLE_76_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_76_LEN)-1)<<NPU_REG_ACT_TABLE_76_POS))
#define NPU_REG_ACT_TABLE_77                                    NPU_REG_ACT_TABLE_77
#define NPU_REG_ACT_TABLE_77_POS                                (24U)
#define NPU_REG_ACT_TABLE_77_LEN                                (8U)
#define NPU_REG_ACT_TABLE_77_MSK                                (((1U<<NPU_REG_ACT_TABLE_77_LEN)-1)<<NPU_REG_ACT_TABLE_77_POS)
#define NPU_REG_ACT_TABLE_77_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_77_LEN)-1)<<NPU_REG_ACT_TABLE_77_POS))

/* 0x178 : BLAI_ACT_TABLE_7B_78 */
#define NPU_BLAI_ACT_TABLE_7B_78_OFFSET                         (0x178)
#define NPU_REG_ACT_TABLE_78                                    NPU_REG_ACT_TABLE_78
#define NPU_REG_ACT_TABLE_78_POS                                (0U)
#define NPU_REG_ACT_TABLE_78_LEN                                (8U)
#define NPU_REG_ACT_TABLE_78_MSK                                (((1U<<NPU_REG_ACT_TABLE_78_LEN)-1)<<NPU_REG_ACT_TABLE_78_POS)
#define NPU_REG_ACT_TABLE_78_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_78_LEN)-1)<<NPU_REG_ACT_TABLE_78_POS))
#define NPU_REG_ACT_TABLE_79                                    NPU_REG_ACT_TABLE_79
#define NPU_REG_ACT_TABLE_79_POS                                (8U)
#define NPU_REG_ACT_TABLE_79_LEN                                (8U)
#define NPU_REG_ACT_TABLE_79_MSK                                (((1U<<NPU_REG_ACT_TABLE_79_LEN)-1)<<NPU_REG_ACT_TABLE_79_POS)
#define NPU_REG_ACT_TABLE_79_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_79_LEN)-1)<<NPU_REG_ACT_TABLE_79_POS))
#define NPU_REG_ACT_TABLE_7A                                    NPU_REG_ACT_TABLE_7A
#define NPU_REG_ACT_TABLE_7A_POS                                (16U)
#define NPU_REG_ACT_TABLE_7A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7A_MSK                                (((1U<<NPU_REG_ACT_TABLE_7A_LEN)-1)<<NPU_REG_ACT_TABLE_7A_POS)
#define NPU_REG_ACT_TABLE_7A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7A_LEN)-1)<<NPU_REG_ACT_TABLE_7A_POS))
#define NPU_REG_ACT_TABLE_7B                                    NPU_REG_ACT_TABLE_7B
#define NPU_REG_ACT_TABLE_7B_POS                                (24U)
#define NPU_REG_ACT_TABLE_7B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7B_MSK                                (((1U<<NPU_REG_ACT_TABLE_7B_LEN)-1)<<NPU_REG_ACT_TABLE_7B_POS)
#define NPU_REG_ACT_TABLE_7B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7B_LEN)-1)<<NPU_REG_ACT_TABLE_7B_POS))

/* 0x17C : BLAI_ACT_TABLE_7F_7C */
#define NPU_BLAI_ACT_TABLE_7F_7C_OFFSET                         (0x17C)
#define NPU_REG_ACT_TABLE_7C                                    NPU_REG_ACT_TABLE_7C
#define NPU_REG_ACT_TABLE_7C_POS                                (0U)
#define NPU_REG_ACT_TABLE_7C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7C_MSK                                (((1U<<NPU_REG_ACT_TABLE_7C_LEN)-1)<<NPU_REG_ACT_TABLE_7C_POS)
#define NPU_REG_ACT_TABLE_7C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7C_LEN)-1)<<NPU_REG_ACT_TABLE_7C_POS))
#define NPU_REG_ACT_TABLE_7D                                    NPU_REG_ACT_TABLE_7D
#define NPU_REG_ACT_TABLE_7D_POS                                (8U)
#define NPU_REG_ACT_TABLE_7D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7D_MSK                                (((1U<<NPU_REG_ACT_TABLE_7D_LEN)-1)<<NPU_REG_ACT_TABLE_7D_POS)
#define NPU_REG_ACT_TABLE_7D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7D_LEN)-1)<<NPU_REG_ACT_TABLE_7D_POS))
#define NPU_REG_ACT_TABLE_7E                                    NPU_REG_ACT_TABLE_7E
#define NPU_REG_ACT_TABLE_7E_POS                                (16U)
#define NPU_REG_ACT_TABLE_7E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7E_MSK                                (((1U<<NPU_REG_ACT_TABLE_7E_LEN)-1)<<NPU_REG_ACT_TABLE_7E_POS)
#define NPU_REG_ACT_TABLE_7E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7E_LEN)-1)<<NPU_REG_ACT_TABLE_7E_POS))
#define NPU_REG_ACT_TABLE_7F                                    NPU_REG_ACT_TABLE_7F
#define NPU_REG_ACT_TABLE_7F_POS                                (24U)
#define NPU_REG_ACT_TABLE_7F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_7F_MSK                                (((1U<<NPU_REG_ACT_TABLE_7F_LEN)-1)<<NPU_REG_ACT_TABLE_7F_POS)
#define NPU_REG_ACT_TABLE_7F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_7F_LEN)-1)<<NPU_REG_ACT_TABLE_7F_POS))

/* 0x180 : BLAI_ACT_TABLE_83_80 */
#define NPU_BLAI_ACT_TABLE_83_80_OFFSET                         (0x180)
#define NPU_REG_ACT_TABLE_80                                    NPU_REG_ACT_TABLE_80
#define NPU_REG_ACT_TABLE_80_POS                                (0U)
#define NPU_REG_ACT_TABLE_80_LEN                                (8U)
#define NPU_REG_ACT_TABLE_80_MSK                                (((1U<<NPU_REG_ACT_TABLE_80_LEN)-1)<<NPU_REG_ACT_TABLE_80_POS)
#define NPU_REG_ACT_TABLE_80_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_80_LEN)-1)<<NPU_REG_ACT_TABLE_80_POS))
#define NPU_REG_ACT_TABLE_81                                    NPU_REG_ACT_TABLE_81
#define NPU_REG_ACT_TABLE_81_POS                                (8U)
#define NPU_REG_ACT_TABLE_81_LEN                                (8U)
#define NPU_REG_ACT_TABLE_81_MSK                                (((1U<<NPU_REG_ACT_TABLE_81_LEN)-1)<<NPU_REG_ACT_TABLE_81_POS)
#define NPU_REG_ACT_TABLE_81_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_81_LEN)-1)<<NPU_REG_ACT_TABLE_81_POS))
#define NPU_REG_ACT_TABLE_82                                    NPU_REG_ACT_TABLE_82
#define NPU_REG_ACT_TABLE_82_POS                                (16U)
#define NPU_REG_ACT_TABLE_82_LEN                                (8U)
#define NPU_REG_ACT_TABLE_82_MSK                                (((1U<<NPU_REG_ACT_TABLE_82_LEN)-1)<<NPU_REG_ACT_TABLE_82_POS)
#define NPU_REG_ACT_TABLE_82_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_82_LEN)-1)<<NPU_REG_ACT_TABLE_82_POS))
#define NPU_REG_ACT_TABLE_83                                    NPU_REG_ACT_TABLE_83
#define NPU_REG_ACT_TABLE_83_POS                                (24U)
#define NPU_REG_ACT_TABLE_83_LEN                                (8U)
#define NPU_REG_ACT_TABLE_83_MSK                                (((1U<<NPU_REG_ACT_TABLE_83_LEN)-1)<<NPU_REG_ACT_TABLE_83_POS)
#define NPU_REG_ACT_TABLE_83_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_83_LEN)-1)<<NPU_REG_ACT_TABLE_83_POS))

/* 0x184 : BLAI_ACT_TABLE_87_84 */
#define NPU_BLAI_ACT_TABLE_87_84_OFFSET                         (0x184)
#define NPU_REG_ACT_TABLE_84                                    NPU_REG_ACT_TABLE_84
#define NPU_REG_ACT_TABLE_84_POS                                (0U)
#define NPU_REG_ACT_TABLE_84_LEN                                (8U)
#define NPU_REG_ACT_TABLE_84_MSK                                (((1U<<NPU_REG_ACT_TABLE_84_LEN)-1)<<NPU_REG_ACT_TABLE_84_POS)
#define NPU_REG_ACT_TABLE_84_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_84_LEN)-1)<<NPU_REG_ACT_TABLE_84_POS))
#define NPU_REG_ACT_TABLE_85                                    NPU_REG_ACT_TABLE_85
#define NPU_REG_ACT_TABLE_85_POS                                (8U)
#define NPU_REG_ACT_TABLE_85_LEN                                (8U)
#define NPU_REG_ACT_TABLE_85_MSK                                (((1U<<NPU_REG_ACT_TABLE_85_LEN)-1)<<NPU_REG_ACT_TABLE_85_POS)
#define NPU_REG_ACT_TABLE_85_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_85_LEN)-1)<<NPU_REG_ACT_TABLE_85_POS))
#define NPU_REG_ACT_TABLE_86                                    NPU_REG_ACT_TABLE_86
#define NPU_REG_ACT_TABLE_86_POS                                (16U)
#define NPU_REG_ACT_TABLE_86_LEN                                (8U)
#define NPU_REG_ACT_TABLE_86_MSK                                (((1U<<NPU_REG_ACT_TABLE_86_LEN)-1)<<NPU_REG_ACT_TABLE_86_POS)
#define NPU_REG_ACT_TABLE_86_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_86_LEN)-1)<<NPU_REG_ACT_TABLE_86_POS))
#define NPU_REG_ACT_TABLE_87                                    NPU_REG_ACT_TABLE_87
#define NPU_REG_ACT_TABLE_87_POS                                (24U)
#define NPU_REG_ACT_TABLE_87_LEN                                (8U)
#define NPU_REG_ACT_TABLE_87_MSK                                (((1U<<NPU_REG_ACT_TABLE_87_LEN)-1)<<NPU_REG_ACT_TABLE_87_POS)
#define NPU_REG_ACT_TABLE_87_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_87_LEN)-1)<<NPU_REG_ACT_TABLE_87_POS))

/* 0x188 : BLAI_ACT_TABLE_8B_88 */
#define NPU_BLAI_ACT_TABLE_8B_88_OFFSET                         (0x188)
#define NPU_REG_ACT_TABLE_88                                    NPU_REG_ACT_TABLE_88
#define NPU_REG_ACT_TABLE_88_POS                                (0U)
#define NPU_REG_ACT_TABLE_88_LEN                                (8U)
#define NPU_REG_ACT_TABLE_88_MSK                                (((1U<<NPU_REG_ACT_TABLE_88_LEN)-1)<<NPU_REG_ACT_TABLE_88_POS)
#define NPU_REG_ACT_TABLE_88_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_88_LEN)-1)<<NPU_REG_ACT_TABLE_88_POS))
#define NPU_REG_ACT_TABLE_89                                    NPU_REG_ACT_TABLE_89
#define NPU_REG_ACT_TABLE_89_POS                                (8U)
#define NPU_REG_ACT_TABLE_89_LEN                                (8U)
#define NPU_REG_ACT_TABLE_89_MSK                                (((1U<<NPU_REG_ACT_TABLE_89_LEN)-1)<<NPU_REG_ACT_TABLE_89_POS)
#define NPU_REG_ACT_TABLE_89_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_89_LEN)-1)<<NPU_REG_ACT_TABLE_89_POS))
#define NPU_REG_ACT_TABLE_8A                                    NPU_REG_ACT_TABLE_8A
#define NPU_REG_ACT_TABLE_8A_POS                                (16U)
#define NPU_REG_ACT_TABLE_8A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8A_MSK                                (((1U<<NPU_REG_ACT_TABLE_8A_LEN)-1)<<NPU_REG_ACT_TABLE_8A_POS)
#define NPU_REG_ACT_TABLE_8A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8A_LEN)-1)<<NPU_REG_ACT_TABLE_8A_POS))
#define NPU_REG_ACT_TABLE_8B                                    NPU_REG_ACT_TABLE_8B
#define NPU_REG_ACT_TABLE_8B_POS                                (24U)
#define NPU_REG_ACT_TABLE_8B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8B_MSK                                (((1U<<NPU_REG_ACT_TABLE_8B_LEN)-1)<<NPU_REG_ACT_TABLE_8B_POS)
#define NPU_REG_ACT_TABLE_8B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8B_LEN)-1)<<NPU_REG_ACT_TABLE_8B_POS))

/* 0x18C : BLAI_ACT_TABLE_8F_8C */
#define NPU_BLAI_ACT_TABLE_8F_8C_OFFSET                         (0x18C)
#define NPU_REG_ACT_TABLE_8C                                    NPU_REG_ACT_TABLE_8C
#define NPU_REG_ACT_TABLE_8C_POS                                (0U)
#define NPU_REG_ACT_TABLE_8C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8C_MSK                                (((1U<<NPU_REG_ACT_TABLE_8C_LEN)-1)<<NPU_REG_ACT_TABLE_8C_POS)
#define NPU_REG_ACT_TABLE_8C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8C_LEN)-1)<<NPU_REG_ACT_TABLE_8C_POS))
#define NPU_REG_ACT_TABLE_8D                                    NPU_REG_ACT_TABLE_8D
#define NPU_REG_ACT_TABLE_8D_POS                                (8U)
#define NPU_REG_ACT_TABLE_8D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8D_MSK                                (((1U<<NPU_REG_ACT_TABLE_8D_LEN)-1)<<NPU_REG_ACT_TABLE_8D_POS)
#define NPU_REG_ACT_TABLE_8D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8D_LEN)-1)<<NPU_REG_ACT_TABLE_8D_POS))
#define NPU_REG_ACT_TABLE_8E                                    NPU_REG_ACT_TABLE_8E
#define NPU_REG_ACT_TABLE_8E_POS                                (16U)
#define NPU_REG_ACT_TABLE_8E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8E_MSK                                (((1U<<NPU_REG_ACT_TABLE_8E_LEN)-1)<<NPU_REG_ACT_TABLE_8E_POS)
#define NPU_REG_ACT_TABLE_8E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8E_LEN)-1)<<NPU_REG_ACT_TABLE_8E_POS))
#define NPU_REG_ACT_TABLE_8F                                    NPU_REG_ACT_TABLE_8F
#define NPU_REG_ACT_TABLE_8F_POS                                (24U)
#define NPU_REG_ACT_TABLE_8F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_8F_MSK                                (((1U<<NPU_REG_ACT_TABLE_8F_LEN)-1)<<NPU_REG_ACT_TABLE_8F_POS)
#define NPU_REG_ACT_TABLE_8F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_8F_LEN)-1)<<NPU_REG_ACT_TABLE_8F_POS))

/* 0x190 : BLAI_ACT_TABLE_93_90 */
#define NPU_BLAI_ACT_TABLE_93_90_OFFSET                         (0x190)
#define NPU_REG_ACT_TABLE_90                                    NPU_REG_ACT_TABLE_90
#define NPU_REG_ACT_TABLE_90_POS                                (0U)
#define NPU_REG_ACT_TABLE_90_LEN                                (8U)
#define NPU_REG_ACT_TABLE_90_MSK                                (((1U<<NPU_REG_ACT_TABLE_90_LEN)-1)<<NPU_REG_ACT_TABLE_90_POS)
#define NPU_REG_ACT_TABLE_90_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_90_LEN)-1)<<NPU_REG_ACT_TABLE_90_POS))
#define NPU_REG_ACT_TABLE_91                                    NPU_REG_ACT_TABLE_91
#define NPU_REG_ACT_TABLE_91_POS                                (8U)
#define NPU_REG_ACT_TABLE_91_LEN                                (8U)
#define NPU_REG_ACT_TABLE_91_MSK                                (((1U<<NPU_REG_ACT_TABLE_91_LEN)-1)<<NPU_REG_ACT_TABLE_91_POS)
#define NPU_REG_ACT_TABLE_91_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_91_LEN)-1)<<NPU_REG_ACT_TABLE_91_POS))
#define NPU_REG_ACT_TABLE_92                                    NPU_REG_ACT_TABLE_92
#define NPU_REG_ACT_TABLE_92_POS                                (16U)
#define NPU_REG_ACT_TABLE_92_LEN                                (8U)
#define NPU_REG_ACT_TABLE_92_MSK                                (((1U<<NPU_REG_ACT_TABLE_92_LEN)-1)<<NPU_REG_ACT_TABLE_92_POS)
#define NPU_REG_ACT_TABLE_92_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_92_LEN)-1)<<NPU_REG_ACT_TABLE_92_POS))
#define NPU_REG_ACT_TABLE_93                                    NPU_REG_ACT_TABLE_93
#define NPU_REG_ACT_TABLE_93_POS                                (24U)
#define NPU_REG_ACT_TABLE_93_LEN                                (8U)
#define NPU_REG_ACT_TABLE_93_MSK                                (((1U<<NPU_REG_ACT_TABLE_93_LEN)-1)<<NPU_REG_ACT_TABLE_93_POS)
#define NPU_REG_ACT_TABLE_93_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_93_LEN)-1)<<NPU_REG_ACT_TABLE_93_POS))

/* 0x194 : BLAI_ACT_TABLE_97_94 */
#define NPU_BLAI_ACT_TABLE_97_94_OFFSET                         (0x194)
#define NPU_REG_ACT_TABLE_94                                    NPU_REG_ACT_TABLE_94
#define NPU_REG_ACT_TABLE_94_POS                                (0U)
#define NPU_REG_ACT_TABLE_94_LEN                                (8U)
#define NPU_REG_ACT_TABLE_94_MSK                                (((1U<<NPU_REG_ACT_TABLE_94_LEN)-1)<<NPU_REG_ACT_TABLE_94_POS)
#define NPU_REG_ACT_TABLE_94_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_94_LEN)-1)<<NPU_REG_ACT_TABLE_94_POS))
#define NPU_REG_ACT_TABLE_95                                    NPU_REG_ACT_TABLE_95
#define NPU_REG_ACT_TABLE_95_POS                                (8U)
#define NPU_REG_ACT_TABLE_95_LEN                                (8U)
#define NPU_REG_ACT_TABLE_95_MSK                                (((1U<<NPU_REG_ACT_TABLE_95_LEN)-1)<<NPU_REG_ACT_TABLE_95_POS)
#define NPU_REG_ACT_TABLE_95_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_95_LEN)-1)<<NPU_REG_ACT_TABLE_95_POS))
#define NPU_REG_ACT_TABLE_96                                    NPU_REG_ACT_TABLE_96
#define NPU_REG_ACT_TABLE_96_POS                                (16U)
#define NPU_REG_ACT_TABLE_96_LEN                                (8U)
#define NPU_REG_ACT_TABLE_96_MSK                                (((1U<<NPU_REG_ACT_TABLE_96_LEN)-1)<<NPU_REG_ACT_TABLE_96_POS)
#define NPU_REG_ACT_TABLE_96_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_96_LEN)-1)<<NPU_REG_ACT_TABLE_96_POS))
#define NPU_REG_ACT_TABLE_97                                    NPU_REG_ACT_TABLE_97
#define NPU_REG_ACT_TABLE_97_POS                                (24U)
#define NPU_REG_ACT_TABLE_97_LEN                                (8U)
#define NPU_REG_ACT_TABLE_97_MSK                                (((1U<<NPU_REG_ACT_TABLE_97_LEN)-1)<<NPU_REG_ACT_TABLE_97_POS)
#define NPU_REG_ACT_TABLE_97_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_97_LEN)-1)<<NPU_REG_ACT_TABLE_97_POS))

/* 0x198 : BLAI_ACT_TABLE_9B_98 */
#define NPU_BLAI_ACT_TABLE_9B_98_OFFSET                         (0x198)
#define NPU_REG_ACT_TABLE_98                                    NPU_REG_ACT_TABLE_98
#define NPU_REG_ACT_TABLE_98_POS                                (0U)
#define NPU_REG_ACT_TABLE_98_LEN                                (8U)
#define NPU_REG_ACT_TABLE_98_MSK                                (((1U<<NPU_REG_ACT_TABLE_98_LEN)-1)<<NPU_REG_ACT_TABLE_98_POS)
#define NPU_REG_ACT_TABLE_98_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_98_LEN)-1)<<NPU_REG_ACT_TABLE_98_POS))
#define NPU_REG_ACT_TABLE_99                                    NPU_REG_ACT_TABLE_99
#define NPU_REG_ACT_TABLE_99_POS                                (8U)
#define NPU_REG_ACT_TABLE_99_LEN                                (8U)
#define NPU_REG_ACT_TABLE_99_MSK                                (((1U<<NPU_REG_ACT_TABLE_99_LEN)-1)<<NPU_REG_ACT_TABLE_99_POS)
#define NPU_REG_ACT_TABLE_99_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_99_LEN)-1)<<NPU_REG_ACT_TABLE_99_POS))
#define NPU_REG_ACT_TABLE_9A                                    NPU_REG_ACT_TABLE_9A
#define NPU_REG_ACT_TABLE_9A_POS                                (16U)
#define NPU_REG_ACT_TABLE_9A_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9A_MSK                                (((1U<<NPU_REG_ACT_TABLE_9A_LEN)-1)<<NPU_REG_ACT_TABLE_9A_POS)
#define NPU_REG_ACT_TABLE_9A_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9A_LEN)-1)<<NPU_REG_ACT_TABLE_9A_POS))
#define NPU_REG_ACT_TABLE_9B                                    NPU_REG_ACT_TABLE_9B
#define NPU_REG_ACT_TABLE_9B_POS                                (24U)
#define NPU_REG_ACT_TABLE_9B_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9B_MSK                                (((1U<<NPU_REG_ACT_TABLE_9B_LEN)-1)<<NPU_REG_ACT_TABLE_9B_POS)
#define NPU_REG_ACT_TABLE_9B_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9B_LEN)-1)<<NPU_REG_ACT_TABLE_9B_POS))

/* 0x19C : BLAI_ACT_TABLE_9F_9C */
#define NPU_BLAI_ACT_TABLE_9F_9C_OFFSET                         (0x19C)
#define NPU_REG_ACT_TABLE_9C                                    NPU_REG_ACT_TABLE_9C
#define NPU_REG_ACT_TABLE_9C_POS                                (0U)
#define NPU_REG_ACT_TABLE_9C_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9C_MSK                                (((1U<<NPU_REG_ACT_TABLE_9C_LEN)-1)<<NPU_REG_ACT_TABLE_9C_POS)
#define NPU_REG_ACT_TABLE_9C_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9C_LEN)-1)<<NPU_REG_ACT_TABLE_9C_POS))
#define NPU_REG_ACT_TABLE_9D                                    NPU_REG_ACT_TABLE_9D
#define NPU_REG_ACT_TABLE_9D_POS                                (8U)
#define NPU_REG_ACT_TABLE_9D_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9D_MSK                                (((1U<<NPU_REG_ACT_TABLE_9D_LEN)-1)<<NPU_REG_ACT_TABLE_9D_POS)
#define NPU_REG_ACT_TABLE_9D_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9D_LEN)-1)<<NPU_REG_ACT_TABLE_9D_POS))
#define NPU_REG_ACT_TABLE_9E                                    NPU_REG_ACT_TABLE_9E
#define NPU_REG_ACT_TABLE_9E_POS                                (16U)
#define NPU_REG_ACT_TABLE_9E_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9E_MSK                                (((1U<<NPU_REG_ACT_TABLE_9E_LEN)-1)<<NPU_REG_ACT_TABLE_9E_POS)
#define NPU_REG_ACT_TABLE_9E_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9E_LEN)-1)<<NPU_REG_ACT_TABLE_9E_POS))
#define NPU_REG_ACT_TABLE_9F                                    NPU_REG_ACT_TABLE_9F
#define NPU_REG_ACT_TABLE_9F_POS                                (24U)
#define NPU_REG_ACT_TABLE_9F_LEN                                (8U)
#define NPU_REG_ACT_TABLE_9F_MSK                                (((1U<<NPU_REG_ACT_TABLE_9F_LEN)-1)<<NPU_REG_ACT_TABLE_9F_POS)
#define NPU_REG_ACT_TABLE_9F_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_9F_LEN)-1)<<NPU_REG_ACT_TABLE_9F_POS))

/* 0x1A0 : BLAI_ACT_TABLE_a3_a0 */
#define NPU_BLAI_ACT_TABLE_A3_A0_OFFSET                         (0x1A0)
#define NPU_REG_ACT_TABLE_A0                                    NPU_REG_ACT_TABLE_A0
#define NPU_REG_ACT_TABLE_A0_POS                                (0U)
#define NPU_REG_ACT_TABLE_A0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A0_MSK                                (((1U<<NPU_REG_ACT_TABLE_A0_LEN)-1)<<NPU_REG_ACT_TABLE_A0_POS)
#define NPU_REG_ACT_TABLE_A0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A0_LEN)-1)<<NPU_REG_ACT_TABLE_A0_POS))
#define NPU_REG_ACT_TABLE_A1                                    NPU_REG_ACT_TABLE_A1
#define NPU_REG_ACT_TABLE_A1_POS                                (8U)
#define NPU_REG_ACT_TABLE_A1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A1_MSK                                (((1U<<NPU_REG_ACT_TABLE_A1_LEN)-1)<<NPU_REG_ACT_TABLE_A1_POS)
#define NPU_REG_ACT_TABLE_A1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A1_LEN)-1)<<NPU_REG_ACT_TABLE_A1_POS))
#define NPU_REG_ACT_TABLE_A2                                    NPU_REG_ACT_TABLE_A2
#define NPU_REG_ACT_TABLE_A2_POS                                (16U)
#define NPU_REG_ACT_TABLE_A2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A2_MSK                                (((1U<<NPU_REG_ACT_TABLE_A2_LEN)-1)<<NPU_REG_ACT_TABLE_A2_POS)
#define NPU_REG_ACT_TABLE_A2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A2_LEN)-1)<<NPU_REG_ACT_TABLE_A2_POS))
#define NPU_REG_ACT_TABLE_A3                                    NPU_REG_ACT_TABLE_A3
#define NPU_REG_ACT_TABLE_A3_POS                                (24U)
#define NPU_REG_ACT_TABLE_A3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A3_MSK                                (((1U<<NPU_REG_ACT_TABLE_A3_LEN)-1)<<NPU_REG_ACT_TABLE_A3_POS)
#define NPU_REG_ACT_TABLE_A3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A3_LEN)-1)<<NPU_REG_ACT_TABLE_A3_POS))

/* 0x1A4 : BLAI_ACT_TABLE_a7_a4 */
#define NPU_BLAI_ACT_TABLE_A7_A4_OFFSET                         (0x1A4)
#define NPU_REG_ACT_TABLE_A4                                    NPU_REG_ACT_TABLE_A4
#define NPU_REG_ACT_TABLE_A4_POS                                (0U)
#define NPU_REG_ACT_TABLE_A4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A4_MSK                                (((1U<<NPU_REG_ACT_TABLE_A4_LEN)-1)<<NPU_REG_ACT_TABLE_A4_POS)
#define NPU_REG_ACT_TABLE_A4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A4_LEN)-1)<<NPU_REG_ACT_TABLE_A4_POS))
#define NPU_REG_ACT_TABLE_A5                                    NPU_REG_ACT_TABLE_A5
#define NPU_REG_ACT_TABLE_A5_POS                                (8U)
#define NPU_REG_ACT_TABLE_A5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A5_MSK                                (((1U<<NPU_REG_ACT_TABLE_A5_LEN)-1)<<NPU_REG_ACT_TABLE_A5_POS)
#define NPU_REG_ACT_TABLE_A5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A5_LEN)-1)<<NPU_REG_ACT_TABLE_A5_POS))
#define NPU_REG_ACT_TABLE_A6                                    NPU_REG_ACT_TABLE_A6
#define NPU_REG_ACT_TABLE_A6_POS                                (16U)
#define NPU_REG_ACT_TABLE_A6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A6_MSK                                (((1U<<NPU_REG_ACT_TABLE_A6_LEN)-1)<<NPU_REG_ACT_TABLE_A6_POS)
#define NPU_REG_ACT_TABLE_A6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A6_LEN)-1)<<NPU_REG_ACT_TABLE_A6_POS))
#define NPU_REG_ACT_TABLE_A7                                    NPU_REG_ACT_TABLE_A7
#define NPU_REG_ACT_TABLE_A7_POS                                (24U)
#define NPU_REG_ACT_TABLE_A7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A7_MSK                                (((1U<<NPU_REG_ACT_TABLE_A7_LEN)-1)<<NPU_REG_ACT_TABLE_A7_POS)
#define NPU_REG_ACT_TABLE_A7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A7_LEN)-1)<<NPU_REG_ACT_TABLE_A7_POS))

/* 0x1A8 : BLAI_ACT_TABLE_aB_a8 */
#define NPU_BLAI_ACT_TABLE_AB_A8_OFFSET                         (0x1A8)
#define NPU_REG_ACT_TABLE_A8                                    NPU_REG_ACT_TABLE_A8
#define NPU_REG_ACT_TABLE_A8_POS                                (0U)
#define NPU_REG_ACT_TABLE_A8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A8_MSK                                (((1U<<NPU_REG_ACT_TABLE_A8_LEN)-1)<<NPU_REG_ACT_TABLE_A8_POS)
#define NPU_REG_ACT_TABLE_A8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A8_LEN)-1)<<NPU_REG_ACT_TABLE_A8_POS))
#define NPU_REG_ACT_TABLE_A9                                    NPU_REG_ACT_TABLE_A9
#define NPU_REG_ACT_TABLE_A9_POS                                (8U)
#define NPU_REG_ACT_TABLE_A9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_A9_MSK                                (((1U<<NPU_REG_ACT_TABLE_A9_LEN)-1)<<NPU_REG_ACT_TABLE_A9_POS)
#define NPU_REG_ACT_TABLE_A9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_A9_LEN)-1)<<NPU_REG_ACT_TABLE_A9_POS))
#define NPU_REG_ACT_TABLE_AA                                    NPU_REG_ACT_TABLE_AA
#define NPU_REG_ACT_TABLE_AA_POS                                (16U)
#define NPU_REG_ACT_TABLE_AA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AA_MSK                                (((1U<<NPU_REG_ACT_TABLE_AA_LEN)-1)<<NPU_REG_ACT_TABLE_AA_POS)
#define NPU_REG_ACT_TABLE_AA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AA_LEN)-1)<<NPU_REG_ACT_TABLE_AA_POS))
#define NPU_REG_ACT_TABLE_AB                                    NPU_REG_ACT_TABLE_AB
#define NPU_REG_ACT_TABLE_AB_POS                                (24U)
#define NPU_REG_ACT_TABLE_AB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AB_MSK                                (((1U<<NPU_REG_ACT_TABLE_AB_LEN)-1)<<NPU_REG_ACT_TABLE_AB_POS)
#define NPU_REG_ACT_TABLE_AB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AB_LEN)-1)<<NPU_REG_ACT_TABLE_AB_POS))

/* 0x1AC : BLAI_ACT_TABLE_aF_aC */
#define NPU_BLAI_ACT_TABLE_AF_AC_OFFSET                         (0x1AC)
#define NPU_REG_ACT_TABLE_AC                                    NPU_REG_ACT_TABLE_AC
#define NPU_REG_ACT_TABLE_AC_POS                                (0U)
#define NPU_REG_ACT_TABLE_AC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AC_MSK                                (((1U<<NPU_REG_ACT_TABLE_AC_LEN)-1)<<NPU_REG_ACT_TABLE_AC_POS)
#define NPU_REG_ACT_TABLE_AC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AC_LEN)-1)<<NPU_REG_ACT_TABLE_AC_POS))
#define NPU_REG_ACT_TABLE_AD                                    NPU_REG_ACT_TABLE_AD
#define NPU_REG_ACT_TABLE_AD_POS                                (8U)
#define NPU_REG_ACT_TABLE_AD_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AD_MSK                                (((1U<<NPU_REG_ACT_TABLE_AD_LEN)-1)<<NPU_REG_ACT_TABLE_AD_POS)
#define NPU_REG_ACT_TABLE_AD_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AD_LEN)-1)<<NPU_REG_ACT_TABLE_AD_POS))
#define NPU_REG_ACT_TABLE_AE                                    NPU_REG_ACT_TABLE_AE
#define NPU_REG_ACT_TABLE_AE_POS                                (16U)
#define NPU_REG_ACT_TABLE_AE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AE_MSK                                (((1U<<NPU_REG_ACT_TABLE_AE_LEN)-1)<<NPU_REG_ACT_TABLE_AE_POS)
#define NPU_REG_ACT_TABLE_AE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AE_LEN)-1)<<NPU_REG_ACT_TABLE_AE_POS))
#define NPU_REG_ACT_TABLE_AF                                    NPU_REG_ACT_TABLE_AF
#define NPU_REG_ACT_TABLE_AF_POS                                (24U)
#define NPU_REG_ACT_TABLE_AF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_AF_MSK                                (((1U<<NPU_REG_ACT_TABLE_AF_LEN)-1)<<NPU_REG_ACT_TABLE_AF_POS)
#define NPU_REG_ACT_TABLE_AF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_AF_LEN)-1)<<NPU_REG_ACT_TABLE_AF_POS))

/* 0x1B0 : BLAI_ACT_TABLE_b3_b0 */
#define NPU_BLAI_ACT_TABLE_B3_B0_OFFSET                         (0x1B0)
#define NPU_REG_ACT_TABLE_B0                                    NPU_REG_ACT_TABLE_B0
#define NPU_REG_ACT_TABLE_B0_POS                                (0U)
#define NPU_REG_ACT_TABLE_B0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B0_MSK                                (((1U<<NPU_REG_ACT_TABLE_B0_LEN)-1)<<NPU_REG_ACT_TABLE_B0_POS)
#define NPU_REG_ACT_TABLE_B0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B0_LEN)-1)<<NPU_REG_ACT_TABLE_B0_POS))
#define NPU_REG_ACT_TABLE_B1                                    NPU_REG_ACT_TABLE_B1
#define NPU_REG_ACT_TABLE_B1_POS                                (8U)
#define NPU_REG_ACT_TABLE_B1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B1_MSK                                (((1U<<NPU_REG_ACT_TABLE_B1_LEN)-1)<<NPU_REG_ACT_TABLE_B1_POS)
#define NPU_REG_ACT_TABLE_B1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B1_LEN)-1)<<NPU_REG_ACT_TABLE_B1_POS))
#define NPU_REG_ACT_TABLE_B2                                    NPU_REG_ACT_TABLE_B2
#define NPU_REG_ACT_TABLE_B2_POS                                (16U)
#define NPU_REG_ACT_TABLE_B2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B2_MSK                                (((1U<<NPU_REG_ACT_TABLE_B2_LEN)-1)<<NPU_REG_ACT_TABLE_B2_POS)
#define NPU_REG_ACT_TABLE_B2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B2_LEN)-1)<<NPU_REG_ACT_TABLE_B2_POS))
#define NPU_REG_ACT_TABLE_B3                                    NPU_REG_ACT_TABLE_B3
#define NPU_REG_ACT_TABLE_B3_POS                                (24U)
#define NPU_REG_ACT_TABLE_B3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B3_MSK                                (((1U<<NPU_REG_ACT_TABLE_B3_LEN)-1)<<NPU_REG_ACT_TABLE_B3_POS)
#define NPU_REG_ACT_TABLE_B3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B3_LEN)-1)<<NPU_REG_ACT_TABLE_B3_POS))

/* 0x1B4 : BLAI_ACT_TABLE_b7_b4 */
#define NPU_BLAI_ACT_TABLE_B7_B4_OFFSET                         (0x1B4)
#define NPU_REG_ACT_TABLE_B4                                    NPU_REG_ACT_TABLE_B4
#define NPU_REG_ACT_TABLE_B4_POS                                (0U)
#define NPU_REG_ACT_TABLE_B4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B4_MSK                                (((1U<<NPU_REG_ACT_TABLE_B4_LEN)-1)<<NPU_REG_ACT_TABLE_B4_POS)
#define NPU_REG_ACT_TABLE_B4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B4_LEN)-1)<<NPU_REG_ACT_TABLE_B4_POS))
#define NPU_REG_ACT_TABLE_B5                                    NPU_REG_ACT_TABLE_B5
#define NPU_REG_ACT_TABLE_B5_POS                                (8U)
#define NPU_REG_ACT_TABLE_B5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B5_MSK                                (((1U<<NPU_REG_ACT_TABLE_B5_LEN)-1)<<NPU_REG_ACT_TABLE_B5_POS)
#define NPU_REG_ACT_TABLE_B5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B5_LEN)-1)<<NPU_REG_ACT_TABLE_B5_POS))
#define NPU_REG_ACT_TABLE_B6                                    NPU_REG_ACT_TABLE_B6
#define NPU_REG_ACT_TABLE_B6_POS                                (16U)
#define NPU_REG_ACT_TABLE_B6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B6_MSK                                (((1U<<NPU_REG_ACT_TABLE_B6_LEN)-1)<<NPU_REG_ACT_TABLE_B6_POS)
#define NPU_REG_ACT_TABLE_B6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B6_LEN)-1)<<NPU_REG_ACT_TABLE_B6_POS))
#define NPU_REG_ACT_TABLE_B7                                    NPU_REG_ACT_TABLE_B7
#define NPU_REG_ACT_TABLE_B7_POS                                (24U)
#define NPU_REG_ACT_TABLE_B7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B7_MSK                                (((1U<<NPU_REG_ACT_TABLE_B7_LEN)-1)<<NPU_REG_ACT_TABLE_B7_POS)
#define NPU_REG_ACT_TABLE_B7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B7_LEN)-1)<<NPU_REG_ACT_TABLE_B7_POS))

/* 0x1B8 : BLAI_ACT_TABLE_bB_b8 */
#define NPU_BLAI_ACT_TABLE_BB_B8_OFFSET                         (0x1B8)
#define NPU_REG_ACT_TABLE_B8                                    NPU_REG_ACT_TABLE_B8
#define NPU_REG_ACT_TABLE_B8_POS                                (0U)
#define NPU_REG_ACT_TABLE_B8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B8_MSK                                (((1U<<NPU_REG_ACT_TABLE_B8_LEN)-1)<<NPU_REG_ACT_TABLE_B8_POS)
#define NPU_REG_ACT_TABLE_B8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B8_LEN)-1)<<NPU_REG_ACT_TABLE_B8_POS))
#define NPU_REG_ACT_TABLE_B9                                    NPU_REG_ACT_TABLE_B9
#define NPU_REG_ACT_TABLE_B9_POS                                (8U)
#define NPU_REG_ACT_TABLE_B9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_B9_MSK                                (((1U<<NPU_REG_ACT_TABLE_B9_LEN)-1)<<NPU_REG_ACT_TABLE_B9_POS)
#define NPU_REG_ACT_TABLE_B9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_B9_LEN)-1)<<NPU_REG_ACT_TABLE_B9_POS))
#define NPU_REG_ACT_TABLE_BA                                    NPU_REG_ACT_TABLE_BA
#define NPU_REG_ACT_TABLE_BA_POS                                (16U)
#define NPU_REG_ACT_TABLE_BA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BA_MSK                                (((1U<<NPU_REG_ACT_TABLE_BA_LEN)-1)<<NPU_REG_ACT_TABLE_BA_POS)
#define NPU_REG_ACT_TABLE_BA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BA_LEN)-1)<<NPU_REG_ACT_TABLE_BA_POS))
#define NPU_REG_ACT_TABLE_BB                                    NPU_REG_ACT_TABLE_BB
#define NPU_REG_ACT_TABLE_BB_POS                                (24U)
#define NPU_REG_ACT_TABLE_BB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BB_MSK                                (((1U<<NPU_REG_ACT_TABLE_BB_LEN)-1)<<NPU_REG_ACT_TABLE_BB_POS)
#define NPU_REG_ACT_TABLE_BB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BB_LEN)-1)<<NPU_REG_ACT_TABLE_BB_POS))

/* 0x1BC : BLAI_ACT_TABLE_bF_bC */
#define NPU_BLAI_ACT_TABLE_BF_BC_OFFSET                         (0x1BC)
#define NPU_REG_ACT_TABLE_BC                                    NPU_REG_ACT_TABLE_BC
#define NPU_REG_ACT_TABLE_BC_POS                                (0U)
#define NPU_REG_ACT_TABLE_BC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BC_MSK                                (((1U<<NPU_REG_ACT_TABLE_BC_LEN)-1)<<NPU_REG_ACT_TABLE_BC_POS)
#define NPU_REG_ACT_TABLE_BC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BC_LEN)-1)<<NPU_REG_ACT_TABLE_BC_POS))
#define NPU_REG_ACT_TABLE_BD                                    NPU_REG_ACT_TABLE_BD
#define NPU_REG_ACT_TABLE_BD_POS                                (8U)
#define NPU_REG_ACT_TABLE_BD_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BD_MSK                                (((1U<<NPU_REG_ACT_TABLE_BD_LEN)-1)<<NPU_REG_ACT_TABLE_BD_POS)
#define NPU_REG_ACT_TABLE_BD_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BD_LEN)-1)<<NPU_REG_ACT_TABLE_BD_POS))
#define NPU_REG_ACT_TABLE_BE                                    NPU_REG_ACT_TABLE_BE
#define NPU_REG_ACT_TABLE_BE_POS                                (16U)
#define NPU_REG_ACT_TABLE_BE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BE_MSK                                (((1U<<NPU_REG_ACT_TABLE_BE_LEN)-1)<<NPU_REG_ACT_TABLE_BE_POS)
#define NPU_REG_ACT_TABLE_BE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BE_LEN)-1)<<NPU_REG_ACT_TABLE_BE_POS))
#define NPU_REG_ACT_TABLE_BF                                    NPU_REG_ACT_TABLE_BF
#define NPU_REG_ACT_TABLE_BF_POS                                (24U)
#define NPU_REG_ACT_TABLE_BF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_BF_MSK                                (((1U<<NPU_REG_ACT_TABLE_BF_LEN)-1)<<NPU_REG_ACT_TABLE_BF_POS)
#define NPU_REG_ACT_TABLE_BF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_BF_LEN)-1)<<NPU_REG_ACT_TABLE_BF_POS))

/* 0x1C0 : BLAI_ACT_TABLE_c3_c0 */
#define NPU_BLAI_ACT_TABLE_C3_C0_OFFSET                         (0x1C0)
#define NPU_REG_ACT_TABLE_C0                                    NPU_REG_ACT_TABLE_C0
#define NPU_REG_ACT_TABLE_C0_POS                                (0U)
#define NPU_REG_ACT_TABLE_C0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C0_MSK                                (((1U<<NPU_REG_ACT_TABLE_C0_LEN)-1)<<NPU_REG_ACT_TABLE_C0_POS)
#define NPU_REG_ACT_TABLE_C0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C0_LEN)-1)<<NPU_REG_ACT_TABLE_C0_POS))
#define NPU_REG_ACT_TABLE_C1                                    NPU_REG_ACT_TABLE_C1
#define NPU_REG_ACT_TABLE_C1_POS                                (8U)
#define NPU_REG_ACT_TABLE_C1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C1_MSK                                (((1U<<NPU_REG_ACT_TABLE_C1_LEN)-1)<<NPU_REG_ACT_TABLE_C1_POS)
#define NPU_REG_ACT_TABLE_C1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C1_LEN)-1)<<NPU_REG_ACT_TABLE_C1_POS))
#define NPU_REG_ACT_TABLE_C2                                    NPU_REG_ACT_TABLE_C2
#define NPU_REG_ACT_TABLE_C2_POS                                (16U)
#define NPU_REG_ACT_TABLE_C2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C2_MSK                                (((1U<<NPU_REG_ACT_TABLE_C2_LEN)-1)<<NPU_REG_ACT_TABLE_C2_POS)
#define NPU_REG_ACT_TABLE_C2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C2_LEN)-1)<<NPU_REG_ACT_TABLE_C2_POS))
#define NPU_REG_ACT_TABLE_C3                                    NPU_REG_ACT_TABLE_C3
#define NPU_REG_ACT_TABLE_C3_POS                                (24U)
#define NPU_REG_ACT_TABLE_C3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C3_MSK                                (((1U<<NPU_REG_ACT_TABLE_C3_LEN)-1)<<NPU_REG_ACT_TABLE_C3_POS)
#define NPU_REG_ACT_TABLE_C3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C3_LEN)-1)<<NPU_REG_ACT_TABLE_C3_POS))

/* 0x1C4 : BLAI_ACT_TABLE_c7_c4 */
#define NPU_BLAI_ACT_TABLE_C7_C4_OFFSET                         (0x1C4)
#define NPU_REG_ACT_TABLE_C4                                    NPU_REG_ACT_TABLE_C4
#define NPU_REG_ACT_TABLE_C4_POS                                (0U)
#define NPU_REG_ACT_TABLE_C4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C4_MSK                                (((1U<<NPU_REG_ACT_TABLE_C4_LEN)-1)<<NPU_REG_ACT_TABLE_C4_POS)
#define NPU_REG_ACT_TABLE_C4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C4_LEN)-1)<<NPU_REG_ACT_TABLE_C4_POS))
#define NPU_REG_ACT_TABLE_C5                                    NPU_REG_ACT_TABLE_C5
#define NPU_REG_ACT_TABLE_C5_POS                                (8U)
#define NPU_REG_ACT_TABLE_C5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C5_MSK                                (((1U<<NPU_REG_ACT_TABLE_C5_LEN)-1)<<NPU_REG_ACT_TABLE_C5_POS)
#define NPU_REG_ACT_TABLE_C5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C5_LEN)-1)<<NPU_REG_ACT_TABLE_C5_POS))
#define NPU_REG_ACT_TABLE_C6                                    NPU_REG_ACT_TABLE_C6
#define NPU_REG_ACT_TABLE_C6_POS                                (16U)
#define NPU_REG_ACT_TABLE_C6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C6_MSK                                (((1U<<NPU_REG_ACT_TABLE_C6_LEN)-1)<<NPU_REG_ACT_TABLE_C6_POS)
#define NPU_REG_ACT_TABLE_C6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C6_LEN)-1)<<NPU_REG_ACT_TABLE_C6_POS))
#define NPU_REG_ACT_TABLE_C7                                    NPU_REG_ACT_TABLE_C7
#define NPU_REG_ACT_TABLE_C7_POS                                (24U)
#define NPU_REG_ACT_TABLE_C7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C7_MSK                                (((1U<<NPU_REG_ACT_TABLE_C7_LEN)-1)<<NPU_REG_ACT_TABLE_C7_POS)
#define NPU_REG_ACT_TABLE_C7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C7_LEN)-1)<<NPU_REG_ACT_TABLE_C7_POS))

/* 0x1C8 : BLAI_ACT_TABLE_cB_c8 */
#define NPU_BLAI_ACT_TABLE_CB_C8_OFFSET                         (0x1C8)
#define NPU_REG_ACT_TABLE_C8                                    NPU_REG_ACT_TABLE_C8
#define NPU_REG_ACT_TABLE_C8_POS                                (0U)
#define NPU_REG_ACT_TABLE_C8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C8_MSK                                (((1U<<NPU_REG_ACT_TABLE_C8_LEN)-1)<<NPU_REG_ACT_TABLE_C8_POS)
#define NPU_REG_ACT_TABLE_C8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C8_LEN)-1)<<NPU_REG_ACT_TABLE_C8_POS))
#define NPU_REG_ACT_TABLE_C9                                    NPU_REG_ACT_TABLE_C9
#define NPU_REG_ACT_TABLE_C9_POS                                (8U)
#define NPU_REG_ACT_TABLE_C9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_C9_MSK                                (((1U<<NPU_REG_ACT_TABLE_C9_LEN)-1)<<NPU_REG_ACT_TABLE_C9_POS)
#define NPU_REG_ACT_TABLE_C9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_C9_LEN)-1)<<NPU_REG_ACT_TABLE_C9_POS))
#define NPU_REG_ACT_TABLE_CA                                    NPU_REG_ACT_TABLE_CA
#define NPU_REG_ACT_TABLE_CA_POS                                (16U)
#define NPU_REG_ACT_TABLE_CA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CA_MSK                                (((1U<<NPU_REG_ACT_TABLE_CA_LEN)-1)<<NPU_REG_ACT_TABLE_CA_POS)
#define NPU_REG_ACT_TABLE_CA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CA_LEN)-1)<<NPU_REG_ACT_TABLE_CA_POS))
#define NPU_REG_ACT_TABLE_CB                                    NPU_REG_ACT_TABLE_CB
#define NPU_REG_ACT_TABLE_CB_POS                                (24U)
#define NPU_REG_ACT_TABLE_CB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CB_MSK                                (((1U<<NPU_REG_ACT_TABLE_CB_LEN)-1)<<NPU_REG_ACT_TABLE_CB_POS)
#define NPU_REG_ACT_TABLE_CB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CB_LEN)-1)<<NPU_REG_ACT_TABLE_CB_POS))

/* 0x1CC : BLAI_ACT_TABLE_cF_cC */
#define NPU_BLAI_ACT_TABLE_CF_CC_OFFSET                         (0x1CC)
#define NPU_REG_ACT_TABLE_CC                                    NPU_REG_ACT_TABLE_CC
#define NPU_REG_ACT_TABLE_CC_POS                                (0U)
#define NPU_REG_ACT_TABLE_CC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CC_MSK                                (((1U<<NPU_REG_ACT_TABLE_CC_LEN)-1)<<NPU_REG_ACT_TABLE_CC_POS)
#define NPU_REG_ACT_TABLE_CC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CC_LEN)-1)<<NPU_REG_ACT_TABLE_CC_POS))
#define NPU_REG_ACT_TABLE_CD                                    NPU_REG_ACT_TABLE_CD
#define NPU_REG_ACT_TABLE_CD_POS                                (8U)
#define NPU_REG_ACT_TABLE_CD_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CD_MSK                                (((1U<<NPU_REG_ACT_TABLE_CD_LEN)-1)<<NPU_REG_ACT_TABLE_CD_POS)
#define NPU_REG_ACT_TABLE_CD_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CD_LEN)-1)<<NPU_REG_ACT_TABLE_CD_POS))
#define NPU_REG_ACT_TABLE_CE                                    NPU_REG_ACT_TABLE_CE
#define NPU_REG_ACT_TABLE_CE_POS                                (16U)
#define NPU_REG_ACT_TABLE_CE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CE_MSK                                (((1U<<NPU_REG_ACT_TABLE_CE_LEN)-1)<<NPU_REG_ACT_TABLE_CE_POS)
#define NPU_REG_ACT_TABLE_CE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CE_LEN)-1)<<NPU_REG_ACT_TABLE_CE_POS))
#define NPU_REG_ACT_TABLE_CF                                    NPU_REG_ACT_TABLE_CF
#define NPU_REG_ACT_TABLE_CF_POS                                (24U)
#define NPU_REG_ACT_TABLE_CF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_CF_MSK                                (((1U<<NPU_REG_ACT_TABLE_CF_LEN)-1)<<NPU_REG_ACT_TABLE_CF_POS)
#define NPU_REG_ACT_TABLE_CF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_CF_LEN)-1)<<NPU_REG_ACT_TABLE_CF_POS))

/* 0x1D0 : BLAI_ACT_TABLE_d3_d0 */
#define NPU_BLAI_ACT_TABLE_D3_D0_OFFSET                         (0x1D0)
#define NPU_REG_ACT_TABLE_D0                                    NPU_REG_ACT_TABLE_D0
#define NPU_REG_ACT_TABLE_D0_POS                                (0U)
#define NPU_REG_ACT_TABLE_D0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D0_MSK                                (((1U<<NPU_REG_ACT_TABLE_D0_LEN)-1)<<NPU_REG_ACT_TABLE_D0_POS)
#define NPU_REG_ACT_TABLE_D0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D0_LEN)-1)<<NPU_REG_ACT_TABLE_D0_POS))
#define NPU_REG_ACT_TABLE_D1                                    NPU_REG_ACT_TABLE_D1
#define NPU_REG_ACT_TABLE_D1_POS                                (8U)
#define NPU_REG_ACT_TABLE_D1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D1_MSK                                (((1U<<NPU_REG_ACT_TABLE_D1_LEN)-1)<<NPU_REG_ACT_TABLE_D1_POS)
#define NPU_REG_ACT_TABLE_D1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D1_LEN)-1)<<NPU_REG_ACT_TABLE_D1_POS))
#define NPU_REG_ACT_TABLE_D2                                    NPU_REG_ACT_TABLE_D2
#define NPU_REG_ACT_TABLE_D2_POS                                (16U)
#define NPU_REG_ACT_TABLE_D2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D2_MSK                                (((1U<<NPU_REG_ACT_TABLE_D2_LEN)-1)<<NPU_REG_ACT_TABLE_D2_POS)
#define NPU_REG_ACT_TABLE_D2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D2_LEN)-1)<<NPU_REG_ACT_TABLE_D2_POS))
#define NPU_REG_ACT_TABLE_D3                                    NPU_REG_ACT_TABLE_D3
#define NPU_REG_ACT_TABLE_D3_POS                                (24U)
#define NPU_REG_ACT_TABLE_D3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D3_MSK                                (((1U<<NPU_REG_ACT_TABLE_D3_LEN)-1)<<NPU_REG_ACT_TABLE_D3_POS)
#define NPU_REG_ACT_TABLE_D3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D3_LEN)-1)<<NPU_REG_ACT_TABLE_D3_POS))

/* 0x1D4 : BLAI_ACT_TABLE_d7_d4 */
#define NPU_BLAI_ACT_TABLE_D7_D4_OFFSET                         (0x1D4)
#define NPU_REG_ACT_TABLE_D4                                    NPU_REG_ACT_TABLE_D4
#define NPU_REG_ACT_TABLE_D4_POS                                (0U)
#define NPU_REG_ACT_TABLE_D4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D4_MSK                                (((1U<<NPU_REG_ACT_TABLE_D4_LEN)-1)<<NPU_REG_ACT_TABLE_D4_POS)
#define NPU_REG_ACT_TABLE_D4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D4_LEN)-1)<<NPU_REG_ACT_TABLE_D4_POS))
#define NPU_REG_ACT_TABLE_D5                                    NPU_REG_ACT_TABLE_D5
#define NPU_REG_ACT_TABLE_D5_POS                                (8U)
#define NPU_REG_ACT_TABLE_D5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D5_MSK                                (((1U<<NPU_REG_ACT_TABLE_D5_LEN)-1)<<NPU_REG_ACT_TABLE_D5_POS)
#define NPU_REG_ACT_TABLE_D5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D5_LEN)-1)<<NPU_REG_ACT_TABLE_D5_POS))
#define NPU_REG_ACT_TABLE_D6                                    NPU_REG_ACT_TABLE_D6
#define NPU_REG_ACT_TABLE_D6_POS                                (16U)
#define NPU_REG_ACT_TABLE_D6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D6_MSK                                (((1U<<NPU_REG_ACT_TABLE_D6_LEN)-1)<<NPU_REG_ACT_TABLE_D6_POS)
#define NPU_REG_ACT_TABLE_D6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D6_LEN)-1)<<NPU_REG_ACT_TABLE_D6_POS))
#define NPU_REG_ACT_TABLE_D7                                    NPU_REG_ACT_TABLE_D7
#define NPU_REG_ACT_TABLE_D7_POS                                (24U)
#define NPU_REG_ACT_TABLE_D7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D7_MSK                                (((1U<<NPU_REG_ACT_TABLE_D7_LEN)-1)<<NPU_REG_ACT_TABLE_D7_POS)
#define NPU_REG_ACT_TABLE_D7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D7_LEN)-1)<<NPU_REG_ACT_TABLE_D7_POS))

/* 0x1D8 : BLAI_ACT_TABLE_dB_d8 */
#define NPU_BLAI_ACT_TABLE_DB_D8_OFFSET                         (0x1D8)
#define NPU_REG_ACT_TABLE_D8                                    NPU_REG_ACT_TABLE_D8
#define NPU_REG_ACT_TABLE_D8_POS                                (0U)
#define NPU_REG_ACT_TABLE_D8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D8_MSK                                (((1U<<NPU_REG_ACT_TABLE_D8_LEN)-1)<<NPU_REG_ACT_TABLE_D8_POS)
#define NPU_REG_ACT_TABLE_D8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D8_LEN)-1)<<NPU_REG_ACT_TABLE_D8_POS))
#define NPU_REG_ACT_TABLE_D9                                    NPU_REG_ACT_TABLE_D9
#define NPU_REG_ACT_TABLE_D9_POS                                (8U)
#define NPU_REG_ACT_TABLE_D9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_D9_MSK                                (((1U<<NPU_REG_ACT_TABLE_D9_LEN)-1)<<NPU_REG_ACT_TABLE_D9_POS)
#define NPU_REG_ACT_TABLE_D9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_D9_LEN)-1)<<NPU_REG_ACT_TABLE_D9_POS))
#define NPU_REG_ACT_TABLE_DA                                    NPU_REG_ACT_TABLE_DA
#define NPU_REG_ACT_TABLE_DA_POS                                (16U)
#define NPU_REG_ACT_TABLE_DA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DA_MSK                                (((1U<<NPU_REG_ACT_TABLE_DA_LEN)-1)<<NPU_REG_ACT_TABLE_DA_POS)
#define NPU_REG_ACT_TABLE_DA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DA_LEN)-1)<<NPU_REG_ACT_TABLE_DA_POS))
#define NPU_REG_ACT_TABLE_DB                                    NPU_REG_ACT_TABLE_DB
#define NPU_REG_ACT_TABLE_DB_POS                                (24U)
#define NPU_REG_ACT_TABLE_DB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DB_MSK                                (((1U<<NPU_REG_ACT_TABLE_DB_LEN)-1)<<NPU_REG_ACT_TABLE_DB_POS)
#define NPU_REG_ACT_TABLE_DB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DB_LEN)-1)<<NPU_REG_ACT_TABLE_DB_POS))

/* 0x1DC : BLAI_ACT_TABLE_dF_dC */
#define NPU_BLAI_ACT_TABLE_DF_DC_OFFSET                         (0x1DC)
#define NPU_REG_ACT_TABLE_DC                                    NPU_REG_ACT_TABLE_DC
#define NPU_REG_ACT_TABLE_DC_POS                                (0U)
#define NPU_REG_ACT_TABLE_DC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DC_MSK                                (((1U<<NPU_REG_ACT_TABLE_DC_LEN)-1)<<NPU_REG_ACT_TABLE_DC_POS)
#define NPU_REG_ACT_TABLE_DC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DC_LEN)-1)<<NPU_REG_ACT_TABLE_DC_POS))
#define NPU_REG_ACT_TABLE_DD                                    NPU_REG_ACT_TABLE_DD
#define NPU_REG_ACT_TABLE_DD_POS                                (8U)
#define NPU_REG_ACT_TABLE_DD_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DD_MSK                                (((1U<<NPU_REG_ACT_TABLE_DD_LEN)-1)<<NPU_REG_ACT_TABLE_DD_POS)
#define NPU_REG_ACT_TABLE_DD_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DD_LEN)-1)<<NPU_REG_ACT_TABLE_DD_POS))
#define NPU_REG_ACT_TABLE_DE                                    NPU_REG_ACT_TABLE_DE
#define NPU_REG_ACT_TABLE_DE_POS                                (16U)
#define NPU_REG_ACT_TABLE_DE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DE_MSK                                (((1U<<NPU_REG_ACT_TABLE_DE_LEN)-1)<<NPU_REG_ACT_TABLE_DE_POS)
#define NPU_REG_ACT_TABLE_DE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DE_LEN)-1)<<NPU_REG_ACT_TABLE_DE_POS))
#define NPU_REG_ACT_TABLE_DF                                    NPU_REG_ACT_TABLE_DF
#define NPU_REG_ACT_TABLE_DF_POS                                (24U)
#define NPU_REG_ACT_TABLE_DF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_DF_MSK                                (((1U<<NPU_REG_ACT_TABLE_DF_LEN)-1)<<NPU_REG_ACT_TABLE_DF_POS)
#define NPU_REG_ACT_TABLE_DF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_DF_LEN)-1)<<NPU_REG_ACT_TABLE_DF_POS))

/* 0x1E0 : BLAI_ACT_TABLE_e3_e0 */
#define NPU_BLAI_ACT_TABLE_E3_E0_OFFSET                         (0x1E0)
#define NPU_REG_ACT_TABLE_E0                                    NPU_REG_ACT_TABLE_E0
#define NPU_REG_ACT_TABLE_E0_POS                                (0U)
#define NPU_REG_ACT_TABLE_E0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E0_MSK                                (((1U<<NPU_REG_ACT_TABLE_E0_LEN)-1)<<NPU_REG_ACT_TABLE_E0_POS)
#define NPU_REG_ACT_TABLE_E0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E0_LEN)-1)<<NPU_REG_ACT_TABLE_E0_POS))
#define NPU_REG_ACT_TABLE_E1                                    NPU_REG_ACT_TABLE_E1
#define NPU_REG_ACT_TABLE_E1_POS                                (8U)
#define NPU_REG_ACT_TABLE_E1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E1_MSK                                (((1U<<NPU_REG_ACT_TABLE_E1_LEN)-1)<<NPU_REG_ACT_TABLE_E1_POS)
#define NPU_REG_ACT_TABLE_E1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E1_LEN)-1)<<NPU_REG_ACT_TABLE_E1_POS))
#define NPU_REG_ACT_TABLE_E2                                    NPU_REG_ACT_TABLE_E2
#define NPU_REG_ACT_TABLE_E2_POS                                (16U)
#define NPU_REG_ACT_TABLE_E2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E2_MSK                                (((1U<<NPU_REG_ACT_TABLE_E2_LEN)-1)<<NPU_REG_ACT_TABLE_E2_POS)
#define NPU_REG_ACT_TABLE_E2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E2_LEN)-1)<<NPU_REG_ACT_TABLE_E2_POS))
#define NPU_REG_ACT_TABLE_E3                                    NPU_REG_ACT_TABLE_E3
#define NPU_REG_ACT_TABLE_E3_POS                                (24U)
#define NPU_REG_ACT_TABLE_E3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E3_MSK                                (((1U<<NPU_REG_ACT_TABLE_E3_LEN)-1)<<NPU_REG_ACT_TABLE_E3_POS)
#define NPU_REG_ACT_TABLE_E3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E3_LEN)-1)<<NPU_REG_ACT_TABLE_E3_POS))

/* 0x1E4 : BLAI_ACT_TABLE_e7_e4 */
#define NPU_BLAI_ACT_TABLE_E7_E4_OFFSET                         (0x1E4)
#define NPU_REG_ACT_TABLE_E4                                    NPU_REG_ACT_TABLE_E4
#define NPU_REG_ACT_TABLE_E4_POS                                (0U)
#define NPU_REG_ACT_TABLE_E4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E4_MSK                                (((1U<<NPU_REG_ACT_TABLE_E4_LEN)-1)<<NPU_REG_ACT_TABLE_E4_POS)
#define NPU_REG_ACT_TABLE_E4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E4_LEN)-1)<<NPU_REG_ACT_TABLE_E4_POS))
#define NPU_REG_ACT_TABLE_E5                                    NPU_REG_ACT_TABLE_E5
#define NPU_REG_ACT_TABLE_E5_POS                                (8U)
#define NPU_REG_ACT_TABLE_E5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E5_MSK                                (((1U<<NPU_REG_ACT_TABLE_E5_LEN)-1)<<NPU_REG_ACT_TABLE_E5_POS)
#define NPU_REG_ACT_TABLE_E5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E5_LEN)-1)<<NPU_REG_ACT_TABLE_E5_POS))
#define NPU_REG_ACT_TABLE_E6                                    NPU_REG_ACT_TABLE_E6
#define NPU_REG_ACT_TABLE_E6_POS                                (16U)
#define NPU_REG_ACT_TABLE_E6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E6_MSK                                (((1U<<NPU_REG_ACT_TABLE_E6_LEN)-1)<<NPU_REG_ACT_TABLE_E6_POS)
#define NPU_REG_ACT_TABLE_E6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E6_LEN)-1)<<NPU_REG_ACT_TABLE_E6_POS))
#define NPU_REG_ACT_TABLE_E7                                    NPU_REG_ACT_TABLE_E7
#define NPU_REG_ACT_TABLE_E7_POS                                (24U)
#define NPU_REG_ACT_TABLE_E7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E7_MSK                                (((1U<<NPU_REG_ACT_TABLE_E7_LEN)-1)<<NPU_REG_ACT_TABLE_E7_POS)
#define NPU_REG_ACT_TABLE_E7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E7_LEN)-1)<<NPU_REG_ACT_TABLE_E7_POS))

/* 0x1E8 : BLAI_ACT_TABLE_eB_e8 */
#define NPU_BLAI_ACT_TABLE_EB_E8_OFFSET                         (0x1E8)
#define NPU_REG_ACT_TABLE_E8                                    NPU_REG_ACT_TABLE_E8
#define NPU_REG_ACT_TABLE_E8_POS                                (0U)
#define NPU_REG_ACT_TABLE_E8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E8_MSK                                (((1U<<NPU_REG_ACT_TABLE_E8_LEN)-1)<<NPU_REG_ACT_TABLE_E8_POS)
#define NPU_REG_ACT_TABLE_E8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E8_LEN)-1)<<NPU_REG_ACT_TABLE_E8_POS))
#define NPU_REG_ACT_TABLE_E9                                    NPU_REG_ACT_TABLE_E9
#define NPU_REG_ACT_TABLE_E9_POS                                (8U)
#define NPU_REG_ACT_TABLE_E9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_E9_MSK                                (((1U<<NPU_REG_ACT_TABLE_E9_LEN)-1)<<NPU_REG_ACT_TABLE_E9_POS)
#define NPU_REG_ACT_TABLE_E9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_E9_LEN)-1)<<NPU_REG_ACT_TABLE_E9_POS))
#define NPU_REG_ACT_TABLE_EA                                    NPU_REG_ACT_TABLE_EA
#define NPU_REG_ACT_TABLE_EA_POS                                (16U)
#define NPU_REG_ACT_TABLE_EA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_EA_MSK                                (((1U<<NPU_REG_ACT_TABLE_EA_LEN)-1)<<NPU_REG_ACT_TABLE_EA_POS)
#define NPU_REG_ACT_TABLE_EA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_EA_LEN)-1)<<NPU_REG_ACT_TABLE_EA_POS))
#define NPU_REG_ACT_TABLE_EB                                    NPU_REG_ACT_TABLE_EB
#define NPU_REG_ACT_TABLE_EB_POS                                (24U)
#define NPU_REG_ACT_TABLE_EB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_EB_MSK                                (((1U<<NPU_REG_ACT_TABLE_EB_LEN)-1)<<NPU_REG_ACT_TABLE_EB_POS)
#define NPU_REG_ACT_TABLE_EB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_EB_LEN)-1)<<NPU_REG_ACT_TABLE_EB_POS))

/* 0x1EC : BLAI_ACT_TABLE_eF_eC */
#define NPU_BLAI_ACT_TABLE_EF_EC_OFFSET                         (0x1EC)
#define NPU_REG_ACT_TABLE_EC                                    NPU_REG_ACT_TABLE_EC
#define NPU_REG_ACT_TABLE_EC_POS                                (0U)
#define NPU_REG_ACT_TABLE_EC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_EC_MSK                                (((1U<<NPU_REG_ACT_TABLE_EC_LEN)-1)<<NPU_REG_ACT_TABLE_EC_POS)
#define NPU_REG_ACT_TABLE_EC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_EC_LEN)-1)<<NPU_REG_ACT_TABLE_EC_POS))
#define NPU_REG_ACT_TABLE_ED                                    NPU_REG_ACT_TABLE_ED
#define NPU_REG_ACT_TABLE_ED_POS                                (8U)
#define NPU_REG_ACT_TABLE_ED_LEN                                (8U)
#define NPU_REG_ACT_TABLE_ED_MSK                                (((1U<<NPU_REG_ACT_TABLE_ED_LEN)-1)<<NPU_REG_ACT_TABLE_ED_POS)
#define NPU_REG_ACT_TABLE_ED_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_ED_LEN)-1)<<NPU_REG_ACT_TABLE_ED_POS))
#define NPU_REG_ACT_TABLE_EE                                    NPU_REG_ACT_TABLE_EE
#define NPU_REG_ACT_TABLE_EE_POS                                (16U)
#define NPU_REG_ACT_TABLE_EE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_EE_MSK                                (((1U<<NPU_REG_ACT_TABLE_EE_LEN)-1)<<NPU_REG_ACT_TABLE_EE_POS)
#define NPU_REG_ACT_TABLE_EE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_EE_LEN)-1)<<NPU_REG_ACT_TABLE_EE_POS))
#define NPU_REG_ACT_TABLE_EF                                    NPU_REG_ACT_TABLE_EF
#define NPU_REG_ACT_TABLE_EF_POS                                (24U)
#define NPU_REG_ACT_TABLE_EF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_EF_MSK                                (((1U<<NPU_REG_ACT_TABLE_EF_LEN)-1)<<NPU_REG_ACT_TABLE_EF_POS)
#define NPU_REG_ACT_TABLE_EF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_EF_LEN)-1)<<NPU_REG_ACT_TABLE_EF_POS))

/* 0x1F0 : BLAI_ACT_TABLE_f3_f0 */
#define NPU_BLAI_ACT_TABLE_F3_F0_OFFSET                         (0x1F0)
#define NPU_REG_ACT_TABLE_F0                                    NPU_REG_ACT_TABLE_F0
#define NPU_REG_ACT_TABLE_F0_POS                                (0U)
#define NPU_REG_ACT_TABLE_F0_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F0_MSK                                (((1U<<NPU_REG_ACT_TABLE_F0_LEN)-1)<<NPU_REG_ACT_TABLE_F0_POS)
#define NPU_REG_ACT_TABLE_F0_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F0_LEN)-1)<<NPU_REG_ACT_TABLE_F0_POS))
#define NPU_REG_ACT_TABLE_F1                                    NPU_REG_ACT_TABLE_F1
#define NPU_REG_ACT_TABLE_F1_POS                                (8U)
#define NPU_REG_ACT_TABLE_F1_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F1_MSK                                (((1U<<NPU_REG_ACT_TABLE_F1_LEN)-1)<<NPU_REG_ACT_TABLE_F1_POS)
#define NPU_REG_ACT_TABLE_F1_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F1_LEN)-1)<<NPU_REG_ACT_TABLE_F1_POS))
#define NPU_REG_ACT_TABLE_F2                                    NPU_REG_ACT_TABLE_F2
#define NPU_REG_ACT_TABLE_F2_POS                                (16U)
#define NPU_REG_ACT_TABLE_F2_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F2_MSK                                (((1U<<NPU_REG_ACT_TABLE_F2_LEN)-1)<<NPU_REG_ACT_TABLE_F2_POS)
#define NPU_REG_ACT_TABLE_F2_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F2_LEN)-1)<<NPU_REG_ACT_TABLE_F2_POS))
#define NPU_REG_ACT_TABLE_F3                                    NPU_REG_ACT_TABLE_F3
#define NPU_REG_ACT_TABLE_F3_POS                                (24U)
#define NPU_REG_ACT_TABLE_F3_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F3_MSK                                (((1U<<NPU_REG_ACT_TABLE_F3_LEN)-1)<<NPU_REG_ACT_TABLE_F3_POS)
#define NPU_REG_ACT_TABLE_F3_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F3_LEN)-1)<<NPU_REG_ACT_TABLE_F3_POS))

/* 0x1F4 : BLAI_ACT_TABLE_f7_f4 */
#define NPU_BLAI_ACT_TABLE_F7_F4_OFFSET                         (0x1F4)
#define NPU_REG_ACT_TABLE_F4                                    NPU_REG_ACT_TABLE_F4
#define NPU_REG_ACT_TABLE_F4_POS                                (0U)
#define NPU_REG_ACT_TABLE_F4_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F4_MSK                                (((1U<<NPU_REG_ACT_TABLE_F4_LEN)-1)<<NPU_REG_ACT_TABLE_F4_POS)
#define NPU_REG_ACT_TABLE_F4_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F4_LEN)-1)<<NPU_REG_ACT_TABLE_F4_POS))
#define NPU_REG_ACT_TABLE_F5                                    NPU_REG_ACT_TABLE_F5
#define NPU_REG_ACT_TABLE_F5_POS                                (8U)
#define NPU_REG_ACT_TABLE_F5_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F5_MSK                                (((1U<<NPU_REG_ACT_TABLE_F5_LEN)-1)<<NPU_REG_ACT_TABLE_F5_POS)
#define NPU_REG_ACT_TABLE_F5_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F5_LEN)-1)<<NPU_REG_ACT_TABLE_F5_POS))
#define NPU_REG_ACT_TABLE_F6                                    NPU_REG_ACT_TABLE_F6
#define NPU_REG_ACT_TABLE_F6_POS                                (16U)
#define NPU_REG_ACT_TABLE_F6_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F6_MSK                                (((1U<<NPU_REG_ACT_TABLE_F6_LEN)-1)<<NPU_REG_ACT_TABLE_F6_POS)
#define NPU_REG_ACT_TABLE_F6_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F6_LEN)-1)<<NPU_REG_ACT_TABLE_F6_POS))
#define NPU_REG_ACT_TABLE_F7                                    NPU_REG_ACT_TABLE_F7
#define NPU_REG_ACT_TABLE_F7_POS                                (24U)
#define NPU_REG_ACT_TABLE_F7_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F7_MSK                                (((1U<<NPU_REG_ACT_TABLE_F7_LEN)-1)<<NPU_REG_ACT_TABLE_F7_POS)
#define NPU_REG_ACT_TABLE_F7_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F7_LEN)-1)<<NPU_REG_ACT_TABLE_F7_POS))

/* 0x1F8 : BLAI_ACT_TABLE_fB_f8 */
#define NPU_BLAI_ACT_TABLE_FB_F8_OFFSET                         (0x1F8)
#define NPU_REG_ACT_TABLE_F8                                    NPU_REG_ACT_TABLE_F8
#define NPU_REG_ACT_TABLE_F8_POS                                (0U)
#define NPU_REG_ACT_TABLE_F8_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F8_MSK                                (((1U<<NPU_REG_ACT_TABLE_F8_LEN)-1)<<NPU_REG_ACT_TABLE_F8_POS)
#define NPU_REG_ACT_TABLE_F8_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F8_LEN)-1)<<NPU_REG_ACT_TABLE_F8_POS))
#define NPU_REG_ACT_TABLE_F9                                    NPU_REG_ACT_TABLE_F9
#define NPU_REG_ACT_TABLE_F9_POS                                (8U)
#define NPU_REG_ACT_TABLE_F9_LEN                                (8U)
#define NPU_REG_ACT_TABLE_F9_MSK                                (((1U<<NPU_REG_ACT_TABLE_F9_LEN)-1)<<NPU_REG_ACT_TABLE_F9_POS)
#define NPU_REG_ACT_TABLE_F9_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_F9_LEN)-1)<<NPU_REG_ACT_TABLE_F9_POS))
#define NPU_REG_ACT_TABLE_FA                                    NPU_REG_ACT_TABLE_FA
#define NPU_REG_ACT_TABLE_FA_POS                                (16U)
#define NPU_REG_ACT_TABLE_FA_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FA_MSK                                (((1U<<NPU_REG_ACT_TABLE_FA_LEN)-1)<<NPU_REG_ACT_TABLE_FA_POS)
#define NPU_REG_ACT_TABLE_FA_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FA_LEN)-1)<<NPU_REG_ACT_TABLE_FA_POS))
#define NPU_REG_ACT_TABLE_FB                                    NPU_REG_ACT_TABLE_FB
#define NPU_REG_ACT_TABLE_FB_POS                                (24U)
#define NPU_REG_ACT_TABLE_FB_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FB_MSK                                (((1U<<NPU_REG_ACT_TABLE_FB_LEN)-1)<<NPU_REG_ACT_TABLE_FB_POS)
#define NPU_REG_ACT_TABLE_FB_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FB_LEN)-1)<<NPU_REG_ACT_TABLE_FB_POS))

/* 0x1FC : BLAI_ACT_TABLE_fF_fC */
#define NPU_BLAI_ACT_TABLE_FF_FC_OFFSET                         (0x1FC)
#define NPU_REG_ACT_TABLE_FC                                    NPU_REG_ACT_TABLE_FC
#define NPU_REG_ACT_TABLE_FC_POS                                (0U)
#define NPU_REG_ACT_TABLE_FC_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FC_MSK                                (((1U<<NPU_REG_ACT_TABLE_FC_LEN)-1)<<NPU_REG_ACT_TABLE_FC_POS)
#define NPU_REG_ACT_TABLE_FC_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FC_LEN)-1)<<NPU_REG_ACT_TABLE_FC_POS))
#define NPU_REG_ACT_TABLE_FD                                    NPU_REG_ACT_TABLE_FD
#define NPU_REG_ACT_TABLE_FD_POS                                (8U)
#define NPU_REG_ACT_TABLE_FD_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FD_MSK                                (((1U<<NPU_REG_ACT_TABLE_FD_LEN)-1)<<NPU_REG_ACT_TABLE_FD_POS)
#define NPU_REG_ACT_TABLE_FD_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FD_LEN)-1)<<NPU_REG_ACT_TABLE_FD_POS))
#define NPU_REG_ACT_TABLE_FE                                    NPU_REG_ACT_TABLE_FE
#define NPU_REG_ACT_TABLE_FE_POS                                (16U)
#define NPU_REG_ACT_TABLE_FE_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FE_MSK                                (((1U<<NPU_REG_ACT_TABLE_FE_LEN)-1)<<NPU_REG_ACT_TABLE_FE_POS)
#define NPU_REG_ACT_TABLE_FE_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FE_LEN)-1)<<NPU_REG_ACT_TABLE_FE_POS))
#define NPU_REG_ACT_TABLE_FF                                    NPU_REG_ACT_TABLE_FF
#define NPU_REG_ACT_TABLE_FF_POS                                (24U)
#define NPU_REG_ACT_TABLE_FF_LEN                                (8U)
#define NPU_REG_ACT_TABLE_FF_MSK                                (((1U<<NPU_REG_ACT_TABLE_FF_LEN)-1)<<NPU_REG_ACT_TABLE_FF_POS)
#define NPU_REG_ACT_TABLE_FF_UMSK                               (~(((1U<<NPU_REG_ACT_TABLE_FF_LEN)-1)<<NPU_REG_ACT_TABLE_FF_POS))


struct  npu_reg {
    /* 0x00 : BALI_GENERAL_CFG */
    union {
        struct {
            uint32_t reserved_0_7                   :  8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t reg_img_in_mode                :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_15                 :  6; /* [15:10],       rsvd,        0x0 */
            uint32_t reg_ftable_idx_base            :  6; /* [21:16],        r/w,        0x5 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_ftable_dat_base            :  6; /* [29:24],        r/w,        0x7 */
            uint32_t axi_w_idle                     :  1; /* [   30],          r,        0x0 */
            uint32_t axi_r_idle                     :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } BALI_GENERAL_CFG;

    /* 0x04 : BLAI_INT_CFG */
    union {
        struct {
            uint32_t reg_blai_start                 :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_blai_stop                  :  1; /* [    1],        w1p,        0x0 */
            uint32_t reg_blai_resume                :  1; /* [    2],        w1p,        0x0 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t reg_int_clr                    :  1; /* [    8],        w1p,        0x0 */
            uint32_t sts_blai_int                   :  1; /* [    9],          r,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } BLAI_INT_CFG;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[8];

    /* 0x10 : BLAI_WEIGHT_ADDR */
    union {
        struct {
            uint32_t reg_weig_addr_base             : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } BLAI_WEIGHT_ADDR;

    /* 0x14 : BLAI_BIAS_ADDR */
    union {
        struct {
            uint32_t reg_bias_addr_base             : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } BLAI_BIAS_ADDR;

    /* 0x18 : BLAI_INST_ADDR */
    union {
        struct {
            uint32_t reg_inst_addr_base             : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } BLAI_INST_ADDR;

    /* 0x1C : APU_DM0_ADDR */
    union {
        struct {
            uint32_t reg_img_addr_base              : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } APU_DM0_ADDR;

    /* 0x20 : APU_DM1_ADDR */
    union {
        struct {
            uint32_t reg_img_mem_seg                : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } APU_DM1_ADDR;

    /* 0x24 : BLAI_TF_CFG0 */
    union {
        struct {
            uint32_t reserved_0_30                  : 31; /* [30: 0],        r/w,        0x0 */
            uint32_t reg_tenflow_en                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } BLAI_TF_CFG0;

    /* 0x28  reserved */
    uint8_t RESERVED0x24[216];

    /* 0x100 : BLAI_ACT_TABLE00 */
    union {
        struct {
            uint32_t reg_act_table_00               :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_act_table_01               :  8; /* [15: 8],        r/w,       0xfb */
            uint32_t reg_act_table_02               :  8; /* [23:16],        r/w,       0xf7 */
            uint32_t reg_act_table_03               :  8; /* [31:24],        r/w,       0xf2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE00;

    /* 0x104 : BLAI_ACT_TABLE07_04 */
    union {
        struct {
            uint32_t reg_act_table_04               :  8; /* [ 7: 0],        r/w,       0xee */
            uint32_t reg_act_table_05               :  8; /* [15: 8],        r/w,       0xea */
            uint32_t reg_act_table_06               :  8; /* [23:16],        r/w,       0xe6 */
            uint32_t reg_act_table_07               :  8; /* [31:24],        r/w,       0xe2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE07_04;

    /* 0x108 : BLAI_ACT_TABLE0B_08 */
    union {
        struct {
            uint32_t reg_act_table_08               :  8; /* [ 7: 0],        r/w,       0xdf */
            uint32_t reg_act_table_09               :  8; /* [15: 8],        r/w,       0xdb */
            uint32_t reg_act_table_0a               :  8; /* [23:16],        r/w,       0xd8 */
            uint32_t reg_act_table_0b               :  8; /* [31:24],        r/w,       0xd5 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE0B_08;

    /* 0x10C : BLAI_ACT_TABLE0F_0C */
    union {
        struct {
            uint32_t reg_act_table_0c               :  8; /* [ 7: 0],        r/w,       0xd2 */
            uint32_t reg_act_table_0d               :  8; /* [15: 8],        r/w,       0xcf */
            uint32_t reg_act_table_0e               :  8; /* [23:16],        r/w,       0xcc */
            uint32_t reg_act_table_0f               :  8; /* [31:24],        r/w,       0xca */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE0F_0C;

    /* 0x110 : BLAI_ACT_TABLE13_10 */
    union {
        struct {
            uint32_t reg_act_table_10               :  8; /* [ 7: 0],        r/w,       0xc7 */
            uint32_t reg_act_table_11               :  8; /* [15: 8],        r/w,       0xc5 */
            uint32_t reg_act_table_12               :  8; /* [23:16],        r/w,       0xc3 */
            uint32_t reg_act_table_13               :  8; /* [31:24],        r/w,       0xc1 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE13_10;

    /* 0x114 : BLAI_ACT_TABLE17_14 */
    union {
        struct {
            uint32_t reg_act_table_14               :  8; /* [ 7: 0],        r/w,       0xbf */
            uint32_t reg_act_table_15               :  8; /* [15: 8],        r/w,       0xbe */
            uint32_t reg_act_table_16               :  8; /* [23:16],        r/w,       0xbc */
            uint32_t reg_act_table_17               :  8; /* [31:24],        r/w,       0xbb */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE17_14;

    /* 0x118 : BLAI_ACT_TABLE1B_18 */
    union {
        struct {
            uint32_t reg_act_table_18               :  8; /* [ 7: 0],        r/w,       0xb9 */
            uint32_t reg_act_table_19               :  8; /* [15: 8],        r/w,       0xb8 */
            uint32_t reg_act_table_1a               :  8; /* [23:16],        r/w,       0xb7 */
            uint32_t reg_act_table_1b               :  8; /* [31:24],        r/w,       0xb6 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE1B_18;

    /* 0x11C : BLAI_ACT_TABLE1F_1C */
    union {
        struct {
            uint32_t reg_act_table_1c               :  8; /* [ 7: 0],        r/w,       0xb5 */
            uint32_t reg_act_table_1d               :  8; /* [15: 8],        r/w,       0xb4 */
            uint32_t reg_act_table_1e               :  8; /* [23:16],        r/w,       0xb3 */
            uint32_t reg_act_table_1f               :  8; /* [31:24],        r/w,       0xb3 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE1F_1C;

    /* 0x120 : BLAI_ACT_TABLE_23_20 */
    union {
        struct {
            uint32_t reg_act_table_20               :  8; /* [ 7: 0],        r/w,       0xb2 */
            uint32_t reg_act_table_21               :  8; /* [15: 8],        r/w,       0xb2 */
            uint32_t reg_act_table_22               :  8; /* [23:16],        r/w,       0xb2 */
            uint32_t reg_act_table_23               :  8; /* [31:24],        r/w,       0xb1 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_23_20;

    /* 0x124 : BLAI_ACT_TABLE_27_24 */
    union {
        struct {
            uint32_t reg_act_table_24               :  8; /* [ 7: 0],        r/w,       0xb1 */
            uint32_t reg_act_table_25               :  8; /* [15: 8],        r/w,       0xb1 */
            uint32_t reg_act_table_26               :  8; /* [23:16],        r/w,       0xb1 */
            uint32_t reg_act_table_27               :  8; /* [31:24],        r/w,       0xb1 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_27_24;

    /* 0x128 : BLAI_ACT_TABLE_2B_28 */
    union {
        struct {
            uint32_t reg_act_table_28               :  8; /* [ 7: 0],        r/w,       0xb1 */
            uint32_t reg_act_table_29               :  8; /* [15: 8],        r/w,       0xb1 */
            uint32_t reg_act_table_2a               :  8; /* [23:16],        r/w,       0xb1 */
            uint32_t reg_act_table_2b               :  8; /* [31:24],        r/w,       0xb2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_2B_28;

    /* 0x12C : BLAI_ACT_TABLE_2F_2C */
    union {
        struct {
            uint32_t reg_act_table_2c               :  8; /* [ 7: 0],        r/w,       0xb2 */
            uint32_t reg_act_table_2d               :  8; /* [15: 8],        r/w,       0xb2 */
            uint32_t reg_act_table_2e               :  8; /* [23:16],        r/w,       0xb3 */
            uint32_t reg_act_table_2f               :  8; /* [31:24],        r/w,       0xb3 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_2F_2C;

    /* 0x130 : BLAI_ACT_TABLE_33_30 */
    union {
        struct {
            uint32_t reg_act_table_30               :  8; /* [ 7: 0],        r/w,       0xb4 */
            uint32_t reg_act_table_31               :  8; /* [15: 8],        r/w,       0xb4 */
            uint32_t reg_act_table_32               :  8; /* [23:16],        r/w,       0xb5 */
            uint32_t reg_act_table_33               :  8; /* [31:24],        r/w,       0xb5 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_33_30;

    /* 0x134 : BLAI_ACT_TABLE_37_34 */
    union {
        struct {
            uint32_t reg_act_table_34               :  8; /* [ 7: 0],        r/w,       0xb6 */
            uint32_t reg_act_table_35               :  8; /* [15: 8],        r/w,       0xb7 */
            uint32_t reg_act_table_36               :  8; /* [23:16],        r/w,       0xb7 */
            uint32_t reg_act_table_37               :  8; /* [31:24],        r/w,       0xb8 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_37_34;

    /* 0x138 : BLAI_ACT_TABLE_3B_38 */
    union {
        struct {
            uint32_t reg_act_table_38               :  8; /* [ 7: 0],        r/w,       0xb9 */
            uint32_t reg_act_table_39               :  8; /* [15: 8],        r/w,       0xba */
            uint32_t reg_act_table_3a               :  8; /* [23:16],        r/w,       0xba */
            uint32_t reg_act_table_3b               :  8; /* [31:24],        r/w,       0xbb */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_3B_38;

    /* 0x13C : BLAI_ACT_TABLE_3F_3C */
    union {
        struct {
            uint32_t reg_act_table_3c               :  8; /* [ 7: 0],        r/w,       0xbc */
            uint32_t reg_act_table_3d               :  8; /* [15: 8],        r/w,       0xbd */
            uint32_t reg_act_table_3e               :  8; /* [23:16],        r/w,       0xbe */
            uint32_t reg_act_table_3f               :  8; /* [31:24],        r/w,       0xbe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_3F_3C;

    /* 0x140 : BLAI_ACT_TABLE_43_40 */
    union {
        struct {
            uint32_t reg_act_table_40               :  8; /* [ 7: 0],        r/w,       0xbf */
            uint32_t reg_act_table_41               :  8; /* [15: 8],        r/w,       0xc0 */
            uint32_t reg_act_table_42               :  8; /* [23:16],        r/w,       0xc1 */
            uint32_t reg_act_table_43               :  8; /* [31:24],        r/w,       0xc2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_43_40;

    /* 0x144 : BLAI_ACT_TABLE_47_44 */
    union {
        struct {
            uint32_t reg_act_table_44               :  8; /* [ 7: 0],        r/w,       0xc3 */
            uint32_t reg_act_table_45               :  8; /* [15: 8],        r/w,       0xc4 */
            uint32_t reg_act_table_46               :  8; /* [23:16],        r/w,       0xc5 */
            uint32_t reg_act_table_47               :  8; /* [31:24],        r/w,       0xc6 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_47_44;

    /* 0x148 : BLAI_ACT_TABLE_4B_48 */
    union {
        struct {
            uint32_t reg_act_table_48               :  8; /* [ 7: 0],        r/w,       0xc6 */
            uint32_t reg_act_table_49               :  8; /* [15: 8],        r/w,       0xc7 */
            uint32_t reg_act_table_4a               :  8; /* [23:16],        r/w,       0xc8 */
            uint32_t reg_act_table_4b               :  8; /* [31:24],        r/w,       0xc9 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_4B_48;

    /* 0x14C : BLAI_ACT_TABLE_4F_4C */
    union {
        struct {
            uint32_t reg_act_table_4c               :  8; /* [ 7: 0],        r/w,       0xca */
            uint32_t reg_act_table_4d               :  8; /* [15: 8],        r/w,       0xcb */
            uint32_t reg_act_table_4e               :  8; /* [23:16],        r/w,       0xcc */
            uint32_t reg_act_table_4f               :  8; /* [31:24],        r/w,       0xcd */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_4F_4C;

    /* 0x150 : BLAI_ACT_TABLE_53_50 */
    union {
        struct {
            uint32_t reg_act_table_50               :  8; /* [ 7: 0],        r/w,       0xce */
            uint32_t reg_act_table_51               :  8; /* [15: 8],        r/w,       0xce */
            uint32_t reg_act_table_52               :  8; /* [23:16],        r/w,       0xcf */
            uint32_t reg_act_table_53               :  8; /* [31:24],        r/w,       0xd0 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_53_50;

    /* 0x154 : BLAI_ACT_TABLE_57_54 */
    union {
        struct {
            uint32_t reg_act_table_54               :  8; /* [ 7: 0],        r/w,       0xd1 */
            uint32_t reg_act_table_55               :  8; /* [15: 8],        r/w,       0xd2 */
            uint32_t reg_act_table_56               :  8; /* [23:16],        r/w,       0xd3 */
            uint32_t reg_act_table_57               :  8; /* [31:24],        r/w,       0xd4 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_57_54;

    /* 0x158 : BLAI_ACT_TABLE_5B_58 */
    union {
        struct {
            uint32_t reg_act_table_58               :  8; /* [ 7: 0],        r/w,       0xd4 */
            uint32_t reg_act_table_59               :  8; /* [15: 8],        r/w,       0xd5 */
            uint32_t reg_act_table_5a               :  8; /* [23:16],        r/w,       0xd6 */
            uint32_t reg_act_table_5b               :  8; /* [31:24],        r/w,       0xd7 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_5B_58;

    /* 0x15C : BLAI_ACT_TABLE_5F_5C */
    union {
        struct {
            uint32_t reg_act_table_5c               :  8; /* [ 7: 0],        r/w,       0xd8 */
            uint32_t reg_act_table_5d               :  8; /* [15: 8],        r/w,       0xd8 */
            uint32_t reg_act_table_5e               :  8; /* [23:16],        r/w,       0xd9 */
            uint32_t reg_act_table_5f               :  8; /* [31:24],        r/w,       0xda */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_5F_5C;

    /* 0x160 : BLAI_ACT_TABLE_63_60 */
    union {
        struct {
            uint32_t reg_act_table_60               :  8; /* [ 7: 0],        r/w,       0xdb */
            uint32_t reg_act_table_61               :  8; /* [15: 8],        r/w,       0xdb */
            uint32_t reg_act_table_62               :  8; /* [23:16],        r/w,       0xdc */
            uint32_t reg_act_table_63               :  8; /* [31:24],        r/w,       0xdd */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_63_60;

    /* 0x164 : BLAI_ACT_TABLE_67_64 */
    union {
        struct {
            uint32_t reg_act_table_64               :  8; /* [ 7: 0],        r/w,       0xde */
            uint32_t reg_act_table_65               :  8; /* [15: 8],        r/w,       0xde */
            uint32_t reg_act_table_66               :  8; /* [23:16],        r/w,       0xdf */
            uint32_t reg_act_table_67               :  8; /* [31:24],        r/w,       0xe0 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_67_64;

    /* 0x168 : BLAI_ACT_TABLE_6B_68 */
    union {
        struct {
            uint32_t reg_act_table_68               :  8; /* [ 7: 0],        r/w,       0xe0 */
            uint32_t reg_act_table_69               :  8; /* [15: 8],        r/w,       0xe1 */
            uint32_t reg_act_table_6a               :  8; /* [23:16],        r/w,       0xe2 */
            uint32_t reg_act_table_6b               :  8; /* [31:24],        r/w,       0xe2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_6B_68;

    /* 0x16C : BLAI_ACT_TABLE_6F_6C */
    union {
        struct {
            uint32_t reg_act_table_6c               :  8; /* [ 7: 0],        r/w,       0xe3 */
            uint32_t reg_act_table_6d               :  8; /* [15: 8],        r/w,       0xe4 */
            uint32_t reg_act_table_6e               :  8; /* [23:16],        r/w,       0xe4 */
            uint32_t reg_act_table_6f               :  8; /* [31:24],        r/w,       0xe5 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_6F_6C;

    /* 0x170 : BLAI_ACT_TABLE_73_70 */
    union {
        struct {
            uint32_t reg_act_table_70               :  8; /* [ 7: 0],        r/w,       0xe5 */
            uint32_t reg_act_table_71               :  8; /* [15: 8],        r/w,       0xe6 */
            uint32_t reg_act_table_72               :  8; /* [23:16],        r/w,       0xe6 */
            uint32_t reg_act_table_73               :  8; /* [31:24],        r/w,       0xe7 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_73_70;

    /* 0x174 : BLAI_ACT_TABLE_77_74 */
    union {
        struct {
            uint32_t reg_act_table_74               :  8; /* [ 7: 0],        r/w,       0xe8 */
            uint32_t reg_act_table_75               :  8; /* [15: 8],        r/w,       0xe8 */
            uint32_t reg_act_table_76               :  8; /* [23:16],        r/w,       0xe9 */
            uint32_t reg_act_table_77               :  8; /* [31:24],        r/w,       0xe9 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_77_74;

    /* 0x178 : BLAI_ACT_TABLE_7B_78 */
    union {
        struct {
            uint32_t reg_act_table_78               :  8; /* [ 7: 0],        r/w,       0xea */
            uint32_t reg_act_table_79               :  8; /* [15: 8],        r/w,       0xea */
            uint32_t reg_act_table_7a               :  8; /* [23:16],        r/w,       0xeb */
            uint32_t reg_act_table_7b               :  8; /* [31:24],        r/w,       0xeb */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_7B_78;

    /* 0x17C : BLAI_ACT_TABLE_7F_7C */
    union {
        struct {
            uint32_t reg_act_table_7c               :  8; /* [ 7: 0],        r/w,       0xec */
            uint32_t reg_act_table_7d               :  8; /* [15: 8],        r/w,       0xec */
            uint32_t reg_act_table_7e               :  8; /* [23:16],        r/w,       0xed */
            uint32_t reg_act_table_7f               :  8; /* [31:24],        r/w,       0xed */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_7F_7C;

    /* 0x180 : BLAI_ACT_TABLE_83_80 */
    union {
        struct {
            uint32_t reg_act_table_80               :  8; /* [ 7: 0],        r/w,       0xed */
            uint32_t reg_act_table_81               :  8; /* [15: 8],        r/w,       0xee */
            uint32_t reg_act_table_82               :  8; /* [23:16],        r/w,       0xee */
            uint32_t reg_act_table_83               :  8; /* [31:24],        r/w,       0xef */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_83_80;

    /* 0x184 : BLAI_ACT_TABLE_87_84 */
    union {
        struct {
            uint32_t reg_act_table_84               :  8; /* [ 7: 0],        r/w,       0xef */
            uint32_t reg_act_table_85               :  8; /* [15: 8],        r/w,       0xef */
            uint32_t reg_act_table_86               :  8; /* [23:16],        r/w,       0xf0 */
            uint32_t reg_act_table_87               :  8; /* [31:24],        r/w,       0xf0 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_87_84;

    /* 0x188 : BLAI_ACT_TABLE_8B_88 */
    union {
        struct {
            uint32_t reg_act_table_88               :  8; /* [ 7: 0],        r/w,       0xf1 */
            uint32_t reg_act_table_89               :  8; /* [15: 8],        r/w,       0xf1 */
            uint32_t reg_act_table_8a               :  8; /* [23:16],        r/w,       0xf1 */
            uint32_t reg_act_table_8b               :  8; /* [31:24],        r/w,       0xf2 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_8B_88;

    /* 0x18C : BLAI_ACT_TABLE_8F_8C */
    union {
        struct {
            uint32_t reg_act_table_8c               :  8; /* [ 7: 0],        r/w,       0xf2 */
            uint32_t reg_act_table_8d               :  8; /* [15: 8],        r/w,       0xf2 */
            uint32_t reg_act_table_8e               :  8; /* [23:16],        r/w,       0xf3 */
            uint32_t reg_act_table_8f               :  8; /* [31:24],        r/w,       0xf3 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_8F_8C;

    /* 0x190 : BLAI_ACT_TABLE_93_90 */
    union {
        struct {
            uint32_t reg_act_table_90               :  8; /* [ 7: 0],        r/w,       0xf3 */
            uint32_t reg_act_table_91               :  8; /* [15: 8],        r/w,       0xf4 */
            uint32_t reg_act_table_92               :  8; /* [23:16],        r/w,       0xf4 */
            uint32_t reg_act_table_93               :  8; /* [31:24],        r/w,       0xf4 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_93_90;

    /* 0x194 : BLAI_ACT_TABLE_97_94 */
    union {
        struct {
            uint32_t reg_act_table_94               :  8; /* [ 7: 0],        r/w,       0xf4 */
            uint32_t reg_act_table_95               :  8; /* [15: 8],        r/w,       0xf5 */
            uint32_t reg_act_table_96               :  8; /* [23:16],        r/w,       0xf5 */
            uint32_t reg_act_table_97               :  8; /* [31:24],        r/w,       0xf5 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_97_94;

    /* 0x198 : BLAI_ACT_TABLE_9B_98 */
    union {
        struct {
            uint32_t reg_act_table_98               :  8; /* [ 7: 0],        r/w,       0xf6 */
            uint32_t reg_act_table_99               :  8; /* [15: 8],        r/w,       0xf6 */
            uint32_t reg_act_table_9a               :  8; /* [23:16],        r/w,       0xf6 */
            uint32_t reg_act_table_9b               :  8; /* [31:24],        r/w,       0xf6 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_9B_98;

    /* 0x19C : BLAI_ACT_TABLE_9F_9C */
    union {
        struct {
            uint32_t reg_act_table_9c               :  8; /* [ 7: 0],        r/w,       0xf7 */
            uint32_t reg_act_table_9d               :  8; /* [15: 8],        r/w,       0xf7 */
            uint32_t reg_act_table_9e               :  8; /* [23:16],        r/w,       0xf7 */
            uint32_t reg_act_table_9f               :  8; /* [31:24],        r/w,       0xf7 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_9F_9C;

    /* 0x1A0 : BLAI_ACT_TABLE_a3_a0 */
    union {
        struct {
            uint32_t reg_act_table_a0               :  8; /* [ 7: 0],        r/w,       0xf7 */
            uint32_t reg_act_table_a1               :  8; /* [15: 8],        r/w,       0xf8 */
            uint32_t reg_act_table_a2               :  8; /* [23:16],        r/w,       0xf8 */
            uint32_t reg_act_table_a3               :  8; /* [31:24],        r/w,       0xf8 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_a3_a0;

    /* 0x1A4 : BLAI_ACT_TABLE_a7_a4 */
    union {
        struct {
            uint32_t reg_act_table_a4               :  8; /* [ 7: 0],        r/w,       0xf8 */
            uint32_t reg_act_table_a5               :  8; /* [15: 8],        r/w,       0xf8 */
            uint32_t reg_act_table_a6               :  8; /* [23:16],        r/w,       0xf9 */
            uint32_t reg_act_table_a7               :  8; /* [31:24],        r/w,       0xf9 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_a7_a4;

    /* 0x1A8 : BLAI_ACT_TABLE_aB_a8 */
    union {
        struct {
            uint32_t reg_act_table_a8               :  8; /* [ 7: 0],        r/w,       0xf9 */
            uint32_t reg_act_table_a9               :  8; /* [15: 8],        r/w,       0xf9 */
            uint32_t reg_act_table_aa               :  8; /* [23:16],        r/w,       0xf9 */
            uint32_t reg_act_table_ab               :  8; /* [31:24],        r/w,       0xf9 */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_aB_a8;

    /* 0x1AC : BLAI_ACT_TABLE_aF_aC */
    union {
        struct {
            uint32_t reg_act_table_ac               :  8; /* [ 7: 0],        r/w,       0xfa */
            uint32_t reg_act_table_ad               :  8; /* [15: 8],        r/w,       0xfa */
            uint32_t reg_act_table_ae               :  8; /* [23:16],        r/w,       0xfa */
            uint32_t reg_act_table_af               :  8; /* [31:24],        r/w,       0xfa */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_aF_aC;

    /* 0x1B0 : BLAI_ACT_TABLE_b3_b0 */
    union {
        struct {
            uint32_t reg_act_table_b0               :  8; /* [ 7: 0],        r/w,       0xfa */
            uint32_t reg_act_table_b1               :  8; /* [15: 8],        r/w,       0xfa */
            uint32_t reg_act_table_b2               :  8; /* [23:16],        r/w,       0xfb */
            uint32_t reg_act_table_b3               :  8; /* [31:24],        r/w,       0xfb */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_b3_b0;

    /* 0x1B4 : BLAI_ACT_TABLE_b7_b4 */
    union {
        struct {
            uint32_t reg_act_table_b4               :  8; /* [ 7: 0],        r/w,       0xfb */
            uint32_t reg_act_table_b5               :  8; /* [15: 8],        r/w,       0xfb */
            uint32_t reg_act_table_b6               :  8; /* [23:16],        r/w,       0xfb */
            uint32_t reg_act_table_b7               :  8; /* [31:24],        r/w,       0xfb */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_b7_b4;

    /* 0x1B8 : BLAI_ACT_TABLE_bB_b8 */
    union {
        struct {
            uint32_t reg_act_table_b8               :  8; /* [ 7: 0],        r/w,       0xfb */
            uint32_t reg_act_table_b9               :  8; /* [15: 8],        r/w,       0xfb */
            uint32_t reg_act_table_ba               :  8; /* [23:16],        r/w,       0xfc */
            uint32_t reg_act_table_bb               :  8; /* [31:24],        r/w,       0xfc */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_bB_b8;

    /* 0x1BC : BLAI_ACT_TABLE_bF_bC */
    union {
        struct {
            uint32_t reg_act_table_bc               :  8; /* [ 7: 0],        r/w,       0xfc */
            uint32_t reg_act_table_bd               :  8; /* [15: 8],        r/w,       0xfc */
            uint32_t reg_act_table_be               :  8; /* [23:16],        r/w,       0xfc */
            uint32_t reg_act_table_bf               :  8; /* [31:24],        r/w,       0xfc */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_bF_bC;

    /* 0x1C0 : BLAI_ACT_TABLE_c3_c0 */
    union {
        struct {
            uint32_t reg_act_table_c0               :  8; /* [ 7: 0],        r/w,       0xfc */
            uint32_t reg_act_table_c1               :  8; /* [15: 8],        r/w,       0xfc */
            uint32_t reg_act_table_c2               :  8; /* [23:16],        r/w,       0xfc */
            uint32_t reg_act_table_c3               :  8; /* [31:24],        r/w,       0xfc */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_c3_c0;

    /* 0x1C4 : BLAI_ACT_TABLE_c7_c4 */
    union {
        struct {
            uint32_t reg_act_table_c4               :  8; /* [ 7: 0],        r/w,       0xfd */
            uint32_t reg_act_table_c5               :  8; /* [15: 8],        r/w,       0xfd */
            uint32_t reg_act_table_c6               :  8; /* [23:16],        r/w,       0xfd */
            uint32_t reg_act_table_c7               :  8; /* [31:24],        r/w,       0xfd */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_c7_c4;

    /* 0x1C8 : BLAI_ACT_TABLE_cB_c8 */
    union {
        struct {
            uint32_t reg_act_table_c8               :  8; /* [ 7: 0],        r/w,       0xfd */
            uint32_t reg_act_table_c9               :  8; /* [15: 8],        r/w,       0xfd */
            uint32_t reg_act_table_ca               :  8; /* [23:16],        r/w,       0xfd */
            uint32_t reg_act_table_cb               :  8; /* [31:24],        r/w,       0xfd */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_cB_c8;

    /* 0x1CC : BLAI_ACT_TABLE_cF_cC */
    union {
        struct {
            uint32_t reg_act_table_cc               :  8; /* [ 7: 0],        r/w,       0xfd */
            uint32_t reg_act_table_cd               :  8; /* [15: 8],        r/w,       0xfd */
            uint32_t reg_act_table_ce               :  8; /* [23:16],        r/w,       0xfd */
            uint32_t reg_act_table_cf               :  8; /* [31:24],        r/w,       0xfd */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_cF_cC;

    /* 0x1D0 : BLAI_ACT_TABLE_d3_d0 */
    union {
        struct {
            uint32_t reg_act_table_d0               :  8; /* [ 7: 0],        r/w,       0xfe */
            uint32_t reg_act_table_d1               :  8; /* [15: 8],        r/w,       0xfe */
            uint32_t reg_act_table_d2               :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_act_table_d3               :  8; /* [31:24],        r/w,       0xfe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_d3_d0;

    /* 0x1D4 : BLAI_ACT_TABLE_d7_d4 */
    union {
        struct {
            uint32_t reg_act_table_d4               :  8; /* [ 7: 0],        r/w,       0xfe */
            uint32_t reg_act_table_d5               :  8; /* [15: 8],        r/w,       0xfe */
            uint32_t reg_act_table_d6               :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_act_table_d7               :  8; /* [31:24],        r/w,       0xfe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_d7_d4;

    /* 0x1D8 : BLAI_ACT_TABLE_dB_d8 */
    union {
        struct {
            uint32_t reg_act_table_d8               :  8; /* [ 7: 0],        r/w,       0xfe */
            uint32_t reg_act_table_d9               :  8; /* [15: 8],        r/w,       0xfe */
            uint32_t reg_act_table_da               :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_act_table_db               :  8; /* [31:24],        r/w,       0xfe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_dB_d8;

    /* 0x1DC : BLAI_ACT_TABLE_dF_dC */
    union {
        struct {
            uint32_t reg_act_table_dc               :  8; /* [ 7: 0],        r/w,       0xfe */
            uint32_t reg_act_table_dd               :  8; /* [15: 8],        r/w,       0xfe */
            uint32_t reg_act_table_de               :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_act_table_df               :  8; /* [31:24],        r/w,       0xfe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_dF_dC;

    /* 0x1E0 : BLAI_ACT_TABLE_e3_e0 */
    union {
        struct {
            uint32_t reg_act_table_e0               :  8; /* [ 7: 0],        r/w,       0xfe */
            uint32_t reg_act_table_e1               :  8; /* [15: 8],        r/w,       0xfe */
            uint32_t reg_act_table_e2               :  8; /* [23:16],        r/w,       0xfe */
            uint32_t reg_act_table_e3               :  8; /* [31:24],        r/w,       0xfe */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_e3_e0;

    /* 0x1E4 : BLAI_ACT_TABLE_e7_e4 */
    union {
        struct {
            uint32_t reg_act_table_e4               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_e5               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_e6               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_e7               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_e7_e4;

    /* 0x1E8 : BLAI_ACT_TABLE_eB_e8 */
    union {
        struct {
            uint32_t reg_act_table_e8               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_e9               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_ea               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_eb               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_eB_e8;

    /* 0x1EC : BLAI_ACT_TABLE_eF_eC */
    union {
        struct {
            uint32_t reg_act_table_ec               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_ed               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_ee               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_ef               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_eF_eC;

    /* 0x1F0 : BLAI_ACT_TABLE_f3_f0 */
    union {
        struct {
            uint32_t reg_act_table_f0               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_f1               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_f2               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_f3               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_f3_f0;

    /* 0x1F4 : BLAI_ACT_TABLE_f7_f4 */
    union {
        struct {
            uint32_t reg_act_table_f4               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_f5               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_f6               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_f7               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_f7_f4;

    /* 0x1F8 : BLAI_ACT_TABLE_fB_f8 */
    union {
        struct {
            uint32_t reg_act_table_f8               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_f9               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_fa               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_fb               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_fB_f8;

    /* 0x1FC : BLAI_ACT_TABLE_fF_fC */
    union {
        struct {
            uint32_t reg_act_table_fc               :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reg_act_table_fd               :  8; /* [15: 8],        r/w,       0xff */
            uint32_t reg_act_table_fe               :  8; /* [23:16],        r/w,       0xff */
            uint32_t reg_act_table_ff               :  8; /* [31:24],        r/w,       0xff */
        }BF;
        uint32_t WORD;
    } BLAI_ACT_TABLE_fF_fC;

};

typedef volatile struct npu_reg npu_reg_t;


#endif  /* __NPU_REG_H__ */
