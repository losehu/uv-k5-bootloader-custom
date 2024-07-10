#ifndef __DP32G030_IIC_H__
#define __DP32G030_IIC_H__

#include "DP32G030.h"


typedef enum
{ 
	SLAVE_MODE  = 0x00,      //从机模式
	MASTER_MODE = 0x01,      //主机模式
} IIC_Master_TypeDef;

typedef enum
{ 
	SLAVE_ADDR_7BIT  = 0x00,    //7位地址模式
	SLAVE_ADDR_10BIT = 0x01,    //10位地址模式
} Slave_Addr_Mode_TypeDef;


typedef struct {
	
	IIC_Master_TypeDef  Master;		           //1 主机模式    0 从机模式
	
	uint16_t            BaudRate;              //传输速率
	
	Slave_Addr_Mode_TypeDef  Slave_Addr_Mode;  //从机地址模式   
	
	uint16_t            Slave_Addr;            //从机地址
	
	uint16_t            Slave_Addr_Mask;       //从机地址掩码
	
	FunctionalState     Clock_Stretch;         //时钟延展使能
	
	FunctionalState     Clock_Stretch_Adaptive;   //时钟延展后数据建立时间自适应使能
	
	FunctionalState     RX_Ovf_IE;             //接收数据寄存器溢出中断使能
	
	FunctionalState     TX_End_IE;             //发送数据结束中断使能
	
	FunctionalState     RX_End_IE;             //接收数据结束中断使能
	
	FunctionalState     Start_IE;              //SLAVE模式下检测到起始信号中断使能
	
	FunctionalState     Stop_IE;               //SLAVE模式下检测到停止信号中断使能 
	
	FunctionalState     SCL_LOW_TimeOut_IE;    //主机模式下SCL低电平超时中断使能
	
} IIC_InitTypeDef;


//断言  IIC模式
#define IS_IIC_MODE(IIC_MODE) (((IIC_MODE) == SLAVE_MODE) || ((IIC_MODE) == MASTER_MODE))

//断言  IIC从机地址模式   
#define IS_IIC_SLAVE_ADDRMODE(IIC_SLAVE_ADDRMODE) (((IIC_SLAVE_ADDRMODE) == SLAVE_ADDR_7BIT) || ((IIC_SLAVE_ADDRMODE) == SLAVE_ADDR_10BIT))


void IIC_Init(IIC_TypeDef *IICx,IIC_InitTypeDef * IIC_InitStruct);   //IIC初始化

void IIC_Open(IIC_TypeDef *IICx);                                  //打开IIC

void IIC_Close(IIC_TypeDef *IICx);                                 //关闭IIC

uint8_t IIC_Start(IIC_TypeDef *IICx,uint8_t addr);                 //产生起始信号并发送设备地址

uint8_t IIC_Start_10bit(IIC_TypeDef *IICx,uint16_t addr,uint8_t readwrite);    //产生起始信号并发送设备地址  10位地址

void IIC_Stop(IIC_TypeDef *IICx);                                  //产生停止信号

uint8_t IIC_Write(IIC_TypeDef *IICx,uint8_t data);                 //写入一个数据

uint8_t IIC_Read(IIC_TypeDef *IICx,uint8_t ack);                   //读取一个数据   

void IIC_Start_NoWait(IIC_TypeDef *IICx,uint8_t addr);                                               //产生起始信号并发送设备地址

void IIC_Start_10bit_First_NoWait(IIC_TypeDef *IICx,uint16_t addr,uint8_t readwrite);                //产生起始信号并发送设备地址  10位地址   bit9 8

void IIC_Start_10bit_Second_NoWait(IIC_TypeDef *IICx,uint16_t addr);                                 //产生起始信号并发送设备地址  10位地址   bit7-0

uint8_t IIC_Wait_ACK(IIC_TypeDef *IICx);                                                             //读取应答信号

void IIC_Write_NoWait(IIC_TypeDef *IICx,uint8_t data);                                               //写入一个数据

void IIC_Read_NoWait(IIC_TypeDef *IICx,uint8_t ack);                                                 //读取一个数据  

void IIC_IntRxOvfEn(IIC_TypeDef *IICx);                                                              //IIC接收数据溢出中断使能

void IIC_IntRxOvfDis(IIC_TypeDef *IICx);                                                             //IIC接收数据溢出中断禁能

