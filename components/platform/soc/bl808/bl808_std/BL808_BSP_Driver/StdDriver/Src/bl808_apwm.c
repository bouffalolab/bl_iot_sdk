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

#include "bl808_apwm.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  APWM
 *  @{
 */

/** @defgroup  APWM_Private_Macros
 *  @{
 */
#define APWM_Get_Channel_Reg(ch) (APWM_BASE + APWM_CHANNEL_OFFSET + (ch)*0x30)
#define APWM_INT_TIMEOUT_COUNT           (160*1000)
#define APWM_STOP_TIMEOUT_COUNT          (160*1000)



/*@} end of group APWM_Private_Macros */

/** @defgroup  APWM_Private_Types
 *  @{
 */

/*@} end of group APWM_Private_Types */

/** @defgroup  APWM_Private_Variables
 *  @{
 */

/**
 *  @brief APWM interrupt callback function address array
*/
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *APWMIntCbfArra[APWM_CH_MAX][APWM_INT_ALL] = {
    {NULL}};
#endif
/*@} end of group APWM_Private_Variables */

/** @defgroup  APWM_Global_Variables
 *  @{
 */

/*@} end of group APWM_Global_Variables */

/** @defgroup  APWM_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type APWM_IntHandler(IRQn_Type intPeriph);
#endif

/*@} end of group APWM_Private_Fun_Declaration */

/** @defgroup  APWM_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  APWM interrupt handle
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type APWM_IntHandler(IRQn_Type intPeriph)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint16_t chIndex, intIndex;
    uint32_t APWMx;
    for (chIndex = APWM_CH0; chIndex < APWM_CH_MAX; chIndex++)
    {
        APWMx = APWM_Get_Channel_Reg(chIndex);
        tmpVal = BL_RD_REG(APWMx, APWM_INT_STS);
        maskVal = BL_RD_REG(APWMx, APWM_INT_MASK);
        for (intIndex = 0; intIndex < APWM_INT_ALL; intIndex++)
        {
            if (((1 << intIndex) & tmpVal) && (((1 << intIndex) & maskVal) == 0))
            {
                BL_WR_REG(APWMx, APWM_INT_CLEAR, 1 << intIndex);
                if (APWMIntCbfArra[chIndex][intIndex] != NULL)
                {
                    APWMIntCbfArra[chIndex][intIndex]();
                }
            }
        }
    }
    return SUCCESS;
}

#endif

/*@} end of group APWM_Private_Functions */

/** @defgroup  APWM_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  PWM channel init
 *
 * @param  chCfg: PWM configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type APWM_Channel_Init(APWM_CH_CFG_Type *chCfg)
{
    uint32_t tmpVal;
    uint32_t timeoutCnt = APWM_STOP_TIMEOUT_COUNT;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(chCfg->ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(chCfg->ch));
    CHECK_PARAM(IS_APWM_CLK_TYPE(chCfg->clk));
    CHECK_PARAM(IS_APWM_STOP_MODE_TYPE(chCfg->stopMode));
    CHECK_PARAM(IS_APWM_EXT_BREAK_POLARITY_TYPE(chCfg->extPol));
    CHECK_PARAM(IS_APWM_TRIGADC_SOURCE_TYPE(chCfg->adcSrc));

    /* Config apwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    BL_WR_REG(APWMx, APWM_CONFIG0, BL_SET_REG_BIT(tmpVal, APWM_STOP_EN));
    while(!BL_IS_REG_BIT_SET(BL_RD_REG(APWMx, APWM_CONFIG0), APWM_STS_STOP)){
        timeoutCnt--;
        if(timeoutCnt == 0){
            return TIMEOUT;
        }
    }
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_REG_CLK_SEL, chCfg->clk);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_STOP_MODE, chCfg->stopMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_EXT_BREAK_PL, chCfg->extPol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_ADC_TRG_SRC, chCfg->adcSrc);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_STOP_ON_REPT, chCfg->stpRept);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CLK_DIV, chCfg->clkDiv);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);

    /* Config apwm period and rept count */
    tmpVal = BL_RD_REG(APWMx, APWM_PERIOD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_PERIOD, chCfg->period);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_INT_PERIOD_CNT, chCfg->intPulseCnt);
    BL_WR_REG(APWMx, APWM_PERIOD, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(APWM_IRQn, APWM_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  PWM channel update clock divider
 *
 * @param  ch: PWM channel
 * @param  div: Clock divider
 *
 * @return None
 *
*******************************************************************************/
void APWM_Channel_Set_Div(APWM_CH_ID_Type ch,uint16_t div)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CLK_DIV, div);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}

