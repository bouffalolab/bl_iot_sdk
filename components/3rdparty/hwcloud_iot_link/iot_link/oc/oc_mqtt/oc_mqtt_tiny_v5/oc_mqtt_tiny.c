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
/**
 *  1, only support CRT tls mode
 *  2, the data encode only support the json mode
 *  3, the pwd only support the no check time mode
 *
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <link_misc.h>
#include <time.h>

#include <hwqueue.h>
//#include <osal.h>
#include <mqtt_al.h>
#include <oc_mqtt_al.h>
#include <sal.h>

#include <cJSON.h>           //json mode
#include "hmac.h"            //used to generate the user pwd
#include <stdio.h> // max.su

////CRT FOR THE OC
static const char s_oc_mqtt_ca_crt[] =
" -----BEGIN CERTIFICATE-----\r\n"
"MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh\r\n"
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\r\n"
"QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT\r\n"
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\r\n"
"b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG\r\n"
"9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB\r\n"
"CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97\r\n"
"nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt\r\n"
"43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P\r\n"
"T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4\r\n"
"gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO\r\n"
"BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR\r\n"
"TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw\r\n"
"DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr\r\n"
"hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg\r\n"
"06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF\r\n"
"PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls\r\n"
"YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk\r\n"
"CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=\r\n"
"-----END CERTIFICATE-----\r\n";


///< devices normal data report and receive topic format
#define CN_CLIENT_ID_FMT                    "%s_0_0_%s"

#define CN_OC_BS_REPORT_TOPIC_FMT           "/huawei/v1/devices/%s/iodpsData"
#define CN_OC_BS_CMD_TOPIC_FMT              "/huawei/v1/devices/%s/iodpsCommand"
#define CN_OC_HUB_SUBTOPIC_DEFAULT_FMT      "$oc/devices/%s/sys/commands/#"
#define CN_OC_HUB_PUBTOPIC_DEFAULT_FMT      "$oc/devices/%s/sys/properties/report"

/*The unit is millisecond*/
#define CN_CON_BACKOFF_TIME     (1000)   ///< UNIT:ms
#define CN_CON_BACKOFF_MAXTIMES  20      ///< WHEN WAIT OR GET ADDRESS ,WE COULD TRY MAX TIMES
#define CN_HMAC_LEN              32
#define CN_STRING_MAXLEN         127

#define CN_OC_MQTT_TIMEOUT             (10*1000)
#define CN_OC_MQTT_LIFETIMEDEFAULT     (120)
#define CN_OC_MQTT_LIFELEAST           (30)
#define CN_OC_MQTT_LIFEMAX             (1200)

const char *s_new_topic_fmt[]=
{
    "$oc/devices/%s/sys/messages/down",
    "$oc/devices/%s/sys/properties/set/#",
    "$oc/devices/%s/sys/properties/get/#",
    "$oc/devices/%s/sys/shadow/get/response/#",
    "$oc/devices/%s/sys/events/down",
};
#define CN_NEW_TOPIC_NUM     (sizeof(s_new_topic_fmt)/sizeof(const char *))


typedef struct
{
    char *hubserver_addr;     ///< we get from the bs server
    char *hubserver_port;     ///< we get from the bs server
}oc_bs_mqtt_cb_t;             ///< when we used


typedef struct
{
    ///< these parameter has been generated when configured
    char   *mqtt_clientid;
    char   *mqtt_user;
    char   *mqtt_passwd;
    char   *server_addr;
    char   *server_port;
    char   *default_pub_topic;
    char   *default_sub_topic;
    fn_mqtt_al_msg_dealer default_msg_deal;
    ///< these parameter is dynamic  and will changed in the connection process
    void   *mqtt_handle;
}oc_mqtt_para_t;


typedef enum
{
    en_daemon_status_idle = 0,
    en_daemon_status_bs_getaddr,
    en_daemon_status_dmp_connecting,
    en_daemon_status_hub_keep,
}en_daemon_status_t;

typedef struct
{
    void  *nxt;
    char  *topic;
    int    qos;
}tiny_topic_sub_t;


typedef struct
{
    int                     daemon_exit;
    char                   *config_mem;   ///< used to storage the configuration information
    oc_mqtt_config_t        config;
    oc_mqtt_para_t          mqtt_para;
    union{

        uint32_t value;
        struct
        {
            uint32_t bit_bs_enable:1;
            uint32_t bit_daemon_status:3;
            uint32_t bit_get_hubaddr:1;
            uint32_t bit_do_bootstrap:1;
            uint32_t bit_do_reportdisconnect:1;
        }bits;
    }flag;
    oc_bs_mqtt_cb_t     bs_cb;
    void               *task_daemon;                ///< oc mqtt lite daemon task
    hwqueue_t            *task_daemon_cmd_queue;      ///< oc mqtt lite daemon task command queue
    char                salt_time[16];              ///< salt time for the connect
    char               *hub_sub_topic[CN_NEW_TOPIC_NUM];
    tiny_topic_sub_t   *subscribe_lst;
}oc_mqtt_tiny_cb_t;   ///< i think we may only got one mqtt
static oc_mqtt_tiny_cb_t *s_oc_mqtt_tiny_cb;

typedef enum
{
    en_oc_mqtt_daemon_cmd_connect = 0,
    en_oc_mqtt_daemon_cmd_send,           ///< when api need send message, then it post this command
    en_oc_mqtt_daemon_cmd_publish,        ///< when api need publish message, then it post this command
    en_oc_mqtt_daemon_cmd_subscribe,      ///< when api need subscribe a topic, then it post this command
    en_oc_mqtt_daemon_cmd_unsubscribe,    ///< when api need un-subscribe a topic,then it post this command
    en_oc_mqtt_daemon_cmd_disconnect,     ///< when api need to stop the connect, then it post this command
    en_oc_mqtt_daemon_cmd_bsgetaddr,      ///< the bs callback post this command to the daemon when get the address
    en_oc_mqtt_daemon_cmd_rebootstrap,    ///< the hub callback post this command to the daemon when get the rebootstrap command
}en_oc_mqtt_daemon_cmd;

