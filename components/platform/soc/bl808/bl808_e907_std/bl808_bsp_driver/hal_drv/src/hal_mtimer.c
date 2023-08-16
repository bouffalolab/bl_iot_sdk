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
#include "hal_mtimer.h"
#include "bl808_glb.h"

static void (*systick_callback)(void);
static uint64_t current_set_ticks = 0;

static void Systick_Handler(void)
{
    csi_coret_config(current_set_ticks, MTIME_IRQn);
    systick_callback();
}

/**
 * @brief
 *
 */
void mtimer_init(void)
{
    uint32_t clkSrc = CPU_Get_MTimer_Source_Clock();

    CPU_Interrupt_Disable(MTIME_IRQn);

    if (clkSrc > 1 * 1000 * 1000) {
        /* Set MTimer clock source 1M */
        CPU_Set_MTimer_CLK(1, clkSrc / 1000 / 1000 - 1);
    } else {
        /* Set MTimer clock source 1k */
        CPU_Set_MTimer_CLK(1, clkSrc / 1000 - 1);
    }

    /* never reset mtimer */
    //CPU_Reset_MTimer();
}

/**
 * @brief
 *
 */
void mtimer_deinit()
{
    CPU_Interrupt_Disable(MTIME_IRQn);
}
/**
 * @brief
 *
 * @param time
 * @param interruptFun
 */
void mtimer_set_alarm_time(uint64_t ticks, void (*interruptfun)(void))
{
    current_set_ticks = ticks;
    systick_callback = interruptfun;

    csi_coret_config_use(ticks, MTIME_IRQn);
    CPU_Interrupt_Disable(MTIME_IRQn);
    Interrupt_Handler_Register(MTIME_IRQn, Systick_Handler);
    CPU_Interrupt_Enable(MTIME_IRQn);
}
/**
 * @brief
 *
 */
void mtimer_start()
{
}
/**
 * @brief
 *
 */
void mtimer_stop()
{
}
/**
 * @brief
 *
 */
void mtimer_clear_time()
{
    CPU_Reset_MTimer();
}

/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t mtimer_get_time_ms()
{
    return CPU_Get_MTimer_MS();
}
/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t mtimer_get_time_us()
{
    return CPU_Get_MTimer_US();
}
/**
 * @brief
 *
 * @param time
 */
void mtimer_delay_ms(uint32_t time)
{
    CPU_MTimer_Delay_MS(time);
}
/**
 * @brief
 *
 * @param time
 */
void mtimer_delay_us(uint32_t time)
{
    CPU_MTimer_Delay_US(time);
}
