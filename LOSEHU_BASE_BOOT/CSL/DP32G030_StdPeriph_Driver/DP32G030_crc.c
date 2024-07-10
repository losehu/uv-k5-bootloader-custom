#include "DP32G030_crc.h"

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Init
* 功能说明:	初始化CRC
* 输    入: CRC_InitTypeDef *CRC_InitStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Init(CRC_InitTypeDef *CRC_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_CRC_SEL(CRC_InitStruct->CrcSel));                  //检查输入的参数CrcSel是否合法     
	
	assert_param(IS_CRC_DATAWIDTH(CRC_InitStruct->DataWidth));         //检查输入的参数DataWidth是否合法     
	
	assert_param(IS_CRC_INPUT_INV(CRC_InitStruct->InputInv));          //检查输入的参数InputInv是否合法     
	
	assert_param(IS_CRC_INPUT_REV(CRC_InitStruct->InputRev));          //检查输入的参数InputRev是否合法   
	
	assert_param(IS_CRC_OUTPUT_INV(CRC_InitStruct->OutputInv));        //检查输入的参数OutputInv是否合法     
	
	assert_param(IS_CRC_OUTPUT_REV(CRC_InitStruct->OutputRev));        //检查输入的参数OutputRev是否合法     
	
	
	SYS->CLKEN |= (0x01<<SYS_CLKEN_CRC_POS);                           //开启CRC时钟
	
	CRC->CR &= ~(0x01<<CRC_CR_EN_POS);                                 //CRC禁能
	
	temp = 0x00;	                                                   //CRC配置寄存器清0
	
	temp |= (CRC_InitStruct->CrcSel << CRC_CR_SEL_POS);                //配置CRC算法
	
	temp |= (CRC_InitStruct->DataWidth << CRC_CR_DATA_WIDTH_POS);      //配置CRC数据位宽
	
	temp |= (CRC_InitStruct->InputInv << CRC_CR_INPUT_INV_POS);        //配置CRC输入数据是否翻转
	
	temp |= (CRC_InitStruct->InputRev << CRC_CR_INPUT_REV_POS);	       //配置输入数据是否取反	
	
	temp |= (CRC_InitStruct->OutputInv << CRC_CR_OUTPUT_INV_POS);      //配置CRC输出数据是否翻转
	
	temp |= (CRC_InitStruct->OutputRev << CRC_CR_OUTPUT_REV_POS);      //配置输出数据是否取反	
	
	CRC->CR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Start
* 功能说明:	启动CRC
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Start(void)
{
	CRC->CR |= (0x01<<CRC_CR_EN_POS);           //CRC使能
}	

/****************************************************************************************************************************************** 
* 函数名称:	CRC_stop
* 功能说明:	关闭CRC
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_stop(void)
{
	CRC->CR &= ~(0x01<<CRC_CR_EN_POS);         //CRC禁能
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Sel
* 功能说明:	配置CRC算法
* 输    入: CrcSel_TypeDef Crc_Sel
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Sel(CrcSel_TypeDef Crc_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_CRC_SEL(Crc_Sel));                  //检查输入的参数Crc_Sel是否合法     
	
	temp = CRC->CR;
	
	temp &= ~(0x03 << CRC_CR_SEL_POS);
	temp |= (Crc_Sel << CRC_CR_SEL_POS);
	
	CRC->CR = temp;                                     //配置CRC算法
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Data_Width
* 功能说明:	配置CRC数据位宽
* 输    入: DataWidth_TypeDef DataWidth
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Data_Width(DataWidth_TypeDef DataWidth)
{
	uint32_t temp = 0;
	
	assert_param(IS_CRC_DATAWIDTH(DataWidth));         //检查输入的参数DataWidth是否合法     
	
	temp = CRC->CR;
	
	temp &= ~(0x03 << CRC_CR_DATA_WIDTH_POS);
	temp |= (DataWidth << CRC_CR_DATA_WIDTH_POS);  
	
	CRC->CR = temp;                                    //配置CRC数据位宽
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Input_Inv
* 功能说明:	配置CRC输入数据是否翻转
* 输    入: InputInv_TypeDef InputInv
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Input_Inv(InputInv_TypeDef InputInv)
{
	uint32_t temp = 0;
	
	assert_param(IS_CRC_INPUT_INV(InputInv));        //检查输入的参数InputInv是否合法     
	
	temp = CRC->CR;
	
	temp &= ~(0x03 << CRC_CR_INPUT_INV_POS);
	temp |= (InputInv << CRC_CR_INPUT_INV_POS);
	
	CRC->CR = temp;                                  //配置CRC输入数据是否翻转
}


/****************************************************************************************************************************************** 
* 函数名称:	CRC_Input_Rev
* 功能说明:	配置CRC输入数据是否取反
* 输    入: InputRev_TypeDef InputRev
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Input_Rev(InputRev_TypeDef InputRev)
{
	assert_param(IS_CRC_INPUT_REV(InputRev));        //检查输入的参数InputRev是否合法   
	
	if(InputRev == DISABLE)                          //配置CRC输入数据是否取反
	{
		CRC->CR &= ~(0x01 << CRC_CR_INPUT_REV_POS);
	}
	else
	{
		CRC->CR |= (0x01 << CRC_CR_INPUT_REV_POS);   
	}
}


/****************************************************************************************************************************************** 
* 函数名称:	CRC_Output_Inv
* 功能说明:	配置CRC输出数据是否翻转
* 输    入: OutputInv_TypeDef OutputInv
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Output_Inv(OutputInv_TypeDef OutputInv)
{
	uint32_t temp = 0;
	
	assert_param(IS_CRC_OUTPUT_INV(OutputInv));        //检查输入的参数OutputInv是否合法     
	
	temp = CRC->CR;
	
	temp &= ~(0x03 << CRC_CR_OUTPUT_INV_POS);
	temp |= (OutputInv << CRC_CR_OUTPUT_INV_POS);   
	
	CRC->CR = temp;                                    //配置CRC输出数据是否翻转
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_Output_Rev
* 功能说明:	配置CRC输出数据是否取反
* 输    入: OutputRev_TypeDef OutputRev
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_Output_Rev(OutputRev_TypeDef OutputRev)
{
	assert_param(IS_CRC_OUTPUT_REV(OutputRev));        //检查输入的参数OutputRev是否合法     
	
	if(OutputRev == DISABLE)                           //配置CRC输出数据是否取反
	{
		CRC->CR &= ~(0x01 << CRC_CR_OUTPUT_REV_POS);
	}
	else
	{
		CRC->CR |= (0x01 << CRC_CR_OUTPUT_REV_POS);
	}   
}


/****************************************************************************************************************************************** 
* 函数名称:	CRC_WriteIV
* 功能说明:	写入CRC初始值
* 输    入: uint32_t data, CRC初始值数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_WriteIV(uint32_t data)
{
	CRC->IV = data;
}	

/****************************************************************************************************************************************** 
* 函数名称:	CRC_WriteData
* 功能说明:	写入CRC校验数据
* 输    入: uint32_t data, CRC校验数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CRC_WriteData(uint32_t data)
{
	CRC->DATAIN = data;
}

/****************************************************************************************************************************************** 
* 函数名称:	CRC_ReadData
* 功能说明:	读取CRC校验值
* 输    入: 无
* 输    出: CRC校验值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t CRC_ReadData(void)
{
	return CRC->DATAOUT;
}





