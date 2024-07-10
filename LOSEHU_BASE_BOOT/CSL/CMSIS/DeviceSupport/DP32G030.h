#ifndef __DP32G030_H__
#define __DP32G030_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers **********************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                        */
  HardFault_IRQn	          = -13,	/*!< 3 Cortex-M0 Hard Fault Interrupt				 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                  */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                  */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M0 System Tick Interrupt              */
  
/******  Cortex-M0 specific Interrupt Numbers ************************************************/
  WWDT_IRQn                   = 0,
  IWDT_IRQn                   = 1,
  RTC_IRQn                    = 2,
  DMA_IRQn                    = 3,
  ADC_IRQn                    = 4,
  TIMBASE0_IRQn               = 5,
  TIMBASE1_IRQn               = 6,
  TIMPLUS0_IRQn               = 7,
  TIMPLUS1_IRQn               = 8,
  PWMBASE0_IRQn               = 9,
  PWMBASE1_IRQn               = 10,
  PWMPLUS0_IRQn               = 11,
  PWMPLUS1_IRQn               = 12,
  UART0_IRQn                  = 13,
  UART1_IRQn                  = 14,
  UART2_IRQn                  = 15,
  SPI0_IRQn                   = 16,
  SPI1_IRQn                   = 17,
  IIC0_IRQn                   = 18,	
  IIC1_IRQn                   = 19,
  CMP_IRQn                    = 20,
  TIMBASE2_IRQn               = 21,
  GPIOA5_IRQn                 = 22,
  GPIOA6_IRQn                 = 23,
  GPIOA7_IRQn                 = 24,
  GPIOB0_IRQn                 = 25,
  GPIOB1_IRQn                 = 26,
  GPIOC0_IRQn                 = 27,
  GPIOC1_IRQn                 = 28,
  GPIOA_IRQn                  = 29,
  GPIOB_IRQn                  = 30,
  GPIOC_IRQn                  = 31,
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT		    0	   /*!< UART does not provide a MPU present or not	     */
#define __NVIC_PRIO_BITS		2	   /*!< UART Supports 2 Bits for the Priority Levels	 */
#define __Vendor_SysTickConfig  0	   /*!< Set to 1 if different SysTick Config is used	 */

#if   defined ( __CC_ARM )
  #pragma anon_unions
#endif

#include <stdio.h>
#include "core_cm0.h"				   /* Cortex-M0 processor and core peripherals		     */

typedef enum {RESET = 0, SET = 1} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = 1} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = 1} ErrorStatus;


/******************************************************************************/
/*				Device Specific Peripheral registers structures			 */
/******************************************************************************/

typedef struct {
	__IO uint32_t LPOW_MD;      //低功耗模式选择
	
	__IO uint32_t LPMD_WKEN;    //低功耗唤醒源使能
	
	__IO uint32_t LPMD_WKST;    //低功耗唤醒源状态
	
	__IO uint32_t CHIPRST_ST;   //芯片复位状态   
	
	__IO uint32_t SRC_CFG;      //时钟源配置寄存器
	
	uint32_t RESERVED2[3];
	
	__IO uint32_t TRIM_POW0;     
	
	__IO uint32_t TRIM_POW1;

	__IO uint32_t TRIM_POW2;   
	
	__IO uint32_t TRIM_POW3; 

	__IO uint32_t TRIM_RCHF; 

	__IO uint32_t TRIM_RCLF;

	__IO uint32_t TRIM_OPA;

	__IO uint32_t TRIM_PLL;
	
	uint32_t RESERVED3[(0x80-0x40)/4];
	
	__IO uint32_t TRIM_LOCK;
	
} PMU_TypeDef;


#define PMU_LPOW_MD_STANDBY_POS         0     //STANDBY模式
#define PMU_LPOW_MD_STANDBY_MSK         (0x01 << PMU_LPOW_MD_STANDBY_POS)

#define PMU_LPOW_MD_SLEEP_POS           1     //SLEEP模式
#define PMU_LPOW_MD_SLEEP_MSK           (0x01 << PMU_LPOW_MD_SLEEP_POS)

#define PMU_LPOW_MD_DEEPSLEEP_POS       2     //DEEPSLEEP模式
#define PMU_LPOW_MD_DEEPSLEEP_MSK       (0x01 << PMU_LPOW_MD_DEEPSLEEP_POS)

#define PMU_LPOW_MD_STOP_POS            3     //STOP模式
#define PMU_LPOW_MD_STOP_MSK            (0x01 << PMU_LPOW_MD_STOP_POS)


#define PMU_LPMD_WKEN_ALM_POS           0    //低功耗模式下  RTC闹钟信号唤醒使能
#define PMU_LPMD_WKEN_ALM_MSK           (0x01 << PMU_LPMD_WKEN_ALM_POS)

#define PMU_LPMD_WKEN_TIM_POS           1    //低功耗模式下  RTC时间信号唤醒使能    半秒  秒  分  时  日均可配置
#define PMU_LPMD_WKEN_TIM_MSK           (0x01 << PMU_LPMD_WKEN_TIM_POS)

#define PMU_LPMD_WKEN_IO_POS            2     //低功耗模式下  IO信号唤醒使能
#define PMU_LPMD_WKEN_IO_MSK            (0x01 << PMU_LPMD_WKEN_IO_POS)


#define PMU_LPMD_WKST_ALM_POS           0     //低功耗模式下  RTC闹钟信号唤醒标志
#define PMU_LPMD_WKST_ALM_MSK           (0x01 << PMU_LPMD_WKST_ALM_POS)

#define PMU_LPMD_WKST_TIM_POS           1     //低功耗模式下  RTC时间信号唤醒标志
#define PMU_LPMD_WKST_TIM_MSK           (0x01 << PMU_LPMD_WKST_TIM_POS)

#define PMU_LPMD_WKST_IO_POS            2     //低功耗模式下  IO信号唤醒标志
#define PMU_LPMD_WKST_IO_MSK            (0x01 << PMU_LPMD_WKST_IO_POS)


#define PMU_CHIPRST_POR_POS		      0	    //上电复位状态
#define PMU_CHIPRST_POR_MSK		      (0x01 << PMU_CHIPRST_POR_POS)
 
#define PMU_CHIPRST_IWDT_POS		  1	    //独立看门狗复位状态
#define PMU_CHIPRST_IWDT_MSK		  (0x01 << PMU_CHIPRST_IWDT_POS)
 
#define PMU_CHIPRST_WWDT_POS		  2	    //窗口看门狗复位状态
#define PMU_CHIPRST_WWDT_MSK		  (0x01 << PMU_CHIPRST_WWDT_POS) 


#define PMU_SRC_CFG_RCHF_EN_POS         0     //RCHF使能
#define PMU_SRC_CFG_RCHF_EN_MSK         (0x01 << PMU_SRC_CFG_RCHF_EN_POS)

#define PMU_SRC_CFG_RCHF_FSEL_POS       1     //RCHF频率选择
#define PMU_SRC_CFG_RCHF_FSEL_MSK       (0x01 << PMU_SRC_CFG_RCHF_FSEL_POS)

#define PMU_SRC_CFG_XTAH_EN_POS         2     //XTAH使能
#define PMU_SRC_CFG_XTAH_EN_MSK         (0x01 << PMU_SRC_CFG_XTAH_EN_POS)

#define PMU_SRC_CFG_XTAL_EN_POS         3     //XTAL使能
#define PMU_SRC_CFG_XTAL_EN_MSK         (0x01 << PMU_SRC_CFG_XTAL_EN_POS)

#define PMU_SRC_CFG_RTC_CLK_SEL_POS     4     //RTC时钟选择  0:RCLF, 1:XTAL
#define PMU_SRC_CFG_RTC_CLK_SEL_MSK     (0x01 << PMU_SRC_CFG_RTC_CLK_SEL_POS)


#define PMU_TRIM_LOCK_POS		        0	//TRIM_LOCK       写入0x55锁定TRIM寄存器
#define PMU_TRIM_LOCK_MSK		        (0xFF << PMU_TRIM_LOCK_POS)

#define PMU_TRIM_UNLOCK_POS		        8	//TRIM_UNLOCK     写入0xAA解锁TRIM寄存器
#define PMU_TRIM_UNLOCK_MSK		        (0xFF << PMU_TRIM_UNLOCK_POS)


typedef struct {
	__IO uint32_t CLKSEL;				//Clock Select

	__IO uint32_t CLKDIV_EN;			//CLK_DIV时钟源开关

	__IO uint32_t CLKEN;			    //外设Clock Enable

	uint32_t RESERVED1[(0x78 - 0x0C)/4];
	
	__IO uint32_t RC_FREQ_DELTA;        //RCHF和RCLF真实频率差值寄存器

	__IO uint32_t VREF_VOLT_DELTA;      //VREF真实电压值差值寄存器	
	
	__IO uint32_t CHIPID0;              //128BIT设备ID寄存器
	
	__IO uint32_t CHIPID1;
	
	__IO uint32_t CHIPID2;
	
	__IO uint32_t CHIPID3;
	
	uint32_t RESERVED2[(0x120 - 0x90)/4];
	
	__IO uint32_t CMP_CFG;              //比较器配置寄存器
	
	__IO uint32_t CMP_ST;               //比较器状态寄存器
	
	uint32_t RESERVED3[(0x140 - 0x128)/4];
	
	__IO uint32_t OPA_CFG;              //运算放大器配置寄存器  
	
	uint32_t RESERVED4[(0x180 - 0x144)/4];
	
	__IO uint32_t PLL_CTRL;             //PLL控制寄存器
	
	__IO uint32_t PLL_ST;               //PLL状态寄存器
} SYS_TypeDef;


#define SYS_CLKSEL_SYS_POS		      0		//系统时钟选择	0 RCHF  1 CLK_DIVx
#define SYS_CLKSEL_SYS_MSK		      (0x01 << SYS_CLKSEL_SYS_POS)

#define SYS_CLKSEL_DIV_POS		      1		//选择CLK_DIVx  0 DIV1  1 DIV2  2 DIV4   3 DIV8  4  DIV16   5  DIV32
#define SYS_CLKSEL_DIV_MSK		      (0x07 << SYS_CLKSEL_DIV_POS)

#define SYS_CLKSEL_SRC_POS		      4		//选择SRC  0 RCHF   1 RCLF   2 XTAH   3 XTAL  4  PLL
#define SYS_CLKSEL_SRC_MSK		      (0x07 << SYS_CLKSEL_SRC_POS)

#define SYS_CLKSEL_PLL_POS		      7		//PLL参考时钟选择	0 RCHF  1 XTAH
#define SYS_CLKSEL_PLL_MSK		      (0x01 << SYS_CLKSEL_PLL_POS)

#define SYS_CLKSEL_PLL_READ_POS       11    //PLL参考时钟  读取
#define SYS_CLKSEL_PLL_READ_MSK       (0x01 << SYS_CLKSEL_PLL_READ_POS)

#define SYS_CLKSEL_ADC_POS		      10	//ADC采样时钟选择  0 1分频   1 2分频   2 4分频   3 8分频
#define SYS_CLKSEL_ADC_MSK		      (0x03 << SYS_CLKSEL_ADC_POS)

#define SYS_CLKSEL_ADC_READ_POS		  7	    //ADC采样时钟   读取
#define SYS_CLKSEL_ADC_READ_MSK		  (0x03 << SYS_CLKSEL_ADC_READ_POS)


#define SYS_CLKDIV_EN_DIV_POS	      0		//分频时钟选择	0 使能分频时钟输出  1 禁止分频时钟输出	
#define SYS_CLKDIV_EN_DIV_MSK         (0x01 << SYS_CLKDIV_EN_DIV_POS)


#define SYS_CLKEN_GPIOA_POS		      0		//GPIOA时钟门控   
#define SYS_CLKEN_GPIOA_MSK		      (0x01 << SYS_CLKEN_GPIOA_POS)

#define SYS_CLKEN_GPIOB_POS		      1		//GPIOB时钟门控   
#define SYS_CLKEN_GPIOB_MSK		      (0x01 << SYS_CLKEN_GPIOB_POS)

#define SYS_CLKEN_GPIOC_POS		      2		//GPIOC时钟门控   
#define SYS_CLKEN_GPIOC_MSK		      (0x01 << SYS_CLKEN_GPIOC_POS)

#define SYS_CLKEN_IIC0_POS		      4		//IIC0时钟门控   
#define SYS_CLKEN_IIC0_MSK		      (0x01 << SYS_CLKEN_IIC0_POS)

#define SYS_CLKEN_IIC1_POS		      5		//IIC1时钟门控   
#define SYS_CLKEN_IIC1_MSK		      (0x01 << SYS_CLKEN_IIC1_POS)

#define SYS_CLKEN_UART0_POS		      6     //UART0时钟门控   
#define SYS_CLKEN_UART0_MSK		      (0x01 << SYS_CLKEN_UART0_POS)

#define SYS_CLKEN_UART1_POS		      7     //UART1时钟门控   
#define SYS_CLKEN_UART1_MSK		      (0x01 << SYS_CLKEN_UART1_POS)

#define SYS_CLKEN_UART2_POS		      8     //UART2时钟门控   
#define SYS_CLKEN_UART2_MSK		      (0x01 << SYS_CLKEN_UART2_POS)

#define SYS_CLKEN_SPI0_POS		      10    //SPI0时钟门控   
#define SYS_CLKEN_SPI0_MSK		      (0x01 << SYS_CLKEN_SPI0_POS)

#define SYS_CLKEN_SPI1_POS		      11    //SPI1时钟门控   
#define SYS_CLKEN_SPI1_MSK		      (0x01 << SYS_CLKEN_SPI1_POS)

#define SYS_CLKEN_TIMBASE0_POS        12    //TIMBASE0时钟门控   
#define SYS_CLKEN_TIMBASE0_MSK        (0x01 << SYS_CLKEN_TIMBASE0_POS)

#define SYS_CLKEN_TIMBASE1_POS        13    //TIMBASE1时钟门控   
#define SYS_CLKEN_TIMBASE1_MSK        (0x01 << SYS_CLKEN_TIMBASE1_POS)

#define SYS_CLKEN_TIMBASE2_POS        14    //TIMBASE2时钟门控   
#define SYS_CLKEN_TIMBASE2_MSK        (0x01 << SYS_CLKEN_TIMBASE2_POS)

#define SYS_CLKEN_TIMPLUS0_POS        15    //TIMPLUS0时钟门控   
#define SYS_CLKEN_TIMPLUS0_MSK        (0x01 << SYS_CLKEN_TIMPLUS0_POS)

#define SYS_CLKEN_TIMPLUS1_POS        16    //TIMPLUS1时钟门控   
#define SYS_CLKEN_TIMPLUS1_MSK        (0x01 << SYS_CLKEN_TIMPLUS1_POS)

#define SYS_CLKEN_PWMBASE0_POS		  17	//PWMBASE0时钟门控   
#define SYS_CLKEN_PWMBASE0_MSK		  (0x01 << SYS_CLKEN_PWMBASE0_POS)

#define SYS_CLKEN_PWMBASE1_POS		  18	//PWMBASE1时钟门控   
#define SYS_CLKEN_PWMBASE1_MSK		  (0x01 << SYS_CLKEN_PWMBASE1_POS)

#define SYS_CLKEN_PWMPLUS0_POS		  20	//PWMPLUS0时钟门控   
#define SYS_CLKEN_PWMPLUS0_MSK		  (0x01 << SYS_CLKEN_PWMPLUS0_POS)

#define SYS_CLKEN_PWMPLUS1_POS		  21	//PWMPLUS1时钟门控   
#define SYS_CLKEN_PWMPLUS1_MSK		  (0x01 << SYS_CLKEN_PWMPLUS1_POS)

#define SYS_CLKEN_RTC_POS		      22    //RTC时钟门控   
#define SYS_CLKEN_RTC_MSK		      (0x01 << SYS_CLKEN_RTC_POS)

#define SYS_CLKEN_IWDT_POS		      23    //IWDT时钟门控   
#define SYS_CLKEN_IWDT_MSK		      (0x01 << SYS_CLKEN_IWDT_POS)

#define SYS_CLKEN_WWDT_POS		      24    //WWDT时钟门控   
#define SYS_CLKEN_WWDT_MSK		      (0x01 << SYS_CLKEN_WWDT_POS)

#define SYS_CLKEN_ADC_POS		      25    //ADC时钟门控   
#define SYS_CLKEN_ADC_MSK		      (0x01 << SYS_CLKEN_ADC_POS)

#define SYS_CLKEN_CRC_POS		      27    //CRC时钟门控   
#define SYS_CLKEN_CRC_MSK		      (0x01 << SYS_CLKEN_CRC_POS)

#define SYS_CLKEN_AES_POS		      28   //AES时钟门控   
#define SYS_CLKEN_AES_MSK		      (0x01 << SYS_CLKEN_AES_POS)

 
#define SYS_RCLF_DELTA_POS            0     //RCLF实际测试频率和32768之间的差值
#define SYS_RCLF_DELTA_MSK            (0x3FF << SYS_RCLF_DELTA_POS)

#define SYS_RCLF_SIG_POS              10     //RCLF实际测试频率和32768之间的差值符号位  1  正值   0  负值
#define SYS_RCLF_SIG_MSK              (0x01 << SYS_RCLF_SIG_POS)

#define SYS_RCHF_DELTA_POS            11     //RCHF实际测试频率和48M之间的差值
#define SYS_RCHF_DELTA_MSK            (0xFFFFF << SYS_RCHF_DELTA_POS)

#define SYS_RCHF_SIG_POS              31     //RCHF实际测试频率和48M之间的差值符号位  1  正值   0  负值
#define SYS_RCHF_SIG_MSK              (0x01 << SYS_RCHF_SIG_POS)


#define SYS_VREF_DELTA_POS            0     //VREF实际测试电压值与理论值之间的差值
#define SYS_VREF_DELTA_MSK            (0x3F << SYS_VREF_DELTA_POS)

#define SYS_VREF_SIG_POS              6     //VREF实际测试电压值与理论值之间的差值符号位  1  正值   0  负值
#define SYS_VREF_SIG_MSK              (0x01 << SYS_VREF_SIG_POS)


#define SYS_CMP_CFG_CMP0_EN_POS       0     //比较器0使能
#define SYS_CMP_CFG_CMP0_EN_MSK       (0x01 << SYS_CMP_CFG_CMP0_EN_POS)

#define SYS_CMP_CFG_CMP1_EN_POS       1     //比较器1使能
#define SYS_CMP_CFG_CMP1_EN_MSK       (0x01 << SYS_CMP_CFG_CMP1_EN_POS)

#define SYS_CMP_CFG_CMP2_EN_POS       2     //比较器2使能
#define SYS_CMP_CFG_CMP2_EN_MSK       (0x01 << SYS_CMP_CFG_CMP2_EN_POS)

#define SYS_CMP_CFG_CMP0_INTEN_POS    8     //比较器0中断使能
#define SYS_CMP_CFG_CMP0_INTEN_MSK    (0x01 << SYS_CMP_CFG_CMP0_INTEN_POS)

#define SYS_CMP_CFG_CMP1_INTEN_POS    9     //比较器1中断使能
#define SYS_CMP_CFG_CMP1_INTEN_MSK    (0x01 << SYS_CMP_CFG_CMP1_INTEN_POS)

#define SYS_CMP_CFG_CMP2_INTEN_POS    10    //比较器2中断使能
#define SYS_CMP_CFG_CMP2_INTEN_MSK    (0x01 << SYS_CMP_CFG_CMP2_INTEN_POS)

#define SYS_CMP_CFG_CMP0_HYS_POS      16    //比较器0迟滞选择                //00  24mv  01  40mv  10  60mv   11  0mv
#define SYS_CMP_CFG_CMP0_HYS_MSK      (0x03 << SYS_CMP_CFG_CMP0_HYS_POS)
 
