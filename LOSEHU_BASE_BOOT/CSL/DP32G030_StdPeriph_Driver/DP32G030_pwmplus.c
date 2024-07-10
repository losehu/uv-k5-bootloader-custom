#include "DP32G030_pwmplus.h"

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_CommonInit()
* 功能说明:	PWMPLUS公共参数初始化
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*			PWMPLUS_InitTypeDef * PWMPLUS_ChannelInitStruct	包含PWMPLUS相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_CommonInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_CommonInitTypeDef * PWMPLUS_CommonInitStruct)
{
	uint32_t temp = 0,data = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                            //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CLKSRC(PWMPLUS_CommonInitStruct->Clk_Src));                 //检查输入的参数ClkSrc是否合法   
	
	assert_param(IS_PWMPLUS_CLKDIV(PWMPLUS_CommonInitStruct->ClkDiv));                 //检查输入的参数ClkDiv是否合法   
	
	assert_param(IS_PWMPLUS_MODE(PWMPLUS_CommonInitStruct->Mode));                     //检查输入的参数Mode是否合法  
	
	assert_param(IS_PWMPLUS_DIR(PWMPLUS_CommonInitStruct->Dir));                       //检查输入的参数Dir是否合法  
	
	assert_param(IS_PWMPLUS_RELOAD_CNT(PWMPLUS_CommonInitStruct->Reload_Cnt));         //检查输入的参数Reload_Cnt是否合法  
	
	assert_param(IS_PWMPLUS_PERIOD(PWMPLUS_CommonInitStruct->Period));                 //检查输入的参数Period是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_FILTER(PWMPLUS_CommonInitStruct->Brake_Filter));     //检查输入的参数Brake_Filter是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_CommonInitStruct->Brake0_InputLevel)); //检查输入的参数Brake0_InputLevel是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_CommonInitStruct->Brake1_InputLevel)); //检查输入的参数Brake1_InputLevel是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_CommonInitStruct->Brake2_InputLevel)); //检查输入的参数Brake2_InputLevel是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_COMP(PWMPLUS_CommonInitStruct->Trig_Comp));           //检查输入的参数Trig_Comp是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(PWMPLUS_CommonInitStruct->Trig_Sel));             //检查输入的参数Trig_Sel是否合法  
	
	assert_param(IS_PWMPLUS_RELOAD_IE(PWMPLUS_CommonInitStruct->Reload_IE));           //检查输入的参数Reload_IE是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE0_IE(PWMPLUS_CommonInitStruct->Brake0_IE));           //检查输入的参数Brake0_IE是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE1_IE(PWMPLUS_CommonInitStruct->Brake1_IE));           //检查输入的参数Brake1_IE是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE1_IE(PWMPLUS_CommonInitStruct->Brake2_IE));           //检查输入的参数Brake2_IE是否合法  
	
	assert_param(IS_PWMPLUS_UP_OVF_IE(PWMPLUS_CommonInitStruct->Up_OvfIE));            //检查输入的参数Up_OvfIE是否合法  
	
	assert_param(IS_PWMPLUS_UP_TRIGCOMP_IE(PWMPLUS_CommonInitStruct->Up_TrigCompIE));            //检查输入的参数Up_TrigCompIE是否合法 
	
	assert_param(IS_PWMPLUS_DOWN_OVF_IE(PWMPLUS_CommonInitStruct->Down_OvfIE));                  //检查输入的参数Down_OvfIE是否合法 
	
	assert_param(IS_PWMPLUS_DOWN_TRIGCOMP_IE(PWMPLUS_CommonInitStruct->Down_TrigCompIE));        //检查输入的参数Down_TrigCompIE是否合法 
	

	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMPLUS0_POS;           //开启PWMPLUS0时钟
		
		break;
		
		case((uint32_t)PWMPLUS1):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMPLUS1_POS;           //开启PWMPLUS1时钟
		
		break;
	}

	PWMPLUS_Stop(PWMPLUSx);                                         //关闭PWMBASE，停止PWM输出  
	
	temp = PWMPLUSx->CLK;
	
	temp &= ~(0x07 << PWMPLUS_CLK_SRC_POS);                //计数时钟选择
	temp |= ((PWMPLUS_CommonInitStruct->Clk_Src) << PWMPLUS_CLK_SRC_POS);
	
	temp &= ~((0xFFFF << PWMPLUS_CLK_PREDIV_POS));             //时钟分频   实际分频为配置值加1
	temp |= ((PWMPLUS_CommonInitStruct->ClkDiv) << PWMPLUS_CLK_PREDIV_POS);
	
	PWMPLUSx->CLK = temp;
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x03 << PWMPLUS_CTR_OPM_POS);                //工作模式
	temp |= (PWMPLUS_CommonInitStruct->Mode << PWMPLUS_CTR_OPM_POS);	
	
	temp &= ~(0x01 << PWMPLUS_CTR_DIR_POS);                //计数方向
	temp |= (PWMPLUS_CommonInitStruct->Dir << PWMPLUS_CTR_DIR_POS);	
	
	temp &= ~(0xFF << PWMPLUS_CTR_RELOAD_POS);             //自动装载次数   实际装载次数为配置值加1
	temp |= (PWMPLUS_CommonInitStruct->Reload_Cnt << PWMPLUS_CTR_RELOAD_POS);
	
	PWMPLUSx->CTR = temp;
	
	if(PWMPLUS_CommonInitStruct->Period == 0)
	{
		PWMPLUS_CommonInitStruct->Period = 0xFFFF;
	}
	
	PWMPLUSx->PERIOD = PWMPLUS_CommonInitStruct->Period;           //PWMPLUS周期
	
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_FILTER_POS);    //刹车滤波
	temp |= (PWMPLUS_CommonInitStruct->Brake_Filter << PWMPLUS_BRK_CTR_FILTER_POS);
	
	data = PWMPLUS_CommonInitStruct->Brake0_InputLevel + (PWMPLUS_CommonInitStruct->Brake1_InputLevel << 1) + (PWMPLUS_CommonInitStruct->Brake2_InputLevel << 2);
	
	temp &= ~(0x07 << PWMPLUS_BRK_CTR_INLEV_POS);     //刹车输入有效电平配置
	temp |= (data << PWMPLUS_BRK_CTR_INLEV_POS);
	
	PWMPLUSx->BRK_CTR = temp;
	
	if(PWMPLUS_CommonInitStruct->Period < PWMPLUS_CommonInitStruct->Trig_Comp)
	{
		PWMPLUS_CommonInitStruct->Trig_Comp = 0;
	}
	
	PWMPLUSx->TRIG_COMP = PWMPLUS_CommonInitStruct->Trig_Comp;     //配置内部触发点
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL0_POS);    //输出的Trig0信号功能选择
	temp |= (PWMPLUS_CommonInitStruct->Trig0_Sel << PWMPLUS_TRIG_CTR_SEL0_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL1_POS);    //输出的Trig1信号功能选择
	temp |= (PWMPLUS_CommonInitStruct->Trig1_Sel << PWMPLUS_TRIG_CTR_SEL1_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL2_POS);    //输出的Trig2信号功能选择
	temp |= (PWMPLUS_CommonInitStruct->Trig2_Sel << PWMPLUS_TRIG_CTR_SEL2_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL3_POS);    //输出的Trig3信号功能选择
	temp |= (PWMPLUS_CommonInitStruct->Trig3_Sel << PWMPLUS_TRIG_CTR_SEL3_POS);
	
	PWMPLUSx->TRIG_SEL = temp;
	
	temp = PWMPLUSx->IE;
	
	temp &= ~(0x01 << PWMPLUS_IE_RELOAD_POS);              //自动装载中断配置
	temp |= (PWMPLUS_CommonInitStruct->Reload_IE << PWMPLUS_IE_RELOAD_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_BRK0_POS);                //BRAKE0中断配置
	temp |= (PWMPLUS_CommonInitStruct->Brake0_IE << PWMPLUS_IE_BRK0_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_BRK1_POS);                //BRAKE1中断配置
	temp |= (PWMPLUS_CommonInitStruct->Brake1_IE << PWMPLUS_IE_BRK1_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_BRK2_POS);                //BRAKE2中断配置
	temp |= (PWMPLUS_CommonInitStruct->Brake2_IE << PWMPLUS_IE_BRK2_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_UP_OVF_POS);              //向上计数周期溢出中断配置
	temp |= (PWMPLUS_CommonInitStruct->Up_OvfIE << PWMPLUS_IE_UP_OVF_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_UP_TRIG_POS);             //向上计数到达触发点中断配置
	temp |= (PWMPLUS_CommonInitStruct->Up_TrigCompIE << PWMPLUS_IE_UP_TRIG_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_DOWN_OVF_POS);            //向下计数周期溢出中断配置
	temp |= (PWMPLUS_CommonInitStruct->Down_OvfIE << PWMPLUS_IE_DOWN_OVF_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_DOWN_TRIG_POS);           //向下计数到达触发点中断配置
	temp |= (PWMPLUS_CommonInitStruct->Down_TrigCompIE << PWMPLUS_IE_DOWN_TRIG_POS);
	
	PWMPLUSx->IE = temp;
	
	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS0_IRQn);
			}
		
		break;
			
		case((uint32_t)PWMPLUS1):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS1_IRQn);
			}
		
		break;
	}
	
	PWMPLUSx->IF = 0xFFFFF;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_ChannelInit()
