/**
 * *****************************************************************************
 * @file lhal_bl702_pwm.c
 * @version 0.1
 * @date 2020-07-23
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

#include "hal_pwm.h"
#include "lhal_bl702_pwm.h"
#include "hal_pin.h"
#include "bflb_platform.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bl702_hbn.h"
#include "bl702_pwm.h"

uint_fast8_t         PWMBLXXX_close(PWM_Handle handle);
int_fast16_t         PWMBLXXX_control(PWM_Handle handle, uint_fast16_t cmd,void *arg);
void                 PWMBLXXX_init(PWM_Handle handle);
PWM_Handle           PWMBLXXX_open(PWM_Handle handle, PWM_Params *params);
uint_fast8_t         PWMBLXXX_start(PWM_Handle handle,uint8_t channel);
uint_fast8_t         PWMBLXXX_stop(PWM_Handle handle,uint8_t channel);
uint_fast8_t         PWMBLXXX_update(PWM_Handle handle,uint8_t channel,uint16_t period , uint16_t threshold1 , uint16_t threshold2);

static bool  PWMBLXXX_initIO(PWM_Handle handle);
static bool  PWMBLXXX_initHw(PWM_Handle handle);
static PWM_Handle pwm_handle_temp=0;

const PWM_FxnTable PWMBLXXX_fxnTable = {
    PWMBLXXX_close,
    PWMBLXXX_control,
    PWMBLXXX_init,
    PWMBLXXX_open,
    PWMBLXXX_start,
    PWMBLXXX_stop,
    PWMBLXXX_update,
};

uint_fast8_t         PWMBLXXX_close(PWM_Handle handle){

    PWMBLXXX_Object               *object;
    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    uint8_t i=0;

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    for(i=0;i< PWM_MAX_PIN_NUM;i++) {
        if(hwAttrs->pwm_output_pin[i % PWM_MAX_PIN_NUM] != PIN_UNASSIGNED){
            PWM_Channel_Disable(i);
        }
    }

    object -> opened = false;

    return 0;
}
int_fast16_t         PWMBLXXX_control(PWM_Handle handle, uint_fast16_t cmd,void *arg){
    return 0;
}
void                 PWMBLXXX_init(PWM_Handle handle){
    PWMBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;
}

PWM_Handle           PWMBLXXX_open(PWM_Handle handle, PWM_Params *params){
    PWMBLXXX_Object               *object;

    object = handle->object;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
       MSG("PWM:(%p) already in use.", handle);
        return (NULL);
    }    
    
    object->PWM_clock_div = params->PWM_clock_div;
    object->PWM_polarity = params->PWM_polarity;
    object->PWM_toggle_threshold_1 =params->PWM_toggle_threshold_1;
    object->PWM_toggle_threshold_2 = params->PWM_toggle_threshold_2;
    object->PWM_wave_period = params->PWM_wave_period;
    object->PWM_pluse_counter_done_callback = params->PWM_pluse_counter_done_callback;
    object->PWM_pluse_count =params->PWM_pluse_count;
    object->PWM_work_mode = params->PWM_work_mode;
    
    if(PWMBLXXX_initIO(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    if(PWMBLXXX_initHw(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    } 

    object->opened = true;
    
    return (handle);

}


uint_fast8_t         PWMBLXXX_start(PWM_Handle handle,uint8_t channel){

    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->pwm_output_pin[channel % PWM_MAX_PIN_NUM] != PIN_UNASSIGNED){
        PWM_Channel_Enable(channel% PWM_MAX_PIN_NUM);
        return SUCCESS;
    }else{
        /*access not initialed pwm io */
        MSG("Can not access io which has not been initialed \r\n");
        return ERROR;
    }


}

uint_fast8_t         PWMBLXXX_stop(PWM_Handle handle,uint8_t channel){

    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->pwm_output_pin[channel % PWM_MAX_PIN_NUM] != PIN_UNASSIGNED){
        PWM_Channel_Disable(channel% PWM_MAX_PIN_NUM);
        return SUCCESS;
    }else{
        /*access not initialed pwm io */
        MSG("Can not access io which has not been initialed \r\n");
        return ERROR;        
    }
}

uint_fast8_t         PWMBLXXX_update(PWM_Handle handle,uint8_t channel,uint16_t period , uint16_t threshold1 , uint16_t threshold2){
    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->pwm_output_pin[channel % PWM_MAX_PIN_NUM] != PIN_UNASSIGNED){
        PWM_Channel_Update(channel % PWM_MAX_PIN_NUM,period,threshold1,threshold2);
        return SUCCESS;
    }else{
        /*access not initialed pwm io */
        MSG("Can not access io which has not been initialed \r\n");
        return ERROR;           
    }
}

