#/*----------------------------------------------------------------------------
# * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
# * All rights reserved.
# * Redistribution and use in source and binary forms, with or without modification,
# * are permitted provided that the following conditions are met:
# * 1. Redistributions of source code must retain the above copyright notice, this list of
# * conditions and the following disclaimer.
# * 2. Redistributions in binary form must reproduce the above copyright notice, this list
# * of conditions and the following disclaimer in the documentation and/or other materials
# * provided with the distribution.
# * 3. Neither the name of the copyright holder nor the names of its contributors may be used
# * to endorse or promote products derived from this software without specific prior written
# * permission.
# * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# *---------------------------------------------------------------------------*/
#/*----------------------------------------------------------------------------
# * Notice of Export Control Law
# * ===============================================
# * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
# * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
# * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
# * applicable export control laws and regulations.
# *---------------------------------------------------------------------------*/


################################################################################
# this is used to take the demo place
################################################################################
vpath %.c $(iot_link_root)/demos
vpath %.c $(iot_link_root)/demos/oc_mqtt_demo
vpath %.c $(iot_link_root)/demos/oc_agriculture_template


ifeq ($(CONFIG_LINKDEMO_ENABLE), y)
    
    C_SOURCES += $(iot_link_root)/demos/app_demo_main.c

	ifeq ($(CONFIG_USERDEMO_MQTT_ENABLE), y)	
		user_demo_src  = ${wildcard $(iot_link_root)/demos/oc_mqtt_demo/oc_mqtt_water_meter.c}
	endif
	ifeq ($(CONFIG_USERDEMO_LWM2M_ENABLE), y)	
		user_demo_src  = ${wildcard $(iot_link_root)/demos/oc_agriculture_template/oc_agriculture_template_lwm2m.c}
	endif
	ifeq ($(CONFIG_USERDEMO_COAP_ENABLE), y)	
		user_demo_src  = ${wildcard $(iot_link_root)/demos/oc_agriculture_template/oc_agriculture_template_coap.c}
	endif


	C_SOURCES += $(user_demo_src)

endif