* 功能说明:	PWMPLUS通道初始化
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*			PWMPLUS_InitTypeDef * PWMPLUS_ChannelInitStruct	包含PWMPLUS相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_ChannelInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_ChannelInitTypeDef * PWMPLUS_ChannelInitStruct)
{
	uint32_t temp = 0,data = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                       //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(PWMPLUS_ChannelInitStruct->Channel));    //检查输入的参数Channel是否合法  
	
	assert_param(IS_PWMPLUS_COMP(PWMPLUS_ChannelInitStruct->Comp));               //检查输入的参数Comp是否合法  
	
	assert_param(IS_PWMPLUS_DEADZONE(PWMPLUS_ChannelInitStruct->DeadZone));       //检查输入的参数DeadZone是否合法  
	
	assert_param(IS_PWMPLUS_OUTEN(PWMPLUS_ChannelInitStruct->CHxOutEn));          //检查输入的参数CHxOutEn是否合法  
	
	assert_param(IS_PWMPLUS_OUTEN(PWMPLUS_ChannelInitStruct->CHxNOutEn));         //检查输入的参数CHxNOutEn是否合法  
	
	assert_param(IS_PWMPLUS_OUTINV(PWMPLUS_ChannelInitStruct->CHxInv));           //检查输入的参数CHxInv是否合法  
	
	assert_param(IS_PWMPLUS_OUTINV(PWMPLUS_ChannelInitStruct->CHxNInv));          //检查输入的参数CHxNInv是否合法  
	
	assert_param(IS_PWMPLUS_START_LEVEL(PWMPLUS_ChannelInitStruct->StartLevel));  //检查输入的参数StartLevel是否合法  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_ChannelInitStruct->CHxIdleLevel));       //检查输入的参数CHxIdleLevel是否合法  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_ChannelInitStruct->CHxNIdleLevel));      //检查输入的参数CHxNIdleLevel是否合法  
	
	assert_param(IS_PWMPLUS_BRAKEEN(PWMPLUS_ChannelInitStruct->Brake0_Enable));         //检查输入的参数Brake0_Enable是否合法  
	
	assert_param(IS_PWMPLUS_BRAKEEN(PWMPLUS_ChannelInitStruct->Brake1_Enable));         //检查输入的参数Brake1_Enable是否合法  
	
	assert_param(IS_PWMPLUS_BRAKEEN(PWMPLUS_ChannelInitStruct->Brake2_Enable));         //检查输入的参数Brake2_Enable是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel));         //检查输入的参数Brake_CHxOutLevel是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel));        //检查输入的参数Brake_CHxNOutLevel是否合法  
	
	assert_param(IS_PWMPLUS_MASK_EN(PWMPLUS_ChannelInitStruct->Mask_CHx_Enable));                  //检查输入的参数Mask_CHx_Enable是否合法  
	
	assert_param(IS_PWMPLUS_MASK_EN(PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable));                 //检查输入的参数Mask_CHxN_Enable是否合法  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(PWMPLUS_ChannelInitStruct->Mask_CHx_Level));                //检查输入的参数Mask_CHx_Level是否合法  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(PWMPLUS_ChannelInitStruct->Mask_CHxN_Level));               //检查输入的参数Mask_CHxN_Level是否合法  
	
	assert_param(IS_PWMPLUS_UP_COMP_IE(PWMPLUS_ChannelInitStruct->Up_CompIE));                     //检查输入的参数Up_CompIE是否合法  
	
	assert_param(IS_PWMPLUS_DOWN_COMP_IE(PWMPLUS_ChannelInitStruct->Down_CompIE));                 //检查输入的参数Down_CompIE是否合法  
	
	
	PWMPLUS_Stop(PWMPLUSx);                                                                        //关闭PWMBASE，停止PWM输出  
	
	if(PWMPLUS_ChannelInitStruct->Comp > PWMPLUS_GetPeriod(PWMPLUSx))
	{
		PWMPLUS_ChannelInitStruct->Comp = 0;
	}

	if(PWMPLUS_ChannelInitStruct->DeadZone > PWMPLUS_ChannelInitStruct->Comp)
	{
		PWMPLUS_ChannelInitStruct->DeadZone = PWMPLUS_ChannelInitStruct->Comp;
		
		if(PWMPLUS_ChannelInitStruct->DeadZone > 1023)
		{
			PWMPLUS_ChannelInitStruct->DeadZone = 1023;
		}
	}
	
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH0) == PWMPLUS_CH0)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
		
		data = PWMPLUS_ChannelInitStruct->Brake0_Enable + (PWMPLUS_ChannelInitStruct->Brake1_Enable << 1) + (PWMPLUS_ChannelInitStruct->Brake2_Enable << 2);
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH0EN_POS);        //刹车使能
		temp |= (data << PWMPLUS_BRK_CTR_CH0EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS);      //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH0_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS);     //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH0N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH0_POS);      //通道x屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH0_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH0N_POS);     //通道xN屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH0N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0_POS);      //通道x屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH0_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS);     //通道xN屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH0N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		PWMPLUSx->CH0_COMP = PWMPLUS_ChannelInitStruct->Comp;                  //配置翻转点
		
		PWMPLUSx->CH0_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;          //配置死区时间
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);            //向上计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH0_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);          //向下计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH0_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH1) == PWMPLUS_CH1)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
		
		data = PWMPLUS_ChannelInitStruct->Brake0_Enable + (PWMPLUS_ChannelInitStruct->Brake1_Enable << 1) + (PWMPLUS_ChannelInitStruct->Brake2_Enable << 2);
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH1EN_POS);     //刹车使能
		temp |= (data << PWMPLUS_BRK_CTR_CH1EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS);     //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH1_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS);     //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH1N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH1_POS);            //通道x屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH1_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH1N_POS);           //通道xN屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH1N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1_POS);      //通道x屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH1_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS);     //通道xN屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH1N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		PWMPLUSx->CH1_COMP = PWMPLUS_ChannelInitStruct->Comp;              //配置翻转点
		
		PWMPLUSx->CH1_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;      //配置死区时间
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);            //向上计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH1_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);          //向下计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH1_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH2) == PWMPLUS_CH2)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
		
		data = PWMPLUS_ChannelInitStruct->Brake0_Enable + (PWMPLUS_ChannelInitStruct->Brake1_Enable << 1) + (PWMPLUS_ChannelInitStruct->Brake2_Enable << 2);
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH2EN_POS);     //刹车使能
		temp |= (data << PWMPLUS_BRK_CTR_CH2EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS);     //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH2_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS);    //刹车输出电平
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH2N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH2_POS);      //通道x屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH2_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH2N_POS);     //通道xN屏蔽是否使能
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH2N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2_POS);      //通道x屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH2_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS);     //通道xN屏蔽输出电平选择
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH2N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		PWMPLUSx->CH2_COMP = PWMPLUS_ChannelInitStruct->Comp;                  //配置翻转点
		
		PWMPLUSx->CH2_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;          //配置死区时间
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);            //向上计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH2_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);          //向下计数到达翻转点中断配置
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH2_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS0_IRQn);
			}
		
		break;
			
		case((uint32_t)PWMPLUS1):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS1_IRQn);
			}
		
		break;
	}
	
	PWMPLUSx->IF = 0xFFFFF;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_Start()
