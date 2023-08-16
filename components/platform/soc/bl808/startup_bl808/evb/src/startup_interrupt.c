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

#include <stdint.h>
#include <clic.h>
#include <csi_rv32_gcc.h>
#ifdef BL808
#include "bl808.h"
#elif defined(BL606P)
#include "bl606p.h"
#else
#error "Use CHIP BL808/BL606P for this module"
#endif


#define MSG(...)

typedef void( *pFunc )( void );
void NMI_Handler(void);

pFunc g_irqvector[IRQn_LAST]={0};
pFunc g_nmivector=NMI_Handler;

extern void Default_IRQHandler(void);
extern void Default_Handler(void);
extern void freertos_risc_v_trap_handler(void);

const pFunc __Vectors[] __attribute__ ((section(".init"),aligned(64))) = {
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,            /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */
    freertos_risc_v_trap_handler,                         /*         */

    freertos_risc_v_trap_handler,//BMX_ERR_IRQHandler_Wrapper,              /* 16 +  0 */
    freertos_risc_v_trap_handler,//BMX_TO_IRQHandler_Wrapper,               /* 16 +  1 */
    freertos_risc_v_trap_handler,//L1C_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  2 */
    freertos_risc_v_trap_handler,//L1C_BMX_TO_IRQHandler_Wrapper,           /* 16 +  3 */
    freertos_risc_v_trap_handler,//SEC_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  4 */
    freertos_risc_v_trap_handler,//RF_TOP_INT0_IRQHandler_Wrapper,          /* 16 +  5 */
    freertos_risc_v_trap_handler,//RF_TOP_INT1_IRQHandler_Wrapper,          /* 16 +  6 */
    freertos_risc_v_trap_handler,//SDIO_IRQHandler_Wrapper,                 /* 16 +  7 */
    freertos_risc_v_trap_handler,//DMA_BMX_ERR_IRQHandler_Wrapper,          /* 16 +  8 */
    freertos_risc_v_trap_handler,//SEC_GMAC_IRQHandler_Wrapper,             /* 16 +  9 */
    freertos_risc_v_trap_handler,//SEC_CDET_IRQHandler_Wrapper,             /* 16 + 10 */
    freertos_risc_v_trap_handler,//SEC_PKA_IRQHandler_Wrapper,              /* 16 + 11 */
    freertos_risc_v_trap_handler,//SEC_TRNG_IRQHandler_Wrapper,             /* 16 + 12 */
    freertos_risc_v_trap_handler,//SEC_AES_IRQHandler_Wrapper,              /* 16 + 13 */
    freertos_risc_v_trap_handler,//SEC_SHA_IRQHandler_Wrapper,              /* 16 + 14 */
    freertos_risc_v_trap_handler,//DMA_ALL_IRQHandler_Wrapper,              /* 16 + 15 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 16 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 17 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 18 */
    freertos_risc_v_trap_handler,//IRTX_IRQHandler_Wrapper,                 /* 16 + 19 */
    freertos_risc_v_trap_handler,//IRRX_IRQHandler_Wrapper,                 /* 16 + 20 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 21 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 22 */
    freertos_risc_v_trap_handler,//SF_CTRL_IRQHandler_Wrapper,              /* 16 + 23 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 24 */
    freertos_risc_v_trap_handler,//GPADC_DMA_IRQHandler_Wrapper,            /* 16 + 25 */
    freertos_risc_v_trap_handler,//EFUSE_IRQHandler_Wrapper,                /* 16 + 26 */
    freertos_risc_v_trap_handler,//SPI_IRQHandler_Wrapper,                  /* 16 + 27 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 28 */
    freertos_risc_v_trap_handler,//UART0_IRQHandler_Wrapper,                /* 16 + 29 */
    freertos_risc_v_trap_handler,//UART1_IRQHandler_Wrapper,                /* 16 + 30 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 31 */
    freertos_risc_v_trap_handler,//I2C_IRQHandler_Wrapper,                  /* 16 + 32 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 33 */
    freertos_risc_v_trap_handler,//PWM_IRQHandler_Wrapper,                  /* 16 + 34 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 35 */
    freertos_risc_v_trap_handler,//TIMER_CH0_IRQHandler_Wrapper,            /* 16 + 36 */
    freertos_risc_v_trap_handler,//TIMER_CH1_IRQHandler_Wrapper,            /* 16 + 37 */
    freertos_risc_v_trap_handler,//TIMER_WDT_IRQHandler_Wrapper,            /* 16 + 38 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 39 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 40 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 41 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 42 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 43 */
    freertos_risc_v_trap_handler,//GPIO_INT0_IRQHandler_Wrapper,            /* 16 + 44 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 45 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 46 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 47 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 48 */
    freertos_risc_v_trap_handler,//0,                                       /* 16 + 49 */
    freertos_risc_v_trap_handler,//PDS_WAKEUP_IRQHandler_Wrapper,           /* 16 + 50 */
    freertos_risc_v_trap_handler,//HBN_OUT0_IRQHandler_Wrapper,             /* 16 + 51 */
    freertos_risc_v_trap_handler,//HBN_OUT1_IRQHandler_Wrapper,             /* 16 + 52 */
    freertos_risc_v_trap_handler,//BOR_IRQHandler_Wrapper,                  /* 16 + 53 */
    freertos_risc_v_trap_handler,//WIFI_IRQHandler_Wrapper,                 /* 16 + 54 */
    freertos_risc_v_trap_handler,//BZ_PHY_IRQHandler_Wrapper,               /* 16 + 55 */
    freertos_risc_v_trap_handler,//BLE_IRQHandler_Wrapper,                  /* 16 + 56 */
    freertos_risc_v_trap_handler,//MAC_TXRX_TIMER_IRQHandler_Wrapper,       /* 16 + 57 */
    freertos_risc_v_trap_handler,//MAC_TXRX_MISC_IRQHandler_Wrapper,        /* 16 + 58 */
    freertos_risc_v_trap_handler,//MAC_RX_TRG_IRQHandler_Wrapper,           /* 16 + 59 */
    freertos_risc_v_trap_handler,//MAC_TX_TRG_IRQHandler_Wrapper,           /* 16 + 60 */
    freertos_risc_v_trap_handler,//MAC_GEN_IRQHandler_Wrapper,              /* 16 + 61 */
    freertos_risc_v_trap_handler,//MAC_PORT_TRG_IRQHandler_Wrapper,         /* 16 + 62 */
    freertos_risc_v_trap_handler,//WIFI_IPC_PUBLIC_IRQHandler_Wrapper,      /* 16 + 63 */
};

