//
// Created by RUPC on 2024/6/28.
//

#ifndef UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_EEPROM_H
#define UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_EEPROM_H
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

void GET_FIRMWARE_NUM() ;
#define FIRMWARE_NUM_ADD 0X40000
void LOAD_FIRMWARE();

#endif //UV_K5_FIRMWARE_CUSTOM_RAM_LOAD_EEPROM_H
