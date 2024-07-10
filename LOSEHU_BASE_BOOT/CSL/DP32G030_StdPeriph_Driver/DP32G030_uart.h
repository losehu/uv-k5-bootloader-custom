#ifndef __DP32G030_UART_H__
#define __DP32G030_UART_H__

#include "DP32G030.h"


typedef enum
{ 
	UART_DATA_8BIT =  0x00,       //数据位8bit
	UART_DATA_9BIT =  0x01        //数据位9bit
} DataBits_TypeDef;

typedef enum
{ 
	UART_PARITY_NONE =  0x00,     //无校验
	UART_PARITY_ODD  =  0x01,     //奇校验
    UART_PARITY_EVEN =  0x03,     //偶校验
	UART_PARITY_ONE  =  0x05,     //常1
	UART_PARITY_ZERO =  0x07      //常0
} Parity_TypeDef;

typedef enum
{ 
	AUTOBAUD_LEN_1BIT =  0x00,       //1位时长  从起始位到第1个上升沿，输入数据位0x01
	AUTOBAUD_LEN_2BIT =  0x01,       //2位时长  从起始位到第1个上升沿，输入数据位0x02
	AUTOBAUD_LEN_4BIT =  0x02,       //4位时长  从起始位到第1个上升沿，输入数据位0x08
	AUTOBAUD_LEN_8BIT =  0x03,       //8位时长  从起始位到第1个上升沿，输入数据位0x80
} AutoBaud_Len_TypeDef;

typedef enum
{ 
	CTS_POL_LOW_ACTIVE  =  0x00,       //低电平有效  当CTS信号输入为低电平时，表示可以发送数据
	CTS_POL_HIGH_ACTIVE =  0x01,       //高电平有效  当CTS信号输入为高电平时，表示可以发送数据
} CTS_Pol_TypeDef;

typedef enum
{ 
	RTS_POL_LOW_ACTIVE  =  0x00,       //低电平有效  当RTS信号输出为低电平时，表示可以接收数据
	RTS_POL_HIGH_ACTIVE =  0x01,       //高电平有效  当RTS信号输出为高电平时，表示可以接收数据
} RTS_Pol_TypeDef;


typedef enum
{ 
	TXFIFO_LEVEL_0 =  0x00,       //设置值为0
	TXFIFO_LEVEL_1 =  0x01,       //设置值为1
	TXFIFO_LEVEL_2 =  0x02,       //设置值为2
	TXFIFO_LEVEL_3 =  0x03,       //设置值为3
	TXFIFO_LEVEL_4 =  0x04,       //设置值为4
	TXFIFO_LEVEL_5 =  0x05,       //设置值为5
	TXFIFO_LEVEL_6 =  0x06,       //设置值为6
	TXFIFO_LEVEL_7 =  0x07,       //设置值为7
} TXFIFO_Level_TypeDef;           //发送FIFO中待发送的数据个数不多于设置值产生中断


typedef enum
{ 
	RXFIFO_LEVEL_1 =  0x00,       //设置值为1
	RXFIFO_LEVEL_2 =  0x01,       //设置值为2
	RXFIFO_LEVEL_3 =  0x02,       //设置值为3
	RXFIFO_LEVEL_4 =  0x03,       //设置值为4
	RXFIFO_LEVEL_5 =  0x04,       //设置值为5
	RXFIFO_LEVEL_6 =  0x05,       //设置值为6
	RXFIFO_LEVEL_7 =  0x06,       //设置值为7
	RXFIFO_LEVEL_8 =  0x07,       //设置值为8
} RXFIFO_Level_TypeDef;           //接收FIFO中接收到的数据至少达到设置值产生中断


