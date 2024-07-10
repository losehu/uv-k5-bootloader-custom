#include <stdint.h>
#include "DP32G030.h"


uint32_t SystemCoreClock  = __HSI;   				      //System Clock Frequency (Core Clock)
uint32_t CyclesPerUs      = (__HSI / 1000000); 		      //Cycles per micro second


void XTAL_Port_Init(void)
{
	PORT_InitTypeDef PORT_InitStruct = {0};
	
	PORT_InitStruct.Port = PORTA;
	PORT_InitStruct.Pin = GPIO_PIN1;
	PORT_InitStruct.Func = PORTA_PIN1_XTAL_XI;
	PORT_InitStruct.Input_En = ENABLE;           
	
	PORT_Init(&PORT_InitStruct);     //PORTA1配置为XTAL的XI引脚
	
	PORT_InitStruct.Port = PORTA;
	PORT_InitStruct.Pin = GPIO_PIN2;
	PORT_InitStruct.Func = PORTA_PIN2_XTAL_XO;
	PORT_InitStruct.Input_En = ENABLE;           
	
	PORT_Init(&PORT_InitStruct);     //PORTA2配置为XTAL的XO引脚
}


void XTAH_Port_Init(void)
{
	PORT_InitTypeDef PORT_InitStruct = {0};
	
	PORT_InitStruct.Port = PORTA;
	PORT_InitStruct.Pin = GPIO_PIN3;
	PORT_InitStruct.Func = PORTA_PIN3_XTAH_XI;
	PORT_InitStruct.Input_En = ENABLE;           
	
	PORT_Init(&PORT_InitStruct);     //PORTA3配置为XTAH的XI引脚
	
	PORT_InitStruct.Port = PORTA;
	PORT_InitStruct.Pin = GPIO_PIN4;
	PORT_InitStruct.Func = PORTA_PIN4_XTAH_XO;
	PORT_InitStruct.Input_En = ENABLE;           
	
	PORT_Init(&PORT_InitStruct);     //PORTA4配置为XTAH的XO引脚
}


uint32_t  Sys_Clk_Read(void)
{
	uint32_t temp = 0,data1 = 0,data2 = 0;
	
	temp = SYS->CLKSEL;
	
	data1 = ((temp & SYS_CLKSEL_PLL_READ_MSK) >> SYS_CLKSEL_PLL_READ_POS) << SYS_CLKSEL_PLL_POS;
	
	temp &= ~(SYS_CLKSEL_PLL_READ_MSK);
	
	data2 = ((temp & SYS_CLKSEL_ADC_READ_MSK) >> SYS_CLKSEL_ADC_READ_POS) << SYS_CLKSEL_ADC_POS;
	
	temp &= ~(SYS_CLKSEL_ADC_READ_MSK);
	
	temp |= data1;
	
	temp |= data2;
	
	return temp;
}


void Switch_CLK_48MHZ(void)
{
	uint32_t temp = 0;
	
	temp = PMU->SRC_CFG;
	
	temp |= 0x01 << PMU_SRC_CFG_RCHF_EN_POS;               //RCHF使能 
	temp &= ~(0x01 << PMU_SRC_CFG_RCHF_FSEL_POS);          //RCHF选择48MHZ
	
	PMU->SRC_CFG = temp;
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);                 //时钟源选择RCHF
	temp &= ~(0x01 << SYS_CLKSEL_SYS_POS);                 //系统时钟选择为RCHF
	
	SYS->CLKSEL = temp;
	
	SYS->CLKDIV_EN &= ~(0x01 << SYS_CLKDIV_EN_DIV_POS);    //分频时钟禁止输出
}


void Switch_CLK_48MHZ_DIV2(void)
{
	uint32_t temp = 0;
	
	temp = PMU->SRC_CFG;
	
	temp |= 0x01 << PMU_SRC_CFG_RCHF_EN_POS;               //RCHF使能 
	temp |= 0x01 << PMU_SRC_CFG_RCHF_FSEL_POS;             //RCHF选择24MHZ
	
	PMU->SRC_CFG = temp;
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);                 //时钟源选择RCHF
	temp &= ~(0x01 << SYS_CLKSEL_SYS_POS);                 //系统时钟选择为RCHF
	
	SYS->CLKSEL = temp;
	
	SYS->CLKDIV_EN &= ~(0x01 << SYS_CLKDIV_EN_DIV_POS);    //分频时钟禁止输出
}


void Switch_CLK_48MHZ_DIV4(void)
{
	uint32_t temp = 0;
	
	Switch_CLK_48MHZ_DIV2();                               //切换时钟时首先切回到内部24MHZ
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x07 << SYS_CLKSEL_DIV_POS);       
	temp |= DIV_CLK_SEL_DIV2 << SYS_CLKSEL_DIV_POS;        //分频时钟选择2分频

	SYS->CLKSEL = temp;
	
	SYS->CLKDIV_EN |= 0x01 << SYS_CLKDIV_EN_DIV_POS;       //分频时钟输出 
	
	temp = Sys_Clk_Read();
	
	temp |= 0x01 << SYS_CLKSEL_SYS_POS;          //系统时钟选择分频时钟   
	
	SYS->CLKSEL = temp;
}

