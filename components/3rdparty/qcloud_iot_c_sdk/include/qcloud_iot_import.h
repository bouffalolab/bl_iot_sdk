/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2018-2020 THL A29 Limited, a Tencent company. All rights
 reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#ifndef QCLOUD_IOT_IMPORT_H_
#define QCLOUD_IOT_IMPORT_H_
#if defined(__cplusplus)
extern "C" {
#endif

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "platform.h"

#define _IN_ /* indicate an input parameter */
#define _OU_ /* indicate a output parameter */

#define IOT_TRUE  (1) /* indicate boolean value true */
#define IOT_FALSE (0) /* indicate boolean value false */

#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))

/**********************************************************************
 * QCloud IoT C-SDK Hardware Abstraction Layer
 * Platform/OS/IP stack/SSL dependant functions
 * Check platform folder for reference implementaions
 * Require porting when adapt SDK to new platform/OS
 *********************************************************************/

typedef void (*ThreadRunFunc)(void *arg);

typedef struct ThreadParams {
    char *        thread_name;
    size_t        thread_id;
    ThreadRunFunc thread_func;
    void *        user_arg;
    uint16_t      priority;
    uint32_t      stack_size;
} ThreadParams;

/**
 * @brief Create a thread/task
 *
 * @param params    thread parameters
 * @return 0 when success, or error code otherwise
 */
int HAL_ThreadCreate(ThreadParams *params);

/**
 * @brief Destroy a thread/task
 *
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_ThreadDestroy(void *thread_t);

/**
 * @brief create semaphore
 *
 * @return a valid semaphore handle when success, or NULL otherwise
 */
void *HAL_SemaphoreCreate(void);

/**
 * @brief Destroy semaphore
 * @param sem   semaphore handle
 */
void HAL_SemaphoreDestroy(void *sem);

/**
 * @brief Post semaphore
 * @param sem   semaphore handle
 */
void HAL_SemaphorePost(void *sem);

/**
 * @brief Wait for semaphore
 * @param sem           semaphore handle
 * @param timeout_ms    waiting timeout value (unit: ms)
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_SemaphoreWait(void *sem, uint32_t timeout_ms);

/**
 * @brief Create mutex
 *
 * @return a valid mutex handle when success, or NULL otherwise
 */
void *HAL_MutexCreate(void);

/**
 * @brief Destroy mutex
 *
 * @param mutex     mutex handle
 */
void HAL_MutexDestroy(_IN_ void *mutex);

/**
 * @brief Lock a mutex in blocking way
 *
 * @param mutex     mutex handle
 */
void HAL_MutexLock(_IN_ void *mutex);

/**
 * @brief Lock a mutex in non-blocking way
 *
 * @param mutex     mutex handle
 * @return 0 for success, or err code for failure
 */
int HAL_MutexTryLock(_IN_ void *mutex);

/**
 * @brief Unlock/release mutex
 *
 * @param mutex     mutex handle
 */
void HAL_MutexUnlock(_IN_ void *mutex);

/**
 * @brief Malloc memory
 *
 * @param size   Expected memory size (unit: byte)
 * @return       pointer to the memory
 */
void *HAL_Malloc(_IN_ uint32_t size);

/**
 * @brief Free memory
 *
 * @param ptr   pointer to the pre-malloc memory
 */
void HAL_Free(_IN_ void *ptr);

/**
 * @brief Print data to console in format
 *
 * @param fmt   print format
 * @param ...   variable number of arguments
 */
void HAL_Printf(_IN_ const char *fmt, ...);

/**
 * @brief Print data to string in format
 *
 * @param str   destination string
 * @param len   Max size of the output
 * @param fmt   print format
 * @param ...   variable number of arguments
 * @return      number of bytes that print successfull
 */
int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...);

/**
 Print data to string in format
  *
  * @param str   destination string
  * @param len   Max size of the output
  * @param fmt   print format
  * @param ap    arguments list
  * @return      number of bytes that print successfull

 */
int HAL_Vsnprintf(_OU_ char *str, _IN_ const int len, _IN_ const char *fmt, _IN_ va_list ap);

/**
 * @brief Get timestamp in millisecond
 *
 * @return   timestamp in millisecond
 */
uint32_t HAL_GetTimeMs(void);

/**
 * @brief Delay operation in blocking way
 *
 * @param ms sleep interval in millisecond
 */
void HAL_DelayMs(_IN_ uint32_t ms);

