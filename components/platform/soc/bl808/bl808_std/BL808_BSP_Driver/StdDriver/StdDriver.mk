#clear_vars
LOCAL_SRCS_FILE:=

SUB_MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver/StdDriver
SUBMODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver/StdDriver
SUBMODULE_SRC_DIR := $(SUB_MODULE_DIR)/Src

STDDRIVER_CFLAGS:=
STDDRIVER_INCLUDE:=  -I $(SUB_MODULE_DIR)/Inc \


stddriver_sources := bl606p_acomp.c \
                     bl606p_aon.c \
                     bl606p_adc.c \
                     bl606p_can.c \
                     bl606p_common.c \
                     bl606p_clock.c \
                     bl606p_dma.c \
                     bl606p_glb.c \
                     bl606p_glb_gpio.c \
                     bl606p_hbn.c \
                     bl606p_nf_cfg.c \
                     bl606p_pds.c \
                     bl606p_sec_dbg.c \
                     bl606p_sec_eng.c \
                     bl606p_timer.c \
                     bl606p_xip_sflash.c \
                     bl606p_psram_ctrl.c \
                     bl606p_i2s.c \
                     bl606p_audio.c \
                     bl606p_cam.c \
                     bl606p_isp_misc.c \
                     bl606p_osd.c \
                     bl606p_mjpeg.c \
                     bl606p_dbi.c \
                     bl606p_apwm.c \
                     bl606p_pwm.c \
                     bl606p_sdh.c \
                     bl606p_spi.c \
                     bl606p_ef_ctrl.c \
                     bl606p_tzc_sec.c \
                     bl606p_i2c.c \
                     bl606p_ipc.c \
                     bl606p_l1c.c \
                     bl606p_nflash.c \
                     bl606p_sflash.c \
                     bl606p_emac.c \
                     bl606p_mcu_misc.c \
                     bl606p_sf_cfg.c \
                     bl606p_sf_ctrl.c \
                     bl606p_ir.c \
                     bl606p_dpi.c \
                     bl808_uart.c \
                     #bl606p_uart.c \
                                                   

ifeq ($(BOOTROM),y)
stddriver_sources += bl606p_romdriver.c
endif

###############################################################################
ifeq ($(USB_DRIVER),y)
stddriver_sources += bl606p_usb.c 
GLOBAL_INCLUDE += -I $(MODULE_DIR)/Inc

ifeq ($(USB_CASE), USB_TO_UART)
stddriver_sources += bl606p_hal_pcd_usb_to_uart.c 
else
stddriver_sources += bl606p_hal_pcd.c 
endif

endif
###############################################################################

ifeq ($(ROMAPI),y)
    #stddriver_sources += bl606p_sf_cfg_ext.c
    #stddriver_sources += bl606p_romapi.c
else
    #stddriver_sources += bl606p_sf_cfg_ext.c
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
