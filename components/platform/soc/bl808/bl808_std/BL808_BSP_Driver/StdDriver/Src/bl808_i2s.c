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

#include "bl808_i2s.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  I2S
 *  @{
 */

/** @defgroup  I2S_Private_Macros
 *  @{
 */

/*@} end of group I2S_Private_Macros */

/** @defgroup  I2S_Private_Types
 *  @{
 */

/*@} end of group I2S_Private_Types */

/** @defgroup  I2S_Private_Variables
 *  @{
 */

/*@} end of group I2S_Private_Variables */

/** @defgroup  I2S_Global_Variables
 *  @{
 */

/*@} end of group I2S_Global_Variables */

/** @defgroup  I2S_Private_Fun_Declaration
 *  @{
 */

/*@} end of group I2S_Private_Fun_Declaration */

/** @defgroup  I2S_Private_Functions
 *  @{
 */

/*@} end of group I2S_Private_Functions */

/** @defgroup  I2S_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  I2S BCLK config
 *
 * @param  i2sNo: I2S ID type
 * @param  i2sCfg: I2S configuration pointer
 *
 * @return NONE
 *
*******************************************************************************/
void I2S_SetBclkPeriod(I2S_ID_Type i2sNo,I2S_CFG_Type *i2sCfg)
{
    uint32_t overSampleRate;
    uint32_t bclkDivCnt;
    uint32_t tmpVal;
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    CHECK_PARAM(IS_I2S_FRAME_SIZE_TYPE(i2sCfg->frameSize));

    overSampleRate = i2sCfg->audioFreqHz/i2sCfg->sampleFreqHz;
    switch(i2sCfg->frameSize)
    {
        case I2S_SIZE_FRAME_8:
            bclkDivCnt = overSampleRate/16;
            break;
        case I2S_SIZE_FRAME_16:
            bclkDivCnt = overSampleRate/32;
            break;
        case I2S_SIZE_FRAME_24:
            bclkDivCnt = overSampleRate/48;
            break;
        case I2S_SIZE_FRAME_32:
            bclkDivCnt = overSampleRate/64;
            break;
        default:
            bclkDivCnt = overSampleRate/16;
            break;
    }
    bclkDivCnt = (bclkDivCnt/2)-1;

    tmpVal = (bclkDivCnt << 16) | bclkDivCnt;
    BL_WR_REG(I2Sx,I2S_BCLK_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  I2S configuration
 *
 * @param  i2sNo: I2S ID type
 * @param  i2sCfg: I2S configuration pointer
 *
 * @return NONE
 *
*******************************************************************************/
void I2S_Init(I2S_ID_Type i2sNo,I2S_CFG_Type *i2sCfg)
{
    uint32_t tmpVal;
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));
    CHECK_PARAM(IS_I2S_ENDIAN_TYPE(i2sCfg->endianType));
    CHECK_PARAM(IS_I2S_MODE_TYPE(i2sCfg->modeType));
    CHECK_PARAM(IS_I2S_FRAME_SIZE_TYPE(i2sCfg->frameSize));
    CHECK_PARAM(IS_I2S_FS_MODE_TYPE(i2sCfg->fsMode));
    CHECK_PARAM(IS_I2S_FS_CHANNEL_TYPE(i2sCfg->fsChannel));
    CHECK_PARAM(IS_I2S_DATA_SIZE_TYPE(i2sCfg->dataSize));
    
    tmpVal=BL_RD_REG(I2Sx, I2S_CONFIG);
   
    /* Set data endian*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_ENDIAN,i2sCfg->endianType);
    
    /* Set I2S mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_I2S_MODE,i2sCfg->modeType);
    
    /* Set BCLK invert */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_I2S_BCLK_INV,i2sCfg->bclkInvert);
    
    /* Set FS size */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_FRAME_SIZE,i2sCfg->frameSize);
    
    /* Set FS invert */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_I2S_FS_INV,i2sCfg->fsInvert);
    
    /* Set FS mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_FS_1T_MODE,i2sCfg->fsMode);
    
    /* Set FS channel mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_FS_4CH_MODE,i2sCfg->fsChannel);
    
    /* Set Data size */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_DATA_SIZE,i2sCfg->dataSize);
    
    /* Set Data offset */
    if(i2sCfg->dataOffset!=0){
        tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_OFS_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_OFS_CNT,i2sCfg->dataOffset-1);
    }else{
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_OFS_EN);
    }
    
    /* Set mono mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_MONO_MODE,i2sCfg->monoMode);
    
    /* Clear mute mode */
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_MUTE_MODE);
    
    BL_WR_REG(I2Sx, I2S_CONFIG, tmpVal);
    
    I2S_SetBclkPeriod(i2sNo,i2sCfg);
}