/**
 * @brief Sleep for a while
 *
 * @param ms sleep interval in millisecond
 */
void HAL_SleepMs(_IN_ uint32_t ms);

/**
 * @brief Set device info to NVS(flash/files)
 *
 * @param pdevInfo reference to device info
 * @return         QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_SetDevInfo(void *pdevInfo);

/**
 * @brief Get device info from NVS(flash/files)
 *
 * @param pdevInfo reference to device info
 * @return         QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_GetDevInfo(void *pdevInfo);

/**
 * @brief Get device info from a JSON file
 *
 * @param file_name JSON file path
 * @param pdevInfo reference to device info
 * @return         QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_GetDevInfoFromFile(const char *file_name, void *dev_info);

#ifdef GATEWAY_ENABLED
/**
 * @brief Get gateway device info from NVS(flash/files)
 *
 * @param pgwDeviceInfo reference to gateway device info
 * @return         QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_GetGwDevInfo(void *pgwDeviceInfo);
#endif

/**
 * @brief Set the name of file which contain device info
 *
 * @param file_name the name of file which contain device info
 * @return         QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_SetDevInfoFile(const char *file_name);

/**
 * Define timer structure, platform dependant
 */
struct Timer {
#if defined(__linux__) && defined(__GLIBC__)
    struct timeval end_time;
#else
    uintptr_t end_time;
#endif
};

typedef struct Timer Timer;

/**
 * @brief Check if timer expires or not
 *
 * @param timer     reference to timer
 * @return          true = expired, false = not expired yet
 */
bool HAL_Timer_expired(Timer *timer);

/**
 * @brief Set the countdown/expired value for the timer
 *
 * @param timer         reference to timer
 * @param timeout_ms    countdown/expired value (unit: millisecond)
 */
void HAL_Timer_countdown_ms(Timer *timer, unsigned int timeout_ms);

/**
 * @brief Set the countdown/expired value for the timer
 *
 * @param timer         reference to timer
 * @param timeout       countdown/expired value (unit: second)
 */
void HAL_Timer_countdown(Timer *timer, unsigned int timeout);

/**
 * @brief Check the remain time of the timer
 *
 * @param timer     reference to timer
 * @return          0 if expired, or the left time in millisecond
 */
int HAL_Timer_remain(Timer *timer);

/**
 * @brief Init the timer
 *
 * @param timer reference to timer
 */
void HAL_Timer_init(Timer *timer);

#define TIME_FORMAT_STR_LEN (20)
/**
 * @brief Get local time in format: %y-%m-%d %H:%M:%S
 *
 * @return string of formatted time
 */
char *HAL_Timer_current(char *time_str);

/**
 * @brief Get timestamp in second
 *
 * @return   timestamp in second
 */
long HAL_Timer_current_sec(void);

#ifdef AT_TCP_ENABLED
int       HAL_AT_TCP_Init(void);
uintptr_t HAL_AT_TCP_Connect(const char *host, uint16_t port);
int       HAL_AT_TCP_Disconnect(uintptr_t fd);
int HAL_AT_TCP_Write(uintptr_t fd, const unsigned char *buf, uint32_t len, uint32_t timeout_ms, size_t *written_len);
int HAL_AT_TCP_Read(uintptr_t fd, uint8_t *buf, uint32_t len, uint32_t timeout_ms, uint32_t *read_len);
int at_device_init(void);
int HAL_AT_Uart_Init(void);
int HAL_AT_Uart_Deinit(void);
int HAL_AT_Uart_Send(void *data, uint32_t size);
int HAL_AT_Uart_Recv(void *data, uint32_t expect_size, uint32_t *recv_size, uint32_t timeout);
#endif

/********** TLS/DTLS network sturcture and operations **********/
#ifndef AUTH_WITH_NOTLS

#ifndef MAX_SIZE_OF_CLIENT_ID
#define MAX_SIZE_OF_CLIENT_ID (80)
#endif
/**
 * @brief Define structure for TLS connection parameters
 *
 */
typedef struct {
    const char *ca_crt;
    uint16_t    ca_crt_len;

#ifdef AUTH_MODE_CERT
    /**
     * Device with certificate
     */
    const char *cert_file;  // public certificate file
    const char *key_file;   // pravite certificate file
#else
    /**
     * Device with PSK
     */
    const char *psk;                                // PSK string
    char        psk_id[MAX_SIZE_OF_CLIENT_ID + 1];  // PSK ID
#endif

    size_t psk_length;  // PSK length

    unsigned int timeout_ms;  // SSL handshake timeout in millisecond

} SSLConnectParams;

