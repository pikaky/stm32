#include "stm32f10x.h"                   // Device header

void HSE_SysClock(uint32_t RCC_PLLMul_x) 
{
	ErrorStatus HSEStatus; //设定好的变量
	
	RCC_DeInit();  //重写时钟 记得复位
	
	
	RCC_HSEConfig(RCC_HSE_ON); //使能hse
	
	HSEStatus=RCC_WaitForHSEStartUp(); //接受返回
	
	if (HSEStatus==SUCCESS)
	{
		// 开启flash预取址
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
    FLASH_SetLatency(FLASH_Latency_2);	//开启2个等待
		
	}
	else
	{
		//失败再说
	}
 RCC_HCLKConfig(RCC_SYSCLK_Div1);  //1分频 配置hclk
 RCC_PCLK1Config(RCC_SYSCLK_Div2); //2分频 配置pclk1
 RCC_PCLK2Config(RCC_SYSCLK_Div1); //1分频 配置pclk2
	
	// 配置pll	 时钟来源 不分频的hse ，倍率因子9 8*9出72mhz
 RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
    // 配置pll使能
 RCC_PLLCmd(ENABLE);
	
while((RCC->CR & RCC_CR_PLLRDY) == 0) //判断PLLRDY标志位
   {
	   //如果没接到就会一直循环 等待pll稳定
   }

  //选择系统时钟来源
 RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);   
   
while(RCC_GetSYSCLKSource()!=0x08);
   {
	  //如果没接到就会一直循环 等待系统时钟稳定
   }
}


