#ifndef __HAL_SYS_H__
#define __HAL_SYS_H__
void hal_reboot();
void hal_sys_reset();
void hal_poweroff();

struct romapi_freertos_map
{
    void *rtos_strlen_ptr;
    void *rtos_sprintf;
    void *rtos_memset_ptr;
    void *exception_entry_ptr;
    void *rtos_clz;
    void *vApplicationGetTimerTaskMemory;
    void *vApplicationMallocFailedHook;
    void *vApplicationTickHook;
    void *rtos_memcpy_ptr;
    void *vAssertCalled;
    void *vApplicationGetIdleTaskMemory;
    void *vApplicationStackOverflowHook;
    void *rtos_strcpy_ptr;
    void *interrupt_entry_ptr;
    void *vApplicationSleep;
    void *vApplicationIdleHook;
    void *xISRStackTop;
};

struct romapi_freertos_map* hal_sys_romapi_get(void);
void hal_sys_romapi_update(struct romapi_freertos_map *romapi);
void hal_sys_capcode_update(uint8_t capin, uint8_t capout);
uint8_t hal_sys_capcode_get(void);

#endif
