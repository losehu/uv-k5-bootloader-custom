#ifndef __DP32G030_TIMERPLUS_H__
#define __DP32G030_TIMERPLUS_H__

#include "DP32G030.h"

typedef enum
{
	HALL_0  = 0x01,             //HALL通道0
	HALL_1  = 0x02,             //HALL通道1
	HALL_2  = 0x04,             //HALL通道2
} TIMPLUS_HallTypeDef;

typedef enum
{
	TIMPLUS_LOW  = 0x01,        //低16位定时器
	TIMPLUS_HIGH = 0x02,        //高16位定时器
	TIMPLUS_BOTH = 0x03,        
} TIMPLUS_TypeTypeDef;

typedef enum
{
	TIMER_MODE = 0x00,          //定时模式
	COUNT_MODE = 0x01,          //计数模式
	INCAP_MODE = 0x02,          //输入捕获模式
	HALL_MODE  = 0x03,          //HALL模式
} TIMPLUS_ModeTypeDef;

typedef enum
{
	SYSCLK_DIV = 0x00,          //系统时钟分频
	CNTSRC0    = 0x01,          //外部输入信号0
	CNTSRC1    = 0x02,          //外部输入信号1
} TIMPLUS_ClkSelTypeDef;

typedef enum
{
	TIMPLUS_IN0 = 0x00,         //定时器输入通道0
	TIMPLUS_IN1 = 0x01,         //定时器输入通道1
} TIMPLUS_ExtSelTypeDef;

typedef enum
{
	EXTLEVEL_RISE = 0x00,       //计数模式或输入捕获模式输入信号有效边沿选择上升沿
	EXTLEVEL_FALL = 0x01,       //计数模式或输入捕获模式输入信号有效边沿选择下降沿
	EXTLEVEL_BOTH = 0x02,       //计数模式或输入捕获模式输入信号有效边沿选择双边沿
} TIMPLUS_ExtLevelTypeDef;


typedef struct
{
	uint16_t                ClkDiv;       //时钟分频
	
	TIMPLUS_ModeTypeDef     Mode;         //工作模式
	
	TIMPLUS_ClkSelTypeDef   ClkSel;       //计数时钟源选择  
	
	TIMPLUS_ExtSelTypeDef   ExtSel;       //计数模式或输入捕获模式输入信号选择
	
	TIMPLUS_ExtLevelTypeDef ExtLevel;     //计数模式或输入捕获模式输入信号有效边沿选择
	
	FunctionalState         DMAEn;        //DMA读取捕获值使能
	
	FunctionalState         OutEn;        //周期脉冲输出使能 
	
	uint16_t                Period;       //周期配置值	
	
	FunctionalState         Ovf_IE;       //溢出中断使能
	
	FunctionalState         RIse_IE;      //上升沿中断使能
	
	FunctionalState         Fall_IE;      //下降沿中断使能
	
} TIMPLUS_CommonInitTypeDef;


typedef struct
{
	FunctionalState         Hall0_Rise_IE;     //HALL0上升沿中断使能
	
	FunctionalState         Hall0_Fall_IE;     //HALL0下降沿中断使能
	
	FunctionalState         Hall1_Rise_IE;     //HALL1上升沿中断使能
	
	FunctionalState         Hall1_Fall_IE;     //HALL1下降沿中断使能
	
	FunctionalState         Hall2_Rise_IE;     //HALL2上升沿中断使能
	
	FunctionalState         Hall2_Fall_IE;     //HALL2下降沿中断使能	
} TIMPLUS_HallInitTypeDef;


//断言  TIMPLUS
#define IS_TIMPLUS_ALL(TIMPLUS)      ((TIMPLUS) == TIMPLUS0 || (TIMPLUS) == TIMPLUS1)

//断言  TIMPLUS 模式
#define IS_TIMPLUS_TYPE(TYPE)        ((TYPE) == TIMPLUS_LOW || (TYPE) == TIMPLUS_HIGH || (TYPE) == TIMPLUS_BOTH)

