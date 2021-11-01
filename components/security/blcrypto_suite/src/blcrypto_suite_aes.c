#include <assert.h>
#include <string.h>
#include "bl_irq.h"
#include "blcrypto_suite/blcrypto_suite_aes.h"
#include <bl602_sec_eng.h>
#include <FreeRTOS.h>

extern void bl_sec_aes_IRQHandler(void);

struct blcrypto_suite_aes_internal {
  struct blcrypto_suite_aes aes;
  SEC_Eng_AES_Link_Config_Type link_cfg;
};

struct blcrypto_suite_aes *blcrypto_suite_aes_init(int aes_id, enum crypto_aes_mode mode) {
  struct blcrypto_suite_aes_internal *aes_internal;

  aes_internal = pvPortMalloc(sizeof(struct blcrypto_suite_aes_internal));
  if (aes_internal == NULL) {
    return NULL;
  }

  aes_internal->aes.aes_id = aes_id;

  //bl_irq_register(SEC_AES_IRQn, bl_sec_aes_IRQHandler);
  //bl_irq_enable(SEC_AES_IRQn);

  Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);

  memset(aes_internal, 0, sizeof(struct blcrypto_suite_aes_internal));
  aes_internal->link_cfg.aesIntClr = 1;
  aes_internal->link_cfg.aesIntSet = 0;

  switch (mode) {
    case AES_ECB:
      aes_internal->link_cfg.aesBlockMode = SEC_ENG_AES_ECB;
      break;

    case AES_CTR:
      aes_internal->link_cfg.aesBlockMode = SEC_ENG_AES_CTR;
      break;

    case AES_CBC:
      aes_internal->link_cfg.aesBlockMode = SEC_ENG_AES_CBC;
      break;

    default:
      vPortFree(aes_internal);
      return NULL;
  }
  return (struct blcrypto_suite_aes *)aes_internal;
}

void blcrypto_suite_aes_deinit(struct blcrypto_suite_aes **aes) {
  assert(aes != NULL && *aes != NULL);

  vPortFree(*aes);
  *aes = NULL;
}

int blcrypto_suite_aes_set_key(struct blcrypto_suite_aes *aes, const uint8_t *key, int bits) {
  assert(aes != NULL);
  struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

  aes_internal->link_cfg.aesDecKeySel = SEC_ENG_AES_USE_NEW;

  switch(bits) {
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

int blcrypto_suite_aes_encrypt(struct blcrypto_suite_aes *aes, const uint8_t *in, uint8_t *out, unsigned int nblk) {
  assert(aes != NULL);
  struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

  /* XXX */
  assert(nblk < 65536 && nblk != 0);

  aes_internal->link_cfg.aesMsgLen = nblk;
  aes_internal->link_cfg.aesDecEn = SEC_ENG_AES_ENCRYPTION;

  /* check overlap: S2 <= E1 && S1 <= E2 */
  assert(!(((uintptr_t)out < (uintptr_t)in + (nblk << 4)) &&
    ((uintptr_t)in < (uintptr_t)out + (nblk << 4))));

  Sec_Eng_AES_Enable_Link(aes_internal->aes.aes_id);
  Sec_Eng_AES_Link_Work(aes_internal->aes.aes_id, (uint32_t)&aes_internal->link_cfg, in, nblk << 4, out);
  Sec_Eng_AES_Disable_Link(aes_internal->aes.aes_id);

  return 0;
}

int blcrypto_suite_aes_decrypt(struct blcrypto_suite_aes *aes, const uint8_t *in, uint8_t *out, unsigned int nblk) {
  assert(aes != NULL);
  struct blcrypto_suite_aes_internal *aes_internal = (struct blcrypto_suite_aes_internal *)aes;

  /* XXX */
  assert(nblk < 65536 && nblk != 0);

  aes_internal->link_cfg.aesMsgLen = nblk;
  aes_internal->link_cfg.aesDecEn = SEC_ENG_AES_DECRYPTION;

  /* check overlap: S2 <= E1 && S1 <= E2 */
  assert(!(((uintptr_t)out < (uintptr_t)in + (nblk << 4)) &&
    ((uintptr_t)in < (uintptr_t)out + (nblk << 4))));

  Sec_Eng_AES_Enable_Link(aes_internal->aes.aes_id);
  Sec_Eng_AES_Link_Work(aes_internal->aes.aes_id, (uint32_t)&aes_internal->link_cfg, in, nblk << 4, out);

  Sec_Eng_AES_Disable_Link(aes_internal->aes.aes_id);

  return 0;
}

