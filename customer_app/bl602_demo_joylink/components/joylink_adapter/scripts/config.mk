# riscv64-unknown-elf-gcc (SiFive GCC 8.3.0-2019.08.0) 8.3.0
CROSS_COMPILE := /work/disk1/share/toolchain/toolchain_riscv_sifive_linux64/bin/riscv64-unknown-elf-

# x86 arch 
CFLAGS := -DJL_SEND_DATA_BY_THREAD -std=gnu99 -Os -gdwarf -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fshort-enums -ffreestanding -fno-strict-aliasing -Wall -Wextra -Wno-old-style-declaration -march=rv32imfc -mabi=ilp32f -save-temps=obj
# other arch 
# CFLAGS := -DuECC_PLATFORM=uECC_arch_other -D__LINUX_PAL__ -DJOYLINK_SDK_EXAMPLE_TEST -D_SAVE_FILE_

LDFLAGS = -lpthread -lm

USE_JOYLINK_JSON= no

#----------------------------------------------以下固定参数
#CFLAGS += -D_IS_DEV_REQUEST_ACTIVE_SUPPORTED_ -D_GET_HOST_BY_NAME_
CFLAGS += -D_IS_DEV_REQUEST_ACTIVE_SUPPORTED_ -D_GET_HOST_BY_NAME_ -DuECC_PLATFORM=uECC_arch_other

TARGET_DIR = ${TOP_DIR}/target
TARGET_LIB = ${TARGET_DIR}/lib
TARGET_BIN = ${TARGET_DIR}/bin

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
RANLIB=$(CROSS_COMPILE)ranlib
STRIP=$(CROSS_COMPILE)strip

RM = rm -rf
CP = cp -rf
MV = mv -f


