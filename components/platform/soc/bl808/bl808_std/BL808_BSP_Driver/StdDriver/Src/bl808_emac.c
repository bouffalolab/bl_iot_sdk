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
#include "bl808_emac.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  EMAC
 *  @{
 */

/** @defgroup  EMAC_Private_Macros
 *  @{
 */
#define PHY_MAX_RETRY      (0x3F)

/*@} end of group EMAC_Private_Macros */

/** @defgroup  EMAC_Private_Types
 *  @{
 */

/*@} end of group EMAC_Private_Types */

/** @defgroup  EMAC_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * emacIntCbfArra[EMAC_INT_CNT]={NULL};
#endif

static const uint32_t emacAddr[EMAC_ID_MAX] = {EMAC0_BASE,EMAC1_BASE};
#define EMAC_USE_ID                     EMAC0_ID

/*@} end of group EMAC_Private_Variables */

/** @defgroup  EMAC_Global_Variables
 *  @{
 */

/*@} end of group EMAC_Global_Variables */

/** @defgroup  EMAC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group EMAC_Private_Fun_Declaration */

/** @defgroup  EMAC_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Set MAC Address
 *
 * @param  macAddr[6]: MAC address buffer array
 *
 * @return None
 *
*******************************************************************************/
static void EMAC_SetMACAddres(EMAC_ID_Type emacId,uint8_t macAddr[6])
{
    uint32_t  EMAC_BASE= emacAddr[emacId];
    BL_WR_REG(EMAC_BASE, EMAC_MAC_ADDR1,(macAddr[0]<<8)|macAddr[1]);
    BL_WR_REG(EMAC_BASE, EMAC_MAC_ADDR0,(macAddr[2]<<24)|(macAddr[3]<<16)|(macAddr[4]<<8)|(macAddr[5]<<0));
}

/****************************************************************************//**
 * @brief  Read PHY register
 *
 * @param  emacId: EMAC ID type
 * @param  phyReg: PHY register
 * @param  regValue: PHY register value pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Phy_Read(EMAC_ID_Type emacId,uint16_t phyReg, uint16_t *regValue)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Set Register Address */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIIADDRESS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,EMAC_RGAD,phyReg);
    BL_WR_REG(EMAC_BASE, EMAC_MIIADDRESS,tmpVal);
    
    /* Trigger read */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIICOMMAND);    
    tmpVal = BL_SET_REG_BIT(tmpVal,EMAC_RSTAT);
    BL_WR_REG(EMAC_BASE, EMAC_MIICOMMAND,tmpVal);
    
    BL_DRV_DUMMY;
    
    do{
        tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIISTATUS);
        ARCH_Delay_US(16);
    }while(BL_IS_REG_BIT_SET(tmpVal, EMAC_MIIM_BUSY));
        
    
    *regValue=BL_RD_REG(EMAC_BASE, EMAC_MIIRX_DATA);
   
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Write PHY register
 *
 * @param  emacId: EMAC ID type
 * @param  phyReg: PHY register
 * @param  regValue: PHY register value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Phy_Write(EMAC_ID_Type emacId,uint16_t phyReg, uint16_t regValue)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Set Register Address */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIIADDRESS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,EMAC_RGAD,phyReg);
    BL_WR_REG(EMAC_BASE, EMAC_MIIADDRESS,tmpVal);
    
    /* Set Write data */
    BL_WR_REG(EMAC_BASE, EMAC_MIITX_DATA,regValue);
    
    /* Trigger write */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIICOMMAND);    
    tmpVal = BL_SET_REG_BIT(tmpVal,EMAC_WCTRLDATA);
    BL_WR_REG(EMAC_BASE, EMAC_MIICOMMAND,tmpVal);
    
    BL_DRV_DUMMY;
    
    do{
        tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIISTATUS); 
    }while(BL_IS_REG_BIT_SET(tmpVal, EMAC_MIIM_BUSY));
        
    
    return SUCCESS;
}

BL_Err_Type EMAC_Phy_Reset(EMAC_ID_Type emacId)
{
    int timeout = 65536UL * 32;
    uint16_t regval = PHY_RESET;

    if(EMAC_Phy_Write(emacId, PHY_BCR, PHY_RESET) != SUCCESS){
        return ERROR;
    }

    for (; timeout; timeout --) {
        if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BCR, &regval)) {
            return ERROR;
        }
        if (!(regval & PHY_RESET)) {
            return SUCCESS;
        }
    }

    return TIMEOUT;
}

