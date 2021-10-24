#ifndef __usart_H__
#define __usart_H__



void usart1_init(void);
void usart_sendbyte(USART_TypeDef* USARTx,uint8_t Data);
void usart_sendarr(USART_TypeDef* USARTx,unsigned char *arr,unsigned char arrnumber);
void usart_sendstr(USART_TypeDef* USARTx,unsigned char *str);
	
unsigned char usart_recieve_data(USART_TypeDef* USARTx);

#endif

