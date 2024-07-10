#ifndef __DP32G030_GPIO_H__
#define	__DP32G030_GPIO_H__

#include "DP32G030.h"

//断言  GPIOA  
#define IS_GPIO_ALL(GPIO) (((GPIO) == GPIOA) || ((GPIO) == GPIOB) || ((GPIO) == GPIOC))
    
#define GPIO_PIN0                  0             //引脚0
#define GPIO_PIN1                  1             //引脚1
#define GPIO_PIN2                  2             //引脚2
#define GPIO_PIN3                  3             //引脚3
#define GPIO_PIN4                  4             //引脚4
#define GPIO_PIN5                  5             //引脚5
#define GPIO_PIN6                  6             //引脚6
#define GPIO_PIN7                  7             //引脚7
#define GPIO_PIN8                  8             //引脚8
#define GPIO_PIN9                  9             //引脚9
#define GPIO_PIN10                 10            //引脚10
#define GPIO_PIN11                 11            //引脚11
#define GPIO_PIN12                 12            //引脚12
#define GPIO_PIN13                 13            //引脚13
#define GPIO_PIN14                 14            //引脚14
#define GPIO_PIN15                 15            //引脚15

#define IS_GPIOA_PIN(PIN)   (((PIN) == GPIO_PIN0)  || ((PIN) == GPIO_PIN1)  ||  \
                             ((PIN) == GPIO_PIN2)  || ((PIN) == GPIO_PIN3)  ||  \
							 ((PIN) == GPIO_PIN4)  || ((PIN) == GPIO_PIN5)  ||  \
							 ((PIN) == GPIO_PIN6)  || ((PIN) == GPIO_PIN7)  ||  \
							 ((PIN) == GPIO_PIN8)  || ((PIN) == GPIO_PIN9)  ||  \
							 ((PIN) == GPIO_PIN10) || ((PIN) == GPIO_PIN11) ||  \
							 ((PIN) == GPIO_PIN12) || ((PIN) == GPIO_PIN13) ||  \
							 ((PIN) == GPIO_PIN14) || ((PIN) == GPIO_PIN15) )
							 
#define IS_GPIOB_PIN(PIN)   (((PIN) == GPIO_PIN0)  || ((PIN) == GPIO_PIN1)  ||  \
                             ((PIN) == GPIO_PIN2)  || ((PIN) == GPIO_PIN3)  ||  \
							 ((PIN) == GPIO_PIN4)  || ((PIN) == GPIO_PIN5)  ||  \
							 ((PIN) == GPIO_PIN6)  || ((PIN) == GPIO_PIN7)  ||  \
							 ((PIN) == GPIO_PIN8)  || ((PIN) == GPIO_PIN9)  ||  \
							 ((PIN) == GPIO_PIN10) || ((PIN) == GPIO_PIN11) ||  \
							 ((PIN) == GPIO_PIN12) || ((PIN) == GPIO_PIN13) ||  \
							 ((PIN) == GPIO_PIN14) || ((PIN) == GPIO_PIN15) )							 
							 
#define IS_GPIOC_PIN(PIN)   (((PIN) == GPIO_PIN0)  || ((PIN) == GPIO_PIN1)  ||  \
                             ((PIN) == GPIO_PIN2)  || ((PIN) == GPIO_PIN3)  ||  \
							 ((PIN) == GPIO_PIN4)  || ((PIN) == GPIO_PIN5)  ||  \
							 ((PIN) == GPIO_PIN6)  || ((PIN) == GPIO_PIN7)  )							 

typedef enum
{ 
	MODE_FLOATING_IN = 0x00,    // 浮空输入
	MODE_PU_IN =       0x01,    // 上拉输入
	MODE_PD_IN =       0x02,    // 下拉输入
	MODE_PP_OUT =      0x03,    // 推挽输出
	MODE_OD_OUT =      0x04,    // 开漏输出
} Mode_TypeDef;

//断言  GPIO模式
#define IS_GPIO_MODE(MODE) (((MODE) == MODE_FLOATING_IN) || ((MODE) == MODE_PU_IN)  || \
                            ((MODE) == MODE_PD_IN)       || ((MODE) == MODE_PP_OUT) || \
                            ((MODE) == MODE_OD_OUT) )

typedef enum
{ 
	WAKEUP_EDGE_FALL =  0x00,    // 下降沿唤醒
	WAKEUP_EDGE_RISE =  0x01,    // 上升沿唤醒
} WakeUpEdge_TypeDef;

typedef enum
{ 
	WAKEUP_DISABLE =  0x00,    // 禁止唤醒
	WAKEUP_ENABLE =   0x01,    // 使能唤醒
} WakeUpEn_TypeDef;


//断言  GPIO唤醒使能
#define IS_GPIO_WAKEUP(WAKEUP) (((WAKEUP) == WAKEUP_DISABLE) || ((WAKEUP) == WAKEUP_ENABLE))

//断言  GPIO唤醒边沿
#define IS_GPIO_WAKEUP_EDGE(WAKEUP_EDGE) (((WAKEUP_EDGE) == WAKEUP_EDGE_FALL) || ((WAKEUP_EDGE) == WAKEUP_EDGE_RISE))


typedef struct
{            
    uint8_t              Pin;               //引脚号                      
    Mode_TypeDef         Mode;              //模式
	WakeUpEdge_TypeDef   WakeUp_Edge;       //PORT的唤醒沿  
	WakeUpEn_TypeDef     WakeUp_En;         //唤醒使能	
} GPIO_InitTypeDef;

void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);        //GPIO初始化

void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//将参数指定的引脚电平置高
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//将参数指定的引脚电平置低
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//将参数指定的引脚电平反转
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);					//读取参数指定的引脚的电平状态

#endif //__DP32G030_GPIO_H__
