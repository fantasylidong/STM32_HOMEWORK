#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//外部中断 驱动代码			   
////////////////////////////////////////////////////////////////////////////////// 	  

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY3==0)	 //按键3
	{
		LED7=!LED7;
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}

//int gKey1Times = 0;
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);//消抖
//	if(KEY3==0)	 //按键3
//	{
//		gKey1Times++;
//	}		 
//	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
//}

//外部中断初始化程序
//初始化PC0-2为中断输入.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	GPIOC->CRL&=0XFFFFFFF0;//PC0-2设置成输入	  
	GPIOC->CRL|=0X00000008;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);//抢占2，子优先级2，组2
}












