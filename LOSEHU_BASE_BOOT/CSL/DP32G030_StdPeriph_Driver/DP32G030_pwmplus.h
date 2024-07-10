#ifndef __DP32G030_PWMPLUS_H__
#define __DP32G030_PWMPLUS_H__

#include "DP32G030.h"


typedef enum
{ 
	CLKSRC_DIV             =  0x00,              // 内部预分频时钟作为计数时钟
	CLKSRC_EXT_PULSE0      =  0x01,              // 外部输入时钟0作为计数时钟
	CLKSRC_EXT_PULSE1      =  0x02,              // 外部输入时钟1作为计数时钟
	CLKSRC_TIMPLUS0_LOW16  =  0x03,              // TIMPLUS0低16位定时器作为计数时钟
	CLKSRC_TIMPLUS0_HIGH16 =  0x04,              // TIMPLUS0高16位定时器作为计数时钟
	CLKSRC_TIMPLUS1_LOW16  =  0x05,              // TIMPLUS1低16位定时器作为计数时钟
	CLKSRC_TIMPLUS1_HIGH16 =  0x06,              // TIMPLUS1高16位定时器作为计数时钟
} PWMPLUS_Clk_Src_TypeDef;


typedef enum
{ 
	SINGLE_EDGE_ALIGN   =  0x00,       // 单次边沿对齐输出
	CYCLE_EDGE_ALIGN    =  0x01,       // 循环边沿对齐输出
	SINGLE_CENTER_ALIGN =  0x02,       // 单次中心对齐输出 
	CYCLE_CENTER_ALIGN  =  0x03,       // 循环中心对齐输出 
} PWMPLUS_Mode_TypeDef;

typedef enum
{ 
	DIR_UP   =  0x00,                  // 向上计数
	DIR_DOWN =  0x01,                  // 向下计数
} PWMPLUS_Dir_TypeDef;

typedef enum
{ 
	PWMPLUS_CH0   =  0x01,             //通道CH0     
	PWMPLUS_CH1   =  0x02,             //通道CH1   
	PWMPLUS_CH2   =  0x04,             //通道CH2   
	PWMPLUS_CH0N  =  0x08,             //通道CH0N   
	PWMPLUS_CH1N  =  0x10,             //通道CH1N   
	PWMPLUS_CH2N  =  0x20,             //通道CH2N   
} PWMPLUS_Channel_TypeDef;

typedef enum
{ 
	LEVEL_LOW   =  0x00,               //低电平
	LEVEL_HIGH  =  0x01,               //高电平
} PWMPLUS_Level_TypeDef;

typedef enum
{ 
	BRAKE_FILTER_1   =  0x00,          //刹车滤波1个时钟周期                
	BRAKE_FILTER_2   =  0x01,          //刹车滤波2个时钟周期 
	BRAKE_FILTER_4   =  0x02,          //刹车滤波4个时钟周期 
	BRAKE_FILTER_8   =  0x03,          //刹车滤波8个时钟周期 
} PWMPLUS_BrakeFilter_TypeDef;

typedef enum
{ 
	NOSIGNAL_TRIG         =  0x00,     //无触发信号
	UP_OVF_TRIG           =  0x01,     //向上计数溢出触发
	DOWN_OVF_TRIG         =  0x02,     //向下计数溢出触发
	UPDOWN_OVF_TRIG       =  0x03,     //向上向下计数溢出触发
	CH0_UP_COMP_TRIG      =  0x04,     //通道0向上翻转点触发
	CH0_DOWN_COMP_TRIG    =  0x05,     //通道0向下翻转点触发
	CH0_UPDOWN_COMP_TRIG  =  0x06,     //通道0向上向下翻转点触发
	CH1_UP_COMP_TRIG      =  0x07,     //通道1向上翻转点触发 
	CH1_DOWN_COMP_TRIG    =  0x08,     //通道1向下翻转点触发
	CH1_UPDOWN_COMP_TRIG  =  0x09,     //通道1向上向下翻转点触发
	CH2_UP_COMP_TRIG      =  0x0A,     //通道2向上翻转点触发 
	CH2_DOWN_COMP_TRIG    =  0x0B,     //通道2向下翻转点触发
	CH2_UPDOWN_COMP_TRIG  =  0x0C,     //通道2向上向下翻转点触发
	UP_INCOMP_TRIG        =  0x0D,     //向上计数内部触发点触发
	DOWN_INCOMP_TRIG      =  0x0E,     //向下计数内部触发点触发   
	UPDOWN_INCOMP_TRIG    =  0x0F,     //向上向下计数内部触发点触发
} PWMPLUS_TrigSel_TypeDef;



