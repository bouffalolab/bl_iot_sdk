/**
 * *****************************************************************************
 * @file lhal_bl702_wtd.c
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

#include <stdint.h>
#include <stdlib.h>
#include "hal_wtd.h"
#include "lhal_bl702_wtd.h"
#include "bflb_platform.h"
#include "bl702_hbn.h"
#include "bl702_timer.h"

/* Function prototypes */
void WatchdogBLXXX_clear(Watchdog_Handle handle);
void WatchdogBLXXX_close(Watchdog_Handle handle);
int  WatchdogBLXXX_control(Watchdog_Handle handle, unsigned int cmd, void *arg);
void WatchdogBLXXX_init(Watchdog_Handle handle);
Watchdog_Handle WatchdogBLXXX_open(Watchdog_Handle handle, Watchdog_Params *params);
void WatchdogBLXXX_setReload(Watchdog_Handle handle, uint32_t value);
uint32_t WatchdogBLXXX_convertMsToTicks(Watchdog_Handle handle, uint32_t milliseconds);
static bool WatchdogBLXXX_initHw(Watchdog_Handle handle);
static Watchdog_Handle watchdog_handle_temp;

/* Watchdog function table for BLXXXX implementation */
const Watchdog_FxnTable WatchdogBLXXX_fxnTable = {
    WatchdogBLXXX_clear,
    WatchdogBLXXX_close,
    WatchdogBLXXX_control,
    WatchdogBLXXX_init,
    WatchdogBLXXX_open,
    WatchdogBLXXX_setReload,
    WatchdogBLXXX_convertMsToTicks,
};

/* Default Watchdog params */
extern const Watchdog_Params Watchdog_defaultParams;

/*
 *  ======== WatchdogBLXXXX_clear ========
 */
void WatchdogBLXXX_clear(Watchdog_Handle handle)
{
    WDT_ResetCounterValue();
}

/*
 *  ======== WatchdogBLXXXX_close ========
 */
void WatchdogBLXXX_close(Watchdog_Handle handle)
{
    WDT_Disable();
}

/*
 *  ======== WatchdogBLXXXX_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int WatchdogBLXXX_control(Watchdog_Handle handle, unsigned int cmd, void *arg)
{
    int ret;

    /* Initialize return value*/
    ret = Watchdog_STATUS_UNDEFINEDCMD;

    switch(cmd)
    {
        case Watchdog_CMD_GET_WTD_COUNT:
            *((uint32_t *)arg) = WDT_GetCounterValue();
            ret = Watchdog_STATUS_SUCCESS;
        break;
        default:
            /* This command is not defined */
            ret = Watchdog_STATUS_UNDEFINEDCMD;
        break;
    }
    /* Return */
    return (ret);
}

/*
 *  ======== Watchdog_init ========
 */
void WatchdogBLXXX_init(Watchdog_Handle handle)
{
    WatchdogBLXXX_Object               *object;

    /* Get the pointer to the object */

    object = handle->object;
    object->opened = false;
}

/*
 *  ======== WatchdogBLXXXX_open ========
 */
Watchdog_Handle WatchdogBLXXX_open(Watchdog_Handle handle, Watchdog_Params *params)
{
    WatchdogBLXXX_Object               *object;
    WatchdogBLXXX_HWAttrs const        *hwAttrs;

    object  = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("WATCHDOG:(%p) already in use.", handle);
        return (NULL);
    }    

    object->resetMode = params->resetMode;
    object->reloadValue = hwAttrs->reloadValue;
    object->debugStallMode = params->debugStallMode;
    object->callbackFxn = params->callbackFxn;
    object->clockDiv = params->clockDiv;

    if(WatchdogBLXXX_initHw(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    } 

    object->opened = true;
    
    return (handle);

}

/*
 *  ======== WatchdogBLXXXX_setReload ========
 */
void WatchdogBLXXX_setReload(Watchdog_Handle handle, uint32_t value)
{
    WDT_SetCompValue(value);
}

void watchdog_callback_fxn(void){
    
    WatchdogBLXXX_Object               *object;

    if(watchdog_handle_temp != NULL){
        object = watchdog_handle_temp->object;
        object ->callbackFxn(watchdog_handle_temp);
    }
}
/*
 *  ======== WatchdogBLXXXX_hwInit ========
 *  This functions initializes the Watchdog hardware module.
 *
 *  @pre    Function assumes that the Watchdog handle is pointing to a hardware
 *          module which has already been opened.
 */
static bool WatchdogBLXXX_initHw(Watchdog_Handle handle) {
    WatchdogBLXXX_Object               *object;

    object = handle->object;

    WDT_Disable();
    
    /* default using 32k clock */
    /* user can config clcok src in this file */

    WDT_Set_Clock(TIMER_CLKSRC_32K,object->clockDiv);
    
    WDT_SetCompValue(object->reloadValue);

    /* now logic is if mask is reset mode , is unmask is interrupt mode
     */
    if(object->resetMode == Watchdog_RESET_OFF){
        WDT_IntMask(WDT_INT, UNMASK);
        WDT_Int_Callback_Install(WDT_INT,&watchdog_callback_fxn);
    }else{
        WDT_IntMask(WDT_INT, MASK);
    }
    watchdog_handle_temp = handle;

    NVIC_EnableIRQ(TIMER_WDT_IRQn);

    WDT_ResetCounterValue();
    
    /* Enable watch dog */
    WDT_Enable();

    return SUCCESS;
}

uint32_t WatchdogBLXXX_convertMsToTicks(Watchdog_Handle handle, uint32_t milliseconds){
    //default wtd clock is 32k

    if(milliseconds > 2048){
        return 0;
    }

    return (65535 - (32 * milliseconds));
}