void IIC_IntRxOvfClr(IIC_TypeDef *IICx);                                                             //IIC接收数据溢出中断状态清除

uint8_t IIC_IntRxOvfStat(IIC_TypeDef *IICx);                                                         //获取IIC接收数据溢出中断状态

void IIC_IntTxFinishEn(IIC_TypeDef *IICx);                                                           //IIC发送数据结束中断使能

void IIC_IntTxFinishDis(IIC_TypeDef *IICx);                                                          //IIC发送数据结束中断禁能

void IIC_IntTxFinishClr(IIC_TypeDef *IICx);                                                          //IIC发送数据结束中断状态清除

uint8_t IIC_IntTxFinishStat(IIC_TypeDef *IICx);                                                      //获取IIC发送数据结束中断状态

void IIC_IntRxFinishEn(IIC_TypeDef *IICx);                                                           //IIC接收数据结束中断使能

void IIC_IntRxFinishDis(IIC_TypeDef *IICx);                                                          //IIC接收数据结束中断禁能

void IIC_IntRxFinishClr(IIC_TypeDef *IICx);                                                          //IIC接收数据结束中断状态清除

uint8_t IIC_IntRxFinishStat(IIC_TypeDef *IICx);                                                      //获取IIC接收数据结束中断状态

void IIC_IntSlaveStartEn(IIC_TypeDef *IICx);                                                         //IIC从机检测到START信号中断使能

void IIC_IntSlaveStartDis(IIC_TypeDef *IICx);                                                        //IIC从机检测到START信号中断禁能

void IIC_IntSlaveStartClr(IIC_TypeDef *IICx);                                                        //IIC从机检测到START信号中断状态清除

uint8_t IIC_IntSlaveStartStat(IIC_TypeDef *IICx);                                                    //获取IIC从机检测到START信号中断状态

void IIC_IntSlaveStopEn(IIC_TypeDef *IICx);                                                          //IIC从机检测到STOP信号中断使能

void IIC_IntSlaveStopDis(IIC_TypeDef *IICx);                                                         //IIC从机检测到STOP信号中断禁能

void IIC_IntSlaveStopClr(IIC_TypeDef *IICx);                                                         //IIC从机检测到STOP信号中断状态清除

uint8_t IIC_IntSlaveStopStat(IIC_TypeDef *IICx);                                                     //获取IIC从机检测到STOP信号中断状态

void IIC_IntSclLowTimeOutEn(IIC_TypeDef *IICx);                                                      //IIC主机模式下SCL低电平超时中断使能

void IIC_IntSclLowTimeOutDis(IIC_TypeDef *IICx);                                                     //IIC主机模式下SCL低电平超时中断禁能

void IIC_IntSclLowTimeOutClr(IIC_TypeDef *IICx);                                                     //IIC主机模式下SCL低电平超时中断状态清除

uint8_t IIC_IntSclLowTimeOutStat(IIC_TypeDef *IICx);                                                 //获取IIC主机模式下SCL低电平超时中断状态

uint8_t IIC_Busy_State(IIC_TypeDef *IICx);                                                           //获取IIC总线忙状态

uint8_t IIC_SCL_State(IIC_TypeDef *IICx);                                                            //获取IIC总线SCL电平状态

uint8_t IIC_SDA_State(IIC_TypeDef *IICx);                                                            //获取IIC总线SDA电平状态

uint8_t IIC_Slave_Read_State(IIC_TypeDef *IICx);                                                     //获取IIC从机读状态

uint8_t IIC_Slave_Write_State(IIC_TypeDef *IICx);                                                    //获取IIC从机写状态

uint8_t IIC_Slave_Data_Type(IIC_TypeDef *IICx);                                                      //获取IIC从机接收到的数据类型

void IIC_TXD_Clear(IIC_TypeDef *IICx);                                                               //IIC发送数据寄存器清空

uint8_t IIC_TXD_Empty_State(IIC_TypeDef *IICx);                                                      //获取IIC发送数据寄存器空状态

uint8_t IIC_RXD_NotEmpty_State(IIC_TypeDef *IICx);                                                   //获取IIC接收数据寄存器非空状态

void IIC_Set_Addr7_Mask(IIC_TypeDef *IICx,uint8_t AddrMask);                                         //配置从机地址掩码
         
void IIC_Set_Addr10_Mask(IIC_TypeDef *IICx,uint8_t AddrMask);                                        //配置从机地址掩码


#endif //__DP32G030_IIC_H__



