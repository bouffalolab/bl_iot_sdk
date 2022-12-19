# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include src/core/include src/inst/include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src


COMPONENT_SRCDIRS := src/core \
		 src/inst

COMPONENT_ADD_LDFLAGS_HEAD := -Wl,--whole-archive
COMPONENT_ADD_LDFLAGS_TAIL := -Wl,--no-whole-archive


