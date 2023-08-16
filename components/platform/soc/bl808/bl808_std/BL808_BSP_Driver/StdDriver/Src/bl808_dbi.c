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

#include "bl808_dbi.h"
#include "dbi_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DBI
 *  @{
 */

/** @defgroup  DBI_Private_Macros
 *  @{
 */

/*@} end of group DBI_Private_Macros */

/** @defgroup  DBI_Private_Types
 *  @{
 */

/*@} end of group DBI_Private_Types */

/** @defgroup  DBI_Private_Variables
 *  @{
 */

/**
 *  @brief DBI interrupt callback function address array
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * DBIIntCbfArra[DBI_INT_ALL]= {
    NULL
};
#endif

/*@} end of group DBI_Private_Variables */

/** @defgroup  DBI_Global_Variables
 *  @{
 */

/*@} end of group DBI_Global_Variables */

/** @defgroup  DBI_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DBI_Private_Fun_Declaration */

/** @defgroup  DBI_Private_Functions
 *  @{
 */

/*@} end of group DBI_Private_Functions */

/** @defgroup  DBI_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  DBI interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DBI_IRQHandler(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_INT_STS);
    
    /* DBI transfer end interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,DBI_END_INT) && !BL_IS_REG_BIT_SET(tmpVal,DBI_CR_DBI_END_MASK)){
        BL_WR_REG(DBI_BASE,DBI_INT_STS,BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_END_CLR));
        if(DBIIntCbfArra[DBI_INT_END] != NULL){
            DBIIntCbfArra[DBI_INT_END]();
        }
    }
    
    /* DBI tx fifo ready interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,DBI_TXF_INT) && !BL_IS_REG_BIT_SET(tmpVal,DBI_CR_DBI_TXF_MASK)){
        if(DBIIntCbfArra[DBI_INT_TX_FIFO_REQ] != NULL){
            DBIIntCbfArra[DBI_INT_TX_FIFO_REQ]();
        }
    }
    
    /* DBI tx fifo ready interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,DBI_FER_INT) && !BL_IS_REG_BIT_SET(tmpVal,DBI_CR_DBI_FER_MASK)){
        if(DBIIntCbfArra[DBI_INT_FIFO_ERR] != NULL){
            DBIIntCbfArra[DBI_INT_FIFO_ERR]();
        }
    }
}
#endif


/****************************************************************************//**
 * @brief  DBI init
 *
 * @param  dbiCfg: DBI configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type DBI_Init(DBI_CFG_Type *dbiCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_MODE_TYPE(dbiCfg->mode));
    CHECK_PARAM(IS_DBI_PIXEL_FORMAT_TYPE(dbiCfg->pixelFormat));
    CHECK_PARAM(IS_DBI_FIFO_FORMAT_TYPE(dbiCfg->fifoFormat));
    CHECK_PARAM(IS_DBI_SCL_CLK_PHASE_TYPE(dbiCfg->clkPhase));
    CHECK_PARAM(IS_DBI_SCL_CLK_POLARITY_TYPE(dbiCfg->clkPolarity));

    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    
    /* Select DBI type B or C */
    if(dbiCfg->mode == DBI_TYPE_B){
        tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_SEL);
    }else if(dbiCfg->mode == DBI_TYPE_C_3_WIRE){
        tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_SEL);
        tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_TC_3W_MODE);
    }else{
        tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_SEL);
        tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_TC_3W_MODE);
    }
    
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_CONT_EN,dbiCfg->continueEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DMY_EN,dbiCfg->dummyEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DMY_CNT,dbiCfg->dummyCnt);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_SCL_PH,dbiCfg->clkPhase);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_SCL_POL,dbiCfg->clkPolarity);
    
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Set data period */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_PRD);
    
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PRD_S,dbiCfg->startLen);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PRD_D_PH_0,dbiCfg->dataPhase0Len);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PRD_D_PH_1,dbiCfg->dataPhase1Len);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PRD_I,dbiCfg->intervalLen);
    
    BL_WR_REG(DBI_BASE,DBI_PRD,tmpVal);
    
    /* Set pixel format */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_PIX_CNT);
    
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PIX_FORMAT,dbiCfg->pixelFormat);
    
    BL_WR_REG(DBI_BASE,DBI_PIX_CNT,tmpVal);
    
    /* Set fifo format */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_0);
    
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_FIFO_FORMAT,dbiCfg->fifoFormat);
    
    BL_WR_REG(DBI_BASE,DBI_FIFO_CONFIG_0,tmpVal);
    
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(DBI_IRQn,DBI_IRQHandler);
#endif
    
    return SUCCESS;
}


