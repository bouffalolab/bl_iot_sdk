/**
 * *****************************************************************************
 * @file lhal_bl702_uart.c
 * @version 0.1
 * @date 2020-06-03
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

/*
 * This file is Lhal driver , which provide glue between HAL and StdDriver.
 * HAL implement standard peripheral API , and This file will reailze HAL 
 * implement use stddriver.
 */

#include "hal_uart.h"
#include "lhal_bl702_uart.h"
#include "bl702_uart.h"
#include "bl702_hbn.h"
#include "bl702_gpio.h"
#include "bl702_glb.h"
#include "bl702.h"
#include "bl702_common.h"
#include "uart_reg.h"
#include "bl702_dma.h"


void         UARTBLXXX_close(UART_Handle handle);
int_fast16_t UARTBLXXX_control(UART_Handle handle, uint_fast16_t cmd,void *arg);
void         UARTBLXXX_init(UART_Handle handle);
UART_Handle  UARTBLXXX_open(UART_Handle handle, UART_Params *params);
int_fast32_t UARTBLXXX_read(UART_Handle handle, void *buffer, size_t size);
uint_fast16_t UARTBLXXX_rxFifoDump(UART_Handle handle,uint8_t * buf);
void         UARTBLXXX_readCancel(UART_Handle handle);
int_fast32_t UARTBLXXX_write(UART_Handle handle, const void *buffer,size_t size);
void         UARTBLXXX_writeCancel(UART_Handle handle);
uint_fast32_t UARTBLXXX_getDMAAddr(UART_Handle handle);
uint_fast8_t UARTBLXXX_getRxReq(UART_Handle handle);
uint_fast8_t UARTBLXXX_getTxReq(UART_Handle handle);

static void  UARTBLXXX_initHw(UART_Handle handle);
static bool  UARTBLXXX_initIO(UART_Handle handle);


static void UARTBLXXX_UART0_RX_Cbf(void);
static void UARTBLXXX_UART1_RX_Cbf(void);
static void UARTBLXXX_UART0_TX_Cbf(void);
static void UARTBLXXX_UART1_TX_Cbf(void);
static void UARTBLXXX_ERROR_Cbf(void);

static intCallback_Type * rx_func_list[]={
    UARTBLXXX_UART0_RX_Cbf,
    UARTBLXXX_UART1_RX_Cbf,
};

static intCallback_Type * tx_func_list[]={
    UARTBLXXX_UART0_TX_Cbf,
    UARTBLXXX_UART1_TX_Cbf,
};

UART_Handle uart_handle_temp[UARTBLXXX_MAX_UART_NUM];
BL_Sts_Type uart_device_open_status[UARTBLXXX_MAX_UART_NUM];
Ring_Buffer_Type      uart_rx_ringBuffer; 
static IRQn_Type uartIrqn_list[] = {
    UART0_IRQn,
    UART1_IRQn,
};

static const uint32_t uart_dma_addr_list[2]={
    0x4000A088,
    0x4000A08c,
};

/* UART function table for UARTBLXXX implementation */
const UART_FxnTable UARTBLXXX_fxnTable = {
    UARTBLXXX_close,
    UARTBLXXX_control,
    UARTBLXXX_init,
    UARTBLXXX_open,
    UARTBLXXX_read,
    UARTBLXXX_rxFifoDump,
    UARTBLXXX_readCancel,
    UARTBLXXX_write,
    UARTBLXXX_writeCancel,
    UARTBLXXX_getDMAAddr,
    UARTBLXXX_getRxReq,
    UARTBLXXX_getTxReq,
};


/*!
 *  @brief UART BLXXX initialization
 *
 *  @pre    Calling context: Hwi, Swi, Task, Main
 *
 *  @param handle  A UART_Handle
 *
 */
void UARTBLXXX_init(UART_Handle handle)
{
    UARTBLXXX_Object           *object;

    /* Get the pointer to the object */
    object = handle->object;
    object->opened = false;
}

