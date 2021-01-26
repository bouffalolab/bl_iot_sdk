################################################################################
# this is used for compile the lwip
################################################################################

#configure the lwip itself
#######################################
# use ethernet
#######################################
WITH_LWIP  := y

#######################################
# IPv4
#######################################
WITH_IPV4 := y

#######################################
# IPv6
#######################################
WITH_IPV6 := n

#######################################
# If Use TCP, when use lwm2m,not need tcp
#######################################
USE_LWIP_TCP := y

ifeq ($(WITH_IPV4), n)
C_DEFS += -DLWIP_IPV4=0
else
C_DEFS += -DLWIP_IPV4=1
endif

ifeq ($(WITH_IPV6), y)
C_DEFS += -DLWIP_IPV6=1
else
C_DEFS += -DLWIP_IPV6=0
endif

LWIP_INC = \
        -I $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/include
        C_INCLUDES += $(LWIP_INC)

LWIP_PORT_INC = \
        -I $(iot_link_root)/network/tcpip/lwip_socket/lwip_port \
        -I $(iot_link_root)/network/tcpip/lwip_socket/lwip_port/arch \
        -I $(iot_link_root)/network/tcpip/lwip_socket/lwip_port/OS
        C_INCLUDES += $(LWIP_PORT_INC)

LWIP_SRC =  \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/api/*.c} \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/core/ipv4/*.c} \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/core/ipv6/*.c} \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/core/*.c} \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip-2.0.3/src/netif/ethernet.c}
        C_SOURCES += $(LWIP_SRC)

LWIP_PORT_SRC = \
        ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip_port/OS/*.c}
        C_SOURCES += $(LWIP_PORT_SRC)


C_DEFS += \
    -DCONFIG_WITH_LWIP \
    -DLWIP_DEBUG \
    -D LWIP_TIMEVAL_PRIVATE=0 

    ifeq ($(USE_LWIP_TCP), y)
        C_DEFS += -DLWIP_TCP=1
    else
        C_DEFS += -DLWIP_TCP=0
    endif
    
LWIP_IMP_SOURCE  = ${wildcard $(iot_link_root)/network/tcpip/lwip_socket/lwip_imp/*.c}
C_SOURCES += $(LWIP_IMP_SOURCE)
		
LWIP_IMP_INC = -I $(iot_link_root)/network/tcpip/lwip_socket/lwip_imp
C_INCLUDES += $(LWIP_IMP_INC)

C_DEFS += -D CONFIG_LWIP_ENABLE=1