typedef struct {
	
	PWMPLUS_Clk_Src_TypeDef Clk_Src;          //计数时钟选择     
	
	uint16_t ClkDiv;		                  //1---65536分频
	
	PWMPLUS_Mode_TypeDef Mode;                //模式   
	
	PWMPLUS_Dir_TypeDef Dir;                  //方向   0 向上计数  1 向下计数
	
	uint8_t Reload_Cnt;                       //自动装载次数
	
	uint16_t Period;		                  //周期,16位
	
	PWMPLUS_BrakeFilter_TypeDef Brake_Filter;      //刹车信号数字滤波  00 不滤波   01  2个时钟滤波  10 4个时钟滤波  11  8个时钟滤波
	
	PWMPLUS_Level_TypeDef Brake0_InputLevel;  //刹车0输入有效电平选择   0  低电平有效  1  高电平有效
	
	PWMPLUS_Level_TypeDef Brake1_InputLevel;  //刹车1输入有效电平选择   0  低电平有效  1  高电平有效
	
	PWMPLUS_Level_TypeDef Brake2_InputLevel;  //刹车2输入有效电平选择   0  低电平有效  1  高电平有效
	
	uint16_t Trig_Comp;                       //内部触发点
	
	PWMPLUS_TrigSel_TypeDef Trig0_Sel;        //输出的trig0信号功能选择
	
	PWMPLUS_TrigSel_TypeDef Trig1_Sel;        //输出的trig1信号功能选择
	
	PWMPLUS_TrigSel_TypeDef Trig2_Sel;        //输出的trig2信号功能选择
	
	PWMPLUS_TrigSel_TypeDef Trig3_Sel;        //输出的trig3信号功能选择
	
	FunctionalState Reload_IE;                //自动装载中断使能
	
	FunctionalState Brake0_IE;                //刹车0中断使能
	
	FunctionalState Brake1_IE;                //刹车1中断使能
	
	FunctionalState Brake2_IE;                //刹车2中断使能
	
	FunctionalState Up_OvfIE;		          //向上计数周期溢出中断使能
	
	FunctionalState Up_TrigCompIE;		      //向上计数内部触发点中断使能
	
	FunctionalState Down_OvfIE;		          //向下计数周期溢出中断使能
	
	FunctionalState Down_TrigCompIE;          //向下计数内部触发点中断使能
} PWMPLUS_CommonInitTypeDef;

