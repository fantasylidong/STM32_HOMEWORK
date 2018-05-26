#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 
//Mini STM32开发板范例代码4
//外部中断实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	  

//注意,此代码还是无法进行SWD仿真!因为使用了中断,没法用普通的方法来考虑间歇复用SWD口! 
int main(void)
{			
 	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();		  	 //初始化与LED连接的硬件接口
	EXTIX_Init();		 //外部中断初始化
	while(1)
	{
		GPIOE->ODR &= ~(0xff<<8);
		LED_SEL=0;
		if(i<=99)i++;
		SetLed(6,i/10);
		delay_us(100);
		SetLed(6,'x');
		SetLed(7,i%10);
		delay_us(100);
		SetLed(7,'x');	    
		delay_ms(100);	  
	}	 
}


//#define uchar unsigned char
//uchar show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7,show_w8,flag,count;
//extern int gKey1Times;
//int main(void)
//{			
// 	Stm32_Clock_Init(6); //系统时钟设置
//	delay_init(72);	     //延时初始化
//	LED_Init();		  	 //初始化与LED连接的硬件接口
//	LED_SEL = 0;
//	EXTIX_Init();		 //外部中断初始化
//	while(1)
//	{
//		SetLed(1, gKey1Times%2);
//	}	 
//}
