typedef SSLConnectParams TLSConnectParams;

/**
 * @brief Setup TLS connection with server
 *
 * @param   pConnectParams reference to TLS connection parameters
 * @host    server address
 * @port    server port
 * @return  TLS connect handle when success, or 0 otherwise
 */
uintptr_t HAL_TLS_Connect(TLSConnectParams *pConnectParams, const char *host, int port);

/**
 * @brief Disconnect with TLS server and release resources
 *
 * @param handle TLS connect handle
 */
void HAL_TLS_Disconnect(uintptr_t handle);

/**
 * @brief Write data via TLS connection
 *
 * @param handle        TLS connect handle
 * @param data          source data to write
 * @param totalLen      length of data
 * @param timeout_ms    timeout value in millisecond
 * @param written_len   length of data written successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_TLS_Write(uintptr_t handle, unsigned char *data, size_t totalLen, uint32_t timeout_ms, size_t *written_len);

/**
 * @brief Read data via TLS connection
 *
 * @param handle        TLS connect handle
 * @param data          destination data buffer where to put data
 * @param totalLen      length of data
 * @param timeout_ms    timeout value in millisecond
 * @param read_len      length of data read successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_TLS_Read(uintptr_t handle, unsigned char *data, size_t totalLen, uint32_t timeout_ms, size_t *read_len);

/********** DTLS network **********/
#ifdef COAP_COMM_ENABLED
typedef SSLConnectParams DTLSConnectParams;

/**
 * @brief Setup DTLS connection with server
 *
 * @param   pConnectParams reference to DTLS connection parameters
 * @host    server address
 * @port    server port
 * @return  DTLS connect handle when success, or 0 otherwise
 */
uintptr_t HAL_DTLS_Connect(DTLSConnectParams *pConnectParams, const char *host, int port);

/**
 * @brief Disconnect with DTLS server and release resources
 *
 * @param handle DTLS connect handle
 */
void HAL_DTLS_Disconnect(uintptr_t handle);

/**
 * @brief Write data via DTLS connection
 *
 * @param handle        DTLS connect handle
 * @param data          source data to write
 * @param totalLen      length of data
 * @param timeout_ms    timeout value in millisecond
 * @param written_len   length of data written successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_DTLS_Write(uintptr_t handle, const unsigned char *data, size_t datalen, size_t *written_len);

/**
 * @brief Read data via DTLS connection
 *
 * @param handle        DTLS connect handle
 * @param data          destination data buffer where to put data
 * @param totalLen      length of data
 * @param timeout_ms    timeout value in millisecond
 * @param read_len      length of data read successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_DTLS_Read(uintptr_t handle, unsigned char *data, size_t datalen, uint32_t timeout_ms, size_t *read_len);

#endif  // COAP_COMM_ENABLED
#endif  // AUTH_WITH_NOTLS

/********** TCP network **********/
/**
 * @brief Setup TCP connection with server
 *
 * @host    server address
 * @port    server port
 * @return  TCP socket handle (value>0) when success, or 0 otherwise
 */
uintptr_t HAL_TCP_Connect(const char *host, uint16_t port);

/**
 * @brief Disconnect with server and release resource
 *
 * @param fd TCP Socket handle
 * @return  0 when success
 */
int HAL_TCP_Disconnect(uintptr_t fd);

/**
 * @brief Write data via TCP connection
 *
 * @param fd            TCP socket handle
 * @param data          source data to write
 * @param len           length of data
 * @param timeout_ms    timeout value in millisecond
 * @param written_len   length of data written successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_TCP_Write(uintptr_t fd, const unsigned char *data, uint32_t len, uint32_t timeout_ms, size_t *written_len);

/**
 * @brief Read data via TCP connection
 *
 * @param fd            TCP socket handle
 * @param data          destination data buffer where to put data
 * @param len           length of data
 * @param timeout_ms    timeout value in millisecond
 * @param read_len      length of data read successfully
 * @return              QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_TCP_Read(uintptr_t fd, unsigned char *data, uint32_t len, uint32_t timeout_ms, size_t *read_len);

/********** UDP network **********/
#ifdef COAP_COMM_ENABLED
/**
 * @brief Setup UDP connection with server
 *
 * @host    server address
 * @port    server port
 * @return  UPD socket handle (value>0) when success, or 0 otherwise
 */
