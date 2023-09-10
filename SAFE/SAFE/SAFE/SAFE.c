/*
 * SAFE.c
 *
 * Created: 07-Aug-23 11:01:13 AM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>

#include "DIO.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "EEPROM.h"
#include "LED.h"

int main(void)
{
    LCD_INIT();
	Keypad_INIT('d',0,'d',4);
	LED_INIT('a',0);
	LED_INIT('a',1);
	
	char i=1,pressed=NOT_PRESSED,counter=0;
	int password=0,firstpassword=0;
	if (EEPROM_READ(0x00)==0xff)
	{
		LCD_send_string("Set Pass:");
		while (i<=4)
		{
			pressed=Keypad_READ('d',0,'d',4);
			if (pressed!=NOT_PRESSED)
			{
				LCD_send_char(pressed);
				EEPROM_WRITE(i,pressed);
				_delay_ms(300);
				LCD_send_cmd(SHIFT_CURSOR_POSITION_LEFT);
				LCD_send_char('*');
				firstpassword=scan_value(EEPROM_READ(i),firstpassword);
				i++;
			}
		}
		
		EEPROM_WRITE(0x00,0);
	}
	else
	{
		LCD_send_string("Welcome");
		_delay_ms(700);
	}
	LCD_CLEAR_Screen();
	LCD_send_string("Enter pass:");
	while(1)
    {
         LED_ON('a',1); 
		 
		 pressed=Keypad_READ('d',0,'d',4);
		 if (pressed!=NOT_PRESSED)
		 {
			 LCD_send_char(pressed);
			 _delay_ms(300);
			 LCD_send_cmd(SHIFT_CURSOR_POSITION_LEFT);
			 LCD_send_char('*');
			 password=scan_value(pressed,password);
			 counter++;
			 
		 } 
		 else if (counter==4)
		 {
			 LCD_CLEAR_Screen();
			 if (password==firstpassword)
			 {
				 LCD_send_string("Opened");
				 LED_ON('a',0);
				 LED_OFF('a',1);
				 _delay_ms(5000);
				 LED_OFF('a',0);
			 } 
			 else
			 {
				 LCD_send_string("Wrong Password");
				 LED_TOGGLE('a',1);
				 _delay_ms(500);
				 LED_TOGGLE('a',1);
				 _delay_ms(500);
				 LED_TOGGLE('a',1);
				 _delay_ms(500);
				 LED_TOGGLE('a',1);
				 _delay_ms(5000);
				 
			 }
			 counter=0;
			 password=0;
			 pressed=NOT_PRESSED;
			 LCD_CLEAR_Screen();
			 LCD_send_string("Enter pass:");
		 }       
    }
}