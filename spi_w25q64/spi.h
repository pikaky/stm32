#ifndef __spi_H__
#define __spi_H__



#define SPIx SPI1
void spi_init(void);
unsigned char spi_sendbyte(unsigned char data);
unsigned char spi_receivebyte(void);


#endif
