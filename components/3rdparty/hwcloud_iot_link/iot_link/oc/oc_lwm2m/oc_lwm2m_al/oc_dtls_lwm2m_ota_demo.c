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
#include <ota_flag.h>
#include <pcp.h>
#include <hwqueue.h>

#define cn_endpoint_id        "sota_test_dtls"
#define cn_app_server         "49.4.85.232"
#define cn_app_port           "5684"
const unsigned char  s_app_psk[]={0x01,0x02,0x03,0x04,0x05,0x06};

#define cn_app_connectivity    0
#define cn_app_lightstats      1
#define cn_app_light           2
#define cn_app_ledcmd          3
#define cn_app_cmdreply        4



#pragma pack(1)

typedef struct
{
    int8_t msgid;
    int16_t intensity;
}app_light_intensity_t;

#pragma pack()


#include <ota_flag.h>

static char s_ota_flag[sizeof(ota_flag_t)];

static int ota_flag_read(ota_flag_t *flag)
{
    (void) memcpy(flag,s_ota_flag,sizeof(ota_flag_t));

    return 0;
}

static int ota_flag_write(ota_flag_t *flag)
{
    (void) memcpy(s_ota_flag,flag,sizeof(ota_flag_t));
    return 0;
}


static int ota_bin_write(int offset ,void *msg,int len)
{

    (void) printf("BIN W:%08d %08d\n\r",offset,len);
    return 0;
}

static int ota_bin_read(int offset ,void *buf,int len)
{

    (void) printf("BIN R:%08d %08d\n\r",offset,len);
    return 0;
}

static ota_storage_t  s_ota_storage_device =
{
      .name = "ota_storage",
      {
         .flag_read = ota_flag_read,
         .flag_write = ota_flag_write,
         .bin_read = ota_bin_read,
         .bin_write =ota_bin_write,
      }
};

static queue_t *s_queue_msgrcv = NULL;   ///< this is used to cached the message


static int ota_msg_send(void *msg,int len)
{
    int ret;
    ret = oc_lwm2m_report((char *)msg,len,1000);
    return ret;
}

//use this function to push all the message to the buffer
static int app_msg_deal(void *usr_data,en_oc_lwm2m_msg_t type,void *msg, int len)
{
    int ret = -1;

    uint8_t  *buf;
    uint32_t  buflen;
    buflen = len +sizeof(buflen);

    buf = osal_malloc(buflen);
    if(NULL != buf)
    {
        (void) memcpy(buf,&buflen,sizeof(buflen));
        (void) memcpy(buf + sizeof(buflen),msg,len);

        ret = queue_push(s_queue_msgrcv,buf,10);

        if(ret != 0)
        {
            osal_free(buf);
        }
    }

    return ret;
}


static int s_report_switch = 1;

static int app_cmd_task_entry()
{
    int ret = -1;

    uint8_t *msg = NULL;
    uint8_t *buf = NULL;
    uint32_t msglen = 0;

    while(1)
    {
        queue_pop(s_queue_msgrcv,(void **)&buf,cn_osal_timeout_forever);
        if(NULL != buf)
        {
            msg = buf + sizeof(msglen);
            (void) memcpy(&msglen,buf,sizeof(msglen));
            msglen -= sizeof(msglen);

            if((0xFF == msg[0]) && (0xFE == msg[1]) && (0x01 == msg[2]))
            {
                s_report_switch = 0;
                pcp_msg_push(msg,msglen);  ///< push the message to the ota queue
            }
            else
            {
                (void) printf("RCVMSG:%d \n\r",(int)msglen);
                osal_free(buf);
            }

        }
    }
    return ret;
}

static int app_report_task_entry()
{
    int ret = -1;

    oc_config_param_t      oc_param;
    app_light_intensity_t  light;
    void                  *context;
    int                    lux = 0;

    (void) memset(&oc_param,0,sizeof(oc_param));

    oc_param.app_server.address = cn_app_server;
    oc_param.app_server.port = cn_app_port;
    oc_param.app_server.ep_id = cn_endpoint_id;
    oc_param.app_server.psk = (char *)s_app_psk;
    oc_param.app_server.psk_len = sizeof(s_app_psk);
    oc_param.app_server.psk_id = cn_endpoint_id;

    oc_param.boot_mode = en_oc_boot_strap_mode_factory;
    oc_param.rcv_func = app_msg_deal;

    ret = oc_lwm2m_config( &oc_param);
    if (0 != ret)
    {
        return ret;
    }

    while(1) //--TODO ,you could add your own code here
    {
        if(s_report_switch)
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

    (void) printf("welcome to the application:OTA_DTLS:%s:%s\r\n",__DATE__,__TIME__);

    ota_storage_install(&s_ota_storage_device);

    s_queue_msgrcv = queue_create("ota_nodtls_rcvmsg",10,1);

    ota_pcp_init(ota_msg_send);

    osal_task_create("app_report",app_report_task_entry,NULL,0x1000,NULL,2);
    osal_task_create("app_command",app_cmd_task_entry,NULL,0x1000,NULL,3);

    return 0;
}





