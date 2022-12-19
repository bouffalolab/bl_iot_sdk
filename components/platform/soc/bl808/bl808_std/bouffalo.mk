BSP_DRIVER_INCS = BL808_BSP_Driver/RISCV/Core/Include \
									BL808_BSP_Driver/platform_print	\
									BL808_BSP_Driver/StdDriver/Inc \
									BL808_BSP_Driver	\
									BSP_Common/lcd/ \
									BSP_Common/lcd/mipi_dpi/ \
									#BL808_BSP_Driver/Startup/$(CPU_ID)/Source \
#									BSP_Common/bflb_platform	\
# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS +=  BL808_BSP_Driver/include \
							  BL808_BSP_Driver/platform_print \
							  BL808_BSP_Driver/RISCV/Core/Include \
							  BL808_BSP_Driver/StdDriver/Inc \
							  BL808_BSP_Driver/dvp/inc \
							  BSP_Common/lcd/ \
							  BSP_Common/lcd/mipi_dpi/ \
							  BSP_Common/lvgl/ \
							  BL808_BSP_Driver/Peripherals \

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := BL808_BSP_Driver/mm_reg

COMMON_DVP_DIR := BL808_BSP_Driver/dvp/src/

dvp_sources := $(COMMON_DVP_DIR)ili9488.c \
				
#               $(COMMON_DVP_DIR)bl_comm_sns.c \
#               $(COMMON_DVP_DIR)bl_img_utils.c \
#               $(COMMON_DVP_DIR)img_proc.c \
#               $(COMMON_DVP_DIR)sha256.c \


## This component's src
COMPONENT_SRCS1 := BL808_BSP_Driver/platform_print/platform_device.c BL808_BSP_Driver/platform_print/platform_gpio.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_uart.c	\
	BL808_BSP_Driver/StdDriver/Src/bl808_glb.c	\
	BL808_BSP_Driver/StdDriver/Src/bl808_common.c	\
	BL808_BSP_Driver/StdDriver/Src/bl808_clock.c	\
	BL808_BSP_Driver/StdDriver/Src/bl808_hbn.c	\
	BL808_BSP_Driver/StdDriver/Src/bl808_glb_gpio.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_clkrst.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_comm_mm.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_dma.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_dvp_tsrc.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_ethmac.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_i2c.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_i2s.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_csi.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_mmsys_misc.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_osd_blend.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_osd_draw.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_osd_probe.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_pdm.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_psram_ctrl.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_pwm.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_sdh.c \
	BL808_BSP_Driver/StdDriver/Src/bl80x_npu.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_dbi.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_cam.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_dma2d.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_code_misc.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_ipc.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_mjpeg.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_spi.c \
	BL808_BSP_Driver/StdDriver/Src/bl808_spp_misc.c \


ifeq ($(CONFIG_ENABLE_LCD),1)
COMPONENT_SRCS1 += BSP_Common/lcd/lcd.c \
                   BSP_Common/lcd/font.c  \
                   BSP_Common/lcd/mipi_dpi/standard_dpi.c
endif

COMPONENT_SRCS1 += $(dvp_sources)

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
COMPONENT_SRCS := $(COMPONENT_SRCS1)
COMPONENT_SRCDIRS := BL808_BSP_Driver BL808_BSP_Driver/platform_print \
	BL808_BSP_Driver/StdDriver/Src \
	BL808_BSP_Driver/dvp/src \

ifeq ($(CONFIG_ENABLE_LCD),1)
COMPONENT_SRCDIRS += BSP_Common/lcd \
                     BSP_Common/lvgl/ \
                     BSP_Common/lcd/mipi_dpi
endif

