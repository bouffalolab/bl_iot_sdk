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

#include "bl808_glb.h"
#include "bl808_clock.h"
#include "bl808_glb.h"
#include "bl808_aon.h"
#include "bl808_hbn.h"
#include "bl808_pds.h"
#include "cci_reg.h"
#include "glb_reg.h"
#include "bl808.h"
#define CCI_BASE         ((uint32_t)0x20008000)
//#include "bl60x_mixed.h"
//#include "bl60x_aon.h"
//#include "bl60x_hbn.h"

/** @addtogroup  BL60x_Peripheral_Driver
 *  @{
 */

/** @addtogroup  GLB
 *  @{
 */

/** @defgroup  GLB_Private_Macros
 *  @{
 */
#define GLB_GPIO_Get_Reg(pin)  (mmsys_misc_gpio_reg_t*)(MMSYS_MISC_BASE+GLB_GPIO_OFFSET+(pin/2)*4)
#define GLB_CLK_SET_DUMMY_WAIT       {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}


/* MIPI PLL Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_24M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_32M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_38P4M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_40M = {
    .clkpllRefdivRatio = 3,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION mipiPllBasicCfg_26M = {
    .clkpllRefdivRatio = 2,  /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2, /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 5,     /*!< pll_vco_speed */
    .clkpllEvenDivEn = 0,    /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 0, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION mipiPllCfg_1500M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                       /*!< XTAL is None */
    { &mipiPllBasicCfg_24M, 0x3E800 },   /*!< XTAL is 24M */
    { &mipiPllBasicCfg_32M, 0x46500 },   /*!< XTAL is 32M */
    { &mipiPllBasicCfg_38P4M, 0x3A980 }, /*!< XTAL is 38.4M */
    { &mipiPllBasicCfg_40M, 0x38400 },   /*!< XTAL is 40M */
    { &mipiPllBasicCfg_26M, 0x39B13 },   /*!< XTAL is 26M */
    { &mipiPllBasicCfg_32M, 0x46500 },   /*!< XTAL is RC32M */
};

/* uhs PLL 2100 Config*/
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_24M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_32M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_38P4M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_40M = {
    .clkpllRefdivRatio = 2,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_CFG_BASIC_Type ATTR_CLOCK_CONST_SECTION uhsPll2100BasicCfg_26M = {
    .clkpllRefdivRatio = 1,     /*!< pll_refdiv_ratio */
    .clkpllSelSampleClk = 2,    /*!< pll_sel_sample_clk */
    .clkpllVcoSpeed = 7,        /*!< pll_vco_speed */
    .clkpllEvenDivEn = 1,       /*!< pll_even_div_en */
    .clkpllEvenDivRatio = 2100/50, /*!< pll_even_div_ratio */
};
const GLB_MU_PLL_Cfg_Type ATTR_CLOCK_CONST_SECTION uhsPllCfg_2100M[GLB_XTAL_MAX] = {
    { NULL, 0x0 },                      /*!< XTAL is None */
    { &uhsPll2100BasicCfg_24M, 0x2BC00 },   /*!< XTAL is 24M */
    { &uhsPll2100BasicCfg_32M, 0x41A00 },   /*!< XTAL is 32M */
    { &uhsPll2100BasicCfg_38P4M, 0x36B00 }, /*!< XTAL is 38.4M */
    { &uhsPll2100BasicCfg_40M, 0x34800 },   /*!< XTAL is 40M */
    { &uhsPll2100BasicCfg_26M, 0x28627 },   /*!< XTAL is 26M */
    { &uhsPll2100BasicCfg_32M, 0x41A00 },   /*!< XTAL is RC32M */
};



/****************************************************************************//**
 * @brief  get core type
 *
 * @param  None
 *
 * @return core type
 *
*******************************************************************************/
GLB_CORE_ID_Type ATTR_CLOCK_SECTION GLB_Get_Core_Type(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_WORD(CORE_ID_ADDRESS);

    switch(tmpVal){
        case CORE_ID_M0:
            return GLB_CORE_ID_M0;
        case CORE_ID_M1:
            return GLB_CORE_ID_M1;
        case CORE_ID_D0:
            return GLB_CORE_ID_D0;
        case CORE_ID_D1:
            return GLB_CORE_ID_D1;
        case CORE_ID_LP:
            return GLB_CORE_ID_LP;
        default :
            return GLB_CORE_ID_INVALID;
    }

    return GLB_CORE_ID_INVALID;
}

static int GLB_Get_BClk_Div(GLB_PLL_CLK_Type fClk)
{
    /* keep BCLK <= 80MHz */
    if (fClk==GLB_PLL_CLK_160M)  return 1;  /* divider 2 */
    if (fClk==GLB_PLL_CLK_320M)  return 3;  /* divider 4 */
    if (fClk==GLB_PLL_CLK_400M)  return 4;  /* divider 5 */

    return 0;   /* divider 1 */
}

/****************************************************************************//**
 * @brief  Set System root clock
 *
 * @param  clkSel: root clock type selection
 *
 * @return None
 *
*******************************************************************************/
void ATTR_CLOCK_SECTION GLB_Set_Root_CLK(GLB_Root_CLK_Type clkSel)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_ROOT_CLK_TYPE(clkSel));

    tmpVal=BL_RD_REG(CLKRST_BASE,CLKRST_MM_CLK_CTRL_CPU);

    if(clkSel==GLB_ROOT_CLK_PLL_WITH_XTAL_ON){
        /* Enable PLL selection before select */
        tmpVal=BL_SET_REG_BIT(tmpVal,CLKRST_REG_PLL_EN);
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,CLKRST_HBN_ROOT_CLK_SEL,clkSel);
        BL_WR_REG(CLKRST_BASE,CLKRST_MM_CLK_CTRL_CPU,tmpVal);
        GLB_CLK_SET_DUMMY_WAIT;
    }else{
        /* TODO: for the first version, pll_en must keep 1, otherwise divider
           is not available(take reg_bclk_div as 0 always) */
        tmpVal=BL_SET_REG_BIT(tmpVal,CLKRST_REG_PLL_EN);

        /* Select RC32M and XTAL first, so there is no risk of making bclk is more than 80M
           if set reg_bclk_div 0 first then set hbn_root_clk_sel ,bclk maybe 160M after bclk_div is 0 */
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,CLKRST_HBN_ROOT_CLK_SEL,clkSel);
        BL_WR_REG(CLKRST_BASE,CLKRST_MM_CLK_CTRL_CPU,tmpVal);
        GLB_CLK_SET_DUMMY_WAIT;

        /* HCLK is RC32M or XTAL, so BCLK no need divider */
        tmpVal=BL_RD_REG(CLKRST_BASE,CLKRST_MM_CLK_CPU);
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,CLKRST_REG_BCLK_DIV,0);
        BL_WR_REG(CLKRST_BASE,CLKRST_MM_CLK_CPU,tmpVal);
        GLB_CLK_SET_DUMMY_WAIT;
    }
}

/****************************************************************************//**
 * @brief  Select PLL output clock
 *
 * @param  fClk: PLL clock type selection
 *
 * @return None
 *
*******************************************************************************/
void ATTR_CLOCK_SECTION GLB_Set_PLL_CLK(GLB_PLL_CLK_Type fClk)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GLB_PLL_CLK_TYPE(fClk));

    /* Power off PLL clk before switch */
    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU);
    tmpVal=BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PLL_EN);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    /* configure and power on PLL clock */
    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CPU);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_CPU_CLK_DIV, 0);     /* CPU clock same as PLL clock */
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_BCLK_DIV, GLB_Get_BClk_Div(fClk));
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CPU, tmpVal);

    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PLL_SEL, fClk);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,CLKRST_HBN_ROOT_CLK_SEL, 2);  /* TODO: root clk selet PLL */
    tmpVal=BL_SET_REG_BIT(tmpVal, CLKRST_REG_PLL_EN);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;
}

void ATTR_CLOCK_SECTION GLB_Set_System_CLK_Div(uint8_t hclkDiv,uint8_t bclkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_CPU_CLK_DIV, hclkDiv);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_BCLK_DIV, bclkDiv);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU, tmpVal);

    GLB_CLK_SET_DUMMY_WAIT;
}
extern uint32_t SystemCoreClock;
void ATTR_CLOCK_SECTION GLB_Set_System_CLK(GLB_PLL_CLK_Type fClk)
{
    /* Before config XTAL and PLL ,make sure root clk is from RC32M */
    GLB_Set_Root_CLK(GLB_ROOT_CLK_RC32M);
    SystemCoreClock=32*1000*1000;

    /* select PLL clock */
    GLB_Set_PLL_CLK(fClk);

    switch(fClk)
    {
        case GLB_PLL_CLK_120M:
            SystemCoreClock=120*1000*1000;
            break;
        case GLB_PLL_CLK_160M:
            SystemCoreClock=160*1000*1000;
            break;
        case GLB_PLL_CLK_320M:
            SystemCoreClock=320*1000*1000;
            break;
        case GLB_PLL_CLK_400M:
            SystemCoreClock=400*1000*1000;
            break;
    }
    GLB_Set_Root_CLK(GLB_ROOT_CLK_PLL_WITH_XTAL_ON);
}