typedef struct
{
    en_oc_mqtt_daemon_cmd   cmd;       ///< this is the command
    void                   *arg;       ///< this is used for the argument
    osal_semp_t             signal;    ///< when done the command, please light this signal
    int                     retcode;   ///< this is the operation code for the command
}oc_mqtt_daemon_cmd_t;                 ///< use this to do the command for the api


///< here we implement the hub and bootstrap server command dealer
///< the bs not debug yet
static void hub_msg_default_deal(void *arg,mqtt_al_msgrcv_t  *msg)
{
    //for we must add the '/0' to the end to make sure the json parse correct
    if ((msg != NULL) && ( msg->msg.data != NULL) &&(msg->msg.len > 0 ) \
        &&(NULL != s_oc_mqtt_tiny_cb->config.msg_deal))
    {
        s_oc_mqtt_tiny_cb->config.msg_deal(s_oc_mqtt_tiny_cb->config.msg_deal_arg,msg);

        return;
    }
    return;
}



///< deal the bootstrap server messages
static void bs_msg_default_deal(void *arg,mqtt_al_msgrcv_t *msg)
{
   cJSON  *root = NULL;
   cJSON  *addr_item = NULL;
   char   *port = NULL;
   char   *server = NULL;

   char   *json_buf;

   LINK_LOG_DEBUG("bs topic:%s qos:%d\n\r",msg->topic.data,(int)msg->qos);

   json_buf = osal_malloc(msg->msg.len + 1);
   if(NULL == json_buf)
   {
       return;
   }

   (void) memcpy(json_buf,msg->msg.data,msg->msg.len);
   json_buf[msg->msg.len] = '\0';

   LINK_LOG_DEBUG("msg:%s\n\r",json_buf);
   root = cJSON_Parse(json_buf);
   if(NULL != root)
   {
       addr_item = cJSON_GetObjectItem(root,"address");
       if(NULL != addr_item)
       {
           LINK_LOG_DEBUG("address:%s\n\r", addr_item->valuestring);
           port = strrchr(addr_item->valuestring, ':');
           if(NULL != port)
           {
               server = addr_item->valuestring;
               *port = '\0';
               port++;
               osal_free(s_oc_mqtt_tiny_cb->bs_cb.hubserver_addr);
               osal_free(s_oc_mqtt_tiny_cb->bs_cb.hubserver_port);

               s_oc_mqtt_tiny_cb->bs_cb.hubserver_addr = osal_strdup(server);
               s_oc_mqtt_tiny_cb->bs_cb.hubserver_port = osal_strdup(port);

               if((NULL != s_oc_mqtt_tiny_cb->bs_cb.hubserver_addr) && \
                       (NULL != s_oc_mqtt_tiny_cb->bs_cb.hubserver_port))
               {
                   s_oc_mqtt_tiny_cb->flag.bits.bit_get_hubaddr =1;
               }

           }
       }
       cJSON_Delete(root);
   }
   osal_free(json_buf);

   return;
}

static char *topic_fmt(const char *fmt, const char *id)
{
    char *ret = NULL;
    int len =  0;

    len = strlen(fmt) + strlen(id) + 1;

    ret = osal_malloc(len);
    if(NULL != ret)
    {
        (void) snprintf(ret,len,fmt,id);
    }

    return ret;
}

static char *clientid_fmt(const char *fmt, const char *id, const char *salt_time)
{
    char *ret = NULL;
    int len =  0;

    len = strlen(fmt) + strlen(id) + strlen(salt_time) + 1;

    ret = osal_malloc(len);
    if(NULL != ret)
    {
        (void) snprintf(ret,len,fmt,id,salt_time);
    }

    return ret;
}

///< return the command code for the operation
static int daemon_cmd_post(en_oc_mqtt_daemon_cmd cmd, void *arg)
{
    int ret = (int)en_oc_mqtt_err_system;
    oc_mqtt_daemon_cmd_t *daemon_cmd;

    daemon_cmd = osal_malloc(sizeof(oc_mqtt_daemon_cmd_t));
    if(NULL != daemon_cmd)
    {
        daemon_cmd->cmd = cmd;
        daemon_cmd->arg = arg;
        daemon_cmd->retcode = ret;
        if(true == osal_semp_create(&daemon_cmd->signal,1,0))
        {
            if(0 == queue_push(s_oc_mqtt_tiny_cb->task_daemon_cmd_queue,daemon_cmd,10))
            {
                (void)osal_semp_pend(daemon_cmd->signal,cn_osal_timeout_forever);
                ret = daemon_cmd->retcode;
            }
            (void) osal_semp_del(daemon_cmd->signal);
        }
        osal_free(daemon_cmd);
    }

    return ret;
}


