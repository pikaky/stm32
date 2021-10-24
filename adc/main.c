#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led_reverse.h"
#include "adc.h"
#include "usart.h"


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

extern __IO uint16_t ADC_ConvertedValue;


float ADC_ConvertedValueLocal;        

int main(void)
{
	
	
	usart1_init();
	
	adc_init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	while (1)
	{
		ADC_ConvertedValueLocal= (float) ADC_ConvertedValue/4096*3.3;	//最小单位1\4096 平均到3.3v上
		
		printf("ad is : 0x%04x v \r\n",ADC_ConvertedValue); 
		//以十六进制形式输出，占宽4位右对齐，不足4位的前面用0补齐。
		//如i=100，则输出0064。
		
		printf("ad is : %f v \r\n",ADC_ConvertedValueLocal); //显示转换后的电压
		
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		
		Delay(0xffffee);
	
	}
}
