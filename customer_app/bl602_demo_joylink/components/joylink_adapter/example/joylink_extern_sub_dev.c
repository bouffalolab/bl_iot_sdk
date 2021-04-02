/* --------------------------------------------------
 * @brief: 
 *
 * @version: 1.0
 * --------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joylink.h"
#include "joylink_extern_json.h"
#include "joylink_extern_sub_dev.h"

#include "joylink_stdio.h"
#include "joylink_memory.h"
#include "joylink_socket.h"
#include "joylink_string.h"
#include "joylink_stdint.h"
#include "joylink_log.h"
#include "joylink_time.h"

#define JL_MAX_SUB 2

int sub_dev_numb = JL_MAX_SUB;

JLSubDevData_t _g_sub_dev[JL_MAX_SUB] = {
    {.mac = "AA0011223344", .type = E_JLDEV_TYPE_SUB, .uuid = "4E4638", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "96f730bd1a6f9fcc2d40cfad0c0d8b9c"},
    {.mac = "AA0011223355", .type = E_JLDEV_TYPE_SUB, .uuid = "4E4638", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "9401a7005788efd93c25b46fdaf169ad"},
#if 0
    {.mac = "AA0011223366", .type = E_JLDEV_TYPE_SUB, .uuid = "4E4638", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "844cd9ab1f28140d8d60bd389b660154"},
    {.mac = "AA0011223377", .type = E_JLDEV_TYPE_SUB, .uuid = "4E4638", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "006b728b172e3e204e16380398ffe9da"},
    {.mac = "AA0011223399", .type = E_JLDEV_TYPE_SUB, .uuid = "514C0E", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "880c86bcd07b1648367c332cb2a1463a"},
    {.mac = "AA00112233AA", .type = E_JLDEV_TYPE_SUB, .uuid = "514C0E", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "4445c58c13659307f298ec51444a7201"},
    {.mac = "AA00112233BB", .type = E_JLDEV_TYPE_SUB, .uuid = "514C0E", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "a2e3c63557d94575015ac713dff54b3d"},
    {.mac = "AA00112233DD", .type = E_JLDEV_TYPE_SUB, .uuid = "514C0E", .lancon = 1, .cmd_tran_type = 1, .state = 1, .protocol = 1, .subNoSnapshot = E_SNAPSHOT_NO, .devAuthValue = "dbc499de2517fe99e7246a5f9b32ef54"}
#endif
};

extern int joylink_util_byte2hexstr(const uint8_t *pBytes, int srcLen, uint8_t *pDstStr, int dstLen);

#ifdef _SAVE_FILE_
char *sub_file = "joylink_subdev_info.txt";

void joylink_dev_sub_data_save(void)
{
    FILE *outfile;
    int i;
    
    if(sub_dev_numb <= 0){
        #ifdef __LINUX_PAL__
        // FIXME remove joylink_subdev_info.txt
        system("rm joylink_subdev_info.txt");
        #endif
        sub_dev_numb = 0;
        return;
    }
        
    outfile = jl_platform_fopen(sub_file, "wb+" );
    for(i = 0; i < JL_MAX_SUB; i++){
        if(jl_platform_strlen(_g_sub_dev[i].uuid) > 0)
            jl_platform_fwrite(&_g_sub_dev[i], sizeof(JLSubDevData_t), 1, outfile);
    }
    jl_platform_fclose(outfile);
}

void joylink_dev_sub_data_read(void)
{
    int ret;
    FILE *infile;

    infile = jl_platform_fopen(sub_file, "rb+");
    if(infile > 0){
        sub_dev_numb = 0;
        jl_platform_memset(_g_sub_dev, 0, sizeof(JLSubDevData_t) * JL_MAX_SUB);

        while(1){
            ret = jl_platform_fread(&_g_sub_dev[sub_dev_numb], sizeof(JLSubDevData_t), 1, infile);
            if(ret <= 0){
                jl_platform_fclose(infile);
                break;
            }
            sub_dev_numb++;
        }
    }
}
#endif

/**
 * @brief: 根据uuid和mac地址锁定一个子设备,持久化存储其认证信息
 *
 * @param[in]: uuid 产品uuid
 * @param[in]: mac  设备mac地址
 * @param[in]: auth_value  认证信息
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误 
 */

int error_auth_flag = 0;

E_JLRetCode_t
joylink_dev_sub_save_auth_value(char *uuid, char *mac, char *auth_value)
{
    int ret = E_RET_ERROR;
    int i; 

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(uuid, _g_sub_dev[i].uuid) && !jl_platform_strcmp(mac, _g_sub_dev[i].mac)){            
        jl_platform_memset(_g_sub_dev[i].devAuthValue, 0, 33);

        joylink_util_byte2hexstr((uint8_t *)auth_value, 16, (uint8_t *)_g_sub_dev[i].devAuthValue, 33);
        jl_platform_printf("SubDev value: %s %s\n", mac, _g_sub_dev[i].devAuthValue);
            ret = E_RET_OK;
        break;
        }
    }
#ifdef _SAVE_FILE_
    joylink_dev_sub_data_save();
