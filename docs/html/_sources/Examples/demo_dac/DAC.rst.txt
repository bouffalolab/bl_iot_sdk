.. _dac-index:

DAC
==================

总览
------

本示例主要介绍如何使用iot板子的DAC播放音乐

使用步骤
-----------

- 编译 ``customer_app/sdk_app_dac`` 工程并下载工程；
  烧写的时候将 audio_32k 音频文件烧写进去romfs。


.. figure:: imgs/dac.png
   :alt: 


应用实例:
将工程和音频文件烧写进入后。重启板子。在shell界面 输入play_audio， 则可以听到音乐。 

NOTE:烧写romfs,是将一个文件夹的所有内容写入。请确保该文件夹中仅有audio_32k 这一个文件。