void ATTR_CLOCK_SECTION SystemCoreClockUpdate (void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CIP);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_PU_MBG);
    BL_WR_REG(CLKRST_BASE, CLKRST_CIP, tmpVal);

    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_PU_SFREG);
    BL_WR_REG(CLKRST_BASE, CLKRST_CIP, tmpVal);

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP1);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_PPU);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_PU);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL2_PPU);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL2_PU);
    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP1, tmpVal);

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP2);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP2, tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;
    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_CLKPLL_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP2, tmpVal);

    //GLB_Set_Fbdiv_Ratio(19);  /* adjust 160M PLL to 152M */

#if CPU_CA5
    GLB_Set_System_CLK(GLB_PLL_CLK_400M);
#else
    GLB_Set_System_CLK(GLB_PLL_CLK_160M);
#endif

#if 0   /* adjust PLL 160M to 152M, so as to get 76M HDMI clk */
    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_CLKPLL2_FBDIV_RATIO, 19);
    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP4, tmpVal);
#endif
}

#if 0
void GLB_Set_WiFi_Core_CLK(uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_CLK_CFG1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_WIFI_MAC_CORE_DIV,clkDiv);
    BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
}

void GLB_Set_WiFi_Encrypt_CLK(uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_CLK_CFG1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_WIFI_MAC_WT_DIV,clkDiv);
    BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
}

void ATTR_VRAM_SECTION GLB_Set_PSRAM_CLK(GLB_PSRAM_CLK_Type clkSel)
{
    uint32_t tmpVal;

    /* power off psram clk before switch */
    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_EMI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PSRAMA_CLK_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PSRAMB_CLK_EN);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_EMI, tmpVal);

    /* configure and power on PLL clock */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PSRAMA_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PSRAMB_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_PSRAMA_CLK_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_PSRAMB_CLK_EN);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_EMI, tmpVal);

    BL_LOGI("[Set_PSRAM_CLK] %d\r\n", clkSel);
}

void GLB_Select_Internal_Flash(void)
{
     uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_PARM);
    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_SEL_EMBEDDED_SFLASH);
    BL_WR_REG(CLKRST_BASE,GLB_PARM,tmpVal);
}

void GLB_Select_External_Flash(void)
{
     uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_PARM);
    tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_SEL_EMBEDDED_SFLASH);
    BL_WR_REG(CLKRST_BASE,GLB_PARM,tmpVal);
}

void GLB_Deswap_Flash_Pin()
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_PARM);
    tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_SWAP_SFLASH_IO_3_IO_0);
    BL_WR_REG(CLKRST_BASE,GLB_PARM,tmpVal);
}

void GLB_Swap_Flash_Pin()
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_PARM);
    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_SWAP_SFLASH_IO_3_IO_0);
    BL_WR_REG(CLKRST_BASE,GLB_PARM,tmpVal);
}

void GLB_Set_Flash_CLK(GLB_SFLASH_CLK_Type clkSel,uint8_t clkDiv)
{
    MIXED_PLL_CLK_Type clk;
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_CLK_CFG1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_DIV,0);
    BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);

    switch(clkSel)
    {
        case GLB_SFLASH_CLK_120M:
            /* Flash CLK is divied by 240M */
            clk=PLL_CLK_240M;
            Mixed_Enable_PLL_Clk(clk);

            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,clkSel);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        case GLB_SFLASH_CLK_80M:
            /* Flash CLK is divied by 320M */
            clk=PLL_CLK_320M;
            Mixed_Enable_PLL_Clk(clk);

            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,clkSel);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        case GLB_SFLASH_CLK_FDIV2:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,clkSel);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        case GLB_SFLASH_CLK_96M:
            clk=PLL_CLK_96M;
            Mixed_Enable_PLL_Clk(clk);

            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,clkSel);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        case GLB_SFLASH_CLK_XTAL:
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_DIV,1);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,GLB_SFLASH_CLK_120M);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        case GLB_SFLASH_CLK_50M:
            clk=PLL_CLK_100M;
            Mixed_Enable_PLL_Clk(clk);

            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_DIV,3);
            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,GLB_SFLASH_CLK_120M);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
        default:
            /* Flash CLK is divied by 320M */
            clk=PLL_CLK_320M;
            Mixed_Enable_PLL_Clk(clk);

            tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SF_CLK_SEL,clkSel);
            BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
            break;
    }
}
#endif

void GLB_DMA_CLK_Enable(GLB_DMA_CLK_ID_Type clk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    tmpVal = BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_DMA_CLK_CTRL);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, MMSYS_MISC_DMA_CLK_EN);
    tmpVal2 |= (1<<clk);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_DMA_CLK_EN, tmpVal2);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_DMA_CLK_CTRL, tmpVal);
}

void GLB_DMA_CLK_Disable(GLB_DMA_CLK_ID_Type clk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_DMA_CLK_CTRL);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, MMSYS_MISC_DMA_CLK_EN);
    tmpVal2 &= (~(1<<clk));
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_DMA_CLK_EN, tmpVal2);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_DMA_CLK_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set spi clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  div: div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_SPI_CLK(uint8_t enable, GLB_DSP_SPI_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_SPI_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_SEL, clkSel);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_SPI_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_SPI_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    return SUCCESS;
}

void GLB_Set_UART_CLK(BL_Fun_Type enable, GLB_UART_CLK_Type clkSel, uint8_t clkDiv)
{
    uint32_t tmpVal;

    if (enable) {
       /* configure UART clk */
       tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU);
       tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_HBN_UART_CLK_SEL, clkSel);
       BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_CPU, tmpVal);

       /* configure clk div and power on UART clk */
       tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI);
       tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_UART_CLK_DIV, clkDiv);
       tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_UART_CLK_DIV_EN);
    } else {
        tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI);
        tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_UART_CLK_DIV_EN);
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI, tmpVal);
}

void GLB_Set_SDH_CLK(BL_Fun_Type enable, GLB_SDH_CLK_Type clkSel)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI);

    if (enable) {
        /* configure and power on SDH clk */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_SDH_CLK_SEL, clkSel);
        tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_SDH_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_SDH_CLK_EN);
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI, tmpVal);
}

void GLB_Set_PDM_CLK(uint8_t id, BL_Fun_Type enable, uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2);

    if (id == 0) {
        if(enable) {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PDM0_CLK_DIV, clkDiv);
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_PDM0_CLK_EN);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PDM0_CLK_EN);
        }
    } else if (id == 1) {
        if(enable) {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_PDM1_CLK_DIV, clkDiv);
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_PDM1_CLK_EN);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_PDM1_CLK_EN);
        }
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2, tmpVal);
}

void GLB_Set_I2S_CLK(uint8_t id, BL_Fun_Type enable, uint8_t refSel, uint8_t outClkEnable, uint8_t outClkDiv)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2);

    if (id == 0) {
        if (enable) {
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_I2S0_CLK_EN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_I2S0_CLK_DIV, outClkDiv);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_I2S0_REF_CLK_OE, outClkEnable);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_I2S0_CLK_EN);
        }
    } else if (id == 1) {
        if (enable) {
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_I2S1_CLK_EN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_I2S1_CLK_DIV, outClkDiv);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_I2S1_REF_CLK_OE, outClkEnable);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_I2S1_CLK_EN);
        }
    }

    BL_WR_REG(CLKRST_BASE,CLKRST_MM_CLK_CTRL_PERI2,tmpVal);
}

// void GLB_Set_I2C_CLK(uint8_t id, BL_Fun_Type enable)
// {
//     uint32_t tmpVal;

//     tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI);

//     /* always use bclk as I2C source clock without clk div. Each I2C module has its own clk div */
//     tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_I2C_CLK_DIV, 0);

//     if (id == 0) {
//         if (enable) {
//             tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_I2CA_CLK_EN);
//         } else {
//             tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_I2CA_CLK_EN);
//         }
//     } else if (id == 1) {
//         if (enable) {
//             tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_I2CB_CLK_EN);
//         } else {
//             tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_I2CB_CLK_EN);
//         }
//     }

//     BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI, tmpVal);
// }

