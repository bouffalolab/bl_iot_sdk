/*
 * Copyright (c) 2020 Bouffalolab.
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
#include "bl602_common.h"
#include "bl602_glb.h"
#include "bl602_hbn.h"
#include "bl602_dac.h"
#include "bl602_dma.h"


#define DAC_DMA_CHANNLE                DMA_CH0

static DMA_LLI_Ctrl_Type LLIList[200];


static struct DMA_Control_Reg dmaCtrlRegVal={
    .TransferSize=500,
    .SBSize=DMA_BURST_SIZE_1,
    .DBSize=DMA_BURST_SIZE_1,
    .SWidth=DMA_TRNS_WIDTH_32BITS,
    .DWidth=DMA_TRNS_WIDTH_32BITS,
    .SI=DMA_PINC_ENABLE,
    .DI=DMA_PINC_DISABLE,
    .I=0,
};

static DMA_LLI_Cfg_Type lliCfg={
    DMA_TRNS_M2P,
    DMA_REQ_NONE,
    DMA_REQ_GPADC1,
};

static GLB_GPIO_Cfg_Type gpioCfg[2] = {
    [0] = {
        .gpioPin = GLB_GPIO_PIN_13,
        .gpioFun = GPIO13_FUN_GPIP_CH3,
        .gpioMode = GPIO_MODE_AF,
        .pullType = GPIO_PULL_NONE,
        .drive = 1,
        .smtCtrl = 1
    },
    [1] = {
        .gpioPin = GLB_GPIO_PIN_14,
        .gpioFun = GPIO14_FUN_GPIP_CH2,
        .gpioMode = GPIO_MODE_AF,
        .pullType = GPIO_PULL_NONE,
        .drive = 1,
        .smtCtrl = 1
    }
};
GLB_GPIP_DAC_Cfg_Type dacCfg = {
    .refSel = GLB_DAC_REF_SEL_INTERNAL,
    .resetChanA = ENABLE,
    .resetChanB = ENABLE,
    .mod = GPIP_DAC_MOD_32K,
    .dmaEn = ENABLE,
    .dmaFmt = GPIP_DAC_DMA_FORMAT_1
};
GLB_GPIP_DAC_ChanA_Cfg_Type chACfg = {
    .chanCovtEn = ENABLE,
    .outputEn = ENABLE,
    .chanEn = ENABLE,
    .src = GPIP_DAC_ChanA_SRC_DMA
};
GLB_GPIP_DAC_ChanB_Cfg_Type chBCfg = {
    .chanCovtEn = ENABLE,
    .outputEn = ENABLE,
    .chanEn = ENABLE,
    .src = GPIP_DAC_ChanA_SRC_DMA
};


/*@} end of group DAC_DMA_Private_Variables */

/** @defgroup  DAC_DMA_Global_Variables
 *  @{
 */

/*@} end of group DAC_DMA_Global_Variables */

/** @defgroup  DAC_DMA_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DAC_DMA_Private_Fun_Declaration */

/** @defgroup  DAC_DMA_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  DAC clock init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void DAC_Clock_Init(void)
{
    GLB_Set_DAC_CLK(ENABLE,GLB_DAC_CLK_32M,0x40);
    //96M / 2+1 = 32M then second devide 64 => final dac clock = 32M/64=500KHZ
}

/****************************************************************************//**
 * @brief  DAC gpio init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void DAC_Gpio_Init(void)
{
    GLB_GPIO_Init(&gpioCfg[0]);
    GLB_GPIO_Init(&gpioCfg[1]);

}

/****************************************************************************//**
 * @brief  LLI Init
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void DAC_LLI_Init(uint32_t *psrc, uint32_t bufsize)
{
    uint32_t i = 0;
    bufsize = bufsize / 2000;
    printf("bufsize == %ld \r\n", bufsize);
    for(i = 0; i < bufsize; i++) {
        LLIList[i].srcDmaAddr = (uint32_t)psrc + i * 2000;
        LLIList[i].destDmaAddr = 0x40002048;
        LLIList[i].nextLLI=0;
        if(i!=0){
            LLIList[i-1].nextLLI=(uint32_t)&LLIList[i];
        }
        if(i==20-1){
            dmaCtrlRegVal.I=0;
        }else{
            dmaCtrlRegVal.I=0;
        }
        LLIList[i].dmaCtrl= dmaCtrlRegVal;
    }
    
    LLIList[i - 1].nextLLI=(uint32_t)&LLIList[0];


    DMA_LLI_Init(DAC_DMA_CHANNLE,&lliCfg);
    DMA_LLI_Update(DAC_DMA_CHANNLE, (uint32_t)&LLIList);
}

/****************************************************************************//**
 * @brief  GPIP DAC reg output test
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type DAC_DMA_Test(uint32_t *psrc, uint32_t bufsize)
{
    DAC_Gpio_Init();
    DAC_Clock_Init();

    GLB_GPIP_DAC_Set_ChanA_Config(&chACfg);
    GLB_GPIP_DAC_Set_ChanB_Config(&chBCfg);

    DMA_Enable();
    DMA_Channel_Disable(DAC_DMA_CHANNLE);
    DAC_LLI_Init(psrc, bufsize);

    DMA_Channel_Enable(DAC_DMA_CHANNLE);

    GLB_GPIP_DAC_Init(&dacCfg);
    GPIP_Set_DAC_DMA_TX_FORMAT_SEL(GPIP_DAC_DMA_FORMAT_1);
    GPIP_Set_DAC_DMA_TX_Enable();

    return SUCCESS;
}


int audio_dac_dma_test(uint16_t *paddr, uint32_t bufsize, int sampling)
{
    sampling = sampling;

    if(SUCCESS != DAC_DMA_Test(paddr, bufsize)){

       return 0;
    }

    return -1;
}


