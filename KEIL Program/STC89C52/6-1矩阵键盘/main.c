#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"


void main()
{
	unsigned char KeyNum;
  //unsigned char KeyNumber;
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey:");
	while(1)
	{
		KeyNum=MatrixKey();
		//LCD_ShowNum(2,1,KeyNum,2);
		if(KeyNum!=0)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}			
	}
}