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
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"
#include "bflb_platform.h"
#include "platform_gpio.h"
#include "platform_device.h"
#include "ring_buffer.h"
#ifndef USE_UART_OUTPUT
#define USE_UART_OUTPUT     1
#endif

static uint8_t uart_dbg_disable=0;
#if ((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
#define UART_DBG_ID     UART1_ID
#define UART_DBG_IRQN   UART1_IRQn
#else
#ifdef LOG_UART_ID_0
#define UART_DBG_ID     UART0_ID
#define UART_DBG_IRQN   UART0_IRQn
#else
#define UART_DBG_ID     UART1_ID
#define UART_DBG_IRQN   UART1_IRQn
#endif

#endif

#if 0
#define BFLB_SYSTICK_INT_RATE   20

#define PLATFORM_INIT_FALSE     (0)
#define PLATFORM_INIT_TRUE      (1)

static const uint8_t hexTable[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
static volatile uint32_t systick_int_cnt=0;
#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
static Ring_Buffer_Type uartRB;
static uint8_t uartBuf[64];
#endif

//static uint32_t init_flag = PLATFORM_INIT_FALSE;

/****************************************************************************//**
 * @brief  UART RX fifo ready interrupt call back function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
static void UART_RFR_Cbf(void)
{
    uint8_t tmpBuf[16];
    uint32_t len=UART_GetRxFifoCount(UART_DBG_ID);
    Ring_Buffer_Write_Callback(&uartRB,len,(ringBuffer_Write_Callback*)(uintptr_t)UART_ReceiveData,
                                (void*)UART_DBG_ID);

    /* Check buf is full */
    len=UART_GetRxFifoCount(UART_DBG_ID);
    if(len!=0&&Ring_Buffer_Get_Empty_Length(&uartRB)==0){
        bflb_platform_printf("UART Recv Full\r\n");
        do{
            UART_ReceiveData(UART_DBG_ID,tmpBuf,sizeof(tmpBuf));
        }while(UART_GetRxFifoCount(UART_DBG_ID));
    }
}
#endif

/****************************************************************************//**
 * @brief  UART RX time-out interrupt call back function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
static void UART_RTO_Cbf(void)
{
    uint8_t tmpBuf[16];
    uint32_t len=UART_GetRxFifoCount(UART_DBG_ID);
    Ring_Buffer_Write_Callback(&uartRB,len,(ringBuffer_Write_Callback*)(uintptr_t)UART_ReceiveData,
                                (void*)UART_DBG_ID);

    /* Check buf is full */
    len=UART_GetRxFifoCount(UART_DBG_ID);
    if(len!=0&&Ring_Buffer_Get_Empty_Length(&uartRB)==0){
        bflb_platform_printf("UART Recv Full\r\n");
        do{
            UART_ReceiveData(UART_DBG_ID,tmpBuf,sizeof(tmpBuf));
        }while(UART_GetRxFifoCount(UART_DBG_ID));
    }
}
#endif

