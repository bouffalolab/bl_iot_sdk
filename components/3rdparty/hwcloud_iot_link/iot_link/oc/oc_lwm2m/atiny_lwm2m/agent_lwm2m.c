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


#include <osal.h>
#include <lwm2m_al.h>
#include <oc_lwm2m_al.h>
#include <atiny_log.h>
#include <string.h>

typedef enum
{
    ATINY_OK                   =  0,
    ATINY_ARG_INVALID          = -1,
    ATINY_BUF_OVERFLOW         = -2,
    ATINY_MSG_CONGEST          = -3,
    ATINY_MALLOC_FAILED        = -4,
    ATINY_RESOURCE_NOT_FOUND   = -5,
    ATINY_RESOURCE_NOT_ENOUGH  = -6,
    ATINY_CLIENT_UNREGISTERED  = -7,
    ATINY_SOCKET_CREATE_FAILED = -8,
    ATINY_ERR                  = -9
} atiny_error_e;

///< uptils now, we don't support the multi handle mode

typedef enum
{
    ATINY_BOOTSTRAP_FACTORY = 0,
    ATINY_BOOTSTRAP_CLIENT_INITIATED,
    ATINY_BOOTSTRAP_SEQUENCE
} atiny_bootstrap_type_e;

typedef struct
{
    char                   *binding;       /* support U and UQ bind mode */
    int                     life_time;      /* required option */
    unsigned int            storing_cnt;    /* storing count */
    atiny_bootstrap_type_e  bootstrap_mode; /* bootstrap mode  */
    int                     hold_off_time;  /* bootstrap hold off time for server initiated bootstrap */
} atiny_server_param_t;

typedef struct
{
    char           *server_ip;
    char           *server_port;
    char           *psk_id;
    char           *psk;
    unsigned short  psk_len;
} atiny_security_param_t;

typedef struct
{
    atiny_server_param_t    server_params;

    //both iot_server and bs_server have psk & pskID, index 0 for iot_server, and index 1 for bs_server
    atiny_security_param_t  security_params[2];

    void                   *userData;
} atiny_param_t;

typedef struct
{
    char *endpoint_name;
    char *manufacturer;
    char *dev_type;
} atiny_device_info_t;

typedef struct
{
    atiny_device_info_t device_info;
    atiny_param_t       tiny_param;
    oc_config_param_t   config_para;
    void               *agent_handle;
    void               *task_handle;
} oc_lwm2m_imp_agent_t;

static oc_lwm2m_imp_agent_t  *s_oc_lwm2m_agent = NULL;

#define SERVER_ID                           (123)
#define BINARY_APP_DATA_OBJECT_ID           19
#define BINARY_APP_DATA_OBJECT_INSTANCE_NUM 2
#define BINARY_APP_DATA_RES_ID              0
#define MSG_NEED_CONFIRMED                  1

#define APP_UP_CHANNEL_URI      "/19/0/0"
#define APP_DOWN_CHANNEL_URI    "/19/1/0"

typedef struct object_uri_list_t
{
    struct object_uri_list_t *next;
    uint16_t object_id;
} object_uri_list;

static object_uri_list *uri_list;

static int lwm2m_agent_receive(en_oc_lwm2m_msg_t type, char *msg, int len)
{
    if ((NULL != s_oc_lwm2m_agent) && (NULL != s_oc_lwm2m_agent->config_para.rcv_func))
    {
        s_oc_lwm2m_agent->config_para.rcv_func(s_oc_lwm2m_agent->config_para.usr_data, type, msg, len);
    }

    return 0;
}

