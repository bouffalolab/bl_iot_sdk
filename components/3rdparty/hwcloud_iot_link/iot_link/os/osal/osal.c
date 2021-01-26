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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


#include <string.h>

#include <osal_imp.h>
#include <osal.h>

static const tag_os *s_os_cb = NULL;

int osal_install(const tag_os *os)
{
    int ret = -1;

    if(NULL == s_os_cb)
    {
        s_os_cb = os;
        ret = 0;
    }

    return ret;
}


void* osal_task_create(const char *name,int (*task_entry)(void *args),\
                      void *args,int stack_size,void *stack,int prior)
{
    void *ret = NULL;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->task_create))
    {
        ret = s_os_cb->ops->task_create(name, task_entry,args,stack_size,stack,prior);
    }

    return ret;
}


int osal_task_kill(void *task)
{
    int ret = -1;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->task_kill))
    {
        ret = s_os_cb->ops->task_kill(task);
    }

    return ret;

}


void osal_task_exit()
{

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->task_exit))
    {
        s_os_cb->ops->task_exit();
    }
    return ;

}


void osal_task_sleep(int ms)
{
    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->task_sleep))
    {
        s_os_cb->ops->task_sleep(ms);
    }

    return ;

}


bool_t  osal_mutex_create(osal_mutex_t *mutex)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mutex_create))
    {
        ret = s_os_cb->ops->mutex_create(mutex);
    }

    return ret;

}


bool_t  osal_mutex_lock(osal_mutex_t mutex)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mutex_lock))
    {
        ret = s_os_cb->ops->mutex_lock(mutex);
    }

    return ret;

}


bool_t  osal_mutex_unlock(osal_mutex_t mutex)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mutex_unlock))
    {
        ret = s_os_cb->ops->mutex_unlock(mutex);
    }

    return ret;

}

bool_t  osal_mutex_del(osal_mutex_t mutex)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mutex_del))
    {
        ret = s_os_cb->ops->mutex_del(mutex);
    }

    return ret;

}

bool_t  osal_semp_create(osal_semp_t *semp,int limit,int initvalue)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->semp_create))
    {
        ret = s_os_cb->ops->semp_create(semp,limit,initvalue);
    }

    return ret;

}

bool_t  osal_semp_pend(osal_semp_t semp,unsigned int timeout)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->semp_pend))
    {
        ret = s_os_cb->ops->semp_pend(semp,timeout);
    }

    return ret;

}


bool_t  osal_semp_post(osal_semp_t semp)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->semp_post))
    {
        ret = s_os_cb->ops->semp_post(semp);
    }

    return ret;

}

bool_t  osal_semp_del(osal_semp_t semp)
{
    bool_t ret = false;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->semp_del))
    {
        ret = s_os_cb->ops->semp_del(semp);
    }

    return ret;

}



void *osal_malloc(size_t size)
{
    void *ret = NULL;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mem_malloc))
    {
        ret = s_os_cb->ops->mem_malloc(size);
    }

    return ret;

}

void  osal_free(void *addr)
{

    if((NULL != addr) && (NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mem_free))
    {
        s_os_cb->ops->mem_free(addr);
    }

    return;
}

void *osal_zalloc(size_t size)
{
    void *ret = NULL;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->mem_malloc))
    {
        ret = s_os_cb->ops->mem_malloc(size);
        if(NULL != ret)
        {
            (void) memset(ret,0,size);
        }
    }

    return ret;

}

void *osal_realloc(void *ptr,size_t newsize)
{
    void *ret = NULL;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->realloc))
    {
        ret = s_os_cb->ops->realloc(ptr,newsize);
    }

    return ret;
}



void *osal_calloc(size_t n, size_t size)
{
    void *ret = NULL;
    size_t len;
    len = n*size;

    ret = malloc(len);
    if(NULL != ret)
    {
        (void) memset(ret, 0,len);
    }

    return ret;
}



unsigned long long osal_sys_time()
{

    unsigned long long  ret = 0;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->get_sys_time))
    {
        ret = s_os_cb->ops->get_sys_time();
    }

    return ret;
}

void osal_loop_timer_init(osal_loop_timer_t *timer)
{
    timer->dead_time = osal_sys_time();
}

char osal_loop_timer_expired(osal_loop_timer_t *timer)
{
    unsigned long long now = osal_sys_time();
    return now >= timer->dead_time;
}

void osal_loop_timer_count_downms(osal_loop_timer_t *timer, unsigned int timeout)
{
    unsigned long long now = osal_sys_time();
    timer->dead_time = now + timeout;
}


void osal_loop_timer_count_down(osal_loop_timer_t *timer, unsigned int timeout)
{
    osal_loop_timer_count_downms(timer,timeout*1000);
}

int osal_loop_timer_left(osal_loop_timer_t *timer)
{
    unsigned long long now = osal_sys_time();
    return timer->dead_time <= now ? 0 : timer->dead_time - now;
}




int osal_reboot()  ///< maybe we should never come back
{
    int ret = -1;

    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->reboot))
    {
        ret = s_os_cb->ops->reboot();
    }

    return ret;
}



int osal_int_connect(int intnum, int prio, int mode, fn_interrupt_handle callback, void *arg)
{
    int ret = -1;
    if((NULL != s_os_cb) &&(NULL != s_os_cb->ops) &&(NULL != s_os_cb->ops->int_connect))
    {
        ret = s_os_cb->ops->int_connect(intnum, prio, mode, callback, arg);
	}

    return ret;
}

#if 0 //
__attribute__((weak))  int os_imp_init(void)
{
    LINK_LOG_DEBUG("%s:###please implement this function by yourself####\n\r",__FUNCTION__);
    return -1;
}
#endif

int osal_init(void)
{
    int ret = -1;
    ret = os_imp_init();
    return ret;
}