/*!
 *  @brief  Function to initialize the BLXXX UART peripheral specified by the
 *          particular handle. The parameter specifies which mode the UART
 *          will operate.
 *
 *  The function will set a dependency on it power domain, i.e. power up the
 *  module and enable the clock. The IOs are allocated. Neither the RX nor TX
 *  will be enabled, and none of the interrupts are enabled.
 *
 *  @pre    UART controller has been initialized
 *          Calling context: Task
 *
 *  @param  handle        A UART_Handle
 *
 *  @param  params        Pointer to a parameter block, if NULL it will use
 *                        default values
 *
 *  @return A UART_Handle on success or a NULL on an error or if it has been
 *          already opened
 *
 *  @sa     UARTBLXXX_close()
 */
UART_Handle UARTBLXXX_open(UART_Handle handle, UART_Params *params)
{
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    object = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        MSG("UART:(%p) already in use.", handle);
        return (NULL);
    }

    object->opened = true;
    
    if(hwAttrs->deviceIndex > UARTBLXXX_MAX_UART_NUM){
        return (NULL);
    }

    /* Initialize the UART object */
    object->readMode       = params->readMode;
    object->writeMode      = params->writeMode;
    object->readTimeout    = params->readTimeout;
    object->writeTimeout   = params->writeTimeout;
    object->readCallback   = params->readCallback;
    object->writeCallback  = params->writeCallback;
    object->readReturnMode = params->readReturnMode;
    object->readDataMode   = params->readDataMode;
    object->writeDataMode  = params->writeDataMode;
    object->baudRate       = params->baudRate;
    object->dataLength     = params->dataLength;
    object->stopBits       = params->stopBits;
    object->parityType     = params->parityType;

    /* Set UART transaction variables to defaults. */
    object->writeBuf = NULL;
    object->readBuf = NULL;
    object->writeCount = 0;
    object->readCount = 0;
    object->writeSize = 0;
    object->readSize = 0;
    object->writeCR = false;

    object->ringBuffer = &uart_rx_ringBuffer;
    
    /* Configure IOs, make sure it was successful */
    if(UARTBLXXX_initIO(handle) != SUCCESS) {
        /* Trying to use UART driver when some other driver or application
        *  has already allocated these pins, error!
        */
        //DebugP_log0("Could not allocate pins, already in use.");
        /* Disable UART */
        UART_Disable(hwAttrs->deviceIndex,UART_TXRX);
        uart_device_open_status[hwAttrs->deviceIndex] = RESET;
        object->opened = false;
        return (NULL);
    }

    UARTBLXXX_initHw(handle);
    
    /* Create circular buffer object to be used for read buffering */
    //RingBuf_construct(&object->ringBuffer, hwAttrs->ringBufPtr, hwAttrs->ringBufSize);

    /*tell uart lhal device open status*/
    uart_device_open_status[hwAttrs->deviceIndex]= SET;

    /* steup up ringbuffer */
    /*Ring_Buffer_Type* rbType,uint8_t* buffer,uint16_t size,ringBuffer_Lock_Callback* lockCb,ringBuffer_Lock_Callback* unlockCb*/
    Ring_Buffer_Init(object->ringBuffer,hwAttrs->ringBufPtr,hwAttrs->ringBufSize,(ringBuffer_Lock_Callback *)hwAttrs->ringBufferLockFnx,(ringBuffer_Lock_Callback *)hwAttrs->ringBufferUnlockFnx);

    return (handle);
}

/*!
 *  @brief  Function to close a given BLXXX UART peripheral specified by the
 *          UART handle.
 *
 *  Will disable the UART, disable all UART interrupts and release the
 *  dependency on the corresponding power domain.
 *
 *  @pre    UARTBLXXX_open() had to be called first.
 *          Calling context: Task
 *
 *  @param  handle  A UART_Handle returned from UART_open()
 *
 *  @sa     UARTBLXXX_open
 */
