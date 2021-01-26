################################################################################
# this is used for compile network
################################################################################
#configure the tcpip for the iot_link

vpath %.c $(iot_link_root)/network

include $(iot_link_root)/network/tcpip/tcpip.mk

#configure the dtls for the iot link
include $(iot_link_root)/network/dtls/dtls.mk

#configure the mqtt
include $(iot_link_root)/network/mqtt/mqtt.mk

#configure the lwm2m
include $(iot_link_root)/network/lwm2m/lwm2m.mk

#configure the coap
include $(iot_link_root)/network/coap/coap.mk


