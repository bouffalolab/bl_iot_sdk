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
#ifndef __BL808_PWM_H__
#define __BL808_PWM_H__

#include "pwm_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PWM
 *  @{
 */

/** @defgroup  PWM_Public_Types
 *  @{
 */

/**
 *  @brief PWM No. type definition
 */
typedef enum {
    PWM_MC0_CH0 = 0x00,                             /*!< PWM MC0 Channel 0 define */
    PWM_MC0_CH1 = 0x01,                             /*!< PWM MC0 Channel 1 define */
    PWM_MC0_CH2 = 0x02,                             /*!< PWM MC0 Channel 2 define */
    PWM_MC0_CH3 = 0x03,                             /*!< PWM MC0 Channel 3 define */
    PWM_MC0_MAX = 0x04,                             /*!<  */
    PWM_MC1_CH0 = 0x10,                             /*!< PWM MC1 Channel 0 define */
    PWM_MC1_CH1 = 0x11,                             /*!< PWM MC1 Channel 1 define */
    PWM_MC1_CH2 = 0x12,                             /*!< PWM MC1 Channel 2 define */
    PWM_MC1_CH3 = 0x13,                             /*!< PWM MC1 Channel 3 define */
    PWM_MC1_MAX = 0x14,                             /*!<  */
}PWM_CH_ID_Type;

/**
 *  @brief PWM MC. type definition
 */
typedef enum {
    PWM_MC0 = 0,                             /*!< PWM MC 0 define */
    PWM_MC1,                                 /*!< PWM MC 1 define */
    PWM_MC_MAX,                              /*!<  */
}PWM_MC_Type;

/**
 *  @brief PWM MC. type definition
 */
typedef enum {
    PWM_CH_COMP_POSITIVE = 0,                   /*!< PWM Channel complementary positive define */
    PWM_CH_COMP_NEGATIVE,                       /*!< PWM Channel complementary negative define */
    PWM_CH_COMP_MAX,                            /*!<  */
}PWM_CH_COMP_Type;

/**
 *  @brief PWM Clock definition
 */
typedef enum {
    PWM_CLK_XTAL = 0,                        /*!< PWM Clock source :XTAL CLK */
    PWM_CLK_BCLK,                            /*!< PWM Clock source :Bus CLK */
    PWM_CLK_32K,                             /*!< PWM Clock source :32K CLK */
    PWM_CLK_MAX,                             /*!<  */
}PWM_Clk_Type;

/**
 *  @brief PWM Stop Mode definition
 */
typedef enum {
    PWM_STOP_ABRUPT = 0,                     /*!< PWM stop abrupt select define */
    PWM_STOP_GRACEFUL,                       /*!< PWM stop graceful select define */
    PWM_STOP_MAX,                            /*!<  */
}PWM_Stop_Mode_Type;

/**
 *  @brief PWM mode type def
 */
typedef enum {
    PWM_POL_NORMAL = 0,                      /*!< PWM normal polarity mode define */
    PWM_POL_INVERT,                         /*!< PWM invert polarity mode define */
    PWM_POL_MAX,                          /*!<  */
}PWM_Polarity_Type;

/**
 *  @brief PWM interrupt type def
 */
typedef enum {
    PWM_INT_PULSE_CNT = 0,                   /*!< PWM Pulse count interrupt define */
    PWM_INT_ALL,                             /*!<  */
}PWM_INT_Type;

/**
 *  @brief PWM configuration structure type definition
 */
typedef struct {
    PWM_CH_ID_Type ch;                       /*!< PWM channel */
    PWM_CH_COMP_Type comp;                   /*!< PWM channel complementary */
    PWM_Clk_Type clk;                        /*!< PWM Clock */
    PWM_Stop_Mode_Type stopMode;             /*!< PWM Stop Mode */
    PWM_Polarity_Type pol;                   /*!< PWM mode type */
    uint16_t clkDiv;                         /*!< PWM clkDiv num */
    uint16_t period;                         /*!< PWM period set */
    uint16_t threshold1;                     /*!< PWM threshold1 num */
    uint16_t threshold2;                     /*!< PWM threshold2 num */
    uint16_t intPulseCnt;                    /*!< PWM interrupt pulse count */
}PWM_CH_CFG_Type;

/*@} end of group PWM_Public_Types */

/** @defgroup  PWM_Public_Constants
 *  @{
 */

/** @defgroup  PWM_MC_ID_TYPE
 *  @{
 */
#define IS_PWM_CH_ID_TYPE(type)                          ((type >= PWM_MC0_CH0 && type < PWM_MC0_MAX) \
                                                           || (type >= PWM_MC1_CH0  || type < PWM_MC1_MAX))

/** @defgroup  IS_PWM_CH_COMP
 *  @{
 */
#define IS_PWM_CH_COMP(type)                             (type >= 0 && type < PWM_CH_COMP_MAX)

/** @defgroup  PWM_CLK_TYPE
 *  @{
 */
#define IS_PWM_CLK_TYPE(type)                            (type >= 0 && type < PWM_CLK_MAX)

/** @defgroup  PWM_STOP_MODE_TYPE
 *  @{
 */
#define IS_PWM_STOP_MODE_TYPE(type)                      (type >= 0 && type < PWM_STOP_MAX )

/** @defgroup  PWM_POLARITY_TYPE
 *  @{
 */
#define IS_PWM_POLARITY_TYPE(type)                       (type >= 0 && type < PWM_POL_MAX )

/** @defgroup  PWM_INT_TYPE
 *  @{
 */
#define IS_PWM_INT_TYPE(type)                            (type >= 0 && type <= PWM_INT_ALL )

/*@} end of group PWM_Public_Constants */

/** @defgroup  PWM_Public_Macros
 *  @{
 */
#define IS_PWM_CH(CH)               ((CH) < PWM_CH_MAX)

/*@} end of group PWM_Public_Macros */

/** @defgroup  PWM_Public_Functions
 *  @{
 */

/**
 *  @brief PWM Functions
 */
void PWM_Channel_Init(PWM_CH_CFG_Type *chCfg);
void PWM_Channel_Update(PWM_CH_ID_Type ch, uint16_t period, uint16_t threshold1, uint16_t threshold2);
void PWM_IntMask(PWM_CH_ID_Type ch,PWM_INT_Type intType, BL_Mask_Type intMask);
void PWM_Channel_Enable(PWM_CH_ID_Type ch);
void PWM_Channel_Disable(PWM_CH_ID_Type ch);
void PWM_Channel_Get(PWM_CH_ID_Type ch,uint16_t *period,uint16_t *threshold1,uint16_t *threshold2);


/*@} end of group PWM_Public_Functions */

/*@} end of group PWM */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_PWM_H__ */
