/**
 * *****************************************************************************
 * @file lhal_bl702_adc.c
 * @version 0.1
 * @date 2020-06-19
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

#include "hal_adc.h"
#include "lhal_bl702_adc.h"
#include "bl702_adc.h"
#include "bl702_common.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bflb_platform.h"
#include "bl702_dma.h"

uint_fast8_t         ADCBLXXX_close(ADC_Handle handle);
int_fast16_t         ADCBLXXX_control(ADC_Handle handle, uint_fast16_t cmd,void *arg);
void                 ADCBLXXX_init(ADC_Handle handle);
ADC_Handle           ADCBLXXX_open(ADC_Handle handle, ADC_Params *params);
uint_fast8_t         ADCBLXXX_start(ADC_Handle handle);
uint_fast8_t         ADCBLXXX_stop(ADC_Handle handle);
uint_fast8_t ADCBLXXX_ConvertToMicroVolts(ADC_Handle handle,uint32_t adcValue ,ADC_Result * result);
static void  ADCBLXXX_initHw(ADC_Handle handle);
static bool  ADCBLXXX_initIO(ADC_Handle handle);
static void enable_micrphone_enhance(void);
uint_fast8_t ADCBLXXX_read(ADC_Handle handle,ADC_Result * result , uint_fast8_t len);
uint_fast32_t ADCBLXXX_getDMAAddrFxn(ADC_Handle handle);
uint_fast8_t  ADCBLXXX_getDmaReqFxn(ADC_Handle handle);
static ADC_Handle adc_handle_temp;

const ADC_FxnTable ADCBLXXX_fxnTable = {
    ADCBLXXX_close,
    ADCBLXXX_control,
    ADCBLXXX_stop,
    ADCBLXXX_start,
    ADCBLXXX_ConvertToMicroVolts,
    ADCBLXXX_init,
    ADCBLXXX_open,
    ADCBLXXX_read,
    ADCBLXXX_getDMAAddrFxn,
    ADCBLXXX_getDmaReqFxn,
};

uint8_t      ADCBLXXX_close(ADC_Handle handle){
    
    ADCBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;

    ADC_Reset();
    ADC_Disable();
    ADC_IntMask(ADC_INT_ALL,MASK);
    NVIC_DisableIRQ(GPADC_DMA_IRQn); 

    object->opened = true;
    return 0;
}
int_fast16_t ADCBLXXX_control(ADC_Handle handle, uint_fast16_t cmd,void *arg){
    int ret;
    /* Initialize return value*/
    ret = ADC_STATUS_UNDEFINEDCMD;

    switch(cmd)
    {
        case ADC_CMD_GET_ADC_FIFO_COUNT:
            ret = ADC_Get_FIFO_Count();
        break;
        case ADC_CMD_SET_AS_INNER_TSEN_MODE:
             ADC_Tsen_Init(ADC_TSEN_MOD_INTERNAL_DIODE);
        break;
        case ADC_CMD_GET_TSEN_OFFSET:       
            if(ADC_Trim_TSEN((uint16_t *)arg) == ERROR){
                MSG("read efuse data failed\r\n");
                ret =  ERROR;
            }
            ret =  SUCCESS;
        break;
        case ADC_CMD_SET_TSEN_CUR_HIGH:
            ADC_SET_TSVBE_HIGH();
        break;
        case ADC_CMD_SET_TSEN_CUR_LOW:
            ADC_SET_TSVBE_LOW();
        break;
        default : break;
    }

    /* Return */
    return (ret);
}

void         ADCBLXXX_init(ADC_Handle handle){
    ADCBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;
}
ADC_Handle   ADCBLXXX_open(ADC_Handle handle, ADC_Params *params){
    ADCBLXXX_Object               *object;

    object = handle->object;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("ADC:(%p) already in use.", handle);
        return (NULL);
    }

    object->adc_data_len = params->adc_data_len;
    object->amplifier_0 = params->amplifier_0;
    object->amplifier_1 = params->amplifier_1;
    object->clk_div = params->clk_div;
    object->src_clk_div = params->src_clk_div;
    object->vref_sel = params->vref_sel;
    object->adc_mode = params->adc_mode;
    object->block_mode_timeout = params->block_mode_timeout;
    object->adc_data_ready_callback = params->adc_data_ready_callback;
    object->micrphone_enhance_sw = params->micrphone_enhance_sw;

    if(ADCBLXXX_initIO(handle) != SUCCESS){
        //DebugP_log0("Could not allocate pins, already in use.");
        /* Disable UART */
        //UART_Disable(hwAttrs->deviceIndex,UART_TXRX);
        //UART_Device_Open[hwAttrs->deviceIndex] = RESET;
        object->opened = false;
        return (NULL);        
    }
    ADCBLXXX_initHw(handle);

    object->opened = true;
    
    return (handle);
}

