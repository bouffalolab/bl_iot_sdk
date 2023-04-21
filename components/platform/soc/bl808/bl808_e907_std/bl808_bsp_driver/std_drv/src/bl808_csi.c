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

#include "bl808_csi.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CSI
 *  @{
 */

/** @defgroup  CSI_Private_Macros
 *  @{
 */

/*@} end of group CSI_Private_Macros */

/** @defgroup  CSI_Private_Types
 *  @{
 */

/*@} end of group CSI_Private_Types */

/** @defgroup  CSI_Private_Variables
 *  @{
 */

static const uint32_t csiAddr[CSI_ID_MAX] = { CSI_BASE };

/**
 *  @brief CSI interrupt callback function address array
*/
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *csiIntCbfArra[CSI_ID_MAX][CSI_INT_COUNT] = {
    { NULL, NULL, NULL, NULL, NULL, NULL }
};
#endif

/*@} end of group CSI_Private_Variables */

/** @defgroup  CSI_Global_Variables
 *  @{
 */

/*@} end of group CSI_Global_Variables */

/** @defgroup  CSI_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type CSI_IntHandler(CSI_ID_Type csiId);
#endif

/*@} end of group CSI_Private_Fun_Declaration */

/** @defgroup  CSI_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  CSI interrupt handle
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type CSI_IntHandler(CSI_ID_Type csiId)
{
    uint32_t maskVal;
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));

    maskVal = BL_RD_REG(CSIx, CSI_INT_MASK);
    tmpVal = BL_RD_REG(CSIx, CSI_INT_STATUS);

    if (tmpVal & CSI_INT_GENERIC_PACKET && !(maskVal & CSI_INT_GENERIC_PACKET)) {
        CSI_IntClear(csiId, CSI_INT_GENERIC_PACKET);

        if (csiIntCbfArra[csiId][0] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][0]();
        }
    }

    if (tmpVal & CSI_INT_LANE_MERGE_ERR && !(maskVal & CSI_INT_LANE_MERGE_ERR)) {
        CSI_IntClear(csiId, CSI_INT_LANE_MERGE_ERR);

        if (csiIntCbfArra[csiId][1] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][1]();
        }
    }

    if (tmpVal & CSI_INT_ECC_ERR && !(maskVal & CSI_INT_ECC_ERR)) {
        CSI_IntClear(csiId, CSI_INT_ECC_ERR);

        if (csiIntCbfArra[csiId][2] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][2]();
        }
    }

    if (tmpVal & CSI_INT_CRC_ERR && !(maskVal & CSI_INT_CRC_ERR)) {
        CSI_IntClear(csiId, CSI_INT_CRC_ERR);

        if (csiIntCbfArra[csiId][3] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][3]();
        }
    }

    if (tmpVal & CSI_INT_PHY_HS_SOT_ERR && !(maskVal & CSI_INT_PHY_HS_SOT_ERR)) {
        CSI_IntClear(csiId, CSI_INT_PHY_HS_SOT_ERR);

        if (csiIntCbfArra[csiId][4] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][4]();
        }
    }

    if (tmpVal & CSI_INT_PHY_HS_SOT_SYNC_ERR && !(maskVal & CSI_INT_PHY_HS_SOT_SYNC_ERR)) {
        CSI_IntClear(csiId, CSI_INT_PHY_HS_SOT_SYNC_ERR);

        if (csiIntCbfArra[csiId][5] != NULL) {
            /* call the callback function */
            csiIntCbfArra[csiId][5]();
        }
    }

    return SUCCESS;
}
#endif

/*@} end of group CSI_Private_Functions */

