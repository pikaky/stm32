#ifndef __led_reverse_H__
#define __led_reverse_H__

#include "stm32f10x.h"// Device header
#include "Delay.h" 
// 位带操作 对gpiob 输出寄存器的 第5位实行位操作
#define addr_A  (GPIOA_BASE+0x0c)
#define PAout(bitnum)  *(unsigned int*)((addr_A&0xf0000000)+0x02000000+((addr_A&0x00ffffff)<<5)+(bitnum<<2)) 
                    //指针转换 然后再解应用

void led_reverse(void);

#endif
