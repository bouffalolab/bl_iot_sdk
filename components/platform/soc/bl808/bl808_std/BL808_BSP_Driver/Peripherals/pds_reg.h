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
#ifndef  __PDS_REG_H__
#define  __PDS_REG_H__

#include "bl808.h"

/* 0x0 : PDS_CTL */
#define PDS_CTL_OFFSET                                          (0x0)
#define PDS_START_PS                                            PDS_START_PS
#define PDS_START_PS_POS                                        (0U)
#define PDS_START_PS_LEN                                        (1U)
#define PDS_START_PS_MSK                                        (((1U<<PDS_START_PS_LEN)-1)<<PDS_START_PS_POS)
#define PDS_START_PS_UMSK                                       (~(((1U<<PDS_START_PS_LEN)-1)<<PDS_START_PS_POS))
#define PDS_CR_SLEEP_FOREVER                                    PDS_CR_SLEEP_FOREVER
#define PDS_CR_SLEEP_FOREVER_POS                                (1U)
#define PDS_CR_SLEEP_FOREVER_LEN                                (1U)
#define PDS_CR_SLEEP_FOREVER_MSK                                (((1U<<PDS_CR_SLEEP_FOREVER_LEN)-1)<<PDS_CR_SLEEP_FOREVER_POS)
#define PDS_CR_SLEEP_FOREVER_UMSK                               (~(((1U<<PDS_CR_SLEEP_FOREVER_LEN)-1)<<PDS_CR_SLEEP_FOREVER_POS))
#define PDS_CR_XTAL_FORCE_OFF                                   PDS_CR_XTAL_FORCE_OFF
#define PDS_CR_XTAL_FORCE_OFF_POS                               (2U)
#define PDS_CR_XTAL_FORCE_OFF_LEN                               (1U)
#define PDS_CR_XTAL_FORCE_OFF_MSK                               (((1U<<PDS_CR_XTAL_FORCE_OFF_LEN)-1)<<PDS_CR_XTAL_FORCE_OFF_POS)
#define PDS_CR_XTAL_FORCE_OFF_UMSK                              (~(((1U<<PDS_CR_XTAL_FORCE_OFF_LEN)-1)<<PDS_CR_XTAL_FORCE_OFF_POS))
#define PDS_CR_PDS_WIFI_SAVE_STATE                              PDS_CR_PDS_WIFI_SAVE_STATE
#define PDS_CR_PDS_WIFI_SAVE_STATE_POS                          (3U)
#define PDS_CR_PDS_WIFI_SAVE_STATE_LEN                          (1U)
#define PDS_CR_PDS_WIFI_SAVE_STATE_MSK                          (((1U<<PDS_CR_PDS_WIFI_SAVE_STATE_LEN)-1)<<PDS_CR_PDS_WIFI_SAVE_STATE_POS)
#define PDS_CR_PDS_WIFI_SAVE_STATE_UMSK                         (~(((1U<<PDS_CR_PDS_WIFI_SAVE_STATE_LEN)-1)<<PDS_CR_PDS_WIFI_SAVE_STATE_POS))
#define PDS_CR_PDS_PD_DCDC                                      PDS_CR_PDS_PD_DCDC
#define PDS_CR_PDS_PD_DCDC_POS                                  (4U)
#define PDS_CR_PDS_PD_DCDC_LEN                                  (1U)
#define PDS_CR_PDS_PD_DCDC_MSK                                  (((1U<<PDS_CR_PDS_PD_DCDC_LEN)-1)<<PDS_CR_PDS_PD_DCDC_POS)
#define PDS_CR_PDS_PD_DCDC_UMSK                                 (~(((1U<<PDS_CR_PDS_PD_DCDC_LEN)-1)<<PDS_CR_PDS_PD_DCDC_POS))
#define PDS_CR_PDS_PD_BG_SYS                                    PDS_CR_PDS_PD_BG_SYS
#define PDS_CR_PDS_PD_BG_SYS_POS                                (5U)
#define PDS_CR_PDS_PD_BG_SYS_LEN                                (1U)
#define PDS_CR_PDS_PD_BG_SYS_MSK                                (((1U<<PDS_CR_PDS_PD_BG_SYS_LEN)-1)<<PDS_CR_PDS_PD_BG_SYS_POS)
#define PDS_CR_PDS_PD_BG_SYS_UMSK                               (~(((1U<<PDS_CR_PDS_PD_BG_SYS_LEN)-1)<<PDS_CR_PDS_PD_BG_SYS_POS))
#define PDS_CR_PDS_CTRL_GPIO_IE_PU_PD                           PDS_CR_PDS_CTRL_GPIO_IE_PU_PD
#define PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_POS                       (6U)
#define PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_LEN                       (1U)
#define PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_MSK                       (((1U<<PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_LEN)-1)<<PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_POS)
#define PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_UMSK                      (~(((1U<<PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_LEN)-1)<<PDS_CR_PDS_CTRL_GPIO_IE_PU_PD_POS))
#define PDS_CR_PDS_CTRL_PU_FLASH                                PDS_CR_PDS_CTRL_PU_FLASH
#define PDS_CR_PDS_CTRL_PU_FLASH_POS                            (7U)
#define PDS_CR_PDS_CTRL_PU_FLASH_LEN                            (1U)
#define PDS_CR_PDS_CTRL_PU_FLASH_MSK                            (((1U<<PDS_CR_PDS_CTRL_PU_FLASH_LEN)-1)<<PDS_CR_PDS_CTRL_PU_FLASH_POS)
#define PDS_CR_PDS_CTRL_PU_FLASH_UMSK                           (~(((1U<<PDS_CR_PDS_CTRL_PU_FLASH_LEN)-1)<<PDS_CR_PDS_CTRL_PU_FLASH_POS))
#define PDS_CR_PDS_GATE_CLK                                     PDS_CR_PDS_GATE_CLK
#define PDS_CR_PDS_GATE_CLK_POS                                 (8U)
#define PDS_CR_PDS_GATE_CLK_LEN                                 (1U)
#define PDS_CR_PDS_GATE_CLK_MSK                                 (((1U<<PDS_CR_PDS_GATE_CLK_LEN)-1)<<PDS_CR_PDS_GATE_CLK_POS)
#define PDS_CR_PDS_GATE_CLK_UMSK                                (~(((1U<<PDS_CR_PDS_GATE_CLK_LEN)-1)<<PDS_CR_PDS_GATE_CLK_POS))
#define PDS_CR_PDS_MEM_STBY                                     PDS_CR_PDS_MEM_STBY
#define PDS_CR_PDS_MEM_STBY_POS                                 (9U)
#define PDS_CR_PDS_MEM_STBY_LEN                                 (1U)
#define PDS_CR_PDS_MEM_STBY_MSK                                 (((1U<<PDS_CR_PDS_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MEM_STBY_POS)
#define PDS_CR_PDS_MEM_STBY_UMSK                                (~(((1U<<PDS_CR_PDS_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MEM_STBY_POS))
#define PDS_CR_SW_PU_FLASH                                      PDS_CR_SW_PU_FLASH
#define PDS_CR_SW_PU_FLASH_POS                                  (10U)
#define PDS_CR_SW_PU_FLASH_LEN                                  (1U)
#define PDS_CR_SW_PU_FLASH_MSK                                  (((1U<<PDS_CR_SW_PU_FLASH_LEN)-1)<<PDS_CR_SW_PU_FLASH_POS)
#define PDS_CR_SW_PU_FLASH_UMSK                                 (~(((1U<<PDS_CR_SW_PU_FLASH_LEN)-1)<<PDS_CR_SW_PU_FLASH_POS))
#define PDS_CR_PDS_ISO_EN                                       PDS_CR_PDS_ISO_EN
#define PDS_CR_PDS_ISO_EN_POS                                   (11U)
#define PDS_CR_PDS_ISO_EN_LEN                                   (1U)
#define PDS_CR_PDS_ISO_EN_MSK                                   (((1U<<PDS_CR_PDS_ISO_EN_LEN)-1)<<PDS_CR_PDS_ISO_EN_POS)
#define PDS_CR_PDS_ISO_EN_UMSK                                  (~(((1U<<PDS_CR_PDS_ISO_EN_LEN)-1)<<PDS_CR_PDS_ISO_EN_POS))
#define PDS_CR_PDS_WAIT_XTAL_RDY                                PDS_CR_PDS_WAIT_XTAL_RDY
#define PDS_CR_PDS_WAIT_XTAL_RDY_POS                            (12U)
#define PDS_CR_PDS_WAIT_XTAL_RDY_LEN                            (1U)
#define PDS_CR_PDS_WAIT_XTAL_RDY_MSK                            (((1U<<PDS_CR_PDS_WAIT_XTAL_RDY_LEN)-1)<<PDS_CR_PDS_WAIT_XTAL_RDY_POS)
#define PDS_CR_PDS_WAIT_XTAL_RDY_UMSK                           (~(((1U<<PDS_CR_PDS_WAIT_XTAL_RDY_LEN)-1)<<PDS_CR_PDS_WAIT_XTAL_RDY_POS))
#define PDS_CR_PDS_PWR_OFF                                      PDS_CR_PDS_PWR_OFF
#define PDS_CR_PDS_PWR_OFF_POS                                  (13U)
#define PDS_CR_PDS_PWR_OFF_LEN                                  (1U)
#define PDS_CR_PDS_PWR_OFF_MSK                                  (((1U<<PDS_CR_PDS_PWR_OFF_LEN)-1)<<PDS_CR_PDS_PWR_OFF_POS)
#define PDS_CR_PDS_PWR_OFF_UMSK                                 (~(((1U<<PDS_CR_PDS_PWR_OFF_LEN)-1)<<PDS_CR_PDS_PWR_OFF_POS))
#define PDS_CR_PDS_PD_XTAL                                      PDS_CR_PDS_PD_XTAL
#define PDS_CR_PDS_PD_XTAL_POS                                  (14U)
#define PDS_CR_PDS_PD_XTAL_LEN                                  (1U)
#define PDS_CR_PDS_PD_XTAL_MSK                                  (((1U<<PDS_CR_PDS_PD_XTAL_LEN)-1)<<PDS_CR_PDS_PD_XTAL_POS)
#define PDS_CR_PDS_PD_XTAL_UMSK                                 (~(((1U<<PDS_CR_PDS_PD_XTAL_LEN)-1)<<PDS_CR_PDS_PD_XTAL_POS))
#define PDS_CR_PDS_CTRL_SOC_ENB                                 PDS_CR_PDS_CTRL_SOC_ENB
#define PDS_CR_PDS_CTRL_SOC_ENB_POS                             (15U)
#define PDS_CR_PDS_CTRL_SOC_ENB_LEN                             (1U)
#define PDS_CR_PDS_CTRL_SOC_ENB_MSK                             (((1U<<PDS_CR_PDS_CTRL_SOC_ENB_LEN)-1)<<PDS_CR_PDS_CTRL_SOC_ENB_POS)
#define PDS_CR_PDS_CTRL_SOC_ENB_UMSK                            (~(((1U<<PDS_CR_PDS_CTRL_SOC_ENB_LEN)-1)<<PDS_CR_PDS_CTRL_SOC_ENB_POS))
#define PDS_CR_PDS_RST_SOC                                      PDS_CR_PDS_RST_SOC
#define PDS_CR_PDS_RST_SOC_POS                                  (16U)
#define PDS_CR_PDS_RST_SOC_LEN                                  (1U)
#define PDS_CR_PDS_RST_SOC_MSK                                  (((1U<<PDS_CR_PDS_RST_SOC_LEN)-1)<<PDS_CR_PDS_RST_SOC_POS)
#define PDS_CR_PDS_RST_SOC_UMSK                                 (~(((1U<<PDS_CR_PDS_RST_SOC_LEN)-1)<<PDS_CR_PDS_RST_SOC_POS))
#define PDS_CR_PDS_RC32M_OFF_DIS                                PDS_CR_PDS_RC32M_OFF_DIS
#define PDS_CR_PDS_RC32M_OFF_DIS_POS                            (17U)
#define PDS_CR_PDS_RC32M_OFF_DIS_LEN                            (1U)
#define PDS_CR_PDS_RC32M_OFF_DIS_MSK                            (((1U<<PDS_CR_PDS_RC32M_OFF_DIS_LEN)-1)<<PDS_CR_PDS_RC32M_OFF_DIS_POS)
#define PDS_CR_PDS_RC32M_OFF_DIS_UMSK                           (~(((1U<<PDS_CR_PDS_RC32M_OFF_DIS_LEN)-1)<<PDS_CR_PDS_RC32M_OFF_DIS_POS))
#define PDS_CR_PDS_DCDC_VSEL_EN                                 PDS_CR_PDS_DCDC_VSEL_EN
#define PDS_CR_PDS_DCDC_VSEL_EN_POS                             (18U)
#define PDS_CR_PDS_DCDC_VSEL_EN_LEN                             (1U)
#define PDS_CR_PDS_DCDC_VSEL_EN_MSK                             (((1U<<PDS_CR_PDS_DCDC_VSEL_EN_LEN)-1)<<PDS_CR_PDS_DCDC_VSEL_EN_POS)
#define PDS_CR_PDS_DCDC_VSEL_EN_UMSK                            (~(((1U<<PDS_CR_PDS_DCDC_VSEL_EN_LEN)-1)<<PDS_CR_PDS_DCDC_VSEL_EN_POS))
#define PDS_CR_PDS_CTRL_AUPLL_PD                                PDS_CR_PDS_CTRL_AUPLL_PD
#define PDS_CR_PDS_CTRL_AUPLL_PD_POS                            (19U)
#define PDS_CR_PDS_CTRL_AUPLL_PD_LEN                            (1U)
#define PDS_CR_PDS_CTRL_AUPLL_PD_MSK                            (((1U<<PDS_CR_PDS_CTRL_AUPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_AUPLL_PD_POS)
#define PDS_CR_PDS_CTRL_AUPLL_PD_UMSK                           (~(((1U<<PDS_CR_PDS_CTRL_AUPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_AUPLL_PD_POS))
#define PDS_CR_PDS_CTRL_ETHPLL_PD                               PDS_CR_PDS_CTRL_ETHPLL_PD
#define PDS_CR_PDS_CTRL_ETHPLL_PD_POS                           (20U)
#define PDS_CR_PDS_CTRL_ETHPLL_PD_LEN                           (1U)
#define PDS_CR_PDS_CTRL_ETHPLL_PD_MSK                           (((1U<<PDS_CR_PDS_CTRL_ETHPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_ETHPLL_PD_POS)
#define PDS_CR_PDS_CTRL_ETHPLL_PD_UMSK                          (~(((1U<<PDS_CR_PDS_CTRL_ETHPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_ETHPLL_PD_POS))
#define PDS_CR_PDS_CTRL_CPUPLL_PD                               PDS_CR_PDS_CTRL_CPUPLL_PD
#define PDS_CR_PDS_CTRL_CPUPLL_PD_POS                           (21U)
#define PDS_CR_PDS_CTRL_CPUPLL_PD_LEN                           (1U)
#define PDS_CR_PDS_CTRL_CPUPLL_PD_MSK                           (((1U<<PDS_CR_PDS_CTRL_CPUPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_CPUPLL_PD_POS)
#define PDS_CR_PDS_CTRL_CPUPLL_PD_UMSK                          (~(((1U<<PDS_CR_PDS_CTRL_CPUPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_CPUPLL_PD_POS))
#define PDS_CR_PDS_CTRL_WIFIPLL_PD                              PDS_CR_PDS_CTRL_WIFIPLL_PD
#define PDS_CR_PDS_CTRL_WIFIPLL_PD_POS                          (22U)
#define PDS_CR_PDS_CTRL_WIFIPLL_PD_LEN                          (1U)
#define PDS_CR_PDS_CTRL_WIFIPLL_PD_MSK                          (((1U<<PDS_CR_PDS_CTRL_WIFIPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_WIFIPLL_PD_POS)
#define PDS_CR_PDS_CTRL_WIFIPLL_PD_UMSK                         (~(((1U<<PDS_CR_PDS_CTRL_WIFIPLL_PD_LEN)-1)<<PDS_CR_PDS_CTRL_WIFIPLL_PD_POS))
#define PDS_CR_PDS_DCDC_VOL                                     PDS_CR_PDS_DCDC_VOL
#define PDS_CR_PDS_DCDC_VOL_POS                                 (23U)
#define PDS_CR_PDS_DCDC_VOL_LEN                                 (5U)
#define PDS_CR_PDS_DCDC_VOL_MSK                                 (((1U<<PDS_CR_PDS_DCDC_VOL_LEN)-1)<<PDS_CR_PDS_DCDC_VOL_POS)
#define PDS_CR_PDS_DCDC_VOL_UMSK                                (~(((1U<<PDS_CR_PDS_DCDC_VOL_LEN)-1)<<PDS_CR_PDS_DCDC_VOL_POS))
#define PDS_CR_PDS_CTRL_RF                                      PDS_CR_PDS_CTRL_RF
#define PDS_CR_PDS_CTRL_RF_POS                                  (28U)
#define PDS_CR_PDS_CTRL_RF_LEN                                  (2U)
#define PDS_CR_PDS_CTRL_RF_MSK                                  (((1U<<PDS_CR_PDS_CTRL_RF_LEN)-1)<<PDS_CR_PDS_CTRL_RF_POS)
#define PDS_CR_PDS_CTRL_RF_UMSK                                 (~(((1U<<PDS_CR_PDS_CTRL_RF_LEN)-1)<<PDS_CR_PDS_CTRL_RF_POS))
#define PDS_CR_PDS_START_USE_TBTT_SLEEP                         PDS_CR_PDS_START_USE_TBTT_SLEEP
#define PDS_CR_PDS_START_USE_TBTT_SLEEP_POS                     (30U)
#define PDS_CR_PDS_START_USE_TBTT_SLEEP_LEN                     (1U)
#define PDS_CR_PDS_START_USE_TBTT_SLEEP_MSK                     (((1U<<PDS_CR_PDS_START_USE_TBTT_SLEEP_LEN)-1)<<PDS_CR_PDS_START_USE_TBTT_SLEEP_POS)
#define PDS_CR_PDS_START_USE_TBTT_SLEEP_UMSK                    (~(((1U<<PDS_CR_PDS_START_USE_TBTT_SLEEP_LEN)-1)<<PDS_CR_PDS_START_USE_TBTT_SLEEP_POS))