* 功能说明:	启动PWMPLUS，开始PWM输出
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_Start(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                      //检查输入的参数PWMPLUSx是否合法   
	
	PWMPLUSx->CTR |= 0x01 << PWMPLUS_CTR_EN_POS; 
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_Stop()
* 功能说明:	关闭PWMPLUS，停止PWM输出
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_Stop(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                      //检查输入的参数PWMPLUSx是否合法   
	
	PWMPLUSx->CTR &= ~(0x01 << PWMPLUS_CTR_EN_POS);  
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetClk_Src()
* 功能说明:	PWMPLUS时钟选择   
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           PWMPLUS_Clk_Src_TypeDef Clk_Src  			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetClk_Src(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Clk_Src_TypeDef Clk_Src)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                      //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CLKSRC(Clk_Src));                    //检查输入的参数Clk_Src是否合法   
	
	temp = PWMPLUSx->CLK;
	
	PWMPLUSx->CLK &= ~(0x07 << PWMPLUS_CLK_SRC_POS);             //PWMPLUS时钟选择   
	PWMPLUSx->CLK |= ((Clk_Src) << PWMPLUS_CLK_SRC_POS);
	
	PWMPLUSx->CLK = temp;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetClkDiv()
* 功能说明:	设置预分频系数   实际分频为配置值加1
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint16_t Clk_Div     预分频系数  			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetClkDiv(PWMPLUS_TypeDef * PWMPLUSx,uint16_t ClkDiv)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                      //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CLKDIV(ClkDiv));                                     //检查输入的参数ClkDiv是否合法   
	
	temp = PWMPLUSx->CLK;
	
	temp &= ~((0xFFFF << PWMPLUS_CLK_PREDIV_POS));             
	temp |= ((ClkDiv) << PWMPLUS_CLK_PREDIV_POS);            //时钟分频   实际分频为配置值加1
	
	PWMPLUSx->CLK = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetMode()
* 功能说明:	设置工作模式
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           PWMPLUS_Mode_TypeDef Mode 	  工作模式		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetMode(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Mode_TypeDef Mode)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_MODE(Mode));                 //检查输入的参数Mode是否合法  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x03 << PWMPLUS_CTR_OPM_POS);
	temp |= (Mode << PWMPLUS_CTR_OPM_POS);	
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetDir()
* 功能说明:	设置计数方向
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           PWMPLUS_Dir_TypeDef Dir     计数方向			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetDir(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Dir_TypeDef Dir)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_DIR(Dir));                   //检查输入的参数Dir是否合法  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x01 << PWMPLUS_CTR_DIR_POS);
	temp |= (Dir << PWMPLUS_CTR_DIR_POS);	
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetReload_Cnt()
* 功能说明:	设置自动装载次数   实际装载次数为配置值加1
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t Reload_Cnt  自动装载次数			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetReload_Cnt(PWMPLUS_TypeDef * PWMPLUSx,uint8_t Reload_Cnt)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                         //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_RELOAD_CNT(Reload_Cnt));                //检查输入的参数Reload_Cnt是否合法  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0xFF << PWMPLUS_CTR_RELOAD_POS);
	temp |= (Reload_Cnt << PWMPLUS_CTR_RELOAD_POS);	                //自动装载次数   实际装载次数为配置值加1
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetBrake_Filter()
* 功能说明:	设置刹车滤波
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                  指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           PWMPLUS_BrakeFilter_TypeDef Brake_Filter    刹车滤波			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_Filter(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeFilter_TypeDef Brake_Filter)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_BRAKE_FILTER(Brake_Filter));                 //检查输入的参数Brake_Filter是否合法  
	
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_FILTER_POS);                       //刹车滤波
	temp |= (Brake_Filter << PWMPLUS_BRK_CTR_FILTER_POS);
	
	PWMPLUSx->BRK_CTR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetBrake_InputLevel()
