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

////< this file used to package the data for the profile and you must make sure the data format is right
#include <oc_mqtt_profile.h>
#include <oc_mqtt_profile_package.h>

#include <cJSON.h>

///< format the report data to json string mode
static cJSON  *profile_fmtvalue(oc_mqtt_profile_kv_t  *kv)
{
    cJSON  *ret = NULL;
    switch (kv->type)
    {
        case EN_OC_MQTT_PROFILE_VALUE_INT:
            ret = cJSON_CreateNumber((double)(*(int *)kv->value));
            break;
        case EN_OC_MQTT_PROFILE_VALUE_LONG:
            ret = cJSON_CreateNumber((double)(*(long *)kv->value));
            break;
        case EN_OC_MQTT_PROFILE_VALUE_FLOAT:
            ret = cJSON_CreateNumber((double)(*(float *)kv->value));
            break;
        case EN_OC_MQTT_PROFILE_VALUE_DOUBLE:
            ret = cJSON_CreateNumber((*(double *)kv->value));
            break;
        case EN_OC_MQTT_PROFILE_VALUE_STRING:
            ret = cJSON_CreateString((const char *)kv->value);
            break;
        default:
            break;
    }

    return ret;
}



#define CN_OC_MQTT_PROFILE_MSGUP_KEY_DEVICEID    "object_device_id"
#define CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGNAME     "name"
#define CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGID       "id"
#define CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGCONTENT  "content"
char *oc_mqtt_profile_package_msgup(oc_mqtt_profile_msgup_t *payload)
{

    char *ret = NULL;
    cJSON *root = NULL;
    cJSON *device_id = NULL;
    cJSON *msg_name;
    cJSON *msg_id;
    cJSON *msg_conntent;

    root = cJSON_CreateObject();
    if(NULL == root)
    {
        goto EXIT_MEM;
    }

    if(NULL != payload->device_id)
    {
        device_id = cJSON_CreateString(payload->device_id);
        if(NULL == device_id)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_MSGUP_KEY_DEVICEID,device_id);
    }

    if(NULL != payload->name)
    {
        msg_name = cJSON_CreateString(payload->name);
        if(NULL == msg_name)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGNAME,msg_name);
    }

    if(NULL != payload->id)
    {
        msg_id = cJSON_CreateString(payload->id);
        if(NULL == msg_id)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGID,msg_id);
    }

    msg_conntent = cJSON_CreateString(payload->msg);
    if(NULL == msg_conntent)
    {
        goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_MSGUP_KEY_MSGCONTENT,msg_conntent);

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }
    return ret;
}


static cJSON *make_kvs(oc_mqtt_profile_kv_t *kvlst)
{

    cJSON *root;
    cJSON *kv;
    oc_mqtt_profile_kv_t  *kv_info;

    ///< build a root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< add all the property to the properties
    kv_info = kvlst;
    while(NULL != kv_info)
    {
        kv = profile_fmtvalue( kv_info);
        if(NULL == kv)
        {
            goto EXIT_MEM;
        }

        cJSON_AddItemToObject(root,kv_info->key,kv);
        kv_info = kv_info->nxt;
    }

    ///< OK, now we return it
    return root;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
       root = NULL;
    }
    return root;


}


#define CN_OC_MQTT_PROFILE_SERVICE_KEY_SERVICEID     "service_id"
#define CN_OC_MQTT_PROFILE_SERVICE_KEY_PROPERTIES    "properties"
#define CN_OC_MQTT_PROFILE_SERVICE_KEY_EVENTTIME     "event_time"


static cJSON *make_service(oc_mqtt_profile_service_t *service_info)
{

    cJSON *root;
    cJSON *service_id;
    cJSON *properties;
    cJSON *event_time;

    ///< build a root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< add the service_id node to the root node
    service_id = cJSON_CreateString(service_info->service_id);
    if(NULL == service_id)
    {
       goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SERVICE_KEY_SERVICEID,service_id);

    ///< add the properties node to the root
    properties = make_kvs(service_info->service_property);
    if(NULL == properties)
    {
       goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SERVICE_KEY_PROPERTIES,properties);

    ///< add the event time (optional) to the root
    if(NULL != service_info->event_time)
    {
        event_time = cJSON_CreateString(service_info->event_time);
        if(NULL == event_time)
        {
           goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SERVICE_KEY_EVENTTIME,event_time);
    }

    ///< OK, now we return it
    return root;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
       root = NULL;
    }
    return root;
}

#define CN_OC_MQTT_PROFILE_SERVICES_KEY        "services"
static cJSON *make_services(oc_mqtt_profile_service_t *service_info)
{
    cJSON *services = NULL;
    cJSON *service;
    oc_mqtt_profile_service_t  *service_tmp;

    ///< create the services array node
    services = cJSON_CreateArray();
    if(NULL == services)
    {
       goto EXIT_MEM;
    }

    service_tmp = service_info;
    while(NULL != service_tmp)
    {
        service = make_service(service_tmp);
        if(NULL == service)
        {
            goto EXIT_MEM;
        }

        cJSON_AddItemToArray(services,service);
        service_tmp = service_tmp->nxt;
    }

    ///< now we return the services
    return services;

EXIT_MEM:
    if(NULL != services)
    {
       cJSON_Delete(services);
       services = NULL;
    }
    return services;
}

char *oc_mqtt_profile_package_propertyreport(oc_mqtt_profile_service_t *payload)
{
    char *ret = NULL;
    cJSON *root;
    cJSON *services;

    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< create the services array node to the root
    services = make_services(payload);
    if(NULL == services)
    {
        goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SERVICES_KEY,services);

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }
    return ret;
}