/* 0x4 : PDS_TIME1 */
#define PDS_TIME1_OFFSET                                        (0x4)
#define PDS_CR_SLEEP_DURATION                                   PDS_CR_SLEEP_DURATION
#define PDS_CR_SLEEP_DURATION_POS                               (0U)
#define PDS_CR_SLEEP_DURATION_LEN                               (32U)
#define PDS_CR_SLEEP_DURATION_MSK                               (((1U<<PDS_CR_SLEEP_DURATION_LEN)-1)<<PDS_CR_SLEEP_DURATION_POS)
#define PDS_CR_SLEEP_DURATION_UMSK                              (~(((1U<<PDS_CR_SLEEP_DURATION_LEN)-1)<<PDS_CR_SLEEP_DURATION_POS))

/* 0xC : PDS_INT */
#define PDS_INT_OFFSET                                          (0xC)
#define PDS_RO_PDS_WAKE_INT                                     PDS_RO_PDS_WAKE_INT
#define PDS_RO_PDS_WAKE_INT_POS                                 (0U)
#define PDS_RO_PDS_WAKE_INT_LEN                                 (1U)
#define PDS_RO_PDS_WAKE_INT_MSK                                 (((1U<<PDS_RO_PDS_WAKE_INT_LEN)-1)<<PDS_RO_PDS_WAKE_INT_POS)
#define PDS_RO_PDS_WAKE_INT_UMSK                                (~(((1U<<PDS_RO_PDS_WAKE_INT_LEN)-1)<<PDS_RO_PDS_WAKE_INT_POS))
#define PDS_RO_PDS_RF_DONE_INT                                  PDS_RO_PDS_RF_DONE_INT
#define PDS_RO_PDS_RF_DONE_INT_POS                              (1U)
#define PDS_RO_PDS_RF_DONE_INT_LEN                              (1U)
#define PDS_RO_PDS_RF_DONE_INT_MSK                              (((1U<<PDS_RO_PDS_RF_DONE_INT_LEN)-1)<<PDS_RO_PDS_RF_DONE_INT_POS)
#define PDS_RO_PDS_RF_DONE_INT_UMSK                             (~(((1U<<PDS_RO_PDS_RF_DONE_INT_LEN)-1)<<PDS_RO_PDS_RF_DONE_INT_POS))
#define PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ                          PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ
#define PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_POS                      (2U)
#define PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_LEN                      (1U)
#define PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_MSK                      (((1U<<PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_LEN)-1)<<PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_POS)
#define PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_UMSK                     (~(((1U<<PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_LEN)-1)<<PDS_RO_PDS_WIFI_TBTT_SLEEP_IRQ_POS))
#define PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ                         PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ
#define PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_POS                     (3U)
#define PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_LEN                     (1U)
#define PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_MSK                     (((1U<<PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_LEN)-1)<<PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_POS)
#define PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_UMSK                    (~(((1U<<PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_LEN)-1)<<PDS_RO_PDS_WIFI_TBTT_WAKEUP_IRQ_POS))
#define PDS_CR_PDS_WAKE_INT_MASK                                PDS_CR_PDS_WAKE_INT_MASK
#define PDS_CR_PDS_WAKE_INT_MASK_POS                            (4U)
#define PDS_CR_PDS_WAKE_INT_MASK_LEN                            (1U)
#define PDS_CR_PDS_WAKE_INT_MASK_MSK                            (((1U<<PDS_CR_PDS_WAKE_INT_MASK_LEN)-1)<<PDS_CR_PDS_WAKE_INT_MASK_POS)
#define PDS_CR_PDS_WAKE_INT_MASK_UMSK                           (~(((1U<<PDS_CR_PDS_WAKE_INT_MASK_LEN)-1)<<PDS_CR_PDS_WAKE_INT_MASK_POS))
#define PDS_CR_PDS_RF_DONE_INT_MASK                             PDS_CR_PDS_RF_DONE_INT_MASK
#define PDS_CR_PDS_RF_DONE_INT_MASK_POS                         (5U)
#define PDS_CR_PDS_RF_DONE_INT_MASK_LEN                         (1U)
#define PDS_CR_PDS_RF_DONE_INT_MASK_MSK                         (((1U<<PDS_CR_PDS_RF_DONE_INT_MASK_LEN)-1)<<PDS_CR_PDS_RF_DONE_INT_MASK_POS)
#define PDS_CR_PDS_RF_DONE_INT_MASK_UMSK                        (~(((1U<<PDS_CR_PDS_RF_DONE_INT_MASK_LEN)-1)<<PDS_CR_PDS_RF_DONE_INT_MASK_POS))
#define PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK                     PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK
#define PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_POS                 (6U)
#define PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_LEN                 (1U)
#define PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_MSK                 (((1U<<PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_LEN)-1)<<PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_POS)
#define PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_UMSK                (~(((1U<<PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_LEN)-1)<<PDS_CR_PDS_WIFI_TBTT_SLEEP_IRQ_MASK_POS))
#define PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK                    PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK
#define PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_POS                (7U)
#define PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_LEN                (1U)
#define PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_MSK                (((1U<<PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_LEN)-1)<<PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_POS)
#define PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_UMSK               (~(((1U<<PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_LEN)-1)<<PDS_CR_PDS_WIFI_TBTT_WAKEUP_IRQ_MASK_POS))
#define PDS_CR_PDS_INT_CLR                                      PDS_CR_PDS_INT_CLR
#define PDS_CR_PDS_INT_CLR_POS                                  (8U)
#define PDS_CR_PDS_INT_CLR_LEN                                  (1U)
#define PDS_CR_PDS_INT_CLR_MSK                                  (((1U<<PDS_CR_PDS_INT_CLR_LEN)-1)<<PDS_CR_PDS_INT_CLR_POS)
#define PDS_CR_PDS_INT_CLR_UMSK                                 (~(((1U<<PDS_CR_PDS_INT_CLR_LEN)-1)<<PDS_CR_PDS_INT_CLR_POS))
#define PDS_CR_PDS_WAKEUP_SRC_EN                                PDS_CR_PDS_WAKEUP_SRC_EN
#define PDS_CR_PDS_WAKEUP_SRC_EN_POS                            (10U)
#define PDS_CR_PDS_WAKEUP_SRC_EN_LEN                            (11U)
#define PDS_CR_PDS_WAKEUP_SRC_EN_MSK                            (((1U<<PDS_CR_PDS_WAKEUP_SRC_EN_LEN)-1)<<PDS_CR_PDS_WAKEUP_SRC_EN_POS)
#define PDS_CR_PDS_WAKEUP_SRC_EN_UMSK                           (~(((1U<<PDS_CR_PDS_WAKEUP_SRC_EN_LEN)-1)<<PDS_CR_PDS_WAKEUP_SRC_EN_POS))
#define PDS_RO_PDS_WAKEUP_EVENT                                 PDS_RO_PDS_WAKEUP_EVENT
#define PDS_RO_PDS_WAKEUP_EVENT_POS                             (21U)
#define PDS_RO_PDS_WAKEUP_EVENT_LEN                             (11U)
#define PDS_RO_PDS_WAKEUP_EVENT_MSK                             (((1U<<PDS_RO_PDS_WAKEUP_EVENT_LEN)-1)<<PDS_RO_PDS_WAKEUP_EVENT_POS)
#define PDS_RO_PDS_WAKEUP_EVENT_UMSK                            (~(((1U<<PDS_RO_PDS_WAKEUP_EVENT_LEN)-1)<<PDS_RO_PDS_WAKEUP_EVENT_POS))

/* 0x10 : PDS_CTL2 */
#define PDS_CTL2_OFFSET                                         (0x10)
#define PDS_CR_PDS_FORCE_NP_PWR_OFF                             PDS_CR_PDS_FORCE_NP_PWR_OFF
#define PDS_CR_PDS_FORCE_NP_PWR_OFF_POS                         (0U)
#define PDS_CR_PDS_FORCE_NP_PWR_OFF_LEN                         (1U)
#define PDS_CR_PDS_FORCE_NP_PWR_OFF_MSK                         (((1U<<PDS_CR_PDS_FORCE_NP_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_NP_PWR_OFF_POS)
#define PDS_CR_PDS_FORCE_NP_PWR_OFF_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_NP_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_NP_PWR_OFF_POS))
#define PDS_CR_PDS_FORCE_MM_PWR_OFF                             PDS_CR_PDS_FORCE_MM_PWR_OFF
#define PDS_CR_PDS_FORCE_MM_PWR_OFF_POS                         (1U)
#define PDS_CR_PDS_FORCE_MM_PWR_OFF_LEN                         (1U)
#define PDS_CR_PDS_FORCE_MM_PWR_OFF_MSK                         (((1U<<PDS_CR_PDS_FORCE_MM_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_MM_PWR_OFF_POS)
#define PDS_CR_PDS_FORCE_MM_PWR_OFF_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_MM_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_MM_PWR_OFF_POS))
#define PDS_CR_PDS_FORCE_WB_PWR_OFF                             PDS_CR_PDS_FORCE_WB_PWR_OFF
#define PDS_CR_PDS_FORCE_WB_PWR_OFF_POS                         (2U)
#define PDS_CR_PDS_FORCE_WB_PWR_OFF_LEN                         (1U)
#define PDS_CR_PDS_FORCE_WB_PWR_OFF_MSK                         (((1U<<PDS_CR_PDS_FORCE_WB_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_WB_PWR_OFF_POS)
#define PDS_CR_PDS_FORCE_WB_PWR_OFF_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_WB_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_WB_PWR_OFF_POS))
#define PDS_CR_PDS_FORCE_AUDIO_PWR_OFF                          PDS_CR_PDS_FORCE_AUDIO_PWR_OFF
#define PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_POS                      (3U)
#define PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_LEN                      (1U)
#define PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_MSK                      (((1U<<PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_POS)
#define PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_UMSK                     (~(((1U<<PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_PWR_OFF_POS))
#define PDS_CR_PDS_FORCE_NP_ISO_EN                              PDS_CR_PDS_FORCE_NP_ISO_EN
#define PDS_CR_PDS_FORCE_NP_ISO_EN_POS                          (4U)
#define PDS_CR_PDS_FORCE_NP_ISO_EN_LEN                          (1U)
#define PDS_CR_PDS_FORCE_NP_ISO_EN_MSK                          (((1U<<PDS_CR_PDS_FORCE_NP_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_NP_ISO_EN_POS)
#define PDS_CR_PDS_FORCE_NP_ISO_EN_UMSK                         (~(((1U<<PDS_CR_PDS_FORCE_NP_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_NP_ISO_EN_POS))
#define PDS_CR_PDS_FORCE_MM_ISO_EN                              PDS_CR_PDS_FORCE_MM_ISO_EN
#define PDS_CR_PDS_FORCE_MM_ISO_EN_POS                          (5U)
#define PDS_CR_PDS_FORCE_MM_ISO_EN_LEN                          (1U)
#define PDS_CR_PDS_FORCE_MM_ISO_EN_MSK                          (((1U<<PDS_CR_PDS_FORCE_MM_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_MM_ISO_EN_POS)
#define PDS_CR_PDS_FORCE_MM_ISO_EN_UMSK                         (~(((1U<<PDS_CR_PDS_FORCE_MM_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_MM_ISO_EN_POS))
#define PDS_CR_PDS_FORCE_WB_ISO_EN                              PDS_CR_PDS_FORCE_WB_ISO_EN
#define PDS_CR_PDS_FORCE_WB_ISO_EN_POS                          (6U)
#define PDS_CR_PDS_FORCE_WB_ISO_EN_LEN                          (1U)
#define PDS_CR_PDS_FORCE_WB_ISO_EN_MSK                          (((1U<<PDS_CR_PDS_FORCE_WB_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_WB_ISO_EN_POS)
#define PDS_CR_PDS_FORCE_WB_ISO_EN_UMSK                         (~(((1U<<PDS_CR_PDS_FORCE_WB_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_WB_ISO_EN_POS))
#define PDS_CR_PDS_FORCE_AUDIO_ISO_EN                           PDS_CR_PDS_FORCE_AUDIO_ISO_EN
#define PDS_CR_PDS_FORCE_AUDIO_ISO_EN_POS                       (7U)
#define PDS_CR_PDS_FORCE_AUDIO_ISO_EN_LEN                       (1U)
#define PDS_CR_PDS_FORCE_AUDIO_ISO_EN_MSK                       (((1U<<PDS_CR_PDS_FORCE_AUDIO_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_ISO_EN_POS)
#define PDS_CR_PDS_FORCE_AUDIO_ISO_EN_UMSK                      (~(((1U<<PDS_CR_PDS_FORCE_AUDIO_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_ISO_EN_POS))
#define PDS_CR_PDS_FORCE_NP_PDS_RST                             PDS_CR_PDS_FORCE_NP_PDS_RST
#define PDS_CR_PDS_FORCE_NP_PDS_RST_POS                         (8U)
#define PDS_CR_PDS_FORCE_NP_PDS_RST_LEN                         (1U)
#define PDS_CR_PDS_FORCE_NP_PDS_RST_MSK                         (((1U<<PDS_CR_PDS_FORCE_NP_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_NP_PDS_RST_POS)
#define PDS_CR_PDS_FORCE_NP_PDS_RST_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_NP_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_NP_PDS_RST_POS))
#define PDS_CR_PDS_FORCE_MM_PDS_RST                             PDS_CR_PDS_FORCE_MM_PDS_RST
#define PDS_CR_PDS_FORCE_MM_PDS_RST_POS                         (9U)
#define PDS_CR_PDS_FORCE_MM_PDS_RST_LEN                         (1U)
#define PDS_CR_PDS_FORCE_MM_PDS_RST_MSK                         (((1U<<PDS_CR_PDS_FORCE_MM_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_MM_PDS_RST_POS)
#define PDS_CR_PDS_FORCE_MM_PDS_RST_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_MM_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_MM_PDS_RST_POS))
#define PDS_CR_PDS_FORCE_WB_PDS_RST                             PDS_CR_PDS_FORCE_WB_PDS_RST
#define PDS_CR_PDS_FORCE_WB_PDS_RST_POS                         (10U)
#define PDS_CR_PDS_FORCE_WB_PDS_RST_LEN                         (1U)
#define PDS_CR_PDS_FORCE_WB_PDS_RST_MSK                         (((1U<<PDS_CR_PDS_FORCE_WB_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_WB_PDS_RST_POS)
#define PDS_CR_PDS_FORCE_WB_PDS_RST_UMSK                        (~(((1U<<PDS_CR_PDS_FORCE_WB_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_WB_PDS_RST_POS))
#define PDS_CR_PDS_FORCE_AUDIO_PDS_RST                          PDS_CR_PDS_FORCE_AUDIO_PDS_RST
#define PDS_CR_PDS_FORCE_AUDIO_PDS_RST_POS                      (11U)
#define PDS_CR_PDS_FORCE_AUDIO_PDS_RST_LEN                      (1U)
#define PDS_CR_PDS_FORCE_AUDIO_PDS_RST_MSK                      (((1U<<PDS_CR_PDS_FORCE_AUDIO_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_PDS_RST_POS)
#define PDS_CR_PDS_FORCE_AUDIO_PDS_RST_UMSK                     (~(((1U<<PDS_CR_PDS_FORCE_AUDIO_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_PDS_RST_POS))
#define PDS_CR_PDS_FORCE_NP_MEM_STBY                            PDS_CR_PDS_FORCE_NP_MEM_STBY
#define PDS_CR_PDS_FORCE_NP_MEM_STBY_POS                        (12U)
#define PDS_CR_PDS_FORCE_NP_MEM_STBY_LEN                        (1U)
#define PDS_CR_PDS_FORCE_NP_MEM_STBY_MSK                        (((1U<<PDS_CR_PDS_FORCE_NP_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_NP_MEM_STBY_POS)
#define PDS_CR_PDS_FORCE_NP_MEM_STBY_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_NP_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_NP_MEM_STBY_POS))
#define PDS_CR_PDS_FORCE_MM_MEM_STBY                            PDS_CR_PDS_FORCE_MM_MEM_STBY
#define PDS_CR_PDS_FORCE_MM_MEM_STBY_POS                        (13U)
#define PDS_CR_PDS_FORCE_MM_MEM_STBY_LEN                        (1U)
#define PDS_CR_PDS_FORCE_MM_MEM_STBY_MSK                        (((1U<<PDS_CR_PDS_FORCE_MM_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_MM_MEM_STBY_POS)
#define PDS_CR_PDS_FORCE_MM_MEM_STBY_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_MM_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_MM_MEM_STBY_POS))
#define PDS_CR_PDS_FORCE_WB_MEM_STBY                            PDS_CR_PDS_FORCE_WB_MEM_STBY
#define PDS_CR_PDS_FORCE_WB_MEM_STBY_POS                        (14U)
#define PDS_CR_PDS_FORCE_WB_MEM_STBY_LEN                        (1U)
#define PDS_CR_PDS_FORCE_WB_MEM_STBY_MSK                        (((1U<<PDS_CR_PDS_FORCE_WB_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_WB_MEM_STBY_POS)
#define PDS_CR_PDS_FORCE_WB_MEM_STBY_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_WB_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_WB_MEM_STBY_POS))
#define PDS_CR_PDS_FORCE_AUDIO_MEM_STBY                         PDS_CR_PDS_FORCE_AUDIO_MEM_STBY
#define PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_POS                     (15U)
#define PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_LEN                     (1U)
#define PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_MSK                     (((1U<<PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_POS)
#define PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_UMSK                    (~(((1U<<PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_MEM_STBY_POS))
#define PDS_CR_PDS_FORCE_NP_GATE_CLK                            PDS_CR_PDS_FORCE_NP_GATE_CLK
#define PDS_CR_PDS_FORCE_NP_GATE_CLK_POS                        (16U)
#define PDS_CR_PDS_FORCE_NP_GATE_CLK_LEN                        (1U)
#define PDS_CR_PDS_FORCE_NP_GATE_CLK_MSK                        (((1U<<PDS_CR_PDS_FORCE_NP_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_NP_GATE_CLK_POS)
#define PDS_CR_PDS_FORCE_NP_GATE_CLK_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_NP_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_NP_GATE_CLK_POS))
#define PDS_CR_PDS_FORCE_MM_GATE_CLK                            PDS_CR_PDS_FORCE_MM_GATE_CLK
#define PDS_CR_PDS_FORCE_MM_GATE_CLK_POS                        (17U)
#define PDS_CR_PDS_FORCE_MM_GATE_CLK_LEN                        (1U)
#define PDS_CR_PDS_FORCE_MM_GATE_CLK_MSK                        (((1U<<PDS_CR_PDS_FORCE_MM_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_MM_GATE_CLK_POS)
#define PDS_CR_PDS_FORCE_MM_GATE_CLK_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_MM_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_MM_GATE_CLK_POS))
#define PDS_CR_PDS_FORCE_WB_GATE_CLK                            PDS_CR_PDS_FORCE_WB_GATE_CLK
#define PDS_CR_PDS_FORCE_WB_GATE_CLK_POS                        (18U)
#define PDS_CR_PDS_FORCE_WB_GATE_CLK_LEN                        (1U)
#define PDS_CR_PDS_FORCE_WB_GATE_CLK_MSK                        (((1U<<PDS_CR_PDS_FORCE_WB_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_WB_GATE_CLK_POS)
#define PDS_CR_PDS_FORCE_WB_GATE_CLK_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_WB_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_WB_GATE_CLK_POS))
#define PDS_CR_PDS_FORCE_AUDIO_GATE_CLK                         PDS_CR_PDS_FORCE_AUDIO_GATE_CLK
#define PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_POS                     (19U)
#define PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_LEN                     (1U)
#define PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_MSK                     (((1U<<PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_POS)
#define PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_UMSK                    (~(((1U<<PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_AUDIO_GATE_CLK_POS))
#define PDS_CR_PDS_NP_LV_PWR                                    PDS_CR_PDS_NP_LV_PWR
#define PDS_CR_PDS_NP_LV_PWR_POS                                (24U)
#define PDS_CR_PDS_NP_LV_PWR_LEN                                (1U)
#define PDS_CR_PDS_NP_LV_PWR_MSK                                (((1U<<PDS_CR_PDS_NP_LV_PWR_LEN)-1)<<PDS_CR_PDS_NP_LV_PWR_POS)
#define PDS_CR_PDS_NP_LV_PWR_UMSK                               (~(((1U<<PDS_CR_PDS_NP_LV_PWR_LEN)-1)<<PDS_CR_PDS_NP_LV_PWR_POS))
#define PDS_CR_PDS_MM_LV_PWR                                    PDS_CR_PDS_MM_LV_PWR
#define PDS_CR_PDS_MM_LV_PWR_POS                                (25U)
#define PDS_CR_PDS_MM_LV_PWR_LEN                                (1U)
#define PDS_CR_PDS_MM_LV_PWR_MSK                                (((1U<<PDS_CR_PDS_MM_LV_PWR_LEN)-1)<<PDS_CR_PDS_MM_LV_PWR_POS)
#define PDS_CR_PDS_MM_LV_PWR_UMSK                               (~(((1U<<PDS_CR_PDS_MM_LV_PWR_LEN)-1)<<PDS_CR_PDS_MM_LV_PWR_POS))
#define PDS_CR_PDS_WB_LV_PWR                                    PDS_CR_PDS_WB_LV_PWR
#define PDS_CR_PDS_WB_LV_PWR_POS                                (26U)
#define PDS_CR_PDS_WB_LV_PWR_LEN                                (1U)
#define PDS_CR_PDS_WB_LV_PWR_MSK                                (((1U<<PDS_CR_PDS_WB_LV_PWR_LEN)-1)<<PDS_CR_PDS_WB_LV_PWR_POS)
#define PDS_CR_PDS_WB_LV_PWR_UMSK                               (~(((1U<<PDS_CR_PDS_WB_LV_PWR_LEN)-1)<<PDS_CR_PDS_WB_LV_PWR_POS))
#define PDS_CR_PDS_AUDIO_LV_PWR                                 PDS_CR_PDS_AUDIO_LV_PWR
#define PDS_CR_PDS_AUDIO_LV_PWR_POS                             (27U)
#define PDS_CR_PDS_AUDIO_LV_PWR_LEN                             (1U)
#define PDS_CR_PDS_AUDIO_LV_PWR_MSK                             (((1U<<PDS_CR_PDS_AUDIO_LV_PWR_LEN)-1)<<PDS_CR_PDS_AUDIO_LV_PWR_POS)
#define PDS_CR_PDS_AUDIO_LV_PWR_UMSK                            (~(((1U<<PDS_CR_PDS_AUDIO_LV_PWR_LEN)-1)<<PDS_CR_PDS_AUDIO_LV_PWR_POS))
#define PDS_CR_PDS_MISC_LV_PWR                                  PDS_CR_PDS_MISC_LV_PWR
#define PDS_CR_PDS_MISC_LV_PWR_POS                              (28U)
#define PDS_CR_PDS_MISC_LV_PWR_LEN                              (1U)
#define PDS_CR_PDS_MISC_LV_PWR_MSK                              (((1U<<PDS_CR_PDS_MISC_LV_PWR_LEN)-1)<<PDS_CR_PDS_MISC_LV_PWR_POS)
#define PDS_CR_PDS_MISC_LV_PWR_UMSK                             (~(((1U<<PDS_CR_PDS_MISC_LV_PWR_LEN)-1)<<PDS_CR_PDS_MISC_LV_PWR_POS))
#define PDS_CR_PDS_LV_PWR                                       PDS_CR_PDS_LV_PWR
#define PDS_CR_PDS_LV_PWR_POS                                   (31U)
#define PDS_CR_PDS_LV_PWR_LEN                                   (1U)
#define PDS_CR_PDS_LV_PWR_MSK                                   (((1U<<PDS_CR_PDS_LV_PWR_LEN)-1)<<PDS_CR_PDS_LV_PWR_POS)
#define PDS_CR_PDS_LV_PWR_UMSK                                  (~(((1U<<PDS_CR_PDS_LV_PWR_LEN)-1)<<PDS_CR_PDS_LV_PWR_POS))

