/**
 * *****************************************************************************
 * @file lhal_bl702_timer.c
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
#include "hal_timer.h"
#include "bflb_platform.h"
#include "lhal_bl702_timer.h"
#include "bl702_timer.h"

void         TIMERBLXXX_close(Timer_Handle handle);
int_fast16_t TIMERBLXXX_control(Timer_Handle handle, uint_fast16_t cmd,void *arg);
void         TIMERBLXXX_init(Timer_Handle handle);
Timer_Handle TIMERBLXXX_open(Timer_Handle handle, Timer_Params *params);
bool  TIMERBLXXX_start(Timer_Handle handle);
bool  TIMERBLXXX_stop(Timer_Handle handle);
bool  TIMERBLXXX_clear(Timer_Handle handle);
uint32_t  TIMERBLXXX_getCount(Timer_Handle handle);

static bool  TIMERBLXXX_initHw(Timer_Handle handle);
static void timer0_callback(void);
static void timer1_callback(void);

static Timer_Handle timer_handle_temp[TIMERBLXXX_MAX_TIMER_NUM];
static intCallback_Type * timer_func_list[]={
    timer0_callback,
    timer1_callback,
};

/* Timer function table for TimerBLXXX implementation */
const Timer_FxnTable TimerBLXXX_fxnTable = {
    TIMERBLXXX_close,
    TIMERBLXXX_control,
    TIMERBLXXX_init,
    TIMERBLXXX_open,
    TIMERBLXXX_start,
    TIMERBLXXX_stop,
    TIMERBLXXX_clear,
    TIMERBLXXX_getCount,
};


void         TIMERBLXXX_close(Timer_Handle handle){
    TIMERBLXXX_Object               *object;
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;

    hwAttrs = handle->hwAttrs;
    object = handle->object;

    TIMER_IntMask(hwAttrs->deviceIndex,TIMER_INT_COMP_0, MASK);
    TIMER_Disable(hwAttrs->deviceIndex);

    /* Mark the module as available */
    object->opened = false;
}