void Switch_CLK_XTAH(void)
{
	uint32_t k = 0,temp = 0;
	
	Switch_CLK_48MHZ_DIV2();                               //切换时钟时首先切回到内部24MHZ
	
	XTAH_Port_Init();                                      //将相应端口配置为XTAH功能
	
	PMU->SRC_CFG |= 0x01 << PMU_SRC_CFG_XTAH_EN_POS;       //XTAH使能
	
	for(k = 0; k < 1000000;k++);                           //XTAH使能后，至少等待10ms再使用
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x07 << SYS_CLKSEL_DIV_POS);              //分频时钟选择1分频
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);       
	temp |= SRC_CLK_SEL_XTAH << SYS_CLKSEL_SRC_POS;     //时钟源选择XTAH
	
	SYS->CLKSEL = temp;
	
	SYS->CLKDIV_EN |= 0x01 << SYS_CLKDIV_EN_DIV_POS;    //分频时钟输出 
	
	temp = Sys_Clk_Read();
	
	temp |= 0x01 << SYS_CLKSEL_SYS_POS;          //系统时钟选择分频时钟   
	
	SYS->CLKSEL = temp;
}

void Switch_CLK_XTAH_DIV2(void)
{
	uint32_t k = 0,temp = 0;
	
	Switch_CLK_48MHZ_DIV2();                            //切换时钟时首先切回到内部24MHZ
	
	XTAH_Port_Init();                                   //将相应端口配置为XTAH功能
	
	PMU->SRC_CFG |= 0x01 << PMU_SRC_CFG_XTAH_EN_POS;    //XTAH使能
	
	for(k = 0; k < 1000000;k++);                        //XTAH使能后，至少等待10ms再使用
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x07 << SYS_CLKSEL_DIV_POS);       
	temp |= 0x01 << SYS_CLKSEL_DIV_POS;                 //分频时钟选择2分频
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);       
	temp |= SRC_CLK_SEL_XTAH << SYS_CLKSEL_SRC_POS;     //时钟源选择XTAH
	
	SYS->CLKSEL = temp;
	
	SYS->CLKDIV_EN |= 0x01 << SYS_CLKDIV_EN_DIV_POS;    //分频时钟输出 
	
	temp = Sys_Clk_Read();
	
	temp |= 0x01 << SYS_CLKSEL_SYS_POS;          //系统时钟选择分频时钟   
	
	SYS->CLKSEL = temp;
}

void Switch_CLK_PLL_RCHF_Set(uint8_t Pll_M,uint8_t Pll_N)
{
	uint32_t temp = 0;
	
	Switch_CLK_48MHZ_DIV2();                            //切换时钟时首先切回到内部24MHZ
	
	temp = Sys_Clk_Read();

	temp &= ~(0x01 << SYS_CLKSEL_PLL_POS);              //PLL参考时钟选择RCHF
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);       
	temp |= SRC_CLK_SEL_PLL << SYS_CLKSEL_SRC_POS;      //时钟源选择PLL
	
	temp &= ~(0x07 << SYS_CLKSEL_DIV_POS);              //分频时钟选择1分频
	
	SYS->CLKSEL = temp;
	
	temp = SYS->PLL_CTRL; 
	
	temp &= ~(0x1F << SYS_PLL_CTRL_PLL_M_POS);          //PLL参考时钟分频参数设置
	temp |= Pll_M << SYS_PLL_CTRL_PLL_M_POS;            //M = Pll_M     2M <= CLK/M <= 6M    最好配置到4M
	
	temp &= ~(0x1F << SYS_PLL_CTRL_PLL_N_POS);          //PLL参考时钟FEEDBACK参数设置
	temp |= Pll_N << SYS_PLL_CTRL_PLL_N_POS;            //N = Pll_N     PLL = CLK/M*N   
	
	temp |= 0x01 << SYS_PLL_CTRL_PLL_EN_POS;            //PLL使能
	
	SYS->PLL_CTRL = temp;
	
	while((SYS->PLL_ST & SYS_PLL_ST_LOCK_MSK) == 0);    //等待PLL锁定
	
	SYS->CLKDIV_EN |= 0x01 << SYS_CLKDIV_EN_DIV_POS;    //分频时钟输出 
	
	temp = Sys_Clk_Read();
	
	temp |= 0x01 << SYS_CLKSEL_SYS_POS;          //系统时钟选择分频时钟   
	
	SYS->CLKSEL = temp;
}