/* 0x14 : PDS_CTL3 */
#define PDS_CTL3_OFFSET                                         (0x14)
#define PDS_CR_PDS_FORCE_MISC_PWR_OFF                           PDS_CR_PDS_FORCE_MISC_PWR_OFF
#define PDS_CR_PDS_FORCE_MISC_PWR_OFF_POS                       (1U)
#define PDS_CR_PDS_FORCE_MISC_PWR_OFF_LEN                       (1U)
#define PDS_CR_PDS_FORCE_MISC_PWR_OFF_MSK                       (((1U<<PDS_CR_PDS_FORCE_MISC_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_PWR_OFF_POS)
#define PDS_CR_PDS_FORCE_MISC_PWR_OFF_UMSK                      (~(((1U<<PDS_CR_PDS_FORCE_MISC_PWR_OFF_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_PWR_OFF_POS))
#define PDS_CR_PDS_FORCE_MISC_ISO_EN                            PDS_CR_PDS_FORCE_MISC_ISO_EN
#define PDS_CR_PDS_FORCE_MISC_ISO_EN_POS                        (4U)
#define PDS_CR_PDS_FORCE_MISC_ISO_EN_LEN                        (1U)
#define PDS_CR_PDS_FORCE_MISC_ISO_EN_MSK                        (((1U<<PDS_CR_PDS_FORCE_MISC_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_ISO_EN_POS)
#define PDS_CR_PDS_FORCE_MISC_ISO_EN_UMSK                       (~(((1U<<PDS_CR_PDS_FORCE_MISC_ISO_EN_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_ISO_EN_POS))
#define PDS_CR_PDS_FORCE_MISC_PDS_RST                           PDS_CR_PDS_FORCE_MISC_PDS_RST
#define PDS_CR_PDS_FORCE_MISC_PDS_RST_POS                       (7U)
#define PDS_CR_PDS_FORCE_MISC_PDS_RST_LEN                       (1U)
#define PDS_CR_PDS_FORCE_MISC_PDS_RST_MSK                       (((1U<<PDS_CR_PDS_FORCE_MISC_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_PDS_RST_POS)
#define PDS_CR_PDS_FORCE_MISC_PDS_RST_UMSK                      (~(((1U<<PDS_CR_PDS_FORCE_MISC_PDS_RST_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_PDS_RST_POS))
#define PDS_CR_PDS_FORCE_MISC_MEM_STBY                          PDS_CR_PDS_FORCE_MISC_MEM_STBY
#define PDS_CR_PDS_FORCE_MISC_MEM_STBY_POS                      (10U)
#define PDS_CR_PDS_FORCE_MISC_MEM_STBY_LEN                      (1U)
#define PDS_CR_PDS_FORCE_MISC_MEM_STBY_MSK                      (((1U<<PDS_CR_PDS_FORCE_MISC_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_MEM_STBY_POS)
#define PDS_CR_PDS_FORCE_MISC_MEM_STBY_UMSK                     (~(((1U<<PDS_CR_PDS_FORCE_MISC_MEM_STBY_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_MEM_STBY_POS))
#define PDS_CR_PDS_FORCE_MISC_GATE_CLK                          PDS_CR_PDS_FORCE_MISC_GATE_CLK
#define PDS_CR_PDS_FORCE_MISC_GATE_CLK_POS                      (13U)
#define PDS_CR_PDS_FORCE_MISC_GATE_CLK_LEN                      (1U)
#define PDS_CR_PDS_FORCE_MISC_GATE_CLK_MSK                      (((1U<<PDS_CR_PDS_FORCE_MISC_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_GATE_CLK_POS)
#define PDS_CR_PDS_FORCE_MISC_GATE_CLK_UMSK                     (~(((1U<<PDS_CR_PDS_FORCE_MISC_GATE_CLK_LEN)-1)<<PDS_CR_PDS_FORCE_MISC_GATE_CLK_POS))
#define PDS_CR_PDS_NP_ISO_EN                                    PDS_CR_PDS_NP_ISO_EN
#define PDS_CR_PDS_NP_ISO_EN_POS                                (24U)
#define PDS_CR_PDS_NP_ISO_EN_LEN                                (1U)
#define PDS_CR_PDS_NP_ISO_EN_MSK                                (((1U<<PDS_CR_PDS_NP_ISO_EN_LEN)-1)<<PDS_CR_PDS_NP_ISO_EN_POS)
#define PDS_CR_PDS_NP_ISO_EN_UMSK                               (~(((1U<<PDS_CR_PDS_NP_ISO_EN_LEN)-1)<<PDS_CR_PDS_NP_ISO_EN_POS))
#define PDS_CR_PDS_MM_ISO_EN                                    PDS_CR_PDS_MM_ISO_EN
#define PDS_CR_PDS_MM_ISO_EN_POS                                (26U)
#define PDS_CR_PDS_MM_ISO_EN_LEN                                (1U)
#define PDS_CR_PDS_MM_ISO_EN_MSK                                (((1U<<PDS_CR_PDS_MM_ISO_EN_LEN)-1)<<PDS_CR_PDS_MM_ISO_EN_POS)
#define PDS_CR_PDS_MM_ISO_EN_UMSK                               (~(((1U<<PDS_CR_PDS_MM_ISO_EN_LEN)-1)<<PDS_CR_PDS_MM_ISO_EN_POS))
#define PDS_CR_PDS_WB_ISO_EN                                    PDS_CR_PDS_WB_ISO_EN
#define PDS_CR_PDS_WB_ISO_EN_POS                                (27U)
#define PDS_CR_PDS_WB_ISO_EN_LEN                                (1U)
#define PDS_CR_PDS_WB_ISO_EN_MSK                                (((1U<<PDS_CR_PDS_WB_ISO_EN_LEN)-1)<<PDS_CR_PDS_WB_ISO_EN_POS)
#define PDS_CR_PDS_WB_ISO_EN_UMSK                               (~(((1U<<PDS_CR_PDS_WB_ISO_EN_LEN)-1)<<PDS_CR_PDS_WB_ISO_EN_POS))
#define PDS_CR_PDS_AUDIO_ISO_EN                                 PDS_CR_PDS_AUDIO_ISO_EN
#define PDS_CR_PDS_AUDIO_ISO_EN_POS                             (29U)
#define PDS_CR_PDS_AUDIO_ISO_EN_LEN                             (1U)
#define PDS_CR_PDS_AUDIO_ISO_EN_MSK                             (((1U<<PDS_CR_PDS_AUDIO_ISO_EN_LEN)-1)<<PDS_CR_PDS_AUDIO_ISO_EN_POS)
#define PDS_CR_PDS_AUDIO_ISO_EN_UMSK                            (~(((1U<<PDS_CR_PDS_AUDIO_ISO_EN_LEN)-1)<<PDS_CR_PDS_AUDIO_ISO_EN_POS))
#define PDS_CR_PDS_MISC_ISO_EN                                  PDS_CR_PDS_MISC_ISO_EN
#define PDS_CR_PDS_MISC_ISO_EN_POS                              (30U)
#define PDS_CR_PDS_MISC_ISO_EN_LEN                              (1U)
#define PDS_CR_PDS_MISC_ISO_EN_MSK                              (((1U<<PDS_CR_PDS_MISC_ISO_EN_LEN)-1)<<PDS_CR_PDS_MISC_ISO_EN_POS)
#define PDS_CR_PDS_MISC_ISO_EN_UMSK                             (~(((1U<<PDS_CR_PDS_MISC_ISO_EN_LEN)-1)<<PDS_CR_PDS_MISC_ISO_EN_POS))

