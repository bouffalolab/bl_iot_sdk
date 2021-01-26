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
#include <FreeRTOS.h>
#include <osdep_service.h>
#include  <stdio.h>


extern struct osdep_service_ops osdep_service;


struct list_node {
    struct list_node *next;
    struct task_struct *freertos_task;
};
static int task_num = 0;

struct list_node *list_header = NULL;

static void __add_to_tail(struct list_node *node)
{
    struct list_node *next_node = list_header;

    if(node != NULL && node->next != NULL)
    {
        node->next = NULL;
    }
    //first add
    if(list_header == NULL)
    {
        list_header = node;
        task_num++;
        DBG_8195A("add node:%p in __add_to_tail,num:%d\r\n",node,task_num);
        return;
    }
    //not first add
    while(next_node->next != NULL)
    {
        next_node = next_node->next;
    }
    task_num++;
    DBG_8195A("++add node:%p in __add_to_tail,num:%d\r\n",node,task_num);
    
    next_node->next = node;
}

static struct list_node * __find_and_del_from_list(_thread_hdl_ task)
{
    struct list_node *next_node = list_header;
    struct list_node *pre_node = list_header;
    int find = 0;
    
    while(next_node != NULL)
    {
        if(next_node->freertos_task->task == task)
        {
            find = 1;
            break;
        }
        pre_node = next_node;
        next_node = next_node->next;
    }

    if(find == 1)
    {
        //first delete
        if(next_node == list_header)
        {
            list_header =  next_node->next;   
        }
        else //not first delete
        {
            pre_node->next = next_node->next;
        }
        return next_node;
    }
    else
    {
        return NULL;
    }
    
    
}


///< this is implement for the task
static void __task_sleep(int ms)
{
    rtw_msleep_os(ms);
}

static void *__task_create(const char *name,int (*task_entry)(void *args),\
        void *args,int stack_size,void *stack,int prior)
{
    struct task_struct *freertos_task = rtw_malloc(sizeof(struct task_struct));
    if (freertos_task == NULL)
        goto failed;
    if(name!=NULL) DBG_8195A("create task(%s), freertos_task:%p\r\n",name,freertos_task);
    else DBG_8195A("create task, freertos_task:%p\r\n",freertos_task);
    int ret = rtw_create_task(freertos_task, name, stack_size, prior, task_entry, args);
    if (ret != pdPASS) {
        rtw_mfree(freertos_task, 0);
        return NULL;
    }
    DBG_8195A("++freertos_task->task:%p\r\n",freertos_task->task);
    struct list_node *node = rtw_malloc(sizeof(*node));
    if(node == NULL)
        goto failed;
    rtw_memset(node,0,sizeof(*node));
    node->freertos_task = freertos_task;
    __add_to_tail(node);
    return (void *)freertos_task->task;
failed:
    if (freertos_task)
        rtw_mfree(freertos_task, 0);
    return NULL;
}

static int __task_kill(void *task)
{
    DBG_8195A("__task_kill:%p\r\n",task);
    struct list_node *node = __find_and_del_from_list(task);
    if(node == NULL)
    {
        DBG_8195A("cannot find task TCB:%p\r\n",task);
        return false;
    }
    task_num--;
    DBG_8195A("__task_kill:node:%p, freertos_task:%p,task_num:%d\r\n",node, node->freertos_task,task_num);
    rtw_delete_task(node->freertos_task);
    rtw_mfree(node->freertos_task, 0);
    rtw_mfree(node, 0);
    return true;
}

static void __task_exit()
{
    while(1);  //not supported yet
}

// static void* __cur_task_id()
// {
//     void *handler = xTaskGetCurrentTaskHandle();
//     DBG_8195A("__cur_task_id, handler:%p\r\n",handler);
//     return handler;
// }
///< this is implement for the mutex
//#include <los_mux.h>
//creat a mutex for the os
static bool_t  __mutex_create(osal_mutex_t *mutex)
{
    rtw_mutex_init(mutex);
    return true;
}
//lock the mutex
static bool_t  __mutex_lock(osal_mutex_t mutex)
{
    rtw_mutex_get(&mutex);
    return true;
}

//unlock the mutex
static bool_t  __mutex_unlock(osal_mutex_t mutex)
{
    rtw_mutex_put(&mutex);
    return true;
}
//delete the mutex
static bool_t  __mutex_del(osal_mutex_t mutex)
{
    rtw_mutex_free(&mutex);

    return true;
}


