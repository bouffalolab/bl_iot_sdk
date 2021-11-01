SUB_MODULE_DIR:= $(MODULE_DIR)/bflb_platform
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/bflb_platform
SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)
HAL_LIB_DIR:= HAL

PLATFORM_PRINT_CFLAGS :=

BFLB_PALTFORM_INCLUDE = -I$(SUB_MODULE_DIR)/ -I$(HAL_LIB_DIR)/Inc -IBSP_Driver/$(DEVICE)_BSP_Driver/ 



COMMON_INCLUDE += -I$(SUB_MODULE_DIR) -IBSP_Driver/$(DEVICE)_BSP_Driver/ 

bflb_paltform_sources :=  bflb_platform.c

bflb_paltform_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(bflb_paltform_sources)))

bsp_common_objs_target += $(bflb_paltform_objs)

#$(info $(bsp_common_objs_target))  

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(EXTERNAL_CFLAGS) $(PLATFORM_PRINT_CFLAGS) \
	$(GLOBAL_INCLUDE)  $(BFLB_PALTFORM_INCLUDE) $(COMMON_INCLUDE) $< -o $@

.PHONY: bflb_platform
bflb_platform: $(bflb_paltform_objs)
	@echo  "bflb_paltform_objs is $(bflb_paltform_objs)"

