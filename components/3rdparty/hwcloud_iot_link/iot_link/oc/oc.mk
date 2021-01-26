################################################################################
# this is used for compile the oceanconnect
################################################################################

vpath %.c $(iot_link_root)/oc

#configure the oc mqtt
include $(iot_link_root)/oc/oc_mqtt/oc_mqtt.mk

#configure the oc lwm2m
include $(iot_link_root)/oc/oc_lwm2m/oc_lwm2m.mk

#configure the oc coap
include $(iot_link_root)/oc/oc_coap/oc_coap.mk


