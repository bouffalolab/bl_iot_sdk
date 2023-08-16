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

#include "bl808_clock.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CLOCK
 *  @{
 */

/** @defgroup  CLOCK_Private_Macros
 *  @{
 */

/*@} end of group CLOCK_Private_Macros */

/** @defgroup  CLOCK_Private_Types
 *  @{
 */

/*@} end of group CLOCK_Private_Types */

/** @defgroup  CLOCK_Private_Variables
 *  @{
 */

/*@} end of group CLOCK_Private_Variables */

/** @defgroup  CLOCK_Global_Variables
 *  @{
 */

/*@} end of group CLOCK_Global_Variables */

/** @defgroup  CLOCK_Private_Fun_Declaration
 *  @{
 */

/*@} end of group CLOCK_Private_Fun_Declaration */

/** @defgroup  CLOCK_Private_Functions
 *  @{
 */

/*@} end of group CLOCK_Private_Functions */

/** @defgroup  CLOCK_Public_Functions
 *  @{
 */

static uint32_t ATTR_CLOCK_SECTION Clock_Get_WiFi_PLL_Output(uint32_t pllOut)
{
    return pllOut;
}

static uint32_t ATTR_CLOCK_SECTION Clock_Get_CPU_PLL_Output(uint32_t pllOut)
{
    float coe=1.0;

    return pllOut*coe;
}

static uint32_t ATTR_CLOCK_SECTION Clock_Get_ETH_PLL_Output(uint32_t pllOut)
{
    float coe=1.0;

    return pllOut*coe;
}

static uint32_t ATTR_CLOCK_SECTION Clock_Xtal_Output(void)
{
    uint8_t xtalType=0;

    if(HBN_Get_Xtal_Type(&xtalType)==SUCCESS){
        switch (xtalType)
        {
        case GLB_PLL_XTAL_NONE:
            return 0;
        case GLB_PLL_XTAL_24M:
            return 24*1000*1000;;
        case GLB_PLL_XTAL_32M:
            return 32*1000*1000;;
        case GLB_PLL_XTAL_38P4M:
            return 38.4*1000*1000;;
        case GLB_PLL_XTAL_40M:
            return 40*1000*1000;;
        case GLB_PLL_XTAL_26M:
            return 26*1000*1000;;
        case GLB_PLL_XTAL_RC32M:
            return 32*1000*1000;;
        default:
            return 0;
        }
    }else{
        return 40*1000*1000;
    }
}

static uint32_t ATTR_CLOCK_SECTION Clock_XClk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* select RC32M */
        return 32*1000*1000;
    }else if(sel==1){
        /* select XTAL */
        return Clock_Xtal_Output();
    }else{
        return 0;
    }
}

