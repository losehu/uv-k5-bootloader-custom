**Read this in other languages: [English](README_en.md), [中文](README.md).**

**语言版本: [English](README_en.md), [中文](README.md).**


# Bootloader for Quansheng UVK5 Firmware Switching

# Function Description
* Capable of reading firmware from EEPROM and writing it to flash, allowing switching between different firmware versions.
* Reads valid firmware from EEPROM and allows selection via button press for loading.

# Principle Description
* Rewrite the UV-K5 bootloader to load Bootloader B into RAM from EEPROM on startup, then jump to Bootloader B in RAM.
* Bootloader B:
    * Reads firmware from EEPROM and writes it to FLASH.
    * Supports traditional burning communication protocols.

# Requirements
* Due to language requirements (Chinese input method), approximately 150KB is needed, so this bootloader is only suitable for UVK5 with 4Mib (512KB) EEPROM.
* Due to flash size limitations, individual firmware size should not exceed 60KB.
* Requires ST-Link（or J-Link） to flash the new bootloader into UVK5's FLASH.

# Instructions
* Refer to the losehu Bootloader Manual.pdf in this directory.
* `LOSEHU_BASE_BOOT` is the base bootloader used to replace the official Quansheng bootloader.
* The bootloader file `L_BLXXX.bin` generated after running `make` in the main directory is stored in EEPROM and loaded into RAM by the base bootloader.
* `L_BLXXX.bin` performs functions such as serial port firmware flashing and firmware switching.

# Donations

If this project has been helpful to you, consider sponsoring to support further development work.

Here is the [list of sponsors](https://losehu.github.io/payment-codes/#%E6%94%B6%E6%AC%BE%E7%A0%81). Thank you very much for your support!

Donation QR code:

[![Donation QR code](https://github.com/losehu/uv-k5-firmware-chinese/blob/main/payment/show.png)](https://losehu.github.io/payment-codes/)

# Disclaimer:

* **I am not responsible**
* Radios may be bricked during the flashing process, and I am not responsible for this.
* I do not assume any legal responsibility. This project is open source; you are free to use it, but you must be responsible for your actions.
