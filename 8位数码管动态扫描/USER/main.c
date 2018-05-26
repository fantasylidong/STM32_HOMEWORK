/******************************8位数码管动态扫描************************
* 8位数码管动态扫描
* 从左到右显示code.学号
***********************************************************************/

#include "sys.h"
#include "delay.h"
#include "led.h"

 
#define uchar unsigned char

uchar show_w1,show_w2,show_w3,show_w4,show_w5,show_w6,show_w7,show_w8,flag,count;
uchar seg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char clock[]={0,1,2,3,4,5,6,7,8,9};
int min=5,sec1=0,sec2=1;

/***************************主函数*****************************/
int main()
{
	int j;	 
	int k;
	int interval = 1;
	int interval1 = 1000;
	//uchar i;

	Stm32_Clock_Init( 6 ); // (12M的)6倍频
	delay_init( 72 );
	LED_Init();

	LED_SEL = 0;
	show_w1=0;
	show_w2=1;
	show_w3=2;
	show_w4=3;
	show_w5=4;
	show_w6=5;
	show_w7=6;
	show_w8=7;
	
 
		  	while(1)
	{
	   	 //学号循环
		int i,j;
		for(i=0;i<22;i++)
		{
		    for(j=0;j<50;j++)
			{
   		    SetLed(0, show_w1%22);
		    //delay_ms(interval);
		    delay_ms(interval);
		    SetLed(1, show_w2%22);
		    //delay_ms(interval);
			delay_ms(interval);
			SetLed(2, show_w3%22);
			//delay_ms(interval);
			delay_ms(interval);
			SetLed(3, show_w4%22);
			//delay_ms(interval);
			delay_ms(interval);
			SetLed(4, show_w5%22);
			//delay_ms(interval);
			delay_ms(interval);
			SetLed(5, show_w6%22);
			//delay_ms(interval);
			delay_ms(interval);
			SetLed(6, show_w7%22);
			//delay_ms(interval);
			delay_ms(interval);
			SetLed(7, show_w8%22);
			//delay_ms(interval);
			delay_ms(interval);	  
			}	
				show_w1++;
				show_w2++;
				show_w3++;
				show_w4++;
				show_w5++;
				show_w6++;
				show_w7++;
				show_w8++;	
 		 }	 
		   
	}	 
  }
