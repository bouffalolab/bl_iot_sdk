ifeq ($(strip $(PROJECT_BOARD)),evb)
ifeq ("$(CPU_ID)", "D0")
include $(COMPONENT_PATH)/evb/d0/evb_d0.mk
else
include $(COMPONENT_PATH)/evb/evb.mk
endif
else
$(error "Please Set PROJECT_BOARD:= [your board name] at Makefile")
endif

