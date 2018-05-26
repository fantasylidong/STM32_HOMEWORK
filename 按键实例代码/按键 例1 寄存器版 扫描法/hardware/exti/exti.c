#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������			   
////////////////////////////////////////////////////////////////////////////////// 	  

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==0)	 //����3
	{
		LED7=!LED7;
	}		 
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}

//int gKey1Times = 0;
//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);//����
//	if(KEY3==0)	 //����3
//	{
//		gKey1Times++;
//	}		 
//	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
//}

//�ⲿ�жϳ�ʼ������
//��ʼ��PC0-2Ϊ�ж�����.
void EXTIX_Init(void)
{
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFFFF0;//PC0-2���ó�����	  
	GPIOC->CRL|=0X00000008;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���

	MY_NVIC_Init(2,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
}