void UARTBLXXX_close(UART_Handle handle)
{
    UARTBLXXX_Object            *object;
    UARTBLXXX_HWAttrsV2 const   *hwAttrs;

    /* Get the pointer to the object and hwAttrs */
    object = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Deallocate pins */
    //PIN_close(object->hPin); //TODO

    /* Disable all UART module interrupts. */
    UART_IntMask(hwAttrs->deviceIndex, UART_INT_ALL,MASK);  

    /* Clear all UART interrupts */
    UART_IntClear(hwAttrs->deviceIndex, UART_INT_ALL);

    /* Mark the module as available */
    object->opened = false;

    /* Cancel any possible ongoing reads/writes */
    UARTBLXXX_writeCancel(handle);
    UARTBLXXX_readCancel(handle);

    uart_device_open_status[hwAttrs->deviceIndex] = RESET;

    /* Disable UART module */
    UART_Disable(hwAttrs->deviceIndex,UART_TXRX);
}

/*!
 *  @brief  Function for setting control parameters of the UART
 *          after it has been opened.
 *
 *  @pre    UARTBLXXX_open() has to be called first.
 *          Calling context: Hwi, Swi, Task
 *
 *  @param  handle A UART handle returned from UARTBLXXX_open()
 *
 *  @param  cmd  The command to execute, supported commands are:
 *          | Command                               | Description             |
 *          |-------------------------------------- |-------------------------|
 *          | ::UARTBLXXX_CMD_RX_FIFO_FLUSH | Flush rx fifo buffer  |
 *
 *  @param  *arg  Pointer to command arguments, currently not in use, set to NULL.
 *
 *  @return ::UART_STATUS_SUCCESS if success, or error code if error.
 */
int_fast16_t UARTBLXXX_control(UART_Handle handle, uint_fast16_t cmd,void *arg){
    UARTBLXXX_Object            *object;
    UARTBLXXX_HWAttrsV2 const   *hwAttrs;
    int ret;

    /* Get the pointer to the object and hwAttrs */
    object = handle->object;
    hwAttrs = handle->hwAttrs;

    /* Initialize return value*/
    ret = UART_STATUS_UNDEFINEDCMD;

    switch(cmd)
    {
        case UARTBLXXX_CMD_RX_FIFO_FLUSH:
            /* Flush RX FIFO */
            hwAttrs = handle->hwAttrs;

            /* Read RX FIFO until empty */
            UART_RxFifoClear(hwAttrs->deviceIndex);

            /* Reset RingBuf */
            //Todo

            /* Set size = 0 to prevent reading and restore interrupts. */
            object->readSize = 0;

            ret = UART_STATUS_SUCCESS;
        break;

        case UARTBLXXX_CMD_TX_FREE_INT_ENABLE: UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,UNMASK);break;
        case UARTBLXXX_CMD_TX_FREE_INT_DISABLE: UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,MASK);break;
        case UARTBLXXX_CMD_RX_INT_ENABLE:UART_IntMask(hwAttrs->deviceIndex,UART_INT_RX_FIFO_REQ,UNMASK);UART_IntMask(hwAttrs->deviceIndex,UART_INT_RTO,UNMASK);break;
        case UARTBLXXX_CMD_RX_INT_DISABLE:UART_IntMask(hwAttrs->deviceIndex,UART_INT_RX_FIFO_REQ,MASK);UART_IntMask(hwAttrs->deviceIndex,UART_INT_RTO,MASK);break;
        default:
            /* This command is not defined */
            ret = UART_STATUS_UNDEFINEDCMD;
        break;
    }

    /* Return */
    return (ret);
}
/**
 * @brief uart write function 
 *        when write mode set as BLCOK WRITE MODE,write function will work as Blcok mode
 *        in Block Mode , uart will block send data until data all sent done or block time out
 *         
 * 
 * @param handle 
 * @param buffer 
 * @param size 
 * @return int_fast32_t 
 */
