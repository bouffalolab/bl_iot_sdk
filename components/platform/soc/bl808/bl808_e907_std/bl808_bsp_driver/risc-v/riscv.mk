#clear_vars
LOCAL_SRCS_FILE:=

SUB_MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver/RISCV
SUBMODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver/RISCV
SUBMODULE_SRC_DIR := $(SUB_MODULE_DIR)/

RISCV_CORE_CFLAGS:=
RISCV_CORE_INCLUDE:=  -I $(SUB_MODULE_DIR)/Core/Include \

riscv_core_sources := rv_hart.c rv_pmp.c

ifeq ($(MCPU),c906)
riscv_core_sources += rv_Sv39.c
endif

riscv_core_objs := $(addprefix $(SUBMODULE_OUT_DIR)/, $(subst .c,.o,$(riscv_core_sources)))
base_objects += $(riscv_core_objs)

$(SUBMODULE_OUT_DIR)/%.o:$(SUBMODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(RISCV_CORE_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $(RISCV_CORE_INCLUDE) $(BFLB_PALTFORM_INCLUDE) $< -o $@

.PHONY: riscv_core
riscv_core: $(riscv_core_objs)
	@echo  "riscv_core_objs is $(riscv_core_objs)"
