/**
* @brief  利用时钟芯片DS1302使用LCD1602显示时钟，可调时钟
  * @param 
  * @retval 
  */


#include <REGX52.h>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

unsigned char KeyNum,MODE,TimeSelect,TimeSetFlashFlag;
unsigned char Second,Minute;

void TimeShow(void)
{ 
	
	  DS1302_ReadTime();
		
	  LCD_ShowNum(1,1,DS1302_Time[0],2);//年
	  LCD_ShowNum(1,4,DS1302_Time[1],2);//月
		LCD_ShowNum(1,7,DS1302_Time[2],2);//日
		
		LCD_ShowNum(2,1,DS1302_Time[3],2);//时
	  LCD_ShowNum(2,4,DS1302_Time[4],2);//分
		LCD_ShowNum(2,7,DS1302_Time[5],2);//秒
		
		LCD_ShowNum(1,11,DS1302_Time[6],1);//星期
	
}

void TimeSet(void)
{
	if(KeyNum==2)
	{
		TimeSelect++;
		TimeSelect%=6;//到6自动清零
	}
	
	if(KeyNum==3)
	{
		DS1302_Time[TimeSelect]++;
		if(DS1302_Time[0]>99){DS1302_Time[0]=0;}
		if(DS1302_Time[1]>12){DS1302_Time[1]=1;}
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
			DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
        {
					if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
				}
				else
				{
					if(DS1302_Time[2]>28){DS1302_Time[2]=1;}
				}
		}
		
		if(DS1302_Time[3]>23){DS1302_Time[3]=0;}
		if(DS1302_Time[4]>59){DS1302_Time[4]=0;}
		if(DS1302_Time[5]>59){DS1302_Time[5]=0;}
	}
	
	if(KeyNum==4)
	{
		DS1302_Time[TimeSelect]--;
		if(DS1302_Time[0]<1){DS1302_Time[0]=99;}
		if(DS1302_Time[1]<1){DS1302_Time[1]=12;}
		if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
			DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
			
		}
		else if(DS1302_Time[1]==4||DS1302_Time[1]==6||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
		}
		else if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)
        {
					if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
					if(DS1302_Time[2]>29){DS1302_Time[2]=1;}
				}
				else
				{
					if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
					if(DS1302_Time[2]>28){DS1302_Time[2]=1;}//越界判断
				}
		}
		
		if(DS1302_Time[3]<0){DS1302_Time[3]=23;}
		if(DS1302_Time[4]<0){DS1302_Time[4]=59;}
		if(DS1302_Time[5]<0){DS1302_Time[5]=59;}
	}
	//刷新显示
	if(TimeSelect==0&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(1,1,"  ");
	}
	else
	{
		LCD_ShowNum(1,1,DS1302_Time[0],2);//年
	}
	  
	if(TimeSelect==1&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(1,4,"  ");
	}
	else
	{
		LCD_ShowNum(1,4,DS1302_Time[1],2);//月
	}
	if(TimeSelect==2&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(1,7,"  ");
	}
	else
	{
		LCD_ShowNum(1,7,DS1302_Time[2],2);//日
	}
	if(TimeSelect==3&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(2,1,"  ");
	}
	else
	{
		LCD_ShowNum(2,1,DS1302_Time[3],2);//时
	}
	if(TimeSelect==4&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(2,4,"  ");
	}
	else
	{
		LCD_ShowNum(2,4,DS1302_Time[4],2);//分
	}
	if(TimeSelect==5&&TimeSetFlashFlag==1)
	{
		LCD_ShowString(2,7,"  ");
	}
	else
	{
		LCD_ShowNum(2,7,DS1302_Time[5],2);//秒
	}
	
	 
		
		LCD_ShowNum(1,11,DS1302_Time[6],1);//星期
	
	 // LCD_ShowNum(2,10,TimeSelect,2);//对调时位置进行选择
	 // LCD_ShowNum(2,15,TimeSetFlashFlag,2);
}




void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();//定时器初始化
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();
	
	
	while(1)
  {
		KeyNum=Key();
		if(KeyNum==1)
		{
			if(MODE==0){MODE=1;TimeSelect=0;}
			else if(MODE==1){MODE=0;DS1302_SetTime();}
		}
		switch(MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
		}
	
  }
}


void Timer0_Routine() interrupt  1
{
	static unsigned int T0Count;
	TL0=0x18;
	TH0=0xFC;//设置定时初值
	T0Count++;
	if(T0Count<=1000)
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}