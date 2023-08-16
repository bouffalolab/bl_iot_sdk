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
#ifndef __BL808_HBN_H__
#define __BL808_HBN_H__

#include "hbn_reg.h"
#include "bl808_aon.h"
#include "bl808_l1c.h"
#include "bl808_sflash.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  HBN
 *  @{
 */

/** @defgroup  HBN_Public_Types
 *  @{
 */

/**
 *  @brief HBN PIR interrupt configuration type definition
 */
typedef struct {
    BL_Fun_Type lowIntEn;                   /*!< Low will trigger interrupt */
    BL_Fun_Type highIntEn;                  /*!< High will trigger interrupt */
}HBN_PIR_INT_CFG_Type;

/**
 *  @brief HBN PIR low pass filter type definition
 */
typedef enum {
    HBN_PIR_LPF_DIV1,                       /*!< HBN PIR lpf div 1 */
    HBN_PIR_LPF_DIV2,                       /*!< HBN PIR lpf div 2 */
}HBN_PIR_LPF_Type;

/**
 *  @brief HBN PIR high pass filter type definition
 */
typedef enum {
    HBN_PIR_HPF_METHOD0,                    /*!< HBN PIR hpf calc method 0, 1-z^-1 */
    HBN_PIR_HPF_METHOD1,                    /*!< HBN PIR hpf calc method 1, 1-z^-2 */
    HBN_PIR_HPF_METHOD2,                    /*!< HBN PIR hpf calc method 2, 1-z^-3 */
}HBN_PIR_HPF_Type;

/**
 *  @brief HBN flash pad pu pd type
 */
typedef enum {
    HBN_FLASH_PAD_PULL_NONE,                /*!< flash pad pull none when Flash at Deep Power Down Mode */
    HBN_FLASH_PAD_PULL_UP,                  /*!< flash pad pull up when Flash at Deep Power Down Mode */
    HBN_FLASH_PAD_PULL_DOWN,                /*!< flash pad pull down when Flash at Deep Power Down Mode */
}HBN_FLASH_PAD_PULL_Type;

/**
 *  @brief HBN BOR threshold type definition
 */
typedef enum {
    HBN_BOR_THRES_2P0V,                     /*!< BOR threshold 2.0V */
    HBN_BOR_THRES_2P4V,                     /*!< BOR threshold 2.4V */
}HBN_BOR_THRES_Type;

/**
 *  @brief HBN BOR mode type definition
 */
typedef enum {
    HBN_BOR_MODE_POR_INDEPENDENT,           /*!< POR is independent of BOR */
    HBN_BOR_MODE_POR_RELEVANT,              /*!< POR is relevant to BOR */
}HBN_BOR_MODE_Type;

/**
 *  @brief HBN 32K clock type definition
 */
typedef enum {
    HBN_32K_RC=0,                           /*!< HBN use rc 32k */
    HBN_32K_XTAL,                           /*!< HBN use xtal 32k */
    HBN_32K_DIG=3,                          /*!< HBN use dig 32k */
}HBN_32K_CLK_Type;

/**
 *  @brief HBN xclk clock type definition
 */
typedef enum {
    HBN_MCU_XCLK_RC32M,                     /*!< use RC32M as xclk clock */
    HBN_MCU_XCLK_XTAL,                      /*!< use XTAL as xclk clock */
}HBN_MCU_XCLK_Type;

/**
 *  @brief HBN root clock type definition
 */
typedef enum {
    HBN_MCU_ROOT_CLK_RC32M,                 /*!< use RC32M as root clock */
    HBN_MCU_ROOT_CLK_XTAL,                  /*!< use XTAL as root clock */
    HBN_MCU_ROOT_CLK_PLL,                   /*!< use PLL as root clock */
}HBN_MCU_ROOT_CLK_Type;

/**
 *  @brief HBN UART clock type definition
 */
typedef enum {
    HBN_UART_CLK_MCU_BCLK=0,                /*!< Select mcu_bclk as UART clock */
    HBN_UART_CLK_160M,                      /*!< Select 160M as UART clock */
    HBN_UART_CLK_XCLK,                      /*!< Select XCLK as UART clock */
}HBN_UART_CLK_Type;

/**
 *  @brief HBN RTC interrupt delay type definition
 */
typedef enum {
    HBN_RTC_INT_DELAY_32T=0,                /*!< HBN RTC interrupt delay 32T */
    HBN_RTC_INT_DELAY_0T=1,                 /*!< HBN RTC interrupt delay 0T */
}HBN_RTC_INT_Delay_Type;

/**
 *  @brief HBN interrupt type definition
 */
typedef enum {
    HBN_INT_GPIO7=0,                        /*!< HBN interrupt type: GPIO7 */
    HBN_INT_GPIO8=1,                        /*!< HBN interrupt type: GPIO8 */
    HBN_INT_RTC=16,                         /*!< HBN interrupt type: RTC */
    HBN_INT_PIR=17,                         /*!< HBN interrupt type: PIR */
    HBN_INT_BOR=18,                         /*!< HBN interrupt type: BOR */
    HBN_INT_ACOMP0=20,                      /*!< HBN interrupt type: ACOMP0 */
    HBN_INT_ACOMP1=22,                      /*!< HBN interrupt type: ACOMP1 */
}HBN_INT_Type;

/**
 *  @brief HBN GPIO pad pu pd type
 */
typedef enum {
    HBN_GPIO_PAD_PULL_NONE = 0, /*!< gpio pad pull none at hbn */
    HBN_GPIO_PAD_PULL_DOWN = 1, /*!< gpio pad pull down at hbn */
    HBN_GPIO_PAD_PULL_UP = 2,   /*!< gpio pad pull up at hbn */
    HBN_GPIO_PAD_ACTIVE_IE = 3, /*!< gpio pad active ie at hbn */
} HBN_GPIO_PAD_PULL_Type;


/**
 *  @brief HBN AON PAD configuration type definition
 */
typedef struct
{
    uint8_t ctrlEn;                 /*!< AON GPIO41/40/15~9  Control by AON HW */
    uint8_t inputEn;                /*!< Always on PAD IE/SMT (if corresponding  AON GPIO controlled by AON HW) */
    uint8_t outputEn;               /*!< Always on PAD OE (if corresponding  AON GPIO controlled by AON HW) */
    HBN_GPIO_PAD_PULL_Type pullCfg; /*!< Always on PAD PU/PD (if corresponding  AON GPIO controlled by AON HW) */
} HBN_AON_PAD_CFG_Type;


/**
 *  @brief HBN GPIO interrupt trigger type definition
 */
typedef enum {
    HBN_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE=0x0,    /*!< HBN GPIO INT trigger type: sync falling edge trigger */
    HBN_GPIO_INT_TRIGGER_SYNC_RISING_EDGE=0x1,    /*!< HBN GPIO INT trigger type: sync rising edge trigger */
    HBN_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL=0x2,    /*!< HBN GPIO INT trigger type: sync low level trigger */
    HBN_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL=0x3,    /*!< HBN GPIO INT trigger type: sync high level trigger */
    HBN_GPIO_INT_TRIGGER_SYNC_RISING_FALLING_EDGE=0x4,    /*!< HBN GPIO INT trigger type: sync rising falling edge trigger */
    HBN_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE=0x8,    /*!< HBN GPIO INT trigger type: async falling edge trigger */
    HBN_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE=0x9,    /*!< HBN GPIO INT trigger type: async rising edge trigger */
    HBN_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL=0xA,    /*!< HBN GPIO INT trigger type: async low level trigger */
    HBN_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL=0xB,    /*!< HBN GPIO INT trigger type: async high level trigger */
}HBN_GPIO_INT_Trigger_Type;

/**
 *  @brief HBN OUT0 interrupt type definition
 */
typedef enum {
    HBN_OUT0_INT_GPIO7=0,                   /*!< HBN out 0 interrupt type: GPIO7 */
    HBN_OUT0_INT_GPIO8,                     /*!< HBN out 0 interrupt type: GPIO8 */
    HBN_OUT0_INT_RTC,                       /*!< HBN out 0 interrupt type: RTC */
    HBN_OUT0_INT_MAX,                       /*!< MAX */
}HBN_OUT0_INT_Type;

/**
 *  @brief HBN OUT0 interrupt type definition
 */
typedef enum {
    HBN_OUT1_INT_PIR,                       /*!< HBN out 1 interrupt type: PIR */
    HBN_OUT1_INT_BOR,                       /*!< HBN out 1 interrupt type: BOR */
    HBN_OUT1_INT_ACOMP0,                    /*!< HBN out 1 interrupt type: ACOMP0 */
    HBN_OUT1_INT_ACOMP1,                    /*!< HBN out 1 interrupt type: ACOMP1 */
    HBN_OUT1_INT_MAX,                       /*!< MAX */
}HBN_OUT1_INT_Type;

/**
 *  @brief HBN LDO level type definition
 */
typedef enum {
    HBN_LDO_LEVEL_0P60V=0,                  /*!< HBN LDO voltage 0.60V */
    HBN_LDO_LEVEL_0P65V=1,                  /*!< HBN LDO voltage 0.65V */
    HBN_LDO_LEVEL_0P70V=2,                  /*!< HBN LDO voltage 0.70V */
    HBN_LDO_LEVEL_0P75V=3,                  /*!< HBN LDO voltage 0.75V */
    HBN_LDO_LEVEL_0P80V=4,                  /*!< HBN LDO voltage 0.80V */
    HBN_LDO_LEVEL_0P85V=5,                  /*!< HBN LDO voltage 0.85V */
    HBN_LDO_LEVEL_0P90V=6,                  /*!< HBN LDO voltage 0.90V */
    HBN_LDO_LEVEL_0P95V=7,                  /*!< HBN LDO voltage 0.95V */
    HBN_LDO_LEVEL_1P00V=8,                  /*!< HBN LDO voltage 1.00V */
    HBN_LDO_LEVEL_1P05V=9,                  /*!< HBN LDO voltage 1.05V */
    HBN_LDO_LEVEL_1P10V=10,                 /*!< HBN LDO voltage 1.10V */
    HBN_LDO_LEVEL_1P15V=11,                 /*!< HBN LDO voltage 1.15V */
    HBN_LDO_LEVEL_1P20V=12,                 /*!< HBN LDO voltage 1.20V */
    HBN_LDO_LEVEL_1P25V=13,                 /*!< HBN LDO voltage 1.25V */
    HBN_LDO_LEVEL_1P30V=14,                 /*!< HBN LDO voltage 1.30V */
    HBN_LDO_LEVEL_1P35V=15,                 /*!< HBN LDO voltage 1.35V */
}HBN_LDO_LEVEL_Type;


/**
 *  @brief HBN aon pad type definition
 */
typedef enum {
    HBN_AON_PAD_GPIO9 = 0,  /*!< HBN aon pad type: GPIO9 */
    HBN_AON_PAD_GPIO10 = 1, /*!< HBN aon pad type: GPIO10 */
    HBN_AON_PAD_GPIO11 = 2, /*!< HBN aon pad type: GPIO11 */
    HBN_AON_PAD_GPIO12 = 3, /*!< HBN aon pad type: GPIO12 */
    HBN_AON_PAD_GPIO13 = 4, /*!< HBN aon pad type: GPIO13 */
    HBN_AON_PAD_GPIO14 = 5, /*!< HBN aon pad type: GPIO14 */
    HBN_AON_PAD_GPIO15 = 6, /*!< HBN aon pad type: GPIO15 */
    HBN_AON_PAD_GPIO40 = 7, /*!< HBN aon pad type: GPIO40 */
    HBN_AON_PAD_GPIO41 = 8, /*!< HBN aon pad type: GPIO41 */
} HBN_AON_PAD_Type;
/**
 *  @brief HBN level type definition
 */
typedef enum {
    HBN_LEVEL_0,                            /*!< HBN pd_core */
    HBN_LEVEL_1,                            /*!< HBN pd_aon_hbncore + pd_core */
    HBN_LEVEL_2,                            /*!< HBN pd_aon_hbnrtc + pd_aon_hbncore + pd_core */
    HBN_LEVEL_3,                            /*!< HBN pd_aon_hbnrtc + pd_aon_hbncore + pd_core */
}HBN_LEVEL_Type;

/**
 *  @brief HBN BOR configuration type definition
 */
typedef struct {
    uint8_t enableBor;                      /*!< Enable BOR or not */
    uint8_t enableBorInt;                   /*!< Enable BOR interrupt or not */
    uint8_t borThreshold;                   /*!< BOR threshold */
    uint8_t enablePorInBor;                 /*!< Enable POR when BOR occure or not */
}HBN_BOR_CFG_Type;

/**
 *  @brief HBN APP configuration type definition
 */
typedef struct {
    uint8_t useXtal32k;                     /*!< Whether use xtal 32K as 32K clock source,otherwise use rc32k */
    uint32_t sleepTime;                     /*!< HBN sleep time */
    uint8_t gpioWakeupSrc;                  /*!< GPIO Wakeup source */
    HBN_GPIO_INT_Trigger_Type gpioTrigType; /*!< GPIO Triger type */
    SPI_Flash_Cfg_Type *flashCfg;           /*!< Flash config pointer, used when power down flash */
    HBN_LEVEL_Type hbnLevel;                /*!< HBN level */
    HBN_LDO_LEVEL_Type ldoLevel;            /*!< LDO level */
}HBN_APP_CFG_Type;

/*@} end of group HBN_Public_Types */

/** @defgroup  HBN_Public_Constants
 *  @{
 */

/** @defgroup  HBN_PIR_LPF_TYPE
 *  @{
 */
#define IS_HBN_PIR_LPF_TYPE(type)                        (((type) == HBN_PIR_LPF_DIV1) || \
                                                          ((type) == HBN_PIR_LPF_DIV2))

