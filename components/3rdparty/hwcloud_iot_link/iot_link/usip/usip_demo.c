/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2019>, <Huawei Technologies Co., Ltd>
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
#include "usip.h"
#define JSON_SESS_DATA "{\r\n"  \
  "\"type\": 1,\r\n"  \
  "\"encryptionMode\": 2,\r\n"  \
  "\"sn1\": \"2122232425262728\",\r\n"  \
  "\"seq\": 67\r\n"  \
  "}\r\n"

#define JSON_REG_DATA  "{\r\n"  \
  "\"devId\": \"\",\r\n"  \
  "\"dtlsPort\": 5784,\r\n"  \
  "\"devInfo\": {\r\n"  \
  "\"sn\": \"00E0FC018008\",\r\n"  \
  "\"model\": \"ddc-xxx\",\r\n"  \
  "\"devType\": \"004\",\r\n"  \
  "\"manu\": \"002\",\r\n"  \
  "\"prodId\": \"000b\",\r\n"  \
  "\"mac\": \"00112233445566\",\r\n"  \
  "\"hiv\": \"1.0\",\r\n"  \
  "\"fwv\": \"10.01\",\r\n"  \
  "\"hwv\": \"VER.C\",\r\n"  \
  "\"swv\": \"V100R001C01B010\",\r\n"  \
  "\"protType\": 1\r\n"  \
  "},\r\n"  \
  "\"services\": [{\r\n"  \
  "\"st\": \"light\",\r\n"  \
  "\"sid\": \"light1\"\r\n"  \
  "}]\r\n"  \
  "}\r\n"  \
  "\r\n"

#define JSON_HEARTBEAT_DATA "{\r\n"  \
  "\"devSn\": \"00E0FC018008\",\r\n"  \
  "}\r\n"

#define JSON_FILEMNGR_DATA "{\r\n"  \
  "\"command\": \"start\",\r\n"  \
  "\"operateCode\": \"update\",\r\n"  \
  "\"fileName\": \"ddc1-logic\",\r\n"  \
  "\"fileType\": \"ctlLogic\",\r\n"  \
  "\"fileSize\": \"30000\",\r\n"  \
  "\"fileDirectory\": \"\",\r\n"  \
  "\"checkSum\": \"23fwedfd...\",  \r\n"  \
  "}\r\n"

extern unsigned short g_received_devreg_result;
int usip_demo(void *args)//this task is used only for test send data
{
    unsigned int send_times = 0;
    unsigned char data[] = {JSON_REG_DATA};

    while(!g_received_devreg_result)//do the loop here
    {
        send_times++ ;
#ifdef USIP_LOG
        USIP_PRINTF("====send_times %d\r\n",send_times);
#endif
        if(usip_send_data(USIP_CMD_DEV_REG,data,(unsigned short)strlen(data)) != USIP_OK)
        {
#ifdef USIP_LOG
            USIP_PRINTF("====usip_send_data failed!\r\n");
#endif
        }
        LOS_TaskDelay(10*3000);
    }

    while(1)
    {
        unsigned char report_data[22] = "report_data:";
        unsigned char tmp[10] = {0};
        send_times++;
        itoa(send_times,tmp,10);
        strcat(report_data,tmp);
        usip_send_data(USIP_CMD_DATA_REPORT,report_data,strlen(report_data));
        LOS_TaskDelay(10*2000);
    }
}

int create_usip_demo_task()
{
    int ret = -1;
    UINT32 uwRet = LOS_OK;
    UINT32  handle;
    TSK_INIT_PARAM_S task_init_param;

    (void) memset (&task_init_param, 0, sizeof (TSK_INIT_PARAM_S));
    task_init_param.uwArg = (unsigned int)NULL;
    task_init_param.usTaskPrio = 7;
    task_init_param.pcName =(char *) "usip_demo";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)usip_demo;
    task_init_param.uwStackSize = 0x1000;
    uwRet = LOS_TaskCreate(&handle, &task_init_param);
    if(LOS_OK == uwRet){
        ret = 0;
    }
    return ret;
}