uint_fast8_t ADCBLXXX_start(ADC_Handle handle){
    ADC_Start();

    return 0;
}
uint_fast8_t ADCBLXXX_stop(ADC_Handle handle){
    ADC_Stop();

    return 0;
}


uint_fast8_t ADCBLXXX_read(ADC_Handle handle,ADC_Result * result , uint_fast8_t len){
    
    uint32_t timeout=0;
    uint32_t adc_value=0;
    ADCBLXXX_Object               *object;

    object = handle->object;

    while(len){
        timeout = object ->block_mode_timeout;

        while( ADC_Get_FIFO_Count() == 0){
            timeout --;
            if(timeout == 0){
                ADCBLXXX_stop(handle);
                MSG("ERROR\n");
                return ERROR;
            }
        }
        adc_value = ADC_Read_FIFO();
        ADCBLXXX_ConvertToMicroVolts(handle,adc_value,result);
            
        len --;
        result++;
    }

    return SUCCESS;

}

uint_fast8_t ADCBLXXX_ConvertToMicroVolts(ADC_Handle handle,uint32_t adcValue ,ADC_Result * result){

    ADCBLXXX_Object               *object;
    ADCBLXXX_HWAttrsV2 const     *hwAttrs;

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    uint8_t neg=0;
    float ref=0.0;
    ADC_Data_Width_Type dataType;
    ADC_SIG_INPUT_Type sigType;

    dataType = object->adc_data_len;
    sigType = hwAttrs->is_diff_input;

    switch(object->vref_sel){
        case     HAL_ADC_VREF_3P3V:ref = 3.3;break;                       
        case     HAL_ADC_VREF_2V:ref = 2.0;break;  
        default : break;
    }

    if(sigType==ADC_INPUT_SINGLE_END){

        result->posChan=adcValue>>21;
        result->negChan=-1;
        if(dataType==ADC_DATA_WIDTH_12){
            result->value=(adcValue&0xffff)>>4;
            result->volt=result->value/4096.0*ref;
        }else if(dataType==ADC_DATA_WIDTH_14_WITH_16_AVERAGE){
            result->value=(adcValue&0xffff)>>2;
            result->volt=result->value/16384.0*ref;
        }else if(dataType==ADC_DATA_WIDTH_16_WITH_64_AVERAGE||dataType==ADC_DATA_WIDTH_16_WITH_256_AVERAGE){
            result->value=(adcValue&0xffff);
            result->volt=result->value/65536.0*ref;
        }
    }else{
        neg = 0;
        result->posChan=adcValue>>21;
        result->negChan=(adcValue>>16)&0x1F;

        if(adcValue&0x8000){
            adcValue = ~adcValue;
            adcValue += 1;
            neg = 1;
        }
        if(dataType==ADC_DATA_WIDTH_12){
            result->value=(adcValue&0xffff)>>4;
            result->volt=result->value/2048.0*ref;
        }else if(dataType==ADC_DATA_WIDTH_14_WITH_16_AVERAGE){
            result->value=(adcValue&0xffff)>>2;
            result->volt=result->value/8192.0*ref;
        }else if(dataType==ADC_DATA_WIDTH_16_WITH_64_AVERAGE||dataType==ADC_DATA_WIDTH_16_WITH_256_AVERAGE){
            result->value=(adcValue&0xffff);
            result->volt=result->value/32768.0*ref;
        }
        if(neg){
            result->volt = - result->volt;
        }
    }
    return SUCCESS;
}

static void adc_data_ready_callback_fxn(void){
    ADCBLXXX_Object               *object;
    object = adc_handle_temp ->object;

    object->adc_data_ready_callback(adc_handle_temp);
}

