#include <stdint.h>
#include <string.h>

#include <bl_sec.h>
#include <utils_hmac_sha1_fast.h>


void utils_hmac_sha1_fast(unsigned char ** ppText,
                    int * pTextLen,
                    int textNum,
                    unsigned char *key,
                    int key_len,
                    unsigned char *output,
                    int outputLen)
{
    uint64_t pBuf[(64 + 20) / 8 + 1]; /*BIG stack*/
    bl_sha_ctx_t sha_ctx;
    unsigned char *k_pad; /* padding - key XORd with i/opad */
    unsigned char *digest;
    int i;

    /* k_pad start at a UINT32 boundary */
    k_pad = (unsigned char *)pBuf;
    digest = k_pad + 64;

    /* if key is longer than 64 bytes reset it to key=SHA1(key) */
    if (key_len > 64)
    {
        bl_sha_init(&sha_ctx, BL_SHA1);
        bl_sha_update(&sha_ctx, key, key_len);
        bl_sha_finish(&sha_ctx, key);

        key_len = 20;
    }

    /*
     * the HMAC_SHA1 transform looks like:
     *
     * SHA1(K XOR opad, SHA1(K XOR ipad, text))
     *
     * where K is an n byte key
     * ipad is the byte 0x36 repeated 64 times
     * opad is the byte 0x5c repeated 64 times
     * and text is the data being protected
     */

    /* perform inner SHA1*/
    /* start out by storing key in pads */
    memset(k_pad, 0, 64);
    memcpy(k_pad, key, key_len);

    /* XOR key with ipad and opad values */
    for (i = 0; i < 8; i++)
    {
        ((uint64_t *)k_pad)[i] ^= 0x3636363636363636;
    }

    bl_sha_init(&sha_ctx, BL_SHA1); /* init context for 1st pass */
    bl_sha_update(&sha_ctx, k_pad, 64); /* start with inner pad */
    for (i = 0; i < textNum; i++)
    {
        /* then text of datagram */
        bl_sha_update(&sha_ctx, ppText[i], pTextLen[i]);
    }

    bl_sha_finish(&sha_ctx, digest); /* finish up 1st pass */

    /* perform outer SHA1 */
    /* start out by storing key in pads */
    memset(k_pad, 0, 64);
    memcpy(k_pad, key, key_len);

    /* XOR key with ipad and opad values */
    for (i = 0; i < 8; i++)
    {
        ((uint64_t *)k_pad)[i] ^= 0x5c5c5c5c5c5c5c5c;
    }

    bl_sha_init(&sha_ctx, BL_SHA1); /* init context for 2nd pass */
    bl_sha_update(&sha_ctx, k_pad, 64); /* start with outer pad */
    bl_sha_update(&sha_ctx, digest, 20); /* then results of 1st hash */
    bl_sha_finish(&sha_ctx, digest); /* finish up 2nd pass */
    memcpy(output, digest, outputLen);
}