/****************************************************************************//**
 * @brief  DBI command and data configuration
 *
 * @param  cdCfg: Pointer of DBI CD configure type
 *
 * @return None
 *
*******************************************************************************/
void DBI_CDConfig(DBI_CD_CFG_Type *cdCfg)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DBI_DATA_TYPE(cdCfg->dataType));
    CHECK_PARAM(IS_DBI_DATA_DIRECTION_TYPE(cdCfg->dataDir));
    
    /* Set command and data comfiguration */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_CMD_EN,cdCfg->commandEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_CMD,cdCfg->command);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DAT_EN,cdCfg->dataEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DAT_TP,cdCfg->dataType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DAT_WR,cdCfg->dataDir);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DAT_BC,cdCfg->dataCnt);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    BL_WR_REG(DBI_BASE,DBI_WDATA,cdCfg->data);
}


/****************************************************************************//**
 * @brief  DBI enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN));
}


/****************************************************************************//**
 * @brief  DBI disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_Disable(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN));
}


/****************************************************************************//**
 * @brief  DBI set to send pixel data function
 *
 * @param  length: Length of data
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetPixel(uint32_t length)
{
    uint32_t tmpVal;
    
    /* Set pixel data */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_TP);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_WR);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_PIX_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PIX_CNT,length-1);
    BL_WR_REG(DBI_BASE,DBI_PIX_CNT,tmpVal);
}


/****************************************************************************//**
 * @brief  DBI send command function
 *
 * @param  command: Command to send
 *
 * @return None
 *
*******************************************************************************/
void DBI_SendCommand(uint8_t command)
{
    uint32_t tmpVal;
    
    /* Set command */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_CMD,command);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Clear interrupt */
    DBI_IntClear();
    
    /* Enable transfer */
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Wait send done */
    while(DBI_GetIntStatus(DBI_INT_END) != SET){}
    
    /* Disable transfer and clear interrupt */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    DBI_IntClear();
}


/****************************************************************************//**
 * @brief  DBI send normal data function
 *
 * @param  data: Data to send
 * @param  byteCnt: Byte count of data
 *
 * @return None
 *
*******************************************************************************/
void DBI_SendData(uint32_t data,uint8_t byteCnt)
{
    uint32_t tmpVal;
    
    /* Set normal data */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_DAT_TP);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_WR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_DAT_BC,byteCnt-1);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    BL_WR_REG(DBI_BASE,DBI_WDATA,data);
    
    /* Clear interrupt */
    DBI_IntClear();
    
    /* Enable transfer */
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Wait send done */
    while(DBI_GetIntStatus(DBI_INT_END) != SET){}
    
    /* Disable transfer and clear interrupt */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    DBI_IntClear();
}


