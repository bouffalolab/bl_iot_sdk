#ifndef _JOYLINK_TEMPKEY_H_
#define _JOYLINK_TEMPKEY_H_

#include "joylink_stdint.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef struct _jl_devinfo_st{
	uint8_t mac[17];
	uint8_t uuid[7];
	uint8_t public_key[33];
}jl_devinfo_st;

/**
 * brief: 临时密码加密
 *
 * @Returns:
 */
int joylink_dev_encode_temp_key(jl_devinfo_st *dev_info, uint8_t *data_in, uint8_t *data_out);

/**
 * brief: 临时秘密解密
 *
 * @Returns:
 */
int joylink_dev_decode_temp_key(jl_devinfo_st *dev_info, uint8_t *data_in, uint8_t *data_out);

#ifdef __cplusplus
}
#endif /* __cplusplus */
        
#endif /* joylink tempkey.h */