typedef struct {
	PWMPLUS_Channel_TypeDef Channel;          //通道选择
	
	uint32_t Comp;                            //翻转点
	
	uint16_t DeadZone;                        //死区长度
	
	PWMPLUS_Level_TypeDef StartLevel;         //计数开始输出电平
	
	PWMPLUS_Level_TypeDef CHxIdleLevel;       //通道x空闲输出电平
	
	PWMPLUS_Level_TypeDef CHxNIdleLevel;      //通道xN空闲输出电平
	
	FunctionalState  CHxInv;                  //通道x输出信号电平翻转
	
	FunctionalState  CHxNInv;                 //通道xN输出信号电平翻转
	
	FunctionalState  CHxOutEn;                //通道x波形输出使能
	
	FunctionalState  CHxNOutEn;               //通道xN波形输出使能
	
	FunctionalState  Brake0_Enable;           //刹车0使能
	
	FunctionalState  Brake1_Enable;           //刹车1使能
	
	FunctionalState  Brake2_Enable;           //刹车2使能
	
	PWMPLUS_Level_TypeDef Brake_CHxOutLevel;  //刹车通道CHx输出电平
	
	PWMPLUS_Level_TypeDef Brake_CHxNOutLevel; //刹车通道CHxN输出电平
	
	FunctionalState Mask_CHx_Enable;          //通道CHx屏蔽使能
	
	FunctionalState Mask_CHxN_Enable;         //通道CHxN屏蔽使能
	
	PWMPLUS_Level_TypeDef Mask_CHx_Level;     //通道CHx屏蔽输出电平
	
	PWMPLUS_Level_TypeDef Mask_CHxN_Level;    //通道CHxN屏蔽输出电平
	
	FunctionalState Up_CompIE;		          //向上计数翻转点中断使能
	
	FunctionalState Down_CompIE;		      //向下计数翻转点中断使能	
} PWMPLUS_ChannelInitTypeDef;


//断言  PWMPLUS
#define IS_PWMPLUS_ALL(PWMPLUS)  (((PWMPLUS) == PWMPLUS0) || ((PWMPLUS) == PWMPLUS1))

//断言  PWMPLUS计数时钟选择
#define IS_PWMPLUS_CLKSRC(PWMPLUS_CLKSRC)    ((PWMPLUS_CLKSRC) == CLKSRC_DIV || (PWMPLUS_CLKSRC) == CLKSRC_TIMPLUS0_LOW16 || (PWMPLUS_CLKSRC) == CLKSRC_TIMPLUS0_HIGH16 || \
                                              (PWMPLUS_CLKSRC) == CLKSRC_TIMPLUS1_LOW16 || (PWMPLUS_CLKSRC) == CLKSRC_TIMPLUS1_HIGH16)                

//断言  PWMPLUS预分频系数  
#define IS_PWMPLUS_CLKDIV(PWMPLUS_CLKDIV)    ((PWMPLUS_CLKDIV) <= 65535)

//断言  PWMPLUS工作模式
#define IS_PWMPLUS_MODE(PWMPLUS_MODE)  ((PWMPLUS_MODE == SINGLE_EDGE_ALIGN)   || (PWMPLUS_MODE == CYCLE_EDGE_ALIGN) || \
                                        (PWMPLUS_MODE == SINGLE_CENTER_ALIGN) || (PWMPLUS_MODE == CYCLE_CENTER_ALIGN) )
//断言  PWMPLUS计数方向
#define IS_PWMPLUS_DIR(PWMPLUS_DIR)    ((PWMPLUS_DIR == DIR_UP) || (PWMPLUS_DIR == DIR_DOWN))
                                        
//断言  PWMPLUS所有通道
#define IS_PWMPLUS_CHANNEL_ALL(PWMPLUS_CHANNEL_ALL)  ((PWMPLUS_CHANNEL_ALL == PWMPLUS_CH0) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH0N) || \
                                                      (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH1) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH1N) || \
                                                      (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH2) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH2N))

//断言  PWMPLUS所有通道
#define IS_PWMPLUS_CHANNEL_HALF(PWMPLUS_CHANNEL_HALF)  ((PWMPLUS_CHANNEL_HALF == PWMPLUS_CH0) || (PWMPLUS_CHANNEL_HALF == PWMPLUS_CH1) || \
                                                        (PWMPLUS_CHANNEL_HALF == PWMPLUS_CH2) ) 
                                                      
//断言  PWMPLUS自动装载次数
#define IS_PWMPLUS_RELOAD_CNT(PWMPLUS_RELOAD_CNT)    ((PWMPLUS_RELOAD_CNT) <= 255)

//断言  PWMPLUS周期
#define IS_PWMPLUS_PERIOD(PWMPLUS_PERIOD)    (((PWMPLUS_PERIOD) > 0) && ((PWMPLUS_PERIOD) < 65536))