void bflb_platform_uart_dbg_init(uint32_t bdrate)
{
    UART_CFG_Type uart_dbg_cfg={
                                    32*1000*1000,         /*UART clock*/
                                    2000000,              /* baudrate  */
                                    UART_DATABITS_8,      /* data bits  */
                                    UART_STOPBITS_1,      /* stop bits */
                                    UART_PARITY_NONE,     /* parity  */
                                    DISABLE,              /* Disable auto flow control */
                                    DISABLE,              /* Disable rx input de-glitch function */
                                    DISABLE,              /* Disable RTS output SW control mode */
                                    DISABLE,              /* Disable tx output SW control mode */
                                    DISABLE,              /* Disable tx lin mode */
                                    DISABLE,              /* Disable rx lin mode */
                                    0,                    /* Tx break bit count for lin mode */
                                    UART_LSB_FIRST,       /* UART each data byte is send out LSB-first */
    };
    UART_FifoCfg_Type fifoCfg = {
                                    16,                   /* TX FIFO threshold */
                                    16,                   /* RX FIFO threshold */
                                    DISABLE,              /* Disable tx dma req/ack interface */
                                    DISABLE               /* Disable rx dma req/ack interface */
    };

    /* init debug uart gpio first */
    bflb_platform_init_uart_debug_gpio();
#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    Ring_Buffer_Init(&uartRB,uartBuf,sizeof(uartBuf),NULL,NULL);
#endif

    /* Init UART clock */
    GLB_Set_UART_CLK(ENABLE ,HBN_UART_CLK_MCU_BCLK,0);
    uart_dbg_cfg.uartClk=Clock_System_Clock_Get(BL_SYSTEM_CLOCK_MCU_BCLK);

    if(bdrate!=0){
        uart_dbg_cfg.baudRate=bdrate;
    }
    
    /* Reset uart register to default value */
    UART_DeInit(UART_DBG_ID);
    
    /* disable all interrupt */
    UART_IntMask(UART_DBG_ID, UART_INT_ALL, MASK);

    /* disable uart before config */
    UART_Disable(UART_DBG_ID,UART_TXRX);

    /* uart init with default configuration */
    UART_Init(UART_DBG_ID, &uart_dbg_cfg);

    /* UART fifo configuration */
    UART_FifoConfig(UART_DBG_ID,&fifoCfg);


    /* Enable tx free run mode */
    UART_TxFreeRun(UART_DBG_ID,ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(UART_DBG_ID,80);

#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    /* UART interrupt configuration */
    UART_IntMask(UART_DBG_ID,UART_INT_RX_FIFO_REQ,UNMASK);
    UART_IntMask(UART_DBG_ID,UART_INT_RTO,UNMASK);

    /* Install the interrupt callback function */
    UART_Int_Callback_Install(UART_DBG_ID,UART_INT_RX_FIFO_REQ,&UART_RFR_Cbf);
    UART_Int_Callback_Install(UART_DBG_ID,UART_INT_RTO,&UART_RTO_Cbf);

    /* Enable UART interrupt*/
    CPU_Interrupt_Enable(UART_DBG_IRQN);
#endif
    /* enable uart */
    UART_Enable(UART_DBG_ID,UART_TXRX);
}

#if ((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
static uint8_t eflash_loader_logbuf[4096] __attribute__ ((section(".system_ram_noinit")));
static uint32_t log_len=0;
uint32_t bflb_platform_get_log(uint8_t *data,uint32_t maxlen)
{
    uint32_t len=log_len;
    if(len>maxlen){
        len=maxlen;
    }
    memcpy(data,eflash_loader_logbuf,len);
    return len;
}
#endif

#endif
void bflb_platform_usart_dbg_send(uint8_t *data,uint32_t len)
{
#if ((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
    if(log_len+len<sizeof(eflash_loader_logbuf)){
        memcpy(eflash_loader_logbuf+log_len,data,len);
        log_len+=len;
    }
#endif
    UART_SendData(UART_DBG_ID, data, len);
}

#if 0
void bflb_platform_uart_dbg_deinit()
{
	uint32_t cnt=0;

	while(UART_GetTxBusBusyStatus(UART_DBG_ID)==SET){
		ARCH_Delay_US(10);
		cnt++;
		if(cnt>100){
			break;
		}
	}

    UART_Disable(UART_DBG_ID,UART_TXRX);
    UART_DeInit(UART_DBG_ID);
    bflb_platform_deinit_uart_debug_gpio();
}
#endif

void bflb_platform_printf(char *fmt,...)
{
    static char print_buf[128];
    va_list ap;
    if(!uart_dbg_disable){
        va_start(ap, fmt);
        vsnprintf(print_buf, sizeof(print_buf)-1, fmt, ap);
        va_end(ap);
        bflb_platform_usart_dbg_send((uint8_t*)print_buf,strlen(print_buf));
    }
}

#if 0
void bflb_platform_dump(const void *data,uint32_t len)
{
    uint32_t i=0;
    uint8_t *p=(uint8_t *)data;

    for(i=0;i<len;i++){
        if(i%16==0){
            bflb_platform_printf("\r\n");
        }
        bflb_platform_printf("%02x ",p[i]);
    }
    bflb_platform_printf("\r\n");
}

void bflb_platform_prints(char *data)
{
    bflb_platform_usart_dbg_send((uint8_t*)data,strlen(data));
}

void bflb_platform_printx(uint32_t val)
{
    uint8_t print_buf[8];
    int32_t i;
    for(i=7;i>=0;i--){
        print_buf[i]=hexTable[(val&0xf)];
        val>>=4;
    }
    bflb_platform_usart_dbg_send((uint8_t*)print_buf,8);
}

void bflb_platform_printc(char c)
{
    UART_SendData(UART_DBG_ID,(uint8_t *)&c,1);
}
#endif
void bflb_platform_clear_time()
{
    CPU_Reset_MTimer();
}

uint64_t  bflb_platform_get_time_us()
{
    return CPU_Get_MTimer_US();
}

uint64_t  bflb_platform_get_time_ms()
{
    return CPU_Get_MTimer_MS();
}

void bflb_platform_set_alarm_time_callback(pFunc interruptFun)
{
    Interrupt_Handler_Register(MTIME_IRQn,interruptFun);
}

void bflb_platform_set_alarm_time(uint64_t time)
{
    /* ToDo */
}

void bflb_platform_init_time()
{
    uint32_t clkSrc=CPU_Get_MTimer_Source_Clock();

    CPU_Interrupt_Disable(MTIME_IRQn);

    if(clkSrc>1*1000*1000){
        /* Set MTimer clock source 1M */
        CPU_Set_MTimer_CLK(1,clkSrc/1000/1000-1);
    }else{
        /* Set MTimer clock source 1k */
        CPU_Set_MTimer_CLK(1,clkSrc/1000-1);
    }

    bflb_platform_clear_time();
}

void bflb_platform_deinit_time()
{
    CPU_Interrupt_Disable(MTIME_IRQn);
}

void bflb_platform_delay_us(uint32_t time)
{
	CPU_MTimer_Delay_US(time);

    return ;
}

void bflb_platform_delay_ms(uint32_t time)
{
	CPU_MTimer_Delay_MS(time);

    return ;
}
#if 0
void bflb_platform_init(uint32_t baudrate)
{
#if 0
    /* Bootrom will reinit due to PLL config, so comment */
    if(PLATFORM_INIT_FALSE!=init_flag){
        return ;
    }
    init_flag = PLATFORM_INIT_TRUE;
#endif
#if 0
    GLB_Power_On_XTAL_And_PLL_CLK(GLB_PLL_XTAL_40M,GLB_PLL_POWER_ON_WIFIPLL|GLB_PLL_POWER_ON_CPUPLL);
    GLB_Set_Muxpll_320M_Sel(GLB_MUXPLL_SEL_320M_CPUPLL);
    GLB_Set_Muxpll_240M_Sel(GLB_MUXPLL_SEL_240M_WIFIPLL);
    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_320M_MUXPLL);
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_640M_CPUPLL);
#endif

    bflb_platform_init_time();
  
    if(!uart_dbg_disable){
        bflb_platform_uart_dbg_init(baudrate);
        bflb_platform_printf("system clock=%d\r\n",SystemCoreClockGet());
    }
}


