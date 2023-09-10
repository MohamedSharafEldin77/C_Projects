/*
 * CFile1.c
 *
 * Created: 16-Jul-23 8:30:12 PM
 *  Author: MT
 */ 
#include "DIO.h"
void LED_INIT (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_set_PIN_dir(portname,pin_number_0_7,1);
}
void BUTTON_INIT (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_set_PIN_dir(portname,pin_number_0_7,0);
}
void BUTTON_INIT_enable_PULLUP (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_set_PIN_dir(portname,pin_number_0_7,0);
	DIO_enable_PULLUP(portname,pin_number_0_7,1);
}
void BUTTON_INIT_disable_PULLUP (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_set_PIN_dir(portname,pin_number_0_7,0);
	DIO_enable_PULLUP(portname,pin_number_0_7,0);
}

void LED_ON (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_output_PIN_on_port(portname,pin_number_0_7,1);
}
void LED_OFF (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_output_PIN_on_port(portname,pin_number_0_7,0);
}
void LED_TOGGLE (unsigned char portname,unsigned char pin_number_0_7)
{
	DIO_Toggle_PIN_on_port(portname,pin_number_0_7);
}
unsigned char READ_PIN_status (unsigned char portname,unsigned char pin_number_0_7)
{	
	return DIO_READ_PIN(portname,pin_number_0_7);
}	