/****************************************************************************//**
 * @brief  DBI send single pixel data function
 *
 * @param  data: Data to send
 * @param  length: Length of data
 *
 * @return None
 *
*******************************************************************************/
void DBI_SendSinglePixel(uint32_t data,uint32_t length)
{
    uint32_t tmpVal;
    uint32_t txLen = 0;
    
    /* Set pixel data */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_TP);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_WR);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_PIX_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PIX_CNT,length-1);
    BL_WR_REG(DBI_BASE,DBI_PIX_CNT,tmpVal);
    
    /* Clear interrupt */
    DBI_IntClear();
    
    /* Write one data to fifo */
    if(DBI_GetTxFifoCount() > 0){
        BL_WR_REG(DBI_BASE,DBI_FIFO_WDATA,data);
        txLen++;
    }
    
    
    /* Enable transfer */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    while(txLen < length){
        if(DBI_GetTxFifoCount() > 0){
            BL_WR_REG(DBI_BASE,DBI_FIFO_WDATA,data);
            txLen++;
        }
    }
    
    /* Wait send done */
    while(DBI_GetIntStatus(DBI_INT_END) != SET){}
    
    /* Disable transfer and clear interrupt */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    DBI_IntClear();
}


/****************************************************************************//**
 * @brief  DBI send various pixel data function
 *
 * @param  data: Data buffer to send
 * @param  length: Length of data buffer
 *
 * @return None
 *
*******************************************************************************/
void DBI_SendVariousPixel(uint32_t *data,uint32_t length)
{
    uint32_t tmpVal;
    uint32_t txLen = 0;
    
    /* Set pixel data */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_TP);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_WR);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_PIX_CNT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_PIX_CNT,length-1);
    BL_WR_REG(DBI_BASE,DBI_PIX_CNT,tmpVal);
    
    /* Clear interrupt */
    DBI_IntClear();
    
    /* Write one data to fifo */
    if(DBI_GetTxFifoCount() > 0){
        BL_WR_REG(DBI_BASE,DBI_FIFO_WDATA,data[txLen++]);
    }
    
    /* Enable transfer */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    while(txLen < length){
        if(DBI_GetTxFifoCount() > 0){
            BL_WR_REG(DBI_BASE,DBI_FIFO_WDATA,data[txLen++]);
        }
    }
    
    /* Wait send done */
    while(DBI_GetIntStatus(DBI_INT_END) != SET){}
    
    /* Disable transfer and clear interrupt */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    DBI_IntClear();
}


/****************************************************************************//**
 * @brief  DBI receive data function
 *
 * @param  None
 *
 * @return Data received
 *
*******************************************************************************/
uint32_t DBI_ReceiveData(void)
{
    uint32_t tmpVal;
    
    /* Set normal data */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_DAT_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_CMD_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_DAT_TP);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_DAT_WR);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Clear interrupt */
    DBI_IntClear();
    
    /* Enable transfer */
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    
    /* Wait send done */
    while(DBI_GetIntStatus(DBI_INT_END) != SET){}
    
    /* Disable transfer and clear interrupt */
    tmpVal = BL_RD_REG(DBI_BASE,DBI_CONFIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal,DBI_CR_DBI_EN);
    BL_WR_REG(DBI_BASE,DBI_CONFIG,tmpVal);
    DBI_IntClear();
    
    return BL_RD_REG(DBI_BASE,DBI_RDATA);
}


/****************************************************************************//**
 * @brief  Clear tx fifo,overflow/underflow flag and fifo error interrupt will be cleared
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_TxFifoClear(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BIT(tmpVal,DBI_TX_FIFO_CLR);
    BL_WR_REG(DBI_BASE,DBI_FIFO_CONFIG_0,tmpVal);
}


/****************************************************************************//**
 * @brief  Enable or disable signal of dma interface
 *
 * @param  dmaEn: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetDMA(BL_Fun_Type dmaEn)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_DMA_TX_EN,dmaEn);
    BL_WR_REG(DBI_BASE,DBI_FIFO_CONFIG_0,tmpVal);
}


/****************************************************************************//**
 * @brief  Set tx fifo threshold
 *
 * @param  threshold: Threshold value
 *
 * @return None
 *
*******************************************************************************/
void DBI_SetTxFifoThreshold(uint8_t threshold)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_TX_FIFO_TH,threshold);
    BL_WR_REG(DBI_BASE,DBI_FIFO_CONFIG_1,tmpVal);
}


