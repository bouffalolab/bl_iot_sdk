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
 
#ifndef __PWM_REG_H__
#define __PWM_REG_H__
#include "bl808.h"

/* 0x0 : pwm_int_config */
#define PWM_INT_CONFIG_OFFSET                    (0x0)
#define PWM0_INT_STS                             PWM0_INT_STS
#define PWM0_INT_STS_POS                         (0U)
#define PWM0_INT_STS_LEN                         (1U)
#define PWM0_INT_STS_MSK                         (((1U<<PWM0_INT_STS_LEN)-1)<<PWM0_INT_STS_POS)
#define PWM0_INT_STS_UMSK                        (~(((1U<<PWM0_INT_STS_LEN)-1)<<PWM0_INT_STS_POS))
#define PWM1_INT_STS                             PWM1_INT_STS
#define PWM1_INT_STS_POS                         (1U)
#define PWM1_INT_STS_LEN                         (1U)
#define PWM1_INT_STS_MSK                         (((1U<<PWM1_INT_STS_LEN)-1)<<PWM1_INT_STS_POS)
#define PWM1_INT_STS_UMSK                        (~(((1U<<PWM1_INT_STS_LEN)-1)<<PWM1_INT_STS_POS))
#define PWM0_INT_CLR                             PWM0_INT_CLR
#define PWM0_INT_CLR_POS                         (8U)
#define PWM0_INT_CLR_LEN                         (1U)
#define PWM0_INT_CLR_MSK                         (((1U<<PWM0_INT_CLR_LEN)-1)<<PWM0_INT_CLR_POS)
#define PWM0_INT_CLR_UMSK                        (~(((1U<<PWM0_INT_CLR_LEN)-1)<<PWM0_INT_CLR_POS))
#define PWM1_INT_CLR                             PWM1_INT_CLR
#define PWM1_INT_CLR_POS                         (9U)
#define PWM1_INT_CLR_LEN                         (1U)
#define PWM1_INT_CLR_MSK                         (((1U<<PWM1_INT_CLR_LEN)-1)<<PWM1_INT_CLR_POS)
#define PWM1_INT_CLR_UMSK                        (~(((1U<<PWM1_INT_CLR_LEN)-1)<<PWM1_INT_CLR_POS))

/* 0x40 : pwm_mc0_config0 */
#define PWM_MC0_CONFIG0_OFFSET                   (0x40)
#define PWM_MC0_CLK_DIV                          PWM_MC0_CLK_DIV
#define PWM_MC0_CLK_DIV_POS                      (0U)
#define PWM_MC0_CLK_DIV_LEN                      (16U)
#define PWM_MC0_CLK_DIV_MSK                      (((1U<<PWM_MC0_CLK_DIV_LEN)-1)<<PWM_MC0_CLK_DIV_POS)
#define PWM_MC0_CLK_DIV_UMSK                     (~(((1U<<PWM_MC0_CLK_DIV_LEN)-1)<<PWM_MC0_CLK_DIV_POS))
#define PWM_MC0_STOP_ON_REPT                     PWM_MC0_STOP_ON_REPT
#define PWM_MC0_STOP_ON_REPT_POS                 (19U)
#define PWM_MC0_STOP_ON_REPT_LEN                 (1U)
#define PWM_MC0_STOP_ON_REPT_MSK                 (((1U<<PWM_MC0_STOP_ON_REPT_LEN)-1)<<PWM_MC0_STOP_ON_REPT_POS)
#define PWM_MC0_STOP_ON_REPT_UMSK                (~(((1U<<PWM_MC0_STOP_ON_REPT_LEN)-1)<<PWM_MC0_STOP_ON_REPT_POS))
#define PWM_MC0_ADC_TRG_SRC                      PWM_MC0_ADC_TRG_SRC
#define PWM_MC0_ADC_TRG_SRC_POS                  (20U)
#define PWM_MC0_ADC_TRG_SRC_LEN                  (4U)
#define PWM_MC0_ADC_TRG_SRC_MSK                  (((1U<<PWM_MC0_ADC_TRG_SRC_LEN)-1)<<PWM_MC0_ADC_TRG_SRC_POS)
#define PWM_MC0_ADC_TRG_SRC_UMSK                 (~(((1U<<PWM_MC0_ADC_TRG_SRC_LEN)-1)<<PWM_MC0_ADC_TRG_SRC_POS))
#define PWM_MC0_SW_BREAK_EN                      PWM_MC0_SW_BREAK_EN
#define PWM_MC0_SW_BREAK_EN_POS                  (24U)
#define PWM_MC0_SW_BREAK_EN_LEN                  (1U)
#define PWM_MC0_SW_BREAK_EN_MSK                  (((1U<<PWM_MC0_SW_BREAK_EN_LEN)-1)<<PWM_MC0_SW_BREAK_EN_POS)
#define PWM_MC0_SW_BREAK_EN_UMSK                 (~(((1U<<PWM_MC0_SW_BREAK_EN_LEN)-1)<<PWM_MC0_SW_BREAK_EN_POS))
#define PWM_MC0_EXT_BREAK_EN                     PWM_MC0_EXT_BREAK_EN
#define PWM_MC0_EXT_BREAK_EN_POS                 (25U)
#define PWM_MC0_EXT_BREAK_EN_LEN                 (1U)
#define PWM_MC0_EXT_BREAK_EN_MSK                 (((1U<<PWM_MC0_EXT_BREAK_EN_LEN)-1)<<PWM_MC0_EXT_BREAK_EN_POS)
#define PWM_MC0_EXT_BREAK_EN_UMSK                (~(((1U<<PWM_MC0_EXT_BREAK_EN_LEN)-1)<<PWM_MC0_EXT_BREAK_EN_POS))
#define PWM_MC0_EXT_BREAK_PL                     PWM_MC0_EXT_BREAK_PL
#define PWM_MC0_EXT_BREAK_PL_POS                 (26U)
#define PWM_MC0_EXT_BREAK_PL_LEN                 (1U)
#define PWM_MC0_EXT_BREAK_PL_MSK                 (((1U<<PWM_MC0_EXT_BREAK_PL_LEN)-1)<<PWM_MC0_EXT_BREAK_PL_POS)
#define PWM_MC0_EXT_BREAK_PL_UMSK                (~(((1U<<PWM_MC0_EXT_BREAK_PL_LEN)-1)<<PWM_MC0_EXT_BREAK_PL_POS))
#define PWM_MC0_STOP_EN                          PWM_MC0_STOP_EN
#define PWM_MC0_STOP_EN_POS                      (27U)
#define PWM_MC0_STOP_EN_LEN                      (1U)
#define PWM_MC0_STOP_EN_MSK                      (((1U<<PWM_MC0_STOP_EN_LEN)-1)<<PWM_MC0_STOP_EN_POS)
#define PWM_MC0_STOP_EN_UMSK                     (~(((1U<<PWM_MC0_STOP_EN_LEN)-1)<<PWM_MC0_STOP_EN_POS))
#define PWM_MC0_STOP_MODE                        PWM_MC0_STOP_MODE
#define PWM_MC0_STOP_MODE_POS                    (28U)
#define PWM_MC0_STOP_MODE_LEN                    (1U)
#define PWM_MC0_STOP_MODE_MSK                    (((1U<<PWM_MC0_STOP_MODE_LEN)-1)<<PWM_MC0_STOP_MODE_POS)
#define PWM_MC0_STOP_MODE_UMSK                   (~(((1U<<PWM_MC0_STOP_MODE_LEN)-1)<<PWM_MC0_STOP_MODE_POS))
#define PWM_MC0_STS_STOP                         PWM_MC0_STS_STOP
#define PWM_MC0_STS_STOP_POS                     (29U)
#define PWM_MC0_STS_STOP_LEN                     (1U)
#define PWM_MC0_STS_STOP_MSK                     (((1U<<PWM_MC0_STS_STOP_LEN)-1)<<PWM_MC0_STS_STOP_POS)
#define PWM_MC0_STS_STOP_UMSK                    (~(((1U<<PWM_MC0_STS_STOP_LEN)-1)<<PWM_MC0_STS_STOP_POS))
#define PWM_MC0_REG_CLK_SEL                      PWM_MC0_REG_CLK_SEL
#define PWM_MC0_REG_CLK_SEL_POS                  (30U)
#define PWM_MC0_REG_CLK_SEL_LEN                  (2U)
#define PWM_MC0_REG_CLK_SEL_MSK                  (((1U<<PWM_MC0_REG_CLK_SEL_LEN)-1)<<PWM_MC0_REG_CLK_SEL_POS)
#define PWM_MC0_REG_CLK_SEL_UMSK                 (~(((1U<<PWM_MC0_REG_CLK_SEL_LEN)-1)<<PWM_MC0_REG_CLK_SEL_POS))

