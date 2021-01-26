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
#ifndef USIP_H_
#define USIP_H_

#include <stdint.h>
#include <stddef.h>
#include "los_sem.h"

#define USIP_IS_MCU  1 // 1 MCU  0 WIFI
#define USIP_LOG

#if USIP_IS_MCU
#define USIP_MCU
#else
#define USIP_WIFI
#endif


#ifdef USIP_LOG
#ifdef USIP_MCU
#define USIP_PRINTF printf
#else
#define USIP_PRINTF DBG_8195A
#endif
#endif

#define END     0xC0 //frame end
#define ESC     0xDB //frame escape
#define ESC_END 0xDC //transposed frame END
#define ESC_ESC 0xDD //transposed Frame Escape

#define USIP_FRM_MAX_LEN      128  //HEAD+PKGNUM+SEQ+CMD+TLVS+CRC8+END <= 128
#define USIP_FRM_DATA_MAX_LEN (USIP_FRM_MAX_LEN - 2)  //PKGNUM+SEQ+CMD+TLVS+CRC8
#define USIP_FRM_CMD_AND_TLVS_MAX_LEN (USIP_FRM_DATA_MAX_LEN - 3) //CMD+TLVS


#define USIP_CRC_TABLE_LEN 256 //CRC8 table length

#define USIP_UART_RCV_BUFF    2048 //USIP uart receive buffer length
#define USIP_UART_SKB_NUM   USIP_UART_RCV_BUFF/USIP_FRM_MAX_LEN

#define USIP_EA_BIT 0X80
#define USIP_EA_VALID_BITS 7

#define USIP_WAIT_ACK_TIMEOUT 50 //milliseconds
#define USIP_MAX_ARQ_TIMES  3 //Retransmission

//PKGNUM
#define USIP_PKGNUM_MAX      0X7F

//SEQ
#define USIP_SEQ_MAX 0X7F
#define USIP_SEQ_MIN 0X00

//CMD
#define USIP_CMD_DEV_REG  0X01  //devreg
#define USIP_CMD_SESS_MNGR  0X02  // online
#define USIP_CMD_FILE_MNGR  0X03  //update
#define USIP_CMD_DEV_REG_RSP  0X04  //devreg response
#define USIP_CMD_SESS_MNGR_RSP  0X05  // online response
#define USIP_CMD_FILE_MNGR_RSP  0X06  //update response

#define USIP_CMD_DATA_REPORT 0X07
#define USIP_CMD_DATA_REPORT_RSP 0X08

//tag
#define USIP_TLV_TAG_ACK       0x00  //ack
//put JSON data to val of one tlv. tag only suport one byte now
#define USIP_TLV_TAG_RST       0X01  //request
#define USIP_TLV_TAG_RSPT       0X02  //response of request
#define USIP_TLV_TAG_LEN       1

#define USIP_OK  0X00
#define USIP_ERROR  0XFF

typedef void (*cmd_process_callback)(unsigned short cmd, unsigned char* data, unsigned short len);

UINT32 usip_init();
void receive_one_byte(unsigned char data);// receive one byte through UART serial port
int usip_send_data(unsigned short cmd,unsigned char* data, unsigned short len);
void register_cmd_process_callback(cmd_process_callback cmd_process);
int usip_rec_task_entry();
#endif /* USIP_H_ */
