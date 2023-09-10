/*
 * CFile1.c
 *
 * Created: 15-Jul-23 3:39:57 PM
 *  Author: MT
 */ 

#include <avr/io.h>
#include "STD_BIT_MACRO.h"

void DIO_set_PIN_dir (unsigned char portname,unsigned char pin_number_0_7,unsigned char direction)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		if (direction==1)
		{
			SET_BIT(DDRA,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(DDRA,pin_number_0_7);
		}
		break;
		//DDRA=dir==1?DDRA|(1<<pin):DDRA&~(1<<pin);
		case 'B':
		case 'b':
		if (direction==1)
		{
			SET_BIT(DDRB,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(DDRB,pin_number_0_7);
		}
		break;
		case 'C':
		case 'c':
		if (direction==1)
		{
			SET_BIT(DDRC,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(DDRC,pin_number_0_7);
		}
		break;
		case 'D':
		case 'd':
		if (direction==1)
		{
			SET_BIT(DDRD,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(DDRD,pin_number_0_7);
		}
		break;
		default:
		break;
	}
}
void DIO_output_PIN_on_port (unsigned char portname,unsigned char pin_number_0_7,unsigned char output)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		if (output==1)
		{
			SET_BIT(PORTA,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTA,pin_number_0_7);
		}
		break;
		case 'B':
		case 'b':
		if (output==1)
		{
			SET_BIT(PORTB,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTB,pin_number_0_7);
		}
		break;
		case 'C':
		case 'c':
		if (output==1)
		{
			SET_BIT(PORTC,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTC,pin_number_0_7);
		}
		break;
		case 'D':
		case 'd':
		if (output==1)
		{
			SET_BIT(PORTD,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTD,pin_number_0_7);
		}
		break;
		default:
		break;
	}
}
void DIO_Toggle_PIN_on_port (unsigned char portname,unsigned char pin_number_0_7)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		TOGGLE_BIT(PORTA,pin_number_0_7);
		break;
		case 'B':
		case 'b':
		TOGGLE_BIT(PORTB,pin_number_0_7);
		break;
		case 'C':
		case 'c':
		TOGGLE_BIT(PORTC,pin_number_0_7);
		break;
		case 'D':
		case 'd':
		TOGGLE_BIT(PORTD,pin_number_0_7);
		break;
		default:
		break;
	}
}
unsigned char DIO_READ_PIN (unsigned char portname,unsigned char pin_number_0_7)
{
	unsigned char val;
	switch (portname)
	{
		case 'A':
		case 'a':
		val=READ_BIT(PINA,pin_number_0_7);
		break;
		case 'B':
		case 'b':
		val=READ_BIT(PINB,pin_number_0_7);
		break;
		case 'C':
		case 'c':
		val=READ_BIT(PINC,pin_number_0_7);
		break;
		case 'D':
		case 'd':
		val=READ_BIT(PIND,pin_number_0_7);
		break;
		default:
		break;	
	}
	return val;
}
void DIO_set_PORT_dir (unsigned char portname,unsigned char portvalue)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		DDRA=portvalue;
		break;
		case 'B':
		case 'b':
		DDRB=portvalue;
		break;
		case 'C':
		case 'c':
		DDRC=portvalue;
		break;
		case 'D':
		case 'd':
		DDRD=portvalue;
		break;
		default:
		break;
	}
}
void DIO_output_on_PORT (unsigned char portname,unsigned char output_on_port)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		PORTA=output_on_port;
		break;
		case 'B':
		case 'b':
		PORTB=output_on_port;
		break;
		case 'C':
		case 'c':
		PORTC=output_on_port;
		break;
		case 'D':
		case 'd':
		PORTD=output_on_port;
		break;
		default:
		break;
	}
}
void DIO_Toggle_PORT (unsigned char portname)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		PORTA=~PORTA;
		break;
		case 'B':
		case 'b':
		PORTB=~PORTB;
		break;
		case 'C':
		case 'c':
		PORTC=~PORTC;
		break;
		case 'D':
		case 'd':
		PORTD=~PORTD;
		break;
		default:
		break;
	}
}
unsigned char DIO_READ_PORT (unsigned char portname)
{
	unsigned char returned_value;
	switch (portname)
	{
		case 'A':
		case 'a':
		returned_value=PORTA;
		break;
		case 'B':
		case 'b':
		returned_value=PORTB;
		break;
		case 'C':
		case 'c':
		returned_value=PORTC;
		break;
		case 'D':
		case 'd':
		returned_value=PORTD;
		break;
		default:
		break;
	}
}
void DIO_enable_PULLUP (unsigned char portname,unsigned char pin_number_0_7,unsigned char enable_pullup)
{
	switch (portname)
	{
		case 'A':
		case 'a':
		if (enable_pullup==1)
		{
			SET_BIT(PORTA,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTA,pin_number_0_7);
		}
		break;
		case 'B':
		case 'b':
		if (enable_pullup==1)
		{
			SET_BIT(PORTB,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTB,pin_number_0_7);
		}
		break;
		case 'C':
		case 'c':
		if (enable_pullup==1)
		{
			SET_BIT(PORTC,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTC,pin_number_0_7);
		}
		break;
		case 'D':
		case 'd':
		if (enable_pullup==1)
		{
			SET_BIT(PORTD,pin_number_0_7);
		}
		else
		{
			CLEAR_BIT(PORTD,pin_number_0_7);
		}
		break;
		default:
		break;
	}
}