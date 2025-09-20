#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor=P1^0;
unsigned char Counter,Compare;
unsigned char KeyNum,Speed;

void main()
{
	Timer0_Init();
	Nixie(1,0);
	while(1)
  {
    KeyNum=Key();
		if(KeyNum)
		{
			//Speed++;
			//Speed%=4;	
			Speed=KeyNum;
			if(Speed==1)
			{
				Compare=20;
			}
			if(Speed==2)
			{
				Compare=50;
			}
			if(Speed==3)
			{
				Compare=100;
			}
			if(Speed==4)
			{
				Compare=0;
			}
			
		}
		Nixie(1,Speed);
  }
}


void Timer0_Routine() interrupt  1
{

  TL0 = 0xA4;				//设置定时初始值
  TH0 = 0xFF;				//设置定时初始值
	
	Counter++;
	Counter%=100;
	
	if(Counter<Compare)
	{
		Motor=1;
	}
	else
	{
	  Motor=0;
	}
}