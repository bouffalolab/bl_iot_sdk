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
#ifndef  __AON_REG_H__
#define  __AON_REG_H__

#include "bl808.h"

/* 0x800 : aon */
#define AON_OFFSET                                              (0x800)
#define AON_RESV                                                AON_RESV
#define AON_RESV_POS                                            (0U)
#define AON_RESV_LEN                                            (8U)
#define AON_RESV_MSK                                            (((1U<<AON_RESV_LEN)-1)<<AON_RESV_POS)
#define AON_RESV_UMSK                                           (~(((1U<<AON_RESV_LEN)-1)<<AON_RESV_POS))
#define AON_PU_AON_DC_TBUF                                      AON_PU_AON_DC_TBUF
#define AON_PU_AON_DC_TBUF_POS                                  (12U)
#define AON_PU_AON_DC_TBUF_LEN                                  (1U)
#define AON_PU_AON_DC_TBUF_MSK                                  (((1U<<AON_PU_AON_DC_TBUF_LEN)-1)<<AON_PU_AON_DC_TBUF_POS)
#define AON_PU_AON_DC_TBUF_UMSK                                 (~(((1U<<AON_PU_AON_DC_TBUF_LEN)-1)<<AON_PU_AON_DC_TBUF_POS))
#define AON_LDO11_RT_PULLDOWN                                   AON_LDO11_RT_PULLDOWN
#define AON_LDO11_RT_PULLDOWN_POS                               (20U)
#define AON_LDO11_RT_PULLDOWN_LEN                               (1U)
#define AON_LDO11_RT_PULLDOWN_MSK                               (((1U<<AON_LDO11_RT_PULLDOWN_LEN)-1)<<AON_LDO11_RT_PULLDOWN_POS)
#define AON_LDO11_RT_PULLDOWN_UMSK                              (~(((1U<<AON_LDO11_RT_PULLDOWN_LEN)-1)<<AON_LDO11_RT_PULLDOWN_POS))
#define AON_LDO11_RT_PULLDOWN_SEL                               AON_LDO11_RT_PULLDOWN_SEL
#define AON_LDO11_RT_PULLDOWN_SEL_POS                           (21U)
#define AON_LDO11_RT_PULLDOWN_SEL_LEN                           (1U)
#define AON_LDO11_RT_PULLDOWN_SEL_MSK                           (((1U<<AON_LDO11_RT_PULLDOWN_SEL_LEN)-1)<<AON_LDO11_RT_PULLDOWN_SEL_POS)
#define AON_LDO11_RT_PULLDOWN_SEL_UMSK                          (~(((1U<<AON_LDO11_RT_PULLDOWN_SEL_LEN)-1)<<AON_LDO11_RT_PULLDOWN_SEL_POS))
#define AON_SW_PU_LDO11_RT                                      AON_SW_PU_LDO11_RT
#define AON_SW_PU_LDO11_RT_POS                                  (22U)
#define AON_SW_PU_LDO11_RT_LEN                                  (1U)
#define AON_SW_PU_LDO11_RT_MSK                                  (((1U<<AON_SW_PU_LDO11_RT_LEN)-1)<<AON_SW_PU_LDO11_RT_POS)
#define AON_SW_PU_LDO11_RT_UMSK                                 (~(((1U<<AON_SW_PU_LDO11_RT_LEN)-1)<<AON_SW_PU_LDO11_RT_POS))

/* 0x804 : aon_common */
#define AON_COMMON_OFFSET                                       (0x804)
#define AON_TMUX_AON                                            AON_TMUX_AON
#define AON_TMUX_AON_POS                                        (0U)
#define AON_TMUX_AON_LEN                                        (3U)
#define AON_TMUX_AON_MSK                                        (((1U<<AON_TMUX_AON_LEN)-1)<<AON_TMUX_AON_POS)
#define AON_TMUX_AON_UMSK                                       (~(((1U<<AON_TMUX_AON_LEN)-1)<<AON_TMUX_AON_POS))
#define AON_TEN_AON                                             AON_TEN_AON
#define AON_TEN_AON_POS                                         (4U)
#define AON_TEN_AON_LEN                                         (1U)
#define AON_TEN_AON_MSK                                         (((1U<<AON_TEN_AON_LEN)-1)<<AON_TEN_AON_POS)
#define AON_TEN_AON_UMSK                                        (~(((1U<<AON_TEN_AON_LEN)-1)<<AON_TEN_AON_POS))
#define AON_DTEN_XTAL32K                                        AON_DTEN_XTAL32K
#define AON_DTEN_XTAL32K_POS                                    (5U)
#define AON_DTEN_XTAL32K_LEN                                    (1U)
#define AON_DTEN_XTAL32K_MSK                                    (((1U<<AON_DTEN_XTAL32K_LEN)-1)<<AON_DTEN_XTAL32K_POS)
#define AON_DTEN_XTAL32K_UMSK                                   (~(((1U<<AON_DTEN_XTAL32K_LEN)-1)<<AON_DTEN_XTAL32K_POS))
#define AON_TEN_XTAL32K                                         AON_TEN_XTAL32K
#define AON_TEN_XTAL32K_POS                                     (6U)
#define AON_TEN_XTAL32K_LEN                                     (1U)
#define AON_TEN_XTAL32K_MSK                                     (((1U<<AON_TEN_XTAL32K_LEN)-1)<<AON_TEN_XTAL32K_POS)
#define AON_TEN_XTAL32K_UMSK                                    (~(((1U<<AON_TEN_XTAL32K_LEN)-1)<<AON_TEN_XTAL32K_POS))
#define AON_TEN_VDDCORE_AON                                     AON_TEN_VDDCORE_AON
#define AON_TEN_VDDCORE_AON_POS                                 (8U)
#define AON_TEN_VDDCORE_AON_LEN                                 (1U)
#define AON_TEN_VDDCORE_AON_MSK                                 (((1U<<AON_TEN_VDDCORE_AON_LEN)-1)<<AON_TEN_VDDCORE_AON_POS)
#define AON_TEN_VDDCORE_AON_UMSK                                (~(((1U<<AON_TEN_VDDCORE_AON_LEN)-1)<<AON_TEN_VDDCORE_AON_POS))
#define AON_PMIP_DC_TP_OUT_EN_AON                               AON_PMIP_DC_TP_OUT_EN_AON
#define AON_PMIP_DC_TP_OUT_EN_AON_POS                           (9U)
#define AON_PMIP_DC_TP_OUT_EN_AON_LEN                           (1U)
#define AON_PMIP_DC_TP_OUT_EN_AON_MSK                           (((1U<<AON_PMIP_DC_TP_OUT_EN_AON_LEN)-1)<<AON_PMIP_DC_TP_OUT_EN_AON_POS)
#define AON_PMIP_DC_TP_OUT_EN_AON_UMSK                          (~(((1U<<AON_PMIP_DC_TP_OUT_EN_AON_LEN)-1)<<AON_PMIP_DC_TP_OUT_EN_AON_POS))
#define AON_TEN_DCDC_0_AON                                      AON_TEN_DCDC_0_AON
#define AON_TEN_DCDC_0_AON_POS                                  (10U)
#define AON_TEN_DCDC_0_AON_LEN                                  (1U)
#define AON_TEN_DCDC_0_AON_MSK                                  (((1U<<AON_TEN_DCDC_0_AON_LEN)-1)<<AON_TEN_DCDC_0_AON_POS)
#define AON_TEN_DCDC_0_AON_UMSK                                 (~(((1U<<AON_TEN_DCDC_0_AON_LEN)-1)<<AON_TEN_DCDC_0_AON_POS))
#define AON_TEN_DCDC_1_AON                                      AON_TEN_DCDC_1_AON
#define AON_TEN_DCDC_1_AON_POS                                  (11U)
#define AON_TEN_DCDC_1_AON_LEN                                  (1U)
#define AON_TEN_DCDC_1_AON_MSK                                  (((1U<<AON_TEN_DCDC_1_AON_LEN)-1)<<AON_TEN_DCDC_1_AON_POS)
#define AON_TEN_DCDC_1_AON_UMSK                                 (~(((1U<<AON_TEN_DCDC_1_AON_LEN)-1)<<AON_TEN_DCDC_1_AON_POS))
#define AON_TEN_BG_SYS_AON                                      AON_TEN_BG_SYS_AON
#define AON_TEN_BG_SYS_AON_POS                                  (12U)
#define AON_TEN_BG_SYS_AON_LEN                                  (1U)
#define AON_TEN_BG_SYS_AON_MSK                                  (((1U<<AON_TEN_BG_SYS_AON_LEN)-1)<<AON_TEN_BG_SYS_AON_POS)
#define AON_TEN_BG_SYS_AON_UMSK                                 (~(((1U<<AON_TEN_BG_SYS_AON_LEN)-1)<<AON_TEN_BG_SYS_AON_POS))
#define AON_TEN_BZ_LDO15RF_AON                                  AON_TEN_BZ_LDO15RF_AON
#define AON_TEN_BZ_LDO15RF_AON_POS                              (15U)
#define AON_TEN_BZ_LDO15RF_AON_LEN                              (1U)
#define AON_TEN_BZ_LDO15RF_AON_MSK                              (((1U<<AON_TEN_BZ_LDO15RF_AON_LEN)-1)<<AON_TEN_BZ_LDO15RF_AON_POS)
#define AON_TEN_BZ_LDO15RF_AON_UMSK                             (~(((1U<<AON_TEN_BZ_LDO15RF_AON_LEN)-1)<<AON_TEN_BZ_LDO15RF_AON_POS))
#define AON_TEN_LDO15RF_AON                                     AON_TEN_LDO15RF_AON
#define AON_TEN_LDO15RF_AON_POS                                 (16U)
#define AON_TEN_LDO15RF_AON_LEN                                 (1U)
#define AON_TEN_LDO15RF_AON_MSK                                 (((1U<<AON_TEN_LDO15RF_AON_LEN)-1)<<AON_TEN_LDO15RF_AON_POS)
#define AON_TEN_LDO15RF_AON_UMSK                                (~(((1U<<AON_TEN_LDO15RF_AON_LEN)-1)<<AON_TEN_LDO15RF_AON_POS))
#define AON_TEN_XTAL_AON                                        AON_TEN_XTAL_AON
#define AON_TEN_XTAL_AON_POS                                    (17U)
#define AON_TEN_XTAL_AON_LEN                                    (1U)
#define AON_TEN_XTAL_AON_MSK                                    (((1U<<AON_TEN_XTAL_AON_LEN)-1)<<AON_TEN_XTAL_AON_POS)
#define AON_TEN_XTAL_AON_UMSK                                   (~(((1U<<AON_TEN_XTAL_AON_LEN)-1)<<AON_TEN_XTAL_AON_POS))
#define AON_DTEN_XTAL_AON                                       AON_DTEN_XTAL_AON
#define AON_DTEN_XTAL_AON_POS                                   (18U)
#define AON_DTEN_XTAL_AON_LEN                                   (1U)
#define AON_DTEN_XTAL_AON_MSK                                   (((1U<<AON_DTEN_XTAL_AON_LEN)-1)<<AON_DTEN_XTAL_AON_POS)
#define AON_DTEN_XTAL_AON_UMSK                                  (~(((1U<<AON_DTEN_XTAL_AON_LEN)-1)<<AON_DTEN_XTAL_AON_POS))
#define AON_TEN_MBG_AON                                         AON_TEN_MBG_AON
#define AON_TEN_MBG_AON_POS                                     (19U)
#define AON_TEN_MBG_AON_LEN                                     (1U)
#define AON_TEN_MBG_AON_MSK                                     (((1U<<AON_TEN_MBG_AON_LEN)-1)<<AON_TEN_MBG_AON_POS)
#define AON_TEN_MBG_AON_UMSK                                    (~(((1U<<AON_TEN_MBG_AON_LEN)-1)<<AON_TEN_MBG_AON_POS))
#define AON_TEN_CIP_MISC_AON                                    AON_TEN_CIP_MISC_AON
#define AON_TEN_CIP_MISC_AON_POS                                (20U)
#define AON_TEN_CIP_MISC_AON_LEN                                (1U)
#define AON_TEN_CIP_MISC_AON_MSK                                (((1U<<AON_TEN_CIP_MISC_AON_LEN)-1)<<AON_TEN_CIP_MISC_AON_POS)
#define AON_TEN_CIP_MISC_AON_UMSK                               (~(((1U<<AON_TEN_CIP_MISC_AON_LEN)-1)<<AON_TEN_CIP_MISC_AON_POS))

/* 0x808 : aon_misc */
#define AON_MISC_OFFSET                                         (0x808)
#define AON_SW_SOC_EN_AON                                       AON_SW_SOC_EN_AON
#define AON_SW_SOC_EN_AON_POS                                   (0U)
#define AON_SW_SOC_EN_AON_LEN                                   (1U)
#define AON_SW_SOC_EN_AON_MSK                                   (((1U<<AON_SW_SOC_EN_AON_LEN)-1)<<AON_SW_SOC_EN_AON_POS)
#define AON_SW_SOC_EN_AON_UMSK                                  (~(((1U<<AON_SW_SOC_EN_AON_LEN)-1)<<AON_SW_SOC_EN_AON_POS))
#define AON_SW_WB_EN_AON                                        AON_SW_WB_EN_AON
#define AON_SW_WB_EN_AON_POS                                    (1U)
#define AON_SW_WB_EN_AON_LEN                                    (1U)
#define AON_SW_WB_EN_AON_MSK                                    (((1U<<AON_SW_WB_EN_AON_LEN)-1)<<AON_SW_WB_EN_AON_POS)
#define AON_SW_WB_EN_AON_UMSK                                   (~(((1U<<AON_SW_WB_EN_AON_LEN)-1)<<AON_SW_WB_EN_AON_POS))

/* 0x810 : bg_sys_top */
#define AON_BG_SYS_TOP_OFFSET                                   (0x810)
#define AON_PMIP_RESV                                           AON_PMIP_RESV
#define AON_PMIP_RESV_POS                                       (0U)
#define AON_PMIP_RESV_LEN                                       (8U)
#define AON_PMIP_RESV_MSK                                       (((1U<<AON_PMIP_RESV_LEN)-1)<<AON_PMIP_RESV_POS)
#define AON_PMIP_RESV_UMSK                                      (~(((1U<<AON_PMIP_RESV_LEN)-1)<<AON_PMIP_RESV_POS))
#define AON_PU_BG_SYS_AON                                       AON_PU_BG_SYS_AON
#define AON_PU_BG_SYS_AON_POS                                   (8U)
#define AON_PU_BG_SYS_AON_LEN                                   (1U)
#define AON_PU_BG_SYS_AON_MSK                                   (((1U<<AON_PU_BG_SYS_AON_LEN)-1)<<AON_PU_BG_SYS_AON_POS)
#define AON_PU_BG_SYS_AON_UMSK                                  (~(((1U<<AON_PU_BG_SYS_AON_LEN)-1)<<AON_PU_BG_SYS_AON_POS))
#define AON_BG_SYS_START_CTRL_AON                               AON_BG_SYS_START_CTRL_AON
#define AON_BG_SYS_START_CTRL_AON_POS                           (12U)
#define AON_BG_SYS_START_CTRL_AON_LEN                           (1U)
#define AON_BG_SYS_START_CTRL_AON_MSK                           (((1U<<AON_BG_SYS_START_CTRL_AON_LEN)-1)<<AON_BG_SYS_START_CTRL_AON_POS)
#define AON_BG_SYS_START_CTRL_AON_UMSK                          (~(((1U<<AON_BG_SYS_START_CTRL_AON_LEN)-1)<<AON_BG_SYS_START_CTRL_AON_POS))

/* 0x814 : dcdc_top_0 */
#define AON_DCDC_TOP_0_OFFSET                                   (0x814)
#define AON_DCDC_VOUT_SEL_AON                                   AON_DCDC_VOUT_SEL_AON
#define AON_DCDC_VOUT_SEL_AON_POS                               (0U)
#define AON_DCDC_VOUT_SEL_AON_LEN                               (5U)
#define AON_DCDC_VOUT_SEL_AON_MSK                               (((1U<<AON_DCDC_VOUT_SEL_AON_LEN)-1)<<AON_DCDC_VOUT_SEL_AON_POS)
#define AON_DCDC_VOUT_SEL_AON_UMSK                              (~(((1U<<AON_DCDC_VOUT_SEL_AON_LEN)-1)<<AON_DCDC_VOUT_SEL_AON_POS))
#define AON_DCDC_VPFM_AON                                       AON_DCDC_VPFM_AON
#define AON_DCDC_VPFM_AON_POS                                   (8U)
#define AON_DCDC_VPFM_AON_LEN                                   (4U)
#define AON_DCDC_VPFM_AON_MSK                                   (((1U<<AON_DCDC_VPFM_AON_LEN)-1)<<AON_DCDC_VPFM_AON_POS)
#define AON_DCDC_VPFM_AON_UMSK                                  (~(((1U<<AON_DCDC_VPFM_AON_LEN)-1)<<AON_DCDC_VPFM_AON_POS))
#define AON_DCDC_OSC_2M_MODE_AON                                AON_DCDC_OSC_2M_MODE_AON
#define AON_DCDC_OSC_2M_MODE_AON_POS                            (12U)
#define AON_DCDC_OSC_2M_MODE_AON_LEN                            (1U)
#define AON_DCDC_OSC_2M_MODE_AON_MSK                            (((1U<<AON_DCDC_OSC_2M_MODE_AON_LEN)-1)<<AON_DCDC_OSC_2M_MODE_AON_POS)
#define AON_DCDC_OSC_2M_MODE_AON_UMSK                           (~(((1U<<AON_DCDC_OSC_2M_MODE_AON_LEN)-1)<<AON_DCDC_OSC_2M_MODE_AON_POS))
#define AON_DCDC_OSC_FREQ_TRIM_AON                              AON_DCDC_OSC_FREQ_TRIM_AON
#define AON_DCDC_OSC_FREQ_TRIM_AON_POS                          (16U)
#define AON_DCDC_OSC_FREQ_TRIM_AON_LEN                          (4U)
#define AON_DCDC_OSC_FREQ_TRIM_AON_MSK                          (((1U<<AON_DCDC_OSC_FREQ_TRIM_AON_LEN)-1)<<AON_DCDC_OSC_FREQ_TRIM_AON_POS)
#define AON_DCDC_OSC_FREQ_TRIM_AON_UMSK                         (~(((1U<<AON_DCDC_OSC_FREQ_TRIM_AON_LEN)-1)<<AON_DCDC_OSC_FREQ_TRIM_AON_POS))
#define AON_DCDC_SLOPE_CURR_SEL_AON                             AON_DCDC_SLOPE_CURR_SEL_AON
#define AON_DCDC_SLOPE_CURR_SEL_AON_POS                         (20U)
#define AON_DCDC_SLOPE_CURR_SEL_AON_LEN                         (5U)
#define AON_DCDC_SLOPE_CURR_SEL_AON_MSK                         (((1U<<AON_DCDC_SLOPE_CURR_SEL_AON_LEN)-1)<<AON_DCDC_SLOPE_CURR_SEL_AON_POS)
#define AON_DCDC_SLOPE_CURR_SEL_AON_UMSK                        (~(((1U<<AON_DCDC_SLOPE_CURR_SEL_AON_LEN)-1)<<AON_DCDC_SLOPE_CURR_SEL_AON_POS))
#define AON_DCDC_EN_STOP_OSC_AON                                AON_DCDC_EN_STOP_OSC_AON
#define AON_DCDC_EN_STOP_OSC_AON_POS                            (25U)
#define AON_DCDC_EN_STOP_OSC_AON_LEN                            (1U)
#define AON_DCDC_EN_STOP_OSC_AON_MSK                            (((1U<<AON_DCDC_EN_STOP_OSC_AON_LEN)-1)<<AON_DCDC_EN_STOP_OSC_AON_POS)
#define AON_DCDC_EN_STOP_OSC_AON_UMSK                           (~(((1U<<AON_DCDC_EN_STOP_OSC_AON_LEN)-1)<<AON_DCDC_EN_STOP_OSC_AON_POS))
#define AON_DCDC_EN_SLOW_OSC_AON                                AON_DCDC_EN_SLOW_OSC_AON
#define AON_DCDC_EN_SLOW_OSC_AON_POS                            (26U)
#define AON_DCDC_EN_SLOW_OSC_AON_LEN                            (1U)
#define AON_DCDC_EN_SLOW_OSC_AON_MSK                            (((1U<<AON_DCDC_EN_SLOW_OSC_AON_LEN)-1)<<AON_DCDC_EN_SLOW_OSC_AON_POS)
#define AON_DCDC_EN_SLOW_OSC_AON_UMSK                           (~(((1U<<AON_DCDC_EN_SLOW_OSC_AON_LEN)-1)<<AON_DCDC_EN_SLOW_OSC_AON_POS))
#define AON_DCDC_EN_OSC_INHIBIT_T2_AON                          AON_DCDC_EN_OSC_INHIBIT_T2_AON
#define AON_DCDC_EN_OSC_INHIBIT_T2_AON_POS                      (27U)
#define AON_DCDC_EN_OSC_INHIBIT_T2_AON_LEN                      (1U)
#define AON_DCDC_EN_OSC_INHIBIT_T2_AON_MSK                      (((1U<<AON_DCDC_EN_OSC_INHIBIT_T2_AON_LEN)-1)<<AON_DCDC_EN_OSC_INHIBIT_T2_AON_POS)
#define AON_DCDC_EN_OSC_INHIBIT_T2_AON_UMSK                     (~(((1U<<AON_DCDC_EN_OSC_INHIBIT_T2_AON_LEN)-1)<<AON_DCDC_EN_OSC_INHIBIT_T2_AON_POS))
#define AON_DCDC_SSTART_TIME_AON                                AON_DCDC_SSTART_TIME_AON
#define AON_DCDC_SSTART_TIME_AON_POS                            (28U)
#define AON_DCDC_SSTART_TIME_AON_LEN                            (2U)
#define AON_DCDC_SSTART_TIME_AON_MSK                            (((1U<<AON_DCDC_SSTART_TIME_AON_LEN)-1)<<AON_DCDC_SSTART_TIME_AON_POS)
#define AON_DCDC_SSTART_TIME_AON_UMSK                           (~(((1U<<AON_DCDC_SSTART_TIME_AON_LEN)-1)<<AON_DCDC_SSTART_TIME_AON_POS))
#define AON_DCDC_RDY_AON                                        AON_DCDC_RDY_AON
#define AON_DCDC_RDY_AON_POS                                    (31U)
#define AON_DCDC_RDY_AON_LEN                                    (1U)
#define AON_DCDC_RDY_AON_MSK                                    (((1U<<AON_DCDC_RDY_AON_LEN)-1)<<AON_DCDC_RDY_AON_POS)
#define AON_DCDC_RDY_AON_UMSK                                   (~(((1U<<AON_DCDC_RDY_AON_LEN)-1)<<AON_DCDC_RDY_AON_POS))

