### 操作系统抽象层

#### 概述

为了让SDK能够更广泛的应用，所以提出了OSAL。SDK内部集成的组件以及SDK本身使用的OS功能，都调用的是OSAL接口，因为SDK要运行起来，必须注册相关的OS进OSAL才行

####  osal使用说明

osal的api接口声明在<osal.h>中，使用相关的接口需要包含该头文件，关于函数的详细参数请参考该头文件的声明。

##### 任务相关接口

| 接口名           | 功能描述                             |
| ---------------- | ------------------------------------ |
| osal_task_create | 创建任务                             |
| osal_task_kill   | 删除某个任务（一般是对非自任务操作） |
| osal_task_exit   | 任务退出                             |
| osal_task_sleep  | 任务休眠                             |

##### 任务同步机制

| 接口名            | 功能描述   |
| ----------------- | ---------- |
| osal_mutex_create | 创建互斥锁 |
| osal_mutex_del    | 删除互斥所 |
| osal_mutex_lock   | 获取互斥锁 |
| osal_mutex_unlock | 释放互斥锁 |
| osal_semp_create  | 信号灯创建 |
| osal_semp_del     | 信号灯删除 |
| osal_semp_pend    | 信号灯等待 |
| osal_semp_post    | 信号灯释放 |

##### 内存相关接口

| 接口名       | 功能描述          |
| ------------ | ----------------- |
| osal_malloc  | 用法意义同malloc  |
| osal_free    | 用法意义同free    |
| osal_zalloc  | 用法意义同zalloc  |
| osal_realloc | 用法意义同realloc |
| osal_calloc  | 用法意义同calloc  |

##### 其他接口

| 接口名        | 功能描述                                        |
| ------------- | ----------------------------------------------- |
| osal_sys_time | 获取系统时间，一般基于tick,可以用作相对时间判定 |
| osal_reboot   | 用作系统重启                                    |



#### 适配OSAL

​		目前而言，我们已经适配了LiteOS/LINUX/MACOS等，意味着我们的SDK可以在这些系统下运行。如果你需要在非上述系统下运行SDK，您需要将新系统适配进OSAL，保障SDK需要的OS功能正常。

​		您需要在您的系统初始化完毕之后，调用osal_install接口将您的系统注册进SDK即可。使用该接口需要包含<osal_imp.h>，相关的宏定义在<osal_type.h>中。详情参考该头文件。

​		如果需要适配第三方的操作系统，务必实现os_imp_init函数，开发者可以在该函数中调用osal_install将自己的操作系统的接口注册进osal中。而link_main则会调用osal_init函数，在在osal_init函数中调用os_imp_init。基本的调用关系如下：

​      link_main --->  osal_init ---->os_imp_init







