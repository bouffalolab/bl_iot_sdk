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
#include <string.h>

#include <sinn_client.h>
#include <mqtt_al.h>
#include <sinn_mqtt.h>
#include <osal.h>

#ifdef WITH_DTLS
#include "sinn_sec_socket.h"
#else
#include "sinn_nosec_socket.h"
#endif

extern sinn_if_funcs_t sinn_nosec_if;
extern sinn_if_funcs_t sinn_sec_if;


typedef struct
{
    sinn_manager_t *mgr;
    void           *task;    //create a task for this client
} sinn_mqtt_cb_t;


static sinn_device_info_t default_dev_info;
static osal_queue_t link_queue;
static osal_semp_t link_sem;

static int __loop_entry(void *arg)
{
    sinn_manager_t *mgr;
    mgr= arg;
    for(;;)
    {
        sinn_poll(mgr, SINN_EVENTS_HANDLE_PERIOD_MS);
    }
    return 0;
}




static void ev_handler(sinn_connection_t *nc, int event, void *event_data)
{
    sinn_mqtt_msg_t *amm = (sinn_mqtt_msg_t *)event_data;
    switch(event)
    {
        case SINN_EV_CONNECTED:
            {
                LINK_LOG_DEBUG("now mqtt connect\r\n");
                sinn_connect_param_t * sinn_conn_param;
                mqtt_connect_opt_t *options;
                sinn_conn_param = (sinn_connect_param_t *)(nc->user_data);

                sinn_register_proto(nc, sinn_mqtt_event_handler);
                options = (mqtt_connect_opt_t *)sinn_conn_param->protocol_con_param;
                nc->proto_data = (void *)osal_malloc((size_t)sizeof(sinn_mqtt_proto_data_t));
                sinn_mqtt_connect(nc, options);
                osal_free(options);
            }
            break;
        case SINN_EV_RECONN:
            {
                (void) osal_semp_post(link_sem);
            }
            break;
        case EV_MQTT_CONNACK:
            {
                if (amm->ret[0] == MQTT_CONNACK_ACCEPTED)
                {
                    osal_queue_send(link_queue, &amm->ret[0], sizeof(amm->ret[0]), 0);
                    (void) osal_semp_post(link_sem);
                }
                else
                {
                    LINK_LOG_DEBUG("MQTT Connect Err:%d", amm->ret[0]);
                }
                free(amm->ret);
            }
            break;
        case EV_MQTT_SUBACK:
            {
                osal_queue_send(link_queue, amm->ret, 8, 0);
                (void) osal_semp_post(link_sem);
                free(amm->ret);
            }
            break;
        case EV_MQTT_PUBLISH:
            {
                LINK_LOG_DEBUG("recv pushlish %s\r\n", (char *)amm->payload);
                mqtt_puback_opt_t options;
                options.puback_head.packet_id = amm->id;

                if (amm->qos != QOS0)
                {
                    if (amm->qos == QOS1)
                    {
                        options.type = MQTT_PACKET_TYPE_PUBACK;
                        (void)sinn_mqtt_puback(nc, &options);
                    }
                    else if (amm->qos == QOS2)
                    {
                        options.type = MQTT_PACKET_TYPE_PUBREC;
                        (void)sinn_mqtt_puback(nc, &options);
                    }
                }
            }
            break;
        case EV_MQTT_PUBREC:
            {
                mqtt_puback_opt_t options;
                options.puback_head.packet_id = amm->id;
                options.type = MQTT_PACKET_TYPE_PUBREL;
                (void)sinn_mqtt_puback(nc, &options);
            }
            break;
        case EV_MQTT_PUBACK:
        case EV_MQTT_PUBCOMP:
            {
                (void) osal_semp_post(link_sem);
            }
            break;
        case EV_MQTT_PUBREL:
            {
                mqtt_puback_opt_t options;
                options.type = MQTT_PACKET_TYPE_PUBCOMP;
                (void)sinn_mqtt_puback(nc, &options);
            }
            break;
        default:
            break;
    }
}

