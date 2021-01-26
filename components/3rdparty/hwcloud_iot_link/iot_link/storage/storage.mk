STORAGE_MODULE_SRC = ${wildcard $(iot_link_root)/storage/*.c}
C_SOURCES += $(STORAGE_MODULE_SRC)

STORAGE_MODULE_INC = -I $(iot_link_root)/storage
C_INCLUDES += $(STORAGE_MODULE_INC)
