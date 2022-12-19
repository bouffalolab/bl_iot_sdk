# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := ff/include

## This component's src 
COMPONENT_SRCS := src/fatfs.c \
                  src/diskio.c \
                  ff/ff.c \
                  ff/ffunicode.c

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := ff src


##
#CPPFLAGS += 
