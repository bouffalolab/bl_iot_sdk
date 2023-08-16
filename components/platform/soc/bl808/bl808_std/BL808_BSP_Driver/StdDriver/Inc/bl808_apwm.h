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
#ifndef __BL808_APWM_H__
#define __BL808_APWM_H__

#include "apwm_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  APWM
 *  @{
 */
#define APWM_IRQn PWM_IRQn
/** @defgroup  APWM_Public_Types
 *  @{
 */

/**
 *  @brief APWM No. type definition
 */
typedef enum {
    APWM_CH0 = 0,                            /*!< APWM Channel 0 define */
    APWM_CH_MAX,                             /*!<  */
}APWM_CH_ID_Type;

/**
 *  @brief APWM Clock definition
 */
typedef enum {
    APWM_CLK_XCLK = 0,                       /*!< APWM Clock source :XTAL CLK */
    APWM_CLK_BCLK,                           /*!< APWM Clock source :Bus CLK */
    APWM_CLK_32K,                            /*!< APWM Clock source :32K CLK */
}APWM_Clk_Type;

/**
 *  @brief APWM Stop Mode definition
 */
typedef enum {
    APWM_STOP_ABRUPT = 0,                    /*!< APWM stop abrupt select define */
    APWM_STOP_GRACEFUL,                      /*!< APWM stop graceful select define */
}APWM_Stop_Mode_Type;

/**
 *  @brief APWM mode type def
 */
typedef enum {
    APWM_POL_ACTIVE_LOW = 0,                 /*!< APWM active low polarity mode define */
    APWM_POL_ACTIVE_HIGH,                    /*!< APWM active high polarity mode define */
}APWM_Polarity_Type;

/**
 *  @brief APWM interrupt type def
 */
typedef enum {
    APWM_INT_CH0L = 0,                       /*!< APWM CC Channel 0L interrupt define */
    APWM_INT_CH0H,                           /*!< APWM CC Channel 0H interrupt define */
    APWM_INT_CH1L,                           /*!< APWM CC Channel 1H interrupt define */
    APWM_INT_CH1H,                           /*!< APWM CC Channel 1H interrupt define */
    APWM_INT_CH2L,                           /*!< APWM CC Channel 2H interrupt define */
    APWM_INT_CH2H,                           /*!< APWM CC Channel 2H interrupt define */
    APWM_INT_CH3L,                           /*!< APWM CC Channel 3H interrupt define */
    APWM_INT_CH3H,                           /*!< APWM CC Channel 3H interrupt define */
    APWM_INT_PRDE,                           /*!< APWM Period end interrupt define */
    APWM_INT_BRK,                            /*!< APWM break interrupt define */
    APWM_INT_REPT,                           /*!< APWM repeat interrupt define */
    APWM_INT_ALL,                            /*!<  */
}APWM_INT_Type;

/**
 *  @brief APWM CC No. type definition
 */
typedef enum {
    APWM_CC_CH0 = 0,                         /*!< APWM CC Channel 0 define */
    APWM_CC_CH1,                             /*!< APWM CC Channel 1 define */
    APWM_CC_CH2,                             /*!< APWM CC Channel 2 define */
    APWM_CC_CH3,                             /*!< APWM CC Channel 3 define */
    APWM_CC_CH_MAX,                          /*!<  */
}APWM_CC_CH_ID_Type;

/**
 *  @brief APWM Mode type definition
 */
typedef enum {
    APWM_MODE_DISABLE = 0,                   /*!< APWM Mode Disable define */
    APWM_MODE_ENABLE,                        /*!< APWM Mode Enable define */
}APWM_Mode_Type;

/**
 *  @brief APWM Idel State type definition
 */
typedef enum {
    APWM_IDLE_STATE_INACTIVE = 0,            /*!< APWM Idle State Inactive define */
    APWM_IDLE_STATE_ACTIVE,                  /*!< APWM Idle State Active define */
}APWM_Idle_State_Type;

/**
 *  @brief APWM break State type definition
 */
typedef enum {
    APWM_BREAK_STATE_INACTIVE = 0,           /*!< APWM Break State Inactive define */
    APWM_BREAK_STATE_ACTIVE,                 /*!< APWM Break State Active define */
}APWM_Break_State_Type;

/**
 *  @brief APWM EXT break Polarity Level type definition
 */
typedef enum {
    APWM_BREAK_Polarity_LOW = 0,             /*!< APWM EXT Break Polarity Low Level define */
    APWM_BREAK_Polarity_HIGH,                /*!< APWM EXT Break Polarity High Level define */
}APWM_EXT_Break_Polarity_Type;

/**
 *  @brief APWM Trig ADC Source type definition
 */
typedef enum {
    APWM_TRIGADC_SOURCE_0L = 0,              /*!< APWM CC Channel 0 Threshold L Trig ADC Source define */
    APWM_TRIGADC_SOURCE_0H,                  /*!< APWM CC Channel 0 Threshold H Trig ADC Source define */
    APWM_TRIGADC_SOURCE_1L,                  /*!< APWM CC Channel 1 Threshold L Trig ADC Source define */
    APWM_TRIGADC_SOURCE_1H,                  /*!< APWM CC Channel 1 Threshold H Trig ADC Source define */
    APWM_TRIGADC_SOURCE_2L,                  /*!< APWM CC Channel 2 Threshold L Trig ADC Source define */
    APWM_TRIGADC_SOURCE_2H,                  /*!< APWM CC Channel 2 Threshold H Trig ADC Source define */
    APWM_TRIGADC_SOURCE_3L,                  /*!< APWM CC Channel 3 Threshold L Trig ADC Source define */
    APWM_TRIGADC_SOURCE_3H,                  /*!< APWM CC Channel 3 Threshold H Trig ADC Source define */
    APWM_TRIGADC_SOURCE_PRDE,                /*!< APWM Period End Reached Trig ADC Source define */
    APWM_TRIGADC_SOURCE_NONE = 0xF,          /*!< APWM None Trig ADC Source define */
}APWM_TrigADC_Source_Type;

/**
 *  @brief APWM configuration structure type definition
 */
typedef struct {
    APWM_CH_ID_Type ch;                      /*!< APWM channel */
    APWM_Clk_Type clk;                       /*!< APWM Clock */
    APWM_Stop_Mode_Type stopMode;            /*!< APWM Stop Mode */
    APWM_EXT_Break_Polarity_Type extPol;     /*!< APWM EXT_Break Polarity */
    APWM_TrigADC_Source_Type adcSrc;         /*!< APWM TrigADC Source */
    BL_Fun_Type stpRept;                     /*!< APWM Stop On Rept */
    uint16_t clkDiv;                         /*!< APWM clkDiv num */
    uint16_t period;                         /*!< APWM period set */
    uint16_t intPulseCnt;                    /*!< APWM interrupt pulse count */
}APWM_CH_CFG_Type;

/**
 *  @brief APWM CC configuration structure type definition
 */
typedef struct {
    APWM_CC_CH_ID_Type cc;                   /*!< APWM CC channel ID */
    APWM_Mode_Type modP;                     /*!< APWM CC Channel P PWM mode type */
    APWM_Mode_Type modN;                     /*!< APWM CC Channel N PWM mode type */
    APWM_Polarity_Type polP;                 /*!< APWM CC Channel P polarity type */
    APWM_Polarity_Type polN;                 /*!< APWM CC Channel N polarity type */
    APWM_Idle_State_Type idlP;               /*!< APWM CC Channel P idle state type */
    APWM_Idle_State_Type idlN;               /*!< APWM CC Channel N idle state type */
    APWM_Break_State_Type brkP;              /*!< APWM CC Channel P break state type */
    APWM_Break_State_Type brkN;              /*!< APWM CC Channel N break state type */
    uint16_t thresholdL;                     /*!< APWM thresholdL num */
    uint16_t thresholdH;                     /*!< APWM thresholdH num */
    uint8_t dtg;                             /*!< APWM CC Channel deadtime generator */
}APWM_CC_CH_CFG_Type;

/*@} end of group APWM_Public_Types */

/** @defgroup  APWM_Public_Constants
 *  @{
 */

/** @defgroup  APWM_CH_ID_TYPE
 *  @{
 */
#define IS_APWM_CH_ID_TYPE(type)                         (((type) == APWM_CH0 ) || \
                                                          ((type) == APWM_CH_MAX))

