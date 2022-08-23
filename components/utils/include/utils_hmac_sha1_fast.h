#ifndef __UTILS_HMAC_SHA1_FASH_H__
#define __UTILS_HMAC_SHA1_FASH_H__

void utils_hmac_sha1_fast(unsigned char ** ppText,
                    int * pTextLen,
                    int textNum,
                    unsigned char *key,
                    int key_len,
                    unsigned char *output,
                    int outputLen);

#endif
