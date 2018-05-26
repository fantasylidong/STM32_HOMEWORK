#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 	 
//定时器中断 实验
extern int second,minute,hour;   
int main(void)
{			
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();
	second=0;minute=0;hour=0;		  	 //初始化与LED连接的硬件接口
	Timerx_Init( 7199,9999 );//10Khz的计数频率，计数到5000为500ms  
	LED_SEL=0;
   	while(1)
	{
	   	SetLed(0,hour/10);
		delay_ms(1);
		SetLed(1,hour%10);
		delay_ms(1);
		SetLed(3,minute/10);
		delay_ms(1);
		SetLed(4,minute%10);
		delay_ms(1);
		SetLed(6,second/10);
		delay_ms(1);
		SetLed(7,second%10);
		delay_ms(1);
	}	 
}

























