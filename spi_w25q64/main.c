#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led_reverse.h"
#include "spi.h"
#include "w25q64.h"
#include "usart.h"

#define sectorerass_addr 0x000000 //在0扇区调试
#define writenumber 256
#define readnumber 256
#define writeaddr 0x000000


int main(void)
{

	led_reverse();
	usart1_init();
	spi_init();
	
	int id_data=w25q64_getid();
	usart_send4byte(USART1,id_data);
	
	Delay_us(200);
	
	int i=w25q64_deviceid();
	usart_send4byte(USART1,i);
	
	unsigned char arr1[256]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,4,5,67,8,9,0,8,8};
	
	unsigned char arr2[256]={3};
	
	unsigned char arr3[256]={3};
	
	Delay_us(200);
	w25q64_sectorerass(sectorerass_addr);
	
	Delay_us(200);
	w25q64_pagewrite(arr1,writeaddr,writenumber);
	
	Delay_us(200);
	w25q64_read(arr2,writeaddr,readnumber);
	
	Delay_us(200);
	usart_sendarr(USART1,arr2,64);
	
	
	
	Delay_us(200);
	w25q64_sectorerass(sectorerass_addr);
	
	Delay_us(200);
	quickWrite(arr1, writeaddr, 256);
	
	Delay_us(200);
	w25q64_read(arr3,writeaddr,readnumber);
	
	Delay_us(200);
	usart_sendarr(USART1,arr3,64);
	
	Delay_us(200);
	w25q64_sectorerass(sectorerass_addr);
	
	while (1)
	{
		led_reverse();
	}
	
}
