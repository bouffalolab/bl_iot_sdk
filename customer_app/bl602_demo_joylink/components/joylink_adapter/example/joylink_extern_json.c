/* --------------------------------------------------
 * @brief: 
 *
 * @version: 1.0
 *
 * @date: 08/01/2018
 *
 * @author: 
 * --------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#include "joylink_log.h"
#include "joylink_extern.h"
#include "joylink_memory.h"
#include "joylink_socket.h"
#include "joylink_string.h"
#include "joylink_stdio.h"
#include "joylink_stdint.h"
#include "joylink_time.h"

#ifdef JOYLINK_SDK_EXAMPLE_MWO
static int cvt_hex_to_bin(const uint8_t *hex, uint8_t *bin, int len)
{
    int ping, pong;
    int ch;
    int i;
    if (!hex || !bin || !len || !(len % 2 == 0)) {
        return -1;
    }
    for (i = 0; i < len; i += 2) {
        ping = pong = 0;
        ch = hex[i];
        if ('0' <= ch && ch <= '9') {
            ping = ch - '0';
        } else if ('a' <= ch && ch <= 'f') {
            ping = ch - 'a' + 10;
        } else if ('A' <= ch && ch <= 'F') {
            ping = ch - 'A' + 10;
        } else {
            return -1;
        }

        ch = hex[i + 1];
        if ('0' <= ch && ch <= '9') {
            pong = ch - '0';
        } else if ('a' <= ch && ch <= 'f') {
            pong = ch - 'a' + 10;
        } else if ('A' <= ch && ch <= 'F') {
            pong = ch - 'A' + 10;
        } else {
            return -1;
        }
        bin[i / 2] = ping * 16 + pong;
    }

    return 0;
}
#endif

/**
 * brief: 
 *
 * @Param: pMsg
 * @Param: user_dev
 *
 * @Returns: 
 */
int 
joylink_dev_parse_ctrl(const char *pMsg, user_dev_status_t *userDev)
{
    int ret = -1;
#ifdef JOYLINK_SDK_EXAMPLE_MWO
    uint8_t cmd_bin[100];
    uint8_t cmd_bin2[100];
    int sl;
    int is_start_cmd = 0;
#endif
    if(NULL == pMsg || NULL == userDev){
        goto RET;
    }
#ifdef JOYLINK_SDK_EXAMPLE_MWO

    log_debug("CMD: %s", pMsg);
    sl = strlen(pMsg);
    if (sl >= 36 * 2) {
        if (cvt_hex_to_bin((uint8_t *)pMsg, cmd_bin, sl) == 0) {
            if (patch_uart_cmd(cmd_bin, sl / 2, &is_start_cmd)) {
                if (is_start_cmd) {
                    memcpy(cmd_bin2, cmd_bin, 36);
                    patch_start_cmd_to_standby(cmd_bin);
                }
                log_debug("[UART TX]: ");
                my_log_buf(cmd_bin, 36);
                jl_app_uart_send(jl_uart_ctx, cmd_bin, 36, 0);

                if (is_start_cmd) {
                    log_debug("[UART TX]: ");
                    my_log_buf(cmd_bin2, 36);
                    jl_app_uart_send(jl_uart_ctx, cmd_bin2, 36, 100);
                }
            }
        }
    }
#endif

#ifdef JOYLINK_SDK_EXAMPLE_TEST
    log_debug("json_org:%s", pMsg);
    cJSON * pSub;
    cJSON * pJson = cJSON_Parse(pMsg);

    if(NULL == pJson){
        log_error("--->:ERROR: pMsg is NULL\n");
        goto RET;
    }

    cJSON *pStreams = cJSON_GetObjectItem(pJson, "streams");
    if(NULL != pStreams){
        int iSize = cJSON_GetArraySize(pStreams);
        int iCnt;
        for( iCnt = 0; iCnt < iSize; iCnt++){
            pSub = cJSON_GetArrayItem(pStreams, iCnt);
            if(NULL == pSub){
                continue;
            }

            cJSON *pSId = cJSON_GetObjectItem(pSub, "stream_id");
            if(NULL == pSId){
                break;
            }
            cJSON *pV = cJSON_GetObjectItem(pSub, "current_value");
            if(NULL == pV){
                continue;
            }
            if(!jl_platform_strcmp(USER_DATA_POWER, pSId->valuestring)){
                if(pV->type == cJSON_String){
                userDev->Power = jl_platform_atoi(pV->valuestring);
                }
                else if(pV->type == cJSON_Number){
                    userDev->Power = pV->valueint;
                }
                joylink_dev_user_data_set( USER_DATA_POWER,userDev);
            }
            if(!jl_platform_strcmp(USER_DATA_MODE, pSId->valuestring)){
                if(pV->type == cJSON_String){
                userDev->Mode = jl_platform_atoi(pV->valuestring);
                }
                else if(pV->type == cJSON_Number){
                    userDev->Mode = pV->valueint;
                }
                joylink_dev_user_data_set( USER_DATA_MODE,userDev);
            }
            if(!jl_platform_strcmp(USER_DATA_STATE, pSId->valuestring)){
                if(pV->type == cJSON_String){
                userDev->State = jl_platform_atoi(pV->valuestring);
                }
                else if(pV->type == cJSON_Number){
                    userDev->State = pV->valueint;
                }
                joylink_dev_user_data_set( USER_DATA_STATE,userDev);
            }

            char *dout = cJSON_PrintUnformatted(pSub);
            if(NULL != dout){
                log_debug("org streams:%s", dout);
                jl_platform_free(dout);
            }
        }
    }                                                                                                         
    cJSON_Delete(pJson);
#endif
#ifdef JOYLINK_SDK_EXAMPLE_BUTTON
    log_debug("json_org:%s", pMsg);
    cJSON * pSub;
    cJSON * pJson = cJSON_Parse(pMsg);

    if(NULL == pJson){
        log_error("--->:ERROR: pMsg is NULL\n");
        goto RET;
    }

    cJSON *pStreams = cJSON_GetObjectItem(pJson, "streams");
    if(NULL != pStreams){
        int iSize = cJSON_GetArraySize(pStreams);
        int iCnt;
        for( iCnt = 0; iCnt < iSize; iCnt++){
            pSub = cJSON_GetArrayItem(pStreams, iCnt);
            if(NULL == pSub){
                continue;
            }

            cJSON *pSId = cJSON_GetObjectItem(pSub, "stream_id");
            if(NULL == pSId){
                break;
            }
            cJSON *pV = cJSON_GetObjectItem(pSub, "current_value");
            if(NULL == pV){
                continue;
            }
            if(!jl_platform_strcmp(USER_DATA_POWER, pSId->valuestring)){
                if(pV->type == cJSON_String){
                userDev->Power = jl_platform_atoi(pV->valuestring);
                }
                else if(pV->type == cJSON_Number){
                    userDev->Power = pV->valueint;
                }
                joylink_dev_user_data_set( USER_DATA_POWER,userDev);
            }

            char *dout = cJSON_PrintUnformatted(pSub);
            if(NULL != dout){
                log_debug("org streams:%s", dout);
                jl_platform_free(dout);
            }
        }
    }                                                                                                         
    cJSON_Delete(pJson);
#endif
RET:
    return ret;
}