#define CN_OC_MQTT_PROFILE_DEVICES_KEY_DEVICES        "devices"
#define CN_OC_MQTT_PROFILE_DEVICES_KEY_DEVICEID       "device_id"

char *oc_mqtt_profile_package_gwpropertyreport(oc_mqtt_profile_device_t *payload)
{
    char *ret = NULL;
    cJSON *root;
    cJSON *services;
    cJSON *devices;
    cJSON *device;
    cJSON *device_id;

    oc_mqtt_profile_device_t *device_info;

    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< create the devices node and add it to root
    devices = cJSON_CreateArray();
    if(NULL == devices)
    {
        goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_DEVICES_KEY_DEVICES,devices);

    ///< loop all the devices and add it to devices
    device_info = payload;
    while(NULL != device_info)
    {
        device = cJSON_CreateObject();
        if(NULL == device)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToArray(devices,device);

        device_id = cJSON_CreateString(device_info->subdevice_id);
        if(NULL == device_id)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(device,CN_OC_MQTT_PROFILE_DEVICES_KEY_DEVICEID,device_id);

        services = make_services(device_info->subdevice_property);
        if(NULL == services)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(device,CN_OC_MQTT_PROFILE_SERVICES_KEY,services);

        device_info = device_info->nxt;
    }

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }
    return ret;
}



#define CN_OC_MQTT_PROFILE_SETPROPERTYRESP_KEY_RETCODE        "result_code"
#define CN_OC_MQTT_PROFILE_SETPROPERTYRESP_KEY_RETDESC        "result_desc"
char *oc_mqtt_profile_package_propertysetresp(oc_mqtt_profile_propertysetresp_t *payload)
{

    char *ret = NULL;
    cJSON *root;
    cJSON *ret_code;
    cJSON *ret_desc;

    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< create retcode and retdesc and add it to the root
    if(NULL != payload)
    {
        ret_code = cJSON_CreateNumber(payload->ret_code);
        if(NULL == ret_code)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SETPROPERTYRESP_KEY_RETCODE,ret_code);

        if(NULL != payload->ret_description)
        {
            ret_desc = cJSON_CreateString(payload->ret_description);
            if(NULL == ret_desc)
            {
                goto EXIT_MEM;
            }
            cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SETPROPERTYRESP_KEY_RETDESC,ret_desc);
        }

    }
    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }
    return ret;

}

char *oc_mqtt_profile_package_propertygetresp(oc_mqtt_profile_propertygetresp_t *payload)
{

    char *ret = NULL;
    cJSON *root;
    cJSON *services;

    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< create the services array node to the root
    services = make_services(payload->services);
    if(NULL == services)
    {
        goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SERVICES_KEY,services);

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }
    return ret;

}

#define CN_OC_MQTT_PROFILE_CMDRESP_KEY_RETCODE        "result_code"
#define CN_OC_MQTT_PROFILE_CMDRESP_KEY_RESPNAME       "response_name"
#define CN_OC_MQTT_PROFILE_CMDRESP_KEY_PARAS          "paras"
char *oc_mqtt_profile_package_cmdresp(oc_mqtt_profile_cmdresp_t *payload)
{
    char *ret = NULL;
    cJSON *root;
    cJSON *ret_code;
    cJSON *ret_name;
    cJSON *paras;


    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }

    ///< create retcode and retdesc and add it to the root
    ret_code = cJSON_CreateNumber(payload->ret_code);
    if(NULL == ret_code)
    {
        goto EXIT_MEM;
    }
    cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_CMDRESP_KEY_RETCODE,ret_code);

    if(NULL != payload->ret_name)
    {
        ret_name = cJSON_CreateString(payload->ret_name);
        if(NULL == ret_name)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_SETPROPERTYRESP_KEY_RETDESC,ret_name);
    }

    if(NULL != payload->paras)
    {
        paras = make_kvs(payload->paras);
        if(NULL == paras)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_CMDRESP_KEY_PARAS,paras);
    }

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }

    return ret;

}



#define CN_OC_MQTT_PROFILE_GETSHADOW_SERVICEID        "service_id"
#define CN_OC_MQTT_PROFILE_GETSHADOW_OBJECTDEVICEID   "object_device_id"
char *oc_mqtt_profile_package_shadowget(oc_mqtt_profile_shadowget_t *payload)
{
    char *ret = NULL;
    cJSON *root = NULL;
    cJSON *object_device_id = NULL;
    cJSON *service_id = NULL;

    ///< create the root node
    root = cJSON_CreateObject();
    if(NULL == root)
    {
       goto EXIT_MEM;
    }
    ///< create retcode and retdesc and add it to the root
    if(NULL != payload->object_device_id)
    {
        object_device_id = cJSON_CreateString(payload->object_device_id);
        if(NULL == object_device_id)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_GETSHADOW_OBJECTDEVICEID,object_device_id);
    }

    if(NULL != payload->service_id)
    {
        service_id = cJSON_CreateString(payload->object_device_id);
        if(NULL == service_id)
        {
            goto EXIT_MEM;
        }
        cJSON_AddItemToObjectCS(root,CN_OC_MQTT_PROFILE_GETSHADOW_SERVICEID,service_id);
    }

    ///< OK, now we make it to a buffer
    ret = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return ret;

EXIT_MEM:
    if(NULL != root)
    {
       cJSON_Delete(root);
    }

    return ret;

}






