/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include "hal_pwm.h"
#include "hal_clock.h"
#include "bl808_pwm.h"

static pwm_device_t pwmx_device[PWM_MAX_INDEX] = {
#ifdef BSP_USING_PWM0
    PWM0_CONFIG,
#endif
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif
};

static void PWM_IRQ(void);

int pwm_open(struct device *dev, uint16_t oflag)
{
    pwm_device_t *pwm_device = (pwm_device_t *)dev;
    PWMx_CFG_Type pwmxCfg = { 0 };

    CPU_Interrupt_Disable(PWM_IRQn);
    PWMx_Disable(pwm_device->id);
    PWM_SW_Break_Disable(pwm_device->id);
    PWM_Int_Mask(pwm_device->id, PWM_INT_ALL, MASK);

    pwmxCfg.clk = pwm_device->clk_source;
    pwmxCfg.clkDiv = pwm_device->clk_div;
    pwmxCfg.stopMode = PWM_STOP_GRACEFUL;
    pwmxCfg.stpRept = pwm_device->output_mode;
    pwmxCfg.extPol = pwm_device->extern_break_polarity;
    pwmxCfg.adcSrc = pwm_device->adc_trig_source;
    pwmxCfg.intPulseCnt = pwm_device->pulse;
    PWMx_Init(pwm_device->id, &pwmxCfg);

    if (pwm_device->extern_break_enable) {
        PWM_EXT_Break_Enable(pwm_device->id);
    } else {
        PWM_EXT_Break_Disable(pwm_device->id);
    }

    if (pwm_device->internal_break_enable) {
        PWM_SW_Break_Enable(pwm_device->id);
    } else {
        PWM_SW_Break_Disable(pwm_device->id);
    }

    Interrupt_Handler_Register(PWM_IRQn, PWM_IRQ);
    CPU_Interrupt_Enable(PWM_IRQn);

    return 0;
}
int pwm_close(struct device *dev)
{
    pwm_device_t *pwm_device = (pwm_device_t *)dev;
    PWM_CHx_CFG_Type chxCfg = { 0 };

    CPU_Interrupt_Disable(PWM_IRQn);
    PWMx_Disable(pwm_device->id);
    PWM_Int_Mask(pwm_device->id, PWM_INT_ALL, MASK);

    for (uint8_t i = 0; i < PWM_CHx_MAX; i++) {
        PWM_Channelx_Init(pwm_device->id, i, &chxCfg);
    }
    PWM_SW_Break_Disable(pwm_device->id);
    PWM_EXT_Break_Disable(pwm_device->id);

    return 0;
}

int pwm_control(struct device *dev, int cmd, void *args)
{
    pwm_device_t *pwm_device = (pwm_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT:
            break;
        case DEVICE_CTRL_CLR_INT:
            break;
        case DEVICE_CTRL_CONFIG:
            break;
        case DEVICE_CTRL_PWM_CHANNEL_CONFIG: {
            pwm_channel_common_t *config = (pwm_channel_common_t *)args;

            PWM_Channelx_Pwm_Mode_Set(pwm_device->id, config->ch, config->chp_enable, config->chn_enable);
            PWM_Channelx_Polarity_Set(pwm_device->id, config->ch, config->chp_polarity, config->chn_polarity);
            PWM_Channelx_Idle_State_Set(pwm_device->id, config->ch, config->chp_idlestate, config->chn_idlestate);
            PWM_Channelx_Threshold_Set(pwm_device->id, config->ch, config->threshold_low, config->threshold_high);

        } break;

        case DEVICE_CTRL_RESUME:
            PWMx_Enable(pwm_device->id);
            break;

        case DEVICE_CTRL_SUSPEND:
            PWMx_Disable(pwm_device->id);
            break;

        case DEVICE_CTRL_PWM_FREQUENCE_CONFIG:
            PWMx_Period_Set(pwm_device->id, (uint32_t)(uintptr_t)args);
            break;

        case DEVICE_CTRL_PWM_DUTYCYCLE_CONFIG: {
            pwm_channel_dutycycle_t *config = (pwm_channel_dutycycle_t *)args;
            PWM_Channelx_Threshold_Set(pwm_device->id, config->ch, config->threshold_low, config->threshold_high);
        }

        break;

        case DEVICE_CTRL_PWM_PULSE_CONFIG: {
            uint32_t tmpVal;
            uint32_t PWMx = PWM_BASE + PWM_CHANNEL_OFFSET + (pwm_device->id) * 0x40;
            tmpVal = BL_RD_REG(PWMx, PWM_PERIOD);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_INT_PERIOD_CNT, (uint32_t)(uintptr_t)args);
            BL_WR_REG(PWMx, PWM_PERIOD, tmpVal);
        } break;
        case DEVICE_CTRL_PWM_BREAK_CONFIG: {
            pwm_channel_break_t *config = (pwm_channel_break_t *)args;
            PWM_Channelx_Break_State_Set(pwm_device->id, config->ch, config->chp_breakstate, config->chn_breakstate);
            PWM_Channelx_Dtg_Set(pwm_device->id, config->ch, config->deadtime);
        }

        break;
        default:
            break;
    }

    return 0;
}

int pwm_register(enum pwm_index_type index, const char *name)
{
    struct device *dev;

    if (PWM_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(pwmx_device[index].parent);

    dev->open = pwm_open;
    dev->close = pwm_close;
    dev->control = pwm_control;
    dev->write = NULL;
    dev->read = NULL;

    dev->type = DEVICE_CLASS_PWM;
    dev->handle = NULL;

    return device_register(dev, name);
}

static void pwm_isr(pwm_device_t *handle)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t PWMx;
    uint16_t intIndex;

    if (!handle->parent.callback) {
        return;
    }

    /* Get PWMx start register address */
    PWMx = PWM_BASE + PWM_CHANNEL_OFFSET + (handle->id) * 0x40;

    tmpVal = BL_RD_REG(PWMx, PWM_INT_STS);
    maskVal = BL_RD_REG(PWMx, PWM_INT_MASK);

    for (intIndex = 0; intIndex < PWM_INT_ALL; intIndex++) {
        if (((1 << intIndex) & tmpVal) && (((1 << intIndex) & maskVal) == 0)) {
            BL_WR_REG(PWMx, PWM_INT_CLEAR, 1 << intIndex);
            handle->parent.callback(&handle->parent, NULL, 0, 1 << intIndex);
        }
    }
}

static void PWM_IRQ(void)
{
    for (int8_t i = 0; i < PWM_MAX_INDEX; i++) {
        pwm_isr(&pwmx_device[i]);
    }
}
