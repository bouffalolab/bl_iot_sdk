# Component Makefile
#
LIB_DIR = linux/lib/xz
LIB_SRCS = xz_crc32.c xz_crc64.c xz_dec_stream.c xz_dec_lzma2.c xz_dec_bcj.c

## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += linux/include/linux

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := $(LIB_DIR) userspace


## This component's src
COMPONENT_SRCS := $(addprefix $(LIB_DIR)/, $(LIB_SRCS)) \
                  unxz-test.c
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := $(LIB_DIR) .

##
#CPPFLAGS +=
