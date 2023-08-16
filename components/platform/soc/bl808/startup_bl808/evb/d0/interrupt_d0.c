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
#include <stdio.h>
#include <stdint.h>
#include <csi_core.h>
#include <bl606p.h>
#include "system_bl606p.h"
#include "bl606p_glb.h"
#include "irq_ctx.h"

pFunc g_irqvector[IRQn_LAST] __attribute__ ((aligned (16))) = {NULL};

void Interrupt_Default_Handler(void) __attribute__ ((weak));
void Interrupt_Default_Handler(void){
    /* un-handled external IRQ */
    /* MSG("Enter interrupt default handler\r\n"); */
}

void Interrupt_Handler_Register(IRQn_Type irq,pFunc interruptFun)
{
    if(irq<IRQn_LAST){
        g_irqvector[irq]=interruptFun;
    }
}

static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs) __attribute__((noreturn));
static uintptr_t exception_handler_default(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    uintptr_t i = 0;

    printf("\n\rUn-handled Exception on CPU %d:\n\r", GLB_Get_Core_Type());
    printf("cause: %lx, tval = %lx, epc = %lx\n\r", cause, val, regs[REG_EPC_NDX]);

    for (i = 1; i < REG_INT_CTX_NDX; i ++) {
        if (!((i - 1) % 4)) printf("\n\r");
        printf("x%02ld = %16lx  ", i, regs[i]);
    }
    printf("\n\r");
    while(1);
}

static uintptr_t exception_handler_ECALL_M(uintptr_t cause, uintptr_t val, uintptr_t *regs)
{
    regs[REG_EPC_NDX] += 4;
    __asm volatile ("nop":::"memory");

    return 0;
}

static exception_handler exception_handlers[RV_EXCEPTION_NUM] = {
    exception_handler_default,        /*  0: Instruction Address Misaligned */
    exception_handler_default,        /*  1: Instruction Access Fault */
    exception_handler_default,        /*  2: Illegal Instruction */
    exception_handler_default,        /*  3: Breakpoint */
    exception_handler_default,        /*  4: Load Address Misaligned */
    exception_handler_default,        /*  5: Load Access Fault */
    exception_handler_default,        /*  6: Store/AMO Address Misaligned */
    exception_handler_default,        /*  7: Store/AMO Access Fault */
    exception_handler_default,        /*  8: Environment Call from U-mode */
    exception_handler_default,        /*  9: Environment Call from S-mode */
    exception_handler_default,        /* 10: Environment Call from H-mode */
    exception_handler_ECALL_M,        /* 11: Environment Call from M-mode */
    exception_handler_default,        /* 12: Instruction Page Fault */
    exception_handler_default,        /* 13: Load Page Fault */
    exception_handler_default,        /* 14: Reserved */
    exception_handler_default,        /* 15: Store/AMO Page Fault */
};

exception_handler exception_handler_install(uintptr_t vec, exception_handler handler)
{
    exception_handler previous = NULL;

    if (RV_EXCEPTION_NUM > vec) {
        previous = exception_handlers[vec];
        exception_handlers[vec] = handler;
    }

    return previous;
}
void riscv_savefpu(uintptr_t *regs);
void riscv_restorefpu(const uintptr_t *regs);


uintptr_t *trap_c(uintptr_t cause, uintptr_t *regs)
{
    uint32_t vec = 0;
    uintptr_t tval = __get_MTVAL();

    riscv_savefpu(regs);

    vec = cause & 0x3FF;

    if (RV_EXCEPTION_NUM > vec) {
        exception_handlers[vec](cause, tval, regs);
    } else {
        while (1);
    }

    riscv_restorefpu(regs);

    return regs;
}

/**
  \brief       enable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void ATTR_TCM_SECTION CPU_Interrupt_Enable(uint32_t irq_num)
{
    if(irq_num >= IRQn_LAST){
        //MSG("Error! This interrupt don't support!\n");
    }else{
        if(csi_vic_get_prio(irq_num) == 0){
            csi_vic_set_prio(irq_num, 1);
        }
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_enable_sirq(irq_num);
#else
        csi_vic_enable_irq(irq_num);
#endif
    }
}

/**
  \brief       disable irq.
  \param[in]   irq_num Number of IRQ.
  \return      None.
*/
void ATTR_TCM_SECTION CPU_Interrupt_Disable(uint32_t irq_num)
{
    if(irq_num >= IRQn_LAST){
        //MSG("Error! This interrupt don't support!\n");
    }else{
#ifdef CONFIG_SYSTEM_SECURE
        csi_vic_disable_sirq(irq_num);
#else
        csi_vic_disable_irq(irq_num);
#endif
    }
}


/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void ATTR_TCM_SECTION CPU_Interrupt_Pending_Clear(uint32_t irq_num)
{
    if(irq_num >= IRQn_LAST){
        //MSG("Error! This interrupt don't support!\n");
        return;
    }else{
#ifdef CONFIG_SYSTEM_SECURE
    	csi_vic_clear_pending_irq(irq_num);
#else
        csi_vic_clear_pending_irq(irq_num);
#endif
    }
}


void System_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    csi_vic_set_prio(IRQn, PreemptPriority);
}

void System_Interrupt_Init(void)
{
    for (uintptr_t irq = 0; irq < IRQn_LAST; irq ++)
    {
        g_irqvector[irq] = Interrupt_Default_Handler;
    }
}
