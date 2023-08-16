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

#include "bl808_pwm.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PWM
 *  @{
 */

/** @defgroup  PWM_Private_Macros
 *  @{
 */
#define PWM_Get_MC_Index(ch)    ((ch >> 4 && 0xF))
#define PWM_Get_CH_Index(ch)    (ch && 0xF)
#define PWM_INT_TIMEOUT_COUNT           (160*1000)
#define PWM_STOP_TIMEOUT_COUNT          (160*1000)

#define PWM_SET_MC_BITS_VAL(mc, val, bitname, bitval) \
    do { \
        if (mc == 0) \
            val = BL_SET_REG_BITS_VAL(val, PWM_MC0_##bitname, bitval); \
        else if (mc == 1) \
            val = BL_SET_REG_BITS_VAL(val, PWM_MC1_##bitname, bitval); \
    } while (0);

#define PWM_GET_MC_BITS_VAL(mc, val, bitname) \
    do { \
        if (mc == 0) \
            val = BL_GET_REG_BITS_VAL(val, PWM_MC0_##bitname); \
        else if (mc == 1) \
            val = BL_GET_REG_BITS_VAL(val, PWM_MC1_##bitname); \
    } while (0);

#define PWM_MC_RD_REG(mc, val, regname) \
    do { \
        if (mc == 0) \
            val = BL_RD_REG(PWM_BASE, PWM_MC0_##regname); \
        else if (mc == 1) \
            val = BL_RD_REG(PWM_BASE, PWM_MC1_##regname); \
    } while (0);

#define PWM_MC_WR_REG(mc, regname, val) \
    do { \
        if (mc == 0) \
            BL_WR_REG(PWM_BASE, PWM_MC0_##regname, val); \
        else if (mc == 1) \
            BL_WR_REG(PWM_BASE, PWM_MC1_##regname, val); \
    } while (0);

#define PWM_SET_CH_BITS_VAL(mc, ch, val, bitname, bitval) \
    do { \
        if (mc == 0) { \
            if (ch == 0) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC0_CH0_##bitname, bitval); \
            else if (ch == 1) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC0_CH1_##bitname, bitval); \
            else if (ch == 2) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC0_CH2_##bitname, bitval); \
            else if (ch == 3) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC0_CH3_##bitname, bitval); \
        } else if (mc == 1) { \
            if (ch == 0) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC1_CH0_##bitname, bitval); \
            else if (ch == 1) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC1_CH1_##bitname, bitval); \
            else if (ch == 2) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC1_CH2_##bitname, bitval); \
            else if (ch == 3) \
                val = BL_SET_REG_BITS_VAL(val, PWM_MC1_CH3_##bitname, bitval); \
        } \
    } while (0);

#define PWM_GET_CH_BITS_VAL(mc, ch, val, bitname) \
    do { \
        if (mc == 0) { \
            if (ch == 0) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC0_CH0_##bitname); \
            else if (ch == 1) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC0_CH1_##bitname); \
            else if (ch == 2) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC0_CH2_##bitname); \
            else if (ch == 3) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC0_CH3_##bitname); \
        } else if (mc == 1) { \
            if (ch == 0) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC1_CH0_##bitname); \
            else if (ch == 1) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC1_CH1_##bitname); \
            else if (ch == 2) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC1_CH2_##bitname); \
            else if (ch == 3) \
                val = BL_GET_REG_BITS_VAL(val, PWM_MC1_CH3_##bitname); \
        } \
    } while (0);

#define PWM_CH_RD_REG(mc, ch, val, regname) \
    do { \
        if (mc == 0) { \
            if (ch == 0) \
                val = BL_RD_REG(PWM_BASE, PWM_MC0_CH0_##regname); \
            else if (ch == 1) \
                val = BL_RD_REG(PWM_BASE, PWM_MC0_CH1_##regname); \
            else if (ch == 2) \
                val = BL_RD_REG(PWM_BASE, PWM_MC0_CH2_##regname); \
            else if (ch == 3) \
                val = BL_RD_REG(PWM_BASE, PWM_MC0_CH3_##regname); \
        } else if (mc == 1) { \
            if (ch == 0) \
                val = BL_RD_REG(PWM_BASE, PWM_MC1_CH0_##regname); \
            else if (ch == 1) \
                val = BL_RD_REG(PWM_BASE, PWM_MC1_CH1_##regname); \
            else if (ch == 2) \
                val = BL_RD_REG(PWM_BASE, PWM_MC1_CH2_##regname); \
            else if (ch == 3) \
                val = BL_RD_REG(PWM_BASE, PWM_MC1_CH3_##regname); \
        } \
    } while (0);

#define PWM_CH_WR_REG(mc, ch, regname, val) \
    do { \
        if (mc == 0) { \
            if (ch == 0) \
                BL_WR_REG(PWM_BASE, PWM_MC0_CH0_##regname, val); \
            else if (ch == 1) \
                BL_WR_REG(PWM_BASE, PWM_MC0_CH1_##regname, val); \
            else if (ch == 2) \
                BL_WR_REG(PWM_BASE, PWM_MC0_CH2_##regname, val); \
            else if (ch == 3) \
                BL_WR_REG(PWM_BASE, PWM_MC0_CH3_##regname, val); \
        } else if (mc == 1) { \
            if (ch == 0) \
                BL_WR_REG(PWM_BASE, PWM_MC1_CH0_##regname, val); \
            else if (ch == 1) \
                BL_WR_REG(PWM_BASE, PWM_MC1_CH1_##regname, val); \
            else if (ch == 2) \
                BL_WR_REG(PWM_BASE, PWM_MC1_CH2_##regname, val); \
            else if (ch == 3) \
                BL_WR_REG(PWM_BASE, PWM_MC1_CH3_##regname, val); \
        } \
    } while (0);


#define PWM_MC_IS_REG_BIT_SET(mc, val, bitname) \
    do { \
        if (mc == 0) \
            val = BL_IS_REG_BIT_SET(val, PWM_MC0_##bitname); \
        else if (mc == 1) \
            val = BL_IS_REG_BIT_SET(val, PWM_MC1_##bitname); \
    } while (0);

/*@} end of group PWM_Private_Macros */

/** @defgroup  PWM_Private_Types
 *  @{
 */

/*@} end of group PWM_Private_Types */

/** @defgroup  PWM_Private_Variables
 *  @{
 */

/*@} end of group PWM_Private_Variables */

/** @defgroup  PWM_Global_Variables
 *  @{
 */

/*@} end of group PWM_Global_Variables */

/** @defgroup  PWM_Public_Functions
 *  @{
 */
/****************************************************************************//**
 * @brief  Clear the PWM interrupt
 *
 * @param  ch: PWM channel number
 * @param  intType: Specifies the interrupt type
 *
 * @return None
 *
*******************************************************************************/
void PWM_Int_Clear(PWM_CH_ID_Type ch,PWM_INT_Type intType)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint8_t mc = PWM_Get_MC_Index(ch);
    uint8_t chn = PWM_Get_CH_Index(ch);


    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_PWM_INT_TYPE(intType));

    PWM_MC_RD_REG(mc, tmpVal, INT_CLEAR);

    switch(intType) {
        case PWM_INT_PULSE_CNT:
            PWM_SET_MC_BITS_VAL(mc, tmpVal, REPT_CLR, 1);
            PWM_MC_WR_REG(mc, INT_CLEAR, tmpVal);
            break;
        default:
            break;
    }
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
void PWM_Int_Mask(PWM_CH_ID_Type ch,PWM_INT_Type intType,BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    /* Get channel register */
    uint8_t mc = PWM_Get_MC_Index(ch);
    uint8_t chn = PWM_Get_CH_Index(ch);


    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));
    CHECK_PARAM(IS_PWM_INT_TYPE(intType));

    PWM_MC_RD_REG(mc, tmpVal, INT_MASK);

    switch(intType) {
        case PWM_INT_PULSE_CNT:
            if (intMask == UNMASK) {
                PWM_SET_MC_BITS_VAL(mc, tmpVal, REPT_MASK, 0);
            } else {
                PWM_SET_MC_BITS_VAL(mc, tmpVal, REPT_MASK, 1);
            }
            PWM_MC_WR_REG(mc, INT_MASK, tmpVal);
            break;
        default:
            break;
    }
}


/****************************************************************************//**
 * @brief  PWM channel init
 *
 * @param  chCfg: PWM configuration
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Init(PWM_CH_CFG_Type *chCfg)
{
    uint32_t tmpVal;
    /* Get channel register */

    uint8_t mc = PWM_Get_MC_Index(chCfg->ch);
    uint8_t ch = PWM_Get_CH_Index(chCfg->ch);
    
    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(chCfg->ch));
    CHECK_PARAM(IS_PWM_CH_COMP(chCfg->comp));
    CHECK_PARAM(IS_PWM_CLK_TYPE(chCfg->clk));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(chCfg->pol));
    CHECK_PARAM(IS_PWM_STOP_MODE_TYPE(chCfg->stopMode));

    /* Stop pwm first */
    PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
    PWM_MC_IS_REG_BIT_SET(mc, tmpVal, STS_STOP);
    if (!tmpVal) {
        PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
        PWM_SET_MC_BITS_VAL(mc, tmpVal, STOP_EN, 1);
        PWM_MC_WR_REG(mc, CONFIG0, tmpVal);
        uint32_t timeoutcnt = PWM_STOP_TIMEOUT_COUNT;
        while (timeoutcnt-- > 0) {        
            PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
            PWM_MC_IS_REG_BIT_SET(mc, tmpVal, STS_STOP);
            if (tmpVal)
                break;
        }
    }

    /* Config pwm clock src, clock div and stop mode */
    PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, REG_CLK_SEL, chCfg->clk);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, STOP_MODE, chCfg->stopMode);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, CLK_DIV, chCfg->clkDiv);
    PWM_MC_WR_REG(mc, CONFIG0, tmpVal);

    /* Todo: Config pwm polarity */
    PWM_MC_RD_REG(mc, tmpVal, CONFIG1);
    if (chCfg->comp == PWM_CH_COMP_POSITIVE) {
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, PPL, chCfg->pol);
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, PSI, chCfg->pol);
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, PEN, ENABLE);
    } else {
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, NPL, chCfg->pol);
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, NSI, chCfg->pol);
        PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, NEN, ENABLE);
    }
    PWM_MC_WR_REG(mc, CONFIG1, tmpVal);

    /* Config pwm period and duty */
    PWM_CH_RD_REG(mc, ch, tmpVal, THRE);
    PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, THREH, chCfg->threshold2);
    PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, THREL, chCfg->threshold1);
    PWM_CH_WR_REG(mc, ch, THRE, tmpVal);

    PWM_MC_RD_REG(mc, tmpVal, PERIOD);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, PERIOD, chCfg->period);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, INT_PERIOD_CNT, chCfg->intPulseCnt&0xFFFF);        
    PWM_MC_WR_REG(mc, PERIOD, tmpVal);

    /* Config interrupt pulse count */
    PWM_MC_RD_REG(mc, tmpVal, INT_EN);
    PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, H_EN, chCfg->intPulseCnt!=0?ENABLE:DISABLE);
    PWM_SET_CH_BITS_VAL(mc, ch, tmpVal, L_EN, chCfg->intPulseCnt!=0?ENABLE:DISABLE);
    PWM_MC_WR_REG(mc, INT_EN, tmpVal);

    PWM_Int_Mask(chCfg->ch, PWM_INT_PULSE_CNT,chCfg->intPulseCnt!=0?UNMASK:MASK);
    PWM_Int_Clear(chCfg->ch, PWM_INT_PULSE_CNT);
}

/****************************************************************************//**
 * @brief  PWM channel update source memory address and len
 *
 * @param  ch: PWM channel
 * @param  period: period
 * @param  threshold1: threshold1
 * @param  threshold2: threshold2
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Update(PWM_CH_ID_Type ch, uint16_t period, uint16_t threshold1,uint16_t threshold2)
{
    uint32_t tmpVal;
    uint8_t mc = PWM_Get_MC_Index(ch);
    uint8_t chn = PWM_Get_CH_Index(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));

    /* Config pwm period and duty */
    PWM_CH_RD_REG(mc, chn, tmpVal, THRE);
    PWM_SET_CH_BITS_VAL(mc, chn, tmpVal, THREH, threshold2);
    PWM_SET_CH_BITS_VAL(mc, chn, tmpVal, THREL, threshold1);
    PWM_CH_WR_REG(mc, chn, THRE, tmpVal);

    PWM_MC_RD_REG(mc, tmpVal, PERIOD);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, PERIOD, period);
    PWM_MC_WR_REG(mc, PERIOD, tmpVal);
}

/****************************************************************************//**
 * @brief  PWM get configuration
 *
 * @param  ch: PWM channel
 * @param  period: period pointer
 * @param  threshold1: threshold1 pointer
 * @param  threshold2: threshold2 pointer
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Get(PWM_CH_ID_Type ch,uint16_t *period,uint16_t *threshold1,uint16_t *threshold2)
{
    uint32_t tmpVal;
    uint8_t mc = PWM_Get_MC_Index(ch);
    uint8_t chn = PWM_Get_CH_Index(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));

    /* get pwm period and duty */
    PWM_CH_RD_REG(mc, chn, tmpVal, THRE);
    PWM_GET_CH_BITS_VAL(mc, chn, tmpVal, THREL);
    *threshold1 = tmpVal;
    PWM_GET_CH_BITS_VAL(mc, chn, tmpVal, THREH);
    *threshold2 = tmpVal;
    PWM_MC_RD_REG(mc, tmpVal, PERIOD);
    PWM_GET_MC_BITS_VAL(mc, tmpVal, PERIOD);
    *period = tmpVal;
}

/****************************************************************************//**
 * @brief  PWM enable
 *
 * @param  ch: PWM channel number
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Enable(PWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    uint8_t mc = PWM_Get_MC_Index(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));


    /* Config pwm clock to enable pwm */
    PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, STOP_EN, 0);
    PWM_MC_WR_REG(mc, CONFIG0, tmpVal)


}

/****************************************************************************//**
 * @brief  PWM disable
 *
 * @param  ch: PWM channel number
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Disable(PWM_CH_ID_Type ch)
{
    uint32_t tmpVal;
    uint8_t mc = PWM_Get_MC_Index(ch);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(ch));


    /* Config pwm clock to enable pwm */
    PWM_MC_RD_REG(mc, tmpVal, CONFIG0);
    PWM_SET_MC_BITS_VAL(mc, tmpVal, STOP_EN, 1);
    PWM_MC_WR_REG(mc, CONFIG0, tmpVal)
}

/****************************************************************************//**
 * @brief  PWM channel force output high
 *
 * @param  ch: PWM channel number
 *
 * @return None
 *
*******************************************************************************/
void PWM_Channel_Fource_Output(PWM_CH_ID_Type ch)
{

}

/*@} end of group PWM_Public_Functions */

/*@} end of group PWM */

/*@} end of group BL60x_Peripheral_Driver */
