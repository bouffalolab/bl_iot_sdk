/**
 * *****************************************************************************
 * @file lhal_bl702_wtd.h
 * @version 0.1
 * @date 2020-07-28
 * @brief 
 * *****************************************************************************
 * @attention
 * 
 *  <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
 * 
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *    3. Neither the name of Bouffalo Lab nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * *****************************************************************************
 */
#ifndef __LHAL_BL702_WTD__
#define __LHAL_BL702_WTD__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "hal_wtd.h"
/*!
 *  @brief  Watchdog hardware attributes for BLXXXX
 */
typedef struct WatchdogBLXXX_HWAttrs {
    uint16_t baseAddr;            /*!< Base adddress for Watchdog */
    uint16_t reloadValue;         /*!< WDT interrupt number */
} WatchdogBLXXX_HWAttrs;

/*!
 *  @brief      Watchdog Object for BLXXXX
 *
 *  Not to be accessed by the user.
 */
typedef struct WatchdogBLXXX_Object {
    bool                opened;             /*!< Flag for open/close status */
    
    uint16_t            clockDiv;            /*!< Clock Div */
                                                 
    unsigned long       reloadValue;        /*!< Reload value for Watchdog */
    Watchdog_Callback   callbackFxn;        /*!< Pointer to callback. Not supported
                                                 on all targets. */
    Watchdog_ResetMode  resetMode;          /*!< Mode to enable resets.
                                                  Not supported on all targets. */
    Watchdog_DebugMode  debugStallMode;     /*!< Mode to stall WDT at breakpoints.*/


} WatchdogBLXXX_Object;


#ifdef __cplusplus
}
#endif

#endif