static uint32_t ATTR_CLOCK_SECTION Clock_F32k_Mux_Output(uint8_t sel)
{
    uint32_t tmpVal;
    uint32_t div=0;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG0);
    div=BL_GET_REG_BITS_VAL(tmpVal,GLB_DIG_32K_DIV);

    if(sel==0){
        /* select RC32K */
        return 32*1000;
    }else if(sel==1){
        /* select xtal 32K */
        return 32*1000;
    }else{
        return Clock_Xtal_Output()/(div+1);
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_F32k_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(HBN_BASE,HBN_GLB);
    return BL_GET_REG_BITS_VAL(tmpVal,HBN_F32K_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_320M_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* ETH PLL 320M */
        return Clock_Get_ETH_PLL_Output(320*1000*1000);
    }else if(sel==1){
        /* CPU PLL 320M */
        return Clock_Get_CPU_PLL_Output(300*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Muxpll_320M_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_320M_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_240M_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* WiFi PLL 240M */
        return Clock_Get_WiFi_PLL_Output(240*1000*1000);
    }else if(sel==1){
        /* CPU PLL 256M */
        return Clock_Get_CPU_PLL_Output(256*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Muxpll_240M_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_240M_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_200M_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* ETH PLL 200M */
        return Clock_Get_ETH_PLL_Output(200*1000*1000);
    }else if(sel==1){
        /* CPU PLL 200M */
        return Clock_Get_CPU_PLL_Output(200*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Muxpll_200M_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_200M_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_160M_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* ETH PLL 160M */
        return Clock_Get_ETH_PLL_Output(160*1000*1000);
    }else if(sel==1){
        /* CPU PLL 160M */
        return Clock_Get_CPU_PLL_Output(160*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Muxpll_160M_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_160M_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_54M_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* ETH PLL 53M */
        return Clock_Get_ETH_PLL_Output(53*1000*1000);
    }else if(sel==1){
        /* CPU PLL 64M */
        return Clock_Get_CPU_PLL_Output(64*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Muxpll_54M_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_54M_SEL);
}

static uint32_t ATTR_CLOCK_SECTION Clock_MCU_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* wifi PLL 160M */
        return Clock_Get_WiFi_PLL_Output(160*1000*1000);
    }else if(sel==1){
        /* wifi PLL 192M */
        return Clock_Get_WiFi_PLL_Output(192*1000*1000);
    }else if(sel==2){
        /* wifi PLL 240M */
        return Clock_Get_WiFi_PLL_Output(240*1000*1000);
    }else{
        /* 320M output */
        return Clock_320M_Clk_Mux_Output(Clock_Get_Muxpll_320M_Sel_Val());
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_MCU_XClk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(HBN_BASE,HBN_GLB);
    tmpVal=BL_GET_REG_BITS_VAL(tmpVal,HBN_ROOT_CLK_SEL);
    
    return (tmpVal&0x1);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_MCU_Root_Clk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(HBN_BASE,HBN_GLB);
    tmpVal=BL_GET_REG_BITS_VAL(tmpVal,HBN_ROOT_CLK_SEL);
    
    return ((tmpVal>>1)&0x1);
}

static uint32_t ATTR_CLOCK_SECTION Clock_MCU_Root_Clk_Mux_Output(uint8_t sel)
{
    uint32_t tmpVal;

    if(sel==0){
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());
    }else if(sel==1){
        /* select PLL */
        tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
        sel = BL_GET_REG_BITS_VAL(tmpVal,PDS_REG_PLL_SEL);
        return Clock_MCU_Clk_Mux_Output(sel);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_MCU_HClk_Div_Val(void)
{
    uint32_t tmpVal;
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_HCLK_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_MCU_BClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_MCU_BCLK_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_Peri_BClk_Div_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_BCLK_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_LP_Clk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG7);
    return BL_GET_REG_BITS_VAL(tmpVal,PDS_REG_PICO_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_DSP_XClk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal=BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL);
    
    return (tmpVal&0x1);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_DSP_Root_Clk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal=BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL);
    
    return ((tmpVal>>1)&0x1);
}

static uint32_t ATTR_CLOCK_SECTION Clock_DSP_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* 240M */
        return Clock_240M_Clk_Mux_Output(Clock_Get_Muxpll_240M_Sel_Val());
    }else if(sel==1){
        /* 320M  */
        return Clock_320M_Clk_Mux_Output(Clock_Get_Muxpll_320M_Sel_Val());
    }else if(sel==2){
        /* ETH PLL 400M */
        return Clock_Get_ETH_PLL_Output(400*1000*1000);
    }else if(sel==3){
        /* CPU PLL 640M */
        return Clock_Get_CPU_PLL_Output(640*1000*1000);
    }else{
        return 0;
    }
}

static uint32_t ATTR_CLOCK_SECTION Clock_DSP_Root_Clk_Mux_Output(uint8_t sel)
{
    uint32_t tmpVal;

    if(sel==0){
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_DSP_XClk_Sel_Val());
    }else if(sel==1){
        /* select PLL */
        tmpVal = BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
        sel = BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CPU_CLK_SEL);
        return Clock_DSP_Clk_Mux_Output(sel);
    }else{
        return 0;
    }
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_DSP_HClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CPU_CLK_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_DSP_BClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK2X_DIV);
}

static uint8_t ATTR_CLOCK_SECTION Clock_Get_MM_BClk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK1X_DIV);
}

