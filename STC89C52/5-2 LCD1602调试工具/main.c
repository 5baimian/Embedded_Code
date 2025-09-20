#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
void main()
{
	int Result=0;
	LCD_Init();	
//	LCD_ShowChar(1,1,'a');
//	
//	LCD_ShowString(1,3,"hello");
//	  
//	LCD_ShowNum(1,9,123,3);
//	  
//	LCD_ShowSignedNum(1,13,-66,2);
	LCD_ShowHexNum(2,1,0xA8,2);//显示十六进制
	LCD_ShowBinNum(2,4,0xAA,8);//显示二进制
	
	while(1)
	{
		Result++;
		Delay(1000);
		LCD_ShowNum(1,1,Result,3);
	}
}