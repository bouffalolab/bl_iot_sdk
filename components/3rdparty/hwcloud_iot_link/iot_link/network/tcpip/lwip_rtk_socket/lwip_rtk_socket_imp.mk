################################################################################
# this is used for compile the macos socket
################################################################################

#configure the macos socket itself

vpath %.c $(iot_link_root)/network/tcpip/lwip_rtk_socket

LWIP_RTK_SOCKET_IMP_SOURCE  = ${wildcard $(iot_link_root)/network/tcpip/lwip_rtk_socket/*.c}
C_SOURCES += $(LWIP_RTK_SOCKET_IMP_SOURCE)
		
LWIP_RTK_SOCKET_IMP_INC = -I $(iot_link_root)/network/tcpip/lwip_rtk_socket
C_INCLUDES += $(LWIP_RTK_SOCKET_IMP_INC)

C_DEFS += -D CONFIG_LWIP_RTK_SOCKET_ENABLE=1 
 