/****************************************************************************//**
 * @brief  PWM channel update period
 *
 * @param  ch: PWM channel
 * @param  period: period
 *
 * @return None
 *
*******************************************************************************/
void APWM_Channel_Set_Period(APWM_CH_ID_Type ch,uint16_t period)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm period and duty */
    tmpVal = BL_RD_REG(APWMx, APWM_PERIOD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_PERIOD, period);
    BL_WR_REG(APWMx, APWM_PERIOD, tmpVal);
}

/****************************************************************************//**
 * @brief  PWM get configuration
 *
 * @param  ch: PWM channel
 * @param  period: period pointer
 *
 * @return None
 *
*******************************************************************************/
void APWM_Channel_Get_Period(APWM_CH_ID_Type ch,uint16_t *period)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* get pwm period */
    tmpVal = BL_RD_REG(APWMx, APWM_PERIOD);
    *period = BL_GET_REG_BITS_VAL(tmpVal, APWM_PERIOD);
}

/****************************************************************************//**
 * @brief  PWM enable
 *
 * @param  ch: PWM channel number
 *
 * @return None
 *
*******************************************************************************/
void APWM_Channel_Enable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm clock to enable pwm */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    BL_WR_REG(APWMx, APWM_CONFIG0, BL_CLR_REG_BIT(tmpVal, APWM_STOP_EN));
}

/****************************************************************************//**
 * @brief  PWM disable
 *
 * @param  ch: PWM channel number
 *
 * @return None
 *
*******************************************************************************/
void APWM_Channel_Disable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm clock to disable pwm */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    BL_WR_REG(APWMx, APWM_CONFIG0, BL_SET_REG_BIT(tmpVal, APWM_STOP_EN));  
}

void APWM_CC_Channel_Init(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_CC_CH_CFG_Type *ccCfg)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_MODE_TYPE(ccCfg->modP));
    CHECK_PARAM(IS_APWM_MODE_TYPE(ccCfg->modN));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(ccCfg->polP));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(ccCfg->polN));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(ccCfg->idlP));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(ccCfg->idlN));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(ccCfg->brkP));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(ccCfg->brkN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PEN, ccCfg->modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NEN, ccCfg->modN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PPL, ccCfg->polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NPL, ccCfg->polN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PSI, ccCfg->idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NSI, ccCfg->idlN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PBS, ccCfg->brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NBS, ccCfg->brkN);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PEN, ccCfg->modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NEN, ccCfg->modN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PPL, ccCfg->polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NPL, ccCfg->polN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PSI, ccCfg->idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NSI, ccCfg->idlN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PBS, ccCfg->brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NBS, ccCfg->brkN);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PEN, ccCfg->modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NEN, ccCfg->modN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PPL, ccCfg->polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NPL, ccCfg->polN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PSI, ccCfg->idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NSI, ccCfg->idlN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PBS, ccCfg->brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NBS, ccCfg->brkN);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PEN, ccCfg->modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NEN, ccCfg->modN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PPL, ccCfg->polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NPL, ccCfg->polN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PSI, ccCfg->idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NSI, ccCfg->idlN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PBS, ccCfg->brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NBS, ccCfg->brkN);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);

    /* Config apwm thresholdL and thresholdH */
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_RD_REG(APWMx, APWM_CH0_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREL, ccCfg->thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREH, ccCfg->thresholdH);
        BL_WR_REG(APWMx, APWM_CH0_THRE, tmpVal);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_RD_REG(APWMx, APWM_CH1_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREL, ccCfg->thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREH, ccCfg->thresholdH);
        BL_WR_REG(APWMx, APWM_CH1_THRE, tmpVal);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_RD_REG(APWMx, APWM_CH2_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREL, ccCfg->thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREH, ccCfg->thresholdH);
        BL_WR_REG(APWMx, APWM_CH2_THRE, tmpVal);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_RD_REG(APWMx, APWM_CH3_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREL, ccCfg->thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREH, ccCfg->thresholdH);
        BL_WR_REG(APWMx, APWM_CH3_THRE, tmpVal);
        break;
    default:
        break;
    }

    /* Config pwm dead time */
    tmpVal = BL_RD_REG(APWMx, APWM_DEAD_TIME);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_DTG, ccCfg->dtg);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_DTG, ccCfg->dtg);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_DTG, ccCfg->dtg);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_DTG, ccCfg->dtg);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_DEAD_TIME, tmpVal);
}

