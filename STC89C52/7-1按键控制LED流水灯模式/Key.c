#include <REGX52.H>
#include "Delay.h"

/**
  * @brief  获取独立按键键码
  * @param 无
  * @retval 按下按键的键码，范围：0~4，无按键按下时返回值为0
  */
unsigned int Key()
{
	unsigned int Keynumber=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);Keynumber=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);Keynumber=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);Keynumber=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);Keynumber=4;}
	return Keynumber;
	
}
