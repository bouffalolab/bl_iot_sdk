ifeq ($(strip $(PROJECT_BOARD)),evb)
include $(COMPONENT_PATH)/evb/evb.mk
else
$(error "Please Set PROJECT_BOARD:= [your board name] at Makefile")
endif
