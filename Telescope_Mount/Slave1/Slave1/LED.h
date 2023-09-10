/*
 * LED.h
 *
 * Created: 16-Jul-23 8:45:19 PM
 *  Author: MT
 */ 


#ifndef LED_H_
#define LED_H_

void LED_INIT (unsigned char portname,unsigned char pin_number_0_7);
void BUTTON_INIT (unsigned char portname,unsigned char pin_number_0_7);
void BUTTON_INIT_enable_PULLUP (unsigned char portname,unsigned char pin_number_0_7);
void BUTTON_INIT_disable_PULLUP (unsigned char portname,unsigned char pin_number_0_7);

void LED_ON (unsigned char portname,unsigned char pin_number_0_7);
void LED_OFF (unsigned char portname,unsigned char pin_number_0_7);
void LED_TOGGLE (unsigned char portname,unsigned char pin_number_0_7);

unsigned char READ_PIN_status (unsigned char portname,unsigned char pin_number_0_7);

#endif /* LED_H_ */