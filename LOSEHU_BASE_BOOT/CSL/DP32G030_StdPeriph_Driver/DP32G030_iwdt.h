#ifndef __DP32G030_IWDT_H__
#define __DP32G030_IWDT_H__

#include "DP32G030.h"


typedef struct
{                                               
	FunctionalState   IntEn;       //中断使能选择
	uint32_t          Load;        //装载值
} IWDT_InitTypeDef;


//断言IWDT中断使能选择
#define IS_IWDT_INT(IWDT_INT)        (((IWDT_INT) == DISABLE) || ((IWDT_INT) == ENABLE))

//断言WDT装载值
#define IS_IWDT_LOAD(IWDT_LOAD)      ((IWDT_LOAD) != 0 && (IWDT_LOAD) <= 0xFFFFF)


void IWDT_Init(IWDT_InitTypeDef * IWDT_InitStruct);  //IWDT初始化

void IWDT_Start(void);                               //启动IWDT

void IWDT_Stop(void);                                //停止IWDT

void IWDT_FEED(void);                                //IWDT喂狗

void IWDT_INT_Enable(void);                          //IWDT中断使能

void IWDT_INT_Disable(void);                         //IWDT中断禁能

uint8_t IWDT_INTStat(void);                          //查询IWDT中断状态

void IWDT_INTClr(void);                              //清除IWDT中断状态


#endif //__DP32G030_IWDT_H__
