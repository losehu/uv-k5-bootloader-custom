#ifndef __DP32G030_PWMBASE_H__
#define __DP32G030_PWMBASE_H__

#include "DP32G030.h"


typedef enum
{ 
	PWMBASE_CH0 =  0x01,                 //通道0   
	
	PWMBASE_CH1 =  0x02,                 //通道1
	
	PWMBASE_CH2 =  0x04,                 //通道2
} PWMBASE_Channel_TypeDef;


typedef struct {
	uint16_t ClkDiv;		             //1---65536分频
	
	uint16_t Period;		             //周期,16位
	
	FunctionalState  OvfIE;		         //周期溢出中断使能	
} PWMBASE_CommonInitTypeDef;


typedef struct {
	PWMBASE_Channel_TypeDef Channel;     //通道选择   
	
	uint16_t Comp;                       //翻转点
	
	FunctionalState  CompIE;             //翻转点中断使能
	
	FunctionalState  Inv;                //输出信号电平翻转
	
	FunctionalState  OutEn;              //波形输出使能
} PWMBASE_ChannelInitTypeDef;


//断言  PWMBASE
#define IS_PWMBASE_ALL(PWMBASE)  (((PWMBASE) == PWMBASE0)  || ((PWMBASE) == PWMBASE1))

//断言  PWMBASE通道
#define IS_PWMBASE_CHANNEL(PWMBASE_CHANNEL)  ((PWMBASE_CHANNEL) == PWMBASE_CH0 || (PWMBASE_CHANNEL) == PWMBASE_CH1 || (PWMBASE_CHANNEL) == PWMBASE_CH2)

//断言  PWMBASE预分频系数  
#define IS_PWMBASE_CLKDIV(PWMBASE_CLKDIV)    ((PWMBASE_CLKDIV) < 65536)

//断言  PWMBASE周期
#define IS_PWMBASE_PERIOD(PWMBASE_PERIOD)    (((PWMBASE_PERIOD) > 0) && ((PWMBASE_PERIOD) < 65536))

//断言  PWMBASE翻转点
#define IS_PWMBASE_COMP(PWMBASE_COMP)        (((PWM_COMP) < 65536))

//断言  PWMBASE输出信号翻转
#define IS_PWMBASE_INV(PWMBASE_INV)          (((PWMBASE_INV) == ENABLE) || ((PWMBASE_INV) == DISABLE))

//断言  PWMBASE输出信号使能
#define IS_PWMBASE_OUTEN(PWMBASE_OUTEN)      (((PWMBASE_OUTEN) == ENABLE) || ((PWMBASE_OUTEN) == DISABLE))

//断言  PWMBASE周期溢出中断
#define IS_PWMBASE_IE_OVF(PWMBASE_IE_OVF)    (((PWMBASE_IE_OVF) == ENABLE) || ((PWMBASE_IE_OVF) == DISABLE))

//断言  PWMBASE翻转点中断
#define IS_PWMBASE_IE_COMP(PWMBASE_IE_COMP)  (((PWMBASE_IE_COMP) == ENABLE) || ((PWMBASE_IE_COMP) == DISABLE))


void PWMBASE_Common_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct);       //PWMBASE公共参数初始化

void PWMBASE_Channel_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct);    //PWMBASE通道初始化

void PWMBASE_Start(PWMBASE_TypeDef * PWMBASEx);                                             //启动PWMBASE，开始PWM输出

void PWMBASE_Stop(PWMBASE_TypeDef * PWMBASEx);                                              //关闭PWMBASE，停止PWM输出

void PWMBASE_SetClkDiv(PWMBASE_TypeDef * PWMBASEx,uint16_t Clk_Div);                        //设置预分频系数   实际分频为配置值加1

void PWMBASE_SetOutInv(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutInv);     //PWMBASE输出信号翻转配置

void PWMBASE_SetOutEn(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutEn);       //PWMBASE输出使能配置

void PWMBASE_SetPeriod(PWMBASE_TypeDef * PWMBASEx, uint16_t Period);                        //设置周期

uint32_t PWMBASE_GetPeriod(PWMBASE_TypeDef * PWMBASEx);                                     //获取周期

void PWMBASE_SetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx,uint16_t Comp);                //设置翻转点

uint32_t PWMBASE_GetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                          //获取配置的翻转点

void PWMBASE_IntCompEn(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                            //PWMBASE翻转点中断使能

void PWMBASE_IntCompDis(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                           //PWMBASE翻转点中断禁能

void PWMBASE_IntCompClr(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                           //PWMBASE翻转点中断标志清除

uint8_t PWMBASE_IntCompState(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                      //PWMBASE翻转点中断状态  

void PWMBASE_IntOvfEn(PWMBASE_TypeDef * PWMBASEx);                                          //PWMBASE周期溢出中断使能

void PWMBASE_IntOvfDis(PWMBASE_TypeDef * PWMBASEx);                                         //PWMBASE周期溢出中断禁能

void PWMBASE_IntOvfClr(PWMBASE_TypeDef * PWMBASEx);                                         //PWMBASE周期溢出中断标志清除

uint8_t PWMBASE_IntOvfState(PWMBASE_TypeDef * PWMBASEx);                                    //PWMBASE周期溢出中断状态



#endif //__DP32G030_PWMBASE_H__
