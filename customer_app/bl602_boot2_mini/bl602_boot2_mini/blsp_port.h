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
#ifndef __BLSP_PORT_H__
#define __BLSP_PORT_H__

#include "stdint.h"
#include "bl602_glb.h"
#include "bl602_aon.h"
#include "bl602_hbn.h"
#include "bl602_ef_ctrl.h"
#include "bl602_sflash.h"
#include "bl602_xip_sflash.h"
#include "bl602_sf_cfg.h"
#include "bl602_timer.h"
#include "bl602_sec_eng.h"
#include "bl602_tzc_sec.h"
#include "bflb_ecdsa.h"

/** @addtogroup  BL606_BLSP_Boot2
 *  @{
 */

/** @addtogroup  BLSP_PORT
 *  @{
 */

/** @defgroup  BLSP_PORT_Public_Types
 *  @{
 */

/*@} end of group BLSP_PORT_Public_Types */

/** @defgroup  BLSP_PORT_Public_Constants
 *  @{
 */
/*CPU1's MSP and PC from NP bootrom*/
//#define BFLB_BOOT2_CPU1_APP_PC_ADDR             (BL60X_SRAM_END-4)
//#define BFLB_BOOT2_CPU1_APP_MSP_ADDR            (BL60X_SRAM_END-8)
//#define BFLB_BOOT2_CPU1_DBG_INFO_ADDR           (BL60X_SRAM_END-12)
#define BFLB_BOOT2_CPU1_APP_PC_ADDR             (0)
#define BFLB_BOOT2_CPU1_APP_MSP_ADDR            (0)
#define BFLB_BOOT2_CPU1_DBG_INFO_ADDR           (0)
#define MFG_START_REQUEST_OFFSET                ((4+184)*1024)
#define BLSP_BOOT2_XIP_BASE                     BL602_FLASH_XIP_BASE
#define ARCH_Delay_MS                           BL602_Delay_MS

/*@} end of group BLSP_PORT_Public_Constants */

/** @defgroup  BLSP_PORT_Public_Macros
 *  @{
 */

/*@} end of group BLSP_PORT_Public_Macros */

/** @defgroup  BLSP_PORT_Public_Functions
 *  @{
 */
void BLSP_Boot2_Init_Timer(void);
void BLSP_Boot2_Disable_Other_Cache(void);
void BLSP_Boot2_Flush_XIP_Cache(void);
void BLSP_Boot2_Reset_Sec_Eng(void);
void BLSP_Boot2_Show_Timer(void);
void BLSP_Boot2_Reset_Sec_Eng(void);
void BLSP_Boot2_Init_Sec_Eng_PKA(void);
uint32_t BLSP_Boot2_Get_CPU_Count(void);
uint8_t BLSP_Read_Power_Save_Mode(void);
void BLSP_Boot2_Pass_Parameter(void *data,uint32_t len);
uint32_t BLSP_Boot2_Get_XIP_Offset();
uint8_t* BLSP_Get_User_Specified_Fw(void);
void BLSP_Clr_User_Specified_Fw(void);
void BLSP_Boot2_Releae_Other_CPU(void);
int32_t BLSP_Is_MSP_Valid(uint32_t mspVal);
int32_t BLSP_Is_PC_Valid(uint32_t pcVal);
void ATTR_TCM_SECTION BLSP_Sboot_Finish(void);;
void BLSP_Fix_Invalid_MSP_PC(void);
uint8_t BLSP_Boot2_Get_TX_GPIO(void);
uint8_t BLSP_Boot2_Get_Feature_Flag(void);
uint8_t BLSP_Boot2_Get_Log_Disable_Flag(void);
uint8_t BLSP_Boot2_8M_Support_Flag(void);
uint8_t BLSP_Boot2_Dump_Critical_Flag(void);
uint32_t BLSP_Boot2_Get_Baudrate(void);

/*@} end of group BLSP_PORT_Public_Functions */

/*@} end of group BLSP_PORT */

/*@} end of group BL606_BLSP_Boot2 */

#endif /* __BLSP_PORT_H__ */
