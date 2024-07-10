#include "DP32G030_timerbase.h"

/****************************************************************************************************************************************** 
* 函数名称: TIMBASE_Init()
* 功能说明:	基本定时器初始化
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
*			uint8_t type	定时器选择   1：低16位定时器  2：高16位定时器 
*			TIMBASE_InitTypeDef * TIMBASE_InitStruct   
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_Init(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type,TIMBASE_InitTypeDef * TIMBASE_InitStruct)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                          //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                             //检查输入的参数type是否合法  
	
	assert_param(IS_TIMBASE_CLKDIV(TIMBASE_InitStruct->ClkDiv));     //检查输入的参数ClkDiv是否合法   
	
	assert_param(IS_TIMBASE_PERIOD(TIMBASE_InitStruct->Period));     //检查输入的参数Period是否合法  
	
	assert_param(IS_TIMBASE_OVF_IE(TIMBASE_InitStruct->Ovf_IE));     //检查输入的参数Ovf_IE是否合法  
	
	
	switch((uint32_t)TIMBASEx)
	{
		case((uint32_t)TIMBASE0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMBASE0_POS;           //开启TIMBASE0时钟
		
		break;
		
		case((uint32_t)TIMBASE1):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMBASE1_POS;           //开启TIMBASE1时钟
		
		break;
		
		case((uint32_t)TIMBASE2):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMBASE2_POS;           //开启TIMBASE2时钟
		
		break;
	}
	
	TIMBASE_Stop(TIMBASEx,type);                                    //关闭定时器输出
	
	TIMBASEx->DIV = TIMBASE_InitStruct->ClkDiv;                     //TIMBASE分频系数,实际分频为配置值加1
	
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->LOW_PERIOD = TIMBASE_InitStruct->Period;
		
		TIMBASEx->IE &= ~(0x01 << TIMBASE_IE_LOW_POS);
		TIMBASEx->IE |= (TIMBASE_InitStruct->Ovf_IE << TIMBASE_IE_LOW_POS);
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->HIGH_PERIOD = TIMBASE_InitStruct->Period;
		
		TIMBASEx->IE &= ~(0x01 << TIMBASE_IE_HIGH_POS);
		TIMBASEx->IE |= (TIMBASE_InitStruct->Ovf_IE << TIMBASE_IE_HIGH_POS);
	}
	
	if(TIMBASE_InitStruct->Ovf_IE)
	{
		switch((uint32_t)TIMBASEx)
		{
			case((uint32_t)TIMBASE0):
			
				NVIC_EnableIRQ(TIMBASE0_IRQn);
			
			break;
			
			case((uint32_t)TIMBASE1):
			
				NVIC_EnableIRQ(TIMBASE1_IRQn);
			
			break;
			
			case((uint32_t)TIMBASE2):
			
				NVIC_EnableIRQ(TIMBASE2_IRQn);
			
			break;
		}
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_Start()
* 功能说明:	启动定时器，从初始值开始计时/计数
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
*           uint8_t type	定时器选择   1：低16位定时器  2：高16位定时器 

* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_Start(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                          //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                             //检查输入的参数type是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->EN |= (0x01 << TIMBASE_EN_LOW_POS);
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->EN |= (0x01 << TIMBASE_EN_HIGH_POS);
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_Stop()
* 功能说明:	停止定时器
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
*           uint8_t type	定时器选择   1：低16位定时器  2：高16位定时器 

* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_Stop(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                          //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                             //检查输入的参数type是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->EN &= ~(0x01 << TIMBASE_EN_LOW_POS);
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->EN &= ~(0x01 << TIMBASE_EN_HIGH_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_SetClkDiv()
* 功能说明:	设置预分频系数   实际分频为配置值加1
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
*           uint16_t Clk_Div      时钟预分频系数  
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_SetClkDiv(TIMBASE_TypeDef * TIMBASEx,uint16_t Clk_Div)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));       //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_CLKDIV(Clk_Div));     //检查输入的参数ClkDiv是否合法   
	
	TIMBASEx->DIV = Clk_Div;                      //TIMBASE分频系数  实际分频为配置值加1
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMPLUS_SetPeriod()
* 功能说明:	设置定时器周期配置值
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
            TIMPLUS_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器 
*	        uint16_t Period          	     定时器周期配置值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_SetPeriod(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type,uint16_t Period)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));      //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));         //检查输入的参数type是否合法  
	
	assert_param(IS_TIMBASE_PERIOD(Period));     //检查输入的参数Period是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->LOW_PERIOD = Period;           //定时器周期配置值
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->HIGH_PERIOD = Period;          //定时器周期配置值
	}	
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_GetPeriod()
* 功能说明:	获取定时器周期配置值
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器        	     
* 输    出: 定时器周期配置值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMBASE_GetPeriod(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));      //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));         //检查输入的参数type是否合法  
	
	if(type == TIMBASE_LOW)
	{
		return TIMBASEx->LOW_PERIOD;             //返回低16位定时器周期配置值
	}
	else if(type == TIMBASE_HIGH)
	{
		return TIMBASEx->HIGH_PERIOD;            //返回高16位定时器周期配置值
	}

	return 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_GetCurValue()
* 功能说明:	获取当前计数值
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器    
* 输    出: 定时器当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMBASE_GetCurValue(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));      //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));         //检查输入的参数type是否合法  
	
	if(type == TIMBASE_LOW)
	{
		return TIMBASEx->LOW_CNT;                //返回定时器当前计数值
	}
	else if(type == TIMBASE_HIGH)
	{
		return TIMBASEx->HIGH_CNT;              //返回定时器当前计数值
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_INTEn()
* 功能说明:	使能中断
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_INTEn(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                   //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                      //检查输入的参数type是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->IE |= (0x01 << TIMBASE_IE_LOW_POS);         //定时器溢出中断使能
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->IE |= (0x01 << TIMBASE_IE_HIGH_POS);        //定时器溢出中断使能
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_INTDis()
* 功能说明:	禁能中断
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1   TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_INTDis(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                    //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                       //检查输入的参数type是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->IE &= ~(0x01 << TIMBASE_IE_LOW_POS);         //定时器溢出中断禁能
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->IE &= ~(0x01 << TIMBASE_IE_HIGH_POS);        //定时器溢出中断禁能
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	TIMBASE_INTClr()
* 功能说明:	清除中断标志
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1   TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMBASE_INTClr(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));                  //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                     //检查输入的参数type是否合法  
	
	if((type & TIMBASE_LOW) == TIMBASE_LOW)
	{
		TIMBASEx->IF = (0x01 << TIMBASE_IF_LOW_POS);         //清除定时器溢出中断状态
	}
	
	if((type & TIMBASE_HIGH) == TIMBASE_HIGH)
	{
		TIMBASEx->IF = (0x01 << TIMBASE_IF_HIGH_POS);        //清除定时器溢出中断状态
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMBASE_INTStat()
* 功能说明:	获取中断状态
* 输    入: TIMBASE_TypeDef * TIMBASEx       有效值有TIMBASE0  TIMBASE1  TIMBASE2
            TIMBASE_TypeTypeDef type         定时器选择   1：低16位定时器  2：高16位定时器  
* 输    出: uint8_t 			   0 TIMBASEx未产生中断    1 TIMBASEx产生了中断
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t TIMBASE_INTStat(TIMBASE_TypeDef * TIMBASEx,TIMBASE_TypeTypeDef type)
{
	assert_param(IS_TIMBASE_ALL(TIMBASEx));              //检查输入的参数TIMBASEx是否合法   
	
	assert_param(IS_TIMBASE_TYPE(type));                 //检查输入的参数type是否合法  
	
	if(type == TIMBASE_LOW)
	{
		if(TIMBASEx->IF & TIMBASE_IF_LOW_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMBASE_HIGH)
	{
		if(TIMBASEx->IF & TIMBASE_IF_HIGH_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}



