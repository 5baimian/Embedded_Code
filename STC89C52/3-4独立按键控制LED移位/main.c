#include <REGX52.H>
#include <INTRINS.H>
void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	while(xms--)
	{
		i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	}
	
}

void main()
{
	unsigned char LEDNum;
	P2=~0x01;//初始化，点亮第一个LED
	while(1)
	{
		if(P3_1==0)
		{
				Delay(20);
				while(P3_1==0);
				Delay(20);//消抖
				
				LEDNum++;
				if(LEDNum>7)
				{
					LEDNum=0;
				}
				P2=~(0x01<<LEDNum);//右移一位
		}
		if(P3_0==0)
		{
				Delay(20);
				while(P3_0==0);
				Delay(20);
				
				if(LEDNum==0)
				{
					LEDNum=7;
				}
				else
				LEDNum--;
				
				P2=~(0x01<<LEDNum);//左移一位
			
		}
	}
}