static void * __connect(mqtt_al_conpara_t *conparam)
{
    void *ret = NULL;
    sinn_mqtt_cb_t *cb = NULL;
    sinn_manager_t *mgr = NULL;
    sinn_connect_param_t *param = NULL;
    mqtt_connect_opt_t *mqtt_con_param;

    cb = osal_malloc(sizeof(sinn_mqtt_cb_t));
    mgr = osal_malloc(sizeof(sinn_manager_t));
    cb->mgr = mgr;

    param = (sinn_connect_param_t *)osal_malloc(sizeof(sinn_connect_param_t));
    param->proto_type = SOCK_STREAM;
    param->server_ip = conparam->serveraddr.data;
    param->server_port = conparam->serverport;
    mqtt_con_param = (mqtt_connect_opt_t *)osal_malloc(sizeof(mqtt_connect_opt_t));
    param->protocol_con_param = mqtt_con_param;

    mqtt_con_param->connect_head = (mqtt_connect_head_t)MQTT_CONNECT_HEAD_INIT;
    mqtt_con_param->connect_head.keep_alive = conparam->keepalivetime;
    mqtt_con_param->connect_payload.client_id = conparam->clientid.data;
    mqtt_con_param->connect_payload.user_name = conparam->user.data;
    mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.psd_flag = 1;
    mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.user_name_flag = 1;
    mqtt_con_param->connect_payload.password = conparam->passwd.data;

    if (NULL != conparam->willmsg)
    {
        mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.will_flag = 1;
        mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.will_qos = conparam->willmsg->qos;
        mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.will_retain = conparam->willmsg->retain;

        mqtt_con_param->connect_payload.will_topic = conparam->willmsg->topic.data;

        mqtt_con_param->connect_payload.will_msg =conparam->willmsg->msg.data;

    }
    else
    {
        mqtt_con_param->connect_head.mqtt_connect_flag_u.bits.will_flag = 0;
    }

    if (NULL == conparam->security || conparam->security->type == en_mqtt_al_security_none)
    {
        param->ssl_param.type = en_mqtt_al_security_none;
        #ifndef WITH_DTLS
        default_dev_info.ifuncs = &sinn_nosec_if;
        #endif
    }
    else
    {
        param->ssl_param.type = conparam->security->type;
        #ifdef WITH_DTLS
            default_dev_info.ifuncs = &sinn_sec_if;
        #endif
        switch(param->ssl_param.type)
        {
            case en_mqtt_al_security_psk:
                param->ssl_param.u.psk.psk_id = (const unsigned char *)conparam->security->u.psk.psk_id.data;
                param->ssl_param.u.psk.psk_id_len = (size_t)conparam->security->u.psk.psk_id.len;
                param->ssl_param.u.psk.psk_len = (size_t)conparam->security->u.psk.psk_key.len;
                param->ssl_param.u.psk.psk = (const unsigned char *)conparam->security->u.psk.psk_key.data;
                break;
            case en_mqtt_al_security_cas:
                param->ssl_param.u.uni_ca.ca_cert_len = (size_t)conparam->security->u.cas.ca_crt.len;
                param->ssl_param.u.uni_ca.ca_cert = (const unsigned char *)conparam->security->u.cas.ca_crt.data;
                break;
            case en_mqtt_al_security_cacs:
                param->ssl_param.u.bi_ca.server_name = (const char *)conparam->security->u.cacs.ca_host.data;
                param->ssl_param.u.bi_ca.ca_cert_len = (size_t)conparam->security->u.cacs.ca_s_crt.len;
                param->ssl_param.u.bi_ca.ca_cert = (const unsigned char *)conparam->security->u.cacs.ca_s_crt.data;
                param->ssl_param.u.bi_ca.client_cert_len = (size_t)conparam->security->u.cacs.ca_c_crt.len;
                param->ssl_param.u.bi_ca.client_cert = (const unsigned char *)conparam->security->u.cacs.ca_c_crt.data;
                param->ssl_param.u.bi_ca.client_key_len = (size_t)conparam->security->u.cacs.ca_c_key.len;
                param->ssl_param.u.bi_ca.client_key = (const unsigned char *)conparam->security->u.cacs.ca_c_key.data;
                break;
            default:
                break;
        }
    }

    sinn_init(mgr, &default_dev_info);
    osal_queue_create(&link_queue, 10, 10);
    osal_semp_create(&link_sem, 1, 0);

    mgr->nc = sinn_connect(mgr, ev_handler, param);
    if(mgr->nc)
    {
        cb->task =osal_task_create("sinn",__loop_entry,mgr,0x800,NULL,4);
        osal_semp_pend(link_sem, 5*1000);
        osal_queue_recv(link_queue, &conparam->conret, sizeof(conparam->conret), 0);

        ret = cb;
        return ret;
    }
    else
    {
        conparam->conret = cn_mqtt_al_con_code_err_network;
        return NULL;
    }
}

static int __disconnect(void *handle)
{
    int ret = -1;
    LINK_LOG_DEBUG("sinn mqtt disconnect\r\n");
    sinn_mqtt_cb_t *cb;

    if (NULL == handle)
    {
        return ret;
    }

    cb = handle;

    //mqtt disconnect
    sinn_mqtt_disconnect(cb->mgr->nc);
    //kill the thread
    osal_task_kill(cb->task);
    //net disconnect
    cb->mgr->interface->ifuncs->if_discon(cb->mgr->nc);
    //deinit the mqtt
    //free the memory
    sinn_destory(cb->mgr->nc);
    osal_queue_del(link_queue);
    (void) osal_semp_del(link_sem);
    if(cb)
    {
        osal_free(cb);
        cb = NULL;
    }

    return 0;
}

