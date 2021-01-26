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


#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <link_endian.h>
#include <osal.h>
#include <oc_lwm2m_al.h>
#include <hwqueue.h>


//#define cn_app_server         "iot-bs.cn-north-4.myhuaweicloud.com"
#define cn_app_server         "119.3.251.30"
#define cn_endpoint_id        "lwm2m_001"
#define cn_app_port           "5683"

#define cn_app_connectivity    0
#define cn_app_lightstats      1
#define cn_app_light           2
#define cn_app_ledcmd          3
#define cn_app_cmdreply        4

#pragma pack(1)
typedef struct
{
    int8_t msgid;
    int16_t rsrp;
    int16_t ecl;
    int16_t snr;
    int32_t cellid;
}app_connectivity_t;

typedef struct
{
    int8_t msgid;
    int16_t tog;
}app_toggle_t;

typedef struct
{
    int8_t msgid;
    int16_t intensity;
}app_light_intensity_t;


typedef struct
{
    int8_t msgid;
    uint16_t mid;
    char led[3];
}app_led_cmd_t;

typedef struct
{
    int8_t msgid;
    uint16_t mid;
    int8_t errorcode;
    char curstats[3];
}app_cmdreply_t;

#pragma pack()



//if your command is very fast,please use a queue here--TODO
static queue_t *s_queue_msgrcv = NULL;     ///< this is used to cached the message
static int32_t  s_lwm2m_reconnect = 0;

// use this var to replace s_lwm2m_context
static int32_t  s_is_lwm2m_configed = 0;

typedef struct
{
    int32_t msg_type;
    int32_t msg_len;
    void   *msg_content;
}oc_bs_msg_t;


//use this function to push all the message to the buffer
static int app_msg_deal(void *usr_data,en_oc_lwm2m_msg_t type,void *msg, int len)
{
    int ret = -1;
    int msg_len;

    oc_bs_msg_t *bs_msg;

    msg_len  = len + sizeof(oc_bs_msg_t);
    bs_msg = osal_malloc(msg_len);
    if(NULL != bs_msg)
    {
        bs_msg->msg_type = type;
        bs_msg->msg_len = len;
        bs_msg->msg_content = (char *)bs_msg + sizeof(oc_bs_msg_t);
        (void) memcpy(bs_msg->msg_content,msg,len);

        ret = queue_push(s_queue_msgrcv,bs_msg,100);
        if( 0 != ret)
        {
            osal_free(bs_msg);
        }
    }
    return ret;
}


static int app_cmd_task_entry()
{
    int ret = -1;
    app_led_cmd_t *led_cmd;
    app_cmdreply_t replymsg;
    int8_t msgid;
    oc_bs_msg_t *bs_msg;

    while(1)
    {
        bs_msg = NULL;
        queue_pop(s_queue_msgrcv,(void **)&bs_msg,cn_osal_timeout_forever);
        if(bs_msg != NULL)
        {
            if(bs_msg->msg_type == EN_OC_LWM2M_MSG_SERVERREBS)  ///< do the reboot strap function
            {
                s_lwm2m_reconnect = 1;
            }
            else
            {
                msgid = *(int8_t *)bs_msg->msg_content;
                switch (msgid)
                {
                    case cn_app_ledcmd:
                        led_cmd = bs_msg->msg_content;
                        (void) printf("LEDCMD:msgid:%d mid:%d msg:%s \n\r",led_cmd->msgid,ntohs(led_cmd->mid),led_cmd->led);
                        //add command action--TODO
                        if (led_cmd->led[0] == 'O' && led_cmd->led[1] == 'N')
                        {
                            //if you need response message,do it here--TODO
                            replymsg.msgid = cn_app_cmdreply;
                            replymsg.mid = led_cmd->mid;
                            (void) printf("reply mid is %d. \n\r",ntohs(replymsg.mid));
                            replymsg.errorcode = 0;
                            replymsg.curstats[0] = 'O';
                            replymsg.curstats[1] = 'N';
                            replymsg.curstats[2] = ' ';
                            oc_lwm2m_report((char *)&replymsg,sizeof(replymsg),1000);    ///< report cmd reply message
                        }

                        else if (led_cmd->led[0] == 'O' && led_cmd->led[1] == 'F' && led_cmd->led[2] == 'F')
                        {

                            //if you need response message,do it here--TODO
                            replymsg.msgid = cn_app_cmdreply;
                            replymsg.mid = led_cmd->mid;
                            (void) printf("reply mid is %d. \n\r",ntohs(replymsg.mid));
                            replymsg.errorcode = 0;
                            replymsg.curstats[0] = 'O';
                            replymsg.curstats[1] = 'F';
                            replymsg.curstats[2] = 'F';
                            oc_lwm2m_report((char *)&replymsg,sizeof(replymsg),1000);    ///< report cmd reply message
                        }
                        else
                        {

                        }
                        break;
                    default:
                        break;
                }

            }

            osal_free(bs_msg);
        }

    }

    return ret;
}



static int app_report_task_entry()
{
    int ret = -1;
    int lux = 0;

    oc_config_param_t      oc_param;
    app_light_intensity_t  light;

    (void) memset(&oc_param,0,sizeof(oc_param));

    oc_param.app_server.ep_id = cn_endpoint_id;


    oc_param.boot_server.address = cn_app_server;
    oc_param.boot_server.port = cn_app_port;
    oc_param.boot_server.ep_id = cn_endpoint_id;

    oc_param.boot_mode = en_oc_boot_strap_mode_client_initialize;
    oc_param.rcv_func = app_msg_deal;

    while(1) //--TODO ,you could add your own code here
    {
        if(0 == s_is_lwm2m_configed)
        {
            ret = oc_lwm2m_config(&oc_param);

            if (0 != ret)
            {
                (void) printf("call oc_lwm2m_config error, return %d\r\n", ret);
            }
            else
            {
                s_is_lwm2m_configed = 1;
            }
        }
        else if(s_lwm2m_reconnect)
        {
            s_lwm2m_reconnect = 0;

            oc_lwm2m_deconfig();

            s_is_lwm2m_configed = 0;

            ret = oc_lwm2m_config(&oc_param);

            if (0 != ret)
            {
                (void) printf("call oc_lwm2m_config error, return %d\r\n", ret);
            }
            else
            {
                s_is_lwm2m_configed = 1;
            }
        }
        else
        {
            lux++;
            lux= lux%10000;

            light.msgid = cn_app_light;
            light.intensity = htons(lux);
            oc_lwm2m_report((char *)&light,sizeof(light),1000); ///< report the light message
        }

        osal_task_sleep(10*1000);

    }

    return ret;
}




int oc_lwm2m_demo_main()
{
    (void) printf("welcome to the application:lwm2m_bs:%s:%s\r\n",__DATE__,__TIME__);

    s_queue_msgrcv = queue_create("ota_nodtls_rcvmsg",10,1);

    osal_task_create("app_report",app_report_task_entry,NULL,0x1000,NULL,2);

    osal_task_create("app_command",app_cmd_task_entry,NULL,0x1000,NULL,3);

    return 0;
}



