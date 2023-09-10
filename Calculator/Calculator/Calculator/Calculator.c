/*
 * Calculator.c
 *
 * Created: 05-Aug-23 2:33:43 PM
 *  Author: MT
 */ 

#include "Calculator.h"
#include "LCD.h"


unsigned long calculating (int x,int y, char operation)
{
	long calculated;
	if (operation=='+')
	{
		calculated = x+y;
	} 
	else if (operation=='-')
	{
		calculated = x-y;
	} 
	else if (operation=='*')
	{
		calculated = x*y;
	} 
	else if (operation=='/')
	{
		calculated = x/y;
	}
	else
	{
		calculated = NO_OPERATION;
	}
	return calculated;
}



/*int asci_val;
	volatile int y=10;
	volatile char x=1;
	while (val>0)
	{
		while (asci_val!=val)
		{
			asci_val=val%y;
			//x++;
			y=y*10;
		}
		asci_val=asci_val*10/y;
		LCD_send_char(asci_val+0x30);
		
		val=val-(asci_val*y/10);
		//x=1;
		y=10;
	}*/
/*else
	{
		while (x>0)
		{
			x=x/10;
			counter++;
		}
	}
		
	if (counter==1)
	{
		LCD_send_char(val+0x30);
	}
	else
	{
		for (counter;counter>1;counter--)
		{
			y=counter;
			asci_val=val;
			for (y;y>1;y--)
			{
				asci_val=(asci_val/10);
			}
			//LCD_send_char('a');
			LCD_send_char((asci_val)+48);
		}
		//LCD_send_char('b');
		LCD_send_char((val%10)+48);
	}*/
/*while (val != 0) {
		remainder = val % 10;
		reverse = reverse * 10 + remainder;
		val /= 10;
	}
	while(val>0)
	{
		//dig = val;
		//LCD_send_char((dig/10)+0x30);
		//LCD_send_char((dig%10)+0x30);
		
		dig = val%10;
		LCD_send_char((dig)+0x30);
		val = val/10;
	}*/