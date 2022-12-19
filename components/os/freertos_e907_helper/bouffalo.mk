# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := freertos_e907_helper_ps_with_irq.c freertos_e907_helper_ps_with_irq_test.c freertos_e907_helper_section_time_stat.c freertos_e907_helper_section_time_stat_test.c


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := .

