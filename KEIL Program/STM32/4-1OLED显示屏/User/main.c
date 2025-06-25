#include "stm32f10x.h"                  // Device header
#include "OLED.h"
int main(void)
{
	OLED_Init();
	
	
	
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"hello world!");
	OLED_ShowNum(2,1,1234,4);
	OLED_ShowSignedNum(2,8,-1234,4);
	OLED_ShowHexNum(3,1,0xF0F0,4);
	//OLED_ShowBinNum(4,1,0101011011,10);//可以直接写二进制，也可以写十六进制
	OLED_ShowBinNum(4,1,0xF0F0,16);
	
	
	OLED_Clear();
	while(1)
	{
		
	}
}

