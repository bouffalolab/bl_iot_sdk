/**
 * *****************************************************************************
 * @file lhal_bl702_pwm.h
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
#include <stdbool.h>
#include "hal_pwm.h"

#define PWM_MAX_PIN_NUM     5
typedef struct PWMBLXXX_HWAttrsV2 {

    uint8_t pwm_output_pin[PWM_MAX_PIN_NUM];
    
} PWMBLXXX_HWAttrsV2;

 /*!
 *  @brief      PWMBLXXX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct {
    bool opened;

    PWM_Work_Mode PWM_work_mode;
    HAL_PWM_Polarity_Type PWM_polarity;
    uint16_t PWM_clock_div;
    uint16_t PWM_wave_period;
    uint16_t PWM_toggle_threshold_1;
    uint16_t PWM_toggle_threshold_2;

    uint16_t PWM_pluse_count;
    PWM_Callback PWM_pluse_counter_done_callback;

} PWMBLXXX_Object, *PWMBLXXX_Handle;

uint_fast8_t         PWMBLXXX_close(PWM_Handle handle);
int_fast16_t         PWMBLXXX_control(PWM_Handle handle, uint_fast16_t cmd,void *arg);
void                 PWMBLXXX_init(PWM_Handle handle);
PWM_Handle           PWMBLXXX_open(PWM_Handle handle, PWM_Params *params);
