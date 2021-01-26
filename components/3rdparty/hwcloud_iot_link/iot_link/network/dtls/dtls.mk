################################################################################
# this is used for compile the dtls
################################################################################

vpath %.c $(iot_link_root)/network/dtls
vpath %.c $(iot_link_root)/network/dtls/dtls_al
#vpath %.c $(iot_link_root)/network/dtls/mbedtls/mbedtls_port

ifeq ($(CONFIG_DTLS_AL_ENABLE), y)

    C_SOURCES += ${wildcard $(iot_link_root)/network/dtls/dtls_al/*.c}
    C_INCLUDES += -I $(iot_link_root)/network/dtls/dtls_al
    
    ifeq ($(CONFIG_MBEDTLS_ENABLE), y)
      include $(iot_link_root)/network/dtls/mbedtls/mbedtls.mk
    endif

endif