static int agent_dealer_callback(int op, const char *uri, char *msg, int len)
{
    int ret = -1;
    LINK_LOG_DEBUG("uri: %s, op: %d\n", uri, op);

    if ((0 == strcmp(uri, APP_DOWN_CHANNEL_URI))
        || (0 == strcmp(uri, URI_TRIGER_SERVER_INITIATED_BS)))
    {
		switch (op)
		{
			case LWM2M_AL_OP_WRITE:
				ret = lwm2m_agent_receive(EN_OC_LWM2M_MSG_APPWRITE, msg, len);
				break;

			case LWM2M_AL_OP_EXCUTE:
				ret = lwm2m_agent_receive(EN_OC_LWM2M_MSG_APPEXECUTE, msg, len);
				break;

			case LWM2M_AL_OP_DISCOVER:
				ret = lwm2m_agent_receive(EN_OC_LWM2M_MSG_APPDISCOVER, msg, len);
				break;

			case LWM2M_AL_OP_SERVERREBS:
				ret = lwm2m_agent_receive(EN_OC_LWM2M_MSG_SERVERREBS, msg, len);
				break;

			default:
				break;
		}
    }
    return ret;
}


/*
 * modify date:   2018-06-20
 * description: in order to check the params for the bootstrap, expecialy for the mode and the ip/port
 * return:
 *              success: (int)ATINY_OK
 *              fail:    (int)ATINY_ARG_INVALID
 *
 */
static int atiny_check_bootstrap_init_param(atiny_param_t *atiny_params)
{
    if (NULL == atiny_params)
    {
        return (int)ATINY_ARG_INVALID;
    }

    if (ATINY_BOOTSTRAP_FACTORY == atiny_params->server_params.bootstrap_mode)
    {
        if ((NULL == atiny_params->security_params[0].server_ip) || (NULL == atiny_params->security_params[0].server_port))
        {
            ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: BOOTSTRAP_FACTORY mode's params is wrong, should have iot server ip/port");
            return (int)ATINY_ARG_INVALID;
        }
    }
    else if (ATINY_BOOTSTRAP_CLIENT_INITIATED == atiny_params->server_params.bootstrap_mode)
    {
        if ((NULL == atiny_params->security_params[1].server_ip) || (NULL == atiny_params->security_params[1].server_port))
        {
            ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: BOOTSTRAP_CLIENT_INITIATED mode's params is wrong, should have bootstrap server ip/port");
            return (int)ATINY_ARG_INVALID;
        }
    }
    else if (ATINY_BOOTSTRAP_SEQUENCE == atiny_params->server_params.bootstrap_mode)
    {
        return (int)ATINY_OK;
    }
    else
    {
        //it is ok? if the mode value is not 0,1,2, we all set it to 2 ?
        ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: BOOTSTRAP only have three mode, should been :0,1,2");
        return (int)ATINY_ARG_INVALID;
    }

    return (int)ATINY_OK;
}

static int atiny_check_psk_init_param(atiny_param_t *atiny_params)
{
    int i = 0;
    int psk_id_len = 0;
    int psk_len = 0;
    const int PSK_ID_LIMIT_LEN = 128;
    const int PSK_LIMIT_LEN = 64;
    int total_element = 0;

    if (NULL == atiny_params)
    {
        return (int)ATINY_ARG_INVALID;
    }

    //security_params have 2 element, we have 2 pair psk.
    total_element = (sizeof(atiny_params->security_params)) / (sizeof(atiny_params->security_params[0]));

    for (i = 0; i < total_element; i++)
    {
        //if there are null, we could run not in security mode
        if ((atiny_params->security_params[i].psk_id != NULL) && (atiny_params->security_params[i].psk != NULL))
        {
            psk_id_len = strlen(atiny_params->security_params[i].psk_id);
            psk_len = strlen(atiny_params->security_params[i].psk);

            //the limit of the len, please read RFC4279  or OMA-TS-LightweightM2M E.1.1
            if ((psk_id_len > PSK_ID_LIMIT_LEN) || (psk_len > PSK_LIMIT_LEN))
            {
                ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: psk_id len over 128 or psk len over 64");
                return (int)ATINY_ARG_INVALID;
            }
        }
    }

    return (int)ATINY_OK;
}