void Switch_CLK_PLL_RCHF_72MHz(void)
{
	Switch_CLK_PLL_RCHF_Set(PLL_M_DIV6,PLL_N_MUL18);     
}


void Switch_CLK_PLL_RCHF_64MHz(void)
{
	Switch_CLK_PLL_RCHF_Set(PLL_M_DIV6,PLL_N_MUL16);
}


void Switch_CLK_PLL_XTAH_Set(uint8_t Pll_M,uint8_t Pll_N)
{
	uint32_t k = 0,temp = 0;
	
	Switch_CLK_48MHZ_DIV2();                            //切换时钟时首先切回到内部24MHZ
	
	XTAH_Port_Init();                                   //将相应端口配置为XTAH功能
	
	PMU->SRC_CFG |= 0x01 << PMU_SRC_CFG_XTAH_EN_POS;    //XTAH使能
	
	for(k = 0; k < 1000000;k++);                        //XTAH使能后，至少等待10ms再使用
	
	temp = Sys_Clk_Read();

	temp |= (0x01 << SYS_CLKSEL_PLL_POS);               //PLL参考时钟选择XTAH
	
	temp &= ~(0x07 << SYS_CLKSEL_SRC_POS);       
	temp |= SRC_CLK_SEL_PLL << SYS_CLKSEL_SRC_POS;      //时钟源选择PLL
	
	temp &= ~(0x07 << SYS_CLKSEL_DIV_POS);              //分频时钟选择1分频
	
	SYS->CLKSEL = temp;
	
	temp = SYS->PLL_CTRL; 
	
	temp &= ~(0x1F << SYS_PLL_CTRL_PLL_M_POS);          //PLL参考时钟分频参数设置
	temp |= Pll_M << SYS_PLL_CTRL_PLL_M_POS;            //M = Pll_N      2M <= HSE/M <= 6M    最好配置到4M
	
	temp &= ~(0x1F << SYS_PLL_CTRL_PLL_N_POS);          //PLL参考时钟FEEDBACK参数设置
	temp |= Pll_N << SYS_PLL_CTRL_PLL_N_POS;            //N = Pll_N     PLL = HSE/M*N   
	
	temp |= 0x01 << SYS_PLL_CTRL_PLL_EN_POS;            //PLL使能
	
	SYS->PLL_CTRL = temp;
	
	while((SYS->PLL_ST & SYS_PLL_ST_LOCK_MSK) == 0);    //等待PLL锁定
	
	SYS->CLKDIV_EN |= 0x01 << SYS_CLKDIV_EN_DIV_POS;    //分频时钟输出 
	
	temp = Sys_Clk_Read();
	
	temp |= 0x01 << SYS_CLKSEL_SYS_POS;                 //系统时钟选择分频时钟   
	
	SYS->CLKSEL = temp;
}

void Switch_CLK_PLL_XTAH_72MHz(void)
{
	Switch_CLK_PLL_XTAH_Set(PLL_M_DIV2,PLL_N_MUL18);    
}

void Switch_CLK_PLL_XTAH_64MHz(void)
{
	Switch_CLK_PLL_XTAH_Set(PLL_M_DIV2,PLL_N_MUL16);
}

void Switch_CLK_PLL_XTAH_56MHz(void)
{
	Switch_CLK_PLL_XTAH_Set(PLL_M_DIV2,PLL_N_MUL14);
}

void Switch_CLK_PLL_XTAH_48MHz(void)
{
	Switch_CLK_PLL_XTAH_Set(PLL_M_DIV2,PLL_N_MUL12);
}


