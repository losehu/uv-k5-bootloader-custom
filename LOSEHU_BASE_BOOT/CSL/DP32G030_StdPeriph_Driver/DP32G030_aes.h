#ifndef __DP32G030_AES_H__
#define __DP32G030_AES_H__

#include "DP32G030.h"

typedef enum
{ 
	ECB =  0x00,             //ECB模式                       
	CBC =  0x01,             //CBC模式
    CTR =  0x02,             //CTR模式
} AESConnectMode_TypeDef;

typedef enum
{ 
	Encrypt    =  0x00,      //加密     
	Key        =  0x01,      //密钥派生
    Decrypt    =  0x02,      //解密
	KeyDecrypt =  0x03       //密钥派生加解密
} AESMode_TypeDef;

typedef enum
{ 
	BIT32    =  0x00,        //32位数据不交换    
	BIT16    =  0x01,        //16位数据交换       
    BIT08    =  0x02,        //8位数据交换
	BIT01    =  0x03         //1位数据交换
} AESDataType_TypeDef;

typedef struct {
	
	AESConnectMode_TypeDef  AESConnectMode;	    //链接模式		
	AESMode_TypeDef         AESMode;	        //模式
	AESDataType_TypeDef     AESDataType;	    //数据类型
} AES_InitTypeDef;

//断言AES链接模式
#define IS_AES_CON_MODE(AES_CON_MODE)    (((AES_CON_MODE) == ECB) || ((AES_CON_MODE) == CBC) || ((AES_CON_MODE) == CTR))

//断言AES模式
#define IS_AES_MODE(AES_MODE)            (((AES_MODE) == Encrypt) || ((AES_MODE) == Key) || ((AES_MODE) == Decrypt) || ((AES_MODE) == KeyDecrypt))        

//断言AES数据类型
#define IS_AES_DATATYPE(AES_DATATYPE)    (((AES_DATATYPE) == BIT32) || ((AES_DATATYPE) == BIT16) || ((AES_DATATYPE) == BIT08) || ((AES_DATATYPE) == BIT01))


void AES_Init(AES_InitTypeDef * AES_InitStruct);         //AES初始化

void AES_Set_Key(uint32_t *key);                         //AES设置KEY
void AES_Set_Key_IV(uint32_t *key,uint32_t *iv);         //AES设置KEY和IV

void AES_Get_KeyDerived(uint32_t *key_derived);          //AES获取派生密钥

void AES_Data_WriteRead(uint32_t *din,uint32_t*dout);    //AES数据写入读出
void AES_Data_Write(uint32_t *din);                      //AES数据写入
void AES_Data_Read(uint32_t*dout);                       //AES数据读出

#endif //__DP32G030_AES_H__
