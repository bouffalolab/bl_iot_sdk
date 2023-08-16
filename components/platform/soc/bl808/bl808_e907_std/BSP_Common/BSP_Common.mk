#clear_vars
LOCAL_SRCS_FILE:=

MODULE_DIR:= BSP_Common
MODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Common

bsp_common_objs_target :=

ifeq ($(HAL_SUPPORT),y)
COM_EXCLUDE_DIR:=$(MODULE_DIR)/platform_print
else
COM_EXCLUDE_DIR:=$(MODULE_DIR)/bflb_platform #$(MODULE_DIR)/partition #$(MODULE_DIR)/cipher_suite
endif

ifneq ($(SDH_SUPPORT),y)
COM_EXCLUDE_DIR += $(MODULE_DIR)/sd_card
endif

ifneq ($(DVP_SUPPORT),y)
COM_EXCLUDE_DIR += $(MODULE_DIR)/dvp
endif

COM_ALL_DIRS := $(shell find $(MODULE_DIR) -maxdepth 1 -mindepth 1 -type d)
COM_DIRS=$(filter-out $(COM_EXCLUDE_DIR), $(COM_ALL_DIRS)) 
COM_MKS=$(foreach com_dir,$(COM_DIRS),$(wildcard $(com_dir)/*.mk))

#$(info $(COM_MKS))
include $(COM_MKS)

base_objects += $(bsp_common_objs_target)

.PHONY: bsp_common
bsp_common: $(bsp_common_objs_target)
