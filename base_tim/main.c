#include "stm32f10x.h"   
#include "tim.h"  

volatile uint32_t time = 0; 

#define addr_B  (GPIOB_BASE+0x0c)
#define PBout(bitnum)  *(unsigned int*)((addr_B&0xf0000000)+0x02000000+((addr_B&0x00ffffff)<<5)+(bitnum<<2)) 


int main(void)
{
	/* led 端口配置 */
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	TIM_Init();
	
  while(1)
  {
    if ( time == 1000 ) /* 1000 * 1 ms = 1s 时间到 */
    {
        time = 0;   
		PBout(5)=~PBout(5); 
    }        
  }
}