//断言  PWMPLUS翻转点
#define IS_PWMPLUS_COMP(PWMPLUS_COMP)    (((PWMPLUS_COMP) >= 0) && ((PWMPLUS_COMP) < 65536))

//断言  PWMPLUS死区长度
#define IS_PWMPLUS_DEADZONE(PWMPLUS_DEADZONE)    (((PWMPLUS_DEADZONE) >= 0) && ((PWMPLUS_DEADZONE) < 1024))

//断言  PWMPLUS刹车信号数字滤波
#define IS_PWMPLUS_BRAKE_FILTER(PWMPLUS_BRAKE_FILTER)    ((PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_1) || (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_2) || \
                                                          (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_4) || (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_8) )
//断言  PWMPLUS刹车信号有效电平
#define IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_BRAKE_LEVEL)    ((PWMPLUS_BRAKE_LEVEL == LEVEL_LOW) || (PWMPLUS_BRAKE_LEVEL == LEVEL_HIGH))
                                                      
//断言  PWMPLUS刹车信号使能
#define IS_PWMPLUS_BRAKE_ENABLE(PWMPLUS_BRAKE_ENABLE)    ((PWMPLUS_BRAKE_ENABLE == ENABLE) || (PWMPLUS_BRAKE_ENABLE == DISABLE))
                                                        
//断言  PWMPLUS输出的trig信号功能选择
#define IS_PWMPLUS_TRIG_SEL(PWMPLUS_TRIG_SEL)    (((PWMPLUS_TRIG_SEL) >= NOSIGNAL_TRIG) && ((PWMPLUS_TRIG_SEL) <= UPDOWN_INCOMP_TRIG))

//断言  PWMPLUS内部触发点
#define IS_PWMPLUS_TRIG_COMP(PWMPLUS_TRIG_COMP)    (((PWMPLUS_TRIG_COMP) > 0) && ((PWMPLUS_TRIG_COMP) < 65536))

//断言  PWMPLUS计数开始输出电平
#define IS_PWMPLUS_START_LEVEL(PWMPLUS_START_LEVEL)    (((PWMPLUS_START_LEVEL) == LEVEL_LOW) || ((PWMPLUS_START_LEVEL) == LEVEL_HIGH))

//断言  PWMPLUS通道空闲输出电平
#define IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_IDLE_LEVEL)    (((PWMPLUS_IDLE_LEVEL) == LEVEL_LOW) || ((PWMPLUS_IDLE_LEVEL) == LEVEL_HIGH))

//断言  PWMPLUS通道输出信号电平翻转
#define IS_PWMPLUS_OUTINV(PWMPLUS_OUTINV)            (((PWMPLUS_OUTINV) == ENABLE) || ((PWMPLUS_OUTINV) == DISABLE))

//断言  PWMPLUS通道波形输出使能
#define IS_PWMPLUS_OUTEN(PWMPLUS_OUTEN)        (((PWMPLUS_OUTEN) == ENABLE) || ((PWMPLUS_OUTEN) == DISABLE))

//断言  PWMPLUS刹车使能
#define IS_PWMPLUS_BRAKEEN(PWMPLUS_BRAKEEN)    (((PWMPLUS_BRAKEEN) == ENABLE) || ((PWMPLUS_BRAKEEN) == DISABLE))

//断言  PWMPLUS刹车通道输出电平
#define IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_BRAKE_OUTLEVEL)    (((PWMPLUS_BRAKE_OUTLEVEL) == LEVEL_LOW) || ((PWMPLUS_BRAKE_OUTLEVEL) == LEVEL_HIGH))

//断言  PWMPLUS通道屏蔽使能
#define IS_PWMPLUS_MASK_EN(PWMPLUS_MASK_EN)    (((PWMPLUS_MASK_EN) == ENABLE) || ((PWMPLUS_MASK_EN) == DISABLE))