/* 0x818 : dcdc_top_1 */
#define AON_DCDC_TOP_1_OFFSET                                   (0x818)
#define AON_DCDC_FORCE_EN_CS_ZVS_AON                            AON_DCDC_FORCE_EN_CS_ZVS_AON
#define AON_DCDC_FORCE_EN_CS_ZVS_AON_POS                        (0U)
#define AON_DCDC_FORCE_EN_CS_ZVS_AON_LEN                        (1U)
#define AON_DCDC_FORCE_EN_CS_ZVS_AON_MSK                        (((1U<<AON_DCDC_FORCE_EN_CS_ZVS_AON_LEN)-1)<<AON_DCDC_FORCE_EN_CS_ZVS_AON_POS)
#define AON_DCDC_FORCE_EN_CS_ZVS_AON_UMSK                       (~(((1U<<AON_DCDC_FORCE_EN_CS_ZVS_AON_LEN)-1)<<AON_DCDC_FORCE_EN_CS_ZVS_AON_POS))
#define AON_DCDC_CS_DELAY_AON                                   AON_DCDC_CS_DELAY_AON
#define AON_DCDC_CS_DELAY_AON_POS                               (1U)
#define AON_DCDC_CS_DELAY_AON_LEN                               (3U)
#define AON_DCDC_CS_DELAY_AON_MSK                               (((1U<<AON_DCDC_CS_DELAY_AON_LEN)-1)<<AON_DCDC_CS_DELAY_AON_POS)
#define AON_DCDC_CS_DELAY_AON_UMSK                              (~(((1U<<AON_DCDC_CS_DELAY_AON_LEN)-1)<<AON_DCDC_CS_DELAY_AON_POS))
#define AON_DCDC_ZVS_TD_OPT_AON                                 AON_DCDC_ZVS_TD_OPT_AON
#define AON_DCDC_ZVS_TD_OPT_AON_POS                             (4U)
#define AON_DCDC_ZVS_TD_OPT_AON_LEN                             (3U)
#define AON_DCDC_ZVS_TD_OPT_AON_MSK                             (((1U<<AON_DCDC_ZVS_TD_OPT_AON_LEN)-1)<<AON_DCDC_ZVS_TD_OPT_AON_POS)
#define AON_DCDC_ZVS_TD_OPT_AON_UMSK                            (~(((1U<<AON_DCDC_ZVS_TD_OPT_AON_LEN)-1)<<AON_DCDC_ZVS_TD_OPT_AON_POS))
#define AON_DCDC_NONOVERLAP_TD_AON                              AON_DCDC_NONOVERLAP_TD_AON
#define AON_DCDC_NONOVERLAP_TD_AON_POS                          (8U)
#define AON_DCDC_NONOVERLAP_TD_AON_LEN                          (5U)
#define AON_DCDC_NONOVERLAP_TD_AON_MSK                          (((1U<<AON_DCDC_NONOVERLAP_TD_AON_LEN)-1)<<AON_DCDC_NONOVERLAP_TD_AON_POS)
#define AON_DCDC_NONOVERLAP_TD_AON_UMSK                         (~(((1U<<AON_DCDC_NONOVERLAP_TD_AON_LEN)-1)<<AON_DCDC_NONOVERLAP_TD_AON_POS))
#define AON_DCDC_RC_SEL_AON                                     AON_DCDC_RC_SEL_AON
#define AON_DCDC_RC_SEL_AON_POS                                 (16U)
#define AON_DCDC_RC_SEL_AON_LEN                                 (4U)
#define AON_DCDC_RC_SEL_AON_MSK                                 (((1U<<AON_DCDC_RC_SEL_AON_LEN)-1)<<AON_DCDC_RC_SEL_AON_POS)
#define AON_DCDC_RC_SEL_AON_UMSK                                (~(((1U<<AON_DCDC_RC_SEL_AON_LEN)-1)<<AON_DCDC_RC_SEL_AON_POS))
#define AON_DCDC_CHF_SEL_AON                                    AON_DCDC_CHF_SEL_AON
#define AON_DCDC_CHF_SEL_AON_POS                                (20U)
#define AON_DCDC_CHF_SEL_AON_LEN                                (4U)
#define AON_DCDC_CHF_SEL_AON_MSK                                (((1U<<AON_DCDC_CHF_SEL_AON_LEN)-1)<<AON_DCDC_CHF_SEL_AON_POS)
#define AON_DCDC_CHF_SEL_AON_UMSK                               (~(((1U<<AON_DCDC_CHF_SEL_AON_LEN)-1)<<AON_DCDC_CHF_SEL_AON_POS))
#define AON_DCDC_CFB_SEL_AON                                    AON_DCDC_CFB_SEL_AON
#define AON_DCDC_CFB_SEL_AON_POS                                (24U)
#define AON_DCDC_CFB_SEL_AON_LEN                                (4U)
#define AON_DCDC_CFB_SEL_AON_MSK                                (((1U<<AON_DCDC_CFB_SEL_AON_LEN)-1)<<AON_DCDC_CFB_SEL_AON_POS)
#define AON_DCDC_CFB_SEL_AON_UMSK                               (~(((1U<<AON_DCDC_CFB_SEL_AON_LEN)-1)<<AON_DCDC_CFB_SEL_AON_POS))
#define AON_DCDC_EN_ANTIRING_AON                                AON_DCDC_EN_ANTIRING_AON
#define AON_DCDC_EN_ANTIRING_AON_POS                            (28U)
#define AON_DCDC_EN_ANTIRING_AON_LEN                            (1U)
#define AON_DCDC_EN_ANTIRING_AON_MSK                            (((1U<<AON_DCDC_EN_ANTIRING_AON_LEN)-1)<<AON_DCDC_EN_ANTIRING_AON_POS)
#define AON_DCDC_EN_ANTIRING_AON_UMSK                           (~(((1U<<AON_DCDC_EN_ANTIRING_AON_LEN)-1)<<AON_DCDC_EN_ANTIRING_AON_POS))
#define AON_DCDC_PULLDOWN_AON                                   AON_DCDC_PULLDOWN_AON
#define AON_DCDC_PULLDOWN_AON_POS                               (29U)
#define AON_DCDC_PULLDOWN_AON_LEN                               (1U)
#define AON_DCDC_PULLDOWN_AON_MSK                               (((1U<<AON_DCDC_PULLDOWN_AON_LEN)-1)<<AON_DCDC_PULLDOWN_AON_POS)
#define AON_DCDC_PULLDOWN_AON_UMSK                              (~(((1U<<AON_DCDC_PULLDOWN_AON_LEN)-1)<<AON_DCDC_PULLDOWN_AON_POS))

/* 0x81C : ldo11soc_and_dctest */
#define AON_LDO11SOC_AND_DCTEST_OFFSET                          (0x81C)
#define AON_PU_LDO11SOC_AON                                     AON_PU_LDO11SOC_AON
#define AON_PU_LDO11SOC_AON_POS                                 (0U)
#define AON_PU_LDO11SOC_AON_LEN                                 (1U)
#define AON_PU_LDO11SOC_AON_MSK                                 (((1U<<AON_PU_LDO11SOC_AON_LEN)-1)<<AON_PU_LDO11SOC_AON_POS)
#define AON_PU_LDO11SOC_AON_UMSK                                (~(((1U<<AON_PU_LDO11SOC_AON_LEN)-1)<<AON_PU_LDO11SOC_AON_POS))
#define AON_PU_VDDCORE_MISC_AON                                 AON_PU_VDDCORE_MISC_AON
#define AON_PU_VDDCORE_MISC_AON_POS                             (30U)
#define AON_PU_VDDCORE_MISC_AON_LEN                             (1U)
#define AON_PU_VDDCORE_MISC_AON_MSK                             (((1U<<AON_PU_VDDCORE_MISC_AON_LEN)-1)<<AON_PU_VDDCORE_MISC_AON_POS)
#define AON_PU_VDDCORE_MISC_AON_UMSK                            (~(((1U<<AON_PU_VDDCORE_MISC_AON_LEN)-1)<<AON_PU_VDDCORE_MISC_AON_POS))

/* 0x820 : psw_irrcv */
#define AON_PSW_IRRCV_OFFSET                                    (0x820)
#define AON_PU_IR_PSW_AON                                       AON_PU_IR_PSW_AON
#define AON_PU_IR_PSW_AON_POS                                   (0U)
#define AON_PU_IR_PSW_AON_LEN                                   (1U)
#define AON_PU_IR_PSW_AON_MSK                                   (((1U<<AON_PU_IR_PSW_AON_LEN)-1)<<AON_PU_IR_PSW_AON_POS)
#define AON_PU_IR_PSW_AON_UMSK                                  (~(((1U<<AON_PU_IR_PSW_AON_LEN)-1)<<AON_PU_IR_PSW_AON_POS))

/* 0x824 : dcdc_top_2 */
#define AON_DCDC_TOP_2_OFFSET                                   (0x824)
#define AON_DCDC_VOUT_TRIM_AON                                  AON_DCDC_VOUT_TRIM_AON
#define AON_DCDC_VOUT_TRIM_AON_POS                              (0U)
#define AON_DCDC_VOUT_TRIM_AON_LEN                              (4U)
#define AON_DCDC_VOUT_TRIM_AON_MSK                              (((1U<<AON_DCDC_VOUT_TRIM_AON_LEN)-1)<<AON_DCDC_VOUT_TRIM_AON_POS)
#define AON_DCDC_VOUT_TRIM_AON_UMSK                             (~(((1U<<AON_DCDC_VOUT_TRIM_AON_LEN)-1)<<AON_DCDC_VOUT_TRIM_AON_POS))
#define AON_DCDC_LOW_DRV_N_STR_AON                              AON_DCDC_LOW_DRV_N_STR_AON
#define AON_DCDC_LOW_DRV_N_STR_AON_POS                          (4U)
#define AON_DCDC_LOW_DRV_N_STR_AON_LEN                          (2U)
#define AON_DCDC_LOW_DRV_N_STR_AON_MSK                          (((1U<<AON_DCDC_LOW_DRV_N_STR_AON_LEN)-1)<<AON_DCDC_LOW_DRV_N_STR_AON_POS)
#define AON_DCDC_LOW_DRV_N_STR_AON_UMSK                         (~(((1U<<AON_DCDC_LOW_DRV_N_STR_AON_LEN)-1)<<AON_DCDC_LOW_DRV_N_STR_AON_POS))
#define AON_DCDC_LOW_DRV_P_STR_AON                              AON_DCDC_LOW_DRV_P_STR_AON
#define AON_DCDC_LOW_DRV_P_STR_AON_POS                          (6U)
#define AON_DCDC_LOW_DRV_P_STR_AON_LEN                          (2U)
#define AON_DCDC_LOW_DRV_P_STR_AON_MSK                          (((1U<<AON_DCDC_LOW_DRV_P_STR_AON_LEN)-1)<<AON_DCDC_LOW_DRV_P_STR_AON_POS)
#define AON_DCDC_LOW_DRV_P_STR_AON_UMSK                         (~(((1U<<AON_DCDC_LOW_DRV_P_STR_AON_LEN)-1)<<AON_DCDC_LOW_DRV_P_STR_AON_POS))
#define AON_DCDC_HIGH_DRV_N_STR_AON                             AON_DCDC_HIGH_DRV_N_STR_AON
#define AON_DCDC_HIGH_DRV_N_STR_AON_POS                         (8U)
#define AON_DCDC_HIGH_DRV_N_STR_AON_LEN                         (2U)
#define AON_DCDC_HIGH_DRV_N_STR_AON_MSK                         (((1U<<AON_DCDC_HIGH_DRV_N_STR_AON_LEN)-1)<<AON_DCDC_HIGH_DRV_N_STR_AON_POS)
#define AON_DCDC_HIGH_DRV_N_STR_AON_UMSK                        (~(((1U<<AON_DCDC_HIGH_DRV_N_STR_AON_LEN)-1)<<AON_DCDC_HIGH_DRV_N_STR_AON_POS))
#define AON_DCDC_HIGH_DRV_P_STR_AON                             AON_DCDC_HIGH_DRV_P_STR_AON
#define AON_DCDC_HIGH_DRV_P_STR_AON_POS                         (10U)
#define AON_DCDC_HIGH_DRV_P_STR_AON_LEN                         (2U)
#define AON_DCDC_HIGH_DRV_P_STR_AON_MSK                         (((1U<<AON_DCDC_HIGH_DRV_P_STR_AON_LEN)-1)<<AON_DCDC_HIGH_DRV_P_STR_AON_POS)
#define AON_DCDC_HIGH_DRV_P_STR_AON_UMSK                        (~(((1U<<AON_DCDC_HIGH_DRV_P_STR_AON_LEN)-1)<<AON_DCDC_HIGH_DRV_P_STR_AON_POS))
#define AON_DCDC_COMP_GM_SEL_AON                                AON_DCDC_COMP_GM_SEL_AON
#define AON_DCDC_COMP_GM_SEL_AON_POS                            (12U)
#define AON_DCDC_COMP_GM_SEL_AON_LEN                            (3U)
#define AON_DCDC_COMP_GM_SEL_AON_MSK                            (((1U<<AON_DCDC_COMP_GM_SEL_AON_LEN)-1)<<AON_DCDC_COMP_GM_SEL_AON_POS)
#define AON_DCDC_COMP_GM_SEL_AON_UMSK                           (~(((1U<<AON_DCDC_COMP_GM_SEL_AON_LEN)-1)<<AON_DCDC_COMP_GM_SEL_AON_POS))
#define AON_DCDC_ISENSE_TRIM_AON                                AON_DCDC_ISENSE_TRIM_AON
#define AON_DCDC_ISENSE_TRIM_AON_POS                            (16U)
#define AON_DCDC_ISENSE_TRIM_AON_LEN                            (3U)
#define AON_DCDC_ISENSE_TRIM_AON_MSK                            (((1U<<AON_DCDC_ISENSE_TRIM_AON_LEN)-1)<<AON_DCDC_ISENSE_TRIM_AON_POS)
#define AON_DCDC_ISENSE_TRIM_AON_UMSK                           (~(((1U<<AON_DCDC_ISENSE_TRIM_AON_LEN)-1)<<AON_DCDC_ISENSE_TRIM_AON_POS))
#define AON_DCDC_VC_CLAMP_VTH_AON                               AON_DCDC_VC_CLAMP_VTH_AON
#define AON_DCDC_VC_CLAMP_VTH_AON_POS                           (20U)
#define AON_DCDC_VC_CLAMP_VTH_AON_LEN                           (3U)
#define AON_DCDC_VC_CLAMP_VTH_AON_MSK                           (((1U<<AON_DCDC_VC_CLAMP_VTH_AON_LEN)-1)<<AON_DCDC_VC_CLAMP_VTH_AON_POS)
#define AON_DCDC_VC_CLAMP_VTH_AON_UMSK                          (~(((1U<<AON_DCDC_VC_CLAMP_VTH_AON_LEN)-1)<<AON_DCDC_VC_CLAMP_VTH_AON_POS))
#define AON_DCDC_OCP_VTH_AON                                    AON_DCDC_OCP_VTH_AON
#define AON_DCDC_OCP_VTH_AON_POS                                (24U)
#define AON_DCDC_OCP_VTH_AON_LEN                                (3U)
#define AON_DCDC_OCP_VTH_AON_MSK                                (((1U<<AON_DCDC_OCP_VTH_AON_LEN)-1)<<AON_DCDC_OCP_VTH_AON_POS)
#define AON_DCDC_OCP_VTH_AON_UMSK                               (~(((1U<<AON_DCDC_OCP_VTH_AON_LEN)-1)<<AON_DCDC_OCP_VTH_AON_POS))
#define AON_DCDC_OCP_RST_AON                                    AON_DCDC_OCP_RST_AON
#define AON_DCDC_OCP_RST_AON_POS                                (27U)
#define AON_DCDC_OCP_RST_AON_LEN                                (1U)
#define AON_DCDC_OCP_RST_AON_MSK                                (((1U<<AON_DCDC_OCP_RST_AON_LEN)-1)<<AON_DCDC_OCP_RST_AON_POS)
#define AON_DCDC_OCP_RST_AON_UMSK                               (~(((1U<<AON_DCDC_OCP_RST_AON_LEN)-1)<<AON_DCDC_OCP_RST_AON_POS))
#define AON_DCDC_OCP_OUT_AON                                    AON_DCDC_OCP_OUT_AON
#define AON_DCDC_OCP_OUT_AON_POS                                (28U)
#define AON_DCDC_OCP_OUT_AON_LEN                                (1U)
#define AON_DCDC_OCP_OUT_AON_MSK                                (((1U<<AON_DCDC_OCP_OUT_AON_LEN)-1)<<AON_DCDC_OCP_OUT_AON_POS)
#define AON_DCDC_OCP_OUT_AON_UMSK                               (~(((1U<<AON_DCDC_OCP_OUT_AON_LEN)-1)<<AON_DCDC_OCP_OUT_AON_POS))