//断言  TIMPLUS预分频系数  
#define IS_TIMPLUS_CLKDIV(CLKDIV)    ((CLKDIV) <= 65535)

//断言  TIMPLUS工作模式
#define IS_TIMPLUS_MODE(MODE)        ((MODE) == TIMER_MODE || (MODE) == COUNT_MODE || (MODE) == INCAP_MODE || (MODE) == HALL_MODE) 

//断言  TIMPLUS计数时钟选择
#define IS_TIMPLUS_CLKSRC(CLKSRC)    ((CLKSRC) == SYSCLK_DIV || (CLKSRC) == CNTSRC0 || (CLKSRC) == CNTSRC1)                

//断言  TIMPLUS计数模式或输入捕获模式输入信号选择
#define IS_TIMPLUS_EXTSEL(EXTSEL)    ((EXTSEL) == TIMPLUS_IN0 || (EXTSEL) == TIMPLUS_IN1)

//断言  TIMPLUS计数模式或输入捕获模式输入信号有效边沿选择
#define IS_TIMPLUS_EXTLEVEL(EXTLEVEL)    ((EXTLEVEL) == EXTLEVEL_RISE || (EXTLEVEL) == EXTLEVEL_FALL || (EXTLEVEL) == EXTLEVEL_BOTH)

//断言  TIMPLUS周期
#define IS_TIMPLUS_PERIOD(PERIOD)    (((PERIOD) > 0) && ((PERIOD) < 65536))

//断言  TIMPLUS DMA读取捕获值使能
#define IS_TIMPLUS_DMAEN(OUTEN)        (((DMAEN) == ENABLE) || ((DMAEN) == DISABLE))

//断言  TIMPLUS周期脉冲输出使能 
#define IS_TIMPLUS_OUTEN(OUTEN)        (((OUTEN) == ENABLE) || ((OUTEN) == DISABLE))

//断言  TIMPLUS溢出中断使能
#define IS_TIMPLUS_OVF_IE(OVF_IE)      (((OVF_IE) == ENABLE) || ((OVF_IE) == DISABLE))

//断言  TIMPLUS上升沿中断使能
#define IS_TIMPLUS_RISE_IE(RISE_IE)    (((RISE_IE) == ENABLE) || ((RISE_IE) == DISABLE))

//断言  TIMPLUS下降沿中断使能
#define IS_TIMPLUS_FALL_IE(FALL_IE)    (((FALL_IE) == ENABLE) || ((FALL_IE) == DISABLE))

//断言  TIMPLUS HALL0上升沿中断使能
#define IS_TIMPLUS_HALL0_RISE_IE(HALL0_RISE_IE)    (((HALL0_RISE_IE) == ENABLE) || ((HALL0_RISE_IE) == DISABLE))

//断言  TIMPLUS HALL0下降沿中断使能
#define IS_TIMPLUS_HALL0_FALL_IE(HALL0_FALL_IE)    (((HALL0_FALL_IE) == ENABLE) || ((HALL0_FALL_IE) == DISABLE))

//断言  TIMPLUS HALL1上升沿中断使能
#define IS_TIMPLUS_HALL1_RISE_IE(HALL1_RISE_IE)    (((HALL1_RISE_IE) == ENABLE) || ((HALL1_RISE_IE) == DISABLE))

//断言  TIMPLUS HALL1下降沿中断使能
#define IS_TIMPLUS_HALL1_FALL_IE(HALL1_FALL_IE)    (((HALL1_FALL_IE) == ENABLE) || ((HALL1_FALL_IE) == DISABLE))

//断言  TIMPLUS HALL0上升沿中断使能
#define IS_TIMPLUS_HALL2_RISE_IE(HALL2_RISE_IE)    (((HALL2_RISE_IE) == ENABLE) || ((HALL2_RISE_IE) == DISABLE))