#define SYS_CMP_CFG_CMP1_HYS_POS      18    //比较器1迟滞选择                //00  24mv  01  40mv  10  60mv   11  0mv
#define SYS_CMP_CFG_CMP1_HYS_MSK      (0x03 << SYS_CMP_CFG_CMP1_HYS_POS)

#define SYS_CMP_CFG_CMP2_HYS_POS      20    //比较器2迟滞选择                //00  24mv  01  40mv  10  60mv   11  0mv
#define SYS_CMP_CFG_CMP2_HYS_MSK      (0x03 << SYS_CMP_CFG_CMP2_HYS_POS)

#define SYS_CMP_CFG_CMP_FILTER_POS    24    //比较器输出滤波选择             //00  不滤波  01  2个系统时钟周期滤波  10  4个系统时钟周期滤波    11  8个系统时钟周期滤波 
#define SYS_CMP_CFG_CMP_FILTER_MSK    (0x03 << SYS_CMP_CFG_CMP_FILTER_POS)



#define SYS_CMP_ST_CMP0_FLITER_OUT_POS       0     //比较器0滤波后结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP0_FLITER_OUT_MSK       (0x01 << SYS_CMP_ST_CMP0_FLITER_OUT_POS)

#define SYS_CMP_ST_CMP1_FLITER_OUT_POS       1     //比较器1滤波后结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP1_FLITER_OUT_MSK       (0x01 << SYS_CMP_ST_CMP1_FLITER_OUT_POS)

#define SYS_CMP_ST_CMP2_FLITER_OUT_POS       2     //比较器2滤波后结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP2_FLITER_OUT_MSK       (0x01 << SYS_CMP_ST_CMP2_FLITER_OUT_POS)

#define SYS_CMP_ST_CMP0_OUT_POS              8     //比较器0滤波前结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP0_OUT_MSK              (0x01 << SYS_CMP_ST_CMP0_OUT_POS)

#define SYS_CMP_ST_CMP1_OUT_POS              9     //比较器1滤波前结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP1_OUT_MSK              (0x01 << SYS_CMP_ST_CMP1_OUT_POS)

#define SYS_CMP_ST_CMP2_OUT_POS              10     //比较器2滤波前结果输出    1  P>N  0  P<N
#define SYS_CMP_ST_CMP2_OUT_MSK              (0x01 << SYS_CMP_ST_CMP2_OUT_POS)

#define SYS_CMP_ST_CMP0_RISEIF_POS           16     //比较器0的中断标志  1  比较器0输出发生0到1的变化
#define SYS_CMP_ST_CMP0_RISEIF_MSK           (0x01 << SYS_CMP_ST_CMP0_RISEIF_POS)

#define SYS_CMP_ST_CMP0_FALLIF_POS           17     //比较器0的中断标志  1  比较器0输出发生1到0的变化
#define SYS_CMP_ST_CMP0_FALLIF_MSK           (0x01 << SYS_CMP_ST_CMP0_FALLIF_POS)

#define SYS_CMP_ST_CMP1_RISEIF_POS           18    //比较器1的中断标志  1  比较器1输出发生0到1的变化
#define SYS_CMP_ST_CMP1_RISEIF_MSK           (0x01 << SYS_CMP_ST_CMP1_RISEIF_POS)

#define SYS_CMP_ST_CMP1_FALLIF_POS           19    //比较器1的中断标志  1  比较器1输出发生1到0的变化
#define SYS_CMP_ST_CMP1_FALLIF_MSK           (0x01 << SYS_CMP_ST_CMP1_FALLIF_POS)

#define SYS_CMP_ST_CMP2_RISEIF_POS           20    //比较器2的中断标志  1  比较器2输出发生0到1的变化
#define SYS_CMP_ST_CMP2_RISEIF_MSK           (0x01 << SYS_CMP_ST_CMP2_RISEIF_POS)

#define SYS_CMP_ST_CMP2_FALLIF_POS           21    //比较器2的中断标志  1  比较器2输出发生1到0的变化
#define SYS_CMP_ST_CMP2_FALLIF_MSK           (0x01 << SYS_CMP_ST_CMP2_FALLIF_POS)



#define SYS_OPA_CFG_OPA0_EN_POS       0     //运算放大器0使能
#define SYS_OPA_CFG_OPA0_EN_MSK       (0x01 << SYS_OPA_CFG_OPA0_EN_POS)

#define SYS_OPA_CFG_OPA1_EN_POS       1     //运算放大器1使能
#define SYS_OPA_CFG_OPA1_EN_MSK       (0x01 << SYS_OPA_CFG_OPA1_EN_POS)


#define SYS_PLL_CTRL_PLL_EN_POS       0     //PLL使能控制位
#define SYS_PLL_CTRL_PLL_EN_MSK       (0x01 << SYS_PLL_CTRL_PLL_EN_POS)

#define SYS_PLL_CTRL_PLL_N_POS        1     //PLL FEEDBACK时钟分频
#define SYS_PLL_CTRL_PLL_N_MSK        (0x1F << SYS_PLL_CTRL_PLL_N_POS)

#define SYS_PLL_CTRL_PLL_M_POS        6     //PLL 参考时钟分频
#define SYS_PLL_CTRL_PLL_M_MSK        (0x1F << SYS_PLL_CTRL_PLL_M_POS)

#define SYS_PLL_CTRL_PLL_FBH_POS      11     //PLL FEEDBACK时钟高电平宽度设置
#define SYS_PLL_CTRL_PLL_FBH_MSK      (0x03 << SYS_PLL_CTRL_PLL_FBH_POS)

#define SYS_PLL_CTRL_FILTER_POS       13     //PLL 输入参考时钟滤波选择
#define SYS_PLL_CTRL_FILTER_MSK      (0x01 << SYS_PLL_CTRL_FILTER_POS)

#define SYS_PLL_CTRL_PLL_CP_POS       14     //PLL CP配置值
#define SYS_PLL_CTRL_PLL_CP_MSK       (0x03 << SYS_PLL_CTRL_PLL_CP_POS)


#define SYS_PLL_ST_LOCK_POS           0
#define SYS_PLL_ST_LOCK_MSK           (0x01 << SYS_PLL_ST_LOCK_POS)



typedef struct {
	__IO uint32_t PORTA_SEL0;               //PORTA功能选择
	
	__IO uint32_t PORTA_SEL1;
	
	__IO uint32_t PORTB_SEL0;               //PORTB功能选择
	
	__IO uint32_t PORTB_SEL1;
	
	__IO uint32_t PORTC_SEL0;               //PORTC功能选择
	
	uint32_t RESERVED1[(0x100 - 0x14)/4];
	
	__IO uint32_t PORTA_INEN;               //PORTA输入使能
	
	__IO uint32_t PORTB_INEN;               //PORTB输入使能
	
	__IO uint32_t PORTC_INEN;               //PORTC输入使能
	
	uint32_t RESERVED2[(0x200 - 0x10C)/4];
	
	__IO uint32_t PORTA_PU_IN;              //PORTA上拉使能
	
	__IO uint32_t PORTB_PU_IN;              //PORTB上拉使能
	
	__IO uint32_t PORTC_PU_IN;              //PORTC上拉使能
	
	uint32_t RESERVED3[(0x300 - 0x20C)/4];
	
    __IO uint32_t PORTA_PD_IN;              //PORTA下拉使能
  
	__IO uint32_t PORTB_PD_IN;              //PORTB下拉使能
  
	__IO uint32_t PORTC_PD_IN;              //PORTC下拉使能
  
    uint32_t RESERVED4[(0x400 - 0x30C)/4];     
			 
	__IO uint32_t PORTA_OD_OUT;             //PORTA开漏使能
    
	__IO uint32_t PORTB_OD_OUT;             //PORTB开漏使能
	
	__IO uint32_t PORTC_OD_OUT;             //PORTC开漏使能
	
    uint32_t RESERVED5[(0x500 - 0x40C)/4]; 
	
	__IO uint32_t PORTA_WAKEUP;            //PORTA唤醒使能
    
	__IO uint32_t PORTB_WAKEUP;            //PORTB唤醒使能
	
	__IO uint32_t PORTC_WAKEUP;            //PORTC唤醒使能
	
    uint32_t RESERVED6[(0x600 - 0x50C)/4]; 
	
	__IO uint32_t PORT_CFG;                //端口配置
	
	uint32_t RESERVED7[(0x700 - 0x604)/4]; 
	
	__IO uint32_t PORTA_WKSEL;             //PORTA端口唤醒边沿选择寄存器
	
	__IO uint32_t PORTB_WKSEL;             //PORTB端口唤醒边沿选择寄存器
	
	__IO uint32_t PORTC_WKSEL;             //PORTC端口唤醒边沿选择寄存器
} PORT_TypeDef;


#define PORT_CFG_PORTA_DS_POS		    0		//PORTA驱动能力选择  00 5ma  01 10ma  10 15ma  11 20ma 
#define PORT_CFG_PORTA_DS_MSK		    (0x03 << PORT_CFG_PORTA_DS_POS)

#define PORT_CFG_PORTB_DS_POS		    2		//PORTB驱动能力选择  00 5ma  01 10ma  10 15ma  11 20ma  
#define PORT_CFG_PORTB_DS_MSK		    (0x03 << PORT_CFG_PORTB_DS_POS)

#define PORT_CFG_PORTC_DS_POS		    4		//PORTC驱动能力选择  00 5ma  01 10ma  10 15ma  11 20ma  
#define PORT_CFG_PORTC_DS_MSK		    (0x03 << PORT_CFG_PORTC_DS_POS)

#define PORT_CFG_HYS_POS		        10		//输入迟滞等级选择  0  低输入 >0.7VDD  <0.3VDD   1 高输入  >0.85VDD <0.15VDD 
#define PORT_CFG_HYS_MSK		        (0x01 << PORT_CFG_HYS_POS)


typedef struct {
	__IO uint32_t DATA;                 //数据寄存器

	__IO uint32_t DIR;					//0 输入	1 输出

	__IO uint32_t INTLVLTRG;			//Interrupt Level Trigger  1 电平触发中断	0 边沿触发中断

	__IO uint32_t INTBE;			    //Both Edge，当INTLVLTRG设为边沿触发中断时，此位置1表示上升沿和下降沿都触发中断，置0时触发边沿由INTRISEEN选择

	__IO uint32_t INTRISEEN;			//Interrupt Rise Edge Enable   1 上升沿/高电平触发中断	0 下降沿/低电平触发中断

	__IO uint32_t INTEN;			    //1 中断使能	0 中断禁止

	__IO uint32_t INTRAWSTAT;			//中断检测单元是否检测到了触发中断的条件 1 检测到了中断触发条件	0 没有检测到中断触发条件

	__IO uint32_t INTSTAT;				//INTSTAT.PIN0 = INTRAWSTAT.PIN0 & INTEN.PIN0

	__IO uint32_t INTCLR;			    //写1清除中断标志，只对边沿触发中断有用

} GPIO_TypeDef;


typedef struct {
	__IO uint32_t LOAD;					    //IWDT计数器初始值
	
	uint32_t RESERVED[1];
	
	__IO uint32_t CTRL;                     //IWDT控制寄存器
	
	__IO uint32_t IF;						//[0] 中断标志，写1清除 
	
	__IO uint32_t FEED;                     //喂狗寄存器  写入0x55即可喂狗
	
} IWDT_TypeDef;

#define IWDT_LOAD_POS         0             //独立看门狗初始值
#define IWDT_LOAD_MSK         (0xFFFFF << IWDT_LOAD_POS)

#define IWDT_CTRL_EN_POS      0             //独立看门狗启动使能
#define IWDT_CTRL_EN_MSK      (0x01 << IWDT_CTRL_EN_POS)

#define IWDT_CTRL_INTEN_POS   1             //独立看门狗中断使能
#define IWDT_CTRL_INTEN_MSK   (0x01 << IWDT_CTRL_INTEN_POS)

#define IWDT_IF_POS           0             //独立看门狗中断状态
#define IWDT_IF_MSK           (0x01 << IWDT_IF_POS)

#define IWDT_FEED_POS         0             //独立看门狗喂狗寄存器   写入0x55即可重启计数器
#define IWDT_FEED_MSK         (0xFF << IWDT_FEED_POS)



typedef struct {
	__IO uint32_t LOAD;					    //WWDT计数器初始值
	
	__IO uint32_t VALUE;					//WWDT当前计数值
	
	__IO uint32_t CTRL;                     //WWDT控制寄存器
	
	__IO uint32_t IF;						//[0] 中断标志，写0清除 
	
	__IO uint32_t FEED;                     //喂狗寄存器  写入0x55即可喂狗
	
} WWDT_TypeDef;

 
#define WWDT_LOAD_INT_POS           0             //窗口看门狗中断比较值    向下计数到该值时可以产生中断   中断比较值一定要大于复位比较值
#define WWDT_LOAD_INT_MSK           (0x7F << WWDT_LOAD_INT_POS)

#define WWDT_LOAD_RST_POS           8             //窗口看门狗复位比较值    向下计数到该值加1时可以产生中断，计数到该值时可以产生复位  
#define WWDT_LOAD_RST_MSK           (0x3F << WWDT_LOAD_RST_POS)


#define WWDT_VALUE_POS              0             //窗口看门狗当前计数值
#define WWDT_VALUE_MSK              (0x7F << WWDT_VALUE_POS)


#define WWDT_CTRL_EN_POS            0             //窗口看门狗使能
#define WWDT_CTRL_EN_MSK            (0x01 << WWDT_CTRL_EN_POS)

#define WWDT_CTRL_CLKDIV_POS        1             //窗口看门狗计数时钟预分频   0  1分频  1  2分频   2  4分频   3  8分频
#define WWDT_CTRL_CLKDIV_MSK        (0x03 << WWDT_CTRL_CLKDIV_POS)

#define WWDT_CTRL_INTEN_POS         3             //窗口看门狗中断使能
#define WWDT_CTRL_INTEN_MSK         (0x01 << WWDT_CTRL_INTEN_POS)

#define WWDT_CTRL_PRESETINTEN_POS   4             //窗口看门狗预复位中断使能
#define WWDT_CTRL_PRESETINTEN_MSK   (0x01 << WWDT_CTRL_PRESETINTEN_POS)
 
 
#define WWDT_IF_WININT_POS          0             //窗口中断标志位       VALUE==INT_LOAD
#define WWDT_IF_WININT_MSK          (0x01 << WWDT_IF_WININT_POS)

#define WWDT_IF_PRESETINT_POS       1             //预复位中断标志位     VALUE==RST_LOAD + 1
#define WWDT_IF_PRESETINT_MSK       (0x01 << WWDT_IF_PRESETINT_POS)


#define WWDT_FEED_POS               0             //窗口看门狗喂狗寄存器   写入0x55即可重启计数器
#define WWDT_FEED_MSK               (0xFF << WWDT_FEED_POS)


typedef struct {
	__IO uint32_t EN;             //定时器使能
	
	__IO uint32_t DIV;            //定时器分频值
	
	uint32_t RESERVED1[2];
	
	__IO uint32_t IE;             //中断使能寄存器
		
	__IO uint32_t IF;             //状态寄存器
	
	uint32_t RESERVED2[2];
	
	__IO uint32_t HIGH_PERIOD;    //高16位周期配置寄存器
	
	__IO uint32_t HIGH_CNT;       //高16位当前计数值寄存器

	uint32_t RESERVED3[2];
	
	__IO uint32_t LOW_PERIOD;     //低16位周期配置寄存器
	
	__IO uint32_t LOW_CNT;        //低16位当前计数值寄存器

}TIMBASE_TypeDef;


#define TIMBASE_EN_LOW_POS       0            //基本定时器低16位使能
#define TIMBASE_EN_LOW_MSK       (0x01 << TIMBASE_EN_LOW_POS)

#define TIMBASE_EN_HIGH_POS      1            //基本定时器高16位使能
#define TIMBASE_EN_HIGH_MSK      (0x01 << TIMBASE_EN_HIGH_POS)


#define TIMBASE_DIV_POS          0            //基本定时器预分频系数   1--65536
#define TIMBASE_DIV_MSK          (0xFFFF << TIMBASE_DIV_POS)


#define TIMBASE_IE_LOW_POS       0            //基本定时器低16位中断使能
#define TIMBASE_IE_LOW_MSK       (0x01 << TIMBASE_IE_LOW_POS)

#define TIMBASE_IE_HIGH_POS      1            //基本定时器高16位中断使能
#define TIMBASE_IE_HIGH_MSK      (0x01 << TIMBASE_IE_HIGH_POS)


#define TIMBASE_IF_LOW_POS       0            //基本定时器低16位中断状态
#define TIMBASE_IF_LOW_MSK       (0x01 << TIMBASE_IF_LOW_POS)

#define TIMBASE_IF_HIGH_POS      1            //基本定时器高16位中断状态
#define TIMBASE_IF_HIGH_MSK      (0x01 << TIMBASE_IF_HIGH_POS)


#define TIMBASE_HIGH_PERIOD_POS    0            //基本定时器高16位周期配置值
#define TIMBASE_HIGH_PERIOD_MSK    (0xFFFF << TIMBASE_HIGH_PERIOD_POS)


#define TIMBASE_HIGH_CNT_POS       0            //基本定时器高16位当前计数值
#define TIMBASE_HIGH_CNT_MSK       (0xFFFF << TIMBASE_HIGH_CNT_POS)


#define TIMBASE_LOW_PERIOD_POS     0            //基本定时器低16位周期配置值
#define TIMBASE_LOW_PERIOD_MSK     (0xFFFF << TIMBASE_LOW_PERIOD_POS)


#define TIMBASE_LOW_CNT_POS        0            //基本定时器低16位当前计数值
#define TIMBASE_LOW_CNT_MSK        (0xFFFF << TIMBASE_LOW_CNT_POS)


typedef struct {
	__IO uint32_t EN;             //定时器使能
	
	__IO uint32_t DIV;            //定时器分频值
	
	__IO uint32_t CTR;            //定时器控制寄存器
	
	uint32_t RESERVED1[1];
	
	__IO uint32_t IE;             //中断使能寄存器
		
	__IO uint32_t IF;             //状态寄存器
	
	uint32_t RESERVED2[2];
	
	__IO uint32_t HIGH_PERIOD;    //高16位周期配置寄存器
	
	__IO uint32_t HIGH_CNT;       //高16位当前计数值寄存器

	__IO uint32_t HIGH_CVAL;      //高16位捕获值寄存器	
	
	uint32_t RESERVED3[1];
	
	__IO uint32_t LOW_PERIOD;     //低16位周期配置寄存器
	
	__IO uint32_t LOW_CNT;        //低16位当前计数值寄存器

	__IO uint32_t LOW_CVAL;       //低16位捕获值寄存器	
	
	uint32_t RESERVED4[1];
	
	__IO uint32_t HALL_VAL;       //HALL的原始信号电平
	
}TIMPLUS_TypeDef;

#define TIMPLUS_EN_LOW_POS            0        //低16位定时器使能寄存器    
#define TIMPLUS_EN_LOW_MSK            (0x01 << TIMPLUS_EN_LOW_POS)

#define TIMPLUS_EN_HIGH_POS           1        //高16位定时器使能寄存器    
#define TIMPLUS_EN_HIGH_MSK           (0x01 << TIMPLUS_EN_HIGH_POS)


#define TIMPLUS_DIV_POS               0        //定时器分频寄存器  1--65536
#define TIMPLUS_DIV_MSK               (0xFFFF << TIMPLUS_DIV_POS)  


#define TIMPLUS_CTR_LOW_MODE_POS       0        //低16位定时器模式寄存器  
#define TIMPLUS_CTR_LOW_MODE_MSK       (0x03 << TIMPLUS_CTR_LOW_MODE_POS)

#define TIMPLUS_CTR_LOW_CLKSEL_POS     2        //低16位定时器计数时钟源选择
#define TIMPLUS_CTR_LOW_CLKSEL_MSK     (0x03 << TIMPLUS_CTR_LOW_CLKSEL_POS)

