/*
 * DIO.h
 *
 * Created: 15-Jul-23 5:00:40 PM
 *  Author: MT
 */ 


#ifndef DIO_H_
#define DIO_H_
void DIO_set_PIN_dir (unsigned char portname,unsigned char pin_number_0_7,unsigned char direction);
void DIO_output_PIN_on_port (unsigned char portname,unsigned char pin_number_0_7,unsigned char output);
void DIO_Toggle_PIN_on_port (unsigned char portname,unsigned char pin_number_0_7);
unsigned char DIO_READ_PIN (unsigned char portname,unsigned char pin_number_0_7);

void DIO_set_PORT_dir (unsigned char portname,unsigned char portvalue);
void DIO_output_on_PORT (unsigned char portname,unsigned char output_on_port);
void DIO_Toggle_PORT (unsigned char portname);
unsigned char DIO_READ_PORT (unsigned char portname);

void DIO_enable_PULLUP (unsigned char portname,unsigned char pin_number_0_7,unsigned char enable_pullup);

#endif /* DIO_H_ */