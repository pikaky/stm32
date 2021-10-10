#include "stm32f10x.h"                  // Device header

void usart1_init(void)
	
{
	//先配置pa9 io口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //选择复用模式 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置pa10 io口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //选择浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//打开usart1上的的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//配置USART_InitTypeDef 初始化结构体
	
	USART_InitTypeDef USART_InitStruct; // 定义结构体
	USART_InitStruct.USART_BaudRate = 115200; //定义波特率
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;  //定义有效位长度
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //选择一位的停止位
	USART_InitStruct.USART_Parity = USART_Parity_No; //这里采用无校验
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //发送模式 接收模式都打开
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStruct); //调用初始化函数

	//配置串口中断优先级 接收时开启中断 
	
	NVIC_InitTypeDef NVIC_InitStruct; //命名结构体
	//优先级分组  例子中选择主1 子3 分组1
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	// 配置nvic初始化结构体
	// 中断源的值在stm32f10x.h 里找   大容量用hd下面的 
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn; //采用USART1
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //主优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1; //子优先级1
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //使能
	
	NVIC_Init(&NVIC_InitStruct); //调用初始化函数
	
	// 配置串口中断     接收寄存器空时产生中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	// 使能串口
	USART_Cmd(USART1, ENABLE);
	
}

// 发送一个字节
void usart_sendbyte(USART_TypeDef* USARTx,uint8_t Data)
{
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET); //判断发送寄存器空 
}

// 发送2个字节
void usart_send2byte(USART_TypeDef* USARTx,uint16_t Data)
{
	unsigned char temph,templ; //定义一个高8位和低8位
	temph= (Data&0xff00)>>8;  //提取高8位并放到最左边 因为等等只会发送前面8个bit
	templ= Data&0xff; //提取低8位
	
	//先发送高8位 然后低8位
	USART_SendData(USARTx,temph);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);	//判断发送完毕

	//再发送低8位 然后低8位
	USART_SendData(USARTx,templ);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

// 发送数组                               数组指针            数组个数
void usart_sendarr(USART_TypeDef* USARTx,unsigned char *arr,unsigned char arrnumber)
{
	unsigned char i;
	for(i=0;i<arrnumber;i++)
	{
		USART_SendData(USARTx,arr[i]);
	}
	
	// 直接判断发送完成 标志位
	
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
	
}

// 发送字符串
void usart_sendstr(USART_TypeDef* USARTx,unsigned char *str)
{
	unsigned char i = 0;
	do
	{
	USART_SendData(USARTx,*(str+i));	
	i++;	
	}while(*(str+i)!='0');   //字符串以\0结束 用这个来判断
	
}



unsigned char usart_recieve_data(USART_TypeDef* USARTx)
{
	
while(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE)==RESET);
return USART_ReceiveData(USARTx);

}
