#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint32_t blinkInterval=1000;//闪烁时间
void App_USART1_Init();
void App_OnBoardLED_Init(void);
void USART1_IRQHandler(void);



int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组
	
	App_OnBoardLED_Init();
	while(1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);//亮
		Delay_ms(blinkInterval);
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);//灭
		Delay_ms(blinkInterval);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{
		uint8_t dataRcvd=USART_ReceiveData(USART1);
	if(dataRcvd=='0')
	{blinkInterval=1000;}
  else if(dataRcvd=='1')
	{blinkInterval=500;}
	else if(dataRcvd=='2')
	{blinkInterval=100;}
	}
	
}

void App_USART1_Init()
{
	//初始化IO引脚
 	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//PA9  AF_PP
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//PA10 AF_IPU
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化USART1
	//开启USART1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//初始化USART1
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	
	//闭合总开关
	
	USART_Cmd(USART1,ENABLE);
	
	//配置中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//闭合RXNE,闭合触发中断的开关
	
	//配置NVIC模块
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级：0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//子优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
}

void App_OnBoardLED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//使能时钟
	
	//配置端口模式
	GPIO_InitTypeDef GPIO_InitStructure;//初始化引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);//熄灭13口的灯
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);//点亮13接口的灯
}