/* 0x880 : rf_top_aon */
#define AON_RF_TOP_AON_OFFSET                                   (0x880)
#define AON_PU_MBG_AON                                          AON_PU_MBG_AON
#define AON_PU_MBG_AON_POS                                      (0U)
#define AON_PU_MBG_AON_LEN                                      (1U)
#define AON_PU_MBG_AON_MSK                                      (((1U<<AON_PU_MBG_AON_LEN)-1)<<AON_PU_MBG_AON_POS)
#define AON_PU_MBG_AON_UMSK                                     (~(((1U<<AON_PU_MBG_AON_LEN)-1)<<AON_PU_MBG_AON_POS))
#define AON_PU_LDO15RF_AON                                      AON_PU_LDO15RF_AON
#define AON_PU_LDO15RF_AON_POS                                  (1U)
#define AON_PU_LDO15RF_AON_LEN                                  (1U)
#define AON_PU_LDO15RF_AON_MSK                                  (((1U<<AON_PU_LDO15RF_AON_LEN)-1)<<AON_PU_LDO15RF_AON_POS)
#define AON_PU_LDO15RF_AON_UMSK                                 (~(((1U<<AON_PU_LDO15RF_AON_LEN)-1)<<AON_PU_LDO15RF_AON_POS))
#define AON_PU_SFREG_AON                                        AON_PU_SFREG_AON
#define AON_PU_SFREG_AON_POS                                    (2U)
#define AON_PU_SFREG_AON_LEN                                    (1U)
#define AON_PU_SFREG_AON_MSK                                    (((1U<<AON_PU_SFREG_AON_LEN)-1)<<AON_PU_SFREG_AON_POS)
#define AON_PU_SFREG_AON_UMSK                                   (~(((1U<<AON_PU_SFREG_AON_LEN)-1)<<AON_PU_SFREG_AON_POS))
#define AON_PU_XTAL_BUF_AON                                     AON_PU_XTAL_BUF_AON
#define AON_PU_XTAL_BUF_AON_POS                                 (4U)
#define AON_PU_XTAL_BUF_AON_LEN                                 (1U)
#define AON_PU_XTAL_BUF_AON_MSK                                 (((1U<<AON_PU_XTAL_BUF_AON_LEN)-1)<<AON_PU_XTAL_BUF_AON_POS)
#define AON_PU_XTAL_BUF_AON_UMSK                                (~(((1U<<AON_PU_XTAL_BUF_AON_LEN)-1)<<AON_PU_XTAL_BUF_AON_POS))
#define AON_PU_XTAL_AON                                         AON_PU_XTAL_AON
#define AON_PU_XTAL_AON_POS                                     (5U)
#define AON_PU_XTAL_AON_LEN                                     (1U)
#define AON_PU_XTAL_AON_MSK                                     (((1U<<AON_PU_XTAL_AON_LEN)-1)<<AON_PU_XTAL_AON_POS)
#define AON_PU_XTAL_AON_UMSK                                    (~(((1U<<AON_PU_XTAL_AON_LEN)-1)<<AON_PU_XTAL_AON_POS))
#define AON_LDO15RF_SSTART_SEL_AON                              AON_LDO15RF_SSTART_SEL_AON
#define AON_LDO15RF_SSTART_SEL_AON_POS                          (8U)
#define AON_LDO15RF_SSTART_SEL_AON_LEN                          (1U)
#define AON_LDO15RF_SSTART_SEL_AON_MSK                          (((1U<<AON_LDO15RF_SSTART_SEL_AON_LEN)-1)<<AON_LDO15RF_SSTART_SEL_AON_POS)
#define AON_LDO15RF_SSTART_SEL_AON_UMSK                         (~(((1U<<AON_LDO15RF_SSTART_SEL_AON_LEN)-1)<<AON_LDO15RF_SSTART_SEL_AON_POS))
#define AON_LDO15RF_SSTART_DELAY_AON                            AON_LDO15RF_SSTART_DELAY_AON
#define AON_LDO15RF_SSTART_DELAY_AON_POS                        (9U)
#define AON_LDO15RF_SSTART_DELAY_AON_LEN                        (2U)
#define AON_LDO15RF_SSTART_DELAY_AON_MSK                        (((1U<<AON_LDO15RF_SSTART_DELAY_AON_LEN)-1)<<AON_LDO15RF_SSTART_DELAY_AON_POS)
#define AON_LDO15RF_SSTART_DELAY_AON_UMSK                       (~(((1U<<AON_LDO15RF_SSTART_DELAY_AON_LEN)-1)<<AON_LDO15RF_SSTART_DELAY_AON_POS))
#define AON_LDO15RF_PULLDOWN_AON                                AON_LDO15RF_PULLDOWN_AON
#define AON_LDO15RF_PULLDOWN_AON_POS                            (12U)
#define AON_LDO15RF_PULLDOWN_AON_LEN                            (1U)
#define AON_LDO15RF_PULLDOWN_AON_MSK                            (((1U<<AON_LDO15RF_PULLDOWN_AON_LEN)-1)<<AON_LDO15RF_PULLDOWN_AON_POS)
#define AON_LDO15RF_PULLDOWN_AON_UMSK                           (~(((1U<<AON_LDO15RF_PULLDOWN_AON_LEN)-1)<<AON_LDO15RF_PULLDOWN_AON_POS))
#define AON_LDO15RF_PULLDOWN_SEL_AON                            AON_LDO15RF_PULLDOWN_SEL_AON
#define AON_LDO15RF_PULLDOWN_SEL_AON_POS                        (13U)
#define AON_LDO15RF_PULLDOWN_SEL_AON_LEN                        (1U)
#define AON_LDO15RF_PULLDOWN_SEL_AON_MSK                        (((1U<<AON_LDO15RF_PULLDOWN_SEL_AON_LEN)-1)<<AON_LDO15RF_PULLDOWN_SEL_AON_POS)
#define AON_LDO15RF_PULLDOWN_SEL_AON_UMSK                       (~(((1U<<AON_LDO15RF_PULLDOWN_SEL_AON_LEN)-1)<<AON_LDO15RF_PULLDOWN_SEL_AON_POS))
#define AON_LDO15RF_VOUT_SEL_AON                                AON_LDO15RF_VOUT_SEL_AON
#define AON_LDO15RF_VOUT_SEL_AON_POS                            (16U)
#define AON_LDO15RF_VOUT_SEL_AON_LEN                            (3U)
#define AON_LDO15RF_VOUT_SEL_AON_MSK                            (((1U<<AON_LDO15RF_VOUT_SEL_AON_LEN)-1)<<AON_LDO15RF_VOUT_SEL_AON_POS)
#define AON_LDO15RF_VOUT_SEL_AON_UMSK                           (~(((1U<<AON_LDO15RF_VOUT_SEL_AON_LEN)-1)<<AON_LDO15RF_VOUT_SEL_AON_POS))
#define AON_LDO15RF_CC_AON                                      AON_LDO15RF_CC_AON
#define AON_LDO15RF_CC_AON_POS                                  (24U)
#define AON_LDO15RF_CC_AON_LEN                                  (2U)
#define AON_LDO15RF_CC_AON_MSK                                  (((1U<<AON_LDO15RF_CC_AON_LEN)-1)<<AON_LDO15RF_CC_AON_POS)
#define AON_LDO15RF_CC_AON_UMSK                                 (~(((1U<<AON_LDO15RF_CC_AON_LEN)-1)<<AON_LDO15RF_CC_AON_POS))
#define AON_LDO15RF_BYPASS_AON                                  AON_LDO15RF_BYPASS_AON
#define AON_LDO15RF_BYPASS_AON_POS                              (28U)
#define AON_LDO15RF_BYPASS_AON_LEN                              (1U)
#define AON_LDO15RF_BYPASS_AON_MSK                              (((1U<<AON_LDO15RF_BYPASS_AON_LEN)-1)<<AON_LDO15RF_BYPASS_AON_POS)
#define AON_LDO15RF_BYPASS_AON_UMSK                             (~(((1U<<AON_LDO15RF_BYPASS_AON_LEN)-1)<<AON_LDO15RF_BYPASS_AON_POS))

/* 0x884 : xtal_cfg */
#define AON_XTAL_CFG_OFFSET                                     (0x884)
#define AON_XTAL_BK_AON                                         AON_XTAL_BK_AON
#define AON_XTAL_BK_AON_POS                                     (0U)
#define AON_XTAL_BK_AON_LEN                                     (2U)
#define AON_XTAL_BK_AON_MSK                                     (((1U<<AON_XTAL_BK_AON_LEN)-1)<<AON_XTAL_BK_AON_POS)
#define AON_XTAL_BK_AON_UMSK                                    (~(((1U<<AON_XTAL_BK_AON_LEN)-1)<<AON_XTAL_BK_AON_POS))
#define AON_XTAL_CAPCODE_EXTRA_AON                              AON_XTAL_CAPCODE_EXTRA_AON
#define AON_XTAL_CAPCODE_EXTRA_AON_POS                          (2U)
#define AON_XTAL_CAPCODE_EXTRA_AON_LEN                          (1U)
#define AON_XTAL_CAPCODE_EXTRA_AON_MSK                          (((1U<<AON_XTAL_CAPCODE_EXTRA_AON_LEN)-1)<<AON_XTAL_CAPCODE_EXTRA_AON_POS)
#define AON_XTAL_CAPCODE_EXTRA_AON_UMSK                         (~(((1U<<AON_XTAL_CAPCODE_EXTRA_AON_LEN)-1)<<AON_XTAL_CAPCODE_EXTRA_AON_POS))
#define AON_XTAL_EXT_SEL_AON                                    AON_XTAL_EXT_SEL_AON
#define AON_XTAL_EXT_SEL_AON_POS                                (3U)
#define AON_XTAL_EXT_SEL_AON_LEN                                (1U)
#define AON_XTAL_EXT_SEL_AON_MSK                                (((1U<<AON_XTAL_EXT_SEL_AON_LEN)-1)<<AON_XTAL_EXT_SEL_AON_POS)
#define AON_XTAL_EXT_SEL_AON_UMSK                               (~(((1U<<AON_XTAL_EXT_SEL_AON_LEN)-1)<<AON_XTAL_EXT_SEL_AON_POS))
#define AON_XTAL_BUF_EN_AON                                     AON_XTAL_BUF_EN_AON
#define AON_XTAL_BUF_EN_AON_POS                                 (4U)
#define AON_XTAL_BUF_EN_AON_LEN                                 (4U)
#define AON_XTAL_BUF_EN_AON_MSK                                 (((1U<<AON_XTAL_BUF_EN_AON_LEN)-1)<<AON_XTAL_BUF_EN_AON_POS)
#define AON_XTAL_BUF_EN_AON_UMSK                                (~(((1U<<AON_XTAL_BUF_EN_AON_LEN)-1)<<AON_XTAL_BUF_EN_AON_POS))
#define AON_XTAL_BUF_HP_AON                                     AON_XTAL_BUF_HP_AON
#define AON_XTAL_BUF_HP_AON_POS                                 (8U)
#define AON_XTAL_BUF_HP_AON_LEN                                 (4U)
#define AON_XTAL_BUF_HP_AON_MSK                                 (((1U<<AON_XTAL_BUF_HP_AON_LEN)-1)<<AON_XTAL_BUF_HP_AON_POS)
#define AON_XTAL_BUF_HP_AON_UMSK                                (~(((1U<<AON_XTAL_BUF_HP_AON_LEN)-1)<<AON_XTAL_BUF_HP_AON_POS))
#define AON_XTAL_FAST_STARTUP_AON                               AON_XTAL_FAST_STARTUP_AON
#define AON_XTAL_FAST_STARTUP_AON_POS                           (12U)
#define AON_XTAL_FAST_STARTUP_AON_LEN                           (1U)
#define AON_XTAL_FAST_STARTUP_AON_MSK                           (((1U<<AON_XTAL_FAST_STARTUP_AON_LEN)-1)<<AON_XTAL_FAST_STARTUP_AON_POS)
#define AON_XTAL_FAST_STARTUP_AON_UMSK                          (~(((1U<<AON_XTAL_FAST_STARTUP_AON_LEN)-1)<<AON_XTAL_FAST_STARTUP_AON_POS))
#define AON_XTAL_SLEEP_AON                                      AON_XTAL_SLEEP_AON
#define AON_XTAL_SLEEP_AON_POS                                  (13U)
#define AON_XTAL_SLEEP_AON_LEN                                  (1U)
#define AON_XTAL_SLEEP_AON_MSK                                  (((1U<<AON_XTAL_SLEEP_AON_LEN)-1)<<AON_XTAL_SLEEP_AON_POS)
#define AON_XTAL_SLEEP_AON_UMSK                                 (~(((1U<<AON_XTAL_SLEEP_AON_LEN)-1)<<AON_XTAL_SLEEP_AON_POS))
#define AON_XTAL_AMP_CTRL_AON                                   AON_XTAL_AMP_CTRL_AON
#define AON_XTAL_AMP_CTRL_AON_POS                               (14U)
#define AON_XTAL_AMP_CTRL_AON_LEN                               (2U)
#define AON_XTAL_AMP_CTRL_AON_MSK                               (((1U<<AON_XTAL_AMP_CTRL_AON_LEN)-1)<<AON_XTAL_AMP_CTRL_AON_POS)
#define AON_XTAL_AMP_CTRL_AON_UMSK                              (~(((1U<<AON_XTAL_AMP_CTRL_AON_LEN)-1)<<AON_XTAL_AMP_CTRL_AON_POS))
#define AON_XTAL_CAPCODE_OUT_AON                                AON_XTAL_CAPCODE_OUT_AON
#define AON_XTAL_CAPCODE_OUT_AON_POS                            (16U)
#define AON_XTAL_CAPCODE_OUT_AON_LEN                            (6U)
#define AON_XTAL_CAPCODE_OUT_AON_MSK                            (((1U<<AON_XTAL_CAPCODE_OUT_AON_LEN)-1)<<AON_XTAL_CAPCODE_OUT_AON_POS)
#define AON_XTAL_CAPCODE_OUT_AON_UMSK                           (~(((1U<<AON_XTAL_CAPCODE_OUT_AON_LEN)-1)<<AON_XTAL_CAPCODE_OUT_AON_POS))
#define AON_XTAL_CAPCODE_IN_AON                                 AON_XTAL_CAPCODE_IN_AON
#define AON_XTAL_CAPCODE_IN_AON_POS                             (22U)
#define AON_XTAL_CAPCODE_IN_AON_LEN                             (6U)
#define AON_XTAL_CAPCODE_IN_AON_MSK                             (((1U<<AON_XTAL_CAPCODE_IN_AON_LEN)-1)<<AON_XTAL_CAPCODE_IN_AON_POS)
#define AON_XTAL_CAPCODE_IN_AON_UMSK                            (~(((1U<<AON_XTAL_CAPCODE_IN_AON_LEN)-1)<<AON_XTAL_CAPCODE_IN_AON_POS))
#define AON_XTAL_GM_BOOST_AON                                   AON_XTAL_GM_BOOST_AON
#define AON_XTAL_GM_BOOST_AON_POS                               (28U)
#define AON_XTAL_GM_BOOST_AON_LEN                               (2U)
#define AON_XTAL_GM_BOOST_AON_MSK                               (((1U<<AON_XTAL_GM_BOOST_AON_LEN)-1)<<AON_XTAL_GM_BOOST_AON_POS)
#define AON_XTAL_GM_BOOST_AON_UMSK                              (~(((1U<<AON_XTAL_GM_BOOST_AON_LEN)-1)<<AON_XTAL_GM_BOOST_AON_POS))
#define AON_XTAL_RDY_SEL_AON                                    AON_XTAL_RDY_SEL_AON
#define AON_XTAL_RDY_SEL_AON_POS                                (30U)
#define AON_XTAL_RDY_SEL_AON_LEN                                (2U)
#define AON_XTAL_RDY_SEL_AON_MSK                                (((1U<<AON_XTAL_RDY_SEL_AON_LEN)-1)<<AON_XTAL_RDY_SEL_AON_POS)
#define AON_XTAL_RDY_SEL_AON_UMSK                               (~(((1U<<AON_XTAL_RDY_SEL_AON_LEN)-1)<<AON_XTAL_RDY_SEL_AON_POS))

/* 0x888 : tsen */
#define AON_TSEN_OFFSET                                         (0x888)
#define AON_TSEN_REFCODE_CORNER                                 AON_TSEN_REFCODE_CORNER
#define AON_TSEN_REFCODE_CORNER_POS                             (0U)
#define AON_TSEN_REFCODE_CORNER_LEN                             (12U)
#define AON_TSEN_REFCODE_CORNER_MSK                             (((1U<<AON_TSEN_REFCODE_CORNER_LEN)-1)<<AON_TSEN_REFCODE_CORNER_POS)
#define AON_TSEN_REFCODE_CORNER_UMSK                            (~(((1U<<AON_TSEN_REFCODE_CORNER_LEN)-1)<<AON_TSEN_REFCODE_CORNER_POS))
#define AON_TSEN_REFCODE_RFCAL                                  AON_TSEN_REFCODE_RFCAL
#define AON_TSEN_REFCODE_RFCAL_POS                              (16U)
#define AON_TSEN_REFCODE_RFCAL_LEN                              (12U)
#define AON_TSEN_REFCODE_RFCAL_MSK                              (((1U<<AON_TSEN_REFCODE_RFCAL_LEN)-1)<<AON_TSEN_REFCODE_RFCAL_POS)
#define AON_TSEN_REFCODE_RFCAL_UMSK                             (~(((1U<<AON_TSEN_REFCODE_RFCAL_LEN)-1)<<AON_TSEN_REFCODE_RFCAL_POS))
#define AON_XTAL_RDY                                            AON_XTAL_RDY
#define AON_XTAL_RDY_POS                                        (28U)
#define AON_XTAL_RDY_LEN                                        (1U)
#define AON_XTAL_RDY_MSK                                        (((1U<<AON_XTAL_RDY_LEN)-1)<<AON_XTAL_RDY_POS)
#define AON_XTAL_RDY_UMSK                                       (~(((1U<<AON_XTAL_RDY_LEN)-1)<<AON_XTAL_RDY_POS))
#define AON_XTAL_INN_CFG_EN_AON                                 AON_XTAL_INN_CFG_EN_AON
#define AON_XTAL_INN_CFG_EN_AON_POS                             (29U)
#define AON_XTAL_INN_CFG_EN_AON_LEN                             (1U)
#define AON_XTAL_INN_CFG_EN_AON_MSK                             (((1U<<AON_XTAL_INN_CFG_EN_AON_LEN)-1)<<AON_XTAL_INN_CFG_EN_AON_POS)
#define AON_XTAL_INN_CFG_EN_AON_UMSK                            (~(((1U<<AON_XTAL_INN_CFG_EN_AON_LEN)-1)<<AON_XTAL_INN_CFG_EN_AON_POS))
#define AON_XTAL_RDY_INT_SEL_AON                                AON_XTAL_RDY_INT_SEL_AON
#define AON_XTAL_RDY_INT_SEL_AON_POS                            (30U)
#define AON_XTAL_RDY_INT_SEL_AON_LEN                            (2U)
#define AON_XTAL_RDY_INT_SEL_AON_MSK                            (((1U<<AON_XTAL_RDY_INT_SEL_AON_LEN)-1)<<AON_XTAL_RDY_INT_SEL_AON_POS)
#define AON_XTAL_RDY_INT_SEL_AON_UMSK                           (~(((1U<<AON_XTAL_RDY_INT_SEL_AON_LEN)-1)<<AON_XTAL_RDY_INT_SEL_AON_POS))

