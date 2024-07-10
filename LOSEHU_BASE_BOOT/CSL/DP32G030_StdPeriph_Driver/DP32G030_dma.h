#ifndef __DP32G030_DMA_H__
#define	__DP32G030_DMA_H__

#include "DP32G030.h"


typedef enum
{ 
	DMA_CH0 =  0x00,                //DMA通道0
	DMA_CH1 =  0x01,                //DMA通道1 
	DMA_CH2 =  0x02,                //DMA通道2 
	DMA_CH3 =  0x03,                //DMA通道3
} CH_TypeDef;

typedef enum
{ 
	PRI_LOW     =  0x00,            //低优先级
	PRI_MID     =  0x01,            //中优先级
	PRI_HIGH    =  0x02,            //高优先级
	PRI_HIGHEST =  0x03,            //最高优先级 
} PRI_TypeDef;


typedef enum
{ 
	ADDR_INC_DIS =  0x00,           //DMA通道地址不变
	ADDR_INC_EN  =  0x01,           //DMA通道地址递增
} ADDR_MODE_TypeDef;


typedef enum
{ 
	SIZE_8BITS   =  0x00,           //DMA通道总线传输宽度为8bits
	SIZE_16BITS  =  0x01,           //DMA通道总线传输宽度为16bits
	SIZE_32BITS  =  0x02,           //DMA通道总线传输宽度为32bits
} ADDR_SIZE_TypeDef;


typedef enum
{ 
	CH0_MS_RAM        =  0x00,      //DMA通道0源地址侧  RAM
	CH0_MS_UART0_RX   =  0x01,      //DMA通道0源地址侧  串口0的接收
	CH0_MS_UART1_RX   =  0x02,      //DMA通道0源地址侧  串口0的接收
	CH0_MS_SARADC     =  0x04,      //DMA通道0源地址侧  SARADC的接收
	CH0_MS_TIMPLUS0_L =  0x05,      //DMA通道0源地址侧  TIMPLUS0_LOW的输入捕获值
	CH0_MS_TIMPLUS1_L =  0x06,      //DMA通道0源地址侧  TIMPLUS1_LOW的输入捕获值
} CH0_MS_TypeDef;


typedef enum
{ 
	CH0_MD_RAM        =  0x00,      //DMA通道0目的地址侧  RAM
} CH0_MD_TypeDef;


typedef enum
{ 
	CH1_MS_RAM        =  0x00,      //DMA通道1源地址侧  RAM
	CH1_MS_UART1_RX   =  0x01,      //DMA通道1源地址侧  串口1的接收
	CH1_MS_UART2_RX   =  0x02,      //DMA通道1源地址侧  串口2的接收
	CH1_MS_SARADC     =  0x04,      //DMA通道1源地址侧  SARADC的接收
	CH1_MS_TIMPLUS0_H =  0x05,      //DMA通道1源地址侧  TIMPLUS0_HIGH的输入捕获值
	CH1_MS_TIMPLUS1_H =  0x06,      //DMA通道1源地址侧  TIMPLUS1_HIGH的输入捕获值
} CH1_MS_TypeDef;

typedef enum
{ 
	CH1_MD_RAM        =  0x00,      //DMA通道1目的地址侧  RAM
} CH1_MD_TypeDef;


typedef enum
{ 
	CH2_MS_RAM        =  0x00,      //DMA通道2源地址侧  RAM
	CH2_MS_UART2_RX   =  0x01,      //DMA通道2源地址侧  串口2的接收
	CH2_MS_UART0_RX   =  0x02,      //DMA通道0源地址侧  串口0的接收
	CH2_MS_SARADC     =  0x04,      //DMA通道2源地址侧  SARADC的接收
	CH2_MS_TIMPLUS1_L =  0x05,      //DMA通道2源地址侧  TIMPLUS1_LOW的输入捕获值
	CH2_MS_TIMPLUS0_L =  0x06,      //DMA通道2源地址侧  TIMPLUS0_LOW的输入捕获值
} CH2_MS_TypeDef;

typedef enum
{ 
	CH2_MD_RAM        =  0x00,      //DMA通道2目的地址侧  RAM
} CH2_MD_TypeDef;


typedef enum
{ 
	CH3_MS_RAM        =  0x00,      //DMA通道0源地址侧  RAM
	CH3_MS_UART0_RX   =  0x01,      //DMA通道0源地址侧  串口0的接收
	CH3_MS_UART1_RX   =  0x02,      //DMA通道0源地址侧  串口0的接收
	CH3_MS_SARADC     =  0x04,      //DMA通道0源地址侧  SARADC的接收
	CH3_MS_TIMPLUS1_H =  0x05,      //DMA通道0源地址侧  TIMPLUS1_HIGH的输入捕获值
	CH3_MS_TIMPLUS0_H =  0x06,      //DMA通道0源地址侧  TIMPLUS0_HIGH的输入捕获值
} CH3_MS_TypeDef;