/* 0x18 : PDS_CTL4 */
#define PDS_CTL4_OFFSET                                         (0x18)
#define PDS_CR_PDS_NP_PWR_OFF                                   PDS_CR_PDS_NP_PWR_OFF
#define PDS_CR_PDS_NP_PWR_OFF_POS                               (0U)
#define PDS_CR_PDS_NP_PWR_OFF_LEN                               (1U)
#define PDS_CR_PDS_NP_PWR_OFF_MSK                               (((1U<<PDS_CR_PDS_NP_PWR_OFF_LEN)-1)<<PDS_CR_PDS_NP_PWR_OFF_POS)
#define PDS_CR_PDS_NP_PWR_OFF_UMSK                              (~(((1U<<PDS_CR_PDS_NP_PWR_OFF_LEN)-1)<<PDS_CR_PDS_NP_PWR_OFF_POS))
#define PDS_CR_PDS_NP_RESET                                     PDS_CR_PDS_NP_RESET
#define PDS_CR_PDS_NP_RESET_POS                                 (1U)
#define PDS_CR_PDS_NP_RESET_LEN                                 (1U)
#define PDS_CR_PDS_NP_RESET_MSK                                 (((1U<<PDS_CR_PDS_NP_RESET_LEN)-1)<<PDS_CR_PDS_NP_RESET_POS)
#define PDS_CR_PDS_NP_RESET_UMSK                                (~(((1U<<PDS_CR_PDS_NP_RESET_LEN)-1)<<PDS_CR_PDS_NP_RESET_POS))
#define PDS_CR_PDS_NP_MEM_STBY                                  PDS_CR_PDS_NP_MEM_STBY
#define PDS_CR_PDS_NP_MEM_STBY_POS                              (2U)
#define PDS_CR_PDS_NP_MEM_STBY_LEN                              (1U)
#define PDS_CR_PDS_NP_MEM_STBY_MSK                              (((1U<<PDS_CR_PDS_NP_MEM_STBY_LEN)-1)<<PDS_CR_PDS_NP_MEM_STBY_POS)
#define PDS_CR_PDS_NP_MEM_STBY_UMSK                             (~(((1U<<PDS_CR_PDS_NP_MEM_STBY_LEN)-1)<<PDS_CR_PDS_NP_MEM_STBY_POS))
#define PDS_CR_PDS_NP_GATE_CLK                                  PDS_CR_PDS_NP_GATE_CLK
#define PDS_CR_PDS_NP_GATE_CLK_POS                              (3U)
#define PDS_CR_PDS_NP_GATE_CLK_LEN                              (1U)
#define PDS_CR_PDS_NP_GATE_CLK_MSK                              (((1U<<PDS_CR_PDS_NP_GATE_CLK_LEN)-1)<<PDS_CR_PDS_NP_GATE_CLK_POS)
#define PDS_CR_PDS_NP_GATE_CLK_UMSK                             (~(((1U<<PDS_CR_PDS_NP_GATE_CLK_LEN)-1)<<PDS_CR_PDS_NP_GATE_CLK_POS))
#define PDS_CR_PDS_MM_PWR_OFF                                   PDS_CR_PDS_MM_PWR_OFF
#define PDS_CR_PDS_MM_PWR_OFF_POS                               (8U)
#define PDS_CR_PDS_MM_PWR_OFF_LEN                               (1U)
#define PDS_CR_PDS_MM_PWR_OFF_MSK                               (((1U<<PDS_CR_PDS_MM_PWR_OFF_LEN)-1)<<PDS_CR_PDS_MM_PWR_OFF_POS)
#define PDS_CR_PDS_MM_PWR_OFF_UMSK                              (~(((1U<<PDS_CR_PDS_MM_PWR_OFF_LEN)-1)<<PDS_CR_PDS_MM_PWR_OFF_POS))
#define PDS_CR_PDS_MM_RESET                                     PDS_CR_PDS_MM_RESET
#define PDS_CR_PDS_MM_RESET_POS                                 (9U)
#define PDS_CR_PDS_MM_RESET_LEN                                 (1U)
#define PDS_CR_PDS_MM_RESET_MSK                                 (((1U<<PDS_CR_PDS_MM_RESET_LEN)-1)<<PDS_CR_PDS_MM_RESET_POS)
#define PDS_CR_PDS_MM_RESET_UMSK                                (~(((1U<<PDS_CR_PDS_MM_RESET_LEN)-1)<<PDS_CR_PDS_MM_RESET_POS))
#define PDS_CR_PDS_MM_MEM_STBY                                  PDS_CR_PDS_MM_MEM_STBY
#define PDS_CR_PDS_MM_MEM_STBY_POS                              (10U)
#define PDS_CR_PDS_MM_MEM_STBY_LEN                              (1U)
#define PDS_CR_PDS_MM_MEM_STBY_MSK                              (((1U<<PDS_CR_PDS_MM_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MM_MEM_STBY_POS)
#define PDS_CR_PDS_MM_MEM_STBY_UMSK                             (~(((1U<<PDS_CR_PDS_MM_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MM_MEM_STBY_POS))
#define PDS_CR_PDS_MM_GATE_CLK                                  PDS_CR_PDS_MM_GATE_CLK
#define PDS_CR_PDS_MM_GATE_CLK_POS                              (11U)
#define PDS_CR_PDS_MM_GATE_CLK_LEN                              (1U)
#define PDS_CR_PDS_MM_GATE_CLK_MSK                              (((1U<<PDS_CR_PDS_MM_GATE_CLK_LEN)-1)<<PDS_CR_PDS_MM_GATE_CLK_POS)
#define PDS_CR_PDS_MM_GATE_CLK_UMSK                             (~(((1U<<PDS_CR_PDS_MM_GATE_CLK_LEN)-1)<<PDS_CR_PDS_MM_GATE_CLK_POS))
#define PDS_CR_PDS_WB_PWR_OFF                                   PDS_CR_PDS_WB_PWR_OFF
#define PDS_CR_PDS_WB_PWR_OFF_POS                               (12U)
#define PDS_CR_PDS_WB_PWR_OFF_LEN                               (1U)
#define PDS_CR_PDS_WB_PWR_OFF_MSK                               (((1U<<PDS_CR_PDS_WB_PWR_OFF_LEN)-1)<<PDS_CR_PDS_WB_PWR_OFF_POS)
#define PDS_CR_PDS_WB_PWR_OFF_UMSK                              (~(((1U<<PDS_CR_PDS_WB_PWR_OFF_LEN)-1)<<PDS_CR_PDS_WB_PWR_OFF_POS))
#define PDS_CR_PDS_WB_RESET                                     PDS_CR_PDS_WB_RESET
#define PDS_CR_PDS_WB_RESET_POS                                 (13U)
#define PDS_CR_PDS_WB_RESET_LEN                                 (1U)
#define PDS_CR_PDS_WB_RESET_MSK                                 (((1U<<PDS_CR_PDS_WB_RESET_LEN)-1)<<PDS_CR_PDS_WB_RESET_POS)
#define PDS_CR_PDS_WB_RESET_UMSK                                (~(((1U<<PDS_CR_PDS_WB_RESET_LEN)-1)<<PDS_CR_PDS_WB_RESET_POS))
#define PDS_CR_PDS_WB_MEM_STBY                                  PDS_CR_PDS_WB_MEM_STBY
#define PDS_CR_PDS_WB_MEM_STBY_POS                              (14U)
#define PDS_CR_PDS_WB_MEM_STBY_LEN                              (1U)
#define PDS_CR_PDS_WB_MEM_STBY_MSK                              (((1U<<PDS_CR_PDS_WB_MEM_STBY_LEN)-1)<<PDS_CR_PDS_WB_MEM_STBY_POS)
#define PDS_CR_PDS_WB_MEM_STBY_UMSK                             (~(((1U<<PDS_CR_PDS_WB_MEM_STBY_LEN)-1)<<PDS_CR_PDS_WB_MEM_STBY_POS))
#define PDS_CR_PDS_WB_GATE_CLK                                  PDS_CR_PDS_WB_GATE_CLK
#define PDS_CR_PDS_WB_GATE_CLK_POS                              (15U)
#define PDS_CR_PDS_WB_GATE_CLK_LEN                              (1U)
#define PDS_CR_PDS_WB_GATE_CLK_MSK                              (((1U<<PDS_CR_PDS_WB_GATE_CLK_LEN)-1)<<PDS_CR_PDS_WB_GATE_CLK_POS)
#define PDS_CR_PDS_WB_GATE_CLK_UMSK                             (~(((1U<<PDS_CR_PDS_WB_GATE_CLK_LEN)-1)<<PDS_CR_PDS_WB_GATE_CLK_POS))
#define PDS_CR_PDS_AUDIO_PWR_OFF                                PDS_CR_PDS_AUDIO_PWR_OFF
#define PDS_CR_PDS_AUDIO_PWR_OFF_POS                            (20U)
#define PDS_CR_PDS_AUDIO_PWR_OFF_LEN                            (1U)
#define PDS_CR_PDS_AUDIO_PWR_OFF_MSK                            (((1U<<PDS_CR_PDS_AUDIO_PWR_OFF_LEN)-1)<<PDS_CR_PDS_AUDIO_PWR_OFF_POS)
#define PDS_CR_PDS_AUDIO_PWR_OFF_UMSK                           (~(((1U<<PDS_CR_PDS_AUDIO_PWR_OFF_LEN)-1)<<PDS_CR_PDS_AUDIO_PWR_OFF_POS))
#define PDS_CR_PDS_AUDIO_RESET                                  PDS_CR_PDS_AUDIO_RESET
#define PDS_CR_PDS_AUDIO_RESET_POS                              (21U)
#define PDS_CR_PDS_AUDIO_RESET_LEN                              (1U)
#define PDS_CR_PDS_AUDIO_RESET_MSK                              (((1U<<PDS_CR_PDS_AUDIO_RESET_LEN)-1)<<PDS_CR_PDS_AUDIO_RESET_POS)
#define PDS_CR_PDS_AUDIO_RESET_UMSK                             (~(((1U<<PDS_CR_PDS_AUDIO_RESET_LEN)-1)<<PDS_CR_PDS_AUDIO_RESET_POS))
#define PDS_CR_PDS_AUDIO_MEM_STBY                               PDS_CR_PDS_AUDIO_MEM_STBY
#define PDS_CR_PDS_AUDIO_MEM_STBY_POS                           (22U)
#define PDS_CR_PDS_AUDIO_MEM_STBY_LEN                           (1U)
#define PDS_CR_PDS_AUDIO_MEM_STBY_MSK                           (((1U<<PDS_CR_PDS_AUDIO_MEM_STBY_LEN)-1)<<PDS_CR_PDS_AUDIO_MEM_STBY_POS)
#define PDS_CR_PDS_AUDIO_MEM_STBY_UMSK                          (~(((1U<<PDS_CR_PDS_AUDIO_MEM_STBY_LEN)-1)<<PDS_CR_PDS_AUDIO_MEM_STBY_POS))
#define PDS_CR_PDS_AUDIO_GATE_CLK                               PDS_CR_PDS_AUDIO_GATE_CLK
#define PDS_CR_PDS_AUDIO_GATE_CLK_POS                           (23U)
#define PDS_CR_PDS_AUDIO_GATE_CLK_LEN                           (1U)
#define PDS_CR_PDS_AUDIO_GATE_CLK_MSK                           (((1U<<PDS_CR_PDS_AUDIO_GATE_CLK_LEN)-1)<<PDS_CR_PDS_AUDIO_GATE_CLK_POS)
#define PDS_CR_PDS_AUDIO_GATE_CLK_UMSK                          (~(((1U<<PDS_CR_PDS_AUDIO_GATE_CLK_LEN)-1)<<PDS_CR_PDS_AUDIO_GATE_CLK_POS))
#define PDS_CR_PDS_MISC_PWR_OFF                                 PDS_CR_PDS_MISC_PWR_OFF
#define PDS_CR_PDS_MISC_PWR_OFF_POS                             (24U)
#define PDS_CR_PDS_MISC_PWR_OFF_LEN                             (1U)
#define PDS_CR_PDS_MISC_PWR_OFF_MSK                             (((1U<<PDS_CR_PDS_MISC_PWR_OFF_LEN)-1)<<PDS_CR_PDS_MISC_PWR_OFF_POS)
#define PDS_CR_PDS_MISC_PWR_OFF_UMSK                            (~(((1U<<PDS_CR_PDS_MISC_PWR_OFF_LEN)-1)<<PDS_CR_PDS_MISC_PWR_OFF_POS))
#define PDS_CR_PDS_MISC_RESET                                   PDS_CR_PDS_MISC_RESET
#define PDS_CR_PDS_MISC_RESET_POS                               (25U)
#define PDS_CR_PDS_MISC_RESET_LEN                               (1U)
#define PDS_CR_PDS_MISC_RESET_MSK                               (((1U<<PDS_CR_PDS_MISC_RESET_LEN)-1)<<PDS_CR_PDS_MISC_RESET_POS)
#define PDS_CR_PDS_MISC_RESET_UMSK                              (~(((1U<<PDS_CR_PDS_MISC_RESET_LEN)-1)<<PDS_CR_PDS_MISC_RESET_POS))
#define PDS_CR_PDS_MISC_MEM_STBY                                PDS_CR_PDS_MISC_MEM_STBY
#define PDS_CR_PDS_MISC_MEM_STBY_POS                            (26U)
#define PDS_CR_PDS_MISC_MEM_STBY_LEN                            (1U)
#define PDS_CR_PDS_MISC_MEM_STBY_MSK                            (((1U<<PDS_CR_PDS_MISC_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MISC_MEM_STBY_POS)
#define PDS_CR_PDS_MISC_MEM_STBY_UMSK                           (~(((1U<<PDS_CR_PDS_MISC_MEM_STBY_LEN)-1)<<PDS_CR_PDS_MISC_MEM_STBY_POS))
#define PDS_CR_PDS_MISC_GATE_CLK                                PDS_CR_PDS_MISC_GATE_CLK
#define PDS_CR_PDS_MISC_GATE_CLK_POS                            (27U)
#define PDS_CR_PDS_MISC_GATE_CLK_LEN                            (1U)
#define PDS_CR_PDS_MISC_GATE_CLK_MSK                            (((1U<<PDS_CR_PDS_MISC_GATE_CLK_LEN)-1)<<PDS_CR_PDS_MISC_GATE_CLK_POS)
#define PDS_CR_PDS_MISC_GATE_CLK_UMSK                           (~(((1U<<PDS_CR_PDS_MISC_GATE_CLK_LEN)-1)<<PDS_CR_PDS_MISC_GATE_CLK_POS))

/* 0x1C : pds_stat */
#define PDS_STAT_OFFSET                                         (0x1C)
#define PDS_RO_PDS_STATE                                        PDS_RO_PDS_STATE
#define PDS_RO_PDS_STATE_POS                                    (0U)
#define PDS_RO_PDS_STATE_LEN                                    (5U)
#define PDS_RO_PDS_STATE_MSK                                    (((1U<<PDS_RO_PDS_STATE_LEN)-1)<<PDS_RO_PDS_STATE_POS)
#define PDS_RO_PDS_STATE_UMSK                                   (~(((1U<<PDS_RO_PDS_STATE_LEN)-1)<<PDS_RO_PDS_STATE_POS))
#define PDS_RO_PDS_RF_STATE                                     PDS_RO_PDS_RF_STATE
#define PDS_RO_PDS_RF_STATE_POS                                 (8U)
#define PDS_RO_PDS_RF_STATE_LEN                                 (4U)
#define PDS_RO_PDS_RF_STATE_MSK                                 (((1U<<PDS_RO_PDS_RF_STATE_LEN)-1)<<PDS_RO_PDS_RF_STATE_POS)
#define PDS_RO_PDS_RF_STATE_UMSK                                (~(((1U<<PDS_RO_PDS_RF_STATE_LEN)-1)<<PDS_RO_PDS_RF_STATE_POS))
#define PDS_RESET_EVENT                                         PDS_RESET_EVENT
#define PDS_RESET_EVENT_POS                                     (24U)
#define PDS_RESET_EVENT_LEN                                     (3U)
#define PDS_RESET_EVENT_MSK                                     (((1U<<PDS_RESET_EVENT_LEN)-1)<<PDS_RESET_EVENT_POS)
#define PDS_RESET_EVENT_UMSK                                    (~(((1U<<PDS_RESET_EVENT_LEN)-1)<<PDS_RESET_EVENT_POS))
#define PDS_CLR_RESET_EVENT                                     PDS_CLR_RESET_EVENT
#define PDS_CLR_RESET_EVENT_POS                                 (31U)
#define PDS_CLR_RESET_EVENT_LEN                                 (1U)
#define PDS_CLR_RESET_EVENT_MSK                                 (((1U<<PDS_CLR_RESET_EVENT_LEN)-1)<<PDS_CLR_RESET_EVENT_POS)
#define PDS_CLR_RESET_EVENT_UMSK                                (~(((1U<<PDS_CLR_RESET_EVENT_LEN)-1)<<PDS_CLR_RESET_EVENT_POS))

/* 0x20 : pds_ram1 */
#define PDS_RAM1_OFFSET                                         (0x20)
#define PDS_CR_OCRAM_SLP                                        PDS_CR_OCRAM_SLP
#define PDS_CR_OCRAM_SLP_POS                                    (0U)
#define PDS_CR_OCRAM_SLP_LEN                                    (4U)
#define PDS_CR_OCRAM_SLP_MSK                                    (((1U<<PDS_CR_OCRAM_SLP_LEN)-1)<<PDS_CR_OCRAM_SLP_POS)
#define PDS_CR_OCRAM_SLP_UMSK                                   (~(((1U<<PDS_CR_OCRAM_SLP_LEN)-1)<<PDS_CR_OCRAM_SLP_POS))
#define PDS_CR_OCRAM_RET                                        PDS_CR_OCRAM_RET
#define PDS_CR_OCRAM_RET_POS                                    (4U)
#define PDS_CR_OCRAM_RET_LEN                                    (4U)
#define PDS_CR_OCRAM_RET_MSK                                    (((1U<<PDS_CR_OCRAM_RET_LEN)-1)<<PDS_CR_OCRAM_RET_POS)
#define PDS_CR_OCRAM_RET_UMSK                                   (~(((1U<<PDS_CR_OCRAM_RET_LEN)-1)<<PDS_CR_OCRAM_RET_POS))
#define PDS_CR_PDS_RAM_CLK_CNT                                  PDS_CR_PDS_RAM_CLK_CNT
#define PDS_CR_PDS_RAM_CLK_CNT_POS                              (8U)
#define PDS_CR_PDS_RAM_CLK_CNT_LEN                              (6U)
#define PDS_CR_PDS_RAM_CLK_CNT_MSK                              (((1U<<PDS_CR_PDS_RAM_CLK_CNT_LEN)-1)<<PDS_CR_PDS_RAM_CLK_CNT_POS)
#define PDS_CR_PDS_RAM_CLK_CNT_UMSK                             (~(((1U<<PDS_CR_PDS_RAM_CLK_CNT_LEN)-1)<<PDS_CR_PDS_RAM_CLK_CNT_POS))
#define PDS_CR_PDS_RAM_CLK2_CNT                                 PDS_CR_PDS_RAM_CLK2_CNT
#define PDS_CR_PDS_RAM_CLK2_CNT_POS                             (16U)
#define PDS_CR_PDS_RAM_CLK2_CNT_LEN                             (6U)
#define PDS_CR_PDS_RAM_CLK2_CNT_MSK                             (((1U<<PDS_CR_PDS_RAM_CLK2_CNT_LEN)-1)<<PDS_CR_PDS_RAM_CLK2_CNT_POS)
#define PDS_CR_PDS_RAM_CLK2_CNT_UMSK                            (~(((1U<<PDS_CR_PDS_RAM_CLK2_CNT_LEN)-1)<<PDS_CR_PDS_RAM_CLK2_CNT_POS))
#define PDS_CR_PDS_CTRL_NP_RAM_CLK                              PDS_CR_PDS_CTRL_NP_RAM_CLK
#define PDS_CR_PDS_CTRL_NP_RAM_CLK_POS                          (24U)
#define PDS_CR_PDS_CTRL_NP_RAM_CLK_LEN                          (1U)
#define PDS_CR_PDS_CTRL_NP_RAM_CLK_MSK                          (((1U<<PDS_CR_PDS_CTRL_NP_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_NP_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_NP_RAM_CLK_UMSK                         (~(((1U<<PDS_CR_PDS_CTRL_NP_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_NP_RAM_CLK_POS))
#define PDS_CR_PDS_CTRL_MM_RAM_CLK                              PDS_CR_PDS_CTRL_MM_RAM_CLK
#define PDS_CR_PDS_CTRL_MM_RAM_CLK_POS                          (25U)
#define PDS_CR_PDS_CTRL_MM_RAM_CLK_LEN                          (1U)
#define PDS_CR_PDS_CTRL_MM_RAM_CLK_MSK                          (((1U<<PDS_CR_PDS_CTRL_MM_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_MM_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_MM_RAM_CLK_UMSK                         (~(((1U<<PDS_CR_PDS_CTRL_MM_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_MM_RAM_CLK_POS))
#define PDS_CR_PDS_CTRL_WB_RAM_CLK                              PDS_CR_PDS_CTRL_WB_RAM_CLK
#define PDS_CR_PDS_CTRL_WB_RAM_CLK_POS                          (26U)
#define PDS_CR_PDS_CTRL_WB_RAM_CLK_LEN                          (1U)
#define PDS_CR_PDS_CTRL_WB_RAM_CLK_MSK                          (((1U<<PDS_CR_PDS_CTRL_WB_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_WB_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_WB_RAM_CLK_UMSK                         (~(((1U<<PDS_CR_PDS_CTRL_WB_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_WB_RAM_CLK_POS))
#define PDS_CR_PDS_CTRL_AUDIO_RAM_CLK                           PDS_CR_PDS_CTRL_AUDIO_RAM_CLK
#define PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_POS                       (27U)
#define PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_LEN                       (1U)
#define PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_MSK                       (((1U<<PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_UMSK                      (~(((1U<<PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_AUDIO_RAM_CLK_POS))
#define PDS_CR_PDS_CTRL_MISC_RAM_CLK                            PDS_CR_PDS_CTRL_MISC_RAM_CLK
#define PDS_CR_PDS_CTRL_MISC_RAM_CLK_POS                        (28U)
#define PDS_CR_PDS_CTRL_MISC_RAM_CLK_LEN                        (1U)
#define PDS_CR_PDS_CTRL_MISC_RAM_CLK_MSK                        (((1U<<PDS_CR_PDS_CTRL_MISC_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_MISC_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_MISC_RAM_CLK_UMSK                       (~(((1U<<PDS_CR_PDS_CTRL_MISC_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_MISC_RAM_CLK_POS))
#define PDS_CR_PDS_CTRL_RAM_CLK2                                PDS_CR_PDS_CTRL_RAM_CLK2
#define PDS_CR_PDS_CTRL_RAM_CLK2_POS                            (30U)
#define PDS_CR_PDS_CTRL_RAM_CLK2_LEN                            (1U)
#define PDS_CR_PDS_CTRL_RAM_CLK2_MSK                            (((1U<<PDS_CR_PDS_CTRL_RAM_CLK2_LEN)-1)<<PDS_CR_PDS_CTRL_RAM_CLK2_POS)
#define PDS_CR_PDS_CTRL_RAM_CLK2_UMSK                           (~(((1U<<PDS_CR_PDS_CTRL_RAM_CLK2_LEN)-1)<<PDS_CR_PDS_CTRL_RAM_CLK2_POS))
#define PDS_CR_PDS_CTRL_RAM_CLK                                 PDS_CR_PDS_CTRL_RAM_CLK
#define PDS_CR_PDS_CTRL_RAM_CLK_POS                             (31U)
#define PDS_CR_PDS_CTRL_RAM_CLK_LEN                             (1U)
#define PDS_CR_PDS_CTRL_RAM_CLK_MSK                             (((1U<<PDS_CR_PDS_CTRL_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_RAM_CLK_POS)
#define PDS_CR_PDS_CTRL_RAM_CLK_UMSK                            (~(((1U<<PDS_CR_PDS_CTRL_RAM_CLK_LEN)-1)<<PDS_CR_PDS_CTRL_RAM_CLK_POS))

