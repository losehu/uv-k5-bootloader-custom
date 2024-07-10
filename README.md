**Read this in other languages: [English](README_en.md), [中文](README.md).**

**语言版本: [English](README_en.md), [中文](README.md).**

# 一种用于泉盛UVK5固件切换的引导程序

# 功能说明
* 能从eeprom中读取固件，写入flash中，实现任意版本固件切换
* 读取eeprom中存在的有效固件，并通过按键选择加载


# 原理说明
* 重写UV-K5引导程序，使之开机可从EEPROM加载引导B进入RAM，然后跳转到RAM中的引导B
* 引导B:
  * 从EEPROM中读取固件，写入FLASH中
  * 具有原版传统烧录通讯协议
  

# 使用条件
* 受到语言影响，需要大约150KB用于中文输入法，所以此引导程序只适用于4Mib(512KB)EEPROM的UVK5。
* 由于FLASH大小限制，单个固件的大小仍然不能超过60KB。
* 需要ST-Link将新的引导程序刷入UVK5的FLASH。

# 使用说明
* 参考目录下losehu Bootloader说明书.pdf

# 打赏

如果这个项目对您有帮助,可以考虑赞助来支持开发工作。

这是：[打赏名单](https://losehu.github.io/payment-codes/#%E6%94%B6%E6%AC%BE%E7%A0%81) 非常感谢各位的支持！！！

打赏码：

[![打赏码](https://github.com/losehu/uv-k5-firmware-chinese/blob/main/payment/show.png)](https://losehu.github.io/payment-codes/)

# 免责声明：

* **我没责任**
* 电台在刷写过程中可能会变砖，我并不为此负责。
* 我也不承担任何法律责任，这个项目是开源的，你可以自由使用，但是你必须对你的操作负责。

