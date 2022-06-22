# Component Makefile
#

ifeq ($(CONFIG_CHIP_NAME),BL602)
CFLAGS += -DBL602
endif
ifeq ($(CONFIG_CHIP_NAME),BL702)
CFLAGS += -DBL702
endif
ifeq ($(CONFIG_CHIP_NAME),BL808)
CFLAGS += -DBL808
endif
ifeq ($(CONFIG_CHIP_NAME),BL606P)
CFLAGS += -DBL606P
endif

## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += mbedtls/include port

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

LIBRARY_DIR := mbedtls/library
LIBRARY_SRCS := \
        aes.c                 \
        aesni.c               \
        arc4.c                \
        aria.c                \
        asn1parse.c           \
        asn1write.c           \
        base64.c              \
        blowfish.c            \
        camellia.c            \
        ccm.c                 \
        certs.c               \
        chacha20.c            \
        chachapoly.c          \
        cipher.c              \
        cipher_wrap.c         \
        cmac.c                \
        ctr_drbg.c            \
        debug.c               \
        des.c                 \
        dhm.c                 \
        ecdh.c                \
        ecdsa.c               \
        ecjpake.c             \
        ecp.c                 \
        ecp_curves.c          \
        entropy.c             \
        error.c               \
        gcm.c                 \
        havege.c              \
        hkdf.c                \
        hmac_drbg.c           \
        md2.c                 \
        md4.c                 \
        md5.c                 \
        md.c                  \
        md_wrap.c             \
        memory_buffer_alloc.c \
        nist_kw.c             \
        oid.c                 \
        padlock.c             \
        pem.c                 \
        pk.c                  \
        pkcs11.c              \
        pkcs12.c              \
        pkcs5.c               \
        pk_wrap.c             \
        pkwrite.c             \
        platform.c            \
        platform_util.c       \
        poly1305.c            \
        ripemd160.c           \
        rsa.c                 \
        rsa_internal.c        \
        sha1.c                \
        sha256.c              \
        sha512.c              \
        ssl_cache.c           \
        ssl_ciphersuites.c    \
        ssl_cli.c             \
        ssl_cookie.c          \
        ssl_srv.c             \
        ssl_ticket.c          \
        ssl_tls.c             \
        threading.c           \
        timing.c              \
        version.c             \
        version_features.c    \
        x509.c                \
        x509_create.c         \
        x509_crl.c            \
        x509_crt.c            \
        x509_csr.c            \
        x509write_crt.c       \
        x509write_csr.c       \
        xtea.c                \

## This component's src
COMPONENT_SRCS := $(addprefix $(LIBRARY_DIR)/, $(LIBRARY_SRCS))

COMPONENT_SRCS += \
        port/pkparse.c          \
        port/mbedtls_port_mem.c \
        port/net_sockets.c      \
        port/entropy_poll.c     \

ifeq ($(CONFIG_MBEDTLS_BIGNUM_USE_HW),1)
COMPONENT_SRCS += port/bignum.c
COMPONENT_SRCS += port/hw_acc/bignum_common.c
else
COMPONENT_SRCS += $(addprefix $(LIBRARY_DIR)/, bignum.c)
endif

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := $(LIBRARY_DIR) port port/hw_acc

##