#define TIMPLUS_CTR_LOW_EXTSEL_POS     4        //低16位定时器计数模式或输入捕获模式输入信号选择
#define TIMPLUS_CTR_LOW_EXTSEL_MSK     (0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS)

#define TIMPLUS_CTR_LOW_EXTLEVEL_POS   5        //低16位定时器计数模式或输入捕获模式输入信号有效边沿选择
#define TIMPLUS_CTR_LOW_EXTLEVEL_MSK   (0x03 << TIMPLUS_CTR_LOW_EXTV_POS)

#define TIMPLUS_CTR_LOW_OUTEN_POS      7        //低16位定时器周期脉冲输出
#define TIMPLUS_CTR_LOW_OUTEN_MSK      (0x01 << TIMPLUS_CTR_LOW_OUTEN_POS)

#define TIMPLUS_CTR_LOW_DMAEN_POS      8        //低16位定时器DMA读取捕获值使能
#define TIMPLUS_CTR_LOW_DMAEN_MSK      (0x01 << TIMPLUS_CTR_LOW_DMAEN_POS)

#define TIMPLUS_CTR_HIGH_MODE_POS      16        //高16位定时器模式寄存器  
#define TIMPLUS_CTR_HIGH_MODE_MSK      (0x03 << TIMPLUS_CTR_HIGH_MODE_POS)

#define TIMPLUS_CTR_HIGH_CLKSEL_POS    18        //高16位定时器计数时钟源选择
#define TIMPLUS_CTR_HIGH_CLKSEL_MSK    (0x03 << TIMPLUS_CTR_HIGH_CLKSEL_POS)

#define TIMPLUS_CTR_HIGH_EXTSEL_POS    20        //高16位定时器计数模式或输入捕获模式输入信号选择
#define TIMPLUS_CTR_HIGH_EXTSEL_MSK    (0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS)

#define TIMPLUS_CTR_HIGH_EXTLEVEL_POS  21        //高16位定时器计数模式或输入捕获模式输入信号有效边沿选择
#define TIMPLUS_CTR_HIGH_EXTLEVEL_MSK  (0x03 << TIMPLUS_CTR_HIGH_EXTLEVEL_POS)

#define TIMPLUS_CTR_HIGH_OUTEN_POS     23        //高16位定时器周期脉冲输出
#define TIMPLUS_CTR_HIGH_OUTEN_MSK     (0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS)

#define TIMPLUS_CTR_HIGH_DMAEN_POS     24        //高16位定时器DMA读取捕获值使能
#define TIMPLUS_CTR_HIGH_DMAEN_MSK     (0x01 << TIMPLUS_CTR_HIGH_DMAEN_POS)


#define TIMPLUS_IE_LOW_OVF_POS         0        //低16位定时器溢出中断使能
#define TIMPLUS_IE_LOW_OVF_MSK         (0x01 << TIMPLUS_IE_LOW_OVF_POS)

#define TIMPLUS_IE_LOW_RISE_POS        1        //低16位定时器输入脉冲上升沿中断使能
#define TIMPLUS_IE_LOW_RISE_MSK        (0x01 << TIMPLUS_IE_LOW_RISE_POS)

#define TIMPLUS_IE_LOW_FALL_POS        2        //低16位定时器输入脉冲下降沿中断使能
#define TIMPLUS_IE_LOW_FALL_MSK        (0x01 << TIMPLUS_IE_LOW_FALL_POS)

#define TIMPLUS_IE_HIGH_OVF_POS        8        //高16位定时器溢出中断使能
#define TIMPLUS_IE_HIGH_OVF_MSK        (0x01 << TIMPLUS_IE_HIGH_OVF_POS)

#define TIMPLUS_IE_HIGH_RISE_POS       9        //高16位定时器输入脉冲上升沿中断使能
#define TIMPLUS_IE_HIGH_RISE_MSK       (0x01 << TIMPLUS_IE_HIGH_RISE_POS)

#define TIMPLUS_IE_HIGH_FALL_POS       10       //高16位定时器输入脉冲下降沿中断使能
#define TIMPLUS_IE_HIGH_FALL_MSK       (0x01 << TIMPLUS_IE_HIGH_FALL_POS)

#define TIMPLUS_IE_HALL0_RISE_POS      16       //HALL0上升沿中断使能
#define TIMPLUS_IE_HALL0_RISE_MSK      (0x01 << TIMPLUS_IE_HALL0_RISE_POS)

#define TIMPLUS_IE_HALL0_FALL_POS      17       //HALL0下降沿中断使能
#define TIMPLUS_IE_HALL0_FALL_MSK      (0x01 << TIMPLUS_IE_HALL0_FALL_POS)

#define TIMPLUS_IE_HALL1_RISE_POS      18       //HALL1上升沿中断使能
#define TIMPLUS_IE_HALL1_RISE_MSK      (0x01 << TIMPLUS_IE_HALL1_RISE_POS)

#define TIMPLUS_IE_HALL1_FALL_POS      19       //HALL1下降沿中断使能
#define TIMPLUS_IE_HALL1_FALL_MSK      (0x01 << TIMPLUS_IE_HALL1_FALL_POS)

#define TIMPLUS_IE_HALL2_RISE_POS      20       //HALL2上升沿中断使能
#define TIMPLUS_IE_HALL2_RISE_MSK      (0x01 << TIMPLUS_IE_HALL2_RISE_POS)

#define TIMPLUS_IE_HALL2_FALL_POS      21       //HALL2下降沿中断使能
#define TIMPLUS_IE_HALL2_FALL_MSK      (0x01 << TIMPLUS_IE_HALL2_FALL_POS)


#define TIMPLUS_IF_LOW_OVF_POS         0        //低16位定时器溢出中断状态
#define TIMPLUS_IF_LOW_OVF_MSK         (0x01 << TIMPLUS_IF_LOW_OVF_POS)

#define TIMPLUS_IF_LOW_RISE_POS        1        //低16位定时器输入脉冲上升沿中断状态
#define TIMPLUS_IF_LOW_RISE_MSK        (0x01 << TIMPLUS_IF_LOW_RISE_POS)

#define TIMPLUS_IF_LOW_FALL_POS        2        //低16位定时器输入脉冲下降沿中断状态
#define TIMPLUS_IF_LOW_FALL_MSK        (0x01 << TIMPLUS_IF_LOW_FALL_POS)

#define TIMPLUS_IF_HIGH_OVF_POS        8        //高16位定时器溢出中断状态
#define TIMPLUS_IF_HIGH_OVF_MSK        (0x01 << TIMPLUS_IF_HIGH_OVF_POS)

#define TIMPLUS_IF_HIGH_RISE_POS       9        //高16位定时器输入脉冲上升沿中断状态
#define TIMPLUS_IF_HIGH_RISE_MSK       (0x01 << TIMPLUS_IF_HIGH_RISE_POS)

#define TIMPLUS_IF_HIGH_FALL_POS       10       //高16位定时器输入脉冲下降沿中断状态
#define TIMPLUS_IF_HIGH_FALL_MSK       (0x01 << TIMPLUS_IF_HIGH_FALL_POS)

#define TIMPLUS_IF_HALL0_RISE_POS      16       //HALL0上升沿中断状态
#define TIMPLUS_IF_HALL0_RISE_MSK      (0x01 << TIMPLUS_IF_HALL0_RISE_POS)

#define TIMPLUS_IF_HALL0_FALL_POS      17       //HALL0下降沿中断状态
#define TIMPLUS_IF_HALL0_FALL_MSK      (0x01 << TIMPLUS_IF_HALL0_FALL_POS)

#define TIMPLUS_IF_HALL1_RISE_POS      18       //HALL1上升沿中断状态
#define TIMPLUS_IF_HALL1_RISE_MSK      (0x01 << TIMPLUS_IF_HALL1_RISE_POS)

#define TIMPLUS_IF_HALL1_FALL_POS      19       //HALL1下降沿中断状态
#define TIMPLUS_IF_HALL1_FALL_MSK      (0x01 << TIMPLUS_IF_HALL1_FALL_POS)

#define TIMPLUS_IF_HALL2_RISE_POS      20       //HALL2上升沿中断状态
#define TIMPLUS_IF_HALL2_RISE_MSK      (0x01 << TIMPLUS_IF_HALL2_RISE_POS)

#define TIMPLUS_IF_HALL2_FALL_POS      21       //HALL2下降沿中断状态
#define TIMPLUS_IF_HALL2_FALL_MSK      (0x01 << TIMPLUS_IF_HALL2_FALL_POS)


#define TIMPLUS_HALL_VAL_HALL0_POS    0        //HALL0的原始信号电平
#define TIMPLUS_HALL_VAL_HALL0_MSK    (0x01 << TIMPLUS_HALL_VAL_HALL0_POS)

#define TIMPLUS_HALL_VAL_HALL1_POS    1        //HALL1的原始信号电平
#define TIMPLUS_HALL_VAL_HALL1_MSK    (0x01 << TIMPLUS_HALL_VAL_HALL1_POS)

#define TIMPLUS_HALL_VAL_HALL2_POS    2        //HALL2的原始信号电平
#define TIMPLUS_HALL_VAL_HALL2_MSK    (0x01 << TIMPLUS_HALL_VAL_HALL2_POS)



typedef struct {
	
	__IO uint32_t EN;                     //PWMBASE使能寄存器
											
	__IO uint32_t DIV;                    //PWMBASE分频寄存器
	
	__IO uint32_t OUTCTR;                 //PWMBASE输出控制寄存器
	
	__IO uint32_t PERIOD;                 //PWMBASE周期配置寄存器
	
	__IO uint32_t IE;                     //PWMBASE中断使能寄存器
	
	__IO uint32_t IF;                     //PWMBASE中断状态寄存器
	
	__IO uint32_t CNT;                    //PWMBASE当前计数值寄存器  
	
	uint32_t RESERVED1[1];
	
	__IO uint32_t CH0_COMP;               //PWMBASE通道0的比较点配置寄存器
	
	uint32_t RESERVED2[3];
	
	__IO uint32_t CH1_COMP;               //PWMBASE通道1的比较点配置寄存器
	
	uint32_t RESERVED3[3];
	
	__IO uint32_t CH2_COMP;               //PWMBASE通道2的比较点配置寄存器
	
	
} PWMBASE_TypeDef;


#define PWMBASE_EN_POS                0      //PWMBASE计数器使能
#define PWMBASE_EN_MSK                (0x01 << PWMBASE_EN_POS)

#define PWMBASE_DIV_POS               0      //PWMBASE计数时钟分频系数    1--65536
#define PWMBASE_DIV_MSK               (0xFFFF << PWMBASE_DIV_POS)

#define PWMBASE_OUTCTR_CH0_INV_POS    0      //PWMBASE通道0输出极性翻转
#define PWMBASE_OUTCTR_CH0_INV_MSK    (0x01 << PWMBASE_OUTCTR_CH0_INV_POS)

#define PWMBASE_OUTCTR_CH1_INV_POS    1      //PWMBASE通道1输出极性翻转
#define PWMBASE_OUTCTR_CH1_INV_MSK    (0x01 << PWMBASE_OUTCTR_CH1_INV_POS)

#define PWMBASE_OUTCTR_CH2_INV_POS    2      //PWMBASE通道2输出极性翻转
#define PWMBASE_OUTCTR_CH2_INV_MSK    (0x01 << PWMBASE_OUTCTR_CH2_INV_POS)

#define PWMBASE_OUTCTR_CH0_EN_POS     4      //PWMBASE通道0输出使能
#define PWMBASE_OUTCTR_CH0_EN_MSK     (0x01 << PWMBASE_OUTCTR_CH0_EN_POS)

#define PWMBASE_OUTCTR_CH1_EN_POS     5      //PWMBASE通道1输出使能
#define PWMBASE_OUTCTR_CH1_EN_MSK     (0x01 << PWMBASE_OUTCTR_CH1_EN_POS)

#define PWMBASE_OUTCTR_CH2_EN_POS     6      //PWMBASE通道2输出使能
#define PWMBASE_OUTCTR_CH2_EN_MSK     (0x01 << PWMBASE_OUTCTR_CH2_EN_POS)

#define PWMBASE_IE_CH0_COMP_POS       0      //PWMBASE通道0到达比较点中断使能
#define PWMBASE_IE_CH0_COMP_MSK       (0x01 << PWMBASE_IE_CH0_COMP_POS)

#define PWMBASE_IE_CH1_COMP_POS       1      //PWMBASE通道1到达比较点中断使能
#define PWMBASE_IE_CH1_COMP_MSK       (0x01 << PWMBASE_IE_CH1_COMP_POS)

#define PWMBASE_IE_CH2_COMP_POS       2      //PWMBASE通道2到达比较点中断使能
#define PWMBASE_IE_CH2_COMP_MSK       (0x01 << PWMBASE_IE_CH2_COMP_POS)

#define PWMBASE_IE_OVF_POS            3      //PWMBASE周期溢出中断使能
#define PWMBASE_IE_OVF_MSK            (0x01 << PWMBASE_IE_OVF_POS)

#define PWMBASE_IF_CH0_COMP_POS       0      //PWMBASE通道0到达比较点中断状态
#define PWMBASE_IF_CH0_COMP_MSK       (0x01 << PWMBASE_IF_CH0_COMP_POS)

#define PWMBASE_IF_CH1_COMP_POS       1      //PWMBASE通道1到达比较点中断状态
#define PWMBASE_IF_CH1_COMP_MSK       (0x01 << PWMBASE_IF_CH1_COMP_POS)

#define PWMBASE_IF_CH2_COMP_POS       2      //PWMBASE通道2到达比较点中断状态
#define PWMBASE_IF_CH2_COMP_MSK       (0x01 << PWMBASE_IF_CH2_COMP_POS)

#define PWMBASE_IF_OVF_POS            3      //PWMBASE周期溢出中断状态
#define PWMBASE_IF_OVF_MSK            (0x01 << PWMBASE_IF_OVF_POS)


typedef struct {
	
	__IO uint32_t CTR;                    //PWMPLUS配置寄存器
											
	__IO uint32_t OUTCTR;                 //PWMPLUS输出控制寄存器
	
	__IO uint32_t CLK;                    //PWMPLUS时钟源选择及分频寄存器
	
	__IO uint32_t BRK_CTR;                //PWMPLUS_BRAKE配置寄存器
	
	__IO uint32_t MSK_LEVEL;              //PWMPLUS强制输出电平选择寄存器
	
	uint32_t RESERVED1[2];
	
	__IO uint32_t PERIOD;                 //PWMPLUS周期配置寄存器
	
	__IO uint32_t CH0_COMP;               //PWMPLUS通道0的比较点配置寄存器
	
	__IO uint32_t CH1_COMP;               //PWMPLUS通道1的比较点配置寄存器
	
	__IO uint32_t CH2_COMP;               //PWMPLUS通道2的比较点配置寄存器
	
	uint32_t RESERVED2[1];
	
	__IO uint32_t CH0_DEADZONE;           //PWMPLUS通道0死区长度配置寄存器
	
	__IO uint32_t CH1_DEADZONE;           //PWMPLUS通道1死区长度配置寄存器
	
	__IO uint32_t CH2_DEADZONE;           //PWMPLUS通道2死区长度配置寄存器
	
	uint32_t RESERVED3[1];
	
	__IO uint32_t TRIG_COMP;              //PWMPLUS内部触发比较点寄存器
	
	__IO uint32_t TRIG_SEL;               //PWMPLUS内部触发配置寄存器
	
	uint32_t RESERVED4[6];
	
	__IO uint32_t IE;                     //PWMPLUS中断使能寄存器
	
	__IO uint32_t IF;                     //PWMPLUS中断状态寄存器
	
	uint32_t RESERVED5[7];

	__IO uint32_t SWLOAD;                 //PWMPLUS  SWLOAD控制寄存器
	
	__IO uint32_t MSK_EN;                 //PWMPLUS屏蔽使能控制寄存器
	
	uint32_t RESERVED6[21];
	
	__IO uint32_t CNT_STATE;              //PWMPLUS当前计数值及状态寄存器  
	
	__IO uint32_t BRK_STATE;              //PWMPLUS刹车状态寄存器  
	
}PWMPLUS_TypeDef;


#define PWMPLUS_CTR_EN_POS             0   //PWMPLUS使能
#define PWMPLUS_CTR_EN_MSK             (0x01 << PWMPLUS_CTR_EN_POS)

#define PWMPLUS_CTR_DIR_POS            1   //PWMPLUS计数器计数方向配置   0  向上计数   1  向下计数
#define PWMPLUS_CTR_DIR_MSK            (0x01 << PWMPLUS_CTR_DIR_POS)

#define PWMPLUS_CTR_OPM_POS            2   //PWMPLUS单次计数模式         0  单次计数   1  重复计数
#define PWMPLUS_CTR_OPM_MSK            (0x01 << PWMPLUS_CTR_OPM_POS)

#define PWMPLUS_CTR_MODE_POS           3   //PWMPLUS输出模式             0  边沿对齐   1  中心对齐
#define PWMPLUS_CTR_MODE_MSK           (0x01 << PWMPLUS_CTR_MODE_POS)

#define PWMPLUS_CTR_RELOAD_POS         8   //PWMPLUS自动装载寄存器
#define PWMPLUS_CTR_RELOAD_MSK         (0xFF << PWMPLUS_CTR_RELOAD_POS)


#define PWMPLUS_OUTCTR_CH0_IDLE_POS    0   //PWMPLUS原始通道0空闲时输出电平
#define PWMPLUS_OUTCTR_CH0_IDLE_MSK    (0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS)

#define PWMPLUS_OUTCTR_CH0N_IDLE_POS   1   //PWMPLUS原始通道0N空闲时输出电平
#define PWMPLUS_OUTCTR_CH0N_IDLE_MSK   (0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS)

#define PWMPLUS_OUTCTR_CH1_IDLE_POS    2   //PWMPLUS原始通道1空闲时输出电平
#define PWMPLUS_OUTCTR_CH1_IDLE_MSK    (0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS)

#define PWMPLUS_OUTCTR_CH1N_IDLE_POS   3   //PWMPLUS原始通道1N空闲时输出电平
#define PWMPLUS_OUTCTR_CH1N_IDLE_MSK   (0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS)

#define PWMPLUS_OUTCTR_CH2_IDLE_POS    4   //PWMPLUS原始通道2空闲时输出电平
#define PWMPLUS_OUTCTR_CH2_IDLE_MSK    (0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS)

#define PWMPLUS_OUTCTR_CH2N_IDLE_POS   5   //PWMPLUS原始通道2N空闲时输出电平
#define PWMPLUS_OUTCTR_CH2N_IDLE_MSK   (0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS)

#define PWMPLUS_OUTCTR_CH0_START_POS   8   //PWMPLUS原始通道0开始计数时输出电平
#define PWMPLUS_OUTCTR_CH0_START_MSK   (0x01 << PWMPLUS_OUTCTR_CH0_START_POS)

#define PWMPLUS_OUTCTR_CH1_START_POS   9   //PWMPLUS原始通道1开始计数时输出电平
#define PWMPLUS_OUTCTR_CH1_START_MSK   (0x01 << PWMPLUS_OUTCTR_CH1_START_POS)

#define PWMPLUS_OUTCTR_CH2_START_POS   10   //PWMPLUS原始通道2开始计数时输出电平
#define PWMPLUS_OUTCTR_CH2_START_MSK   (0x01 << PWMPLUS_OUTCTR_CH2_START_POS)

#define PWMPLUS_OUTCTR_CH0_INV_POS     16   //PWMPLUS原始通道0输出电平反转
#define PWMPLUS_OUTCTR_CH0_INV_MSK     (0x01 << PWMPLUS_OUTCTR_CH0_INV_POS)

#define PWMPLUS_OUTCTR_CH0N_INV_POS    17   //PWMPLUS原始通道0N输出电平反转
#define PWMPLUS_OUTCTR_CH0N_INV_MSK    (0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS)

