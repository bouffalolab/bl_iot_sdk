/*
 * Copyright (C) 2016-2020 Bouffalo Lab
 */
#include "riscv_encoding.h"

_start:
    .text
    .align  2
    .globl  Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
.option push
.option norelax
    la      gp, __global_pointer$
.option pop

    li      t0, MSTATUS_MIE | MSTATUS_SIE
    csrc    mstatus, t0

    /* mapbaddr */
    /* ? clear PLIC ?*/
    csrr    t1, 0xfc1
    li      t2, 0x00200004
    add     t2, t2, t1
    lw      t3, 0(t2)
    sw      t3, 0(t2)
    li      t4, 0x00201004
    add     t2, t4, t1
    lw      t3, 0(t2)
    sw      t3, 0(t2)

    csrw    mie, zero
    csrw    mip, zero

	/* invalid all MMU TLB Entry */
    sfence.vma x0,x0

    /* TODO: debug */
    csrw    mcycle, zero
    csrw    minstret, zero

    /*
     * enable thead ISA extension:
     * THEADISAEE = 1, MM = 1,
     */
    csrr    t0, mxstatus
    li      t1, (1 << 22) | (1 << 15)
    or      t1, t1, t0
    csrw    mxstatus, t1

    /* FP: initial state */
    csrr    t0, mstatus
    li      t1, ~0x6000
    and     t0, t0, t1
    li      t1, 0x2000
    or      t0, t0, t1
    csrw    mstatus, t0
    /* csrwi   fcsr, 0 */

    /* RVV: initial state */
    li    t0, ~(3 << 23)
    csrr  t1, mstatus
    and   t2, t1, t0
    li    t0, 1 << 23
    or    t2, t2, t0
    csrw  mstatus, t2

    la      a0, __Vectors__
    ori     a0, a0, 1
    csrw    mtvec, a0

    la      a0, __Vectors_S__
    ori     a0, a0, 1
    csrw    stvec, a0

    .weak __StackTop
    la      sp, __StackTop
    csrw    mscratch, sp

#if defined(DUAL_CORE)
    /* dual core test */
    li      t0, 0xF0000000
    li      t1, 0xDEAD5501
    lw      t2, 0(t0)
    li      t0, 0xffffffff
    and     t2, t2, t0
    beq     t1, t2, Set_Stack_D1

    call    D0_wakeup_D1
    j       cont_D0

Set_Stack_D1:
    /* on D1 */
    /* TODO: dedicate stack area for D1 */
    addi    sp, sp, -2048
    csrw    mscratch, sp

cont_D0:
#endif /* DUAL_CORE */

#ifndef __NO_SYSTEM_INIT
    jal     SystemInit
#endif

    /* start load code to itcm like. */
    jal     start_load

#ifndef __NO_BOARD_INIT

    jal     board_init
#endif

    jal     bfl_main

    .size   Reset_Handler, . - Reset_Handler

__exit:
    j      __exit
