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


#ifndef __OS_AL_H
#define __OS_AL_H

#include <stdint.h>
#include <stddef.h>

#include <link_log.h>
#include <link_misc.h>
#include <osal_types.h>

//we need nothing here except the standard struct here
//kernel port here
//create a task:return the task handle here while -1 means create failed

/**
 * @brief:use this function to create a task here
 *
 * @param[in]:name, task name
 * @param[in]:task_entry, the task entry function
 * @param[in]:stack_size,the task stack size
 * @param[in]:stack, the stack memory, if NULL, which needed malloc by the system
 * @param[in]:args,the parameter pass to the entry function
 * @param[in]:prior,the prior if supported for the task;the bigger value, the lower prior
 *
 * @return:the task handle, while NULL failed
 *
 * */
void* osal_task_create(const char *name,int (*task_entry)(void *args),\
                      void *args,int stack_size,void *stack,int prior);

/**
 * @brief:use this funciton to kill the task
 *
 * @param[in]:task, the object get from task_create
 *
 * @return:0 success while false failed
 * */
int osal_task_kill(void *task);

/**
 * @brief:use this function  to exit from the current task
 *
 **/
void osal_task_exit();

/**
 * @brief:use this function to make the task to sleep
 *
 * @param[in]:ms, how much time to sleep, unit:ms
 *
 * @return:0 success while -1 failed
 **/
void osal_task_sleep(int ms);

/**
 *@brief: the mutex that the os must supplied for the link
 *
 **/

bool_t  osal_mutex_create(osal_mutex_t *mutex);
bool_t  osal_mutex_lock(osal_mutex_t mutex);
bool_t  osal_mutex_unlock(osal_mutex_t mutex);
bool_t  osal_mutex_del(osal_mutex_t mutex);

/**
 *@brief: the semp method that the os must supplied for the link
 *
 **/
bool_t  osal_semp_create(osal_semp_t *semp,int limit,int initvalue);
bool_t  osal_semp_pend(osal_semp_t semp,unsigned int timeout);
bool_t  osal_semp_post(osal_semp_t semp);
bool_t  osal_semp_del(osal_semp_t semp);


/**
 *@brief: the memory method that the os must supplied for the link
 *
 **/
void *osal_malloc(size_t size);
void  osal_free(void *addr);
void *osal_zalloc(size_t size);
void *osal_realloc(void *ptr,size_t newsize);
void *osal_calloc(size_t n, size_t size);


/**
 * @brief: use this function to get the system time
 *
 * @return:system time (unit ms)
 * */
unsigned long long osal_sys_time();

/**
 *
 * @brief: the loop soft timer
 * @param[in] : timer, the loop timer to be initialized
 *
 * */
void osal_loop_timer_init(osal_loop_timer_t *timer);

/**
 *
 * @brief: the loop soft timer
 * @param[in] : timer, the loop timer
 *
 * @return: true expired while false not expired
 *
 * */
char osal_loop_timer_expired(osal_loop_timer_t *timer);

/**
 *
 * @brief: the loop soft timer
 * @param[in]: timer, the loop timer
 * @param[in]: timeout, how many time to be expired,unit:second
 *
 * */
void osal_loop_timer_count_down(osal_loop_timer_t *timer, unsigned int timeout);
/**
 *
 * @brief: the loop soft timer
 * @param[in]: timer, the loop timer
 * @param[in]: timeout, how many time to be expired,unit:ms
 *
 * */
void osal_loop_timer_count_downms(osal_loop_timer_t *timer, unsigned int timeout);

/**
 *
 * @brief: the loop soft timer
 * @param[in]: timer, the loop timer
 * @return: how many ms to be expired
 * */
int osal_loop_timer_left(osal_loop_timer_t *timer);




/**
 * @brief:  you could use this function to do the system reboot
 *
 *
 * */
int osal_reboot(void);



int osal_int_connect(int intnum, int prio, int mode, fn_interrupt_handle callback, void *arg);

/**
 * @brief:use this function to initialize the os abstract layer
 *
 * @return:0 success while -1 failed
 * */
int osal_init(void);


#endif /* __OS_AL_H */
