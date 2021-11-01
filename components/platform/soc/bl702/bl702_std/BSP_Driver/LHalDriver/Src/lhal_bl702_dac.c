/**
 * *****************************************************************************
 * @file lhal_bl702_dac.c
 * @version 0.1
 * @date 2020-06-28
 * @brief 
 * *****************************************************************************
 * @attention
 * 
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * *****************************************************************************
 */

#include "hal_dac.h"
#include "lhal_bl702_dac.h"
#include "bl702_dac.h"
#include "bflb_platform.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bl702_hbn.h"
#include "bl702_dma.h"

uint_fast8_t         DACBLXXX_close(DAC_Handle handle);
int_fast16_t         DACBLXXX_control(DAC_Handle handle, uint_fast16_t cmd,void *arg);
void                 DACBLXXX_init(DAC_Handle handle);
DAC_Handle           DACBLXXX_open(DAC_Handle handle, DAC_Params *params);
void                 DACBLXXX_write(DAC_Handle handle,uint8_t dac_ch_index , uint32_t reg_data);
uint_fast32_t DACBLXXX_getDMAAddrFxn(DAC_Handle handle);
uint_fast8_t  DACBLXXX_getDmaReqFxn(DAC_Handle handle);

const DAC_FxnTable DACBLXXX_fxnTable = {
    DACBLXXX_close,
    DACBLXXX_control,
    DACBLXXX_open,
    DACBLXXX_init,
    DACBLXXX_write,
    DACBLXXX_getDMAAddrFxn,
    DACBLXXX_getDmaReqFxn,
};

uint_fast8_t DACBLXXX_close(DAC_Handle handle){

    GLB_GPIP_DAC_Cfg_Type dacCfg = {
        .refSel = GLB_DAC_REF_SEL_INTERNAL,
        .resetChanA = ENABLE,
        .resetChanB = ENABLE,
        .div = DAC_CLK_DIV_16,
        .dmaEn = DISABLE,
        .dmaFmt = GPIP_DAC_DMA_FORMAT_0
    };

    GLB_GPIP_DAC_ChanA_Cfg_Type chACfg = {
        .chanCovtEn = DISABLE,
        .outputEn = DISABLE,
        .chanEn = DISABLE,
        .src = GPIP_DAC_ChanA_SRC_REG
    };

    GLB_GPIP_DAC_ChanB_Cfg_Type chBCfg = {
        .chanCovtEn = DISABLE,
        .outputEn = DISABLE,
        .chanEn = DISABLE,
        .src = GPIP_DAC_ChanB_SRC_REG
    };    

    GLB_GPIP_DAC_Init(&dacCfg);
    GLB_GPIP_DAC_Set_ChanA_Config(&chACfg);
    GLB_GPIP_DAC_Set_ChanB_Config(&chBCfg);

    return 0;
}

int_fast16_t DACBLXXX_control(DAC_Handle handle, uint_fast16_t cmd,void *arg){
    return 0;
}

void         DACBLXXX_init(DAC_Handle handle){
    DACBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;

}

DAC_Handle   DACBLXXX_open(DAC_Handle handle, DAC_Params *params){

    DACBLXXX_Object               *object;
    DACBLXXX_HWAttrsV2 const      *hwAttrs;
    uint8_t dac_pin_sel[2];

    GLB_GPIP_DAC_Cfg_Type dacCfg = {
        .refSel = GLB_DAC_REF_SEL_INTERNAL,
        .resetChanA = ENABLE,
        .resetChanB = ENABLE,
        .div = DAC_CLK_DIV_16,
        .dmaEn = DISABLE,
        .dmaFmt = GPIP_DAC_DMA_FORMAT_0
    };

    GLB_GPIP_DAC_ChanA_Cfg_Type chACfg = {
        .chanCovtEn = ENABLE,
        .outputEn = ENABLE,
        .chanEn = ENABLE,
        .src = GPIP_DAC_ChanA_SRC_REG
    };

    GLB_GPIP_DAC_ChanB_Cfg_Type chBCfg = {
        .chanCovtEn = ENABLE,
        .outputEn = ENABLE,
        .chanEn = ENABLE,
        .src = GPIP_DAC_ChanB_SRC_REG
    };

    object = handle->object;
    hwAttrs = handle ->hwAttrs;

    object->dac_clk_mode = params->dac_clk_mode;
    object->dac_format = params->dac_format;
    object->dac_mode = params->dac_mode;

    GLB_Set_DAC_CLK(ENABLE,GLB_DAC_CLK_XCLK,0x40);

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("DMA:(%p) already in use.", handle);
        return (NULL);
    }

    if(hwAttrs->dac_output_pin_0 != GLB_GPIO_PIN_13 && hwAttrs->dac_output_pin_1 != GLB_GPIO_PIN_14){
        return (NULL);
        /*PIN ONLY SUPPORT GPIO13 & GPIO14*/
    }

    dac_pin_sel[0] = hwAttrs->dac_output_pin_0;
    dac_pin_sel[1] = hwAttrs->dac_output_pin_1;

    GLB_GPIO_Func_Init(GPIO_FUN_ANALOG,dac_pin_sel,2);


    dacCfg.div = (DAC_CLK_Type)object->dac_clk_mode;
    dacCfg.dmaFmt = object->dac_format;
    
    if(object->dac_mode == DAC_MODE_DMA){
        dacCfg.dmaEn = ENABLE;
        chACfg.src = GPIP_DAC_ChanA_SRC_DMA;
        chBCfg.src = GPIP_DAC_ChanB_SRC_DMA;
    }else{
        dacCfg.dmaEn = DISABLE;
        chACfg.src = GPIP_DAC_ChanA_SRC_REG;
        chBCfg.src = GPIP_DAC_ChanB_SRC_REG;
    }


    GLB_GPIP_DAC_Set_ChanA_Config(&chACfg);
    GLB_GPIP_DAC_Set_ChanB_Config(&chBCfg);

    GLB_GPIP_DAC_Init(&dacCfg);
    
    if(object->dac_mode == DAC_MODE_DMA){
        GPIP_Set_DAC_DMA_TX_FORMAT_SEL(object->dac_format);
        GPIP_Set_DAC_DMA_TX_Enable();
    }

    return handle;
}

void DACBLXXX_write(DAC_Handle handle,uint8_t dac_ch_index , uint32_t reg_data){
    switch(dac_ch_index){
        case 0: GLB_DAC_Set_ChanA_Value(reg_data);break;
        case 1: GLB_DAC_Set_ChanB_Value(reg_data);break;
        default: break;
    }
}

uint_fast32_t DACBLXXX_getDMAAddrFxn(DAC_Handle handle){
    return 0x40002048;
}
uint_fast8_t  DACBLXXX_getDmaReqFxn(DAC_Handle handle){
    return (uint_fast8_t)DMA_REQ_GPADC1;
}