* 功能说明:	设置刹车输入有效电平选择 
* 输    入: PWMPLUS_TypeDef * PWMPLUSx                      指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           PWMPLUS_Level_TypeDef Brake0_InputLevel	 	    刹车0输入有效电平选择 	
*           PWMPLUS_Level_TypeDef Brake1_InputLevel	 	    刹车1输入有效电平选择 
*           PWMPLUS_Level_TypeDef Brake2_InputLevel	 	    刹车2输入有效电平选择 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_InputLevel(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Level_TypeDef Brake0_InputLevel,PWMPLUS_Level_TypeDef Brake1_InputLevel,PWMPLUS_Level_TypeDef Brake2_InputLevel)
{
	uint32_t temp = 0,data = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(Brake_InputLevel));              //检查输入的参数Brake_InputLevel是否合法  
	
	data = Brake0_InputLevel + (Brake1_InputLevel << 1) + (Brake2_InputLevel << 2);
		
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x07 << PWMPLUS_BRK_CTR_INLEV_POS);           //刹车输入有效电平选择 
	temp |= (data << PWMPLUS_BRK_CTR_INLEV_POS);
	
	PWMPLUSx->BRK_CTR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetBrake_Enable()
* 功能说明:	设置刹车使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx          指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_BrakeEnable_TypeDef Brake_Enable   刹车使能		    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Brake0_Enable,FunctionalState Brake1_Enable,FunctionalState Brake2_Enable)
{
	uint32_t temp = 0,data = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_ENABLE(Brake0_Enable));                //检查输入的参数Brake0_Enable是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_ENABLE(Brake1_Enable));                //检查输入的参数Brake1_Enable是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_ENABLE(Brake2_Enable));                //检查输入的参数Brake2_Enable是否合法  
	
	
	data = Brake0_Enable + (Brake1_Enable << 1) + (Brake2_Enable << 2);
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH0EN_POS);          
		temp |= (data << PWMPLUS_BRK_CTR_CH0EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH1EN_POS);          
		temp |= (data << PWMPLUS_BRK_CTR_CH1EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH2EN_POS);          
		temp |= (data << PWMPLUS_BRK_CTR_CH2EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetBrake_OutLevel()
* 功能说明:	设置刹车时通道输出电平
* 输    入: PWMPLUS_TypeDef * PWMPLUSx          指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_Level_TypeDef Brake_OutLevel  	刹车时通道输出电平	    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_OutLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Brake_OutLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(Brake_OutLevel));             //检查输入的参数Brake_OutLevel是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS);
		}        
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS);
		}   
	}	
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS);
		}   
	}	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetMask_Enable()
