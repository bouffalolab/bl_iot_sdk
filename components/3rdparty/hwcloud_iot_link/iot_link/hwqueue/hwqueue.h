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

#ifndef HWQUEUE_H
#define HWQUEUE_H

#include <osal.h>


//////////////////////////////LOOK OUT//////////////////////////////////////////
///this is a common queue, which means first in first out, if you want to specified
///its priority,please use message box
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    const     char   *name;     ///< queue name
    int               msg_buflen;   ///< how many message could be cached
    void            **msg_buf;      ///< the message buf
    int               cur_write;    ///< point to the position to write
    int               cur_read;     ///< point to the position to read
    int               msg_num;      ///< how many message has been cached
    ///< the multi thread  dealer, you could config it or not
    int               sync_mode;    ///< which means we do the sync or not
    osal_semp_t       sync_read;    ///< read will pend here if no message here
    osal_semp_t       sync_write;   ///< write will pend here if no space here
    osal_mutex_t      lock;         ///< used to lock the queue operation
}hwqueue_t;

/**
 * @brief: use this function to create a queue to communicate with other thread.
 * @param: name, this is a queue name
 * @param: len, this means how many message could be cached in the queue
 * @param: syncmode, if set to 1, it will create means use semp and mutex in the queue,
 *         and this queue type could not be used in the interrupt; else you do the synchronize your self
 *
 * @return: the queue you created or NULL failed for some reason
 * */
hwqueue_t* queue_create(const char *name,int len,int syncmode);

/**
 * @brief: use this function to push the message to the queue
 * @param: queue, the destination queue
 * @param: data, the data you want to cached
 * @param: timeout, if any space, we would not wait; else we will wait until any space release within the timeout
 *         and its unit is mini second
 *
 * @return:0 success while -1 failed (timeout)
 * */
int queue_push(hwqueue_t *queue,void *data,int timeout);


/**
 * @brief: use this function to pop a message from the queue
 * @param: queue, the source queue
 * @param: buf, used to storage the data we cached
 * @param: timeout, if any message, we would not wait; else we will wait until any message cached  within the timeout
 *         and its unit is mini second
 * @return:the data you cached
 * */
int queue_pop(hwqueue_t *queue,void **buf,int timeout);

/**
 * @brief: use this function delete the queue you created
 * @param: queue, the queue we want to delete
 * @return: 0 success while -1 failed
 * */
int queue_delete(hwqueue_t *queue);



#endif /* HWQUEUE_H */
