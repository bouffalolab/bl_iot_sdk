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
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_irq.h>
#include <bl_sec.h>
#include "bl_sec_hw_common.h"

#include <blog.h>

#define BL_SHA_ID SEC_ENG_SHA_ID0 // this is the only valid value

#ifdef BL602
static bl_SEC_Eng_SHA_Link_Config_Type working_link_cfg __attribute__((section(".wifi_ram")));
#else
#error "No support for this chip"
#endif

int bl_sec_sha_init()
{
    Sec_Eng_SHA_Enable_Link(BL_SHA_ID);

    return 0;
}

int bl_sha_mutex_take()
{
    taskENTER_CRITICAL();
    return 0;
}

int bl_sha_mutex_give()
{
    taskEXIT_CRITICAL();
    return 0;
}

static int bl_to_drv_type(bl_sha_type_t type)
{
    const uint8_t map[] = {
        [BL_SHA1] = SEC_ENG_SHA1,
        [BL_SHA224] = SEC_ENG_SHA224,
        [BL_SHA256] = SEC_ENG_SHA256,
#ifdef MD5_CAPABLE
        [BL_MD5] = SEC_ENG_MD5,
#endif
#ifdef SHA512_CAPABLE
        [BL_SHA384] = SEC_ENG_SHA384,
        [BL_SHA512] = SEC_ENG_SHA512,
#endif
    };
    if (type < sizeof(map)) {
        return map[type];
    }
    return -1;
}


/*
 * SHA1
 */
int bl_sha_init(bl_sha_ctx_t *ctx, const bl_sha_type_t type)
{
    if (!(type == BL_SHA1 || type == BL_SHA224 || type == BL_SHA256)) {
        return -1;
    }
    const SEC_ENG_SHA_Type sha_type = (SEC_ENG_SHA_Type)bl_to_drv_type(type);

    memset(ctx, 0, sizeof(*ctx));
    ctx->type = type;
    SEC_Eng_SHA_Link_Config_Type *lc = (SEC_Eng_SHA_Link_Config_Type *)&ctx->link_cfg;
    lc->shaMode = sha_type;
    lc->shaIntSet = 1;
    lc->shaIntClr = 1;
    Sec_Eng_SHA256_Link_Init((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, (uint32_t)&working_link_cfg, ctx->tmp, ctx->pad);
    return 0;
}

int bl_sha_clone(bl_sha_ctx_t *dst, const bl_sha_ctx_t *src)
{
    if (!(dst && src)) {
        return -1;
    }

    *dst = *src;
    dst->ctx.shaBuf = dst->tmp;
    dst->ctx.shaPadding = dst->pad;
    return 0;
}

int bl_sha_update(bl_sha_ctx_t *ctx, const uint8_t *input, uint32_t len)
{
    ARCH_MemCpy_Fast(&working_link_cfg, &ctx->link_cfg, sizeof(working_link_cfg));
    Sec_Eng_SHA256_Link_Update((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, input, len);
    ARCH_MemCpy_Fast(&ctx->link_cfg, &working_link_cfg, sizeof(working_link_cfg));
    return 0;
}

int bl_sha_finish(bl_sha_ctx_t *ctx, uint8_t *hash)
{
    ARCH_MemCpy_Fast(&working_link_cfg, &ctx->link_cfg, sizeof(working_link_cfg));
    Sec_Eng_SHA256_Link_Finish((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, hash);
    return 0;
}


#include <stdlib.h>
/*
 * Test cases
 */
static const char tc_hash_input[] = "The quick brown fox jumps over the lazy dog";
bool tc_sha1()
{
    int i;
    const bl_sha_type_t types[] = {BL_SHA1, BL_SHA224, BL_SHA256};
    uint8_t result[32];
    const uint8_t expected_results[][32] = {
        {0x2f, 0xd4, 0xe1, 0xc6, 0x7a, 0x2d, 0x28, 0xfc, 0xed, 0x84, 0x9e, 0xe1, 0xbb, 0x76, 0xe7, 0x39, 0x1b, 0x93, 0xeb, 0x12, },
        {0x73, 0x0e, 0x10, 0x9b, 0xd7, 0xa8, 0xa3, 0x2b, 0x1c, 0xb9, 0xd9, 0xa0, 0x9a, 0xa2, 0x32, 0x5d, 0x24, 0x30, 0x58, 0x7d, 0xdb, 0xc0, 0xc3, 0x8b, 0xad, 0x91, 0x15, 0x25, },
        {0xd7, 0xa8, 0xfb, 0xb3, 0x07, 0xd7, 0x80, 0x94, 0x69, 0xca, 0x9a, 0xbc, 0xb0, 0x08, 0x2e, 0x4f, 0x8d, 0x56, 0x51, 0xe4, 0x6d, 0x3c, 0xdb, 0x76, 0x2d, 0x02, 0xd0, 0xbf, 0x37, 0xc9, 0xe5, 0x92, },
    };

    while (1) {
        uint8_t *in_buf;
        bl_sha_ctx_t *ctx;

        for (int i = 0; i < 5; ++i) {
            in_buf = malloc(64);
            ctx = malloc(sizeof(*ctx));
            if (!in_buf || !ctx) {
                printf("Over!\r\n");
                while (1) {
                }
            }
        }
        printf("Test addr %p\r\n", ctx);
        for (int j = 0; j < 10 * 1000; ++j) {
            for (i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
                size_t len = sizeof(tc_hash_input) - 1;
                memcpy(in_buf, tc_hash_input, len);
                bl_sha_init(ctx, types[i]);
                bl_sha_update(ctx, in_buf, len);
                memset(result, 0, sizeof(result));
                bl_sha_finish(ctx, result);
                if (memcmp(result, expected_results[i], 32) != 0) {
                    printf("SHA1 #%d failed\r\n", i);
                    return false;
                }
            }
        }
    }
    return true;
}

#define MD(tc) {tc, #tc}
static struct {
    bool (*tc_fun)(void);
    const char *desc;
} tc[] = {
    MD(tc_sha1),
};

int bl_sec_sha_test(void)
{
    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); ++i) {
        printf("Running test case %s\r\n", tc[i].desc);
        if (tc[i].tc_fun()) {
            printf("\t\tPassed\r\n");
        } else {
            printf("\t\tFailed\r\n");
        }
    }
    return 0;
}
