#include "DP32G030_cmp.h"


/****************************************************************************************************************************************** 
* 函数名称: CMP_Init()
* 功能说明:	比较器初始化
* 输    入: CMP_InitTypeDef* CMP_InitStruct  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_Init(CMP_InitTypeDef* CMP_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_CMP_ALL(CMP_InitStruct->CMP));         //检查输入的参数CMP是否合法  
  
	assert_param(IS_CMP_HYS(CMP_InitStruct->HYS));         //检查输入的参数HYS是否合法  
 
	assert_param(IS_CMP_FILTER(CMP_InitStruct->FILTER));   //检查输入的参数FILTER是否合法  

	assert_param(IS_CMP_IE(CMP_InitStruct->IE));           //检查输入的参数IE是否合法  
	 
	
	CMP_Close(CMP_InitStruct->CMP);
	
	temp = SYS->CMP_CFG;
	
	temp &= ~(0x03 << SYS_CMP_CFG_CMP_FILTER_POS);
	
	temp |= CMP_InitStruct->FILTER << SYS_CMP_CFG_CMP_FILTER_POS;
	
	if(CMP_InitStruct->CMP == CMP0)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP0_HYS_POS);	
		temp |= CMP_InitStruct->HYS << SYS_CMP_CFG_CMP0_HYS_POS;	
		
		if(CMP_InitStruct->IE == ENABLE)
		{
			temp |= 0x01<<SYS_CMP_CFG_CMP0_INTEN_POS;
		}
	}
	else if(CMP_InitStruct->CMP == CMP1)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP1_HYS_POS);	
		temp |= CMP_InitStruct->HYS << SYS_CMP_CFG_CMP1_HYS_POS;

		if(CMP_InitStruct->IE == ENABLE)
		{
			temp |= 0x01<<SYS_CMP_CFG_CMP1_INTEN_POS;
		}		
	}
	else if(CMP_InitStruct->CMP == CMP2)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP2_HYS_POS);	
		temp |= CMP_InitStruct->HYS << SYS_CMP_CFG_CMP2_HYS_POS;

		if(CMP_InitStruct->IE == ENABLE)
		{
			temp |= 0x01<<SYS_CMP_CFG_CMP2_INTEN_POS;
		}
	}
	
	SYS->CMP_CFG = temp;
	
	if(CMP_InitStruct->IE == ENABLE)
	{
		NVIC_EnableIRQ(CMP_IRQn);
	}	
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_Open()
* 功能说明:	比较器打开
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_Open(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_ALL(Cmp));    //检查输入的参数Cmp是否合法  
	
	if((Cmp & CMP0) == CMP0)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP0_EN_POS);
	}
	
	if((Cmp & CMP1) == CMP1)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP1_EN_POS);
	}
	
	if((Cmp & CMP2) == CMP2)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP2_EN_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_Close()
* 功能说明:	比较器关闭
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_Close(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_ALL(Cmp));    //检查输入的参数Cmp是否合法  
	
	if((Cmp & CMP0) == CMP0)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP0_EN_POS);
	}
	
	if((Cmp & CMP1) == CMP1)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP1_EN_POS);
	}
	
	if((Cmp & CMP2) == CMP2)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP2_EN_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_INTEn()
* 功能说明:	比较器中断使能
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_INTEn(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_ALL(Cmp));    //检查输入的参数Cmp是否合法  
	
	if((Cmp & CMP0) == CMP0)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP0_INTEN_POS);
	}
	
	if((Cmp & CMP1) == CMP1)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP1_INTEN_POS);
	}
	
	if((Cmp & CMP2) == CMP2)
	{
		SYS->CMP_CFG |= (0x01 << SYS_CMP_CFG_CMP2_INTEN_POS);
	}
	
	NVIC_EnableIRQ(CMP_IRQn);
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_INTDis()
* 功能说明:	比较器中断禁能
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_INTDis(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_ALL(Cmp));    //检查输入的参数Cmp是否合法  
	
	if((Cmp & CMP0) == CMP0)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP0_INTEN_POS);
	}
	
	if((Cmp & CMP1) == CMP1)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP1_INTEN_POS);
	}
	
	if((Cmp & CMP2) == CMP2)
	{
		SYS->CMP_CFG &= ~(0x01 << SYS_CMP_CFG_CMP2_INTEN_POS);
	}
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_SetHys()
* 功能说明:	比较器配置迟滞电压
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2  
            CMP_HYS_TypeDef Cmp_Hys  有效值有CMP_HYS_24MV  CMP_HYS_40MV  CMP_HYS_60MV  CMP_HYS_0MV
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_SetHys(CMP_TypeDef Cmp,CMP_HYS_TypeDef Cmp_Hys)
{
	uint32_t temp = 0;
	
	assert_param(IS_CMP_ALL(Cmp));        //检查输入的参数Cmp是否合法  
	
	assert_param(IS_CMP_HYS(Cmp_Hys));    //检查输入的参数Cmp_Hys是否合法  
	
	temp = SYS->CMP_CFG;
	
	if((Cmp & CMP0) == CMP0)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP0_HYS_POS);	
		temp |= Cmp_Hys << SYS_CMP_CFG_CMP0_HYS_POS;	
	}
	
	if((Cmp & CMP1) == CMP1)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP1_HYS_POS);
		temp |= Cmp_Hys << SYS_CMP_CFG_CMP1_HYS_POS;
	}
	
	if((Cmp & CMP2) == CMP2)
	{
		temp &= ~(0x03 << SYS_CMP_CFG_CMP2_HYS_POS);	
		temp |= Cmp_Hys << SYS_CMP_CFG_CMP2_HYS_POS;
	}
	
	SYS->CMP_CFG = temp;
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_SetFilter()
* 功能说明:	比较器配置滤波
* 输    入: CMP_FILTER_TypeDef Cmp_Filter       有效值有CMP_FILTER_0CLK  CMP_FILTER_2CLK  CMP_FILTER_4CLK  CMP_FILTER_8CLK 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_SetFilter(CMP_FILTER_TypeDef Cmp_Filter)
{
	uint32_t temp = 0;
	
	assert_param(IS_CMP_FILTER(Cmp_Filter));    //检查输入的参数Cmp_Filter是否合法  
	
	temp = SYS->CMP_CFG;
	
	temp &= ~(0x03 << SYS_CMP_CFG_CMP_FILTER_POS);
	
	temp |= Cmp_Filter << SYS_CMP_CFG_CMP_FILTER_POS;
	
	SYS->CMP_CFG = temp;
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_Get_Value_AfterFilter()
* 功能说明:	比较器获取滤波后的比较结果
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 0  P端<N端  1  P端>N端
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t CMP_Get_Value_AfterFilter(CMP_TypeDef Cmp)
{
	uint8_t value = 0;
	
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP0_FLITER_OUT_POS) & 0x01;
	}
	else if(Cmp == CMP1)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP1_FLITER_OUT_POS) & 0x01;
	}
	else if(Cmp == CMP2)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP2_FLITER_OUT_POS) & 0x01;
	}
	
	return value;
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_Get_Value_BeforeFilter()
* 功能说明:	比较器获取滤波前的比较结果
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 0  P端<N端  1  P端>N端
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t CMP_Get_Value_BeforeFilter(CMP_TypeDef Cmp)
{
	uint8_t value = 0;
	
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP0_OUT_POS) & 0x01;
	}
	else if(Cmp == CMP1)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP1_OUT_POS) & 0x01;
	}
	else if(Cmp == CMP2)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP2_OUT_POS) & 0x01;
	}
	
	return value;
}

/****************************************************************************************************************************************** 
* 函数名称: CMP_INTRiseStat()
* 功能说明:	比较器输出是否发生从0到1的变化
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 0  没有发生从0到1的变化   1  发生从0到1的变化
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t CMP_INTRiseStat(CMP_TypeDef Cmp)
{
	uint8_t value = 0;
	
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP0_RISEIF_POS) & 0x01;
	}
	else if(Cmp == CMP1)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP1_RISEIF_POS) & 0x01;
	}
	else if(Cmp == CMP2)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP2_RISEIF_POS) & 0x01;
	}
	
	return value;
}


/****************************************************************************************************************************************** 
* 函数名称: CMP_INTFallStat()
* 功能说明:	比较器输出是否发生从1到0的变化
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 0  没有发生从1到0的变化   1  发生从1到0的变化
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t CMP_INTFallStat(CMP_TypeDef Cmp)
{
	uint8_t value = 0;
	
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP0_FALLIF_POS) & 0x01;
	}
	else if(Cmp == CMP1)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP1_FALLIF_POS) & 0x01;
	}
	else if(Cmp == CMP2)
	{
		value = (SYS->CMP_ST >> SYS_CMP_ST_CMP2_FALLIF_POS) & 0x01;
	}
	
	return value;
}


/****************************************************************************************************************************************** 
* 函数名称: CMP_INTRiseClr()
* 功能说明:	比较器输出发生从0到1的变化中断标志清除
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_INTRiseClr(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP0_RISEIF_POS;
	}
	else if(Cmp == CMP1)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP1_RISEIF_POS;
	}
	else if(Cmp == CMP2)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP2_RISEIF_POS;
	}
}


/****************************************************************************************************************************************** 
* 函数名称: CMP_INTFallClr()
* 功能说明:	比较器输出发生从1到0的变化中断标志清除
* 输    入: CMP_TypeDef Cmp       有效值有CMP0  CMP1  CMP2 
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void CMP_INTFallClr(CMP_TypeDef Cmp)
{
	assert_param(IS_CMP_TYPE(Cmp));        //检查输入的参数Cmp是否合法  
	
	if(Cmp == CMP0)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP0_FALLIF_POS;
	}
	else if(Cmp == CMP1)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP1_FALLIF_POS;
	}
	else if(Cmp == CMP2)
	{
		SYS->CMP_ST = 0x01 << SYS_CMP_ST_CMP2_FALLIF_POS;
	}
}

