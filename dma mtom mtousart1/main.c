#include "stm32f10x.h"                  // Device header
#include "dma.h" 
#include "Delay.h"
#include "usart.h"
#include "led_reverse.h"

int main(void)
{
	int i =0;
	dma_mtom_init();
	usart1_init();
	
	extern unsigned int asrc_buffer[32];
	extern unsigned char send_buffer[tx_buffer_size];
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC6)==RESET); //判断发送完成标志 位于通道6 的 tc6
	DMA_ClearFlag(DMA1_FLAG_TC6); //清除发送完成标志
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//通过串口发送 sram上的数组
	usart_sendarr32(USART1,(unsigned int*)asrc_buffer,32);
	
	//填充一波数组sendarr
	ema_mtousart1tx_init();
	
	for(i=0;i<tx_buffer_size;i++)
	{
		send_buffer[i]='p';
	}
	
	//usart1 向 dma发送tx请求
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	
	//cpu是空闲的 可以干别的事情
	while (1)
	{
	led_reverse();
	}
}
