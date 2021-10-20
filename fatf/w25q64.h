#ifndef __w25q64_H__
#define __w25q64_H__

#define dummy_byte 0xff  

#define SPIx SPI1

#define addr_C  (GPIOC_BASE+0x0c)
#define PCout(bitnum)  *(unsigned int*)((addr_C&0xf0000000)+0x02000000+((addr_C&0x00ffffff)<<5)+(bitnum<<2)) 
                    
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F

unsigned int w25q64_deviceid(void);
unsigned int w25q64_getid(void);
void w25q64_write_enable(void);
void w25q64_waitforwrite(void);
void w25q64_sectorerass(unsigned char sectorerass_addr);
void w25q64_pagewrite(unsigned char *data,unsigned int writeaddr,unsigned short writenumber);
void w25q64_read(unsigned char *data,unsigned int writeaddr,unsigned short readnumber);
void quickWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void w25q64_powerdown(void);
void w25q64_wakeup(void);


#endif

