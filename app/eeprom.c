//
// Created by RUPC on 2024/6/28.
//
#include "eeprom.h"
#include "../app/uart.h"

void ERROR_DISPLAY() {
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));
    UI_PrintStringSmall("NO Firmware !!", 0, 127, 2);
    UI_PrintStringSmall("Write in:", 0, 127, 3);
    UI_PrintStringSmall("k5.vicicode.com", 0, 127, 4);
    UI_PrintStringSmall("WRITE OR EXIT", 0, 127, 6);

//    show_uint32(sum_menu, 5);
    ST7565_BlitFullScreen();

    while (1) {
        if (KEYBOARD_Poll() == KEY_EXIT) {
            while (KEYBOARD_Poll() == KEY_EXIT);
            return;
        }
        UART_READ();
    }
}

void GET_FIRMWARE_NUM() {

    EEPROM_ReadBuffer(FIRMWARE_NUM_ADD, (uint8_t * ) & sum_menu, 1);
    if (sum_menu > 64 || sum_menu == 0) {
        ERROR_DISPLAY();
        NVIC_SystemReset();

    }
}

void LOAD_FIRMWARE() {
    //²Á³ý
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));
    UI_PrintStringSmall("KEEP POWER ON!", 0, 127, 4);
    uint32_t start_add, end_add;
    EEPROM_ReadBuffer(0x40020 + 32 * now_menu - 16, (uint8_t * ) & start_add, 4);
    EEPROM_ReadBuffer(0x40020 + 32 * now_menu - 16 + 4, (uint8_t * ) & end_add, 4);
    if (start_add > end_add || end_add > 0x80000 || start_add > 0x80000) {
        ERROR_DISPLAY();
        return;
    }
    char str[20];
    sprintf(str, "From 0x%08x", start_add);
    UI_PrintStringSmall(str, 0, 127, 6);
    uint32_t flash_add = 0;
    uint8_t flash_num = 0;
    if ((FLASH_MASK & 0x3) == 0) {
        flash_add = 0x1000;
        flash_num = 8;
    }
    for (int i = 0 + flash_num; i < 120 + flash_num; ++i) {
        Erase_Flash(i);
        char str[20];
        sprintf(str, "Erase: %03d/120", i + 1 - flash_num);
        UI_PrintStringSmall(str, 20, 0, 1);
        ST7565_BlitFullScreen();
    }


    CP_EEPROM_TO_FLASH(start_add, flash_add, end_add - start_add + 1);
    NVIC_SystemReset();

}