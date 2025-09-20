#include <REGX52.H>
#include "Timer0.h"
#include"Key.h"
#include "Delay.h"
#include <INTRINS.H>

//void Timer0_Init(void)		//1毫秒@11.0592MHz
//{
//	TMOD=0x01;//TMOD不可以按位寻址
//	//TMOD=TMOD&0xF0;//把TMOD的低四位清零，高四位保持不变
//	//TMOD=TMOD|0x01;//把TMOD的最低位置1，高四位保持不变
//	TH0=64535/256;
//	TL0=64535%256;
//	ET0=1;
//	EA=1;
//	PT0=0;
//	TR0=1;
//}
unsigned int Keynum,LEDMode;
void main()
	
{
	P2=0xFE;
	Timer0_Init();
	while(1)
	{
		
		Keynum=Key();
		if(Keynum)
		{
			if(Keynum==1)
			{
				LEDMode++;
				if(LEDMode>=2)
					LEDMode=0;
			}
		  
		}
	}
}

//定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		if(LEDMode==0)
		{
			P2=_crol_(P2,1);
		}
		if(LEDMode==1)
		{
			P2=_cror_(P2,1);
		}
		
	}
}





