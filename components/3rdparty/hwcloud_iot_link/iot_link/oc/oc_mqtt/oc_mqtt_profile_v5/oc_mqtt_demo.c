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
#include <stdio.h>
#include <string.h>

#include <iot_link_config.h>

#include <hwqueue.h>
#include <oc_mqtt_al.h>
#include <oc_mqtt_profile.h>

///< and i think the platform will make the timeout much longer and fix this problem
///< for the MCU has weak compute ability, and the new CERT FILE of platform is very big, so should not use tls for the MCUS
///< 1.设备接入服务重新更新了证书以及加密套件，椭圆加密算法算法需要大算力去链接服务器，因此对月MCU而言，请选择非加密方案
///< 2.设备发放平台目前本身在和设备接入做对接，还不ready.

//#define CN_SERVER_IPV4       "iot-mqtts.cn-north-4.myhuaweicloud.com"
#define CN_SERVER_IPV4       "121.36.42.100"

#if  CONFIG_OC_MQTTV5_DEMO_TLS

#define CN_SERVER_PORT       "8883"
#define CN_SECURITY_TYPE     EN_DTLS_AL_SECURITY_TYPE_CERT

#else

#define CN_SERVER_PORT       "1883"
#define CN_SECURITY_TYPE     EN_DTLS_AL_SECURITY_TYPE_NONE

#endif
///< server key
static const char s_server_ca[] =
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


#ifndef CONFIG_OCMQTTV5_DEMO_DEVICEID
#define CONFIG_OCMQTTV5_DEMO_DEVICEID  "5ec3f516cce62b02c56524a9_ca002"
#endif

#ifndef CONFIG_OCMQTTV5_DEMO_DEVPWD
#define CONFIG_OCMQTTV5_DEMO_DEVPWD     "f62fcf47d62c4ed18913"
#endif

#ifndef CONFIG_OCMQTTV5_DEMO_REPORTCYCLE
#define CONFIG_OCMQTTV5_DEMO_REPORTCYCLE   1000
#endif


#define CN_EP_DEVICEID        CONFIG_OCMQTTV5_DEMO_DEVICEID
#define CN_EP_PASSWD          CONFIG_OCMQTTV5_DEMO_DEVPWD

///< the client use the cert mode  SHA-256
//72DC0E75D88CEC38A025E9C48C79D222F608B039D080BCEFC0007DAD1AFFAD00
//#define CN_EP_DEVICEID         "5d0c76788a48f95ac41bcb9c_ca002"

#define CN_BOOT_MODE            0
#define CN_LIFE_TIME            60                         ///< the platform need more
//if your command is very fast,please use a queue here--TODO
static queue_t                   *s_queue_rcvmsg = NULL;   ///< this is used to cached the message
static oc_mqtt_profile_service_t  s_device_service;