int_fast32_t UARTBLXXX_write(UART_Handle handle, const void *buffer,size_t size){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    /* Get the pointer to the object */
    object = handle->object;
    hwAttrs = handle->hwAttrs;   

    uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};
    uint32_t timeoutCnt = object->writeTimeout;

    if(object->writeMode == UART_MODE_BLOCKING){

    object->writeBuf = buffer;
    object->writeCount = 0;
    /* Send data */
    while(size){

        if(UART_GetTxFifoCount(hwAttrs->deviceIndex)>0){
            BL_WR_BYTE(uartAddr[hwAttrs->deviceIndex]+UART_FIFO_WDATA_OFFSET,*((uint8_t *)object->writeBuf + object->writeCount));
            object->writeCount++;
            timeoutCnt = object->writeTimeout;
            size --;
        }else{
            timeoutCnt--;
            if(timeoutCnt == 0){
                return TIMEOUT;
            }
        }

    }

    timeoutCnt = object->writeTimeout;

    while(UART_GetTxBusBusyStatus(hwAttrs->deviceIndex) == SET){}

    }else if(object->writeMode == UART_MODE_CALLBACK){
        /* Disable UART function. */
        UART_Disable(hwAttrs->deviceIndex,UART_TXRX);
        UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,tx_func_list[hwAttrs->deviceIndex]);

        uart_handle_temp[hwAttrs->deviceIndex] = handle;

        object->writeBuf = buffer;
        object->writeSize = size;
        object->writeCount =0;

        /*unmask interrupt */
        UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,UNMASK);

        /* Disable UART function. */
        UART_Enable(hwAttrs->deviceIndex,UART_TXRX);
    }else{

    }

    return SUCCESS;
}
/**
 * @brief Cancel write operation 
 * 
 * @param handle 
 * 
 * Not Supported
 */
void UARTBLXXX_writeCancel(UART_Handle handle){
    /* Not supported */
}
/**
 * @brief uart read data
 *        in block mode uart will read size data or read time out
 *        For examples
 *              while( UART_read(uart_device,read_buf,6) != SUCCESS);
 *        contorller will rec fixed len data or will timeout
 * @param handle 
 * @param buffer 
 * @param size 
 * @return int_fast32_t 
 */
int_fast32_t UARTBLXXX_read(UART_Handle handle, void *buffer, size_t size){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    /* Get the pointer to the object */
    object = handle->object;
    hwAttrs = handle->hwAttrs;   

    uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};
    uint32_t timeoutCnt = object->readTimeout;
    size_t recLen=0;

    if(object->readMode == UART_MODE_BLOCKING){

        while(recLen<=size){
            if(UART_GetRxFifoCount(hwAttrs->deviceIndex)>0){
                *((uint8_t *)buffer+recLen) = BL_RD_BYTE(uartAddr[hwAttrs->deviceIndex]+UART_FIFO_RDATA_OFFSET);
                recLen++;
                timeoutCnt = object->readTimeout;
            }else{
                timeoutCnt --;
                if(timeoutCnt == 0){
                    return TIMEOUT;
                }
            }
        }

    }else if(object->readMode == UART_MODE_CALLBACK){

    }else{
        /*
         * DMA MODE not support write
         * User can use DMA Module to start uart transfer
         */

    }

    return SUCCESS;
}

/**
 * @brief dump data stored at rx fifo
 * 
 * @param handle 
 * @return uint_fast16_t 
 */
uint_fast16_t UARTBLXXX_rxFifoDump(UART_Handle handle,uint8_t * buf){

    uint32_t  dataLenInRxFifo;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;
    
    hwAttrs = handle->hwAttrs;

    dataLenInRxFifo = UART_ReceiveData(hwAttrs->deviceIndex,buf,16);
    
    return dataLenInRxFifo;
}

/**
 * @brief Cancel read operation 
 * 
 * @param handle 
 * 
 * Not Supported
 */
void UARTBLXXX_readCancel(UART_Handle handle){
    /* Not supported */
}

/*
 *  ======== UARTBLXXX_initIO ========
 *  This functions initializes the UART IOs.
 *
 *  @pre    Function assumes that the UART handle is pointing to a hardware
 *          module which has already been opened.
 */
