/*
 * osal_imp.h
 *
 */

#ifndef __OSAL_IMP_H
#define __OSAL_IMP_H


#include <link_log.h>
#include <osal_types.h>

typedef struct
{
    ///< task function needed
    void* (*task_create)(const char *name,int (*task_entry)(void *args),\
                      void *args,int stack_size,void *stack,int prior);
    int   (*task_kill)(void *task);
    void  (*task_exit)();
    void  (*task_sleep)(int ms);

    ///< mutex function needed
    bool_t  (* mutex_create)(osal_mutex_t *mutex);
    bool_t  (* mutex_lock)(osal_mutex_t mutex);
    bool_t  (* mutex_unlock)(osal_mutex_t mutex);
    bool_t  (* mutex_del)(osal_mutex_t mutex);

    ///< semp function needed
    bool_t (*semp_create)(osal_semp_t *semp,int limit,int initvalue);
    bool_t (*semp_pend)(osal_semp_t semp,unsigned int timeout);
    bool_t (*semp_post)(osal_semp_t semp);
    bool_t (*semp_del)(osal_semp_t semp);

    ///< queue function needed
    bool_t (*queue_create)(osal_queue_t *queue,int len,int msgsize);
    bool_t (*queue_send)(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout);
    bool_t (*queue_recv)(osal_queue_t queue, void *pbuf, unsigned int bufsize, unsigned int timeout);
    bool_t (*queue_del)(osal_queue_t queue);

    ///< memory function needed
    void *(*mem_malloc)(int size);
    void  (*mem_free)(void *addr);
    void *(*realloc)(void *ptr, int newsize);


    ///< system time
    unsigned long long (*get_sys_time)(void);

    ///< reboot
    int (*reboot)(void); ///< never come back only if failed

    int (*int_connect)(int intnum, int prio, int mode, fn_interrupt_handle callback,void *arg);

}tag_os_ops;


typedef struct
{
    const char         *name;  ///< operation system name
    const tag_os_ops   *ops;   ///< system function interface
}tag_os;

int osal_install(const tag_os *os); //install the os to the link layer

int os_imp_init(void);   ///< this function must be implement by the developer, which will
                            ///< call osal_install to install your own operation system


#endif /* __OSAL_IMP_H */
