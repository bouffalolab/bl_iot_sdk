include $(COMPONENT_PATH)/../ble_common.mk

##################################################################################
#
# Component Makefile
#
##################################################################################
ble_stack_srcs_dirs := src/bl_hci_wrapper \
					src/port \
					src/common \
					src/common/tinycrypt/source  \
					src/hci_onchip   \
					src/host   \
					src/host_cmdproc   \
					src/services

ifeq ($(CONFIG_BT_OAD_SERVER),1)
ble_stack_srcs_dirs+= src/profiles/oad
endif

ifeq ($(CONFIG_BT_STACK_CLI),1)
ble_stack_srcs_dirs+= src/cli_cmds
endif

ble_stack_srcs_include_dirs    += src/port/include \
                                src/common \
								src/common/include \
								src/common/include/zephyr  \
								src/common/include/misc  \
								src/common/include/toolchain \
								src/common/tinycrypt/include/tinycrypt  \
								src/hci_onchip   \
								src/bl_hci_wrapper \
								src/host   \
								src/include/bluetooth  \
								src/include/drivers/bluetooth  \
								src/profiles \
								src/host_cmdproc \
								src/cli_cmds \
								src/services

ifneq ($(CONFIG_BT_OAD_SERVER)_$(CONFIG_BT_OAD_CLIENT),0_0)
ble_stack_srcs_include_dirs    += src/profiles/oad
endif

# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS := $(ble_stack_srcs_include_dirs)

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS   :=

## This component's src
ble_stack_srcs  := src/port/bl_port.c \
					src/common/atomic_c.c \
					src/common/buf.c \
					src/common/log.c \
					src/common/poll.c \
					src/common/rpa.c \
					src/common/work_q.c \
					src/common/utils.c \
					src/common/dec.c \
					src/common/dummy.c \
					src/common/tinycrypt/source/aes_decrypt.c \
					src/common/tinycrypt/source/aes_encrypt.c \
					src/common/tinycrypt/source/cbc_mode.c \
					src/common/tinycrypt/source/ccm_mode.c \
					src/common/tinycrypt/source/cmac_mode.c \
					src/common/tinycrypt/source/ctr_mode.c \
					src/common/tinycrypt/source/ctr_prng.c \
					src/common/tinycrypt/source/ecc.c \
					src/common/tinycrypt/source/ecc_dh.c \
					src/common/tinycrypt/source/ecc_dsa.c \
					src/common/tinycrypt/source/ecc_platform_specific.c \
					src/common/tinycrypt/source/hmac.c \
					src/common/tinycrypt/source/hmac_prng.c \
					src/common/tinycrypt/source/sha256.c \
					src/common/tinycrypt/source/utils.c \
					src/bl_hci_wrapper/bl_hci_wrapper.c \
					src/hci_onchip/hci_driver.c \
					src/host/att.c \
					src/host/conn.c \
					src/host/crypto.c \
					src/host/gatt.c \
					src/host/hci_core.c \
					src/host/hci_ecc.c \
					src/host/l2cap.c \
					src/host/uuid.c \

ifneq ($(CONFIG_DISABLE_BT_SMP), 1)
ble_stack_srcs  += src/host/smp.c \
                   src/host/keys.c
endif

ifeq ($(CONFIG_BT_OAD_CLIENT),1)
ble_stack_srcs   += src/host_cmdproc/oadc_cmdproc.c
endif

ifneq ($(CONFIG_DBG_RUN_ON_FPGA), 1)
ble_stack_srcs   += src/host/settings.c
endif

ifeq ($(CONFIG_BT_OAD_SERVER),1)
ble_stack_srcs   += src/profiles/oad/oad_api.c \
					src/profiles/oad/oad_service.c
endif

ifeq ($(CONFIG_BT_STACK_CLI),1)
ble_stack_srcs   += src/cli_cmds/ble_cli_cmds.c \
					src/cli_cmds/pts_cli_cmds.c
endif

ifeq ($(CONFIG_BT_BAS_SERVER),1)
ble_stack_srcs   += src/services/bas.c
endif

ifeq ($(CONFIG_BT_SCPS_SERVER),1)
ble_stack_srcs   += src/services/scps.c
endif

ifeq ($(CONFIG_BT_DIS_SERVER),1)
ble_stack_srcs   += src/services/dis.c
endif

ifeq ($(CONFIG_BT_WIFIPROV_SERVER),1)
ble_stack_srcs   += src/services/wifi_prov.c
endif

ifeq ($(CONFIG_BLE_TP_SERVER),1)
ble_stack_srcs   += src/services/ble_tp_svc.c
endif

ifeq ($(CONFIG_BLE_MULTI_ADV),1)
ble_stack_srcs   += src/host/multi_adv.c
endif


COMPONENT_SRCS := $(ble_stack_srcs)

COMPONENT_OBJS   := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := $(ble_stack_srcs_dirs)
