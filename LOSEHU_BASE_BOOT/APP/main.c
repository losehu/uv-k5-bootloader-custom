#include "delay.h"
#include "key.h"
#include "iap.h"
#include "eeprom.h"
#include "string.h"
#include "port.h"
// void write_to_memory(uint32_t address, uint32_t data) {
//    // 将地址数值转换为指针
//    uint32_t *target_address = (uint32_t *) address;
//    // 向目标地址写入数据
//    *target_address = data;
//    // 为了避免优化，确保代码不会被优化掉
//    volatile uint32_t read_back = *target_address;
//	 
//}

typedef void (*pFunction)(void);

/* APP flash address */
#define APP_FLASH_ADDR             (0x20000800)

void jump_to_app(void) {
    uint32_t JumpAddress;
    pFunction Jump_To_Application;

    /* 检查栈顶地址是否合法 */

    /* 屏蔽所有中断，防止在跳转过程中，中断干扰出现异常 */
    __disable_irq();

    /* 用户代码区第二个 字 为程序开始地址(复位地址) */
    JumpAddress = *(__IO
    uint32_t *) (APP_FLASH_ADDR + 4);

    /* Initialize user application's Stack Pointer */
    /* 初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址) */
    __set_MSP(*(__IO
    uint32_t *) APP_FLASH_ADDR);

    /* 类型转换 */
    Jump_To_Application = (pFunction) JumpAddress;

    /* 跳转到 APP */
    Jump_To_Application();

}


void write_to_memory1(uint32_t address, uint32_t *data, size_t length) {
    // 将地址数值转换为指针
    uint32_t *target_address = (uint32_t *) address;

    // 循环写入数据到目标地址
    for (size_t i = 0; i < length; i++) {
        target_address[i] = data[i];
        // 为了避免优化，确保代码不会被优化掉
        volatile uint32_t read_back = target_address[i];
    }
}


int main(void) {
    SystemInit();           //时钟初始化
    Key_Init();
    delay_init();           //延时初始化
    uint8_t boot_mode = 1;
    if (!GPIO_GetBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) || !GPIO_GetBit(GPIOA, GPIO_PIN3)) {
        if (!GPIO_GetBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)) {
            boot_mode = 2;
        }
        EEPROM_WriteBuffer(0X01FF0, (uint8_t * ) & boot_mode, 1);//进入引导
        LED1_OFF;
#define NUM  16
        for (int i = 0; i < 12 * 1024 / NUM; i += 4) {
            uint32_t c[NUM];
            EEPROM_ReadBuffer(0x41000 + i * NUM, (uint8_t * )
            c, NUM * 4);
            write_to_memory1(0x20000800 + i * NUM, c, NUM);
        }
        jump_to_app();
    }
    boot_to_app();
}