/** @defgroup  CSI_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  CSI module init
 *
 * @param  csiId: CSI ID type
 * @param  cfg: CSI configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void CSI_Init(CSI_ID_Type csiId, CSI_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    CHECK_PARAM(IS_CSI_LANE_NUMBER_TYPE(cfg->laneNum));
    
    tmpVal = BL_RD_REG(CSIx, CSI_MIPI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_VC_DVP0, cfg->dvp0VirtualChan);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_UNPACK_EN, cfg->dataUnpackEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_SYNC_SP_EN, cfg->syncShortPacketEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_DATA_BIT_INV, cfg->dataBitInverseEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_LANE_INV, cfg->laneInverseEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CSI_CR_LANE_NUM, cfg->laneNum);
    BL_WR_REG(CSIx, CSI_MIPI_CONFIG, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MIPI_CSI_IRQn, CSI_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Deinit CSI module
 *
 * @param  csiId: CSI ID type
 *
 * @return None
 *
*******************************************************************************/
void CSI_Deinit(CSI_ID_Type csiId)
{
}

/****************************************************************************/ /**
 * @brief  Enable CSI function
 *
 * @param  csiId: CSI ID type
 *
 * @return None
 *
*******************************************************************************/
void CSI_Enable(CSI_ID_Type csiId)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));

    tmpVal = BL_RD_REG(CSIx, CSI_MIPI_CONFIG);

    BL_WR_REG(CSIx, CSI_MIPI_CONFIG, BL_SET_REG_BIT(tmpVal, CSI_CR_CSI_EN));
}

/****************************************************************************/ /**
 * @brief  Disable CSI function
 *
 * @param  csiId: CSI ID type
 *
 * @return None
 *
*******************************************************************************/
void CSI_Disable(CSI_ID_Type csiId)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));

    tmpVal = BL_RD_REG(CSIx, CSI_MIPI_CONFIG);

    BL_WR_REG(CSIx, CSI_MIPI_CONFIG, BL_CLR_REG_BIT(tmpVal, CSI_CR_CSI_EN));
}