/* 0x88C : rf2_top_aon */
#define AON_RF2_TOP_AON_OFFSET                                  (0x88C)
#define AON_PU_BZ_MBG_AON                                       AON_PU_BZ_MBG_AON
#define AON_PU_BZ_MBG_AON_POS                                   (0U)
#define AON_PU_BZ_MBG_AON_LEN                                   (1U)
#define AON_PU_BZ_MBG_AON_MSK                                   (((1U<<AON_PU_BZ_MBG_AON_LEN)-1)<<AON_PU_BZ_MBG_AON_POS)
#define AON_PU_BZ_MBG_AON_UMSK                                  (~(((1U<<AON_PU_BZ_MBG_AON_LEN)-1)<<AON_PU_BZ_MBG_AON_POS))
#define AON_PU_BZ_LDO15RF_AON                                   AON_PU_BZ_LDO15RF_AON
#define AON_PU_BZ_LDO15RF_AON_POS                               (1U)
#define AON_PU_BZ_LDO15RF_AON_LEN                               (1U)
#define AON_PU_BZ_LDO15RF_AON_MSK                               (((1U<<AON_PU_BZ_LDO15RF_AON_LEN)-1)<<AON_PU_BZ_LDO15RF_AON_POS)
#define AON_PU_BZ_LDO15RF_AON_UMSK                              (~(((1U<<AON_PU_BZ_LDO15RF_AON_LEN)-1)<<AON_PU_BZ_LDO15RF_AON_POS))
#define AON_PU_BZ_SFREG_AON                                     AON_PU_BZ_SFREG_AON
#define AON_PU_BZ_SFREG_AON_POS                                 (2U)
#define AON_PU_BZ_SFREG_AON_LEN                                 (1U)
#define AON_PU_BZ_SFREG_AON_MSK                                 (((1U<<AON_PU_BZ_SFREG_AON_LEN)-1)<<AON_PU_BZ_SFREG_AON_POS)
#define AON_PU_BZ_SFREG_AON_UMSK                                (~(((1U<<AON_PU_BZ_SFREG_AON_LEN)-1)<<AON_PU_BZ_SFREG_AON_POS))
#define AON_BZ_LDO15RF_SSTART_SEL_AON                           AON_BZ_LDO15RF_SSTART_SEL_AON
#define AON_BZ_LDO15RF_SSTART_SEL_AON_POS                       (8U)
#define AON_BZ_LDO15RF_SSTART_SEL_AON_LEN                       (1U)
#define AON_BZ_LDO15RF_SSTART_SEL_AON_MSK                       (((1U<<AON_BZ_LDO15RF_SSTART_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_SSTART_SEL_AON_POS)
#define AON_BZ_LDO15RF_SSTART_SEL_AON_UMSK                      (~(((1U<<AON_BZ_LDO15RF_SSTART_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_SSTART_SEL_AON_POS))
#define AON_BZ_LDO15RF_SSTART_DELAY_AON                         AON_BZ_LDO15RF_SSTART_DELAY_AON
#define AON_BZ_LDO15RF_SSTART_DELAY_AON_POS                     (9U)
#define AON_BZ_LDO15RF_SSTART_DELAY_AON_LEN                     (2U)
#define AON_BZ_LDO15RF_SSTART_DELAY_AON_MSK                     (((1U<<AON_BZ_LDO15RF_SSTART_DELAY_AON_LEN)-1)<<AON_BZ_LDO15RF_SSTART_DELAY_AON_POS)
#define AON_BZ_LDO15RF_SSTART_DELAY_AON_UMSK                    (~(((1U<<AON_BZ_LDO15RF_SSTART_DELAY_AON_LEN)-1)<<AON_BZ_LDO15RF_SSTART_DELAY_AON_POS))
#define AON_BZ_LDO15RF_PULLDOWN_AON                             AON_BZ_LDO15RF_PULLDOWN_AON
#define AON_BZ_LDO15RF_PULLDOWN_AON_POS                         (12U)
#define AON_BZ_LDO15RF_PULLDOWN_AON_LEN                         (1U)
#define AON_BZ_LDO15RF_PULLDOWN_AON_MSK                         (((1U<<AON_BZ_LDO15RF_PULLDOWN_AON_LEN)-1)<<AON_BZ_LDO15RF_PULLDOWN_AON_POS)
#define AON_BZ_LDO15RF_PULLDOWN_AON_UMSK                        (~(((1U<<AON_BZ_LDO15RF_PULLDOWN_AON_LEN)-1)<<AON_BZ_LDO15RF_PULLDOWN_AON_POS))
#define AON_BZ_LDO15RF_PULLDOWN_SEL_AON                         AON_BZ_LDO15RF_PULLDOWN_SEL_AON
#define AON_BZ_LDO15RF_PULLDOWN_SEL_AON_POS                     (13U)
#define AON_BZ_LDO15RF_PULLDOWN_SEL_AON_LEN                     (1U)
#define AON_BZ_LDO15RF_PULLDOWN_SEL_AON_MSK                     (((1U<<AON_BZ_LDO15RF_PULLDOWN_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_PULLDOWN_SEL_AON_POS)
#define AON_BZ_LDO15RF_PULLDOWN_SEL_AON_UMSK                    (~(((1U<<AON_BZ_LDO15RF_PULLDOWN_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_PULLDOWN_SEL_AON_POS))
#define AON_BZ_LDO15RF_VOUT_SEL_AON                             AON_BZ_LDO15RF_VOUT_SEL_AON
#define AON_BZ_LDO15RF_VOUT_SEL_AON_POS                         (16U)
#define AON_BZ_LDO15RF_VOUT_SEL_AON_LEN                         (3U)
#define AON_BZ_LDO15RF_VOUT_SEL_AON_MSK                         (((1U<<AON_BZ_LDO15RF_VOUT_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_VOUT_SEL_AON_POS)
#define AON_BZ_LDO15RF_VOUT_SEL_AON_UMSK                        (~(((1U<<AON_BZ_LDO15RF_VOUT_SEL_AON_LEN)-1)<<AON_BZ_LDO15RF_VOUT_SEL_AON_POS))
#define AON_BZ_LDO15RF_CC_AON                                   AON_BZ_LDO15RF_CC_AON
#define AON_BZ_LDO15RF_CC_AON_POS                               (24U)
#define AON_BZ_LDO15RF_CC_AON_LEN                               (2U)
#define AON_BZ_LDO15RF_CC_AON_MSK                               (((1U<<AON_BZ_LDO15RF_CC_AON_LEN)-1)<<AON_BZ_LDO15RF_CC_AON_POS)
#define AON_BZ_LDO15RF_CC_AON_UMSK                              (~(((1U<<AON_BZ_LDO15RF_CC_AON_LEN)-1)<<AON_BZ_LDO15RF_CC_AON_POS))
#define AON_BZ_LDO15RF_BYPASS_AON                               AON_BZ_LDO15RF_BYPASS_AON
#define AON_BZ_LDO15RF_BYPASS_AON_POS                           (28U)
#define AON_BZ_LDO15RF_BYPASS_AON_LEN                           (1U)
#define AON_BZ_LDO15RF_BYPASS_AON_MSK                           (((1U<<AON_BZ_LDO15RF_BYPASS_AON_LEN)-1)<<AON_BZ_LDO15RF_BYPASS_AON_POS)
#define AON_BZ_LDO15RF_BYPASS_AON_UMSK                          (~(((1U<<AON_BZ_LDO15RF_BYPASS_AON_LEN)-1)<<AON_BZ_LDO15RF_BYPASS_AON_POS))

/* 0x900 : acomp0_ctrl */
#define AON_ACOMP0_CTRL_OFFSET                                  (0x900)
#define AON_ACOMP0_EN                                           AON_ACOMP0_EN
#define AON_ACOMP0_EN_POS                                       (0U)
#define AON_ACOMP0_EN_LEN                                       (1U)
#define AON_ACOMP0_EN_MSK                                       (((1U<<AON_ACOMP0_EN_LEN)-1)<<AON_ACOMP0_EN_POS)
#define AON_ACOMP0_EN_UMSK                                      (~(((1U<<AON_ACOMP0_EN_LEN)-1)<<AON_ACOMP0_EN_POS))
#define AON_ACOMP0_HYST_SELN                                    AON_ACOMP0_HYST_SELN
#define AON_ACOMP0_HYST_SELN_POS                                (4U)
#define AON_ACOMP0_HYST_SELN_LEN                                (3U)
#define AON_ACOMP0_HYST_SELN_MSK                                (((1U<<AON_ACOMP0_HYST_SELN_LEN)-1)<<AON_ACOMP0_HYST_SELN_POS)
#define AON_ACOMP0_HYST_SELN_UMSK                               (~(((1U<<AON_ACOMP0_HYST_SELN_LEN)-1)<<AON_ACOMP0_HYST_SELN_POS))
#define AON_ACOMP0_HYST_SELP                                    AON_ACOMP0_HYST_SELP
#define AON_ACOMP0_HYST_SELP_POS                                (7U)
#define AON_ACOMP0_HYST_SELP_LEN                                (3U)
#define AON_ACOMP0_HYST_SELP_MSK                                (((1U<<AON_ACOMP0_HYST_SELP_LEN)-1)<<AON_ACOMP0_HYST_SELP_POS)
#define AON_ACOMP0_HYST_SELP_UMSK                               (~(((1U<<AON_ACOMP0_HYST_SELP_LEN)-1)<<AON_ACOMP0_HYST_SELP_POS))
#define AON_ACOMP0_BIAS_PROG                                    AON_ACOMP0_BIAS_PROG
#define AON_ACOMP0_BIAS_PROG_POS                                (10U)
#define AON_ACOMP0_BIAS_PROG_LEN                                (2U)
#define AON_ACOMP0_BIAS_PROG_MSK                                (((1U<<AON_ACOMP0_BIAS_PROG_LEN)-1)<<AON_ACOMP0_BIAS_PROG_POS)
#define AON_ACOMP0_BIAS_PROG_UMSK                               (~(((1U<<AON_ACOMP0_BIAS_PROG_LEN)-1)<<AON_ACOMP0_BIAS_PROG_POS))
#define AON_ACOMP0_LEVEL_SEL                                    AON_ACOMP0_LEVEL_SEL
#define AON_ACOMP0_LEVEL_SEL_POS                                (12U)
#define AON_ACOMP0_LEVEL_SEL_LEN                                (6U)
#define AON_ACOMP0_LEVEL_SEL_MSK                                (((1U<<AON_ACOMP0_LEVEL_SEL_LEN)-1)<<AON_ACOMP0_LEVEL_SEL_POS)
#define AON_ACOMP0_LEVEL_SEL_UMSK                               (~(((1U<<AON_ACOMP0_LEVEL_SEL_LEN)-1)<<AON_ACOMP0_LEVEL_SEL_POS))
#define AON_ACOMP0_NEG_SEL                                      AON_ACOMP0_NEG_SEL
#define AON_ACOMP0_NEG_SEL_POS                                  (18U)
#define AON_ACOMP0_NEG_SEL_LEN                                  (4U)
#define AON_ACOMP0_NEG_SEL_MSK                                  (((1U<<AON_ACOMP0_NEG_SEL_LEN)-1)<<AON_ACOMP0_NEG_SEL_POS)
#define AON_ACOMP0_NEG_SEL_UMSK                                 (~(((1U<<AON_ACOMP0_NEG_SEL_LEN)-1)<<AON_ACOMP0_NEG_SEL_POS))
#define AON_ACOMP0_POS_SEL                                      AON_ACOMP0_POS_SEL
#define AON_ACOMP0_POS_SEL_POS                                  (22U)
#define AON_ACOMP0_POS_SEL_LEN                                  (4U)
#define AON_ACOMP0_POS_SEL_MSK                                  (((1U<<AON_ACOMP0_POS_SEL_LEN)-1)<<AON_ACOMP0_POS_SEL_POS)
#define AON_ACOMP0_POS_SEL_UMSK                                 (~(((1U<<AON_ACOMP0_POS_SEL_LEN)-1)<<AON_ACOMP0_POS_SEL_POS))
#define AON_ACOMP0_MUXEN                                        AON_ACOMP0_MUXEN
#define AON_ACOMP0_MUXEN_POS                                    (26U)
#define AON_ACOMP0_MUXEN_LEN                                    (1U)
#define AON_ACOMP0_MUXEN_MSK                                    (((1U<<AON_ACOMP0_MUXEN_LEN)-1)<<AON_ACOMP0_MUXEN_POS)
#define AON_ACOMP0_MUXEN_UMSK                                   (~(((1U<<AON_ACOMP0_MUXEN_LEN)-1)<<AON_ACOMP0_MUXEN_POS))

/* 0x904 : acomp1_ctrl */
#define AON_ACOMP1_CTRL_OFFSET                                  (0x904)
#define AON_ACOMP1_EN                                           AON_ACOMP1_EN
#define AON_ACOMP1_EN_POS                                       (0U)
#define AON_ACOMP1_EN_LEN                                       (1U)
#define AON_ACOMP1_EN_MSK                                       (((1U<<AON_ACOMP1_EN_LEN)-1)<<AON_ACOMP1_EN_POS)
#define AON_ACOMP1_EN_UMSK                                      (~(((1U<<AON_ACOMP1_EN_LEN)-1)<<AON_ACOMP1_EN_POS))
#define AON_ACOMP1_HYST_SELN                                    AON_ACOMP1_HYST_SELN
#define AON_ACOMP1_HYST_SELN_POS                                (4U)
#define AON_ACOMP1_HYST_SELN_LEN                                (3U)
#define AON_ACOMP1_HYST_SELN_MSK                                (((1U<<AON_ACOMP1_HYST_SELN_LEN)-1)<<AON_ACOMP1_HYST_SELN_POS)
#define AON_ACOMP1_HYST_SELN_UMSK                               (~(((1U<<AON_ACOMP1_HYST_SELN_LEN)-1)<<AON_ACOMP1_HYST_SELN_POS))
#define AON_ACOMP1_HYST_SELP                                    AON_ACOMP1_HYST_SELP
#define AON_ACOMP1_HYST_SELP_POS                                (7U)
#define AON_ACOMP1_HYST_SELP_LEN                                (3U)
#define AON_ACOMP1_HYST_SELP_MSK                                (((1U<<AON_ACOMP1_HYST_SELP_LEN)-1)<<AON_ACOMP1_HYST_SELP_POS)
#define AON_ACOMP1_HYST_SELP_UMSK                               (~(((1U<<AON_ACOMP1_HYST_SELP_LEN)-1)<<AON_ACOMP1_HYST_SELP_POS))
#define AON_ACOMP1_BIAS_PROG                                    AON_ACOMP1_BIAS_PROG
#define AON_ACOMP1_BIAS_PROG_POS                                (10U)
#define AON_ACOMP1_BIAS_PROG_LEN                                (2U)
#define AON_ACOMP1_BIAS_PROG_MSK                                (((1U<<AON_ACOMP1_BIAS_PROG_LEN)-1)<<AON_ACOMP1_BIAS_PROG_POS)
#define AON_ACOMP1_BIAS_PROG_UMSK                               (~(((1U<<AON_ACOMP1_BIAS_PROG_LEN)-1)<<AON_ACOMP1_BIAS_PROG_POS))
#define AON_ACOMP1_LEVEL_SEL                                    AON_ACOMP1_LEVEL_SEL
#define AON_ACOMP1_LEVEL_SEL_POS                                (12U)
#define AON_ACOMP1_LEVEL_SEL_LEN                                (6U)
#define AON_ACOMP1_LEVEL_SEL_MSK                                (((1U<<AON_ACOMP1_LEVEL_SEL_LEN)-1)<<AON_ACOMP1_LEVEL_SEL_POS)
#define AON_ACOMP1_LEVEL_SEL_UMSK                               (~(((1U<<AON_ACOMP1_LEVEL_SEL_LEN)-1)<<AON_ACOMP1_LEVEL_SEL_POS))
#define AON_ACOMP1_NEG_SEL                                      AON_ACOMP1_NEG_SEL
#define AON_ACOMP1_NEG_SEL_POS                                  (18U)
#define AON_ACOMP1_NEG_SEL_LEN                                  (4U)
#define AON_ACOMP1_NEG_SEL_MSK                                  (((1U<<AON_ACOMP1_NEG_SEL_LEN)-1)<<AON_ACOMP1_NEG_SEL_POS)
#define AON_ACOMP1_NEG_SEL_UMSK                                 (~(((1U<<AON_ACOMP1_NEG_SEL_LEN)-1)<<AON_ACOMP1_NEG_SEL_POS))
#define AON_ACOMP1_POS_SEL                                      AON_ACOMP1_POS_SEL
#define AON_ACOMP1_POS_SEL_POS                                  (22U)
#define AON_ACOMP1_POS_SEL_LEN                                  (4U)
#define AON_ACOMP1_POS_SEL_MSK                                  (((1U<<AON_ACOMP1_POS_SEL_LEN)-1)<<AON_ACOMP1_POS_SEL_POS)
#define AON_ACOMP1_POS_SEL_UMSK                                 (~(((1U<<AON_ACOMP1_POS_SEL_LEN)-1)<<AON_ACOMP1_POS_SEL_POS))
#define AON_ACOMP1_MUXEN                                        AON_ACOMP1_MUXEN
#define AON_ACOMP1_MUXEN_POS                                    (26U)
#define AON_ACOMP1_MUXEN_LEN                                    (1U)
#define AON_ACOMP1_MUXEN_MSK                                    (((1U<<AON_ACOMP1_MUXEN_LEN)-1)<<AON_ACOMP1_MUXEN_POS)
#define AON_ACOMP1_MUXEN_UMSK                                   (~(((1U<<AON_ACOMP1_MUXEN_LEN)-1)<<AON_ACOMP1_MUXEN_POS))

/* 0x908 : acomp_ctrl */
#define AON_ACOMP_CTRL_OFFSET                                   (0x908)
#define AON_ACOMP1_RSTN_ANA                                     AON_ACOMP1_RSTN_ANA
#define AON_ACOMP1_RSTN_ANA_POS                                 (0U)
#define AON_ACOMP1_RSTN_ANA_LEN                                 (1U)
#define AON_ACOMP1_RSTN_ANA_MSK                                 (((1U<<AON_ACOMP1_RSTN_ANA_LEN)-1)<<AON_ACOMP1_RSTN_ANA_POS)
#define AON_ACOMP1_RSTN_ANA_UMSK                                (~(((1U<<AON_ACOMP1_RSTN_ANA_LEN)-1)<<AON_ACOMP1_RSTN_ANA_POS))
#define AON_ACOMP0_RSTN_ANA                                     AON_ACOMP0_RSTN_ANA
#define AON_ACOMP0_RSTN_ANA_POS                                 (1U)
#define AON_ACOMP0_RSTN_ANA_LEN                                 (1U)
#define AON_ACOMP0_RSTN_ANA_MSK                                 (((1U<<AON_ACOMP0_RSTN_ANA_LEN)-1)<<AON_ACOMP0_RSTN_ANA_POS)
#define AON_ACOMP0_RSTN_ANA_UMSK                                (~(((1U<<AON_ACOMP0_RSTN_ANA_LEN)-1)<<AON_ACOMP0_RSTN_ANA_POS))
#define AON_ACOMP1_TEST_EN                                      AON_ACOMP1_TEST_EN
#define AON_ACOMP1_TEST_EN_POS                                  (8U)
#define AON_ACOMP1_TEST_EN_LEN                                  (1U)
#define AON_ACOMP1_TEST_EN_MSK                                  (((1U<<AON_ACOMP1_TEST_EN_LEN)-1)<<AON_ACOMP1_TEST_EN_POS)
#define AON_ACOMP1_TEST_EN_UMSK                                 (~(((1U<<AON_ACOMP1_TEST_EN_LEN)-1)<<AON_ACOMP1_TEST_EN_POS))
#define AON_ACOMP0_TEST_EN                                      AON_ACOMP0_TEST_EN
#define AON_ACOMP0_TEST_EN_POS                                  (9U)
#define AON_ACOMP0_TEST_EN_LEN                                  (1U)
#define AON_ACOMP0_TEST_EN_MSK                                  (((1U<<AON_ACOMP0_TEST_EN_LEN)-1)<<AON_ACOMP0_TEST_EN_POS)
#define AON_ACOMP0_TEST_EN_UMSK                                 (~(((1U<<AON_ACOMP0_TEST_EN_LEN)-1)<<AON_ACOMP0_TEST_EN_POS))
#define AON_ACOMP1_TEST_SEL                                     AON_ACOMP1_TEST_SEL
#define AON_ACOMP1_TEST_SEL_POS                                 (10U)
#define AON_ACOMP1_TEST_SEL_LEN                                 (2U)
#define AON_ACOMP1_TEST_SEL_MSK                                 (((1U<<AON_ACOMP1_TEST_SEL_LEN)-1)<<AON_ACOMP1_TEST_SEL_POS)
#define AON_ACOMP1_TEST_SEL_UMSK                                (~(((1U<<AON_ACOMP1_TEST_SEL_LEN)-1)<<AON_ACOMP1_TEST_SEL_POS))
#define AON_ACOMP0_TEST_SEL                                     AON_ACOMP0_TEST_SEL
#define AON_ACOMP0_TEST_SEL_POS                                 (12U)
#define AON_ACOMP0_TEST_SEL_LEN                                 (2U)
#define AON_ACOMP0_TEST_SEL_MSK                                 (((1U<<AON_ACOMP0_TEST_SEL_LEN)-1)<<AON_ACOMP0_TEST_SEL_POS)
#define AON_ACOMP0_TEST_SEL_UMSK                                (~(((1U<<AON_ACOMP0_TEST_SEL_LEN)-1)<<AON_ACOMP0_TEST_SEL_POS))
#define AON_ACOMP1_OUT_RAW                                      AON_ACOMP1_OUT_RAW
#define AON_ACOMP1_OUT_RAW_POS                                  (17U)
#define AON_ACOMP1_OUT_RAW_LEN                                  (1U)
#define AON_ACOMP1_OUT_RAW_MSK                                  (((1U<<AON_ACOMP1_OUT_RAW_LEN)-1)<<AON_ACOMP1_OUT_RAW_POS)
#define AON_ACOMP1_OUT_RAW_UMSK                                 (~(((1U<<AON_ACOMP1_OUT_RAW_LEN)-1)<<AON_ACOMP1_OUT_RAW_POS))
#define AON_ACOMP0_OUT_RAW                                      AON_ACOMP0_OUT_RAW
#define AON_ACOMP0_OUT_RAW_POS                                  (19U)
#define AON_ACOMP0_OUT_RAW_LEN                                  (1U)
#define AON_ACOMP0_OUT_RAW_MSK                                  (((1U<<AON_ACOMP0_OUT_RAW_LEN)-1)<<AON_ACOMP0_OUT_RAW_POS)
#define AON_ACOMP0_OUT_RAW_UMSK                                 (~(((1U<<AON_ACOMP0_OUT_RAW_LEN)-1)<<AON_ACOMP0_OUT_RAW_POS))
#define AON_ACOMP_RESERVED                                      AON_ACOMP_RESERVED
#define AON_ACOMP_RESERVED_POS                                  (24U)
#define AON_ACOMP_RESERVED_LEN                                  (8U)
#define AON_ACOMP_RESERVED_MSK                                  (((1U<<AON_ACOMP_RESERVED_LEN)-1)<<AON_ACOMP_RESERVED_POS)
#define AON_ACOMP_RESERVED_UMSK                                 (~(((1U<<AON_ACOMP_RESERVED_LEN)-1)<<AON_ACOMP_RESERVED_POS))

