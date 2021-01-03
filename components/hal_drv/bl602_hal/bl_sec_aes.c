/*
 * Copyright (c) 2020 Bouffalolab.
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
#include <stdio.h>
#include <string.h>

#include <sec_eng_reg.h>
#include <bl602_sec_eng.h>

#include "bl_irq.h"
#include "bl_sec.h"

#include <blog.h>
#define USER_UNUSED(a) ((void)(a))

int bl_sec_aes_enc(uint8_t *key, int keysize, uint8_t *input, uint8_t *output)
{
    return 0;
}

static void Aes_Compare_Data(const uint8_t *expected, uint8_t *input, uint32_t len)
{
    int i = 0, is_failed = 0;

    for (i = 0; i < len; i++) {
        if (input[i] != expected[i]) {
            is_failed = 1;
            blog_info("%s[%02d], %02x %02x\r\n",
                input[i] ==expected[i] ? "S" : "F",
                i,
                input[i],
                expected[i]
            );
        }
    }
    if (is_failed) {
        blog_error("====== Failed %lu Bytes======\r\n", len);
    } else {
        blog_info("====== Success %lu Bytes=====\r\n", len);
    }
}

static void _dump_iv_status(SEC_Eng_AES_Link_Config_Type *linkCfg)
{
    int i;
    uint8_t *iv;

    USER_UNUSED(iv);
    USER_UNUSED(i);

    for (i = 0, iv = (uint8_t*)&(linkCfg->aesIV0); i < 16; i++) {
        blog_print("%02x", iv[i]);
    }
    blog_print("\r\n");
}

static const uint8_t aesSrcBuf_data[] =
{
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
};

void Sec_Eng_AES_Link_Case_CBC_128(SEC_ENG_AES_ID_Type aesId)
{
    uint8_t aesDstBuf[32];
    static const uint8_t aesResult_entrypted_cbc_128[] =
    {
        0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
        0x4c, 0xbb, 0xc8, 0x58, 0x75, 0x6b, 0x35, 0x81, 0x25, 0x52, 0x9e, 0x96, 0x98, 0xa3, 0x8f, 0x44,
        0x9f, 0x6f, 0x07, 0x96, 0xee, 0x3e, 0x47, 0xb0, 0xd8, 0x7c, 0x76, 0x1b, 0x20, 0x52, 0x7f, 0x78,
        0x07, 0x01, 0x34, 0x08, 0x5f, 0x02, 0x75, 0x17, 0x55, 0xef, 0xca, 0x3b, 0x4c, 0xdc, 0x7d, 0x62,
    };


    SEC_Eng_AES_Link_Config_Type linkCfg = {
        .aesMode = SEC_ENG_AES_KEY_128BITS,                            /* 128-bit key mode select */
        .aesDecEn = SEC_ENG_AES_ENCRYPTION,                            /* Encode */
        .aesDecKeySel = SEC_ENG_AES_USE_NEW,                           /* Use new key */
        .aesIntClr = 0,                                                /* Not clear intrrupt */
        .aesIntSet = 1,                                                /* Not set interrupt */
        .aesBlockMode = SEC_ENG_AES_CBC,                               /* ECB mode select */
        .aesIVSel = SEC_ENG_AES_USE_NEW,                               /* Use new iv */
        .aesMsgLen = 1,                                                /* Number of 128-bit block */
        .aesSrcAddr = 0,                                               /* Message source address */
        .aesDstAddr = 0,                                               /* Message destination address */
        .aesIV0 = 0x03020100,                                          /* Big endian initial vector(MSB) */
        .aesIV1 = 0x07060504,                                          /* Big endian initial vector */
        .aesIV2 = 0x0b0a0908,                                          /* Big endian initial vector */
        .aesIV3 = 0x0f0e0d0c,                                          /* Big endian initial vector(LSB)(CTR mode:counter initial value) */
        .aesKey0 = 0x16157e2b,                                         /* Big endian aes key(aes-128/256 key MSB) */
        .aesKey1 = 0xa6d2ae28,                                         /* Big endian aes key */
        .aesKey2 = 0x8815f7ab,                                         /* Big endian aes key */
        .aesKey3 = 0x3c4fcf09,                                         /* Big endian aes key(aes-128 key LSB) */
        .aesKey4 = 0,                                                  /* Big endian aes key */
        .aesKey5 = 0,                                                  /* Big endian aes key */
        .aesKey6 = 0,                                                  /* Big endian aes key */
        .aesKey7 = 0                                                   /* Big endian aes key(aes-256 key LSB) */
    };

    Sec_Eng_AES_Enable_Link(aesId);

    puts("[CBC] AES-128-CBC case...\r\n");

    blog_info("[CBC] IV Status Initial, %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);
    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]), 32, aesDstBuf);
    Aes_Compare_Data(aesResult_entrypted_cbc_128, (uint8_t*)linkCfg.aesDstAddr, 32);
    blog_info("[CBC] IV Status After, %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 32, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_cbc_128[0]) + 32, (uint8_t*)linkCfg.aesDstAddr, 16);
    blog_info("[CBC] IV Status After %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 48, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_cbc_128[0]) + 48, (uint8_t*)linkCfg.aesDstAddr, 16);
    blog_info("[CBC] IV Status After, %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Disable_Link(aesId);
}

void Sec_Eng_AES_Link_Case_CTR_128(SEC_ENG_AES_ID_Type aesId)
{
    uint8_t aesDstBuf[32];
    static const uint8_t aesResult_entrypted_ctr_128[] =
    {
        0x87, 0x4d, 0x61, 0x91, 0xb6, 0x20, 0xe3, 0x26, 0x1b, 0xef, 0x68, 0x64, 0x99, 0x0d, 0xb6, 0xce,
        0x5d, 0xea, 0xc2, 0xde, 0x49, 0x33, 0xce, 0xf5, 0xf1, 0x9d, 0x09, 0xc6, 0x8f, 0xc3, 0x64, 0x84,
        0x01, 0xed, 0x7d, 0x9a, 0x56, 0xc9, 0xa8, 0xd9, 0x57, 0x89, 0xb6, 0x0a, 0x64, 0x29, 0x7b, 0x6e,
        0x83, 0x5d, 0x87, 0x7d, 0xde, 0xb1, 0x07, 0x50, 0x3d, 0x37, 0x4f, 0xca, 0x66, 0xff, 0xbc, 0xd4,
    };
    SEC_Eng_AES_Link_Config_Type linkCfg = {
        .aesMode = SEC_ENG_AES_KEY_128BITS,                            /* 128-bit key mode select */
        .aesDecEn = SEC_ENG_AES_ENCRYPTION,                            /* Encode */
        .aesDecKeySel = SEC_ENG_AES_USE_NEW,                           /* Use new key */
        .aesIntClr = 0,                                                /* Not clear intrrupt */
        .aesIntSet = 1,                                                /* Not set interrupt */
        .aesBlockMode = SEC_ENG_AES_CTR,                               /* CTR mode select */
        .aesIVSel = SEC_ENG_AES_USE_NEW,                               /* Use new iv */
        .aesMsgLen = 1,                                                /* Number of 128-bit block */
        .aesSrcAddr = 0,                                               /* Message source address */
        .aesDstAddr = 0,                                               /* Message destination address */
        .aesIV0 = 0xf3f2f1f0,                                          /* Big endian initial vector(MSB) */
        .aesIV1 = 0xf7f6f5f4,                                          /* Big endian initial vector */
        .aesIV2 = 0xfbfaf9f8,                                          /* Big endian initial vector */
        .aesIV3 = 0xfffefdfc,                                          /* Big endian initial vector(LSB)(CTR mode:counter initial value) */
        .aesKey0 = 0x16157e2b,                                         /* Big endian aes key(aes-128/256 key MSB) */
        .aesKey1 = 0xa6d2ae28,                                         /* Big endian aes key */
        .aesKey2 = 0x8815f7ab,                                         /* Big endian aes key */
        .aesKey3 = 0x3c4fcf09,                                         /* Big endian aes key(aes-128 key LSB) */
        .aesKey4 = 0,                                                  /* Big endian aes key */
        .aesKey5 = 0,                                                  /* Big endian aes key */
        .aesKey6 = 0,                                                  /* Big endian aes key */
        .aesKey7 = 0                                                   /* Big endian aes key(aes-256 key LSB) */
    };

    Sec_Eng_AES_Enable_Link(aesId);

    puts("[CTR] AES-128-CTR case...\r\n");
    blog_info("[CTR] IV Status Initial, %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]), 32, aesDstBuf);
    Aes_Compare_Data(aesResult_entrypted_ctr_128, (uint8_t*)linkCfg.aesDstAddr, 32);

    blog_info("[CTR] IV Status After %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 32, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_ctr_128[0]) + 32, (uint8_t*)linkCfg.aesDstAddr, 16);
    blog_info("[CTR] IV Status After %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 48, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_ctr_128[0]) + 48, (uint8_t*)linkCfg.aesDstAddr, 16);
    blog_info("[CTR] IV Status After, %08lx\r\n", linkCfg.aesSrcAddr);
    _dump_iv_status(&linkCfg);

    Sec_Eng_AES_Disable_Link(aesId);
}

void Sec_Eng_AES_Link_Case_ECB_128(SEC_ENG_AES_ID_Type aesId)
{
    uint8_t aesDstBuf[32];
    static const uint8_t aesResult_entrypted_ecb_128[] =
    {
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97,
    };
    SEC_Eng_AES_Link_Config_Type linkCfg = {
        .aesMode = SEC_ENG_AES_KEY_128BITS,                            /* 128-bit key mode select */
        .aesDecEn = SEC_ENG_AES_ENCRYPTION,                            /* Encode */
        .aesDecKeySel = SEC_ENG_AES_USE_NEW,                           /* Use new key */
        .aesIntClr = 0,                                                /* Not clear intrrupt */
        .aesIntSet = 1,                                                /* Not set interrupt */
        .aesBlockMode = SEC_ENG_AES_ECB,                               /* CTR mode select */
        .aesIVSel = SEC_ENG_AES_USE_NEW,                               /* Use new iv */
        .aesMsgLen = 1,                                                /* Number of 128-bit block */
        .aesSrcAddr = 0,                                               /* Message source address */
        .aesDstAddr = 0,                                               /* Message destination address */
        .aesIV0 = 0xf3f2f1f0,                                          /* Big endian initial vector(MSB) */
        .aesIV1 = 0xf7f6f5f4,                                          /* Big endian initial vector */
        .aesIV2 = 0xfbfaf9f8,                                          /* Big endian initial vector */
        .aesIV3 = 0xfffefdfc,                                          /* Big endian initial vector(LSB)(CTR mode:counter initial value) */
        .aesKey0 = 0x16157e2b,                                         /* Big endian aes key(aes-128/256 key MSB) */
        .aesKey1 = 0xa6d2ae28,                                         /* Big endian aes key */
        .aesKey2 = 0x8815f7ab,                                         /* Big endian aes key */
        .aesKey3 = 0x3c4fcf09,                                         /* Big endian aes key(aes-128 key LSB) */
        .aesKey4 = 0,                                                  /* Big endian aes key */
        .aesKey5 = 0,                                                  /* Big endian aes key */
        .aesKey6 = 0,                                                  /* Big endian aes key */
        .aesKey7 = 0                                                   /* Big endian aes key(aes-256 key LSB) */
    };

    puts("[ECB] AES-128-ECB case...\r\n");

    Sec_Eng_AES_Enable_Link(aesId);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]), 32, aesDstBuf);
    Aes_Compare_Data(aesResult_entrypted_ecb_128, (uint8_t*)linkCfg.aesDstAddr, 32);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 32, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_ecb_128[0]) + 32, (uint8_t*)linkCfg.aesDstAddr, 16);

    Sec_Eng_AES_Link_Work(aesId, (uint32_t)&linkCfg, &(aesSrcBuf_data[0]) + 48, 16, aesDstBuf);
    Aes_Compare_Data(&(aesResult_entrypted_ecb_128[0]) + 48, (uint8_t*)linkCfg.aesDstAddr, 16);

    Sec_Eng_AES_Disable_Link(aesId);
}

int bl_sec_aes_init(void)
{
    Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID0);
    return 0;
}

int bl_sec_aes_test(void)
{
    bl_irq_register(SEC_AES_IRQn, bl_sec_aes_IRQHandler);
    bl_irq_enable(SEC_AES_IRQn);
    blog_print("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n");
    Sec_Eng_AES_Link_Case_CBC_128(SEC_ENG_AES_ID0);
    blog_print("####################################################################################\r\n");
    Sec_Eng_AES_Link_Case_CTR_128(SEC_ENG_AES_ID0);
    blog_print("####################################################################################\r\n");
    Sec_Eng_AES_Link_Case_ECB_128(SEC_ENG_AES_ID0);
    blog_print("------------------------------------------------------------------------------------\r\n");
    return 0;
}

static void _clear_aes_int()
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t val;

    val = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    val = BL_SET_REG_BIT(val, SEC_ENG_SE_AES_0_INT_CLR_1T);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, val);
}

void bl_sec_aes_IRQHandler(void)
{
    blog_print("--->>> AES IRQ\r\n");
    _clear_aes_int();
}