typedef struct {
	uint32_t          Baudrate;         //波特率
	
	DataBits_TypeDef  DataBits;			//数据位位数，可取值UART_DATA_8BIT、UART_DATA_9BIT
	
	Parity_TypeDef    Parity;			//奇偶校验位，可取值UART_PARITY_NONE、UART_PARITY_ODD、UART_PARITY_EVEN、UART_PARITY_ONE、UART_PARITY_ZERO
	
	FunctionalState   TX_Enable;        //发送使能
	
	FunctionalState   RX_Enable;        //接收使能
	
	FunctionalState   RX_DMAEnable;     //接收DMA传输使能
	
	FunctionalState   AutoBaud_Enable;  //自动波特率检测使能
	
	AutoBaud_Len_TypeDef AutoBaud_Len;  //自动波特率检测位长配置
	
	uint16_t          Rx_TimeOut;       //接收超时配置值
	
	FunctionalState   CTS_Enable;       //CTS流控使能
	
	FunctionalState   RTS_Enable;       //RTS流控使能
	
	CTS_Pol_TypeDef   CTS_Pol;          //CTS信号极性配置
	
	RTS_Pol_TypeDef   RTS_Pol;          //RTS信号极性配置
	
	TXFIFO_Level_TypeDef  TXFIFO_Level; //发送FIFO水位设置
	
	RXFIFO_Level_TypeDef  RXFIFO_Level; //接收FIFO水位设置
	
	FunctionalState  TXFIFO_Clr_Enable; //发送FIFO清除使能
	
	FunctionalState  RXFIFO_Clr_Enable; //接收FIFO清除使能
	
	FunctionalState  TX_DONE_IE;        //全部数据发送完成中断使能 
	
	FunctionalState  PARITY_ERROR_IE;   //接收数据出现奇偶校验错误中断使能
	
	FunctionalState  STOP_ERROR_IE;     //接收数据出现停止位错误中断使能
	
	FunctionalState  RX_TIMEOUT_IE;     //接收超时中断使能
	
	FunctionalState  RXFIFO_LEVEL_IE;   //接收FIFO中接收到的数据达到设定水位中断使能
	
	FunctionalState  TXFIFO_LEVEL_IE;   //发送FIFO中待发送的数据个数不多于设置值中断使能
	
	FunctionalState  RXFIFO_OVF_IE;     //接收FIFO溢出中断使能
	
	FunctionalState  AUTOBAUD_OVF_IE;   //自动波特率检测功能计数器溢出中断使能
		
} UART_InitTypeDef;


//断言  UART0  UART1   UART2
#define IS_UART_ALL(UART) (((UART) == UART0) || ((UART) == UART1)|| ((UART) == UART2))

//断言串口数据位位数
#define IS_UART_DATABITS(UART_DATABITS)  ( ((UART_DATABITS) == UART_DATA_8BIT) || ((UART_DATABITS) == UART_DATA_9BIT) )  
										 
//断言串口奇偶校验位
#define IS_UART_PARITY(UART_PARITY)      ( ((UART_PARITY) == UART_PARITY_NONE) || ((UART_PARITY) == UART_PARITY_ODD) ||  \
                                           ((UART_PARITY) == UART_PARITY_EVEN) || ((UART_PARITY) == UART_PARITY_ONE) ||  \
                                           ((UART_PARITY) == UART_PARITY_ZERO) )

//断言串口自动波特率位长
#define IS_UART_AUTOBAUD_LEN(UART_AUTOBAUD_LEN)  (((UART_AUTOBAUD_LEN) == AUTOBAUD_LEN_1BIT) || ((UART_AUTOBAUD_LEN) == AUTOBAUD_LEN_2BIT)  \
                                                  ((UART_AUTOBAUD_LEN) == AUTOBAUD_LEN_4BIT) || ((UART_AUTOBAUD_LEN) == AUTOBAUD_LEN_8BIT) )

//断言串口CTS信号极性配置
#define IS_UART_CTS_POL(UART_CTS_POL)     (((UART_CTS_POL) == CTS_POL_LOW_ACTIVE) || ((UART_CTS_POL) == CTS_POL_HIGH_ACTIVE))

//断言串口RTS信号极性配置
#define IS_UART_RTS_POL(UART_RTS_POL)     (((UART_RTS_POL) == RTS_POL_LOW_ACTIVE) || ((UART_RTS_POL) == RTS_POL_HIGH_ACTIVE))


//断言串口发送FIFO水位设置
#define IS_UART_TXFIFO_LEVEL(UART_TXFIFO_LEVEL)  (((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_0) || ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_1)  \
                                                  ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_2) || ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_3)  \
                                                  ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_4) || ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_5)  \
                                                  ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_6) || ((UART_TXFIFO_LEVEL) == TXFIFO_LEVEL_7) )

//断言串口接收FIFO水位设置
#define IS_UART_RXFIFO_LEVEL(UART_RXFIFO_LEVEL)  (((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_1) || ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_2)  \
                                                  ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_3) || ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_4)  \
                                                  ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_5) || ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_6)  \
                                                  ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_7) || ((UART_RXFIFO_LEVEL) == RXFIFO_LEVEL_8) )



void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * UART_InitStruct);	//UART串口初始化

void UART_Open(UART_TypeDef * UARTx);                                       //串口打开
void UART_Close(UART_TypeDef * UARTx);                                      //串口关闭

