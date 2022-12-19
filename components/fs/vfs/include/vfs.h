/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef AOS_VFS_H
#define AOS_VFS_H

#include <sys/types.h>
#include <sys/stat.h>
#include "vfs_dir.h"
#include "vfs_inode.h"

#ifdef __cplusplus
extern "C" {
#endif

/*section for ADC IOCTRL*/
#define IOCTL_ADC_TRIGGER_DISABLE                      (0)
#define IOCTL_ADC_TRIGGER_ENABLE_HIGH_LEVEL            (1)
#define IOCTL_ADC_TRIGGER_ENABLE_LOW_LEVEL             (2)
#define IOCTL_ADC_TRIGGER_ENABLE_LEVEL_CUSTOM_HIGHER   (3)
#define IOCTL_ADC_TRIGGER_ENABLE_LEVEL_CUSTOM_LOWER    (4)

/* section for ROMFS IOCCTRL */
#define IOCTL_ROMFS_GET_FILEBUF                        (1)

/*section for GPIO IOCTRL*/
#define IOCTL_GPIO_PULL_UP                             (0)  /* PULLUP */
#define IOCTL_GPIO_PULL_DOWN                           (1)  /* PULLDOWN */
#define IOCTL_GPIO_PULL_NONE                           (2)  /* PULLNONE */

/*section for GPIO OUTPUT*/
#define OUTPUT_LOW                                     (0)  /* low level output */
#define OUTPUT_HIGH                                    (1)  /* high level output */
#define OUTPUT_TOGGLE                                  (2)  /* toggle output */

/**
 * Init vfs.
 *
 * @param[in] NULL
 *
 * @return 0 on success, negative error on failure.
 */
int vfs_init(void);

/**
 * Open the file or device by its path.
 *
 * @param[in]  path   the path of the file or device to open.
 * @param[in]  flags  the mode of open operation.
 *
 * @return  the new file descriptor, negative error on failure.
 */
int aos_open(const char *path, int flags);

/**
 * Close the file or device by its file descriptor.
 *
 * @param[in]  fd  the file descriptor of the file or device.
 *
 * @return  0 on success, negative error on failure.
 */
int aos_close(int fd);

/**
 * Read the contents of a file or device into a buffer.
 *
 * @param[in]   fd      the file descriptor of the file or device.
 * @param[in]   nbytes  the number of bytes to read.
 * @param[out]  buf     the buffer to read in to.
 *
 * @return  The number of bytes read, 0 at end of file, negative error on failure.
 */
ssize_t aos_read(int fd, void *buf, size_t nbytes);

/**
 * Write the contents of a buffer to file or device.
 *
 * @param[in]  fd      the file descriptor of the file or device.
 * @param[in]  nbytes  the number of bytes to write.
 * @param[in]  buf     the buffer to write from.
 *
 * @return  The number of bytes written, negative error on failure.
 */
ssize_t aos_write(int fd, const void *buf, size_t nbytes);

/**
 * This is a wildcard API for sending controller specific commands.
 *
 * @param[in]  fd   the file descriptior of the file or device.
 * @param[in]  cmd  A controller specific command.
 * @param[in]  arg  Argument to the command, interpreted according to the command.
 *
 * @return  any return from the command.
 */
int aos_ioctl(int fd, int cmd, unsigned long arg);

/**
 * A mechanism to multiplex input/output over a set of file descriptors.
 * For every file descriptor provided, poll() examines it for any events registered for that particular file descriptor.
 *
 * @param[in]  fds      a point to the array of pollfd struct carrying a file descriptor and bitmasks of events.
 * @param[in]  nfhs     number of file descriptors.
 * @param[in]  timeout  timer value to timeout or -1 for loop forever.
 *
 * @return  number of file descriptors selected (for which revents is non-zero). 0 if timed out with nothing selected. -1 for error.
 */
int aos_poll(struct pollfd *fds, int nfds, int timeout);

/**
 * Performs one of the operations described below on the open file descriptor, The operation is determined by cmd.
 *
 * @param[in]  fd   the file descriptor of the file or device.
 * @param[in]  cmd  the operation of the file or device.
 * @param[in]  val  it depends on whether cmd need params.
 *
 * @return  0 on success, negative error on failure.
 */
int aos_fcntl(int fd, int cmd, int val);

/**
 * Move the file position to a given offset from a given location.
 *
 * @param[in]  fd      the file descriptor of the file.
 * @param[in]  offset  The offset from whence to move to.
 * @param[in]  whence  The start of where to seek.
 *                     SEEK_SET to start from beginning of file.
 *                     SEEK_CUR to start from current position in file.
 *                     SEEK_END to start from end of file.
 *
 * @return  The new offset of the file.
 */
off_t aos_lseek(int fd, off_t offset, int whence);

/**
 * Flush any buffers associated with the file.
 *
 * @param[in]  fd  the file descriptor of the file.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_sync(int fd);

/**
 * Store information about the file in a stat structure.
 *
 * @param[in]   path  The path of the file to find information about.
 * @param[out]  st    The stat buffer to write to.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_stat(const char *path, struct stat *st);

/**
 * Remove a file from the filesystem.
 *
 * @param[in]  path  The path of the file to remove.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_unlink(const char *path);

/**
 * Rename a file in the filesystem.
 *
 * @param[in]  oldpath  The path of the file to rename.
 * @param[in]  newpath  The path to rename it to.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_rename(const char *oldpath, const char *newpath);

/**
 * Open a directory on the filesystem.
 *
 * @param[in]  path  the path of the directory to open.
 *
 * @return  a point of directory stream on success, NULL on failure.
 */
aos_dir_t *aos_opendir(const char *path);

/**
 * Close a directory.
 *
 * @param[in]  dir  the handle of the directory to close.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_closedir(aos_dir_t *dir);

/**
 * Read the next directory entry.
 *
 * @param[in]  dir  the handle of the directory to read.
 *
 * @return  a pointer to a dirent structure.
 */
aos_dirent_t *aos_readdir(aos_dir_t *dir);

/**
 * Create the directory, if they do not already exist.
 *
 * @param[in]  path  the path of the directory.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_mkdir(const char *path);

/**
 * Remove a directory.
 *
 * @param[in]  path  the path of the directory.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_rmdir(const char *path);

/**
 * Reset the position of a directory stream to the beginning of a directory.
 *
 * @param[in]  dir  the handle of the directory.
 *
 * @return  none.
 */
void aos_rewinddir(aos_dir_t *dir);

/**
 * Obtain the current location associated with the directory stream specified by dirp.
 *
 * @param[in]  dir  the handle of the directory.
 *
 * @return  0 on success, negative error code on failure.
 */
long aos_telldir(aos_dir_t *dir);

/**
 * Reset the position of a directory stream to the beginning of a directory.
 *
 * @param[in]  dir  the handle of the directory.
 * @param[in]  loc  the position of the directory.
 *
 * @return  none.
 */
void aos_seekdir(aos_dir_t *dir, long loc);

/**
 * Store information about the file system in a statfs structure.
 *
 * @param[in]   path  The path of the file system to find information about.
 * @param[out]  buf    The statfs buffer to write to.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_statfs(const char *path, struct statfs *buf);

/**
 * get access info.
 *
 * @param path The path of the file.
 * @param mode the info to get.
 *
 * @return  0 on success, negative error code on failure.
 */
int aos_access(const char *path, int amode);

#ifdef __cplusplus
}
#endif

#endif /* AOS_VFS_H */
