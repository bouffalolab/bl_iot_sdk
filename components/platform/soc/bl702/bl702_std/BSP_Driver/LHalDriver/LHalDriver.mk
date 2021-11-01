#clear_vars
LOCAL_SRCS_FILE:=

LHAL_MODULE_DIR:= BSP_Driver/$(DEVICE)_BSP_Driver/LHalDriver
LHAL_MODULE_OUT_DIR:= $(TARGET_OUT_PATH)/BSP_Driver/$(DEVICE)_BSP_Driver/LHalDriver
LHAL_MODULE_SRC_DIR := $(LHAL_MODULE_DIR)/Src

#hardware lay lib dir
STD_DIRVER_DIR = BSP_Driver/$(DEVICE)_BSP_Driver/StdDriver
STD_DRIVER_SRC_DIR = $(STD_DIRVER_DIR)/Src

#hal lay lib dir
HAL_DRIVER_DIR = HAL
HAL_DRIVER_SRC_DIR = $(HAL_DRIVER_DIR)/Src

LHALDRIVER_CFLAGS:= 
LHALDRIVER_INCLUDE:=  -I $(LHAL_MODULE_DIR)/Inc -I $(STD_DIRVER_DIR)/Inc -I $(HAL_DRIVER_DIR)/Inc

#lhaldriver_sources := lhal_bl702_uart.c  \

lhaldriver_sources := lhal_bl702_uart.c lhal_bl702_dma.c lhal_bl702_spi.c lhal_bl702_adc.c lhal_bl702_dac.c lhal_bl702_pin.c lhal_bl702_pwm.c lhal_bl702_wtd.c lhal_bl702_timer.c lhal_bl702_i2c.c \

lhaldriver_objs := $(addprefix $(LHAL_MODULE_OUT_DIR)/, $(subst .c,.o,$(lhaldriver_sources)))
base_objects += $(lhaldriver_objs)

$(LHAL_MODULE_OUT_DIR)/%.o:$(LHAL_MODULE_SRC_DIR)/%.c 
	@mkdir -p $(dir $@)
	@echo "cc $<"
	$(AT)$(CC) -c $(GLOBAL_CFLAGS) $(LHALDRIVER_CFLAGS) $(GLOBAL_INCLUDE) $(COMMON_INCLUDE) $(LHALDRIVER_INCLUDE) $< -o $@

.PHONY: lhaldriver
lhaldriver: $(lhaldriver_objs)
	@echo  "lhaldriver_objs is $(lhaldriver_objs)"
