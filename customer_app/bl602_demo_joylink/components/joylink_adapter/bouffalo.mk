# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += joylink/inc \
                             pal/inc \
                             example

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := joylink/inc/json

#OUT_SRC := test.c

## This component's src
COMPONENT_SRCS := $(wildcard pal/src/*.c) \
                  $(filter-out ${OUT_SRC}, $(wildcard example/*.c))

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_OBJS := $(patsubst %.cpp,%.o, $(COMPONENT_OBJS))

COMPONENT_SRCDIRS := pal/src \
                     example

LIBS ?= joylink
COMPONENT_ADD_LDFLAGS += -L$(COMPONENT_PATH)/joylink/lib $(addprefix -l,$(LIBS))
ALL_LIB_FILES := $(patsubst %,$(COMPONENT_PATH)/joylink/lib/lib%.a,$(LIBS))
COMPONENT_ADD_LINKER_DEPS := $(ALL_LIB_FILES)

##
