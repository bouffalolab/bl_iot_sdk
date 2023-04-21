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

#include <bl_sec.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <bl_sec_hw_common.h>

#define BL_SHA_ID SEC_ENG_SHA_ID0
#define SHA1_LEN 20
#define SHAx SEC_ENG_BASE
#define SEC_ENG_SHA_BUSY_TIMEOUT_COUNT  (100 * 160 * 1000)
#define PUT_UINT32_BE(n, b, i)               \
    {                                        \
        (b)[(i)] = (uint8_t)((n) >> 24);     \
        (b)[(i) + 1] = (uint8_t)((n) >> 16); \
        (b)[(i) + 2] = (uint8_t)((n) >> 8);  \
        (b)[(i) + 3] = (uint8_t)((n));       \
    }

/*
 * XXX WARNING:
 * sha_hw_init() and sha_hw_deinit() are tighty coupled with bl_sec_sha_init().
 * Make sure they are compatible.
 */
static void sha_hw_init(void)
{
    uint32_t t;

    bl_sha_mutex_take();
    Sec_Eng_SHA_Disable_Link(BL_SHA_ID);

    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
#ifdef BL616
    t = BL_SET_REG_BITS_VAL(t, SEC_ENG_SE_SHA_0_MODE_EXT, 0);
#endif
    t = BL_SET_REG_BITS_VAL(t, SEC_ENG_SE_SHA_0_MODE, SEC_ENG_SHA1);
    t = BL_SET_REG_BITS_VAL(t, SEC_ENG_SE_SHA_0_MSG_LEN, 2);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, t);

    Sec_Eng_SHA_Start(BL_SHA_ID);
}

static void sha_hw_deinit(void)
{
    uint32_t t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    t = BL_CLR_REG_BIT(t, SEC_ENG_SE_SHA_0_HASH_SEL);
    t = BL_CLR_REG_BIT(t, SEC_ENG_SE_SHA_0_EN);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, t);

    Sec_Eng_SHA_Enable_Link(BL_SHA_ID);
    bl_sha_mutex_give();
}

static inline int wait_done(void)
{
    size_t timeout_cnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;
    uint32_t t;

    do {
        t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeout_cnt--;

        if (timeout_cnt == 0) {
            return -1;
        }
    } while (BL_IS_REG_BIT_SET(t, SEC_ENG_SE_SHA_0_BUSY));

    return 0;
}

static inline void read_result_(uint32_t *result)
{
    uint32_t t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_0);
    *result++ = t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_1);
    *result++ = t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_2);
    *result++ = t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_3);
    *result++ = t;
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_4);
    *result = t;
}

static void pad_buf(void *sha_buf, size_t input_len)
{
    uint8_t *p = sha_buf + input_len;
    *p++ = 0x80;
    size_t pad_len = 128 - input_len - 1 - 4;
    memset(p, 0, pad_len);
    p += pad_len;
    size_t input_len_bits = input_len << 3;
    PUT_UINT32_BE(input_len_bits, p, 0);
}

static inline int sha1_(void *sha_buf, void *output)
{
    uint32_t t;

    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uint32_t)sha_buf);
    t = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    t = BL_SET_REG_BIT(t, SEC_ENG_SE_SHA_0_TRIG_1T);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, t);
    if (wait_done()) {
        return -1;
    }
    read_result_((uint32_t *)output);
    return 0;
}

static void F_(const char *password, const void *ssid, size_t ssid_len, size_t block_idx, void *output)
{
    size_t password_len = strlen(password);
    uint32_t sha_input_buf[(256 + SHA1_LEN) / 4];
    const size_t iterations = 4096;
    void *sha_buf = sha_input_buf;
    void *p;
    uint32_t *pw, *pw2;
    int i;

#ifdef BL616
    if (bl_sec_is_cache_addr(sha_input_buf)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)sha_input_buf, sizeof(sha_input_buf));
        sha_buf = bl_sec_get_no_cache_addr(sha_input_buf);
    }
