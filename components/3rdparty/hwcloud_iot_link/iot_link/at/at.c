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

#include <at.h>
#include <stdlib.h>
#include <string.h>
#include <driver.h>
#include <sys/fcntl.h>

//these defines could be reconfigured at the iot_link_config.h

#ifndef CONFIG_AT_DEVNAME
#define CONFIG_AT_DEVNAME              "atdev"
#endif

#ifndef CONFIG_AT_OOBTABLEN
#define CONFIG_AT_OOBTABLEN              6              //only allow 6 oob command monitor here,you could configure it more
#endif

#ifndef CONFIG_AT_RECVMAXLEN
#define CONFIG_AT_RECVMAXLEN             1024           //PROSING THAT COULD GET THE MOST REPSLENGTH
#endif

#ifndef CONFIG_AT_TASKPRIOR
#define CONFIG_AT_TASKPRIOR              10
#endif





//at control block here
typedef struct
{
    const void *cmd;               //pointed to the at command
    size_t      cmdlen;            //how many bytes of the command for the command may not be string(binary string)
    const char *index;             //used to check if the frame is the response of the command
    const void *respbuf;           //which used to storage the response,supplied by the at command
    size_t      respbuflen;        //index the response buffer length,supplied by the at command
    size_t      respdatalen;       //index how many data in the response buffer, filled by the at engine
    osal_semp_t      respsync;     //binary semphore, activated by the at engine,if any response matched
    osal_semp_t      cmdsync;      //used to make the at command sync, binary sempore, only one at command could be excuted at one time
    osal_mutex_t     cmdlock;      //make the command list atomic
}at_cmd_item;//the member cmd and cmdlen not used yet,will be used for the debug

typedef struct
{
    const char *name;     ///< this function used for the oob item name
    fn_at_oob   func;     ///<  the function that will deal the out of band data
    void       *args;     ///<  the function param for the function
    const char *index;    ///<  used to match the out of band data,only compared from the header
    size_t      len;   ///<  used for the index length
}at_oob_item;

typedef enum
{
    en_at_debug_none = 0,
    en_at_debug_ascii,
    en_at_debug_hex,
}en_at_rxtx_debugmode;        //FUNCTION USED TO CONTROL THE DEBUG MODE

typedef struct
{
    const char             *devname;  //we use the device frame work to do this
    los_dev_t               devhandle;//the device handle used 

    at_cmd_item             cmd;      //the at command,only one command could be excuted
    at_oob_item             oob[CONFIG_AT_OOBTABLEN];        //storage the out of band dealer
    char                    rcvbuf[CONFIG_AT_RECVMAXLEN];     //used storage one frame,read from the at channel
    unsigned int            rxdebugmode:2;                 //receive debug mode
    unsigned int            txdebugmode:2;                 //send debug mode

    int                     streammode;
}at_cb_t;
static at_cb_t g_at_cb;   //this is the at controller here