/* 0x24 : PDS_CTL5 */
#define PDS_CTL5_OFFSET                                         (0x24)
#define PDS_CR_NP_WFI_MASK                                      PDS_CR_NP_WFI_MASK
#define PDS_CR_NP_WFI_MASK_POS                                  (0U)
#define PDS_CR_NP_WFI_MASK_LEN                                  (2U)
#define PDS_CR_NP_WFI_MASK_MSK                                  (((1U<<PDS_CR_NP_WFI_MASK_LEN)-1)<<PDS_CR_NP_WFI_MASK_POS)
#define PDS_CR_NP_WFI_MASK_UMSK                                 (~(((1U<<PDS_CR_NP_WFI_MASK_LEN)-1)<<PDS_CR_NP_WFI_MASK_POS))
#define PDS_CR_MM_WFI_MASK                                      PDS_CR_MM_WFI_MASK
#define PDS_CR_MM_WFI_MASK_POS                                  (2U)
#define PDS_CR_MM_WFI_MASK_LEN                                  (2U)
#define PDS_CR_MM_WFI_MASK_MSK                                  (((1U<<PDS_CR_MM_WFI_MASK_LEN)-1)<<PDS_CR_MM_WFI_MASK_POS)
#define PDS_CR_MM_WFI_MASK_UMSK                                 (~(((1U<<PDS_CR_MM_WFI_MASK_LEN)-1)<<PDS_CR_MM_WFI_MASK_POS))
#define PDS_CR_PICO_WFI_MASK                                    PDS_CR_PICO_WFI_MASK
#define PDS_CR_PICO_WFI_MASK_POS                                (4U)
#define PDS_CR_PICO_WFI_MASK_LEN                                (1U)
#define PDS_CR_PICO_WFI_MASK_MSK                                (((1U<<PDS_CR_PICO_WFI_MASK_LEN)-1)<<PDS_CR_PICO_WFI_MASK_POS)
#define PDS_CR_PICO_WFI_MASK_UMSK                               (~(((1U<<PDS_CR_PICO_WFI_MASK_LEN)-1)<<PDS_CR_PICO_WFI_MASK_POS))

/* 0x28 : PDS_RAM2 */
#define PDS_RAM2_OFFSET                                         (0x28)
#define PDS_CR_WRAM_SLP                                         PDS_CR_WRAM_SLP
#define PDS_CR_WRAM_SLP_POS                                     (0U)
#define PDS_CR_WRAM_SLP_LEN                                     (10U)
#define PDS_CR_WRAM_SLP_MSK                                     (((1U<<PDS_CR_WRAM_SLP_LEN)-1)<<PDS_CR_WRAM_SLP_POS)
#define PDS_CR_WRAM_SLP_UMSK                                    (~(((1U<<PDS_CR_WRAM_SLP_LEN)-1)<<PDS_CR_WRAM_SLP_POS))
#define PDS_CR_WRAM_RET                                         PDS_CR_WRAM_RET
#define PDS_CR_WRAM_RET_POS                                     (10U)
#define PDS_CR_WRAM_RET_LEN                                     (10U)
#define PDS_CR_WRAM_RET_MSK                                     (((1U<<PDS_CR_WRAM_RET_LEN)-1)<<PDS_CR_WRAM_RET_POS)
#define PDS_CR_WRAM_RET_UMSK                                    (~(((1U<<PDS_CR_WRAM_RET_LEN)-1)<<PDS_CR_WRAM_RET_POS))

/* 0x30 : pds_gpio_set_pu_pd */
#define PDS_GPIO_SET_PU_PD_OFFSET                               (0x30)
#define PDS_CR_PDS_GPIO_32_27_PD                                PDS_CR_PDS_GPIO_32_27_PD
#define PDS_CR_PDS_GPIO_32_27_PD_POS                            (0U)
#define PDS_CR_PDS_GPIO_32_27_PD_LEN                            (6U)
#define PDS_CR_PDS_GPIO_32_27_PD_MSK                            (((1U<<PDS_CR_PDS_GPIO_32_27_PD_LEN)-1)<<PDS_CR_PDS_GPIO_32_27_PD_POS)
#define PDS_CR_PDS_GPIO_32_27_PD_UMSK                           (~(((1U<<PDS_CR_PDS_GPIO_32_27_PD_LEN)-1)<<PDS_CR_PDS_GPIO_32_27_PD_POS))
#define PDS_CR_PDS_GPIO_32_27_PU                                PDS_CR_PDS_GPIO_32_27_PU
#define PDS_CR_PDS_GPIO_32_27_PU_POS                            (8U)
#define PDS_CR_PDS_GPIO_32_27_PU_LEN                            (6U)
#define PDS_CR_PDS_GPIO_32_27_PU_MSK                            (((1U<<PDS_CR_PDS_GPIO_32_27_PU_LEN)-1)<<PDS_CR_PDS_GPIO_32_27_PU_POS)
#define PDS_CR_PDS_GPIO_32_27_PU_UMSK                           (~(((1U<<PDS_CR_PDS_GPIO_32_27_PU_LEN)-1)<<PDS_CR_PDS_GPIO_32_27_PU_POS))
#define PDS_CR_PDS_GPIO_38_33_PD                                PDS_CR_PDS_GPIO_38_33_PD
#define PDS_CR_PDS_GPIO_38_33_PD_POS                            (16U)
#define PDS_CR_PDS_GPIO_38_33_PD_LEN                            (6U)
#define PDS_CR_PDS_GPIO_38_33_PD_MSK                            (((1U<<PDS_CR_PDS_GPIO_38_33_PD_LEN)-1)<<PDS_CR_PDS_GPIO_38_33_PD_POS)
#define PDS_CR_PDS_GPIO_38_33_PD_UMSK                           (~(((1U<<PDS_CR_PDS_GPIO_38_33_PD_LEN)-1)<<PDS_CR_PDS_GPIO_38_33_PD_POS))
#define PDS_CR_PDS_GPIO_38_33_PU                                PDS_CR_PDS_GPIO_38_33_PU
#define PDS_CR_PDS_GPIO_38_33_PU_POS                            (24U)
#define PDS_CR_PDS_GPIO_38_33_PU_LEN                            (6U)
#define PDS_CR_PDS_GPIO_38_33_PU_MSK                            (((1U<<PDS_CR_PDS_GPIO_38_33_PU_LEN)-1)<<PDS_CR_PDS_GPIO_38_33_PU_POS)
#define PDS_CR_PDS_GPIO_38_33_PU_UMSK                           (~(((1U<<PDS_CR_PDS_GPIO_38_33_PU_LEN)-1)<<PDS_CR_PDS_GPIO_38_33_PU_POS))

/* 0x40 : pds_gpio_int */
#define PDS_GPIO_INT_OFFSET                                     (0x40)
#define PDS_GPIO_INT_MASK                                       PDS_GPIO_INT_MASK
#define PDS_GPIO_INT_MASK_POS                                   (0U)
#define PDS_GPIO_INT_MASK_LEN                                   (1U)
#define PDS_GPIO_INT_MASK_MSK                                   (((1U<<PDS_GPIO_INT_MASK_LEN)-1)<<PDS_GPIO_INT_MASK_POS)
#define PDS_GPIO_INT_MASK_UMSK                                  (~(((1U<<PDS_GPIO_INT_MASK_LEN)-1)<<PDS_GPIO_INT_MASK_POS))
#define PDS_GPIO_INT_STAT                                       PDS_GPIO_INT_STAT
#define PDS_GPIO_INT_STAT_POS                                   (1U)
#define PDS_GPIO_INT_STAT_LEN                                   (1U)
#define PDS_GPIO_INT_STAT_MSK                                   (((1U<<PDS_GPIO_INT_STAT_LEN)-1)<<PDS_GPIO_INT_STAT_POS)
#define PDS_GPIO_INT_STAT_UMSK                                  (~(((1U<<PDS_GPIO_INT_STAT_LEN)-1)<<PDS_GPIO_INT_STAT_POS))
#define PDS_GPIO_INT_CLR                                        PDS_GPIO_INT_CLR
#define PDS_GPIO_INT_CLR_POS                                    (2U)
#define PDS_GPIO_INT_CLR_LEN                                    (1U)
#define PDS_GPIO_INT_CLR_MSK                                    (((1U<<PDS_GPIO_INT_CLR_LEN)-1)<<PDS_GPIO_INT_CLR_POS)
#define PDS_GPIO_INT_CLR_UMSK                                   (~(((1U<<PDS_GPIO_INT_CLR_LEN)-1)<<PDS_GPIO_INT_CLR_POS))
#define PDS_GPIO_INT_MODE                                       PDS_GPIO_INT_MODE
#define PDS_GPIO_INT_MODE_POS                                   (4U)
#define PDS_GPIO_INT_MODE_LEN                                   (4U)
#define PDS_GPIO_INT_MODE_MSK                                   (((1U<<PDS_GPIO_INT_MODE_LEN)-1)<<PDS_GPIO_INT_MODE_POS)
#define PDS_GPIO_INT_MODE_UMSK                                  (~(((1U<<PDS_GPIO_INT_MODE_LEN)-1)<<PDS_GPIO_INT_MODE_POS))
#define PDS_GPIO_INT_SELECT                                     PDS_GPIO_INT_SELECT
#define PDS_GPIO_INT_SELECT_POS                                 (8U)
#define PDS_GPIO_INT_SELECT_LEN                                 (3U)
#define PDS_GPIO_INT_SELECT_MSK                                 (((1U<<PDS_GPIO_INT_SELECT_LEN)-1)<<PDS_GPIO_INT_SELECT_POS)
#define PDS_GPIO_INT_SELECT_UMSK                                (~(((1U<<PDS_GPIO_INT_SELECT_LEN)-1)<<PDS_GPIO_INT_SELECT_POS))

/* 0x100 : l1c_range_h */
#define PDS_L1C_RANGE_H_OFFSET                                  (0x100)
#define PDS_L1C_RANGE_H                                         PDS_L1C_RANGE_H
#define PDS_L1C_RANGE_H_POS                                     (10U)
#define PDS_L1C_RANGE_H_LEN                                     (21U)
#define PDS_L1C_RANGE_H_MSK                                     (((1U<<PDS_L1C_RANGE_H_LEN)-1)<<PDS_L1C_RANGE_H_POS)
#define PDS_L1C_RANGE_H_UMSK                                    (~(((1U<<PDS_L1C_RANGE_H_LEN)-1)<<PDS_L1C_RANGE_H_POS))

/* 0x104 : l1c_range_l */
#define PDS_L1C_RANGE_L_OFFSET                                  (0x104)
#define PDS_L1C_RANGE_L                                         PDS_L1C_RANGE_L
#define PDS_L1C_RANGE_L_POS                                     (10U)
#define PDS_L1C_RANGE_L_LEN                                     (21U)
#define PDS_L1C_RANGE_L_MSK                                     (((1U<<PDS_L1C_RANGE_L_LEN)-1)<<PDS_L1C_RANGE_L_POS)
#define PDS_L1C_RANGE_L_UMSK                                    (~(((1U<<PDS_L1C_RANGE_L_LEN)-1)<<PDS_L1C_RANGE_L_POS))

/* 0x110 : cpu_core_cfg0 */
#define PDS_CPU_CORE_CFG0_OFFSET                                (0x110)
#define PDS_REG_PICO_CLK_EN                                     PDS_REG_PICO_CLK_EN
#define PDS_REG_PICO_CLK_EN_POS                                 (28U)
#define PDS_REG_PICO_CLK_EN_LEN                                 (1U)
#define PDS_REG_PICO_CLK_EN_MSK                                 (((1U<<PDS_REG_PICO_CLK_EN_LEN)-1)<<PDS_REG_PICO_CLK_EN_POS)
#define PDS_REG_PICO_CLK_EN_UMSK                                (~(((1U<<PDS_REG_PICO_CLK_EN_LEN)-1)<<PDS_REG_PICO_CLK_EN_POS))
#define PDS_E902_DFS_REQ                                        PDS_E902_DFS_REQ
#define PDS_E902_DFS_REQ_POS                                    (29U)
#define PDS_E902_DFS_REQ_LEN                                    (1U)
#define PDS_E902_DFS_REQ_MSK                                    (((1U<<PDS_E902_DFS_REQ_LEN)-1)<<PDS_E902_DFS_REQ_POS)
#define PDS_E902_DFS_REQ_UMSK                                   (~(((1U<<PDS_E902_DFS_REQ_LEN)-1)<<PDS_E902_DFS_REQ_POS))
#define PDS_E902_DFS_ACK                                        PDS_E902_DFS_ACK
#define PDS_E902_DFS_ACK_POS                                    (30U)
#define PDS_E902_DFS_ACK_LEN                                    (1U)
#define PDS_E902_DFS_ACK_MSK                                    (((1U<<PDS_E902_DFS_ACK_LEN)-1)<<PDS_E902_DFS_ACK_POS)
#define PDS_E902_DFS_ACK_UMSK                                   (~(((1U<<PDS_E902_DFS_ACK_LEN)-1)<<PDS_E902_DFS_ACK_POS))

/* 0x114 : cpu_core_cfg1 */
#define PDS_CPU_CORE_CFG1_OFFSET                                (0x114)
#define PDS_REG_PLL_SEL                                         PDS_REG_PLL_SEL
#define PDS_REG_PLL_SEL_POS                                     (4U)
#define PDS_REG_PLL_SEL_LEN                                     (2U)
#define PDS_REG_PLL_SEL_MSK                                     (((1U<<PDS_REG_PLL_SEL_LEN)-1)<<PDS_REG_PLL_SEL_POS)
#define PDS_REG_PLL_SEL_UMSK                                    (~(((1U<<PDS_REG_PLL_SEL_LEN)-1)<<PDS_REG_PLL_SEL_POS))
#define PDS_REG_MCU1_CLK_EN                                     PDS_REG_MCU1_CLK_EN
#define PDS_REG_MCU1_CLK_EN_POS                                 (8U)
#define PDS_REG_MCU1_CLK_EN_LEN                                 (1U)
#define PDS_REG_MCU1_CLK_EN_MSK                                 (((1U<<PDS_REG_MCU1_CLK_EN_LEN)-1)<<PDS_REG_MCU1_CLK_EN_POS)
#define PDS_REG_MCU1_CLK_EN_UMSK                                (~(((1U<<PDS_REG_MCU1_CLK_EN_LEN)-1)<<PDS_REG_MCU1_CLK_EN_POS))
#define PDS_REG_MCU2_CLK_EN                                     PDS_REG_MCU2_CLK_EN
#define PDS_REG_MCU2_CLK_EN_POS                                 (9U)
#define PDS_REG_MCU2_CLK_EN_LEN                                 (1U)
#define PDS_REG_MCU2_CLK_EN_MSK                                 (((1U<<PDS_REG_MCU2_CLK_EN_LEN)-1)<<PDS_REG_MCU2_CLK_EN_POS)
#define PDS_REG_MCU2_CLK_EN_UMSK                                (~(((1U<<PDS_REG_MCU2_CLK_EN_LEN)-1)<<PDS_REG_MCU2_CLK_EN_POS))

