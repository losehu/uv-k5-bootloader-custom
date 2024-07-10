#include "key.h"




/***********************************************
KEY初始化函数

按键按下后，采集到低电平，
没有按下时，采集到高电平
***********************************************/
void Key_Init(void)
{
	
	
	    GPIO_InitTypeDef GPIO_InitStruct;              /*定义一个GPIO_InitTypeDef类型的结构体*/
	
	GPIO_InitStruct.Pin = LED1_GPIO_PIN;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	
	
	GPIO_InitStruct.Pin = SCL_GPIO_PIN;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(SCL_GPIO_PORT,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/

	
		
	GPIO_InitStruct.Pin = SDA_GPIO_PIN;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(SDA_GPIO_PORT,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	
	GPIO_InitStruct.Pin = KEY1_GPIO_PIN;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PU_IN;             /*设置引脚模式为上拉输入*/
	
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	

		
	GPIO_InitStruct.Pin = GPIO_PIN3;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PU_IN;             /*设置引脚模式为上拉输入*/
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/

	
	
	
			
	GPIO_InitStruct.Pin = GPIO_PIN4;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	
	
		GPIO_InitStruct.Pin = GPIO_PIN5;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	
	
		GPIO_InitStruct.Pin = GPIO_PIN6;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
	
	
		GPIO_InitStruct.Pin = GPIO_PIN7;           /*选择要控制的GPIO引脚*/
	
	GPIO_InitStruct.Mode = MODE_PP_OUT;            /*设置引脚模式为推挽输出*/
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);    /*调用库函数，初始化GPIO*/
	
GPIO_SetBit(GPIOA,GPIO_PIN5);
GPIO_SetBit(GPIOA,GPIO_PIN6);
GPIO_SetBit(GPIOA,GPIO_PIN7);
	GPIO_ClrBit(GPIOA,GPIO_PIN4);

}



