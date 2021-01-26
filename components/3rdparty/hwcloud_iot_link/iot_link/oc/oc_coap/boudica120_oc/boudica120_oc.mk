BOUDICA120_SOURCE = ${wildcard $(iot_link_root)/oc/oc_coap/boudica120_oc/*.c} 
C_SOURCES += $(BOUDICA120_SOURCE)
        
BOUDICA120_INC = -I $(iot_link_root)/oc/oc_coap/boudica120_oc
C_INCLUDES += $(BOUDICA120_INC)

C_DEFS += -D CONFIG_OC_COAP_BOUDICA120_ENABLE=1