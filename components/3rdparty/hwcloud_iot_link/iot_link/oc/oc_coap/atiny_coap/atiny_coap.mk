################################################################################
# this is used for compile the oc mqtt implement
# please add the corresponding file to C_SOURCES C_INCLUDES C_DEFS
################################################################################

#uptils now, we only support the atiny_mqtt mode, you could add more implement as you wish
vpath %.c $(iot_link_root)/oc/oc_coap/atiny_coap

atiny_coap_src = ${wildcard $(iot_link_root)/oc/oc_coap/atiny_coap/*.c}
C_SOURCES += $(atiny_coap_src)

atiny_coap_inc = -I $(iot_link_root)/oc/oc_coap/atiny_coap
C_INCLUDES += $(atiny_coap_inc)

atiny_coap_defs = -D CONFIG_ATINY_COAP_ENABLE=1    
C_DEFS += $(atiny_coap_defs)

LDFLAGS += -u _printf_float
