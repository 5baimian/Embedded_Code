/**
* @brief  利用时钟芯片DS1302使用LCD1602显示时钟
  * @param 
  * @retval 
  */


#include <REGX52.h>
#include "LCD1602.h"
#include "DS1302.h"

unsigned char Second,Minute;
void main()
{
	LCD_Init();
	DS1302_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();
	
	
	while(1)
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
}