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
#ifndef __HAL_PWM__H__
#define __HAL_PWM__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define DEVICE_CTRL_PWM_CHANNEL_CONFIG   0x10
#define DEVICE_CTRL_PWM_BREAK_CONFIG     0x11
#define DEVICE_CTRL_PWM_FREQUENCE_CONFIG 0x12
#define DEVICE_CTRL_PWM_DUTYCYCLE_CONFIG 0x13
#define DEVICE_CTRL_PWM_PULSE_CONFIG     0x14

enum pwm_index_type {
#ifdef BSP_USING_PWM0
    PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
    PWM_MAX_INDEX
};

#define PWM_CHANNEL_0 (1 << 0)
#define PWM_CHANNEL_1 (1 << 1)
#define PWM_CHANNEL_2 (1 << 2)
#define PWM_CHANNEL_3 (1 << 3)

#define PWM_SINGLE_OUTPUT_MODE   0
#define PWM_CONTINUE_OUTPUT_MODE 1

#define PWM_CLK_SOURCE_XCLK 0
#define PWM_CLK_SOURCE_BCLK 1
#define PWM_CLK_SOURCE_32K  2

enum pwm_event_type {
    PWM_EVENT_PERIOD_END,
    PWM_EVENT_PULSE,
    PWM_EVENT_BREAK,
};

typedef struct
{
    uint8_t ch;
    uint8_t chp_enable;
    uint8_t chn_enable;
    uint8_t chp_polarity;
    uint8_t chn_polarity;
    uint8_t chp_idlestate;
    uint8_t chn_idlestate;
    uint16_t threshold_low;
    uint16_t threshold_high;
} pwm_channel_common_t;

typedef struct
{
    uint8_t ch;
    uint16_t threshold_low;
    uint16_t threshold_high;
} pwm_channel_dutycycle_t;

typedef struct
{
    uint8_t ch;
    uint8_t chp_breakstate;
    uint8_t chn_breakstate;
    uint8_t deadtime;
} pwm_channel_break_t;

typedef struct pwm_device {
    struct device parent;
    uint8_t id;
    uint8_t clk_source;
    uint8_t clk_div;
    uint8_t output_mode;
    uint16_t period;
    uint16_t pulse;
    uint8_t extern_break_polarity;
    uint8_t extern_break_enable;
    uint8_t internal_break_enable;
    uint8_t adc_trig_source;
} pwm_device_t;

#define PWM_DEV(dev) ((pwm_device_t *)dev)

int pwm_register(enum pwm_index_type index, const char *name);

#ifdef __cplusplus
}
#endif
#endif
