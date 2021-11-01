# Copyright (C) 2016-2020, BouffaloLab Ltd.
# All Rights Reserved.

CPU_ARCH := RISCV
MCPU := riscv-e24
MARCH := rv32imafc
MABI := ilp32f

CROSS_COMPILE := riscv64-unknown-elf-
ROM_LINK_FILE_PATH = BSP_Driver/$(DEVICE)_BSP_Driver/bl702_rom.ld
FLASH_LINK_FILE_PATH = BSP_Driver/$(DEVICE)_BSP_Driver/bl702_flash.ld
RAM_LINK_FILE_PATH = BSP_Driver/$(DEVICE)_BSP_Driver/bl702_ram.ld
CASE_DEFAULT_LINK_SCRIPT = BSP_Driver/$(DEVICE)_BSP_Driver/bl702_flash.ld

COMMON_CFLAGS:= 
COMMON_INCLUDE:= 
GLOBAL_INCLUDE = -I BSP_Driver/$(DEVICE)_BSP_Driver/RISCV/Core/Include \
                 -I BSP_Driver/$(DEVICE)_BSP_Driver/RISCV/Device/Bouffalo/$(DEVICE)/Startup \
                 -I BSP_Driver/$(DEVICE)_BSP_Driver/RISCV/Device/Bouffalo/$(DEVICE)/Startup/GCC 

GLOBAL_CFLAGS = -DARCH_RISCV -DBFLB_CRYPT_HARDWARE -DBFLB_PKA_HARDWARE
ifeq ($(BOOTROM),y)
    GLOBAL_CFLAGS += -DBOOTROM
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