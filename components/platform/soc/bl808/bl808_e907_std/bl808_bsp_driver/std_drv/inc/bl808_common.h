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
#ifndef __BL808_COMMON_H__
#define __BL808_COMMON_H__

#include "bl808.h"
#include "misc.h"

#ifndef __set_MSP
#define __set_MSP(msp) __ASM volatile("add sp, x0, %0" ::"r"(msp))
#endif

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  COMMON
 *  @{
 */

/** @defgroup  COMMON_Public_Types
 *  @{
 */

/*@} end of group COMMON_Public_Types */

/** @defgroup  COMMON_Public_Constants
 *  @{
 */

/** @defgroup DRIVER_INT_PERIPH
 *  @{
 */
#define IS_INT_PERIPH(INT_PERIPH) ((INT_PERIPH) < IRQn_LAST)

/*@} end of group DRIVER_INT_PERIPH */

/** @defgroup DRIVER_INT_MASK
 *  @{
 */
#define IS_BL_MASK_TYPE(type) (((type) == MASK) || ((type) == UNMASK))

/*@} end of group COMMON_Public_Constants */

/** @defgroup DRIVER_Public_FunctionDeclaration
 *  @brief DRIVER functions declaration
 *  @{
 */

void ASM_Delay_Us(uint32_t core, uint32_t cnt, uint32_t loopT);
void arch_delay_us(uint32_t cnt);
void arch_delay_ms(uint32_t cnt);

void C906_All_Int_Enable(void);
void C906_All_Int_Disable(void);
/*@} end of group DRIVER_COMMON  */

#endif /* __BL808_COMMON_H__ */
