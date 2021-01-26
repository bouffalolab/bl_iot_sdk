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
 *  1, the data encode only support the json mode
 *  2, the passwd only support the no check time mode
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <link_misc.h>
#include <time.h>

#include <queue.h>
#include <mqtt_al.h>
#include <oc_mqtt_al.h>
#include <sal.h>

#include <cJSON.h>           //json mode
#include "hmac.h"            //used to generate the user passwd

////CRT FOR THE OC
static const char s_oc_mqtt_ca_crt[] =
"-----BEGIN CERTIFICATE-----\r\n"
"MIID4DCCAsigAwIBAgIJAK97nNS67HRvMA0GCSqGSIb3DQEBCwUAMFMxCzAJBgNV\r\n"
"BAYTAkNOMQswCQYDVQQIEwJHRDELMAkGA1UEBxMCU1oxDzANBgNVBAoTBkh1YXdl\r\n"
"aTELMAkGA1UECxMCQ04xDDAKBgNVBAMTA0lPVDAeFw0xNjA1MDQxMjE3MjdaFw0y\r\n"
"NjA1MDIxMjE3MjdaMFMxCzAJBgNVBAYTAkNOMQswCQYDVQQIEwJHRDELMAkGA1UE\r\n"
"BxMCU1oxDzANBgNVBAoTBkh1YXdlaTELMAkGA1UECxMCQ04xDDAKBgNVBAMTA0lP\r\n"
"VDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJxM9fwkwvxeILpkvoAM\r\n"
"Gdqq3x0G9o445F6Shg3I0xmmzu9Of8wYuW3c4jtQ/6zscuIGyWf06ke1z//AVZ/o\r\n"
"dp8LkuFbBbDXR5swjUJ6z15b6yaYH614Ty/d6DrCM+RaU+FWmxmOon9W/VELu2BB\r\n"
"NXDQHJBSbWrLNGnZA2erk4JSMp7RhHrZ0QaNtT4HhIczFYtQ2lYF+sQJpQMrjoRn\r\n"
"dSV9WB872Ja4DgcISU1+wuWLmS/NKjIvOWW1upS79yu2I4Rxos2mFy9xxz311rGC\r\n"
"Z3X65ejFNzCUrNgf6NEP1N7wB9hUu7u50aA+/56D7EgjeI0gpFytC+a4f6JCPVWI\r\n"
"Lr0CAwEAAaOBtjCBszAdBgNVHQ4EFgQUcGqy59oawLEgMl21//7F5RyABpwwgYMG\r\n"
"A1UdIwR8MHqAFHBqsufaGsCxIDJdtf/+xeUcgAacoVekVTBTMQswCQYDVQQGEwJD\r\n"
"TjELMAkGA1UECBMCR0QxCzAJBgNVBAcTAlNaMQ8wDQYDVQQKEwZIdWF3ZWkxCzAJ\r\n"
"BgNVBAsTAkNOMQwwCgYDVQQDEwNJT1SCCQCve5zUuux0bzAMBgNVHRMEBTADAQH/\r\n"
"MA0GCSqGSIb3DQEBCwUAA4IBAQBgv2PQn66gRMbGJMSYS48GIFqpCo783TUTePNS\r\n"
"tV8G1MIiQCpYNdk2wNw/iFjoLRkdx4va6jgceht5iX6SdjpoQF7y5qVDVrScQmsP\r\n"
"U95IFcOkZJCNtOpUXdT+a3N+NlpxiScyIOtSrQnDFixWMCJQwEfg8j74qO96UvDA\r\n"
"FuTCocOouER3ZZjQ8MEsMMquNEvMHJkMRX11L5Rxo1pc6J/EMWW5scK2rC0Hg91a\r\n"
"Lod6aezh2K7KleC0V5ZlIuEvFoBc7bCwcBSAKA3BnQveJ8nEu9pbuBsVAjHOroVb\r\n"
"8/bL5retJigmAN2GIyFv39TFXIySw+lW0wlp+iSPxO9s9J+t\r\n"
"-----END CERTIFICATE-----\r\n";


