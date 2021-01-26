/*----------------------------------------------------------------------------
 * Copyright (c) <2019>, <Huawei Technologies Co., Ltd>
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


#include "lwm2m_port.h"
#include <lwm2m_al.h>
#include "lwm2m_rpt.h"
#include "lwm2m_context.h"
#include "internals.h"
//#include "lwm2m_common.h"
//#include <atiny_log.h>
//#include "connection.h"
//
//#include <stdio.h>

#ifdef CONFIG_FEATURE_FOTA
    #include "lwm2m_fota_manager.h"
#endif

typedef enum
{
    MSG_NONCONFIRMABLE,
    MSG_CONFIRMABLE
} lwm2m_message_type_e;

int g_reboot = 0;

/* data access control */
static osal_mutex_t g_data_mutex = cn_mutex_invalid;

static int __disconnect(void *handle);

static int generate_new_object_instance_id(lwm2m_list_t* instance_list)
{
    int id = 0;
    lwm2m_list_t *head = instance_list;

    if (NULL == instance_list)
    {
        return id;
    }

    while (NULL != head)
    {
        if (id < head->id)
        {
            break;
        }

        id++;

        head = head->next;
    }

    return id;
}

static int config_object(lwm2m_object_t *obj, void *param)
{
    int ret = (int) LWM2M_ERR;

    if (NULL == obj)
    {
        return (int) LWM2M_ARG_INVALID;
    }

    switch (obj->objID)
    {
        case OBJ_SECURITY_ID:
        {
            ret = config_security_object(obj, param);
            break;
        }

        case OBJ_SERVER_ID:
        {
            ret = config_server_object(obj, param);
            break;
        }

        case OBJ_ACCESS_CONTROL_ID:
        {
            ret = config_access_control_object(obj, param);
            break;
        }

        case OBJ_DEVICE_ID:
        {
            ret = config_device_object(obj, param);
            break;
        }

        case OBJ_CONNECTIVITY_MONITORING_ID:
        {
            ret = config_connectivity_monitoring_object(obj, param);
            break;
        }

#ifdef CONFIG_FEATURE_FOTA

        case OBJ_FIRMWARE_UPDATE_ID:
        {
            ret = config_firmware_update_object(obj, param);
            break;
        }

#endif

        case OBJ_LOCATION_ID:
        {
            ret = config_location_object(obj, param);
            break;
        }

        case OBJ_APP_DATA_ID:
        {
            ret = config_app_data_object(obj, param);
            break;
        }

        default:
        {
            break;
        }
    }

    return ret;
}

static int add_object_instance(lwm2m_object_t *obj,
                               lwm2m_list_t *obj_instance,
                               int object_instance_id,
                               uint16_t resource_id,
                               void *param)
{
    int ret = (int) LWM2M_ERR;

    if (NULL == obj)
    {
        return (int) LWM2M_ARG_INVALID;
    }

    switch (obj->objID)
    {
        case OBJ_SECURITY_ID:
        {
            ret = add_security_object_instance(obj, object_instance_id, param);
            break;
        }

        case OBJ_SERVER_ID:
        {
            ret = add_server_object_instance(obj, object_instance_id, param);
            break;
        }

        case OBJ_ACCESS_CONTROL_ID:
        {
            ret = add_access_control_object_instance(obj);
            break;
        }

        case OBJ_DEVICE_ID:
        {
            ret = add_device_object_instance(obj, object_instance_id);
            break;
        }

        case OBJ_CONNECTIVITY_MONITORING_ID:
        {
            ret = add_connectivity_monitoring_object_instance(obj, object_instance_id);
            break;
        }

#ifdef CONFIG_FEATURE_FOTA

        case OBJ_FIRMWARE_UPDATE_ID:
        {
            ret = add_firmware_update_object_instance(obj, object_instance_id);
            break;
        }

#endif

        case OBJ_LOCATION_ID:
        {
            ret = add_location_object_instance(obj, object_instance_id);
            break;
        }

        case OBJ_APP_DATA_ID:
        {
            ret = add_app_data_object_instance(obj, obj_instance, object_instance_id, resource_id, param);
            break;
        }

        default:
        {
            break;
        }
    }

    return ret;
}


/*
int lwm2m_receive(int type, char *msg, int len)
{
    if(g_cmd_func != NULL)
    {
        g_cmd_func(type, msg, len);
    }

    return 0;
}*/