/* 0x44 : pwm_mc0_config1 */
#define PWM_MC0_CONFIG1_OFFSET                   (0x44)
#define PWM_MC0_CH0_PEN                          PWM_MC0_CH0_PEN
#define PWM_MC0_CH0_PEN_POS                      (0U)
#define PWM_MC0_CH0_PEN_LEN                      (1U)
#define PWM_MC0_CH0_PEN_MSK                      (((1U<<PWM_MC0_CH0_PEN_LEN)-1)<<PWM_MC0_CH0_PEN_POS)
#define PWM_MC0_CH0_PEN_UMSK                     (~(((1U<<PWM_MC0_CH0_PEN_LEN)-1)<<PWM_MC0_CH0_PEN_POS))
#define PWM_MC0_CH0_PSI                          PWM_MC0_CH0_PSI
#define PWM_MC0_CH0_PSI_POS                      (1U)
#define PWM_MC0_CH0_PSI_LEN                      (1U)
#define PWM_MC0_CH0_PSI_MSK                      (((1U<<PWM_MC0_CH0_PSI_LEN)-1)<<PWM_MC0_CH0_PSI_POS)
#define PWM_MC0_CH0_PSI_UMSK                     (~(((1U<<PWM_MC0_CH0_PSI_LEN)-1)<<PWM_MC0_CH0_PSI_POS))
#define PWM_MC0_CH0_NEN                          PWM_MC0_CH0_NEN
#define PWM_MC0_CH0_NEN_POS                      (2U)
#define PWM_MC0_CH0_NEN_LEN                      (1U)
#define PWM_MC0_CH0_NEN_MSK                      (((1U<<PWM_MC0_CH0_NEN_LEN)-1)<<PWM_MC0_CH0_NEN_POS)
#define PWM_MC0_CH0_NEN_UMSK                     (~(((1U<<PWM_MC0_CH0_NEN_LEN)-1)<<PWM_MC0_CH0_NEN_POS))
#define PWM_MC0_CH0_NSI                          PWM_MC0_CH0_NSI
#define PWM_MC0_CH0_NSI_POS                      (3U)
#define PWM_MC0_CH0_NSI_LEN                      (1U)
#define PWM_MC0_CH0_NSI_MSK                      (((1U<<PWM_MC0_CH0_NSI_LEN)-1)<<PWM_MC0_CH0_NSI_POS)
#define PWM_MC0_CH0_NSI_UMSK                     (~(((1U<<PWM_MC0_CH0_NSI_LEN)-1)<<PWM_MC0_CH0_NSI_POS))
#define PWM_MC0_CH1_PEN                          PWM_MC0_CH1_PEN
#define PWM_MC0_CH1_PEN_POS                      (4U)
#define PWM_MC0_CH1_PEN_LEN                      (1U)
#define PWM_MC0_CH1_PEN_MSK                      (((1U<<PWM_MC0_CH1_PEN_LEN)-1)<<PWM_MC0_CH1_PEN_POS)
#define PWM_MC0_CH1_PEN_UMSK                     (~(((1U<<PWM_MC0_CH1_PEN_LEN)-1)<<PWM_MC0_CH1_PEN_POS))
#define PWM_MC0_CH1_PSI                          PWM_MC0_CH1_PSI
#define PWM_MC0_CH1_PSI_POS                      (5U)
#define PWM_MC0_CH1_PSI_LEN                      (1U)
#define PWM_MC0_CH1_PSI_MSK                      (((1U<<PWM_MC0_CH1_PSI_LEN)-1)<<PWM_MC0_CH1_PSI_POS)
#define PWM_MC0_CH1_PSI_UMSK                     (~(((1U<<PWM_MC0_CH1_PSI_LEN)-1)<<PWM_MC0_CH1_PSI_POS))
#define PWM_MC0_CH1_NEN                          PWM_MC0_CH1_NEN
#define PWM_MC0_CH1_NEN_POS                      (6U)
#define PWM_MC0_CH1_NEN_LEN                      (1U)
#define PWM_MC0_CH1_NEN_MSK                      (((1U<<PWM_MC0_CH1_NEN_LEN)-1)<<PWM_MC0_CH1_NEN_POS)
#define PWM_MC0_CH1_NEN_UMSK                     (~(((1U<<PWM_MC0_CH1_NEN_LEN)-1)<<PWM_MC0_CH1_NEN_POS))
#define PWM_MC0_CH1_NSI                          PWM_MC0_CH1_NSI
#define PWM_MC0_CH1_NSI_POS                      (7U)
#define PWM_MC0_CH1_NSI_LEN                      (1U)
#define PWM_MC0_CH1_NSI_MSK                      (((1U<<PWM_MC0_CH1_NSI_LEN)-1)<<PWM_MC0_CH1_NSI_POS)
#define PWM_MC0_CH1_NSI_UMSK                     (~(((1U<<PWM_MC0_CH1_NSI_LEN)-1)<<PWM_MC0_CH1_NSI_POS))
#define PWM_MC0_CH2_PEN                          PWM_MC0_CH2_PEN
#define PWM_MC0_CH2_PEN_POS                      (8U)
#define PWM_MC0_CH2_PEN_LEN                      (1U)
#define PWM_MC0_CH2_PEN_MSK                      (((1U<<PWM_MC0_CH2_PEN_LEN)-1)<<PWM_MC0_CH2_PEN_POS)
#define PWM_MC0_CH2_PEN_UMSK                     (~(((1U<<PWM_MC0_CH2_PEN_LEN)-1)<<PWM_MC0_CH2_PEN_POS))
#define PWM_MC0_CH2_PSI                          PWM_MC0_CH2_PSI
#define PWM_MC0_CH2_PSI_POS                      (9U)
#define PWM_MC0_CH2_PSI_LEN                      (1U)
#define PWM_MC0_CH2_PSI_MSK                      (((1U<<PWM_MC0_CH2_PSI_LEN)-1)<<PWM_MC0_CH2_PSI_POS)
#define PWM_MC0_CH2_PSI_UMSK                     (~(((1U<<PWM_MC0_CH2_PSI_LEN)-1)<<PWM_MC0_CH2_PSI_POS))
#define PWM_MC0_CH2_NEN                          PWM_MC0_CH2_NEN
#define PWM_MC0_CH2_NEN_POS                      (10U)
#define PWM_MC0_CH2_NEN_LEN                      (1U)
#define PWM_MC0_CH2_NEN_MSK                      (((1U<<PWM_MC0_CH2_NEN_LEN)-1)<<PWM_MC0_CH2_NEN_POS)
#define PWM_MC0_CH2_NEN_UMSK                     (~(((1U<<PWM_MC0_CH2_NEN_LEN)-1)<<PWM_MC0_CH2_NEN_POS))
#define PWM_MC0_CH2_NSI                          PWM_MC0_CH2_NSI
#define PWM_MC0_CH2_NSI_POS                      (11U)
#define PWM_MC0_CH2_NSI_LEN                      (1U)
#define PWM_MC0_CH2_NSI_MSK                      (((1U<<PWM_MC0_CH2_NSI_LEN)-1)<<PWM_MC0_CH2_NSI_POS)
#define PWM_MC0_CH2_NSI_UMSK                     (~(((1U<<PWM_MC0_CH2_NSI_LEN)-1)<<PWM_MC0_CH2_NSI_POS))
#define PWM_MC0_CH3_PEN                          PWM_MC0_CH3_PEN
#define PWM_MC0_CH3_PEN_POS                      (12U)
#define PWM_MC0_CH3_PEN_LEN                      (1U)
#define PWM_MC0_CH3_PEN_MSK                      (((1U<<PWM_MC0_CH3_PEN_LEN)-1)<<PWM_MC0_CH3_PEN_POS)
#define PWM_MC0_CH3_PEN_UMSK                     (~(((1U<<PWM_MC0_CH3_PEN_LEN)-1)<<PWM_MC0_CH3_PEN_POS))
#define PWM_MC0_CH3_PSI                          PWM_MC0_CH3_PSI
#define PWM_MC0_CH3_PSI_POS                      (13U)
#define PWM_MC0_CH3_PSI_LEN                      (1U)
#define PWM_MC0_CH3_PSI_MSK                      (((1U<<PWM_MC0_CH3_PSI_LEN)-1)<<PWM_MC0_CH3_PSI_POS)
#define PWM_MC0_CH3_PSI_UMSK                     (~(((1U<<PWM_MC0_CH3_PSI_LEN)-1)<<PWM_MC0_CH3_PSI_POS))
#define PWM_MC0_CH3_NEN                          PWM_MC0_CH3_NEN
#define PWM_MC0_CH3_NEN_POS                      (14U)
#define PWM_MC0_CH3_NEN_LEN                      (1U)
#define PWM_MC0_CH3_NEN_MSK                      (((1U<<PWM_MC0_CH3_NEN_LEN)-1)<<PWM_MC0_CH3_NEN_POS)
#define PWM_MC0_CH3_NEN_UMSK                     (~(((1U<<PWM_MC0_CH3_NEN_LEN)-1)<<PWM_MC0_CH3_NEN_POS))
#define PWM_MC0_CH3_NSI                          PWM_MC0_CH3_NSI
#define PWM_MC0_CH3_NSI_POS                      (15U)
#define PWM_MC0_CH3_NSI_LEN                      (1U)
#define PWM_MC0_CH3_NSI_MSK                      (((1U<<PWM_MC0_CH3_NSI_LEN)-1)<<PWM_MC0_CH3_NSI_POS)
#define PWM_MC0_CH3_NSI_UMSK                     (~(((1U<<PWM_MC0_CH3_NSI_LEN)-1)<<PWM_MC0_CH3_NSI_POS))
#define PWM_MC0_CH0_PPL                          PWM_MC0_CH0_PPL
#define PWM_MC0_CH0_PPL_POS                      (16U)
#define PWM_MC0_CH0_PPL_LEN                      (1U)
#define PWM_MC0_CH0_PPL_MSK                      (((1U<<PWM_MC0_CH0_PPL_LEN)-1)<<PWM_MC0_CH0_PPL_POS)
#define PWM_MC0_CH0_PPL_UMSK                     (~(((1U<<PWM_MC0_CH0_PPL_LEN)-1)<<PWM_MC0_CH0_PPL_POS))
#define PWM_MC0_CH0_NPL                          PWM_MC0_CH0_NPL
#define PWM_MC0_CH0_NPL_POS                      (17U)
#define PWM_MC0_CH0_NPL_LEN                      (1U)
#define PWM_MC0_CH0_NPL_MSK                      (((1U<<PWM_MC0_CH0_NPL_LEN)-1)<<PWM_MC0_CH0_NPL_POS)
#define PWM_MC0_CH0_NPL_UMSK                     (~(((1U<<PWM_MC0_CH0_NPL_LEN)-1)<<PWM_MC0_CH0_NPL_POS))
#define PWM_MC0_CH1_PPL                          PWM_MC0_CH1_PPL
#define PWM_MC0_CH1_PPL_POS                      (18U)
#define PWM_MC0_CH1_PPL_LEN                      (1U)
#define PWM_MC0_CH1_PPL_MSK                      (((1U<<PWM_MC0_CH1_PPL_LEN)-1)<<PWM_MC0_CH1_PPL_POS)
#define PWM_MC0_CH1_PPL_UMSK                     (~(((1U<<PWM_MC0_CH1_PPL_LEN)-1)<<PWM_MC0_CH1_PPL_POS))
#define PWM_MC0_CH1_NPL                          PWM_MC0_CH1_NPL
#define PWM_MC0_CH1_NPL_POS                      (19U)
#define PWM_MC0_CH1_NPL_LEN                      (1U)
#define PWM_MC0_CH1_NPL_MSK                      (((1U<<PWM_MC0_CH1_NPL_LEN)-1)<<PWM_MC0_CH1_NPL_POS)
#define PWM_MC0_CH1_NPL_UMSK                     (~(((1U<<PWM_MC0_CH1_NPL_LEN)-1)<<PWM_MC0_CH1_NPL_POS))
#define PWM_MC0_CH2_PPL                          PWM_MC0_CH2_PPL
#define PWM_MC0_CH2_PPL_POS                      (20U)
#define PWM_MC0_CH2_PPL_LEN                      (1U)
#define PWM_MC0_CH2_PPL_MSK                      (((1U<<PWM_MC0_CH2_PPL_LEN)-1)<<PWM_MC0_CH2_PPL_POS)
#define PWM_MC0_CH2_PPL_UMSK                     (~(((1U<<PWM_MC0_CH2_PPL_LEN)-1)<<PWM_MC0_CH2_PPL_POS))
#define PWM_MC0_CH2_NPL                          PWM_MC0_CH2_NPL
#define PWM_MC0_CH2_NPL_POS                      (21U)
#define PWM_MC0_CH2_NPL_LEN                      (1U)
#define PWM_MC0_CH2_NPL_MSK                      (((1U<<PWM_MC0_CH2_NPL_LEN)-1)<<PWM_MC0_CH2_NPL_POS)
#define PWM_MC0_CH2_NPL_UMSK                     (~(((1U<<PWM_MC0_CH2_NPL_LEN)-1)<<PWM_MC0_CH2_NPL_POS))
#define PWM_MC0_CH3_PPL                          PWM_MC0_CH3_PPL
#define PWM_MC0_CH3_PPL_POS                      (22U)
#define PWM_MC0_CH3_PPL_LEN                      (1U)
#define PWM_MC0_CH3_PPL_MSK                      (((1U<<PWM_MC0_CH3_PPL_LEN)-1)<<PWM_MC0_CH3_PPL_POS)
#define PWM_MC0_CH3_PPL_UMSK                     (~(((1U<<PWM_MC0_CH3_PPL_LEN)-1)<<PWM_MC0_CH3_PPL_POS))
#define PWM_MC0_CH3_NPL                          PWM_MC0_CH3_NPL
#define PWM_MC0_CH3_NPL_POS                      (23U)
#define PWM_MC0_CH3_NPL_LEN                      (1U)
#define PWM_MC0_CH3_NPL_MSK                      (((1U<<PWM_MC0_CH3_NPL_LEN)-1)<<PWM_MC0_CH3_NPL_POS)
#define PWM_MC0_CH3_NPL_UMSK                     (~(((1U<<PWM_MC0_CH3_NPL_LEN)-1)<<PWM_MC0_CH3_NPL_POS))
#define PWM_MC0_CH0_PBS                          PWM_MC0_CH0_PBS
#define PWM_MC0_CH0_PBS_POS                      (24U)
#define PWM_MC0_CH0_PBS_LEN                      (1U)
#define PWM_MC0_CH0_PBS_MSK                      (((1U<<PWM_MC0_CH0_PBS_LEN)-1)<<PWM_MC0_CH0_PBS_POS)
#define PWM_MC0_CH0_PBS_UMSK                     (~(((1U<<PWM_MC0_CH0_PBS_LEN)-1)<<PWM_MC0_CH0_PBS_POS))
#define PWM_MC0_CH0_NBS                          PWM_MC0_CH0_NBS
#define PWM_MC0_CH0_NBS_POS                      (25U)
#define PWM_MC0_CH0_NBS_LEN                      (1U)
#define PWM_MC0_CH0_NBS_MSK                      (((1U<<PWM_MC0_CH0_NBS_LEN)-1)<<PWM_MC0_CH0_NBS_POS)
#define PWM_MC0_CH0_NBS_UMSK                     (~(((1U<<PWM_MC0_CH0_NBS_LEN)-1)<<PWM_MC0_CH0_NBS_POS))
#define PWM_MC0_CH1_PBS                          PWM_MC0_CH1_PBS
#define PWM_MC0_CH1_PBS_POS                      (26U)
#define PWM_MC0_CH1_PBS_LEN                      (1U)
#define PWM_MC0_CH1_PBS_MSK                      (((1U<<PWM_MC0_CH1_PBS_LEN)-1)<<PWM_MC0_CH1_PBS_POS)
#define PWM_MC0_CH1_PBS_UMSK                     (~(((1U<<PWM_MC0_CH1_PBS_LEN)-1)<<PWM_MC0_CH1_PBS_POS))
#define PWM_MC0_CH1_NBS                          PWM_MC0_CH1_NBS
#define PWM_MC0_CH1_NBS_POS                      (27U)
#define PWM_MC0_CH1_NBS_LEN                      (1U)
#define PWM_MC0_CH1_NBS_MSK                      (((1U<<PWM_MC0_CH1_NBS_LEN)-1)<<PWM_MC0_CH1_NBS_POS)
#define PWM_MC0_CH1_NBS_UMSK                     (~(((1U<<PWM_MC0_CH1_NBS_LEN)-1)<<PWM_MC0_CH1_NBS_POS))
#define PWM_MC0_CH2_PBS                          PWM_MC0_CH2_PBS
#define PWM_MC0_CH2_PBS_POS                      (28U)
#define PWM_MC0_CH2_PBS_LEN                      (1U)
#define PWM_MC0_CH2_PBS_MSK                      (((1U<<PWM_MC0_CH2_PBS_LEN)-1)<<PWM_MC0_CH2_PBS_POS)
#define PWM_MC0_CH2_PBS_UMSK                     (~(((1U<<PWM_MC0_CH2_PBS_LEN)-1)<<PWM_MC0_CH2_PBS_POS))
#define PWM_MC0_CH2_NBS                          PWM_MC0_CH2_NBS
#define PWM_MC0_CH2_NBS_POS                      (29U)
#define PWM_MC0_CH2_NBS_LEN                      (1U)
#define PWM_MC0_CH2_NBS_MSK                      (((1U<<PWM_MC0_CH2_NBS_LEN)-1)<<PWM_MC0_CH2_NBS_POS)
#define PWM_MC0_CH2_NBS_UMSK                     (~(((1U<<PWM_MC0_CH2_NBS_LEN)-1)<<PWM_MC0_CH2_NBS_POS))
#define PWM_MC0_CH3_PBS                          PWM_MC0_CH3_PBS
#define PWM_MC0_CH3_PBS_POS                      (30U)
#define PWM_MC0_CH3_PBS_LEN                      (1U)
#define PWM_MC0_CH3_PBS_MSK                      (((1U<<PWM_MC0_CH3_PBS_LEN)-1)<<PWM_MC0_CH3_PBS_POS)
#define PWM_MC0_CH3_PBS_UMSK                     (~(((1U<<PWM_MC0_CH3_PBS_LEN)-1)<<PWM_MC0_CH3_PBS_POS))
#define PWM_MC0_CH3_NBS                          PWM_MC0_CH3_NBS
#define PWM_MC0_CH3_NBS_POS                      (31U)
#define PWM_MC0_CH3_NBS_LEN                      (1U)
#define PWM_MC0_CH3_NBS_MSK                      (((1U<<PWM_MC0_CH3_NBS_LEN)-1)<<PWM_MC0_CH3_NBS_POS)
#define PWM_MC0_CH3_NBS_UMSK                     (~(((1U<<PWM_MC0_CH3_NBS_LEN)-1)<<PWM_MC0_CH3_NBS_POS))

/* 0x48 : pwm_mc0_period */
#define PWM_MC0_PERIOD_OFFSET                    (0x48)
#define PWM_MC0_PERIOD                           PWM_MC0_PERIOD
#define PWM_MC0_PERIOD_POS                       (0U)
#define PWM_MC0_PERIOD_LEN                       (16U)
#define PWM_MC0_PERIOD_MSK                       (((1U<<PWM_MC0_PERIOD_LEN)-1)<<PWM_MC0_PERIOD_POS)
#define PWM_MC0_PERIOD_UMSK                      (~(((1U<<PWM_MC0_PERIOD_LEN)-1)<<PWM_MC0_PERIOD_POS))
#define PWM_MC0_INT_PERIOD_CNT                   PWM_MC0_INT_PERIOD_CNT
#define PWM_MC0_INT_PERIOD_CNT_POS               (16U)
#define PWM_MC0_INT_PERIOD_CNT_LEN               (16U)
#define PWM_MC0_INT_PERIOD_CNT_MSK               (((1U<<PWM_MC0_INT_PERIOD_CNT_LEN)-1)<<PWM_MC0_INT_PERIOD_CNT_POS)
#define PWM_MC0_INT_PERIOD_CNT_UMSK              (~(((1U<<PWM_MC0_INT_PERIOD_CNT_LEN)-1)<<PWM_MC0_INT_PERIOD_CNT_POS))

/* 0x4c : pwm_mc0_dead_time */
#define PWM_MC0_DEAD_TIME_OFFSET                 (0x4c)
#define PWM_MC0_CH0_DTG                          PWM_MC0_CH0_DTG
#define PWM_MC0_CH0_DTG_POS                      (0U)
#define PWM_MC0_CH0_DTG_LEN                      (8U)
#define PWM_MC0_CH0_DTG_MSK                      (((1U<<PWM_MC0_CH0_DTG_LEN)-1)<<PWM_MC0_CH0_DTG_POS)
#define PWM_MC0_CH0_DTG_UMSK                     (~(((1U<<PWM_MC0_CH0_DTG_LEN)-1)<<PWM_MC0_CH0_DTG_POS))
#define PWM_MC0_CH1_DTG                          PWM_MC0_CH1_DTG
#define PWM_MC0_CH1_DTG_POS                      (8U)
#define PWM_MC0_CH1_DTG_LEN                      (8U)
#define PWM_MC0_CH1_DTG_MSK                      (((1U<<PWM_MC0_CH1_DTG_LEN)-1)<<PWM_MC0_CH1_DTG_POS)
#define PWM_MC0_CH1_DTG_UMSK                     (~(((1U<<PWM_MC0_CH1_DTG_LEN)-1)<<PWM_MC0_CH1_DTG_POS))
#define PWM_MC0_CH2_DTG                          PWM_MC0_CH2_DTG
#define PWM_MC0_CH2_DTG_POS                      (16U)
#define PWM_MC0_CH2_DTG_LEN                      (8U)
#define PWM_MC0_CH2_DTG_MSK                      (((1U<<PWM_MC0_CH2_DTG_LEN)-1)<<PWM_MC0_CH2_DTG_POS)
#define PWM_MC0_CH2_DTG_UMSK                     (~(((1U<<PWM_MC0_CH2_DTG_LEN)-1)<<PWM_MC0_CH2_DTG_POS))
#define PWM_MC0_CH3_DTG                          PWM_MC0_CH3_DTG
#define PWM_MC0_CH3_DTG_POS                      (24U)
#define PWM_MC0_CH3_DTG_LEN                      (8U)
#define PWM_MC0_CH3_DTG_MSK                      (((1U<<PWM_MC0_CH3_DTG_LEN)-1)<<PWM_MC0_CH3_DTG_POS)
#define PWM_MC0_CH3_DTG_UMSK                     (~(((1U<<PWM_MC0_CH3_DTG_LEN)-1)<<PWM_MC0_CH3_DTG_POS))

/* 0x50 : pwm_mc0_ch0_thre */
#define PWM_MC0_CH0_THRE_OFFSET                  (0x50)
#define PWM_MC0_CH0_THREL                        PWM_MC0_CH0_THREL
#define PWM_MC0_CH0_THREL_POS                    (0U)
#define PWM_MC0_CH0_THREL_LEN                    (16U)
#define PWM_MC0_CH0_THREL_MSK                    (((1U<<PWM_MC0_CH0_THREL_LEN)-1)<<PWM_MC0_CH0_THREL_POS)
#define PWM_MC0_CH0_THREL_UMSK                   (~(((1U<<PWM_MC0_CH0_THREL_LEN)-1)<<PWM_MC0_CH0_THREL_POS))
#define PWM_MC0_CH0_THREH                        PWM_MC0_CH0_THREH
#define PWM_MC0_CH0_THREH_POS                    (16U)
#define PWM_MC0_CH0_THREH_LEN                    (16U)
#define PWM_MC0_CH0_THREH_MSK                    (((1U<<PWM_MC0_CH0_THREH_LEN)-1)<<PWM_MC0_CH0_THREH_POS)
#define PWM_MC0_CH0_THREH_UMSK                   (~(((1U<<PWM_MC0_CH0_THREH_LEN)-1)<<PWM_MC0_CH0_THREH_POS))

/* 0x54 : pwm_mc0_ch1_thre */
#define PWM_MC0_CH1_THRE_OFFSET                  (0x54)
#define PWM_MC0_CH1_THREL                        PWM_MC0_CH1_THREL
#define PWM_MC0_CH1_THREL_POS                    (0U)
#define PWM_MC0_CH1_THREL_LEN                    (16U)
#define PWM_MC0_CH1_THREL_MSK                    (((1U<<PWM_MC0_CH1_THREL_LEN)-1)<<PWM_MC0_CH1_THREL_POS)
#define PWM_MC0_CH1_THREL_UMSK                   (~(((1U<<PWM_MC0_CH1_THREL_LEN)-1)<<PWM_MC0_CH1_THREL_POS))
#define PWM_MC0_CH1_THREH                        PWM_MC0_CH1_THREH
#define PWM_MC0_CH1_THREH_POS                    (16U)
#define PWM_MC0_CH1_THREH_LEN                    (16U)
#define PWM_MC0_CH1_THREH_MSK                    (((1U<<PWM_MC0_CH1_THREH_LEN)-1)<<PWM_MC0_CH1_THREH_POS)
#define PWM_MC0_CH1_THREH_UMSK                   (~(((1U<<PWM_MC0_CH1_THREH_LEN)-1)<<PWM_MC0_CH1_THREH_POS))

/* 0x58 : pwm_mc0_ch2_thre */
#define PWM_MC0_CH2_THRE_OFFSET                  (0x58)
#define PWM_MC0_CH2_THREL                        PWM_MC0_CH2_THREL
#define PWM_MC0_CH2_THREL_POS                    (0U)
#define PWM_MC0_CH2_THREL_LEN                    (16U)
#define PWM_MC0_CH2_THREL_MSK                    (((1U<<PWM_MC0_CH2_THREL_LEN)-1)<<PWM_MC0_CH2_THREL_POS)
#define PWM_MC0_CH2_THREL_UMSK                   (~(((1U<<PWM_MC0_CH2_THREL_LEN)-1)<<PWM_MC0_CH2_THREL_POS))
#define PWM_MC0_CH2_THREH                        PWM_MC0_CH2_THREH
#define PWM_MC0_CH2_THREH_POS                    (16U)
#define PWM_MC0_CH2_THREH_LEN                    (16U)
#define PWM_MC0_CH2_THREH_MSK                    (((1U<<PWM_MC0_CH2_THREH_LEN)-1)<<PWM_MC0_CH2_THREH_POS)
#define PWM_MC0_CH2_THREH_UMSK                   (~(((1U<<PWM_MC0_CH2_THREH_LEN)-1)<<PWM_MC0_CH2_THREH_POS))