//this function used to send the data to the AT channel
static int __cmd_send(const void *buf,size_t buflen,uint32_t timeout)
{
    int i = 0;
    ssize_t ret = 0;
    int debugmode;

    ret = los_dev_write(g_at_cb.devhandle,0,buf,buflen,timeout);
    if(ret > 0)
    {
        debugmode = g_at_cb.txdebugmode;
        switch (debugmode)
        {
            case en_at_debug_ascii:
                LINK_LOG_DEBUG("ATSND:%d Bytes:%s\n\r",(int)ret,(char *)buf);
                break;
            case en_at_debug_hex:
                LINK_LOG_DEBUG("ATSND:%d Bytes:",(int)ret);
                for(i =0;i<ret;i++)
                {
                    LINK_LOG_DEBUG("%02x ",*((uint8_t *)(buf) + i));
                }
                LINK_LOG_DEBUG("\n\r");
                break;
            default:
                break;
        }
        ret = 0;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

//this function used to receive data from the AT channel
static int __resp_rcv(void *buf,size_t buflen,uint32_t timeout)
{
    int i = 0;
    ssize_t ret = 0;
    int debugmode;

    ret = los_dev_read(g_at_cb.devhandle,0,buf,buflen,timeout);
    if(ret > 0)
    {
        debugmode = g_at_cb.rxdebugmode;
        switch (debugmode)
        {
            case en_at_debug_ascii:
                LINK_LOG_DEBUG("ATRCV:%d Bytes:%s\n\r",(int)ret,(char *)buf);
                break;
            case en_at_debug_hex:
                LINK_LOG_DEBUG("ATRCV:%d Bytes:",(int)ret);
                for(i =0;i<ret;i++)
                {
                    LINK_LOG_DEBUG("%02x ",*((uint8_t *)(buf) + i));
                }
                LINK_LOG_DEBUG("\n\r");
                break;
            default:
                break;
        }
    }  
 
    return ret;
}

//create a command
static int  __cmd_create(const void *cmdbuf,size_t cmdlen,const char *index,void *respbuf,size_t respbuflen,uint32_t timeout)
{
    int  ret = -1;
    at_cmd_item *cmd;

    cmd = &g_at_cb.cmd;
    if(osal_semp_pend(cmd->cmdsync,timeout))
    {
        if(osal_mutex_lock(cmd->cmdlock))
        {
            cmd->cmd = cmdbuf;
            cmd->cmdlen = cmdlen;
            cmd->index = index;
            cmd->respbuf = respbuf;
            cmd->respbuflen = respbuflen;
            (void) osal_semp_pend(cmd->respsync,0); //used to clear the sync
            (void) osal_mutex_unlock(cmd->cmdlock);
        }
        ret = 0;
    }
    return ret;
}

//clear the at command here
static int __cmd_clear(void)
{
     at_cmd_item *cmd;

     cmd = &g_at_cb.cmd;
     if(osal_mutex_lock(cmd->cmdlock))
     {
        cmd->cmd = NULL;
        cmd->cmdlen = 0;
        cmd->index = NULL;
        cmd->respbuf = NULL;
        cmd->respbuflen = 0;
        cmd->respdatalen = 0;
        (void) osal_mutex_unlock(cmd->cmdlock);
     }
     (void) osal_semp_post(cmd->cmdsync);
     return 0;
}

//check if the data received is the at command need
static int  __cmd_match(const void *data,size_t len)
{
    int  ret = -1;
    int  cpylen;
    at_cmd_item *cmd = NULL;

    cmd = &g_at_cb.cmd;
    if(osal_mutex_lock(cmd->cmdlock))
    {
        if((NULL != cmd->index)&&(NULL != strstr((const char *)data,cmd->index)))
        {
            if(NULL != cmd->respbuf)
            {
                cpylen = len > cmd->respbuflen?cmd->respbuflen:len;
                (void) memcpy((char *)cmd->respbuf,data,cpylen);
                cmd->respdatalen = cpylen;
            }
            else
            {
                cmd->respdatalen = len; //tell the command that how many data has been get
            }
            (void) osal_semp_post(cmd->respsync);
            ret = 0;
        }
        (void) osal_mutex_unlock(cmd->cmdlock);
    }
    return ret;
}

//check if any out of band method could deal the data
static int  __oob_match(void *data,size_t len)
{
    int ret = -1;
    at_oob_item *oob;
    int i = 0;
    for(i =0;i<CONFIG_AT_OOBTABLEN;i++)
    {
        oob = &g_at_cb.oob[i];
        if((oob->func != NULL)&&(oob->index != NULL)&&\
            (0 == memcmp(oob->index,data,oob->len)))
        {
            ret = oob->func(oob->args,data,len);
            break;
        }
    }
    return ret;
}

/*******************************************************************************
function     :this is the  at receiver engine
parameters   :
instruction  :this task read the device continousely and blocked by the read function
              if pass by mode, then pass it to the pass function;else will match the 
              at command, if not then match the out of band
*******************************************************************************/
static int __rcv_task_entry(void *args)
{
    bool_t matchret;
    int oobret;
    int  rcvlen = 0;

    g_at_cb.devhandle = los_dev_open(g_at_cb.devname,O_RDWR);
    if(NULL == g_at_cb.devhandle)
    {
        LINK_LOG_DEBUG("%s:open %s err\n\r",__FUNCTION__,g_at_cb.devname);
        return 0;
    }

    while(NULL != g_at_cb.devhandle)
    {
    	if (1 == g_at_cb.streammode)  //in stream mode, we need to save previous frames in buffer
    	{
            if(rcvlen == 0)
            {
                (void)memset(g_at_cb.rcvbuf,0,CONFIG_AT_RECVMAXLEN);
            }
            rcvlen += __resp_rcv(g_at_cb.rcvbuf+ rcvlen,CONFIG_AT_RECVMAXLEN,cn_osal_timeout_forever);
            if( rcvlen > 0)
            {
                matchret = __cmd_match(g_at_cb.rcvbuf,rcvlen);
                if(0 != matchret)
                {
                    oobret = __oob_match(g_at_cb.rcvbuf,rcvlen);
                    if(oobret != -1)
                    {
                        rcvlen = 0;
                    }
                }
                else
                {
                    rcvlen = 0;
                }
            }
    	}
    	else
    	{
    	    (void) memset(g_at_cb.rcvbuf,0,CONFIG_AT_RECVMAXLEN);
    	    rcvlen = __resp_rcv(g_at_cb.rcvbuf,CONFIG_AT_RECVMAXLEN,cn_osal_timeout_forever);
    	    if(rcvlen > 0)
	        {
                matchret = __cmd_match(g_at_cb.rcvbuf,rcvlen);
                if(0 != matchret)
                {
                    (void) __oob_match(g_at_cb.rcvbuf,rcvlen);
                }
	        }
        }
    }

    return 0;
}

/*******************************************************************************
function     :you could use this function to to enable or disable at stream mode.
parameters   :mode:1 for stream mode, 0 for dgram mode.
instruction  :If stream mode is enabled, we can process data from multiple frames.
			  mode equals 0 by default.
*******************************************************************************/
int at_streammode_set(int mode)
{
	g_at_cb.streammode = mode;
	return 0;
}


int at_debugclose(void)
{
    //for the debug
    g_at_cb.rxdebugmode = en_at_debug_none;
    g_at_cb.txdebugmode = en_at_debug_none;

    return 0;
}


/*******************************************************************************
function     :this is our at command here,you could send any command as you wish
parameters   :
instruction  :only one command could be dealt at one time, for we use the semphore
              here do the sync;if the respbuf is not NULL,then we will cpoy the 
              response data to the respbuf as much as the respbuflen permit
*******************************************************************************/
int  at_command(const void *cmd,size_t cmdlen,const char *index,void *respbuf,\
		        size_t respbuflen,uint32_t timeout)
{
    int ret = -1;
    if(NULL == cmd)
    {
        return ret;
    }
    if(NULL != index)
    {
        ret = __cmd_create(cmd,cmdlen,index,respbuf,respbuflen,timeout);
        if(0 == ret)
        {
            ret = __cmd_send(cmd,cmdlen,timeout);
            if(0 == ret)
            {
                if(osal_semp_pend(g_at_cb.cmd.respsync,timeout))
                {
                    ret = g_at_cb.cmd.respdatalen;
                }
                else
                {
                    ret = -1;
                }
            }
            else
            {
                ret = -1;
            }

            (void) __cmd_clear();
        }

    }
    else
    {
        ret = __cmd_send(cmd,cmdlen,timeout);
    }

    return ret;
}

/*******************************************************************************
function     :you could use this function to register a method to deal the out of band data
parameters   :
instruction  :as you know, we only check the frame begin,using memcmp, so you must
              write the header of the frame as the index
*******************************************************************************/
int at_oobregister(const char *name,const void *index,size_t len,fn_at_oob func,void *args)
{
    int ret = -1;
    at_oob_item *oob;
    int i = 0;

    if((NULL == func)||(NULL == index))
    {
        return ret;
    }

    for(i =0;i<CONFIG_AT_OOBTABLEN;i++)
    {
        oob = &g_at_cb.oob[i];
        if((oob->func == NULL)&&(oob->index == NULL))
        {
            oob->name = name;
            oob->index = index;
            oob->len = len;
            oob->func = func;
            oob->args = args;
            ret = 0;
            break;
        }
    }

    return ret;
}

/*******************************************************************************
function     :this is the  at module initialize function
parameters   :func_read:which will read a frame from the device
              func_write:which will be used to write a frame to the device
instruction  :if you want to use the at frame work, please call this function 
              please supply the function read and write.the read function must be
              a block function controlled by timeout
*******************************************************************************/
int at_init()
{
    int ret = -1;

    (void) memset(&g_at_cb,0,sizeof(g_at_cb));
    g_at_cb.devname = CONFIG_AT_DEVNAME;


    if(false == osal_semp_create(&g_at_cb.cmd.cmdsync,1,1))
    {
        LINK_LOG_DEBUG("%s:cmdsync error\n\r",__FUNCTION__);
        goto EXIT_CMDSYNC;
    }
    if(false == osal_semp_create(&g_at_cb.cmd.respsync,1,0))
    {
        LINK_LOG_DEBUG("%s:cmdsync error\n\r",__FUNCTION__);
        goto EXIT_RESPSYNC;
    }
    if(false == osal_mutex_create(&g_at_cb.cmd.cmdlock))
    {
        LINK_LOG_DEBUG("%s:cmdlock error\n\r",__FUNCTION__);
        goto EXIT_CMDLOCK;
    }

    if(NULL == osal_task_create("at_rcv",__rcv_task_entry,NULL,0x800,NULL,10))
    {
        LINK_LOG_DEBUG("%s:rcvtask create error\n\r",__FUNCTION__);
        goto EXIT_RCVTASK;
    }

    //for the debug
    g_at_cb.rxdebugmode = en_at_debug_ascii;
    g_at_cb.txdebugmode = en_at_debug_ascii;

    ret = 0;
    return ret;


EXIT_RCVTASK:
    (void) osal_mutex_del(&g_at_cb.cmd.cmdlock);
    g_at_cb.cmd.cmdlock = cn_mutex_invalid;
EXIT_CMDLOCK:
    (void) osal_semp_del(&g_at_cb.cmd.respsync);
    g_at_cb.cmd.respsync = cn_semp_invalid;
EXIT_RESPSYNC:
    (void) osal_semp_del(&g_at_cb.cmd.cmdsync);
    g_at_cb.cmd.cmdsync = cn_semp_invalid;
EXIT_CMDSYNC:
    return ret;
}

//////////////////////////////////DEBUG COMMAND FOLLOWING/////////////////////////////////////////
#ifdef CONFIG_SHELL_ENABLE

#include <shell.h>
//use this shell command,you could input at command through the terminal
static int shell_at(int argc, const char *argv[])
{
    #define CN_AT_SHELL_LEN 64
     
    char respbuf[CN_AT_SHELL_LEN];
    unsigned char cmdbuf[CN_AT_SHELL_LEN];
    
    const char *index =NULL ;
    int ret = -1;

    if((argc !=2)&&(argc != 3))
    {
        LINK_LOG_DEBUG("paras error\n\r");
        return ret;
    }
    if(argc == 3)
    {
        index = argv[2];
    }
    

    (void) (void) memset(respbuf,0,CN_AT_SHELL_LEN);
    (void) snprintf((char *)cmdbuf,CN_AT_SHELL_LEN,"%s\r\n",argv[1]);

    ret = at_command(cmdbuf,strlen((const char *)cmdbuf),index,respbuf,CN_AT_SHELL_LEN,1000); //one second
    if(ret == 0)
    {
        LINK_LOG_DEBUG("atresponse:%d Bytes:%s\n\r",ret,respbuf);
    }
    else
    {
        LINK_LOG_DEBUG("atresponse:timeout or error\n\r");
    }
    return ret;
}
OSSHELL_EXPORT_CMD(shell_at,"atcmd","atcmd atcommand atrespindex");

//use this function to set the at command display mode:none/ascii/hex
static int shell_atdebug(int argc,const char *argv[])
{
    en_at_rxtx_debugmode mode = en_at_debug_none;
    if(argc != 3)
    {
        LINK_LOG_DEBUG("paras error\n\r");
        return -1;
    }

    if(0 == strcmp(argv[2],"none"))
    {
        mode = en_at_debug_none;
    }
    else if(0 == strcmp(argv[2],"ascii"))
    {
        mode = en_at_debug_ascii;
    }
    else if(0 == strcmp(argv[2],"hex"))
    {
        mode = en_at_debug_hex;
    }
    else
    {
        LINK_LOG_DEBUG("mode set error\n\r");
        return -2;
    }

    if(0 == strcmp(argv[1],"rx"))
    {
        g_at_cb.rxdebugmode = (unsigned int) mode;
    }
    else if(0 == strcmp(argv[1],"tx"))
    {
        g_at_cb.txdebugmode = (unsigned int ) mode;
    }
    else
    {
        LINK_LOG_DEBUG("type set error\n\r");
        return -3;
    }

    return 0;
}
OSSHELL_EXPORT_CMD(shell_atdebug,"atdebug","atdebug rx/tx none/ascii/hex");

#endif




