#ifndef __DP32G030_PORT_H__
#define __DP32G030_PORT_H__          

#include "DP32G030.h"


typedef struct
{
	uint8_t Port;         //端口       
    uint8_t Pin;          //引脚号                              
    uint8_t Func;         //功能
	uint8_t Input_En;     //输入使能     
} PORT_InitTypeDef;


typedef enum
{ 
	OUT_CURRENT_5MA  =  0x00,    // 输出电流5MA
	OUT_CURRENT_10MA =  0x01,    // 输出电流10MA
	OUT_CURRENT_15MA =  0x02,    // 输出电流15MA
	OUT_CURRENT_20MA =  0x03,    // 输出电流20MA
} OutCurrent_TypeDef;

typedef enum
{ 
	INPUT_HYS_LOW =   0x00,      // 低输入迟滞  
	INPUT_HYS_HIGH =  0x01,      // 高输入迟滞  
} InputHys_TypeDef;


typedef struct
{
	OutCurrent_TypeDef   PortA_Out_Cur;          //PORTA的驱动能力
	OutCurrent_TypeDef   PortB_Out_Cur;          //PORTB的驱动能力
	OutCurrent_TypeDef   PortC_Out_Cur;          //PORTC的驱动能力
	InputHys_TypeDef     InputHys;               //PORT的输入迟滞等级
} PORT_CFGTypeDef;

//断言  PORTA  
#define IS_PORT_ALL(PORT)           (((PORT) == PORTA) || ((PORT) == PORTB) || ((PORT) == PORTC))

//断言端口功能
#define IS_PORT_FUNC(PORT_FUNC)     ((PORT_FUNC) < 8)

//断言输入使能
#define IS_INPUT_EN(INPUT_EN)       (((INPUT_EN) == ENABLE) || ((INPUT_EN) == DISABLE))

//断言驱动能力
#define IS_OUT_CURRENT(OUT_CURRENT) (((OUT_CURRENT) == OUT_CURRENT_5MA ) || ((OUT_CURRENT) == OUT_CURRENT_10MA) || \
                                     ((OUT_CURRENT) == OUT_CURRENT_15MA) || ((OUT_CURRENT) == OUT_CURRENT_20MA) )

//断言输入迟滞等级
#define IS_INPUT_HYS(INPUT_HYS)     (((INPUT_HYS) == INPUT_HYS_LOW) || ((INPUT_HYS) == INPUT_HYS_HIGH))


#define PORTA	                   0             //端口A
#define PORTB	                   1             //端口B
#define PORTC	                   2             //端口C


#define PORTA_PIN0_GPIO		 	   0             //PORTA0配置为GPIOA0
#define PORTA_PIN0_PWMP1_PULSE0    1             //PORTA0配置为PWMPLUS1的PULSE0
#define PORTA_PIN0_PWMP0_PULSE1    2             //PORTA0配置为PWMPLUS0的PULSE1
#define PORTA_PIN0_TM	 	       3             //PORTA0配置为RTC的1/2秒标
#define PORTA_PIN0_WAKEUP0	 	   4             //PORTA0配置为唤醒引脚0

#define PORTA_PIN1_GPIO			   0             //PORTA1配置为GPIOA1
#define PORTA_PIN1_XTAL_XI		   1             //PORTA1配置为XTAL_XI

#define PORTA_PIN2_GPIO			   0             //PORTA2配置为GPIOA2
#define PORTA_PIN2_XTAL_XO		   1             //PORTA2配置为XTAL_XO

#define PORTA_PIN3_GPIO			   0             //PORTA3配置为GPIOA3
#define PORTA_PIN3_CMP0_VN		   1             //PORTA3配置为比较器0的N端输入
#define PORTA_PIN3_XTAH_XI		   2             //PORTA3配置为XTAH_XI

#define PORTA_PIN4_GPIO			   0             //PORTA4配置为GPIOA4
#define PORTA_PIN4_CMP0_VP		   1             //PORTA4配置为比较器0的P端输入
#define PORTA_PIN4_XTAH_XO		   2             //PORTA4配置为XTAH_XO