void APWM_CC_Channel_Set_Threshold(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdL, uint16_t thresholdH)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));

    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_RD_REG(APWMx, APWM_CH0_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREL, thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH0_THRE, tmpVal);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_RD_REG(APWMx, APWM_CH1_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREL, thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH1_THRE, tmpVal);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_RD_REG(APWMx, APWM_CH2_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREL, thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH2_THRE, tmpVal);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_RD_REG(APWMx, APWM_CH3_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREL, thresholdL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH3_THRE, tmpVal);
        break;
    default:
        break;
    }
}

void APWM_CC_Channel_Set_ThresholdL(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdL)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));

    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_RD_REG(APWMx, APWM_CH0_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREL, thresholdL);
        BL_WR_REG(APWMx, APWM_CH0_THRE, tmpVal);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_RD_REG(APWMx, APWM_CH1_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREL, thresholdL);
        BL_WR_REG(APWMx, APWM_CH1_THRE, tmpVal);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_RD_REG(APWMx, APWM_CH2_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREL, thresholdL);
        BL_WR_REG(APWMx, APWM_CH2_THRE, tmpVal);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_RD_REG(APWMx, APWM_CH3_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREL, thresholdL);
        BL_WR_REG(APWMx, APWM_CH3_THRE, tmpVal);
        break;
    default:
        break;
    }
}
void APWM_CC_Channel_Set_ThresholdH(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdH)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));

    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_RD_REG(APWMx, APWM_CH0_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH0_THRE, tmpVal);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_RD_REG(APWMx, APWM_CH1_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH1_THRE, tmpVal);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_RD_REG(APWMx, APWM_CH2_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH2_THRE, tmpVal);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_RD_REG(APWMx, APWM_CH3_THRE);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_THREH, thresholdH);
        BL_WR_REG(APWMx, APWM_CH3_THRE, tmpVal);
        break;
    default:
        break;
    }
}
void APWM_CC_Channel_Get_Threshold(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t *thresholdL, uint16_t *thresholdH)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));

    /* get pwm thresholdL and thresholdH */
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_RD_REG(APWMx, APWM_CH0_THRE);
        *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH0_THREL);
        *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH0_THREH);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_RD_REG(APWMx, APWM_CH1_THRE);
        *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH1_THREL);
        *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH1_THREH);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_RD_REG(APWMx, APWM_CH2_THRE);
        *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH2_THREL);
        *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH2_THREH);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_RD_REG(APWMx, APWM_CH3_THRE);
        *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH3_THREL);
        *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, APWM_CH3_THREH);
        break;
    default:
        break;
    }
}

void APWM_CC_Channel_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type modP, APWM_Mode_Type modN)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_MODE_TYPE(modP));
    CHECK_PARAM(IS_APWM_MODE_TYPE(modN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PEN, modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NEN, modN);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PEN, modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NEN, modN);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PEN, modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NEN, modN);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PEN, modP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NEN, modN);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelP_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_MODE_TYPE(mod));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PEN, mod);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PEN, mod);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PEN, mod);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PEN, mod);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelN_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_MODE_TYPE(mod));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NEN, mod);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NEN, mod);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NEN, mod);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NEN, mod);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}

void APWM_CC_Channel_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type polP, APWM_Polarity_Type polN)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(polP));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(polN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PPL, polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NPL, polN);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PPL, polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NPL, polN);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PPL, polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NPL, polN);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PPL, polP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NPL, polN);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelP_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(pol));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PPL, pol);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PPL, pol);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PPL, pol);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PPL, pol);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelN_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_POLARITY_TYPE(pol));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NPL, pol);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NPL, pol);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NPL, pol);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NPL, pol);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_Channel_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idlP, APWM_Idle_State_Type idlN)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(idlP));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(idlN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PSI, idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NSI, idlN);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PSI, idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NSI, idlN);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PSI, idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NSI, idlN);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PSI, idlP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NSI, idlN);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelP_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idl)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(idl));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PSI, idl);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PSI, idl);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PSI, idl);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PSI, idl);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelN_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idl)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_IDLE_STATE_TYPE(idl));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NSI, idl);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NSI, idl);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NSI, idl);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NSI, idl);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}

void APWM_CC_Channel_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brkP, APWM_Break_State_Type brkN)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(brkP));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(brkN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PBS, brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NBS, brkN);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PBS, brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NBS, brkN);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PBS, brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NBS, brkN);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PBS, brkP);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NBS, brkN);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelP_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brk)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(brk));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_PBS, brk);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_PBS, brk);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_PBS, brk);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_PBS, brk);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}
void APWM_CC_ChannelN_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brk)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));
    CHECK_PARAM(IS_APWM_BREAK_STATE_TYPE(brk));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG1);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_NBS, brk);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_NBS, brk);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_NBS, brk);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_NBS, brk);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_CONFIG1, tmpVal);
}