/* 0x5c : pwm_mc0_ch3_thre */
#define PWM_MC0_CH3_THRE_OFFSET                  (0x5c)
#define PWM_MC0_CH3_THREL                        PWM_MC0_CH3_THREL
#define PWM_MC0_CH3_THREL_POS                    (0U)
#define PWM_MC0_CH3_THREL_LEN                    (16U)
#define PWM_MC0_CH3_THREL_MSK                    (((1U<<PWM_MC0_CH3_THREL_LEN)-1)<<PWM_MC0_CH3_THREL_POS)
#define PWM_MC0_CH3_THREL_UMSK                   (~(((1U<<PWM_MC0_CH3_THREL_LEN)-1)<<PWM_MC0_CH3_THREL_POS))
#define PWM_MC0_CH3_THREH                        PWM_MC0_CH3_THREH
#define PWM_MC0_CH3_THREH_POS                    (16U)
#define PWM_MC0_CH3_THREH_LEN                    (16U)
#define PWM_MC0_CH3_THREH_MSK                    (((1U<<PWM_MC0_CH3_THREH_LEN)-1)<<PWM_MC0_CH3_THREH_POS)
#define PWM_MC0_CH3_THREH_UMSK                   (~(((1U<<PWM_MC0_CH3_THREH_LEN)-1)<<PWM_MC0_CH3_THREH_POS))

/* 0x60 : pwm_mc0_int_sts */
#define PWM_MC0_INT_STS_OFFSET                   (0x60)
#define PWM_MC0_CH0_L_INT                        PWM_MC0_CH0_L_INT
#define PWM_MC0_CH0_L_INT_POS                    (0U)
#define PWM_MC0_CH0_L_INT_LEN                    (1U)
#define PWM_MC0_CH0_L_INT_MSK                    (((1U<<PWM_MC0_CH0_L_INT_LEN)-1)<<PWM_MC0_CH0_L_INT_POS)
#define PWM_MC0_CH0_L_INT_UMSK                   (~(((1U<<PWM_MC0_CH0_L_INT_LEN)-1)<<PWM_MC0_CH0_L_INT_POS))
#define PWM_MC0_CH0_H_INT                        PWM_MC0_CH0_H_INT
#define PWM_MC0_CH0_H_INT_POS                    (1U)
#define PWM_MC0_CH0_H_INT_LEN                    (1U)
#define PWM_MC0_CH0_H_INT_MSK                    (((1U<<PWM_MC0_CH0_H_INT_LEN)-1)<<PWM_MC0_CH0_H_INT_POS)
#define PWM_MC0_CH0_H_INT_UMSK                   (~(((1U<<PWM_MC0_CH0_H_INT_LEN)-1)<<PWM_MC0_CH0_H_INT_POS))
#define PWM_MC0_CH1_L_INT                        PWM_MC0_CH1_L_INT
#define PWM_MC0_CH1_L_INT_POS                    (2U)
#define PWM_MC0_CH1_L_INT_LEN                    (1U)
#define PWM_MC0_CH1_L_INT_MSK                    (((1U<<PWM_MC0_CH1_L_INT_LEN)-1)<<PWM_MC0_CH1_L_INT_POS)
#define PWM_MC0_CH1_L_INT_UMSK                   (~(((1U<<PWM_MC0_CH1_L_INT_LEN)-1)<<PWM_MC0_CH1_L_INT_POS))
#define PWM_MC0_CH1_H_INT                        PWM_MC0_CH1_H_INT
#define PWM_MC0_CH1_H_INT_POS                    (3U)
#define PWM_MC0_CH1_H_INT_LEN                    (1U)
#define PWM_MC0_CH1_H_INT_MSK                    (((1U<<PWM_MC0_CH1_H_INT_LEN)-1)<<PWM_MC0_CH1_H_INT_POS)
#define PWM_MC0_CH1_H_INT_UMSK                   (~(((1U<<PWM_MC0_CH1_H_INT_LEN)-1)<<PWM_MC0_CH1_H_INT_POS))
#define PWM_MC0_CH2_L_INT                        PWM_MC0_CH2_L_INT
#define PWM_MC0_CH2_L_INT_POS                    (4U)
#define PWM_MC0_CH2_L_INT_LEN                    (1U)
#define PWM_MC0_CH2_L_INT_MSK                    (((1U<<PWM_MC0_CH2_L_INT_LEN)-1)<<PWM_MC0_CH2_L_INT_POS)
#define PWM_MC0_CH2_L_INT_UMSK                   (~(((1U<<PWM_MC0_CH2_L_INT_LEN)-1)<<PWM_MC0_CH2_L_INT_POS))
#define PWM_MC0_CH2_H_INT                        PWM_MC0_CH2_H_INT
#define PWM_MC0_CH2_H_INT_POS                    (5U)
#define PWM_MC0_CH2_H_INT_LEN                    (1U)
#define PWM_MC0_CH2_H_INT_MSK                    (((1U<<PWM_MC0_CH2_H_INT_LEN)-1)<<PWM_MC0_CH2_H_INT_POS)
#define PWM_MC0_CH2_H_INT_UMSK                   (~(((1U<<PWM_MC0_CH2_H_INT_LEN)-1)<<PWM_MC0_CH2_H_INT_POS))
#define PWM_MC0_CH3_L_INT                        PWM_MC0_CH3_L_INT
#define PWM_MC0_CH3_L_INT_POS                    (6U)
#define PWM_MC0_CH3_L_INT_LEN                    (1U)
#define PWM_MC0_CH3_L_INT_MSK                    (((1U<<PWM_MC0_CH3_L_INT_LEN)-1)<<PWM_MC0_CH3_L_INT_POS)
#define PWM_MC0_CH3_L_INT_UMSK                   (~(((1U<<PWM_MC0_CH3_L_INT_LEN)-1)<<PWM_MC0_CH3_L_INT_POS))
#define PWM_MC0_CH3_H_INT                        PWM_MC0_CH3_H_INT
#define PWM_MC0_CH3_H_INT_POS                    (7U)
#define PWM_MC0_CH3_H_INT_LEN                    (1U)
#define PWM_MC0_CH3_H_INT_MSK                    (((1U<<PWM_MC0_CH3_H_INT_LEN)-1)<<PWM_MC0_CH3_H_INT_POS)
#define PWM_MC0_CH3_H_INT_UMSK                   (~(((1U<<PWM_MC0_CH3_H_INT_LEN)-1)<<PWM_MC0_CH3_H_INT_POS))
#define PWM_MC0_PRDE_INT                         PWM_MC0_PRDE_INT
#define PWM_MC0_PRDE_INT_POS                     (8U)
#define PWM_MC0_PRDE_INT_LEN                     (1U)
#define PWM_MC0_PRDE_INT_MSK                     (((1U<<PWM_MC0_PRDE_INT_LEN)-1)<<PWM_MC0_PRDE_INT_POS)
#define PWM_MC0_PRDE_INT_UMSK                    (~(((1U<<PWM_MC0_PRDE_INT_LEN)-1)<<PWM_MC0_PRDE_INT_POS))
#define PWM_MC0_BRK_INT                          PWM_MC0_BRK_INT
#define PWM_MC0_BRK_INT_POS                      (9U)
#define PWM_MC0_BRK_INT_LEN                      (1U)
#define PWM_MC0_BRK_INT_MSK                      (((1U<<PWM_MC0_BRK_INT_LEN)-1)<<PWM_MC0_BRK_INT_POS)
#define PWM_MC0_BRK_INT_UMSK                     (~(((1U<<PWM_MC0_BRK_INT_LEN)-1)<<PWM_MC0_BRK_INT_POS))
#define PWM_MC0_REPT_INT                         PWM_MC0_REPT_INT
#define PWM_MC0_REPT_INT_POS                     (10U)
#define PWM_MC0_REPT_INT_LEN                     (1U)
#define PWM_MC0_REPT_INT_MSK                     (((1U<<PWM_MC0_REPT_INT_LEN)-1)<<PWM_MC0_REPT_INT_POS)
#define PWM_MC0_REPT_INT_UMSK                    (~(((1U<<PWM_MC0_REPT_INT_LEN)-1)<<PWM_MC0_REPT_INT_POS))

/* 0x64 : pwm_mc0_int_mask */
#define PWM_MC0_INT_MASK_OFFSET                  (0x64)
#define PWM_MC0_CH0_L_MASK                       PWM_MC0_CH0_L_MASK
#define PWM_MC0_CH0_L_MASK_POS                   (0U)
#define PWM_MC0_CH0_L_MASK_LEN                   (1U)
#define PWM_MC0_CH0_L_MASK_MSK                   (((1U<<PWM_MC0_CH0_L_MASK_LEN)-1)<<PWM_MC0_CH0_L_MASK_POS)
#define PWM_MC0_CH0_L_MASK_UMSK                  (~(((1U<<PWM_MC0_CH0_L_MASK_LEN)-1)<<PWM_MC0_CH0_L_MASK_POS))
#define PWM_MC0_CH0_H_MASK                       PWM_MC0_CH0_H_MASK
#define PWM_MC0_CH0_H_MASK_POS                   (1U)
#define PWM_MC0_CH0_H_MASK_LEN                   (1U)
#define PWM_MC0_CH0_H_MASK_MSK                   (((1U<<PWM_MC0_CH0_H_MASK_LEN)-1)<<PWM_MC0_CH0_H_MASK_POS)
#define PWM_MC0_CH0_H_MASK_UMSK                  (~(((1U<<PWM_MC0_CH0_H_MASK_LEN)-1)<<PWM_MC0_CH0_H_MASK_POS))
#define PWM_MC0_CH1_L_MASK                       PWM_MC0_CH1_L_MASK
#define PWM_MC0_CH1_L_MASK_POS                   (2U)
#define PWM_MC0_CH1_L_MASK_LEN                   (1U)
#define PWM_MC0_CH1_L_MASK_MSK                   (((1U<<PWM_MC0_CH1_L_MASK_LEN)-1)<<PWM_MC0_CH1_L_MASK_POS)
#define PWM_MC0_CH1_L_MASK_UMSK                  (~(((1U<<PWM_MC0_CH1_L_MASK_LEN)-1)<<PWM_MC0_CH1_L_MASK_POS))
#define PWM_MC0_CH1_H_MASK                       PWM_MC0_CH1_H_MASK
#define PWM_MC0_CH1_H_MASK_POS                   (3U)
#define PWM_MC0_CH1_H_MASK_LEN                   (1U)
#define PWM_MC0_CH1_H_MASK_MSK                   (((1U<<PWM_MC0_CH1_H_MASK_LEN)-1)<<PWM_MC0_CH1_H_MASK_POS)
#define PWM_MC0_CH1_H_MASK_UMSK                  (~(((1U<<PWM_MC0_CH1_H_MASK_LEN)-1)<<PWM_MC0_CH1_H_MASK_POS))
#define PWM_MC0_CH2_L_MASK                       PWM_MC0_CH2_L_MASK
#define PWM_MC0_CH2_L_MASK_POS                   (4U)
#define PWM_MC0_CH2_L_MASK_LEN                   (1U)
#define PWM_MC0_CH2_L_MASK_MSK                   (((1U<<PWM_MC0_CH2_L_MASK_LEN)-1)<<PWM_MC0_CH2_L_MASK_POS)
#define PWM_MC0_CH2_L_MASK_UMSK                  (~(((1U<<PWM_MC0_CH2_L_MASK_LEN)-1)<<PWM_MC0_CH2_L_MASK_POS))
#define PWM_MC0_CH2_H_MASK                       PWM_MC0_CH2_H_MASK
#define PWM_MC0_CH2_H_MASK_POS                   (5U)
#define PWM_MC0_CH2_H_MASK_LEN                   (1U)
#define PWM_MC0_CH2_H_MASK_MSK                   (((1U<<PWM_MC0_CH2_H_MASK_LEN)-1)<<PWM_MC0_CH2_H_MASK_POS)
#define PWM_MC0_CH2_H_MASK_UMSK                  (~(((1U<<PWM_MC0_CH2_H_MASK_LEN)-1)<<PWM_MC0_CH2_H_MASK_POS))
#define PWM_MC0_CH3_L_MASK                       PWM_MC0_CH3_L_MASK
#define PWM_MC0_CH3_L_MASK_POS                   (6U)
#define PWM_MC0_CH3_L_MASK_LEN                   (1U)
#define PWM_MC0_CH3_L_MASK_MSK                   (((1U<<PWM_MC0_CH3_L_MASK_LEN)-1)<<PWM_MC0_CH3_L_MASK_POS)
#define PWM_MC0_CH3_L_MASK_UMSK                  (~(((1U<<PWM_MC0_CH3_L_MASK_LEN)-1)<<PWM_MC0_CH3_L_MASK_POS))
#define PWM_MC0_CH3_H_MASK                       PWM_MC0_CH3_H_MASK
#define PWM_MC0_CH3_H_MASK_POS                   (7U)
#define PWM_MC0_CH3_H_MASK_LEN                   (1U)
#define PWM_MC0_CH3_H_MASK_MSK                   (((1U<<PWM_MC0_CH3_H_MASK_LEN)-1)<<PWM_MC0_CH3_H_MASK_POS)
#define PWM_MC0_CH3_H_MASK_UMSK                  (~(((1U<<PWM_MC0_CH3_H_MASK_LEN)-1)<<PWM_MC0_CH3_H_MASK_POS))
#define PWM_MC0_PRDE_MASK                        PWM_MC0_PRDE_MASK
#define PWM_MC0_PRDE_MASK_POS                    (8U)
#define PWM_MC0_PRDE_MASK_LEN                    (1U)
#define PWM_MC0_PRDE_MASK_MSK                    (((1U<<PWM_MC0_PRDE_MASK_LEN)-1)<<PWM_MC0_PRDE_MASK_POS)
#define PWM_MC0_PRDE_MASK_UMSK                   (~(((1U<<PWM_MC0_PRDE_MASK_LEN)-1)<<PWM_MC0_PRDE_MASK_POS))
#define PWM_MC0_BRK_MASK                         PWM_MC0_BRK_MASK
#define PWM_MC0_BRK_MASK_POS                     (9U)
#define PWM_MC0_BRK_MASK_LEN                     (1U)
#define PWM_MC0_BRK_MASK_MSK                     (((1U<<PWM_MC0_BRK_MASK_LEN)-1)<<PWM_MC0_BRK_MASK_POS)
#define PWM_MC0_BRK_MASK_UMSK                    (~(((1U<<PWM_MC0_BRK_MASK_LEN)-1)<<PWM_MC0_BRK_MASK_POS))
#define PWM_MC0_REPT_MASK                        PWM_MC0_REPT_MASK
#define PWM_MC0_REPT_MASK_POS                    (10U)
#define PWM_MC0_REPT_MASK_LEN                    (1U)
#define PWM_MC0_REPT_MASK_MSK                    (((1U<<PWM_MC0_REPT_MASK_LEN)-1)<<PWM_MC0_REPT_MASK_POS)
#define PWM_MC0_REPT_MASK_UMSK                   (~(((1U<<PWM_MC0_REPT_MASK_LEN)-1)<<PWM_MC0_REPT_MASK_POS))

/* 0x68 : pwm_mc0_int_clear */
#define PWM_MC0_INT_CLEAR_OFFSET                 (0x68)
#define PWM_MC0_CH0_L_CLR                        PWM_MC0_CH0_L_CLR
#define PWM_MC0_CH0_L_CLR_POS                    (0U)
#define PWM_MC0_CH0_L_CLR_LEN                    (1U)
#define PWM_MC0_CH0_L_CLR_MSK                    (((1U<<PWM_MC0_CH0_L_CLR_LEN)-1)<<PWM_MC0_CH0_L_CLR_POS)
#define PWM_MC0_CH0_L_CLR_UMSK                   (~(((1U<<PWM_MC0_CH0_L_CLR_LEN)-1)<<PWM_MC0_CH0_L_CLR_POS))
#define PWM_MC0_CH0_H_CLR                        PWM_MC0_CH0_H_CLR
#define PWM_MC0_CH0_H_CLR_POS                    (1U)
#define PWM_MC0_CH0_H_CLR_LEN                    (1U)
#define PWM_MC0_CH0_H_CLR_MSK                    (((1U<<PWM_MC0_CH0_H_CLR_LEN)-1)<<PWM_MC0_CH0_H_CLR_POS)
#define PWM_MC0_CH0_H_CLR_UMSK                   (~(((1U<<PWM_MC0_CH0_H_CLR_LEN)-1)<<PWM_MC0_CH0_H_CLR_POS))
#define PWM_MC0_CH1_L_CLR                        PWM_MC0_CH1_L_CLR
#define PWM_MC0_CH1_L_CLR_POS                    (2U)
#define PWM_MC0_CH1_L_CLR_LEN                    (1U)
#define PWM_MC0_CH1_L_CLR_MSK                    (((1U<<PWM_MC0_CH1_L_CLR_LEN)-1)<<PWM_MC0_CH1_L_CLR_POS)
#define PWM_MC0_CH1_L_CLR_UMSK                   (~(((1U<<PWM_MC0_CH1_L_CLR_LEN)-1)<<PWM_MC0_CH1_L_CLR_POS))
#define PWM_MC0_CH1_H_CLR                        PWM_MC0_CH1_H_CLR
#define PWM_MC0_CH1_H_CLR_POS                    (3U)
#define PWM_MC0_CH1_H_CLR_LEN                    (1U)
#define PWM_MC0_CH1_H_CLR_MSK                    (((1U<<PWM_MC0_CH1_H_CLR_LEN)-1)<<PWM_MC0_CH1_H_CLR_POS)
#define PWM_MC0_CH1_H_CLR_UMSK                   (~(((1U<<PWM_MC0_CH1_H_CLR_LEN)-1)<<PWM_MC0_CH1_H_CLR_POS))
#define PWM_MC0_CH2_L_CLR                        PWM_MC0_CH2_L_CLR
#define PWM_MC0_CH2_L_CLR_POS                    (4U)
#define PWM_MC0_CH2_L_CLR_LEN                    (1U)
#define PWM_MC0_CH2_L_CLR_MSK                    (((1U<<PWM_MC0_CH2_L_CLR_LEN)-1)<<PWM_MC0_CH2_L_CLR_POS)
#define PWM_MC0_CH2_L_CLR_UMSK                   (~(((1U<<PWM_MC0_CH2_L_CLR_LEN)-1)<<PWM_MC0_CH2_L_CLR_POS))
#define PWM_MC0_CH2_H_CLR                        PWM_MC0_CH2_H_CLR
#define PWM_MC0_CH2_H_CLR_POS                    (5U)
#define PWM_MC0_CH2_H_CLR_LEN                    (1U)
#define PWM_MC0_CH2_H_CLR_MSK                    (((1U<<PWM_MC0_CH2_H_CLR_LEN)-1)<<PWM_MC0_CH2_H_CLR_POS)
#define PWM_MC0_CH2_H_CLR_UMSK                   (~(((1U<<PWM_MC0_CH2_H_CLR_LEN)-1)<<PWM_MC0_CH2_H_CLR_POS))
#define PWM_MC0_CH3_L_CLR                        PWM_MC0_CH3_L_CLR
#define PWM_MC0_CH3_L_CLR_POS                    (6U)
#define PWM_MC0_CH3_L_CLR_LEN                    (1U)
#define PWM_MC0_CH3_L_CLR_MSK                    (((1U<<PWM_MC0_CH3_L_CLR_LEN)-1)<<PWM_MC0_CH3_L_CLR_POS)
#define PWM_MC0_CH3_L_CLR_UMSK                   (~(((1U<<PWM_MC0_CH3_L_CLR_LEN)-1)<<PWM_MC0_CH3_L_CLR_POS))
#define PWM_MC0_CH3_H_CLR                        PWM_MC0_CH3_H_CLR
#define PWM_MC0_CH3_H_CLR_POS                    (7U)
#define PWM_MC0_CH3_H_CLR_LEN                    (1U)
#define PWM_MC0_CH3_H_CLR_MSK                    (((1U<<PWM_MC0_CH3_H_CLR_LEN)-1)<<PWM_MC0_CH3_H_CLR_POS)
#define PWM_MC0_CH3_H_CLR_UMSK                   (~(((1U<<PWM_MC0_CH3_H_CLR_LEN)-1)<<PWM_MC0_CH3_H_CLR_POS))
#define PWM_MC0_PRDE_CLR                         PWM_MC0_PRDE_CLR
#define PWM_MC0_PRDE_CLR_POS                     (8U)
#define PWM_MC0_PRDE_CLR_LEN                     (1U)
#define PWM_MC0_PRDE_CLR_MSK                     (((1U<<PWM_MC0_PRDE_CLR_LEN)-1)<<PWM_MC0_PRDE_CLR_POS)
#define PWM_MC0_PRDE_CLR_UMSK                    (~(((1U<<PWM_MC0_PRDE_CLR_LEN)-1)<<PWM_MC0_PRDE_CLR_POS))
#define PWM_MC0_BRK_CLR                          PWM_MC0_BRK_CLR
#define PWM_MC0_BRK_CLR_POS                      (9U)
#define PWM_MC0_BRK_CLR_LEN                      (1U)
#define PWM_MC0_BRK_CLR_MSK                      (((1U<<PWM_MC0_BRK_CLR_LEN)-1)<<PWM_MC0_BRK_CLR_POS)
#define PWM_MC0_BRK_CLR_UMSK                     (~(((1U<<PWM_MC0_BRK_CLR_LEN)-1)<<PWM_MC0_BRK_CLR_POS))
#define PWM_MC0_REPT_CLR                         PWM_MC0_REPT_CLR
#define PWM_MC0_REPT_CLR_POS                     (10U)
#define PWM_MC0_REPT_CLR_LEN                     (1U)
#define PWM_MC0_REPT_CLR_MSK                     (((1U<<PWM_MC0_REPT_CLR_LEN)-1)<<PWM_MC0_REPT_CLR_POS)
#define PWM_MC0_REPT_CLR_UMSK                    (~(((1U<<PWM_MC0_REPT_CLR_LEN)-1)<<PWM_MC0_REPT_CLR_POS))

