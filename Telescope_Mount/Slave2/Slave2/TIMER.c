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
void timer1_INIT_WAVE_Fast_PMW_A (double value)
{
	value=value*0.0055555555555556+1.5;
	SET_BIT(DDRD,5);//set bin d5 to be output bin
	SET_BIT(DDRD,4);
	CLEAR_BIT(TCCR1A,WGM10);//select fast PWM mode with ICR1 as top
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	OCR1A=value*1000;//load the OCR1A,ICR1 values
	OCR1B=value*1000;
	ICR1=19999;
	SET_BIT(TCCR1B,CS11);//no prescaling
	SET_BIT(TCCR1A,COM1A1);
}

void timer1_INIT_WAVE_Fast_PMW_B (double value)
{
	value=value*0.0055555555555556+1.5;
	SET_BIT(DDRD,4);//set bin d5 to be output bin
	CLEAR_BIT(TCCR1A,WGM10);//select fast PWM mode with ICR1 as top
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	OCR1B=value*1000;//load the OCR1A,ICR1 values
	ICR1=19999;
	SET_BIT(TCCR1B,CS11);//no prescaling
	SET_BIT(TCCR1A,COM1B1);
}