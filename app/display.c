//
// Created by RUPC on 2024/6/28.
//


#include "../external/printf/printf.h"
#include "../driver/st7565.h"

#include "string.h"
#include "../ui/helper.h"
#include "display.h"
#include "key.h"

const uint8_t BITMAP_ARRAY_DOWN[5];
const uint8_t BITMAP_ARRAY_UP[5];
const uint8_t BITMAP_ARRAY_RIGHT[7];
const uint8_t BITMAP_ARRAY_LEFT[7];

void SELECT_DISPLAY() {
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));
    memset(gStatusLine, 0, sizeof(gStatusLine));
    char str[22] = {0};
    for (int i = 0; i < NUM_PER_PAGE; ++i) {
        uint8_t show_num = ((now_menu - 1) / NUM_PER_PAGE) * NUM_PER_PAGE + 1 + i;
        if (show_num > sum_menu)
            break;
        char str1[14];
        EEPROM_ReadBuffer(0x40020 + 32 * (show_num - 1), str1, 13);
        str1[13] = 0;
        sprintf(str, "%02d.%s", show_num, str1);
        UI_PrintStringSmall(str, 8, 0, i);
    }
    if ((now_menu - 1) / NUM_PER_PAGE * NUM_PER_PAGE + 1 < sum_menu) memcpy(&gStatusLine[120], BITMAP_ARRAY_DOWN, 5);
    if ((now_menu - 1) / NUM_PER_PAGE) memcpy(&gStatusLine[112], BITMAP_ARRAY_UP, 5);
    //固件版本
    UI_PrintStringSmallBuffer("LoseHu BL 0.02", gStatusLine);
    //选中箭头
    memcpy(&gFrameBuffer[(now_menu - 1) % NUM_PER_PAGE][0], BITMAP_ARRAY_RIGHT, sizeof(BITMAP_ARRAY_RIGHT));
    memcpy(&gFrameBuffer[(now_menu - 1) % NUM_PER_PAGE][120], BITMAP_ARRAY_LEFT, sizeof(BITMAP_ARRAY_LEFT));
    sprintf(str, "%02d/%02d", now_menu, sum_menu);
    UI_PrintStringSmall(str, 0, 0, 6);
    ST7565_BlitFullScreen();
    ST7565_BlitStatusLine();
}


const uint8_t BITMAP_ARRAY_DOWN[5] =
        {
                0b00000110,
                0b00011110,
                0b01111110,
                0b00011110,
                0b00000110
        };
const uint8_t BITMAP_ARRAY_UP[5] =
        {
                0b01100000,
                0b01111000,
                0b01111110,
                0b01111000,
                0b01100000
        };

const uint8_t BITMAP_ARRAY_RIGHT[7] =
        {
//                0b00000000,
                0b01111111,
                0b01111111,
                0b00111110,
                0b00111110,
                0b00011100,
                0b00011100,
                0b00001000
        };
const uint8_t BITMAP_ARRAY_LEFT[7] =
        {
//                0b00000000,
                0b00001000,
                0b00011100,
                0b00011100,
                0b00111110,
                0b00111110,
                0b01111111,
                0b01111111
        };