//断言  PWMPLUS通道屏蔽输出电平
#define IS_PWMPLUS_MASK_LEVEL(PWMPLUS_MASK_LEVEL)    (((PWMPLUS_MASK_LEVEL) == LEVEL_LOW) || ((PWMPLUS_MASK_LEVEL) == LEVEL_HIGH))

//断言  PWMPLUS自动装载中断使能
#define IS_PWMPLUS_RELOAD_IE(PWMPLUS_RELOAD_IE)    (((PWMPLUS_RELOAD_IE) == ENABLE) || ((PWMPLUS_RELOAD_IE) == DISABLE))

//断言  PWMPLUS刹车0中断使能
#define IS_PWMPLUS_BRAKE0_IE(PWMPLUS_BRAKE0_IE)    (((PWMPLUS_BRAKE0_IE) == ENABLE) || ((PWMPLUS_BRAKE0_IE) == DISABLE))

//断言  PWMPLUS刹车1中断使能
#define IS_PWMPLUS_BRAKE1_IE(PWMPLUS_BRAKE1_IE)    (((PWMPLUS_BRAKE1_IE) == ENABLE) || ((PWMPLUS_BRAKE1_IE) == DISABLE))

//断言  PWMPLUS向上计数周期溢出中断使能
#define IS_PWMPLUS_UP_OVF_IE(PWMPLUS_UP_OVF_IE)    (((PWMPLUS_UP_OVF_IE) == ENABLE) || ((PWMPLUS_UP_OVF_IE) == DISABLE))

//断言  PWMPLUS向下计数周期溢出中断使能
#define IS_PWMPLUS_DOWN_OVF_IE(PWMPLUS_DOWN_OVF_IE)    (((PWMPLUS_DOWN_OVF_IE) == ENABLE) || ((PWMPLUS_DOWN_OVF_IE) == DISABLE))

//断言  PWMPLUS向上计数内部触发点中断使能
#define IS_PWMPLUS_UP_TRIGCOMP_IE(PWMPLUS_UP_TRIGCOMP_IE)    (((PWMPLUS_UP_TRIGCOMP_IE) == ENABLE) || ((PWMPLUS_UP_TRIGCOMP_IE) == DISABLE))

//断言  PWMPLUS向下计数内部触发点中断使能
#define IS_PWMPLUS_DOWN_TRIGCOMP_IE(PWMPLUS_DOWN_TRIGCOMP_IE)    (((PWMPLUS_DOWN_TRIGCOMP_IE) == ENABLE) || ((PWMPLUS_DOWN_TRIGCOMP_IE) == DISABLE))

//断言  PWMPLUS向上计数翻转点中断使能
#define IS_PWMPLUS_UP_COMP_IE(PWMPLUS_UP_COMP_IE)    (((PWMPLUS_UP_COMP_IE) == ENABLE) || ((PWMPLUS_UP_COMP_IE) == DISABLE))

//断言  PWMPLUS向下计数翻转点中断使能
#define IS_PWMPLUS_DOWN_COMP_IE(PWMPLUS_DOWN_COMP_IE)    (((PWMPLUS_DOWN_COMP_IE) == ENABLE) || ((PWMPLUS_DOWN_COMP_IE) == DISABLE))



void PWMPLUS_CommonInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_CommonInitTypeDef * PWMPLUS_CommonInitStruct);        //PWMPLUS公共参数初始化

void PWMPLUS_ChannelInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_ChannelInitTypeDef * PWMPLUS_ChannelInitStruct);     //PWMPLUS通道初始化

void PWMPLUS_Start(PWMPLUS_TypeDef * PWMPLUSx);                                                                   //启动PWMPLUS，开始PWM输出

void PWMPLUS_Stop(PWMPLUS_TypeDef * PWMPLUSx);                                                                    //关闭PWMPLUS，停止PWM输出

void PWMPLUS_SetClk_Src(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Clk_Src_TypeDef Clk_Src);                              //PWMPLUS时钟选择

