/**
 * *****************************************************************************
 * @file lhal_bl702_spi.c
 * @version 0.1
 * @date 2020-07-14
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

#include "hal_spi.h"
#include "hal_pin.h"
#include "lhal_bl702_spi.h"
#include "bl702_spi.h"
#include "bflb_platform.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bl702_hbn.h"
#include "bl702_dma.h"

uint_fast8_t         SPIBLXXX_close(SPI_Handle handle);
int_fast16_t         SPIBLXXX_control(SPI_Handle handle, uint_fast16_t cmd,void *arg);
void                 SPIBLXXX_init(SPI_Handle handle);
SPI_Handle           SPIBLXXX_open(SPI_Handle handle, SPI_Params *params);
uint_fast8_t         SPIBLXXX_write(SPI_Handle handle, SPI_Data *buff,uint32_t length);
uint_fast8_t         SPIBLXXX_read(SPI_Handle handle, SPI_Data *buff,uint32_t length);
uint_fast8_t         SPIBLXXX_readWrite(SPI_Handle handle, SPI_Data *sendBuff,SPI_Data *recvBuff,uint32_t length);
uint_fast32_t        SPIBLXXX_getDMATxAddrFxn(SPI_Handle handle);
uint_fast8_t         SPIBLXXX_getDmaTxReqFxn(SPI_Handle handle);
uint_fast32_t        SPIBLXXX_getDMARxAddrFxn(SPI_Handle handle);
uint_fast8_t         SPIBLXXX_getDmaRxReqFxn(SPI_Handle handle);

static bool          SPIBLXXX_initHw(SPI_Handle handle);
static bool          SPIBLXXX_initIO(SPI_Handle handle);

const SPI_FxnTable SPIBLXXX_fxnTable = {
    SPIBLXXX_close,
    SPIBLXXX_control,
    SPIBLXXX_init,
    SPIBLXXX_open,
    SPIBLXXX_write,
    SPIBLXXX_read,
    SPIBLXXX_readWrite,
    SPIBLXXX_getDMATxAddrFxn,
    SPIBLXXX_getDmaTxReqFxn,
    SPIBLXXX_getDMARxAddrFxn,
    SPIBLXXX_getDmaRxReqFxn,

};

uint_fast8_t         SPIBLXXX_close(SPI_Handle handle){

    SPIBLXXX_Object               *object;
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;

    object = handle->object;
    hwAttrs = handle->hwAttrs;
    
    SPI_Disable(hwAttrs->spi_index,0);

    object -> opened = false;

    return 0;
}
int_fast16_t         SPIBLXXX_control(SPI_Handle handle, uint_fast16_t cmd,void *arg){
    return 0;
}
void                 SPIBLXXX_init(SPI_Handle handle){
    SPIBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;
}

SPI_Handle           SPIBLXXX_open(SPI_Handle handle, SPI_Params *params){
    SPIBLXXX_Object               *object;

    object = handle->object;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("SPI:(%p) already in use.", handle);
        return (NULL);
    }    

    object->spi_block_timeout = params->spi_block_timeout;
    object->spi_clock_div = params->spi_clock_div;
    object->spi_cpha = params->spi_cpha;
    object->spi_cpol = params->spi_cpol;
    object->spi_data_first = params->spi_data_first;
    object->spi_data_size = params->spi_data_size;
    object->spi_work_mode = params->spi_work_mode;

    if(SPIBLXXX_initIO(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    if(SPIBLXXX_initHw(handle) != SUCCESS){
        object->opened = false;
        return (NULL);        
    }  

    object->opened = true;
    
    return (handle);

}
uint_fast32_t SPIBLXXX_getDMATxAddrFxn(SPI_Handle handle){
    return SPI_BASE+SPI_FIFO_WDATA_OFFSET;
}

uint_fast8_t  SPIBLXXX_getDmaTxReqFxn(SPI_Handle handle){
    return DMA_REQ_SPI_TX;    
}

uint_fast32_t SPIBLXXX_getDMARxAddrFxn(SPI_Handle handle){
    return SPI_BASE+SPI_FIFO_RDATA_OFFSET;
}

uint_fast8_t  SPIBLXXX_getDmaRxReqFxn(SPI_Handle handle){
    return DMA_REQ_SPI_RX;    
}

static bool  SPIBLXXX_initHw(SPI_Handle handle){

    SPI_CFG_Type spi_cfg={
        .deglitchEnable = DISABLE,
        .continuousEnable = DISABLE,
        .byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST,
        .bitSequence = SPI_BIT_INVERSE_MSB_FIRST,
        .frameSize = SPI_FRAME_SIZE_8,
    };

    SPI_ClockCfg_Type clockCfg ={
        1,                                                       /* Length of start condition */
        1,                                                       /* Length of stop condition */
        1,                                                       /* Length of data phase 0,affecting clock */
        1,                                                       /* Length of data phase 1,affecting clock */
        1      
    };

    SPI_FifoCfg_Type fifoCfg = {
        1,                                                       /* SPI tx FIFO threshold */
        1,                                                       /* SPI rx FIFO threshold */
        DISABLE,                                                  /* Enable or disable tx dma req/ack interface */
        DISABLE                                                   /* Enable or disable rx dma req/ack interface */
};


    SPIBLXXX_Object               *object;
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;

    object  = handle->object;
    hwAttrs  = handle->hwAttrs;

    /*default spi clock is bclk 40 /10 M for bl702*/
    GLB_Set_SPI_CLK(ENABLE,object->spi_clock_div);
    SPI_ClockConfig(hwAttrs->spi_index,&clockCfg);

    spi_cfg.clkPhaseInv = object->spi_cpha;
    spi_cfg.clkPolarity = object->spi_cpol;

    spi_cfg.frameSize = object->spi_data_size;
    spi_cfg.byteSequence = object->spi_data_first;
    spi_cfg.bitSequence = object->spi_data_first;


    SPI_Init(hwAttrs->spi_index,&spi_cfg);

    /*set spi mode*/
    if(object->spi_work_mode == SPI_SLAVE_MODE){
        /* Not support spi slave mode in v1.0 version*/
        /* Todo Support */
        return ERROR;
    }else{
        GLB_Set_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER); 
        SPI_Enable(hwAttrs->spi_index,SPI_WORK_MODE_MASTER);
    }

    
    if(object->spi_work_mode == SPI_MASTER_DMA_MODE){
        fifoCfg.rxFifoDmaEnable = ENABLE;
        fifoCfg.txFifoDmaEnable = ENABLE;
        fifoCfg.rxFifoThreshold = hwAttrs->spi_rx_dma_thr;
        fifoCfg.txFifoThreshold = hwAttrs->spi_tx_dma_thr;
    }

    SPI_FifoConfig(hwAttrs->spi_index,&fifoCfg);

    return SUCCESS;

}
static bool  SPIBLXXX_initIO(SPI_Handle handle){
    /* Locals */
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    if(hwAttrs->spi_miso_pin == PIN_UNASSIGNED ||
       hwAttrs->spi_mosi_pin == PIN_UNASSIGNED ||
       hwAttrs->spi_sclk_pin == PIN_UNASSIGNED ){
           return ERROR;
           /* SCLK MISO MOSI can not be unassigned */
       }


    //TODO support more spi device
    if(hwAttrs->spi_cs_pin == PIN_UNASSIGNED){
        GLB_GPIO_Func_Init(GPIO_FUN_SPI0,(uint8_t *)hwAttrs,3);
    }else{
        GLB_GPIO_Func_Init(GPIO_FUN_SPI0,(uint8_t *)hwAttrs,4);
    }

    return SUCCESS;    
}

