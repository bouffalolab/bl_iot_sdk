BSP_DRIVER_INCS = bl808_bsp_driver/risc-v/Core/Include \
									bl808_bsp_driver/regs \
									bl808_bsp_driver/startup/m0/source \
									bl808_bsp_driver/std_drv/inc \
									common/misc \
									common/misc/compiler \
									common/soft_crc \
									common/device \
									common/list \

# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += $(BSP_DRIVER_INCS)

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS1 := bl808_bsp_driver/std_drv/src/bl808_uart.c \
	bl808_bsp_driver/std_drv/src/bl808_common.c	\
	bl808_bsp_driver/std_drv/src/bl808_l1c.c	\
	bl808_bsp_driver/std_drv/src/bl808_sf_ctrl.c \
	bl808_bsp_driver/std_drv/src/bl808_sflash.c \
	bl808_bsp_driver/std_drv/src/bl808_ef_ctrl.c \
	bl808_bsp_driver/std_drv/src/bl808_sf_cfg.c \
	bl808_bsp_driver/std_drv/src/bl808_xip_sflash.c \
	bl808_bsp_driver/std_drv/src/bl808_ipc.c \
	bl808_bsp_driver/std_drv/src/bl808_psram_uhs.c \
	bl808_bsp_driver/std_drv/src/bl808_tzc_sec.c \
	bl808_bsp_driver/std_drv/src/bl808_sec_eng.c \
	bl808_bsp_driver/std_drv/src/bl808_clock.c \
	bl808_bsp_driver/std_drv/src/bl808_glb.c \
	bl808_bsp_driver/std_drv/src/bl808_glb_gpio.c \
	bl808_bsp_driver/std_drv/src/bl808_pds.c \
	bl808_bsp_driver/std_drv/src/bl808_hbn.c \
	bl808_bsp_driver/std_drv/src/bl808_usb.c \
	bl808_bsp_driver/std_drv/src/bl808_emac.c \
	bl808_bsp_driver/std_drv/src/bl808_audio.c	\
	bl808_bsp_driver/std_drv/src/bl808_dma.c	\
	bl808_bsp_driver/std_drv/src/bl808_pwm.c	\
	bl808_bsp_driver/std_drv/src/bl808_spi.c	\
	bl808_bsp_driver/std_drv/src/bl808_adc.c        \
	bl808_bsp_driver/std_drv/src/bl808_sdh.c	\
	bl808_bsp_driver/std_drv/src/bl808_mjpeg.c      \
	common/soft_crc/softcrc.c \
	common/misc/misc.c \



COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
COMPONENT_SRCS := $(COMPONENT_SRCS1)
COMPONENT_SRCDIRS := bl808_bsp_driver/std_drv/src \
	common/soft_crc \
	common/misc \