#define PORTA_PIN5_GPIO			   0             //PORTA5配置为GPIOA5
#define PORTA_PIN5_UART1_CTS	   1             //PORTA5配置为串口1的CTS引脚
#define PORTA_PIN5_PWMP1_PULSE1    2             //PORTA5配置为PWMPLUS1的PULSE1
#define PORTA_PIN5_TIMP1_IN0       3             //PORTA5配置为TIMPLUS1的输入0
#define PORTA_PIN5_TIMP1_OUT_L     4             //PORTA5配置为TIMPLUS1的低16位定时器的输出
#define PORTA_PIN5_WAKEUP1	 	   5             //PORTA5配置为唤醒引脚1
#define PORTA_PIN5_ADC_CH0	       7             //PORTA5配置为ADC的通道0

#define PORTA_PIN6_GPIO			   0             //PORTA6配置为GPIOA6
#define PORTA_PIN6_UART1_RTS	   1             //PORTA6配置为串口1的RTS引脚
#define PORTA_PIN6_TIMP1_IN1       2             //PORTA6配置为TIMPLUS1的输入1
#define PORTA_PIN6_TIMP1_OUT_H     3             //PORTA6配置为TIMPLUS1的高16位定时器的输出
#define PORTA_PIN6_ADC_CH1	       4             //PORTA6配置为ADC的通道1
#define PORTA_PIN6_OPA0_OUT		   5             //PORTA6配置为运算放大器0的输出引脚

#define PORTA_PIN7_GPIO			   0             //PORTA7配置为GPIOA7
#define PORTA_PIN7_UART1_TX	       1             //PORTA7配置为串口1的发送引脚
#define PORTA_PIN7_TIMP0_IN0       2             //PORTA7配置为TIMPLUS0的输入0
#define PORTA_PIN7_TIMP0_OUT_L     3             //PORTA7配置为TIMPLUS0的低16位定时器的输出
#define PORTA_PIN7_ADC_CH2	       4             //PORTA7配置为ADC的通道2
#define PORTA_PIN7_OPA0_VP		   5             //PORTA7配置为运算放大器0的P端输入

#define PORTA_PIN8_GPIO		 	   0             //PORTA8配置为GPIOA8
#define PORTA_PIN8_UART1_RX	       1             //PORTA8配置为串口1的接收引脚
#define PORTA_PIN8_TIMP0_IN1       2             //PORTA8配置为TIMPLUS0的输入1
#define PORTA_PIN8_TIMP0_OUT_H     3             //PORTA8配置为TIMPLUS0的高16位定时器的输出
#define PORTA_PIN8_ADC_CH3	       4             //PORTA8配置为ADC的通道3
#define PORTA_PIN8_OPA0_VN		   5             //PORTA8配置为运算放大器0的N端输入

#define PORTA_PIN9_GPIO			   0             //PORTA9配置为GPIOA9
#define PORTA_PIN9_SPI0_SSN	       1             //PORTA9配置为SPI0的片选
#define PORTA_PIN9_TIMP1_IN0       2             //PORTA9配置为TIMPLUS1的输入0
#define PORTA_PIN9_TIMP1_OUT_L     3             //PORTA9配置为TIMPLUS1的低16位定时器的输出
#define PORTA_PIN9_TM	           4             //PORTA9配置为RTC的1/2秒标
#define PORTA_PIN9_ADC_CH4	       5             //PORTA9配置为ADC的通道4
#define PORTA_PIN9_CMP1_VN		   6             //PORTA9配置为比较器1的N端输入

#define PORTA_PIN10_GPIO		   0             //PORTA10配置为GPIOA10
#define PORTA_PIN10_SPI0_CLK       1             //PORTA10配置为SPI0的时钟
#define PORTA_PIN10_ADC_CH5	       2             //PORTA10配置为ADC的通道5
#define PORTA_PIN10_CMP1_VP		   3             //PORTA10配置为比较器1的P端输入

#define PORTA_PIN11_GPIO		   0             //PORTA11配置为GPIOA11
#define PORTA_PIN11_SPI0_MISO	   1             //PORTA11配置为SPI0的主入从出
#define PORTA_PIN11_PWMB0_CH0      2             //PORTA11配置为PWMBASE0的通道0
#define PORTA_PIN11_PWMP0_BRK0     3             //PORTA11配置为PWMPLUS0的BREAK0
#define PORTA_PIN11_TIMP1_IN1      4             //PORTA11配置为TIMPLUS1的输入1
#define PORTA_PIN11_TIMP1_OUT_H    5             //PORTA11配置为TIMPLUS1的高16位定时器的输出
#define PORTA_PIN11_ADC_CH6	       6             //PORTA11配置为ADC的通道6