static bool UARTBLXXX_initIO(UART_Handle handle){
    /* Locals */
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;
    uint8_t uart_gpioPins[2];   
    uint8_t port_sig[4];

    //TODO:use pin_open to implement it

    /* Get the pointer to the object and hwAttrs */
    hwAttrs = handle->hwAttrs;

    uart_gpioPins[0] = hwAttrs->txPin;
    uart_gpioPins[1] = hwAttrs->rxPin;


    //TODO io redefine error check

    /*
     * Initial UART IO 
     */
    GLB_GPIO_Func_Init(GPIO_FUN_UART,uart_gpioPins,sizeof(uart_gpioPins)/sizeof(uart_gpioPins[0]));

    port_sig[0] = hwAttrs->txPin % 8;
    port_sig[1] = hwAttrs->rxPin % 8;

    if(port_sig[0] == port_sig[1]){
        return ERROR;
        /* single can not be same */
    }

    if(hwAttrs->deviceIndex == 0){
        GLB_UART_Fun_Sel(port_sig[0],GLB_UART_SIG_FUN_UART0_TXD);
        GLB_UART_Fun_Sel(port_sig[1],GLB_UART_SIG_FUN_UART0_RXD);
    }else{
        GLB_UART_Fun_Sel(port_sig[0],GLB_UART_SIG_FUN_UART1_TXD);
        GLB_UART_Fun_Sel(port_sig[1],GLB_UART_SIG_FUN_UART1_RXD);        
    }

    return SUCCESS;

}

/*
 *  ======== UARTBLXXX_initHW ========
 *  This functions initializes the UART hardware module.
 *
 *  @pre    Function assumes that the UART handle is pointing to a hardware
 *          module which has already been opened.
 */
