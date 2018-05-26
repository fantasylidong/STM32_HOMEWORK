/****************LED���й�ʵ�ֺ���********************
* ���ߣ�������
******************************************************************/

#include "led.h"

/***************************����ܶ�ѡ***************************/
                 //0   1   2     3    4    5    6    7    8    9
u8 segTable[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x48,0x40};
u8 b[] = {0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
u8 segTablePortation[] = {0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
u8 a[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x3f,0x5e,0xf9,0x06,0x6d,0x3f,0x6d,0x3f,0x66,0x3f,0x06,0x06,0x07};
	/*	SetLed(0, 0x39);
		delay_us(interval);
		SetLed(1, 0x3f);
		delay_us(interval);
		SetLed(2, 0x5e);
		delay_us(interval);
		SetLed(3, 0xf9);
		delay_us(interval);
		SetLed(4, 0x3f);
		delay_us(interval);
		SetLed(5, 0x06);
		delay_us(interval);
		SetLed(6, 0x3f);
		delay_us(interval);
		SetLed(7, 0x07);
		delay_us(interval);	  */
/****************************************************
* ��ʼ��������LED�Ƶ����Ŷ˿�
******************************************************/
void LED_Init()
{
	RCC->APB2ENR|=1<<0;	//ʹ��AFIO
	RCC->APB2ENR|=1<<3;  //ʹ��PORTBʱ��			   //R0�Ĵ�����0*00000001��Ϊ0*00000009
	RCC->APB2ENR|=1<<6;	//ʹ��PORTEʱ��	 
	
	AFIO->MAPR |= 0x02000000; //���ÿ�����	����PB.3ΪI/O�ڿ��ã��ҿ���SW����
	   	 
	GPIOB->CRL &= 0xFFFF0000;
	GPIOB->CRL |= 0x00003333; //PB.3�������
	GPIOB->ODR |= 0x000000FF; //PB.3�����
											  
	GPIOE->CRH&=0X00000000;
	GPIOE->CRH|=0X33333333; //PE.8-15�������
	GPIOE->ODR|=0x0000FF00; //PE.8-15����� 	
}

/***************************************
* ��ˮ��ѡ�񣬻�����ܶ�ѡ
* value:��ʾ����ֵ��Ӧ�Ķ�ѡ������ֵ
****************************************/
void LedValue(u8 value)
{
	GPIOE->ODR &= ~(0xff<<8);
	GPIOE->ODR |= value<<8;
 //	  LED0 = (value&0x01)?1:0;
 //		LED1 = (value&0x02)?1:0;
 //		LED2 = (value&0x04)?1:0;
 //		LED3 = (value&0x08)?1:0;
 //		LED4 = (value&0x10)?1:0;
 //		LED5 = (value&0x20)?1:0;
 //		LED6 = (value&0x40)?1:0;
 //		LED7 = (value&0x80)?1:0;	
}

/***************************************
* �������ʾ����С�������ֵ
* ���� w:��ʾ��λ�ã���λѡ����-�ң�0-7
*      value:Ҫ��ʾ����ֵ
****************************************/
void SetLedm(u8 w, u8 value)
{
	SEL0 = w%2;
	SEL1 = w/2%2;
	SEL2 = w/4;
	//LedValue(segTable[value]);
	LedValue(b[value]);
}
void SetLed(u8 w, u8 value)
{
	SEL0 = w%2;
	SEL1 = w/2%2;
	SEL2 = w/4;
	//LedValue(segTable[value]);
	LedValue(a[value]);
}
 void SetLed1(u8 w, u8 value)
{
	SEL0 = w%2;
	SEL1 = w/2%2;
	SEL2 = w/4;
	LedValue(segTable[value]);
	//LedValue(a[value]);
}

/***************************************
* �������ʾ��С�������ֵ
* ���� w:��ʾ��λ�ã���λѡ����-�ң�0-7
*      value:Ҫ��ʾ����ֵ
****************************************/
void PortationDisplay(u8 w, u8 value)
{
	SEL0 = w%2;
	SEL1 = w/2%2;
	SEL2 = w/4;
	LedValue( segTablePortation[value] );
}