/* 0x118 : cpu_core_cfg2 */
#define PDS_CPU_CORE_CFG2_OFFSET                                (0x118)
#define PDS_L1C_CACHEABLE                                       PDS_L1C_CACHEABLE
#define PDS_L1C_CACHEABLE_POS                                   (0U)
#define PDS_L1C_CACHEABLE_LEN                                   (1U)
#define PDS_L1C_CACHEABLE_MSK                                   (((1U<<PDS_L1C_CACHEABLE_LEN)-1)<<PDS_L1C_CACHEABLE_POS)
#define PDS_L1C_CACHEABLE_UMSK                                  (~(((1U<<PDS_L1C_CACHEABLE_LEN)-1)<<PDS_L1C_CACHEABLE_POS))
#define PDS_L1C_CNT_EN                                          PDS_L1C_CNT_EN
#define PDS_L1C_CNT_EN_POS                                      (1U)
#define PDS_L1C_CNT_EN_LEN                                      (1U)
#define PDS_L1C_CNT_EN_MSK                                      (((1U<<PDS_L1C_CNT_EN_LEN)-1)<<PDS_L1C_CNT_EN_POS)
#define PDS_L1C_CNT_EN_UMSK                                     (~(((1U<<PDS_L1C_CNT_EN_LEN)-1)<<PDS_L1C_CNT_EN_POS))
#define PDS_L1C_INVALID_EN                                      PDS_L1C_INVALID_EN
#define PDS_L1C_INVALID_EN_POS                                  (2U)
#define PDS_L1C_INVALID_EN_LEN                                  (1U)
#define PDS_L1C_INVALID_EN_MSK                                  (((1U<<PDS_L1C_INVALID_EN_LEN)-1)<<PDS_L1C_INVALID_EN_POS)
#define PDS_L1C_INVALID_EN_UMSK                                 (~(((1U<<PDS_L1C_INVALID_EN_LEN)-1)<<PDS_L1C_INVALID_EN_POS))
#define PDS_L1C_INVALID_DONE                                    PDS_L1C_INVALID_DONE
#define PDS_L1C_INVALID_DONE_POS                                (3U)
#define PDS_L1C_INVALID_DONE_LEN                                (1U)
#define PDS_L1C_INVALID_DONE_MSK                                (((1U<<PDS_L1C_INVALID_DONE_LEN)-1)<<PDS_L1C_INVALID_DONE_POS)
#define PDS_L1C_INVALID_DONE_UMSK                               (~(((1U<<PDS_L1C_INVALID_DONE_LEN)-1)<<PDS_L1C_INVALID_DONE_POS))
#define PDS_L1C_WT_EN                                           PDS_L1C_WT_EN
#define PDS_L1C_WT_EN_POS                                       (4U)
#define PDS_L1C_WT_EN_LEN                                       (1U)
#define PDS_L1C_WT_EN_MSK                                       (((1U<<PDS_L1C_WT_EN_LEN)-1)<<PDS_L1C_WT_EN_POS)
#define PDS_L1C_WT_EN_UMSK                                      (~(((1U<<PDS_L1C_WT_EN_LEN)-1)<<PDS_L1C_WT_EN_POS))
#define PDS_L1C_WB_EN                                           PDS_L1C_WB_EN
#define PDS_L1C_WB_EN_POS                                       (5U)
#define PDS_L1C_WB_EN_LEN                                       (1U)
#define PDS_L1C_WB_EN_MSK                                       (((1U<<PDS_L1C_WB_EN_LEN)-1)<<PDS_L1C_WB_EN_POS)
#define PDS_L1C_WB_EN_UMSK                                      (~(((1U<<PDS_L1C_WB_EN_LEN)-1)<<PDS_L1C_WB_EN_POS))
#define PDS_L1C_WA_EN                                           PDS_L1C_WA_EN
#define PDS_L1C_WA_EN_POS                                       (6U)
#define PDS_L1C_WA_EN_LEN                                       (1U)
#define PDS_L1C_WA_EN_MSK                                       (((1U<<PDS_L1C_WA_EN_LEN)-1)<<PDS_L1C_WA_EN_POS)
#define PDS_L1C_WA_EN_UMSK                                      (~(((1U<<PDS_L1C_WA_EN_LEN)-1)<<PDS_L1C_WA_EN_POS))
#define PDS_L1C_RANDOM_REPLACE                                  PDS_L1C_RANDOM_REPLACE
#define PDS_L1C_RANDOM_REPLACE_POS                              (7U)
#define PDS_L1C_RANDOM_REPLACE_LEN                              (1U)
#define PDS_L1C_RANDOM_REPLACE_MSK                              (((1U<<PDS_L1C_RANDOM_REPLACE_LEN)-1)<<PDS_L1C_RANDOM_REPLACE_POS)
#define PDS_L1C_RANDOM_REPLACE_UMSK                             (~(((1U<<PDS_L1C_RANDOM_REPLACE_LEN)-1)<<PDS_L1C_RANDOM_REPLACE_POS))
#define PDS_L1C_WAY_DIS                                         PDS_L1C_WAY_DIS
#define PDS_L1C_WAY_DIS_POS                                     (8U)
#define PDS_L1C_WAY_DIS_LEN                                     (2U)
#define PDS_L1C_WAY_DIS_MSK                                     (((1U<<PDS_L1C_WAY_DIS_LEN)-1)<<PDS_L1C_WAY_DIS_POS)
#define PDS_L1C_WAY_DIS_UMSK                                    (~(((1U<<PDS_L1C_WAY_DIS_LEN)-1)<<PDS_L1C_WAY_DIS_POS))
#define PDS_L1C_BYPASS                                          PDS_L1C_BYPASS
#define PDS_L1C_BYPASS_POS                                      (14U)
#define PDS_L1C_BYPASS_LEN                                      (1U)
#define PDS_L1C_BYPASS_MSK                                      (((1U<<PDS_L1C_BYPASS_LEN)-1)<<PDS_L1C_BYPASS_POS)
#define PDS_L1C_BYPASS_UMSK                                     (~(((1U<<PDS_L1C_BYPASS_LEN)-1)<<PDS_L1C_BYPASS_POS))
#define PDS_EARLY_RESP_DIS                                      PDS_EARLY_RESP_DIS
#define PDS_EARLY_RESP_DIS_POS                                  (25U)
#define PDS_EARLY_RESP_DIS_LEN                                  (1U)
#define PDS_EARLY_RESP_DIS_MSK                                  (((1U<<PDS_EARLY_RESP_DIS_LEN)-1)<<PDS_EARLY_RESP_DIS_POS)
#define PDS_EARLY_RESP_DIS_UMSK                                 (~(((1U<<PDS_EARLY_RESP_DIS_LEN)-1)<<PDS_EARLY_RESP_DIS_POS))
#define PDS_WRAP_DIS                                            PDS_WRAP_DIS
#define PDS_WRAP_DIS_POS                                        (26U)
#define PDS_WRAP_DIS_LEN                                        (1U)
#define PDS_WRAP_DIS_MSK                                        (((1U<<PDS_WRAP_DIS_LEN)-1)<<PDS_WRAP_DIS_POS)
#define PDS_WRAP_DIS_UMSK                                       (~(((1U<<PDS_WRAP_DIS_LEN)-1)<<PDS_WRAP_DIS_POS))
#define PDS_L1C_FLUSH_EN                                        PDS_L1C_FLUSH_EN
#define PDS_L1C_FLUSH_EN_POS                                    (28U)
#define PDS_L1C_FLUSH_EN_LEN                                    (1U)
#define PDS_L1C_FLUSH_EN_MSK                                    (((1U<<PDS_L1C_FLUSH_EN_LEN)-1)<<PDS_L1C_FLUSH_EN_POS)
#define PDS_L1C_FLUSH_EN_UMSK                                   (~(((1U<<PDS_L1C_FLUSH_EN_LEN)-1)<<PDS_L1C_FLUSH_EN_POS))
#define PDS_L1C_FLUSH_DONE                                      PDS_L1C_FLUSH_DONE
#define PDS_L1C_FLUSH_DONE_POS                                  (29U)
#define PDS_L1C_FLUSH_DONE_LEN                                  (1U)
#define PDS_L1C_FLUSH_DONE_MSK                                  (((1U<<PDS_L1C_FLUSH_DONE_LEN)-1)<<PDS_L1C_FLUSH_DONE_POS)
#define PDS_L1C_FLUSH_DONE_UMSK                                 (~(((1U<<PDS_L1C_FLUSH_DONE_LEN)-1)<<PDS_L1C_FLUSH_DONE_POS))

/* 0x11C : cpu_core_cfg3 */
#define PDS_CPU_CORE_CFG3_OFFSET                                (0x11C)
#define PDS_PICO_HIT_CNT_LSB                                    PDS_PICO_HIT_CNT_LSB
#define PDS_PICO_HIT_CNT_LSB_POS                                (0U)
#define PDS_PICO_HIT_CNT_LSB_LEN                                (32U)
#define PDS_PICO_HIT_CNT_LSB_MSK                                (((1U<<PDS_PICO_HIT_CNT_LSB_LEN)-1)<<PDS_PICO_HIT_CNT_LSB_POS)
#define PDS_PICO_HIT_CNT_LSB_UMSK                               (~(((1U<<PDS_PICO_HIT_CNT_LSB_LEN)-1)<<PDS_PICO_HIT_CNT_LSB_POS))

/* 0x120 : cpu_core_cfg4 */
#define PDS_CPU_CORE_CFG4_OFFSET                                (0x120)
#define PDS_PICO_HIT_CNT_MSB                                    PDS_PICO_HIT_CNT_MSB
#define PDS_PICO_HIT_CNT_MSB_POS                                (0U)
#define PDS_PICO_HIT_CNT_MSB_LEN                                (32U)
#define PDS_PICO_HIT_CNT_MSB_MSK                                (((1U<<PDS_PICO_HIT_CNT_MSB_LEN)-1)<<PDS_PICO_HIT_CNT_MSB_POS)
#define PDS_PICO_HIT_CNT_MSB_UMSK                               (~(((1U<<PDS_PICO_HIT_CNT_MSB_LEN)-1)<<PDS_PICO_HIT_CNT_MSB_POS))

/* 0x124 : cpu_core_cfg5 */
#define PDS_CPU_CORE_CFG5_OFFSET                                (0x124)
#define PDS_PICO_MISS_CNT                                       PDS_PICO_MISS_CNT
#define PDS_PICO_MISS_CNT_POS                                   (0U)
#define PDS_PICO_MISS_CNT_LEN                                   (32U)
#define PDS_PICO_MISS_CNT_MSK                                   (((1U<<PDS_PICO_MISS_CNT_LEN)-1)<<PDS_PICO_MISS_CNT_POS)
#define PDS_PICO_MISS_CNT_UMSK                                  (~(((1U<<PDS_PICO_MISS_CNT_LEN)-1)<<PDS_PICO_MISS_CNT_POS))

/* 0x128 : cpu_core_cfg6 */
#define PDS_CPU_CORE_CFG6_OFFSET                                (0x128)
#define PDS_L1C_FSM                                             PDS_L1C_FSM
#define PDS_L1C_FSM_POS                                         (28U)
#define PDS_L1C_FSM_LEN                                         (3U)
#define PDS_L1C_FSM_MSK                                         (((1U<<PDS_L1C_FSM_LEN)-1)<<PDS_L1C_FSM_POS)
#define PDS_L1C_FSM_UMSK                                        (~(((1U<<PDS_L1C_FSM_LEN)-1)<<PDS_L1C_FSM_POS))

/* 0x12C : cpu_core_cfg7 */
#define PDS_CPU_CORE_CFG7_OFFSET                                (0x12C)
#define PDS_REG_PICO_DIV                                        PDS_REG_PICO_DIV
#define PDS_REG_PICO_DIV_POS                                    (0U)
#define PDS_REG_PICO_DIV_LEN                                    (8U)
#define PDS_REG_PICO_DIV_MSK                                    (((1U<<PDS_REG_PICO_DIV_LEN)-1)<<PDS_REG_PICO_DIV_POS)
#define PDS_REG_PICO_DIV_UMSK                                   (~(((1U<<PDS_REG_PICO_DIV_LEN)-1)<<PDS_REG_PICO_DIV_POS))
#define PDS_E902_LPMD_B                                         PDS_E902_LPMD_B
#define PDS_E902_LPMD_B_POS                                     (28U)
#define PDS_E902_LPMD_B_LEN                                     (2U)
#define PDS_E902_LPMD_B_MSK                                     (((1U<<PDS_E902_LPMD_B_LEN)-1)<<PDS_E902_LPMD_B_POS)
#define PDS_E902_LPMD_B_UMSK                                    (~(((1U<<PDS_E902_LPMD_B_LEN)-1)<<PDS_E902_LPMD_B_POS))
#define PDS_PICO_RST_MASK                                       PDS_PICO_RST_MASK
#define PDS_PICO_RST_MASK_POS                                   (31U)
#define PDS_PICO_RST_MASK_LEN                                   (1U)
#define PDS_PICO_RST_MASK_MSK                                   (((1U<<PDS_PICO_RST_MASK_LEN)-1)<<PDS_PICO_RST_MASK_POS)
#define PDS_PICO_RST_MASK_UMSK                                  (~(((1U<<PDS_PICO_RST_MASK_LEN)-1)<<PDS_PICO_RST_MASK_POS))

/* 0x130 : cpu_core_cfg8 */
#define PDS_CPU_CORE_CFG8_OFFSET                                (0x130)
#define PDS_E902_RTC_DIV                                        PDS_E902_RTC_DIV
#define PDS_E902_RTC_DIV_POS                                    (0U)
#define PDS_E902_RTC_DIV_LEN                                    (10U)
#define PDS_E902_RTC_DIV_MSK                                    (((1U<<PDS_E902_RTC_DIV_LEN)-1)<<PDS_E902_RTC_DIV_POS)
#define PDS_E902_RTC_DIV_UMSK                                   (~(((1U<<PDS_E902_RTC_DIV_LEN)-1)<<PDS_E902_RTC_DIV_POS))
#define PDS_E902_RTC_RST                                        PDS_E902_RTC_RST
#define PDS_E902_RTC_RST_POS                                    (30U)
#define PDS_E902_RTC_RST_LEN                                    (1U)
#define PDS_E902_RTC_RST_MSK                                    (((1U<<PDS_E902_RTC_RST_LEN)-1)<<PDS_E902_RTC_RST_POS)
#define PDS_E902_RTC_RST_UMSK                                   (~(((1U<<PDS_E902_RTC_RST_LEN)-1)<<PDS_E902_RTC_RST_POS))
#define PDS_E902_RTC_EN                                         PDS_E902_RTC_EN
#define PDS_E902_RTC_EN_POS                                     (31U)
#define PDS_E902_RTC_EN_LEN                                     (1U)
#define PDS_E902_RTC_EN_MSK                                     (((1U<<PDS_E902_RTC_EN_LEN)-1)<<PDS_E902_RTC_EN_POS)
#define PDS_E902_RTC_EN_UMSK                                    (~(((1U<<PDS_E902_RTC_EN_LEN)-1)<<PDS_E902_RTC_EN_POS))

/* 0x134 : cpu_core_cfg9 */
#define PDS_CPU_CORE_CFG9_OFFSET                                (0x134)
#define PDS_PICO_RTC_CNT_L                                      PDS_PICO_RTC_CNT_L
#define PDS_PICO_RTC_CNT_L_POS                                  (0U)
#define PDS_PICO_RTC_CNT_L_LEN                                  (32U)
#define PDS_PICO_RTC_CNT_L_MSK                                  (((1U<<PDS_PICO_RTC_CNT_L_LEN)-1)<<PDS_PICO_RTC_CNT_L_POS)
#define PDS_PICO_RTC_CNT_L_UMSK                                 (~(((1U<<PDS_PICO_RTC_CNT_L_LEN)-1)<<PDS_PICO_RTC_CNT_L_POS))

/* 0x138 : cpu_core_cfg10 */
#define PDS_CPU_CORE_CFG10_OFFSET                               (0x138)
#define PDS_PICO_RTC_CNT_H                                      PDS_PICO_RTC_CNT_H
#define PDS_PICO_RTC_CNT_H_POS                                  (0U)
#define PDS_PICO_RTC_CNT_H_LEN                                  (32U)
#define PDS_PICO_RTC_CNT_H_MSK                                  (((1U<<PDS_PICO_RTC_CNT_H_LEN)-1)<<PDS_PICO_RTC_CNT_H_POS)
#define PDS_PICO_RTC_CNT_H_UMSK                                 (~(((1U<<PDS_PICO_RTC_CNT_H_LEN)-1)<<PDS_PICO_RTC_CNT_H_POS))

/* 0x13C : cpu_core_cfg11 */
#define PDS_CPU_CORE_CFG11_OFFSET                               (0x13C)
#define PDS_PICO_ROM_MISR_DATAOUT                               PDS_PICO_ROM_MISR_DATAOUT
#define PDS_PICO_ROM_MISR_DATAOUT_POS                           (0U)
#define PDS_PICO_ROM_MISR_DATAOUT_LEN                           (32U)
#define PDS_PICO_ROM_MISR_DATAOUT_MSK                           (((1U<<PDS_PICO_ROM_MISR_DATAOUT_LEN)-1)<<PDS_PICO_ROM_MISR_DATAOUT_POS)
#define PDS_PICO_ROM_MISR_DATAOUT_UMSK                          (~(((1U<<PDS_PICO_ROM_MISR_DATAOUT_LEN)-1)<<PDS_PICO_ROM_MISR_DATAOUT_POS))

/* 0x140 : cpu_core_cfg12 */
#define PDS_CPU_CORE_CFG12_OFFSET                               (0x140)
#define PDS_E902_IAHBL_BASE                                     PDS_E902_IAHBL_BASE
#define PDS_E902_IAHBL_BASE_POS                                 (0U)
#define PDS_E902_IAHBL_BASE_LEN                                 (12U)
#define PDS_E902_IAHBL_BASE_MSK                                 (((1U<<PDS_E902_IAHBL_BASE_LEN)-1)<<PDS_E902_IAHBL_BASE_POS)
#define PDS_E902_IAHBL_BASE_UMSK                                (~(((1U<<PDS_E902_IAHBL_BASE_LEN)-1)<<PDS_E902_IAHBL_BASE_POS))
#define PDS_E902_IAHBL_MASK                                     PDS_E902_IAHBL_MASK
#define PDS_E902_IAHBL_MASK_POS                                 (16U)
#define PDS_E902_IAHBL_MASK_LEN                                 (12U)
#define PDS_E902_IAHBL_MASK_MSK                                 (((1U<<PDS_E902_IAHBL_MASK_LEN)-1)<<PDS_E902_IAHBL_MASK_POS)
#define PDS_E902_IAHBL_MASK_UMSK                                (~(((1U<<PDS_E902_IAHBL_MASK_LEN)-1)<<PDS_E902_IAHBL_MASK_POS))

/* 0x144 : cpu_core_cfg13 */
#define PDS_CPU_CORE_CFG13_OFFSET                               (0x144)
#define PDS_E902_RST_ADDR                                       PDS_E902_RST_ADDR
#define PDS_E902_RST_ADDR_POS                                   (0U)
#define PDS_E902_RST_ADDR_LEN                                   (32U)
#define PDS_E902_RST_ADDR_MSK                                   (((1U<<PDS_E902_RST_ADDR_LEN)-1)<<PDS_E902_RST_ADDR_POS)
#define PDS_E902_RST_ADDR_UMSK                                  (~(((1U<<PDS_E902_RST_ADDR_LEN)-1)<<PDS_E902_RST_ADDR_POS))

/* 0x148 : cpu_core_cfg14 */
#define PDS_CPU_CORE_CFG14_OFFSET                               (0x148)
#define PDS_E906_RST_ADDR                                       PDS_E906_RST_ADDR
#define PDS_E906_RST_ADDR_POS                                   (0U)
#define PDS_E906_RST_ADDR_LEN                                   (32U)
#define PDS_E906_RST_ADDR_MSK                                   (((1U<<PDS_E906_RST_ADDR_LEN)-1)<<PDS_E906_RST_ADDR_POS)
#define PDS_E906_RST_ADDR_UMSK                                  (~(((1U<<PDS_E906_RST_ADDR_LEN)-1)<<PDS_E906_RST_ADDR_POS))

