/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <blcrypto_suite/blcrypto_suite_aes.h>
#include "rijndael.h"

static uint8_t aes_key[16] = {
  0x2b, 0x7e, 0x15, 0x16,
  0x28, 0xae, 0xd2, 0xa6,
  0xab, 0xf7, 0x15, 0x88,
  0x09, 0xcf, 0x4f, 0x3c,
};

static const uint8_t aesSrcBuf_data[] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
};

static const uint8_t aesResult_entrypted_ecb_128[] =
{
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
    0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
};

uint8_t aesOut_Buf[16];

void rijndael_aes_test(void) {
    struct blcrypto_suite_aes *aes;
    rijndael_ctx rij_ctx;

    aes = blcrypto_suite_aes_init(0, AES_ECB);
    blcrypto_suite_aes_set_key(aes, aes_key, 128);
    blcrypto_suite_aes_encrypt(aes, aesSrcBuf_data, aesOut_Buf, 1);
    if (memcmp(aesOut_Buf, aesResult_entrypted_ecb_128, 16)) {
      printf("enc mis match\r\n");
    } else {
      printf("enc match\r\n");
    }

    blcrypto_suite_aes_decrypt(aes, aesResult_entrypted_ecb_128, aesOut_Buf, 1);

    if (memcmp(aesOut_Buf, aesSrcBuf_data, 16)) {
      printf("dec mis match\r\n");
    } else {
      printf("dec match\r\n");
    }

    blcrypto_suite_aes_deinit(&aes);

    rijndael_set_key(&rij_ctx, aes_key, 128, 1);
    rijndael_encrypt(&rij_ctx, (u8 *)aesSrcBuf_data, aesOut_Buf);
    if (memcmp(aesOut_Buf, aesResult_entrypted_ecb_128, 16)) {
      printf("enc mis match\r\n");
    } else {
      printf("enc match\r\n");
    }

    rijndael_set_key(&rij_ctx, aes_key, 128, 0);
    rijndael_decrypt(&rij_ctx, (u8*)aesResult_entrypted_ecb_128, aesOut_Buf);
    if (memcmp(aesOut_Buf, aesSrcBuf_data, 16)) {
      printf("dec mis match\r\n");
    } else {
      printf("dec match\r\n");
    }
}