/****************************************************************************//**
 * @brief  Get System Clock
 *
 * @param  type: System clock type
 *
 * @return System clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION Clock_System_Clock_Get(BL_System_Clock_Type type)
{
    uint32_t clock=0;
    uint32_t div=0;
    
   switch(type){
        case BL_SYSTEM_CLOCK_MCU_XCLK:
            /*!< MCU xclk clock */
            return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());

        case BL_SYSTEM_CLOCK_MCU_ROOT_CLK:
            /*!< MCU root clock */
            return Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val());

        case BL_SYSTEM_CLOCK_MCU_CLK:
            /*!< MCU Fast clock/CPU clock */
            clock=Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val());
            div=Clock_Get_MCU_HClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_MCU_BCLK:
            /*!< MCU BUS clock */
            clock=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            div=Clock_Get_MCU_BClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_PERI_BCLK:
            /*!< MCU peri BUS clock */
            clock=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_BCLK);
            div=Clock_Get_Peri_BClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_DSP_XCLK:
            /*!< DSP xclk clock */
            return Clock_XClk_Mux_Output(Clock_Get_DSP_XClk_Sel_Val());

        case BL_SYSTEM_CLOCK_DSP_ROOT_CLK:
            /*!< DSP root clock */
            return Clock_DSP_Root_Clk_Mux_Output(Clock_Get_DSP_Root_Clk_Sel_Val());

        case BL_SYSTEM_CLOCK_DSP_CLK:
            /*!< DSP Fast clock/CPU clock */
            clock=Clock_DSP_Root_Clk_Mux_Output(Clock_Get_DSP_Root_Clk_Sel_Val());
            div=Clock_Get_DSP_HClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_DSP_BCLK:
            /*!< DSP BUS clock */
            clock=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            div=Clock_Get_DSP_BClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_MM_BCLK:
            /*!< DSP mm BUS clock */
            clock=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_BCLK);
            div=Clock_Get_MM_BClk_Div_Val();
            return clock/(div+1);

        case BL_SYSTEM_CLOCK_LP_CLK:
            /*!< LP clock */
            clock=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_PERI_BCLK);
            div=Clock_Get_LP_Clk_Div_Val();
            return clock/(div+1);
    
        case BL_SYSTEM_CLOCK_F32K:
            /*!< F32K clock */            
            return Clock_F32k_Mux_Output(Clock_Get_F32k_Sel_Val());

        case BL_SYSTEM_CLOCK_XCLK:
            /*!< XCLK:RC32M or XTAL */
            return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());

        case BL_SYSTEM_CLOCK_XTAL:
            /*!< XTAL clock */
            return Clock_Xtal_Output();

        default:
            return 0;
    }
}

static uint32_t Clock_EMI_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* CPU 213M */
        return Clock_Get_CPU_PLL_Output(213*1000*1000);
    }else if(sel==1){
        /* 240M  */
        return Clock_240M_Clk_Mux_Output(Clock_Get_Muxpll_240M_Sel_Val());
    }else if(sel==2){
        /* 320M */
        return Clock_320M_Clk_Mux_Output(Clock_Get_Muxpll_320M_Sel_Val());
    }else if(sel==3){
        /* ETH PLL 400M */
        return Clock_Get_ETH_PLL_Output(400*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t Clock_Get_EMI_Clk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_EMI_CFG0);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_EMI_CLK_DIV);
}

static uint8_t Clock_Get_EMI_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_EMI_CFG0);
    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_EMI_CLK_SEL);
}

uint32_t Clock_Get_EMI_Clk(void)
{
    uint32_t clock=Clock_EMI_Clk_Mux_Output(Clock_Get_EMI_Clk_Sel_Val());
    uint32_t div=Clock_Get_EMI_Clk_Div_Val();

    return clock/(div+1);
}

static uint32_t Clock_ISP_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* 160M */
        return Clock_160M_Clk_Mux_Output(Clock_Get_Muxpll_160M_Sel_Val());
    }else if(sel==1){
        /* ETH PLL 400M */
        return Clock_Get_ETH_PLL_Output(400*1000*1000);
    }else if(sel==2){
        /* 240M  */
        return Clock_240M_Clk_Mux_Output(Clock_Get_Muxpll_240M_Sel_Val());
    }else if(sel==3){
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());
    }else{
        return 0;
    }
}

static uint8_t Clock_Get_ISP_Clk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_ISP_SUB_SYS);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_ISP_CLK_DIV);
}

static uint8_t Clock_Get_ISP_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_ISP_SUB_SYS);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_ISP_CLK_SEL);
}

uint32_t Clock_Get_ISP_Clk(void)
{
    uint32_t clock=Clock_ISP_Clk_Mux_Output(Clock_Get_ISP_Clk_Sel_Val());
    uint32_t div=Clock_Get_ISP_Clk_Div_Val();

    return clock/(div+1);
}

static uint32_t Clock_BLAI_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* 160M */
        return Clock_160M_Clk_Mux_Output(Clock_Get_Muxpll_160M_Sel_Val());
    }else if(sel==1){
        /* 240M  */
        return Clock_240M_Clk_Mux_Output(Clock_Get_Muxpll_240M_Sel_Val());
    }else if(sel==2){
        /* ETH PLL 267M */
        return Clock_Get_ETH_PLL_Output(267*1000*1000);
    }else if(sel==3){
        /* 320M */
        return Clock_320M_Clk_Mux_Output(Clock_Get_Muxpll_320M_Sel_Val());
    }else{
        return 0;
    }
}

static uint8_t Clock_Get_BLAI_Clk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CNN_CLK_DIV);
}

static uint8_t Clock_Get_BLAI_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CNN_CLK_SEL);
}

uint32_t Clock_Get_BLAI_Clk(void)
{
    uint32_t clock=Clock_BLAI_Clk_Mux_Output(Clock_Get_BLAI_Clk_Sel_Val());
    uint32_t div=Clock_Get_BLAI_Clk_Div_Val();

    return clock/(div+1);
}