///< release the config parameters
static int config_parameter_release(oc_mqtt_tiny_cb_t *cb)
{
    tiny_topic_sub_t  *sub_topic;
    tiny_topic_sub_t  *sub_topic_nxt;

    if( NULL != cb->config_mem )
    {
        osal_free(cb->config_mem);
        cb->config_mem = NULL;
    }

    if( cb->bs_cb.hubserver_addr != NULL )
    {
        osal_free(cb->bs_cb.hubserver_addr);
    }
    if( cb->bs_cb.hubserver_port != NULL )
    {
        osal_free(cb->bs_cb.hubserver_port);
    }

    unsigned int i = 0;
    for(i = 0;i < CN_NEW_TOPIC_NUM;i++)
    {
        if(NULL != cb->hub_sub_topic[i])
        {
            osal_free(cb->hub_sub_topic[i]);
        }
    }
    (void) memset((void *)&cb->hub_sub_topic[0],0,sizeof(cb->hub_sub_topic));

    (void) memset(&cb->config,0,sizeof(oc_mqtt_config_t));

    (void) memset(&cb->bs_cb,0,sizeof(oc_bs_mqtt_cb_t));

    cb->flag.bits.bit_daemon_status = en_daemon_status_idle;

    sub_topic = cb->subscribe_lst;
    cb->subscribe_lst = NULL;

    while( NULL != sub_topic)
    {
        sub_topic_nxt = sub_topic->nxt;
        osal_free ( sub_topic );

        sub_topic = sub_topic_nxt;
    }

    return (int)en_oc_mqtt_err_ok;
}
///< check the config parameters
static int config_parameter_clone(oc_mqtt_tiny_cb_t *cb,oc_mqtt_config_t *config)
{
    int ret = (int)en_oc_mqtt_err_parafmt;
    int mem_len = 0;
    char *mem_buf = NULL;

    if(config->security.type == EN_DTLS_AL_SECURITY_TYPE_CERT)
    {
        mem_len += config->security.u.cert.server_ca_len + config->security.u.cert.client_ca_len +\
                   config->security.u.cert.client_pk_len + config->security.u.cert.client_pk_pwd_len;
        if(NULL != config->security.u.cert.server_name)
        {
            mem_len += strlen(config->security.u.cert.server_name) + 1;
        }
    }
    else if(config->security.type == EN_DTLS_AL_SECURITY_TYPE_PSK)
    {
        mem_len += config->security.u.psk.psk_id_len + config->security.u.psk.psk_key_len;
    }

    mem_len += strlen(config->id) +1;
    if( NULL != config->pwd )                              ///PWD could be NULL
    {
        mem_len += strlen(config->pwd) + 1;
    }
    mem_len += strlen(config->server_addr) + 1;
    mem_len += strlen(config->server_port) + 1;
    ////< now we
    mem_buf = osal_malloc(mem_len);
    if( NULL == mem_buf )
    {
        return ret;
    }

    /// now we copy the parameter
    (void) memset( &cb->config, 0 ,sizeof(cb->config) );

    if( config->boot_mode == en_oc_mqtt_mode_bs_static_nodeid_hmacsha256_notimecheck_json )
    {
        cb->flag.bits.bit_bs_enable = 1;
    }
    else
    {
        cb->flag.bits.bit_bs_enable = 0;
    }
    cb->config.boot_mode  = config->boot_mode;
    cb->config.lifetime = config->lifetime;
    cb->config.msg_deal = config->msg_deal;
    cb->config.msg_deal_arg = config->msg_deal_arg;
    cb->config.log_dealer  = config->log_dealer;

    cb->config_mem = mem_buf; ///< this is the membuf

    cb->config.id = mem_buf;
    (void) strncpy( mem_buf,config->id,strlen(config->id)+1 );
    mem_buf += strlen(config->id) + 1;

    if ( NULL != config->pwd )
    {
        cb->config.pwd = mem_buf;
        (void) strncpy( mem_buf, config->pwd ,strlen(config->pwd)+1);
        mem_buf += strlen( config->pwd ) + 1;
    }
    else
    {
        cb->config.pwd = NULL;
    }

    cb->config.server_addr = mem_buf;
    (void) strncpy( mem_buf,config->server_addr,strlen(config->server_addr)+1 );
    mem_buf += strlen(config->server_addr) + 1;

    cb->config.server_port = mem_buf;
    (void) strncpy( mem_buf,config->server_port,strlen(config->server_port) + 1 );
    mem_buf += strlen(config->server_port) + 1;

    cb->config.security.type = config->security.type;
    if(config->security.type == EN_DTLS_AL_SECURITY_TYPE_CERT)
    {
        if ( 0 != config->security.u.cert.server_ca_len)
        {
            cb->config.security.u.cert.server_ca_len = config->security.u.cert.server_ca_len;
            cb->config.security.u.cert.server_ca = (uint8_t *)mem_buf;
            (void) memcpy( mem_buf, config->security.u.cert.server_ca, config->security.u.cert.server_ca_len );
            mem_buf += config->security.u.cert.server_ca_len;
        }
        else
        {
            cb->config.security.u.cert.server_ca  =  (uint8_t *) s_oc_mqtt_ca_crt;
            cb->config.security.u.cert.server_ca_len = sizeof( s_oc_mqtt_ca_crt );
        }

        if ( 0 != config->security.u.cert.client_ca_len)
        {
            cb->config.security.u.cert.client_ca_len =  config->security.u.cert.client_ca_len;
            cb->config.security.u.cert.client_ca = (uint8_t *)mem_buf;
            (void) memcpy( mem_buf, config->security.u.cert.client_ca, config->security.u.cert.client_ca_len );
            mem_buf += config->security.u.cert.client_ca_len;
        }

        if ( 0 != config->security.u.cert.client_pk_len)
        {
            cb->config.security.u.cert.client_pk_len =  config->security.u.cert.client_pk_len;
            cb->config.security.u.cert.client_pk = (uint8_t *)mem_buf;
            (void) memcpy( mem_buf, config->security.u.cert.client_pk, config->security.u.cert.client_pk_len );
            mem_buf += config->security.u.cert.client_pk_len;
        }

        if ( 0 != config->security.u.cert.client_pk_pwd_len)
        {
            cb->config.security.u.cert.client_pk_pwd_len = config->security.u.cert.client_pk_pwd_len ;
            cb->config.security.u.cert.client_pk_pwd = (uint8_t *)mem_buf;
            (void) memcpy( mem_buf, config->security.u.cert.client_pk_pwd, config->security.u.cert.client_pk_pwd_len );
        }
    }

    unsigned int i = 0;
    for(i = 0;i < CN_NEW_TOPIC_NUM;i++)
    {
        cb->hub_sub_topic[i] = topic_fmt(s_new_topic_fmt[i],(const char *)cb->config.id);
        if(NULL == cb->hub_sub_topic[i])
        {
            (void)config_parameter_release(cb);
            ret = (int)en_oc_mqtt_err_sysmem;
            return ret;
        }
    }


    ret = (int)en_oc_mqtt_err_ok;
    return ret;
}


///< generate the client_id user pwd for the mqtt need
static int oc_mqtt_para_release(oc_mqtt_tiny_cb_t *cb)
{
    (void)mqtt_al_disconnect(cb->mqtt_para.mqtt_handle);
    osal_free(cb->mqtt_para.mqtt_clientid);
    osal_free(cb->mqtt_para.mqtt_user);
    osal_free(cb->mqtt_para.mqtt_passwd);
    osal_free(cb->mqtt_para.default_pub_topic);
    osal_free(cb->mqtt_para.default_sub_topic);

    (void) memset(&cb->mqtt_para,0,sizeof(oc_mqtt_para_t));

    return 0;
}