/** @defgroup  APWM_CLK_TYPE
 *  @{
 */
#define IS_APWM_CLK_TYPE(type)                           (((type) == APWM_CLK_XCLK ) || \
                                                          ((type) == APWM_CLK_BCLK) || \
                                                          ((type) == APWM_CLK_32K))

/** @defgroup  APWM_STOP_MODE_TYPE
 *  @{
 */
#define IS_APWM_STOP_MODE_TYPE(type)                     (((type) == APWM_STOP_ABRUPT ) || \
                                                          ((type) == APWM_STOP_GRACEFUL))

/** @defgroup  APWM_POLARITY_TYPE
 *  @{
 */
#define IS_APWM_POLARITY_TYPE(type)                      (((type) == APWM_POL_ACTIVE_LOW ) || \
                                                          ((type) == APWM_POL_ACTIVE_HIGH))

/** @defgroup  APWM_INT_TYPE
 *  @{
 */
#define IS_APWM_INT_TYPE(type)                           (((type) == APWM_INT_CH0L ) || \
                                                          ((type) == APWM_INT_CH0H) || \
                                                          ((type) == APWM_INT_CH1L) || \
                                                          ((type) == APWM_INT_CH1H) || \
                                                          ((type) == APWM_INT_CH2L) || \
                                                          ((type) == APWM_INT_CH2H) || \
                                                          ((type) == APWM_INT_CH3L) || \
                                                          ((type) == APWM_INT_CH3H) || \
                                                          ((type) == APWM_INT_PRDE) || \
                                                          ((type) == APWM_INT_BRK) || \
                                                          ((type) == APWM_INT_REPT) || \
                                                          ((type) == APWM_INT_ALL))

