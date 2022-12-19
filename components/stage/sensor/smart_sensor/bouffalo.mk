# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src


COMPONENT_SRCDIRS := src \
                     galaxycore_gc0308 \
					 galaxycore_gc0328 \
					 omnivision_ov2685 \
					 byd_bf2013

					 #opnous_opnm8508pa \

COMPONENT_ADD_LDFLAGS_HEAD := -Wl,--whole-archive
COMPONENT_ADD_LDFLAGS_TAIL := -Wl,--no-whole-archive




##
#CPPFLAGS +=