static int lwm2m_check_mandatory_objects(lwm2m_object_t *object_list)
{
    lwm2m_object_t *obj = NULL;
    int object_num = 0;
    uint8_t found = 0;

    if (NULL == object_list)
    {
        return (int) LWM2M_ARG_INVALID;
    }

    obj = object_list;

    while (NULL != obj)
    {
        object_num++;

        if ((int)OBJ_SECURITY_ID == obj->objID)
        {
            found |= 0x01;
        }
        else if ((int)OBJ_SERVER_ID == obj->objID)
        {
            found |= 0x02;
        }
        else if ((int)OBJ_DEVICE_ID == obj->objID)
        {
            found |= 0x04;
        }

        obj = obj->next;
    }

    if ((object_num < 3) || (0x07 != found))
    {
        return (int)LWM2M_COAP_400_BAD_REQUEST;
    }

    return (int)(int) LWM2M_OK;
}

/*
 * add date:     2018-06-05
 * description:  get bootstrap info from atiny_params which from user, set bs_sequence_state and bs_server_uri for
lwm2m_context.
 *
 * return:       none
 * param:
 *     in:  atiny_params
 *     out: lwm2m_context
 */
static void lwm2m_set_bootstrap_sequence_state(lwm2m_al_init_param_t *lwm2m_params, lwm2m_context_t *lwm2m_context)
{
    (void)lwm2m_initBootStrap(lwm2m_context, (lwm2m_bootstrap_type_e)(lwm2m_params->bootstrap_type));
}


static void lwm2m_send_ack_callback(lwm2m_report_type_e type, int cookie, data_send_status_e status)
{
    LINK_LOG_DEBUG("type:%d cookie:%d status:%d\n", (int)type, cookie, (int)status);
}

static void observe_handle_ack(lwm2m_transaction_t *transacP, void *message)
{
    lwm2m_ack_callback ack_callback = (lwm2m_ack_callback)transacP->cfg.callback;

    if (transacP->ack_received)
    {
        ack_callback((lwm2m_report_type_e)(transacP->cfg.type), transacP->cfg.cookie, SENT_SUCCESS);
    }
    else if (transacP->retrans_counter > COAP_MAX_RETRANSMIT)
    {
        ack_callback((lwm2m_report_type_e)(transacP->cfg.type), transacP->cfg.cookie, SENT_TIME_OUT);
    }
    else
    {
        ack_callback((lwm2m_report_type_e)(transacP->cfg.type), transacP->cfg.cookie, SENT_FAIL);
    }
}

