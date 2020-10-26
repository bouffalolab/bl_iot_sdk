# Component Makefile
#
## These include paths would be exported to project level
HAL_DRV_HAS_CONFIG := 0

ifeq ($(CONFIG_CHIP_NAME),BL606)
HAL_DRV_HAS_CONFIG := 1
include $(COMPONENT_PATH)/bl606.mk
endif

ifeq ($(CONFIG_CHIP_NAME),BL602)
HAL_DRV_HAS_CONFIG := 1
include $(COMPONENT_PATH)/bl602.mk
endif

ifeq ($(CONFIG_CHIP_NAME),BL702)
HAL_DRV_HAS_CONFIG := 1
include $(COMPONENT_PATH)/bl702.mk
endif

ifeq ($(HAL_DRV_HAS_CONFIG),0)
$(error "Please Set CONFIG_CHIP_NAME, Avaliable list: BL606 BL602 BL702")
endif
