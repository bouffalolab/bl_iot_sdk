SUB_MODULE_DIR:= $(MODULE_DIR)/dvp
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)/dvp

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)/src
DVP_INC := -I$(SUB_MODULE_DIR)/inc

DVP_CFLAGS :=

COMMON_INCLUDE += -I $(MODULE_DIR)/dvp/inc

ifeq ($(DEVICE),BL808)
dvp_sources := image_sensor.c ae_algo.c awb_algo.c awb1_algo.c awb2_algo.c \
               bnr_firmware.c wdr_firmware.c img_param.c bl_comm_sns.c \
               bl_img_utils.c img_proc.c sha256.c ili9488.c
else
dvp_sources := image_sensor.c ili9488.c
endif

dvp_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(dvp_sources)))

bsp_common_objs_target += $(dvp_objs)
                      
$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(EXTERNAL_CFLAGS) $(BSP_CFLAGS) $(DVP_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) \
    $(BSP_INCLUDES) $(DVP_INC) $< -o $@
