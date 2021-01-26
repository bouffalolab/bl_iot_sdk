# Hwcloud Makefile
#
include $(COMPONENT_PATH)/hwcloud_iot_link_config.mk

######### HWCLOUD_ADD_INCLUDEDIRS ########################
HWCLOUD_ADD_INCLUDEDIRS += ./           \
							iot_link    \
							iot_link/inc    \
							iot_link/link_misc    \
							iot_link/network    \
							iot_link/oc    \
							

#enable FREERTOS_BL OSAL
ifeq ($(CONFIG_FREERTOS_BL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/os/osal \
							iot_link/os/freertos_bl
endif
#enable LinkLog
ifeq ($(CONFIG_LINKLOG_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/link_log
endif
#enable linkqueue
ifeq ($(CONFIG_LINKQUEUE_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/hwqueue
endif
#enable cJSON
ifeq ($(CONFIG_CJSON_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/cJSON
endif
#enable TcpIP AL
ifeq ($(CONFIG_TCIP_AL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/tcpip    \
							iot_link/network/tcpip/sal    
    #enable Lwip_BL
    ifeq ($(CONFIG_LWIP_BL_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/tcpip/lwip_bl_socket
    endif
endif
#enable OCLWM2M
ifeq ($(CONFIG_OCLWM2M_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_lwm2m  \
                           iot_link/oc/oc_lwm2m/oc_lwm2m_al  
    #enable OCLWM2MTINY
    ifeq ($(CONFIG_OCLWM2MTINY_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_lwm2m/atiny_lwm2m
    endif
endif

#enable LWM2M_AL
ifeq ($(CONFIG_LWM2M_AL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/lwm2m    \
                           iot_link/network/lwm2m/lwm2m_al
    #enable WAKAAMALWM2M
    ifeq ($(CONFIG_WAKAAMALWM2M_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/lwm2m/wakaama_lwm2m   \
                                   iot_link/network/lwm2m/wakaama_lwm2m    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13
    endif
endif
#enable DTLS AL
ifeq ($(CONFIG_DTLS_AL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/dtls   \
                            iot_link/network/dtls/dtls_al
endif
#enable mbedtls
ifeq ($(CONFIG_MBEDTLS_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/dtls/mbedtls/mbedtls_port
endif
#enable MQTT AL
ifeq ($(CONFIG_MQTT_AL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/mqtt    \
                            iot_link/network/mqtt/mqtt_al
    #enable paho mqtt
    ifeq ($(CONFIG_PAHO_MQTT),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/mqtt/paho_mqtt   \
                                   iot_link/network/mqtt/paho_mqtt/port    \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTClient-C/src   
    endif
endif
#enable oc mqtt
ifeq ($(CONFIG_OCMQTT_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_mqtt  \
                           iot_link/oc/oc_mqtt/oc_mqtt_al
    #enable oc_mqttv5 profile
    ifeq ($(CONFIG_OC_MQTTV5_PROFILE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_mqtt/oc_mqtt_profile_v5  
    endif
    #enable oc tiny mqttv5
    ifeq ($(CONFIG_OC_TINYMQTTV5_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_mqtt/oc_mqtt_tiny_v5
    endif
endif
#enable COAP_AL
ifeq ($(CONFIG_COAP_AL_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/coap  \
                            iot_link/network/coap/coap_al
    #enable LIBCOAP
    ifeq ($(CONFIG_LIBCOAP_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/network/coap/libcoap   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/include   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/include/coap2   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/src   \
                                    iot_link/network/coap/libcoap/adapter   \
                                    iot_link/network/coap/libcoap/adapter/port   \
                                    iot_link/network/coap/libcoap/adapter/oc   
    endif
endif
#enable OCCOAP
ifeq ($(CONFIG_OCCOAP_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_coap   \
                            iot_link/oc/oc_coap/oc_coap_al
    #enable OCCOAPTINY
    ifeq ($(CONFIG_OCCOAPTINY_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/oc/oc_coap/atiny_coap
    endif
endif

#max.su

#enable link demo
ifeq ($(CONFIG_LINKDEMO_ENABLE),1)
HWCLOUD_ADD_INCLUDEDIRS += iot_link/demos 
    ifeq ($(CONFIG_USERDEMO_LWM2M_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/demos/oc_agriculture_template
    endif
    ifeq ($(CONFIG_USERDEMO_MQTT_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/demos/oc_mqtt_demo
    endif
    ifeq ($(CONFIG_USERDEMO_COAP_ENABLE),1)
        HWCLOUD_ADD_INCLUDEDIRS += iot_link/demos/oc_agriculture_template
    endif
endif


############ HWCLOUD_PRIV_INCLUDEDIRS #####################
HWCLOUD_PRIV_INCLUDEDIRS += 

############ HWCLOUD_SRCS #####################
HWCLOUD_SRCS += example_hwcloud_iot_link.c   \
				iot_link/link_main.c    \
				iot_link/link_misc/link_random.c   \
				iot_link/link_misc/link_ring_buffer.c   \
				iot_link/link_misc/link_string.c   \


#enable FREERTOS_BL OSAL
ifeq ($(CONFIG_FREERTOS_BL_ENABLE),1)
HWCLOUD_SRCS += iot_link/os/osal/osal.c   \
				iot_link/os/freertos_bl/freertos_bl_imp.c
endif
#enable LinkLog
ifeq ($(CONFIG_LINKLOG_ENABLE),1)
HWCLOUD_SRCS += iot_link/link_log/link_log.c
endif
#enable linkqueue
ifeq ($(CONFIG_LINKQUEUE_ENABLE),1)
HWCLOUD_SRCS += iot_link/hwqueue/hwqueue.c
endif
#enable cJSON
ifeq ($(CONFIG_CJSON_ENABLE),1)
HWCLOUD_SRCS += iot_link/cJSON/cJSON.c
endif
#enable TcpIP AL
ifeq ($(CONFIG_TCIP_AL_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/tcpip/sal/sal.c   \
				iot_link/network/tcpip/sal/sal_netdb.c
    #enable Lwip_BL
	ifeq ($(CONFIG_LWIP_BL_ENABLE),1)
        HWCLOUD_SRCS += iot_link/network/tcpip/lwip_bl_socket/lwip_bl_socket_imp.c
    endif
endif
#enable OCLWM2M
ifeq ($(CONFIG_OCLWM2M_ENABLE),1)
HWCLOUD_SRCS += iot_link/oc/oc_lwm2m/oc_lwm2m_al/oc_lwm2m_al.c
    #enable OCLWM2MTINY
    ifeq ($(CONFIG_OCLWM2MTINY_ENABLE),1)
        HWCLOUD_SRCS += iot_link/oc/oc_lwm2m/atiny_lwm2m/agent_lwm2m.c
    endif
endif
#enable LWM2M_AL
ifeq ($(CONFIG_LWM2M_AL_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/lwm2m/lwm2m_al/lwm2m_al.c
    #enable WAKAAMALWM2M
    ifeq ($(CONFIG_WAKAAMALWM2M_ENABLE),1)
        HWCLOUD_SRCS += iot_link/network/lwm2m/wakaama_lwm2m/port/connection.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_cmd_ioctl.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_port.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_rpt.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_uri.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_access_control.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_binary_app_data_container.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_connectivity_moni.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_connectivity_stat.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_device.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_firmware.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_location.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_security.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/object_server.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/platform_adapter.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port/util_timer.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared/commandline.c   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/block1.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/bootstrap.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/data.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/discover.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/json.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/liblwm2m.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/lwm2m_utils.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/management.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/objects.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/observe.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/packet.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/registration.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/tlv.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/transaction.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/uri.c    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/wakaama_list.c    \
								   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13/er-coap-13.c
                                   #iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_fota_manager.c   
                                   #iot_link/network/lwm2m/wakaama_lwm2m/port/lwm2m_fota_state.c   
                                   #iot_link/network/lwm2m/wakaama_lwm2m/port/firmware_update.c   
    endif
endif
#enable DTLS AL
ifeq ($(CONFIG_DTLS_AL_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/dtls/dtls_al/dtls_al.c
endif
#enable mbedtls
ifeq ($(CONFIG_MBEDTLS_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/dtls/mbedtls/mbedtls_port/dtls_interface.c   \
                iot_link/network/dtls/mbedtls/mbedtls_port/entropy_hardware_poll.c      \
                iot_link/network/dtls/mbedtls/mbedtls_port/mbed_port.c      \
                iot_link/network/dtls/mbedtls/mbedtls_port/net_sockets_alt.c      \
                iot_link/network/dtls/mbedtls/mbedtls_port/timing_alt.c      
endif
#enable MQTT AL
ifeq ($(CONFIG_MQTT_AL_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/mqtt/mqtt_al/mqtt_al.c
    #enable paho mqtt
    ifeq ($(CONFIG_PAHO_MQTT),1)
        HWCLOUD_SRCS +=            iot_link/network/mqtt/paho_mqtt/port/paho_mqtt_port.c    \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTConnectClient.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTConnectServer.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTDeserializePublish.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTFormat.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTPacket.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTSerializePublish.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTSubscribeClient.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTSubscribeServer.c  \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTUnsubscribeClient.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src/MQTTUnsubscribeServer.c   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTClient-C/src/MQTTClient.c
    endif
endif
#enable oc mqtt
ifeq ($(CONFIG_OCMQTT_ENABLE),1)
HWCLOUD_SRCS += iot_link/oc/oc_mqtt/oc_mqtt_al/oc_mqtt_al.c
    #enable oc_mqttv5 profile
    ifeq ($(CONFIG_OC_MQTTV5_PROFILE),1)
        HWCLOUD_SRCS +=             iot_link/oc/oc_mqtt/oc_mqtt_profile_v5/oc_mqtt_profile.c   \
                                    iot_link/oc/oc_mqtt/oc_mqtt_profile_v5/oc_mqtt_profile_package.c
    endif
    #enable oc tiny mqttv5
    ifeq ($(CONFIG_OC_TINYMQTTV5_ENABLE),1)
        HWCLOUD_SRCS += iot_link/oc/oc_mqtt/oc_mqtt_tiny_v5/hmac.c  \
                        iot_link/oc/oc_mqtt/oc_mqtt_tiny_v5/oc_mqtt_tiny.c
    endif
endif
#enable COAP_AL
ifeq ($(CONFIG_COAP_AL_ENABLE),1)
HWCLOUD_SRCS += iot_link/network/coap/coap_al/coap_al.c
    #enable LIBCOAP
    ifeq ($(CONFIG_LIBCOAP_ENABLE),1)
        HWCLOUD_SRCS += iot_link/network/coap/libcoap/libcoap-4.2.0/src/address.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/async.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/block.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/coap_debug.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/coap_event.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/coap_hashkey.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/coap_session.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/encode.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/net.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/option.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/pdu.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/resource.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/str.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/subscribe.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/uri.c   \
                        iot_link/network/coap/libcoap/libcoap-4.2.0/src/coap_notls.c   \
                                    iot_link/network/coap/libcoap/adapter/port/coap_io.c   \
                                    iot_link/network/coap/libcoap/adapter/port/coap_mem.c   \
                                    iot_link/network/coap/libcoap/adapter/port/coap_time.c   \
                                    iot_link/network/coap/libcoap/adapter/oc/libcoap_port.c   
    endif
endif
#enable OCCOAP
ifeq ($(CONFIG_OCCOAP_ENABLE),1)
HWCLOUD_SRCS += iot_link/oc/oc_coap/oc_coap_al/oc_coap_al.c
    #enable OCCOAPTINY
    ifeq ($(CONFIG_OCCOAPTINY_ENABLE),1)
        HWCLOUD_SRCS += iot_link/oc/oc_coap/atiny_coap/atiny_coap.c
    endif
endif


#max.su

#enable link demo
ifeq ($(CONFIG_LINKDEMO_ENABLE),1)
HWCLOUD_SRCS += iot_link/demos/app_demo_main.c
    ifeq ($(CONFIG_USERDEMO_LWM2M_ENABLE),1)
        HWCLOUD_SRCS += iot_link/demos/oc_agriculture_template/oc_agriculture_template_lwm2m.c
    endif
    ifeq ($(CONFIG_USERDEMO_MQTT_ENABLE),1)
        HWCLOUD_SRCS += iot_link/demos/oc_mqtt_demo/oc_mqtt_water_meter.c
    endif
    ifeq ($(CONFIG_USERDEMO_COAP_ENABLE),1)
        HWCLOUD_SRCS += iot_link/demos/oc_agriculture_template/oc_agriculture_template_coap.c
    endif
endif



########### HWCLOUD_SRCDIRS ######################
HWCLOUD_SRCDIRS += ./          \
							iot_link    \
							iot_link/inc    \
							iot_link/link_misc    \
							iot_link/network    \
							iot_link/oc    \


#enable FREERTOS_BL OSAL
ifeq ($(CONFIG_FREERTOS_BL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/os/osal   \
					iot_link/os/freertos_bl
endif
#enable LinkLog
ifeq ($(CONFIG_LINKLOG_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/link_log
endif
#enable linkqueue
ifeq ($(CONFIG_LINKQUEUE_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/hwqueue
endif
#enable cJSON
ifeq ($(CONFIG_CJSON_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/cJSON
endif
#enable TcpIP AL
ifeq ($(CONFIG_TCIP_AL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/tcpip    \
					iot_link/network/tcpip/sal    
    #enable Lwip_BL
    ifeq ($(CONFIG_LWIP_BL_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/network/tcpip/lwip_bl_socket
    endif
endif
#enable OCLWM2M
ifeq ($(CONFIG_OCLWM2M_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/oc/oc_lwm2m  \
                           iot_link/oc/oc_lwm2m/oc_lwm2m_al  
    #enable OCLWM2MTINY
    ifeq ($(CONFIG_OCLWM2MTINY_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/oc/oc_lwm2m/atiny_lwm2m
    endif
endif

#enable LWM2M_AL
ifeq ($(CONFIG_LWM2M_AL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/lwm2m    \
                           iot_link/network/lwm2m/lwm2m_al
    #enable WAKAAMALWM2M
    ifeq ($(CONFIG_WAKAAMALWM2M_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/network/lwm2m/wakaama_lwm2m   \
                                   iot_link/network/lwm2m/wakaama_lwm2m    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/port   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/examples/shared   \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core    \
                                   iot_link/network/lwm2m/wakaama_lwm2m/wakaama-master/core/er-coap-13
    endif
endif
#enable DTLS AL
ifeq ($(CONFIG_DTLS_AL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/dtls   \
                            iot_link/network/dtls/dtls_al
endif
#enable mbedtls
ifeq ($(CONFIG_MBEDTLS_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/dtls/mbedtls/mbedtls_port
endif
#enable MQTT AL
ifeq ($(CONFIG_MQTT_AL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/mqtt    \
                            iot_link/network/mqtt/mqtt_al
    #enable paho mqtt
    ifeq ($(CONFIG_PAHO_MQTT),1)
        HWCLOUD_SRCDIRS += iot_link/network/mqtt/paho_mqtt   \
                                   iot_link/network/mqtt/paho_mqtt/port    \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTPacket/src   \
                                   iot_link/network/mqtt/paho_mqtt/paho/MQTTClient-C/src   
    endif
endif
#enable oc mqtt
ifeq ($(CONFIG_OCMQTT_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/oc/oc_mqtt  \
                           iot_link/oc/oc_mqtt/oc_mqtt_al
    #enable oc_mqttv5 profile
    ifeq ($(CONFIG_OC_MQTTV5_PROFILE),1)
        HWCLOUD_SRCDIRS += iot_link/oc/oc_mqtt/oc_mqtt_profile_v5  
    endif
    #enable oc tiny mqttv5
    ifeq ($(CONFIG_OC_TINYMQTTV5_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/oc/oc_mqtt/oc_mqtt_tiny_v5
    endif
endif
#enable COAP_AL
ifeq ($(CONFIG_COAP_AL_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/network/coap  \
                            iot_link/network/coap/coap_al
    #enable LIBCOAP
    ifeq ($(CONFIG_LIBCOAP_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/network/coap/libcoap   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/include   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/include/coap2   \
                                    iot_link/network/coap/libcoap/libcoap-4.2.0/src   \
                                    iot_link/network/coap/libcoap/adapter   \
                                    iot_link/network/coap/libcoap/adapter/port   \
                                    iot_link/network/coap/libcoap/adapter/oc   
    endif
endif
#enable OCCOAP
ifeq ($(CONFIG_OCCOAP_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/oc/oc_coap   \
                            iot_link/oc/oc_coap/oc_coap_al
    #enable OCCOAPTINY
    ifeq ($(CONFIG_OCCOAPTINY_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/oc/oc_coap/atiny_coap
    endif
endif


#max.su

#enable link demo
ifeq ($(CONFIG_LINKDEMO_ENABLE),1)
HWCLOUD_SRCDIRS += iot_link/demos 
    ifeq ($(CONFIG_USERDEMO_LWM2M_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/demos/oc_agriculture_template
    endif
    ifeq ($(CONFIG_USERDEMO_MQTT_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/demos/oc_mqtt_demo
    endif
    ifeq ($(CONFIG_USERDEMO_COAP_ENABLE),1)
        HWCLOUD_SRCDIRS += iot_link/demos/oc_agriculture_template
    endif
endif

########## CFLAGS #######################
#enable FREERTOS_BL OSAL
ifeq ($(CONFIG_FREERTOS_BL_ENABLE), 1)
CFLAGS += -D CONFIG_FREERTOS_BL_ENABLE=1
endif
#enable LinkLog
ifeq ($(CONFIG_LINKLOG_ENABLE), 1)
CFLAGS += -D CONFIG_LINK_LOG_ENABLE=1 -D CONFIG_LINKLOG_ENABLE=1
endif
#enable cJSON
ifeq ($(CONFIG_CJSON_ENABLE), 1)
CFLAGS += -D CONFIG_JSON_ENABLE=1 -D CONFIG_CJSON_ENABLE=1
endif
#enable TcpIP AL
ifeq ($(CONFIG_TCIP_AL_ENABLE), 1)
CFLAGS += -D CONFIG_TCIP_AL_ENABLE=1
endif
#enable OCLWM2M
ifeq ($(CONFIG_OCLWM2M_ENABLE),1)
CFLAGS += -D CONFIG_OCLWM2M_ENABLE=1
    #enable OCLWM2MTINY
    ifeq ($(CONFIG_OCLWM2MTINY_ENABLE),1)
        CFLAGS += -D CONFIG_OC_LWM2M_AGENT_ENABLE=1 -D CONFIG_OCLWM2MTINY_ENABLE=1
    endif
endif
#enable LWM2M_AL
ifeq ($(CONFIG_LWM2M_AL_ENABLE),1)
CFLAGS += 
    #enable WAKAAMALWM2M
    ifeq ($(CONFIG_WAKAAMALWM2M_ENABLE),1)
        CFLAGS += -D LWM2M_LITTLE_ENDIAN -D LWM2M_CLIENT_MODE -D LWM2M_WITH_LOGS -D CONFIG_LWM2M_AL_ENABLE=1
    endif
endif
#enable DTLS AL
ifeq ($(CONFIG_DTLS_AL_ENABLE), 1)
CFLAGS += -D CONFIG_DTLS_AL_ENABLE
endif
#enable mbedtls
ifeq ($(CONFIG_MBEDTLS_ENABLE),1)
CFLAGS += -D WITH_DTLS -D CONFIG_MBEDTLS_ENABLE
    #enable USE_MBEDTLS_AES_ROM_TABLES
    ifeq (1,1)
        CFLAGS += -D MBEDTLS_AES_ROM_TABLES
    endif
    #enable mbedtls psk
    ifeq ($(CONFIG_MBEDTLS_PSK),1)
        CFLAGS += -D MBEDTLS_CONFIG_FILE=\"los_mbedtls_config.h\"   \
                  -D CONFIG_DTLS_MBEDTLS_PSK   -D CFG_MBEDTLS_MODE=PSK -D CONFIG_MBEDTLS_PSK
    endif
endif
#enable MQTT AL
ifeq ($(CONFIG_MQTT_AL_ENABLE),1)
CFLAGS += -D CONFIG_MQTT_AL_ENABLE
    #enable paho mqtt
    ifeq ($(CONFIG_PAHO_MQTT),1)
        CFLAGS += -D MQTTCLIENT_PLATFORM_HEADER=paho_osdepends.h -D CONFIG_MQTT_PAHO_ENABLE=1 -D CONFIG_PAHO_MQTT
    endif
    #enable oc tiny mqttv5
    ifeq ($(CONFIG_OC_TINYMQTTV5_ENABLE),1)
        CFLAGS += -D CONFIG_OC_MQTT_TINY_ENABLE=1  -D CONFIG_OC_TINYMQTTV5_ENABLE
    endif
endif
#enable oc mqtt
ifeq ($(CONFIG_OCMQTT_ENABLE), 1)
CFLAGS += -D CONFIG_OCMQTT_ENABLE
    #enable oc_mqttv5 profile
    ifeq ($(CONFIG_OC_MQTTV5_PROFILE),1)
        CFLAGS += -D CONFIG_OC_MQTTV5_PROFILE
    endif
endif
#enable COAP_AL
ifeq ($(CONFIG_COAP_AL_ENABLE),1)
CFLAGS += -D CONFIG_COAP_AL_ENABLE
    #enable LIBCOAP
    ifeq ($(CONFIG_LIBCOAP_ENABLE),1)
        CFLAGS += -D CONFIG_LIBCOAP_ENABLE
    endif
endif
#enable OCCOAP
ifeq ($(CONFIG_OCCOAP_ENABLE),1)
CFLAGS += -D CONFIG_OCCOAP_ENABLE
    #enable OCCOAPTINY
    ifeq ($(CONFIG_OCCOAPTINY_ENABLE),1)
        CFLAGS += -D CONFIG_ATINY_COAP_ENABLE=1  -D CONFIG_OCCOAPTINY_ENABLE
    endif
endif

#max.su


#enable link demo
ifeq ($(CONFIG_LINKDEMO_ENABLE),1)
CFLAGS += -D CONFIG_LINKDEMO_ENABLE=1
endif



######### HWCLOUD_LDFLAGS ########################
HWCLOUD_LDFLAGS += 
#enable cJSON
ifeq ($(CONFIG_CJSON_ENABLE), 1)
HWCLOUD_LDFLAGS += -u _printf_float
endif
#enable oc tiny mqttv5
ifeq ($(CONFIG_OC_TINYMQTTV5_ENABLE), 1)
HWCLOUD_LDFLAGS += -u _printf_float
endif
#enable OCCOAPTINY
ifeq ($(CONFIG_OCCOAPTINY_ENABLE), 1)
HWCLOUD_LDFLAGS += -u _printf_float
endif


# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += $(HWCLOUD_ADD_INCLUDEDIRS)
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := $(HWCLOUD_PRIV_INCLUDEDIRS)
## This component's src
COMPONENT_SRCS := $(HWCLOUD_SRCS)
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
## This component's src dir
COMPONENT_SRCDIRS := $(HWCLOUD_SRCDIRS)
##
#CPPFLAGS +=
COMPONENT_LDFLAGS := $(HWCLOUD_LDFLAGS)