typedef enum
{ 
	CH3_MD_RAM        =  0x00,      //DMA通道3目的地址侧  RAM
} CH3_MD_TypeDef;



typedef struct {
	uint16_t          Lenth;             //传输的数据长度  单位由SIZE决定
	
	FunctionalState   Loop;              //循环方式   0  单次  1  循环
	
	PRI_TypeDef       Priority;          //通道优先级   00 低  01  中  10 高  11 最高 
	
	uint32_t          MS_Addr;           //MS侧的地址
	
	ADDR_MODE_TypeDef MS_AddrMode;       //MS侧的地址变化选择  0  地址不变  1  地址递增
	
	ADDR_SIZE_TypeDef MS_AddrSize;       //MS侧的总线传输宽度  00  8bits  01 16bits   10 32bits
	
	uint8_t           MS_Sel;            //MS侧的外设选择
	
	uint32_t          MD_Addr;           //MD侧的地址
	
	ADDR_MODE_TypeDef MD_AddrMode;       //MD侧的地址变化选择  0  地址不变  1  地址递增
	
	ADDR_SIZE_TypeDef MD_AddrSize;       //MD侧的总线传输宽度  00  8bits  01 16bits   10 32bits
	
	uint8_t           MD_Sel;            //MD侧的外设选择
	
	FunctionalState   Complete_IE;       //传输完成中断使能
	
	FunctionalState   HalfComplete_IE;   //传输一半完成中断使能	
} DMA_ChannelInitTypeDef;


//断言DMA通道
#define IS_DMA_CH(DMA_CH)    (((DMA_CH) == DMA_CH0) || ((DMA_CH) == DMA_CH1) || ((DMA_CH) == DMA_CH2) || ((DMA_CH) == DMA_CH3))  

//断言DMA通道优先级 
#define IS_DMA_PRI(DMA_PRI)  (((DMA_PRI) == PRI_LOW) || ((DMA_PRI) == PRI_MID) || ((DMA_PRI) == PRI_HIGH) || ((DMA_PRI) == PRI_HIGHEST))  

//断言DMA地址变化选择
#define IS_DMA_ADDRMODE(DMA_ADDRMODE)    (((DMA_ADDRMODE) == ADDR_INC_DIS) || ((DMA_ADDRMODE) == ADDR_INC_EN))  

//断言DMA总线传输宽度
#define IS_DMA_ADDRSIZE(DMA_ADDRSIZE)    (((DMA_ADDRSIZE) == SIZE_8BITS) || ((DMA_ADDRSIZE) == SIZE_16BITS) || ((DMA_ADDRSIZE) == SIZE_32BITS)) 




void DMA_Channel_Init(CH_TypeDef  CHx,DMA_ChannelInitTypeDef  * DMA_ChannelInitStruct);   //DMA初始化

void DMA_Open(void);                                                   //DMA打开 

void DMA_Close(void);                                                  //DMA关闭

void DMA_CH_En(CH_TypeDef  CHx);                                       //DMA通道使能

void DMA_CH_Dis(CH_TypeDef  CHx);                                      //DMA通道禁能

void DMA_CH_Set_Lenth(CH_TypeDef  CHx,uint16_t Lenth);                 //DMA通道传输数据数量配置

void DMA_CH_Loop_En(CH_TypeDef  CHx);                                  //DMA通道循环方式使能

void DMA_CH_Loop_Dis(CH_TypeDef  CHx);                                 //DMA通道循环方式禁能

void DMA_CH_Set_Priority(CH_TypeDef  CHx,PRI_TypeDef Priority);        //DMA通道优先级配置

void DMA_CH_SwReq_En(CH_TypeDef  CHx);                                 //DMA通道软件方式请求发送 

void DMA_CH_MS_AddrMode(CH_TypeDef  CHx,ADDR_MODE_TypeDef AddrMode);   //DMA通道MS侧地址变化方式选择

void DMA_CH_MS_Size(CH_TypeDef  CHx,ADDR_SIZE_TypeDef Size);           //DMA通道MS侧总线传输宽度

void DMA_CH0_MS_Sel(CH0_MS_TypeDef  Sel);                              //DMA通道0的MS侧外设选择

void DMA_CH1_MS_Sel(CH1_MS_TypeDef  Sel);                              //DMA通道1的MS侧外设选择

void DMA_CH2_MS_Sel(CH2_MS_TypeDef  Sel);                              //DMA通道2的MS侧外设选择

void DMA_CH3_MS_Sel(CH3_MS_TypeDef  Sel);                              //DMA通道3的MS侧外设选择

