/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
#include "usart.h"
#include "stm32f4xx.h"
#include <los_hwi.h>

#include "usip.h"
#include "usip_uart.h"

static USART_TypeDef*     s_pUSART = USART1;
static uint32_t           s_uwIRQn = USART1_IRQn;

UART_HandleTypeDef usip_uart_handle;

static UINT32 g_send_timeout = 0;
// deal uart interrupt
void usip_uart_irq(void)
{
    uint8_t data;
    if(__HAL_UART_GET_FLAG(&usip_uart_handle, UART_FLAG_RXNE) != RESET)   //receive Data register not empty interrupt.
    {
        data = (uint8_t)(usip_uart_handle.Instance->DR & 0x00FF);
        receive_one_byte(data);
    }
}

void usip_uart_init()
{
    //initialize the usip_uart
    usip_uart_handle.Instance = s_pUSART;
    usip_uart_handle.Init.BaudRate = 115200;
    usip_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    usip_uart_handle.Init.StopBits = UART_STOPBITS_1;
    usip_uart_handle.Init.Parity = UART_PARITY_NONE;
    usip_uart_handle.Init.Mode = UART_MODE_TX_RX;
    usip_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    usip_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&usip_uart_handle) != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
    }

    //create a hardware interrupt to deal usip_uart_irq
    LOS_HwiCreate(s_uwIRQn, 3, 0, usip_uart_irq, 0);

    __HAL_UART_CLEAR_FLAG(&usip_uart_handle,UART_FLAG_TC);

    //enable usip_uart UART_IT_RXNE interrupt
    __HAL_UART_ENABLE_IT(&usip_uart_handle,UART_IT_RXNE);//Receive Data register not empty interrupt

    __HAL_UART_ENABLE(&usip_uart_handle);

    g_send_timeout = LOS_MS2Tick(USIP_WAIT_ACK_TIMEOUT);
}

void send_one_byte(unsigned char data)
{
    HAL_UART_Transmit(&usip_uart_handle,&data,1,g_send_timeout);
}

