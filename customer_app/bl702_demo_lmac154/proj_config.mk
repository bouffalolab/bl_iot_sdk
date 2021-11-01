#
#compiler flag config domain
#

#
#board config domain
#

#firmware config domain
#

CONFIG_CHIP_NAME := BL702
CONFIG_USB_CDC := 1
CONFIG_GEN_ROM := 0
CONFIG_LINK_RAM := 0
CONFIG_BUILD_ROM_CODE := 1

ifeq ($(CONFIG_USB_CDC),1)
CONFIG_BL702_USE_USB_DRIVER := 1
endif

CONFIG_BL702_USE_ROM_DRIVER := 1

LOG_ENABLED_COMPONENTS := hosal vfs
