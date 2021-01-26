################################################################################
# this is used for compile the coap
################################################################################
vpath %.c $(iot_link_root)/network/coap
vpath %.c $(iot_link_root)/network/coap/coap_al

ifeq ($(CONFIG_COAP_AL_ENABLE), y)

    C_SOURCES += ${wildcard $(iot_link_root)/network/coap/coap_al/*.c}  		
    C_INCLUDES += -I $(iot_link_root)/network/coap/coap_al
        
    ifeq ($(CONFIG_LITECOAP_ENABLE), y)
        include $(iot_link_root)/network/coap/lite_coap/lite_coap.mk
    else ifeq ($(CONFIG_LIBCOAP_ENABLE), y)
        include $(iot_link_root)/network/coap/libcoap/libcoap.mk
    endif
     
endif