/* 0x14C : tzc_pds */
#define PDS_TZC_PDS_OFFSET                                      (0x14C)
#define PDS_CR_E902_CFG_WR_LOCK                                 PDS_CR_E902_CFG_WR_LOCK
#define PDS_CR_E902_CFG_WR_LOCK_POS                             (0U)
#define PDS_CR_E902_CFG_WR_LOCK_LEN                             (1U)
#define PDS_CR_E902_CFG_WR_LOCK_MSK                             (((1U<<PDS_CR_E902_CFG_WR_LOCK_LEN)-1)<<PDS_CR_E902_CFG_WR_LOCK_POS)
#define PDS_CR_E902_CFG_WR_LOCK_UMSK                            (~(((1U<<PDS_CR_E902_CFG_WR_LOCK_LEN)-1)<<PDS_CR_E902_CFG_WR_LOCK_POS))
#define PDS_CR_E906_CFG_WR_LOCK                                 PDS_CR_E906_CFG_WR_LOCK
#define PDS_CR_E906_CFG_WR_LOCK_POS                             (1U)
#define PDS_CR_E906_CFG_WR_LOCK_LEN                             (1U)
#define PDS_CR_E906_CFG_WR_LOCK_MSK                             (((1U<<PDS_CR_E906_CFG_WR_LOCK_LEN)-1)<<PDS_CR_E906_CFG_WR_LOCK_POS)
#define PDS_CR_E906_CFG_WR_LOCK_UMSK                            (~(((1U<<PDS_CR_E906_CFG_WR_LOCK_LEN)-1)<<PDS_CR_E906_CFG_WR_LOCK_POS))

/* 0x300 : rc32m_ctrl0 */
#define PDS_RC32M_CTRL0_OFFSET                                  (0x300)
#define PDS_RC32M_CAL_DONE                                      PDS_RC32M_CAL_DONE
#define PDS_RC32M_CAL_DONE_POS                                  (0U)
#define PDS_RC32M_CAL_DONE_LEN                                  (1U)
#define PDS_RC32M_CAL_DONE_MSK                                  (((1U<<PDS_RC32M_CAL_DONE_LEN)-1)<<PDS_RC32M_CAL_DONE_POS)
#define PDS_RC32M_CAL_DONE_UMSK                                 (~(((1U<<PDS_RC32M_CAL_DONE_LEN)-1)<<PDS_RC32M_CAL_DONE_POS))
#define PDS_RC32M_RDY                                           PDS_RC32M_RDY
#define PDS_RC32M_RDY_POS                                       (1U)
#define PDS_RC32M_RDY_LEN                                       (1U)
#define PDS_RC32M_RDY_MSK                                       (((1U<<PDS_RC32M_RDY_LEN)-1)<<PDS_RC32M_RDY_POS)
#define PDS_RC32M_RDY_UMSK                                      (~(((1U<<PDS_RC32M_RDY_LEN)-1)<<PDS_RC32M_RDY_POS))
#define PDS_RC32M_CAL_INPROGRESS                                PDS_RC32M_CAL_INPROGRESS
#define PDS_RC32M_CAL_INPROGRESS_POS                            (2U)
#define PDS_RC32M_CAL_INPROGRESS_LEN                            (1U)
#define PDS_RC32M_CAL_INPROGRESS_MSK                            (((1U<<PDS_RC32M_CAL_INPROGRESS_LEN)-1)<<PDS_RC32M_CAL_INPROGRESS_POS)
#define PDS_RC32M_CAL_INPROGRESS_UMSK                           (~(((1U<<PDS_RC32M_CAL_INPROGRESS_LEN)-1)<<PDS_RC32M_CAL_INPROGRESS_POS))
#define PDS_RC32M_CAL_DIV                                       PDS_RC32M_CAL_DIV
#define PDS_RC32M_CAL_DIV_POS                                   (3U)
#define PDS_RC32M_CAL_DIV_LEN                                   (2U)
#define PDS_RC32M_CAL_DIV_MSK                                   (((1U<<PDS_RC32M_CAL_DIV_LEN)-1)<<PDS_RC32M_CAL_DIV_POS)
#define PDS_RC32M_CAL_DIV_UMSK                                  (~(((1U<<PDS_RC32M_CAL_DIV_LEN)-1)<<PDS_RC32M_CAL_DIV_POS))
#define PDS_RC32M_CAL_PRECHARGE                                 PDS_RC32M_CAL_PRECHARGE
#define PDS_RC32M_CAL_PRECHARGE_POS                             (5U)
#define PDS_RC32M_CAL_PRECHARGE_LEN                             (1U)
#define PDS_RC32M_CAL_PRECHARGE_MSK                             (((1U<<PDS_RC32M_CAL_PRECHARGE_LEN)-1)<<PDS_RC32M_CAL_PRECHARGE_POS)
#define PDS_RC32M_CAL_PRECHARGE_UMSK                            (~(((1U<<PDS_RC32M_CAL_PRECHARGE_LEN)-1)<<PDS_RC32M_CAL_PRECHARGE_POS))
#define PDS_RC32M_DIG_CODE_FR_CAL                               PDS_RC32M_DIG_CODE_FR_CAL
#define PDS_RC32M_DIG_CODE_FR_CAL_POS                           (6U)
#define PDS_RC32M_DIG_CODE_FR_CAL_LEN                           (8U)
#define PDS_RC32M_DIG_CODE_FR_CAL_MSK                           (((1U<<PDS_RC32M_DIG_CODE_FR_CAL_LEN)-1)<<PDS_RC32M_DIG_CODE_FR_CAL_POS)
#define PDS_RC32M_DIG_CODE_FR_CAL_UMSK                          (~(((1U<<PDS_RC32M_DIG_CODE_FR_CAL_LEN)-1)<<PDS_RC32M_DIG_CODE_FR_CAL_POS))
#define PDS_RC32M_ALLOW_CAL                                     PDS_RC32M_ALLOW_CAL
#define PDS_RC32M_ALLOW_CAL_POS                                 (17U)
#define PDS_RC32M_ALLOW_CAL_LEN                                 (1U)
#define PDS_RC32M_ALLOW_CAL_MSK                                 (((1U<<PDS_RC32M_ALLOW_CAL_LEN)-1)<<PDS_RC32M_ALLOW_CAL_POS)
#define PDS_RC32M_ALLOW_CAL_UMSK                                (~(((1U<<PDS_RC32M_ALLOW_CAL_LEN)-1)<<PDS_RC32M_ALLOW_CAL_POS))
#define PDS_RC32M_REFCLK_HALF                                   PDS_RC32M_REFCLK_HALF
#define PDS_RC32M_REFCLK_HALF_POS                               (18U)
#define PDS_RC32M_REFCLK_HALF_LEN                               (1U)
#define PDS_RC32M_REFCLK_HALF_MSK                               (((1U<<PDS_RC32M_REFCLK_HALF_LEN)-1)<<PDS_RC32M_REFCLK_HALF_POS)
#define PDS_RC32M_REFCLK_HALF_UMSK                              (~(((1U<<PDS_RC32M_REFCLK_HALF_LEN)-1)<<PDS_RC32M_REFCLK_HALF_POS))
#define PDS_RC32M_EXT_CODE_EN                                   PDS_RC32M_EXT_CODE_EN
#define PDS_RC32M_EXT_CODE_EN_POS                               (19U)
#define PDS_RC32M_EXT_CODE_EN_LEN                               (1U)
#define PDS_RC32M_EXT_CODE_EN_MSK                               (((1U<<PDS_RC32M_EXT_CODE_EN_LEN)-1)<<PDS_RC32M_EXT_CODE_EN_POS)
#define PDS_RC32M_EXT_CODE_EN_UMSK                              (~(((1U<<PDS_RC32M_EXT_CODE_EN_LEN)-1)<<PDS_RC32M_EXT_CODE_EN_POS))
#define PDS_RC32M_CAL_EN                                        PDS_RC32M_CAL_EN
#define PDS_RC32M_CAL_EN_POS                                    (20U)
#define PDS_RC32M_CAL_EN_LEN                                    (1U)
#define PDS_RC32M_CAL_EN_MSK                                    (((1U<<PDS_RC32M_CAL_EN_LEN)-1)<<PDS_RC32M_CAL_EN_POS)
#define PDS_RC32M_CAL_EN_UMSK                                   (~(((1U<<PDS_RC32M_CAL_EN_LEN)-1)<<PDS_RC32M_CAL_EN_POS))
#define PDS_RC32M_PD                                            PDS_RC32M_PD
#define PDS_RC32M_PD_POS                                        (21U)
#define PDS_RC32M_PD_LEN                                        (1U)
#define PDS_RC32M_PD_MSK                                        (((1U<<PDS_RC32M_PD_LEN)-1)<<PDS_RC32M_PD_POS)
#define PDS_RC32M_PD_UMSK                                       (~(((1U<<PDS_RC32M_PD_LEN)-1)<<PDS_RC32M_PD_POS))
#define PDS_RC32M_CODE_FR_EXT                                   PDS_RC32M_CODE_FR_EXT
#define PDS_RC32M_CODE_FR_EXT_POS                               (22U)
#define PDS_RC32M_CODE_FR_EXT_LEN                               (8U)
#define PDS_RC32M_CODE_FR_EXT_MSK                               (((1U<<PDS_RC32M_CODE_FR_EXT_LEN)-1)<<PDS_RC32M_CODE_FR_EXT_POS)
#define PDS_RC32M_CODE_FR_EXT_UMSK                              (~(((1U<<PDS_RC32M_CODE_FR_EXT_LEN)-1)<<PDS_RC32M_CODE_FR_EXT_POS))

/* 0x304 : rc32m_ctrl1 */
#define PDS_RC32M_CTRL1_OFFSET                                  (0x304)
#define PDS_RC32M_TEST_EN                                       PDS_RC32M_TEST_EN
#define PDS_RC32M_TEST_EN_POS                                   (0U)
#define PDS_RC32M_TEST_EN_LEN                                   (1U)
#define PDS_RC32M_TEST_EN_MSK                                   (((1U<<PDS_RC32M_TEST_EN_LEN)-1)<<PDS_RC32M_TEST_EN_POS)
#define PDS_RC32M_TEST_EN_UMSK                                  (~(((1U<<PDS_RC32M_TEST_EN_LEN)-1)<<PDS_RC32M_TEST_EN_POS))
#define PDS_RC32M_SOFT_RST                                      PDS_RC32M_SOFT_RST
#define PDS_RC32M_SOFT_RST_POS                                  (1U)
#define PDS_RC32M_SOFT_RST_LEN                                  (1U)
#define PDS_RC32M_SOFT_RST_MSK                                  (((1U<<PDS_RC32M_SOFT_RST_LEN)-1)<<PDS_RC32M_SOFT_RST_POS)
#define PDS_RC32M_SOFT_RST_UMSK                                 (~(((1U<<PDS_RC32M_SOFT_RST_LEN)-1)<<PDS_RC32M_SOFT_RST_POS))
#define PDS_RC32M_CLK_SOFT_RST                                  PDS_RC32M_CLK_SOFT_RST
#define PDS_RC32M_CLK_SOFT_RST_POS                              (2U)
#define PDS_RC32M_CLK_SOFT_RST_LEN                              (1U)
#define PDS_RC32M_CLK_SOFT_RST_MSK                              (((1U<<PDS_RC32M_CLK_SOFT_RST_LEN)-1)<<PDS_RC32M_CLK_SOFT_RST_POS)
#define PDS_RC32M_CLK_SOFT_RST_UMSK                             (~(((1U<<PDS_RC32M_CLK_SOFT_RST_LEN)-1)<<PDS_RC32M_CLK_SOFT_RST_POS))
#define PDS_RC32M_CLK_INV                                       PDS_RC32M_CLK_INV
#define PDS_RC32M_CLK_INV_POS                                   (3U)
#define PDS_RC32M_CLK_INV_LEN                                   (1U)
#define PDS_RC32M_CLK_INV_MSK                                   (((1U<<PDS_RC32M_CLK_INV_LEN)-1)<<PDS_RC32M_CLK_INV_POS)
#define PDS_RC32M_CLK_INV_UMSK                                  (~(((1U<<PDS_RC32M_CLK_INV_LEN)-1)<<PDS_RC32M_CLK_INV_POS))
#define PDS_RC32M_CLK_FORCE_ON                                  PDS_RC32M_CLK_FORCE_ON
#define PDS_RC32M_CLK_FORCE_ON_POS                              (4U)
#define PDS_RC32M_CLK_FORCE_ON_LEN                              (1U)
#define PDS_RC32M_CLK_FORCE_ON_MSK                              (((1U<<PDS_RC32M_CLK_FORCE_ON_LEN)-1)<<PDS_RC32M_CLK_FORCE_ON_POS)
#define PDS_RC32M_CLK_FORCE_ON_UMSK                             (~(((1U<<PDS_RC32M_CLK_FORCE_ON_LEN)-1)<<PDS_RC32M_CLK_FORCE_ON_POS))
#define PDS_RC32M_RESERVED                                      PDS_RC32M_RESERVED
#define PDS_RC32M_RESERVED_POS                                  (24U)
#define PDS_RC32M_RESERVED_LEN                                  (8U)
#define PDS_RC32M_RESERVED_MSK                                  (((1U<<PDS_RC32M_RESERVED_LEN)-1)<<PDS_RC32M_RESERVED_POS)
#define PDS_RC32M_RESERVED_UMSK                                 (~(((1U<<PDS_RC32M_RESERVED_LEN)-1)<<PDS_RC32M_RESERVED_POS))

/* 0x400 : pu_rst_clkpll */
#define PDS_PU_RST_CLKPLL_OFFSET                                (0x400)
#define PDS_CR_PDS_PU_CLKPLL_SFREG                              PDS_CR_PDS_PU_CLKPLL_SFREG
#define PDS_CR_PDS_PU_CLKPLL_SFREG_POS                          (9U)
#define PDS_CR_PDS_PU_CLKPLL_SFREG_LEN                          (1U)
#define PDS_CR_PDS_PU_CLKPLL_SFREG_MSK                          (((1U<<PDS_CR_PDS_PU_CLKPLL_SFREG_LEN)-1)<<PDS_CR_PDS_PU_CLKPLL_SFREG_POS)
#define PDS_CR_PDS_PU_CLKPLL_SFREG_UMSK                         (~(((1U<<PDS_CR_PDS_PU_CLKPLL_SFREG_LEN)-1)<<PDS_CR_PDS_PU_CLKPLL_SFREG_POS))
#define PDS_CR_PDS_PU_CLKPLL                                    PDS_CR_PDS_PU_CLKPLL
#define PDS_CR_PDS_PU_CLKPLL_POS                                (10U)
#define PDS_CR_PDS_PU_CLKPLL_LEN                                (1U)
#define PDS_CR_PDS_PU_CLKPLL_MSK                                (((1U<<PDS_CR_PDS_PU_CLKPLL_LEN)-1)<<PDS_CR_PDS_PU_CLKPLL_POS)
#define PDS_CR_PDS_PU_CLKPLL_UMSK                               (~(((1U<<PDS_CR_PDS_PU_CLKPLL_LEN)-1)<<PDS_CR_PDS_PU_CLKPLL_POS))


struct  pds_reg {
    /* 0x0 : PDS_CTL */
    union {
        struct {
            uint32_t pds_start_ps                   :  1; /* [    0],        w1p,        0x0 */
            uint32_t cr_sleep_forever               :  1; /* [    1],        r/w,        0x0 */
            uint32_t cr_xtal_force_off              :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_pds_wifi_save_state         :  1; /* [    3],        r/w,        0x0 */
            uint32_t cr_pds_pd_dcdc                 :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_pds_pd_bg_sys               :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_gpio_ie_pu_pd      :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_pu_flash           :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_pds_gate_clk                :  1; /* [    8],        r/w,        0x1 */
            uint32_t cr_pds_mem_stby                :  1; /* [    9],        r/w,        0x1 */
            uint32_t cr_sw_pu_flash                 :  1; /* [   10],        r/w,        0x1 */
            uint32_t cr_pds_iso_en                  :  1; /* [   11],        r/w,        0x1 */
            uint32_t cr_pds_wait_xtal_rdy           :  1; /* [   12],        r/w,        0x0 */
            uint32_t cr_pds_pwr_off                 :  1; /* [   13],        r/w,        0x1 */
            uint32_t cr_pds_pd_xtal                 :  1; /* [   14],        r/w,        0x1 */
            uint32_t cr_pds_ctrl_soc_enb            :  1; /* [   15],        r/w,        0x0 */
            uint32_t cr_pds_rst_soc                 :  1; /* [   16],        r/w,        0x0 */
            uint32_t cr_pds_rc32m_off_dis           :  1; /* [   17],        r/w,        0x0 */
            uint32_t cr_pds_dcdc_vsel_en            :  1; /* [   18],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_aupll_pd           :  1; /* [   19],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_ethpll_pd          :  1; /* [   20],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_cpupll_pd          :  1; /* [   21],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_wifipll_pd         :  1; /* [   22],        r/w,        0x0 */
            uint32_t cr_pds_dcdc_vol                :  5; /* [27:23],        r/w,        0x8 */
            uint32_t cr_pds_ctrl_rf                 :  2; /* [29:28],        r/w,        0x1 */
            uint32_t cr_pds_start_use_tbtt_sleep    :  1; /* [   30],        r/w,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_CTL;

    /* 0x4 : PDS_TIME1 */
    union {
        struct {
            uint32_t cr_sleep_duration              : 32; /* [31: 0],        r/w,      0xca8 */
        }BF;
        uint32_t WORD;
    } PDS_TIME1;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[4];