int_fast16_t TIMERBLXXX_control(Timer_Handle handle, uint_fast16_t cmd,void *arg){
    return 0;
}
void         TIMERBLXXX_init(Timer_Handle handle){

}
Timer_Handle TIMERBLXXX_open(Timer_Handle handle, Timer_Params *params){
    TIMERBLXXX_Object               *object;
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;

    object  = handle->object;
    hwAttrs = handle->hwAttrs;    

    if (object->opened == true) {
        MSG("TIMER:(%p) already in use.", handle);
        return (NULL);
    }    

    if(hwAttrs->width == TIMER_WIDTH_16BIT){
        MSG("Do not support 16 BIT counter\r\n");
        return (NULL);
    }

    if(params->direction == TIMER_DIRECTION_DOWN){
        MSG("Do not support down direction\r\n");
        return (NULL);        
    }

    if(params->mode == TIMER_MODE_CAP_EDGE_COUNT || params->mode == TIMER_MODE_CAP_EDGE_TIME){
        MSG("Do not support capture mode\r\n");
        return (NULL);             
    }

    object->debugStallMode = params->debugStallMode;
    object->direction = params->direction;
    object->matchTiming = params->matchTiming;
    object->mode = params->mode;
    object->preloadValue = params->preloadValue;
    object->matchValue = params->matchValue;
    object->clockDiv = params->clockDiv;
    object->timerCallback = params->timerCallback;
    object->enableTimerCallback = params->enableTimerCallback;

    if(TIMERBLXXX_initHw(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    object->opened = true;
    
    return (handle);

}

static void timer0_callback(void){
    TIMERBLXXX_Object               *object;

    if(timer_handle_temp != NULL){
        object = timer_handle_temp[0]->object;

        if(object->mode == TIMER_MODE_ONESHOT){
            TIMER_IntMask(0,TIMER_INT_COMP_0, MASK);
            TIMER_Disable(0);        
        }

        if(object->timerCallback != NULL){
            object->timerCallback(timer_handle_temp[0]);
        }
    }
}

static void timer1_callback(void){
    TIMERBLXXX_Object               *object;
    if(timer_handle_temp != NULL){
        object = timer_handle_temp[1]->object;

        if(object->mode == TIMER_MODE_ONESHOT){
            TIMER_IntMask(1,TIMER_INT_COMP_0, MASK);
            TIMER_Disable(1);        
        }

        if(object->timerCallback != NULL){
            object->timerCallback(timer_handle_temp[1]);
        }
    }
}

static bool  TIMERBLXXX_initHw(Timer_Handle handle){
    TIMERBLXXX_Object               *object;
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;
    TIMER_CFG_Type timerCfg = {
                                    TIMER_CH0,                           /* timer channel 0 */
                                    TIMER_CLKSRC_FCLK,                   /* timer clock source:bus clock */
                                    TIMER_PRELOAD_TRIG_COMP0,            /* reaload on comaparator 0  */
                                    TIMER_COUNT_PRELOAD,                 /* preload when match occur */
                                    0,                                   /* Timer clock divison value */
                                    230000,                              /* match value 0  */
                                    230000,                              /* match value 1 */
                                    230000,                              /* match value 2 */
                                    200000,                              /* preload value */
                            };  
                            
    object  = handle->object;
    hwAttrs = handle->hwAttrs;


    if(object->clockDiv > 255){
        MSG("BL702 max clock divider is 255\r\n");
        return ERROR;
    }

    if(hwAttrs->deviceIndex > TIMERBLXXX_MAX_TIMER_NUM){
        MSG("BL702 only support two timer\r\n");
        return ERROR;        
    }

    /*default clock is FCLK*/
    timerCfg.clkSrc = TIMER_CLKSRC_32K;
    timerCfg.clockDivision = object->clockDiv;
    timerCfg.matchVal0 = object->matchValue;
    timerCfg.preLoadVal = object->preloadValue;
    timerCfg.timerCh = hwAttrs->deviceIndex;

    /* Disable all interrupt */
    TIMER_IntMask(hwAttrs->deviceIndex,TIMER_INT_ALL, MASK);

    /* Disable timer before config */
    TIMER_Disable(hwAttrs->deviceIndex);

    /* Timer init with configuration */
    TIMER_Init(&timerCfg);

    /* Clear interrupt status*/
    TIMER_ClearIntStatus(hwAttrs->deviceIndex,TIMER_COMP_ID_0);

    /* Disable timer match interrupt */
    TIMER_IntMask(hwAttrs->deviceIndex,TIMER_INT_COMP_0, MASK);

    /* Install the interrupt callback function */
    Timer_Int_Callback_Install(hwAttrs->deviceIndex, TIMER_INT_COMP_0, timer_func_list[hwAttrs->deviceIndex]);

    NVIC_ClearPendingIRQ((IRQn_Type)(hwAttrs->deviceIndex+TIMER_CH0_IRQn));
    NVIC_EnableIRQ((IRQn_Type)(hwAttrs->deviceIndex+TIMER_CH0_IRQn));

    timer_handle_temp[hwAttrs->deviceIndex] = handle;
    /* Enable timer */


    return SUCCESS;
}

bool  TIMERBLXXX_start(Timer_Handle handle){
    TIMERBLXXX_Object               *object;
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;

    hwAttrs = handle->hwAttrs;
    object  = handle->object;

    if(object->enableTimerCallback){
        TIMER_IntMask(hwAttrs->deviceIndex,TIMER_INT_COMP_0, UNMASK);
    }

    TIMER_Enable(hwAttrs->deviceIndex);

    return SUCCESS;
}

bool  TIMERBLXXX_stop(Timer_Handle handle){
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;
    hwAttrs = handle->hwAttrs;


    TIMER_IntMask(hwAttrs->deviceIndex,TIMER_INT_COMP_0, MASK);
    TIMER_Disable(hwAttrs->deviceIndex);

    return SUCCESS;
}

bool  TIMERBLXXX_clear(Timer_Handle handle){
    //TODO Need hardware to support
    return 0;
}

uint32_t  TIMERBLXXX_getCount(Timer_Handle handle){
    TIMERBLXXX_HWAttrsV2 const      *hwAttrs;
    hwAttrs = handle->hwAttrs;    

    return TIMER_GetCounterValue(hwAttrs->deviceIndex);
}