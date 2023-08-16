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

#include "bl808_dsi.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSI
 *  @{
 */

/** @defgroup  DSI_Private_Macros
 *  @{
 */


/*@} end of group DSI_Private_Macros */

/** @defgroup  DSI_Private_Types
 *  @{
 */

/*@} end of group DSI_Private_Types */

/** @defgroup  DSI_Private_Variables
 *  @{
 */

static const uint32_t dsiAddr[DSI_ID_MAX] = {DSI_BASE};

/**
 *  @brief DSI interrupt callback function address array
*/
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *DSIIntCbfArra[DSI_ID_MAX][DSI_INT_COUNT] = {
    {NULL,NULL,NULL}
};
#endif
/*@} end of group DSI_Private_Variables */

/** @defgroup  DSI_Global_Variables
 *  @{
 */

/*@} end of group DSI_Global_Variables */

/** @defgroup  DSI_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type DSI_IntHandler(DSI_ID_Type dsiId);
#endif

/*@} end of group DSI_Private_Fun_Declaration */

/** @defgroup  DSI_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  DSI interrupt handle
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type DSI_IntHandler(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_CAM_ID_TYPE(dsiId));
    
    tmpVal=BL_RD_REG(DSIx,DSI_INT_STATUS);
    if(tmpVal&DSI_INT_DATA_OVERRUN_ERR){
        DSI_IntClear(dsiId,DSI_INT_DATA_OVERRUN_ERR);
        if(DSIIntCbfArra[dsiId][0] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][0]();
        }
    }

    if(tmpVal&DSI_INT_DATA_DISCONT_ERR){
        DSI_IntClear(dsiId,DSI_INT_DATA_DISCONT_ERR);
        if(DSIIntCbfArra[dsiId][1] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][1]();
        }
    }

    if(tmpVal&DSI_INT_DATA_LEN_ERR){
        DSI_IntClear(dsiId,DSI_INT_DATA_LEN_ERR);
        if(DSIIntCbfArra[dsiId][2] != NULL) {
            /* call the callback function */
            DSIIntCbfArra[dsiId][2]();
        }
    }

    return SUCCESS;
}
#endif

/*@} end of group DSI_Private_Functions */

/** @defgroup  DSI_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  DSI module init
 *
 * @param  dsiId: DSI ID type
 * @param  cfg: DSI configuration structure pointer
 *
 * @return None
 *
*******************************************************************************/
void DSI_Init(DSI_ID_Type dsiId,DSI_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_DSI_DATA_TYPE(cfg->dataType));
    
    /* Set DSI configuration */
    tmpVal=BL_RD_REG(DSIx,DSI_CONFIG);

    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,DSI_CR_VC,cfg->virtualChans);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,DSI_CR_DT,cfg->dataType);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,DSI_CR_LSE_PKT_EN,cfg->lsePktEn);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,DSI_CR_LANE_NUM,cfg->laneNum);
        
    BL_WR_REG(DSIx,DSI_CONFIG,tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(MIPI_DSI_IRQn,DSI0_IRQHandler);
#endif
}

