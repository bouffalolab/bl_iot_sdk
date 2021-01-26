BOUDICA150_SOURCE = ${wildcard $(iot_link_root)/oc/oc_lwm2m/boudica150_oc/*.c} 
C_SOURCES += $(BOUDICA150_SOURCE)
        
BOUDICA150_INC = -I $(iot_link_root)/oc/oc_lwm2m/boudica150_oc
C_INCLUDES += $(BOUDICA150_INC)

C_DEFS += -D CONFIG_OC_LWM2M_BOUDICA150_ENABLE=1