/** @defgroup  HBN_PIR_HPF_TYPE
 *  @{
 */
#define IS_HBN_PIR_HPF_TYPE(type)                        (((type) == HBN_PIR_HPF_METHOD0) || \
                                                          ((type) == HBN_PIR_HPF_METHOD1) || \
                                                          ((type) == HBN_PIR_HPF_METHOD2))

/** @defgroup  HBN_FLASH_PAD_PULL_TYPE
 *  @{
 */
#define IS_HBN_FLASH_PAD_PULL_TYPE(type)                 (((type) == HBN_FLASH_PAD_PULL_NONE) || \
                                                          ((type) == HBN_FLASH_PAD_PULL_UP) || \
                                                          ((type) == HBN_FLASH_PAD_PULL_DOWN))

/** @defgroup  HBN_BOR_THRES_TYPE
 *  @{
 */
#define IS_HBN_BOR_THRES_TYPE(type)                      (((type) == HBN_BOR_THRES_2P0V) || \
                                                          ((type) == HBN_BOR_THRES_2P4V))

/** @defgroup  HBN_BOR_MODE_TYPE
 *  @{
 */
#define IS_HBN_BOR_MODE_TYPE(type)                       (((type) == HBN_BOR_MODE_POR_INDEPENDENT) || \
                                                          ((type) == HBN_BOR_MODE_POR_RELEVANT))

