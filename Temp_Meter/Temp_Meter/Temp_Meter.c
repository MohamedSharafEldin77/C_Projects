/*
 * Temp_Meter.c
 *
 * Created: 08-Aug-23 11:19:37 PM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include "ADC.h"
#include "LCD.h"

int main(void)
{
    LCD_INIT();
	ADC_INIT();
	char i;
	int temp,volt_mV;
	LCD_send_cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_send_string("TEMP:");
	while(1)
    {
		//temp=0.25*ADC_read();//(2.56[V]*read_value*1000[to get V in mv])/1024[level]*10[mV_10mV for every degree]
		volt_mV=ADC_read()*2.5;
		LCD_MOVE_CURSOR(1,6);
		if (volt_mV>=1000)
		{
			temp=(volt_mV-1000)/10;
			print_val(temp);
			LCD_send_char(0xDf); //degree sign
			LCD_send_char('C'); // C sign
			LCD_send_char(' ');
			LCD_send_char(' ');
		} 
		else
		{
			
			temp=(1000-volt_mV)/10;
			LCD_send_char('-');
			print_val(temp);
			LCD_send_char(0xDf); //degree sign
			LCD_send_char('C'); // C sign
			LCD_send_char(' ');
			
		}
		/*this code to get the positive degrees of temprature
		/*print_val(temp);
		LCD_send_char(0xDf); //degree sign
		LCD_send_char('C'); // C sign
		LCD_MOVE_CURSOR(1,6);*/
    }
}