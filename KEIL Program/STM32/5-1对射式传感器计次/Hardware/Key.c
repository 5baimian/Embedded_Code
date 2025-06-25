#include "stm32f10x.h"                  // Device header
#include"Delay.h"
/**
  * @brief  初始化按键，配置按键各个接口
  * @param 无
  * @retval 无
  */
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/**
  * @brief  读取按键的值
  * @param 无
  * @retval 无
  */
uint8_t Key_GetNum(void)//uint--unsigned char类型名
{
	uint8_t KeyNum=0;
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==1)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0);
		Delay_ms(20);
		
		KeyNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0);
		Delay_ms(20);
		
		KeyNum=2;
	}
	return KeyNum;
}
