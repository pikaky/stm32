#include "stm32f10x.h"                  // Device header

// 位带操作 对gpiob 输出寄存器的 第5位实行位操作
#define addr_a  (GPIOB_BASE+0x0c)
#define PBout(bitnum)  *(unsigned int*)((addr_a&0xf0000000)+0x02000000+((addr_a&0x00ffffff)<<5)+(bitnum<<2)) 
                    //指针转换 然后再解应用

#define I2C_SDA PBout(7)
#define I2C_SCL PBout(6)

void i2c_init()
	
{
	//配置pB6 io口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //复用开漏输出 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//配置pB7 io口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; // 复用开漏输出 用于i2c
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void I2C_start(void)
{
	I2C_SDA=1;  //保证起始条件一致高电平
	I2C_SCL=1; 
	
	I2C_SDA=0;  //看原理图
	I2C_SCL=0; 
}

void I2C_stop(void)
{
	//I2C_SCL=0; 
	I2C_SDA=0;  //保证起始条件一致低电平
	
	I2C_SCL=1;  //看原理图
	I2C_SDA=1;  

}
/**
*@brief 发送一个字节
*@param byte
*@retval 
*/
void I2C_send(char byte)
{
	int i=0;
	//I2C_SCL=0; 默认0
	for(i=0;i<8;i++)
	{
	  I2C_SDA=byte&(0x80>>i);  //sda x xxxxxx & 1 0000000 =x 00000000 留下来第一位的数据 同理重复8次
	  I2C_SCL=1;  //拉高 读一位数
	  I2C_SCL=0;  //再拉低 读完
	}
}

unsigned char I2C_receivebyte(void)
{
	unsigned char byte=0x00; //初始化byte000000 在|时，遇到1 变成1，0还是0；实现sda高电平时变1；低电平时还是0；
	int i=0;
	I2C_SDA=1; //先释放总线
	
	I2C_SCL=1;
	
	//因为直接读取低电平不标准，所以利用if语句 读取高电平时，byte 0位变成1，低电平时候0位还是0；
	for(i=0;i<8;i++)
{
	if(I2C_SDA==1)
	{
		byte=byte|(0x80>>i);
	}
	I2C_SCL=0;
}
	
	return byte;
		
}

/**
*@brief 发送应答
*@param ackbit 应答位 0应答 1非应答
*@retval 
*/

void I2C_sendack(unsigned char ackbit) //发送应答
{
	
	I2C_SDA=ackbit; //看图
	I2C_SCL=1;
	I2C_SCL=0;
}

unsigned char I2C_receiveack(void)  //接收应答
{
	
	unsigned char ackbit;
	
	I2C_SDA=1; //先释放总线
	I2C_SCL=1;
	
	ackbit=I2C_SDA; //sda出0应答，反之无应答 
	
	I2C_SCL=0;
	
	
	return ackbit;
	
}