static int oc_mqtt_para_gernerate(oc_mqtt_tiny_cb_t *cb)
{
    int ret = (int)en_oc_mqtt_err_ok;;
    uint8_t hmac[CN_HMAC_LEN] = {0};

    struct tm *date;
    time_t time_now;

    time_now = osal_sys_time()/1000;
    date = gmtime(&time_now);
    if(NULL == date)
    {
        return ret;
    }

    (void) snprintf(cb->salt_time,11,"%04d%02d%02d%02d",date->tm_year+1900,\
            date->tm_mon,date->tm_mday,date->tm_hour);

    (void) oc_mqtt_para_release(cb);         ///< try to free all the resource we have built

    cb->mqtt_para.mqtt_clientid = clientid_fmt(CN_CLIENT_ID_FMT,(const char *)cb->config.id,(const char *)cb->salt_time);
    if(NULL == cb->mqtt_para.mqtt_clientid)
    {
        goto EXIT_MEM;
    }

    cb->mqtt_para.mqtt_user = osal_strdup(cb->config.id);
    if(NULL == cb->mqtt_para.mqtt_user)
    {
        goto EXIT_MEM;
    }

    if(NULL != cb->config.pwd)
    {
        (void) hmac_generate_passwd(cb->config.pwd,strlen(cb->config.pwd),\
                cb->salt_time,strlen(cb->salt_time),hmac,sizeof(hmac));
        cb->mqtt_para.mqtt_passwd = osal_malloc(CN_HMAC_LEN*2+1);
        if(NULL != cb->mqtt_para.mqtt_passwd)
        {
            (void)byte2hexstr(hmac,CN_HMAC_LEN,cb->mqtt_para.mqtt_passwd);
        }
        else
        {
            goto EXIT_MEM;
        }
    }
    else
    {
        cb->mqtt_para.mqtt_passwd = NULL;
    }


    if(cb->flag.bits.bit_daemon_status == (int)en_daemon_status_bs_getaddr)
    {
        cb->mqtt_para.default_pub_topic = topic_fmt(CN_OC_BS_REPORT_TOPIC_FMT,(const char *)cb->config.id);

        cb->mqtt_para.default_sub_topic = topic_fmt(CN_OC_BS_CMD_TOPIC_FMT,(const char *)cb->config.id);

        cb->mqtt_para.default_msg_deal = bs_msg_default_deal;

        if((NULL == cb->mqtt_para.default_pub_topic) || \
                (NULL == cb->mqtt_para.default_sub_topic))
        {
            goto EXIT_MEM;
        }
    }
    else
    {

        cb->mqtt_para.default_pub_topic = topic_fmt(CN_OC_HUB_PUBTOPIC_DEFAULT_FMT,(const char *)cb->config.id);

        cb->mqtt_para.default_sub_topic = topic_fmt(CN_OC_HUB_SUBTOPIC_DEFAULT_FMT,(const char *)cb->config.id);

        cb->mqtt_para.default_msg_deal = hub_msg_default_deal;

        if((NULL == cb->mqtt_para.default_pub_topic) || \
                (NULL == cb->mqtt_para.default_sub_topic))
        {
            goto EXIT_MEM;
        }
    }

    if(cb->flag.bits.bit_bs_enable && ((cb->flag.bits.bit_daemon_status == (int)en_daemon_status_hub_keep)||\
            (cb->flag.bits.bit_daemon_status == (int)en_daemon_status_dmp_connecting)))
    {
        cb->mqtt_para.server_addr = cb->bs_cb.hubserver_addr;
        cb->mqtt_para.server_port = cb->bs_cb.hubserver_port;
    }
    else
    {
        cb->mqtt_para.server_addr = cb->config.server_addr;
        cb->mqtt_para.server_port = cb->config.server_port;
    }
    if((NULL == cb->mqtt_para.server_addr ) || \
       (NULL == cb->mqtt_para.server_port ))
    {
        goto EXIT_MEM;
    }
    return ret;

EXIT_MEM:
    (void) oc_mqtt_para_release(cb);
    ret = (int)en_oc_mqtt_err_sysmem;
    return ret;
}


///< return the reason code defined by the mqtt_al.h
static int dmp_connect(oc_mqtt_tiny_cb_t *cb)
{
    int  ret = (int)en_oc_mqtt_err_system;

    mqtt_al_conpara_t conpara;

    (void) memset(&conpara,0,sizeof(conpara));

    conpara.clientid.data = cb->mqtt_para.mqtt_clientid;
    conpara.clientid.len = strlen(conpara.clientid.data);

    conpara.user.data =  cb->mqtt_para.mqtt_user;
    conpara.user.len = strlen(conpara.user.data);

    conpara.passwd.data = cb->mqtt_para.mqtt_passwd;
    if(NULL != cb->mqtt_para.mqtt_passwd)
    {
        conpara.passwd.len = strlen(conpara.passwd.data);
    }

    conpara.cleansession = 1;
    conpara.keepalivetime = cb->config.lifetime;
    conpara.security = &cb->config.security;
    conpara.serveraddr.data = (char *)cb->mqtt_para.server_addr;
    conpara.serveraddr.len = strlen(conpara.serveraddr.data);
    conpara.serverport = atoi(cb->mqtt_para.server_port);
    conpara.timeout = CN_OC_MQTT_TIMEOUT;
    conpara.version = en_mqtt_al_version_3_1_1;
    conpara.willmsg = NULL;

    LINK_LOG_DEBUG("oc_mqtt_connect:server:%s port:%s \n\r",cb->mqtt_para.server_addr,cb->mqtt_para.server_port);
    LINK_LOG_DEBUG("oc_mqtt_connect:client_id:%s \n\r",cb->mqtt_para.mqtt_clientid);
    LINK_LOG_DEBUG("oc_mqtt_connect:user:%s passwd:%s \n\r",cb->mqtt_para.mqtt_user,(cb->mqtt_para.mqtt_passwd==NULL)?"NULL":cb->mqtt_para.mqtt_passwd);
    cb->mqtt_para.mqtt_handle = mqtt_al_connect(&conpara);

    if(NULL != cb->mqtt_para.mqtt_handle)
    {
        ret = (int)en_oc_mqtt_err_ok;
    }
    else
    {
        if(cn_mqtt_al_con_code_err_clientID == conpara.conret)
        {
            ret = (int)en_oc_mqtt_err_conclientid;
        }
        else if(cn_mqtt_al_con_code_err_netrefuse == conpara.conret)
        {
            ret = (int)en_oc_mqtt_err_conserver;
        }
        else if(cn_mqtt_al_con_code_err_u_p == conpara.conret)
        {
            ret = (int)en_oc_mqtt_err_conuserpwd;
        }
        else if(cn_mqtt_al_con_code_err_auth == conpara.conret)
        {
            ret = (int)en_oc_mqtt_err_conclient;
        }
        else
        {
            ret = (int)en_oc_mqtt_err_network;
        }
    }

    LINK_LOG_DEBUG("oc_mqtt_connect:recode:%d :%s\n\r",ret,ret==(int)en_oc_mqtt_err_ok?"SUCCESS":"FAILED");

    return ret;

}