/****************************************************************************/ /**
 * @brief  set SPI clock
 *
 * @param  enable: Enable or disable SPI clock
 * @param  clkSel: clock selection
 * @param  div: divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_SPI_CLK(uint8_t enable, GLB_SPI_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_SPI_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x1F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_DIV, div);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_SPI_CLK_SEL, clkSel);
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_SPI_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_SPI_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_SPI_CFG0, tmpVal);

    return SUCCESS;
}

BL_Err_Type GLB_Set_I2C_CLK(uint8_t enable, GLB_I2C_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_I2C_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_I2C_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_I2C_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_I2C_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_I2C_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure CPUPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_CPU_PLL(GLB_XTAL_Type xtalType, const GLB_WAC_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_CPUPLL);
    GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_CPUPLL, refClk);
    GLB_Power_On_WAC_PLL(GLB_WAC_PLL_CPUPLL, &(pllCfgList[xtalType]), 1);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure MIPIPLL clock
 *
 * @param  xtalType: XTAL frequency type
 * @param  pllCfg: PLL configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_MIPI_PLL(GLB_XTAL_Type xtalType, const GLB_MU_PLL_Cfg_Type * pllCfgList)
{
    GLB_PLL_REF_CLK_Type refClk;
    
    if (xtalType == GLB_XTAL_RC32M) {
        refClk = GLB_PLL_REFCLK_RC32M;
    } else {
        refClk = GLB_PLL_REFCLK_XTAL;
    }
    
    GLB_Power_Off_MU_PLL(GLB_MU_PLL_MIPIPLL);
    GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_MIPIPLL, refClk);
    GLB_Power_On_MU_PLL(GLB_MU_PLL_MIPIPLL, &(pllCfgList[xtalType]), 1);
    
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  reconfigure MIPIPLL clock div
 *
 * @param  divEn: div enable
 * @param  divRatio: div ratio
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Config_MIPI_PLL_Div(uint8_t divEn, uint8_t divRatio)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;
    
    REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
    
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN, divEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_RATIO, divRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    
    return SUCCESS;
}



/****************************************************************************/ /**
 * @brief  GLB power off mipi uhs PLL
 *
 * @param  pllType: PLL XTAL type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_MU_PLL(GLB_MU_PLL_Type pllType)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    //CHECK_PARAM(IS_GLB_Power_Off_MU_TYPE(pllType));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

    /* cfg0 : pu_aupll=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* cfg0 : pu_aupll_sfreg=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB mipi uhs PLL ref clock select
 *
 * @param  pllType: PLL XTAL type
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_MU_PLL_Ref_Clk_Sel(GLB_MU_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    // CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));
    // CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, refClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on PLL
 *
 * @param  pllType: PLL XTAL type
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_MU_PLL(GLB_MU_PLL_Type pllType, const GLB_MU_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    /* unknown */
    //CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_MU_PLL_MIPIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
        case GLB_MU_PLL_UHSPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_UHS_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_MIPI_PLL_CFG0_OFFSET;
            break;
    }

    /* Step1:config parameter */
    /* cfg1:Set aupll_refclk_sel and aupll_refdiv_ratio */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg4:Set aupll_sel_sample_clk */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set aupll_vco_speed */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg1: uhspll_even_div_en and uhspll_even_div_ratio */
    if (GLB_MU_PLL_UHSPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_EVEN_DIV_EN, cfg->basicCfg->clkpllEvenDivEn);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UHSPLL_EVEN_DIV_RATIO, cfg->basicCfg->clkpllEvenDivRatio);
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    }

    /* cfg6:Set aupll_sdm_bypass,aupll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDMIN, cfg->clkpllSdmin);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

    /* Step2:config pu */
    /* cfg0 : pu_aupll_sfreg=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
   // arch_delay_us(3);

    /* cfg0 : pu_wifipll=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
   // arch_delay_us(3);

    /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : aupll_sdm_reset */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
   // arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle aupll_reset_fbdv, pulse 0 > 1us */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
   // arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    if (waitStable) {
        /* Wait 1.5*30us    */
      //  arch_delay_us(45);
    }

    return SUCCESS;
}


/****************************************************************************/ /**
 * @brief  GLB power off wifi audio cpu PLL
 *
 * @param  pllType: PLL XTAL type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_Off_WAC_PLL(GLB_WAC_PLL_Type pllType)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

    /* cfg0 : pu_aupll=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* cfg0 : pu_aupll_sfreg=0 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB wifi audio cpu PLL ref clock select
 *
 * @param  pllType: PLL XTAL type
 * @param  refClk: PLL ref clock select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_WAC_PLL_Ref_Clk_Sel(GLB_WAC_PLL_Type pllType, GLB_PLL_REF_CLK_Type refClk)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));
    CHECK_PARAM(IS_GLB_PLL_REF_CLK_TYPE(refClk));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

    /* xxxpll_refclk_sel */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    if ((GLB_WAC_PLL_WIFIPLL == pllType) && (GLB_PLL_REFCLK_XTAL == refClk)) {
        /* wifipll_refclk_sel different from other's pll, 1 means xtal */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFCLK_SEL, refClk);
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  GLB power on PLL
 *
 * @param  pllType: PLL XTAL type
 * @param  cfg: GLB PLL configuration
 * @param  waitStable: wait PLL clock stable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Power_On_WAC_PLL(GLB_WAC_PLL_Type pllType, const GLB_WAC_PLL_Cfg_Type *const cfg, uint8_t waitStable)
{
    uint32_t REG_PLL_BASE_ADDRESS = 0;
    uint32_t tmpVal = 0;

    /* unknown */
    CHECK_PARAM(IS_GLB_WAC_PLL_TYPE(pllType));

    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            REG_PLL_BASE_ADDRESS = GLB_BASE + GLB_WIFI_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_AUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
        case GLB_WAC_PLL_CPUPLL:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_CPU_PLL_CFG0_OFFSET;
            break;
        default:
            REG_PLL_BASE_ADDRESS = CCI_BASE + CCI_AUDIO_PLL_CFG0_OFFSET;
            break;
    }

    /* Step1:config parameter */
    /* cfg1:Set aupll_refclk_sel and aupll_refdiv_ratio */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_REFDIV_RATIO, cfg->basicCfg->clkpllRefdivRatio);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);

    /* cfg2:Set aupll_int_frac_sw,aupll_icp_1u,aupll_icp_5u */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_INT_FRAC_SW, cfg->basicCfg->clkpllIntFracSw);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_ICP_1U, cfg->basicCfg->clkpllIcp1u);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_ICP_5U, cfg->basicCfg->clkpllIcp5u);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 2, tmpVal);

    /* cfg3:Set aupll_rz,aupll_cz,aupll_c3,aupll_r4_short,aupll_r4_en */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_RZ, cfg->basicCfg->clkpllRz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_CZ, cfg->basicCfg->clkpllCz);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_C3, cfg->basicCfg->clkpllC3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_R4_SHORT, cfg->basicCfg->clkpllR4Short);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_C4_EN, cfg->basicCfg->clkpllC4En);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 3, tmpVal);

    /* cfg4:Set aupll_sel_sample_clk */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SEL_SAMPLE_CLK, cfg->basicCfg->clkpllSelSampleClk);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 4, tmpVal);

    /* cfg5:Set aupll_vco_speed */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_VCO_SPEED, cfg->basicCfg->clkpllVcoSpeed);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);

    /* cfg6:Set aupll_sdm_bypass,aupll_sdmin */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 6);
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_CTRL_HW, cfg->basicCfg->clkpllSdmCtrlHw);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_SDMIN, cfg->clkpllSdmin);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_BYPASS, cfg->basicCfg->clkpllSdmBypass);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDMIN, cfg->clkpllSdmin);
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 6, tmpVal);

    /* Step2:config pu */
    /* cfg0 : pu_aupll_sfreg=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL_SFREG, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
   // arch_delay_us(3);

    /* cfg0 : pu_wifipll=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_PU_AUPLL, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* delay > 2us */
    //arch_delay_us(3);

    /* toggle sdm_reset (pulse 0 > 1us) */
    /* cfg0 : aupll_sdm_reset */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_SDM_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* Step3:reset pll */
    /* cfg0 : toggle aupll_reset_fbdv, pulse 0 > 1us */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 0);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);
    //arch_delay_us(2);
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_FBDV_RSTB, 1);
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 0, tmpVal);

    /* aupll : cfg1, aupll_postdiv = 0x12 or 0x14 */
    if (GLB_WAC_PLL_AUPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 1);
        if ((cfg->clkpllSdmin==0x12D0E)||(cfg->clkpllSdmin==0x1C395)||(cfg->clkpllSdmin==0x17851)||(cfg->clkpllSdmin==0x16944)||(cfg->clkpllSdmin==0x115E5)) {
            /* 451.548 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_POSTDIV, 0x14);
        } else {
            /* 442.368 */
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CCI_AUPLL_POSTDIV, 0x12);
        }
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 1, tmpVal);
    }

    /* Step4:enable output clock */
    /* wifipll : cfg5, wifipll_vco_div3_en=1 */
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 5);
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_VCO_DIV3_EN);
        BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 5, tmpVal);
    }
    /* cfg8 : wifipll->wifipll_en_ctrl_hw=1 */
    tmpVal = BL_RD_WORD(REG_PLL_BASE_ADDRESS + 4 * 8);
    if (GLB_WAC_PLL_WIFIPLL == pllType) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_WIFIPLL_EN_CTRL_HW, 1);
    }
    /* cfg8 : wifipll/aupll/cpupll clock enable */
    switch (pllType) {
        case GLB_WAC_PLL_WIFIPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV4);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV5);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV6);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV8);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_WIFIPLL_EN_DIV10);
            break;
        case GLB_WAC_PLL_AUPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV1);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV2P5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_AUPLL_EN_DIV6);
            break;
        case GLB_WAC_PLL_CPUPLL:
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV1);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV2);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV2P5);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV4);
            tmpVal = BL_SET_REG_BIT(tmpVal, CCI_CPUPLL_EN_DIV5);
            break;
        default:
            break;
    }
    BL_WR_WORD(REG_PLL_BASE_ADDRESS + 4 * 8, tmpVal);

    if (waitStable) {
        /* Wait 1.5*30us    */
       // arch_delay_us(45);
    }

    return SUCCESS;
}


