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
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"
#include "platform_gpio.h"

#define NO_FPGA     0
__WEAK
void bflb_platform_init_uart_debug_gpio()
{
#if NO_FPGA
    /* Todo */
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive=0;
    cfg.smtCtrl=1;

    /*set GPIO as UART TX */
    cfg.gpioPin=BFLB_UART_DBG_TX_GPIO;
    cfg.gpioFun=BFLB_UART_DBG_TX_NORMAL_FUN;
    cfg.gpioMode=GPIO_MODE_OUTPUT;
    cfg.pullType=GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);

    /* select uart gpio function */
    GLB_UART_Fun_Sel(BFLB_UART_DBG_TX_SIG,BFLB_UART_DBG_TX_SIG_FUN);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)BFLB_UART_DBG_TX_SIG_FUN,(GLB_UART_SIG_FUN_Type)BFLB_UART_DBG_TX_SIG);

#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    /*set GPIO as UART RX */
    cfg.gpioPin=BFLB_UART_DBG_RX_GPIO;
    cfg.gpioFun=BFLB_UART_DBG_RX_NORMAL_FUN;
    cfg.gpioMode=GPIO_MODE_INPUT;
    cfg.pullType=GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);
    /* select uart gpio function */
    GLB_UART_Fun_Sel(BFLB_UART_DBG_RX_SIG,BFLB_UART_DBG_RX_SIG_FUN);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)BFLB_UART_DBG_RX_SIG_FUN,(GLB_UART_SIG_FUN_Type)BFLB_UART_DBG_RX_SIG);
#endif
#endif
}

__WEAK
void bflb_platform_deinit_uart_debug_gpio()
{
#if NO_FPGA
    GLB_GPIO_Cfg_Type cfg;

    cfg.gpioMode=GPIO_MODE_INPUT;
    cfg.pullType=GPIO_PULL_NONE;
    cfg.drive=0;
    cfg.smtCtrl=1;

    /*set GPIO as input */
    cfg.gpioPin=BFLB_UART_DBG_TX_GPIO;
    cfg.gpioFun=BFLB_UART_DBG_TX_INPUT_FUN;
    GLB_GPIO_Init(&cfg);

    GLB_UART_Sig_Swap_Set(UART_SIG_SWAP_NONE);

    /* restore uart function sel*/
    GLB_UART_Fun_Sel(BFLB_UART_DBG_TX_SIG,(GLB_UART_SIG_FUN_Type)BFLB_UART_DBG_TX_SIG);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)BFLB_UART_DBG_TX_SIG_FUN,BFLB_UART_DBG_TX_SIG_FUN);

#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    /*set GPIO as input */
    cfg.gpioPin=BFLB_UART_DBG_RX_GPIO;
    cfg.gpioFun=BFLB_UART_DBG_RX_INPUT_FUN;
    GLB_GPIO_Init(&cfg);

    /* restore uart function sel*/
    GLB_UART_Fun_Sel(BFLB_UART_DBG_RX_SIG,(GLB_UART_SIG_FUN_Type)BFLB_UART_DBG_RX_SIG); 
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)BFLB_UART_DBG_RX_SIG_FUN,BFLB_UART_DBG_RX_SIG_FUN);

#endif
#endif
}
