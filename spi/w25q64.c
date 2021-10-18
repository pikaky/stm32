#include "stm32f10x.h"                  // Device header
#include "spi.h"   
#define dummy_byte 0xff   //随便弄一个 因为得发送才能接收

#define SPIx SPI1

#define addr_A  (GPIOA_BASE+0x0c)
#define PAout(bitnum)  *(unsigned int*)((addr_A&0xf0000000)+0x02000000+((addr_A&0x00ffffff)<<5)+(bitnum<<2)) 
                    


unsigned int w25q64_getid(void)
{
	unsigned int temp1,temp2,temp3,temp=0;
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	
	//发送读芯片id指令 芯片id返回有3个字节 用3次receivebyte接收
	
	spi_sendbyte(0x9f);
	
	temp1=spi_sendbyte(0x00);
	
	temp2=spi_sendbyte(0x01);
	
	temp3=spi_sendbyte(0x02);
	
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	//整合数据到一个int temp上
	temp=(temp1<<16)|(temp2<<8)|temp3;
	
	return temp;
}

void w25q64_write_enable(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	spi_sendbyte(0x06);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}



