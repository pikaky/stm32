#include "stm32f10x.h"                  // Device header
#include "usart.h"
int main(void)
{
	usart1_init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	unsigned char arr1[10]={0};
	
	
	usart_sendarr(USART1,arr1,10);
	
	while (1)
	{
	
	}
}