/* 0x6c : pwm_mc0_int_en */
#define PWM_MC0_INT_EN_OFFSET                    (0x6c)
#define PWM_MC0_CH0_L_EN                         PWM_MC0_CH0_L_EN
#define PWM_MC0_CH0_L_EN_POS                     (0U)
#define PWM_MC0_CH0_L_EN_LEN                     (1U)
#define PWM_MC0_CH0_L_EN_MSK                     (((1U<<PWM_MC0_CH0_L_EN_LEN)-1)<<PWM_MC0_CH0_L_EN_POS)
#define PWM_MC0_CH0_L_EN_UMSK                    (~(((1U<<PWM_MC0_CH0_L_EN_LEN)-1)<<PWM_MC0_CH0_L_EN_POS))
#define PWM_MC0_CH0_H_EN                         PWM_MC0_CH0_H_EN
#define PWM_MC0_CH0_H_EN_POS                     (1U)
#define PWM_MC0_CH0_H_EN_LEN                     (1U)
#define PWM_MC0_CH0_H_EN_MSK                     (((1U<<PWM_MC0_CH0_H_EN_LEN)-1)<<PWM_MC0_CH0_H_EN_POS)
#define PWM_MC0_CH0_H_EN_UMSK                    (~(((1U<<PWM_MC0_CH0_H_EN_LEN)-1)<<PWM_MC0_CH0_H_EN_POS))
#define PWM_MC0_CH1_L_EN                         PWM_MC0_CH1_L_EN
#define PWM_MC0_CH1_L_EN_POS                     (2U)
#define PWM_MC0_CH1_L_EN_LEN                     (1U)
#define PWM_MC0_CH1_L_EN_MSK                     (((1U<<PWM_MC0_CH1_L_EN_LEN)-1)<<PWM_MC0_CH1_L_EN_POS)
#define PWM_MC0_CH1_L_EN_UMSK                    (~(((1U<<PWM_MC0_CH1_L_EN_LEN)-1)<<PWM_MC0_CH1_L_EN_POS))
#define PWM_MC0_CH1_H_EN                         PWM_MC0_CH1_H_EN
#define PWM_MC0_CH1_H_EN_POS                     (3U)
#define PWM_MC0_CH1_H_EN_LEN                     (1U)
#define PWM_MC0_CH1_H_EN_MSK                     (((1U<<PWM_MC0_CH1_H_EN_LEN)-1)<<PWM_MC0_CH1_H_EN_POS)
#define PWM_MC0_CH1_H_EN_UMSK                    (~(((1U<<PWM_MC0_CH1_H_EN_LEN)-1)<<PWM_MC0_CH1_H_EN_POS))
#define PWM_MC0_CH2_L_EN                         PWM_MC0_CH2_L_EN
#define PWM_MC0_CH2_L_EN_POS                     (4U)
#define PWM_MC0_CH2_L_EN_LEN                     (1U)
#define PWM_MC0_CH2_L_EN_MSK                     (((1U<<PWM_MC0_CH2_L_EN_LEN)-1)<<PWM_MC0_CH2_L_EN_POS)
#define PWM_MC0_CH2_L_EN_UMSK                    (~(((1U<<PWM_MC0_CH2_L_EN_LEN)-1)<<PWM_MC0_CH2_L_EN_POS))
#define PWM_MC0_CH2_H_EN                         PWM_MC0_CH2_H_EN
#define PWM_MC0_CH2_H_EN_POS                     (5U)
#define PWM_MC0_CH2_H_EN_LEN                     (1U)
#define PWM_MC0_CH2_H_EN_MSK                     (((1U<<PWM_MC0_CH2_H_EN_LEN)-1)<<PWM_MC0_CH2_H_EN_POS)
#define PWM_MC0_CH2_H_EN_UMSK                    (~(((1U<<PWM_MC0_CH2_H_EN_LEN)-1)<<PWM_MC0_CH2_H_EN_POS))
#define PWM_MC0_CH3_L_EN                         PWM_MC0_CH3_L_EN
#define PWM_MC0_CH3_L_EN_POS                     (6U)
#define PWM_MC0_CH3_L_EN_LEN                     (1U)
#define PWM_MC0_CH3_L_EN_MSK                     (((1U<<PWM_MC0_CH3_L_EN_LEN)-1)<<PWM_MC0_CH3_L_EN_POS)
#define PWM_MC0_CH3_L_EN_UMSK                    (~(((1U<<PWM_MC0_CH3_L_EN_LEN)-1)<<PWM_MC0_CH3_L_EN_POS))
#define PWM_MC0_CH3_H_EN                         PWM_MC0_CH3_H_EN
#define PWM_MC0_CH3_H_EN_POS                     (7U)
#define PWM_MC0_CH3_H_EN_LEN                     (1U)
#define PWM_MC0_CH3_H_EN_MSK                     (((1U<<PWM_MC0_CH3_H_EN_LEN)-1)<<PWM_MC0_CH3_H_EN_POS)
#define PWM_MC0_CH3_H_EN_UMSK                    (~(((1U<<PWM_MC0_CH3_H_EN_LEN)-1)<<PWM_MC0_CH3_H_EN_POS))
#define PWM_MC0_PRDE_EN                          PWM_MC0_PRDE_EN
#define PWM_MC0_PRDE_EN_POS                      (8U)
#define PWM_MC0_PRDE_EN_LEN                      (1U)
#define PWM_MC0_PRDE_EN_MSK                      (((1U<<PWM_MC0_PRDE_EN_LEN)-1)<<PWM_MC0_PRDE_EN_POS)
#define PWM_MC0_PRDE_EN_UMSK                     (~(((1U<<PWM_MC0_PRDE_EN_LEN)-1)<<PWM_MC0_PRDE_EN_POS))
#define PWM_MC0_BRK_EN                           PWM_MC0_BRK_EN
#define PWM_MC0_BRK_EN_POS                       (9U)
#define PWM_MC0_BRK_EN_LEN                       (1U)
#define PWM_MC0_BRK_EN_MSK                       (((1U<<PWM_MC0_BRK_EN_LEN)-1)<<PWM_MC0_BRK_EN_POS)
#define PWM_MC0_BRK_EN_UMSK                      (~(((1U<<PWM_MC0_BRK_EN_LEN)-1)<<PWM_MC0_BRK_EN_POS))
#define PWM_MC0_REPT_EN                          PWM_MC0_REPT_EN
#define PWM_MC0_REPT_EN_POS                      (10U)
#define PWM_MC0_REPT_EN_LEN                      (1U)
#define PWM_MC0_REPT_EN_MSK                      (((1U<<PWM_MC0_REPT_EN_LEN)-1)<<PWM_MC0_REPT_EN_POS)
#define PWM_MC0_REPT_EN_UMSK                     (~(((1U<<PWM_MC0_REPT_EN_LEN)-1)<<PWM_MC0_REPT_EN_POS))

/* 0x80 : pwm_mc1_config0 */
#define PWM_MC1_CONFIG0_OFFSET                   (0x80)
#define PWM_MC1_CLK_DIV                          PWM_MC1_CLK_DIV
#define PWM_MC1_CLK_DIV_POS                      (0U)
#define PWM_MC1_CLK_DIV_LEN                      (16U)
#define PWM_MC1_CLK_DIV_MSK                      (((1U<<PWM_MC1_CLK_DIV_LEN)-1)<<PWM_MC1_CLK_DIV_POS)
#define PWM_MC1_CLK_DIV_UMSK                     (~(((1U<<PWM_MC1_CLK_DIV_LEN)-1)<<PWM_MC1_CLK_DIV_POS))
#define PWM_MC1_STOP_ON_REPT                     PWM_MC1_STOP_ON_REPT
#define PWM_MC1_STOP_ON_REPT_POS                 (19U)
#define PWM_MC1_STOP_ON_REPT_LEN                 (1U)
#define PWM_MC1_STOP_ON_REPT_MSK                 (((1U<<PWM_MC1_STOP_ON_REPT_LEN)-1)<<PWM_MC1_STOP_ON_REPT_POS)
#define PWM_MC1_STOP_ON_REPT_UMSK                (~(((1U<<PWM_MC1_STOP_ON_REPT_LEN)-1)<<PWM_MC1_STOP_ON_REPT_POS))
#define PWM_MC1_ADC_TRG_SRC                      PWM_MC1_ADC_TRG_SRC
#define PWM_MC1_ADC_TRG_SRC_POS                  (20U)
#define PWM_MC1_ADC_TRG_SRC_LEN                  (4U)
#define PWM_MC1_ADC_TRG_SRC_MSK                  (((1U<<PWM_MC1_ADC_TRG_SRC_LEN)-1)<<PWM_MC1_ADC_TRG_SRC_POS)
#define PWM_MC1_ADC_TRG_SRC_UMSK                 (~(((1U<<PWM_MC1_ADC_TRG_SRC_LEN)-1)<<PWM_MC1_ADC_TRG_SRC_POS))
#define PWM_MC1_SW_BREAK_EN                      PWM_MC1_SW_BREAK_EN
#define PWM_MC1_SW_BREAK_EN_POS                  (24U)
#define PWM_MC1_SW_BREAK_EN_LEN                  (1U)
#define PWM_MC1_SW_BREAK_EN_MSK                  (((1U<<PWM_MC1_SW_BREAK_EN_LEN)-1)<<PWM_MC1_SW_BREAK_EN_POS)
#define PWM_MC1_SW_BREAK_EN_UMSK                 (~(((1U<<PWM_MC1_SW_BREAK_EN_LEN)-1)<<PWM_MC1_SW_BREAK_EN_POS))
#define PWM_MC1_EXT_BREAK_EN                     PWM_MC1_EXT_BREAK_EN
#define PWM_MC1_EXT_BREAK_EN_POS                 (25U)
#define PWM_MC1_EXT_BREAK_EN_LEN                 (1U)
#define PWM_MC1_EXT_BREAK_EN_MSK                 (((1U<<PWM_MC1_EXT_BREAK_EN_LEN)-1)<<PWM_MC1_EXT_BREAK_EN_POS)
#define PWM_MC1_EXT_BREAK_EN_UMSK                (~(((1U<<PWM_MC1_EXT_BREAK_EN_LEN)-1)<<PWM_MC1_EXT_BREAK_EN_POS))
#define PWM_MC1_EXT_BREAK_PL                     PWM_MC1_EXT_BREAK_PL
#define PWM_MC1_EXT_BREAK_PL_POS                 (26U)
#define PWM_MC1_EXT_BREAK_PL_LEN                 (1U)
#define PWM_MC1_EXT_BREAK_PL_MSK                 (((1U<<PWM_MC1_EXT_BREAK_PL_LEN)-1)<<PWM_MC1_EXT_BREAK_PL_POS)
#define PWM_MC1_EXT_BREAK_PL_UMSK                (~(((1U<<PWM_MC1_EXT_BREAK_PL_LEN)-1)<<PWM_MC1_EXT_BREAK_PL_POS))
#define PWM_MC1_STOP_EN                          PWM_MC1_STOP_EN
#define PWM_MC1_STOP_EN_POS                      (27U)
#define PWM_MC1_STOP_EN_LEN                      (1U)
#define PWM_MC1_STOP_EN_MSK                      (((1U<<PWM_MC1_STOP_EN_LEN)-1)<<PWM_MC1_STOP_EN_POS)
#define PWM_MC1_STOP_EN_UMSK                     (~(((1U<<PWM_MC1_STOP_EN_LEN)-1)<<PWM_MC1_STOP_EN_POS))
#define PWM_MC1_STOP_MODE                        PWM_MC1_STOP_MODE
#define PWM_MC1_STOP_MODE_POS                    (28U)
#define PWM_MC1_STOP_MODE_LEN                    (1U)
#define PWM_MC1_STOP_MODE_MSK                    (((1U<<PWM_MC1_STOP_MODE_LEN)-1)<<PWM_MC1_STOP_MODE_POS)
#define PWM_MC1_STOP_MODE_UMSK                   (~(((1U<<PWM_MC1_STOP_MODE_LEN)-1)<<PWM_MC1_STOP_MODE_POS))
#define PWM_MC1_STS_STOP                         PWM_MC1_STS_STOP
#define PWM_MC1_STS_STOP_POS                     (29U)
#define PWM_MC1_STS_STOP_LEN                     (1U)
#define PWM_MC1_STS_STOP_MSK                     (((1U<<PWM_MC1_STS_STOP_LEN)-1)<<PWM_MC1_STS_STOP_POS)
#define PWM_MC1_STS_STOP_UMSK                    (~(((1U<<PWM_MC1_STS_STOP_LEN)-1)<<PWM_MC1_STS_STOP_POS))
#define PWM_MC1_REG_CLK_SEL                      PWM_MC1_REG_CLK_SEL
#define PWM_MC1_REG_CLK_SEL_POS                  (30U)
#define PWM_MC1_REG_CLK_SEL_LEN                  (2U)
#define PWM_MC1_REG_CLK_SEL_MSK                  (((1U<<PWM_MC1_REG_CLK_SEL_LEN)-1)<<PWM_MC1_REG_CLK_SEL_POS)
#define PWM_MC1_REG_CLK_SEL_UMSK                 (~(((1U<<PWM_MC1_REG_CLK_SEL_LEN)-1)<<PWM_MC1_REG_CLK_SEL_POS))

