#include "stm32f10x.h"                  // Device header
#define SPIx SPI1
#define dummy_byte 0xff   //随便弄一个 因为得发送才能接收


void spi_init(void)
{
	//mosi pa7
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//miso pa6 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	//clk pa5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	//nss pC0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master; //主机模式
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; //8位
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;  //模式3 
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; //偶数采样 见模式3
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft ; //控制nss
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //4分频 
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //用高位先行
	SPI_InitStruct.SPI_CRCPolynomial = 7; //随便搞个值 反正没用
	
	SPI_Init(SPIx, &SPI_InitStruct);
	SPI_Cmd(SPIx, ENABLE);
	
	
	
}

unsigned char spi_sendbyte(unsigned char data)
{
	//全双工 发送接收一起进行
	
	
	//判断发送寄存器空
	while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET) ;
			
	SPI_I2S_SendData(SPIx,data);
	
	//判断接受寄存器空
	while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE)==RESET) ;
	
	return SPI_I2S_ReceiveData(SPIx);

}

unsigned char spi_receivebyte(void)
{
	//随便弄一个dummy_byte 因为得发送才能接收
	return spi_sendbyte(dummy_byte);
	
}





