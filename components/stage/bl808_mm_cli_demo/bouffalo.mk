# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := include

## This component's src
ifeq ("$(CPU_ID)", "D0")
ifeq ($(CONFIG_NO_SPP_CAM), 1)
COMPONENT_SRCS := src/helper_cam_yuv_sensor.c
else
COMPONENT_SRCS := src/helper_mjpeg.c \
                  src/helper_cam_yuv_sensor.c \

endif
else
COMPONENT_SRCS := src/helper_mjpeg.c \
 
endif

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
#CPPFLAGS +=
