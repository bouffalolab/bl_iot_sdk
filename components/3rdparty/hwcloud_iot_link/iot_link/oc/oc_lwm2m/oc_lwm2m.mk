################################################################################
# this is used for compile the oc lwm2m agent
################################################################################
vpath %.c $(iot_link_root)/oc/oc_lwm2m
vpath %.c $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m_al


ifeq ($(CONFIG_OCLWM2M_ENABLE), y)

    C_SOURCES += $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m_al/oc_lwm2m_al.c     		
    C_INCLUDES += -I $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m_al

    ifeq ($(CONFIG_OCLWM2MTINY_ENABLE), y)
    	include $(iot_link_root)/oc/oc_lwm2m/atiny_lwm2m/atiny_lwm2m.mk
    else ifeq ($(CONFIG_BOUDICA150_ENABLE),y)
    	include $(iot_link_root)/oc/oc_lwm2m/boudica150_oc/boudica150_oc.mk            
    endif
    
    ifeq ($(CONFIG_OCLWM2M_DEMO_DTLS_ENABLE),y)
        C_SOURCES += $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m_al/oc_dtls_lwm2m_demo.c     
    else ifeq ($(CONFIG_OCLWM2M_DEMO_ENABLE),y)
        C_SOURCES += $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m_al/oc_lwm2m_demo.c                  
    endif
        
endif