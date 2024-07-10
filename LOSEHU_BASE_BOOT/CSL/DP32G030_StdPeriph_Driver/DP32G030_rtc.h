#ifndef __DP32G030_RTC_H__
#define __DP32G030_RTC_H__

#include "DP32G030.h"


#define RTC_WEEK_SUN  0x00      //星期日
#define RTC_WEEK_MON  0x01      //星期一
#define RTC_WEEK_TUE  0x02      //星期二
#define RTC_WEEK_WED  0x03      //星期三
#define RTC_WEEK_THU  0x04      //星期四
#define RTC_WEEK_FRI  0x05      //星期五
#define RTC_WEEK_SAT  0x06      //星期六


#define RTC_ALM_SUN   0x01      //闹钟星期日
#define RTC_ALM_MON   0x02      //闹钟星期一
#define RTC_ALM_TUE   0x04      //闹钟星期二
#define RTC_ALM_WED   0x08      //闹钟星期三
#define RTC_ALM_THU   0x10      //闹钟星期四
#define RTC_ALM_FRI   0x20      //闹钟星期五
#define RTC_ALM_SAT   0x40      //闹钟星期六


typedef enum
{                 
	RTC_SEL_RCLF =  0x00,            //内部低频32768HZ
	RTC_SEL_XTAL =  0x01             //外部低频晶振32768HZ
} RTC_SelTypeDef;

typedef enum
{                 
	RTC_PREPERIOD_8S  =  0x00,       //8秒校准一次
	RTC_PREPERIOD_16S =  0x01        //16秒校准一次
} RTC_PrePeriodTypeDef;

typedef struct
{                 
	uint16_t Year;    //年   取值范围2000~2099
	uint8_t  Month;   //月   取值范围1~12
	uint8_t  Date;    //日   取值范围1~31
	uint8_t  Hour;    //时   取值范围0~23
	uint8_t  Minute;  //分   取值范围0~59
	uint8_t  Second;  //秒   取值范围0~59
	uint8_t  Week;    //星期 取值范围1~7
} RTC_TimeTypeDef;

typedef struct
{                 
	uint8_t  Week;    //星期 取值范围1~7
	uint8_t  Hour;    //时   取值范围0~23
	uint8_t  Minute;  //分   取值范围0~59
	uint8_t  Second;  //秒   取值范围0~59
} RTC_AlarmTypeDef;

typedef struct
{
	RTC_SelTypeDef  ClkSel;           // 0:RCLF(32768Hz), 1:XTAL(32768Hz)
	RTC_PrePeriodTypeDef pre_period;  // 0:8s, 1:16s
	float    act_freq;                // 输入到RTC模块的实际频率值
	FunctionalState  LoadTime_En;     // 时间使能控制位
	FunctionalState  Alarm_En;        // 闹钟使能控制位
	RTC_TimeTypeDef  Time;            // 配置时间
	RTC_AlarmTypeDef Alarm;           // 配置闹钟    	
	FunctionalState  SecIntEn;        // 秒中断使能
	FunctionalState  MinIntEn;        // 分中断使能
	FunctionalState  HourIntEn;       // 时中断使能
	FunctionalState  DateIntEn;       // 日中断使能
	FunctionalState  AlmIntEn;        // 闹钟中断使能
	FunctionalState  MsIntEn;         // 半秒中断使能
} RTC_InitTypeDef;


//断言  RTC输入时钟选择
#define IS_RTC_CLKSEL(RTC_CLKSEL) (((RTC_CLKSEL) == RTC_SEL_RCLF) || ((RTC_CLKSEL) == RTC_SEL_XTAL))

//断言  RTC输入时钟选择
#define IS_RTC_PREPERIOD(RTC_PREPERIOD) (((RTC_PREPERIOD) == RTC_PREPERIOD_8S) || ((RTC_PREPERIOD) == RTC_PREPERIOD_16S))


void RTC_Init(RTC_TypeDef * RTCx, RTC_InitTypeDef * RTC_InitStruct);      //RTC模块初始化