void APWM_CC_Channel_Update_Config1(APWM_CH_ID_Type ch, uint32_t cfg)
{
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm config1 */
    BL_WR_REG(APWMx, APWM_CONFIG1, cfg);
}
void APWM_CC_Channel_Get_Config1(APWM_CH_ID_Type ch, uint32_t *cfg)
{
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Get pwm config1 value */
    *cfg = BL_RD_REG(APWMx, APWM_CONFIG1);
}
void APWM_CC_Channel_Set_Dtg(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint8_t dtg)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_CC_CH_ID_TYPE(cc));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(APWMx, APWM_DEAD_TIME);
    switch (cc)
    {
    case APWM_CC_CH0:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH0_DTG, dtg);
        break;
    case APWM_CC_CH1:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH1_DTG, dtg);
        break;
    case APWM_CC_CH2:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH2_DTG, dtg);
        break;
    case APWM_CC_CH3:
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_CH3_DTG, dtg);
        break;
    default:
        break;
    }
    BL_WR_REG(APWMx, APWM_DEAD_TIME, tmpVal);
}
void APWM_SW_Break_Enable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, APWM_SW_BREAK_EN);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}
void APWM_SW_Break_Disable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, APWM_SW_BREAK_EN);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}
void APWM_EXT_Break_Enable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, APWM_EXT_BREAK_EN);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}
void APWM_EXT_Break_Disable(APWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, APWM_EXT_BREAK_EN);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}
void APWM_EXT_Break_Set_Polarity(APWM_CH_ID_Type ch, APWM_EXT_Break_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_EXT_BREAK_POLARITY_TYPE(pol));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_EXT_BREAK_PL, pol);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}

void APWM_Set_TrigADC_Source(APWM_CH_ID_Type ch, APWM_TrigADC_Source_Type src)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_TRIGADC_SOURCE_TYPE(src));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(APWMx, APWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, APWM_ADC_TRG_SRC, src);
    BL_WR_REG(APWMx, APWM_CONFIG0, tmpVal);
}

/****************************************************************************//**
 * @brief  Mask/Unmask the PWM interrupt
 *
 * @param  ch: PWM channel number
 * @param  intType: Specifies the interrupt type
 * @param  intMask: Enable/Disable Specified interrupt type
 *
 * @return None
 *
*******************************************************************************/
void APWM_Int_Mask(APWM_CH_ID_Type ch,APWM_INT_Type intType,BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(APWMx, APWM_INT_MASK);
    if(intType == APWM_INT_ALL){
        if(intMask == UNMASK){
            tmpVal &= ~((1U << APWM_INT_ALL) - 1);
        }
        else{
            tmpVal |= ((1U << APWM_INT_ALL) - 1);
        }
    }
    else{
        if (intMask == UNMASK)
        {
            tmpVal &= ~(1U << intType);
        }
        else
        {
            tmpVal |= (1U << intType);
        }
    }
    BL_WR_REG(APWMx, APWM_INT_MASK, tmpVal);
}

void APWM_Int_Clear(APWM_CH_ID_Type ch, APWM_INT_Type intType)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(APWMx, APWM_INT_CLEAR);

    if (intType == APWM_INT_ALL)
    {
        tmpVal = ((1U << APWM_INT_ALL) - 1);
    }
    else
    {
        tmpVal = (1U << intType);
    }
    BL_WR_REG(APWMx, APWM_INT_CLEAR, tmpVal);
}

BL_Sts_Type APWM_Get_Int_Status(APWM_CH_ID_Type ch, APWM_INT_Type intType)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint32_t APWMx = APWM_Get_Channel_Reg(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_APWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_APWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(APWMx, APWM_INT_STS);

    if (intType == APWM_INT_ALL)
    {
        if(tmpVal & ((1<<APWM_CC_CH_MAX)-1))
        {
            return SET;
        }
        else
        {
            return RESET;
        }
    }
    else
    {
        if (tmpVal & (1 << intType))
        {
            return SET;
        }
        else
        {
            return RESET;
        }
    }
}

/****************************************************************************//**
 * @brief  Install PWM interrupt callback function
 *
 * @param  ch: PWM channel number
 * @param  intType: PWM interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void APWM_Int_Callback_Install(APWM_CH_ID_Type ch, uint32_t intType, intCallback_Type *cbFun)
{
    APWMIntCbfArra[ch][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  PWM interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void APWM_IRQHandler(void)
{
    APWM_IntHandler(APWM_IRQn);
}
#endif

/*@} end of group APWM_Public_Functions */

/*@} end of group APWM */

/*@} end of group BL808_Peripheral_Driver */
