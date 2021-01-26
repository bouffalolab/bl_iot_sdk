################################################################################
# this is used for compile the macos socket
################################################################################

#configure the macos socket itself
RTK8710_SOCKET_IMP_SOURCE  = ${wildcard $(iot_link_root)/network/tcpip/rtk8710_socket/*.c}
C_SOURCES += $(RTK8710_SOCKET_IMP_SOURCE)
		
RTK8710_SOCKET_IMP_INC = -I $(iot_link_root)/network/tcpip/rtk8710_socket
C_INCLUDES += $(RTK8710_SOCKET_IMP_INC)

C_DEFS += -D CONFIG_RTK8710_SOCKET_ENABLE=1
