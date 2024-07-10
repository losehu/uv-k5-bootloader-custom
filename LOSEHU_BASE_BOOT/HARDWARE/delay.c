#include "delay.h"

static uint8_t  fac_us = 0;							//us延时倍乘数			   
static uint32_t fac_ms = 0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
			   
void delay_init(void)
{
	fac_us = SystemCoreClock/1000000;	
	fac_ms = fac_us*1000;
}

//延时nus
//nus为要延时的us数.		    								   
void delay_us(uint32_t nus)
{		
	uint32_t temp;	
	
	SysTick->LOAD = nus*fac_us; 				//时间加载	  		 
	SysTick->VAL = 0x00;        				//清空计数器
	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;  //开始倒数 	 
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      	 			//关闭计数器
	SysTick->VAL = 0x00;       				//清空计数器	 
}
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*1000/SystemCoreClock
//SystemCoreClock单位为Hz,nms单位为ms
//对24M条件下,nms<=699
//对48M条件下,nms<=349
//对72M条件下,nms<=233
void delay_nms(uint16_t nms)
{	 		  	  
	uint32_t temp;
	
	SysTick->LOAD =(uint32_t)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk;  //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;   //关闭计数器
	SysTick->VAL =0x00;       				//清空计数器	  	    
} 

void delay_ms(uint16_t nms)
{	 		  	  	
	while(nms>200)
	{
		delay_nms(200);
		nms-=200;
	}
	if(nms>0)
	{
		delay_nms(nms);
	}	    
}
