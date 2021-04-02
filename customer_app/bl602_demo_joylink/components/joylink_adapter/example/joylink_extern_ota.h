/* --------------------------------------------------
 * @file: joylink_extern_ota.h
 *
 * @brief: 
 *
 * @version: 2.0
 *
 * @date: 2018/07/26 PM
 *
 * --------------------------------------------------
 */

#ifndef _JOYLINK_EXTERN_OTA_H_
#define _JOYLINK_EXTERN_OTA_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "joylink_extern.h"
//#define HTTP_URL "http://storage.360buyimg.com/devh5/micapp_ota_9_1532350290755.bin"

#define OTA_STATUS_DOWNLOAD 0
#define OTA_STATUS_INSTALL  1
#define OTA_STATUS_SUCCESS  2
#define OTA_STATUS_FAILURE  3

//#define OTA_PACKET_NUMB  1

#define HTTP_DEFAULT_PORT 80

#define EVERY_PACKET_LEN  1024 // XXX: MUST BE A MULTIPLE OF 4, AND >= 512

#define OTA_TIME_OUT (5 * 60 * 1000)
#define HTTP_GET "GET /%s HTTP/1.1\r\nHOST: %s\r\nAccept: */*\r\n\r\n"

typedef struct _http_ota_st
{
    char url[256];

    char host_name[64];
    int host_port;

    char file_path[64];
    char file_name[64];

    long int file_size;
    long int file_offset;

    int finish_percent;
} http_ota_st;


void *joylink_ota_task(void *data);

void joylink_set_ota_info(JLOtaOrder_t *ota_info);

#ifdef __cplusplus
}
#endif

#endif
