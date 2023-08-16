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

#ifndef __WM8978_H
#define __WM8978_H

#include "stdint.h"

#define WM8978_ADDR 0X1A

#define EQ1_80Hz  0X00
#define EQ1_105Hz 0X01
#define EQ1_135Hz 0X02
#define EQ1_175Hz 0X03

#define EQ2_230Hz 0X00
#define EQ2_300Hz 0X01
#define EQ2_385Hz 0X02
#define EQ2_500Hz 0X03

#define EQ3_650Hz   0X00
#define EQ3_850Hz   0X01
#define EQ3_1100Hz  0X02
#define EQ3_14000Hz 0X03

#define EQ4_1800Hz 0X00
#define EQ4_2400Hz 0X01
#define EQ4_3200Hz 0X02
#define EQ4_4100Hz 0X03

#define EQ5_5300Hz  0X00
#define EQ5_6900Hz  0X01
#define EQ5_9000Hz  0X02
#define EQ5_11700Hz 0X03

uint8_t WM8978_Init(void);
void WM8978_ADDA_Cfg(uint8_t dacen, uint8_t adcen);
void WM8978_Input_Cfg(uint8_t micen, uint8_t lineinen, uint8_t auxen);
void WM8978_Output_Cfg(uint8_t dacen, uint8_t bpsen);
void WM8978_MIC_Gain(uint8_t gain);
void WM8978_LINEIN_Gain(uint8_t gain);
void WM8978_AUX_Gain(uint8_t gain);
uint8_t WM8978_Write_Reg(uint8_t reg, uint16_t val);
uint16_t WM8978_Read_Reg(uint8_t reg);
void WM8978_HPvol_Set(uint8_t voll, uint8_t volr);
void WM8978_SPKvol_Set(uint8_t volx);
void WM8978_I2S_Cfg(uint8_t fmt, uint8_t len);
void WM8978_PlayMode(void);
void WM8978_RecoMode(void);
void WM8978_3D_Set(uint8_t depth);
void WM8978_EQ_3D_Dir(uint8_t dir);
void WM8978_EQ1_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ2_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ3_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ4_Set(uint8_t cfreq, uint8_t gain);
void WM8978_EQ5_Set(uint8_t cfreq, uint8_t gain);

bool wm8978_master_cfg(void);
#endif