static int dmp_subscribe(oc_mqtt_tiny_cb_t *cb)
{
    int  ret = (int)en_oc_mqtt_err_system;
    mqtt_al_subpara_t   subpara;

    LINK_LOG_DEBUG("oc_mqtt_subscribe:start\n\r");

    if(NULL == cb->mqtt_para.mqtt_handle)
    {
        ret = (int)en_oc_mqtt_err_noconected;
        return ret;
    }
    (void) memset(&subpara,0,sizeof(subpara));

    if(cb->flag.bits.bit_daemon_status == (int)en_daemon_status_bs_getaddr)
    {
        subpara.dealer = bs_msg_default_deal;
    }
    else
    {
        subpara.dealer = hub_msg_default_deal;
    }

    subpara.arg = cb;
    subpara.qos = en_mqtt_al_qos_1;
    subpara.topic.data = cb->mqtt_para.default_sub_topic ;
    subpara.topic.len = strlen(subpara.topic.data );
    subpara.timeout = CN_OC_MQTT_TIMEOUT;


    LINK_LOG_DEBUG("oc_mqtt_default_subscribe:topic:%s\n\r",subpara.topic.data);

    ret = mqtt_al_subscribe(cb->mqtt_para.mqtt_handle,&subpara);
    if(0 != ret)
    {
        ret = (int)en_oc_mqtt_err_subscribe;
    }

    LINK_LOG_DEBUG("oc_mqtt_default_subscribe:retcode:%d:%s\n\r",ret,oc_mqtt_err(ret));

    ///if not the bs mode, then subscribe all the other topic
    if(cb->flag.bits.bit_daemon_status != (int)en_daemon_status_bs_getaddr)
    {
        int i = 0;
        for(i =0;i<(int)CN_NEW_TOPIC_NUM;i++)
        {
            subpara.arg = cb;
            subpara.qos = en_mqtt_al_qos_1;
            subpara.topic.data = cb->hub_sub_topic[i] ;
            subpara.topic.len = strlen(subpara.topic.data );
            subpara.timeout = CN_OC_MQTT_TIMEOUT;

            LINK_LOG_DEBUG("oc_mqtt_subscribe:topic:%s\n\r",subpara.topic.data);

            ret = mqtt_al_subscribe(cb->mqtt_para.mqtt_handle,&subpara);

            LINK_LOG_DEBUG("oc_mqtt_subscribe:retcode:%d:%s\n\r",ret,oc_mqtt_err(ret));
            if(0 != ret)
            {
                 ret = (int)en_oc_mqtt_err_subscribe;
                 break;
            }
        }

        ///< subscribe the user topic
        tiny_topic_sub_t  *topic_sub;
        topic_sub = cb->subscribe_lst;
        while(NULL != topic_sub)
        {
            subpara.arg = cb;
            subpara.qos = en_mqtt_al_qos_1;
            subpara.topic.data = topic_sub->topic ;
            subpara.topic.len = strlen(subpara.topic.data );
            subpara.timeout = CN_OC_MQTT_TIMEOUT;

            LINK_LOG_DEBUG("oc_mqtt_subscribe:topic:%s\n\r",subpara.topic.data);

            ret = mqtt_al_subscribe(cb->mqtt_para.mqtt_handle,&subpara);

            LINK_LOG_DEBUG("oc_mqtt_subscribe:retcode:%d:%s\n\r",ret,oc_mqtt_err(ret));
            if(0 != ret)
            {
                 ret = (int)en_oc_mqtt_err_subscribe;
                 break;
            }
            topic_sub = topic_sub->nxt;
        }
    }

    return ret;
}

static int dmp_publish(oc_mqtt_tiny_cb_t *cb,char *topic, uint8_t *msg, int len, int qos)
{
    int  ret = (int)en_oc_mqtt_err_system;
    mqtt_al_pubpara_t pubpara;


    ///< pub the mqtt request
    (void) memset(&pubpara, 0, sizeof(pubpara));
    pubpara.qos = (en_mqtt_al_qos_t)qos;
    pubpara.retain = 0;
    pubpara.timeout = 1000;

    if(NULL == topic)
    {
        topic = cb->mqtt_para.default_pub_topic;
    }

    pubpara.topic.data = topic;
    pubpara.topic.len =strlen(pubpara.topic.data );
    pubpara.msg.data = (char *)msg;
    pubpara.msg.len = len;
    ret = mqtt_al_publish(cb->mqtt_para.mqtt_handle, &pubpara);
    if(ret != 0)
    {
        ret = (int)en_oc_mqtt_err_publish;
    }
    return ret;
}
static int hub_step(oc_mqtt_tiny_cb_t  *cb)
{
    int ret = (int)en_oc_mqtt_err_system;

    LINK_LOG_DEBUG("%s:enter\n\r",__FUNCTION__);
    if((int)en_oc_mqtt_err_ok != oc_mqtt_para_gernerate(cb))
    {
        goto EXIT_ERR;
    }

    ret = dmp_connect(cb);
    if((int)en_oc_mqtt_err_ok != ret)
    {
       goto EXIT_ERR;
    }
    ///< subscribe the topic here
    ret = dmp_subscribe(cb);
    if(ret  != (int)en_oc_mqtt_err_ok)
    {
        goto EXIT_ERR;
    }
    else
    {
        if(NULL != cb->config.log_dealer)
        {
            cb->flag.bits.bit_do_reportdisconnect = 0;
            cb->config.log_dealer(en_oc_mqtt_log_connected);
        }
    }

    LINK_LOG_DEBUG("%s:ok exit\n\r",__FUNCTION__);
    return ret;

EXIT_ERR:
    (void) oc_mqtt_para_release(cb);
    LINK_LOG_DEBUG("%s:err:%d \n\r",__FUNCTION__,ret);
    return ret;

}

