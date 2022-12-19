
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += Source/include Source/portable/GCC/RISC-V Source/portable/GCC/RISC-V/chip_specific_extensions/Thead_E906FD_RV32IMAFDC
COMPONENT_OBJS := $(patsubst %.c,%.o, \
                    Source/event_groups.c \
                    Source/list.c \
                    Source/queue.c \
                    Source/stream_buffer.c \
                    Source/tasks.c \
                    Source/timers.c \
                    Source/portable/GCC/RISC-V/port.c \
                    Source/portable/GCC/RISC-V/portASM.S \
                    Source/portable/MemMang/heap_5.c)

COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))

COMPONENT_SRCDIRS := Source Source/portable Source/portable/GCC/RISC-V Source/portable/MemMang

OPT_FLAG_G := $(findstring -Og, $(CFLAGS))
ifeq ($(strip $(OPT_FLAG_G)),-Og)
CFLAGS := $(patsubst -Og,-O2,$(CFLAGS))
endif
OPT_FLAG_S := $(findstring -Os, $(CFLAGS))
ifeq ($(strip $(OPT_FLAG_S)),-Os)
CFLAGS := $(patsubst -Os,-O2,$(CFLAGS))
endif