/****************************************************************************/ /**
 * @brief  GLB set display clock
 *
 * @param  enable: ENABLE or DISABLE
 * @param  srcClk: source clock type
 * @param  evenDiv: divider in even number
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Display_CLK(uint8_t enable, GLB_DISP_CLK_Type srcClk, uint8_t evenDiv)
{
    uint32_t tmpVal = 0;
    uint32_t evenNum = 0;

    CHECK_PARAM(IS_GLB_DISP_CLK_TYPE(srcClk));
    CHECK_PARAM((evenDiv <= 0x7F));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG1, tmpVal);

    if ((evenDiv >= 8) && (evenDiv <= 126)) {
        evenNum = evenDiv & ~(1 << 0);
    } else {
        evenNum = evenDiv;
    }

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG1);
    if(enable){
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    }else{
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_MIPIPLL_EVEN_DIV_EN);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_EVEN_DIV_RATIO, evenNum);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG1, tmpVal);

    return SUCCESS;
}

BL_Err_Type GLB_Set_DSP_I2C0_CLK(uint8_t enable, GLB_DSP_I2C_CLK_Type clkSel, uint8_t divEn, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_I2C_CLK_TYPE(clkSel));

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    tmpVal = *(uint32_t *)0x30007000;
    tmpVal = tmpVal & ~(1<<6);
    *(uint32_t *)0x30007000 = tmpVal;

    // tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C_CLK_SEL, clkSel);
    // BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_CPU, tmpVal);

    tmpVal = BL_RD_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, MM_GLB_REG_I2C0_CLK_DIV, div);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_EN);
    }
    if (divEn) {
        tmpVal = BL_SET_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_DIV_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, MM_GLB_REG_I2C0_CLK_DIV_EN);
    }
    BL_WR_REG(MM_GLB_BASE, MM_GLB_MM_CLK_CTRL_PERI, tmpVal);

    return SUCCESS;
}


void GLB_Set_HDMI_CLK(BL_Fun_Type enable, HDMI_CLK_SEL_E clkSel, uint8_t outClkDiv)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_ISP_DP_CLK);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_HDMI_CLK_DIV_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_DISP_CLK_SEL, clkSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_DISP_CLK_DIV, outClkDiv);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_HDMI_CLK_DIV_EN);
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_ISP_DP_CLK, tmpVal);
}


void GLB_Set_H264_CLK(BL_Fun_Type enable, H264_CLK_SEL_E clkSel, uint8_t outClkDiv)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_ISP_DP_CLK);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_REG_H264_CLK_DIV_EN);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_H264_CLK_SEL, clkSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_REG_H264_CLK_DIV, outClkDiv);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, CLKRST_REG_H264_CLK_DIV_EN);
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_ISP_DP_CLK, tmpVal);
}

void ATTR_CLOCK_SECTION GLB_Set_Fbdiv_Ratio(uint32_t ratio)
{
    uint32_t tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP4);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, CLKRST_CLKPLL2_FBDIV_RATIO, ratio);

    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP4, tmpVal);
}

void ATTR_CLOCK_SECTION GLB_Enable_PLL_CLK(GLB_PLL_CLK_EN_Type clkSel)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP_POSTDIV);

    switch (clkSel)
    {
        case GLB_CLKPLL_EN_25M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_25M_CLK);
            break;
        case GLB_CLKPLL_EN_50M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_50M_CLK);
            break;
        case GLB_CLKPLL_EN_100M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_100M_CLK);
            break;
        case GLB_CLKPLL_EN_120M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_120M_CLK);
            break;
        case GLB_CLKPLL_EN_160M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_160M_CLK);
            break;
        case GLB_CLKPLL_EN_192M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_192M_CLK);
            break;
        case GLB_CLKPLL_EN_240M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_240M_CLK);
            break;
        case GLB_CLKPLL_EN_267M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_267M_CLK);
            break;
        case GLB_CLKPLL_EN_320M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_320M_CLK);
            break;
        case GLB_CLKPLL_EN_400M:
            tmpVal = BL_SET_REG_BIT(tmpVal, CLKRST_CLKPLL_EN_400M_CLK);
            break;
    }

    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP_POSTDIV, tmpVal);
}

/****************************************************************************//**
 * @brief  Power on audio PLL function
 *
 * @param  clkType: Audio PLL clock type
 * @param  posDivCount: Audio MCLK divider
 *
 * @return None
 *
*******************************************************************************/
void GLB_Power_On_Audio_PLL(uint32_t audClk)
{
    uint32_t tmpVal = 0;
    uint32_t fXtal = 38.4*1000000;
    uint32_t aupllSdmin;
    uint8_t postDiv;
    uint8_t refDiv;

    /* f_audio_pll_out = f_xtal * aupll_sdmin_real / aupll_postdiv / aupll_refdiv_ratio */
    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP_AUPLL1);
    refDiv = BL_GET_REG_BITS_VAL(tmpVal, CLKRST_AUPLL_REFDIV_RATIO);
    aupllSdmin = BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP_AUPLL2);
    postDiv = ((fXtal / 100000) * aupllSdmin / (audClk / 100000) / refDiv) >> 17;

    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_CLKIP_AUPLL3);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, CLKRST_AUPLL_POSTDIV, postDiv&0x7F);
    tmpVal=BL_SET_REG_BIT(tmpVal, CLKRST_AUPLL_PU);
    BL_WR_REG(CLKRST_BASE, CLKRST_CLKIP_AUPLL3, tmpVal);

    tmpVal=BL_RD_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2);
    tmpVal=BL_CLR_REG_BIT(tmpVal, CLKRST_REG_I2S0_REF_CLK_OE);
    tmpVal=BL_SET_REG_BIT(tmpVal, CLKRST_REG_I2S0_CLK_EN);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_CLK_CTRL_PERI2, tmpVal);

#if 0
    /*enable I2S mclk output*/
    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_GPIO_CTL);
    tmpVal=BL_SET_REG_BIT(tmpVal, MMSYS_MISC_REG_DEBUG_OE);
    BL_WR_REG(CLKRST_BASE, MMSYS_MISC_GPIO_CTL, tmpVal);

    tmpVal=BL_RD_REG(MMSYS_MISC_BASE, MMSYS_MISC_REG_DBG_LL_CTRL);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_DBG_LL, 0xC0000008);
    BL_WR_REG(MMSYS_MISC_BASE, MMSYS_MISC_REG_DBG_LL_CTRL, tmpVal);
#endif
}

void GLB_Set_Cam_Ref_CLK(BL_Fun_Type enable, uint8_t clkSel, uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_CAM_CFG0);

    if(enable){
        tmpVal=BL_SET_REG_BIT(tmpVal,GLB_REG_CAM_REF_CLK_EN);
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_CAM_REF_CLK_SRC_SEL, clkSel);
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_CAM_REF_CLK_DIV,clkDiv);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_CAM_REF_CLK_EN);
    }

    BL_WR_REG(GLB_BASE,GLB_CAM_CFG0,tmpVal);
}

void GLB_Set_ClkOutSel(uint8_t clkout_num, uint8_t val)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG2);

    switch (clkout_num)
    {
    case 0:
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_CHIP_CLK_OUT_0_SEL, val);
        break;
    case 1:
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_CHIP_CLK_OUT_1_SEL, val);
        break;
    case 2:
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_CHIP_CLK_OUT_2_SEL, val);
        break;
    case 3:
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_CHIP_CLK_OUT_3_SEL, val);
        break;
    }

    BL_WR_REG(GLB_BASE,GLB_DIG_CLK_CFG2,tmpVal);
}

#if 0
void GLB_Set_SSP_CLK(BL_Fun_Type enable,uint8_t clkDiv)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_I2C_SSP_CLK_CTRL);

    if(enable){
        tmpVal=BL_SET_REG_BIT(tmpVal,GLB_REG_SSP_CLK_EN);
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_SSP_CLK_DIV,clkDiv);
        BL_WR_REG(CLKRST_BASE,GLB_I2C_SSP_CLK_CTRL,tmpVal);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_SSP_CLK_EN);
        BL_WR_REG(CLKRST_BASE,GLB_I2C_SSP_CLK_CTRL,tmpVal);
    }
}

