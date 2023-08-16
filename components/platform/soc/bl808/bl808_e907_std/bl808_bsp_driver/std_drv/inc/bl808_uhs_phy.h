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
#ifndef __UHS_PHY_H__
#define __UHS_PHY_H__

#include "bl808_common.h"
// /** @addtogroup Configuration_section_for_RISCV
//   * @{
//   */
// #define BL_RD_WORD(addr)                             (*((volatile uint32_t*)(addr)))
// #define BL_WR_WORD(addr,val)                         ((*(volatile uint32_t*)(addr))=(val))
// #define BL_RD_SHORT(addr)                            (*((volatile uint16_t*)(addr)))
// #define BL_WR_SHORT(addr,val)                        ((*(volatile uint16_t*)(addr))=(val))
// #define BL_RD_BYTE(addr)                             (*((volatile uint8_t*)(addr)))
// #define BL_WR_BYTE(addr,val)                         ((*(volatile uint8_t*)(addr))=(val))
// #define BL_RDWD_FRM_BYTEP(p)                         ((p[3]<<24)|(p[2]<<16)|(p[1]<<8)|(p[0]))
// #define BL_WRWD_TO_BYTEP(p,val)                      {p[0]=val&0xff;p[1]=(val>>8)&0xff;p[2]=(val>>16)&0xff;p[3]=(val>>24)&0xff;}
// /**
//  * @brief Register access macro
//  */
// #define BL_RD_REG16(addr,regname)                    BL_RD_SHORT(addr+regname##_OFFSET)
// #define BL_WR_REG16(addr,regname,val)                BL_WR_SHORT(addr+regname##_OFFSET,val)
// #define BL_RD_REG(addr,regname)                      BL_RD_WORD(addr+regname##_OFFSET)
// #define BL_WR_REG(addr,regname,val)                  BL_WR_WORD(addr+regname##_OFFSET,val)
// #define BL_SET_REG_BIT(val,bitname)                  ( (val) |(1U<<bitname##_POS))
// #define BL_CLR_REG_BIT(val,bitname)                  ( (val) & bitname##_UMSK )
// #define BL_GET_REG_BITS_VAL(val,bitname)             ( ((val) & bitname##_MSK) >> bitname##_POS )
// #define BL_SET_REG_BITS_VAL(val,bitname,bitval)      ( ((val)&bitname##_UMSK) | ((uint32_t)(bitval)<<bitname##_POS) )
// #define BL_IS_REG_BIT_SET(val,bitname)               ( ((val)&(1U<<(bitname##_POS))) !=0 )
// #define BL_DRV_DUMMY                                 {__NOP();__NOP();__NOP();__NOP();}

enum {
    UHS_LATENCY_CODE_533 = 3, // "0"
    UHS_LATENCY_CODE_800 = 3, // "1"
    UHS_LATENCY_CODE_933 = 3, // "2"
    UHS_LATENCY_CODE_1066 = 3,
    UHS_LATENCY_CODE_RESERVED = 3, //"4"
    UHS_LATENCY_CODE_400 = 3, //"5"
    UHS_LATENCY_CODE_333 = 3, //"6"
    UHS_LATENCY_CODE_200 = 3, //"7"
};

// function call  
void uhs_phy_init(uint32_t datarate);        
void uhs_phy_pwr_down(void);
void soft_reset(void);

#endif  // __UHS_PHY_H__