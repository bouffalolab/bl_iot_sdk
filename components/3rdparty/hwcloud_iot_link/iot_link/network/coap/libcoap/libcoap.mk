
LIBCOAP_DIR			= $(iot_link_root)/network/coap/libcoap
LIBCOAP_BASE_DIR    = $(LIBCOAP_DIR)/libcoap-4.2.0
LIBCOAP_ADAPTER_DIR	= $(LIBCOAP_DIR)/adapter

LIBCOAP_SRC_DIR = $(LIBCOAP_BASE_DIR)/src

LIBCOAP_SRC = \
		$(LIBCOAP_SRC_DIR)/address.c \
		$(LIBCOAP_SRC_DIR)/async.c \
		$(LIBCOAP_SRC_DIR)/block.c \
		$(LIBCOAP_SRC_DIR)/coap_debug.c \
		$(LIBCOAP_SRC_DIR)/coap_event.c \
		$(LIBCOAP_SRC_DIR)/coap_hashkey.c \
		$(LIBCOAP_SRC_DIR)/coap_session.c \
		$(LIBCOAP_SRC_DIR)/encode.c \
		$(LIBCOAP_SRC_DIR)/net.c \
		$(LIBCOAP_SRC_DIR)/option.c \
		$(LIBCOAP_SRC_DIR)/pdu.c \
		$(LIBCOAP_SRC_DIR)/resource.c \
		$(LIBCOAP_SRC_DIR)/str.c \
		$(LIBCOAP_SRC_DIR)/subscribe.c \
		$(LIBCOAP_SRC_DIR)/uri.c
		
LIBCOAP_SRC += \
		$(LIBCOAP_SRC_DIR)/coap_notls.c
		
LIBCOAP_SRC += \
		${wildcard $(LIBCOAP_ADAPTER_DIR)/port/*.c} \
		${wildcard $(LIBCOAP_ADAPTER_DIR)/oc/*.c}

C_SOURCES += $(LIBCOAP_SRC)


LIBCOAP_INC = \
		-I $(LIBCOAP_BASE_DIR)/include \
		-I $(LIBCOAP_BASE_DIR)/include/coap2 \
		-I $(LIBCOAP_ADAPTER_DIR)/port \
		-I $(LIBCOAP_ADAPTER_DIR)/oc
		

C_INCLUDES += $(LIBCOAP_INC)
