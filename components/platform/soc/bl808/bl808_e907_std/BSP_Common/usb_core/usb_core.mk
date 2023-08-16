#
ifeq ($(USB_COMMON),y)
SUB_MODULE_DIR:= $(MODULE_DIR)/usb_core
SUB_MODULE_OUT_DIR:= $(MODULE_OUT_DIR)

SUB_MODULE_SRC_DIR := $(SUB_MODULE_DIR)

COMMON_INCLUDE += -I $(MODULE_DIR)/usb_core
GLOBAL_INCLUDE += -I $(MODULE_DIR)/usb_core

usb_core_sources := usbd_core.c \
                    usbd_ctlreq.c \
                    usbd_ioreq.c \
                    #usb_mem.c \
                    

usb_core_objs := $(addprefix $(SUB_MODULE_OUT_DIR)/, $(subst .c,.o,$(usb_core_sources)))

bsp_common_objs_target += $(usb_core_objs)

$(SUB_MODULE_OUT_DIR)/%.o:$(SUB_MODULE_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(COMMON_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $< -o $@
endif