/****************************************************************************/ /**
 * @brief  CSI mask or unmask Interrupt
 *
 * @param  csiId: CSI ID type
 * @param  intType: CSI Interrupt Type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void CSI_IntMask(CSI_ID_Type csiId, CSI_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    CHECK_PARAM(IS_CSI_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(CSIx, CSI_INT_MASK);

    if (intMask == UNMASK) {
        /* Unmask this interrupt */
        tmpVal &= (~intType);

    } else {
        /* Mask this interrupt */
        tmpVal |= intType;
    }

    BL_WR_REG(CSIx, CSI_INT_MASK, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CSI Clear Interrupt
 *
 * @param  csiId: CSI ID type
 * @param  intType: CSI Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void CSI_IntClear(CSI_ID_Type csiId, CSI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    CHECK_PARAM(IS_CSI_INT_TYPE(intType));

    tmpVal = BL_RD_REG(CSIx, CSI_INT_CLEAR);

    /* Clear this interrupt */
    tmpVal |= intType;

    BL_WR_REG(CSIx, CSI_INT_CLEAR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Install CSI interrupt callback function
 *
 * @param  csiId: CSI ID type
 * @param  intType: CSI interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CSI_Int_Callback_Install(CSI_ID_Type csiId, CSI_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    CHECK_PARAM(IS_CSI_INT_TYPE(intType));

    csiIntCbfArra[csiId][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  CSI Reset D-PHY
 *
 * @param  csiId: CSI ID type
 *
 * @return None
 *
*******************************************************************************/
void CSI_PHY_Reset(CSI_ID_Type csiId)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];

    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));

    tmpVal = BL_RD_REG(CSIx, CSI_DPHY_CONFIG_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_RESET_N);
    BL_WR_REG(CSIx, CSI_DPHY_CONFIG_0, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, CSI_RESET_N);
    BL_WR_REG(CSIx, CSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CSI D-PHY configure
 *
 * @param  csiId: CSI ID type
 *
 * @param  txClkEsc: tx clock escape
 *
 * @param  dataRate: data rate
 *
 * @return None
 *
*******************************************************************************/
void CSI_PHY_Config(CSI_ID_Type csiId, uint32_t txClkEsc, uint32_t dataRate)
{
    uint32_t tmpVal = 0;
    uint32_t CSIx = csiAddr[csiId];
    
    /* Unit: ns */
    float TD_TERM_EN_MAX = 35 + 4 * (1e3) / dataRate; 
    uint32_t TD_TERM_EN = (TD_TERM_EN_MAX * dataRate / 2 / (1e3)) - 1;
    float THS_SETTLE_MAX = 145 + 10 * (1e3) / dataRate;
    /* THS_SETTLE = reg_time_hs_settle + reg_time_hs_term_en */
    uint32_t THS_SETTLE = ((THS_SETTLE_MAX - TD_TERM_EN * 2 * (1e3) / dataRate) * dataRate / 2 / (1e3)) - 1;
    uint32_t TCLK_TERM_EN_MAX = 38;
    uint32_t TCLK_TERM_EN = (txClkEsc * TCLK_TERM_EN_MAX) / (1e3);
    uint32_t TCLK_SETTLE_MAX = 300;
    /* TCLK_SETTLE = reg_time_ck_settle + reg_time_ck_term_en */
    uint32_t TCLK_SETTLE = ((TCLK_SETTLE_MAX - TCLK_TERM_EN * (1e3) / txClkEsc) * txClkEsc / (1e3)) - 1;

    uint32_t ANA_TERM_EN = 0x8;
    
    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    
    tmpVal = BL_RD_REG(CSIx,CSI_DPHY_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,CSI_REG_TIME_HS_TERM_EN,TD_TERM_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,CSI_REG_TIME_HS_SETTLE,THS_SETTLE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,CSI_REG_TIME_CK_TERM_EN,TCLK_TERM_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,CSI_REG_TIME_CK_SETTLE,TCLK_SETTLE);
    BL_WR_REG(CSIx,CSI_DPHY_CONFIG_1,tmpVal);

    tmpVal = BL_RD_REG(CSIx,CSI_DPHY_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,CSI_REG_ANA_TERM_EN,ANA_TERM_EN);
    BL_WR_REG(CSIx,CSI_DPHY_CONFIG_2,tmpVal);
}

/****************************************************************************/ /**
 * @brief  CSI enable lanes
 *
 * @param  csiId: CSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void CSI_PHY_Enable_Lanes(CSI_ID_Type csiId, CSI_Lane_Number_Type lanes)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    CHECK_PARAM(IS_CSI_LANE_NUMBER_TYPE(lanes));
    
    tmpVal = BL_RD_REG(CSIx, CSI_DPHY_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, CSI_DL0_FORCERXMODE);
    tmpVal = BL_SET_REG_BIT(tmpVal, CSI_CL_ENABLE);
    tmpVal = BL_SET_REG_BIT(tmpVal, CSI_DL0_ENABLE);
    if(lanes == CSI_LANE_NUMBER_2){
        tmpVal = BL_SET_REG_BIT(tmpVal, CSI_DL1_FORCERXMODE);
        tmpVal = BL_SET_REG_BIT(tmpVal, CSI_DL1_ENABLE);
    }
    BL_WR_REG(CSIx, CSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CSI disable lanes
 *
 * @param  csiId: CSI ID type
 *
 * @return None
 *
*******************************************************************************/
void CSI_PHY_Disable_Lanes(CSI_ID_Type csiId)
{
    uint32_t tmpVal;
    uint32_t CSIx = csiAddr[csiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_CSI_ID_TYPE(csiId));
    
    tmpVal = BL_RD_REG(CSIx, CSI_DPHY_CONFIG_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_DL1_FORCERXMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_DL0_FORCERXMODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_CL_ENABLE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_DL1_ENABLE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CSI_DL0_ENABLE);
    BL_WR_REG(CSIx, CSI_DPHY_CONFIG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  CSI interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void CSI_IRQHandler(void)
{
    CSI_IntHandler(CSI0_ID);
}
#endif

/*@} end of group CSI_Public_Functions */

/*@} end of group CSI */

/*@} end of group BL808_Peripheral_Driver */
