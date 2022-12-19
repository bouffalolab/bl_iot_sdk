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
#ifndef  __DVP_TSRC_AXI_REG_H__
#define  __DVP_TSRC_AXI_REG_H__

/* 0x0 : config */
#define DVP_TSRC_AXI_CONFIG_OFFSET                              (0x0)
#define DVP_TSRC_AXI_CR_ENABLE_POS                              (0U)
#define DVP_TSRC_AXI_CR_ENABLE_LEN                              (1U)
#define DVP_TSRC_AXI_CR_ENABLE_MSK                              (((1U<<DVP_TSRC_AXI_CR_ENABLE_LEN)-1)<<DVP_TSRC_AXI_CR_ENABLE_POS)
#define DVP_TSRC_AXI_CR_ENABLE_UMSK                             (~(((1U<<DVP_TSRC_AXI_CR_ENABLE_LEN)-1)<<DVP_TSRC_AXI_CR_ENABLE_POS))
#define DVP_TSRC_AXI_CR_ENABLE_SET                              (1U<<DVP_TSRC_AXI_CR_ENABLE_POS)
#define DVP_TSRC_AXI_CR_ENABLE_CLEAR                            (~(((1U<<DVP_TSRC_AXI_CR_ENABLE_LEN)-1)<<DVP_TSRC_AXI_CR_ENABLE_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_POS                          (1U)
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_LEN                          (1U)
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_MSK                          (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_EN_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_EN_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_UMSK                         (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_EN_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_EN_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_SET                          (1U<<DVP_TSRC_AXI_CR_AXI2DVP_EN_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_EN_CLEAR                        (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_EN_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_EN_POS))
#define DVP_TSRC_AXI_CR_MODE_CEA_861_POS                        (2U)
#define DVP_TSRC_AXI_CR_MODE_CEA_861_LEN                        (1U)
#define DVP_TSRC_AXI_CR_MODE_CEA_861_MSK                        (((1U<<DVP_TSRC_AXI_CR_MODE_CEA_861_LEN)-1)<<DVP_TSRC_AXI_CR_MODE_CEA_861_POS)
#define DVP_TSRC_AXI_CR_MODE_CEA_861_UMSK                       (~(((1U<<DVP_TSRC_AXI_CR_MODE_CEA_861_LEN)-1)<<DVP_TSRC_AXI_CR_MODE_CEA_861_POS))
#define DVP_TSRC_AXI_CR_MODE_CEA_861_SET                        (1U<<DVP_TSRC_AXI_CR_MODE_CEA_861_POS)
#define DVP_TSRC_AXI_CR_MODE_CEA_861_CLEAR                      (~(((1U<<DVP_TSRC_AXI_CR_MODE_CEA_861_LEN)-1)<<DVP_TSRC_AXI_CR_MODE_CEA_861_POS))
#define DVP_TSRC_AXI_CR_SNSR_EN_POS                             (3U)
#define DVP_TSRC_AXI_CR_SNSR_EN_LEN                             (1U)
#define DVP_TSRC_AXI_CR_SNSR_EN_MSK                             (((1U<<DVP_TSRC_AXI_CR_SNSR_EN_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_EN_POS)
#define DVP_TSRC_AXI_CR_SNSR_EN_UMSK                            (~(((1U<<DVP_TSRC_AXI_CR_SNSR_EN_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_EN_POS))
#define DVP_TSRC_AXI_CR_SNSR_EN_SET                             (1U<<DVP_TSRC_AXI_CR_SNSR_EN_POS)
#define DVP_TSRC_AXI_CR_SNSR_EN_CLEAR                           (~(((1U<<DVP_TSRC_AXI_CR_SNSR_EN_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_EN_POS))
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_POS                      (4U)
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_LEN                      (1U)
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_MSK                      (((1U<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_POS)
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_UMSK                     (~(((1U<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_POS))
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_SET                      (1U<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_POS)
#define DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_CLEAR                    (~(((1U<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_HSYNC_INV_POS))
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_POS                      (5U)
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_LEN                      (1U)
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_MSK                      (((1U<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_POS)
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_UMSK                     (~(((1U<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_POS))
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_SET                      (1U<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_POS)
#define DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_CLEAR                    (~(((1U<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_VSYNC_INV_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_POS                   (6U)
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_LEN                   (1U)
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_MSK                   (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_UMSK                  (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_SET                   (1U<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_CLEAR                 (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_8BIT_MODE_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_POS                   (7U)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_LEN                   (1U)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_MSK                   (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_UMSK                  (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_SET                   (1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_CLEAR                 (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_MODE_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_POS                (8U)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_LEN                (2U)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_MSK                (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_UMSK               (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_SWAP_IDX_SEL_POS))

/* 0x4 : frame_size_h */
#define DVP_TSRC_AXI_FRAME_SIZE_H_OFFSET                        (0x4)
#define DVP_TSRC_AXI_CR_TOTAL_H_POS                             (0U)
#define DVP_TSRC_AXI_CR_TOTAL_H_LEN                             (12U)
#define DVP_TSRC_AXI_CR_TOTAL_H_MSK                             (((1U<<DVP_TSRC_AXI_CR_TOTAL_H_LEN)-1)<<DVP_TSRC_AXI_CR_TOTAL_H_POS)
#define DVP_TSRC_AXI_CR_TOTAL_H_UMSK                            (~(((1U<<DVP_TSRC_AXI_CR_TOTAL_H_LEN)-1)<<DVP_TSRC_AXI_CR_TOTAL_H_POS))
#define DVP_TSRC_AXI_CR_BLANK_H_POS                             (16U)
#define DVP_TSRC_AXI_CR_BLANK_H_LEN                             (12U)
#define DVP_TSRC_AXI_CR_BLANK_H_MSK                             (((1U<<DVP_TSRC_AXI_CR_BLANK_H_LEN)-1)<<DVP_TSRC_AXI_CR_BLANK_H_POS)
#define DVP_TSRC_AXI_CR_BLANK_H_UMSK                            (~(((1U<<DVP_TSRC_AXI_CR_BLANK_H_LEN)-1)<<DVP_TSRC_AXI_CR_BLANK_H_POS))

/* 0x8 : frame_size_v */
#define DVP_TSRC_AXI_FRAME_SIZE_V_OFFSET                        (0x8)
#define DVP_TSRC_AXI_CR_TOTAL_V_POS                             (0U)
#define DVP_TSRC_AXI_CR_TOTAL_V_LEN                             (12U)
#define DVP_TSRC_AXI_CR_TOTAL_V_MSK                             (((1U<<DVP_TSRC_AXI_CR_TOTAL_V_LEN)-1)<<DVP_TSRC_AXI_CR_TOTAL_V_POS)
#define DVP_TSRC_AXI_CR_TOTAL_V_UMSK                            (~(((1U<<DVP_TSRC_AXI_CR_TOTAL_V_LEN)-1)<<DVP_TSRC_AXI_CR_TOTAL_V_POS))
#define DVP_TSRC_AXI_CR_BLANK_V_POS                             (16U)
#define DVP_TSRC_AXI_CR_BLANK_V_LEN                             (12U)
#define DVP_TSRC_AXI_CR_BLANK_V_MSK                             (((1U<<DVP_TSRC_AXI_CR_BLANK_V_LEN)-1)<<DVP_TSRC_AXI_CR_BLANK_V_POS)
#define DVP_TSRC_AXI_CR_BLANK_V_UMSK                            (~(((1U<<DVP_TSRC_AXI_CR_BLANK_V_LEN)-1)<<DVP_TSRC_AXI_CR_BLANK_V_POS))

/* 0xC : frame_size_cea_861 */
#define DVP_TSRC_AXI_FRAME_SIZE_CEA_861_OFFSET                  (0xC)
#define DVP_TSRC_AXI_CR_H_DURATION_POS                          (0U)
#define DVP_TSRC_AXI_CR_H_DURATION_LEN                          (8U)
#define DVP_TSRC_AXI_CR_H_DURATION_MSK                          (((1U<<DVP_TSRC_AXI_CR_H_DURATION_LEN)-1)<<DVP_TSRC_AXI_CR_H_DURATION_POS)
#define DVP_TSRC_AXI_CR_H_DURATION_UMSK                         (~(((1U<<DVP_TSRC_AXI_CR_H_DURATION_LEN)-1)<<DVP_TSRC_AXI_CR_H_DURATION_POS))
#define DVP_TSRC_AXI_CR_H_PLACEMENT_POS                         (8U)
#define DVP_TSRC_AXI_CR_H_PLACEMENT_LEN                         (8U)
#define DVP_TSRC_AXI_CR_H_PLACEMENT_MSK                         (((1U<<DVP_TSRC_AXI_CR_H_PLACEMENT_LEN)-1)<<DVP_TSRC_AXI_CR_H_PLACEMENT_POS)
#define DVP_TSRC_AXI_CR_H_PLACEMENT_UMSK                        (~(((1U<<DVP_TSRC_AXI_CR_H_PLACEMENT_LEN)-1)<<DVP_TSRC_AXI_CR_H_PLACEMENT_POS))
#define DVP_TSRC_AXI_CR_V_DURATION_POS                          (16U)
#define DVP_TSRC_AXI_CR_V_DURATION_LEN                          (8U)
#define DVP_TSRC_AXI_CR_V_DURATION_MSK                          (((1U<<DVP_TSRC_AXI_CR_V_DURATION_LEN)-1)<<DVP_TSRC_AXI_CR_V_DURATION_POS)
#define DVP_TSRC_AXI_CR_V_DURATION_UMSK                         (~(((1U<<DVP_TSRC_AXI_CR_V_DURATION_LEN)-1)<<DVP_TSRC_AXI_CR_V_DURATION_POS))
#define DVP_TSRC_AXI_CR_V_PLACEMENT_POS                         (24U)
#define DVP_TSRC_AXI_CR_V_PLACEMENT_LEN                         (8U)
#define DVP_TSRC_AXI_CR_V_PLACEMENT_MSK                         (((1U<<DVP_TSRC_AXI_CR_V_PLACEMENT_LEN)-1)<<DVP_TSRC_AXI_CR_V_PLACEMENT_POS)
#define DVP_TSRC_AXI_CR_V_PLACEMENT_UMSK                        (~(((1U<<DVP_TSRC_AXI_CR_V_PLACEMENT_LEN)-1)<<DVP_TSRC_AXI_CR_V_PLACEMENT_POS))

/* 0x10 : pix_data_range */
#define DVP_TSRC_AXI_PIX_DATA_RANGE_OFFSET                      (0x10)
#define DVP_TSRC_AXI_CR_DATA_MIN_POS                            (0U)
#define DVP_TSRC_AXI_CR_DATA_MIN_LEN                            (16U)
#define DVP_TSRC_AXI_CR_DATA_MIN_MSK                            (((1U<<DVP_TSRC_AXI_CR_DATA_MIN_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_MIN_POS)
#define DVP_TSRC_AXI_CR_DATA_MIN_UMSK                           (~(((1U<<DVP_TSRC_AXI_CR_DATA_MIN_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_MIN_POS))
#define DVP_TSRC_AXI_CR_DATA_MAX_POS                            (16U)
#define DVP_TSRC_AXI_CR_DATA_MAX_LEN                            (16U)
#define DVP_TSRC_AXI_CR_DATA_MAX_MSK                            (((1U<<DVP_TSRC_AXI_CR_DATA_MAX_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_MAX_POS)
#define DVP_TSRC_AXI_CR_DATA_MAX_UMSK                           (~(((1U<<DVP_TSRC_AXI_CR_DATA_MAX_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_MAX_POS))

/* 0x14 : pix_data_step */
#define DVP_TSRC_AXI_PIX_DATA_STEP_OFFSET                       (0x14)
#define DVP_TSRC_AXI_CR_DATA_STEP_POS                           (0U)
#define DVP_TSRC_AXI_CR_DATA_STEP_LEN                           (8U)
#define DVP_TSRC_AXI_CR_DATA_STEP_MSK                           (((1U<<DVP_TSRC_AXI_CR_DATA_STEP_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_STEP_POS)
#define DVP_TSRC_AXI_CR_DATA_STEP_UMSK                          (~(((1U<<DVP_TSRC_AXI_CR_DATA_STEP_LEN)-1)<<DVP_TSRC_AXI_CR_DATA_STEP_POS))

/* 0x20 : axi2dvp_setting */
#define DVP_TSRC_AXI_AXI2DVP_SETTING_OFFSET                     (0x20)
#define DVP_TSRC_AXI_CR_AXI2DVP_XLEN_POS                        (0U)
#define DVP_TSRC_AXI_CR_AXI2DVP_XLEN_LEN                        (3U)
#define DVP_TSRC_AXI_CR_AXI2DVP_XLEN_MSK                        (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_XLEN_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_XLEN_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_XLEN_UMSK                       (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_XLEN_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_XLEN_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_POS               (4U)
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_LEN               (1U)
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_MSK               (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_UMSK              (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_POS))
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_SET               (1U<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_CLEAR             (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_DRAIN_ERR_CLR_POS))

/* 0x24 : axi2dvp_start_addr */
#define DVP_TSRC_AXI_AXI2DVP_START_ADDR_OFFSET                  (0x24)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_POS                  (0U)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_LEN                  (32U)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_MSK                  (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_UMSK                 (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_START_POS))

/* 0x28 : axi2dvp_burst_cnt */
#define DVP_TSRC_AXI_AXI2DVP_BURST_CNT_OFFSET                   (0x28)
#define DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_POS             (0U)
#define DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_LEN             (32U)
#define DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_MSK             (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_UMSK            (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_FRAME_BURST_CNT_POS))

/* 0x2C : axi2dvp_status */
#define DVP_TSRC_AXI_AXI2DVP_STATUS_OFFSET                      (0x2C)
#define DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_POS                    (0U)
#define DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_LEN                    (7U)
#define DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_MSK                    (((1U<<DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_UMSK                   (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_FIFO_CNT_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_POS                 (7U)
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_LEN                 (1U)
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_MSK                 (((1U<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_UMSK                (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_SET                 (1U<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_CLEAR               (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_DRAIN_ERROR_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_POS                  (8U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_LEN                  (1U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_MSK                  (((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_UMSK                 (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_SET                  (1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_CLEAR                (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_IDLE_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_POS                  (9U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_LEN                  (1U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_MSK                  (((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_UMSK                 (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_SET                  (1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_CLEAR                (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FUNC_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_POS                  (10U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_LEN                  (1U)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_MSK                  (((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_UMSK                 (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_POS))
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_SET                  (1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_POS)
#define DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_CLEAR                (~(((1U<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_LEN)-1)<<DVP_TSRC_AXI_ST_AXI2DVP_STATE_FLSH_POS))

/* 0x30 : axi2dvp_swap_addr */
#define DVP_TSRC_AXI_AXI2DVP_SWAP_ADDR_OFFSET                   (0x30)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_POS                   (0U)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_LEN                   (32U)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_MSK                   (((1U<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_POS)
#define DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_UMSK                  (~(((1U<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_LEN)-1)<<DVP_TSRC_AXI_CR_AXI2DVP_ADDR_SWAP_POS))

/* 0x34 : axi2dvp_prefetch */
#define DVP_TSRC_AXI_AXI2DVP_PREFETCH_OFFSET                    (0x34)
#define DVP_TSRC_AXI_CR_PREFETCH_V_POS                          (0U)
#define DVP_TSRC_AXI_CR_PREFETCH_V_LEN                          (12U)
#define DVP_TSRC_AXI_CR_PREFETCH_V_MSK                          (((1U<<DVP_TSRC_AXI_CR_PREFETCH_V_LEN)-1)<<DVP_TSRC_AXI_CR_PREFETCH_V_POS)
#define DVP_TSRC_AXI_CR_PREFETCH_V_UMSK                         (~(((1U<<DVP_TSRC_AXI_CR_PREFETCH_V_LEN)-1)<<DVP_TSRC_AXI_CR_PREFETCH_V_POS))

/* 0x38 : snsr2dvp_wait_pos */
#define DVP_TSRC_AXI_SNSR2DVP_WAIT_POS_OFFSET                   (0x38)
#define DVP_TSRC_AXI_CR_SNSR_FIFO_TH_POS                        (0U)
#define DVP_TSRC_AXI_CR_SNSR_FIFO_TH_LEN                        (12U)
#define DVP_TSRC_AXI_CR_SNSR_FIFO_TH_MSK                        (((1U<<DVP_TSRC_AXI_CR_SNSR_FIFO_TH_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_FIFO_TH_POS)
#define DVP_TSRC_AXI_CR_SNSR_FIFO_TH_UMSK                       (~(((1U<<DVP_TSRC_AXI_CR_SNSR_FIFO_TH_LEN)-1)<<DVP_TSRC_AXI_CR_SNSR_FIFO_TH_POS))


struct  dvp_tsrc_axi_reg {
    /* 0x0 : config */
    union {
        struct {
            uint32_t cr_enable                      :  1; /* [    0],        r/w,        0x0 */
            uint32_t cr_axi2dvp_en                  :  1; /* [    1],        r/w,        0x0 */
            uint32_t cr_mode_cea_861                :  1; /* [    2],        r/w,        0x0 */
            uint32_t cr_snsr_en                     :  1; /* [    3],        r/w,        0x0 */
            uint32_t cr_snsr_hsync_inv              :  1; /* [    4],        r/w,        0x0 */
            uint32_t cr_snsr_vsync_inv              :  1; /* [    5],        r/w,        0x0 */
            uint32_t cr_axi2dvp_8bit_mode           :  1; /* [    6],        r/w,        0x0 */
            uint32_t cr_axi2dvp_swap_mode           :  1; /* [    7],        r/w,        0x0 */
            uint32_t cr_axi2dvp_swap_idx_sel        :  2; /* [ 9: 8],        r/w,        0x0 */
            uint32_t reserved_10_31                 : 22; /* [31:10],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } config;

    /* 0x4 : frame_size_h */
    union {
        struct {
            uint32_t cr_total_h                     : 12; /* [11: 0],        r/w,      0x897 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cr_blank_h                     : 12; /* [27:16],        r/w,      0x117 */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_size_h;

    /* 0x8 : frame_size_v */
    union {
        struct {
            uint32_t cr_total_v                     : 12; /* [11: 0],        r/w,      0x464 */
            uint32_t reserved_12_15                 :  4; /* [15:12],       rsvd,        0x0 */
            uint32_t cr_blank_v                     : 12; /* [27:16],        r/w,       0x2c */
            uint32_t reserved_28_31                 :  4; /* [31:28],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } frame_size_v;

    /* 0xC : frame_size_cea_861 */
    union {
        struct {
            uint32_t cr_h_duration                  :  8; /* [ 7: 0],        r/w,       0x83 */
            uint32_t cr_h_placement                 :  8; /* [15: 8],        r/w,       0x57 */
            uint32_t cr_v_duration                  :  8; /* [23:16],        r/w,        0x8 */
            uint32_t cr_v_placement                 :  8; /* [31:24],        r/w,        0x3 */
        }BF;
        uint32_t WORD;
    } frame_size_cea_861;

    /* 0x10 : pix_data_range */
    union {
        struct {
            uint32_t cr_data_min                    : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t cr_data_max                    : 16; /* [31:16],        r/w,     0xffff */
        }BF;
        uint32_t WORD;
    } pix_data_range;

    /* 0x14 : pix_data_step */
    union {
        struct {
            uint32_t cr_data_step                   :  8; /* [ 7: 0],        r/w,        0x1 */
            uint32_t reserved_8_31                  : 24; /* [31: 8],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } pix_data_step;

    /* 0x18  reserved */
    uint8_t RESERVED0x18[8];

    /* 0x20 : axi2dvp_setting */
    union {
        struct {
            uint32_t cr_axi2dvp_xlen                :  3; /* [ 2: 0],        r/w,        0x3 */
            uint32_t reserved_3                     :  1; /* [    3],       rsvd,        0x0 */
            uint32_t cr_axi2dvp_drain_err_clr       :  1; /* [    4],        w1p,        0x0 */
            uint32_t reserved_5_31                  : 27; /* [31: 5],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_setting;

    /* 0x24 : axi2dvp_start_addr */
    union {
        struct {
            uint32_t cr_axi2dvp_addr_start          : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_start_addr;

    /* 0x28 : axi2dvp_burst_cnt */
    union {
        struct {
            uint32_t cr_axi2dvp_frame_burst_cnt     : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_burst_cnt;

    /* 0x2C : axi2dvp_status */
    union {
        struct {
            uint32_t st_axi2dvp_fifo_cnt            :  7; /* [ 6: 0],          r,        0x0 */
            uint32_t st_axi2dvp_drain_error         :  1; /* [    7],          r,        0x0 */
            uint32_t st_axi2dvp_state_idle          :  1; /* [    8],          r,        0x0 */
            uint32_t st_axi2dvp_state_func          :  1; /* [    9],          r,        0x0 */
            uint32_t st_axi2dvp_state_flsh          :  1; /* [   10],          r,        0x0 */
            uint32_t reserved_11_31                 : 21; /* [31:11],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_status;

    /* 0x30 : axi2dvp_swap_addr */
    union {
        struct {
            uint32_t cr_axi2dvp_addr_swap           : 32; /* [31: 0],        r/w,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_swap_addr;

    /* 0x34 : axi2dvp_prefetch */
    union {
        struct {
            uint32_t cr_prefetch_v                  : 12; /* [11: 0],        r/w,       0x28 */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } axi2dvp_prefetch;

    /* 0x38 : snsr2dvp_wait_pos */
    union {
        struct {
            uint32_t cr_snsr_fifo_th                : 12; /* [11: 0],        r/w,       0x8b */
            uint32_t reserved_12_31                 : 20; /* [31:12],       rsvd,        0x0 */
        }BF;
        uint32_t WORD;
    } snsr2dvp_wait_pos;

};

typedef volatile struct dvp_tsrc_axi_reg dvp_tsrc_axi_reg_t;


#endif  /* __DVP_TSRC_AXI_REG_H__ */
