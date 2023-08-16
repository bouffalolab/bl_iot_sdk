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
#ifndef __HAL_CLOCK__H__
#define __HAL_CLOCK__H__

#include "hal_common.h"

/*XTAL_TYPE*/
#define XTAL_NONE           0
#define EXTERNAL_XTAL_24M   1
#define EXTERNAL_XTAL_32M   2
#define EXTERNAL_XTAL_38P4M 3
#define EXTERNAL_XTAL_40M   4
#define EXTERNAL_XTAL_26M   5
#define INTERNAL_RC_32M     6

/*CLOCK_32K_XTAL*/
#define EXTERNAL_XTAL_32K 0
#define INTERNAL_RC_32K   1

#define ROOT_CLOCK_SOURCE_32K_CLK      0
#define ROOT_CLOCK_SOURCE_XCLK         1
#define ROOT_CLOCK_SOURCE_WIFIPLL_32M  2
#define ROOT_CLOCK_SOURCE_WIFIPLL_48M  3
#define ROOT_CLOCK_SOURCE_WIFIPLL_80M  4
#define ROOT_CLOCK_SOURCE_WIFIPLL_96M  5
#define ROOT_CLOCK_SOURCE_WIFIPLL_160M 6
#define ROOT_CLOCK_SOURCE_WIFIPLL_240M 7
#define ROOT_CLOCK_SOURCE_WIFIPLL_320M 8
#define ROOT_CLOCK_SOURCE_CPUPLL_80M   9
#define ROOT_CLOCK_SOURCE_CPUPLL_100M  10
#define ROOT_CLOCK_SOURCE_CPUPLL_160M  11
#define ROOT_CLOCK_SOURCE_CPUPLL_200M  12
#define ROOT_CLOCK_SOURCE_CPUPLL_400M  13
#define ROOT_CLOCK_SOURCE_AUPLL_DIV1   14
#define ROOT_CLOCK_SOURCE_AUPLL_DIV2   15
#define ROOT_CLOCK_SOURCE_AUPLL_DIV2P5 16
#define ROOT_CLOCK_SOURCE_AUPLL_DIV5   17
#define ROOT_CLOCK_SOURCE_AUPLL_DIV6   18
#define ROOT_CLOCK_SOURCE_AUPLL_CLK    19

#define BSP_CLOCK_SOURCE_FCLK 20
#define BSP_CLOCK_SOURCE_BCLK 21

#define BSP_CLOCK_SOURCE_MUXPLL_80M  ROOT_CLOCK_SOURCE_WIFIPLL_80M
#define BSP_CLOCK_SOURCE_MUXPLL_160M ROOT_CLOCK_SOURCE_WIFIPLL_160M

void system_clock_init(void);
void peripheral_clock_init(void);
void system_mtimer_clock_init(void);
void system_mtimer_clock_reinit(void);
#endif