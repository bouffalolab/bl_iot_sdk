
PROJECT_NAME := bl808_demo_event
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
COMPONENTS_VFS     :=
COMPONENTS_DEMO_CLI := bl808_wlan_cli_demo

# wifi module
COMPONENTS_NETWORK := lwip lwip_dhcpd dns_server netutils mbedtls_lts
COMPONENTS_NETWORK += wifi wifi_manager blcrypto_suite wpa_supplicant wifi_hosal wifi_bt_coex
COMPONENTS_NETWORK += bl606p_phyrf rfparam_adapter_tmp
COMPONENTS_NETWORK += bl_os_adapter

INCLUDE_COMPONENTS += freertos_e907 vfs yloop cli utils newlibc blmtd easyflash4 boot_cpu0 freertos_e907_helper coredump
INCLUDE_COMPONENTS += startup_bl808
INCLUDE_COMPONENTS += bl808_e907_std
INCLUDE_COMPONENTS += hosal blfdt bl808_audio
INCLUDE_COMPONENTS += romfs usb_stack
INCLUDE_COMPONENTS += fatfs sdh_helper
ifeq ($(CONFIG_BT_ENABLE),1)
INCLUDE_COMPONENTS += btblecontroller btprofile
ifeq ($(CONFIG_BTBLE_STACK),1)
INCLUDE_COMPONENTS += btblestack
else
INCLUDE_COMPONENTS += blestack
endif
endif

ifeq ($(CONFIG_COMPONENT_BUGKILLER_ENABLE),1)
INCLUDE_COMPONENTS += bugkiller_freertos
endif

INCLUDE_COMPONENTS += $(COMPONENTS_BLSYS)
INCLUDE_COMPONENTS += $(COMPONENTS_VFS)
INCLUDE_COMPONENTS += $(COMPONENTS_DEMO_CLI)
INCLUDE_COMPONENTS += $(COMPONENTS_NETWORK)
INCLUDE_COMPONENTS += $(PROJECT_NAME)

include $(BL60X_SDK_PATH)/make_scripts_riscv/project_common.mk
