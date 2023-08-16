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
#include "hal_sec_aes.h"
#include "bl808_sec_eng.h"

static SEC_Eng_AES_Ctx aesCtx;

int sec_aes_init(sec_aes_handle_t *handle, sec_aes_type aes_tye, sec_aes_key_type key_type)
{
    handle->aes_type = aes_tye;
    handle->key_type = key_type;

    return 0;
}

static SEC_ENG_AES_Key_Type sec_aes_get_key_type(sec_aes_handle_t *handle)
{
    SEC_ENG_AES_Key_Type type = 0;

    switch (handle->key_type) {
        case SEC_AES_KEY_128:
            type = SEC_ENG_AES_KEY_128BITS;
            break;

        case SEC_AES_KEY_256:
            type = SEC_ENG_AES_KEY_256BITS;
            break;

        case SEC_AES_KEY_192:
            type = SEC_ENG_AES_KEY_192BITS;
            break;

        default:
            return SEC_ENG_AES_KEY_128BITS;
    }

    return type;
}

int sec_aes_setkey(sec_aes_handle_t *handle, const uint8_t *key, uint8_t key_len, const uint8_t *nonce, uint8_t dir)
{
    SEC_ENG_AES_Key_Type type = sec_aes_get_key_type(handle);

    switch (handle->aes_type) {
        case SEC_AES_CBC:
            Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);
            Sec_Eng_AES_Init(&aesCtx, SEC_ENG_AES_ID0, SEC_ENG_AES_CBC, type,
                             SEC_AES_DIR_ENCRYPT == dir ? SEC_ENG_AES_ENCRYPTION : SEC_ENG_AES_DECRYPTION);
            break;

        case SEC_AES_CTR:
            Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);
            Sec_Eng_AES_Init(&aesCtx, SEC_ENG_AES_ID0, SEC_ENG_AES_CTR, type,
                             SEC_AES_DIR_ENCRYPT == dir ? SEC_ENG_AES_ENCRYPTION : SEC_ENG_AES_DECRYPTION);
            break;

        case SEC_AES_XTS:
            Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);
            Sec_Eng_AES_Init(&aesCtx, SEC_ENG_AES_ID0, SEC_ENG_AES_XTS, type,
                             SEC_AES_DIR_ENCRYPT == dir ? SEC_ENG_AES_ENCRYPTION : SEC_ENG_AES_DECRYPTION);
            break;

        case SEC_AES_ECB:
            break;

        default:
            return -1;
    }

    /* if key len is 0, means key is from efuse and *key value is key_sel value */
    if (key_len == 0) {
        Sec_Eng_AES_Set_Key_IV_BE(SEC_ENG_AES_ID0, SEC_ENG_AES_KEY_HW, key, nonce);
    } else {
        Sec_Eng_AES_Set_Key_IV_BE(SEC_ENG_AES_ID0, SEC_ENG_AES_KEY_SW, key, nonce);
    }

    return 0;
}

int sec_aes_encrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out)
{
    if (SUCCESS != Sec_Eng_AES_Crypt(&aesCtx, SEC_ENG_AES_ID0, in, len, out)) {
        return -1;
    }

    return 0;
}

int sec_aes_decrypt(sec_aes_handle_t *handle, const uint8_t *in, uint32_t len, size_t offset, uint8_t *out)
{
    if (SUCCESS != Sec_Eng_AES_Crypt(&aesCtx, SEC_ENG_AES_ID0, in, len, out)) {
        return -1;
    }

    return 0;
}

int sec_aes_deinit(sec_aes_handle_t *handle)
{
    Sec_Eng_AES_Finish(SEC_ENG_AES_ID0);

    memset(handle, 0, sizeof(sec_aes_handle_t));

    return 0;
}
