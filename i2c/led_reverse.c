#include "stm32f10x.h"// Device header
#include "Delay.h" 
// 位带操作 对gpiob 输出寄存器的 第5位实行位操作
#define addr_A  (GPIOA_BASE+0x0c)
#define PAout(bitnum)  *(unsigned int*)((addr_A&0xf0000000)+0x02000000+((addr_A&0x00ffffff)<<5)+(bitnum<<2)) 
                    //指针转换 然后再解应用

void led_reverse(void)
	


{	
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
Delay_s(1);	
PAout(5)=~PAout(5);	  

}

