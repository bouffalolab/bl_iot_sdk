# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include/FreeRTOS_POSIX

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src
COMPONENT_SRCS := src/FreeRTOS_POSIX_clock.c \
				  src/FreeRTOS_POSIX_pthread_barrier.c \
				  src/FreeRTOS_POSIX_pthread_cond.c \
				  src/FreeRTOS_POSIX_sched.c \
				  src/FreeRTOS_POSIX_timer.c \
				  src/FreeRTOS_POSIX_utils.c \
				  src/FreeRTOS_POSIX_mqueue.c \
				  src/FreeRTOS_POSIX_pthread.c \
				  src/FreeRTOS_POSIX_pthread_mutex.c \
				  src/FreeRTOS_POSIX_semaphore.c \
				  src/FreeRTOS_POSIX_unistd.c \
				  src/os_hal.c 

COMPONENT_OBJS := $(patsubst %.c,%.o, $(COMPONENT_SRCS))

COMPONENT_SRCDIRS := src


##
#CPPFLAGS +=
