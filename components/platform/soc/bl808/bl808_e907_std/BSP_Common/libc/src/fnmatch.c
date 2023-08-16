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
 * fnmatch.c
 *
 * Original implementation by Kay Sievers, modified by H. Peter Anvin.
 */

#include <fnmatch.h>

int fnmatch(const char *p, const char *s, int flags)
{
	if (flags & FNM_PATHNAME && *s == '/')
		return (*p != '/') || fnmatch(p+1, s+1, flags);
	if (flags & FNM_PERIOD && *s == '.')
		return (*p != '.') || fnmatch(p+1, s+1, flags);

	flags &= ~FNM_PERIOD;	/* Only applies at beginning */

	if (!(flags & FNM_NOESCAPE) && *p == '\\') {
		p++;
		return (*p != *s) || fnmatch(p+1, s+1, flags);
	}

	if (*s == '\0') {
		while (*p == '*')
			p++;
		return (*p != '\0');
	}

	switch (*p) {
	case '[':
		{
			int not_mark = 0;
			p++;
			if (*p == '!') {
				not_mark = 1;
				p++;
			}
			while ((*p != '\0') && (*p != ']')) {
				int match = 0;
				if (p[1] == '-') {
					if ((*s >= *p) && (*s <= p[2]))
						match = 1;
					p += 3;
				} else {
					match = (*p == *s);
					p++;
				}
				if (match ^ not_mark) {
					while ((*p != '\0') && (*p != ']'))
						p++;
					if (*p == ']')
						return fnmatch(p+1, s+1, flags);
				}
			}
		}
		break;
	case '*':
		if (fnmatch(p, s+1, flags))
			return fnmatch(p+1, s, flags);
		return 0;
	case '\0':
		if (*s == '\0') {
			return 0;
		}
		break;
	default:
		if ((*p == *s) || (*p == '?'))
			return fnmatch(p+1, s+1, flags);
		break;
	}
	return 1;
}
