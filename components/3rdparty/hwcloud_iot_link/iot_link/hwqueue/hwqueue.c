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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <osal.h>


#include "hwqueue.h"

hwqueue_t* queue_create(const char *name,int len,int syncmode)
{
    hwqueue_t *ret;

    ret = osal_malloc(sizeof(hwqueue_t) + len*sizeof(void *));

    if(NULL == ret)
    {
        goto EXIT_MEM;
    }

    (void) memset(ret,0,sizeof(hwqueue_t));
    ret->name = name;
    ret->msg_buflen = len;
    ret->msg_buf = (void **)(uintptr_t)((uint8_t *)ret + sizeof(hwqueue_t));
    ret->sync_mode = syncmode;

    if(0 == syncmode)
    {
        goto EXIT_OK;
    }

    if(false == osal_semp_create(&ret->sync_read,len,0))
    {
        goto EXIT_SYNCREAD;
    }

    if(false == osal_semp_create(&ret->sync_write,len,len))
    {
        goto EXIT_SYNCWRITE;
    }

    if(false == osal_mutex_create(&ret->lock))
    {
        goto EXIT_LOCK;
    }


EXIT_OK:
    return ret;

EXIT_LOCK:
    (void) osal_semp_del(ret->sync_write);
EXIT_SYNCWRITE:
    (void) osal_semp_del(ret->sync_read);
EXIT_SYNCREAD:
    osal_free(ret);
    ret = NULL;
EXIT_MEM:
    ret = NULL;
    return ret;

}


static int raw_queue_pushdata(hwqueue_t *queue,void *data)
{
    int ret = -1;
    if(queue->msg_num < queue->msg_buflen)
    {
        queue->msg_buf[queue->cur_write] = data;
        queue->cur_write = (queue->cur_write + 1)%queue->msg_buflen;
        queue->msg_num ++;
        ret = 0;
    }

    return ret;
}

///< push a data to the queue, 0 success while -1 failed
int queue_push(hwqueue_t *queue,void *data,int timeout)
{
    int ret = -1;

    if((NULL == queue) || (NULL == data))
    {
        return ret;
    }
    if(queue->sync_mode)
    {
        if(osal_semp_pend(queue->sync_write,timeout))
        {
            if(osal_mutex_lock(queue->lock))
            {
                ret = raw_queue_pushdata(queue,data);
                (void) osal_mutex_unlock(queue->lock);
            }

            if(0 == ret)
            {
                (void) osal_semp_post(queue->sync_read);
            }
        }
    }
    else
    {
        ret = raw_queue_pushdata(queue,data);
    }
    return ret;

}

///< pop a data from the queue
static int raw_queue_pop(hwqueue_t *queue,void **buf)
{
    int ret = -1;
    if(queue->msg_num > 0)
    {
        *buf = queue->msg_buf[queue->cur_read];
        queue->cur_read = (queue->cur_read +1)%queue->msg_buflen;
        queue->msg_num--;
        ret = 0;
    }
    return ret;
}


int queue_pop(hwqueue_t *queue,void **buf, int timeout)
{
    int ret = -1;
    if((NULL == queue) || (NULL == buf))
    {
        return ret;
    }

    if(queue->sync_mode)
    {
        if(osal_semp_pend(queue->sync_read,timeout))
        {
            if(osal_mutex_lock(queue->lock))
            {
                ret = raw_queue_pop(queue,buf);
                (void) osal_mutex_unlock(queue->lock);
            }
            if(0 == ret)
            {
                (void) osal_semp_post(queue->sync_write);
            }
        }
    }
    else
    {
        ret = raw_queue_pop(queue,buf);
    }
    return ret;
}

///< delete the queue,if any data in the queue, which means could not kill it
int queue_delete(hwqueue_t *queue)
{
    int ret = -1;

    if((NULL == queue))
    {
        return ret;
    }
    if(queue->sync_mode)
    {
        (void) osal_semp_del(queue->sync_read);
        (void) osal_semp_del(queue->sync_write);
        (void) osal_mutex_del(queue->lock);
    }
    osal_free(queue);
    ret = 0;

    return ret;

}