void bflb_platform_deinit()
{
#if 0
    if(PLATFORM_INIT_FALSE==init_flag){
        return ;
    }
    init_flag = PLATFORM_INIT_FALSE;
#endif
    bflb_platform_deinit_time();
        
    if(!uart_dbg_disable){
        bflb_platform_uart_dbg_deinit();
    }
}

void bflb_platform_print_set(uint8_t logDisable)
{
    uart_dbg_disable=logDisable;
}

uint32_t bflb_platform_print_disable_get(void)
{
    return uart_dbg_disable;
}

int bflb_platform_get_random(uint8_t *data,uint32_t len)
{
    uint8_t tmpBuf[32];
    uint32_t readLen=0;
    uint32_t i=0,cnt=0;

    while(readLen<len){
        if(Sec_Eng_Trng_Read(tmpBuf)!=SUCCESS){
            return -1;
        }
        cnt=len-readLen;
        if(cnt>sizeof(tmpBuf)){
            cnt=sizeof(tmpBuf);
        }
        for(i=0;i<cnt;i++){
            data[readLen+i]=tmpBuf[i];
        }
        readLen+=cnt;
    }

    return 0;
}

#if !((defined BOOTROM) || (defined BFLB_EFLASH_LOADER))
int bflb_platform_get_input(uint8_t *data,uint32_t maxLen)
{
    uint32_t retLen=Ring_Buffer_Get_Length(&uartRB);

    if(retLen>maxLen){
        retLen=maxLen;
    }

    return Ring_Buffer_Read(&uartRB,data,retLen);
}

int bflb_platform_get_length(void)
{
    return Ring_Buffer_Get_Length(&uartRB);
}
#endif
#endif
