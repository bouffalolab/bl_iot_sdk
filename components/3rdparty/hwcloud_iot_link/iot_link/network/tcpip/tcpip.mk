################################################################################
# this is used for compile the iotlink
################################################################################
vpath %.c $(iot_link_root)/network/tcpip
vpath %.c $(iot_link_root)/network/tcpip/sal
vpath %.c $(iot_link_root)/network/tcpip/lwip_rtk_socket

ifeq ($(CONFIG_TCIP_AL_ENABLE), y)

    C_SOURCES += ${wildcard $(iot_link_root)/network/tcpip/sal/*.c}    		
    C_INCLUDES += -I $(iot_link_root)/network/tcpip/sal
    C_DEFS += -D TCPIP_AL_ENABLE=1
   
    #now suport "lwip" and "linux"  "macos" socket
    ifeq ($(CONFIG_LWIP_ENABLE), y)
        include $(iot_link_root)/network/tcpip/lwip_socket/lwip_socket_imp.mk
    endif
        
    ifeq ($(CONFIG_LINUXSOCKET_ENABLE), y)
        include $(iot_link_root)/network/tcpip/linux_socket/linux_socket_imp.mk
    endif
    
    ifeq ($(CONFIG_MACOSSOCKET_ENABLE), y)
        include $(iot_link_root)/network/tcpip/macos_socket/macos_socket_imp.mk
    endif
    
    ifeq ($(CONFIG_ESP8266_ENABLE), y)
        include $(iot_link_root)/network/tcpip/esp8266_socket/esp8266_socket_imp.mk
    endif
    
    ifeq ($(CONFIG_RTK8710_ENABLE), y)
        include $(iot_link_root)/network/tcpip/rtk8710_socket/rtk8710_socket_imp.mk        
    endif

    ifeq ($(CONFIG_LWIP_RTK_ENABLE), y)
        include $(iot_link_root)/network/tcpip/lwip_rtk_socket/lwip_rtk_socket_imp.mk        
    endif

    
endif
