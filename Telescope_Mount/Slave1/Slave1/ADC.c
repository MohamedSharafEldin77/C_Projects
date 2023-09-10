/*
 * ADC.c
 *
 * Created: 08-Aug-23 3:02:12 PM
 *  Author: MT
 */ 
#include <avr/io.h>
#include "STD_BIT_MACRO.h"

void ADC_INIT (void)
{
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);//for 1 1 to get 2.56v internal
	SET_BIT(ADMUX,MUX4);//to get the (A0-A1)*1 [differential mode] remove it to get back page_215
	SET_BIT(ADCSRA,ADEN);
	//set the clock generated to the ADC
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
}
unsigned short ADC_read (void)
{
	unsigned short read_value;
	SET_BIT(ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADSC)==1);
	/*while(READ_BIT(ADCSRA,ADIF)==0);
	SET_BIT(ADCSRA,ADIF);//clear ADIF*/
	read_value=ADCL;
	read_value|=(ADCH<<8);
	return read_value;
}