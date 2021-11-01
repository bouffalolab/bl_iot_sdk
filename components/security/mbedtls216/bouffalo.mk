# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
# COMPONENT_PRIV_INCLUDEDIRS := include/icrypto

NAME := mbedtls27

$(NAME)_MBINS_TYPE := kernel
$(NAME)_VERSION := 2.7.14
$(NAME)_SUMMARY := Mbed Transport Layer Security on Embedded Devices for AliOS Things

## This component's src 
COMPONENT_SRCS := library/aes.c
COMPONENT_SRCS += library/aesni.c
COMPONENT_SRCS += library/arc4.c
COMPONENT_SRCS += library/asn1write.c
COMPONENT_SRCS += library/asn1parse.c
COMPONENT_SRCS += library/base64.c
COMPONENT_SRCS += library/bignum.c
COMPONENT_SRCS += library/blowfish.c
COMPONENT_SRCS += library/camellia.c
COMPONENT_SRCS += library/ccm.c
COMPONENT_SRCS += library/cipher.c
COMPONENT_SRCS += library/cipher_wrap.c
COMPONENT_SRCS += library/cmac.c
COMPONENT_SRCS += library/ctr_drbg.c
COMPONENT_SRCS += library/debug.c
COMPONENT_SRCS += library/des.c
COMPONENT_SRCS += library/dhm.c
COMPONENT_SRCS += library/ecdh.c
COMPONENT_SRCS += library/ecdsa.c
COMPONENT_SRCS += library/ecjpake.c
COMPONENT_SRCS += library/ecp.c
COMPONENT_SRCS += library/ecp_curves.c
COMPONENT_SRCS += library/entropy.c
COMPONENT_SRCS += library/error.c
COMPONENT_SRCS += library/gcm.c
COMPONENT_SRCS += library/havege.c
COMPONENT_SRCS += library/hmac_drbg.c
COMPONENT_SRCS += library/md2.c
COMPONENT_SRCS += library/md4.c
COMPONENT_SRCS += library/md.c
COMPONENT_SRCS += library/md_wrap.c
COMPONENT_SRCS += library/memory_buffer_alloc.c
COMPONENT_SRCS += library/oid.c
COMPONENT_SRCS += library/padlock.c
COMPONENT_SRCS += library/pem.c
COMPONENT_SRCS += library/pk.c
COMPONENT_SRCS += library/pkcs11.c
COMPONENT_SRCS += library/pkcs12.c
COMPONENT_SRCS += library/pkcs5.c
COMPONENT_SRCS += library/pkparse.c
COMPONENT_SRCS += library/pk_wrap.c
COMPONENT_SRCS += library/pkwrite.c
COMPONENT_SRCS += library/platform.c
COMPONENT_SRCS += library/platform_util.c
COMPONENT_SRCS += library/ripemd160.c
COMPONENT_SRCS += library/rsa.c
COMPONENT_SRCS += library/rsa_internal.c
COMPONENT_SRCS += library/md5.c
COMPONENT_SRCS += library/sha1.c
COMPONENT_SRCS += library/sha256.c
COMPONENT_SRCS += library/sha512.c
COMPONENT_SRCS += library/ssl_cache.c
COMPONENT_SRCS += library/ssl_ciphersuites.c
COMPONENT_SRCS += library/ssl_cli.c
COMPONENT_SRCS += library/ssl_cookie.c
COMPONENT_SRCS += library/ssl_srv.c
COMPONENT_SRCS += library/ssl_ticket.c
COMPONENT_SRCS += library/ssl_tls.c
COMPONENT_SRCS += library/timing.c
COMPONENT_SRCS += library/threading.c
COMPONENT_SRCS += library/version.c
COMPONENT_SRCS += library/version_features.c
COMPONENT_SRCS += library/x509.c
COMPONENT_SRCS += library/x509_create.c
COMPONENT_SRCS += library/x509_crl.c
COMPONENT_SRCS += library/x509_crt.c
COMPONENT_SRCS += library/x509_csr.c
COMPONENT_SRCS += library/x509write_crt.c
COMPONENT_SRCS += library/x509write_csr.c
COMPONENT_SRCS += library/xtea.c

## port layer src 
COMPONENT_SRCS += port/net_sockets.c
COMPONENT_SRCS += port/entropy_poll.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := library port


##
CPPFLAGS += -DLWIP_ENABLED -DCONFIG_PLAT_AOS  
