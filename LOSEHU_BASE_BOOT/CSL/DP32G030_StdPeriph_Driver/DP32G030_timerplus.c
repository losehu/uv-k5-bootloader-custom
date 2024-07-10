#include "DP32G030_timerplus.h"


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_Common_Init()
* 功能说明:	TIMPLUS公共参数初始化
* 输    入: TIMPLUS_TypeDef * TIMPLUSx                              指定要被设置的TIMPLUS，有效值包括TIMPLUS0、TIMPLUS1
*			TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct	包含TIMPLUS相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_Common_Init(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                                //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));                                   //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_CLKDIV(TIMPLUS_CommonInitStruct->ClkDiv));     //检查输入的参数ClkDiv是否合法   
	
	assert_param(IS_TIMPLUS_MODE(TIMPLUS_CommonInitStruct->Mode));         //检查输入的参数Mode是否合法  
	
	assert_param(IS_TIMPLUS_CLKSRC(TIMPLUS_CommonInitStruct->ClkSel));     //检查输入的参数ClkSel是否合法  
	
	assert_param(IS_TIMPLUS_EXTSEL(TIMPLUS_CommonInitStruct->ExtSel));     //检查输入的参数ExtSel是否合法  
	
	assert_param(IS_TIMPLUS_EXTLEVEL(TIMPLUS_CommonInitStruct->ExtLevel)); //检查输入的参数ExtLevel是否合法  
	
	assert_param(IS_TIMPLUS_PERIOD(TIMPLUS_CommonInitStruct->Period));     //检查输入的参数Period是否合法  
	
	assert_param(IS_TIMPLUS_OUTEN(TIMPLUS_CommonInitStruct->OutEn));       //检查输入的参数OutEn是否合法  
	
	assert_param(IS_TIMPLUS_OVF_IE(TIMPLUS_CommonInitStruct->Ovf_IE));     //检查输入的参数Ovf_IE是否合法  
	
	assert_param(IS_TIMPLUS_RISE_IE(TIMPLUS_CommonInitStruct->RIse_IE));   //检查输入的参数RIse_IE是否合法  
	
	assert_param(IS_TIMPLUS_FALL_IE(TIMPLUS_CommonInitStruct->Fall_IE));   //检查输入的参数Fall_IE是否合法  
	

	switch((uint32_t)TIMPLUSx)
	{
		case((uint32_t)TIMPLUS0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMPLUS0_POS;           //开启TIMPLUS0时钟
		
		break;
		
		case((uint32_t)TIMPLUS1):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMPLUS1_POS;           //开启TIMPLUS1时钟
		
		break;
	}
	
	TIMPLUS_Stop(TIMPLUSx,type);                                    //关闭定时器输出
	
	TIMPLUSx->DIV = TIMPLUS_CommonInitStruct->ClkDiv;               //TIMPLUS分频系数,实际分频为配置值加1
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_MODE_POS);       //工作模式选择
		temp |=  (TIMPLUS_CommonInitStruct->Mode << TIMPLUS_CTR_LOW_MODE_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_CLKSEL_POS);     //计数时钟源选择
		temp |=  (TIMPLUS_CommonInitStruct->ClkSel << TIMPLUS_CTR_LOW_CLKSEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS);     //计数模式或输入捕获模式输入信号选择
		temp |=  (TIMPLUS_CommonInitStruct->ExtSel << TIMPLUS_CTR_LOW_EXTSEL_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_EXTLEVEL_POS);   //计数模式或输入捕获模式输入信号有效边沿选择
		temp |=  (TIMPLUS_CommonInitStruct->ExtLevel << TIMPLUS_CTR_LOW_EXTLEVEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);      //定时模式下周期脉冲输出
		temp |=  (TIMPLUS_CommonInitStruct->OutEn << TIMPLUS_CTR_LOW_OUTEN_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_LOW_DMAEN_POS);      //DMA读取捕获值使能
		temp |=  (TIMPLUS_CommonInitStruct->DMAEn << TIMPLUS_CTR_LOW_DMAEN_POS);
		
		TIMPLUSx->CTR = temp;
		
		TIMPLUSx->LOW_PERIOD = TIMPLUS_CommonInitStruct->Period;    //定时器周期配置值
		
		temp = TIMPLUSx->IE;
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_OVF_POS);          //定时器溢出中断使能
		temp |= (TIMPLUS_CommonInitStruct->Ovf_IE << TIMPLUS_IE_LOW_OVF_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_RISE_POS);         //定时器输入脉冲上升沿中断使能
		temp |= (TIMPLUS_CommonInitStruct->RIse_IE << TIMPLUS_IE_LOW_RISE_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_FALL_POS);         //定时器输入脉冲下降沿中断使能
		temp |= (TIMPLUS_CommonInitStruct->Fall_IE << TIMPLUS_IE_LOW_FALL_POS);
		
		TIMPLUSx->IE = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(TIMPLUS_CommonInitStruct->Mode >= HALL_MODE)
		{
			TIMPLUS_CommonInitStruct->Mode = TIMER_MODE;
		}
		
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_MODE_POS);       //工作模式选择
		temp |=  (TIMPLUS_CommonInitStruct->Mode << TIMPLUS_CTR_HIGH_MODE_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_CLKSEL_POS);     //计数时钟源选择
		temp |=  (TIMPLUS_CommonInitStruct->ClkSel << TIMPLUS_CTR_HIGH_CLKSEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS);     //计数模式或输入捕获模式输入信号选择
		temp |=  (TIMPLUS_CommonInitStruct->ExtSel << TIMPLUS_CTR_HIGH_EXTSEL_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);   //计数模式或输入捕获模式输入信号有效边沿选择
		temp |=  (TIMPLUS_CommonInitStruct->ExtLevel << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);      //定时模式下周期脉冲输出
		temp |=  (TIMPLUS_CommonInitStruct->OutEn << TIMPLUS_CTR_HIGH_OUTEN_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_HIGH_DMAEN_POS);      //DMA读取捕获值使能
		temp |=  (TIMPLUS_CommonInitStruct->DMAEn << TIMPLUS_CTR_HIGH_DMAEN_POS);
		
		TIMPLUSx->CTR = temp;
		
		TIMPLUSx->HIGH_PERIOD = TIMPLUS_CommonInitStruct->Period;    //定时器周期配置值
		
		temp = TIMPLUSx->IE;
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_OVF_POS);          //定时器溢出中断使能
		temp |= (TIMPLUS_CommonInitStruct->Ovf_IE << TIMPLUS_IE_HIGH_OVF_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_RISE_POS);         //定时器输入脉冲上升沿中断使能
		temp |= (TIMPLUS_CommonInitStruct->RIse_IE << TIMPLUS_IE_HIGH_RISE_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_FALL_POS);         //定时器输入脉冲下降沿中断使能
		temp |= (TIMPLUS_CommonInitStruct->Fall_IE << TIMPLUS_IE_HIGH_FALL_POS);
		
		TIMPLUSx->IE = temp;
	}
	
	if(TIMPLUSx->IE != 0)
	{
		switch((uint32_t)TIMPLUSx)
		{
			case((uint32_t)TIMPLUS0):
			
				NVIC_EnableIRQ(TIMPLUS0_IRQn);
			
			break;
			
			case((uint32_t)TIMPLUS1):
			
				NVIC_EnableIRQ(TIMPLUS1_IRQn);
			
			break;
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_Hall_Init()
* 功能说明:	TIMPLUS通道初始化
* 输    入: TIMPLUS_TypeDef * TIMPLUSx                  指定要被设置的TIMPLUS，有效值包括TIMPLUS0、TIMPLUS1
*			TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct	包含TIMPLUS HALL相关设定值的结构体
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_Hall_Init(TIMPLUS_TypeDef * TIMPLUSx, TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                                          //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL0_RISE_IE(TIMPLUS_HallInitStruct->Hall0_Rise_IE));   //检查输入的参数Hall0_Rise_IE是否合法   
	
	assert_param(IS_TIMPLUS_HALL0_FALL_IE(TIMPLUS_HallInitStruct->Hall0_Fall_IE));   //检查输入的参数Hall0_Fall_IE是否合法   
	
	assert_param(IS_TIMPLUS_HALL1_RISE_IE(TIMPLUS_HallInitStruct->Hall1_Rise_IE));   //检查输入的参数Hall1_Rise_IE是否合法   
	
	assert_param(IS_TIMPLUS_HALL1_FALL_IE(TIMPLUS_HallInitStruct->Hall1_Fall_IE));   //检查输入的参数Hall1_Fall_IE是否合法   
	
	assert_param(IS_TIMPLUS_HALL2_RISE_IE(TIMPLUS_HallInitStruct->Hall2_Rise_IE));   //检查输入的参数Hall2_Rise_IE是否合法   
	
	assert_param(IS_TIMPLUS_HALL2_FALL_IE(TIMPLUS_HallInitStruct->Hall2_Fall_IE));   //检查输入的参数Hall2_Fall_IE是否合法   
	
	
	TIMPLUS_Stop(TIMPLUSx,TIMPLUS_LOW);                            //关闭定时器输出
	
	temp = 0;
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL0_RISE_POS);          //HALL0上升沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall0_Rise_IE << TIMPLUS_IE_HALL0_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL0_FALL_POS);          //HALL0下降沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall0_Fall_IE << TIMPLUS_IE_HALL0_FALL_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL1_RISE_POS);          //HALL1上升沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall1_Rise_IE << TIMPLUS_IE_HALL1_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL1_FALL_POS);          //HALL1下降沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall1_Fall_IE << TIMPLUS_IE_HALL1_FALL_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL2_RISE_POS);          //HALL2上升沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall2_Rise_IE << TIMPLUS_IE_HALL2_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL2_FALL_POS);          //HALL2下降沿中断使能
	temp |= (TIMPLUS_HallInitStruct->Hall2_Fall_IE << TIMPLUS_IE_HALL2_FALL_POS);
	
	TIMPLUSx->IE = temp;
	
	if(TIMPLUSx->IE != 0)
	{
		switch((uint32_t)TIMPLUSx)
		{
			case((uint32_t)TIMPLUS0):
			
				NVIC_EnableIRQ(TIMPLUS0_IRQn);
			
			break;
			
			case((uint32_t)TIMPLUS1):
			
				NVIC_EnableIRQ(TIMPLUS1_IRQn);
			
			break;
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_Start()
* 功能说明:	启动定时器，从初始值开始计时/计数
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
*           uint8_t type	定时器选择   1：低16位定时器  2：高16位定时器 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_Start(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                         //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));                            //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->EN |= (0x01 << TIMPLUS_EN_LOW_POS);
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->EN |= (0x01 << TIMPLUS_EN_HIGH_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_Stop()
* 功能说明:	停止定时器
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
*           uint8_t type	定时器选择   1：低16位定时器  2：高16位定时器 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_Stop(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                         //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));                            //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->EN &= ~(0x01 << TIMPLUS_EN_LOW_POS);
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->EN &= ~(0x01 << TIMPLUS_EN_HIGH_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetClkDiv()
* 功能说明:	设置预分频系数   实际分频为配置值加1
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            uint16_t Clk_Div   预分频系数   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetClkDiv(TIMPLUS_TypeDef * TIMPLUSx,uint16_t Clk_Div)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_CLKDIV(Clk_Div));     //检查输入的参数ClkDiv是否合法  
	
	
	TIMPLUSx->DIV = Clk_Div;                      //TIMPLUS分频系数  实际分频为配置值加1
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetMode()
* 功能说明:	设置工作模式
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type     定时器选择   1：低16位定时器  2：高16位定时器 
*	        TIMPLUS_ModeTypeDef Mode	 工作模式选择	
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetMode(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ModeTypeDef Mode)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_MODE(Mode));          //检查输入的参数Mode是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_MODE_POS);       //工作模式选择
		temp |=  (Mode << TIMPLUS_CTR_LOW_MODE_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_MODE_POS);      //工作模式选择
		temp |=  (Mode << TIMPLUS_CTR_HIGH_MODE_POS);
		
		TIMPLUSx->CTR = temp;
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetDMAEn()
* 功能说明:	设置DMA读取捕获值使能或者禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        FunctionalState DMAEn	         DMA读取捕获值使能或者禁能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetDMAEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState DMAEn)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_DMAEN(DMAEn));        //检查输入的参数DMAEn是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		if(DMAEn == DISABLE)
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_LOW_DMAEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_LOW_DMAEN_POS);
		}
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(DMAEn == DISABLE)
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_HIGH_DMAEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_HIGH_DMAEN_POS);
		}
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetClkSel()
* 功能说明:	设置计数时钟源
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        TIMPLUS_ClkSelTypeDef ClkSel	 计数时钟源选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetClkSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ClkSelTypeDef ClkSel)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_CLKSRC(ClkSel));      //检查输入的参数ClkSel是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_CLKSEL_POS);       //计数时钟源选择
		temp |=  (ClkSel << TIMPLUS_CTR_LOW_CLKSEL_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_CLKSEL_POS);       //计数时钟源选择
		temp |=  (ClkSel << TIMPLUS_CTR_HIGH_CLKSEL_POS);
		
		TIMPLUSx->CTR = temp;
	}	
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetExtSel()
* 功能说明:	设置计数模式或输入捕获模式输入信号
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        TIMPLUS_ExtSelTypeDef ExtSel	 计数模式或输入捕获模式输入信号选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetExtSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtSelTypeDef ExtSel)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_EXTSEL(ExtSel));      //检查输入的参数ExtSel是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		if(ExtSel == TIMPLUS_IN0)                 //计数模式或输入捕获模式输入信号选择
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS); 
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS);
		}
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(ExtSel == TIMPLUS_IN0)                 //计数模式或输入捕获模式输入信号选择
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS); 
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS);
		}
	}	
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetExtLevel()
* 功能说明:	设置计数模式或输入捕获模式输入信号有效边沿
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type             定时器选择   1：低16位定时器  2：高16位定时器 
*	        TIMPLUS_ExtLevelTypeDef ExtLevel	 计数模式或输入捕获模式输入信号有效边沿选择
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetExtLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtLevelTypeDef ExtLevel)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_EXTLEVEL(ExtLevel));      //检查输入的参数ExtLevel是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_EXTLEVEL_POS);       //计数模式或输入捕获模式输入信号有效边沿选择
		temp |=  (ExtLevel << TIMPLUS_CTR_LOW_EXTLEVEL_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);       //计数模式或输入捕获模式输入信号有效边沿选择
		temp |=  (ExtLevel << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);
		
		TIMPLUSx->CTR = temp;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetOutEn()
