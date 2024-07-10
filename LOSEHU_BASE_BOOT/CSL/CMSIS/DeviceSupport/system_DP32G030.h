#ifndef __SYSTEM_HBM32G030_H__
#define __SYSTEM_HBM32G030_H__

#include "core_cm0.h"


#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************************************************************************
 * 系统时钟设定
 *****************************************************************************************************************************************/
#define SYS_CLK_48MHz		       0	 	//0 内部高频48MHz RC振荡器
#define SYS_CLK_48MHz_DIV2	       1		//1 内部高频48MHz RC振荡器  2分频
#define SYS_CLK_48MHz_DIV4	       2		//2 内部高频48MHz RC振荡器  4分频
#define SYS_CLK_XTAH		       3		//3 外部高频晶体振荡器（4-32MHz）
#define SYS_CLK_XTAH_DIV2	       4		//4 外部高频晶体振荡器（4-32MHz） 2分频
#define SYS_CLK_PLL_RCHF_72MHz     5        //5 PLL时钟  RCHF作为输入时钟倍频输出72MHz
#define SYS_CLK_PLL_RCHF_64MHz     6        //6 PLL时钟  RCHF作为输入时钟倍频输出64MHz
#define SYS_CLK_PLL_XTAH_72MHz     7        //7 PLL时钟  XTAH作为输入时钟倍频输出72MHz
#define SYS_CLK_PLL_XTAH_64MHz     8        //8 PLL时钟  XTAH作为输入时钟倍频输出64MHz	
#define SYS_CLK_PLL_XTAH_56MHz     9        //9 PLL时钟  XTAH作为输入时钟倍频输出56MHz	
#define SYS_CLK_PLL_XTAH_48MHz     10      //10 PLL时钟  XTAH作为输入时钟倍频输出48MHz	
	 
	 
#define __HSI		(48000000UL)		//高速内部时钟
#define __LSI		(   32768UL)		//低速内部时钟
#define __HSE		( 8000000UL)		//高速外部时钟	 
#define __LSE		(   32768UL)		//低速外部时钟 
	
	
#define PLL_CLK_SEL_RCHF        0x00    //PLL时钟选择RCHF	
#define PLL_CLK_SEL_XTAH        0x01    //PLL时钟选择XTAH	

#define SRC_CLK_SEL_RCHF        0x00    //源时钟选择RCHF
#define SRC_CLK_SEL_RCLF        0x01    //源时钟选择RCLF
#define SRC_CLK_SEL_XTAH        0x02    //源时钟选择XTAH	
#define SRC_CLK_SEL_XTAL        0x03    //源时钟选择XTAL		
#define SRC_CLK_SEL_PLL         0x04    //源时钟选择PLL	
	
#define DIV_CLK_SEL_DIV1        0x00    //源时钟1分频	
#define DIV_CLK_SEL_DIV2        0x01    //源时钟2分频		
#define DIV_CLK_SEL_DIV4        0x02    //源时钟4分频		
#define DIV_CLK_SEL_DIV8        0x03    //源时钟8分频		
#define DIV_CLK_SEL_DIV16       0x04    //源时钟16分频		
#define DIV_CLK_SEL_DIV32       0x05    //源时钟32分频		
	
#define PLL_M_DIV1              0x00    //PLL参考时钟分频系数为1
#define PLL_M_DIV2              0x01    //PLL参考时钟分频系数为2
#define PLL_M_DIV3              0x02    //PLL参考时钟分频系数为3
#define PLL_M_DIV4              0x03    //PLL参考时钟分频系数为4
#define PLL_M_DIV5              0x04    //PLL参考时钟分频系数为5
#define PLL_M_DIV6              0x05    //PLL参考时钟分频系数为6
#define PLL_M_DIV7              0x06    //PLL参考时钟分频系数为7
#define PLL_M_DIV8              0x07    //PLL参考时钟分频系数为8
#define PLL_M_DIV9              0x08    //PLL参考时钟分频系数为9
#define PLL_M_DIV10             0x09    //PLL参考时钟分频系数为10
#define PLL_M_DIV11             0x0A    //PLL参考时钟分频系数为11
#define PLL_M_DIV12             0x0B    //PLL参考时钟分频系数为12
#define PLL_M_DIV13             0x0C    //PLL参考时钟分频系数为13
#define PLL_M_DIV14             0x0D    //PLL参考时钟分频系数为14
#define PLL_M_DIV15             0x0E    //PLL参考时钟分频系数为15
#define PLL_M_DIV16             0x0F    //PLL参考时钟分频系数为16


#define PLL_N_MUL2              0x00    //PLL时钟倍频系数为2
#define PLL_N_MUL4              0x01    //PLL时钟倍频系数为4
#define PLL_N_MUL6              0x02    //PLL时钟倍频系数为6
#define PLL_N_MUL8              0x03    //PLL时钟倍频系数为8
#define PLL_N_MUL10             0x04    //PLL时钟倍频系数为10
#define PLL_N_MUL12             0x05    //PLL时钟倍频系数为12
#define PLL_N_MUL14             0x06    //PLL时钟倍频系数为14
#define PLL_N_MUL16             0x07    //PLL时钟倍频系数为16
#define PLL_N_MUL18             0x08    //PLL时钟倍频系数为18
#define PLL_N_MUL20             0x09    //PLL时钟倍频系数为20
#define PLL_N_MUL22             0x0A    //PLL时钟倍频系数为22
#define PLL_N_MUL24             0x0B    //PLL时钟倍频系数为24
#define PLL_N_MUL26             0x0C    //PLL时钟倍频系数为26
#define PLL_N_MUL28             0x0D    //PLL时钟倍频系数为28
#define PLL_N_MUL30             0x0E    //PLL时钟倍频系数为30
#define PLL_N_MUL32             0x0F    //PLL时钟倍频系数为32


extern uint32_t SystemCoreClock;		// System Clock Frequency (Core Clock)
extern uint32_t CyclesPerUs;			// Cycles per micro second

extern uint32_t  Sys_Clk_Read(void);
extern void SystemInit(void);


#ifdef __cplusplus
}
#endif

#endif //__SYSTEM_HBM32G030_H__