///< devices normal data report and receive topic format
#define CN_CLIENT_ID_FMT                    "%s_2_0_%s"
#define CN_OC_HUB_CMD_TOPIC_FMT             "/huawei/v1/devices/%s/command/json"
#define CN_OC_HUB_REPORT_TOPIC_FMT          "/huawei/v1/devices/%s/data/json"
#define CN_OC_BS_REPORT_TOPIC_FMT           "/huawei/v1/devices/%s/iodpsData"
#define CN_OC_BS_CMD_TOPIC_FMT              "/huawei/v1/devices/%s/iodpsCommand"

/*The unit is millisecond*/
#define CN_CON_BACKOFF_TIME     (1000)   ///< UNIT:ms
#define CN_CON_BACKOFF_MAXTIMES  20      ///< WHEN WAIT OR GET ADDRESS ,WE COULD TRY MAX TIMES
#define CN_HMAC_LEN              32


#define CN_STRING_MAXLEN    127
#define IS_VALID_STRING(name) (strnlen((name), CN_STRING_MAXLEN + 1) <= CN_STRING_MAXLEN)

typedef struct
{
    char *hubserver_addr;     ///< we get from the bs server
    char *hubserver_port;     ///< we get from the bs server
}oc_bs_mqtt_cb_t; ///< when we used


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

        }bits;
    }flag;
    oc_bs_mqtt_cb_t     bs_cb;
    void               *task_daemon;            ///< oc mqtt lite daemon task
    queue_t            *task_daemon_cmd_queue;  ///< oc mqtt lite daemon task command queue
    char                salt_time[16];          ///< salt time for the connect
}oc_mqtt_tiny_cb_t;   ///< i think we may only got one mqtt
static oc_mqtt_tiny_cb_t *s_oc_mqtt_tiny_cb;