///< two way mqtt mode
static const char s_client_ca[] = \
"-----BEGIN CERTIFICATE-----\r\n"
"MIICuDCCAaACCQDAnCoP3W+otTANBgkqhkiG9w0BAQsFADAdMQswCQYDVQQGEwJD\r\n"
"QTEOMAwGA1UEAwwFTVkgQ0EwHhcNMjAwMjE3MTEyNTA2WhcNMjEwMjExMTEyNTA2\r\n"
"WjAfMQswCQYDVQQGEwJDTjEQMA4GA1UEAwwHQ0xJRU5UMjCCASIwDQYJKoZIhvcN\r\n"
"AQEBBQADggEPADCCAQoCggEBALKOOfeq1QQnwLNsMboqr47ClO24sTd6oLiSjGYe\r\n"
"zb7IECnjiEg+sILEH5avi6uKdCR8QZHskIWdQbNqi2h0E01MTxuneTCnFaAdYh2z\r\n"
"B8n4IUsGr1gyCayfKCQG8ElDElBkB2JMce/IEuxJvnFdhXy6c9zhj8iU+fusD9hm\r\n"
"jvx34zd6Sn2uRl8wdI89pVwkESKyx6J5za/dBWCS0hxvOtDEY2gJA9av8BNYjTxQ\r\n"
"tRlwnxGzgaza8aA9LMbnRmv1bML98w4NgNHkVGUtw1eQso0unHnyEF1WhqEu0pLk\r\n"
"BJQbdO4s4ajQ1rOr7niVnCT99KtzJuWm3oymNdDT6BHsnn0CAwEAATANBgkqhkiG\r\n"
"9w0BAQsFAAOCAQEAPayFtS8du8D+mPdRU96vFqVpDx6oksGhrUIO+3GZ4ruuHjtf\r\n"
"A764y6zD1/LxQVw15xN44G+AqUwEi/BZszQ+5rSitwqoZFciKMblaqd0ZJSG6G2d\r\n"
"Cqyl87cTL6Tlgpa5cBka4ksaMs2OVU9x1aaNnejrTbX2PvZO7o/pVVimQE8Yh+1J\r\n"
"k2D26hg9UoWN4Z3/9LdGC3y4dsmtuQS+Cye61ZfHtT3/XjTRjl9/c+xKtVsQpE6g\r\n"
"dpaGVxWpFUCpGe4POrNHjOOAXaFiCHP7o9Kab1UnxuFVKHCtNT9wdJ7v8puCliwB\r\n"
"t40h9oegMyUYL/VG+14wOYgEPuCeGqqilht+4w==\r\n"
"-----END CERTIFICATE-----\r\n";
static const char s_client_pk[]= \
"-----BEGIN PRIVATE KEY-----\r\n"
"MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQCyjjn3qtUEJ8Cz\r\n"
"bDG6Kq+OwpTtuLE3eqC4koxmHs2+yBAp44hIPrCCxB+Wr4urinQkfEGR7JCFnUGz\r\n"
"aotodBNNTE8bp3kwpxWgHWIdswfJ+CFLBq9YMgmsnygkBvBJQxJQZAdiTHHvyBLs\r\n"
"Sb5xXYV8unPc4Y/IlPn7rA/YZo78d+M3ekp9rkZfMHSPPaVcJBEisseiec2v3QVg\r\n"
"ktIcbzrQxGNoCQPWr/ATWI08ULUZcJ8Rs4Gs2vGgPSzG50Zr9WzC/fMODYDR5FRl\r\n"
"LcNXkLKNLpx58hBdVoahLtKS5ASUG3TuLOGo0Nazq+54lZwk/fSrcyblpt6MpjXQ\r\n"
"0+gR7J59AgMBAAECggEAFbjx2myhD6laazmdbx2kUATiI22Vub8kcG/7vqy+sRgb\r\n"
"x0zUFp3x0WbUxPtETbFBYfLv8zXJe0ffZ1lt7l44vu2qrh2Yw89/9QO+HQjbyLl0\r\n"
"K3F7wYoM3UBbnM5vSypqvvb8YvwT3G0FyFNMZPRQuhTg5Z1XZbqiEvki0Fvhx1sG\r\n"
"bksCKK85dPaH/7kXxMTPZ67/2Z3TlwUERo1YSPRnrQXGnDowudLqQjn8ptiPfO39\r\n"
"bIMQhM/HI1bTw4F5EevL7sS4rcnhpmQNU6ZeINPvYuel+hP36uPwTHMm1hkZbMgP\r\n"
"a69Yk8/meENffl9fQ+T8woYMGgKq0DM+O5ip7QzrLQKBgQDdvwI/9npuwpYkdjWT\r\n"
"tLj5BKFNINjn+TjyvN1QQmOhXqzTy1y9HVm7EYh1l0H5PY/WgYadBWNYabgNSIe0\r\n"
"vxl7tdDxDX4DBQqDIIEY45sPa3glq6flCgtPzkZxcYTvZpqmdX8/iMYGXHpdOMdm\r\n"
"S8jngobFDEgLxFS1lLLs+LtTTwKBgQDOIz08d2zMRX5AW0SkQ+VbdwcO7G5qlTJV\r\n"
"42Rf51Dmr0as/bX5eIWAAfcsEi/kG2e5Ozupe4BVZXarw7AL1bzE4mLvfcwZEUiJ\r\n"
"Qj56H6QTOiVm/DTZdBz415z60zjCui+59luev6txZBL51ZhoifzfdAfxd8ztucV+\r\n"
"mj3kytIucwKBgBSdporl0norsyPOrap+2dek+44dKK1geU/wCS9mDLc7AxxpwsR+\r\n"
"TxJaTfKIzoRqmc3amvZMQvE8WvU5Mgy225qpy7QtifKj7FdGlVoIBymG11PBQsnD\r\n"
"hku0JM51PGO5iVVChUMV5zs+K84w8jDriNElTHxTaPtXFH0RRxVLBrd3AoGAIYX1\r\n"
"lXnOhcHfcFPna9dm22MWEMU+h7LPxsv+LOKPc5SZp9Ry3alN/K1VJyOmCjCyw5rw\r\n"
"bvWYv0qK7BAc9y/BTTuL32rT4FfBNiFBy9aNdlsEbiUh6yNI+ucFrnzfRDvHOzTn\r\n"
"XX/KP9yIgXzNFmMqbqSODiTvfNGzXo1y91xMpiUCgYAfO+Xb5msOMABiBNGD85qr\r\n"
"C+0xpuWoPe4pB5ccgniv1zhPlUJ+8l1vWz/ZWnH/6oVxGGrq5xLtoBgFWM4uSseI\r\n"
"Je0fSqZp0XAbaFI7wkEV/uP6VMjjFT5TfJz4idgI+EaE72va2jbFBgg1MyfR3gx4\r\n"
"deaXc4ZpE64iV+eAtZ8VVQ==\r\n"
"-----END PRIVATE KEY-----\r\n";
static const char *s_client_pk_pwd = "123456";

