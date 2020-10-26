/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _AT_DEBUG_H_
#define _AT_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AT_DBG_ON		1
#define AT_WRN_ON		1
#define AT_ERR_ON		1

#define AT_AST_ON		1

#define AT_CHECK_OVERFLOW		1

#define AT_SYSLOG		printf
#define AT_ABORT()	do { } while (1) //sys_abort()

#define AT_LOG(flags, fmt, arg...)	\
	do {								\
		if (flags) 						\
			AT_SYSLOG(fmt, ##arg);	\
	} while (0)

#define AT_DBG(fmt, arg...)	AT_LOG(AT_DBG_ON, "[atcmd] "fmt, ##arg)
#define AT_WRN(fmt, arg...)	AT_LOG(AT_WRN_ON, "[atcmd WARN] "fmt, ##arg)
#define AT_ERR(fmt, arg...)								\
	do {													\
		AT_LOG(AT_ERR_ON, "[atcmd ERR] %s():%d, "fmt,	\
	           __func__, __LINE__, ##arg);					\
	    if (AT_ERR_ON)									\
			AT_ABORT();									\
	} while (0)

#if AT_AST_ON == 1
#define AT_ASSERT(con)	\
	do { \
		if (!(con)) { \
			AT_LOG(AT_AST_ON, "[atcmd ASSERT] %s():%d assert \"%s\" faild!\n",	\
				__func__, __LINE__, #con);					\
	    	if (AT_AST_ON) \
				AT_ABORT(); \
		} \
	} while (0)
#else
#define AT_ASSERT(con, msg)
#endif

#define FUN_DEBUG_ON 0

#if FUN_DEBUG_ON == 1
#define FUN_DEBUG(fmt...)                           \
  {                                                 \
    printf("file:%s line:%d ", __FILE__, __LINE__); \
      printf(fmt);                                    \
  }
#else
#define FUN_DEBUG(fmt...)
#endif

#ifdef __cplusplus
}
#endif

#endif

