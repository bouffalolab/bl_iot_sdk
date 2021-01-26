################################################################################
# this is used for compile the OC_COAP
################################################################################
vpath %.c $(iot_link_root)/oc/oc_coap
vpath %.c $(iot_link_root)/oc/oc_coap/oc_coap_al

ifeq ($(CONFIG_OCCOAP_ENABLE), y)

    C_SOURCES += $(iot_link_root)/oc/oc_coap/oc_coap_al/oc_coap_al.c    
    C_INCLUDES += -I $(iot_link_root)/oc/oc_coap/oc_coap_al
        
    ifeq ($(CONFIG_OCCOAP_DEMO_DTLS_ENABLE),y)
        C_SOURCES += $(iot_link_root)/oc/oc_coap/oc_coap_al/oc_dtls_coap_demo.c
    else ifeq ($(CONFIG_OCCOAP_DEMO_ENABLE),y)
        C_SOURCES += $(iot_link_root)/oc/oc_coap/oc_coap_al/oc_coap_demo.c              
    endif
        
    ifeq ($(CONFIG_OCCOAPTINY_ENABLE), y)    
		include $(iot_link_root)/oc/oc_coap/atiny_coap/atiny_coap.mk
    else ifeq ($(CONFIG_BOUDICA120_ENABLE),y)
    	include $(iot_link_root)/oc/oc_coap/boudica120_oc/boudica120_oc.mk	
    endif

endif