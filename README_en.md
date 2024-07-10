**Read this in other languages: [English](README_en.md), [中文](README.md).**

**语言版本: [English](README_en.md), [中文](README.md).**

# A Bootloader for Larger Capacity Firmware/Firmware Switching on Quansheng UVK5

## Functional Description
* Reads firmware from EEPROM and writes it to flash to switch firmware.
* Reads valid firmware stored in EEPROM and allows selection via a button press.

## Principle Explanation
* The DP32G030 chip has 64KB of flash and 16KB of RAM.
    * Out of the 64KB flash, 4KB is used for the bootloader that writes programs, leaving 60KB for custom firmware.
    * Due to the flash size limitation, the custom firmware can only be up to 60KB.
    * The custom firmware requires slightly less than 4KB of RAM to store data, and 128B of stack space, leaving about 12KB.
    * A small program can be added to the custom firmware with the following content:
        * Triggered by a certain button press.
        * Reads the bootloader of this project from the EEPROM and loads it to the last 12K address in the RAM.
        * Jumps to the RAM to execute the bootloader of this project.
        * The bootloader reads valid firmware from the EEPROM and allows selection via a button press.
        * The selected firmware is read from the EEPROM, written to the flash, and then jumps to the entry address of the firmware.
        * After startup, firmware switching/APP loading is achieved.

## Conditions of Use
* Due to language requirements, approximately 150KB is needed for Chinese input method, so this bootloader is only suitable for UVK5 with 4MiB (512KB) EEPROM.
* For each firmware stored in the EEPROM, approximately 250B of a jump program segment is required to load the bootloader to RAM, which is simple.
* Due to flash size limitations, the size of a single firmware still cannot exceed 60KB.

## Sponsorship

If this project has been helpful to you, consider donating to support the development work.

Here is the [Sponsorship List](https://losehu.github.io/payment-codes/#%E6%94%B6%E6%AC%BE%E7%A0%81). Many thanks to everyone for their support!

Donation code:

[![Donation Code](https://github.com/losehu/uv-k5-firmware-chinese/blob/main/payment/show.png)](https://losehu.github.io/payment-codes/)

## Disclaimer:
* **No Liability**
* The radio may become bricked during the flashing process, for which I am not responsible.
* I do not assume any legal responsibility. This project is open-source, and you are free to use it, but you must take responsibility for your actions.