static uint32_t Clock_Display_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* 54M */
        return Clock_54M_Clk_Mux_Output(Clock_Get_Muxpll_54M_Sel_Val());
    }else if(sel==1){
        /* 160M */
        return Clock_160M_Clk_Mux_Output(Clock_Get_Muxpll_160M_Sel_Val());
    }else if(sel==2){
        /* 240M  */
        return Clock_240M_Clk_Mux_Output(Clock_Get_Muxpll_240M_Sel_Val());
    }else if(sel==3){
        /* ETH PLL 267M */
        return Clock_Get_ETH_PLL_Output(267*1000*1000);
    }else{
        return 0;
    }
}

static uint8_t Clock_Get_Display_Clk_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_ISP_SUB_SYS);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_DP_CLK_DIV);
}

static uint8_t Clock_Get_Display_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_ISP_SUB_SYS);
    return BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_REG_DP_CLK_SEL);
}

uint32_t Clock_Get_Display_Clk(void)
{
    uint32_t clock=Clock_Display_Clk_Mux_Output(Clock_Get_Display_Clk_Sel_Val());
    uint32_t div=Clock_Get_Display_Clk_Div_Val();

    return clock/(div+1);
}

static uint32_t Clock_UART_Clk_Mux_Output(uint8_t sel)
{
    uint32_t div=0;

    if(sel==0){
        /* select mcu bclk */
        div=Clock_Get_MCU_BClk_Div_Val(); 
        return Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val())/(div+1);
    }else if(sel==1){
        /* select wifi 160Mkz */
        return Clock_Get_WiFi_PLL_Output(160*1000*1000);
    }else{
        /* select XCLK */  
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());       
    }
}

static uint8_t Clock_Get_UART_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_UART_CFG0);

    return ((BL_GET_REG_BITS_VAL(tmpVal,GLB_HBN_UART_CLK_SEL2)<<1) | BL_GET_REG_BITS_VAL(tmpVal,GLB_HBN_UART_CLK_SEL));
}

static uint8_t Clock_Get_UART_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_UART_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_UART_CLK_DIV);
}

static uint8_t Clock_Get_SF_Clk_Sel2_Val(void)
{
    uint32_t tmpVal; 

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SF_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_SF_CLK_SEL2);
}

static uint32_t Clock_SF_SEL2_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* select wifi 120Mkz */
        return Clock_Get_WiFi_PLL_Output(120*1000*1000);
    }else if(sel==1){
        /* select xtal */
        return Clock_Xtal_Output();
    }
    else{
        /* select wifi 48Mkz */
        return Clock_Get_WiFi_PLL_Output(48*1000*1000);
    }
}

static uint32_t Clock_SF_SEL_Clk_Mux_Output(uint8_t sel)
{
    uint32_t div=0;

    if(sel==0){
        /* select sf sel2 */
        return Clock_SF_SEL2_Clk_Mux_Output(Clock_Get_SF_Clk_Sel2_Val());
    }else if(sel==1){
        /* select clk_80m */
        return (80*1000*1000);
    }else if(sel==2){
        /* select bclk */
        div=Clock_Get_Peri_BClk_Div_Val();
        return Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val())/(div+1);       
    }
    else{
        /* select wifi 96Mkz */
        return Clock_Get_WiFi_PLL_Output(96*1000*1000);
    }
}

static uint8_t Clock_Get_SF_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SF_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_SF_CLK_SEL);
}

static uint8_t Clock_Get_SF_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SF_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_SF_CLK_DIV);
}

static uint32_t Clock_SPI_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* select wifi 160Mkz */
        return Clock_Get_WiFi_PLL_Output(160*1000*1000);
    }else{
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());       
    }
}

static uint8_t Clock_Get_SPI_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SPI_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_SPI_CLK_SEL);
}

static uint8_t Clock_Get_SPI_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SF_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_SPI_CLK_DIV);
}

static uint32_t Clock_I2C_Clk_Mux_Output(uint8_t sel)
{
    uint32_t div=0;

    if(sel==0){
        /* select bclk */
        div=Clock_Get_Peri_BClk_Div_Val();
        return Clock_MCU_Root_Clk_Mux_Output(Clock_Get_MCU_Root_Clk_Sel_Val())/(div+1);
    }else{
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());       
    }
}

static uint8_t Clock_Get_I2C_Clk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_I2C_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_I2C_CLK_SEL);
}

static uint8_t Clock_Get_I2C_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_I2C_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_I2C_CLK_DIV);
}

static uint32_t Clock_GPADC_PIR_DISABLE_Clk_Mux_Output(uint8_t sel)
{

    if(sel==0){
        /* audio_pll_clk:24.576MHz */
        return (24576 * 1000);
    }else{
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());      
    }
}

