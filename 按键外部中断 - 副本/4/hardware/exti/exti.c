#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ⲿ�ж� ��������			   
////////////////////////////////////////////////////////////////////////////////// 	  
extern int i,j,k,flag;
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY3==0)	 //����3 //if(EXTI->PR & 0x1)
	{
		flag=3;
		if(k<99)k++;
		//delay_ms(5000);
	}		 
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}

void EXTI1_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY2==0)	 //����3 //if(EXTI->PR & 0x1)
	{
		flag=2;
		
		if(j<99)j++;
		//delay_ms(5000);
	}		 
	EXTI->PR=1<<1;  //���LINE0�ϵ��жϱ�־λ  
}
void EXTI2_IRQHandler(void)
{
	
	delay_ms(10);//����
	if(KEY1==0)	 //����3 //if(EXTI->PR & 0x1)
	{
		flag=1;

		if(i<99)i++;
		//delay_ms(5000);
	}		 
	EXTI->PR=1<<2;  //���LINE0�ϵ��жϱ�־λ  
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
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���
	MY_NVIC_Init(2,2,EXTI2_IRQChannel,2);//��ռ2�������ȼ�2����2
	MY_NVIC_Init(1,1,EXTI1_IRQChannel,2);//��ռ1�������ȼ�2����2
	MY_NVIC_Init(0,0,EXTI0_IRQChannel,2);//��ռ0�������ȼ�2����2
}