/** @defgroup  HBN_32K_CLK_TYPE
 *  @{
 */
#define IS_HBN_32K_CLK_TYPE(type)                        (((type) == HBN_32K_RC) || \
                                                          ((type) == HBN_32K_XTAL) || \
                                                          ((type) == HBN_32K_DIG))

/** @defgroup  HBN_MCU_XCLK_TYPE
 *  @{
 */
#define IS_HBN_MCU_XCLK_TYPE(type)                       (((type) == HBN_MCU_XCLK_RC32M) || \
                                                          ((type) == HBN_MCU_XCLK_XTAL))

/** @defgroup  HBN_MCU_ROOT_CLK_TYPE
 *  @{
 */
#define IS_HBN_MCU_ROOT_CLK_TYPE(type)                   (((type) == HBN_MCU_ROOT_CLK_RC32M) || \
                                                          ((type) == HBN_MCU_ROOT_CLK_XTAL) || \
                                                          ((type) == HBN_MCU_ROOT_CLK_PLL))

/** @defgroup  HBN_UART_CLK_TYPE
 *  @{
 */
#define IS_HBN_UART_CLK_TYPE(type)                       (((type) == HBN_UART_CLK_MCU_BCLK) || \
                                                          ((type) == HBN_UART_CLK_160M) || \
                                                          ((type) == HBN_UART_CLK_XCLK))

