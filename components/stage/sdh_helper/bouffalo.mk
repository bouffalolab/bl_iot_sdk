# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := include

## This component's src
#COMPONENT_SRCS := src/helper_psm.c \
                  src/helper_amr.c \
                  src/helper_audio.c \
                  src/helper_ota.c \
                  src/helper_http.c \
                  src/helper_sdh.c \
                  src/helper_nv.c \
                  src/helper_wifi.c \
                  src/helper_blsync.c \
                  src/helper_fdt.c \
                  src/helper_tc.c \
                  src/helper_sys.c \
                  src/helper_mjpegsd.c \
                  src/helper_avisd.c \
                  src/helper_backtrace.c \
                  src/helper_aws.c	\
                  src/helper_netstat.c

COMPONENT_SRCS = src/helper_sdh.c \

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
#CPPFLAGS +=
