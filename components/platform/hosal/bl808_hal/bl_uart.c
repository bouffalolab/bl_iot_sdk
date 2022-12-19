/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <bl808_common.h>
#include <bl808_glb.h>
#include <bl808_gpio.h>
#include <bl808_uart.h>

#include "bl_irq.h"
#include "bl_uart.h"

#define UART_NUMBER_SUPPORTED   2
/*
 * We use HALF Empty for TX-Fifo trigger level
 * Also, the TX FIFO has depth 64 bytes
 * */
#define FIFO_TX_SIZE_BURST  (32)
#define NO_FPGA     0

#define UART_DEFAULT_RTO_TIMEOUT 100

static const uint32_t uartAddr[4] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE};

void UART0_IRQHandler(void);
void UART1_IRQHandler(void);

typedef struct bl_uart_notify {
    cb_uart_notify_t rx_cb;
    void            *rx_cb_arg;

    cb_uart_notify_t tx_cb;
    void            *tx_cb_arg;
} bl_uart_notify_t;

static bl_uart_notify_t g_uart_notify_arg[UART_NUMBER_SUPPORTED];

//TODO use pinmux function map provided by uplayer
static const GLB_GPIO_Type uart_pin[UART_NUMBER_SUPPORTED][2] =
{
    {GLB_GPIO_PIN_4,   GLB_GPIO_PIN_5},
    {GLB_GPIO_PIN_26,   GLB_GPIO_PIN_27},   /* TODO */
};
//static const int uart_fun[UART_NUMBER_SUPPORTED][2] =
//{
//    {GPIO26_FUN_UART_TXD,     GPIO27_FUN_UART_RXD},
//    {GPIO26_FUN_UART_TXD,     GPIO27_FUN_UART_RXD}, /* TODO */
//};

static const GLB_UART_SIG_Type uart_sig[UART_NUMBER_SUPPORTED][2] =
{
    {GLB_UART_SIG_4,    GLB_UART_SIG_5},
    {GLB_UART_SIG_3,    GLB_UART_SIG_8},
};

static const GLB_UART_SIG_FUN_Type uart_sig_fun[UART_NUMBER_SUPPORTED][2] =
{
    {GLB_UART_SIG_FUN_UART0_RXD,    GLB_UART_SIG_FUN_UART0_TXD},
    {GLB_UART_SIG_FUN_UART1_RXD,    GLB_UART_SIG_FUN_UART1_TXD},
};

static cb_uart_notify_t cbs_notify[UART_NUMBER_SUPPORTED];
static void *cbs_uart_notify_arg[UART_NUMBER_SUPPORTED][8];

#if NO_FPAG
static void gpio_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin)
{
    GLB_GPIO_Cfg_Type cfg;
    GLB_UART_SIG_FUN_Type tx_sigfun, rx_sigfun;

    cfg.drive = 1;
    cfg.smtCtrl = 1;
    cfg.gpioFun = 7;

    cfg.gpioPin = rx_pin;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);

    cfg.gpioPin = tx_pin;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);

    /*FIXME : need use sig swap ?*/
    //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, 1);
    GLB_UART_Fun_Sel(uart_sig[id][0], uart_sig_fun[id][1]);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig_fun[id][1], (GLB_UART_SIG_FUN_Type)uart_sig[id][0]);
 
    //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO0_GPIO11, 1);
    GLB_UART_Fun_Sel(uart_sig[id][1], uart_sig_fun[id][0]);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig_fun[id][0], (GLB_UART_SIG_FUN_Type)uart_sig[id][1]);
}
#endif

