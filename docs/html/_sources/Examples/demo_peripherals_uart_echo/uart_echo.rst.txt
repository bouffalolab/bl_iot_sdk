.. _uart_echo-index:

UART_echo
==================

总览
----------------

本示例主要介绍通过UART1将收到的数据回传给发送方的过程。

准备及使用步骤
----------------

- 使用之前需要准备一个 ``USB转TTL`` 串口线，并配置SDK目录下 ``bl_iot_sdk/tools/flash_tool/bl602/device_tree/bl_factory_params_evb_40M.dts`` 文件中的 ``uart`` ，具体配置可以参考本例。

::
    
    uart {
        #address-cells = <1>;
        #size-cells = <1>;
        uart@4000A000 {
            status = "okay";
            id = <0>;
            compatible = "bl602_uart";
            path = "/dev/ttyS0";
            baudrate = <2000000>;
            pin {
                rx = <7>;
                tx = <16>;
            };
            feature {
                tx = "okay";
                rx = "okay";
                cts = "disable";
                rts = "disable";
            };
        };
        uart@4000A100 {
            status = "okay";
            id = <1>;
            compatible = "bl602_uart";
            path = "/dev/ttyS1";
            baudrate = <115200>;
            pin {
                rx = <3>;
                tx = <4>;
            };
            feature {
                tx = "okay";
                rx = "okay";
                cts = "disable";
                rts = "disable";
            };
        };
    };

- 使用步骤：
 - 将板子的 ``gpio3`` 和 ``gpio4`` 和 ``GND`` 分别与 ``USB转TTL`` 串口线的 ``TXD`` 、 ``RXD`` 、 ``GND`` 分别连接起来；
 - 编译 ``customer_app/sdk_app_uart_echo`` 工程并下载工程；
 - 打开一个串口终端窗口A（波特率为115200，用于接收和发送uart消息），打开另一个串口终端窗口B（波特率为2000000，用于打印log）。板子上电可以看到窗口A接收到 ``1234567890abcdefg`` ，窗口B打印的log 停止在 ``send case`` 处，在A窗口中输入 ``1234567890abcdefg`` （没有回显）可以在B串口看到 ``recv case`` 和 ``end`` 的消息，此时说明演示成功。

.. figure:: imgs/image1.png
   :alt: 

.. figure:: imgs/image2.png
   :alt: 
   
应用实例
----------------

- 调用 ``aos_write()`` 接口通过UART1给终端发送数据，并等待终端返回接收到的数据，如接收与发送的数据一致，则log口将打印UART1中收发的消息内容。

::

    aos_write(fd, send_recv_log, strlen(send_recv_log));
    log_step(ci_table_step_send);

    while (1) {
        length = aos_read(fd, buf_recv, strlen(send_recv_log));
        if (length != strlen(send_recv_log)) {
            continue;
        }
        if (memcmp(buf_recv, send_recv_log, strlen(send_recv_log)) == 0) {
            printf("recvbuff:%s\r\n", send_recv_log);
            log_step(ci_table_step_recv);
            break;
        }
        vTaskDelay(10);
    }
    log_step(ci_table_step_end);

- 在 ``customer_app/sdk_app_uart_echo/sdk_app_uart_echo/main.c`` 中 ``static void aos_loop_proc(void *pvParameters)`` 函数里调用ci_loop_proc()函数创建 ``uart_echo`` 的任务。