/* 0x90C : gpadc_reg_cmd */
#define AON_GPADC_REG_CMD_OFFSET                                (0x90C)
#define AON_GPADC_GLOBAL_EN                                     AON_GPADC_GLOBAL_EN
#define AON_GPADC_GLOBAL_EN_POS                                 (0U)
#define AON_GPADC_GLOBAL_EN_LEN                                 (1U)
#define AON_GPADC_GLOBAL_EN_MSK                                 (((1U<<AON_GPADC_GLOBAL_EN_LEN)-1)<<AON_GPADC_GLOBAL_EN_POS)
#define AON_GPADC_GLOBAL_EN_UMSK                                (~(((1U<<AON_GPADC_GLOBAL_EN_LEN)-1)<<AON_GPADC_GLOBAL_EN_POS))
#define AON_GPADC_CONV_START                                    AON_GPADC_CONV_START
#define AON_GPADC_CONV_START_POS                                (1U)
#define AON_GPADC_CONV_START_LEN                                (1U)
#define AON_GPADC_CONV_START_MSK                                (((1U<<AON_GPADC_CONV_START_LEN)-1)<<AON_GPADC_CONV_START_POS)
#define AON_GPADC_CONV_START_UMSK                               (~(((1U<<AON_GPADC_CONV_START_LEN)-1)<<AON_GPADC_CONV_START_POS))
#define AON_GPADC_SOFT_RST                                      AON_GPADC_SOFT_RST
#define AON_GPADC_SOFT_RST_POS                                  (2U)
#define AON_GPADC_SOFT_RST_LEN                                  (1U)
#define AON_GPADC_SOFT_RST_MSK                                  (((1U<<AON_GPADC_SOFT_RST_LEN)-1)<<AON_GPADC_SOFT_RST_POS)
#define AON_GPADC_SOFT_RST_UMSK                                 (~(((1U<<AON_GPADC_SOFT_RST_LEN)-1)<<AON_GPADC_SOFT_RST_POS))
#define AON_GPADC_NEG_SEL                                       AON_GPADC_NEG_SEL
#define AON_GPADC_NEG_SEL_POS                                   (3U)
#define AON_GPADC_NEG_SEL_LEN                                   (5U)
#define AON_GPADC_NEG_SEL_MSK                                   (((1U<<AON_GPADC_NEG_SEL_LEN)-1)<<AON_GPADC_NEG_SEL_POS)
#define AON_GPADC_NEG_SEL_UMSK                                  (~(((1U<<AON_GPADC_NEG_SEL_LEN)-1)<<AON_GPADC_NEG_SEL_POS))
#define AON_GPADC_POS_SEL                                       AON_GPADC_POS_SEL
#define AON_GPADC_POS_SEL_POS                                   (8U)
#define AON_GPADC_POS_SEL_LEN                                   (5U)
#define AON_GPADC_POS_SEL_MSK                                   (((1U<<AON_GPADC_POS_SEL_LEN)-1)<<AON_GPADC_POS_SEL_POS)
#define AON_GPADC_POS_SEL_UMSK                                  (~(((1U<<AON_GPADC_POS_SEL_LEN)-1)<<AON_GPADC_POS_SEL_POS))
#define AON_GPADC_NEG_GND                                       AON_GPADC_NEG_GND
#define AON_GPADC_NEG_GND_POS                                   (13U)
#define AON_GPADC_NEG_GND_LEN                                   (1U)
#define AON_GPADC_NEG_GND_MSK                                   (((1U<<AON_GPADC_NEG_GND_LEN)-1)<<AON_GPADC_NEG_GND_POS)
#define AON_GPADC_NEG_GND_UMSK                                  (~(((1U<<AON_GPADC_NEG_GND_LEN)-1)<<AON_GPADC_NEG_GND_POS))
#define AON_GPADC_MICBIAS_EN                                    AON_GPADC_MICBIAS_EN
#define AON_GPADC_MICBIAS_EN_POS                                (14U)
#define AON_GPADC_MICBIAS_EN_LEN                                (1U)
#define AON_GPADC_MICBIAS_EN_MSK                                (((1U<<AON_GPADC_MICBIAS_EN_LEN)-1)<<AON_GPADC_MICBIAS_EN_POS)
#define AON_GPADC_MICBIAS_EN_UMSK                               (~(((1U<<AON_GPADC_MICBIAS_EN_LEN)-1)<<AON_GPADC_MICBIAS_EN_POS))
#define AON_GPADC_MICPGA_EN                                     AON_GPADC_MICPGA_EN
#define AON_GPADC_MICPGA_EN_POS                                 (15U)
#define AON_GPADC_MICPGA_EN_LEN                                 (1U)
#define AON_GPADC_MICPGA_EN_MSK                                 (((1U<<AON_GPADC_MICPGA_EN_LEN)-1)<<AON_GPADC_MICPGA_EN_POS)
#define AON_GPADC_MICPGA_EN_UMSK                                (~(((1U<<AON_GPADC_MICPGA_EN_LEN)-1)<<AON_GPADC_MICPGA_EN_POS))
#define AON_GPADC_BYP_MICBOOST                                  AON_GPADC_BYP_MICBOOST
#define AON_GPADC_BYP_MICBOOST_POS                              (16U)
#define AON_GPADC_BYP_MICBOOST_LEN                              (1U)
#define AON_GPADC_BYP_MICBOOST_MSK                              (((1U<<AON_GPADC_BYP_MICBOOST_LEN)-1)<<AON_GPADC_BYP_MICBOOST_POS)
#define AON_GPADC_BYP_MICBOOST_UMSK                             (~(((1U<<AON_GPADC_BYP_MICBOOST_LEN)-1)<<AON_GPADC_BYP_MICBOOST_POS))
#define AON_GPADC_RCAL_EN                                       AON_GPADC_RCAL_EN
#define AON_GPADC_RCAL_EN_POS                                   (17U)
#define AON_GPADC_RCAL_EN_LEN                                   (1U)
#define AON_GPADC_RCAL_EN_MSK                                   (((1U<<AON_GPADC_RCAL_EN_LEN)-1)<<AON_GPADC_RCAL_EN_POS)
#define AON_GPADC_RCAL_EN_UMSK                                  (~(((1U<<AON_GPADC_RCAL_EN_LEN)-1)<<AON_GPADC_RCAL_EN_POS))
#define AON_GPADC_DWA_EN                                        AON_GPADC_DWA_EN
#define AON_GPADC_DWA_EN_POS                                    (18U)
#define AON_GPADC_DWA_EN_LEN                                    (1U)
#define AON_GPADC_DWA_EN_MSK                                    (((1U<<AON_GPADC_DWA_EN_LEN)-1)<<AON_GPADC_DWA_EN_POS)
#define AON_GPADC_DWA_EN_UMSK                                   (~(((1U<<AON_GPADC_DWA_EN_LEN)-1)<<AON_GPADC_DWA_EN_POS))
#define AON_GPADC_MIC2_DIFF                                     AON_GPADC_MIC2_DIFF
#define AON_GPADC_MIC2_DIFF_POS                                 (19U)
#define AON_GPADC_MIC2_DIFF_LEN                                 (1U)
#define AON_GPADC_MIC2_DIFF_MSK                                 (((1U<<AON_GPADC_MIC2_DIFF_LEN)-1)<<AON_GPADC_MIC2_DIFF_POS)
#define AON_GPADC_MIC2_DIFF_UMSK                                (~(((1U<<AON_GPADC_MIC2_DIFF_LEN)-1)<<AON_GPADC_MIC2_DIFF_POS))
#define AON_GPADC_MIC1_DIFF                                     AON_GPADC_MIC1_DIFF
#define AON_GPADC_MIC1_DIFF_POS                                 (20U)
#define AON_GPADC_MIC1_DIFF_LEN                                 (1U)
#define AON_GPADC_MIC1_DIFF_MSK                                 (((1U<<AON_GPADC_MIC1_DIFF_LEN)-1)<<AON_GPADC_MIC1_DIFF_POS)
#define AON_GPADC_MIC1_DIFF_UMSK                                (~(((1U<<AON_GPADC_MIC1_DIFF_LEN)-1)<<AON_GPADC_MIC1_DIFF_POS))
#define AON_GPADC_MIC_PGA2_GAIN                                 AON_GPADC_MIC_PGA2_GAIN
#define AON_GPADC_MIC_PGA2_GAIN_POS                             (21U)
#define AON_GPADC_MIC_PGA2_GAIN_LEN                             (2U)
#define AON_GPADC_MIC_PGA2_GAIN_MSK                             (((1U<<AON_GPADC_MIC_PGA2_GAIN_LEN)-1)<<AON_GPADC_MIC_PGA2_GAIN_POS)
#define AON_GPADC_MIC_PGA2_GAIN_UMSK                            (~(((1U<<AON_GPADC_MIC_PGA2_GAIN_LEN)-1)<<AON_GPADC_MIC_PGA2_GAIN_POS))
#define AON_GPADC_MICBOOST_32DB_EN                              AON_GPADC_MICBOOST_32DB_EN
#define AON_GPADC_MICBOOST_32DB_EN_POS                          (23U)
#define AON_GPADC_MICBOOST_32DB_EN_LEN                          (1U)
#define AON_GPADC_MICBOOST_32DB_EN_MSK                          (((1U<<AON_GPADC_MICBOOST_32DB_EN_LEN)-1)<<AON_GPADC_MICBOOST_32DB_EN_POS)
#define AON_GPADC_MICBOOST_32DB_EN_UMSK                         (~(((1U<<AON_GPADC_MICBOOST_32DB_EN_LEN)-1)<<AON_GPADC_MICBOOST_32DB_EN_POS))
#define AON_GPADC_CHIP_SEN_PU                                   AON_GPADC_CHIP_SEN_PU
#define AON_GPADC_CHIP_SEN_PU_POS                               (27U)
#define AON_GPADC_CHIP_SEN_PU_LEN                               (1U)
#define AON_GPADC_CHIP_SEN_PU_MSK                               (((1U<<AON_GPADC_CHIP_SEN_PU_LEN)-1)<<AON_GPADC_CHIP_SEN_PU_POS)
#define AON_GPADC_CHIP_SEN_PU_UMSK                              (~(((1U<<AON_GPADC_CHIP_SEN_PU_LEN)-1)<<AON_GPADC_CHIP_SEN_PU_POS))
#define AON_GPADC_SEN_SEL                                       AON_GPADC_SEN_SEL
#define AON_GPADC_SEN_SEL_POS                                   (28U)
#define AON_GPADC_SEN_SEL_LEN                                   (3U)
#define AON_GPADC_SEN_SEL_MSK                                   (((1U<<AON_GPADC_SEN_SEL_LEN)-1)<<AON_GPADC_SEN_SEL_POS)
#define AON_GPADC_SEN_SEL_UMSK                                  (~(((1U<<AON_GPADC_SEN_SEL_LEN)-1)<<AON_GPADC_SEN_SEL_POS))
#define AON_GPADC_SEN_TEST_EN                                   AON_GPADC_SEN_TEST_EN
#define AON_GPADC_SEN_TEST_EN_POS                               (31U)
#define AON_GPADC_SEN_TEST_EN_LEN                               (1U)
#define AON_GPADC_SEN_TEST_EN_MSK                               (((1U<<AON_GPADC_SEN_TEST_EN_LEN)-1)<<AON_GPADC_SEN_TEST_EN_POS)
#define AON_GPADC_SEN_TEST_EN_UMSK                              (~(((1U<<AON_GPADC_SEN_TEST_EN_LEN)-1)<<AON_GPADC_SEN_TEST_EN_POS))

/* 0x910 : gpadc_reg_config1 */
#define AON_GPADC_REG_CONFIG1_OFFSET                            (0x910)
#define AON_GPADC_CAL_OS_EN                                     AON_GPADC_CAL_OS_EN
#define AON_GPADC_CAL_OS_EN_POS                                 (0U)
#define AON_GPADC_CAL_OS_EN_LEN                                 (1U)
#define AON_GPADC_CAL_OS_EN_MSK                                 (((1U<<AON_GPADC_CAL_OS_EN_LEN)-1)<<AON_GPADC_CAL_OS_EN_POS)
#define AON_GPADC_CAL_OS_EN_UMSK                                (~(((1U<<AON_GPADC_CAL_OS_EN_LEN)-1)<<AON_GPADC_CAL_OS_EN_POS))
#define AON_GPADC_CONT_CONV_EN                                  AON_GPADC_CONT_CONV_EN
#define AON_GPADC_CONT_CONV_EN_POS                              (1U)
#define AON_GPADC_CONT_CONV_EN_LEN                              (1U)
#define AON_GPADC_CONT_CONV_EN_MSK                              (((1U<<AON_GPADC_CONT_CONV_EN_LEN)-1)<<AON_GPADC_CONT_CONV_EN_POS)
#define AON_GPADC_CONT_CONV_EN_UMSK                             (~(((1U<<AON_GPADC_CONT_CONV_EN_LEN)-1)<<AON_GPADC_CONT_CONV_EN_POS))
#define AON_GPADC_RES_SEL                                       AON_GPADC_RES_SEL
#define AON_GPADC_RES_SEL_POS                                   (2U)
#define AON_GPADC_RES_SEL_LEN                                   (3U)
#define AON_GPADC_RES_SEL_MSK                                   (((1U<<AON_GPADC_RES_SEL_LEN)-1)<<AON_GPADC_RES_SEL_POS)
#define AON_GPADC_RES_SEL_UMSK                                  (~(((1U<<AON_GPADC_RES_SEL_LEN)-1)<<AON_GPADC_RES_SEL_POS))
#define AON_GPADC_VCM_SEL_EN                                    AON_GPADC_VCM_SEL_EN
#define AON_GPADC_VCM_SEL_EN_POS                                (8U)
#define AON_GPADC_VCM_SEL_EN_LEN                                (1U)
#define AON_GPADC_VCM_SEL_EN_MSK                                (((1U<<AON_GPADC_VCM_SEL_EN_LEN)-1)<<AON_GPADC_VCM_SEL_EN_POS)
#define AON_GPADC_VCM_SEL_EN_UMSK                               (~(((1U<<AON_GPADC_VCM_SEL_EN_LEN)-1)<<AON_GPADC_VCM_SEL_EN_POS))
#define AON_GPADC_VCM_HYST_SEL                                  AON_GPADC_VCM_HYST_SEL
#define AON_GPADC_VCM_HYST_SEL_POS                              (9U)
#define AON_GPADC_VCM_HYST_SEL_LEN                              (1U)
#define AON_GPADC_VCM_HYST_SEL_MSK                              (((1U<<AON_GPADC_VCM_HYST_SEL_LEN)-1)<<AON_GPADC_VCM_HYST_SEL_POS)
#define AON_GPADC_VCM_HYST_SEL_UMSK                             (~(((1U<<AON_GPADC_VCM_HYST_SEL_LEN)-1)<<AON_GPADC_VCM_HYST_SEL_POS))
#define AON_GPADC_LOWV_DET_EN                                   AON_GPADC_LOWV_DET_EN
#define AON_GPADC_LOWV_DET_EN_POS                               (10U)
#define AON_GPADC_LOWV_DET_EN_LEN                               (1U)
#define AON_GPADC_LOWV_DET_EN_MSK                               (((1U<<AON_GPADC_LOWV_DET_EN_LEN)-1)<<AON_GPADC_LOWV_DET_EN_POS)
#define AON_GPADC_LOWV_DET_EN_UMSK                              (~(((1U<<AON_GPADC_LOWV_DET_EN_LEN)-1)<<AON_GPADC_LOWV_DET_EN_POS))
#define AON_GPADC_PWM_TRG_EN                                    AON_GPADC_PWM_TRG_EN
#define AON_GPADC_PWM_TRG_EN_POS                                (11U)
#define AON_GPADC_PWM_TRG_EN_LEN                                (1U)
#define AON_GPADC_PWM_TRG_EN_MSK                                (((1U<<AON_GPADC_PWM_TRG_EN_LEN)-1)<<AON_GPADC_PWM_TRG_EN_POS)
#define AON_GPADC_PWM_TRG_EN_UMSK                               (~(((1U<<AON_GPADC_PWM_TRG_EN_LEN)-1)<<AON_GPADC_PWM_TRG_EN_POS))
#define AON_GPADC_CLK_ANA_DLY                                   AON_GPADC_CLK_ANA_DLY
#define AON_GPADC_CLK_ANA_DLY_POS                               (12U)
#define AON_GPADC_CLK_ANA_DLY_LEN                               (4U)
#define AON_GPADC_CLK_ANA_DLY_MSK                               (((1U<<AON_GPADC_CLK_ANA_DLY_LEN)-1)<<AON_GPADC_CLK_ANA_DLY_POS)
#define AON_GPADC_CLK_ANA_DLY_UMSK                              (~(((1U<<AON_GPADC_CLK_ANA_DLY_LEN)-1)<<AON_GPADC_CLK_ANA_DLY_POS))
#define AON_GPADC_CLK_ANA_DLY_EN                                AON_GPADC_CLK_ANA_DLY_EN
#define AON_GPADC_CLK_ANA_DLY_EN_POS                            (16U)
#define AON_GPADC_CLK_ANA_DLY_EN_LEN                            (1U)
#define AON_GPADC_CLK_ANA_DLY_EN_MSK                            (((1U<<AON_GPADC_CLK_ANA_DLY_EN_LEN)-1)<<AON_GPADC_CLK_ANA_DLY_EN_POS)
#define AON_GPADC_CLK_ANA_DLY_EN_UMSK                           (~(((1U<<AON_GPADC_CLK_ANA_DLY_EN_LEN)-1)<<AON_GPADC_CLK_ANA_DLY_EN_POS))
#define AON_GPADC_CLK_ANA_INV                                   AON_GPADC_CLK_ANA_INV
#define AON_GPADC_CLK_ANA_INV_POS                               (17U)
#define AON_GPADC_CLK_ANA_INV_LEN                               (1U)
#define AON_GPADC_CLK_ANA_INV_MSK                               (((1U<<AON_GPADC_CLK_ANA_INV_LEN)-1)<<AON_GPADC_CLK_ANA_INV_POS)
#define AON_GPADC_CLK_ANA_INV_UMSK                              (~(((1U<<AON_GPADC_CLK_ANA_INV_LEN)-1)<<AON_GPADC_CLK_ANA_INV_POS))
#define AON_GPADC_CLK_DIV_RATIO                                 AON_GPADC_CLK_DIV_RATIO
#define AON_GPADC_CLK_DIV_RATIO_POS                             (18U)
#define AON_GPADC_CLK_DIV_RATIO_LEN                             (3U)
#define AON_GPADC_CLK_DIV_RATIO_MSK                             (((1U<<AON_GPADC_CLK_DIV_RATIO_LEN)-1)<<AON_GPADC_CLK_DIV_RATIO_POS)
#define AON_GPADC_CLK_DIV_RATIO_UMSK                            (~(((1U<<AON_GPADC_CLK_DIV_RATIO_LEN)-1)<<AON_GPADC_CLK_DIV_RATIO_POS))
#define AON_GPADC_SCAN_LENGTH                                   AON_GPADC_SCAN_LENGTH
#define AON_GPADC_SCAN_LENGTH_POS                               (21U)
#define AON_GPADC_SCAN_LENGTH_LEN                               (4U)
#define AON_GPADC_SCAN_LENGTH_MSK                               (((1U<<AON_GPADC_SCAN_LENGTH_LEN)-1)<<AON_GPADC_SCAN_LENGTH_POS)
#define AON_GPADC_SCAN_LENGTH_UMSK                              (~(((1U<<AON_GPADC_SCAN_LENGTH_LEN)-1)<<AON_GPADC_SCAN_LENGTH_POS))
#define AON_GPADC_SCAN_EN                                       AON_GPADC_SCAN_EN
#define AON_GPADC_SCAN_EN_POS                                   (25U)
#define AON_GPADC_SCAN_EN_LEN                                   (1U)
#define AON_GPADC_SCAN_EN_MSK                                   (((1U<<AON_GPADC_SCAN_EN_LEN)-1)<<AON_GPADC_SCAN_EN_POS)
#define AON_GPADC_SCAN_EN_UMSK                                  (~(((1U<<AON_GPADC_SCAN_EN_LEN)-1)<<AON_GPADC_SCAN_EN_POS))
#define AON_GPADC_DITHER_EN                                     AON_GPADC_DITHER_EN
#define AON_GPADC_DITHER_EN_POS                                 (26U)
#define AON_GPADC_DITHER_EN_LEN                                 (1U)
#define AON_GPADC_DITHER_EN_MSK                                 (((1U<<AON_GPADC_DITHER_EN_LEN)-1)<<AON_GPADC_DITHER_EN_POS)
#define AON_GPADC_DITHER_EN_UMSK                                (~(((1U<<AON_GPADC_DITHER_EN_LEN)-1)<<AON_GPADC_DITHER_EN_POS))
#define AON_GPADC_V11_SEL                                       AON_GPADC_V11_SEL
#define AON_GPADC_V11_SEL_POS                                   (27U)
#define AON_GPADC_V11_SEL_LEN                                   (2U)
#define AON_GPADC_V11_SEL_MSK                                   (((1U<<AON_GPADC_V11_SEL_LEN)-1)<<AON_GPADC_V11_SEL_POS)
#define AON_GPADC_V11_SEL_UMSK                                  (~(((1U<<AON_GPADC_V11_SEL_LEN)-1)<<AON_GPADC_V11_SEL_POS))
#define AON_GPADC_V18_SEL                                       AON_GPADC_V18_SEL
#define AON_GPADC_V18_SEL_POS                                   (29U)
#define AON_GPADC_V18_SEL_LEN                                   (2U)
#define AON_GPADC_V18_SEL_MSK                                   (((1U<<AON_GPADC_V18_SEL_LEN)-1)<<AON_GPADC_V18_SEL_POS)
#define AON_GPADC_V18_SEL_UMSK                                  (~(((1U<<AON_GPADC_V18_SEL_LEN)-1)<<AON_GPADC_V18_SEL_POS))