/* 0x84 : pwm_mc1_config1 */
#define PWM_MC1_CONFIG1_OFFSET                   (0x84)
#define PWM_MC1_CH0_PEN                          PWM_MC1_CH0_PEN
#define PWM_MC1_CH0_PEN_POS                      (0U)
#define PWM_MC1_CH0_PEN_LEN                      (1U)
#define PWM_MC1_CH0_PEN_MSK                      (((1U<<PWM_MC1_CH0_PEN_LEN)-1)<<PWM_MC1_CH0_PEN_POS)
#define PWM_MC1_CH0_PEN_UMSK                     (~(((1U<<PWM_MC1_CH0_PEN_LEN)-1)<<PWM_MC1_CH0_PEN_POS))
#define PWM_MC1_CH0_PSI                          PWM_MC1_CH0_PSI
#define PWM_MC1_CH0_PSI_POS                      (1U)
#define PWM_MC1_CH0_PSI_LEN                      (1U)
#define PWM_MC1_CH0_PSI_MSK                      (((1U<<PWM_MC1_CH0_PSI_LEN)-1)<<PWM_MC1_CH0_PSI_POS)
#define PWM_MC1_CH0_PSI_UMSK                     (~(((1U<<PWM_MC1_CH0_PSI_LEN)-1)<<PWM_MC1_CH0_PSI_POS))
#define PWM_MC1_CH0_NEN                          PWM_MC1_CH0_NEN
#define PWM_MC1_CH0_NEN_POS                      (2U)
#define PWM_MC1_CH0_NEN_LEN                      (1U)
#define PWM_MC1_CH0_NEN_MSK                      (((1U<<PWM_MC1_CH0_NEN_LEN)-1)<<PWM_MC1_CH0_NEN_POS)
#define PWM_MC1_CH0_NEN_UMSK                     (~(((1U<<PWM_MC1_CH0_NEN_LEN)-1)<<PWM_MC1_CH0_NEN_POS))
#define PWM_MC1_CH0_NSI                          PWM_MC1_CH0_NSI
#define PWM_MC1_CH0_NSI_POS                      (3U)
#define PWM_MC1_CH0_NSI_LEN                      (1U)
#define PWM_MC1_CH0_NSI_MSK                      (((1U<<PWM_MC1_CH0_NSI_LEN)-1)<<PWM_MC1_CH0_NSI_POS)
#define PWM_MC1_CH0_NSI_UMSK                     (~(((1U<<PWM_MC1_CH0_NSI_LEN)-1)<<PWM_MC1_CH0_NSI_POS))
#define PWM_MC1_CH1_PEN                          PWM_MC1_CH1_PEN
#define PWM_MC1_CH1_PEN_POS                      (4U)
#define PWM_MC1_CH1_PEN_LEN                      (1U)
#define PWM_MC1_CH1_PEN_MSK                      (((1U<<PWM_MC1_CH1_PEN_LEN)-1)<<PWM_MC1_CH1_PEN_POS)
#define PWM_MC1_CH1_PEN_UMSK                     (~(((1U<<PWM_MC1_CH1_PEN_LEN)-1)<<PWM_MC1_CH1_PEN_POS))
#define PWM_MC1_CH1_PSI                          PWM_MC1_CH1_PSI
#define PWM_MC1_CH1_PSI_POS                      (5U)
#define PWM_MC1_CH1_PSI_LEN                      (1U)
#define PWM_MC1_CH1_PSI_MSK                      (((1U<<PWM_MC1_CH1_PSI_LEN)-1)<<PWM_MC1_CH1_PSI_POS)
#define PWM_MC1_CH1_PSI_UMSK                     (~(((1U<<PWM_MC1_CH1_PSI_LEN)-1)<<PWM_MC1_CH1_PSI_POS))
#define PWM_MC1_CH1_NEN                          PWM_MC1_CH1_NEN
#define PWM_MC1_CH1_NEN_POS                      (6U)
#define PWM_MC1_CH1_NEN_LEN                      (1U)
#define PWM_MC1_CH1_NEN_MSK                      (((1U<<PWM_MC1_CH1_NEN_LEN)-1)<<PWM_MC1_CH1_NEN_POS)
#define PWM_MC1_CH1_NEN_UMSK                     (~(((1U<<PWM_MC1_CH1_NEN_LEN)-1)<<PWM_MC1_CH1_NEN_POS))
#define PWM_MC1_CH1_NSI                          PWM_MC1_CH1_NSI
#define PWM_MC1_CH1_NSI_POS                      (7U)
#define PWM_MC1_CH1_NSI_LEN                      (1U)
#define PWM_MC1_CH1_NSI_MSK                      (((1U<<PWM_MC1_CH1_NSI_LEN)-1)<<PWM_MC1_CH1_NSI_POS)
#define PWM_MC1_CH1_NSI_UMSK                     (~(((1U<<PWM_MC1_CH1_NSI_LEN)-1)<<PWM_MC1_CH1_NSI_POS))
#define PWM_MC1_CH2_PEN                          PWM_MC1_CH2_PEN
#define PWM_MC1_CH2_PEN_POS                      (8U)
#define PWM_MC1_CH2_PEN_LEN                      (1U)
#define PWM_MC1_CH2_PEN_MSK                      (((1U<<PWM_MC1_CH2_PEN_LEN)-1)<<PWM_MC1_CH2_PEN_POS)
#define PWM_MC1_CH2_PEN_UMSK                     (~(((1U<<PWM_MC1_CH2_PEN_LEN)-1)<<PWM_MC1_CH2_PEN_POS))
#define PWM_MC1_CH2_PSI                          PWM_MC1_CH2_PSI
#define PWM_MC1_CH2_PSI_POS                      (9U)
#define PWM_MC1_CH2_PSI_LEN                      (1U)
#define PWM_MC1_CH2_PSI_MSK                      (((1U<<PWM_MC1_CH2_PSI_LEN)-1)<<PWM_MC1_CH2_PSI_POS)
#define PWM_MC1_CH2_PSI_UMSK                     (~(((1U<<PWM_MC1_CH2_PSI_LEN)-1)<<PWM_MC1_CH2_PSI_POS))
#define PWM_MC1_CH2_NEN                          PWM_MC1_CH2_NEN
#define PWM_MC1_CH2_NEN_POS                      (10U)
#define PWM_MC1_CH2_NEN_LEN                      (1U)
#define PWM_MC1_CH2_NEN_MSK                      (((1U<<PWM_MC1_CH2_NEN_LEN)-1)<<PWM_MC1_CH2_NEN_POS)
#define PWM_MC1_CH2_NEN_UMSK                     (~(((1U<<PWM_MC1_CH2_NEN_LEN)-1)<<PWM_MC1_CH2_NEN_POS))
#define PWM_MC1_CH2_NSI                          PWM_MC1_CH2_NSI
#define PWM_MC1_CH2_NSI_POS                      (11U)
#define PWM_MC1_CH2_NSI_LEN                      (1U)
#define PWM_MC1_CH2_NSI_MSK                      (((1U<<PWM_MC1_CH2_NSI_LEN)-1)<<PWM_MC1_CH2_NSI_POS)
#define PWM_MC1_CH2_NSI_UMSK                     (~(((1U<<PWM_MC1_CH2_NSI_LEN)-1)<<PWM_MC1_CH2_NSI_POS))
#define PWM_MC1_CH3_PEN                          PWM_MC1_CH3_PEN
#define PWM_MC1_CH3_PEN_POS                      (12U)
#define PWM_MC1_CH3_PEN_LEN                      (1U)
#define PWM_MC1_CH3_PEN_MSK                      (((1U<<PWM_MC1_CH3_PEN_LEN)-1)<<PWM_MC1_CH3_PEN_POS)
#define PWM_MC1_CH3_PEN_UMSK                     (~(((1U<<PWM_MC1_CH3_PEN_LEN)-1)<<PWM_MC1_CH3_PEN_POS))
#define PWM_MC1_CH3_PSI                          PWM_MC1_CH3_PSI
#define PWM_MC1_CH3_PSI_POS                      (13U)
#define PWM_MC1_CH3_PSI_LEN                      (1U)
#define PWM_MC1_CH3_PSI_MSK                      (((1U<<PWM_MC1_CH3_PSI_LEN)-1)<<PWM_MC1_CH3_PSI_POS)
#define PWM_MC1_CH3_PSI_UMSK                     (~(((1U<<PWM_MC1_CH3_PSI_LEN)-1)<<PWM_MC1_CH3_PSI_POS))
#define PWM_MC1_CH3_NEN                          PWM_MC1_CH3_NEN
#define PWM_MC1_CH3_NEN_POS                      (14U)
#define PWM_MC1_CH3_NEN_LEN                      (1U)
#define PWM_MC1_CH3_NEN_MSK                      (((1U<<PWM_MC1_CH3_NEN_LEN)-1)<<PWM_MC1_CH3_NEN_POS)
#define PWM_MC1_CH3_NEN_UMSK                     (~(((1U<<PWM_MC1_CH3_NEN_LEN)-1)<<PWM_MC1_CH3_NEN_POS))
#define PWM_MC1_CH3_NSI                          PWM_MC1_CH3_NSI
#define PWM_MC1_CH3_NSI_POS                      (15U)
#define PWM_MC1_CH3_NSI_LEN                      (1U)
#define PWM_MC1_CH3_NSI_MSK                      (((1U<<PWM_MC1_CH3_NSI_LEN)-1)<<PWM_MC1_CH3_NSI_POS)
#define PWM_MC1_CH3_NSI_UMSK                     (~(((1U<<PWM_MC1_CH3_NSI_LEN)-1)<<PWM_MC1_CH3_NSI_POS))
#define PWM_MC1_CH0_PPL                          PWM_MC1_CH0_PPL
#define PWM_MC1_CH0_PPL_POS                      (16U)
#define PWM_MC1_CH0_PPL_LEN                      (1U)
#define PWM_MC1_CH0_PPL_MSK                      (((1U<<PWM_MC1_CH0_PPL_LEN)-1)<<PWM_MC1_CH0_PPL_POS)
#define PWM_MC1_CH0_PPL_UMSK                     (~(((1U<<PWM_MC1_CH0_PPL_LEN)-1)<<PWM_MC1_CH0_PPL_POS))
#define PWM_MC1_CH0_NPL                          PWM_MC1_CH0_NPL
#define PWM_MC1_CH0_NPL_POS                      (17U)
#define PWM_MC1_CH0_NPL_LEN                      (1U)
#define PWM_MC1_CH0_NPL_MSK                      (((1U<<PWM_MC1_CH0_NPL_LEN)-1)<<PWM_MC1_CH0_NPL_POS)
#define PWM_MC1_CH0_NPL_UMSK                     (~(((1U<<PWM_MC1_CH0_NPL_LEN)-1)<<PWM_MC1_CH0_NPL_POS))
#define PWM_MC1_CH1_PPL                          PWM_MC1_CH1_PPL
#define PWM_MC1_CH1_PPL_POS                      (18U)
#define PWM_MC1_CH1_PPL_LEN                      (1U)
#define PWM_MC1_CH1_PPL_MSK                      (((1U<<PWM_MC1_CH1_PPL_LEN)-1)<<PWM_MC1_CH1_PPL_POS)
#define PWM_MC1_CH1_PPL_UMSK                     (~(((1U<<PWM_MC1_CH1_PPL_LEN)-1)<<PWM_MC1_CH1_PPL_POS))
#define PWM_MC1_CH1_NPL                          PWM_MC1_CH1_NPL
#define PWM_MC1_CH1_NPL_POS                      (19U)
#define PWM_MC1_CH1_NPL_LEN                      (1U)
#define PWM_MC1_CH1_NPL_MSK                      (((1U<<PWM_MC1_CH1_NPL_LEN)-1)<<PWM_MC1_CH1_NPL_POS)
#define PWM_MC1_CH1_NPL_UMSK                     (~(((1U<<PWM_MC1_CH1_NPL_LEN)-1)<<PWM_MC1_CH1_NPL_POS))
#define PWM_MC1_CH2_PPL                          PWM_MC1_CH2_PPL
#define PWM_MC1_CH2_PPL_POS                      (20U)
#define PWM_MC1_CH2_PPL_LEN                      (1U)
#define PWM_MC1_CH2_PPL_MSK                      (((1U<<PWM_MC1_CH2_PPL_LEN)-1)<<PWM_MC1_CH2_PPL_POS)
#define PWM_MC1_CH2_PPL_UMSK                     (~(((1U<<PWM_MC1_CH2_PPL_LEN)-1)<<PWM_MC1_CH2_PPL_POS))
#define PWM_MC1_CH2_NPL                          PWM_MC1_CH2_NPL
#define PWM_MC1_CH2_NPL_POS                      (21U)
#define PWM_MC1_CH2_NPL_LEN                      (1U)
#define PWM_MC1_CH2_NPL_MSK                      (((1U<<PWM_MC1_CH2_NPL_LEN)-1)<<PWM_MC1_CH2_NPL_POS)
#define PWM_MC1_CH2_NPL_UMSK                     (~(((1U<<PWM_MC1_CH2_NPL_LEN)-1)<<PWM_MC1_CH2_NPL_POS))
#define PWM_MC1_CH3_PPL                          PWM_MC1_CH3_PPL
#define PWM_MC1_CH3_PPL_POS                      (22U)
#define PWM_MC1_CH3_PPL_LEN                      (1U)
#define PWM_MC1_CH3_PPL_MSK                      (((1U<<PWM_MC1_CH3_PPL_LEN)-1)<<PWM_MC1_CH3_PPL_POS)
#define PWM_MC1_CH3_PPL_UMSK                     (~(((1U<<PWM_MC1_CH3_PPL_LEN)-1)<<PWM_MC1_CH3_PPL_POS))
#define PWM_MC1_CH3_NPL                          PWM_MC1_CH3_NPL
#define PWM_MC1_CH3_NPL_POS                      (23U)
#define PWM_MC1_CH3_NPL_LEN                      (1U)
#define PWM_MC1_CH3_NPL_MSK                      (((1U<<PWM_MC1_CH3_NPL_LEN)-1)<<PWM_MC1_CH3_NPL_POS)
#define PWM_MC1_CH3_NPL_UMSK                     (~(((1U<<PWM_MC1_CH3_NPL_LEN)-1)<<PWM_MC1_CH3_NPL_POS))
#define PWM_MC1_CH0_PBS                          PWM_MC1_CH0_PBS
#define PWM_MC1_CH0_PBS_POS                      (24U)
#define PWM_MC1_CH0_PBS_LEN                      (1U)
#define PWM_MC1_CH0_PBS_MSK                      (((1U<<PWM_MC1_CH0_PBS_LEN)-1)<<PWM_MC1_CH0_PBS_POS)
#define PWM_MC1_CH0_PBS_UMSK                     (~(((1U<<PWM_MC1_CH0_PBS_LEN)-1)<<PWM_MC1_CH0_PBS_POS))
#define PWM_MC1_CH0_NBS                          PWM_MC1_CH0_NBS
#define PWM_MC1_CH0_NBS_POS                      (25U)
#define PWM_MC1_CH0_NBS_LEN                      (1U)
#define PWM_MC1_CH0_NBS_MSK                      (((1U<<PWM_MC1_CH0_NBS_LEN)-1)<<PWM_MC1_CH0_NBS_POS)
#define PWM_MC1_CH0_NBS_UMSK                     (~(((1U<<PWM_MC1_CH0_NBS_LEN)-1)<<PWM_MC1_CH0_NBS_POS))
#define PWM_MC1_CH1_PBS                          PWM_MC1_CH1_PBS
#define PWM_MC1_CH1_PBS_POS                      (26U)
#define PWM_MC1_CH1_PBS_LEN                      (1U)
#define PWM_MC1_CH1_PBS_MSK                      (((1U<<PWM_MC1_CH1_PBS_LEN)-1)<<PWM_MC1_CH1_PBS_POS)
#define PWM_MC1_CH1_PBS_UMSK                     (~(((1U<<PWM_MC1_CH1_PBS_LEN)-1)<<PWM_MC1_CH1_PBS_POS))
#define PWM_MC1_CH1_NBS                          PWM_MC1_CH1_NBS
#define PWM_MC1_CH1_NBS_POS                      (27U)
#define PWM_MC1_CH1_NBS_LEN                      (1U)
#define PWM_MC1_CH1_NBS_MSK                      (((1U<<PWM_MC1_CH1_NBS_LEN)-1)<<PWM_MC1_CH1_NBS_POS)
#define PWM_MC1_CH1_NBS_UMSK                     (~(((1U<<PWM_MC1_CH1_NBS_LEN)-1)<<PWM_MC1_CH1_NBS_POS))
#define PWM_MC1_CH2_PBS                          PWM_MC1_CH2_PBS
#define PWM_MC1_CH2_PBS_POS                      (28U)
#define PWM_MC1_CH2_PBS_LEN                      (1U)
#define PWM_MC1_CH2_PBS_MSK                      (((1U<<PWM_MC1_CH2_PBS_LEN)-1)<<PWM_MC1_CH2_PBS_POS)
#define PWM_MC1_CH2_PBS_UMSK                     (~(((1U<<PWM_MC1_CH2_PBS_LEN)-1)<<PWM_MC1_CH2_PBS_POS))
#define PWM_MC1_CH2_NBS                          PWM_MC1_CH2_NBS
#define PWM_MC1_CH2_NBS_POS                      (29U)
#define PWM_MC1_CH2_NBS_LEN                      (1U)
#define PWM_MC1_CH2_NBS_MSK                      (((1U<<PWM_MC1_CH2_NBS_LEN)-1)<<PWM_MC1_CH2_NBS_POS)
#define PWM_MC1_CH2_NBS_UMSK                     (~(((1U<<PWM_MC1_CH2_NBS_LEN)-1)<<PWM_MC1_CH2_NBS_POS))
#define PWM_MC1_CH3_PBS                          PWM_MC1_CH3_PBS
#define PWM_MC1_CH3_PBS_POS                      (30U)
#define PWM_MC1_CH3_PBS_LEN                      (1U)
#define PWM_MC1_CH3_PBS_MSK                      (((1U<<PWM_MC1_CH3_PBS_LEN)-1)<<PWM_MC1_CH3_PBS_POS)
#define PWM_MC1_CH3_PBS_UMSK                     (~(((1U<<PWM_MC1_CH3_PBS_LEN)-1)<<PWM_MC1_CH3_PBS_POS))
#define PWM_MC1_CH3_NBS                          PWM_MC1_CH3_NBS
#define PWM_MC1_CH3_NBS_POS                      (31U)
#define PWM_MC1_CH3_NBS_LEN                      (1U)
#define PWM_MC1_CH3_NBS_MSK                      (((1U<<PWM_MC1_CH3_NBS_LEN)-1)<<PWM_MC1_CH3_NBS_POS)
#define PWM_MC1_CH3_NBS_UMSK                     (~(((1U<<PWM_MC1_CH3_NBS_LEN)-1)<<PWM_MC1_CH3_NBS_POS))

