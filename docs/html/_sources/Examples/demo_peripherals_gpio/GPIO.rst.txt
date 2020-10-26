.. _gpio-index:

GPIO
==================

总览
------

本示例主要介绍如何配置GPIO。

使用步骤
-----------

- 编译 ``customer_app/sdk_app_gpio`` 工程并下载工程；
- 使用 ``gpio-func <pinnum> <inputmode> <pullup> <pulldown>`` 命令配置指定gpio口的输入输出模式，上拉下拉情况，如输入 ``gpio-func 8 0 0 0`` 命令表示将gpio8设置为输出模式，无上下拉；

.. figure:: imgs/image1.png
   :alt: 

- 使用 ``gpio-set <pinnum> <val>`` 命令可以设置指定gpio口的电平（该gpio设置为输出模式）；

.. figure:: imgs/image2.png
   :alt: 

- 使用 ``gpio-get <pinnum>`` 命令可以获取指定gpio口电平。

.. figure:: imgs/image3.png
   :alt: 

应用实例
---------

- gpio-func命令的实现

::

    if (5 != argc) {
        printf("Usage: %s 24 1 1 0\r\n  set GPIO24 to input with pullup\r\n",
                argv[0]
        );  
        return;
    }   
    ionum = atoi(argv[1]);
    inputmode = atoi(argv[2]);
    pullup = atoi(argv[3]);
    pulldown = atoi(argv[4]);
    if (ionum < 0 || inputmode < 0 || pullup < 0 || pulldown < 0) {
        puts("Illegal arg\r\n");
        return;
    }   
    printf("GPIO%d is set %s with %s pullup %s pulldown\r\n",
            ionum,
            inputmode ? "input" : "output",
            pullup ? "Active" : "null",
            pulldown ? "Active" : "null"
    );  
    if (inputmode) {
        bl_gpio_enable_input(ionum, pullup ? 1 : 0, pulldown ? 1 : 0); 
    } else {
        bl_gpio_enable_output(ionum, pullup ? 1 : 0, pulldown ? 1 : 0); 
    }  

获取命令行传入的信息，并作为参数传给 ``bl_gpio_enable_input(uint8, uint8, uint8)`` 或 ``bl_gpio_enable_output(uint8, uint8, uint8)`` 函数，从而配置对应gpio口。

- gpio-set命令的实现
::

    if (3 != argc) {
        printf("Usage: %s 24 1\r\n  set GPIO24 output to high\r\n",
                argv[0]
        );
        return;
    }
    ionum = atoi(argv[1]);
    val = atoi(argv[2]);
    if (ionum < 0 || val < 0) {
        puts("Illegal arg\r\n");
        return;
    }
    printf("GPIO%d is set to %s\r\n",
        ionum,
        val ? "high" : "lo"
    );
    bl_gpio_output_set(ionum, val ? 1 : 0);

获取命令行传入的信息，并作为参数传给 ``bl_gpio_output_set(uint8, uint8)`` 函数，设置对应gpio口的电平。

- gpio-get命令的实现
::

   if (2 != argc) { 
        printf("Usage: %s 24\r\n  get GPIO24 value\r\n",
                argv[0]
        );
        return;
    }
    ionum = atoi(argv[1]);
    if (ionum < 0) {
        puts("Illegal arg\r\n");
        return;
    }
    ret = bl_gpio_input_get(ionum, &val);
    printf("GPIO%d val is %s\r\n",
        ionum,
        0 == ret ? (val ? "high" : "low") : "Err"
    );

获取命令行传入的信息，并作为参数传给 ``bl_gpio_input_get(uint8, uint8*)`` 函数，获取对应gpio口的电平。

- 在 ``customer_app/sdk_app_gpio/sdk_app_gpio/main.c`` 中的 ``static void _cli_init()`` 函数里调用 ``gpio_cli_init()`` 初始化gpio相关的操作命令。
