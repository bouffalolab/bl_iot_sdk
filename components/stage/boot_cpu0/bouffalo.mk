# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += inc
							 
## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 						 

## This component's src 
COMPONENT_SRCS := src/boot_cpu0.c src/l2_sram.c src/ipc_xram_test.c
				  
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
#CPPFLAGS += 
