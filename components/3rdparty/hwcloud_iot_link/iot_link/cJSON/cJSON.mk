################################################################################
# this is used for compile the at modules
# make sure that this module depends on the driver module
# make sure driver module is enabled
################################################################################

vpath %.c $(iot_link_root)/cJSON


ifeq ($(CONFIG_CJSON_ENABLE),y)

    C_SOURCES += ${wildcard $(iot_link_root)/cJSON/*.c}     		
    C_INCLUDES += -I $(iot_link_root)/cJSON
    C_DEFS += -D CONFIG_JSON_ENABLE=1
    LDFLAGS += -u _printf_float
        
endif


