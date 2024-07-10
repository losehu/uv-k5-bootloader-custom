/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */
#include "external/printf/printf.h"
#include "bsp/dp32g030/gpio.h"
#include "driver/gpio.h"
#include "sram-overlay.h"
#include "string.h"
#include "ui/helper.h"
#include "driver/system.h"
#include "board.h"
#include "bsp/dp32g030/syscon.h"
#include "driver/systick.h"
#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "ARMCM0.h"
#include "driver/keyboard.h"
#include "app/key.h"
#include "app/display.h"
#include "app/eeprom.h"
#include "app/uart.h"
#include "driver/uart.h"

uint8_t send_data[] = {0xab, 0xcd, 0x24, 0x00, 0x0e, 0x69, 0x34, 0xe6, 0x2f, 0x93, 0x0e, 0x42, 0x2d, 0x66, 0x9f,
                       0x73,
                       0x5e, 0x40, 0x16, 0x93, 0x37, 0x6c, 0x3c, 0xe6, 0x1c, 0xbf, 0x3d,
                       0x70, 0x0f, 0x05, 0xe3, 0x40, 0x27, 0x09, 0xe9, 0x80, 0x16, 0x6c,
                       0x14, 0xc6, 0xff, 0xff, 0xdc, 0xba};

void Main(void) {
    //BOOT_Mode_t  BootMode;
    // Enable clock gating of blocks we need
    SYSCON_DEV_CLK_GATE = 0
                          | SYSCON_DEV_CLK_GATE_GPIOA_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_GPIOB_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_GPIOC_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_UART1_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_SPI0_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_SARADC_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_CRC_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_AES_BITS_ENABLE
                          | SYSCON_DEV_CLK_GATE_PWM_PLUS0_BITS_ENABLE;
    SYSTICK_Init();
    BOARD_Init();
    UART_Init();

    memset(gStatusLine, 0, sizeof(gStatusLine));
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));
    ST7565_BlitStatusLine();
    ST7565_BlitFullScreen();
    uint8_t boot_mode = 0;
    bool mode = 0;

    EEPROM_ReadBuffer(0X01FF0, (uint8_t * ) & boot_mode, 1);
    if (boot_mode == 2) {
        mode = 1;
    }
    if (mode) {
        GPIO_SetBit(&GPIOC->DATA, GPIOC_PIN_FLASHLIGHT);
        GPIO_ClearBit(&GPIOB->DATA, GPIOB_PIN_BACKLIGHT);
    } else {
        GET_FIRMWARE_NUM();

        GPIO_SetBit(&GPIOB->DATA, GPIOB_PIN_BACKLIGHT);
        UI_PrintStringSmall("Boot OK", 0, 127, 2);
        UI_PrintStringSmall("Release Key", 0, 127, 6);
        ST7565_BlitStatusLine();
        ST7565_BlitFullScreen();
        while (KEYBOARD_Poll() == KEY_MENU);
    }

    int cnt = 0;
    while (1) {
        if (mode == 1) {
            if (uart_flag == 0) {
                UART_Send(send_data, 44);
                cnt = 0;
            }

        }
        UART_READ();
        if (mode == 0) {
            HandleUserInput();
            SELECT_DISPLAY();
        }
        cnt++;
    }
}



