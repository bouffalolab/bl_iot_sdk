#ifndef BLCRYPTO_SUITE_AES_H
#define BLCRYPTO_SUITE_AES_H

#include <stdint.h>

struct blcrypto_suite_aes {
  int aes_id;
};

enum crypto_aes_mode {
  AES_ECB,
  AES_CTR,
  AES_CBC
};

struct blcrypto_suite_aes *blcrypto_suite_aes_init(int aes_id, enum crypto_aes_mode mode);
int blcrypto_suite_aes_set_key(struct blcrypto_suite_aes *aes, const uint8_t *key, int bits);
int blcrypto_suite_aes_encrypt(struct blcrypto_suite_aes *aes, const uint8_t *in, uint8_t *out, unsigned int nblk);
int blcrypto_suite_aes_decrypt(struct blcrypto_suite_aes *aes, const uint8_t *in, uint8_t *out, unsigned int nblk);
void blcrypto_suite_aes_deinit(struct blcrypto_suite_aes **aes);

#endif /* end of include guard: BLCRYPTO_SUITE_HACC_H */
