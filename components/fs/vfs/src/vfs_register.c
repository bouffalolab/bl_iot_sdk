/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <string.h>
#include <FreeRTOS.h>
#include <semphr.h>
#include <vfs_conf.h>
#include <vfs_err.h>
#include <vfs_register.h>

extern SemaphoreHandle_t g_vfs_mutex;

int aos_register_driver(const char *path, file_ops_t *ops, void *arg)
{
    inode_t *node = NULL;
    int err, ret;

    if (pdTRUE != xSemaphoreTake(g_vfs_mutex, portMAX_DELAY)) {
        err = -1;
        return err;
    }

    ret = inode_reserve(path, &node);
    if (ret == VFS_SUCCESS) {
        /* now populate it with char specific information */
        INODE_SET_CHAR(node);

        node->ops.i_ops = ops;
        node->i_arg     = arg;
    }

    /* step out critical area for type is allocated */
    if (pdTRUE != xSemaphoreGive(g_vfs_mutex)) {
        err = -1;
        if (node->i_name != NULL) {
            vPortFree(node->i_name);
        }

        memset(node, 0, sizeof(inode_t));
        return err;
    }

    return ret;
}

int aos_unregister_driver(const char *path)
{
    int err, ret;

    if (pdTRUE != xSemaphoreTake(g_vfs_mutex, portMAX_DELAY)) {
        err = -1;
        return err;
    }

    ret = inode_release(path);

    if (pdTRUE != xSemaphoreGive(g_vfs_mutex)) {
        err = -1;
        return err;
    }

    return ret;
}

int aos_register_fs(const char *path, fs_ops_t *ops, void *arg)
{
    inode_t *node = NULL;
    int err, ret;

    if (pdTRUE != xSemaphoreTake(g_vfs_mutex, portMAX_DELAY)) {
        err = -1;
        return err;
    }

    ret = inode_reserve(path, &node);
    if (ret == VFS_SUCCESS) {
        INODE_SET_FS(node);

        node->ops.i_fops = ops;
        node->i_arg      = arg;
    }

    if (pdTRUE != xSemaphoreGive(g_vfs_mutex)) {
        err = -1;
        if (node->i_name != NULL) {
            vPortFree(node->i_name);
        }

        memset(node, 0, sizeof(inode_t));
        return err;
    }

    return ret;
}

int aos_unregister_fs(const char *path)
{
    int err, ret;
 
    if (pdTRUE != xSemaphoreTake(g_vfs_mutex, portMAX_DELAY)) {
        err = -1;
        return err;
    }

    ret = inode_release(path);

    if (pdTRUE != xSemaphoreGive(g_vfs_mutex)) {
        err = -1;
        return err;
    }

    return ret;
}

