# Copyright (C) 2016-2020, BouffaloLab Ltd.
# All Rights Reserved.

CPU_ARCH := RISCV
MCPU := e907
#E906 rv32imacxthead ilp32 e906
#E906F rv32imacfxthead ilp32f e906
#E906FD rv32imacfdxthead ilp32d e906
MARCH := rv32imafcpzp64_xtheade
MABI := ilp32f

CROSS_COMPILE := riscv64-unknown-elf-

FLASH_LINK_FILE_PATH = BSP_Driver/$(DEVICE)_BSP_Driver/Startup/$(CPU_ID)/bl808_flash.ld
RAM_LINK_FILE_PATH = BSP_Driver/$(DEVICE)_BSP_Driver/Startup/$(CPU_ID)/bl808_ram.ld
CASE_DEFAULT_LINK_SCRIPT := $(RAM_LINK_FILE_PATH)


COMMON_CFLAGS:= 
COMMON_INCLUDE:= 
GLOBAL_INCLUDE = -I BSP_Driver/$(DEVICE)_BSP_Driver/RISCV/Core/Include \
                 -I BSP_Driver/$(DEVICE)_BSP_Driver/Startup/$(CPU_ID)/Source \
                 -I ChipTest/BootROM \

GLOBAL_CFLAGS = -DARCH_RISCV -DBFLB_CRYPT_HARDWARE -DBFLB_PKA_HARDWARE -DCPU_$(CPU_ID)
ifeq ($(BOOTROM),y)
    GLOBAL_CFLAGS += -DBOOTROM -DBFLB_USE_HAL_DRIVER
ifeq ($(DV_COSIM),y)
    GLOBAL_CFLAGS += -DDV_COSIM
endif
endif

ifeq ($(TARGETS),Eflash_Loader)
    GLOBAL_CFLAGS += -DBFLB_EFLASH_LOADER
endif
ifeq ($(TARGETS),Boot2)
    GLOBAL_CFLAGS += -DBFLB_USE_HAL_DRIVER
endif