/** @defgroup  HBN_RTC_INT_DELAY_TYPE
 *  @{
 */
#define IS_HBN_RTC_INT_DELAY_TYPE(type)                  (((type) == HBN_RTC_INT_DELAY_32T) || \
                                                          ((type) == HBN_RTC_INT_DELAY_0T))

/** @defgroup  HBN_INT_TYPE
 *  @{
 */
#define IS_HBN_INT_TYPE(type)                            (((type) == HBN_INT_GPIO7) || \
                                                          ((type) == HBN_INT_GPIO8) || \
                                                          ((type) == HBN_INT_RTC) || \
                                                          ((type) == HBN_INT_PIR) || \
                                                          ((type) == HBN_INT_BOR) || \
                                                          ((type) == HBN_INT_ACOMP0) || \
                                                          ((type) == HBN_INT_ACOMP1))

/** @defgroup  HBN_GPIO_INT_TRIGGER_TYPE
 *  @{
 */
#define IS_HBN_GPIO_INT_TRIGGER_TYPE(type)               (((type) == HBN_GPIO_INT_TRIGGER_SYNC_FALLING_EDGE) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_SYNC_RISING_EDGE) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_SYNC_LOW_LEVEL) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_SYNC_HIGH_LEVEL) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_SYNC_RISING_FALLING_EDGE) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_ASYNC_FALLING_EDGE) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_ASYNC_RISING_EDGE) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_ASYNC_LOW_LEVEL) || \
                                                          ((type) == HBN_GPIO_INT_TRIGGER_ASYNC_HIGH_LEVEL))

