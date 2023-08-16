#[[
Copyright (c) 2016-2023 Bouffalolab.

This file is part of
    *** Bouffalolab Software Dev Kit ***
     (see www.bouffalolab.com).

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
  3. Neither the name of Bouffalo Lab nor the names of its contributors
     may be used to endorse or promote products derived from this software
     without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
]]

﻿################# Add global include #################
list(APPEND ADD_INCLUDE
"${CMAKE_CURRENT_SOURCE_DIR}/hal_drv/inc"
"${CMAKE_CURRENT_SOURCE_DIR}/std_drv/inc"
"${CMAKE_CURRENT_SOURCE_DIR}/regs"
"${CMAKE_CURRENT_SOURCE_DIR}/startup/${CPU_ID}/source"
"${CMAKE_CURRENT_SOURCE_DIR}/risc-v/Core/Include"
"${CMAKE_CURRENT_SOURCE_DIR}/risc-v/csi_dsp/include"
"${CMAKE_CURRENT_SOURCE_DIR}/risc-v"
)
#######################################################

################# Add private include #################
list(APPEND ADD_PRIVATE_INCLUDE
"${CMAKE_CURRENT_SOURCE_DIR}/hal_drv/default_config"
)
#######################################################

############## Add current dir source files ###########
file(GLOB_RECURSE sources
#"${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/hal_drv/src/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/risc-v/rv_*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/startup/${CPU_ID}/source/interrupt.c"
"${CMAKE_CURRENT_SOURCE_DIR}/startup/${CPU_ID}/source/system_bl808.c"
"${CMAKE_CURRENT_SOURCE_DIR}/startup/${CPU_ID}/source/GCC/*.S"
"${CMAKE_CURRENT_SOURCE_DIR}/startup/${CPU_ID}/source/GCC/start_load.c"
)
list(APPEND ADD_SRCS  ${sources})

list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_acomp.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_adc.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_aon.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_audio.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_cam.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_iso11898.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_clock.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_common.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dac.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dbi.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dma.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dma2d.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dsi.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_dvp_tsrc.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_ef_ctrl.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_ef_cfg.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_emac.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_glb.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_glb_gpio.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_hbn.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_i2c.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_i2s.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_ipc.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_ir.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_isp_axi_ctrl.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_isp_misc.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_l1c.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_lz4d.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_mjdec.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_mjpeg.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_osd_blend.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_osd_draw.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_osd_probe.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_pds.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_psram.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_psram_uhs.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_pwm.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sdh.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sec_dbg.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sec_eng.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sflash.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sf_cfg.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sf_ctrl.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_spi.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_timer.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_touch.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_tzc_sec.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_aupdm.c")
#list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_uart.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_usb.c")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_xip_sflash.c")
if(${CPU_ID} STREQUAL "m0" )
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_uhs_phy.c")  #wljin
endif()
if(${BOOTROM} STREQUAL "y")
list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_romdriver_e907.c")
endif()

if(NOT CONFIG_ROMAPI)
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_ef_ctrl.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_pds.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sflash.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_uart.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_xip_sflash.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sf_cfg.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_glb.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_glb_gpio.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_l1c.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_aon.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_common.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_hbn.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_sf_ctrl.c")
elseif(CONFIG_ROMAPI)
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_romapi_patch.c")
	list(APPEND ADD_SRCS  "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_romapi_e907.c")
else()
	message(FATAL_ERROR "SUPPORT_ROMAPI param error,y or n")
endif()
# Sv39 is only available on D0
if(NOT(${CPU_ID} STREQUAL "d0"))
    list(REMOVE_ITEM ADD_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/risc-v/rv_Sv39.c"
    )
endif()

if(${CPU_ID} STREQUAL "d0" )
	if(${CONFIG_ROMAPI} STREQUAL "y")
    	message(FATAL_ERROR "D0 or D1 do not support romapi")
	endif()
endif()

# aux_source_directory(src ADD_SRCS)
list(REMOVE_ITEM ADD_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/std_drv/src/bl808_snflash.c"
)
#######################################################

########### Add required/dependent components #########
list(APPEND ADD_REQUIREMENTS common)
#######################################################

############ Add static libs ##########################
# if(CONFIG_COMPONENT1_INCLUDE_STATIC_LIB)
#     list(APPEND ADD_STATIC_LIB "lib/libtest.a")
# endif()
if(${CPU_ID} STREQUAL "m0")
    list(APPEND ADD_STATIC_LIB "${CMAKE_CURRENT_SOURCE_DIR}/risc-v/csi_dsp/lib/libcsi_xt900p32f_dsp.a")
endif()

#######################################################

############ Add dynamic libs #########################
# list(APPEND ADD_DYNAMIC_LIB "lib/arch/v831/libmaix_nn.so"
#                             "lib/arch/v831/libmaix_cam.so"
# )
#######################################################

############ Add global compile option ################
#add components denpend on this component
if(CONFIG_HALAPI)
list(APPEND ADD_DEFINITIONS -DBFLB_USE_HAL_DRIVER)
endif()
string(TOUPPER ${CPU_ID} CPUID)
list(APPEND ADD_DEFINITIONS -DARCH_RISCV -DCPU_${CPUID})
if(CONFIG_DUALCORE)
list(APPEND ADD_DEFINITIONS -DDUALCORE)
endif()
#######################################################

############ Add private compile option ################
#add compile option for this component that won't affect other modules
# list(APPEND ADD_DEFINITIONS_PRIVATE -DAAAAA=1)
#######################################################

generate_library()
