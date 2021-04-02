#ifndef _JOYLINK_DEV_ACTIVE_H_
#define _JOYLINK_DEV_ACTIVE_H_
#include "joylink.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/**
 * 设备激活绑定流程说明:
 * 使用softAP配网:
 *      1. 只需将设备设置为softAP模式后,调用joylink_softap_start进行配网,如果配网成功SDK内部会自动完成激活绑定流程
 * 使用其他配网方式,如摄像头扫码配网，需按照如下步骤进行激活绑定:
 *      1. 应用层需通过扫码或其他方式获取到激活绑定所需的url和token
 *      2. 调用joylink_dev_active_start函数,通过参数传入激活绑定的url和token
 *      3. 调用joylink_dev_active_req函数,此函数会向云端发送设备激活绑定请求,应用层必须实现joylink_dev_https_post
 */

/**
 * @brief: 向云端发送设备激活绑定的HTTPS请求
 * 
 * @return: 0 成功, -1 失败
 */
int joylink_dev_active_req(void);

/**
 * @brief: 设置设备激活绑定所需的url和token
 * 
 * @param[in] urlstr: 设备激活绑定请求的目标url
 * @param[in] tokenstr: 设备激活绑定请求所需携带的token
 * 
 */
void joylink_dev_active_start(char *urlstr,char *tokenstr);

/**
 * @brief: 获取设备激活状态 1-正在激活绑定  0-激活绑定停止
 */
int joylink_dev_active_enable(void);

/**
 * @brief: 停止激活绑定
 */
void joylink_dev_active_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
