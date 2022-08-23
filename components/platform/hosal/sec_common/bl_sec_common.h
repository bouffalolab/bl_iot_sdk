#pragma once

#include <stdint.h>

typedef enum {
    BL_SHA1,
    BL_SHA224,
    BL_SHA256,
    BL_MD5,
    BL_SHA384,
    BL_SHA512,
} bl_sha_type_t;

/*
 * SHA1
 */
/* copied SEC_Eng_SHA256_Ctx from stddrv */
typedef struct {
    uint32_t total[2];
    uint32_t  *shaBuf;
    uint32_t  *shaPadding;
    uint32_t linkAddr;
} bl_SEC_Eng_SHA256_Link_Ctx;

typedef struct {
    uint32_t :2;                            /*!< [1:0]reserved */
    uint32_t shaMode:3;                     /*!< [4:2]Sha-256/sha-224/sha-1/sha-1 */
    uint32_t :1;                            /*!< [5]reserved */
    uint32_t shaHashSel:1;                  /*!< [6]New hash or accumulate last hash */
    uint32_t :2;                            /*!< [8:7]reserved */
    uint32_t shaIntClr:1;                   /*!< [9]Clear interrupt */
    uint32_t shaIntSet:1;                   /*!< [10]Set interrupt */
    uint32_t :5;                            /*!< [15:11]reserved */
    uint32_t shaMsgLen:16;                  /*!< [31:16]Number of 512-bit block */
    uint32_t shaSrcAddr;                     /*!< Message source address */
    uint32_t result[8];                      /*!< Result of SHA */
} __attribute__ ((aligned(4))) bl_SEC_Eng_SHA_Link_Config_Type;

typedef struct bl_sha_ctx {
    bl_sha_type_t type;
    bl_SEC_Eng_SHA256_Link_Ctx ctx;
    bl_SEC_Eng_SHA_Link_Config_Type link_cfg;
    uint32_t tmp[16];
    uint32_t pad[16];
} bl_sha_ctx_t;