static uint8_t Clock_Get_GPADC_Clk_Sel_Val(void)
{
    uint32_t tmpVal;
    
    tmpVal=BL_RD_REG(GLB_BASE,GLB_ADC_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_GPADC_32M_CLK_SEL);
}

static uint8_t Clock_Get_GPADC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_ADC_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_GPADC_32M_CLK_DIV);
}

static uint32_t Clock_GPADC_Clk_Mux_Output(uint8_t en)
{
    uint32_t div=0;

    if(en==1){
        /* pir enable: f32k bclk */
        return Clock_F32k_Mux_Output(Clock_Get_F32k_Sel_Val());
    }else{
        /* pir disable */
        div=Clock_Get_GPADC_Div_Val();
        return Clock_GPADC_PIR_DISABLE_Clk_Mux_Output(Clock_Get_GPADC_Clk_Sel_Val())/(div+1);       
    }
}

static uint32_t Clock_ADC_Clk_Mux_Output()
{
    /* audio_pll_clk:24.576MHz */
    return (24576 * 1000);
}

static uint8_t Clock_Get_ADC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_AUDIO_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_AUDIO_ADC_CLK_DIV);
}

static uint8_t Clock_Get_GPADC_Clk_PIR_Val()
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(HBN_BASE,HBN_PIR_CFG);

    return BL_GET_REG_BITS_VAL(tmpVal,HBN_PIR_EN);
}

static uint32_t Clock_GPDAC_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* audio_pll_clk:24.576MHz */
        return (24576 * 1000);
    }else if(sel==1){
        /* select wifi 32Mkz */
        return Clock_Get_WiFi_PLL_Output(32*1000*1000);
    }else{
        /* select XCLK */
        return Clock_XClk_Mux_Output(Clock_Get_MCU_XClk_Sel_Val());      
    }
}

static uint8_t Clock_Get_GPDAC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_DIG_512K_DIV);
}

static uint8_t Clock_Get_GPDAC_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_DIG_CLK_SRC_SEL);
}

static uint32_t Clock_DAC_Clk_Mux_Output()
{
    /* audio_pll_clk:24.576MHz */
    return (24576 * 1000);
}

static uint8_t Clock_Get_DAC_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_AUDIO_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_AUDIO_DAC_CLK_DIV);
}

static uint32_t Clock_USB_Clk_Mux_Output()
{      
    /* select wifi 48Mkz */
    return Clock_Get_WiFi_PLL_Output(48*1000*1000);
    
}

static uint32_t Clock_SDH_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* select wifi 96Mkz */
        return Clock_Get_WiFi_PLL_Output(96*1000*1000);
    }else
        /* 200M output */
        return Clock_200M_Clk_Mux_Output(Clock_Get_Muxpll_200M_Sel_Val());
}

static uint8_t Clock_Get_SDH_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SDH_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_SDH_CLK_SEL);
}

static uint8_t Clock_Get_SDH_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_SDH_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_SDH_CLK_DIV);
}

static uint32_t Clock_PSRAM_Clk_Mux_Output(uint8_t sel)
{
    if(sel==0){
        /* ETH PLL 267M */
        return Clock_Get_ETH_PLL_Output(267*1000*1000);
    }else if(sel==1){
        /* ETH PLL 320M */
        return Clock_Get_ETH_PLL_Output(320*1000*1000);
    }else if(sel==2){
        /* ETH PLL 400M */
        return Clock_Get_ETH_PLL_Output(400*1000*1000);
    }else{
        /* ETH PLL 800M */
        return Clock_Get_ETH_PLL_Output(800*1000*1000);       
    }
}

static uint8_t Clock_Get_PSRAMA_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_PSRAM_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_PSRAMA_CLK_SEL);
}

static uint8_t Clock_Get_PSRAMA_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_PSRAM_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_PSRAMA_CLK_DIV);
}

static uint8_t Clock_Get_PSRAMB_Clk_Sel_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_PSRAM_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_PSRAMB_CLK_SEL);
}

static uint8_t Clock_Get_PSRAMB_Div_Val(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_PSRAM_CFG0);

    return BL_GET_REG_BITS_VAL(tmpVal,GLB_REG_PSRAMB_CLK_DIV);
}

