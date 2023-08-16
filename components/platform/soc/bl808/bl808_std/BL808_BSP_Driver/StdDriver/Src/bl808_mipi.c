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
#include <bl808_mipi.h>

static MIPI_RX_LANE_NUM_E mipi_rx_lane_num_s = MIPI_RX_1_LANE;

void MIPI_IRQHandler();

void MIPI_IRQHandler()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_INT_STATUS);

    if (tmpVal & MIPI_GENERIC_ERR) {
        BL_LOGE("MIPI_IRQHandler: generic error\r\n");
    }

    if (tmpVal & MIPI_LANE_MERGE_ERR) {
        BL_LOGE("MIPI_IRQHandler: merge error\r\n");
    }

    if (tmpVal & MIPI_ECC_ERR) {
        BL_LOGE("MIPI_IRQHandler: ecc error\r\n");
    }

    if (tmpVal & MIPI_CRC_ERR) {
        BL_LOGE("MIPI_IRQHandler: crc error\r\n");
    }

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_INT_CLEAR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_INT_CLEAR, 0xF);
    BL_WR_REG(MIPI_BASE, MIPI_INT_CLEAR, tmpVal);
}

static void MIPI_Ctrl_Intr_Init()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_INT_MASK);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_INT_MASK, 0);
    BL_WR_REG(MIPI_BASE, MIPI_INT_MASK, tmpVal);

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_INT_CLEAR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_INT_CLEAR, 0xF);
    BL_WR_REG(MIPI_BASE, MIPI_INT_CLEAR, tmpVal);
}

static void MIPI_DPHY_Reset()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_CSI_RESET_N);
    BL_WR_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0, tmpVal);

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_CSI_RESET_N);
    BL_WR_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0, tmpVal);
}

static void MIPI_DPHY_Set_State(BL_Fun_Type state)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0);

    if (state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_DL0_FORCERXMODE);
        tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_CL_ENABLE);
        tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_DL0_ENABLE);

        if (MIPI_RX_2_LANE == mipi_rx_lane_num_s) {
            tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_DL1_FORCERXMODE);
            tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_DL1_ENABLE);
        }
    }
    else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_DL0_FORCERXMODE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_CL_ENABLE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_DL0_ENABLE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_DL1_FORCERXMODE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_DL1_ENABLE);
    }

    BL_WR_REG(MIPI_BASE, MIPI_DPHY_CONFIG_0, tmpVal);
}

static void MIPI_DPHY_Init()
{
    MIPI_DPHY_Set_State(DISABLE);

    MIPI_DPHY_Reset();
}

static void MIPI_Ctrl_Set_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_CONFIG);
    if (state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MIPI_CR_MIPI_EN);
    }
    else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MIPI_CR_MIPI_EN);
    }
    BL_WR_REG(MIPI_BASE, MIPI_CONFIG, tmpVal);
}

void MIPI_Init()
{
    MIPI_Ctrl_Set_State(DISABLE);
    MIPI_Ctrl_Intr_Init();
    MIPI_DPHY_Init();
}

void MIPI_Config(MIPI_CFG_S* Cfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(MIPI_BASE, MIPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_VC_DVP0, Cfg->dvp_vc_num);
    // dvp port1 not open to user now
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_VC_DVP1, 1);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_UNPACK_EN, Cfg->unpack_en);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_SYNC_SP_EN, Cfg->sync_sp_en);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_DATA_BIT_INV, Cfg->data_bit_inv_en);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MIPI_CR_LANE_NUM, Cfg->lane_num);
    BL_WR_REG(MIPI_BASE, MIPI_CONFIG, tmpVal);

    mipi_rx_lane_num_s = Cfg->lane_num;
}

void MIPI_Set_State(BL_Fun_Type state)
{
    if (state) {
        *(uint32_t *)0x3001a084 =  0x01020006;
        MIPI_Ctrl_Set_State(state);
        vTaskDelay(1000);
        MIPI_DPHY_Set_State(state);
    }
    else {
        MIPI_DPHY_Set_State(state);
        vTaskDelay(1000);
        MIPI_Ctrl_Set_State(state);
    }
}