* 功能说明:	设置屏蔽功能是否使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx          指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH1
*		    FunctionalState Mask_Enable		    屏蔽功能是否使能  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetMask_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Mask_Enable)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_MASK_EN(Mask_Enable));                       //检查输入的参数Mask_Enable是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH0_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH0_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH1_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH1_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH2_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH2_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH0N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH0N_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH1N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH1N_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH2N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH2N_POS);
		} 
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetMask_Level()
* 功能说明:	设置屏蔽输出电平
* 输    入: PWMPLUS_TypeDef * PWMPLUSx          指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_Level_TypeDef Mask_Level	屏蔽输出电平	    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetMask_Level(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Mask_Level)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(Mask_Level));                     //检查输入的参数Mask_Level是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH0_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH1_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH2_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS);
		}   
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetStartLevel()
* 功能说明:	PWMPLUS计数开始输出电平
* 输    入: PWMPLUS_TypeDef * PWMPLUSx          指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH1
*           PWMPLUS_Level_TypeDef StartLevel    计数开始输出电平
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetStartLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef StartLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_START_LEVEL(StartLevel));                    //检查输入的参数StartLevel是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetIdleLevel()
* 功能说明:	PWMPLUS空闲输出电平配置
* 输    入: PWMPLUS_TypeDef * PWMPLUSx         指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                        通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
*           PWMPLUS_Level_TypeDef  IdleLevel   有效值包括LEVEL_LOW  LEVEL_HIGH
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetIdleLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef  IdleLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(IdleLevel));                      //检查输入的参数IdleLevel是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetOutEn()
* 功能说明:	PWMPLUS输出使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx     指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
            FunctionalState  OutEn         输出使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetOutEn(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutEn)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_OUTEN(OutEn));                               //检查输入的参数OutEn是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetOutInv()