void trap_c(uint32_t *regs)
{
    int i;
    uint32_t vec = 0;

    vec = __get_MCAUSE() & 0x3FF;

    MSG("CPU Exception: NO.%d", vec);
    MSG("\n");

    for (i = 0; i < 31; i++) {
        MSG("x%d: %08x\t", i + 1, regs[i]);

        if ((i % 4) == 3) {
            MSG("\n");
        }
    }

    MSG("\n");
    MSG("mepc   : %08x\n", regs[31]);
    MSG("mstatus: %08x\n", regs[32]);

    //if (trap_c_callback) {
    //    trap_c_callback();
    //}

    while (1);
}

void NMI_Handler(void)
{

    MSG("NMI_Handler\r\n");

    while (1);
}

void Interrupt_Handler_Register(IRQn_Type irq,pFunc interruptFun)
{
    if(irq<IRQn_LAST){
        g_irqvector[irq]=interruptFun;
    }
}

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Enable(uint32_t irq_num)
{
#ifdef CONFIG_SYSTEM_SECURE
    csi_vic_enable_sirq(irq_num);
#else
    csi_vic_enable_irq(irq_num);
#endif
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void CPU_Interrupt_Disable(uint32_t irq_num)
{
#ifdef CONFIG_SYSTEM_SECURE
    csi_vic_disable_sirq(irq_num);
#else
    csi_vic_disable_irq(irq_num);
#endif
}