///< this is implement for the semp
//#include <los_sem.h>


//semp of the os
static bool_t  __semp_create(osal_semp_t *semp,int limit,int initvalue)
{
//    extern unsigned int osSemCreate (UINT16 usCount, UINT16 usMaxCount, unsigned int *puwSemHandle);
    rtw_init_sema(semp, initvalue);

    return true;
}
static bool_t  __semp_pend(osal_semp_t semp,int timeout)
{
    int ret = false;
    if(timeout == cn_osal_timeout_forever)
    {
        timeout = -1;
    }
    ret = rtw_down_timeout_sema((_sema*)semp,(unsigned int)timeout);
    if (ret == pdTRUE) {
        return true;
    } else {
        return false;
    }
}
static bool_t  __semp_post(osal_semp_t semp)
{
    rtw_up_sema((_sema*)semp);
    return true;
}

static bool_t  __semp_del(osal_semp_t semp)
{
    rtw_free_sema((_sema*)semp);
    return true;
}


///< this implement for the memory management
//#include <los_memory.h>

extern void *pvPortMalloc( size_t xWantedSize );

static void *__mem_malloc(int size)
{
    void *ret = NULL;

    if(size > 0)
    {
        ret = rtw_malloc(size);
        rtw_memset(ret, 0, size);
    }

    return ret;
}

static void __mem_free(void *addr)
{
    rtw_mfree(addr, 0);
}


static bool_t __queue_create(osal_queue_t *queue,int len,int msgsize)
{
    int ret =  rtw_init_xqueue(queue, "", msgsize, len);
    if (ret == 0) {
        return true;
    } else {
        return false;
    }
}

static bool_t __queue_send(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout)
{
    int ret = rtw_push_to_xqueue(&queue, pbuf, timeout);
    if (ret == 0) {
        return true;
    } else {
        return false;
    }
}

static bool_t __queue_recv(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout)
{
    int ret =  rtw_pop_from_xqueue(&queue, pbuf, timeout);
    if (ret == 0) {
        return true;
    } else {
        return false;
    }
}

static bool_t __queue_del(osal_queue_t queue)
{
    int ret =  rtw_deinit_xqueue(&queue);
    if (ret == 0) {
        return true;
    } else {
        return false;
    }
}

///< sys time
//#include <los_sys.ph>

//extern UINT64 osKernelGetTickCount (void);
#define OS_SYS_MS_PER_SECOND                   1000

static unsigned long long __get_sys_time()
{
    return rtw_get_current_time();
}


//interrupt
// #include <los_hwi.h>
// static int __int_connect(int intnum, int prio, int mode, fn_interrupt_handle callback, void* arg)
// {
//     extern unsigned int LOS_HwiCreate(HWI_HANDLE_T  uwHwiNum, \
//                                 HWI_PRIOR_T   usHwiPrio, \
//                                 HWI_MODE_T    usMode, \
//                                 HWI_PROC_FUNC pfnHandler, \
//                                 HWI_ARG_T     uwArg \
//                                 );
//     return LOS_HwiCreate((HWI_HANDLE_T)intnum, (HWI_PRIOR_T)prio,(HWI_MODE_T) mode, (HWI_PROC_FUNC)callback, (HWI_ARG_T)arg);
// }

static const tag_os_ops s_cmsisos_ops =
{
    .task_sleep = __task_sleep,
    .task_create = __task_create,
    .task_kill = __task_kill,
    .task_exit = __task_exit,
    // .cur_task_id = __cur_task_id,

    .mutex_create = __mutex_create,
    .mutex_lock = __mutex_lock,
    .mutex_unlock = __mutex_unlock,
    .mutex_del = __mutex_del,

    .semp_create = __semp_create,
    .semp_pend = __semp_pend,
    .semp_post = __semp_post,
    .semp_del = __semp_del,

    .mem_malloc = __mem_malloc,
    .mem_free = __mem_free,
    // .realloc = 

    .queue_create = __queue_create, 
    .queue_send = __queue_send,
    .queue_recv = __queue_recv, 
    .queue_del = __queue_del,

    .get_sys_time = __get_sys_time,
//    .reboot = liteos_reboot,

//    .int_connect = __int_connect,
};



static const tag_os s_link_cmsisos =
{
    .name = "OSAL",
    .ops = &s_cmsisos_ops,
};

int os_imp_init(void)
{
    int ret = -1;

    ret = osal_install(&s_link_cmsisos);

    return ret;
}

