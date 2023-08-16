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
#include "bflb_rsa.h"
#include "bflb_hash.h"

int32_t bflb_rsa_init(bflb_rsa_handle_t *rsa_handle,int padding,int hashtype )
{
    int32_t ret = BFLB_RSA_OK;
    memset(rsa_handle,0,sizeof(bflb_rsa_handle_t));
    mbedtls_rsa_init((mbedtls_rsa_context*)&rsa_handle->rsa_ctx, padding, bflb_hash_get_type(hashtype));
    return ret;
}

int32_t bflb_rsa_set_parameter(bflb_rsa_handle_t *rsa_handle,int type,uint8_t *value,
                                uint32_t len )
{
    int32_t ret = BFLB_RSA_OK;
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;
    
	switch(type)
	{
        case BFLB_RSA_PARA_N:
            mbedtls_mpi_read_binary(&rsa->N,value,len);
            rsa->len = ( mbedtls_mpi_bitlen( &rsa->N ) + 7 ) >> 3;
            break;
        case BFLB_RSA_PARA_E:
            mbedtls_mpi_read_binary(&rsa->E,value,len);
            break;
        case BFLB_RSA_PARA_D:
            mbedtls_mpi_read_binary(&rsa->D,value,len);
            break;
        case BFLB_RSA_PARA_P:
            mbedtls_mpi_read_binary(&rsa->P,value,len);
            break;
        case BFLB_RSA_PARA_Q:
            mbedtls_mpi_read_binary(&rsa->Q,value,len);
            break;
        case BFLB_RSA_PARA_DP:
            mbedtls_mpi_read_binary(&rsa->DP,value,len);
            break;
        case BFLB_RSA_PARA_DQ:
            mbedtls_mpi_read_binary(&rsa->DQ,value,len);
            break;
        case BFLB_RSA_PARA_QP:
            mbedtls_mpi_read_binary(&rsa->QP,value,len);
            break;
        default:
            ret=BFLB_RSA_ERROR;
            break;
	}
	
    return ret;
}

int32_t bflb_rsa_check_private(bflb_rsa_handle_t *rsa_handle)
{
    int32_t ret = BFLB_RSA_OK;
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;
    
	if( ( ret = mbedtls_rsa_check_privkey( rsa ) ) != 0 )
    {
        bflb_rsa_printe("failed\r\n!rsa_check_privkey failed with -0x%0x\n", -ret );
        return BFLB_RSA_ERROR;
    }

    return BFLB_RSA_OK;
}

int32_t bflb_rsa_check_public(bflb_rsa_handle_t *rsa_handle)
{
    int32_t ret = BFLB_RSA_OK;
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;

	if( ( ret = mbedtls_rsa_check_pubkey( rsa ) ) != 0 )
    {
        bflb_rsa_printe("failed\r\n!rsa_check_privkey failed with -0x%0x\n", -ret );
        return BFLB_RSA_ERROR;
    }
	
    return BFLB_RSA_OK;
}

int32_t bflb_rsa_sign( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,uint8_t *sig,uint32_t *slen)
{
    int32_t ret = BFLB_RSA_OK;
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;
    
	ret = mbedtls_rsa_pkcs1_sign( rsa, NULL, NULL, MBEDTLS_RSA_PRIVATE,
    						(mbedtls_md_type_t)bflb_hash_get_type(hashtype),
                            hashlen, hash, sig );
    if( ret != 0 )
    {
        bflb_rsa_printe("failed\r\n!rsa_pkcs1_sign failed with -0x%0x\n", -ret );
        return BFLB_RSA_ERROR;
    }	
    *slen=rsa->len;
    return BFLB_RSA_OK;                        
}

int32_t bflb_rsa_verify( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,const uint8_t *sig,uint32_t slen)
{
    int32_t ret = BFLB_RSA_OK;
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;
    
    ret = mbedtls_rsa_pkcs1_verify( rsa, NULL, NULL, MBEDTLS_RSA_PUBLIC, 
    						(mbedtls_md_type_t)bflb_hash_get_type(hashtype),
                            hashlen, hash, sig );
    if( ret != 0 )
    {
        bflb_rsa_printe("failed\r\n!rsa_pkcs1_verify failed with -0x%0x\n", -ret );
        return BFLB_RSA_ERROR;
    }	
    return BFLB_RSA_OK;                        
}

int32_t bflb_rsa_deinit( bflb_rsa_handle_t *rsa_handle)
{
    mbedtls_rsa_context* rsa=(mbedtls_rsa_context*)&rsa_handle->rsa_ctx;
    
    mbedtls_rsa_free( rsa );
    memset(rsa_handle,0,sizeof(bflb_rsa_handle_t));
    
    return BFLB_RSA_OK;                        
}