void RTC_Start(RTC_TypeDef * RTCx);                                       //启动RTC

void RTC_Stop(RTC_TypeDef * RTCx);                                        //停止RTC

void RTC_AlarmEnable(RTC_TypeDef * RTCx);                                 //RTC闹钟功能使能

void RTC_AlarmDisable(RTC_TypeDef * RTCx);                                //RTC闹钟功能关闭

void RTC_LoadTimeEnable(RTC_TypeDef * RTCx);                              //装载RTC时间设定值

void RTC_IntSecEn(RTC_TypeDef * RTCx);                                    //RTC秒中断使能

void RTC_IntSecDis(RTC_TypeDef * RTCx);                                   //RTC秒中断禁止

void RTC_IntSecClr(RTC_TypeDef * RTCx);                                   //RTC秒中断标志清除

uint8_t RTC_IntSecState(RTC_TypeDef * RTCx);                              //RTC秒中断状态读取

void RTC_IntMinEn(RTC_TypeDef * RTCx);                                    //RTC分中断使能

void RTC_IntMinDis(RTC_TypeDef * RTCx);                                   //RTC分中断禁止

void RTC_IntMinClr(RTC_TypeDef * RTCx);                                   //RTC分中断标志清除

uint8_t RTC_IntMinState(RTC_TypeDef * RTCx);                              //RTC分中断状态读取

void RTC_IntHourEn(RTC_TypeDef * RTCx);                                   //RTC小时中断使能

void RTC_IntHourDis(RTC_TypeDef * RTCx);                                  //RTC小时中断禁止

void RTC_IntHourClr(RTC_TypeDef * RTCx);                                  //RTC小时中断标志清除

uint8_t RTC_IntHourState(RTC_TypeDef * RTCx);                             //RTC小时中断状态读取

void RTC_IntDateEn(RTC_TypeDef * RTCx);                                   //RTC日期中断使能

void RTC_IntDateDis(RTC_TypeDef * RTCx);                                  //RTC日期中断禁止

void RTC_IntDateClr(RTC_TypeDef * RTCx);                                  //RTC日期中断清除

uint8_t RTC_IntDateState(RTC_TypeDef * RTCx);                             //RTC日期中断状态读取

void RTC_IntAlarmEn(RTC_TypeDef * RTCx);                                  //RTC闹钟中断使能

void RTC_IntAlarmDis(RTC_TypeDef * RTCx);                                 //RTC闹钟中断禁止

void RTC_IntAlarmClr(RTC_TypeDef * RTCx);                                 //RTC闹钟中断清除

uint8_t RTC_IntAlarmState(RTC_TypeDef * RTCx);                            //RTC闹钟中断状态读取

void RTC_IntMsEn(RTC_TypeDef * RTCx);                                     //RTC毫秒中断使能

void RTC_IntMsDis(RTC_TypeDef * RTCx);                                    //RTC毫秒中断禁止

void RTC_IntMsClr(RTC_TypeDef * RTCx);                                    //RTC毫秒中断清除

uint8_t RTC_IntMsState(RTC_TypeDef * RTCx);                               //RTC毫秒中断状态读取

uint8_t RTC_TimeErrorState(RTC_TypeDef * RTCx);                           //RTC时间格式错误标志读取

uint8_t RTC_AlarmErrorState(RTC_TypeDef * RTCx);                          //RTC闹钟格式错误标志读取

uint8_t RTC_IsLeapYear(RTC_TypeDef * RTCx);                               //RTC闰年判断

void RTC_SetTime(RTC_TypeDef * RTCx, RTC_TimeTypeDef * RTC_TimeStruct);   //RTC时间设置

void RTC_GetTime(RTC_TypeDef * RTCx, RTC_TimeTypeDef * RTC_TimeStruct);   //获取RTC当前时间

void RTC_SetAlarm(RTC_TypeDef * RTCx, RTC_AlarmTypeDef * RTC_AlarmStruct);//RTC闹钟设置


#endif //__DP32G030_RTC_H__