* 功能说明:	设置定时模式下周期脉冲输出
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        TIMPLUS_OutEnTypeDef OutEn	     定时模式下周期脉冲输出
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetOutEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState OutEn)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_OUTEN(OutEn));            //检查输入的参数OutEn是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		if(OutEn == DISABLE)                          //定时模式下周期脉冲输出
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);
		}
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(OutEn == DISABLE)                          //定时模式下周期脉冲输出
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);
		}
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetPeriod()
* 功能说明:	设置定时器周期配置值
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        uint16_t Period          	     定时器周期配置值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_SetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,uint16_t Period)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	assert_param(IS_TIMPLUS_PERIOD(Period));          //检查输入的参数Period是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->LOW_PERIOD = Period;     //定时器周期配置值
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->HIGH_PERIOD = Period;    //定时器周期配置值
	}	
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetPeriod()
* 功能说明:	获取定时器周期配置值
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 定时器周期配置值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_PERIOD;     //返回定时器周期配置值
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_PERIOD;    //返回定时器周期配置值
	}

	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_GetCurrentCnt()
* 功能说明:	获取定时器当前计数值
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 定时器当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetCurrentValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_CNT;     //返回定时器当前计数值
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_CNT;    //返回定时器当前计数值
	}
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_GetCaptureCnt()
* 功能说明:	获取定时器捕获值
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 定时器捕获值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetCaptureValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_CVAL;     //返回定时器捕获值
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_CVAL;    //返回定时器捕获值
	}
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_GetHallLevel()
* 功能说明:	获取HALL初始电平
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_HallTypeDef HallLevel    霍尔选择  HALL0  HALL1  HALL2     	     
* 输    出: HALL初始电平
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_GetHallLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallLevel)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));    //检查输入的参数HallType是否合法  
	
	
	if(HallLevel == HALL_0)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL0_MSK);
	}
	else if(HallLevel == HALL_1)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL1_MSK);
	}
	else if(HallLevel == HALL_2)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL2_MSK);
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntOvfEn()
* 功能说明:	设置定时器溢出中断使能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntOvfEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_OVF_POS);         //定时器溢出中断使能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_OVF_POS);        //定时器溢出中断使能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntOvfDis()
* 功能说明:	设置定时器溢出中断禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntOvfDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_OVF_POS);         //定时器溢出中断禁能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_OVF_POS);        //定时器溢出中断禁能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntOvfClr()
* 功能说明:	清除定时器溢出中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntOvfClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_OVF_POS);         //清除定时器溢出中断状态
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_OVF_POS);        //清除定时器溢出中断状态
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntOvfState()
* 功能说明:	获取定时器溢出中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 1 溢出中断已经发生    0  溢出中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntOvfState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_OVF_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_OVF_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntRiseEn()
* 功能说明:	设置定时器输入脉冲上升沿中断使能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_RISE_POS);         //定时器输入脉冲上升沿中断使能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_RISE_POS);        //定时器输入脉冲上升沿中断使能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntRiseDis()
* 功能说明:	设置定时器输入脉冲上升沿中断禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_RISE_POS);         //定时器输入脉冲上升沿中断禁能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_RISE_POS);        //定时器输入脉冲上升沿中断禁能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntRiseClr()
* 功能说明:	清除定时器输入脉冲上升沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_RISE_POS);         //清除定时器输入脉冲上升沿中断状态
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_RISE_POS);        //清除定时器输入脉冲上升沿中断状态
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntRiseState()
* 功能说明:	获取定时器输入脉冲上升沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 1 上升沿中断已经发生    0 上升沿中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_RISE_MSK)
		{
			return 1;
		}
	}
	
	if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_RISE_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntFallEn()
