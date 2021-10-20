#include "stm32f10x.h"                  // Device header
#include "diskio.h"		/* FatFs lower layer API */
#include "spi.h"		/* FatFs lower layer API */
#include "w25q64.h"
#include "Delay.h"

/* Definitions of physical drive number for each drive */
#define flash	1	/* Example: Map ATA harddisk to physical drive 0 */

#define w25q64_id 0xef4017	


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status = STA_NOINIT;
	
	unsigned int data;
	
	switch (pdrv) {
		
	case flash :
		
	data=w25q64_getid();
		if(data==w25q64_id)
		{
			//读取成功
			status&=~STA_NOINIT;  //0x01 返回个0也行 和noinit不一样就行
			
		}
		else
		{
			//状态不正常
			status = STA_NOINIT;
		}
	break;
		
	}
	return status;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status=STA_NOINIT;

	switch (pdrv) {
	case flash :
		
		spi_init();
	
		Delay_us(10);
	
		w25q64_wakeup();    //从powerdown模式下唤醒
	
		status=disk_status(flash);  //返回flash芯片状态
		break;
}
	
return status;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*----------DRESULT枚举变量 返回数值解析看头文件-------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	unsigned char readarr;
	
	switch (pdrv) {
	case flash :
		
	sector=sector+512; 
	readarr=sector<<12; //左移12位就是*4096 一个扇区4096个字节
	count=count<<12;
	
	w25q64_read(buff,readarr,count);
	
	res=RES_OK; //默认返回ok 写的没毛病
	
	return res;
	
}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
	
{
	DRESULT res;

	unsigned int sectorerass_addr;
	switch (pdrv) {
	case flash :
	
	sector=sector+512; //扇区偏移2mb 前面的2mb空一下 只用后面的6mb
	sectorerass_addr=sector<<12;
	
	w25q64_sectorerass(sectorerass_addr);
	
	quickWrite(((u8 *)buff),sectorerass_addr,count<<12);
	
	res=RES_OK; //默认返回ok 写的没毛病
	
	return res;
	
}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions  格式化函数                                       */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */ //控制命令
	void *buff		/* Buffer to send/receive control data 发送 接受命令后返回数据的指针 */ 
)
{
	DRESULT res;


	switch (pdrv) {
	case flash :
	
	switch(cmd) //控制命令在ffconf.h
	{
	//扇区 1536*4096byte  /1024/1024 = 6mb
	
		case GET_SECTOR_COUNT:  //返回扇区个数	
		*(DWORD*)buff=1536;
		
		break;
		
		case GET_SECTOR_SIZE:  //扇区大小
		*(DWORD*)buff=4096;
		break;
	
		case GET_BLOCK_SIZE:  //同时擦去扇区的个数
		*(DWORD*)buff=1;
		break;
	}
		
		res=RES_OK;
		
		return res;

}
	return RES_PARERR;
}
#endif

//时间戳获取
DWORD get_fattime(void)
{
	return 0;
}

