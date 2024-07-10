#ifndef __DP32G030_WWDT_H__
#define __DP32G030_WWDT_H__

#include "DP32G030.h"

typedef enum
{ 
	WWDT_CLKDIV_1 =  0x00,       //时钟1分频
	WWDT_CLKDIV_2 =  0x01,       //时钟2分频
	WWDT_CLKDIV_4 =  0x02,       //时钟4分频
	WWDT_CLKDIV_8 =  0x03        //时钟8分频
} WWDT_ClkDiv_TypeDef;


typedef struct
{                                               
	WWDT_ClkDiv_TypeDef    ClkDiv;            //时钟预分频
	uint8_t                Int_Load;          //中断比较值
	uint8_t                Rst_Load;          //复位比较值
	FunctionalState        IntEn;             //中断使能选择
	FunctionalState        PresetIntEn;       //预复位中断使能选择
} WWDT_InitTypeDef;


//断言  WWDT时钟预分频
#define IS_WWDT_CLKDIV(WWDT_CLKDIV)  (((WWDT_CLKDIV) == WWDT_CLKDIV_1) || ((WWDT_CLKDIV) == WWDT_CLKDIV_2)  \
                                      ((WWDT_CLKDIV) == WWDT_CLKDIV_4) || ((WWDT_CLKDIV) == WWDT_CLKDIV_8)) 

//断言  WWDT中断比较值
#define IS_WWDT_INTLOAD(WWDT_INTLOAD) ((WWDT_INTLOAD) > 0x00 && (WWDT_INTLOAD) <= 0x7F)

//断言  WWDT复位比较值
#define IS_WWDT_RSTLOAD(WWDT_RSTLOAD) ((WWDT_RSTLOAD) > 0x00 && (WWDT_RSTLOAD) <= 0x3F)

//断言  WWDT中断使能
#define IS_INT_EN(INT_EN)             (((INT_EN) == ENABLE) || ((INT_EN) == DISABLE))

//断言  WWDT预复位中断使能
#define IS_PREINT_EN(PREINT_EN)       (((PREINT_EN) == ENABLE) || ((PREINT_EN) == DISABLE))



void WWDT_Init(WWDT_InitTypeDef * WWDT_InitStruct);  //WWDT初始化

void WWDT_Start(void);                               //启动WWDT

void WWDT_Stop(void);                                //停止WWDT

void WWDT_Feed(void);                                //WWDT喂狗 

uint8_t WWDT_Read(void);                             //读WWDT的当前计数值

void WWDT_INT_Enable(void);                          //WWDT窗口中断使能

void WWDT_INT_Disable(void);                         //WWDT窗口中断禁能

uint8_t WWDT_INTStat(void);                          //WWDT窗口中断状态查询

void WWDT_INTClr(void);                              //WWDT窗口中断标志清除

void WWDT_PRESETINT_Enable(void);                    //WWDT预复位中断使能

void WWDT_PRESETINT_Disable(void);                   //WWDT预复位中断禁能

uint8_t WWDT_PRESETINTStat(void);                    //WWDT预复位中断状态查询

void WWDT_PRESETINTClr(void);                        //WWDT预复位中断标志清除


#endif //__DP32G030_WWDT_H__