#endif

    return ret;
}

/**
 * @brief: 添加子设备到全局数组_g_sub_dev中
 *
 * @param[in]: dev 设备结构
 * @param[in]: num TODO: 明确这个参数作用
 *
 * @returns:  E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_dev_sub_add(JLSubDevData_t *dev, int num)
{
    /**
     *FIXME: todo
     */
    int i = 0;
    int ret = E_RET_OK;

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(dev->uuid, _g_sub_dev[i].uuid) && !jl_platform_strcmp(dev->mac, _g_sub_dev[i].mac))
            return ret;
    }
    for(i = 0; i < JL_MAX_SUB; i++){
        if(jl_platform_strlen(_g_sub_dev[i].uuid) == 0){
            jl_platform_memcpy(&_g_sub_dev[i], dev, sizeof(JLSubDevData_t));
        sub_dev_numb++;
        break;
        }
    }
    return ret;
}

/**
 * @brief: 根据设备feedid删除子设备
 *
 * @param[in]: feedid
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_sub_dev_del(char *feedid)
{
    /**
     *FIXME: todo
     */
    int ret = E_RET_OK;
    int i = 0;
    
    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(feedid, _g_sub_dev[i].feedid)){
            jl_platform_memset(&_g_sub_dev[i], 0, sizeof(JLSubDevData_t));
        sub_dev_numb--;
        break;
        }
    }
    return ret;
}

/**
 * @brief: 根据feedid获取子设备实例信息,SDK中使用该函数的返回值判断是否进行后续的控制逻辑
 *
 * @param[in]: feedid
 * @param[out]: dev
 *
 * @returns: E_RET_OK 成功,E_RET_ERROR 失败
 */
E_JLRetCode_t
joylink_dev_sub_get_by_feedid(char *feedid, JLSubDevData_t *dev)
{
    /**
     *FIXME: todo
     */
    int ret = E_RET_ERROR;
    int i; 

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(feedid, _g_sub_dev[i].feedid)){
            jl_platform_memcpy(dev, &_g_sub_dev[i], sizeof(JLSubDevData_t));
            ret = E_RET_OK;
        break;
        }
    }

    return ret;
}

/**
 * @brief: 根据uuid和mac地址获取设备信息
 *
 * @param[in]: uuid 产品uuid
 * @param[in]: mac  设备mac地址
 * @param[out]: dev  设备信息
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_sub_dev_get_by_uuid_mac(char *uuid, char *mac, JLSubDevData_t *dev)
{
    /**
     *FIXME: todo
     */
    int ret = E_RET_OK;
    int i; 

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(uuid, _g_sub_dev[i].uuid) && !jl_platform_strcmp(mac, _g_sub_dev[i].mac)){
            jl_platform_memcpy(dev, &_g_sub_dev[i], sizeof(JLSubDevData_t));
            ret = E_RET_OK;
        break;
        }
    }

    return ret;
}

/**
 * @brief: 根据uuid和mac地址锁定一个子设备,更新其认证信息accesskey,localkey,feedid,lancon,cmd_tran_type,state
 *
 * @param[in]: uuid 产品uuid,小京鱼后台获取
 * @param[in]: mac 设备MAC地址
 * @param[in]: dev  子设备结构
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_dev_sub_update_keys_by_uuid_mac(char *uuid, char *mac, JLSubDevData_t *dev)
{
    /**
     *FIXME: todo
     */
    int ret = E_RET_ERROR;
    int i; 

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(uuid, _g_sub_dev[i].uuid) && !jl_platform_strcmp(mac, _g_sub_dev[i].mac)){
            jl_platform_memcpy(_g_sub_dev[i].accesskey, dev->accesskey, sizeof(dev->accesskey));
            jl_platform_memcpy(_g_sub_dev[i].localkey, dev->localkey, sizeof(dev->localkey));
            jl_platform_memcpy(_g_sub_dev[i].feedid, dev->feedid, sizeof(dev->feedid));

        _g_sub_dev[i].lancon = dev->lancon;
            _g_sub_dev[i].cmd_tran_type = dev->cmd_tran_type;
    
            _g_sub_dev[i].state = E_JLDEV_ONLINE;
            ret = E_RET_OK;
        break;
        }
    }
#ifdef _SAVE_FILE_
    joylink_dev_sub_data_save();
#endif

    return ret;
}

/**
 * @brief: 更新子设备版本信息
 *
 * @param[in]: feedid
 * @param[in]: version
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_dev_sub_version_update(char *feedid, int version)
{
    /**
     *FIXME: todo
     */
    int ret = E_RET_ERROR;
    int i; 

    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(feedid, _g_sub_dev[i].feedid)){
            _g_sub_dev[i].version = version;
            ret = E_RET_OK;
        break;
        }
    }

    return ret;
}

/**
 * brief: 根据子设备mac查询子设备其他信息。
 *
 * @Param: macstr
 *
 * @Returns: 
 */
