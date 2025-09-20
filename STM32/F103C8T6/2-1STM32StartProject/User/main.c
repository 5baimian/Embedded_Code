#include "stm32f10x.h"                  // Device header
int main()
{
	
//寄存器操作方式	
//	RCC->APB2ENR=0x00000010;
//	GPIOC->CRH=0x00300000;
//	GPIOC->ODR=0x00000000;
	
	//用库函数间接配置寄存器
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//配置端口模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);//熄灭13口的灯
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//点亮13接口的灯
	while(1)
	{
		
	}
}
