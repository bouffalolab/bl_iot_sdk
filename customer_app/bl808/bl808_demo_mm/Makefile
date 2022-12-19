#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := bl808_demo_mm
PROJECT_PATH := $(abspath .)
PROJECT_BOARD := evb
export PROJECT_PATH PROJECT_BOARD
#CONFIG_TOOLPREFIX :=

-include ./proj_config.mk

ifeq ($(origin BL60X_SDK_PATH), undefined)
BL60X_SDK_PATH_GUESS ?= $(shell pwd)
BL60X_SDK_PATH ?= $(BL60X_SDK_PATH_GUESS)/../../..
$(info ****** Please SET BL60X_SDK_PATH ******)
$(info ****** Trying SDK PATH [$(BL60X_SDK_PATH)])
endif

COMPONENTS_CAM   :=smart_sensor sccb bl808_mm_cli_demo
INCLUDE_COMPONENTS += $(COMPONENTS_CAM)

COMPONENTS_POSIX := freertos_posix
INCLUDE_COMPONENTS += bl808_c906_freertos bl808 bl808_std newlibc lwip lwip_dhcpd hosal vfs yloop utils cli blog  blfdt blai_nn blai_npu_encoder
INCLUDE_COMPONENTS += $(COMPONENTS_CAM)
INCLUDE_COMPONENTS += $(COMPONENTS_POSIX)
INCLUDE_COMPONENTS += $(PROJECT_NAME)
include $(BL60X_SDK_PATH)/make_scripts_riscv/project_common.mk
