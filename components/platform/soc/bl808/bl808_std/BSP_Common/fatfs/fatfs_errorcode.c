/*
 * Copyright (c) 2016-2023 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
const char *FR_Table[] = {
    "FR_OK：成功",                                           /* (0) Succeeded */
    "FR_DISK_ERR：底层硬件错误",                             /* (1) A hard error occurred in the low level disk I/O layer */
    "FR_INT_ERR：断言失败",                                  /* (2) Assertion failed */
    "FR_NOT_READY：物理驱动没有工作",                        /* (3) The physical drive cannot work */
    "FR_NO_FILE：文件不存在",                                /* (4) Could not find the file */
    "FR_NO_PATH：路径不存在",                                /* (5) Could not find the path */
    "FR_INVALID_NAME：无效文件名",                           /* (6) The path name format is invalid */
    "FR_DENIED：由于禁止访问或者目录已满访问被拒绝",         /* (7) Access denied due to prohibited access or directory full */
    "FR_EXIST：文件已经存在",                                /* (8) Access denied due to prohibited access */
    "FR_INVALID_OBJECT：文件或者目录对象无效",               /* (9) The file/directory object is invalid */
    "FR_WRITE_PROTECTED：物理驱动被写保护",                  /* (10) The physical drive is write protected */
    "FR_INVALID_DRIVE：逻辑驱动号无效",                      /* (11) The logical drive number is invalid */
    "FR_NOT_ENABLED：卷中无工作区",                          /* (12) The volume has no work area */
    "FR_NO_FILESYSTEM：没有有效的FAT卷",                     /* (13) There is no valid FAT volume */
    "FR_MKFS_ABORTED：由于参数错误f_mkfs()被终止",           /* (14) The f_mkfs() aborted due to any parameter error */
    "FR_TIMEOUT：在规定的时间内无法获得访问卷的许可",        /* (15) Could not get a grant to access the volume within defined period */
    "FR_LOCKED：由于文件共享策略操作被拒绝",                 /* (16) The operation is rejected according to the file sharing policy */
    "FR_NOT_ENOUGH_CORE：无法分配长文件名工作区",            /* (17) LFN working buffer could not be allocated */
    "FR_TOO_MANY_OPEN_FILES：当前打开的文件数大于_FS_SHARE", /* (18) Number of open files > _FS_SHARE */
    "FR_INVALID_PARAMETER：参数无效"                         /* (19) Given parameter is invalid */
};