static bool  PWMBLXXX_initIO(PWM_Handle handle){
    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    uint8_t i=0,vaild_pwm_num=0;
    uint8_t pwm_io_list[5];

    hwAttrs = handle->hwAttrs;

    for(i=0;i<PWM_MAX_PIN_NUM;i++){
        if(hwAttrs->pwm_output_pin[i] != PIN_UNASSIGNED){
            pwm_io_list[i] = hwAttrs->pwm_output_pin[i];
            vaild_pwm_num ++;
        }
    }

    if(vaild_pwm_num){
        GLB_GPIO_Func_Init(GPIO_FUN_PWM,pwm_io_list,vaild_pwm_num);
        return SUCCESS;
    }else{
        return ERROR;
    }
}

void PWM_ch0_callback(void)
{
    PWMBLXXX_Object               *object;

    if(pwm_handle_temp != NULL){
        object = pwm_handle_temp->object;
        object->PWM_pluse_counter_done_callback(pwm_handle_temp,0);
    }
}
void PWM_ch1_callback(void)
{
    PWMBLXXX_Object               *object;

    if(pwm_handle_temp != NULL){
        object = pwm_handle_temp->object;
        object->PWM_pluse_counter_done_callback(pwm_handle_temp,1);
    }
}
void PWM_ch2_callback(void)
{
    PWMBLXXX_Object               *object;

    if(pwm_handle_temp != NULL){
        object = pwm_handle_temp->object;
        object->PWM_pluse_counter_done_callback(pwm_handle_temp,2);
    }
}
void PWM_ch3_callback(void)
{
    PWMBLXXX_Object               *object;

    if(pwm_handle_temp != NULL){
        object = pwm_handle_temp->object;
        object->PWM_pluse_counter_done_callback(pwm_handle_temp,3);
    }
}
void PWM_ch4_callback(void)
{
    PWMBLXXX_Object               *object;

    if(pwm_handle_temp != NULL){
        object = pwm_handle_temp->object;
        object->PWM_pluse_counter_done_callback(pwm_handle_temp,4);
    }
}

intCallback_Type * pwm_callback_func_list[]= {PWM_ch0_callback, PWM_ch1_callback, PWM_ch2_callback, PWM_ch3_callback, PWM_ch4_callback};

static bool  PWMBLXXX_initHw(PWM_Handle handle){

    PWMBLXXX_Object               *object;
    PWMBLXXX_HWAttrsV2 const     *hwAttrs;

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    uint8_t i=0;

    PWM_CH_CFG_Type pwmCfg=
    {
        .ch=PWM_CH0,
        .clk=PWM_CLK_XCLK,
        .stopMode=PWM_STOP_ABRUPT,
        .pol=PWM_POL_INVERT,
        .clkDiv=0,
        .period=1000,
        .threshold1=0,
        .threshold2=1000,
        .intPulseCnt=0,
    };


    pwmCfg.clkDiv = object->PWM_clock_div ;
    pwmCfg.pol = object->PWM_polarity;
    pwmCfg.threshold1 = object->PWM_toggle_threshold_1;
    pwmCfg.threshold2 = object->PWM_toggle_threshold_2;
    pwmCfg.period = object->PWM_wave_period;
    pwmCfg.intPulseCnt = object->PWM_pluse_count;

    for(i=0;i<PWM_MAX_PIN_NUM;i++) {

        if(hwAttrs->pwm_output_pin[i] != PIN_UNASSIGNED){

            pwmCfg. ch =  hwAttrs->pwm_output_pin[i] % PWM_MAX_PIN_NUM;
            PWM_Channel_Init(&pwmCfg);

            if(object->PWM_work_mode == PWM_GENERATE_COUNTER_MODE){
                
                /* install the interrupt callback function */
                PWM_Int_Callback_Install(i,PWM_INT_PULSE_CNT,pwm_callback_func_list[i]);
                PWM_IntMask(i,PWM_INT_PULSE_CNT,UNMASK);
                pwm_handle_temp = handle;
            }
        }
    }

    if(object->PWM_work_mode == PWM_GENERATE_COUNTER_MODE){
        /* enable pwm interrupt*/
        NVIC_EnableIRQ(PWM_IRQn);        
    }

    return SUCCESS;
}

