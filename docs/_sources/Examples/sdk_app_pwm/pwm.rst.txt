.. _pwm-index:

Pwm
==================

总览
------

本示例主要介绍demo_pwm相关

使用步骤
----------------

- dts　文件的修改

::

    pwm {
        #address-cells = <1>;
        #size-cells = <1>;
        pwm@4000A420 {
            status = "okay";
            compatible = "bl602_pwm";
            reg = <0x4000A420 0x20>;
            path = "/dev/pwm0";
            id = <0>;
            pin = <0>;
            freq = <800000>;
            duty = <50>;
        };
   };

- 编译 ``customer_app/sdk_app_pwm`` 工程并下载对应的bin文件；


功能
----------

命令： ``pwm_task`` ，开启pwm_task相关测试线程，用示波器测量io0，会发现从占空比为0到100递增，到最后关闭。


