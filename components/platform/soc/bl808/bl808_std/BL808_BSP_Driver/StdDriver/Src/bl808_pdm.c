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

#include "bl808.h"
#include "bl808_pdm.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDM
 *  @{
 */

/** @defgroup  PDM_Private_Macros
 *  @{
 */

/*@} end of group PDM_Private_Macros */

/** @defgroup  PDM_Private_Types
 *  @{
 */

/*@} end of group PDM_Private_Types */

/** @defgroup  PDM_Private_Variables
 *  @{
 */

/*@} end of group PDM_Private_Variables */

/** @defgroup  PDM_Global_Variables
 *  @{
 */

/*@} end of group PDM_Global_Variables */

/** @defgroup  PDM_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PDM_Private_Fun_Declaration */

/** @defgroup  PDM_Private_Functions
 *  @{
 */

/*@} end of group PDM_Private_Functions */

/** @defgroup  PDM_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Config PDM module
 *
 * @param  cfg: PDM configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void PDM_Init(PDM_CFG_Type *cfg)
{
    uint32_t tmpVal;
    
    /* Disable PDM first */
    tmpVal = BL_RD_REG(PDM_BASE, PDM_DATAPATH_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDM_DMA_RX_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDM_DMA_TX_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDM_EN);
    BL_WR_REG(PDM_BASE, PDM_DATAPATH_CONFIG,tmpVal);
    
    /* Set PDM config */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_OUT_SEL_INV,cfg->outClkInv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_OUT_SEL_DLY,cfg->outClkDly);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_OUT_DAT_DLY,cfg->outDataDly);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_DSD_SWAP,cfg->dsdSwap);
    
    if(cfg->chanType==PDM_CHAN_LEFT_RIGHT){
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_FORCE_SEL);
    }else{
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_FORCE_SEL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_FORCE_LR,cfg->chanType);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_TX_SEL_128FS,cfg->txFs);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_SEL_128FS,cfg->rxFs); 

    BL_WR_REG(PDM_BASE, PDM_DATAPATH_CONFIG,tmpVal);    
}

/****************************************************************************//**
 * @brief  Config PDM FIFO
 *
 * @param  cfg: PDM FIFO configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void PDM_FIFO_Init(PDM_FIFO_CFG_Type *cfg)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(PDM_BASE, PDM_DMA_CONFIG);
    
    /* Set PDM FIFO config */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_TX_DATA_SHIFT,cfg->txDataRShift);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_TX_FORMAT,cfg->txFmt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_DMA_TX_EN,cfg->txDMAEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_FORMAT,cfg->rxFmt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_DMA_RX_EN,cfg->rxDMAEn);

    BL_WR_REG(PDM_BASE, PDM_DMA_CONFIG,tmpVal);    
}

/****************************************************************************//**
 * @brief  Enable PDM
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void PDM_Enable(void)
{
    uint32_t tmpVal;
    
    /* Enable PDM */
    tmpVal = BL_RD_REG(PDM_BASE, PDM_DATAPATH_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDM_EN);
    BL_WR_REG(PDM_BASE, PDM_DATAPATH_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  Disable PDM
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void PDM_Disable(void)
{
    uint32_t tmpVal;
    
    /* Disable PDM */
    tmpVal = BL_RD_REG(PDM_BASE, PDM_DATAPATH_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDM_EN);
    BL_WR_REG(PDM_BASE, PDM_DATAPATH_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  Read PCM data from PDM stream
 *
 * @param  None
 *
 * @return PCM data
 *
*******************************************************************************/
uint32_t PDM_Read(void)
{
    return BL_RD_REG(PDM_BASE, PDM_DMA_RDATA);
}

/****************************************************************************//**
 * @brief  Write PDM data
 *
 * @param  data: PDM data
 *
 * @return None
 *
*******************************************************************************/
void PDM_Write1(uint32_t data)
{
    while(BL_IS_REG_BIT_SET(BL_RD_REG(PDM_BASE, PDM_TX_FIFO_STATUS), PDM_TX_FIFO_FULL)){
        /*wait FIFO when it's full*/
    };
    BL_WR_REG(PDM_BASE, PDM_DMA_WDATA,data);
}

/****************************************************************************//**
 * @brief  Write PDM data2
 *
 * @param  data: PDM data
 *
 * @return None
 *
*******************************************************************************/
void PDM_Write2(uint32_t data)
{
    while(BL_IS_REG_BIT_SET(BL_RD_REG(PDM_BASE, PDM_TX_FIFO_STATUS), PDM_TX2_FIFO_FULL)){
        /*wait FIFO when it's full*/
    };
    BL_WR_REG(PDM_BASE, PDM_DMA_WDATA2,data);
}

/*@} end of group PDM_Public_Functions */

/*@} end of group PDM */

/*@} end of group BL60x_Peripheral_Driver */