BL_Err_Type EMAC_Phy_AutoNegotiate(EMAC_ID_Type emacId, ETHPHY_CFG_Type *cfg)
{
    uint16_t regval = 0;
    uint16_t advertise = 0;
    uint16_t lpa = 0;
    uint32_t timeout = PHY_MAX_RETRY;

    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_PHYID1, &regval)) {
        return ERROR;
    }

    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_PHYID2, &regval)) {
        return ERROR;
    }

    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BCR, &regval)) {
        return ERROR;
    }

    regval &= ~PHY_AUTONEGOTIATION;
    regval &= ~(PHY_LOOPBACK | PHY_POWERDOWN);
    regval |= PHY_ISOLATE;
    if(EMAC_Phy_Write(emacId, PHY_BCR, regval) != SUCCESS){
        return ERROR;
    }

    /* set advertisement mode */
    advertise = PHY_ADVERTISE_100BASETXFULL | PHY_ADVERTISE_100BASETXHALF |
             PHY_ADVERTISE_10BASETXFULL | PHY_ADVERTISE_10BASETXHALF |
             PHY_ADVERTISE_8023;
    if(EMAC_Phy_Write(emacId, PHY_ADVERTISE, advertise) != SUCCESS){
        return ERROR;
    }

    ARCH_Delay_MS(16);
    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BCR, &regval)) {
        return ERROR;
    }

    ARCH_Delay_MS(16);
    regval |= (PHY_FULLDUPLEX_100M | PHY_AUTONEGOTIATION);
    if(EMAC_Phy_Write(emacId, PHY_BCR, regval) != SUCCESS){
        return ERROR;
    }

    regval |= PHY_RESTART_AUTONEGOTIATION;
    regval &= ~PHY_ISOLATE;
    if(EMAC_Phy_Write(emacId, PHY_BCR, regval) != SUCCESS){
        return ERROR;
    }

    ARCH_Delay_MS(16);
    while(1) {
        if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BSR, &regval)) {
            return ERROR;
        }

        if (regval & PHY_AUTONEGO_COMPLETE) {
            /* complete */
            break;
        }

        if (!(--timeout)) {
            return TIMEOUT;
        }
    }

    ARCH_Delay_MS(5000);
    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_LPA, &lpa)) {
        return ERROR;
    }


    if (((advertise & lpa) & PHY_ADVERTISE_100BASETXFULL) != 0)
    {
        /* 100BaseTX and Full Duplex */
        cfg->duplex = EMAC_MODE_FULLDUPLEX;
        cfg->speed = EMAC_SPEED_100M;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXFULL) != 0)
    {
        /* 10BaseT and Full Duplex */
        cfg->duplex = EMAC_MODE_FULLDUPLEX;
        cfg->speed = EMAC_SPEED_10M;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_100BASETXHALF) != 0)
    {
        /* 100BaseTX and half Duplex */
        cfg->duplex = EMAC_MODE_HALFDUPLEX;
        cfg->speed = EMAC_SPEED_100M;
    }
    else if (((advertise & lpa) & PHY_ADVERTISE_10BASETXHALF) != 0)
    {
        /* 10BaseT and half Duplex */
        cfg->duplex = EMAC_MODE_HALFDUPLEX;
        cfg->speed = EMAC_SPEED_10M;
    }

    return SUCCESS;
}