#define PORTA_PIN12_GPIO		   0             //PORTA12配置为GPIOA12
#define PORTA_PIN12_SPI0_MOSI	   1             //PORTA12配置为SPI0的主出从入
#define PORTA_PIN12_PWMB0_CH1      2             //PORTA12配置为PWMBASE0的通道1
#define PORTA_PIN12_PWMP0_CH0N     3             //PORTA12配置为PWMPLUS0的通道0N
#define PORTA_PIN12_TIMP0_IN0      4             //PORTA12配置为TIMPLUS0的输入0
#define PORTA_PIN12_TIMP0_OUT_L    5             //PORTA12配置为TIMPLUS0的低16位定时器的输出
#define PORTA_PIN12_ADC_CH7	       6             //PORTA12配置为ADC的通道7

#define PORTA_PIN13_GPIO		   0             //PORTA13配置为GPIOA13
#define PORTA_PIN13_PWMB0_CH2      1             //PORTA13配置为PWMBASE0的通道2
#define PORTA_PIN13_PWMP0_CH1N     2             //PORTA13配置为PWMPLUS0的通道1N
#define PORTA_PIN13_TIMP0_IN1      3             //PORTA13配置为TIMPLUS0的输入1
#define PORTA_PIN13_TIMP0_OUT_H    4             //PORTA13配置为TIMPLUS0的高16位定时器的输出
#define PORTA_PIN13_ADC_CH8	       5             //PORTA13配置为ADC的通道8

#define PORTA_PIN14_GPIO		   0             //PORTA14配置为GPIOA14
#define PORTA_PIN14_PWMB1_CH0      1             //PORTA14配置为PWMBASE1的通道0
#define PORTA_PIN14_PWMP0_CH2N     2             //PORTA14配置为PWMPLUS0的通道2N
#define PORTA_PIN14_TIMP1_IN0      3             //PORTA14配置为TIMPLUS1的输入0
#define PORTA_PIN14_TIMP1_OUT_L    4             //PORTA14配置为TIMPLUS1的低16位定时器的输出
#define PORTA_PIN14_ADC_CH9	       5             //PORTA14配置为ADC的通道9

#define PORTA_PIN15_GPIO		   0             //PORTA15配置为GPIOA15
#define PORTA_PIN15_PWMB1_CH1      1             //PORTA15配置为PWMBASE1的通道1
#define PORTA_PIN15_PWMP0_CH0      2             //PORTA15配置为PWMPLUS0的通道0
#define PORTA_PIN15_TIMP1_IN1      3             //PORTA15配置为TIMPLUS1的输入1
#define PORTA_PIN15_TIMP1_OUT_H    4             //PORTA15配置为TIMPLUS1的高16位定时器的输出


#define PORTB_PIN0_GPIO		 	   0             //PORTB0配置为GPIOB0
#define PORTB_PIN0_UART2_TX	       1             //PORTB0配置为串口2的发送引脚
#define PORTB_PIN0_IIC0_SCL	       2             //PORTB0配置为IIC0的时钟引脚
#define PORTB_PIN0_PWMB1_CH2       3             //PORTB0配置为PWMBASE1的通道2
#define PORTB_PIN0_PWMP0_CH1       4             //PORTB0配置为PWMPLUS0的通道1

#define PORTB_PIN1_GPIO		 	   0             //PORTB1配置为GPIOB1
#define PORTB_PIN1_UART2_RX	       1             //PORTB1配置为串口2的接收引脚
#define PORTB_PIN1_IIC0_SDA	       2             //PORTB1配置为IIC0的数据引脚
#define PORTB_PIN1_PWMP0_CH2       3             //PORTB1配置为PWMPLUS0的通道2

#define PORTB_PIN2_GPIO		 	   0             //PORTB2配置为GPIOB2
#define PORTB_PIN2_SPI1_SSN	       1             //PORTB2配置为SPI1的片选
#define PORTB_PIN2_PWMP0_BRK1      2             //PORTB2配置为PWMPLUS0的BREAK1
#define PORTB_PIN2_TIMP1_HALL0     3             //PORTB2配置为TIMPLUS1的HALL0

