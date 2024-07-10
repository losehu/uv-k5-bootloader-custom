#include "DP32G030_power.h"


/****************************************************************************************************************************************** 
* ��������: Enter_LowPower_Mode()
* ����˵��:	���ý���͹���ģʽ     
* ��    ��: uint8_t Mode	1 STANDBY   2 SLEEP   3 DEEPSLEEP  4  STOP  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void Enter_LowPower_Mode(uint8_t Mode)
{
	assert_param(IS_LOWPOWER_MODE(Mode));                              //�������Ĳ���Mode�Ƿ�Ϸ� 
	
	switch(Mode)
	{
		case MODE_STANDBY:
			
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STANDBY_POS;            //����ϵͳ����STANDBYģʽ
		
			while(PMU->LPMD_WKST == 0);
		
		break;
		
		case MODE_SLEEP:
			
			FLASH_Set_DeepSleep_Mode();
		
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_SLEEP_POS;              //����ϵͳ����SLEEPģʽ
		
			while(PMU->LPMD_WKST == 0);
		
			FLASH_Set_Normal_Mode();
		
		break;
		
		case MODE_DEEPSLEEP:
			
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_DEEPSLEEP_POS;          //����ϵͳ����DEEPSLEEPģʽ 
		
			while(PMU->LPMD_WKST == 0);
		
		break;
		
		case MODE_STOP:
		
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STOP_POS;               //����ϵͳ����STOPģʽ 
		
		break;
	
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_Style_Enable()
* ����˵��:	����ģʽʹ��  
* ��    ��: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_Style_Enable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                         //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_ALM_POS;            //����RTC���ӻ���ʹ��
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_TIM_POS;            //����RTCʱ�份��ʹ��		
		
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_IO_POS;             //����IO����ʹ��
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_Style_Disable()
* ����˵��:	����ģʽ���� 
* ��    ��: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_Style_Disable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_ALM_POS);            //����RTC���ӻ��ѽ���
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_TIM_POS);            //����RTCʱ�份�ѽ���	
		
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_IO_POS);             //����IO���ѽ���
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_State_Check()
* ����˵��:	����״̬��ѯ
* ��    ��: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* ��    ��: 1  ���������ѱ�־   0δ�������ѱ�־
* ע������: ��
******************************************************************************************************************************************/
uint8_t WakeUp_State_Check(uint8_t WakeUp_Style)
{
	uint8_t state = 0;
	
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_ALM_MSK)                     //�ж��Ƿ����RTC���ӻ��ѱ�־
			{
				state = 1;
			}			
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_TIM_MSK)                     //�ж��Ƿ����RTCʱ�份�ѱ�־
			{
				state = 1;
			}
			
		break;
		
		case WAKEUP_IO:
			
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_IO_MSK)                      //�ж��Ƿ����IO���ѱ�־
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
* ��������: WakeUp_State_Clear()
* ����˵��:	����״̬���
* ��    ��: uint8_t WakeUp_Style	1 WAKEUP_RTC_ALARM   2 WAKEUP_RTC_TIME   3 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_State_Clear(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                                 //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_RTC_ALARM:
			
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_ALM_POS;                     //���RTC���ӻ��ѱ�־		
		
		break;
		
		case WAKEUP_RTC_TIME:
		
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_TIM_POS;                    //���RTCʱ�份�ѱ�־
			
		break;
		
		case WAKEUP_IO:
			
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_IO_POS;                     //���IO���ѱ�־
		
		break;
		
		default:	
		
		break;
	}
}