/** @defgroup  APWM_CC_CH_ID_TYPE
 *  @{
 */
#define IS_APWM_CC_CH_ID_TYPE(type)                      (((type) == APWM_CC_CH0 ) || \
                                                          ((type) == APWM_CC_CH1) || \
                                                          ((type) == APWM_CC_CH2) || \
                                                          ((type) == APWM_CC_CH3) || \
                                                          ((type) == APWM_CC_CH_MAX))

/** @defgroup  APWM_MODE_TYPE
 *  @{
 */
#define IS_APWM_MODE_TYPE(type)                          (((type) == APWM_MODE_DISABLE ) || \
                                                          ((type) == APWM_Mode_ENABLE))

/** @defgroup  APWM_IDLE_STATE_TYPE
 *  @{
 */
#define IS_APWM_IDLE_STATE_TYPE(type)                    (((type) == APWM_IDLE_STATE_INACTIVE ) || \
                                                          ((type) == APWM_IDLE_STATE_ACTIVE))

/** @defgroup  APWM_BREAK_STATE_TYPE
 *  @{
 */
#define IS_APWM_BREAK_STATE_TYPE(type)                   (((type) == APWM_BREAK_STATE_INACTIVE ) || \
                                                          ((type) == APWM_BREAK_STATE_ACTIVE))

/** @defgroup  APWM_EXT_BREAK_POLARITY_TYPE
 *  @{
 */
#define IS_APWM_EXT_BREAK_POLARITY_TYPE(type)            (((type) == APWM_BREAK_Polarity_LOW ) || \
                                                          ((type) == APWM_BREAK_Polarity_HIGH))

/** @defgroup  APWM_TRIGADC_SOURCE_TYPE
 *  @{
 */
#define IS_APWM_TRIGADC_SOURCE_TYPE(type)                (((type) == APWM_TRIGADC_SOURCE_0L ) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_0H) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_1L) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_1H) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_2L) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_2H) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_3L) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_3H) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_PRDE) || \
                                                          ((type) == APWM_TRIGADC_SOURCE_NONE ))

/*@} end of group APWM_Public_Constants */

/** @defgroup  APWM_Public_Macros
 *  @{
 */