void PWMPLUS_SetClkDiv(PWMPLUS_TypeDef * PWMPLUSx,uint16_t ClkDiv);                                                //设置预分频系数   实际分频为配置值加1

void PWMPLUS_SetMode(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Mode_TypeDef Mode);                                       //设置工作模式

void PWMPLUS_SetDir(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Dir_TypeDef Dir);                                          //设置计数方向

void PWMPLUS_SetReload_Cnt(PWMPLUS_TypeDef * PWMPLUSx,uint8_t Reload_Cnt);                                        //设置自动装载次数   实际装载次数为配置值加1

void PWMPLUS_SetBrake_Filter(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeFilter_TypeDef Brake_Filter);                //设置刹车滤波

void PWMPLUS_SetBrake_InputLevel(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Level_TypeDef Brake0_InputLevel,PWMPLUS_Level_TypeDef Brake1_InputLevel,PWMPLUS_Level_TypeDef Brake2_InputLevel);    //设置刹车输入有效电平选择 

void PWMPLUS_SetBrake_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Brake0_Enable,FunctionalState Brake1_Enable,FunctionalState Brake2_Enable);                          //设置刹车使能

void PWMPLUS_SetBrake_OutLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Brake_OutLevel);      //设置刹车时通道输出电平

void PWMPLUS_SetMask_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Mask_Enable);                  //设置屏蔽功能是否使能

void PWMPLUS_SetMask_Level(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Mask_Level);              //设置屏蔽输出电平

void PWMPLUS_SetStartLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef StartLevel);              //PWMPLUS计数开始输出电平

void PWMPLUS_SetIdleLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef  IdleLevel);               //PWMPLUS空闲输出电平配置

void PWMPLUS_SetOutEn(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutEn);                             //PWMPLUS输出使能

void PWMPLUS_SetOutInv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutInv);                           //PWMPLUS输出信号翻转

void PWMPLUS_SetPeriod(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Period);                                              //设置周期

uint32_t PWMPLUS_GetPeriod(PWMPLUS_TypeDef * PWMPLUSx);                                                           //获取周期

void PWMPLUS_SetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t Comp);                                      //设置翻转点

uint32_t PWMPLUS_GetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                                //获取配置的翻转点

void PWMPLUS_SetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t DeadZone);                              //设置通道死区长度

uint16_t PWMPLUS_GetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //获取通道死区长度

void PWMPLUS_SetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx, uint32_t Trig_Comp);                                        //设置内部触发点

uint32_t PWMPLUS_GetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx);                                                        //获取内部触发点