BL_Err_Type EMAC_Phy_Linkup(EMAC_ID_Type emacId, ETHPHY_CFG_Type *cfg)
{
    uint16_t phy_bsr = 0;
    uint16_t phy_sr = 0;

    ARCH_Delay_MS(16);
    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BSR, &phy_bsr)) {
        return ERROR;
    }

    ARCH_Delay_MS(16);
    if (!(PHY_LINKED_STATUS & phy_bsr)) {
        return ERROR;
    }

    ARCH_Delay_MS(16);
    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_SR, &phy_sr)) {
        return ERROR;
    }

    if ((phy_bsr & PHY_BSR_100BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXFULL)) {
        /* 100BaseTX and Full Duplex */
        cfg->duplex = EMAC_MODE_FULLDUPLEX;
        cfg->speed = EMAC_SPEED_100M;
    } else if ((phy_bsr & PHY_BSR_10BASETXFULL) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXFULL)) {
        /* 10BaseT and Full Duplex */
        cfg->duplex = EMAC_MODE_FULLDUPLEX;
        cfg->speed = EMAC_SPEED_10M;
    } else if ((phy_bsr & PHY_BSR_100BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_100BASETXHALF)) {
        /* 100BaseTX and half Duplex */
        cfg->duplex = EMAC_MODE_HALFDUPLEX;
        cfg->speed = EMAC_SPEED_100M;
    } else if ((phy_bsr & PHY_BSR_10BASETXHALF) && PHY_SR_SPEED_MODE_COMPARE(phy_sr, PHY_SR_SPEED_10BASETXHALF)) {
        /* 10BaseT and half Duplex */
        cfg->duplex = EMAC_MODE_HALFDUPLEX;
        cfg->speed = EMAC_SPEED_10M;
    } else {
        /* 10BaseT and half Duplex */
        cfg->duplex = -1;
        cfg->speed = -1;
        return ERROR;
    }

#if 0
    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BCR, &phy_bsr)) {
        return ERROR;
    }

    /* enter test mode: near-end loopback */
    ARCH_Delay_MS(16);
    phy_bsr |= PHY_LOOPBACK;
    if(EMAC_Phy_Write(emacId, PHY_BCR, phy_bsr) != SUCCESS){
        return ERROR;
    }

    if (SUCCESS != EMAC_Phy_Read(emacId, PHY_BCR, &phy_bsr)) {
        return ERROR;
    }
#endif

#if 0
    if (SUCCESS != EMAC_Phy_Read(emacId, 17, &phy_bsr)) {
        return ERROR;
    }

    /* enter test mode: far loopback */
    ARCH_Delay_MS(16);
    phy_bsr |= (1 << 9); /* mode control/status register, FARLOOPBACK bit */
    if(EMAC_Phy_Write(emacId, 17, phy_bsr) != SUCCESS){
        return ERROR;
    }
#endif

    return SUCCESS;
}

/*@} end of group EMAC_Private_Functions */

/** @defgroup  EMAC_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  Initialize EMAC module
 *
 * @param  emacId: EMAC ID type
 * @param  cfg: EMAC configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Init(EMAC_ID_Type emacId,EMAC_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Disable clock gate */
    GLB_AHB_Slave2_Clock_Gate(DISABLE,BL_AHB_SLAVE2_EXT_EMAC);
    
    /* Set MAC config */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_RMII_EN,1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_RECSMALL,cfg->recvSmallFrame);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_PAD,cfg->padEnable);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_HUGEN,cfg->recvHugeFrame);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_CRCEN,cfg->crcEnable);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_NOPRE,cfg->noPreamble);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_BRO,cfg->recvBroadCast);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_PRO,ENABLE);
    //tmpVal |= (1 << 7); /* local loopback in emac */
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_IFG,cfg->interFrameGapCheck);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);
    
    /* Set inter frame gap value */
    BL_WR_REG(EMAC_BASE, EMAC_IPGT,cfg->interFrameGapValue);
    
    /* Set MII interface */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIIMODE);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_MIINOPRE,cfg->miiNoPreamble);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_CLKDIV,cfg->miiClkDiv);
    BL_WR_REG(EMAC_BASE, EMAC_MIIMODE,tmpVal);
    
    /* Set collision */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_COLLCONFIG);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_MAXRET,cfg->maxTxRetry);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_COLLVALID,cfg->collisionValid);
    BL_WR_REG(EMAC_BASE, EMAC_COLLCONFIG,tmpVal);
    
    /* Set frame length */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_PACKETLEN);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_MINFL,cfg->minFrameLen);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_MAXFL,cfg->maxFrameLen);
    BL_WR_REG(EMAC_BASE, EMAC_PACKETLEN,tmpVal);
    
    EMAC_SetMACAddres(emacId,cfg->macAddr);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(EMAC_IRQn,EMAC0_IRQHandler);
    Interrupt_Handler_Register(EMAC_IRQn,EMAC1_IRQHandler);
