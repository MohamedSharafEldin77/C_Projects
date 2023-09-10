/*
 * GccApplication1.c
 *
 * Created: 14-Jul-23 2:09:48 AM
 *  Author: MT
 */ 


#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "KEYPAD.h"
#include "Calculator.h"

int main(void)
{
	LCD_INIT();
	Keypad_INIT('d',0,'d',4);
	unsigned char pressed;
	int xx=0,yy=0,result=0,operation=NO_OPERATION;
    while(1)
    {
		pressed=Keypad_READ('d',0,'d',4);
		if (pressed!=NOT_PRESSED)
		{
			LCD_send_char(pressed);
			if (pressed==KEYPAD_RESET_SCREEN)
			{
				LCD_send_cmd(CLEAR_SCREEN);
				xx=0,yy=0;result=0;operation=NO_OPERATION;
			}
			else if (pressed=='+'||pressed=='-'||pressed=='*'||pressed=='/')
			{
				operation=pressed;
			}
			else if (pressed=='=')
			{
				result=calculating(xx,yy,operation);
				print_val (result);
				operation=NO_OPERATION;
			}
			else
			{
				if (operation==NO_OPERATION)
				{
					xx=scan_value(pressed,xx);
				}
				else
				{
					yy=scan_value(pressed,yy);
				}
			}
		}
		
    }
}
