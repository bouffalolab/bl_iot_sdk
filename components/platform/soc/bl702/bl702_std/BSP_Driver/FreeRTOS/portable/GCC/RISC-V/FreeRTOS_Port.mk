#
SUB_MODULE_DIR:= $(MODULE_DIR)/FreeRTOS/portable/GCC/RISC-V
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/FreeRTOS

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)

FREERTOS_INCLUDE := -I$(MODULE_DIR)/FreeRTOS/portable/GCC/RISC-V \
                    -I$(MODULE_DIR)/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_CLINT_no_extensions

COMMON_INCLUDE += -I$(MODULE_DIR)/FreeRTOS/portable/GCC/RISC-V

freertos_port_sources := port.c

freertos_port_asm_sources := portASM.S

freertos_port_objs += $(subst .c,.o,$(freertos_port_sources))
freertos_port_objs += $(subst .S,.o,$(freertos_port_asm_sources))
freertos_port_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(freertos_port_objs))

base_objects += $(freertos_port_objs)

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(FREERTOS_INCLUDE) $(COMMON_INCLUDE) $< -o $@

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	@echo "as $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) -DportasmHANDLE_INTERRUPT=FreeRTOS_Interrupt_Handler $(GLOBAL_INCLUDE) $(FREERTOS_INCLUDE) $< -o $@