* 功能说明:	PWMPLUS输出信号翻转
* 输    入: PWMPLUS_TypeDef * PWMPLUSx     指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
            FunctionalState  OutInv        输出信号翻转
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetOutInv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutInv)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_OUTINV(OutInv));                             //检查输入的参数OutInv是否合法  

	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}	
	}
}



/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetPeriod()
* 功能说明:	设置周期
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*			uint16_t Period			            要设定的周期值,16位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetPeriod(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Period)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                            //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_PERIOD(Period));                           //检查输入的参数CHx是否合法  
	
	if(Period == 0)
	{
		Period = 0xFFFF;
	}
	
	PWMPLUSx->PERIOD = Period;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetPeriod()
* 功能说明:	获取周期
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 周期值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetPeriod(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                            //检查输入的参数PWMPLUSx是否合法   
	
	return PWMPLUSx->PERIOD;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetComp()
* 功能说明:	设置翻转点
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
*			uint32_t Comp			            要设定的翻转点,16位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t Comp)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_COMP(Comp));                                 //检查输入的参数Comp是否合法  

	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->CH0_COMP  = Comp;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->CH1_COMP  = Comp;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->CH2_COMP  = Comp;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetComp()
* 功能说明:	获取配置的翻转点
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 返回配置的翻转点
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if(CHx == PWMPLUS_CH0) 
	{
		return PWMPLUSx->CH0_COMP;
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		return PWMPLUSx->CH1_COMP;
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		return PWMPLUSx->CH2_COMP;
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetDeadZone()
* 功能说明:	设置通道死区长度
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
*			uint16_t DeadZone			        要设定的死区长度,10位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t DeadZone)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	assert_param(IS_PWMPLUS_DEADZONE(DeadZone));                         //检查输入的参数DeadZone是否合法  

	if(DeadZone > PWMPLUS_GetComp(PWMPLUSx,CHx))
	{
		DeadZone = PWMPLUS_GetComp(PWMPLUSx,CHx);
		
		if(DeadZone > 1023)
		{
			DeadZone = 1023;
		}
	}
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->CH0_DEADZONE  = DeadZone;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->CH1_DEADZONE  = DeadZone;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->CH2_DEADZONE  = DeadZone;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetDeadZone()
* 功能说明:	获取通道死区长度
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 返回配置的通道死区长度
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWMPLUS_GetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if(CHx == PWMPLUS_CH0) 
	{
		return PWMPLUSx->CH0_DEADZONE;
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		return PWMPLUSx->CH1_DEADZONE;
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		return PWMPLUSx->CH2_DEADZONE;
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetTrig_Comp()
* 功能说明:	设置内部触发点
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*			uint32_t Trig_Comp			        要设置的内部触发点,16位  必须小于周期值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx, uint32_t Trig_Comp)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_COMP(Trig_Comp));                       //检查输入的参数Trig_Comp是否合法  
	
	if(Trig_Comp > PWMPLUS_GetPeriod(PWMPLUSx))
	{
		Trig_Comp = 0;
	}
	
	PWMPLUSx->TRIG_COMP = Trig_Comp;            //配置内部触发点
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetTrig_Comp()
* 功能说明:	获取内部触发点
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 内部触发点
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	return PWMPLUSx->TRIG_COMP;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetTrig_Sel0()
* 功能说明:	设置触发信号0功能选择
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    要设置的触发信号功能选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel0(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //检查输入的参数Trig_Sel是否合法  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL0_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL0_POS);                     //配置触发信号功能选择
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetTrig_Sel1()
* 功能说明:	设置触发信号1功能选择
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    要设置的触发信号功能选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel1(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //检查输入的参数Trig_Sel是否合法  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL1_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL1_POS);                     //配置触发信号功能选择
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetTrig_Sel2()
* 功能说明:	设置触发信号2功能选择
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    要设置的触发信号功能选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel2(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //检查输入的参数Trig_Sel是否合法  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL2_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL2_POS);                     //配置触发信号功能选择
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SetTrig_Sel3()
* 功能说明:	设置触发信号3功能选择
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    要设置的触发信号功能选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel3(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //检查输入的参数Trig_Sel是否合法  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL3_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL3_POS);                     //配置触发信号功能选择
	
	PWMPLUSx->TRIG_SEL = temp;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntReloadEn()
* 功能说明:	设置自动装载中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntReloadEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_RELOAD_POS);                     //自动装载中断使能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntReloadDis()
* 功能说明:	设置自动装载中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntReloadDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_RELOAD_POS);                    //自动装载中断禁能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntReloadState()
* 功能说明:	获取自动装载中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 自动装载中断已经发生    0  自动装载中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntReloadState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_RELOAD_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntReloadClr()
* 功能说明:	清除自动装载中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntReloadClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_RELOAD_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake0En()
* 功能说明:	设置刹车0中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0En(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_BRK0_POS);                       //刹车0中断使能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake0Dis()
* 功能说明:	设置刹车0中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0Dis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_BRK0_POS);                      //自动装载中断禁能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake0State()
* 功能说明:	获取刹车0中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 刹车0中断已经发生    0  刹车0中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntBrake0State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_BRK0_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake0Clr()
* 功能说明:	清除刹车0中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0Clr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_BRK0_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake1En()
* 功能说明:	设置刹车1中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1En(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_BRK1_POS);                       //刹车1中断使能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake1Dis()
* 功能说明:	设置刹车1中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1Dis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_BRK1_POS);                      //刹车1中断禁能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake1State()
* 功能说明:	获取刹车1中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 刹车1中断已经发生    0  刹车1中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntBrake1State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  

	if(PWMPLUSx->IF & PWMPLUS_IF_BRK1_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake1Clr()
* 功能说明:	清除刹车1中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1Clr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_BRK1_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake2En()
* 功能说明:	设置刹车2中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake2En(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_BRK2_POS);                       //刹车2中断使能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake2Dis()
* 功能说明:	设置刹车2中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake2Dis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_BRK2_POS);                      //刹车2中断禁能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake2State()
* 功能说明:	获取刹车2中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 刹车2中断已经发生    0  刹车2中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntBrake2State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  

	if(PWMPLUSx->IF & PWMPLUS_IF_BRK2_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntBrake2Clr()
* 功能说明:	清除刹车2中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntBrake2Clr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_BRK2_POS);	
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_OvfEn()
* 功能说明:	设置向上计数周期溢出中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_UP_OVF_POS);                     //向上计数周期溢出中断使能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_OvfDis()
* 功能说明:	设置向上计数周期溢出中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_UP_OVF_POS);                    //向上计数周期溢出中断禁能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_OvfState()
* 功能说明:	获取向上计数周期溢出中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 向上计数周期溢出中断已经发生    0  向上计数周期溢出中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_OvfState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_UP_OVF_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_OvfClr()
* 功能说明:	清除向上计数周期溢出中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_UP_OVF_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_TrigCompEn()
* 功能说明:	设置向上计数到达触发点中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_UP_TRIG_POS);                    //向上计数到达触发点中断使能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_TrigCompDis()
* 功能说明:	设置向上计数到达触发点中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_UP_TRIG_POS);                   //向上计数到达触发点中断禁能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_TrigCompState()
* 功能说明:	获取向上计数到达触发点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 向上计数到达触发点中断已经发生    0  向上计数到达触发点中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_UP_TRIG_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_TrigCompClr()
* 功能说明:	清除向上计数到达触发点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_UP_TRIG_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_OvfEn()
* 功能说明:	设置向下计数周期溢出中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_DOWN_OVF_POS);                   //向下计数周期溢出中断使能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_OvfDis()
* 功能说明:	设置向下计数周期溢出中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_DOWN_OVF_POS);                  //向下计数周期溢出中断禁能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_OvfState()
* 功能说明:	获取向下计数周期溢出中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 向下计数周期溢出中断已经发生    0  向下计数周期溢出中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_OvfState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_DOWN_OVF_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_OvfClr()
* 功能说明:	清除向下计数周期溢出中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_DOWN_OVF_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_TrigCompEn()
* 功能说明:	设置向下计数到达触发点中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_DOWN_TRIG_POS);                  //向下计数到达触发点中断使能
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_TrigCompDis()
* 功能说明:	设置向下计数到达触发点中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_DOWN_TRIG_POS);                 //向下计数到达触发点中断禁能
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_TrigCompState()
* 功能说明:	获取向下计数到达触发点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 1 向下计数到达触发点中断已经发生    0  向下计数到达触发点中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_DOWN_TRIG_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_TrigCompClr()
* 功能说明:	清除向下计数到达触发点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_DOWN_TRIG_POS);	
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_CompEn()
* 功能说明:	设置向上计数到达翻转点中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_CompDis()
* 功能说明:	设置向上计数到达翻转点中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_CompState()
* 功能说明:	获取向上计数到达翻转点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 1 向上计数到达翻转点中断已经发生    0  向上计数到达翻转点中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if(CHx == PWMPLUS_CH0) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH0_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH1_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH2_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntUp_CompClr()
* 功能说明:	清除向上计数到达翻转点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH2_UP_COMP_POS);
	}
}