static void  ADCBLXXX_initHw(ADC_Handle handle){
    ADCBLXXX_Object               *object;
    ADCBLXXX_HWAttrsV2 const     *hwAttrs;

    ADC_CFG_Type adcCfg = {
        .v18Sel=ADC_V18_SEL_1P82V,                /*!< ADC 1.8V select */
        .v11Sel=ADC_V11_SEL_1P1V,                 /*!< ADC 1.1V select */
        .clkDiv=ADC_CLK_DIV_32,                   /*!< Clock divider */
        .gain1=ADC_PGA_GAIN_NONE,                 /*!< PGA gain 1 */
        .gain2=ADC_PGA_GAIN_NONE,                 /*!< PGA gain 2 */
        .chopMode=ADC_CHOP_MOD_AZ_PGA_ON,           /*!< ADC chop mode select */
        .biasSel=ADC_BIAS_SEL_MAIN_BANDGAP,       /*!< ADC current form main bandgap or aon bandgap */
        .vcm=ADC_PGA_VCM_1V,                      /*!< ADC VCM value */
        .vref=ADC_VREF_3P3V,                      /*!< ADC voltage reference */
        .inputMode=ADC_INPUT_SINGLE_END,          /*!< ADC input signal type */
        .resWidth=ADC_DATA_WIDTH_12,              /*!< ADC resolution and oversample rate */
        .offsetCalibEn=0,                         /*!< Offset calibration enable */
        .offsetCalibVal=0,                        /*!< Offset calibration value */        
    };

    ADC_FIFO_Cfg_Type adcFifoCfg = {
        .fifoThreshold = ADC_FIFO_THRESHOLD_1,
        .dmaEn = DISABLE,
    };

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    /*
     * hal defautlt adc clock set , src clk is 96M devided by dir parameter
     */
    GLB_Set_ADC_CLK(ENABLE,GLB_ADC_CLK_XCLK,object->src_clk_div);

    /* Disable all interrupt */
    ADC_IntMask(ADC_INT_ALL,MASK);

    ADC_Disable();
    ADC_Enable();

    ADC_Reset();

    adcCfg.gain1 = object->amplifier_0;
    adcCfg.gain2 = object->amplifier_1;
    adcCfg.clkDiv = object->clk_div;
    adcCfg.vref = object->vref_sel;
    adcCfg.inputMode = hwAttrs->is_diff_input;
    adcCfg.resWidth = object->adc_data_len;
    
    ADC_Init(&adcCfg);

    if(object->micrphone_enhance_sw){
        enable_micrphone_enhance();
    }

    if(object->adc_mode != ADC_MODE_DMA){
        adcFifoCfg.dmaEn = DISABLE;
        if(object->adc_mode == ADC_MODE_ONE_SHOT){
            ADC_Scan_Channel_Config(object->postive_ch_list,object->negative_ch_list,object->adc_conver_list_len,false);            
        }else{
            ADC_Scan_Channel_Config(object->postive_ch_list,object->negative_ch_list,object->adc_conver_list_len,true);
        }
        ADC_FIFO_Cfg(&adcFifoCfg);

    }else{
        adcFifoCfg.dmaEn = ENABLE;
        adcFifoCfg.fifoThreshold = hwAttrs->adc_fifo_dma_threshold;
        
        if(object->micrphone_enhance_sw){
            /* mic application do not support scan mode */
            ADC_Channel_Config(object->postive_ch_list[0],object->negative_ch_list[0],true);
        }else{
            ADC_Scan_Channel_Config(object->postive_ch_list,object->negative_ch_list,object->adc_conver_list_len,true); 
        }

        ADC_FIFO_Cfg(&adcFifoCfg);        
    }

    if(object->adc_mode == ADC_MODE_CALLBACK){
        ADC_IntMask(ADC_INT_ADC_READY,UNMASK);
        adc_handle_temp = handle;
        ADC_Int_Callback_Install(ADC_INT_ADC_READY, adc_data_ready_callback_fxn);
    }
    
    ADC_IntClr(ADC_INT_ALL);

    ADC_Int_Callback_Install(ADC_INT_POS_SATURATION, hwAttrs->pos_Saturation_callback);
    ADC_Int_Callback_Install(ADC_INT_NEG_SATURATION, hwAttrs->neg_Saturation_callback);
    ADC_Int_Callback_Install(ADC_INT_FIFO_UNDERRUN, hwAttrs->underrun_callback);
    ADC_Int_Callback_Install(ADC_INT_FIFO_OVERRUN, hwAttrs->overrun_callback);

    /*enable error interrupt*/
    ADC_IntMask(ADC_INT_POS_SATURATION,UNMASK);
    ADC_IntMask(ADC_INT_NEG_SATURATION,UNMASK);
    ADC_IntMask(ADC_INT_FIFO_UNDERRUN,UNMASK);

   /*
    *  in scan mode , fifo overrun error always happend , if user read fifo speed 
    *  is slower than adc generate.
    *  
    *  so mask this fifo overrun error interrupt is default config in this version.
    *  
    */
    ADC_IntMask(ADC_INT_FIFO_OVERRUN,MASK);

    NVIC_EnableIRQ(GPADC_DMA_IRQn); 

}   
static bool  ADCBLXXX_initIO(ADC_Handle handle){
    ADCBLXXX_HWAttrsV2 const     *hwAttrs;
    ADCBLXXX_Object               *object;

    uint8_t adc_pin_sel[ADC_MAX_PIN_NUM];
    uint8_t channel_pin_index=0;
    uint8_t channle_pin_vaild_index=0;

    hwAttrs = handle->hwAttrs;    
    object = handle->object;

    object->adc_conver_list_len =  0;

    for(channel_pin_index = 0;channel_pin_index < ADC_MAX_PIN_NUM;channel_pin_index ++){
        if(hwAttrs->adc_gpio_pin_list[channel_pin_index][ADC_POSITIVE]!= GLB_GPIO_GND){
            adc_pin_sel[channle_pin_vaild_index] = hwAttrs->adc_gpio_pin_list[channel_pin_index][ADC_POSITIVE];
            channle_pin_vaild_index++;
        }
        if(hwAttrs->adc_gpio_pin_list[channel_pin_index][ADC_NEGATIVE]!= GLB_GPIO_GND){
            adc_pin_sel[channle_pin_vaild_index] = hwAttrs->adc_gpio_pin_list[channel_pin_index][ADC_NEGATIVE];
            channle_pin_vaild_index++;
        }        
    }

    for(channel_pin_index = 0;channel_pin_index < ADC_MAX_PIN_NUM;channel_pin_index ++){
        if(hwAttrs->adc_gpio_ch_list[channel_pin_index][ADC_POSITIVE]!= ADC_CHANNEL_UNUSED || hwAttrs->adc_gpio_ch_list[channel_pin_index][ADC_NEGATIVE]!= ADC_CHANNEL_UNUSED){
            object->postive_ch_list[object->adc_conver_list_len]  = hwAttrs->adc_gpio_ch_list[channel_pin_index][ADC_POSITIVE];
            object->negative_ch_list[object->adc_conver_list_len] = hwAttrs->adc_gpio_ch_list[channel_pin_index][ADC_NEGATIVE];
            object->adc_conver_list_len++;
        }           
    }


    if(object->adc_conver_list_len > ADC_MAX_PIN_NUM){
        return ERROR;
    }

    if(channle_pin_vaild_index){
        GLB_GPIO_Func_Init(GPIO_FUN_ANALOG,adc_pin_sel,channle_pin_vaild_index);
    }

    return SUCCESS;

}

static void enable_micrphone_enhance(void){
    /* mic default config list */
    ADC_MIC_Type adcmicCfg = {
        .micboostDb=ADC_MICBOOST_DB_32DB,           /*!< MIC boost db */
        .micPga2Gain=ADC_PGA2_GAIN_12DB,             /*!< MIC pga2 gain */
        .mic1Mode=ADC_MIC_MODE_DIFF,                /*!< MIC1 single or diff */
        .mic2Mode=ADC_MIC_MODE_DIFF,                /*!< MIC2 single or diff */
        .dwaEn=ENABLE,                              /*!< Improve dynamic performance */
        .micboostBypassEn=DISABLE,                  /*!< MIC boost amp bypass enable or disable */
        .micPgaEn=ENABLE,                           /*!< MIC pga enable or disable */
        .micBiasEn=DISABLE,                         /*!< MIC bias enable or disable */
    };

    ADC_Mic_Init(&adcmicCfg);
}
uint_fast32_t ADCBLXXX_getDMAAddrFxn(ADC_Handle handle){
    return 0x40002000+0x4;
}
uint_fast8_t  ADCBLXXX_getDmaReqFxn(ADC_Handle handle){
    return (uint8_t)DMA_REQ_GPADC0;
}