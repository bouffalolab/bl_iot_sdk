/**
 * *****************************************************************************
 * @file lhal_bl702_adc.h
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
#include "bl702_adc.h"

/*
 * set gpio as adc input pin ,max gpio is 8
 *!< GPIO 0, ADC channel 0 
 *!< GPIO 1, ADC channel 1 
 *!< GPIO 2, ADC channel 2 
 *!< GPIO 3, ADC channel 3 
 *!< GPIO 4, ADC channel 4 
 *!< GPIO 5, ADC channel 5 
 *!< GPIO 6, ADC channel 6 
 *!< GPIO 7, ADC channel 7 
 */
#define ADC_MAX_PIN_NUM     11
#define ADC_CHANNEL_UNUSED 0xff
#define GLB_GPIO_GND 0xff

typedef enum{
    ADC_POSITIVE=0,
    ADC_NEGATIVE,
}ADC_POLARITY;


typedef void (*ADCBLXXX_Underrun_ErrorCallback) (void);
typedef void (*ADCBLXXX_OverrunErrorCallback) (void);
typedef void (*ADCBLXXX_Pos_Saturation_ErrorCallback) (void);
typedef void (*ADCBLXXX_Neg_Saturation_ErrorCallback) (void);

typedef struct ADCBLXXX_HWAttrsV2 {
    uint8_t adc_gpio_pin_list[ADC_MAX_PIN_NUM][2];
    uint8_t adc_gpio_ch_list[ADC_MAX_PIN_NUM][2];

    ADC_FIFO_Threshold_Type adc_fifo_dma_threshold;

    /*
     * At This Version , ADC conversion queue only support one input mode,diff or single mode
     * user must config adc pin correctly in hardware attr
     */
    bool                is_diff_input;

    ADCBLXXX_Underrun_ErrorCallback underrun_callback;
    ADCBLXXX_OverrunErrorCallback   overrun_callback;
    ADCBLXXX_Pos_Saturation_ErrorCallback pos_Saturation_callback;
    ADCBLXXX_Neg_Saturation_ErrorCallback neg_Saturation_callback;

} ADCBLXXX_HWAttrsV2;

 /*!
 *  @brief      ADCBLXXX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct {
    bool                opened;         /*!< Has the obj been opened */

    /* bl702 chip default src clk is 96M
       user only can devide src clk(96M) by src_clk_div paramter;
    */
    uint8_t src_clk_div;

    /* second adc clock devider
       final adc clock frequency = 96M/src_clk_div/clk_div
    */    
    ADC_Clock_Devide clk_div;

    ADC_PGA_Gain amplifier_0;
    ADC_PGA_Gain amplifier_1;
    ADC_Vref_Sel vref_sel;
    ADC_Data_Width adc_data_len;

    ADC_Mode            adc_mode;
    uint32_t            block_mode_timeout;    

    /*
     * adc data ready callback
     */
    ADC_Callback        adc_data_ready_callback;

    uint8_t     adc_conver_list_len;
    uint8_t     postive_pin_list[ADC_MAX_PIN_NUM];
    uint8_t     negative_pin_list[ADC_MAX_PIN_NUM];

    uint8_t     postive_ch_list[ADC_MAX_PIN_NUM];
    uint8_t     negative_ch_list[ADC_MAX_PIN_NUM];


    bool micrphone_enhance_sw;

} ADCBLXXX_Object, *ADCBLXXX_Handle;