#endif
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Initialize EMAC PHY module
 *
 * @param  emacId: EMAC ID type
 * @param  cfg: EMAC PHY configuration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_PhyInit(EMAC_ID_Type emacId,ETHPHY_CFG_Type *cfg)
{
    uint32_t tmpVal;
    //uint32_t cnt=0;
    uint16_t phyReg;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Set Phy Address */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MIIADDRESS);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_FIAD,cfg->phyAddress);
    BL_WR_REG(EMAC_BASE, EMAC_MIIADDRESS,tmpVal);

    if (SUCCESS != EMAC_Phy_Reset(EMAC_USE_ID)) {
        return ERROR;
    }

    if(cfg->autoNegotiation){
/*
        do{
            if(EMAC_Phy_Read(emacId, PHY_BSR, &phyReg) != SUCCESS){
                return ERROR;
            }
            cnt++;
            if(cnt>PHY_LINK_TO){
                return ERROR;
            }
        }while((phyReg & PHY_LINKED_STATUS) != PHY_LINKED_STATUS);
*/
        EMAC_Phy_AutoNegotiate(emacId,cfg);
    }else{      
        if(EMAC_Phy_Read(emacId, PHY_BCR, &phyReg) != SUCCESS){
            return ERROR;
        }
        phyReg&=(~PHY_FULLDUPLEX_100M);
        if(cfg->speed == EMAC_SPEED_10M){
            if(cfg->duplex==EMAC_MODE_FULLDUPLEX){
                phyReg|=PHY_FULLDUPLEX_10M;
            }else{
                phyReg|=PHY_HALFDUPLEX_10M;
            }
        }else{
            if(cfg->duplex==EMAC_MODE_FULLDUPLEX){
                phyReg|=PHY_FULLDUPLEX_100M;
            }else{
                phyReg|=PHY_HALFDUPLEX_100M;
            }
        }
        if((EMAC_Phy_Write(emacId, PHY_BCR, phyReg)) != SUCCESS){
            return ERROR;
        }
    }
    
    /* Set MAC duplex config */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,EMAC_FULLD,cfg->duplex);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);

    return EMAC_Phy_Linkup(emacId,cfg);
}

