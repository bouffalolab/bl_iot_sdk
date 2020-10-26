.. _zigbee-index:

Zigbee
==================

总览
------

本示例主要介绍如何使用zigbee。

使用步骤
-----------

- 编译 ``customer_app/bl702_demo_event`` 工程并下载工程；
- 1. Device1 使用 ``zb_set_role 0`` 命令设置设备类型ZC; 使用``zb_nwk_form 15 0x6666``创建信道15，PANID 0x6666的ZHA网络 ,打印的部分log如下。

    .. figure:: imgs/ZC-Startup.png
       :alt: 
 
- 2. Device1 使用 ``zb_nwk_permit 120`` 开放网络120秒；

    .. figure:: imgs/ZC-Permit.png
       :alt: 

- 3. Device2 使用 ``zb_set_role 1`` 命令设置设备类型ZR， 使用``zb_nwk_start`` 自动搜索zigbee网络，找到网络后打印的部分log如下。

    .. figure:: imgs/ZR-Startup.png
       :alt: 

- 4. Device1 使用 ``zb_zcl_onoff 0x9716 1 1 2`` 命令向Device2 ep1 发送zcl:toggle 命令

    .. figure:: imgs/ZC-SendOnOff.png
       :alt: 

- 5. Device2 使用接收到zcl:toggle命令，打印的部分log如下。

    .. figure:: imgs/ZR-Receive-OnOff.png
       :alt: 