static void general_dealer(sinn_mqtt_msg_t *data)
{
    mqtt_al_msgrcv_t           msg;
    fn_mqtt_al_msg_dealer      dealer;
    msg.dup = data->dup;
    msg.qos = data->qos;
    msg.retain = data->retained;
    msg.msg.len = data->payloadlen;
    msg.msg.data = data->payload;
    msg.topic.data = data->topic;
    msg.topic.len = data->topiclen;

    if (NULL != data->arg)
    {
        dealer = data->arg;
        dealer(NULL,&msg);  ///<   the args not implement yet
    }
}


static int __subscribe(void *handle,mqtt_al_subpara_t *para)
{
    int ret = -1;
    mqtt_subscribe_opt_t opt;
    sinn_connection_t *nc;
    sinn_mqtt_cb_t *cb;
    cb = (sinn_mqtt_cb_t *)handle;
    nc = cb->mgr->nc;

    opt.subscribe_payload.count = 1;
    opt.subscribe_payload.qoss = (unsigned char *)osal_malloc(sizeof(unsigned char) * opt.subscribe_payload.count);
    opt.subscribe_payload.topic = (char **)osal_malloc(opt.subscribe_payload.count * sizeof(char *));
    opt.subscribe_payload.qoss[0] = para->qos;
    opt.subscribe_payload.topic[0] = para->topic.data;

    ret = sinn_mqtt_subscribe(nc, &opt, general_dealer, para->dealer);
    if (ret > 0)
    {
        ret = osal_semp_pend(link_sem, 5*1000);
        if (ret == false)
        {
            ret = -1;
            goto exit;
        }
        else
        {
            ret = 0;
        }
    }
    else
    {
        ret = -1;
        goto exit;
    }
    osal_queue_recv(link_queue, &para->subret, sizeof(para->subret), 0);

exit:
    if (opt.subscribe_payload.qoss)
        osal_free(opt.subscribe_payload.qoss);
    if (opt.subscribe_payload.topic)
        osal_free(opt.subscribe_payload.topic);

    return ret;
}

static int __unsubscribe(void *handle,mqtt_al_unsubpara_t *para)
{
    int ret = -1;
    mqtt_unsubscribe_opt_t opt;
    sinn_connection_t *nc;
    sinn_mqtt_cb_t *cb;

    cb = (sinn_mqtt_cb_t *)handle;
    nc = cb->mgr->nc;

    opt.unsubscribe_payload.count = 1;
    opt.unsubscribe_payload.topic = (char **)osal_malloc(opt.unsubscribe_payload.count * sizeof(char *));
    opt.unsubscribe_payload.topic[0] = para->topic.data;

    ret = sinn_mqtt_unsubscribe(nc, &opt);
    if (ret > 0)
    {
        ret = osal_semp_pend(link_sem, 5*1000);
        if (ret == false)
        {
            ret = -1;
            goto exit;
        }
    }
    else
    {
        ret = -1;
        goto exit;
    }

exit:
    if (opt.unsubscribe_payload.topic)
        osal_free(opt.unsubscribe_payload.topic);

    return ret;
}

static int __publish(void *handle, mqtt_al_pubpara_t *para)
{
    int ret = -1;
    mqtt_publish_opt_t opt;
    sinn_connection_t *nc;
    sinn_mqtt_cb_t *cb;

    cb = (sinn_mqtt_cb_t *)handle;
    nc = cb->mgr->nc;

    opt.publish_head.topic = para->topic.data;
    opt.publish_head.topic_len = para->topic.len;

    opt.qos = para->qos;
    opt.retain = para->retain;
    opt.dup = 0;

    opt.publish_payload.msg = para->msg.data;
    opt.publish_payload.msg_len = para->msg.len;
    ret = sinn_mqtt_publish(nc, &opt);
    if (ret > 0)
    {
        ret = osal_semp_pend(link_sem, 5*1000);
        if (ret == true)
            return 0;
        else
            return -1;
    }
    else
    {
        return -1;
    }
}

static en_mqtt_al_connect_state __check_status(void *handle)
{
    int ret = en_mqtt_al_connect_err;
    sinn_connection_t *nc;
    sinn_mqtt_cb_t *cb;

    cb = (sinn_mqtt_cb_t *)handle;
    nc = cb->mgr->nc;

    if (!(nc->flags & SINN_FG_RECONNECT))
    {
        ret = en_mqtt_al_connect_ok;
    }
    else
    {
        nc->flags &= ~SINN_FG_RECONNECT;
    }

    return ret;
}

int mqtt_install_sinnmqtt()
{
    int ret = -1;

    mqtt_al_op_t sinn_mqtt_op =
    {
        .connect = __connect,
        .disconnect = __disconnect,
        .subscribe = __subscribe,
        .unsubscribe = __unsubscribe,
        .publish = __publish,
        .check_status = __check_status,
    };

    ret = mqtt_al_install(&sinn_mqtt_op);

    return ret;
}
