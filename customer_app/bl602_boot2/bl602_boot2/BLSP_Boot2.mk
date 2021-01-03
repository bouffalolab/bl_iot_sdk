CASE_ROOT_DIR:=Examples
MODULE_DIR:= $(CASE_ROOT_DIR)/BLSP_Boot2
CASE_PREFIX=$(shell echo $(CASE_ROOT_DIR) | tr A-Z a-z)
MODULE_OUT_DIR:= $(TARGET_OUT_PATH)/$(MODULE_DIR)

#LOCAL_CFLAGS:=-DBLSP_BOOT2_ROLLBACK
$(MODULE_OUT_DIR)/%.o: LOCAL_CFLAGS:= -DBLSP_BOOT2_ROLLBACK -O2
$(MODULE_OUT_DIR)/%.o: LOCAL_INCLUDE:= -I$(MODULE_DIR)

LOCAL_COM_SRCS_FILE:=
local_com_objs := $(subst .c,.o,$(LOCAL_COM_SRCS_FILE))

$(MODULE_OUT_DIR)/%.o:$(MODULE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(LOCAL_CFLAGS) \
	$(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $(LOCAL_INCLUDE) $< -o $@

local_com_objs_target:= $(addprefix $(MODULE_OUT_DIR)/,$(local_com_objs))

all_objects += $(local_com_objs_target)

#blsp_boot2
BOOT2_TARGETS += blsp_boot2
BLSP_BOOT2_SRCS_FILE:= blsp_boot2.c blsp_common.c blsp_media_boot.c blsp_boot_parser.c blsp_boot_decompress.c blsp_port.c

blsp_boot2_objs := $(subst .c,.o,$(BLSP_BOOT2_SRCS_FILE))
blsp_boot2_objs_target:= $(addprefix $(MODULE_OUT_DIR)/,$(blsp_boot2_objs))
all_objects += $(blsp_boot2_objs_target)

blsp_boot2: TARGET := blsp_boot2
blsp_boot2: TARGET_OUT := $(MODULE_OUT_DIR)
blsp_boot2: TARGET_OBJS := $(blsp_boot2_objs_target) $(local_com_objs_target) $(base_objects)
blsp_boot2: BL_TARGET_LDSCRIPT := $(MODULE_DIR)/blsp_boot2_flash.ld

blsp_boot2: $(all_objects)
	@echo " build output $(TARGET_OUT_PATH)/$@ $(TARGET_OUT)"
	$(AT)$(LD) $(TARGET_OBJS) $(GLOBAL_LDFLAGS) -L$(BSP_DSP_PATH) -l$(BSP_DSP_LIB)
	$(AT)$(OBJCOPY) -O binary $(TARGET_OUT)/$(basename $(TARGET)).elf $(TARGET_OUT)/$(TARGET).bin