* 功能说明:	设置定时器输入脉冲下降沿中断使能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_FALL_POS);         //定时器输入脉冲下降沿中断使能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_FALL_POS);        //定时器输入脉冲下降沿中断使能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntFallDis()
* 功能说明:	设置定时器输入脉冲下降沿中断禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_FALL_POS);         //定时器输入脉冲下降沿中断禁能
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_FALL_POS);        //定时器输入脉冲下降沿中断禁能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntFallClr()
* 功能说明:	清除定时器输入脉冲下降沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_FALL_POS);         //清除定时器输入脉冲下降沿中断状态
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_FALL_POS);        //清除定时器输入脉冲下降沿中断状态
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntFallState()
* 功能说明:	获取定时器输入脉冲下降沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0、TIMPLUS1
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 1 下降沿中断已经发生    0 下降沿中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //检查输入的参数type是否合法  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_FALL_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_FALL_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallRiseEn()
* 功能说明:	设置定时器HALL上升沿中断使能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL0_RISE_POS);      //定时器HALL0上升沿中断使能
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL1_RISE_POS);     //定时器HALL1上升沿中断使能
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL2_RISE_POS);     //定时器HALL2上升沿中断使能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallRiseDis()
* 功能说明:	设置定时器HALL上升沿中断禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2     	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL0_RISE_POS);    //定时器HALL0上升沿中断禁能
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL1_RISE_POS);    //定时器HALL1上升沿中断禁能
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL2_RISE_POS);    //定时器HALL2上升沿中断禁能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallRiseClr()
* 功能说明:	清除定时器HALL上升沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2        	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL0_RISE_POS);    //清除定时器HALL0上升沿中断状态
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL1_RISE_POS);    //清除定时器HALL1上升沿中断状态
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL2_RISE_POS);    //清除定时器HALL2上升沿中断状态
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallRiseState()
* 功能说明:	获取定时器HALL上升沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0  	     
* 输    出: 1 上升沿中断已经发生    0 上升沿中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntHallRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if(HallType == HALL_0)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL0_RISE_MSK)
		{
			return 1;
		}
	}
	
	if(HallType == HALL_1)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL1_RISE_MSK)
		{
			return 1;
		}
	}
	
	if(HallType == HALL_2)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL2_RISE_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallFallEn()
