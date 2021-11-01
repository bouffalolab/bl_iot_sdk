#clear_vars
LOCAL_SRCS_FILE:=

MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver/StdDriver
SUBMODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver/StdDriver
SUBMODULE_SRC_DIR := $(MODULE_DIR)/Src

STDDRIVER_CFLAGS:=
STDDRIVER_INCLUDE:=  -I $(MODULE_DIR)/Inc \


stddriver_sources := bl702_common.c bl702_ef_ctrl.c bl702_aon.c bl702_dma.c bl702_glb.c bl702_hbn.c bl702_l1c.c bl702_pds.c \
                     bl702_uart.c bl702_sf_ctrl.c bl702_sflash.c bl702_sflash_ext.c bl702_xip_sflash.c bl702_clock.c \
                     bl702_timer.c bl702_i2c.c bl702_spi.c bl702_ir.c bl702_psram.c bl702_sec_eng.c bl702_adc.c bl702_dac.c \
                     bl702_i2s.c bl702_kys.c bl702_emac.c bl702_qdec.c bl702_cam.c bl702_mjpeg.c bl702_xip_sflash_ext.c\
                     bl702_sf_cfg.c bl702_pwm.c bl702_acomp.c bl702_sec_dbg.c bl702_i2c_gpio_sim.c bl702_nflash.c bl702_nf_cfg.c\
                     bl702_snflash.c

###############################################################################
ifeq ($(USB_DRIVER),y)
stddriver_sources += bl702_usb.c 
stddriver_sources += bl702_hal_pcd.c 
GLOBAL_INCLUDE += -I $(MODULE_DIR)/Inc
endif
###############################################################################

ifeq ($(ROMAPI),y)
ifeq ($(ROMAPI_TEST),y)
    stddriver_sources += bl702_romapi.c
else
    stddriver_sources += bl702_sf_cfg_ext.c
    stddriver_sources += bl702_romapi.c
endif
else
    stddriver_sources += bl702_sf_cfg_ext.c
endif

stddriver_objs := $(addprefix $(SUBMODULE_OUT_DIR)/, $(subst .c,.o,$(stddriver_sources)))
base_objects += $(stddriver_objs)

$(SUBMODULE_OUT_DIR)/%.o:$(SUBMODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(STDDRIVER_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $(STDDRIVER_INCLUDE) $(BFLB_PALTFORM_INCLUDE) $< -o $@

.PHONY: stddriver
stddriver: $(stddriver_objs)
	@echo  "stddriver_objs is $(stddriver_objs)"