/****************************************************************************//**
 * @brief  I2S configure FIFO function
 *
 * @param  i2sNo: I2S ID type
 * @param  fifoCfg: FIFO configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void I2S_FifoConfig(I2S_ID_Type i2sNo, I2S_FifoCfg_Type * fifoCfg)
{
    uint32_t tmpVal;
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;
    
    tmpVal=BL_RD_REG(I2Sx, I2S_DMA_CONFIG);
    /* Set packed mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_FIFO_LR_MERGE,fifoCfg->lRMerge);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_CSR_FIFO_LR_EXCHG,fifoCfg->frameDataExchange);
    /* Clear tx and rx FIFO signal */
    tmpVal = BL_SET_REG_BIT(tmpVal, I2S_TX_FIFO_CLR);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2S_RX_FIFO_CLR);
    
    /* Set DMA config */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_DMA_TX_EN,fifoCfg->txfifoDmaEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_DMA_RX_EN,fifoCfg->rxfifoDmaEnable);
    
    BL_WR_REG(I2Sx, I2S_DMA_CONFIG,tmpVal);
    
    /* Set CLR signal to 0*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_TX_FIFO_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_RX_FIFO_CLR);
    BL_WR_REG(I2Sx, I2S_DMA_CONFIG,tmpVal);
    
    tmpVal=BL_RD_REG(I2Sx, I2S_DMA_FIFO_CONFIG);
    /* Set TX and RX FIFO threshold */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_TX_FIFO_TH,fifoCfg->txFifoLevel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, I2S_RX_FIFO_TH,fifoCfg->rxFifoLevel);
    
    BL_WR_REG(I2Sx, I2S_DMA_FIFO_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  Enable I2S
 *
 * @param  i2sNo: I2S ID type
 * @param  roleType: I2S master or slave
 *
 * @return None
 *
*******************************************************************************/
void I2S_Enable(I2S_ID_Type i2sNo,I2S_Role_Type roleType)
{
    uint32_t tmpVal;
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));
    CHECK_PARAM(IS_I2S_ROLE_TYPE(roleType));

    tmpVal = BL_RD_REG(I2Sx, I2S_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_I2S_TXD_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_I2S_RXD_EN);
        
    /* Set role type */
    if (I2S_ROLE_MASTER == roleType) {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_I2S_M_EN);
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_S_EN);
    } else if (I2S_ROLE_SLAVE == roleType) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_M_EN);
        tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_I2S_S_EN);
    }
    
    BL_WR_REG(I2Sx, I2S_CONFIG, tmpVal);
}

/****************************************************************************//**
 * @brief  Disable I2S
 *
 * @param  i2sNo: I2S ID type
 *
 * @return None
 *
*******************************************************************************/
void I2S_Disable(I2S_ID_Type i2sNo)
{
    uint32_t tmpVal;
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    tmpVal = BL_RD_REG(I2Sx, I2S_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_TXD_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_RXD_EN);
    
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_M_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_I2S_S_EN);
    BL_WR_REG(I2Sx, I2S_CONFIG, tmpVal);
}

/****************************************************************************//**
 * @brief  I2S write data
 *
 * @param  i2sNo: I2S ID type
 * @param  data: write data
 *
 * @return None
 *
*******************************************************************************/
void I2S_Write(I2S_ID_Type i2sNo, uint32_t data)
{
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    while (0 == BL_GET_REG_BITS_VAL(BL_RD_REG(I2Sx, I2S_DMA_FIFO_CONFIG), I2S_TX_FIFO_CNT)){};
    BL_WR_REG(I2Sx, I2S_DMA_WDATA, data);
}

/****************************************************************************//**
 * @brief  I2S set mute
 *
 * @param  i2sNo: I2S ID type
 * @param  enabled: mute enabled or not
 *
 * @return None
 *
*******************************************************************************/
void I2S_Mute(I2S_ID_Type i2sNo, BL_Fun_Type enabled)
{
    uint32_t tmpVal;
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    tmpVal = BL_RD_REG(I2Sx, I2S_CONFIG);
    if(enabled ? 1 : 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, I2S_CSR_MUTE_MODE);
    }
    else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, I2S_CSR_MUTE_MODE);
    }
    BL_WR_REG(I2Sx, I2S_CONFIG, tmpVal);
}

/****************************************************************************//**
 * @brief  I2S flush
 *
 * @param  i2sNo: I2S ID type
 *
 * @return data count in TX FIFO
 *
*******************************************************************************/
uint32_t I2S_GetTxFIFO_AvlCnt(I2S_ID_Type i2sNo)
{
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(I2Sx, I2S_DMA_FIFO_CONFIG), I2S_TX_FIFO_CNT);
}

/****************************************************************************//**
 * @brief  I2S flush
 *
 * @param  i2sNo: I2S ID type
 *
 * @return data count in RX FIFO
 *
*******************************************************************************/
uint32_t I2S_GetRxFIFO_AvlCnt(I2S_ID_Type i2sNo)
{
    /* Get I2S register */
    uint32_t I2Sx = i2sNo ? I2S1_BASE: I2S0_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(I2Sx, I2S_DMA_FIFO_CONFIG), I2S_RX_FIFO_CNT);
}

/****************************************************************************//**
 * @brief  I2S flush
 *
 * @param  i2sNo: I2S ID type
 *
 * @return None
 *
*******************************************************************************/
void I2S_Flush(I2S_ID_Type i2sNo)
{
    /* Check the parameters */
    CHECK_PARAM(IS_I2S_ID_TYPE(i2sNo));

    while (I2S_TX_FIFO_SIZE != I2S_GetTxFIFO_AvlCnt(i2sNo));
}


/*@} end of group I2S_Public_Functions */

/*@} end of group I2S */

/*@} end of group BL60x_Peripheral_Driver */