static int atiny_check_parameter(atiny_param_t *atiny_params,
                                 const atiny_device_info_t *device_info)
{
    if ((NULL == atiny_params) || (NULL == device_info))
    {
        ATINY_LOG(LOG_FATAL, "Parameter null");
        return (int)ATINY_ARG_INVALID;
    }

    if (NULL == device_info->endpoint_name)
    {
        ATINY_LOG(LOG_FATAL, "Endpoint name null");
        return (int)ATINY_ARG_INVALID;
    }

    if (NULL == device_info->manufacturer)
    {
        ATINY_LOG(LOG_FATAL, "Manufacturer name null");
        return (int)ATINY_ARG_INVALID;
    }

    if ((int)ATINY_OK != atiny_check_bootstrap_init_param(atiny_params))
    {
        ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: BOOTSTRAP's params are wrong");
        return (int)ATINY_ARG_INVALID;
    }

    //#ifdef LWM2M_BOOTSTRAP
    if ((int)ATINY_OK != atiny_check_psk_init_param(atiny_params))
    {
        ATINY_LOG(LOG_FATAL, "[bootstrap_tag]: psk params are wrong");
        return (int)ATINY_ARG_INVALID;
    }

    //#endif
    return (int)ATINY_OK;
}

static void uri_list_add(object_uri_list **head, object_uri_list *list)
{
    object_uri_list *temp;

    if (NULL == *head)
    {
        *head = list;
        (*head)->next = NULL;
    }
    else
    {
        temp = *head;

        while (temp)
        {
            if (NULL == temp->next)
            {
                temp->next = list;
                list->next = NULL;
            }

            temp = temp->next;
        }
    }
}


static int agent_add_security_object(void *handle, atiny_param_t *lwm2m_params)
{
    uint16_t instance_id = 0;
    const uint8_t INS_IOT_SERVER_FLAG = 0x01;
    const uint8_t INS_BS_SERVER_FLAG = 0x02;
    uint8_t  ins_flag = 0x00;
    uint8_t total_ins = 1;
    uint8_t security_params_index = 0;
    int i;
    int ret = (int) ATINY_ERR;
    object_uri_list *security_list = NULL;
    lwm2m_al_sec_obj_param_t security_object_param;

    if (NULL == lwm2m_params)
    {
        return (int)ATINY_ARG_INVALID;
    }

    security_object_param.server_id = SERVER_ID;
    security_object_param.hold_off_time = lwm2m_params->server_params.hold_off_time;

    switch (lwm2m_params->server_params.bootstrap_mode)
    {
        case ATINY_BOOTSTRAP_FACTORY:
            ins_flag |= INS_IOT_SERVER_FLAG;
            total_ins = 1;
            break;

        case ATINY_BOOTSTRAP_SEQUENCE:
            if ((lwm2m_params->security_params[0].server_ip != NULL) && (lwm2m_params->security_params[0].server_port != NULL))
            {
                ins_flag |= INS_IOT_SERVER_FLAG;
                ins_flag |= INS_BS_SERVER_FLAG;
                total_ins = 2;
            }
            else
            {
                ins_flag |= INS_BS_SERVER_FLAG;
                total_ins = 1;
            }

            break;

        case ATINY_BOOTSTRAP_CLIENT_INITIATED:
            ins_flag |= INS_BS_SERVER_FLAG;
            total_ins = 1;
            break;

        default:
            return -1;
    }

    //at most, have two instance. in fact
    for (i = 0; i < total_ins; i++)
    {
        if ((ins_flag & INS_IOT_SERVER_FLAG) && (ins_flag & INS_BS_SERVER_FLAG))
        {
            instance_id = i;
            security_object_param.is_bootstrap = ((i == 0) ? (false) : (true));
            security_params_index = i;
        }
        else
        {
            if (ins_flag & INS_IOT_SERVER_FLAG)
            {
                instance_id = 0;
                security_object_param.is_bootstrap = false;
                security_params_index = 0;
            }
            else  //if(ins_flag & INS_BS_SERVER_FLAG)  //even if not set INS_BS_SERVER_FLAG, still run in a certain process.
            {
                instance_id = 1;
                security_object_param.is_bootstrap = true;
                security_params_index = 1;
            }
        }

        security_object_param.server_ip = lwm2m_params->security_params[security_params_index].server_ip;
        security_object_param.server_port = lwm2m_params->security_params[security_params_index].server_port;
        security_object_param.psk_id = lwm2m_params->security_params[security_params_index].psk_id;
        security_object_param.psk = lwm2m_params->security_params[security_params_index].psk;
        security_object_param.psk_len = lwm2m_params->security_params[security_params_index].psk_len;
        ret = lwm2m_al_add_object(handle, (int)OBJ_SECURITY_ID, instance_id, 0, &security_object_param);

        if ((int) LWM2M_OK != ret)
        {
            (void)lwm2m_al_delete_object(handle, (int)OBJ_SECURITY_ID);
            return ret;
        }
    }//end for loop

    security_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == security_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_SECURITY_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    security_list->object_id = (int)OBJ_SECURITY_ID;
    uri_list_add(&uri_list, security_list);
    return 0;
}

