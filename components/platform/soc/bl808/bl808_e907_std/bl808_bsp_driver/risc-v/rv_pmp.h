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
#ifndef _RV_PMP_H_
#define _RV_PMP_H_

#define RV_PMP_ENTRY (8)

#define ENTRY_FLAG_PERM_R     (1 << 0)
#define ENTRY_FLAG_PERM_W     (1 << 1)
#define ENTRY_FLAG_PERM_X     (1 << 2)
#define ENTRY_FLAG_ADDR_OFF   (0 << 3)
#define ENTRY_FLAG_ADDR_TOR   (1 << 3)
#define ENTRY_FLAG_ADDR_NAPOT (3 << 3)
#define ENTRY_FLAG_ADDR_MASK  (3 << 3)
#define ENTRY_FLAG_M_MODE_L   (1 << 7)

#define ENTRY_FLAG_SIZE (8)
#define ENTRY_FLAG_MASK (0xFF)

#define ENTRY_IN_CFG_REG (__riscv_xlen / ENTRY_FLAG_SIZE)

/* E907: the smallest granularity is 128B */
/* C906: the smallest granularity is 4K */
#define PMP_REG_SZ_128B (1 <<  8)
#define PMP_REG_SZ_256B (1 <<  9)
#define PMP_REG_SZ_512B (1 << 10)
#define PMP_REG_SZ_1K   (1 << 11)
#define PMP_REG_SZ_2K   (1 << 12)
#define PMP_REG_SZ_4K   (1 << 12)
#define PMP_REG_SZ_8K   (1 << 13)
#define PMP_REG_SZ_16K  (1 << 14)
#define PMP_REG_SZ_32K  (1 << 15)
#define PMP_REG_SZ_64K  (1 << 16)
#define PMP_REG_SZ_128K (1 << 17)
#define PMP_REG_SZ_256K (1 << 18)
#define PMP_REG_SZ_512K (1 << 19)
#define PMP_REG_SZ_1M   (1 << 20)
#define PMP_REG_SZ_2M   (1 << 21)
#define PMP_REG_SZ_4M   (1 << 22)
#define PMP_REG_SZ_8M   (1 << 23)
#define PMP_REG_SZ_16M  (1 << 24)
#define PMP_REG_SZ_32M  (1 << 25)
#define PMP_REG_SZ_64M  (1 << 26)
#define PMP_REG_SZ_128M (1 << 27)
#define PMP_REG_SZ_256M (1 << 28)
#define PMP_REG_SZ_512M (1 << 29)
#define PMP_REG_SZ_1G   (1 << 30)
#define PMP_REG_SZ_1024M (PMP_REG_SZ_1G)

typedef enum _pmp_status_type_ {
    PMP_STATUS_OK = 0,
    PMP_STATUS_BUSY,
    PMP_STATUS_DENIED,
    PMP_STATUS_INVALID,
    PMP_STATUS_UNSUPPORTED,
    PMP_STATUS_MAX = 0x7FFFFFFF
} pmp_status_type_e;

typedef enum _addr_match_type_ {
    PMP_ADDR_MATCH_OFF = 0,
    PMP_ADDR_MATCH_TOR,
    PMP_ADDR_MATCH_NA4,
    PMP_ADDR_MATCH_NAPOT
} pmp_addr_match_type_e;

typedef struct _pmp_config_entry {
    uintptr_t entry_pa_base;
    uintptr_t entry_pa_length;
    uintptr_t entry_flag;
} pmp_config_entry_t;

pmp_status_type_e rvpmp_fill_entry(const pmp_config_entry_t *entry, uintptr_t i, uintptr_t force);
pmp_status_type_e rvpmp_init(const pmp_config_entry_t *entry, uintptr_t n);

#endif /* _RV_PMP_H_ */
