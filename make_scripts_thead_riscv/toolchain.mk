##change to your toolchain path
SRC_ARCH=$(shell uname -m)
SRC_OS=$(shell uname | cut -d '_' -f1)

ifeq ($(SRC_OS), MSYS)
SRC_ARCH := x86_32
endif

CONFIG_TOOLPREFIX ?= $(BL60X_SDK_PATH)/toolchain/riscv/Thead_riscv/$(SRC_OS)_$(SRC_ARCH)/bin/riscv64-unknown-elf-