//use this function to push all the message to the buffer
static int app_msg_deal(oc_mqtt_profile_msgrcv_t *msg)
{
    int    ret = -1;
    char  *buf;
    int    buflen;
    int    datalen = 0;
    oc_mqtt_profile_msgrcv_t *demo_msg;

    ///< clone the message
    buflen = sizeof(oc_mqtt_profile_msgrcv_t) + msg->msg_len + 1;///< we copy with '\0' endings
    if(NULL != msg->request_id)
    {
        buflen += strlen(msg->request_id) +1; ///< ending with '\0'
    }

    buf = osal_malloc(buflen);
    if(NULL != buf)
    {
        demo_msg = (oc_mqtt_profile_msgrcv_t *)(uintptr_t)buf;
        buf += sizeof(oc_mqtt_profile_msgrcv_t);
        ///< copy the message and push it to the queue
        demo_msg->type = msg->type;

        if(NULL != msg->request_id)
        {
            demo_msg->request_id = buf;
            datalen = strlen(msg->request_id);
            (void) memcpy(buf,msg->request_id,datalen);
            buf[datalen] = '\0';
            buf += (datalen+1);
        }
        else
        {
            demo_msg->request_id = NULL;
        }

        demo_msg->msg = buf;
        demo_msg->msg_len = msg->msg_len;
        datalen = msg->msg_len;
        (void) memcpy(buf,msg->msg,datalen);
        buf[datalen] = '\0';

        (void) printf("RCVMSG:type:%d reuqestID:%s payloadlen:%d payload:%s\n\r",\
                (int) demo_msg->type,demo_msg->request_id==NULL?"NULL":demo_msg->request_id,\
                demo_msg->msg_len,(char *)demo_msg->msg);

        ret = queue_push(s_queue_rcvmsg,demo_msg,10);
        if(ret != 0)
        {
            osal_free(demo_msg);
        }
    }

    return ret;
}

///< now we deal the message here
static int  oc_cmd_normal(oc_mqtt_profile_msgrcv_t *demo_msg)
{
    static int value = 0;
    oc_mqtt_profile_cmdresp_t  cmdresp;
    oc_mqtt_profile_propertysetresp_t propertysetresp;
    oc_mqtt_profile_propertygetresp_t propertygetresp;

    switch(demo_msg->type)
    {
        case EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_MSGDOWN:
            ///< add your own deal here
            break;
        case EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_COMMANDS:
            ///< add your own deal here

            ///< do the response
            cmdresp.paras = NULL;
            cmdresp.request_id = demo_msg->request_id;
            cmdresp.ret_code = 0;
            cmdresp.ret_name = NULL;
            (void)oc_mqtt_profile_cmdresp(NULL,&cmdresp);
            break;

        case EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_PROPERTYSET:
            ///< add your own deal here

            ///< do the response
            propertysetresp.request_id = demo_msg->request_id;
            propertysetresp.ret_code = 0;
            propertysetresp.ret_description = NULL;
            (void)oc_mqtt_profile_propertysetresp(NULL,&propertysetresp);
            break;

        case  EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_PROPERTYGET:
            ///< add your own deal here

            ///< do the response
            value  = (value+1)%100;
            s_device_service.service_property->key = "radioValue";
            s_device_service.service_property->value = &value;
            s_device_service.service_property->type = EN_OC_MQTT_PROFILE_VALUE_INT;

            propertygetresp.request_id = demo_msg->request_id;
            propertygetresp.services = &s_device_service;
            (void)oc_mqtt_profile_propertygetresp(NULL,&propertygetresp);
            break;
        case EN_OC_MQTT_PROFILE_MSG_TYPE_DOWN_EVENT:
            break;

        default:
            break;

    }
    return 0;
}