void GLB_Enable_Dig32K_CLK(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL);

    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_REG_EN_DIG_32K_GEN);

    BL_WR_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL,tmpVal);
}

void GLB_Disable_Dig32K_CLK(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL);

    tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_EN_DIG_32K_GEN);

    BL_WR_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL,tmpVal);
}

void GLB_Set_DAC_CLK(BL_Fun_Type enable,GLB_DAC_CLK_Type clk)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL);

    if(enable){
        tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_512K_SEL,clk);
        tmpVal=BL_SET_REG_BIT(tmpVal,GLB_REG_EN_DIG_32K_GEN);
    }else{
        tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_REG_EN_DIG_32K_GEN);
    }

    BL_WR_REG(CLKRST_BASE,GLB_WIFI_LP32K_WAKEUP_CTRL,tmpVal);
}

void GLB_Sleep_CLK_Gate_Enable()
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_CLK_CFG1);
    tmpVal=BL_CLR_REG_BIT(tmpVal,GLB_CM4_GATEHCLK_DIS);
    BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
}

void GLB_Sleep_CLK_Gate_Disable()
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_CLK_CFG1);
    tmpVal=BL_SET_REG_BIT(tmpVal,GLB_CM4_GATEHCLK_DIS);
    BL_WR_REG(CLKRST_BASE,GLB_CLK_CFG1,tmpVal);
}

void GLB_AHB_Slave0_Reset(BL_AHB_Slave0_Type slave)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_SWRST_S0);

    tmpVal |= (1<<slave);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S0,tmpVal);
    tmpVal &= (~(1<<slave));
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S0,tmpVal);
}

void GLB_AHB_Slave1_Reset(BL_AHB_Slave1_Type slave)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_SWRST_S1);

    tmpVal |= (1<<slave);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S1,tmpVal);
    tmpVal &= (~(1<<slave));
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S1,tmpVal);
}

void GLB_AHB_Slave2_Reset(BL_AHB_Slave2_Type slave)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_SWRST_S2);

    tmpVal |= (1<<slave);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S2,tmpVal);
    tmpVal &= (~(1<<slave));
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S2,tmpVal);
}

void GLB_AHB_Slave3_Reset(BL_AHB_Slave3_Type slave)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_SWRST_S3);

    tmpVal |= (1<<slave);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S3,tmpVal);
    tmpVal &= (~(1<<slave));
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_S3,tmpVal);
}

void GLB_SW_POR_Reset()
{
    uint32_t tmpVal;

    GLB_Set_Root_CLK(GLB_ROOT_CLK_RC32M);

    tmpVal=BL_RD_REG(CLKRST_BASE,GLB_SWRST_GLB);

    tmpVal=BL_CLR_REG_BIT(CLKRST_BASE,GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_GLB,tmpVal);

    tmpVal=BL_SET_REG_BIT(CLKRST_BASE,GLB_REG_CTRL_PWRON_RST);
    BL_WR_REG(CLKRST_BASE,GLB_SWRST_GLB,tmpVal);

    /* POR reset is ASYN ,waiting for reset */
    while(1){
        BL60X_Delay_US(10);
    }
}
#endif

void GLB_SW_CPU_Reset(GLB_CPU_SEL_Type cpu)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET);

    if (cpu == GLB_CPU_CM4) {
        tmpVal = BL_CLR_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_CPU_RESET);
        BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);

        tmpVal = BL_SET_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_CPU_RESET);
        BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);
    } else if (cpu == GLB_CPU_CA5) {
        tmpVal = BL_CLR_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_A5_CPU_RESET);
        BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);

        tmpVal = BL_SET_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_A5_CPU_RESET);
        BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);
    }
}

void GLB_SW_System_Reset(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET);

    tmpVal = BL_CLR_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_SYS_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);

    tmpVal = BL_SET_REG_BIT(CLKRST_BASE, CLKRST_REG_CTRL_SYS_RESET);
    BL_WR_REG(CLKRST_BASE, CLKRST_MM_SW_SYS_RESET, tmpVal);
}

#if 0
void GLB_Uart_Fun_Sel(GLB_UART_SIG_Type sig,GLB_UART_SIG_FUN_Type fun)
{
    uint32_t sig_pos=0;
    uint32_t tmpVal;

    if(sig<=GLB_UART_SIG_7){
        tmpVal=BL_RD_REG(CLKRST_BASE,GLB_UART_SIG_SEL_0);

        sig_pos=(sig*4);
        /* Clear original val */
        tmpVal &= (~(0xf<<sig_pos));
        /* Set new value */
        tmpVal |= (fun<<sig_pos);

        BL_WR_REG(CLKRST_BASE,GLB_UART_SIG_SEL_0,tmpVal);
    }else{
        tmpVal=BL_RD_REG(CLKRST_BASE,GLB_UART_SIG_SEL_1);

        sig -= GLB_UART_SIG_8;
        sig_pos=(sig*4);
        /* Clear original val*/
        tmpVal &= (~(0xf<<sig_pos));
        /* Set new value */
        tmpVal |= (fun<<sig_pos);

        BL_WR_REG(CLKRST_BASE,GLB_UART_SIG_SEL_1,tmpVal);
    }
}

void GLB_L2C_Hit_Count_Get(uint32_t *hitCountLow,uint32_t *hitCountHigh)
{
    *hitCountLow=BL_RD_REG(MMSYS_MISC_BASE,GLB_L2C_HIT_CNT_LSB);
    *hitCountHigh=BL_RD_REG(MMSYS_MISC_BASE,GLB_L2C_HIT_CNT_MSB);
}

uint32_t GLB_L2C_Miss_Count_Get(void)
{
    return BL_RD_REG(MMSYS_MISC_BASE,GLB_L2C_MISS_CNT);
}
#endif
#if 0
BL_Err_Type ATTR_TCM_SECTION GLB_GPIO_Init(GLB_GPIO_Cfg_Type *cfg)
{
    uint8_t gpioPin = cfg->gpioPin;
    uint32_t gpioCfgAddress;
    uint32_t tmpVal;

    /* drive strength(drive) = 0  <=>  8.0mA  @ 3.3V */
    /* drive strength(drive) = 1  <=>  9.6mA  @ 3.3V */
    /* drive strength(drive) = 2  <=>  11.2mA @ 3.3V */
    /* drive strength(drive) = 3  <=>  12.8mA @ 3.3V */

    gpioCfgAddress = GLB_BASE + GLB_GPIO_CFG0_OFFSET + (gpioPin << 2);

    /* Disable output anyway*/
    tmpVal = BL_RD_WORD(gpioCfgAddress);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    /* input/output, pull up/down, drive, smt, function */
    tmpVal = BL_RD_WORD(gpioCfgAddress);

    if (cfg->gpioMode != GPIO_MODE_ANALOG) {
        /* not analog mode */

        if (cfg->gpioMode == GPIO_MODE_OUTPUT) {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
        } else {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);
        }

        if (cfg->pullType == GPIO_PULL_UP) {
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        } else if (cfg->pullType == GPIO_PULL_DOWN) {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        } else {
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
        }
    } else {
        /* analog mode */

        /* clear ie && oe */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_IE);
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_OE);

        /* clear pu && pd */
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PU);
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_GPIO_0_PD);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_DRV, cfg->drive);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_SMT, cfg->smtCtrl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_FUNC_SEL, cfg->gpioFun);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_GPIO_0_MODE, cfg->outputMode);
    BL_WR_WORD(gpioCfgAddress, tmpVal);

    return SUCCESS;
}

uint8_t GLB_GPIO_Get_Fun(GLB_GPIO_Type gpioPin)
{
    uint32_t tmpVal;
    tmpVal=BL_RD_WORD(MMSYS_MISC_BASE+MMSYS_MISC_GPIO_OFFSET+gpioPin/2*4);

   if(gpioPin%2==0){
       return BL_GET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_GPIO_0_FUNC_SEL);
   }else{
       return BL_GET_REG_BITS_VAL(tmpVal, MMSYS_MISC_REG_GPIO_1_FUNC_SEL);
   }
}

BL_Err_Type GLB_GPIO_Write(GLB_GPIO_Type gpioPin,uint32_t val)
{
    uint32_t *pOut=(uint32_t *)(MMSYS_MISC_BASE+MMSYS_MISC_GPIO_OUTPUT_OFFSET+((gpioPin>>5)<<2));
    uint32_t pos=gpioPin%32;
    uint32_t tmpOut;

    tmpOut=*pOut;
    if(val>0){
        tmpOut |= (1<<pos);
    }else{
        tmpOut &= (~(1<<pos));
    }
    *pOut=tmpOut;

    return SUCCESS;
}