#define PORTB_PIN3_GPIO		 	   0             //PORTB3配置为GPIOB3
#define PORTB_PIN3_SPI1_CLK        1             //PORTB3配置为SPI1的时钟
#define PORTB_PIN3_IIC1_SDA	       2             //PORTB3配置为IIC1的数据引脚
#define PORTB_PIN3_PWMP0_CH0N      3             //PORTB3配置为PWMPLUS0的通道0N
#define PORTB_PIN3_TIMP1_HALL1     4             //PORTB3配置为TIMPLUS1的HALL1

#define PORTB_PIN4_GPIO		 	   0             //PORTB4配置为GPIOB4
#define PORTB_PIN4_SPI1_MISO	   1             //PORTB4配置为SPI1的主入从出
#define PORTB_PIN4_IIC1_SCL	       2             //PORTB4配置为IIC1的时钟引脚
#define PORTB_PIN4_PWMP1_CH0       3             //PORTB4配置为PWMPLUS1的通道0
#define PORTB_PIN4_PWMP0_CH1N      4             //PORTB4配置为PWMPLUS0的通道1N
#define PORTB_PIN4_TIMP1_HALL2     5             //PORTB4配置为TIMPLUS1的HALL2

#define PORTB_PIN5_GPIO		 	   0             //PORTB5配置为GPIOB5
#define PORTB_PIN5_SPI1_MOSI	   1             //PORTB5配置为SPI1的主出从入
#define PORTB_PIN5_PWMP1_CH0N      2             //PORTB5配置为PWMPLUS1的通道0N
#define PORTB_PIN5_PWMP0_CH2N      3             //PORTB5配置为PWMPLUS0的通道2N
#define PORTB_PIN5_TIMP0_IN0       4             //PORTB5配置为TIMPLUS0的输入0
#define PORTB_PIN5_TIMP0_OUT_L     5             //PORTB5配置为TIMPLUS0的低16位定时器的输出

#define PORTB_PIN6_GPIO		 	   0             //PORTB6配置为GPIOB6
#define PORTB_PIN6_PWMP0_CH0       1             //PORTB6配置为PWMPLUS0的通道0
#define PORTB_PIN6_TIMP0_IN1       2             //PORTB6配置为TIMPLUS0的输入1
#define PORTB_PIN6_TIMP0_OUT_H     3             //PORTB6配置为TIMPLUS0的高16位定时器的输出

#define PORTB_PIN7_GPIO		 	   0             //PORTB7配置为GPIOB7
#define PORTB_PIN7_SPI0_SSN	       1             //PORTB7配置为SPI0的片选
#define PORTB_PIN7_UART0_TX	       2             //PORTB7配置为串口0的发送引脚
#define PORTB_PIN7_IIC0_SCL	       3             //PORTB7配置为IIC0的时钟引脚
#define PORTB_PIN7_PWMP1_BRK0      4             //PORTB7配置为PWMPLUS1的BREAK0
#define PORTB_PIN7_PWMP0_CH1       5             //PORTB7配置为PWMPLUS0的通道1

#define PORTB_PIN8_GPIO		 	   0             //PORTB8配置为GPIOB8
#define PORTB_PIN8_SPI0_CLK        1             //PORTB8配置为SPI0的时钟
#define PORTB_PIN8_UART0_RX	       2             //PORTB8配置为串口0的接收引脚
#define PORTB_PIN8_IIC0_SDA	       3             //PORTB8配置为IIC0的数据引脚
#define PORTB_PIN8_PWMB0_CH0       4             //PORTB8配置为PWMBASE0的通道0
#define PORTB_PIN8_PWMP1_BRK1      5             //PORTB8配置为PWMPLUS1的BREAK1
#define PORTB_PIN8_PWMP0_CH2       6             //PORTB8配置为PWMPLUS0的通道2

