#include "stm32f10x.h"                  // Device header

#include "I2C.h"

#define at24c02_address 0xA0  //定义固件地址 设定好是这个 1010000 写

                       //发送地址               发送数据
 void at24c02_write(unsigned char wordaddress,unsigned char dat)
{
	unsigned char ack;
	
    I2C_start();
	I2C_send(at24c02_address);
	I2C_receiveack();
	ack=I2C_receiveack();
    while(ack==1); //eep还没应答
	I2C_send(wordaddress);
	ack=I2C_receiveack();
    while(ack==1); //eep还没应答
	I2C_send(dat);
	ack=I2C_receiveack();
	while(ack==0); //eep非应答
	I2C_stop(); //搞定
}

unsigned char at24c02_read (unsigned char wordaddress)
{
	unsigned char dat;
	
	return dat;
	
}