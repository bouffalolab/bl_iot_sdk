# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += StdDriver/Inc \
							 RISCV/Core/Include \

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src

COMPONENT_SRCDIRS := . StdDriver/Src


##
#CPPFLAGS += -DBL60X_USE_HAL_DRIVER