/****************************************************************************//**
 * @brief  DeInitialize EMAC module
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_DeInit(void)
{
    EMAC_Disable(EMAC_USE_ID);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Initialize EMAC TX RX MDA buffer
 *
 * @param  emacId: EMAC ID type
 * @param  handle: EMAC handle pointer
 * @param  txBuff: TX buffer
 * @param  txBuffCount: TX buffer count
 * @param  rxBuff: RX buffer
 * @param  rxBuffCount: RX buffer count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_DMADescListInit(EMAC_ID_Type emacId,EMAC_Handle_Type *handle,uint8_t *txBuff, uint32_t txBuffCount,uint8_t *rxBuff, uint32_t rxBuffCount)
{
    uint32_t i = 0;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Set the Ethernet handler env */
    handle->bd = (EMAC_BD_Desc_Type *)(uintptr_t)(EMAC_BASE+EMAC_DMA_DESC_OFFSET);
    handle->txIndexEMAC = 0;
    handle->txIndexCPU  = 0;
    handle->txBuffLimit = txBuffCount - 1;
    /* The receive descriptors' address starts right after the last transmit BD. */
    handle->rxIndexEMAC = txBuffCount;
    handle->rxIndexCPU  = txBuffCount;
    handle->rxBuffLimit = txBuffCount + rxBuffCount - 1;

    /* Fill each DMARxDesc descriptor with the right values */
    for(i=0; i < txBuffCount; i++){
        /* Get the pointer on the ith member of the Tx Desc list */
        handle->bd[i].C_S_L = 0;
        handle->bd[i].Buffer= (NULL == txBuff) ? 0 : (uintptr_t)(txBuff+(ETH_MAX_PACKET_SIZE*i));
    }
    /* For the last TX DMA Descriptor, it should be wrap back */
    handle->bd[handle->txBuffLimit].C_S_L |= EMAC_BD_FIELD_MSK(TX_WR);

    for(i = txBuffCount; i < (txBuffCount + rxBuffCount); i++){
        /* Get the pointer on the ith member of the Rx Desc list */
        handle->bd[i].C_S_L = (ETH_MAX_PACKET_SIZE << 16) |
                               EMAC_BD_FIELD_MSK(RX_IRQ) |
                               EMAC_BD_FIELD_MSK(RX_E);
        handle->bd[i].Buffer= ( NULL == rxBuff) ? 0 : (uintptr_t)(rxBuff+(ETH_MAX_PACKET_SIZE*i));
    }
    /* For the last RX DMA Descriptor, it should be wrap back */
    handle->bd[handle->rxBuffLimit].C_S_L |= EMAC_BD_FIELD_MSK(RX_WR);
    
    /* For the TX DMA Descriptor, it will wrap to 0 according to EMAC_TX_BD_NUM*/
    BL_WR_REG(EMAC_BASE, EMAC_TX_BD_NUM,txBuffCount);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Get TX MDA buffer descripter for data to send
 *
 * @param  handle: EMAC handle pointer
 * @param  txDMADesc: TX DMA descriptor pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_DMATxDescGet(EMAC_Handle_Type *handle,EMAC_BD_Desc_Type **txDMADesc)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Start TX
 *
 * @param  handle: EMAC handle pointer
 * @param  txDMADesc: TX DMA descriptor pointer
 * @param  len: len
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_StartTx(EMAC_Handle_Type *handle,EMAC_BD_Desc_Type *txDMADesc, uint32_t len)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Enable EMAC module
 *
 * @param  emacId: EMAC ID type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Enable(EMAC_ID_Type emacId)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Enable EMAC */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_SET_REG_BIT(tmpVal,EMAC_TXEN);
    tmpVal=BL_SET_REG_BIT(tmpVal,EMAC_RXEN);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  EMAC_Enable_TX
 *
 * @param  emacId: EMAC ID type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Enable_TX(EMAC_ID_Type emacId)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Enable EMAC */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_SET_REG_BIT(tmpVal,EMAC_TXEN);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  EMAC_Disable_TX
 *
 * @param  emacId: EMAC ID type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Disable_TX(EMAC_ID_Type emacId)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Enable EMAC */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,EMAC_TXEN);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Disable EMAC module
 *
 * @param  emacId: EMAC ID type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_Disable(EMAC_ID_Type emacId)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    /* Enable EMAC */
    tmpVal=BL_RD_REG(EMAC_BASE, EMAC_MODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,EMAC_TXEN);
    tmpVal=BL_CLR_REG_BIT(tmpVal,EMAC_RXEN);
    BL_WR_REG(EMAC_BASE, EMAC_MODE,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  EMAC mask or unmask certain or all interrupt
 *
 * @param  emacId: EMAC ID type
 * @param  intType: EMAC interrupt type
 * @param  intMask: EMAC interrupt mask value( MASK:disbale interrupt,UNMASK:enable interrupt )
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_IntMask(EMAC_ID_Type emacId,EMAC_INT_Type intType,BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Check the parameters */
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal = BL_RD_REG(EMAC_BASE,EMAC_INT_MASK);

    /* Mask or unmask certain or all interrupt */    
    if(MASK == intMask){
        tmpVal |= intType;
    }else{
        tmpVal &= (~intType);
    }
    
    /* Write back */
    BL_WR_REG(EMAC_BASE,EMAC_INT_MASK,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Get EMAC interrupt status
 *
 * @param  emacId: EMAC ID type
 * @param  intType: EMAC interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Sts_Type EMAC_GetIntStatus(EMAC_ID_Type emacId,EMAC_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Check the parameters */
    CHECK_PARAM(IS_EMAC_INT_TYPE(intType));
    
    tmpVal = BL_RD_REG(EMAC_BASE,EMAC_INT_SOURCE);
    
    return (tmpVal & intType) ? SET : RESET;
    
}

/****************************************************************************//**
 * @brief  Clear EMAC interrupt
 *
 * @param  emacId: EMAC ID type
 * @param  intType: EMAC interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_ClrIntStatus(EMAC_ID_Type emacId,EMAC_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];

    /* Check the parameters */
    CHECK_PARAM(IS_EMAC_INT_TYPE(intType));

    tmpVal = BL_RD_REG(EMAC_BASE,EMAC_INT_SOURCE);

    BL_WR_REG(EMAC_BASE,EMAC_INT_SOURCE,tmpVal | intType);

    return SUCCESS;
}


/****************************************************************************//**
 * @brief  EMAC_Int_Callback_Install
 *
 * @param  intIdx: EMAC_INT_Index
 * @param  cbFun: call back
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type EMAC_Int_Callback_Install(EMAC_INT_Index intIdx, intCallback_Type* cbFun)
{
    /* Check the parameters */

    emacIntCbfArra[intIdx] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************//**
 * @brief  EMAC_IRQHandler
 *
 * @param  emacId: EMAC ID type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void EMAC_IRQHandler(EMAC_ID_Type emacId)
{
    uint32_t tmpVal;
    uint32_t  EMAC_BASE= emacAddr[emacId];
    
    tmpVal = BL_RD_REG(EMAC_BASE,EMAC_INT_MASK);
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_DONE) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXB_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_DONE);
        if(emacIntCbfArra[EMAC_INT_TX_DONE_IDX]){
            emacIntCbfArra[EMAC_INT_TX_DONE_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_ERROR) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXE_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_ERROR);
        if(emacIntCbfArra[EMAC_INT_TX_ERROR_IDX]){
            emacIntCbfArra[EMAC_INT_TX_ERROR_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_DONE) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXB_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_DONE);
        if(emacIntCbfArra[EMAC_INT_RX_DONE_IDX]){
            emacIntCbfArra[EMAC_INT_RX_DONE_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_ERROR) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXE_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_ERROR);
        if(emacIntCbfArra[EMAC_INT_RX_ERROR_IDX]){
            emacIntCbfArra[EMAC_INT_RX_ERROR_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_BUSY) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_BUSY_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_BUSY);
        if(emacIntCbfArra[EMAC_INT_RX_BUSY_IDX]){
            emacIntCbfArra[EMAC_INT_RX_BUSY_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_TX_CTRL) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_TXC_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_TX_CTRL);
        if(emacIntCbfArra[EMAC_INT_TX_CTRL_IDX]){
            emacIntCbfArra[EMAC_INT_TX_CTRL_IDX]();
        }
    }
    
    if (SET == EMAC_GetIntStatus(emacId,EMAC_INT_RX_CTRL) && !BL_IS_REG_BIT_SET(tmpVal,EMAC_RXC_M)) {
        EMAC_ClrIntStatus(emacId,EMAC_INT_RX_CTRL);
        if(emacIntCbfArra[EMAC_INT_RX_CTRL_IDX]){
            emacIntCbfArra[EMAC_INT_RX_CTRL_IDX]();
        }
    }
}
#endif

