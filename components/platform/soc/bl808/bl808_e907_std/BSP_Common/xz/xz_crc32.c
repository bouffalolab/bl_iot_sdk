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
 * CRC32 using the polynomial from IEEE-802.3
 *
 * Authors: Lasse Collin <lasse.collin@tukaani.org>
 *          Igor Pavlov <http://7-zip.org/>
 *
 * This file has been put into the public domain.
 * You can do whatever you want with this file.
 */

/*
 * This is not the fastest implementation, but it is pretty compact.
 * The fastest versions of xz_crc32() on modern CPUs without hardware
 * accelerated CRC instruction are 3-5 times as fast as this version,
 * but they are bigger and use more memory for the lookup table.
 */

#include "xz_private.h"

/*
 * STATIC_RW_DATA is used in the pre-boot environment on some architectures.
 * See <linux/decompress/mm.h> for details.
 */
#ifndef STATIC_RW_DATA
#	define STATIC_RW_DATA static
#endif

//STATIC_RW_DATA uint32_t xz_crc32_table[256];
extern const uint32_t crc32Tab[256];

XZ_EXTERN void xz_crc32_init(void)
{
#if 0
	const uint32_t poly = 0xEDB88320;

	uint32_t i;
	uint32_t j;
	uint32_t r;

	for (i = 0; i < 256; ++i) {
		r = i;
		for (j = 0; j < 8; ++j)
			r = (r >> 1) ^ (poly & ~((r & 1) - 1));

		xz_crc32_table[i] = r;
	}
#endif
	return;
}

XZ_EXTERN uint32_t xz_crc32(const uint8_t *buf, size_t size, uint32_t crc)
{
	crc = ~crc;

	while (size != 0) {
		crc = crc32Tab[*buf++ ^ (crc & 0xFF)] ^ (crc >> 8);
		--size;
	}

	return ~crc;
}
