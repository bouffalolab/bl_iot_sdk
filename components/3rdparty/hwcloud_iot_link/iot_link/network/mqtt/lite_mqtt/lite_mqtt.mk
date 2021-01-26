################################################################################
# this is used for compile the mqtt lib
################################################################################

mqtt_sinn_src = \
        ${wildcard $(iot_link_root)/network/mqtt/lite_mqtt/mqtt_port/*.c} \
        ${wildcard $(iot_link_root)/network/mqtt/lite_mqtt/mqtt_sinn/*.c}
C_SOURCES += $(mqtt_sinn_src)

mqtt_sinn_inc = \
        -I $(iot_link_root)/network/mqtt/lite_mqtt/mqtt_sinn \
        -I $(iot_link_root)/network/mqtt/lite_mqtt/mqtt_port
C_INCLUDES += $(mqtt_sinn_inc)

C_DEFS += -D CONFIG_MQTT_SINN_ENABLE=1