#endif
    void *sha_buf2 = sha_buf + 128;
    void *sha_out = sha_buf + 256;

    memset(sha_buf, 0, sizeof(sha_input_buf));
    memcpy(sha_buf, password, password_len);
    memcpy(sha_buf2, password, password_len);
    pw = (uint32_t *)sha_buf;
    pw2 = (uint32_t *)sha_buf2;
    for (i = 0; i < 16; ++i) {
        *pw++ ^= 0x36363636;
        *pw2++ ^= 0x5c5c5c5c;
    }

    /* U1 = PRF(P, S || int(i)) */
    p = sha_buf + 64;
    memcpy(p, ssid, ssid_len);
    p += ssid_len + 3;
    ((uint8_t *)p)[0] = block_idx;

    void *cp1 = sha_buf + 64;
    void *cp2 = sha_buf2 + 64;
    pad_buf(sha_buf, 64 + ssid_len + 4);
    sha_hw_init();
    sha1_(sha_buf, cp2);
    pad_buf(sha_buf2, 64 + SHA1_LEN);
    sha1_(sha_buf2, sha_out);
    /* output = U1 */
    memcpy(output, sha_out, SHA1_LEN);

    pad_buf(sha_buf, 64 + SHA1_LEN);
    pw = (uint32_t *)sha_out;
    pw2 = (uint32_t *)output;
    for (i = 1; i < iterations; ++i) {
        /* Un = PRF(P, Un-1) */
        for (int j = 0; j < 5; ++j) {
            ((uint32_t *)cp1)[j] = pw[j];
        }
        sha1_(sha_buf, cp2);
        sha1_(sha_buf2, sha_out);

        /* output = output xor Un */
        for (int j = 0; j < 5; ++j) {
            pw2[j] ^= pw[j];
        }
    }

    sha_hw_deinit();
    memset(sha_buf, 0, sizeof(sha_input_buf));
}

int bl_sec_psk(const char *password, const void *ssid, size_t ssid_len, void *output)
{
    size_t password_len;
    uint32_t output_[32 / 4];

    if (!password || !ssid) {
        return -1;
    }

    password_len = strlen(password);
    if (!(password_len >= 8 && password_len <= 63 && ssid_len <= 32)) {
        return -1;
    }
    F_(password, ssid, ssid_len, 1, output_);
    memcpy(output, output_, SHA1_LEN);
    F_(password, ssid, ssid_len, 2, output_);
    memcpy(output + SHA1_LEN, output_, 12);

    return 0;
}

//
// Test cases
//
static bool tc_psk(void)
{
    const char tc_ssid[][33] = {
        "testme",
        "1",
        "bouffalolab",
        "0123456789ABCDEF0123456789ABCDEF",
    };
    const char tc_password[][64] = {
        "12345678",
        "password",
        "bouffalolab",
        "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDE",
    };
    const char tc_psk[][32] = {
        {0xEE, 0x9A, 0x63, 0x11, 0x6A, 0x1C, 0x9F, 0xF7, 0xCC, 0xA1, 0x7B, 0x98, 0x55, 0xEE, 0x82, 0x19, 0x67, 0x39, 0xA6, 0x24, 0x3F, 0x83, 0x0B, 0x28, 0x6A, 0x42, 0xAC, 0x53, 0xCE, 0xA0, 0x54, 0xD2, },
        {0xBF, 0xE5, 0x8E, 0x1C, 0x9A, 0x0D, 0xDB, 0xF5, 0x61, 0x08, 0xC5, 0xA2, 0x18, 0x68, 0xE8, 0x19, 0x7A, 0xC2, 0x31, 0x25, 0x3B, 0x97, 0x94, 0x15, 0x47, 0x15, 0xDF, 0xCE, 0x21, 0x95, 0x38, 0xCF, },
        {0x18, 0x72, 0xD2, 0xD4, 0xE0, 0xBD, 0xA7, 0x46, 0x27, 0xE1, 0x58, 0x1B, 0xE9, 0x76, 0x3C, 0x41, 0xFF, 0x8B, 0xDB, 0x79, 0x1A, 0xAA, 0xD4, 0xB5, 0x51, 0x87, 0x7C, 0x6F, 0x9C, 0x34, 0x9D, 0xE1, },
        {0x59, 0xE5, 0xA9, 0xFA, 0xED, 0xE6, 0xE1, 0xA0, 0x79, 0xC7, 0xA5, 0x45, 0x8C, 0xC8, 0x15, 0xC5, 0x72, 0xB6, 0xC5, 0x03, 0x9D, 0x7A, 0x94, 0x8F, 0x3C, 0x86, 0x74, 0x95, 0x31, 0xA0, 0x0A, 0xED, },
    };
    uint8_t psk[32];

    for (int i = 0; i < sizeof(tc_ssid) / sizeof(tc_ssid[0]); ++i) {
        memset(psk, 0, sizeof(psk));
        if (bl_sec_psk(tc_password[i], tc_ssid[i], strlen(tc_ssid[i]), psk)) {
            printf("%s: #%d error\r\n", __func__, i);
            return false;
        }

        if (memcmp(psk, tc_psk[i], 32)) {
            printf("%s: #%d failed\r\n", __func__, i);
            return false;
        }
    }
    return true;
}

int bl_sec_psk_test(void)
{
    if (tc_psk()) {
        printf("tc_psk passed\r\n");
    } else {
        printf("tc_psk failed\r\n");
    }
    return 0;
}
