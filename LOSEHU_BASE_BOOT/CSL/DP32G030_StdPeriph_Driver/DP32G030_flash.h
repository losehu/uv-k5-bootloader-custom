#ifndef __DP32G030_FLASH_H__
#define __DP32G030_FLASH_H__

#include "DP32G030.h"


#define FLASH_MODE_READ          0x00       //FLASH读操作
#define FLASH_MODE_WRITE         0x01       //FLASH写操作
#define FLASH_MODE_SECTOR_ERASE  0x02       //FLASH扇区擦操作
#define FLASH_MODE_RECALL_READ   0x05       //FLASH RECALL读操作

#define FLASH_MAIN_ARRAY         0x00       //FLASH选择MAIN区
#define FLASH_NVR_ARRAY          0x01       //FLASH选择NVR区

#define FLASH_ONE_CLK_WAIT       0x00       //读速率选择  1个时钟周期等待  系统时钟小于等于56MHz
#define FLASH_TWO_CLK_WAIT       0x01       //读速率选择  2个时钟周期等待  系统时钟大于56MHz

#define FLASH_MAIN_NO_MASK       0x00       //FLASH的MAIN区无屏蔽全部作为程序区
#define FLASH_MAIN_2K_MASK       0x01       //FLASH的MAIN区最低2K字节屏蔽作为BOOT区域
#define FLASH_MAIN_4K_MASK       0x02       //FLASH的MAIN区最低4K字节屏蔽作为BOOT区域
#define FLASH_MAIN_8K_MASK       0x03       //FLASH的MAIN区最低8K字节屏蔽作为BOOT区域

#define FLASH_TRCV_TIME          52         //至少大于50us  这里配置为60us
#define FLASH_TERASE_TIME        3600       //在3.2ms到4ms之间  这里配置为3.6ms  也就是3600us

#define FLASH_TPGS_TIME          22         //至少大于20us  这里配置为30us
#define FLASH_TPROG_TIME         18         //在16us到20us之间  这里配置为18us


#define FLASH_CHIPID3_ADDR        0xF024    //CHIP ID3
#define FLASH_CHIPID2_ADDR        0xF020    //CHIP ID2
#define FLASH_CHIPID1_ADDR        0xF01C    //CHIP ID1
#define FLASH_CHIPID0_ADDR        0xF018    //CHIP ID0

#define FLASH_TRIM_PWR0_ADDR      0x7E4     //电压相关TRIM值
#define FLASH_TRIM_PWR1_ADDR      0x7E0     //电压相关TRIM值
#define FLASH_TRIM_RCHF_ADDR      0x7D8     //内部高频TRIM值
#define FLASH_TRIM_RCLF_ADDR      0x7D4     //内部低频TRIM值
#define FLASH_TRIM_OPA_ADDR       0x7D0     //运放TRIM值
#define FLASH_TRIM_PLLRES_ADDR    0x7CC     //PLL电阻TRIM值
#define FLASH_FREQ_DELTA_ADDR     0x7C8     //内部高频和低频时钟实际值和理论值的差值
#define FLASH_VREF_DELTA_ADDR     0x7C4     //VREF电压差值
#define FLASH_TRIM_ADC_ADDR       0x7BC     //ADC模块TRIM值
#define FLASH_TRIM_TEMP_ADDR      0x7B8     //温度传感器TRIM值


extern uint32_t Temp_Trim_Value;                 //温度传感器校准值

uint8_t FLASH_Check_Init_Complete(void);         //FLASH检查控制器初始化是否完成

uint8_t FLASH_Check_Busy(void);                  //FLASH检查控制器忙

uint8_t FLASH_Check_BufEmpty(void);              //FLASH检查编程数据缓存寄存器是否为空

void FLASH_Set_DeepSleep_Mode(void);             //FLASH进入深度睡眠模式，可以降低功耗

void FLASH_Set_Normal_Mode(void);                //FLASH进入正常工作模式

void FLASH_Set_ClkWait(uint8_t ClkWait);         //FLASH配置读速率模式时钟周期等待时间   0  1个系统时钟等待  1  2个系统时钟等待

void FLASH_Set_Array(uint8_t Array);             //FLASH配置区域选择   0  MAIN ARRAY(64K)   1 NVR ARRAY(2K) 

void FLASH_Set_Operate_Mode(uint8_t Mode);       //FLASH配置工作模式   0 读  1 写  2 扇区擦 3 全片擦 

void FLASH_Set_EraseTime(void);                  //FLASH配置擦除时间参数

void FLASH_Set_ProgramTime(void);                //FLASH配置编程时间参数

void FLASH_Operate_Lock(void);                   //FLASH上锁后不能进行FLASH编程

void FLASH_Operate_UnLock(void);                 //FLASH解锁后可以进行FLASH编程

void FLASH_Init(uint8_t ClkWait);                //FLASH初始化   

void FLASH_Command_Start(void);                  //FLASH解锁，命令启动

void FLASH_Mask_Lock(void);                      //FLASH MASK选择上锁后，不能进行屏蔽选择

void FLASH_Mask_UnLock(void);                    //FLASH MASK解锁后可以进行屏蔽选择

void FLASH_Mask_Sel(uint8_t Mask_Sel);           //FLASH MASK扇区选择   0 无屏蔽  1 2KB屏蔽   2  4KB屏蔽   3  8KB屏蔽

void FLASH_Unlock_Lock(void);                    //FLASH解锁，执行命令，等待完成，返回读操作，上锁

void FLASH_Sector_Erase(uint32_t addr);          //FLASH扇区擦   一个扇区512字节  输入的地址参数最好是512的整数倍

void FLASH_Write_Word(uint32_t addr,uint32_t data);                      //FLASH编程一个字

uint8_t FLASH_Write_Words(uint32_t addr,uint32_t data[],uint8_t num);    //FLASH编程多个字   

uint32_t FLASH_Recall_Read(uint32_t addr);															 //FLASH RECALL读数据

uint32_t FLASH_Read_Word(uint32_t addr);                                 //FLASH读单个字

void FLASH_Read_Words(uint32_t addr,uint32_t data[],uint32_t num);       //FLASH读多个字 

void Read_Trim_Value_From_Flash(void);                                   //从NVR区读取TRIM值写入相应寄存器


#endif //__DP32G030_FLASH_H__