/* 0x88 : pwm_mc1_period */
#define PWM_MC1_PERIOD_OFFSET                    (0x88)
#define PWM_MC1_PERIOD                           PWM_MC1_PERIOD
#define PWM_MC1_PERIOD_POS                       (0U)
#define PWM_MC1_PERIOD_LEN                       (16U)
#define PWM_MC1_PERIOD_MSK                       (((1U<<PWM_MC1_PERIOD_LEN)-1)<<PWM_MC1_PERIOD_POS)
#define PWM_MC1_PERIOD_UMSK                      (~(((1U<<PWM_MC1_PERIOD_LEN)-1)<<PWM_MC1_PERIOD_POS))
#define PWM_MC1_INT_PERIOD_CNT                   PWM_MC1_INT_PERIOD_CNT
#define PWM_MC1_INT_PERIOD_CNT_POS               (16U)
#define PWM_MC1_INT_PERIOD_CNT_LEN               (16U)
#define PWM_MC1_INT_PERIOD_CNT_MSK               (((1U<<PWM_MC1_INT_PERIOD_CNT_LEN)-1)<<PWM_MC1_INT_PERIOD_CNT_POS)
#define PWM_MC1_INT_PERIOD_CNT_UMSK              (~(((1U<<PWM_MC1_INT_PERIOD_CNT_LEN)-1)<<PWM_MC1_INT_PERIOD_CNT_POS))

/* 0x8c : pwm_mc1_dead_time */
#define PWM_MC1_DEAD_TIME_OFFSET                 (0x8c)
#define PWM_MC1_CH0_DTG                          PWM_MC1_CH0_DTG
#define PWM_MC1_CH0_DTG_POS                      (0U)
#define PWM_MC1_CH0_DTG_LEN                      (8U)
#define PWM_MC1_CH0_DTG_MSK                      (((1U<<PWM_MC1_CH0_DTG_LEN)-1)<<PWM_MC1_CH0_DTG_POS)
#define PWM_MC1_CH0_DTG_UMSK                     (~(((1U<<PWM_MC1_CH0_DTG_LEN)-1)<<PWM_MC1_CH0_DTG_POS))
#define PWM_MC1_CH1_DTG                          PWM_MC1_CH1_DTG
#define PWM_MC1_CH1_DTG_POS                      (8U)
#define PWM_MC1_CH1_DTG_LEN                      (8U)
#define PWM_MC1_CH1_DTG_MSK                      (((1U<<PWM_MC1_CH1_DTG_LEN)-1)<<PWM_MC1_CH1_DTG_POS)
#define PWM_MC1_CH1_DTG_UMSK                     (~(((1U<<PWM_MC1_CH1_DTG_LEN)-1)<<PWM_MC1_CH1_DTG_POS))
#define PWM_MC1_CH2_DTG                          PWM_MC1_CH2_DTG
#define PWM_MC1_CH2_DTG_POS                      (16U)
#define PWM_MC1_CH2_DTG_LEN                      (8U)
#define PWM_MC1_CH2_DTG_MSK                      (((1U<<PWM_MC1_CH2_DTG_LEN)-1)<<PWM_MC1_CH2_DTG_POS)
#define PWM_MC1_CH2_DTG_UMSK                     (~(((1U<<PWM_MC1_CH2_DTG_LEN)-1)<<PWM_MC1_CH2_DTG_POS))
#define PWM_MC1_CH3_DTG                          PWM_MC1_CH3_DTG
#define PWM_MC1_CH3_DTG_POS                      (24U)
#define PWM_MC1_CH3_DTG_LEN                      (8U)
#define PWM_MC1_CH3_DTG_MSK                      (((1U<<PWM_MC1_CH3_DTG_LEN)-1)<<PWM_MC1_CH3_DTG_POS)
#define PWM_MC1_CH3_DTG_UMSK                     (~(((1U<<PWM_MC1_CH3_DTG_LEN)-1)<<PWM_MC1_CH3_DTG_POS))

/* 0x90 : pwm_mc1_ch0_thre */
#define PWM_MC1_CH0_THRE_OFFSET                  (0x90)
#define PWM_MC1_CH0_THREL                        PWM_MC1_CH0_THREL
#define PWM_MC1_CH0_THREL_POS                    (0U)
#define PWM_MC1_CH0_THREL_LEN                    (16U)
#define PWM_MC1_CH0_THREL_MSK                    (((1U<<PWM_MC1_CH0_THREL_LEN)-1)<<PWM_MC1_CH0_THREL_POS)
#define PWM_MC1_CH0_THREL_UMSK                   (~(((1U<<PWM_MC1_CH0_THREL_LEN)-1)<<PWM_MC1_CH0_THREL_POS))
#define PWM_MC1_CH0_THREH                        PWM_MC1_CH0_THREH
#define PWM_MC1_CH0_THREH_POS                    (16U)
#define PWM_MC1_CH0_THREH_LEN                    (16U)
#define PWM_MC1_CH0_THREH_MSK                    (((1U<<PWM_MC1_CH0_THREH_LEN)-1)<<PWM_MC1_CH0_THREH_POS)
#define PWM_MC1_CH0_THREH_UMSK                   (~(((1U<<PWM_MC1_CH0_THREH_LEN)-1)<<PWM_MC1_CH0_THREH_POS))

/* 0x94 : pwm_mc1_ch1_thre */
#define PWM_MC1_CH1_THRE_OFFSET                  (0x94)
#define PWM_MC1_CH1_THREL                        PWM_MC1_CH1_THREL
#define PWM_MC1_CH1_THREL_POS                    (0U)
#define PWM_MC1_CH1_THREL_LEN                    (16U)
#define PWM_MC1_CH1_THREL_MSK                    (((1U<<PWM_MC1_CH1_THREL_LEN)-1)<<PWM_MC1_CH1_THREL_POS)
#define PWM_MC1_CH1_THREL_UMSK                   (~(((1U<<PWM_MC1_CH1_THREL_LEN)-1)<<PWM_MC1_CH1_THREL_POS))
#define PWM_MC1_CH1_THREH                        PWM_MC1_CH1_THREH
#define PWM_MC1_CH1_THREH_POS                    (16U)
#define PWM_MC1_CH1_THREH_LEN                    (16U)
#define PWM_MC1_CH1_THREH_MSK                    (((1U<<PWM_MC1_CH1_THREH_LEN)-1)<<PWM_MC1_CH1_THREH_POS)
#define PWM_MC1_CH1_THREH_UMSK                   (~(((1U<<PWM_MC1_CH1_THREH_LEN)-1)<<PWM_MC1_CH1_THREH_POS))

/* 0x98 : pwm_mc1_ch2_thre */
#define PWM_MC1_CH2_THRE_OFFSET                  (0x98)
#define PWM_MC1_CH2_THREL                        PWM_MC1_CH2_THREL
#define PWM_MC1_CH2_THREL_POS                    (0U)
#define PWM_MC1_CH2_THREL_LEN                    (16U)
#define PWM_MC1_CH2_THREL_MSK                    (((1U<<PWM_MC1_CH2_THREL_LEN)-1)<<PWM_MC1_CH2_THREL_POS)
#define PWM_MC1_CH2_THREL_UMSK                   (~(((1U<<PWM_MC1_CH2_THREL_LEN)-1)<<PWM_MC1_CH2_THREL_POS))
#define PWM_MC1_CH2_THREH                        PWM_MC1_CH2_THREH
#define PWM_MC1_CH2_THREH_POS                    (16U)
#define PWM_MC1_CH2_THREH_LEN                    (16U)
#define PWM_MC1_CH2_THREH_MSK                    (((1U<<PWM_MC1_CH2_THREH_LEN)-1)<<PWM_MC1_CH2_THREH_POS)
#define PWM_MC1_CH2_THREH_UMSK                   (~(((1U<<PWM_MC1_CH2_THREH_LEN)-1)<<PWM_MC1_CH2_THREH_POS))

/* 0x9c : pwm_mc1_ch3_thre */
#define PWM_MC1_CH3_THRE_OFFSET                  (0x9c)
#define PWM_MC1_CH3_THREL                        PWM_MC1_CH3_THREL
#define PWM_MC1_CH3_THREL_POS                    (0U)
#define PWM_MC1_CH3_THREL_LEN                    (16U)
#define PWM_MC1_CH3_THREL_MSK                    (((1U<<PWM_MC1_CH3_THREL_LEN)-1)<<PWM_MC1_CH3_THREL_POS)
#define PWM_MC1_CH3_THREL_UMSK                   (~(((1U<<PWM_MC1_CH3_THREL_LEN)-1)<<PWM_MC1_CH3_THREL_POS))
#define PWM_MC1_CH3_THREH                        PWM_MC1_CH3_THREH
#define PWM_MC1_CH3_THREH_POS                    (16U)
#define PWM_MC1_CH3_THREH_LEN                    (16U)
#define PWM_MC1_CH3_THREH_MSK                    (((1U<<PWM_MC1_CH3_THREH_LEN)-1)<<PWM_MC1_CH3_THREH_POS)
#define PWM_MC1_CH3_THREH_UMSK                   (~(((1U<<PWM_MC1_CH3_THREH_LEN)-1)<<PWM_MC1_CH3_THREH_POS))

/* 0xa0 : pwm_mc1_int_sts */
#define PWM_MC1_INT_STS_OFFSET                   (0xa0)
#define PWM_MC1_CH0_L_INT                        PWM_MC1_CH0_L_INT
#define PWM_MC1_CH0_L_INT_POS                    (0U)
#define PWM_MC1_CH0_L_INT_LEN                    (1U)
#define PWM_MC1_CH0_L_INT_MSK                    (((1U<<PWM_MC1_CH0_L_INT_LEN)-1)<<PWM_MC1_CH0_L_INT_POS)
#define PWM_MC1_CH0_L_INT_UMSK                   (~(((1U<<PWM_MC1_CH0_L_INT_LEN)-1)<<PWM_MC1_CH0_L_INT_POS))
#define PWM_MC1_CH0_H_INT                        PWM_MC1_CH0_H_INT
#define PWM_MC1_CH0_H_INT_POS                    (1U)
#define PWM_MC1_CH0_H_INT_LEN                    (1U)
#define PWM_MC1_CH0_H_INT_MSK                    (((1U<<PWM_MC1_CH0_H_INT_LEN)-1)<<PWM_MC1_CH0_H_INT_POS)
#define PWM_MC1_CH0_H_INT_UMSK                   (~(((1U<<PWM_MC1_CH0_H_INT_LEN)-1)<<PWM_MC1_CH0_H_INT_POS))
#define PWM_MC1_CH1_L_INT                        PWM_MC1_CH1_L_INT
#define PWM_MC1_CH1_L_INT_POS                    (2U)
#define PWM_MC1_CH1_L_INT_LEN                    (1U)
#define PWM_MC1_CH1_L_INT_MSK                    (((1U<<PWM_MC1_CH1_L_INT_LEN)-1)<<PWM_MC1_CH1_L_INT_POS)
#define PWM_MC1_CH1_L_INT_UMSK                   (~(((1U<<PWM_MC1_CH1_L_INT_LEN)-1)<<PWM_MC1_CH1_L_INT_POS))
#define PWM_MC1_CH1_H_INT                        PWM_MC1_CH1_H_INT
#define PWM_MC1_CH1_H_INT_POS                    (3U)
#define PWM_MC1_CH1_H_INT_LEN                    (1U)
#define PWM_MC1_CH1_H_INT_MSK                    (((1U<<PWM_MC1_CH1_H_INT_LEN)-1)<<PWM_MC1_CH1_H_INT_POS)
#define PWM_MC1_CH1_H_INT_UMSK                   (~(((1U<<PWM_MC1_CH1_H_INT_LEN)-1)<<PWM_MC1_CH1_H_INT_POS))
#define PWM_MC1_CH2_L_INT                        PWM_MC1_CH2_L_INT
#define PWM_MC1_CH2_L_INT_POS                    (4U)
#define PWM_MC1_CH2_L_INT_LEN                    (1U)
#define PWM_MC1_CH2_L_INT_MSK                    (((1U<<PWM_MC1_CH2_L_INT_LEN)-1)<<PWM_MC1_CH2_L_INT_POS)
#define PWM_MC1_CH2_L_INT_UMSK                   (~(((1U<<PWM_MC1_CH2_L_INT_LEN)-1)<<PWM_MC1_CH2_L_INT_POS))
#define PWM_MC1_CH2_H_INT                        PWM_MC1_CH2_H_INT
#define PWM_MC1_CH2_H_INT_POS                    (5U)
#define PWM_MC1_CH2_H_INT_LEN                    (1U)
#define PWM_MC1_CH2_H_INT_MSK                    (((1U<<PWM_MC1_CH2_H_INT_LEN)-1)<<PWM_MC1_CH2_H_INT_POS)
#define PWM_MC1_CH2_H_INT_UMSK                   (~(((1U<<PWM_MC1_CH2_H_INT_LEN)-1)<<PWM_MC1_CH2_H_INT_POS))
#define PWM_MC1_CH3_L_INT                        PWM_MC1_CH3_L_INT
#define PWM_MC1_CH3_L_INT_POS                    (6U)
#define PWM_MC1_CH3_L_INT_LEN                    (1U)
#define PWM_MC1_CH3_L_INT_MSK                    (((1U<<PWM_MC1_CH3_L_INT_LEN)-1)<<PWM_MC1_CH3_L_INT_POS)
#define PWM_MC1_CH3_L_INT_UMSK                   (~(((1U<<PWM_MC1_CH3_L_INT_LEN)-1)<<PWM_MC1_CH3_L_INT_POS))
#define PWM_MC1_CH3_H_INT                        PWM_MC1_CH3_H_INT
#define PWM_MC1_CH3_H_INT_POS                    (7U)
#define PWM_MC1_CH3_H_INT_LEN                    (1U)
#define PWM_MC1_CH3_H_INT_MSK                    (((1U<<PWM_MC1_CH3_H_INT_LEN)-1)<<PWM_MC1_CH3_H_INT_POS)
#define PWM_MC1_CH3_H_INT_UMSK                   (~(((1U<<PWM_MC1_CH3_H_INT_LEN)-1)<<PWM_MC1_CH3_H_INT_POS))
#define PWM_MC1_PRDE_INT                         PWM_MC1_PRDE_INT
#define PWM_MC1_PRDE_INT_POS                     (8U)
#define PWM_MC1_PRDE_INT_LEN                     (1U)
#define PWM_MC1_PRDE_INT_MSK                     (((1U<<PWM_MC1_PRDE_INT_LEN)-1)<<PWM_MC1_PRDE_INT_POS)
#define PWM_MC1_PRDE_INT_UMSK                    (~(((1U<<PWM_MC1_PRDE_INT_LEN)-1)<<PWM_MC1_PRDE_INT_POS))
#define PWM_MC1_BRK_INT                          PWM_MC1_BRK_INT
#define PWM_MC1_BRK_INT_POS                      (9U)
#define PWM_MC1_BRK_INT_LEN                      (1U)
#define PWM_MC1_BRK_INT_MSK                      (((1U<<PWM_MC1_BRK_INT_LEN)-1)<<PWM_MC1_BRK_INT_POS)
#define PWM_MC1_BRK_INT_UMSK                     (~(((1U<<PWM_MC1_BRK_INT_LEN)-1)<<PWM_MC1_BRK_INT_POS))
#define PWM_MC1_REPT_INT                         PWM_MC1_REPT_INT
#define PWM_MC1_REPT_INT_POS                     (10U)
#define PWM_MC1_REPT_INT_LEN                     (1U)
#define PWM_MC1_REPT_INT_MSK                     (((1U<<PWM_MC1_REPT_INT_LEN)-1)<<PWM_MC1_REPT_INT_POS)
#define PWM_MC1_REPT_INT_UMSK                    (~(((1U<<PWM_MC1_REPT_INT_LEN)-1)<<PWM_MC1_REPT_INT_POS))

