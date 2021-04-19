# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include \
							 include/exports \
							 sdk_src/internal_inc 

qcloud_iot_src := sdk_src \
				  platform  
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := platform/HAL_Device_freertos.c \
                  platform/HAL_DTLS_mbedtls.c \
                  platform/HAL_OS_freertos.c \
                  platform/HAL_TCP_lwip.c \
                  platform/HAL_Timer_freertos.c \
                  platform/HAL_TLS_mbedtls.c \
				  platform/HAL_UDP_lwip.c \
				  platform/HAL_Airkiss.c \
				  platform/HAL_BTCombo_config.c \
				  platform/HAL_Wifi_api.c \
				  platform/HAL_Soft_ap.c \
				  platform/HAL_Smart_config.c \
				  platform/HAL_Simple_config.c \
				  sdk_src/qcloud_wifi_config.c \
				  sdk_src/qcloud_wifi_config_comm_service.c \
				  sdk_src/qcloud_wifi_config_device_bind.c \
				  sdk_src/qcloud_wifi_config_error_handle.c \
				  sdk_src/qcloud_wifi_config_log_handle.c \
				  sdk_src/asr_client.c \
				  sdk_src/data_template_action.c \
				  sdk_src/data_template_client.c \
				  sdk_src/data_template_client_common.c \
				  sdk_src/data_template_client_json.c \
				  sdk_src/data_template_client_manager.c \
				  sdk_src/data_template_event.c \
				  sdk_src/dynreg.c \
				  sdk_src/json_parser.c \
				  sdk_src/json_token.c \
				  sdk_src/mqtt_client.c \
				  sdk_src/mqtt_client_common.c \
				  sdk_src/mqtt_client_connect.c \
				  sdk_src/mqtt_client_net.c \
				  sdk_src/mqtt_client_publish.c \
				  sdk_src/mqtt_client_subscribe.c \
				  sdk_src/mqtt_client_unsubscribe.c \
				  sdk_src/mqtt_client_yield.c \
				  sdk_src/network_interface.c \
				  sdk_src/network_socket.c  \
				  sdk_src/network_tls.c \
				  sdk_src/ota_client.c \
				  sdk_src/ota_fetch.c \
				  sdk_src/ota_lib.c \
				  sdk_src/ota_mqtt.c \
				  sdk_src/qcloud_iot_ca.c \
				  sdk_src/qcloud_iot_device.c \
				  sdk_src/qcloud_iot_log.c \
				  sdk_src/qutils_base64.c \
				  sdk_src/qutils_hmac.c \
				  sdk_src/qutils_list.c \
				  sdk_src/qutils_md5.c \
				  sdk_src/qutils_sha1.c \
				  sdk_src/resource_client.c \
				  sdk_src/service_mqtt.c \
				  sdk_src/qstring_utils.c \
				  sdk_src/qutils_aes.c \
				  sdk_src/qutils_httpc.c \
				  sdk_src/qutils_ringbuff.c \
				  sdk_src/qutils_timer.c \
				  sdk_src/qutils_url_download.c\
				  sdk_src/qutils_url_upload.c \
				  sdk_src/qutils_getopt.c
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS :=  $(qcloud_iot_src)
					 


