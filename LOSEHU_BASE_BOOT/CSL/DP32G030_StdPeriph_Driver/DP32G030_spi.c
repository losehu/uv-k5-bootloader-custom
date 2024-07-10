#include "DP32G030_spi.h"

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Init()
* 功能说明:	SPI初始化
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1  
            SPI_InitTypeDef * SPI_InitStruct    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Init(SPI_TypeDef * SPIx,SPI_InitTypeDef * SPI_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_SPI_MODE(SPI_InitStruct->Master));               //检查输入的参数Master是否合法     
	
	assert_param(IS_SPI_CLKDIV(SPI_InitStruct->ClkDiv));             //检查输入的参数ClkDiv是否合法 
	
	assert_param(IS_SPI_SAMPLE_EDGE(SPI_InitStruct->SampleEdge));    //检查输入的参数SampleEdge是否合法 
	
	assert_param(IS_SPI_IDLE_LEVEL(SPI_InitStruct->IdleLevel));      //检查输入的参数IdleLevel是否合法 
	
	assert_param(IS_SPI_LSBFIRST(SPI_InitStruct->LsbFirst));         //检查输入的参数LsbFirst是否合法 
	
	switch((uint32_t)SPIx)
	{
		case ((uint32_t)SPI0):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_SPI0_POS;    //打开SPI0时钟
		
		break;
		
		case ((uint32_t)SPI1):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_SPI1_POS;    //打开SPI1时钟
		
		break;
	}
	
	SPI_Close(SPIx);     //SPI关闭时设置寄存器
	
	temp = SPIx->CTRL;
	
	temp &= ~(SPI_CTRL_CLKDIV_MSK | SPI_CTRL_CPHA_MSK | SPI_CTRL_CPOL_MSK | SPI_CTRL_MSTR_MSK | SPI_CTRL_LSBF_MSK);
	
	temp |= (SPI_InitStruct->ClkDiv     << SPI_CTRL_CLKDIV_POS) |       //波特率
	        (SPI_InitStruct->SampleEdge << SPI_CTRL_CPHA_POS)   |       //时钟相位选择
	        (SPI_InitStruct->IdleLevel  << SPI_CTRL_CPOL_POS)   |       //时钟极性选择
	        (SPI_InitStruct->Master     << SPI_CTRL_MSTR_POS)   |       //主从模式选择
	        (SPI_InitStruct->LsbFirst   << SPI_CTRL_LSBF_POS);          //数据传输顺序选择  MSB  LSB
	
	temp &= ~SPI_CTRL_RF_CLR_MSK;
	temp |= (SPI_InitStruct->RXFIFO_Clr_Enable << SPI_CTRL_RF_CLR_POS); //接收FIFO清除使能配置
	
	temp &= ~SPI_CTRL_TF_CLR_MSK;
	temp |= (SPI_InitStruct->TXFIFO_Clr_Enable << SPI_CTRL_TF_CLR_POS); //发送FIFO清除使能配置 
	
	SPIx->CTRL = temp;
	
	temp = 0x00;  
	
	temp |= (SPI_InitStruct->RXFIFO_Ovf_IE << SPI_IE_RXFIFO_OVF_POS);          //接收FIFO溢出中断使能配置
	
	temp |= (SPI_InitStruct->RXFIFO_Full_IE << SPI_IE_RXFIFO_FULL_POS);        //接收FIFO满中断使能配置
	
	temp |= (SPI_InitStruct->RXFIFO_HalfFull_IE << SPI_IE_RXFIFO_HFULL_POS);   //接收FIFO半满中断使能配置
	
	temp |= (SPI_InitStruct->TXFIFO_Empty_IE << SPI_IE_TXFIFO_EMPTY_POS);      //发送FIFO空中断使能配置
	
	temp |= (SPI_InitStruct->TXFIFO_HalfFull_IE << SPI_IE_TXFIFO_HFULL_POS);   //发送FIFO半满中断使能配置
	
	SPIx->IE = temp;
	
	if(SPIx->IE != 0)
	{
		switch((uint32_t)SPIx)
		{
			case ((uint32_t)SPI0):
				
				NVIC_EnableIRQ(SPI0_IRQn);        //使能SPI0中断   
			
			break;
			
			case ((uint32_t)SPI1):
				
				NVIC_EnableIRQ(SPI1_IRQn);        //使能SPI1中断   
			
			break;
		}
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Open()
* 功能说明:	SPI打开，允许收发
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Open(SPI_TypeDef * SPIx)
{
	SPIx->CTRL |= (0x01 << SPI_CTRL_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Close()
* 功能说明:	SPI关闭，禁止收发
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Close(SPI_TypeDef * SPIx)
{
	SPIx->CTRL &= ~(0x01 << SPI_CTRL_EN_POS);
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Write()
* 功能说明: 发送一个数据
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
             uint8_t data 			要发送的数据		
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_Write(SPI_TypeDef * SPIx,uint8_t data)
{
	SPIx->WDATA = data;	
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_ReadWrite()
* 功能说明: 发送一个数据，并返回发送过程中接收到的
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
            uint8_t data 			要发送的数据		
* 输    出: uint8_t				    接收到的数据
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_ReadWrite(SPI_TypeDef * SPIx,uint8_t data)
{
	uint8_t temp;
	
	SPIx->WDATA = data;

	while((SPIx->FIFOST & SPI_FIFOST_RXFIFO_EMPTY_MSK));
	temp = SPIx->RDATA;
	
	return temp;
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_WriteBytes()
* 功能说明: 发送数量为num的数据
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
            uint8_t num 			要发送的数据个数	
            uint8_t	*data			发送到的数据
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_WriteBytes(SPI_TypeDef * SPIx,uint8_t* data,uint8_t num)
{
	uint8_t i;
	
	for(i = 0; i < num; i++)
	{
		SPIx->WDATA = data[i];
		while((SPIx->FIFOST & SPI_FIFOST_TXFIFO_FULL_MSK));
	}
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_ReadBytes()
* 功能说明: 接收数量为num的数据
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
            uint8_t num 			要读取的数据个数	
* 输    出: uint8_t	*data			接收到的数据
* 注意事项: 
******************************************************************************************************************************************/
void SPI_ReadBytes(SPI_TypeDef * SPIx,uint8_t* data,uint8_t num)
{
	uint8_t i;
	
	for(i = 0; i < num; i++)
	{
		SPIx->WDATA = 0xFF;
		while((SPIx->FIFOST & SPI_FIFOST_TXFIFO_FULL_MSK));
		
		while((SPIx->FIFOST & SPI_FIFOST_RXFIFO_EMPTY_MSK));
		data[i] = SPIx->RDATA;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Master_SSN_Out()
* 功能说明: 主模式下，SSN输出高低电平控制从机的片选引脚
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 
            uint8_t out 			SSN要输出的电平    0 低电平   1 高电平		
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_Master_SSN_Out(SPI_TypeDef * SPIx,uint8_t out)
{
	if(out == 0)
	{
		SPIx->CTRL &= ~(0x01 << SPI_CTRL_MST_SSN_POS);
	}
	else
	{
		SPIx->CTRL |= (0x01 << SPI_CTRL_MST_SSN_POS);
	}	
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_TXFIFO_Clr()
* 功能说明: 发送FIFO寄存器清除    软件写1清除，硬件自动清0
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_TXFIFO_Clr(SPI_TypeDef * SPIx)
{
	SPIx->CTRL |= (0x01 << SPI_CTRL_TF_CLR_POS); //发送FIFO清除使能配置 
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_RXFIFO_Clr()
* 功能说明: 接收FIFO寄存器清除    软件写1清除，硬件自动清0
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_RXFIFO_Clr(SPI_TypeDef * SPIx)
{
	SPIx->CTRL |= (0x01 << SPI_CTRL_RF_CLR_POS); //接收FIFO清除使能配置 
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_TXFIFO_Level()
* 功能说明: 获取发送FIFO水位状态
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_TXFIFO_Level(SPI_TypeDef * SPIx)
{
	uint8_t level = 0;
	
	level = ((SPIx->FIFOST >> SPI_FIFOST_TX_LEVEL_POS) & 0x07);
	
	if(level == 0)
	{
		if(SPIx->FIFOST & SPI_FIFOST_TXFIFO_FULL_MSK)
		{
			level = 8;
		}
	}
	
	return level;
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_RXFIFO_Level()
* 功能说明: 获取接收FIFO水位状态
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_RXFIFO_Level(SPI_TypeDef * SPIx)
{
	uint8_t level = 0;
	
	level = ((SPIx->FIFOST >> SPI_FIFOST_RX_LEVEL_POS) & 0x07);
	
	if(level == 0)
	{
		if(SPIx->FIFOST & SPI_FIFOST_RXFIFO_FULL_MSK)
		{
			level = 8;
		}
	}
	
	return level;
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_RXFIFO_Empty_State()
* 功能说明: 获取接收FIFO空标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非空  1  接收FIFO空
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_RXFIFO_Empty_State(SPI_TypeDef * SPIx)
{
	return (SPIx->FIFOST & SPI_FIFOST_RXFIFO_EMPTY_MSK);
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_RXFIFO_Full_State()
* 功能说明: 获取接收FIFO满标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非满  1  接收FIFO满
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_RXFIFO_Full_State(SPI_TypeDef * SPIx)
{
	return ((SPIx->FIFOST & SPI_FIFOST_RXFIFO_FULL_MSK) >> SPI_FIFOST_RXFIFO_FULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_RXFIFO_HalfFull_State()
* 功能说明: 获取接收FIFO半满标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非半满  1  接收FIFO半满
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_RXFIFO_HalfFull_State(SPI_TypeDef * SPIx)
{
	return ((SPIx->FIFOST & SPI_FIFOST_RXFIFO_HFULL_MSK) >> SPI_FIFOST_RXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_TXFIFO_Empty_State()
* 功能说明: 获取发送FIFO空标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非空  1  接收FIFO空
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_TXFIFO_Empty_State(SPI_TypeDef * SPIx)
{
	return (SPIx->FIFOST & SPI_FIFOST_TXFIFO_EMPTY_MSK);
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_TXFIFO_Full_State()
* 功能说明: 获取发送FIFO满标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非满  1  接收FIFO满
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_TXFIFO_Full_State(SPI_TypeDef * SPIx)
{
	return ((SPIx->FIFOST & SPI_FIFOST_TXFIFO_FULL_MSK) >> SPI_FIFOST_TXFIFO_FULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Get_TXFIFO_HalfFull_State()
* 功能说明: 获取发送FIFO半满标志      
* 输    入: SPI_TypeDef * SPIx      有效输入为SPI0  SPI1 	
* 输    出: 0  接收FIFO非半满  1  接收FIFO半满
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_Get_TXFIFO_HalfFull_State(SPI_TypeDef * SPIx)
{
	return ((SPIx->FIFOST & SPI_FIFOST_TXFIFO_HFULL_MSK) >> SPI_FIFOST_TXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOOvfEn()
* 功能说明:	SPI接收FIFO溢出中断使能 
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOOvfEn(SPI_TypeDef * SPIx)
{
	SPIx->IE |= (0x01 << SPI_IE_RXFIFO_OVF_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOOvfDis()
* 功能说明:	SPI接收FIFO溢出中断禁能
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOOvfDis(SPI_TypeDef * SPIx)
{
	SPIx->IE &= ~(0x01 << SPI_IE_RXFIFO_OVF_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOOvfClr()
* 功能说明:	SPI接收FIFO溢出中断标志清除
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOOvfClr(SPI_TypeDef * SPIx)
{
	SPIx->IF = (0x01 << SPI_IF_RXFIFO_OVF_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOOvfState()
* 功能说明:	SPI接收FIFO溢出中断状态
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 1  接收FIFO溢出  0  接收FIFO未溢出
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SPI_IntRXFIFOOvfState(SPI_TypeDef * SPIx)
{
	uint8_t State = 0;
	
	if(SPIx->IF & SPI_IF_RXFIFO_OVF_MSK)
	{
		State = 1;
	}
	
	return State;
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOFullEn()
* 功能说明:	SPI接收FIFO满中断使能 
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOFullEn(SPI_TypeDef * SPIx)
{
	SPIx->IE |= (0x01 << SPI_IE_RXFIFO_FULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOFullDis()
* 功能说明:	SPI接收FIFO满中断禁能
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOFullDis(SPI_TypeDef * SPIx)
{
	SPIx->IE &= ~(0x01 << SPI_IE_RXFIFO_FULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOFullClr()
* 功能说明:	SPI接收FIFO满中断标志清除
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOFullClr(SPI_TypeDef * SPIx)
{
	SPIx->IF = (0x01 << SPI_IF_RXFIFO_FULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOFullState()
* 功能说明:	SPI接收FIFO满中断状态
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 1  接收FIFO满  0  接收FIFO未满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SPI_IntRXFIFOFullState(SPI_TypeDef * SPIx)
{
	uint8_t State = 0;
	
	if(SPIx->IF & SPI_IF_RXFIFO_FULL_MSK)
	{
		State = 1;
	}
	
	return State;
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOHalfFullEn()
* 功能说明:	SPI接收FIFO半满中断使能 
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOHalfFullEn(SPI_TypeDef * SPIx)
{
	SPIx->IE |= (0x01 << SPI_IE_RXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOHalfFullDis()
* 功能说明:	SPI接收FIFO半满中断禁能
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOHalfFullDis(SPI_TypeDef * SPIx)
{
	SPIx->IE &= ~(0x01 << SPI_IE_RXFIFO_HFULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOHalfFullClr()
* 功能说明:	SPI接收FIFO半满中断标志清除
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntRXFIFOHalfFullClr(SPI_TypeDef * SPIx)
{
	SPIx->IF = (0x01 << SPI_IF_RXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntRXFIFOHalfFullState()
* 功能说明:	SPI接收FIFO半满中断状态
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 1  接收FIFO半满  0  接收FIFO未半满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SPI_IntRXFIFOHalfFullState(SPI_TypeDef * SPIx)
{
	uint8_t State = 0;
	
	if(SPIx->IF & SPI_IF_RXFIFO_HFULL_MSK)
	{
		State = 1;
	}
	
	return State;
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOEmptyEn()
* 功能说明:	SPI发送FIFO空中断使能 
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOEmptyEn(SPI_TypeDef * SPIx)
{
	SPIx->IE |= (0x01 << SPI_IE_TXFIFO_EMPTY_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOEmptyDis()
* 功能说明:	SPI发送FIFO空中断禁能
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOEmptyDis(SPI_TypeDef * SPIx)
{
	SPIx->IE &= ~(0x01 << SPI_IE_TXFIFO_EMPTY_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOEmptyClr()
* 功能说明:	SPI发送FIFO空中断标志清除
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOEmptyClr(SPI_TypeDef * SPIx)
{
	SPIx->IF = (0x01 << SPI_IF_TXFIFO_EMPTY_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOEmptyState()
* 功能说明:	SPI发送FIFO空中断状态
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 1  发送FIFO空   0  发送FIFO非空
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SPI_IntTXFIFOEmptyState(SPI_TypeDef * SPIx)
{
	uint8_t State = 0;
	
	if(SPIx->IF & SPI_IF_TXFIFO_EMPTY_MSK)
	{
		State = 1;
	}
	
	return State;
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOHalfFullEn()
* 功能说明:	SPI发送FIFO半满中断使能 
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOHalfFullEn(SPI_TypeDef * SPIx)
{
	SPIx->IE |= (0x01 << SPI_IE_TXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOHalfFullDis()
* 功能说明:	SPI发送FIFO半满中断禁能
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOHalfFullDis(SPI_TypeDef * SPIx)
{
	SPIx->IE &= ~(0x01 << SPI_IE_TXFIFO_HFULL_POS);
}


/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOHalfFullClr()
* 功能说明:	SPI发送FIFO半满中断标志清除
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_IntTXFIFOHalfFullClr(SPI_TypeDef * SPIx)
{
	SPIx->IF = (0x01 << SPI_IF_TXFIFO_HFULL_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_IntTXFIFOHalfFullState()
* 功能说明:	SPI发送FIFO半满中断状态
* 输    入: SPI_TypeDef * SPIx     SPI0   SPI1
* 输    出: 1  发送FIFO半满  0  发送FIFO未半满
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t SPI_IntTXFIFOHalfFullState(SPI_TypeDef * SPIx)
{
	uint8_t State = 0;
	
	if(SPIx->IF & SPI_IF_TXFIFO_HFULL_MSK)
	{
		State = 1;
	}
	
	return State;
}



