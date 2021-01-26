################################################################################
# this is used for compile the iotlink
################################################################################
vpath %.c $(iot_link_root)/os/freertos_rtk

FREERTOS_RTK_IMP_SOURCE  = ${wildcard $(iot_link_root)/os/freertos_rtk/*.c}
C_SOURCES += $(FREERTOS_RTK_IMP_SOURCE)

FREERTOS_RTK_IMP_INC = -I $(iot_link_root)/os/freertos_rtk
C_INCLUDES += $(FREERTOS_RTK_IMP_INC)

C_DEFS += -D CONFIG_FREERTOS_RTK_ENABLE=1
