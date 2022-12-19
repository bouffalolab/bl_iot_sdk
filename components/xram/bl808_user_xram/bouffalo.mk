# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include 

## This component's src 
COMPONENT_SRCS := src/bl808_user_xram.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src

OPT_FLAG_G := $(findstring -Og, $(CFLAGS))
ifeq ($(strip $(OPT_FLAG_G)),-Og)
CFLAGS := $(patsubst -Og,-O2,$(CFLAGS))
endif
OPT_FLAG_S := $(findstring -Os, $(CFLAGS))
ifeq ($(strip $(OPT_FLAG_S)),-Os)
CFLAGS := $(patsubst -Os,-O2,$(CFLAGS))
endif

ifeq ($(CONFIG_CPU_E907),1)
	CFLAGS+= -DXRAM_CPU_E907
endif
ifeq ($(CONFIG_CPU_C906),1)
	CFLAGS+= -DXRAM_CPU_C906
endif
ifeq ($(CONFIG_CPU_E902),1)
	CFLAGS+= -DXRAM_CPU_E902
endif

CFLAGS+=-Wno-error=unused-but-set-variable -Wno-error=unused-but-set-parameter -Wno-error=unused-const-variable