#define PWMPLUS_OUTCTR_CH1_INV_POS     18   //PWMPLUS原始通道1输出电平反转
#define PWMPLUS_OUTCTR_CH1_INV_MSK     (0x01 << PWMPLUS_OUTCTR_CH1_INV_POS)

#define PWMPLUS_OUTCTR_CH1N_INV_POS    19   //PWMPLUS原始通道1N输出电平反转
#define PWMPLUS_OUTCTR_CH1N_INV_MSK    (0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS)

#define PWMPLUS_OUTCTR_CH2_INV_POS     20   //PWMPLUS原始通道2输出电平反转
#define PWMPLUS_OUTCTR_CH2_INV_MSK     (0x01 << PWMPLUS_OUTCTR_CH2_INV_POS)

#define PWMPLUS_OUTCTR_CH2N_INV_POS    21   //PWMPLUS原始通道2N输出电平反转
#define PWMPLUS_OUTCTR_CH2N_INV_MSK    (0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS)

#define PWMPLUS_OUTCTR_CH0_OUTEN_POS   24   //PWMPLUS原始通道0输出使能
#define PWMPLUS_OUTCTR_CH0_OUTEN_MSK   (0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS)

#define PWMPLUS_OUTCTR_CH0N_OUTEN_POS  25   //PWMPLUS原始通道0N输出使能
#define PWMPLUS_OUTCTR_CH0N_OUTEN_MSK  (0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS)

#define PWMPLUS_OUTCTR_CH1_OUTEN_POS   26   //PWMPLUS原始通道1输出使能
#define PWMPLUS_OUTCTR_CH1_OUTEN_MSK   (0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS)

#define PWMPLUS_OUTCTR_CH1N_OUTEN_POS  27   //PWMPLUS原始通道1N输出使能
#define PWMPLUS_OUTCTR_CH1N_OUTEN_MSK  (0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS)

#define PWMPLUS_OUTCTR_CH2_OUTEN_POS   28   //PWMPLUS原始通道2输出使能
#define PWMPLUS_OUTCTR_CH2_OUTEN_MSK   (0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS)

#define PWMPLUS_OUTCTR_CH2N_OUTEN_POS  29   //PWMPLUS原始通道2N输出使能
#define PWMPLUS_OUTCTR_CH2N_OUTEN_MSK  (0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS)


#define PWMPLUS_CLK_SRC_POS            0    //计数时钟选择   000 内部预分频时钟作为计数时钟    011  选择低16位定时器作为计数时钟   100  选择高16位定时器作为计数时钟
#define PWMPLUS_CLK_SRC_MSK            (0x07 << PWMPLUS_CLK_SRC_POS)

#define PWMPLUS_CLK_PREDIV_POS         16   //PWMPLUS计数时钟选择               1--65536
#define PWMPLUS_CLK_PREDIV_MSK         (0xFFFF << PWMPLUS_CLK_PREDIV_POS)


#define PWMPLUS_BRK_CTR_CH0EN_POS      0    //PWMPLUS通道0和0N刹车控制使能
#define PWMPLUS_BRK_CTR_CH0EN_MSK      (0x07 << PWMPLUS_BRK_CTR_CH0EN_POS)

#define PWMPLUS_BRK_CTR_CH1EN_POS      3    //PWMPLUS通道1和1N刹车控制使能
#define PWMPLUS_BRK_CTR_CH1EN_MSK      (0x07 << PWMPLUS_BRK_CTR_CH1EN_POS)

#define PWMPLUS_BRK_CTR_CH2EN_POS      6    //PWMPLUS通道2和2N刹车控制使能
#define PWMPLUS_BRK_CTR_CH2EN_MSK      (0x07 << PWMPLUS_BRK_CTR_CH2EN_POS)

#define PWMPLUS_BRK_CTR_INLEV_POS      12    //PWMPLUS刹车输入有效电平选择
#define PWMPLUS_BRK_CTR_INLEV_MSK      (0x07 << PWMPLUS_BRK_CTR_INLEV_POS)

#define PWMPLUS_BRK_CTR_CH0_POL_POS    16    //PWMPLUS刹车时通道0输出电平选择
#define PWMPLUS_BRK_CTR_CH0_POL_MSK    (0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS)

#define PWMPLUS_BRK_CTR_CH0N_POL_POS   17    //PWMPLUS刹车时通道0N输出电平选择
#define PWMPLUS_BRK_CTR_CH0N_POL_MSK   (0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS)

#define PWMPLUS_BRK_CTR_CH1_POL_POS    18    //PWMPLUS刹车时通道1输出电平选择
#define PWMPLUS_BRK_CTR_CH1_POL_MSK    (0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS)

#define PWMPLUS_BRK_CTR_CH1N_POL_POS   19    //PWMPLUS刹车时通道1N输出电平选择
#define PWMPLUS_BRK_CTR_CH1N_POL_MSK   (0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS)

#define PWMPLUS_BRK_CTR_CH2_POL_POS    20    //PWMPLUS刹车时通道2输出电平选择
#define PWMPLUS_BRK_CTR_CH2_POL_MSK    (0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS)

#define PWMPLUS_BRK_CTR_CH2N_POL_POS   21    //PWMPLUS刹车时通道2N输出电平选择
#define PWMPLUS_BRK_CTR_CH2N_POL_MSK   (0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS)

#define PWMPLUS_BRK_CTR_FILTER_POS     24    //PWMPLUS数字滤波
#define PWMPLUS_BRK_CTR_FILTER_MSK     (0x03 << PWMPLUS_BRK_CTR_FILTER_POS)


#define PWMPLUS_MSK_LEVEL_CH0_POS      0    //PWMPLUS通道0屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH0_MSK      (0x01 << PWMPLUS_MSK_LEVEL_CH0_POS)

#define PWMPLUS_MSK_LEVEL_CH0N_POS     1    //PWMPLUS通道0N屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH0N_MSK     (0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS)

#define PWMPLUS_MSK_LEVEL_CH1_POS      2    //PWMPLUS通道1屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH1_MSK      (0x01 << PWMPLUS_MSK_LEVEL_CH1_POS)

#define PWMPLUS_MSK_LEVEL_CH1N_POS     3    //PWMPLUS通道1N屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH1N_MSK     (0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS)

#define PWMPLUS_MSK_LEVEL_CH2_POS      4    //PWMPLUS通道2屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH2_MSK      (0x01 << PWMPLUS_MSK_LEVEL_CH2_POS)

#define PWMPLUS_MSK_LEVEL_CH2N_POS     5    //PWMPLUS通道2N屏蔽电平选择
#define PWMPLUS_MSK_LEVEL_CH2N_MSK     (0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS)


#define PWMPLUS_TRIG_CTR_SEL0_POS      0    //PWMPLUS输出的触发信号0功能选择
#define PWMPLUS_TRIG_CTR_SEL0_MSK      (0x0F << PWMPLUS_TRIG_CTR_SEL0_POS)

#define PWMPLUS_TRIG_CTR_SEL1_POS      4    //PWMPLUS输出的触发信号1功能选择
#define PWMPLUS_TRIG_CTR_SEL1_MSK      (0x0F << PWMPLUS_TRIG_CTR_SEL1_POS)

#define PWMPLUS_TRIG_CTR_SEL2_POS      8    //PWMPLUS输出的触发信号2功能选择
#define PWMPLUS_TRIG_CTR_SEL2_MSK      (0x0F << PWMPLUS_TRIG_CTR_SEL2_POS)

#define PWMPLUS_TRIG_CTR_SEL3_POS      12   //PWMPLUS输出的触发信号3功能选择
#define PWMPLUS_TRIG_CTR_SEL3_MSK      (0x0F << PWMPLUS_TRIG_CTR_SEL3_POS)


#define PWMPLUS_IE_CH0_UP_COMP_POS      0    //PWMPLUS通道0向上计数到达比较点中断使能
#define PWMPLUS_IE_CH0_UP_COMP_MSK      (0x01 << PWMPLUS_IE_CH0_UP_COMP_POS)

#define PWMPLUS_IE_CH1_UP_COMP_POS      1    //PWMPLUS通道1向上计数到达比较点中断使能
#define PWMPLUS_IE_CH1_UP_COMP_MSK      (0x01 << PWMPLUS_IE_CH1_UP_COMP_POS)

#define PWMPLUS_IE_CH2_UP_COMP_POS      2    //PWMPLUS通道2向上计数到达比较点中断使能
#define PWMPLUS_IE_CH2_UP_COMP_MSK      (0x01 << PWMPLUS_IE_CH2_UP_COMP_POS)

#define PWMPLUS_IE_UP_OVF_POS           3    //PWMPLUS向上计数周期溢出中断使能
#define PWMPLUS_IE_UP_OVF_MSK           (0x01 << PWMPLUS_IE_UP_OVF_POS)

#define PWMPLUS_IE_UP_TRIG_POS          4    //PWMPLUS向上计数到达触发点中断使能
#define PWMPLUS_IE_UP_TRIG_MSK          (0x01 << PWMPLUS_IE_UP_TRIG_POS)

#define PWMPLUS_IE_CH0_DOWN_COMP_POS    8    //PWMPLUS通道0向下计数到达比较点中断使能
#define PWMPLUS_IE_CH0_DOWN_COMP_MSK    (0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS)

#define PWMPLUS_IE_CH1_DOWN_COMP_POS    9    //PWMPLUS通道1向下计数到达比较点中断使能
#define PWMPLUS_IE_CH1_DOWN_COMP_MSK    (0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS)

#define PWMPLUS_IE_CH2_DOWN_COMP_POS    10   //PWMPLUS通道2向下计数到达比较点中断使能
#define PWMPLUS_IE_CH2_DOWN_COMP_MSK    (0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS)

#define PWMPLUS_IE_DOWN_OVF_POS        11   //PWMPLUS向下计数周期溢出中断使能
#define PWMPLUS_IE_DOWN_OVF_MSK        (0x01 << PWMPLUS_IE_DOWN_OVF_POS)

#define PWMPLUS_IE_DOWN_TRIG_POS       12   //PWMPLUS向下计数到达触发点中断使能
#define PWMPLUS_IE_DOWN_TRIG_MSK       (0x01 << PWMPLUS_IE_DOWN_TRIG_POS)

#define PWMPLUS_IE_BRK0_POS            16   //PWMPLUS刹车0中断使能
#define PWMPLUS_IE_BRK0_MSK            (0x01 << PWMPLUS_IE_BRK0_POS)

#define PWMPLUS_IE_BRK1_POS            17   //PWMPLUS刹车1中断使能
#define PWMPLUS_IE_BRK1_MSK            (0x01 << PWMPLUS_IE_BRK1_POS)

#define PWMPLUS_IE_BRK2_POS            18   //PWMPLUS刹车2中断使能
#define PWMPLUS_IE_BRK2_MSK            (0x01 << PWMPLUS_IE_BRK2_POS)

#define PWMPLUS_IE_RELOAD_POS          19   //PWMPLUS自动装载中断使能
#define PWMPLUS_IE_RELOAD_MSK          (0x01 << PWMPLUS_IE_RELOAD_POS)


#define PWMPLUS_IF_CH0_UP_COMP_POS      0    //PWMPLUS通道0向上计数到达比较点中断状态
#define PWMPLUS_IF_CH0_UP_COMP_MSK      (0x01 << PWMPLUS_IF_CH0_UP_COMP_POS)

#define PWMPLUS_IF_CH1_UP_COMP_POS      1    //PWMPLUS通道1向上计数到达比较点中断状态
#define PWMPLUS_IF_CH1_UP_COMP_MSK      (0x01 << PWMPLUS_IF_CH1_UP_COMP_POS)

#define PWMPLUS_IF_CH2_UP_COMP_POS      2    //PWMPLUS通道2向上计数到达比较点中断状态
#define PWMPLUS_IF_CH2_UP_COMP_MSK      (0x01 << PWMPLUS_IF_CH2_UP_COMP_POS)

#define PWMPLUS_IF_UP_OVF_POS           3    //PWMPLUS向上计数周期溢出中断状态
#define PWMPLUS_IF_UP_OVF_MSK           (0x01 << PWMPLUS_IF_UP_OVF_POS)

#define PWMPLUS_IF_UP_TRIG_POS          4    //PWMPLUS向上计数到达触发点中断状态
#define PWMPLUS_IF_UP_TRIG_MSK          (0x01 << PWMPLUS_IF_UP_TRIG_POS)

#define PWMPLUS_IF_CH0_DOWN_COMP_POS    8    //PWMPLUS通道0向下计数到达比较点中断状态
#define PWMPLUS_IF_CH0_DOWN_COMP_MSK    (0x01 << PWMPLUS_IF_CH0_DOWN_COMP_POS)

#define PWMPLUS_IF_CH1_DOWN_COMP_POS    9    //PWMPLUS通道1向下计数到达比较点中断状态
#define PWMPLUS_IF_CH1_DOWN_COMP_MSK    (0x01 << PWMPLUS_IF_CH1_DOWN_COMP_POS)

#define PWMPLUS_IF_CH2_DOWN_COMP_POS    10   //PWMPLUS通道2向下计数到达比较点中断状态
#define PWMPLUS_IF_CH2_DOWN_COMP_MSK    (0x01 << PWMPLUS_IF_CH2_DOWN_COMP_POS)

#define PWMPLUS_IF_DOWN_OVF_POS         11   //PWMPLUS向下计数周期溢出中断状态
#define PWMPLUS_IF_DOWN_OVF_MSK         (0x01 << PWMPLUS_IF_DOWN_OVF_POS)

#define PWMPLUS_IF_DOWN_TRIG_POS        12   //PWMPLUS向下计数到达触发点中断状态
#define PWMPLUS_IF_DOWN_TRIG_MSK        (0x01 << PWMPLUS_IF_DOWN_TRIG_POS)

#define PWMPLUS_IF_BRK0_POS             16   //PWMPLUS刹车0中断状态
#define PWMPLUS_IF_BRK0_MSK             (0x01 << PWMPLUS_IF_BRK0_POS)

#define PWMPLUS_IF_BRK1_POS             17   //PWMPLUS刹车1中断状态
#define PWMPLUS_IF_BRK1_MSK             (0x01 << PWMPLUS_IF_BRK1_POS)

#define PWMPLUS_IF_BRK2_POS             18   //PWMPLUS刹车2中断状态
#define PWMPLUS_IF_BRK2_MSK             (0x01 << PWMPLUS_IF_BRK2_POS)

#define PWMPLUS_IF_RELOAD_POS           19   //PWMPLUS自动装载中断状态
#define PWMPLUS_IF_RELOAD_MSK           (0x01 << PWMPLUS_IF_RELOAD_POS)


#define PWMPLUS_SWLOAD_POS              0    //PWMPLUS软件LOAD
#define PWMPLUS_SWLOAD_MSK              (0x01 << PWMPLUS_SWLOAD_POS)


#define PWMPLUS_MSK_EN_CH0_POS         0    //PWMPLUS通道0屏蔽使能
#define PWMPLUS_MSK_EN_CH0_MSK         (0x01 << PWMPLUS_MSK_EN_CH0_POS)

#define PWMPLUS_MSK_EN_CH0N_POS        1    //PWMPLUS通道0N屏蔽使能
#define PWMPLUS_MSK_EN_CH0N_MSK        (0x01 << PWMPLUS_MSK_EN_CH0N_POS)

#define PWMPLUS_MSK_EN_CH1_POS         2    //PWMPLUS通道1屏蔽使能
#define PWMPLUS_MSK_EN_CH1_MSK         (0x01 << PWMPLUS_MSK_EN_CH1_POS)

#define PWMPLUS_MSK_EN_CH1N_POS        3    //PWMPLUS通道1N屏蔽使能
#define PWMPLUS_MSK_EN_CH1N_MSK        (0x01 << PWMPLUS_MSK_EN_CH1N_POS)

#define PWMPLUS_MSK_EN_CH2_POS         4    //PWMPLUS通道2屏蔽使能
#define PWMPLUS_MSK_EN_CH2_MSK         (0x01 << PWMPLUS_MSK_EN_CH2_POS)

#define PWMPLUS_MSK_EN_CH2N_POS        5    //PWMPLUS通道2N屏蔽使能
#define PWMPLUS_MSK_EN_CH2N_MSK        (0x01 << PWMPLUS_MSK_EN_CH2N_POS)


#define PWMPLUS_CNT_STATE_CNT_POS      0    //PWMPLUS当前计数值
#define PWMPLUS_CNT_STATE_CNT_MSK      (0xFFFF << PWMPLUS_CNT_STATE_CNT_POS)

#define PWMPLUS_CNT_STATE_DIR_POS      16    //PWMPLUS当前计数方向
#define PWMPLUS_CNT_STATE_DIR_MSK      (0x01 << PWMPLUS_CNT_STATE_DIR_POS)

#define PWMPLUS_CNT_STATE_STATE_POS    17    //PWMPLUS计数器工作状态
#define PWMPLUS_CNT_STATE_STATE_MSK    (0x01 << PWMPLUS_CNT_STATE_STATE_POS)

#define PWMPLUS_BRK0_STATE_POS         0     //PWMPLUS刹车0输入信号当前状态
#define PWMPLUS_BRK0_STATE_MSK         (0x01 << PWMPLUS_BRK0_STATE_POS)

#define PWMPLUS_BRK1_STATE_POS         1     //PWMPLUS刹车1输入信号当前状态
#define PWMPLUS_BRK1_STATE_MSK         (0x01 << PWMPLUS_BRK1_STATE_POS)



typedef struct {
	__IO uint32_t CFG;        //控制寄存器

	__IO uint32_t IE;         //中断使能

	__IO uint32_t IF;         //中断状态 
	
	uint32_t RESERVED[1];
	
	__IO uint32_t MS;         //秒标初始值
	
	__IO uint32_t TR;         //时间寄存器
	
	__IO uint32_t DR;         //日期寄存器
	
	__IO uint32_t AR;         //闹钟寄存器
	
	__IO uint32_t TSTR;       //当前时间寄存器
	
	__IO uint32_t TSDR;       //当前日期寄存器
	
	__IO uint32_t TSMR;       //当前秒标寄存器 
	
	__IO uint32_t VALID;      //当前时间有效标志寄存器
	
} RTC_TypeDef;


#define RTC_CFG_RTC_EN_POS     0      //RTC使能位
#define RTC_CFG_RTC_EN_MSK     (0x01 << RTC_CFG_RTC_EN_POS)

#define RTC_CFG_ALM_EN_POS     1      //闹钟使能位
#define RTC_CFG_ALM_EN_MSK     (0x01 << RTC_CFG_ALM_EN_POS)

#define RTC_CFG_LOAD_EN_POS    2      //加载寄存器TR和DR设定值使能位
#define RTC_CFG_LOAD_EN_MSK    (0x01 << RTC_CFG_LOAD_EN_POS)


#define RTC_IE_SEC_POS         0      //秒中断使能
#define RTC_IE_SEC_MSK         (0x01 << RTC_IE_SEC_POS)

#define RTC_IE_MIN_POS         1      //分钟中断使能
#define RTC_IE_MIN_MSK         (0x01 << RTC_IE_MIN_POS)

#define RTC_IE_HOUR_POS        2      //小时中断使能
#define RTC_IE_HOUR_MSK        (0x01 << RTC_IE_HOUR_POS)

#define RTC_IE_DATE_POS        3      //日中断使能
#define RTC_IE_DATE_MSK        (0x01 << RTC_IE_DATE_POS)

#define RTC_IE_ALM_POS         4      //闹钟中断使能
#define RTC_IE_ALM_MSK         (0x01 << RTC_IE_ALM_POS)

#define RTC_IE_MS_POS          5      //毫秒中断使能
#define RTC_IE_MS_MSK          (0x01 << RTC_IE_MS_POS)


#define RTC_IF_SEC_POS         0      //秒中断状态
#define RTC_IF_SEC_MSK         (0x01 << RTC_IF_SEC_POS)