static int demo_usersub_topic(void)
{
    int ret1;
    int ret2;
    int ret;
    char *topic;
    topic = "$oc/devices/"CN_EP_DEVICEID"/user/demo_sub1";
    ret1 = oc_mqtt_subscribe(topic, 0);

    topic = "$oc/devices/"CN_EP_DEVICEID"/user/demo_sub2";
    ret2 = oc_mqtt_subscribe(topic, 0);
    ret = ret1>ret2?ret1:ret2;
    return ret;
}

static int demo_userunsub_topic(void)
{
    int ret;
    int ret1;
    int ret2;
    char *topic;
    topic = "$oc/devices/"CN_EP_DEVICEID"/user/demo_sub1";
    ret1 = oc_mqtt_unsubscribe(topic);

    topic = "$oc/devices/"CN_EP_DEVICEID"/user/demo_sub2";
    ret2 = oc_mqtt_unsubscribe(topic);

    ret = ret1>ret2?ret1:ret2;
    return ret;
}

static int demo_userpub(void)
{
    int ret;
    char *topic;
    topic = "$oc/devices/"CN_EP_DEVICEID"/user/demo_pub";
    ret = oc_mqtt_publish(topic,(uint8_t *) "hello world",strlen("hello world"),1);
    return ret;
}

static int demo_msgup_shortdata(void)   ///< big data test
{
    int ret = (int)en_oc_mqtt_err_ok;
    oc_mqtt_profile_msgup_t msgup;

    msgup.device_id = CN_EP_DEVICEID;
    msgup.id = "54321";
    msgup.name = "MSGUP";
    msgup.msg = (void *)"Hello, new world";
    msgup.msg_len = strlen(msgup.msg);
    ret = oc_mqtt_profile_msgup(NULL,&msgup);
    return ret;
}

static int demo_msgup_longdata(void)   ///< big data test
{
    int ret = (int)en_oc_mqtt_err_ok;
    oc_mqtt_profile_msgup_t msgup;

    msgup.device_id = CN_EP_DEVICEID;
    msgup.id = "12345";
    msgup.name = "MSGUP";
    msgup.msg = (void *)s_client_pk;
    msgup.msg_len = sizeof(s_client_pk);
    ret = oc_mqtt_profile_msgup(NULL,&msgup);
    return ret;
}

static int demo_propertireport(void)
{
    int ret;
    static int value = 1;

    value++;
    s_device_service.service_property->key = "radioValue";
    s_device_service.service_property->value = &value;
    s_device_service.service_property->type = EN_OC_MQTT_PROFILE_VALUE_INT;
    ret = oc_mqtt_profile_propertyreport(NULL,&s_device_service);

    return ret;
}

static int demo_pubdefault(void)
{
    int ret ;
    const char *data = "{\"services\":[{\"service_id\":\"DeviceStatus\",\"properties\":{\"radioValue\":2}}]}";
    ret = oc_mqtt_publish(NULL,(uint8_t *)data, strlen(data),0);
    return ret;
}

static int demo_getshadow(void)
{
    int ret;
    oc_mqtt_profile_shadowget_t  payload;
    payload.object_device_id = NULL;
    payload.request_id = "123456789";
    payload.service_id = NULL;

    ret = oc_mqtt_profile_getshadow(NULL,&payload);
    return ret;
}

static int demo_reportversion(void)
{
    int ret;
    char *topic = "$oc/devices/"CN_EP_DEVICEID"/sys/events/up";
    char *data = "{ \"services\": [{ \"service_id\": \"$ota\", \"event_type\": \"version_report\", \"paras\": { \"sw_version\":\"v1.0\",\"fw_version\":\"v1.0\" } }]}";
    ret = oc_mqtt_publish(topic,(uint8_t *)data, strlen(data),0);

    return ret;
}


typedef int (*fn_ocmqttv5_demofunc)(void);
typedef struct
{
    const char          *name;
    fn_ocmqttv5_demofunc func;
    int                  failtimes;
}ocmqttv5_democase_t;

static ocmqttv5_democase_t g_ocmqttv5_testarray []=
{
    {"USERSUB",demo_usersub_topic},
    {"USERPUB",demo_userpub},
    {"USERUNSUB",demo_userunsub_topic},
    {"MSGUP_SHORTDATA",demo_msgup_shortdata},
    {"MSGUP_LONGDATA",demo_msgup_longdata},
    {"PROPERTY_REPORT",demo_propertireport},
    {"PUBLISH_DEFAULT",demo_pubdefault},
    {"GETSHADOW",demo_getshadow},
    {"REPORTVERSION",demo_reportversion},

};
#define CN_OCMQTTV5_DEMOCASENUM    (sizeof(g_ocmqttv5_testarray)/sizeof(ocmqttv5_democase_t))

