#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 
//Mini STM32�����巶������4
//�ⲿ�ж�ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com	  

//ע��,�˴��뻹���޷�����SWD����!��Ϊʹ�����ж�,û������ͨ�ķ��������Ǽ�Ъ����SWD��! 
int main(void)
{			
 	Stm32_Clock_Init(6); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
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
// 	Stm32_Clock_Init(6); //ϵͳʱ������
//	delay_init(72);	     //��ʱ��ʼ��
//	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
//	LED_SEL = 0;
//	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
//	while(1)
//	{
//		SetLed(1, gKey1Times%2);
//	}	 
//}
























