#include <REGX52.H>
#include<INTRINS.H>
void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();//空语句，引入头文件<INTRINS.H>
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	while(1)
	{ 
		 P2=0xFE;
			Delay500ms();
		 P2=0xFF;
			Delay500ms();
	}
}