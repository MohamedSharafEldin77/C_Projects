/*
 * TIMER.c
 *
 * Created: 14-Aug-23 10:51:41 PM
 *  Author: MT
 */ 
#include "STD_BIT_MACRO.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void timer2_INIT_OVERFLOW_Interrupt (void)
{
	SET_BIT(ASSR,AS2);//choose the oscillation source [0 for internal / 1 for TOSC2]
	
	SET_BIT(TCCR2,CS20);//choose the prescaler factor from table
	SET_BIT(TCCR2,CS22);
	
	//enable interrupt
	sei();
	SET_BIT(TIMSK,TOIE2);//for overflow interrupt
}