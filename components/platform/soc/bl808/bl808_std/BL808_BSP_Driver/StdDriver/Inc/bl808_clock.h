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
#ifndef __BL808_CLOCK_H__
#define __BL808_CLOCK_H__

#include "glb_reg.h"
#include "mcu_misc_reg.h"
#include "mm_misc_reg.h"
#include "pds_reg.h"
#include "bl808_glb.h"
#include "bl808_hbn.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CLOCK
 *  @{
 */

/** @defgroup  CLOCK_Public_Types
 *  @{
 */

/**
 *  @brief System clock type definition
 */
typedef enum {
    BL_SYSTEM_CLOCK_MCU_XCLK,               /*!< MCU xclk clock */
    BL_SYSTEM_CLOCK_MCU_ROOT_CLK,           /*!< MCU root clock */
    BL_SYSTEM_CLOCK_MCU_CLK,                /*!< MCU Fast clock/CPU clock */
    BL_SYSTEM_CLOCK_MCU_BCLK,               /*!< MCU BUS clock */
    BL_SYSTEM_CLOCK_PERI_BCLK,              /*!< MCU peri BUS clock */
    BL_SYSTEM_CLOCK_DSP_XCLK,               /*!< MCU xclk clock */
    BL_SYSTEM_CLOCK_DSP_ROOT_CLK,           /*!< DSP root clock */
    BL_SYSTEM_CLOCK_DSP_CLK,                /*!< DSP Fast clock/CPU clock */
    BL_SYSTEM_CLOCK_DSP_BCLK,               /*!< DSP BUS clock */
    BL_SYSTEM_CLOCK_MM_BCLK,                /*!< DSP mm BUS clock */
    BL_SYSTEM_CLOCK_LP_CLK,                 /*!< LP clock */
    BL_SYSTEM_CLOCK_F32K,                   /*!< F32K clock */
    BL_SYSTEM_CLOCK_XCLK,                   /*!< XCLK:RC32M or XTAL */
    BL_SYSTEM_CLOCK_XTAL,                   /*!< XTAL clock */
    BL_SYSTEM_CLOCK_MAX,                    /*!< MAX type of system clock */
}BL_System_Clock_Type;

/**
 *  @brief PLL XTAL type definition
 */
typedef enum {
    GLB_PLL_XTAL_NONE,                      /*!< XTAL is none */
    GLB_PLL_XTAL_24M,                       /*!< XTAL is 24M */
    GLB_PLL_XTAL_32M,                       /*!< XTAL is 32M */
    GLB_PLL_XTAL_38P4M,                     /*!< XTAL is 38.4M */
    GLB_PLL_XTAL_40M,                       /*!< XTAL is 40M */
    GLB_PLL_XTAL_26M,                       /*!< XTAL is 26M */
    GLB_PLL_XTAL_RC32M,                     /*!< XTAL is RC32M */
    GLB_PLL_XTAL_MAX,                       /*!< type max num */
}GLB_PLL_XTAL_Type;

/**
 *  @brief SOC clock config type
 */
typedef struct {
    uint32_t magic;                         /*!< Clock config magic */
    uint32_t systemClock[BL_SYSTEM_CLOCK_MAX];    /*!< System lock value */
    uint32_t peripheralClock[BL_AHB_SLAVE1_MAX];    /*!< Pewripherals clock value */
    uint32_t i2sClock;                      /*!< I2S clock */
}Clock_Cfg_Type;

/*@} end of group CLOCK_Public_Types */

/** @defgroup  CLOCK_Public_Constants
 *  @{
 */

/** @defgroup  BL_SYSTEM_CLOCK_TYPE
 *  @{
 */
#define IS_BL_SYSTEM_CLOCK_TYPE(type)                    (((type) == BL_SYSTEM_CLOCK_MCU_XCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_MCU_ROOT_CLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_MCU_CLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_MCU_BCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_PERI_BCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_DSP_ROOT_CLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_DSP_CLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_DSP_BCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_MM_BCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_LP_CLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_F32K) || \
                                                          ((type) == BL_SYSTEM_CLOCK_XCLK) || \
                                                          ((type) == BL_SYSTEM_CLOCK_XTAL) || \
                                                          ((type) == BL_SYSTEM_CLOCK_MAX))

/*@} end of group CLOCK_Public_Constants */

/** @defgroup  CLOCK_Public_Macros
 *  @{
 */
#define SYS_CLOCK_CFG_MAGIC                 (0x12345678)
#define SYS_CLOCK_CFG_ADDR                  (0x20010000+4*1024-512)

/*@} end of group CLOCK_Public_Macros */

/** @defgroup  CLOCK_Public_Functions
 *  @{
 */
/*----------*/
uint32_t Clock_System_Clock_Get(BL_System_Clock_Type type);
uint32_t  Clock_Peripheral1_Clock_Get(BL_AHB_Slave1_Type type);
uint32_t  Clock_Peripheral2_Clock_Get(BL_AHB_Slave2_Type type);
uint32_t  Clock_Audio_ADC_Clock_Get(void);
uint32_t  Clock_Audio_DAC_Clock_Get(void);
/*----------*/
uint32_t SystemCoreClockGet(void);
/*----------*/
BL_Err_Type CPU_Set_MTimer_RST(uint8_t rstEn);
BL_Err_Type CPU_Reset_MTimer(void);
BL_Err_Type CPU_Set_MTimer_CLK(uint8_t enable,uint16_t div);
uint32_t CPU_Get_MTimer_Source_Clock(void);
uint32_t CPU_Get_MTimer_Clock(void);
uint64_t CPU_Get_MTimer_Counter(void);
uint64_t CPU_Get_CPU_Cycle(void);
uint64_t CPU_Get_MTimer_US(void);
uint64_t CPU_Get_MTimer_MS(void);
BL_Err_Type CPU_MTimer_Delay_US(uint32_t cnt);
BL_Err_Type CPU_MTimer_Delay_MS(uint32_t cnt);
uint32_t Clock_Get_EMI_Clk(void);
uint32_t Clock_Get_ISP_Clk(void);
uint32_t Clock_Get_BLAI_Clk(void);
uint32_t Clock_Get_Display_Clk(void);
/*----------*/

/*@} end of group CLOCK_Public_Functions */

/*@} end of group CLOCK */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_CLOCK_H__ */
