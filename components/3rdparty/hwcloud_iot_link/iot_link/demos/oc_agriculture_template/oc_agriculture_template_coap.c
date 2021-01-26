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

#include <osal.h>
#include <oc_coap_al.h>
#include <link_endian.h>

#define cn_endpoint_id        "coap_15001230036"
#define cn_app_server         "119.3.250.80"
#define cn_app_port           "5683"

#define cn_app_Agriculture 0x0
#define cn_app_Agriculture_Control_Light 0x1
#define cn_app_response_Agriculture_Control_Light 0x2
#define cn_app_Agriculture_Control_Motor 0x3
#define cn_app_response_Agriculture_Control_Motor 0x4

#pragma pack(1)
typedef struct
{
    int8_t messageId;
    int8_t Temperature;
    int8_t Humidity;
    uint16_t Luminance;
} tag_app_Agriculture;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    int8_t errcode;
    int8_t Light_State;
} tag_app_Response_Agriculture_Control_Light;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    int8_t errcode;
    int8_t Motor_State;
} tag_app_Response_Agriculture_Control_Motor;

typedef struct
{
    int8_t messageId;
    uint16_t mid;
    char Light[3];
} tag_app_Agriculture_Control_Light;

typedef struct
{
    uint8_t messageId;
    uint16_t mid;
    char Motor[3];
} tag_app_Agriculture_Control_Motor;
#pragma pack()

//if your command is very fast,please use a queue here--TODO
#define cn_app_rcv_buf_len 128
static int             s_rcv_buffer[cn_app_rcv_buf_len];
static int             s_rcv_datalen;
static osal_semp_t     s_rcv_sync;

static void           *s_coap_handle = NULL;

//use this function to push all the message to the buffer
static int app_msg_deal(void *data, int len)
{
    unsigned char *msg;
    msg = data;
    int ret = -1;

    if(len <= cn_app_rcv_buf_len)
    {
    	if (msg[0] == 0xaa && msg[1] == 0xaa)
    	{
    		printf("OC respond message received! \n\r");
    		return ret;
    	}
        memcpy(s_rcv_buffer,msg,len);
        s_rcv_datalen = len;

        (void) osal_semp_post(s_rcv_sync);

        ret = 0;

    }
    return ret;
}