/****************************************************************************//**
 * @brief  Deinit DSI module
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_Deinit(DSI_ID_Type dsiId)
{

}

/****************************************************************************//**
 * @brief  Enable DSI module
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_Enable(DSI_ID_Type dsiId)
{    
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    
    /* Enable DSI module */
    tmpVal=BL_RD_REG(DSIx,DSI_CONFIG);

    tmpVal=BL_RD_REG(DSIx,DSI_CONFIG);
    tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CR_ENABLE);

    BL_WR_REG(DSIx,DSI_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  Disable DSI module
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_Disable(DSI_ID_Type dsiId)
{    
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    
    /* Enable DSI module */
    tmpVal=BL_RD_REG(DSIx,DSI_CONFIG);

    tmpVal=BL_RD_REG(DSIx,DSI_CONFIG);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CR_ENABLE);

    BL_WR_REG(DSIx,DSI_CONFIG,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI Enable Disable Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntMask(DSI_ID_Type dsiId,DSI_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpVal=BL_RD_REG(DSIx,DSI_INT_MASK);

    if(intMask == UNMASK){
        /* Enable this interrupt */
        tmpVal &= (~intType);
        
    }else{
        /* Disable this interrupt */
        tmpVal |= intType;
    }

    BL_WR_REG(DSIx,DSI_INT_MASK,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI Clear Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntClear(DSI_ID_Type dsiId,DSI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_INT_CLEAR);

    /* Disable this interrupt */
    tmpVal |= intType;

    BL_WR_REG(DSIx,DSI_INT_CLEAR,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI Enable Interrupt
 *
 * @param  dsiId: DSI ID type
 * @param  intType: DSI Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void DSI_IntEnable(DSI_ID_Type dsiId,DSI_INT_Type intType)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_INT_ENABLE);

    /* Disable this interrupt */
    tmpVal |= intType;

    BL_WR_REG(DSIx,DSI_INT_ENABLE,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI Get Interrupt status
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
DSI_INT_Type DSI_IntGet(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_INT_STATUS);

    return BL_GET_REG_BITS_VAL(tmpVal,DSI_INT_STATUS);
}

/****************************************************************************//**
 * @brief  DSI Set LS/LE packet
 *
 * @param  dsiId: DSI ID type
 *
 * @param  num: frame number
 *
 * @return None
 *
*******************************************************************************/
void DSI_Set_Frame_Num(DSI_ID_Type dsiId,uint32_t num)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_FRAME_NUM);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,DSI_CR_FRAME_NUM,num);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CR_FRAME_UPD);
    BL_WR_REG(DSIx,DSI_FRAME_NUM,tmpVal);

    tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CR_FRAME_UPD);
    BL_WR_REG(DSIx,DSI_FRAME_NUM,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI Reinit data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Reset(DSI_ID_Type dsiId)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_RESET_N);
    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);

    tmpVal=BL_SET_REG_BIT(tmpVal,DSI_RESET_N);
    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}
