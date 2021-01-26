################################################################################
# this is used for compile the wakaama
################################################################################

vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m
vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port
vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master
vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared
vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core
vpath %.c $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13

WAKAAMA_COAP_SRC = \
        ${wildcard $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13/er-coap-13.c}
        C_SOURCES += $(WAKAAMA_COAP_SRC)

WAKAMA_LWM2MSRC = \
        ${wildcard $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core/*.c} \
        ${wildcard $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared/*.c}
        C_SOURCES += $(WAKAMA_LWM2MSRC)

WAKAAMA_COAP_INC = \
        -I $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13
        C_INCLUDES += $(WAKAAMA_COAP_INC)
WAKAMA_LWM2MINC = \
        -I $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/core \
        -I $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared
        C_INCLUDES += $(WAKAMA_LWM2MINC)

WAKAAMA_PORT_SRC = ${wildcard $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port/*.c}

ifeq ($(CONFIG_FOTA_ENABLE), y)
    C_SOURCES += $(WAKAAMA_PORT_SRC)
    C_DEFS += -D CONFIG_FEATURE_FOTA
else
    WAKAAMA_PORT_SRC_NO_FOTA = \
    $(filter-out $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port/lwm2m_fota_manager.c \
    $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port/lwm2m_fota_state.c \
    $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port/firmware_update.c, $(WAKAAMA_PORT_SRC))

    C_SOURCES += $(WAKAAMA_PORT_SRC_NO_FOTA)
endif

C_INCLUDES += -I $(iot_link_root)/network/lwm2m/wakaama_lwm2m/port

C_DEFS += -D LWM2M_LITTLE_ENDIAN -D LWM2M_CLIENT_MODE -D LWM2M_WITH_LOGS
