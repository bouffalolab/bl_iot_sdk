# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

COMPONENT_SRCS1 := evb/d0/startup_d0.S          \
				   evb/d0/vectors_d0.S          \
				   evb/d0/riscv_fpu_d0.S        \
				   evb/d0/start_load_d0.c	    \
				   evb/d0/interrupt_d0.c	    \
				   evb/d0/system_bl606p_d0.c	\
				   evb/d0/debug_d0.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
COMPONENT_SRCS := $(COMPONENT_SRCS1)
COMPONENT_SRCDIRS := evb/src/ evb/d0

ifneq ($(CONFIG_LINK_CUSTOMER),1)

ifeq ($(CONFIG_LINK_RAM),1)
LINKER_SCRIPTS := bl606p_d0_ram.ld
CPPFLAGS += -DRUN_IN_RAM
else

ifeq ($(CONFIG_LINK_ROM),1)
LINKER_SCRIPTS := bl606p_d0_flash_rom.ld
else
LINKER_SCRIPTS := bl606p_d0_flash.ld
endif

endif

##
COMPONENT_ADD_LDFLAGS += -L $(COMPONENT_PATH)/evb/d0 \
                         $(addprefix -T ,$(LINKER_SCRIPTS))
##
COMPONENT_ADD_LINKER_DEPS := $(addprefix evb/d0/,$(LINKER_SCRIPTS))
endif

ifeq ($(CONFIG_DISABLE_PRINT),1)
CPPFLAGS += -DDISABLE_PRINT
endif

ifeq ($(CONFIG_DISABLE_PRINT_FLOAT),1)
CPPFLAGS += -DDISABLE_PRINT_FLOAT
endif

##
#CPPFLAGS += -D__NO_SYSTEM_INIT -D__NO_BOARD_INIT