///< this is the hub connect subscribe
static int bs_step(oc_mqtt_tiny_cb_t  *cb)
{
    int ret = (int)en_oc_mqtt_err_system;
    int wait_times = CN_CON_BACKOFF_MAXTIMES;

    LINK_LOG_DEBUG("%s:enter\n\r",__FUNCTION__);
    cb->flag.bits.bit_get_hubaddr = 0;

    if((int)en_oc_mqtt_err_ok != oc_mqtt_para_gernerate(cb))
    {
        goto EXIT_ERR;
    }

    ret = dmp_connect(cb);
    if((int)en_oc_mqtt_err_ok != ret)
    {
       goto EXIT_ERR;
    }
    ///< subscribe the topic here
    ret = dmp_subscribe(cb);
    if(ret  != (int)en_oc_mqtt_err_ok)
    {
       goto EXIT_ERR;
    }

    ///< pub the mqtt request
    if(ret != dmp_publish(cb,NULL,NULL,0,1))
    {
        goto EXIT_ERR;
    }
    ///< do the wait for the new address until timeout
    while((0 == cb->flag.bits.bit_get_hubaddr) && (wait_times-- > 0))
    {
        osal_task_sleep(CN_CON_BACKOFF_TIME);
    }

    if(cb->flag.bits.bit_get_hubaddr)
    {
        ret = (int)en_oc_mqtt_err_ok;
    }
    else
    {
        ret = (int)en_oc_mqtt_err_gethubaddrtimeout;
    }



EXIT_ERR:
    (void) oc_mqtt_para_release(cb);

    LINK_LOG_DEBUG("%s:exit ret:%d\n\r",__FUNCTION__,ret);

    return ret;

}


