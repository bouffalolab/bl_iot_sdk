################################################################################
# this is used for compile the mqtt lib
################################################################################
vpath %.c $(iot_link_root)/network/coap/lite_coap
vpath %.c $(iot_link_root)/network/coap/lite_coap/src
vpath %.c $(iot_link_root)/network/coap/lite_coap/port

lite_coap_src = \
		${wildcard $(iot_link_root)/network/coap/lite_coap/src/*.c} \
		${wildcard $(iot_link_root)/network/coap/lite_coap/port/*.c}
        C_SOURCES += $(lite_coap_src)
        
lite_coap_inc = \
        -I $(iot_link_root)/network/coap/lite_coap/include
        C_INCLUDES += $(lite_coap_inc)