/****************************************************************************//**
 * @brief  Get tx fifo count value
 *
 * @param  None
 *
 * @return Count value
 *
*******************************************************************************/
uint8_t DBI_GetTxFifoCount(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_1),DBI_TX_FIFO_CNT);
}


/****************************************************************************//**
 * @brief  Get interrupt status
 *
 * @param  intType: DBI interrupt type
 *
 * @return Status of interrupt
 *
*******************************************************************************/
BL_Sts_Type DBI_GetIntStatus(DBI_INT_Type intType)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_INT_STS);
    
    if((tmpVal<<intType&1) == 1){
        return SET;
    }else{
        return RESET;
    }
}


/****************************************************************************//**
 * @brief  Get tx fifo overflow/underflow status
 *
 * @param  overflow: Select overflow or underflow
 *
 * @return Status of tx fifo
 *
*******************************************************************************/
BL_Sts_Type DBI_GetOverflowStatus(DBI_Overflow_Type overflow)
{
    uint32_t tmpVal;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DBI_OVERFLOW_TYPE(overflow));
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_FIFO_CONFIG_0);
    
    if(overflow == DBI_TX_OVERFLOW){
        if(BL_IS_REG_BIT_SET(tmpVal,DBI_TX_FIFO_OVERFLOW)){
            return SET;
        }else{
            return RESET;
        }
    }else{
        if(BL_IS_REG_BIT_SET(tmpVal,DBI_TX_FIFO_UNDERFLOW)){
            return SET;
        }else{
            return RESET;
        }
    }
}


/****************************************************************************//**
 * @brief  Get DBI bus busy status
 *
 * @param  None
 *
 * @return Status of DBI bus
 *
*******************************************************************************/
BL_Sts_Type DBI_GetBusBusyStatus(void)
{
    if(BL_IS_REG_BIT_SET(BL_RD_REG(DBI_BASE,DBI_BUS_BUSY),DBI_STS_DBI_BUS_BUSY)){
        return SET;
    }else{
        return RESET;
    }
}


/****************************************************************************//**
 * @brief  Mask/Unmask the DBI interrupt
 *
 * @param  intType: DBI interrupt type
 * @param  intMask: Mask/Unmask
 *
 * @return None
 *
*******************************************************************************/
void DBI_IntMask(DBI_INT_Type intType,BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DBI_INT_TYPE(intType));

    tmpVal = BL_RD_REG(DBI_BASE,DBI_INT_STS);

    switch(intType){
        case DBI_INT_END:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_END_MASK,intMask);
            break;
        case DBI_INT_TX_FIFO_REQ:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_TXF_MASK,intMask);
            break;
        case DBI_INT_FIFO_ERR:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_FER_MASK,intMask);
            break;
        case DBI_INT_ALL:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_END_MASK,intMask);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_TXF_MASK,intMask);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal,DBI_CR_DBI_FER_MASK,intMask);
            break;
        default:
            break;
    }
    
    BL_WR_REG(DBI_BASE,DBI_INT_STS,tmpVal);
}


/****************************************************************************//**
 * @brief  Clear DBI interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void DBI_IntClear(void)
{
    uint32_t tmpVal;
    
    tmpVal = BL_RD_REG(DBI_BASE,DBI_INT_STS);
    BL_WR_REG(DBI_BASE,DBI_INT_STS,BL_SET_REG_BIT(tmpVal,DBI_CR_DBI_END_CLR));
}


/****************************************************************************//**
 * @brief  Install DBI interrupt callback function
 *
 * @param  intType: DBI interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DBI_Int_Callback_Install(DBI_INT_Type intType,intCallback_Type* cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_DBI_INT_TYPE(intType));
    
    DBIIntCbfArra[intType] = cbFun;
}
#endif

/*@} end of group DBI_Public_Functions */

/*@} end of group DBI */

/*@} end of group BL808_Peripheral_Driver */
