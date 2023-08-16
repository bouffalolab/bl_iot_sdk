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
#include "bl808_pds.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDS
 *  @{
 */

/** @defgroup  PDS_Private_Macros
 *  @{
 */

/*@} end of group PDS_Private_Macros */

/** @defgroup  PDS_Private_Types
 *  @{
 */

/*@} end of group PDS_Private_Types */

/** @defgroup  PDS_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type * pdsIntCbfArra[PDS_INT_MAX]={NULL};
#endif

/*@} end of group PDS_Private_Variables */

/** @defgroup  PDS_Global_Variables
 *  @{
 */

/*@} end of group PDS_Global_Variables */

/** @defgroup  PDS_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PDS_Private_Fun_Declaration */

/** @defgroup  PDS_Private_Functions
 *  @{
 */

/*@} end of group PDS_Private_Functions */

/** @defgroup  PDS_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  set sflash2 pad pull type in pds
 *
 * @param  pullType: pull type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Set_SFlash2_Pad_PuPd(PDS_FLASH_PAD_PULL_Type pullType)
{
    uint32_t tmpVal;
    
    CHECK_PARAM(IS_PDS_FLASH_PAD_PULL_TYPE(pullType));
    
    tmpVal=BL_RD_REG(PDS_BASE,PDS_GPIO_SET_PU_PD);
    switch(pullType){
        case PDS_FLASH_PAD_PULL_NONE:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PD,0x00);
            break;
        case PDS_FLASH_PAD_PULL_UP:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PU,0x3F);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PD,0x00);
            break;
        case PDS_FLASH_PAD_PULL_DOWN:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PD,0x3F);
            break;
        default :
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_32_27_PD,0x00);
            break;
    }
    BL_WR_REG(PDS_BASE,PDS_GPIO_SET_PU_PD,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set sflash3 pad pull type in pds
 *
 * @param  pullType: pull type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Set_SFlash3_Pad_PuPd(PDS_FLASH_PAD_PULL_Type pullType)
{
    uint32_t tmpVal;
    
    CHECK_PARAM(IS_PDS_FLASH_PAD_PULL_TYPE(pullType));
    
    tmpVal=BL_RD_REG(PDS_BASE,PDS_GPIO_SET_PU_PD);
    switch(pullType){
        case PDS_FLASH_PAD_PULL_NONE:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PD,0x00);
            break;
        case PDS_FLASH_PAD_PULL_UP:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PU,0x3F);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PD,0x00);
            break;
        case PDS_FLASH_PAD_PULL_DOWN:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PD,0x3F);
            break;
        default :
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PU,0x00);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_CR_PDS_GPIO_38_33_PD,0x00);
            break;
    }
    BL_WR_REG(PDS_BASE,PDS_GPIO_SET_PU_PD,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU0 clock enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU0_Clock_Enable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDS_REG_MCU1_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG1,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU0 clock disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU0_Clock_Disable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_REG_MCU1_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG1,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU1 clock enable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU1_Clock_Enable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDS_REG_MCU2_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG1,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU1 clock disable
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU1_Clock_Disable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_REG_MCU2_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG1,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU0 MCU1 bclk div
 *
 * @param  div: clock div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU_Bclk_Div(uint8_t div)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_MCU_BCLK_DIV,div);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set MCU0 reset address
 *
 * @param  addr: address
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_MCU0_Reset_Address(uint32_t addr)
{
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG14,addr);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  enable LP clock
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_LP_Clock_Enable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG0);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDS_REG_PICO_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG0,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  disable LP clock
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_LP_Clock_Disable(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_REG_PICO_CLK_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG0,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set LP clock divider
 *
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_LP_System_CLK_Div(uint8_t div)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PICO_DIV,1);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG7,tmpVal);
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PICO_DIV,div);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG7,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set LP clock
 *
 * @param  clkFreq: clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Set_LP_System_CLK(PDS_LP_SYS_CLK_Type clkFreq)
{
    CHECK_PARAM(IS_PDS_LP_SYS_CLK_TYPE(clkFreq));
    
    /* do nothing */
    (void)clkFreq;
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  reset LP rtc
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Reset_LP_RTC(void)
{
    uint32_t tmpVal = 0;
    
    /* lp rtc_rst=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_E902_RTC_RST);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    /* lp rtc_rst=1 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDS_E902_RTC_RST);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    /* lp rtc_rst=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_E902_RTC_RST);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set LP rtc clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: clock div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_LP_RTC_CLK(uint8_t enable,uint16_t div)
{
    uint32_t tmpVal = 0;
    
    CHECK_PARAM((div<=0x3FF));
    
    /* lp rtc_en=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_E902_RTC_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    /* lp rtc_div=div */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_E902_RTC_DIV,div);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    /* lp rtc_en=0/1 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG8);
    if(enable){
        tmpVal = BL_SET_REG_BIT(tmpVal,PDS_E902_RTC_EN);
    }else{
        tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_E902_RTC_EN);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG8,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set LP reset address
 *
 * @param  addr: address
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_LP_Reset_Address(uint32_t addr)
{
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG13,addr);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  power on mm system
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Power_On_MM_System(void)
{
    uint32_t tmpVal = 0;
    
    /* mm_pwr_off=0, [1]=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_FORCE_MM_PWR_OFF);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    
    /* wait > 30us */
    ARCH_Delay_US(45);
    
    /* mm_iso_en=0, [5]=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_FORCE_MM_ISO_EN);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    
    /* mm_gate_clk=0, [17]=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_FORCE_MM_GATE_CLK);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    
    /* mm_stby=0, [13]=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_FORCE_MM_MEM_STBY);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    
    /* mm_reset=0, [9]=0 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CTL2);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_FORCE_MM_PDS_RST);
    BL_WR_REG(PDS_BASE,PDS_CTL2,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Enable cache
 *
 * @param  wayDisable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_LP_Cache_Enable_Set(uint8_t wayDisable)
{
    PDS_LP_Cache_Flush(wayDisable);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  L1C cache write set
 *
 * @param  wtEn: L1C write through enable
 * @param  wbEn: L1C write back enable
 * @param  waEn: L1C write allocate enable
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_LP_Cache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    if(wtEn){
        tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_WT_EN);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WT_EN);
    }
    if(wbEn){
        tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_WB_EN);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WB_EN);
    }
    if(waEn){
        tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_WA_EN);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WA_EN);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
}

/****************************************************************************//**
 * @brief  Flush cache
 *
 * @param  wayDisable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_LP_Cache_Flush(uint8_t wayDisable)
{
    uint32_t tmpVal;
    uint32_t cnt=0;
    uint8_t finWayDisable=0;
    
    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WAY_DIS);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CNT_EN);
    finWayDisable=BL_GET_REG_BITS_VAL(tmpVal,PDS_L1C_WAY_DIS);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    /*Set Tag RAM to zero */
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_INVALID_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_INVALID_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /* Polling for invalid done */
    do{
        ARCH_Delay_US(1);
        cnt++;
        tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    }while(!BL_IS_REG_BIT_SET(tmpVal,PDS_L1C_INVALID_DONE)&&cnt<100);

    /* data flush */
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    /* Left space for hardware change status*/
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /* Polling for flush done */
    do{
        ARCH_Delay_US(1);
        cnt++;
        tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    }while(!BL_IS_REG_BIT_SET(tmpVal,PDS_L1C_FLUSH_DONE)&&cnt<100);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_FLUSH_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_BYPASS);
    tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CNT_EN);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    if(wayDisable!=0xff){
        finWayDisable=wayDisable;
    }

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_WAY_DIS);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal|=(finWayDisable<<PDS_L1C_WAY_DIS_POS);
    /* If way disable is 0x0f, cacheable can't be set */
    if(finWayDisable!=0x0f){
       tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }else{
       tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Get cache hit count
 *
 * @param  hitCountLow: hit count low 32 bits pointer
 * @param  hitCountHigh: hit count high 32 bits pointer
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_LP_Cache_Hit_Count_Get(uint32_t *hitCountLow,uint32_t *hitCountHigh)
{
    *hitCountLow=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG3);
    *hitCountHigh=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG4);
}

