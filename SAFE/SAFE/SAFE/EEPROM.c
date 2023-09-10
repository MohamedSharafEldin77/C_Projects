/*
 * EEPROM.c
 *
 * Created: 23-Jul-23 5:12:49 PM
 *  Author: MT
 */ 
#include <avr/io.h>
#include "STD_BIT_MACRO.h"

void EEPROM_WRITE (unsigned short address,unsigned char data)
{
	EEAR=address;
	EEDR=data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
	while(READ_BIT(EECR,EEWE)==1);
}
unsigned char EEPROM_READ (unsigned short address)
{
	EEAR=address;
	SET_BIT(EECR,EERE);
	return EEDR;
}