typedef enum
{
    en_oc_mqtt_daemon_cmd_connect = 0,
    en_oc_mqtt_daemon_cmd_send,           ///< when api need to send message, then it post this command
    en_oc_mqtt_daemon_cmd_publish,        ///< when api need to publish message, then it post this command
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

static void hub_msg_default_deal(void *arg,mqtt_al_msgrcv_t  *msg)
{
    cJSON  *root = NULL;
    cJSON  *cmd_item = NULL;
    cJSON  *serviceid_item = NULL;
    char   *json_buf;
    int     re_bootstrap = 0;

    mqtt_al_msgrcv_t normal_msg;

    //for we must add the '/0' to the end to make sure the json parse correct
    if ((msg == NULL) || ( msg->msg.data == NULL) ||(msg->msg.len == 0))
    {
        return;
    }

    json_buf = osal_malloc(msg->msg.len + 1);
    if(NULL != json_buf)
    {
        (void) memcpy(json_buf,msg->msg.data,msg->msg.len);
        json_buf[msg->msg.len] = '\0';

        LINK_LOG_DEBUG("bsmsg:%s\n\r",json_buf);
        root = cJSON_Parse(json_buf);
        if(NULL != root)
        {
            cmd_item = cJSON_GetObjectItem(root,"cmd");
            serviceid_item = cJSON_GetObjectItem(root,"serviceid");
            if(((NULL != cmd_item) && (strncmp(cmd_item->valuestring, "BootstrapRequestTrigger", strlen(cmd_item->valuestring)) == 0)) &&\
              ((NULL != serviceid_item) && (strncmp(serviceid_item->valuestring, "IOTHUB.BS", strlen(serviceid_item->valuestring)) == 0)))
            {
                s_oc_mqtt_tiny_cb->flag.bits.bit_do_bootstrap =1;
            }
            cJSON_Delete(root);
        }

        osal_free(json_buf);
    }
    if((0 == re_bootstrap)&&(NULL != s_oc_mqtt_tiny_cb->config.msg_deal))
    {
        normal_msg.dup = msg->dup;
        normal_msg.qos = msg->qos;
        normal_msg.retain = msg->retain;
        normal_msg.msg = msg->msg;
        if((NULL != msg->topic.data) && (NULL != s_oc_mqtt_tiny_cb->mqtt_para.default_sub_topic) \
                && (0 == memcmp(s_oc_mqtt_tiny_cb->mqtt_para.default_sub_topic,msg->topic.data,msg->topic.len)))
        {
            normal_msg.topic.data = NULL;
            normal_msg.topic.len = 0;
        }
        else
        {
            normal_msg.topic = msg->topic;
        }

        s_oc_mqtt_tiny_cb->config.msg_deal(s_oc_mqtt_tiny_cb->config.msg_deal_arg,&normal_msg);
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

static char *topic_fmt(const char *fmt, const char *arg)
{
    char *ret = NULL;
    int len =  0;

    len = strlen(fmt) + strlen(arg) + 1;

    ret = osal_malloc(len);
    if(NULL != ret)
    {
        (void) snprintf(ret,len,fmt,arg);
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
                osal_semp_pend(daemon_cmd->signal,cn_osal_timeout_forever);
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

    if(cb->config.id != NULL)
        osal_free(cb->config.id);

    if(cb->config.pwd != NULL)
        osal_free(cb->config.pwd);

    if(cb->config.server_addr != NULL)
        osal_free(cb->config.server_addr);

    if(cb->config.server_port != NULL)
        osal_free(cb->config.server_port);

    if(cb->bs_cb.hubserver_addr != NULL)
        osal_free(cb->bs_cb.hubserver_addr);

    if(cb->bs_cb.hubserver_port != NULL)
        osal_free(cb->bs_cb.hubserver_port);

    (void) memset(&cb->config,0,sizeof(oc_mqtt_config_t));

    (void) memset(&cb->bs_cb,0,sizeof(oc_bs_mqtt_cb_t));

    cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_idle;

    return (int)en_oc_mqtt_err_ok;
}
///< check the config parameters
static int config_parameter_clone(oc_mqtt_tiny_cb_t *cb,oc_mqtt_config_t *config)
{
    int ret = (int)en_oc_mqtt_err_parafmt;


    switch (config->boot_mode)
    {
        case en_oc_mqtt_mode_bs_static_nodeid_hmacsha256_notimecheck_json:
            cb->flag.bits.bit_bs_enable = 1;
            break;
        case en_oc_mqtt_mode_nobs_static_nodeid_hmacsha256_notimecheck_json:
            cb->flag.bits.bit_bs_enable = 0;
            break;
        default:
            return ret;
    }

    cb->config.security.type = config->security.type;
    if(config->security.type == EN_DTLS_AL_SECURITY_TYPE_CERT)
    {
        cb->config.security.u.cert.server_ca  = (uint8_t  *)s_oc_mqtt_ca_crt;
        cb->config.security.u.cert.server_ca_len = sizeof(s_oc_mqtt_ca_crt) ;
    }

    cb->config.boot_mode  = config->boot_mode;
    cb->config.id = osal_strdup(config->id);
    cb->config.pwd= osal_strdup(config->pwd);
    cb->config.lifetime = config->lifetime;
    cb->config.msg_deal = config->msg_deal;
    cb->config.msg_deal_arg = config->msg_deal_arg;
    cb->config.server_addr = osal_strdup(config->server_addr);
    cb->config.server_port = osal_strdup(config->server_port);

    if((NULL == cb->config.id) || (NULL == cb->config.pwd) ||\
       (NULL == cb->config.server_addr) || (NULL == cb->config.server_port))
    {
        (void)config_parameter_release(cb);
        ret = (int)en_oc_mqtt_err_sysmem;
        return ret;
    }

    ret = (int)en_oc_mqtt_err_ok;
    return ret;
}


///< generate the client_id user passwd for the mqtt need
static int  oc_mqtt_para_release(oc_mqtt_tiny_cb_t *cb)
{
    mqtt_al_disconnect(cb->mqtt_para.mqtt_handle);
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
        goto EXIT_MEM;
    }
    (void) snprintf(cb->salt_time,11,"%04d%02d%02d%02d",date->tm_year+1900,\
            date->tm_mon,date->tm_mday,date->tm_hour);

    (void) oc_mqtt_para_release(cb);         ///< try to free all the resource we have built

    cb->mqtt_para.mqtt_clientid = clientid_fmt(CN_CLIENT_ID_FMT,cb->config.id,cb->salt_time);
    if(NULL == cb->mqtt_para.mqtt_clientid)
    {
        goto EXIT_MEM;
    }

    cb->mqtt_para.mqtt_user = osal_strdup(cb->config.id);
    if(NULL == cb->mqtt_para.mqtt_user)
    {
        goto EXIT_MEM;
    }

    (void)hmac_generate_passwd(cb->config.pwd,strlen(cb->config.pwd),\
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

    if(cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_bs_getaddr)
    {
        cb->mqtt_para.default_pub_topic = topic_fmt(CN_OC_BS_REPORT_TOPIC_FMT,cb->config.id);

        cb->mqtt_para.default_sub_topic = topic_fmt(CN_OC_BS_CMD_TOPIC_FMT,cb->config.id);

        cb->mqtt_para.default_msg_deal = bs_msg_default_deal;

        if((NULL == cb->mqtt_para.default_pub_topic) || \
                (NULL == cb->mqtt_para.default_sub_topic))
        {
            goto EXIT_MEM;
        }
    }
    else
    {
        cb->mqtt_para.default_pub_topic = topic_fmt(CN_OC_HUB_REPORT_TOPIC_FMT,cb->config.id);

        cb->mqtt_para.default_sub_topic = topic_fmt(CN_OC_HUB_CMD_TOPIC_FMT,cb->config.id);

        cb->mqtt_para.default_msg_deal = hub_msg_default_deal;

        if((NULL == cb->mqtt_para.default_pub_topic) || \
                (NULL == cb->mqtt_para.default_sub_topic))
        {
            goto EXIT_MEM;
        }
    }

    if(cb->flag.bits.bit_bs_enable && ((cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_hub_keep)||\
            (cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_dmp_connecting)))
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
    conpara.passwd.len = strlen(conpara.passwd.data);

    conpara.cleansession = 1;
    conpara.keepalivetime = cb->config.lifetime;
    conpara.security = &cb->config.security;

    conpara.serveraddr.data = (char *)cb->mqtt_para.server_addr;
    conpara.serveraddr.len = strlen(conpara.serveraddr.data);
    conpara.serverport = atoi(cb->mqtt_para.server_port);
    conpara.timeout = 10000;
    conpara.version = en_mqtt_al_version_3_1_1;
    conpara.willmsg = NULL;

    LINK_LOG_DEBUG("oc_mqtt_connect:server:%s port:%s \n\r",cb->mqtt_para.server_addr,cb->mqtt_para.server_port);
    LINK_LOG_DEBUG("oc_mqtt_connect:client_id:%s \n\r",cb->mqtt_para.mqtt_clientid);
    LINK_LOG_DEBUG("oc_mqtt_connect:user:%s passwd:%s \n\r",cb->mqtt_para.mqtt_user,cb->mqtt_para.mqtt_passwd);
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
    }
    (void) memset(&subpara,0,sizeof(subpara));

    if(cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_bs_getaddr)
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

    LINK_LOG_DEBUG("oc_mqtt_subscribe:topic:%s\n\r",subpara.topic.data);

    ret = mqtt_al_subscribe(cb->mqtt_para.mqtt_handle,&subpara);
    if(0 != ret)
    {
        ret = (int)en_oc_mqtt_err_subscribe;
    }

    LINK_LOG_DEBUG("oc_mqtt_subscribe:retcode:%d:%s\n\r",ret,ret==0?"SUCCESS":"FAIL");


    return ret;
}

static int dmp_publish(oc_mqtt_tiny_cb_t *cb,char *topic, uint8_t *msg, int len, int qos)
{
    int  ret = (int)en_oc_mqtt_err_system;
    mqtt_al_pubpara_t pubpara;


    ///< pub the mqtt request
    (void) memset(&pubpara, 0, sizeof(pubpara));
    pubpara.qos = qos;
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

    LINK_LOG_DEBUG("oc_mqtt_publish:topic:%s  qos:%d msglen:%d\n\r",topic,qos,len);

    ret = mqtt_al_publish(cb->mqtt_para.mqtt_handle, &pubpara);
    if(ret != 0)
    {
        ret = (int)en_oc_mqtt_err_publish;
    }
    LINK_LOG_DEBUG("oc_mqtt_publish:retcode:%d:%s\n\r",ret,ret==0?"SUCCESS":"FAIL");
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

    LINK_LOG_DEBUG("%s:ok exit\n\r",__FUNCTION__);
    return ret;

EXIT_ERR:
    (void) oc_mqtt_para_release(cb);
    LINK_LOG_DEBUG("%s:err:%d n\r",__FUNCTION__,ret);
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


///< this is the daemon task entry
static int daemon_entry(void *arg)
{
    int ret = (int)en_oc_mqtt_err_ok;
    oc_mqtt_tiny_cb_t  *cb;
    oc_mqtt_daemon_cmd_t   *daemon_cmd = NULL;

    cb = arg;
    LINK_LOG_DEBUG("%s:start\n\r",__FUNCTION__);
    while(1)
    {
        if(0 == queue_pop(cb->task_daemon_cmd_queue,(void **)&daemon_cmd,10*1000))
        {
            ret = (int)en_oc_mqtt_err_ok;
            switch (daemon_cmd->cmd)             ///< execute the command here
            {
                case en_oc_mqtt_daemon_cmd_connect:
                    if(cb->flag.bits.bit_daemon_status != (uint32_t) en_daemon_status_idle)
                    {
                         ret = (int)en_oc_mqtt_err_configured;
                    }
                    else
                    {
                        ret = config_parameter_clone(cb,daemon_cmd->arg);
                        if((ret == (int)en_oc_mqtt_err_ok) && (cb->flag.bits.bit_bs_enable))
                        {
                            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_bs_getaddr;
                            ret = bs_step(cb);
                        }
                        if(ret == (int)en_oc_mqtt_err_ok)
                        {
                            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_dmp_connecting;  ///< now we step in connecting status
                            ret = hub_step(cb);
                        }

                        if(ret == (int)en_oc_mqtt_err_ok)
                        {
                            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_hub_keep;    ///< now we step in keep status
                        }
                        else
                        {
                            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_idle;
                            (void) oc_mqtt_para_release(cb);
                            (void)config_parameter_release(cb);
                        }
                    }
                    daemon_cmd->retcode = ret;
                    break;
                case en_oc_mqtt_daemon_cmd_disconnect:
                    if(cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_idle)
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
                    LINK_LOG_DEBUG("daemon:publish enter\n\r");
                    if((uint32_t) en_daemon_status_idle == cb->flag.bits.bit_daemon_status)
                    {
                        daemon_cmd->retcode = (int)en_oc_mqtt_err_noconfigured;
                    }
                    else if(((uint32_t) en_daemon_status_hub_keep == cb->flag.bits.bit_daemon_status) &&\
                            (en_mqtt_al_connect_ok == mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
                    {
                        mqtt_al_pubpara_t *pubpara;
                        pubpara = daemon_cmd->arg;
                        daemon_cmd->retcode = dmp_publish(cb, pubpara->topic.data,\
                                   (uint8_t *)pubpara->msg.data,pubpara->msg.len,pubpara->qos);
                    }
                    else
                    {
                        daemon_cmd->retcode = (int)en_oc_mqtt_err_noconected;
                    }
                    LINK_LOG_DEBUG("daemon:publish exit\n\r");
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

            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_bs_getaddr;
            bs_step(cb);

            cb->flag.bits.bit_daemon_status = (uint32_t) en_daemon_status_hub_keep;
            hub_step(cb);
        }
        else if((cb->flag.bits.bit_daemon_status == (uint32_t) en_daemon_status_hub_keep) &&\
                (en_mqtt_al_connect_ok != mqtt_al_check_status(cb->mqtt_para.mqtt_handle)))
        {
            hub_step(cb);
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
    int ret = (int)en_oc_mqtt_err_parafmt;
    if(NULL != config)
    {
        if((NULL == config->id) || (NULL == config->pwd) ||\
            (NULL == config->server_addr) || (NULL == config->server_port))
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

    if(qos >= en_mqtt_al_qos_err)
    {
        return ret;
    }
    if(NULL == s_oc_mqtt_tiny_cb)
    {
        ret = (int)en_oc_mqtt_err_system;
    }

    ///< pub the mqtt request
    (void) memset(&pubpara, 0, sizeof(pubpara));
    pubpara.qos = qos;
    pubpara.retain = 0;
    pubpara.timeout = 1000;
    pubpara.topic.data = topic;
    pubpara.msg.data = (char *)payload;
    pubpara.msg.len = len;

    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_publish,&pubpara);


    return ret;
}


///< use this function to deconfig it
static int tiny_deconfig()
{
    int ret = (int)en_oc_mqtt_err_system;

    ret = daemon_cmd_post(en_oc_mqtt_daemon_cmd_disconnect,NULL);

    return ret;
}

static const oc_mqtt_t s_oc_mqtt_lite = \
{
    .name = "oc_mqtt_tiny",
    .op =
    {
        .config = tiny_config,
        .deconfig = tiny_deconfig,
        .publish = tiny_publish,
    },
};

///< use this function to install the oc mqtt to the oc mqtt abstract layer
int oc_mqtt_imp_init()
{
    int ret = -1;

    oc_mqtt_tiny_cb_t *cb;

    cb = osal_malloc(sizeof(oc_mqtt_tiny_cb_t));
    if(NULL == cb)
    {
        goto EXIT_MALLOC;
    }
    (void) memset(cb,0,sizeof(oc_mqtt_tiny_cb_t));

    cb->task_daemon_cmd_queue = queue_create("oc_mqtt_tiny_cmd_queue",10,1);
    if(NULL == cb->task_daemon_cmd_queue)
    {
        goto EXIT_QUEUE;
    }

    cb->task_daemon = osal_task_create("oc_mqtt_tiny_daemon",daemon_entry,\
                                        cb,0x1800,NULL,10);
    if(NULL == cb->task_daemon)
    {
        goto EXIT_TASK;
    }

    ret = oc_mqtt_register(&s_oc_mqtt_lite);
    if(0 != ret)
    {
        goto EXIT_REGISTER;
    }
    s_oc_mqtt_tiny_cb = cb;
    return ret;


EXIT_REGISTER:
    osal_task_kill(cb->task_daemon);
    cb->task_daemon = NULL;

EXIT_TASK:
    queue_delete(cb->task_daemon_cmd_queue);
    cb->task_daemon_cmd_queue = NULL;

EXIT_QUEUE:
    osal_free(cb);
    cb = NULL;

EXIT_MALLOC:
    return ret;
}

void oc_mqtt_imp_deinit(void)
{
    oc_mqtt_tiny_cb_t *cb = s_oc_mqtt_tiny_cb;
    if(!cb)
        return;
    if(cb->task_daemon)
    {
        osal_task_kill(cb->task_daemon);
        osal_task_sleep(500);
    }

    if(cb->task_daemon_cmd_queue)
    {
        queue_delete(cb->task_daemon_cmd_queue);
    }

    osal_free(cb);
    
    s_oc_mqtt_tiny_cb = NULL;
}