/****************************************************************************//**

 * @brief  Get Peripheral1 Clock
 *
 * @param  type: Peripheral1 clock type
 *
 * @return Peripheral1 clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION Clock_Peripheral1_Clock_Get(BL_AHB_Slave1_Type type)
{
    uint32_t clock=0;
    uint32_t div=0;

    switch(type){
        /*!< uart0 clock */
        case BL_AHB_SLAVE1_UART0:
        	ATTR_FALLTHROUGH();
        /*!< uart1 clock */
        case BL_AHB_SLAVE1_UART1:
        	ATTR_FALLTHROUGH();
        /*!< uart2 clock */
        case BL_AHB_SLAVE1_UART2:
            clock=Clock_UART_Clk_Mux_Output(Clock_Get_UART_Clk_Sel_Val());
            div=Clock_Get_UART_Div_Val();
            return clock/(div+1);

        /*!< sflash clock */
        case BL_AHB_SLAVE1_SF_CTRL:
            clock=Clock_SF_SEL_Clk_Mux_Output(Clock_Get_SF_Clk_Sel_Val());
            div=Clock_Get_SF_Div_Val();
            return clock/(div+1);

        /*!< spi clock */
        case BL_AHB_SLAVE1_SPI:
            clock=Clock_SPI_Clk_Mux_Output(Clock_Get_SPI_Clk_Sel_Val());
            div=Clock_Get_SPI_Div_Val();
            return clock/(div+1);
        
        /*!< spi clock */
        case BL_AHB_SLAVE1_I2C:
            clock=Clock_I2C_Clk_Mux_Output(Clock_Get_I2C_Clk_Sel_Val());
            div=Clock_Get_I2C_Div_Val();
            return clock/(div+1);

        /*!< adc clock */
        case BL_AHB_SLAVE1_GPADC:
            return Clock_GPADC_Clk_Mux_Output(Clock_Get_GPADC_Clk_PIR_Val());

        /*!< dac clock */
        case BL_AHB_SLAVE1_GPDAC:
            clock=Clock_GPDAC_Clk_Mux_Output(Clock_Get_GPDAC_Clk_Sel_Val());
            div=Clock_Get_GPDAC_Div_Val();
            return clock/(div+1);

        default:
            return 0;
    }
}

/****************************************************************************//**

 * @brief  Get Peripheral2 Clock
 *
 * @param  type: Peripheral2 clock type
 *
 * @return Peripheral2 clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION Clock_Peripheral2_Clock_Get(BL_AHB_Slave2_Type type)
{
    uint32_t clock=0;
    uint32_t div=0;

    switch(type){
        /*!< usb clock */
        case BL_AHB_SLAVE2_EXT_USB:
            clock=Clock_USB_Clk_Mux_Output();

        /*!< sdh clock */
        case BL_AHB_SLAVE2_EXT_SDH:
            clock=Clock_SDH_Clk_Mux_Output(Clock_Get_SDH_Clk_Sel_Val());
            div=Clock_Get_SDH_Div_Val();
            return clock/(div+1);

        /*!< psram clock */
        case BL_AHB_SLAVE2_EXT_PSRAM0_CTRL:
            clock=Clock_PSRAM_Clk_Mux_Output(Clock_Get_PSRAMA_Clk_Sel_Val());
            div=Clock_Get_PSRAMA_Div_Val();
            return clock/(div+1);

        case BL_AHB_SLAVE2_EXT_PSRAM1_CTRL:
            clock=Clock_PSRAM_Clk_Mux_Output(Clock_Get_PSRAMB_Clk_Sel_Val());
            div=Clock_Get_PSRAMB_Div_Val();
            return clock/(div+1);

        default:
            return 0;        
    }
}

