################################################################################
# this is used for compile the atiny_mqtt
################################################################################

vpath %.c $(iot_link_root)/oc/oc_mqtt/oc_mqtt_tiny_v5


C_SOURCES += ${wildcard $(iot_link_root)/oc/oc_mqtt/oc_mqtt_tiny_v5/*.c}
C_INCLUDES += -I $(iot_link_root)/oc/oc_mqtt/oc_mqtt_tiny_v5

C_DEFS += -D CONFIG_OC_MQTT_TINY_ENABLE=1

