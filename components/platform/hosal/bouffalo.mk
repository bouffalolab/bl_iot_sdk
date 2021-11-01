# Component Makefile
#
## These include paths would be exported to project level
HAL_DRV_HAS_CONFIG := 0

SOC_DRV = $(shell echo $(CONFIG_CHIP_NAME) | tr A-Z a-z)
HAL_DRV_HAS_CONFIG := 1
include $(COMPONENT_PATH)/$(SOC_DRV).mk

COMPONENT_ADD_INCLUDEDIRS += include

ifeq ($(HAL_DRV_HAS_CONFIG),0)
$(error "Please Set CONFIG_CHIP_NAME, Avaliable list: BL606 BL602 BL702 BL606p BL808")
endif
