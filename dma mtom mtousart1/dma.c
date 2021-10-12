#include "stm32f10x.h"                  // Device header

#define buffer_size 32 // 定义发送数据大小
#define tx_buffer_size 100 
#define DMA_Channel_mtom DMA1_Channel6  //定义 m to m 通道采用dma1 通道6
#define DMA_Channel_mtousart1tx DMA1_Channel4
#define DMA_Channel_mtousart1rx DMA1_Channel5

//先定义一个常量数组 放在flash上 作为dma传输数据源
const unsigned int asrc_coanst_buffer[buffer_size]={
	0x01020304, 0x05060708, 0x090A0B0c, 0x0D0E0F10,
	0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
	0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
	0x31323334, 0x35363738, 0X393A3B3C, 0x3D3E3F40,
	0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
	0x51525354, 0x55565758, 0x595A5B5c, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
	0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};
	
//定义一个变量数组 存在在sram上	
unsigned int asrc_buffer[buffer_size]; 
	
unsigned char send_buffer[tx_buffer_size]; 
	
void dma_mtom_init(void)
	
{
	//打开dma1上的时钟  这是挂载在ahb系统总线上的
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct;//定义结构体
	
	//外设地址 为flash
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)asrc_coanst_buffer;
	
	//存储器地址 为sram
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)asrc_buffer;
	
	//传输方向 src：源  DMA_DIR_PeripheralDST:外设
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	//传输数据量
	DMA_InitStruct.DMA_BufferSize = buffer_size;
	
	//外设地址增量模式
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	//存储器地址增量模式
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	//外设数据宽度                            32bit
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	//存储器数据宽度                        32bit
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	//模式选择 普通模式 不循环
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	
	//通道优先级 选个低
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	
	//存储器到存储器模式使能
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
	
	//调用初始函数 采用通道6
	DMA_Init(DMA_Channel_mtom,&DMA_InitStruct);
	
	//使能 dma
	DMA_Cmd(DMA_Channel_mtom,ENABLE);
	
}

void ema_mtousart1tx_init(void)
{
	//打开dma1上的时钟  这是挂载在ahb系统总线上的
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct;//定义结构体
	
	//外设地址 为串口数据寄存器地址 即usart_DR 地址偏移0x04 
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(USART1_BASE+0X04);
	
	//存储器地址 为sram
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)send_buffer;
	
	//传输方向 src：源  DST:外设
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	
	//传输数据量
	DMA_InitStruct.DMA_BufferSize = tx_buffer_size;
	
	//外设地址增量模式 关闭 dr寄存器只有一个
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	
	//存储器地址增量模式
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	//外设数据宽度                            8bit
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	//存储器数据宽度                        8bit
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	
	//模式选择 普通模式 不循环
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	
	//通道优先级 选个高
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	//存储器到存储器模式使能 关闭
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	//调用初始函数 采用通道4
	DMA_Init(DMA_Channel_mtousart1tx,&DMA_InitStruct);
	
	//使能 dma
	DMA_Cmd(DMA_Channel_mtousart1tx,ENABLE);
	
	
}

