//
// Created by RUPC on 2024/6/28.
//

#ifndef UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_DISPLAY_H
#define UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_DISPLAY_H
#include "key.h"
#include "../external/printf/printf.h"
#include "../bsp/dp32g030/gpio.h"
#include "../driver/gpio.h"
#include "../sram-overlay.h"
#include "string.h"
#include "../ui/helper.h"
#include "../driver/system.h"
#include "../board.h"
#include "../bsp/dp32g030/syscon.h"
#include "../driver/systick.h"
#include "../driver/eeprom.h"
#include "../driver/st7565.h"
#include "../driver/keyboard.h"
#include "../external/CMSIS_5/Device/ARM/ARMCM0/Include/ARMCM0.h"


#define NUM_PER_PAGE 6
void SELECT_DISPLAY() ;

#endif //UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_DISPLAY_H
