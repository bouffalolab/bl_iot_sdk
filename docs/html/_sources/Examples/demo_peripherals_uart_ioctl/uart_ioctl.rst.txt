.. _uart_ioctl-index:

UART_ioctl
==================

总览
----------------

本示例主要介绍如何设置UART1的多种模式。

相关配置
----------------

- 配置参考 ``uart_echo`` 中的配置。
- 使用步骤
 - 将板子的 ``gpio3`` 和 ``gpio4`` 和 ``GND`` 分别与 ``USB转TTL`` 串口线的 ``TXD`` 、 ``RXD`` 、 ``GND`` 分别连接起来；
 - 编译 ``customer_app/sdk_app_uart_ctl`` 工程并下载工程；
 - 打开一个串口终端窗口A（波特率为115200，用于接收和发送uart消息），打开另一个串口终端窗口B（波特率为2000000，用于打印log）。例如使用应用实现中case1中的配置，在窗口A中输入 ``123456789abcdef`` ，在窗口A中可以看到接收到的数据，同时窗口B中打印出接收数据的个数。

.. figure:: imgs/image1.png
   :alt: 
   
应用实例
----------------

aos_ioctl选项为 ``IOCTL_UART_IOC_WAITRD_MODE`` 及 ``IOCTL_UART_IOC_WAITRDFULL_MODE`` ：

::

    while (1) {
        //log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = 0;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }

- case1： ``waitr_arg.timeout = 0`` case1中调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg))`` 表示当串口中的数据都读完或者读取到sizeof(buf_recv)长度的数据时立即返回。调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg))`` 用法与 ``IOCTL_UART_IOC_WAITRD_MODE`` 一致。

- case2： ``waitr_arg.timeout = AOS_WAIT_FOREVER`` case2中调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg))`` 表示当串口中的数据都读完或者读取到sizeof(buf_recv)长度的数据时立即返回，串口中无数据则一直等待。调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg))`` 表示一直等待直到读取到sizeof(buf_recv)长度的数据时立即返回。

- case3： ``waitr_arg.timeout = 5000`` case3中调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg))`` 表示当串口中的数据都读完或者读取到sizeof(buf_recv)长度的数据或者到达超时时间（超时时间从调用此接口算起，不是数据发送结束后算起）时立即返回。调用 ``aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg))`` 表示读取到sizeof(buf_recv)长度的数据或者到达超时时间（超时时间从调用此接口算起，不是数据发送结束后算起）时立即返回。

aos_ioctl选项为 ``UART_IOC_BAUD_MODE`` ：

::

    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 9600);

配置如上， ``9600`` 表示波特率。

aos_ioctl选项为 ``IOCTL_UART_IOC_READ_BLOCK`` 及 ``IOCTL_UART_IOC_READ_NOBLOCK`` ：

::

    while (1) {
        length = aos_read(fd, buf_recv, sizeof(buf_recv));
        if (length > 0) {
            log_info("%s name.length = %d:\r\n", name, length);
            aos_write(fd, buf_recv, length);
        }
        vTaskDelay(500);
        log_info("test.\r\n");
        count++;

        if (count == 5) {
            log_info("set noblock.\r\n");
            aos_ioctl(fd, IOCTL_UART_IOC_READ_NOBLOCK, 0);
        }

        if (count == 10) {
            log_info("set block.\r\n");
            aos_ioctl(fd, IOCTL_UART_IOC_READ_BLOCK, 0);
        }
    }

``aos_ioctl(fd, IOCTL_UART_IOC_READ_BLOCK, 0)`` 表示读取到sizeof(buf_recv)长度的数据立即返回，否则一致等待。 ``aos_ioctl(fd, IOCTL_UART_IOC_READ_NOBLOCK, 0)`` 表示当串口中的数据都读完或者读取到sizeof(buf_recv)长度的数据时立即返回。