static int agent_add_server_object(void *handle, atiny_param_t *lwm2m_params)
{
    uint16_t instance_id = 0;
    lwm2m_al_srv_obj_param_t server_object_param;
    object_uri_list *server_list = NULL;
    int ret = (int) ATINY_ERR;

    if (NULL == lwm2m_params)
    {
        return (int)ATINY_ARG_INVALID;
    }

    server_object_param.server_id = SERVER_ID;
    server_object_param.binding = lwm2m_params->server_params.binding;
    server_object_param.life_time = lwm2m_params->server_params.life_time;
    server_object_param.storing_cnt = lwm2m_params->server_params.storing_cnt;
    ret = lwm2m_al_add_object(handle, (int)OBJ_SERVER_ID, instance_id, 0, &server_object_param);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    server_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == server_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_SERVER_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    server_list->object_id = OBJ_SERVER_ID;
    uri_list_add(&uri_list, server_list);
    return 0;
}

static int agent_add_acc_ctrl_object(void *handle)
{
    uint16_t instance_id = 0;
    object_uri_list *acc_ctrl_list = NULL;
    int ret = (int) ATINY_ERR;
    ret = lwm2m_al_add_object(handle, (int)OBJ_ACCESS_CONTROL_ID, instance_id, 0, NULL);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    acc_ctrl_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == acc_ctrl_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_ACCESS_CONTROL_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    acc_ctrl_list->object_id = OBJ_ACCESS_CONTROL_ID;
    uri_list_add(&uri_list, acc_ctrl_list);
    return 0;
}

static int agent_add_device_object(void *handle)
{
    uint16_t instance_id = 0;
    object_uri_list *device_list = NULL;
    int ret = (int) ATINY_ERR;
    ret = lwm2m_al_add_object(handle, (int)OBJ_DEVICE_ID, instance_id, 0, NULL);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    device_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == device_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_DEVICE_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    device_list->object_id = OBJ_DEVICE_ID;
    uri_list_add(&uri_list, device_list);
    return 0;
}

static int agent_add_conn_m_object(void *handle)
{
    uint16_t instance_id = 0;
    object_uri_list *conn_m_list = NULL;
    int ret = (int) ATINY_ERR;
    ret = lwm2m_al_add_object(handle, (int)OBJ_CONNECTIVITY_MONITORING_ID, instance_id, 0, NULL);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    conn_m_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == conn_m_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_CONNECTIVITY_MONITORING_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    conn_m_list->object_id = OBJ_CONNECTIVITY_MONITORING_ID;
    uri_list_add(&uri_list, conn_m_list);
    return 0;
}