//断言  TIMPLUS HALL0下降沿中断使能
#define IS_TIMPLUS_HALL2_FALL_IE(HALL2_FALL_IE)    (((HALL2_FALL_IE) == ENABLE) || ((HALL2_FALL_IE) == DISABLE))

//断言  TIMPLUS HALL通道
#define IS_TIMPLUS_HALL_TYPE(HALL_TYPE)            ((HALL_TYPE) >= HALL_0 && (HALL_TYPE) <= (HALL_0 + HALL_1 + HALL_2))


void TIMPLUS_Common_Init(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct);      //TIMPLUS公共参数初始化

void TIMPLUS_Hall_Init(TIMPLUS_TypeDef * TIMPLUSx, TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct);                                    //TIMPLUS通道初始化

void TIMPLUS_Start(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                                 //启动定时器，从初始值开始计时/计数

void TIMPLUS_Stop(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                                  //停止定时器

void TIMPLUS_SetClkDiv(TIMPLUS_TypeDef * TIMPLUSx,uint16_t Clk_Div);                                                     //设置预分频系数   实际分频为配置值加1

void TIMPLUS_SetMode(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ModeTypeDef Mode);                      //设置工作模式

void TIMPLUS_SetDMAEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState DMAEn);                        //设置DMA读取捕获值使能或者禁能

void TIMPLUS_SetClkSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ClkSelTypeDef ClkSel);                //设置计数时钟源

void TIMPLUS_SetExtSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtSelTypeDef ExtSel);                //设置计数模式或输入捕获模式输入信号

void TIMPLUS_SetExtLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtLevelTypeDef ExtLevel);          //设置计数模式或输入捕获模式输入信号有效边沿

void TIMPLUS_SetOutEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState OutEn);                        //设置定时模式下周期脉冲输出

void TIMPLUS_SetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,uint16_t Period);                             //设置定时器周期配置值

uint16_t TIMPLUS_GetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                         //获取定时器周期配置值

uint16_t TIMPLUS_GetCurrentValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                   //获取定时器当前计数值

uint16_t TIMPLUS_GetCaptureValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                   //获取定时器捕获值

uint8_t TIMPLUS_GetHallLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallLevel);                                  //获取HALL初始电平

void TIMPLUS_IntOvfEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                              //设置定时器溢出中断使能

void TIMPLUS_IntOvfDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //设置定时器溢出中断禁能

void TIMPLUS_IntOvfClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //清除定时器溢出中断状态  

uint8_t TIMPLUS_IntOvfState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                        //获取定时器溢出中断状态                                                                     
                                                           
void TIMPLUS_IntRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //设置定时器输入脉冲上升沿中断使能

void TIMPLUS_IntRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //设置定时器输入脉冲上升沿中断禁能

void TIMPLUS_IntRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //清除定时器输入脉冲上升沿中断状态

uint8_t TIMPLUS_IntRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                       //获取定时器输入脉冲上升沿中断状态   

void TIMPLUS_IntFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //设置定时器输入脉冲下降沿中断使能

void TIMPLUS_IntFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //设置定时器输入脉冲下降沿中断禁能

void TIMPLUS_IntFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //清除定时器输入脉冲下降沿中断状态

uint8_t TIMPLUS_IntFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                       //获取定时器输入脉冲下降沿中断状态

void TIMPLUS_IntHallRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                     //设置定时器HALL上升沿中断使能

void TIMPLUS_IntHallRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //设置定时器HALL上升沿中断禁能

void TIMPLUS_IntHallRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //清除定时器HALL上升沿中断状态

uint8_t TIMPLUS_IntHallRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                               //获取定时器HALL上升沿中断状态                                    

void TIMPLUS_IntHallFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                     //设置定时器HALL下降沿中断使能

void TIMPLUS_IntHallFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //设置定时器HALL下降沿中断禁能

void TIMPLUS_IntHallFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //清除定时器HALL下降沿中断状态

uint8_t TIMPLUS_IntHallFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                               //获取定时器HALL下降沿中断状态



#endif //__DP32G030_TIMERPLUS_H__