uintptr_t HAL_UDP_Connect(const char *host, unsigned short port);

/**
 * @brief Disconnect with server and release resource
 *
 * @param fd UDP Socket handle
 * @return  0 when success
 */
void HAL_UDP_Disconnect(uintptr_t fd);

/**
 * @brief Write data via UDP connection
 *
 * @param fd            UDP socket handle
 * @param data          source data to write
 * @param len           length of data
 * @return              length of data written when success, or err code for
 * failure
 */
int HAL_UDP_Write(uintptr_t fd, const unsigned char *data, unsigned int len);

/**
 * @brief Read data via UDP connection
 *
 * @param fd            UDP socket handle
 * @param data          destination data buffer where to put data
 * @param len           length of data
 * @return              length of data read when success, or err code for
 * failure
 */
int HAL_UDP_Read(uintptr_t fd, unsigned char *data, unsigned int len);

/**
 * @brief Read data via UDP connection
 *
 * @param fd            UDP socket handle
 * @param data          destination data buffer where to put data
 * @param len           length of data
 * @param timeout_ms    timeout value in millisecond
 * @return              length of data read when success, or err code for
 * failure
 */
int HAL_UDP_ReadTimeout(uintptr_t fd, unsigned char *p_data, unsigned int datalen, unsigned int timeout_ms);
#endif  // COAP_COMM_ENABLED

#ifdef LOG_UPLOAD
/* Functions for saving/reading logs into/from NVS(files/FLASH) after log upload
 * fail/recover */
/**
 * @brief Functions for saving logs into NVS(files/FLASH) after log upload fail
 * @param log           source log buffer
 * @param len           length of log to save
 * @return              length of data save when success, or 0 for failure
 */
size_t HAL_Log_Save(const char *log, size_t len);

/**
 * @brief Functions for reading logs from NVS(files/FLASH) when log upload ready
 * @param buf           destination log buffer
 * @param len           length of log to read
 * @return              length of data read when success, or 0 for failure
 */
size_t HAL_Log_Read(char *buf, size_t len);

/**
 * @brief Functions for deleting logs in NVS(files/FLASH).
 * @return              0 when success
 */
int HAL_Log_Del(void);

/**
 * @brief Functions for reading the size of logs in NVS(files/FLASH).
 * @return              0 when nothing exist
 */
size_t HAL_Log_Get_Size(void);
#endif

/**
 * @brief Opens the filename pointed to by filename using the given mode.
 */
void *HAL_FileOpen(const char *filename, const char *mode);

/**
 * @brief Reads data from the given stream into the array pointed to by ptr.
 */
size_t HAL_FileRead(void *ptr, size_t size, size_t nmemb, void *fp);

/**
 * @brief Writes data from the array pointed to by ptr to the given stream.
 */
size_t HAL_FileWrite(const void *ptr, size_t size, size_t nmemb, void *fp);

/**
 * @brief Sets the file position of the stream to the given offset. The argument
 * offset signifies the number of bytes to seek from the given whence position.
 */
int HAL_FileSeek(void *fp, long int offset, int whence);

/**
 * @brief Closes the stream. All buffers are flushed.
 */
int HAL_FileClose(void *fp);

/**
 * @brief Deletes the given filename so that it is no longer accessible.
 */
int HAL_FileRemove(const char *filename);

/**
 * @brief Sets the file position to the beginning of the file of the given stream.
 */
int HAL_FileRewind(void *fp);

/**
 * @brief Causes the filename referred to, by old_filename to be changed to new_filename
 */
int HAL_FileRename(const char *old_filename, const char *new_filename);

/**
 * @brief Tests the end-of-file indicator for the given stream.
 */
int HAL_FileEof(void *fp);

/**
 * @brief Get the current pose of stream.
 */
long HAL_FileTell(void *fp);

/**
 * @brief Get the stream size.
 */
long HAL_FileSize(void *fp);

/**
 * @brief Get one line from the stream.
 */
char *HAL_FileGets(char *str, int n, void *fp);

/**
 * @brief Flushes the output buffer of a stream.
 */
int HAL_FileFlush(void *fp);

#if defined(__cplusplus)
}
#endif
#endif /* QCLOUD_IOT_IMPORT_H_ */
