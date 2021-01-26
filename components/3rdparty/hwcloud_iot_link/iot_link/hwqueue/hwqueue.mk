################################################################################
# this is used for compile the queue modules
################################################################################

vpath %.c $(iot_link_root)/hwqueue

ifeq ($(CONFIG_LINKQUEUE_ENABLE), y)
    
    C_SOURCES += ${wildcard $(iot_link_root)/hwqueue/*.c} 
    C_INCLUDES += -I $(iot_link_root)/hwqueue

endif
