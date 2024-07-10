//
// Created by RUPC on 2024/6/28.
//
#include "key.h"
#include "../ui/helper.h"
#include "../driver/system.h"
#include "../external/CMSIS_5/Device/ARM/ARMCM0/Include/ARMCM0.h"
#include "eeprom.h"

uint8_t now_menu = 1;
uint8_t sum_menu;
KeyboardState kbd = {KEY_INVALID, KEY_INVALID, 0};


void HandleUserInput() {
    kbd.prev = kbd.current;
    kbd.current = GetKey();
    if (kbd.current == KEY_INVALID) {
        kbd.counter = 0;
    }

    if (kbd.current != KEY_INVALID && kbd.current == kbd.prev) {
        if (kbd.counter < 16)
            kbd.counter++;
        else
            kbd.counter -= 3;
        SYSTEM_DelayMs(20);
    } else {
        kbd.counter = 0;
    }


    if (kbd.counter == 2 || kbd.counter == 16) {
        switch (kbd.current) {
            case KEY_UP:
                if (now_menu > 1)
                    now_menu--;
                else now_menu = sum_menu;
                break;
            case KEY_DOWN:

                if (now_menu < sum_menu)
                    now_menu++;
                else now_menu = 1;

                break;

            case KEY_MENU:
                LOAD_FIRMWARE();
                break;
            case KEY_EXIT:

                NVIC_SystemReset();
                break;

            default:
                break;
        }
    }

}