/* 0x914 : gpadc_reg_config2 */
#define AON_GPADC_REG_CONFIG2_OFFSET                            (0x914)
#define AON_GPADC_DIFF_MODE                                     AON_GPADC_DIFF_MODE
#define AON_GPADC_DIFF_MODE_POS                                 (2U)
#define AON_GPADC_DIFF_MODE_LEN                                 (1U)
#define AON_GPADC_DIFF_MODE_MSK                                 (((1U<<AON_GPADC_DIFF_MODE_LEN)-1)<<AON_GPADC_DIFF_MODE_POS)
#define AON_GPADC_DIFF_MODE_UMSK                                (~(((1U<<AON_GPADC_DIFF_MODE_LEN)-1)<<AON_GPADC_DIFF_MODE_POS))
#define AON_GPADC_VREF_SEL                                      AON_GPADC_VREF_SEL
#define AON_GPADC_VREF_SEL_POS                                  (3U)
#define AON_GPADC_VREF_SEL_LEN                                  (1U)
#define AON_GPADC_VREF_SEL_MSK                                  (((1U<<AON_GPADC_VREF_SEL_LEN)-1)<<AON_GPADC_VREF_SEL_POS)
#define AON_GPADC_VREF_SEL_UMSK                                 (~(((1U<<AON_GPADC_VREF_SEL_LEN)-1)<<AON_GPADC_VREF_SEL_POS))
#define AON_GPADC_VBAT_EN                                       AON_GPADC_VBAT_EN
#define AON_GPADC_VBAT_EN_POS                                   (4U)
#define AON_GPADC_VBAT_EN_LEN                                   (1U)
#define AON_GPADC_VBAT_EN_MSK                                   (((1U<<AON_GPADC_VBAT_EN_LEN)-1)<<AON_GPADC_VBAT_EN_POS)
#define AON_GPADC_VBAT_EN_UMSK                                  (~(((1U<<AON_GPADC_VBAT_EN_LEN)-1)<<AON_GPADC_VBAT_EN_POS))
#define AON_GPADC_TSEXT_SEL                                     AON_GPADC_TSEXT_SEL
#define AON_GPADC_TSEXT_SEL_POS                                 (5U)
#define AON_GPADC_TSEXT_SEL_LEN                                 (1U)
#define AON_GPADC_TSEXT_SEL_MSK                                 (((1U<<AON_GPADC_TSEXT_SEL_LEN)-1)<<AON_GPADC_TSEXT_SEL_POS)
#define AON_GPADC_TSEXT_SEL_UMSK                                (~(((1U<<AON_GPADC_TSEXT_SEL_LEN)-1)<<AON_GPADC_TSEXT_SEL_POS))
#define AON_GPADC_TS_EN                                         AON_GPADC_TS_EN
#define AON_GPADC_TS_EN_POS                                     (6U)
#define AON_GPADC_TS_EN_LEN                                     (1U)
#define AON_GPADC_TS_EN_MSK                                     (((1U<<AON_GPADC_TS_EN_LEN)-1)<<AON_GPADC_TS_EN_POS)
#define AON_GPADC_TS_EN_UMSK                                    (~(((1U<<AON_GPADC_TS_EN_LEN)-1)<<AON_GPADC_TS_EN_POS))
#define AON_GPADC_PGA_VCM                                       AON_GPADC_PGA_VCM
#define AON_GPADC_PGA_VCM_POS                                   (7U)
#define AON_GPADC_PGA_VCM_LEN                                   (2U)
#define AON_GPADC_PGA_VCM_MSK                                   (((1U<<AON_GPADC_PGA_VCM_LEN)-1)<<AON_GPADC_PGA_VCM_POS)
#define AON_GPADC_PGA_VCM_UMSK                                  (~(((1U<<AON_GPADC_PGA_VCM_LEN)-1)<<AON_GPADC_PGA_VCM_POS))
#define AON_GPADC_PGA_OS_CAL                                    AON_GPADC_PGA_OS_CAL
#define AON_GPADC_PGA_OS_CAL_POS                                (9U)
#define AON_GPADC_PGA_OS_CAL_LEN                                (4U)
#define AON_GPADC_PGA_OS_CAL_MSK                                (((1U<<AON_GPADC_PGA_OS_CAL_LEN)-1)<<AON_GPADC_PGA_OS_CAL_POS)
#define AON_GPADC_PGA_OS_CAL_UMSK                               (~(((1U<<AON_GPADC_PGA_OS_CAL_LEN)-1)<<AON_GPADC_PGA_OS_CAL_POS))
#define AON_GPADC_PGA_EN                                        AON_GPADC_PGA_EN
#define AON_GPADC_PGA_EN_POS                                    (13U)
#define AON_GPADC_PGA_EN_LEN                                    (1U)
#define AON_GPADC_PGA_EN_MSK                                    (((1U<<AON_GPADC_PGA_EN_LEN)-1)<<AON_GPADC_PGA_EN_POS)
#define AON_GPADC_PGA_EN_UMSK                                   (~(((1U<<AON_GPADC_PGA_EN_LEN)-1)<<AON_GPADC_PGA_EN_POS))
#define AON_GPADC_PGA_VCMI_EN                                   AON_GPADC_PGA_VCMI_EN
#define AON_GPADC_PGA_VCMI_EN_POS                               (14U)
#define AON_GPADC_PGA_VCMI_EN_LEN                               (1U)
#define AON_GPADC_PGA_VCMI_EN_MSK                               (((1U<<AON_GPADC_PGA_VCMI_EN_LEN)-1)<<AON_GPADC_PGA_VCMI_EN_POS)
#define AON_GPADC_PGA_VCMI_EN_UMSK                              (~(((1U<<AON_GPADC_PGA_VCMI_EN_LEN)-1)<<AON_GPADC_PGA_VCMI_EN_POS))
#define AON_GPADC_CHOP_MODE                                     AON_GPADC_CHOP_MODE
#define AON_GPADC_CHOP_MODE_POS                                 (15U)
#define AON_GPADC_CHOP_MODE_LEN                                 (2U)
#define AON_GPADC_CHOP_MODE_MSK                                 (((1U<<AON_GPADC_CHOP_MODE_LEN)-1)<<AON_GPADC_CHOP_MODE_POS)
#define AON_GPADC_CHOP_MODE_UMSK                                (~(((1U<<AON_GPADC_CHOP_MODE_LEN)-1)<<AON_GPADC_CHOP_MODE_POS))
#define AON_GPADC_BIAS_SEL                                      AON_GPADC_BIAS_SEL
#define AON_GPADC_BIAS_SEL_POS                                  (17U)
#define AON_GPADC_BIAS_SEL_LEN                                  (1U)
#define AON_GPADC_BIAS_SEL_MSK                                  (((1U<<AON_GPADC_BIAS_SEL_LEN)-1)<<AON_GPADC_BIAS_SEL_POS)
#define AON_GPADC_BIAS_SEL_UMSK                                 (~(((1U<<AON_GPADC_BIAS_SEL_LEN)-1)<<AON_GPADC_BIAS_SEL_POS))
#define AON_GPADC_TEST_EN                                       AON_GPADC_TEST_EN
#define AON_GPADC_TEST_EN_POS                                   (18U)
#define AON_GPADC_TEST_EN_LEN                                   (1U)
#define AON_GPADC_TEST_EN_MSK                                   (((1U<<AON_GPADC_TEST_EN_LEN)-1)<<AON_GPADC_TEST_EN_POS)
#define AON_GPADC_TEST_EN_UMSK                                  (~(((1U<<AON_GPADC_TEST_EN_LEN)-1)<<AON_GPADC_TEST_EN_POS))
#define AON_GPADC_TEST_SEL                                      AON_GPADC_TEST_SEL
#define AON_GPADC_TEST_SEL_POS                                  (19U)
#define AON_GPADC_TEST_SEL_LEN                                  (3U)
#define AON_GPADC_TEST_SEL_MSK                                  (((1U<<AON_GPADC_TEST_SEL_LEN)-1)<<AON_GPADC_TEST_SEL_POS)
#define AON_GPADC_TEST_SEL_UMSK                                 (~(((1U<<AON_GPADC_TEST_SEL_LEN)-1)<<AON_GPADC_TEST_SEL_POS))
#define AON_GPADC_PGA2_GAIN                                     AON_GPADC_PGA2_GAIN
#define AON_GPADC_PGA2_GAIN_POS                                 (22U)
#define AON_GPADC_PGA2_GAIN_LEN                                 (3U)
#define AON_GPADC_PGA2_GAIN_MSK                                 (((1U<<AON_GPADC_PGA2_GAIN_LEN)-1)<<AON_GPADC_PGA2_GAIN_POS)
#define AON_GPADC_PGA2_GAIN_UMSK                                (~(((1U<<AON_GPADC_PGA2_GAIN_LEN)-1)<<AON_GPADC_PGA2_GAIN_POS))
#define AON_GPADC_PGA1_GAIN                                     AON_GPADC_PGA1_GAIN
#define AON_GPADC_PGA1_GAIN_POS                                 (25U)
#define AON_GPADC_PGA1_GAIN_LEN                                 (3U)
#define AON_GPADC_PGA1_GAIN_MSK                                 (((1U<<AON_GPADC_PGA1_GAIN_LEN)-1)<<AON_GPADC_PGA1_GAIN_POS)
#define AON_GPADC_PGA1_GAIN_UMSK                                (~(((1U<<AON_GPADC_PGA1_GAIN_LEN)-1)<<AON_GPADC_PGA1_GAIN_POS))
#define AON_GPADC_DLY_SEL                                       AON_GPADC_DLY_SEL
#define AON_GPADC_DLY_SEL_POS                                   (28U)
#define AON_GPADC_DLY_SEL_LEN                                   (3U)
#define AON_GPADC_DLY_SEL_MSK                                   (((1U<<AON_GPADC_DLY_SEL_LEN)-1)<<AON_GPADC_DLY_SEL_POS)
#define AON_GPADC_DLY_SEL_UMSK                                  (~(((1U<<AON_GPADC_DLY_SEL_LEN)-1)<<AON_GPADC_DLY_SEL_POS))
#define AON_GPADC_TSVBE_LOW                                     AON_GPADC_TSVBE_LOW
#define AON_GPADC_TSVBE_LOW_POS                                 (31U)
#define AON_GPADC_TSVBE_LOW_LEN                                 (1U)
#define AON_GPADC_TSVBE_LOW_MSK                                 (((1U<<AON_GPADC_TSVBE_LOW_LEN)-1)<<AON_GPADC_TSVBE_LOW_POS)
#define AON_GPADC_TSVBE_LOW_UMSK                                (~(((1U<<AON_GPADC_TSVBE_LOW_LEN)-1)<<AON_GPADC_TSVBE_LOW_POS))

/* 0x918 : adc converation sequence 1 */
#define AON_GPADC_REG_SCN_POS1_OFFSET                           (0x918)
#define AON_GPADC_SCAN_POS_0                                    AON_GPADC_SCAN_POS_0
#define AON_GPADC_SCAN_POS_0_POS                                (0U)
#define AON_GPADC_SCAN_POS_0_LEN                                (5U)
#define AON_GPADC_SCAN_POS_0_MSK                                (((1U<<AON_GPADC_SCAN_POS_0_LEN)-1)<<AON_GPADC_SCAN_POS_0_POS)
#define AON_GPADC_SCAN_POS_0_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_0_LEN)-1)<<AON_GPADC_SCAN_POS_0_POS))
#define AON_GPADC_SCAN_POS_1                                    AON_GPADC_SCAN_POS_1
#define AON_GPADC_SCAN_POS_1_POS                                (5U)
#define AON_GPADC_SCAN_POS_1_LEN                                (5U)
#define AON_GPADC_SCAN_POS_1_MSK                                (((1U<<AON_GPADC_SCAN_POS_1_LEN)-1)<<AON_GPADC_SCAN_POS_1_POS)
#define AON_GPADC_SCAN_POS_1_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_1_LEN)-1)<<AON_GPADC_SCAN_POS_1_POS))
#define AON_GPADC_SCAN_POS_2                                    AON_GPADC_SCAN_POS_2
#define AON_GPADC_SCAN_POS_2_POS                                (10U)
#define AON_GPADC_SCAN_POS_2_LEN                                (5U)
#define AON_GPADC_SCAN_POS_2_MSK                                (((1U<<AON_GPADC_SCAN_POS_2_LEN)-1)<<AON_GPADC_SCAN_POS_2_POS)
#define AON_GPADC_SCAN_POS_2_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_2_LEN)-1)<<AON_GPADC_SCAN_POS_2_POS))
#define AON_GPADC_SCAN_POS_3                                    AON_GPADC_SCAN_POS_3
#define AON_GPADC_SCAN_POS_3_POS                                (15U)
#define AON_GPADC_SCAN_POS_3_LEN                                (5U)
#define AON_GPADC_SCAN_POS_3_MSK                                (((1U<<AON_GPADC_SCAN_POS_3_LEN)-1)<<AON_GPADC_SCAN_POS_3_POS)
#define AON_GPADC_SCAN_POS_3_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_3_LEN)-1)<<AON_GPADC_SCAN_POS_3_POS))
#define AON_GPADC_SCAN_POS_4                                    AON_GPADC_SCAN_POS_4
#define AON_GPADC_SCAN_POS_4_POS                                (20U)
#define AON_GPADC_SCAN_POS_4_LEN                                (5U)
#define AON_GPADC_SCAN_POS_4_MSK                                (((1U<<AON_GPADC_SCAN_POS_4_LEN)-1)<<AON_GPADC_SCAN_POS_4_POS)
#define AON_GPADC_SCAN_POS_4_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_4_LEN)-1)<<AON_GPADC_SCAN_POS_4_POS))
#define AON_GPADC_SCAN_POS_5                                    AON_GPADC_SCAN_POS_5
#define AON_GPADC_SCAN_POS_5_POS                                (25U)
#define AON_GPADC_SCAN_POS_5_LEN                                (5U)
#define AON_GPADC_SCAN_POS_5_MSK                                (((1U<<AON_GPADC_SCAN_POS_5_LEN)-1)<<AON_GPADC_SCAN_POS_5_POS)
#define AON_GPADC_SCAN_POS_5_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_5_LEN)-1)<<AON_GPADC_SCAN_POS_5_POS))

/* 0x91C : adc converation sequence 2 */
#define AON_GPADC_REG_SCN_POS2_OFFSET                           (0x91C)
#define AON_GPADC_SCAN_POS_6                                    AON_GPADC_SCAN_POS_6
#define AON_GPADC_SCAN_POS_6_POS                                (0U)
#define AON_GPADC_SCAN_POS_6_LEN                                (5U)
#define AON_GPADC_SCAN_POS_6_MSK                                (((1U<<AON_GPADC_SCAN_POS_6_LEN)-1)<<AON_GPADC_SCAN_POS_6_POS)
#define AON_GPADC_SCAN_POS_6_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_6_LEN)-1)<<AON_GPADC_SCAN_POS_6_POS))
#define AON_GPADC_SCAN_POS_7                                    AON_GPADC_SCAN_POS_7
#define AON_GPADC_SCAN_POS_7_POS                                (5U)
#define AON_GPADC_SCAN_POS_7_LEN                                (5U)
#define AON_GPADC_SCAN_POS_7_MSK                                (((1U<<AON_GPADC_SCAN_POS_7_LEN)-1)<<AON_GPADC_SCAN_POS_7_POS)
#define AON_GPADC_SCAN_POS_7_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_7_LEN)-1)<<AON_GPADC_SCAN_POS_7_POS))
#define AON_GPADC_SCAN_POS_8                                    AON_GPADC_SCAN_POS_8
#define AON_GPADC_SCAN_POS_8_POS                                (10U)
#define AON_GPADC_SCAN_POS_8_LEN                                (5U)
#define AON_GPADC_SCAN_POS_8_MSK                                (((1U<<AON_GPADC_SCAN_POS_8_LEN)-1)<<AON_GPADC_SCAN_POS_8_POS)
#define AON_GPADC_SCAN_POS_8_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_8_LEN)-1)<<AON_GPADC_SCAN_POS_8_POS))
#define AON_GPADC_SCAN_POS_9                                    AON_GPADC_SCAN_POS_9
#define AON_GPADC_SCAN_POS_9_POS                                (15U)
#define AON_GPADC_SCAN_POS_9_LEN                                (5U)
#define AON_GPADC_SCAN_POS_9_MSK                                (((1U<<AON_GPADC_SCAN_POS_9_LEN)-1)<<AON_GPADC_SCAN_POS_9_POS)
#define AON_GPADC_SCAN_POS_9_UMSK                               (~(((1U<<AON_GPADC_SCAN_POS_9_LEN)-1)<<AON_GPADC_SCAN_POS_9_POS))
#define AON_GPADC_SCAN_POS_10                                   AON_GPADC_SCAN_POS_10
#define AON_GPADC_SCAN_POS_10_POS                               (20U)
#define AON_GPADC_SCAN_POS_10_LEN                               (5U)
#define AON_GPADC_SCAN_POS_10_MSK                               (((1U<<AON_GPADC_SCAN_POS_10_LEN)-1)<<AON_GPADC_SCAN_POS_10_POS)
#define AON_GPADC_SCAN_POS_10_UMSK                              (~(((1U<<AON_GPADC_SCAN_POS_10_LEN)-1)<<AON_GPADC_SCAN_POS_10_POS))
#define AON_GPADC_SCAN_POS_11                                   AON_GPADC_SCAN_POS_11
#define AON_GPADC_SCAN_POS_11_POS                               (25U)
#define AON_GPADC_SCAN_POS_11_LEN                               (5U)
#define AON_GPADC_SCAN_POS_11_MSK                               (((1U<<AON_GPADC_SCAN_POS_11_LEN)-1)<<AON_GPADC_SCAN_POS_11_POS)
#define AON_GPADC_SCAN_POS_11_UMSK                              (~(((1U<<AON_GPADC_SCAN_POS_11_LEN)-1)<<AON_GPADC_SCAN_POS_11_POS))

