#include "stm32f10x.h"                  // Device header

#define ADCx ADC1 
#define RCC_APB2Periph_ADCx RCC_APB2Periph_ADC1
#define ADC_Channel_x ADC_Channel_11

__IO uint16_t ADC_ConvertedValue;

void adc_Init()
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADCx, ENABLE); //时钟
	ADC_InitTypeDef ADC_InitStruct;
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式 只使用一个adc
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//不开启扫描(一个adc不需要)
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续读取
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不开启硬件中断
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//12位数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;//一个通道 pc1
	
	ADC_Init(ADCx, &ADC_InitStruct);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); //adc时钟8分频 9mhz
	
	//adc通道配置 选择adc1 adc通道口 转换顺序（第一个采样） 采样周期 55机器周期
	ADC_RegularChannelConfig(ADCx,ADC_Channel_x,1,ADC_SampleTime_55Cycles5);
	
	
	ADC_ITConfig(ADCx,ADC_IT_EOC,ENABLE);//在规则通道转换结束后产生中断 在中断程序读取值
	
	ADC_Cmd(ADCx, ENABLE);
	
	ADC_ResetCalibration(ADCx);//初始化adc校准寄存器

	while(ADC_GetResetCalibrationStatus(ADCx));//读取标志位 等待完成
	
	ADC_StartCalibration(ADCx);//开始校准adc
	
	while(ADC_GetCalibrationStatus(ADCx));//
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);// 开启软件中断
	
}

void nvic_adc()
{
	//优先级配置
	NVIC_InitTypeDef NVIC_Initstructure ;
	
	NVIC_Initstructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_Initstructure);
	
}

void gpio_adc()
{
	
		//gpio配置 使用pc1 模拟输入
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
}

void adc_init()
{
	nvic_adc();
	gpio_adc();
	adc_Init();
}
