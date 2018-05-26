#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"	 	 
//���ڿ��Ź�ʵ��
   
int main(void)
{
	extern int feedtime;	
  	Stm32_Clock_Init(6); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	LED_SEL=0;	  
	WWDG_Init(0x7f,0x5f,8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		SetLed(4,feedtime/1000);
		delay_ms(1);
		SetLed(5,feedtime/100%10);
		delay_ms(1)	;
		SetLed(6,feedtime/10%10);
		delay_ms(1);
		SetLed(7,feedtime%10%10);
		delay_ms(1)	;
		if(feedtime==9999)feedtime=0;		  	   
	}	 
}

























