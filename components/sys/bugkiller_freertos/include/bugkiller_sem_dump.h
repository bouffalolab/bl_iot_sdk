#ifndef __SEM_DUMP_H__
#define __SEM_DUMP_H__
#include <list.h>
#include <queue.h>
#include <semphr.h>

void bugkiller_sem_dump(void *res);
typedef struct tskTaskControlBlock
{
	volatile StackType_t	*pxTopOfStack;
	#if ( portUSING_MPU_WRAPPERS == 1 )
		xMPU_SETTINGS	xMPUSettings;	
	#endif

	ListItem_t			xStateListItem;
	ListItem_t			xEventListItem;
	UBaseType_t			uxPriority;	
	StackType_t			*pxStack;
	char				pcTaskName[ configMAX_TASK_NAME_LEN ];
	#if ( ( portSTACK_GROWTH > 0 ) || ( configRECORD_STACK_HIGH_ADDRESS == 1 ) )
		StackType_t		*pxEndOfStack;
	#endif

	#if ( portCRITICAL_NESTING_IN_TCB == 1 )
		UBaseType_t		uxCriticalNesting;
	#endif

	#if ( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t		uxTCBNumber;	
		UBaseType_t		uxTaskNumber;
	#endif

	#if ( configUSE_MUTEXES == 1 )
		UBaseType_t		uxBasePriority;
		UBaseType_t		uxMutexesHeld;
	#endif

	#if ( configUSE_APPLICATION_TASK_TAG == 1 )
		TaskHookFunction_t pxTaskTag;
	#endif

	#if( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
		void			*pvThreadLocalStoragePointers[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
	#endif

	#if( configGENERATE_RUN_TIME_STATS == 1 )
		uint32_t		ulRunTimeCounter;
	#endif

	#if ( configUSE_NEWLIB_REENTRANT == 1 )
		struct	_reent xNewLib_reent;
	#endif

	#if( configUSE_TASK_NOTIFICATIONS == 1 )
		volatile uint32_t ulNotifiedValue;
		volatile uint8_t ucNotifyState;
	#endif

	#if( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) 
		uint8_t	ucStaticallyAllocated;
	#endif

	#if( INCLUDE_xTaskAbortDelay == 1 )
		uint8_t ucDelayAborted;
	#endif

	#if( configUSE_POSIX_ERRNO == 1 )
		int iTaskErrno;
	#endif

} tskTCB;
typedef tskTCB TCB_t;
#endif