/** @defgroup  HBN_OUT0_INT_TYPE
 *  @{
 */
#define IS_HBN_OUT0_INT_TYPE(type)                       (((type) == HBN_OUT0_INT_GPIO7) || \
                                                          ((type) == HBN_OUT0_INT_GPIO8) || \
                                                          ((type) == HBN_OUT0_INT_RTC) || \
                                                          ((type) == HBN_OUT0_INT_MAX))

/** @defgroup  HBN_OUT1_INT_TYPE
 *  @{
 */
#define IS_HBN_OUT1_INT_TYPE(type)                       (((type) == HBN_OUT1_INT_PIR) || \
                                                          ((type) == HBN_OUT1_INT_BOR) || \
                                                          ((type) == HBN_OUT1_INT_ACOMP0) || \
                                                          ((type) == HBN_OUT1_INT_ACOMP1) || \
                                                          ((type) == HBN_OUT1_INT_MAX))

/** @defgroup  HBN_LDO_LEVEL_TYPE
 *  @{
 */
#define IS_HBN_LDO_LEVEL_TYPE(type)                      (((type) == HBN_LDO_LEVEL_0P60V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P65V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P70V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P75V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P80V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P85V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P90V) || \
                                                          ((type) == HBN_LDO_LEVEL_0P95V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P00V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P05V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P10V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P15V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P20V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P25V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P30V) || \
                                                          ((type) == HBN_LDO_LEVEL_1P35V))


/** @defgroup  HBN_GPIO_PAD_PULL_TYPE
 *  @{
 */
#define IS_HBN_GPIO_PAD_PULL_TYPE(type) (((type) == HBN_GPIO_PAD_PULL_NONE) || \
                                         ((type) == HBN_GPIO_PAD_PULL_DOWN) || \
                                         ((type) == HBN_GPIO_PAD_PULL_UP) ||   \
                                         ((type) == HBN_GPIO_PAD_ACTIVE_IE))


                                
/** @defgroup  HBN_AON_PAD_TYPE
 *  @{
 */
#define IS_HBN_AON_PAD_TYPE(type) (((type) == HBN_AON_PAD_GPIO9) ||  \
                                   ((type) == HBN_AON_PAD_GPIO10) || \
                                   ((type) == HBN_AON_PAD_GPIO11) || \
                                   ((type) == HBN_AON_PAD_GPIO12) || \
                                   ((type) == HBN_AON_PAD_GPIO13) || \
                                   ((type) == HBN_AON_PAD_GPIO14) || \
                                   ((type) == HBN_AON_PAD_GPIO15) || \
                                   ((type) == HBN_AON_PAD_GPIO40) || \
                                   ((type) == HBN_AON_PAD_GPIO41))

/** @defgroup  HBN_LEVEL_TYPE
 *  @{
 */
#define IS_HBN_LEVEL_TYPE(type)                          (((type) == HBN_LEVEL_0) || \
                                                          ((type) == HBN_LEVEL_1) || \
                                                          ((type) == HBN_LEVEL_2) || \
                                                          ((type) == HBN_LEVEL_3))

