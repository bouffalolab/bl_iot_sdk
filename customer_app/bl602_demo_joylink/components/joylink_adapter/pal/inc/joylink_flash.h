#ifndef _JOYLINK_FLASH_H_
#define _JOYLINK_FLASH_H_

#include "joylink_stdint.h"

//key用于存储：工厂模组连接ap失败原因
#define KEY_FAC     "fac_ap_con_fail"
//key用于存储：sdk softap配网失败原因
#define KEY_SDK     "sdk_softap_fail"

/**
 * @brief:set data in jl_flash
 *
 * @param: key, value
 *
 * @returns: success 0, failed -1
 */
int32_t jl_flash_SetInt8(const char* key, int8_t value);
int32_t jl_flash_SetInt32(const char* key, int32_t value);
int32_t jl_flash_SetInt64(const char* key, int64_t value);
int32_t jl_flash_SetBool(const char* key, int8_t value);

/**
 * @brief:set buff in jl_flash
 *
 * @param: key, buff, len
 *
 * @returns: success 0, failed -1
 */
int32_t jl_flash_SetString(const char* key, const char* buff, int32_t len);

/**
 * @brief:get data from jl_flash
 *
 * @param: key, value
 *
 * @returns: 读取到的value值, 如果读取失败则返回defaultValue.
 */
int8_t 	jl_flash_GetInt8(const char* key, int8_t defaultValue);
int32_t jl_flash_GetInt32(const char* key, int32_t defaultValue);
int64_t jl_flash_GetInt64(const char* key, int64_t defaultValue);
int8_t  jl_flash_GetBool(const char* key, int8_t defaultValue);
/**
 * @brief:get data from jl_flash
 *
 * @param: key, value
 *
 * @returns: 读取到value的长度len, 如果无数据则返回0.
 */
int32_t jl_flash_GetString(const char* key, char* buff, int32_t len);

/**
 * @brief:clear jl_flash data 
 *
 * @param: key
 *
 * @returns: none
 */
void jl_flash_ClearKey(const char *key);

/**
 * @brief: 二进制数据写入flash
 * 
 * @param[in] offset: flash地址偏移
 * 
 * @param[in] buf: 写入flash的数据
 * 
 * @param[in] len: 要写入数据的长度
 * 
 * @return 返回实际写入的数据长度，写入失败则返回-1
 * 
 */

int32_t jl_flash_SetBuffer(int32_t offset, const void* buf, int32_t len);


/**
 * @brief: SDK申请预留flash空间
 * 
 * @param[in] size: 申请空间的大小，字节为单位
 * 
 * @return： 申请flash空间的偏移，如果申请失败则返回-1
 * 
 */
int32_t jl_flash_request(int32_t size);

/**
 * @brief: 读取指定偏移地址的数据
 * 
 * @param[in] offset: flash偏移地址
 * 
 * @param[out] buf: 存储读取数据的buffer
 * 
 * @param[in] len: 预期读取的数据长度
 * 
 * @return int32_t: 实际读取的数据长度，如果读取失败则返回-1
 * 
 */ 

int32_t jl_flash_GetBuffer(int32_t offset, const void* buf, int32_t len);

/**
 * @brief: 清除指定偏移地址的数据
 * 
 * @param[in] offset: flash偏移地址
 * 
 * @param[in] len: 预期读取的数据长度
 * 
 * @return int32_t: 实际读取的数据长度，如果读取失败则返回-1
 * 
 */ 
int32_t jl_flash_ClearBuffer(int32_t offset, int32_t len);

#endif
