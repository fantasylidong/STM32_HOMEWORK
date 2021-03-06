#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"	
#include "includes.h"	 
//Mini STM32开发板扩展实例 8
//ucos 实验
//正点原子@ALIENTEK
//技术支持：www.openedv.com

 
//设置任务堆栈大小
#define LED_STK_SIZE     64
#define LED1_STK_SIZE    64
#define START_STK_SIZE   128
#define WATCH_STK_SIZE    64
//设置任务优先级
#define LED_TASK_Prio       9
#define LED1_TASK_Prio      5
#define START_TASK_Prio     10
#define WATCH_TASK_Prio     8
//任务堆栈
OS_STK  TASK_LED1_STK[LED_STK_SIZE];
OS_STK  TASK_LED_STK[LED_STK_SIZE];
OS_STK  TASK_START_STK[START_STK_SIZE];
OS_STK  TASK_WATCH_STK[WATCH_STK_SIZE];
//任务申明
void TaskStart(void *pdata);
void TaskLed(void *pdata);
void TaskLed1(void *pdata);
void TaskWatch(void *pdata);
//系统时钟配置函数
void SysTick_Configuration(void);
int second,minute,hour,TEMP;
	 
//Mini STM32开发板ucos范例
//基于ucos2.52内核.
//正点原子@ALIENTEK
//www.openedv.com
//2010.12.15			 
int main(void)
{			 	   
	Stm32_Clock_Init(6); //系统时钟设置
	delay_init(72);	     //延时初始化 
	uart_init(72,9600);	 //串口初始化为9600
	//***重要***//
	LED_Init();		  	 //LED初始化
	second=0;minute=0;hour=0;
	//Timerx_Init( 10000,10000 );//10Khz的计数频率，计数到5000为500ms  
	SysTick_Configuration();
	LED_SEL=0;
	//***重要***//
	OSInit(); // 操作系统初始化
	//***重要***//
	OSTaskCreate( TaskStart,	//task pointer
					(void *)0,	//parameter
					(OS_STK *)&TASK_START_STK[START_STK_SIZE-1],	//task stack top pointer
					START_TASK_Prio );	//task priority
		//***重要***//
	OSStart();	 // 启动操作系统
	return 0;	   
}
//开始任务
void TaskStart(void * pdata)
{
	pdata = pdata; 
	OS_ENTER_CRITICAL();   
	//***重要***//
	OSTaskCreate( TaskLed, (void * )0, (OS_STK *)&TASK_LED_STK[LED_STK_SIZE-1], LED_TASK_Prio);
	OSTaskCreate( TaskLed1, (void * )0, (OS_STK *)&TASK_LED1_STK[LED1_STK_SIZE-1], LED1_TASK_Prio);
	//OSTaskSuspend(START_TASK_Prio);	//suspend but not delete
	OSTaskCreate( TaskLed, (void * )0, (OS_STK *)&TASK_WATCH_STK[WATCH_STK_SIZE-1], WATCH_TASK_Prio);
	OS_EXIT_CRITICAL();
}
//任务1
//控制DS0的亮灭.
void TaskLed(void *pdata)
{
	while(1)
	{
				SetLed(0,hour/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(1,hour%10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(3,minute/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(4,minute%10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(6,second/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(7,second%10);
		OSTimeDlyHMSM(0,0,0,1);	
	}
}
//任务2
//控制DS1的亮灭.
void TaskLed1(void *pdata)
{
	while(1)
	{
		LED6 = !LED6;
		OSTimeDlyHMSM(0,0,0,200);	
	}
}
//数字钟
void TaskWatch(void *pdata)
{
	while(1)
	{
		SetLed(0,hour/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(1,hour%10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(3,minute/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(4,minute%10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(6,second/10);
		OSTimeDlyHMSM(0,0,0,1);
		SetLed(7,second%10);
		OSTimeDlyHMSM(0,0,0,1);
	}
}	  
//系统时钟中断服务函数
void SysTick_Handler(void)
{
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR  */
	OSIntNesting++;
	TEMP++;
    if(TEMP==1000)
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
		TEMP=0;
	}
    OS_EXIT_CRITICAL();

    OSTimeTick();        /* Call uC/OS-II's OSTimeTick()               */

    OSIntExit();         /* Tell uC/OS-II that we are leaving the ISR  */
}
//系统时钟配置，设计1ms产生一次中断
void SysTick_Configuration(void)
{
 	SysTick->CTRL &= ~(1<<2);//SYSTICK使用外部时钟源
	SysTick->CTRL |= 1<<1;   //开启SYSTICK中断
	SysTick->LOAD = 9000;    //产生1ms中断
	//bit2清空,选择外部时钟  HCLK/8
	//MY_NVIC_Init(3,3,SystemHandler_SysTick,2);//组2，最低优先级 
	SysTick->CTRL |= 1<<0;   //开启SYSTICK
}




















