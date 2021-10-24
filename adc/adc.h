#ifndef __adc_H__
#define __adc_H__

#include "stdio.h"
#define DEBUG_USARTx USART1

#define ADCx ADC1 
#define RCC_APB2Periph_ADCx RCC_APB2Periph_ADC1
#define ADC_Channel_x ADC_Channel_11

void adc_init(void);


#endif
