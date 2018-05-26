#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 

#define SampleNum_Keycheck 60

///*
int main(void)
{
	int Key_count_STD; //设置按键检测次数
	int Key_count;	 //按键实际按下次数
	int Key_C = 1;//检测结束时，key当前的状态
	int Key_P = 1;//检测结束时，对key能够确定的前一个状态
	int refValue = 0x80;
	vu32 idrC;
				
 	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();		  	 //初始化与LED连接的硬件接口
	KEY_Init();
	LED_SEL = 1;
	GPIOE->ODR = 0;

	Key_count_STD = SampleNum_Keycheck; //设置按键检测次数
	Key_count = refValue+60/3*2;

	while(1)
	{
		delay_us(50);	// 延时0.05ms
		idrC = 	GPIOC->IDR;
		
		if((idrC & 0x1) == 0) // 进行一次检测
		{
			  Key_count--;
		}
		Key_count_STD--;
		if(Key_count_STD == 0)								 
		{
			if(Key_count < refValue)  // 能确定按键按下
			{
				Key_C=0; //当前状态变成0
				if(Key_P==1)	//前一状态是1。说明是下降沿（按键做动作）
				{
					if(GPIOE->ODR == (0x01<<8)){
						GPIOE->ODR = 0x0;
					}
					else{
						GPIOE->ODR = 0x01<<8;
					}
					Key_P=0;
				}
			}
			else // if(Key_count>=refValue) // 还不能确定按键按下
			{
				Key_C=1;
				if(Key_P==0)
					Key_P=1;	//上升沿（假设不做动作那就继续）
			}
			Key_count_STD = SampleNum_Keycheck; //重置按键检测次数
			Key_count = refValue+SampleNum_Keycheck/3*2;	 //按键实际按下次数
		}
	}
}
//*/

/*
#define uchar unsigned char
uchar show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7,show_w8,flag,count;
extern int gKey1Times;
int main(void)
{			
 	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化
	LED_Init();		  	 //初始化与LED连接的硬件接口
	LED_SEL = 0;
	EXTIX_Init();		 //外部中断初始化
	while(1)
	{
		SetLed(1, gKey1Times%2);
	}	 
}
//*/