void UART_Set_BaudRate(UART_TypeDef * UARTx,uint32_t BaudRate);             //配置串口波特率 

void UART_TX_Enable(UART_TypeDef * UARTx);                                  //串口发送使能
void UART_TX_Disable(UART_TypeDef * UARTx);                                 //串口发送禁能

void UART_RX_Enable(UART_TypeDef * UARTx);                                  //串口接收使能
void UART_RX_Disable(UART_TypeDef * UARTx);                                 //串口接收禁能

void UART_RXDMA_Enable(UART_TypeDef * UARTx);                               //串口接收DMA传输使能
void UART_RXDMA_Disable(UART_TypeDef * UARTx);                              //串口接收DMA传输禁能

void UART_AutoBaud_Enable(UART_TypeDef * UARTx);                            //串口自动波特率检测使能
void UART_AutoBaud_Disable(UART_TypeDef * UARTx);                           //串口自动波特率检测禁能

void UART_Set_AutoBaud_Len(UART_TypeDef * UARTx,AutoBaud_Len_TypeDef AutoBaud_Len);   //串口自动波特率检测位长设置  

uint8_t UART_AutoBaud_Finished_Check(UART_TypeDef * UARTx);                 //串口自动波特率检测完成状态

void UART_Set_RX_TimeOut(UART_TypeDef * UARTx,uint8_t RX_TimeOut);          //串口接收超时时间设置

void UART_CTS_Enable(UART_TypeDef * UARTx);                                 //串口CTS流控使能
void UART_CTS_Disable(UART_TypeDef * UARTx);                                //串口CTS流控禁能

void UART_RTS_Enable(UART_TypeDef * UARTx);                                 //串口RTS流控使能
void UART_RTS_Disable(UART_TypeDef * UARTx);                                //串口RTS流控禁能

void UART_Set_CTS_Pol(UART_TypeDef * UARTx,CTS_Pol_TypeDef   CTS_Pol);      //串口CTS信号极性设置
void UART_Set_RTS_Pol(UART_TypeDef * UARTx,RTS_Pol_TypeDef RTS_Pol);        //串口RTS信号极性设置 

uint8_t UART_Get_CTS_Pol(UART_TypeDef * UARTx);                             //获取CTS信号极性
uint8_t UART_Get_RTS_Pol(UART_TypeDef * UARTx);                             //获取RTS信号极性

void UART_Set_TXFIFO_Level(UART_TypeDef * UARTx,TXFIFO_Level_TypeDef  TXFIFO_Level);   //串口发送FIFO水位设置
void UART_Set_RXFIFO_Level(UART_TypeDef * UARTx,RXFIFO_Level_TypeDef  RXFIFO_Level);   //串口接收FIFO水位设置

void UART_Set_TXFIFO_Clr(UART_TypeDef * UARTx);                             //串口发送FIFO清除使能设置
void UART_Set_RXFIFO_Clr(UART_TypeDef * UARTx);                             //串口接收FIFO清除使能设置

void UART_IntTxDoneEn(UART_TypeDef * UARTx);                                //串口数据全部发送完成中断使能
void UART_IntTxDoneDis(UART_TypeDef * UARTx);                               //串口数据全部发送完成中断禁能
void UART_IntTxDoneClr(UART_TypeDef * UARTx);                               //串口数据全部发送完成中断标志清除
uint8_t UART_IntTxDoneState(UART_TypeDef * UARTx);                          //串口数据全部发送完成中断状态

void UART_IntParityErrorEn(UART_TypeDef * UARTx);                           //串口接收数据出现奇偶校验错误中断使能
void UART_IntParityErrorDis(UART_TypeDef * UARTx);                          //串口接收数据出现奇偶校验错误中断禁能
void UART_IntParityErrorClr(UART_TypeDef * UARTx);                          //串口接收数据出现奇偶校验错误中断标志清除
uint8_t UART_IntParityErrorState(UART_TypeDef * UARTx);                     //串口接收数据出现奇偶校验错误中断状态

void UART_IntStopErrorEn(UART_TypeDef * UARTx);                             //串口接收数据出现停止位错误中断使能
void UART_IntStopErrorDis(UART_TypeDef * UARTx);                            //串口接收数据出现停止位错误中断禁能
void UART_IntStopErrorClr(UART_TypeDef * UARTx);                            //串口接收数据出现停止位错误中断标志清除
uint8_t UART_IntStopErrorState(UART_TypeDef * UARTx);                       //串口接收数据出现停止位错误中断状态

