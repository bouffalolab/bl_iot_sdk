# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += BSP_Driver \
                             BSP_Driver/StdDriver/Inc \
                             BSP_Driver/Peripherals \
                             BSP_Driver/platform_print \
                             BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup \
                             BSP_Driver/RISCV/Core/Include \
                             BSP_Common/soft_crc \
                             BSP_Common/partition \
                             BSP_Common/xz \
                             BSP_Common/cipher_suite/inc \
                             BSP_Common/ring_buffer \
                             BSP_Common/usb_core \

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS := 


## This component's src 
COMPONENT_SRCS := BSP_Driver/StdDriver/Src/bl702_uart.c \
                  BSP_Driver/StdDriver/Src/bl702_adc.c \
                  BSP_Driver/StdDriver/Src/bl702_sec_eng.c \
                  BSP_Driver/StdDriver/Src/bl702_dma.c \
                  BSP_Driver/StdDriver/Src/bl702_common.c \
                  BSP_Driver/StdDriver/Src/bl702_glb.c \
                  BSP_Driver/StdDriver/Src/bl702_hbn.c \
                  BSP_Driver/StdDriver/Src/bl702_timer.c \
                  BSP_Driver/StdDriver/Src/bl702_aon.c \
                  BSP_Driver/StdDriver/Src/bl702_pds.c \
                  BSP_Driver/StdDriver/Src/bl702_pwm.c \
                  BSP_Driver/StdDriver/Src/bl702_psram.c \
                  BSP_Driver/StdDriver/Src/bl702_l1c.c \
                  BSP_Driver/StdDriver/Src/bl702_ef_ctrl.c \
                  BSP_Driver/StdDriver/Src/bl702_sf_ctrl.c \
                  BSP_Driver/StdDriver/Src/bl702_sflash.c \
                  BSP_Driver/StdDriver/Src/bl702_xip_sflash.c \
                  BSP_Driver/StdDriver/Src/bl702_xip_sflash_ext.c \
                  BSP_Driver/StdDriver/Src/bl702_sf_cfg.c \
                  BSP_Driver/StdDriver/Src/bl702_sf_cfg_ext.c \
                  BSP_Driver/StdDriver/Src/bl702_dac.c \
                  BSP_Driver/StdDriver/Src/bl702_ir.c \
                  BSP_Driver/StdDriver/Src/bl702_spi.c \
                  BSP_Driver/StdDriver/Src/bl702_i2c.c \
                  BSP_Driver/StdDriver/Src/bl702_cam.c \
                  BSP_Driver/StdDriver/Src/bl702_mjpeg.c \
                  BSP_Driver/platform_print/platform_device.c \
                  BSP_Driver/platform_print/platform_gpio.c \
                  BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup/interrupt.c \
                  BSP_Common/soft_crc/softcrc.c \
                  BSP_Common/xz/xz_crc32.c \
                  BSP_Common/xz/xz_dec_lzma2.c \
                  BSP_Common/xz/xz_dec_stream.c \
                  BSP_Common/xz/xz_decompress.c \
                  BSP_Common/xz/xz_port.c \
                  BSP_Common/cipher_suite/src/bflb_crypt.c \
                  BSP_Common/cipher_suite/src/bflb_hash.c \
                  BSP_Common/cipher_suite/src/bflb_dsa.c \
                  BSP_Common/cipher_suite/src/bflb_ecdsa.c \
                  BSP_Common/ring_buffer/ring_buffer.c \

ifeq ($(CONFIG_BL702_USE_ROM_DRIVER),1)
COMPONENT_SRCS += BSP_Driver/StdDriver/Src/bl702_romapi.c
CPPFLAGS += -DBFLB_USE_ROM_DRIVER
endif

ifeq ($(CONFIG_BL702_USE_USB_DRIVER),1)
COMPONENT_SRCS += BSP_Driver/StdDriver/Src/bl702_usb.c
COMPONENT_SRCS += BSP_Common/usb_core/usbd_core.c
COMPONENT_SRCS += BSP_Common/usb_core/usbd_ctlreq.c
COMPONENT_SRCS += BSP_Common/usb_core/usbd_ioreq.c
endif

ifeq ($(CONFIG_BL702_USE_BSP_PARTITION),1)
COMPONENT_SRCS += BSP_Common/partition/partition.c
endif

ifeq ($(CONFIG_BL702_USE_BSP_STARTUP),1)
COMPONENT_SRCS += BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup/GCC/entry.S
COMPONENT_SRCS += BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup/GCC/start_load.c
COMPONENT_SRCS += BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup/system_bl702.c
endif


COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))

COMPONENT_SRCDIRS := BSP_Driver/StdDriver/Src \
                     BSP_Driver/platform_print \
                     BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup \
                     BSP_Driver/RISCV/Device/Bouffalo/BL702/Startup/GCC \
                     BSP_Common/soft_crc \
                     BSP_Common/cipher_suite/src \
                     BSP_Common/partition/src \
                     BSP_Common/xz \
                     BSP_Common/ring_buffer \
                     BSP_Common/usb_core \

##
CPPFLAGS += -DARCH_RISCV -DBFLB_CRYPT_HARDWARE -DBFLB_PKA_HARDWARE
ifndef CONFIG_USE_STD_DRIVER
CPPFLAGS += -DBFLB_USE_HAL_DRIVER
endif
