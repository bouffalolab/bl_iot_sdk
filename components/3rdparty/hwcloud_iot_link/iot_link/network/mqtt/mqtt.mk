################################################################################
# this is used for compile the mqtt lib
################################################################################

vpath %.c $(iot_link_root)/network/mqtt
vpath %.c $(iot_link_root)/network/mqtt/mqtt_al


ifeq ($(CONFIG_MQTT_AL_ENABLE), y)

    C_SOURCES  += ${wildcard $(iot_link_root)/network/mqtt/mqtt_al/*.c}
    C_INCLUDES += -I $(iot_link_root)/network/mqtt/mqtt_al    
    
    ifeq ($(CONFIG_PAHO_MQTT), y)
    	include $(iot_link_root)/network/mqtt/paho_mqtt/paho_mqtt.mk
    endif	
    
    ifeq ($(CONFIG_LITE_MQTT), y)
    	include $(iot_link_root)/network/mqtt/lite_mqtt/lite_mqtt.mk
    endif	
       
endif

