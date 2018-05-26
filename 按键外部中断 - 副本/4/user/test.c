#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 
//Mini STM32开发板范例代码4
//外部中断实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	  
int i,j,k,flag,light;
//注意,此代码还是无法进行SWD仿真!因为使用了中断,没法用普通的方法来考虑间歇复用SWD口! 
int main(void)
{
	
 	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();		  	 //初始化与LED连接的硬件接口
	EXTIX_Init();		 //外部中断初始化
	i=0;j=0;k=0;flag=0;
	while(1)
	{	
	/*	LED_SEL=0;
		SetLed(0,k/10);
		delay_us(100);
		SetLed(0,'x');
		SetLed(1,k%10);
		delay_us(100);
		SetLed(1,'x');
		SetLed(3,j/10);
		delay_us(100);
		SetLed(3,'x');
		SetLed(4,j%10);
		delay_us(100);
		SetLed(4,'x');  
		SetLed(6,i/10);
		delay_us(100);
		SetLed(6,'x');
		SetLed(7,i%10);
		delay_us(100);
		SetLed(7,'x');  
		delay_us(100);	*/
		if(flag==1)light=0x01;
		else if(flag==2)light=0x02;
		else light=0x04;
		LED_SEL=1;
		GPIOE->ODR &= ~(0xff<<8);
		GPIOE->ODR |= (light<<8);
		delay_us(100);
		LED_SEL=0;
		SetLed(7,flag);
		delay_us(100);
		  
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
























