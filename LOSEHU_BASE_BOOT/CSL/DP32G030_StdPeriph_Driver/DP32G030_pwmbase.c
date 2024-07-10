#include "DP32G030_pwmbase.h"

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_Common_Init()
* 功能说明:	PWMBASE公共参数初始化
* 输    入: PWMBASE_TypeDef * PWMBASEx                              指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*			PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct	包含PWMBASE相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_Common_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_CLKDIV(PWMBASE_CommonInitStruct->ClkDiv));     //检查输入的参数ClkDiv是否合法     
	
	assert_param(IS_PWMBASE_PERIOD(PWMBASE_CommonInitStruct->Period));     //检查输入的参数Period是否合法     
	
	assert_param(IS_PWMBASE_IE_OVF(PWMBASE_CommonInitStruct->OvfIE));      //检查输入的参数OvfIE是否合法     
	
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMBASE0_POS;           //开启PWMBASE0时钟
		
		break;
		
		case((uint32_t)PWMBASE1):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMBASE1_POS;           //开启PWMBASE1时钟
		
		break;
	}
	
	PWMBASE_Stop(PWMBASEx);                                         //关闭PWMBASE，停止PWM输出  

	PWMBASEx->DIV = PWMBASE_CommonInitStruct->ClkDiv;               //PWMBASE分频系数   实际分频为配置值加1
	
	if(PWMBASE_CommonInitStruct->Period == 0)
	{
		PWMBASE_CommonInitStruct->Period = 0xFFFF;
	}
	
	PWMBASEx->PERIOD = PWMBASE_CommonInitStruct->Period;            //PWMBASE周期
	
	if(PWMBASE_CommonInitStruct->OvfIE == ENABLE)                   //PWMBASE周期溢出中断使能
	{
		PWMBASEx->IE |= 0x01 << PWMBASE_IE_OVF_POS;
	}
	else
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_OVF_POS);
	}
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			if(PWMBASE_CommonInitStruct->OvfIE)
			{
				NVIC_EnableIRQ(PWMBASE0_IRQn);
			}
		
		break;
			
		case((uint32_t)PWMBASE1):
		
			if(PWMBASE_CommonInitStruct->OvfIE)
			{
				NVIC_EnableIRQ(PWMBASE1_IRQn);
			}
		
		break;
	}
	
	PWMBASEx->IF = 0x0F;       //清中断标志
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_Channel_Init()
* 功能说明:	PWMBASE通道初始化
* 输    入: PWMBASE_TypeDef * PWMBASEx                  指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*			PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct	包含PWMBASE相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_Channel_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                  //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_COMP(PWMBASE_ChannelInitStruct->Comp));          //检查输入的参数Comp是否合法    
	
	assert_param(IS_PWMBASE_INV(PWMBASE_ChannelInitStruct->Inv));            //检查输入的参数Inv是否合法  
	
	assert_param(IS_PWMBASE_OUTEN(PWMBASE_ChannelInitStruct->OutEn));        //检查输入的参数OutEn是否合法  
	
	assert_param(IS_PWMBASE_IE_COMP(PWMBASE_ChannelInitStruct->CompIE));     //检查输入的参数CompIE是否合法  
	
	
	PWMBASE_Stop(PWMBASEx);                                                 //关闭PWMBASE，停止PWM输出  

	if(PWMBASE_ChannelInitStruct->Comp > PWMBASE_GetPeriod(PWMBASEx))
	{
		PWMBASE_ChannelInitStruct->Comp = 0;
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH0) == PWMBASE_CH0)
	{
		PWMBASEx->CH0_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE配置通道0翻转点
		
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASE通道0信号输出翻转
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_INV_POS);
		}

		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASE通道0信号输出使能
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_EN_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASE通道0到达翻转点中断使能
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH0_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH0_COMP_POS);
		}
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH1) == PWMBASE_CH1)
	{
		PWMBASEx->CH1_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE配置通道1翻转点
	
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASE通道1信号输出翻转
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_INV_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASE通道1信号输出使能
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_EN_POS);
		}
		
		PWMBASEx->CH1_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE配置通道1翻转点
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASE通道1到达翻转点中断使能
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH1_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH1_COMP_POS);
		}	
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH2) == PWMBASE_CH2)
	{
		PWMBASEx->CH2_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE配置通道2翻转点
	
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASE通道2信号输出翻转
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_INV_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASE通道2信号输出使能
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_EN_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASE通道2到达翻转点中断使能
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH2_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH2_COMP_POS);
		}
	}
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			if(PWMBASE_ChannelInitStruct->CompIE)
			{
				NVIC_EnableIRQ(PWMBASE0_IRQn);
			}
		
		break;
	}
	
	PWMBASEx->IF = 0x0F;       //清中断标志
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_Start()
* 功能说明:	启动PWMBASE，开始PWM输出
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_Start(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //检查输入的参数PWMBASEx是否合法    
	
	PWMBASEx->EN |= 0x01 << PWMBASE_EN_POS; 
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_Stop()
* 功能说明:	关闭PWMBASE，停止PWM输出
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_Stop(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //检查输入的参数PWMBASEx是否合法    
	
	PWMBASEx->EN &= ~(0x01 << PWMBASE_EN_POS);  
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_SetClkDiv()
* 功能说明:	设置预分频系数   实际分频为配置值加1
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
            uint16_t Clk_Div   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_SetClkDiv(PWMBASE_TypeDef * PWMBASEx,uint16_t Clk_Div)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_CLKDIV(Clk_Div));     //检查输入的参数ClkDiv是否合法   
	
	PWMBASEx->DIV = Clk_Div;                      //PWMBASE分频系数  实际分频为配置值加1
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_SetOutInv()
* 功能说明:	PWMBASE输出信号翻转配置
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
*           FunctionalState  OutEn         有效值包括ENABLE  DISABLE
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_SetOutInv(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutInv)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	assert_param(IS_PWMBASE_INV(OutInv));         //检查输入的参数OutInv是否合法 
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_INV_POS);
		}	
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_INV_POS);
		}
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_INV_POS);
		}
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_SetOutEn()
* 功能说明:	PWMBASE输出使能配置
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_SetOutEn(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutEn)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	assert_param(IS_PWMBASE_OUTEN(OutEn));        //检查输入的参数OutEn是否合法 
	
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_EN_POS);
		}	
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_EN_POS);
		}
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_EN_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_SetPeriod()
* 功能说明:	设置周期
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*			uint32_t Period			            要设定的周期值,16位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_SetPeriod(PWMBASE_TypeDef * PWMBASEx, uint16_t Period)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法    
	
	assert_param(IS_PWMBASE_PERIOD(Period));      //检查输入的参数Period是否合法    
	
	if(Period == 0)
	{
		Period = 0xFFFF;
	}
	
	PWMBASEx->PERIOD = Period;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_GetPeriod()
