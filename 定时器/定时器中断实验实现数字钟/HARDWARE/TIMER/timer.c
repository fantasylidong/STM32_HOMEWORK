#include "timer.h"
#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
int minute,second,hour;

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR & 0x0001)//溢出中断
	{
		second++;
		if(second>59){
		second=0;
		minute++;
		if(minute>59){
		minute=0;
		hour++;
		if(hour>23)
		hour=0;
		}
		}			    				   				     	    	
	}				   
	TIM3->SR &= ~(1<<0);//清除中断标志位 	    
}

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void Timerx_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR |= 1<<1;//TIM3时钟使能    
 	TIM3->ARR = arr;  //设定计数器自动重装值//刚好1ms    
	TIM3->PSC = psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个要同时设置才可以使用中断
	TIM3->DIER |= 1<<0;   //允许更新中断				
	TIM3->DIER |= 1<<6;   //允许触发中断	   
	TIM3->CR1 |= 0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM3_IRQChannel ,2);//抢占1，子优先级3，组2									 
}














