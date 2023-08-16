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
#ifndef _RV_SYSCALL_H_
#define _RV_SYSCALL_H_

#include <stdint.h>
#include <riscv_encoding.h>

#define RV_SYSCALL_BACK_TO_MACHINE  0
#define RV_SYSCALL_WFI              1


#ifndef __riscv_32e

#define RV_SYSCALL(which, arg0, arg1, arg2, arg3) ({           \
    register uintptr_t a0 __asm ("a0") = (uintptr_t)(arg0);    \
    register uintptr_t a1 __asm ("a1") = (uintptr_t)(arg1);    \
    register uintptr_t a2 __asm ("a2") = (uintptr_t)(arg2);    \
    register uintptr_t a3 __asm ("a3") = (uintptr_t)(arg3);    \
    register uintptr_t a7 __asm ("a7") = (uintptr_t)(which);   \
    asm volatile ("ecall"                                      \
              : "+r" (a0)                                      \
              : "r" (a1), "r" (a2), "r" (a3), "r" (a7)         \
              : "memory");                                     \
    a0;                                                        \
})

#else

#define RV_SYSCALL(which, arg0, arg1, arg2, arg3) ({           \
    register uintptr_t a0 __asm ("a0") = (uintptr_t)(arg0);    \
    register uintptr_t a1 __asm ("a1") = (uintptr_t)(arg1);    \
    register uintptr_t a2 __asm ("a2") = (uintptr_t)(arg2);    \
    register uintptr_t a3 __asm ("a3") = (uintptr_t)(arg3);    \
    register uintptr_t a5 __asm ("a5") = (uintptr_t)(which);   \
    asm volatile ("ecall"                                      \
              : "+r" (a0)                                      \
              : "r" (a1), "r" (a2), "r" (a3), "r" (a5)         \
              : "memory");                                     \
    a0;                                                        \
})

#endif

static inline void rv_syscall_back_to_machine(void)
{
    RV_SYSCALL(RV_SYSCALL_BACK_TO_MACHINE, 0, 0, 0, 0);
}

#endif /* _RV_SYSCALL_H_ */
