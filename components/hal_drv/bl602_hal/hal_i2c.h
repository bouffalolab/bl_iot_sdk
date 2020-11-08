/*
 * Copyright (c) 2020 Bouffalolab.
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
#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include <bl_i2c.h>

#define EV_I2C_END_INT       0
#define EV_I2C_TXF_INT       1
#define EV_I2C_RXF_INT       3
#define EV_I2C_FER_INT       4
#define EV_I2C_ARB_INT       5
#define EV_I2C_NAK_INT       6
#define EV_I2C_UNKNOW_INT    0xff

int hal_i2c_init(int i2cx, int freq);
int hal_i2c_read_block(int address, char *data, int length, int subaddr_len, int subaddr);
int hal_i2c_write_block(int address, const char *data, int length, int subaddr_len, int subaddr);
int hal_i2c_write_no_block(int address, const char *data, int length, int subaddr_len, int subaddr);
int hal_i2c_read_no_block(int address, const char *data, int length, int subaddr_len, int subaddr);

int i2c_transfer_msgs_block(i2c_msg_t *pstmsg, int num, int support_ins);
void i2c_msgs_process(i2c_msg_t *pstmsg);
void i2c_insert_msgs_process(i2c_msg_t *pstmsg);

#endif