/* 0x920 : adc converation sequence 3 */
#define AON_GPADC_REG_SCN_NEG1_OFFSET                           (0x920)
#define AON_GPADC_SCAN_NEG_0                                    AON_GPADC_SCAN_NEG_0
#define AON_GPADC_SCAN_NEG_0_POS                                (0U)
#define AON_GPADC_SCAN_NEG_0_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_0_MSK                                (((1U<<AON_GPADC_SCAN_NEG_0_LEN)-1)<<AON_GPADC_SCAN_NEG_0_POS)
#define AON_GPADC_SCAN_NEG_0_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_0_LEN)-1)<<AON_GPADC_SCAN_NEG_0_POS))
#define AON_GPADC_SCAN_NEG_1                                    AON_GPADC_SCAN_NEG_1
#define AON_GPADC_SCAN_NEG_1_POS                                (5U)
#define AON_GPADC_SCAN_NEG_1_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_1_MSK                                (((1U<<AON_GPADC_SCAN_NEG_1_LEN)-1)<<AON_GPADC_SCAN_NEG_1_POS)
#define AON_GPADC_SCAN_NEG_1_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_1_LEN)-1)<<AON_GPADC_SCAN_NEG_1_POS))
#define AON_GPADC_SCAN_NEG_2                                    AON_GPADC_SCAN_NEG_2
#define AON_GPADC_SCAN_NEG_2_POS                                (10U)
#define AON_GPADC_SCAN_NEG_2_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_2_MSK                                (((1U<<AON_GPADC_SCAN_NEG_2_LEN)-1)<<AON_GPADC_SCAN_NEG_2_POS)
#define AON_GPADC_SCAN_NEG_2_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_2_LEN)-1)<<AON_GPADC_SCAN_NEG_2_POS))
#define AON_GPADC_SCAN_NEG_3                                    AON_GPADC_SCAN_NEG_3
#define AON_GPADC_SCAN_NEG_3_POS                                (15U)
#define AON_GPADC_SCAN_NEG_3_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_3_MSK                                (((1U<<AON_GPADC_SCAN_NEG_3_LEN)-1)<<AON_GPADC_SCAN_NEG_3_POS)
#define AON_GPADC_SCAN_NEG_3_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_3_LEN)-1)<<AON_GPADC_SCAN_NEG_3_POS))
#define AON_GPADC_SCAN_NEG_4                                    AON_GPADC_SCAN_NEG_4
#define AON_GPADC_SCAN_NEG_4_POS                                (20U)
#define AON_GPADC_SCAN_NEG_4_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_4_MSK                                (((1U<<AON_GPADC_SCAN_NEG_4_LEN)-1)<<AON_GPADC_SCAN_NEG_4_POS)
#define AON_GPADC_SCAN_NEG_4_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_4_LEN)-1)<<AON_GPADC_SCAN_NEG_4_POS))
#define AON_GPADC_SCAN_NEG_5                                    AON_GPADC_SCAN_NEG_5
#define AON_GPADC_SCAN_NEG_5_POS                                (25U)
#define AON_GPADC_SCAN_NEG_5_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_5_MSK                                (((1U<<AON_GPADC_SCAN_NEG_5_LEN)-1)<<AON_GPADC_SCAN_NEG_5_POS)
#define AON_GPADC_SCAN_NEG_5_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_5_LEN)-1)<<AON_GPADC_SCAN_NEG_5_POS))

/* 0x924 : adc converation sequence 4 */
#define AON_GPADC_REG_SCN_NEG2_OFFSET                           (0x924)
#define AON_GPADC_SCAN_NEG_6                                    AON_GPADC_SCAN_NEG_6
#define AON_GPADC_SCAN_NEG_6_POS                                (0U)
#define AON_GPADC_SCAN_NEG_6_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_6_MSK                                (((1U<<AON_GPADC_SCAN_NEG_6_LEN)-1)<<AON_GPADC_SCAN_NEG_6_POS)
#define AON_GPADC_SCAN_NEG_6_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_6_LEN)-1)<<AON_GPADC_SCAN_NEG_6_POS))
#define AON_GPADC_SCAN_NEG_7                                    AON_GPADC_SCAN_NEG_7
#define AON_GPADC_SCAN_NEG_7_POS                                (5U)
#define AON_GPADC_SCAN_NEG_7_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_7_MSK                                (((1U<<AON_GPADC_SCAN_NEG_7_LEN)-1)<<AON_GPADC_SCAN_NEG_7_POS)
#define AON_GPADC_SCAN_NEG_7_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_7_LEN)-1)<<AON_GPADC_SCAN_NEG_7_POS))
#define AON_GPADC_SCAN_NEG_8                                    AON_GPADC_SCAN_NEG_8
#define AON_GPADC_SCAN_NEG_8_POS                                (10U)
#define AON_GPADC_SCAN_NEG_8_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_8_MSK                                (((1U<<AON_GPADC_SCAN_NEG_8_LEN)-1)<<AON_GPADC_SCAN_NEG_8_POS)
#define AON_GPADC_SCAN_NEG_8_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_8_LEN)-1)<<AON_GPADC_SCAN_NEG_8_POS))
#define AON_GPADC_SCAN_NEG_9                                    AON_GPADC_SCAN_NEG_9
#define AON_GPADC_SCAN_NEG_9_POS                                (15U)
#define AON_GPADC_SCAN_NEG_9_LEN                                (5U)
#define AON_GPADC_SCAN_NEG_9_MSK                                (((1U<<AON_GPADC_SCAN_NEG_9_LEN)-1)<<AON_GPADC_SCAN_NEG_9_POS)
#define AON_GPADC_SCAN_NEG_9_UMSK                               (~(((1U<<AON_GPADC_SCAN_NEG_9_LEN)-1)<<AON_GPADC_SCAN_NEG_9_POS))
#define AON_GPADC_SCAN_NEG_10                                   AON_GPADC_SCAN_NEG_10
#define AON_GPADC_SCAN_NEG_10_POS                               (20U)
#define AON_GPADC_SCAN_NEG_10_LEN                               (5U)
#define AON_GPADC_SCAN_NEG_10_MSK                               (((1U<<AON_GPADC_SCAN_NEG_10_LEN)-1)<<AON_GPADC_SCAN_NEG_10_POS)
#define AON_GPADC_SCAN_NEG_10_UMSK                              (~(((1U<<AON_GPADC_SCAN_NEG_10_LEN)-1)<<AON_GPADC_SCAN_NEG_10_POS))
#define AON_GPADC_SCAN_NEG_11                                   AON_GPADC_SCAN_NEG_11
#define AON_GPADC_SCAN_NEG_11_POS                               (25U)
#define AON_GPADC_SCAN_NEG_11_LEN                               (5U)
#define AON_GPADC_SCAN_NEG_11_MSK                               (((1U<<AON_GPADC_SCAN_NEG_11_LEN)-1)<<AON_GPADC_SCAN_NEG_11_POS)
#define AON_GPADC_SCAN_NEG_11_UMSK                              (~(((1U<<AON_GPADC_SCAN_NEG_11_LEN)-1)<<AON_GPADC_SCAN_NEG_11_POS))

/* 0x928 : gpadc_reg_status */
#define AON_GPADC_REG_STATUS_OFFSET                             (0x928)
#define AON_GPADC_DATA_RDY                                      AON_GPADC_DATA_RDY
#define AON_GPADC_DATA_RDY_POS                                  (0U)
#define AON_GPADC_DATA_RDY_LEN                                  (1U)
#define AON_GPADC_DATA_RDY_MSK                                  (((1U<<AON_GPADC_DATA_RDY_LEN)-1)<<AON_GPADC_DATA_RDY_POS)
#define AON_GPADC_DATA_RDY_UMSK                                 (~(((1U<<AON_GPADC_DATA_RDY_LEN)-1)<<AON_GPADC_DATA_RDY_POS))
#define AON_GPADC_RESERVED                                      AON_GPADC_RESERVED
#define AON_GPADC_RESERVED_POS                                  (16U)
#define AON_GPADC_RESERVED_LEN                                  (16U)
#define AON_GPADC_RESERVED_MSK                                  (((1U<<AON_GPADC_RESERVED_LEN)-1)<<AON_GPADC_RESERVED_POS)
#define AON_GPADC_RESERVED_UMSK                                 (~(((1U<<AON_GPADC_RESERVED_LEN)-1)<<AON_GPADC_RESERVED_POS))

/* 0x92C : gpadc_reg_isr */
#define AON_GPADC_REG_ISR_OFFSET                                (0x92C)
#define AON_GPADC_NEG_SATUR                                     AON_GPADC_NEG_SATUR
#define AON_GPADC_NEG_SATUR_POS                                 (0U)
#define AON_GPADC_NEG_SATUR_LEN                                 (1U)
#define AON_GPADC_NEG_SATUR_MSK                                 (((1U<<AON_GPADC_NEG_SATUR_LEN)-1)<<AON_GPADC_NEG_SATUR_POS)
#define AON_GPADC_NEG_SATUR_UMSK                                (~(((1U<<AON_GPADC_NEG_SATUR_LEN)-1)<<AON_GPADC_NEG_SATUR_POS))
#define AON_GPADC_POS_SATUR                                     AON_GPADC_POS_SATUR
#define AON_GPADC_POS_SATUR_POS                                 (1U)
#define AON_GPADC_POS_SATUR_LEN                                 (1U)
#define AON_GPADC_POS_SATUR_MSK                                 (((1U<<AON_GPADC_POS_SATUR_LEN)-1)<<AON_GPADC_POS_SATUR_POS)
#define AON_GPADC_POS_SATUR_UMSK                                (~(((1U<<AON_GPADC_POS_SATUR_LEN)-1)<<AON_GPADC_POS_SATUR_POS))
#define AON_GPADC_NEG_SATUR_CLR                                 AON_GPADC_NEG_SATUR_CLR
#define AON_GPADC_NEG_SATUR_CLR_POS                             (4U)
#define AON_GPADC_NEG_SATUR_CLR_LEN                             (1U)
#define AON_GPADC_NEG_SATUR_CLR_MSK                             (((1U<<AON_GPADC_NEG_SATUR_CLR_LEN)-1)<<AON_GPADC_NEG_SATUR_CLR_POS)
#define AON_GPADC_NEG_SATUR_CLR_UMSK                            (~(((1U<<AON_GPADC_NEG_SATUR_CLR_LEN)-1)<<AON_GPADC_NEG_SATUR_CLR_POS))
#define AON_GPADC_POS_SATUR_CLR                                 AON_GPADC_POS_SATUR_CLR
#define AON_GPADC_POS_SATUR_CLR_POS                             (5U)
#define AON_GPADC_POS_SATUR_CLR_LEN                             (1U)
#define AON_GPADC_POS_SATUR_CLR_MSK                             (((1U<<AON_GPADC_POS_SATUR_CLR_LEN)-1)<<AON_GPADC_POS_SATUR_CLR_POS)
#define AON_GPADC_POS_SATUR_CLR_UMSK                            (~(((1U<<AON_GPADC_POS_SATUR_CLR_LEN)-1)<<AON_GPADC_POS_SATUR_CLR_POS))
#define AON_GPADC_NEG_SATUR_MASK                                AON_GPADC_NEG_SATUR_MASK
#define AON_GPADC_NEG_SATUR_MASK_POS                            (8U)
#define AON_GPADC_NEG_SATUR_MASK_LEN                            (1U)
#define AON_GPADC_NEG_SATUR_MASK_MSK                            (((1U<<AON_GPADC_NEG_SATUR_MASK_LEN)-1)<<AON_GPADC_NEG_SATUR_MASK_POS)
#define AON_GPADC_NEG_SATUR_MASK_UMSK                           (~(((1U<<AON_GPADC_NEG_SATUR_MASK_LEN)-1)<<AON_GPADC_NEG_SATUR_MASK_POS))
#define AON_GPADC_POS_SATUR_MASK                                AON_GPADC_POS_SATUR_MASK
#define AON_GPADC_POS_SATUR_MASK_POS                            (9U)
#define AON_GPADC_POS_SATUR_MASK_LEN                            (1U)
#define AON_GPADC_POS_SATUR_MASK_MSK                            (((1U<<AON_GPADC_POS_SATUR_MASK_LEN)-1)<<AON_GPADC_POS_SATUR_MASK_POS)
#define AON_GPADC_POS_SATUR_MASK_UMSK                           (~(((1U<<AON_GPADC_POS_SATUR_MASK_LEN)-1)<<AON_GPADC_POS_SATUR_MASK_POS))

/* 0x930 : gpadc_reg_result */
#define AON_GPADC_REG_RESULT_OFFSET                             (0x930)
#define AON_GPADC_DATA_OUT                                      AON_GPADC_DATA_OUT
#define AON_GPADC_DATA_OUT_POS                                  (0U)
#define AON_GPADC_DATA_OUT_LEN                                  (26U)
#define AON_GPADC_DATA_OUT_MSK                                  (((1U<<AON_GPADC_DATA_OUT_LEN)-1)<<AON_GPADC_DATA_OUT_POS)
#define AON_GPADC_DATA_OUT_UMSK                                 (~(((1U<<AON_GPADC_DATA_OUT_LEN)-1)<<AON_GPADC_DATA_OUT_POS))

/* 0x934 : gpadc_reg_raw_result */
#define AON_GPADC_REG_RAW_RESULT_OFFSET                         (0x934)
#define AON_GPADC_RAW_DATA                                      AON_GPADC_RAW_DATA
#define AON_GPADC_RAW_DATA_POS                                  (0U)
#define AON_GPADC_RAW_DATA_LEN                                  (12U)
#define AON_GPADC_RAW_DATA_MSK                                  (((1U<<AON_GPADC_RAW_DATA_LEN)-1)<<AON_GPADC_RAW_DATA_POS)
#define AON_GPADC_RAW_DATA_UMSK                                 (~(((1U<<AON_GPADC_RAW_DATA_LEN)-1)<<AON_GPADC_RAW_DATA_POS))

/* 0x938 : gpadc_reg_define */
#define AON_GPADC_REG_DEFINE_OFFSET                             (0x938)
#define AON_GPADC_OS_CAL_DATA                                   AON_GPADC_OS_CAL_DATA
#define AON_GPADC_OS_CAL_DATA_POS                               (0U)
#define AON_GPADC_OS_CAL_DATA_LEN                               (16U)
#define AON_GPADC_OS_CAL_DATA_MSK                               (((1U<<AON_GPADC_OS_CAL_DATA_LEN)-1)<<AON_GPADC_OS_CAL_DATA_POS)
#define AON_GPADC_OS_CAL_DATA_UMSK                              (~(((1U<<AON_GPADC_OS_CAL_DATA_LEN)-1)<<AON_GPADC_OS_CAL_DATA_POS))

/* 0x93C : hbncore_resv0 */
#define AON_HBNCORE_RESV0_OFFSET                                (0x93C)
#define AON_HBNCORE_RESV0_DATA                                  AON_HBNCORE_RESV0_DATA
#define AON_HBNCORE_RESV0_DATA_POS                              (0U)
#define AON_HBNCORE_RESV0_DATA_LEN                              (32U)
#define AON_HBNCORE_RESV0_DATA_MSK                              (((1U<<AON_HBNCORE_RESV0_DATA_LEN)-1)<<AON_HBNCORE_RESV0_DATA_POS)
#define AON_HBNCORE_RESV0_DATA_UMSK                             (~(((1U<<AON_HBNCORE_RESV0_DATA_LEN)-1)<<AON_HBNCORE_RESV0_DATA_POS))

/* 0x940 : hbncore_resv1 */
#define AON_HBNCORE_RESV1_OFFSET                                (0x940)
#define AON_HBNCORE_RESV1_DATA                                  AON_HBNCORE_RESV1_DATA
#define AON_HBNCORE_RESV1_DATA_POS                              (0U)
#define AON_HBNCORE_RESV1_DATA_LEN                              (32U)
#define AON_HBNCORE_RESV1_DATA_MSK                              (((1U<<AON_HBNCORE_RESV1_DATA_LEN)-1)<<AON_HBNCORE_RESV1_DATA_POS)
#define AON_HBNCORE_RESV1_DATA_UMSK                             (~(((1U<<AON_HBNCORE_RESV1_DATA_LEN)-1)<<AON_HBNCORE_RESV1_DATA_POS))


