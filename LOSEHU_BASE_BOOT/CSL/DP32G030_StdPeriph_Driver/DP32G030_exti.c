#include "DP32G030_exti.h"

/****************************************************************************************************************************************** 
* 函数名称: EXTI_Assert_Param()
* 功能说明:	检查输入的参数是否合法    
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin		    指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Assert_Param(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	assert_param(IS_GPIO_ALL(GPIOx));                                 //检查输入的参数GPIOx是否合法    
	
	if((uint32_t)GPIOx == (uint32_t)GPIOA)
	{
		assert_param(IS_GPIOA_PIN(GPIO_Pin));                         //检查输入的参数Pin是否合法    
	}
	else if((uint32_t)GPIOx == (uint32_t)GPIOB)
	{
		assert_param(IS_GPIOB_PIN(GPIO_Pin));                         //检查输入的参数Pin是否合法  
	}
	else if((uint32_t)GPIOx == (uint32_t)GPIOC)
	{
		assert_param(IS_GPIOC_PIN(GPIO_Pin));                         //检查输入的参数Pin是否合法  
	}
}


/****************************************************************************************************************************************** 
* 函数名称: EXTI_Init()
* 功能说明:	指定引脚外部中断初始化
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 		指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*			uint32_t mode	        有效值有EXTI_FALL_EDGE、EXTI_RISE_EDGE、EXTI_BOTH_EDGE、EXTI_LOW_LEVEL、EXTI_HIGH_LEVEL
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Init(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t mode)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	assert_param(IS_EXTI_MODE(mode));                      //检查输入的参数Pin是否合法  
	
	
	EXTI_Close(GPIOx, GPIO_Pin);			               //配置关键寄存器前先关闭
	
	if(mode & 0x10)
	{
		GPIOx->INTLVLTRG |= (0x01 << GPIO_Pin);			   //电平触发
		
		if(mode & 0x01)
			GPIOx->INTRISEEN |= (0x01 << GPIO_Pin);		   //高电平触发
		else
			GPIOx->INTRISEEN &= ~(0x01 << GPIO_Pin);	   //低电平触发
	}		
	else
	{
		GPIOx->INTLVLTRG &= ~(0x01 << GPIO_Pin);		   //边沿触发
		
		if(mode & 0x02)
		{
			GPIOx->INTBE |= (0x01 << GPIO_Pin);			   //双边沿触发	
		}
		else
		{
			GPIOx->INTBE &= ~(0x01 << GPIO_Pin);		   //单边沿触发
			
			if(mode & 0x01)
				GPIOx->INTRISEEN |= (0x01 << GPIO_Pin);	   //上升沿触发
			else
				GPIOx->INTRISEEN &= ~(0x01 << GPIO_Pin);   //下降沿触发
		}
	}
	
	GPIOx->INTCLR = (1 << GPIO_Pin);		//清除掉因为模式配置可能产生的中断
}

/****************************************************************************************************************************************** 
* 函数名称:	EXTI_Open()
* 功能说明:	指定引脚外部中断打开（即使能）
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 		指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Open(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	GPIOx->INTEN |= (0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* 函数名称:	EXTI_Close()
* 功能说明:	指定引脚外部中断关闭（即禁能）
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 		指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void EXTI_Close(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	GPIOx->INTEN &= ~(0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* 函数名称:	EXTI_State()
* 功能说明:	指定引脚是否触发了中断
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 		指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: uint32_t	            1 此引脚触发了中断    0 此引脚未触发中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t EXTI_State(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	return (GPIOx->INTSTAT >> GPIO_Pin) & 0x01;
}

/****************************************************************************************************************************************** 
* 函数名称:	EXTI_RawState()
* 功能说明:	指定引脚是否满足过/了中断触发条件，当此中断关闭时可通过调用此函数以查询的方式检测引脚上是否满足过/了中断触发条件
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 	    指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: uint32_t	            1 此引脚满足过/了中断触发条件    0 此引脚未满足过/了中断触发条件
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t EXTI_RawState(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	return (GPIOx->INTRAWSTAT >> GPIO_Pin) & 0x01;
}

/****************************************************************************************************************************************** 
* 函数名称:	EXTI_Clear()
* 功能说明:	指定引脚外部中断清除（即清除中断标志，以免再次进入此中断）
* 输    入: GPIO_TypeDef * GPIOx	指定产生外部中断的GPIO端口，有效值包括GPIOA、GPIOB、GPIOC
*			uint32_t GPIO_Pin 	    指定产生外部中断的GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 只能清除边沿触发中断的标志，电平触发中断的标志无法清除，只能在引脚电平不符合中断触发条件后硬件自动清除
******************************************************************************************************************************************/
void EXTI_Clear(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	EXTI_Assert_Param(GPIOx,GPIO_Pin);                     //检查输入的参数是否合法    
	
	GPIOx->INTCLR = (0x01 << GPIO_Pin);
}


