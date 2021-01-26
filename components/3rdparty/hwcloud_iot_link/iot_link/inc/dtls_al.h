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

#ifndef LITEOS_LAB_IOT_LINK_NETWORK_DTLS_DTLS_AL_DTLS_AL_H_
#define LITEOS_LAB_IOT_LINK_NETWORK_DTLS_DTLS_AL_DTLS_AL_H_


#include <stdint.h>
#include <stddef.h>

typedef enum
{
    EN_DTLS_AL_ERR_OK = 0,
    EN_DTLS_AL_ERR_PARA,
    EN_DTLS_AL_ERR_SYS,
    EN_DTLS_AL_ERR_SYSMEM,
    EN_DTLS_AL_ERR_NOCONFIG,
    EN_DTLS_AL_ERR_NETWORK,
    EN_DTLS_AL_ERR_SERVERCERTPARSE,
    EN_DTLS_AL_ERR_CLIENTCERTPARSE,
    EN_DTLS_AL_ERR_CLIENTPKPARSE,
}en_dtls_al_err_t;

/** @brief  this enum all the transport encode we support now*/
typedef enum
{
    EN_DTLS_AL_SECURITY_TYPE_NONE = 0,   ///< no encode
    EN_DTLS_AL_SECURITY_TYPE_PSK,        ///< use the psk mode in transport layer
    EN_DTLS_AL_SECURITY_TYPE_CERT,       ///< use the ca mode in transport layer,only check the server
}en_dtls_al_security_type_t;

/** @brief this data defines for the psk mode*/
typedef struct
{
    uint8_t     *psk_id;           ///< the psk id
    uint8_t     *psk_key;          ///< the psk key
    int          psk_id_len;       ///< the psk id length
    int          psk_key_len;      ///< the psk key length
}dtls_al_security_psk_t;


/** @brief this data defines for the cas mode:only check the server  */
typedef struct
{
    uint8_t    *server_ca;
    uint8_t    *client_ca;
    uint8_t    *client_pk;
    uint8_t    *client_pk_pwd;
    int         server_ca_len;
    int         client_ca_len;
    int         client_pk_len;
    int         client_pk_pwd_len;
    char       *server_name;
}dtls_al_security_cert_t;


/** @brief this data defines for the encode parameter for the connect */
typedef struct
{
    en_dtls_al_security_type_t    type;         ///< which security type of the data
    union
    {
        dtls_al_security_psk_t     psk;         ///< psk data  if the type is EN_DTSL_SECURITY_TYPE_PSK
        dtls_al_security_cert_t    cert;         ///< cert data  if the type is EN_DTSL_SECURITY_TYPE_CERT
    }u;
}dtls_al_security_t;

typedef struct
{
    int                 istcp;
    int                 isclient;
    dtls_al_security_t  security;
}dtls_al_para_t;

en_dtls_al_err_t  dtls_al_new(dtls_al_para_t *para,void **handle);
int   dtls_al_connect(void *handle,const char *ip, const char *port, int timeout );
int   dtls_al_write(void *handle, uint8_t *msg, size_t len, int timeout );
int   dtls_al_read(void *handle,uint8_t *buf, size_t len,int timeout );
en_dtls_al_err_t   dtls_al_destroy(void *handle);

typedef en_dtls_al_err_t (*fn_dtls_al_new)(dtls_al_para_t *para,void **handle);
typedef int (*fn_dtls_al_connect)(void *handle,const char *server_ip, const char *server_port,int timeout);
typedef int (*fn_dtls_al_write)(void *handle,uint8_t *msg, size_t len, int timeout);
typedef int (*fn_dtls_al_read)(void *handle, uint8_t *buf, size_t len, int timeout);
typedef en_dtls_al_err_t (*fn_dtls_al_destroy)(void *handle);

typedef struct
{
    fn_dtls_al_new            io_new;
    fn_dtls_al_connect        io_connect;
    fn_dtls_al_write          io_write;
    fn_dtls_al_read           io_read;
    fn_dtls_al_destroy        io_destroy;
}dtls_al_io_t;

typedef struct
{
    const char     *name;
    dtls_al_io_t    io;
}dtls_al_t;

int dtls_al_install(const dtls_al_t *dtls);
int dtls_al_uninstall(const char*name);

///< this function should implemented by the developer of the tls
int dtls_imp_init(void);
int dtls_al_init(void) ;  ///< this function will call dtls_imp_init()



#endif /* LITEOS_LAB_IOT_LINK_NETWORK_DTLS_DTLS_AL_DTLS_AL_H_ */