* 功能说明:	设置定时器HALL下降沿中断使能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2         	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL0_FALL_POS);      //定时器HALL0下降沿中断使能
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL1_FALL_POS);     //定时器HALL1下降沿中断使能
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL2_FALL_POS);     //定时器HALL2下降沿中断使能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallFallDis()
* 功能说明:	设置定时器HALL下降沿中断禁能
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2       	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL0_FALL_POS);    //定时器HALL0下降沿中断禁能
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL1_FALL_POS);    //定时器HALL1下降沿中断禁能
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL2_FALL_POS);    //定时器HALL2下降沿中断禁能
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallFallClr()
* 功能说明:	清除定时器HALL下降沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0
            TIMPLUS_HallTypeDef HallType    霍尔选择  HALL0  HALL1  HALL2         	     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL0_FALL_POS);    //清除定时器HALL0下降沿中断状态
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL1_FALL_POS);    //清除定时器HALL1下降沿中断状态
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL2_FALL_POS);    //清除定时器HALL2下降沿中断状态
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_IntHallFallState()
* 功能说明:	获取定时器HALL下降沿中断状态
* 输    入: TIMPLUS_TypeDef * TIMPLUSx       有效值有TIMPLUS0     	     
* 输    出: 1 下降沿中断已经发生    0 下降沿中断未发生
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntHallFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //检查输入的参数TIMPLUSx是否合法   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //检查输入的参数HallType是否合法  
	
	
	if(HallType == HALL_0)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL0_FALL_MSK)
		{
			return 1;
		}
	}
	
	if(HallType == HALL_1)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL1_FALL_MSK)
		{
			return 1;
		}
	}
	
	if(HallType == HALL_2)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL2_FALL_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}

