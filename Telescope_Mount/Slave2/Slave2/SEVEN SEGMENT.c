/*
 * SEVEN_SEGMENT.c
 *
 * Created: 18-Jul-23 8:09:12 PM
 *  Author: MT
 */ 

#include "STD_BIT_MACRO.h"
#include "DIO.h"

char SS[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void SEVEN_SEGMENT_INT (unsigned char portname)
{
	DIO_set_PORT_dir(portname,0xff);
}
void SEVEN_SEGMENT_write (unsigned char portname, unsigned char number,unsigned char Comm_Cathode_1_Comm_Anode_2)
{
	if (Comm_Cathode_1_Comm_Anode_2==1)
	{
		DIO_output_on_PORT(portname,SS[number]);
	}
	else
	{
		DIO_output_on_PORT(portname,~SS[number]);
	}
}
void SEVEN_SEGMENT_INT_BCD (unsigned char portname,unsigned char firstpin)
{
	unsigned char counter=0;
	for (counter;counter<=3;counter++)
	{
		DIO_set_PIN_dir(portname,firstpin,1);
		firstpin++;
	}
}
void SEVEN_SEGMENT_write_BCD (unsigned char portname,unsigned char firstpin,unsigned char number)
{
	unsigned char counter=0;
	for (counter=0;counter<=3;counter++)
	{
		DIO_output_PIN_on_port(portname,firstpin,READ_BIT(number,counter));
		firstpin++;
	}
}