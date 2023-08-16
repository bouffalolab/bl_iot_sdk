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
 * ctypes.c
 *
 * This is the array that defines <ctype.h> classes.
 * This assumes ISO 8859-1.
 */

#include <ctype.h>

const unsigned char __ctypes[257] = {
	0,			/* EOF */

	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl | __ctype_space,	/* BS */
	__ctype_cntrl | __ctype_space,	/* TAB */
	__ctype_cntrl | __ctype_space,	/* LF */
	__ctype_cntrl | __ctype_space,	/* VT */
	__ctype_cntrl | __ctype_space,	/* FF */
	__ctype_cntrl | __ctype_space,	/* CR */
	__ctype_cntrl,		/* control character */

	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */

	__ctype_print | __ctype_space,	/* space */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */

	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_digit | __ctype_xdigit,	/* digit */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */

	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper | __ctype_xdigit,	/* A-F */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */

	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_upper,	/* G-Z */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */

	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower | __ctype_xdigit,	/* a-f */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */

	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_lower,	/* g-z */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_cntrl,		/* control character */

	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */

	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */
	__ctype_cntrl,		/* control character */

	__ctype_print | __ctype_space,	/* NBSP */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */

	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_punct,	/* punctuation */

	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */

	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_upper,	/* upper accented */
	__ctype_print | __ctype_lower,	/* lower accented */

	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */

	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_punct,	/* punctuation */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
	__ctype_print | __ctype_lower,	/* lower accented */
};
