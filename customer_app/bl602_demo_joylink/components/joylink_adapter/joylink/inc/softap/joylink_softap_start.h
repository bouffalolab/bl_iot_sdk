#ifndef _JOYLINK_SOFTAP_START_H_
#define _JOYLINK_SOFTAP_START_H_
#include "joylink_stdint.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/**
 * @brief: 开始softAP配网流程.
 * 
 * @note: 在调用此函数开始softAP配网之前,需要确保设备wifi已经进入AP模式,否则无法成功配网.
 * 
 * @param[in] timeout_ms: 配网超时时间,单位毫秒
 * 
 * @returns: 0 配网成功, -1 配网失败
 */
int joylink_softap_start(unsigned int timeout_ms);


/**
 * @name:joylink_softap_status 
 *
 * @returns:   0，不是softap配网状态；1，softap配网进行中
 */
uint8_t joylink_softap_status(void);

uint8_t joylink_softap_client_online(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
