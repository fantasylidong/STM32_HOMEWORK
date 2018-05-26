#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 	 
//��ʱ���ж� ʵ��
extern int second,minute,hour;   
int main(void)
{			
 	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();
	second=0;minute=0;hour=0;		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	Timerx_Init( 7199,9999 );//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
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

























