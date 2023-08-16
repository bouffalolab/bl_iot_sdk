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
#ifndef __PLATFORM_GPIO_H__
#define __PLATFORM_GPIO_H__

#include "bl808_glb.h"
#include "bl808_gpio.h"
#include "bl808_glb_gpio.h"
#include "bl808_uart.h"


#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    /*UART  dbug option */
    #define BFLB_UART_DBG_RX_GPIO          GLB_GPIO_PIN_19
    #define BFLB_UART_DBG_RX_INPUT_FUN     GPIO19_FUN_SWGPIO_19
    #define BFLB_UART_DBG_RX_NORMAL_FUN    GPIO19_FUN_UART_SIG7
    #define BFLB_UART_DBG_RX_SIG           GLB_UART_SIG_7
    #define BFLB_UART_DBG_RX_SIG_FUN       GLB_UART_SIG_FUN_UART1_RXD

    #define BFLB_UART_DBG_TX_GPIO          GLB_GPIO_PIN_39
    #define BFLB_UART_DBG_TX_INPUT_FUN     GPIO39_FUN_SWGPIO_39
    #define BFLB_UART_DBG_TX_NORMAL_FUN    GPIO39_FUN_UART_SIG3
    #define BFLB_UART_DBG_TX_SIG           GLB_UART_SIG_3
    #define BFLB_UART_DBG_TX_SIG_FUN       GLB_UART_SIG_FUN_UART0_TXD
#else
    #define BFLB_UART_DBG_TX_GPIO          GLB_GPIO_PIN_39
    #define BFLB_UART_DBG_TX_INPUT_FUN     GPIO39_FUN_SWGPIO_39
    #define BFLB_UART_DBG_TX_NORMAL_FUN    GPIO39_FUN_UART_SIG3
    #define BFLB_UART_DBG_TX_SIG           GLB_UART_SIG_3
    #define BFLB_UART_DBG_TX_SIG_FUN       GLB_UART_SIG_FUN_UART0_TXD
#endif



void bflb_platform_init_uart_debug_gpio(void);
void bflb_platform_deinit_uart_debug_gpio(void);


#endif

