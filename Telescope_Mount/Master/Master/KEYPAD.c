/*
 * KEYPAD.c
 *
 * Created: 04-Aug-23 11:15:23 PM
 *  Author: MT
 */ 

#include "STD_BIT_MACRO.h"
#include "KEYPAD.h"


unsigned char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{KEYPAD_RESET_SCREEN,'0','=','+'}};

void Keypad_INIT (unsigned char output_portname,unsigned char output_firstpin,unsigned char input_portname,unsigned char input_firstpin)
{
	unsigned char counter=0;
	for (counter=0;counter<=3;counter++)
	{
		DIO_set_PIN_dir(output_portname,output_firstpin+counter,1);
		DIO_set_PIN_dir(input_portname,input_firstpin+counter,0);
		DIO_enable_PULLUP(input_portname,input_firstpin+counter,1);
		
		DIO_output_PIN_on_port(output_portname,output_firstpin+0,1);
		DIO_output_PIN_on_port(output_portname,output_firstpin+1,1);
		DIO_output_PIN_on_port(output_portname,output_firstpin+2,1);
		DIO_output_PIN_on_port(output_portname,output_firstpin+3,1);
	}
}
unsigned char Keypad_READ (unsigned char output_portname,unsigned char output_firstpin,unsigned char input_portname,unsigned char input_firstpin)
{
	
	unsigned char row=0,col=0,return_val=NOT_PRESSED;
	
	for (row=0;row<=3;row++)
	{
		
		DIO_output_PIN_on_port(output_portname,output_firstpin+row,0);
		
		for (col=0;col<=3;col++)
		{
			if (DIO_READ_PIN(input_portname,input_firstpin+col)==0)
			{
				while(DIO_READ_PIN(input_portname,input_firstpin+col)==0);
				return_val = arr[row][col];
				break;
			}
		}
		
		DIO_output_PIN_on_port(output_portname,output_firstpin+row,1);
		
		if (return_val!=0xff)
		{
			break;
		}
	}	
	return return_val;
}
/*unsigned char Keypad_READ (unsigned char output_portname,unsigned char output_firstpin,unsigned char input_portname,unsigned char input_firstpin)
{
unsigned char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
unsigned char row=0,col=0,x;
for (row=0;row<=3;row++)
{
	DIO_output_PIN_on_port(output_portname,output_firstpin+row,0);
	//DIO_READ_PIN(input_portname,input_firstpin);
	x=DIO_READ_PORT(input_portname);
	if (x<0x7f)
	{
		while (READ_BIT(x,col)==1)
		{
			col++;
		}
		return arr[row,col];
	}
	DIO_output_PIN_on_port(output_portname,output_firstpin+row,1);
	
}

return NOT_PRESSED;
}*/