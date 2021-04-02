#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

ifeq ("$(CONFIG_CHIP_NAME)", "BL606p")

ifeq ("$(CPU_ID)", "M1")
CFLAGS += -DBFLB_USE_HAL_DRIVER -DCPU_M1 -DARCH_RISCV
else ifeq ("$(CPU_ID)", "D0")
CFLAGS += -DBFLB_USE_HAL_DRIVER -DCPU_D0 -DARCH_RISCV
endif
include $(BL60X_SDK_PATH)/make_scripts_thead_riscv/project.mk

endif

ifeq ("$(CONFIG_CHIP_NAME)", "BL808")
CFLAGS += -DBFLB_USE_HAL_DRIVER -DCPU_D0 -DARCH_RISCV
include $(BL60X_SDK_PATH)/make_scripts_thead_riscv/project.mk
endif
