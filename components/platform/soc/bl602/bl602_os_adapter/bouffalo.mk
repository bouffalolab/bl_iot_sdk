# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += bl602_os_adapter/include \
							 bl602_os_adapter/include/bl_os_adapter
							 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := bl602_os_adapter			 

## This component's src 
COMPONENT_SRCS := bl602_os_adapter/bl602_os_hal.c
				  
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := bl602_os_adapter

CFLAGS   += -DCFG_FREERTOS 
##
#CPPFLAGS += 
