# eeprom分配说明
* 0x00000~0x3FFFF 0~256KB 256KB 保留
* 0x40000~0x40FFF 256KB~260KB 4KB 固件信息
  * 0X40000 固件数量 0~64 1B
  * 0X40001 启动模式 0固件 1切换 2刷机 1B
  * 0X40008~0X4000F 引导名称，例如：L_BL001
  * 每个固件信息存放需要32B
    * 从0x40020开始，每32B为一个固件信息
      * 前13B为固件名称，13个ASCII字符，不包括结束符
      * 后16B为固件起始地址(4B)、结束地址(4B)，地址需要满足4B对齐(4的倍数)，剩余8B闲置
* 0x41000~0x43FFF 256KB~260KB 11.75KB 引导程序(L_BL001.bin)
* 0x44000~0x80000 240KB 存放固件 4B对齐
