/*
 * LCD.c
 *
 * Created: 26-Jul-23 7:35:53 PM
 *  Author: MT
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include "LCD.h"
#include "STD_BIT_MACRO.h"

// define the LCD 4 or 8 bits mode and the register and pin for EN,RN and LCD data pins.
//#define EIGHT_BITS_MODE
#define Four_BITS_MODE

//LCD data pins
#define RLCD_16 'a'
#define RLCD_16_firstpin 2 

//send the first 4 most pins to LCD before the least 4 pins

//RS pin
#define RS_Rg_selection 'a'
#define RS_Pn_selection 7

//EN pin
#define En_Rg_selection 'a'
#define En_Pn_selection 6

//choose between command and data for RS
#define command 0
#define data 1

void static enable_pulse (void)
{
	DIO_output_PIN_on_port(En_Rg_selection,En_Pn_selection,1);
	_delay_ms(2);
	DIO_output_PIN_on_port(En_Rg_selection,En_Pn_selection,0);
}


#if defined EIGHT_BITS_MODE
void LCD_send_char(unsigned char letter)
{
	DIO_output_on_PORT(RLCD_16,letter);
	DIO_output_PIN_on_port(RS_Rg_selection,RS_Pn_selection,data);
	enable_pulse();
	_delay_ms(1);
}
#elif defined Four_BITS_MODE
void LCD_send_char (unsigned char letter)
{
	unsigned char counter=0,x=3;//RLCD_16_firstpin;
	for (counter;counter<=7;counter++)
	{
		
		DIO_output_PIN_on_port(RLCD_16,RLCD_16_firstpin+x,READ_BIT(letter,7-counter));
		x--;
		if (counter==3||counter==7)
		{
			DIO_output_PIN_on_port(RS_Rg_selection,RS_Pn_selection,data);
			enable_pulse();
			x=3;
		}
	}
	_delay_ms(1);
}
#endif


#if defined EIGHT_BITS_MODE
void LCD_send_cmd (unsigned char cmd)
{
	DIO_output_on_PORT(RLCD_16,cmd);
	DIO_output_PIN_on_port(RS_Rg_selection,RS_Pn_selection,command);
	enable_pulse();
	_delay_ms(1);
}
#elif defined Four_BITS_MODE
void LCD_send_cmd (unsigned char letter)
{
	unsigned char counter=0,x=3;//;
	for (counter;counter<=7;counter++)
	{
		DIO_output_PIN_on_port(RLCD_16,RLCD_16_firstpin+x,READ_BIT(letter,7-counter));
		x--;
		if (counter==3||counter==7)
		{
			DIO_output_PIN_on_port(RS_Rg_selection,RS_Pn_selection,command);
			enable_pulse();
			x=3;
		}
	}
	_delay_ms(1);
}
#endif


void LCD_CLEAR_Screen (void)
{
	LCD_send_cmd(0x01);
	_delay_ms(10);
}


#if defined EIGHT_BITS_MODE
void LCD_INIT (void)
{
	_delay_ms(50);
	DIO_set_PORT_dir(RLCD_16,0x0f);
	DIO_set_PIN_dir(En_Rg_selection,En_Pn_selection,1);
	DIO_set_PIN_dir(RS_Rg_selection,RS_Pn_selection,1);
	LCD_send_cmd(0x38);
	LCD_send_cmd(DISPLAY_ON_CURSOR_ON);
	LCD_send_cmd(CLEAR_SCREEN);
	_delay_ms(5);
	LCD_send_cmd(ENTRY_MODE_RTL);
	
}
#elif defined Four_BITS_MODE
void LCD_INIT (void)
{
	_delay_ms(50);
	unsigned char counter=0;
	unsigned char x=RLCD_16_firstpin;
	for (counter;counter<=3;counter++)
	{
		DIO_set_PIN_dir(RLCD_16,x,1);
		x++;
	}
	DIO_set_PIN_dir(En_Rg_selection,En_Pn_selection,1);
	DIO_set_PIN_dir(RS_Rg_selection,RS_Pn_selection,1);
	LCD_send_cmd(RETURN_HOME);
	_delay_ms(5);
	LCD_send_cmd(0x28);
	LCD_send_cmd(DISPLAY_ON_CURSOR_ON);
	LCD_send_cmd(CLEAR_SCREEN);
	_delay_ms(5);
	LCD_send_cmd(ENTRY_MODE_RTL);
}
#endif

void LCD_MOVE_CURSOR (unsigned char row,unsigned char coloumn)
{
	if (row>2||row<1||coloumn>16||coloumn<1)
	{
		LCD_send_cmd(0x80);
	}
	else if (row==1)
	{
		LCD_send_cmd(0x80+coloumn-1);
	}
	else if (row==2)
	{
		LCD_send_cmd(0xc0+coloumn-1);
	}
}
void LCD_send_string (char*ptr)
{
	while (*ptr!=0)
	{
		LCD_send_char(*ptr);
		ptr++;
	}
}
int scan_value (unsigned char first_asci,int first_value)
{
	
	first_value*=10;
	first_value+=(first_asci-0x30);
	
	return first_value;
}
void print_val (int val)
{
	int asci_val,counter=1,x=val;
	if (val==0)
	{
		LCD_send_char('0');
	}
	else if (val<10)
	{
		LCD_send_char(val+0x30);
	}
	else
	{
		while (x>=10)
		{
			x=x/10;
			counter*=10;
		}
		while (counter>=10)
		{
			asci_val=(val/counter)%10;
			LCD_send_char(asci_val+0x30);
			counter/=10;
		}
		LCD_send_char((val%10)+0x30);
	}
}
