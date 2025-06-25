#include "stm32f10x.h" 
void APP_HC_SR04_Init()
{
	//1.��ʼ��ʱ����Ԫ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=71;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	//2.��ʼ�����벶��
	//2.1��ʼ��IO���ţ�PA8,IPD��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//2.2��ʼ�����벶���ͨ��1
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	
	TIM_ICInit(TIM1,&TIM_ICInitStruct);
	
	
	//2.3��ʼ�����벶���ͨ��2
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_IndirectTI;
	
	TIM_ICInit(TIM1,&TIM_ICInitStruct);
	
}