# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += bl60x_hal

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := bl60x_hal/bl_uart.c \
                  bl60x_hal/bl_sys.c \
                  bl60x_hal/bl_sdh.c \
                  bl60x_hal/hal_sdh.c \
                  bl60x_hal/hal_sys.c \
                  bl60x_hal/hosal_uart.c \
                  bl60x_hal/bl_psram.c \
                  bl60x_hal/bl_gpio.c \
                  bl60x_hal/bl_venc.c \
                  bl60x_hal/bl_mjdec.c \
                  bl60x_hal/bl_mmsys.c \
                  bl60x_hal/bl_i2s.c \
                  bl60x_hal/bl_cpu.c \
                  bl60x_hal/bl_npu.c \

#				  bl60x_hal/bl_wifi.c \
#                 bl60x_hal/bl_efuse.c \
#                 bl60x_hal/bl_dma.c \
#                 bl60x_hal/bl_cam.c \


ifneq ($(CONFIG_MCU_ONLY),1)
#COMPONENT_SRCS += bl60x_hal/bl_wifi.c
endif

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := bl60x_hal


##
#CPPFLAGS +=
