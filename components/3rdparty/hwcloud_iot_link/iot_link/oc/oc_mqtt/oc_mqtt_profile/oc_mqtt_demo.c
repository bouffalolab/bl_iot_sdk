/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
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
#include <stdio.h>
#include <string.h>
#include <queue.h>

#include <osal.h>
#include <oc_mqtt_al.h>
#include <oc_mqtt_assistant.h>

///< ANYWAY, YOU COULD CONFIG IT TO THE ONE MODE,ALL THE INFORMATION IS JUST FOR THE TEST
#if CONFIG_OC_MQTT_DEMO_BS

///< the device bootstrap center

#define CN_SERVER_IPV4         "119.3.251.30"
#define CN_SERVER_PORT         "8883"
#define CN_EP_NODEID           "mqtt_sdk03"
#define CN_EP_PASSWD           "f62fcf47d62c4ed18913"
#define CN_DEMO_MODE            en_oc_mqtt_mode_bs_static_nodeid_hmacsha256_notimecheck_json

#else

///< the iot device access center
//#define CN_SERVER_IPV4         "119.3.248.253"
//#define CN_SERVER_PORT         "8883"
//#define CN_EP_NODEID           "mqtt_sdk03"
//#define CN_EP_PASSWD           "f62fcf47d62c4ed18913"

///< the iot develop center
#define CN_SERVER_IPV4         "49.4.93.24"
#define CN_SERVER_PORT         "8883"
#define CN_EP_NODEID           "mqtt_sdk01"
#define CN_EP_PASSWD           "c18f10422c93548e6fef"


#define CN_DEMO_MODE            en_oc_mqtt_mode_nobs_static_nodeid_hmacsha256_notimecheck_json

#endif

#define DEFAULT_LIFETIME            60                 ///< the platform need more

//if your command is very fast,please use a queue here--TODO
static queue_t *s_queue_rcvmsg = NULL;   ///< this is used to cached the message

typedef struct
{
    int        qos;
    int        dup;
    int        retain;
    int        msg_len;
    char      *topic;
    uint8_t   *msg;
    uint8_t   *buf;
}demo_msg_t;

//use this function to push all the message to the buffer
static int app_msg_deal(void *arg,mqtt_al_msgrcv_t *msg)
{
    int ret = -1;
    uint8_t  *buf;
    uint32_t  buflen;
    demo_msg_t *demo_msg;

    buflen =msg->msg.len + msg->topic.len + sizeof(demo_msg_t) + 1 +1;
    buf = osal_malloc(buflen);
    if(NULL != buf)
    {
        ///< copy the message and push it to the queue
        demo_msg = (demo_msg_t *)buf;
        demo_msg->buf = buf + sizeof(demo_msg_t);
        demo_msg->dup = msg->dup;
        demo_msg->qos = msg->qos;
        demo_msg->retain = msg->retain;

        demo_msg->topic = (char *) demo_msg->buf;
        buf = (uint8_t *)demo_msg->topic;
        (void) memcpy(buf,msg->topic.data,msg->topic.len);
        buf[msg->topic.len] = '\0';

        demo_msg->msg = demo_msg->buf + msg->topic.len +1;
        demo_msg->msg_len = msg->msg.len;
        buf = demo_msg->msg;
        (void) memcpy(buf,msg->msg.data,msg->msg.len);
        buf[msg->msg.len] = '\0';

        (void) printf("RCVMSG:qos:%d dup:%d retain:%d topic:%s msg:len:%d payload:%s\n\r",\
                demo_msg->qos,demo_msg->dup,demo_msg->retain,\
                demo_msg->topic,demo_msg->msg_len,demo_msg->msg);

        ret = queue_push(s_queue_rcvmsg,demo_msg,10);
        if(ret != 0)
        {
            osal_free(demo_msg);
        }
    }

    return ret;
}


