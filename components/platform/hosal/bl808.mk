# Component Makefile
#
ifeq ("$(CPU_ID)" ,$(filter "$(CPU_ID)", "M1" "M0"))

## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += bl808_e907_hal

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS +=

## This component's src
COMPONENT_SRCS := bl808_e907_hal/bl_uart.c \
	bl808_e907_hal/bl_irq.c \
	bl808_e907_hal/bl_sec.c \
	bl808_e907_hal/bl_chip.c	\
	bl808_e907_hal/bl_timer.c 	\
	bl808_e907_hal/bl_flash.c   \
	bl808_e907_hal/bl_wifi.c 	\
	bl808_e907_hal/bl_efuse.c 	\
	bl808_e907_hal/bl_sys.c 	\
	bl808_e907_hal/bl_pm.c 	\
	bl808_e907_hal/bl_boot2.c 	\
	bl808_e907_hal/hal_boot2.c 	\
	bl808_e907_hal/hal_board.c 	\
	bl808_e907_hal/hal_sys.c	\
	bl808_e907_hal/bl_psram.c	\
	bl808_e907_hal/bl_mm_clock.c	\
	bl808_e907_hal/hosal_uart.c	\
	bl808_e907_hal/hosal_pwm.c	\
	bl808_e907_hal/hosal_spi.c	\
	bl808_e907_hal/hosal_dma.c      \
	bl808_e907_hal/hosal_adc.c      \
	bl808_e907_hal/bl_ipc.c	\
	bl808_e907_hal/bl_audio.c \
	bl808_e907_hal/bl_sdh.c \
	bl808_e907_hal/hal_sdh.c \
	bl808_e907_hal/bl_cam.c \
	sec_common/bl_sec_pka.c \

ifeq ($(CONFIG_ETH),1)
COMPONENT_SRCS += bl808_e907_hal/bl_ethernetif.c \
                  bl808_e907_hal/emac_phy.c	\
                  bl808_e907_hal/phy_8720.c	\
                  bl808_e907_hal/hal_emac.c
endif

ifeq ($(CONFIG_WIFI),1)
COMPONENT_SRCS += bl808_e907_hal/bl_wifi.c \
		  bl808_e907_hal/hal_wifi.c
endif

ifeq ($(CONFIG_USB_CAM_ENABLE),1)
COMPONENT_SRCS += bl808_e907_hal/hal_usb.c \
		  bl808_e907_hal/bl_usb_cam.c
endif
COMPONENT_SRCDIRS += bl808_e907_hal sec_common

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_OBJS := $(patsubst %.cpp,%.o, $(COMPONENT_OBJS))

##
ifeq ($(CONFIG_BT),1)
CPPFLAGS += -DCFG_BLE_ENABLE
else
endif

ifeq ($(CONF_ENABLE_COREDUMP),1)
CPPFLAGS += -DSYS_ENABLE_COREDUMP
endif

CPPFLAGS += -DARCH_RISCV
ifndef CONFIG_USE_STD_DRIVER
CPPFLAGS += -DBL606P_USE_HAL_DRIVER
endif

ifeq ($(CONFIG_USE_XTAL32K),1)
CFLAGS += -DCFG_USE_XTAL32K
endif

else

ifeq ($(CONFIG_ENABLE_YUV_CAM),1)
CFLAGS += -DCONF_USER_YUV_CAM
endif

## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += bl808_hal

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := bl808_hal/bl_uart.c \
	bl808_hal/bl_irq.c \
	bl808_hal/bl_sec.c \
	bl808_hal/bl_chip.c	\
	bl808_hal/bl_timer.c 	\
	bl808_hal/hal_sys.c	\
	bl808_hal/hosal_uart.c \
	bl808_hal/bl_sdh.c \
	bl808_hal/hal_sdh.c \
	bl808_hal/bl_psram.c \
	bl808_hal/bl_gpio.c \
	bl808_hal/bl_pwm.c \
	bl808_hal/bl_npu.c \
	bl808_hal/bl_ipc.c \
	bl808_hal/bl_cam.c \
	bl808_hal/bl_dma.c \
	bl808_hal/bl_spi_cli.c \
	bl808_hal/hosal_spi.c \
	bl808_hal/hosal_dma.c \
	bl808_hal/jpeg_head.c \
	bl808_hal/bl_comm_sns.c
	#bl808_hal/bl_mjdec.c \

ifeq ($(CONFIG_WIFI),1)
COMPONENT_SRCS += bl808_hal/bl_wifi.c \
		  bl808_hal/hal_wifi.c
endif

ifeq ($(CONFIG_ENABLE_ETHMAC), 1)
COMPONENT_SRCS += bl808_hal/bl_ethernetif.c
endif

COMPONENT_SRCDIRS := bl808_hal

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_OBJS := $(patsubst %.cpp,%.o, $(COMPONENT_OBJS))

##
ifeq ($(CONFIG_BT),1)
CPPFLAGS += -DCFG_BLE_ENABLE
else
endif

CPPFLAGS += -DARCH_RISCV
ifndef CONFIG_USE_STD_DRIVER
CPPFLAGS += -DBL808_USE_HAL_DRIVER
endif

ifeq ($(CONFIG_USE_XTAL32K),1)
CFLAGS += -DCFG_USE_XTAL32K
endif

endif