int bl_uart_gpio_init(uint8_t id, uint8_t tx, uint8_t rx, uint8_t rts, uint8_t cts, int baudrate)
{
/*FIXME :need know uart clk*/
#ifdef  WLAN_DEBUG
    uint32_t uart_clk = 32000000; //debug for fpga
#else
extern uint32_t SystemCoreClock;
    uint32_t uart_clk = SystemCoreClock ; //debug for fpga
#endif
    GLB_GPIO_Cfg_Type cfg;
    UART_CFG_Type uart_cfg = {
        160*1000*1000, /*UART clock*/
        115200,          /* baudrate  */
        UART_DATABITS_8,  /* data bits  */
        UART_STOPBITS_1,  /* stop bits */
        UART_PARITY_NONE, /* parity  */
        DISABLE,          /* Disable auto flow control */
        DISABLE,          /* Disable rx input de-glitch function */
        DISABLE,          /* Disable RTS output SW control mode */
        DISABLE,          /* Disable tx output SW control mode */
        DISABLE,          /* Disable tx lin mode */
        DISABLE,          /* Disable rx lin mode */
        0,                /* Tx break bit count for lin mode */
        UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };
    if (!(id < UART_NUMBER_SUPPORTED)) {
        return -1;
    }

    cfg.pullType = GPIO_PULL_NONE;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    if (tx) {
        /*set GPIO as UART TX */
        cfg.gpioPin = uart_pin[id][0];
        //cfg.gpioFun = uart_fun[id][0];
        cfg.gpioFun = GPIO_FUN_UART;
        cfg.gpioMode = GPIO_MODE_AF;
        cfg.pullType = GPIO_PULL_NONE;
        GLB_GPIO_Init(&cfg);
        /* select uart gpio function */
        /* FIXME need sig swap ? */
        //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 1);
        GLB_UART_Fun_Sel(uart_sig[id][0], uart_sig_fun[id][1]);
        GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig_fun[id][1], (GLB_UART_SIG_FUN_Type)uart_sig[id][0]);
    }

    if (rx) {
        /*set GPIO as UART RX */
        cfg.gpioPin = uart_pin[id][1];
        //cfg.gpioFun = uart_fun[id][1];
        cfg.gpioFun = GPIO_FUN_UART;
        cfg.gpioMode = GPIO_MODE_AF;
        cfg.pullType = GPIO_PULL_NONE;
        GLB_GPIO_Init(&cfg);
        /* select uart gpio function */
        /* FIXME need sig swap ? */
        //GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 1);
        /* FIXME enable rx sig ?*/
        //GLB_UART_Fun_Sel(uart_sig[id][1], uart_sig_fun[id][0]);
        //GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig_fun[id][0], (GLB_UART_SIG_FUN_Type)uart_sig[id][1]);
    }
    
    UART_FifoCfg_Type fifoCfg = {
      16,      /* TX FIFO threshold */
      16,      /* RX FIFO threshold */
      DISABLE, /* Disable tx dma req/ack interface */
      DISABLE  /* Disable rx dma req/ack interface */
    };
    
    /* disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);
    /* disable uart before config */
    UART_Disable(id, UART_TXRX);
    //Clock_Peripheral_Clock_Get(PERIPHERAL_CLOCK_UART);

    uart_cfg.baudRate = baudrate;
    uart_cfg.uartClk = uart_clk;

    /* uart init with default configuration */
    UART_Init(id, &uart_cfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(id, UART_DEFAULT_RTO_TIMEOUT);

    fifoCfg.txFifoDmaEnable = ENABLE;

    fifoCfg.rxFifoDmaEnable = ENABLE;

    UART_FifoConfig(id, &fifoCfg);
    /* enable uart */
    UART_Enable(id, UART_TXRX);
 
    return 0;
}

int bl_uart_c906_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate)
{
    UART_CFG_Type uart_dbg_cfg = {
      40 * 1000 * 1000, /*UART clock*/
      baudrate,          /* baudrate  */
      UART_DATABITS_8,  /* data bits  */
      UART_STOPBITS_1,  /* stop bits */
      UART_PARITY_NONE, /* parity  */
      DISABLE,          /* Disable auto flow control */
      DISABLE,          /* Disable rx input de-glitch function */
      DISABLE,          /* Disable RTS output SW control mode */
      DISABLE,          /* Disable tx output SW control mode */
      DISABLE,          /* Disable tx lin mode */
      DISABLE,          /* Disable rx lin mode */
      0,                /* Tx break bit count for lin mode */
      UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };

    UART_FifoCfg_Type fifoCfg = {
      16,      /* TX FIFO threshold */
      16,      /* RX FIFO threshold */
      DISABLE, /* Disable tx dma req/ack interface */
      DISABLE  /* Disable rx dma req/ack interface */
    };

    GLB_GPIO_Type gpioPins[2] = {tx_pin,rx_pin};
    GLB_GPIO_Func_Init(GPIO_FUN_MM_UART,gpioPins,sizeof(gpioPins)/sizeof(gpioPins[0]));

#if 0
    GLB_GPIO_Cfg_Type cfg;
    cfg.pullType = GPIO_PULL_NONE;
    cfg.drive = 0;
    cfg.smtCtrl = 1;
    cfg.gpioPin = uart_pin[id][0];
    //cfg.gpioFun = uart_fun[id][0];
    cfg.gpioFun = 27;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    /*set GPIO as UART RX */
    cfg.gpioPin = uart_pin[id][1];
    //cfg.gpioFun = uart_fun[id][1];
    cfg.gpioFun = 27;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);
