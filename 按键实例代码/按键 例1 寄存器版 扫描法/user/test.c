#include "sys.h"
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 

#define SampleNum_Keycheck 60

///*
int main(void)
{
	int Key_count_STD; //���ð���������
	int Key_count;	 //����ʵ�ʰ��´���
	int Key_C = 1;//������ʱ��key��ǰ��״̬
	int Key_P = 1;//������ʱ����key�ܹ�ȷ����ǰһ��״̬
	int refValue = 0x80;
	vu32 idrC;
				
 	Stm32_Clock_Init(6); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();
	LED_SEL = 1;
	GPIOE->ODR = 0;

	Key_count_STD = SampleNum_Keycheck; //���ð���������
	Key_count = refValue+60/3*2;

	while(1)
	{
		delay_us(50);	// ��ʱ0.05ms
		idrC = 	GPIOC->IDR;
		
		if((idrC & 0x1) == 0) // ����һ�μ��
		{
			  Key_count--;
		}
		Key_count_STD--;
		if(Key_count_STD == 0)								 
		{
			if(Key_count < refValue)  // ��ȷ����������
			{
				Key_C=0; //��ǰ״̬���0
				if(Key_P==1)	//ǰһ״̬��1��˵�����½��أ�������������
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
			else // if(Key_count>=refValue) // ������ȷ����������
			{
				Key_C=1;
				if(Key_P==0)
					Key_P=1;	//�����أ����費�������Ǿͼ�����
			}
			Key_count_STD = SampleNum_Keycheck; //���ð���������
			Key_count = refValue+SampleNum_Keycheck/3*2;	 //����ʵ�ʰ��´���
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
 	Stm32_Clock_Init(6); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED_SEL = 0;
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
	while(1)
	{
		SetLed(1, gKey1Times%2);
	}	 
}
//*/