#define RTC_IF_MIN_POS         1      //分钟中断状态
#define RTC_IF_MIN_MSK         (0x01 << RTC_IF_MIN_POS)

#define RTC_IF_HOUR_POS        2      //小时中断状态
#define RTC_IF_HOUR_MSK        (0x01 << RTC_IF_HOUR_POS)

#define RTC_IF_DATE_POS        3      //日中断状态
#define RTC_IF_DATE_MSK        (0x01 << RTC_IF_DATE_POS)

#define RTC_IF_ALM_POS         4      //闹钟中断状态
#define RTC_IF_ALM_MSK         (0x01 << RTC_IF_ALM_POS)

#define RTC_IF_MS_POS          5      //毫秒中断状态
#define RTC_IF_MS_MSK          (0x01 << RTC_IF_MS_POS)

#define RTC_IF_TIME_ERR_POS    8      //时间设定有效标志
#define RTC_IF_TIME_ERR_MSK    (0x01 << RTC_IF_TIME_ERR_POS)

#define RTC_IF_ALM_ERR_POS     9     //闹钟设定有效标志
#define RTC_IF_ALM_ERR_MSK     (0x01 << RTC_IF_ALM_ERR_POS)


#define RTC_MS_PRE_ROUND_POS         0      //预分频整数部分
#define RTC_MS_PRE_ROUND_MSK         (0xFFFFF << RTC_MS_PRE_ROUND_POS) 
                                     
#define RTC_MS_PRE_DECIMAL_POS       20     //预分频小数部分
#define RTC_MS_PRE_DECIMAL_MSK       (0xF << RTC_MS_PRE_DECIMAL_POS) 
                                     
#define RTC_MS_PRE_PERIOD_POS        24     //小数计算周期选择
#define RTC_MS_PRE_PERIOD_MSK        (0x1 << RTC_MS_PRE_PERIOD_POS) 


#define RTC_TR_BCD_SEC_POS           0     //秒钟的个位数  BCD码
#define RTC_TR_BCD_SEC_MSK           (0xF << RTC_TR_BCD_SEC_POS) 

#define RTC_TR_BCD_SEC_DEC_POS       4     //秒钟的十位数  BCD码
#define RTC_TR_BCD_SEC_DEC_MSK       (0x7 << RTC_TR_BCD_SEC_DEC_POS) 

#define RTC_TR_BCD_MIN_POS           8     //分钟的个位数  BCD码
#define RTC_TR_BCD_MIN_MSK           (0xF << RTC_TR_BCD_MIN_POS) 

#define RTC_TR_BCD_MIN_DEC_POS       12     //分钟的十位数  BCD码
#define RTC_TR_BCD_MIN_DEC_MSK       (0x7 << RTC_TR_BCD_MIN_DEC_POS) 

#define RTC_TR_BCD_HOUR_POS          16     //小时的个位数  BCD码
#define RTC_TR_BCD_HOUR_MSK          (0xF << RTC_TR_BCD_HOUR_POS) 

#define RTC_TR_BCD_HOUR_DEC_POS      20     //小时的十位数  BCD码
#define RTC_TR_BCD_HOUR_DEC_MSK      (0x3 << RTC_TR_BCD_HOUR_DEC_POS) 

#define RTC_TR_BCD_WEEK_POS          24     //星期的BCD码
#define RTC_TR_BCD_WEEK_MSK          (0x7 << RTC_TR_BCD_WEEK_POS) 


#define RTC_DR_BCD_DATE_POS          0      //日期的个位数 BCD码
#define RTC_DR_BCD_DATE_MSK          (0xF << RTC_DR_BCD_DATE_POS) 

#define RTC_DR_BCD_DATE_DEC_POS      4      //日期的十位数 BCD码
#define RTC_DR_BCD_DATE_DEC_MSK      (0x3 << RTC_DR_BCD_DATE_DEC_POS) 

#define RTC_DR_BCD_MONTH_POS         8      //月份的个位数 BCD码
#define RTC_DR_BCD_MONTH_MSK         (0xF << RTC_DR_BCD_MONTH_POS) 

#define RTC_DR_BCD_MONTH_DEC_POS     12     //月份的十位数 BCD码
#define RTC_DR_BCD_MONTH_DEC_MSK     (0x1 << RTC_DR_BCD_MONTH_DEC_POS) 

#define RTC_DR_BCD_YEAR_POS          16     //年的个位数 BCD码
#define RTC_DR_BCD_YEAR_MSK          (0xF << RTC_DR_BCD_YEAR_POS) 

#define RTC_DR_BCD_YEAR_DEC_POS      20     //年的十位数 BCD码
#define RTC_DR_BCD_YEAR_DEC_MSK      (0x3 << RTC_DR_BCD_YEAR_DEC_POS)


#define RTC_AR_BCD_SEC_POS           0     //闹钟 秒钟的个位数  BCD码
#define RTC_AR_BCD_SEC_MSK           (0xF << RTC_AR_BCD_SEC_POS) 

#define RTC_AR_BCD_SEC_DEC_POS       4     //闹钟 秒钟的十位数  BCD码
#define RTC_AR_BCD_SEC_DEC_MSK       (0x7 << RTC_AR_BCD_SEC_DEC_POS) 

#define RTC_AR_BCD_MIN_POS           8     //闹钟 分钟的个位数  BCD码
#define RTC_AR_BCD_MIN_MSK           (0xF << RTC_AR_BCD_MIN_POS) 

#define RTC_AR_BCD_MIN_DEC_POS       12     //闹钟 分钟的十位数  BCD码
#define RTC_AR_BCD_MIN_DEC_MSK       (0x7 << RTC_AR_BCD_MIN_DEC_POS) 

#define RTC_AR_BCD_HOUR_POS          16     //闹钟 小时的个位数  BCD码
#define RTC_AR_BCD_HOUR_MSK          (0xF << RTC_AR_BCD_HOUR_POS) 

#define RTC_AR_BCD_HOUR_DEC_POS      20     //闹钟 小时的十位数  BCD码
#define RTC_AR_BCD_HOUR_DEC_MSK      (0x3 << RTC_AR_BCD_HOUR_DEC_POS) 

#define RTC_AR_BCD_WEEK_POS          24     //闹钟 星期的BCD码
#define RTC_AR_BCD_WEEK_MSK          (0x7F << RTC_AR_BCD_WEEK_POS) 


#define RTC_TSTR_BCD_SEC_POS           0     //秒钟的个位数  BCD码    当前时间
#define RTC_TSTR_BCD_SEC_MSK           (0xF << RTC_TSTR_BCD_SEC_POS) 

#define RTC_TSTR_BCD_SEC_DEC_POS       4     //秒钟的十位数  BCD码    当前时间
#define RTC_TSTR_BCD_SEC_DEC_MSK       (0x7 << RTC_TSTR_BCD_SEC_DEC_POS) 

#define RTC_TSTR_BCD_MIN_POS           8     //分钟的个位数  BCD码    当前时间
#define RTC_TSTR_BCD_MIN_MSK           (0xF << RTC_TSTR_BCD_MIN_POS) 

#define RTC_TSTR_BCD_MIN_DEC_POS       12     //分钟的十位数  BCD码   当前时间
#define RTC_TSTR_BCD_MIN_DEC_MSK       (0x7 << RTC_TSTR_BCD_MIN_DEC_POS) 

#define RTC_TSTR_BCD_HOUR_POS          16     //小时的个位数  BCD码   当前时间
#define RTC_TSTR_BCD_HOUR_MSK          (0xF << RTC_TSTR_BCD_HOUR_POS) 

#define RTC_TSTR_BCD_HOUR_DEC_POS      20     //小时的十位数  BCD码   当前时间
#define RTC_TSTR_BCD_HOUR_DEC_MSK      (0x3 << RTC_TSTR_BCD_HOUR_DEC_POS) 

#define RTC_TSTR_BCD_WEEK_POS          24     //星期的BCD码           当前时间
#define RTC_TSTR_BCD_WEEK_MSK          (0x7 << RTC_TSTR_BCD_WEEK_POS) 


#define RTC_TSDR_BCD_DATE_POS          0      //日期的个位数 BCD码        当前时间
#define RTC_TSDR_BCD_DATE_MSK          (0xF << RTC_TSDR_BCD_DATE_POS) 
 
#define RTC_TSDR_BCD_DATE_DEC_POS      4      //日期的十位数 BCD码        当前时间
#define RTC_TSDR_BCD_DATE_DEC_MSK      (0x3 << RTC_TSDR_BCD_DATE_DEC_POS) 

#define RTC_TSDR_BCD_MOUTH_POS         8      //月份的个位数 BCD码        当前时间
#define RTC_TSDR_BCD_MOUTH_MSK         (0xF << RTC_TSDR_BCD_MOUTH_POS) 

#define RTC_TSDR_BCD_MOUTH_DEC_POS     12     //月份的十位数 BCD码        当前时间
#define RTC_TSDR_BCD_MOUTH_DEC_MSK     (0x1 << RTC_TSDR_BCD_MOUTH_DEC_POS) 

#define RTC_TSDR_BCD_YEAR_POS          16     //年的个位数 BCD码          当前时间
#define RTC_TSDR_BCD_YEAR_MSK          (0xF << RTC_TSDR_BCD_YEAR_POS) 
 
#define RTC_TSDR_BCD_YEAR_DEC_POS      20     //年的十位数 BCD码          当前时间
#define RTC_TSDR_BCD_YEAR_DEC_MSK      (0x3 << RTC_TSDR_BCD_YEAR_DEC_POS)

#define RTC_TSDR_LEAPYEAR_POS          24     //闰年标志位  1:闰年, 0:平年
#define RTC_TSDR_LEAPYEAR_MSK          (0x1 << RTC_TSDR_LEAPYEAR_POS)


#define RTC_TSMS_CNT_20_POS            0     //秒标当前计数值
#define RTC_TSMS_CNT_20_MSK            (0xFFFFF << RTC_TSMS_CNT_20_POS) 


#define RTC_CUR_VALID_POS              0     //当前时间有效标志位  1:有效, 2:无效
#define RTC_CUR_VALID_MSK              (0x1 << RTC_CUR_VALID_POS) 


typedef struct {
	
	__IO uint32_t CTRL;       //控制寄存器
	
	__IO uint32_t BAUD;       //波特率配置寄存器
	
	__IO uint32_t TDR;        //发送数据寄存器
	
	__IO uint32_t RDR;        //接收数据寄存器
	
	__IO uint32_t IE;         //中断使能寄存器  
	
	__IO uint32_t IF;         //中断状态寄存器
	
	__IO uint32_t FIFO;       //FIFO控制寄存器
	
	__IO uint32_t FC;         //流控配置寄存器 
	
	__IO uint32_t RXTO;       //接收超时配置寄存器 
		
} UART_TypeDef;


#define UART_CTRL_EN_POS         0       //串口使能
#define UART_CTRL_EN_MSK         (0x01 << UART_CTRL_EN_POS)

#define UART_CTRL_RXEN_POS       1       //串口接收使能
#define UART_CTRL_RXEN_MSK       (0x01 << UART_CTRL_RXEN_POS)

#define UART_CTRL_TXEN_POS       2       //串口发送使能
#define UART_CTRL_TXEN_MSK       (0x01 << UART_CTRL_TXEN_POS)

#define UART_CTRL_RXDMAEN_POS    3       //串口接收DMA传输使能
#define UART_CTRL_RXDMAEN_MSK    (0x01 << UART_CTRL_RXDMAEN_POS)

#define UART_CTRL_TXDMAEN_POS    4       //串口发送DMA传输使能
#define UART_CTRL_TXDMAEN_MSK    (0x01 << UART_CTRL_TXDMAEN_POS)

#define UART_CTRL_NINEBIT_POS    5       //9bit数据模式使能
#define UART_CTRL_NINEBIT_MSK    (0x01 << UART_CTRL_NINEBIT_POS)

#define UART_CTRL_PARITY_POS     6       //奇偶校验
#define UART_CTRL_PARITY_MSK     (0x07 << UART_CTRL_PARITY_POS)

#define UART_CTRL_STOP_POS       9       //停止位长度选择
#define UART_CTRL_STOP_MSK       (0x03 << UART_CTRL_STOP_POS)

#define UART_CTRL_ABRDEN_POS     11      //自动波特率检测使能
#define UART_CTRL_ABRDEN_MSK     (0x01 << UART_CTRL_ABRDEN_POS)

#define UART_CTRL_ABRDBIT_POS    12      //自动波特率检测位长配置
#define UART_CTRL_ABRDBIT_MSK    (0x03 << UART_CTRL_ABRDBIT_POS)

#define UART_CTRL_TXDLY_POS      14      //发送延迟时间配置
#define UART_CTRL_TXDLY_MSK      (0x07 << UART_CTRL_TXDLY_POS)

#define UART_BAUD_POS            0       //波特率配置数据
#define UART_BAUD_MSK            (0xFFFF << UART_BAUD_POS)

#define UART_TDR_POS             0       //发送数据寄存器
#define UART_TDR_MSK             (0x1FF << UART_TDR_POS)

#define UART_RDR_POS             0       //接收数据寄存器
#define UART_RDR_MSK             (0x1FF << UART_RDR_POS)


#define UART_IE_TXDONE_POS       2       //数据全部发送完成中断使能
#define UART_IE_TXDONE_MSK       (0x01 << UART_IE_TXDONE_POS)

#define UART_IE_PARITYE_POS      3       //接收数据出现奇偶校验错误中断使能
#define UART_IE_PARITYE_MSK      (0x01 << UART_IE_PARITYE_POS)

#define UART_IE_STOPE_POS        4       //接收数据出现停止位错误中断使能
#define UART_IE_STOPE_MSK        (0x01 << UART_IE_STOPE_POS)

#define UART_IE_RXTO_POS         5       //接收超时中断使能
#define UART_IE_RXTO_MSK         (0x01 << UART_IE_RXTO_POS)

#define UART_IE_RXFIFO_POS       6       //接收FIFO中接收的数据达到了设定的水位中断使能
#define UART_IE_RXFIFO_MSK       (0x01 << UART_IE_RXFIFO_POS)   

#define UART_IE_TXFIFO_POS       7       //发送FIFO中接收的数据达到了设定的水位中断使能
#define UART_IE_TXFIFO_MSK       (0x01 << UART_IE_TXFIFO_POS)  

#define UART_IE_RXFIFO_OVF_POS   8       //接收FIFO溢出中断使能
#define UART_IE_RXFIFO_OVF_MSK   (0x01 << UART_IE_RXFIFO_OVF_POS)   

#define UART_IE_ABRD_OVF_POS     9       //自动波特率检测计数器溢出中断使能
#define UART_IE_ABRD_OVF_MSK     (0x01 << UART_IE_ABRD_OVF_POS) 


#define UART_IF_TXDONE_POS       2       //数据全部发送完成中断状态
#define UART_IF_TXDONE_MSK       (0x01 << UART_IF_TXDONE_POS)

#define UART_IF_PARITYE_POS      3       //接收数据出现奇偶校验错误中断状态
#define UART_IF_PARITYE_MSK      (0x01 << UART_IF_PARITYE_POS)

#define UART_IF_STOPE_POS        4       //接收数据出现停止位错误中断状态
#define UART_IF_STOPE_MSK        (0x01 << UART_IF_STOPE_POS)

#define UART_IF_RXTO_POS         5       //接收超时中断状态
#define UART_IF_RXTO_MSK         (0x01 << UART_IF_RXTO_POS)

#define UART_IF_RXFIFO_POS       6       //接收FIFO中接收的数据达到了设定的水位中断状态
#define UART_IF_RXFIFO_MSK       (0x01 << UART_IF_RXFIFO_POS)   

#define UART_IF_TXFIFO_POS       7       //发送FIFO中接收的数据达到了设定的水位中断状态
#define UART_IF_TXFIFO_MSK       (0x01 << UART_IF_TXFIFO_POS)  

#define UART_IF_RXFIFO_OVF_POS   8       //接收FIFO溢出中断状态
#define UART_IF_RXFIFO_OVF_MSK   (0x01 << UART_IF_RXFIFO_OVF_POS)   

#define UART_IF_ABRD_OVF_POS     9       //自动波特率检测计数器溢出中断状态
#define UART_IF_ABRD_OVF_MSK     (0x01 << UART_IF_ABRD_OVF_POS) 

#define UART_IF_RXFIFO_EMPTY_POS    10       //接收FIFO空标志
#define UART_IF_RXFIFO_EMPTY_MSK    (0x01 << UART_IF_RXFIFO_EMPTY_POS) 

#define UART_IF_RXFIFO_FULL_POS     11       //接收FIFO满标志
#define UART_IF_RXFIFO_FULL_MSK     (0x01 << UART_IF_RXFIFO_FULL_POS) 

#define UART_IF_RXFIFO_HFULL_POS    12      //接收FIFO半满标志
#define UART_IF_RXFIFO_HFULL_MSK    (0x01 << UART_IF_RXFIFO_HFULL_POS) 

#define UART_IF_TXFIFO_EMPTY_POS    13      //发送FIFO空标志
#define UART_IF_TXFIFO_EMPTY_MSK    (0x01 << UART_IF_TXFIFO_EMPTY_POS) 

#define UART_IF_TXFIFO_FULL_POS     14      //发送FIFO满标志
#define UART_IF_TXFIFO_FULL_MSK     (0x01 << UART_IF_TXFIFO_FULL_POS) 

#define UART_IF_TXFIFO_HFULL_POS    15      //发送FIFO半满标志
#define UART_IF_TXFIFO_HFULL_MSK    (0x01 << UART_IF_TXFIFO_HFULL_POS) 

#define UART_IF_TXBUSY_POS          16      //数据发送忙标志
#define UART_IF_TXBUSY_MSK          (0x01 << UART_IF_TXBUSY_POS) 

#define UART_IF_RX_LEVEL_POS        17      //接收FIFO水位标志信号
#define UART_IF_RX_LEVEL_MSK        (0x07 << UART_IF_RX_LEVEL_POS) 

#define UART_IF_TX_LEVEL_POS        20      //发送FIFO水位标志信号
#define UART_IF_TX_LEVEL_MSK        (0x07 << UART_IF_TX_LEVEL_POS) 


#define UART_FIFO_RF_LEVEL_POS      0       //RXFIFO产生中断的水位设置
#define UART_FIFO_RF_LEVEL_MSK      (0x07 << UART_FIFO_RF_LEVEL_POS)

#define UART_FIFO_TF_LEVEL_POS      3       //TXFIFO产生中断的水位设置
#define UART_FIFO_TF_LEVEL_MSK      (0x07 << UART_FIFO_TF_LEVEL_POS)

#define UART_FIFO_RF_CLR_POS        6       //RXFIFO清除使能
#define UART_FIFO_RF_CLR_MSK        (0x01 << UART_FIFO_RF_CLR_POS)

#define UART_FIFO_TF_CLR_POS        7       //TXFIFO清除使能
#define UART_FIFO_TF_CLR_MSK        (0x01 << UART_FIFO_TF_CLR_POS)


#define UART_FC_CTS_EN_POS          0       //CTS流控使能
#define UART_FC_CTS_EN_MSK          (0x01 << UART_FC_CTS_EN_POS)

#define UART_FC_RTS_EN_POS          1       //RTS流控使能
#define UART_FC_RTS_EN_MSK          (0x01 << UART_FC_RTS_EN_POS)

#define UART_FC_CTS_POL_POS         2       //CTS信号极性配置
#define UART_FC_CTS_POL_MSK         (0x01 << UART_FC_CTS_POL_POS)

#define UART_FC_RTS_POL_POS         3       //RTS信号极性配置
#define UART_FC_RTS_POL_MSK         (0x01 << UART_FC_RTS_POL_POS)

#define UART_FC_CTS_SIGNAL_POS      4       //CTS当前信号状态
#define UART_FC_CTS_SIGNAL_MSK      (0x01 << UART_FC_CTS_SIGNAL_POS)