/**
 * brief: 
 * NOTE: If return is not NULL, 
 * must free it, after use.
 *
 * @Param: retMsg
 * @Param: retCode
 * @Param: wci
 * @Param: devlist
 *
 * @Returns: char * 
 */
char * 
joylink_dev_package_info(const int retCode, user_dev_status_t *userDev)
{
    if(NULL == userDev){
        return NULL;
    }
    cJSON *root, *arrary;
    char *out  = NULL; 

    root = cJSON_CreateObject();
    if(NULL == root){
        goto RET;
    }
    arrary = cJSON_CreateArray();
    if(NULL == arrary){
        cJSON_Delete(root);
        goto RET;
    }
    cJSON_AddNumberToObject(root, "code", retCode);
    cJSON_AddItemToObject(root, "streams", arrary);

#ifdef JOYLINK_SDK_EXAMPLE_TEST
    char i2str[64];
    cJSON *data_Power = cJSON_CreateObject();
    cJSON_AddItemToArray(arrary, data_Power);
    cJSON_AddStringToObject(data_Power, "stream_id", "Power");
    jl_platform_memset(i2str, 0, sizeof(i2str));
    jl_platform_sprintf(i2str, "%d", userDev->Power);
    cJSON_AddStringToObject(data_Power, "current_value", i2str);

    cJSON *data_Mode = cJSON_CreateObject();
    cJSON_AddItemToArray(arrary, data_Mode);
    cJSON_AddStringToObject(data_Mode, "stream_id", "Mode");
    jl_platform_memset(i2str, 0, sizeof(i2str));
    jl_platform_sprintf(i2str, "%d", userDev->Mode);
    cJSON_AddStringToObject(data_Mode, "current_value", i2str);

    cJSON *data_State = cJSON_CreateObject();
    cJSON_AddItemToArray(arrary, data_State);
    cJSON_AddStringToObject(data_State, "stream_id", "State");
    jl_platform_memset(i2str, 0, sizeof(i2str));
    jl_platform_sprintf(i2str, "%d", userDev->State);
    cJSON_AddStringToObject(data_State, "current_value", i2str);
#endif

#ifdef JOYLINK_SDK_EXAMPLE_BUTTON
    char i2str[64];
    cJSON *data_Power = cJSON_CreateObject();
    cJSON_AddItemToArray(arrary, data_Power);
    cJSON_AddStringToObject(data_Power, "stream_id", "Power");
    jl_platform_memset(i2str, 0, sizeof(i2str));
    jl_platform_sprintf(i2str, "%d", userDev->Power);
    cJSON_AddStringToObject(data_Power, "current_value", i2str);
#endif
    out=cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
RET:
    return out;
}

/**
 * brief: 
 *
 * @Param: retCode
 * @Param: userDev
 *
 * @Returns: 
 */
char * 
joylink_dev_modelcode_info(const int retCode, JLPInfo_t *userDev)
{
    if(NULL == userDev){
        return NULL;
    }
    cJSON *root, *arrary;
    char *out  = NULL; 

    root = cJSON_CreateObject();
    if(NULL == root){
        goto RET;
    }
    arrary = cJSON_CreateArray();
    if(NULL == arrary){
        cJSON_Delete(root);
        goto RET;
    }
    cJSON_AddItemToObject(root, "model_codes", arrary);
    
    char i2str[32];
    jl_platform_memset(i2str, 0, sizeof(i2str));
    cJSON *element = cJSON_CreateObject();
    cJSON_AddItemToArray(arrary, element);
    cJSON_AddStringToObject(element, "feedid", userDev->feedid);
    cJSON_AddStringToObject(element, "model_code", "12345678123456781234567812345678");

    out=cJSON_PrintUnformatted(root);  
    cJSON_Delete(root); 
RET:
    return out;
}