#define PORTB_PIN9_GPIO		 	   0             //PORTB9配置为GPIOB9
#define PORTB_PIN9_SPI0_MISO	   1             //PORTB9配置为SPI0的主入从出
#define PORTB_PIN9_UART0_CTS	   2             //PORTB9配置为串口0的CTS引脚
#define PORTB_PIN9_PWMB0_CH1       3             //PORTB9配置为PWMBASE0的通道1
#define PORTB_PIN9_PWMP1_CH0       4             //PORTB9配置为PWMPLUS1的通道0
#define PORTB_PIN9_TIMP1_IN1       5             //PORTB9配置为TIMPLUS1的输入1
#define PORTB_PIN9_TIMP1_OUT_H     6             //PORTB9配置为TIMPLUS1的高16位定时器的输出

#define PORTB_PIN10_GPIO		   0             //PORTB10配置为GPIOB10
#define PORTB_PIN10_SPI0_MOSI	   1             //PORTB10配置为SPI0的主出从入
#define PORTB_PIN10_UART0_RTS	   2             //PORTB10配置为串口0的RTS引脚
#define PORTB_PIN10_PWMB0_CH2      3             //PORTB10配置为PWMBASE0的通道2
#define PORTB_PIN10_PWMP1_CH1      4             //PORTB10配置为PWMPLUS1的通道1
#define PORTB_PIN10_PWMP0_PULSE0   5             //PORTB10配置为PWMPLUS0的PULSE0
#define PORTB_PIN10_TIMP1_IN0      6             //PORTB10配置为TIMPLUS1的输入0
#define PORTB_PIN10_TIMP1_OUT_L    7             //PORTB10配置为TIMPLUS1的低16位定时器的输出

#define PORTB_PIN11_GPIO		   0             //PORTB11配置为GPIOB11
#define PORTB_PIN11_SWDIO		   1             //PORTB11配置为SW下载的数据
#define PORTB_PIN11_PWMP1_CH2      2             //PORTB11配置为PWMPLUS1的通道2
#define PORTB_PIN11_PWMP0_BRK2     3             //PORTB11配置为PWMPLUS0的BREAK2

#define PORTB_PIN12_GPIO		   0             //PORTB12配置为GPIOB12
#define PORTB_PIN12_UART1_TX	   1             //PORT12配置为串口1的发送引脚
#define PORTB_PIN12_IIC1_SCL	   2             //PORTB12配置为IIC1的时钟引脚
#define PORTB_PIN12_PWMP1_CH0N     3             //PORTB12配置为PWMPLUS1的通道0N

#define PORTB_PIN13_GPIO		   0             //PORTB13配置为GPIOB13
#define PORTB_PIN13_UART1_RX	   1             //PORTB13配置为串口1的接收引脚
#define PORTB_PIN13_IIC1_SDA	   2             //PORTB13配置为IIC1的数据引脚
#define PORTB_PIN13_PWMP1_CH1N     3             //PORTB13配置为PWMPLUS1的通道1N

#define PORTB_PIN14_GPIO		   0             //PORTB14配置为GPIOB14
#define PORTB_PIN14_SWCLK		   1             //PORTB14配置为SW下载的时钟
#define PORTB_PIN14_UART2_TX	   2             //PORTB14配置为串口2的发送引脚
#define PORTB_PIN14_PWMP1_CH2N     3             //PORTB14配置为PWMPLUS1的通道2N

#define PORTB_PIN15_GPIO		   0             //PORTB15配置为GPIOB15
#define PORTB_PIN15_SPI1_SSN	   1             //PORTB15配置为SPI1的片选
#define PORTB_PIN15_UART2_RX	   2             //PORTB15配置为串口2的接收引脚


#define PORTC_PIN0_GPIO		 	   0             //PORTC0配置为GPIOC0
#define PORTC_PIN0_SPI1_CLK        1             //PORTC0配置为SPI1的时钟
#define PORTC_PIN0_UART2_CTS	   2             //PORTC0配置为串口2的CTS引脚
#define PORTC_PIN0_PWMB1_CH0       3             //PORTC0配置为PWMBASE1的通道0

#define PORTC_PIN1_GPIO		 	   0             //PORTC1配置为GPIOC1
#define PORTC_PIN1_SPI1_MISO	   1             //PORTC1配置为SPI1的主入从出
#define PORTC_PIN1_UART2_RTS	   2             //PORTC1配置为串口2的RTS引脚
#define PORTC_PIN1_PWMB1_CH1       3             //PORTC1配置为PWMBASE1的通道1
#define PORTC_PIN1_TIMP0_IN0       4             //PORTC1配置为TIMPLUS0的输入0
#define PORTC_PIN1_TIMP0_OUT_L     5             //PORTC1配置为TIMPLUS0的低16位定时器的输出