///< this function deal with api subscribe
static int deal_api_subscribe( oc_mqtt_tiny_cb_t  *cb, oc_mqtt_daemon_cmd_t *cmd)
{
    int ret = (int)en_oc_mqtt_err_noconfigured;
    tiny_topic_sub_t  *topic_sub;
    mqtt_al_subpara_t *subpara;
    mqtt_al_subpara_t  sub_new;

    subpara = cmd->arg;
    if((int)en_daemon_status_idle == cb->flag.bits.bit_daemon_status)
    {
        ret = (int)en_oc_mqtt_err_noconfigured;
    }
    else if(((int)en_daemon_status_hub_keep == cb->flag.bits.bit_daemon_status) &&\
            (en_mqtt_al_connect_ok == mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
    {
        ///< checkif the topic has been subscribe
        topic_sub = cb->subscribe_lst;
        while(NULL != topic_sub)
        {
            if(0 == strcmp(topic_sub->topic, subpara->topic.data))
            {
                break;
            }
            topic_sub = topic_sub->nxt;
        }

        if(NULL != topic_sub) ///< THERE HAS BEEN ONE
        {
            LINK_LOG_DEBUG("RESUBSCRIBED THE SAME TOPIC");
            ret = (int)en_oc_mqtt_err_subscribe;
        }
        else
        {
            topic_sub = osal_malloc( sizeof( tiny_topic_sub_t ) + subpara->topic.len + 1 );
            if ( NULL != topic_sub)
            {
                ///< initialize the subtopic and add it to the subscribe list when success
                topic_sub->qos = (int) subpara->qos;
                topic_sub->topic = (char *)topic_sub + sizeof(tiny_topic_sub_t);
                (void) strncpy(topic_sub->topic, subpara->topic.data,subpara->topic.len);
                topic_sub->topic[subpara->topic.len] = '\0';

                ///< copy the old parameters to the new one, for we could not change the user's memory
                (void)memset(&sub_new,0,sizeof(sub_new));
                sub_new.arg = cb;
                sub_new.dealer = hub_msg_default_deal;
                sub_new.timeout = CN_OC_MQTT_TIMEOUT;
                sub_new.qos = topic_sub->qos;
                sub_new.topic.data  = topic_sub->topic;
                sub_new.topic.len = subpara->topic.len;
                if( 0  == mqtt_al_subscribe( cb->mqtt_para.mqtt_handle, &sub_new) )
                {
                    topic_sub->nxt = cb->subscribe_lst;
                    cb->subscribe_lst = topic_sub;
                    ret = (int)en_oc_mqtt_err_ok;
                }
                else
                {
                    osal_free ( topic_sub );
                    ret = (int)en_oc_mqtt_err_subscribe;
                }
                subpara->subret = sub_new.subret;
            }
            else
            {
                ret = (int)en_oc_mqtt_err_sysmem;
            }
        }
    }
    else
    {
        ret = (int)en_oc_mqtt_err_noconected;
    }

    cmd->retcode = ret;

    return ret;

}

///< unsubscribe the specified topic
static int deal_api_unsubscribe( oc_mqtt_tiny_cb_t  *cb, oc_mqtt_daemon_cmd_t *cmd)
{
    int ret = (int)en_oc_mqtt_err_noconfigured;
    tiny_topic_sub_t  *topic_sub;
    tiny_topic_sub_t  *topic_sub_nxt;
    mqtt_al_unsubpara_t *unsubpara;

    unsubpara = cmd->arg;

    if((int)en_daemon_status_idle == cb->flag.bits.bit_daemon_status)
    {
        ret = (int)en_oc_mqtt_err_noconfigured;
    }
    else if(((int)en_daemon_status_hub_keep == cb->flag.bits.bit_daemon_status) &&\
            (en_mqtt_al_connect_ok == mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
    {

        if( 0  == mqtt_al_unsubscribe( cb->mqtt_para.mqtt_handle, unsubpara) )
        {
            ///< remove the topic from the subscribe list;
            topic_sub = cb->subscribe_lst;
            if(NULL != topic_sub)
            {
                if  ( 0 == strcmp( unsubpara->topic.data, topic_sub->topic ))
                {
                    cb->subscribe_lst = topic_sub->nxt;
                    osal_free(topic_sub);
                }
                else
                {
                    topic_sub_nxt = topic_sub->nxt;
                    while( NULL != topic_sub_nxt )
                    {
                        if ( 0 == strcmp( unsubpara->topic.data, topic_sub_nxt->topic))
                        {
                            topic_sub->nxt = topic_sub_nxt->nxt;
                            osal_free(topic_sub_nxt);
                            break;
                        }
                        else
                        {
                            topic_sub = topic_sub_nxt;
                            topic_sub_nxt = topic_sub_nxt->nxt;
                        }
                    }
                }
            }
            ret = (int)en_oc_mqtt_err_ok;
        }
        else
        {
            ret = (int)en_oc_mqtt_err_unsubscribe;
        }
    }
    else
    {
        ret = (int)en_oc_mqtt_err_noconected;
    }

    cmd->retcode = ret;

    return ret;

}


int daemon_entry_exit( oc_mqtt_tiny_cb_t  *cb)
{
    int ret = -1;

    if(NULL != cb)
    {
        cb->daemon_exit = 1;
        ret = 0;
    }
    return ret;
}


///< this is the daemon task entry
static int daemon_entry(void *arg)
{
    int ret = (int)en_oc_mqtt_err_ok;
    oc_mqtt_tiny_cb_t  *cb;
    oc_mqtt_daemon_cmd_t   *daemon_cmd = NULL;

    cb = arg;
    while((NULL != cb) && (0 == cb->daemon_exit))
    {
        if(0 == queue_pop(cb->task_daemon_cmd_queue,(void **)&daemon_cmd,10*1000))
        {
            switch (daemon_cmd->cmd)             ///< execute the command here
            {
                case en_oc_mqtt_daemon_cmd_connect:
                    if(cb->flag.bits.bit_daemon_status != (int)en_daemon_status_idle)
                    {
                         ret = (int)en_oc_mqtt_err_configured;
                    }
                    else
                    {
                        ret = config_parameter_clone(cb,daemon_cmd->arg);
                        if((ret == (int)en_oc_mqtt_err_ok) && (cb->flag.bits.bit_bs_enable))
                        {
                            cb->flag.bits.bit_daemon_status = en_daemon_status_bs_getaddr;
                            ret = bs_step(cb);
                        }
                        if(ret == (int)en_oc_mqtt_err_ok)
                        {
                            cb->flag.bits.bit_daemon_status = en_daemon_status_dmp_connecting;  ///< now we step in connecting status
                            ret = hub_step(cb);
                        }

                        if(ret == (int)en_oc_mqtt_err_ok)
                        {
                            cb->flag.bits.bit_daemon_status = en_daemon_status_hub_keep;    ///< now we step in keep status
                        }
                        else
                        {
                            cb->flag.bits.bit_daemon_status = en_daemon_status_idle;
                            (void) oc_mqtt_para_release(cb);
                            (void) config_parameter_release(cb);
                        }
                    }
                    daemon_cmd->retcode = ret;
                    break;
                case en_oc_mqtt_daemon_cmd_disconnect:
                    if(cb->flag.bits.bit_daemon_status == (int)en_daemon_status_idle)
                    {
                        daemon_cmd->retcode = (int)en_oc_mqtt_err_noconfigured;
                    }
                    else
                    {
                        (void) oc_mqtt_para_release(cb);

                        daemon_cmd->retcode = config_parameter_release(cb);
                    }
                    break;
                case en_oc_mqtt_daemon_cmd_publish:
                    if((int)en_daemon_status_idle == cb->flag.bits.bit_daemon_status)
                    {
                        daemon_cmd->retcode = (int)en_oc_mqtt_err_noconfigured;
                    }
                    else if(((int)en_daemon_status_hub_keep == cb->flag.bits.bit_daemon_status) &&\
                            (en_mqtt_al_connect_ok == mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
                    {
                        mqtt_al_pubpara_t *pubpara;
                        pubpara = daemon_cmd->arg;
                        daemon_cmd->retcode = dmp_publish(cb, pubpara->topic.data,\
                                   (uint8_t *)pubpara->msg.data,pubpara->msg.len,(int)pubpara->qos);
                    }
                    else
                    {
                        daemon_cmd->retcode = (int)en_oc_mqtt_err_noconected;
                    }
                    break;
                case en_oc_mqtt_daemon_cmd_subscribe:
                    LINK_LOG_DEBUG("daemon:subscribe enter\n\r");
                    (void) deal_api_subscribe( cb, daemon_cmd );
                    LINK_LOG_DEBUG("daemon:subscribe exit\n\r");
                    break;
                case en_oc_mqtt_daemon_cmd_unsubscribe:
                    LINK_LOG_DEBUG("daemon:unsubscribe enter\n\r");
                    (void) deal_api_unsubscribe( cb, daemon_cmd );
                    LINK_LOG_DEBUG("daemon:unsubscribe exit\n\r");
                    break;

                default:
                    break;

            }
            (void) osal_semp_post(daemon_cmd->signal); ///< activate the commander
        }

        ///< timeout we should check if we should do the reconnect
        if(cb->flag.bits.bit_do_bootstrap)
        {
            cb->flag.bits.bit_do_bootstrap = 0;

            cb->flag.bits.bit_daemon_status = en_daemon_status_bs_getaddr;
            (void) bs_step(cb);

            cb->flag.bits.bit_daemon_status = en_daemon_status_hub_keep;
            (void) hub_step(cb);
        }
        else if((cb->flag.bits.bit_daemon_status == (int)en_daemon_status_hub_keep) &&\
                (en_mqtt_al_connect_ok != mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
        {
            if((cb->flag.bits.bit_do_reportdisconnect == 0) && (NULL != cb->config.log_dealer))
            {
                cb->config.log_dealer(en_oc_mqtt_log_disconnected);
                cb->flag.bits.bit_do_reportdisconnect =1;
            }

            (void) hub_step(cb);
        }
        else
        {
            ///< do nothing here
        }
    }

    LINK_LOG_DEBUG("%s:quit\n\r",__FUNCTION__);
    return 0;
}


///< use this function to configure
static int tiny_config(oc_mqtt_config_t *config)
{
    int cert_mode = 0;
    int ret = (int)en_oc_mqtt_err_parafmt;
    if(NULL != config)
    {
        if((NULL == config->server_addr) || (NULL == config->server_port))  ///< no server information get
        {
            return ret;
        }
        if(config->boot_mode != en_oc_mqtt_mode_nobs_static_nodeid_hmacsha256_notimecheck_json )
        {
            LINK_LOG_DEBUG("BS NOT SUPPORT YET");
            ret = en_oc_mqtt_err_gethubaddrtimeout;
            return ret;
        }

        if(config->lifetime == 0)
        {
            config->lifetime = CN_OC_MQTT_LIFETIMEDEFAULT;
        }
        else if(config->lifetime < CN_OC_MQTT_LIFELEAST)
        {
            config->lifetime = CN_OC_MQTT_LIFELEAST;
        }
        else if(config->lifetime > CN_OC_MQTT_LIFEMAX)
        {
            config->lifetime = CN_OC_MQTT_LIFEMAX;
        }

        if(NULL == config->id)   ///< we should know your id
        {
            return ret;
        }

        if((config->security.type != EN_DTLS_AL_SECURITY_TYPE_CERT) &&(config->security.type != EN_DTLS_AL_SECURITY_TYPE_NONE))   ///< we only suport the two
        {
            return ret;
        }

        if(config->security.type == EN_DTLS_AL_SECURITY_TYPE_CERT)
        {
            if((NULL != config->security.u.cert.client_ca) && (NULL != config->security.u.cert.client_pk))
            {
                cert_mode = 1;
            }
        }

        if((NULL == config->pwd) && (cert_mode == 0))   ///< we permit the no pwd but you should config the client ca
        {
            return ret;
        }

        ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_connect,config);
    }
    return ret;
}



///< use this function to publish message
static int tiny_publish(char *topic,uint8_t *payload, int len,int qos )
{
    mqtt_al_pubpara_t pubpara;
    int  ret = (int)en_oc_mqtt_err_parafmt;

    if(qos >= (int)en_mqtt_al_qos_err)
    {
        return ret;
    }
    if(NULL == s_oc_mqtt_tiny_cb)
    {
        ret = (int)en_oc_mqtt_err_system;
        return ret;
    }

    ///< pub the mqtt request
    (void) memset(&pubpara, 0, sizeof(pubpara));
    pubpara.qos = (en_mqtt_al_qos_t)qos;
    pubpara.retain = 0;
    pubpara.timeout = 1000;
    pubpara.topic.data = topic;
    pubpara.msg.data = (char *)payload;
    pubpara.msg.len = len;

    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_publish,&pubpara);

    return ret;
}

///< use this function to subscribe a topic
static int tiny_subscribe(char *topic, int qos)
{
    ///< use this function to subscribe a topic
    mqtt_al_subpara_t  subpara;

    int  ret = (int)en_oc_mqtt_err_parafmt;

    if(qos >= (int)en_mqtt_al_qos_err)
    {
        return ret;
    }
    if(NULL == s_oc_mqtt_tiny_cb)
    {
        ret = (int)en_oc_mqtt_err_system;
        return ret;
    }

    ///< pub the mqtt request
    (void) memset(&subpara, 0, sizeof(subpara));
    subpara.qos = (en_mqtt_al_qos_t)qos;
    subpara.topic.data = topic;
    subpara.topic.len = strlen(topic);

    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_subscribe,&subpara);

    return ret;
}
///< use this function to unsubscribe a topic
static int tiny_unsubscribe(char *topic)
{
    ///< use this function to subscribe a topic
    mqtt_al_unsubpara_t  unsubpara;

    int  ret = (int)en_oc_mqtt_err_parafmt;
    if(NULL == s_oc_mqtt_tiny_cb)
    {
        ret = (int)en_oc_mqtt_err_system;
        return ret;
    }
    ///< pub the mqtt request
    (void) memset(&unsubpara, 0, sizeof(unsubpara));
    unsubpara.topic.data = topic;
    unsubpara.topic.len = strlen(topic);
    unsubpara.timeout = CN_OC_MQTT_TIMEOUT;
    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_unsubscribe,&unsubpara);

    return ret;
}

///< use this function to deconfig it
static int tiny_deconfig()
{
    int ret = (int)en_oc_mqtt_err_system;

    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_disconnect,NULL);

    return ret;
}



static const oc_mqtt_t s_oc_mqtt_tiny = \
{
    .name = "oc_mqtt_tiny",
    .op =
    {
        .config = tiny_config,
        .deconfig = tiny_deconfig,
        .publish = tiny_publish,
        .subscribe = tiny_subscribe,
        .unsubscribe = tiny_unsubscribe,
    },
};

///< use this function to install the oc mqtt to the oc mqtt abstract layer
int oc_mqtt_imp_init()
{
    int ret = -1;
    printf("max.su -> [%s:%d]\r\n", __FUNCTION__, __LINE__); // max.su

    oc_mqtt_tiny_cb_t *cb;

    cb = osal_malloc(sizeof(oc_mqtt_tiny_cb_t));
    if(NULL == cb)
    {
        goto EXIT_MALLOC;
    }
    (void) memset(cb,0,sizeof(oc_mqtt_tiny_cb_t));

    cb->task_daemon_cmd_queue = queue_create("daemon_cmd_queue",10,1);
    if(NULL == cb->task_daemon_cmd_queue)
    {
        goto EXIT_QUEUE;
    }

    cb->task_daemon = osal_task_create("oc_mqtt_tiny",daemon_entry,\
                                        cb,0x1800,NULL,10);
    if(NULL == cb->task_daemon)
    {
        goto EXIT_TASK;
    }

    ret = oc_mqtt_register(&s_oc_mqtt_tiny);
    if(0 != ret)
    {
        goto EXIT_REGISTER;
    }
    cb->daemon_exit = 0;
    s_oc_mqtt_tiny_cb = cb;
    return ret;


EXIT_REGISTER:
    (void) osal_task_kill(cb->task_daemon);
    cb->task_daemon = NULL;

EXIT_TASK:
    (void) queue_delete(cb->task_daemon_cmd_queue);
    cb->task_daemon_cmd_queue = NULL;

EXIT_QUEUE:
    osal_free(cb);
    cb = NULL;

EXIT_MALLOC:
    return ret;
}
