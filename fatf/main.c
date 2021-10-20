#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led_reverse.h"
#include "ff.h"
#include "usart.h"
#include "stdio.h"

FATFS fp;        //文件信息结构体 里面塞得是文件系统的信息

int main(void)
{
	
	usart1_init();
	
	
	FRESULT res; //返回定义 里面有各种返回 通过判断返回 确认运行状况
	
	//挂载文件系统 初始化整个系统 ；路径为1 即选择flash；1为立即挂载
	res=f_mount(&fp,"1:",1);
	usart_sendbyte(USART1,res);
	
	res=f_mkfs("1:",0,0);
	usart_sendbyte(USART1,res);
	
	f_mount(NULL,"1:",1);
	res=f_mount(&fp,"1:",1);
	usart_sendbyte(USART1,res);
	
	
	
	while (1)
	{
	led_reverse();
	}
	
	
}