/****************************************************************************//**

 * @brief  Get Audio ADC Clock
 *
 * @return Audio ADC clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION Clock_Audio_ADC_Clock_Get(void)
{
    uint32_t clock=0;
    uint32_t div=0;

    clock=Clock_ADC_Clk_Mux_Output();
    div=Clock_Get_ADC_Div_Val();

    return clock/(div+1);
}

/****************************************************************************//**

 * @brief  Get Audio DAC Clock
 *
 * @return Audio DAC clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION Clock_Audio_DAC_Clock_Get(void)
{
    uint32_t clock=0;
    uint32_t div=0;

    clock=Clock_DAC_Clk_Mux_Output();
    div=Clock_Get_DAC_Div_Val();

    return clock/(div+1);
}

/****************************************************************************//**
 * @brief  get system core clock
 *
 * @param  None
 *
 * @return system core clock value
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION SystemCoreClockGet(void)
{
    uint32_t clockVal=0;
    
    switch(GLB_Get_Core_Type()){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            clockVal=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            clockVal=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            break;
        case GLB_CORE_ID_LP:
            clockVal=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
            break;
        default :
            clockVal=0;
            break;
    }
    clockVal=clockVal?clockVal:(32*1000*1000);
    
    return clockVal;
}

/****************************************************************************//**
 * @brief  mcu rtc reset
 *
 * @param  rstEn: hold reset or not
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION CPU_Set_MTimer_RST(uint8_t rstEn)
{
    uint32_t tmpVal=0;
    uint32_t address=0;
    
    switch(GLB_Get_Core_Type()){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            address=MM_MISC_BASE+MM_MISC_CPU_RTC_OFFSET;
            break;
        case GLB_CORE_ID_LP:
            address=PDS_BASE+PDS_CPU_CORE_CFG8_OFFSET;
            break;
        default :
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            break;
    }
    
    /* set reset */
    /* MCU RTC_RST is [30] */
    /* DSP RTC_RST is [30] */
    /* LP  RTC_RST is [30] */
    tmpVal=BL_RD_WORD(address);
    if(rstEn){
        tmpVal=BL_SET_REG_BIT(tmpVal,MCU_MISC_E906_RTC_RST);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,MCU_MISC_E906_RTC_RST);
    }
    BL_WR_WORD(address,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  mcu rtc reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION CPU_Reset_MTimer(void)
{
    CPU_Set_MTimer_RST(1);
    CPU_Set_MTimer_RST(0);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set mcu rtc clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION CPU_Set_MTimer_CLK(uint8_t enable,uint16_t div)
{
    uint32_t tmpVal=0;
    uint32_t address=0;
    
    CHECK_PARAM((div<=0x3FF));
    
    switch(GLB_Get_Core_Type()){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            address=MM_MISC_BASE+MM_MISC_CPU_RTC_OFFSET;
            break;
        case GLB_CORE_ID_LP:
            address=PDS_BASE+PDS_CPU_CORE_CFG8_OFFSET;
            break;
        default :
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            break;
    }
    
    /* disable rtc first */
    /* MCU RTC_EN is [31] */
    /* DSP RTC_EN is [31] */
    /* LP  RTC_EN is [31] */
    tmpVal=BL_RD_WORD(address);
    tmpVal=BL_CLR_REG_BIT(tmpVal,MCU_MISC_E906_RTC_EN);
    BL_WR_WORD(address,tmpVal);
    
    /* set div */
    /* MCU RTC_DIV is [9:0] */
    /* DSP RTC_DIV is [9:0] */
    /* LP  RTC_DIV is [9:0] */
    tmpVal=BL_RD_WORD(address);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,MCU_MISC_E906_RTC_DIV,div);
    BL_WR_WORD(address,tmpVal);
    
    /* enable or not */
    /* MCU RTC_EN is [31] */
    /* DSP RTC_EN is [31] */
    /* LP  RTC_EN is [31] */
    tmpVal=BL_RD_WORD(address);
    if(enable){
        tmpVal=BL_SET_REG_BIT(tmpVal,MCU_MISC_E906_RTC_EN);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,MCU_MISC_E906_RTC_EN);
    }
    BL_WR_WORD(address,tmpVal);
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  get cpu rtc source clock
 *
 * @param  None
 *
 * @return cpu rtc source clock
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION CPU_Get_MTimer_Source_Clock(void)
{
    uint32_t coreFreq=0;
    
    /* get cpu core clock */
    switch(GLB_Get_Core_Type()){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            break;
        case GLB_CORE_ID_LP:
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
            break;
        default :
            coreFreq = 0;
            break;
    }
    coreFreq = coreFreq?coreFreq:(32*1000*1000);
    
    return coreFreq;
}

/****************************************************************************//**
 * @brief  get mcu rtc clock
 *
 * @param  None
 *
 * @return mcu rtc counter clock
 *
*******************************************************************************/
uint32_t ATTR_CLOCK_SECTION CPU_Get_MTimer_Clock(void)
{
    uint32_t coreFreq=0;
    uint32_t address=0;
    uint32_t div=0;
    
    /* get cpu core clock */
    /* get mtimer clock div */
    switch(GLB_Get_Core_Type()){
        case GLB_CORE_ID_M0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_M1:
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_CLK);
            break;
        case GLB_CORE_ID_D0:
            ATTR_FALLTHROUGH();
        case GLB_CORE_ID_D1:
            address=MM_MISC_BASE+MM_MISC_CPU_RTC_OFFSET;
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_DSP_CLK);
            break;
        case GLB_CORE_ID_LP:
            address=PDS_BASE+PDS_CPU_CORE_CFG8_OFFSET;
            coreFreq = Clock_System_Clock_Get(BL_SYSTEM_CLOCK_LP_CLK);
            break;
        default :
            address=MCU_MISC_BASE+MCU_MISC_E906_RTC_OFFSET;
            coreFreq = 0;
            break;
    }
    /* MCU RTC_DIV is [9:0] */
    /* DSP RTC_DIV is [9:0] */
    /* LP  RTC_DIV is [9:0] */
    div=BL_GET_REG_BITS_VAL(BL_RD_WORD(address),MCU_MISC_E906_RTC_DIV);
    div += 1;
    coreFreq = coreFreq?coreFreq:(32*1000*1000);
    coreFreq = coreFreq/div;                            /* mtimer clock = cpu clock / mtimer div */
    
    return coreFreq;
}