static void lwm2m_event_handle(module_type_t type, int code, const char *arg, int arg_len)
{
    switch (type)
    {
        case MODULE_LWM2M:
        {
            if ((int)STATE_REGISTERED == code)
            {
                lwm2m_event_notify(LWM2M_REG_OK, NULL, 0);
#ifdef CONFIG_FEATURE_FOTA
                (void)lwm2m_fota_manager_repot_result(lwm2m_fota_manager_get_instance());
#endif
            }
            else if ((int)STATE_REG_FAILED == code)
            {
                lwm2m_event_notify(LWM2M_REG_FAIL, NULL, 0);
            }

            break;
        }

        case MODULE_NET:
        {
            break;
        }

        case MODULE_URI:
        {
            if ((NULL == arg) || ((size_t)arg_len < sizeof(lwm2m_uri_t)))
            {
                break;
            }

            if (OBSERVE_UNSUBSCRIBE == code)
            {
                if (dm_isUriOpaqueHandle((lwm2m_uri_t *)arg))
                {
                    lwm2m_report_type_e rpt_type = APP_DATA;
                    lwm2m_event_notify(LWM2M_DATA_UNSUBSCRIBLE, (char *)&rpt_type, sizeof(rpt_type));
                }

                (void)lwm2m_clear_rpt_data((lwm2m_uri_t *)arg, (int)SENT_FAIL);
            }
            else if (OBSERVE_SUBSCRIBE == code)
            {
                if (dm_isUriOpaqueHandle((lwm2m_uri_t *)arg))
                {
                    lwm2m_report_type_e rpt_type = APP_DATA;
                    lwm2m_event_notify(LWM2M_DATA_SUBSCRIBLE, (char *)&rpt_type, sizeof(rpt_type));
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

static void lwm2m_connection_err_notify(lwm2m_context_t *context, connection_err_e err_type, bool boostrap_flag)
{
    handle_data_t *handle = NULL;

    if ((NULL == context) || (NULL == context->userData))
    {
        ATINY_LOG(LOG_ERR, "null point");
        return;
    }

    if (!boostrap_flag)
    {
        handle = LWM2M_FIELD_TO_STRUCT(context->userData, handle_data_t, client_data);
        (void)lwm2m_reconnect_ex(handle);
    }

    ATINY_LOG(LOG_INFO, "connection err type %d bootstrap %d", (int)err_type, boostrap_flag);
}

static int lwm2m_poll(handle_data_t *phandle, uint32_t timeout)
{
    client_data_t *dataP;
    int numBytes;
    connection_t *connP;
    lwm2m_context_t *contextP = NULL;
    uint8_t *recv_buffer = NULL;

    if ((NULL == phandle) || (NULL == phandle->recv_buffer))
    {
        return (int) LWM2M_ARG_INVALID;
    }

    recv_buffer = phandle->recv_buffer;
    contextP = phandle->lwm2m_context;
    dataP = (client_data_t *)(contextP->userData);
    connP = dataP->connList;

    while (NULL != connP)
    {
        numBytes = lwm2m_buffer_recv(connP, recv_buffer, MAX_PACKET_SIZE, timeout);

        if (numBytes <= 0)
        {
            ATINY_LOG(LOG_INFO, "no packet arrived!");
        }
        else
        {
            output_buffer(stderr, recv_buffer, numBytes, 0);
            lwm2m_handle_packet(contextP, recv_buffer, numBytes, connP);
        }

        connP = connP->next;
    }

    return (int) LWM2M_OK;
}

int lwm2m_destroy(void *handle)
{
    handle_data_t *handle_data = NULL;

    if (NULL == handle)
    {
        return (int) LWM2M_ARG_INVALID;
    }

    handle_data = (handle_data_t *)handle;
#ifdef CONFIG_FEATURE_FOTA
    lwm2m_fota_manager_destroy(lwm2m_fota_manager_get_instance());
#endif
    lwm2m_destroy_rpt();

    if (NULL != handle_data->lwm2m_context)
    {

#ifdef LWM2M_CLIENT_MODE
        (void) osal_mutex_del(handle_data->lwm2m_context->observe_mutex);
#endif

        lwm2m_close(handle_data->lwm2m_context);
    }

    (void) osal_semp_del(handle_data->quit_sem);
    handle_data->quit_sem = cn_semp_invalid;

    /* release receive data buffer */
    if (NULL != handle_data->recv_buffer)
    {
        lwm2m_free(handle_data->recv_buffer);
        handle_data->recv_buffer = NULL;
    }

    lwm2m_free(handle_data);
    (void) osal_mutex_del(g_data_mutex);
    return (int) LWM2M_OK;
}

void reboot_check(void)
{
    if (1 == g_reboot)
    {
        (void)lwm2m_cmd_ioctl(LWM2M_DO_DEV_REBOOT, NULL, 0);
    }
}

static void lwm2m_handle_reconnect(handle_data_t *handle)
{
    if ((NULL != handle) && handle->reconnect_flag)
    {
        (void)lwm2m_reconnect(handle->lwm2m_context);
        handle->reconnect_flag = false;
        ATINY_LOG(LOG_INFO, "lwm2m reconnect");
    }
}

void lwm2m_wait_task(void *phandle)
{
    handle_data_t *handle;

    if (NULL == phandle)
    {
        return;
    }

    handle = (handle_data_t *)phandle;
    handle->lwm2m_quit = 1;
    osal_semp_pend(handle->quit_sem, cn_osal_timeout_forever);
}

int lwm2m_reconnect_ex(void *phandle)
{
    handle_data_t *handle = (handle_data_t *)phandle;

    if (NULL == phandle)
    {
        ATINY_LOG(LOG_FATAL, "Parameter null");
        return (int) LWM2M_ARG_INVALID;
    }

    handle->reconnect_flag = true;
    return (int) LWM2M_OK;
}

void lwm2m_set_reboot_flag()
{
    g_reboot = true;
}

int __lwm2m_task_entry(void *args)
{
    uint32_t timeout;
    static handle_data_t *hd = NULL;
    if (NULL == args)
    {
        ATINY_LOG(LOG_ERR, "args is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    hd = (handle_data_t *)args;
    // (void) memcpy(&hd, args, sizeof(handle_data_t));

    while (!hd->lwm2m_quit)
    {
        timeout = BIND_TIMEOUT;
        (void)lwm2m_step_rpt(hd->lwm2m_context);
        lwm2m_handle_reconnect(hd);

        (void)lwm2m_step(hd->lwm2m_context, (time_t *)(uint32_t *)&timeout);

        reboot_check();

        if (0 == timeout)
        {
            timeout = 1;
        }

        (void)lwm2m_poll(hd, timeout);
    }

    /* notify task quit */
    (void) osal_semp_post(hd->quit_sem);
    return (int) LWM2M_OK;
}

static int __config(void **handle, lwm2m_al_init_param_t *init_param)
{
    int result = 0;
    lwm2m_context_t  *lwm2m_context = NULL;
    handle_data_t *hd = NULL;

    /* check input parameters */
    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    if (NULL == init_param)
    {
        ATINY_LOG(LOG_ERR, "init_param is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    /* check msg handle callback */
    if (NULL == init_param->dealer)
    {
        ATINY_LOG(LOG_ERR, "init_param->dealer is NULL!");
        return (int) LWM2M_ARG_INVALID;
    }

    hd = lwm2m_malloc(sizeof(handle_data_t));

    if (NULL == hd)
    {
        ATINY_LOG(LOG_FATAL, "memory not enough");
        return LWM2M_MALLOC_FAILED;
    }

    result = lwm2m_init_rpt();

    if ((int) LWM2M_OK != result)
    {
        ATINY_LOG(LOG_FATAL, "lwm2m_init_rpt fail,ret=%d", result);
        return result;
    }

    // g_cmd_func = init_param->dealer;
    (void) lwm2m_cmd_register_dealer(init_param->dealer);
    (void) memset(hd, 0, sizeof(handle_data_t));
    lwm2m_context = lwm2m_init(&(hd->client_data));

    if (NULL == lwm2m_context)
    {
        ATINY_LOG(LOG_ERR, "lwm2m_init fail");
        return (int)LWM2M_MALLOC_FAILED;
    }

    lwm2m_set_bootstrap_sequence_state(init_param, lwm2m_context);
    /* config parameters: endpoint name */
    lwm2m_context->endpointName = lwm2m_strdup(init_param->endpoint_name);

    if (NULL == lwm2m_context->endpointName)
    {
        /* release memory of lwm2m_context */
        lwm2m_free(lwm2m_context);
        return (int)LWM2M_MALLOC_FAILED;
    }

    lwm2m_context->msisdn = NULL;
    lwm2m_context->altPath = NULL;

    if (false == osal_mutex_create(&g_data_mutex))
    {
        ATINY_LOG(LOG_ERR, "osal_mutex_create fail");
        return (int)LWM2M_RESOURCE_NOT_ENOUGH;;
    }

    if (false == osal_semp_create(&(hd->quit_sem), 1, 0))
    {
        ATINY_LOG(LOG_FATAL, "osal_semp_create fail");
        lwm2m_free(lwm2m_context->endpointName);
        lwm2m_free(lwm2m_context);
        (void) osal_mutex_del(g_data_mutex);
        return (int)LWM2M_RESOURCE_NOT_ENOUGH;
    }

    /* register callback */
    lwm2m_register_observe_ack_call_back(observe_handle_ack);
    lwm2m_register_event_handler(lwm2m_event_handle);
    lwm2m_register_connection_err_notify(lwm2m_connection_err_notify);
    hd->recv_buffer = (uint8_t *)lwm2m_malloc(MAX_PACKET_SIZE);

    if (NULL == hd->recv_buffer)
    {
        ATINY_LOG(LOG_FATAL, "memory not enough");
        lwm2m_free(lwm2m_context->endpointName);
        lwm2m_free(lwm2m_context);
        (void) osal_mutex_del(g_data_mutex);
        (void) osal_semp_del(hd->quit_sem);
        return (int)LWM2M_MALLOC_FAILED;
    }
#ifdef LWM2M_CLIENT_MODE

    if(false == osal_mutex_create(&lwm2m_context->observe_mutex))
    {
        ATINY_LOG(LOG_FATAL, "memory not enough");
        lwm2m_free(lwm2m_context->endpointName);
        lwm2m_free(lwm2m_context);
        (void) osal_mutex_del(g_data_mutex);
        (void) osal_semp_del(hd->quit_sem);
        osal_free(hd->recv_buffer);
        return LWM2M_MALLOC_FAILED;
    }
#endif


#ifdef CONFIG_FEATURE_FOTA
    result = lwm2m_fota_manager_set_storage_device(lwm2m_fota_manager_get_instance());

    if ((int) LWM2M_OK != result)
    {
        ATINY_LOG(LOG_FATAL, "lwm2m_fota_manager_set_storage_device() called fail");
        lwm2m_free(lwm2m_context->endpointName);
        lwm2m_free(lwm2m_context);
        (void) osal_mutex_del(g_data_mutex);
        (void) osal_semp_del(hd->quit_sem);
        return result;
    }

    (void)lwm2m_fota_manager_set_lwm2m_context(lwm2m_fota_manager_get_instance(), lwm2m_context);
#endif



    hd->client_data.lwm2mH = lwm2m_context;
    hd->lwm2m_context = lwm2m_context;
    *handle = hd;
    ATINY_LOG(LOG_INFO, "result %d", result);
    return result;
}

static int __deconfig(void *handle)
{
    int ret = (int) LWM2M_ERR;

    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    ret = __disconnect(handle);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    return lwm2m_destroy(handle);
}

int __add_object(void *handle, int object_id, int object_instance_id, int resource_id, void *param)
{
    lwm2m_object_t *obj = NULL;
    lwm2m_list_t *obj_instance = NULL;
    handle_data_t *hd = NULL;
    int obj_ins_id = object_instance_id;

    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    hd = (handle_data_t *)handle;

    /* find object */
    LOG_ARG("ID: %d", object_id);

    obj = (lwm2m_object_t *)LWM2M_LIST_FIND(hd->lwm2m_context->objectList, object_id);

    if (NULL == obj)
    {
        /* not found, create new one */
        obj = (lwm2m_object_t *)lwm2m_malloc(sizeof(lwm2m_object_t));

        if (NULL == obj)
        {
            return LWM2M_MALLOC_FAILED;
        }

        (void) memset(obj, 0, sizeof(lwm2m_object_t));

        /* set object id */
        obj->objID = object_id;

        /* object config */
        config_object(obj, param);

        if (OBJ_SECURITY_ID == object_id)
        {
            hd->client_data.securityObjP = obj;
        }

        /* add to list */
        hd->lwm2m_context->objectList = (lwm2m_object_t *)LWM2M_LIST_ADD(hd->lwm2m_context->objectList, obj);
    }

    /* find object instance */
    if (-1 == obj_ins_id)
    {
        /* -1: find an available one */
        obj_ins_id = generate_new_object_instance_id(obj->instanceList);
        LINK_LOG_DEBUG("obj_ins_id: %d\n", obj_ins_id);
    }
    else
    {
        LINK_LOG_DEBUG("obj_ins_id: %d\n", obj_ins_id);
        obj_instance = (lwm2m_list_t *)LWM2M_LIST_FIND(obj->instanceList, obj_ins_id);
    }

    /* check if following objects are single instance:
       device,
       connectivity monitoring,
       firmware update,
       location,
       connectivity statistics

       condition: above object and obj instance list in not NULL and obj instance id is not found
      */
    if ((object_id >= OBJ_DEVICE_ID)
        && (object_id <= OBJ_CONNECTIVITY_STATISTICS_ID)
        && (NULL != obj->instanceList)
        && (NULL == obj_instance))
    {
        LINK_LOG_DEBUG("standard object_id %d only supports single instance!\n", object_id);
        return (int) LWM2M_SUPPORT_SINGLE_INSTANCE_ONLY;
    }

    /* found these objects' instance, return
        OBJ_SECURITY_ID,
        OBJ_SERVER_ID,
        OBJ_ACCESS_CONTROL_ID,
        */
    if ((object_id >= (int)OBJ_SECURITY_ID)
        && (object_id <= (int)OBJ_ACCESS_CONTROL_ID)
        && (NULL != obj_instance))
    {
        LINK_LOG_DEBUG("standard object_uri %d/%d/%d does not add resource!\n", object_id, obj_ins_id, resource_id);
        return (int) LWM2M_OBJECT_INSTANCE_EXISTED;
    }

    return add_object_instance(obj, obj_instance, obj_ins_id, resource_id, param);
}

int __delete_object(void *handle, int object_id)
{
    lwm2m_object_t *obj = NULL;
    lwm2m_context_t  *lwm2m_context = NULL;
    handle_data_t *hd = NULL;
    LOG_ARG("ID: %d", object_id);

    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    hd = (handle_data_t *)handle;

    if (NULL == hd->lwm2m_context)
    {
        return (int) LWM2M_NULL_POINTER;
    }

    lwm2m_context = hd->lwm2m_context;
    lwm2m_context->objectList = (lwm2m_object_t *)LWM2M_LIST_RM(lwm2m_context->objectList, object_id, &obj);

    if (NULL == obj)
    {
        return LWM2M_RESOURCE_NOT_FOUND;
    }

    switch (object_id)
    {
        case OBJ_SECURITY_ID:
        {
            clean_security_object(obj);
            break;
        }

        case OBJ_SERVER_ID:
        {
            clean_server_object(obj);
            break;
        }

        case OBJ_ACCESS_CONTROL_ID:
        {
            acl_ctrl_free_object(obj);
            break;
        }

        case OBJ_DEVICE_ID:
        {
            free_object_device(obj);
            break;
        }

        case OBJ_CONNECTIVITY_MONITORING_ID:
        {
            free_object_conn_m(obj);
            break;
        }

#ifdef CONFIG_FEATURE_FOTA

        case OBJ_FIRMWARE_UPDATE_ID:
        {
            free_object_firmware(obj);
            break;
        }

#endif

        case OBJ_LOCATION_ID:
        {
            free_object_location(obj);
            break;
        }

        case OBJ_APP_DATA_ID:
        {
            free_binary_app_data_object(obj);
            break;
        }

        default:
        {
            break;
        }
    }

    return (int) LWM2M_OK;
}

static int __connect(void *handle)
{
    int result = (int) LWM2M_OK;
    handle_data_t *hd = NULL;

    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    hd = (handle_data_t *)handle;

    if (NULL == hd->lwm2m_context)
    {
        return (int) LWM2M_NULL_POINTER;
    }

    /* check mandatory objects */
    result = lwm2m_check_mandatory_objects(hd->lwm2m_context->objectList);

    if ((int) LWM2M_OK != result)
    {
        return result;
    }

    hd->lwm2m_quit = 0;
    /* create the task for internal data process */
    hd->task_handle = osal_task_create("lwm2m_run", __lwm2m_task_entry, handle, 0x2000, NULL, 10);

    if (NULL == hd->task_handle)
    {
        result = (int) LWM2M_ERR;
    }

    ATINY_LOG(LOG_INFO, "result %d", result);
    return result;
}

int __disconnect(void *handle)
{
    handle_data_t *hd = (handle_data_t *)handle;
    osal_mutex_lock(g_data_mutex);

    if ((NULL != hd) && (NULL != hd->task_handle))
    {
        lwm2m_wait_task(handle);
        osal_task_kill(hd->task_handle);
        hd->task_handle = NULL;
    }

    (void) osal_mutex_unlock(g_data_mutex);
    return (int) LWM2M_OK;
}

static int __send(void *handle, lwm2m_al_send_param_t *send_param)
{
    int ret = -1;
    lwm2m_uri_t uri;
    data_report_t data;

    if (NULL == handle)
    {
        ATINY_LOG(LOG_ERR, "handle is an invalid parameter!");
        return (int) LWM2M_ARG_INVALID;
    }

    if ((NULL == send_param)
        || (send_param->length <= 0)
        || (send_param->length > MAX_REPORT_DATA_LEN)
        || (NULL == send_param->data))
    {
        ATINY_LOG(LOG_ERR, "invalid args");
        return (int) LWM2M_ARG_INVALID;
    }

    (void) memset((void *)&uri, 0, sizeof(uri));
    get_resource_uri(send_param->object_id, send_param->object_instance_id, send_param->resource_id, &uri);
    data.buf = lwm2m_malloc(send_param->length);

    if (NULL == data.buf)
    {
        ATINY_LOG(LOG_ERR, "lwm2m_malloc fail,len %d", data.len);
        return LWM2M_MALLOC_FAILED;;
    }

    (void) memcpy(data.buf, send_param->data, send_param->length);
    data.len = send_param->length;
    data.callback = (send_param->mode == MSG_CONFIRMABLE) ? lwm2m_send_ack_callback : NULL;
    data.cookie = 0;
    // data.type = APP_DATA;
    ret = lwm2m_queue_rpt_data(&uri, &data);

    if ((int) LWM2M_OK != ret)
    {
        if (NULL != data.buf)
        {
            lwm2m_free(data.buf);
        }
    }

    return (int) LWM2M_OK;
}

int lwm2m_imp_init(void)
{
    lwm2m_al_op_t lwm2m_op =
    {
        .config = __config,
        .deconfig = __deconfig,
        .add_object = __add_object,
        .delete_object = __delete_object,
        .connect = __connect,
        .disconnect = __disconnect,
        .send = __send,
    };
    return lwm2m_al_install(&lwm2m_op);
}

