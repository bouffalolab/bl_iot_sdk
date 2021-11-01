SUB_MODULE_DIR:= $(MODULE_DIR)/sd_card
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/sd_card

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)

COMMON_INCLUDE += -I $(MODULE_DIR)/sd_card
                  
sd_card_sources := bsp_sdio_sdcard.c fatfs_port.c

sd_card_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(sd_card_sources)))

bsp_common_objs_target += $(sd_card_objs)

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $< -o $@