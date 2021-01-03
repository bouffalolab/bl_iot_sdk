/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _AT_PRIVATE_H_
#define _AT_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AT_MAX_PEER_NUM 5
#define AT_CMD_MAX_SIZE 32
#define AT_SOCKET_BUFFER_SIZE   1024L
#define MAX_DUMP_BUFF_SIZE  1024L

#define CMD_CACHE_MAX_LEN (1024)
#define CMD_SEND_DATA_MAX_LEN (1024 + 4)
#define CMD_SEND_TIMEOUT (10)

#define WLAN_SSID_MAX_LEN 32
#define SYSINFO_SSID_LEN_MAX        (32)
#define SYSINFO_PSK_LEN_MAX         (65)

#define MAX_SCAN_RESULTS 50
#define IP_ADDR_SIZE 15
#define PATH_MAX_LEN 64

#define ANL_WINDOWS 0
#define ANL_UNIX    1
#define ANL_MAC     2

#ifndef BIT
#define BIT(bit)                  (1u << (bit))
#endif
#define BIT_ISSET(data, bit)      ((data) & BIT(bit))
#define BIT_GET(data, bit)        (BIT_ISSET(data, bit) ? 1 : 0)

#ifndef NULL
#define NULL ((void *)0)
#endif

#define SIZE_LIMIT_MASK ((AT_PARA_MAX_SIZE<<1)-1)
#define SIZE_LIMIT(opt) ((opt) & SIZE_LIMIT_MASK)
/* #define END_PARA(opt)    ((((opt) & AET_PARA)!=0)?1:0) */
/* #define END_LINE(opt)    ((((opt) & AET_LINE)!=0)?1:0) */

typedef enum {
    APT_TEXT, /* text */
    APT_TDATA,
    APT_HEX, /* hex format data */
    APT_DI, /* decimal integer */
    APT_HI, /* hexadecimal integer */
    APT_IP, /* ip format data */
} AT_PARA_TYPE;

typedef enum {
    APO_RO, /* read only */
    APO_RW, /* read and write */
} AT_PARA_OPTION;

typedef enum {
    AET_PARA=AT_PARA_MAX_SIZE<<2,
    AET_LINE=AT_PARA_MAX_SIZE<<3,
} AT_END_TYPE;

typedef enum {
    AM_CMD=0,
    AM_DATA,
} AT_MODE;

typedef struct {
    AT_PARA_TYPE pt; /* parameter type */
    void *pvar; /* the pointer to the variable */
    u32 option; /* <end type> | <size limit> */
} at_para_descriptor_t;

typedef union {
    at_text_t text[AT_PARA_MAX_SIZE];
    at_hex_t hex[AT_PARA_MAX_SIZE];
    at_di_t di;
    at_hi_t hi;
    at_ip_t ip;
} at_value_t;

typedef struct {
    char *key;  /* variable keyword */
    AT_PARA_TYPE pt; /* parameter type */
    AT_PARA_OPTION po; /* parameter option */
    void *pvar; /* pointer to variable */
    s32 vsize; /* data size limit */
    s32 (*verify)(at_value_t *value); /* check data range */
} at_var_descriptor_t; /* variable descriptor */

#ifdef __cplusplus
}
#endif

#endif