#define UART_FC_RTS_SIGNAL_POS      5       //RTS当前信号状态
#define UART_FC_RTS_SIGNAL_MSK      (0x01 << UART_FC_RTS_SIGNAL_POS)


#define UART_RXTO_POS               0       //接收数据超时触发比较值
#define UART_RXTO_MSK               (0xFF << UART_RXTO_POS)



typedef struct {
	__IO uint32_t CTRL;       //控制寄存器

	__IO uint32_t WDATA;      //写数据寄存器

	__IO uint32_t RDATA;      //读数据寄存器

	uint32_t RESERVED1[1];
	
	__IO uint32_t IE;         //中断使能

	__IO uint32_t IF;         //中断状态 
	
	__IO uint32_t FIFOST;     //FIFO状态 
	
} SPI_TypeDef;


#define SPI_CTRL_CLKDIV_POS     0           //Clock Divider, SPI工作时钟 = SYS_Freq/pow(2, CLKDIV+2)
#define SPI_CTRL_CLKDIV_MSK     (0x07 << SPI_CTRL_CLKDIV_POS)

#define SPI_CTRL_EN_POS         3           //SPI系统使能
#define SPI_CTRL_EN_MSK         (0x01 << SPI_CTRL_EN_POS)

#define SPI_CTRL_CPHA_POS		4		    //0 在SCLK的第一个跳变沿采样数据	1 在SCLK的第二个跳变沿采样数据
#define SPI_CTRL_CPHA_MSK		(0x01 << SPI_CTRL_CPHA_POS)

#define SPI_CTRL_CPOL_POS		5		    //0 空闲状态下SCLK为低电平		  1 空闲状态下SCLK为高电平
#define SPI_CTRL_CPOL_MSK		(0x01 << SPI_CTRL_CPOL_POS)

#define SPI_CTRL_MSTR_POS		6		    //Master, 1 主模式	0 从模式
#define SPI_CTRL_MSTR_MSK		(0x01 << SPI_CTRL_MSTR_POS)

#define SPI_CTRL_LSBF_POS		7		    //数据传输顺序选择  0 MSB Fisrt  1 LSB Fisrt
#define SPI_CTRL_LSBF_MSK		(0x01 << SPI_CTRL_LSBF_POS)

#define SPI_CTRL_DATAHOLD_POS   8           //从模式下CPHA为1时，数据保持时间配置寄存器
#define SPI_CTRL_DATAHOLD_MSK   (0x0F << SPI_CTRL_DATAHOLD_POS)

#define SPI_CTRL_MST_SSN_POS    12          //主机模式下，SSN输出   默认输出高电平
#define SPI_CTRL_MST_SSN_MSK    (0x01 << SPI_CTRL_MST_SSN_POS)

#define SPI_CTRL_RX_DMAEN_POS   13          //接收DMA控制使能
#define SPI_CTRL_RX_DMAEN_MSK   (0x01 << SPI_CTRL_RX_DMAEN_POS)

#define SPI_CTRL_TX_DMAEN_POS   14          //发送DMA控制使能
#define SPI_CTRL_TX_DMAEN_MSK   (0x01 << SPI_CTRL_TX_DMAEN_POS)

#define SPI_CTRL_RF_CLR_POS     15         //RXFIFO清除使能
#define SPI_CTRL_RF_CLR_MSK     (0x01 << SPI_CTRL_RF_CLR_POS)

#define SPI_CTRL_TF_CLR_POS     16         //TXFIFO清除使能
#define SPI_CTRL_TF_CLR_MSK     (0x01 << SPI_CTRL_TF_CLR_POS)


#define SPI_IE_RXFIFO_OVF_POS      0        //接收FIFO溢出中断使能
#define SPI_IE_RXFIFO_OVF_MSK      (0x01 << SPI_IE_RXFIFO_OVF_POS)

#define SPI_IE_RXFIFO_FULL_POS     1        //接收FIFO满中断使能
#define SPI_IE_RXFIFO_FULL_MSK     (0x01 << SPI_IE_RXFIFO_FULL_POS)

#define SPI_IE_RXFIFO_HFULL_POS    2        //接收FIFO半满中断使能
#define SPI_IE_RXFIFO_HFULL_MSK    (0x01 << SPI_IE_RXFIFO_HFULL_POS)

#define SPI_IE_TXFIFO_EMPTY_POS    3        //发送FIFO空中断使能
#define SPI_IE_TXFIFO_EMPTY_MSK    (0x01 << SPI_IE_TXFIFO_EMPTY_POS)

#define SPI_IE_TXFIFO_HFULL_POS    4        //发送FIFO半满中断使能
#define SPI_IE_TXFIFO_HFULL_MSK    (0x01 << SPI_IE_TXFIFO_HFULL_POS)


#define SPI_IF_RXFIFO_OVF_POS      0        //接收FIFO溢出中断状态
#define SPI_IF_RXFIFO_OVF_MSK      (0x01 << SPI_IF_RXFIFO_OVF_POS)

#define SPI_IF_RXFIFO_FULL_POS     1        //接收FIFO满中断状态
#define SPI_IF_RXFIFO_FULL_MSK     (0x01 << SPI_IF_RXFIFO_FULL_POS)

#define SPI_IF_RXFIFO_HFULL_POS    2        //接收FIFO半满中断状态
#define SPI_IF_RXFIFO_HFULL_MSK    (0x01 << SPI_IF_RXFIFO_HFULL_POS)

#define SPI_IF_TXFIFO_EMPTY_POS    3        //发送FIFO空中断状态
#define SPI_IF_TXFIFO_EMPTY_MSK    (0x01 << SPI_IF_TXFIFO_EMPTY_POS)

#define SPI_IF_TXFIFO_HFULL_POS    4        //发送FIFO半满中断状态
#define SPI_IF_TXFIFO_HFULL_MSK    (0x01 << SPI_IF_TXFIFO_HFULL_POS)

#define SPI_IF_TXFIFO_BUSY_POS     5        //SPI 传输忙状态标志
#define SPI_IF_TXFIFO_BUSY_MSK     (0x01 << SPI_IF_TXFIFO_BUSY_POS)

#define SPI_FIFOST_RXFIFO_EMPTY_POS      0        //接收FIFO空状态
#define SPI_FIFOST_RXFIFO_EMPTY_MSK      (0x01 << SPI_FIFOST_RXFIFO_EMPTY_POS)

#define SPI_FIFOST_RXFIFO_FULL_POS       1        //接收FIFO满状态
#define SPI_FIFOST_RXFIFO_FULL_MSK       (0x01 << SPI_FIFOST_RXFIFO_FULL_POS)

#define SPI_FIFOST_RXFIFO_HFULL_POS      2        //接收FIFO半满状态
#define SPI_FIFOST_RXFIFO_HFULL_MSK      (0x01 << SPI_FIFOST_RXFIFO_HFULL_POS)

#define SPI_FIFOST_TXFIFO_EMPTY_POS      3        //发送FIFO空状态
#define SPI_FIFOST_TXFIFO_EMPTY_MSK      (0x01 << SPI_FIFOST_TXFIFO_EMPTY_POS)

#define SPI_FIFOST_TXFIFO_FULL_POS       4        //发送FIFO满状态
#define SPI_FIFOST_TXFIFO_FULL_MSK       (0x01 << SPI_FIFOST_TXFIFO_FULL_POS)

#define SPI_FIFOST_TXFIFO_HFULL_POS      5        //发送FIFO半满状态
#define SPI_FIFOST_TXFIFO_HFULL_MSK      (0x01 << SPI_FIFOST_TXFIFO_HFULL_POS)

#define SPI_FIFOST_RX_LEVEL_POS          6        //接收FIFO水位标志信号
#define SPI_FIFOST_RX_LEVEL_MSK          (0x07 << SPI_FIFOST_RX_LEVEL_POS) 

#define SPI_FIFOST_TX_LEVEL_POS          9       //发送FIFO水位标志信号
#define SPI_FIFOST_TX_LEVEL_MSK          (0x07 << SPI_FIFOST_TX_LEVEL_POS) 


typedef struct {
	
	__IO uint32_t CCFG;          //通用配置寄存器
	
	__IO uint32_t CST;           //通用状态寄存器
	
	__IO uint32_t CTRANS;        //通用传输寄存器
	
	__IO uint32_t RXDATA;        //接收数据寄存器
	
	__IO uint32_t TXDATA;        //发送数据寄存器
	
	__IO uint32_t IE;            //中断使能寄存器
	
	__IO uint32_t IF;            //中断状态寄存器
	
	uint32_t RESERVED1[1];
	
	__IO uint32_t MCTRL;         //主机模式控制寄存器
	
	__IO uint32_t MSPC;          //时序配置寄存器
	
	uint32_t RESERVED2[2];
	
	__IO uint32_t SCTRL;         //从机模式控制寄存器 
	
	__IO uint32_t SADDR;         //从机地址寄存器
	
} IIC_TypeDef;


#define IIC_CCFG_EN_POS         0     //IIC使能
#define IIC_CCFG_EN_MSK         (0x01 << IIC_CCFG_EN_POS)

#define IIC_CCFG_MODE_POS       1     //模式选择
#define IIC_CCFG_MODE_MSK       (0x01 << IIC_CCFG_MODE_POS)

#define IIC_CCFG_HS_POS         2     //HIGH SPEED MODE
#define IIC_CCFG_HS_MSK         (0x01 << IIC_CCFG_HS_POS)

#define IIC_CCFG_DNF_POS        3     //数字滤波
#define IIC_CCFG_DNF_MSK        (0x0F << IIC_CCFG_DNF_POS)

#define IIC_CST_BUSY_POS        0     //总线忙状态
#define IIC_CST_BUSY_MSK        (0x01 << IIC_CST_BUSY_POS)

#define IIC_CST_SCL_POS         1     //SCL状态
#define IIC_CST_SCL_MSK         (0x01 << IIC_CST_SCL_POS)

#define IIC_CST_SDA_POS         2     //SDA状态
#define IIC_CST_SDA_MSK         (0x01 << IIC_CST_SDA_POS)

#define IIC_CST_SLV_RD_POS      9     //SLAVE模式读状态
#define IIC_CST_SLV_RD_MSK      (0x01 << IIC_CST_SLV_RD_POS)

#define IIC_CST_SLV_WR_POS      10    //SLAVE模式读状态
#define IIC_CST_SLV_WR_MSK      (0x01 << IIC_CST_SLV_WR_POS)

#define IIC_CST_SLV_BUSY_POS    11    //SLAVE时钟STRETCH忙状态
#define IIC_CST_SLV_BUSY_MSK    (0x01 << IIC_CST_SLV_BUSY_POS)

#define IIC_CST_SLV_RXDT_POS    12    //SLAVE接收到的数据类型
#define IIC_CST_SLV_RXDT_MSK    (0x03 << IIC_CST_SLV_RXDT_POS)


#define IIC_CTRANS_TX_ACK_POS   0     //当作为接收方时，发送ACK或NACK
#define IIC_CTRANS_TX_ACK_MSK   (0x01 << IIC_CTRANS_TX_ACK_POS)

#define IIC_CTRANS_RX_ACK_POS   1     //当作为发送方时，接收到ACK或NACK
#define IIC_CTRANS_RX_ACK_MSK   (0x01 << IIC_CTRANS_RX_ACK_POS)

#define IIC_CTRANS_TXD_CLR_POS  2     //发送数据寄存器清空
#define IIC_CTRANS_TXD_CLR_MSK  (0x01 << IIC_CTRANS_TXD_CLR_POS)


#define IIC_RXDATA_POS          0     //接收数据寄存器
#define IIC_RXDATA_MSK          (0xFF << IIC_RXDATA_POS)


#define IIC_TXDATA_POS          0     //发送数据寄存器
#define IIC_TXDATA_MSK          (0xFF << IIC_TXDATA_POS)


#define IIC_IE_RXOVF_POS        2     //接收数据寄存器溢出中断使能
#define IIC_IE_RXOVF_MSK        (0x01 << IIC_IE_RXOVF_POS)

#define IIC_IE_TXF_POS          3     //发送数据结束中断使能
#define IIC_IE_TXF_MSK          (0x01 << IIC_IE_TXF_POS)

#define IIC_IE_RXF_POS          4     //接收数据结束中断使能
#define IIC_IE_RXF_MSK          (0x01 << IIC_IE_RXF_POS)

#define IIC_IE_SLV_STA_POS      8     //SLAVE检测到START中断使能
#define IIC_IE_SLV_STA_MSK      (0x01 << IIC_IE_SLV_STA_POS)

#define IIC_IE_SLV_STO_POS      9     //SLAVE检测到STOP中断使能
#define IIC_IE_SLV_STO_MSK      (0x01 << IIC_IE_SLV_STO_POS)

#define IIC_IE_MLTO_POS         17     //MASTER SCL LOW超时中断使能
#define IIC_IE_MLTO_MSK         (0x01 << IIC_IE_MLTO_POS)


#define IIC_IF_TXE_POS          0     //发送数据寄存器空中断状态
#define IIC_IF_TXE_MSK          (0x01 << IIC_IF_TXE_POS)

#define IIC_IF_RXNE_POS         1     //接收数据寄存器非空中断状态
#define IIC_IF_RXNE_MSK         (0x01 << IIC_IF_RXNE_POS)

#define IIC_IF_RXOVF_POS        2     //接收数据寄存器溢出中断状态
#define IIC_IF_RXOVF_MSK        (0x01 << IIC_IF_RXOVF_POS)

#define IIC_IF_TXF_POS          3     //发送数据结束中断状态
#define IIC_IF_TXF_MSK          (0x01 << IIC_IF_TXF_POS)

#define IIC_IF_RXF_POS          4     //接收数据结束中断状态
#define IIC_IF_RXF_MSK          (0x01 << IIC_IF_RXF_POS)

#define IIC_IF_SLV_STA_POS      8     //SLAVE检测到START中断状态
#define IIC_IF_SLV_STA_MSK      (0x01 << IIC_IF_SLV_STA_POS)

#define IIC_IF_SLV_STO_POS      9     //SLAVE检测到STOP中断状态
#define IIC_IF_SLV_STO_MSK      (0x01 << IIC_IF_SLV_STO_POS)

#define IIC_IF_MLTO_POS         17     //MASTER SCL LOW超时中断状态
#define IIC_IF_MLTO_MSK         (0x01 << IIC_IF_MLTO_POS)


#define IIC_MCTRL_STA_POS       0      //产生START信号
#define IIC_MCTRL_STA_MSK       (0x01 << IIC_MCTRL_STA_POS)

#define IIC_MCTRL_RD_POS        1      //接收数据到RXDATA
#define IIC_MCTRL_RD_MSK        (0x01 << IIC_MCTRL_RD_POS)

#define IIC_MCTRL_WR_POS        2      //发送TXDATA中的数据
#define IIC_MCTRL_WR_MSK        (0x01 << IIC_MCTRL_WR_POS)

#define IIC_MCTRL_STO_POS       3      //产生STOP信号
#define IIC_MCTRL_STO_MSK       (0x01 << IIC_MCTRL_STO_POS)


#define IIC_MSPC_SCL_LOW_POS    0      //SCL时钟低电平时间配置
#define IIC_MSPC_SCL_LOW_MSK    (0xFF << IIC_MSPC_SCL_LOW_POS)

#define IIC_MSPC_SCL_HI_POS     8     //SCL时钟高电平时间配置
#define IIC_MSPC_SCL_HI_MSK     (0xFF << IIC_MSPC_SCL_HI_POS)

#define IIC_MSPC_CPD_POS        16    //时钟预分频
#define IIC_MSPC_CPD_MSK        (0xFF << IIC_MSPC_CPD_POS)

#define IIC_MSPC_DATAHOLD_POS   24    //SDA数据保持时间配置
#define IIC_MSPC_DATAHOLD_MSK   (0x0F << IIC_MSPC_DATAHOLD_POS)


#define IIC_SCTRL_ADMD_POS      0     //SLAVE地址模式选择
#define IIC_SCTRL_ADMD_MSK      (0x01 << IIC_SCTRL_ADMD_POS)

#define IIC_SCTRL_MCDE_POS      1     //MASTER CODE 检测使能
#define IIC_SCTRL_MCDE_MSK      (0x01 << IIC_SCTRL_MCDE_POS)

#define IIC_SCTRL_STRETCH_POS   2     //时钟STRETCH使能
#define IIC_SCTRL_STRETCH_MSK   (0x01 << IIC_SCTRL_STRETCH_POS)

#define IIC_SCTRL_ASDS_POS      3     //时钟STRETCH后数据建立时间自适应使能
#define IIC_SCTRL_ASDS_MSK      (0x01 << IIC_SCTRL_ASDS_POS)


#define IIC_SADDR_ADDR0_POS     0     //ADDR0
#define IIC_SADDR_ADDR0_MSK     (0x01 << IIC_SADDR_ADDR0_POS)

#define IIC_SADDR_ADDR1_7_POS   1     //ADDR1--7
#define IIC_SADDR_ADDR1_7_MSK   (0x7F << IIC_SADDR_ADDR1_7_POS)

#define IIC_SADDR_ADDR8_9_POS   8     //ADDR8--9
#define IIC_SADDR_ADDR8_9_MSK   (0x03 << IIC_SADDR_ADDR8_9_POS)

#define IIC_SADDR_MASK_ADDR0_POS     16  //SLAVE对应地址位掩码
#define IIC_SADDR_MASK_ADDR0_MSK     (0x01 << IIC_SADDR_MASK_ADDR0_POS)

#define IIC_SADDR_MASK_ADDR1_7_POS   17  //SLAVE对应地址位掩码
#define IIC_SADDR_MASK_ADDR1_7_MSK   (0x7F << IIC_SADDR_MASK_ADDR1_7_POS)


typedef struct {
	__IO uint32_t CFG;               //ADC配置寄存器      
	
	__IO uint32_t START;             //ADC启动寄存器  

	__IO uint32_t IE;                //ADC中断使能寄存器  
	
	__IO uint32_t IF;                //ADC中断状态寄存器  
	
 	struct {
		__IO uint32_t STAT;          //通道状态寄存器
		
		__IO uint32_t DATA;          //通道数据寄存器
	} CH[16];
	
	uint32_t RESERVED1[4];
	
	__IO uint32_t FIFO_STAT;         //FIFO状态寄存器
	
	__IO uint32_t FIFO_DATA;         //FIFO数据寄存器
	
	uint32_t RESERVED2[2];
	
	__IO uint32_t EXTTRIG_SEL;       //外部信号触发ADC选择寄存器
	
	uint32_t RESERVED3[15];
	
	__IO uint32_t CALIB_OFFSET;     //ADC校准OFFSET寄存器
	
	__IO uint32_t CALIB_KD;         //ADC校准KD寄存器
	
} ADC_TypeDef;


#define ADC_CFG_CH0_POS			    0		//通道0选中
#define ADC_CFG_CH0_MSK			    (0x01 << ADC_CFG_CH0_POS)

#define ADC_CFG_CH1_POS			    1		//通道1选中
#define ADC_CFG_CH1_MSK			    (0x01 << ADC_CFG_CH1_POS)

#define ADC_CFG_CH2_POS			    2		//通道2选中
#define ADC_CFG_CH2_MSK			    (0x01 << ADC_CFG_CH2_POS)

#define ADC_CFG_CH3_POS			    3		//通道3选中
#define ADC_CFG_CH3_MSK			    (0x01 << ADC_CFG_CH3_POS)

#define ADC_CFG_CH4_POS			    4		//通道4选中
#define ADC_CFG_CH4_MSK			    (0x01 << ADC_CFG_CH4_POS)

#define ADC_CFG_CH5_POS			    5		//通道5选中
#define ADC_CFG_CH5_MSK			    (0x01 << ADC_CFG_CH5_POS)

