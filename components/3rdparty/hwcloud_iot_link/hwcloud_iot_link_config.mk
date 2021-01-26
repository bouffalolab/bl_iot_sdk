
#HuaweiCloud iot link config 

######### HWCloud IoTLink ########################
#enable FREERTOS_BL OSAL
CONFIG_FREERTOS_BL_ENABLE := 1
#enable LinkLog
CONFIG_LINKLOG_ENABLE := 1
#enable TcpIP AL
CONFIG_TCIP_AL_ENABLE := 1
#enable Lwip_BL
CONFIG_LWIP_BL_ENABLE := 1
#enable linkqueue
CONFIG_LINKQUEUE_ENABLE := 1
#enable cJSON 
#Attention: use cJSON in BLSDK
CONFIG_CJSON_ENABLE := 0
######### OC-LWM2M ########################
#enable LWM2M_AL
CONFIG_LWM2M_AL_ENABLE := 0
#enable WAKAAMALWM2M
CONFIG_WAKAAMALWM2M_ENABLE := 0
#enable OCLWM2M
CONFIG_OCLWM2M_ENABLE := 0
#enable OCLWM2MTINY
CONFIG_OCLWM2MTINY_ENABLE := 0
######### OC-MQTT ########################
#enable DTLS AL
CONFIG_DTLS_AL_ENABLE := 1
#enable mbedtls
CONFIG_MBEDTLS_ENABLE := 1
#enable mbedtls psk
CONFIG_MBEDTLS_PSK := 1
#enable MQTT AL
CONFIG_MQTT_AL_ENABLE := 1
#enable paho mqtt
CONFIG_PAHO_MQTT := 1
#enable oc mqtt
CONFIG_OCMQTT_ENABLE := 1
#enable oc_mqttv5 profile
CONFIG_OC_MQTTV5_PROFILE := 1
#enable oc tiny mqttv5
CONFIG_OC_TINYMQTTV5_ENABLE := 1
######### OC-COAP ########################
#enable COAP_AL
CONFIG_COAP_AL_ENABLE := 0
#enable LIBCOAP
CONFIG_LIBCOAP_ENABLE := 0
#enable OCCOAP
CONFIG_OCCOAP_ENABLE := 0
#enable OCCOAPTINY
CONFIG_OCCOAPTINY_ENABLE := 0
######### DEMOS ########################
#enable link demo
CONFIG_LINKDEMO_ENABLE := 1
#enable user demo
# Attention: Only one type of demo can be selected when compiling
CONFIG_USERDEMO_LWM2M_ENABLE := 0
CONFIG_USERDEMO_MQTT_ENABLE := 1
CONFIG_USERDEMO_COAP_ENABLE := 0
###
