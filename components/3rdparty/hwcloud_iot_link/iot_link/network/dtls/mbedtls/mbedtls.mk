################################################################################
# this is used for compile the mbedtls
################################################################################
#only support the "crt" mode and "psk" mode

vpath %.c $(iot_link_root)/network/dtls/mbedtls/mbedtls_port


USE_MBEDTLS_AES_ROM_TABLES := y


MBEDTLS_INC = \
        -I $(iot_link_root)/network/dtls/mbedtls/mbedtls_port

MBEDTLS_SRC = \
        ${wildcard $(iot_link_root)/network/dtls/mbedtls/mbedtls_port/*.c}

MBEDTLS_DEF = -D WITH_DTLS

ifeq ($(CONFIG_MBED_DEBUG_ENABLE), y) 
    MBEDTLS_DEF += -D MBEDTLS_DEBUG_C=1
endif

ifeq ($(USE_MBEDTLS_AES_ROM_TABLES), y)
    MBEDTLS_DEF += -D MBEDTLS_AES_ROM_TABLES
endif


ifeq ($(CONFIG_MBEDTLS_CERT), y)
    C_DEFS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config_cert.h\"
    C_INCLUDES += $(MBEDTLS_INC)
    C_SOURCES += $(MBEDTLS_SRC)
    MBEDTLS_DEF += -D CONFIG_DTLS_MBEDTLS_CERT
    C_DEFS += $(MBEDTLS_DEF) -D CFG_MBEDTLS_MODE=CRT
else ifeq ($(CONFIG_MBEDTLS_PSK), y)
    C_DEFS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config.h\"
    C_INCLUDES += $(MBEDTLS_INC)
    C_SOURCES += $(MBEDTLS_SRC)
    MBEDTLS_DEF += -D CONFIG_DTLS_MBEDTLS_PSK
    C_DEFS += $(MBEDTLS_DEF) -D CFG_MBEDTLS_MODE=PSK
else ifeq ($(CONFIG_MBEDTLS_CERT_PSK), y)
    C_DEFS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config_dtls.h\"
    C_INCLUDES += $(MBEDTLS_INC)
    C_SOURCES += $(MBEDTLS_SRC)
    MBEDTLS_DEF += -D CONFIG_DTLS_MBEDTLS_CERT -D CONFIG_DTLS_MBEDTLS_PSK
    C_DEFS += $(MBEDTLS_DEF) -D CFG_MBEDTLS_MODE=PSK_CERT
else
    C_DEFS += -D NO_DTLS
endif



