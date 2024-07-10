#include "DP32G030_power.h"


/****************************************************************************************************************************************** 
* 函数名称: Enter_LowPower_Mode()
* 功能说明:	配置进入低功耗模式     
* 输    入: uint8_t Mode	1 STANDBY   2 SLEEP   3 DEEPSLEEP  4  STOP  		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void Enter_LowPower_Mode(uint8_t Mode)
{
	assert_param(IS_LOWPOWER_MODE(Mode));                              //检查输入的参数Mode是否合法 
	
	switch(Mode)
	{
		case MODE_STANDBY:
			
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STANDBY_POS;            //配置系统进入STANDBY模式
		
			while(PMU->LPMD_WKST == 0);
		
		break;
		
		case MODE_SLEEP:
			
			FLASH_Set_DeepSleep_Mode();
		
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_SLEEP_POS;              //配置系统进入SLEEP模式
		
			while(PMU->LPMD_WKST == 0);
		
			FLASH_Set_Normal_Mode();
		
		break;
		
		case MODE_DEEPSLEEP:
			
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_DEEPSLEEP_POS;          //配置系统进入DEEPSLEEP模式 
		
			while(PMU->LPMD_WKST == 0);
		
		break;
		
		case MODE_STOP:
		
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STOP_POS;               //配置系统进入STOP模式 
		
		break;
	
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: WakeUp_Style_Enable()
* 功能说明:	唤醒模式使能  
* 输    入: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void WakeUp_Style_Enable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                         //检查输入的参数WakeUp_Style是否合法 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_ALM_POS;            //配置RTC闹钟唤醒使能
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_TIM_POS;            //配置RTC时间唤醒使能		
		
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_IO_POS;             //配置IO唤醒使能
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: WakeUp_Style_Disable()
* 功能说明:	唤醒模式禁能 
* 输    入: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void WakeUp_Style_Disable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //检查输入的参数WakeUp_Style是否合法 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_ALM_POS);            //配置RTC闹钟唤醒禁能
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_TIM_POS);            //配置RTC时间唤醒禁能	
		
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_IO_POS);             //配置IO唤醒禁能
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: WakeUp_State_Check()
* 功能说明:	唤醒状态查询
* 输    入: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* 输    出: 1  产生过唤醒标志   0未产生唤醒标志
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t WakeUp_State_Check(uint8_t WakeUp_Style)
{
	uint8_t state = 0;
	
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //检查输入的参数WakeUp_Style是否合法 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_ALM_MSK)                     //判断是否产生RTC闹钟唤醒标志
			{
				state = 1;
			}			
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_TIM_MSK)                     //判断是否产生RTC时间唤醒标志
			{
				state = 1;
			}
			
		break;
		
		case WAKEUP_IO:
			
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_IO_MSK)                      //判断是否产生IO唤醒标志
			{
				state = 1;
			}
		
		break;
		
		default:
			
			state = 0;
		
		break;
	}

	return state;
}

/****************************************************************************************************************************************** 
* 函数名称: WakeUp_State_Clear()
* 功能说明:	唤醒状态清除
* 输    入: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void WakeUp_State_Clear(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                                 //检查输入的参数WakeUp_Style是否合法 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_ALM_POS;                     //清除RTC闹钟唤醒标志		
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_TIM_POS;                    //清除RTC时间唤醒标志
			
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_IO_POS;                     //清除IO唤醒标志
		
		break;
		
		default:	
		
		break;
	}
}