/****************************************************************************//**
 * @brief  Get cache miss count
 *
 * @param  None
 *
 * @return Cache miss count
 *
*******************************************************************************/
uint32_t ATTR_TCM_SECTION PDS_LP_Cache_Miss_Count_Get(void)
{
    return BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG5);
}

/****************************************************************************//**
 * @brief  Disable read from flash or psram with cache
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION PDS_LP_Cache_Read_Disable(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
}

/****************************************************************************//**
 * @brief  wrap set
 *
 * @param  wrap: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_LP_Set_Cache_Wrap(BL_Fun_Type wrap)
{
    uint32_t tmpVal = 0;
    uint8_t cacheEn = 0;

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    cacheEn = BL_IS_REG_BIT_SET(PDS_BASE,PDS_L1C_CACHEABLE);
    if(cacheEn != 0){
        tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
        BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    }

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    if(wrap == ENABLE){
        tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_WRAP_DIS);
    }else{
        tmpVal=BL_SET_REG_BIT(tmpVal,PDS_WRAP_DIS);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    if(cacheEn != 0){
        tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
        BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  cache way disable set
 *
 * @param  disableVal: cache way disable value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_LP_Set_Cache_Way_Disable(uint8_t disableVal)
{
    uint32_t tmpVal = 0;

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    tmpVal=BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG2);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_L1C_WAY_DIS,disableVal);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    if(disableVal!=0x0f){
       tmpVal=BL_SET_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }else{
       tmpVal=BL_CLR_REG_BIT(tmpVal,PDS_L1C_CACHEABLE);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG2,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Enable power down sleep
 *
 * @param  cfg: power down sleep configuration 1
 * @param  cfg4: power down sleep configuration 2
 * @param  pdsSleepCnt: power down sleep count cycle
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Enable(PDS_CTL_Type *cfg,PDS_CTL4_Type *cfg4,uint32_t pdsSleepCnt)
{
    
    /* PDS sleep time 0 <=> sleep forever */
    /* PDS sleep time 1~PDS_WARMUP_LATENCY_CNT <=> error */
    /* PDS sleep time >PDS_WARMUP_LATENCY_CNT <=> correct */
    if(!pdsSleepCnt){
        cfg->sleepForever = 1;
    }else if((pdsSleepCnt)&&(pdsSleepCnt<=PDS_WARMUP_LATENCY_CNT)){
        return ERROR;
    }else{
        BL_WR_REG(PDS_BASE,PDS_TIME1,pdsSleepCnt-PDS_WARMUP_LATENCY_CNT);
    }
    
    /* PDS_CTL4 config */
    BL_WR_REG(PDS_BASE,PDS_CTL4,*(uint32_t *)cfg4);
    
    /* PDS_CTL config */
    if(cfg->pdsStart){
        BL_WR_REG(PDS_BASE,PDS_CTL,(*(uint32_t *)cfg&~(1<<0)));
        BL_WR_REG(PDS_BASE,PDS_CTL,(*(uint32_t *)cfg|(1<<0)));
    }else{
        BL_WR_REG(PDS_BASE,PDS_CTL,*(uint32_t *)cfg);
    }
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  power down sleep force configure
 *
 * @param  cfg2: power down sleep force configuration 1
 * @param  cfg3: power down sleep force configuration 2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Force_Config(PDS_CTL2_Type *cfg2,PDS_CTL3_Type *cfg3)
{
    /* PDS_CTL2 config */
    BL_WR_REG(PDS_BASE,PDS_CTL2,*(uint32_t *)cfg2);
    
    /* PDS_CTL3 config */
    BL_WR_REG(PDS_BASE,PDS_CTL3,*(uint32_t *)cfg3);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  power down sleep ram configure
 *
 * @param  ramCfg: power down sleep force ram configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg)
{
    if(NULL==ramCfg){
        return ERROR;
    }
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  power down sleep force configure
 *
 * @param  defaultLvCfg: power down sleep default level configuration
 * @param  ramCfg: ram configuration
 * @param  pdsSleepCnt: power down sleep time count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg,PDS_RAM_CFG_Type *ramCfg,uint32_t pdsSleepCnt)
{
    /* RAM config need fix after ECO */
    PDS_RAM_Config(ramCfg);
    PDS_Force_Config((PDS_CTL2_Type *)&(defaultLvCfg->pdsCtl2),(PDS_CTL3_Type *)&(defaultLvCfg->pdsCtl3));
    PDS_Enable((PDS_CTL_Type *)&(defaultLvCfg->pdsCtl),(PDS_CTL4_Type *)&(defaultLvCfg->pdsCtl4),pdsSleepCnt);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  power down sleep int mask
 *
 * @param  intType: PDS int type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_IntMask(PDS_INT_Type intType,BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_INT);
    if(intMask!=UNMASK){
        tmpVal = tmpVal|(1<<(intType+PDS_INT_MASK_BIT_OFFSET));
    }else{
        tmpVal = tmpVal&~(1<<(intType+PDS_INT_MASK_BIT_OFFSET));
    }
    BL_WR_REG(PDS_BASE,PDS_INT,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  get power down sleep int status
 *
 * @param  intType: PDS int type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type PDS_Get_IntStatus(PDS_INT_Type intType)
{
    return (BL_RD_REG(PDS_BASE,PDS_INT)&(1<<intType))?SET:RESET;
}

/****************************************************************************//**
 * @brief  clear power down sleep int status
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_IntClear(void)
{
    uint32_t tmpVal = 0;
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE,PDS_INT,tmpVal);
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal,PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE,PDS_INT,tmpVal);
    
    tmpVal = BL_RD_REG(PDS_BASE,PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal,PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE,PDS_INT,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  get power down sleep RF status
 *
 * @param  None
 *
 * @return PDS RF status
 *
*******************************************************************************/
PDS_RF_STS_Type PDS_Get_PdsRfStstus(void)
{
    return (PDS_RF_STS_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE,PDS_STAT),PDS_RO_PDS_RF_STATE);
}

/****************************************************************************//**
 * @brief  get power down sleep status
 *
 * @param  None
 *
 * @return PDS status
 *
*******************************************************************************/
PDS_STS_Type PDS_Get_PdsStstus(void)
{
    return (PDS_STS_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE,PDS_STAT),PDS_RO_PDS_STATE);
}

