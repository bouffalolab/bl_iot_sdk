# Component Makefile
#

## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := bugkiller_string.c \
                  bugkiller_clocktree_dump.c \
                  bugkiller_uart_dump.c \
                  bugkiller.c \
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := .

ifeq ($(CONFIG_CHIP_NAME),BL602)
CFLAGS   += -DBL602
endif

ifeq ($(CONFIG_CHIP_NAME),BL808)
CFLAGS   += -DBL808
endif
##