static int agent_add_firmware_object(void *handle)
{
#ifdef CONFIG_FEATURE_FOTA
    int ret = (int) ATINY_ERR;
    uint16_t instance_id = 0;
    object_uri_list *firmware_list = NULL;
    ret = lwm2m_al_add_object(handle, OBJ_FIRMWARE_UPDATE_ID, instance_id, 0, NULL);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    firmware_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == firmware_list)
    {
        lwm2m_al_delete_object(handle, OBJ_FIRMWARE_UPDATE_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    firmware_list->object_id = OBJ_FIRMWARE_UPDATE_ID;
    uri_list_add(&uri_list, firmware_list);
#endif
    return 0;
}

static int agent_add_location_object(void *handle)
{
    uint16_t instance_id = 0;
    object_uri_list *location_list = NULL;
    int ret = (int) ATINY_ERR;
    ret = lwm2m_al_add_object(handle,(int)OBJ_LOCATION_ID, instance_id, 0, NULL);

    if ((int) LWM2M_OK != ret)
    {
        return ret;
    }

    location_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == location_list)
    {
        (void)lwm2m_al_delete_object(handle, (int)OBJ_LOCATION_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    location_list->object_id = OBJ_LOCATION_ID;
    uri_list_add(&uri_list, location_list);
    return 0;
}

static int agent_add_binary_app_data_object(void *handle, unsigned int *storing_cnt)
{
    uint16_t instance_id = 0;
    int i;
    object_uri_list *binary_app_list = NULL;
    int ret = (int) ATINY_ERR;

    if (NULL == storing_cnt)
    {
        return (int)ATINY_ARG_INVALID;
    }

    // /19/0/0, /19/1/0
    for (i = 0; i < BINARY_APP_DATA_OBJECT_INSTANCE_NUM; ++i)
    {
        instance_id = i;
        ret = lwm2m_al_add_object(handle, BINARY_APP_DATA_OBJECT_ID, instance_id, 0, storing_cnt);

        if ((int) LWM2M_OK != ret)
        {
            return ret;
        }
    }

    binary_app_list = osal_malloc(sizeof(object_uri_list));

    if (NULL == binary_app_list)
    {
        (void)lwm2m_al_delete_object(handle, BINARY_APP_DATA_OBJECT_ID);
        return (int) ATINY_MALLOC_FAILED;
    }

    binary_app_list->object_id = BINARY_APP_DATA_OBJECT_ID;
    uri_list_add(&uri_list, binary_app_list);
    return 0;
}

static int agent_add_objects(void *handle, atiny_param_t *lwm2m_params)
{
    int ret = (int) ATINY_ERR;
    ret = agent_add_security_object(handle, lwm2m_params);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_server_object(handle, lwm2m_params);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_acc_ctrl_object(handle);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_device_object(handle);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_conn_m_object(handle);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_firmware_object(handle);

    if (0 != ret)
    {
        return ret;
    }

    ret = agent_add_location_object(handle);

    if (0 != ret)
    {
        return ret;
    }

    return agent_add_binary_app_data_object(handle, &(lwm2m_params->server_params.storing_cnt));
}

static int agent_delete_object(void *handle)
{
    object_uri_list *temp = uri_list;
    object_uri_list *node = NULL;
    int ret = (int) ATINY_ERR;

    while (temp != NULL)
    {
        node = temp;
        temp = temp->next;
        ret = lwm2m_al_delete_object(handle, node->object_id);

        if ((int) LWM2M_OK != ret)
        {
            osal_free(node);
            return ret;
        }

        osal_free(node);
    }

    uri_list = NULL;
    return 0;
}

static int __agent_config(oc_config_param_t *param)
{
    int ret = (int ) en_oc_lwm2m_err_system;
    oc_lwm2m_imp_agent_t  *agent = NULL;

    if (NULL != s_oc_lwm2m_agent)
    {
        ret = (int ) en_oc_lwm2m_err_configured;
        return ret;
    }

    if (NULL == param)
    {
        ret =(int ) en_oc_lwm2m_err_parafmt;
        return ret;
    }

    agent = osal_zalloc(sizeof(oc_lwm2m_imp_agent_t));
    if (NULL == agent)
    {
        ret = (int ) en_oc_lwm2m_err_sysmem;
        return ret;
    }

    agent->config_para = *param;
    ///< initialize the param that agent tiny need
    atiny_param_t *atiny_params;
    atiny_security_param_t  *iot_security_param = NULL;
    atiny_security_param_t  *bs_security_param = NULL;
    atiny_device_info_t *device_info = &agent->device_info;
    device_info->endpoint_name = agent->config_para.app_server.ep_id;
    device_info->dev_type = "Lwm2mFota";
    device_info->manufacturer = "Agent_Tiny";
    atiny_params = &agent->tiny_param;
    atiny_params->server_params.binding = "UQ";
    atiny_params->server_params.life_time = 2000;
    atiny_params->server_params.storing_cnt = 5;
    atiny_params->server_params.bootstrap_mode = param->boot_mode;
    atiny_params->server_params.hold_off_time = 10;
    atiny_params->userData = param->usr_data;
    //pay attention: index 0 for iot server, index 1 for bootstrap server.
    iot_security_param = &(atiny_params->security_params[0]);
    bs_security_param = &(atiny_params->security_params[1]);
    iot_security_param->server_ip = agent->config_para.app_server.address;
    iot_security_param->server_port = agent->config_para.app_server.port;
    iot_security_param->psk_id = agent->config_para.app_server.psk_id;
    iot_security_param->psk = agent->config_para.app_server.psk;
    iot_security_param->psk_len = agent->config_para.app_server.psk_len;
    bs_security_param->server_ip = agent->config_para.boot_server.address;
    bs_security_param->server_port = agent->config_para.boot_server.port;
    bs_security_param->psk_id = agent->config_para.boot_server.psk_id;
    bs_security_param->psk = agent->config_para.boot_server.psk;
    bs_security_param->psk_len = agent->config_para.boot_server.psk_len;
    ret = atiny_check_parameter(atiny_params, device_info);

    if ((int)ATINY_OK != ret)
    {
        osal_free(agent);

        ret = (int ) en_oc_lwm2m_err_parafmt;
        return ret;
    }

    //TODO: add objects
    lwm2m_al_init_param_t init_param;
    init_param.endpoint_name =  device_info->endpoint_name;
    init_param.dealer = agent_dealer_callback;
    init_param.bootstrap_type = (int)(param->boot_mode);
    ret = lwm2m_al_config(&(agent->agent_handle), &init_param);

    if ((int)ATINY_OK != ret)
    {
        osal_free(agent);
        ret = (int ) en_oc_lwm2m_err_parafmt;
        return ret;
    }

    ret = agent_add_objects(agent->agent_handle, atiny_params);

    if (0 != ret)
    {
        osal_free(agent);
        ret = (int ) en_oc_lwm2m_err_system;
        return ret;
    }

    ret = lwm2m_al_connect(agent->agent_handle);

    if ((int)ATINY_OK != ret)
    {
        osal_free(agent);
        ret = (int ) en_oc_lwm2m_err_network;
        return ret;
    }

    s_oc_lwm2m_agent = agent;
    ret = (int ) en_oc_lwm2m_err_ok;

    return ret;
}

static int __agent_deconfig(void)
{
    int ret;
    oc_lwm2m_imp_agent_t  *handle = s_oc_lwm2m_agent;

    if (NULL == handle)
    {
        ret = (int ) en_oc_lwm2m_err_noconfigured;
        return ret;
    }

    (void)lwm2m_al_disconnect(handle->agent_handle);
    (void)agent_delete_object(handle->agent_handle);
    (void)lwm2m_al_deconfig(handle->agent_handle);
    osal_free(handle);
    s_oc_lwm2m_agent = NULL;

    ret = (int ) en_oc_lwm2m_err_ok;
    return ret;
}

static int __agent_report(char *msg, int len, int timeout)
{
    int ret = (int ) en_oc_lwm2m_err_noconfigured;
    lwm2m_al_send_param_t send_param;

    if(NULL != s_oc_lwm2m_agent)
    {
        send_param.data = (uint8_t *)msg;
        send_param.length = len;
        send_param.mode = MSG_NEED_CONFIRMED;
        send_param.object_id = (int) OBJ_APP_DATA_ID;
        send_param.object_instance_id = 0;
        send_param.resource_id = BINARY_APP_DATA_RES_ID;

        if(0 == lwm2m_al_send(s_oc_lwm2m_agent,&send_param))
        {
            ret = (int ) en_oc_lwm2m_err_ok;
        }
        else
        {
            ret  = (int ) en_oc_lwm2m_err_network;
        }
    }

    return ret;

}

const oc_lwm2m_opt_t  s_oc_lwm2m_agent_opt = \
{
    .config = __agent_config,
    .deconfig = __agent_deconfig,
    .report = __agent_report,
};

int oc_lwm2m_imp_init()
{
    int ret = -1;
    ret = oc_lwm2m_register("oc_lwm2m_agent", &s_oc_lwm2m_agent_opt);
    return ret;
}
