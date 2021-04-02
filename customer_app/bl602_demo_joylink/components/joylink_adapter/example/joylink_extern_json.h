/* --------------------------------------------------
 * @file: joylink_extern_json.h
 *
 * @brief: 
 *
 * @version: 1.0
 *
 * @date: 10/26/2015 02:21:59 PM
 *
 * --------------------------------------------------
 */

#ifndef __JOYLINK_EXTERN_JSON__
#define __JOYLINK_EXTERN_JSON__

#include "joylink_extern.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/**
 * brief: 
 *
 * @Param: pCtrl
 * @Param: pMsg
 *
 * @Returns: 
 */
int 
joylink_dev_parse_ctrl(const char * pMsg, user_dev_status_t *userDev);

/**
 * brief: 
 *
 * @Param: retCode
 * @Param: pCtrl
 *
 * @Returns: 
 */
char * 
joylink_dev_package_info(const int retCode, user_dev_status_t *userDev);

/**
 * brief: 
 *
 * @Param: retCode
 * @Param: pCtrl
 *
 * @Returns: 
 */
char * 
joylink_dev_modelcode_info(const int retCode, JLPInfo_t *userDev);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