/* 0xa4 : pwm_mc1_int_mask */
#define PWM_MC1_INT_MASK_OFFSET                  (0xa4)
#define PWM_MC1_CH0_L_MASK                       PWM_MC1_CH0_L_MASK
#define PWM_MC1_CH0_L_MASK_POS                   (0U)
#define PWM_MC1_CH0_L_MASK_LEN                   (1U)
#define PWM_MC1_CH0_L_MASK_MSK                   (((1U<<PWM_MC1_CH0_L_MASK_LEN)-1)<<PWM_MC1_CH0_L_MASK_POS)
#define PWM_MC1_CH0_L_MASK_UMSK                  (~(((1U<<PWM_MC1_CH0_L_MASK_LEN)-1)<<PWM_MC1_CH0_L_MASK_POS))
#define PWM_MC1_CH0_H_MASK                       PWM_MC1_CH0_H_MASK
#define PWM_MC1_CH0_H_MASK_POS                   (1U)
#define PWM_MC1_CH0_H_MASK_LEN                   (1U)
#define PWM_MC1_CH0_H_MASK_MSK                   (((1U<<PWM_MC1_CH0_H_MASK_LEN)-1)<<PWM_MC1_CH0_H_MASK_POS)
#define PWM_MC1_CH0_H_MASK_UMSK                  (~(((1U<<PWM_MC1_CH0_H_MASK_LEN)-1)<<PWM_MC1_CH0_H_MASK_POS))
#define PWM_MC1_CH1_L_MASK                       PWM_MC1_CH1_L_MASK
#define PWM_MC1_CH1_L_MASK_POS                   (2U)
#define PWM_MC1_CH1_L_MASK_LEN                   (1U)
#define PWM_MC1_CH1_L_MASK_MSK                   (((1U<<PWM_MC1_CH1_L_MASK_LEN)-1)<<PWM_MC1_CH1_L_MASK_POS)
#define PWM_MC1_CH1_L_MASK_UMSK                  (~(((1U<<PWM_MC1_CH1_L_MASK_LEN)-1)<<PWM_MC1_CH1_L_MASK_POS))
#define PWM_MC1_CH1_H_MASK                       PWM_MC1_CH1_H_MASK
#define PWM_MC1_CH1_H_MASK_POS                   (3U)
#define PWM_MC1_CH1_H_MASK_LEN                   (1U)
#define PWM_MC1_CH1_H_MASK_MSK                   (((1U<<PWM_MC1_CH1_H_MASK_LEN)-1)<<PWM_MC1_CH1_H_MASK_POS)
#define PWM_MC1_CH1_H_MASK_UMSK                  (~(((1U<<PWM_MC1_CH1_H_MASK_LEN)-1)<<PWM_MC1_CH1_H_MASK_POS))
#define PWM_MC1_CH2_L_MASK                       PWM_MC1_CH2_L_MASK
#define PWM_MC1_CH2_L_MASK_POS                   (4U)
#define PWM_MC1_CH2_L_MASK_LEN                   (1U)
#define PWM_MC1_CH2_L_MASK_MSK                   (((1U<<PWM_MC1_CH2_L_MASK_LEN)-1)<<PWM_MC1_CH2_L_MASK_POS)
#define PWM_MC1_CH2_L_MASK_UMSK                  (~(((1U<<PWM_MC1_CH2_L_MASK_LEN)-1)<<PWM_MC1_CH2_L_MASK_POS))
#define PWM_MC1_CH2_H_MASK                       PWM_MC1_CH2_H_MASK
#define PWM_MC1_CH2_H_MASK_POS                   (5U)
#define PWM_MC1_CH2_H_MASK_LEN                   (1U)
#define PWM_MC1_CH2_H_MASK_MSK                   (((1U<<PWM_MC1_CH2_H_MASK_LEN)-1)<<PWM_MC1_CH2_H_MASK_POS)
#define PWM_MC1_CH2_H_MASK_UMSK                  (~(((1U<<PWM_MC1_CH2_H_MASK_LEN)-1)<<PWM_MC1_CH2_H_MASK_POS))
#define PWM_MC1_CH3_L_MASK                       PWM_MC1_CH3_L_MASK
#define PWM_MC1_CH3_L_MASK_POS                   (6U)
#define PWM_MC1_CH3_L_MASK_LEN                   (1U)
#define PWM_MC1_CH3_L_MASK_MSK                   (((1U<<PWM_MC1_CH3_L_MASK_LEN)-1)<<PWM_MC1_CH3_L_MASK_POS)
#define PWM_MC1_CH3_L_MASK_UMSK                  (~(((1U<<PWM_MC1_CH3_L_MASK_LEN)-1)<<PWM_MC1_CH3_L_MASK_POS))
#define PWM_MC1_CH3_H_MASK                       PWM_MC1_CH3_H_MASK
#define PWM_MC1_CH3_H_MASK_POS                   (7U)
#define PWM_MC1_CH3_H_MASK_LEN                   (1U)
#define PWM_MC1_CH3_H_MASK_MSK                   (((1U<<PWM_MC1_CH3_H_MASK_LEN)-1)<<PWM_MC1_CH3_H_MASK_POS)
#define PWM_MC1_CH3_H_MASK_UMSK                  (~(((1U<<PWM_MC1_CH3_H_MASK_LEN)-1)<<PWM_MC1_CH3_H_MASK_POS))
#define PWM_MC1_PRDE_MASK                        PWM_MC1_PRDE_MASK
#define PWM_MC1_PRDE_MASK_POS                    (8U)
#define PWM_MC1_PRDE_MASK_LEN                    (1U)
#define PWM_MC1_PRDE_MASK_MSK                    (((1U<<PWM_MC1_PRDE_MASK_LEN)-1)<<PWM_MC1_PRDE_MASK_POS)
#define PWM_MC1_PRDE_MASK_UMSK                   (~(((1U<<PWM_MC1_PRDE_MASK_LEN)-1)<<PWM_MC1_PRDE_MASK_POS))
#define PWM_MC1_BRK_MASK                         PWM_MC1_BRK_MASK
#define PWM_MC1_BRK_MASK_POS                     (9U)
#define PWM_MC1_BRK_MASK_LEN                     (1U)
#define PWM_MC1_BRK_MASK_MSK                     (((1U<<PWM_MC1_BRK_MASK_LEN)-1)<<PWM_MC1_BRK_MASK_POS)
#define PWM_MC1_BRK_MASK_UMSK                    (~(((1U<<PWM_MC1_BRK_MASK_LEN)-1)<<PWM_MC1_BRK_MASK_POS))
#define PWM_MC1_REPT_MASK                        PWM_MC1_REPT_MASK
#define PWM_MC1_REPT_MASK_POS                    (10U)
#define PWM_MC1_REPT_MASK_LEN                    (1U)
#define PWM_MC1_REPT_MASK_MSK                    (((1U<<PWM_MC1_REPT_MASK_LEN)-1)<<PWM_MC1_REPT_MASK_POS)
#define PWM_MC1_REPT_MASK_UMSK                   (~(((1U<<PWM_MC1_REPT_MASK_LEN)-1)<<PWM_MC1_REPT_MASK_POS))

/* 0xa8 : pwm_mc1_int_clear */
#define PWM_MC1_INT_CLEAR_OFFSET                 (0xa8)
#define PWM_MC1_CH0_L_CLR                        PWM_MC1_CH0_L_CLR
#define PWM_MC1_CH0_L_CLR_POS                    (0U)
#define PWM_MC1_CH0_L_CLR_LEN                    (1U)
#define PWM_MC1_CH0_L_CLR_MSK                    (((1U<<PWM_MC1_CH0_L_CLR_LEN)-1)<<PWM_MC1_CH0_L_CLR_POS)
#define PWM_MC1_CH0_L_CLR_UMSK                   (~(((1U<<PWM_MC1_CH0_L_CLR_LEN)-1)<<PWM_MC1_CH0_L_CLR_POS))
#define PWM_MC1_CH0_H_CLR                        PWM_MC1_CH0_H_CLR
#define PWM_MC1_CH0_H_CLR_POS                    (1U)
#define PWM_MC1_CH0_H_CLR_LEN                    (1U)
#define PWM_MC1_CH0_H_CLR_MSK                    (((1U<<PWM_MC1_CH0_H_CLR_LEN)-1)<<PWM_MC1_CH0_H_CLR_POS)
#define PWM_MC1_CH0_H_CLR_UMSK                   (~(((1U<<PWM_MC1_CH0_H_CLR_LEN)-1)<<PWM_MC1_CH0_H_CLR_POS))
#define PWM_MC1_CH1_L_CLR                        PWM_MC1_CH1_L_CLR
#define PWM_MC1_CH1_L_CLR_POS                    (2U)
#define PWM_MC1_CH1_L_CLR_LEN                    (1U)
#define PWM_MC1_CH1_L_CLR_MSK                    (((1U<<PWM_MC1_CH1_L_CLR_LEN)-1)<<PWM_MC1_CH1_L_CLR_POS)
#define PWM_MC1_CH1_L_CLR_UMSK                   (~(((1U<<PWM_MC1_CH1_L_CLR_LEN)-1)<<PWM_MC1_CH1_L_CLR_POS))
#define PWM_MC1_CH1_H_CLR                        PWM_MC1_CH1_H_CLR
#define PWM_MC1_CH1_H_CLR_POS                    (3U)
#define PWM_MC1_CH1_H_CLR_LEN                    (1U)
#define PWM_MC1_CH1_H_CLR_MSK                    (((1U<<PWM_MC1_CH1_H_CLR_LEN)-1)<<PWM_MC1_CH1_H_CLR_POS)
#define PWM_MC1_CH1_H_CLR_UMSK                   (~(((1U<<PWM_MC1_CH1_H_CLR_LEN)-1)<<PWM_MC1_CH1_H_CLR_POS))
#define PWM_MC1_CH2_L_CLR                        PWM_MC1_CH2_L_CLR
#define PWM_MC1_CH2_L_CLR_POS                    (4U)
#define PWM_MC1_CH2_L_CLR_LEN                    (1U)
#define PWM_MC1_CH2_L_CLR_MSK                    (((1U<<PWM_MC1_CH2_L_CLR_LEN)-1)<<PWM_MC1_CH2_L_CLR_POS)
#define PWM_MC1_CH2_L_CLR_UMSK                   (~(((1U<<PWM_MC1_CH2_L_CLR_LEN)-1)<<PWM_MC1_CH2_L_CLR_POS))
#define PWM_MC1_CH2_H_CLR                        PWM_MC1_CH2_H_CLR
#define PWM_MC1_CH2_H_CLR_POS                    (5U)
#define PWM_MC1_CH2_H_CLR_LEN                    (1U)
#define PWM_MC1_CH2_H_CLR_MSK                    (((1U<<PWM_MC1_CH2_H_CLR_LEN)-1)<<PWM_MC1_CH2_H_CLR_POS)
#define PWM_MC1_CH2_H_CLR_UMSK                   (~(((1U<<PWM_MC1_CH2_H_CLR_LEN)-1)<<PWM_MC1_CH2_H_CLR_POS))
#define PWM_MC1_CH3_L_CLR                        PWM_MC1_CH3_L_CLR
#define PWM_MC1_CH3_L_CLR_POS                    (6U)
#define PWM_MC1_CH3_L_CLR_LEN                    (1U)
#define PWM_MC1_CH3_L_CLR_MSK                    (((1U<<PWM_MC1_CH3_L_CLR_LEN)-1)<<PWM_MC1_CH3_L_CLR_POS)
#define PWM_MC1_CH3_L_CLR_UMSK                   (~(((1U<<PWM_MC1_CH3_L_CLR_LEN)-1)<<PWM_MC1_CH3_L_CLR_POS))
#define PWM_MC1_CH3_H_CLR                        PWM_MC1_CH3_H_CLR
#define PWM_MC1_CH3_H_CLR_POS                    (7U)
#define PWM_MC1_CH3_H_CLR_LEN                    (1U)
#define PWM_MC1_CH3_H_CLR_MSK                    (((1U<<PWM_MC1_CH3_H_CLR_LEN)-1)<<PWM_MC1_CH3_H_CLR_POS)
#define PWM_MC1_CH3_H_CLR_UMSK                   (~(((1U<<PWM_MC1_CH3_H_CLR_LEN)-1)<<PWM_MC1_CH3_H_CLR_POS))
#define PWM_MC1_PRDE_CLR                         PWM_MC1_PRDE_CLR
#define PWM_MC1_PRDE_CLR_POS                     (8U)
#define PWM_MC1_PRDE_CLR_LEN                     (1U)
#define PWM_MC1_PRDE_CLR_MSK                     (((1U<<PWM_MC1_PRDE_CLR_LEN)-1)<<PWM_MC1_PRDE_CLR_POS)
#define PWM_MC1_PRDE_CLR_UMSK                    (~(((1U<<PWM_MC1_PRDE_CLR_LEN)-1)<<PWM_MC1_PRDE_CLR_POS))
#define PWM_MC1_BRK_CLR                          PWM_MC1_BRK_CLR
#define PWM_MC1_BRK_CLR_POS                      (9U)
#define PWM_MC1_BRK_CLR_LEN                      (1U)
#define PWM_MC1_BRK_CLR_MSK                      (((1U<<PWM_MC1_BRK_CLR_LEN)-1)<<PWM_MC1_BRK_CLR_POS)
#define PWM_MC1_BRK_CLR_UMSK                     (~(((1U<<PWM_MC1_BRK_CLR_LEN)-1)<<PWM_MC1_BRK_CLR_POS))
#define PWM_MC1_REPT_CLR                         PWM_MC1_REPT_CLR
#define PWM_MC1_REPT_CLR_POS                     (10U)
#define PWM_MC1_REPT_CLR_LEN                     (1U)
#define PWM_MC1_REPT_CLR_MSK                     (((1U<<PWM_MC1_REPT_CLR_LEN)-1)<<PWM_MC1_REPT_CLR_POS)
#define PWM_MC1_REPT_CLR_UMSK                    (~(((1U<<PWM_MC1_REPT_CLR_LEN)-1)<<PWM_MC1_REPT_CLR_POS))

