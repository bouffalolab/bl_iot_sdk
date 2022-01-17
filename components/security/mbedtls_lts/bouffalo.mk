# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += mbedtls/include port

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS += mbedtls/library/aes.c
COMPONENT_SRCS += mbedtls/library/aesni.c
COMPONENT_SRCS += mbedtls/library/arc4.c
COMPONENT_SRCS += mbedtls/library/aria.c
COMPONENT_SRCS += mbedtls/library/asn1parse.c
COMPONENT_SRCS += mbedtls/library/asn1write.c
COMPONENT_SRCS += mbedtls/library/base64.c
ifeq ($(CONFIG_MBEDTLS_BIGNUM_USE_HW),1)
COMPONENT_SRCS += port/bignum.c
else
COMPONENT_SRCS += mbedtls/library/bignum.c
endif
COMPONENT_SRCS += mbedtls/library/blowfish.c
COMPONENT_SRCS += mbedtls/library/camellia.c
COMPONENT_SRCS += mbedtls/library/ccm.c
COMPONENT_SRCS += mbedtls/library/certs.c
COMPONENT_SRCS += mbedtls/library/chacha20.c
COMPONENT_SRCS += mbedtls/library/chachapoly.c
COMPONENT_SRCS += mbedtls/library/cipher.c
COMPONENT_SRCS += mbedtls/library/cipher_wrap.c
COMPONENT_SRCS += mbedtls/library/cmac.c
COMPONENT_SRCS += mbedtls/library/ctr_drbg.c
COMPONENT_SRCS += mbedtls/library/debug.c
COMPONENT_SRCS += mbedtls/library/des.c
COMPONENT_SRCS += mbedtls/library/dhm.c
COMPONENT_SRCS += mbedtls/library/ecdh.c
COMPONENT_SRCS += mbedtls/library/ecdsa.c
COMPONENT_SRCS += mbedtls/library/ecjpake.c
COMPONENT_SRCS += mbedtls/library/ecp.c
COMPONENT_SRCS += mbedtls/library/ecp_curves.c
COMPONENT_SRCS += mbedtls/library/entropy.c
COMPONENT_SRCS += mbedtls/library/error.c
COMPONENT_SRCS += mbedtls/library/gcm.c
COMPONENT_SRCS += mbedtls/library/havege.c
COMPONENT_SRCS += mbedtls/library/hkdf.c
COMPONENT_SRCS += mbedtls/library/hmac_drbg.c
COMPONENT_SRCS += mbedtls/library/md2.c
COMPONENT_SRCS += mbedtls/library/md4.c
COMPONENT_SRCS += mbedtls/library/md5.c
COMPONENT_SRCS += mbedtls/library/md.c
COMPONENT_SRCS += mbedtls/library/md_wrap.c
COMPONENT_SRCS += mbedtls/library/memory_buffer_alloc.c
COMPONENT_SRCS += mbedtls/library/nist_kw.c
COMPONENT_SRCS += mbedtls/library/oid.c
COMPONENT_SRCS += mbedtls/library/padlock.c
COMPONENT_SRCS += mbedtls/library/pem.c
COMPONENT_SRCS += mbedtls/library/pk.c
COMPONENT_SRCS += mbedtls/library/pkcs11.c
COMPONENT_SRCS += mbedtls/library/pkcs12.c
COMPONENT_SRCS += mbedtls/library/pkcs5.c
COMPONENT_SRCS += mbedtls/library/pk_wrap.c
COMPONENT_SRCS += mbedtls/library/pkwrite.c
COMPONENT_SRCS += mbedtls/library/platform.c
COMPONENT_SRCS += mbedtls/library/platform_util.c
COMPONENT_SRCS += mbedtls/library/poly1305.c
COMPONENT_SRCS += mbedtls/library/ripemd160.c
COMPONENT_SRCS += mbedtls/library/rsa.c
COMPONENT_SRCS += mbedtls/library/rsa_internal.c
COMPONENT_SRCS += mbedtls/library/sha1.c
COMPONENT_SRCS += mbedtls/library/sha256.c
COMPONENT_SRCS += mbedtls/library/sha512.c
COMPONENT_SRCS += mbedtls/library/ssl_cache.c
COMPONENT_SRCS += mbedtls/library/ssl_ciphersuites.c
COMPONENT_SRCS += mbedtls/library/ssl_cli.c
COMPONENT_SRCS += mbedtls/library/ssl_cookie.c
COMPONENT_SRCS += mbedtls/library/ssl_srv.c
COMPONENT_SRCS += mbedtls/library/ssl_ticket.c
COMPONENT_SRCS += mbedtls/library/ssl_tls.c
COMPONENT_SRCS += mbedtls/library/threading.c
COMPONENT_SRCS += mbedtls/library/timing.c
COMPONENT_SRCS += mbedtls/library/version.c
COMPONENT_SRCS += mbedtls/library/version_features.c
COMPONENT_SRCS += mbedtls/library/x509.c
COMPONENT_SRCS += mbedtls/library/x509_create.c
COMPONENT_SRCS += mbedtls/library/x509_crl.c
COMPONENT_SRCS += mbedtls/library/x509_crt.c
COMPONENT_SRCS += mbedtls/library/x509_csr.c
COMPONENT_SRCS += mbedtls/library/x509write_crt.c
COMPONENT_SRCS += mbedtls/library/x509write_csr.c
COMPONENT_SRCS += mbedtls/library/xtea.c

COMPONENT_SRCS += port/pkparse.c
COMPONENT_SRCS += port/mbedtls_port_mem.c
COMPONENT_SRCS += port/net_sockets.c
COMPONENT_SRCS += port/entropy_poll.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := mbedtls/library port

##