static void UARTBLXXX_initHw(UART_Handle handle) {
    UARTBLXXX_Object *object;
    UARTBLXXX_HWAttrsV2 const *hwAttrs;
    UART_FifoCfg_Type UART_FifoCfg={
        16,                   /* TX FIFO threshold */
        16,                   /* RX FIFO threshold */
        DISABLE,              /* Disable tx dma req/ack interface */
        DISABLE               /* Disable rx dma req/ack interface */
    };
    UART_CFG_Type UART_CFG={
        96*1000*1000,                                        /* UART clock */
        2000000,                                             /* UART Baudrate */
        UART_DATABITS_8,                                     /* UART data bits length */
        UART_STOPBITS_1,                                     /* UART data stop bits length */
        UART_PARITY_NONE,                                    /* UART no parity */
        DISABLE,                                             /* Disable auto flow control */
        DISABLE,                                             /* Disable rx input de-glitch function */
        DISABLE,                                             /* Disable RTS output SW control mode */
        DISABLE,                                             /* Disable tx output SW control mode */
        DISABLE,                                             /* Disable tx lin mode */
        DISABLE,                                             /* Disable rx lin mode */
        0,                                                   /* Tx break bit count for lin mode */
        UART_LSB_FIRST                                       /* UART each data byte is send out LSB-first */
    };

    /* Get the pointer to the object and hwAttrs */
    object = handle->object;
    hwAttrs = handle->hwAttrs;

    if(hwAttrs->deviceIndex == 0){
        GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_UART0);
    }else{
        GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_UART1);        
    }

    /* Configure frame format and baudrate */
    GLB_Set_UART_CLK(ENABLE ,HBN_UART_CLK_96M,0);

    GLB_AHB_Slave1_Reset(BL_AHB_SLAVE1_UART0+hwAttrs->deviceIndex);

    /* Disable all UART module interrupts. */
    UART_IntMask(hwAttrs->deviceIndex, UART_INT_ALL,MASK);  

    /* Disable UART function. */
    UART_Disable(hwAttrs->deviceIndex,UART_TXRX);

    UART_CFG.baudRate = object->baudRate;
    UART_CFG.uartClk = 96*1000*1000;
    UART_CFG.dataBits = object->dataLength;
    UART_CFG.stopBits = object->stopBits;
    UART_CFG.parity = object->parityType;

    UART_Init(hwAttrs->deviceIndex,&UART_CFG);

    /* Clear all UART interrupts */
    UART_IntClear(hwAttrs->deviceIndex, UART_INT_ALL);

    /* Set TX interrupt FIFO level and RX interrupt FIFO level */
    UART_FifoCfg.txFifoDmaThreshold =  hwAttrs->dmaTxIntFifoThr;
    UART_FifoCfg.rxFifoDmaThreshold =  hwAttrs->dmaRxIntFifoThr;

    if(object->readMode == UART_MODE_DMA){
        UART_FifoCfg.rxFifoDmaEnable = ENABLE;
    }

    if(object->writeMode == UART_MODE_DMA){
        UART_FifoCfg.txFifoDmaEnable = ENABLE;
    }

    UART_FifoConfig(hwAttrs->deviceIndex, &UART_FifoCfg);


    /*unmask interrupt */
    UART_IntMask(hwAttrs->deviceIndex,UART_INT_PCE,UNMASK); // Parity error interrupt
    UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FER,UNMASK);// tx fifo overflow
    UART_IntMask(hwAttrs->deviceIndex,UART_INT_RX_FER,UNMASK);// rx fifo overflow

    UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_PCE,UARTBLXXX_ERROR_Cbf);
    UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_TX_FER,UARTBLXXX_ERROR_Cbf);
    UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_RX_FER,UARTBLXXX_ERROR_Cbf);


    /* Set rx time-out value used for data tail*/
    UART_SetRxTimeoutValue(hwAttrs->deviceIndex,UART_DEFAULT_RECV_TIMEOUT);

    /*unmask interrupt */
    UART_IntMask(hwAttrs->deviceIndex,UART_INT_RX_FIFO_REQ,MASK);
    UART_IntMask(hwAttrs->deviceIndex,UART_INT_RTO,MASK);

    /*install interrupt callback */
    UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_RX_FIFO_REQ,rx_func_list[hwAttrs->deviceIndex % UARTBLXXX_MAX_UART_NUM]);
    UART_Int_Callback_Install(hwAttrs->deviceIndex,UART_INT_RTO,rx_func_list[hwAttrs->deviceIndex % UARTBLXXX_MAX_UART_NUM]);

    uart_handle_temp[hwAttrs->deviceIndex] = handle;

    /* Enable UART interrupt*/
    NVIC_EnableIRQ(uartIrqn_list[hwAttrs->deviceIndex]);

    /* Enable tx free run mode */
    UART_TxFreeRun(hwAttrs->deviceIndex,ENABLE);
    UART_Enable(hwAttrs->deviceIndex,UART_TXRX);
}

static void UARTBLXXX_UART0_RX_Cbf(void){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;
    uint32_t rx_len=0;
    uint8_t rx_buf[UARTBLXXX_FIFO_SIZE];
    uint32_t maxLen = 0xFFFFFFFE;

    object = uart_handle_temp[0]->object;
    hwAttrs = uart_handle_temp[0]->hwAttrs;  
     
    rx_len = UART_ReceiveData(hwAttrs->deviceIndex,rx_buf,maxLen);

    if(object->readCallback != NULL){
        object->readCallback(uart_handle_temp[0],rx_buf,rx_len);
    }
}

static void UARTBLXXX_UART1_RX_Cbf(void){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;
    uint32_t rx_len=0;
    uint8_t rx_buf[UARTBLXXX_FIFO_SIZE];
    uint32_t maxLen = 0xFFFFFFFE;

    object = uart_handle_temp[1]->object;
    hwAttrs = uart_handle_temp[1]->hwAttrs;  
     
    rx_len = UART_ReceiveData(hwAttrs->deviceIndex,rx_buf,maxLen);

    if(object->readCallback != NULL){
        object->readCallback(uart_handle_temp[1],rx_buf,rx_len);
    }
}

