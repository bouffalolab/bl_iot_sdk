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
#ifndef __HAL_TIMER__H__
#define __HAL_TIMER__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define DEVICE_CTRL_TIMER_CH_START 0x80
#define DEVICE_CTRL_TIMER_CH_STOP  0x81

enum timer_index_type {
#ifdef BSP_USING_TIMER_CH0
    TIMER_CH0_INDEX,
#endif
#ifdef BSP_USING_TIMER_CH1
    TIMER_CH1_INDEX,
#endif
    TIMER_MAX_INDEX
};

enum timer_event_type {
    TIMER_EVENT_COMP0,
    TIMER_EVENT_COMP1,
    TIMER_EVENT_COMP2,
    TIMER_EVENT_UNKNOWN
};

enum timer_it_type {
    TIMER_COMP0_IT = 1 << 0,
    TIMER_COMP1_IT = 1 << 1,
    TIMER_COMP2_IT = 1 << 2,
    TIMER_ALL_IT = 1 << 3
};
typedef enum {
    TIMER_CLK_FCLK,
    TIMER_CLK_32K,
    TIMER_CLK_1K,
    TIMER_CLK_XTAL,
} timer_clk_src_t;

typedef enum {
    TIMER_PL_TRIG_NONE,
    TIMER_PL_TRIG_COMP0,
    TIMER_PL_TRIG_COMP1,
    TIMER_PL_TRIG_COMP2,
} timer_pl_trig_t;

typedef enum {
    TIMER_CNT_PRELOAD,
    TIMER_CNT_FREERUN,
} timer_cnt_mode;

typedef struct
{
    uint32_t timeout_val;
    uint32_t comp_it;
} timer_user_cfg_t;

typedef struct timer_device {
    struct device parent;
    uint8_t id;
    uint8_t ch;
    uint8_t clk_div;
    timer_cnt_mode cnt_mode;
    timer_pl_trig_t pl_trig_src;
} timer_device_t;

#define TIMER_DEV(dev) ((timer_device_t *)dev)

int timer_register(enum timer_index_type index, const char *name);

#endif