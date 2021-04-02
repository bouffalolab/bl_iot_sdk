#ifndef __JOYLINK_SUB_DEV_H__
#define __JOYLINK_SUB_DEV_H__

#include <stdio.h>

#include <locale.h>
#include <stdlib.h>
#include <signal.h>

#include "joylink_socket.h"
#include "joylink_stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

#pragma pack(1)
typedef struct {
    unsigned int    timestamp;
    unsigned int    code;
}JLDataSubHbRsp_t;

typedef struct {
    unsigned int timestamp;
    unsigned char feedid[JL_MAX_FEEDID_LEN];
    unsigned int code;
}JLDataSubUploadRsp_t;

typedef struct {
    unsigned short  version;
    unsigned short  rssi;
    unsigned char   feedid[JL_MAX_FEEDID_LEN];
    unsigned char state;
}JLSubDevInfo_t;

typedef struct {
    unsigned int timestamp; 
    unsigned short  verion;
    unsigned short  rssi;
    unsigned short num;
    JLSubDevInfo_t sdevinfo[];
}JLSubHearBeat_t;

typedef struct {
    unsigned int timestamp;
    unsigned int biz_code;
    unsigned int     serial;
    char feedid [JL_MAX_FEEDID_LEN];
    unsigned char *cmd;
}JLSubContrl_t;

typedef struct {
    unsigned int    timestamp;
    unsigned int    biz_code;
    unsigned int    serial;
    unsigned short  num;
    JLSubDevInfo_t  *info;
}JLSubUnbind_t;

typedef struct {
    char uuid[8];
    char mac[17];

    short version;

    char state;
    char type;
    char lancon;
    char cmd_tran_type;

    char protocol;

    char feedid[33];
    char accesskey[33];
    char localkey[33];

    char pubkey[65];

    char devAuthValue[33];
    char cloudAuthValue[33];

    int subNoSnapshot;
}JLSubDevData_t;

#pragma pack()

/**
 * brief: 
 *
 * @Param: src
 * @Param: sin_recv
 * @Param: addrlen
 *
 * @Returns: 
 */
E_JLRetCode_t 
joylink_proc_lan_sub_add(uint8_t *src, jl_sockaddr_in *sin_recv, int addrlen);
// joylink_proc_lan_sub_add(uint8_t *src, struct sockaddr_in *sin_recv, socklen_t addrlen);

/**
 * brief: 
 *
 * @Param: src
 * @Param: sin_recv
 * @Param: addrlen
 *
 * @Returns: 
 */
E_JLRetCode_t 
joylink_proc_lan_sub_auth(uint8_t *src, jl_sockaddr_in *sin_recv, int addrlen);
// joylink_proc_lan_sub_auth(uint8_t *src, struct sockaddr_in *sin_recv, socklen_t addrlen);

/**
 * brief: 
 *
 * @Param: src
 * @Param: src_len
 * @Param: sin_recv
 * @Param: addrlen
 *
 * @Returns: 
 */
E_JLRetCode_t 
joylink_proc_lan_sub_script_ctrl(uint8_t *src, int src_len, jl_sockaddr_in *sin_recv, int addrlen);
// joylink_proc_lan_sub_script_ctrl(uint8_t *src, int src_len, struct sockaddr_in *sin_recv, socklen_t addrlen);

/**
 * brief: 
 *
 * @Returns: 
 */
int 
joylink_packet_check_sub_hb(void);
/**
 * brief: 
 *
 * @Returns: 
 */
int
joylink_packet_server_sub_hb_req(int index);

/**
 * brief: 
 *
 * @Param: recPainText
 * @Param: ctr
 * @Param: payloadlen
 *
 * @Returns: 
 */
int 
joylink_subdev_script_ctrl(uint8_t* recPainText, JLSubContrl_t *ctr, unsigned short payloadlen);

/**
 * brief: 
 *
 * @Param: data
 * @Param: max
 * @Param: ctrl
 *
 * @Returns: 
 */
int 
joylink_packet_subdev_script_ctrl_rsp(char *data, int max, JLSubContrl_t *ctrl);

/**
 * brief: 
 *
 * @Param: recPainText
 * @Param: unbind
 *
 * @Returns: 
 */
int
joylink_subdev_unbind(uint8_t* recPainText, JLSubUnbind_t* unbind);

/**
 * brief: 
 *
 * @Param: data
 * @Param: max
 * @Param: unbind
 *
 * @Returns: 
 */
int
joylink_packet_subdev_unbind_rsp(char* data, int max, JLSubUnbind_t* unbind);
#ifdef __cplusplus
}
#endif

#endif /* __SUB_DEV_H__*/
