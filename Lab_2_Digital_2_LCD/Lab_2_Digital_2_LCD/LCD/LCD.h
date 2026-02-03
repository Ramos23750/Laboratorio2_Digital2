/*
 * LCD.h
 *
 * Created: 1/27/2026 3:50:27 PM
 *  Author: diegu
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#ifndef LCD_H_
#define LCD_H_

void init8bits(void);
void LCDCMD(char a);
void LCD_WRITE_CHAR(char c);
void LCD_WRITE_STRING(char *a);
void LCDPORT(char a);
void LCD_SET_CURSOR(char c, char f);
void LCD_SHIFT_RIGHT(void);
void LCD_SHIFT_LEFT(void);
#endif /* LCD_H_ */