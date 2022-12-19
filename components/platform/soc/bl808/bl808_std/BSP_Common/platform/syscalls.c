/*
 * Copyright (c) 2016-2022 Bouffalolab.
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
#include <reent.h>
#include <errno.h>
#include <unistd.h>
#include "drv_mmheap.h"
#include "drv_device.h"

#ifdef CONFIG_MEM_USE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

extern struct heap_info mmheap_root;

#ifdef CONF_VFS_ENABLE
#include <vfs.h>
#endif

/* Reentrant versions of system calls.  */

/* global errno in RT-Thread */
static volatile int _sys_errno = 0;

#ifndef _REENT_ONLY
int *__errno()
{
    // #if (configUSE_POSIX_ERRNO == 1)
    //     {
    //         extern int FreeRTOS_errno;

    //         return &FreeRTOS_errno;
    //     }
    // #endif
    return (int *)&_sys_errno;
}
#endif

int _getpid_r(struct _reent *ptr)
{
    return 0;
}

int _execve_r(struct _reent *ptr, const char *name, char *const *argv, char *const *env)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _fork_r(struct _reent *ptr)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _isatty_r(struct _reent *ptr, int fd)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _kill_r(struct _reent *ptr, int pid, int sig)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

int _link_r(struct _reent *ptr, const char *old, const char *new)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

_off_t _lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    _off_t rc;

    rc = aos_lseek(fd, pos, whence);
    return rc;
#endif
}

int _mkdir_r(struct _reent *ptr, const char *name, int mode)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    int rc;

    rc = aos_mkdir(name);
    return rc;
#endif
}

int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    int rc;

    rc = aos_open(file, flags);
    return rc;
#endif
}

int _close_r(struct _reent *ptr, int fd)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    return aos_close(fd);
#endif
}

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    _ssize_t rc;

    rc = aos_read(fd, buf, nbytes);
    return rc;
#endif
}

int _rename_r(struct _reent *ptr, const char *old, const char *new)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    int rc;

    rc = aos_rename(old, new);
    return rc;
#endif
}

int _stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    int rc;

    rc = aos_stat(file, pstat);
    return rc;
#endif
}

int _unlink_r(struct _reent *ptr, const char *file)
{
#ifndef CONF_VFS_ENABLE
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
#else
    return aos_unlink(file);
#endif
}

int _wait_r(struct _reent *ptr, int *status)
{
    /* return "not supported" */
    ptr->_errno = -ENOSYS;
    return -1;
}

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
#ifndef CONF_VFS_ENABLE
    struct device *uart = device_find("debug_log");
    if ((STDOUT_FILENO == fd) || (STDERR_FILENO == fd)) {
        device_write(uart, 0, (uint8_t *)buf, nbytes);
    }
    return 0;
#else
    _ssize_t rc;

    rc = aos_write(fd, buf, nbytes);
    return rc;
#endif
}

void *_malloc_r(struct _reent *ptr, size_t size)
{
    void *result;
#ifdef CONFIG_MEM_USE_FREERTOS
    result = pvPortMalloc(size);
#else
    result = (void *)mmheap_alloc(&mmheap_root, size);
    if (result == NULL) {
        ptr->_errno = -ENOMEM;
    }
#endif
    return result;
}

void *_realloc_r(struct _reent *ptr, void *old, size_t newlen)
{
    void *result;
#ifdef CONFIG_MEM_USE_FREERTOS
#else
    result = (void *)mmheap_realloc(&mmheap_root, old, newlen);
#endif
    if (result == NULL) {
        ptr->_errno = -ENOMEM;
    }
    return result;
}

void *_calloc_r(struct _reent *ptr, size_t size, size_t len)
{
    void *result;
#ifdef CONFIG_MEM_USE_FREERTOS
    result = pvPortMalloc(size * len);
    if (result) {
        memset(result, 0, size * len);
    }
#else
    result = (void *)mmheap_calloc(&mmheap_root, size, len);
    if (result == NULL) {
        ptr->_errno = -ENOMEM;
    }
#endif
    return result;
}

void *_memalign_r(struct _reent *ptr, size_t align, size_t size)
{
    void *result;
#ifdef CONFIG_MEM_USE_FREERTOS
#else
    result = (void *)mmheap_align_alloc(&mmheap_root, align, size);
#endif
    if (result == NULL) {
        ptr->_errno = -ENOMEM;
    }

    return result;
}

void _free_r(struct _reent *ptr, void *addr)
{
#ifdef CONFIG_MEM_USE_FREERTOS
    vPortFree(addr);
#else
    mmheap_free(&mmheap_root, addr);
#endif
}

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    void *ret;
    ptr->_errno = ENOMEM;
    ret = (void *)-1;

    return ret;
}

/* for exit() and abort() */
void __attribute__((noreturn))
_exit(int status)
{
    while (1) {
    }
}

void _system(const char *s)
{
}

void __libc_init_array(void)
{
    /* we not use __libc init_aray to initialize C++ objects */
}

mode_t umask(mode_t mask)
{
    return 022;
}

int flock(int fd, int operation)
{
    return 0;
}

/*
These functions are implemented and replaced by the 'common/time.c' file
int _gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp);
_CLOCK_T_  _times_r(struct _reent *ptr, struct tms *ptms);
*/
