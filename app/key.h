//
// Created by RUPC on 2024/6/28.
//

#ifndef UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_KEY_H
#define UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_KEY_H

#include "../driver/keyboard.h"
typedef enum {
    KEY_STATE_IDLE,
    KEY_STATE_PRESSED,
    KEY_STATE_HELD,
    KEY_STATE_RELEASED
} KeyState_t;
typedef struct KeyboardState {
    KEY_Code_t current;
    KEY_Code_t prev;
    uint8_t counter;
    KeyState_t state;
    bool gRepeatHeld;

} KeyboardState;
extern uint8_t now_menu ;
extern uint8_t sum_menu;
 void HandleUserInput() ;

#endif //UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_KEY_H