static void UARTBLXXX_UART0_TX_Cbf(void){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};

    object = uart_handle_temp[0]->object;
    hwAttrs = uart_handle_temp[0]->hwAttrs;  
    
    while(UART_GetTxFifoCount(hwAttrs->deviceIndex)>0 && object->writeCount < object->writeSize){
        BL_WR_BYTE(uartAddr[hwAttrs->deviceIndex]+UART_FIFO_WDATA_OFFSET,*((uint8_t *)object->writeBuf + object->writeCount));
        object->writeCount++;
    }

    if(object->writeCount == object->writeSize){
        if(object->writeCallback != NULL){
            object->writeCallback(uart_handle_temp[0],(uint8_t *)object->writeBuf,object->writeSize);
        }
        UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,MASK);
    }
}

static void UARTBLXXX_UART1_TX_Cbf(void){
    UARTBLXXX_Object               *object;
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};

    object = uart_handle_temp[1]->object;
    hwAttrs = uart_handle_temp[1]->hwAttrs;  
    
    while(UART_GetTxFifoCount(hwAttrs->deviceIndex)>0 && object->writeCount < object->writeSize){
        BL_WR_BYTE(uartAddr[hwAttrs->deviceIndex]+UART_FIFO_WDATA_OFFSET,*((uint8_t *)object->writeBuf + object->writeCount));
        object->writeCount++;
    }

    if(object->writeCount == object->writeSize){
        if(object->writeCallback != NULL){
            object->writeCallback(uart_handle_temp[1],(uint8_t *)object->writeBuf,object->writeSize);
        }
        UART_IntMask(hwAttrs->deviceIndex,UART_INT_TX_FIFO_REQ,MASK);
    }
}


static void UARTBLXXX_ERROR_Cbf(void){
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    uint32_t tmpVal = 0;
    uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};
    uint32_t UARTx = 0;
    uint32_t maskVal = 0;
    uint8_t i=0;

    for(i=0;i<UARTBLXXX_MAX_UART_NUM;i++){

        if(uart_device_open_status[i] == SET){
            UARTx = uartAddr[i];
            tmpVal = BL_RD_REG(UARTx,UART_INT_STS);
            maskVal = BL_RD_REG(UARTx,UART_INT_MASK);

            hwAttrs = uart_handle_temp[i]->hwAttrs;  

            /* Rx parity check error interrupt */
            if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_PCE_MASK)){
                BL_WR_REG(UARTx,UART_INT_CLEAR,0x20);
                if(hwAttrs->errorFxn != NULL){
                    hwAttrs->errorFxn(uart_handle_temp[i],UART_INT_PCE);
                }
            }
            
            /* Tx fifo overflow/underflow error interrupt */
            if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_FER_MASK)){
                if(hwAttrs->errorFxn != NULL){
                    hwAttrs->errorFxn(uart_handle_temp[i],UART_INT_TX_FER);
                }
            }
            
            /* Rx fifo overflow/underflow error interrupt */
            if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_FER_MASK)){
                if(hwAttrs->errorFxn != NULL){
                    hwAttrs->errorFxn(uart_handle_temp[i],UART_INT_RX_FER);
                }
            }
        }
    }
}

uint_fast32_t  UARTBLXXX_getDMAAddr(UART_Handle handle){
    UARTBLXXX_HWAttrsV2 const *hwAttrs;
    uint32_t dma_addr;

    hwAttrs = handle->hwAttrs;

    dma_addr =  uart_dma_addr_list[hwAttrs->deviceIndex] + 0x100 * hwAttrs->deviceIndex;
    
    return dma_addr; 
}


uint_fast8_t UARTBLXXX_getRxReq(UART_Handle handle){
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->deviceIndex == 0){
        return DMA_REQ_UART0_RX;
    }else{
        return DMA_REQ_UART1_RX;
    }  

}
uint_fast8_t UARTBLXXX_getTxReq(UART_Handle handle){
    UARTBLXXX_HWAttrsV2 const     *hwAttrs;

    hwAttrs = handle->hwAttrs;

    if(hwAttrs->deviceIndex == 0){
        return DMA_REQ_UART0_TX;
    }else{
        return DMA_REQ_UART1_TX;
    }  
}

