/*
 * TIMER.h
 *
 * Created: 14-Aug-23 10:51:56 PM
 *  Author: MT
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "DIO.h"

void timer2_INIT_OVERFLOW_Interrupt (void);
void timer1_INIT_WAVE_Fast_PMW_A (double value);
void timer1_INIT_WAVE_Fast_PMW_B (double value);

#endif /* TIMER_H_ */