################################################################################
# this is used for compile the lwm2m
################################################################################
vpath %.c $(iot_link_root)/network/lwm2m
vpath %.c $(iot_link_root)/network/lwm2m/lwm2m_al

ifeq ($(CONFIG_LWM2M_AL_ENABLE), y)

    C_SOURCES += ${wildcard $(iot_link_root)/network/lwm2m/lwm2m_al/*.c}    		
    C_INCLUDES += -I $(iot_link_root)/network/lwm2m/lwm2m_al
    
    ifeq ($(CONFIG_WAKAAMALWM2M_ENABLE), y)
        include $(iot_link_root)/network/lwm2m/wakaama_lwm2m/wakaama.mk
    else ifeq ($(CONFIG_WAKAAMARAW_ENABLE), y)
        include $(iot_link_root)/network/lwm2m/wakaama_raw/wakaama.mk
    else
    	#you could extend the lwm2m support implement
    endif
endif