/****************************************************************************//**
 * @brief  DSI Reinit data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Reinit_Data_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL0_FORCERXMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL1_FORCERXMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL2_FORCERXMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL3_FORCERXMODE);
    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);

    if(lanes&DSI_LANE_DATA0){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL0_FORCERXMODE);
    }
    if(lanes&DSI_LANE_DATA1){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL1_FORCERXMODE);
    }
    if(lanes&DSI_LANE_DATA2){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL2_FORCERXMODE);
    }
    if(lanes&DSI_LANE_DATA3){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL3_FORCERXMODE);
    }

    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI enable lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Enable_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    if(lanes&DSI_LANE_DATA0){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL0_ENABLE);
    }
    if(lanes&DSI_LANE_DATA1){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL1_ENABLE);
    }
    if(lanes&DSI_LANE_DATA2){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL2_ENABLE);
    }
    if(lanes&DSI_LANE_DATA3){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL3_ENABLE);
    }
    if(lanes&DSI_LANE_CLOCK){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CL_ENABLE);
    }

    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI disable lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Disable_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    if(lanes&DSI_LANE_DATA0){
        tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL0_ENABLE);
    }
    if(lanes&DSI_LANE_DATA1){
        tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL1_ENABLE);
    }
    if(lanes&DSI_LANE_DATA2){
        tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL2_ENABLE);
    }
    if(lanes&DSI_LANE_DATA3){
        tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL3_ENABLE);
    }
    if(lanes&DSI_LANE_CLOCK){
        tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CL_ENABLE);
    }

    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI stop data lanes
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Stop_Data_Lanes(DSI_ID_Type dsiId,DSI_Lane_Type lanes)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL0_FORCETXSTOPMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL1_FORCETXSTOPMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL2_FORCETXSTOPMODE);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_DL3_FORCETXSTOPMODE);
    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);

    if(lanes&DSI_LANE_DATA0){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL0_FORCETXSTOPMODE);
    }
    if(lanes&DSI_LANE_DATA1){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL1_FORCETXSTOPMODE);
    }
    if(lanes&DSI_LANE_DATA2){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL2_FORCETXSTOPMODE);
    }
    if(lanes&DSI_LANE_DATA3){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_DL3_FORCETXSTOPMODE);
    }

    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}

/****************************************************************************//**
 * @brief  DSI get lanes state
 *
 * @param  dsiId: DSI ID type
 *
 * @param  lanes: lanes
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Get_Lanes_State(DSI_ID_Type dsiId,DSI_Lane_Type lane,DSI_Lane_State_Type *state)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    uint32_t stop_state_pos=0;
    uint32_t ulp_state_pos=0;
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    *state=DSI_LANE_STAT_NORMAL;

    if(lane==DSI_LANE_DATA0){
        stop_state_pos=DSI_DL0_STOPSTATE_POS;
        ulp_state_pos=DSI_DL0_ULPSACTIVENOT_POS;
    }else if(lane==DSI_LANE_DATA1){
        stop_state_pos=DSI_DL1_STOPSTATE_POS;
        ulp_state_pos=DSI_DL1_ULPSACTIVENOT_POS;
    }else if(lane==DSI_LANE_DATA2){
        stop_state_pos=DSI_DL2_STOPSTATE_POS;
        ulp_state_pos=DSI_DL2_ULPSACTIVENOT_POS;
    }else if(lane==DSI_LANE_DATA3){
        stop_state_pos=DSI_DL3_STOPSTATE_POS;
        ulp_state_pos=DSI_DL3_ULPSACTIVENOT_POS;
    }else if(lane==DSI_LANE_CLOCK){
        stop_state_pos=DSI_CL_STOPSTATE_POS;
        ulp_state_pos=DSI_CL_ULPSACTIVENOT_POS;
    }else{
        return; 
    }

    if(tmpVal&(1<<stop_state_pos)){
        *state|=DSI_LANE_STAT_STOP;
    }
    if(tmpVal&(1<<ulp_state_pos)){
        *state|=DSI_LANE_STAT_ULP;
    }
}

/****************************************************************************//**
 * @brief  Set clock lane operation
 *
 * @param  dsiId: DSI ID type
 *
 * @param  opt: operation type
 *
 * @return None
 *
*******************************************************************************/
void DSI_PHY_Set_Clock_Lane(DSI_ID_Type dsiId,DSI_Clock_Lane_Opt_Type opt)
{
    uint32_t tmpVal;
    uint32_t DSIx = dsiAddr[dsiId];
    
    /* Check the parameters */
    CHECK_PARAM(IS_DSI_ID_TYPE(dsiId));

    tmpVal=BL_RD_REG(DSIx,DSI_DPHY_CONFIG_0);

    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CL_TXULPSCLK);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CL_TXULPSEXIT);
    tmpVal=BL_CLR_REG_BIT(tmpVal,DSI_CL_TXREQUESTHS);
    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);

    if(opt&DSI_CLOCK_LANE_OPT_ULP_ENTER){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CL_TXULPSCLK);
    }
    if(opt&DSI_CLOCK_LANE_OPT_ULP_EXIT){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CL_TXULPSEXIT);
    }
    if(opt&DSI_CLOCK_LANE_OPT_HS_REQ){
        tmpVal=BL_SET_REG_BIT(tmpVal,DSI_CL_TXREQUESTHS);
    }

    BL_WR_REG(DSIx,DSI_DPHY_CONFIG_0,tmpVal);
}

/****************************************************************************/ /**
 * @brief  PWM interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void DSI_IRQHandler(void)
{
    DSI_IntHandler(DSI0_ID);
}
#endif

/*@} end of group DSI_Public_Functions */

/*@} end of group DSI */

/*@} end of group BL808_Peripheral_Driver */