/****************************************************************************//**
 * @brief  get mcu rtc counter
 *
 * @param  None
 *
 * @return mcu rtc counter
 *
*******************************************************************************/
uint64_t ATTR_CLOCK_SECTION CPU_Get_MTimer_Counter(void)
{
    volatile uint64_t tmpValLow,tmpValHigh,tmpValLow1,tmpValHigh1;
    uint8_t cnt=0;

    do{
        tmpValHigh=(uint64_t)csi_coret_get_valueh();
        tmpValLow=(uint64_t)csi_coret_get_value();
        tmpValLow1=(uint64_t)csi_coret_get_value();
        tmpValHigh1=(uint64_t)csi_coret_get_valueh();
        cnt++;
        if(cnt>4){
            break;
        }
    }while(tmpValLow>tmpValLow1||tmpValHigh!=tmpValHigh1);
    
    return (uint64_t)((tmpValHigh1<<32)+tmpValLow1);
}

/****************************************************************************//**
 * @brief  get mcu cycle
 *
 * @param  None
 *
 * @return mcu cycle
 *
*******************************************************************************/
uint64_t ATTR_CLOCK_SECTION CPU_Get_CPU_Cycle(void)
{
    volatile uint64_t tmpValLow,tmpValHigh,tmpValLow1,tmpValHigh1;
    uint8_t cnt=0;

    do{
        tmpValHigh=(uint64_t)__get_MCYCLEH();
        tmpValLow=(uint64_t)__get_MCYCLE();
        tmpValLow1=(uint64_t)__get_MCYCLE();
        tmpValHigh1=(uint64_t)__get_MCYCLEH();
        cnt++;
        if(cnt>4){
            break;
        }
    }while(tmpValLow>tmpValLow1||tmpValHigh!=tmpValHigh1);
    
    return (uint64_t)((tmpValHigh1<<32)+tmpValLow1);
}

/****************************************************************************//**
 * @brief  get mcu rtc counter in us
 *
 * @param  None
 *
 * @return mcu rtc counter in us
 *
*******************************************************************************/
uint64_t ATTR_CLOCK_SECTION CPU_Get_MTimer_US(void)
{
    uint32_t clk=CPU_Get_MTimer_Clock();
    uint64_t mtimer_counter= CPU_Get_MTimer_Counter();
    if(mtimer_counter==0){
        mtimer_counter=CPU_Get_CPU_Cycle();
        clk= SystemCoreClockGet();
    }    

    if(clk<1000*1000){
        return mtimer_counter*1000/(clk/1000);
    }else{
        return mtimer_counter/(clk/1000/1000);
    }
}

/****************************************************************************//**
 * @brief  get mcu rtc counter in ms
 *
 * @param  None
 *
 * @return mcu rtc counter in ms
 *
*******************************************************************************/
uint64_t ATTR_CLOCK_SECTION CPU_Get_MTimer_MS(void)
{
    uint32_t clk=CPU_Get_MTimer_Clock();
    uint64_t mtimer_counter= CPU_Get_MTimer_Counter();
    if(mtimer_counter==0){
        mtimer_counter=CPU_Get_CPU_Cycle();
        clk= SystemCoreClockGet();
    }

    return mtimer_counter/(clk/1000);
}

/****************************************************************************//**
 * @brief  mcu timer delay us
 *
 * @param  cnt: us
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION CPU_MTimer_Delay_US(uint32_t cnt)
{
    volatile uint64_t us1 = 0;
    volatile uint64_t us2 = 0;
    
    us1 = CPU_Get_MTimer_US();
    do{
        us2 = CPU_Get_MTimer_US();
    }while(((us2-us1)<(uint64_t)(cnt)));
    
    return SUCCESS;
}

/****************************************************************************//**
 * @brief  mcu timer delay ms
 *
 * @param  cnt: ms
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION CPU_MTimer_Delay_MS(uint32_t cnt)
{
    volatile uint64_t ms1 = 0;
    volatile uint64_t ms2 = 0;
    
    ms1 = CPU_Get_MTimer_MS();
    do{
        ms2 = CPU_Get_MTimer_MS();
    }while(((ms2-ms1)<(uint64_t)(cnt)));
    
    return SUCCESS;
}

/*@} end of group CLOCK_Public_Functions */

/*@} end of group CLOCK */

/*@} end of group BL808_Peripheral_Driver */
