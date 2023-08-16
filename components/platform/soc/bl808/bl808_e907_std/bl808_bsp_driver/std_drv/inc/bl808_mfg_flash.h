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
#ifndef __BL602_MFG_FLASH_H__
#define __BL602_MFG_FLASH_H__

#include "stdint.h"
#include "bl808_xip_sflash.h"

typedef struct rf_para_flash_tag{
    uint32_t magic;            //"RFPA"
    uint8_t capcode_valid;     //0x5A
    uint8_t capcode;
    uint8_t poweroffset_valid; //0x5A
    int8_t poweroffset[3];
    uint8_t mac_valid;         //0x5A
    uint8_t mac[6];
    uint8_t rsvd[3];
    uint32_t crc32;
}rf_para_flash_t;

int8_t mfg_flash_init( SPI_Flash_Cfg_Type *flashCfg);
int8_t mfg_flash_write_xtal_capcode_pre(uint8_t capcode,uint8_t program);
void mfg_flash_write_xtal_capcode(void);
int8_t mfg_flash_read_xtal_capcode(uint8_t *capcode,uint8_t reload);
int8_t mfg_flash_write_poweroffset_pre(int8_t pwrOffset[14],uint8_t program);
void mfg_flash_write_poweroffset(void);
int8_t mfg_flash_read_poweroffset(int8_t pwrOffset[14],uint8_t reload);
int8_t mfg_flash_write_macaddr_pre(uint8_t mac[6],uint8_t program);
void mfg_flash_write_macaddr(void);
int8_t mfg_flash_read_macaddr(uint8_t mac[6],uint8_t reload);

#endif/*__BL602_MFG_FLASH_H__*/
