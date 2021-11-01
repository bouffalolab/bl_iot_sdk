/**
 * *****************************************************************************
 * @file lhal_bl702_dma.c
 * @version 0.1
 * @date 2020-06-15
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

#include "hal_dma.h"
#include "lhal_bl702_dma.h"
#include "bl702_dma.h"
#include "bl702_glb.h"
#include "bflb_platform.h"

uint8_t      DMABLXXX_close(DMA_Handle handle);
int_fast16_t DMABLXXX_control(DMA_Handle handle, uint_fast16_t cmd,void *arg);
void         DMABLXXX_init(DMA_Handle handle);
DMA_Handle  DMABLXXX_open(DMA_Handle handle);
void         DMABLXXX_Start(DMA_Handle handle);
void         DMABLXXX_Stop(DMA_Handle handle);
int_fast16_t DMABLXXX_Append(DMA_Handle handle,DMA_Trans_Task * trans_task);
int_fast16_t DMABLXXX_Clear(DMA_Handle handle);

bool DMA_CH_STATUS[BL702_MAX_DMA_NUM];

/* DMA function table for DMABLXXX implementation */
const DMA_FxnTable DMABLXXX_fxnTable = {
    DMABLXXX_close,
    DMABLXXX_control,
    DMABLXXX_init,
    DMABLXXX_open,
    DMABLXXX_Start,
    DMABLXXX_Stop,
    DMABLXXX_Append,
    DMABLXXX_Clear
};


uint8_t DMABLXXX_close(DMA_Handle handle){
    DMABLXXX_Object            *object;   
    /* Get the pointer to the object and hwAttrs */
    object = handle->object;

    DMA_Channel_Disable(object->dma_ch % BL702_MAX_DMA_NUM);
    DMA_CH_STATUS[object->dma_ch % BL702_MAX_DMA_NUM] = false;
    DMA_IntMask(object->dma_ch % BL702_MAX_DMA_NUM, DMA_INT_ALL, MASK);

    return (object->dma_ch);
}


int_fast16_t DMABLXXX_control(DMA_Handle handle, uint_fast16_t cmd,void *arg){
    DMABLXXX_Object            *object;
    int ret;

    /* Get the pointer to the object and hwAttrs */
    object = handle->object;

    /* Initialize return value*/
    ret = DMA_STATUS_UNDEFINEDCMD;

    switch(cmd)
    {
        case DMA_CMD_GET_DMA_STATUS:
            ret = DMA_Channel_Is_Busy(object->dma_ch);
        break;
        default : break;
    }

    /* Return */
    return (ret);
}



static uint8_t DMA_Get_Free_Ch_Num(void){
    uint8_t i=0;
    uint8_t rlt=0;

    for(i=0;i<BL702_MAX_DMA_NUM;i++){
        if(DMA_CH_STATUS[i]== false){
            rlt++;
        }
    }

    return rlt;
}

static uint8_t allocate_dma_channel(void){
    
    uint8_t i=0;

    if(DMA_Get_Free_Ch_Num()==0){
        return 0xff;
    }

    for(i=0;i<BL702_MAX_DMA_NUM;i++){
        if(DMA_CH_STATUS[i]== false){
            return i;
        }
    }

    /* cannont be run here*/
    return 0;
}
                                         
void DMABLXXX_init(DMA_Handle handle){
    DMABLXXX_Object           *object;
    uint8_t i=0;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;

    for(i=0;i<BL702_MAX_DMA_NUM;i++){
        DMA_CH_STATUS[i] = false;
    }
}

