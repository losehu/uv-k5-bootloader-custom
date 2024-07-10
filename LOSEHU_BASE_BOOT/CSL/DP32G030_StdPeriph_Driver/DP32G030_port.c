#include "DP32G030_port.h"


/****************************************************************************************************************************************** 
* 函数名称: PORT_Init()
* 功能说明:	端口引脚功能选择
* 输    入: PORT_InitTypeDef* PORT_InitStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_Init(PORT_InitTypeDef* PORT_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_PORT_ALL(PORT_InitStruct->Port));                             //检查输入的参数Port是否合法   
	
	assert_param(IS_INPUT_EN(PORT_InitStruct->Input_En));                         //检查输入的参数Input_En是否合法   
	
	assert_param(IS_PORT_FUNC(PORT_InitStruct->Func));                            //检查输入的参数Func是否合法 
	
	switch(PORT_InitStruct->Port)
	{
		case PORTA:
			
			assert_param(IS_GPIOA_PIN(PORT_InitStruct->Pin));                     //检查输入的参数Pin是否合法    
		
			if(PORT_InitStruct->Pin <= GPIO_PIN7)
			{
				temp = PORT->PORTA_SEL0;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin)*4));
				
				PORT->PORTA_SEL0 = temp;          //PORTA0-7 IO端口功能配置
			}
			else if(PORT_InitStruct->Pin <= GPIO_PIN15)
			{
				temp = PORT->PORTA_SEL1;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin - GPIO_PIN8)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin - GPIO_PIN8)*4));

				PORT->PORTA_SEL1 = temp;          //PORTA8-15 IO端口功能配置
			}
			
			if(PORT_InitStruct->Input_En == ENABLE)                                 
			{
				PORT->PORTA_INEN |=  (0x01 << (PORT_InitStruct->Pin));           //输入使能打开
			}
			else
			{
				PORT->PORTA_INEN &= ~(0x01 << (PORT_InitStruct->Pin));           //输入使能关闭
			}
			
		break;

		case PORTB:
			
			assert_param(IS_GPIOB_PIN(PORT_InitStruct->Pin));                     //检查输入的参数Pin是否合法  
			
			if(PORT_InitStruct->Pin <= GPIO_PIN7)
			{
				temp = PORT->PORTB_SEL0;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin)*4));
				
				PORT->PORTB_SEL0 = temp;          //PORTB0-7 IO端口功能配置
			}
			else if(PORT_InitStruct->Pin <= GPIO_PIN15)
			{
				temp = PORT->PORTB_SEL1;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin - GPIO_PIN8)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin - GPIO_PIN8)*4));

				PORT->PORTB_SEL1 = temp;          //PORTB8-15 IO端口功能配置
			}
			
			if(PORT_InitStruct->Input_En == ENABLE)                                 
			{
				PORT->PORTB_INEN |=  (0x01 << (PORT_InitStruct->Pin));           //输入使能打开
			}
			else
			{
				PORT->PORTB_INEN &= ~(0x01 << (PORT_InitStruct->Pin));           //输入使能关闭
			}
			
		break;
			
		case PORTC:
		
			assert_param(IS_GPIOC_PIN(PORT_InitStruct->Pin));                     //检查输入的参数Pin是否合法  
			
			if(PORT_InitStruct->Pin <= GPIO_PIN7)
			{
				temp = PORT->PORTC_SEL0;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin)*4));
				
				PORT->PORTC_SEL0 = temp;          //PORTC0-7 IO端口功能配置
			}
			
			if(PORT_InitStruct->Input_En == ENABLE)                                 
			{
				PORT->PORTC_INEN |=  (0x01 << (PORT_InitStruct->Pin));           //输入使能打开
			}
			else
			{
				PORT->PORTC_INEN &= ~(0x01 << (PORT_InitStruct->Pin));           //输入使能关闭
			}

		break;
		
		default:
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: PORT_CFG_Init()
* 功能说明:	端口配置
* 输    入: PORT_CFGTypeDef* PORT_CFGStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_OUT_CURRENT(PORT_CFGStruct->PortA_Out_Cur));                           //检查输入的参数PortA_Out_Cur是否合法     
	
	assert_param(IS_OUT_CURRENT(PORT_CFGStruct->PortB_Out_Cur));                           //检查输入的参数PortB_Out_Cur是否合法  
	
	assert_param(IS_OUT_CURRENT(PORT_CFGStruct->PortC_Out_Cur));                           //检查输入的参数PortC_Out_Cur是否合法  
	
	assert_param(IS_INPUT_HYS(PORT_CFGStruct->InputHys));                                  //检查输入的参数InputHys是否合法   
	
	
	temp = PORT->PORT_CFG;

	temp &= ~(0x03 << PORT_CFG_PORTA_DS_POS);
	temp |=  ((PORT_CFGStruct->PortA_Out_Cur) << PORT_CFG_PORTA_DS_POS);          //配置PORTA的驱动能力
	
	temp &= ~(0x03 << PORT_CFG_PORTB_DS_POS);
	temp |=  ((PORT_CFGStruct->PortB_Out_Cur) << PORT_CFG_PORTB_DS_POS);          //配置PORTB的驱动能力
	
	temp &= ~(0x03 << PORT_CFG_PORTC_DS_POS);
	temp |=  ((PORT_CFGStruct->PortC_Out_Cur) << PORT_CFG_PORTC_DS_POS);          //配置PORTC的驱动能力
	
	temp &= ~(0x01 << PORT_CFG_HYS_POS);
	temp |=  ((PORT_CFGStruct->InputHys) << PORT_CFG_HYS_POS);                    //配置PORT的输入迟滞等级

	PORT->PORT_CFG = temp;	
}



