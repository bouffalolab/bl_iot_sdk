EC2X_SOURCE = ${wildcard $(iot_link_root)/oc/oc_mqtt/ec2x_oc/*.c}
C_SOURCES += $(EC2X_SOURCE)

EC2X_INC = -I $(iot_link_root)/oc/oc_mqtt/ec2x_oc

C_INCLUDES += $(EC2X_INC)
C_DEFS += -D CONFIG_OC_MQTT_EC2X_ENABLE=1

