#include <blcrypto_suite/blcrypto_suite_top_config.h>
#include "blcrypto_suite/blcrypto_suite_aes.h"

#if USE_HWCRYPTO
#include <string.h>
#include <FreeRTOS.h>
#ifdef CFG_CHIP_BL602
#include <bl602_sec_eng.h>
#endif


#ifdef CFG_CHIP_BL602
#include <bl602_sec_eng.h>
#endif

#ifdef CFG_CHIP_BL808
#include <bl606p_sec_eng.h>
#endif

#include "bl_irq.h"

struct blcrypto_suite_aes_internal {
    int aes_id;
    SEC_Eng_AES_Link_Config_Type link_cfg;
};

struct blcrypto_suite_aes *blcrypto_suite_aes_init()
{
    struct blcrypto_suite_aes_internal *aes_internal;

    aes_internal = pvPortMalloc(sizeof(struct blcrypto_suite_aes_internal));
    if (aes_internal == NULL) {
        return NULL;
    }

    aes_internal->aes_id = 0;

    Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);

    memset(aes_internal, 0, sizeof(struct blcrypto_suite_aes_internal));
    aes_internal->link_cfg.aesIntClr = 1;
    aes_internal->link_cfg.aesIntSet = 0;

    aes_internal->link_cfg.aesBlockMode = SEC_ENG_AES_ECB;
    return (struct blcrypto_suite_aes *)aes_internal;
}

void blcrypto_suite_aes_deinit(struct blcrypto_suite_aes **aes)
{
    if (!(aes != NULL && *aes != NULL)) {
        return;
    }

    vPortFree(*aes);
    *aes = NULL;
}

int blcrypto_suite_aes_set_key(struct blcrypto_suite_aes *aes, enum crypto_aes_mode mode, const uint8_t *key, int bits)
{
    if (!aes) {
        return -1;
    }
    struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

    (void)mode;
    aes_internal->link_cfg.aesDecKeySel = SEC_ENG_AES_USE_NEW;

    switch (bits) {
        case 128:
            aes_internal->link_cfg.aesMode = SEC_ENG_AES_KEY_128BITS;
            memcpy(&aes_internal->link_cfg.aesKey0, key, 16);
            break;

        case 192:
            aes_internal->link_cfg.aesMode = SEC_ENG_AES_KEY_192BITS;
            memcpy(&aes_internal->link_cfg.aesKey0, key, 24);
            break;

        case 256:
            aes_internal->link_cfg.aesMode = SEC_ENG_AES_KEY_256BITS;
            memcpy(&aes_internal->link_cfg.aesKey0, key, 32);
            break;

        default:
            return -1;
    }
    return 0;
}

int blcrypto_suite_aes_crypt(struct blcrypto_suite_aes *aes, enum crypto_aes_mode mode, const uint8_t *in, uint8_t *out)
{
    if (!aes) {
        return -1;
    }
    struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

    const uint16_t n_blk = 1;
    aes_internal->link_cfg.aesMsgLen = n_blk;
    if (mode == AES_ENC) {
        aes_internal->link_cfg.aesDecEn = SEC_ENG_AES_ENCRYPTION;
    } else {
        aes_internal->link_cfg.aesDecEn = SEC_ENG_AES_DECRYPTION;
    }

    Sec_Eng_AES_Enable_Link(aes_internal->aes_id);
    Sec_Eng_AES_Link_Work(aes_internal->aes_id, (uint32_t)&aes_internal->link_cfg, in, n_blk << 4, out);
    Sec_Eng_AES_Disable_Link(aes_internal->aes_id);

    return 0;
}
#else
#include <FreeRTOS.h>
#include <mbedtls/aes.h>

struct blcrypto_suite_aes_internal {
    mbedtls_aes_context aes;
};

// only ECB is supported
struct blcrypto_suite_aes *blcrypto_suite_aes_init()
{
    struct blcrypto_suite_aes_internal *aes_internal;

    aes_internal = pvPortMalloc(sizeof(struct blcrypto_suite_aes_internal));
    if (aes_internal == NULL) {
        return NULL;
    }

    mbedtls_aes_init(&aes_internal->aes);
    return (struct blcrypto_suite_aes *)aes_internal;
}

void blcrypto_suite_aes_deinit(struct blcrypto_suite_aes **aes)
{
    if (!(aes != NULL && *aes != NULL)) {
        return;
    }

    vPortFree(*aes);
    *aes = NULL;
}

int blcrypto_suite_aes_set_key(struct blcrypto_suite_aes *aes, enum crypto_aes_mode mode, const uint8_t *key, int bits)
{
    if (!aes) {
        return -1;
    }
    struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

    if (mode == AES_ENC) {
        mbedtls_aes_setkey_enc(&aes_internal->aes, key, bits);
    } else {
        mbedtls_aes_setkey_dec(&aes_internal->aes, key, bits);
    }
    return 0;
}

int blcrypto_suite_aes_crypt(struct blcrypto_suite_aes *aes, enum crypto_aes_mode mode, const uint8_t *in, uint8_t *out)
{
    if (!aes) {
        return -1;
    }
    struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

    if (mode == AES_ENC) {
        mbedtls_aes_crypt_ecb(&aes_internal->aes, MBEDTLS_AES_ENCRYPT, in, out);
    } else {
        mbedtls_aes_crypt_ecb(&aes_internal->aes, MBEDTLS_AES_DECRYPT, in, out);
    }
    return 0;
}
#endif