#define PORTC_PIN2_GPIO		 	   0             //PORTC2配置为GPIOC2
#define PORTC_PIN2_SPI1_MOSI	   1             //PORTC2配置为SPI1的主出从入
#define PORTC_PIN2_PWMB1_CH2       2             //PORTC2配置为PWMBASE1的通道2
#define PORTC_PIN2_PWMP1_BRK2      3             //PORTC2配置为PWMPLUS1的BREAK2
#define PORTC_PIN2_TIMP0_IN1       4             //PORTC2配置为TIMPLUS0的输入1
#define PORTC_PIN2_TIMP0_OUT_H     5             //PORTC2配置为TIMPLUS0的高16位定时器的输出

#define PORTC_PIN3_GPIO		 	   0             //PORTC3配置为GPIOC3
#define PORTC_PIN3_UART0_TX	       1             //PORTC3配置为串口0的发送引脚
#define PORTC_PIN3_IIC0_SCL	       2             //PORTC3配置为IIC0的时钟引脚
#define PORTC_PIN3_PWMP1_CH1N      3             //PORTC3配置为PWMPLUS1的通道1N
#define PORTC_PIN3_TIMP0_HALL0     4             //PORTC3配置为TIMPLUS0的HALL0
#define PORTC_PIN3_CMP2_VN		   5             //PORTC3配置为比较器2的N端输入

#define PORTC_PIN4_GPIO		 	   0             //PORTC4配置为GPIOC4
#define PORTC_PIN4_UART0_RX	       1             //PORTC4配置为串口0的接收引脚
#define PORTC_PIN4_IIC0_SDA	       2             //PORTC4配置为IIC0的数据引脚
#define PORTC_PIN4_PWMP1_CH2N      3             //PORTC4配置为PWMPLUS1的通道2N
#define PORTC_PIN4_TIMP0_HALL1     4             //PORTC4配置为TIMPLUS0的HALL1
#define PORTC_PIN4_CMP2_VP		   5             //PORTC4配置为比较器2的P端输入

#define PORTC_PIN5_GPIO		 	   0             //PORTC5配置为GPIOC5
#define PORTC_PIN5_TIMP0_HALL2     1             //PORTC5配置为TIMPLUS0的HALL2
#define PORTC_PIN5_TM	           2             //PORTC5配置为RTC的1/2秒标
#define PORTC_PIN5_OPA1_VP		   3             //PORTC5配置为运算放大器1的P端输入


#define PORTC_PIN6_GPIO		 	   0             //PORTC6配置为GPIOC6
#define PORTC_PIN6_IIC1_SCL	       1             //PORTC6配置为IIC1的时钟引脚
#define PORTC_PIN6_PWMP1_CH1       2             //PORTC6配置为PWMPLUS1的通道1
#define PORTC_PIN6_TIMP1_IN1       3             //PORTC6配置为TIMPLUS1的输入1
#define PORTC_PIN6_TIMP1_OUT_H     4             //PORTC6配置为TIMPLUS1的高16位定时器的输出
#define PORTC_PIN6_OPA1_VN		   5             //PORTC6配置为运算放大器1的N端输入

#define PORTC_PIN7_GPIO		 	   0             //PORTC7配置为GPIOC7
#define PORTC_PIN7_IIC1_SDA	       1             //PORTC7配置为IIC1的数据引脚
#define PORTC_PIN7_PWMP1_CH2       2             //PORTC7配置为PWMPLUS1的通道2
#define PORTC_PIN7_TIMP1_IN0       3             //PORTC7配置为TIMPLUS1的输入0
#define PORTC_PIN7_TIMP1_OUT_L     4             //PORTC7配置为TIMPLUS1的低16位定时器的输出
#define PORTC_PIN7_OPA1_OUT		   5             //PORTC7配置为运算放大器1的输出
#define PORTC_PIN7_ADC_CH10	       6             //PORTC7配置为ADC的通道10


void PORT_Init(PORT_InitTypeDef* PORT_InitStruct);               //PORT初始化函数
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct);             //PORT配置寄存器函数

#endif //__DP32G030_PORT_H__
