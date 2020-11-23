/**
 * \file config.h
 *
 * \brief Configuration options (set of defines)
 *
 *  This set of compile-time options may be used to enable
 *  or disable features selectively, and reduce the global
 *  memory footprint.
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

#if !defined(CONFIG_MBEDTLS_ORIG)
/* System support */
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_FS_IO
//#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
//#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
//#define MBEDTLS_ECDH_C
#define MBEDTLS_ECP_C
//#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED

/* mbed TLS feature support */
#define MBEDTLS_GCM_C
#define MBEDTLS_CIPHER_MODE_CTR
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_PADDING_ZEROS
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_COOKIE_C
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_SESSION_TICKETS
#define MBEDTLS_CIPHER_MODE_CFB
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
//#define MBEDTLS_SSL_RENEGOTIATION
//#define MBEDTLS_SSL_DTLS_ANTI_REPLAY
#define MBEDTLS_SSL_ALPN
//#define MBEDTLS_THREADING_C
//#define MBEDTLS_TIMING_C
//#define MBEDTLS_NO_PLATFORM_ENTROPY

/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_OID_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_MD_C
#define MBEDTLS_MD5_C
#define MBEDTLS_NET_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_RSA_C
#define MBEDTLS_RSA_PRIV_ENABLED
#define MBEDTLS_SHA1_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_PEM_PARSE_C

/* For test certificates */
#define MBEDTLS_ERROR_C
#define MBEDTLS_ERROR_STRERROR_DUMMY
#define MBEDTLS_GENPRIME
#define MBEDTLS_BASE64_C
//#define MBEDTLS_SSL_ALL_ALERT_MESSAGES

#define CONFIG_SSL_DEBUG
#if defined(CONFIG_SSL_DEBUG)
#define MBEDTLS_DEBUG_C
#endif

#else  /* CONFIG_MBEDTLS_ORIG */

/* System support */
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PLATFORM_ALT

/* mbed TLS feature support */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_THREADING_C

/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C

#define MBEDTLS_OID_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_MD_C
#define MBEDTLS_MD5_C
#define MBEDTLS_NET_C
#define MBEDTLS_PK_C
#define MBEDTLS_PKMBEDTLS_THREADING_C_PARSE_C
#define MBEDTLS_RSMBEDTLS_THREADING_CA_C
#define MBEDTLS_SHMBEDTLS_THREADING_CA1_C
#define MBEDTLS_SHMBEDTLS_THREADING_CA256_C
#define MBEDTLS_SSMBEDTLS_THREADING_CL_CLI_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_SESSION_TICKETS
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ENTROPY_C

/* mbed DTLS modules */
#define MBEDTLS_TIMING_C
#define MBEDTLS_SSL_COOKIE_C
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY

/* mbed TLS debug */
#if defined(CONFIG_SSL_DEBUG)
#define MBEDTLS_DEBUG_C
#endif

#define MBEDTLS_IOT_SPECIFIC
#define MBEDTLS_MD_ALT
#define MBEDTLS_PK_ALT
#define MBEDTLS_AES_ALT

#if defined(MBEDTLS_MD_ALT)
#if defined(MBEDTLS_MD5_C)
#define MBEDTLS_MD5_ALT
#endif
#if defined(MBEDTLS_SHA1_C)
#define MBEDTLS_SHA1_ALT
#endif
#if defined(MBEDTLS_SHA256_C)
#define MBEDTLS_SHA256_ALT
#endif
#endif /* MBEDTLS_MD_ALT */

#endif /* CONFIG_MBEDTLS_ORIG */

#if defined(CONFIG_PLAT_AOS)
//#define MBEDTLS_THREADING_ALT
#define MBEDTLS_NET_ALT
#else
//#define MBEDTLS_THREADING_PTHREAD
#endif /* CONFIG_PLAT_AOS */

#define OTA_CONFIG_TLS
#if defined(OTA_CONFIG_TLS)
#define MBEDTLS_SSL_MAX_CONTENT_LEN    (16 * 1024)    /* Size of the input / output buffer */
#else
#define MBEDTLS_SSL_MAX_CONTENT_LEN    (16 * 1024)    /* Size of the input / output buffer */
#endif
#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */
