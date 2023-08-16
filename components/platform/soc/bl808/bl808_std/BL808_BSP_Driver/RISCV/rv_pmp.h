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
#ifndef _RV_PMP_H_
#define _RV_PMP_H_

#define RV_PMP_ENTRY          (16)

#define ENTRY_FLAG_PERM_R     (1 << 0)
#define ENTRY_FLAG_PERM_W     (1 << 1)
#define ENTRY_FLAG_PERM_X     (1 << 2)
#define ENTRY_FLAG_ADDR_OFF   (0 << 3)
#define ENTRY_FLAG_ADDR_TOR   (1 << 3)
#define ENTRY_FLAG_ADDR_NAPOT (3 << 3)
# define ENTRY_FLAG_ADDR_MASK (3 << 3)
#define ENTRY_FLAG_M_MODE_L   (1 << 7)

#define ENTRY_FLAG_SIZE       (8)
#define ENTRY_FLAG_MASK       (0xFF)

#define ENTRY_IN_CFG_REG      (__riscv_xlen / ENTRY_FLAG_SIZE)

/* C906: the smallest granularity is 4K */
#define PMP_REG_SZ_4K         (1 << 12)
#define PMP_REG_SZ_8K         (1 << 13)
#define PMP_REG_SZ_16K        (1 << 14)
#define PMP_REG_SZ_32K        (1 << 15)
#define PMP_REG_SZ_64K        (1 << 16)
#define PMP_REG_SZ_128K       (1 << 17)
#define PMP_REG_SZ_256K       (1 << 18)
#define PMP_REG_SZ_512K       (1 << 19)
#define PMP_REG_SZ_1M         (1 << 20)
#define PMP_REG_SZ_2M         (1 << 21)
#define PMP_REG_SZ_4M         (1 << 22)
#define PMP_REG_SZ_8M         (1 << 23)

typedef enum _addr_match_type_ {
    PMP_ADDR_MATCH_OFF = 0,
    PMP_ADDR_MATCH_TOR,
    PMP_ADDR_MATCH_NA4,
    PMP_ADDR_MATCH_NAPOT
} pmp_addr_match_type_e;


typedef struct _pmp_config_entry
{
    uintptr_t entry_pa_base;
    uintptr_t entry_pa_length;
    uintptr_t entry_flag;
} pmp_config_entry_t;

void rvpmp_init(const pmp_config_entry_t *entry, uintptr_t n);

#endif /* _RV_PMP_H_ */
