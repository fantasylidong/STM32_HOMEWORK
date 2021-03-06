/******************************温度与光照测量************************
* 温度与光照
* 温度显示与左边，光照显示在右边
******************************************************************/

#include "sys.h"
#include "led.h"
#include "delay.h"
#include "adc.h"

/***************************主函数*****************************/
int main()
{
 	float adcx = 0.0;
	u16 adcValue = 0;
	u8 i = 0;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	
	AdcInitForInternalChannels();// 温度和光照AD转换器初始化

	LED_Init();
	LED_SEL = 0;
	adcx = GetTemperature(); //使用PC5 ADC1, 通道15
	adcValue = GetLightAdc(17); //使用PC4 ADC1, 通道14
	while(1)
	{		
		i++;
		if( i > 50 ) //大约每隔350ms重新扫描一次ADC的值
		{
			adcx = GetTemperature(); //获取温度值. 使用PC5 ADC1, 通道15
			adcValue =GetLightAdc(17) ; //获取光照AD转换值. 使用PC4 ADC1, 通道14
			i = 0;
		}
		//温度
		SetLed(0, adcx/10);
		delay_ms(1);
		PortationDisplay(1,(u8)adcx%10);
		delay_ms(1);
		SetLed(2, (u8)(adcx*10)%10);
		delay_ms(1);
		
		//光照
		SetLed(4, adcValue/1000);
		delay_ms(1);
		SetLed(5, adcValue%1000/100);
		delay_ms(1);
		SetLed(6, adcValue%100/10);
		delay_ms(1);
		SetLed(7, adcValue%10);
		delay_ms(1);
	}	
}

