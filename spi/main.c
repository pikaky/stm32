#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led_reverse.h"
#include "spi.h"
#include "w25q64.h"
#include "usart.h"


int main(void)
{

	
	usart1_init();
	
	spi_init();
	
	int id_data=w25q64_getid();
    
	usart_send4byte(USART1,id_data);
	
	id_data=w25q64_getid();
	
	usart_send4byte(USART1,id_data);

	while (1)
	{
		led_reverse();
	}
	
}
