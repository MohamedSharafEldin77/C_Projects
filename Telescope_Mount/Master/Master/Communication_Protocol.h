/*
 * Communication_Protocol.h
 *
 * Created: 22-Aug-23 9:20:13 PM
 *  Author: MT
 */ 


#ifndef COMMUNICATION_PROTOCOL_H_
#define COMMUNICATION_PROTOCOL_H_

void UART_INIT (unsigned long baud);
void UART_send_data (char data);
char UART_receive_data (void);
void UART_send_string (char *ptr);


void SPI_MASTER_INIT (void);
void SPI_SLAVE_INIT (void);
unsigned char SPI_MASTER_Transmit_char (unsigned char data,unsigned char slave_SS);
unsigned char SPI_SLAVE_recieve_char (unsigned char data);
unsigned char SPI_MASTER_Transmit_string (unsigned char *ptr,unsigned char slave_SS);


#endif /* COMMUNICATION_PROTOCOL_H_ */