#endif
    /* init debug uart gpio first */
    //gpio_init();

    /* Init UART clock，Todo */
    //GLB_Set_UART_CLK(ENABLE ,HBN_UART_CLK_160M,0);
    //uart_dbg_cfg.uartClk=160*1000*1000;

    if (baudrate != 0) {
        uart_dbg_cfg.baudRate = baudrate;
    }

    /* Todo */
    //if(UART0_ID==UART_DBG_ID){
    //    GLB_AHB_Slave1_Reset(BL_AHB_SLAVE1_UART0);
    //}else if(UART1_ID==UART_DBG_ID){
    //    GLB_AHB_Slave1_Reset(BL_AHB_SLAVE1_UART1);
    //}else{
    //    /* nothing */
    //}
    /* disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);

    /* disable uart before config */
    UART_Disable(id, UART_TXRX);

    /* uart init with default configuration */
    UART_Init(id, &uart_dbg_cfg);

    /* UART fifo configuration */
    UART_FifoConfig(id, &fifoCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(id, 80);

    /* enable uart */
    UART_Enable(id, UART_TXRX);
    return 0;
}

int bl_uart_int_rx_enable(uint8_t id)
{
    UART_SetRxTimeoutValue((UART_ID_Type)id, 24);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_FIFO_REQ, UNMASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_END, UNMASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RTO, UNMASK);
    return 0;
}

int bl_uart_int_rx_disable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_FIFO_REQ, MASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_END, MASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RTO, MASK);
    return 0;
}

int bl_uart_int_tx_enable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_TX_FIFO_REQ, UNMASK);
    return 0;
}

int bl_uart_int_tx_disable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_TX_FIFO_REQ, MASK);
    return 0;
}

int bl_uart_data_send(uint8_t id, uint8_t data)
{
    uint32_t UARTx = uartAddr[id];

    /* Wait for FIFO */
    while (UART_GetTxFifoCount(id) == 0) {
    }

    BL_WR_BYTE(UARTx + UART_FIFO_WDATA_OFFSET, data);

    return 0;
}

int bl_uart_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate)
{
#if NO_FPGA
    static uint8_t uart_clk_init = 0;
    const uint8_t uart_div = 3;

    UART_CFG_Type uartCfg = {
        160*1000*1000, /*UART clock*/
        115200,          /* baudrate  */
        UART_DATABITS_8,  /* data bits  */
        UART_STOPBITS_1,  /* stop bits */
        UART_PARITY_NONE, /* parity  */
        DISABLE,          /* Disable auto flow control */
        DISABLE,          /* Disable rx input de-glitch function */
        DISABLE,          /* Disable RTS output SW control mode */
        DISABLE,          /* Disable tx output SW control mode */
        DISABLE,          /* Disable tx lin mode */
        DISABLE,          /* Disable rx lin mode */
        0,                /* Tx break bit count for lin mode */
        UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };
    UART_FifoCfg_Type fifoCfg =
    {
        .txFifoDmaThreshold     = 0x10,
        .rxFifoDmaThreshold     = 0x10,
        .txFifoDmaEnable        = DISABLE,
        .rxFifoDmaEnable        = DISABLE,
    };

    /* enable clk */
    if (0 == uart_clk_init) {
        GLB_Set_UART_CLK(1, HBN_UART_CLK_160M, uart_div);
        uart_clk_init = 1;
    }

    /* gpio init */
    gpio_init(id, tx_pin, rx_pin, cts_pin, rts_pin);

    uartCfg.baudRate = baudrate;
    uartCfg.uartClk = (160 * 1000 * 1000) / (uart_div + 1);

    /* Disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);

    /* Disable uart before config */
    UART_Disable(id, UART_TXRX);

    /* UART init */
    UART_Init(id, &uartCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* FIFO Config*/
    UART_FifoConfig(id, &fifoCfg);

    /* Enable uart */
    UART_Enable(id, UART_TXRX);

#endif
    return 0;
}

int bl_uart_flush(uint8_t id)
{
#if NO_FPGA
    /* Wait for FIFO */
    while (UART_FIFO_TX_CNT != UART_GetTxFifoCount(id)) {
    }

    while(UART_GetTxBusBusyStatus(id) == SET){}
    
#endif
    return 0;
}

void bl_uart_setconfig(uint8_t id, uint32_t baudrate, UART_Parity_Type parity)
{
#if NO_FPGA
    UART_CFG_Type UartCfg = {
        160*1000*1000, /*UART clock*/
        115200,          /* baudrate  */
        UART_DATABITS_8,  /* data bits  */
        UART_STOPBITS_1,  /* stop bits */
        UART_PARITY_NONE, /* parity  */
        DISABLE,          /* Disable auto flow control */
        DISABLE,          /* Disable rx input de-glitch function */
        DISABLE,          /* Disable RTS output SW control mode */
        DISABLE,          /* Disable tx output SW control mode */
        DISABLE,          /* Disable tx lin mode */
        DISABLE,          /* Disable rx lin mode */
        0,                /* Tx break bit count for lin mode */
        UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };
    UartCfg.baudRate = baudrate;
    UartCfg.parity = parity;             //UART_PARITY_NONE

    /* Disable uart before config */
    UART_Disable(id, UART_TXRX);
    /* UART init */
    UART_Init(id, &UartCfg);
    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);
    /* Enable uart */
    UART_Enable(id, UART_TXRX);
#endif
}

