#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "adc.h"	 	 
//定时器中断 实验
extern int second,minute,hour,day,mouth,year;
int TimeFlag; 
int DayFlag,temp;
float adcx = 0.0;
u16 adcValue = 0;
int MouthLimit[]={31,29,31,30,31,30,31,31,30,31,30,31};
u8 t,i = 0;
void Time_Show()
{
		LED_SEL=0;
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
void Day_Show()
{
		LED_SEL=0;
	 	SetLed(0,year/1000);
		delay_ms(1);
		SetLed(1,year/100%10);
		delay_ms(1);
		SetLed(2,year/10%10);
		delay_ms(1);
		SetLed(3,year%10);
		delay_ms(1);
		SetLed(4,mouth/10);
		delay_ms(1);
		SetLed(5,mouth%10);
		delay_ms(1);
		SetLed(6,day/10);
		delay_ms(1);
		SetLed(7,day%10);
		delay_ms(1);
}
void XueHao_Show()
{
		LED_SEL=0;
	 	SetLed(0,0);
		delay_ms(1);
		SetLed(1,5);
		delay_ms(1);
		SetLed(2,0);
		delay_ms(1);
		SetLed(3,4);
		delay_ms(1);
		SetLed(4,0);
		delay_ms(1);
		SetLed(5,1);
		delay_ms(1);
		SetLed(6,1);
		delay_ms(1);
		SetLed(7,7);
		delay_ms(1);
}
int Judge_RunNian(int year)
{
	if((year%4==0)&&(year%100!=0)||(year%400==0))
		return 1;
	else
		return 0;

}
void Temp_Show()
{
		LED_SEL=0;
		SetLed(0, adcx/10);
		delay_ms(1);
		PortationDisplay(1,(u8)adcx%10);
		delay_ms(1);
		SetLed(2, (u8)(adcx*10)%10);
		delay_ms(1);			
		//光照
		LED_SEL=0;
		SetLed(4, adcValue/1000);
		delay_ms(1);
		SetLed(5, adcValue%1000/100);
		delay_ms(1);
		SetLed(6, adcValue%100/10);
		delay_ms(1);
		SetLed(7, adcValue%10);
		delay_ms(1);	
}

void Time_Init()
{
	 second=0;
	 minute=0;
	 hour=0;
	 TimeFlag=1;
	 while(1)
	 {
	 		t = KEY_Scan();//得到键值	   							   
			switch(t)
			{				 
				case 2:
					if(TimeFlag==3)	return ;
					TimeFlag++;
					break;
				case 1:
				   	if(TimeFlag==1){hour++;if(hour==24)hour=0; }
					else if(TimeFlag==2){minute++;if(minute==60)minute=0;}
					else {second++;if(second==60)second=0;}
					break;
				case 3:
					if(TimeFlag==1){hour--;if(hour==-1)hour=23; }
					else if(TimeFlag==2){minute--;if(minute==-1)minute=59;}
					else {second++;if(second==-1)second=59;}
					break;
				default:
					{
						Time_Show();
					}
	 	 	}
	}
}
void Day_Init()
{
	 day=0;
	 mouth=0;
	 year=2018;
	 DayFlag=1;
	 while(1)
	 {
	 		t = KEY_Scan();//得到键值	   							   
			switch(t)
			{				 
				case 2:
					if(DayFlag==3)	return ;
					DayFlag++;
					if(DayFlag==2)
					{
						if(Judge_RunNian(year))MouthLimit[1]=28;
						else MouthLimit[1]=29;
					}
					break;
				case 1:
				   	if(DayFlag==1)year++;
					else if(DayFlag==2){mouth++;if(mouth==13)mouth%=12;}
					else {day++;if(day>MouthLimit[mouth-1])day=1;}
					break;
				case 3:
					if(DayFlag==1)year--;
					else if(DayFlag==2){mouth--;if(mouth==0)mouth=12;}
					else {day--;if(day==0)day=MouthLimit[mouth-1];}
					break;
				default:
					{
						Day_Show();
					}
	 	 	}
	}
}


int main(void)
{		
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	TemperatureAndLightAdcInit();// 温度和光照AD转换器初始化
	LED_SEL=0;
	LED_Init();		  	 //初始化与LED连接的硬件接口
	Day_Init();			//日期初始化函数
	Time_Init();		   //时间初始化函数
	Timerx_Init( 10000,10000 );//10Khz的计数频率，计数到5000为500ms  
	adcx = GetTemperature(); //使用PC5 ADC1, 通道15
	adcValue = GetLightAdc(14); //使用PC4 ADC1, 通道14
   	while(1)
	{
		i++;
		if( i > 50 ) //大约每隔350ms重新扫描一次ADC的值
		{
			adcx = GetTemperature(); //获取温度值. 使用PC5 ADC1, 通道15
			adcValue = GetLightAdc(14); //获取光照AD转换值. 使用PC4 ADC1, 通道14
			i = 0;
		}	
		if(adcx>25&i>45)
		{
			LED_SEL=1;
			GPIOE->ODR &= ~(0xff<<8);
			LED0=!LED0;
			LED1=!LED1;
			LED2=!LED2;
			LED3=!LED3;
			delay_ms(2);
		}					
		if(adcx<10&i>45)
		{
			LED_SEL=1;
			GPIOE->ODR &= ~(0xff<<8);
			LED7=!LED7;
			LED6=!LED6;
			LED5=!LED5;
			LED4=!LED4;
			delay_ms(2);	
		}
	 	t = KEY_Scan();//得到键值	   							   
		switch(t)
		{				 

				case 1:
				   	for(temp=0;temp<1429;temp++)
						{
							if(temp%25==0)
							{
								adcx = GetTemperature(); //获取温度值. 使用PC5 ADC1, 通道15
								adcValue = GetLightAdc(14); //获取光照AD转换值. 使用PC4 ADC1, 通道14
							}
							Temp_Show();
						}
					break;
				case 2:
					for(temp=0;temp<1250;temp++)
						Day_Show();
					break;
				case 3:
					for(temp=0;temp<1250;temp++)
						XueHao_Show();
					break;
				default:
					{
						Time_Show();
					}
	 	 	
	}
	 }	
}




















