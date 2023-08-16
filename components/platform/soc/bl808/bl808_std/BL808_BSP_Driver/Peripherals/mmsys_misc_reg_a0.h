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

/* 0x20 : peri_apb_ctrl */
#define MMSYS_MISC_PERI_APB_CTRL_OFFSET                         (0x20)
#define MMSYS_MISC_RG_PCLK_FORCE_ON                             MMSYS_MISC_RG_PCLK_FORCE_ON
#define MMSYS_MISC_RG_PCLK_FORCE_ON_POS                         (0U)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_LEN                         (16U)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_MSK                         (((1U<<MMSYS_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MMSYS_MISC_RG_PCLK_FORCE_ON_POS)
#define MMSYS_MISC_RG_PCLK_FORCE_ON_UMSK                        (~(((1U<<MMSYS_MISC_RG_PCLK_FORCE_ON_LEN)-1)<<MMSYS_MISC_RG_PCLK_FORCE_ON_POS))

/* 0x24 : mm_infra_ctrl */
#define MMSYS_MISC_MM_INFRA_CTRL_OFFSET                         (0x24)
#define MMSYS_MISC_REG_M42EMI_ADDR_BANK                         MMSYS_MISC_REG_M42EMI_ADDR_BANK
#define MMSYS_MISC_REG_M42EMI_ADDR_BANK_POS                     (0U)
#define MMSYS_MISC_REG_M42EMI_ADDR_BANK_LEN                     (2U)
#define MMSYS_MISC_REG_M42EMI_ADDR_BANK_MSK                     (((1U<<MMSYS_MISC_REG_M42EMI_ADDR_BANK_LEN)-1)<<MMSYS_MISC_REG_M42EMI_ADDR_BANK_POS)
#define MMSYS_MISC_REG_M42EMI_ADDR_BANK_UMSK                    (~(((1U<<MMSYS_MISC_REG_M42EMI_ADDR_BANK_LEN)-1)<<MMSYS_MISC_REG_M42EMI_ADDR_BANK_POS))
#define MMSYS_MISC_REG_M42EMI_W_THRE                            MMSYS_MISC_REG_M42EMI_W_THRE
#define MMSYS_MISC_REG_M42EMI_W_THRE_POS                        (4U)
#define MMSYS_MISC_REG_M42EMI_W_THRE_LEN                        (3U)
#define MMSYS_MISC_REG_M42EMI_W_THRE_MSK                        (((1U<<MMSYS_MISC_REG_M42EMI_W_THRE_LEN)-1)<<MMSYS_MISC_REG_M42EMI_W_THRE_POS)
#define MMSYS_MISC_REG_M42EMI_W_THRE_UMSK                       (~(((1U<<MMSYS_MISC_REG_M42EMI_W_THRE_LEN)-1)<<MMSYS_MISC_REG_M42EMI_W_THRE_POS))
#define MMSYS_MISC_REG_REG2MEM_W_THRE                           MMSYS_MISC_REG_REG2MEM_W_THRE
#define MMSYS_MISC_REG_REG2MEM_W_THRE_POS                       (16U)
#define MMSYS_MISC_REG_REG2MEM_W_THRE_LEN                       (3U)
#define MMSYS_MISC_REG_REG2MEM_W_THRE_MSK                       (((1U<<MMSYS_MISC_REG_REG2MEM_W_THRE_LEN)-1)<<MMSYS_MISC_REG_REG2MEM_W_THRE_POS)
#define MMSYS_MISC_REG_REG2MEM_W_THRE_UMSK                      (~(((1U<<MMSYS_MISC_REG_REG2MEM_W_THRE_LEN)-1)<<MMSYS_MISC_REG_REG2MEM_W_THRE_POS))

/* 0x28 : emi_infra_ctrl */
#define MMSYS_MISC_EMI_INFRA_CTRL_OFFSET                        (0x28)
#define MMSYS_MISC_REG_CPU2EMI_W_THRE                           MMSYS_MISC_REG_CPU2EMI_W_THRE
#define MMSYS_MISC_REG_CPU2EMI_W_THRE_POS                       (0U)
#define MMSYS_MISC_REG_CPU2EMI_W_THRE_LEN                       (3U)
#define MMSYS_MISC_REG_CPU2EMI_W_THRE_MSK                       (((1U<<MMSYS_MISC_REG_CPU2EMI_W_THRE_LEN)-1)<<MMSYS_MISC_REG_CPU2EMI_W_THRE_POS)
#define MMSYS_MISC_REG_CPU2EMI_W_THRE_UMSK                      (~(((1U<<MMSYS_MISC_REG_CPU2EMI_W_THRE_LEN)-1)<<MMSYS_MISC_REG_CPU2EMI_W_THRE_POS))
#define MMSYS_MISC_REG_MM2EMIA_W_THRE                           MMSYS_MISC_REG_MM2EMIA_W_THRE
#define MMSYS_MISC_REG_MM2EMIA_W_THRE_POS                       (4U)
#define MMSYS_MISC_REG_MM2EMIA_W_THRE_LEN                       (3U)
#define MMSYS_MISC_REG_MM2EMIA_W_THRE_MSK                       (((1U<<MMSYS_MISC_REG_MM2EMIA_W_THRE_LEN)-1)<<MMSYS_MISC_REG_MM2EMIA_W_THRE_POS)
#define MMSYS_MISC_REG_MM2EMIA_W_THRE_UMSK                      (~(((1U<<MMSYS_MISC_REG_MM2EMIA_W_THRE_LEN)-1)<<MMSYS_MISC_REG_MM2EMIA_W_THRE_POS))
#define MMSYS_MISC_REG_MM2EMIB_W_THRE                           MMSYS_MISC_REG_MM2EMIB_W_THRE
#define MMSYS_MISC_REG_MM2EMIB_W_THRE_POS                       (8U)
#define MMSYS_MISC_REG_MM2EMIB_W_THRE_LEN                       (3U)
#define MMSYS_MISC_REG_MM2EMIB_W_THRE_MSK                       (((1U<<MMSYS_MISC_REG_MM2EMIB_W_THRE_LEN)-1)<<MMSYS_MISC_REG_MM2EMIB_W_THRE_POS)
#define MMSYS_MISC_REG_MM2EMIB_W_THRE_UMSK                      (~(((1U<<MMSYS_MISC_REG_MM2EMIB_W_THRE_LEN)-1)<<MMSYS_MISC_REG_MM2EMIB_W_THRE_POS))

/* 0x2C : mm_infra_qos_ctrl */
#define MMSYS_MISC_MM_INFRA_QOS_CTRL_OFFSET                     (0x2C)
#define MMSYS_MISC_REG_M4ID2EMI_AWQOS                           MMSYS_MISC_REG_M4ID2EMI_AWQOS
#define MMSYS_MISC_REG_M4ID2EMI_AWQOS_POS                       (0U)
#define MMSYS_MISC_REG_M4ID2EMI_AWQOS_LEN                       (1U)
#define MMSYS_MISC_REG_M4ID2EMI_AWQOS_MSK                       (((1U<<MMSYS_MISC_REG_M4ID2EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG_M4ID2EMI_AWQOS_POS)
#define MMSYS_MISC_REG_M4ID2EMI_AWQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_M4ID2EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG_M4ID2EMI_AWQOS_POS))
#define MMSYS_MISC_REG_M4ID2EMI_ARQOS                           MMSYS_MISC_REG_M4ID2EMI_ARQOS
#define MMSYS_MISC_REG_M4ID2EMI_ARQOS_POS                       (1U)
#define MMSYS_MISC_REG_M4ID2EMI_ARQOS_LEN                       (1U)
#define MMSYS_MISC_REG_M4ID2EMI_ARQOS_MSK                       (((1U<<MMSYS_MISC_REG_M4ID2EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_M4ID2EMI_ARQOS_POS)
#define MMSYS_MISC_REG_M4ID2EMI_ARQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_M4ID2EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_M4ID2EMI_ARQOS_POS))
#define MMSYS_MISC_REG_A52VRAM_AWQOS                            MMSYS_MISC_REG_A52VRAM_AWQOS
#define MMSYS_MISC_REG_A52VRAM_AWQOS_POS                        (2U)
#define MMSYS_MISC_REG_A52VRAM_AWQOS_LEN                        (1U)
#define MMSYS_MISC_REG_A52VRAM_AWQOS_MSK                        (((1U<<MMSYS_MISC_REG_A52VRAM_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A52VRAM_AWQOS_POS)
#define MMSYS_MISC_REG_A52VRAM_AWQOS_UMSK                       (~(((1U<<MMSYS_MISC_REG_A52VRAM_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A52VRAM_AWQOS_POS))
#define MMSYS_MISC_REG_A52VRAM_ARQOS                            MMSYS_MISC_REG_A52VRAM_ARQOS
#define MMSYS_MISC_REG_A52VRAM_ARQOS_POS                        (3U)
#define MMSYS_MISC_REG_A52VRAM_ARQOS_LEN                        (1U)
#define MMSYS_MISC_REG_A52VRAM_ARQOS_MSK                        (((1U<<MMSYS_MISC_REG_A52VRAM_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A52VRAM_ARQOS_POS)
#define MMSYS_MISC_REG_A52VRAM_ARQOS_UMSK                       (~(((1U<<MMSYS_MISC_REG_A52VRAM_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A52VRAM_ARQOS_POS))
#define MMSYS_MISC_REG_A52EMI_AWQOS                             MMSYS_MISC_REG_A52EMI_AWQOS
#define MMSYS_MISC_REG_A52EMI_AWQOS_POS                         (4U)
#define MMSYS_MISC_REG_A52EMI_AWQOS_LEN                         (1U)
#define MMSYS_MISC_REG_A52EMI_AWQOS_MSK                         (((1U<<MMSYS_MISC_REG_A52EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A52EMI_AWQOS_POS)
#define MMSYS_MISC_REG_A52EMI_AWQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_A52EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG_A52EMI_AWQOS_POS))
#define MMSYS_MISC_REG_A52EMI_ARQOS                             MMSYS_MISC_REG_A52EMI_ARQOS
#define MMSYS_MISC_REG_A52EMI_ARQOS_POS                         (5U)
#define MMSYS_MISC_REG_A52EMI_ARQOS_LEN                         (1U)
#define MMSYS_MISC_REG_A52EMI_ARQOS_MSK                         (((1U<<MMSYS_MISC_REG_A52EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A52EMI_ARQOS_POS)
#define MMSYS_MISC_REG_A52EMI_ARQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_A52EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_A52EMI_ARQOS_POS))
#define MMSYS_MISC_REG_E74MEM_AWQOS                             MMSYS_MISC_REG_E74MEM_AWQOS
#define MMSYS_MISC_REG_E74MEM_AWQOS_POS                         (6U)
#define MMSYS_MISC_REG_E74MEM_AWQOS_LEN                         (1U)
#define MMSYS_MISC_REG_E74MEM_AWQOS_MSK                         (((1U<<MMSYS_MISC_REG_E74MEM_AWQOS_LEN)-1)<<MMSYS_MISC_REG_E74MEM_AWQOS_POS)
#define MMSYS_MISC_REG_E74MEM_AWQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_E74MEM_AWQOS_LEN)-1)<<MMSYS_MISC_REG_E74MEM_AWQOS_POS))
#define MMSYS_MISC_REG_E74MEM_ARQOS                             MMSYS_MISC_REG_E74MEM_ARQOS
#define MMSYS_MISC_REG_E74MEM_ARQOS_POS                         (7U)
#define MMSYS_MISC_REG_E74MEM_ARQOS_LEN                         (1U)
#define MMSYS_MISC_REG_E74MEM_ARQOS_MSK                         (((1U<<MMSYS_MISC_REG_E74MEM_ARQOS_LEN)-1)<<MMSYS_MISC_REG_E74MEM_ARQOS_POS)
#define MMSYS_MISC_REG_E74MEM_ARQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_E74MEM_ARQOS_LEN)-1)<<MMSYS_MISC_REG_E74MEM_ARQOS_POS))
#define MMSYS_MISC_REG_E74SYS_AWQOS                             MMSYS_MISC_REG_E74SYS_AWQOS
#define MMSYS_MISC_REG_E74SYS_AWQOS_POS                         (8U)
#define MMSYS_MISC_REG_E74SYS_AWQOS_LEN                         (1U)
#define MMSYS_MISC_REG_E74SYS_AWQOS_MSK                         (((1U<<MMSYS_MISC_REG_E74SYS_AWQOS_LEN)-1)<<MMSYS_MISC_REG_E74SYS_AWQOS_POS)
#define MMSYS_MISC_REG_E74SYS_AWQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_E74SYS_AWQOS_LEN)-1)<<MMSYS_MISC_REG_E74SYS_AWQOS_POS))
#define MMSYS_MISC_REG_E74SYS_ARQOS                             MMSYS_MISC_REG_E74SYS_ARQOS
#define MMSYS_MISC_REG_E74SYS_ARQOS_POS                         (9U)
#define MMSYS_MISC_REG_E74SYS_ARQOS_LEN                         (1U)
#define MMSYS_MISC_REG_E74SYS_ARQOS_MSK                         (((1U<<MMSYS_MISC_REG_E74SYS_ARQOS_LEN)-1)<<MMSYS_MISC_REG_E74SYS_ARQOS_POS)
#define MMSYS_MISC_REG_E74SYS_ARQOS_UMSK                        (~(((1U<<MMSYS_MISC_REG_E74SYS_ARQOS_LEN)-1)<<MMSYS_MISC_REG_E74SYS_ARQOS_POS))
#define MMSYS_MISC_REG2EMI_AWQOS                                MMSYS_MISC_REG2EMI_AWQOS
#define MMSYS_MISC_REG2EMI_AWQOS_POS                            (10U)
#define MMSYS_MISC_REG2EMI_AWQOS_LEN                            (1U)
#define MMSYS_MISC_REG2EMI_AWQOS_MSK                            (((1U<<MMSYS_MISC_REG2EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG2EMI_AWQOS_POS)
#define MMSYS_MISC_REG2EMI_AWQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG2EMI_AWQOS_LEN)-1)<<MMSYS_MISC_REG2EMI_AWQOS_POS))
#define MMSYS_MISC_REG2EMI_ARQOS                                MMSYS_MISC_REG2EMI_ARQOS
#define MMSYS_MISC_REG2EMI_ARQOS_POS                            (11U)
#define MMSYS_MISC_REG2EMI_ARQOS_LEN                            (1U)
#define MMSYS_MISC_REG2EMI_ARQOS_MSK                            (((1U<<MMSYS_MISC_REG2EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG2EMI_ARQOS_POS)
#define MMSYS_MISC_REG2EMI_ARQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG2EMI_ARQOS_LEN)-1)<<MMSYS_MISC_REG2EMI_ARQOS_POS))
#define MMSYS_MISC_REG2VRAM_AWQOS                               MMSYS_MISC_REG2VRAM_AWQOS
#define MMSYS_MISC_REG2VRAM_AWQOS_POS                           (12U)
#define MMSYS_MISC_REG2VRAM_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG2VRAM_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG2VRAM_AWQOS_LEN)-1)<<MMSYS_MISC_REG2VRAM_AWQOS_POS)
#define MMSYS_MISC_REG2VRAM_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG2VRAM_AWQOS_LEN)-1)<<MMSYS_MISC_REG2VRAM_AWQOS_POS))
#define MMSYS_MISC_REG2VRAM_ARQOS                               MMSYS_MISC_REG2VRAM_ARQOS
#define MMSYS_MISC_REG2VRAM_ARQOS_POS                           (13U)
#define MMSYS_MISC_REG2VRAM_ARQOS_LEN                           (1U)
#define MMSYS_MISC_REG2VRAM_ARQOS_MSK                           (((1U<<MMSYS_MISC_REG2VRAM_ARQOS_LEN)-1)<<MMSYS_MISC_REG2VRAM_ARQOS_POS)
#define MMSYS_MISC_REG2VRAM_ARQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG2VRAM_ARQOS_LEN)-1)<<MMSYS_MISC_REG2VRAM_ARQOS_POS))
#define MMSYS_MISC_REG_NR3D_AWQOS                               MMSYS_MISC_REG_NR3D_AWQOS
#define MMSYS_MISC_REG_NR3D_AWQOS_POS                           (14U)
#define MMSYS_MISC_REG_NR3D_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_NR3D_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_NR3D_AWQOS_LEN)-1)<<MMSYS_MISC_REG_NR3D_AWQOS_POS)
#define MMSYS_MISC_REG_NR3D_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_NR3D_AWQOS_LEN)-1)<<MMSYS_MISC_REG_NR3D_AWQOS_POS))
#define MMSYS_MISC_REG_NR3D_ARQOS                               MMSYS_MISC_REG_NR3D_ARQOS
#define MMSYS_MISC_REG_NR3D_ARQOS_POS                           (15U)
#define MMSYS_MISC_REG_NR3D_ARQOS_LEN                           (1U)
#define MMSYS_MISC_REG_NR3D_ARQOS_MSK                           (((1U<<MMSYS_MISC_REG_NR3D_ARQOS_LEN)-1)<<MMSYS_MISC_REG_NR3D_ARQOS_POS)
#define MMSYS_MISC_REG_NR3D_ARQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_NR3D_ARQOS_LEN)-1)<<MMSYS_MISC_REG_NR3D_ARQOS_POS))
#define MMSYS_MISC_REG_SDH_AWQOS                                MMSYS_MISC_REG_SDH_AWQOS
#define MMSYS_MISC_REG_SDH_AWQOS_POS                            (16U)
#define MMSYS_MISC_REG_SDH_AWQOS_LEN                            (1U)
#define MMSYS_MISC_REG_SDH_AWQOS_MSK                            (((1U<<MMSYS_MISC_REG_SDH_AWQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_AWQOS_POS)
#define MMSYS_MISC_REG_SDH_AWQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_SDH_AWQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_AWQOS_POS))
#define MMSYS_MISC_REG_SDH_ARQOS                                MMSYS_MISC_REG_SDH_ARQOS
#define MMSYS_MISC_REG_SDH_ARQOS_POS                            (17U)
#define MMSYS_MISC_REG_SDH_ARQOS_LEN                            (1U)
#define MMSYS_MISC_REG_SDH_ARQOS_MSK                            (((1U<<MMSYS_MISC_REG_SDH_ARQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_ARQOS_POS)
#define MMSYS_MISC_REG_SDH_ARQOS_UMSK                           (~(((1U<<MMSYS_MISC_REG_SDH_ARQOS_LEN)-1)<<MMSYS_MISC_REG_SDH_ARQOS_POS))
#define MMSYS_MISC_REG_CODEC_FO_AWQOS                           MMSYS_MISC_REG_CODEC_FO_AWQOS
#define MMSYS_MISC_REG_CODEC_FO_AWQOS_POS                       (18U)
#define MMSYS_MISC_REG_CODEC_FO_AWQOS_LEN                       (1U)
#define MMSYS_MISC_REG_CODEC_FO_AWQOS_MSK                       (((1U<<MMSYS_MISC_REG_CODEC_FO_AWQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FO_AWQOS_POS)
#define MMSYS_MISC_REG_CODEC_FO_AWQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_CODEC_FO_AWQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FO_AWQOS_POS))
#define MMSYS_MISC_REG_CODEC_FI_ARQOS                           MMSYS_MISC_REG_CODEC_FI_ARQOS
#define MMSYS_MISC_REG_CODEC_FI_ARQOS_POS                       (19U)
#define MMSYS_MISC_REG_CODEC_FI_ARQOS_LEN                       (1U)
#define MMSYS_MISC_REG_CODEC_FI_ARQOS_MSK                       (((1U<<MMSYS_MISC_REG_CODEC_FI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FI_ARQOS_POS)
#define MMSYS_MISC_REG_CODEC_FI_ARQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_CODEC_FI_ARQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FI_ARQOS_POS))
#define MMSYS_MISC_REG_CODEC_FO2_AWQOS                          MMSYS_MISC_REG_CODEC_FO2_AWQOS
#define MMSYS_MISC_REG_CODEC_FO2_AWQOS_POS                      (20U)
#define MMSYS_MISC_REG_CODEC_FO2_AWQOS_LEN                      (1U)
#define MMSYS_MISC_REG_CODEC_FO2_AWQOS_MSK                      (((1U<<MMSYS_MISC_REG_CODEC_FO2_AWQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FO2_AWQOS_POS)
#define MMSYS_MISC_REG_CODEC_FO2_AWQOS_UMSK                     (~(((1U<<MMSYS_MISC_REG_CODEC_FO2_AWQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FO2_AWQOS_POS))
#define MMSYS_MISC_REG_CODEC_FI2_ARQOS                          MMSYS_MISC_REG_CODEC_FI2_ARQOS
#define MMSYS_MISC_REG_CODEC_FI2_ARQOS_POS                      (21U)
#define MMSYS_MISC_REG_CODEC_FI2_ARQOS_LEN                      (1U)
#define MMSYS_MISC_REG_CODEC_FI2_ARQOS_MSK                      (((1U<<MMSYS_MISC_REG_CODEC_FI2_ARQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FI2_ARQOS_POS)
#define MMSYS_MISC_REG_CODEC_FI2_ARQOS_UMSK                     (~(((1U<<MMSYS_MISC_REG_CODEC_FI2_ARQOS_LEN)-1)<<MMSYS_MISC_REG_CODEC_FI2_ARQOS_POS))
#define MMSYS_MISC_REG_H264_REF_AWQOS                           MMSYS_MISC_REG_H264_REF_AWQOS
#define MMSYS_MISC_REG_H264_REF_AWQOS_POS                       (22U)
#define MMSYS_MISC_REG_H264_REF_AWQOS_LEN                       (1U)
#define MMSYS_MISC_REG_H264_REF_AWQOS_MSK                       (((1U<<MMSYS_MISC_REG_H264_REF_AWQOS_LEN)-1)<<MMSYS_MISC_REG_H264_REF_AWQOS_POS)
#define MMSYS_MISC_REG_H264_REF_AWQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_H264_REF_AWQOS_LEN)-1)<<MMSYS_MISC_REG_H264_REF_AWQOS_POS))
#define MMSYS_MISC_REG_H264_REF_ARQOS                           MMSYS_MISC_REG_H264_REF_ARQOS
#define MMSYS_MISC_REG_H264_REF_ARQOS_POS                       (23U)
#define MMSYS_MISC_REG_H264_REF_ARQOS_LEN                       (1U)
#define MMSYS_MISC_REG_H264_REF_ARQOS_MSK                       (((1U<<MMSYS_MISC_REG_H264_REF_ARQOS_LEN)-1)<<MMSYS_MISC_REG_H264_REF_ARQOS_POS)
#define MMSYS_MISC_REG_H264_REF_ARQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_H264_REF_ARQOS_LEN)-1)<<MMSYS_MISC_REG_H264_REF_ARQOS_POS))
#define MMSYS_MISC_REG_H264_EXT_AWQOS                           MMSYS_MISC_REG_H264_EXT_AWQOS
#define MMSYS_MISC_REG_H264_EXT_AWQOS_POS                       (24U)
#define MMSYS_MISC_REG_H264_EXT_AWQOS_LEN                       (1U)
#define MMSYS_MISC_REG_H264_EXT_AWQOS_MSK                       (((1U<<MMSYS_MISC_REG_H264_EXT_AWQOS_LEN)-1)<<MMSYS_MISC_REG_H264_EXT_AWQOS_POS)
#define MMSYS_MISC_REG_H264_EXT_AWQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_H264_EXT_AWQOS_LEN)-1)<<MMSYS_MISC_REG_H264_EXT_AWQOS_POS))
#define MMSYS_MISC_REG_H264_EXT_ARQOS                           MMSYS_MISC_REG_H264_EXT_ARQOS
#define MMSYS_MISC_REG_H264_EXT_ARQOS_POS                       (25U)
#define MMSYS_MISC_REG_H264_EXT_ARQOS_LEN                       (1U)
#define MMSYS_MISC_REG_H264_EXT_ARQOS_MSK                       (((1U<<MMSYS_MISC_REG_H264_EXT_ARQOS_LEN)-1)<<MMSYS_MISC_REG_H264_EXT_ARQOS_POS)
#define MMSYS_MISC_REG_H264_EXT_ARQOS_UMSK                      (~(((1U<<MMSYS_MISC_REG_H264_EXT_ARQOS_LEN)-1)<<MMSYS_MISC_REG_H264_EXT_ARQOS_POS))
#define MMSYS_MISC_REG_D2BA_AWQOS                               MMSYS_MISC_REG_D2BA_AWQOS
#define MMSYS_MISC_REG_D2BA_AWQOS_POS                           (26U)
#define MMSYS_MISC_REG_D2BA_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_D2BA_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_D2BA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BA_AWQOS_POS)
#define MMSYS_MISC_REG_D2BA_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_D2BA_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BA_AWQOS_POS))
#define MMSYS_MISC_REG_D2BB_AWQOS                               MMSYS_MISC_REG_D2BB_AWQOS
#define MMSYS_MISC_REG_D2BB_AWQOS_POS                           (27U)
#define MMSYS_MISC_REG_D2BB_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_D2BB_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_D2BB_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BB_AWQOS_POS)
#define MMSYS_MISC_REG_D2BB_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_D2BB_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BB_AWQOS_POS))
#define MMSYS_MISC_REG_D2BC_AWQOS                               MMSYS_MISC_REG_D2BC_AWQOS
#define MMSYS_MISC_REG_D2BC_AWQOS_POS                           (28U)
#define MMSYS_MISC_REG_D2BC_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_D2BC_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_D2BC_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BC_AWQOS_POS)
#define MMSYS_MISC_REG_D2BC_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_D2BC_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BC_AWQOS_POS))
#define MMSYS_MISC_REG_D2BD_AWQOS                               MMSYS_MISC_REG_D2BD_AWQOS
#define MMSYS_MISC_REG_D2BD_AWQOS_POS                           (29U)
#define MMSYS_MISC_REG_D2BD_AWQOS_LEN                           (1U)
#define MMSYS_MISC_REG_D2BD_AWQOS_MSK                           (((1U<<MMSYS_MISC_REG_D2BD_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BD_AWQOS_POS)
#define MMSYS_MISC_REG_D2BD_AWQOS_UMSK                          (~(((1U<<MMSYS_MISC_REG_D2BD_AWQOS_LEN)-1)<<MMSYS_MISC_REG_D2BD_AWQOS_POS))
#define MMSYS_MISC_REG_ISP_DTSRC_ARQOS                          MMSYS_MISC_REG_ISP_DTSRC_ARQOS
#define MMSYS_MISC_REG_ISP_DTSRC_ARQOS_POS                      (30U)
#define MMSYS_MISC_REG_ISP_DTSRC_ARQOS_LEN                      (1U)
#define MMSYS_MISC_REG_ISP_DTSRC_ARQOS_MSK                      (((1U<<MMSYS_MISC_REG_ISP_DTSRC_ARQOS_LEN)-1)<<MMSYS_MISC_REG_ISP_DTSRC_ARQOS_POS)
#define MMSYS_MISC_REG_ISP_DTSRC_ARQOS_UMSK                     (~(((1U<<MMSYS_MISC_REG_ISP_DTSRC_ARQOS_LEN)-1)<<MMSYS_MISC_REG_ISP_DTSRC_ARQOS_POS))
#define MMSYS_MISC_REG_HDMI_DTSRC_ARQOS                         MMSYS_MISC_REG_HDMI_DTSRC_ARQOS
#define MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_POS                     (31U)
#define MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_LEN                     (1U)
#define MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_MSK                     (((1U<<MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_LEN)-1)<<MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_POS)
#define MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_UMSK                    (~(((1U<<MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_LEN)-1)<<MMSYS_MISC_REG_HDMI_DTSRC_ARQOS_POS))

