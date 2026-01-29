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

void inicializar_LCD_8bits(void);
void LCD_CMD(char a);
void LCD_write_char(char c);
void LCD_write_string(char *a);
void LCD_set_cursor(char c, char f);
#endif /* LCD_H_ */