/****************************************************************************//**
 * @brief  Install PDS interrupt callback function
 *
 * @param  intType: PDS int type
 * @param  cbFun: cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type PDS_Int_Callback_Install(PDS_INT_Type intType,intCallback_Type* cbFun)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(PDS_WAKEUP_IRQn,PDS_WAKEUP_IRQHandler);
#endif
    
    pdsIntCbfArra[intType] = cbFun;
    
    return SUCCESS;
}
#endif

/****************************************************************************//**
 * @brief  Trim RC32M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Trim_RC32M(void)
{
    Efuse_Ana_RC32M_Trim_Type trim;
    int32_t tmpVal = 0;
    
    EF_Ctrl_Read_RC32M_Trim(&trim);
    if(trim.trimRc32mExtCodeEn){
        if(trim.trimRc32mCodeFrExtParity==EF_Ctrl_Get_Trim_Parity(trim.trimRc32mCodeFrExt,8)){
            tmpVal=BL_RD_REG(PDS_BASE,PDS_RC32M_CTRL0);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,PDS_RC32M_CODE_FR_EXT,trim.trimRc32mCodeFrExt);
            tmpVal=BL_SET_REG_BIT(tmpVal,PDS_RC32M_EXT_CODE_EN);
            BL_WR_REG(PDS_BASE,PDS_RC32M_CTRL0,tmpVal);
            ARCH_Delay_US(2);
            return SUCCESS;
        }
    }
    
    return ERROR;
}

/****************************************************************************//**
 * @brief  Select RC32M as PLL ref source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_RC32M_As_PLL_Ref(void)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Select XTAL as PLL ref source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_XTAL_As_PLL_Ref(void)
{
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Power down sleep wake up interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void PDS_WAKEUP_IRQHandler(void)
{
    for(PDS_INT_Type intType=PDS_INT_WAKEUP;intType<PDS_INT_MAX;intType++){
        if(PDS_Get_IntStatus(intType)&&(pdsIntCbfArra[intType]!=NULL)){
            pdsIntCbfArra[intType]();
        }
    }
    
    PDS_IntClear();
}
#endif

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL808_Peripheral_Driver */