uint32_t GLB_GPIO_Read(GLB_GPIO_Type gpioPin)
{
    uint32_t *p=(uint32_t *)(MMSYS_MISC_BASE+MMSYS_MISC_GPIO_INPUT_OFFSET+((gpioPin>>5)<<2));
    uint32_t pos=gpioPin%32;

    if((*p)&(1<<pos)){
        return 1;
    }else{
        return 0;
    }
}
#endif
/****************************************************************************//**
 * @brief  get DSP0 DSP1 root clock
 *
 * @param  None
 *
 * @return mm glb root clock type
 *
*******************************************************************************/
GLB_DSP_ROOT_CLK_Type ATTR_CLOCK_SECTION GLB_Get_DSP_ROOT_CLK_Sel(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);

    switch(BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL)){
        case 0:
            return GLB_DSP_ROOT_CLK_RC32M;
        case 1:
            return GLB_DSP_ROOT_CLK_XTAL;
        case 2:
            return GLB_DSP_ROOT_CLK_PLL;
        case 3:
            return GLB_DSP_ROOT_CLK_PLL;
        default :
            return GLB_DSP_ROOT_CLK_RC32M;
    }
}

/****************************************************************************//**
 * @brief  get xclk clock source Select
 *
 * @param  None
 *
 * @return xclk clock type selection
 *
*******************************************************************************/
GLB_DSP_XCLK_Type ATTR_CLOCK_SECTION GLB_Get_DSP_XCLK_Sel(void)
{
    uint32_t tmpVal;

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal=BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL);

    return (GLB_DSP_XCLK_Type)(tmpVal&0x1);
}

/****************************************************************************//**
 * @brief  select DSP0 DSP1 root clock
 *
 * @param  rootClk: mm glb root clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_Type rootClk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_GLB_DSP_ROOT_CLK_TYPE(rootClk));

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal2=BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL);
    switch(rootClk){
        case GLB_DSP_ROOT_CLK_RC32M:
            tmpVal2=0x0;
            break;
        case GLB_DSP_ROOT_CLK_XTAL:
            tmpVal2=0x1;
            break;
        case GLB_DSP_ROOT_CLK_PLL:
            tmpVal2|=(1<<1);
            break;
        default :
            break;
    }
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL,tmpVal2);
    BL_WR_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU,tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Select xclk clock source
 *
 * @param  xclk: xclk clock type selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_XCLK_Sel(GLB_DSP_XCLK_Type xclk)
{
    uint32_t tmpVal;
    uint32_t tmpVal2;

    CHECK_PARAM(IS_GLB_DSP_XCLK_TYPE(xclk));

    tmpVal=BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal2=BL_GET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL);
    switch(xclk){
        case GLB_DSP_XCLK_RC32M:
            tmpVal2&=(~(1<<0));
            break;
        case GLB_DSP_XCLK_XTAL:
            tmpVal2|=(1<<0);
            break;
        default :
            break;
    }
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_HBN_ROOT_CLK_SEL,tmpVal2);
    BL_WR_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU,tmpVal);
    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

BL_Err_Type GLB_Set_CAM_CLK(uint8_t enable, GLB_CAM_CLK_Type clkSel, uint8_t div)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_CAM_CLK_TYPE(clkSel));
    CHECK_PARAM((div <= 0x3));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_SRC_SEL, clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_CAM_REF_CLK_DIV, div);
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_CAM_CFG0);
    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, GLB_REG_CAM_REF_CLK_EN);
    }
    BL_WR_REG(GLB_BASE, GLB_CAM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set muxpll 320M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_320M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_MUXPLL_320M_CLK_SEL_TYPE(clkSel));

    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_320M_SEL,clkSel);
    BL_WR_REG(GLB_BASE,GLB_DIG_CLK_CFG1,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  gate slave3 clock or not
 *
 * @param  enable: ENABLE or DISABLE
 * @param  slave3: slave3 num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_AHB_Slave3_Clock_Gate(uint8_t enable,BL_AHB_Slave3_Type slave3)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_BL_AHB_SLAVE3_TYPE(slave3));

    if(slave3>=BL_AHB_SLAVE3_MAX){
        return ERROR;
    }

    tmpVal=BL_RD_REG(GLB_BASE,GLB_CGEN_CFG3);
    if(enable){
        /* clear bit means clock gate */
        tmpVal &=(~(1<<slave3));
    }else{
        /* set bit means clock pass */
        tmpVal |=(1<<slave3);
    }
    BL_WR_REG(GLB_BASE,GLB_CGEN_CFG3,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  select DSP0 DSP1 pll clock
 *
 * @param  pllClk: mm glb pll clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_PLL_CLK_Sel(GLB_DSP_PLL_CLK_Type pllClk)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_DSP_PLL_CLK_TYPE(pllClk));

    tmpVal = BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CPU_CLK_SEL,pllClk);
    BL_WR_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CTRL_CPU,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  set muxpll 240M selection
 *
 * @param  clkSel: clock selection
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_Muxpll_240M_Sel(GLB_MUXPLL_240M_CLK_SEL_Type clkSel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_MUXPLL_240M_CLK_SEL_TYPE(clkSel));

    if(clkSel==GLB_MUXPLL_SEL_240M_WIFIPLL){
        GLB_AHB_Slave3_Clock_Gate(DISABLE,BL_AHB_SLAVE3_WIFIPLL_240M);
    }

    tmpVal=BL_RD_REG(GLB_BASE,GLB_DIG_CLK_CFG1);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_MUXPLL_240M_SEL,clkSel);
    BL_WR_REG(GLB_BASE,GLB_DIG_CLK_CFG1,tmpVal);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Set System clock divider
 *
 * @param  hclkDiv: HCLK divider
 * @param  mcuBclkDiv: MCU BCLK divider
 * @param  periBclkDiv: BCLK divider
 * @param  lpDiv: LP clock divider
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_System_CLK_Div(uint8_t hclkDiv,uint8_t mcuBclkDiv,uint8_t periBclkDiv,uint8_t lpDiv)
{
    uint32_t tmpVal;
    HBN_MCU_XCLK_Type xclkSel;
    HBN_MCU_ROOT_CLK_Type rootClkSel;

    /* get root clock */
    xclkSel = HBN_Get_MCU_XCLK_Sel();
    rootClkSel = HBN_Get_MCU_Root_CLK_Sel();

    if(rootClkSel!=HBN_MCU_ROOT_CLK_RC32M){
        HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_RC32M);
    }

    /* config hclk_div=0 */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_HCLK_DIV,0);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config mcu_bclk_div=0 */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_MCU_BCLK_DIV,0);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config bclk_div=0 */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_BCLK_DIV,0);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config lp clock div=1 */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PICO_DIV,1);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG7,tmpVal);

    /* config hclk_div=hclkDiv */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_HCLK_DIV,hclkDiv);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config mcu_bclk_div=mcuBclkDiv */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_MCU_BCLK_DIV,mcuBclkDiv);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config bclk_div=periBclkDiv */
    tmpVal=BL_RD_REG(GLB_BASE,GLB_SYS_CFG0);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,GLB_REG_BCLK_DIV,periBclkDiv);
    BL_WR_REG(GLB_BASE,GLB_SYS_CFG0,tmpVal);

    /* config lp clock div=lpDiv */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PICO_DIV,lpDiv);
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG7,tmpVal);

    /* recover root clock */
    HBN_Set_MCU_XCLK_Sel(xclkSel);
    HBN_Set_MCU_Root_CLK_Sel(rootClkSel);

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}
/****************************************************************************//**
 * @brief  Set mcu System clock
 *
 * @param  clkFreq: mcu system clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_Type clkFreq)
{
    uint32_t tmpVal;
    HBN_MCU_XCLK_Type mcuXclkSel;

    CHECK_PARAM(IS_GLB_MCU_SYS_CLK_TYPE(clkFreq));

    /* get xclk&&rootclk clock */
    mcuXclkSel = HBN_Get_MCU_XCLK_Sel();

    /* change root clock to rc32m */
    HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_RC32M);
    GLB_Set_MCU_System_CLK_Div(0,0,0,0);

    /* select pll output clock before select root clock */
    tmpVal = BL_RD_REG(PDS_BASE,PDS_CPU_CORE_CFG1);
    if(GLB_MCU_SYS_CLK_300M_CPUPLL==clkFreq){
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PLL_SEL,GLB_MCU_SYS_CLK_320M_ETHPLL-GLB_MCU_SYS_CLK_160M_WIFIPLL);
    }else if(clkFreq>=GLB_MCU_SYS_CLK_160M_WIFIPLL){
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal,PDS_REG_PLL_SEL,clkFreq-GLB_MCU_SYS_CLK_160M_WIFIPLL);
    }
    BL_WR_REG(PDS_BASE,PDS_CPU_CORE_CFG1,tmpVal);

    /* select root clock */
    switch(clkFreq){
        case GLB_MCU_SYS_CLK_RC32M:
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_RC32M);
            break;
        case GLB_MCU_SYS_CLK_XTAL:
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_XTAL);
            break;
        case GLB_MCU_SYS_CLK_160M_WIFIPLL:
            /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0,1,1,0);
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_AHB_Slave3_Clock_Gate(DISABLE,BL_AHB_SLAVE3_WIFIPLL_240M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_192M_WIFIPLL:
             /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0,1,1,1);
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_AHB_Slave3_Clock_Gate(DISABLE,BL_AHB_SLAVE3_WIFIPLL_240M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_240M_WIFIPLL:
             /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0,1,1,1);
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_AHB_Slave3_Clock_Gate(DISABLE,BL_AHB_SLAVE3_WIFIPLL_240M);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_320M_ETHPLL:
             /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0,1,1,1);
            GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_SEL_320M_ETHPLL);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        case GLB_MCU_SYS_CLK_300M_CPUPLL:
             /* For high speed, set DIV first */
            GLB_Set_MCU_System_CLK_Div(0,1,1,1);
            GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_SEL_300M_CPUPLL);
            HBN_Set_MCU_Root_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            HBN_Set_MCU_XCLK_Sel(mcuXclkSel);
            break;
        default :
            break;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  select DSP0 DSP1 clock div
 *
 * @param  cpuDiv: mm glb bclk1x div
 * @param  dspBclkDiv: mm glb bclk2x div
 * @param  mmBclkDiv: mm glb cpu div
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_System_CLK_Div(uint8_t cpuDiv,uint8_t dspBclkDiv,uint8_t mmBclkDiv)
{
    uint32_t tmpVal = 0;
    GLB_DSP_XCLK_Type dspXclkSel;
    GLB_DSP_ROOT_CLK_Type dspRootClkSel;

    /* get root clock */
    dspXclkSel = GLB_Get_DSP_XCLK_Sel();
    dspRootClkSel = GLB_Get_DSP_ROOT_CLK_Sel();

    /* change root clock to rc32m */
    if(dspRootClkSel!=GLB_DSP_ROOT_CLK_RC32M){
        GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_RC32M);
    }

    /* div=0 */
    tmpVal = BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK1X_DIV,0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK2X_DIV,0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CPU_CLK_DIV,0);
    BL_WR_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU,tmpVal);

    /* set div */
    tmpVal = BL_RD_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK1X_DIV,mmBclkDiv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_BCLK2X_DIV,dspBclkDiv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal,MM_GLB_REG_CPU_CLK_DIV,cpuDiv);
    BL_WR_REG(MM_GLB_BASE,MM_GLB_MM_CLK_CPU,tmpVal);

    /* recover root clock */
    GLB_Set_DSP_XCLK_Sel(dspXclkSel);
    GLB_Set_DSP_ROOT_CLK_Sel(dspRootClkSel);

    return SUCCESS;
}

