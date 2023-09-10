/*
 * KEYPAD.h
 *
 * Created: 04-Aug-23 11:15:38 PM
 *  Author: MT
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define NOT_PRESSED 0xff
#define KEYPAD_RESET_SCREEN 'C'

void Keypad_INIT (unsigned char output_portname,unsigned char output_firstpin,unsigned char input_portname,unsigned char input_firstpin);
unsigned char Keypad_READ (unsigned char output_portname,unsigned char output_firstpin,unsigned char input_portname,unsigned char input_firstpin);



#endif /* KEYPAD_H_ */