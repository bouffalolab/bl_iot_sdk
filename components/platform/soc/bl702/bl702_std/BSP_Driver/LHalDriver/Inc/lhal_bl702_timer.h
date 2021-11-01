/**
 * *****************************************************************************
 * @file lhal_bl702_timer.h
 * @version 0.1
 * @date 2020-07-29
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

#include <stdint.h>
#include <stdbool.h>
#include "hal_timer.h"
#include "bl702_timer.h"


#define TIMERBLXXX_MAX_TIMER_NUM 2


typedef struct {
    uint32_t                deviceIndex;    /*!< Timer index */
    TIMER_Width             width;          /*!< Timer configuration (32/16-bit)  */

} TIMERBLXXX_HWAttrsV2;


typedef struct {
    /* TIMER control variables */
    bool                opened;         /*!< Has the obj been opened */

    TIMER_Mode              mode;                   /*!< Timer mode */
    TIMER_SetMatchTiming    matchTiming;            /*!< Set new match values on next timeout or next cycle */
    TIMER_Direction         direction;              /*!< Count up or down */
    TIMER_DebugMode         debugStallMode;         /*!< Timer debug stall mode */
    uint32_t                preloadValue;           /*!< Preload Value */
    uint32_t                matchValue;             /*!< Match Value */
    uint32_t                clockDiv;               /*!< Clock devider */
    bool                    enableTimerCallback;    /*< enable/disable timer */
    Timer_Callback          timerCallback;          /*!< Timer up callback */
    
} TIMERBLXXX_Object, *TIMERBLXXX_Handle;