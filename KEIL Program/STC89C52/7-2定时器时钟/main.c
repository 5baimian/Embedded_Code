#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"
#include "LCD1602.h"
unsigned char sec=55,Min=59,Hour=23;
void main()
{
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	
	while(1)
  {
    LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,sec,2);
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
		sec++;
		if(sec>=60)
		{
			sec=0;
			Min++;
			if(Min>=60)
			{
				Min=0;
				Hour++;
				if(Hour>=24)
				{
					Hour=0;
				}
			}
		}
		
	}
}