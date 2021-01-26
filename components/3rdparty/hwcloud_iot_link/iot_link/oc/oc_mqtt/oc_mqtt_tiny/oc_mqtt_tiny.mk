################################################################################
# this is used for compile the atiny_mqtt
################################################################################
OC_MQTT_TINY_SRC = ${wildcard $(iot_link_root)/oc/oc_mqtt/oc_mqtt_tiny/*.c}
C_SOURCES += $(OC_MQTT_TINY_SRC)

OC_MQTT_TINY_INC = -I $(iot_link_root)/oc/oc_mqtt/oc_mqtt_tiny
C_INCLUDES += $(OC_MQTT_TINY_INC)

C_DEFS += -D CONFIG_OC_MQTT_TINY_ENABLE=1

LDFLAGS += -u _printf_float
