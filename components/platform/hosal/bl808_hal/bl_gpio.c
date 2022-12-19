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
#include <stdint.h>

#include <bl808_glb.h>
#include <bl808_gpio.h>
#include "bl_gpio.h"

int bl_gpio_enable_output(uint8_t pin, uint8_t pullup, uint8_t pulldown)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = pin;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.gpioMode = GPIO_MODE_OUTPUT;
    cfg.pullType = GPIO_PULL_NONE;
    if (pullup) {
        cfg.pullType = GPIO_PULL_UP;
    }
    if (pulldown) {
        cfg.pullType = GPIO_PULL_DOWN;
    }
    GLB_GPIO_Init(&cfg);

    return 0;
}

int bl_gpio_enable_input(uint8_t pin, uint8_t pullup, uint8_t pulldown)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = pin;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    if (pullup) {
        cfg.pullType = GPIO_PULL_UP;
    }
    if (pulldown) {
        cfg.pullType = GPIO_PULL_DOWN;
    }
    GLB_GPIO_Init(&cfg);

    return 0;
}

int bl_gpio_output_set(uint8_t pin, uint8_t value)
{
    GLB_GPIO_Write((GLB_GPIO_Type)pin, value ? 1 : 0);
    return 0;
}

int bl_gpio_input_get(uint8_t pin, uint8_t *value)
{
    *value = GLB_GPIO_Read((GLB_GPIO_Type)pin);
    return 0;
}

int bl_gpio_input_get_value(uint8_t pin)
{
    return GLB_GPIO_Read((GLB_GPIO_Type)pin);
}

#if 0
void SDH_GPIO_Init(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[2];
    uint8_t gpiofuns[2];
    uint8_t gpioMode[2];
    int i;

    GLB_Set_SDH_CLK(1,GLB_SDH_CLK_24M);

    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_NONE;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioMode=GPIO_MODE_OUTPUT;


    gpiopins[0]=GLB_GPIO_PIN_16;
    gpiopins[1]=GLB_GPIO_PIN_17;
    gpiofuns[0]=GPIO16_FUN_SDH_CLK;
    gpiofuns[1]=GPIO17_FUN_SDH_CMD;
    gpioMode[0]=GPIO_MODE_AF;
    gpioMode[1]=GPIO_MODE_AF;

    for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
        cfg.gpioPin=gpiopins[i];
        cfg.gpioFun=gpiofuns[i];
        cfg.gpioMode=gpioMode[i];
        GLB_GPIO_Init(&cfg);
    }
}
#endif
