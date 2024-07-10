#include "DP32G030_aes.h"


/****************************************************************************************************************************************** 
* 函数名称: AES_Init()
* 功能说明:	AES初始化，包含链接方式 数据类型  模式
* 输    入: AES_InitTypeDef * AES_InitStruct   
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Init(AES_InitTypeDef * AES_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_AES_CON_MODE(AES_InitStruct->AESConnectMode));      //检查输入的参数AESConnectMode是否合法    
	
	assert_param(IS_AES_MODE(AES_InitStruct->AESMode));                 //检查输入的参数AESMode是否合法  
	
	assert_param(IS_AES_DATATYPE(AES_InitStruct->AESDataType));         //检查输入的参数AESDataType是否合法  
	
	
	SYS->CLKEN |= 0x01 << SYS_CLKEN_AES_POS;                //开启AES时钟
	
	AES128->CR &= ~(0x01 << AES128_CR_EN_POS);              //AES禁能 进行配置寄存器
	
	temp = AES128->CR;
	
	temp &= ~(0x03 << AES128_CR_CHMODE_POS);          //配置AES的链接方式
	temp |= (AES_InitStruct->AESConnectMode << AES128_CR_CHMODE_POS);
	
	temp &= ~(0x03 << AES128_CR_MODE_POS);            //配置AES的模式
	temp |= (AES_InitStruct->AESMode << AES128_CR_MODE_POS);
	
	temp &= ~(0x03 << AES128_CR_DATATYPE_POS);        //配置AES的数据类型
	temp |= (AES_InitStruct->AESDataType << AES128_CR_DATATYPE_POS); 
	
	AES128->CR = temp;
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Set_Key()
* 功能说明:	AES配置KEY
* 输    入: uint32_t *key    128bit  KEY 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Set_Key(uint32_t *key)
{
	AES128->CR &= ~(0x01 << AES128_CR_EN_POS);          //AES禁能 进行配置寄存器
    
	AES128->KEYR3 = key[0];                             //配置KEY
	AES128->KEYR2 = key[1];
	AES128->KEYR1 = key[2];
	AES128->KEYR0 = key[3];
	
	AES128->CR |= 0x01 << AES128_CR_EN_POS;             //AES使能
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Set_Key_IV()
* 功能说明:	AES配置KEY IV
* 输    入: uint32_t *key    128bit  KEY 
            uint32_t *iv     128bit  IV
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Set_Key_IV(uint32_t *key,uint32_t *iv)
{
	AES128->CR &= ~(0x01 << AES128_CR_EN_POS);          //AES禁能 进行配置寄存器
    
	AES128->KEYR3 = key[0];                             //配置KEY
	AES128->KEYR2 = key[1];
	AES128->KEYR1 = key[2];
	AES128->KEYR0 = key[3];
	
	AES128->IVR3  = iv[0];                              //配置IV
	AES128->IVR2  = iv[1];
	AES128->IVR1  = iv[2];
	AES128->IVR0  = iv[3];
	
	AES128->CR |= 0x01 << AES128_CR_EN_POS;             //AES使能
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Get_KeyDerived()
* 功能说明:	AES密钥派生
* 输    入: uint32_t *key    128bit  KEY 
            uint32_t *key_derived     128bit  派生密钥
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Get_KeyDerived(uint32_t *key_derived)
{
	while(!(AES128->SR & AES128_SR_CCF_MSK)){};         //等待AES计算完成
		
	key_derived[0] = AES128->KEYR3;                     //取出派生后的密钥
	key_derived[1] = AES128->KEYR2;
	key_derived[2] = AES128->KEYR1;
	key_derived[3] = AES128->KEYR0;	

	AES128->CR |= 0x01 << AES128_CR_CCFC_POS;           //清除AES计算完成标志
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Data_WriteRead()
* 功能说明:	AES数据写入读出
* 输    入: uint32_t *din    128bit  输入数据 
            uint32_t*dout    128bit  输出数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Data_WriteRead(uint32_t *din,uint32_t*dout)
{
	AES128->DINR = din[0];                              //写入数据                
	AES128->DINR = din[1]; 
	AES128->DINR = din[2]; 
	AES128->DINR = din[3]; 
	
	while(!(AES128->SR & AES128_SR_CCF_MSK)){};         //等待AES计算完成
		
    dout[0] = AES128->DOUTR;                            //读出数据
    dout[1] = AES128->DOUTR; 
    dout[2] = AES128->DOUTR; 
    dout[3] = AES128->DOUTR; 
	  
	AES128->CR |= 0x01 << AES128_CR_CCFC_POS;           //清除AES计算完成标志
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Data_Write()
* 功能说明:	AES数据写入
* 输    入: uint32_t *din    128bit  输入数据 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Data_Write(uint32_t *din)
{
	AES128->DINR = din[0];                              //写入数据    
	AES128->DINR = din[1]; 
	AES128->DINR = din[2]; 
	AES128->DINR = din[3]; 
}

/****************************************************************************************************************************************** 
* 函数名称: AES_Data_Read()
* 功能说明:	AES数据读出
* 输    入: uint32_t*dout    128bit  输出数据     
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void AES_Data_Read(uint32_t*dout)
{
    dout[0] = AES128->DOUTR;                            //读出数据
    dout[1] = AES128->DOUTR; 
    dout[2] = AES128->DOUTR; 
    dout[3] = AES128->DOUTR; 
	  
	AES128->CR |= 0x01 << AES128_CR_CCFC_POS;           //清除AES计算完成标志
}



