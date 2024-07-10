#ifndef __DP32G030_TIMERBASE_H__
#define	__DP32G030_TIMERBASE_H__

#include "DP32G030.h"


typedef enum
{
	TIMBASE_LOW  = 0x01,
	TIMBASE_HIGH = 0x02,
	TIMBASE_BOTH = 0x03,
} TIMBASE_TypeTypeDef;


typedef struct
{
	uint16_t                ClkDiv;       //时钟分频
	
	uint16_t                Period;       //周期配置值	
	
	FunctionalState         Ovf_IE;       //溢出中断使能
	
} TIMBASE_InitTypeDef;


//断言  TIMBASE
#define IS_TIMBASE_ALL(TIMBASE)      ((TIMBASE) == TIMBASE0 || (TIMBASE) == TIMBASE1 || (TIMBASE) == TIMBASE2)

//断言  TIMBASE模式
#define IS_TIMBASE_TYPE(TYPE)        ((TYPE) == TIMBASE_LOW || (TYPE) == TIMBASE_HIGH || (TYPE) == TIMBASE_BOTH)

//断言  TIMBASE预分频系数  
#define IS_TIMBASE_CLKDIV(CLKDIV)    ((CLKDIV) <= 65535)

//断言  TIMBASE周期
#define IS_TIMBASE_PERIOD(PERIOD)    (((PERIOD) > 0) && ((PERIOD) <= 65535))

//断言  TIMBASE溢出中断使能
#define IS_TIMBASE_OVF_IE(OVF_IE)      (((OVF_IE) == ENABLE) || ((OVF_IE) == DISABLE))


void TIMBASE_Init(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type,TIMBASE_InitTypeDef * TIMBASE_InitStruct);    //定时器初始化

void TIMBASE_Start(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                          //启动定时器

void TIMBASE_Stop(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                           //停止定时器

void TIMBASE_SetClkDiv(TIMBASE_TypeDef * TIMBASEx,uint16_t Clk_Div);                              //设置定时器预分频系数  

void TIMBASE_SetPeriod(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type,uint16_t Period);      //设置定时器周期值   

uint16_t TIMBASE_GetPeriod(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                  //获取定时器周期值            

uint16_t TIMBASE_GetCurValue(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                //获取定时器当前值

void TIMBASE_INTEn(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                          //定时器中断使能

void TIMBASE_INTDis(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                         //定时器中断禁能

void TIMBASE_INTClr(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                         //定时器中断清除

uint8_t TIMBASE_INTStat(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type);                     //获取定时器中断状态


#endif //__DP32G030_TIMERBASE_H__