uint_fast8_t         SPIBLXXX_write(SPI_Handle handle, SPI_Data *buff,uint32_t length){
    /* Locals */
    SPIBLXXX_Object               *object;
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;
    uint8_t ret = 0;

    object  = handle->object;
    hwAttrs  = handle->hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    if(sizeof(SPI_Data) == 1){
        ret = SPI_Send_8bits(hwAttrs->spi_index, (uint8_t *)  buff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 2){
        ret = SPI_Send_16bits(hwAttrs->spi_index,(uint16_t * )buff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 3){
        ret = SPI_Send_24bits(hwAttrs->spi_index,(uint32_t * )buff,length,object->spi_block_timeout);
    }else{
        ret = SPI_Send_32bits(hwAttrs->spi_index,(uint32_t * )buff,length,object->spi_block_timeout);
    }
    return ret;
}
uint_fast8_t         SPIBLXXX_read(SPI_Handle handle, SPI_Data *buff,uint32_t length){
    /* Locals */
    SPIBLXXX_Object               *object;
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;
    uint8_t ret = 0;

    object  = handle->object;
    hwAttrs  = handle->hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    if(sizeof(SPI_Data) == 1){
       ret = SPI_Recv_8bits(hwAttrs->spi_index, (uint8_t * )buff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 2){
       ret = SPI_Recv_16bits(hwAttrs->spi_index,(uint16_t *)buff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 3){
       ret = SPI_Recv_24bits(hwAttrs->spi_index,(uint32_t *)buff,length,object->spi_block_timeout);
    }else{
       ret = SPI_Recv_32bits(hwAttrs->spi_index,(uint32_t *)buff,length,object->spi_block_timeout);
    }

    return ret;
}
uint_fast8_t         SPIBLXXX_readWrite(SPI_Handle handle, SPI_Data *sendBuff,SPI_Data *recvBuff,uint32_t length){
    /* Locals */
    SPIBLXXX_Object               *object;
    SPIBLXXX_HWAttrsV2 const     *hwAttrs;
    uint8_t ret = 0;

    object  = handle->object;
    hwAttrs  = handle->hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    if(sizeof(SPI_Data) == 1){
       ret = SPI_SendRecv_8bits(hwAttrs->spi_index,(uint8_t * )  sendBuff,  (uint8_t * )recvBuff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 2){
       ret = SPI_SendRecv_16bits(hwAttrs->spi_index,(uint16_t * )sendBuff,(uint16_t * )recvBuff,length,object->spi_block_timeout);
    }else if(sizeof(SPI_Data) == 3){
       ret = SPI_SendRecv_24bits(hwAttrs->spi_index,(uint32_t * )sendBuff,(uint32_t * )recvBuff,length,object->spi_block_timeout);
    }else{
       ret = SPI_SendRecv_32bits(hwAttrs->spi_index,(uint32_t * )sendBuff,(uint32_t * )recvBuff,length,object->spi_block_timeout);
    }
    
    return ret;
}