/****************************************************************************//**
 * @brief  Set dsp System clock
 *
 * @param  clkFreq: dsp system clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_Type clkFreq)
{
    GLB_DSP_XCLK_Type dspXclkSel;

    CHECK_PARAM(IS_GLB_DSP_SYS_CLK_TYPE(clkFreq));

    /* get root clock */
    dspXclkSel = GLB_Get_DSP_XCLK_Sel();

    /* Before config XTAL and PLL ,make sure root clk is from RC32M */
    GLB_Set_DSP_ROOT_CLK_Sel(GLB_DSP_ROOT_CLK_RC32M);
    GLB_Set_DSP_System_CLK_Div(0,0,0);

    /* select pll output clock before select root clock */
    if(GLB_DSP_SYS_CLK_240M_CPUPLL==clkFreq){
        GLB_Set_DSP_PLL_CLK_Sel(GLB_DSP_SYS_CLK_240M_WIFIPLL-GLB_DSP_SYS_CLK_240M_WIFIPLL);
    }else if(GLB_DSP_SYS_CLK_300M_CPUPLL==clkFreq){
        GLB_Set_DSP_PLL_CLK_Sel(GLB_DSP_SYS_CLK_320M_ETHPLL-GLB_DSP_SYS_CLK_240M_WIFIPLL);
    }else if(clkFreq>=GLB_DSP_SYS_CLK_240M_WIFIPLL){
        GLB_Set_DSP_PLL_CLK_Sel(clkFreq-GLB_DSP_SYS_CLK_240M_WIFIPLL);
    }

    /* select root clock */
    switch(clkFreq){
        case GLB_DSP_SYS_CLK_RC32M:
            GLB_Set_DSP_System_CLK_Div(0,0,0);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_RC32M);
            break;
        case GLB_DSP_SYS_CLK_XTAL:
            GLB_Set_DSP_System_CLK_Div(0,0,0);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_XTAL);
            break;
        case GLB_DSP_SYS_CLK_240M_WIFIPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            /* unuseful for mcu, useful for dsp, just for safe */
            GLB_AHB_Slave3_Clock_Gate(DISABLE,BL_AHB_SLAVE3_WIFIPLL_240M);
            GLB_Set_Muxpll_240M_Sel(GLB_MUXPLL_SEL_240M_WIFIPLL);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_320M_ETHPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_SEL_320M_ETHPLL);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_400M_ETHPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_640M_CPUPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_240M_CPUPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            GLB_Set_Muxpll_240M_Sel(GLB_MUXPLL_SEL_240M_CPUPLL);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        case GLB_DSP_SYS_CLK_300M_CPUPLL:
            GLB_Set_DSP_System_CLK_Div(0,1,1);
            GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_SEL_300M_CPUPLL);
            GLB_Set_DSP_ROOT_CLK_Sel(HBN_MCU_ROOT_CLK_PLL);
            /* recover xclk */
            GLB_Set_DSP_XCLK_Sel(dspXclkSel);
            break;
        default :
            break;
    }

    GLB_CLK_SET_DUMMY_WAIT;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  swap UART gpio pins sig function
 *
 * @param  group: UART swap set group
 * @param  swap: swap or no swap
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_Type group, uint8_t swap)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    CHECK_PARAM(IS_GLB_UART_SIG_SWAP_GRP_TYPE(group));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET);
    if (swap) {
        tmpVal2 |= (1 << group);
    } else {
        tmpVal2 &= ~(1 << group);
    }
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_UART_SWAP_SET, tmpVal2);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select UART signal function
 *
 * @param  sig: UART signal
 * @param  fun: UART function
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_UART_Fun_Sel(GLB_UART_SIG_Type sig, GLB_UART_SIG_FUN_Type fun)
{
    uint32_t sig_pos = 0;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_GLB_UART_SIG_TYPE(sig));
    CHECK_PARAM(IS_GLB_UART_SIG_FUN_TYPE(fun));

    if (sig < GLB_UART_SIG_8) {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG1);
        sig_pos = (sig * 4);
        /* Clear original val */
        tmpVal &= (~(0xf << sig_pos));
        /* Set new value */
        tmpVal |= (fun << sig_pos);
        BL_WR_REG(GLB_BASE, GLB_UART_CFG1, tmpVal);
    } else {
        tmpVal = BL_RD_REG(GLB_BASE, GLB_UART_CFG2);
        sig_pos = ((sig - 8) * 4);
        /* Clear original val */
        tmpVal &= (~(0xf << sig_pos));
        /* Set new value */
        tmpVal |= (fun << sig_pos);
        BL_WR_REG(GLB_BASE, GLB_UART_CFG2, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select DSP SPI_0 act mode
 *
 * @param  mod: SPI work mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_SPI_PAD_ACT_AS_TYPE(mod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_MM_SPI_MASTER_MODE, mod);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select SPI_0 act mode
 *
 * @param  mod: SPI work mode
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_MCU_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_Type mod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_SPI_PAD_ACT_AS_TYPE(mod));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SPI_0_MASTER_MODE, mod);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  software reset
 *
 * @param  swrst: reset num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_Type swrst)
{
    uint32_t tmpVal = 0;
    uint32_t bit = 0;
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_GLB_AHB_MCU_SW_TYPE(swrst));

    if (swrst < 32) {
        bit = swrst;
        regAddr = GLB_BASE + GLB_SWRST_CFG0_OFFSET;
    } else if (swrst < 64) {
        bit = swrst - 32;
        regAddr = GLB_BASE + GLB_SWRST_CFG1_OFFSET;
    } else if (swrst < 96) {
        bit = swrst - 64;
        regAddr = GLB_BASE + GLB_SWRST_CFG2_OFFSET;
    }

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal |= (1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get first 1 from u64, then clear it
 *
 * @param  val: target value
 * @param  bit: first 1 in bit
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type GLB_Get_And_Clr_First_Set_From_U64(uint64_t *val, uint32_t *bit)
{
    if (!*val) {
        return ERROR;
    }

    for (uint8_t i = 0; i < 64; i++) {
        if ((*val) & ((uint64_t)1 << i)) {
            *bit = i;
            (*val) &= ~((uint64_t)1 << i);
            break;
        }
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  release IPs clock
 *
 * @param  ips: GLB_AHB_CLOCK_xxx | GLB_AHB_CLOCK_xxx | ...... (not GLB_AHB_CLOCK_IP_xxx)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_PER_Clock_UnGate(uint64_t ips)
{
    /* api request from cjy */

    uint32_t tmpValCfg0 = 0;
    uint32_t tmpValCfg1 = 0;
    uint32_t tmpValCfg2 = 0;
    uint32_t bitfield = 0;

    tmpValCfg0 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpValCfg1 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG1);
    tmpValCfg2 = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG2);
    while (ips) {
        if (SUCCESS == GLB_Get_And_Clr_First_Set_From_U64(&ips, &bitfield)) {
            switch (bitfield) {
                case GLB_AHB_CLOCK_IP_CPU:
                    tmpValCfg0 |= (1 << 0);
                    break;
                case GLB_AHB_CLOCK_IP_SDU:
                    tmpValCfg0 |= (1 << 1);
                    break;
                case GLB_AHB_CLOCK_IP_SEC:
                    tmpValCfg0 |= (1 << 2);
                    tmpValCfg1 |= (1 << 3);
                    tmpValCfg1 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_0:
                    tmpValCfg0 |= (1 << 3);
                    tmpValCfg1 |= (1 << 12);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_1:
                    tmpValCfg0 |= (1 << 3);
                    break;
                case GLB_AHB_CLOCK_IP_DMA_2:
                    tmpValCfg0 |= (1 << 3);
                    tmpValCfg2 |= (1 << 24);
                    break;
                case GLB_AHB_CLOCK_IP_CCI:
                    tmpValCfg0 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_RF_TOP:
                    tmpValCfg1 |= (1 << 1);
                    break;
                case GLB_AHB_CLOCK_IP_GPIP:
                    tmpValCfg1 |= (1 << 2);
                    break;
                case GLB_AHB_CLOCK_IP_TZC:
                    tmpValCfg1 |= (1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_EF_CTRL:
                    tmpValCfg1 |= (1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_SF_CTRL:
                    tmpValCfg1 |= (1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_EMAC:
                    tmpValCfg2 |= (1 << 19);
                    tmpValCfg2 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_UART0:
                    tmpValCfg1 |= (1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_UART1:
                    tmpValCfg1 |= (1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_UART2:
                    tmpValCfg1 |= (1 << 26);
                    break;
                case GLB_AHB_CLOCK_IP_UART3:
                    break;
                case GLB_AHB_CLOCK_IP_UART4:
                    break;
                case GLB_AHB_CLOCK_IP_SPI:
                    tmpValCfg1 |= (1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_I2C:
                    tmpValCfg1 |= (1 << 19);
                    break;
                case GLB_AHB_CLOCK_IP_PWM:
                    tmpValCfg1 |= (1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_TIMER:
                    tmpValCfg1 |= (1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_IR:
                    tmpValCfg1 |= (1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_CHECKSUM:
                    tmpValCfg1 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_QDEC:
                    break;
                case GLB_AHB_CLOCK_IP_KYS:
                    break;
                case GLB_AHB_CLOCK_IP_I2S:
                    tmpValCfg1 |= (1 << 23);
                    break;
                case GLB_AHB_CLOCK_IP_USB11:
                    break;
                case GLB_AHB_CLOCK_IP_CAM:
                    break;
                case GLB_AHB_CLOCK_IP_MJPEG:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_NORMAL:
                    tmpValCfg2 |= (1 << 8);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_LP:
                    break;
                case GLB_AHB_CLOCK_IP_ZB_NORMAL:
                    tmpValCfg2 |= (1 << 9);
                    break;
                case GLB_AHB_CLOCK_IP_ZB_LP:
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_NORMAL:
                    tmpValCfg2 |= (1 << 4);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_LP:
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_NORMAL:
                    tmpValCfg2 |= (1 << 10);
                    break;
                case GLB_AHB_CLOCK_IP_BT_BLE_2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_EMI_MISC:
                    tmpValCfg2 |= (1 << 16);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM0_CTRL:
                    tmpValCfg2 |= (1 << 17);
                    break;
                case GLB_AHB_CLOCK_IP_PSRAM1_CTRL:
                    tmpValCfg2 |= (1 << 18);
                    break;
                case GLB_AHB_CLOCK_IP_USB20:
                    tmpValCfg1 |= (1 << 13);
                    break;
                case GLB_AHB_CLOCK_IP_MIX2:
                    tmpValCfg2 |= (1 << 20);
                    break;
                case GLB_AHB_CLOCK_IP_AUDIO:
                    tmpValCfg2 |= (1 << 21);
                    break;
                case GLB_AHB_CLOCK_IP_SDH:
                    tmpValCfg2 |= (1 << 22);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_NORMAL:
                    tmpValCfg2 |= (1 << 11);
                    break;
                case GLB_AHB_CLOCK_IP_ZB2_LP:
                    break;
                case GLB_AHB_CLOCK_IP_I2C1:
                    tmpValCfg1 |= (1 << 25);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PHY:
                    tmpValCfg0 |= (1 << 7);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_MAC_PHY:
                    tmpValCfg0 |= (1 << 6);
                    break;
                case GLB_AHB_CLOCK_IP_WIFI_PLATFORM:
                    tmpValCfg0 |= (1 << 5);
                    break;
                case GLB_AHB_CLOCK_IP_LZ4:
                    tmpValCfg1 |= (1 << 29);
                    break;
                case GLB_AHB_CLOCK_IP_AUPDM:
                    tmpValCfg1 |= (1 << 28);
                    break;
                case GLB_AHB_CLOCK_IP_GAUGE:
                    tmpValCfg1 |= (1 << 0);
                    break;
                default:
                    break;
            }
        }
    }
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpValCfg0);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG1, tmpValCfg1);
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG2, tmpValCfg2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  software reset
 *
 * @param  swrst: reset num
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_Type swrst)
{
    uint32_t tmpVal = 0;
    uint32_t bit = 0;
    uint32_t regAddr = 0;

    CHECK_PARAM(IS_GLB_AHB_DSP_SW_TYPE(swrst));

    if (swrst < 32) {
        bit = swrst;
        regAddr = MM_GLB_BASE + MM_GLB_MM_SW_SYS_RESET_OFFSET;
    } else if (swrst < 64) {
        bit = swrst - 32;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_MM_PERI_OFFSET;
    } else if (swrst < 96) {
        bit = swrst - 64;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_ISP_SUB_OFFSET;
    } else if (swrst < 128) {
        bit = swrst - 96;
        regAddr = MM_GLB_BASE + MM_GLB_SW_RESET_CODEC_SUB_OFFSET;
    } else if (swrst < 160) {
        bit = swrst - 128;
        regAddr = MM_GLB_BASE + MM_GLB_IMAGE_SENSOR_CTRL_OFFSET;
    }

    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal |= (1 << bit);
    BL_WR_WORD(regAddr, tmpVal);
    BL_DRV_DUMMY;
    tmpVal = BL_RD_WORD(regAddr);
    tmpVal &= ~(1 << bit);
    BL_WR_WORD(regAddr, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set ldo15cis vout select
 *
 * @param  ldoLevel: ldo level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_Set_Ldo15cis_Vout(GLB_LDO15CIS_LEVEL_Type ldoLevel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_GLB_LDO15CIS_LEVEL_TYPE(ldoLevel));

    tmpVal = BL_RD_REG(GLB_BASE, GLB_LDO15CIS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_LDO15CIS_VOUT_SEL, ldoLevel);
    BL_WR_REG(GLB_BASE, GLB_LDO15CIS, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  config mipipll for CSI
 *
 * @param  postDivSel: mipipll post div sel
 * @param  sdmin: mipipll sdmin
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_CSI_Config_MIPIPLL(uint8_t postDivSel, uint32_t sdmin)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_VCO_POSTDIV_SEL, postDivSel);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG5, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_SDMIN, sdmin);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG6, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power up mipipll for CSI
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type GLB_CSI_Power_Up_MIPIPLL(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_MIPIPLL_SFREG, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_PU_MIPIPLL, 1);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG0, tmpVal);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_FBDV_RSTB, 1);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG0, tmpVal);
    ARCH_Delay_US(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_FBDV_RSTB, 0);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG0, tmpVal);
    ARCH_Delay_US(2);
    tmpVal = BL_RD_REG(GLB_BASE, GLB_MIPI_PLL_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_MIPIPLL_FBDV_RSTB, 1);
    BL_WR_REG(GLB_BASE, GLB_MIPI_PLL_CFG0, tmpVal);

    return SUCCESS;
}
/*@} end of group GLB_Public_Functions */

/*@} end of group GLB */

/*@} end of group BL60x_Peripheral_Driver */
