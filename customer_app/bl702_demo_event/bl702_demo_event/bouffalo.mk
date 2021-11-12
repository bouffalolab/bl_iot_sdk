#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

ifeq ($(CONFIG_ZIGBEE), 1)
include $(BL60X_SDK_PATH)/components/network/zigbee/zigbee_common.mk
endif
ifeq ($(CONFIG_BT),1)
include $(BL60X_SDK_PATH)/components/network/ble/ble_common.mk
endif

ifeq ($(CONFIG_LINK_CUSTOMER),1)

ifeq ($(CONFIG_PDS_CPU_PWROFF),1)
LINKER_SCRIPTS := bl702_demo_event_pds.ld
endif

ifeq ($(CONFIG_SIMPLE_MASTER),1)
LINKER_SCRIPTS := bl702_demo_event_simple_master.ld
endif

COMPONENT_ADD_LDFLAGS += -L $(BL60X_SDK_PATH)/customer_app/bl702_demo_event/bl702_demo_event/ \
                         $(addprefix -T ,$(LINKER_SCRIPTS))
##
COMPONENT_ADD_LINKER_DEPS := $(addprefix ,$(LINKER_SCRIPTS))

endif ## CONFIG_LINK_CUSTOMER

ifeq ($(CONFIG_USB_CDC),1)
CPPFLAGS += -DCFG_USB_CDC_ENABLE
endif

ifeq ($(CONFIG_EFLASH_LOADER),1)
CPPFLAGS += -DCFG_EFLASH_LOADER_ENABLE
endif

ifeq ($(CONFIG_RFPHY_CLI),1)
CPPFLAGS += -DCFG_RFPHY_CLI_ENABLE
endif

ifeq ($(CONFIG_ZIGBEE_ROUTER_STARTUP),1)
CPPFLAGS += -DCFG_ZIGBEE_ROUTER_STARTUP
endif

ifeq ($(CONFIG_ZIGBEE_ACTIVE_END_DEVICE_STARTUP),1)
CPPFLAGS += -DCFG_ZIGBEE_ACTIVE_END_DEVICE_STARTUP
endif

ifeq ($(CONFIG_ZIGBEE_SLEEPY_END_DEVICE_STARTUP),1)
CPPFLAGS += -DCFG_ZIGBEE_SLEEPY_END_DEVICE_STARTUP
endif

ifeq ($(CONFIG_ZIGBEE_COORDINATOR_STARTUP),1)
CPPFLAGS += -DCFG_ZIGBEE_COORDINATOR_STARTUP
endif

ifeq ($(CONFIG_ETHERNET), 1)
CFLAGS   += -DCFG_ETHERNET_ENABLE
CPPFLAGS += -DCFG_ETHERNET_ENABLE
endif

ifeq ($(CONFIG_USE_PSRAM), 1)
CFLAGS   += -DCFG_USE_PSRAM
CPPFLAGS += -DCFG_USE_PSRAM
endif