DMA_Handle DMABLXXX_open(DMA_Handle handle){
    DMABLXXX_Object               *object; 
    DMA_Chan_Type allocate_ch;
    
    object = handle->object;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("DMA:(%p) already in use.", handle);
        return (NULL);
    }

    if(DMA_Get_Free_Ch_Num() == 0){
        return(NULL);
        /* no free dma channel for allocting */
    }

    allocate_ch = allocate_dma_channel ();



    if(allocate_ch == 0xff){
        return(NULL);
        /*no free dma channel for allocting */
    }

    GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_DMA);

    DMA_CH_STATUS[allocate_ch] = true;

    object->dma_ch = allocate_ch;
    object->dma_trans_is_loop = false;
    object->dma_trans_task_index = 0;
    object->dma_trans_task_num=0;
    object->first_task_pointer = NULL;
    object->previous_task_pointer = NULL;

    object->opened = true;  
    
    return handle;  
}     

void DMABLXXX_Stop(DMA_Handle handle){
    DMABLXXX_Object               *object; 
    object = handle->object;

    DMA_Channel_Disable(object->dma_ch);    
}

void DMABLXXX_Start(DMA_Handle handle){
    DMABLXXX_Object               *object; 
    object = handle->object;

    DMA_Channel_Enable(object->dma_ch);  
}

