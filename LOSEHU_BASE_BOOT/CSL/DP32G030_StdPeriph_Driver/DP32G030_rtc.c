#include "DP32G030_rtc.h"

/****************************************************************************************************************************************** 
* 函数名称:	RTC_Init
* 功能说明:	RTC模块初始化
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC，RTC_InitTypeDef * RTC_InitStruct  配置RTC初始化参数 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_Init(RTC_TypeDef * RTCx, RTC_InitTypeDef * RTC_InitStruct)
{
	uint8_t pre_decimal = 0;
	
	assert_param(IS_RTC_CLKSEL(RTC_InitStruct->ClkSel));             //检查输入的参数ClkSel是否合法      
	
	assert_param(IS_RTC_PREPERIOD(RTC_InitStruct->pre_period));      //检查输入的参数pre_period是否合法   
	
	
	SYS->CLKEN |= (0x01<<SYS_CLKEN_RTC_POS);
	
	PMU->SRC_CFG &= ~(0x01<<PMU_SRC_CFG_RTC_CLK_SEL_POS);
	
	PMU->SRC_CFG |= (RTC_InitStruct->ClkSel<<PMU_SRC_CFG_RTC_CLK_SEL_POS);
	
	RTC_Stop(RTCx);
	
	if(RTC_InitStruct->pre_period == RTC_PREPERIOD_16S)
	{
		pre_decimal = (int)((RTC_InitStruct->act_freq-(int)(RTC_InitStruct->act_freq))*16+0.5);
	}
	else if(RTC_InitStruct->pre_period == RTC_PREPERIOD_8S)
	{
		pre_decimal = (int)((RTC_InitStruct->act_freq-(int)(RTC_InitStruct->act_freq))*8+0.5);		
	}	
	
	RTCx->MS = (((int)(RTC_InitStruct->act_freq)-1)<<RTC_MS_PRE_ROUND_POS)|(pre_decimal<<RTC_MS_PRE_DECIMAL_POS)|(RTC_InitStruct->pre_period<<RTC_MS_PRE_PERIOD_POS);	
	
	RTCx->TR = (((RTC_InitStruct->Time.Second)%10)<<RTC_TR_BCD_SEC_POS) |       \
	           (((RTC_InitStruct->Time.Second)/10)<<RTC_TR_BCD_SEC_DEC_POS)|    \
	           (((RTC_InitStruct->Time.Minute)%10)<<RTC_TR_BCD_MIN_POS)|        \
	           (((RTC_InitStruct->Time.Minute)/10)<<RTC_TR_BCD_MIN_DEC_POS)|    \
	           (((RTC_InitStruct->Time.Hour)%10)<<RTC_TR_BCD_HOUR_POS)|         \
	           (((RTC_InitStruct->Time.Hour)/10)<<RTC_TR_BCD_HOUR_DEC_POS)|     \
	           (((RTC_InitStruct->Time.Week)%7)<<RTC_TR_BCD_WEEK_POS);	
	
	RTCx->DR = (((RTC_InitStruct->Time.Date)%10)<<RTC_DR_BCD_DATE_POS)|         \
	           (((RTC_InitStruct->Time.Date)/10)<<RTC_DR_BCD_DATE_DEC_POS)|     \
	           (((RTC_InitStruct->Time.Month)%10)<<RTC_DR_BCD_MONTH_POS)|       \
	           (((RTC_InitStruct->Time.Month)/10)<<RTC_DR_BCD_MONTH_DEC_POS)|   \
	           (((RTC_InitStruct->Time.Year)%10)<<RTC_DR_BCD_YEAR_POS)|         \
	           ((((RTC_InitStruct->Time.Year)%100)/10)<<RTC_DR_BCD_YEAR_DEC_POS);
	
	if(RTC_InitStruct->LoadTime_En == ENABLE)
	{
		while(RTC_TimeErrorState(RTCx));	
		RTC_LoadTimeEnable(RTCx);
	}
	
	RTCx->AR =  (((RTC_InitStruct->Alarm.Second)%10)<<RTC_AR_BCD_SEC_POS)|      \
	           (((RTC_InitStruct->Alarm.Second)/10)<<RTC_AR_BCD_SEC_DEC_POS)|   \
	           (((RTC_InitStruct->Alarm.Minute)%10)<<RTC_AR_BCD_MIN_POS)|       \
	           (((RTC_InitStruct->Alarm.Minute)/10)<<RTC_AR_BCD_MIN_DEC_POS)|   \
	           (((RTC_InitStruct->Alarm.Hour)%10)<<RTC_AR_BCD_HOUR_POS)|        \
			   (((RTC_InitStruct->Alarm.Hour)/10)<<RTC_AR_BCD_HOUR_DEC_POS)|    \
	           ((RTC_InitStruct->Alarm.Week)<<RTC_AR_BCD_WEEK_POS);	
	
	if(RTC_InitStruct->Alarm_En == ENABLE)
	{
		while(RTC_AlarmErrorState(RTCx));
		RTC_AlarmEnable(RTCx);
	}
	
	RTCx->IE = (RTC_InitStruct->SecIntEn<<RTC_IE_SEC_POS)  |    \
	           (RTC_InitStruct->MinIntEn<<RTC_IE_MIN_POS)  |    \
	           (RTC_InitStruct->HourIntEn<<RTC_IE_HOUR_POS)|    \
	           (RTC_InitStruct->DateIntEn<<RTC_IE_DATE_POS)|    \
	           (RTC_InitStruct->AlmIntEn<<RTC_IE_ALM_POS)  |    \
	           (RTC_InitStruct->MsIntEn<<RTC_IE_MS_POS);
			   
	if(RTCx->IE != 0)
	{
		NVIC_EnableIRQ(RTC_IRQn); 
	}
	
	RTCx->IF = 0x3F;
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_Start
* 功能说明:	启动RTC
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_Start(RTC_TypeDef * RTCx)
{
	RTCx->CFG |= (0x01 << RTC_CFG_RTC_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_Stop
* 功能说明:	停止RTC
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_Stop(RTC_TypeDef * RTCx)
{
	RTCx->CFG &= ~(0x01 << RTC_CFG_RTC_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_AlarmEnable
* 功能说明:	RTC闹钟功能使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_AlarmEnable(RTC_TypeDef * RTCx)
{
	RTCx->CFG |= (0x01 << RTC_CFG_ALM_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_AlarmDisable
* 功能说明:	RTC闹钟功能关闭
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_AlarmDisable(RTC_TypeDef * RTCx)
{
	RTCx->CFG &= ~(0x01<<RTC_CFG_ALM_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_LoadTimeEnable
* 功能说明:	装载RTC时间设定值
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_LoadTimeEnable(RTC_TypeDef * RTCx)
{
	RTCx->CFG |= (0x01<<RTC_CFG_LOAD_EN_POS);
	while (RTCx->CFG&RTC_CFG_LOAD_EN_MSK);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntSecEn
* 功能说明:	RTC秒中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntSecEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_SEC_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntSecDis
* 功能说明:	RTC秒中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntSecDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_SEC_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntSecClr
* 功能说明:	RTC秒中断标志清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntSecClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_SEC_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntSecState
* 功能说明:	RTC秒中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  秒中断触发  0  秒中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntSecState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_SEC_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMinEn
* 功能说明:	RTC分中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMinEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_MIN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMinDis
* 功能说明:	RTC分中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMinDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_MIN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMinClr
* 功能说明:	RTC分中断标志清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMinClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_MIN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMinState
* 功能说明:	RTC分中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  分中断触发  0  分中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntMinState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_MIN_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntHourEn
* 功能说明:	RTC小时中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntHourEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_HOUR_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntHourDis
* 功能说明:	RTC小时中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntHourDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_HOUR_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntHourClr
* 功能说明:	RTC小时中断标志清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntHourClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_HOUR_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntHourState
* 功能说明:	RTC小时中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  小时中断触发  0  小时中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntHourState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_HOUR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntDateEn
* 功能说明:	RTC日期中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntDateEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_DATE_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntDateDis
* 功能说明:	RTC日期中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntDateDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_DATE_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntDateClr
* 功能说明:	RTC日期中断清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntDateClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_DATE_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntDateState
* 功能说明:	RTC日期中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  日期中断触发  0  日期中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntDateState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_DATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntAlarmEn
* 功能说明:	RTC闹钟中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntAlarmEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_ALM_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntAlarmDis
* 功能说明:	RTC闹钟中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntAlarmDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_ALM_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntAlarmClr
* 功能说明:	RTC闹钟中断清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntAlarmClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_ALM_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntAlarmState
* 功能说明:	RTC闹钟中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  闹钟中断触发  0  闹钟中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntAlarmState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_ALM_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMsEn
* 功能说明:	RTC毫秒中断使能
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMsEn(RTC_TypeDef * RTCx)
{
	RTCx->IE |= (0x01<<RTC_IE_MS_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMsDis
* 功能说明:	RTC毫秒中断禁止
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMsDis(RTC_TypeDef * RTCx)
{
	RTCx->IE &= ~(0x01<<RTC_IE_MS_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMsClr
* 功能说明:	RTC毫秒中断清除
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_IntMsClr(RTC_TypeDef * RTCx)
{
	RTCx->IF = (0x01<<RTC_IF_MS_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IntMsState
* 功能说明:	RTC毫秒中断状态读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  毫秒中断触发  0  毫秒中断没有触发
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IntMsState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_MS_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_TimeErrorState
* 功能说明:	RTC时间格式错误标志读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  时间格式设定错误  0  时间格式设定正确
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_TimeErrorState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_TIME_ERR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_AlarmErrorState
* 功能说明:	RTC闹钟格式错误标志读取
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  闹钟格式设定错误  0  闹钟格式设定错误
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_AlarmErrorState(RTC_TypeDef * RTCx)
{	
	if(RTCx->IF & RTC_IF_ALM_ERR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_IsLeapYear
* 功能说明:	RTC闰年判断
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出:  1  闰年   0  平年
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t RTC_IsLeapYear(RTC_TypeDef * RTCx)
{	
	if(RTCx->TSDR & RTC_TSDR_LEAPYEAR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_SetTime
* 功能说明:	RTC时间设置
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC，RTC_TimeTypeDef * RTC_TimeStruct  配置时间结构体参数
* 输    出:
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_SetTime(RTC_TypeDef * RTCx, RTC_TimeTypeDef * RTC_TimeStruct)
{		
	RTCx->TR = ((RTC_TimeStruct->Second%10)<<RTC_TR_BCD_SEC_POS)|
	           ((RTC_TimeStruct->Second/10)<<RTC_TR_BCD_SEC_DEC_POS)|
	           ((RTC_TimeStruct->Minute%10)<<RTC_TR_BCD_MIN_POS)|
	           ((RTC_TimeStruct->Minute/10)<<RTC_TR_BCD_MIN_DEC_POS)|
	           ((RTC_TimeStruct->Hour%10)<<RTC_TR_BCD_HOUR_POS)|
	           ((RTC_TimeStruct->Hour/10)<<RTC_TR_BCD_HOUR_DEC_POS)|
	           ((RTC_TimeStruct->Week%7)<<RTC_TR_BCD_WEEK_POS);		
	RTCx->DR = ((RTC_TimeStruct->Date%10)<<RTC_DR_BCD_DATE_POS)|
	           ((RTC_TimeStruct->Date/10)<<RTC_DR_BCD_DATE_DEC_POS)|
	           ((RTC_TimeStruct->Month%10)<<RTC_DR_BCD_MONTH_POS)|
	           ((RTC_TimeStruct->Month/10)<<RTC_DR_BCD_MONTH_DEC_POS)|
	           ((RTC_TimeStruct->Year%10)<<RTC_DR_BCD_YEAR_POS)|
	           (((RTC_TimeStruct->Year%100)/10)<<RTC_DR_BCD_YEAR_DEC_POS);				  
	
	while(RTC_TimeErrorState(RTCx));	 
	RTC_LoadTimeEnable(RTCx);	
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_GetTime
* 功能说明:	RTC当前时间获得
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC
* 输    出: RTC_TimeTypeDef * RTC_TimeStruct  获取时间结构体参数
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_GetTime(RTC_TypeDef * RTCx, RTC_TimeTypeDef * RTC_TimeStruct)
{		
	while(!(RTC->VALID&RTC_CUR_VALID_MSK));
	RTC_TimeStruct->Year = ((RTCx->TSDR>>RTC_TSDR_BCD_YEAR_POS)&0xF)+((RTCx->TSDR>>RTC_TSDR_BCD_YEAR_DEC_POS)&0xF)*10+2000;
	RTC_TimeStruct->Month = ((RTCx->TSDR>>RTC_TSDR_BCD_MOUTH_POS)&0xF)+((RTCx->TSDR>>RTC_TSDR_BCD_MOUTH_DEC_POS)&0x1)*10;
	RTC_TimeStruct->Date = ((RTCx->TSDR>>RTC_TSDR_BCD_DATE_POS)&0xF)+((RTCx->TSDR>>RTC_TSDR_BCD_DATE_DEC_POS)&0x3)*10;
	RTC_TimeStruct->Hour = ((RTCx->TSTR>>RTC_TSTR_BCD_HOUR_POS)&0xF)+((RTCx->TSTR>>RTC_TSTR_BCD_HOUR_DEC_POS)&0x3)*10;
	RTC_TimeStruct->Minute = ((RTCx->TSTR>>RTC_TSTR_BCD_MIN_POS)&0xF)+((RTCx->TSTR>>RTC_TSTR_BCD_MIN_DEC_POS)&0x7)*10;
	RTC_TimeStruct->Second = ((RTCx->TSTR>>RTC_TSTR_BCD_SEC_POS)&0xF)+((RTCx->TSTR>>RTC_TSTR_BCD_SEC_DEC_POS)&0x7)*10;
	RTC_TimeStruct->Week = ((RTCx->TSTR>>RTC_TSTR_BCD_WEEK_POS)&0x7);
	
	if (RTC_TimeStruct->Week==0) RTC_TimeStruct->Week += 7;
}

/****************************************************************************************************************************************** 
* 函数名称:	RTC_SetAlarm
* 功能说明:	RTC闹钟设置
* 输    入: RTC_TypeDef * RTCx	指定要被设置的RTC，可取值包括RTC，RTC_TimeTypeDef * RTC_TimeStruct  配置闹钟结构体参数
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void RTC_SetAlarm(RTC_TypeDef * RTCx, RTC_AlarmTypeDef * RTC_AlarmStruct)
{	
	RTCx->AR = ((RTC_AlarmStruct->Second%10)<<RTC_AR_BCD_SEC_POS)|
	           ((RTC_AlarmStruct->Second/10)<<RTC_AR_BCD_SEC_DEC_POS)|
	           ((RTC_AlarmStruct->Minute%10)<<RTC_AR_BCD_MIN_POS)|
	           ((RTC_AlarmStruct->Minute/10)<<RTC_AR_BCD_MIN_DEC_POS)|
	           ((RTC_AlarmStruct->Hour%10)<<RTC_AR_BCD_HOUR_POS)|
			   ((RTC_AlarmStruct->Hour/10)<<RTC_AR_BCD_HOUR_DEC_POS)|
	           (RTC_AlarmStruct->Week<<RTC_AR_BCD_WEEK_POS);					  
	
	while(RTC_AlarmErrorState(RTCx));		  			  
	RTC_AlarmEnable(RTCx);
}