static void  oc_report_normal(void)
{
    int i = 0;
    int ret;
    static uint32_t runtimes = 0;
    runtimes++;

    for(i= 0;i< (int)CN_OCMQTTV5_DEMOCASENUM;i++)
    {
        ret = g_ocmqttv5_testarray[i].func();
        if(ret != 0)
        {
            g_ocmqttv5_testarray[i].failtimes++;
        }
        (void) printf("DEMORUN:%d TIMES CASE:%d RET:%d FAILTTOTAL:%d NAME:%s \r\n",\
                       (int)runtimes,i,ret,g_ocmqttv5_testarray[i].failtimes,g_ocmqttv5_testarray[i].name);
    }
    return;
}


static int task_rcvmsg_entry( void *args)
{
    oc_mqtt_profile_msgrcv_t *demo_msg;
    while(1)
    {
        demo_msg = NULL;
        (void)queue_pop(s_queue_rcvmsg,(void **)&demo_msg,(int)cn_osal_timeout_forever);
        if(NULL != demo_msg)
        {
            (void) oc_cmd_normal(demo_msg);
            osal_free(demo_msg);
        }
    }
    return 0;
}

void  hwoc_mqtt_log(en_oc_mqtt_log_t  logtype)
{

    if(logtype == en_oc_mqtt_log_connected)
    {
        (void)printf("%s:connected %d\n\r",__FUNCTION__,(int)logtype);
    }
    else
    {
        (void)printf("%s:disconnected %d\n\r",__FUNCTION__,(int)logtype);
    }

    return;
}

static int task_reportmsg_entry(void *args)
{
    int ret;
    oc_mqtt_profile_connect_t  connect_para;

    (void) memset( &connect_para, 0, sizeof(connect_para));

    connect_para.boostrap =      CN_BOOT_MODE;
    connect_para.device_id =     CN_EP_DEVICEID;
    connect_para.device_passwd = CN_EP_PASSWD;
    connect_para.server_addr =   CN_SERVER_IPV4;
    connect_para.sevver_port =   CN_SERVER_PORT;
    connect_para.life_time =     CN_LIFE_TIME;
    connect_para.rcvfunc =       app_msg_deal;
    connect_para.logfunc  = hwoc_mqtt_log;

    connect_para.security.type = CN_SECURITY_TYPE;

    connect_para.security.u.cert.server_ca = (uint8_t *)s_server_ca;
    connect_para.security.u.cert.server_ca_len = sizeof(s_server_ca);

    connect_para.security.u.cert.client_ca = (uint8_t *)s_client_ca;
    connect_para.security.u.cert.client_ca_len = sizeof(s_client_ca);
    connect_para.security.u.cert.client_pk = (uint8_t *)s_client_pk;
    connect_para.security.u.cert.client_pk_len = sizeof(s_client_pk);
    connect_para.security.u.cert.client_pk_pwd = (uint8_t *)s_client_pk_pwd;
    connect_para.security.u.cert.client_pk_pwd_len = strlen(s_client_pk_pwd);

    ret = oc_mqtt_profile_connect(&connect_para);
    if((ret != (int)en_oc_mqtt_err_ok))
    {
        (void) printf("config:err :code:%d\r\n",ret);
        return -1;
    }

    while(1)  //do the loop here
    {
        oc_report_normal();
        osal_task_sleep(CONFIG_OCMQTTV5_DEMO_REPORTCYCLE);
    }
    return 0;
}

int oc_mqtt_demo_main()
{
    static oc_mqtt_profile_kv_t  property;
    (void)printf("DO THE OC MQTT V5 DEMOS\n\r");
    s_queue_rcvmsg = queue_create("queue_rcvmsg",2,1);
    ///< initialize the service
    property.nxt   = NULL;
    s_device_service.event_time = NULL;
    s_device_service.service_id = "DeviceStatus";
    s_device_service.service_property = &property;
    s_device_service.nxt = NULL;

    (void) osal_task_create("demo_reportmsg",task_reportmsg_entry,NULL,0x800,NULL,8);
    (void) osal_task_create("demo_rcvmsg",task_rcvmsg_entry,NULL,0x800,NULL,8);

    return 0;
}
