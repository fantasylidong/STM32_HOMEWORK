#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
u8 light;	 
//按键输入实验
void Led(int num)
{
	light=0xff;
	LED_SEL=0;
	GPIOE->ODR &= ~(0xff<<8);
	SetLed(7, num%10);
	delay_us(100);
	SetLed(7,'x');
	SetLed(6,num/10);
	delay_us(100);
	SetLed(6,'x');
	GPIOE->ODR &= ~(0xff<<8);
	LED_SEL=1;
	delay_us(100-num);
	GPIOE->ODR |= (light<<8);
	delay_us(num);
	GPIOE->ODR &= ~(0xff<<8);

}

int main(void)
{								  
	u8 t;
	int Light=50;		  
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
					if(Light>0){Light--;
					GPIOE->ODR &= ~(0xff<<8);}
					break;
				case 2:
					Light=50;GPIOE->ODR &= ~(0xff<<8);
					break;
				case 3:
					if(Light<100){Light++;
					GPIOE->ODR &= ~(0xff<<8);}
					break;
				default:
					{
					Led(Light);
					}
			}	  
	}	 
}

























