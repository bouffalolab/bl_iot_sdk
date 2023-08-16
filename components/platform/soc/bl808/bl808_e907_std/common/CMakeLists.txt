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
"${CMAKE_CURRENT_SOURCE_DIR}/ring_buffer"
"${CMAKE_CURRENT_SOURCE_DIR}/soft_crc"
"${CMAKE_CURRENT_SOURCE_DIR}/memheap"
"${CMAKE_CURRENT_SOURCE_DIR}/misc"
"${CMAKE_CURRENT_SOURCE_DIR}/list"
"${CMAKE_CURRENT_SOURCE_DIR}/device"
"${CMAKE_CURRENT_SOURCE_DIR}/partition"
"${CMAKE_CURRENT_SOURCE_DIR}/bl_math"
"${CMAKE_CURRENT_SOURCE_DIR}/pid"
"${CMAKE_CURRENT_SOURCE_DIR}/timestamp"
)
#######################################################

################# Add private include #################
# list(APPEND ADD_PRIVATE_INCLUDE
# )
#######################################################

############## Add current dir source files ###########
file(GLOB_RECURSE sources
"${CMAKE_CURRENT_SOURCE_DIR}/ring_buffer/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/soft_crc/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/memheap/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/misc/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/device/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/partition/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/bl_math/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/pid/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/timestamp/*.c"
)

#aux_source_directory(. sources)
list(APPEND ADD_SRCS  ${sources})
#######################################################

########### Add required/dependent components #########
#list(APPEND ADD_REQUIREMENTS xxx)
#######################################################

############ Add static libs ##########################
#list(APPEND ADD_STATIC_LIB "libxxx.a")
#######################################################

############ Add dynamic libs #########################
# list(APPEND ADD_DYNAMIC_LIB "libxxx.so"
# )
#######################################################

############ Add global compile option ################
#add components denpend on this component
string(TOUPPER ${CHIP} CHIPNAME)
list(APPEND ADD_DEFINITIONS -D${CHIPNAME})
#######################################################

############ Add private compile option ################
#add compile option for this component that won't affect other modules
# list(APPEND ADD_PRIVATE_DEFINITIONS -Dxxx)
#######################################################

generate_library()