int joylink_sub_dev_get_by_deviceid(char *macstr, JLSubDevData_t *info_out)
{
    int i;
    if(macstr == NULL || info_out == NULL){
        return -1;
    }
    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(macstr, _g_sub_dev[i].mac)){            
            jl_platform_memcpy(info_out, &_g_sub_dev[i], sizeof(JLSubDevData_t));
            return 0;
        }
    }
    return -1;
}

/**
 * brief: 更新子设备信息，并根据标识进行保存。
 *
 * @Param: macstr
 *
 * @Returns: 
 */
int joylink_sub_dev_update_device_info(JLSubDevData_t *info_in, int save_flag)
{
    int i;
    if(info_in == NULL){
        return -1;
    }
    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(info_in->mac, _g_sub_dev[i].mac)){     
            jl_platform_memcpy(&_g_sub_dev[i], info_in, sizeof(JLSubDevData_t));
            if(save_flag){
#ifdef _SAVE_FILE_
                joylink_dev_sub_data_save();
#endif
            }
            return 0;
        }
    }
    return -1;
}

/**
 * @brief: 获取所有子设备实例
 *
 * @param[out]: count 子设备总数
 *
 * @returns: JLSubDevData_t指针
 */

#ifdef _SAVE_FILE_
static char read_flag = 0;
#endif

JLSubDevData_t *
joylink_dev_sub_devs_get(int *count)
{
    /**
     *FIXME: todo must lock
     */
    int i = 0, j = 0, sum = 0; 
    JLSubDevData_t *devs = NULL;

    #ifdef _SAVE_FILE_
    if(read_flag == 0){
    read_flag = 1;
    joylink_dev_sub_data_read();
    }
    #endif
    
    sum = sub_dev_numb;
    devs = (JLSubDevData_t *)jl_platform_malloc(sizeof(JLSubDevData_t) * sum);
    jl_platform_memset(devs, 0, sizeof(JLSubDevData_t) * sum);
    if(devs != NULL){
        for(i = 0; i < JL_MAX_SUB; i++){
			if(jl_platform_strlen(_g_sub_dev[i].uuid) != 0){            
				jl_platform_memcpy(&devs[j], &_g_sub_dev[i], sizeof(JLSubDevData_t));
				j++;
			}
        }
    }
   
    *count = sum;
    return devs;
}

/**
 * @brief: 根据传入参数cmd对子设备进行控制,使用feedid获取对应子设备实例
 *
 * @param[in]: cmd 控制命令
 * @param[in]: cmd_len 控制命令长度
 * @param[in]: feedid 子设备feedid
 *
 * @Returns: 
 */

static int sub_power = 0;

E_JLRetCode_t
joylink_dev_sub_ctrl(const char* cmd, int cmd_len, char* feedid)
{
    /**
     *FIXME: todo must lock
     */
    log_debug("cmd:%s:feedid:%s\n", cmd, feedid);
    int ret = E_RET_OK;

    if(sub_power == 0)
    sub_power = 1;
    else if(sub_power == 1)
    sub_power = 0;

    return ret;
}

/**
 * @brief: 获取子设备快照json结构,返回序列化后的字符串,out_len为该结构的长度
 *
 * @param[in]: feedid  设备feed id
 * @Param[out]: out_len   设备快照的长度
 *
 * @returns:  序列化为字符串的设备快照json结构
 */


char *
joylink_dev_sub_get_snap_shot(char *feedid, int *out_len)
{
    /**
     *FIXME: todo must lock
     */
    char on[] = "{\"code\": 0,  \"streams\": [{ \"current_value\": \"1\", \"stream_id\": \"power\" }]}";
    char off[] = "{\"code\": 0,  \"streams\": [{ \"current_value\": \"0\", \"stream_id\": \"power\" }]}";

    char *tp =  NULL;

    char *ss = (char*)jl_platform_malloc(100);

    if(sub_power == 0)
    tp = off;
    else if(sub_power == 1)
    tp = on;

    if(ss != NULL){
        jl_platform_memset(ss, 0, 100);
        jl_platform_memcpy(ss, tp, jl_platform_strlen(tp)); 
        *out_len = jl_platform_strlen(tp);
    }

    return ss;
}

/**
 * @brief: 从全局子设备数组中,删除feedid匹配的设备,实现子设备解绑操作
 *
 * @param[in]: feedid 设备feed id
 *
 * @returns: E_RET_OK 成功, E_RET_ERROR 发生错误
 */
E_JLRetCode_t
joylink_dev_sub_unbind(const char *feedid)
{
    /**
     *FIXME: todo must lock
     */
    int ret = E_RET_OK;
    int i = 0;
    
    log_debug("feedid:%s\n", feedid);
    
    for(i = 0; i < JL_MAX_SUB; i++){
        if(!jl_platform_strcmp(feedid, _g_sub_dev[i].feedid)){
            //_g_sub_dev[i].state = 2;//E_JLDEV_UNBIND;
            jl_platform_memset(&_g_sub_dev[i], 0, sizeof(JLSubDevData_t));
            sub_dev_numb--;
            break;
        }
    }
#ifdef _SAVE_FILE_
    joylink_dev_sub_data_save();
#endif

    return ret;
}
