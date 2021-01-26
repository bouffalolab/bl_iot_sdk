/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#ifndef LITEOS_LAB_IOT_LINK_LINK_LOG_LINK_LOG_H_
#define LITEOS_LAB_IOT_LINK_LINK_LOG_LINK_LOG_H_

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include <iot_link_config.h>
/**
 * @brief:this defines for the log module, and  LINK_LOG_TRACE/LINK_LOG_DEBUG will not participate the compile in the release version
 *
 *
 * */
typedef enum
{
    EN_LINK_LOG_LEVEL_TRACE = 0,    ///< this is used as the trace function,like the function enter and function out
    EN_LINK_LOG_LEVEL_DEBUG,        ///< this is used as the debug, you could add any debug as you wish
    EN_LINK_LOG_LEVEL_INFO,         ///< which means it is import message, and you should known
    EN_LINK_LOG_LEVEL_WARN,      ///< this is used as the executed result,which means the status is not what we expected,but could accept
    EN_LINK_LOG_LEVEL_ERROR,        ///< this is used as the executed result,which means the status is not what we expected,could not accepta
    EN_LINK_LOG_LEVEL_FATAL,        ///< this is used as the parameters input for the api interface, which could not accepted
    EN_LINK_LOG_LEVEL_MAX,
}en_link_log_level_t;

/**
 * @brief:use this function to get the current output log
 *
 * @return: the current output mask log, defined by en_link_log_level_t
 * */
en_link_log_level_t link_log_level_get(void);

/**
 * @brief: use this function to get the debug level name
 *
 * @parameter[in]:level, the level to get
 *
 * @return: the mapped level name
 * */
const char *link_log_level_name(en_link_log_level_t level);

/**
 * @brief:use this function to set the current output log
 *
 *@parameter[in] level:defined by en_link_log_level_t
 *
 * @return: 0 success while -1 failed
 * */
int link_log_level_set(en_link_log_level_t level);


/*
 * @brief: this is a weak function ,and you could rewrite one
 *
 * @param fmt: same use as the fmt for printf
 *
 * @param unfixed: same use for printf
 *
 * @return: don't care about it
 *
 * @attention: and the components should not call this function directly, you'd better
 *
 *             call LINK_LOG groups
 *
 * */
//__attribute__((weak)) void link_printf(const char *format, ...);

#ifndef link_printf
#define link_printf printf
#endif

#ifdef CONFIG_LINKLOG_ENABLE

extern unsigned long long osal_sys_time();
#define LINK_LOG(level,fmt, ...) \
    do \
    { \
        (void)link_printf("[%s][%u][%s:%d] " fmt "\r\n", \
        link_log_level_name((level)), (unsigned int)osal_sys_time(), __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define LINK_LOG_TRACE(fmt, ...) \
    do \
    { \
        if ((EN_LINK_LOG_LEVEL_TRACE) >= link_log_level_get()) \
        { \
            LINK_LOG(EN_LINK_LOG_LEVEL_TRACE,fmt,##__VA_ARGS__); \
        } \
    } while (0)

#define LINK_LOG_DEBUG(fmt, ...) \
    do \
    { \
        if ((EN_LINK_LOG_LEVEL_DEBUG) >= link_log_level_get()) \
        { \
            LINK_LOG(EN_LINK_LOG_LEVEL_DEBUG,fmt,##__VA_ARGS__); \
        } \
    } while (0)

#else

#define LINK_LOG(level,fmt, ...)
#define LINK_LOG_TRACE(fmt, ...)
#define LINK_LOG_DEBUG(fmt, ...)

#endif


#define LINK_LOG_INFO(fmt, ...)   LINK_LOG(EN_LINK_LOG_LEVEL_INFO,fmt,##__VA_ARGS__)
#define LINK_LOG_WARN(fmt, ...)   LINK_LOG(EN_LINK_LOG_LEVEL_WARN,fmt,##__VA_ARGS__)
#define LINK_LOG_ERROR(fmt, ...)  LINK_LOG(EN_LINK_LOG_LEVEL_ERROR,fmt,##__VA_ARGS__)
#define LINK_LOG_FATAL(fmt, ...)  LINK_LOG(EN_LINK_LOG_LEVEL_FATAL,fmt,##__VA_ARGS__)


#endif /* LITEOS_LAB_IOT_LINK_LINK_LOG_LINK_LOG_H_ */
