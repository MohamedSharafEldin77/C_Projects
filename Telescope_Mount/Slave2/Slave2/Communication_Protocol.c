/*
 * Communication_Protocol.c
 *
 * Created: 22-Aug-23 9:20:23 PM
 *  Author: MT
 */ 
#include "STD_BIT_MACRO.h"
#define F_CPU 8000000UL
#include "avr/io.h"
#include "avr/delay.h"
#include "DIO.h"
//#define 


void UART_INIT (unsigned long baud)
{
	unsigned short UBRR;
	UBRR=(F_CPU/(16*baud))-1;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)(UBRR);//choosing the baud speed from the equation
	
	UCSRB|=(1<<RXEN)|(1<<TXEN);//enable the RX , TX in UCSRB
	
	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);//setting the 8-bit character size with URSEL to choose UCSRC
}
void UART_send_data (char data)
{
	while (READ_BIT(UCSRA,UDRE)==0);//waiting data register empty bit to be 1 so it is clear to write
	UDR=data;//writing
}
char UART_receive_data (void)
{
	while (READ_BIT(UCSRA,RXC)==0);
	return UDR;
}
void UART_send_string (char *ptr)
{
	while (*ptr!=0)
	{
		UART_send_data(*ptr);
		ptr++;
		_delay_ms(50);
	}
}
void SPI_MASTER_INIT (void)
{
	DIO_set_PIN_dir('b',4,1);//SS
	DIO_set_PIN_dir('b',5,1);//MOSI
	DIO_set_PIN_dir('b',6,0);//MISO
	DIO_set_PIN_dir('b',7,1);//SCK
	SET_BIT(SPCR,MSTR);//enable Master
	SET_BIT(SPCR,SPE);//set SPE to enable the SPI
	DIO_output_PIN_on_port('b',4,1);//SS to logic high (idle)
}
void SPI_SLAVE_INIT (void)
{
	SET_BIT(SPCR,SPE);//set SPE to enable the SPI
	SET_BIT(SPCR,SPIE);//set SPIE to enable the Interrupt
	DIO_set_PIN_dir('b',6,1);//Set MISO output
}
unsigned char SPI_MASTER_Transmit_char (unsigned char data,unsigned char slave_SS)
{
	DIO_output_PIN_on_port('b',slave_SS,0);
	SPDR=data;//put the data into SPDR to be transmitted
	while (READ_BIT(SPSR,SPIF)==0);//waiting till transmission is finished
	return SPDR;
}
unsigned char SPI_SLAVE_recieve_char (unsigned char data)
{
	SPDR=data;
	while(READ_BIT(SPSR,SPIF)==0);//waiting till transmission is finished
	return SPDR;
}
unsigned char SPI_MASTER_Transmit_string (unsigned char *ptr,unsigned char slave_SS)
{
	while ((*ptr)!=0)
	{
		SPI_MASTER_Transmit_char(*ptr,slave_SS);
		_delay_ms(300);
		ptr++;
	}
}