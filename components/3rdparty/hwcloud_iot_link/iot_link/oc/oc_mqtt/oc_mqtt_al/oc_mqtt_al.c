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

#include <link_log.h>
#include <oc_mqtt_al.h>

static oc_mqtt_t *s_oc_mqtt = NULL;
///////////////////////OC AGENT INSTALL INTERFACE///////////////////////////////
int oc_mqtt_register(const oc_mqtt_t *opt)
{
    int ret =(int)en_oc_mqtt_err_system;

    if(NULL != opt)
    {
        s_oc_mqtt = (oc_mqtt_t *) opt;
        ret =(int)en_oc_mqtt_err_ok;
    }

    return ret;
}

//////////////////////////APPLICATION INTERFACE/////////////////////////////////
int oc_mqtt_config(oc_mqtt_config_t *param)
{
    int ret =(int)en_oc_mqtt_err_system ;
    if((NULL != s_oc_mqtt) &&(NULL != s_oc_mqtt->op.config))
    {
       ret = s_oc_mqtt->op.config(param);
    }

    return ret;
}

int oc_mqtt_deconfig()
{
    int ret =(int)en_oc_mqtt_err_system;

    if((NULL != s_oc_mqtt) \
       &&(NULL != s_oc_mqtt->op.config))
    {
       ret = s_oc_mqtt->op.deconfig();
    }

    return ret;
}

int oc_mqtt_publish(char  *topic,uint8_t *msg,int msg_len,int qos)
{
    int ret =(int)en_oc_mqtt_err_system;

    if((NULL != s_oc_mqtt) &&(NULL != s_oc_mqtt->op.publish))
    {
       ret = s_oc_mqtt->op.publish(topic,msg,msg_len,qos);
    }

    return ret;
}

int oc_mqtt_report(uint8_t *msg, int len, int qos)
{
    int ret =(int)en_oc_mqtt_err_system;

    ret = oc_mqtt_publish(NULL,msg,len,qos);

    return ret;
}

int oc_mqtt_subscribe(char *topic,int qos)
{
    int ret =(int)en_oc_mqtt_err_system;

    if((NULL != s_oc_mqtt) &&(NULL != s_oc_mqtt->op.subscribe))
    {
       ret = s_oc_mqtt->op.subscribe(topic,qos);
    }

    return ret;
}


int oc_mqtt_unsubscribe(char *topic)
{
    int ret =(int)en_oc_mqtt_err_system;

    if((NULL != s_oc_mqtt) &&(NULL != s_oc_mqtt->op.unsubscribe))
    {
       ret = s_oc_mqtt->op.unsubscribe(topic);
    }

    return ret;
}

///////////////////////OC MQTT TINY AGENT INITIALIZE////////////////////////////

#if 0 //
__attribute__ ((weak)) int oc_mqtt_imp_init(void)
{
    LINK_LOG_DEBUG("%s:###please implement oc mqtt by yourself####\n\r",__FUNCTION__);
    return 0;
}
#endif

__attribute__ ((weak)) int oc_mqtt_demo_main(void)
{
    LINK_LOG_WARN("Please implement the oc mqtt v5 demo yourself \n\r");
    return -1;
}


int oc_mqtt_init()
{
    int ret;

    ret = oc_mqtt_imp_init();

    LINK_LOG_DEBUG("IOT_LINK:DO OC MQTT LOAD-IMPLEMENT RET:%d\n\r",ret);


#ifdef CONFIG_OCMQTT_DEMOENABLE
    (void) oc_mqtt_demo_main();
#endif


    return ret;
}


static const char *s_oc_mqtt_err_tab[] =
{
    "success",
    "parameter_err",
    "network_err",
    "version_err",
    "clientid_err",
    "server_err",
    "userpwd_err",
    "clientauth_err",
    "subscribe_err",
    "publish_err",
    "reconfigure_err",
    "nonconfigure_err",
    "mqttconnect_err",
    "bsaddrtimeout_err",
    "sysmemory_err",
    "system_err",
};


#define CN_ERR_TABITEM     (sizeof(s_oc_mqtt_err_tab)/sizeof(const char *))

const char *oc_mqtt_err(en_oc_mqtt_err_code_t code)
{
    const char *ret = NULL;
    if((unsigned int)code < CN_ERR_TABITEM)
    {
        ret = s_oc_mqtt_err_tab[(int)code];
    }
    else
    {
        ret = "UNKNOWN";
    }
    return ret;
}




