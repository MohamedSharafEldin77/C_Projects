/*
 * REAL_TIME_CLOCK.c
 *
 * Created: 14-Aug-23 10:11:59 PM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "DIO.h"
#include "STD_BIT_MACRO.h"
#include "SEVEN SEGMENT.h"
#include "KEYPAD.h"
#include "TIMER.h"
volatile char second=0;

int main(void)
{
	timer2_INIT_OVERFLOW_Interrupt();
	Keypad_INIT('d',0,'d',4);
	unsigned char minute=0,hours=0,pressed=NOT_PRESSED,first_digit,second_digit,i=0,c=0;
	
	SEVEN_SEGMENT_INT('a');
	DIO_set_PIN_dir('c',0,1);
	DIO_set_PIN_dir('c',1,1);
	DIO_set_PIN_dir('c',2,1);
	DIO_set_PIN_dir('c',3,1);
	DIO_set_PIN_dir('c',4,1);
	DIO_set_PIN_dir('c',5,1);
	
    while(1)
    {
		
		
		SEVEN_SEGMENT_write('a',second%10,1);
		DIO_output_PIN_on_port('c',5,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',5,1);
		
		SEVEN_SEGMENT_write('a',second/10,1);
		DIO_output_PIN_on_port('c',4,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',4,1);
		
		SEVEN_SEGMENT_write('a',minute%10,1);
		DIO_output_PIN_on_port('c',3,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',3,1);
		
		SEVEN_SEGMENT_write('a',minute/10,1);
		DIO_output_PIN_on_port('c',2,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',2,1);
		
		SEVEN_SEGMENT_write('a',hours%10,1);
		DIO_output_PIN_on_port('c',1,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',1,1);
		
		SEVEN_SEGMENT_write('a',hours/10,1);
		DIO_output_PIN_on_port('c',0,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('c',0,1);
		
		if (second>=60)
        {
			second=0;
			minute++;
        } 
        else if (minute>=60)
        {
			minute=0;
			hours++;
        } 
        else if (hours>=24)
        {
			hours=0;
        }
		
		pressed=Keypad_READ('d',0,'d',4);
		
		if (pressed!=NOT_PRESSED)
		{
			if (pressed==KEYPAD_RESET_SCREEN)
			{
				/*_delay_ms(5000);
				pressed=Keypad_READ('d',0,'d',5);
				if (pressed==ke)
				{
				}*/
				i++;
				c=1;
			}				
		}
		if (i==1)
		{
			if (c==1)
			{
				second=0;
				second=pressed-48;
				c=2;
			} 
			else if (c==2)
			{
				second=second*10+(pressed-48);
				//c=0;
			}
		}
		else if (i==2)
		{
			if (c==1)
			{
				minute=0;
				minute=pressed;
				c=2;
			}
			else if (c==2)
			{
				minute=minute*10+pressed;
				//c=0;
			}
		}
		else if (i==3)
		{
			if (c==1)
			{
				hours=0;
				hours=pressed;
				c=2;
			}
			else if (c==2)
			{
				hours=hours*10+pressed;
				//c=0;
			}
			i=0;
		}
    }
}
ISR(TIMER2_OVF_vect)
{
	second++;
}