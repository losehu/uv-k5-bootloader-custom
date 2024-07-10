#ifndef __DP32G030_CRC_H__
#define __DP32G030_CRC_H__

#include "DP32G030.h"

typedef enum
{ 
	CRC_SEL_CCITT         =  0x00,  // 算法选择CCITT
	CRC_SEL_8             =  0x01,  // 算法选择CRC8
	CRC_SEL_16            =  0x02,  // 算法选择CRC16
	CRC_SEL_32            =  0x03,  // 算法选择CRC32
} CrcSel_TypeDef;

typedef enum
{ 
	DATA_WIDTH_32         =  0x00,  // 输入数据位宽为32bit
	DATA_WIDTH_16         =  0x01,  // 输入数据位宽为16bit
	DATA_WIDTH_8          =  0x02,  // 输入数据位宽为8bit
} DataWidth_TypeDef;

typedef enum
{ 
	INPUT_INV_NORMAL      =  0x00,  // 输入数据不翻转
	INPUT_INV_BIT         =  0x01,  // 输入数据按bit翻转
	INPUT_INV_BIT_BYTE    =  0x02,  // 输入数据按byte和bit翻转
	INPUT_INV_BYTE        =  0x03,  // 输入数据按byte翻转
} InputInv_TypeDef;

typedef enum
{ 
	INPUT_REV_DISABLE     =  0x00,  // 输入数据不取反
	INPUT_REV_ENABLE      =  0x01,  // 输入数据取反
} InputRev_TypeDef;

typedef enum
{ 
	OUTPUT_INV_NORMAL     =  0x00,  // 输出数据不翻转
	OUTPUT_INV_BIT        =  0x01,  // 输出数据按bit翻转
	OUTPUT_INV_BIT_BYTE   =  0x02,  // 输出数据按byte和bit翻转
	OUTPUT_INV_BYTE       =  0x03,  // 输出数据按byte翻转
} OutputInv_TypeDef;

typedef enum
{ 
	OUTPUT_REV_DISABLE    =  0x00,  // 输出数据不取反
	OUTPUT_REV_ENABLE     =  0x01,  // 输出数据取反
} OutputRev_TypeDef;


typedef struct
{                                               	
	CrcSel_TypeDef    CrcSel;     // CRC算法多项式选择
	
	DataWidth_TypeDef DataWidth;  // CRC输入数据宽度
	
	InputInv_TypeDef  InputInv;   // CRC输入数据翻转模式选择
	
	InputRev_TypeDef  InputRev;   // CRC输入数据取反使能
	
	OutputInv_TypeDef OutputInv;  // CRC输出数据翻转模式选择
	
	OutputRev_TypeDef OutputRev;  // CRC输出数据取反使能
} CRC_InitTypeDef;


//断言  CRC算法多项式  
#define IS_CRC_SEL(CRC_SEL) (((CRC_SEL) == CRC_SEL_CCITT) || ((CRC_SEL) == CRC_SEL_8) || ((CRC_SEL) == CRC_SEL_16) || ((CRC_SEL) == CRC_SEL_32))

//断言  CRC输入数据宽度
#define IS_CRC_DATAWIDTH(CRC_DATAWIDTH) (((CRC_DATAWIDTH) == DATA_WIDTH_32) || ((CRC_DATAWIDTH) == DATA_WIDTH_16) || ((CRC_DATAWIDTH) == DATA_WIDTH_8))

//断言  CRC输入数据翻转模式选择
#define IS_CRC_INPUT_INV(CRC_INPUT_INV) (((CRC_INPUT_INV) == INPUT_INV_NORMAL) || ((CRC_INPUT_INV) == INPUT_INV_BIT) || ((CRC_INPUT_INV) == INPUT_INV_BIT_BYTE) || ((CRC_INPUT_INV) == INPUT_INV_BYTE))

//断言  CRC输入数据取反使能 
#define IS_CRC_INPUT_REV(CRC_INPUT_REV) (((CRC_INPUT_REV) == INPUT_REV_DISABLE) || ((CRC_INPUT_REV) == INPUT_REV_ENABLE))

//断言  CRC输出数据翻转模式选择
#define IS_CRC_OUTPUT_INV(CRC_OUTPUT_INV) (((CRC_OUTPUT_INV) == OUTPUT_INV_NORMAL) || ((CRC_OUTPUT_INV) == OUTPUT_INV_BIT) || ((CRC_OUTPUT_INV) == OUTPUT_INV_BIT_BYTE) || ((CRC_OUTPUT_INV) == OUTPUT_INV_BYTE))

//断言  CRC输出数据取反使能 
#define IS_CRC_OUTPUT_REV(CRC_OUTPUT_REV) (((CRC_OUTPUT_REV) == OUTPUT_REV_DISABLE) || ((CRC_OUTPUT_REV) == OUTPUT_REV_ENABLE))



void CRC_Init(CRC_InitTypeDef *CRC_InitStruct);               //初始化CRC

void CRC_Start(void);                                         //启动CRC

void CRC_Stop(void);                                          //关闭CRC

void CRC_Sel(CrcSel_TypeDef Crc_Sel);                         //配置CRC算法

void CRC_Data_Width(DataWidth_TypeDef DataWidth);             //配置CRC数据位宽

void CRC_Input_Inv(InputInv_TypeDef InputInv);                //配置CRC输入数据是否翻转

void CRC_Input_Rev(InputRev_TypeDef InputRev);                //配置CRC输入数据是否取反

void CRC_Output_Inv(OutputInv_TypeDef OutputInv);             //配置CRC输出数据是否翻转

void CRC_Output_Rev(OutputRev_TypeDef OutputRev);             //配置CRC输出数据是否取反

void CRC_WriteIV(uint32_t data);                              //写入CRC初始值

void CRC_WriteData(uint32_t data);                            //写入CRC校验数据

uint32_t CRC_ReadData(void);                                  //读取CRC校验值
 

#endif //__DP32G030_CRC_H__
