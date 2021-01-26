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


//include the file which implement the function
#include  <string.h>
#include  <osal_imp.h>

///< this is implement for the task
#include "os_cpu.h"
#include <ucos_ii.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static void __task_sleep(int ms)
{
    uint32_t sys_tick_ms = 1000 / OS_TICKS_PER_SEC;
    uint32_t delay_tick;

    delay_tick = (ms + sys_tick_ms - 1) / sys_tick_ms;
    OSTimeDly(delay_tick);
    return;
}

static void *__task_create(const char *name,int (*task_entry)(void *args),\
        void *args,int stack_size,void *stack,int prior)
{
    INT8U err;
    void *ret = NULL; 
    INT8U   __u8Prio = 0;
    if (prior > 0 && prior <= OS_LOWEST_PRIO)
    {
        OS_STK *os_stk;
        stack_size = stack_size / sizeof(OS_STK);
        os_stk = (OS_STK *)malloc(stack_size * sizeof(OS_STK));
        __u8Prio = 10 + prior;
        if (os_stk == NULL)
            return ret;

        err = OSTaskCreateExt((void   (*)(void *p_arg))task_entry,
                            (void *)args,
                            (OS_STK *)&os_stk[stack_size - 1],
                            __u8Prio,
                            __u8Prio,
                            (OS_STK *)&os_stk[0],
                            stack_size,
                            (void *)0,
                            OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
         if (err != OS_ERR_NONE)
             return ret;
             
     }
 
    #if OS_TASK_NAME_SIZE > 13
    OSTaskNameSet(__u8Prio, (INT8U *)name, &err);
    #endif
    ret = (void *)__u8Prio;
    return ret;
}

static int __task_kill(void *task)
{
    int ret = -1;
    OS_TCB       *ptcb;
    INT8U prio;
    OS_STK *stack;
    if(NULL != task)
    {
        prio = (INT8U) task;
        ptcb = OSTCBPrioTbl[prio];
        
        stack = ptcb->OSTCBStkBottom;
        if(OS_ERR_NONE == OSTaskDel(prio))
        {
            ret = 0;
            if (stack != NULL)
                free(stack);
        }
    }

    return ret;
}

static void __task_exit()
{
    while(1);  //not supported yet
}

///< this is implement for the mutex
//#include <los_mux.h>
//creat a mutex for the os
static bool_t  __mutex_create(osal_mutex_t *mutex)
{
    OS_EVENT *event;

    event = OSSemCreate(1);
    if (event != NULL)
    {
        *mutex = (void *)event;
        return true;
    }
    return false;
}
//lock the mutex
static bool_t  __mutex_lock(osal_mutex_t mutex)
{
    INT8U err;
    OS_EVENT *event;

    event = (OS_EVENT *) mutex;

    OSSemPend(event, 0, &err);
    if (err == OS_ERR_NONE)
        return true;
    else
        return false;
}

//unlock the mutex
static bool_t  __mutex_unlock(osal_mutex_t mutex)
{
    OS_EVENT *event;

    event = (OS_EVENT *) mutex;

    if (event->OSEventCnt == 0)
    {
        OSSemPost(event);
        return true;
    }

    return false;
}
//delete the mutex
static bool_t  __mutex_del(osal_mutex_t mutex)
{
    OS_EVENT *event;
    INT8U err;

    event = (OS_EVENT *) mutex;

    OSSemDel(event, OS_DEL_NO_PEND, &err);
    if (OS_ERR_NONE == err)
        return true;

    return false;
}


///< this is implement for the semp
//#include <los_sem.h>


//semp of the os
static bool_t  __semp_create(osal_semp_t *semp,int limit,int initvalue)
{
    OS_EVENT *event;

    event = OSSemCreate(initvalue);

    if (event != NULL)
    {
        *semp = (void *)event;
        return true;
    }
    return false;
}

static bool_t  __semp_pend(osal_semp_t semp,int timeout)
{
    INT8U err;
    OS_EVENT *event;

    event = (OS_EVENT *) semp;

    if (timeout == 0)
        timeout = 1;
    else if (timeout == 0xffffffff)
        timeout = 0;

    OSSemPend(event, timeout, &err);
    if (err == OS_ERR_NONE)
        return true;
    else
        return false;
}

static bool_t  __semp_post(osal_semp_t semp)
{
    INT8U err;
    OS_EVENT *event;

    event = (OS_EVENT *) semp;
    err = OSSemPost(event);
    if (OS_ERR_NONE == err)
    {
        return true;
    }

    return false;
}

static bool_t  __semp_del(osal_semp_t semp)
{
    OS_EVENT *event;
    INT8U err;

    event = (OS_EVENT *) semp;

    OSSemDel(event, OS_DEL_NO_PEND, &err);
    if (OS_ERR_NONE == err)
        return true;

    return false;
}

///< this implement for the memory management
//#include <los_memory.h>
extern OS_MEM *os_mem_pool;

static void *__mem_malloc(int size)
{
    void *ret = NULL;
    INT8U err;

    if(size > 0)
    {
        ret = OSMemGet(os_mem_pool, &err);
        if (ret == NULL)
            printf("malloc failed!!!\r\n");
    }

    return ret;
}

static void __mem_free(void *addr)
{
    if (addr != NULL)
        OSMemPut(os_mem_pool, addr);
}

///< sys time
static unsigned long long __get_sys_time()
{
    return OSTimeGet() * 1000 / OS_TICKS_PER_SEC;
}



//interrupt
static int __int_connect(int intnum, int prio, int mode, fn_interrupt_handle callback, void* arg)
{
    return 0;
}

static const tag_os_ops s_ucos_ops =
{
    .task_sleep = __task_sleep,
    .task_create = __task_create,
    .task_kill = __task_kill,
    .task_exit = __task_exit,

    .mutex_create = __mutex_create,
    .mutex_lock = __mutex_lock,
    .mutex_unlock = __mutex_unlock,
    .mutex_del = __mutex_del,

    .semp_create = __semp_create,
    .semp_pend = __semp_pend,
    .semp_post = __semp_post,
    .semp_del = __semp_del,

    .malloc = __mem_malloc,
    .free = __mem_free,

    .get_sys_time = __get_sys_time,
    .reboot = liteos_reboot,

    .int_connect = __int_connect,
};



static const tag_os s_link_ucos =
{
    .name = "Ucos_ii",
    .ops = &s_ucos_ops,
};

int os_imp_init(void)
{
    int ret = -1;

    ret = osal_install(&s_link_ucos);

    return ret;
}