/*@} end of group HBN_Public_Constants */

/** @defgroup  HBN_Public_Macros
 *  @{
 */
#define HBN_RAM_SIZE                    (4*1024)
#define HBN_RTC_COMP_BIT0_39            0x01
#define HBN_RTC_COMP_BIT0_23            0x02
#define HBN_RTC_COMP_BIT13_39           0x04
#define HBN_STATUS_ENTER_FLAG           0x4e424845
#define HBN_STATUS_WAKEUP_FLAG          0x4e424857
#define HBN_RELEASE_CORE_FLAG           (0x4800)
#define HBN_REPOWER_INTERNAL_FLASH_FLAG (0x5200)
#define HBN_XTAL_FLAG_MASK              0x0000ff00
#define HBN_XTAL_FLAG_VALUE             0x5800
#define HBN_WAKEUP_GPIO_NONE            0x00
#define HBN_WAKEUP_GPIO_7               0x01
#define HBN_WAKEUP_GPIO_8               0x02
#define HBN_WAKEUP_GPIO_ALL             0x03

/*@} end of group HBN_Public_Macros */

/** @defgroup  HBN_Public_Functions
 *  @{
 */
/*----------*/
#ifndef BFLB_USE_HAL_DRIVER
void HBN_OUT0_IRQHandler(void);
void HBN_OUT1_IRQHandler(void);
#endif
/*----------*/
void HBN_Mode_Enter(HBN_APP_CFG_Type *cfg);
void HBN_Power_Down_Flash(SPI_Flash_Cfg_Type *flashCfg);
void HBN_Enable(uint32_t aGPIOIeCfg,HBN_LDO_LEVEL_Type ldoLevel,HBN_LEVEL_Type hbnLevel);
BL_Err_Type HBN_Reset(void);
BL_Err_Type HBN_App_Reset(void);
/*----------*/
BL_Err_Type HBN_PIR_Enable(void);
BL_Err_Type HBN_PIR_Disable(void);
BL_Err_Type HBN_PIR_INT_Config(HBN_PIR_INT_CFG_Type* pirIntCfg);
BL_Err_Type HBN_PIR_LPF_Sel(HBN_PIR_LPF_Type lpf);
BL_Err_Type HBN_PIR_HPF_Sel(HBN_PIR_HPF_Type hpf);
BL_Err_Type HBN_Set_PIR_Threshold(uint16_t threshold);
uint16_t HBN_Get_PIR_Threshold(void);
BL_Err_Type HBN_Set_PIR_Interval(uint16_t interval);
uint16_t HBN_Get_PIR_Interval(void);
/*----------*/
BL_Err_Type HBN_Set_SFlash2_Pad_PuPd(HBN_FLASH_PAD_PULL_Type pullType);
BL_Sts_Type HBN_Get_BOR_OUT_State(void);
BL_Err_Type HBN_Set_BOR_Config(uint8_t enable,HBN_BOR_THRES_Type threshold,HBN_BOR_MODE_Type mode);
/*----------*/
BL_Err_Type HBN_Set_Ldo11_Aon_Vout(HBN_LDO_LEVEL_Type ldoLevel);
BL_Err_Type HBN_Set_Ldo11_Rt_Vout(HBN_LDO_LEVEL_Type ldoLevel);
BL_Err_Type HBN_Set_Ldo11_Soc_Vout(HBN_LDO_LEVEL_Type ldoLevel);
BL_Err_Type HBN_Set_Ldo11_All_Vout(HBN_LDO_LEVEL_Type ldoLevel);
/*----------*/
BL_Err_Type HBN_32K_Sel(HBN_32K_CLK_Type clkType);
BL_Err_Type HBN_Set_UART_CLK_Sel(HBN_UART_CLK_Type clkSel);
HBN_MCU_XCLK_Type HBN_Get_MCU_XCLK_Sel(void);
BL_Err_Type HBN_Set_MCU_XCLK_Sel(HBN_MCU_XCLK_Type xclk);
HBN_MCU_ROOT_CLK_Type HBN_Get_MCU_Root_CLK_Sel(void);
BL_Err_Type HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_Type rootClk);
/*----------*/
BL_Err_Type HBN_Set_HRAM_slp(void);
BL_Err_Type HBN_Set_HRAM_Ret(void);
/*----------*/
uint32_t HBN_Get_Status_Flag(void);
BL_Err_Type HBN_Set_Status_Flag(uint32_t flag);
uint32_t HBN_Get_Wakeup_Addr(void);
BL_Err_Type HBN_Set_Wakeup_Addr(uint32_t addr);
uint8_t HBN_Get_Core_Unhalt_Config(void);
BL_Err_Type HBN_Set_Core_Reboot_Config(uint8_t rcfg);
uint8_t HBN_Get_MM_Power_Config(void);
BL_Err_Type HBN_Set_MM_Power_Config(uint8_t pcfg);
uint16_t HBN_Get_Internal_Flash_Repower_Config(void);
BL_Err_Type HBN_Set_Internal_Flash_Repower_Delay(uint8_t delay);
BL_Err_Type HBN_Set_Xtal_Type(uint8_t xtalType);
BL_Err_Type HBN_Get_Xtal_Type(uint8_t *xtalType);
/*----------*/
BL_Err_Type HBN_Clear_RTC_Counter(void);
BL_Err_Type HBN_Enable_RTC_Counter(void);
BL_Err_Type HBN_Set_RTC_Timer(HBN_RTC_INT_Delay_Type delay,uint32_t compValLow,uint32_t compValHigh,uint8_t compMode);
BL_Err_Type HBN_Get_RTC_Timer_Val(uint32_t *valLow,uint32_t *valHigh);
BL_Err_Type HBN_Clear_RTC_IRQ(void);
/*----------*/
BL_Err_Type HBN_GPIO_INT_Enable(HBN_GPIO_INT_Trigger_Type gpioIntTrigType);
BL_Err_Type HBN_GPIO_INT_Disable(void);
BL_Sts_Type HBN_Get_INT_State(HBN_INT_Type irqType);
uint8_t HBN_Get_Pin_Wakeup_Mode(void);
BL_Err_Type HBN_Clear_IRQ(HBN_INT_Type irqType);
BL_Err_Type HBN_Hw_Pu_Pd_Cfg(uint8_t enable);
BL_Err_Type HBN_Aon_Pad_IeSmt_Cfg(uint32_t padCfg);
BL_Err_Type HBN_Pin_WakeUp_Mask(uint8_t maskVal);
/*----------*/
BL_Err_Type HBN_Enable_AComp0_IRQ(void);
BL_Err_Type HBN_Disable_AComp0_IRQ(void);
BL_Err_Type HBN_Enable_AComp1_IRQ(void);
BL_Err_Type HBN_Disable_AComp1_IRQ(void);
/*----------*/
BL_Err_Type HBN_Enable_BOR_IRQ(void);
BL_Err_Type HBN_Disable_BOR_IRQ(void);
/*----------*/
BL_Err_Type HBN_Out0_Callback_Install(HBN_OUT0_INT_Type intType,intCallback_Type* cbFun);
BL_Err_Type HBN_Out1_Callback_Install(HBN_OUT1_INT_Type intType,intCallback_Type* cbFun);
/*----------*/
BL_Err_Type HBN_Aon_Pad_WakeUpCfg(BL_Fun_Type puPdEn,uint32_t ieSmtEn,
                                                 HBN_GPIO_INT_Trigger_Type trigMode,uint32_t maskVal,BL_Fun_Type dlyEn,uint8_t dlySec);
/*----------*/
BL_Err_Type HBN_Power_On_Xtal_32K(void);
BL_Err_Type HBN_Power_Off_Xtal_32K(void);
BL_Err_Type HBN_Power_On_RC32K(void);
BL_Err_Type HBN_Power_Off_RC32K(void);
BL_Err_Type HBN_Trim_RC32K(void);
BL_Err_Type HBN_Set_BOR_Cfg(HBN_BOR_CFG_Type *cfg);
BL_Err_Type HBN_Clear_RTC_INT(void);
BL_Err_Type HBN_Aon_Pad_Cfg(uint8_t aonPadHwCtrlEn, HBN_AON_PAD_Type aonGpio, HBN_AON_PAD_CFG_Type *aonPadCfg);
/*@} end of group HBN_Public_Functions */

/*@} end of group HBN */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_HBN_H__ */
