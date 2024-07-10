#ifndef __KEY_H
#define __KEY_H

#include "common.h"


#define KEY1_GPIO_PORT    	GPIOC		                /* GPIO端口 */
#define KEY1_GPIO_PIN		GPIO_PIN5		        /* 连接到KEY1的GPIO */


/* 定义LED1连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED1引脚 */
#define LED1_GPIO_PORT    	GPIOB                /* GPIO端口 */
#define LED1_GPIO_PIN		GPIO_PIN6			        /* 连接到LED1的GPIO */

/* 定义LED2连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED2引脚 */
#define SCL_GPIO_PORT    	GPIOA		                /* GPIO端口 */
#define SCL_GPIO_PIN		GPIO_PIN10			        /* 连接到LED2的GPIO */

/* 定义LED3连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED3引脚 */
#define SDA_GPIO_PORT    	GPIOA		                /* GPIO端口 */
#define SDA_GPIO_PIN		GPIO_PIN11			        /* 连接到LED3的GPIO */




/* 定义控制IO的宏  此处定义的LED都是共阳极供电的，也就是输出低电平LED点亮*/
#define LED1_TOGGLE		   GPIO_InvBit(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF		   GPIO_SetBit(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_ON			   GPIO_ClrBit(LED1_GPIO_PORT,LED1_GPIO_PIN)





extern void Key_Init(void);

#endif