#define ADC_CFG_CH6_POS			    6		//通道6选中
#define ADC_CFG_CH6_MSK			    (0x01 << ADC_CFG_CH6_POS)
 
#define ADC_CFG_CH7_POS			    7		//通道7选中
#define ADC_CFG_CH7_MSK			    (0x01 << ADC_CFG_CH7_POS)

#define ADC_CFG_CH8_POS			    8		//通道8选中
#define ADC_CFG_CH8_MSK			    (0x01 << ADC_CFG_CH8_POS)

#define ADC_CFG_CH9_POS			    9		//通道9选中
#define ADC_CFG_CH9_MSK			    (0x01 << ADC_CFG_CH9_POS)

#define ADC_CFG_CH10_POS			10		//通道10选中
#define ADC_CFG_CH10_MSK			(0x01 << ADC_CFG_CH10_POS)

#define ADC_CFG_CH11_POS			11		//通道11选中
#define ADC_CFG_CH11_MSK			(0x01 << ADC_CFG_CH11_POS)

#define ADC_CFG_CH12_POS			12		//通道12选中
#define ADC_CFG_CH12_MSK			(0x01 << ADC_CFG_CH12_POS)

#define ADC_CFG_CH13_POS			13		//通道13选中
#define ADC_CFG_CH13_MSK			(0x01 << ADC_CFG_CH13_POS)

#define ADC_CFG_CH14_POS			14		//通道14选中
#define ADC_CFG_CH14_MSK			(0x01 << ADC_CFG_CH14_POS)

#define ADC_CFG_CH15_POS			15		//通道15选中
#define ADC_CFG_CH15_MSK			(0x01 << ADC_CFG_CH15_POS)

#define ADC_CFG_AVG_POS		        16		//0 1次采样	  1 2次采样取平均值	  2 4次采样取平均值	  3 8次采样取平均值	
#define ADC_CFG_AVG_MSK		        (0x03 << ADC_CFG_AVG_POS)

#define ADC_CFG_CONT_POS		    18		//Continuous conversion，只在软件启动模式下有效，0 单次转换，转换完成后START位自动清除停止转换
#define ADC_CFG_CONT_MSK		    (0x01 << ADC_CFG_CONT_POS)							//   1 连续转换，启动后一直采样、转换，直到软件清除START位

#define ADC_CFG_SMPL_SETUP_POS      19      //ADC外部采样时钟方式下采样建立时间   0:1  1:2  2:4  3:8  4:16  5:32  6:64  7:128
#define ADC_CFG_SMPL_SETUP_MSK      (0x07 << ADC_CFG_SPL_SETUP_POS)

#define ADC_CFG_MEM_MODE_POS        22      //ADC数据存储方式选择   0:FIFO模式   1:通道模式
#define ADC_CFG_MEM_MODE_MSK        (0x01 << ADC_CFG_MEM_MODE_POS)

#define ADC_CFG_SMPL_CLK_POS        23      //ADC采样模式选择    0:内部采样时钟  1:外部采样时钟
#define ADC_CFG_SMPL_CLK_MSK        (0x01 << ADC_CFG_SMPL_CLK_POS)

#define ADC_CFG_IN_SMPL_WIN_POS     24      //ADC内部采样时钟方式采样窗口设置   0:1Tclk   1:3Tclk   2:5Tclk   3:7Tclk  4:9Tclk  5:11Tclk  6:13Tclk  7:15Tclk
#define ADC_CFG_IN_SMPL_WIN_MSK     (0x07 << ADC_CFG_IN_SMPL_WIN_POS)

#define ADC_CFG_EN_POS              27      //ADC使能控制位   0:不使能  1:使能
#define ADC_CFG_EN_MSK              (0x01 << ADC_CFG_EN_POS)

#define ADC_CFG_TRIG_POS            28      //ADC触发源选择
#define ADC_CFG_TRIG_MSK            (0x01 << ADC_CFG_TRIG_POS)

#define ADC_CFG_DMAEN_POS           29      //DMA读取FIFO使能
#define ADC_CFG_DMAEN_MSK           (0x01 << ADC_CFG_DMAEN_POS)


#define ADC_START_START_POS         0      //ADC启动信号   0:不启动  1:启动
#define ADC_START_START_MSK         (0x01 << ADC_START_START_POS) 

#define ADC_START_BUSY_POS          1      //ADC忙状态   0:空闲  1:忙
#define ADC_START_BUSY_MSK          (0x01 << ADC_START_BUSY_POS) 

#define ADC_START_SOFT_RESET_POS    2      //ADC软复位使能位
#define ADC_START_SOFT_RESET_MSK    (0x01 << ADC_START_SOFT_RESET_POS) 

#define ADC_START_FIFOCLR_POS       3      //ADC FIFO清除使能
#define ADC_START_FIFOCLR_MSK       (0x01 << ADC_START_FIFOCLR_POS) 


#define ADC_IE_CH0EOC_POS			0		//CH0转换完成中断使能
#define ADC_IE_CH0EOC_MSK			(0x01 << ADC_IE_CH0EOC_POS)

#define ADC_IE_CH1EOC_POS			1		//CH1转换完成中断使能
#define ADC_IE_CH1EOC_MSK			(0x01 << ADC_IE_CH1EOC_POS)

#define ADC_IE_CH2EOC_POS			2		//CH2转换完成中断使能
#define ADC_IE_CH2EOC_MSK			(0x01 << ADC_IE_CH2EOC_POS)

#define ADC_IE_CH3EOC_POS			3		//CH3转换完成中断使能
#define ADC_IE_CH3EOC_MSK			(0x01 << ADC_IE_CH3EOC_POS)

#define ADC_IE_CH4EOC_POS			4		//CH4转换完成中断使能
#define ADC_IE_CH4EOC_MSK			(0x01 << ADC_IE_CH4EOC_POS)

#define ADC_IE_CH5EOC_POS			5		//CH5转换完成中断使能
#define ADC_IE_CH5EOC_MSK			(0x01 << ADC_IE_CH5EOC_POS)

#define ADC_IE_CH6EOC_POS			6		//CH6转换完成中断使能
#define ADC_IE_CH6EOC_MSK			(0x01 << ADC_IE_CH6EOC_POS)

#define ADC_IE_CH7EOC_POS			7		//CH7转换完成中断使能
#define ADC_IE_CH7EOC_MSK			(0x01 << ADC_IE_CH7EOC_POS)

#define ADC_IE_CH8EOC_POS			8		//CH8转换完成中断使能
#define ADC_IE_CH8EOC_MSK			(0x01 << ADC_IE_CH8EOC_POS)

#define ADC_IE_CH9EOC_POS			9		//CH9转换完成中断使能
#define ADC_IE_CH9EOC_MSK			(0x01 << ADC_IE_CH9EOC_POS)

#define ADC_IE_CH10EOC_POS			10		//CH10转换完成中断使能
#define ADC_IE_CH10EOC_MSK			(0x01 << ADC_IE_CH10EOC_POS)

#define ADC_IE_CH11EOC_POS			11		//CH11转换完成中断使能
#define ADC_IE_CH11EOC_MSK			(0x01 << ADC_IE_CH11EOC_POS)

#define ADC_IE_CH12EOC_POS			12		//CH12转换完成中断使能
#define ADC_IE_CH12EOC_MSK			(0x01 << ADC_IE_CH12EOC_POS)

#define ADC_IE_CH13EOC_POS			13		//CH13转换完成中断使能
#define ADC_IE_CH13EOC_MSK			(0x01 << ADC_IE_CH13EOC_POS)

#define ADC_IE_CH14EOC_POS			14		//CH4转换完成中断使能
#define ADC_IE_CH14EOC_MSK			(0x01 << ADC_IE_CH14EOC_POS)

#define ADC_IE_CH15EOC_POS			15		//CH15转换完成中断使能
#define ADC_IE_CH15EOC_MSK			(0x01 << ADC_IE_CH15EOC_POS)

#define ADC_IE_FIFO_FULL_POS	    16       //FIFO满中断使能
#define ADC_IE_FIFO_FULL_MSK	    (0x01 << ADC_IE_FIFO_FULL_POS)

#define ADC_IE_FIFO_HFULL_POS	    17       //FIFO半满中断使能
#define ADC_IE_FIFO_HFULL_MSK	    (0x01 << ADC_IE_FIFO_HFULL_POS)

#define ADC_IE_FIFO_OVF_POS			18		//FIFO溢出中断使能
#define ADC_IE_FIFO_OVF_MSK			(0x01 << ADC_IE_FIFO_OVF_POS)


#define ADC_IF_CH0EOC_POS			0		//CH0转换完成中断状态
#define ADC_IF_CH0EOC_MSK			(0x01 << ADC_IF_CH0EOC_POS)

#define ADC_IF_CH1EOC_POS			1		//CH1转换完成中断状态
#define ADC_IF_CH1EOC_MSK			(0x01 << ADC_IF_CH1EOC_POS)

#define ADC_IF_CH2EOC_POS			2		//CH2转换完成中断状态
#define ADC_IF_CH2EOC_MSK			(0x01 << ADC_IF_CH2EOC_POS)

#define ADC_IF_CH3EOC_POS			3		//CH3转换完成中断状态
#define ADC_IF_CH3EOC_MSK			(0x01 << ADC_IF_CH3EOC_POS)

#define ADC_IF_CH4EOC_POS			4		//CH4转换完成中断状态
#define ADC_IF_CH4EOC_MSK			(0x01 << ADC_IF_CH4EOC_POS)

#define ADC_IF_CH5EOC_POS			5		//CH5转换完成中断状态
#define ADC_IF_CH5EOC_MSK			(0x01 << ADC_IF_CH5EOC_POS)

#define ADC_IF_CH6EOC_POS			6		//CH6转换完成中断状态
#define ADC_IF_CH6EOC_MSK			(0x01 << ADC_IF_CH6EOC_POS)

#define ADC_IF_CH7EOC_POS			7		//CH7转换完成中断状态
#define ADC_IF_CH7EOC_MSK			(0x01 << ADC_IF_CH7EOC_POS)

#define ADC_IF_CH8EOC_POS			8		//CH8转换完成中断状态
#define ADC_IF_CH8EOC_MSK			(0x01 << ADC_IF_CH8EOC_POS)

#define ADC_IF_CH9EOC_POS			9		//CH9转换完成中断状态
#define ADC_IF_CH9EOC_MSK			(0x01 << ADC_IF_CH9EOC_POS)

#define ADC_IF_CH10EOC_POS			10		//CH10转换完成中断状态
#define ADC_IF_CH10EOC_MSK			(0x01 << ADC_IF_CH10EOC_POS)

#define ADC_IF_CH11EOC_POS			11		//CH11转换完成中断状态
#define ADC_IF_CH11EOC_MSK			(0x01 << ADC_IF_CH11EOC_POS)

#define ADC_IF_CH12EOC_POS			12		//CH12转换完成中断状态
#define ADC_IF_CH12EOC_MSK			(0x01 << ADC_IF_CH12EOC_POS)

#define ADC_IF_CH13EOC_POS			13		//CH13转换完成中断状态
#define ADC_IF_CH13EOC_MSK			(0x01 << ADC_IF_CH13EOC_POS)

#define ADC_IF_CH14EOC_POS			14		//CH14转换完成中断状态
#define ADC_IF_CH14EOC_MSK			(0x01 << ADC_IF_CH14EOC_POS)

#define ADC_IF_CH15EOC_POS			15		//CH15转换完成中断状态
#define ADC_IF_CH15EOC_MSK			(0x01 << ADC_IF_CH15EOC_POS)

#define ADC_IF_FIFO_FULL_POS	    16       //FIFO满中断状态
#define ADC_IF_FIFO_FULL_MSK	    (0x01 << ADC_IF_FIFO_FULL_POS)

#define ADC_IF_FIFO_HFULL_POS	    17       //FIFO半满中断状态
#define ADC_IF_FIFO_HFULL_MSK	    (0x01 << ADC_IF_FIFO_HFULL_POS)


#define ADC_STAT_EOC_POS			0		//向ADC_IF相应通道对应位写1可清零
#define ADC_STAT_EOC_MSK			(0x01 << ADC_STAT_EOC_POS)


#define ADC_DATA_DATA_POS           0       //ADC通道数据寄存器
#define ADC_DATA_DATA_MSK           (0xFFF << ADC_DATA_DATA_POS)

#define ADC_DATA_NUM_POS            12      //ADC数据对应的通道编号
#define ADC_DATA_NUM_MSK            (0x0F << ADC_DATA_NUM_POS)


#define ADC_FIFO_STAT_FULL_POS      0       //ADC数据FIFO满标志位
#define ADC_FIFO_STAT_FULL_MSK      (0x01 << ADC_FIFO_STAT_FULL_POS)

#define ADC_FIFO_STAT_HFULL_POS     1       //ADC数据FIFO半满标志位
#define ADC_FIFO_STAT_HFULL_MSK     (0x01 << ADC_FIFO_STAT_HFULL_POS)

#define ADC_FIFO_STAT_EMPTY_POS     2       //ADC数据FIFO空标志位
#define ADC_FIFO_STAT_EMPTY_MSK     (0x01 << ADC_FIFO_STAT_EMPTY_POS)

#define ADC_FIFO_STAT_LEVEL_POS     4       //ADC数据FIFO水线设置
#define ADC_FIFO_STAT_LEVEL_MSK     (0x0F << ADC_FIFO_STAT_LEVEL_POS)


#define ADC_FIFO_DATA_POS           0       //ADC数据FIFO寄存器
#define ADC_FIFO_DATA_MSK           (0xFFF << ADC_FIFO_DATA_POS)

#define ADC_FIFO_NUM_POS            12      //ADC数据FIFO对应的通道编号
#define ADC_FIFO_NUM_MSK            (0x0F << ADC_FIFO_NUM_POS)


#define ADC_EXTTRIG_PWMPLUS0_TRIG0_POS   0       //选择PWMPLUS0_TRIG0触发ADC采样
#define ADC_EXTTRIG_PWMPLUS0_TRIG0_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS0_TRIG0_POS)

#define ADC_EXTTRIG_PWMPLUS0_TRIG1_POS   1       //选择PWMPLUS0_TRIG1触发ADC采样
#define ADC_EXTTRIG_PWMPLUS0_TRIG1_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS0_TRIG1_POS)

#define ADC_EXTTRIG_PWMPLUS0_TRIG2_POS   2       //选择PWMPLUS0_TRIG2触发ADC采样 
#define ADC_EXTTRIG_PWMPLUS0_TRIG2_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS0_TRIG2_POS)

#define ADC_EXTTRIG_PWMPLUS0_TRIG3_POS   3       //选择PWMPLUS0_TRIG3触发ADC采样
#define ADC_EXTTRIG_PWMPLUS0_TRIG3_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS0_TRIG3_POS)

#define ADC_EXTTRIG_PWMPLUS1_TRIG0_POS   4       //选择PWMPLUS1_TRIG0触发ADC采样
#define ADC_EXTTRIG_PWMPLUS1_TRIG0_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS1_TRIG0_POS)

#define ADC_EXTTRIG_PWMPLUS1_TRIG1_POS   5       //选择PWMPLUS1_TRIG1触发ADC采样
#define ADC_EXTTRIG_PWMPLUS1_TRIG1_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS1_TRIG1_POS)

#define ADC_EXTTRIG_PWMPLUS1_TRIG2_POS   6       //选择PWMPLUS1_TRIG2触发ADC采样 
#define ADC_EXTTRIG_PWMPLUS1_TRIG2_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS1_TRIG2_POS)

#define ADC_EXTTRIG_PWMPLUS1_TRIG3_POS   7       //选择PWMPLUS1_TRIG3触发ADC采样
#define ADC_EXTTRIG_PWMPLUS1_TRIG3_MSK   (0x01 << ADC_EXTTRIG_PWMPLUS1_TRIG3_POS)

#define ADC_EXTTRIG_TIMPLUS0_LOW_POS     8       //选择TIMERPLUS0_LOW触发ADC采样
#define ADC_EXTTRIG_TIMPLUS0_LOW_MSK     (0x01 << ADC_EXTTRIG_TIMPLUS0_LOW_POS)

#define ADC_EXTTRIG_TIMPLUS0_HIGH_POS    9       //选择TIMERPLUS0_HIGH触发ADC采样
#define ADC_EXTTRIG_TIMPLUS0_HIGH_MSK    (0x01 << ADC_EXTTRIG_TIMPLUS0_HIGH_POS)

#define ADC_EXTTRIG_TIMPLUS1_LOW_POS     10      //选择TIMERPLUS1_LOW触发ADC采样
#define ADC_EXTTRIG_TIMPLUS1_LOW_MSK     (0x01 << ADC_EXTTRIG_TIMPLUS1_LOW_POS)

#define ADC_EXTTRIG_TIMPLUS1_HIGH_POS    11      //选择TIMERPLUS1_HIGH触发ADC采样
#define ADC_EXTTRIG_TIMPLUS1_HIGH_MSK    (0x01 << ADC_EXTTRIG_TIMPLUS1_HIGH_POS)


#define ADC_CALIB_OFFSET_POS        0       //ADC数据校准OFFSET
#define ADC_CALIB_OFFSET_MSK        (0xFF << ADC_CALIB_OFFSET_POS)

#define ADC_CALIB_OFFSET_VALID_POS  16      //ADC数据校准OFFSET数据是否有效
#define ADC_CALIB_OFFSET_VALID_MSK  (0xFF << ADC_CALIB_OFFSET_VALID_POS)


#define ADC_CALIB_KD_POS            0       //ADC数据校准KD
#define ADC_CALIB_KD_MSK            (0x3FF << ADC_CALIB_KD_POS)

#define ADC_CALIB_KD_VALID_POS      16      //ADC数据校准KD数据是否有效
#define ADC_CALIB_KD_VALID_MSK      (0xFF << ADC_CALIB_KD_VALID_POS)


typedef struct {
	__IO uint32_t CFG;          //FLASH配置寄存器      
	
	__IO uint32_t ADDR;         //FLASH地址寄存器   

	__IO uint32_t WDATA;        //FLASH写数据寄存器
	
	__IO uint32_t RDATA;        //FLASH读数据寄存器
	
	__IO uint32_t START;        //FLASH启动寄存器
	
	__IO uint32_t STATE;        //FLASH状态寄存器  
	
	__IO uint32_t LOCK;         //FLASH锁定控制寄存器

	__IO uint32_t UNLOCK; 	    //FLASH解锁控制寄存器
	
	__IO uint32_t MASK;         //FLASH屏蔽控制寄存器

	__IO uint32_t ERASETIME;    //FLASH擦除时间参数配置寄存器
	
	__IO uint32_t PROGTIME;     //FLASH编程时间参数配置寄存器
	
} FLASH_TypeDef;


#define FLASH_CFG_CLK_WAIT_POS      0       //FLASH读速率模式选择
#define FLASH_CFG_CLK_WAIT_MSK      (0x01 << FLASH_CFG_CLK_WAIT_POS)

#define FLASH_CFG_NVR_SEL_POS       1       //FLASH MAIN区和NVR区选择
#define FLASH_CFG_NVR_SEL_MSK       (0x01 << FLASH_CFG_NVR_SEL_POS)

#define FLASH_CFG_MODE_POS          2       //FLASH 操作模式配置
#define FLASH_CFG_MODE_MSK          (0x07 << FLASH_CFG_MODE_POS)

#define FLASH_CFG_DEEP_PD_POS       31       //FLASH进入DEEP POWER DOWN模式
#define FLASH_CFG_DEEP_PD_MSK       ((uint32_t)0x01 << FLASH_CFG_DEEP_PD_POS)


#define FLASH_ADDR_POS              0        //编程或者擦除地址寄存器  以字为单位
#define FLASH_ADDR_MSK              (0x3FFF << FLASH_ADDR_POS)


#define FLASH_START_EN_POS          0        //操作启动控制位
#define FLASH_START_EN_MSK          (0x01 << FLASH_START_EN_POS)


