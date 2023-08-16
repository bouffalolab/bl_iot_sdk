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
 * Derived from:
 * http://www.kernel.org/pub/linux/libs/klibc/
 */
/*
 * qsort.c
 *
 * This is actually combsort.  It's an O(n log n) algorithm with
 * simplicity/small code size being its main virtue.
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <wmlibc.h>

static __inline size_t newgap(size_t gap)
{
	gap = (gap * 10) / 13;
	if (gap == 9 || gap == 10)
		gap = 11;

	if (gap < 1)
		gap = 1;
	return gap;
}

void qsort(void *base, size_t nmemb, size_t size,
	   int (*compar) (const void *, const void *))
{
	size_t gap = nmemb;
	size_t i, j;
	char *p1, *p2;
	int swapped;

	if (!nmemb)
		return;

	do {
		gap = newgap(gap);
		swapped = 0;

		for (i = 0, p1 = (char*)base; i < nmemb - gap; i++, p1 += size) {
			j = i + gap;
			if (compar(p1, p2 = (char *)base + j * size) > 0) {
				memswap(p1, p2, size);
				swapped = 1;
			}
		}
	} while (gap > 1 || swapped);
}
