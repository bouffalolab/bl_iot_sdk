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
#ifndef __BFLB_PLATFORM__H__
#define __BFLB_PLATFORM__H__

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <string.h>
#include "launch.h"
#include "bflb_stub.h"
#include "mcu_sdk_version.h"
#include "hal_uart.h"


#define MSG(a,...)              bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_DBG(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_WAR(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define MSG_ERR(a,...)          bflb_platform_printf(a,##__VA_ARGS__)
#define BL_CASE_FAIL            {MSG(" Case Fail\r\n");while(1){}}
#define BL_CASE_SUCCESS         {MSG(" Case Success\r\n");while(1){}}


typedef void (*bflb_platform_ring_buffer_load_callback) (UART_Handle handle);


void bflb_platform_print_set(uint8_t logDisable);
void bflb_platform_printf(char *fmt,...);
void bflb_platform_prints(char *data);
void bflb_platform_print_hex(uint8_t * buf , uint16_t len);
void bflb_platform_init(uint32_t baudrate);
void bflb_platform_uart_dbg_init(uint32_t bdrate);

void bflb_platform_deinit(void);
int bflb_platform_get_random(uint8_t *data,uint32_t len);
void bflb_platform_init_time(void);
void bflb_platform_clear_time(void);
uint64_t bflb_platform_get_time_ms(void);
uint64_t bflb_platform_get_time_us(void);
void bflb_platform_start_time(void);
void bflb_platform_stop_time(void);
void bflb_platform_set_alarm_time_callback(void( *interruptFun )( void ));
void bflb_platform_set_alarm_time(uint64_t time);
void bflb_platform_deinit_time(void);
void bflb_platform_delay_ms(uint32_t time);
void bflb_platform_delay_us(uint32_t time);
void bflb_platform_install_callback(bflb_platform_ring_buffer_load_callback fxn);



typedef enum 
{
  BFLB_SUCCESS  = 0, 
  BFLB_ERROR   = 1,
  BFLB_TIMEOUT = 2,
}BFLB_Err_Type;

#endif