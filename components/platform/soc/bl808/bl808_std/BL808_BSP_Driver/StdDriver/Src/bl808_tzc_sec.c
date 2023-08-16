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

#include "string.h"
#include "bl808_tzc_sec.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TZC_ENG
 *  @{
 */

/** @defgroup  TZC_ENG_Private_Macros
 *  @{
 */

/*@} end of group TZC_ENG_Private_Macros */

/** @defgroup  TZC_ENG_Private_Types
 *  @{
 */

/*@} end of group TZC_ENG_Private_Types */

/** @defgroup  TZC_ENG_Private_Variables
 *  @{
 */

/*@} end of group TZC_ENG_Private_Variables */

/** @defgroup  TZC_ENG_Global_Variables
 *  @{
 */

/*@} end of group TZC_ENG_Global_Variables */

/** @defgroup  TZC_ENG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group TZC_ENG_Private_Fun_Declaration */

/** @defgroup  TZC_ENG_Private_Functions
 *  @{
 */

/*@} end of group TZC_ENG_Private_Functions */

/** @defgroup  TZC_ENG_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  None
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Tzc_Sec_Set_Sboot_Done(void)
{
    uint32_t tmpVal;
    /* Set Sboot done */
    tmpVal = BL_RD_REG(TZ1_BASE,TZC_SEC_TZC_ROM_TZSRG_CTRL);
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,TZC_SEC_TZC_SBOOT_DONE,0xf);
    BL_WR_REG(TZ1_BASE,TZC_SEC_TZC_ROM_TZSRG_CTRL,tmpVal);
}

void Tzc_Sec_Set_CPU_Group(uint8_t cpu,uint8_t group)
{
  uint32_t tmpVal;
  uint32_t tmpVal2;

  /* Set Sboot down */
  tmpVal = BL_RD_REG(TZ1_BASE,TZC_SEC_TZC_BMX_TZMID);
  tmpVal2 = BL_RD_REG(TZ1_BASE,TZC_SEC_TZC_BMX_TZMID_LOCK);

  if(cpu==GLB_CORE_ID_M0){
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,TZC_SEC_TZC_CPU_TZMID,group);
    tmpVal2=BL_SET_REG_BITS_VAL(tmpVal2,TZC_SEC_TZC_CPU_TZMID_LOCK,1);
  }else if(cpu==GLB_CORE_ID_D0){
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,TZC_SEC_TZC_MM_TZMID,group);
    tmpVal2=BL_SET_REG_BITS_VAL(tmpVal2,TZC_SEC_TZC_MM_TZMID_LOCK,1);
  }else if(cpu==GLB_CORE_ID_LP){
    tmpVal=BL_SET_REG_BITS_VAL(tmpVal,TZC_SEC_TZC_PICO_TZMID,group);
    tmpVal2=BL_SET_REG_BITS_VAL(tmpVal2,TZC_SEC_TZC_PICO_TZMID_LOCK,1);
  }
  BL_WR_REG(TZ1_BASE,TZC_SEC_TZC_BMX_TZMID,tmpVal);
  BL_WR_REG(TZ1_BASE,TZC_SEC_TZC_BMX_TZMID_LOCK,tmpVal2);
    
}

/*@} end of group TZC_ENG_Public_Functions */

/*@} end of group TZC_ENG */

/*@} end of group BL808_Peripheral_Driver */