static int app_cmd_task_entry()
{
    int ret = -1;
    tag_app_Response_Agriculture_Control_Light Response_Agriculture_Control_Light;
    tag_app_Response_Agriculture_Control_Motor Response_Agriculture_Control_Motor;
    tag_app_Agriculture_Control_Light *Agriculture_Control_Light;
    tag_app_Agriculture_Control_Motor *Agriculture_Control_Motor;
    int8_t msgid;

    while(1)
    {
        if(osal_semp_pend(s_rcv_sync,cn_osal_timeout_forever))
        {
            msgid = s_rcv_buffer[0] & 0x000000FF;
            switch (msgid)
            {
                case cn_app_Agriculture_Control_Light:
                    Agriculture_Control_Light = (tag_app_Agriculture_Control_Light *)s_rcv_buffer;
                    printf("Agriculture_Control_Light:msgid:%d mid:%d", Agriculture_Control_Light->messageId, ntohs(Agriculture_Control_Light->mid));
                    /********** code area for cmd from IoT cloud  **********/
                    if (Agriculture_Control_Light->Light[0] == 'O' && Agriculture_Control_Light->Light[1] == 'N')
                    {
                        printf("max.su -> [%s:%d] light gpio set \r\n", __FUNCTION__, __LINE__); 
                        Response_Agriculture_Control_Light.messageId = cn_app_response_Agriculture_Control_Light;
                    	Response_Agriculture_Control_Light.mid = Agriculture_Control_Light->mid;
                        Response_Agriculture_Control_Light.errcode = 0;
                		Response_Agriculture_Control_Light.Light_State = 1;
                        oc_coap_report(s_coap_handle,(char *)&Response_Agriculture_Control_Light,sizeof(Response_Agriculture_Control_Light));
                        //oc_lwm2m_report((char *)&Response_Agriculture_Control_Light,sizeof(Response_Agriculture_Control_Light),1000);    ///< report cmd reply message
                    }
                    if (Agriculture_Control_Light->Light[0] == 'O' && Agriculture_Control_Light->Light[1] == 'F' && Agriculture_Control_Light->Light[2] == 'F')
                    {
                        printf("max.su -> [%s:%d] light gpio reset \r\n", __FUNCTION__, __LINE__); 
                        Response_Agriculture_Control_Light.messageId = cn_app_response_Agriculture_Control_Light;
                    	Response_Agriculture_Control_Light.mid = Agriculture_Control_Light->mid;
                        Response_Agriculture_Control_Light.errcode = 0;
                		Response_Agriculture_Control_Light.Light_State = 0;
                        oc_coap_report(s_coap_handle,(char *)&Response_Agriculture_Control_Light,sizeof(Response_Agriculture_Control_Light));
                        //oc_lwm2m_report((char *)&Response_Agriculture_Control_Light,sizeof(Response_Agriculture_Control_Light),1000);    ///< report cmd reply message
                    }
                    /********** code area end  **********/
                    break;
                case cn_app_Agriculture_Control_Motor:
                    Agriculture_Control_Motor = (tag_app_Agriculture_Control_Motor *)s_rcv_buffer;
                    printf("Agriculture_Control_Motor:msgid:%d mid:%d", Agriculture_Control_Motor->messageId, ntohs(Agriculture_Control_Motor->mid));
                    /********** code area for cmd from IoT cloud  **********/
                    if (Agriculture_Control_Motor->Motor[0] == 'O' && Agriculture_Control_Motor->Motor[1] == 'N')
                    {
                        printf("max.su -> [%s:%d] motor gpio set  \r\n", __FUNCTION__, __LINE__); 
                        Response_Agriculture_Control_Motor.messageId = cn_app_response_Agriculture_Control_Motor;
                    	Response_Agriculture_Control_Motor.mid = Agriculture_Control_Motor->mid;
                        Response_Agriculture_Control_Motor.errcode = 0;
                		Response_Agriculture_Control_Motor.Motor_State = 1;
                        oc_coap_report(s_coap_handle, (char *)&Response_Agriculture_Control_Motor,sizeof(Response_Agriculture_Control_Motor));
                        //oc_lwm2m_report((char *)&Response_Agriculture_Control_Motor,sizeof(Response_Agriculture_Control_Motor),1000);    ///< report cmd reply message
                    }
                    if (Agriculture_Control_Motor->Motor[0] == 'O' && Agriculture_Control_Motor->Motor[1] == 'F' && Agriculture_Control_Motor->Motor[2] == 'F')
                    {
                        printf("max.su -> [%s:%d] motor gpio reset  \r\n", __FUNCTION__, __LINE__); 
                        Response_Agriculture_Control_Motor.messageId = cn_app_response_Agriculture_Control_Motor;
                    	Response_Agriculture_Control_Motor.mid = Agriculture_Control_Motor->mid;
                        Response_Agriculture_Control_Motor.errcode = 0;
                		Response_Agriculture_Control_Motor.Motor_State = 0;
                        oc_coap_report(s_coap_handle, (char *)&Response_Agriculture_Control_Motor,sizeof(Response_Agriculture_Control_Motor));
                        //oc_lwm2m_report((char *)&Response_Agriculture_Control_Motor,sizeof(Response_Agriculture_Control_Motor),1000);    ///< report cmd reply message
                    }
                    /********** code area end  **********/
                    break;
                default:
                    break;
            }
        }
    }

    return ret;
}



static int app_report_task_entry()
{
    int ret = -1;

    oc_config_param_t      oc_param;
    tag_app_Agriculture Agriculture;

    (void) memset(&oc_param,0,sizeof(oc_param));

    oc_param.app_server.address = cn_app_server;
    oc_param.app_server.port = cn_app_port;
    oc_param.app_server.ep_id = cn_endpoint_id;
    oc_param.boot_mode = en_oc_boot_strap_mode_factory;
    oc_param.rcv_func = app_msg_deal;

    s_coap_handle = oc_coap_config(&oc_param);
    ret = oc_coap_config( &oc_param);
    
    if (0 != ret)
    {
    	return ret;
    }

    //install a dealer for the led message received
    while(1) //--TODO ,you could add your own code here
    {
        Agriculture.messageId = cn_app_Agriculture;
        Agriculture.Temperature = (int8_t)rand()%10;
        Agriculture.Humidity = (int8_t)rand()%20;
        Agriculture.Luminance = htons((uint16_t)rand()%30);
        oc_coap_report( s_coap_handle, (char *)&Agriculture, sizeof(Agriculture));
        osal_task_sleep(2*1000);
		printf("max.su -> [%s:%d]\r\n", __FUNCTION__, __LINE__);

    }
    return ret;
}

#include <stimer.h>

int standard_app_demo_main()
{
	osal_semp_create(&s_rcv_sync,1,0);

    osal_task_create("app_report",app_report_task_entry,NULL,0x2000,NULL,2);
    osal_task_create("app_command",app_cmd_task_entry,NULL,0x2000,NULL,3);

    return 0;
}