void DMA_CH_MD_AddrMode(CH_TypeDef  CHx,ADDR_MODE_TypeDef AddrMode);   //DMA通道MD侧地址变化方式选择

void DMA_CH_MD_Size(CH_TypeDef  CHx,ADDR_SIZE_TypeDef Size);           //DMA通道MD侧总线传输宽度

void DMA_CH0_MD_Sel(CH0_MD_TypeDef  Sel);                              //DMA通道0的MD侧外设选择

void DMA_CH1_MD_Sel(CH1_MD_TypeDef  Sel);                              //DMA通道1的MD侧外设选择

void DMA_CH2_MD_Sel(CH2_MD_TypeDef  Sel);                              //DMA通道2的MD侧外设选择

void DMA_CH3_MD_Sel(CH3_MD_TypeDef  Sel);                              //DMA通道3的MD侧外设选择

void DMA_CH0_Int_Complete_En(void);                                    //DMA通道0的传输完成中断使能

void DMA_CH0_Int_Complete_Dis(void);                                   //DMA通道0的传输完成中断禁能

void DMA_CH0_Int_Complete_Clr(void);                                   //DMA通道0的传输完成中断状态清除

uint8_t DMA_CH0_Int_Complete_State(void);                              //获取DMA通道0的传输完成中断状态

void DMA_CH1_Int_Complete_En(void);                                    //DMA通道1的传输完成中断使能

void DMA_CH1_Int_Complete_Dis(void);                                   //DMA通道1的传输完成中断禁能

void DMA_CH1_Int_Complete_Clr(void);                                   //DMA通道1的传输完成中断状态清除

uint8_t DMA_CH1_Int_Complete_State(void);                              //获取DMA通道1的传输完成中断状态

void DMA_CH2_Int_Complete_En(void);                                    //DMA通道2的传输完成中断使能

void DMA_CH2_Int_Complete_Dis(void);                                   //DMA通道2的传输完成中断禁能

void DMA_CH2_Int_Complete_Clr(void);                                   //DMA通道2的传输完成中断状态清除

uint8_t DMA_CH2_Int_Complete_State(void);                              //获取DMA通道2的传输完成中断状态

void DMA_CH3_Int_Complete_En(void);                                    //DMA通道3的传输完成中断使能

void DMA_CH3_Int_Complete_Dis(void);                                   //DMA通道3的传输完成中断禁能

void DMA_CH3_Int_Complete_Clr(void);                                   //DMA通道3的传输完成中断状态清除

uint8_t DMA_CH3_Int_Complete_State(void);                              //获取DMA通道3的传输完成中断状态

void DMA_CH0_Int_HalfComplete_En(void);                                //DMA通道0的传输一半完成中断使能

void DMA_CH0_Int_HalfComplete_Dis(void);                               //DMA通道0的传输一半完成中断禁能

void DMA_CH0_Int_HalfComplete_Clr(void);                               //DMA通道0的传输一半完成中断状态清除

uint8_t DMA_CH0_Int_HalfComplete_State(void);                          //获取DMA通道0的传输一半完成中断状态

void DMA_CH1_Int_HalfComplete_En(void);                                //DMA通道1的传输一半完成中断使能

void DMA_CH1_Int_HalfComplete_Dis(void);                               //DMA通道1的传输一半完成中断禁能

void DMA_CH1_Int_HalfComplete_Clr(void);                               //DMA通道1的传输一半完成中断状态清除

uint8_t DMA_CH1_Int_HalfComplete_State(void);                          //获取DMA通道1的传输一半完成中断状态

void DMA_CH2_Int_HalfComplete_En(void);                                //DMA通道2的传输一半完成中断使能

void DMA_CH2_Int_HalfComplete_Dis(void);                               //DMA通道2的传输一半完成中断禁能

void DMA_CH2_Int_HalfComplete_Clr(void);                               //DMA通道2的传输一半完成中断状态清除

uint8_t DMA_CH2_Int_HalfComplete_State(void);                          //获取DMA通道2的传输一半完成中断状态

void DMA_CH3_Int_HalfComplete_En(void);                                //DMA通道3的传输一半完成中断使能

void DMA_CH3_Int_HalfComplete_Dis(void);                               //DMA通道3的传输一半完成中断禁能

void DMA_CH3_Int_HalfComplete_Clr(void);                               //DMA通道3的传输一半完成中断状态清除

uint8_t DMA_CH3_Int_HalfComplete_State(void);                          //获取DMA通道3的传输一半完成中断状态

uint16_t DMA_CH_Get_CurLenth(CH_TypeDef  CHx);                         //获取通道当前传输个数



#endif //__DP32G030_DMA_H__


