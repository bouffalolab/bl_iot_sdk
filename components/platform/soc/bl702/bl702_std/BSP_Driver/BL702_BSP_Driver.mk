#clear_vars
LOCAL_SRCS_FILE:=

MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver

include $(wildcard $(MODULE_DIR)/RISCV/Device/Bouffalo/$(DEVICE_UPPER)/Startup/*.mk)
include $(wildcard $(MODULE_DIR)/FreeRTOS/portable/GCC/RISC-V/*.mk)
include $(wildcard $(MODULE_DIR)/StdDriver/*.mk)



#clear_vars
MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver

COMMON_INCLUDE += -I$(MODULE_DIR) 

ifeq ($(HAL_SUPPORT),y)
include $(wildcard $(MODULE_DIR)/LHalDriver/*.mk)


LAUNCH_FILE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver
LAUNCH_FILE_SRC_DIR := $(MODULE_DIR)

LAUNCH_FILE_CFLAGS:=
COMMON_INCLUDE += -I $(MODULE_DIR)/LHalDriver/Inc -I $(MODULE_DIR)/Stddriver/Inc

launch_file_sources := launch.c bflb_stub.c

launch_file_objs := $(addprefix $(LAUNCH_FILE_OUT_DIR)/, $(subst .c,.o,$(launch_file_sources)))
base_objects += $(launch_file_objs)

$(LAUNCH_FILE_OUT_DIR)/%.o:$(LAUNCH_FILE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(STDDRIVER_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $< -o $@

.PHONY: launch
launch: $(launch_file_objs)
	@echo  "stddriver_objs is $(launch_file_objs)"

else
COMMON_INCLUDE += -I$(MODULE_DIR)/platform_print
include $(wildcard $(MODULE_DIR)/platform_print/*.mk)
endif