int_fast16_t DMABLXXX_Append(DMA_Handle handle,DMA_Trans_Task * trans_task){

    DMABLXXX_Object               *object;   
    DMABLXXX_HWAttrsV2 const   *hwAttrs;  
    DMA_Channel_Cfg_Type chCfg;
    DMA_LLI_Cfg_Type lliCfg;

    union  dmaRegUnion_t
    {
        struct DMA_Control_Reg dmaCtrlRegVal;
        uint32_t dmaReg_u32;
    };

    union dmaRegUnion_t dmaRegUnion;

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    chCfg.srcBurstSize =trans_task->srcBurstSize;
    chCfg.dstBurstSize =trans_task->dstBurstSize;

    NVIC_DisableIRQ(DMA_ALL_IRQn);

    switch(trans_task->dma_dir_mode){
        case DMA_TRNS_M2M  : chCfg.srcAddrInc=1;chCfg.destAddrInc=1; break;                   
        case DMA_TRNS_M2P  : chCfg.srcAddrInc=1;chCfg.destAddrInc=0;break;                  
        case DMA_TRNS_P2M  : chCfg.srcAddrInc=0;chCfg.destAddrInc=1;break;               
        case DMA_TRNS_P2P  : chCfg.srcAddrInc=0;chCfg.destAddrInc=0;break;
        default: break;                       
    }


    if(object->dma_trans_task_num == 0){

        object->dma_trans_task_num ++;

        chCfg.srcDmaAddr = trans_task->src_addr;
        chCfg.destDmaAddr = trans_task->des_addr;
        chCfg.transfLength = trans_task->trans_len % 4096;
        chCfg.dir = trans_task->dma_dir_mode;
        chCfg.ch = object->dma_ch;
        chCfg.srcTransfWidth = trans_task->src_trans_width;
        chCfg.dstTransfWidth = trans_task->des_trans_width;
        chCfg.srcPeriph = trans_task->srcPeriph;
        chCfg.dstPeriph = trans_task->dstPeriph;

        DMA_Enable();
        DMA_Channel_Disable(chCfg.ch);


        if(trans_task->enable_tc_callback){
            DMA_Int_Callback_Install(chCfg.ch, DMA_INT_TCOMPLETED,trans_task->dma_tc_callback_func);
            DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_ALL, UNMASK);
        }

        dmaRegUnion.dmaCtrlRegVal.TransferSize=trans_task->trans_len % 4096;
        dmaRegUnion.dmaCtrlRegVal.SBSize=chCfg.srcBurstSize;
        dmaRegUnion.dmaCtrlRegVal.DBSize=chCfg.dstBurstSize;
        dmaRegUnion.dmaCtrlRegVal.SWidth=chCfg.srcTransfWidth;
        dmaRegUnion.dmaCtrlRegVal.DWidth=chCfg.dstTransfWidth;
        dmaRegUnion.dmaCtrlRegVal.SI=chCfg.srcAddrInc;
        dmaRegUnion.dmaCtrlRegVal.DI=chCfg.destAddrInc;
        dmaRegUnion.dmaCtrlRegVal.I=trans_task->enable_tc_callback;

        trans_task->dma_ctr_reg = dmaRegUnion.dmaReg_u32;

        object->first_task_pointer = trans_task;
        object->previous_task_pointer = trans_task;


        if(trans_task->enable_tc_callback){
            DMA_Int_Callback_Install(object->dma_ch, DMA_INT_TCOMPLETED,trans_task->dma_tc_callback_func);
            DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_TCOMPLETED, UNMASK);
        }else{
            DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_TCOMPLETED, MASK);
        }

        if(trans_task->dma_loop){
            object->dma_trans_is_loop = true;
            trans_task->next_task_addr = (uint32_t)object->first_task_pointer;

            lliCfg.dir = trans_task->dma_dir_mode;
            lliCfg.dstPeriph = trans_task->dstPeriph;
            lliCfg.srcPeriph = trans_task->srcPeriph;

            DMA_LLI_Init(object->dma_ch,&lliCfg);
            DMA_LLI_Update(object->dma_ch, (uint32_t)object->first_task_pointer);
        }else{
            DMA_Channel_Init(&chCfg);
            trans_task->next_task_addr = 0;
        }



    }else{
        
        if(object->previous_task_pointer->dma_loop){
            return 0xff;
            /* last task is loop , do not accept task any more */
        }

        object->dma_trans_task_num ++;

        object->previous_task_pointer->next_task_addr = (uint32_t)trans_task;

        lliCfg.dir = trans_task->dma_dir_mode;
        lliCfg.dstPeriph = trans_task->dstPeriph;
        lliCfg.srcPeriph = trans_task->srcPeriph;

        dmaRegUnion.dmaCtrlRegVal.TransferSize=trans_task->trans_len % 4096;
        dmaRegUnion.dmaCtrlRegVal.SBSize=chCfg.srcBurstSize;
        dmaRegUnion.dmaCtrlRegVal.DBSize=chCfg.dstBurstSize;
        dmaRegUnion.dmaCtrlRegVal.SWidth=chCfg.srcTransfWidth;
        dmaRegUnion.dmaCtrlRegVal.DWidth=chCfg.dstTransfWidth;
        dmaRegUnion.dmaCtrlRegVal.SI=chCfg.srcAddrInc;
        dmaRegUnion.dmaCtrlRegVal.DI=chCfg.destAddrInc;
        dmaRegUnion.dmaCtrlRegVal.I=trans_task->enable_tc_callback;

        trans_task->dma_ctr_reg = dmaRegUnion.dmaReg_u32;;

        object->previous_task_pointer = trans_task;

        if(trans_task->dma_loop){
            object->dma_trans_is_loop = true;
            trans_task->next_task_addr = (uint32_t)object->first_task_pointer;
        }else{
            trans_task->next_task_addr = 0;
        }

        if(trans_task->enable_tc_callback){
            DMA_Int_Callback_Install(object->dma_ch, DMA_INT_TCOMPLETED,trans_task->dma_tc_callback_func);
            DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_TCOMPLETED, UNMASK);
        }else{
            DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_TCOMPLETED, MASK);
        }

        DMA_LLI_Init(object->dma_ch,&lliCfg);
        DMA_LLI_Update(object->dma_ch, (uint32_t)object->first_task_pointer);
    }

    DMA_Int_Callback_Install(chCfg.ch, DMA_INT_ERR, hwAttrs->errorFxn);
    DMA_IntMask(chCfg.ch % BL702_MAX_DMA_NUM, DMA_INT_ERR, UNMASK);

    NVIC_EnableIRQ(DMA_ALL_IRQn);

    return 0;
}
int_fast16_t DMABLXXX_Clear(DMA_Handle handle){

    DMABLXXX_Object               *object;   

    object = handle->object;

    object->dma_trans_is_loop = false;
    object->dma_trans_task_index = 0;
    object->dma_trans_task_num=0;
    object->first_task_pointer = NULL;
    object->previous_task_pointer = NULL;

    DMA_Channel_Disable(object->dma_ch);
    
    return 0;
}
