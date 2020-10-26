# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := include/mbedtls include/icrypto

NAME := imbedtls

$(NAME)_MBINS_TYPE := kernel
$(NAME)_VERSION := 2.0.1
$(NAME)_SUMMARY := Mbed Transport Layer Security on Embedded Devices for AliOS Things

## This component's src 
COMPONENT_SRCS := src/aes.c
COMPONENT_SRCS += src/aesni.c
COMPONENT_SRCS += src/arc4.c
COMPONENT_SRCS += src/asn1write.c
COMPONENT_SRCS += src/asn1parse.c
COMPONENT_SRCS += src/base64.c
COMPONENT_SRCS += src/bignum.c
COMPONENT_SRCS += src/blowfish.c
COMPONENT_SRCS += src/camellia.c
COMPONENT_SRCS += src/ccm.c
COMPONENT_SRCS += src/cipher.c
COMPONENT_SRCS += src/cipher_wrap.c
COMPONENT_SRCS += src/cmac.c
COMPONENT_SRCS += src/ctr_drbg.c
COMPONENT_SRCS += src/debug.c
COMPONENT_SRCS += src/des.c
COMPONENT_SRCS += src/dhm.c
COMPONENT_SRCS += src/ecdh.c
COMPONENT_SRCS += src/ecdsa.c
COMPONENT_SRCS += src/ecjpake.c
COMPONENT_SRCS += src/ecp.c
COMPONENT_SRCS += src/ecp_curves.c
COMPONENT_SRCS += src/entropy.c
COMPONENT_SRCS += src/entropy_poll.c
COMPONENT_SRCS += src/error.c
COMPONENT_SRCS += src/gcm.c
COMPONENT_SRCS += src/havege.c
COMPONENT_SRCS += src/hmac_drbg.c
COMPONENT_SRCS += src/md2.c
COMPONENT_SRCS += src/md4.c
COMPONENT_SRCS += src/md.c
COMPONENT_SRCS += src/md_wrap.c
COMPONENT_SRCS += src/memory_buffer_alloc.c
COMPONENT_SRCS += src/net_sockets.c
COMPONENT_SRCS += src/oid.c
COMPONENT_SRCS += src/padlock.c
COMPONENT_SRCS += src/pem.c
COMPONENT_SRCS += src/pk.c
COMPONENT_SRCS += src/pkcs11.c
COMPONENT_SRCS += src/pkcs12.c
COMPONENT_SRCS += src/pkcs5.c
COMPONENT_SRCS += src/pkparse.c
COMPONENT_SRCS += src/pk_wrap.c
COMPONENT_SRCS += src/pkwrite.c
COMPONENT_SRCS += src/platform.c
COMPONENT_SRCS += src/ripemd160.c
COMPONENT_SRCS += src/rsa.c
COMPONENT_SRCS += src/md5.c
COMPONENT_SRCS += src/sha1.c
COMPONENT_SRCS += src/sha256.c
COMPONENT_SRCS += src/sha512.c
COMPONENT_SRCS += src/ssl_cache.c
COMPONENT_SRCS += src/ssl_ciphersuites.c
COMPONENT_SRCS += src/ssl_cli.c
COMPONENT_SRCS += src/ssl_cookie.c
COMPONENT_SRCS += src/ssl_srv.c
COMPONENT_SRCS += src/ssl_ticket.c
COMPONENT_SRCS += src/ssl_tls.c
COMPONENT_SRCS += src/timing.c
COMPONENT_SRCS += src/threading.c
COMPONENT_SRCS += src/version.c
COMPONENT_SRCS += src/version_features.c
COMPONENT_SRCS += src/x509.c
COMPONENT_SRCS += src/x509_create.c
COMPONENT_SRCS += src/x509_crl.c
COMPONENT_SRCS += src/x509_crt.c
COMPONENT_SRCS += src/x509_csr.c
COMPONENT_SRCS += src/x509write_crt.c
COMPONENT_SRCS += src/x509write_csr.c
COMPONENT_SRCS += src/xtea.c
COMPONENT_SRCS += src/mbedtls_alt.c
COMPONENT_SRCS += src/mbedtls_net.c
COMPONENT_SRCS += src/mbedtls_ssl.c
COMPONENT_SRCS += src/mycalloc.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
CPPFLAGS += -DLWIP_ENABLED -DCONFIG_PLAT_AOS  