struct  aon_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[2048];

    /* 0x800 : aon */
    union {
        struct {
            uint32_t aon_resv                       :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reserved_8_11                  :  4; /* [11: 8],       rsvd,        0x0 */
            uint32_t pu_aon_dc_tbuf                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_19                 :  7; /* [19:13],       rsvd,        0x0 */
            uint32_t ldo11_rt_pulldown              :  1; /* [   20],        r/w,        0x0 */
            uint32_t ldo11_rt_pulldown_sel          :  1; /* [   21],        r/w,        0x0 */
            uint32_t sw_pu_ldo11_rt                 :  1; /* [   22],        r/w,        0x1 */
            uint32_t reserved_23_31                 :  9; /* [31:23],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } aon;

    /* 0x804 : aon_common */
    union {
        struct {
            uint32_t tmux_aon                       :  3; /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t ten_aon                        :  1; /* [    4],        r/w,        0x0 */
            uint32_t dten_xtal32k                   :  1; /* [    5],        r/w,        0x0 */
            uint32_t ten_xtal32k                    :  1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t ten_vddcore_aon                :  1; /* [    8],        r/w,        0x0 */
            uint32_t pmip_dc_tp_out_en_aon          :  1; /* [    9],        r/w,        0x0 */
            uint32_t ten_dcdc_0_aon                 :  1; /* [   10],        r/w,        0x0 */
            uint32_t ten_dcdc_1_aon                 :  1; /* [   11],        r/w,        0x0 */
            uint32_t ten_bg_sys_aon                 :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_14                 :  2; /* [14:13],       rsvd,        0x0 */
            uint32_t ten_bz_ldo15rf_aon             :  1; /* [   15],        r/w,        0x0 */
            uint32_t ten_ldo15rf_aon                :  1; /* [   16],        r/w,        0x0 */
            uint32_t ten_xtal_aon                   :  1; /* [   17],        r/w,        0x0 */
            uint32_t dten_xtal_aon                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t ten_mbg_aon                    :  1; /* [   19],        r/w,        0x0 */
            uint32_t ten_cip_misc_aon               :  1; /* [   20],        r/w,        0x0 */
            uint32_t reserved_21_31                 : 11; /* [31:21],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } aon_common;

    /* 0x808 : aon_misc */
    union {
        struct {
            uint32_t sw_soc_en_aon                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t sw_wb_en_aon                   :  1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_31                  : 30; /* [31: 2],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } aon_misc;

    /* 0x80c  reserved */
    uint8_t RESERVED0x80c[4];

    /* 0x810 : bg_sys_top */
    union {
        struct {
            uint32_t pmip_resv                      :  8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t pu_bg_sys_aon                  :  1; /* [    8],        r/w,        0x1 */
            uint32_t reserved_9_11                  :  3; /* [11: 9],       rsvd,        0x0 */
            uint32_t bg_sys_start_ctrl_aon          :  1; /* [   12],        r/w,        0x1 */
            uint32_t reserved_13_31                 : 19; /* [31:13],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } bg_sys_top;

    /* 0x814 : dcdc_top_0 */
    union {
        struct {
            uint32_t dcdc_vout_sel_aon              :  5; /* [ 4: 0],        r/w,        0x8 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t dcdc_vpfm_aon                  :  4; /* [11: 8],        r/w,        0x7 */
            uint32_t dcdc_osc_2m_mode_aon           :  1; /* [   12],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t dcdc_osc_freq_trim_aon         :  4; /* [19:16],        r/w,        0x8 */
            uint32_t dcdc_slope_curr_sel_aon        :  5; /* [24:20],        r/w,        0x5 */
            uint32_t dcdc_en_stop_osc_aon           :  1; /* [   25],        r/w,        0x1 */
            uint32_t dcdc_en_slow_osc_aon           :  1; /* [   26],        r/w,        0x0 */
            uint32_t dcdc_en_osc_inhibit_t2_aon     :  1; /* [   27],        r/w,        0x0 */
            uint32_t dcdc_sstart_time_aon           :  2; /* [29:28],        r/w,        0x0 */
            uint32_t reserved_30                    :  1; /* [   30],       rsvd,        0x0 */
            uint32_t dcdc_rdy_aon                   :  1; /* [   31],          r,        0x1 */
        }BF;
        uint32_t WORD;
    } dcdc_top_0;

    /* 0x818 : dcdc_top_1 */
    union {
        struct {
            uint32_t dcdc_force_en_cs_zvs_aon       :  1; /* [    0],        r/w,        0x0 */
            uint32_t dcdc_cs_delay_aon              :  3; /* [ 3: 1],        r/w,        0x4 */
            uint32_t dcdc_zvs_td_opt_aon            :  3; /* [ 6: 4],        r/w,        0x4 */
            uint32_t reserved_7                     :  1; /* [    7],       rsvd,        0x0 */
            uint32_t dcdc_nonoverlap_td_aon         :  5; /* [12: 8],        r/w,        0x0 */
            uint32_t reserved_13_15                 :  3; /* [15:13],       rsvd,        0x0 */
            uint32_t dcdc_rc_sel_aon                :  4; /* [19:16],        r/w,        0x8 */
            uint32_t dcdc_chf_sel_aon               :  4; /* [23:20],        r/w,        0x1 */
            uint32_t dcdc_cfb_sel_aon               :  4; /* [27:24],        r/w,        0x8 */
            uint32_t dcdc_en_antiring_aon           :  1; /* [   28],        r/w,        0x1 */
            uint32_t dcdc_pulldown_aon              :  1; /* [   29],        r/w,        0x0 */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dcdc_top_1;

    /* 0x81C : ldo11soc_and_dctest */
    union {
        struct {
            uint32_t pu_ldo11soc_aon                :  1; /* [    0],        r/w,        0x1 */
            uint32_t reserved_1_29                  : 29; /* [29: 1],       rsvd,        0x0 */
            uint32_t pu_vddcore_misc_aon            :  1; /* [   30],        r/w,        0x1 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } ldo11soc_and_dctest;

    /* 0x820 : psw_irrcv */
    union {
        struct {
            uint32_t pu_ir_psw_aon                  :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_31                  : 31; /* [31: 1],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } psw_irrcv;

    /* 0x824 : dcdc_top_2 */
    union {
        struct {
            uint32_t dcdc_vout_trim_aon             :  4; /* [ 3: 0],        r/w,        0x7 */
            uint32_t dcdc_low_drv_n_str_aon         :  2; /* [ 5: 4],        r/w,        0x3 */
            uint32_t dcdc_low_drv_p_str_aon         :  2; /* [ 7: 6],        r/w,        0x3 */
            uint32_t dcdc_high_drv_n_str_aon        :  2; /* [ 9: 8],        r/w,        0x3 */
            uint32_t dcdc_high_drv_p_str_aon        :  2; /* [11:10],        r/w,        0x3 */
            uint32_t dcdc_comp_gm_sel_aon           :  3; /* [14:12],        r/w,        0x4 */
            uint32_t reserved_15                    :  1; /* [   15],       rsvd,        0x0 */
            uint32_t dcdc_isense_trim_aon           :  3; /* [18:16],        r/w,        0x4 */
            uint32_t reserved_19                    :  1; /* [   19],       rsvd,        0x0 */
            uint32_t dcdc_vc_clamp_vth_aon          :  3; /* [22:20],        r/w,        0x4 */
            uint32_t reserved_23                    :  1; /* [   23],       rsvd,        0x0 */
            uint32_t dcdc_ocp_vth_aon               :  3; /* [26:24],        r/w,        0x4 */
            uint32_t dcdc_ocp_rst_aon               :  1; /* [   27],        r/w,        0x0 */
            uint32_t dcdc_ocp_out_aon               :  1; /* [   28],          r,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } dcdc_top_2;

    /* 0x828  reserved */
    uint8_t RESERVED0x828[88];

    /* 0x880 : rf_top_aon */
    union {
        struct {
            uint32_t pu_mbg_aon                     :  1; /* [    0],        r/w,        0x1 */
            uint32_t pu_ldo15rf_aon                 :  1; /* [    1],        r/w,        0x1 */
            uint32_t pu_sfreg_aon                   :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t pu_xtal_buf_aon                :  1; /* [    4],        r/w,        0x1 */
            uint32_t pu_xtal_aon                    :  1; /* [    5],        r/w,        0x1 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t ldo15rf_sstart_sel_aon         :  1; /* [    8],        r/w,        0x1 */
            uint32_t ldo15rf_sstart_delay_aon       :  2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t ldo15rf_pulldown_aon           :  1; /* [   12],        r/w,        0x0 */
            uint32_t ldo15rf_pulldown_sel_aon       :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t ldo15rf_vout_sel_aon           :  3; /* [18:16],        r/w,        0x2 */
            uint32_t reserved_19_23                 :  5; /* [23:19],       rsvd,        0x0 */
            uint32_t ldo15rf_cc_aon                 :  2; /* [25:24],        r/w,        0x0 */
            uint32_t reserved_26_27                 :  2; /* [27:26],       rsvd,        0x0 */
            uint32_t ldo15rf_bypass_aon             :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } rf_top_aon;

    /* 0x884 : xtal_cfg */
    union {
        struct {
            uint32_t xtal_bk_aon                    :  2; /* [ 1: 0],        r/w,        0x0 */
            uint32_t xtal_capcode_extra_aon         :  1; /* [    2],        r/w,        0x0 */
            uint32_t xtal_ext_sel_aon               :  1; /* [    3],        r/w,        0x0 */
            uint32_t xtal_buf_en_aon                :  4; /* [ 7: 4],        r/w,        0xf */
            uint32_t xtal_buf_hp_aon                :  4; /* [11: 8],        r/w,        0x0 */
            uint32_t xtal_fast_startup_aon          :  1; /* [   12],        r/w,        0x1 */
            uint32_t xtal_sleep_aon                 :  1; /* [   13],        r/w,        0x1 */
            uint32_t xtal_amp_ctrl_aon              :  2; /* [15:14],        r/w,        0x3 */
            uint32_t xtal_capcode_out_aon           :  6; /* [21:16],        r/w,       0x10 */
            uint32_t xtal_capcode_in_aon            :  6; /* [27:22],        r/w,       0x10 */
            uint32_t xtal_gm_boost_aon              :  2; /* [29:28],        r/w,        0x3 */
            uint32_t xtal_rdy_sel_aon               :  2; /* [31:30],        r/w,        0x2 */
        }BF;
        uint32_t WORD;
    } xtal_cfg;

    /* 0x888 : tsen */
    union {
        struct {
            uint32_t tsen_refcode_corner            : 12; /* [11: 0],        r/w,      0x8ff */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t tsen_refcode_rfcal             : 12; /* [27:16],        r/w,      0x8ff */
            uint32_t xtal_rdy                       :  1; /* [   28],          r,        0x1 */
            uint32_t xtal_inn_cfg_en_aon            :  1; /* [   29],        r/w,        0x1 */
            uint32_t xtal_rdy_int_sel_aon           :  2; /* [31:30],        r/w,        0x1 */
        }BF;
        uint32_t WORD;
    } tsen;

    /* 0x88C : rf2_top_aon */
    union {
        struct {
            uint32_t pu_bz_mbg_aon                  :  1; /* [    0],        r/w,        0x1 */
            uint32_t pu_bz_ldo15rf_aon              :  1; /* [    1],        r/w,        0x1 */
            uint32_t pu_bz_sfreg_aon                :  1; /* [    2],        r/w,        0x1 */
            uint32_t reserved_3_7                   :  5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t bz_ldo15rf_sstart_sel_aon      :  1; /* [    8],        r/w,        0x1 */
            uint32_t bz_ldo15rf_sstart_delay_aon    :  2; /* [10: 9],        r/w,        0x0 */
            uint32_t reserved_11                    :  1; /* [   11],       rsvd,        0x0 */
            uint32_t bz_ldo15rf_pulldown_aon        :  1; /* [   12],        r/w,        0x0 */
            uint32_t bz_ldo15rf_pulldown_sel_aon    :  1; /* [   13],        r/w,        0x0 */
            uint32_t reserved_14_15                 :  2; /* [15:14],       rsvd,        0x0 */
            uint32_t bz_ldo15rf_vout_sel_aon        :  3; /* [18:16],        r/w,        0x2 */
            uint32_t reserved_19_23                 :  5; /* [23:19],       rsvd,        0x0 */
            uint32_t bz_ldo15rf_cc_aon              :  2; /* [25:24],        r/w,        0x0 */
            uint32_t reserved_26_27                 :  2; /* [27:26],       rsvd,        0x0 */
            uint32_t bz_ldo15rf_bypass_aon          :  1; /* [   28],        r/w,        0x0 */
            uint32_t reserved_29_31                 :  3; /* [31:29],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } rf2_top_aon;

    /* 0x890  reserved */
    uint8_t RESERVED0x890[112];

    /* 0x900 : acomp0_ctrl */
    union {
        struct {
            uint32_t acomp0_en                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t acomp0_hyst_seln               :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t acomp0_hyst_selp               :  3; /* [ 9: 7],        r/w,        0x0 */
            uint32_t acomp0_bias_prog               :  2; /* [11:10],        r/w,        0x0 */
            uint32_t acomp0_level_sel               :  6; /* [17:12],        r/w,        0x0 */
            uint32_t acomp0_neg_sel                 :  4; /* [21:18],        r/w,        0x0 */
            uint32_t acomp0_pos_sel                 :  4; /* [25:22],        r/w,        0x0 */
            uint32_t acomp0_muxen                   :  1; /* [   26],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } acomp0_ctrl;

    /* 0x904 : acomp1_ctrl */
    union {
        struct {
            uint32_t acomp1_en                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3                   :  3; /* [ 3: 1],       rsvd,        0x0 */
            uint32_t acomp1_hyst_seln               :  3; /* [ 6: 4],        r/w,        0x0 */
            uint32_t acomp1_hyst_selp               :  3; /* [ 9: 7],        r/w,        0x0 */
            uint32_t acomp1_bias_prog               :  2; /* [11:10],        r/w,        0x0 */
            uint32_t acomp1_level_sel               :  6; /* [17:12],        r/w,        0x0 */
            uint32_t acomp1_neg_sel                 :  4; /* [21:18],        r/w,        0x0 */
            uint32_t acomp1_pos_sel                 :  4; /* [25:22],        r/w,        0x0 */
            uint32_t acomp1_muxen                   :  1; /* [   26],        r/w,        0x0 */
            uint32_t reserved_27_31                 :  5; /* [31:27],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } acomp1_ctrl;

    /* 0x908 : acomp_ctrl */
    union {
        struct {
            uint32_t acomp1_rstn_ana                :  1; /* [    0],        r/w,        0x1 */
            uint32_t acomp0_rstn_ana                :  1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_7                   :  6; /* [ 7: 2],       rsvd,        0x0 */
            uint32_t acomp1_test_en                 :  1; /* [    8],        r/w,        0x0 */
            uint32_t acomp0_test_en                 :  1; /* [    9],        r/w,        0x0 */
            uint32_t acomp1_test_sel                :  2; /* [11:10],        r/w,        0x0 */
            uint32_t acomp0_test_sel                :  2; /* [13:12],        r/w,        0x0 */
            uint32_t reserved_14_16                 :  3; /* [16:14],       rsvd,        0x0 */
            uint32_t acomp1_out_raw                 :  1; /* [   17],          r,        0x0 */
            uint32_t reserved_18                    :  1; /* [   18],       rsvd,        0x0 */
            uint32_t acomp0_out_raw                 :  1; /* [   19],          r,        0x0 */
            uint32_t reserved_20_23                 :  4; /* [23:20],       rsvd,        0x0 */
            uint32_t acomp_reserved                 :  8; /* [31:24],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } acomp_ctrl;

    /* 0x90C : gpadc_reg_cmd */
    union {
        struct {
            uint32_t gpadc_global_en                :  1; /* [    0],        r/w,        0x0 */
            uint32_t gpadc_conv_start               :  1; /* [    1],        r/w,        0x0 */
            uint32_t gpadc_soft_rst                 :  1; /* [    2],        r/w,        0x0 */
            uint32_t gpadc_neg_sel                  :  5; /* [ 7: 3],        r/w,        0xf */
            uint32_t gpadc_pos_sel                  :  5; /* [12: 8],        r/w,        0xf */
            uint32_t gpadc_neg_gnd                  :  1; /* [   13],        r/w,        0x0 */
            uint32_t gpadc_micbias_en               :  1; /* [   14],        r/w,        0x0 */
            uint32_t gpadc_micpga_en                :  1; /* [   15],        r/w,        0x0 */
            uint32_t gpadc_byp_micboost             :  1; /* [   16],        r/w,        0x0 */
            uint32_t gpadc_rcal_en                  :  1; /* [   17],        r/w,        0x0 */
            uint32_t gpadc_dwa_en                   :  1; /* [   18],        r/w,        0x0 */
            uint32_t gpadc_mic2_diff                :  1; /* [   19],        r/w,        0x0 */
            uint32_t gpadc_mic1_diff                :  1; /* [   20],        r/w,        0x0 */
            uint32_t gpadc_mic_pga2_gain            :  2; /* [22:21],        r/w,        0x0 */
            uint32_t gpadc_micboost_32db_en         :  1; /* [   23],        r/w,        0x0 */
            uint32_t reserved_24_26                 :  3; /* [26:24],       rsvd,        0x0 */
            uint32_t gpadc_chip_sen_pu              :  1; /* [   27],        r/w,        0x0 */
            uint32_t gpadc_sen_sel                  :  3; /* [30:28],        r/w,        0x0 */
            uint32_t gpadc_sen_test_en              :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_cmd;

    /* 0x910 : gpadc_reg_config1 */
    union {
        struct {
            uint32_t gpadc_cal_os_en                :  1; /* [    0],        r/w,        0x0 */
            uint32_t gpadc_cont_conv_en             :  1; /* [    1],        r/w,        0x1 */
            uint32_t gpadc_res_sel                  :  3; /* [ 4: 2],        r/w,        0x0 */
            uint32_t reserved_5_7                   :  3; /* [ 7: 5],       rsvd,        0x0 */
            uint32_t gpadc_vcm_sel_en               :  1; /* [    8],        r/w,        0x0 */
            uint32_t gpadc_vcm_hyst_sel             :  1; /* [    9],        r/w,        0x0 */
            uint32_t gpadc_lowv_det_en              :  1; /* [   10],        r/w,        0x0 */
            uint32_t gpadc_pwm_trg_en               :  1; /* [   11],        r/w,        0x0 */
            uint32_t gpadc_clk_ana_dly              :  4; /* [15:12],        r/w,        0x0 */
            uint32_t gpadc_clk_ana_dly_en           :  1; /* [   16],        r/w,        0x0 */
            uint32_t gpadc_clk_ana_inv              :  1; /* [   17],        r/w,        0x0 */
            uint32_t gpadc_clk_div_ratio            :  3; /* [20:18],        r/w,        0x3 */
            uint32_t gpadc_scan_length              :  4; /* [24:21],        r/w,        0x0 */
            uint32_t gpadc_scan_en                  :  1; /* [   25],        r/w,        0x0 */
            uint32_t gpadc_dither_en                :  1; /* [   26],        r/w,        0x0 */
            uint32_t gpadc_v11_sel                  :  2; /* [28:27],        r/w,        0x0 */
            uint32_t gpadc_v18_sel                  :  2; /* [30:29],        r/w,        0x0 */
            uint32_t reserved_31                    :  1; /* [   31],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_config1;

    /* 0x914 : gpadc_reg_config2 */
    union {
        struct {
            uint32_t reserved_0_1                   :  2; /* [ 1: 0],       rsvd,        0x0 */
            uint32_t gpadc_diff_mode                :  1; /* [    2],        r/w,        0x0 */
            uint32_t gpadc_vref_sel                 :  1; /* [    3],        r/w,        0x0 */
            uint32_t gpadc_vbat_en                  :  1; /* [    4],        r/w,        0x0 */
            uint32_t gpadc_tsext_sel                :  1; /* [    5],        r/w,        0x0 */
            uint32_t gpadc_ts_en                    :  1; /* [    6],        r/w,        0x0 */
            uint32_t gpadc_pga_vcm                  :  2; /* [ 8: 7],        r/w,        0x2 */
            uint32_t gpadc_pga_os_cal               :  4; /* [12: 9],        r/w,        0x8 */
            uint32_t gpadc_pga_en                   :  1; /* [   13],        r/w,        0x0 */
            uint32_t gpadc_pga_vcmi_en              :  1; /* [   14],        r/w,        0x0 */
            uint32_t gpadc_chop_mode                :  2; /* [16:15],        r/w,        0x3 */
            uint32_t gpadc_bias_sel                 :  1; /* [   17],        r/w,        0x0 */
            uint32_t gpadc_test_en                  :  1; /* [   18],        r/w,        0x0 */
            uint32_t gpadc_test_sel                 :  3; /* [21:19],        r/w,        0x0 */
            uint32_t gpadc_pga2_gain                :  3; /* [24:22],        r/w,        0x0 */
            uint32_t gpadc_pga1_gain                :  3; /* [27:25],        r/w,        0x0 */
            uint32_t gpadc_dly_sel                  :  3; /* [30:28],        r/w,        0x0 */
            uint32_t gpadc_tsvbe_low                :  1; /* [   31],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_config2;

    /* 0x918 : adc converation sequence 1 */
    union {
        struct {
            uint32_t gpadc_scan_pos_0               :  5; /* [ 4: 0],        r/w,        0xf */
            uint32_t gpadc_scan_pos_1               :  5; /* [ 9: 5],        r/w,        0xf */
            uint32_t gpadc_scan_pos_2               :  5; /* [14:10],        r/w,        0xf */
            uint32_t gpadc_scan_pos_3               :  5; /* [19:15],        r/w,        0xf */
            uint32_t gpadc_scan_pos_4               :  5; /* [24:20],        r/w,        0xf */
            uint32_t gpadc_scan_pos_5               :  5; /* [29:25],        r/w,        0xf */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_scn_pos1;

    /* 0x91C : adc converation sequence 2 */
    union {
        struct {
            uint32_t gpadc_scan_pos_6               :  5; /* [ 4: 0],        r/w,        0xf */
            uint32_t gpadc_scan_pos_7               :  5; /* [ 9: 5],        r/w,        0xf */
            uint32_t gpadc_scan_pos_8               :  5; /* [14:10],        r/w,        0xf */
            uint32_t gpadc_scan_pos_9               :  5; /* [19:15],        r/w,        0xf */
            uint32_t gpadc_scan_pos_10              :  5; /* [24:20],        r/w,        0xf */
            uint32_t gpadc_scan_pos_11              :  5; /* [29:25],        r/w,        0xf */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_scn_pos2;

    /* 0x920 : adc converation sequence 3 */
    union {
        struct {
            uint32_t gpadc_scan_neg_0               :  5; /* [ 4: 0],        r/w,        0xf */
            uint32_t gpadc_scan_neg_1               :  5; /* [ 9: 5],        r/w,        0xf */
            uint32_t gpadc_scan_neg_2               :  5; /* [14:10],        r/w,        0xf */
            uint32_t gpadc_scan_neg_3               :  5; /* [19:15],        r/w,        0xf */
            uint32_t gpadc_scan_neg_4               :  5; /* [24:20],        r/w,        0xf */
            uint32_t gpadc_scan_neg_5               :  5; /* [29:25],        r/w,        0xf */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_scn_neg1;

    /* 0x924 : adc converation sequence 4 */
    union {
        struct {
            uint32_t gpadc_scan_neg_6               :  5; /* [ 4: 0],        r/w,        0xf */
            uint32_t gpadc_scan_neg_7               :  5; /* [ 9: 5],        r/w,        0xf */
            uint32_t gpadc_scan_neg_8               :  5; /* [14:10],        r/w,        0xf */
            uint32_t gpadc_scan_neg_9               :  5; /* [19:15],        r/w,        0xf */
            uint32_t gpadc_scan_neg_10              :  5; /* [24:20],        r/w,        0xf */
            uint32_t gpadc_scan_neg_11              :  5; /* [29:25],        r/w,        0xf */
            uint32_t reserved_30_31                 :  2; /* [31:30],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_scn_neg2;

    /* 0x928 : gpadc_reg_status */
    union {
        struct {
            uint32_t gpadc_data_rdy                 :  1; /* [    0],          r,        0x0 */
            uint32_t reserved_1_15                  : 15; /* [15: 1],       rsvd,        0x0 */
            uint32_t gpadc_reserved                 : 16; /* [31:16],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_status;

    /* 0x92C : gpadc_reg_isr */
    union {
        struct {
            uint32_t gpadc_neg_satur                :  1; /* [    0],          r,        0x0 */
            uint32_t gpadc_pos_satur                :  1; /* [    1],          r,        0x0 */
            uint32_t reserved_2_3                   :  2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t gpadc_neg_satur_clr            :  1; /* [    4],        r/w,        0x0 */
            uint32_t gpadc_pos_satur_clr            :  1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7                   :  2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t gpadc_neg_satur_mask           :  1; /* [    8],        r/w,        0x0 */
            uint32_t gpadc_pos_satur_mask           :  1; /* [    9],        r/w,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_isr;

    /* 0x930 : gpadc_reg_result */
    union {
        struct {
            uint32_t gpadc_data_out                 : 26; /* [25: 0],          r,  0x1ef0000 */
            uint32_t reserved_26_31                 :  6; /* [31:26],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_result;

    /* 0x934 : gpadc_reg_raw_result */
    union {
        struct {
            uint32_t gpadc_raw_data                 : 12; /* [11: 0],          r,        0x0 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_raw_result;

    /* 0x938 : gpadc_reg_define */
    union {
        struct {
            uint32_t gpadc_os_cal_data              : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31                 : 16; /* [31:16],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } gpadc_reg_define;

    /* 0x93C : hbncore_resv0 */
    union {
        struct {
            uint32_t hbncore_resv0_data             : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } hbncore_resv0;

    /* 0x940 : hbncore_resv1 */
    union {
        struct {
            uint32_t hbncore_resv1_data             : 32; /* [31: 0],        r/w, 0xffffffff */
        }BF;
        uint32_t WORD;
    } hbncore_resv1;

};

typedef volatile struct aon_reg aon_reg_t;


#endif  /* __AON_REG_H__ */
