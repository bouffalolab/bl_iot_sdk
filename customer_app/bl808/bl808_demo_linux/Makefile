#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := bl808_demo_linux
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

COMPONENTS_BLSYS   := blog

M0_COMPONENTS += freertos_e907 newlibc hal_drv vfs yloop cli utils blmtd
M0_COMPONENTS += startup_bl808
M0_COMPONENTS += bl808_e907_std
M0_COMPONENTS += hosal blfdt
M0_COMPONENTS += romfs
M0_COMPONENTS += unxz

D0_COMPONENTS += bl808_c906_freertos bl808 bl808_std newlibc hosal vfs yloop utils cli blog blfdt

# wifi module
COMPONENTS_NETWORK := lwip lwip_dhcpd dns_server netutils mbedtls_lts
COMPONENTS_NETWORK += bl808_wifi wifi_manager blcrypto_suite wpa_supplicant wifi_hosal
COMPONENTS_NETWORK += bl606p_phyrf rfparam_adapter_tmp
COMPONENTS_NETWORK += bl_os_adapter

# amp
COMPONENTS_AMP := bl808_xram bl808_ring bl808_net remote_net_manager

INCLUDE_COMPONENTS += $(PROJECT_NAME)

ifeq ($(CPU_ID), M0)
INCLUDE_COMPONENTS += $(M0_COMPONENTS)
INCLUDE_COMPONENTS += $(COMPONENTS_BLSYS)
INCLUDE_COMPONENTS += $(COMPONENTS_VFS)
INCLUDE_COMPONENTS += $(COMPONENTS_NETWORK)
INCLUDE_COMPONENTS += $(COMPONENTS_AMP)
endif

ifeq ($(CPU_ID), D0)
INCLUDE_COMPONENTS += $(D0_COMPONENTS)
endif

include $(BL60X_SDK_PATH)/make_scripts_riscv/project_common.mk
