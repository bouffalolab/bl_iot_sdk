################################################################################
# this is used for compile the mqtt lib
################################################################################

vpath %.c $(iot_link_root)/network/mqtt/paho_mqtt
vpath %.c $(iot_link_root)/network/mqtt/paho_mqtt/port
vpath %.c $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTPacket/src
vpath %.c $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTClient-C/src/


mqtt_paho_src = \
		${wildcard $(iot_link_root)/network/mqtt/paho_mqtt/port/*.c} \
        ${wildcard $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTPacket/src/*.c} \
        $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTClient-C/src/MQTTClient.c
        C_SOURCES += $(mqtt_paho_src)
        
mqtt_paho_inc = \
        -I $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTClient-C/src \
		-I $(iot_link_root)/network/mqtt/paho_mqtt/paho/MQTTPacket/src \
		-I $(iot_link_root)/network/mqtt/paho_mqtt/port 

C_INCLUDES += $(mqtt_paho_inc)

mqtt_paho_defs = -D MQTTCLIENT_PLATFORM_HEADER=paho_osdepends.h -D CONFIG_MQTT_PAHO_ENABLE=1
C_DEFS += $(mqtt_paho_defs)
