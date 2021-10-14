#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led_reverse.h"
#include "I2C.h"


int main(void)
{
    
	
	while (1)
	{
	led_reverse();
	}
}
