#ifndef __BL_SEC_H__
#define __BL_SEC_H__
#include <stddef.h>
#include <stdint.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_sec_common.h>
#include <bl_sec_pka.h>
#include <bl_sec_aes.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern SemaphoreHandle_t g_bl_sec_sha_mutex;

int bl_sec_init(void);
int bl_sec_test(void);
int bl_pka_test(void);
int bl_sec_aes_enc(uint8_t *key, int keysize, uint8_t *input, uint8_t *output);
int bl_sec_aes_test(void);
uint32_t bl_sec_get_random_word(void);
void bl_rand_stream(uint8_t *buf, int len);
int bl_rand(void);
/*SHA Engine API*/
int bl_sec_sha_init();
int bl_sec_sha_test(void);
/* mutex used to guard SHA1/SHA512/MD5 */
int bl_sha_mutex_take();
int bl_sha_mutex_give();
/* SHA1, SHA224, SHA256 */
int bl_sha_init(bl_sha_ctx_t *ctx, const bl_sha_type_t type);
int bl_sha_clone(bl_sha_ctx_t *dst, const bl_sha_ctx_t *src);
int bl_sha_update(bl_sha_ctx_t *ctx, const uint8_t *input, uint32_t len);
int bl_sha_finish(bl_sha_ctx_t *ctx, uint8_t *hash);

int bl_sec_ccm_encrypt_and_tag(const uint8_t *key, unsigned int key_bytelen, size_t length, const unsigned char *iv, size_t iv_len, const unsigned char *add, size_t add_len,
                         const unsigned char *input, unsigned char *output, unsigned char *tag, size_t tag_len);
int bl_sec_ccm_auth_decrypt(const uint8_t *key, unsigned int key_bytelen, size_t length,const unsigned char *iv, size_t iv_len, const unsigned char *add,
							 size_t add_len, const unsigned char *input, unsigned char *output, const unsigned char *tag, size_t tag_len);
int bl_sec_aes_ecb_encrypt(const uint8_t *key, unsigned int key_bytelen, size_t length, const unsigned char *input, unsigned char *output);
int bl_sec_aes_ecb_decrypt(const uint8_t *key, unsigned int key_bytelen, size_t length, const unsigned char *input, unsigned char *output);

#if defined(__cplusplus)
}
#endif

#endif
