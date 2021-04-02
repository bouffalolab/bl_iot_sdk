#ifndef _JOYLINK_RET_CODE_H_
#define _JOYLINK_RET_CODE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef enum _jl_bool{
    E_JL_FALSE = 0,
    E_JL_TRUE = 1
}E_JLBOOL_t;

typedef enum _jl_ret_code{
    E_RET_ERROR_DEV_ACTIVED         = -2001,
    E_RET_ERROR_PKG_SAME            = -1001,
    E_RET_ERROR_PKG_NUM_BREAK_MAX   = -1002,
    E_RET_ERROR_PKG_BREAK_ARRAY     = -1003,
    E_RET_ERROR_PARAM_INVAID        = -3,
    E_RET_ERROR_NO_EXIST            = -2,
    E_RET_ERROR                     = -1,
    E_RET_OK                        = 0,
    E_RET_ALL_DATA_HIT              = 1001,
    E_RET_DATA_COMING               = 1002
}E_JLRetCode_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
