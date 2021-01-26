/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/


#include <string.h>
#include <osal.h>
#include <dtls_al.h>
#include <dtls_interface.h>

#include <platform.h> //

#if defined(MBEDTLS_DEBUG_C)
static void mbed_port_debug( void *ctx, int level,
                      const char *file, int line,
                      const char *str )
{
    const char *p, *basename;

    /* Extract basename from file */
    for( p = basename = file; *p != '\0'; p++ )
        if( *p == '/' || *p == '\\' )
            basename = p + 1;

    printf("%s:%04d: |%d| %s", basename, line, level, str );
}
#endif

en_dtls_al_err_t mbed_new(dtls_al_para_t *para, void **handle)
{

    en_dtls_al_err_t ret = EN_DTLS_AL_ERR_PARA;
    mbedtls_ssl_context  *ssl;
    dtls_establish_info_s einfo;
    char  plat_type;

    if(para->security.type == EN_DTLS_AL_SECURITY_TYPE_CERT)
    {
        einfo.psk_or_cert = VERIFY_WITH_CERT;

        einfo.v.c.ca_cert = para->security.u.cert.server_ca;
        einfo.v.c.cert_len = para->security.u.cert.server_ca_len;
        einfo.v.c.client_ca = para->security.u.cert.client_ca;
        einfo.v.c.client_ca_len = para->security.u.cert.client_ca_len;
        einfo.v.c.client_pk = para->security.u.cert.client_pk;
        einfo.v.c.client_pk_len = para->security.u.cert.client_pk_len;
        einfo.v.c.client_pk_pwd = para->security.u.cert.client_pk_pwd;
        einfo.v.c.client_pk_pwd_len = para->security.u.cert.client_pk_pwd_len;
    }
    else
    {
        einfo.psk_or_cert  = VERIFY_WITH_PSK;
        einfo.v.p.psk = para->security.u.psk.psk_key;
        einfo.v.p.psk_len = para->security.u.psk.psk_key_len;
        einfo.v.p.psk_identity = para->security.u.psk.psk_id;
    }

    if(para->istcp)
    {
        einfo.udp_or_tcp = MBEDTLS_NET_PROTO_TCP;
    }
    else
    {
        einfo.udp_or_tcp = MBEDTLS_NET_PROTO_UDP;
    }


    if(para->isclient)
    {
        plat_type = MBEDTLS_SSL_IS_CLIENT;
    }
    else
    {
        plat_type = MBEDTLS_SSL_IS_SERVER;
    }

    ssl = dtls_ssl_new(&einfo, plat_type);

    if(NULL != ssl)
    {
        *handle = ssl;
        ret = EN_DTLS_AL_ERR_OK;

        #if defined(MBEDTLS_DEBUG_C)
            mbedtls_debug_set_threshold(10);
            mbedtls_ssl_conf_dbg (ssl->conf,mbed_port_debug,NULL);
        #endif
    }

    return ret;
}


en_dtls_al_err_t mbed_destroy(void *handle)
{
    en_dtls_al_err_t ret = EN_DTLS_AL_ERR_PARA;
    if(NULL != handle)
    {
        dtls_ssl_destroy(handle);
        ret = EN_DTLS_AL_ERR_OK;
    }
    return ret;
}


///< make it return as normal socket return

int mbed_write(void *handle, uint8_t *buf, size_t len,int timeout)
{

    int ret;

    ret = dtls_write(handle, buf,len);

    return ret;
}


int mbed_read( void *handle, unsigned char *buf, size_t len, int timeout)
{
    int ret;

    ret = dtls_read(handle, buf,len,timeout);

    return ret;
}

int dtls_shakehand(mbedtls_ssl_context *ssl, const dtls_shakehand_info_s *info);


int mbed_connect(void *handle,const char *server_ip, const char *server_port,int timeout)
{
    int ret = -1;
    dtls_shakehand_info_s  sinfo;


    (void) memset(&sinfo, 0, sizeof(sinfo));


    sinfo.u.c.host = server_ip;
    sinfo.u.c.port = server_port;

    sinfo.client_or_server = MBEDTLS_SSL_IS_CLIENT;
    sinfo.udp_or_tcp = MBEDTLS_NET_PROTO_TCP;
    sinfo.timeout = timeout;

    ret = dtls_shakehand( handle,&sinfo);

    return ret;
}

static const dtls_al_t  s_mbedtls_io =
{
    .name = "mbed",
    .io = {
            .io_new = mbed_new,
            .io_connect = mbed_connect,
            .io_read = mbed_read,
            .io_write = mbed_write,
            .io_destroy = mbed_destroy,
    },
};



int dtls_imp_init(void)
{
    int ret =-1;

    (void)mbedtls_platform_set_calloc_free(osal_calloc, osal_free);
    (void)mbedtls_platform_set_snprintf(snprintf);
    (void)mbedtls_platform_set_printf(printf);
    ret = dtls_al_install(&s_mbedtls_io);

    return ret;
}

