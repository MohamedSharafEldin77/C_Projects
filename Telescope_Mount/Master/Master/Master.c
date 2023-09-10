/*
 * Master.c
 *
 * Created: 23-Aug-23 7:43:38 PM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "STD_BIT_MACRO.h"
#include "LCD.h"
#include "Communication_Protocol.h"
#include "KEYPAD.h"
#include "TIMER.h"
#include "LED.h"
#include "DIO.h"

#define NO_OPERATION 0xFE
#define POINTING_MODE 0xDD
#define SLEWING_MODE 0xDE
#define TRACKING_MODE 0xDF
#define HOMING_MODE 0xDC
#define SET_TIME 0xEE
#define check_mode 0xAA

static void Call_slave1 (unsigned char data);
static void Call_slave2 (unsigned char data);
int main(void)
{
    DIO_set_PIN_dir('a',0,1);//set the INT0 in slave 1
	DIO_set_PIN_dir('b',0,1);//set the INT0 in slave 2
	DIO_output_PIN_on_port('a',0,0);//idle mode for INT0 slave 1
	DIO_output_PIN_on_port('b',0,0);//idle mode for INT0 slave 2
	LED_INIT('d',7);
	sei();
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(GICR,INT0);
	DIO_set_PIN_dir('d',2,0);//int0 source
	SPI_MASTER_INIT();
	_delay_ms(500);
	LCD_INIT();
	Keypad_INIT('c',0,'c',4);
	unsigned char pressed;
	int operation=NO_OPERATION;
	unsigned char i=0;
	unsigned char main_menu=1,degree_mode=0,settings_mode=0;
	unsigned char point_mode=0,slew_mode=0,track_mode=0,home_mode=0,set_time=0;
	unsigned char degree1[3]={0,0,0};
	unsigned char degree2[3]={0,0,0};
	unsigned char slew_time1[2]={0,0};
	unsigned char slew_time2[2]={0,0};
	unsigned char slew_seconds=0,slew_minutes=0;
	unsigned char time[6]={0,0,0,0,0,0};
	LCD_send_cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_send_string("    Welcome");
	_delay_ms(1000);
	LCD_CLEAR_Screen();
    while(1)
    {
		Call_slave1(1);
		if (main_menu==1)
		{
			LCD_CLEAR_Screen();
			LCD_send_string("Choose your mode");
			_delay_ms(1000);
			LCD_CLEAR_Screen();
			LCD_send_string("1-Movement");
			LCD_MOVE_CURSOR(2,1);
			LCD_send_string("2-Settings");
			do 
			{
				pressed=Keypad_READ('c',0,'c',4);
			} while (pressed==NOT_PRESSED);
			LCD_send_char(pressed);
			LCD_CLEAR_Screen();
			if (pressed=='1')
			{
				degree_mode=1;
				main_menu=0;
				LCD_send_string("Select Mode");
				_delay_ms(1000);
				LCD_CLEAR_Screen();
				//LCD_send_char(pressed);
				LCD_send_string("1-Point  2-slew");
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("3-track  4-home");
				do
				{
					pressed=Keypad_READ('c',0,'c',4);
				} while (pressed==NOT_PRESSED);
				if (pressed=='1')
				{
					point_mode=1,slew_mode=0,track_mode=0,home_mode=0;
				} 
				else if (pressed=='2')
				{
					point_mode=0,slew_mode=1,track_mode=0,home_mode=0;
				} 
				else if (pressed=='3')
				{
					point_mode=0,slew_mode=0,track_mode=1,home_mode=0;
				}
				else if (pressed=='4')
				{
					point_mode=0,slew_mode=0,track_mode=0,home_mode=1;
				} 
				else
				{
					LCD_CLEAR_Screen();
					LCD_send_string("Wrong Input");
					_delay_ms(2000);
					main_menu=1;
					point_mode=0,slew_mode=0,track_mode=0,home_mode=0;
					degree_mode=0;
					settings_mode=0;
				}
			} 
			else if (pressed=='2')
			{
				settings_mode=1;
				main_menu=0;
				LCD_CLEAR_Screen();
				LCD_send_string("1-Set Time");
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("2-Check Mode");
				do
				{
					pressed=Keypad_READ('c',0,'c',4);
				} while (pressed==NOT_PRESSED);
				LCD_CLEAR_Screen();
				if (pressed=='1')
				{
					LCD_send_string("Setting Time");
					_delay_ms(1000);
					set_time=1;
					main_menu=1;
				}
				else if (pressed=='2')
				{
					LCD_send_string("Checking Mode ON");
					_delay_ms(1000);
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
					i=0;
					Call_slave1(check_mode);
					_delay_ms(50);
					
					Call_slave2(check_mode);
					_delay_ms(50);
					Call_slave2(check_mode);
					for (i=0;i<=8;i++)
					{
						_delay_ms(20);
						Call_slave2(0);
					}
					Call_slave2(0xf0);
					LED_ON('d',7);
					_delay_ms(10000);
					LED_OFF('d',7);
					LCD_CLEAR_Screen();
					point_mode=0,slew_mode=0,track_mode=0,home_mode=0,set_time=0;
					main_menu=1;
				} 
				else
				{
					LCD_CLEAR_Screen();
					LCD_send_string("Wrong Input");
					_delay_ms(2000);
					set_time=0;
					settings_mode=0;
					main_menu=1;
				}
			}
			else
			{
				LCD_CLEAR_Screen();
				LCD_send_string("Wrong Input");
				_delay_ms(2000);
				main_menu=1;
				degree_mode=0;
				settings_mode=0;
			}
			pressed=NOT_PRESSED;
			LCD_CLEAR_Screen();
		}
		if (degree_mode==1)
		{
			/*get the degrees values*/
			if (home_mode==1)
			{
				LCD_CLEAR_Screen();
				LCD_send_string("Homing Mode ON");
				
			}
			else
			{
				LCD_send_cmd(DISPLAY_ON_CURSOR_ON);
				LCD_send_string("Degree1:");
				for (i=0;i<=2;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					degree1[i]=pressed-48;
					pressed=NOT_PRESSED;
				}
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("Degree2:");
				for (i=0;i<=2;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					degree2[i]=pressed-48;
					pressed=NOT_PRESSED;
				}
			}
			
			_delay_ms(1000);
			LCD_CLEAR_Screen();
			
			if (point_mode==1)
			{
				Call_slave2(POINTING_MODE);
				slew_seconds=0;
				slew_minutes=0;
				point_mode=0;
			} 
			else if (slew_mode==1)
			{
				Call_slave2(SLEWING_MODE);
				slew_seconds=0;
				slew_minutes=0;
				slew_time1[0]=0;
				slew_time1[1]=0;
				slew_time2[0]=0;
				slew_time2[1]=0;
				/*scan the second time*/
				LCD_CLEAR_Screen();
				LCD_send_string("First time>>>");
				_delay_ms(1000);
				LCD_CLEAR_Screen();
				LCD_send_string("Seconds_1:");
				for (i=0;i<=1;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					slew_time1[0]=slew_time1[0]*10+(pressed-48);
					pressed=NOT_PRESSED;
				}
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("Minutes_1:");
				for (i=0;i<=1;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					slew_time1[1]=slew_time1[1]*10+(pressed-48);
					pressed=NOT_PRESSED;
				}
				/*
				slew_seconds=slew_time[0];
				slew_minutes=slew_time[1];
				*/
				/*scan the second time*/
				LCD_CLEAR_Screen();
				LCD_send_string("Second time>>>");
				_delay_ms(1000);
				LCD_CLEAR_Screen();
				LCD_send_string("Seconds_2:");
				for (i=0;i<=1;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					slew_time2[0]=slew_time2[0]*10+(pressed-48);
					pressed=NOT_PRESSED;
				}
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("Minutes_2:");
				for (i=0;i<=1;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					slew_time2[1]=slew_time2[1]*10+(pressed-48);
					pressed=NOT_PRESSED;
				}
				
				slew_mode=0;
			}
			else if (track_mode==1)
			{
				Call_slave2(TRACKING_MODE);
				LCD_send_string("Not provided yet");
				track_mode=0;
			}
			else if (home_mode==1)
			{
				Call_slave2(HOMING_MODE);
				for (i=0;i<=2;i++)
				{
					degree1[i]=0;
				}
				for (i=0;i<=2;i++)
				{
					degree2[i]=0;
				}
				home_mode=0;
			}
			else
			{
				LCD_send_string("Wrong Input");
			}
			_delay_ms(2000);
			LCD_CLEAR_Screen();
			LCD_send_cmd(DISPLAY_ON_CURSOR_OFF);
			LCD_send_string("Sending");
			//Call_slave2()
			for (i=0;i<=2;i++)
			{
				_delay_ms(50);
				Call_slave2(degree1[i]);
				LCD_send_char('.');
			}
			for (i=0;i<=2;i++)
			{
				_delay_ms(50);
				Call_slave2(degree2[i]);
				LCD_send_char('.');
			}
			Call_slave2(slew_time1[0]);//slew_seconds1
			LCD_send_char('.');
			_delay_ms(50);
			Call_slave2(slew_time1[1]);//slew_minutes1
			LCD_send_char('.');
			_delay_ms(50);
			Call_slave2(slew_time2[0]);//slew_seconds2
			LCD_send_char('.');
			_delay_ms(50);
			Call_slave2(slew_time2[1]);//slew_minutes2
			LCD_send_char('.');
			_delay_ms(50);
			Call_slave2(0xf0);
			LCD_CLEAR_Screen();
			degree_mode=0;
			main_menu=1;
		} 
		else if (settings_mode==1)
		{
			/*LCD_send_string("settings");
			_delay_ms(1000);*/
			LCD_CLEAR_Screen();
			if (set_time==1)
			{
				Call_slave2(SET_TIME);
				_delay_ms(50);
				LCD_send_string("Hours:Mins:Secs");
				LCD_MOVE_CURSOR(2,1);
				for (i=0;i<=5;i++)
				{
					do
					{
						pressed=Keypad_READ('c',0,'c',4);
					} while (pressed==NOT_PRESSED);
					LCD_send_char(pressed);
					time[i]=pressed-48;
				}
				LCD_CLEAR_Screen();
				LCD_send_string("sending");
				for (i=0;i<=5;i++)
				{
					_delay_ms(50);
					Call_slave2(time[i]);
					LCD_send_char('.');
				}
				for (i=0;i<=3;i++)
				{
					_delay_ms(50);
					Call_slave2(0);
					LCD_send_char('.');
				}
				_delay_ms(50);
				Call_slave2(0xf0);
				LCD_send_char('.');
			}
			set_time=0;
			settings_mode=0;
			main_menu=1;
		}
		else
		{
		}
    }
}
static void Call_slave1 (unsigned char data)
{
	_delay_ms(1);
	/*DIO_output_PIN_on_port('b',0,1);
	//_delay_ms(500);
	DIO_output_PIN_on_port('b',0,0);*/
	SPI_MASTER_Transmit_char(data,4);
}
static void Call_slave2 (unsigned char data)
{
	_delay_ms(1);
	/*DIO_output_PIN_on_port('a',0,1);
	//_delay_ms(500);
	DIO_output_PIN_on_port('a',0,0);*/
	SPI_MASTER_Transmit_char(data,3);
}
ISR(INT0_vect)
{
	LCD_CLEAR_Screen();
	LCD_send_string("Heat Warning!!!");
	LED_ON('d',7);
}

