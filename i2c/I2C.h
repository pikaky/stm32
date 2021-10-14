#ifndef __I2C_H__
#define __I2C_H__


void I2C_start(void);
void I2C_stop(void);
void I2C_send(unsigned char byte);
unsigned char I2C_receivebyte(void);
void I2C_sendack(unsigned char byte);
unsigned char I2C_receiveack(void);




#endif
