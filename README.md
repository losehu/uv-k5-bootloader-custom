**Read this in other languages: [English](README_en.md), [中文](README.md).**

**语言版本: [English](README_en.md), [中文](README.md).**

# 一种用于泉盛UVK5更大容量固件/固件切换的引导程序

# 功能说明
* 能从eeprom中读取固件，写入flash中，实现固件切换
* 读取eeprom中存在的有效固件，并通过按键选择加载


# 原理说明
* DP32G030芯片有64KB的flash，16KB的RAM
* 其中64KB flash有4K用于刷写程序的引导程序，剩下的60KB用于存放自定义的固件
* 受限于flash大小，自定义固件只能小于等于60KB
* 自定义固件需要占用略小于4KB的RAM用于存放数据,以及128B的堆栈空间，所以剩下大约12KB
* 可以在自定义固件中加入一小段程序，内容如下：
  * 通过某种按键触发
  * 从EEPROM中读取本项目的引导程序，加载到RAM中的后12K地址。
  * 让程序跳转到RAM中，执行本项目的引导程序
  * 引导程序读取eeprom中存在的有效固件，并通过按键选择
  * 将选择的固件从eeprom中读取，写入flash中，然后跳转到固件的入口地址
  * 启动后便实现了固件切换/APP加载

# 使用条件
* 受到语言影响，需要大约150KB用于中文输入法，所以此引导程序只适用于4Mib(512KB)EEPROM的UVK5。
* 对于每一个存入eeprom的固件，需要加入大约250B的跳转程序段实现将引导程序加载到RAM，这很简单。
* 由于FLASH大小限制，单个固件的大小仍然不能超过60KB。

# 打赏

如果这个项目对您有帮助,可以考虑赞助来支持开发工作。

这是：[打赏名单](https://losehu.github.io/payment-codes/#%E6%94%B6%E6%AC%BE%E7%A0%81) 非常感谢各位的支持！！！

打赏码：

[![打赏码](https://github.com/losehu/uv-k5-firmware-chinese/blob/main/payment/show.png)](https://losehu.github.io/payment-codes/)

# 免责声明：

* **我没责任**
* 电台在刷写过程中可能会变砖，我并不为此负责。
* 我也不承担任何法律责任，这个项目是开源的，你可以自由使用，但是你必须对你的操作负责。