void UART_IntRxTimeOutEn(UART_TypeDef * UARTx);                             //串口数据接收超时中断使能
void UART_IntRxTimeOutDis(UART_TypeDef * UARTx);                            //串口数据接收超时中断禁能
void UART_IntRxTimeOutClr(UART_TypeDef * UARTx);                            //串口数据接收超时中断标志清除
uint8_t UART_IntRxTimeOutState(UART_TypeDef * UARTx);                       //串口数据接收超时中断状态

void UART_IntRXFIFOLevelEn(UART_TypeDef * UARTx);                           //串口接收FIFO中接收到的数据达到设定水位中断使能
void UART_IntRXFIFOLevelDis(UART_TypeDef * UARTx);                          //串口接收FIFO中接收到的数据达到设定水位中断禁能
void UART_IntRXFIFOLevelClr(UART_TypeDef * UARTx);                          //串口接收FIFO中接收到的数据达到设定水位中断标志清除
uint8_t UART_IntRXFIFOLevelState(UART_TypeDef * UARTx);                     //串口接收FIFO中接收到的数据达到设定水位中断状态

void UART_IntTXFIFOLevelEn(UART_TypeDef * UARTx);                           //串口发送FIFO中待发送的数据个数不多于设置值中断使能
void UART_IntTXFIFOLevelDis(UART_TypeDef * UARTx);                          //串口发送FIFO中待发送的数据个数不多于设置值中断禁能
void UART_IntTXFIFOLevelClr(UART_TypeDef * UARTx);                          //串口发送FIFO中待发送的数据个数不多于设置值中断标志清除
uint8_t UART_IntTXFIFOLevelState(UART_TypeDef * UARTx);                     //串口发送FIFO中待发送的数据个数不多于设置值中断状态

void UART_IntRXFIFOOvfEn(UART_TypeDef * UARTx);                             //串口接收FIFO溢出中断使能
void UART_IntRXFIFOOvfDis(UART_TypeDef * UARTx);                            //串口接收FIFO溢出中断禁能
void UART_IntRXFIFOOvfClr(UART_TypeDef * UARTx);                            //串口接收FIFO溢出中断标志清除
uint8_t UART_IntRXFIFOOvfState(UART_TypeDef * UARTx);                       //串口接收FIFO溢出中断状态

void UART_IntAutoBaudOvfEn(UART_TypeDef * UARTx);                           //串口自动波特率检测功能计数器溢出中断使能
void UART_IntAutoBaudOvfDis(UART_TypeDef * UARTx);                          //串口自动波特率检测功能计数器溢出中断禁能
void UART_IntAutoBaudOvfClr(UART_TypeDef * UARTx);                          //串口自动波特率检测功能计数器溢出中断标志清除
uint8_t UART_IntAutoBaudOvfState(UART_TypeDef * UARTx);                     //串口自动波特率检测功能计数器溢出中断状态

void UART_SendData(UART_TypeDef * UARTx, uint16_t data);                    //串口发送函数  

uint16_t UART_ReceiveData(UART_TypeDef * UARTx);                            //串口接收函数  

uint8_t UART_RXFIFOEmptyState(UART_TypeDef * UARTx);                        //串口接收FIFO空状态

uint8_t UART_RXFIFOFullState(UART_TypeDef * UARTx);                         //串口接收FIFO满状态

uint8_t UART_RXFIFOHalfFullState(UART_TypeDef * UARTx);                     //串口接收FIFO半满状态

uint8_t UART_TXFIFOEmptyState(UART_TypeDef * UARTx);                        //串口发送FIFO空状态

uint8_t UART_TXFIFOFullState(UART_TypeDef * UARTx);                         //串口发送FIFO满状态

uint8_t UART_TXFIFOHalfFullState(UART_TypeDef * UARTx);                     //串口发送FIFO半满状态

uint8_t UART_TXBusyState(UART_TypeDef * UARTx);                             //串口发送忙状态

uint8_t UART_RXFIFOLevelState(UART_TypeDef * UARTx);                        //串口接收FIFO水位

uint8_t UART_TXFIFOLevelState(UART_TypeDef * UARTx);                        //串口发送FIFO水位


void UART_RX_Stop_2bit(UART_TypeDef * UARTx);

void UART_TXRX_Stop_2bit(UART_TypeDef * UARTx);

void UART_TX_Stop_1bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_1bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_2bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_3bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_4bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_5bit(UART_TypeDef * UARTx);

void UART_TX_Stop_2bit_Idle_6bit(UART_TypeDef * UARTx);




#endif //__DP32G030_UART_H__
