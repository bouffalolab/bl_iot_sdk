SUB_MODULE_DIR:= $(MODULE_DIR)/soft_crc
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/soft_crc

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)

COMMON_INCLUDE += -I $(SUB_MODULE_DIR)

ifneq ($(DEVICE),BL606P)
softcrc_sources :=  softcrc.c
endif

softcrc_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(softcrc_sources)))

bsp_common_objs_target += $(softcrc_objs)
                      
$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(EXTERNAL_CFLAGS) \
	$(GLOBAL_INCLUDE)  $(COMMON_INCLUDE) $< -o $@
