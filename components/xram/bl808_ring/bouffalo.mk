# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
#COMPONENT_PRIV_INCLUDEDIRS := include ../bl808_ring/include ../bl808_xram/include

## This component's src 
COMPONENT_SRCS := src/ring.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


ifeq ($(CONFIG_CPU_E907),1)
	CFLAGS+= -DXRAM_CPU_E907
endif
ifeq ($(CONFIG_CPU_C906),1)
	CFLAGS+= -DXRAM_CPU_C906
endif
ifeq ($(CONFIG_CPU_E902),1)
	CFLAGS+= -DXRAM_CPU_E902
endif
##
#CPPFLAGS += 
