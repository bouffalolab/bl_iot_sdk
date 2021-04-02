#ifndef __JOYLINK_LOG_H__
#define __JOYLINK_LOG_H__

#include <stdio.h>

#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include "joylink_stdio.h"
#include "joylink_time.h"
#include "joylink_stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define JL_LOG_LEVEL_FATAL      (0)
#define JL_LOG_LEVEL_NOTICE     (1)
#define JL_LOG_LEVEL_INFO       (2)
#define JL_LOG_LEVEL_ERROR      (3)
#define JL_LOG_LEVEL_WARN       (4)
#define JL_LOG_LEVEL_DEBUG      (5)

#define Black   0;30
#define Red     0;31
#define Green   0;32
#define Brown   0;33
#define Blue    0;34
#define Purple  0;35
#define Cyan    0;36

//#define JL_LOG_LEVEL  JL_LOG_LEVEL_ERROR
#define JL_LOG_LEVEL  JL_LOG_LEVEL_DEBUG

#ifndef __FILENAME__
#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#endif

#ifdef __GNUC__
#define SHORT_FILE    __FILENAME__
#else
#define SHORT_FILE   strrchr(__FILE__, '\\')?strrchr(__FILE__, '\\') + 1 : __FILE__
#endif

#define log_fatal(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_FATAL){\
            jl_platform_printf("\033[0;31m[FATAL][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(),  SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)

#define log_notice(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_NOTICE){\
            jl_platform_printf("\033[0;36m[NOTICE][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(), SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)

#define log_info(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_INFO){\
            jl_platform_printf("\033[1;36m[INFO][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(),  SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)

#define log_error(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_ERROR){\
            jl_platform_printf("\033[0;31m[ERROR][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(), SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)

#define log_warn(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_WARN){\
            jl_platform_printf("\033[1;33m[WARN][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(),  SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)

#define log_debug(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_DEBUG){\
            jl_platform_printf("\033[1;32m[DEBUG][%s][%s][%s][%d]\r\n" format "\r\n\033[0m", jl_get_time_str(),  SHORT_FILE, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
        }\
    }while(0)


#ifdef __cplusplus
}
#endif
#endif
