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
#ifndef _XPT2046_H_
#define _XPT2046_H_

#include "bflb_platform.h"

#define TOUCH_PIN_CS GPIO_PIN_6
//#define TOUCH_PIN_PEN GPIO_PIN_11

#define XPT2046_TOUCH_THRESHOLD 500 // Threshold for touch detection

#define XPT2046_AVG_NUM 5

#define TOUCH_ROT_NONE 0
#define TOUCH_ROT_90   1
#define TOUCH_ROT_180  2
#define TOUCH_ROT_270  3

#define XPT2046_X_MIN 310
#define XPT2046_Y_MIN 175
#define XPT2046_X_MAX 3850
#define XPT2046_Y_MAX 3700

#define XPT2046_MAX_POINT 1

extern struct device *touch_spi;
#ifdef __cplusplus
extern "C" {
#endif
void xpt2046_init(void);
uint8_t xpt2046_read(int16_t *x, int16_t *y);
#ifdef __cplusplus
}
#endif
#endif