/****************************************************************************//**
 * @brief  EMAC0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void EMAC0_IRQHandler(void)
{
    EMAC_IRQHandler(EMAC0_ID);
}
#endif

/****************************************************************************//**
 * @brief  EMAC1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void EMAC1_IRQHandler(void)
{
    EMAC_IRQHandler(EMAC1_ID);
}
#endif

/****************************************************************************//**
 * @brief  Request to pause TX
 *
 * @param  emacId: EMAC ID type
 * @param  timeCount: Pause time count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_TxPauseReq(EMAC_ID_Type emacId,uint16_t timeCount)
{
    uint32_t  EMAC_BASE= emacAddr[emacId];

    BL_WR_REG(EMAC_BASE,EMAC_TXCTRL,(1<<16)|timeCount);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Set hash value
 *
 * @param  emacId: EMAC ID type
 * @param  hash0: Hash value one
 * @param  hash1: Hash value two
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EMAC_SetHash(EMAC_ID_Type emacId,uint32_t hash0,uint32_t hash1)
{
    uint32_t  EMAC_BASE= emacAddr[emacId];

    BL_WR_REG(EMAC_BASE,EMAC_HASH0_ADDR,hash0);
    
    BL_WR_REG(EMAC_BASE,EMAC_HASH1_ADDR,hash1);
    
    return SUCCESS;
}


/*@} end of group EMAC_Public_Functions */

/*@} end of group EMAC */

/*@} end of group BL808_Peripheral_Driver */
