toolchains := gcc

ifeq ($(CONFIG_CHIP_NAME),BL808)
CFLAGS   += -DBL808
endif

ifeq ($(CONFIG_CHIP_NAME),BL606P)
CFLAGS   += -DBL606P
endif

# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += evb/src

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS1 := evb/src/boot/$(toolchains)/startup.S \
				  evb/src/boot/$(toolchains)/start_load.c	\
				  evb/src/startup_interrupt.c	\
				  evb/src/startup_bl606p.c	\
				  evb/src/debug.c	\

				  #evb/src/boot/$(toolchains)/vectors.S \

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
COMPONENT_SRCS := $(COMPONENT_SRCS1)
COMPONENT_SRCDIRS := evb/src/boot/$(toolchains) evb/src

ifneq ($(CONFIG_LINK_CUSTOMER),1)

ifeq ($(CONFIG_CHIP_NAME),BL808)

ifeq ($(CONFIG_LINK_RAM),1)
LINKER_SCRIPTS := bl808_ram.ld
CPPFLAGS += -DRUN_IN_RAM
else ifeq ($(CONFIG_LINK_RAM4PHYRF),1)
$(info "using bl808_ram_phyrf.ld")
LINKER_SCRIPTS := bl808_ram_phyrf.ld
CPPFLAGS += -DRUN_IN_RAM
else ifeq ($(CONFIG_LINK_ROM),1)
LINKER_SCRIPTS := bl808_flash_rom.ld
else ifeq ($(CONFIG_LINK_FLASH4PHYRF),1)
$(info "using bl808_flash_phyrf.ld")
LINKER_SCRIPTS := bl808_flash_phyrf.ld
else ifeq ($(CONFIG_LINK_NO_WIFI),1)
$(info "using bl808_flash_no_wifi.ld")
LINKER_SCRIPTS := bl808_flash_no_wifi.ld
else
LINKER_SCRIPTS := bl808_flash.ld
endif

else ifeq ($(CONFIG_CHIP_NAME),BL606P)

ifeq ($(CONFIG_LINK_RAM),1)
LINKER_SCRIPTS := bl606p_ram.ld
CPPFLAGS += -DRUN_IN_RAM
else ifeq ($(CONFIG_LINK_RAM4PHYRF),1)
$(info "using bl606p_ram_phyrf.ld")
LINKER_SCRIPTS := bl606p_ram_phyrf.ld
CPPFLAGS += -DRUN_IN_RAM
else ifeq ($(CONFIG_LINK_ROM),1)
LINKER_SCRIPTS := bl606p_flash_rom.ld
else ifeq ($(CONFIG_LINK_FLASH4PHYRF),1)
$(info "using bl606p_flash_phyrf.ld")
LINKER_SCRIPTS := bl606p_flash_phyrf.ld
else
LINKER_SCRIPTS := bl606p_flash.ld
endif

endif

##
COMPONENT_ADD_LDFLAGS += -L $(COMPONENT_PATH)/evb/ld \
                         $(addprefix -T ,$(LINKER_SCRIPTS))
##
COMPONENT_ADD_LINKER_DEPS := $(addprefix evb/ld/,$(LINKER_SCRIPTS))
endif

ifeq ($(CONFIG_DISABLE_PRINT),1)
CPPFLAGS += -DDISABLE_PRINT
endif

ifeq ($(CONFIG_DISABLE_PRINT_FLOAT),1)
CPPFLAGS += -DDISABLE_PRINT_FLOAT
endif

