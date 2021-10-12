#include "stm32f10x.h"

//定时时间t=reload*（1/clk）
 //clk=72mhz时
 //reload= 72, t=1us
 //reload= 72000, t=1ms
 
//void systick_Delay_us(uint32_t us)  套用函数  
//	int i = 0;
//	SysTick_Config(72); //微秒用72   毫秒把72改成72000即可  
//
//	for (i = 0; i < us; i++) //等待计时器计数 
//	{
//		while (!(SysTick->CTRL & 0x00010000)); //通过按位与寻位 找到countflag位判断是否变成1了
//	}
//	SysTick->CTRL = 0x00000004; //关闭计时器 即00000000000000000000000000000100
//										//clksource位置1  enable位 tickint位 countflag位清0；                                   


/** 操作寄存器方法
  * @brief  微秒级延时      寄存器图在m3指南 表8.9
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值  
	
	SysTick->VAL = 0x00;					//清空当前计数值  
	
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器 即00000000000000000000000000000101 不打开tickint位（中断异常请求位）
	
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0   //通过按位与寻位 找到countflag位判断
	
	SysTick->CTRL = 0x00000004;				//关闭定时器   即00000000000000000000000000000100
	                                    //clksource位置1  enable位 tickint位 countflag位清0；       
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
