/*
 * Servo_Motor.c
 *
 * Created: 18-Aug-23 10:37:03 PM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "STD_BIT_MACRO.h"
#include "TIMER.h"
#include <avr/delay.h>

int main(void)
{
    while(1)
    {
        timer1_INIT_WAVE_Fast_PMW(15);
		_delay_ms(1000);
		
		timer1_INIT_WAVE_Fast_PMW(-12);
		_delay_ms(1000);
		
		timer1_INIT_WAVE_Fast_PMW(80);
		_delay_ms(1000);
		
		timer1_INIT_WAVE_Fast_PMW(-70);
		_delay_ms(1000);
    }
}