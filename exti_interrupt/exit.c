#include "stm32f10x.h"                  // Device header

void exit_nvic_init(void)  //初始化exit 下的nvic
{
	NVIC_InitTypeDef NVIC_InitStruct; //命名结构体
	
	//优先级分组  例子中选择主1 子3 分组1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	// 配置nvic初始化结构体
	// 中断源的值在stm32f10x.h 里找   大容量用hd下面的 
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; //采用exti0
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //主优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //子优先级1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	
	NVIC_Init(&NVIC_InitStruct); //调用初始化函数
	
}



void exit_key_init()
{
	EXTI_InitTypeDef EXTI_InitStruct;   //命名结构体
	GPIO_InitTypeDef GPIO_InitStructure;  //命名结构体
	
	exit_nvic_init(); //在nvic里配置优先级
	
	//先配置PA0口 按键输入 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
// 下面开始配置exit中断	 例子中使用PA0口 接一个按键
	
	//打开exit上的时钟  具体总线看手册 2.1 系统总图
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// 配置中断线 在afio寄存器里 手册8.4.3
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);	
	
	// 配置exti初始化结构体   
	EXTI_InitStruct.EXTI_Line = EXTI_Line0; //用线0
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;  //使能
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; //选择中断模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; //选择上升沿触发	
    
	// 调用初始化函数 会自动配置寄存器
    EXTI_Init(&EXTI_InitStruct);
	
}
