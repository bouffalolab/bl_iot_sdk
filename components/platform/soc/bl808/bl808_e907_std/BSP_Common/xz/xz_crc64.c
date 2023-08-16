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

/*
 * CRC64 using the polynomial from ECMA-182
 *
 * This file is similar to xz_crc32.c. See the comments there.
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <http://7-zip.org/>
 *
 * This file has been put into the public domain.
 * You can do whatever you want with this file.
 */

#include "xz_private.h"

#ifndef STATIC_RW_DATA
#	define STATIC_RW_DATA static
#endif

STATIC_RW_DATA uint64_t xz_crc64_table[256];

XZ_EXTERN void xz_crc64_init(void)
{
	const uint64_t poly = 0xC96C5795D7870F42;

	uint32_t i;
	uint32_t j;
	uint64_t r;

	for (i = 0; i < 256; ++i) {
		r = i;
		for (j = 0; j < 8; ++j)
			r = (r >> 1) ^ (poly & ~((r & 1) - 1));

		xz_crc64_table[i] = r;
	}

	return;
}

XZ_EXTERN uint64_t xz_crc64(const uint8_t *buf, size_t size, uint64_t crc)
{
	crc = ~crc;

	while (size != 0) {
		crc = xz_crc64_table[*buf++ ^ (crc & 0xFF)] ^ (crc >> 8);
		--size;
	}

	return ~crc;
}
