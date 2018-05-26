#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
u8 light;	 	 
//按键输入实验
int main(void)
{								  
	u8 t;
	int k;
	int flag=0;	  
	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();          //初始化与按键连接的硬件接口
	GPIOE->ODR &= ~(0xff<<8);
	while(1)
	{
		t = KEY_Scan();//得到键值
	   						   
			switch(t)
			{				 
				case 1:
					flag=1;
					GPIOE->ODR &= ~(0xff<<8);
					light=0x01;
					break;
				case 2:
					flag=2;
					GPIOE->ODR &= ~(0xff<<8);
					light=0x02;
					break;
				case 3:
					flag=3;
					GPIOE->ODR &= ~(0xff<<8);				
					light=0x04;
					break;
				default:{
						  LED_SEL=0;
					
						  SetLed(7,flag);
						  delay_ms(10);
						  LED_SEL=1;
						  GPIOE->ODR &= ~(0xff<<8);
						  GPIOE->ODR |= (light<<8);
						   for(k=0;k<10;k++)
						   delay_us(100);
			}
			
		}
		
	}	 
}

























