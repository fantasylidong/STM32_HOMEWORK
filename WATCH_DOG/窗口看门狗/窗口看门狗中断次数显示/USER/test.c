#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"	 	 
//窗口看门狗实验
   
int main(void)
{
	extern int feedtime;	
  	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	LED_SEL=0;	  
	WWDG_Init(0x7f,0x5f,8);//计数器值为7f,窗口寄存器为5f,分频数为8	   
 	while(1)
	{
		SetLed(4,feedtime/1000);
		delay_ms(1);
		SetLed(5,feedtime/100%10);
		delay_ms(1)	;
		SetLed(6,feedtime/10%10);
		delay_ms(1);
		SetLed(7,feedtime%10%10);
		delay_ms(1)	;
		if(feedtime==9999)feedtime=0;		  	   
	}	 
}

