void bl_uart_getdefconfig(uint8_t id, uint8_t *parity)
{
    if (NULL == parity) {
        return;
    }

    //*baudrate = 115200;/* not support set no baud */
    *parity = (uint8_t)UART_PARITY_NONE;
}

int bl_uart_data_send_II(uint8_t id)
{
    uint8_t *buffer, *idx_write, *idx_read;
    uint8_t idx_w, idx_r;

    buffer = cbs_uart_notify_arg[id][5];
    idx_write = cbs_uart_notify_arg[id][6];
    idx_read = cbs_uart_notify_arg[id][7];

    idx_w = *idx_write;
    idx_r = *idx_read;

    if (idx_r < idx_w) {
        UART_SendData((UART_ID_Type)id, &buffer[idx_r], idx_w - idx_r);
    } else {
        UART_SendData((UART_ID_Type)id, &buffer[idx_r], BL_UART_BUFFER_SIZE_MIN - idx_r);
        UART_SendData((UART_ID_Type)id, &buffer[0], idx_w);
    }

    /* all data sent, update ringbuffer status*/
    *idx_read = idx_w;

    return 0;
}

int bl_uart_datas_send(uint8_t id, uint8_t *data, int len)
{
    UART_SendData((UART_ID_Type)id, data, len);
    return 0;
}

int bl_uart_data_recv(uint8_t id)
{
    int ret;
    uint32_t UARTx = uartAddr[id];

    /* Receive data */
    if (UART_GetRxFifoCount(id) > 0) {
        ret  = BL_RD_BYTE(UARTx + UART_FIFO_RDATA_OFFSET);
    } else {
        ret = -1;
    }

    return ret;
}

int bl_uart_int_status_clear(uint8_t id)
{
#if 0
//    uint32_t intId;
    uart_reg_t * UARTx;

    switch (id) {
        case 0:
        {
            UARTx = (uart_reg_t *)UART0_BASE;
        }
        break;
        case 1:
        {
            UARTx = (uart_reg_t *)UART1_BASE;
        }
        break;
        default:
        {
            while (1) {
                /*hang here*/
            }
        }
    }
    //intId = UARTx->IIR_FCR.WORD;
    //(void)intId;

    if(((intId >>1)&0x3) == 2) {
        rt_hw_serial_isr(&(uart0.uart), RT_SERIAL_EVENT_RX_IND);
    }
#endif

    return 0;
}

void bl_uart_setbaud(uint8_t id, uint32_t baud)
{
    bl_uart_setconfig(id, baud, UART_PARITY_NONE);
}