static int  oc_cmd_normal(demo_msg_t *demo_msg)
{

    int ret = 0;
    char   *buf = NULL;  ///< used for the mqtt

    cJSON               *mid_json;
    cJSON               *cmd_json;
    cJSON               *response_msg;
    tag_oc_mqtt_response response;
    tag_key_value_list   list;
    int mid_int = 0;
    int err_int = 0;
    //////////////HANDLE YOUR MESSAGE HERE WITH YOUR DEVICE PROFILE///////////
    cmd_json = cJSON_Parse((const char *)demo_msg->msg);
    mid_json = cJSON_GetObjectItem(cmd_json,"mid");
    if(NULL != mid_json)
    {
        mid_int = mid_json->valueint;
    }
    cJSON_Delete(cmd_json);
    //////////////DO THE RESPONSE FOR THE COMMAND/////////////////////////////
    list.item.name = "body_para";
    list.item.buf = "body_para";
    list.item.type = en_key_value_type_string;
    list.next = NULL;

    response.hasmore = 0;
    response.errcode = err_int;
    response.mid = mid_int;
    response.bodylst = &list;

    response_msg = oc_mqtt_json_fmt_response(&response);
    if(NULL != response_msg)
    {
        buf = cJSON_PrintUnformatted(response_msg);
        if(NULL != buf)
        {
            ret = oc_mqtt_report((uint8_t *)buf,strlen(buf),en_mqtt_al_qos_1);
            (void) printf("%s:RESPONSE:mid:%d err_int:%d retcode:%d \r\n",__FUNCTION__,\
                    mid_int,err_int,ret);

            osal_free(buf);
        }
        cJSON_Delete(response_msg);
    }

    return 0;
}


static int  oc_report_normal(void)
{
    int ret = 0;
    cJSON *root = NULL;
    char  *buf = NULL;
    tag_oc_mqtt_report  report;
    tag_key_value_list  lst;
    static int value = 1;
    static int times = 1;


    value = (value + 7 )%100;

    lst.item.name = "radioValue";
    lst.item.buf = (char *)&value;
    lst.item.len = sizeof(value);
    lst.item.type = en_key_value_type_int;
    lst.next = NULL;

    report.hasmore = en_oc_mqtt_has_more_no;
    report.paralst= &lst;
    report.serviceid = "DeviceStatus";
    report.eventtime = NULL;

    root = oc_mqtt_json_fmt_report(&report);
    if(NULL != root)
    {
        buf = cJSON_PrintUnformatted(root);
        if(NULL != buf)
        {
            ret = oc_mqtt_report((uint8_t *)buf,strlen(buf),en_mqtt_al_qos_1);
            (void) printf("%s:REPORT:times:%d:value:%d retcode:%d \r\n",__FUNCTION__,times++,value,ret);
            osal_free(buf);
        }

        cJSON_Delete(root);
    }

    return 0;
}


static int task_rcvmsg_entry( void *args)
{

    demo_msg_t *demo_msg;

    while(1)
    {
        demo_msg = NULL;
        queue_pop(s_queue_rcvmsg,(void **)&demo_msg,cn_osal_timeout_forever);

        if(NULL != demo_msg)
        {
            oc_cmd_normal(demo_msg);  ///< this is the old model
            osal_free(demo_msg);
        }
    }

    return 0;
}

static int task_reportmsg_entry(void *args)
{
    int ret;
    oc_mqtt_config_t config;

    (void) memset( &config, 0, sizeof(config));

    config.boot_mode = CN_DEMO_MODE;
    config.msg_deal = app_msg_deal;
    config.msg_deal_arg = NULL;
    config.lifetime = DEFAULT_LIFETIME;
    config.server_addr = CN_SERVER_IPV4;
    config.server_port = CN_SERVER_PORT;
    config.id = CN_EP_NODEID;
    config.pwd= CN_EP_PASSWD;
    config.security.type = EN_DTLS_AL_SECURITY_TYPE_CERT;


    ret = oc_mqtt_config(&config);
    if((ret != en_oc_mqtt_err_ok))
    {
        (void) printf("config:err :code:%d\r\n",ret);
        return -1;
    }

    while(1)  //do the loop here
    {
        oc_report_normal();
        osal_task_sleep(1000);
    }
    return 0;
}

int oc_mqtt_demo_main()
{
    printf("DO THE OC MQTT V1 DEMOS\n\r");

    s_queue_rcvmsg = queue_create("queue_rcvmsg",2,1);

    osal_task_create("demo_reportmsg",task_reportmsg_entry,NULL,0x800,NULL,8);

    osal_task_create("demo_rcvmsg",task_rcvmsg_entry,NULL,0x800,NULL,8);

    return 0;
}
