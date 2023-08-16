#
SUB_MODULE_DIR:= $(MODULE_DIR)/FreeRTOS
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/FreeRTOS

3RDPARTY_INCLUDE += -I$(MODULE_DIR)/FreeRTOS/Source/portable/GCC/RISC-V
3RDPARTY_INCLUDE += -I$(MODULE_DIR)/FreeRTOS/Demo/Common/include
3RDPARTY_INCLUDE += -I$(MODULE_DIR)/FreeRTOS/Source/portable/GCC/RISC-V/chip_specific_extensions/Thead_E906FD_RV32IMAFDC

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)

freertos_lib_sources := Source/tasks.c Source/list.c Source/queue.c Source/timers.c Source/stream_buffer.c Source/croutine.c
freertos_lib_sources += Source/portable/GCC/RISC-V/port.c
freertos_lib_sources += Source/portable/MemMang/heap_5.c

freertos_lib_sources += Demo/Common/Full/BlockQ.c Demo/Common/Full/events.c Demo/Common/Full/flash.c
freertos_lib_sources += Demo/Common/Full/comtest.c Demo/Common/Full/flop.c Demo/Common/Full/integer.c
freertos_lib_sources += Demo/Common/Full/death.c Demo/Common/Full/PollQ.c Demo/Common/Full/print.c
freertos_lib_sources += Demo/Common/Full/dynamic.c Demo/Common/Full/semtest.c

freertos_lib_sources += Demo/Common/Minimal/blocktim.c Demo/Common/Minimal/countsem.c
freertos_lib_sources += Demo/Common/Minimal/GenQTest.c Demo/Common/Minimal/recmutex.c
freertos_lib_sources += Demo/Common/Minimal/TaskNotify.c

freertos_lib_asm_sources := Source/portable/GCC/RISC-V/portASM.S

freertos_lib_objs += $(subst .c,.o,$(freertos_lib_sources))
freertos_lib_objs += $(subst .S,.o,$(freertos_lib_asm_sources))
freertos_lib_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(freertos_lib_objs))

3rdparty_objs_target += $(freertos_lib_objs)

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(3RDPARTY_INCLUDE) $(COMMON_INCLUDE) $< -o $@

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(AS) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(3RDPARTY_INCLUDE) $(COMMON_INCLUDE) $< -o $@