#define IS_APWM_CH(CH)               ((CH) < APWM_CH_MAX)
#define IS_APWM_CC_CH(CH)            ((CH) < APWM_CC_CH_MAX)

/*@} end of group APWM_Public_Macros */

/** @defgroup  APWM_Public_Functions
 *  @{
 */

/**
 *  @brief APWM Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void APWM_IRQHandler(void);
#endif
BL_Err_Type APWM_Channel_Init(APWM_CH_CFG_Type *chCfg);
void APWM_Channel_Set_Div(APWM_CH_ID_Type ch,uint16_t div);
void APWM_Channel_Set_Period(APWM_CH_ID_Type ch,uint16_t period);
void APWM_Channel_Get_Period(APWM_CH_ID_Type ch,uint16_t *period);
void APWM_Channel_Enable(APWM_CH_ID_Type ch);
void APWM_Channel_Disable(APWM_CH_ID_Type ch);
//void APWM_Int_Callback_Install(APWM_CH_ID_Type ch,uint32_t intType,intCallback_Type* cbFun);
void APWM_CC_Channel_Init(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_CC_CH_CFG_Type *ccCfg);
void APWM_CC_Channel_Set_Threshold(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdL,
                                   uint16_t thresholdH);
void APWM_CC_Channel_Set_ThresholdL(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdL);
void APWM_CC_Channel_Set_ThresholdH(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t thresholdH);
void APWM_CC_Channel_Get_Threshold(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint16_t *thresholdL,
                                   uint16_t *thresholdH);
void APWM_CC_Channel_APWM_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type modP, APWM_Mode_Type modN);
void APWM_CC_ChannelP_APWM_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod);
void APWM_CC_ChannelN_APWM_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod);
void APWM_CC_Channel_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type polP,
                                  APWM_Polarity_Type polN);
void APWM_CC_ChannelP_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type pol);
void APWM_CC_ChannelN_Set_Polarity(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Polarity_Type pol);
void APWM_CC_Channel_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idlP,
                                    APWM_Idle_State_Type idlN);
void APWM_CC_ChannelP_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idl);
void APWM_CC_ChannelN_Set_Idle_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Idle_State_Type idl);
void APWM_CC_Channel_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brkP,
                                     APWM_Break_State_Type brkN);
void APWM_CC_ChannelP_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brk);
void APWM_CC_ChannelN_Set_Break_State(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Break_State_Type brk);
void APWM_CC_Channel_Update_Config1(APWM_CH_ID_Type ch, uint32_t cfg);
void APWM_CC_Channel_Get_Config1(APWM_CH_ID_Type ch, uint32_t *cfg);
void APWM_CC_Channel_Set_Dtg(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, uint8_t dtg);
void APWM_SW_Break_Enable(APWM_CH_ID_Type ch);
void APWM_SW_Break_Disable(APWM_CH_ID_Type ch);
void APWM_EXT_Break_Enable(APWM_CH_ID_Type ch);
void APWM_EXT_Break_Disable(APWM_CH_ID_Type ch);
void APWM_EXT_Break_Set_Polarity(APWM_CH_ID_Type ch, APWM_EXT_Break_Polarity_Type pol);
void APWM_Set_TrigADC_Source(APWM_CH_ID_Type ch, APWM_TrigADC_Source_Type src);
void APWM_Int_Mask(APWM_CH_ID_Type ch, APWM_INT_Type intType, BL_Mask_Type intMask);
void APWM_Int_Clear(APWM_CH_ID_Type ch, APWM_INT_Type intType);
BL_Sts_Type APWM_Get_Int_Status(APWM_CH_ID_Type ch, APWM_INT_Type intType);
void APWM_Int_Callback_Install(APWM_CH_ID_Type ch, uint32_t intType, intCallback_Type *cbFun);
void APWM_CC_Channel_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type modP, APWM_Mode_Type modN);
void APWM_CC_ChannelP_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod);
void APWM_CC_ChannelN_Pwm_Mode(APWM_CH_ID_Type ch, APWM_CC_CH_ID_Type cc, APWM_Mode_Type mod);
/*@} end of group APWM_Public_Functions */

/*@} end of group APWM */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_APWM_H__ */