/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_CompEn()
* 功能说明:	设置向下计数到达翻转点中断使能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_CompDis()
* 功能说明:	设置向下计数到达翻转点中断禁能
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_CompState()
* 功能说明:	获取向下计数到达翻转点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 1 向下计数到达翻转点中断已经发生    0  向下计数到达翻转点中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if(CHx == PWMPLUS_CH0) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH0_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH1_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH2_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_IntDown_CompClr()
* 功能说明:	清除向下计数到达翻转点中断状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //检查输入的参数CHx是否合法  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH2_DOWN_COMP_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_SoftLoad()
* 功能说明:	PWMPLUS软件LOAD
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMPLUS_SoftLoad(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	PWMPLUSx->SWLOAD = (0x01 << PWMPLUS_SWLOAD_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetCntState()
* 功能说明:	获取PWMPLUS计数器工作状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 1 计数器正在计数   0 计数器未工作
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetCntState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->CNT_STATE & PWMPLUS_CNT_STATE_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetCntDir()
* 功能说明:	获取PWMPLUS计数器当前计数方向
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 1 计数器当前向下计数   0 计数器当前向上计数
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetCntDir(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->CNT_STATE & PWMPLUS_CNT_STATE_DIR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetCurrentCnt()
* 功能说明:	获取PWMPLUS计数器当前计数值
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 计数器当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t PWMPLUS_GetCurrentCnt(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	return (PWMPLUSx->CNT_STATE & 0xFFFF);
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetBrake0State()
* 功能说明:	获取PWMPLUS刹车0的当前状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 刹车0的当前状态
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetBrake0State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->BRK_STATE & PWMPLUS_BRK0_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMPLUS_GetBrake1State()
* 功能说明:	获取PWMPLUS刹车1的当前状态
* 输    入: PWMPLUS_TypeDef * PWMPLUSx			指定要被设置的PWMPLUS，有效值包括PWMPLUS0、PWMPLUS1
*           
* 输    出: 刹车1的当前状态
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetBrake1State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //检查输入的参数PWMPLUSx是否合法  
	
	if(PWMPLUSx->BRK_STATE & PWMPLUS_BRK1_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



