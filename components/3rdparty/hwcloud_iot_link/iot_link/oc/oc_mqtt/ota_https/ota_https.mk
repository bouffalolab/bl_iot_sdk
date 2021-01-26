################################################################################
# this is used for compile the atiny_mqtt
################################################################################
C_SOURCES += ${wildcard $(iot_link_root)/oc/oc_mqtt/ota_https/*.c}
C_INCLUDES += -I $(iot_link_root)/oc/oc_mqtt/ota_https

C_DEFS += -D CONFIG_OC_MQTT_OTA_ENABLE=1

