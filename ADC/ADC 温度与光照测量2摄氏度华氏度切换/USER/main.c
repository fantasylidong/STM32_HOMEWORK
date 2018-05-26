/******************************�¶�����ղ���************************
* �¶������
* �¶���ʾ����ߣ�������ʾ���ұ�
******************************************************************/

#include "sys.h"
#include "led.h"
#include "delay.h"
#include "adc.h"
#include "key.h"
/***************************������*****************************/
int main()
{
 	float adcx = 0.0;
	u16 adcValue = 0;
	u8 t,i = 0;
		int flag;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	TemperatureAndLightAdcInit();// �¶Ⱥ͹���ADת������ʼ��
	 flag=2;
	LED_Init();
	LED_SEL = 0;
	adcx = GetTemperature(); //ʹ��PC5 ADC1, ͨ��15
	adcValue = GetLightAdc(14); //ʹ��PC4 ADC1, ͨ��14
	while(1)
	{
			i++;
			if( i > 50 ) //��Լÿ��350ms����ɨ��һ��ADC��ֵ
				{
					adcx = GetTemperature(); //��ȡ�¶�ֵ. ʹ��PC5 ADC1, ͨ��15
					if(flag==2)adcx=1.8*adcx+32;
					adcValue = GetLightAdc(14); //��ȡ����ADת��ֵ. ʹ��PC4 ADC1, ͨ��14
					i = 0;
				}	
			t = KEY_Scan();//�õ���ֵ
	   							   
			switch(t)
			{				 
				case 1:
					flag=1;	
					break;
				case 2:
						 flag=2;

					break;

				default:
					{
					//�¶�

		SetLed(0, adcx/10);
		delay_ms(1);
		PortationDisplay(1,(u8)adcx%10);
		delay_ms(1);
		SetLed(2, (u8)(adcx*10)%10);
		delay_ms(1);
					

	}	
	}
}

}