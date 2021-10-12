#ifndef __dma_H__
#define __dma_H__\


#define buffer_size 32 // 定义发送数据大小
#define tx_buffer_size 100 
#define DMA_Channel_mtom DMA1_Channel6  //定义 m to m 通道采用dma1 通道6
#define DMA_Channel_mtousart1tx DMA1_Channel4
#define DMA_Channel_mtousart1rx DMA1_Channel5

#define DMA_Channel_mtousart1tx DMA1_Channel4
#define DMA_Channel_mtousart1rx DMA1_Channel5
void dma_mtom_init(void);
void ema_mtousart1tx_init(void);
	
#endif