void PWMPLUS_SetTrig_Sel0(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //设置触发信号0功能选择

void PWMPLUS_SetTrig_Sel1(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //设置触发信号1功能选择

void PWMPLUS_SetTrig_Sel2(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //设置触发信号2功能选择

void PWMPLUS_SetTrig_Sel3(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //设置触发信号3功能选择

void PWMPLUS_IntReloadEn(PWMPLUS_TypeDef * PWMPLUSx);                                                             //设置自动装载中断使能

void PWMPLUS_IntReloadDis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //设置自动装载中断禁能

uint8_t PWMPLUS_IntReloadState(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取自动装载中断状态

void PWMPLUS_IntReloadClr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //清除自动装载中断状态

void PWMPLUS_IntBrake0En(PWMPLUS_TypeDef * PWMPLUSx);                                                             //设置刹车0中断使能
 
void PWMPLUS_IntBrake0Dis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //设置刹车0中断禁能

uint8_t PWMPLUS_IntBrake0State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取刹车0中断状态

void PWMPLUS_IntBrake0Clr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //清除刹车0中断状态

void PWMPLUS_IntBrake1En(PWMPLUS_TypeDef * PWMPLUSx);                                                             //设置刹车1中断使能

void PWMPLUS_IntBrake1Dis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //设置刹车1中断禁能

uint8_t PWMPLUS_IntBrake1State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取刹车1中断状态

void PWMPLUS_IntBrake1Clr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //清除刹车1中断状态

void PWMPLUS_IntBrake2En(PWMPLUS_TypeDef * PWMPLUSx);                                                             //设置刹车2中断使能

void PWMPLUS_IntBrake2Dis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //设置刹车2中断禁能

uint8_t PWMPLUS_IntBrake2State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取刹车2中断状态

void PWMPLUS_IntBrake2Clr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //清除刹车2中断状态

void PWMPLUS_IntUp_OvfEn(PWMPLUS_TypeDef * PWMPLUSx);                                                             //设置向上计数周期溢出中断使能

void PWMPLUS_IntUp_OvfDis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //设置向上计数周期溢出中断禁能

uint8_t PWMPLUS_IntUp_OvfState(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取向上计数周期溢出中断状态

void PWMPLUS_IntUp_OvfClr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //清除向上计数周期溢出中断状态

void PWMPLUS_IntUp_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx);                                                        //设置向上计数到达触发点中断使能

void PWMPLUS_IntUp_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx);                                                       //设置向上计数到达触发点中断禁能

uint8_t PWMPLUS_IntUp_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx);                                                  //获取向上计数到达触发点中断状态

void PWMPLUS_IntUp_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx);                                                       //清除向上计数到达触发点中断状态

void PWMPLUS_IntDown_OvfEn(PWMPLUS_TypeDef * PWMPLUSx);                                                           //设置向下计数周期溢出中断使能

void PWMPLUS_IntDown_OvfDis(PWMPLUS_TypeDef * PWMPLUSx);                                                          //设置向下计数周期溢出中断禁能

uint8_t PWMPLUS_IntDown_OvfState(PWMPLUS_TypeDef * PWMPLUSx);                                                     //获取向下计数周期溢出中断状态

void PWMPLUS_IntDown_OvfClr(PWMPLUS_TypeDef * PWMPLUSx);                                                          //清除向下计数周期溢出中断状态

void PWMPLUS_IntDown_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx);                                                      //设置向下计数到达触发点中断使能

void PWMPLUS_IntDown_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx);                                                     //设置向下计数到达触发点中断禁能

uint8_t PWMPLUS_IntDown_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx);                                                //获取向下计数到达触发点中断状态

void PWMPLUS_IntDown_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx);                                                     //清除向下计数到达触发点中断状态

void PWMPLUS_IntUp_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                               //设置向上计数到达翻转点中断使能

void PWMPLUS_IntUp_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                              //设置向上计数到达翻转点中断禁能

uint8_t PWMPLUS_IntUp_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                         //获取向上计数到达翻转点中断状态

void PWMPLUS_IntUp_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                              //清除向上计数到达翻转点中断状态

void PWMPLUS_IntDown_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                             //设置向下计数到达翻转点中断使能

void PWMPLUS_IntDown_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //设置向下计数到达翻转点中断禁能

uint8_t PWMPLUS_IntDown_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                       //获取向下计数到达翻转点中断状态

void PWMPLUS_IntDown_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //清除向下计数到达翻转点中断状态

void PWMPLUS_SoftLoad(PWMPLUS_TypeDef * PWMPLUSx);                                                                //PWMPLUS软件LOAD

uint8_t PWMPLUS_GetCntState(PWMPLUS_TypeDef * PWMPLUSx);                                                          //获取PWMPLUS计数器工作状态

uint8_t PWMPLUS_GetCntDir(PWMPLUS_TypeDef * PWMPLUSx);                                                            //获取PWMPLUS计数器当前计数方向

uint16_t PWMPLUS_GetCurrentCnt(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取PWMPLUS计数器当前计数值

uint8_t PWMPLUS_GetBrake0State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取PWMPLUS刹车0的当前状态

uint8_t PWMPLUS_GetBrake1State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //获取PWMPLUS刹车1的当前状态
	

#endif //__DP32G030_PWMPLUS_H__
