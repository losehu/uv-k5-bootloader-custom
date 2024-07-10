#include "DP32G030_adc.h"

/****************************************************************************************************************************************** 
* 函数名称: ADC_Init()
* 功能说明:	ADC模数转换器初始化
* 输    入: ADC_ADC_initStructure * ADC_initStruct		包含ADC各相关定值的结构体		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Init(ADC_InitStructure * ADC_initStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_ADC_CLKDIV(ADC_initStruct->Clk_Div));                      //检查输入的参数Clk_Div是否合法   
	
	assert_param(IS_ADC_CH(ADC_initStruct->Channels));                         //检查输入的参数Channels是否合法  
	
	assert_param(IS_ADC_SAMP_AVG(ADC_initStruct->SampAvg));                    //检查输入的参数SampAvg是否合法  
	
	assert_param(IS_ADC_SAMP_MODE(ADC_initStruct->Samp_Mode));                 //检查输入的参数Samp_Mode是否合法  
	
	assert_param(IS_ADC_EXTSAMP_CLKWIN(ADC_initStruct->ExtSamp_ClkWin));       //检查输入的参数ExtSamp_ClkWin是否合法  
	
	assert_param(IS_ADC_MODE(ADC_initStruct->Mode));                           //检查输入的参数Mode是否合法  
	
	assert_param(IS_ADC_SAMP_CLOCK(ADC_initStruct->SampClk));                  //检查输入的参数SampClk是否合法  
	
	assert_param(IS_ADC_INSAMP_CLKWIN(ADC_initStruct->InSamp_ClkWin));         //检查输入的参数InSamp_ClkWin是否合法  
	
	assert_param(IS_ADC_OFFSET_EN(ADC_initStruct->Offset_En));                 //检查输入的参数Offset_En是否合法  
	
	assert_param(IS_ADC_KD_EN(ADC_initStruct->Kd_En));                         //检查输入的参数Kd_En是否合法  
	
	assert_param(IS_ADC_DMA_EN(ADC_initStruct->DMA_En));                       //检查输入的参数Kd_En是否合法  
	
	assert_param(IS_ADC_FIFO_FULL_IEN(ADC_initStruct->Full_IEn));              //检查输入的参数Full_IEn是否合法  
	
	assert_param(IS_ADC_FIFO_HALFFULL_IEN(ADC_initStruct->HalfFull_IEn));      //检查输入的参数HalfFull_IEn是否合法  
	 
	
	SYS->CLKEN |= 0x01 << SYS_CLKEN_ADC_POS;        //打开ADC的时钟

	ADC_Close();                                    //一些关键寄存器只能在ADC关闭时设置
	
	temp = Sys_Clk_Read();
	
	temp &= ~(0x03 << SYS_CLKSEL_ADC_POS);
	temp |= ADC_initStruct->Clk_Div << SYS_CLKSEL_ADC_POS;     //ADC转换时钟分频，取值1 2 4 8
	
	SYS->CLKSEL = temp;
	
	temp = ADC->CFG;
	
	temp &= ~(0xFFFF << ADC_CFG_CH0_POS);
	temp |= ADC_initStruct->Channels << ADC_CFG_CH0_POS;   //ADC转换通道选中，ADC_CH0、ADC_CH1、... ... 、ADC_CH15及其组合（即“按位或”运算）
	
	temp &= ~(0x03 << ADC_CFG_AVG_POS);
	temp |= ADC_initStruct->SampAvg << ADC_CFG_AVG_POS;    //采样取平均，触发启动ADC转换后，ADC在一个通道上连续采样、转换多次，并将它们的平均值作为该通道转换结果
	
	temp &= ~(0x01 << ADC_CFG_CONT_POS);
	temp |= ADC_initStruct->Samp_Mode << ADC_CFG_CONT_POS;  //在软件触发模式下：1 连续转换模式，启动后一直采样、转换，直到软件清除START位
                                                            //                  0 单次转换模式，转换完成后START位自动清除停止转换	 
	temp &= ~(0x07 << ADC_CFG_SMPL_SETUP_POS);
	temp |= ADC_initStruct->ExtSamp_ClkWin << ADC_CFG_SMPL_SETUP_POS;  //外部采样窗口设置
	
	temp &= ~(0x01 << ADC_CFG_MEM_MODE_POS);
	temp |= ADC_initStruct->Mode << ADC_CFG_MEM_MODE_POS;      //数据存储为FIFO模式还是通道模式   0: FIFO  1:通道
	
	temp &= ~(0x01 << ADC_CFG_SMPL_CLK_POS);
	temp |= ADC_initStruct->SampClk << ADC_CFG_SMPL_CLK_POS;   //ADC采样时钟选择  1:内部采样时钟   0:外部采样时钟
	
	temp &= ~(0x07 << ADC_CFG_IN_SMPL_WIN_POS);
	temp |= ADC_initStruct->InSamp_ClkWin << ADC_CFG_IN_SMPL_WIN_POS;  //内部采样窗口设置
	
	temp &= ~(0x01 << ADC_CFG_TRIG_POS);
	temp |= ADC_initStruct->Trig << ADC_CFG_TRIG_POS;                  //ADC触发源信号选择
	
	temp &= ~(0x01 << ADC_CFG_DMAEN_POS);
	temp |= ADC_initStruct->DMA_En << ADC_CFG_DMAEN_POS;               //DMA使能  0:不使能 CPU读取FIFO数据 1:使能  DMA读取FIFO数据
	
	ADC->CFG = temp;
	
	temp = ADC->EXTTRIG_SEL;
	
	temp &= ~(0xFFF << ADC_EXTTRIG_PWMPLUS0_TRIG0_POS);               //选择触发源来触发ADC采样
	temp = (ADC_initStruct->ExtTrig_Sel << ADC_EXTTRIG_PWMPLUS0_TRIG0_POS);
	
	ADC->EXTTRIG_SEL = temp;
	
	if(ADC_initStruct->Offset_En == ENABLE)                      //offset数据使能   0:不使能  1:使能
	{
		ADC->CALIB_OFFSET |=  0x01 << ADC_CALIB_OFFSET_VALID_POS;  
	}
	else
	{
		ADC->CALIB_OFFSET &= ~(0x01 << ADC_CALIB_OFFSET_VALID_POS);
	}
	
	if(ADC_initStruct->Kd_En == ENABLE)                         //kd数据使能       0:不使能  1:使能
	{
		ADC->CALIB_KD |= 0x01 << ADC_CALIB_KD_VALID_POS;              
	}
	else
	{
		ADC->CALIB_KD &= ~(0x01 << ADC_CALIB_KD_VALID_POS);
	}
	

	ADC->IF = 0xFFFFFFFF;	//清除中断标志
	
	temp = ADC->IE;
	
	temp &= ~(0xFFFF);
	temp |=  (((ADC_initStruct->Eoc_IEn & ADC_CH0)  ? 1 : 0) << ADC_IE_CH0EOC_POS)  |
		     (((ADC_initStruct->Eoc_IEn & ADC_CH1)  ? 1 : 0) << ADC_IE_CH1EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH2)  ? 1 : 0) << ADC_IE_CH2EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH3)  ? 1 : 0) << ADC_IE_CH3EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH4)  ? 1 : 0) << ADC_IE_CH4EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH5)  ? 1 : 0) << ADC_IE_CH5EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH6)  ? 1 : 0) << ADC_IE_CH6EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH7)  ? 1 : 0) << ADC_IE_CH7EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH8)  ? 1 : 0) << ADC_IE_CH8EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH9)  ? 1 : 0) << ADC_IE_CH9EOC_POS)  |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH10) ? 1 : 0) << ADC_IE_CH10EOC_POS) |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH11) ? 1 : 0) << ADC_IE_CH11EOC_POS) |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH12) ? 1 : 0) << ADC_IE_CH12EOC_POS) |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH13) ? 1 : 0) << ADC_IE_CH13EOC_POS) |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH14) ? 1 : 0) << ADC_IE_CH14EOC_POS) |
			 (((ADC_initStruct->Eoc_IEn & ADC_CH15) ? 1 : 0) << ADC_IE_CH15EOC_POS) ;   //通道数据转换完成中断使能  如果开启了多个通道转换，只需要开启最后一个通道的中断即可
	 
	temp &= ~(0x01 << ADC_IE_FIFO_FULL_POS);
	temp |= ADC_initStruct->Full_IEn << ADC_IE_FIFO_FULL_POS;        //FIFO满中断使能
	
	temp &= ~(0x01 << ADC_IE_FIFO_HFULL_POS);
	temp |= ADC_initStruct->HalfFull_IEn << ADC_IE_FIFO_HFULL_POS;   //FIFO半满中断使能  

	ADC->IE = temp;
	
	if(ADC->IE != 0)
	{
		NVIC_EnableIRQ(ADC_IRQn);
	}
	else
	{
		NVIC_DisableIRQ(ADC_IRQn);
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_Open()
* 功能说明:	ADC开启
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Open(void)
{
	ADC->CFG |= (0x01 << ADC_CFG_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_Close()
* 功能说明:	ADC关闭
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Close(void)
{
	ADC->CFG &= ~(0x01 << ADC_CFG_EN_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_Start()
* 功能说明:	ADC启动转换
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Start(void)
{
	ADC->START |= (0x01 << ADC_START_START_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_Stop()
* 功能说明:	ADC停止转换
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Stop(void)
{
	ADC->START &= ~(0x01 << ADC_START_START_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_SoftReset()
* 功能说明:	ADC软复位
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_SoftReset(void)
{
	ADC->START &= ~(0x01 << ADC_START_SOFT_RESET_POS);
	ADC->START |= (0x01 << ADC_START_SOFT_RESET_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	chn2idx()
* 功能说明:	通道转换
* 输    入: chn   ADC_CH0  ---  ADC_CH15 
* 输    出: 通道索引
* 注意事项: 无
******************************************************************************************************************************************/
static uint8_t chn2idx(uint32_t chn)
{
	uint32_t idx = 0;
	
	assert_param(IS_ADC_CH(chn));           //检查输入的参数chn是否合法   
	
	switch(chn)
	{
		case 0x01:   idx = 0;  break;
		case 0x02:   idx = 1;  break;
		case 0x04:   idx = 2;  break;
		case 0x08:   idx = 3;  break;
		case 0x10:   idx = 4;  break;
		case 0x20:   idx = 5;  break;
		case 0x40:   idx = 6;  break;
		case 0x80:   idx = 7;  break;
		case 0x100:  idx = 8;  break;
		case 0x200:  idx = 9;  break;
		case 0x400:  idx = 10; break;
		case 0x800:  idx = 11; break;
		case 0x1000: idx = 12; break;
		case 0x2000: idx = 13; break;
		case 0x4000: idx = 14; break;
		case 0x8000: idx = 15; break;
	}
	
	return idx;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_Read()
* 功能说明:	从指定通道读取转换结果
* 输    入: uint32_t chn			要读取转换结果的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15				
* 输    出: uint16_t				读取到的转换结果
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t ADC_Read(uint32_t chn)
{
	uint16_t data = 0;
	
	uint8_t idx = chn2idx(chn);

	data = ADC->CH[idx].DATA & 0xFFF;
		
	ADC->IF = (0x01 << idx);   //清除EOC标志
	
	return data;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_Read_FIFO()
* 功能说明:	从FIFO寄存器中读取转换结果
* 输    入: uint8_t num			    要读取的数据个数			
* 输    出: uint16_t * buffer	    读取的num个数据   数据中包含了通道号和通道转换结果
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_Read_FIFO(uint16_t * buffer,uint8_t num)
{
	uint8_t k = 0;
	
	for(k = 0;k < num;k++)
	{
		buffer[k] = ADC->FIFO_DATA & 0xFFFF;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_FIFO_Clr()
* 功能说明:	清除FIFO寄存器
* 输    入: 无			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_FIFO_Clr(void)
{
	ADC->START |= 0x01 << ADC_START_FIFOCLR_POS;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_IsEOC()
* 功能说明:	指定通道是否转换完成
* 输    入: uint32_t chn			要查询状态的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15				
* 输    出: uint8_t				    1 该通道完成了转换    0 该通道未完成转换
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_IsEOC(uint32_t chn)
{
	uint8_t idx = chn2idx(chn);
	
	return (ADC->CH[idx].STAT & ADC_STAT_EOC_MSK) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntEOCEn()
* 功能说明:	转换完成中断使能
* 输    入: uint32_t chn			要设置的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15				
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntEOCEn(uint32_t chn)
{
	uint8_t idx = chn2idx(chn);
	
	ADC->IE |= (0x01 << idx);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntEOCEn()
* 功能说明:	转换完成中断禁止
* 输    入: uint32_t chn			要设置的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15				
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntEOCDis(uint32_t chn)
{
	uint8_t idx = chn2idx(chn);
	
	ADC->IE &= ~(0x01 << idx);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntEOCStat()
* 功能说明:	转换完成中断状态
* 输    入: uint32_t chn			要查询的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15					
* 输    出: uint8_t				    1 该通道完成了转换    0 该通道未完成转换
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_IntEOCStat(uint32_t chn)
{
	uint8_t idx = chn2idx(chn);
	
	return (ADC->IF & (0x01 << idx)) ? 1 : 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntEOCEn()
* 功能说明:	转换完成中断标志清除
* 输    入: uint32_t chn			要设置的通道，有效值ADC_CH0、ADC_CH1、... ... 、ADC_CH15				
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntEOCClr(uint32_t chn)
{
	uint8_t idx = chn2idx(chn);
	
	ADC->IF = (0x01 << idx);
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_FIFO_Level()
* 功能说明:	获取FIFO水位
* 输    入: 无		
* 输    出: uint8_t	  FIFO水位  表示FIFO中现在有多少数据可以读取			    
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_FIFO_Level(void)
{
	uint8_t Level = 0;
	
	Level = (ADC->FIFO_STAT & ADC_FIFO_STAT_LEVEL_MSK) >> ADC_FIFO_STAT_LEVEL_POS;

	if(Level == 0)
	{
		if((ADC->FIFO_STAT & ADC_FIFO_STAT_FULL_MSK))
		{
			Level = 16;
		}
	}
	
	return Level;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_FULLStat()
* 功能说明:	FIFO满状态
* 输    入: 无		
* 输    出: uint8_t				1 FIFO满   0 FIFO未满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_FULLStat(void)
{
	return (ADC->FIFO_STAT & ADC_FIFO_STAT_FULL_MSK) ? 1 : 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_HALFFULLStat()
* 功能说明:	FIFO半满状态
* 输    入: 无		
* 输    出: uint8_t				1 FIFO半满   0 FIFO未半满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_HALFFULLStat(void)
{
	return (ADC->FIFO_STAT & ADC_FIFO_STAT_HFULL_MSK) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_EMPTYStat()
* 功能说明:	FIFO空状态
* 输    入: 无		
* 输    出: uint8_t				1 FIFO空  0 FIFO未空
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_EMPTYStat(void)
{
	return (ADC->FIFO_STAT & ADC_FIFO_STAT_EMPTY_MSK) ? 1 : 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntFULLEn()
* 功能说明:	FIFO满中断使能
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntFULLEn(void)
{
	ADC->IE |= (0x01 << ADC_IE_FIFO_FULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntFULLDis()
* 功能说明:	FIFO满中断禁止
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntFULLDis(void)
{
	ADC->IE &= ~(0x01 << ADC_IE_FIFO_FULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntFULLStat()
* 功能说明:	FIFO满中断状态
* 输    入: 无		
* 输    出: uint8_t				1 FIFO满   0 FIFO未满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_IntFULLStat(void)
{
	return (ADC->IF & ADC_IF_FIFO_FULL_MSK) ? 1 : 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntFULLClr()
* 功能说明:	FIFO满中断状态清除
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntFULLClr(void)
{
	ADC->IF = (0x01 << ADC_IF_FIFO_FULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntHALFFULLEn()
* 功能说明:	FIFO半满中断使能
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntHALFFULLEn(void)
{
	ADC->IE |= (0x01 << ADC_IE_FIFO_HFULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntHALFFULLDis()
* 功能说明:	FIFO半满中断禁止
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntHALFFULLDis(void)
{
	ADC->IE &= ~(0x01 << ADC_IE_FIFO_HFULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntHALFFULLStat()
* 功能说明:	FIFO半满中断状态
* 输    入: 无		
* 输    出: uint8_t				1 FIFO半满   0 FIFO未半满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t ADC_IntHALFFULLStat(void)
{
	return (ADC->IF & ADC_IF_FIFO_HFULL_MSK) ? 1 : 0;
}


/****************************************************************************************************************************************** 
* 函数名称:	ADC_IntHALFFULLClr()
* 功能说明:	FIFO半满中断状态清除
* 输    入: 无		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void ADC_IntHALFFULLClr(void)
{
	ADC->IF = (0x01 << ADC_IF_FIFO_HFULL_POS);
}


