vpath %.c $(iot_link_root)/oc/oc_lwm2m/atiny_lwm2m


OC_LWM2M_AGENT_SRC = \
        ${wildcard $(iot_link_root)/oc/oc_lwm2m/atiny_lwm2m/*.c}

C_SOURCES += $(OC_LWM2M_AGENT_SRC)

OC_LWM2M_ATINY_INC = -I $(iot_link_root)/oc/oc_lwm2m/atiny_lwm2m        
C_INCLUDES += $(OC_LWM2M_ATINY_INC)
C_DEFS += -D CONFIG_OC_LWM2M_AGENT_ENABLE=1