    /* 0xC : PDS_INT */
    union {
        struct {
            uint32_t ro_pds_wake_int                :  1; /* [    0],          r,        0x0 */
            uint32_t ro_pds_rf_done_int             :  1; /* [    1],          r,        0x0 */
            uint32_t ro_pds_wifi_tbtt_sleep_irq     :  1; /* [    2],          r,        0x0 */
            uint32_t ro_pds_wifi_tbtt_wakeup_irq    :  1; /* [    3],          r,        0x0 */
            uint32_t cr_pds_wake_int_mask           :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_pds_rf_done_int_mask        :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_pds_wifi_tbtt_sleep_irq_mask :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_pds_wifi_tbtt_wakeup_irq_mask :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_pds_int_clr                 :  1; /* [    8],        r/w,        0x0 */
            uint32_t reserved_9                     :  1; /* [    9],       rsvd,        0x0 */
            uint32_t cr_pds_wakeup_src_en           : 11; /* [20:10],        r/w,      0x7ff */
            uint32_t ro_pds_wakeup_event            : 11; /* [31:21],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_INT;

    /* 0x10 : PDS_CTL2 */
    union {
        struct {
            uint32_t cr_pds_force_np_pwr_off        :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_pds_force_mm_pwr_off        :  1; /* [    1],        r/w,        0x1 */
            uint32_t cr_pds_force_wb_pwr_off        :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_pds_force_audio_pwr_off     :  1; /* [    3],        r/w,        0x0 */
            uint32_t cr_pds_force_np_iso_en         :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_pds_force_mm_iso_en         :  1; /* [    5],        r/w,        0x1 */
            uint32_t cr_pds_force_wb_iso_en         :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_pds_force_audio_iso_en      :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_pds_force_np_pds_rst        :  1; /* [    8],        r/w,        0x0 */
            uint32_t cr_pds_force_mm_pds_rst        :  1; /* [    9],        r/w,        0x1 */
            uint32_t cr_pds_force_wb_pds_rst        :  1; /* [   10],        r/w,        0x0 */
            uint32_t cr_pds_force_audio_pds_rst     :  1; /* [   11],        r/w,        0x0 */
            uint32_t cr_pds_force_np_mem_stby       :  1; /* [   12],        r/w,        0x0 */
            uint32_t cr_pds_force_mm_mem_stby       :  1; /* [   13],        r/w,        0x1 */
            uint32_t cr_pds_force_wb_mem_stby       :  1; /* [   14],        r/w,        0x0 */
            uint32_t cr_pds_force_audio_mem_stby    :  1; /* [   15],        r/w,        0x0 */
            uint32_t cr_pds_force_np_gate_clk       :  1; /* [   16],        r/w,        0x0 */
            uint32_t cr_pds_force_mm_gate_clk       :  1; /* [   17],        r/w,        0x1 */
            uint32_t cr_pds_force_wb_gate_clk       :  1; /* [   18],        r/w,        0x0 */
            uint32_t cr_pds_force_audio_gate_clk    :  1; /* [   19],        r/w,        0x0 */
            uint32_t reserved_20_23                 :  4; /* [23:20],       rsvd,        0x0 */
            uint32_t cr_pds_np_lv_pwr               :  1; /* [   24],        r/w,        0x0 */
            uint32_t cr_pds_mm_lv_pwr               :  1; /* [   25],        r/w,        0x0 */
            uint32_t cr_pds_wb_lv_pwr               :  1; /* [   26],        r/w,        0x0 */
            uint32_t cr_pds_audio_lv_pwr            :  1; /* [   27],        r/w,        0x0 */
            uint32_t cr_pds_misc_lv_pwr             :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29_30                 :  2; /* [30:29],       rsvd,        0x0 */
            uint32_t cr_pds_lv_pwr                  :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_CTL2;

    /* 0x14 : PDS_CTL3 */
    union {
        struct {
            uint32_t reserved_0                     :  1; /* [    0],       rsvd,        0x0 */
            uint32_t cr_pds_force_misc_pwr_off      :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t cr_pds_force_misc_iso_en       :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_6                   :  2; /* [ 6: 5],       rsvd,        0x0 */
            uint32_t cr_pds_force_misc_pds_rst      :  1; /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_9                   :  2; /* [ 9: 8],       rsvd,        0x0 */
            uint32_t cr_pds_force_misc_mem_stby     :  1; /* [   10],        r/w,        0x0 */
            uint32_t reserved_11_12                 :  2; /* [12:11],       rsvd,        0x0 */
            uint32_t cr_pds_force_misc_gate_clk     :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_23                 : 10; /* [23:14],       rsvd,        0x0 */
            uint32_t cr_pds_np_iso_en               :  1; /* [   24],        r/w,        0x1 */
            uint32_t reserved_25                    :  1; /* [   25],       rsvd,        0x0 */
            uint32_t cr_pds_mm_iso_en               :  1; /* [   26],        r/w,        0x1 */
            uint32_t cr_pds_wb_iso_en               :  1; /* [   27],        r/w,        0x1 */
            uint32_t reserved_28                    :  1; /* [   28],       rsvd,        0x0 */
            uint32_t cr_pds_audio_iso_en            :  1; /* [   29],        r/w,        0x1 */
            uint32_t cr_pds_misc_iso_en             :  1; /* [   30],        r/w,        0x1 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_CTL3;

    /* 0x18 : PDS_CTL4 */
    union {
        struct {
            uint32_t cr_pds_np_pwr_off              :  1; /* [    0],        r/w,        0x1 */
            uint32_t cr_pds_np_reset                :  1; /* [    1],        r/w,        0x1 */
            uint32_t cr_pds_np_mem_stby             :  1; /* [    2],        r/w,        0x1 */
            uint32_t cr_pds_np_gate_clk             :  1; /* [    3],        r/w,        0x1 */
            uint32_t reserved_4_7                   :  4; /* [ 7: 4],       rsvd,        0x0 */
            uint32_t cr_pds_mm_pwr_off              :  1; /* [    8],        r/w,        0x1 */
            uint32_t cr_pds_mm_reset                :  1; /* [    9],        r/w,        0x1 */
            uint32_t cr_pds_mm_mem_stby             :  1; /* [   10],        r/w,        0x1 */
            uint32_t cr_pds_mm_gate_clk             :  1; /* [   11],        r/w,        0x1 */
            uint32_t cr_pds_wb_pwr_off              :  1; /* [   12],        r/w,        0x1 */
            uint32_t cr_pds_wb_reset                :  1; /* [   13],        r/w,        0x1 */
            uint32_t cr_pds_wb_mem_stby             :  1; /* [   14],        r/w,        0x1 */
            uint32_t cr_pds_wb_gate_clk             :  1; /* [   15],        r/w,        0x1 */
            uint32_t reserved_16_19                 :  4; /* [19:16],       rsvd,        0x0 */
            uint32_t cr_pds_audio_pwr_off           :  1; /* [   20],        r/w,        0x1 */
            uint32_t cr_pds_audio_reset             :  1; /* [   21],        r/w,        0x1 */
            uint32_t cr_pds_audio_mem_stby          :  1; /* [   22],        r/w,        0x1 */
            uint32_t cr_pds_audio_gate_clk          :  1; /* [   23],        r/w,        0x1 */
            uint32_t cr_pds_misc_pwr_off            :  1; /* [   24],        r/w,        0x1 */
            uint32_t cr_pds_misc_reset              :  1; /* [   25],        r/w,        0x1 */
            uint32_t cr_pds_misc_mem_stby           :  1; /* [   26],        r/w,        0x1 */
            uint32_t cr_pds_misc_gate_clk           :  1; /* [   27],        r/w,        0x1 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_CTL4;

    /* 0x1C : pds_stat */
    union {
        struct {
            uint32_t ro_pds_state                   :  5; /* [ 4: 0],          r,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t ro_pds_rf_state                :  4; /* [11: 8],          r,        0x0 */
            uint32_t reserved_12_23                 : 12; /* [23:12],       rsvd,        0x0 */
            uint32_t pds_reset_event                :  3; /* [26:24],          r,        0x0 */
            uint32_t reserved_27_30                 :  4; /* [30:27],       rsvd,        0x0 */
            uint32_t pds_clr_reset_event            :  1; /* [   31],        w1c,        0x0 */
        }BF;
        uint32_t WORD;
    } pds_stat;

    /* 0x20 : pds_ram1 */
    union {
        struct {
            uint32_t cr_ocram_slp                   :  4; /* [ 3: 0],        r/w,        0x0 */
            uint32_t cr_ocram_ret                   :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t cr_pds_ram_clk_cnt             :  6; /* [13: 8],        r/w,        0x8 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t cr_pds_ram_clk2_cnt            :  6; /* [21:16],        r/w,       0x18 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t cr_pds_ctrl_np_ram_clk         :  1; /* [   24],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_mm_ram_clk         :  1; /* [   25],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_wb_ram_clk         :  1; /* [   26],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_audio_ram_clk      :  1; /* [   27],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_misc_ram_clk       :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29                    :  1; /* [   29],       rsvd,        0x0 */
            uint32_t cr_pds_ctrl_ram_clk2           :  1; /* [   30],        r/w,        0x0 */
            uint32_t cr_pds_ctrl_ram_clk            :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } pds_ram1;

    /* 0x24 : PDS_CTL5 */
    union {
        struct {
            uint32_t cr_np_wfi_mask                 :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t cr_mm_wfi_mask                 :  2; /* [ 3: 2],        r/w,        0x0 */
            uint32_t cr_pico_wfi_mask               :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_CTL5;

    /* 0x28 : PDS_RAM2 */
    union {
        struct {
            uint32_t cr_wram_slp                    : 10; /* [ 9: 0],        r/w,        0x0 */
            uint32_t cr_wram_ret                    : 10; /* [19:10],        r/w,        0x0 */
            uint32_t reserved_20_31                 : 12; /* [31:20],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } PDS_RAM2;

    /* 0x2c  reserved */
    uint8_t RESERVED0x2c[4];

    /* 0x30 : pds_gpio_set_pu_pd */
    union {
        struct {
            uint32_t cr_pds_gpio_32_27_pd           :  6; /* [ 5: 0],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t cr_pds_gpio_32_27_pu           :  6; /* [13: 8],        r/w,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t cr_pds_gpio_38_33_pd           :  6; /* [21:16],        r/w,        0x0 */
            uint32_t reserved_22_23                 :  2; /* [23:22],       rsvd,        0x0 */
            uint32_t cr_pds_gpio_38_33_pu           :  6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } pds_gpio_set_pu_pd;

    /* 0x34  reserved */
    uint8_t RESERVED0x34[12];

    /* 0x40 : pds_gpio_int */
    union {
        struct {
            uint32_t pds_gpio_int_mask              :  1; /* [    0],        r/w,        0x1 */
            uint32_t pds_gpio_int_stat              :  1; /* [    1],          r,        0x0 */
            uint32_t pds_gpio_int_clr               :  1; /* [    2],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t pds_gpio_int_mode              :  4; /* [ 7: 4],        r/w,        0x0 */
            uint32_t pds_gpio_int_select            :  3; /* [10: 8],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } pds_gpio_int;

    /* 0x44  reserved */
    uint8_t RESERVED0x44[188];

    /* 0x100 : l1c_range_h */
    union {
        struct {
            uint32_t reserved_0_9                   : 10; /* [ 9: 0],       rsvd,        0x0 */
            uint32_t l1c_range_h                    : 21; /* [30:10],        r/w,  0x1c00000 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_range_h;

    /* 0x104 : l1c_range_l */
    union {
        struct {
            uint32_t reserved_0_9                   : 10; /* [ 9: 0],       rsvd,        0x0 */
            uint32_t l1c_range_l                    : 21; /* [30:10],        r/w,  0x1400000 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } l1c_range_l;

    /* 0x108  reserved */
    uint8_t RESERVED0x108[8];

    /* 0x110 : cpu_core_cfg0 */
    union {
        struct {
            uint32_t reserved_0_27                  : 28; /* [27: 0],       rsvd,        0x0 */
            uint32_t reg_pico_clk_en                :  1; /* [   28],        r/w,        0x0 */
            uint32_t e902_dfs_req                   :  1; /* [   29],        r/w,        0x0 */
            uint32_t e902_dfs_ack                   :  1; /* [   30],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg0;

    /* 0x114 : cpu_core_cfg1 */
    union {
        struct {
            uint32_t reserved_0_3                   :  4; /* [ 3: 0],       rsvd,        0x0 */
            uint32_t reg_pll_sel                    :  2; /* [ 5: 4],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_mcu1_clk_en                :  1; /* [    8],        r/w,        0x1 */
            uint32_t reg_mcu2_clk_en                :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg1;

    /* 0x118 : cpu_core_cfg2 */
    union {
        struct {
            uint32_t l1c_cacheable                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t l1c_cnt_en                     :  1; /* [    1],        r/w,        0x0 */
            uint32_t l1c_invalid_en                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t l1c_invalid_done               :  1; /* [    3],          r,        0x0 */
            uint32_t l1c_wt_en                      :  1; /* [    4],        r/w,        0x0 */
            uint32_t l1c_wb_en                      :  1; /* [    5],        r/w,        0x0 */
            uint32_t l1c_wa_en                      :  1; /* [    6],        r/w,        0x0 */
            uint32_t l1c_random_replace             :  1; /* [    7],        r/w,        0x0 */
            uint32_t l1c_way_dis                    :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_13                 :  4; /* [13:10],       rsvd,        0x0 */
            uint32_t l1c_bypass                     :  1; /* [   14],        r/w,        0x1 */
            uint32_t reserved_15_24                 : 10; /* [24:15],       rsvd,        0x0 */
            uint32_t early_resp_dis                 :  1; /* [   25],        r/w,        0x0 */
            uint32_t wrap_dis                       :  1; /* [   26],        r/w,        0x0 */
            uint32_t reserved_27                    :  1; /* [   27],       rsvd,        0x0 */
            uint32_t l1c_flush_en                   :  1; /* [   28],        r/w,        0x0 */
            uint32_t l1c_flush_done                 :  1; /* [   29],          r,        0x0 */
            uint32_t reserved_31_30                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg2;

    /* 0x11C : cpu_core_cfg3 */
    union {
        struct {
            uint32_t pico_hit_cnt_lsb               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg3;

    /* 0x120 : cpu_core_cfg4 */
    union {
        struct {
            uint32_t pico_hit_cnt_msb               : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg4;

    /* 0x124 : cpu_core_cfg5 */
    union {
        struct {
            uint32_t pico_miss_cnt                  : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg5;

    /* 0x128 : cpu_core_cfg6 */
    union {
        struct {
            uint32_t reserved_0_27                  : 28; /* [27: 0],       rsvd,        0x0 */
            uint32_t l1c_fsm                        :  3; /* [30:28],          r,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg6;

    /* 0x12C : cpu_core_cfg7 */
    union {
        struct {
            uint32_t reg_pico_div                   :  8; /* [ 7: 0],        r/w,        0x1 */
            uint32_t reserved_8_27                  : 20; /* [27: 8],       rsvd,        0x0 */
            uint32_t e902_lpmd_b                    :  2; /* [29:28],          r,        0x0 */
            uint32_t reserved_30                    :  1; /* [   30],       rsvd,        0x0 */
            uint32_t pico_rst_mask                  :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg7;

    /* 0x130 : cpu_core_cfg8 */
    union {
        struct {
            uint32_t e902_rtc_div                   : 10; /* [ 9: 0],        r/w,        0xa */
            uint32_t reserved_10_29                 : 20; /* [29:10],       rsvd,        0x0 */
            uint32_t e902_rtc_rst                   :  1; /* [   30],        r/w,        0x0 */
            uint32_t e902_rtc_en                    :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg8;

    /* 0x134 : cpu_core_cfg9 */
    union {
        struct {
            uint32_t pico_rtc_cnt_l                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg9;

    /* 0x138 : cpu_core_cfg10 */
    union {
        struct {
            uint32_t pico_rtc_cnt_h                 : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg10;

    /* 0x13C : cpu_core_cfg11 */
    union {
        struct {
            uint32_t pico_rom_misr_dataout          : 32; /* [31: 0],          r,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg11;

    /* 0x140 : cpu_core_cfg12 */
    union {
        struct {
            uint32_t e902_iahbl_base                : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t e902_iahbl_mask                : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg12;

    /* 0x144 : cpu_core_cfg13 */
    union {
        struct {
            uint32_t e902_rst_addr                  : 32; /* [31: 0],        r/w, 0x22010000 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg13;

    /* 0x148 : cpu_core_cfg14 */
    union {
        struct {
            uint32_t e906_rst_addr                  : 32; /* [31: 0],        r/w, 0xc1000000 */
        }BF;
        uint32_t WORD;
    } cpu_core_cfg14;

    /* 0x14C : tzc_pds */
    union {
        struct {
            uint32_t cr_e902_cfg_wr_lock            :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_e906_cfg_wr_lock            :  1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } tzc_pds;

    /* 0x150  reserved */
    uint8_t RESERVED0x150[432];

    /* 0x300 : rc32m_ctrl0 */
    union {
        struct {
            uint32_t rc32m_cal_done                 :  1; /* [    0],          r,        0x0 */
            uint32_t rc32m_rdy                      :  1; /* [    1],          r,        0x0 */
            uint32_t rc32m_cal_inprogress           :  1; /* [    2],          r,        0x0 */
            uint32_t rc32m_cal_div                  :  2; /* [ 4: 3],        r/w,        0x3 */
            uint32_t rc32m_cal_precharge            :  1; /* [    5],          r,        0x0 */
            uint32_t rc32m_dig_code_fr_cal          :  8; /* [13: 6],          r,        0x0 */
            uint32_t reserved_14_16                 :  3; /* [16:14],       rsvd,        0x0 */
            uint32_t rc32m_allow_cal                :  1; /* [   17],        r/w,        0x0 */
            uint32_t rc32m_refclk_half              :  1; /* [   18],        r/w,        0x0 */
            uint32_t rc32m_ext_code_en              :  1; /* [   19],        r/w,        0x1 */
            uint32_t rc32m_cal_en                   :  1; /* [   20],        r/w,        0x0 */
            uint32_t rc32m_pd                       :  1; /* [   21],        r/w,        0x0 */
            uint32_t rc32m_code_fr_ext              :  8; /* [29:22],        r/w,       0x60 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } rc32m_ctrl0;

    /* 0x304 : rc32m_ctrl1 */
    union {
        struct {
            uint32_t rc32m_test_en                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t rc32m_soft_rst                 :  1; /* [    1],        r/w,        0x0 */
            uint32_t rc32m_clk_soft_rst             :  1; /* [    2],        r/w,        0x0 */
            uint32_t rc32m_clk_inv                  :  1; /* [    3],        r/w,        0x0 */
            uint32_t rc32m_clk_force_on             :  1; /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_23                  : 19; /* [23: 5],       rsvd,        0x0 */
            uint32_t rc32m_reserved                 :  8; /* [31:24],        r/w,        0xf */
        }BF;
        uint32_t WORD;
    } rc32m_ctrl1;

    /* 0x308  reserved */
    uint8_t RESERVED0x308[248];

    /* 0x400 : pu_rst_clkpll */
    union {
        struct {
            uint32_t reserved_0_8                   :  9; /* [ 8: 0],       rsvd,        0x0 */
            uint32_t cr_pds_pu_clkpll_sfreg         :  1; /* [    9],        r/w,        0x0 */
            uint32_t cr_pds_pu_clkpll               :  1; /* [   10],        r/w,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } pu_rst_clkpll;

};

typedef volatile struct pds_reg pds_reg_t;


#endif  /* __PDS_REG_H__ */