int bl_uart_int_enable(uint8_t id)
{
    switch (id) {
        case 0:
        {
            bl_uart_int_rx_enable(0);
            bl_uart_int_tx_enable(0);
            bl_irq_register(UART0_IRQn, UART0_IRQHandler);
            bl_irq_enable(UART0_IRQn);
        }
        break;
        case 1:
        {
            bl_uart_int_rx_enable(1);
            bl_uart_int_tx_enable(1);
            bl_irq_register(UART1_IRQn, UART1_IRQHandler);
            bl_irq_enable(UART1_IRQn);
        }
        break;
        default:
        {
            return -1;
        }
    }

    return 0;
}

int bl_uart_int_disable(uint8_t id)
{
    switch (id) {
        case 0:
        {
            bl_uart_int_rx_disable(0);
            bl_uart_int_tx_disable(0);
            bl_irq_unregister(UART0_IRQn, UART0_IRQHandler);
            bl_irq_disable(UART0_IRQn);
        }
        break;
        case 1:
        {
            bl_uart_int_rx_disable(1);
            bl_uart_int_tx_disable(1);
            bl_irq_unregister(UART1_IRQn, UART1_IRQHandler);
            bl_irq_disable(UART1_IRQn);
        }
        break;
        default:
        {
            return -1;
        }
    }

    return 0;
}

int bl_uart_int_rx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }

    g_uart_notify_arg[id].rx_cb = cb;
    g_uart_notify_arg[id].rx_cb_arg = arg;

    return 0;
}

int bl_uart_int_tx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }

    g_uart_notify_arg[id].tx_cb = cb;
    g_uart_notify_arg[id].tx_cb_arg = arg;

    return 0;
}

int bl_uart_int_rx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }
    g_uart_notify_arg[id].rx_cb = NULL;
    g_uart_notify_arg[id].rx_cb_arg = NULL;

    return 0;
}

int bl_uart_int_tx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }
    g_uart_notify_arg[id].tx_cb = NULL;
    g_uart_notify_arg[id].tx_cb_arg = NULL;

    return 0;
}

int bl_uart_int_cb_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }

    cbs_uart_notify_arg[id][0] = arg;
    cbs_notify[id] = cb;

    return 0;
}

int bl_uart_int_cb_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }
    cbs_uart_notify_arg[id][0] = NULL;
    cbs_notify[id] =NULL;

    return 0;
}

// FIXME error: array subscript is above array bounds
static void uart_generic_notify_handler(uint8_t id)
{
    cb_uart_notify_t cb;
    void *arg;
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t UARTx = uartAddr[id];

    tmpVal = BL_RD_REG(UARTx,UART_INT_STS);
    maskVal = BL_RD_REG(UARTx,UART_INT_MASK);


    /* Length of uart tx data transfer arrived interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_END_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_END_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x1);
    }

    /* Length of uart rx data transfer arrived interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_END_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_END_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x2);

        /*Receive Data ready*/
        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Tx fifo ready interrupt,auto-cleared when data is pushed */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_FRDY_MASK)){
        /* Transmit data request interrupt */
        cb = g_uart_notify_arg[id].tx_cb;
        arg = g_uart_notify_arg[id].tx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx fifo ready interrupt,auto-cleared when data is popped */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_FRDY_MASK)){
        /*Receive Data ready*/

        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx time-out interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal,UART_URX_RTO_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_RTO_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x10);

        /*Receive Data ready*/
        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx parity check error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_PCE_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x20);
    }

    /* Tx fifo overflow/underflow error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_FER_MASK)){
    }

    /* Rx fifo overflow/underflow error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_FER_MASK)){
    }

    return;
#if 0
    if (UART_IS_RX_Fifo_Int(id)) {
        while (UART_ReceiveData(id, &ch) == SUCCESS) {
            if (((idx_w + 1) & BL_UART_BUFFER_SIZE_MASK) != idx_r) {
                /*buffer is not full. so we read to ring buffer and callback*/
                buffer[idx_w] = ch;
                idx_w = ((idx_w + 1) & BL_UART_BUFFER_SIZE_MASK);
            }
        }

        *idx_write = idx_w;
        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* refill tx bufffer if necessary */
    UART_TX_Refill((UART_ID_Type)id);

    return;
#endif
}

void UART0_IRQHandler(void)
{
    uart_generic_notify_handler(0);
}

void UART1_IRQHandler(void)
{
    uart_generic_notify_handler(1);
}

