#include "stm32f10x.h"                  // Device header


#define buffer_size 32 // 定义发送数据大小


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

	
void i2c_init ()
{
	
	//配置i2c 初始化结构体
	I2C_InitTypeDef I2C_InitStruct;
	
	I2C_InitStruct.I2C_ClockSpeed = 400; //时钟频率
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C; //就用这个模式
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2; //快速模式 采用占空比2
	I2C_InitStruct.I2C_OwnAddress1 =(uint32_t)asrc_coanst_buffer; //主机地址
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable; //打开应答
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; //7位地址长度
	
	I2C_Init(I2C1, &I2C_InitStruct); //调用初始化函数
	
	
	
	
	
	
}