/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <FreeRTOS.h>
#include <stream_buffer.h>
#include <task.h>
#include <string.h>
#include <aos/kernel.h>
#include <device/vfs_uart.h>
#include <hal/soc/soc.h>
#include <vfs_err.h>
#include <yloop_types.h>
#include <utils_log.h>

/* uart driver struct */
const struct file_ops uart_ops =
{
    .open = vfs_uart_open,
    .close = vfs_uart_close,
    .read = vfs_uart_read,
    .write = vfs_uart_write,
    .poll = vfs_uart_poll,
    .ioctl = vfs_uart_ioctl,
    .sync = vfs_uart_sync,
};

static void __uart_rx_irq(void *p_arg)
{
    uint8_t tmp_buf[64];
    uint32_t length = 0;
    uart_dev_t *uart = (uart_dev_t *)p_arg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    hal_uart_recv_II(uart, tmp_buf, sizeof(tmp_buf), &length, 0);
    if (length) {
        xStreamBufferSendFromISR(uart->rx_ringbuf_handle, tmp_buf,
                length, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    if (uart->poll_cb != NULL) {
        ((struct pollfd*)uart->fd)->revents |= POLLIN;
        ((poll_notify_t)uart->poll_cb)(uart->fd, uart->poll_data);
    }
}

static void __uart_tx_irq(void *p_arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uart_dev_t *uart = (uart_dev_t *)p_arg;
    uint8_t ch;
    size_t ret;

    ret = xStreamBufferReceiveFromISR(uart->tx_ringbuf_handle, &ch, 1,
                                      &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    if (ret == 1) {
        hal_uart_send(uart, (const void *)&ch, 1, 0);
    } else {
        hal_uart_send_trigger_off(uart);
    }
}

int vfs_uart_open(inode_t *inode, file_t *fp)
{
    int ret = -1;                /* return value */
    uart_dev_t *uart_dev = NULL; /* device pointer */

    /* check empty pointer. */
    if ((fp != NULL) && (fp->node != NULL)) {

        /* Initialize if the device is first opened. */
        if (fp->node->refs == 1) {
            /* get the device pointer. */
            uart_dev = (uart_dev_t *)(fp->node->i_arg);

            aos_mutex_new((aos_mutex_t*)&(uart_dev->mutex));
            uart_dev->rx_ringbuf_handle = xStreamBufferCreate(uart_dev->rx_buf_size, 1);
            uart_dev->tx_ringbuf_handle = xStreamBufferCreate(uart_dev->tx_buf_size, 1);
            if (uart_dev->rx_ringbuf_handle == NULL || uart_dev->tx_ringbuf_handle == NULL) {
                return -EINVAL;
            }

            /*  init uart device. */
            hal_uart_notify_register(uart_dev, UART_TX_INT, __uart_tx_irq);
            hal_uart_notify_register(uart_dev, UART_RX_INT, __uart_rx_irq);
            ret = hal_uart_init(uart_dev);
        } else {
            ret = VFS_SUCCESS;
        }
    } else {
        ret = -EINVAL;
    }

    return ret;
}

int vfs_uart_close(file_t *fp)
{
    int ret = -1;                /* return value */
    uart_dev_t *uart_dev = NULL; /* device pointer */

    /* check empty pointer. */
    if ((fp != NULL) && (fp->node != NULL)) {

        /* close device if the device is last closed. */
        if (fp->node->refs == 1) {
            /* get the device pointer. */
            uart_dev = (uart_dev_t *)(fp->node->i_arg);

            if (uart_dev != NULL) {

                aos_mutex_free((aos_mutex_t*)&(uart_dev->mutex));
                vStreamBufferDelete(uart_dev->rx_ringbuf_handle);
                vStreamBufferDelete(uart_dev->tx_ringbuf_handle);
                /* turns off hardware. */
                ret = hal_uart_finalize(uart_dev);
            } else {
                ret = -EINVAL;
            }
        } else {
            ret = VFS_SUCCESS;
        }
    } else {
        ret = -EINVAL;
    }

    return ret;
}

#define use_tick(now, old) ((uint32_t)(((int32_t)(now)) - ((uint32_t)(old))))

ssize_t vfs_uart_read(file_t *fp, void *buf, size_t nbytes)
{
    int ret = -1;                /* return value */
    uart_dev_t *uart_dev = NULL; /* device pointer */
    uint32_t timeout;

    /* check empty pointer. */
    if ((fp != NULL) && (fp->node != NULL)) {

        /* get the device pointer. */
        uart_dev = (uart_dev_t *)(fp->node->i_arg);

        if ((nbytes > 0) && (uart_dev != NULL)) {
#if defined(CFG_USB_CDC_ENABLE)
            extern int usb_cdc_is_port_open(void);
            extern int usb_cdc_read(uint8_t *data, uint32_t len);
            if(usb_cdc_is_port_open()){
                return usb_cdc_read((uint8_t *)buf, nbytes);
            }
#endif

            aos_mutex_lock((aos_mutex_t*)&(uart_dev->mutex), AOS_WAIT_FOREVER);

            ret = 0;

            /* block */
            timeout = (UART_READ_CFG_BLOCK == uart_dev->read_block_flag) ? AOS_WAIT_FOREVER : 0;

            while (1) {
                ret += xStreamBufferReceive(uart_dev->rx_ringbuf_handle,
                                            buf + ret, nbytes - ret, timeout);
                if ((ret == nbytes) || (timeout == 0)) {
                    break;
                }
            }

            aos_mutex_unlock((aos_mutex_t*)&(uart_dev->mutex));
        } else {
            ret = -EINVAL;
        }
    } else {
        ret = -EINVAL;
    }

    return ret;
}

//TODO block write is needed
ssize_t vfs_uart_write(file_t *fp, const void *buf, size_t nbytes)
{
    int ret = -1;                /* return value */
    uart_dev_t *uart_dev = NULL; /* device pointer */

    /* check empty pointer. */
    if ((fp != NULL) && (fp->node != NULL)) {

        /* get the device pointer. */
        uart_dev = (uart_dev_t *)(fp->node->i_arg);

        if (uart_dev != NULL) {
#if defined(CFG_USB_CDC_ENABLE)
            extern int usb_cdc_is_port_open(void);
            extern int usb_cdc_write(const uint8_t *data, uint32_t len);
            if(usb_cdc_is_port_open()){
                return usb_cdc_write((const uint8_t *)buf, nbytes);
            }
#endif

            ret = xStreamBufferSend(uart_dev->tx_ringbuf_handle, buf, nbytes, 0);

            /*Trigger UART Write Now*/
            if (ret > 0) {
                hal_uart_send_trigger(uart_dev);
            }
        } else {
            ret = -EINVAL;
        }
    } else {
        ret = -EINVAL;
    }

    return ret;
}

int vfs_uart_poll(file_t *fp, bool setup, poll_notify_t notify, struct pollfd *fd, void *opa)
{
    uart_dev_t *uart_dev = (uart_dev_t *)(fp->node->i_arg);

    aos_mutex_lock((aos_mutex_t*)&(uart_dev->mutex), AOS_WAIT_FOREVER);
    if (!setup) {
        /*Enter Critical to protect callback from INT context and other task*/
        taskENTER_CRITICAL();
        //vPortEnterCritical();
        uart_dev->poll_cb = NULL;
        uart_dev->poll_data = NULL;
        taskEXIT_CRITICAL();
        //vPortExitCritical();
        goto out;
    }
    /*Protect callback from INT*/
    taskENTER_CRITICAL();
    //vPortEnterCritical();
    uart_dev->poll_cb = notify;
    uart_dev->fd = fd;
    uart_dev->poll_data = opa;
    taskEXIT_CRITICAL();
    //vPortExitCritical();

    if (xStreamBufferIsEmpty(uart_dev->rx_ringbuf_handle) != pdTRUE) {
        ((struct pollfd*)uart_dev->fd)->revents |= POLLIN;
        (*notify)(fd, opa);
    }
out:
    aos_mutex_unlock((aos_mutex_t*)&(uart_dev->mutex));

    return 0;
}

int uart_ioctl_cmd_waimode(uart_dev_t *uart_dev, int cmd, unsigned long arg)
{
    int ret = 0;
    uint32_t timeout;
    uint32_t nbytes;
    uart_ioc_waitread_t *waitr_arg = (uart_ioc_waitread_t *)arg;

    if (NULL == waitr_arg) {
        return -EINVAL;
    }

    nbytes = waitr_arg->read_size;

    timeout = pdMS_TO_TICKS(waitr_arg->timeout);

    while (1) {
        ret += xStreamBufferReceive(uart_dev->rx_ringbuf_handle,
                                    (uint8_t*)waitr_arg->buf + ret,
                                    nbytes - ret,
                                    timeout);
        if ((ret == nbytes) || (timeout == 0)) {
            break;
        }
        if (IOCTL_UART_IOC_WAITRD_MODE == cmd) {
            if (ret > 0) {
                break;
            }
        }
    }

    return ret;
}

int uart_ioctl_cmd_setconfig(uart_dev_t *uart_dev, unsigned long arg)
{
    uart_ioc_config_t *config = (uart_ioc_config_t *)arg;
    hal_uart_parity_t parity;

    if (NULL == config) {
        return -EINVAL;
    }

    if (config->parity == IO_UART_PARITY_ODD) {
        parity = ODD_PARITY;
    } else if (config->parity == IO_UART_PARITY_EVEN) {
        parity = EVEN_PARITY;
    } else {
        parity = NO_PARITY;
    }

    hal_uart_setconfig(uart_dev, config->baud, parity);

    return 0;
}

int vfs_uart_ioctl(file_t *fp, int cmd, unsigned long arg)
{
    int ret = -1;
    uart_dev_t *uart_dev = NULL;

    /* check empty pointer. */
    if ((fp == NULL) || (fp->node == NULL)) {
        return -EINVAL;
    }

    /* get the device pointer. */
    uart_dev = (uart_dev_t *)(fp->node->i_arg);

    if (uart_dev == NULL) {
        return -EINVAL;
    }

    aos_mutex_lock((aos_mutex_t*)&(uart_dev->mutex), AOS_WAIT_FOREVER);
    switch(cmd) {
        case IOCTL_UART_IOC_WAITRD_MODE:
        case IOCTL_UART_IOC_WAITRDFULL_MODE:
        {
            ret = uart_ioctl_cmd_waimode(uart_dev, cmd, arg);
        }
        break;
        case IOCTL_UART_IOC_FLUSH_MODE:
        {
            hal_uart_send_flush(uart_dev, 0);
        }
        break;
        case IOCTL_UART_IOC_BAUD_MODE:
        {
            hal_uart_setbaud(uart_dev, (uint32_t)arg);
        }
        break;
        case IOCTL_UART_IOC_CONFIG_MODE:
        {
            ret = uart_ioctl_cmd_setconfig(uart_dev, arg);
        }
        break;
        case IOCTL_UART_IOC_READ_BLOCK:
        {
            uart_dev->read_block_flag = UART_READ_CFG_BLOCK;
        }
        break;
        case IOCTL_UART_IOC_READ_NOBLOCK:
        {
            uart_dev->read_block_flag = UART_READ_CFG_NOBLOCK;
        }
        break;
        default:
        {
            ret =  -EINVAL;
        }
    }

    aos_mutex_unlock((aos_mutex_t*)&(uart_dev->mutex));

    return ret;
}

int vfs_uart_sync(file_t *fp)
{
    uart_dev_t *uart_dev = NULL;

    /* check empty pointer. */
    if ((fp == NULL) || (fp->node == NULL)) {
        return -EINVAL;
    }

    /* get the device pointer. */
    uart_dev = (uart_dev_t *)(fp->node->i_arg);

    if (uart_dev == NULL) {
        return -EINVAL;
    }

    aos_mutex_lock((aos_mutex_t*)&(uart_dev->mutex), AOS_WAIT_FOREVER);
    hal_uart_send_flush(uart_dev, 0);
    aos_mutex_unlock((aos_mutex_t*)&(uart_dev->mutex));

    return 0;
}

