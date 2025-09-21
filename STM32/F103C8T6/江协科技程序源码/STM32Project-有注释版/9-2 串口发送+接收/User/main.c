#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;			//定义用于接收串口数据的变量
uint32_t blinkInterval=1000;//闪烁时间
void App_OnBoardLED_Init(void);

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "RxData:");
	//板载LED初始化
	App_OnBoardLED_Init();
	
	/*串口初始化*/
	Serial_Init();		//串口初始化
	  
	
	while (1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);//亮
		Delay_ms(blinkInterval);
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);//灭
		Delay_ms(blinkInterval);
		if (Serial_GetRxFlag() == 1)			//检查串口接收数据的标志位
		{
			RxData = Serial_GetRxData();		//获取串口接收的数据
			Serial_SendByte(RxData);			//串口将收到的数据回传回去，用于测试
			OLED_ShowHexNum(1, 8, RxData, 2);	//显示串口接收的数据
			
				if(RxData==0)
				{blinkInterval=800;}
				else if(RxData==1)
				{blinkInterval=200;}
				else if(RxData==2)
				{blinkInterval=50;}	
		}
		}
		
	
	
}

void App_OnBoardLED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//使能时钟
	
	//配置端口模式
	GPIO_InitTypeDef GPIO_InitStructure;//初始化引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);//熄灭13口的灯
	//GPIO_ResetBits(GPIOC,GPIO_Pin_13);//点亮13接口的灯
}