#
SUB_MODULE_DIR:= $(MODULE_DIR)/platform_print
SUB_MODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver/platform_print

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)/

ifneq ($(DV_TEST),y)
COMMON_INCLUDE += -I $(MODULE_DIR)/platform_print
else
COMMON_CFLAGS += -DDV_TEST
endif

platform_print_sources :=  platform_device.c platform_gpio.c

platform_print_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(platform_print_sources)))

base_objects += $(platform_print_objs)

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $< -o $@
