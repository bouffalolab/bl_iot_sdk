ifeq ($(strip $(PROJECT_BOARD)),evb)
include $(COMPONENT_PATH)/evb/evb.mk

ifdef CONFIG_SYS_APP_TASK_STACK_SIZE
CPPFLAGS += -DSYS_APP_TASK_STACK_SIZE=$(CONFIG_SYS_APP_TASK_STACK_SIZE)
endif

ifdef CONFIG_SYS_APP_TASK_PRIORITY
CPPFLAGS += -DSYS_APP_TASK_PRIORITY=$(CONFIG_SYS_APP_TASK_PRIORITY)
endif

ifeq ($(CONFIG_SYS_VFS_ENABLE),1)
CPPFLAGS += -DSYS_VFS_ENABLE
endif

ifeq ($(CONFIG_SYS_VFS_UART_ENABLE),1)
CPPFLAGS += -DSYS_VFS_UART_ENABLE
endif

ifeq ($(CONFIG_SYS_AOS_CLI_ENABLE),1)
CPPFLAGS += -DSYS_AOS_CLI_ENABLE
endif

ifeq ($(CONFIG_SYS_AOS_LOOP_ENABLE),1)
CPPFLAGS += -DSYS_AOS_LOOP_ENABLE
endif

ifeq ($(CONFIG_SYS_BLOG_ENABLE),1)
CPPFLAGS += -DSYS_BLOG_ENABLE
endif

ifeq ($(CONFIG_SYS_DMA_ENABLE),1)
CPPFLAGS += -DSYS_DMA_ENABLE
endif

ifeq ($(CONFIG_SYS_LOOPRT_ENABLE),1)
CPPFLAGS += -DSYS_LOOPRT_ENABLE
endif

ifeq ($(CONFIG_SYS_USER_VFS_ROMFS_ENABLE),1)
CPPFLAGS += -DSYS_USER_VFS_ROMFS_ENABLE
endif

ifeq ($(CONFIG_ZIGBEE_DONGLE_ENABLE), 1)
CFLAGS   += -DCFG_ZIGBEE_DONGLE_EN
CPPFLAGS += -DCFG_ZIGBEE_DONGLE_EN
endif

ifeq ($(CONFIG_OPENTHREAD_ENABLE), 1)
CPPFLAGS += -DCFG_OPENTHREAD_EN
endif

ifeq ($(CONFIG_SYS_COMMON_MAIN_ENABLE),1)
## This component's src 
COMPONENT_SRCS1 += bfl_main.c
COMPONENT_SRCDIRS += .
COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS1))
COMPONENT_OBJS := $(patsubst %.S,%.o, $(COMPONENT_OBJS))
endif

else
$(error "Please Set PROJECT_BOARD:= [your board name] at Makefile")
endif
