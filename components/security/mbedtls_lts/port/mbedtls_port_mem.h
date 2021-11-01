#ifndef MBEDTLS_PORT_MEM_H_9E8RSFXZ
#define MBEDTLS_PORT_MEM_H_9E8RSFXZ

#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>

#define MBEDTLS_PLATFORM_FREE_MACRO vPortFree
#define MBEDTLS_PLATFORM_CALLOC_MACRO mbedtls_port_calloc

#define MBEDTLS_PLATFORM_FPRINTF_MACRO fprintf
#define MBEDTLS_PLATFORM_PRINTF_MACRO printf
#define MBEDTLS_PLATFORM_SNPRINTF_MACRO snprintf
#define MBEDTLS_PLATFORM_EXIT_MACRO exit

void *mbedtls_port_calloc( size_t nmemb, size_t size );

#endif /* end of include guard: MBEDTLS_PORT_MEM_H_9E8RSFXZ */
