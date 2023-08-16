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
#include "csi_core.h"
#include "rv_hart.h"
#include "riscv_encoding.h"

#define INSERT_FIELD(val, which, fieldval) \
    (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

void __attribute__((noreturn)) rv_hart_hang(void)
{
    while (1) {
        __WFI();
    }

    __builtin_unreachable();
}

/* determine CPU extension, return non-zero support */
int rv_hart_misa_ext_chk(char ext)
{
    unsigned long misa = read_csr(misa);

    if (misa) {
        if ('A' <= ext && ext <= 'Z') {
            return misa & (1 << (ext - 'A'));
        }

        if ('a' <= ext && ext <= 'z') {
            return misa & (1 << (ext - 'a'));
        }

        return 0;
    }

    return 0;
}

void rv_enterSupervisor(void)
{
    __asm volatile(
        "fence\n\t"
        "csrw mepc, ra\n\t"
        "li   t0, ~(3 << 11)\n\t"
        "li   t1, 1 << 11\n\t"
        "csrr t2, mstatus\n\t"
        "and  t0, t0, t2\n\t"
        "or   t0, t0, t1\n\t"
        "csrw mstatus, t0\n\t"
        "mret\n\t"
        :
        :
        : "memory");
}

void rv_enterUser(void)
{
    __asm volatile(
        "fence\n\t"
        "csrw mepc, ra\n\t"
        "li   t0, ~(3 << 11)\n\t"
        "csrr t2, mstatus\n\t"
        "and  t0, t0, t2\n\t"
        "csrw mstatus, t0\n\t"
        "mret\n\t"
        :
        :
        : "memory");
}

void __attribute__((noreturn))
rv_hart_switch_mode_from_M(uintptr_t arg0, uintptr_t arg1,
                           uintptr_t next_addr, uintptr_t next_mode)
{
#if __riscv_xlen == 32
    unsigned long val;
#else
    unsigned long val;
#endif

    switch (next_mode) {
        case PRV_M:
            break;

        case PRV_S:
            if (!rv_hart_misa_ext_chk('S')) {
                rv_hart_hang();
            }

            break;

        case PRV_U:
            if (!rv_hart_misa_ext_chk('U')) {
                rv_hart_hang();
            }

            break;

        default:
            rv_hart_hang();
    }

    val = read_csr(mstatus);
    val = INSERT_FIELD(val, MSTATUS_MPP, next_mode);
    val = INSERT_FIELD(val, MSTATUS_MPIE, 0);

    write_csr(mstatus, val);
    write_csr(mepc, next_addr);

    if (next_mode == PRV_S) {
        write_csr(stvec, next_addr);
        write_csr(sscratch, 0);
        write_csr(sie, 0);
        write_csr(satp, 0);
    } else if (next_mode == PRV_U) {
        /* un-implemented
		        write_csr(utvec, next_addr);
		        write_csr(uscratch, 0);
		        write_csr(uie, 0);
		*/
    }

    register unsigned long a0 __asm("a0") = arg0;
    register unsigned long a1 __asm("a1") = arg1;
    __asm__ __volatile__("mret"
                         :
                         : "r"(a0), "r"(a1));
    __builtin_unreachable();
}
