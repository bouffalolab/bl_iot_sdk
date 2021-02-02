/*
 * Tencent is pleased to support the open source community by making IoT Hub
 available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file
 except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software
 distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND,
 * either express or implied. See the License for the specific language
 governing permissions and
 * limitations under the License.
 *
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PATH_MAX 1024
/* Max size of cert/key file full path */
#define FILE_PATH_MAX_LEN 256

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#include <limits.h>
typedef unsigned long ssize_t;
#define getcwd(buffer, len) _getcwd(buffer, len)
#endif

#if defined(__linux__)
#include <fcntl.h>
#include <pthread.h>
//#include <sys/time.h>
#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#endif

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H_ */