/* 0x30 : mm_infra_bus_error */
#define MMSYS_MISC_MM_INFRA_BUS_ERROR_OFFSET                    (0x30)
#define MMSYS_MISC_REG_MI_DEC_ERR_CLR                           MMSYS_MISC_REG_MI_DEC_ERR_CLR
#define MMSYS_MISC_REG_MI_DEC_ERR_CLR_POS                       (0U)
#define MMSYS_MISC_REG_MI_DEC_ERR_CLR_LEN                       (1U)
#define MMSYS_MISC_REG_MI_DEC_ERR_CLR_MSK                       (((1U<<MMSYS_MISC_REG_MI_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_MI_DEC_ERR_CLR_POS)
#define MMSYS_MISC_REG_MI_DEC_ERR_CLR_UMSK                      (~(((1U<<MMSYS_MISC_REG_MI_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_MI_DEC_ERR_CLR_POS))
#define MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST                    MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST
#define MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_POS                (1U)
#define MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_LEN                (1U)
#define MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_MSK                (((1U<<MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_POS)
#define MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_UMSK               (~(((1U<<MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_MI_DEC_ERR_LATCH_LAST_POS))
#define MMSYS_MISC_MM_INFRA_DEC_ERR                             MMSYS_MISC_MM_INFRA_DEC_ERR
#define MMSYS_MISC_MM_INFRA_DEC_ERR_POS                         (2U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_LEN                         (1U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_MSK                         (((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_POS)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_UMSK                        (~(((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_POS))
#define MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE                       MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE
#define MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_POS                   (3U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_LEN                   (1U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_MSK                   (((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_POS)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_UMSK                  (~(((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_WRITE_POS))
#define MMSYS_MISC_MM_INFRA_DEC_ERR_SRC                         MMSYS_MISC_MM_INFRA_DEC_ERR_SRC
#define MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_POS                     (4U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_LEN                     (3U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_MSK                     (((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_POS)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_UMSK                    (~(((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_SRC_POS))
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ID                          MMSYS_MISC_MM_INFRA_DEC_ERR_ID
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ID_POS                      (8U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ID_LEN                      (8U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ID_MSK                      (((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_ID_POS)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ID_UMSK                     (~(((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_ID_POS))

/* 0x34 : mm_infra_bus_error_addr */
#define MMSYS_MISC_MM_INFRA_BUS_ERROR_ADDR_OFFSET               (0x34)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR                        MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_POS                    (0U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_LEN                    (32U)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_MSK                    (((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_POS)
#define MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_UMSK                   (~(((1U<<MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_MM_INFRA_DEC_ERR_ADDR_POS))

/* 0x38 : emi_bus_error */
#define MMSYS_MISC_EMI_BUS_ERROR_OFFSET                         (0x38)
#define MMSYS_MISC_REG_EMI_DEC_ERR_CLR                          MMSYS_MISC_REG_EMI_DEC_ERR_CLR
#define MMSYS_MISC_REG_EMI_DEC_ERR_CLR_POS                      (0U)
#define MMSYS_MISC_REG_EMI_DEC_ERR_CLR_LEN                      (1U)
#define MMSYS_MISC_REG_EMI_DEC_ERR_CLR_MSK                      (((1U<<MMSYS_MISC_REG_EMI_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_EMI_DEC_ERR_CLR_POS)
#define MMSYS_MISC_REG_EMI_DEC_ERR_CLR_UMSK                     (~(((1U<<MMSYS_MISC_REG_EMI_DEC_ERR_CLR_LEN)-1)<<MMSYS_MISC_REG_EMI_DEC_ERR_CLR_POS))
#define MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST                   MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST
#define MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_POS               (1U)
#define MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_LEN               (1U)
#define MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_MSK               (((1U<<MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_POS)
#define MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_UMSK              (~(((1U<<MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_LEN)-1)<<MMSYS_MISC_REG_EMI_DEC_ERR_LATCH_LAST_POS))
#define MMSYS_MISC_EMI_DEC_ERR                                  MMSYS_MISC_EMI_DEC_ERR
#define MMSYS_MISC_EMI_DEC_ERR_POS                              (2U)
#define MMSYS_MISC_EMI_DEC_ERR_LEN                              (1U)
#define MMSYS_MISC_EMI_DEC_ERR_MSK                              (((1U<<MMSYS_MISC_EMI_DEC_ERR_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_POS)
#define MMSYS_MISC_EMI_DEC_ERR_UMSK                             (~(((1U<<MMSYS_MISC_EMI_DEC_ERR_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_POS))
#define MMSYS_MISC_EMI_DEC_ERR_WRITE                            MMSYS_MISC_EMI_DEC_ERR_WRITE
#define MMSYS_MISC_EMI_DEC_ERR_WRITE_POS                        (3U)
#define MMSYS_MISC_EMI_DEC_ERR_WRITE_LEN                        (1U)
#define MMSYS_MISC_EMI_DEC_ERR_WRITE_MSK                        (((1U<<MMSYS_MISC_EMI_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_WRITE_POS)
#define MMSYS_MISC_EMI_DEC_ERR_WRITE_UMSK                       (~(((1U<<MMSYS_MISC_EMI_DEC_ERR_WRITE_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_WRITE_POS))
#define MMSYS_MISC_EMI_DEC_ERR_SRC                              MMSYS_MISC_EMI_DEC_ERR_SRC
#define MMSYS_MISC_EMI_DEC_ERR_SRC_POS                          (4U)
#define MMSYS_MISC_EMI_DEC_ERR_SRC_LEN                          (2U)
#define MMSYS_MISC_EMI_DEC_ERR_SRC_MSK                          (((1U<<MMSYS_MISC_EMI_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_SRC_POS)
#define MMSYS_MISC_EMI_DEC_ERR_SRC_UMSK                         (~(((1U<<MMSYS_MISC_EMI_DEC_ERR_SRC_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_SRC_POS))
#define MMSYS_MISC_EMI_DEC_ERR_ID                               MMSYS_MISC_EMI_DEC_ERR_ID
#define MMSYS_MISC_EMI_DEC_ERR_ID_POS                           (8U)
#define MMSYS_MISC_EMI_DEC_ERR_ID_LEN                           (9U)
#define MMSYS_MISC_EMI_DEC_ERR_ID_MSK                           (((1U<<MMSYS_MISC_EMI_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_ID_POS)
#define MMSYS_MISC_EMI_DEC_ERR_ID_UMSK                          (~(((1U<<MMSYS_MISC_EMI_DEC_ERR_ID_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_ID_POS))

/* 0x3C : emi_bus_error_addr */
#define MMSYS_MISC_EMI_BUS_ERROR_ADDR_OFFSET                    (0x3C)
#define MMSYS_MISC_EMI_DEC_ERR_ADDR                             MMSYS_MISC_EMI_DEC_ERR_ADDR
#define MMSYS_MISC_EMI_DEC_ERR_ADDR_POS                         (0U)
#define MMSYS_MISC_EMI_DEC_ERR_ADDR_LEN                         (32U)
#define MMSYS_MISC_EMI_DEC_ERR_ADDR_MSK                         (((1U<<MMSYS_MISC_EMI_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_ADDR_POS)
#define MMSYS_MISC_EMI_DEC_ERR_ADDR_UMSK                        (~(((1U<<MMSYS_MISC_EMI_DEC_ERR_ADDR_LEN)-1)<<MMSYS_MISC_EMI_DEC_ERR_ADDR_POS))

/* 0x40 : dma_clk_ctrl */
#define MMSYS_MISC_DMA_CLK_CTRL_OFFSET                          (0x40)
#define MMSYS_MISC_DMA_CLK_EN                                   MMSYS_MISC_DMA_CLK_EN
#define MMSYS_MISC_DMA_CLK_EN_POS                               (0U)
#define MMSYS_MISC_DMA_CLK_EN_LEN                               (8U)
#define MMSYS_MISC_DMA_CLK_EN_MSK                               (((1U<<MMSYS_MISC_DMA_CLK_EN_LEN)-1)<<MMSYS_MISC_DMA_CLK_EN_POS)
#define MMSYS_MISC_DMA_CLK_EN_UMSK                              (~(((1U<<MMSYS_MISC_DMA_CLK_EN_LEN)-1)<<MMSYS_MISC_DMA_CLK_EN_POS))

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

/* 0xF0 : gpio_ctl */
#define MMSYS_MISC_GPIO_CTL_OFFSET                              (0xF0)
#define MMSYS_MISC_REG_DEBUG_OE                                 MMSYS_MISC_REG_DEBUG_OE
#define MMSYS_MISC_REG_DEBUG_OE_POS                             (0U)
#define MMSYS_MISC_REG_DEBUG_OE_LEN                             (1U)
#define MMSYS_MISC_REG_DEBUG_OE_MSK                             (((1U<<MMSYS_MISC_REG_DEBUG_OE_LEN)-1)<<MMSYS_MISC_REG_DEBUG_OE_POS)
#define MMSYS_MISC_REG_DEBUG_OE_UMSK                            (~(((1U<<MMSYS_MISC_REG_DEBUG_OE_LEN)-1)<<MMSYS_MISC_REG_DEBUG_OE_POS))
#define MMSYS_MISC_REG_SPI_MASTER_MODE                          MMSYS_MISC_REG_SPI_MASTER_MODE
#define MMSYS_MISC_REG_SPI_MASTER_MODE_POS                      (1U)
#define MMSYS_MISC_REG_SPI_MASTER_MODE_LEN                      (1U)
#define MMSYS_MISC_REG_SPI_MASTER_MODE_MSK                      (((1U<<MMSYS_MISC_REG_SPI_MASTER_MODE_LEN)-1)<<MMSYS_MISC_REG_SPI_MASTER_MODE_POS)
#define MMSYS_MISC_REG_SPI_MASTER_MODE_UMSK                     (~(((1U<<MMSYS_MISC_REG_SPI_MASTER_MODE_LEN)-1)<<MMSYS_MISC_REG_SPI_MASTER_MODE_POS))
#define MMSYS_MISC_REG_SPI_SWAP                                 MMSYS_MISC_REG_SPI_SWAP
#define MMSYS_MISC_REG_SPI_SWAP_POS                             (2U)
#define MMSYS_MISC_REG_SPI_SWAP_LEN                             (1U)
#define MMSYS_MISC_REG_SPI_SWAP_MSK                             (((1U<<MMSYS_MISC_REG_SPI_SWAP_LEN)-1)<<MMSYS_MISC_REG_SPI_SWAP_POS)
#define MMSYS_MISC_REG_SPI_SWAP_UMSK                            (~(((1U<<MMSYS_MISC_REG_SPI_SWAP_LEN)-1)<<MMSYS_MISC_REG_SPI_SWAP_POS))

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

/* 0x200 : GPIO_CFGCTL0 */
#define MMSYS_MISC_GPIO_CFGCTL0_OFFSET                          (0x200)
#define MMSYS_MISC_REG_GPIO_0_IE                                MMSYS_MISC_REG_GPIO_0_IE
#define MMSYS_MISC_REG_GPIO_0_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_0_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_IE_POS)
#define MMSYS_MISC_REG_GPIO_0_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_IE_POS))
#define MMSYS_MISC_REG_GPIO_0_SMT                               MMSYS_MISC_REG_GPIO_0_SMT
#define MMSYS_MISC_REG_GPIO_0_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_0_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_0_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_0_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_SMT_POS)
#define MMSYS_MISC_REG_GPIO_0_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_0_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_SMT_POS))
#define MMSYS_MISC_REG_GPIO_0_DRV                               MMSYS_MISC_REG_GPIO_0_DRV
#define MMSYS_MISC_REG_GPIO_0_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_0_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_0_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_0_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_DRV_POS)
#define MMSYS_MISC_REG_GPIO_0_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_0_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_DRV_POS))
#define MMSYS_MISC_REG_GPIO_0_PU                                MMSYS_MISC_REG_GPIO_0_PU
#define MMSYS_MISC_REG_GPIO_0_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_0_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PU_POS)
#define MMSYS_MISC_REG_GPIO_0_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PU_POS))
#define MMSYS_MISC_REG_GPIO_0_PD                                MMSYS_MISC_REG_GPIO_0_PD
#define MMSYS_MISC_REG_GPIO_0_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_0_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PD_POS)
#define MMSYS_MISC_REG_GPIO_0_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PD_POS))
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL                          MMSYS_MISC_REG_GPIO_0_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_1_IE                                MMSYS_MISC_REG_GPIO_1_IE
#define MMSYS_MISC_REG_GPIO_1_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_1_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_IE_POS)
#define MMSYS_MISC_REG_GPIO_1_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_IE_POS))
#define MMSYS_MISC_REG_GPIO_1_SMT                               MMSYS_MISC_REG_GPIO_1_SMT
#define MMSYS_MISC_REG_GPIO_1_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_1_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_1_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_1_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_SMT_POS)
#define MMSYS_MISC_REG_GPIO_1_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_1_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_SMT_POS))
#define MMSYS_MISC_REG_GPIO_1_DRV                               MMSYS_MISC_REG_GPIO_1_DRV
#define MMSYS_MISC_REG_GPIO_1_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_1_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_1_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_1_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_DRV_POS)
#define MMSYS_MISC_REG_GPIO_1_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_1_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_DRV_POS))
#define MMSYS_MISC_REG_GPIO_1_PU                                MMSYS_MISC_REG_GPIO_1_PU
#define MMSYS_MISC_REG_GPIO_1_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_1_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PU_POS)
#define MMSYS_MISC_REG_GPIO_1_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PU_POS))
#define MMSYS_MISC_REG_GPIO_1_PD                                MMSYS_MISC_REG_GPIO_1_PD
#define MMSYS_MISC_REG_GPIO_1_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_1_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PD_POS)
#define MMSYS_MISC_REG_GPIO_1_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PD_POS))
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL                          MMSYS_MISC_REG_GPIO_1_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS))

/* 0x204 : GPIO_CFGCTL1 */
#define MMSYS_MISC_GPIO_CFGCTL1_OFFSET                          (0x204)
#define MMSYS_MISC_REG_GPIO_2_IE                                MMSYS_MISC_REG_GPIO_2_IE
#define MMSYS_MISC_REG_GPIO_2_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_2_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_2_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_2_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_IE_POS)
#define MMSYS_MISC_REG_GPIO_2_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_2_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_IE_POS))
#define MMSYS_MISC_REG_GPIO_2_SMT                               MMSYS_MISC_REG_GPIO_2_SMT
#define MMSYS_MISC_REG_GPIO_2_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_2_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_2_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_2_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_SMT_POS)
#define MMSYS_MISC_REG_GPIO_2_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_2_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_SMT_POS))
#define MMSYS_MISC_REG_GPIO_2_DRV                               MMSYS_MISC_REG_GPIO_2_DRV
#define MMSYS_MISC_REG_GPIO_2_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_2_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_2_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_2_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_DRV_POS)
#define MMSYS_MISC_REG_GPIO_2_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_2_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_DRV_POS))
#define MMSYS_MISC_REG_GPIO_2_PU                                MMSYS_MISC_REG_GPIO_2_PU
#define MMSYS_MISC_REG_GPIO_2_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_2_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_2_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_2_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_PU_POS)
#define MMSYS_MISC_REG_GPIO_2_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_2_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_PU_POS))
#define MMSYS_MISC_REG_GPIO_2_PD                                MMSYS_MISC_REG_GPIO_2_PD
#define MMSYS_MISC_REG_GPIO_2_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_2_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_2_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_2_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_PD_POS)
#define MMSYS_MISC_REG_GPIO_2_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_2_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_PD_POS))
#define MMSYS_MISC_REG_GPIO_2_FUNC_SEL                          MMSYS_MISC_REG_GPIO_2_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_2_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_2_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_2_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_2_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_2_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_2_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_3_IE                                MMSYS_MISC_REG_GPIO_3_IE
#define MMSYS_MISC_REG_GPIO_3_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_3_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_3_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_3_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_IE_POS)
#define MMSYS_MISC_REG_GPIO_3_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_3_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_IE_POS))
#define MMSYS_MISC_REG_GPIO_3_SMT                               MMSYS_MISC_REG_GPIO_3_SMT
#define MMSYS_MISC_REG_GPIO_3_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_3_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_3_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_3_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_SMT_POS)
#define MMSYS_MISC_REG_GPIO_3_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_3_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_SMT_POS))
#define MMSYS_MISC_REG_GPIO_3_DRV                               MMSYS_MISC_REG_GPIO_3_DRV
#define MMSYS_MISC_REG_GPIO_3_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_3_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_3_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_3_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_DRV_POS)
#define MMSYS_MISC_REG_GPIO_3_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_3_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_DRV_POS))
#define MMSYS_MISC_REG_GPIO_3_PU                                MMSYS_MISC_REG_GPIO_3_PU
#define MMSYS_MISC_REG_GPIO_3_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_3_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_3_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_3_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_PU_POS)
#define MMSYS_MISC_REG_GPIO_3_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_3_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_PU_POS))
#define MMSYS_MISC_REG_GPIO_3_PD                                MMSYS_MISC_REG_GPIO_3_PD
#define MMSYS_MISC_REG_GPIO_3_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_3_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_3_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_3_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_PD_POS)
#define MMSYS_MISC_REG_GPIO_3_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_3_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_PD_POS))
#define MMSYS_MISC_REG_GPIO_3_FUNC_SEL                          MMSYS_MISC_REG_GPIO_3_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_3_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_3_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_3_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_3_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_3_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_3_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_FUNC_SEL_POS))

/* 0x208 : GPIO_CFGCTL2 */
#define MMSYS_MISC_GPIO_CFGCTL2_OFFSET                          (0x208)
#define MMSYS_MISC_REG_GPIO_4_IE                                MMSYS_MISC_REG_GPIO_4_IE
#define MMSYS_MISC_REG_GPIO_4_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_4_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_4_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_4_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_IE_POS)
#define MMSYS_MISC_REG_GPIO_4_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_4_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_IE_POS))
#define MMSYS_MISC_REG_GPIO_4_SMT                               MMSYS_MISC_REG_GPIO_4_SMT
#define MMSYS_MISC_REG_GPIO_4_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_4_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_4_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_4_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_SMT_POS)
#define MMSYS_MISC_REG_GPIO_4_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_4_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_SMT_POS))
#define MMSYS_MISC_REG_GPIO_4_DRV                               MMSYS_MISC_REG_GPIO_4_DRV
#define MMSYS_MISC_REG_GPIO_4_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_4_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_4_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_4_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_DRV_POS)
#define MMSYS_MISC_REG_GPIO_4_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_4_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_DRV_POS))
#define MMSYS_MISC_REG_GPIO_4_PU                                MMSYS_MISC_REG_GPIO_4_PU
#define MMSYS_MISC_REG_GPIO_4_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_4_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_4_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_4_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_PU_POS)
#define MMSYS_MISC_REG_GPIO_4_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_4_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_PU_POS))
#define MMSYS_MISC_REG_GPIO_4_PD                                MMSYS_MISC_REG_GPIO_4_PD
#define MMSYS_MISC_REG_GPIO_4_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_4_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_4_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_4_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_PD_POS)
#define MMSYS_MISC_REG_GPIO_4_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_4_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_PD_POS))
#define MMSYS_MISC_REG_GPIO_4_FUNC_SEL                          MMSYS_MISC_REG_GPIO_4_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_4_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_4_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_4_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_4_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_4_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_4_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_5_IE                                MMSYS_MISC_REG_GPIO_5_IE
#define MMSYS_MISC_REG_GPIO_5_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_5_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_5_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_5_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_IE_POS)
#define MMSYS_MISC_REG_GPIO_5_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_5_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_IE_POS))
#define MMSYS_MISC_REG_GPIO_5_SMT                               MMSYS_MISC_REG_GPIO_5_SMT
#define MMSYS_MISC_REG_GPIO_5_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_5_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_5_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_5_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_SMT_POS)
#define MMSYS_MISC_REG_GPIO_5_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_5_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_SMT_POS))
#define MMSYS_MISC_REG_GPIO_5_DRV                               MMSYS_MISC_REG_GPIO_5_DRV
#define MMSYS_MISC_REG_GPIO_5_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_5_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_5_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_5_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_DRV_POS)
#define MMSYS_MISC_REG_GPIO_5_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_5_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_DRV_POS))
#define MMSYS_MISC_REG_GPIO_5_PU                                MMSYS_MISC_REG_GPIO_5_PU
#define MMSYS_MISC_REG_GPIO_5_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_5_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_5_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_5_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_PU_POS)
#define MMSYS_MISC_REG_GPIO_5_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_5_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_PU_POS))
#define MMSYS_MISC_REG_GPIO_5_PD                                MMSYS_MISC_REG_GPIO_5_PD
#define MMSYS_MISC_REG_GPIO_5_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_5_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_5_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_5_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_PD_POS)
#define MMSYS_MISC_REG_GPIO_5_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_5_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_PD_POS))
#define MMSYS_MISC_REG_GPIO_5_FUNC_SEL                          MMSYS_MISC_REG_GPIO_5_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_5_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_5_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_5_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_5_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_5_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_5_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_FUNC_SEL_POS))

/* 0x20C : GPIO_CFGCTL3 */
#define MMSYS_MISC_GPIO_CFGCTL3_OFFSET                          (0x20C)
#define MMSYS_MISC_REG_GPIO_6_IE                                MMSYS_MISC_REG_GPIO_6_IE
#define MMSYS_MISC_REG_GPIO_6_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_6_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_6_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_6_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_IE_POS)
#define MMSYS_MISC_REG_GPIO_6_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_6_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_IE_POS))
#define MMSYS_MISC_REG_GPIO_6_SMT                               MMSYS_MISC_REG_GPIO_6_SMT
#define MMSYS_MISC_REG_GPIO_6_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_6_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_6_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_6_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_SMT_POS)
#define MMSYS_MISC_REG_GPIO_6_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_6_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_SMT_POS))
#define MMSYS_MISC_REG_GPIO_6_DRV                               MMSYS_MISC_REG_GPIO_6_DRV
#define MMSYS_MISC_REG_GPIO_6_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_6_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_6_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_6_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_DRV_POS)
#define MMSYS_MISC_REG_GPIO_6_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_6_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_DRV_POS))
#define MMSYS_MISC_REG_GPIO_6_PU                                MMSYS_MISC_REG_GPIO_6_PU
#define MMSYS_MISC_REG_GPIO_6_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_6_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_6_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_6_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_PU_POS)
#define MMSYS_MISC_REG_GPIO_6_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_6_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_PU_POS))
#define MMSYS_MISC_REG_GPIO_6_PD                                MMSYS_MISC_REG_GPIO_6_PD
#define MMSYS_MISC_REG_GPIO_6_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_6_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_6_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_6_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_PD_POS)
#define MMSYS_MISC_REG_GPIO_6_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_6_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_PD_POS))
#define MMSYS_MISC_REG_GPIO_6_FUNC_SEL                          MMSYS_MISC_REG_GPIO_6_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_6_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_6_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_6_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_6_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_6_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_6_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_7_IE                                MMSYS_MISC_REG_GPIO_7_IE
#define MMSYS_MISC_REG_GPIO_7_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_7_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_7_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_7_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_IE_POS)
#define MMSYS_MISC_REG_GPIO_7_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_7_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_IE_POS))
#define MMSYS_MISC_REG_GPIO_7_SMT                               MMSYS_MISC_REG_GPIO_7_SMT
#define MMSYS_MISC_REG_GPIO_7_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_7_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_7_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_7_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_SMT_POS)
#define MMSYS_MISC_REG_GPIO_7_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_7_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_SMT_POS))
#define MMSYS_MISC_REG_GPIO_7_DRV                               MMSYS_MISC_REG_GPIO_7_DRV
#define MMSYS_MISC_REG_GPIO_7_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_7_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_7_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_7_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_DRV_POS)
#define MMSYS_MISC_REG_GPIO_7_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_7_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_DRV_POS))
#define MMSYS_MISC_REG_GPIO_7_PU                                MMSYS_MISC_REG_GPIO_7_PU
#define MMSYS_MISC_REG_GPIO_7_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_7_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_7_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_7_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_PU_POS)
#define MMSYS_MISC_REG_GPIO_7_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_7_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_PU_POS))
#define MMSYS_MISC_REG_GPIO_7_PD                                MMSYS_MISC_REG_GPIO_7_PD
#define MMSYS_MISC_REG_GPIO_7_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_7_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_7_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_7_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_PD_POS)
#define MMSYS_MISC_REG_GPIO_7_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_7_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_PD_POS))
#define MMSYS_MISC_REG_GPIO_7_FUNC_SEL                          MMSYS_MISC_REG_GPIO_7_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_7_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_7_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_7_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_7_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_7_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_7_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_FUNC_SEL_POS))

/* 0x210 : GPIO_CFGCTL4 */
#define MMSYS_MISC_GPIO_CFGCTL4_OFFSET                          (0x210)
#define MMSYS_MISC_REG_GPIO_8_IE                                MMSYS_MISC_REG_GPIO_8_IE
#define MMSYS_MISC_REG_GPIO_8_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_8_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_8_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_8_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_IE_POS)
#define MMSYS_MISC_REG_GPIO_8_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_8_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_IE_POS))
#define MMSYS_MISC_REG_GPIO_8_SMT                               MMSYS_MISC_REG_GPIO_8_SMT
#define MMSYS_MISC_REG_GPIO_8_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_8_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_8_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_8_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_SMT_POS)
#define MMSYS_MISC_REG_GPIO_8_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_8_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_SMT_POS))
#define MMSYS_MISC_REG_GPIO_8_DRV                               MMSYS_MISC_REG_GPIO_8_DRV
#define MMSYS_MISC_REG_GPIO_8_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_8_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_8_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_8_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_DRV_POS)
#define MMSYS_MISC_REG_GPIO_8_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_8_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_DRV_POS))
#define MMSYS_MISC_REG_GPIO_8_PU                                MMSYS_MISC_REG_GPIO_8_PU
#define MMSYS_MISC_REG_GPIO_8_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_8_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_8_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_8_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_PU_POS)
#define MMSYS_MISC_REG_GPIO_8_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_8_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_PU_POS))
#define MMSYS_MISC_REG_GPIO_8_PD                                MMSYS_MISC_REG_GPIO_8_PD
#define MMSYS_MISC_REG_GPIO_8_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_8_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_8_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_8_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_PD_POS)
#define MMSYS_MISC_REG_GPIO_8_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_8_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_PD_POS))
#define MMSYS_MISC_REG_GPIO_8_FUNC_SEL                          MMSYS_MISC_REG_GPIO_8_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_8_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_8_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_8_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_8_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_8_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_8_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_9_IE                                MMSYS_MISC_REG_GPIO_9_IE
#define MMSYS_MISC_REG_GPIO_9_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_9_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_9_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_9_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_IE_POS)
#define MMSYS_MISC_REG_GPIO_9_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_9_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_IE_POS))
#define MMSYS_MISC_REG_GPIO_9_SMT                               MMSYS_MISC_REG_GPIO_9_SMT
#define MMSYS_MISC_REG_GPIO_9_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_9_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_9_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_9_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_SMT_POS)
#define MMSYS_MISC_REG_GPIO_9_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_9_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_SMT_POS))
#define MMSYS_MISC_REG_GPIO_9_DRV                               MMSYS_MISC_REG_GPIO_9_DRV
#define MMSYS_MISC_REG_GPIO_9_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_9_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_9_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_9_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_DRV_POS)
#define MMSYS_MISC_REG_GPIO_9_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_9_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_DRV_POS))
#define MMSYS_MISC_REG_GPIO_9_PU                                MMSYS_MISC_REG_GPIO_9_PU
#define MMSYS_MISC_REG_GPIO_9_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_9_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_9_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_9_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_PU_POS)
#define MMSYS_MISC_REG_GPIO_9_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_9_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_PU_POS))
#define MMSYS_MISC_REG_GPIO_9_PD                                MMSYS_MISC_REG_GPIO_9_PD
#define MMSYS_MISC_REG_GPIO_9_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_9_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_9_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_9_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_PD_POS)
#define MMSYS_MISC_REG_GPIO_9_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_9_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_PD_POS))
#define MMSYS_MISC_REG_GPIO_9_FUNC_SEL                          MMSYS_MISC_REG_GPIO_9_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_9_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_9_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_9_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_9_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_9_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_9_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_FUNC_SEL_POS))

/* 0x214 : GPIO_CFGCTL5 */
#define MMSYS_MISC_GPIO_CFGCTL5_OFFSET                          (0x214)
#define MMSYS_MISC_REG_GPIO_10_IE                               MMSYS_MISC_REG_GPIO_10_IE
#define MMSYS_MISC_REG_GPIO_10_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_10_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_10_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_10_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_IE_POS)
#define MMSYS_MISC_REG_GPIO_10_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_10_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_IE_POS))
#define MMSYS_MISC_REG_GPIO_10_SMT                              MMSYS_MISC_REG_GPIO_10_SMT
#define MMSYS_MISC_REG_GPIO_10_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_10_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_10_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_10_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_SMT_POS)
#define MMSYS_MISC_REG_GPIO_10_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_10_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_SMT_POS))
#define MMSYS_MISC_REG_GPIO_10_DRV                              MMSYS_MISC_REG_GPIO_10_DRV
#define MMSYS_MISC_REG_GPIO_10_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_10_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_10_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_10_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_DRV_POS)
#define MMSYS_MISC_REG_GPIO_10_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_10_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_DRV_POS))
#define MMSYS_MISC_REG_GPIO_10_PU                               MMSYS_MISC_REG_GPIO_10_PU
#define MMSYS_MISC_REG_GPIO_10_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_10_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_10_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_10_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_PU_POS)
#define MMSYS_MISC_REG_GPIO_10_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_10_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_PU_POS))
#define MMSYS_MISC_REG_GPIO_10_PD                               MMSYS_MISC_REG_GPIO_10_PD
#define MMSYS_MISC_REG_GPIO_10_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_10_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_10_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_10_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_PD_POS)
#define MMSYS_MISC_REG_GPIO_10_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_10_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_PD_POS))
#define MMSYS_MISC_REG_GPIO_10_FUNC_SEL                         MMSYS_MISC_REG_GPIO_10_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_10_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_10_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_10_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_10_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_10_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_10_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_11_IE                               MMSYS_MISC_REG_GPIO_11_IE
#define MMSYS_MISC_REG_GPIO_11_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_11_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_11_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_11_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_IE_POS)
#define MMSYS_MISC_REG_GPIO_11_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_11_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_IE_POS))
#define MMSYS_MISC_REG_GPIO_11_SMT                              MMSYS_MISC_REG_GPIO_11_SMT
#define MMSYS_MISC_REG_GPIO_11_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_11_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_11_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_11_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_SMT_POS)
#define MMSYS_MISC_REG_GPIO_11_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_11_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_SMT_POS))
#define MMSYS_MISC_REG_GPIO_11_DRV                              MMSYS_MISC_REG_GPIO_11_DRV
#define MMSYS_MISC_REG_GPIO_11_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_11_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_11_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_11_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_DRV_POS)
#define MMSYS_MISC_REG_GPIO_11_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_11_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_DRV_POS))
#define MMSYS_MISC_REG_GPIO_11_PU                               MMSYS_MISC_REG_GPIO_11_PU
#define MMSYS_MISC_REG_GPIO_11_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_11_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_11_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_11_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_PU_POS)
#define MMSYS_MISC_REG_GPIO_11_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_11_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_PU_POS))
#define MMSYS_MISC_REG_GPIO_11_PD                               MMSYS_MISC_REG_GPIO_11_PD
#define MMSYS_MISC_REG_GPIO_11_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_11_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_11_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_11_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_PD_POS)
#define MMSYS_MISC_REG_GPIO_11_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_11_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_PD_POS))
#define MMSYS_MISC_REG_GPIO_11_FUNC_SEL                         MMSYS_MISC_REG_GPIO_11_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_11_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_11_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_11_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_11_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_11_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_11_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_FUNC_SEL_POS))

/* 0x218 : GPIO_CFGCTL6 */
#define MMSYS_MISC_GPIO_CFGCTL6_OFFSET                          (0x218)
#define MMSYS_MISC_REG_GPIO_12_IE                               MMSYS_MISC_REG_GPIO_12_IE
#define MMSYS_MISC_REG_GPIO_12_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_12_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_12_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_12_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_IE_POS)
#define MMSYS_MISC_REG_GPIO_12_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_12_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_IE_POS))
#define MMSYS_MISC_REG_GPIO_12_SMT                              MMSYS_MISC_REG_GPIO_12_SMT
#define MMSYS_MISC_REG_GPIO_12_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_12_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_12_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_12_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_SMT_POS)
#define MMSYS_MISC_REG_GPIO_12_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_12_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_SMT_POS))
#define MMSYS_MISC_REG_GPIO_12_DRV                              MMSYS_MISC_REG_GPIO_12_DRV
#define MMSYS_MISC_REG_GPIO_12_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_12_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_12_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_12_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_DRV_POS)
#define MMSYS_MISC_REG_GPIO_12_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_12_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_DRV_POS))
#define MMSYS_MISC_REG_GPIO_12_PU                               MMSYS_MISC_REG_GPIO_12_PU
#define MMSYS_MISC_REG_GPIO_12_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_12_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_12_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_12_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_PU_POS)
#define MMSYS_MISC_REG_GPIO_12_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_12_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_PU_POS))
#define MMSYS_MISC_REG_GPIO_12_PD                               MMSYS_MISC_REG_GPIO_12_PD
#define MMSYS_MISC_REG_GPIO_12_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_12_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_12_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_12_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_PD_POS)
#define MMSYS_MISC_REG_GPIO_12_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_12_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_PD_POS))
#define MMSYS_MISC_REG_GPIO_12_FUNC_SEL                         MMSYS_MISC_REG_GPIO_12_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_12_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_12_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_12_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_12_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_12_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_12_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_13_IE                               MMSYS_MISC_REG_GPIO_13_IE
#define MMSYS_MISC_REG_GPIO_13_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_13_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_13_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_13_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_IE_POS)
#define MMSYS_MISC_REG_GPIO_13_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_13_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_IE_POS))
#define MMSYS_MISC_REG_GPIO_13_SMT                              MMSYS_MISC_REG_GPIO_13_SMT
#define MMSYS_MISC_REG_GPIO_13_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_13_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_13_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_13_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_SMT_POS)
#define MMSYS_MISC_REG_GPIO_13_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_13_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_SMT_POS))
#define MMSYS_MISC_REG_GPIO_13_DRV                              MMSYS_MISC_REG_GPIO_13_DRV
#define MMSYS_MISC_REG_GPIO_13_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_13_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_13_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_13_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_DRV_POS)
#define MMSYS_MISC_REG_GPIO_13_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_13_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_DRV_POS))
#define MMSYS_MISC_REG_GPIO_13_PU                               MMSYS_MISC_REG_GPIO_13_PU
#define MMSYS_MISC_REG_GPIO_13_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_13_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_13_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_13_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_PU_POS)
#define MMSYS_MISC_REG_GPIO_13_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_13_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_PU_POS))
#define MMSYS_MISC_REG_GPIO_13_PD                               MMSYS_MISC_REG_GPIO_13_PD
#define MMSYS_MISC_REG_GPIO_13_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_13_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_13_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_13_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_PD_POS)
#define MMSYS_MISC_REG_GPIO_13_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_13_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_PD_POS))
#define MMSYS_MISC_REG_GPIO_13_FUNC_SEL                         MMSYS_MISC_REG_GPIO_13_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_13_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_13_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_13_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_13_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_13_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_13_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_FUNC_SEL_POS))

/* 0x21C : GPIO_CFGCTL7 */
#define MMSYS_MISC_GPIO_CFGCTL7_OFFSET                          (0x21C)
#define MMSYS_MISC_REG_GPIO_14_IE                               MMSYS_MISC_REG_GPIO_14_IE
#define MMSYS_MISC_REG_GPIO_14_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_14_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_14_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_14_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_IE_POS)
#define MMSYS_MISC_REG_GPIO_14_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_14_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_IE_POS))
#define MMSYS_MISC_REG_GPIO_14_SMT                              MMSYS_MISC_REG_GPIO_14_SMT
#define MMSYS_MISC_REG_GPIO_14_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_14_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_14_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_14_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_SMT_POS)
#define MMSYS_MISC_REG_GPIO_14_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_14_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_SMT_POS))
#define MMSYS_MISC_REG_GPIO_14_DRV                              MMSYS_MISC_REG_GPIO_14_DRV
#define MMSYS_MISC_REG_GPIO_14_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_14_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_14_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_14_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_DRV_POS)
#define MMSYS_MISC_REG_GPIO_14_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_14_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_DRV_POS))
#define MMSYS_MISC_REG_GPIO_14_PU                               MMSYS_MISC_REG_GPIO_14_PU
#define MMSYS_MISC_REG_GPIO_14_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_14_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_14_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_14_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_PU_POS)
#define MMSYS_MISC_REG_GPIO_14_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_14_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_PU_POS))
#define MMSYS_MISC_REG_GPIO_14_PD                               MMSYS_MISC_REG_GPIO_14_PD
#define MMSYS_MISC_REG_GPIO_14_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_14_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_14_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_14_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_PD_POS)
#define MMSYS_MISC_REG_GPIO_14_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_14_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_PD_POS))
#define MMSYS_MISC_REG_GPIO_14_FUNC_SEL                         MMSYS_MISC_REG_GPIO_14_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_14_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_14_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_14_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_14_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_14_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_14_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_15_IE                               MMSYS_MISC_REG_GPIO_15_IE
#define MMSYS_MISC_REG_GPIO_15_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_15_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_15_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_15_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_IE_POS)
#define MMSYS_MISC_REG_GPIO_15_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_15_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_IE_POS))
#define MMSYS_MISC_REG_GPIO_15_SMT                              MMSYS_MISC_REG_GPIO_15_SMT
#define MMSYS_MISC_REG_GPIO_15_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_15_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_15_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_15_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_SMT_POS)
#define MMSYS_MISC_REG_GPIO_15_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_15_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_SMT_POS))
#define MMSYS_MISC_REG_GPIO_15_DRV                              MMSYS_MISC_REG_GPIO_15_DRV
#define MMSYS_MISC_REG_GPIO_15_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_15_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_15_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_15_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_DRV_POS)
#define MMSYS_MISC_REG_GPIO_15_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_15_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_DRV_POS))
#define MMSYS_MISC_REG_GPIO_15_PU                               MMSYS_MISC_REG_GPIO_15_PU
#define MMSYS_MISC_REG_GPIO_15_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_15_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_15_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_15_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_PU_POS)
#define MMSYS_MISC_REG_GPIO_15_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_15_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_PU_POS))
#define MMSYS_MISC_REG_GPIO_15_PD                               MMSYS_MISC_REG_GPIO_15_PD
#define MMSYS_MISC_REG_GPIO_15_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_15_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_15_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_15_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_PD_POS)
#define MMSYS_MISC_REG_GPIO_15_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_15_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_PD_POS))
#define MMSYS_MISC_REG_GPIO_15_FUNC_SEL                         MMSYS_MISC_REG_GPIO_15_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_15_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_15_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_15_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_15_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_15_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_15_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_FUNC_SEL_POS))

/* 0x220 : GPIO_CFGCTL8 */
#define MMSYS_MISC_GPIO_CFGCTL8_OFFSET                          (0x220)
#define MMSYS_MISC_REG_GPIO_16_IE                               MMSYS_MISC_REG_GPIO_16_IE
#define MMSYS_MISC_REG_GPIO_16_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_16_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_16_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_16_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_IE_POS)
#define MMSYS_MISC_REG_GPIO_16_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_16_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_IE_POS))
#define MMSYS_MISC_REG_GPIO_16_SMT                              MMSYS_MISC_REG_GPIO_16_SMT
#define MMSYS_MISC_REG_GPIO_16_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_16_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_16_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_16_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_SMT_POS)
#define MMSYS_MISC_REG_GPIO_16_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_16_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_SMT_POS))
#define MMSYS_MISC_REG_GPIO_16_DRV                              MMSYS_MISC_REG_GPIO_16_DRV
#define MMSYS_MISC_REG_GPIO_16_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_16_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_16_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_16_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_DRV_POS)
#define MMSYS_MISC_REG_GPIO_16_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_16_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_DRV_POS))
#define MMSYS_MISC_REG_GPIO_16_PU                               MMSYS_MISC_REG_GPIO_16_PU
#define MMSYS_MISC_REG_GPIO_16_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_16_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_16_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_16_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_PU_POS)
#define MMSYS_MISC_REG_GPIO_16_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_16_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_PU_POS))
#define MMSYS_MISC_REG_GPIO_16_PD                               MMSYS_MISC_REG_GPIO_16_PD
#define MMSYS_MISC_REG_GPIO_16_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_16_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_16_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_16_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_PD_POS)
#define MMSYS_MISC_REG_GPIO_16_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_16_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_PD_POS))
#define MMSYS_MISC_REG_GPIO_16_FUNC_SEL                         MMSYS_MISC_REG_GPIO_16_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_16_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_16_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_16_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_16_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_16_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_16_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_17_IE                               MMSYS_MISC_REG_GPIO_17_IE
#define MMSYS_MISC_REG_GPIO_17_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_17_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_17_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_17_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_IE_POS)
#define MMSYS_MISC_REG_GPIO_17_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_17_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_IE_POS))
#define MMSYS_MISC_REG_GPIO_17_SMT                              MMSYS_MISC_REG_GPIO_17_SMT
#define MMSYS_MISC_REG_GPIO_17_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_17_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_17_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_17_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_SMT_POS)
#define MMSYS_MISC_REG_GPIO_17_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_17_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_SMT_POS))
#define MMSYS_MISC_REG_GPIO_17_DRV                              MMSYS_MISC_REG_GPIO_17_DRV
#define MMSYS_MISC_REG_GPIO_17_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_17_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_17_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_17_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_DRV_POS)
#define MMSYS_MISC_REG_GPIO_17_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_17_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_DRV_POS))
#define MMSYS_MISC_REG_GPIO_17_PU                               MMSYS_MISC_REG_GPIO_17_PU
#define MMSYS_MISC_REG_GPIO_17_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_17_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_17_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_17_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_PU_POS)
#define MMSYS_MISC_REG_GPIO_17_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_17_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_PU_POS))
#define MMSYS_MISC_REG_GPIO_17_PD                               MMSYS_MISC_REG_GPIO_17_PD
#define MMSYS_MISC_REG_GPIO_17_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_17_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_17_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_17_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_PD_POS)
#define MMSYS_MISC_REG_GPIO_17_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_17_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_PD_POS))
#define MMSYS_MISC_REG_GPIO_17_FUNC_SEL                         MMSYS_MISC_REG_GPIO_17_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_17_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_17_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_17_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_17_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_17_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_17_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_FUNC_SEL_POS))

/* 0x224 : GPIO_CFGCTL9 */
#define MMSYS_MISC_GPIO_CFGCTL9_OFFSET                          (0x224)
#define MMSYS_MISC_REG_GPIO_18_IE                               MMSYS_MISC_REG_GPIO_18_IE
#define MMSYS_MISC_REG_GPIO_18_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_18_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_18_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_18_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_IE_POS)
#define MMSYS_MISC_REG_GPIO_18_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_18_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_IE_POS))
#define MMSYS_MISC_REG_GPIO_18_SMT                              MMSYS_MISC_REG_GPIO_18_SMT
#define MMSYS_MISC_REG_GPIO_18_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_18_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_18_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_18_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_SMT_POS)
#define MMSYS_MISC_REG_GPIO_18_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_18_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_SMT_POS))
#define MMSYS_MISC_REG_GPIO_18_DRV                              MMSYS_MISC_REG_GPIO_18_DRV
#define MMSYS_MISC_REG_GPIO_18_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_18_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_18_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_18_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_DRV_POS)
#define MMSYS_MISC_REG_GPIO_18_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_18_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_DRV_POS))
#define MMSYS_MISC_REG_GPIO_18_PU                               MMSYS_MISC_REG_GPIO_18_PU
#define MMSYS_MISC_REG_GPIO_18_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_18_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_18_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_18_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_PU_POS)
#define MMSYS_MISC_REG_GPIO_18_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_18_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_PU_POS))
#define MMSYS_MISC_REG_GPIO_18_PD                               MMSYS_MISC_REG_GPIO_18_PD
#define MMSYS_MISC_REG_GPIO_18_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_18_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_18_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_18_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_PD_POS)
#define MMSYS_MISC_REG_GPIO_18_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_18_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_PD_POS))
#define MMSYS_MISC_REG_GPIO_18_FUNC_SEL                         MMSYS_MISC_REG_GPIO_18_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_18_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_18_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_18_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_18_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_18_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_18_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_19_IE                               MMSYS_MISC_REG_GPIO_19_IE
#define MMSYS_MISC_REG_GPIO_19_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_19_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_19_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_19_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_IE_POS)
#define MMSYS_MISC_REG_GPIO_19_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_19_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_IE_POS))
#define MMSYS_MISC_REG_GPIO_19_SMT                              MMSYS_MISC_REG_GPIO_19_SMT
#define MMSYS_MISC_REG_GPIO_19_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_19_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_19_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_19_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_SMT_POS)
#define MMSYS_MISC_REG_GPIO_19_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_19_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_SMT_POS))
#define MMSYS_MISC_REG_GPIO_19_DRV                              MMSYS_MISC_REG_GPIO_19_DRV
#define MMSYS_MISC_REG_GPIO_19_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_19_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_19_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_19_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_DRV_POS)
#define MMSYS_MISC_REG_GPIO_19_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_19_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_DRV_POS))
#define MMSYS_MISC_REG_GPIO_19_PU                               MMSYS_MISC_REG_GPIO_19_PU
#define MMSYS_MISC_REG_GPIO_19_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_19_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_19_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_19_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_PU_POS)
#define MMSYS_MISC_REG_GPIO_19_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_19_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_PU_POS))
#define MMSYS_MISC_REG_GPIO_19_PD                               MMSYS_MISC_REG_GPIO_19_PD
#define MMSYS_MISC_REG_GPIO_19_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_19_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_19_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_19_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_PD_POS)
#define MMSYS_MISC_REG_GPIO_19_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_19_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_PD_POS))
#define MMSYS_MISC_REG_GPIO_19_FUNC_SEL                         MMSYS_MISC_REG_GPIO_19_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_19_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_19_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_19_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_19_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_19_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_19_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_FUNC_SEL_POS))

/* 0x228 : GPIO_CFGCTL10 */
#define MMSYS_MISC_GPIO_CFGCTL10_OFFSET                         (0x228)
#define MMSYS_MISC_REG_GPIO_20_IE                               MMSYS_MISC_REG_GPIO_20_IE
#define MMSYS_MISC_REG_GPIO_20_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_20_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_20_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_20_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_IE_POS)
#define MMSYS_MISC_REG_GPIO_20_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_20_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_IE_POS))
#define MMSYS_MISC_REG_GPIO_20_SMT                              MMSYS_MISC_REG_GPIO_20_SMT
#define MMSYS_MISC_REG_GPIO_20_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_20_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_20_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_20_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_SMT_POS)
#define MMSYS_MISC_REG_GPIO_20_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_20_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_SMT_POS))
#define MMSYS_MISC_REG_GPIO_20_DRV                              MMSYS_MISC_REG_GPIO_20_DRV
#define MMSYS_MISC_REG_GPIO_20_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_20_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_20_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_20_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_DRV_POS)
#define MMSYS_MISC_REG_GPIO_20_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_20_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_DRV_POS))
#define MMSYS_MISC_REG_GPIO_20_PU                               MMSYS_MISC_REG_GPIO_20_PU
#define MMSYS_MISC_REG_GPIO_20_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_20_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_20_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_20_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_PU_POS)
#define MMSYS_MISC_REG_GPIO_20_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_20_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_PU_POS))
#define MMSYS_MISC_REG_GPIO_20_PD                               MMSYS_MISC_REG_GPIO_20_PD
#define MMSYS_MISC_REG_GPIO_20_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_20_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_20_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_20_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_PD_POS)
#define MMSYS_MISC_REG_GPIO_20_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_20_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_PD_POS))
#define MMSYS_MISC_REG_GPIO_20_FUNC_SEL                         MMSYS_MISC_REG_GPIO_20_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_20_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_20_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_20_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_20_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_20_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_20_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_21_IE                               MMSYS_MISC_REG_GPIO_21_IE
#define MMSYS_MISC_REG_GPIO_21_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_21_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_21_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_21_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_IE_POS)
#define MMSYS_MISC_REG_GPIO_21_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_21_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_IE_POS))
#define MMSYS_MISC_REG_GPIO_21_SMT                              MMSYS_MISC_REG_GPIO_21_SMT
#define MMSYS_MISC_REG_GPIO_21_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_21_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_21_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_21_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_SMT_POS)
#define MMSYS_MISC_REG_GPIO_21_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_21_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_SMT_POS))
#define MMSYS_MISC_REG_GPIO_21_DRV                              MMSYS_MISC_REG_GPIO_21_DRV
#define MMSYS_MISC_REG_GPIO_21_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_21_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_21_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_21_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_DRV_POS)
#define MMSYS_MISC_REG_GPIO_21_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_21_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_DRV_POS))
#define MMSYS_MISC_REG_GPIO_21_PU                               MMSYS_MISC_REG_GPIO_21_PU
#define MMSYS_MISC_REG_GPIO_21_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_21_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_21_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_21_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_PU_POS)
#define MMSYS_MISC_REG_GPIO_21_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_21_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_PU_POS))
#define MMSYS_MISC_REG_GPIO_21_PD                               MMSYS_MISC_REG_GPIO_21_PD
#define MMSYS_MISC_REG_GPIO_21_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_21_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_21_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_21_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_PD_POS)
#define MMSYS_MISC_REG_GPIO_21_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_21_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_PD_POS))
#define MMSYS_MISC_REG_GPIO_21_FUNC_SEL                         MMSYS_MISC_REG_GPIO_21_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_21_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_21_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_21_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_21_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_21_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_21_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_FUNC_SEL_POS))

/* 0x22C : GPIO_CFGCTL11 */
#define MMSYS_MISC_GPIO_CFGCTL11_OFFSET                         (0x22C)
#define MMSYS_MISC_REG_GPIO_22_IE                               MMSYS_MISC_REG_GPIO_22_IE
#define MMSYS_MISC_REG_GPIO_22_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_22_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_22_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_22_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_IE_POS)
#define MMSYS_MISC_REG_GPIO_22_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_22_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_IE_POS))
#define MMSYS_MISC_REG_GPIO_22_SMT                              MMSYS_MISC_REG_GPIO_22_SMT
#define MMSYS_MISC_REG_GPIO_22_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_22_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_22_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_22_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_SMT_POS)
#define MMSYS_MISC_REG_GPIO_22_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_22_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_SMT_POS))
#define MMSYS_MISC_REG_GPIO_22_DRV                              MMSYS_MISC_REG_GPIO_22_DRV
#define MMSYS_MISC_REG_GPIO_22_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_22_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_22_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_22_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_DRV_POS)
#define MMSYS_MISC_REG_GPIO_22_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_22_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_DRV_POS))
#define MMSYS_MISC_REG_GPIO_22_PU                               MMSYS_MISC_REG_GPIO_22_PU
#define MMSYS_MISC_REG_GPIO_22_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_22_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_22_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_22_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_PU_POS)
#define MMSYS_MISC_REG_GPIO_22_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_22_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_PU_POS))
#define MMSYS_MISC_REG_GPIO_22_PD                               MMSYS_MISC_REG_GPIO_22_PD
#define MMSYS_MISC_REG_GPIO_22_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_22_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_22_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_22_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_PD_POS)
#define MMSYS_MISC_REG_GPIO_22_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_22_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_PD_POS))
#define MMSYS_MISC_REG_GPIO_22_FUNC_SEL                         MMSYS_MISC_REG_GPIO_22_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_22_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_22_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_22_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_22_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_22_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_22_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_23_IE                               MMSYS_MISC_REG_GPIO_23_IE
#define MMSYS_MISC_REG_GPIO_23_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_23_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_23_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_23_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_IE_POS)
#define MMSYS_MISC_REG_GPIO_23_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_23_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_IE_POS))
#define MMSYS_MISC_REG_GPIO_23_SMT                              MMSYS_MISC_REG_GPIO_23_SMT
#define MMSYS_MISC_REG_GPIO_23_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_23_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_23_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_23_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_SMT_POS)
#define MMSYS_MISC_REG_GPIO_23_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_23_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_SMT_POS))
#define MMSYS_MISC_REG_GPIO_23_DRV                              MMSYS_MISC_REG_GPIO_23_DRV
#define MMSYS_MISC_REG_GPIO_23_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_23_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_23_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_23_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_DRV_POS)
#define MMSYS_MISC_REG_GPIO_23_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_23_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_DRV_POS))
#define MMSYS_MISC_REG_GPIO_23_PU                               MMSYS_MISC_REG_GPIO_23_PU
#define MMSYS_MISC_REG_GPIO_23_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_23_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_23_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_23_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_PU_POS)
#define MMSYS_MISC_REG_GPIO_23_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_23_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_PU_POS))
#define MMSYS_MISC_REG_GPIO_23_PD                               MMSYS_MISC_REG_GPIO_23_PD
#define MMSYS_MISC_REG_GPIO_23_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_23_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_23_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_23_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_PD_POS)
#define MMSYS_MISC_REG_GPIO_23_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_23_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_PD_POS))
#define MMSYS_MISC_REG_GPIO_23_FUNC_SEL                         MMSYS_MISC_REG_GPIO_23_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_23_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_23_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_23_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_23_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_23_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_23_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_FUNC_SEL_POS))

/* 0x230 : GPIO_CFGCTL12 */
#define MMSYS_MISC_GPIO_CFGCTL12_OFFSET                         (0x230)
#define MMSYS_MISC_REG_GPIO_24_IE                               MMSYS_MISC_REG_GPIO_24_IE
#define MMSYS_MISC_REG_GPIO_24_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_24_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_24_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_24_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_IE_POS)
#define MMSYS_MISC_REG_GPIO_24_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_24_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_IE_POS))
#define MMSYS_MISC_REG_GPIO_24_SMT                              MMSYS_MISC_REG_GPIO_24_SMT
#define MMSYS_MISC_REG_GPIO_24_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_24_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_24_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_24_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_SMT_POS)
#define MMSYS_MISC_REG_GPIO_24_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_24_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_SMT_POS))
#define MMSYS_MISC_REG_GPIO_24_DRV                              MMSYS_MISC_REG_GPIO_24_DRV
#define MMSYS_MISC_REG_GPIO_24_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_24_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_24_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_24_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_DRV_POS)
#define MMSYS_MISC_REG_GPIO_24_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_24_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_DRV_POS))
#define MMSYS_MISC_REG_GPIO_24_PU                               MMSYS_MISC_REG_GPIO_24_PU
#define MMSYS_MISC_REG_GPIO_24_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_24_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_24_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_24_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_PU_POS)
#define MMSYS_MISC_REG_GPIO_24_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_24_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_PU_POS))
#define MMSYS_MISC_REG_GPIO_24_PD                               MMSYS_MISC_REG_GPIO_24_PD
#define MMSYS_MISC_REG_GPIO_24_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_24_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_24_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_24_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_PD_POS)
#define MMSYS_MISC_REG_GPIO_24_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_24_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_PD_POS))
#define MMSYS_MISC_REG_GPIO_24_FUNC_SEL                         MMSYS_MISC_REG_GPIO_24_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_24_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_24_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_24_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_24_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_24_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_24_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_25_IE                               MMSYS_MISC_REG_GPIO_25_IE
#define MMSYS_MISC_REG_GPIO_25_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_25_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_25_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_25_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_IE_POS)
#define MMSYS_MISC_REG_GPIO_25_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_25_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_IE_POS))
#define MMSYS_MISC_REG_GPIO_25_SMT                              MMSYS_MISC_REG_GPIO_25_SMT
#define MMSYS_MISC_REG_GPIO_25_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_25_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_25_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_25_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_SMT_POS)
#define MMSYS_MISC_REG_GPIO_25_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_25_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_SMT_POS))
#define MMSYS_MISC_REG_GPIO_25_DRV                              MMSYS_MISC_REG_GPIO_25_DRV
#define MMSYS_MISC_REG_GPIO_25_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_25_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_25_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_25_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_DRV_POS)
#define MMSYS_MISC_REG_GPIO_25_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_25_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_DRV_POS))
#define MMSYS_MISC_REG_GPIO_25_PU                               MMSYS_MISC_REG_GPIO_25_PU
#define MMSYS_MISC_REG_GPIO_25_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_25_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_25_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_25_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_PU_POS)
#define MMSYS_MISC_REG_GPIO_25_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_25_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_PU_POS))
#define MMSYS_MISC_REG_GPIO_25_PD                               MMSYS_MISC_REG_GPIO_25_PD
#define MMSYS_MISC_REG_GPIO_25_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_25_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_25_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_25_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_PD_POS)
#define MMSYS_MISC_REG_GPIO_25_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_25_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_PD_POS))
#define MMSYS_MISC_REG_GPIO_25_FUNC_SEL                         MMSYS_MISC_REG_GPIO_25_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_25_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_25_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_25_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_25_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_25_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_25_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_FUNC_SEL_POS))

/* 0x234 : GPIO_CFGCTL13 */
#define MMSYS_MISC_GPIO_CFGCTL13_OFFSET                         (0x234)
#define MMSYS_MISC_REG_GPIO_26_IE                               MMSYS_MISC_REG_GPIO_26_IE
#define MMSYS_MISC_REG_GPIO_26_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_26_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_26_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_26_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_IE_POS)
#define MMSYS_MISC_REG_GPIO_26_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_26_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_IE_POS))
#define MMSYS_MISC_REG_GPIO_26_SMT                              MMSYS_MISC_REG_GPIO_26_SMT
#define MMSYS_MISC_REG_GPIO_26_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_26_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_26_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_26_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_SMT_POS)
#define MMSYS_MISC_REG_GPIO_26_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_26_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_SMT_POS))
#define MMSYS_MISC_REG_GPIO_26_DRV                              MMSYS_MISC_REG_GPIO_26_DRV
#define MMSYS_MISC_REG_GPIO_26_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_26_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_26_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_26_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_DRV_POS)
#define MMSYS_MISC_REG_GPIO_26_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_26_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_DRV_POS))
#define MMSYS_MISC_REG_GPIO_26_PU                               MMSYS_MISC_REG_GPIO_26_PU
#define MMSYS_MISC_REG_GPIO_26_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_26_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_26_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_26_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_PU_POS)
#define MMSYS_MISC_REG_GPIO_26_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_26_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_PU_POS))
#define MMSYS_MISC_REG_GPIO_26_PD                               MMSYS_MISC_REG_GPIO_26_PD
#define MMSYS_MISC_REG_GPIO_26_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_26_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_26_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_26_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_PD_POS)
#define MMSYS_MISC_REG_GPIO_26_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_26_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_PD_POS))
#define MMSYS_MISC_REG_GPIO_26_FUNC_SEL                         MMSYS_MISC_REG_GPIO_26_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_26_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_26_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_26_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_26_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_26_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_26_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_27_IE                               MMSYS_MISC_REG_GPIO_27_IE
#define MMSYS_MISC_REG_GPIO_27_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_27_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_27_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_27_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_IE_POS)
#define MMSYS_MISC_REG_GPIO_27_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_27_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_IE_POS))
#define MMSYS_MISC_REG_GPIO_27_SMT                              MMSYS_MISC_REG_GPIO_27_SMT
#define MMSYS_MISC_REG_GPIO_27_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_27_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_27_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_27_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_SMT_POS)
#define MMSYS_MISC_REG_GPIO_27_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_27_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_SMT_POS))
#define MMSYS_MISC_REG_GPIO_27_DRV                              MMSYS_MISC_REG_GPIO_27_DRV
#define MMSYS_MISC_REG_GPIO_27_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_27_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_27_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_27_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_DRV_POS)
#define MMSYS_MISC_REG_GPIO_27_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_27_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_DRV_POS))
#define MMSYS_MISC_REG_GPIO_27_PU                               MMSYS_MISC_REG_GPIO_27_PU
#define MMSYS_MISC_REG_GPIO_27_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_27_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_27_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_27_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_PU_POS)
#define MMSYS_MISC_REG_GPIO_27_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_27_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_PU_POS))
#define MMSYS_MISC_REG_GPIO_27_PD                               MMSYS_MISC_REG_GPIO_27_PD
#define MMSYS_MISC_REG_GPIO_27_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_27_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_27_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_27_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_PD_POS)
#define MMSYS_MISC_REG_GPIO_27_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_27_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_PD_POS))
#define MMSYS_MISC_REG_GPIO_27_FUNC_SEL                         MMSYS_MISC_REG_GPIO_27_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_27_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_27_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_27_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_27_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_27_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_27_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_FUNC_SEL_POS))

/* 0x238 : GPIO_CFGCTL14 */
#define MMSYS_MISC_GPIO_CFGCTL14_OFFSET                         (0x238)
#define MMSYS_MISC_REG_GPIO_28_IE                               MMSYS_MISC_REG_GPIO_28_IE
#define MMSYS_MISC_REG_GPIO_28_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_28_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_28_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_28_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_IE_POS)
#define MMSYS_MISC_REG_GPIO_28_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_28_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_IE_POS))
#define MMSYS_MISC_REG_GPIO_28_SMT                              MMSYS_MISC_REG_GPIO_28_SMT
#define MMSYS_MISC_REG_GPIO_28_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_28_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_28_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_28_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_SMT_POS)
#define MMSYS_MISC_REG_GPIO_28_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_28_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_SMT_POS))
#define MMSYS_MISC_REG_GPIO_28_DRV                              MMSYS_MISC_REG_GPIO_28_DRV
#define MMSYS_MISC_REG_GPIO_28_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_28_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_28_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_28_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_DRV_POS)
#define MMSYS_MISC_REG_GPIO_28_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_28_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_DRV_POS))
#define MMSYS_MISC_REG_GPIO_28_PU                               MMSYS_MISC_REG_GPIO_28_PU
#define MMSYS_MISC_REG_GPIO_28_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_28_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_28_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_28_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_PU_POS)
#define MMSYS_MISC_REG_GPIO_28_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_28_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_PU_POS))
#define MMSYS_MISC_REG_GPIO_28_PD                               MMSYS_MISC_REG_GPIO_28_PD
#define MMSYS_MISC_REG_GPIO_28_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_28_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_28_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_28_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_PD_POS)
#define MMSYS_MISC_REG_GPIO_28_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_28_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_PD_POS))
#define MMSYS_MISC_REG_GPIO_28_FUNC_SEL                         MMSYS_MISC_REG_GPIO_28_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_28_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_28_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_28_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_28_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_28_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_28_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_29_IE                               MMSYS_MISC_REG_GPIO_29_IE
#define MMSYS_MISC_REG_GPIO_29_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_29_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_29_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_29_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_IE_POS)
#define MMSYS_MISC_REG_GPIO_29_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_29_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_IE_POS))
#define MMSYS_MISC_REG_GPIO_29_SMT                              MMSYS_MISC_REG_GPIO_29_SMT
#define MMSYS_MISC_REG_GPIO_29_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_29_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_29_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_29_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_SMT_POS)
#define MMSYS_MISC_REG_GPIO_29_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_29_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_SMT_POS))
#define MMSYS_MISC_REG_GPIO_29_DRV                              MMSYS_MISC_REG_GPIO_29_DRV
#define MMSYS_MISC_REG_GPIO_29_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_29_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_29_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_29_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_DRV_POS)
#define MMSYS_MISC_REG_GPIO_29_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_29_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_DRV_POS))
#define MMSYS_MISC_REG_GPIO_29_PU                               MMSYS_MISC_REG_GPIO_29_PU
#define MMSYS_MISC_REG_GPIO_29_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_29_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_29_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_29_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_PU_POS)
#define MMSYS_MISC_REG_GPIO_29_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_29_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_PU_POS))
#define MMSYS_MISC_REG_GPIO_29_PD                               MMSYS_MISC_REG_GPIO_29_PD
#define MMSYS_MISC_REG_GPIO_29_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_29_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_29_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_29_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_PD_POS)
#define MMSYS_MISC_REG_GPIO_29_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_29_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_PD_POS))
#define MMSYS_MISC_REG_GPIO_29_FUNC_SEL                         MMSYS_MISC_REG_GPIO_29_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_29_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_29_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_29_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_29_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_29_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_29_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_FUNC_SEL_POS))

/* 0x23C : GPIO_CFGCTL15 */
#define MMSYS_MISC_GPIO_CFGCTL15_OFFSET                         (0x23C)
#define MMSYS_MISC_REG_GPIO_30_IE                               MMSYS_MISC_REG_GPIO_30_IE
#define MMSYS_MISC_REG_GPIO_30_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_30_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_30_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_30_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_IE_POS)
#define MMSYS_MISC_REG_GPIO_30_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_30_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_IE_POS))
#define MMSYS_MISC_REG_GPIO_30_SMT                              MMSYS_MISC_REG_GPIO_30_SMT
#define MMSYS_MISC_REG_GPIO_30_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_30_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_30_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_30_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_SMT_POS)
#define MMSYS_MISC_REG_GPIO_30_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_30_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_SMT_POS))
#define MMSYS_MISC_REG_GPIO_30_DRV                              MMSYS_MISC_REG_GPIO_30_DRV
#define MMSYS_MISC_REG_GPIO_30_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_30_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_30_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_30_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_DRV_POS)
#define MMSYS_MISC_REG_GPIO_30_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_30_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_DRV_POS))
#define MMSYS_MISC_REG_GPIO_30_PU                               MMSYS_MISC_REG_GPIO_30_PU
#define MMSYS_MISC_REG_GPIO_30_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_30_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_30_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_30_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_PU_POS)
#define MMSYS_MISC_REG_GPIO_30_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_30_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_PU_POS))
#define MMSYS_MISC_REG_GPIO_30_PD                               MMSYS_MISC_REG_GPIO_30_PD
#define MMSYS_MISC_REG_GPIO_30_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_30_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_30_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_30_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_PD_POS)
#define MMSYS_MISC_REG_GPIO_30_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_30_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_PD_POS))
#define MMSYS_MISC_REG_GPIO_30_FUNC_SEL                         MMSYS_MISC_REG_GPIO_30_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_30_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_30_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_30_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_30_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_30_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_30_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_31_IE                               MMSYS_MISC_REG_GPIO_31_IE
#define MMSYS_MISC_REG_GPIO_31_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_31_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_31_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_31_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_IE_POS)
#define MMSYS_MISC_REG_GPIO_31_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_31_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_IE_POS))
#define MMSYS_MISC_REG_GPIO_31_SMT                              MMSYS_MISC_REG_GPIO_31_SMT
#define MMSYS_MISC_REG_GPIO_31_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_31_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_31_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_31_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_SMT_POS)
#define MMSYS_MISC_REG_GPIO_31_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_31_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_SMT_POS))
#define MMSYS_MISC_REG_GPIO_31_DRV                              MMSYS_MISC_REG_GPIO_31_DRV
#define MMSYS_MISC_REG_GPIO_31_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_31_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_31_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_31_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_DRV_POS)
#define MMSYS_MISC_REG_GPIO_31_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_31_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_DRV_POS))
#define MMSYS_MISC_REG_GPIO_31_PU                               MMSYS_MISC_REG_GPIO_31_PU
#define MMSYS_MISC_REG_GPIO_31_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_31_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_31_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_31_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_PU_POS)
#define MMSYS_MISC_REG_GPIO_31_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_31_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_PU_POS))
#define MMSYS_MISC_REG_GPIO_31_PD                               MMSYS_MISC_REG_GPIO_31_PD
#define MMSYS_MISC_REG_GPIO_31_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_31_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_31_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_31_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_PD_POS)
#define MMSYS_MISC_REG_GPIO_31_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_31_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_PD_POS))
#define MMSYS_MISC_REG_GPIO_31_FUNC_SEL                         MMSYS_MISC_REG_GPIO_31_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_31_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_31_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_31_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_31_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_31_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_31_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_FUNC_SEL_POS))

/* 0x240 : GPIO_CFGCTL16 */
#define MMSYS_MISC_GPIO_CFGCTL16_OFFSET                         (0x240)
#define MMSYS_MISC_REG_GPIO_32_IE                               MMSYS_MISC_REG_GPIO_32_IE
#define MMSYS_MISC_REG_GPIO_32_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_32_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_32_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_32_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_IE_POS)
#define MMSYS_MISC_REG_GPIO_32_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_32_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_IE_POS))
#define MMSYS_MISC_REG_GPIO_32_SMT                              MMSYS_MISC_REG_GPIO_32_SMT
#define MMSYS_MISC_REG_GPIO_32_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_32_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_32_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_32_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_SMT_POS)
#define MMSYS_MISC_REG_GPIO_32_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_32_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_SMT_POS))
#define MMSYS_MISC_REG_GPIO_32_DRV                              MMSYS_MISC_REG_GPIO_32_DRV
#define MMSYS_MISC_REG_GPIO_32_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_32_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_32_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_32_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_DRV_POS)
#define MMSYS_MISC_REG_GPIO_32_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_32_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_DRV_POS))
#define MMSYS_MISC_REG_GPIO_32_PU                               MMSYS_MISC_REG_GPIO_32_PU
#define MMSYS_MISC_REG_GPIO_32_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_32_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_32_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_32_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_PU_POS)
#define MMSYS_MISC_REG_GPIO_32_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_32_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_PU_POS))
#define MMSYS_MISC_REG_GPIO_32_PD                               MMSYS_MISC_REG_GPIO_32_PD
#define MMSYS_MISC_REG_GPIO_32_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_32_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_32_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_32_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_PD_POS)
#define MMSYS_MISC_REG_GPIO_32_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_32_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_PD_POS))
#define MMSYS_MISC_REG_GPIO_32_FUNC_SEL                         MMSYS_MISC_REG_GPIO_32_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_32_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_32_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_32_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_32_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_32_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_32_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_33_IE                               MMSYS_MISC_REG_GPIO_33_IE
#define MMSYS_MISC_REG_GPIO_33_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_33_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_33_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_33_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_IE_POS)
#define MMSYS_MISC_REG_GPIO_33_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_33_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_IE_POS))
#define MMSYS_MISC_REG_GPIO_33_SMT                              MMSYS_MISC_REG_GPIO_33_SMT
#define MMSYS_MISC_REG_GPIO_33_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_33_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_33_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_33_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_SMT_POS)
#define MMSYS_MISC_REG_GPIO_33_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_33_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_SMT_POS))
#define MMSYS_MISC_REG_GPIO_33_DRV                              MMSYS_MISC_REG_GPIO_33_DRV
#define MMSYS_MISC_REG_GPIO_33_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_33_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_33_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_33_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_DRV_POS)
#define MMSYS_MISC_REG_GPIO_33_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_33_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_DRV_POS))
#define MMSYS_MISC_REG_GPIO_33_PU                               MMSYS_MISC_REG_GPIO_33_PU
#define MMSYS_MISC_REG_GPIO_33_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_33_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_33_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_33_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_PU_POS)
#define MMSYS_MISC_REG_GPIO_33_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_33_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_PU_POS))
#define MMSYS_MISC_REG_GPIO_33_PD                               MMSYS_MISC_REG_GPIO_33_PD
#define MMSYS_MISC_REG_GPIO_33_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_33_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_33_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_33_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_PD_POS)
#define MMSYS_MISC_REG_GPIO_33_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_33_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_PD_POS))
#define MMSYS_MISC_REG_GPIO_33_FUNC_SEL                         MMSYS_MISC_REG_GPIO_33_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_33_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_33_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_33_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_33_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_33_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_33_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_FUNC_SEL_POS))

/* 0x244 : GPIO_CFGCTL17 */
#define MMSYS_MISC_GPIO_CFGCTL17_OFFSET                         (0x244)
#define MMSYS_MISC_REG_GPIO_34_IE                               MMSYS_MISC_REG_GPIO_34_IE
#define MMSYS_MISC_REG_GPIO_34_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_34_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_34_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_34_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_IE_POS)
#define MMSYS_MISC_REG_GPIO_34_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_34_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_IE_POS))
#define MMSYS_MISC_REG_GPIO_34_SMT                              MMSYS_MISC_REG_GPIO_34_SMT
#define MMSYS_MISC_REG_GPIO_34_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_34_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_34_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_34_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_SMT_POS)
#define MMSYS_MISC_REG_GPIO_34_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_34_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_SMT_POS))
#define MMSYS_MISC_REG_GPIO_34_DRV                              MMSYS_MISC_REG_GPIO_34_DRV
#define MMSYS_MISC_REG_GPIO_34_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_34_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_34_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_34_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_DRV_POS)
#define MMSYS_MISC_REG_GPIO_34_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_34_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_DRV_POS))
#define MMSYS_MISC_REG_GPIO_34_PU                               MMSYS_MISC_REG_GPIO_34_PU
#define MMSYS_MISC_REG_GPIO_34_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_34_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_34_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_34_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_PU_POS)
#define MMSYS_MISC_REG_GPIO_34_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_34_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_PU_POS))
#define MMSYS_MISC_REG_GPIO_34_PD                               MMSYS_MISC_REG_GPIO_34_PD
#define MMSYS_MISC_REG_GPIO_34_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_34_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_34_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_34_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_PD_POS)
#define MMSYS_MISC_REG_GPIO_34_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_34_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_PD_POS))
#define MMSYS_MISC_REG_GPIO_34_FUNC_SEL                         MMSYS_MISC_REG_GPIO_34_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_34_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_34_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_34_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_34_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_34_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_34_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_35_IE                               MMSYS_MISC_REG_GPIO_35_IE
#define MMSYS_MISC_REG_GPIO_35_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_35_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_35_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_35_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_IE_POS)
#define MMSYS_MISC_REG_GPIO_35_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_35_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_IE_POS))
#define MMSYS_MISC_REG_GPIO_35_SMT                              MMSYS_MISC_REG_GPIO_35_SMT
#define MMSYS_MISC_REG_GPIO_35_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_35_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_35_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_35_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_SMT_POS)
#define MMSYS_MISC_REG_GPIO_35_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_35_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_SMT_POS))
#define MMSYS_MISC_REG_GPIO_35_DRV                              MMSYS_MISC_REG_GPIO_35_DRV
#define MMSYS_MISC_REG_GPIO_35_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_35_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_35_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_35_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_DRV_POS)
#define MMSYS_MISC_REG_GPIO_35_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_35_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_DRV_POS))
#define MMSYS_MISC_REG_GPIO_35_PU                               MMSYS_MISC_REG_GPIO_35_PU
#define MMSYS_MISC_REG_GPIO_35_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_35_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_35_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_35_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_PU_POS)
#define MMSYS_MISC_REG_GPIO_35_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_35_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_PU_POS))
#define MMSYS_MISC_REG_GPIO_35_PD                               MMSYS_MISC_REG_GPIO_35_PD
#define MMSYS_MISC_REG_GPIO_35_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_35_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_35_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_35_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_PD_POS)
#define MMSYS_MISC_REG_GPIO_35_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_35_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_PD_POS))
#define MMSYS_MISC_REG_GPIO_35_FUNC_SEL                         MMSYS_MISC_REG_GPIO_35_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_35_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_35_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_35_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_35_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_35_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_35_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_FUNC_SEL_POS))

/* 0x248 : GPIO_CFGCTL18 */
#define MMSYS_MISC_GPIO_CFGCTL18_OFFSET                         (0x248)
#define MMSYS_MISC_REG_GPIO_36_IE                               MMSYS_MISC_REG_GPIO_36_IE
#define MMSYS_MISC_REG_GPIO_36_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_36_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_36_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_36_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_IE_POS)
#define MMSYS_MISC_REG_GPIO_36_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_36_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_IE_POS))
#define MMSYS_MISC_REG_GPIO_36_SMT                              MMSYS_MISC_REG_GPIO_36_SMT
#define MMSYS_MISC_REG_GPIO_36_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_36_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_36_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_36_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_SMT_POS)
#define MMSYS_MISC_REG_GPIO_36_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_36_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_SMT_POS))
#define MMSYS_MISC_REG_GPIO_36_DRV                              MMSYS_MISC_REG_GPIO_36_DRV
#define MMSYS_MISC_REG_GPIO_36_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_36_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_36_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_36_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_DRV_POS)
#define MMSYS_MISC_REG_GPIO_36_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_36_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_DRV_POS))
#define MMSYS_MISC_REG_GPIO_36_PU                               MMSYS_MISC_REG_GPIO_36_PU
#define MMSYS_MISC_REG_GPIO_36_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_36_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_36_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_36_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_PU_POS)
#define MMSYS_MISC_REG_GPIO_36_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_36_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_PU_POS))
#define MMSYS_MISC_REG_GPIO_36_PD                               MMSYS_MISC_REG_GPIO_36_PD
#define MMSYS_MISC_REG_GPIO_36_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_36_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_36_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_36_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_PD_POS)
#define MMSYS_MISC_REG_GPIO_36_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_36_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_PD_POS))
#define MMSYS_MISC_REG_GPIO_36_FUNC_SEL                         MMSYS_MISC_REG_GPIO_36_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_36_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_36_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_36_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_36_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_36_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_36_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_37_IE                               MMSYS_MISC_REG_GPIO_37_IE
#define MMSYS_MISC_REG_GPIO_37_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_37_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_37_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_37_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_IE_POS)
#define MMSYS_MISC_REG_GPIO_37_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_37_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_IE_POS))
#define MMSYS_MISC_REG_GPIO_37_SMT                              MMSYS_MISC_REG_GPIO_37_SMT
#define MMSYS_MISC_REG_GPIO_37_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_37_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_37_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_37_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_SMT_POS)
#define MMSYS_MISC_REG_GPIO_37_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_37_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_SMT_POS))
#define MMSYS_MISC_REG_GPIO_37_DRV                              MMSYS_MISC_REG_GPIO_37_DRV
#define MMSYS_MISC_REG_GPIO_37_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_37_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_37_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_37_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_DRV_POS)
#define MMSYS_MISC_REG_GPIO_37_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_37_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_DRV_POS))
#define MMSYS_MISC_REG_GPIO_37_PU                               MMSYS_MISC_REG_GPIO_37_PU
#define MMSYS_MISC_REG_GPIO_37_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_37_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_37_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_37_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_PU_POS)
#define MMSYS_MISC_REG_GPIO_37_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_37_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_PU_POS))
#define MMSYS_MISC_REG_GPIO_37_PD                               MMSYS_MISC_REG_GPIO_37_PD
#define MMSYS_MISC_REG_GPIO_37_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_37_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_37_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_37_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_PD_POS)
#define MMSYS_MISC_REG_GPIO_37_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_37_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_PD_POS))
#define MMSYS_MISC_REG_GPIO_37_FUNC_SEL                         MMSYS_MISC_REG_GPIO_37_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_37_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_37_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_37_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_37_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_37_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_37_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_FUNC_SEL_POS))

/* 0x24C : GPIO_CFGCTL19 */
#define MMSYS_MISC_GPIO_CFGCTL19_OFFSET                         (0x24C)
#define MMSYS_MISC_REG_GPIO_38_IE                               MMSYS_MISC_REG_GPIO_38_IE
#define MMSYS_MISC_REG_GPIO_38_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_38_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_38_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_38_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_IE_POS)
#define MMSYS_MISC_REG_GPIO_38_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_38_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_IE_POS))
#define MMSYS_MISC_REG_GPIO_38_SMT                              MMSYS_MISC_REG_GPIO_38_SMT
#define MMSYS_MISC_REG_GPIO_38_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_38_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_38_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_38_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_SMT_POS)
#define MMSYS_MISC_REG_GPIO_38_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_38_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_SMT_POS))
#define MMSYS_MISC_REG_GPIO_38_DRV                              MMSYS_MISC_REG_GPIO_38_DRV
#define MMSYS_MISC_REG_GPIO_38_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_38_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_38_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_38_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_DRV_POS)
#define MMSYS_MISC_REG_GPIO_38_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_38_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_DRV_POS))
#define MMSYS_MISC_REG_GPIO_38_PU                               MMSYS_MISC_REG_GPIO_38_PU
#define MMSYS_MISC_REG_GPIO_38_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_38_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_38_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_38_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_PU_POS)
#define MMSYS_MISC_REG_GPIO_38_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_38_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_PU_POS))
#define MMSYS_MISC_REG_GPIO_38_PD                               MMSYS_MISC_REG_GPIO_38_PD
#define MMSYS_MISC_REG_GPIO_38_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_38_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_38_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_38_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_PD_POS)
#define MMSYS_MISC_REG_GPIO_38_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_38_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_PD_POS))
#define MMSYS_MISC_REG_GPIO_38_FUNC_SEL                         MMSYS_MISC_REG_GPIO_38_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_38_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_38_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_38_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_38_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_38_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_38_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_39_IE                               MMSYS_MISC_REG_GPIO_39_IE
#define MMSYS_MISC_REG_GPIO_39_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_39_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_39_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_39_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_IE_POS)
#define MMSYS_MISC_REG_GPIO_39_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_39_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_IE_POS))
#define MMSYS_MISC_REG_GPIO_39_SMT                              MMSYS_MISC_REG_GPIO_39_SMT
#define MMSYS_MISC_REG_GPIO_39_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_39_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_39_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_39_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_SMT_POS)
#define MMSYS_MISC_REG_GPIO_39_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_39_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_SMT_POS))
#define MMSYS_MISC_REG_GPIO_39_DRV                              MMSYS_MISC_REG_GPIO_39_DRV
#define MMSYS_MISC_REG_GPIO_39_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_39_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_39_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_39_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_DRV_POS)
#define MMSYS_MISC_REG_GPIO_39_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_39_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_DRV_POS))
#define MMSYS_MISC_REG_GPIO_39_PU                               MMSYS_MISC_REG_GPIO_39_PU
#define MMSYS_MISC_REG_GPIO_39_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_39_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_39_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_39_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_PU_POS)
#define MMSYS_MISC_REG_GPIO_39_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_39_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_PU_POS))
#define MMSYS_MISC_REG_GPIO_39_PD                               MMSYS_MISC_REG_GPIO_39_PD
#define MMSYS_MISC_REG_GPIO_39_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_39_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_39_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_39_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_PD_POS)
#define MMSYS_MISC_REG_GPIO_39_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_39_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_PD_POS))
#define MMSYS_MISC_REG_GPIO_39_FUNC_SEL                         MMSYS_MISC_REG_GPIO_39_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_39_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_39_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_39_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_39_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_39_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_39_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_FUNC_SEL_POS))

/* 0x250 : GPIO_CFGCTL20 */
#define MMSYS_MISC_GPIO_CFGCTL20_OFFSET                         (0x250)
#define MMSYS_MISC_REG_GPIO_40_IE                               MMSYS_MISC_REG_GPIO_40_IE
#define MMSYS_MISC_REG_GPIO_40_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_40_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_40_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_40_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_IE_POS)
#define MMSYS_MISC_REG_GPIO_40_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_40_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_IE_POS))
#define MMSYS_MISC_REG_GPIO_40_SMT                              MMSYS_MISC_REG_GPIO_40_SMT
#define MMSYS_MISC_REG_GPIO_40_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_40_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_40_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_40_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_SMT_POS)
#define MMSYS_MISC_REG_GPIO_40_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_40_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_SMT_POS))
#define MMSYS_MISC_REG_GPIO_40_DRV                              MMSYS_MISC_REG_GPIO_40_DRV
#define MMSYS_MISC_REG_GPIO_40_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_40_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_40_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_40_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_DRV_POS)
#define MMSYS_MISC_REG_GPIO_40_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_40_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_DRV_POS))
#define MMSYS_MISC_REG_GPIO_40_PU                               MMSYS_MISC_REG_GPIO_40_PU
#define MMSYS_MISC_REG_GPIO_40_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_40_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_40_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_40_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_PU_POS)
#define MMSYS_MISC_REG_GPIO_40_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_40_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_PU_POS))
#define MMSYS_MISC_REG_GPIO_40_PD                               MMSYS_MISC_REG_GPIO_40_PD
#define MMSYS_MISC_REG_GPIO_40_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_40_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_40_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_40_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_PD_POS)
#define MMSYS_MISC_REG_GPIO_40_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_40_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_PD_POS))
#define MMSYS_MISC_REG_GPIO_40_FUNC_SEL                         MMSYS_MISC_REG_GPIO_40_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_40_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_40_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_40_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_40_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_40_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_40_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_41_IE                               MMSYS_MISC_REG_GPIO_41_IE
#define MMSYS_MISC_REG_GPIO_41_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_41_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_41_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_41_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_IE_POS)
#define MMSYS_MISC_REG_GPIO_41_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_41_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_IE_POS))
#define MMSYS_MISC_REG_GPIO_41_SMT                              MMSYS_MISC_REG_GPIO_41_SMT
#define MMSYS_MISC_REG_GPIO_41_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_41_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_41_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_41_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_SMT_POS)
#define MMSYS_MISC_REG_GPIO_41_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_41_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_SMT_POS))
#define MMSYS_MISC_REG_GPIO_41_DRV                              MMSYS_MISC_REG_GPIO_41_DRV
#define MMSYS_MISC_REG_GPIO_41_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_41_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_41_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_41_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_DRV_POS)
#define MMSYS_MISC_REG_GPIO_41_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_41_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_DRV_POS))
#define MMSYS_MISC_REG_GPIO_41_PU                               MMSYS_MISC_REG_GPIO_41_PU
#define MMSYS_MISC_REG_GPIO_41_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_41_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_41_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_41_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_PU_POS)
#define MMSYS_MISC_REG_GPIO_41_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_41_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_PU_POS))
#define MMSYS_MISC_REG_GPIO_41_PD                               MMSYS_MISC_REG_GPIO_41_PD
#define MMSYS_MISC_REG_GPIO_41_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_41_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_41_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_41_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_PD_POS)
#define MMSYS_MISC_REG_GPIO_41_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_41_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_PD_POS))
#define MMSYS_MISC_REG_GPIO_41_FUNC_SEL                         MMSYS_MISC_REG_GPIO_41_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_41_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_41_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_41_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_41_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_41_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_41_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_FUNC_SEL_POS))

/* 0x254 : GPIO_CFGCTL21 */
#define MMSYS_MISC_GPIO_CFGCTL21_OFFSET                         (0x254)
#define MMSYS_MISC_REG_GPIO_42_IE                               MMSYS_MISC_REG_GPIO_42_IE
#define MMSYS_MISC_REG_GPIO_42_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_42_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_42_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_42_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_IE_POS)
#define MMSYS_MISC_REG_GPIO_42_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_42_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_IE_POS))
#define MMSYS_MISC_REG_GPIO_42_SMT                              MMSYS_MISC_REG_GPIO_42_SMT
#define MMSYS_MISC_REG_GPIO_42_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_42_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_42_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_42_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_SMT_POS)
#define MMSYS_MISC_REG_GPIO_42_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_42_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_SMT_POS))
#define MMSYS_MISC_REG_GPIO_42_DRV                              MMSYS_MISC_REG_GPIO_42_DRV
#define MMSYS_MISC_REG_GPIO_42_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_42_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_42_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_42_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_DRV_POS)
#define MMSYS_MISC_REG_GPIO_42_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_42_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_DRV_POS))
#define MMSYS_MISC_REG_GPIO_42_PU                               MMSYS_MISC_REG_GPIO_42_PU
#define MMSYS_MISC_REG_GPIO_42_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_42_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_42_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_42_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_PU_POS)
#define MMSYS_MISC_REG_GPIO_42_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_42_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_PU_POS))
#define MMSYS_MISC_REG_GPIO_42_PD                               MMSYS_MISC_REG_GPIO_42_PD
#define MMSYS_MISC_REG_GPIO_42_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_42_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_42_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_42_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_PD_POS)
#define MMSYS_MISC_REG_GPIO_42_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_42_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_PD_POS))
#define MMSYS_MISC_REG_GPIO_42_FUNC_SEL                         MMSYS_MISC_REG_GPIO_42_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_42_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_42_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_42_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_42_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_42_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_42_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_43_IE                               MMSYS_MISC_REG_GPIO_43_IE
#define MMSYS_MISC_REG_GPIO_43_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_43_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_43_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_43_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_IE_POS)
#define MMSYS_MISC_REG_GPIO_43_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_43_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_IE_POS))
#define MMSYS_MISC_REG_GPIO_43_SMT                              MMSYS_MISC_REG_GPIO_43_SMT
#define MMSYS_MISC_REG_GPIO_43_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_43_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_43_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_43_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_SMT_POS)
#define MMSYS_MISC_REG_GPIO_43_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_43_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_SMT_POS))
#define MMSYS_MISC_REG_GPIO_43_DRV                              MMSYS_MISC_REG_GPIO_43_DRV
#define MMSYS_MISC_REG_GPIO_43_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_43_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_43_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_43_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_DRV_POS)
#define MMSYS_MISC_REG_GPIO_43_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_43_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_DRV_POS))
#define MMSYS_MISC_REG_GPIO_43_PU                               MMSYS_MISC_REG_GPIO_43_PU
#define MMSYS_MISC_REG_GPIO_43_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_43_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_43_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_43_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_PU_POS)
#define MMSYS_MISC_REG_GPIO_43_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_43_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_PU_POS))
#define MMSYS_MISC_REG_GPIO_43_PD                               MMSYS_MISC_REG_GPIO_43_PD
#define MMSYS_MISC_REG_GPIO_43_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_43_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_43_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_43_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_PD_POS)
#define MMSYS_MISC_REG_GPIO_43_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_43_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_PD_POS))
#define MMSYS_MISC_REG_GPIO_43_FUNC_SEL                         MMSYS_MISC_REG_GPIO_43_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_43_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_43_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_43_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_43_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_43_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_43_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_FUNC_SEL_POS))

/* 0x258 : GPIO_CFGCTL22 */
#define MMSYS_MISC_GPIO_CFGCTL22_OFFSET                         (0x258)
#define MMSYS_MISC_REG_GPIO_44_IE                               MMSYS_MISC_REG_GPIO_44_IE
#define MMSYS_MISC_REG_GPIO_44_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_44_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_44_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_44_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_IE_POS)
#define MMSYS_MISC_REG_GPIO_44_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_44_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_IE_POS))
#define MMSYS_MISC_REG_GPIO_44_SMT                              MMSYS_MISC_REG_GPIO_44_SMT
#define MMSYS_MISC_REG_GPIO_44_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_44_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_44_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_44_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_SMT_POS)
#define MMSYS_MISC_REG_GPIO_44_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_44_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_SMT_POS))
#define MMSYS_MISC_REG_GPIO_44_DRV                              MMSYS_MISC_REG_GPIO_44_DRV
#define MMSYS_MISC_REG_GPIO_44_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_44_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_44_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_44_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_DRV_POS)
#define MMSYS_MISC_REG_GPIO_44_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_44_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_DRV_POS))
#define MMSYS_MISC_REG_GPIO_44_PU                               MMSYS_MISC_REG_GPIO_44_PU
#define MMSYS_MISC_REG_GPIO_44_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_44_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_44_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_44_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_PU_POS)
#define MMSYS_MISC_REG_GPIO_44_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_44_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_PU_POS))
#define MMSYS_MISC_REG_GPIO_44_PD                               MMSYS_MISC_REG_GPIO_44_PD
#define MMSYS_MISC_REG_GPIO_44_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_44_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_44_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_44_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_PD_POS)
#define MMSYS_MISC_REG_GPIO_44_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_44_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_PD_POS))
#define MMSYS_MISC_REG_GPIO_44_FUNC_SEL                         MMSYS_MISC_REG_GPIO_44_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_44_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_44_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_44_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_44_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_44_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_44_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_45_IE                               MMSYS_MISC_REG_GPIO_45_IE
#define MMSYS_MISC_REG_GPIO_45_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_45_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_45_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_45_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_IE_POS)
#define MMSYS_MISC_REG_GPIO_45_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_45_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_IE_POS))
#define MMSYS_MISC_REG_GPIO_45_SMT                              MMSYS_MISC_REG_GPIO_45_SMT
#define MMSYS_MISC_REG_GPIO_45_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_45_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_45_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_45_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_SMT_POS)
#define MMSYS_MISC_REG_GPIO_45_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_45_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_SMT_POS))
#define MMSYS_MISC_REG_GPIO_45_DRV                              MMSYS_MISC_REG_GPIO_45_DRV
#define MMSYS_MISC_REG_GPIO_45_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_45_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_45_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_45_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_DRV_POS)
#define MMSYS_MISC_REG_GPIO_45_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_45_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_DRV_POS))
#define MMSYS_MISC_REG_GPIO_45_PU                               MMSYS_MISC_REG_GPIO_45_PU
#define MMSYS_MISC_REG_GPIO_45_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_45_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_45_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_45_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_PU_POS)
#define MMSYS_MISC_REG_GPIO_45_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_45_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_PU_POS))
#define MMSYS_MISC_REG_GPIO_45_PD                               MMSYS_MISC_REG_GPIO_45_PD
#define MMSYS_MISC_REG_GPIO_45_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_45_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_45_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_45_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_PD_POS)
#define MMSYS_MISC_REG_GPIO_45_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_45_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_PD_POS))
#define MMSYS_MISC_REG_GPIO_45_FUNC_SEL                         MMSYS_MISC_REG_GPIO_45_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_45_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_45_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_45_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_45_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_45_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_45_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_FUNC_SEL_POS))

/* 0x25C : GPIO_CFGCTL23 */
#define MMSYS_MISC_GPIO_CFGCTL23_OFFSET                         (0x25C)
#define MMSYS_MISC_REG_GPIO_46_IE                               MMSYS_MISC_REG_GPIO_46_IE
#define MMSYS_MISC_REG_GPIO_46_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_46_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_46_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_46_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_IE_POS)
#define MMSYS_MISC_REG_GPIO_46_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_46_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_IE_POS))
#define MMSYS_MISC_REG_GPIO_46_SMT                              MMSYS_MISC_REG_GPIO_46_SMT
#define MMSYS_MISC_REG_GPIO_46_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_46_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_46_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_46_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_SMT_POS)
#define MMSYS_MISC_REG_GPIO_46_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_46_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_SMT_POS))
#define MMSYS_MISC_REG_GPIO_46_DRV                              MMSYS_MISC_REG_GPIO_46_DRV
#define MMSYS_MISC_REG_GPIO_46_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_46_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_46_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_46_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_DRV_POS)
#define MMSYS_MISC_REG_GPIO_46_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_46_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_DRV_POS))
#define MMSYS_MISC_REG_GPIO_46_PU                               MMSYS_MISC_REG_GPIO_46_PU
#define MMSYS_MISC_REG_GPIO_46_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_46_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_46_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_46_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_PU_POS)
#define MMSYS_MISC_REG_GPIO_46_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_46_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_PU_POS))
#define MMSYS_MISC_REG_GPIO_46_PD                               MMSYS_MISC_REG_GPIO_46_PD
#define MMSYS_MISC_REG_GPIO_46_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_46_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_46_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_46_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_PD_POS)
#define MMSYS_MISC_REG_GPIO_46_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_46_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_PD_POS))
#define MMSYS_MISC_REG_GPIO_46_FUNC_SEL                         MMSYS_MISC_REG_GPIO_46_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_46_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_46_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_46_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_46_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_46_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_46_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_47_IE                               MMSYS_MISC_REG_GPIO_47_IE
#define MMSYS_MISC_REG_GPIO_47_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_47_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_47_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_47_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_IE_POS)
#define MMSYS_MISC_REG_GPIO_47_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_47_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_IE_POS))
#define MMSYS_MISC_REG_GPIO_47_SMT                              MMSYS_MISC_REG_GPIO_47_SMT
#define MMSYS_MISC_REG_GPIO_47_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_47_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_47_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_47_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_SMT_POS)
#define MMSYS_MISC_REG_GPIO_47_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_47_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_SMT_POS))
#define MMSYS_MISC_REG_GPIO_47_DRV                              MMSYS_MISC_REG_GPIO_47_DRV
#define MMSYS_MISC_REG_GPIO_47_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_47_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_47_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_47_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_DRV_POS)
#define MMSYS_MISC_REG_GPIO_47_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_47_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_DRV_POS))
#define MMSYS_MISC_REG_GPIO_47_PU                               MMSYS_MISC_REG_GPIO_47_PU
#define MMSYS_MISC_REG_GPIO_47_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_47_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_47_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_47_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_PU_POS)
#define MMSYS_MISC_REG_GPIO_47_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_47_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_PU_POS))
#define MMSYS_MISC_REG_GPIO_47_PD                               MMSYS_MISC_REG_GPIO_47_PD
#define MMSYS_MISC_REG_GPIO_47_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_47_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_47_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_47_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_PD_POS)
#define MMSYS_MISC_REG_GPIO_47_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_47_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_PD_POS))
#define MMSYS_MISC_REG_GPIO_47_FUNC_SEL                         MMSYS_MISC_REG_GPIO_47_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_47_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_47_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_47_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_47_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_47_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_47_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_FUNC_SEL_POS))

/* 0x260 : GPIO_CFGCTL24 */
#define MMSYS_MISC_GPIO_CFGCTL24_OFFSET                         (0x260)
#define MMSYS_MISC_REG_GPIO_48_IE                               MMSYS_MISC_REG_GPIO_48_IE
#define MMSYS_MISC_REG_GPIO_48_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_48_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_48_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_48_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_IE_POS)
#define MMSYS_MISC_REG_GPIO_48_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_48_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_IE_POS))
#define MMSYS_MISC_REG_GPIO_48_SMT                              MMSYS_MISC_REG_GPIO_48_SMT
#define MMSYS_MISC_REG_GPIO_48_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_48_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_48_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_48_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_SMT_POS)
#define MMSYS_MISC_REG_GPIO_48_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_48_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_SMT_POS))
#define MMSYS_MISC_REG_GPIO_48_DRV                              MMSYS_MISC_REG_GPIO_48_DRV
#define MMSYS_MISC_REG_GPIO_48_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_48_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_48_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_48_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_DRV_POS)
#define MMSYS_MISC_REG_GPIO_48_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_48_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_DRV_POS))
#define MMSYS_MISC_REG_GPIO_48_PU                               MMSYS_MISC_REG_GPIO_48_PU
#define MMSYS_MISC_REG_GPIO_48_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_48_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_48_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_48_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_PU_POS)
#define MMSYS_MISC_REG_GPIO_48_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_48_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_PU_POS))
#define MMSYS_MISC_REG_GPIO_48_PD                               MMSYS_MISC_REG_GPIO_48_PD
#define MMSYS_MISC_REG_GPIO_48_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_48_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_48_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_48_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_PD_POS)
#define MMSYS_MISC_REG_GPIO_48_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_48_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_PD_POS))
#define MMSYS_MISC_REG_GPIO_48_FUNC_SEL                         MMSYS_MISC_REG_GPIO_48_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_48_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_48_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_48_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_48_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_48_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_48_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_49_IE                               MMSYS_MISC_REG_GPIO_49_IE
#define MMSYS_MISC_REG_GPIO_49_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_49_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_49_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_49_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_IE_POS)
#define MMSYS_MISC_REG_GPIO_49_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_49_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_IE_POS))
#define MMSYS_MISC_REG_GPIO_49_SMT                              MMSYS_MISC_REG_GPIO_49_SMT
#define MMSYS_MISC_REG_GPIO_49_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_49_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_49_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_49_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_SMT_POS)
#define MMSYS_MISC_REG_GPIO_49_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_49_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_SMT_POS))
#define MMSYS_MISC_REG_GPIO_49_DRV                              MMSYS_MISC_REG_GPIO_49_DRV
#define MMSYS_MISC_REG_GPIO_49_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_49_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_49_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_49_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_DRV_POS)
#define MMSYS_MISC_REG_GPIO_49_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_49_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_DRV_POS))
#define MMSYS_MISC_REG_GPIO_49_PU                               MMSYS_MISC_REG_GPIO_49_PU
#define MMSYS_MISC_REG_GPIO_49_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_49_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_49_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_49_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_PU_POS)
#define MMSYS_MISC_REG_GPIO_49_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_49_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_PU_POS))
#define MMSYS_MISC_REG_GPIO_49_PD                               MMSYS_MISC_REG_GPIO_49_PD
#define MMSYS_MISC_REG_GPIO_49_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_49_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_49_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_49_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_PD_POS)
#define MMSYS_MISC_REG_GPIO_49_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_49_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_PD_POS))
#define MMSYS_MISC_REG_GPIO_49_FUNC_SEL                         MMSYS_MISC_REG_GPIO_49_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_49_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_49_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_49_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_49_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_49_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_49_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_FUNC_SEL_POS))

/* 0x264 : GPIO_CFGCTL25 */
#define MMSYS_MISC_GPIO_CFGCTL25_OFFSET                         (0x264)
#define MMSYS_MISC_REG_GPIO_50_IE                               MMSYS_MISC_REG_GPIO_50_IE
#define MMSYS_MISC_REG_GPIO_50_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_50_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_50_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_50_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_IE_POS)
#define MMSYS_MISC_REG_GPIO_50_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_50_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_IE_POS))
#define MMSYS_MISC_REG_GPIO_50_SMT                              MMSYS_MISC_REG_GPIO_50_SMT
#define MMSYS_MISC_REG_GPIO_50_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_50_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_50_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_50_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_SMT_POS)
#define MMSYS_MISC_REG_GPIO_50_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_50_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_SMT_POS))
#define MMSYS_MISC_REG_GPIO_50_DRV                              MMSYS_MISC_REG_GPIO_50_DRV
#define MMSYS_MISC_REG_GPIO_50_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_50_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_50_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_50_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_DRV_POS)
#define MMSYS_MISC_REG_GPIO_50_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_50_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_DRV_POS))
#define MMSYS_MISC_REG_GPIO_50_PU                               MMSYS_MISC_REG_GPIO_50_PU
#define MMSYS_MISC_REG_GPIO_50_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_50_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_50_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_50_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_PU_POS)
#define MMSYS_MISC_REG_GPIO_50_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_50_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_PU_POS))
#define MMSYS_MISC_REG_GPIO_50_PD                               MMSYS_MISC_REG_GPIO_50_PD
#define MMSYS_MISC_REG_GPIO_50_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_50_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_50_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_50_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_PD_POS)
#define MMSYS_MISC_REG_GPIO_50_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_50_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_PD_POS))
#define MMSYS_MISC_REG_GPIO_50_FUNC_SEL                         MMSYS_MISC_REG_GPIO_50_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_50_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_50_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_50_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_50_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_50_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_50_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_51_IE                               MMSYS_MISC_REG_GPIO_51_IE
#define MMSYS_MISC_REG_GPIO_51_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_51_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_51_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_51_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_IE_POS)
#define MMSYS_MISC_REG_GPIO_51_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_51_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_IE_POS))
#define MMSYS_MISC_REG_GPIO_51_SMT                              MMSYS_MISC_REG_GPIO_51_SMT
#define MMSYS_MISC_REG_GPIO_51_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_51_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_51_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_51_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_SMT_POS)
#define MMSYS_MISC_REG_GPIO_51_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_51_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_SMT_POS))
#define MMSYS_MISC_REG_GPIO_51_DRV                              MMSYS_MISC_REG_GPIO_51_DRV
#define MMSYS_MISC_REG_GPIO_51_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_51_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_51_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_51_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_DRV_POS)
#define MMSYS_MISC_REG_GPIO_51_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_51_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_DRV_POS))
#define MMSYS_MISC_REG_GPIO_51_PU                               MMSYS_MISC_REG_GPIO_51_PU
#define MMSYS_MISC_REG_GPIO_51_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_51_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_51_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_51_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_PU_POS)
#define MMSYS_MISC_REG_GPIO_51_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_51_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_PU_POS))
#define MMSYS_MISC_REG_GPIO_51_PD                               MMSYS_MISC_REG_GPIO_51_PD
#define MMSYS_MISC_REG_GPIO_51_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_51_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_51_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_51_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_PD_POS)
#define MMSYS_MISC_REG_GPIO_51_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_51_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_PD_POS))
#define MMSYS_MISC_REG_GPIO_51_FUNC_SEL                         MMSYS_MISC_REG_GPIO_51_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_51_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_51_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_51_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_51_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_51_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_51_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_FUNC_SEL_POS))

/* 0x268 : GPIO_CFGCTL26 */
#define MMSYS_MISC_GPIO_CFGCTL26_OFFSET                         (0x268)
#define MMSYS_MISC_REG_GPIO_52_IE                               MMSYS_MISC_REG_GPIO_52_IE
#define MMSYS_MISC_REG_GPIO_52_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_52_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_52_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_52_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_IE_POS)
#define MMSYS_MISC_REG_GPIO_52_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_52_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_IE_POS))
#define MMSYS_MISC_REG_GPIO_52_SMT                              MMSYS_MISC_REG_GPIO_52_SMT
#define MMSYS_MISC_REG_GPIO_52_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_52_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_52_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_52_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_SMT_POS)
#define MMSYS_MISC_REG_GPIO_52_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_52_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_SMT_POS))
#define MMSYS_MISC_REG_GPIO_52_DRV                              MMSYS_MISC_REG_GPIO_52_DRV
#define MMSYS_MISC_REG_GPIO_52_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_52_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_52_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_52_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_DRV_POS)
#define MMSYS_MISC_REG_GPIO_52_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_52_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_DRV_POS))
#define MMSYS_MISC_REG_GPIO_52_PU                               MMSYS_MISC_REG_GPIO_52_PU
#define MMSYS_MISC_REG_GPIO_52_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_52_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_52_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_52_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_PU_POS)
#define MMSYS_MISC_REG_GPIO_52_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_52_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_PU_POS))
#define MMSYS_MISC_REG_GPIO_52_PD                               MMSYS_MISC_REG_GPIO_52_PD
#define MMSYS_MISC_REG_GPIO_52_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_52_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_52_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_52_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_PD_POS)
#define MMSYS_MISC_REG_GPIO_52_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_52_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_PD_POS))
#define MMSYS_MISC_REG_GPIO_52_FUNC_SEL                         MMSYS_MISC_REG_GPIO_52_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_52_FUNC_SEL_POS                     (8U)
#define MMSYS_MISC_REG_GPIO_52_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_52_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_52_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_52_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_52_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_53_IE                               MMSYS_MISC_REG_GPIO_53_IE
#define MMSYS_MISC_REG_GPIO_53_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_53_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_53_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_53_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_IE_POS)
#define MMSYS_MISC_REG_GPIO_53_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_53_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_IE_POS))
#define MMSYS_MISC_REG_GPIO_53_SMT                              MMSYS_MISC_REG_GPIO_53_SMT
#define MMSYS_MISC_REG_GPIO_53_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_53_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_53_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_53_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_SMT_POS)
#define MMSYS_MISC_REG_GPIO_53_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_53_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_SMT_POS))
#define MMSYS_MISC_REG_GPIO_53_DRV                              MMSYS_MISC_REG_GPIO_53_DRV
#define MMSYS_MISC_REG_GPIO_53_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_53_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_53_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_53_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_DRV_POS)
#define MMSYS_MISC_REG_GPIO_53_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_53_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_DRV_POS))
#define MMSYS_MISC_REG_GPIO_53_PU                               MMSYS_MISC_REG_GPIO_53_PU
#define MMSYS_MISC_REG_GPIO_53_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_53_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_53_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_53_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_PU_POS)
#define MMSYS_MISC_REG_GPIO_53_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_53_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_PU_POS))
#define MMSYS_MISC_REG_GPIO_53_PD                               MMSYS_MISC_REG_GPIO_53_PD
#define MMSYS_MISC_REG_GPIO_53_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_53_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_53_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_53_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_PD_POS)
#define MMSYS_MISC_REG_GPIO_53_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_53_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_PD_POS))
#define MMSYS_MISC_REG_GPIO_53_FUNC_SEL                         MMSYS_MISC_REG_GPIO_53_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_53_FUNC_SEL_POS                     (24U)
#define MMSYS_MISC_REG_GPIO_53_FUNC_SEL_LEN                     (4U)
#define MMSYS_MISC_REG_GPIO_53_FUNC_SEL_MSK                     (((1U<<MMSYS_MISC_REG_GPIO_53_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_53_FUNC_SEL_UMSK                    (~(((1U<<MMSYS_MISC_REG_GPIO_53_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_FUNC_SEL_POS))

/* 0x26C : GPIO_CFGCTL27 */
#define MMSYS_MISC_GPIO_CFGCTL27_OFFSET                         (0x26C)
#define MMSYS_MISC_REG_GPIO_54_IE                               MMSYS_MISC_REG_GPIO_54_IE
#define MMSYS_MISC_REG_GPIO_54_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_54_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_54_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_54_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_IE_POS)
#define MMSYS_MISC_REG_GPIO_54_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_54_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_IE_POS))
#define MMSYS_MISC_REG_GPIO_54_SMT                              MMSYS_MISC_REG_GPIO_54_SMT
#define MMSYS_MISC_REG_GPIO_54_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_54_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_54_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_54_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_SMT_POS)
#define MMSYS_MISC_REG_GPIO_54_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_54_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_SMT_POS))
#define MMSYS_MISC_REG_GPIO_54_DRV                              MMSYS_MISC_REG_GPIO_54_DRV
#define MMSYS_MISC_REG_GPIO_54_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_54_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_54_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_54_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_DRV_POS)
#define MMSYS_MISC_REG_GPIO_54_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_54_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_DRV_POS))
#define MMSYS_MISC_REG_GPIO_54_PU                               MMSYS_MISC_REG_GPIO_54_PU
#define MMSYS_MISC_REG_GPIO_54_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_54_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_54_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_54_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_PU_POS)
#define MMSYS_MISC_REG_GPIO_54_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_54_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_PU_POS))
#define MMSYS_MISC_REG_GPIO_54_PD                               MMSYS_MISC_REG_GPIO_54_PD
#define MMSYS_MISC_REG_GPIO_54_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_54_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_54_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_54_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_PD_POS)
#define MMSYS_MISC_REG_GPIO_54_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_54_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_PD_POS))
#define MMSYS_MISC_REG_GPIO_55_IE                               MMSYS_MISC_REG_GPIO_55_IE
#define MMSYS_MISC_REG_GPIO_55_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_55_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_55_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_55_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_IE_POS)
#define MMSYS_MISC_REG_GPIO_55_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_55_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_IE_POS))
#define MMSYS_MISC_REG_GPIO_55_SMT                              MMSYS_MISC_REG_GPIO_55_SMT
#define MMSYS_MISC_REG_GPIO_55_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_55_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_55_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_55_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_SMT_POS)
#define MMSYS_MISC_REG_GPIO_55_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_55_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_SMT_POS))
#define MMSYS_MISC_REG_GPIO_55_DRV                              MMSYS_MISC_REG_GPIO_55_DRV
#define MMSYS_MISC_REG_GPIO_55_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_55_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_55_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_55_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_DRV_POS)
#define MMSYS_MISC_REG_GPIO_55_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_55_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_DRV_POS))
#define MMSYS_MISC_REG_GPIO_55_PU                               MMSYS_MISC_REG_GPIO_55_PU
#define MMSYS_MISC_REG_GPIO_55_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_55_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_55_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_55_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_PU_POS)
#define MMSYS_MISC_REG_GPIO_55_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_55_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_PU_POS))
#define MMSYS_MISC_REG_GPIO_55_PD                               MMSYS_MISC_REG_GPIO_55_PD
#define MMSYS_MISC_REG_GPIO_55_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_55_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_55_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_55_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_PD_POS)
#define MMSYS_MISC_REG_GPIO_55_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_55_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_PD_POS))

/* 0x270 : GPIO_CFGCTL28 */
#define MMSYS_MISC_GPIO_CFGCTL28_OFFSET                         (0x270)
#define MMSYS_MISC_REG_GPIO_56_IE                               MMSYS_MISC_REG_GPIO_56_IE
#define MMSYS_MISC_REG_GPIO_56_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_56_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_56_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_56_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_IE_POS)
#define MMSYS_MISC_REG_GPIO_56_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_56_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_IE_POS))
#define MMSYS_MISC_REG_GPIO_56_SMT                              MMSYS_MISC_REG_GPIO_56_SMT
#define MMSYS_MISC_REG_GPIO_56_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_56_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_56_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_56_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_SMT_POS)
#define MMSYS_MISC_REG_GPIO_56_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_56_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_SMT_POS))
#define MMSYS_MISC_REG_GPIO_56_DRV                              MMSYS_MISC_REG_GPIO_56_DRV
#define MMSYS_MISC_REG_GPIO_56_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_56_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_56_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_56_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_DRV_POS)
#define MMSYS_MISC_REG_GPIO_56_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_56_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_DRV_POS))
#define MMSYS_MISC_REG_GPIO_56_PU                               MMSYS_MISC_REG_GPIO_56_PU
#define MMSYS_MISC_REG_GPIO_56_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_56_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_56_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_56_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_PU_POS)
#define MMSYS_MISC_REG_GPIO_56_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_56_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_PU_POS))
#define MMSYS_MISC_REG_GPIO_56_PD                               MMSYS_MISC_REG_GPIO_56_PD
#define MMSYS_MISC_REG_GPIO_56_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_56_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_56_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_56_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_PD_POS)
#define MMSYS_MISC_REG_GPIO_56_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_56_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_PD_POS))
#define MMSYS_MISC_REG_GPIO_57_IE                               MMSYS_MISC_REG_GPIO_57_IE
#define MMSYS_MISC_REG_GPIO_57_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_57_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_57_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_57_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_IE_POS)
#define MMSYS_MISC_REG_GPIO_57_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_57_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_IE_POS))
#define MMSYS_MISC_REG_GPIO_57_SMT                              MMSYS_MISC_REG_GPIO_57_SMT
#define MMSYS_MISC_REG_GPIO_57_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_57_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_57_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_57_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_SMT_POS)
#define MMSYS_MISC_REG_GPIO_57_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_57_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_SMT_POS))
#define MMSYS_MISC_REG_GPIO_57_DRV                              MMSYS_MISC_REG_GPIO_57_DRV
#define MMSYS_MISC_REG_GPIO_57_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_57_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_57_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_57_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_DRV_POS)
#define MMSYS_MISC_REG_GPIO_57_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_57_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_DRV_POS))
#define MMSYS_MISC_REG_GPIO_57_PU                               MMSYS_MISC_REG_GPIO_57_PU
#define MMSYS_MISC_REG_GPIO_57_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_57_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_57_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_57_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_PU_POS)
#define MMSYS_MISC_REG_GPIO_57_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_57_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_PU_POS))
#define MMSYS_MISC_REG_GPIO_57_PD                               MMSYS_MISC_REG_GPIO_57_PD
#define MMSYS_MISC_REG_GPIO_57_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_57_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_57_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_57_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_PD_POS)
#define MMSYS_MISC_REG_GPIO_57_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_57_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_PD_POS))

/* 0x274 : GPIO_CFGCTL29 */
#define MMSYS_MISC_GPIO_CFGCTL29_OFFSET                         (0x274)
#define MMSYS_MISC_REG_GPIO_58_IE                               MMSYS_MISC_REG_GPIO_58_IE
#define MMSYS_MISC_REG_GPIO_58_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_58_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_58_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_58_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_IE_POS)
#define MMSYS_MISC_REG_GPIO_58_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_58_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_IE_POS))
#define MMSYS_MISC_REG_GPIO_58_SMT                              MMSYS_MISC_REG_GPIO_58_SMT
#define MMSYS_MISC_REG_GPIO_58_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_58_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_58_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_58_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_SMT_POS)
#define MMSYS_MISC_REG_GPIO_58_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_58_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_SMT_POS))
#define MMSYS_MISC_REG_GPIO_58_DRV                              MMSYS_MISC_REG_GPIO_58_DRV
#define MMSYS_MISC_REG_GPIO_58_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_58_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_58_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_58_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_DRV_POS)
#define MMSYS_MISC_REG_GPIO_58_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_58_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_DRV_POS))
#define MMSYS_MISC_REG_GPIO_58_PU                               MMSYS_MISC_REG_GPIO_58_PU
#define MMSYS_MISC_REG_GPIO_58_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_58_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_58_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_58_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_PU_POS)
#define MMSYS_MISC_REG_GPIO_58_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_58_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_PU_POS))
#define MMSYS_MISC_REG_GPIO_58_PD                               MMSYS_MISC_REG_GPIO_58_PD
#define MMSYS_MISC_REG_GPIO_58_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_58_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_58_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_58_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_PD_POS)
#define MMSYS_MISC_REG_GPIO_58_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_58_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_PD_POS))
#define MMSYS_MISC_REG_GPIO_59_IE                               MMSYS_MISC_REG_GPIO_59_IE
#define MMSYS_MISC_REG_GPIO_59_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_59_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_59_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_59_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_IE_POS)
#define MMSYS_MISC_REG_GPIO_59_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_59_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_IE_POS))
#define MMSYS_MISC_REG_GPIO_59_SMT                              MMSYS_MISC_REG_GPIO_59_SMT
#define MMSYS_MISC_REG_GPIO_59_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_59_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_59_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_59_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_SMT_POS)
#define MMSYS_MISC_REG_GPIO_59_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_59_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_SMT_POS))
#define MMSYS_MISC_REG_GPIO_59_DRV                              MMSYS_MISC_REG_GPIO_59_DRV
#define MMSYS_MISC_REG_GPIO_59_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_59_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_59_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_59_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_DRV_POS)
#define MMSYS_MISC_REG_GPIO_59_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_59_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_DRV_POS))
#define MMSYS_MISC_REG_GPIO_59_PU                               MMSYS_MISC_REG_GPIO_59_PU
#define MMSYS_MISC_REG_GPIO_59_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_59_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_59_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_59_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_PU_POS)
#define MMSYS_MISC_REG_GPIO_59_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_59_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_PU_POS))
#define MMSYS_MISC_REG_GPIO_59_PD                               MMSYS_MISC_REG_GPIO_59_PD
#define MMSYS_MISC_REG_GPIO_59_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_59_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_59_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_59_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_PD_POS)
#define MMSYS_MISC_REG_GPIO_59_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_59_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_PD_POS))

/* 0x278 : GPIO_CFGCTL30 */
#define MMSYS_MISC_GPIO_CFGCTL30_OFFSET                         (0x278)
#define MMSYS_MISC_REG_GPIO_60_IE                               MMSYS_MISC_REG_GPIO_60_IE
#define MMSYS_MISC_REG_GPIO_60_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_60_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_60_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_60_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_IE_POS)
#define MMSYS_MISC_REG_GPIO_60_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_60_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_IE_POS))
#define MMSYS_MISC_REG_GPIO_60_SMT                              MMSYS_MISC_REG_GPIO_60_SMT
#define MMSYS_MISC_REG_GPIO_60_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_60_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_60_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_60_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_SMT_POS)
#define MMSYS_MISC_REG_GPIO_60_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_60_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_SMT_POS))
#define MMSYS_MISC_REG_GPIO_60_DRV                              MMSYS_MISC_REG_GPIO_60_DRV
#define MMSYS_MISC_REG_GPIO_60_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_60_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_60_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_60_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_DRV_POS)
#define MMSYS_MISC_REG_GPIO_60_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_60_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_DRV_POS))
#define MMSYS_MISC_REG_GPIO_60_PU                               MMSYS_MISC_REG_GPIO_60_PU
#define MMSYS_MISC_REG_GPIO_60_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_60_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_60_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_60_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_PU_POS)
#define MMSYS_MISC_REG_GPIO_60_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_60_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_PU_POS))
#define MMSYS_MISC_REG_GPIO_60_PD                               MMSYS_MISC_REG_GPIO_60_PD
#define MMSYS_MISC_REG_GPIO_60_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_60_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_60_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_60_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_PD_POS)
#define MMSYS_MISC_REG_GPIO_60_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_60_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_PD_POS))
#define MMSYS_MISC_REG_GPIO_61_IE                               MMSYS_MISC_REG_GPIO_61_IE
#define MMSYS_MISC_REG_GPIO_61_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_61_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_61_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_61_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_IE_POS)
#define MMSYS_MISC_REG_GPIO_61_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_61_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_IE_POS))
#define MMSYS_MISC_REG_GPIO_61_SMT                              MMSYS_MISC_REG_GPIO_61_SMT
#define MMSYS_MISC_REG_GPIO_61_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_61_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_61_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_61_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_SMT_POS)
#define MMSYS_MISC_REG_GPIO_61_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_61_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_SMT_POS))
#define MMSYS_MISC_REG_GPIO_61_DRV                              MMSYS_MISC_REG_GPIO_61_DRV
#define MMSYS_MISC_REG_GPIO_61_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_61_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_61_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_61_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_DRV_POS)
#define MMSYS_MISC_REG_GPIO_61_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_61_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_DRV_POS))
#define MMSYS_MISC_REG_GPIO_61_PU                               MMSYS_MISC_REG_GPIO_61_PU
#define MMSYS_MISC_REG_GPIO_61_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_61_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_61_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_61_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_PU_POS)
#define MMSYS_MISC_REG_GPIO_61_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_61_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_PU_POS))
#define MMSYS_MISC_REG_GPIO_61_PD                               MMSYS_MISC_REG_GPIO_61_PD
#define MMSYS_MISC_REG_GPIO_61_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_61_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_61_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_61_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_PD_POS)
#define MMSYS_MISC_REG_GPIO_61_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_61_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_PD_POS))

/* 0x27C : GPIO_CFGCTL31 */
#define MMSYS_MISC_GPIO_CFGCTL31_OFFSET                         (0x27C)
#define MMSYS_MISC_REG_GPIO_62_IE                               MMSYS_MISC_REG_GPIO_62_IE
#define MMSYS_MISC_REG_GPIO_62_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_62_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_62_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_62_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_IE_POS)
#define MMSYS_MISC_REG_GPIO_62_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_62_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_IE_POS))
#define MMSYS_MISC_REG_GPIO_62_SMT                              MMSYS_MISC_REG_GPIO_62_SMT
#define MMSYS_MISC_REG_GPIO_62_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_62_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_62_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_62_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_SMT_POS)
#define MMSYS_MISC_REG_GPIO_62_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_62_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_SMT_POS))
#define MMSYS_MISC_REG_GPIO_62_DRV                              MMSYS_MISC_REG_GPIO_62_DRV
#define MMSYS_MISC_REG_GPIO_62_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_62_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_62_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_62_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_DRV_POS)
#define MMSYS_MISC_REG_GPIO_62_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_62_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_DRV_POS))
#define MMSYS_MISC_REG_GPIO_62_PU                               MMSYS_MISC_REG_GPIO_62_PU
#define MMSYS_MISC_REG_GPIO_62_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_62_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_62_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_62_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_PU_POS)
#define MMSYS_MISC_REG_GPIO_62_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_62_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_PU_POS))
#define MMSYS_MISC_REG_GPIO_62_PD                               MMSYS_MISC_REG_GPIO_62_PD
#define MMSYS_MISC_REG_GPIO_62_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_62_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_62_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_62_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_PD_POS)
#define MMSYS_MISC_REG_GPIO_62_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_62_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_PD_POS))
#define MMSYS_MISC_REG_GPIO_63_IE                               MMSYS_MISC_REG_GPIO_63_IE
#define MMSYS_MISC_REG_GPIO_63_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_63_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_63_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_63_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_IE_POS)
#define MMSYS_MISC_REG_GPIO_63_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_63_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_IE_POS))
#define MMSYS_MISC_REG_GPIO_63_SMT                              MMSYS_MISC_REG_GPIO_63_SMT
#define MMSYS_MISC_REG_GPIO_63_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_63_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_63_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_63_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_SMT_POS)
#define MMSYS_MISC_REG_GPIO_63_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_63_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_SMT_POS))
#define MMSYS_MISC_REG_GPIO_63_DRV                              MMSYS_MISC_REG_GPIO_63_DRV
#define MMSYS_MISC_REG_GPIO_63_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_63_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_63_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_63_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_DRV_POS)
#define MMSYS_MISC_REG_GPIO_63_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_63_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_DRV_POS))
#define MMSYS_MISC_REG_GPIO_63_PU                               MMSYS_MISC_REG_GPIO_63_PU
#define MMSYS_MISC_REG_GPIO_63_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_63_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_63_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_63_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_PU_POS)
#define MMSYS_MISC_REG_GPIO_63_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_63_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_PU_POS))
#define MMSYS_MISC_REG_GPIO_63_PD                               MMSYS_MISC_REG_GPIO_63_PD
#define MMSYS_MISC_REG_GPIO_63_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_63_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_63_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_63_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_PD_POS)
#define MMSYS_MISC_REG_GPIO_63_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_63_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_PD_POS))

/* 0x280 : GPIO_CFGCTL32 */
#define MMSYS_MISC_GPIO_CFGCTL32_OFFSET                         (0x280)
#define MMSYS_MISC_REG_GPIO_64_IE                               MMSYS_MISC_REG_GPIO_64_IE
#define MMSYS_MISC_REG_GPIO_64_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_64_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_64_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_64_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_IE_POS)
#define MMSYS_MISC_REG_GPIO_64_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_64_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_IE_POS))
#define MMSYS_MISC_REG_GPIO_64_SMT                              MMSYS_MISC_REG_GPIO_64_SMT
#define MMSYS_MISC_REG_GPIO_64_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_64_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_64_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_64_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_SMT_POS)
#define MMSYS_MISC_REG_GPIO_64_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_64_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_SMT_POS))
#define MMSYS_MISC_REG_GPIO_64_DRV                              MMSYS_MISC_REG_GPIO_64_DRV
#define MMSYS_MISC_REG_GPIO_64_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_64_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_64_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_64_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_DRV_POS)
#define MMSYS_MISC_REG_GPIO_64_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_64_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_DRV_POS))
#define MMSYS_MISC_REG_GPIO_64_PU                               MMSYS_MISC_REG_GPIO_64_PU
#define MMSYS_MISC_REG_GPIO_64_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_64_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_64_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_64_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_PU_POS)
#define MMSYS_MISC_REG_GPIO_64_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_64_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_PU_POS))
#define MMSYS_MISC_REG_GPIO_64_PD                               MMSYS_MISC_REG_GPIO_64_PD
#define MMSYS_MISC_REG_GPIO_64_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_64_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_64_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_64_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_PD_POS)
#define MMSYS_MISC_REG_GPIO_64_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_64_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_PD_POS))
#define MMSYS_MISC_REG_GPIO_65_IE                               MMSYS_MISC_REG_GPIO_65_IE
#define MMSYS_MISC_REG_GPIO_65_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_65_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_65_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_65_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_IE_POS)
#define MMSYS_MISC_REG_GPIO_65_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_65_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_IE_POS))
#define MMSYS_MISC_REG_GPIO_65_SMT                              MMSYS_MISC_REG_GPIO_65_SMT
#define MMSYS_MISC_REG_GPIO_65_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_65_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_65_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_65_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_SMT_POS)
#define MMSYS_MISC_REG_GPIO_65_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_65_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_SMT_POS))
#define MMSYS_MISC_REG_GPIO_65_DRV                              MMSYS_MISC_REG_GPIO_65_DRV
#define MMSYS_MISC_REG_GPIO_65_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_65_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_65_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_65_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_DRV_POS)
#define MMSYS_MISC_REG_GPIO_65_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_65_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_DRV_POS))
#define MMSYS_MISC_REG_GPIO_65_PU                               MMSYS_MISC_REG_GPIO_65_PU
#define MMSYS_MISC_REG_GPIO_65_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_65_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_65_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_65_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_PU_POS)
#define MMSYS_MISC_REG_GPIO_65_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_65_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_PU_POS))
#define MMSYS_MISC_REG_GPIO_65_PD                               MMSYS_MISC_REG_GPIO_65_PD
#define MMSYS_MISC_REG_GPIO_65_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_65_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_65_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_65_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_PD_POS)
#define MMSYS_MISC_REG_GPIO_65_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_65_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_PD_POS))

/* 0x284 : GPIO_CFGCTL33 */
#define MMSYS_MISC_GPIO_CFGCTL33_OFFSET                         (0x284)
#define MMSYS_MISC_REG_GPIO_66_IE                               MMSYS_MISC_REG_GPIO_66_IE
#define MMSYS_MISC_REG_GPIO_66_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_66_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_66_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_66_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_IE_POS)
#define MMSYS_MISC_REG_GPIO_66_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_66_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_IE_POS))
#define MMSYS_MISC_REG_GPIO_66_SMT                              MMSYS_MISC_REG_GPIO_66_SMT
#define MMSYS_MISC_REG_GPIO_66_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_66_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_66_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_66_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_SMT_POS)
#define MMSYS_MISC_REG_GPIO_66_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_66_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_SMT_POS))
#define MMSYS_MISC_REG_GPIO_66_DRV                              MMSYS_MISC_REG_GPIO_66_DRV
#define MMSYS_MISC_REG_GPIO_66_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_66_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_66_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_66_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_DRV_POS)
#define MMSYS_MISC_REG_GPIO_66_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_66_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_DRV_POS))
#define MMSYS_MISC_REG_GPIO_66_PU                               MMSYS_MISC_REG_GPIO_66_PU
#define MMSYS_MISC_REG_GPIO_66_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_66_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_66_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_66_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_PU_POS)
#define MMSYS_MISC_REG_GPIO_66_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_66_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_PU_POS))
#define MMSYS_MISC_REG_GPIO_66_PD                               MMSYS_MISC_REG_GPIO_66_PD
#define MMSYS_MISC_REG_GPIO_66_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_66_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_66_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_66_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_PD_POS)
#define MMSYS_MISC_REG_GPIO_66_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_66_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_PD_POS))
#define MMSYS_MISC_REG_GPIO_67_IE                               MMSYS_MISC_REG_GPIO_67_IE
#define MMSYS_MISC_REG_GPIO_67_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_67_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_67_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_67_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_IE_POS)
#define MMSYS_MISC_REG_GPIO_67_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_67_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_IE_POS))
#define MMSYS_MISC_REG_GPIO_67_SMT                              MMSYS_MISC_REG_GPIO_67_SMT
#define MMSYS_MISC_REG_GPIO_67_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_67_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_67_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_67_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_SMT_POS)
#define MMSYS_MISC_REG_GPIO_67_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_67_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_SMT_POS))
#define MMSYS_MISC_REG_GPIO_67_DRV                              MMSYS_MISC_REG_GPIO_67_DRV
#define MMSYS_MISC_REG_GPIO_67_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_67_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_67_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_67_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_DRV_POS)
#define MMSYS_MISC_REG_GPIO_67_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_67_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_DRV_POS))
#define MMSYS_MISC_REG_GPIO_67_PU                               MMSYS_MISC_REG_GPIO_67_PU
#define MMSYS_MISC_REG_GPIO_67_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_67_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_67_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_67_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_PU_POS)
#define MMSYS_MISC_REG_GPIO_67_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_67_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_PU_POS))
#define MMSYS_MISC_REG_GPIO_67_PD                               MMSYS_MISC_REG_GPIO_67_PD
#define MMSYS_MISC_REG_GPIO_67_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_67_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_67_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_67_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_PD_POS)
#define MMSYS_MISC_REG_GPIO_67_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_67_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_PD_POS))

/* 0x288 : GPIO_CFGCTL34 */
#define MMSYS_MISC_GPIO_CFGCTL34_OFFSET                         (0x288)
#define MMSYS_MISC_REG_GPIO_68_IE                               MMSYS_MISC_REG_GPIO_68_IE
#define MMSYS_MISC_REG_GPIO_68_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_68_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_68_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_68_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_IE_POS)
#define MMSYS_MISC_REG_GPIO_68_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_68_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_IE_POS))
#define MMSYS_MISC_REG_GPIO_68_SMT                              MMSYS_MISC_REG_GPIO_68_SMT
#define MMSYS_MISC_REG_GPIO_68_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_68_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_68_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_68_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_SMT_POS)
#define MMSYS_MISC_REG_GPIO_68_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_68_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_SMT_POS))
#define MMSYS_MISC_REG_GPIO_68_DRV                              MMSYS_MISC_REG_GPIO_68_DRV
#define MMSYS_MISC_REG_GPIO_68_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_68_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_68_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_68_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_DRV_POS)
#define MMSYS_MISC_REG_GPIO_68_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_68_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_DRV_POS))
#define MMSYS_MISC_REG_GPIO_68_PU                               MMSYS_MISC_REG_GPIO_68_PU
#define MMSYS_MISC_REG_GPIO_68_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_68_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_68_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_68_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_PU_POS)
#define MMSYS_MISC_REG_GPIO_68_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_68_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_PU_POS))
#define MMSYS_MISC_REG_GPIO_68_PD                               MMSYS_MISC_REG_GPIO_68_PD
#define MMSYS_MISC_REG_GPIO_68_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_68_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_68_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_68_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_PD_POS)
#define MMSYS_MISC_REG_GPIO_68_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_68_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_PD_POS))
#define MMSYS_MISC_REG_GPIO_69_IE                               MMSYS_MISC_REG_GPIO_69_IE
#define MMSYS_MISC_REG_GPIO_69_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_69_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_69_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_69_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_IE_POS)
#define MMSYS_MISC_REG_GPIO_69_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_69_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_IE_POS))
#define MMSYS_MISC_REG_GPIO_69_SMT                              MMSYS_MISC_REG_GPIO_69_SMT
#define MMSYS_MISC_REG_GPIO_69_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_69_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_69_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_69_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_SMT_POS)
#define MMSYS_MISC_REG_GPIO_69_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_69_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_SMT_POS))
#define MMSYS_MISC_REG_GPIO_69_DRV                              MMSYS_MISC_REG_GPIO_69_DRV
#define MMSYS_MISC_REG_GPIO_69_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_69_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_69_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_69_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_DRV_POS)
#define MMSYS_MISC_REG_GPIO_69_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_69_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_DRV_POS))
#define MMSYS_MISC_REG_GPIO_69_PU                               MMSYS_MISC_REG_GPIO_69_PU
#define MMSYS_MISC_REG_GPIO_69_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_69_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_69_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_69_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_PU_POS)
#define MMSYS_MISC_REG_GPIO_69_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_69_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_PU_POS))
#define MMSYS_MISC_REG_GPIO_69_PD                               MMSYS_MISC_REG_GPIO_69_PD
#define MMSYS_MISC_REG_GPIO_69_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_69_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_69_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_69_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_PD_POS)
#define MMSYS_MISC_REG_GPIO_69_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_69_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_PD_POS))

/* 0x28C : GPIO_CFGCTL35 */
#define MMSYS_MISC_GPIO_CFGCTL35_OFFSET                         (0x28C)
#define MMSYS_MISC_REG_GPIO_70_IE                               MMSYS_MISC_REG_GPIO_70_IE
#define MMSYS_MISC_REG_GPIO_70_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_70_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_70_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_70_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_IE_POS)
#define MMSYS_MISC_REG_GPIO_70_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_70_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_IE_POS))
#define MMSYS_MISC_REG_GPIO_70_SMT                              MMSYS_MISC_REG_GPIO_70_SMT
#define MMSYS_MISC_REG_GPIO_70_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_70_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_70_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_70_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_SMT_POS)
#define MMSYS_MISC_REG_GPIO_70_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_70_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_SMT_POS))
#define MMSYS_MISC_REG_GPIO_70_DRV                              MMSYS_MISC_REG_GPIO_70_DRV
#define MMSYS_MISC_REG_GPIO_70_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_70_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_70_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_70_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_DRV_POS)
#define MMSYS_MISC_REG_GPIO_70_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_70_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_DRV_POS))
#define MMSYS_MISC_REG_GPIO_70_PU                               MMSYS_MISC_REG_GPIO_70_PU
#define MMSYS_MISC_REG_GPIO_70_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_70_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_70_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_70_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_PU_POS)
#define MMSYS_MISC_REG_GPIO_70_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_70_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_PU_POS))
#define MMSYS_MISC_REG_GPIO_70_PD                               MMSYS_MISC_REG_GPIO_70_PD
#define MMSYS_MISC_REG_GPIO_70_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_70_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_70_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_70_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_PD_POS)
#define MMSYS_MISC_REG_GPIO_70_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_70_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_PD_POS))
#define MMSYS_MISC_REG_GPIO_71_IE                               MMSYS_MISC_REG_GPIO_71_IE
#define MMSYS_MISC_REG_GPIO_71_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_71_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_71_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_71_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_IE_POS)
#define MMSYS_MISC_REG_GPIO_71_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_71_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_IE_POS))
#define MMSYS_MISC_REG_GPIO_71_SMT                              MMSYS_MISC_REG_GPIO_71_SMT
#define MMSYS_MISC_REG_GPIO_71_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_71_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_71_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_71_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_SMT_POS)
#define MMSYS_MISC_REG_GPIO_71_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_71_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_SMT_POS))
#define MMSYS_MISC_REG_GPIO_71_DRV                              MMSYS_MISC_REG_GPIO_71_DRV
#define MMSYS_MISC_REG_GPIO_71_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_71_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_71_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_71_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_DRV_POS)
#define MMSYS_MISC_REG_GPIO_71_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_71_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_DRV_POS))
#define MMSYS_MISC_REG_GPIO_71_PU                               MMSYS_MISC_REG_GPIO_71_PU
#define MMSYS_MISC_REG_GPIO_71_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_71_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_71_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_71_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_PU_POS)
#define MMSYS_MISC_REG_GPIO_71_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_71_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_PU_POS))
#define MMSYS_MISC_REG_GPIO_71_PD                               MMSYS_MISC_REG_GPIO_71_PD
#define MMSYS_MISC_REG_GPIO_71_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_71_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_71_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_71_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_PD_POS)
#define MMSYS_MISC_REG_GPIO_71_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_71_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_PD_POS))

/* 0x290 : GPIO_CFGCTL36 */
#define MMSYS_MISC_GPIO_CFGCTL36_OFFSET                         (0x290)
#define MMSYS_MISC_REG_GPIO_72_IE                               MMSYS_MISC_REG_GPIO_72_IE
#define MMSYS_MISC_REG_GPIO_72_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_72_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_72_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_72_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_IE_POS)
#define MMSYS_MISC_REG_GPIO_72_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_72_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_IE_POS))
#define MMSYS_MISC_REG_GPIO_72_SMT                              MMSYS_MISC_REG_GPIO_72_SMT
#define MMSYS_MISC_REG_GPIO_72_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_72_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_72_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_72_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_SMT_POS)
#define MMSYS_MISC_REG_GPIO_72_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_72_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_SMT_POS))
#define MMSYS_MISC_REG_GPIO_72_DRV                              MMSYS_MISC_REG_GPIO_72_DRV
#define MMSYS_MISC_REG_GPIO_72_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_72_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_72_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_72_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_DRV_POS)
#define MMSYS_MISC_REG_GPIO_72_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_72_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_DRV_POS))
#define MMSYS_MISC_REG_GPIO_72_PU                               MMSYS_MISC_REG_GPIO_72_PU
#define MMSYS_MISC_REG_GPIO_72_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_72_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_72_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_72_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_PU_POS)
#define MMSYS_MISC_REG_GPIO_72_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_72_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_PU_POS))
#define MMSYS_MISC_REG_GPIO_72_PD                               MMSYS_MISC_REG_GPIO_72_PD
#define MMSYS_MISC_REG_GPIO_72_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_72_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_72_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_72_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_PD_POS)
#define MMSYS_MISC_REG_GPIO_72_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_72_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_PD_POS))
#define MMSYS_MISC_REG_GPIO_73_IE                               MMSYS_MISC_REG_GPIO_73_IE
#define MMSYS_MISC_REG_GPIO_73_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_73_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_73_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_73_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_IE_POS)
#define MMSYS_MISC_REG_GPIO_73_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_73_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_IE_POS))
#define MMSYS_MISC_REG_GPIO_73_SMT                              MMSYS_MISC_REG_GPIO_73_SMT
#define MMSYS_MISC_REG_GPIO_73_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_73_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_73_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_73_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_SMT_POS)
#define MMSYS_MISC_REG_GPIO_73_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_73_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_SMT_POS))
#define MMSYS_MISC_REG_GPIO_73_DRV                              MMSYS_MISC_REG_GPIO_73_DRV
#define MMSYS_MISC_REG_GPIO_73_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_73_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_73_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_73_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_DRV_POS)
#define MMSYS_MISC_REG_GPIO_73_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_73_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_DRV_POS))
#define MMSYS_MISC_REG_GPIO_73_PU                               MMSYS_MISC_REG_GPIO_73_PU
#define MMSYS_MISC_REG_GPIO_73_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_73_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_73_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_73_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_PU_POS)
#define MMSYS_MISC_REG_GPIO_73_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_73_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_PU_POS))
#define MMSYS_MISC_REG_GPIO_73_PD                               MMSYS_MISC_REG_GPIO_73_PD
#define MMSYS_MISC_REG_GPIO_73_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_73_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_73_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_73_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_PD_POS)
#define MMSYS_MISC_REG_GPIO_73_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_73_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_PD_POS))

/* 0x294 : GPIO_CFGCTL37 */
#define MMSYS_MISC_GPIO_CFGCTL37_OFFSET                         (0x294)
#define MMSYS_MISC_REG_GPIO_74_IE                               MMSYS_MISC_REG_GPIO_74_IE
#define MMSYS_MISC_REG_GPIO_74_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_74_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_74_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_74_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_IE_POS)
#define MMSYS_MISC_REG_GPIO_74_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_74_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_IE_POS))
#define MMSYS_MISC_REG_GPIO_74_SMT                              MMSYS_MISC_REG_GPIO_74_SMT
#define MMSYS_MISC_REG_GPIO_74_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_74_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_74_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_74_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_SMT_POS)
#define MMSYS_MISC_REG_GPIO_74_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_74_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_SMT_POS))
#define MMSYS_MISC_REG_GPIO_74_DRV                              MMSYS_MISC_REG_GPIO_74_DRV
#define MMSYS_MISC_REG_GPIO_74_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_74_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_74_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_74_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_DRV_POS)
#define MMSYS_MISC_REG_GPIO_74_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_74_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_DRV_POS))
#define MMSYS_MISC_REG_GPIO_74_PU                               MMSYS_MISC_REG_GPIO_74_PU
#define MMSYS_MISC_REG_GPIO_74_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_74_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_74_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_74_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_PU_POS)
#define MMSYS_MISC_REG_GPIO_74_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_74_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_PU_POS))
#define MMSYS_MISC_REG_GPIO_74_PD                               MMSYS_MISC_REG_GPIO_74_PD
#define MMSYS_MISC_REG_GPIO_74_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_74_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_74_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_74_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_PD_POS)
#define MMSYS_MISC_REG_GPIO_74_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_74_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_PD_POS))
#define MMSYS_MISC_REG_GPIO_75_IE                               MMSYS_MISC_REG_GPIO_75_IE
#define MMSYS_MISC_REG_GPIO_75_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_75_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_75_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_75_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_IE_POS)
#define MMSYS_MISC_REG_GPIO_75_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_75_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_IE_POS))
#define MMSYS_MISC_REG_GPIO_75_SMT                              MMSYS_MISC_REG_GPIO_75_SMT
#define MMSYS_MISC_REG_GPIO_75_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_75_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_75_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_75_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_SMT_POS)
#define MMSYS_MISC_REG_GPIO_75_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_75_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_SMT_POS))
#define MMSYS_MISC_REG_GPIO_75_DRV                              MMSYS_MISC_REG_GPIO_75_DRV
#define MMSYS_MISC_REG_GPIO_75_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_75_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_75_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_75_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_DRV_POS)
#define MMSYS_MISC_REG_GPIO_75_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_75_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_DRV_POS))
#define MMSYS_MISC_REG_GPIO_75_PU                               MMSYS_MISC_REG_GPIO_75_PU
#define MMSYS_MISC_REG_GPIO_75_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_75_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_75_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_75_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_PU_POS)
#define MMSYS_MISC_REG_GPIO_75_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_75_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_PU_POS))
#define MMSYS_MISC_REG_GPIO_75_PD                               MMSYS_MISC_REG_GPIO_75_PD
#define MMSYS_MISC_REG_GPIO_75_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_75_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_75_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_75_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_PD_POS)
#define MMSYS_MISC_REG_GPIO_75_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_75_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_PD_POS))

/* 0x298 : GPIO_CFGCTL38 */
#define MMSYS_MISC_GPIO_CFGCTL38_OFFSET                         (0x298)
#define MMSYS_MISC_REG_GPIO_76_IE                               MMSYS_MISC_REG_GPIO_76_IE
#define MMSYS_MISC_REG_GPIO_76_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_76_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_76_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_76_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_IE_POS)
#define MMSYS_MISC_REG_GPIO_76_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_76_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_IE_POS))
#define MMSYS_MISC_REG_GPIO_76_SMT                              MMSYS_MISC_REG_GPIO_76_SMT
#define MMSYS_MISC_REG_GPIO_76_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_76_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_76_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_76_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_SMT_POS)
#define MMSYS_MISC_REG_GPIO_76_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_76_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_SMT_POS))
#define MMSYS_MISC_REG_GPIO_76_DRV                              MMSYS_MISC_REG_GPIO_76_DRV
#define MMSYS_MISC_REG_GPIO_76_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_76_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_76_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_76_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_DRV_POS)
#define MMSYS_MISC_REG_GPIO_76_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_76_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_DRV_POS))
#define MMSYS_MISC_REG_GPIO_76_PU                               MMSYS_MISC_REG_GPIO_76_PU
#define MMSYS_MISC_REG_GPIO_76_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_76_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_76_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_76_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_PU_POS)
#define MMSYS_MISC_REG_GPIO_76_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_76_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_PU_POS))
#define MMSYS_MISC_REG_GPIO_76_PD                               MMSYS_MISC_REG_GPIO_76_PD
#define MMSYS_MISC_REG_GPIO_76_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_76_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_76_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_76_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_PD_POS)
#define MMSYS_MISC_REG_GPIO_76_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_76_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_PD_POS))
#define MMSYS_MISC_REG_GPIO_77_IE                               MMSYS_MISC_REG_GPIO_77_IE
#define MMSYS_MISC_REG_GPIO_77_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_77_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_77_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_77_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_IE_POS)
#define MMSYS_MISC_REG_GPIO_77_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_77_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_IE_POS))
#define MMSYS_MISC_REG_GPIO_77_SMT                              MMSYS_MISC_REG_GPIO_77_SMT
#define MMSYS_MISC_REG_GPIO_77_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_77_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_77_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_77_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_SMT_POS)
#define MMSYS_MISC_REG_GPIO_77_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_77_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_SMT_POS))
#define MMSYS_MISC_REG_GPIO_77_DRV                              MMSYS_MISC_REG_GPIO_77_DRV
#define MMSYS_MISC_REG_GPIO_77_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_77_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_77_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_77_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_DRV_POS)
#define MMSYS_MISC_REG_GPIO_77_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_77_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_DRV_POS))
#define MMSYS_MISC_REG_GPIO_77_PU                               MMSYS_MISC_REG_GPIO_77_PU
#define MMSYS_MISC_REG_GPIO_77_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_77_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_77_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_77_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_PU_POS)
#define MMSYS_MISC_REG_GPIO_77_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_77_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_PU_POS))
#define MMSYS_MISC_REG_GPIO_77_PD                               MMSYS_MISC_REG_GPIO_77_PD
#define MMSYS_MISC_REG_GPIO_77_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_77_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_77_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_77_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_PD_POS)
#define MMSYS_MISC_REG_GPIO_77_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_77_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_PD_POS))

/* 0x29C : GPIO_CFGCTL39 */
#define MMSYS_MISC_GPIO_CFGCTL39_OFFSET                         (0x29C)
#define MMSYS_MISC_REG_GPIO_78_IE                               MMSYS_MISC_REG_GPIO_78_IE
#define MMSYS_MISC_REG_GPIO_78_IE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_78_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_78_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_78_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_IE_POS)
#define MMSYS_MISC_REG_GPIO_78_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_78_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_IE_POS))
#define MMSYS_MISC_REG_GPIO_78_SMT                              MMSYS_MISC_REG_GPIO_78_SMT
#define MMSYS_MISC_REG_GPIO_78_SMT_POS                          (1U)
#define MMSYS_MISC_REG_GPIO_78_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_78_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_78_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_SMT_POS)
#define MMSYS_MISC_REG_GPIO_78_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_78_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_SMT_POS))
#define MMSYS_MISC_REG_GPIO_78_DRV                              MMSYS_MISC_REG_GPIO_78_DRV
#define MMSYS_MISC_REG_GPIO_78_DRV_POS                          (2U)
#define MMSYS_MISC_REG_GPIO_78_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_78_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_78_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_DRV_POS)
#define MMSYS_MISC_REG_GPIO_78_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_78_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_DRV_POS))
#define MMSYS_MISC_REG_GPIO_78_PU                               MMSYS_MISC_REG_GPIO_78_PU
#define MMSYS_MISC_REG_GPIO_78_PU_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_78_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_78_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_78_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_PU_POS)
#define MMSYS_MISC_REG_GPIO_78_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_78_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_PU_POS))
#define MMSYS_MISC_REG_GPIO_78_PD                               MMSYS_MISC_REG_GPIO_78_PD
#define MMSYS_MISC_REG_GPIO_78_PD_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_78_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_78_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_78_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_PD_POS)
#define MMSYS_MISC_REG_GPIO_78_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_78_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_PD_POS))
#define MMSYS_MISC_REG_GPIO_79_IE                               MMSYS_MISC_REG_GPIO_79_IE
#define MMSYS_MISC_REG_GPIO_79_IE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_79_IE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_79_IE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_79_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_IE_POS)
#define MMSYS_MISC_REG_GPIO_79_IE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_79_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_IE_POS))
#define MMSYS_MISC_REG_GPIO_79_SMT                              MMSYS_MISC_REG_GPIO_79_SMT
#define MMSYS_MISC_REG_GPIO_79_SMT_POS                          (17U)
#define MMSYS_MISC_REG_GPIO_79_SMT_LEN                          (1U)
#define MMSYS_MISC_REG_GPIO_79_SMT_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_79_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_SMT_POS)
#define MMSYS_MISC_REG_GPIO_79_SMT_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_79_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_SMT_POS))
#define MMSYS_MISC_REG_GPIO_79_DRV                              MMSYS_MISC_REG_GPIO_79_DRV
#define MMSYS_MISC_REG_GPIO_79_DRV_POS                          (18U)
#define MMSYS_MISC_REG_GPIO_79_DRV_LEN                          (2U)
#define MMSYS_MISC_REG_GPIO_79_DRV_MSK                          (((1U<<MMSYS_MISC_REG_GPIO_79_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_DRV_POS)
#define MMSYS_MISC_REG_GPIO_79_DRV_UMSK                         (~(((1U<<MMSYS_MISC_REG_GPIO_79_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_DRV_POS))
#define MMSYS_MISC_REG_GPIO_79_PU                               MMSYS_MISC_REG_GPIO_79_PU
#define MMSYS_MISC_REG_GPIO_79_PU_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_79_PU_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_79_PU_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_79_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_PU_POS)
#define MMSYS_MISC_REG_GPIO_79_PU_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_79_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_PU_POS))
#define MMSYS_MISC_REG_GPIO_79_PD                               MMSYS_MISC_REG_GPIO_79_PD
#define MMSYS_MISC_REG_GPIO_79_PD_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_79_PD_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_79_PD_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_79_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_PD_POS)
#define MMSYS_MISC_REG_GPIO_79_PD_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_79_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_PD_POS))

/* 0x2A0 : GPIO_CFGCTL40 */
#define MMSYS_MISC_GPIO_CFGCTL40_OFFSET                         (0x2A0)
#define MMSYS_MISC_REG_GPIO_0_I                                 MMSYS_MISC_REG_GPIO_0_I
#define MMSYS_MISC_REG_GPIO_0_I_POS                             (0U)
#define MMSYS_MISC_REG_GPIO_0_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_0_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_0_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_I_POS)
#define MMSYS_MISC_REG_GPIO_0_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_0_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_I_POS))
#define MMSYS_MISC_REG_GPIO_1_I                                 MMSYS_MISC_REG_GPIO_1_I
#define MMSYS_MISC_REG_GPIO_1_I_POS                             (1U)
#define MMSYS_MISC_REG_GPIO_1_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_1_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_1_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_I_POS)
#define MMSYS_MISC_REG_GPIO_1_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_1_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_I_POS))
#define MMSYS_MISC_REG_GPIO_2_I                                 MMSYS_MISC_REG_GPIO_2_I
#define MMSYS_MISC_REG_GPIO_2_I_POS                             (2U)
#define MMSYS_MISC_REG_GPIO_2_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_2_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_2_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_I_POS)
#define MMSYS_MISC_REG_GPIO_2_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_2_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_I_POS))
#define MMSYS_MISC_REG_GPIO_3_I                                 MMSYS_MISC_REG_GPIO_3_I
#define MMSYS_MISC_REG_GPIO_3_I_POS                             (3U)
#define MMSYS_MISC_REG_GPIO_3_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_3_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_3_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_I_POS)
#define MMSYS_MISC_REG_GPIO_3_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_3_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_I_POS))
#define MMSYS_MISC_REG_GPIO_4_I                                 MMSYS_MISC_REG_GPIO_4_I
#define MMSYS_MISC_REG_GPIO_4_I_POS                             (4U)
#define MMSYS_MISC_REG_GPIO_4_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_4_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_4_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_I_POS)
#define MMSYS_MISC_REG_GPIO_4_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_4_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_I_POS))
#define MMSYS_MISC_REG_GPIO_5_I                                 MMSYS_MISC_REG_GPIO_5_I
#define MMSYS_MISC_REG_GPIO_5_I_POS                             (5U)
#define MMSYS_MISC_REG_GPIO_5_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_5_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_5_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_I_POS)
#define MMSYS_MISC_REG_GPIO_5_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_5_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_I_POS))
#define MMSYS_MISC_REG_GPIO_6_I                                 MMSYS_MISC_REG_GPIO_6_I
#define MMSYS_MISC_REG_GPIO_6_I_POS                             (6U)
#define MMSYS_MISC_REG_GPIO_6_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_6_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_6_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_I_POS)
#define MMSYS_MISC_REG_GPIO_6_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_6_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_I_POS))
#define MMSYS_MISC_REG_GPIO_7_I                                 MMSYS_MISC_REG_GPIO_7_I
#define MMSYS_MISC_REG_GPIO_7_I_POS                             (7U)
#define MMSYS_MISC_REG_GPIO_7_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_7_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_7_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_I_POS)
#define MMSYS_MISC_REG_GPIO_7_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_7_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_I_POS))
#define MMSYS_MISC_REG_GPIO_8_I                                 MMSYS_MISC_REG_GPIO_8_I
#define MMSYS_MISC_REG_GPIO_8_I_POS                             (8U)
#define MMSYS_MISC_REG_GPIO_8_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_8_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_8_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_I_POS)
#define MMSYS_MISC_REG_GPIO_8_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_8_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_I_POS))
#define MMSYS_MISC_REG_GPIO_9_I                                 MMSYS_MISC_REG_GPIO_9_I
#define MMSYS_MISC_REG_GPIO_9_I_POS                             (9U)
#define MMSYS_MISC_REG_GPIO_9_I_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_9_I_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_9_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_I_POS)
#define MMSYS_MISC_REG_GPIO_9_I_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_9_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_I_POS))
#define MMSYS_MISC_REG_GPIO_10_I                                MMSYS_MISC_REG_GPIO_10_I
#define MMSYS_MISC_REG_GPIO_10_I_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_10_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_10_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_10_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_I_POS)
#define MMSYS_MISC_REG_GPIO_10_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_10_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_I_POS))
#define MMSYS_MISC_REG_GPIO_11_I                                MMSYS_MISC_REG_GPIO_11_I
#define MMSYS_MISC_REG_GPIO_11_I_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_11_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_11_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_11_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_I_POS)
#define MMSYS_MISC_REG_GPIO_11_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_11_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_I_POS))
#define MMSYS_MISC_REG_GPIO_12_I                                MMSYS_MISC_REG_GPIO_12_I
#define MMSYS_MISC_REG_GPIO_12_I_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_12_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_12_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_12_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_I_POS)
#define MMSYS_MISC_REG_GPIO_12_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_12_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_I_POS))
#define MMSYS_MISC_REG_GPIO_13_I                                MMSYS_MISC_REG_GPIO_13_I
#define MMSYS_MISC_REG_GPIO_13_I_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_13_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_13_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_13_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_I_POS)
#define MMSYS_MISC_REG_GPIO_13_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_13_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_I_POS))
#define MMSYS_MISC_REG_GPIO_14_I                                MMSYS_MISC_REG_GPIO_14_I
#define MMSYS_MISC_REG_GPIO_14_I_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_14_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_14_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_14_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_I_POS)
#define MMSYS_MISC_REG_GPIO_14_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_14_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_I_POS))
#define MMSYS_MISC_REG_GPIO_15_I                                MMSYS_MISC_REG_GPIO_15_I
#define MMSYS_MISC_REG_GPIO_15_I_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_15_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_15_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_15_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_I_POS)
#define MMSYS_MISC_REG_GPIO_15_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_15_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_I_POS))
#define MMSYS_MISC_REG_GPIO_16_I                                MMSYS_MISC_REG_GPIO_16_I
#define MMSYS_MISC_REG_GPIO_16_I_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_16_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_16_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_16_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_I_POS)
#define MMSYS_MISC_REG_GPIO_16_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_16_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_I_POS))
#define MMSYS_MISC_REG_GPIO_17_I                                MMSYS_MISC_REG_GPIO_17_I
#define MMSYS_MISC_REG_GPIO_17_I_POS                            (17U)
#define MMSYS_MISC_REG_GPIO_17_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_17_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_17_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_I_POS)
#define MMSYS_MISC_REG_GPIO_17_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_17_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_I_POS))
#define MMSYS_MISC_REG_GPIO_18_I                                MMSYS_MISC_REG_GPIO_18_I
#define MMSYS_MISC_REG_GPIO_18_I_POS                            (18U)
#define MMSYS_MISC_REG_GPIO_18_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_18_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_18_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_I_POS)
#define MMSYS_MISC_REG_GPIO_18_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_18_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_I_POS))
#define MMSYS_MISC_REG_GPIO_19_I                                MMSYS_MISC_REG_GPIO_19_I
#define MMSYS_MISC_REG_GPIO_19_I_POS                            (19U)
#define MMSYS_MISC_REG_GPIO_19_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_19_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_19_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_I_POS)
#define MMSYS_MISC_REG_GPIO_19_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_19_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_I_POS))
#define MMSYS_MISC_REG_GPIO_20_I                                MMSYS_MISC_REG_GPIO_20_I
#define MMSYS_MISC_REG_GPIO_20_I_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_20_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_20_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_20_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_I_POS)
#define MMSYS_MISC_REG_GPIO_20_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_20_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_I_POS))
#define MMSYS_MISC_REG_GPIO_21_I                                MMSYS_MISC_REG_GPIO_21_I
#define MMSYS_MISC_REG_GPIO_21_I_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_21_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_21_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_21_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_I_POS)
#define MMSYS_MISC_REG_GPIO_21_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_21_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_I_POS))
#define MMSYS_MISC_REG_GPIO_22_I                                MMSYS_MISC_REG_GPIO_22_I
#define MMSYS_MISC_REG_GPIO_22_I_POS                            (22U)
#define MMSYS_MISC_REG_GPIO_22_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_22_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_22_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_I_POS)
#define MMSYS_MISC_REG_GPIO_22_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_22_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_I_POS))
#define MMSYS_MISC_REG_GPIO_23_I                                MMSYS_MISC_REG_GPIO_23_I
#define MMSYS_MISC_REG_GPIO_23_I_POS                            (23U)
#define MMSYS_MISC_REG_GPIO_23_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_23_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_23_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_I_POS)
#define MMSYS_MISC_REG_GPIO_23_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_23_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_I_POS))
#define MMSYS_MISC_REG_GPIO_24_I                                MMSYS_MISC_REG_GPIO_24_I
#define MMSYS_MISC_REG_GPIO_24_I_POS                            (24U)
#define MMSYS_MISC_REG_GPIO_24_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_24_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_24_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_I_POS)
#define MMSYS_MISC_REG_GPIO_24_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_24_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_I_POS))
#define MMSYS_MISC_REG_GPIO_25_I                                MMSYS_MISC_REG_GPIO_25_I
#define MMSYS_MISC_REG_GPIO_25_I_POS                            (25U)
#define MMSYS_MISC_REG_GPIO_25_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_25_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_25_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_I_POS)
#define MMSYS_MISC_REG_GPIO_25_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_25_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_I_POS))
#define MMSYS_MISC_REG_GPIO_26_I                                MMSYS_MISC_REG_GPIO_26_I
#define MMSYS_MISC_REG_GPIO_26_I_POS                            (26U)
#define MMSYS_MISC_REG_GPIO_26_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_26_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_26_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_I_POS)
#define MMSYS_MISC_REG_GPIO_26_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_26_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_I_POS))
#define MMSYS_MISC_REG_GPIO_27_I                                MMSYS_MISC_REG_GPIO_27_I
#define MMSYS_MISC_REG_GPIO_27_I_POS                            (27U)
#define MMSYS_MISC_REG_GPIO_27_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_27_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_27_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_I_POS)
#define MMSYS_MISC_REG_GPIO_27_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_27_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_I_POS))
#define MMSYS_MISC_REG_GPIO_28_I                                MMSYS_MISC_REG_GPIO_28_I
#define MMSYS_MISC_REG_GPIO_28_I_POS                            (28U)
#define MMSYS_MISC_REG_GPIO_28_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_28_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_28_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_I_POS)
#define MMSYS_MISC_REG_GPIO_28_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_28_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_I_POS))
#define MMSYS_MISC_REG_GPIO_29_I                                MMSYS_MISC_REG_GPIO_29_I
#define MMSYS_MISC_REG_GPIO_29_I_POS                            (29U)
#define MMSYS_MISC_REG_GPIO_29_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_29_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_29_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_I_POS)
#define MMSYS_MISC_REG_GPIO_29_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_29_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_I_POS))
#define MMSYS_MISC_REG_GPIO_30_I                                MMSYS_MISC_REG_GPIO_30_I
#define MMSYS_MISC_REG_GPIO_30_I_POS                            (30U)
#define MMSYS_MISC_REG_GPIO_30_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_30_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_30_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_I_POS)
#define MMSYS_MISC_REG_GPIO_30_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_30_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_I_POS))
#define MMSYS_MISC_REG_GPIO_31_I                                MMSYS_MISC_REG_GPIO_31_I
#define MMSYS_MISC_REG_GPIO_31_I_POS                            (31U)
#define MMSYS_MISC_REG_GPIO_31_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_31_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_31_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_I_POS)
#define MMSYS_MISC_REG_GPIO_31_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_31_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_I_POS))

/* 0x2A4 : GPIO_CFGCTL41 */
#define MMSYS_MISC_GPIO_CFGCTL41_OFFSET                         (0x2A4)
#define MMSYS_MISC_REG_GPIO_32_I                                MMSYS_MISC_REG_GPIO_32_I
#define MMSYS_MISC_REG_GPIO_32_I_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_32_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_32_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_32_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_I_POS)
#define MMSYS_MISC_REG_GPIO_32_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_32_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_I_POS))
#define MMSYS_MISC_REG_GPIO_33_I                                MMSYS_MISC_REG_GPIO_33_I
#define MMSYS_MISC_REG_GPIO_33_I_POS                            (1U)
#define MMSYS_MISC_REG_GPIO_33_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_33_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_33_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_I_POS)
#define MMSYS_MISC_REG_GPIO_33_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_33_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_I_POS))
#define MMSYS_MISC_REG_GPIO_34_I                                MMSYS_MISC_REG_GPIO_34_I
#define MMSYS_MISC_REG_GPIO_34_I_POS                            (2U)
#define MMSYS_MISC_REG_GPIO_34_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_34_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_34_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_I_POS)
#define MMSYS_MISC_REG_GPIO_34_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_34_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_I_POS))
#define MMSYS_MISC_REG_GPIO_35_I                                MMSYS_MISC_REG_GPIO_35_I
#define MMSYS_MISC_REG_GPIO_35_I_POS                            (3U)
#define MMSYS_MISC_REG_GPIO_35_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_35_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_35_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_I_POS)
#define MMSYS_MISC_REG_GPIO_35_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_35_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_I_POS))
#define MMSYS_MISC_REG_GPIO_36_I                                MMSYS_MISC_REG_GPIO_36_I
#define MMSYS_MISC_REG_GPIO_36_I_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_36_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_36_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_36_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_I_POS)
#define MMSYS_MISC_REG_GPIO_36_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_36_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_I_POS))
#define MMSYS_MISC_REG_GPIO_37_I                                MMSYS_MISC_REG_GPIO_37_I
#define MMSYS_MISC_REG_GPIO_37_I_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_37_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_37_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_37_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_I_POS)
#define MMSYS_MISC_REG_GPIO_37_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_37_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_I_POS))
#define MMSYS_MISC_REG_GPIO_38_I                                MMSYS_MISC_REG_GPIO_38_I
#define MMSYS_MISC_REG_GPIO_38_I_POS                            (6U)
#define MMSYS_MISC_REG_GPIO_38_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_38_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_38_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_I_POS)
#define MMSYS_MISC_REG_GPIO_38_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_38_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_I_POS))
#define MMSYS_MISC_REG_GPIO_39_I                                MMSYS_MISC_REG_GPIO_39_I
#define MMSYS_MISC_REG_GPIO_39_I_POS                            (7U)
#define MMSYS_MISC_REG_GPIO_39_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_39_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_39_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_I_POS)
#define MMSYS_MISC_REG_GPIO_39_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_39_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_I_POS))
#define MMSYS_MISC_REG_GPIO_40_I                                MMSYS_MISC_REG_GPIO_40_I
#define MMSYS_MISC_REG_GPIO_40_I_POS                            (8U)
#define MMSYS_MISC_REG_GPIO_40_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_40_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_40_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_I_POS)
#define MMSYS_MISC_REG_GPIO_40_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_40_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_I_POS))
#define MMSYS_MISC_REG_GPIO_41_I                                MMSYS_MISC_REG_GPIO_41_I
#define MMSYS_MISC_REG_GPIO_41_I_POS                            (9U)
#define MMSYS_MISC_REG_GPIO_41_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_41_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_41_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_I_POS)
#define MMSYS_MISC_REG_GPIO_41_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_41_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_I_POS))
#define MMSYS_MISC_REG_GPIO_42_I                                MMSYS_MISC_REG_GPIO_42_I
#define MMSYS_MISC_REG_GPIO_42_I_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_42_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_42_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_42_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_I_POS)
#define MMSYS_MISC_REG_GPIO_42_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_42_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_I_POS))
#define MMSYS_MISC_REG_GPIO_43_I                                MMSYS_MISC_REG_GPIO_43_I
#define MMSYS_MISC_REG_GPIO_43_I_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_43_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_43_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_43_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_I_POS)
#define MMSYS_MISC_REG_GPIO_43_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_43_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_I_POS))
#define MMSYS_MISC_REG_GPIO_44_I                                MMSYS_MISC_REG_GPIO_44_I
#define MMSYS_MISC_REG_GPIO_44_I_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_44_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_44_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_44_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_I_POS)
#define MMSYS_MISC_REG_GPIO_44_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_44_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_I_POS))
#define MMSYS_MISC_REG_GPIO_45_I                                MMSYS_MISC_REG_GPIO_45_I
#define MMSYS_MISC_REG_GPIO_45_I_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_45_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_45_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_45_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_I_POS)
#define MMSYS_MISC_REG_GPIO_45_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_45_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_I_POS))
#define MMSYS_MISC_REG_GPIO_46_I                                MMSYS_MISC_REG_GPIO_46_I
#define MMSYS_MISC_REG_GPIO_46_I_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_46_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_46_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_46_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_I_POS)
#define MMSYS_MISC_REG_GPIO_46_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_46_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_I_POS))
#define MMSYS_MISC_REG_GPIO_47_I                                MMSYS_MISC_REG_GPIO_47_I
#define MMSYS_MISC_REG_GPIO_47_I_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_47_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_47_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_47_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_I_POS)
#define MMSYS_MISC_REG_GPIO_47_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_47_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_I_POS))
#define MMSYS_MISC_REG_GPIO_48_I                                MMSYS_MISC_REG_GPIO_48_I
#define MMSYS_MISC_REG_GPIO_48_I_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_48_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_48_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_48_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_I_POS)
#define MMSYS_MISC_REG_GPIO_48_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_48_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_I_POS))
#define MMSYS_MISC_REG_GPIO_49_I                                MMSYS_MISC_REG_GPIO_49_I
#define MMSYS_MISC_REG_GPIO_49_I_POS                            (17U)
#define MMSYS_MISC_REG_GPIO_49_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_49_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_49_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_I_POS)
#define MMSYS_MISC_REG_GPIO_49_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_49_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_I_POS))
#define MMSYS_MISC_REG_GPIO_50_I                                MMSYS_MISC_REG_GPIO_50_I
#define MMSYS_MISC_REG_GPIO_50_I_POS                            (18U)
#define MMSYS_MISC_REG_GPIO_50_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_50_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_50_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_I_POS)
#define MMSYS_MISC_REG_GPIO_50_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_50_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_I_POS))
#define MMSYS_MISC_REG_GPIO_51_I                                MMSYS_MISC_REG_GPIO_51_I
#define MMSYS_MISC_REG_GPIO_51_I_POS                            (19U)
#define MMSYS_MISC_REG_GPIO_51_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_51_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_51_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_I_POS)
#define MMSYS_MISC_REG_GPIO_51_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_51_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_I_POS))
#define MMSYS_MISC_REG_GPIO_52_I                                MMSYS_MISC_REG_GPIO_52_I
#define MMSYS_MISC_REG_GPIO_52_I_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_52_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_52_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_52_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_I_POS)
#define MMSYS_MISC_REG_GPIO_52_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_52_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_I_POS))
#define MMSYS_MISC_REG_GPIO_53_I                                MMSYS_MISC_REG_GPIO_53_I
#define MMSYS_MISC_REG_GPIO_53_I_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_53_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_53_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_53_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_I_POS)
#define MMSYS_MISC_REG_GPIO_53_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_53_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_I_POS))
#define MMSYS_MISC_REG_GPIO_54_I                                MMSYS_MISC_REG_GPIO_54_I
#define MMSYS_MISC_REG_GPIO_54_I_POS                            (22U)
#define MMSYS_MISC_REG_GPIO_54_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_54_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_54_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_I_POS)
#define MMSYS_MISC_REG_GPIO_54_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_54_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_I_POS))
#define MMSYS_MISC_REG_GPIO_55_I                                MMSYS_MISC_REG_GPIO_55_I
#define MMSYS_MISC_REG_GPIO_55_I_POS                            (23U)
#define MMSYS_MISC_REG_GPIO_55_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_55_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_55_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_I_POS)
#define MMSYS_MISC_REG_GPIO_55_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_55_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_I_POS))
#define MMSYS_MISC_REG_GPIO_56_I                                MMSYS_MISC_REG_GPIO_56_I
#define MMSYS_MISC_REG_GPIO_56_I_POS                            (24U)
#define MMSYS_MISC_REG_GPIO_56_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_56_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_56_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_I_POS)
#define MMSYS_MISC_REG_GPIO_56_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_56_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_I_POS))
#define MMSYS_MISC_REG_GPIO_57_I                                MMSYS_MISC_REG_GPIO_57_I
#define MMSYS_MISC_REG_GPIO_57_I_POS                            (25U)
#define MMSYS_MISC_REG_GPIO_57_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_57_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_57_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_I_POS)
#define MMSYS_MISC_REG_GPIO_57_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_57_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_I_POS))
#define MMSYS_MISC_REG_GPIO_58_I                                MMSYS_MISC_REG_GPIO_58_I
#define MMSYS_MISC_REG_GPIO_58_I_POS                            (26U)
#define MMSYS_MISC_REG_GPIO_58_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_58_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_58_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_I_POS)
#define MMSYS_MISC_REG_GPIO_58_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_58_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_I_POS))
#define MMSYS_MISC_REG_GPIO_59_I                                MMSYS_MISC_REG_GPIO_59_I
#define MMSYS_MISC_REG_GPIO_59_I_POS                            (27U)
#define MMSYS_MISC_REG_GPIO_59_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_59_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_59_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_I_POS)
#define MMSYS_MISC_REG_GPIO_59_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_59_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_I_POS))
#define MMSYS_MISC_REG_GPIO_60_I                                MMSYS_MISC_REG_GPIO_60_I
#define MMSYS_MISC_REG_GPIO_60_I_POS                            (28U)
#define MMSYS_MISC_REG_GPIO_60_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_60_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_60_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_I_POS)
#define MMSYS_MISC_REG_GPIO_60_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_60_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_I_POS))
#define MMSYS_MISC_REG_GPIO_61_I                                MMSYS_MISC_REG_GPIO_61_I
#define MMSYS_MISC_REG_GPIO_61_I_POS                            (29U)
#define MMSYS_MISC_REG_GPIO_61_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_61_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_61_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_I_POS)
#define MMSYS_MISC_REG_GPIO_61_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_61_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_I_POS))
#define MMSYS_MISC_REG_GPIO_62_I                                MMSYS_MISC_REG_GPIO_62_I
#define MMSYS_MISC_REG_GPIO_62_I_POS                            (30U)
#define MMSYS_MISC_REG_GPIO_62_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_62_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_62_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_I_POS)
#define MMSYS_MISC_REG_GPIO_62_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_62_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_I_POS))
#define MMSYS_MISC_REG_GPIO_63_I                                MMSYS_MISC_REG_GPIO_63_I
#define MMSYS_MISC_REG_GPIO_63_I_POS                            (31U)
#define MMSYS_MISC_REG_GPIO_63_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_63_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_63_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_I_POS)
#define MMSYS_MISC_REG_GPIO_63_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_63_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_I_POS))

/* 0x2A8 : GPIO_CFGCTL42 */
#define MMSYS_MISC_GPIO_CFGCTL42_OFFSET                         (0x2A8)
#define MMSYS_MISC_REG_GPIO_64_I                                MMSYS_MISC_REG_GPIO_64_I
#define MMSYS_MISC_REG_GPIO_64_I_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_64_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_64_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_64_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_I_POS)
#define MMSYS_MISC_REG_GPIO_64_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_64_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_I_POS))
#define MMSYS_MISC_REG_GPIO_65_I                                MMSYS_MISC_REG_GPIO_65_I
#define MMSYS_MISC_REG_GPIO_65_I_POS                            (1U)
#define MMSYS_MISC_REG_GPIO_65_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_65_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_65_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_I_POS)
#define MMSYS_MISC_REG_GPIO_65_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_65_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_I_POS))
#define MMSYS_MISC_REG_GPIO_66_I                                MMSYS_MISC_REG_GPIO_66_I
#define MMSYS_MISC_REG_GPIO_66_I_POS                            (2U)
#define MMSYS_MISC_REG_GPIO_66_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_66_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_66_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_I_POS)
#define MMSYS_MISC_REG_GPIO_66_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_66_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_I_POS))
#define MMSYS_MISC_REG_GPIO_67_I                                MMSYS_MISC_REG_GPIO_67_I
#define MMSYS_MISC_REG_GPIO_67_I_POS                            (3U)
#define MMSYS_MISC_REG_GPIO_67_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_67_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_67_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_I_POS)
#define MMSYS_MISC_REG_GPIO_67_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_67_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_I_POS))
#define MMSYS_MISC_REG_GPIO_68_I                                MMSYS_MISC_REG_GPIO_68_I
#define MMSYS_MISC_REG_GPIO_68_I_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_68_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_68_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_68_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_I_POS)
#define MMSYS_MISC_REG_GPIO_68_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_68_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_I_POS))
#define MMSYS_MISC_REG_GPIO_69_I                                MMSYS_MISC_REG_GPIO_69_I
#define MMSYS_MISC_REG_GPIO_69_I_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_69_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_69_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_69_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_I_POS)
#define MMSYS_MISC_REG_GPIO_69_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_69_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_I_POS))
#define MMSYS_MISC_REG_GPIO_70_I                                MMSYS_MISC_REG_GPIO_70_I
#define MMSYS_MISC_REG_GPIO_70_I_POS                            (6U)
#define MMSYS_MISC_REG_GPIO_70_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_70_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_70_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_I_POS)
#define MMSYS_MISC_REG_GPIO_70_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_70_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_I_POS))
#define MMSYS_MISC_REG_GPIO_71_I                                MMSYS_MISC_REG_GPIO_71_I
#define MMSYS_MISC_REG_GPIO_71_I_POS                            (7U)
#define MMSYS_MISC_REG_GPIO_71_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_71_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_71_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_I_POS)
#define MMSYS_MISC_REG_GPIO_71_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_71_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_I_POS))
#define MMSYS_MISC_REG_GPIO_72_I                                MMSYS_MISC_REG_GPIO_72_I
#define MMSYS_MISC_REG_GPIO_72_I_POS                            (8U)
#define MMSYS_MISC_REG_GPIO_72_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_72_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_72_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_I_POS)
#define MMSYS_MISC_REG_GPIO_72_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_72_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_I_POS))
#define MMSYS_MISC_REG_GPIO_73_I                                MMSYS_MISC_REG_GPIO_73_I
#define MMSYS_MISC_REG_GPIO_73_I_POS                            (9U)
#define MMSYS_MISC_REG_GPIO_73_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_73_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_73_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_I_POS)
#define MMSYS_MISC_REG_GPIO_73_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_73_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_I_POS))
#define MMSYS_MISC_REG_GPIO_74_I                                MMSYS_MISC_REG_GPIO_74_I
#define MMSYS_MISC_REG_GPIO_74_I_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_74_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_74_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_74_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_I_POS)
#define MMSYS_MISC_REG_GPIO_74_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_74_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_I_POS))
#define MMSYS_MISC_REG_GPIO_75_I                                MMSYS_MISC_REG_GPIO_75_I
#define MMSYS_MISC_REG_GPIO_75_I_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_75_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_75_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_75_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_I_POS)
#define MMSYS_MISC_REG_GPIO_75_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_75_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_I_POS))
#define MMSYS_MISC_REG_GPIO_76_I                                MMSYS_MISC_REG_GPIO_76_I
#define MMSYS_MISC_REG_GPIO_76_I_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_76_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_76_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_76_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_I_POS)
#define MMSYS_MISC_REG_GPIO_76_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_76_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_I_POS))
#define MMSYS_MISC_REG_GPIO_77_I                                MMSYS_MISC_REG_GPIO_77_I
#define MMSYS_MISC_REG_GPIO_77_I_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_77_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_77_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_77_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_I_POS)
#define MMSYS_MISC_REG_GPIO_77_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_77_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_I_POS))
#define MMSYS_MISC_REG_GPIO_78_I                                MMSYS_MISC_REG_GPIO_78_I
#define MMSYS_MISC_REG_GPIO_78_I_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_78_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_78_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_78_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_I_POS)
#define MMSYS_MISC_REG_GPIO_78_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_78_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_I_POS))
#define MMSYS_MISC_REG_GPIO_79_I                                MMSYS_MISC_REG_GPIO_79_I
#define MMSYS_MISC_REG_GPIO_79_I_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_79_I_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_79_I_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_79_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_I_POS)
#define MMSYS_MISC_REG_GPIO_79_I_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_79_I_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_I_POS))

/* 0x2B0 : GPIO_CFGCTL43 */
#define MMSYS_MISC_GPIO_CFGCTL43_OFFSET                         (0x2B0)
#define MMSYS_MISC_REG_GPIO_0_O                                 MMSYS_MISC_REG_GPIO_0_O
#define MMSYS_MISC_REG_GPIO_0_O_POS                             (0U)
#define MMSYS_MISC_REG_GPIO_0_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_0_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_0_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_O_POS)
#define MMSYS_MISC_REG_GPIO_0_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_0_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_O_POS))
#define MMSYS_MISC_REG_GPIO_1_O                                 MMSYS_MISC_REG_GPIO_1_O
#define MMSYS_MISC_REG_GPIO_1_O_POS                             (1U)
#define MMSYS_MISC_REG_GPIO_1_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_1_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_1_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_O_POS)
#define MMSYS_MISC_REG_GPIO_1_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_1_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_O_POS))
#define MMSYS_MISC_REG_GPIO_2_O                                 MMSYS_MISC_REG_GPIO_2_O
#define MMSYS_MISC_REG_GPIO_2_O_POS                             (2U)
#define MMSYS_MISC_REG_GPIO_2_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_2_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_2_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_O_POS)
#define MMSYS_MISC_REG_GPIO_2_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_2_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_O_POS))
#define MMSYS_MISC_REG_GPIO_3_O                                 MMSYS_MISC_REG_GPIO_3_O
#define MMSYS_MISC_REG_GPIO_3_O_POS                             (3U)
#define MMSYS_MISC_REG_GPIO_3_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_3_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_3_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_O_POS)
#define MMSYS_MISC_REG_GPIO_3_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_3_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_O_POS))
#define MMSYS_MISC_REG_GPIO_4_O                                 MMSYS_MISC_REG_GPIO_4_O
#define MMSYS_MISC_REG_GPIO_4_O_POS                             (4U)
#define MMSYS_MISC_REG_GPIO_4_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_4_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_4_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_O_POS)
#define MMSYS_MISC_REG_GPIO_4_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_4_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_O_POS))
#define MMSYS_MISC_REG_GPIO_5_O                                 MMSYS_MISC_REG_GPIO_5_O
#define MMSYS_MISC_REG_GPIO_5_O_POS                             (5U)
#define MMSYS_MISC_REG_GPIO_5_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_5_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_5_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_O_POS)
#define MMSYS_MISC_REG_GPIO_5_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_5_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_O_POS))
#define MMSYS_MISC_REG_GPIO_6_O                                 MMSYS_MISC_REG_GPIO_6_O
#define MMSYS_MISC_REG_GPIO_6_O_POS                             (6U)
#define MMSYS_MISC_REG_GPIO_6_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_6_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_6_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_O_POS)
#define MMSYS_MISC_REG_GPIO_6_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_6_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_O_POS))
#define MMSYS_MISC_REG_GPIO_7_O                                 MMSYS_MISC_REG_GPIO_7_O
#define MMSYS_MISC_REG_GPIO_7_O_POS                             (7U)
#define MMSYS_MISC_REG_GPIO_7_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_7_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_7_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_O_POS)
#define MMSYS_MISC_REG_GPIO_7_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_7_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_O_POS))
#define MMSYS_MISC_REG_GPIO_8_O                                 MMSYS_MISC_REG_GPIO_8_O
#define MMSYS_MISC_REG_GPIO_8_O_POS                             (8U)
#define MMSYS_MISC_REG_GPIO_8_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_8_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_8_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_O_POS)
#define MMSYS_MISC_REG_GPIO_8_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_8_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_O_POS))
#define MMSYS_MISC_REG_GPIO_9_O                                 MMSYS_MISC_REG_GPIO_9_O
#define MMSYS_MISC_REG_GPIO_9_O_POS                             (9U)
#define MMSYS_MISC_REG_GPIO_9_O_LEN                             (1U)
#define MMSYS_MISC_REG_GPIO_9_O_MSK                             (((1U<<MMSYS_MISC_REG_GPIO_9_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_O_POS)
#define MMSYS_MISC_REG_GPIO_9_O_UMSK                            (~(((1U<<MMSYS_MISC_REG_GPIO_9_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_O_POS))
#define MMSYS_MISC_REG_GPIO_10_O                                MMSYS_MISC_REG_GPIO_10_O
#define MMSYS_MISC_REG_GPIO_10_O_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_10_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_10_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_10_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_O_POS)
#define MMSYS_MISC_REG_GPIO_10_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_10_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_O_POS))
#define MMSYS_MISC_REG_GPIO_11_O                                MMSYS_MISC_REG_GPIO_11_O
#define MMSYS_MISC_REG_GPIO_11_O_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_11_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_11_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_11_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_O_POS)
#define MMSYS_MISC_REG_GPIO_11_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_11_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_O_POS))
#define MMSYS_MISC_REG_GPIO_12_O                                MMSYS_MISC_REG_GPIO_12_O
#define MMSYS_MISC_REG_GPIO_12_O_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_12_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_12_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_12_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_O_POS)
#define MMSYS_MISC_REG_GPIO_12_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_12_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_O_POS))
#define MMSYS_MISC_REG_GPIO_13_O                                MMSYS_MISC_REG_GPIO_13_O
#define MMSYS_MISC_REG_GPIO_13_O_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_13_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_13_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_13_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_O_POS)
#define MMSYS_MISC_REG_GPIO_13_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_13_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_O_POS))
#define MMSYS_MISC_REG_GPIO_14_O                                MMSYS_MISC_REG_GPIO_14_O
#define MMSYS_MISC_REG_GPIO_14_O_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_14_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_14_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_14_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_O_POS)
#define MMSYS_MISC_REG_GPIO_14_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_14_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_O_POS))
#define MMSYS_MISC_REG_GPIO_15_O                                MMSYS_MISC_REG_GPIO_15_O
#define MMSYS_MISC_REG_GPIO_15_O_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_15_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_15_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_15_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_O_POS)
#define MMSYS_MISC_REG_GPIO_15_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_15_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_O_POS))
#define MMSYS_MISC_REG_GPIO_16_O                                MMSYS_MISC_REG_GPIO_16_O
#define MMSYS_MISC_REG_GPIO_16_O_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_16_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_16_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_16_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_O_POS)
#define MMSYS_MISC_REG_GPIO_16_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_16_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_O_POS))
#define MMSYS_MISC_REG_GPIO_17_O                                MMSYS_MISC_REG_GPIO_17_O
#define MMSYS_MISC_REG_GPIO_17_O_POS                            (17U)
#define MMSYS_MISC_REG_GPIO_17_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_17_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_17_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_O_POS)
#define MMSYS_MISC_REG_GPIO_17_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_17_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_O_POS))
#define MMSYS_MISC_REG_GPIO_18_O                                MMSYS_MISC_REG_GPIO_18_O
#define MMSYS_MISC_REG_GPIO_18_O_POS                            (18U)
#define MMSYS_MISC_REG_GPIO_18_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_18_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_18_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_O_POS)
#define MMSYS_MISC_REG_GPIO_18_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_18_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_O_POS))
#define MMSYS_MISC_REG_GPIO_19_O                                MMSYS_MISC_REG_GPIO_19_O
#define MMSYS_MISC_REG_GPIO_19_O_POS                            (19U)
#define MMSYS_MISC_REG_GPIO_19_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_19_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_19_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_O_POS)
#define MMSYS_MISC_REG_GPIO_19_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_19_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_O_POS))
#define MMSYS_MISC_REG_GPIO_20_O                                MMSYS_MISC_REG_GPIO_20_O
#define MMSYS_MISC_REG_GPIO_20_O_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_20_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_20_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_20_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_O_POS)
#define MMSYS_MISC_REG_GPIO_20_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_20_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_O_POS))
#define MMSYS_MISC_REG_GPIO_21_O                                MMSYS_MISC_REG_GPIO_21_O
#define MMSYS_MISC_REG_GPIO_21_O_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_21_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_21_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_21_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_O_POS)
#define MMSYS_MISC_REG_GPIO_21_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_21_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_O_POS))
#define MMSYS_MISC_REG_GPIO_22_O                                MMSYS_MISC_REG_GPIO_22_O
#define MMSYS_MISC_REG_GPIO_22_O_POS                            (22U)
#define MMSYS_MISC_REG_GPIO_22_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_22_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_22_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_O_POS)
#define MMSYS_MISC_REG_GPIO_22_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_22_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_O_POS))
#define MMSYS_MISC_REG_GPIO_23_O                                MMSYS_MISC_REG_GPIO_23_O
#define MMSYS_MISC_REG_GPIO_23_O_POS                            (23U)
#define MMSYS_MISC_REG_GPIO_23_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_23_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_23_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_O_POS)
#define MMSYS_MISC_REG_GPIO_23_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_23_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_O_POS))
#define MMSYS_MISC_REG_GPIO_24_O                                MMSYS_MISC_REG_GPIO_24_O
#define MMSYS_MISC_REG_GPIO_24_O_POS                            (24U)
#define MMSYS_MISC_REG_GPIO_24_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_24_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_24_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_O_POS)
#define MMSYS_MISC_REG_GPIO_24_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_24_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_O_POS))
#define MMSYS_MISC_REG_GPIO_25_O                                MMSYS_MISC_REG_GPIO_25_O
#define MMSYS_MISC_REG_GPIO_25_O_POS                            (25U)
#define MMSYS_MISC_REG_GPIO_25_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_25_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_25_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_O_POS)
#define MMSYS_MISC_REG_GPIO_25_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_25_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_O_POS))
#define MMSYS_MISC_REG_GPIO_26_O                                MMSYS_MISC_REG_GPIO_26_O
#define MMSYS_MISC_REG_GPIO_26_O_POS                            (26U)
#define MMSYS_MISC_REG_GPIO_26_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_26_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_26_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_O_POS)
#define MMSYS_MISC_REG_GPIO_26_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_26_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_O_POS))
#define MMSYS_MISC_REG_GPIO_27_O                                MMSYS_MISC_REG_GPIO_27_O
#define MMSYS_MISC_REG_GPIO_27_O_POS                            (27U)
#define MMSYS_MISC_REG_GPIO_27_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_27_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_27_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_O_POS)
#define MMSYS_MISC_REG_GPIO_27_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_27_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_O_POS))
#define MMSYS_MISC_REG_GPIO_28_O                                MMSYS_MISC_REG_GPIO_28_O
#define MMSYS_MISC_REG_GPIO_28_O_POS                            (28U)
#define MMSYS_MISC_REG_GPIO_28_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_28_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_28_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_O_POS)
#define MMSYS_MISC_REG_GPIO_28_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_28_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_O_POS))
#define MMSYS_MISC_REG_GPIO_29_O                                MMSYS_MISC_REG_GPIO_29_O
#define MMSYS_MISC_REG_GPIO_29_O_POS                            (29U)
#define MMSYS_MISC_REG_GPIO_29_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_29_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_29_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_O_POS)
#define MMSYS_MISC_REG_GPIO_29_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_29_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_O_POS))
#define MMSYS_MISC_REG_GPIO_30_O                                MMSYS_MISC_REG_GPIO_30_O
#define MMSYS_MISC_REG_GPIO_30_O_POS                            (30U)
#define MMSYS_MISC_REG_GPIO_30_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_30_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_30_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_O_POS)
#define MMSYS_MISC_REG_GPIO_30_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_30_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_O_POS))
#define MMSYS_MISC_REG_GPIO_31_O                                MMSYS_MISC_REG_GPIO_31_O
#define MMSYS_MISC_REG_GPIO_31_O_POS                            (31U)
#define MMSYS_MISC_REG_GPIO_31_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_31_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_31_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_O_POS)
#define MMSYS_MISC_REG_GPIO_31_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_31_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_O_POS))

/* 0x2B4 : GPIO_CFGCTL44 */
#define MMSYS_MISC_GPIO_CFGCTL44_OFFSET                         (0x2B4)
#define MMSYS_MISC_REG_GPIO_32_O                                MMSYS_MISC_REG_GPIO_32_O
#define MMSYS_MISC_REG_GPIO_32_O_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_32_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_32_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_32_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_O_POS)
#define MMSYS_MISC_REG_GPIO_32_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_32_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_O_POS))
#define MMSYS_MISC_REG_GPIO_33_O                                MMSYS_MISC_REG_GPIO_33_O
#define MMSYS_MISC_REG_GPIO_33_O_POS                            (1U)
#define MMSYS_MISC_REG_GPIO_33_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_33_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_33_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_O_POS)
#define MMSYS_MISC_REG_GPIO_33_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_33_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_O_POS))
#define MMSYS_MISC_REG_GPIO_34_O                                MMSYS_MISC_REG_GPIO_34_O
#define MMSYS_MISC_REG_GPIO_34_O_POS                            (2U)
#define MMSYS_MISC_REG_GPIO_34_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_34_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_34_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_O_POS)
#define MMSYS_MISC_REG_GPIO_34_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_34_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_O_POS))
#define MMSYS_MISC_REG_GPIO_35_O                                MMSYS_MISC_REG_GPIO_35_O
#define MMSYS_MISC_REG_GPIO_35_O_POS                            (3U)
#define MMSYS_MISC_REG_GPIO_35_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_35_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_35_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_O_POS)
#define MMSYS_MISC_REG_GPIO_35_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_35_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_O_POS))
#define MMSYS_MISC_REG_GPIO_36_O                                MMSYS_MISC_REG_GPIO_36_O
#define MMSYS_MISC_REG_GPIO_36_O_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_36_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_36_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_36_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_O_POS)
#define MMSYS_MISC_REG_GPIO_36_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_36_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_O_POS))
#define MMSYS_MISC_REG_GPIO_37_O                                MMSYS_MISC_REG_GPIO_37_O
#define MMSYS_MISC_REG_GPIO_37_O_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_37_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_37_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_37_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_O_POS)
#define MMSYS_MISC_REG_GPIO_37_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_37_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_O_POS))
#define MMSYS_MISC_REG_GPIO_38_O                                MMSYS_MISC_REG_GPIO_38_O
#define MMSYS_MISC_REG_GPIO_38_O_POS                            (6U)
#define MMSYS_MISC_REG_GPIO_38_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_38_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_38_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_O_POS)
#define MMSYS_MISC_REG_GPIO_38_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_38_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_O_POS))
#define MMSYS_MISC_REG_GPIO_39_O                                MMSYS_MISC_REG_GPIO_39_O
#define MMSYS_MISC_REG_GPIO_39_O_POS                            (7U)
#define MMSYS_MISC_REG_GPIO_39_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_39_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_39_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_O_POS)
#define MMSYS_MISC_REG_GPIO_39_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_39_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_O_POS))
#define MMSYS_MISC_REG_GPIO_40_O                                MMSYS_MISC_REG_GPIO_40_O
#define MMSYS_MISC_REG_GPIO_40_O_POS                            (8U)
#define MMSYS_MISC_REG_GPIO_40_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_40_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_40_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_O_POS)
#define MMSYS_MISC_REG_GPIO_40_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_40_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_O_POS))
#define MMSYS_MISC_REG_GPIO_41_O                                MMSYS_MISC_REG_GPIO_41_O
#define MMSYS_MISC_REG_GPIO_41_O_POS                            (9U)
#define MMSYS_MISC_REG_GPIO_41_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_41_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_41_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_O_POS)
#define MMSYS_MISC_REG_GPIO_41_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_41_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_O_POS))
#define MMSYS_MISC_REG_GPIO_42_O                                MMSYS_MISC_REG_GPIO_42_O
#define MMSYS_MISC_REG_GPIO_42_O_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_42_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_42_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_42_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_O_POS)
#define MMSYS_MISC_REG_GPIO_42_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_42_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_O_POS))
#define MMSYS_MISC_REG_GPIO_43_O                                MMSYS_MISC_REG_GPIO_43_O
#define MMSYS_MISC_REG_GPIO_43_O_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_43_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_43_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_43_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_O_POS)
#define MMSYS_MISC_REG_GPIO_43_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_43_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_O_POS))
#define MMSYS_MISC_REG_GPIO_44_O                                MMSYS_MISC_REG_GPIO_44_O
#define MMSYS_MISC_REG_GPIO_44_O_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_44_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_44_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_44_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_O_POS)
#define MMSYS_MISC_REG_GPIO_44_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_44_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_O_POS))
#define MMSYS_MISC_REG_GPIO_45_O                                MMSYS_MISC_REG_GPIO_45_O
#define MMSYS_MISC_REG_GPIO_45_O_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_45_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_45_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_45_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_O_POS)
#define MMSYS_MISC_REG_GPIO_45_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_45_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_O_POS))
#define MMSYS_MISC_REG_GPIO_46_O                                MMSYS_MISC_REG_GPIO_46_O
#define MMSYS_MISC_REG_GPIO_46_O_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_46_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_46_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_46_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_O_POS)
#define MMSYS_MISC_REG_GPIO_46_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_46_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_O_POS))
#define MMSYS_MISC_REG_GPIO_47_O                                MMSYS_MISC_REG_GPIO_47_O
#define MMSYS_MISC_REG_GPIO_47_O_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_47_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_47_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_47_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_O_POS)
#define MMSYS_MISC_REG_GPIO_47_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_47_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_O_POS))
#define MMSYS_MISC_REG_GPIO_48_O                                MMSYS_MISC_REG_GPIO_48_O
#define MMSYS_MISC_REG_GPIO_48_O_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_48_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_48_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_48_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_O_POS)
#define MMSYS_MISC_REG_GPIO_48_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_48_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_O_POS))
#define MMSYS_MISC_REG_GPIO_49_O                                MMSYS_MISC_REG_GPIO_49_O
#define MMSYS_MISC_REG_GPIO_49_O_POS                            (17U)
#define MMSYS_MISC_REG_GPIO_49_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_49_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_49_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_O_POS)
#define MMSYS_MISC_REG_GPIO_49_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_49_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_O_POS))
#define MMSYS_MISC_REG_GPIO_50_O                                MMSYS_MISC_REG_GPIO_50_O
#define MMSYS_MISC_REG_GPIO_50_O_POS                            (18U)
#define MMSYS_MISC_REG_GPIO_50_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_50_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_50_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_O_POS)
#define MMSYS_MISC_REG_GPIO_50_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_50_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_O_POS))
#define MMSYS_MISC_REG_GPIO_51_O                                MMSYS_MISC_REG_GPIO_51_O
#define MMSYS_MISC_REG_GPIO_51_O_POS                            (19U)
#define MMSYS_MISC_REG_GPIO_51_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_51_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_51_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_O_POS)
#define MMSYS_MISC_REG_GPIO_51_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_51_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_O_POS))
#define MMSYS_MISC_REG_GPIO_52_O                                MMSYS_MISC_REG_GPIO_52_O
#define MMSYS_MISC_REG_GPIO_52_O_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_52_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_52_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_52_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_O_POS)
#define MMSYS_MISC_REG_GPIO_52_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_52_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_O_POS))
#define MMSYS_MISC_REG_GPIO_53_O                                MMSYS_MISC_REG_GPIO_53_O
#define MMSYS_MISC_REG_GPIO_53_O_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_53_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_53_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_53_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_O_POS)
#define MMSYS_MISC_REG_GPIO_53_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_53_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_O_POS))
#define MMSYS_MISC_REG_GPIO_54_O                                MMSYS_MISC_REG_GPIO_54_O
#define MMSYS_MISC_REG_GPIO_54_O_POS                            (22U)
#define MMSYS_MISC_REG_GPIO_54_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_54_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_54_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_O_POS)
#define MMSYS_MISC_REG_GPIO_54_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_54_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_O_POS))
#define MMSYS_MISC_REG_GPIO_55_O                                MMSYS_MISC_REG_GPIO_55_O
#define MMSYS_MISC_REG_GPIO_55_O_POS                            (23U)
#define MMSYS_MISC_REG_GPIO_55_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_55_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_55_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_O_POS)
#define MMSYS_MISC_REG_GPIO_55_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_55_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_O_POS))
#define MMSYS_MISC_REG_GPIO_56_O                                MMSYS_MISC_REG_GPIO_56_O
#define MMSYS_MISC_REG_GPIO_56_O_POS                            (24U)
#define MMSYS_MISC_REG_GPIO_56_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_56_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_56_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_O_POS)
#define MMSYS_MISC_REG_GPIO_56_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_56_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_O_POS))
#define MMSYS_MISC_REG_GPIO_57_O                                MMSYS_MISC_REG_GPIO_57_O
#define MMSYS_MISC_REG_GPIO_57_O_POS                            (25U)
#define MMSYS_MISC_REG_GPIO_57_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_57_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_57_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_O_POS)
#define MMSYS_MISC_REG_GPIO_57_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_57_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_O_POS))
#define MMSYS_MISC_REG_GPIO_58_O                                MMSYS_MISC_REG_GPIO_58_O
#define MMSYS_MISC_REG_GPIO_58_O_POS                            (26U)
#define MMSYS_MISC_REG_GPIO_58_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_58_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_58_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_O_POS)
#define MMSYS_MISC_REG_GPIO_58_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_58_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_O_POS))
#define MMSYS_MISC_REG_GPIO_59_O                                MMSYS_MISC_REG_GPIO_59_O
#define MMSYS_MISC_REG_GPIO_59_O_POS                            (27U)
#define MMSYS_MISC_REG_GPIO_59_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_59_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_59_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_O_POS)
#define MMSYS_MISC_REG_GPIO_59_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_59_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_O_POS))
#define MMSYS_MISC_REG_GPIO_60_O                                MMSYS_MISC_REG_GPIO_60_O
#define MMSYS_MISC_REG_GPIO_60_O_POS                            (28U)
#define MMSYS_MISC_REG_GPIO_60_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_60_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_60_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_O_POS)
#define MMSYS_MISC_REG_GPIO_60_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_60_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_O_POS))
#define MMSYS_MISC_REG_GPIO_61_O                                MMSYS_MISC_REG_GPIO_61_O
#define MMSYS_MISC_REG_GPIO_61_O_POS                            (29U)
#define MMSYS_MISC_REG_GPIO_61_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_61_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_61_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_O_POS)
#define MMSYS_MISC_REG_GPIO_61_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_61_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_O_POS))
#define MMSYS_MISC_REG_GPIO_62_O                                MMSYS_MISC_REG_GPIO_62_O
#define MMSYS_MISC_REG_GPIO_62_O_POS                            (30U)
#define MMSYS_MISC_REG_GPIO_62_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_62_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_62_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_O_POS)
#define MMSYS_MISC_REG_GPIO_62_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_62_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_O_POS))
#define MMSYS_MISC_REG_GPIO_63_O                                MMSYS_MISC_REG_GPIO_63_O
#define MMSYS_MISC_REG_GPIO_63_O_POS                            (31U)
#define MMSYS_MISC_REG_GPIO_63_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_63_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_63_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_O_POS)
#define MMSYS_MISC_REG_GPIO_63_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_63_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_O_POS))

/* 0x2B8 : GPIO_CFGCTL45 */
#define MMSYS_MISC_GPIO_CFGCTL45_OFFSET                         (0x2B8)
#define MMSYS_MISC_REG_GPIO_64_O                                MMSYS_MISC_REG_GPIO_64_O
#define MMSYS_MISC_REG_GPIO_64_O_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_64_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_64_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_64_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_O_POS)
#define MMSYS_MISC_REG_GPIO_64_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_64_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_O_POS))
#define MMSYS_MISC_REG_GPIO_65_O                                MMSYS_MISC_REG_GPIO_65_O
#define MMSYS_MISC_REG_GPIO_65_O_POS                            (1U)
#define MMSYS_MISC_REG_GPIO_65_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_65_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_65_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_O_POS)
#define MMSYS_MISC_REG_GPIO_65_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_65_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_O_POS))
#define MMSYS_MISC_REG_GPIO_66_O                                MMSYS_MISC_REG_GPIO_66_O
#define MMSYS_MISC_REG_GPIO_66_O_POS                            (2U)
#define MMSYS_MISC_REG_GPIO_66_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_66_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_66_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_O_POS)
#define MMSYS_MISC_REG_GPIO_66_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_66_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_O_POS))
#define MMSYS_MISC_REG_GPIO_67_O                                MMSYS_MISC_REG_GPIO_67_O
#define MMSYS_MISC_REG_GPIO_67_O_POS                            (3U)
#define MMSYS_MISC_REG_GPIO_67_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_67_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_67_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_O_POS)
#define MMSYS_MISC_REG_GPIO_67_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_67_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_O_POS))
#define MMSYS_MISC_REG_GPIO_68_O                                MMSYS_MISC_REG_GPIO_68_O
#define MMSYS_MISC_REG_GPIO_68_O_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_68_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_68_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_68_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_O_POS)
#define MMSYS_MISC_REG_GPIO_68_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_68_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_O_POS))
#define MMSYS_MISC_REG_GPIO_69_O                                MMSYS_MISC_REG_GPIO_69_O
#define MMSYS_MISC_REG_GPIO_69_O_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_69_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_69_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_69_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_O_POS)
#define MMSYS_MISC_REG_GPIO_69_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_69_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_O_POS))
#define MMSYS_MISC_REG_GPIO_70_O                                MMSYS_MISC_REG_GPIO_70_O
#define MMSYS_MISC_REG_GPIO_70_O_POS                            (6U)
#define MMSYS_MISC_REG_GPIO_70_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_70_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_70_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_O_POS)
#define MMSYS_MISC_REG_GPIO_70_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_70_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_O_POS))
#define MMSYS_MISC_REG_GPIO_71_O                                MMSYS_MISC_REG_GPIO_71_O
#define MMSYS_MISC_REG_GPIO_71_O_POS                            (7U)
#define MMSYS_MISC_REG_GPIO_71_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_71_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_71_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_O_POS)
#define MMSYS_MISC_REG_GPIO_71_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_71_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_O_POS))
#define MMSYS_MISC_REG_GPIO_72_O                                MMSYS_MISC_REG_GPIO_72_O
#define MMSYS_MISC_REG_GPIO_72_O_POS                            (8U)
#define MMSYS_MISC_REG_GPIO_72_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_72_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_72_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_O_POS)
#define MMSYS_MISC_REG_GPIO_72_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_72_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_O_POS))
#define MMSYS_MISC_REG_GPIO_73_O                                MMSYS_MISC_REG_GPIO_73_O
#define MMSYS_MISC_REG_GPIO_73_O_POS                            (9U)
#define MMSYS_MISC_REG_GPIO_73_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_73_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_73_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_O_POS)
#define MMSYS_MISC_REG_GPIO_73_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_73_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_O_POS))
#define MMSYS_MISC_REG_GPIO_74_O                                MMSYS_MISC_REG_GPIO_74_O
#define MMSYS_MISC_REG_GPIO_74_O_POS                            (10U)
#define MMSYS_MISC_REG_GPIO_74_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_74_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_74_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_O_POS)
#define MMSYS_MISC_REG_GPIO_74_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_74_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_O_POS))
#define MMSYS_MISC_REG_GPIO_75_O                                MMSYS_MISC_REG_GPIO_75_O
#define MMSYS_MISC_REG_GPIO_75_O_POS                            (11U)
#define MMSYS_MISC_REG_GPIO_75_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_75_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_75_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_O_POS)
#define MMSYS_MISC_REG_GPIO_75_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_75_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_O_POS))
#define MMSYS_MISC_REG_GPIO_76_O                                MMSYS_MISC_REG_GPIO_76_O
#define MMSYS_MISC_REG_GPIO_76_O_POS                            (12U)
#define MMSYS_MISC_REG_GPIO_76_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_76_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_76_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_O_POS)
#define MMSYS_MISC_REG_GPIO_76_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_76_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_O_POS))
#define MMSYS_MISC_REG_GPIO_77_O                                MMSYS_MISC_REG_GPIO_77_O
#define MMSYS_MISC_REG_GPIO_77_O_POS                            (13U)
#define MMSYS_MISC_REG_GPIO_77_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_77_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_77_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_O_POS)
#define MMSYS_MISC_REG_GPIO_77_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_77_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_O_POS))
#define MMSYS_MISC_REG_GPIO_78_O                                MMSYS_MISC_REG_GPIO_78_O
#define MMSYS_MISC_REG_GPIO_78_O_POS                            (14U)
#define MMSYS_MISC_REG_GPIO_78_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_78_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_78_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_O_POS)
#define MMSYS_MISC_REG_GPIO_78_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_78_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_O_POS))
#define MMSYS_MISC_REG_GPIO_79_O                                MMSYS_MISC_REG_GPIO_79_O
#define MMSYS_MISC_REG_GPIO_79_O_POS                            (15U)
#define MMSYS_MISC_REG_GPIO_79_O_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_79_O_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_79_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_O_POS)
#define MMSYS_MISC_REG_GPIO_79_O_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_79_O_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_O_POS))

/* 0x2C0 : GPIO_CFGCTL46 */
#define MMSYS_MISC_GPIO_CFGCTL46_OFFSET                         (0x2C0)
#define MMSYS_MISC_REG_GPIO_0_OE                                MMSYS_MISC_REG_GPIO_0_OE
#define MMSYS_MISC_REG_GPIO_0_OE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_0_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_OE_POS)
#define MMSYS_MISC_REG_GPIO_0_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_OE_POS))
#define MMSYS_MISC_REG_GPIO_1_OE                                MMSYS_MISC_REG_GPIO_1_OE
#define MMSYS_MISC_REG_GPIO_1_OE_POS                            (1U)
#define MMSYS_MISC_REG_GPIO_1_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_OE_POS)
#define MMSYS_MISC_REG_GPIO_1_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_OE_POS))
#define MMSYS_MISC_REG_GPIO_2_OE                                MMSYS_MISC_REG_GPIO_2_OE
#define MMSYS_MISC_REG_GPIO_2_OE_POS                            (2U)
#define MMSYS_MISC_REG_GPIO_2_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_2_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_2_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_OE_POS)
#define MMSYS_MISC_REG_GPIO_2_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_2_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_2_OE_POS))
#define MMSYS_MISC_REG_GPIO_3_OE                                MMSYS_MISC_REG_GPIO_3_OE
#define MMSYS_MISC_REG_GPIO_3_OE_POS                            (3U)
#define MMSYS_MISC_REG_GPIO_3_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_3_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_3_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_OE_POS)
#define MMSYS_MISC_REG_GPIO_3_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_3_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_3_OE_POS))
#define MMSYS_MISC_REG_GPIO_4_OE                                MMSYS_MISC_REG_GPIO_4_OE
#define MMSYS_MISC_REG_GPIO_4_OE_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_4_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_4_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_4_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_OE_POS)
#define MMSYS_MISC_REG_GPIO_4_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_4_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_4_OE_POS))
#define MMSYS_MISC_REG_GPIO_5_OE                                MMSYS_MISC_REG_GPIO_5_OE
#define MMSYS_MISC_REG_GPIO_5_OE_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_5_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_5_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_5_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_OE_POS)
#define MMSYS_MISC_REG_GPIO_5_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_5_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_5_OE_POS))
#define MMSYS_MISC_REG_GPIO_6_OE                                MMSYS_MISC_REG_GPIO_6_OE
#define MMSYS_MISC_REG_GPIO_6_OE_POS                            (6U)
#define MMSYS_MISC_REG_GPIO_6_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_6_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_6_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_OE_POS)
#define MMSYS_MISC_REG_GPIO_6_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_6_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_6_OE_POS))
#define MMSYS_MISC_REG_GPIO_7_OE                                MMSYS_MISC_REG_GPIO_7_OE
#define MMSYS_MISC_REG_GPIO_7_OE_POS                            (7U)
#define MMSYS_MISC_REG_GPIO_7_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_7_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_7_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_OE_POS)
#define MMSYS_MISC_REG_GPIO_7_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_7_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_7_OE_POS))
#define MMSYS_MISC_REG_GPIO_8_OE                                MMSYS_MISC_REG_GPIO_8_OE
#define MMSYS_MISC_REG_GPIO_8_OE_POS                            (8U)
#define MMSYS_MISC_REG_GPIO_8_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_8_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_8_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_OE_POS)
#define MMSYS_MISC_REG_GPIO_8_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_8_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_8_OE_POS))
#define MMSYS_MISC_REG_GPIO_9_OE                                MMSYS_MISC_REG_GPIO_9_OE
#define MMSYS_MISC_REG_GPIO_9_OE_POS                            (9U)
#define MMSYS_MISC_REG_GPIO_9_OE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_9_OE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_9_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_OE_POS)
#define MMSYS_MISC_REG_GPIO_9_OE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_9_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_9_OE_POS))
#define MMSYS_MISC_REG_GPIO_10_OE                               MMSYS_MISC_REG_GPIO_10_OE
#define MMSYS_MISC_REG_GPIO_10_OE_POS                           (10U)
#define MMSYS_MISC_REG_GPIO_10_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_10_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_10_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_OE_POS)
#define MMSYS_MISC_REG_GPIO_10_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_10_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_10_OE_POS))
#define MMSYS_MISC_REG_GPIO_11_OE                               MMSYS_MISC_REG_GPIO_11_OE
#define MMSYS_MISC_REG_GPIO_11_OE_POS                           (11U)
#define MMSYS_MISC_REG_GPIO_11_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_11_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_11_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_OE_POS)
#define MMSYS_MISC_REG_GPIO_11_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_11_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_11_OE_POS))
#define MMSYS_MISC_REG_GPIO_12_OE                               MMSYS_MISC_REG_GPIO_12_OE
#define MMSYS_MISC_REG_GPIO_12_OE_POS                           (12U)
#define MMSYS_MISC_REG_GPIO_12_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_12_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_12_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_OE_POS)
#define MMSYS_MISC_REG_GPIO_12_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_12_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_12_OE_POS))
#define MMSYS_MISC_REG_GPIO_13_OE                               MMSYS_MISC_REG_GPIO_13_OE
#define MMSYS_MISC_REG_GPIO_13_OE_POS                           (13U)
#define MMSYS_MISC_REG_GPIO_13_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_13_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_13_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_OE_POS)
#define MMSYS_MISC_REG_GPIO_13_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_13_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_13_OE_POS))
#define MMSYS_MISC_REG_GPIO_14_OE                               MMSYS_MISC_REG_GPIO_14_OE
#define MMSYS_MISC_REG_GPIO_14_OE_POS                           (14U)
#define MMSYS_MISC_REG_GPIO_14_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_14_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_14_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_OE_POS)
#define MMSYS_MISC_REG_GPIO_14_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_14_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_14_OE_POS))
#define MMSYS_MISC_REG_GPIO_15_OE                               MMSYS_MISC_REG_GPIO_15_OE
#define MMSYS_MISC_REG_GPIO_15_OE_POS                           (15U)
#define MMSYS_MISC_REG_GPIO_15_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_15_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_15_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_OE_POS)
#define MMSYS_MISC_REG_GPIO_15_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_15_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_15_OE_POS))
#define MMSYS_MISC_REG_GPIO_16_OE                               MMSYS_MISC_REG_GPIO_16_OE
#define MMSYS_MISC_REG_GPIO_16_OE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_16_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_16_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_16_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_OE_POS)
#define MMSYS_MISC_REG_GPIO_16_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_16_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_16_OE_POS))
#define MMSYS_MISC_REG_GPIO_17_OE                               MMSYS_MISC_REG_GPIO_17_OE
#define MMSYS_MISC_REG_GPIO_17_OE_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_17_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_17_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_17_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_OE_POS)
#define MMSYS_MISC_REG_GPIO_17_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_17_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_17_OE_POS))
#define MMSYS_MISC_REG_GPIO_18_OE                               MMSYS_MISC_REG_GPIO_18_OE
#define MMSYS_MISC_REG_GPIO_18_OE_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_18_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_18_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_18_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_OE_POS)
#define MMSYS_MISC_REG_GPIO_18_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_18_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_18_OE_POS))
#define MMSYS_MISC_REG_GPIO_19_OE                               MMSYS_MISC_REG_GPIO_19_OE
#define MMSYS_MISC_REG_GPIO_19_OE_POS                           (19U)
#define MMSYS_MISC_REG_GPIO_19_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_19_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_19_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_OE_POS)
#define MMSYS_MISC_REG_GPIO_19_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_19_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_19_OE_POS))
#define MMSYS_MISC_REG_GPIO_20_OE                               MMSYS_MISC_REG_GPIO_20_OE
#define MMSYS_MISC_REG_GPIO_20_OE_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_20_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_20_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_20_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_OE_POS)
#define MMSYS_MISC_REG_GPIO_20_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_20_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_20_OE_POS))
#define MMSYS_MISC_REG_GPIO_21_OE                               MMSYS_MISC_REG_GPIO_21_OE
#define MMSYS_MISC_REG_GPIO_21_OE_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_21_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_21_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_21_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_OE_POS)
#define MMSYS_MISC_REG_GPIO_21_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_21_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_21_OE_POS))
#define MMSYS_MISC_REG_GPIO_22_OE                               MMSYS_MISC_REG_GPIO_22_OE
#define MMSYS_MISC_REG_GPIO_22_OE_POS                           (22U)
#define MMSYS_MISC_REG_GPIO_22_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_22_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_22_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_OE_POS)
#define MMSYS_MISC_REG_GPIO_22_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_22_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_22_OE_POS))
#define MMSYS_MISC_REG_GPIO_23_OE                               MMSYS_MISC_REG_GPIO_23_OE
#define MMSYS_MISC_REG_GPIO_23_OE_POS                           (23U)
#define MMSYS_MISC_REG_GPIO_23_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_23_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_23_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_OE_POS)
#define MMSYS_MISC_REG_GPIO_23_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_23_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_23_OE_POS))
#define MMSYS_MISC_REG_GPIO_24_OE                               MMSYS_MISC_REG_GPIO_24_OE
#define MMSYS_MISC_REG_GPIO_24_OE_POS                           (24U)
#define MMSYS_MISC_REG_GPIO_24_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_24_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_24_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_OE_POS)
#define MMSYS_MISC_REG_GPIO_24_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_24_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_24_OE_POS))
#define MMSYS_MISC_REG_GPIO_25_OE                               MMSYS_MISC_REG_GPIO_25_OE
#define MMSYS_MISC_REG_GPIO_25_OE_POS                           (25U)
#define MMSYS_MISC_REG_GPIO_25_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_25_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_25_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_OE_POS)
#define MMSYS_MISC_REG_GPIO_25_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_25_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_25_OE_POS))
#define MMSYS_MISC_REG_GPIO_26_OE                               MMSYS_MISC_REG_GPIO_26_OE
#define MMSYS_MISC_REG_GPIO_26_OE_POS                           (26U)
#define MMSYS_MISC_REG_GPIO_26_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_26_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_26_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_OE_POS)
#define MMSYS_MISC_REG_GPIO_26_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_26_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_26_OE_POS))
#define MMSYS_MISC_REG_GPIO_27_OE                               MMSYS_MISC_REG_GPIO_27_OE
#define MMSYS_MISC_REG_GPIO_27_OE_POS                           (27U)
#define MMSYS_MISC_REG_GPIO_27_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_27_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_27_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_OE_POS)
#define MMSYS_MISC_REG_GPIO_27_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_27_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_27_OE_POS))
#define MMSYS_MISC_REG_GPIO_28_OE                               MMSYS_MISC_REG_GPIO_28_OE
#define MMSYS_MISC_REG_GPIO_28_OE_POS                           (28U)
#define MMSYS_MISC_REG_GPIO_28_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_28_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_28_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_OE_POS)
#define MMSYS_MISC_REG_GPIO_28_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_28_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_28_OE_POS))
#define MMSYS_MISC_REG_GPIO_29_OE                               MMSYS_MISC_REG_GPIO_29_OE
#define MMSYS_MISC_REG_GPIO_29_OE_POS                           (29U)
#define MMSYS_MISC_REG_GPIO_29_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_29_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_29_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_OE_POS)
#define MMSYS_MISC_REG_GPIO_29_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_29_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_29_OE_POS))
#define MMSYS_MISC_REG_GPIO_30_OE                               MMSYS_MISC_REG_GPIO_30_OE
#define MMSYS_MISC_REG_GPIO_30_OE_POS                           (30U)
#define MMSYS_MISC_REG_GPIO_30_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_30_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_30_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_OE_POS)
#define MMSYS_MISC_REG_GPIO_30_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_30_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_30_OE_POS))
#define MMSYS_MISC_REG_GPIO_31_OE                               MMSYS_MISC_REG_GPIO_31_OE
#define MMSYS_MISC_REG_GPIO_31_OE_POS                           (31U)
#define MMSYS_MISC_REG_GPIO_31_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_31_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_31_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_OE_POS)
#define MMSYS_MISC_REG_GPIO_31_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_31_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_31_OE_POS))

/* 0x2C4 : GPIO_CFGCTL47 */
#define MMSYS_MISC_GPIO_CFGCTL47_OFFSET                         (0x2C4)
#define MMSYS_MISC_REG_GPIO_32_OE                               MMSYS_MISC_REG_GPIO_32_OE
#define MMSYS_MISC_REG_GPIO_32_OE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_32_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_32_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_32_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_OE_POS)
#define MMSYS_MISC_REG_GPIO_32_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_32_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_32_OE_POS))
#define MMSYS_MISC_REG_GPIO_33_OE                               MMSYS_MISC_REG_GPIO_33_OE
#define MMSYS_MISC_REG_GPIO_33_OE_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_33_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_33_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_33_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_OE_POS)
#define MMSYS_MISC_REG_GPIO_33_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_33_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_33_OE_POS))
#define MMSYS_MISC_REG_GPIO_34_OE                               MMSYS_MISC_REG_GPIO_34_OE
#define MMSYS_MISC_REG_GPIO_34_OE_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_34_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_34_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_34_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_OE_POS)
#define MMSYS_MISC_REG_GPIO_34_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_34_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_34_OE_POS))
#define MMSYS_MISC_REG_GPIO_35_OE                               MMSYS_MISC_REG_GPIO_35_OE
#define MMSYS_MISC_REG_GPIO_35_OE_POS                           (3U)
#define MMSYS_MISC_REG_GPIO_35_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_35_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_35_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_OE_POS)
#define MMSYS_MISC_REG_GPIO_35_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_35_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_35_OE_POS))
#define MMSYS_MISC_REG_GPIO_36_OE                               MMSYS_MISC_REG_GPIO_36_OE
#define MMSYS_MISC_REG_GPIO_36_OE_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_36_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_36_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_36_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_OE_POS)
#define MMSYS_MISC_REG_GPIO_36_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_36_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_36_OE_POS))
#define MMSYS_MISC_REG_GPIO_37_OE                               MMSYS_MISC_REG_GPIO_37_OE
#define MMSYS_MISC_REG_GPIO_37_OE_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_37_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_37_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_37_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_OE_POS)
#define MMSYS_MISC_REG_GPIO_37_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_37_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_37_OE_POS))
#define MMSYS_MISC_REG_GPIO_38_OE                               MMSYS_MISC_REG_GPIO_38_OE
#define MMSYS_MISC_REG_GPIO_38_OE_POS                           (6U)
#define MMSYS_MISC_REG_GPIO_38_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_38_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_38_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_OE_POS)
#define MMSYS_MISC_REG_GPIO_38_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_38_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_38_OE_POS))
#define MMSYS_MISC_REG_GPIO_39_OE                               MMSYS_MISC_REG_GPIO_39_OE
#define MMSYS_MISC_REG_GPIO_39_OE_POS                           (7U)
#define MMSYS_MISC_REG_GPIO_39_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_39_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_39_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_OE_POS)
#define MMSYS_MISC_REG_GPIO_39_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_39_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_39_OE_POS))
#define MMSYS_MISC_REG_GPIO_40_OE                               MMSYS_MISC_REG_GPIO_40_OE
#define MMSYS_MISC_REG_GPIO_40_OE_POS                           (8U)
#define MMSYS_MISC_REG_GPIO_40_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_40_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_40_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_OE_POS)
#define MMSYS_MISC_REG_GPIO_40_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_40_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_40_OE_POS))
#define MMSYS_MISC_REG_GPIO_41_OE                               MMSYS_MISC_REG_GPIO_41_OE
#define MMSYS_MISC_REG_GPIO_41_OE_POS                           (9U)
#define MMSYS_MISC_REG_GPIO_41_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_41_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_41_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_OE_POS)
#define MMSYS_MISC_REG_GPIO_41_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_41_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_41_OE_POS))
#define MMSYS_MISC_REG_GPIO_42_OE                               MMSYS_MISC_REG_GPIO_42_OE
#define MMSYS_MISC_REG_GPIO_42_OE_POS                           (10U)
#define MMSYS_MISC_REG_GPIO_42_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_42_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_42_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_OE_POS)
#define MMSYS_MISC_REG_GPIO_42_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_42_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_42_OE_POS))
#define MMSYS_MISC_REG_GPIO_43_OE                               MMSYS_MISC_REG_GPIO_43_OE
#define MMSYS_MISC_REG_GPIO_43_OE_POS                           (11U)
#define MMSYS_MISC_REG_GPIO_43_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_43_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_43_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_OE_POS)
#define MMSYS_MISC_REG_GPIO_43_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_43_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_43_OE_POS))
#define MMSYS_MISC_REG_GPIO_44_OE                               MMSYS_MISC_REG_GPIO_44_OE
#define MMSYS_MISC_REG_GPIO_44_OE_POS                           (12U)
#define MMSYS_MISC_REG_GPIO_44_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_44_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_44_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_OE_POS)
#define MMSYS_MISC_REG_GPIO_44_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_44_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_44_OE_POS))
#define MMSYS_MISC_REG_GPIO_45_OE                               MMSYS_MISC_REG_GPIO_45_OE
#define MMSYS_MISC_REG_GPIO_45_OE_POS                           (13U)
#define MMSYS_MISC_REG_GPIO_45_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_45_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_45_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_OE_POS)
#define MMSYS_MISC_REG_GPIO_45_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_45_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_45_OE_POS))
#define MMSYS_MISC_REG_GPIO_46_OE                               MMSYS_MISC_REG_GPIO_46_OE
#define MMSYS_MISC_REG_GPIO_46_OE_POS                           (14U)
#define MMSYS_MISC_REG_GPIO_46_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_46_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_46_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_OE_POS)
#define MMSYS_MISC_REG_GPIO_46_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_46_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_46_OE_POS))
#define MMSYS_MISC_REG_GPIO_47_OE                               MMSYS_MISC_REG_GPIO_47_OE
#define MMSYS_MISC_REG_GPIO_47_OE_POS                           (15U)
#define MMSYS_MISC_REG_GPIO_47_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_47_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_47_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_OE_POS)
#define MMSYS_MISC_REG_GPIO_47_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_47_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_47_OE_POS))
#define MMSYS_MISC_REG_GPIO_48_OE                               MMSYS_MISC_REG_GPIO_48_OE
#define MMSYS_MISC_REG_GPIO_48_OE_POS                           (16U)
#define MMSYS_MISC_REG_GPIO_48_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_48_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_48_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_OE_POS)
#define MMSYS_MISC_REG_GPIO_48_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_48_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_48_OE_POS))
#define MMSYS_MISC_REG_GPIO_49_OE                               MMSYS_MISC_REG_GPIO_49_OE
#define MMSYS_MISC_REG_GPIO_49_OE_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_49_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_49_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_49_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_OE_POS)
#define MMSYS_MISC_REG_GPIO_49_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_49_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_49_OE_POS))
#define MMSYS_MISC_REG_GPIO_50_OE                               MMSYS_MISC_REG_GPIO_50_OE
#define MMSYS_MISC_REG_GPIO_50_OE_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_50_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_50_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_50_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_OE_POS)
#define MMSYS_MISC_REG_GPIO_50_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_50_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_50_OE_POS))
#define MMSYS_MISC_REG_GPIO_51_OE                               MMSYS_MISC_REG_GPIO_51_OE
#define MMSYS_MISC_REG_GPIO_51_OE_POS                           (19U)
#define MMSYS_MISC_REG_GPIO_51_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_51_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_51_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_OE_POS)
#define MMSYS_MISC_REG_GPIO_51_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_51_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_51_OE_POS))
#define MMSYS_MISC_REG_GPIO_52_OE                               MMSYS_MISC_REG_GPIO_52_OE
#define MMSYS_MISC_REG_GPIO_52_OE_POS                           (20U)
#define MMSYS_MISC_REG_GPIO_52_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_52_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_52_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_OE_POS)
#define MMSYS_MISC_REG_GPIO_52_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_52_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_52_OE_POS))
#define MMSYS_MISC_REG_GPIO_53_OE                               MMSYS_MISC_REG_GPIO_53_OE
#define MMSYS_MISC_REG_GPIO_53_OE_POS                           (21U)
#define MMSYS_MISC_REG_GPIO_53_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_53_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_53_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_OE_POS)
#define MMSYS_MISC_REG_GPIO_53_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_53_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_53_OE_POS))
#define MMSYS_MISC_REG_GPIO_54_OE                               MMSYS_MISC_REG_GPIO_54_OE
#define MMSYS_MISC_REG_GPIO_54_OE_POS                           (22U)
#define MMSYS_MISC_REG_GPIO_54_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_54_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_54_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_OE_POS)
#define MMSYS_MISC_REG_GPIO_54_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_54_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_54_OE_POS))
#define MMSYS_MISC_REG_GPIO_55_OE                               MMSYS_MISC_REG_GPIO_55_OE
#define MMSYS_MISC_REG_GPIO_55_OE_POS                           (23U)
#define MMSYS_MISC_REG_GPIO_55_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_55_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_55_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_OE_POS)
#define MMSYS_MISC_REG_GPIO_55_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_55_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_55_OE_POS))
#define MMSYS_MISC_REG_GPIO_56_OE                               MMSYS_MISC_REG_GPIO_56_OE
#define MMSYS_MISC_REG_GPIO_56_OE_POS                           (24U)
#define MMSYS_MISC_REG_GPIO_56_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_56_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_56_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_OE_POS)
#define MMSYS_MISC_REG_GPIO_56_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_56_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_56_OE_POS))
#define MMSYS_MISC_REG_GPIO_57_OE                               MMSYS_MISC_REG_GPIO_57_OE
#define MMSYS_MISC_REG_GPIO_57_OE_POS                           (25U)
#define MMSYS_MISC_REG_GPIO_57_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_57_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_57_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_OE_POS)
#define MMSYS_MISC_REG_GPIO_57_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_57_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_57_OE_POS))
#define MMSYS_MISC_REG_GPIO_58_OE                               MMSYS_MISC_REG_GPIO_58_OE
#define MMSYS_MISC_REG_GPIO_58_OE_POS                           (26U)
#define MMSYS_MISC_REG_GPIO_58_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_58_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_58_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_OE_POS)
#define MMSYS_MISC_REG_GPIO_58_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_58_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_58_OE_POS))
#define MMSYS_MISC_REG_GPIO_59_OE                               MMSYS_MISC_REG_GPIO_59_OE
#define MMSYS_MISC_REG_GPIO_59_OE_POS                           (27U)
#define MMSYS_MISC_REG_GPIO_59_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_59_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_59_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_OE_POS)
#define MMSYS_MISC_REG_GPIO_59_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_59_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_59_OE_POS))
#define MMSYS_MISC_REG_GPIO_60_OE                               MMSYS_MISC_REG_GPIO_60_OE
#define MMSYS_MISC_REG_GPIO_60_OE_POS                           (28U)
#define MMSYS_MISC_REG_GPIO_60_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_60_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_60_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_OE_POS)
#define MMSYS_MISC_REG_GPIO_60_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_60_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_60_OE_POS))
#define MMSYS_MISC_REG_GPIO_61_OE                               MMSYS_MISC_REG_GPIO_61_OE
#define MMSYS_MISC_REG_GPIO_61_OE_POS                           (29U)
#define MMSYS_MISC_REG_GPIO_61_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_61_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_61_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_OE_POS)
#define MMSYS_MISC_REG_GPIO_61_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_61_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_61_OE_POS))
#define MMSYS_MISC_REG_GPIO_62_OE                               MMSYS_MISC_REG_GPIO_62_OE
#define MMSYS_MISC_REG_GPIO_62_OE_POS                           (30U)
#define MMSYS_MISC_REG_GPIO_62_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_62_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_62_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_OE_POS)
#define MMSYS_MISC_REG_GPIO_62_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_62_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_62_OE_POS))
#define MMSYS_MISC_REG_GPIO_63_OE                               MMSYS_MISC_REG_GPIO_63_OE
#define MMSYS_MISC_REG_GPIO_63_OE_POS                           (31U)
#define MMSYS_MISC_REG_GPIO_63_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_63_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_63_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_OE_POS)
#define MMSYS_MISC_REG_GPIO_63_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_63_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_63_OE_POS))

/* 0x2C8 : GPIO_CFGCTL48 */
#define MMSYS_MISC_GPIO_CFGCTL48_OFFSET                         (0x2C8)
#define MMSYS_MISC_REG_GPIO_64_OE                               MMSYS_MISC_REG_GPIO_64_OE
#define MMSYS_MISC_REG_GPIO_64_OE_POS                           (0U)
#define MMSYS_MISC_REG_GPIO_64_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_64_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_64_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_OE_POS)
#define MMSYS_MISC_REG_GPIO_64_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_64_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_64_OE_POS))
#define MMSYS_MISC_REG_GPIO_65_OE                               MMSYS_MISC_REG_GPIO_65_OE
#define MMSYS_MISC_REG_GPIO_65_OE_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_65_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_65_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_65_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_OE_POS)
#define MMSYS_MISC_REG_GPIO_65_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_65_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_65_OE_POS))
#define MMSYS_MISC_REG_GPIO_66_OE                               MMSYS_MISC_REG_GPIO_66_OE
#define MMSYS_MISC_REG_GPIO_66_OE_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_66_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_66_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_66_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_OE_POS)
#define MMSYS_MISC_REG_GPIO_66_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_66_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_66_OE_POS))
#define MMSYS_MISC_REG_GPIO_67_OE                               MMSYS_MISC_REG_GPIO_67_OE
#define MMSYS_MISC_REG_GPIO_67_OE_POS                           (3U)
#define MMSYS_MISC_REG_GPIO_67_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_67_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_67_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_OE_POS)
#define MMSYS_MISC_REG_GPIO_67_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_67_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_67_OE_POS))
#define MMSYS_MISC_REG_GPIO_68_OE                               MMSYS_MISC_REG_GPIO_68_OE
#define MMSYS_MISC_REG_GPIO_68_OE_POS                           (4U)
#define MMSYS_MISC_REG_GPIO_68_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_68_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_68_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_OE_POS)
#define MMSYS_MISC_REG_GPIO_68_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_68_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_68_OE_POS))
#define MMSYS_MISC_REG_GPIO_69_OE                               MMSYS_MISC_REG_GPIO_69_OE
#define MMSYS_MISC_REG_GPIO_69_OE_POS                           (5U)
#define MMSYS_MISC_REG_GPIO_69_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_69_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_69_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_OE_POS)
#define MMSYS_MISC_REG_GPIO_69_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_69_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_69_OE_POS))
#define MMSYS_MISC_REG_GPIO_70_OE                               MMSYS_MISC_REG_GPIO_70_OE
#define MMSYS_MISC_REG_GPIO_70_OE_POS                           (6U)
#define MMSYS_MISC_REG_GPIO_70_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_70_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_70_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_OE_POS)
#define MMSYS_MISC_REG_GPIO_70_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_70_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_70_OE_POS))
#define MMSYS_MISC_REG_GPIO_71_OE                               MMSYS_MISC_REG_GPIO_71_OE
#define MMSYS_MISC_REG_GPIO_71_OE_POS                           (7U)
#define MMSYS_MISC_REG_GPIO_71_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_71_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_71_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_OE_POS)
#define MMSYS_MISC_REG_GPIO_71_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_71_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_71_OE_POS))
#define MMSYS_MISC_REG_GPIO_72_OE                               MMSYS_MISC_REG_GPIO_72_OE
#define MMSYS_MISC_REG_GPIO_72_OE_POS                           (8U)
#define MMSYS_MISC_REG_GPIO_72_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_72_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_72_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_OE_POS)
#define MMSYS_MISC_REG_GPIO_72_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_72_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_72_OE_POS))
#define MMSYS_MISC_REG_GPIO_73_OE                               MMSYS_MISC_REG_GPIO_73_OE
#define MMSYS_MISC_REG_GPIO_73_OE_POS                           (9U)
#define MMSYS_MISC_REG_GPIO_73_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_73_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_73_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_OE_POS)
#define MMSYS_MISC_REG_GPIO_73_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_73_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_73_OE_POS))
#define MMSYS_MISC_REG_GPIO_74_OE                               MMSYS_MISC_REG_GPIO_74_OE
#define MMSYS_MISC_REG_GPIO_74_OE_POS                           (10U)
#define MMSYS_MISC_REG_GPIO_74_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_74_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_74_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_OE_POS)
#define MMSYS_MISC_REG_GPIO_74_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_74_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_74_OE_POS))
#define MMSYS_MISC_REG_GPIO_75_OE                               MMSYS_MISC_REG_GPIO_75_OE
#define MMSYS_MISC_REG_GPIO_75_OE_POS                           (11U)
#define MMSYS_MISC_REG_GPIO_75_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_75_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_75_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_OE_POS)
#define MMSYS_MISC_REG_GPIO_75_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_75_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_75_OE_POS))
#define MMSYS_MISC_REG_GPIO_76_OE                               MMSYS_MISC_REG_GPIO_76_OE
#define MMSYS_MISC_REG_GPIO_76_OE_POS                           (12U)
#define MMSYS_MISC_REG_GPIO_76_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_76_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_76_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_OE_POS)
#define MMSYS_MISC_REG_GPIO_76_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_76_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_76_OE_POS))
#define MMSYS_MISC_REG_GPIO_77_OE                               MMSYS_MISC_REG_GPIO_77_OE
#define MMSYS_MISC_REG_GPIO_77_OE_POS                           (13U)
#define MMSYS_MISC_REG_GPIO_77_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_77_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_77_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_OE_POS)
#define MMSYS_MISC_REG_GPIO_77_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_77_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_77_OE_POS))
#define MMSYS_MISC_REG_GPIO_78_OE                               MMSYS_MISC_REG_GPIO_78_OE
#define MMSYS_MISC_REG_GPIO_78_OE_POS                           (14U)
#define MMSYS_MISC_REG_GPIO_78_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_78_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_78_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_OE_POS)
#define MMSYS_MISC_REG_GPIO_78_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_78_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_78_OE_POS))
#define MMSYS_MISC_REG_GPIO_79_OE                               MMSYS_MISC_REG_GPIO_79_OE
#define MMSYS_MISC_REG_GPIO_79_OE_POS                           (15U)
#define MMSYS_MISC_REG_GPIO_79_OE_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_79_OE_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_79_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_OE_POS)
#define MMSYS_MISC_REG_GPIO_79_OE_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_79_OE_LEN)-1)<<MMSYS_MISC_REG_GPIO_79_OE_POS))

#define MMSYS_MISC_REG_DBG_LL_CTRL_OFFSET                    (0x2d0)
#define MMSYS_MISC_REG_DBG_LL                                              MMSYS_MISC_REG_DBG_LL
#define MMSYS_MISC_REG_DBG_LL_POS                                     (0U)
#define MMSYS_MISC_REG_DBG_LL_LEN                                      (32U)
#define MMSYS_MISC_REG_DBG_LL_MSK                                     (0xFFFFFFFFU)
#define MMSYS_MISC_REG_DBG_LL_UMSK                                   (0U)

struct  mmsys_misc_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[32];

    /* 0x20 : peri_apb_ctrl */
    union {
        struct {
            uint32_t rg_pclk_force_on               : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } peri_apb_ctrl;

    /* 0x24 : mm_infra_ctrl */
    union {
        struct {
            uint32_t reg_m42emi_addr_bank           :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t reg_m42emi_w_thre              :  3; /* [ 6: 4],        r/w,        0x2 */
            uint32_t reserved_7_15                  :  9; /* [15: 7],       rsvd,        0x0 */
            uint32_t reg_reg2mem_w_thre             :  3; /* [18:16],        r/w,        0x2 */
            uint32_t reserved_19_31                 : 13; /* [31:19],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_ctrl;

    /* 0x28 : emi_infra_ctrl */
    union {
        struct {
            uint32_t reg_cpu2emi_w_thre             :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t reg_mm2emiA_w_thre             :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_mm2emiB_w_thre             :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } emi_infra_ctrl;

    /* 0x2C : mm_infra_qos_ctrl */
    union {
        struct {
            uint32_t reg_m4id2emi_awqos             :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_m4id2emi_arqos             :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_a52vram_awqos              :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_a52vram_arqos              :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_a52emi_awqos               :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_a52emi_arqos               :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_e74mem_awqos               :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_e74mem_arqos               :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_e74sys_awqos               :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_e74sys_arqos               :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg2emi_awqos                  :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg2emi_arqos                  :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg2vram_awqos                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg2vram_arqos                 :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_nr3d_awqos                 :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_nr3d_arqos                 :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_sdh_awqos                  :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_sdh_arqos                  :  1; /* [   17],        r/w,        0x0 */
            uint32_t reg_codec_fo_awqos             :  1; /* [   18],        r/w,        0x0 */
            uint32_t reg_codec_fi_arqos             :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_codec_fo2_awqos            :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_codec_fi2_arqos            :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_h264_ref_awqos             :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_h264_ref_arqos             :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_h264_ext_awqos             :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_h264_ext_arqos             :  1; /* [   25],        r/w,        0x0 */
            uint32_t reg_d2bA_awqos                 :  1; /* [   26],        r/w,        0x0 */
            uint32_t reg_d2bB_awqos                 :  1; /* [   27],        r/w,        0x0 */
            uint32_t reg_d2bC_awqos                 :  1; /* [   28],        r/w,        0x0 */
            uint32_t reg_d2bD_awqos                 :  1; /* [   29],        r/w,        0x0 */
            uint32_t reg_isp_dtsrc_arqos            :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_hdmi_dtsrc_arqos           :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_qos_ctrl;

    /* 0x30 : mm_infra_bus_error */
    union {
        struct {
            uint32_t reg_mi_dec_err_clr             :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_mi_dec_err_latch_last      :  1; /* [    1],        r/w,        0x0 */
            uint32_t mm_infra_dec_err               :  1; /* [    2],          r,        0x0 */
            uint32_t mm_infra_dec_err_write         :  1; /* [    3],          r,        0x0 */
            uint32_t mm_infra_dec_err_src           :  3; /* [ 6: 4],          r,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t mm_infra_dec_err_id            :  8; /* [15: 8],          r,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_bus_error;

    /* 0x34 : mm_infra_bus_error_addr */
    union {
        struct {
            uint32_t mm_infra_dec_err_addr          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } mm_infra_bus_error_addr;

    /* 0x38 : emi_bus_error */
    union {
        struct {
            uint32_t reg_emi_dec_err_clr            :  1; /* [    0],        w1p,        0x0 */
            uint32_t reg_emi_dec_err_latch_last     :  1; /* [    1],        r/w,        0x0 */
            uint32_t emi_dec_err                    :  1; /* [    2],          r,        0x0 */
            uint32_t emi_dec_err_write              :  1; /* [    3],          r,        0x0 */
            uint32_t emi_dec_err_src                :  2; /* [ 5: 4],          r,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t emi_dec_err_id                 :  9; /* [16: 8],          r,        0x0 */
            uint32_t reserved_17_31                 : 15; /* [31:17],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } emi_bus_error;

    /* 0x3C : emi_bus_error_addr */
    union {
        struct {
            uint32_t emi_dec_err_addr               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } emi_bus_error_addr;

    /* 0x40 : dma_clk_ctrl */
    union {
        struct {
            uint32_t dma_clk_en                     :  8; /* [ 7: 0],        r/w,       0xff */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dma_clk_ctrl;

    /* 0x44  reserved */
    uint8_t RESERVED0x44[28];

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
    uint8_t RESERVED0x70[128];

    /* 0xF0 : gpio_ctl */
    union {
        struct {
            uint32_t reg_debug_oe                   :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_spi_master_mode            :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_spi_swap                   :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31                  : 29; /* [31: 3],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpio_ctl;

    /* 0xf4  reserved */
    uint8_t RESERVED0xf4[8];

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

    /* 0x104  reserved */
    uint8_t RESERVED0x104[252];

    /* 0x200 : GPIO_CFGCTL0 */
    union {
        struct {
            uint32_t reg_gpio_0_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_0_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_0_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_0_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_0_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_0_func_sel            :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_1_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_1_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_1_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_1_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_1_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_1_func_sel            :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL0;

    /* 0x204 : GPIO_CFGCTL1 */
    union {
        struct {
            uint32_t reg_gpio_2_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_2_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_2_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_2_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_2_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_2_func_sel            :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_3_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_3_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_3_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_3_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_3_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_3_func_sel            :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL1;

    /* 0x208 : GPIO_CFGCTL2 */
    union {
        struct {
            uint32_t reg_gpio_4_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_4_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_4_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_4_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_4_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_4_func_sel            :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_5_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_5_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_5_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_5_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_5_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_5_func_sel            :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL2;

    /* 0x20C : GPIO_CFGCTL3 */
    union {
        struct {
            uint32_t reg_gpio_6_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_6_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_6_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_6_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_6_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_6_func_sel            :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_7_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_7_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_7_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_7_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_7_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_7_func_sel            :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL3;

    /* 0x210 : GPIO_CFGCTL4 */
    union {
        struct {
            uint32_t reg_gpio_8_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_8_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_8_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_8_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_8_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_8_func_sel            :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_9_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_9_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_9_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_9_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_9_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_9_func_sel            :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL4;

    /* 0x214 : GPIO_CFGCTL5 */
    union {
        struct {
            uint32_t reg_gpio_10_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_10_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_10_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_10_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_10_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_10_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_11_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_11_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_11_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_11_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_11_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_11_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL5;

    /* 0x218 : GPIO_CFGCTL6 */
    union {
        struct {
            uint32_t reg_gpio_12_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_12_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_12_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_12_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_12_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_12_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_13_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_13_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_13_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_13_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_13_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_13_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL6;

    /* 0x21C : GPIO_CFGCTL7 */
    union {
        struct {
            uint32_t reg_gpio_14_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_14_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_14_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_14_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_14_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_14_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_15_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_15_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_15_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_15_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_15_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_15_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL7;

    /* 0x220 : GPIO_CFGCTL8 */
    union {
        struct {
            uint32_t reg_gpio_16_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_16_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_16_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_16_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_16_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_16_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_17_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_17_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_17_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_17_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_17_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_17_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL8;

    /* 0x224 : GPIO_CFGCTL9 */
    union {
        struct {
            uint32_t reg_gpio_18_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_18_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_18_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_18_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_18_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_18_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_19_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_19_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_19_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_19_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_19_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_19_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL9;

    /* 0x228 : GPIO_CFGCTL10 */
    union {
        struct {
            uint32_t reg_gpio_20_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_20_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_20_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_20_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_20_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_20_func_sel           :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_21_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_21_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_21_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_21_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_21_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_21_func_sel           :  4; /* [27:24],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL10;

    /* 0x22C : GPIO_CFGCTL11 */
    union {
        struct {
            uint32_t reg_gpio_22_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_22_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_22_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_22_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_22_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_22_func_sel           :  4; /* [11: 8],        r/w,        0x1 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_23_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_23_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_23_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_23_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_23_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_23_func_sel           :  4; /* [27:24],        r/w,        0x1 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL11;

    /* 0x230 : GPIO_CFGCTL12 */
    union {
        struct {
            uint32_t reg_gpio_24_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_24_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_24_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_24_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_24_pd                 :  1; /* [    5],        r/w,        0x1 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_24_func_sel           :  4; /* [11: 8],        r/w,        0xc */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_25_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_25_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_25_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_25_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_25_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_25_func_sel           :  4; /* [27:24],        r/w,        0xc */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL12;

    /* 0x234 : GPIO_CFGCTL13 */
    union {
        struct {
            uint32_t reg_gpio_26_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_26_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_26_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_26_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_26_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_26_func_sel           :  4; /* [11: 8],        r/w,        0xc */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_27_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_27_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_27_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_27_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_27_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_27_func_sel           :  4; /* [27:24],        r/w,        0xc */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL13;

    /* 0x238 : GPIO_CFGCTL14 */
    union {
        struct {
            uint32_t reg_gpio_28_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_28_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_28_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_28_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_28_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_28_func_sel           :  4; /* [11: 8],        r/w,        0xd */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_29_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_29_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_29_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_29_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_29_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_29_func_sel           :  4; /* [27:24],        r/w,        0xd */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL14;

    /* 0x23C : GPIO_CFGCTL15 */
    union {
        struct {
            uint32_t reg_gpio_30_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_30_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_30_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_30_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_30_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_30_func_sel           :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_31_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_31_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_31_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_31_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_31_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_31_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL15;

    /* 0x240 : GPIO_CFGCTL16 */
    union {
        struct {
            uint32_t reg_gpio_32_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_32_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_32_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_32_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_32_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_32_func_sel           :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_33_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_33_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_33_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_33_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_33_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_33_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL16;

    /* 0x244 : GPIO_CFGCTL17 */
    union {
        struct {
            uint32_t reg_gpio_34_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_34_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_34_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_34_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_34_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_34_func_sel           :  4; /* [11: 8],        r/w,        0xe */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_35_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_35_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_35_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_35_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_35_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_35_func_sel           :  4; /* [27:24],        r/w,        0xe */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL17;

    /* 0x248 : GPIO_CFGCTL18 */
    union {
        struct {
            uint32_t reg_gpio_36_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_36_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_36_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_36_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_36_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_36_func_sel           :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_37_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_37_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_37_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_37_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_37_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_37_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL18;

    /* 0x24C : GPIO_CFGCTL19 */
    union {
        struct {
            uint32_t reg_gpio_38_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_38_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_38_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_38_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_38_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_38_func_sel           :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_39_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_39_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_39_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_39_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_39_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_39_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL19;

    /* 0x250 : GPIO_CFGCTL20 */
    union {
        struct {
            uint32_t reg_gpio_40_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_40_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_40_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_40_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_40_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_40_func_sel           :  4; /* [11: 8],        r/w,        0x4 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_41_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_41_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_41_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_41_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_41_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_41_func_sel           :  4; /* [27:24],        r/w,        0x4 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL20;

    /* 0x254 : GPIO_CFGCTL21 */
    union {
        struct {
            uint32_t reg_gpio_42_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_42_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_42_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_42_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_42_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_42_func_sel           :  4; /* [11: 8],        r/w,        0x4 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_43_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_43_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_43_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_43_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_43_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_43_func_sel           :  4; /* [27:24],        r/w,        0x4 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL21;

    /* 0x258 : GPIO_CFGCTL22 */
    union {
        struct {
            uint32_t reg_gpio_44_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_44_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_44_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_44_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_44_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_44_func_sel           :  4; /* [11: 8],        r/w,        0x4 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_45_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_45_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_45_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_45_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_45_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_45_func_sel           :  4; /* [27:24],        r/w,        0x4 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL22;

    /* 0x25C : GPIO_CFGCTL23 */
    union {
        struct {
            uint32_t reg_gpio_46_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_46_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_46_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_46_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_46_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_46_func_sel           :  4; /* [11: 8],        r/w,        0x3 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_47_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_47_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_47_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_47_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_47_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_47_func_sel           :  4; /* [27:24],        r/w,        0x3 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL23;

    /* 0x260 : GPIO_CFGCTL24 */
    union {
        struct {
            uint32_t reg_gpio_48_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_48_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_48_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_48_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_48_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_48_func_sel           :  4; /* [11: 8],        r/w,        0x3 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_49_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_49_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_49_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_49_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_49_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_49_func_sel           :  4; /* [27:24],        r/w,        0x3 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL24;

    /* 0x264 : GPIO_CFGCTL25 */
    union {
        struct {
            uint32_t reg_gpio_50_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_50_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_50_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_50_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_50_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_50_func_sel           :  4; /* [11: 8],        r/w,        0xb */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_51_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_51_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_51_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_51_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_51_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_51_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL25;

    /* 0x268 : GPIO_CFGCTL26 */
    union {
        struct {
            uint32_t reg_gpio_52_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_52_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_52_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_52_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_52_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_52_func_sel           :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_53_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_53_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_53_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_53_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_53_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_53_func_sel           :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL26;

    /* 0x26C : GPIO_CFGCTL27 */
    union {
        struct {
            uint32_t reg_gpio_54_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_54_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_54_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_54_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_54_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_55_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_55_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_55_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_55_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_55_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL27;

    /* 0x270 : GPIO_CFGCTL28 */
    union {
        struct {
            uint32_t reg_gpio_56_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_56_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_56_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_56_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_56_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_57_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_57_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_57_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_57_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_57_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL28;

    /* 0x274 : GPIO_CFGCTL29 */
    union {
        struct {
            uint32_t reg_gpio_58_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_58_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_58_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_58_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_58_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_59_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_59_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_59_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_59_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_59_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL29;

    /* 0x278 : GPIO_CFGCTL30 */
    union {
        struct {
            uint32_t reg_gpio_60_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_60_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_60_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_60_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_60_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_61_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_61_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_61_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_61_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_61_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL30;

    /* 0x27C : GPIO_CFGCTL31 */
    union {
        struct {
            uint32_t reg_gpio_62_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_62_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_62_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_62_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_62_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_63_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_63_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_63_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_63_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_63_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL31;

    /* 0x280 : GPIO_CFGCTL32 */
    union {
        struct {
            uint32_t reg_gpio_64_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_64_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_64_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_64_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_64_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_65_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_65_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_65_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_65_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_65_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL32;

    /* 0x284 : GPIO_CFGCTL33 */
    union {
        struct {
            uint32_t reg_gpio_66_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_66_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_66_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_66_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_66_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_67_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_67_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_67_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_67_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_67_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL33;

    /* 0x288 : GPIO_CFGCTL34 */
    union {
        struct {
            uint32_t reg_gpio_68_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_68_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_68_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_68_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_68_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_69_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_69_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_69_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_69_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_69_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL34;

    /* 0x28C : GPIO_CFGCTL35 */
    union {
        struct {
            uint32_t reg_gpio_70_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_70_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_70_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_70_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_70_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_71_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_71_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_71_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_71_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_71_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL35;

    /* 0x290 : GPIO_CFGCTL36 */
    union {
        struct {
            uint32_t reg_gpio_72_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_72_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_72_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_72_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_72_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_73_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_73_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_73_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_73_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_73_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL36;

    /* 0x294 : GPIO_CFGCTL37 */
    union {
        struct {
            uint32_t reg_gpio_74_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_74_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_74_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_74_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_74_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_75_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_75_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_75_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_75_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_75_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL37;

    /* 0x298 : GPIO_CFGCTL38 */
    union {
        struct {
            uint32_t reg_gpio_76_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_76_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_76_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_76_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_76_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_77_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_77_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_77_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_77_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_77_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL38;

    /* 0x29C : GPIO_CFGCTL39 */
    union {
        struct {
            uint32_t reg_gpio_78_ie                 :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_78_smt                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_78_drv                :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_78_pu                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_78_pd                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_15                  : 10; /* [15: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_79_ie                 :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_79_smt                :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_79_drv                :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_79_pu                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_79_pd                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_31                 : 10; /* [31:22],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL39;

    /* 0x2A0 : GPIO_CFGCTL40 */
    union {
        struct {
            uint32_t reg_gpio_0_i                   :  1; /* [    0],          r,        0x0 */
            uint32_t reg_gpio_1_i                   :  1; /* [    1],          r,        0x0 */
            uint32_t reg_gpio_2_i                   :  1; /* [    2],          r,        0x0 */
            uint32_t reg_gpio_3_i                   :  1; /* [    3],          r,        0x0 */
            uint32_t reg_gpio_4_i                   :  1; /* [    4],          r,        0x0 */
            uint32_t reg_gpio_5_i                   :  1; /* [    5],          r,        0x0 */
            uint32_t reg_gpio_6_i                   :  1; /* [    6],          r,        0x0 */
            uint32_t reg_gpio_7_i                   :  1; /* [    7],          r,        0x0 */
            uint32_t reg_gpio_8_i                   :  1; /* [    8],          r,        0x0 */
            uint32_t reg_gpio_9_i                   :  1; /* [    9],          r,        0x0 */
            uint32_t reg_gpio_10_i                  :  1; /* [   10],          r,        0x0 */
            uint32_t reg_gpio_11_i                  :  1; /* [   11],          r,        0x0 */
            uint32_t reg_gpio_12_i                  :  1; /* [   12],          r,        0x0 */
            uint32_t reg_gpio_13_i                  :  1; /* [   13],          r,        0x0 */
            uint32_t reg_gpio_14_i                  :  1; /* [   14],          r,        0x0 */
            uint32_t reg_gpio_15_i                  :  1; /* [   15],          r,        0x0 */
            uint32_t reg_gpio_16_i                  :  1; /* [   16],          r,        0x0 */
            uint32_t reg_gpio_17_i                  :  1; /* [   17],          r,        0x0 */
            uint32_t reg_gpio_18_i                  :  1; /* [   18],          r,        0x0 */
            uint32_t reg_gpio_19_i                  :  1; /* [   19],          r,        0x0 */
            uint32_t reg_gpio_20_i                  :  1; /* [   20],          r,        0x0 */
            uint32_t reg_gpio_21_i                  :  1; /* [   21],          r,        0x0 */
            uint32_t reg_gpio_22_i                  :  1; /* [   22],          r,        0x0 */
            uint32_t reg_gpio_23_i                  :  1; /* [   23],          r,        0x0 */
            uint32_t reg_gpio_24_i                  :  1; /* [   24],          r,        0x0 */
            uint32_t reg_gpio_25_i                  :  1; /* [   25],          r,        0x0 */
            uint32_t reg_gpio_26_i                  :  1; /* [   26],          r,        0x0 */
            uint32_t reg_gpio_27_i                  :  1; /* [   27],          r,        0x0 */
            uint32_t reg_gpio_28_i                  :  1; /* [   28],          r,        0x0 */
            uint32_t reg_gpio_29_i                  :  1; /* [   29],          r,        0x0 */
            uint32_t reg_gpio_30_i                  :  1; /* [   30],          r,        0x0 */
            uint32_t reg_gpio_31_i                  :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL40;

    /* 0x2A4 : GPIO_CFGCTL41 */
    union {
        struct {
            uint32_t reg_gpio_32_i                  :  1; /* [    0],          r,        0x0 */
            uint32_t reg_gpio_33_i                  :  1; /* [    1],          r,        0x0 */
            uint32_t reg_gpio_34_i                  :  1; /* [    2],          r,        0x0 */
            uint32_t reg_gpio_35_i                  :  1; /* [    3],          r,        0x0 */
            uint32_t reg_gpio_36_i                  :  1; /* [    4],          r,        0x0 */
            uint32_t reg_gpio_37_i                  :  1; /* [    5],          r,        0x0 */
            uint32_t reg_gpio_38_i                  :  1; /* [    6],          r,        0x0 */
            uint32_t reg_gpio_39_i                  :  1; /* [    7],          r,        0x0 */
            uint32_t reg_gpio_40_i                  :  1; /* [    8],          r,        0x0 */
            uint32_t reg_gpio_41_i                  :  1; /* [    9],          r,        0x0 */
            uint32_t reg_gpio_42_i                  :  1; /* [   10],          r,        0x0 */
            uint32_t reg_gpio_43_i                  :  1; /* [   11],          r,        0x0 */
            uint32_t reg_gpio_44_i                  :  1; /* [   12],          r,        0x0 */
            uint32_t reg_gpio_45_i                  :  1; /* [   13],          r,        0x0 */
            uint32_t reg_gpio_46_i                  :  1; /* [   14],          r,        0x0 */
            uint32_t reg_gpio_47_i                  :  1; /* [   15],          r,        0x0 */
            uint32_t reg_gpio_48_i                  :  1; /* [   16],          r,        0x0 */
            uint32_t reg_gpio_49_i                  :  1; /* [   17],          r,        0x0 */
            uint32_t reg_gpio_50_i                  :  1; /* [   18],          r,        0x0 */
            uint32_t reg_gpio_51_i                  :  1; /* [   19],          r,        0x0 */
            uint32_t reg_gpio_52_i                  :  1; /* [   20],          r,        0x0 */
            uint32_t reg_gpio_53_i                  :  1; /* [   21],          r,        0x0 */
            uint32_t reg_gpio_54_i                  :  1; /* [   22],          r,        0x0 */
            uint32_t reg_gpio_55_i                  :  1; /* [   23],          r,        0x0 */
            uint32_t reg_gpio_56_i                  :  1; /* [   24],          r,        0x0 */
            uint32_t reg_gpio_57_i                  :  1; /* [   25],          r,        0x0 */
            uint32_t reg_gpio_58_i                  :  1; /* [   26],          r,        0x0 */
            uint32_t reg_gpio_59_i                  :  1; /* [   27],          r,        0x0 */
            uint32_t reg_gpio_60_i                  :  1; /* [   28],          r,        0x0 */
            uint32_t reg_gpio_61_i                  :  1; /* [   29],          r,        0x0 */
            uint32_t reg_gpio_62_i                  :  1; /* [   30],          r,        0x0 */
            uint32_t reg_gpio_63_i                  :  1; /* [   31],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL41;

    /* 0x2A8 : GPIO_CFGCTL42 */
    union {
        struct {
            uint32_t reg_gpio_64_i                  :  1; /* [    0],          r,        0x0 */
            uint32_t reg_gpio_65_i                  :  1; /* [    1],          r,        0x0 */
            uint32_t reg_gpio_66_i                  :  1; /* [    2],          r,        0x0 */
            uint32_t reg_gpio_67_i                  :  1; /* [    3],          r,        0x0 */
            uint32_t reg_gpio_68_i                  :  1; /* [    4],          r,        0x0 */
            uint32_t reg_gpio_69_i                  :  1; /* [    5],          r,        0x0 */
            uint32_t reg_gpio_70_i                  :  1; /* [    6],          r,        0x0 */
            uint32_t reg_gpio_71_i                  :  1; /* [    7],          r,        0x0 */
            uint32_t reg_gpio_72_i                  :  1; /* [    8],          r,        0x0 */
            uint32_t reg_gpio_73_i                  :  1; /* [    9],          r,        0x0 */
            uint32_t reg_gpio_74_i                  :  1; /* [   10],          r,        0x0 */
            uint32_t reg_gpio_75_i                  :  1; /* [   11],          r,        0x0 */
            uint32_t reg_gpio_76_i                  :  1; /* [   12],          r,        0x0 */
            uint32_t reg_gpio_77_i                  :  1; /* [   13],          r,        0x0 */
            uint32_t reg_gpio_78_i                  :  1; /* [   14],          r,        0x0 */
            uint32_t reg_gpio_79_i                  :  1; /* [   15],          r,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL42;

    /* 0x2ac  reserved */
    uint8_t RESERVED0x2ac[4];

    /* 0x2B0 : GPIO_CFGCTL43 */
    union {
        struct {
            uint32_t reg_gpio_0_o                   :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_1_o                   :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_2_o                   :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_3_o                   :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_4_o                   :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_5_o                   :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_6_o                   :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_7_o                   :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_8_o                   :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_9_o                   :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_10_o                  :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_11_o                  :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_12_o                  :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_13_o                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_14_o                  :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_15_o                  :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_gpio_16_o                  :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_gpio_17_o                  :  1; /* [   17],        r/w,        0x0 */
            uint32_t reg_gpio_18_o                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t reg_gpio_19_o                  :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_gpio_20_o                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_21_o                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_gpio_22_o                  :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_gpio_23_o                  :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_gpio_24_o                  :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_gpio_25_o                  :  1; /* [   25],        r/w,        0x0 */
            uint32_t reg_gpio_26_o                  :  1; /* [   26],        r/w,        0x0 */
            uint32_t reg_gpio_27_o                  :  1; /* [   27],        r/w,        0x0 */
            uint32_t reg_gpio_28_o                  :  1; /* [   28],        r/w,        0x0 */
            uint32_t reg_gpio_29_o                  :  1; /* [   29],        r/w,        0x0 */
            uint32_t reg_gpio_30_o                  :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_gpio_31_o                  :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL43;

    /* 0x2B4 : GPIO_CFGCTL44 */
    union {
        struct {
            uint32_t reg_gpio_32_o                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_33_o                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_34_o                  :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_35_o                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_36_o                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_37_o                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_38_o                  :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_39_o                  :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_40_o                  :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_41_o                  :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_42_o                  :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_43_o                  :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_44_o                  :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_45_o                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_46_o                  :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_47_o                  :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_gpio_48_o                  :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_gpio_49_o                  :  1; /* [   17],        r/w,        0x0 */
            uint32_t reg_gpio_50_o                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t reg_gpio_51_o                  :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_gpio_52_o                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_53_o                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_gpio_54_o                  :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_gpio_55_o                  :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_gpio_56_o                  :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_gpio_57_o                  :  1; /* [   25],        r/w,        0x0 */
            uint32_t reg_gpio_58_o                  :  1; /* [   26],        r/w,        0x0 */
            uint32_t reg_gpio_59_o                  :  1; /* [   27],        r/w,        0x0 */
            uint32_t reg_gpio_60_o                  :  1; /* [   28],        r/w,        0x0 */
            uint32_t reg_gpio_61_o                  :  1; /* [   29],        r/w,        0x0 */
            uint32_t reg_gpio_62_o                  :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_gpio_63_o                  :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL44;

    /* 0x2B8 : GPIO_CFGCTL45 */
    union {
        struct {
            uint32_t reg_gpio_64_o                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_65_o                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_66_o                  :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_67_o                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_68_o                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_69_o                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_70_o                  :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_71_o                  :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_72_o                  :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_73_o                  :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_74_o                  :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_75_o                  :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_76_o                  :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_77_o                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_78_o                  :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_79_o                  :  1; /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL45;

    /* 0x2bc  reserved */
    uint8_t RESERVED0x2bc[4];

    /* 0x2C0 : GPIO_CFGCTL46 */
    union {
        struct {
            uint32_t reg_gpio_0_oe                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_1_oe                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_2_oe                  :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_3_oe                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_4_oe                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_5_oe                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_6_oe                  :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_7_oe                  :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_8_oe                  :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_9_oe                  :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_10_oe                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_11_oe                 :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_12_oe                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_13_oe                 :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_14_oe                 :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_15_oe                 :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_gpio_16_oe                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_gpio_17_oe                 :  1; /* [   17],        r/w,        0x0 */
            uint32_t reg_gpio_18_oe                 :  1; /* [   18],        r/w,        0x0 */
            uint32_t reg_gpio_19_oe                 :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_gpio_20_oe                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_21_oe                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_gpio_22_oe                 :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_gpio_23_oe                 :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_gpio_24_oe                 :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_gpio_25_oe                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t reg_gpio_26_oe                 :  1; /* [   26],        r/w,        0x0 */
            uint32_t reg_gpio_27_oe                 :  1; /* [   27],        r/w,        0x0 */
            uint32_t reg_gpio_28_oe                 :  1; /* [   28],        r/w,        0x0 */
            uint32_t reg_gpio_29_oe                 :  1; /* [   29],        r/w,        0x0 */
            uint32_t reg_gpio_30_oe                 :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_gpio_31_oe                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL46;

    /* 0x2C4 : GPIO_CFGCTL47 */
    union {
        struct {
            uint32_t reg_gpio_32_oe                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_33_oe                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_34_oe                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_35_oe                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_36_oe                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_37_oe                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_38_oe                 :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_39_oe                 :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_40_oe                 :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_41_oe                 :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_42_oe                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_43_oe                 :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_44_oe                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_45_oe                 :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_46_oe                 :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_47_oe                 :  1; /* [   15],        r/w,        0x0 */
            uint32_t reg_gpio_48_oe                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t reg_gpio_49_oe                 :  1; /* [   17],        r/w,        0x0 */
            uint32_t reg_gpio_50_oe                 :  1; /* [   18],        r/w,        0x0 */
            uint32_t reg_gpio_51_oe                 :  1; /* [   19],        r/w,        0x0 */
            uint32_t reg_gpio_52_oe                 :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_53_oe                 :  1; /* [   21],        r/w,        0x0 */
            uint32_t reg_gpio_54_oe                 :  1; /* [   22],        r/w,        0x0 */
            uint32_t reg_gpio_55_oe                 :  1; /* [   23],        r/w,        0x0 */
            uint32_t reg_gpio_56_oe                 :  1; /* [   24],        r/w,        0x0 */
            uint32_t reg_gpio_57_oe                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t reg_gpio_58_oe                 :  1; /* [   26],        r/w,        0x0 */
            uint32_t reg_gpio_59_oe                 :  1; /* [   27],        r/w,        0x0 */
            uint32_t reg_gpio_60_oe                 :  1; /* [   28],        r/w,        0x0 */
            uint32_t reg_gpio_61_oe                 :  1; /* [   29],        r/w,        0x0 */
            uint32_t reg_gpio_62_oe                 :  1; /* [   30],        r/w,        0x0 */
            uint32_t reg_gpio_63_oe                 :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL47;

    /* 0x2C8 : GPIO_CFGCTL48 */
    union {
        struct {
            uint32_t reg_gpio_64_oe                 :  1; /* [    0],        r/w,        0x0 */
            uint32_t reg_gpio_65_oe                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t reg_gpio_66_oe                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t reg_gpio_67_oe                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t reg_gpio_68_oe                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_69_oe                 :  1; /* [    5],        r/w,        0x0 */
            uint32_t reg_gpio_70_oe                 :  1; /* [    6],        r/w,        0x0 */
            uint32_t reg_gpio_71_oe                 :  1; /* [    7],        r/w,        0x0 */
            uint32_t reg_gpio_72_oe                 :  1; /* [    8],        r/w,        0x0 */
            uint32_t reg_gpio_73_oe                 :  1; /* [    9],        r/w,        0x0 */
            uint32_t reg_gpio_74_oe                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t reg_gpio_75_oe                 :  1; /* [   11],        r/w,        0x0 */
            uint32_t reg_gpio_76_oe                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reg_gpio_77_oe                 :  1; /* [   13],        r/w,        0x0 */
            uint32_t reg_gpio_78_oe                 :  1; /* [   14],        r/w,        0x0 */
            uint32_t reg_gpio_79_oe                 :  1; /* [   15],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL48;

};

typedef volatile struct mmsys_misc_reg mmsys_misc_reg_t;


/* 0x0 : GPIO_CFGCTL */
#define MMSYS_MISC_GPIO_CFGCTL_OFFSET                           (0x0)
#define MMSYS_MISC_REG_GPIO_0_IE                                MMSYS_MISC_REG_GPIO_0_IE
#define MMSYS_MISC_REG_GPIO_0_IE_POS                            (0U)
#define MMSYS_MISC_REG_GPIO_0_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_IE_POS)
#define MMSYS_MISC_REG_GPIO_0_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_IE_POS))
#define MMSYS_MISC_REG_GPIO_0_SMT                               MMSYS_MISC_REG_GPIO_0_SMT
#define MMSYS_MISC_REG_GPIO_0_SMT_POS                           (1U)
#define MMSYS_MISC_REG_GPIO_0_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_0_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_0_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_SMT_POS)
#define MMSYS_MISC_REG_GPIO_0_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_0_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_SMT_POS))
#define MMSYS_MISC_REG_GPIO_0_DRV                               MMSYS_MISC_REG_GPIO_0_DRV
#define MMSYS_MISC_REG_GPIO_0_DRV_POS                           (2U)
#define MMSYS_MISC_REG_GPIO_0_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_0_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_0_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_DRV_POS)
#define MMSYS_MISC_REG_GPIO_0_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_0_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_DRV_POS))
#define MMSYS_MISC_REG_GPIO_0_PU                                MMSYS_MISC_REG_GPIO_0_PU
#define MMSYS_MISC_REG_GPIO_0_PU_POS                            (4U)
#define MMSYS_MISC_REG_GPIO_0_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PU_POS)
#define MMSYS_MISC_REG_GPIO_0_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PU_POS))
#define MMSYS_MISC_REG_GPIO_0_PD                                MMSYS_MISC_REG_GPIO_0_PD
#define MMSYS_MISC_REG_GPIO_0_PD_POS                            (5U)
#define MMSYS_MISC_REG_GPIO_0_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_0_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_0_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PD_POS)
#define MMSYS_MISC_REG_GPIO_0_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_0_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_PD_POS))
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL                          MMSYS_MISC_REG_GPIO_0_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS                      (8U)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_0_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_0_FUNC_SEL_POS))
#define MMSYS_MISC_REG_GPIO_1_IE                                MMSYS_MISC_REG_GPIO_1_IE
#define MMSYS_MISC_REG_GPIO_1_IE_POS                            (16U)
#define MMSYS_MISC_REG_GPIO_1_IE_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_IE_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_IE_POS)
#define MMSYS_MISC_REG_GPIO_1_IE_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_IE_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_IE_POS))
#define MMSYS_MISC_REG_GPIO_1_SMT                               MMSYS_MISC_REG_GPIO_1_SMT
#define MMSYS_MISC_REG_GPIO_1_SMT_POS                           (17U)
#define MMSYS_MISC_REG_GPIO_1_SMT_LEN                           (1U)
#define MMSYS_MISC_REG_GPIO_1_SMT_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_1_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_SMT_POS)
#define MMSYS_MISC_REG_GPIO_1_SMT_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_1_SMT_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_SMT_POS))
#define MMSYS_MISC_REG_GPIO_1_DRV                               MMSYS_MISC_REG_GPIO_1_DRV
#define MMSYS_MISC_REG_GPIO_1_DRV_POS                           (18U)
#define MMSYS_MISC_REG_GPIO_1_DRV_LEN                           (2U)
#define MMSYS_MISC_REG_GPIO_1_DRV_MSK                           (((1U<<MMSYS_MISC_REG_GPIO_1_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_DRV_POS)
#define MMSYS_MISC_REG_GPIO_1_DRV_UMSK                          (~(((1U<<MMSYS_MISC_REG_GPIO_1_DRV_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_DRV_POS))
#define MMSYS_MISC_REG_GPIO_1_PU                                MMSYS_MISC_REG_GPIO_1_PU
#define MMSYS_MISC_REG_GPIO_1_PU_POS                            (20U)
#define MMSYS_MISC_REG_GPIO_1_PU_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_PU_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PU_POS)
#define MMSYS_MISC_REG_GPIO_1_PU_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_PU_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PU_POS))
#define MMSYS_MISC_REG_GPIO_1_PD                                MMSYS_MISC_REG_GPIO_1_PD
#define MMSYS_MISC_REG_GPIO_1_PD_POS                            (21U)
#define MMSYS_MISC_REG_GPIO_1_PD_LEN                            (1U)
#define MMSYS_MISC_REG_GPIO_1_PD_MSK                            (((1U<<MMSYS_MISC_REG_GPIO_1_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PD_POS)
#define MMSYS_MISC_REG_GPIO_1_PD_UMSK                           (~(((1U<<MMSYS_MISC_REG_GPIO_1_PD_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_PD_POS))
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL                          MMSYS_MISC_REG_GPIO_1_FUNC_SEL
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS                      (24U)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN                      (4U)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_MSK                      (((1U<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS)
#define MMSYS_MISC_REG_GPIO_1_FUNC_SEL_UMSK                     (~(((1U<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_LEN)-1)<<MMSYS_MISC_REG_GPIO_1_FUNC_SEL_POS))


struct  mmsys_misc_gpio_reg {
    /* 0x0 : GPIO_CFGCTL */
    union {
        struct {
            uint32_t reg_gpio_0_ie                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t reg_gpio_0_smt                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t reg_gpio_0_drv                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t reg_gpio_0_pu                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t reg_gpio_0_pd                  :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_gpio_0_func_sel            :  4; /* [11: 8],        r/w,        0xf */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t reg_gpio_1_ie                  :  1; /* [   16],        r/w,        0x1 */
            uint32_t reg_gpio_1_smt                 :  1; /* [   17],        r/w,        0x1 */
            uint32_t reg_gpio_1_drv                 :  2; /* [19:18],        r/w,        0x0 */
            uint32_t reg_gpio_1_pu                  :  1; /* [   20],        r/w,        0x0 */
            uint32_t reg_gpio_1_pd                  :  1; /* [   21],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t reg_gpio_1_func_sel            :  4; /* [27:24],        r/w,        0xf */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } GPIO_CFGCTL;

};

typedef volatile struct mmsys_misc_gpio_reg mmsys_misc_gpio_reg_t;

#define MMSYS_MISC_GPIO_OFFSET              0x200
#define MMSYS_MISC_GPIO_INPUT_OFFSET        0x2A0
#define MMSYS_MISC_GPIO_OUTPUT_OFFSET       0x2B0
#define MMSYS_MISC_GPIO_OUTPUT_EN_OFFSET    0x2C0


#endif  /* __MMSYS_MISC_REG_H__ */
