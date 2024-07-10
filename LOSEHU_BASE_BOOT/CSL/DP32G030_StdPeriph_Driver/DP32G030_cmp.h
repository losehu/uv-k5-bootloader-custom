#ifndef __DP32G030_CMP_H__
#define __DP32G030_CMP_H__          

#include "DP32G030.h"

typedef enum
{ 
	CMP0 =  0x01,                     //比较器0
	CMP1 =  0x02,                     //比较器1
	CMP2 =  0x04,                     //比较器2
} CMP_TypeDef;

typedef enum
{ 
	CMP_HYS_24MV = 0x00,              //比较器迟滞电压24毫伏          
	CMP_HYS_40MV = 0x01,              //比较器迟滞电压40毫伏    
	CMP_HYS_60MV = 0x02,              //比较器迟滞电压60毫伏    
	CMP_HYS_0MV  = 0x03,              //比较器迟滞电压0毫伏    
} CMP_HYS_TypeDef;

typedef enum
{ 
	CMP_FILTER_0CLK = 0x00,           //比较器输出不滤波 
	CMP_FILTER_2CLK = 0x01,           //比较器输出经过2个系统时钟周期的滤波
	CMP_FILTER_4CLK = 0x02,           //比较器输出经过4个系统时钟周期的滤波
	CMP_FILTER_8CLK = 0x03,           //比较器输出经过8个系统时钟周期的滤波
} CMP_FILTER_TypeDef;


typedef struct
{
	CMP_TypeDef          CMP;         //比较器选择       
    CMP_HYS_TypeDef      HYS;         //迟滞                              
    CMP_FILTER_TypeDef   FILTER;      //滤波控制
	FunctionalState      IE;          //中断使能
} CMP_InitTypeDef;




//断言  CMP
#define IS_CMP_ALL(CMP)        (((CMP) >= 0x01) && ((CMP) <= 0x07))

//断言  CMP_TYPE
#define IS_CMP_TYPE(CMP)       (((CMP) == CMP0) || ((CMP) == CMP1) || ((CMP) == CMP2))

//断言  CMP_HYS
#define IS_CMP_HYS(HYS)        ((HYS) == CMP_HYS_24MV || (HYS) == CMP_HYS_40MV || (HYS) == CMP_HYS_60MV || (HYS) == CMP_HYS_0MV)

//断言  CMP_FILTER
#define IS_CMP_FILTER(FILTER)  ((FILTER) == CMP_FILTER_0CLK || (FILTER) == CMP_FILTER_2CLK || (FILTER) == CMP_FILTER_4CLK || (FILTER) == CMP_FILTER_8CLK)

//断言  CMP中断
#define IS_CMP_IE(IE)          (((IE) == ENABLE) || ((IE) == DISABLE))


void CMP_Init(CMP_InitTypeDef* CMP_InitStruct);               //比较器初始化

void CMP_Open(CMP_TypeDef Cmp);                               //比较器打开

void CMP_Close(CMP_TypeDef Cmp);                              //比较器关闭

void CMP_INTEn(CMP_TypeDef Cmp);                              //比较器中断使能
 
void CMP_INTDis(CMP_TypeDef Cmp);                             //比较器中断禁能

void CMP_SetHys(CMP_TypeDef Cmp,CMP_HYS_TypeDef Cmp_Hys);     //比较器配置迟滞电压

void CMP_SetFilter(CMP_FILTER_TypeDef Cmp_Filter);            //比较器配置滤波

uint8_t CMP_Get_Value_AfterFilter(CMP_TypeDef Cmp);           //比较器获取滤波后的比较结果

uint8_t CMP_Get_Value_BeforeFilter(CMP_TypeDef Cmp);          //比较器获取滤波前的比较结果

uint8_t CMP_INTRiseStat(CMP_TypeDef Cmp);                     //比较器输出是否发生从0到1的变化

uint8_t CMP_INTFallStat(CMP_TypeDef Cmp);                     //比较器输出是否发生从1到0的变化

void CMP_INTRiseClr(CMP_TypeDef Cmp);                         //比较器输出发生从0到1的变化中断标志清除

void CMP_INTFallClr(CMP_TypeDef Cmp);                         //比较器输出发生从1到0的变化中断标志清除


#endif //__DP32G030_CMP_H__
