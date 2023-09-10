/*
 * LCD.h
 *
 * Created: 26-Jul-23 7:36:07 PM
 *  Author: MT
 */ 


#ifndef LCD_H_
#define LCD_H_

#define CLEAR_SCREEN 0x01
#define RETURN_HOME 0x02
#define ENTRY_MODE_LTR 0x04
#define ENTRY_MODE_RTL 0x06
#define DISPLAY_ON_CURSOR_ON 0x0e
#define DISPLAY_ON_CURSOR_OFF 0x0c
#define DISPLAY_SHIFT_LEFT 0x18
#define DISPLAY_SHIFT_RIGHT 0x1c


void static enable_pulse (void);
void LCD_send_char(unsigned char letter);
void LCD_send_cmd (unsigned char cmd);
void LCD_CLEAR_Screen (void);
void LCD_INIT (void);
void LCD_MOVE_CURSOR (unsigned char row,unsigned char coloumn);
void LCD_send_string (char*ptr);
int scan_value (unsigned char asci,int value);
void print_val (int val);

#endif /* LCD_H_ */