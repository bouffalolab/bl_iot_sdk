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
#ifndef __BL602_MFG_EFUSE_H__
#define __BL602_MFG_EFUSE_H__

#include "stdint.h"

uint8_t mfg_efuse_get_rf_cal_slots(void);
void mfg_efuse_set_rf_cal_slots(uint8_t slots);
uint8_t mfg_efuse_is_xtal_capcode_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_xtal_capcode_pre(uint8_t capcode,uint8_t program);
void mfg_efuse_write_xtal_capcode(void);
int8_t mfg_efuse_read_xtal_capcode(uint8_t *capcode,uint8_t reload);
uint8_t mfg_efuse_is_poweroffset_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program);
void mfg_efuse_write_poweroffset(void);
int8_t mfg_efuse_read_poweroffset(int8_t pwrOffset[14],uint8_t reload);
uint8_t mfg_efuse_is_macaddr_slot_empty(uint8_t reload);
int8_t mfg_efuse_write_macaddr_pre(uint8_t mac[6],uint8_t program);
void mfg_efuse_write_macaddr(void);
int8_t mfg_efuse_read_macaddr(uint8_t mac[6],uint8_t reload);
int8_t mfg_efuse_read(uint32_t addr,uint32_t *data,uint32_t countInword,uint8_t reload);
int8_t mfg_efuse_program(void);
int8_t mfg_efuse_write_pre(uint32_t addr,uint32_t *data,uint32_t countInword);
int8_t mfg_efuse_read_poweroffset_ate(int8_t *pwrOffset);

#endif/*__BL602_MFG_EFUSE_H__*/
