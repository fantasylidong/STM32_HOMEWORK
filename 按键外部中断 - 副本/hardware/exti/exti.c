#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//外部中断 驱动代码			   
////////////////////////////////////////////////////////////////////////////////// 	  
int i,j,k;
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY3==0)	 //按键3 //if(EXTI->PR & 0x1)
	{
		if(i<=99)i++;

	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
 void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	 //按键3 //if(EXTI->PR & 0x1)
	{
		LED2=!LED2;
		GPIOE->ODR &= ~(0xff<<8);
		LED_SEL=0;
		if(j<=99)j++;
		SetLed(3,j/10);
		delay_us(100);
		SetLed(3,'x');
		SetLed(4,j%10);
		delay_us(100);
		SetLed(4,'x');
	}		 
	EXTI->PR=1<<1;  //清除LINE0上的中断标志位  
}
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==0)	 //按键3 //if(EXTI->PR & 0x1)
	{
		if(k<=99)k++;
		GPIOE->ODR &= ~(0xff<<8);
		LED_SEL=0;
		SetLed(0,k/10);
		delay_us(100);
		SetLed(0,'x');
		SetLed(1,k%10);
		delay_us(100);
		SetLed(1,'x');
	}		 
	EXTI->PR=1<<2;  //清除LINE0上的中断标志位  
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
	i=0;
	j=0;
	k=0;
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,1,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,2,FTIR);//下降沿触发
	MY_NVIC_Init(0,2,EXTI0_IRQChannel,2);//抢占2，子优先级0，组2
	MY_NVIC_Init(1,2,EXTI1_IRQChannel,2);//抢占2，子优先级1，组2
	MY_NVIC_Init(2,2,EXTI2_IRQChannel,2);//抢占2，子优先级2，组2
}