void SystemCoreClockUpdate(void)
{
	uint8_t Clk_Div = 1;
	
	if((SYS->CLKSEL & SYS_CLKSEL_SYS_MSK) == 0)               //系统时钟选择RCHF
	{
		if(PMU->SRC_CFG & PMU_SRC_CFG_RCHF_FSEL_MSK)          
		{
			SystemCoreClock  = __HSI >> 1;                    //RCHF频率选择24M
		}
		else
		{
			SystemCoreClock  = __HSI;                         //RCHF频率选择48M
		}
	}
	else
	{
		Clk_Div = 0x01 << ((SYS->CLKSEL & SYS_CLKSEL_DIV_MSK) >> SYS_CLKSEL_DIV_POS);              //获取配置的分频时钟分频系数
		
		if(((SYS->CLKSEL & SYS_CLKSEL_SRC_MSK)>> SYS_CLKSEL_SRC_POS) == SRC_CLK_SEL_RCHF)          //源时钟选择RCHF        
		{
			if(PMU->SRC_CFG & PMU_SRC_CFG_RCHF_FSEL_MSK) 
			{
				Clk_Div  *= 2;      //如果RCHF是24M，则分频系数乘以2
			}
			
			SystemCoreClock  = __HSI / Clk_Div; 
		}
		else if(((SYS->CLKSEL & SYS_CLKSEL_SRC_MSK) >> SYS_CLKSEL_SRC_POS) == SRC_CLK_SEL_XTAH)    //源时钟选择XTAH 
		{
			SystemCoreClock  = __HSE / Clk_Div; 
		}
		else if(((SYS->CLKSEL & SYS_CLKSEL_SRC_MSK) >> SYS_CLKSEL_SRC_POS) == SRC_CLK_SEL_PLL)     //源时钟选择PLL
		{
			if(((SYS->CLKSEL & SYS_CLKSEL_PLL_READ_MSK) >> SYS_CLKSEL_PLL_READ_POS) == PLL_CLK_SEL_RCHF)
			{
				if(PMU->SRC_CFG & PMU_SRC_CFG_RCHF_FSEL_MSK) 
				{
					Clk_Div  *= 2;      //如果RCHF是24M，则分频系数乘以2
				}
				
				SystemCoreClock = __HSI / (((SYS->PLL_CTRL & SYS_PLL_CTRL_PLL_M_MSK) >> SYS_PLL_CTRL_PLL_M_POS) + 1);
			}
			else
			{
				SystemCoreClock = __HSE / (((SYS->PLL_CTRL & SYS_PLL_CTRL_PLL_M_MSK) >> SYS_PLL_CTRL_PLL_M_POS) + 1);
			}
			
			SystemCoreClock *= ((((SYS->PLL_CTRL & SYS_PLL_CTRL_PLL_N_MSK) >> SYS_PLL_CTRL_PLL_N_POS) + 1)*2);
				
			SystemCoreClock /= Clk_Div;
		}		
	}

	CyclesPerUs = SystemCoreClock/1000000;
}




void SystemClkSel(uint8_t clk)
{		
	switch(clk)
	{
		case SYS_CLK_48MHz:			               //0 内部高频48MHz RC振荡器
			
			Switch_CLK_48MHZ();
		
		break;
		
		case SYS_CLK_48MHz_DIV2:			       //1 内部高频48MHz RC振荡器  2分频
			
			Switch_CLK_48MHZ_DIV2();
		
		break;
		
		case SYS_CLK_48MHz_DIV4:                   //2 内部高频48MHz RC振荡器  4分频
			
			Switch_CLK_48MHZ_DIV4();
		
		break;
		
		case SYS_CLK_XTAH:                         //3 外部高频晶体振荡器（4-32MHz）
			
			Switch_CLK_XTAH();
		
		break;
		
		case SYS_CLK_XTAH_DIV2:                    //4 外部高频晶体振荡器（4-32MHz） 2分频
			
			Switch_CLK_XTAH_DIV2();
		
		break;
		
		case SYS_CLK_PLL_RCHF_72MHz:              //5 PLL时钟  RCHF作为输入时钟倍频输出72MHz
			
			Switch_CLK_PLL_RCHF_72MHz();
		
		break;
		
		case SYS_CLK_PLL_RCHF_64MHz:              //6 PLL时钟  RCHF作为输入时钟倍频输出64MHz
			
			Switch_CLK_PLL_RCHF_64MHz();
		
		break;
		
		case SYS_CLK_PLL_XTAH_72MHz:              //7 PLL时钟  XTAH作为输入时钟倍频输出72MHz
			
			Switch_CLK_PLL_XTAH_72MHz();
		
		break;
		
		case SYS_CLK_PLL_XTAH_64MHz:              //8 PLL时钟  XTAH作为输入时钟倍频输出64MHz	
			
			Switch_CLK_PLL_XTAH_64MHz();
		
		break;
		
		case SYS_CLK_PLL_XTAH_56MHz:              //9 PLL时钟  XTAH作为输入时钟倍频输出56MHz	
			
			Switch_CLK_PLL_XTAH_56MHz();
		
		break;
		
		case SYS_CLK_PLL_XTAH_48MHz:              //10 PLL时钟  XTAH作为输入时钟倍频输出48MHz	
			
			Switch_CLK_PLL_XTAH_48MHz();
		
		break;
	}
}


/****************************************************************************************************************************************** 
* 函数名称: 
* 功能说明: The necessary initializaiton of system
* 输    入: 
* 输    出: 
* 注意事项: 
******************************************************************************************************************************************/
void SystemInit(void)
{		
	FLASH_Init(FLASH_ONE_CLK_WAIT);                    //FLASH初始化
	
	Read_Trim_Value_From_Flash();                      //从NVR区读取TTRIM值并写入相应寄存器
	
	SystemClkSel(SYS_CLK_48MHz);                       //配置系统时钟为48MHz
	
	SystemCoreClockUpdate();	                       //计算配置的系统时钟 
	
	FLASH_Init(FLASH_TWO_CLK_WAIT);                    //FLASH初始化
}


