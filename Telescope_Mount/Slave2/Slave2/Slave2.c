/*
 * Slave2.c
 *
 * Created: 23-Aug-23 7:44:30 PM
 *  Author: MT
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "Communication_Protocol.h"
#include "LCD.h"
#include "DIO.h"
#include "STD_BIT_MACRO.h"
#include "TIMER.h"


#define POINTING_MODE 0xDD
#define SLEWING_MODE 0xDE
#define TRACKING_MODE 0xDF
#define HOMING_MODE 0xDC
#define SET_TIME 0xEE
#define check_mode 0xAA

//,pressed=NOT_PRESSED,first_digit,second_digit,i=0,c=0
unsigned char second=0,minute=0,hours=0,starting_sec=0,starting_min;
unsigned long starting_time=0,time=0;
void TIME_CLOCK (void);
void check_mode_fn(void);

	//sei();
	unsigned char d1[12]={0,0,0};
	//unsigned char d2[3]={0,0,0};
	unsigned char i=0,x,cmd=0x00,dr=0,slew_degree1=0,slew_degree2=0,s_seconds_1=0,s_minutes_1=0,s_seconds_2=0,s_minutes_2=0;
	unsigned long s_time_1=0,s_time_2=0;
	
int main(void)
{
	timer2_INIT_OVERFLOW_Interrupt();
	
	SEVEN_SEGMENT_INT('a');
	DIO_set_PIN_dir('d',0,1);
	DIO_set_PIN_dir('d',1,1);
	DIO_set_PIN_dir('b',0,1);
	DIO_set_PIN_dir('b',1,1);
	DIO_set_PIN_dir('b',2,1);
	DIO_set_PIN_dir('b',3,1);
	LCD_INIT();
	//_delay_ms(300);
	SPI_SLAVE_INIT();
	sei();
	DIO_set_PIN_dir('d',2,0);
	/*SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(GICR,INT0);*/
	//_delay_ms(500);
	unsigned short degree1=0,degree2=0;
	LCD_send_cmd(DISPLAY_ON_CURSOR_OFF);
	while(1)
	{
		TIME_CLOCK();
		_delay_ms(1);
		if (i>=1)
		{
			d1[i-1]=x;
			dr=0;
		}
		
		if (dr==0&d1[11]==0xf0)
			{
				degree1=0;
				degree2=0;
				LCD_CLEAR_Screen();
				if (d1[0]==SET_TIME)
				{
					LCD_send_string("setting time");
					second=(d1[5]*10)+d1[6];
					minute=(d1[3]*10)+d1[4];
					hours=(d1[1]*10)+d1[2];
					TIME_CLOCK();
					for (i=0;i<=11;i++)
					{
						d1[i]=0;
					}
					i=0;
					dr=1;
					_delay_ms(1000);
					LCD_CLEAR_Screen();
					//_delay_ms(1000);
				} 
				else if (d1[0]==check_mode&d1[1]==check_mode)
				{
					check_mode_fn();
					for (i=0;i<=11;i++)
					{
						d1[i]=0;
					}
					i=0;
					dr=1;
				}
				else
				{
					LCD_MOVE_CURSOR(1,1);
					LCD_send_string("degree1:");
					for (i=1;i<=3;i++)
					{
						LCD_send_char(d1[i]+48);
						degree1=scan_value(d1[i]+48,degree1);
					}
					LCD_MOVE_CURSOR(2,1);
					LCD_send_string("degree2:");
					for (i=4;i<=6;i++)
					{
						LCD_send_char(d1[i]+48);
						degree2=scan_value(d1[i]+48,degree2);
					}
					s_seconds_1=d1[7];
					s_minutes_1=d1[8];
					s_seconds_2=d1[9];
					s_minutes_2=d1[10];
					s_time_1=(s_seconds_1+s_minutes_1*60);
					s_time_2=(s_seconds_2+s_minutes_2*60);
				}
				i=0;
				dr=1;
				//d1[9]=0x00
				//_delay_ms(2000);
				d1[11]=0xff;
			}
			
			if (d1[0]==POINTING_MODE&d1[11]==0xff&dr==1)
			{
				
				timer1_INIT_WAVE_Fast_PMW_A(degree1);
				timer1_INIT_WAVE_Fast_PMW_B(degree2);
				for (i=0;i<=11;i++)
				{
					d1[i]=0;
				}
				i=0;
				degree1=0;
				degree2=0;
				//dr=0;
				//_delay_ms(2000);
			}
			else if (d1[0]==SLEWING_MODE&d1[11]==0xff&dr>=1)
			{
				
				/*starting_sec=second;
				starting_min=minute;*/
				dr++;
				if (s_time_1>0)
				{
					slew_degree1+=(degree1/(s_seconds_1+s_minutes_1*60));
					timer1_INIT_WAVE_Fast_PMW_A(slew_degree1);
					s_time_1--;
				}
				else if (s_time_1==0)
				{
				}
				if (s_time_2>0)
				{
					slew_degree2+=(degree2/(s_seconds_2+s_minutes_2*60));
					timer1_INIT_WAVE_Fast_PMW_B(slew_degree2);
					s_time_2--;
				}
				else if (s_time_2==0)
				{
				}
				
				/*to exit mode*/
				
				
				if (dr==1)
				{
					LCD_CLEAR_Screen();
					LCD_MOVE_CURSOR(1,1);
					LCD_send_string("degree1:");
					LCD_MOVE_CURSOR(2,1);
					LCD_send_string("degree2:");
					
				}
				LCD_MOVE_CURSOR(1,9);
				LCD_send_char(' ');
				print_val(slew_degree1);
				LCD_send_char(' ');
				LCD_MOVE_CURSOR(2,9);
				LCD_send_char(' ');
				print_val(slew_degree2);
				LCD_send_char(' ');
				if (s_time_1==0&s_time_2==0)
				{
					for (i=0;i<=11;i++)
					{
						d1[i]=0;
					}
					i=0;
					degree1=0;
					degree2=0;
					s_seconds_1=0,s_seconds_2=0,s_minutes_1=0,s_minutes_2=0;
					slew_degree1=0,slew_degree2=0;
				}
				starting_time=(second)+(minute*60)+(hours*60*60);
				do 
				{
					TIME_CLOCK();
					time=(second)+(minute*60)+(hours*60*60);
				} while (time==starting_time);
			}
			else if (d1[0]==HOMING_MODE&d1[11]==0xff&dr==1)
			{
				timer1_INIT_WAVE_Fast_PMW_A(0);
				timer1_INIT_WAVE_Fast_PMW_B(0);
				LCD_CLEAR_Screen();
				LCD_send_string("degree1:");
				LCD_send_char('0');
				LCD_MOVE_CURSOR(2,1);
				LCD_send_string("degree2:");
				LCD_send_char('0');
				for (i=0;i<=11;i++)
				{
					d1[i]=0;
				}
				i=0;
				degree1=0;
				degree2=0;
			}
			else if (d1[0]==TRACKING_MODE&d1[11]==0xff&dr==1)
			{
				LCD_CLEAR_Screen();
				LCD_send_string("Not Supported yet");
				degree1=0;
				degree2=0;
				for (i=0;i<=11;i++)
				{
					d1[i]=0;
				}
				i=0;
			}
			else
			{
				/*LCD_CLEAR_Screen();
				LCD_send_string("Wrong input");*/
			}
		//POSITION REFREANCE - ACTUAL POSITION = ERROR
		//0.00056 DEGREE
		
	}
}
ISR(SPI_STC_vect)
{
	x=SPI_SLAVE_recieve_char(1);
	i++;
}
ISR(TIMER2_OVF_vect)
{
	second++;
}
void TIME_CLOCK (void)
{
		SEVEN_SEGMENT_write('a',second%10,1);
		DIO_output_PIN_on_port('b',3,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('b',3,1);
		
		SEVEN_SEGMENT_write('a',second/10,1);
		DIO_output_PIN_on_port('b',2,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('b',2,1);
		
		SEVEN_SEGMENT_write('a',minute%10,1);
		DIO_output_PIN_on_port('b',1,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('b',1,1);
		
		SEVEN_SEGMENT_write('a',minute/10,1);
		DIO_output_PIN_on_port('b',0,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('b',0,1);
		
		SEVEN_SEGMENT_write('a',hours%10,1);
		DIO_output_PIN_on_port('d',1,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('d',1,1);
		
		SEVEN_SEGMENT_write('a',hours/10,1);
		DIO_output_PIN_on_port('d',0,0);
		_delay_ms(1);
		DIO_output_PIN_on_port('d',0,1);
		
		if (second>=60)
        {
			second=0;
			minute++;
        } 
        else if (minute>=60)
        {
			minute=0;
			hours++;
        } 
        else if (hours>=24)
        {
			hours=0;
        }
}
void check_mode_fn (void)
{
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
	SEVEN_SEGMENT_write('a',8,1);
	DIO_output_PIN_on_port('b',3,0);
	DIO_output_PIN_on_port('b',2,0);
	DIO_output_PIN_on_port('b',1,0);
	DIO_output_PIN_on_port('b',0,0);
	DIO_output_PIN_on_port('d',1,0);
	DIO_output_PIN_on_port('d',0,0);
	_delay_ms(10000);
	TIME_CLOCK();
	LCD_CLEAR_Screen();
}
