#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := bl602_boot2_mini
PROJECT_PATH := $(abspath .)
PROJECT_BOARD := evb
PROJECT_COMPONENT := $(abspath .)/bl602_boot2_mini
export PROJECT_PATH PROJECT_BOARD PROJECT_COMPONENT
#CONFIG_TOOLPREFIX :=

-include ./proj_config.mk

ifeq ($(origin BL60X_SDK_PATH), undefined)
BL60X_SDK_PATH_GUESS ?= $(shell pwd)
BL60X_SDK_PATH ?= $(BL60X_SDK_PATH_GUESS)/../..
$(info ****** Please SET BL60X_SDK_PATH ******)
$(info ****** Trying SDK PATH [$(BL60X_SDK_PATH)])
endif

INCLUDE_COMPONENTS += bl602 bl602_std
INCLUDE_COMPONENTS += bl602_boot2_mini

include $(BL60X_SDK_PATH)/make_scripts_riscv/project.mk

