#include "stm32f10x.h"                  // Device header
#include "overclocking.h"
#include "Delay.h"

int main(void)
{
	// 来到这里的时候；系统时钟已经配置到72m了
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//HSE_SysClock(RCC_PLLMul_16); //128mhz 
	
	while (1)
	{
	    GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);  
//		
		Delay_ms(500);
//		
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
//		
		Delay_ms(500);
	}
}