/* 0xac : pwm_mc1_int_en */
#define PWM_MC1_INT_EN_OFFSET                    (0xac)
#define PWM_MC1_CH0_L_EN                         PWM_MC1_CH0_L_EN
#define PWM_MC1_CH0_L_EN_POS                     (0U)
#define PWM_MC1_CH0_L_EN_LEN                     (1U)
#define PWM_MC1_CH0_L_EN_MSK                     (((1U<<PWM_MC1_CH0_L_EN_LEN)-1)<<PWM_MC1_CH0_L_EN_POS)
#define PWM_MC1_CH0_L_EN_UMSK                    (~(((1U<<PWM_MC1_CH0_L_EN_LEN)-1)<<PWM_MC1_CH0_L_EN_POS))
#define PWM_MC1_CH0_H_EN                         PWM_MC1_CH0_H_EN
#define PWM_MC1_CH0_H_EN_POS                     (1U)
#define PWM_MC1_CH0_H_EN_LEN                     (1U)
#define PWM_MC1_CH0_H_EN_MSK                     (((1U<<PWM_MC1_CH0_H_EN_LEN)-1)<<PWM_MC1_CH0_H_EN_POS)
#define PWM_MC1_CH0_H_EN_UMSK                    (~(((1U<<PWM_MC1_CH0_H_EN_LEN)-1)<<PWM_MC1_CH0_H_EN_POS))
#define PWM_MC1_CH1_L_EN                         PWM_MC1_CH1_L_EN
#define PWM_MC1_CH1_L_EN_POS                     (2U)
#define PWM_MC1_CH1_L_EN_LEN                     (1U)
#define PWM_MC1_CH1_L_EN_MSK                     (((1U<<PWM_MC1_CH1_L_EN_LEN)-1)<<PWM_MC1_CH1_L_EN_POS)
#define PWM_MC1_CH1_L_EN_UMSK                    (~(((1U<<PWM_MC1_CH1_L_EN_LEN)-1)<<PWM_MC1_CH1_L_EN_POS))
#define PWM_MC1_CH1_H_EN                         PWM_MC1_CH1_H_EN
#define PWM_MC1_CH1_H_EN_POS                     (3U)
#define PWM_MC1_CH1_H_EN_LEN                     (1U)
#define PWM_MC1_CH1_H_EN_MSK                     (((1U<<PWM_MC1_CH1_H_EN_LEN)-1)<<PWM_MC1_CH1_H_EN_POS)
#define PWM_MC1_CH1_H_EN_UMSK                    (~(((1U<<PWM_MC1_CH1_H_EN_LEN)-1)<<PWM_MC1_CH1_H_EN_POS))
#define PWM_MC1_CH2_L_EN                         PWM_MC1_CH2_L_EN
#define PWM_MC1_CH2_L_EN_POS                     (4U)
#define PWM_MC1_CH2_L_EN_LEN                     (1U)
#define PWM_MC1_CH2_L_EN_MSK                     (((1U<<PWM_MC1_CH2_L_EN_LEN)-1)<<PWM_MC1_CH2_L_EN_POS)
#define PWM_MC1_CH2_L_EN_UMSK                    (~(((1U<<PWM_MC1_CH2_L_EN_LEN)-1)<<PWM_MC1_CH2_L_EN_POS))
#define PWM_MC1_CH2_H_EN                         PWM_MC1_CH2_H_EN
#define PWM_MC1_CH2_H_EN_POS                     (5U)
#define PWM_MC1_CH2_H_EN_LEN                     (1U)
#define PWM_MC1_CH2_H_EN_MSK                     (((1U<<PWM_MC1_CH2_H_EN_LEN)-1)<<PWM_MC1_CH2_H_EN_POS)
#define PWM_MC1_CH2_H_EN_UMSK                    (~(((1U<<PWM_MC1_CH2_H_EN_LEN)-1)<<PWM_MC1_CH2_H_EN_POS))
#define PWM_MC1_CH3_L_EN                         PWM_MC1_CH3_L_EN
#define PWM_MC1_CH3_L_EN_POS                     (6U)
#define PWM_MC1_CH3_L_EN_LEN                     (1U)
#define PWM_MC1_CH3_L_EN_MSK                     (((1U<<PWM_MC1_CH3_L_EN_LEN)-1)<<PWM_MC1_CH3_L_EN_POS)
#define PWM_MC1_CH3_L_EN_UMSK                    (~(((1U<<PWM_MC1_CH3_L_EN_LEN)-1)<<PWM_MC1_CH3_L_EN_POS))
#define PWM_MC1_CH3_H_EN                         PWM_MC1_CH3_H_EN
#define PWM_MC1_CH3_H_EN_POS                     (7U)
#define PWM_MC1_CH3_H_EN_LEN                     (1U)
#define PWM_MC1_CH3_H_EN_MSK                     (((1U<<PWM_MC1_CH3_H_EN_LEN)-1)<<PWM_MC1_CH3_H_EN_POS)
#define PWM_MC1_CH3_H_EN_UMSK                    (~(((1U<<PWM_MC1_CH3_H_EN_LEN)-1)<<PWM_MC1_CH3_H_EN_POS))
#define PWM_MC1_PRDE_EN                          PWM_MC1_PRDE_EN
#define PWM_MC1_PRDE_EN_POS                      (8U)
#define PWM_MC1_PRDE_EN_LEN                      (1U)
#define PWM_MC1_PRDE_EN_MSK                      (((1U<<PWM_MC1_PRDE_EN_LEN)-1)<<PWM_MC1_PRDE_EN_POS)
#define PWM_MC1_PRDE_EN_UMSK                     (~(((1U<<PWM_MC1_PRDE_EN_LEN)-1)<<PWM_MC1_PRDE_EN_POS))
#define PWM_MC1_BRK_EN                           PWM_MC1_BRK_EN
#define PWM_MC1_BRK_EN_POS                       (9U)
#define PWM_MC1_BRK_EN_LEN                       (1U)
#define PWM_MC1_BRK_EN_MSK                       (((1U<<PWM_MC1_BRK_EN_LEN)-1)<<PWM_MC1_BRK_EN_POS)
#define PWM_MC1_BRK_EN_UMSK                      (~(((1U<<PWM_MC1_BRK_EN_LEN)-1)<<PWM_MC1_BRK_EN_POS))
#define PWM_MC1_REPT_EN                          PWM_MC1_REPT_EN
#define PWM_MC1_REPT_EN_POS                      (10U)
#define PWM_MC1_REPT_EN_LEN                      (1U)
#define PWM_MC1_REPT_EN_MSK                      (((1U<<PWM_MC1_REPT_EN_LEN)-1)<<PWM_MC1_REPT_EN_POS)
#define PWM_MC1_REPT_EN_UMSK                     (~(((1U<<PWM_MC1_REPT_EN_LEN)-1)<<PWM_MC1_REPT_EN_POS))

 struct pwm_reg {

    /* 0x0 : pwm_int_config */
    union {
        struct {
            uint32_t pwm0_int_sts                   :  1; /* [    0],         r,       0x0 */
            uint32_t pwm1_int_sts                   :  1; /* [    1],         r,       0x0 */
            uint32_t pwm_reserved0_7_2              :  6; /* [ 7: 2],      rsvd,       0x0 */
            uint32_t pwm0_int_clr                   :  1; /* [    8],       w1c,       0x0 */
            uint32_t pwm1_int_clr                   :  1; /* [    9],       w1c,       0x0 */
            uint32_t pwm_reserved0_31_10            : 22; /* [31:10],      rsvd,       0x0 */
        };
    };

    /* 0x4 : reserved */
    uint8_t pwm_reserved4[60];

    /* 0x40 : pwm_mc0_config0 */
    union {
        struct {
            uint32_t pwm_mc0_clk_div                : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_reserved64_18_16           :  3; /* [18:16],      rsvd,       0x0 */
            uint32_t pwm_mc0_stop_on_rept           :  1; /* [   19],       r/w,       0x0 */
            uint32_t pwm_mc0_adc_trg_src            :  4; /* [23:20],       r/w,       0xf */
            uint32_t pwm_mc0_sw_break_en            :  1; /* [   24],       r/w,       0x0 */
            uint32_t pwm_mc0_ext_break_en           :  1; /* [   25],       r/w,       0x0 */
            uint32_t pwm_mc0_ext_break_pl           :  1; /* [   26],       r/w,       0x0 */
            uint32_t pwm_mc0_stop_en                :  1; /* [   27],       r/w,       0x0 */
            uint32_t pwm_mc0_stop_mode              :  1; /* [   28],       r/w,       0x1 */
            uint32_t pwm_mc0_sts_stop               :  1; /* [   29],         r,       0x0 */
            uint32_t pwm_mc0_reg_clk_sel            :  2; /* [31:30],       r/w,       0x0 */
        };
    };

    /* 0x44 : pwm_mc0_config1 */
    union {
        struct {
            uint32_t pwm_mc0_ch0_pen                :  1; /* [    0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch0_psi                :  1; /* [    1],       r/w,       0x0 */
            uint32_t pwm_mc0_ch0_nen                :  1; /* [    2],       r/w,       0x0 */
            uint32_t pwm_mc0_ch0_nsi                :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_pen                :  1; /* [    4],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_psi                :  1; /* [    5],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_nen                :  1; /* [    6],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_nsi                :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_pen                :  1; /* [    8],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_psi                :  1; /* [    9],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_nen                :  1; /* [   10],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_nsi                :  1; /* [   11],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_pen                :  1; /* [   12],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_psi                :  1; /* [   13],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_nen                :  1; /* [   14],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_nsi                :  1; /* [   15],       r/w,       0x1 */
            uint32_t pwm_mc0_ch0_ppl                :  1; /* [   16],       r/w,       0x1 */
            uint32_t pwm_mc0_ch0_npl                :  1; /* [   17],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_ppl                :  1; /* [   18],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_npl                :  1; /* [   19],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_ppl                :  1; /* [   20],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_npl                :  1; /* [   21],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_ppl                :  1; /* [   22],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_npl                :  1; /* [   23],       r/w,       0x1 */
            uint32_t pwm_mc0_ch0_pbs                :  1; /* [   24],       r/w,       0x0 */
            uint32_t pwm_mc0_ch0_nbs                :  1; /* [   25],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_pbs                :  1; /* [   26],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_nbs                :  1; /* [   27],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_pbs                :  1; /* [   28],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_nbs                :  1; /* [   29],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_pbs                :  1; /* [   30],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_nbs                :  1; /* [   31],       r/w,       0x0 */
        };
    };

    /* 0x48 : pwm_mc0_period */
    union {
        struct {
            uint32_t pwm_mc0_period                 : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_int_period_cnt         : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x4c : pwm_mc0_dead_time */
    union {
        struct {
            uint32_t pwm_mc0_ch0_dtg                :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_dtg                :  8; /* [15: 8],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_dtg                :  8; /* [23:16],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_dtg                :  8; /* [31:24],       r/w,       0x0 */
        };
    };

    /* 0x50 : pwm_mc0_ch0_thre */
    union {
        struct {
            uint32_t pwm_mc0_ch0_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch0_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x54 : pwm_mc0_ch1_thre */
    union {
        struct {
            uint32_t pwm_mc0_ch1_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch1_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x58 : pwm_mc0_ch2_thre */
    union {
        struct {
            uint32_t pwm_mc0_ch2_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch2_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x5c : pwm_mc0_ch3_thre */
    union {
        struct {
            uint32_t pwm_mc0_ch3_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc0_ch3_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x60 : pwm_mc0_int_sts */
    union {
        struct {
            uint32_t pwm_mc0_ch0_l_int              :  1; /* [    0],         r,       0x0 */
            uint32_t pwm_mc0_ch0_h_int              :  1; /* [    1],         r,       0x0 */
            uint32_t pwm_mc0_ch1_l_int              :  1; /* [    2],         r,       0x0 */
            uint32_t pwm_mc0_ch1_h_int              :  1; /* [    3],         r,       0x0 */
            uint32_t pwm_mc0_ch2_l_int              :  1; /* [    4],         r,       0x0 */
            uint32_t pwm_mc0_ch2_h_int              :  1; /* [    5],         r,       0x0 */
            uint32_t pwm_mc0_ch3_l_int              :  1; /* [    6],         r,       0x0 */
            uint32_t pwm_mc0_ch3_h_int              :  1; /* [    7],         r,       0x0 */
            uint32_t pwm_mc0_prde_int               :  1; /* [    8],         r,       0x0 */
            uint32_t pwm_mc0_brk_int                :  1; /* [    9],         r,       0x0 */
            uint32_t pwm_mc0_rept_int               :  1; /* [   10],         r,       0x0 */
            uint32_t pwm_reserved96_31_11           : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0x64 : pwm_mc0_int_mask */
    union {
        struct {
            uint32_t pwm_mc0_ch0_l_mask             :  1; /* [    0],       r/w,       0x1 */
            uint32_t pwm_mc0_ch0_h_mask             :  1; /* [    1],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_l_mask             :  1; /* [    2],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_h_mask             :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_l_mask             :  1; /* [    4],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_h_mask             :  1; /* [    5],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_l_mask             :  1; /* [    6],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_h_mask             :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc0_prde_mask              :  1; /* [    8],       r/w,       0x1 */
            uint32_t pwm_mc0_brk_mask               :  1; /* [    9],       r/w,       0x1 */
            uint32_t pwm_mc0_rept_mask              :  1; /* [   10],       r/w,       0x1 */
            uint32_t pwm_reserved100_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0x68 : pwm_mc0_int_clear */
    union {
        struct {
            uint32_t pwm_mc0_ch0_l_clr              :  1; /* [    0],       w1c,       0x0 */
            uint32_t pwm_mc0_ch0_h_clr              :  1; /* [    1],       w1c,       0x0 */
            uint32_t pwm_mc0_ch1_l_clr              :  1; /* [    2],       w1c,       0x0 */
            uint32_t pwm_mc0_ch1_h_clr              :  1; /* [    3],       w1c,       0x0 */
            uint32_t pwm_mc0_ch2_l_clr              :  1; /* [    4],       w1c,       0x0 */
            uint32_t pwm_mc0_ch2_h_clr              :  1; /* [    5],       w1c,       0x0 */
            uint32_t pwm_mc0_ch3_l_clr              :  1; /* [    6],       w1c,       0x0 */
            uint32_t pwm_mc0_ch3_h_clr              :  1; /* [    7],       w1c,       0x0 */
            uint32_t pwm_mc0_prde_clr               :  1; /* [    8],       w1c,       0x0 */
            uint32_t pwm_mc0_brk_clr                :  1; /* [    9],       w1c,       0x0 */
            uint32_t pwm_mc0_rept_clr               :  1; /* [   10],       w1c,       0x0 */
            uint32_t pwm_reserved104_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0x6c : pwm_mc0_int_en */
    union {
        struct {
            uint32_t pwm_mc0_ch0_l_en               :  1; /* [    0],       r/w,       0x1 */
            uint32_t pwm_mc0_ch0_h_en               :  1; /* [    1],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_l_en               :  1; /* [    2],       r/w,       0x1 */
            uint32_t pwm_mc0_ch1_h_en               :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_l_en               :  1; /* [    4],       r/w,       0x1 */
            uint32_t pwm_mc0_ch2_h_en               :  1; /* [    5],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_l_en               :  1; /* [    6],       r/w,       0x1 */
            uint32_t pwm_mc0_ch3_h_en               :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc0_prde_en                :  1; /* [    8],       r/w,       0x1 */
            uint32_t pwm_mc0_brk_en                 :  1; /* [    9],       r/w,       0x1 */
            uint32_t pwm_mc0_rept_en                :  1; /* [   10],       r/w,       0x1 */
            uint32_t pwm_reserved108_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0x70 : reserved */
    uint8_t pwm_reserved112[16];

    /* 0x80 : pwm_mc1_config0 */
    union {
        struct {
            uint32_t pwm_mc1_clk_div                : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_reserved128_18_16          :  3; /* [18:16],      rsvd,       0x0 */
            uint32_t pwm_mc1_stop_on_rept           :  1; /* [   19],       r/w,       0x0 */
            uint32_t pwm_mc1_adc_trg_src            :  4; /* [23:20],       r/w,       0xf */
            uint32_t pwm_mc1_sw_break_en            :  1; /* [   24],       r/w,       0x0 */
            uint32_t pwm_mc1_ext_break_en           :  1; /* [   25],       r/w,       0x0 */
            uint32_t pwm_mc1_ext_break_pl           :  1; /* [   26],       r/w,       0x0 */
            uint32_t pwm_mc1_stop_en                :  1; /* [   27],       r/w,       0x0 */
            uint32_t pwm_mc1_stop_mode              :  1; /* [   28],       r/w,       0x1 */
            uint32_t pwm_mc1_sts_stop               :  1; /* [   29],         r,       0x0 */
            uint32_t pwm_mc1_reg_clk_sel            :  2; /* [31:30],       r/w,       0x0 */
        };
    };

    /* 0x84 : pwm_mc1_config1 */
    union {
        struct {
            uint32_t pwm_mc1_ch0_pen                :  1; /* [    0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch0_psi                :  1; /* [    1],       r/w,       0x0 */
            uint32_t pwm_mc1_ch0_nen                :  1; /* [    2],       r/w,       0x0 */
            uint32_t pwm_mc1_ch0_nsi                :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_pen                :  1; /* [    4],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_psi                :  1; /* [    5],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_nen                :  1; /* [    6],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_nsi                :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_pen                :  1; /* [    8],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_psi                :  1; /* [    9],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_nen                :  1; /* [   10],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_nsi                :  1; /* [   11],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_pen                :  1; /* [   12],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_psi                :  1; /* [   13],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_nen                :  1; /* [   14],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_nsi                :  1; /* [   15],       r/w,       0x1 */
            uint32_t pwm_mc1_ch0_ppl                :  1; /* [   16],       r/w,       0x1 */
            uint32_t pwm_mc1_ch0_npl                :  1; /* [   17],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_ppl                :  1; /* [   18],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_npl                :  1; /* [   19],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_ppl                :  1; /* [   20],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_npl                :  1; /* [   21],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_ppl                :  1; /* [   22],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_npl                :  1; /* [   23],       r/w,       0x1 */
            uint32_t pwm_mc1_ch0_pbs                :  1; /* [   24],       r/w,       0x0 */
            uint32_t pwm_mc1_ch0_nbs                :  1; /* [   25],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_pbs                :  1; /* [   26],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_nbs                :  1; /* [   27],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_pbs                :  1; /* [   28],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_nbs                :  1; /* [   29],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_pbs                :  1; /* [   30],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_nbs                :  1; /* [   31],       r/w,       0x0 */
        };
    };

    /* 0x88 : pwm_mc1_period */
    union {
        struct {
            uint32_t pwm_mc1_period                 : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_int_period_cnt         : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x8c : pwm_mc1_dead_time */
    union {
        struct {
            uint32_t pwm_mc1_ch0_dtg                :  8; /* [ 7: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_dtg                :  8; /* [15: 8],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_dtg                :  8; /* [23:16],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_dtg                :  8; /* [31:24],       r/w,       0x0 */
        };
    };

    /* 0x90 : pwm_mc1_ch0_thre */
    union {
        struct {
            uint32_t pwm_mc1_ch0_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch0_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x94 : pwm_mc1_ch1_thre */
    union {
        struct {
            uint32_t pwm_mc1_ch1_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch1_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x98 : pwm_mc1_ch2_thre */
    union {
        struct {
            uint32_t pwm_mc1_ch2_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch2_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0x9c : pwm_mc1_ch3_thre */
    union {
        struct {
            uint32_t pwm_mc1_ch3_threl              : 16; /* [15: 0],       r/w,       0x0 */
            uint32_t pwm_mc1_ch3_threh              : 16; /* [31:16],       r/w,       0x0 */
        };
    };

    /* 0xa0 : pwm_mc1_int_sts */
    union {
        struct {
            uint32_t pwm_mc1_ch0_l_int              :  1; /* [    0],         r,       0x0 */
            uint32_t pwm_mc1_ch0_h_int              :  1; /* [    1],         r,       0x0 */
            uint32_t pwm_mc1_ch1_l_int              :  1; /* [    2],         r,       0x0 */
            uint32_t pwm_mc1_ch1_h_int              :  1; /* [    3],         r,       0x0 */
            uint32_t pwm_mc1_ch2_l_int              :  1; /* [    4],         r,       0x0 */
            uint32_t pwm_mc1_ch2_h_int              :  1; /* [    5],         r,       0x0 */
            uint32_t pwm_mc1_ch3_l_int              :  1; /* [    6],         r,       0x0 */
            uint32_t pwm_mc1_ch3_h_int              :  1; /* [    7],         r,       0x0 */
            uint32_t pwm_mc1_prde_int               :  1; /* [    8],         r,       0x0 */
            uint32_t pwm_mc1_brk_int                :  1; /* [    9],         r,       0x0 */
            uint32_t pwm_mc1_rept_int               :  1; /* [   10],         r,       0x0 */
            uint32_t pwm_reserved160_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0xa4 : pwm_mc1_int_mask */
    union {
        struct {
            uint32_t pwm_mc1_ch0_l_mask             :  1; /* [    0],       r/w,       0x1 */
            uint32_t pwm_mc1_ch0_h_mask             :  1; /* [    1],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_l_mask             :  1; /* [    2],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_h_mask             :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_l_mask             :  1; /* [    4],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_h_mask             :  1; /* [    5],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_l_mask             :  1; /* [    6],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_h_mask             :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc1_prde_mask              :  1; /* [    8],       r/w,       0x1 */
            uint32_t pwm_mc1_brk_mask               :  1; /* [    9],       r/w,       0x1 */
            uint32_t pwm_mc1_rept_mask              :  1; /* [   10],       r/w,       0x1 */
            uint32_t pwm_reserved164_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0xa8 : pwm_mc1_int_clear */
    union {
        struct {
            uint32_t pwm_mc1_ch0_l_clr              :  1; /* [    0],       w1c,       0x0 */
            uint32_t pwm_mc1_ch0_h_clr              :  1; /* [    1],       w1c,       0x0 */
            uint32_t pwm_mc1_ch1_l_clr              :  1; /* [    2],       w1c,       0x0 */
            uint32_t pwm_mc1_ch1_h_clr              :  1; /* [    3],       w1c,       0x0 */
            uint32_t pwm_mc1_ch2_l_clr              :  1; /* [    4],       w1c,       0x0 */
            uint32_t pwm_mc1_ch2_h_clr              :  1; /* [    5],       w1c,       0x0 */
            uint32_t pwm_mc1_ch3_l_clr              :  1; /* [    6],       w1c,       0x0 */
            uint32_t pwm_mc1_ch3_h_clr              :  1; /* [    7],       w1c,       0x0 */
            uint32_t pwm_mc1_prde_clr               :  1; /* [    8],       w1c,       0x0 */
            uint32_t pwm_mc1_brk_clr                :  1; /* [    9],       w1c,       0x0 */
            uint32_t pwm_mc1_rept_clr               :  1; /* [   10],       w1c,       0x0 */
            uint32_t pwm_reserved168_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };

    /* 0xac : pwm_mc1_int_en */
    union {
        struct {
            uint32_t pwm_mc1_ch0_l_en               :  1; /* [    0],       r/w,       0x1 */
            uint32_t pwm_mc1_ch0_h_en               :  1; /* [    1],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_l_en               :  1; /* [    2],       r/w,       0x1 */
            uint32_t pwm_mc1_ch1_h_en               :  1; /* [    3],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_l_en               :  1; /* [    4],       r/w,       0x1 */
            uint32_t pwm_mc1_ch2_h_en               :  1; /* [    5],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_l_en               :  1; /* [    6],       r/w,       0x1 */
            uint32_t pwm_mc1_ch3_h_en               :  1; /* [    7],       r/w,       0x1 */
            uint32_t pwm_mc1_prde_en                :  1; /* [    8],       r/w,       0x1 */
            uint32_t pwm_mc1_brk_en                 :  1; /* [    9],       r/w,       0x1 */
            uint32_t pwm_mc1_rept_en                :  1; /* [   10],       r/w,       0x1 */
            uint32_t pwm_reserved172_31_11          : 21; /* [31:11],      rsvd,       0x0 */
        };
    };
};

typedef volatile struct pwm_reg pwm_reg_t;

#endif // __PWM_REG_H__