#define FLASH_STATE_INITBUSY_POS    0        //FLASH初始化忙标志
#define FLASH_STATE_INITBUSY_MSK    (0x01 << FLASH_STATE_INITBUSY_POS)

#define FLASH_STATE_BUSY_POS        1        //FLASH忙标志
#define FLASH_STATE_BUSY_MSK        (0x01 << FLASH_STATE_BUSY_POS)

#define FLASH_STATE_BUFEMPTY_POS    2        //FLASH编程数据缓存寄存器空标志
#define FLASH_STATE_BUFEMPTY_MSK    (0x01 << FLASH_STATE_BUFEMPTY_POS)


#define FLASH_LOCK_POS              0        //FLASH锁定控制寄存器   写入0x55即可锁定FLASH
#define FLASH_LOCK_MSK              (0xFF << FLASH_LOCK_POS)


#define FLASH_UNLOCK_POS            0        //FLASH解锁控制寄存器   写入0xAA即可解锁FLASH
#define FLASH_UNLOCK_MSK            (0xFF << FLASH_UNLOCK_POS)


#define FLASH_MASK_SEL_POS          0        //MASK选择
#define FLASH_MASK_SEL_MSK          (0x03 << FLASH_MASK_SEL_POS)

#define FLASH_MASK_LOCK_POS         2        //MASK选择锁定控制位
#define FLASH_MASK_LOCK_MSK         (0x01 << FLASH_MASK_LOCK_POS)


#define FLASH_ERASETIME_TERASE_POS  0
#define FLASH_ERASETIME_TERASE_MSK  (0x7FFFF << FLASH_ERASETIME_TERASE_POS)

#define FLASH_ERASETIME_TRCV_POS    19
#define FLASH_ERASETIME_TRCV_MSK    (0xFFFF << FLASH_ERASETIME_TRCV_POS)


#define FLASH_PROGTIME_TPROG_POS    0
#define FLASH_PROGTIME_TPROG_MSK    (0x7FFF << FLASH_PROGTIME_TPROG_POS)

#define FLASH_PROGTIME_TPGS_POS     11
#define FLASH_PROGTIME_TPGS_MSK     (0x7FFF << FLASH_PROGTIME_TPGS_POS)


typedef struct {
	__IO uint32_t CR;          //CRC控制寄存器
	
	__IO uint32_t IV;          //CRC初始值寄存器
	
	__IO uint32_t DATAIN;      //CRC输入数据寄存器
	
	__IO uint32_t DATAOUT;     //CRC输出数据寄存器
	
} CRC_TypeDef;


#define CRC_CR_EN_POS               0      //CRC使能
#define CRC_CR_EN_MSK               (0x01 << CRC_CR_EN_POS)

#define CRC_CR_INPUT_REV_POS        1      //CRC输入数据是否取反
#define CRC_CR_INPUT_REV_MSK        (0x01 << CRC_CR_INPUT_REV_POS)

#define CRC_CR_INPUT_INV_POS        2      //CRC输入数据翻转寄存器
#define CRC_CR_INPUT_INV_MSK        (0x03 << CRC_CR_INPUT_INV_POS)

#define CRC_CR_OUTPUT_REV_POS       4      //CRC输出数据是否取反
#define CRC_CR_OUTPUT_REV_MSK       (0x01 << CRC_CR_OUTPUT_REV_POS)

#define CRC_CR_OUTPUT_INV_POS       5      //CRC输出数据翻转寄存器
#define CRC_CR_OUTPUT_INV_MSK       (0x03 << CRC_CR_OUTPUT_INV_POS)

#define CRC_CR_DATA_WIDTH_POS       7      //CRC输入数据有效位数寄存器
#define CRC_CR_DATA_WIDTH_MSK       (0x03 << CRC_CR_DATA_WIDTH_POS)

#define CRC_CR_SEL_POS              9      //CRC算法选择寄存器
#define CRC_CR_SEL_MSK              (0x03 << CRC_CR_SEL_POS)



typedef struct {
	__IO uint32_t CTR;             //DMA控制寄存器          
	
	__IO uint32_t INTEN;           //DMA中断使能寄存器         
	
	__IO uint32_t INTST;           //DMA中断状态寄存器 
	
	uint32_t RESERVED1[(0x100 - 0x0C)/4];
	
	struct {
		__IO uint32_t CH_CTR;      //通道控制寄存器
		
		__IO uint32_t CH_MODE;     //通道模式寄存器 
		
		__IO uint32_t CH_MSADDR;   //通道源地址寄存器
		
		__IO uint32_t CH_MDADDR;   //通道目的地址寄存器	
		
		__IO uint32_t CH_ST;       //通道状态寄存器
		
		uint32_t RESERVED2[3];
	} CH[4];
	
} DMA_TypeDef;


#define DMA_CTR_EN_POS              0    //DMA使能    1  使能  0 禁能
#define DMA_CTR_EN_MSK              (0x01 << DMA_CTR_EN_POS)


#define DMA_INTEN_CH0_TC_EN_POS     0    //DMA通道0传输完成中断使能
#define DMA_INTEN_CH0_TC_EN_MSK     (0x01 << DMA_INTEN_CH0_TC_EN_POS)

#define DMA_INTEN_CH1_TC_EN_POS     1    //DMA通道1传输完成中断使能
#define DMA_INTEN_CH1_TC_EN_MSK     (0x01 << DMA_INTEN_CH1_TC_EN_POS)

#define DMA_INTEN_CH2_TC_EN_POS     2    //DMA通道2传输完成中断使能
#define DMA_INTEN_CH2_TC_EN_MSK     (0x01 << DMA_INTEN_CH2_TC_EN_POS)

#define DMA_INTEN_CH3_TC_EN_POS     3    //DMA通道3传输完成中断使能
#define DMA_INTEN_CH3_TC_EN_MSK     (0x01 << DMA_INTEN_CH3_TC_EN_POS)

#define DMA_INTEN_CH0_THC_EN_POS    8    //DMA通道0传输一半完成中断使能 
#define DMA_INTEN_CH0_THC_EN_MSK    (0x01 << DMA_INTEN_CH0_THC_EN_POS)

#define DMA_INTEN_CH1_THC_EN_POS    9    //DMA通道1传输一半完成中断使能 
#define DMA_INTEN_CH1_THC_EN_MSK    (0x01 << DMA_INTEN_CH1_THC_EN_POS)

#define DMA_INTEN_CH2_THC_EN_POS    10   //DMA通道2传输一半完成中断使能 
#define DMA_INTEN_CH2_THC_EN_MSK    (0x01 << DMA_INTEN_CH2_THC_EN_POS)

#define DMA_INTEN_CH3_THC_EN_POS    11   //DMA通道3传输一半完成中断使能 
#define DMA_INTEN_CH3_THC_EN_MSK    (0x01 << DMA_INTEN_CH3_THC_EN_POS)


#define DMA_INTST_CH0_TC_ST_POS     0    //DMA通道0传输完成中断状态
#define DMA_INTST_CH0_TC_ST_MSK     (0x01 << DMA_INTST_CH0_TC_ST_POS)

#define DMA_INTST_CH1_TC_ST_POS     1    //DMA通道1传输完成中断状态
#define DMA_INTST_CH1_TC_ST_MSK     (0x01 << DMA_INTST_CH1_TC_ST_POS)

#define DMA_INTST_CH2_TC_ST_POS     2    //DMA通道2传输完成中断状态
#define DMA_INTST_CH2_TC_ST_MSK     (0x01 << DMA_INTST_CH2_TC_ST_POS)

#define DMA_INTST_CH3_TC_ST_POS     3    //DMA通道3传输完成中断状态
#define DMA_INTST_CH3_TC_ST_MSK     (0x01 << DMA_INTST_CH3_TC_ST_POS)

#define DMA_INTST_CH0_THC_ST_POS    8    //DMA通道0传输一半完成中断状态
#define DMA_INTST_CH0_THC_ST_MSK    (0x01 << DMA_INTST_CH0_THC_ST_POS)

#define DMA_INTST_CH1_THC_ST_POS    9    //DMA通道1传输一半完成中断状态
#define DMA_INTST_CH1_THC_ST_MSK    (0x01 << DMA_INTST_CH1_THC_ST_POS)

#define DMA_INTST_CH2_THC_ST_POS    10   //DMA通道2传输一半完成中断状态
#define DMA_INTST_CH2_THC_ST_MSK    (0x01 << DMA_INTST_CH2_THC_ST_POS)

#define DMA_INTST_CH3_THC_ST_POS    11   //DMA通道3传输一半完成中断状态
#define DMA_INTST_CH3_THC_ST_MSK    (0x01 << DMA_INTST_CH3_THC_ST_POS)


#define DMA_CH_CTR_EN_POS            0    //DMA通道使能
#define DMA_CH_CTR_EN_MSK            (0x01 << DMA_CH_CTR_EN_POS)

#define DMA_CH_CTR_LENTH_POS         1    //DMA通道传输数量    最多可以传输4096
#define DMA_CH_CTR_LENTH_MSK         (0xFFF << DMA_CH_CTR_LENTH_POS)

#define DMA_CH_CTR_LOOP_POS          13  //DMA通道循环方式控制位   0 单次模式  1 循环模式
#define DMA_CH_CTR_LOOP_MSK          (0x01 << DMA_CH_CTR_LOOP_POS)

#define DMA_CH_CTR_PRI_POS           14    //DMA通道优先级   00 低  01  中  10 高  11 最高
#define DMA_CH_CTR_PRI_MSK           (0x03 << DMA_CH_CTR_PRI_POS)

#define DMA_CH_CTR_SWREQ_POS         16    //DMA通道软件方式请求发送   仅限于源地址侧为存储设备时发起
#define DMA_CH_CTR_SWREQ_MSK         (0x01 << DMA_CH_CTR_SWREQ_POS)


#define DMA_CH_MODE_MS_ADDR_POS      0    //DMA通道源地址侧地址变化方式选择   0  地址不变  1  地址递增
#define DMA_CH_MODE_MS_ADDR_MSK      (0x01 << DMA_CH_MODE_MS_ADDR_POS)

#define DMA_CH_MODE_MS_SIZE_POS      1    //DMA通道源地址侧总线传输宽度       00  8bits  01 16bits   10 32bits  11 保留
#define DMA_CH_MODE_MS_SIZE_MSK      (0x03 << DMA_CH_MODE_MS_SIZE_POS)

#define DMA_CH_MODE_MS_SEL_POS       3    //DMA通道源地址侧外设选择           000  RAM   001--111  其他外设  
#define DMA_CH_MODE_MS_SEL_MSK       (0x07 << DMA_CH_MODE_MS_SEL_POS)

#define DMA_CH_MODE_MD_ADDR_POS      8    //DMA通道目的地址侧地址变化方式选择   0  地址不变  1  地址递增
#define DMA_CH_MODE_MD_ADDR_MSK      (0x01 << DMA_CH_MODE_MD_ADDR_POS)

#define DMA_CH_MODE_MD_SIZE_POS      9    //DMA通道目的地址侧总线传输宽度       00  8bits  01 16bits   10 32bits  11 保留
#define DMA_CH_MODE_MD_SIZE_MSK      (0x03 << DMA_CH_MODE_MD_SIZE_POS)

#define DMA_CH_MODE_MD_SEL_POS       11    //DMA通道目的地址侧外设选择          000  RAM   001--111  其他外设  
#define DMA_CH_MODE_MD_SEL_MSK       (0x07 << DMA_CH_MODE_MD_SEL_POS)


#define DMA_CH_ST_CUR_LENTH_POS      0    //DMA通道当前传输个数
#define DMA_CH_ST_CUR_LENTH_MSK      (0xFFF << DMA_CH_ST_CUR_LENTH_POS)


typedef struct {
	__IO uint32_t CR;              //控制寄存器
            
	__IO uint32_t SR;              //状态寄存器

	__IO uint32_t DINR;            //输入数据寄存器

	__IO uint32_t DOUTR;           //输出数据寄存器

	__IO uint32_t KEYR0;           //密钥寄存器0
	
	__IO uint32_t KEYR1;           //密钥寄存器1
	
	__IO uint32_t KEYR2;           //密钥寄存器2
	
	__IO uint32_t KEYR3;           //密钥寄存器3
	
	__IO uint32_t IVR0;            //加密起始点寄存器0
	
	__IO uint32_t IVR1;            //加密起始点寄存器1
	
	__IO uint32_t IVR2;            //加密起始点寄存器2
	
	__IO uint32_t IVR3;            //加密起始点寄存器3
	
} AES128_TypeDef;


#define AES128_CR_EN_POS               0          //AES128使能信号
#define AES128_CR_EN_MSK               (0x01 << AES128_CR_EN_POS)

#define AES128_CR_DATATYPE_POS         1          //AES128数据类型选择
#define AES128_CR_DATATYPE_MSK         (0x03 << AES128_CR_DATATYPE_POS)

#define AES128_CR_MODE_POS             3          //AES128模式选择
#define AES128_CR_MODE_MSK             (0x03 << AES128_CR_MODE_POS)

#define AES128_CR_CHMODE_POS           5          //AES128链接模式选择
#define AES128_CR_CHMODE_MSK           (0x03 << AES128_CR_CHMODE_POS)

#define AES128_CR_CCFC_POS             7          //AES128计算完成标志清除
#define AES128_CR_CCFC_MSK             (0x01 << AES128_CR_CCFC_POS)

#define AES128_CR_ERRC_POS             8          //AES128错误标志清除
#define AES128_CR_ERRC_MSK             (0x01 << AES128_CR_ERRC_POS)

#define AES128_SR_CCF_POS              0          //AES128计算完成标志
#define AES128_SR_CCF_MSK              (0x01 << AES128_SR_CCF_POS)

#define AES128_SR_RDERR_POS            1          //AES128读取错误标志
#define AES128_SR_RDERR_MSK            (0x01 << AES128_SR_RDERR_POS)

#define AES128_SR_WRERR_POS            2          //AES128写入错误标志
#define AES128_SR_WRERR_MSK            (0x01 << AES128_SR_WRERR_POS)





/******************************************************************************/
/*						 Peripheral memory map							  */
/******************************************************************************/
#define RAM_BASE		    ((uint32_t)0x20000000)
#define AHB_BASE			((uint32_t)0x40000000)
#define APB1_BASE		 	((uint32_t)0x40060000)
#define APB2_BASE			((uint32_t)0x400B0000)

/* AHB Peripheral memory map */
#define SYS_BASE			(AHB_BASE + 0x0000)
#define PMU_BASE			(AHB_BASE + 0x0800)
#define DMA_BASE			(AHB_BASE + 0x1000)
#define CRC_BASE			(AHB_BASE + 0x3000)

/* APB1 Peripheral memory map */
#define GPIOA_BASE		    (APB1_BASE + 0x0000)
#define GPIOB_BASE		    (APB1_BASE + 0x0800)
#define GPIOC_BASE		    (APB1_BASE + 0x1000)

#define TIMBASE0_BASE       (APB1_BASE + 0x4000)
#define TIMBASE1_BASE       (APB1_BASE + 0x4800)
#define TIMBASE2_BASE       (APB1_BASE + 0x5000)

#define TIMPLUS0_BASE       (APB1_BASE + 0x7000)
#define TIMPLUS1_BASE       (APB1_BASE + 0x7800)

#define RTC_BASE		    (APB1_BASE + 0x9000)

#define IWDT_BASE		    (APB1_BASE + 0xA000)
#define WWDT_BASE		    (APB1_BASE + 0xA800)

#define UART0_BASE		    (APB1_BASE + 0xB000)
#define UART1_BASE		    (APB1_BASE + 0xB800)
#define UART2_BASE		    (APB1_BASE + 0xC000)

#define FLASH_CTRL_BASE		(APB1_BASE + 0xF000)

/* APB2 Peripheral memory map */
#define PORT_BASE			(APB2_BASE + 0x0000)

#define PWMBASE0_BASE		(APB2_BASE + 0x1000)
#define PWMBASE1_BASE		(APB2_BASE + 0x1800)

#define PWMPLUS0_BASE		(APB2_BASE + 0x4000)
#define PWMPLUS1_BASE		(APB2_BASE + 0x4800)

#define SPI0_BASE			(APB2_BASE + 0x8000)
#define SPI1_BASE			(APB2_BASE + 0x8800)

#define IIC0_BASE			(APB2_BASE + 0x9000)
#define IIC1_BASE			(APB2_BASE + 0x9800)

#define ADC_BASE			(APB2_BASE + 0xA000)

#define AES128_BASE		    (APB2_BASE + 0xD000)

/******************************************************************************/
/*						 Peripheral declaration							 */
/******************************************************************************/
#define SYS					((SYS_TypeDef  *) SYS_BASE)

#define PMU 				((PMU_TypeDef  *) PMU_BASE)

#define DMA				    ((DMA_TypeDef*) DMA_BASE)

#define CRC				    ((CRC_TypeDef*) CRC_BASE)

#define GPIOA				((GPIO_TypeDef *) GPIOA_BASE)

#define GPIOB				((GPIO_TypeDef *) GPIOB_BASE)

#define GPIOC				((GPIO_TypeDef *) GPIOC_BASE)

#define TIMBASE0			((TIMBASE_TypeDef *) TIMBASE0_BASE)

#define TIMBASE1			((TIMBASE_TypeDef *) TIMBASE1_BASE)

#define TIMBASE2			((TIMBASE_TypeDef *) TIMBASE2_BASE)

#define TIMPLUS0			((TIMPLUS_TypeDef *) TIMPLUS0_BASE)

#define TIMPLUS1			((TIMPLUS_TypeDef *) TIMPLUS1_BASE)

#define RTC				    ((RTC_TypeDef  *) RTC_BASE)

#define IWDT				((IWDT_TypeDef  *) IWDT_BASE)

#define WWDT				((WWDT_TypeDef  *) WWDT_BASE)

#define UART0				((UART_TypeDef *) UART0_BASE)

#define UART1				((UART_TypeDef *) UART1_BASE)

#define UART2				((UART_TypeDef *) UART2_BASE)

#define FLASH               ((FLASH_TypeDef  *) FLASH_CTRL_BASE)


#define PORT				((PORT_TypeDef *) PORT_BASE)

#define PWMBASE0			((PWMBASE_TypeDef  *) PWMBASE0_BASE)

#define PWMBASE1			((PWMBASE_TypeDef  *) PWMBASE1_BASE)

#define PWMPLUS0			((PWMPLUS_TypeDef  *) PWMPLUS0_BASE)

#define PWMPLUS1			((PWMPLUS_TypeDef  *) PWMPLUS1_BASE)

#define SPI0				((SPI_TypeDef  *) SPI0_BASE)

#define SPI1				((SPI_TypeDef  *) SPI1_BASE)

#define IIC0                ((IIC_TypeDef  *) IIC0_BASE)

#define IIC1                ((IIC_TypeDef  *) IIC1_BASE)

#define ADC				    ((ADC_TypeDef  *) ADC_BASE)

#define AES128			    ((AES128_TypeDef  *) AES128_BASE)


#include "system_DP32G030.h"
#include "DP32G030_port.h"
#include "DP32G030_gpio.h"
#include "DP32G030_flash.h"
#include "DP32G030_conf.h"
#include "DP32G030_uart.h"
#include "DP32G030_exti.h"
#include "DP32G030_spi.h"
#include "DP32G030_iic.h"
#include "DP32G030_pwmbase.h"
#include "DP32G030_pwmplus.h"
#include "DP32G030_timerbase.h"
#include "DP32G030_timerplus.h"
#include "DP32G030_iwdt.h"
#include "DP32G030_wwdt.h"
#include "DP32G030_crc.h"
#include "DP32G030_rtc.h"
#include "DP32G030_dma.h"
#include "DP32G030_aes.h"
#include "DP32G030_power.h"
#include "DP32G030_adc.h"
#include "DP32G030_cmp.h"
#include "DP32G030_opa.h"
#endif //__DP32G030_H__