* 功能说明:	获取周期
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 周期值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWMBASE_GetPeriod(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法    
	
	return PWMBASEx->PERIOD;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_SetComp()
* 功能说明:	设置翻转点
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                         PWMBASE_CH0    PWMBASE_CH1   PWMBASE_CH2
*			uint32_t Comp			            要设定的翻转点,16位
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_SetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx,uint16_t Comp)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	assert_param(IS_PWMBASE_COMP(Comp));          //检查输入的参数Comp是否合法    
	
	
	if(Comp > PWMBASE_GetPeriod(PWMBASEx))
	{
		Comp = 0;
	}
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->CH0_COMP  = Comp;
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->CH1_COMP  = Comp;
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->CH2_COMP  = Comp;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_GetComp()
* 功能说明:	获取配置的翻转点
* 输    入: PWMBASE_TypeDef * PWMBASEx			指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                         PWMBASE_CH0    PWMBASE_CH1   PWMBASE_CH2
* 输    出: 返回配置的翻转点
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t PWMBASE_GetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	
	if(CHx  == PWMBASE_CH0) 
	{
		return PWMBASEx->CH0_COMP;
	}
	else if(CHx == PWMBASE_CH1) 
	{
		return PWMBASEx->CH1_COMP;
	}
	else if(CHx == PWMBASE_CH2) 
	{
		return PWMBASEx->CH2_COMP;
	}
	
	return 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntCompEn()
* 功能说明:	PWMBASE翻转点中断使能
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntCompEn(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH2_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntCompDis()
* 功能说明:	PWMBASE翻转点中断禁能
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntCompDis(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH2_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntCompClr()
* 功能说明:	PWMBASE翻转点中断标志清除
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择  可以多通道进行操作 比如  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntCompClr(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH2_COMP_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntCompState()
* 功能说明:	PWMBASE翻转点中断状态
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
*           uint8_t CHx                    通道选择 只能选择一个通道  PWMBASE_CH0   PWMBASE_CH1   PWMBASE_CH2
* 输    出: 1 翻转点中断已经发生    0  翻转点中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMBASE_IntCompState(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	uint8_t State = 0;
	
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //检查输入的参数CHx是否合法    
	
	
	if(CHx  == PWMBASE_CH0) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH0_COMP_MSK)
		{
			State = 1;
		}
	}
	else if(CHx == PWMBASE_CH1) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH1_COMP_MSK)
		{
			State = 1;
		}
	}
	else if(CHx == PWMBASE_CH2) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH2_COMP_MSK)
		{
			State = 1;
		}
	}

	return State;
}



/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntOvfEn()
* 功能说明:	PWMBASE周期溢出中断使能
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntOvfEn(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	PWMBASEx->IE |= (0x01 << PWMBASE_IE_OVF_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntOvfDis()
* 功能说明:	PWMBASE周期溢出中断禁能
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntOvfDis(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_OVF_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntOvfClr()
* 功能说明:	PWMBASE周期溢出中断标志清除
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PWMBASE_IntOvfClr(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	PWMBASEx->IF = (0x01 << PWMBASE_IF_OVF_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	PWMBASE_IntOvfState()
* 功能说明:	PWMBASE周期溢出中断状态
* 输    入: PWMBASE_TypeDef * PWMBASEx     指定要被设置的PWMBASE，有效值包括PWMBASE0、PWMBASE1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t PWMBASE_IntOvfState(PWMBASE_TypeDef * PWMBASEx)
{
	uint8_t State = 0;
	
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //检查输入的参数PWMBASEx是否合法  
	
	if(PWMBASEx->IF & PWMBASE_IF_OVF_MSK)
	{
		State = 1;
	}
	
	return State;
}




