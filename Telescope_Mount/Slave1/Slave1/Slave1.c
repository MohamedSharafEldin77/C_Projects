//*


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "ADC.h"
#include "LCD.h"
#include "DIO.h"
#include "LED.h"
#include "Communication_Protocol.h"
#include "STD_BIT_MACRO.h"
#include "TIMER.h"

#define check_mode 0xAA
unsigned char check_mode_var=0,x=0;


int main(void)
{
    LCD_INIT();
	ADC_INIT();
	SPI_SLAVE_INIT();
	sei();
	char i;
	int temp,volt_mV;
	LCD_send_cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_send_string("TEMP:");
	DIO_set_PIN_dir('d',7,1);
	DIO_output_PIN_on_port('d',7,0);
	LED_INIT('a',2);
	LED_INIT('a',3);
	LED_INIT('a',4);
	
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
		if (temp>=50&temp<60)
		{
			LED_ON('a',2);
			LED_OFF('a',4);
		}
		else if (temp>=60)
		{
			LED_ON('a',2);
			LED_ON('a',3);
			DIO_output_PIN_on_port('d',7,1);
		}
		else
		{
			LED_OFF('a',2);
			LED_ON('a',4);
		}
		if (x==check_mode)
		{
			LED_ON('a',2);
			LED_ON('a',3);
			LED_ON('a',4);
			LCD_MOVE_CURSOR(1,1);
			for (i=0;i<=15;i++)
			{
				LCD_send_char(0xff);
			}
			LCD_MOVE_CURSOR(2,1);
			for (i=0;i<=15;i++)
			{
				LCD_send_char(0xff);
			}
			_delay_ms(10000);
			LED_OFF('a',2);
			LED_OFF('a',3);
			LED_OFF('a',4);
			LCD_CLEAR_Screen();
			LCD_send_string("TEMP:");
			x=0;
		}
		
		/*this code to get the positive degrees of temperature
		/*print_val(temp);
		LCD_send_char(0xDf); //degree sign
		LCD_send_char('C'); // C sign
		LCD_MOVE_CURSOR(1,6);*/
    }
}
ISR(SPI_STC_vect)
{
	x=SPI_SLAVE_recieve_char(1);
}
