/*
 * Copyright (c) 2016-2024 Bouffalolab.
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
#include "bl_sec_hw_common.h"
#include <bl_sec_aes.h>

#define AES_ID SEC_ENG_AES_ID0

int bl_sec_aes_init()
{
    Sec_Eng_AES_Enable_BE(AES_ID);
    return 0;
}

int bl_aes_acquire_hw()
{
    taskENTER_CRITICAL();
    return 0;
}

int bl_aes_release_hw()
{
    taskEXIT_CRITICAL();
    return 0;
}

int bl_aes_init(bl_sec_aes_t *aes)
{
    if (!aes) {
        return -1;
    }
    memset(aes, 0, sizeof(*aes));
    aes->link_cfg.aesIntClr = 1;
    aes->link_cfg.aesBlockMode = SEC_ENG_AES_ECB;

    return 0;
}

int bl_aes_set_key(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *key, size_t key_len)
{
    if (!(aes && key && (key_len == 16 || key_len == 24 || key_len == 32))) {
        return -1;
    }
    (void)op;

    aes->link_cfg.aesDecKeySel = SEC_ENG_AES_USE_NEW;
    SEC_ENG_AES_Key_Type key_type;
    if (key_len == 16) {
        key_type = SEC_ENG_AES_KEY_128BITS;
    } else if (key_len == 24) {
        key_type = SEC_ENG_AES_KEY_192BITS;
    } else {
        key_type = SEC_ENG_AES_KEY_256BITS;
    }
    aes->link_cfg.aesMode = key_type;
    memcpy(&aes->link_cfg.aesKey0, key, key_len);

    return 0;
}

int bl_aes_transform(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *input, uint8_t *output)
{
    const uint16_t n_blk = 1;
    if (!(aes && input && output)) {
        return -1;
    }

    aes->link_cfg.aesMsgLen = n_blk;
    if (op == BL_AES_ENCRYPT) {
        aes->link_cfg.aesDecEn = SEC_ENG_AES_ENCRYPTION;
    } else {
        aes->link_cfg.aesDecEn = SEC_ENG_AES_DECRYPTION;
    }

    Sec_Eng_AES_Enable_Link(AES_ID);
    Sec_Eng_AES_Link_Work(AES_ID, (uint32_t)&aes->link_cfg, input, n_blk << 4, output);
    Sec_Eng_AES_Disable_Link(AES_ID);

    return 0;
}
