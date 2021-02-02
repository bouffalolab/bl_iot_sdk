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
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include  <stdio.h>
#include  <string.h>
#include  <osal_imp.h>

///< this is implement for the task
static void __task_sleep(int ms)
{
    (void)vTaskDelay(ms);
    return;
}

static void *__task_create(const char *name,void (*task_entry)(void *args),\
        void *args,int stack_size,void *stack,int prior)
{
    void *ret = NULL;
    TaskHandle_t task_handle = pvPortMalloc(sizeof(TaskHandle_t));
    memset(&task_handle, 0, sizeof(TaskHandle_t));
    ret = xTaskCreate((TaskFunction_t)task_entry, (char *) name, \
                stack_size, args, (UBaseType_t)prior, &task_handle);
    if (ret == pdTRUE) {
        printf("task create -> [%s:%d]\r\n", __FUNCTION__, __LINE__);
    } else {
        printf("task create failed!!!\r\n");
    }
	return ret;
}

static int __task_kill(void *task)
{
    int ret = -1;
    TaskHandle_t handle;
    if(NULL != task)
    {
        handle = (TaskHandle_t)task;
        vTaskDelete(handle);
        ret = 0;
    }
    return ret;
}

static void __task_exit()
{
    while(1);  //not supported yet
}


static bool_t  __mutex_create(osal_mutex_t *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    if( *mutex != NULL)
    {
        return true;
    }else
    {
        return false;
    }
}
//lock the mutex
static bool_t  __mutex_lock(osal_mutex_t mutex)
{
    if(pdTRUE == xSemaphoreTake((SemaphoreHandle_t) mutex, (TickType_t)portMAX_DELAY))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//unlock the mutex
static bool_t  __mutex_unlock(osal_mutex_t mutex)
{
    if(pdPASS == xSemaphoreGive((SemaphoreHandle_t)mutex))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//delete the mutex
static bool_t  __mutex_del(osal_mutex_t mutex)
{
    if(mutex != NULL){
        vSemaphoreDelete((SemaphoreHandle_t)mutex);
    }
    mutex = NULL;
    return true;
}


///< this is implement for the semp
//semp of the os
static bool_t  __semp_create(osal_semp_t *semp,int limit,int initvalue)
{
    *semp = xSemaphoreCreateCounting(limit, initvalue);
	if( *semp != NULL)
    {
        return true;
    }else
    {
        return false;
    }
}
static bool_t  __semp_pend(osal_semp_t semp,int timeout)
{
    int ret = false;
    if(timeout == cn_osal_timeout_forever)
    {
        timeout = portMAX_DELAY;
    }
    ret = xSemaphoreTake((SemaphoreHandle_t)semp,(TickType_t)timeout);
    if (ret == pdTRUE) {
        return true;
    } else {
        return false;
    }
}
static bool_t  __semp_post(osal_semp_t semp)
{
    int ret = false;
    ret = xSemaphoreGive((SemaphoreHandle_t)semp);
    if (ret == pdTRUE) {
        return true;
    } else {
        return false;
    }
}
static bool_t  __semp_del(osal_semp_t semp)
{
    vSemaphoreDelete((SemaphoreHandle_t)semp);
    semp = NULL;
    return true;
}


///< this implement for the memory management
extern void *pvPortMalloc( size_t xWantedSize );
static void *__mem_malloc(int size)
{
    void *ret = NULL;
    if(size > 0)
    {
        ret = pvPortMalloc(size);
        if(NULL != ret)
        {
            return ret;
        }else
        {
            printf("malloc failed!!!\r\n");
        }
    }
}

extern void vPortFree(void *pv);
static void __mem_free(void *addr)
{
    
    if (addr != NULL)
    {
        vPortFree(addr);
        addr = NULL;
    }
}

static bool_t __queue_create(osal_queue_t *queue,int len,int msgsize)
{
   *queue = xQueueCreate(len, msgsize);
	if( *queue != NULL)
    {
        return true;
    }else
    {
        return false;
    }
}

static bool_t __queue_send(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout)
{
    BaseType_t ret = xQueueSend(queue, pbuf, timeout);
    if (ret == pdTRUE) {
        return true;
    } else {
        return false;
    }
}

static bool_t __queue_recv(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout)
{
    BaseType_t ret =  xQueueReceive(queue, pbuf, timeout);
    if (ret == pdTRUE) {
        return true;
    } else {
        return false;
    }
}

static bool_t __queue_del(osal_queue_t queue)
{
    vQueueDelete(queue);
    return true;
}

///< sys time
#define OS_SYS_MS_PER_SECOND                   1000
static unsigned long long __get_sys_time()
{
    return xTaskGetTickCount();
}

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
    //.realloc = NULL,

    .queue_create = __queue_create,
    .queue_send = __queue_send,
    .queue_recv = __queue_recv,
    .queue_del = __queue_del,

    .get_sys_time = __get_sys_time,

    //.reboot = NULL,
    //.int_connect = NULL,
};

static const tag_os s_link_cmsisos =
{
    .name = "FreeRTOS",
    .ops = &s_cmsisos_ops,
};

int os_imp_init(void)
{
    int ret = -1;
    ret = osal_install(&s_link_cmsisos);
    return ret;
}
