/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/


#include <stdio.h>
#include <iot_link_config.h>
#include <link_version.h>
//RTOS KERNEL
#include <osal.h> 
#include <link_log.h> 


#ifdef CONFIG_MACOS_ENABLE
    #include <sys/select.h>
#endif


#define  CN_LINK_VERSION_MAJOR      2
#define  CN_LINK_VERSION_MINOR      2
#define  CN_LINK_VERSION_FEATURE    1


static char s_link_mainversion[64];
const char *linkmain_version()
{
    (void) snprintf(s_link_mainversion,64,"V%d.%d.%d AT %s ON %s",CN_LINK_VERSION_MAJOR,\
            CN_LINK_VERSION_MINOR,CN_LINK_VERSION_FEATURE,__TIME__,__DATE__);
    return s_link_mainversion;
}


static int s_link_start = 0;
int link_main(void *args)
{
    ///< install the RTOS kernel for the link
    if(s_link_start)
    {
       return -1;
    }
    s_link_start =1;
    
    (void)osal_init();
    LINK_LOG_DEBUG("linkmain:%s \n\r",linkmain_version());

#ifdef CONFIG_STIMER_ENABLE
    #include <stimer.h>
    stimer_init();
#endif

#ifdef CONFIG_SHELL_ENABLE
    #include <shell.h>
    shell_init();
#endif

    /* add loader code here */
#ifdef CONFIG_OTA_ENABLE
    extern int ota_img_init();
    ota_img_init();
#endif

///< install the driver framework
#ifdef CONFIG_DRIVER_ENABLE
    #include <driver.h>
    ///< install the driver framework for the link
    (void)los_driv_init();
#endif


///< install the at framework
#ifdef CONFIG_AT_ENABLE
    #include <at.h>
    (void)at_init();
#endif

#if 0 // 
///< install the cJSON, for the oc mqtt agent need the cJSON
#ifdef CONFIG_CJSON_ENABLE
    #include <cJSON.h>

    cJSON_Hooks  hook;
    hook.free_fn = osal_free;
    hook.malloc_fn = osal_malloc;
    cJSON_InitHooks(&hook);

#endif
#endif

//////////////////////////  TCPIP PROTOCOL /////////////////////////////////////
#ifdef CONFIG_TCIP_AL_ENABLE
    #include <sal.h>
    (void)link_tcpip_init();

#endif

//////////////////////////  DTLS PROTOCOL  /////////////////////////////////////
#ifdef CONFIG_DTLS_AL_ENABLE
    #include <dtls_al.h>
    (void)dtls_al_init();
#endif

//////////////////////////  MQTT PROTOCOL  /////////////////////////////////////
#ifdef CONFIG_MQTT_AL_ENABLE
    #include <mqtt_al.h>
    mqtt_al_init();
#endif


//////////////////////////  COAP PROTOCOL  /////////////////////////////////
#ifdef CONFIG_COAP_AL_ENABLE
    #include <coap_al.h>
    (void)coap_al_init();
#endif

//////////////////////////  LWM2M PROTOCOL  /////////////////////////////////
#ifdef CONFIG_LWM2M_AL_ENABLE
    #include <lwm2m_al.h>
    (void)lwm2m_al_init();
#endif

//////////////////////////  OC MQTT  //////////////////////////////////
#ifdef CONFIG_OCMQTT_ENABLE
    #include <oc_mqtt_al.h>
    (void)oc_mqtt_init();

#endif

////////////////////////////  OC LWM2M /////////////////////////////////////////
#ifdef CONFIG_OCLWM2M_ENABLE
    #include <oc_lwm2m_al.h>
    oc_lwm2m_init();
#endif

////////////////////////////  OC COAP //////////////////////////////////////////
#ifdef CONFIG_OCCOAP_ENABLE
	#include <oc_coap_al.h>
    oc_coap_init();
#endif


#ifdef CONFIG_AUTO_TEST
    #include <test_case.h>
    autotest_start();
#endif


#ifdef CONFIG_LINKDEMO_ENABLE
    extern int standard_app_demo_main(void);
    (void) standard_app_demo_main();
#endif


    while (1)  
    {
        printf("max.su -> go [%s:%d]\r\n", __FUNCTION__, __LINE__); 
        osal_task_sleep(5000);
    }


    return 0;
}


