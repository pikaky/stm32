#include "stm32f10x.h"                  // Device header
#include "spi.h"   
#include "w25q64.h"  
#define dummy_byte 0xff   //随便弄一个 因为得发送才能接收

#define SPIx SPI1

#define addr_C  (GPIOC_BASE+0x0c)
#define PCout(bitnum)  *(unsigned int*)((addr_C&0xf0000000)+0x02000000+((addr_C&0x00ffffff)<<5)+(bitnum<<2)) 
                    


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

unsigned int w25q64_deviceid(void)
{
  unsigned int temp=0;
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	
	//发送读芯片id指令 只有最后一个有用
	
	spi_sendbyte(0xab);
	
	spi_sendbyte(0x00);
	
	spi_sendbyte(0x00);
	
	spi_sendbyte(0x00);     
	
	temp=spi_sendbyte(0x00);
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	

	
	return temp;
}

void w25q64_waitforwrite()
{
	//通过读取状态寄存器的busy位判断发完上面的代码没
	
	unsigned char flag;
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	spi_sendbyte(0x05);
	
	while(1)
	{
		flag=spi_sendbyte(0x00); //随便弄的
		
		if((flag&0x01)==0) //读busy位 详情寄存器看w25q64手册
		{
			break;
		}
		
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}

void w25q64_sectorerass(unsigned char sectorerass_addr)
{
	//擦除扇区
	w25q64_write_enable(); //先发送写使能
	
	w25q64_waitforwrite(); //等等
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	spi_sendbyte(W25X_SectorErase);    //地址24位 一共要发3次 分开发
	
	spi_sendbyte((sectorerass_addr&0xff0000)>>16); 
	spi_sendbyte((sectorerass_addr&0xff00)>>8); 
	spi_sendbyte((sectorerass_addr&0xff)>>0); 
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	w25q64_waitforwrite();
	
}

//页写入
void w25q64_pagewrite(unsigned char *data,unsigned int writeaddr,unsigned short writenumber)
{
	
	w25q64_write_enable(); //先发送写使能
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	spi_sendbyte(W25X_PageProgram);
	//分3次发送地址
	spi_sendbyte((writeaddr&0xff0000)>>16); 
	spi_sendbyte((writeaddr&0xff00)>>8); 
	spi_sendbyte((writeaddr&0xff)>>0); 
	
  while (writenumber--)
  {
    /* 发送当前要写入的字节数据 */
    spi_sendbyte(*data);
    /* 指向下一字节数据 */
    data++;
  }
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	w25q64_waitforwrite(); //等等
	
}

//不定量写入



//读数据 写个数组来存就行

void w25q64_read(unsigned char *data,unsigned int writeaddr,unsigned short readnumber)
{
	
	
	w25q64_write_enable(); //先发送写使能
	
	w25q64_waitforwrite(); //等等
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信
	
	spi_sendbyte(W25X_ReadData);
	//分3次发送地址
	
	spi_sendbyte((writeaddr&0xff0000)>>16); 
	
	spi_sendbyte((writeaddr&0xff00)>>8); 
	
	spi_sendbyte((writeaddr&0xff)>>0); 
	
	while (readnumber--) /* while there is data to be read */
  {
    /* 读取一个字节*/
    *data = spi_sendbyte(0x00);
    /* 指向下一个字节缓冲区 */
    data++;
  }
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	w25q64_waitforwrite(); //等等
	
}

void quickWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
	/*mod运算求余，若writeAddr是SPI_FLASH_PageSize整数倍，运算结果Addr值为0*/
  Addr = WriteAddr % 256;
	/*差count个数据值，刚好可以对齐到页地址*/
  count = 256 - Addr;
	/*计算出要写多少整数页*/
  NumOfPage =  NumByteToWrite / 256;
	/*mod运算求余，计算出剩余不满一页的字节数*/
  NumOfSingle = NumByteToWrite % 256;
	
	/* Addr=0,则WriteAddr 刚好按页对齐 aligned  */
  if (Addr == 0)
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
      w25q64_pagewrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    { 
			/*先把整数页都写了*/
      while (NumOfPage--)
      {
        w25q64_pagewrite(pBuffer, WriteAddr,256);
        WriteAddr +=  256;
        pBuffer += 256;
      }
			/*若有多余的不满一页的数据，把它写完*/
      w25q64_pagewrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	/* 若地址与 SPI_FLASH_PageSize 不对齐  */
  else 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0)
    {
			/*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;
				/*先写满当前页*/
        w25q64_pagewrite(pBuffer, WriteAddr, count);
				
        WriteAddr +=  count;
        pBuffer += count;
				/*再写剩余的数据*/
        w25q64_pagewrite(pBuffer, WriteAddr, temp);
      }
      else /*当前页剩余的count个位置能写完NumOfSingle个数据*/
      {
        w25q64_pagewrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*地址不对齐多出的count分开处理，不加入这个运算*/
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / 256;
      NumOfSingle = NumByteToWrite % 256;
			
			/* 先写完count个数据，为的是让下一次要写的地址对齐 */
      w25q64_pagewrite(pBuffer, WriteAddr, count);
			
			/* 接下来就重复地址对齐的情况 */
      WriteAddr +=  count;
      pBuffer += count;
			/*把整数页都写了*/
      while (NumOfPage--)
      {
        w25q64_pagewrite(pBuffer, WriteAddr, 256);
        WriteAddr +=  256;
        pBuffer += 256;
      }
			/*若有多余的不满一页的数据，把它写完*/
      if (NumOfSingle != 0)
      {
        w25q64_pagewrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}


//从powerdown模式下唤醒他
void w25q64_wakeup(void)   
{

	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信

	spi_sendbyte(W25X_ReleasePowerDown);

	GPIO_SetBits(GPIOC,GPIO_Pin_0); 
}   

void w25q64_powerdown(void)   
{

	GPIO_ResetBits(GPIOC,GPIO_Pin_0); //拉低nss引脚 开始通信

	spi_sendbyte(W25X_PowerDown);

	GPIO_SetBits(GPIOC,GPIO_Pin_0); 
}   

