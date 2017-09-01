# briup_STM32F103ZET6
基于STM32的课堂小程序

### 项目配置步骤

#### 配置选项
1. Xtal(MHz):8.0

2. C/C++ -> Define 添加 
    - STM32F10X_HD

3. C/C++ -> IncludePath添加
    - ..\..\User\inc
    - ..\..\Libraries\CMSIS\CM3\CoreSupport
    - ..\..\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x
    - ..\..\Hardware\inc
    - ..\..\Libraries\STM32F10x_StdPeriph_Driver\inc
    
#### 目录树
```
project
    |-user [User\src\*]  
    |-cmsis
        |-core_cm3.c [Libraries\CMSIS\CM3\CoreSupport\core_cm3.c]
        |-system_stm32f10x.c [Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.c]
    |-boot
        |-startup_stm32f10x_hd.s [Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm\startup_stm32f10x_hd.s]
    |-hardware [Hardware\src\*]
```

