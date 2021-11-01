/**
 * *****************************************************************************
 * @file lhal_bl702_pin.c
 * @version 0.1
 * @date 2020-07-13
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
#include "hal_pin.h"
#include "lhal_bl702_pin.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bflb_platform.h"

PIN_Handle pin_handle_temp = NULL;

uint_fast8_t PINBLXXX_close(PIN_Handle handle);
int_fast16_t PINBLXXX_control(PIN_Handle handle, uint_fast16_t cmd, void *arg);
void PINBLXXX_init(PIN_Handle handle);
PIN_Handle PINBLXXX_open(PIN_Handle handle,PIN_Params * params, const PIN_List pinList[]);
void PINBLXXX_write(PIN_Handle handle,PIN_List pin , uint8_t value);
uint32_t PINBLXXX_read(PIN_Handle handle,PIN_List pin);
void PINBLXXX_changeDir(PIN_Handle handle, uint8_t pin_index , PIN_Dir dir);

const PIN_FxnTable PINBLXXX_fxnTable = {
    PINBLXXX_close,
    PINBLXXX_control,
    PINBLXXX_open,
    PINBLXXX_init,
    PINBLXXX_write,
    PINBLXXX_read,
    PINBLXXX_changeDir,
};

uint_fast8_t PINBLXXX_close(PIN_Handle handle)
{
    NVIC_DisableIRQ(GPIO_INT0_IRQn);
    return 0;
}

int_fast16_t PINBLXXX_control(PIN_Handle handle, uint_fast16_t cmd, void *arg)
{
    return 0;
}

void PINBLXXX_init(PIN_Handle handle)
{
    //todo
}

void PINBLXXX_callback(void)
{
    PINBLXXX_Object const *object;
    GLB_GPIO_Type gpioPin;

    object = pin_handle_temp->object;

    for (gpioPin = GLB_GPIO_PIN_0; gpioPin <= GLB_GPIO_PIN_22; gpioPin++)
    {
        if (SET == GLB_Get_GPIO_IntStatus(gpioPin))
        {
            if (pin_handle_temp != NULL)
            {
                object->pin_callback(pin_handle_temp, gpioPin);
            }
        }
    }
}

PIN_Handle PINBLXXX_open(PIN_Handle handle,PIN_Params * params,const PIN_List pinList[])
{
    uint32_t i = 0;
    GLB_GPIO_Cfg_Type gpio_cfg;
    PINBLXXX_Object *object;

    object = handle->object;

    object ->pin_callback = params->pin_callback;

    for (i = 0; PIN_ID(pinList[i]) != PIN_TERMINATE; i++)
    {
        // Ignore unassigned pins
        if (PIN_ID(pinList[i]) == PIN_UNASSIGNED)
        {
            continue;
        }
        // Check that pin exists and is available
        if (PIN_ID(pinList[i]) > BL702_PIN_MAX)
        {
            MSG("PIN_NO_ACCESS\r\n");
            return NULL;
            /*return PIN_NO_ACCESS;*/
        }

        if(PIN_GEN & pinList[i]){
            gpio_cfg.gpioPin = PIN_ID(pinList[i]);
            gpio_cfg.gpioFun = 11;

            if ((pinList[i] & PIN_GPIO_OUTPUT_EN) == PIN_GPIO_OUTPUT_EN)
            {
                gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
                GLB_GPIO_OUTPUT_Enable(PIN_ID(pinList[i]));
 
                gpio_cfg.smtCtrl = 1;
            }else{
                gpio_cfg.gpioMode = GPIO_MODE_INPUT;
                gpio_cfg.smtCtrl = 0;
                GLB_GPIO_INPUT_Enable(PIN_ID(pinList[i]));
                GLB_GPIO_OUTPUT_Disable(PIN_ID(pinList[i]));
            }
            
            gpio_cfg.pullType = GPIO_PULL_NONE;

            if ((pinList[i] & PIN_PULLDOWN) == PIN_PULLDOWN)
            {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
            }

            if ((pinList[i] & PIN_PULLUP) == PIN_PULLUP)
            {
                gpio_cfg.pullType = GPIO_PULL_UP;
            }

            if ((pinList[i] & PIN_DRVSTR_MAX) == PIN_DRVSTR_MAX)
            {
                gpio_cfg.drive = 1;
            }
            else
            {
                gpio_cfg.drive = 0;
            }

            GLB_GPIO_Init(&gpio_cfg);

            if(gpio_cfg.gpioMode == GPIO_MODE_OUTPUT){
                if ((pinList[i] & PIN_GPIO_HIGH) == PIN_GPIO_HIGH)
                {
                    GLB_GPIO_Write(PIN_ID(pinList[i]), 1);
                }
                else
                {
                    GLB_GPIO_Write(PIN_ID(pinList[i]), 0);
                }
            }
            
            if (((pinList[i] & (PIN_IRQ_NEGEDGE)) == PIN_IRQ_NEGEDGE) || ((pinList[i] & (PIN_IRQ_POSEDGE)) == PIN_IRQ_POSEDGE)){
                if((pinList[i] & (PIN_INPUT_EN)) == PIN_INPUT_EN){
                    //gpio external interrupt open
                    GLB_GPIO_IntMask(PIN_ID(pinList[i]), MASK);

                    if ((pinList[i] & PIN_IRQ_NEGEDGE) == PIN_IRQ_NEGEDGE)
                    {
                        GLB_Set_GPIO_IntMod(PIN_ID(pinList[i]), GLB_GPIO_INT_CONTROL_ASYNC, GLB_GPIO_INT_TRIG_NEG_PULSE);
                    }

                    if ((pinList[i] & PIN_IRQ_POSEDGE) == PIN_IRQ_POSEDGE)
                    {
                        GLB_Set_GPIO_IntMod(PIN_ID(pinList[i]), GLB_GPIO_INT_CONTROL_ASYNC, GLB_GPIO_INT_TRIG_NEG_PULSE);
                    }
                    //enable
                    GLB_GPIO_INT0_Callback_Install(PIN_ID(pinList[i]), PINBLXXX_callback);
                    GLB_GPIO_IntMask(PIN_ID(pinList[i]), UNMASK);
                    NVIC_EnableIRQ(GPIO_INT0_IRQn);
                }
            }
        }else{
            /*return PIN_UNSUPPORTED;*/
            MSG("PIN_UNSUPPORTED 2\r\n");
            return NULL;
        }
    }

    pin_handle_temp = handle;

    return handle;
}


void PINBLXXX_write(PIN_Handle handle,PIN_List pin , uint8_t value){
    GLB_GPIO_Write(pin, value);
}

uint32_t PINBLXXX_read(PIN_Handle handle,PIN_List pin){
    return GLB_GPIO_Read(pin);
}

void PINBLXXX_changeDir(PIN_Handle handle, uint8_t pin_index , PIN_Dir dir){

    if(dir == PIN_DIR_OUTPUT){
        GLB_GPIO_INPUT_Disable(pin_index);
        GLB_GPIO_OUTPUT_Enable(pin_index);
    }else{
        GLB_GPIO_OUTPUT_Disable(pin_index);
        GLB_GPIO_INPUT_Enable(pin_index);
    }
}