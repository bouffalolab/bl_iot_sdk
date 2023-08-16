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
#include "xz.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static struct xz_dec *s;

int xz_uncompress_init(struct xz_buf *stream, uint8_t *sbuf, uint8_t *dbuf)
{
    xz_crc32_init();

    /*
     * Support up to 32 KiB dictionary. The actually needed memory
     * is allocated once the headers have been parsed.
     */
    s = xz_dec_init(XZ_DYNALLOC, 1 << 15);
    if (s == NULL) {
            return 1;
    }

    stream->in = sbuf;
    stream->in_pos = 0;
    stream->in_size = 0;
    stream->out = dbuf;
    stream->out_pos = 0;
    stream->out_size = 0;

	return 0;
}

int xz_uncompress_stream(struct xz_buf *stream, uint8_t *sbuf, uint32_t slen,
		uint8_t *dbuf, uint32_t dlen, uint32_t *decomp_len)
{
	int status;
	*decomp_len = 0;

	if (stream->in_pos == stream->in_size) {
		stream->in_size = slen;
	        stream->in_pos = 0;
	}

	if (stream->out_pos == stream->out_size) {
	        stream->out_size = dlen;
		stream->out_pos = 0;
	}

	status = xz_dec_run(s, stream);

	if ((status == XZ_STREAM_END) || (stream->out_pos == stream->out_size))
		*decomp_len = stream->out_pos;

	return status;
}

void xz_uncompress_end()
{
	xz_dec_end(s);
}
